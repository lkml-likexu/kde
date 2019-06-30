#### KVM's SYSCALL emulation for GenuineIntel is buggyTo: kvm list <kvm@vger.kernel.org>,
##### From: Andy Lutomirski <luto@kernel.org>

```c
If I do SYSCALL with EFLAGS.TF set from compat mode on Intel hardware
with -cpu host and no other funny business, the guest kernel seems to
get #DB with the stored IP pointing at the SYSCALL instruction.  This
is wrong -- SYSCALL is #UD, which is a *fault*, so there shouldn't be
a single-step trap.

Unless I'm missing something in the code, emulate_ud() is mishandled
in general -- it seems to make cause inject_emulated_exception() to
return false here:

    if (ctxt->have_exception) {
        r = EMULATE_DONE;
        if (inject_emulated_exception(vcpu))
            return r;

and then we land here:

        if (r == EMULATE_DONE && ctxt->tf)
            kvm_vcpu_do_singlestep(vcpu, &r);

if TF was set, which is wrong.

You can test this by applying the attached patch, building x86
selftests, and running syscall_arg_fault_32 in a VM.  It hangs.  It
should complete successfully, and it does on bare metal.

commit fae8e860584b5a8c2253b522cb478e92b8b0c281
Author: Andy Lutomirski <luto@kernel.org>
Date:   Fri Jun 28 19:54:34 2019 -0700

    selftests/x86: Test SYSCALL and SYSENTER manually with TF set
    
    Make sure that we exercise both variants of the nasty
    TF-in-compat-syscall regardless of what vendor's CPU is running the
    tests.
    
    Also change the intentional signal after SYSCALL to use ud2, which
    is a lot more comprehensible.
    
    This crashes the kernel due to an FSGSBASE bug right now.
    
    Reported-by: Vegard Nossum <vegard.nossum@oracle.com>
    Cc: "Bae, Chang Seok" <chang.seok.bae@intel.com>
    Signed-off-by: Andy Lutomirski <luto@kernel.org>

```
