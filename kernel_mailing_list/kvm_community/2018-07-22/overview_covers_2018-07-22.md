

#### [RFC PATCH 00/10] vfio/mdev: IOMMU aware mediated device
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
which still need to rely on parent devices, this patch set adds a
domain type attribute to each mdev.

enum mdev_domain_type {
       DOMAIN_TYPE_EXTERNAL,   /* Use the external domain and all
                                * IOMMU staff controlled by the
                                * parent device driver.
                                */
       DOMAIN_TYPE_INHERITANCE,/* Use the same domain as the parent device. */
       DOMAIN_TYPE_PRIVATE,    /* Capable of having a private domain. For an
                                * example, the parent device is able to bind
                                * a specific PASID for a mediated device and
                                * transfering data with the asigned PASID.
                                */
};

The mdev parent device driver could opt-in whether an mdev is IOMMU
capable when the device is created by invoking below interface within
its @create callback:

int mdev_set_domain_type(struct device *dev,
                         enum mdev_domain_type type);

In vfio_iommu_type1_attach_group(), a domain will be found and assigned
to the group according to the domain type attributes of mdev devices in
the group.

Besides above, we still need below changes to sport IOMMU-capable mdev
device:
a) The platform specific iommu ops should be set to mdev bus. So that,
   the vfio/mdev framework could call iommu APIs.
b) The iommu driver should be changed to support setting up the translation
   structures for a mediated device.

This patch series extends both IOMMU and vfio components to support
mdev device passing through when it could be isolated and protected
by the IOMMU units. The first part of this series (PATCH 1/10 ~ 5/10)
makes the Intel IOMMU driver to be aware of a mediated device. The
second part (PATCH 6/10 ~ 8/10) sets the iommu ops for the mdev bus.
The last part (PATCH 9/10 ~ 10/10) adds the domain type attribute to
a mdev device and allocates an iommu domain if it is IOMMU-capable.

This patch series depends on a patch set posted here [4] for discussion
which added the support for scalable mode in Intel IOMMU driver.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[4] https://lkml.org/lkml/2018/7/16/62

Best regards,
Lu Baolu

Lu Baolu (10):
  iommu/vt-d: Get iommu device for a mediated device
  iommu/vt-d: Alloc domain for a mediated device
  iommu/vt-d: Allocate groups for mediated devices
  iommu/vt-d: Get pasid table for a mediated device
  iommu/vt-d: Setup DMA remapping for mediated devices
  iommu: Add iommu_set_bus API interface
  iommu/vt-d: Add set_bus iommu ops
  vfio/mdev: Set iommu ops for mdev bus
  vfio/mdev: Add mediated device domain type
  vfio/type1: Allocate domain for mediated device

 drivers/iommu/intel-iommu.c      | 127 ++++++++++++++++++++++++++++++++++++---
 drivers/iommu/intel-pasid.c      |  16 ++++-
 drivers/iommu/intel-pasid.h      |  16 +++++
 drivers/iommu/iommu.c            |  23 +++++++
 drivers/vfio/mdev/mdev_core.c    |  30 ++++++++-
 drivers/vfio/mdev/mdev_driver.c  |  10 +++
 drivers/vfio/mdev/mdev_private.h |   1 +
 drivers/vfio/vfio_iommu_type1.c  |  43 +++++++++----
 include/linux/intel-iommu.h      |   5 ++
 include/linux/iommu.h            |  12 ++++
 include/linux/mdev.h             |  22 +++++++
 11 files changed, 282 insertions(+), 23 deletions(-)
```
