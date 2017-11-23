

#### [PATCH v3 00/10] migration: compression optimization
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Changelog in v3:

Thanks to Peter's comments, the changes in this version are:
1) make compress-wait-thread be true on default to keep current behavior
2) save the compressed-size instead of reduced size and fix calculating
   compression ratio
3) fix calculating xbzrle_counters.cache_miss_rate and
   compression_counters.busy_rate


Xiao Guangrong (10):
  migration: do not wait for free thread
  migration: fix counting normal page for compression
  migration: introduce save_zero_page_to_file
  migration: drop the return value of do_compress_ram_page
  migration: move handle of zero page to the thread
  migration: hold the lock only if it is really needed
  migration: do not flush_compressed_data at the end of each iteration
  migration: handle the error condition properly
  migration: fix calculating xbzrle_counters.cache_miss_rate
  migration: show the statistics of compression

 hmp.c                 |  21 ++++
 include/qemu/queue.h  |   1 +
 migration/migration.c |  33 ++++++
 migration/migration.h |   1 +
 migration/ram.c       | 283 +++++++++++++++++++++++++++++++++++++-------------
 migration/ram.h       |   1 +
 qapi/migration.json   |  49 +++++++--
 7 files changed, 308 insertions(+), 81 deletions(-)
```
#### [PATCH v3 0/4] Balloon inhibit enhancements, vfio restriction
##### From: Alex Williamson <alex.williamson@redhat.com>

```c

v3:
 - Drop "nested" term in commit log (David)
 - Adopt suggested wording in ccw code (Cornelia)
 - Explain balloon inhibitor usage in vfio common (Peter)
 - Fix to call inhibitor prior to re-using existing containers
   to avoid gap that pinning may have occurred in set container
   ioctl (self) - Peter, this change is the reason I didn't
   include your R-b.
 - Add R-b to patches 1 & 2

v2:
 - Use atomic ops for balloon inhibit counter (Peter)
 - Allow endpoint driver opt-in for ballooning, vfio-ccw opt-in by
   default, vfio-pci opt-in by device option, only allowed for mdev
   devices, no support added for platform as there are no platform
   mdev devices.

See patch 3/4 for detailed explanation why ballooning and device
assignment typically don't mix.  If this eventually changes, flags
on the iommu info struct or perhaps device info struct can inform
us for automatic opt-in.  Thanks,

Alex

Alex Williamson (4):
  balloon: Allow multiple inhibit users
  kvm: Use inhibit to prevent ballooning without synchronous mmu
  vfio: Inhibit ballooning based on group attachment to a container
  vfio/ccw/pci: Allow devices to opt-in for ballooning

 accel/kvm/kvm-all.c           |  4 +++
 balloon.c                     | 13 ++++++---
 hw/vfio/ccw.c                 |  9 +++++++
 hw/vfio/common.c              | 51 +++++++++++++++++++++++++++++++++++
 hw/vfio/pci.c                 | 26 +++++++++++++++++-
 hw/vfio/trace-events          |  1 +
 hw/virtio/virtio-balloon.c    |  4 +--
 include/hw/vfio/vfio-common.h |  2 ++
 8 files changed, 103 insertions(+), 7 deletions(-)
```
