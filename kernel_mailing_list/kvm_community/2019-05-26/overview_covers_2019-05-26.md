

#### [PATCH v8 00/29] SMMUv3 Nested Stage Setup
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

This series depends on the shared SVA user api originally contributed
by Jacob, Yi Liu, Tianyu in [1-2] and Jean-Philippe [3-4] and
progressively matured up to the state found in Jean-Philippe's
sva/api branch (git://linux-arm.org/linux-jpb.git). I guess we will
try to get this upstreamed first in separate series so please
consider this actual series starts at:
"iommu: Introduce bind/unbind_guest_msi".

Also I reordered the patches to split the series into an iommu/smmuv3
part and a VFIO part. Those two parts may be considered to be upstreamed
separately.

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.2-rc1-2stage-v8

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

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

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


Eric Auger (17):
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Dynamically allocate s1_cfg and s2_cfg
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Introduce __arm_smmu_tlb_inv_asid/s1_range_nosync
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults
  vfio: VFIO_IOMMU_BIND/UNBIND_MSI
  vfio-pci: Add a new VFIO_REGION_TYPE_NESTED region type
  vfio-pci: Register an iommu fault handler
  vfio_pci: Allow to mmap the fault queue
  vfio-pci: Add VFIO_PCI_DMA_FAULT_IRQ_INDEX
  vfio: Document nested stage control

Jacob Pan (6):
  driver core: Add per device iommu param
  iommu: Introduce device fault data
  iommu: Introduce device fault report API
  iommu: Add a timeout parameter for PRQ response
  iommu: Use device fault trace event
  iommu: Introduce attach/detach_pasid_table API

Jean-Philippe Brucker (3):
  iommu: Add recoverable fault reporting
  trace/iommu: Add sva trace events
  iommu/arm-smmu-v3: Maintain a SID->device structure

Liu, Yi L (2):
  vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

Yi L Liu (1):
  iommu: Introduce cache_invalidate API

 .../admin-guide/kernel-parameters.txt         |   8 +
 Documentation/vfio.txt                        |  83 ++
 drivers/iommu/arm-smmu-v3.c                   | 817 ++++++++++++++++--
 drivers/iommu/dma-iommu.c                     | 139 ++-
 drivers/iommu/iommu.c                         | 299 ++++++-
 drivers/vfio/pci/vfio_pci.c                   | 214 +++++
 drivers/vfio/pci/vfio_pci_intrs.c             |  19 +
 drivers/vfio/pci/vfio_pci_private.h           |  18 +
 drivers/vfio/pci/vfio_pci_rdwr.c              |  73 ++
 drivers/vfio/vfio_iommu_type1.c               | 172 ++++
 include/linux/device.h                        |   3 +
 include/linux/dma-iommu.h                     |  16 +
 include/linux/iommu.h                         | 176 ++++
 include/trace/events/iommu.h                  |  87 ++
 include/uapi/linux/iommu.h                    | 280 ++++++
 include/uapi/linux/vfio.h                     | 107 +++
 16 files changed, 2421 insertions(+), 90 deletions(-)
 create mode 100644 include/uapi/linux/iommu.h
```
