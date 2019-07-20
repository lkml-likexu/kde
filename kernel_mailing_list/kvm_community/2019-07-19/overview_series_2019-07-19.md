#### [Bug 204209] kernel 5.2.1: "floating point exception" in qemu with kvm enabled
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

https://bugzilla.kernel.org/show_bug.cgi?id=204209

--- Comment #2 from anthony (antdev66@gmail.com) ---
I tested the patch indicated on https://lkml.org/lkml/2019/7/19/644 with simple
```
#### [PATCH] KVM: nVMX: do not use dangling shadow VMCS after guest reset
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
If a KVM guest is reset while running a nested guest, free_nested will
disable the shadow VMCS execution control in the vmcs01.  However,
on the next KVM_RUN vmx_vcpu_run would nevertheless try to sync
the VMCS12 to the shadow VMCS which has since been freed.

This causes a vmptrld of a NULL pointer on my machime, but Jan reports
the host to hang altogether.  Let's see how much this trivial patch fixes.

Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: VMX: dump VMCS on failed entry
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This is useful for debugging, and is ratelimited nowadays.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/5] objtool: KVM: x86: Check kvm_rebooting in kvm_spurious_fault()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Explicitly check kvm_reboot in kvm_spurious_fault() prior to invoking
BUG(), as opposed to assuming the caller has already done so.  Letting
kvm_spurious_fault() be called "directly" will allow VMX to better
optimize its low level assembly flows.

As a happy side effect, kvm_spurious_fault() no longer needs to be
marked as a dead end since it doesn't unconditionally BUG().

Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/x86.c              | 3 ++-
 tools/objtool/check.c           | 1 -
 3 files changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH 1/4] objtool: KVM: x86: Check kvm_rebooting in kvm_spurious_fault()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Explicitly check kvm_reboot in kvm_spurious_fault() prior to invoking
BUG(), as opposed to assuming the caller has already done so.  Letting
kvm_spurious_fault() be called "directly" will allow VMX to better
optimize its low level assembly flows.

As a happy side effect, kvm_spurious_fault() no longer needs to be
marked as a dead end since it doesn't unconditionally BUG().

Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c    | 3 ++-
 tools/objtool/check.c | 1 -
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: WARN on invalid vmptrld or vmclear
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/ops.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: nVMX: do not use dangling shadow VMCS after guest reset
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
If a KVM guest is reset while running a nested guest, free_nested will
disable the shadow VMCS execution control in the vmcs01.  However,
on the next KVM_RUN vmx_vcpu_run would nevertheless try to sync
the VMCS12 to the shadow VMCS which has since been freed.

This causes a vmptrld of a NULL pointer on my machime, but Jan reports
the host to hang altogether.  Let's see how much this trivial patch fixes.

Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by:  Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH v3 4/9] x86/mm/tlb: Flush remote and local TLBs concurrently
##### From: Nadav Amit <namit@vmware.com>

```c
To improve TLB shootdown performance, flush the remote and local TLBs
concurrently. Introduce flush_tlb_multi() that does so. Introduce
paravirtual versions of flush_tlb_multi() for KVM, Xen and hyper-v (Xen
and hyper-v are only compile-tested).

While the updated smp infrastructure is capable of running a function on
a single local core, it is not optimized for this case. The multiple
function calls and the indirect branch introduce some overhead, and
might make local TLB flushes slower than they were before the recent
changes.

Before calling the SMP infrastructure, check if only a local TLB flush
is needed to restore the lost performance in this common case. This
requires to check mm_cpumask() one more time, but unless this mask is
updated very frequently, this should impact performance negatively.

Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: x86@kernel.org
Cc: Juergen Gross <jgross@suse.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org
Cc: xen-devel@lists.xenproject.org
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 arch/x86/hyperv/mmu.c                 | 10 +++---
 arch/x86/include/asm/paravirt.h       |  6 ++--
 arch/x86/include/asm/paravirt_types.h |  4 +--
 arch/x86/include/asm/tlbflush.h       |  8 ++---
 arch/x86/include/asm/trace/hyperv.h   |  2 +-
 arch/x86/kernel/kvm.c                 | 11 +++++--
 arch/x86/kernel/paravirt.c            |  2 +-
 arch/x86/mm/tlb.c                     | 47 ++++++++++++++++++---------
 arch/x86/xen/mmu_pv.c                 | 11 +++----
 include/trace/events/xen.h            |  2 +-
 10 files changed, 62 insertions(+), 41 deletions(-)

```
