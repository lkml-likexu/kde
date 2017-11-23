

#### [PATCH v4 0/6] VFIO mdev aggregated resources handling
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c

Hi,

This is respin of previous sending from https://www.spinics.net/lists/kvm/msg176447.html

Current mdev device create interface depends on fixed mdev type, which get uuid
from user to create instance of mdev device. If user wants to use customized
number of resource for mdev device, then only can create new mdev type for that
which may not be flexible. This requirement comes not only from to be able to
allocate flexible resources for KVMGT, but also from Intel scalable IO
virtualization which would use vfio/mdev to be able to allocate arbitrary
resources on mdev instance. More info on [1] [2] [3].

To allow to create user defined resources for mdev, it trys to extend mdev
create interface by adding new "aggregate=xxx" parameter following UUID, for
target mdev type if aggregation is supported, it can create new mdev device
which contains resources combined by number of instances, e.g

    echo "<uuid>,aggregate=10" > create

VM manager e.g libvirt can check mdev type with "aggregation" attribute which
can support this setting. If no "aggregation" attribute found for mdev type,
previous behavior is still kept for one instance allocation. And new sysfs
attribute "aggregated_instances" is created for each mdev device to show allocated number.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification  
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

v2:
  - Add new create_with_instances driver hook
  - Update doc for new attributes

v3:
  - Rename parameter and attribute names from review
  - Make "aggregation" attribute to show maxium resource number
    for aggregation
  - Check driver hooks for attribute create validation
  - Update doc and ABI spec

v4:
  - Rebase

Zhenyu Wang (6):
  vfio/mdev: Add new "aggregate" parameter for mdev create
  vfio/mdev: Add "aggregation" attribute for supported mdev type
  vfio/mdev: Add "aggregated_instances" attribute for supported mdev
    device
  Documentation/vfio-mediated-device.txt: Update for vfio/mdev
    aggregation support
  Documentation/ABI/testing/sysfs-bus-vfio-mdev: Update for vfio/mdev
    aggregation support
  drm/i915/gvt: Add new type with aggregation support

 Documentation/ABI/testing/sysfs-bus-vfio-mdev | 25 +++++++
 Documentation/vfio-mediated-device.txt        | 44 +++++++++--
 drivers/gpu/drm/i915/gvt/gvt.h                | 11 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 53 ++++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c               | 56 +++++++++++++-
 drivers/vfio/mdev/mdev_core.c                 | 40 +++++++++-
 drivers/vfio/mdev/mdev_private.h              |  6 +-
 drivers/vfio/mdev/mdev_sysfs.c                | 74 ++++++++++++++++++-
 include/linux/mdev.h                          | 19 +++++
 9 files changed, 305 insertions(+), 23 deletions(-)
```
#### [PATCH v2 0/4] x86/kvm/hyper-v: Implement Direct Mode for synthetic
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v1:
- avoid open-coding stimer_mark_pending() in kvm_hv_notify_acked_sint() and
  kvm_hv_synic_send_eoi [Paolo Bonzini]

Turns out Hyper-V on KVM (as of 2016) will only use synthetic timers
if direct mode is available. With direct mode we notify the guest by
asserting APIC irq instead of sending a SynIC message.

Qemu and kvm-unit-test patches for testing this series can be found in
v1 submission:
https://lkml.org/lkml/2018/11/13/972

Vitaly Kuznetsov (4):
  x86/hyper-v: move synic/stimer control structures definitions to
    hyperv-tlfs.h
  x86/kvm/hyper-v: use stimer config definition from hyperv-tlfs.h
  x86/kvm/hyper-v: direct mode for synthetic timers
  x86/kvm/hyper-v: avoid open-coding stimer_mark_pending() in
    kvm_hv_notify_acked_sint()

 arch/x86/include/asm/hyperv-tlfs.h |  73 ++++++++++++++++++--
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/hyperv.c              | 106 +++++++++++++++++++++--------
 arch/x86/kvm/trace.h               |  10 +--
 arch/x86/kvm/x86.c                 |   1 +
 drivers/hv/hv.c                    |   2 +-
 drivers/hv/hyperv_vmbus.h          |  68 ------------------
 include/uapi/linux/kvm.h           |   1 +
 8 files changed, 154 insertions(+), 109 deletions(-)
```
#### [PATCH 0/3] kvm: split retrieval and clearing of dirty log
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

There are two problems with KVM_GET_DIRTY_LOG.  First, and less important,
it can take kvm->mmu_lock for an extended period of time.  Second, its user
can actually see many false positives in some cases.  The latter is due
to a benign race like this:

  1. KVM_GET_DIRTY_LOG returns a set of dirty pages and write protects
     them.
  2. The guest modifies the pages, causing them to be marked ditry.
  3. Userspace actually copies the pages.
  4. KVM_GET_DIRTY_LOG returns those pages as dirty again, even though
     they were not written to since (3).

This is especially a problem for large guests, where the time between
(1) and (3) can be substantial.  This patch introduces a new
capability which, when enabled, makes KVM_GET_DIRTY_LOG not
write-protect the pages it returns.  Instead, userspace has to
explicitly clear the dirty log bits just before using the content
of the page.  The new KVM_CLEAR_DIRTY_LOG ioctl can operate on a
64-page granularity rather than requiring to sync a full memslot.
This way the mmu_lock is taken for small amounts of time, and
only a small amount of time will pass between write protection
of pages and the sending of their content.

This is entirely implemented in generic code, but only users of
kvm_get_dirty_log_protect get the support (that is x86_64 and ARM).

Paolo Bonzini (3):
  kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic
  kvm: rename last argument to kvm_get_dirty_log_protect
  kvm: introduce manual dirty log reprotect

 Documentation/virtual/kvm/api.txt                  |  78 ++++++++++-
 arch/mips/kvm/mips.c                               |  29 +++-
 arch/powerpc/kvm/powerpc.c                         |  14 +-
 arch/s390/kvm/kvm-s390.c                           |  11 +-
 arch/x86/kvm/x86.c                                 |  47 ++++---
 include/linux/kvm_host.h                           |   9 +-
 include/uapi/linux/kvm.h                           |  15 +++
 tools/testing/selftests/kvm/Makefile               |   2 +
 tools/testing/selftests/kvm/clear_dirty_log_test.c |   2 +
 tools/testing/selftests/kvm/dirty_log_test.c       |  19 +++
 tools/testing/selftests/kvm/include/kvm_util.h     |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  13 ++
 virt/kvm/arm/arm.c                                 |  22 ++-
 virt/kvm/kvm_main.c                                | 147 ++++++++++++++++++---
 14 files changed, 345 insertions(+), 65 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
```
