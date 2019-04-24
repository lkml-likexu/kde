#### [RFC 1/7] iommu/vt-d: Set the dma_ops per device so we can remove the iommu_no_mapping code
##### From: Tom Murphy <tmurphy@arista.com>

```c
Set the dma_ops per device so we can remove the iommu_no_mapping code.

Signed-off-by: Tom Murphy <tmurphy@arista.com>
---
 drivers/iommu/intel-iommu.c | 85 +++----------------------------------
 1 file changed, 6 insertions(+), 79 deletions(-)

```
