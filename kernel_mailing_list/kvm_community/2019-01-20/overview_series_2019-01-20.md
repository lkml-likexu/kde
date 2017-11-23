#### [PULL] virtio, vhost: fixes and cleanups
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
This mostly fixes the fallout from the balloon changes.

The following changes since commit 1c7fc5cbc33980acd13d668f1c8f0313d6ae9fd8:

  Linux 5.0-rc2 (2019-01-14 10:41:12 +1200)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 8e5dadfe76cf2862ebf3e4f22adef29982df7766:

  vhost/scsi: Use copy_to_iter() to send control queue response (2019-01-14 20:28:08 -0500)

----------------------------------------------------------------
virtio, vhost: fixes, cleanups

fixes and cleanups all over the place

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Bijan Mottahedeh (1):
      vhost/scsi: Use copy_to_iter() to send control queue response

Cornelia Huck (2):
      virtio: fix virtio_config_ops description
      virtio: document virtio_config_ops restrictions

Pavel Tikhomirov (1):
      vhost: return EINVAL if iovecs size does not match the message size

Wei Wang (3):
      virtio_pci: use queue idx instead of array idx to set up the vq
      virtio: don't allocate vqs when names[i] = NULL
      virtio-balloon: tweak config_changed implementation

 drivers/misc/mic/vop/vop_main.c        |  9 +++-
 drivers/remoteproc/remoteproc_virtio.c |  9 +++-
 drivers/s390/virtio/virtio_ccw.c       | 12 +++--
 drivers/vhost/scsi.c                   | 20 ++++---
 drivers/vhost/vhost.c                  |  8 ++-
 drivers/virtio/virtio_balloon.c        | 98 ++++++++++++++++++++++------------
 drivers/virtio/virtio_mmio.c           |  9 +++-
 drivers/virtio/virtio_pci_common.c     |  8 +--
 include/linux/virtio_config.h          | 13 +++--
 9 files changed, 126 insertions(+), 60 deletions(-)
```
