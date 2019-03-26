

#### [PATCHv1 0/7] vfio/mdev: Improve vfio/mdev core module
##### From: Parav Pandit <parav@mellanox.com>

```c

As we would like to use mdev subsystem for wider use case as
discussed in [1], [2] apart from an offline discussion.
This use case is also discussed with wider forum in [4] in track
'Lightweight NIC HW functions for container offload use cases'.

This series is prep-work and improves vfio/mdev module in following ways.

Patch-1 Fixes releasing parent dev reference during error unwinding
mdev parent registration.
Patch-2 Simplifies mdev device for unused kref.
Patch-3 Drops redundant extern prefix of exported symbols.
Patch-4 Returns right error code from vendor driver.
Patch-5 Fixes to use right sysfs remove sequence.
Patch-6 Fixes removing all child devices if one of them fails.
Patch-7 Fixes conditions with mdev device life cycle APIs

This series is tested using
(a) mtty with VM using vfio_mdev driver for positive tests.
(b) mtty with vfio_mdev with error race condition cases of create,
remove and unloading of mtty driver.
(c) mlx5 core driver using RFC patches [3] and internal patches.
Internal patches are large and cannot be combined with this
prep-work patches. It will posted once prep-work completes.

[1] https://www.spinics.net/lists/netdev/msg556978.html
[2] https://lkml.org/lkml/2019/3/7/696
[3] https://lkml.org/lkml/2019/3/8/819
[4] https://netdevconf.org/0x13/session.html?workshop-hardware-offload
---
Changelog:
---

v0->v1:
 - Dropped device placement on bus sequence patch for this series
 - Addressed below comments from Alex, Kirti, Maxim.
 - Added Review-by tag for already reviewed patches.
 - Dropped incorrect patch of put_device().
 - Corrected Fixes commit tag for sysfs remove sequence fix
 - Split last 8th patch to smaller refactor and fixes patch
 - Following coding style commenting format
 - Fixed accidental delete of mutex_lock in mdev_unregister_device
 - Renamed remove helped to mdev_device_remove_common().
 - Rebased for uuid/guid change


Parav Pandit (7):
  vfio/mdev: Avoid release parent reference during error path
  vfio/mdev: Removed unused kref
  vfio/mdev: Drop redundant extern for exported symbols
  vfio/mdev: Avoid masking error code to EBUSY
  vfio/mdev: Follow correct remove sequence
  vfio/mdev: Fix aborting mdev child device removal if one fails
  vfio/mdev: Fix race conditions with mdev device life cycle APIs

 drivers/vfio/mdev/mdev_core.c    | 102 ++++++++++++++++++++++++++++-----------
 drivers/vfio/mdev/mdev_private.h |   7 ++-
 drivers/vfio/mdev/mdev_sysfs.c   |   2 +-
 include/linux/mdev.h             |  21 ++++----
 4 files changed, 91 insertions(+), 41 deletions(-)
```
