

#### [PATCH v4 0/3] virtio-balloon: tweak config_changed
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Since virtio-ccw doesn't work with accessing to the config space
inside an interrupt context, this patch series avoids that issue by
moving the config register accesses to the related workqueue contexts.

v3->v4 ChangeLog:
    - change virtio32_to_cpu to cpu_to_virtio_32 in send_cmd_id_start;
v2->v3 ChangeLog:
    - rename cmd_id_received to cmd_id_received_cache, and have call sites
      read the latest value via virtio_balloon_cmd_id_received. (Still
      kept Cornelia and Halil's reviewed-by as it's a minor change)
    - remove zeroing vb->num_free_page_blocks in probe since vb is
      allocated via kzalloc.
v1->v2 ChangeLog:
    - add config_read_bitmap to indicate to the workqueue callbacks about
      the necessity of reading the related config fields.

Wei Wang (3):
  virtio-balloon: tweak config_changed implementation
  virtio-balloon: improve update_balloon_size_func
  virtio_balloon: remove the unnecessary 0-initialization

 drivers/virtio/virtio_balloon.c | 104 ++++++++++++++++++++++++++--------------
 1 file changed, 69 insertions(+), 35 deletions(-)
```
#### [RFC v3 00/21] SMMUv3 Nested Stage Setup
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
https://github.com/eauger/linux/tree/v5.0-rc1-2stage-rfc-v3

This was tested on Qualcomm HW featuring SMMUv3 and with adapted QEMU
vSMMUv3.

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

Eric Auger (12):
  iommu: Introduce bind_guest_msi
  vfio: VFIO_IOMMU_BIND_MSI
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement set_pasid_table
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Implement bind_guest_msi
  iommu/smmuv3: Report non recoverable faults
  vfio-pci: Add a new VFIO_REGION_TYPE_NESTED region type
  vfio-pci: Register an iommu fault handler
  vfio-pci: Add VFIO_PCI_DMA_FAULT_IRQ_INDEX
  vfio: Document nested stage control

Jacob Pan (4):
  iommu: Introduce set_pasid_table API
  iommu: introduce device fault data
  driver core: add per device iommu param
  iommu: introduce device fault report API

Jean-Philippe Brucker (2):
  iommu/arm-smmu-v3: Link domains and devices
  iommu/arm-smmu-v3: Maintain a SID->device structure

Liu, Yi L (3):
  iommu: Introduce cache_invalidate API
  vfio: VFIO_IOMMU_SET_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

 Documentation/vfio.txt              |  62 ++++
 drivers/iommu/arm-smmu-v3.c         | 460 ++++++++++++++++++++++++++--
 drivers/iommu/dma-iommu.c           | 112 ++++++-
 drivers/iommu/iommu.c               | 187 ++++++++++-
 drivers/vfio/pci/vfio_pci.c         | 147 ++++++++-
 drivers/vfio/pci/vfio_pci_intrs.c   |  19 ++
 drivers/vfio/pci/vfio_pci_private.h |   3 +
 drivers/vfio/vfio_iommu_type1.c     | 105 +++++++
 include/linux/device.h              |   3 +
 include/linux/dma-iommu.h           |  11 +
 include/linux/iommu.h               | 127 +++++++-
 include/uapi/linux/iommu.h          | 234 ++++++++++++++
 include/uapi/linux/vfio.h           |  38 +++
 13 files changed, 1476 insertions(+), 32 deletions(-)
 create mode 100644 include/uapi/linux/iommu.h
```
