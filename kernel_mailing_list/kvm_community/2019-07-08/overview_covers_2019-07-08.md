

#### [PATCH v7 00/12] Guest LBR Enabling
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
3) the host will help save/resotre the LBR stack when the vCPU is
   scheduled out/in.

ChangeLog:
    pmu.c:
        - patch 4: remove guest_cpuid_is_intel, which can be avoided by
                   directly checking pmu_ops->lbr_enable.
    pmu_intel.c:
        - patch 10: include MSR_LBR_SELECT into is_lbr_msr check, and pass
                    this msr through to the guest, instead of trapping
                    accesses.
        - patch 12: fix the condition check of setting LBRS_FROZEN and
                    COUNTERS_FROZEN;
                    update the global_ovf_ctrl_mask for LBRS_FROZEN and
                    COUNTERS_FROZEN.

previous:
https://lkml.org/lkml/2019/6/6/133

Like Xu (1):
  KVM/x86/vPMU: Add APIs to support host save/restore the guest lbr
    stack

Wei Wang (11):
  perf/x86: fix the variable type of the LBR MSRs
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: intel_pmu_lbr_enable
  KVM/x86/vPMU: tweak kvm_pmu_get_msr
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  perf/x86: no counter allocation support
  perf/x86: save/restore LBR_SELECT on vCPU switching
  KVM/x86/lbr: lazy save the guest lbr stack
  KVM/x86: remove the common handling of the debugctl msr
  KVM/VMX/vPMU: support to report GLOBAL_STATUS_LBRS_FROZEN

 arch/x86/events/core.c            |  12 ++
 arch/x86/events/intel/lbr.c       |  43 ++++-
 arch/x86/events/perf_event.h      |   6 +-
 arch/x86/include/asm/kvm_host.h   |   5 +
 arch/x86/include/asm/perf_event.h |  16 ++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/pmu.c                |  29 ++-
 arch/x86/kvm/pmu.h                |  12 +-
 arch/x86/kvm/pmu_amd.c            |   7 +-
 arch/x86/kvm/vmx/pmu_intel.c      | 393 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |   4 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  32 ++--
 include/linux/perf_event.h        |  13 ++
 include/uapi/linux/kvm.h          |   1 +
 kernel/events/core.c              |  37 ++--
 16 files changed, 562 insertions(+), 52 deletions(-)
```
#### [RFC v2 0/5] Some vfio-ccw fixes
##### From: Farhan Ali <alifm@linux.ibm.com>

```c

Hi,

While trying to chase down the problem regarding the stacktraces,
I have also found some minor problems in the code.

Would appreciate any review or feedback regarding them.

Thanks
Farhan

ChangeLog
---------
v1 -> v2
   - Update docs for csch/hsch since we can support those
     instructions now (patch 5)
   - Fix the memory leak where we fail to free a ccwchain (patch 2)
   - Add fixes tag where appropriate.
   - Fix comment instead of the order when setting orb.cmd.c64 (patch 1)

Farhan Ali (5):
  vfio-ccw: Fix misleading comment when setting orb.cmd.c64
  vfio-ccw: Fix memory leak and don't call cp_free in cp_init
  vfio-ccw: Set pa_nr to 0 if memory allocation fails for pa_iova_pfn
  vfio-ccw: Don't call cp_free if we are processing a channel program
  vfio-ccw: Update documentation for csch/hsch

 Documentation/s390/vfio-ccw.rst | 31 ++++++++++++++++++++++++++++---
 drivers/s390/cio/vfio_ccw_cp.c  | 19 ++++++++++++-------
 drivers/s390/cio/vfio_ccw_drv.c |  2 +-
 3 files changed, 41 insertions(+), 11 deletions(-)
```
