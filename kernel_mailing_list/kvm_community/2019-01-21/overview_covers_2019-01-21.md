

#### [PATCH v2 0/5] vfio-ccw: support hsch/csch (kernel part)
##### From: Cornelia Huck <cohuck@redhat.com>

```c

[This is the Linux kernel part, git tree is available at
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/vfio-ccw.git vfio-ccw-eagain-caps

The companion QEMU patches are available at
https://github.com/cohuck/qemu vfio-ccw-caps]

Currently, vfio-ccw only relays START SUBCHANNEL requests to the real
device. This tends to work well for the most common 'good path' scenarios;
however, as we emulate {HALT,CLEAR} SUBCHANNEL in QEMU, things like
clearing pending requests at the device is currently not supported.
This may be a problem for e.g. error recovery.

This patch series introduces capabilities (similar to what vfio-pci uses)
and exposes a new async region for handling hsch/csch.

New in v2 are two patches dealing with concurrency.

Lightly tested (I can interact with a dasd as before, and reserve/release
seems to work well.) Not sure if there is a better way to test this, ideas
welcome.

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


Cornelia Huck (5):
  vfio-ccw: make it safe to access channel programs
  vfio-ccw: concurrent I/O handling
  vfio-ccw: add capabilities chain
  s390/cio: export hsch to modules
  vfio-ccw: add handling for async channel instructions

 drivers/s390/cio/Makefile           |   3 +-
 drivers/s390/cio/ioasm.c            |   1 +
 drivers/s390/cio/vfio_ccw_async.c   |  91 ++++++++++++
 drivers/s390/cio/vfio_ccw_cp.c      |   3 +
 drivers/s390/cio/vfio_ccw_cp.h      |   2 +
 drivers/s390/cio/vfio_ccw_drv.c     |  46 ++++--
 drivers/s390/cio/vfio_ccw_fsm.c     | 122 +++++++++++++++-
 drivers/s390/cio/vfio_ccw_ops.c     | 211 +++++++++++++++++++++++-----
 drivers/s390/cio/vfio_ccw_private.h |  45 ++++++
 include/uapi/linux/vfio.h           |   4 +
 include/uapi/linux/vfio_ccw.h       |  12 ++
 11 files changed, 487 insertions(+), 53 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_async.c
```
#### [PATCH v2 0/2] vfio-ccw: support hsch/csch (QEMU part)
##### From: Cornelia Huck <cohuck@redhat.com>

```c

[This is the QEMU part, git tree is available at
https://github.com/cohuck/qemu vfio-ccw-caps

The companion Linux kernel patches are available at
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/vfio-ccw.git vfio-ccw-eagain-caps]

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
#### [PATCH 0/3] virtio-ccw: updates
##### From: Cornelia Huck <cohuck@redhat.com>

```c

[Now not as pull request, as requested. The first patch had already been
in my last pull request. Patches are against master, but should apply
basically anywhere.

Git branch:
git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git virtio-ccw]

Some updates: documentation, gracefully handle invalid queues, and wire
up the ->bus_name callback (which had somehow fallen through the cracks.)

Cornelia Huck (2):
  virtio-ccw: diag 500 may return a negative cookie
  virtio-ccw: wire up ->bus_name callback

Halil Pasic (1):
  s390/virtio: handle find on invalid queue gracefully

 Documentation/virtual/kvm/s390-diag.txt |  3 ++-
 drivers/s390/virtio/virtio_ccw.c        | 12 +++++++++++-
 2 files changed, 13 insertions(+), 2 deletions(-)
```
#### [RFC v1 0/2] Small vfio-ccw fixes
##### From: Farhan Ali <alifm@linux.ibm.com>

```c

Hi,

I have noticed some errors when running an intensive I/O workload
on a passthrough DASD device.

While debugging and looking through the code, I found 2 places
where things don't look write.

Thank you
Farhan

Farhan Ali (2):
  vfio-ccw: Don't assume there are more ccws after a TIC
  vfio-ccw: Don't exit early if state of the vfio-ccw subchannel is not
    idle

 drivers/s390/cio/vfio_ccw_cp.c  | 2 +-
 drivers/s390/cio/vfio_ccw_ops.c | 2 --
 2 files changed, 1 insertion(+), 3 deletions(-)
```
