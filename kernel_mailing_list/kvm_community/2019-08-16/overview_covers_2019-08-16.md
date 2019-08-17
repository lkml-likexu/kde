

#### [PATCH v5 0/6] Deliver vGPU display refresh event to userspace
##### From: Tina Zhang <tina.zhang@intel.com>

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

v5:
- Introduce a vGPU display irq cap which can notify user space with
  both primary and cursor plane update events through one eventfd. (Gerd & Alex)
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

 drivers/gpu/drm/i915/gvt/cmd_parser.c |   6 +-
 drivers/gpu/drm/i915/gvt/display.c    |  49 +++++-
 drivers/gpu/drm/i915/gvt/display.h    |   3 +
 drivers/gpu/drm/i915/gvt/gvt.h        |   6 +
 drivers/gpu/drm/i915/gvt/handlers.c   |  32 +++-
 drivers/gpu/drm/i915/gvt/hypercall.h  |   1 +
 drivers/gpu/drm/i915/gvt/interrupt.c  |   7 +
 drivers/gpu/drm/i915/gvt/interrupt.h  |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c      | 230 +++++++++++++++++++++++++-
 drivers/gpu/drm/i915/gvt/mpt.h        |  17 ++
 include/uapi/linux/vfio.h             |  40 ++++-
 11 files changed, 375 insertions(+), 19 deletions(-)
```
#### [PATCH v2 00/10] Add definition for the number of standard PCI BARs
##### From: Denis Efremov <efremov@linux.com>

```c

Code that iterates over all standard PCI BARs typically uses
PCI_STD_RESOURCE_END, but this is error-prone because it requires
"i <= PCI_STD_RESOURCE_END" rather than something like
"i < PCI_STD_NUM_BARS". We could add such a definition and use it the same
way PCI_SRIOV_NUM_BARS is used. There is already the definition
PCI_BAR_COUNT for s390 only. Thus, this patchset introduces it globally.

Changes in v2:
  - Reverse checks in pci_iomap_range,pci_iomap_wc_range.
  - Refactor loops in vfio_pci to keep PCI_STD_RESOURCES.
  - Add 2 new patches to replace the magic constant with new define.
  - Split net patch in v1 to separate stmmac and dwc-xlgmac patches.

Denis Efremov (10):
  PCI: Add define for the number of standard PCI BARs
  s390/pci: Loop using PCI_STD_NUM_BARS
  x86/PCI: Loop using PCI_STD_NUM_BARS
  stmmac: pci: Loop using PCI_STD_NUM_BARS
  net: dwc-xlgmac: Loop using PCI_STD_NUM_BARS
  rapidio/tsi721: Loop using PCI_STD_NUM_BARS
  efifb: Loop using PCI_STD_NUM_BARS
  vfio_pci: Loop using PCI_STD_NUM_BARS
  PCI: hv: Use PCI_STD_NUM_BARS
  PCI: Use PCI_STD_NUM_BARS

 arch/s390/include/asm/pci.h                      |  5 +----
 arch/s390/include/asm/pci_clp.h                  |  6 +++---
 arch/s390/pci/pci.c                              | 16 ++++++++--------
 arch/s390/pci/pci_clp.c                          |  6 +++---
 arch/x86/pci/common.c                            |  2 +-
 drivers/net/ethernet/stmicro/stmmac/stmmac_pci.c |  4 ++--
 drivers/net/ethernet/synopsys/dwc-xlgmac-pci.c   |  2 +-
 drivers/pci/controller/pci-hyperv.c              | 10 +++++-----
 drivers/pci/pci.c                                | 11 ++++++-----
 drivers/pci/quirks.c                             |  4 ++--
 drivers/rapidio/devices/tsi721.c                 |  2 +-
 drivers/vfio/pci/vfio_pci.c                      | 11 +++++++----
 drivers/vfio/pci/vfio_pci_config.c               | 10 ++++++----
 drivers/vfio/pci/vfio_pci_private.h              |  4 ++--
 drivers/video/fbdev/efifb.c                      |  2 +-
 include/linux/pci.h                              |  2 +-
 include/uapi/linux/pci_regs.h                    |  1 +
 17 files changed, 51 insertions(+), 47 deletions(-)
```
#### [PATCH RFC 0/1] s390dbf logging for vfio-ccw
##### From: Cornelia Huck <cohuck@redhat.com>

```c

The current discussions around uuids and mdev devices got me thinking,
and I realized that the uuid is an interesting information for
debugging devices.

Currently, vfio-ccw does not really log any debug data (there's just
a lone trace event). The common I/O layer has logged interesting
information into the s390dbf for a long time; this has been very
useful in the past, as the logged information can be accessed in a
crash dump (e.g. by the crash tool). We cannot log directly into
the common I/O layer debug features, though, as vfio-ccw may be a
module.

Another limitation is that for the sprintf-type debug feature, any
string logged via '%s' must outlive the debug feature (as it is not
copied for performance reasons). That means that logging the device
name is right out, as devices may go away (the current common I/O
layer code logs the numerical values of ssid/subchannel number instead);
logging the uuid of an mdev device via %pU just works fine, though.

My patch just logs some basics right now, we can certainly add more
events. We should also think about adding more trace events: they
may serve a similar purpose, especially if we should enhance the vfio
code with trace events in the future (so that we can correlate those
trace events with the vfio-ccw trace events, just as we can correlate
the s390dbf events with the common I/O layer dbf events to get a more
complete picture.)

Cornelia Huck (1):
  vfio-ccw: add some logging

 drivers/s390/cio/vfio_ccw_drv.c     | 50 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_fsm.c     | 51 ++++++++++++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_ops.c     | 10 ++++++
 drivers/s390/cio/vfio_ccw_private.h | 17 ++++++++++
 4 files changed, 124 insertions(+), 4 deletions(-)
```
