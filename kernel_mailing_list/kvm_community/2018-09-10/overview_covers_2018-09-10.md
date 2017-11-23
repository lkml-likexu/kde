

#### [PATCH 00/13] x86/KVM/Hyper-v: Add HV ept tlb range flush hypercall
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c

For nested memory virtualization, Hyper-v doesn't set write-protect
L1 hypervisor EPT page directory and page table node to track changes 
while it relies on guest to tell it changes via HvFlushGuestAddressLlist
hypercall. HvFlushGuestAddressLlist hypercall provides a way to flush
EPT page table with ranges which are specified by L1 hypervisor.

If L1 hypervisor uses INVEPT or HvFlushGuestAddressSpace hypercall to
flush EPT tlb, Hyper-V will invalidate associated EPT shadow page table
and sync L1's EPT table when next EPT page fault is triggered.
HvFlushGuestAddressLlist hypercall helps to avoid such redundant EPT
page fault and synchronization of shadow page table.

Lan Tianyu (13):
  KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
  KVM/MMU: Add tlb flush with range helper function
  KVM: Replace old tlb flush function with new one to flush a specified
    range.
  KVM/MMU: Flush tlb directly in the kvm_handle_hva_range()
  KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()
  KVM/MMU: Flush tlb directly in kvm_mmu_zap_collapsible_spte()
  KVM: Add flush_link and parent_pte in the struct kvm_mmu_page
  KVM: Add spte's point in the struct kvm_mmu_page
  KVM/MMU: Replace tlb flush function with range list flush function
  x86/hyper-v: Add HvFlushGuestAddressList hypercall support
  x86/Hyper-v: Add trace in the
    hyperv_nested_flush_guest_mapping_range()
  KVM/VMX: Change hv flush logic when ept tables are mismatched.
  KVM/VMX: Add hv tlb range flush support

 arch/x86/hyperv/nested.c            | 111 +++++++++++++++++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h  |  17 +++++
 arch/x86/include/asm/kvm_host.h     |  10 +++
 arch/x86/include/asm/mshyperv.h     |   7 ++
 arch/x86/include/asm/trace/hyperv.h |  14 ++++
 arch/x86/kvm/mmu.c                  | 146 +++++++++++++++++++++++++++++++-----
 arch/x86/kvm/paging_tmpl.h          |  16 +++-
 arch/x86/kvm/vmx.c                  |  41 +++++++---
 8 files changed, 331 insertions(+), 31 deletions(-)
```
#### [PATCH v6 00/16] Add support for Hygon Dhyana Family 18h processor
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
  x86/cpu: Create Hygon Dhyana architecture support file
  x86/cpu: Get cache info and setup cache cpumap for Hygon Dhyana
  x86/cpu/mtrr: Support TOP_MEM2 and get MTRR number
  x86/smpboot: SMP init nodelay and not flush caches before sleep
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
 arch/x86/include/asm/cacheinfo.h                   |   1 +
 arch/x86/include/asm/kvm_emulate.h                 |   4 +
 arch/x86/include/asm/mce.h                         |   2 +
 arch/x86/include/asm/processor.h                   |   3 +-
 arch/x86/include/asm/virtext.h                     |   5 +-
 arch/x86/kernel/alternative.c                      |   4 +
 arch/x86/kernel/amd_nb.c                           |  47 ++-
 arch/x86/kernel/apic/apic.c                        |  13 +-
 arch/x86/kernel/apic/probe_32.c                    |   1 +
 arch/x86/kernel/cpu/Makefile                       |   1 +
 arch/x86/kernel/cpu/bugs.c                         |   6 +-
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
 42 files changed, 646 insertions(+), 51 deletions(-)
 create mode 100644 arch/x86/kernel/cpu/hygon.c
```
#### [PATCH v7 0/5] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Changes since v6:
 - improve commit messages
 - rename free_decrypted_mem -> mem_encrypt_free_decrypted_mem

Changes since v5:
 - rename hvclock_boot_dec -> hvclock_boot_aux.
 - rename section from .data..decrypted_aux -> .data..decrypted.aux.
 - use NR_CPUS instead of random number elements in hv_clock_aux variable.

Changes since v4:
 - define few static pages in .data..decrypted which can be used
   for cpus > HVC_BOOT_ARRAY_SIZE when SEV is active.

Changes since v3:
 - commit message improvements (based on Sean's feedback)

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (5):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: Enhance sme_populate_pgd() to update page flags
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute in shared variables
  x86/kvm: Avoid dynamic allocation of pvclock data when SEV is active

 arch/x86/include/asm/mem_encrypt.h |  10 ++
 arch/x86/kernel/head64.c           |  11 ++
 arch/x86/kernel/kvmclock.c         |  18 ++-
 arch/x86/kernel/vmlinux.lds.S      |  20 ++++
 arch/x86/mm/init.c                 |   3 +
 arch/x86/mm/mem_encrypt.c          |  10 ++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 7 files changed, 240 insertions(+), 64 deletions(-)
```
