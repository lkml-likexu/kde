

#### [PATCH 0/7] KVM: lapic: Fix a variety of timer adv issues
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The recent change to automatically calculate lapic_timer_advance_ns
introduced a handful of gnarly bugs, and also exposed a latent bug by
virtue of the advancement logic being enabled by default.  Inspection
and debug revealed several other opportunities for minor improvements.

The primary issue is that the auto-tuning of lapic_timer_advance_ns is
completely unbounded, e.g. there's nothing in the logic that prevents the
advancement from creeping up to hundreds of milliseconds.  Adjusting the
timers by large amounts creates major discrepancies in the guest, e.g. a
timer that was configured to fire after multiple milliseconds may arrive
before the guest executes a single instruction.  While technically correct
from a time perspective, it breaks a reasonable assumption from the guest
that it can execute some number of instructions between timer events.

The other major issue is that the advancement is global, while TSC scaling
is done on a per-vCPU basic.  Adjusting the advancement at runtime
exacerbates this as there is no protection against multiple vCPUs and/or
multiple VMs concurrently modifying the advancement value, e.g. it can
effectively become corrupted or never stabilize due to getting bounced all
over tarnation.

As for the latent bug, when timer advancement was applied to the hv_timer,
i.e. the VMX preemption timer, the logic to trigger wait_for_lapic_timer()
was not updated.  As a result, a timer interrupt emulated via the hv_timer
can easily arrive too early from a *time* perspective, as opposed to
simply arriving early from a "number of instructions executed" perspective.

As an aside, the test stage counting in kvm-unit-tests' vmx.flat/interrupt
is off by one, which causes it to misreport what it's testing, e.g. says
it's testing "direct interrupt" when the unit test's host is intercepting
interrupts and vice versa.  That was a fun few hours of debug.

Sean Christopherson (7):
  KVM: lapic: Hard cap the auto-calculated timer advancement
  KVM: lapic: Delay 1ns at a time when waiting for timer to "expire"
  KVM: lapic: Track lapic timer advance per vCPU
  KVM: lapic: Allow user to override auto-tuning of timer advancement
  KVM: lapic: Busy wait for timer to expire when using hv_timer
  KVM: lapic: Clean up the code for handling of a pre-expired hv_timer
  KVM: VMX: Skip delta_tsc shift-and-divide if the dividend is zero

 arch/x86/kvm/lapic.c   | 56 +++++++++++++++++++++++++-----------------
 arch/x86/kvm/lapic.h   |  6 ++++-
 arch/x86/kvm/vmx/vmx.c |  9 ++++---
 arch/x86/kvm/x86.c     |  7 +++---
 arch/x86/kvm/x86.h     |  2 --
 5 files changed, 47 insertions(+), 33 deletions(-)
```
