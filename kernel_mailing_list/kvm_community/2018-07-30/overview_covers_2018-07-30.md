

#### [PATCH v2 0/4] Balloon inhibit enhancements, vfio restriction
##### From: Alex Williamson <alex.williamson@redhat.com>

```c

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
---

Alex Williamson (4):
      balloon: Allow nested inhibits
      kvm: Use inhibit to prevent ballooning without synchronous mmu
      vfio: Inhibit ballooning based on group attachment to a container
      vfio/ccw/pci: Allow devices to opt-in for ballooning


 accel/kvm/kvm-all.c           |    4 ++++
 balloon.c                     |   13 ++++++++++---
 hw/vfio/ccw.c                 |    9 +++++++++
 hw/vfio/common.c              |   26 ++++++++++++++++++++++++++
 hw/vfio/pci.c                 |   26 +++++++++++++++++++++++++-
 hw/vfio/trace-events          |    1 +
 hw/virtio/virtio-balloon.c    |    4 +---
 include/hw/vfio/vfio-common.h |    2 ++
 8 files changed, 78 insertions(+), 7 deletions(-)
```
