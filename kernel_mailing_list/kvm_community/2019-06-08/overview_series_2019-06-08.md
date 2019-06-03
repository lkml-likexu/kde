#### [tip:x86/urgent] x86/fpu: Update kernel's FPU state before using for the fsave header
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  aab8445c4e1cceeb3f739352041ec1c2586bc923
Gitweb:     https://git.kernel.org/tip/aab8445c4e1cceeb3f739352041ec1c2586bc923
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Fri, 7 Jun 2019 16:29:16 +0200
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Sat, 8 Jun 2019 11:45:15 +0200

x86/fpu: Update kernel's FPU state before using for the fsave header

In commit

  39388e80f9b0c ("x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()")

I removed the statement

|       if (ia32_fxstate)
|               copy_fxregs_to_kernel(fpu);

and argued that it was wrongly merged because the content was already
saved in kernel's state.

This was wrong: It is required to write it back because it is only
saved on the user-stack and save_fsave_header() reads it from task's
FPU-state. I missed that part…

Save x87 FPU state unless thread's FPU registers are already up to date.

Fixes: 39388e80f9b0c ("x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()")
Reported-by: Eric Biggers <ebiggers@kernel.org>
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Tested-by: Eric Biggers <ebiggers@kernel.org>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@intel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Hugh Dickins <hughd@google.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Jann Horn <jannh@google.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Rik van Riel <riel@surriel.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20190607142915.y52mfmgk5lvhll7n@linutronix.de
---
 arch/x86/kernel/fpu/signal.c | 5 +++++
 1 file changed, 5 insertions(+)

```
