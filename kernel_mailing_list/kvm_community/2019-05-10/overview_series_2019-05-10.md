#### [GIT PULL] VFIO updates for v5.2-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit 085b7755808aa11f78ab9377257e1dad2e6fa4bb:

  Linux 5.1-rc6 (2019-04-21 10:45:57 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.2-rc1

for you to fetch changes up to 15c80c1659f27364734a3938b04d1c67479aa11c:

  vfio: Add Cornelia Huck as reviewer (2019-05-08 11:41:26 -0600)

----------------------------------------------------------------
VFIO updates for v5.2-rc1

 - Improve dev_printk() usage (Bjorn Helgaas)

 - Fix issue with blocking in !TASK_RUNNING state while waiting for
   userspace to release devices (Farhan Ali)

 - Fix error path cleanup in nvlink setup (Greg Kurz)

 - mdev-core cleanups and fixes in preparation for more use cases
   (Parav Pandit)

 - Cornelia has volunteered as an official vfio reviewer (Cornelia Huck)

----------------------------------------------------------------
Bjorn Helgaas (1):
      vfio: Use dev_printk() when possible

Cornelia Huck (1):
      vfio: Add Cornelia Huck as reviewer

Farhan Ali (1):
      vfio: Fix WARNING "do not call blocking ops when !TASK_RUNNING"

Greg Kurz (1):
      vfio-pci/nvlink2: Fix potential VMA leak

Parav Pandit (7):
      vfio/mdev: Avoid release parent reference during error path
      vfio/mdev: Removed unused kref
      vfio/mdev: Drop redundant extern for exported symbols
      vfio/mdev: Avoid masking error code to EBUSY
      vfio/mdev: Follow correct remove sequence
      vfio/mdev: Fix aborting mdev child device removal if one fails
      vfio/mdev: Avoid inline get and put parent helpers

 MAINTAINERS                                        |  1 +
 drivers/vfio/mdev/mdev_core.c                      | 18 +++----
 drivers/vfio/mdev/mdev_private.h                   |  1 -
 drivers/vfio/mdev/mdev_sysfs.c                     |  2 +-
 drivers/vfio/pci/vfio_pci.c                        | 23 ++++-----
 drivers/vfio/pci/vfio_pci_config.c                 | 29 +++++------
 drivers/vfio/pci/vfio_pci_nvlink2.c                |  2 +
 .../vfio/platform/reset/vfio_platform_amdxgbe.c    |  5 +-
 drivers/vfio/platform/vfio_platform_common.c       | 12 +++--
 drivers/vfio/vfio.c                                | 59 +++++++++-------------
 include/linux/mdev.h                               | 21 ++++----
 include/linux/pci.h                                |  3 ++
 12 files changed, 81 insertions(+), 95 deletions(-)
```
#### [PATCH 1/4] s390: pci: Exporting access to CLP PCI function and PCI group
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
For the generic implementation of VFIO PCI we need to retrieve
the hardware configuration for the PCI functions and the
PCI function groups.

We modify the internal function using CLP Query PCI function and
CLP query PCI function group so that they can be called from
outside the S390 architecture PCI code and prefix the two
functions with "zdev" to make clear that they can be called
knowing only the associated zdevice.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Sebastian Ott <sebott@linux.ibm.com>
---
 arch/s390/include/asm/pci.h |  3 ++
 arch/s390/pci/pci_clp.c     | 72 ++++++++++++++++++++++++---------------------
 2 files changed, 41 insertions(+), 34 deletions(-)

```
#### [PATCH v8 1/6] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  8 +++++++-
 6 files changed, 46 insertions(+), 12 deletions(-)

```
#### [PATCH v2 1/8] vsock/virtio: limit the memory used per-socket
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Since virtio-vsock was introduced, the buffers filled by the host
and pushed to the guest using the vring, are directly queued in
a per-socket list avoiding to copy it.
These buffers are preallocated by the guest with a fixed
size (4 KB).

The maximum amount of memory used by each socket should be
controlled by the credit mechanism.
The default credit available per-socket is 256 KB, but if we use
only 1 byte per packet, the guest can queue up to 262144 of 4 KB
buffers, using up to 1 GB of memory per-socket. In addition, the
guest will continue to fill the vring with new 4 KB free buffers
to avoid starvation of other sockets.

This patch solves this issue copying the payload in a new buffer.
Then it is queued in the per-socket list, and the 4KB buffer used
by the host is freed.

In this way, the memory used by each socket respects the credit
available, and we still avoid starvation, paying the cost of an
extra memory copy. When the buffer is completely full we do a
"zero-copy", moving the buffer directly in the per-socket list.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vsock.c                   |  2 +
 include/linux/virtio_vsock.h            |  8 +++
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 95 ++++++++++++++++++-------
 4 files changed, 81 insertions(+), 25 deletions(-)

```
