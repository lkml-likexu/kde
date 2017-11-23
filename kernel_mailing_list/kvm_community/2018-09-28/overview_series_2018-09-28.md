#### [kvm-unit-tests PATCH 1/4] x86: Declare local functions as "static" and specify argument types
##### From: Thomas Huth <thuth@redhat.com>

```c
This makes the code compilable with the compiler flags -Wstrict-prototypes
and -Wmissing-prototypes.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 x86/cmpxchg8b.c | 2 +-
 x86/tsc.c       | 4 ++--
 x86/umip.c      | 6 +++---
 x86/vmx.c       | 6 +++---
 4 files changed, 9 insertions(+), 9 deletions(-)

```
#### [FIXUP v11] fixup! s390: vfio-ap: implement mediated device open callback
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

```c
From: Tony Krowiak <akrowiak@linux.ibm.com>

Fixes case statement in vfio_ap_mdev_copy_masks() function in
vfio-ap-ops.c.
---
 drivers/s390/crypto/vfio_ap_ops.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [FIXUP v9] fixup! fixup! s390: doc: detailed specifications for AP virtualization
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

```c
From: Tony Krowiak <akrowiak@linux.ibm.com>

Removes extraneous text from third line below:

+05          CEX5A Accelerator
+05.0047     CEX5A Accelerator
+05.00ff     CEX5A Accelerator (5,4), (5,171), (6,4), (6,171),
                               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
---
 Documentation/s390/vfio-ap.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: LAPIC: Tune lapic_timer_advance_ns automatically
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

In cloud environment, lapic_timer_advance_ns is needed to be tuned for every CPU 
generations, and every host kernel versions(the kvm-unit-tests/tscdeadline_latency.flat 
is 5700 cycles for upstream kernel and 9600 cycles for our 3.10 product kernel, 
both preemption_timer=N, Skylake server).

This patch adds the capability to automatically tune lapic_timer_advance_ns
step by step, the initial value is 1000ns as d0659d946be05 (KVM: x86: add 
option to advance tscdeadline hrtimer expiration) recommended, it will be 
reduced when it is too early, and increased when it is too late. The guest_tsc 
and tsc_deadline are hard to equal, so we assume we are done when the delta 
is within a small scope e.g. 100 cycles. This patch reduces latency 
(kvm-unit-tests/tscdeadline_latency, busy waits, preemption_timer enabled)
from ~2600 cyles to ~1200 cyles on our Skylake server.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 7 +++++++
 arch/x86/kvm/x86.c   | 2 +-
 2 files changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/33] KVM: PPC: Book3S: Simplify external interrupt handling
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Currently we use two bits in the vcpu pending_exceptions bitmap to
indicate that an external interrupt is pending for the guest, one
for "one-shot" interrupts that are cleared when delivered, and one
for interrupts that persist until cleared by an explicit action of
the OS (e.g. an acknowledge to an interrupt controller).  The
BOOK3S_IRQPRIO_EXTERNAL bit is used for one-shot interrupt requests
and BOOK3S_IRQPRIO_EXTERNAL_LEVEL is used for persisting interrupts.

In practice BOOK3S_IRQPRIO_EXTERNAL never gets used, because our
Book3S platforms generally, and pseries in particular, expect
external interrupt requests to persist until they are acknowledged
at the interrupt controller.  That combined with the confusion
introduced by having two bits for what is essentially the same thing
makes it attractive to simplify things by only using one bit.  This
patch does that.

With this patch there is only BOOK3S_IRQPRIO_EXTERNAL, and by default
it has the semantics of a persisting interrupt.  In order to avoid
breaking the ABI, we introduce a new "external_oneshot" flag which
preserves the behaviour of the KVM_INTERRUPT ioctl with the
KVM_INTERRUPT_SET argument.

Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/include/asm/kvm_asm.h             |  4 +--
 arch/powerpc/include/asm/kvm_host.h            |  1 +
 arch/powerpc/kvm/book3s.c                      | 43 ++++++++++++++++++++------
 arch/powerpc/kvm/book3s_hv_rm_xics.c           |  5 ++-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S        |  4 +--
 arch/powerpc/kvm/book3s_pr.c                   |  1 -
 arch/powerpc/kvm/book3s_xics.c                 | 11 +++----
 arch/powerpc/kvm/book3s_xive_template.c        |  2 +-
 arch/powerpc/kvm/trace_book3s.h                |  1 -
 tools/perf/arch/powerpc/util/book3s_hv_exits.h |  1 -
 10 files changed, 44 insertions(+), 29 deletions(-)

```
#### [PATCH] KVM/VMX: Remve unused function is_external_interrupt().Thread-Topic: [PATCH] KVM/VMX: Remve unused function is_external_interrupt().
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
is_external_interrupt() is not used now and so remove it.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/kvm/vmx.c | 6 ------
 1 file changed, 6 deletions(-)

```
#### [PATCH] KVM: x86: move definition PT_MAX_HUGEPAGE_LEVEL and KVM_NR_PAGE_SIZES together
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Currently, there are two definitions related to huge page, but a little bit
far from each other and seems loosely connected:

 * KVM_NR_PAGE_SIZES defines the number of different size a page could map
 * PT_MAX_HUGEPAGE_LEVEL means the maximum level of huge page

The number of different size a page could map equals the maximum level
of huge page, which is implied by current definition.

While current implementation may not be kind to readers and further
developers:

 * KVM_NR_PAGE_SIZES looks like a stand alone definition at first sight
 * in case we need to support more level, two places need to change

This patch tries to make these two definition more close, so that reader
and developer would feel more comfortable to manipulate.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/include/asm/kvm_host.h | 10 +++++++++-
 arch/x86/kvm/mmu.h              |  5 -----
 2 files changed, 9 insertions(+), 6 deletions(-)

```
#### [PATCH]  kvm/x86 : set meaningful return value
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

kvm_irq_delivery_to_apic_fast()-->
    kvm_apic_map_get_dest_lapic()-->
        kvm_apic_disabled_lapic_found()
kvm_apic_map_get_dest_lapic return with bitmap==0 and dst[i]==NULL,
then (*r == -1) will be returned to qemu and "KVM: injection failed,
MSI lost(Operation not permitted)" will be recorded in qemu log. The
output is puzzling.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
