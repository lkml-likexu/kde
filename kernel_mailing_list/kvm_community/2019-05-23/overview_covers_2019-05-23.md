

#### [PATCH 0/4] KVM: PPC: Book3S: Fix potential deadlocks
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

Recent reports of lockdep splats in the HV KVM code revealed that it
was taking the kvm->lock mutex in several contexts where a vcpu mutex
was already held.  Lockdep has only started warning since I added code
to take the vcpu mutexes in the XIVE device release functions, but
since Documentation/virtual/kvm/locking.txt specifies that the vcpu
mutexes nest inside kvm->lock, it seems that the new code is correct
and it is most of the old uses of kvm->lock that are wrong.

This series should fix the problems, by adding new mutexes that nest
inside the vcpu mutexes and using them instead of kvm->lock.

Paul.
```
#### [PATCH 00/15] arm64: KVM: add SPE profiling support for guest
##### From: Sudeep Holla <sudeep.holla@arm.com>

```c

Hi,

This series implements support for allowing KVM guests to use the Arm
Statistical Profiling Extension (SPE).

The patches are also available on a branch[1]. The last two extra
patches are for the kvmtool if someone wants to play with it.

Regards,
Sudeep

v1->v2:
	- Rebased on v5.2-rc1
	- Adjusted sysreg_elx_s macros with merged clang build support

[1] git://git.kernel.org/pub/scm/linux/kernel/git/sudeep.holla/linux.git kvm_spe

Sudeep Holla (15):
  KVM: arm64: add {read,write}_sysreg_elx_s versions for new registers
  dt-bindings: ARM SPE: highlight the need for PPI partitions on
    heterogeneous systems
  arm64: KVM: reset E2PB correctly in MDCR_EL2 when exiting the
    guest(VHE)
  arm64: KVM: define SPE data structure for each vcpu
  arm64: KVM: add access handler for SPE system registers
  arm64: KVM/VHE: enable the use PMSCR_EL12 on VHE systems
  arm64: KVM: split debug save restore across vm/traps activation
  arm64: KVM/debug: drop pmscr_el1 and use sys_regs[PMSCR_EL1] in
    kvm_cpu_context
  arm64: KVM: add support to save/restore SPE profiling buffer controls
  arm64: KVM: enable conditional save/restore full SPE profiling buffer
    controls
  arm64: KVM/debug: trap all accesses to SPE controls at EL1
  KVM: arm64: add a new vcpu device control group for SPEv1
  KVM: arm64: enable SPE support
  KVMTOOL: update_headers: Sync kvm UAPI headers with linux v5.2-rc1
  KVMTOOL: kvm: add a vcpu feature for SPEv1 support

 .../devicetree/bindings/arm/spe-pmu.txt       |   5 +-
 Documentation/virtual/kvm/devices/vcpu.txt    |  28 +++
 arch/arm64/boot/dts/arm/rtsm_ve-aemv8a.dts    | 185 +++++++++++-------
 arch/arm64/configs/defconfig                  |   6 +
 arch/arm64/include/asm/kvm_host.h             |  19 +-
 arch/arm64/include/asm/kvm_hyp.h              |  26 ++-
 arch/arm64/include/uapi/asm/kvm.h             |   4 +
 arch/arm64/kvm/Kconfig                        |   7 +
 arch/arm64/kvm/Makefile                       |   1 +
 arch/arm64/kvm/guest.c                        |   9 +
 arch/arm64/kvm/hyp/debug-sr.c                 |  98 +++++++---
 arch/arm64/kvm/hyp/switch.c                   |  18 +-
 arch/arm64/kvm/reset.c                        |   3 +
 arch/arm64/kvm/sys_regs.c                     |  35 ++++
 include/kvm/arm_spe.h                         |  71 +++++++
 include/uapi/linux/kvm.h                      |   1 +
 virt/kvm/arm/arm.c                            |   5 +
 virt/kvm/arm/spe.c                            | 163 +++++++++++++++
 18 files changed, 570 insertions(+), 114 deletions(-)
 create mode 100644 include/kvm/arm_spe.h
 create mode 100644 virt/kvm/arm/spe.c
---
2.17.1
```
#### [PATCH v3 0/3] Retrieving zPCI specific info with VFIO
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

We define a new configuration entry for VFIO/PCI, VFIO_PCI_ZDEV
to configure access to a zPCI region dedicated for retrieving
zPCI features.

When the VFIO_PCI_ZDEV feature is configured we initialize
a new device region, VFIO_REGION_SUBTYPE_ZDEV_CLP, to hold
the information from the ZPCI device the userland needs to
give to a guest driving the zPCI function.


Note that in the current state we do not use the CLP instructions
to access the firmware but get the information directly from
the zdev device.

-This means that the patch 1, "s390: pci: Exporting access to CLP PCI
function and PCI group" is not used and can be let out of this series
without denying the good working of the other patches.
- But we will need this later, eventually in the next iteration
  to retrieve values not being saved inside the zdev structure.
  like maxstbl and the PCI supported version

To share the code with arch/s390/pci/pci_clp.c the original functions
in pci_clp.c to query PCI functions and PCI functions group are
modified so that they can be exported.

A new function clp_query_pci() replaces clp_query_pci_fn() and
the previous calls to clp_query_pci_fn() and clp_query_pci_fngrp()
are replaced with calls to zdev_query_pci_fn() and zdev_query_pci_fngrp()
using a zdev pointer as argument.


Pierre Morel (3):
  s390: pci: Exporting access to CLP PCI function and PCI group
  vfio: zpci: defining the VFIO headers
  vfio: pci: Using a device region to retrieve zPCI information

 arch/s390/include/asm/pci.h         |  3 ++
 arch/s390/pci/pci_clp.c             | 70 ++++++++++++++++---------------
 drivers/vfio/pci/Kconfig            |  7 ++++
 drivers/vfio/pci/Makefile           |  1 +
 drivers/vfio/pci/vfio_pci.c         |  9 ++++
 drivers/vfio/pci/vfio_pci_private.h | 10 +++++
 drivers/vfio/pci/vfio_pci_zdev.c    | 83 +++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |  4 ++
 include/uapi/linux/vfio_zdev.h      | 34 +++++++++++++++
 9 files changed, 187 insertions(+), 34 deletions(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_zdev.c
 create mode 100644 include/uapi/linux/vfio_zdev.h
```
#### [PATCH 0/4] kvm: selftests: aarch64: use struct kvm_vcpu_init
##### From: Andrew Jones <drjones@redhat.com>

```c

aarch64 vcpu setup requires a vcpu init step that takes a kvm_vcpu_init
struct. So far we've just hard coded that to be one that requests no
features and always uses KVM_ARM_TARGET_GENERIC_V8 for the target. We
should have used the preferred target from the beginning, so we do that
now, and we also provide an API to unit tests to select a target of their
choosing and/or cpu features.

Switching to the preferred target fixes running on platforms that don't
like KVM_ARM_TARGET_GENERIC_V8. The new API will be made use of with
some coming unit tests.

Andrew Jones (4):
  kvm: selftests: rename vm_vcpu_add to vm_vcpu_add_memslots
  kvm: selftests: introduce vm_vcpu_add
  kvm: selftests: introduce aarch64_vcpu_setup
  kvm: selftests: introduce aarch64_vcpu_add_default

 .../selftests/kvm/include/aarch64/processor.h |  4 +++
 .../testing/selftests/kvm/include/kvm_util.h  |  5 +--
 .../selftests/kvm/lib/aarch64/processor.c     | 33 +++++++++++++++----
 tools/testing/selftests/kvm/lib/kvm_util.c    | 28 +++++++++++++---
 .../selftests/kvm/lib/x86_64/processor.c      |  2 +-
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  2 +-
 .../kvm/x86_64/kvm_create_max_vcpus.c         |  2 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c |  2 +-
 .../testing/selftests/kvm/x86_64/state_test.c |  2 +-
 9 files changed, 62 insertions(+), 18 deletions(-)
```
#### [PATCH v2 0/8] s390: virtio: support protected virtualization
##### From: Michael Mueller <mimu@linux.ibm.com>

```c

Enhanced virtualization protection technology may require the use of
bounce buffers for I/O. While support for this was built into the virtio
core, virtio-ccw wasn't changed accordingly.

Some background on technology (not part of this series) and the
terminology used.

* Protected Virtualization (PV):

Protected Virtualization guarantees, that non-shared memory of a  guest
that operates in PV mode private to that guest. I.e. any attempts by the
hypervisor or other guests to access it will result in an exception. If
supported by the environment (machine, KVM, guest VM) a guest can decide
to change into PV mode by doing the appropriate ultravisor calls.

* Ultravisor:

A hardware/firmware entity that manages PV guests, and polices access to
their memory. A PV guest prospect needs to interact with the ultravisor,
to enter PV mode, and potentially to share pages (for I/O which should
be encrypted by the guest). A guest interacts with the ultravisor via so
called ultravisor calls. A hypervisor needs to interact with the
ultravisor to facilitate interpretation, emulation and swapping. A
hypervisor  interacts with the ultravisor via ultravisor calls and via
the SIE state description. Generally the ultravisor sanitizes hypervisor
inputs so that the guest can not be corrupted (except for denial of
service.


What needs to be done
=====================

Thus what needs to be done to bring virtio-ccw up to speed with respect
to protected virtualization is:
* use some 'new' common virtio stuff
* make sure that virtio-ccw specific stuff uses shared memory when
  talking to the hypervisor (except control/communication blocks like ORB,
  these are handled by the ultravisor)
* make sure the DMA API does what is necessary to talk through shared
  memory if we are a protected virtualization guest.
* make sure the common IO layer plays along as well (airqs, sense).


Important notes
================

* This patch set is based on Martins features branch
 (git://git.kernel.org/pub/scm/linux/kernel/git/s390/linux.git branch
 'features').

* Documentation is still very sketchy. I'm committed to improving this,
  but I'm currently hampered by some dependencies currently.  

* The existing naming in the common infrastructure (kernel internal
  interfaces) is pretty much based on the AMD SEV terminology. Thus the
  names aren't always perfect. There might be merit to changing these
  names to more abstract ones. I did not put much thought into that at
  the current stage.

* Testing: Please use iommu_platform=on for any virtio devices you are
  going to test this code with (so virtio actually uses the DMA API).

Change log
==========

v1 --> v2:
* patch "virtio/s390: use vring_create_virtqueue" went already upstream
* patch "virtio/s390: DMA support for virtio-ccw" went already upstream
* patch "virtio/s390: enable packed ring" went already upstream
* Made dev.dma_mask point to dev.coherent_dma_mask for css, subchannel
  and ccw devices.
* While rebasing 's390/airq: use DMA memory for adapter interrupts' the
  newly introduced kmem_cache  was replaced with an equivalent dma_pool;
  the kalloc() allocations are now replaced with cio_dma_zalloc()
  allocations to avoid wasting almost a full page.
* Made virtio-ccw use the new AIRQ_IV_CACHELINE flag.
* fixed all remaining checkpatch issues

RFC --> v1:
* Fixed bugs found by Connie (may_reduce and handling reduced,  warning,
  split move -- thanks Connie!).
* Fixed console bug found by Sebastian (thanks Sebastian!).
* Removed the completely useless duplicate of dma-mapping.h spotted by
  Christoph (thanks Christoph!).
* Don't use the global DMA pool for subchannel and ccw device
  owned memory as requested by Sebastian. Consequences:
	* Both subchannel and ccw devices have their dma masks
	now (both specifying 31 bit addressable)
	* We require at least 2 DMA pages per ccw device now, most of
	this memory is wasted though.
	* DMA memory allocated by virtio is also 31 bit addressable now
        as virtio uses the parent (which is the ccw device).
* Enabled packed ring.
* Rebased onto Martins feature branch; using the actual uv (ultravisor)
  interface instead of TODO comments.
* Added some explanations to the cover letter (Connie, David).
* Squashed a couple of patches together and fixed some text stuff. 

Looking forward to your review, or any other type of input.

Halil Pasic (8):
  s390/mm: force swiotlb for protected virtualization
  s390/cio: introduce DMA pools to cio
  s390/cio: add basic protected virtualization support
  s390/airq: use DMA memory for adapter interrupts
  virtio/s390: use cacheline aligned airq bit vectors
  virtio/s390: add indirection to indicators access
  virtio/s390: use DMA memory for ccw I/O and classic notifiers
  virtio/s390: make airq summary indicators DMA

 arch/s390/Kconfig                   |   5 +
 arch/s390/include/asm/airq.h        |   2 +
 arch/s390/include/asm/ccwdev.h      |   4 +
 arch/s390/include/asm/cio.h         |  11 ++
 arch/s390/include/asm/mem_encrypt.h |  18 +++
 arch/s390/mm/init.c                 |  47 +++++++
 drivers/s390/cio/airq.c             |  32 +++--
 drivers/s390/cio/ccwreq.c           |   9 +-
 drivers/s390/cio/cio.h              |   2 +
 drivers/s390/cio/css.c              | 111 ++++++++++++++++
 drivers/s390/cio/device.c           |  64 ++++++++--
 drivers/s390/cio/device_fsm.c       |  53 +++++---
 drivers/s390/cio/device_id.c        |  20 +--
 drivers/s390/cio/device_ops.c       |  21 +++-
 drivers/s390/cio/device_pgid.c      |  22 ++--
 drivers/s390/cio/device_status.c    |  24 ++--
 drivers/s390/cio/io_sch.h           |  20 ++-
 drivers/s390/virtio/virtio_ccw.c    | 244 ++++++++++++++++++++----------------
 18 files changed, 514 insertions(+), 195 deletions(-)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h
```
#### [PATCH v1 0/9] KVM selftests for s390x
##### From: Thomas Huth <thuth@redhat.com>

```c

This patch series enables the KVM selftests for s390x. As a first
test, the sync_regs from x86 has been adapted to s390x, and after
a fix for KVM_CAP_MAX_VCPU_ID on s390x, the kvm_create_max_vcpus
is now enabled here, too.

Please note that the ucall() interface is not used yet - since
s390x neither has PIO nor MMIO, this needs some more work first
before it becomes usable (we likely should use a DIAG hypercall
here, which is what the sync_reg test is currently using, too...
I started working on that topic, but did not finish that work
yet, so I decided to not include it yet).

RFC -> v1:
 - Rebase, needed to add the first patch for vcpu_nested_state_get/set
 - Added patch to introduce VM_MODE_DEFAULT macro
 - Improved/cleaned up the code in processor.c
 - Added patch to fix KVM_CAP_MAX_VCPU_ID on s390x
 - Added patch to enable the kvm_create_max_vcpus on s390x and aarch64

Andrew Jones (1):
  kvm: selftests: aarch64: fix default vm mode

Thomas Huth (8):
  KVM: selftests: Wrap vcpu_nested_state_get/set functions with x86
    guard
  KVM: selftests: Guard struct kvm_vcpu_events with
    __KVM_HAVE_VCPU_EVENTS
  KVM: selftests: Introduce a VM_MODE_DEFAULT macro for the default bits
  KVM: selftests: Align memory region addresses to 1M on s390x
  KVM: selftests: Add processor code for s390x
  KVM: selftests: Add the sync_regs test for s390x
  KVM: s390: Do not report unusabled IDs via KVM_CAP_MAX_VCPU_ID
  KVM: selftests: Move kvm_create_max_vcpus test to generic code

 MAINTAINERS                                   |   2 +
 arch/mips/kvm/mips.c                          |   3 +
 arch/powerpc/kvm/powerpc.c                    |   3 +
 arch/s390/kvm/kvm-s390.c                      |   1 +
 arch/x86/kvm/x86.c                            |   3 +
 tools/testing/selftests/kvm/Makefile          |   7 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  10 +
 .../selftests/kvm/include/s390x/processor.h   |  22 ++
 .../kvm/{x86_64 => }/kvm_create_max_vcpus.c   |   3 +-
 .../selftests/kvm/lib/aarch64/processor.c     |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  25 +-
 .../selftests/kvm/lib/s390x/processor.c       | 286 ++++++++++++++++++
 .../selftests/kvm/lib/x86_64/processor.c      |   2 +-
 .../selftests/kvm/s390x/sync_regs_test.c      | 151 +++++++++
 virt/kvm/arm/arm.c                            |   3 +
 virt/kvm/kvm_main.c                           |   2 -
 16 files changed, 514 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/processor.h
 rename tools/testing/selftests/kvm/{x86_64 => }/kvm_create_max_vcpus.c (93%)
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/processor.c
 create mode 100644 tools/testing/selftests/kvm/s390x/sync_regs_test.c
```
