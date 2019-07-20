

#### [PATCH v3 0/9] x86: Concurrent TLB flushes
##### From: Nadav Amit <namit@vmware.com>

```c

[ Cover-letter is identical to v2, including benchmark results,
  excluding the change log. ] 

Currently, local and remote TLB flushes are not performed concurrently,
which introduces unnecessary overhead - each INVLPG can take 100s of
cycles. This patch-set allows TLB flushes to be run concurrently: first
request the remote CPUs to initiate the flush, then run it locally, and
finally wait for the remote CPUs to finish their work.

In addition, there are various small optimizations to avoid unwarranted
false-sharing and atomic operations.

The proposed changes should also improve the performance of other
invocations of on_each_cpu(). Hopefully, no one has relied on this
behavior of on_each_cpu() that invoked functions first remotely and only
then locally [Peter says he remembers someone might do so, but without
further information it is hard to know how to address it].

Running sysbench on dax/ext4 w/emulated-pmem, write-cache disabled on
2-socket, 48-logical-cores (24+SMT) Haswell-X, 5 repetitions:

 sysbench fileio --file-total-size=3G --file-test-mode=rndwr \
  --file-io-mode=mmap --threads=X --file-fsync-mode=fdatasync run

  Th.   tip-jun28 avg (stdev)   +patch-set avg (stdev)  change
  ---   ---------------------   ----------------------  ------
  1     1267765 (14146)         1299253 (5715)          +2.4%
  2     1734644 (11936)         1799225 (19577)         +3.7%
  4     2821268 (41184)         2919132 (40149)         +3.4%
  8     4171652 (31243)         4376925 (65416)         +4.9%
  16    5590729 (24160)         5829866 (8127)          +4.2%
  24    6250212 (24481)         6522303 (28044)         +4.3%
  32    3994314 (26606)         4077543 (10685)         +2.0%
  48    4345177 (28091)         4417821 (41337)         +1.6%

(Note that on configurations with up to 24 threads numactl was used to
set all threads on socket 1, which explains the drop in performance when
going to 32 threads).

Running the same benchmark with security mitigations disabled (PTI,
Spectre, MDS):

  Th.   tip-jun28 avg (stdev)   +patch-set avg (stdev)  change
  ---   ---------------------   ----------------------  ------
  1     1598896 (5174)          1607903 (4091)          +0.5%
  2     2109472 (17827)         2224726 (4372)          +5.4%
  4     3448587 (11952)         3668551 (30219)         +6.3%
  8     5425778 (29641)         5606266 (33519)         +3.3%
  16    6931232 (34677)         7054052 (27873)         +1.7%
  24    7612473 (23482)         7783138 (13871)         +2.2%
  32    4296274 (18029)         4283279 (32323)         -0.3%
  48    4770029 (35541)         4764760 (13575)         -0.1%

Presumably, PTI requires two invalidations of each mapping, which allows
to get higher benefits from concurrency when PTI is on. At the same
time, when mitigations are on, other overheads reduce the potential
speedup.

I tried to reduce the size of the code of the main patch, which required
restructuring of the series.

v2 -> v3:
* Open-code the remote/local-flush decision code [Andy]
* Fix hyper-v, Xen implementations [Andrew]
* Fix redundant TLB flushes.

v1 -> v2:
* Removing the patches that Thomas took [tglx]
* Adding hyper-v, Xen compile-tested implementations [Dave]
* Removing UV [Andy]
* Adding lazy optimization, removing inline keyword [Dave]
* Restructuring patch-set

RFCv2 -> v1:
* Fix comment on flush_tlb_multi [Juergen]
* Removing async invalidation optimizations [Andy]
* Adding KVM support [Paolo]

Cc: Andy Lutomirski <luto@kernel.org>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Cc: Juergen Gross <jgross@suse.com>
Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Rik van Riel <riel@surriel.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: x86@kernel.org
Cc: xen-devel@lists.xenproject.org

Nadav Amit (9):
  smp: Run functions concurrently in smp_call_function_many()
  x86/mm/tlb: Remove reason as argument for flush_tlb_func_local()
  x86/mm/tlb: Open-code on_each_cpu_cond_mask() for tlb_is_not_lazy()
  x86/mm/tlb: Flush remote and local TLBs concurrently
  x86/mm/tlb: Privatize cpu_tlbstate
  x86/mm/tlb: Do not make is_lazy dirty for no reason
  cpumask: Mark functions as pure
  x86/mm/tlb: Remove UV special case
  x86/mm/tlb: Remove unnecessary uses of the inline keyword

 arch/x86/hyperv/mmu.c                 |  10 +-
 arch/x86/include/asm/paravirt.h       |   6 +-
 arch/x86/include/asm/paravirt_types.h |   4 +-
 arch/x86/include/asm/tlbflush.h       |  47 ++++-----
 arch/x86/include/asm/trace/hyperv.h   |   2 +-
 arch/x86/kernel/kvm.c                 |  11 ++-
 arch/x86/kernel/paravirt.c            |   2 +-
 arch/x86/mm/init.c                    |   2 +-
 arch/x86/mm/tlb.c                     | 133 ++++++++++++++++----------
 arch/x86/xen/mmu_pv.c                 |  11 +--
 include/linux/cpumask.h               |   6 +-
 include/linux/smp.h                   |  27 ++++--
 include/trace/events/xen.h            |   2 +-
 kernel/smp.c                          | 133 ++++++++++++--------------
 14 files changed, 218 insertions(+), 178 deletions(-)
Reviewed-by: Dave Hansen <dave.hansen@linux.intel.com>
```
#### [PATCH 0/4] KVM: VMX: Preemptivly optimize VMX instrs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

An in-flight patch[1] to make __kvm_handle_fault_on_reboot() play nice
with objtool will add a JMP after most VMX instructions so that the reboot
macro can use an actual CALL to kvm_spurious_fault() instead of a funky
PUSH+JMP facsimile.

Rework the low level VMX instruction helpers to handle unexpected faults
manually instead of relying on the "fault on reboot" macro.  By using
asm-goto, most helpers can branch directly to an in-function call to
kvm_spurious_fault(), which can then be optimized by compilers to reside
out-of-line at the end of the function instead of inline as done by
"fault on reboot".

The net impact relative to the current code base is more or less a nop
when building with a compiler that supports __GCC_ASM_FLAG_OUTPUTS__.
A bunch of code that was previously in .fixup gets moved into the slow
paths of functions, but the fast paths are more basically unchanged.

Without __GCC_ASM_FLAG_OUTPUTS__, manually coding the Jcc is a net
positive as CC_SET() without compiler support almost always generates a
SETcc+CMP+Jcc sequence, which is now replaced with a single Jcc.

A small bonus is that the Jcc instrs are hinted to predict that the VMX
instr will be successful.

[1] https://lkml.kernel.org/r/64a9b64d127e87b6920a97afde8e96ea76f6524e.1563413318.git.jpoimboe@redhat.com

Sean Christopherson (4):
  objtool: KVM: x86: Check kvm_rebooting in kvm_spurious_fault()
  KVM: VMX: Optimize VMX instruction error and fault handling
  KVM: VMX: Add error handling to VMREAD helper
  KVM: x86: Drop ____kvm_handle_fault_on_reboot()

 arch/x86/include/asm/kvm_host.h |  6 +--
 arch/x86/kvm/vmx/ops.h          | 93 ++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.c          | 42 +++++++++++++++
 arch/x86/kvm/x86.c              |  3 +-
 tools/objtool/check.c           |  1 -
 5 files changed, 102 insertions(+), 43 deletions(-)
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
```
#### [PATCH v2 0/5] KVM: VMX: Optimize VMX instrs error/fault handling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

A recent commit reworked __kvm_handle_fault_on_reboot() to play nice with
objtool.  An unfortunate side effect is that JMP is now inserted after
most VMX instructions so that the reboot macro can use an actual CALL to
kvm_spurious_fault() instead of a funky PUSH+JMP facsimile in .fixup.

Rework the low level VMX instruction helpers to handle unexpected faults
manually instead of relying on the "fault on reboot" macro.  By using
asm-goto, most helpers can branch directly to an in-function call to
kvm_spurious_fault(), which can then be optimized by compilers to reside
out-of-line at the end of the function instead of inline as done by
"fault on reboot".

The net impact relative to the current code base is more or less a nop
when building with a compiler that supports __GCC_ASM_FLAG_OUTPUTS__.
A bunch of code that was previously in .fixup gets moved into the slow
paths of functions, but the fast paths are more basically unchanged.

Without __GCC_ASM_FLAG_OUTPUTS__, manually coding the Jcc is a net
positive as CC_SET() without compiler support almost always generates a
SETcc+CMP+Jcc sequence, which is now replaced with a single Jcc.

A small bonus is that the Jcc instrs are hinted to predict that the VMX
instr will be successful.

v2:
  - Rebased to x86/master, commit eceffd88ca20 ("Merge branch 'x86/urgent'")
  - Reworded changelogs to reference the commit instead lkml link for
    the recent changes to __kvm_handle_fault_on_reboot().
  - Added Paolo's acks for patch 1-4
  - Added patch 5 to do more cleanup, which was made possible by rebasing
    on top of the __kvm_handle_fault_on_reboot() changes.
  
Sean Christopherson (5):
  objtool: KVM: x86: Check kvm_rebooting in kvm_spurious_fault()
  KVM: VMX: Optimize VMX instruction error and fault handling
  KVM: VMX: Add error handling to VMREAD helper
  KVM: x86: Drop ____kvm_handle_fault_on_reboot()
  KVM: x86: Don't check kvm_rebooting in __kvm_handle_fault_on_reboot()

 arch/x86/include/asm/kvm_host.h | 16 ++----
 arch/x86/kvm/vmx/ops.h          | 93 ++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.c          | 42 +++++++++++++++
 arch/x86/kvm/x86.c              |  3 +-
 tools/objtool/check.c           |  1 -
 5 files changed, 104 insertions(+), 51 deletions(-)
```
