

#### [PATCH v4 0/6] vfio-ccw: support hsch/csch (kernel part)
##### From: Cornelia Huck <cohuck@redhat.com>

```c

[This is the Linux kernel part, git tree is available at
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/vfio-ccw.git vfio-ccw-eagain-caps-v3

The companion QEMU patches are available at
https://github.com/cohuck/qemu vfio-ccw-caps]

Currently, vfio-ccw only relays START SUBCHANNEL requests to the real
device. This tends to work well for the most common 'good path' scenarios;
however, as we emulate {HALT,CLEAR} SUBCHANNEL in QEMU, things like
clearing pending requests at the device is currently not supported.
This may be a problem for e.g. error recovery.

This patch series introduces capabilities (similar to what vfio-pci uses)
and exposes a new async region for handling hsch/csch.

Lightly tested (I can interact with a dasd as before, and reserve/release
seems to work well.) Not sure if there is a better way to test this, ideas
welcome.

Changes v3->v4:
- shrunk the capability offset, we don't need to accommodate as much as pci
- make checks in patch 1 more consistent and less buggy
- rebased on top of my current vfio-ccw branch

Changes v2->v3:
- Unb0rked patch 1, improved scope
- Split out the new mutex from patch 2 into new patch 3; added missing
  locking and hopefully improved description
- Patch 2 now reworks the state handling by splitting the BUSY state
  into CP_PROCESSING and CP_PENDING
- Patches 3 and 5 adapted on top of the reworked patches; hsch/csch
  are allowed in CP_PENDING, but not in CP_PROCESSING (did not add
  any R-b due to that)
- Added missing free in patch 5
- Probably some small changes I forgot to note down

Changes v1->v2:
- New patch 1: make it safe to use the cp accessors at any time; this
  should avoid problems with unsolicited interrupt handling
- New patch 2: handle concurrent accesses to the io region; the idea is
  to return -EAGAIN to userspace more often (so it can simply retry)
- also handle concurrent accesses to the async io region
- change VFIO_REGION_TYPE_CCW
- merge events for halt and clear to a single async event; this turned out
  to make the code quite a bit simpler
- probably some small changes I forgot to note down

Cornelia Huck (6):
  vfio-ccw: make it safe to access channel programs
  vfio-ccw: rework ssch state handling
  vfio-ccw: protect the I/O region
  vfio-ccw: add capabilities chain
  s390/cio: export hsch to modules
  vfio-ccw: add handling for async channel instructions

 drivers/s390/cio/Makefile           |   3 +-
 drivers/s390/cio/ioasm.c            |   1 +
 drivers/s390/cio/vfio_ccw_async.c   |  88 ++++++++++++
 drivers/s390/cio/vfio_ccw_cp.c      |  21 ++-
 drivers/s390/cio/vfio_ccw_cp.h      |   2 +
 drivers/s390/cio/vfio_ccw_drv.c     |  57 ++++++--
 drivers/s390/cio/vfio_ccw_fsm.c     | 143 +++++++++++++++++-
 drivers/s390/cio/vfio_ccw_ops.c     | 215 +++++++++++++++++++++++-----
 drivers/s390/cio/vfio_ccw_private.h |  48 ++++++-
 include/uapi/linux/vfio.h           |   4 +
 include/uapi/linux/vfio_ccw.h       |  12 ++
 11 files changed, 537 insertions(+), 57 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_async.c
```
#### [PATCH v3 0/2] vfio-ccw: support hsch/csch (QEMU part)
##### From: Cornelia Huck <cohuck@redhat.com>

```c

[This is the QEMU part, git tree is available at
https://github.com/cohuck/qemu vfio-ccw-caps

The companion Linux kernel patches are available at
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/vfio-ccw.git vfio-ccw-eagain-caps-v4]

Currently, vfio-ccw only relays START SUBCHANNEL requests to the real
device. This tends to work well for the most common 'good path' scenarios;
however, as we emulate {HALT,CLEAR} SUBCHANNEL in QEMU, things like
clearing pending requests at the device is currently not supported.
This may be a problem for e.g. error recovery.

This patch series makes use of the newly introduced async command region
to issue hsch/csch; if it is not present, continue to emulate hsch/csch,
as before.

Note that the kernel side now returns -EAGAIN to trigger a retry in more
cases; QEMU should already be fine with that.

[I'm not quite happy with how this async processing hooks up in css.c;
ideas welcome.]

Lightly tested (I can interact with a dasd as before, and reserve/release
seems to work well.) Not sure if there is a better way to test this, ideas
welcome.


Changes v2->v3:
- update kernel header to v4 of kernel patches
- rebased on master
Changes v1->v2:
- update kernel header to v2 of kernel patches
- rebased on master

Cornelia Huck (2):
  vfio-ccw: new capability chain support
  vfio-ccw: support async command subregion

 hw/s390x/css.c                 |  27 ++++++--
 hw/vfio/ccw.c                  | 109 ++++++++++++++++++++++++++++++++-
 include/hw/s390x/s390-ccw.h    |   3 +
 linux-headers/linux/vfio.h     |   4 ++
 linux-headers/linux/vfio_ccw.h |  12 ++++
 5 files changed, 149 insertions(+), 6 deletions(-)
```
