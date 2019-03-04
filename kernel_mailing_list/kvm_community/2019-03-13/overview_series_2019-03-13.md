#### [PATCH] KVM: selftests: assert on exit reason in CR4/cpuid sync test
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
...so that the test doesn't end up in an infinite loop if it fails for
whatever reason, e.g. SHUTDOWN due to gcc inserting stack canary code
into ucall() and attempting to derefence a null segment.

Fixes: ca359066889f7 ("kvm: selftests: add cr4_cpuid_sync_test")
Cc: Wei Huang <wei@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 .../kvm/x86_64/cr4_cpuid_sync_test.c          | 35 ++++++++++---------
 1 file changed, 19 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: selftests: disable stack protector for all KVM tests
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Since 4.8.3, gcc has enabled -fstack-protector by default.  This is
problematic for the KVM selftests as they do not configure fs or gs
segments (the stack canary is pulled from fs:0x28).  With the default
behavior, gcc will insert a stack canary on any function that creates
buffers of 8 bytes or more.  As a result, ucall() will hit a triple
fault shutdown due to reading a bad fs segment when inserting its
stack canary, i.e. every test fails with an unexpected SHUTDOWN.

Fixes: 14c47b7530e2d ("kvm: selftests: introduce ucall")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 tools/testing/selftests/kvm/Makefile | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: use macro APIC_SEND_PENDING
##### From: Li RongQing <lirongqing@baidu.com>

```c
instead of hardcode value, use APIC_SEND_PENDING to make
code more readable

Signed-off-by: Li RongQing <lirongqing@baidu.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] MAINTAINERS: Add KVM selftests to existing KVM entry
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
It's safe to assume Paolo and Radim are maintaining the KVM selftests
given that the vast majority of commits have their SOBs.  Play nice
with get_maintainers and make it official.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5 1/7] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command and only this command.
The preceding behavior for other commands should not change.

We inject the correct exceptions from inside KVM for the case the
callback is not initialized, which happens when the vfio_ap driver
is not loaded.

It is the duty of the vfio_driver to setup a pqap callback inside
the crypto structure.
If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h      |  8 +++++
 arch/s390/kvm/priv.c                  | 62 +++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  2 ++
 3 files changed, 72 insertions(+)

```
#### [PATCH] x86/kvm/hyper-v: avoid spurious pending stimer on vCPU init
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
When userspace initializes guest vCPUs it may want to zero all supported
MSRs including Hyper-V related ones including HV_X64_MSR_STIMERn_CONFIG/
HV_X64_MSR_STIMERn_COUNT. With commit f3b138c5d89a ("kvm/x86: Update SynIC
timers on guest entry only") we began doing stimer_mark_pending()
unconditionally on every config change.

The issue I'm observing manifests itself as following:
- Qemu writes 0 to STIMERn_{CONFIG,COUNT} MSRs and marks all stimers as
  pending in stimer_pending_bitmap, arms KVM_REQ_HV_STIMER;
- kvm_hv_has_stimer_pending() starts returning true;
- kvm_vcpu_has_events() starts returning true;
- kvm_arch_vcpu_runnable() starts returning true;
- when kvm_arch_vcpu_ioctl_run() gets into
  (vcpu->arch.mp_state == KVM_MP_STATE_UNINITIALIZED) case:
  - kvm_vcpu_block() gets in 'kvm_vcpu_check_block(vcpu) < 0' and returns
    immediately, avoiding normal wait path;
  - -EAGAIN is returned from kvm_arch_vcpu_ioctl_run() immediately forcing
    userspace to retry.

So instead of normal wait path we get a busy loop on all secondary vCPUs
before they get INIT signal. This seems to be undesirable, especially given
that this happens even when Hyper-V extensions are not used.

Generally, it seems to be pointless to mark an stimer as pending in
stimer_pending_bitmap and arm KVM_REQ_HV_STIMER as the only thing
kvm_hv_process_stimers() will do is clear the corresponding bit. We may
just not mark disabled timers as pending instead.

Fixes: f3b138c5d89a ("kvm/x86: Update SynIC timers on guest entry only")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
