

#### [PATCH v5 0/8] vfio/mdev: IOMMU aware mediated device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c

Hi,

The Mediate Device is a framework for fine-grained physical device
sharing across the isolated domains. Currently the mdev framework
is designed to be independent of the platform IOMMU support. As the
result, the DMA isolation relies on the mdev parent device in a
vendor specific way.

There are several cases where a mediated device could be protected
and isolated by the platform IOMMU. For example, Intel vt-d rev3.0
[1] introduces a new translation mode called 'scalable mode', which
enables PASID-granular translations. The vt-d scalable mode is the
key ingredient for Scalable I/O Virtualization [2] [3] which allows
sharing a device in minimal possible granularity (ADI - Assignable
Device Interface).

A mediated device backed by an ADI could be protected and isolated
by the IOMMU since 1) the parent device supports tagging an unique
PASID to all DMA traffic out of the mediated device; and 2) the DMA
translation unit (IOMMU) supports the PASID granular translation.
We can apply IOMMU protection and isolation to this kind of devices
just as what we are doing with an assignable PCI device.

In order to distinguish the IOMMU-capable mediated devices from those
which still need to rely on parent devices, this patch set adds one
new member in struct mdev_device.

* iommu_device
  - This, if set, indicates that the mediated device could
    be fully isolated and protected by IOMMU via attaching
    an iommu domain to this device. If empty, it indicates
    using vendor defined isolation.

Below helpers are added to set and get above iommu device in mdev core
implementation.

* mdev_set/get_iommu_device(dev, iommu_device)
  - Set or get the iommu device which represents this mdev
    in IOMMU's device scope. Drivers don't need to set the
    iommu device if it uses vendor defined isolation.

The mdev parent device driver could opt-in that the mdev could be
fully isolated and protected by the IOMMU when the mdev is being
created by invoking mdev_set_iommu_device() in its @create().

In the vfio_iommu_type1_attach_group(), a domain allocated through
iommu_domain_alloc() will be attached to the mdev iommu device if
an iommu device has been set. Otherwise, the dummy external domain
will be used and all the DMA isolation and protection are routed to
parent driver as the result.

On IOMMU side, a basic requirement is allowing to attach multiple
domains to a PCI device if the device advertises the capability
and the IOMMU hardware supports finer granularity translations than
the normal PCI Source ID based translation.

As the result, a PCI device could work in two modes: normal mode
and auxiliary mode. In the normal mode, a pci device could be
isolated in the Source ID granularity; the pci device itself could
be assigned to a user application by attaching a single domain
to it. In the auxiliary mode, a pci device could be isolated in
finer granularity, hence subsets of the device could be assigned
to different user level application by attaching a different domain
to each subset.

Below APIs are introduced in iommu generic layer for aux-domain
purpose:

* iommu_dev_has_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Check whether both IOMMU and device support IOMMU aux
    domain feature. Below aux-domain specific interfaces
    are available only after this returns true.

* iommu_dev_enable/disable_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Enable/disable device specific aux-domain feature.

* iommu_aux_attach_device(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_aux_detach_device(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_aux_get_pasid(domain, dev)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalable IOV needs
    to write this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

In order for the ease of discussion, sometimes we call "a domain in
auxiliary mode' or simply 'an auxiliary domain' when a domain is
attached to a device for finer granularity translations. But we need
to keep in mind that this doesn't mean there is a differnt domain
type. A same domain could be bound to a device for Source ID based
translation, and bound to another device for finer granularity
translation at the same time.

This patch series extends both IOMMU and vfio components to support
mdev device passing through when it could be isolated and protected
by the IOMMU units. The first part of this series (PATCH 1/08~5/08)
adds the interfaces and implementation of the multiple domains per
device. The second part (PATCH 6/08~8/08) adds the iommu device
attribute to each mdev, determines isolation type according to the
existence of an iommu device when attaching group in vfio type1 iommu
module, and attaches the domain to iommu aware mediated devices.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

Best regards,
Lu Baolu

Change log:
  v4->v5:
  - The iommu APIs have been updated with Joerg's proposal posted
    here https://www.spinics.net/lists/iommu/msg31874.html.
  - Some typos in commit message and comments have been fixed.
  - PATCH 3/8 was split from 4/8 to ease code review.
  - mdev->domain was removed and could bring back when there's a
    real consumer.
  - Other code review comments I received during v4 review period
    except the EXPORT_SYMBOL vs. EXPORT_SYMBOL_GPL in PATCH 6/8.
  - Rebase all patches to 5.0-rc1.

  v3->v4:
  - Use aux domain specific interfaces for domain attach and detach.
  - Rebase all patches to 4.20-rc1.

  v2->v3:
  - Remove domain type enum and use a pointer on mdev_device instead.
  - Add a generic interface for getting/setting per device iommu
    attributions. And use it for query aux domain capability, enable
    aux domain and disable aux domain purpose.
  - Reuse iommu_domain_get_attr() to retrieve the id in a aux domain.
  - We discussed the impact of the default domain implementation
    on reusing iommu_at(de)tach_device() interfaces. We agreed
    that reusing iommu_at(de)tach_device() interfaces is the right
    direction and we could tweak the code to remove the impact.
    https://www.spinics.net/lists/kvm/msg175285.html  
  - Removed the RFC tag since no objections received.
  - This patch has been submitted separately.
    https://www.spinics.net/lists/kvm/msg173936.html

  v1->v2:
  - Rewrite the patches with the concept of auxiliary domains.

Lu Baolu (8):
  iommu: Add APIs for multiple domains per device
  iommu/vt-d: Add per-device IOMMU feature ops entries
  iommu/vt-d: Move common code out of iommu_attch_device()
  iommu/vt-d: Aux-domain specific domain attach/detach
  iommu/vt-d: Return ID associated with an auxiliary domain
  vfio/mdev: Add iommu related member in mdev_device
  vfio/type1: Add domain at(de)taching group helpers
  vfio/type1: Handle different mdev isolation type

 drivers/iommu/intel-iommu.c      | 304 ++++++++++++++++++++++++++++---
 drivers/iommu/iommu.c            |  80 ++++++++
 drivers/vfio/mdev/mdev_core.c    |  18 ++
 drivers/vfio/mdev/mdev_private.h |   1 +
 drivers/vfio/vfio_iommu_type1.c  | 132 ++++++++++++--
 include/linux/intel-iommu.h      |  11 ++
 include/linux/iommu.h            |  61 +++++++
 include/linux/mdev.h             |  14 ++
 8 files changed, 585 insertions(+), 36 deletions(-)
```
#### [PATCH kvmtool v2 00/13] Implement reset of virtio devices
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

This series was developped by Jean-Philippe and is needed for a series
I'll be posting shortly after to load firmwares on arm kvmtool.

Currently, when a guest tries to reset a device, a lot of ressources
aren't reset (threads keep running, virtio queue keep their state, etc).

When the guest only does the reset to initialize the device and there
were no previous users, there is no noticeable issue. But when a guest
has a firmare + Linux, if the firmware uses a virtio device, Linux will
fail to probe that device.

This series aim to properly reset the virtio resources when the guests
requests it.

Reset of net vhost is unsupported for now.

Patch 1 is a bug fix on ioeventfd
Patch 2-6 provide the core support so devices can implement their reset
Patch 7-13 implements the reset for the various virtio devices

Changes since v1[1]:
- Fix build issue by removing reference to VIRTIO_CONFIG_S_NEEDS_RESET

[1] https://marc.info/?l=kvm&m=154392208726108&w=2

Thanks,

Julien

-->

Jean-Philippe Brucker (13):
  ioeventfd: Fix removal of ioeventfd
  virtio: Implement notify_status
  virtio: Add get_vq_count() callback
  virtio: Add get_vq() callback
  virtio: Add exit_vq() callback
  virtio: Add reset() callback
  net/uip: Add exit function
  virtio/net: Clean virtqueue state
  virtio/net: Implement device and virtqueue reset
  virtio/blk: Reset virtqueue
  threadpool: Add cancel() function
  virtio/p9: Implement reset
  virtio/console: Implement reset

 include/kvm/threadpool.h  |   2 +
 include/kvm/uip.h         |   6 ++
 include/kvm/virtio-mmio.h |   1 +
 include/kvm/virtio-pci.h  |   1 +
 include/kvm/virtio.h      |  29 ++++++-
 ioeventfd.c               |   6 +-
 net/uip/core.c            |  17 ++++
 net/uip/dhcp.c            |   6 ++
 net/uip/tcp.c             |  54 ++++++++++---
 net/uip/udp.c             |  41 ++++++++--
 util/threadpool.c         |  25 +++++-
 virtio/9p.c               |  33 +++++++-
 virtio/balloon.c          |  17 +++-
 virtio/blk.c              |  84 ++++++++++++++------
 virtio/console.c          |  49 ++++++++----
 virtio/core.c             |  42 ++++++++++
 virtio/mmio.c             |  52 +++++++++----
 virtio/net.c              | 195 +++++++++++++++++++++++++++++++++-------------
 virtio/pci.c              |  49 ++++++++----
 virtio/rng.c              |  12 ++-
 virtio/scsi.c             |  17 +++-
 21 files changed, 581 insertions(+), 157 deletions(-)
---
1.9.1
```
#### [PATCH kvmtool v2 0/6] arm: Add support for firmware booting
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

This series is based on the virtio reset series[1] posted earlier.

We would like to be able to load firmwares like UEFI in kvmtool.

The series contains:
A way to load the firmware into RAM and an option to be able to create
non-volatile memory zones and load data into them.

Those non-volatile memory are presented throught the DT with a node:

	<flash>@<addr> {
		compatible = "kvmtool,flash";
		reg = < <addr> <size> >;
		label = <name>;
	}

These are expected to be dealt with by specific kvmtool driver and not
to be picked up by existing drivers (although technically it is just
plain memory, mapped in the guest).


Changes since v1[2]:
* Added Andre's Reviewed-by tags.
* Changed the DT binding for nvmem.
* removed the requirement to provide firmware load address (defaults to
  the start of RAM).

[1] https://marc.info/?l=kvm&m=154712959125764&w=2
[2] https://marc.info/?l=kvm&m=154392208726108&w=2

Cheers,

Julien

-->

Julien Thierry (5):
  arm: Move firmware function
  builtin-run: Do not look for default kernel when firmware is provided
  arm: Support firmware loading
  kvm: Add arch specific reset
  arm: Support non-volatile memory

Sami Mujawar (1):
  rtc: Initialize the Register D for MC146818 RTC

 arm/fdt.c                                |  58 +++++++--
 arm/include/arm-common/kvm-arch.h        |   5 +-
 arm/include/arm-common/kvm-config-arch.h |  21 +++-
 arm/kvm.c                                | 207 +++++++++++++++++++++++++++++++
 builtin-run.c                            |  24 ++--
 hw/rtc.c                                 |   8 ++
 include/kvm/kvm.h                        |   1 +
 kvm.c                                    |   2 +
 mips/kvm.c                               |   4 +
 powerpc/kvm.c                            |   4 +
 x86/kvm.c                                |   4 +
 11 files changed, 317 insertions(+), 21 deletions(-)
---
1.9.1
```
#### [kvm-unit-tests PATCH v5 00/11] s390x: Add cross hypervisor and disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks.

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console
    * Binary generation in Makefile

v5:
	* Cleaned up linemode
	* Minor fixups and squash of sclp int and lock patches
	* Removed time patches, added phys alloc setup

v4:
	* Added sigp header file
	* Moved clearing to xgr instead of lm
	* Minor renames, comment additions

v3:
	* Rebased on David's SCLP fixes
	* Added binary generation make command
	* Split up cleanup and sclp common movement
	* Fixed whitespace problems
	* Added more comments
	* Added linemode buffer to get rid of line splits

v2:
	* Moved cleanup to the front and broadened patch
	* Split up SCLP patch into interrupt and linemode
	* Removed unneeded instructions
	* Improved comments and commit messages

Janosch Frank (11):
  s390x: Add Sigp header file
  s390x: Rename and cleanup sclp-ascii.c
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch and enable 64 bit addressing mode
  s390x: Add BSS clearing for non ELF boot
  s390x: Move common sclp data and functions to sclp.c
  s390x: Use interrupts in SCLP and add locking
  s390x: Add linemode console
  s390x: Add binary generation to makefile
  s390x: Add linemode buffer to fix newline on every print
  s390x: Initialize the physical allocator on mem init

 lib/s390x/asm/arch_def.h  |   1 +
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/asm/sigp.h      |  60 +++++++++++++
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |  13 +--
 lib/s390x/sclp-ascii.c    |  68 --------------
 lib/s390x/sclp-console.c  | 225 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/sclp.c          |  83 ++++++++++++++++-
 lib/s390x/sclp.h          |  62 ++++++++++++-
 s390x/Makefile            |  11 ++-
 s390x/cstart64.S          |  41 ++++++++-
 s390x/flat.lds            |  15 +++-
 12 files changed, 500 insertions(+), 93 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h
 delete mode 100644 lib/s390x/sclp-ascii.c
 create mode 100644 lib/s390x/sclp-console.c
```
#### [PATCH 00/14] KVM: x86/mmu: Remove fast invalidate mechanism
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Though not explicitly stated, for all intents and purposes the fast
invalidate mechanism was added to speed up the scenario where removing
a memslot, e.g. when accessing PCI ROM, caused KVM to flush all shadow
entries[1].

The other use cases of "flush everything" are VM teardown and handling
MMIO generation overflow, neither of which is a performance critial
path (see "Other Uses" below).

For the memslot case, zapping all shadow entries is overkill, i.e. KVM
only needs to zap the entries associated with the memslot, but KVM has
historically used a big hammer because if all you have is a hammer,
everything looks like a nail.

Rather than zap all pages when removing a memslot, zap only the shadow
entries associated with said memslot.  I see a performance improvement
of ~5% when zapping only the pages for the deleted memslot when using a
slightly modified version of the original benchmark[2][3][4] (I don't
have easy access to a system with hundreds of gigs of memory).

$ cat shell.sh
        #!/bin/sh

        echo 3 > /proc/sys/vm/drop_caches
        ./mmtest -c 8 -m 2000 -e ./rom.sh

I.e. running 8 threads and 2gb of memory per thread, time in milliseconds:

Before: 89.117
After:  84.768


With the memslot use case gone, maintaining the fast invalidate path
adds a moderate amount of complexity but provides little to no value.
Furhtermore, its existence may give the impression that it's "ok" to zap
all shadow pages.  Remove the fast invalidate mechanism to simplify the
code and to discourage future code from zapping all pages as using such
a big hammer should be a last resort.


History:
Flushing of shadow pages when removing a memslot was originally added
by commit 34d4cb8fca1f ("KVM: MMU: nuke shadowed pgtable pages and ptes
on memslot destruction"), and obviously emphasized functionality over
performance.  Commit 2df72e9bc4c5 ("KVM: split kvm_arch_flush_shadow")
added a path to allow flushing only the removed slot's shadow pages,
but x86 just redirected to the "zap all" flow.

Eventually, it became evident that zapping everything is slow, and so
x86 developed a more efficient hammer in the form of the fast invalidate
mechanism.

Other Uses:
When a VM is being destroyed, either there are no active vcpus, i.e.
there's no lock contention, or the VM has ungracefully terminated, in
which case we want to reclaim its pages as quickly as possible, i.e.
not release the MMU lock if there are still CPUs executing in the VM.

The MMIO generation scenario is almost literally a one-in-a-million
occurrence, i.e. is not a performance sensitive scenario.

It's worth noting that prior to the "fast invalidate" series being
applied, there was actually another use case of kvm_mmu_zap_all() in
emulator_fix_hypercall().  That may have contributed to improving the
performance of "zap all" instead of avoiding it altogether, but that
usage was removed by the series itself in commit 758ccc89b83c ("KVM:
x86: drop calling kvm_mmu_zap_all in emulator_fix_hypercall").

[1] https://lkml.kernel.org/r/1369960590-14138-1-git-send-email-xiaoguangrong@linux.vnet.ibm.com
[2] https://lkml.kernel.org/r/1368706673-8530-1-git-send-email-xiaoguangrong@linux.vnet.ibm.com
[3] http://lkml.iu.edu/hypermail/linux/kernel/1305.2/00277.html
[4] http://lkml.iu.edu/hypermail/linux/kernel/1305.2/00277/mmtest.tar.bz2


Sean Christopherson (14):
  KVM: x86/mmu: Move slot_level_*() helper functions up a few lines
  KVM: x86/mmu: Split remote_flush+zap case out of
    kvm_mmu_flush_or_zap()
  KVM: x86/mmu: Zap only the relevant pages when removing a memslot
  Revert "KVM: MMU: document fast invalidate all pages"
  Revert "KVM: MMU: drop kvm_mmu_zap_mmio_sptes"
  KVM: x86/mmu: Remove is_obsolete() call
  Revert "KVM: MMU: reclaim the zapped-obsolete page first"
  Revert "KVM: MMU: collapse TLB flushes when zap all pages"
  Revert "KVM: MMU: zap pages in batch"
  Revert "KVM: MMU: add tracepoint for kvm_mmu_invalidate_all_pages"
  Revert "KVM: MMU: show mmu_valid_gen in shadow page related
    tracepoints"
  Revert "KVM: x86: use the fast way to invalidate all pages"
  Revert "KVM: MMU: fast invalidate all pages"
  KVM: x86/mmu: Consolidate kvm_mmu_zap_all() and
    kvm_mmu_zap_mmio_sptes()

 Documentation/virtual/kvm/mmu.txt |  28 +--
 arch/x86/include/asm/kvm_host.h   |   7 +-
 arch/x86/kvm/mmu.c                | 325 ++++++++++++------------------
 arch/x86/kvm/mmu.h                |   1 -
 arch/x86/kvm/mmutrace.h           |  42 +---
 arch/x86/kvm/x86.c                |   3 +-
 6 files changed, 145 insertions(+), 261 deletions(-)
```
