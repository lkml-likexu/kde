#### KVM: x86: SVM: Call x86_spec_ctrl_set_guest/host() with interrupts disabled
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Subject: KVM: x86: SVM: Call x86_spec_ctrl_set_guest/host() with interrupts disabled
From: Thomas Gleixner <tglx@linutronix.de>
Date: Sun, 12 Aug 2018 20:41:45 +0200

Mikhail reported the following lockdep splat:

WARNING: possible irq lock inversion dependency detected
CPU 0/KVM/10284 just changed the state of lock:
  000000000d538a88 (&st->lock){+...}, at:
  speculative_store_bypass_update+0x10b/0x170

but this lock was taken by another, HARDIRQ-safe lock
in the past:

(&(&sighand->siglock)->rlock){-.-.}

   and interrupts could create inverse lock ordering between them.
 
Possible interrupt unsafe locking scenario:

    CPU0                    CPU1
    ----                    ----
   lock(&st->lock);
                           local_irq_disable();
                           lock(&(&sighand->siglock)->rlock);
                           lock(&st->lock);
    <Interrupt>
     lock(&(&sighand->siglock)->rlock);
     *** DEADLOCK ***

The code path which connects those locks is:

   speculative_store_bypass_update()
   ssb_prctl_set()
   do_seccomp()
   do_syscall_64()

In svm_vcpu_run() speculative_store_bypass_update() is called with
interupts enabled via x86_virt_spec_ctrl_set_guest/host().

Move the invocations of x86_virt_spec_ctrl_set_guest/host() into the
interrupt disabled region to cure it.

Fixes: 1f50ddb4f418 ("x86/speculation: Handle HT correctly on AMD")
Reported-by: Mikhail Gavrilov <mikhail.v.gavrilov@gmail.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Tested-by: Mikhail Gavrilov <mikhail.v.gavrilov@gmail.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Matthew Wilcox <willy@infradead.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: x86@kernel.org
Cc: stable@vger.kernel.org
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c |    8 ++++----
```
