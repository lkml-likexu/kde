

#### [PATCH v3 00/20] KVM: nVMX: add option to perform early consistency
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM currently defers many VMX consistency checks to the CPU, including
checks that result in VMFail (as opposed to VMExit).  This behavior
may be undesirable for some users since this means KVM detects certain
classes of VMFail only after it has processed guest state.  Because
there is a strict ordering between checks that cause VMFail and those
that cause VMExit, i.e. all VMFail checks are performed before any
checks that cause VMExit, we can detect all VMFail conditions via a
dry run of sorts.

The end goal of this series is to add an optional (param-controlled)
pre-run VMEnter into the nested_vmx_run() flow in order to perform
all VMFail consistency checks prior to actually running vmcs02.  By
itself, this is not a complex process, but getting KVM to a point
where the approach is viable requires a fair amount of refactoring,
e.g. to split prepare_vmcs02() so that there is a point where vmcs02
can pass the VMFail checks without first consuming guest state.

And while the goal (and subject) of this series is to enable early
consistency checks, the vast majority of the series deals with bug
fixes and cleanups in the nested VMX code.  During the refactoring
and testing, a number of pre-existing bugs, opportunities for code
cleanup and easy optimization points (which unconvered more bugs)
were encountered.

Ideally, these patches would be split into 3-4 separate series,
especially the bug fix patches.  I smushed everything into a single
series because the early VMEnter code breaks without the bug fixes
and the refactoring shuffles the same code, and some of the cleanup
and fixes are inter-dependent.

Patch Synopsis:
  1-4:   bug fixes
  5-6:   optimizations
  7:     function rename
  8:     bug fix and refactoring
  9-12:  refactoring
  13:    optimization
  14:    refactoring
  15-16: bug fix
  17:    refactoring
  18:    optimization and prereq for early consistency checks
  19-20: early consistency checks

v1: https://www.spinics.net/lists/kvm/msg172795.html

v2:
  - rebased on tag kvm-4.19-2
  - added patch to skip instr in nested_vmx_{fail,succeed}

v3:
  - rebased on tag v4.19-rc1
  - use GUEST_RFLAGS to trigger failure during h/w checks [0-Day]
  - reset control shadows and seg cache in vmx_switch_vmcs() [Jim Mattson]
  - remove pml_pg ASSERT in dedicated patch [Jim Mattson]
  - add dedicated flag to track vmcs02 initialization [Jim Mattson]
  - use vmentry_fail_vmexit terminology [Jim Mattson]
  - fix a bug when moving check_vmentry_postreqs() [Jim Mattson]
  - introduce speculation of VM_EXIT_LOAD_IA32_EFER in correct patch [Jim Mattson]
  - remove unnecessary braces [Jim Mattson]
  
Sean Christopherson (20):
  KVM: nVMX: move host EFER consistency checks to VMFail path
  KVM: nVMX: move vmcs12 EPTP consistency check to
    check_vmentry_prereqs()
  KVM: nVMX: use vm_exit_controls_init() to write exit controls for
    vmcs02
  KVM: nVMX: reset cache/shadows when switching loaded VMCS
  KVM: vmx: do not unconditionally clear EFER switching
  KVM: nVMX: try to set EFER bits correctly when initializing controls
  KVM: nVMX: rename enter_vmx_non_root_mode to
    nested_vmx_enter_non_root_mode
  KVM: nVMX: move check_vmentry_postreqs() call to
    nested_vmx_enter_non_root_mode()
  KVM: nVMX: assimilate nested_vmx_entry_failure() into
    nested_vmx_enter_non_root_mode()
  KVM: vVMX: rename label for post-enter_guest_mode consistency check
  KVM: VMX: remove ASSERT() on vmx->pml_pg validity
  KVM: nVMX: split pieces of prepare_vmcs02() to prepare_vmcs02_early()
  KVM: nVMX: initialize vmcs02 constant exactly once (per VMCS)
  KVM: nVMX: do early preparation of vmcs02 before
    check_vmentry_postreqs()
  KVM: nVMX: do not skip VMEnter instruction that succeeds
  KVM: nVMX: do not call nested_vmx_succeed() for consistency check
    VMExit
  KVM: nVMX: call kvm_skip_emulated_instruction in
    nested_vmx_{fail,succeed}
  KVM: vmx: write HOST_IA32_EFER in vmx_set_constant_host_state()
  KVM: nVMX: add option to perform early consistency checks via H/W
  KVM: nVMX: WARN if nested run hits VMFail with early consistency
    checks enabled

 arch/x86/kvm/vmx.c | 1032 +++++++++++++++++++++++++-------------------
 1 file changed, 581 insertions(+), 451 deletions(-)
```
#### [PATCH v6 00/18] kvm: arm64: Dynamic IPA and 52bit IPA
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
new cap KVM_CAP_ARM_VM_IPA_SIZE. When supported, this capability
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

The series applies on 4.19-rc4. A tree is available here:

	 git://linux-arm.org/linux-skp.git ipa52/v6

Tested with
  - Modified kvmtool, which can only be used for (patches included in
    the series for reference / testing):
    * with virtio-pci upto 44bit PA (Due to 4K page size for virtio-pci
      legacy implemented by kvmtool)
    * Upto 48bit PA with virtio-mmio, due to 32bit PFN limitation.
  - Hacked Qemu (boot loader support for highmem, IPA size support)
    * with virtio-pci GIC-v3 ITS & MSI upto 52bit on Foundation model.
    Also see [1] for Qemu support.

[0] https://lkml.org/lkml/2018/4/24/777
[1] https://lists.gnu.org/archive/html/qemu-devel/2018-06/msg05759.html

Change since v5:
 - Don't raise the IPA Limit to 40bits on systems with lower PA size.
   Doesn't break backward compatibility, we still allow KVM_CREATE_VM
   to succeed with "0" as the IPA size (40bits). But prevent specifying
   40bit explicitly, when the limit is lower.
 - Rename CAP, KVM_CAP_ARM_VM_PHYS_SHIFT => KVM_CAP_ARM_VM_IPA_SIZE
   and helper, KVM_VM_TYPE_ARM_VM_PHY_SHIFT => KVM_VM_TYPE_ARM_VM_IPA_SIZE
 - Update Documentation of the API
 - Update comments and commit description as reported by Eric
 - Set the missing TCR_T0SZ in patch "kvm: arm64: Configure VTCR_EL2 per VM"
 - Fix bits for CBASER_ADDRESS mask, GITS_CBASER_ADDRESS()

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

 Documentation/virtual/kvm/api.txt             |  31 +++
 arch/arm/include/asm/kvm_arm.h                |   3 +-
 arch/arm/include/asm/kvm_host.h               |   7 +
 arch/arm/include/asm/kvm_mmu.h                |  15 +-
 arch/arm/include/asm/stage2_pgtable.h         |  50 ++--
 arch/arm64/include/asm/cpufeature.h           |  20 ++
 arch/arm64/include/asm/kvm_arm.h              | 157 +++++++++---
 arch/arm64/include/asm/kvm_asm.h              |   2 -
 arch/arm64/include/asm/kvm_host.h             |  16 +-
 arch/arm64/include/asm/kvm_hyp.h              |  10 +
 arch/arm64/include/asm/kvm_mmu.h              |  42 +++-
 arch/arm64/include/asm/stage2_pgtable-nopmd.h |  42 ----
 arch/arm64/include/asm/stage2_pgtable-nopud.h |  39 ---
 arch/arm64/include/asm/stage2_pgtable.h       | 236 +++++++++++++-----
 arch/arm64/kvm/hyp/Makefile                   |   1 -
 arch/arm64/kvm/hyp/s2-setup.c                 |  90 -------
 arch/arm64/kvm/hyp/switch.c                   |   4 +-
 arch/arm64/kvm/hyp/tlb.c                      |   4 +-
 arch/arm64/kvm/reset.c                        | 103 ++++++++
 include/linux/irqchip/arm-gic-v3.h            |   5 +
 include/uapi/linux/kvm.h                      |  10 +
 virt/kvm/arm/arm.c                            |   9 +-
 virt/kvm/arm/mmu.c                            | 120 ++++-----
 virt/kvm/arm/vgic/vgic-its.c                  |  36 +--
 virt/kvm/arm/vgic/vgic-kvm-device.c           |   2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c              |   2 -
 26 files changed, 648 insertions(+), 408 deletions(-)
 delete mode 100644 arch/arm64/include/asm/stage2_pgtable-nopmd.h
 delete mode 100644 arch/arm64/include/asm/stage2_pgtable-nopud.h
 delete mode 100644 arch/arm64/kvm/hyp/s2-setup.c

kvmtool changes:

Suzuki K Poulose (4):
  kvmtool: Allow backends to run checks on the KVM device fd
  kvmtool: arm64: Add support for guest physical address size
  kvmtool: arm64: Switch memory layout
  kvmtool: arm: Add support for creating VM with PA size

 arm/aarch32/include/kvm/kvm-arch.h        |  6 ++--
 arm/aarch64/include/kvm/kvm-arch.h        | 15 ++++++++--
 arm/aarch64/include/kvm/kvm-config-arch.h |  5 +++-
 arm/include/arm-common/kvm-arch.h         | 17 ++++++++----
 arm/include/arm-common/kvm-config-arch.h  |  1 +
 arm/kvm.c                                 | 34 ++++++++++++++++++++++-
 include/kvm/kvm.h                         |  4 +++
 kvm.c                                     |  2 ++
 8 files changed, 71 insertions(+), 13 deletions(-)
Tested-by: Eric Auger <eric.auger@redhat.com>
```
#### [PATCH v6 0/7] KVM: x86: hyperv: PV IPI support for Windows guests
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v5:
- New 'hybrid' approach to VP indexes: introduce 'num_mismatched_vp_indexes'
  and use it for optimization in both PV IPI and TLB flush [Paolo Bonzini,
  Roman Kagan].
- Rebase, KVM_CAP_HYPERV_SEND_IPI is now '160'.
- Patches 3-5 are new in this version.
- Drop "x86/hyper-v: rename ipi_arg_{ex,non_ex} structures" patch as it is
  already merged in kvm/queue.

Original description:
Using hypercall for sending IPIs is faster because this allows to specify
any number of vCPUs (even > 64 with sparse CPU set), the whole procedure
will take only one VMEXIT.

Same as PV TLB flush, this allows Windows guests having > 64 vCPUs to boot
on KVM when Hyper-V extensions are enabled.

Vitaly Kuznetsov (7):
  KVM: x86: hyperv: enforce vp_index < KVM_MAX_VCPUS
  KVM: x86: hyperv: optimize 'all cpus' case in kvm_hv_flush_tlb()
  KVM: x86: hyperv: consistently use 'hv_vcpu' for 'struct kvm_vcpu_hv'
    variables
  KVM: x86: hyperv: keep track of mismatched VP indexes
  KVM: x86: hyperv: valid_bank_mask should be 'u64'
  KVM: x86: hyperv: optimize kvm_hv_flush_tlb() for vp_index == vcpu_idx
    case
  KVM: x86: hyperv: implement PV IPI send hypercalls

 Documentation/virtual/kvm/api.txt |   7 +
 arch/x86/include/asm/kvm_host.h   |   3 +
 arch/x86/kvm/hyperv.c             | 268 +++++++++++++++++++++++-------
 arch/x86/kvm/trace.h              |  42 +++++
 arch/x86/kvm/x86.c                |   1 +
 include/uapi/linux/kvm.h          |   1 +
 virt/kvm/kvm_main.c               |   6 +-
 7 files changed, 265 insertions(+), 63 deletions(-)
```
