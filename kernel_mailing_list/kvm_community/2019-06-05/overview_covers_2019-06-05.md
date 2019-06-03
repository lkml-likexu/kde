

#### [PATCH 0/3] KVM: LAPIC: Implement Exitless Timer
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Dedicated instances are currently disturbed by unnecessary jitter due 
to the emulated lapic timers fire on the same pCPUs which vCPUs resident.
There is no hardware virtual timer on Intel for guest like ARM. Both 
programming timer in guest and the emulated timer fires incur vmexits.
This patchset tries to avoid vmexit which is incurred by the emulated 
timer fires in dedicated instance scenario. 

When nohz_full is enabled in dedicated instances scenario, the unpinned 
timer will be moved to the nearest busy housekeepers after commit 444969223c8
("sched/nohz: Fix affine unpinned timers mess"). However, KVM always makes 
lapic timer pinned to the pCPU which vCPU residents, the reason is explained 
by commit 61abdbe0 (kvm: x86: make lapic hrtimer pinned). Actually, these 
emulated timers can be offload to the housekeeping cpus since APICv 
is really common in recent years. The guest timer interrupt is injected by 
posted-interrupt which is delivered by housekeeping cpu once the emulated 
timer fires. 

This patchset introduces a new kvm module parameter, it is false by default.
The host admin can enable it after fine tuned, e.g. dedicated instances 
scenario w/ nohz_full cover the pCPUs which vCPUs resident, several pCPUs 
surplus for housekeeping, disable mwait/hlt/pause vmexits to occupy the 
pCPUs, fortunately preemption timer is disabled after mwait is exposed 
to guest which makes emulated timer offload can be possible. 
3%~5% redis performance benefit can be observed on Skylake server.

Wanpeng Li (3):
  KVM: LAPIC: Make lapic timer unpinned when timer is injected by posted-interrupt
  KVM: LAPIC: lapic timer is injected by posted interrupt
  KVM: LAPIC: Ignore timer migration when lapic timer is injected by
    posted-interrupt

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/lapic.c            | 45 +++++++++++++++++++++++++++++++++++------
 arch/x86/kvm/svm.c              |  5 +++++
 arch/x86/kvm/vmx/vmx.c          |  9 +++++++++
 4 files changed, 54 insertions(+), 6 deletions(-)
```
