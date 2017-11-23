#### [RFC PATCH 01/10] iommu/vt-d: Get iommu device for a mediated device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
This patch adds the support to get the iommu device for a mediated
device. The assumption is that each mediated device is a minimal
assignable set of a physical PCI device. Hence, we should use the
iommu device of the parent PCI device to manage the translation.

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Signed-off-by: Sanjay Kumar <sanjay.k.kumar@intel.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel-iommu.c |  6 ++++++
 drivers/iommu/intel-pasid.h | 16 ++++++++++++++++
 2 files changed, 22 insertions(+)

```
