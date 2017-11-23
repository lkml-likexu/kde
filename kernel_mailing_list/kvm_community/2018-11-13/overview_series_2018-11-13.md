#### [PATCH 1/6] nVMX x86: Re-name check_vmentry_pre[post]reqs to nested_check_vmentry_pre[post]
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Re-name the functions check_vmentry_pre[post]reqs to
nested_check_pre[post]reqs because these functions are used only in
nested context.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/kvm/vmx.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: nSVM: Fix nested guest support for PAUSE filtering.Thread-Topic: [PATCH] KVM: nSVM: Fix nested guest support for PAUSE filtering.
##### From: "Tambe, William" <William.Tambe@amd.com>

```c
Currently, the nested guest's PAUSE intercept intentions are not being
honored.  Instead, since the L0 hypervisor's pause_filter_count and
pause_filter_thresh values are still in place, these values are used
instead of those programmed in the VMCB by the L1 hypervisor.

To honor the desired PAUSE intercept support of the L1 hypervisor, the L0
hypervisor must use the PAUSE filtering fields of the L1 hypervisor. This
requires saving and restoring of both the L0 and L1 hypervisor's PAUSE
filtering fields.

Signed-off-by: William Tambe <william.tambe@amd.com>
---
 arch/x86/kvm/svm.c | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [PATCH] KVM: nVMX: vmcs12 revision_id is always VMCS12_REVISION even when copied from eVMCS
##### From: Liran Alon <liran.alon@oracle.com>

```c
vmcs12 represents the per-CPU cache of L1 active vmcs12.

This cache can be loaded by one of the following:
1) Guest making a vmcs12 active by exeucting VMPTRLD
2) Guest specifying eVMCS in VP assist page and executing
VMLAUNCH/VMRESUME.

Either way, vmcs12 should have revision_id of VMCS12_REVISION.
Which is not equal to eVMCS revision_id which specifies used
VersionNumber of eVMCS struct (e.g. KVM_EVMCS_VERSION).

Specifically, this causes an issue in restoring a nested VM state
because vmx_set_nested_state() verifies that vmcs12->revision_id
is equal to VMCS12_REVISION which was not true in case vmcs12
was populated from an eVMCS by vmx_get_nested_state() which calls
copy_enlightened_to_vmcs12().

Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PULL 1/4] s390/cio: make vfio_ccw_io_region static
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Sebastian Ott <sebott@linux.ibm.com>

Fix the following sparse warning:
drivers/s390/cio/vfio_ccw_drv.c:25:19: warning: symbol 'vfio_ccw_io_region'
was not declared. Should it be static?

Signed-off-by: Sebastian Ott <sebott@linux.ibm.com>
Message-Id: <alpine.LFD.2.21.1810151328570.1636@schleppi.aag-de.ibmmobiledemo.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [QEMU PATCH] i386/kvm: add support for Direct Mode for Hyper-V synthetic timers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 linux-headers/linux/kvm.h  |  1 +
 target/i386/cpu.c          |  1 +
 target/i386/cpu.h          |  1 +
 target/i386/hyperv-proto.h |  1 +
 target/i386/kvm.c          | 11 +++++++++++
 5 files changed, 15 insertions(+)

```
#### [PATCH RESEND] KVM: nSVM: Fix nested guest support for PAUSE filtering.
##### From: "Tambe, William" <William.Tambe@amd.com>

```c
Currently, the nested guest's PAUSE intercept intentions are not being
honored.  Instead, since the L0 hypervisor's pause_filter_count and
pause_filter_thresh values are still in place, these values are used
instead of those programmed in the VMCB by the L1 hypervisor.

To honor the desired PAUSE intercept support of the L1 hypervisor, the L0
hypervisor must use the PAUSE filtering fields of the L1 hypervisor. This
requires saving and restoring of both the L0 and L1 hypervisor's PAUSE
filtering fields.

Signed-off-by: William Tambe <william.tambe@amd.com>
---
 arch/x86/kvm/svm.c | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [kvm-unit-tests PATCH] x86/hyper-v: stimer_direct test
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/Makefile.common        |   3 +
 x86/hyperv.h               |   7 ++
 x86/hyperv_stimer_direct.c | 250 +++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg          |   6 +
 4 files changed, 266 insertions(+)
 create mode 100644 x86/hyperv_stimer_direct.c

```
#### [PATCH] reset: Add reset_control_get_count()
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
Currently the reset core has internal support for counting the number of
resets for a device described in DT.  Generalize this to devices using
lookup resets, and export it for public use.

This will be used by generic drivers that need to be sure a device is
controlled by a single, dedicated reset line (e.g. vfio-platform).

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
---
See https://lore.kernel.org/lkml/1539003437.11512.20.camel@pengutronix.de/
for the rationale to ensure a single, dedicated reset line.

 drivers/reset/core.c  | 41 +++++++++++++++++++++++++++++++++++++++++
 include/linux/reset.h |  7 +++++++
 2 files changed, 48 insertions(+)

```
#### [PATCH v5] vfio: platform: Add generic reset controller support
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
Vfio-platform requires dedicated reset support, provided either by ACPI,
or, on DT platforms, by a device-specific reset driver matching against
the device's compatible value.

On many SoCs, devices are connected to an SoC-internal reset controller.
If the reset hierarchy is described in DT using "resets" properties, or
in lookup tables in platform code, and devices have exactly one
dedicated reset each, such devices can be reset in a generic way through
the reset controller subsystem.  Hence add support for this, avoiding
the need to write device-specific reset drivers for each single device
on affected SoCs.

Devices that do require a more complex reset procedure can still provide
a device-specific reset driver, as that takes precedence.

Note that this functionality depends on CONFIG_RESET_CONTROLLER=y, and
becomes a no-op (as in: "No reset function found for device") if reset
controller support is disabled.

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
Reviewed-by: Philipp Zabel <p.zabel@pengutronix.de>
Reviewed-by: Simon Horman <horms+renesas@verge.net.au>
---
This depends on "[PATCH] reset: Add reset_control_get_count()"
(https://lore.kernel.org/lkml/20181113124744.7769-1-geert+renesas@glider.be/).

v5:
  - Use reset_control_get_exclusive() instead of rejected
    reset_control_get_dedicated(), as exclusive already implies a
    dedicated reset line,
  - Ensure the device has exactly one reset,

v4:
  - Add Reviewed-by,
  - Use new RFC reset_control_get_dedicated() instead of
    of_reset_control_get_exclusive(), to (a) make it more generic, and
    (b) make sure the reset returned is really a dedicated reset, and
    does not affect other devices,

v3:
  - Add Reviewed-by,
  - Merge similar checks in vfio_platform_has_reset(),

v2:
  - Don't store error values in vdev->reset_control,
  - Use of_reset_control_get_exclusive() instead of
    __of_reset_control_get(),
  - Improve description.
---
 drivers/vfio/platform/vfio_platform_common.c  | 29 +++++++++++++++++--
 drivers/vfio/platform/vfio_platform_private.h |  1 +
 2 files changed, 28 insertions(+), 2 deletions(-)

```
#### [PATCH] vfio/mdev: add static modifier to add_mdev_supported_type
##### From: Paolo Cretaro <paolocretaro@gmail.com>

```c
Set add_mdev_supported_type as static since it is only used within
mdev_sysfs.c.
This fixes -Wmissing-prototypes gcc warning.

Signed-off-by: Paolo Cretaro <paolocretaro@gmail.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/mdev/mdev_sysfs.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] x86/hyper-v: move synic/stimer control structures definitions to hyperv-tlfs.h
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
We implement Hyper-V SynIC and synthetic timers in KVM too so there's some
room for code sharing.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 69 ++++++++++++++++++++++++++++++
 drivers/hv/hv.c                    |  2 +-
 drivers/hv/hyperv_vmbus.h          | 68 -----------------------------
 3 files changed, 70 insertions(+), 69 deletions(-)

```
