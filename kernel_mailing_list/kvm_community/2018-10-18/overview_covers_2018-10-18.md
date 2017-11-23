

#### [PATCH v1 0/2] vfio: ccw: VFIO CCW cleanup part1
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

The first patch of this serie is essentially cosmetic
to clarify the code.

The second patch is a bug correction.



Pierre Morel (2):
  vfio: ccw: Merge BUSY and BOXED states
  vfio: ccw: Register mediated device once all structures are
    initialized

 drivers/s390/cio/vfio_ccw_drv.c     | 8 ++++----
 drivers/s390/cio/vfio_ccw_fsm.c     | 7 +------
 drivers/s390/cio/vfio_ccw_private.h | 1 -
 3 files changed, 5 insertions(+), 11 deletions(-)
```
