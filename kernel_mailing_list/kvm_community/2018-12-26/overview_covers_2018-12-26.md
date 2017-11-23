

#### [PATCH v1 0/8] This patch-set is to enable kvm Guest OS CET support.
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

Control-flow Enforcement Technology (CET) provides protection against
return/jump-oriented programming (ROP) attacks. To make kvm Guest OS
own the capability, this patch-set is required. It enables CET related
CPUID report, xsaves/xrstors, vmx entry configuration etc for Guest OS.

PATCH 1/3/4: Enable CET support in VMCS.
PATCH 2    : Define CR4.CET master enable bit.
PATCH 5    : Enable xsave components for CET in XSS.
PATCH 6/7/8: Report CET feature support in CPUID.
 
Yang Weijiang (8):
  kvm:vmx  Introduce CET related VMCS field definitions.
  kvm:  Define CR4.CET[bit 23] (master enable bit) for guest OS.
  kvm:vmx  Enable loading CET state bit while guest CR4.CET is being
    set.
  kvm:vmx  Pass through host CET related MSRs to Guest.
  kvm:x86  Enable MSR_IA32_XSS bit 11 and 12 for CET xsaves/xrstors.
  kvm:cpuid  Add CPUID support for CET xsaves component query.
  kvm:cpuid  Fix xsaves area size calculation for CPUID.(EAX=0xD,ECX=1).
  kvm:cpuid  Report CET SHSTK and IBT support in CPUID.(EAX=0x7,ECX=0).

 arch/x86/include/asm/kvm_host.h |  3 ++-
 arch/x86/include/asm/vmx.h      |  8 +++++++
 arch/x86/kvm/cpuid.c            | 23 +++++++++++++-------
 arch/x86/kvm/vmx.c              | 37 ++++++++++++++++++++++++++++++---
 4 files changed, 60 insertions(+), 11 deletions(-)
```
#### [Qemu-devel][PATCH 0/4] This patch-set is to enable Guest CET
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

Control-flow Enforcement Technology (CET) provides protection against
return/jump-oriented programming (ROP) attacks. To make kvm Guest OS
own the capability, this patch-set is required. It enables CET related
CPUID report and xsaves/xrstors support etc in qemu.

Yang Weijiang (4):
  Add CET xsaves/xrstors related macros and structures.
  Add CET SHSTK and IBT CPUID feature-word definitions.
  Add hepler functions for CPUID xsave area size calculation.
  Report CPUID xsave area support for CET.

 target/i386/cpu.c | 67 ++++++++++++++++++++++++++++++++++++++++++++---
 target/i386/cpu.h | 36 ++++++++++++++++++++++++-
 2 files changed, 99 insertions(+), 4 deletions(-)
```
#### [PATCH v4 00/10] Guest LBR Enabling
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
v3->v4:
    - perf/x86:
        - Patch 1: change the lbr msr variable type to "unsigned int";
        - Patch 6: add a "no_counter" boolean attr to let callers
          explicitly tell the perf core to not allocate counters for the
          event;
        - Patch 7: change "cpuc->vcpu_lbr" from "boolean" to "u8", and add
          the PF_VCPU and is_kernel_event checks befoer setting it;
        - Patch 8: add the LBR_SELECT save/restore on vCPU switching;
	- Patch 9: move lbr_select_user_callstack to .h, instead of
          exporting it;

    - KVM/x86:
        - Patch 3: use "cap->args[0]" to enable/disable the lbr feature
          from userspace;
        - Patch 4: forbid the enabling the guest lbr when the host and
          guest see different lbr stack entries;
        - Patch 10: in guest_access_lbr_msr, pass through the lbr stack
          only when it has been passed through (i.e. add the check
          !vcpu->arch.lbr_used).
previous:
https://lkml.org/lkml/2018/9/20/507

Like Xu (1):
  KVM/x86/vPMU: Add APIs to support host save/restore the guest lbr
    stack

Wei Wang (9):
  perf/x86: fix the variable type of the LBR MSRs
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: intel_pmu_lbr_enable
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  perf/x86: no counter allocation support
  perf/x86: save/restore LBR_SELECT on vCPU switching
  perf/x86: function to check lbr user callstack mode
  KVM/x86/lbr: lazy save the guest lbr stack

 arch/x86/events/core.c            |  12 +++
 arch/x86/events/intel/lbr.c       |  82 ++++++++---------
 arch/x86/events/perf_event.h      |   6 +-
 arch/x86/include/asm/kvm_host.h   |   7 ++
 arch/x86/include/asm/perf_event.h |  64 +++++++++++++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/cpuid.h              |   8 ++
 arch/x86/kvm/pmu.c                |   8 ++
 arch/x86/kvm/pmu.h                |  10 +++
 arch/x86/kvm/pmu_intel.c          | 183 ++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx.c                | 147 ++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                |  14 +++
 include/linux/perf_event.h        |  12 +++
 include/uapi/linux/kvm.h          |   1 +
 include/uapi/linux/perf_event.h   |   3 +-
 kernel/events/core.c              |   7 --
 16 files changed, 514 insertions(+), 52 deletions(-)
```
#### [RFC][PATCH v2 00/21] PMEM NUMA node and hotness accounting/migration
##### From: Fengguang Wu <fengguang.wu@intel.com>

```c

This is an attempt to use NVDIMM/PMEM as volatile NUMA memory that's
transparent to normal applications and virtual machines.

The code is still in active development. It's provided for early design review.

Key functionalities:

1) create and describe PMEM NUMA node for NVDIMM memory
2) dumb /proc/PID/idle_pages interface, for user space driven hot page accounting
3) passive kernel cold page migration in page reclaim path
4) improved move_pages() for active user space hot/cold page migration

(1) is foundation for transparent usage of NVDIMM for normal apps and virtual
machines. (2-4) enable auto placing hot pages in DRAM for better performance.
A user space migration daemon is being built based on this kernel patchset to
make the full vertical solution.

Base kernel is v4.20 . The patches are not suitable for upstreaming in near
future -- some are quick hacks, some others need more works. However they are
complete enough to demo the necessary kernel changes for the proposed app&VM
transparent NVDIMM volatile use model.

The interfaces are far from finalized. They kind of illustrate what would be
necessary for creating a user space driven solution. The exact forms will ask
for more thoughts and inputs. We may adopt HMAT based solution for NUMA node
related interface when they are ready. The /proc/PID/idle_pages interface is
standalone but non-trivial. Before upstreaming some day, it's expected to take
long time to collect various real use cases and feedbacks, so as to refine and
stabilize the format.

Create PMEM numa node

	[PATCH 01/21] e820: cheat PMEM as DRAM

Mark numa node as DRAM/PMEM

	[PATCH 02/21] acpi/numa: memorize NUMA node type from SRAT table
	[PATCH 03/21] x86/numa_emulation: fix fake NUMA in uniform case
	[PATCH 04/21] x86/numa_emulation: pass numa node type to fake nodes
	[PATCH 05/21] mmzone: new pgdat flags for DRAM and PMEM
	[PATCH 06/21] x86,numa: update numa node type
	[PATCH 07/21] mm: export node type {pmem|dram} under /sys/bus/node

Point neighbor DRAM/PMEM to each other

	[PATCH 08/21] mm: introduce and export pgdat peer_node
	[PATCH 09/21] mm: avoid duplicate peer target node

Standalone zonelist for DRAM and PMEM nodes

	[PATCH 10/21] mm: build separate zonelist for PMEM and DRAM node

Keep page table pages in DRAM

	[PATCH 11/21] kvm: allocate page table pages from DRAM
	[PATCH 12/21] x86/pgtable: allocate page table pages from DRAM

/proc/PID/idle_pages interface for virtual machine and normal tasks

	[PATCH 13/21] x86/pgtable: dont check PMD accessed bit
	[PATCH 14/21] kvm: register in mm_struct
	[PATCH 15/21] ept-idle: EPT walk for virtual machine
	[PATCH 16/21] mm-idle: mm_walk for normal task
	[PATCH 17/21] proc: introduce /proc/PID/idle_pages
	[PATCH 18/21] kvm-ept-idle: enable module

Mark hot pages

	[PATCH 19/21] mm/migrate.c: add move_pages(MPOL_MF_SW_YOUNG) flag

Kernel DRAM=>PMEM migration

	[PATCH 20/21] mm/vmscan.c: migrate anon DRAM pages to PMEM node
	[PATCH 21/21] mm/vmscan.c: shrink anon list if can migrate to PMEM

 arch/x86/include/asm/numa.h    |    2 
 arch/x86/include/asm/pgalloc.h |   10 
 arch/x86/include/asm/pgtable.h |    3 
 arch/x86/kernel/e820.c         |    3 
 arch/x86/kvm/Kconfig           |   11 
 arch/x86/kvm/Makefile          |    4 
 arch/x86/kvm/ept_idle.c        |  841 +++++++++++++++++++++++++++++++
 arch/x86/kvm/ept_idle.h        |  116 ++++
 arch/x86/kvm/mmu.c             |   12 
 arch/x86/mm/numa.c             |    3 
 arch/x86/mm/numa_emulation.c   |   30 +
 arch/x86/mm/pgtable.c          |   22 
 drivers/acpi/numa.c            |    5 
 drivers/base/node.c            |   21 
 fs/proc/base.c                 |    2 
 fs/proc/internal.h             |    1 
 fs/proc/task_mmu.c             |   54 +
 include/linux/mm_types.h       |   11 
 include/linux/mmzone.h         |   38 +
 mm/mempolicy.c                 |   14 
 mm/migrate.c                   |   13 
 mm/page_alloc.c                |   77 ++
 mm/pagewalk.c                  |    1 
 mm/vmscan.c                    |   38 +
 virt/kvm/kvm_main.c            |    3 
 25 files changed, 1306 insertions(+), 29 deletions(-)

V1 patches: https://lkml.org/lkml/2018/9/2/13

Regards,
Fengguang
Signed-off-by: Liu Jingqi <jingqi.liu@intel.com>
Signed-off-by: Fengguang Wu <fengguang.wu@intel.com>
```
