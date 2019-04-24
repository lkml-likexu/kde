

#### [PATCH 0/3] KVM: PPC: Book3S HV: XIVE: assorted fixes on vCPU and RAM
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

Here are a couple of fixes for issues in the XIVE KVM device when
testing the limits : RAM size and number of vCPUS.

Based on 5.2-rc1.

Available on GitHub:

    https://github.com/legoater/linux/commits/xive-5.2

Thanks,

C. 

Cédric Le Goater (3):
  KVM: PPC: Book3S HV: XIVE: clear file mapping when device is released
  KVM: PPC: Book3S HV: XIVE: do not test the EQ flag validity when
    reseting
  KVM: PPC: Book3S HV: XIVE: fix the enforced limit on the vCPU
    identifier

 arch/powerpc/kvm/book3s_xive_native.c | 46 ++++++++++++++++-----------
 1 file changed, 27 insertions(+), 19 deletions(-)
```
#### [PATCH v4 0/5] KVM: LAPIC: Optimize timer latency further 
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Advance lapic timer tries to hidden the hypervisor overhead between the 
host emulated timer fires and the guest awares the timer is fired. However, 
it just hidden the time between apic_timer_fn/handle_preemption_timer -> 
wait_lapic_expire, instead of the real position of vmentry which is 
mentioned in the orignial commit d0659d946be0 ("KVM: x86: add option to 
advance tscdeadline hrtimer expiration"). There is 700+ cpu cycles between 
the end of wait_lapic_expire and before world switch on my haswell desktop.

This patchset tries to narrow the last gap(wait_lapic_expire -> world switch), 
it takes the real overhead time between apic_timer_fn/handle_preemption_timer
and before world switch into consideration when adaptively tuning timer 
advancement. The patchset can reduce 40% latency (~1600+ cycles to ~1000+ 
cycles on a haswell desktop) for kvm-unit-tests/tscdeadline_latency when 
testing busy waits.

v3 -> v4:
 * create timer_advance_ns debugfs entry iff lapic_in_kernel() 
 * keep if (guest_tsc < tsc_deadline) before the call to __wait_lapic_expire()

v2 -> v3:
 * expose 'kvm_timer.timer_advance_ns' to userspace
 * move the tracepoint below guest_exit_irqoff()
 * move wait_lapic_expire() before flushing the L1

v1 -> v2:
 * fix indent in patch 1/4
 * remove the wait_lapic_expire() tracepoint and expose by debugfs
 * move the call to wait_lapic_expire() into vmx.c and svm.c

Wanpeng Li (5):
  KVM: LAPIC: Extract adaptive tune timer advancement logic
  KVM: LAPIC: Fix lapic_timer_advance_ns parameter overflow
  KVM: LAPIC: Expose per-vCPU timer_advance_ns to userspace
  KVM: LAPIC: Delay trace advance expire delta
  KVM: LAPIC: Optimize timer latency further

 arch/x86/kvm/debugfs.c | 18 +++++++++++++++
 arch/x86/kvm/lapic.c   | 60 +++++++++++++++++++++++++++++---------------------
 arch/x86/kvm/lapic.h   |  3 ++-
 arch/x86/kvm/svm.c     |  4 ++++
 arch/x86/kvm/vmx/vmx.c |  4 ++++
 arch/x86/kvm/x86.c     |  9 ++++----
 6 files changed, 68 insertions(+), 30 deletions(-)
```
#### [PATCH 0/2] KVM: x86/pmu: do not mask the value that is written to
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

The first patch is a small refactoring to enforce masking of values
returned by RDPMC and RDMSR.  The second patch fix pmu_intel.c to
behave the same as real hardware; this fixes the failing tests
introduced in kvm-unit-tests by "x86: PMU: Fix PMU counters masking".

(Nadav, this is just FYI.  I am not CCing you on individual patches
to avoid problems with your corporate overlords, and I am not expecting
a review from you).

Paolo

Paolo Bonzini (2):
  KVM: x86/pmu: mask the result of rdpmc according to the width of the
    counters
  KVM: x86/pmu: do not mask the value that is written to fixed PMUs

 arch/x86/kvm/pmu.c           | 10 +++-------
 arch/x86/kvm/pmu.h           |  3 ++-
 arch/x86/kvm/pmu_amd.c       |  2 +-
 arch/x86/kvm/vmx/pmu_intel.c | 26 +++++++++++++++++---------
 4 files changed, 23 insertions(+), 18 deletions(-)
```
#### [PATCH 0/2] KVM: nVMX: Alternative no-EPT GUEST_CR3 fix
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

As an alternative to forcing early consistency checks in hardware (to
avoid reaching nested_vmx_restore_host_state() due to a missed VM-FAIL),
stuff vmcs01.GUEST_CR3 with L1's desired CR3 prior to nested VM-Entry
so that nested_vmx_restore_host_state() loads the correct L1 state when
EPT is disabled in L0.

Code complexity in the two approaches is roughly similar, although the
GUEST_CR3 stuffing is definitely more subtle.  The primary motiviation
is performance, e.g. VMWRITE is less than 30 cyles, whereas doing
consistency checks via hardware is several hundred cycles.  Arguably
performance may be somewhat of a moot point when EPT is disabled, but
Nehalem hardware isn't *that* old.  :-)

Sean Christopherson (2):
  KVM: nVMX: Stash L1's CR3 in vmcs01.GUEST_CR3 on nested entry w/o EPT
  Revert "KVM: nVMX: always use early vmcs check when EPT is disabled"

 arch/x86/include/uapi/asm/vmx.h |  1 -
 arch/x86/kvm/vmx/nested.c       | 27 ++++++---------------------
 2 files changed, 6 insertions(+), 22 deletions(-)
```
