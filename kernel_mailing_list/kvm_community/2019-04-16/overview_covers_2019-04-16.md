

#### [PATCH v2 0/7] KVM: lapic: Fix a variety of timer adv issues
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

v2:
 - Add explicit param to control automatic tuning. [Liran]
 - Document the effect of per-vCPU tracking on the module params.
 - Use fancy math to convert guest clockcycles to host nanoseconds
   instead of brute forcing the delay with a for loop. [Liran]
 - Refactor start_hv_timer()'s return semantics to move the "expired
   timer" handling up a level. [Liran and Paolo]
 - Add Liran's Reviewed-by tags.

v1: https://patchwork.kernel.org/cover/10899101/


Sean Christopherson (7):
  KVM: lapic: Hard cap the auto-calculated timer advancement
  KVM: lapic: Convert guest TSC to host time domain when delaying
  KVM: lapic: Track lapic timer advance per vCPU
  KVM: lapic: Allow user to disable auto-tuning of timer advancement
  KVM: lapic: Busy wait for timer to expire when using hv_timer
  KVM: lapic: Refactor start_hv_timer()'s semantics and usage
  KVM: VMX: Skip delta_tsc shift-and-divide if the dividend is zero

 arch/x86/kvm/lapic.c   | 104 +++++++++++++++++++++++++++--------------
 arch/x86/kvm/lapic.h   |   5 +-
 arch/x86/kvm/vmx/vmx.c |   9 ++--
 arch/x86/kvm/x86.c     |  11 +++--
 arch/x86/kvm/x86.h     |   2 -
 5 files changed, 84 insertions(+), 47 deletions(-)
```
#### [PATCH v2 0/2] disabling halt polling for nested virtualization
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

v1->v2:
	- add kvm_vcpu parameter to kvm_arch_no_poll
	- add kvm stat in the s390 implementation
	- make the value tunable
	
Folks,

this is a very simple variant to disable halt polling when the KVM host
is already running virtualized. We could imagine more complex variants
(like tuning down the halt polling value) but this seems to do the trick
for some kvm deployment scenarios on s390x. (e.g. having multiple LPARS
with KVMs that are in itself already overcommitted). 


Christian Borntraeger (2):
  KVM: polling: add architecture backend to disable polling
  KVM: s390: provide kvm_arch_no_poll function

 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/kvm/Kconfig            |  1 +
 arch/s390/kvm/kvm-s390.c         | 17 +++++++++++++++++
 include/linux/kvm_host.h         | 10 ++++++++++
 virt/kvm/Kconfig                 |  3 +++
 virt/kvm/kvm_main.c              |  2 +-
 6 files changed, 33 insertions(+), 1 deletion(-)
```
#### [PATCH v3 0/9] KVM: lapic: Fix a variety of timer adv issues
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

v3:
 - Split the refactoring of start_hv_timer() and ->set_hv_timer
   into three separate patches instead of attempting to do a big
   refactor in a single patch to fix three separate issues.
    - Explicitly cancel the hv timer to avoid
    - Use a param for "expired" instead of overloading the return
      value of ->set_hv_timer().
    - Check for a pending non-periodic in restart_apic_timer(). [Liran]
 - Add more Reviewed-by tags.

v2:
 - https://patchwork.kernel.org/cover/10903613/
 - Add explicit param to control automatic tuning. [Liran]
 - Document the effect of per-vCPU tracking on the module params.
 - Use fancy math to convert guest clockcycles to host nanoseconds
   instead of brute forcing the delay with a for loop. [Liran]
 - Refactor start_hv_timer()'s return semantics to move the "expired
   timer" handling up a level. [Liran and Paolo]
 - Add Liran's Reviewed-by tags.

v1: https://patchwork.kernel.org/cover/10899101/

Sean Christopherson (9):
  KVM: lapic: Hard cap the auto-calculated timer advancement
  KVM: lapic: Convert guest TSC to host time domain when delaying
  KVM: lapic: Track lapic timer advance per vCPU
  KVM: lapic: Allow user to disable auto-tuning of timer advancement
  KVM: lapic: Busy wait for timer to expire when using hv_timer
  KVM: lapic: Explicitly cancel the hv timer if it's pre-expired
  KVM: lapic: Refactor ->set_hv_timer to use an explicit expired param
  KVM: lapic: Check for a pending timer intr prior to start_hv_timer()
  KVM: VMX: Skip delta_tsc shift-and-divide if the dividend is zero

 arch/x86/include/asm/kvm_host.h |  3 +-
 arch/x86/kvm/lapic.c            | 81 +++++++++++++++++++++------------
 arch/x86/kvm/lapic.h            |  5 +-
 arch/x86/kvm/vmx/vmx.c          | 15 +++---
 arch/x86/kvm/x86.c              | 11 +++--
 arch/x86/kvm/x86.h              |  2 -
 6 files changed, 73 insertions(+), 44 deletions(-)
```
