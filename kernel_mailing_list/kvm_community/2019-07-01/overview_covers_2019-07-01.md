

#### [PATCH v5 0/2] clocksource/drivers: Create new Hyper-V clocksource
##### From: Michael Kelley <mikelley@microsoft.com>

```c

This patch series moves Hyper-V clock/timer code to a separate Hyper-V
clocksource driver. Previously, Hyper-V clock/timer code and data
structures were mixed in with other Hyper-V code in the ISA independent
drivers/hv code as well as in ISA dependent code. The new Hyper-V
clocksource driver is ISA agnostic, with a just few dependencies on
ISA specific functions. The patch series does not change any behavior
or functionality -- it only reorganizes the existing code and fixes up
the linkages. A few places outside of Hyper-V code are fixed up to use
the new #include file structure.

This restructuring is in response to Marc Zyngier's review comments
on supporting Hyper-V running on ARM64, and is a good idea in general.
It increases the amount of code shared between the x86 and ARM64
architectures, and reduces the size of the new code for supporting
Hyper-V on ARM64. A new version of the Hyper-V on ARM64 patches will
follow once this clocksource restructuring is accepted.

The code is diff'ed against the upstream tip tree:
git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git timers/vdso

Changes in v5:
* Revised commit summaries [Thomas Gleixner]
* Removed call to clockevents_unbind_device() [Thomas Gleixner]
* Restructured hv_init_clocksource() [Thomas Gleixner]
* Various other small code cleanups [Thomas Gleixner]

Changes in v4:
* Revised commit messages
* Rebased to upstream tip tree

Changes in v3:
* Removed boolean argument to hv_init_clocksource(). Always call
sched_clock_register, which is needed on ARM64 but a no-op on x86.
* Removed separate cpuhp setup in hv_stimer_alloc() and instead
directly call hv_stimer_init() and hv_stimer_cleanup() from
corresponding VMbus functions.  This more closely matches original
code and avoids clocksource stop/restart problems on ARM64 when
VMbus code denies CPU offlining request.

Changes in v2:
* Revised commit short descriptions so the distinction between
the first and second patches is clearer [GregKH]
* Renamed new clocksource driver files and functions to use
existing "timer" and "stimer" names instead of introducing
"syntimer". [Vitaly Kuznetsov]
* Introduced CONFIG_HYPER_TIMER to fix build problem when
CONFIG_HYPERV=m [Vitaly Kuznetsov]
* Added "Suggested-by: Marc Zyngier"

Michael Kelley (2):
  clocksource/drivers: Make Hyper-V clocksource ISA agnostic
  clocksource/drivers: Continue making Hyper-V clocksource ISA agnostic

 MAINTAINERS                              |   2 +
 arch/x86/entry/vdso/vma.c                |   2 +-
 arch/x86/hyperv/hv_init.c                |  91 +--------
 arch/x86/include/asm/hyperv-tlfs.h       |   6 +
 arch/x86/include/asm/mshyperv.h          |  81 +-------
 arch/x86/include/asm/vdso/gettimeofday.h |   2 +-
 arch/x86/kernel/cpu/mshyperv.c           |   4 +-
 arch/x86/kvm/x86.c                       |   1 +
 drivers/clocksource/Makefile             |   1 +
 drivers/clocksource/hyperv_timer.c       | 339 +++++++++++++++++++++++++++++++
 drivers/hv/Kconfig                       |   3 +
 drivers/hv/hv.c                          | 156 +-------------
 drivers/hv/hv_util.c                     |   1 +
 drivers/hv/hyperv_vmbus.h                |   3 -
 drivers/hv/vmbus_drv.c                   |  42 ++--
 include/clocksource/hyperv_timer.h       | 105 ++++++++++
 16 files changed, 503 insertions(+), 336 deletions(-)
 create mode 100644 drivers/clocksource/hyperv_timer.c
 create mode 100644 include/clocksource/hyperv_timer.h
```
#### [PATCH 0/4] kvm: x86: introduce CONFIG_KVM_DEBUG
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c

This series introduce CONFIG_KVM_DEBUG, using which we can make
the invoking *_debug in KVM simly and uniform.

FYI: the former discussion can been found in:
https://www.spinics.net/lists/kvm/msg187026.html

Yi Wang (4):
  kvm: x86: Add CONFIG_KVM_DEBUG
  kvm: x86: allow set apic and ioapic debug dynamically
  kvm: x86: replace MMU_DEBUG with CONFIG_KVM_DEBUG
  kvm: x86: convert TSC pr_debugs to be gated by CONFIG_KVM_DEBUG

 arch/x86/kvm/Kconfig  |  8 ++++++++
 arch/x86/kvm/ioapic.c |  2 +-
 arch/x86/kvm/lapic.c  |  5 ++++-
 arch/x86/kvm/mmu.c    |  5 ++---
 arch/x86/kvm/x86.c    | 18 ++++++++++++------
 5 files changed, 27 insertions(+), 11 deletions(-)
```
#### [PATCH v3 00/15] hw/i386/pc: Do not restrict the fw_cfg functions to
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c

Hi,

This is my take at salvaging some NEMU good work.
Samuel worked in adding the fw_cfg device to the x86-virt NEMU machine.
This series is inspired by NEMU's commit 3cb92d080835 [0] and adapted
to upstream style. The result makes the upstream codebase more
modularizable.
There are very little logical changes, this is mostly a cleanup
refactor.

Since v2 [2]:
- Addressed MST comments from v2 (only patch #2 modified)
  - do not use unsigned for enum
  - do not add unuseful documentation

Since v1 [1]:
- Addressed Li and MST comments

$ git backport-diff -u v2
Key:
[----] : patches are identical
[####] : number of functional differences between upstream/downstream patch
[down] : patch is downstream-only
The flags [FC] indicate (F)unctional and (C)ontextual differences, respectively

001/15:[----] [--] 'hw/i386/pc: Use e820_get_num_entries() to access e820_entries'
002/15:[0131] [FC] 'hw/i386/pc: Extract e820 memory layout code'
003/15:[----] [--] 'hw/i386/pc: Use address_space_memory in place'
004/15:[----] [--] 'hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create'
005/15:[----] [--] 'hw/i386/pc: Pass the boot_cpus value by argument'
006/15:[----] [--] 'hw/i386/pc: Pass the apic_id_limit value by argument'
007/15:[----] [--] 'hw/i386/pc: Pass the CPUArchIdList array by argument'
008/15:[----] [--] 'hw/i386/pc: Let fw_cfg_init() use the generic MachineState'
009/15:[----] [--] 'hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument'
010/15:[----] [--] 'hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument'
011/15:[----] [--] 'hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()'
012/15:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument'
013/15:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a MachineState argument'
014/15:[----] [--] 'hw/i386/pc: Rename pc_build_feature_control() as generic fw_cfg_build_*'
015/15:[----] [--] 'hw/i386/pc: Extract the x86 generic fw_cfg code'

Regards,

Phil.

[0] https://github.com/intel/nemu/commit/3cb92d080835ac8d47c8b713156338afa33cff5c
[1] https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg05759.html
[2] https://lists.gnu.org/archive/html/qemu-devel/2019-06/msg02786.html

Philippe Mathieu-Daudé (15):
  hw/i386/pc: Use e820_get_num_entries() to access e820_entries
  hw/i386/pc: Extract e820 memory layout code
  hw/i386/pc: Use address_space_memory in place
  hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create
  hw/i386/pc: Pass the boot_cpus value by argument
  hw/i386/pc: Pass the apic_id_limit value by argument
  hw/i386/pc: Pass the CPUArchIdList array by argument
  hw/i386/pc: Let fw_cfg_init() use the generic MachineState
  hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument
  hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument
  hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()
  hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument
  hw/i386/pc: Let pc_build_feature_control() take a MachineState
    argument
  hw/i386/pc: Rename pc_build_feature_control() as generic
    fw_cfg_build_*
  hw/i386/pc: Extract the x86 generic fw_cfg code

 hw/i386/Makefile.objs        |   2 +-
 hw/i386/e820_memory_layout.c |  59 ++++++++++
 hw/i386/e820_memory_layout.h |  42 ++++++++
 hw/i386/fw_cfg.c             | 137 ++++++++++++++++++++++++
 hw/i386/fw_cfg.h             |   8 ++
 hw/i386/pc.c                 | 201 ++---------------------------------
 include/hw/i386/pc.h         |  11 --
 target/i386/kvm.c            |   1 +
 8 files changed, 256 insertions(+), 205 deletions(-)
 create mode 100644 hw/i386/e820_memory_layout.c
 create mode 100644 hw/i386/e820_memory_layout.h
```
#### [RFC v1 0/4] Some vfio-ccw fixes
##### From: Farhan Ali <alifm@linux.ibm.com>

```c

Hi,

While trying to chase down the problem regarding the stacktraces,
I have also found some minor problems in the code.

Would appreciate any review or feedback regarding them.

Thanks
Farhan 

Farhan Ali (4):
  vfio-ccw: Set orb.cmd.c64 before calling ccwchain_handle_ccw
  vfio-ccw: No need to call cp_free on an error in cp_init
  vfio-ccw: Set pa_nr to 0 if memory allocation fails for pa_iova_pfn
  vfio-ccw: Don't call cp_free if we are processing a channel program

 drivers/s390/cio/vfio_ccw_cp.c  | 12 ++++++------
 drivers/s390/cio/vfio_ccw_drv.c |  2 +-
 2 files changed, 7 insertions(+), 7 deletions(-)
```
#### [patch 0/5] cpuidle haltpoll driver and governor (v5)
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

The cpuidle-haltpoll driver with haltpoll governor allows the guest
vcpus to poll for a specified amount of time before halting.
This provides the following benefits to host side polling:

         1) The POLL flag is set while polling is performed, which allows
            a remote vCPU to avoid sending an IPI (and the associated
            cost of handling the IPI) when performing a wakeup.

         2) The VM-exit cost can be avoided.

The downside of guest side polling is that polling is performed
even with other runnable tasks in the host.

Results comparing halt_poll_ns and server/client application
where a small packet is ping-ponged:

host                                        --> 31.33
halt_poll_ns=300000 / no guest busy spin    --> 33.40   (93.8%)
halt_poll_ns=0 / guest_halt_poll_ns=300000  --> 32.73   (95.7%)

For the SAP HANA benchmarks (where idle_spin is a parameter
of the previous version of the patch, results should be the
same):

hpns == halt_poll_ns

                           idle_spin=0/   idle_spin=800/    idle_spin=0/
                           hpns=200000    hpns=0            hpns=800000
DeleteC06T03 (100 thread) 1.76           1.71 (-3%)        1.78   (+1%)
InsertC16T02 (100 thread) 2.14           2.07 (-3%)        2.18   (+1.8%)
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)	   1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)	   4.53   (-5%)

V2:

- Move from x86 to generic code (Paolo/Christian)
- Add auto-tuning logic (Paolo)
- Add MSR to disable host side polling (Paolo)

V3:

- Do not be specific about HLT VM-exit in the documentation (Ankur Arora)
- Mark tuning parameters static and __read_mostly (Andrea Arcangeli)
- Add WARN_ON if host does not support poll control (Joao Martins)
- Use sched_clock and cleanup haltpoll_enter_idle (Peter Zijlstra)
- Mark certain functions in kvm.c as static (kernel test robot)
- Remove tracepoints as they use RCU from extended quiescent state (kernel
test robot)

V4:
- Use a haltpoll governor, use poll_state.c poll code (Rafael J. Wysocki)

V5:
- Take latency requirement into consideration (Rafael J. Wysocki)
- Set target_residency/exit_latency to 1 (Rafael J. Wysocki)
- Do not load cpuidle driver if not virtualized (Rafael J. Wysocki)
```
