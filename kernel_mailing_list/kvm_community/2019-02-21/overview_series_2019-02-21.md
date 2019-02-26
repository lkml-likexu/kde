#### [PATCH 01/22] x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a preparation for the removal of the ->initialized member in the
fpu struct.
__fpu__restore_sig() is deactivating the FPU via fpu__drop() and then
setting manually ->initialized followed by fpu__restore(). The result is
that it is possible to manipulate fpu->state and the state of registers
won't be saved/restored on a context switch which would overwrite
fpu->state.

Don't access the fpu->state while the content is read from user space
and examined / sanitized. Use a temporary kmalloc() buffer for the
preparation of the FPU registers and once the state is considered okay,
load it. Should something go wrong, return with an error and without
altering the original FPU registers.

The removal of "fpu__initialize()" is a nop because fpu->initialized is
already set for the user task.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/fpu/signal.h |  2 +-
 arch/x86/kernel/fpu/regset.c      |  5 ++--
 arch/x86/kernel/fpu/signal.c      | 40 ++++++++++++-------------------
 3 files changed, 18 insertions(+), 29 deletions(-)

```
#### [PATCH 1/2] KVM: s390: implement subfunction processor calls
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
While we will not implement interception for query functions yet, we can
and should disable functions that have a control bit based on the given
CPU model.

Let us start with enabling the subfunction interface.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.vnet.ibm.com>
---
 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/kvm/kvm-s390.c         | 34 +++++++++++++++++++++-----------
 2 files changed, 23 insertions(+), 12 deletions(-)

```
#### [PATCH v1 1/2] tap13: list testcases individually
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
The current tap13 support summarizes testcases on a rather coarse
granularity. Which sort of defeats the purpose, especially in CI
environments.
This patch improves things by post-processing the log files, extracting
results for individual testcases. One could argue that post-processing the
logs is a rather fragile approach. Which is true - but apparently already
the case, see e.g. extract_summary in scripts/runtime.bash.
Plus this is quite cheap, while a proper solution would require to modify
the kernels, so we can e.g. pass in a counter for the testcase number. Plus
we would probably have to come up with reasonable testcase names, while
this approach simply derives them from each test output.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 run_tests.sh         | 28 +++++++++++++++++++++++-----
 scripts/runtime.bash | 10 ----------
 2 files changed, 23 insertions(+), 15 deletions(-)

```
#### [PATCH v2 1/1] kvm/mmu_notifier: re-enable the change_pte() optimization.
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

Since changes to mmu notifier the change_pte() optimization was lost
for kvm. This re-enable it, when ever a pte is going from read and
write to read only with same pfn, or from read only to read and write
with different pfn.

It is safe to update the secondary MMUs, because the primary MMU
pte invalidate must have already happened with a ptep_clear_flush()
before set_pte_at_notify() is invoked (and thus before change_pte()
callback).

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
---
 virt/kvm/kvm_main.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)

```
#### [PATCH v2 1/2] KVM: PPC: Book3S HV: Simplify machine check handling
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This makes the handling of machine check interrupts that occur inside
a guest simpler and more robust, with less done in assembler code and
in real mode.

Now, when a machine check occurs inside a guest, we always get the
machine check event struct and put a copy in the vcpu struct for the
vcpu where the machine check occurred.  We no longer call
machine_check_queue_event() from kvmppc_realmode_mc_power7(), because
on POWER8, when a vcpu is running on an offline secondary thread and
we call machine_check_queue_event(), that calls irq_work_queue(),
which doesn't work because the CPU is offline, but instead triggers
the WARN_ON(lazy_irq_pending()) in pnv_smp_cpu_kill_self() (which
fires again and again because nothing clears the condition).

All that machine_check_queue_event() actually does is to cause the
event to be printed to the console.  For a machine check occurring in
the guest, we now print the event in kvmppc_handle_exit_hv()
instead.

The assembly code at label machine_check_realmode now just calls C
code and then continues exiting the guest.  We no longer either
synthesize a machine check for the guest in assembly code or return
to the guest without a machine check.

The code in kvmppc_handle_exit_hv() is extended to handle the case
where the guest is not FWNMI-capable.  In that case we now always
synthesize a machine check interrupt for the guest.  Previously, if
the host thinks it has recovered the machine check fully, it would
return to the guest without any notification that the machine check
had occurred.  If the machine check was caused by some action of the
guest (such as creating duplicate SLB entries), it is much better to
tell the guest that it has caused a problem.  Therefore we now always
generate a machine check interrupt for guests that are not
FWNMI-capable.

Reviewed-by: Aravinda Prasad <aravinda@linux.vnet.ibm.com>
Reviewed-by: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: fix comment as requested by Aravinda

 arch/powerpc/include/asm/kvm_ppc.h      |  3 +-
 arch/powerpc/kvm/book3s.c               |  7 ++++
 arch/powerpc/kvm/book3s_hv.c            | 18 ++++++++--
 arch/powerpc/kvm/book3s_hv_ras.c        | 58 ++++++++-------------------------
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 40 ++---------------------
 5 files changed, 42 insertions(+), 84 deletions(-)

```
#### [PATCH v7] x86: load FPU registers on return to userland
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a refurbished series originally started by by Rik van Riel. The
goal is load the FPU registers on return to userland and not on every
context switch. By this optimisation we can:
- avoid loading the registers if the task stays in kernel and does
  not return to userland
- make kernel_fpu_begin() cheaper: it only saves the registers on the
  first invocation. The second invocation does not need save them again.

To access the FPU registers in kernel we need:
- disable preemption to avoid that the scheduler switches tasks. By
  doing so it would set TIF_NEED_FPU_LOAD and the FPU registers would be
  not valid.
- disable BH because the softirq might use kernel_fpu_begin() and then
  set TIF_NEED_FPU_LOAD instead loading the FPU registers on completion.

v6…v7:
Rebased on top of v5.0-rc7 and addressed Borislav Petkov's review.

v5…v6:
Rebased on top of v5.0-rc1. Integrated a few fixes which I noticed while
looking over the patches, dropped the first few patches which were
already applied.

v4…v5:
Rebased on top of a fix, noticed a problem with XSAVES and then redid
the restore on sig return (patch #26 to #28).

I don't like very much the sig save+restore thing that we are doing. It
has been always like that. I *think* that this is just because we have
nowhere to stash the FPU state while we are handling the signal. We
could add another fpu->state for the signal handler and avoid the thing.
Debian code-search revealed that `criu' is using it (and I didn't
figure out why). Nothing else (that is packaged in Debian). Maybe we
could get rid of this and if `criu' would then use a dedicated interface
for its needs rather the signal interface that happen to do what it
wants :)

v3…v4:
It has been suggested to remove the `initialized' member of the struct
fpu because it should not required be needed with lazy-FPU-restore and
would make the review easier. This is the first part of the series, the
second is basically the rebase of the v3 queue. As a result, the
diffstat became negative (which wasn't the case in previous version) :)
I tried to incorporate all the review comments that came up, some of
them were "outdated" after the removal of the `initialized' member. I'm
sorry should I missed any.

v1…v3:
v2 was never posted. I followed the idea to completely decouple PKRU
from xstate. This didn't quite work and made a few things complicated. 
One obvious required fixup is copy_fpstate_to_sigframe() where the PKRU
state needs to be fiddled into xstate. This required another
xfeatures_mask so that the sanity checks were performed and
xstate_offsets would be computed. Additionally ptrace also reads/sets
xstate in order to get/set the register and PKRU is one of them. So this
would need some fiddle, too.
In v3 I dropped that decouple idea. I also learned that the wrpkru
instruction is not privileged and so caching it in kernel does not work.
Instead I keep PKRU in xstate area and load it at context switch time
while the remaining registers are deferred (until return to userland).
The offset of PKRU within xstate is enumerated at boot time so why not
use it.

The following changes since commit a3b22b9f11d9fbc48b0291ea92259a5a810e9438:

  Linux 5.0-rc7 (2019-02-17 18:46:40 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/bigeasy/staging.git x86_fpu_rtu_v7

for you to fetch changes up to c0bd7b2b7b694c71f7b0101c338c0102aef8a91f:

  x86/fpu: Defer FPU state load until return to userspace (2019-02-21 12:29:00 +0100)

----------------------------------------------------------------
Rik van Riel (5):
      x86/fpu: Add (__)make_fpregs_active helpers
      x86/fpu: Eager switch PKRU state
      x86/fpu: Always store the registers in copy_fpstate_to_sigframe()
      x86/fpu: Prepare copy_fpstate_to_sigframe() for TIF_NEED_FPU_LOAD
      x86/fpu: Defer FPU state load until return to userspace

Sebastian Andrzej Siewior (17):
      x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
      x86/fpu: Remove fpu__restore()
      x86/fpu: Remove preempt_disable() in fpu__clear()
      x86/fpu: Always init the `state' in fpu__clear()
      x86/fpu: Remove fpu->initialized usage in copy_fpstate_to_sigframe()
      x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()
      x86/fpu: Remove fpu->initialized
      x86/fpu: Remove user_fpu_begin()
      x86/fpu: Make __raw_xsave_addr() use feature number instead of mask
      x86/fpu: Make get_xsave_field_ptr() and get_xsave_addr() use feature number instead of mask
      x86/fpu: Only write PKRU if it is different from current
      x86/pkeys: Don't check if PKRU is zero before writting it
      x86/entry: Add TIF_NEED_FPU_LOAD
      x86/fpu: Update xstate's PKRU value on write_pkru()
      x86/fpu: Inline copy_user_to_fpregs_zeroing()
      x86/fpu: Let __fpu__restore_sig() restore the !32bit+fxsr frame from kernel memory
      x86/fpu: Merge the two code paths in __fpu__restore_sig()

 Documentation/preempt-locking.txt    |   1 -
 arch/x86/entry/common.c              |   8 ++
 arch/x86/ia32/ia32_signal.c          |  17 ++-
 arch/x86/include/asm/fpu/api.h       |  31 ++++++
 arch/x86/include/asm/fpu/internal.h  | 163 +++++++++++++----------------
 arch/x86/include/asm/fpu/signal.h    |   2 +-
 arch/x86/include/asm/fpu/types.h     |   9 --
 arch/x86/include/asm/fpu/xstate.h    |   5 +-
 arch/x86/include/asm/pgtable.h       |  20 +++-
 arch/x86/include/asm/special_insns.h |   6 ++
 arch/x86/include/asm/thread_info.h   |   2 +
 arch/x86/include/asm/trace/fpu.h     |   8 +-
 arch/x86/kernel/fpu/core.c           | 194 +++++++++++++++++------------------
 arch/x86/kernel/fpu/init.c           |   2 -
 arch/x86/kernel/fpu/regset.c         |  24 ++---
 arch/x86/kernel/fpu/signal.c         | 191 +++++++++++++++-------------------
 arch/x86/kernel/fpu/xstate.c         |  42 ++++----
 arch/x86/kernel/process.c            |   2 +-
 arch/x86/kernel/process_32.c         |  11 +-
 arch/x86/kernel/process_64.c         |  11 +-
 arch/x86/kernel/signal.c             |  17 ++-
 arch/x86/kernel/traps.c              |   2 +-
 arch/x86/kvm/x86.c                   |  48 +++++----
 arch/x86/math-emu/fpu_entry.c        |   3 -
 arch/x86/mm/mpx.c                    |   6 +-
 arch/x86/mm/pkeys.c                  |  14 +--
 26 files changed, 408 insertions(+), 431 deletions(-)

Sebastian
```
#### [kvm-unit-tests PATCH 1/5] x86: nVMX: Check the return value of setup_eptp() in setup_ept()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A recent patch neglected to check the return value of the helper
function it factored out of setup_ept().

Fixes: d065566f60288 ("KVM: nVMX: Add enable_ept() helper to configure legal EPTP")
Reported-by: Marc Orr <marcorr@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 x86/vmx_tests.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
