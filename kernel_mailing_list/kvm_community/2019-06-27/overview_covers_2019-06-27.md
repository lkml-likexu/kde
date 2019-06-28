

#### [RFC PATCH v3 0/4] Deliver vGPU display vblank event to userspace
##### From: Tina Zhang <tina.zhang@intel.com>

```c

This series tries to send the vGPU display vblank event to user land.

Instead of delivering page flip events, we choose to post display vblank
event. Handling page flip events for both primary plane and cursor plane
may make user space quite busy, although we have the mask/unmask mechansim
for mitigation. Besides, there are some cases that guest app only uses
one framebuffer for both drawing and display. In such case, guest OS won't
do the plane page flip when the framebuffer is updated, thus the user
land won't be notified about the updated framebuffer.

With vGPU's vblank event working as a timer, userspace still needs to
query the framebuffer first, before getting a new dma-buf for it.

v3:
- Deliver display vblank event instead of page flip event. (Zhenyu)
v2:
- Use VFIO irq chain to get eventfds from userspace instead of adding
a new ABI. (Alex)
v1:
- https://patchwork.kernel.org/cover/10962341/


Tina Zhang (4):
  vfio: Define device specific irq type capability
  vfio: Introduce vGPU display irq type
  drm/i915/gvt: Register vGPU display vblank irq
  drm/i915/gvt: Deliver vGPU vblank event to userspace

 drivers/gpu/drm/i915/gvt/display.c   |  14 +-
 drivers/gpu/drm/i915/gvt/gvt.h       |   6 +
 drivers/gpu/drm/i915/gvt/hypercall.h |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c     | 193 +++++++++++++++++++++++++--
 drivers/gpu/drm/i915/gvt/mpt.h       |  17 +++
 include/uapi/linux/vfio.h            |  22 ++-
 6 files changed, 241 insertions(+), 12 deletions(-)
```
