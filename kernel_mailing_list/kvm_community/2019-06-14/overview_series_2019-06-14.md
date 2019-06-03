#### [PATCH v4 1/2] KVM: LAPIC: Optimize timer latency consider world switch time
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Advance lapic timer tries to hidden the hypervisor overhead between the
host emulated timer fires and the guest awares the timer is fired. However,
even though after more sustaining optimizations, kvm-unit-tests/tscdeadline_latency 
still awares ~1000 cycles latency since we lost the time between the end of 
wait_lapic_expire and the guest awares the timer is fired. There are 
codes between the end of wait_lapic_expire and the world switch, furthermore, 
the world switch itself also has overhead. Actually the guest_tsc is equal 
to the target deadline time in wait_lapic_expire is too late, guest will
aware the latency between the end of wait_lapic_expire() and after vmentry 
to the guest. This patch takes this time into consideration. 

The vmentry_advance_ns module parameter is conservative 25ns by default(thanks 
to Radim's kvm-unit-tests/vmentry_latency.flat), it can be tuned/reworked in 
the future.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v3 -> v4:
 * default value is 25ns
 * compute vmentry_advance_cycles in kvm_set_tsc_khz() path
v2 -> v3:
 * read-only module parameter
 * get_vmentry_advance_cycles() not inline
v1 -> v2:
 * rename get_vmentry_advance_delta to get_vmentry_advance_cycles
 * cache vmentry_advance_cycles by setting param bit 0 
 * add param max limit 

 arch/x86/kvm/lapic.c   | 21 ++++++++++++++++++---
 arch/x86/kvm/lapic.h   |  2 ++
 arch/x86/kvm/vmx/vmx.c |  3 ++-
 arch/x86/kvm/x86.c     | 12 ++++++++++--
 arch/x86/kvm/x86.h     |  2 ++
 5 files changed, 34 insertions(+), 6 deletions(-)

```
