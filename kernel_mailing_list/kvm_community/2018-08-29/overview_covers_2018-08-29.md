

#### [PATCH v5 00/16] Add support for Hygon Dhyana Family 18h processor
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
 arch/x86/kernel/cpu/hygon.c                        | 411 +++++++++++++++++++++
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
 drivers/edac/amd64_edac.c                          |  20 +-
 drivers/edac/amd64_edac.h                          |   4 +
 drivers/edac/mce_amd.c                             |   4 +-
 include/linux/pci_ids.h                            |   2 +
 tools/power/cpupower/utils/cpufreq-info.c          |   6 +-
 tools/power/cpupower/utils/helpers/amd.c           |   6 +-
 tools/power/cpupower/utils/helpers/cpuid.c         |   8 +-
 tools/power/cpupower/utils/helpers/helpers.h       |   2 +-
 tools/power/cpupower/utils/helpers/misc.c          |   3 +-
 .../cpupower/utils/idle_monitor/mperf_monitor.c    |   3 +-
 46 files changed, 690 insertions(+), 69 deletions(-)
 create mode 100644 arch/x86/kernel/cpu/hygon.c
```
#### [kvm-unit-tests PATCH v2 0/5] s390x: simple DXC test
##### From: David Hildenbrand <david@redhat.com>

```c

The DXC was not handled by TCG correctly (and I have a patch series on
the QEMU list, which fixes that).

Add a simple test case that forces a DATA exception and verifies that
the DXC (0xff) is written to the right locations. One time with and
one time without AFP.

While at it, I found one bug related to storing/saving floating point
registers during interrupts and added one cleanup.

Tested under KVM and under TCG.

v1 -> v2:
- Added "s390x: fix spelling of "initial""
- Minor style + spelling fixes

David Hildenbrand (5):
  s390x: user ctl_set/clear_bit for low address protection
  s390x: fix storing/loading fregs to right address
  s390x: fix spelling of "initial"
  s390x: save/restore cr0 in IRQ handlers
  s390x: test if the DXC is correctly stored

 lib/s390x/asm-offsets.c   |  1 +
 lib/s390x/asm/arch_def.h  |  4 ++-
 lib/s390x/asm/float.h     | 51 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/asm/interrupt.h | 12 ++-------
 s390x/cstart64.S          | 19 ++++++++++-----
 s390x/emulator.c          | 34 ++++++++++++++++++++++++++
 6 files changed, 104 insertions(+), 17 deletions(-)
 create mode 100644 lib/s390x/asm/float.h
```
#### [PATCH v3 0/4] x86: Fix SEV guest regression
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

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (4):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: fix sme_populate_pgd() to update page flags
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute in shared variables

 arch/x86/include/asm/mem_encrypt.h |   6 +
 arch/x86/kernel/head64.c           |  11 ++
 arch/x86/kernel/kvmclock.c         |  30 ++++-
 arch/x86/kernel/vmlinux.lds.S      |  17 +++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 5 files changed, 229 insertions(+), 67 deletions(-)
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
```
#### [PATCH 0/2] Propagate accurate MSR access failures to userspace
##### From: Peter Shier <pshier@google.com>

```c

KVM_GET/SET_MSRS ioctls do not enable userspace clients to differentiate
between ioctl execution errors (e.g. bad pointer, memory allocation
failure) and MSR access errors (e.g. bad MSR parameter, unknown MSR).

This series repurposes kvm_msrs.pad to return the error from the first
failed msr access. It enables callers to use a sequence such as:

struct kvm_msrs msrs;
... init msrs ...
r = ioctl(vcpu_fd, KVM_GET_MSRS, &msrs);
if (r < 0) {
      	check errno for ioctl execution error
} else if (r < msrs.nmsrs) {
        if r > 0
	        reading msrs.entries[0]..msrs.entries[r-1] succeeded
        reading msrs.entries[r] failed
	msrs.errno has the reason
}

The second patch changes code that handles ranges of MSRs to return -ENOENT
when it encounters an unknown MSR. Prior to this it was not possible for
userspace to differentiate between unknown MSRs and other MSR access
errors.

The patches do not change any existing API contracts or guest-visible
exceptions.

Peter Shier (2):
  kvm: x86: propagate KVM_GET/SET_MSRS failures to userspace
  kvm: x86: differentiate unrecognized MSRs from errors

 Documentation/virtual/kvm/api.txt | 12 ++++++++---
 arch/x86/include/uapi/asm/kvm.h   |  2 +-
 arch/x86/kvm/hyperv.c             | 16 +++++++--------
 arch/x86/kvm/lapic.c              |  2 +-
 arch/x86/kvm/mtrr.c               | 10 ++++++---
 arch/x86/kvm/pmu_amd.c            | 24 ++++++++++++----------
 arch/x86/kvm/pmu_intel.c          |  5 +++--
 arch/x86/kvm/vmx.c                |  4 ++--
 arch/x86/kvm/x86.c                | 34 +++++++++++++++++++------------
 9 files changed, 65 insertions(+), 44 deletions(-)
```
