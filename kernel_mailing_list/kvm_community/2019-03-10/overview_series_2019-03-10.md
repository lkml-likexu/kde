#### [PULL] virtio,vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit 1c163f4c7b3f621efff9b28a47abb36f7378d783:

  Linux 5.0 (2019-03-03 15:21:29 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to cfdbb4ed31aa777d59b288810f66eb06249ee5b7:

  vhost: silence an unused-variable warning (2019-03-06 11:32:37 -0500)

----------------------------------------------------------------
virtio: fixes, cleanups

Several fixes, most notably fix for virtio on swiotlb systems.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Arnd Bergmann (1):
      vhost: silence an unused-variable warning

Cornelia Huck (3):
      virtio-ccw: diag 500 may return a negative cookie
      virtio-ccw: wire up ->bus_name callback
      virtio: hint if callbacks surprisingly might sleep

Halil Pasic (1):
      s390/virtio: handle find on invalid queue gracefully

Joerg Roedel (5):
      swiotlb: Introduce swiotlb_max_mapping_size()
      swiotlb: Add is_swiotlb_active() function
      dma: Introduce dma_max_mapping_size()
      virtio: Introduce virtio_max_dma_size()
      virtio-blk: Consider virtio_max_dma_size() for maximum segment size

Wei Wang (2):
      virtio-balloon: improve update_balloon_size_func
      virtio_balloon: remove the unnecessary 0-initialization

 Documentation/DMA-API.txt               |  8 ++++++++
 Documentation/virtual/kvm/s390-diag.txt |  3 ++-
 drivers/block/virtio_blk.c              | 10 ++++++----
 drivers/s390/virtio/virtio_ccw.c        | 12 +++++++++++-
 drivers/vhost/vhost.c                   |  2 +-
 drivers/virtio/virtio.c                 |  2 ++
 drivers/virtio/virtio_balloon.c         |  6 ++++--
 drivers/virtio/virtio_ring.c            | 11 +++++++++++
 include/linux/dma-mapping.h             |  8 ++++++++
 include/linux/swiotlb.h                 | 11 +++++++++++
 include/linux/virtio.h                  |  2 ++
 include/linux/virtio_config.h           | 13 +++++++++++++
 kernel/dma/direct.c                     | 11 +++++++++++
 kernel/dma/mapping.c                    | 14 ++++++++++++++
 kernel/dma/swiotlb.c                    | 14 ++++++++++++++
 15 files changed, 118 insertions(+), 9 deletions(-)
```
