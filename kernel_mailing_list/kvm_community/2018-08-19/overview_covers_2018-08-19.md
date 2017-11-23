

#### [PATCH v4 00/16] Add support for Hygon Dhyana Family 18h processor
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

This patch series have been applied and tested successfully in Hygon's
Dhyana SoC silicon. Also tested on AMD's EPYC (Family 17h) processor
works fine and makes no harm to existing codes.


v3->v4:
  - Rebased on 4.18.3 and tested against it.
  - Merge patchs 05/17 perfctr and 10/17 events in v3 to patch 05/16
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
  - Split the patchset to small series of patches.
  - Rework patch descriptions.
  - Create a separated arch/x86/kernel/cpu/hygon.c for Dhyana CPU
    initialization to reduce long-term maintenance effort.


Pu Wen (16):
  x86/cpu: create Dhyana init file and register new cpu_dev to system
  x86/cache: get cache size/leaves and setup cache cpumap for Dhyana
  x86/mtrr: get MTRR number and support TOP_MEM2
  x86/smpboot: smp init nodelay and no flush caches before sleep
  x86/pmu: enable Hygon support to PMU infrastructure
  x86/nops: init ideal_nops for Hygon
  x86/pci: add Hygon PCI vendor and northbridge support
  x86/apic: add modern APIC support for Hygon
  x86/bugs: add lfence mitigation to spectre v2 and no meltdown for
    Hygon
  x86/mce: enable Hygon support to MCE infrastructure
  x86/kvm: enable Hygon support to KVM infrastructure
  x86/xen: enable Hygon support to Xen
  driver/acpi: enable Hygon support to ACPI driver
  driver/cpufreq: enable Hygon support to cpufreq driver
  driver/edac: enable Hygon support to AMD64 EDAC driver
  tools/cpupower: enable Hygon support to cpupower tool

 MAINTAINERS                                        |   6 +
 arch/x86/Kconfig                                   |   2 +-
 arch/x86/Kconfig.cpu                               |  13 +
 arch/x86/events/amd/core.c                         |   6 +
 arch/x86/events/amd/uncore.c                       |  15 +-
 arch/x86/events/core.c                             |   4 +
 arch/x86/include/asm/cacheinfo.h                   |   1 +
 arch/x86/include/asm/kvm_emulate.h                 |   4 +
 arch/x86/include/asm/mce.h                         |   5 +
 arch/x86/include/asm/nospec-branch.h               |   4 +-
 arch/x86/include/asm/processor.h                   |   3 +-
 arch/x86/include/asm/virtext.h                     |   5 +-
 arch/x86/kernel/alternative.c                      |   4 +
 arch/x86/kernel/amd_nb.c                           |  51 ++-
 arch/x86/kernel/apic/apic.c                        |  19 +-
 arch/x86/kernel/apic/probe_32.c                    |   1 +
 arch/x86/kernel/cpu/Makefile                       |   1 +
 arch/x86/kernel/cpu/bugs.c                         |  28 +-
 arch/x86/kernel/cpu/cacheinfo.c                    |  31 +-
 arch/x86/kernel/cpu/common.c                       |   1 +
 arch/x86/kernel/cpu/cpu.h                          |   1 +
 arch/x86/kernel/cpu/hygon.c                        | 409 +++++++++++++++++++++
 arch/x86/kernel/cpu/mcheck/mce-severity.c          |   3 +-
 arch/x86/kernel/cpu/mcheck/mce.c                   |  21 +-
 arch/x86/kernel/cpu/mtrr/cleanup.c                 |   3 +-
 arch/x86/kernel/cpu/mtrr/generic.c                 |   5 +-
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
 drivers/edac/amd64_edac.c                          |  52 ++-
 drivers/edac/amd64_edac.h                          |   5 +
 drivers/edac/mce_amd.c                             |  15 +-
 include/linux/pci_ids.h                            |   2 +
 tools/power/cpupower/utils/cpufreq-info.c          |   6 +-
 tools/power/cpupower/utils/helpers/amd.c           |   6 +-
 tools/power/cpupower/utils/helpers/cpuid.c         |   8 +-
 tools/power/cpupower/utils/helpers/helpers.h       |   2 +-
 tools/power/cpupower/utils/helpers/misc.c          |   3 +-
 .../cpupower/utils/idle_monitor/mperf_monitor.c    |   3 +-
 46 files changed, 732 insertions(+), 69 deletions(-)
 create mode 100644 arch/x86/kernel/cpu/hygon.c
```
