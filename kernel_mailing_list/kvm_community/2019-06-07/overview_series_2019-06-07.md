#### [PATCH kvmtool v2 1/2] list: Clean up ghost socket files
##### From: Andre Przywara <andre.przywara@arm.com>

```c
When kvmtool (or the host kernel) crashes or gets killed, we cannot
automatically remove the socket file we created for that VM.
A later call of "lkvm list" iterates over all those files and complains
about those "ghost socket files", as there is no one listening on
the other side. Also sometimes the automatic guest name generation
happens to generate the same name again, so an unrelated "lkvm run"
later complains and stops, which is bad for automation.

As the only code doing a listen() on this socket is kvmtool upon VM
*creation*, such an orphaned socket file will never come back to life,
so we can as well unlink() those sockets in the code. This spares the
user from doing it herself.
We keep the message in the code to notify the user of this.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 kvm-ipc.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: VMX: simplify vmx_prepare_switch_to_{guest,host}
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
vmx->loaded_cpu_state can only be NULL or equal to vmx->loaded_vmcs,
so change it to a bool.  Because the direction of the bool is
now the opposite of vmx->guest_msrs_dirty, change the direction of
vmx->guest_msrs_dirty so that they match.

Finally, do not imply that MSRs have to be reloaded when
vmx->guest_sregs_loaded is false; instead, set vmx->guest_msrs_loaded
to false explicitly in vmx_prepare_switch_to_host.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
	Still untested.

 arch/x86/kvm/vmx/vmx.c | 26 +++++++++++++-------------
 arch/x86/kvm/vmx/vmx.h | 18 ++++++++++++------
 2 files changed, 25 insertions(+), 19 deletions(-)

```
#### [PATCH v3 07/20] docs: amd-memory-encryption.rst get rid of warnings
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Get rid of those warnings:

    Documentation/virtual/kvm/amd-memory-encryption.rst:244: WARNING: Citation [white-paper] is not referenced.
    Documentation/virtual/kvm/amd-memory-encryption.rst:246: WARNING: Citation [amd-apm] is not referenced.
    Documentation/virtual/kvm/amd-memory-encryption.rst:247: WARNING: Citation [kvm-forum] is not referenced.

For references that aren't mentioned at the text by adding an
explicit reference to them.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/amd-memory-encryption.rst | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] nVMX: Get rid of prepare_vmcs02_early_full and inline its content in the caller
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
..as there is no need for a separate function

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 30 +++++++++++++-----------------
 1 file changed, 13 insertions(+), 17 deletions(-)

```
#### [PATCH trivial] KVM: arm/arm64: Always capitalize ITS
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
All but one reference is capitalized.  Fix the remaining one.

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
---
 Documentation/virtual/kvm/devices/arm-vgic-its.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: nVMX: Stash L1's CR3 in vmcs01.GUEST_CR3 on nested entry w/o EPT
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
KVM does not have 100% coverage of VMX consistency checks, i.e. some
checks that cause VM-Fail may only be detected by hardware during a
nested VM-Entry.  In such a case, KVM must restore L1's state to the
pre-VM-Enter state as L2's state has already been loaded into KVM's
software model.

L1's CR3 and PDPTRs in particular are loaded from vmcs01.GUEST_*.  But
when EPT is disabled, the associated fields hold KVM's shadow values,
not L1's "real" values.  Fortunately, when EPT is disabled the PDPTRs
come from memory, i.e. are not cached in the VMCS.  Which leaves CR3
as the sole anomaly.

A previously applied workaround to handle CR3 was to force nested early
checks if EPT is disabled:

  commit 2b27924bb1d48 ("KVM: nVMX: always use early vmcs check when EPT
                         is disabled")

Forcing nested early checks is undesirable as doing so adds hundreds of
cycles to every nested VM-Entry.  Rather than take this performance hit,
handle CR3 by overwriting vmcs01.GUEST_CR3 with L1's CR3 during nested
VM-Entry when EPT is disabled *and* nested early checks are disabled.
By stuffing vmcs01.GUEST_CR3, nested_vmx_restore_host_state() will
naturally restore the correct vcpu->arch.cr3 from vmcs01.GUEST_CR3.

These shenanigans work because nested_vmx_restore_host_state() does a
full kvm_mmu_reset_context(), i.e. unloads the current MMU, which
guarantees vmcs01.GUEST_CR3 will be rewritten with a new shadow CR3
prior to re-entering L1.

vcpu->arch.root_mmu.root_hpa is set to INVALID_PAGE via:

    nested_vmx_restore_host_state() ->
        kvm_mmu_reset_context() ->
            kvm_mmu_unload() ->
                kvm_mmu_free_roots()

kvm_mmu_unload() has WARN_ON(root_hpa != INVALID_PAGE), i.e. we can bank
on 'root_hpa == INVALID_PAGE' unless the implementation of
kvm_mmu_reset_context() is changed.

On the way into L1, VMCS.GUEST_CR3 is guaranteed to be written (on a
successful entry) via:

    vcpu_enter_guest() ->
        kvm_mmu_reload() ->
            kvm_mmu_load() ->
                kvm_mmu_load_cr3() ->
                    vmx_set_cr3()

Stuff vmcs01.GUEST_CR3 if and only if nested early checks are disabled
as a "late" VM-Fail should never happen win that case (KVM WARNs), and
the conditional write avoids the need to restore the correct GUEST_CR3
when nested_vmx_check_vmentry_hw() fails.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2: Squashed the revert of the previous workaround into this patch
    and added a beefy comment [Paolo].

 arch/x86/include/uapi/asm/vmx.h |  1 -
 arch/x86/kvm/vmx/nested.c       | 44 +++++++++++++++++----------------
 2 files changed, 23 insertions(+), 22 deletions(-)

```
#### [PATCH v5 1/3] kvm: vmx: fix limit checking in get_vmx_mem_address()
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
Intel SDM vol. 3, 5.3:
The processor causes a
general-protection exception (or, if the segment is SS, a stack-fault
exception) any time an attempt is made to access the following addresses
in a segment:
- A byte at an offset greater than the effective limit
- A word at an offset greater than the (effective-limit – 1)
- A doubleword at an offset greater than the (effective-limit – 3)
- A quadword at an offset greater than the (effective-limit – 7)

Therefore, the generic limit checking error condition must be

exn = (off > limit + 1 - access_len) = (off + access_len - 1 > limit)

but not

exn = (off + access_len > limit)

as for now.

Also avoid integer overflow of `off` at 32-bit KVM by casting it to u64.

Note: access length is currently sizeof(u64) which is incorrect. This
will be fixed in the subsequent patch.

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
Changes in v3 since v2: fixed limit checking condition to avoid underflow;
added note
Changes in v4 since v3: fixed `off` overflow at 32-bit by casting to u64

 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/fpu: Update kernel's FPU state before using for the fsave header
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
In commit

  39388e80f9b0c ("x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()")

I removed the statement
|       if (ia32_fxstate)
|               copy_fxregs_to_kernel(fpu);

and argued that is was wrongly merged because the content was already
saved in kernel's state and the content.
This was wrong: It is required to write it back because it is only saved
on the user-stack and save_fsave_header() reads it from task's
FPU-state. I missed that part…

Save x87 FPU state unless thread's FPU registers are already up to date.

Fixes: 39388e80f9b0c ("x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()")
Reported-by: Eric Biggers <ebiggers@kernel.org>
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Tested-by: Eric Biggers <ebiggers@kernel.org>
---
 arch/x86/kernel/fpu/signal.c | 5 +++++
 1 file changed, 5 insertions(+)

```
