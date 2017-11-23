#### [PATCH] KVM: VMX: Move vmx_vcpu_run()'s VM-Enter asm blob to a helper function
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
...along with the function's STACK_FRAME_NON_STANDARD tag.  Moving the
asm blob results in a significantly smaller amount of code that is
marked with STACK_FRAME_NON_STANDARD, which makes it far less likely
that gcc will split the function and trigger a spurious objtool warning.
As a bonus, removing STACK_FRAME_NON_STANDARD from vmx_vcpu_run() allows
the bulk of code to be properly checked by objtool.

Because %rbp is not loaded via VMCS fields, vmx_vcpu_run() must manually
save/restore the host's RBP and load the guest's RBP prior to calling
vmx_vmenter().  Modifying %rbp triggers objtool's stack validation code,
and so vmx_vcpu_run() is tagged with STACK_FRAME_NON_STANDARD since it's
impossible to avoid modifying %rbp.

Unfortunately, vmx_vcpu_run() is also a gigantic function that gcc will
split into separate functions, e.g. so that pieces of the function can
be inlined.  Splitting the function means that the compiled Elf file
will contain one or more vmx_vcpu_run.part.* functions in addition to
a vmx_vcpu_run function.  Depending on where the function is split,
objtool may warn about a "call without frame pointer save/setup" in
vmx_vcpu_run.part.* since objtool's stack validation looks for exact
names when whitelisting functions tagged with STACK_FRAME_NON_STANDARD.

Up until recently, the undesirable function splitting was effectively
blocked because vmx_vcpu_run() was tagged with __noclone.  At the time,
__noclone had an unintended side effect that put vmx_vcpu_run() into a
separate optimization unit, which in turn prevented gcc from inlining
the function (or any of its own function calls) and thus eliminated gcc's
motivation to split the function.  Removing the __noclone attribute
allowed gcc to optimize vmx_vcpu_run(), exposing the objtool warning.

Kudos to Qian Cai for root causing that the fnsplit optimization is what
caused objtool to complain.

Fixes: 453eafbe65f7 ("KVM: VMX: Move VM-Enter + VM-Exit handling to non-inline sub-routines")
Cc: Qian Cai <cai@lca.pw>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Tested-by: Qian Cai <cai@lca.pw>
---
 arch/x86/kvm/vmx/vmx.c | 139 ++++++++++++++++++++++-------------------
 1 file changed, 73 insertions(+), 66 deletions(-)

```
