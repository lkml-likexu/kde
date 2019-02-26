

#### [PATCH v7 0/9] vfio/mdev: IOMMU aware mediated device
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
  - Detect both IOMMU and PCI endpoint devices supporting
    the feature (aux-domain here) without the host driver
    dependency.

* iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX)
  - Check the enabling status of the feature (aux-domain
    here). The aux-domain interfaces are available only
    if this returns true.

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
by the IOMMU units. The first part of this series (PATCH 1/09~6/09)
adds the interfaces and implementation of the multiple domains per
device. The second part (PATCH 7/09~9/09) adds the iommu device
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
  v6->v7:
  - Update PATCH 1/9 and the cover letter with Jean's comments
    posted at https://patchwork.kernel.org/patch/10809093/.
  - Add Jean's Reviewed-by in patch 1,7,8,9.

  v5->v6:
  - Add a new API iommu_dev_feature_enabled() to check whether
    an IOMMU specific feature is enabled.
  - Rework the vt-d specific per device feature ops according
    to Joerg's comments. [https://lkml.org/lkml/2019/1/11/302].
  - PATCH 2/9 is added to move intel_iommu_enable_pasid() out
    of the scope of CONFIG_INTEL_IOMMU_SVM without functional
    changes.
  - All patches are rebased on top of vt-d branch of Joerg's
    iommu tree.

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

Lu Baolu (9):
  iommu: Add APIs for multiple domains per device
  iommu/vt-d: Move enable pasid out of CONFIG_INTEL_IOMMU_SVM
  iommu/vt-d: Add per-device IOMMU feature ops entries
  iommu/vt-d: Move common code out of iommu_attch_device()
  iommu/vt-d: Aux-domain specific domain attach/detach
  iommu/vt-d: Return ID associated with an auxiliary domain
  vfio/mdev: Add iommu related member in mdev_device
  vfio/type1: Add domain at(de)taching group helpers
  vfio/type1: Handle different mdev isolation type

 drivers/iommu/intel-iommu.c      | 399 ++++++++++++++++++++++++++++---
 drivers/iommu/intel-svm.c        |  19 +-
 drivers/iommu/iommu.c            |  96 ++++++++
 drivers/vfio/mdev/mdev_core.c    |  18 ++
 drivers/vfio/mdev/mdev_private.h |   1 +
 drivers/vfio/vfio_iommu_type1.c  | 132 ++++++++--
 include/linux/intel-iommu.h      |  13 +-
 include/linux/iommu.h            |  70 ++++++
 include/linux/mdev.h             |  14 ++
 9 files changed, 709 insertions(+), 53 deletions(-)
```
#### [PATCH v2 00/16] KVM: PPC: Book3S HV: add XIVE native exploitation
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIOs to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter subengine.

PowerNV/baremetal Linux runs natively under XIVE but sPAPR guests need
special support from the hypervisor to do the same. This is called the
XIVE native exploitation mode and today, it can be activated under the
PowerPC Hypervisor, pHyp. However, Linux/KVM lacks XIVE native support
and still offers the old interrupt mode interface using a KVM device
implementing the XICS hcalls over XIVE.

The following series is proposal to add the same support under KVM.

A new KVM device is introduced for the XIVE native exploitation
mode. It reuses most of the XICS-over-XIVE glue implementation
structures which are internal to KVM but has a completely different
interface. A set of KVM device ioctls provide support for the
hypervisor calls, all handled in QEMU, to configure the sources and
the event queues. From there, all interrupt control is transferred to
the guest which can use MMIOs.

These MMIO regions (ESB and TIMA) are exposed to guests in QEMU,
similarly to VFIO, and the associated VMAs are populated dynamically
with the appropriate pages using a fault handler. These are now
implemented using mmap()s of the KVM device fd.

Migration has its own specific needs regarding memory. The patchset
provides a specific control to quiesce XIVE before capturing the
memory. The save and restore of the internal state is based on the
same ioctls used for the hcalls.

On a POWER9 sPAPR machine, the Client Architecture Support (CAS)
negotiation process determines whether the guest operates with a
interrupt controller using the XICS legacy model, as found on POWER8,
or in XIVE exploitation mode. Which means that the KVM interrupt
device should be created at runtime, after the machine has started.
This requires extra support from KVM to destroy KVM devices. It is
introduced at the end of the patcshet as it still requires some
attention and a XIVE-only VM would not need.

This is 5.2 material. I expect a couple of respin for fixes, and the
OPAL patches have not yet been merged.


GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.0

OPAL:

  https://github.com/legoater/skiboot/commits/xive


Thanks,

C.

Changes since v1:

 - Better documentation (was missing)
 - Nested support. XIVE not advertised on non PowerNV platforms. This
   is a good way to test the fallback on QEMU emulated devices.
 - ESB and TIMA special mapping done using the KVM device fd
 - All hcalls moved to QEMU. Dropped the patch moving the hcall flags.
 - Reworked of the KVM device ioctl controls to support hcalls and
   migration needs to capture/save states
 - Merged the control syncing XIVE and marking the EQ page dirty
 - Fixed passthrough support using the KVM device file address_space
   to clear the ESB pages from the mapping
 - Misc enhancements and fixes 

Cédric Le Goater (16):
  powerpc/xive: add OPAL extensions for the XIVE native exploitation
    support
  KVM: PPC: Book3S HV: add a new KVM device for the XIVE native
    exploitation mode
  KVM: PPC: Book3S HV: XIVE: introduce a new capability
    KVM_CAP_PPC_IRQ_XIVE
  KVM: PPC: Book3S HV: XIVE: add a control to initialize a source
  KVM: PPC: Book3S HV: XIVE: add a control to configure a source
  KVM: PPC: Book3S HV: XIVE: add controls for the EQ configuration
  KVM: PPC: Book3S HV: XIVE: add a global reset control
  KVM: PPC: Book3S HV: XIVE: add a control to sync the sources
  KVM: PPC: Book3S HV: XIVE: add a control to dirty the XIVE EQ pages
  KVM: PPC: Book3S HV: XIVE: add get/set accessors for the VP XIVE state
  KVM: introduce a 'mmap' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: add a TIMA mapping
  KVM: PPC: Book3S HV: XIVE: add a mapping for the source ESB pages
  KVM: PPC: Book3S HV: XIVE: add passthrough support
  KVM: introduce a KVM_DESTROY_DEVICE ioctl
  KVM: PPC: Book3S HV: XIVE: clear the vCPU interrupt presenters

 arch/powerpc/include/asm/kvm_host.h           |    2 +
 arch/powerpc/include/asm/kvm_ppc.h            |   32 +
 arch/powerpc/include/asm/opal-api.h           |   11 +-
 arch/powerpc/include/asm/opal.h               |    7 +
 arch/powerpc/include/asm/xive.h               |   17 +
 arch/powerpc/include/uapi/asm/kvm.h           |   48 +
 arch/powerpc/kvm/book3s_xive.h                |   31 +
 include/linux/kvm_host.h                      |    1 +
 include/uapi/linux/kvm.h                      |   10 +
 arch/powerpc/kvm/book3s.c                     |   31 +-
 arch/powerpc/kvm/book3s_xics.c                |   19 +
 arch/powerpc/kvm/book3s_xive.c                |  149 ++-
 arch/powerpc/kvm/book3s_xive_native.c         | 1171 +++++++++++++++++
 arch/powerpc/kvm/powerpc.c                    |   33 +
 arch/powerpc/sysdev/xive/native.c             |  110 ++
 virt/kvm/kvm_main.c                           |   49 +
 Documentation/virtual/kvm/api.txt             |   28 +
 Documentation/virtual/kvm/devices/xive.txt    |  190 +++
 arch/powerpc/kvm/Makefile                     |    2 +-
 .../powerpc/platforms/powernv/opal-wrappers.S |    3 +
 20 files changed, 1896 insertions(+), 48 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
```
#### [PATCH v3 0/2] KVM: arm/arm64: Add VCPU workarounds firmware register
##### From: Andre Przywara <andre.przywara@arm.com>

```c

Hi,

Aside from a rebase against kvm-arm/next, this update introduces a new
UNAFFECTED value for WORKAROUND_1, which is not used at the moment, but
will become useful with some patches extending the host kernel workaround
code [1]. We add the value to the ABI already.
Also we now require an exact match for the two WORKAROUND_1 levels, as
we can't allow a guest to migrate from a system with an effectively
unknown workaround state to a system which requires an active guest
workaround.
Now tested with actual migration, see below.

Cheers,
Andre

-----------------------------
Workarounds for Spectre variant 2 or 4 vulnerabilities require some help
from the firmware, so KVM implements an interface to provide that for
guests. When such a guest is migrated, we want to make sure we don't
loose the protection the guest relies on.

This introduces two new firmware registers in KVM's GET/SET_ONE_REG
interface, so userland can save the level of protection implemented by
the hypervisor and used by the guest. Upon restoring these registers,
we make sure we don't downgrade and reject any values that would mean
weaker protection.
The protection level is encoding in the lower 4 bits, with smaller
values indicating weaker protection.

Patch 1 implements the two firmware registers, patch 2 adds the
documentation.

ARM(32) is a bit of a pain (again), as the firmware register interface
is shared, but 32-bit does not implement all the workarounds.
For now I stuffed two wrappers into kvm_emulate.h, which doesn't sound
like the best solution. Happy to hear about better solutions.

This has been tested with migration between two Juno systems. Out of the
box they advertise identical workaround levels, and migration succeeds.
However when disabling the A57 cluster on one system, WORKAROUND_1 is
not needed and the host kernel disables this. Migration between the two
now fails, as expected.

Please have a look and comment!

Cheers,
Andre

[1] http://lists.infradead.org/pipermail/linux-arm-kernel/2019-January/627791.html

Changelog:
v1 .. v2:
- complete rework of WORKAROUND_2 presentation to use a linear scale,
  dropping the complicated comparison routine

v2 .. v3:
- rebase against latest kvm-arm/next
- introduce UNAFFECTED value for WORKAROUND_1
- require exact match for WORKAROUND_1 levels

Andre Przywara (2):
  KVM: arm/arm64: Add save/restore support for firmware workaround state
  KVM: doc: add API documentation on the KVM_REG_ARM_WORKAROUNDS
    register

 Documentation/virtual/kvm/arm/psci.txt |  24 +++++
 arch/arm/include/asm/kvm_emulate.h     |  10 +++
 arch/arm/include/uapi/asm/kvm.h        |  10 +++
 arch/arm64/include/asm/kvm_emulate.h   |  14 +++
 arch/arm64/include/uapi/asm/kvm.h      |   9 ++
 virt/kvm/arm/psci.c                    | 119 +++++++++++++++++++++----
 6 files changed, 170 insertions(+), 16 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/2] Misc patches
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c

Primary purpose of this patch series is to improve tap13 output to be
fit for CI purposes. While almost ready to submit, stumbled upon a
glitch in the most recently added support for specifying desired tests
on the command line, so added another patch to fix that up.


v2:
Patch 1:
- Added the more elaborate patch description that got somehow lost in
  my inital post
- Output tap13 as the testcases progress instead of once at the end.
  Note: Tried to use flock() for the locking required, but that didn't
        really help to protect a file against concurrent access. Went
        for a surprisingly simple approach that does the job as well.

Patch 2:
- Again, a piece got lost on the initial version, whereby desired tests
  specified on the command line would get lost. Fixed.



Stefan Raspl (2):
  tap13: list testcases individually
  run_tests: fix command line options handling

 run_tests.sh         | 57 +++++++++++++++++++++++++++++++---------------------
 scripts/runtime.bash | 47 +++++++++++++++++++++++++++++++++++--------
 2 files changed, 73 insertions(+), 31 deletions(-)
```
#### [PATCH V3 00/10] X86/KVM/Hyper-V: Add HV ept tlb range list flush
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

```c

From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patchset is to introduce hv ept tlb range list flush function
support in the KVM MMU component. Flushing ept tlbs of several address
range can be done via single hypercall and new list flush function is
used in the kvm_mmu_commit_zap_page() and FNAME(sync_page). This patchset
also adds more hv ept tlb range flush support in more KVM MMU function.

This patchset is based on the fix patch "x86/Hyper-V: Fix definition HV_MAX_FLUSH_REP_COUNT".
(https://www.mail-archive.com/linux-kernel@vger.kernel.org/msg1939455.html)

Change since v2:
	1) Fix calculation of flush pages in the kvm_fill_hv_flush_list_func()
	2) Change the logic of setting/clearing last_level flag

Change since v1:
	1) Make flush list as a hlist instead of list in order to 
	keep struct kvm_mmu_page size.
	2) Add last_level flag in the struct kvm_mmu_page instead
	of spte pointer
	3) Move tlb flush from kvm_mmu_notifier_clear_flush_young() to kvm_age_hva()
	4) Use range flush in the kvm_vm_ioctl_get/clear_dirty_log()


Lan Tianyu (10):
  X86/Hyper-V: Add parameter offset for
    hyperv_fill_flush_guest_mapping_list()
  KVM/VMX: Fill range list in kvm_fill_hv_flush_list_func()
  KVM/MMU: Introduce tlb flush with range list
  KVM/MMU: Use range flush in sync_page()
  KVM/MMU: Flush tlb directly in the kvm_mmu_slot_gfn_write_protect()
  KVM: Add kvm_get_memslot() to get memslot via slot id
  KVM: Use tlb range flush in the kvm_vm_ioctl_get/clear_dirty_log()
  KVM: Add flush parameter for kvm_age_hva()
  KVM/MMU: Use tlb range flush in the kvm_age_hva()
  KVM/MMU: Add last_level flag in the struct mmu_spte_page

 arch/arm/include/asm/kvm_host.h     |  3 +-
 arch/arm64/include/asm/kvm_host.h   |  3 +-
 arch/mips/include/asm/kvm_host.h    |  3 +-
 arch/mips/kvm/mmu.c                 | 11 ++++++--
 arch/powerpc/include/asm/kvm_host.h |  3 +-
 arch/powerpc/kvm/book3s.c           | 10 +++++--
 arch/powerpc/kvm/e500_mmu_host.c    |  3 +-
 arch/x86/hyperv/nested.c            |  4 +--
 arch/x86/include/asm/kvm_host.h     | 11 +++++++-
 arch/x86/include/asm/mshyperv.h     |  2 +-
 arch/x86/kvm/mmu.c                  | 55 ++++++++++++++++++++++++++++++-------
 arch/x86/kvm/mmu.h                  |  7 +++++
 arch/x86/kvm/paging_tmpl.h          |  5 ++--
 arch/x86/kvm/vmx/vmx.c              | 18 ++++++++++--
 arch/x86/kvm/x86.c                  | 16 ++++++++---
 include/linux/kvm_host.h            |  1 +
 virt/kvm/arm/mmu.c                  | 13 +++++++--
 virt/kvm/kvm_main.c                 | 51 ++++++++++++++--------------------
 18 files changed, 156 insertions(+), 63 deletions(-)
```
#### [PATCH v4 0/7] vfio: ap: AP Queue Interrupt Control
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

This patch implement PQAP/AQIC interception in KVM.

To implement this we need to add a new structure, vfio_ap_queue,to be
able to retrieve the mediated device associated with a queue and specific
values needed to register/unregister the interrupt structures:
 - APQN: to be able to issue the commands and search for queue structures
 - NIB : to unpin the NIB on clear IRQ
 - ISC : to unregister with the GIB interface
 - MATRIX: a pointer to the matrix mediated device
 - LIST: the list_head to handle the vfio_queue life cycle

Having this structure and the list management greatly ease the handling
of the AP queues and diminues the LOCs needed in the vfio_ap driver by
more than 150 lines in comparison with the previous version.


0) Queues life cycle

vfio_ap_queues are created on probe

We define one bucket on the matrix device to store the free vfio_ap_queues,
the queues not assign to any matrix mediated device.

We define one bucket on each matrix mediated device to hold the
vfio_ap_queues belonging to it.

vfio_ap_queues are deleted on remove

This makes the search for a queue easy and the detection of assignent
incoherency obvious (the queue is not avilable) and simplifies assignment.


1) Phase 1, probe and remove from vfio_ap_queue

The vfio_ap_queue structures are dynamically allocated and setup
when a queue is probed by the ap_vfio_driver.
The vfio_ap_queue is linked to the ap_queue device as the driver data.

The new The vfio_ap_queue is put on a free_list belonging to the
matrix device.

The vfio_ap_queue are free during remove.


2) Phase 2, assignment of vfio_ap_queue to a mediated device

When a APID is assigned we look for APQI already assigned to
the matrix mediated device and associate all the queue with the
APQN = (APID,APQI) to the mediated device by adding them to
the mediated device queue list.
We do the same when a APQI is assigned.

If any queue with a matching APQN can not be found on the matrix
device free list it means it is already associated to another matrix
mediated device and no queue is added to the matrix mediated device.

3) Phase 3, starting the guest

When the VFIO device is opened the PQAP callback and a pointer to
the matrix mediated device are set inside KVM during the open callback.

When the device is closed or if a queue is removed, the vfio_ap_queue is
dissociated from the mediated device.


4) Phase 3 intercepting the PQAP/AQIC instruction

On interception of the PQAP/AQIC instruction, the interception code
makes sure the pqap_hook is initialized and allowed to be called
and call it.
Otherwise it reports the usual -EOPNOTSUPP return code to let
QEMU handle the fault.
  
the pqap callback search for the queue asociated with the APQN
stored in the register 0, setting the code to "illegal APQN"
if the vfio_ap_queue can not be found.

Depending on the "i" bit of the register 1, the pqap callback
setup or clear the interruption by calling the host format PQAP/AQIC
instruction.
When seting up the interruption it uses the NIB and the guest ISC
provided by the guest and the host ISC provided by the registration
to the GIB code, pin the NIB and also stores ISC and NIB inside
the vfio_ap_queue structure.
When clearing the interrupt it retrieves the host ISC to unregister
with the GIB code and unpin the NIB.

We take care when enabling GISA that the guest may have issued a
reset and will not need to disable the interuptions before
re-enabling interruptions.


5) Phase 4 clean dissociation from the mediated device on remove

On removing of the AP device the remove callback is called.
To be sure that the guest will not access the queue anymore
we clear the APID CRYCB bit.
Cleaning the APID, over the APQI, is chosen because the architecture
specifies that only the APID can be dynamically changed outside IPL.


6) Associated QEMU patch

There is a QEMU patch which is needed to enable the PQAP/AQIC
facility in the guest.

Posted in qemu-devel@nongnu.org as:
Message-Id: <1550146494-21085-1-git-send-email-pmorel@linux.ibm.com>


Pierre Morel (7):
  s390: ap: kvm: add PQAP interception for AQIC
  s390: ap: new vfio_ap_queue structure
  s390: ap: associate a ap_vfio_queue and a matrix mdev
  vfio: ap: register IOMMU VFIO notifier
  s390: ap: implement PAPQ AQIC interception in kernel
  s390: ap: Cleanup on removing the AP device
  s390: ap: kvm: Enable PQAP/AQIC facility for the guest

 arch/s390/include/asm/kvm_host.h      |   2 +
 arch/s390/kvm/priv.c                  |  52 +++
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/ap_bus.h          |   1 +
 drivers/s390/crypto/vfio_ap_drv.c     |  62 +++-
 drivers/s390/crypto/vfio_ap_ops.c     | 630 +++++++++++++++++++++++-----------
 drivers/s390/crypto/vfio_ap_private.h |  15 +
 7 files changed, 563 insertions(+), 200 deletions(-)
```
#### [PATCH 0/2] Fix vfio-ccw handling of TIC recursion
##### From: Eric Farman <farman@linux.ibm.com>

```c

Per the discussion [1] about a problem with how vfio-ccw calculates
the length of a channel program (specifically when using the
forthcoming QEMU BIOS code for DASD IPL), I present this fix.

Patch 1 fixes the problem, and is over-engineered
for readability sake.

Patch 2 takes the functions from Patch 1, and refactors the
existing code to make other areas a little easier to understand.
(I hope.)

I've been running fio for over 24 hours now, and have seen
zero hours.  Previously, I would have probably seen "a few"
errors by now, where prior to the original fix I would've seen
"many" errors.  Further tests are still ongoing.

[1] https://marc.info/?l=linux-s390&m=155063096321940&w=2

Eric Farman (2):
  s390/cio: Fix vfio-ccw handling of recursive TICs
  s390/cio: Use cpa range elsewhere within vfio-ccw

 drivers/s390/cio/vfio_ccw_cp.c | 55 ++++++++++++++++++++++++++++++++----------
 1 file changed, 42 insertions(+), 13 deletions(-)
Reviewed-by: Farhan Ali <alifm@linux.ibm.com> for the series.
```
