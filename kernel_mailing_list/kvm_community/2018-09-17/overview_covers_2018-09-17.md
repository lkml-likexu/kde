

#### [PATCH v5 00/18] kvm: arm64: Dynamic IPA and 52bit IPA
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c

The physical address space size for a VM (IPA size) on arm/arm64 is
limited to a static limit of 40bits. This series adds support for
using an IPA size specific to a VM, allowing to use a size supported
by the host (based on the host kernel configuration and CPU support).
The default size is fixed to 40bits. On arm64, we can allow the limit
to be lowered (limiting the number of levels in stage2 to 2, to prevent
splitting the host PMD huge pages at stage2). We also add support for
handling 52bit IPA addresses (where supported) added by Arm v8.2
extensions.

We need to set the IPA limit as early as the VM creation to keep the
code simpler to avoid sprinkling checks everywhere to ensure that the
IPA is configured. We encode the IPA size in the machine_type
argument to KVM_CREATE_VM ioctl. Bits [7-0] of the type are reserved
for the IPA size. The availability of this feature is advertised by a
new cap KVM_CAP_ARM_VM_PHYS_SHIFT. When supported, this capability
returns the maximum IPA shift supported by the host. The supported IPA
size on a host could be different from the system's PARange indicated
by the CPUs (e.g, kernel limit on the PA size).

Supporting different IPA size requires modification to the stage2 page
table code. The arm64 page table level helpers are defined based on the
page table levels used by the host VA. So, the accessors may not work
if the guest uses more number of levels in stage2 than the stage1
of the host.  The previous versions (v1 & v2) of this series refactored
the stage1 page table accessors to reuse the low-level accessors for an
independent stage2 table. However, due to the level folding in the
generic code, the types are redefined as well. i.e, if the PUD is
folded, the pud_t could be defined as :

 typedef struct { pgd_t pgd; } pud_t;

similarly for pmd_t.  So, without stage1 independent page table entry
types for stage2, we could be dealing with a different type for level
 0-2 entries. This is practically fine on arm/arm64 as the entries
have similar format and size and we always use the appropriate
accessors to get the raw value (i.e, pud_val/pmd_val etc). But not
ideal for a solution upstream. So, this version caps the stage2 page
table levels to that of the stage1. This has the following impact on
the IPA support for various pagesize/host-va combinations :


x-----------------------------------------------------x
| host\ipa    | 40bit | 42bit | 44bit | 48bit | 52bit |
-------------------------------------------------------
| 39bit-4K    |  y    |   y   |  n    |   n   |  n/a  |
-------------------------------------------------------
| 48bit-4K    |  y    |   y   |  y    |   y   |  n/a  |
-------------------------------------------------------
| 36bit-16K   |  y    |   n   |  n    |   n   |  n/a  |
-------------------------------------------------------
| 47bit-16K   |  y    |   y   |  y    |   y   |  n/a  |
-------------------------------------------------------
| 48bit-4K    |  y    |   y   |  y    |   y   |  n/a  |
-------------------------------------------------------
| 42bit-64K   |  y    |   y   |  y    |   n   |  n    |
-------------------------------------------------------
| 48bit-64K   |  y    |   y   |  y    |   y   |  y    |
x-----------------------------------------------------x

Or the following list shows what cannot be supported :

 39bit-4K host  | [44 - 48]
 36bit-16K host | [41 - 48]
 42bit-64K host | [47 - 52]

which is not really bad. We can pursue the independent stage2
page table support and lift the restriction once we get there.
Given there is a proposal for new generic page table walker [0],
it would make sense to make our efforts in sync with it to avoid
diverting from a common API.

52bit support is added for VGIC (including ITS emulation) and handling
of PAR, HPFAR registers.

The series applies on 4.19-rc3. A tree is available here:

	 git://linux-arm.org/linux-skp.git ipa52/v5

Tested with
  - Modified kvmtool, which can only be used for (patches included in
    the series for reference / testing):
    * with virtio-pci upto 44bit PA (Due to 4K page size for virtio-pci
      legacy implemented by kvmtool)
    * Upto 48bit PA with virtio-mmio, due to 32bit PFN limitation.
  - Hacked Qemu (boot loader support for highmem, phys-shift support)
    * with virtio-pci GIC-v3 ITS & MSI upto 52bit on Foundation model.
    Also see [1] for Qemu support.

[0] https://lkml.org/lkml/2018/4/24/777
[1] https://lists.gnu.org/archive/html/qemu-devel/2018-06/msg05759.html

Changes since V4:
 - Rebased on v4.19-rc3
 - Dropped virtio patches queued already by mst.
 - Collect Acks from Christoffer
 - Restrict IPA configuration support to arm64 only
 - Use KVM_CAP_ARM_VM_PHYS_SHIFT for detecting the support for
   IPA size configuration along with the limit on the IPA for the host.
 - Update comments on __load_guest_stage2
 - Add comment about the default value for unknown PARange values.
 - Update Documentation of the API

Changes since V3:
 - Use per-VM VTCR instead per-VM private VTCR bits
 - Allow IPA less than 40bits
 - Split the patch adding support for stage2 dynamic page tables
 - Rearrange the series to keep the userspace API at the end, which
   needs further discussion.
 - Collect Reviews/Acks from Eric & Marc

Changes since V2:
 - Drop "refactoring of host page table helpers" and restrict the IPA size
   to make sure stage2 doesn't use more page table levels than that of the host.
 - Load VTCR for TLB operations on behalf of the VM (Pointed-by: James Morse)
 - Split a couple of patches to make them easier to review.
 - Fall back to normal (non-concatenated) entry level page table support if
   possible.
 - Bump the IOCTL number

Changes since V1:
 - Change the userspace API for configuring VM to encode the IPA
   size in the VM type.  (suggested by Christoffer)
 - Expose the IPA limit on the host via ioctl on /dev/kvm
 - Handle 52bit addresses in PAR & HPFAR
 - Drop patch changing the life time of stage2 PGD
 - Rename macros for 48-to-52 bit conversion for GIC ITS BASER.
   (suggested by Christoffer)
 - Split virtio PFN check patches and address comments.

Kristina Martsenko (1):
  vgic: Add support for 52bit guest physical address

Suzuki K Poulose (17):
  kvm: arm/arm64: Fix stage2_flush_memslot for 4 level page table
  kvm: arm/arm64: Remove spurious WARN_ON
  kvm: arm64: Add helper for loading the stage2 setting for a VM
  arm64: Add a helper for PARange to physical shift conversion
  kvm: arm64: Clean up VTCR_EL2 initialisation
  kvm: arm/arm64: Allow arch specific configurations for VM
  kvm: arm64: Configure VTCR_EL2 per VM
  kvm: arm/arm64: Prepare for VM specific stage2 translations
  kvm: arm64: Prepare for dynamic stage2 page table layout
  kvm: arm64: Make stage2 page table layout dynamic
  kvm: arm64: Dynamic configuration of VTTBR mask
  kvm: arm64: Configure VTCR_EL2.SL0 per VM
  kvm: arm64: Switch to per VM IPA limit
  kvm: arm64: Add 52bit support for PAR to HPFAR conversoin
  kvm: arm64: Set a limit on the IPA size
  kvm: arm64: Limit the minimum number of page table levels
  kvm: arm64: Allow tuning the physical address size for VM

 Documentation/virtual/kvm/api.txt             |   8 +
 arch/arm/include/asm/kvm_arm.h                |   3 +-
 arch/arm/include/asm/kvm_host.h               |   7 +
 arch/arm/include/asm/kvm_mmu.h                |  15 +-
 arch/arm/include/asm/stage2_pgtable.h         |  50 ++--
 arch/arm64/include/asm/cpufeature.h           |  20 ++
 arch/arm64/include/asm/kvm_arm.h              | 130 ++++++++--
 arch/arm64/include/asm/kvm_asm.h              |   2 -
 arch/arm64/include/asm/kvm_host.h             |  16 +-
 arch/arm64/include/asm/kvm_hyp.h              |  10 +
 arch/arm64/include/asm/kvm_mmu.h              |  42 +++-
 arch/arm64/include/asm/stage2_pgtable-nopmd.h |  42 ----
 arch/arm64/include/asm/stage2_pgtable-nopud.h |  39 ---
 arch/arm64/include/asm/stage2_pgtable.h       | 237 +++++++++++++-----
 arch/arm64/kvm/hyp/Makefile                   |   1 -
 arch/arm64/kvm/hyp/s2-setup.c                 |  90 -------
 arch/arm64/kvm/hyp/switch.c                   |   4 +-
 arch/arm64/kvm/hyp/tlb.c                      |   4 +-
 arch/arm64/kvm/reset.c                        | 105 ++++++++
 include/linux/irqchip/arm-gic-v3.h            |   5 +
 include/uapi/linux/kvm.h                      |  10 +
 virt/kvm/arm/arm.c                            |   9 +-
 virt/kvm/arm/mmu.c                            | 120 ++++-----
 virt/kvm/arm/vgic/vgic-its.c                  |  36 +--
 virt/kvm/arm/vgic/vgic-kvm-device.c           |   2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c              |   2 -
 26 files changed, 617 insertions(+), 392 deletions(-)
 delete mode 100644 arch/arm64/include/asm/stage2_pgtable-nopmd.h
 delete mode 100644 arch/arm64/include/asm/stage2_pgtable-nopud.h
 delete mode 100644 arch/arm64/kvm/hyp/s2-setup.c

kvmtool changes:

Suzuki K Poulose (4):
  kvmtool: Allow backends to run checks on the KVM device fd
  kvmtool: arm64: Add support for guest physical address size
  kvmtool: arm64: Switch memory layout
  kvmtool: arm: Add support for creating VM with PA size

 arm/aarch32/include/kvm/kvm-arch.h        |  6 +++--
 arm/aarch64/include/kvm/kvm-arch.h        | 15 +++++++++---
 arm/aarch64/include/kvm/kvm-config-arch.h |  5 +++-
 arm/include/arm-common/kvm-arch.h         | 17 ++++++++-----
 arm/include/arm-common/kvm-config-arch.h  |  1 +
 arm/kvm.c                                 | 29 ++++++++++++++++++++++-
 include/kvm/kvm.h                         |  4 ++++
 kvm.c                                     |  2 ++
 8 files changed, 66 insertions(+), 13 deletions(-)
```
#### [PATCH v7 00/16] Add support for Hygon Dhyana Family 18h processor
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
 42 files changed, 641 insertions(+), 48 deletions(-)
 create mode 100644 arch/x86/kernel/cpu/hygon.c
```
#### [PATCH 00/35] exec: drop BQL from interrupt handling
##### From: "Emilio G. Cota" <cota@braap.org>

```c

This series comes originally from a series of patches that Paolo
sent to me a long time ago. I have kept most of his S-o-b tags,
but I have done the forward port of the patches to the current
QEMU code base, so please blame all possible bugs on me, not him.

The goal of this series is to push the BQL out of interrupt
handling wherever possible. Many targets do not need the BQL
to handle interrupts, so for those targets we get rid of the
BQL in interrupt handling. In TCG mode, this by itself does
not yield measurable performance gains. However, it is a
necessary first step before tackling BQL contention when
managing CPU states (i.e. exiting the exec loop always
involves taking the BQL, which does not scale).

The patches:

- Patch 0 accesses icount_decr.u16 consistently with atomics.
  This is important because we use it across threads to signal
  that an interrupt is pending.

- 2-28: convert direct callers of cpu->interrupt_request
  to use atomic accesses or CPU helper functions that use atomics.
  I have broken these up into individual patches to ease review.
  Note that in some cases I have added many atomic_reads, most
  of which are probably unnecessary. However, I'd leave this up
  to the maintainers, since I do not want to break things by
  doing a single atomic_read(&cpu->interrupt_request) at the
  beginning of a function and then miss subsequent updates to
  cpu->interrupt_request.

- 29-31: drop the BQL requirement when handling cpu->interrupt_request

- 32-33: drop now unnecessary BQL acquisitions in i386 and ppc

- 34-35: push down the BQL acquisition to cpu->do_interrupt
  and cpu->cpu_exec_interrupt. Here I am Cc'ing everyone so that
  we can make sure I am not missing any target that requires
  the BQL on either do_interrupt or cpu_exec_interrupt.

This series is checkpatch-clean, and can be fetched from:
  https://github.com/cota/qemu/tree/cpu-lock

Note that the series applies on top of patches that are
already on the qemu-devel list and will hopefully soon
be upstream. This series begins after commit
4ece0cbd74 ("cpus: access .qemu_icount_bias with atomic64")
in that tree.

Thanks,

		Emilio
Tested-by: Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>
```
#### [PATCH/RFC v4 0/2] vfio: platform: Add generic reset controller
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c

Hi all,

This patch series implements generic reset controller support for
vfio-platform, for devices that are connected to an SoC-internal reset
controller and can be reset in a generic way.  This avoids having to
write/change a vfio-specific reset driver for each and every device to be
passed-through to a guest.

It consists of two patches:
  - The first patch enhances the reset controller subsystem to add support
    for dedicated resets.
    This addresses the issue that even reset_control_get_exclusive() does
    not guarantee that we have an exclusive wire between the device and
    the reset controller.
  - The second patch enhances vfio-platform to add generic reset controller
    support.

Changes compared to v3:
  - Add Reviewed-by,
  - New patch "reset: Add support for dedicated reset controls",
  - Use new RFC reset_control_get_dedicated() instead of
    of_reset_control_get_exclusive(), to (a) make it more generic, and
    (b) make sure the reset returned is really a dedicated reset, and
    does not affect other devices,
  - Drop vfio-platform reset leak fix, which has been applied.

Changes compared to v2:
  - Add Reviewed-by,
  - Merge similar checks in vfio_platform_has_reset().

Changes compared to v1:
  - Add Reviewed-by,
  - Don't store error values in vdev->reset_control,
  - Use of_reset_control_get_exclusive() instead of
    __of_reset_control_get(),
  - Improve description.

This has been tested on R-Car H3/Salvator-XS:
  - SATA can be exported, as it has a dedicated reset,
  - PWM1 cannot, as its reset is shared with all other PWM modules:
    "VFIO: No reset function found for device e6e31000.pwm".

Thanks for your comments!

Geert Uytterhoeven (2):
  [RFC] reset: Add support for dedicated reset controls
  [RFC] vfio: platform: Add generic reset controller support

 drivers/reset/core.c                          | 76 ++++++++++++++++---
 drivers/vfio/platform/vfio_platform_common.c  | 20 ++++-
 drivers/vfio/platform/vfio_platform_private.h |  1 +
 include/linux/reset.h                         | 60 ++++++++++-----
 4 files changed, 126 insertions(+), 31 deletions(-)
```
