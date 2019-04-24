#### [PATCH v16 01/10] hw/arm/virt: Add RAS platform version for migration
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Support this feature since version 4.1, disable it by
default in the old version.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
 hw/arm/virt.c         | 6 ++++++
 include/hw/arm/virt.h | 1 +
 2 files changed, 7 insertions(+)

```
#### [RFC KVM 01/27] kernel: Export memory-management symbols required for KVM address space isolation
##### From: Alexandre Chartre <alexandre.chartre@oracle.com>

```c
From: Liran Alon <liran.alon@oracle.com>

Export symbols needed to create, manage, populate and switch
a mm from a kernel module (kvm in this case).

This is a hacky way for now to start.
This should be changed to some suitable memory-management API.

Signed-off-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Alexandre Chartre <alexandre.chartre@oracle.com>
---
 arch/x86/kernel/ldt.c |    1 +
 arch/x86/mm/tlb.c     |    3 ++-
 mm/memory.c           |    5 +++++
 3 files changed, 8 insertions(+), 1 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Make sure to load LPID for radix VCPUs
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Commit 70ea13f6e609 ("KVM: PPC: Book3S HV: Flush TLB on secondary radix
threads", 2019-04-29) aimed to make radix guests that are using the
real-mode entry path load the LPID register and flush the TLB in the
same place where those things are done for HPT guests.  However, it
omitted to remove a branch which branches around that code for radix
guests.  The result is that with indep_thread_mode = N, radix guests
don't run correctly.  (With indep_threads_mode = Y, which is the
default, radix guests use a different entry path.)

This removes the offending branch, and also the load and compare that
the branch depends on, since the cr7 setting is now unused.

Reported-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Fixes: 70ea13f6e609 ("KVM: PPC: Book3S HV: Flush TLB on secondary radix threads")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 6 ------
 1 file changed, 6 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Halt on exit
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
In some cases, shutdown through the test device and Bochs might fail.
Just hang in a loop that executes halt in such cases. Remove the
__builtin_unreachable() as it is not needed anymore.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/io.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: X86: Enable IA32_MSIC_ENABLE MONITOR bit when exposing mwait/monitor
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

MSR IA32_MSIC_ENABLE bit 18, according to SDM:

 | When this bit is set to 0, the MONITOR feature flag is not set (CPUID.01H:ECX[bit 3] = 0). 
 | This indicates that MONITOR/MWAIT are not supported.
 | 
 | Software attempts to execute MONITOR/MWAIT will cause #UD when this bit is 0.
 | 
 | When this bit is set to 1 (default), MONITOR/MWAIT are supported (CPUID.01H:ECX[bit 3] = 1). 

This bit should be set to 1, if BIOS enables MONITOR/MWAIT support on host and 
we intend to expose mwait/monitor to the guest.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 16 +++++++++-------
 1 file changed, 9 insertions(+), 7 deletions(-)

```
#### [PATCH net] vhost: don't use kmap() to log dirty pages
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost log dirty pages directly to a userspace bitmap through GUP and
kmap_atomic() since kernel doesn't have a set_bit_to_user()
helper. This will cause issues for the arch that has virtually tagged
caches. The way to fix is to keep using userspace virtual
address. Fortunately, futex has arch_futex_atomic_op_inuser() which
could be used for setting a bit to user.

Note there're several cases that futex helper can fail e.g a page
fault or the arch that doesn't have the support. For those cases, a
simplified get_user()/put_user() pair protected by a global mutex is
provided as a fallback. The fallback may lead false positive that
userspace may see more dirty pages.

Cc: Christoph Hellwig <hch@infradead.org>
Cc: James Bottomley <James.Bottomley@HansenPartnership.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Darren Hart <dvhart@infradead.org>
Fixes: 3a4d5c94e9593 ("vhost_net: a kernel-level virtio server")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
Changes from RFC V2:
- drop GUP and provide get_user()/put_user() fallbacks
- round down log_base
Changes from RFC V1:
- switch to use arch_futex_atomic_op_inuser()
---
 drivers/vhost/vhost.c | 54 ++++++++++++++++++++++++++++-----------------------
 1 file changed, 30 insertions(+), 24 deletions(-)

```
#### [RFC PATCH V2] kvm: arm64: export memory error recovery capability to user space
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
When user space do memory recovery, it will check whether KVM and
guest support the error recovery, only when both of them support,
user space will do the error recovery. This patch exports this
capability of KVM to user space.

Cc: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
v1->v2:
1. check whether host support memory failure instead of RAS capability
   https://patchwork.kernel.org/patch/10730827/

v1:
1. User space needs to check this capability of host is suggested by Peter[1],
this patch as RFC tag because user space patches are still under review,
so this kernel patch is firstly sent out for review.

[1]: https://patchwork.codeaurora.org/patch/652261/
---
 Documentation/virtual/kvm/api.txt | 9 +++++++++
 arch/arm64/kvm/reset.c            | 3 +++
 include/uapi/linux/kvm.h          | 1 +
 3 files changed, 13 insertions(+)

```
