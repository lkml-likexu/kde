

#### [PATCH v7 0/6] vfio/type1: Add support for valid iova list management
##### From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>

```c

This is to revive this series which almost made to 4.18 but got dropped
as Alex found an issue[1] with IGD and USB devices RMRR region being
reported as reserved regions.

Thanks to Eric for his work here[2]. It provides a way to exclude
these regions while reporting the valid iova regions and this respin
make use of that.

Please note that I don't have a platform to verify the reported RMRR
issue and appreciate testing on those platforms.

Thanks,
Shameer

[1] https://lkml.org/lkml/2018/6/5/760
[2] https://lore.kernel.org/patchwork/cover/1083072/

v6-->v7
 -Rebased to 5.2-rc6 + Eric's patches
 -Added logic to exclude IOMMU_RESV_DIRECT_RELAXABLE reserved memory
  region type(patch #2).
 -Dropped patch #4 of v6 as it is already part of mainline.
 -Addressed "container with only an mdev device will have an empty list"
  case(patches 4/6 & 5/6 - Suggested by Alex)

Old
----
This series introduces an iova list associated with a vfio 
iommu. The list is kept updated taking care of iommu apertures,
and reserved regions. Also this series adds checks for any conflict
with existing dma mappings whenever a new device group is attached to
the domain.

User-space can retrieve valid iova ranges using VFIO_IOMMU_GET_INFO
ioctl capability chains. Any dma map request outside the valid iova
range will be rejected.

v5 --> v6

 -Rebased to 4.17-rc1
 -Changed the ordering such that previous patch#7 "iommu/dma: Move
  PCI window region reservation back...")  is now patch #4. This
  will avoid any bisection issues pointed out by Alex.
 -Added Robins's Reviewed-by tag for patch#4

v4 --> v5
Rebased to next-20180315.
 
 -Incorporated the corner case bug fix suggested by Alex to patch #5.
 -Based on suggestions by Alex and Robin, added patch#7. This
  moves the PCI window  reservation back in to DMA specific path.
  This is to fix the issue reported by Eric[1].

v3 --> v4
 Addressed comments received for v3.
 -dma_addr_t instead of phys_addr_t
 -LIST_HEAD() usage.
 -Free up iova_copy list in case of error.
 -updated logic in filling the iova caps info(patch #5)

RFCv2 --> v3
 Removed RFC tag.
 Addressed comments from Alex and Eric:
 - Added comments to make iova list management logic more clear.
 - Use of iova list copy so that original is not altered in
   case of failure.

RFCv1 --> RFCv2
 Addressed comments from Alex:
-Introduced IOVA list management and added checks for conflicts with 
 existing dma map entries during attach/detach.

Shameer Kolothum (6):
  vfio/type1: Introduce iova list and add iommu aperture validity check
  vfio/type1: Check reserve region conflict and update iova list
  vfio/type1: Update iova list on detach
  vfio/type1: check dma map request is within a valid iova range
  vfio/type1: Add IOVA range capability support
  vfio/type1: remove duplicate retrieval of reserved regions

 drivers/vfio/vfio_iommu_type1.c | 510 +++++++++++++++++++++++++++++++-
 include/uapi/linux/vfio.h       |  23 ++
 2 files changed, 520 insertions(+), 13 deletions(-)
```
