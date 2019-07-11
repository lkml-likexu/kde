#### [PATCH v3 01/11] KVM: SVM: Add KVM_SEV SEND_START commandThread-Topic: [PATCH v3 01/11] KVM: SVM: Add KVM_SEV SEND_START command
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 .../virtual/kvm/amd-memory-encryption.rst     |  27 +++++
 arch/x86/kvm/svm.c                            | 105 ++++++++++++++++++
 include/uapi/linux/kvm.h                      |  12 ++
 3 files changed, 144 insertions(+)

```
#### [PATCH v3 1/3] Documentation: virtual: Convert paravirt_ops.txt to .rst
##### From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

```c
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Convert paravirt_opts.txt to .rst format to be able to be parsed by
sphinx.

Made some minor spacing and formatting corrections to make defintions
much more clear and easy to read. Added default kernel license to the
document.

Signed-off-by: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
---
 Changes since v3:
 none
 Changes since v2:
 none
 Changes since v1:
 + Converted doc to .rst format
 
 .../{paravirt_ops.txt => paravirt_ops.rst}    | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)
 rename Documentation/virtual/{paravirt_ops.txt => paravirt_ops.rst} (65%)

diff --git a/Documentation/virtual/paravirt_ops.txt b/Documentation/virtual/paravirt_ops.rst
similarity index 65%
rename from Documentation/virtual/paravirt_ops.txt
```
#### [PATCH] KVM: Properly check if "page" is valid in kvm_vcpu_unmap
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
The field "page" is initialized to KVM_UNMAPPED_PAGE when it is not used
(i.e. when the memory lives outside kernel control). So this check will
always end up using kunmap even for memremap regions.

Fixes: e45adf665a53 ("KVM: Introduce a new guest mapping API")
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] arm: Add PL031 test
##### From: Alexander Graf <graf@amazon.com>

```c
This patch adds a unit test for the PL031 RTC that is used in the virt machine.
It just pokes basic functionality. I've mostly written it to familiarize myself
with the device, but I suppose having the test around does not hurt, as it also
exercises the GIC SPI interrupt path.

Signed-off-by: Alexander Graf <graf@amazon.com>
---
 arm/Makefile.common |   1 +
 arm/pl031.c         | 227 ++++++++++++++++++++++++++++++++++++++++++++
 lib/arm/asm/gic.h   |   1 +
 3 files changed, 229 insertions(+)
 create mode 100644 arm/pl031.c

```
#### [PATCH] KVM: x86: Unconditionally enable irqs in guest context
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
On VMX, KVM currently does not re-enable irqs until after it has exited
the guest context.  As a result, a tick that fires in the window between
VM-Exit and guest_exit_irqoff() will be accounted as system time.  While
said window is relatively small, it's large enough to be problematic in
some configurations, e.g. if VM-Exits are consistently occurring a hair
earlier than the tick irq.

Intentionally toggle irqs back off so that guest_exit_irqoff() can be
used in lieu of guest_exit() in order to avoid the save/restore of flags
in guest_exit().  On my Haswell system, "nop; cli; sti" is ~6 cycles,
versus ~28 cycles for "pushf; pop <reg>; cli; push <reg>; popf".

Fixes: f2485b3e0c6c0 ("KVM: x86: use guest_exit_irqoff")
Reported-by: Wei Yang <w90p710@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c | 10 +---------
 arch/x86/kvm/x86.c | 11 +++++++++++
 2 files changed, 12 insertions(+), 9 deletions(-)

```
#### [RFC][Patch v11 1/2] mm: page_hinting: core infrastructure
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch introduces the core infrastructure for free page hinting in
virtual environments. It enables the kernel to track the free pages which
can be reported to its hypervisor so that the hypervisor could
free and reuse that memory as per its requirement.

While the pages are getting processed in the hypervisor (e.g.,
via MADV_FREE), the guest must not use them, otherwise, data loss
would be possible. To avoid such a situation, these pages are
temporarily removed from the buddy. The amount of pages removed
temporarily from the buddy is governed by the backend(virtio-balloon
in our case).

To efficiently identify free pages that can to be hinted to the
hypervisor, bitmaps in a coarse granularity are used. Only fairly big
chunks are reported to the hypervisor - especially, to not break up THP
in the hypervisor - "MAX_ORDER - 2" on x86, and to save space. The bits
in the bitmap are an indication whether a page *might* be free, not a
guarantee. A new hook after buddy merging sets the bits.

Bitmaps are stored per zone, protected by the zone lock. A workqueue
asynchronously processes the bitmaps, trying to isolate and report pages
that are still free. The backend (virtio-balloon) is responsible for
reporting these batched pages to the host synchronously. Once reporting/
freeing is complete, isolated pages are returned back to the buddy.

There are still various things to look into (e.g., memory hotplug, more
efficient locking, possible races when disabling).

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 include/linux/page_hinting.h |  45 +++++++
 mm/Kconfig                   |   6 +
 mm/Makefile                  |   1 +
 mm/page_alloc.c              |  18 +--
 mm/page_hinting.c            | 250 +++++++++++++++++++++++++++++++++++
 5 files changed, 312 insertions(+), 8 deletions(-)
 create mode 100644 include/linux/page_hinting.h
 create mode 100644 mm/page_hinting.c

diff --git a/include/linux/page_hinting.h b/include/linux/page_hinting.h
new file mode 100644
index 000000000000..4900feb796f9
--- /dev/null
+++ b/include/linux/page_hinting.h
@@ -0,0 +1,45 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _LINUX_PAGE_HINTING_H
+#define _LINUX_PAGE_HINTING_H
+
+/*
+ * Minimum page order required for a page to be hinted to the host.
+ */
+#define PAGE_HINTING_MIN_ORDER		(MAX_ORDER - 2)
+
+/*
+ * struct page_hinting_config: holds the information supplied by the balloon
+ * device to page hinting.
+ * @hint_pages:		Callback which reports the isolated pages
+ *			synchornously to the host.
+ * @max_pages:		Maxmimum pages that are going to be hinted to the host
+ *			at a time of granularity >= PAGE_HINTING_MIN_ORDER.
+ */
+struct page_hinting_config {
+	void (*hint_pages)(struct list_head *list);
+	int max_pages;
+};
+
+extern int __isolate_free_page(struct page *page, unsigned int order);
+extern void __free_one_page(struct page *page, unsigned long pfn,
+			    struct zone *zone, unsigned int order,
+			    int migratetype, bool hint);
+#ifdef CONFIG_PAGE_HINTING
+void page_hinting_enqueue(struct page *page, int order);
+int page_hinting_enable(const struct page_hinting_config *conf);
+void page_hinting_disable(void);
+#else
+static inline void page_hinting_enqueue(struct page *page, int order)
+{
+}
+
+static inline int page_hinting_enable(const struct page_hinting_config *conf)
+{
+	return -EOPNOTSUPP;
+}
+
+static inline void page_hinting_disable(void)
+{
+}
+#endif
+#endif /* _LINUX_PAGE_HINTING_H */
```
#### [QEMU Patch] virtio-baloon: Support for page hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Enables QEMU to perform madvise free on the memory range reported
by the vm.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 hw/virtio/trace-events                        |  1 +
 hw/virtio/virtio-balloon.c                    | 59 +++++++++++++++++++
 include/hw/virtio/virtio-balloon.h            |  2 +-
 include/qemu/osdep.h                          |  7 +++
 .../standard-headers/linux/virtio_balloon.h   |  1 +
 5 files changed, 69 insertions(+), 1 deletion(-)

```
#### [PATCH RESEND v2] target-i386: adds PV_SCHED_YIELD CPUID feature bit
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Adds PV_SCHED_YIELD CPUID feature bit.

Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note: kvm part is merged
v1 -> v2:
 * use bit 13 instead of bit 12 since bit 12 has user now

 target/i386/cpu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] target-i386: adds PV_SCHED_YIELD CPUID feature bit
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Adds PV_SCHED_YIELD CPUID feature bit.

Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note: kvm part is merged
v1 -> v2:
 * use bit 13 instead of bit 12 since bit 12 has user now

 target/i386/cpu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] kvm: x86: Fix -Wmissing-prototypes warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We get a warning when build kernel W=1:

arch/x86/kvm/../../../virt/kvm/eventfd.c:48:1: warning: no previous prototype for ‘kvm_arch_irqfd_allowed’ [-Wmissing-prototypes]
 kvm_arch_irqfd_allowed(struct kvm *kvm, struct kvm_irqfd *args)
 ^

The reason is kvm_arch_irqfd_allowed() is declared in arch/x86/kvm/irq.h,
which is not included by eventfd.c. Considering kvm_arch_irqfd_allowed()
is a weakly defined function in eventfd.c, remove the declaration to
kvm_host.h can fix this.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v2: add comments about the reason.
---
 arch/x86/kvm/irq.h       | 1 -
 include/linux/kvm_host.h | 1 +
 2 files changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] mdev: Send uevents around parent device registrationFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
This allows udev to trigger rules when a parent device is registered
or unregistered from mdev.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: Kirti Wankhede <kwankhede@nvidia.com>
---

v3: Add Connie's R-b
    Add comment clarifying expected device requirements for unreg

 drivers/vfio/mdev/mdev_core.c |    9 +++++++++
 1 file changed, 9 insertions(+)

```
