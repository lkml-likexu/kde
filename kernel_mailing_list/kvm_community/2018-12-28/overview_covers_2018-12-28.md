

#### [PATCH v1 0/2] Virtio: fix some vq allocation issues
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Some vqs don't need to be allocated when the related feature bits are
disabled. Callers notice the vq allocation layer by setting the related
names[i] to be NULL.

This patch series fixes the find_vqs implementations to handle this case.

Wei Wang (2):
  virtio_pci: use queue idx instead of array idx to set up the vq
  virtio: don't allocate vqs when names[i] = NULL

 drivers/misc/mic/vop/vop_main.c        |  9 +++++++--
 drivers/remoteproc/remoteproc_virtio.c |  9 +++++++--
 drivers/s390/virtio/virtio_ccw.c       | 12 +++++++++---
 drivers/virtio/virtio_mmio.c           |  9 +++++++--
 drivers/virtio/virtio_pci_common.c     |  8 ++++----
 5 files changed, 34 insertions(+), 13 deletions(-)
```
#### [RFC PATCH V2 0/3] vhost: accelerate metadata access through vmap()
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to access virtqueue metadata through kernel virtual
address instead of copy_user() friends since they had too much
overheads like checks, spec barriers or even hardware feature
toggling.

Test shows about 24% improvement on TX PPS. It should benefit other
cases as well.

Changes from V1:
- instead of pinning pages, use MMU notifier to invalidate vmaps and
  remap duing metadata prefetch
- fix build warning on MIPS

Please review

Jason Wang (3):
  vhost: generalize adding used elem
  vhost: fine grain userspace memory accessors
  vhost: access vq metadata through kernel virtual address

 drivers/vhost/net.c   |   4 +-
 drivers/vhost/vhost.c | 362 ++++++++++++++++++++++++++++++++++++++----
 drivers/vhost/vhost.h |  15 +-
 3 files changed, 348 insertions(+), 33 deletions(-)
```
