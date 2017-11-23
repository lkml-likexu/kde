

#### [PATCH v8 00/16] Add support for Hygon Dhyana Family 18h processor
##### From: Pu Wen <puwen@hygon.cn>

```c

As a new x86 CPU Vendor, Chengdu Haiguang IC Design Co., Ltd (Hygon)
is a Joint Venture between AMD and Haiguang Information Technology Co.,
Ltd., and aims at providing high performance x86 processor for China
server market.

The first generation Hygon's processor(Dhyana) originates from AMD
technology and shares most of the architecture with AMD's family 17h,
but with different CPU Vendor ID("HygonGenuine")/PCIE Device Vendor ID
(0x1D94)/Family series number (Family 18h).

To enable the support of Linux kernel to Hygon's CPU, we added a new
vendor type (X86_VENDOR_HYGON, with value of 9) in arch/x86/include/
asm/processor.h, and shared most of kernel support codes with AMD
family 17h.

As Hygon will negotiate with AMD to make sure that only Hygon will
use family 18h, so try to minimize code modification and share most
codes with AMD under this consideration.

This patch series have been applied and tested successfully on Hygon
Dhyana SoC silicon. Also tested on AMD EPYC (Family 17h) processor,
it works fine and makes no harm to the existing codes.


v7->v8:
  - Fix the issue that patch x86/pci may cause LKP boot test failure
    on some Intel platform.

v6->v7:
  - Rebased on 4.19-rc4 and tested against it.
  - Add Reviewed-by from Borislav Petkov for patches x86/cpu,
    x86/cpu/mtrr, perf/x86, x86/pci, x86/apic, x86/mce.
  - Refine the patch descriptions and fix some typos.
  - Remove unneeded vendor checking for patch x86/apic.
  - Restore the user-visible pr_err string in patch x86/bugs.

v5->v6:
  - Rebased on 4.19-rc3 and tested against it.
  - Add Reviewed-by from Borislav Petkov for cacheinfo, smpboot,
    alternative and kvm.
  - Rework the patch subjects and patch descriptions.
  - Rework vendor checking for some patches to minimize the code
    modification.

v4->v5:
  - Rebased on 4.19-rc1 and tested against it.
  - Add Reviewed-by from Boris Ostrovsky for Xen.
  - Rework EDAC patch without vendor checking for minimal modification.

v3->v4:
  - Rebased on 4.18.3 and tested against it.
  - Merge patches 05/17 perfctr and 10/17 events in v3 to patch 05/16
    PMU for better patch function group.
  - Add hygon_get_topology_early() in patch 01/16.
  - Rework vendor checking and refine coding style.
  - Add Acked-by from Bjorn Helgaas for pci.
  - Add Acked-by from Rafael J. Wysocki for cpufreq and acpi.

v2->v3:
  - Rebased on 4.18-rc8 and tested against it.
  - Rework vendor checking codes to improve consistency.

v1->v2:
  - Rebased on 4.18-rc6 and tested against it.
  - Split the patch set to small series of patches.
  - Rework patch descriptions.
  - Create a separated arch/x86/kernel/cpu/hygon.c for Dhyana CPU
    initialization to reduce long-term maintenance effort.


Pu Wen (16):
  x86/cpu: Create Hygon Dhyana architecture support file
  x86/cpu: Get cache info and setup cache cpumap for Hygon Dhyana
  x86/cpu/mtrr: Support TOP_MEM2 and get MTRR number
  x86/smpboot: SMP init no delay and not flush caches before sleep
  perf/x86: Add Hygon Dhyana support to PMU infrastructure
  x86/alternative: Init ideal_nops for Hygon Dhyana
  x86/pci: Add Hygon Dhyana support to PCI and north bridge
  x86/apic: Add Hygon Dhyana support to APIC
  x86/bugs: Add mitigation to spectre and no meltdown for Hygon Dhyana
  x86/mce: Add Hygon Dhyana support to MCE infrastructure
  x86/kvm: Add Hygon Dhyana support to KVM infrastructure
  x86/xen: Add Hygon Dhyana support to Xen
  ACPI, x86: Add Hygon Dhyana support
  cpufreq, x86: Add Hygon Dhyana support
  EDAC, amd64: Add Hygon Dhyana support
  cpupower, x86: Add Hygon Dhyana support

 MAINTAINERS                                        |   6 +
 arch/x86/Kconfig.cpu                               |  14 +
 arch/x86/events/amd/core.c                         |   4 +
 arch/x86/events/amd/uncore.c                       |  20 +-
 arch/x86/events/core.c                             |   4 +
 arch/x86/include/asm/amd_nb.h                      |   3 +
 arch/x86/include/asm/cacheinfo.h                   |   1 +
 arch/x86/include/asm/kvm_emulate.h                 |   4 +
 arch/x86/include/asm/mce.h                         |   2 +
 arch/x86/include/asm/processor.h                   |   3 +-
 arch/x86/include/asm/virtext.h                     |   5 +-
 arch/x86/kernel/alternative.c                      |   4 +
 arch/x86/kernel/amd_nb.c                           |  47 ++-
 arch/x86/kernel/apic/apic.c                        |   7 +
 arch/x86/kernel/apic/probe_32.c                    |   1 +
 arch/x86/kernel/cpu/Makefile                       |   1 +
 arch/x86/kernel/cpu/bugs.c                         |   4 +-
 arch/x86/kernel/cpu/cacheinfo.c                    |  31 +-
 arch/x86/kernel/cpu/common.c                       |   1 +
 arch/x86/kernel/cpu/cpu.h                          |   1 +
 arch/x86/kernel/cpu/hygon.c                        | 411 +++++++++++++++++++++
 arch/x86/kernel/cpu/mcheck/mce-severity.c          |   3 +-
 arch/x86/kernel/cpu/mcheck/mce.c                   |  20 +-
 arch/x86/kernel/cpu/mtrr/cleanup.c                 |   3 +-
 arch/x86/kernel/cpu/mtrr/mtrr.c                    |   2 +-
 arch/x86/kernel/cpu/perfctr-watchdog.c             |   2 +
 arch/x86/kernel/smpboot.c                          |   4 +-
 arch/x86/kvm/emulate.c                             |  11 +-
 arch/x86/pci/amd_bus.c                             |   6 +-
 arch/x86/xen/pmu.c                                 |  12 +-
 drivers/acpi/acpi_pad.c                            |   1 +
 drivers/acpi/processor_idle.c                      |   1 +
 drivers/cpufreq/acpi-cpufreq.c                     |   5 +
 drivers/cpufreq/amd_freq_sensitivity.c             |   9 +-
 drivers/edac/amd64_edac.c                          |   8 +-
 drivers/edac/mce_amd.c                             |   4 +-
 include/linux/pci_ids.h                            |   2 +
 tools/power/cpupower/utils/cpufreq-info.c          |   6 +-
 tools/power/cpupower/utils/helpers/amd.c           |   4 +-
 tools/power/cpupower/utils/helpers/cpuid.c         |   8 +-
 tools/power/cpupower/utils/helpers/helpers.h       |   2 +-
 tools/power/cpupower/utils/helpers/misc.c          |   2 +-
 .../cpupower/utils/idle_monitor/mperf_monitor.c    |   3 +-
 43 files changed, 644 insertions(+), 48 deletions(-)
 create mode 100644 arch/x86/kernel/cpu/hygon.c
```
