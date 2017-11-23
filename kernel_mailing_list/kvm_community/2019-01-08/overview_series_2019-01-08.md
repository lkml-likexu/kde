#### [RFC v3 01/21] iommu: Introduce set_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on a guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/VTD terminology) while to host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API. We foresee at least two specializations of this struct,
for PASID table passing and ARM SMMUv3.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

This patch generalizes the API introduced by Jacob & co-authors in
https://lwn.net/Articles/754331/

v2 -> v3:
- replace unbind/bind by set_pasid_table
- move table pointer and pasid bits in the generic part of the struct

v1 -> v2:
- restore the original pasid table name
- remove the struct device * parameter in the API
- reworked iommu_pasid_smmuv3
---
 drivers/iommu/iommu.c      | 10 ++++++++
 include/linux/iommu.h      | 14 +++++++++++
 include/uapi/linux/iommu.h | 50 ++++++++++++++++++++++++++++++++++++++
 3 files changed, 74 insertions(+)
 create mode 100644 include/uapi/linux/iommu.h

```
#### [PATCH] vfio_pci: set TRACE_INCLUDE_PATH to fix the build error
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
drivers/vfio/pci/vfio_pci_nvlink2.c cannot be compiled for in-tree
building.

    CC      drivers/vfio/pci/vfio_pci_nvlink2.o
  In file included from drivers/vfio/pci/trace.h:102,
                   from drivers/vfio/pci/vfio_pci_nvlink2.c:29:
  ./include/trace/define_trace.h:89:42: fatal error: ./trace.h: No such file or directory
   #include TRACE_INCLUDE(TRACE_INCLUDE_FILE)
                                          ^
  compilation terminated.
  make[1]: *** [scripts/Makefile.build;277: drivers/vfio/pci/vfio_pci_nvlink2.o] Error 1

To fix the build error, let's tell include/trace/define_trace.h the
location of drivers/vfio/pci/trace.h

Fixes: 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver")
Reported-by: Laura Abbott <labbott@redhat.com>
Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

 drivers/vfio/pci/trace.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio/type1: Fix unmap overflow off-by-oneFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
The below referenced commit adds a test for integer overflow, but in
doing so prevents the unmap ioctl from ever including the last page of
the address space.  Subtract one to compare to the last address of the
unmap to avoid the overflow and wrap-around.

Fixes: 71a7d3d78e3c ("vfio/type1: silence integer overflow warning")
Link: https://bugzilla.redhat.com/show_bug.cgi?id=1662291
Cc: Dan Carpenter <dan.carpenter@oracle.com>
Reported-by: Pei Zhang <pezhang@redhat.com>
Debugged-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Tested-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vhost/vsock: fix vhost vsock cid hashing inconsistent
##### From: Zha Bin <zhabin@linux.alibaba.com>

```c
The vsock core only supports 32bit CID, but the Virtio-vsock spec define
CID (dst_cid and src_cid) as u64 and the upper 32bits is reserved as
zero. This inconsistency causes one bug in vhost vsock driver. The
scenarios is:

  0. A hash table (vhost_vsock_hash) is used to map an CID to a vsock
  object. And hash_min() is used to compute the hash key. hash_min() is
  defined as:
  (sizeof(val) <= 4 ? hash_32(val, bits) : hash_long(val, bits)).
  That means the hash algorithm has dependency on the size of macro
  argument 'val'.
  0. In function vhost_vsock_set_cid(), a 64bit CID is passed to
  hash_min() to compute the hash key when inserting a vsock object into
  the hash table.
  0. In function vhost_vsock_get(), a 32bit CID is passed to hash_min()
  to compute the hash key when looking up a vsock for an CID.

Because the different size of the CID, hash_min() returns different hash
key, thus fails to look up the vsock object for an CID.

To fix this bug, we keep CID as u64 in the IOCTLs and virtio message
headers, but explicitly convert u64 to u32 when deal with the hash table
and vsock core.

Fixes: 834e772c8db0 ("vhost/vsock: fix use-after-free in network stack callers")
Link: https://github.com/stefanha/virtio/blob/vsock/trunk/content.tex
Signed-off-by: Zha Bin <zhabin@linux.alibaba.com>
Reviewed-by: Liu Jiang <gerry@linux.alibaba.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vsock.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/3] virtio-balloon: tweak config_changed implementation
##### From: Wei Wang <wei.w.wang@intel.com>

```c
virtio-ccw has deadlock issues with reading the config space inside the
interrupt context, so we tweak the virtballoon_changed implementation
by moving the config read operations into the related workqueue contexts.
The config_read_bitmap is used as a flag to the workqueue callbacks
about the related config fields that need to be read.

The cmd_id_received is also renamed to cmd_id_received_cache, and
the value should be obtained via virtio_balloon_cmd_id_received.

Fixes: 86a559787e6f ("virtio-balloon: VIRTIO_BALLOON_F_FREE_PAGE_HINT")
Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Tested-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/virtio/virtio_balloon.c | 98 +++++++++++++++++++++++++++--------------
 1 file changed, 65 insertions(+), 33 deletions(-)

```
