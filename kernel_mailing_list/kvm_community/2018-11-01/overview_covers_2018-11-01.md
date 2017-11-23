

#### [PATCH v1 0/8] Intel Virtual PMU Optimization
##### From: Wei Wang <wei.w.wang@intel.com>

```c

This patch series optimizes the Intel PMU virtualization by reducing the
PMU virtualization overhead and providing guests with accurate PMU
statistics.

The differences of the traditional approach and the optimized apporach
are depicted in the figures here:
https://github.com/weiwangwork/vPMU/blob/master/vPMU%20Optimization.pdf

The traditional approach of PMU virtualization is host perf event oriented.
The KVM vPMU layer sits on top of the host perf subsystem and each guest's
update to the vPMU is translated into a new host perf event, which needs
to go through the host perf software stack (e.g. releasing the old perf
event, re-creating a new one and getting it rescheduled to a hardware perf
counter) for a reconfiguration.

With this optimization, we intend to make the virtualization layer to be
register oriented. The KVM vPMU layer is moved down to directly sit on the
hardware perf counters. The guest accesses to the vPMU registers can be
directly applied to the related hardware counter by the vPMU. It can
reduce the virtualization overhead from around 2500000ns to 400ns.
(Tested on Intel(R) Xeon(R) CPU E5-2699 v4 @ 2.20GHz, and added host
booting parameter "nowatchdog" to avoid the noise from watchdog_hld)

We still need the vPMU to get the ownership of the physical perf counters
from the host perf core. The guest used counters are taken from the host
perf core via x86_perf_mask_perf_counters, which in most cases is a
bit-setting of the guest mask.

This series currently covers the basic perf counter virtualization. Other
features, such as pebs and lbr, will come after this series.

Wei Wang (8):
  perf/x86: add support to mask counters from host
  perf/x86/intel: add pmi callback support
  KVM/x86/vPMU: optimize intel vPMU
  KVM/x86/vPMU: support msr switch on vmx transitions
  KVM/x86/vPMU: intel_pmu_read_pmc
  KVM/x86/vPMU: remove some unused functions
  KVM/x86/vPMU: save/restore guest perf counters on vCPU switching
  KVM/x86/vPMU: return the counters to host if guest is torn down

 arch/x86/events/core.c            |  47 ++++
 arch/x86/events/intel/core.c      |  65 ++----
 arch/x86/events/perf_event.h      |  10 +-
 arch/x86/include/asm/kvm_host.h   |  13 ++
 arch/x86/include/asm/perf_event.h |  16 +-
 arch/x86/kvm/pmu.c                |  15 ++
 arch/x86/kvm/pmu.h                |   7 +
 arch/x86/kvm/pmu_intel.c          | 448 +++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx.c                |   6 +-
 arch/x86/kvm/x86.c                |   6 +
 include/linux/kvm_host.h          |   1 +
 virt/kvm/kvm_main.c               |   3 +
 12 files changed, 416 insertions(+), 221 deletions(-)
```
