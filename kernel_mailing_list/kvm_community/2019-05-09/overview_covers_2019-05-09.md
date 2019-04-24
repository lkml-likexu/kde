

#### [PATCH 0/3] KVM: LAPIC: Optimize timer latency further
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Advance lapic timer tries to hidden the hypervisor overhead between host 
timer fires and the guest awares the timer is fired. However, it just hidden 
the time between apic_timer_fn/handle_preemption_timer -> wait_lapic_expire, 
instead of the real position of vmentry which is mentioned in the orignial 
commit d0659d946be0 ("KVM: x86: add option to advance tscdeadline hrtimer 
expiration"). There is 700+ cpu cycles between the end of wait_lapic_expire 
and before world switch on my haswell desktop, it will be 2400+ cycles if 
vmentry_l1d_flush is tuned to always. 

This patchset tries to narrow the last gap, it measures the time between 
the end of wait_lapic_expire and before world switch, we take this 
time into consideration when busy waiting, otherwise, the guest still 
awares the latency between wait_lapic_expire and world switch, we also 
consider this when adaptively tuning the timer advancement. The patch 
can reduce 50% latency (~1600+ cycles to ~800+ cycles on a haswell 
desktop) for kvm-unit-tests/tscdeadline_latency when testing busy waits.

Wanpeng Li (3):
  KVM: LAPIC: Extract adaptive tune timer advancement logic
  KVM: LAPIC: Fix lapic_timer_advance_ns parameter overflow
  KVM: LAPIC: Optimize timer latency further

 arch/x86/kvm/lapic.c   | 78 ++++++++++++++++++++++++++++++++++----------------
 arch/x86/kvm/lapic.h   |  8 ++++++
 arch/x86/kvm/vmx/vmx.c |  2 ++
 arch/x86/kvm/x86.c     |  2 +-
 4 files changed, 64 insertions(+), 26 deletions(-)
```
#### [PATCH 0/4][kvm-unit-test nVMX]: Test "load IA32_PERF_GLOBAL_CONTROL"
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c

This set contains the unit test, and related changes, for the "load
IA32_PERF_GLOBAL_CONTROL" VM-entry control that was enabled in my previous
patchset titled:

	[KVM nVMX]: Check "load IA32_PERF_GLOBAL_CTRL" on vmentry of nested guests


[PATCH 1/4][kvm-unit-test nVMX]: Rename guest_pat_main to guest_state_test_main
[PATCH 2/4][kvm-unit-test nVMX]: Rename report_guest_pat_test to
[PATCH 3/4][kvm-unit-test nVMX]: Add #define for "load IA32_PERF_GLOBAL_CONTROL" bit
[PATCH 4/4][kvm-unit-test nVMX]: Test "load IA32_PERF_GLOBAL_CONTROL" VM-entry

 x86/vmx.h       |   1 +
 x86/vmx_tests.c | 108 +++++++++++++++++++++++++++++++++++++++++++-----------
 2 files changed, 87 insertions(+), 22 deletions(-)

Krish Sadhukhan (4):
      nVMX: Rename guest_pat_main to guest_state_test_main
      nVMX: Rename report_guest_pat_test to report_guest_state_test
      nVMX: Add #define for "load IA32_PERF_GLOBAL_CONTROL" bit
      nVMX: Test "load IA32_PERF_GLOBAL_CONTROL" VM-entry control on vmentry of nested guests
```
