#### [PATCH v15 01/17] uaccess: add untagged_addr definition for other arches
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
To allow arm64 syscalls to accept tagged pointers from userspace, we must
untag them when they are passed to the kernel. Since untagging is done in
generic parts of the kernel, the untagged_addr macro needs to be defined
for all architectures.

Define it as a noop for architectures other than arm64.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 include/linux/mm.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v2 2/2] drm/i915/gvt: export mdev device version to sysfs for Intel vGPU
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
This feature implements the version attribute for Intel's vGPU mdev
devices.

version attribute is rw.
It's used to check device compatibility for two mdev devices.
version string format and length are private for vendor driver. vendor
driver is able to define them freely.

For Intel vGPU of gen8 and gen9, the mdev device version
consists of 3 fields: "vendor id" + "device id" + "mdev type".

Reading from a vGPU's version attribute, a string is returned in below
format: <vendor id>-<device id>-<mdev type>. e.g.
8086-193b-i915-GVTg_V5_2.

Writing a string to a vGPU's version attribute will trigger GVT to check
whether a vGPU identified by the written string is compatible with
current vGPU owning this version attribute. errno is returned if the two
vGPUs are incompatible. The length of written string is returned in
compatible case.

For other platforms, and for GVT not supporting vGPU live migration
feature, errnos are returned when read/write of mdev devices' version
attributes.

For old GVT versions where no version attributes exposed in sysfs, it is
regarded as not supporting vGPU live migration.

For future platforms, besides the current 2 fields in vendor proprietary
part, more fields may be added to identify Intel vGPU well for live
migration purpose.

v2:
1. removed 32 common part of version string
(Alex Williamson)
2. do not register version attribute for GVT not supporting live
migration.(Cornelia Huck)
3. for platforms out of gen8, gen9, return -EINVAL --> -ENODEV for
incompatible. (Cornelia Huck)

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Erik Skultety <eskultet@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: "Tian, Kevin" <kevin.tian@intel.com>
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: "Wang, Zhi A" <zhi.a.wang@intel.com>
c: Neo Jia <cjia@nvidia.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/gpu/drm/i915/gvt/Makefile         |  2 +-
 drivers/gpu/drm/i915/gvt/device_version.c | 87 +++++++++++++++++++++++
 drivers/gpu/drm/i915/gvt/gvt.c            | 51 +++++++++++++
 drivers/gpu/drm/i915/gvt/gvt.h            |  6 ++
 4 files changed, 145 insertions(+), 1 deletion(-)
 create mode 100644 drivers/gpu/drm/i915/gvt/device_version.c

```
#### [PATCH v1 1/2] vfio-ccw: Set subchannel state STANDBY on open
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
When no guest is associated with the mediated device,
i.e. the mediated device is not opened, the state of
the mediated device is VFIO_CCW_STATE_NOT_OPER.

The subchannel enablement and the according setting to the
VFIO_CCW_STATE_STANDBY state should only be done when all
parts of the VFIO mediated device have been initialized
i.e. after the mediated device has been successfully opened.

Let's stay in VFIO_CCW_STATE_NOT_OPER until the mediated
device has been opened.

When the mediated device is closed, disable the sub channel
by calling vfio_ccw_sch_quiesce() no reset needs to be done
the mediated devce will be enable on next open.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 10 +---------
 drivers/s390/cio/vfio_ccw_ops.c | 36 ++++++++++++++++++------------------
 2 files changed, 19 insertions(+), 27 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Disable intercept for *_BASE MSR in vmcs02 when possible
##### From: Jintack Lim <jintack@cs.columbia.edu>

```c
Even when neither L0 nor L1 configured to trap *_BASE MSR accesses from
its own VMs, the current KVM L0 always traps *_BASE MSR accesses from
L2.  Let's check if both L0 and L1 disabled trap for *_BASE MSR for its
VMs respectively, and let L2 access to*_BASE MSR without trap if that's
the case.

Signed-off-by: Jintack Lim <jintack@cs.columbia.edu>
---

Changes since v1:
- Added GS_BASE and KENREL_GS_BASE (Jim, Sean)
- Changed to allow reads as well as writes (Sean)
---
 arch/x86/kvm/vmx/nested.c | 24 +++++++++++++++++++++++-
 1 file changed, 23 insertions(+), 1 deletion(-)

```
#### [PATCH v2] tests: kvm: Add tests to .gitignoreFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 tools/testing/selftests/kvm/.gitignore | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
