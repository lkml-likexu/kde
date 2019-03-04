

#### [PATCH v3 00/17] KVM: PPC: Book3S HV: add XIVE native exploitation
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIOs to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter sub-engine.

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
device should be created at run-time, after the machine has started.
This requires extra support from KVM to destroy KVM devices. It is
introduced at the end of the patchset as it still requires some
attention and a XIVE-only VM would not need.

This is 5.2 material hopefully. The OPAL patches have not yet been
merged.


GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.0

OPAL:

  https://github.com/legoater/skiboot/commits/xive

Thanks,

C.

Caveats :

 - We should introduce a set of definitions common to XIVE and XICS
 - The XICS-over-XIVE device file book3s_xive.c could be renamed to
   book3s_xics_on_xive.c or book3s_xics_p9.c
 - The XICS-over-XIVE device has locking issues in the setup. 

Changes since v2:

 - removed extra OPAL call definitions
 - removed ->q_order setting. Only useful in the XICS-on-XIVE KVM
   device which allocates the EQs on behalf of the guest.
 - returned -ENXIO when VP base is invalid
 - made use of the xive_vp() macro to compute VP identifiers
 - reworked locking in kvmppc_xive_native_connect_vcpu() to fix races 
 - stop advertising KVM_CAP_PPC_IRQ_XIVE as support is not fully
   available yet
 - fixed comment on XIVE IRQ number space
 - removed usage of the __x_* macros
 - fixed locking on source block
 - fixed comments on the KVM device attribute definitions
 - handled MASKED EAS configuration
 - fixed check on supported EQ size to restrict to 64K pages
 - checked kvm_eq.flags that need to be zero
 - removed the OPAL call when EQ qtoggle bit and index are zero. 
 - reduced the size of kvmppc_one_reg timaval attribute to two u64s
 - stopped returning of the OS CAM line value
 
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

Cédric Le Goater (17):
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
  KVM: PPC: Book3S HV: XIVE: activate XIVE exploitation mode
  KVM: introduce a KVM_DESTROY_DEVICE ioctl
  KVM: PPC: Book3S HV: XIVE: clear the vCPU interrupt presenters

 arch/powerpc/include/asm/kvm_host.h           |    2 +
 arch/powerpc/include/asm/kvm_ppc.h            |   32 +
 arch/powerpc/include/asm/opal-api.h           |    7 +-
 arch/powerpc/include/asm/opal.h               |    7 +
 arch/powerpc/include/asm/xive.h               |   17 +
 arch/powerpc/include/uapi/asm/kvm.h           |   48 +
 arch/powerpc/kvm/book3s_xive.h                |   36 +
 include/linux/kvm_host.h                      |    1 +
 include/uapi/linux/kvm.h                      |   10 +
 arch/powerpc/kvm/book3s.c                     |   31 +-
 arch/powerpc/kvm/book3s_xics.c                |   19 +
 arch/powerpc/kvm/book3s_xive.c                |  170 ++-
 arch/powerpc/kvm/book3s_xive_native.c         | 1200 +++++++++++++++++
 arch/powerpc/kvm/powerpc.c                    |   37 +
 arch/powerpc/sysdev/xive/native.c             |  110 ++
 virt/kvm/kvm_main.c                           |   53 +
 Documentation/virtual/kvm/api.txt             |   29 +
 Documentation/virtual/kvm/devices/xive.txt    |  196 +++
 arch/powerpc/kvm/Makefile                     |    2 +-
 .../powerpc/platforms/powernv/opal-wrappers.S |    3 +
 20 files changed, 1950 insertions(+), 60 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
```
#### [PATCH v5 00/22] SMMUv3 Nested Stage Setup
##### From: Eric Auger <eric.auger@redhat.com>

```c

This series allows a virtualizer to program the nested stage mode.
This is useful when both the host and the guest are exposed with
an SMMUv3 and a PCI device is assigned to the guest using VFIO.

In this mode, the physical IOMMU must be programmed to translate
the two stages: the one set up by the guest (IOVA -> GPA) and the
one set up by the host VFIO driver as part of the assignment process
(GPA -> HPA).

On Intel, this is traditionnaly achieved by combining the 2 stages
into a single physical stage. However this relies on the capability
to trap on each guest translation structure update. This is possible
by using the VTD Caching Mode. Unfortunately the ARM SMMUv3 does
not offer a similar mechanism.

However, the ARM SMMUv3 architecture supports 2 physical stages! Those
were devised exactly with that use case in mind. Assuming the HW
implements both stages (optional), the guest now can use stage 1
while the host uses stage 2.

This assumes the virtualizer has means to propagate guest settings
to the host SMMUv3 driver. This series brings this VFIO/IOMMU
infrastructure.  Those services are:
- bind the guest stage 1 configuration to the stream table entry
- propagate guest TLB invalidations
- bind MSI IOVAs
- propagate faults collected at physical level up to the virtualizer

This series largely reuses the user API and infrastructure originally
devised for SVA/SVM and patches submitted by Jacob, Yi Liu, Tianyu in
[1-2] and Jean-Philippe [3-4].

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.0-2stage-v5

References:
[1] [PATCH v5 00/23] IOMMU and VT-d driver support for Shared Virtual
    Address (SVA)
    https://lwn.net/Articles/754331/
[2] [RFC PATCH 0/8] Shared Virtual Memory virtualization for VT-d
    (VFIO part)
    https://lists.linuxfoundation.org/pipermail/iommu/2017-April/021475.html
[3] [v2,00/40] Shared Virtual Addressing for the IOMMU
    https://patchwork.ozlabs.org/cover/912129/
[4] [PATCH v3 00/10] Shared Virtual Addressing for the IOMMU
    https://patchwork.kernel.org/cover/10608299/

History:
v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (13):
  iommu: Introduce bind/unbind_guest_msi
  vfio: VFIO_IOMMU_BIND/UNBIND_MSI
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults
  vfio-pci: Add a new VFIO_REGION_TYPE_NESTED region type
  vfio-pci: Register an iommu fault handler
  vfio_pci: Allow to mmap the fault queue
  vfio-pci: Add VFIO_PCI_DMA_FAULT_IRQ_INDEX
  vfio: Document nested stage control

Jacob Pan (4):
  driver core: add per device iommu param
  iommu: introduce device fault data
  iommu: introduce device fault report API
  iommu: Introduce attach/detach_pasid_table API

Jean-Philippe Brucker (2):
  iommu/arm-smmu-v3: Link domains and devices
  iommu/arm-smmu-v3: Maintain a SID->device structure

Liu, Yi L (3):
  iommu: Introduce cache_invalidate API
  vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

 Documentation/vfio.txt              |  83 ++++
 drivers/iommu/arm-smmu-v3.c         | 581 ++++++++++++++++++++++++++--
 drivers/iommu/dma-iommu.c           | 145 ++++++-
 drivers/iommu/iommu.c               | 201 +++++++++-
 drivers/vfio/pci/vfio_pci.c         | 214 ++++++++++
 drivers/vfio/pci/vfio_pci_intrs.c   |  19 +
 drivers/vfio/pci/vfio_pci_private.h |  18 +
 drivers/vfio/pci/vfio_pci_rdwr.c    |  73 ++++
 drivers/vfio/vfio_iommu_type1.c     | 158 ++++++++
 include/linux/device.h              |   3 +
 include/linux/dma-iommu.h           |  18 +
 include/linux/iommu.h               | 143 +++++++
 include/uapi/linux/iommu.h          | 233 +++++++++++
 include/uapi/linux/vfio.h           | 102 +++++
 14 files changed, 1957 insertions(+), 34 deletions(-)
 create mode 100644 include/uapi/linux/iommu.h
```
