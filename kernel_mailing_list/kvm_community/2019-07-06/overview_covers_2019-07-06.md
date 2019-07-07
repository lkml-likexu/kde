

#### [PATCH v7 0/2] KVM: LAPIC: Implement Exitless Timer
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
timer will be moved to the nearest busy housekeepers after commit
9642d18eee2cd (nohz: Affine unpinned timers to housekeepers) and commit 
444969223c8 ("sched/nohz: Fix affine unpinned timers mess"). However, 
KVM always makes lapic timer pinned to the pCPU which vCPU residents, the 
reason is explained by commit 61abdbe0 (kvm: x86: make lapic hrtimer 
pinned). Actually, these emulated timers can be offload to the housekeeping 
cpus since APICv is really common in recent years. The guest timer interrupt 
is injected by posted-interrupt which is delivered by housekeeping cpu 
once the emulated timer fires. 

The host admin should fine tuned, e.g. dedicated instances scenario w/ 
nohz_full cover the pCPUs which vCPUs resident, several pCPUs surplus 
for busy housekeeping, disable mwait/hlt/pause vmexits to keep in non-root  
mode, ~3% redis performance benefit can be observed on Skylake server.

w/o patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time   Avg time

EXTERNAL_INTERRUPT    42916    49.43%   39.30%   0.47us   106.09us   0.71us ( +-   1.09% )

w/ patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time         Avg time

EXTERNAL_INTERRUPT    6871     9.29%     2.96%   0.44us    57.88us   0.72us ( +-   4.02% )

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>

v6 -> v7:
 * remove bool argument

v5 -> v6:
 * don't overwrites whatever the user specified
 * introduce kvm_can_post_timer_interrupt and kvm_use_posted_timer_interrupt
 * remove kvm_hlt_in_guest() condition
 * squash all of 2/3/4 together

v4 -> v5:
 * update patch description in patch 1/4
 * feed latest apic->lapic_timer.expired_tscdeadline to kvm_wait_lapic_expire()
 * squash advance timer handling to patch 2/4

v3 -> v4:
 * drop the HRTIMER_MODE_ABS_PINNED, add kick after set pending timer
 * don't posted inject already-expired timer

v2 -> v3:
 * disarming the vmx preemption timer when posted_interrupt_inject_timer_enabled()
 * check kvm_hlt_in_guest instead

v1 -> v2:
 * check vcpu_halt_in_guest
 * move module parameter from kvm-intel to kvm
 * add housekeeping_enabled
 * rename apic_timer_expired_pi to kvm_apic_inject_pending_timer_irqs


Wanpeng Li (2):
  KVM: LAPIC: Make lapic timer unpinned
  KVM: LAPIC: Inject timer interrupt via posted interrupt

 arch/x86/kvm/lapic.c            | 109 ++++++++++++++++++++++++++--------------
 arch/x86/kvm/lapic.h            |   1 +
 arch/x86/kvm/vmx/vmx.c          |   3 +-
 arch/x86/kvm/x86.c              |  12 +++--
 arch/x86/kvm/x86.h              |   2 +
 include/linux/sched/isolation.h |   2 +
 kernel/sched/isolation.c        |   6 +++
 7 files changed, 90 insertions(+), 45 deletions(-)
```
#### [PATCH 0/3] [PATCH 0/3] Documentation: virtual: convert files from
##### From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
X-Google-Original-From: Luke Nowakowski-Krijger <lnowakow@neg.ucsd.edu>
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

```c

From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Converted a few documents in virtual and virtual/kvm to .rst format.
Also added toctree hooks wherever there were .rst files. Adding hooks to
the main doc tree should be in another patch series once there are more
files in the directory. 

After confirming with the appropriate lists that all the 
Documentation/virtual/* files are not obsolete I will continue
converting the rest of the .txt files to .rst. 

Luke Nowakowski-Krijger (3):
  Documentation: virtual: Add toctree hooks
  Documentation: kvm: Convert cpuid.txt to .rst
  Documentation: virtual: Convert paravirt_ops.txt to .rst

 Documentation/virtual/index.rst               | 18 ++++
 Documentation/virtual/kvm/cpuid.rst           | 99 +++++++++++++++++++
 Documentation/virtual/kvm/cpuid.txt           | 83 ----------------
 Documentation/virtual/kvm/index.rst           | 12 +++
 .../{paravirt_ops.txt => paravirt_ops.rst}    | 19 ++--
 5 files changed, 140 insertions(+), 91 deletions(-)
 create mode 100644 Documentation/virtual/index.rst
 create mode 100644 Documentation/virtual/kvm/cpuid.rst
 delete mode 100644 Documentation/virtual/kvm/cpuid.txt
 create mode 100644 Documentation/virtual/kvm/index.rst
 rename Documentation/virtual/{paravirt_ops.txt => paravirt_ops.rst} (65%)
```
