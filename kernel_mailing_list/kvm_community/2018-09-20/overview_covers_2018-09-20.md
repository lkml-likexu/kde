

#### [PATCH v3 0/5] Guest LBR Enabling
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Last Branch Recording (LBR) is a performance monitor unit (PMU) feature
on Intel CPUs that captures branch related info. This patch series enables
this feature to KVM guests.

Here is a conclusion of the fundamental methods that we use:
1) the LBR feature is enabled per guest via QEMU setting of
   KVM_CAP_X86_GUEST_LBR;
2) the LBR stack is passed through to the guest for direct accesses after
   the guest's first access to any of the lbr related MSRs;
3) When the guest uses the LBR feature with the user callstack mode, the
   host will help save/resotre the LBR stack when the vCPU is scheduled
   out/in.

ChangeLog:
v2->v3:
    - replaces the pv approach with a lazy save approach to saving the lbr
      stack on vCPU switching;
    - destroy the host side perf event if the guest is torn down;
    - remove the unnecessary event->pmu->stop() before calling
      perf_event_release_kernel().
v1->v2:
    - add the per guest LBR capability, KVM_CAP_X86_GUEST_LBR;
    - save/restore the LBR stack conditionally on the vCPU thread context
      switching, instead of on VMX transitions;
    - expose MSR_IA32_PERF_CAPABILITIES to the guest.

Like Xu (1):
  KVM/x86/vPMU: Add APIs to support host save/restore the guest lbr
    stack

Wei Wang (4):
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  KVM/x86/lbr: lazy save the guest lbr stack

 arch/x86/events/intel/lbr.c       |  49 ++++++++++++-
 arch/x86/events/perf_event.h      |   1 +
 arch/x86/include/asm/kvm_host.h   |   7 ++
 arch/x86/include/asm/perf_event.h |  22 ++++++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/pmu.h                |   8 +++
 arch/x86/kvm/pmu_intel.c          |  41 +++++++++++
 arch/x86/kvm/vmx.c                | 144 ++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                |  10 +++
 include/uapi/linux/kvm.h          |   1 +
 10 files changed, 281 insertions(+), 4 deletions(-)
```
