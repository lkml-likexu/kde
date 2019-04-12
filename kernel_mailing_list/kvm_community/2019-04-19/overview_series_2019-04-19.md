#### [PATCH 1/2] vfio/mdev: add version field as mandatory attribute for mdev device
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
device version attribute in mdev sysfs is used by user space software
(e.g. libvirt) to query device compatibility for live migration of VFIO
mdev devices. This attribute is mandatory if a mdev device supports live
migration.

It consists of two parts: common part and vendor proprietary part.
common part: 32 bit. lower 16 bits is vendor id and higher 16 bits
             identifies device type. e.g., for pci device, it is
             "pci vendor id" | (VFIO_DEVICE_FLAGS_PCI << 16).
vendor proprietary part: this part is varied in length. vendor driver can
             specify any string to identify a device.

When reading this attribute, it should show device version string of the
device of type <type-id>. If a device does not support live migration, it
should return errno.
When writing a string to this attribute, it returns errno for
incompatibility or returns written string length in compatibility case.
If a device does not support live migration, it always returns errno.

For user space software to use:
1.
Before starting live migration, user space software first reads source side
mdev device's version. e.g.
"#cat \
/sys/bus/pci/devices/0000\:00\:02.0/5ac1fb20-2bbf-4842-bb7e-36c58c3be9cd/mdev_type/version"
00028086-193b-i915-GVTg_V5_4

2.
Then, user space software writes the source side returned version string
to device version attribute in target side, and checks the return value.
If a negative errno is returned in the target side, then mdev devices in
source and target sides are not compatible;
If a positive number is returned and it equals to the length of written
string, then the two mdev devices in source and target side are compatible.
e.g.
(a) compatibility case
"# echo 00028086-193b-i915-GVTg_V5_4 >
/sys/bus/pci/devices/0000\:00\:02.0/882cc4da-dede-11e7-9180-078a62063ab1/mdev_type/version"

(b) incompatibility case
"#echo 00028086-193b-i915-GVTg_V5_1 >
/sys/bus/pci/devices/0000\:00\:02.0/882cc4da-dede-11e7-9180-078a62063ab1/mdev_type/version"
-bash: echo: write error: Invalid argument

3. if two mdev devices are compatible, user space software can start
live migration, and vice versa.

Note: if a mdev device does not support live migration, it either does
not provide a version attribute, or always returns errno when its version
attribute is read/written.

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Erik Skultety <eskultet@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: "Tian, Kevin" <kevin.tian@intel.com>
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: "Wang, Zhi A" <zhi.a.wang@intel.com>
Cc: Neo Jia <cjia@nvidia.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 Documentation/vfio-mediated-device.txt | 36 ++++++++++++++++++++++++++
 samples/vfio-mdev/mbochs.c             | 17 ++++++++++++
 samples/vfio-mdev/mdpy.c               | 16 ++++++++++++
 samples/vfio-mdev/mtty.c               | 16 ++++++++++++
 4 files changed, 85 insertions(+)

```
#### [kvm-unit-tests PULL 1/4] Add s390x/*.bin to the .gitignore file
##### From: Thomas Huth <thuth@redhat.com>

```c
Since commit 1a4cd2f22a48b8de53ef9e46afb8 ("s390x: Add binary generation
to makefile") we are also generating *.bin files from the *.elf files
in the s390x directory. Add them to the .gitignore file so that they
do not show up in the output of "git status" anymore.

Acked-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .gitignore | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] kvm: x86: refine kvm_get_arch_capabilities()
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
1. Using X86_FEATURE_ARCH_CAPABILITIES to enumerate the existence of
MSR_IA32_ARCH_CAPABILITIES to avoid using rdmsrl_safe().

2. Since kvm_get_arch_capabilities() is only used in this file, making
it static.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h | 1 -
 arch/x86/kvm/x86.c              | 8 ++++----
 2 files changed, 4 insertions(+), 5 deletions(-)

```
#### [PATCH RFC] KVM: x86: Add a mechanism for restricting guest PMU access to a set of whitelisted events
##### From: Eric Hankland <ehankland@google.com>

```c
Some events can provide a guest with information about other guests or the host
 (e.g. L3 cache stats); providing the capability to restrict access to
a "safe" set
 of events would limit the potential for the PMU to be used in any side channel
 attacks. This change introduces a new vcpu ioctl that sets an event whitelist.
If the guest attempts to program a counter for any unwhitelisted event,
the kernel counter won't be created, so any RDPMC/RDMSR will
show 0 instances of that event.

Signed-off-by: Eric Hankland <ehankland@google.com>

```
