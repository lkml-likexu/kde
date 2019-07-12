#### [RFC v2 01/26] mm/x86: Introduce kernel address space isolation
##### From: Alexandre Chartre <alexandre.chartre@oracle.com>

```c
Introduce core functions and structures for implementing Address Space
Isolation (ASI). Kernel address space isolation provides the ability to
run some kernel code with a reduced kernel address space.

An address space isolation is defined with a struct asi structure which
has its own page-table. While, for now, this page-table is empty, it
will eventually be possible to populate it so that it is much smaller
than the full kernel page-table.

Isolation is entered by calling asi_enter() which switches the kernel
page-table to the address space isolation page-table. Isolation is then
exited by calling asi_exit() which switches the page-table back to the
kernel page-table.

Signed-off-by: Alexandre Chartre <alexandre.chartre@oracle.com>
---
 arch/x86/include/asm/asi.h |   41 ++++++++++++
 arch/x86/mm/Makefile       |    2 +
 arch/x86/mm/asi.c          |  152 ++++++++++++++++++++++++++++++++++++++++++++
 security/Kconfig           |   10 +++
 4 files changed, 205 insertions(+), 0 deletions(-)
 create mode 100644 arch/x86/include/asm/asi.h
 create mode 100644 arch/x86/mm/asi.c

diff --git a/arch/x86/include/asm/asi.h b/arch/x86/include/asm/asi.h
new file mode 100644
index 0000000..8a13f73
--- /dev/null
+++ b/arch/x86/include/asm/asi.h
@@ -0,0 +1,41 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef ARCH_X86_MM_ASI_H
+#define ARCH_X86_MM_ASI_H
+
+#ifdef CONFIG_ADDRESS_SPACE_ISOLATION
+
+#include <linux/spinlock.h>
+#include <asm/pgtable.h>
+
+struct asi {
+	spinlock_t		lock;		/* protect all attributes */
+	pgd_t			*pgd;		/* ASI page-table */
+};
+
+/*
+ * An ASI session maintains the state of address state isolation on a
+ * cpu. There is one ASI session per cpu. There is no lock to protect
+ * members of the asi_session structure as each cpu is managing its
+ * own ASI session.
+ */
+
+enum asi_session_state {
+	ASI_SESSION_STATE_INACTIVE,	/* no address space isolation */
+	ASI_SESSION_STATE_ACTIVE,	/* address space isolation is active */
+};
+
+struct asi_session {
+	struct asi		*asi;		/* ASI for this session */
+	enum asi_session_state	state;		/* state of ASI session */
+	unsigned long		original_cr3;	/* cr3 before entering ASI */
+	struct task_struct	*task;		/* task during isolation */
+} __aligned(PAGE_SIZE);
+
+extern struct asi *asi_create(void);
+extern void asi_destroy(struct asi *asi);
+extern int asi_enter(struct asi *asi);
+extern void asi_exit(struct asi *asi);
+
+#endif	/* CONFIG_ADDRESS_SPACE_ISOLATION */
+
+#endif
```
#### [PATCH v3 1/2] KVM: nVMX: add tracepoint for failed nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Debugging a failed VM-Enter is often like searching for a needle in a
haystack, e.g. there are over 80 consistency checks that funnel into
the "invalid control field" error code.  One way to expedite debug is
to run the buggy code as an L1 guest under KVM (and pray that the
failing check is detected by KVM).  However, extracting useful debug
information out of L0 KVM requires attaching a debugger to KVM and/or
modifying the source, e.g. to log which check is failing.

Make life a little less painful for VMM developers and add a tracepoint
for failed VM-Enter consistency checks.  Ideally the tracepoint would
capture both what check failed and precisely why it failed, but logging
why a checked failed is difficult to do in a generic tracepoint without
resorting to invasive techniques, e.g. generating a custom string on
failure.  That being said, for the vast majority of VM-Enter failures
the most difficult step is figuring out exactly what to look at, e.g.
figuring out which bit was incorrectly set in a control field is usually
not too painful once the guilty field as been identified.

To reach a happy medium between precision and ease of use, simply log
the code that detected a failed check, using a macro to execute the
check and log the trace event on failure.  This approach enables tracing
arbitrary code, e.g. it's not limited to function calls or specific
formats of checks, and the changes to the existing code are minimally
invasive.  A macro with a two-character name is desirable as usage of
the macro doesn't result in overly long lines or confusing alignment,
while still retaining some amount of readability.  I.e. a one-character
name is a little too terse, and a three-character name results in the
contents being passed to the macro aligning with an indented line when
the macro is used an in if-statement, e.g.:

        if (VCC(nested_vmx_check_long_line_one(...) &&
                nested_vmx_check_long_line_two(...)))
                return -EINVAL;

And that is the story of how the CC(), a.k.a. Consistency Check, macro
got its name.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/trace.h      |  19 +++
 arch/x86/kvm/vmx/nested.c | 256 ++++++++++++++++++++------------------
 arch/x86/kvm/x86.c        |   1 +
 3 files changed, 153 insertions(+), 123 deletions(-)

```
#### [kvm-unit-tests PATCH] tscdeadline_latency: Check condition first before loop
##### From: Peter Xu <zhexu@redhat.com>

```c
This patch fixes a tscdeadline_latency hang when specifying a very
small breakmax value.  It's easily reproduced on my host with
parameters like "200000 10000 10" (set breakmax to 10 TSC clocks).

The problem is test_tsc_deadline_timer() can be very slow because
we've got printf() in there.  So when reach the main loop we might
have already triggered the IRQ handler for multiple times and we might
have triggered the hitmax condition which will turn IRQ off.  Then
with no IRQ that first HLT instruction can last forever.

Fix this by simply checking the condition first in the loop.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 x86/tscdeadline_latency.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL 01/19] migration: fix multifd_recv event typo
##### From: Juan Quintela <quintela@redhat.com>

```c
It uses num in multifd_send().  Make it coherent.

Signed-off-by: Juan Quintela <quintela@redhat.com>
Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Reviewed-by: Wei Yang <richardw.yang@linux.intel.com>
Signed-off-by: Juan Quintela <quintela@redhat.com>
---
 migration/trace-events | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v9 01/14] iommu: Introduce attach/detach_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on the guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/Intel terminology) while the host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to set/unset the pasid table information.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/iommu/iommu.c      | 19 ++++++++++++++
 include/linux/iommu.h      | 18 ++++++++++++++
 include/uapi/linux/iommu.h | 51 ++++++++++++++++++++++++++++++++++++++
 3 files changed, 88 insertions(+)

```
#### [PATCH v9 01/11] vfio: VFIO_IOMMU_SET_PASID_TABLE
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: "Liu, Yi L" <yi.l.liu@linux.intel.com>

This patch adds an VFIO_IOMMU_SET_PASID_TABLE ioctl
which aims to pass the virtual iommu guest configuration
to the host. This latter takes the form of the so-called
PASID table.

Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
v8 -> v9:
- Merge VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE into a single
  VFIO_IOMMU_SET_PASID_TABLE ioctl.

v6 -> v7:
- add a comment related to VFIO_IOMMU_DETACH_PASID_TABLE

v3 -> v4:
- restore ATTACH/DETACH
- add unwind on failure

v2 -> v3:
- s/BIND_PASID_TABLE/SET_PASID_TABLE

v1 -> v2:
- s/BIND_GUEST_STAGE/BIND_PASID_TABLE
- remove the struct device arg
---
 drivers/vfio/vfio_iommu_type1.c | 56 +++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h       | 19 +++++++++++
 2 files changed, 75 insertions(+)

```
#### [PATCH v3 1/5] vfio-ccw: Fix misleading comment when setting orb.cmd.c64
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
The comment is misleading because it tells us that
we should set orb.cmd.c64 before calling ccwchain_calc_length,
otherwise the function ccwchain_calc_length would return an
error. This is not completely accurate.

We want to allow an orb without cmd.c64, and this is fine
as long as the channel program does not use IDALs. But we do
want to reject any channel program that uses IDALs and does
not set the flag, which is what we do in ccwchain_calc_length.

After we have done the ccw processing, we need to set cmd.c64,
as we use IDALs for all translated channel programs.

Also for better code readability let's move the setting of
cmd.c64 within the non error path.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH v1] KVM: x86: expose AVX512_BF16 feature to guest
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
AVX512 BFLOAT16 instructions support 16-bit BFLOAT16 floating-point
format (BF16) for deep learning optimization.

Intel adds AVX512 BFLOAT16 feature in CooperLake, which is CPUID.7.1.EAX[5].

Detailed information of the CPUID bit can be found here,
https://software.intel.com/sites/default/files/managed/c5/15/\
architecture-instruction-set-extensions-programming-reference.pdf.

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---

This patch depends on kernel patch https://lkml.org/lkml/2019/6/19/912
and Paolo's patch set https://lkml.org/lkml/2019/7/4/468.

 arch/x86/kvm/cpuid.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: PMU Event FilterTo: Wei Wang <wei.w.wang@intel.com>,
##### From: Eric Hankland <ehankland@google.com>

```c
- Add a VM ioctl that can control which events the guest can monitor.

Signed-off-by: ehankland <ehankland@google.com>
---
Changes since v1:
-Moved to a vm ioctl rather than a vcpu one
-Changed from a whitelist to a configurable filter which can either be
white or black
-Only restrict GP counters since fixed counters require extra handling
and they can be disabled by setting the guest cpuid (though only by
setting the number - they can't be disabled individually)
---
 Documentation/virtual/kvm/api.txt | 25 +++++++++++++
 arch/x86/include/asm/kvm_host.h   |  2 +
 arch/x86/include/uapi/asm/kvm.h   | 10 +++++
 arch/x86/kvm/pmu.c                | 61 +++++++++++++++++++++++++++++++
 arch/x86/kvm/pmu.h                |  1 +
 arch/x86/kvm/x86.c                |  6 +++
 include/uapi/linux/kvm.h          |  3 ++
 7 files changed, 108 insertions(+)

 #define KVM_CREATE_DEVICE        _IOWR(KVMIO,  0xe0, struct kvm_create_device)

diff --git a/Documentation/virtual/kvm/api.txt
```
#### [PATCH] vfio: platform: reset: add support for XHCI reset hook
##### From: Gregory CLEMENT <gregory.clement@bootlin.com>

```c
The VFIO reset hook is called every time a platform device is passed
to a guest or removed from a guest.

When the XHCI device is unbound from the host, the host driver
disables the XHCI clocks/phys/regulators so when the device is passed
to the guest it becomes dis-functional.

This initial implementation uses the VFIO reset hook to enable the
XHCI clocks/phys on behalf of the guest.

Ported from Marvell LSP code originally written by Yehuda Yitschak

Signed-off-by: Gregory CLEMENT <gregory.clement@bootlin.com>
---
 drivers/vfio/platform/reset/Kconfig           |  8 +++
 drivers/vfio/platform/reset/Makefile          |  2 +
 .../vfio/platform/reset/vfio_platform_xhci.c  | 60 +++++++++++++++++++
 3 files changed, 70 insertions(+)
 create mode 100644 drivers/vfio/platform/reset/vfio_platform_xhci.c

```
