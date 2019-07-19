

#### [RFC PATCH v4 0/6] Deliver vGPU display refresh event to  userspace
##### From: Kechen Lu <kechen.lu@intel.com>

```c

This series tries to send the vGPU display refresh event to user land.

Instead of delivering page flip events only or vblank events only, we 
choose to combine two of them, i.e. post display refresh event at vblanks 
and skip some of them when no page flip happens. Vblanks as upper bound 
are safe and skipping no-page-flip vblanks guarantees both trivial performance 
impacts and good user experience without screen tearing. Plus, we have the 
mask/unmask mechansim providing user space flexibility to switch between 
event-notified refresh and classic timer-based refresh.

In addition, there are some cases that guest app only uses one framebuffer 
for both drawing and display. In such case, guest OS won't do the plane page 
flip when the framebuffer is updated, thus the user land won't be notified 
about the updated framebuffer. Hence, in single framebuffer case, we apply
a heuristic to determine whether it is the case or not. If it is, notify user
land when each vblank event triggers.

v4:
- Deliver page flip event and single framebuffer refresh event bounded 
by display vblanks. (Kechen)
v3:
- Deliver display vblank event instead of page flip event. (Zhenyu)
v2:
- Use VFIO irq chain to get eventfds from userspace instead of adding
a new ABI. (Alex)
v1:
- https://patchwork.kernel.org/cover/10962341/

Kechen Lu (2):
  drm/i915/gvt: Deliver async primary plane page flip events at vblank
  drm/i915/gvt: Add cursor plane reg update trap emulation handler

Tina Zhang (4):
  vfio: Define device specific irq type capability
  vfio: Introduce vGPU display irq type
  drm/i915/gvt: Register vGPU display event irq
  drm/i915/gvt: Deliver vGPU refresh event to userspace

 drivers/gpu/drm/i915/gvt/cmd_parser.c |   5 +-
 drivers/gpu/drm/i915/gvt/display.c    |  54 ++++++-
 drivers/gpu/drm/i915/gvt/gvt.h        |  11 ++
 drivers/gpu/drm/i915/gvt/handlers.c   |  32 ++++-
 drivers/gpu/drm/i915/gvt/hypercall.h  |   1 +
 drivers/gpu/drm/i915/gvt/interrupt.c  |   7 +
 drivers/gpu/drm/i915/gvt/interrupt.h  |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c      | 197 ++++++++++++++++++++++++--
 drivers/gpu/drm/i915/gvt/mpt.h        |  17 +++
 include/uapi/linux/vfio.h             |  22 ++-
 10 files changed, 330 insertions(+), 19 deletions(-)
```
#### [PATCH v3 0/2] Boost vCPUs that are ready to deliver interrupts
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

My take on Wanpeng's patches with some extra cleanups.

Wanpeng Li (2):
  KVM: Boost vCPUs that are delivering interrupts
  KVM: s390: Use kvm_vcpu_wake_up in kvm_s390_vcpu_wakeup

 arch/s390/kvm/interrupt.c | 23 +++--------------------
 include/linux/kvm_host.h  |  1 +
 virt/kvm/kvm_main.c       |  9 +++++++--
 3 files changed, 11 insertions(+), 22 deletions(-)
```
