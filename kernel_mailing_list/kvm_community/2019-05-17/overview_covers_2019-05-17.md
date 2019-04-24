

#### [PATCH V2 0/4] Prevent vhost kthread from hogging CPU
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series try to prevent a guest triggerable CPU hogging through
vhost kthread. This is done by introducing and checking the weight
after each requrest. The patch has been tested with reproducer of
vsock and virtio-net. Only compile test is done for vhost-scsi.

Please review.

This addresses CVE-2019-3900.

Changs from V1:
- fix user-ater-free in vosck patch

Jason Wang (4):
  vhost: introduce vhost_exceeds_weight()
  vhost_net: fix possible infinite loop
  vhost: vsock: add weight support
  vhost: scsi: add weight support

 drivers/vhost/net.c   | 41 ++++++++++++++---------------------------
 drivers/vhost/scsi.c  | 21 ++++++++++++++-------
 drivers/vhost/vhost.c | 20 +++++++++++++++++++-
 drivers/vhost/vhost.h |  5 ++++-
 drivers/vhost/vsock.c | 28 +++++++++++++++++++++-------
 5 files changed, 72 insertions(+), 43 deletions(-)
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
```
#### [PATCH v2 0/4] Retrieving zPCI specific info with VFIO
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

Using the PCI VFIO interface allows userland, a.k.a. QEMU, to retrieve
ZPCI specific information without knowing Z specific identifiers
like the function ID or the function handle of the zPCI function
hidden behind the PCI interface.

By using the VFIO_IOMMU_GET_INFO ioctl we enter the vfio_iommu_type1
ioctl callback and can insert there the treatment for a new Z specific
capability.

Once in vfio_iommu_type1 we can retrieve the real iommu device,
s390_iommu and call the get_attr iommu operation's callback
in which we can retrieve the zdev device and start clp operations
to retrieve Z specific values the guest driver is concerned with.

To share the code with arch/s390/pci/pci_clp.c the original functions
in pci_clp.c to query PCI functions and PCI functions group are
modified so that they can be exported.

A new function clp_query_pci() replaces clp_query_pci_fn() and
the previous calls to clp_query_pci_fn() and clp_query_pci_fngrp()
are replaced with calls to zdev_query_pci_fn() and zdev_query_pci_fngrp()
using a zdev pointer as argument.


Pierre Morel (4):
  s390: pci: Exporting access to CLP PCI function and PCI group
  vfio: vfio_iommu_type1: Define VFIO_IOMMU_INFO_CAPABILITIES
  s390: iommu: Adding get attributes for s390_iommu
  vfio: vfio_iommu_type1: implement VFIO_IOMMU_INFO_CAPABILITIES

 arch/s390/include/asm/pci.h     |   3 +
 arch/s390/pci/pci_clp.c         |  70 ++++++++++++-----------
 drivers/iommu/s390-iommu.c      |  77 +++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 122 +++++++++++++++++++++++++++++++++++++++-
 include/linux/iommu.h           |   4 ++
 include/uapi/linux/vfio.h       |  67 ++++++++++++++++++++++
 6 files changed, 308 insertions(+), 35 deletions(-)
```
