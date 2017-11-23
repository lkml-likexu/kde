#### [GIT PULL] Changes for KVM 4.21
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 40e020c129cfc991e8ab4736d2665351ffd1468d:

  Linux 4.20-rc6 (2018-12-09 15:31:00 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to a0aea130afebcd091d5396d13f25b9da24c9144a:

  KVM: x86: Add CPUID support for new instruction WBNOINVD (2018-12-21 14:26:32 +0100)

The PT and Hyper-V changes have been acked by the maintainers; since
Ingo acked the MPX issue and is going to remove the topic branch, all that
is left is two trivial conflicts.

One is due to the disintegration of arch/x86/kvm/vmx.c; only one commit
in all of linux-next touched that file, so this will be enough to fix it:

	$ git log --oneline v4.20-rc6..origin/master -- arch/x86/kvm/vmx.c
	c2dd5146e9fe KVM: Fix UAF in nested posted interrupt processing
	$ git rm arch/x86/kvm/vmx.c
	$ git show c2dd5146e9fe | patch arch/x86/kvm/vmx/nested.c
	patching file arch/x86/kvm/vmx/nested.c
	Hunk #1 succeeded at 2881 (offset -9104 lines).

The second is with the PPC tree, due to commit d7b456152230 in my tree, you
can solve it in your sleep but anyway the resolution is after the diffstat.
 
Thanks,

Paolo

----------------------------------------------------------------
* ARM: selftests improvements, large PUD support for HugeTLB,
single-stepping fixes, improved tracing, various timer and vGIC
fixes

* x86: Processor Tracing virtualization, STIBP support, some correctness fixes,
refactorings and splitting of vmx.c, use the Hyper-V range TLB flush hypercall,
reduce order of vcpu struct, WBNOINVD support, do not use -ftrace for __noclone
functions, nested guest support for PAUSE filtering on AMD, more Hyper-V
enlightenments (direct mode for synthetic timers)

* PPC: nested VFIO

* s390: bugfixes only this time

----------------------------------------------------------------
Andrew Jones (8):
      kvm: selftests: x86_64: dirty_log_test: fix -t
      kvm: selftests: dirty_log_test: don't identity map the test mem
      kvm: selftests: dirty_log_test: always use -t
      kvm: selftests: dirty_log_test: reset guest test phys offset
      kvm: selftests: dirty_log_test: improve mode param management
      kvm: selftests: add pa-48/va-48 VM modes
      kvm: selftests: aarch64: dirty_log_test: support greater than 40-bit IPAs
      kvm: selftests: ucall: fix exit mmio address guessing

Bharata B Rao (1):
      KVM: PPC: Pass change type down to memslot commit function

Chao Peng (7):
      perf/x86/intel/pt: Move Intel PT MSRs bit defines to global header
      perf/x86/intel/pt: Export pt_cap_get()
      KVM: x86: Add Intel PT virtualization work mode
      KVM: x86: Add Intel Processor Trace cpuid emulation
      KVM: x86: Add Intel PT context switch for each vcpu
      KVM: x86: Implement Intel PT MSRs read/write emulation
      KVM: x86: Set intercept for Intel PT MSRs read/write

Christoffer Dall (9):
      KVM: arm/arm64: Fix VMID alloc race by reverting to lock-less
      KVM: arm/arm64: vgic-v2: Set active_source to 0 when restoring state
      KVM: arm64: Clarify explanation of STAGE2_PGTABLE_LEVELS
      KVM: arm/arm64: vgic: Consider priority and active state for pending irq
      KVM: arm/arm64: Fixup the kvm_exit tracepoint
      KVM: arm/arm64: Remove arch timer workqueue
      KVM: arm/arm64: arch_timer: Simplify kvm_timer_vcpu_terminate
      KVM: arm64: Make vcpu const in vcpu_read_sys_reg
      KVM: arm/arm64: Fix unintended stage 2 PMD mappings

Eduardo Habkost (1):
      kvm: x86: Report STIBP on GET_SUPPORTED_CPUID

Gustavo A. R. Silva (1):
      KVM: arm/arm64: vgic: Fix off-by-one bug in vgic_get_irq()

Jim Mattson (11):
      KVM: nVMX: Unrestricted guest mode requires EPT
      kvm: nVMX: Set VM instruction error for VMPTRLD of unbacked page
      kvm: vmx: Set IA32_TSC_AUX for legacy mode guests
      kvm: vmx: Document the need for MSR_STAR in i386 builds
      kvm: vmx: Don't set hardware IA32_CSTAR MSR on VM-entry
      kvm: vmx: Skip all SYSCALL MSRs in setup_msrs() when !EFER.SCE
      kvm: x86: Don't modify MSR_PLATFORM_INFO on vCPU reset
      kvm: Disallow wraparound in kvm_gfn_to_hva_cache_init
      kvm: Change offset in kvm_write_guest_offset_cached to unsigned
      kvm: nVMX: NMI-window and interrupt-window exiting should wake L2 from HLT
      kvm: vmx: Allow guest read access to IA32_TSC

Julien Thierry (1):
      KVM: arm/arm64: vgic: Do not cond_resched_lock() with IRQs disabled

Krish Sadhukhan (8):
      nVMX x86: Check VMX-preemption timer controls on vmentry of L2 guests
      KVM nVMX: MSRs should not be stored if VM-entry fails during or after loading guest state
      KVM: nVMX: Prepend "nested_vmx_" to check_vmentry_{pre,post}reqs()
      KVM: nVMX: Move the checks for VM-Execution Control Fields to a separate helper function
      KVM: nVMX: Move the checks for VM-Exit Control Fields to a separate helper function
      KVM: nVMX: Move the checks for VM-Entry Control Fields to a separate helper function
      KVM: nVMX: Move the checks for Host Control Registers and MSRs to a separate helper function
      KVM: nVMX: Move the checks for Guest Non-Register States to a separate helper function

Lan Tianyu (10):
      KVM/VMX: Check ept_pointer before flushing ept tlb
      KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
      x86/hyper-v: Add HvFlushGuestAddressList hypercall support
      KVM/VMX: Add hv tlb range flush support
      KVM/MMU: Add tlb flush with range helper function
      KVM: Replace old tlb flush function with new one to flush a specified range.
      KVM: Make kvm_set_spte_hva() return int
      KVM/MMU: Move tlb flush in kvm_set_pte_rmapp() to kvm_mmu_notifier_change_pte()
      KVM/MMU: Flush tlb directly in kvm_set_pte_rmapp()
      KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()

Luwei Kang (5):
      perf/x86/intel/pt: Introduce intel_pt_validate_cap()
      perf/x86/intel/pt: Add new bit definitions for PT MSRs
      perf/x86/intel/pt: add new capability for Intel PT
      KVM: x86: Introduce a function to initialize the PT configuration
      KVM: x86: Disable Intel PT when VMXON in L1 guest

Marc Orr (2):
      kvm: x86: Use task structs fpu field for user
      kvm: x86: Dynamically allocate guest_fpu

Marc Zyngier (5):
      KVM: arm/arm64: vgic: Cap SPIs to the VM-defined maximum
      arm64: KVM: Add trapped system register access tracepoint
      arm/arm64: KVM: vgic: Force VM halt when changing the active state of GICv3 PPIs/SGIs
      arm/arm64: KVM: Add ARM_EXCEPTION_IS_TRAP macro
      arm: KVM: Add S2_PMD_{MASK,SIZE} constants

Mark Rutland (3):
      arm64: KVM: Skip MMIO insn after emulation
      arm64: KVM: Consistently advance singlestep when emulating instructions
      KVM: arm/arm64: Log PSTATE for unhandled sysregs

Michael Mueller (2):
      KVM: s390: unregister debug feature on failing arch init
      KVM: s390: fix kmsg component kvm-s390

Paolo Bonzini (10):
      KVM: x86: Trace changes to active TSC offset regardless if vCPU in guest-mode
      Merge branch 'khdr_fix' of git://git.kernel.org/.../shuah/linux-kselftest into HEAD
      kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic
      kvm: rename last argument to kvm_get_dirty_log_protect
      kvm: introduce manual dirty log reprotect
      kvm: selftests: ucall: improve ucall placement in memory, fix unsigned comparison
      Merge tag 'kvmarm-for-v4.21' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      Merge tag 'kvm-s390-next-4.21-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      KVM: x86: fix size of x86_fpu_cache objects
      Merge tag 'kvm-ppc-next-4.21-2' of git://git.kernel.org/.../paulus/powerpc into kvm-next

Paul Mackerras (4):
      KVM: PPC: Book3S HV: Fix race between kvm_unmap_hva_range and MMU mode switch
      KVM: PPC: Book3S HV: Map single pages when doing dirty page logging
      KVM: PPC: Book3S HV: Cleanups - constify memslots, fix comments
      KVM: PPC: Book3S HV: Flush guest mappings when turning dirty tracking on/off

Peng Hao (3):
      kvm: svm: remove unused struct definition
      kvm: x86: remove unnecessary recalculate_apic_map
      x86/kvmclock: convert to SPDX identifiers

Punit Agrawal (8):
      KVM: arm/arm64: Share common code in user_mem_abort()
      KVM: arm/arm64: Re-factor setting the Stage 2 entry to exec on fault
      KVM: arm/arm64: Introduce helpers to manipulate page table entries
      KVM: arm64: Support dirty page tracking for PUD hugepages
      KVM: arm64: Support PUD hugepage in stage2_is_exec()
      KVM: arm64: Support handling access faults for PUD hugepages
      KVM: arm64: Update age handlers to support PUD hugepages
      KVM: arm64: Add support for creating PUD hugepages at stage 2

Radim Krčmář (1):
      Merge tag 'kvm-ppc-next-4.21-1' of git://git.kernel.org/.../paulus/powerpc

Robert Hoo (1):
      KVM: x86: Add CPUID support for new instruction WBNOINVD

Roman Kagan (2):
      x86: kvm: hyperv: simplify SynIC message delivery
      x86: kvm: hyperv: don't retry message delivery for periodic timers

Sean Christopherson (35):
      KVM: nVMX: Free the VMREAD/VMWRITE bitmaps if alloc_kvm_area() fails
      KVM: nVMX: Allocate and configure VM{READ,WRITE} bitmaps iff enable_shadow_vmcs
      KVM: VMX: Alphabetize the includes in vmx.c
      KVM: x86: Add requisite includes to kvm_cache_regs.h
      KVM: x86: Add requisite includes to hyperv.h
      KVM: VMX: Move VMX specific files to a "vmx" subdirectory
      KVM: VMX: rename vmx_shadow_fields.h to vmcs_shadow_fields.h
      KVM: VMX: Drop the "vmx" prefix from vmx_evmcs.h
      KVM: VMX: Move caching of MSR_IA32_XSS to hardware_setup()
      KVM: VMX: Properly handle dynamic VM Entry/Exit controls
      KVM: VMX: Pass vmx_capability struct to setup_vmcs_config()
      KVM: VMX: Move capabilities structs and helpers to dedicated file
      KVM: VMX: Expose various module param vars via capabilities.h
      KVM: VMX: Move VMCS definitions to dedicated file
      KVM: nVMX: Move vmcs12 code to dedicated files
      KVM: VMX: Add vmx.h to hold VMX definitions
      KVM: VMX: Move eVMCS code to dedicated files
      KVM: VMX: Move VMX instruction wrappers to a dedicated header file
      KVM: VMX: Move nested hardware/vcpu {un}setup to helper functions
      KVM: x86: nVMX: Allow nested_enable_evmcs to be NULL
      KVM: VMX: Move the hardware {un}setup functions to the bottom
      KVM: nVMX: Set callbacks for nested functions during hardware setup
      KVM: nVMX: Call nested_vmx_setup_ctls_msrs() iff @nested is true
      KVM: nVMX: Move "vmcs12 to shadow/evmcs sync" to helper function
      KVM: VMX: Expose misc variables needed for nested VMX
      KVM: VMX: Expose various getters and setters to nested VMX
      KVM: VMX: Expose nested_vmx_allowed() to nested VMX as a non-inline
      KVM: nVMX: Move nested code to dedicated files
      KVM: nVMX: Remove param indirection from nested_vmx_check_msr_switch()
      KVM: x86: Remove KF() macro placeholder
      MAINTAINERS: Add arch/x86/kvm sub-directories to existing KVM/x86 entry
      KVM: x86: Use jmp to invoke kvm_spurious_fault() from .fixup
      KVM: VMX: Explicitly reference RCX as the vmx_vcpu pointer in asm blobs
      KVM: VMX: Move VM-Enter + VM-Exit handling to non-inline sub-routines
      Revert "compiler-gcc: disable -ftracer for __noclone functions"

Shuah Khan (1):
      selftests: Fix test errors related to lib.mk khdr target

Stefan Raspl (1):
      tools/kvm_stat: switch to python3

Suraj Jitindar Singh (14):
      KVM: PPC: Book3S PR: Set hflag to indicate that POWER9 supports 1T segments
      KVM: PPC: Book3S: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
      KVM: PPC: Book3S HV: Add function kvmhv_vcpu_is_radix()
      KVM: PPC: Book3S HV: Implement functions to access quadrants 1 & 2
      KVM: PPC: Add load_from_eaddr and store_to_eaddr to the kvmppc_ops struct
      KVM: PPC: Update kvmppc_st and kvmppc_ld to use quadrants
      KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L2 guest
      KVM: PPC: Book3S: Introduce new hcall H_COPY_TOFROM_GUEST to access quadrants 1 & 2
      KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L3 guest
      KVM: PPC: Book3S HV: Hold kvm->mmu_lock across updating nested pte rc bits
      KVM: PPC: Book3S HV: Align gfn to L1 page size when inserting nest-rmap entry
      KVM: PPC: Book3S HV: Apply combination of host and l1 pte rc for nested guest
      KVM: PPC: Book3S HV: Introduce kvmhv_update_nest_rmap_rc_list()
      KVM: PPC: Book3S HV: Keep rc bits in shadow pgtable in sync with host

Tambe, William (1):
      KVM: nSVM: Fix nested guest support for PAUSE filtering.

Uros Bizjak (2):
      KVM/nVMX: Remove unneeded forward jump in nested_vmx_check_vmentry_hw asm
      KVM/x86: Use SVM assembly instruction mnemonics instead of .byte streams

Vitaly Kuznetsov (14):
      x86/hyper-v: Mark TLFS structures packed
      x86/hyper-v: Do some housekeeping in hyperv-tlfs.h
      x86/hyper-v: Drop HV_X64_CONFIGURE_PROFILER definition
      x86/kvm/hyper-v: Introduce nested_get_evmcs_version() helper
      x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID
      KVM: selftests: implement an unchecked version of vcpu_ioctl()
      KVM: selftests: Add hyperv_cpuid test
      x86/hyper-v: move synic/stimer control structures definitions to hyperv-tlfs.h
      x86/kvm/hyper-v: use stimer config definition from hyperv-tlfs.h
      x86/kvm/hyper-v: direct mode for synthetic timers
      x86/kvm/hyper-v: avoid open-coding stimer_mark_pending() in kvm_hv_notify_acked_sint()
      x86/hyper-v: Stop caring about EOI for direct stimers
      KVM: x86: svm: report MSR_IA32_MCG_EXT_CTL as unsupported
      selftests: kvm: report failed stage when exit reason is unexpected

Wei Huang (1):
      kvm: vmx: add cpu into VMX preemption timer bug list

Wei Yang (1):
      KVM: fix some typos

Will Deacon (1):
      arm64: KVM: Avoid setting the upper 32 bits of VTCR_EL2 to 1

Yangtao Li (1):
      KVM: PPC: Book3S HV: Change to use DEFINE_SHOW_ATTRIBUTE macro

YueHaibing (1):
      KVM: VMX: Remove duplicated include from vmx.c

 Documentation/virtual/kvm/api.txt                  |   136 +-
 MAINTAINERS                                        |     1 +
 arch/arm/include/asm/kvm_asm.h                     |     4 +
 arch/arm/include/asm/kvm_host.h                    |     7 +-
 arch/arm/include/asm/kvm_mmu.h                     |    61 +
 arch/arm/include/asm/stage2_pgtable.h              |     8 +
 arch/arm/kvm/coproc.c                              |     4 +-
 arch/arm64/include/asm/kvm_arm.h                   |     6 +-
 arch/arm64/include/asm/kvm_asm.h                   |     7 +
 arch/arm64/include/asm/kvm_emulate.h               |    35 +-
 arch/arm64/include/asm/kvm_host.h                  |     5 +-
 arch/arm64/include/asm/kvm_mmu.h                   |    48 +
 arch/arm64/include/asm/pgtable-hwdef.h             |     4 +
 arch/arm64/include/asm/pgtable.h                   |     9 +
 arch/arm64/include/asm/stage2_pgtable.h            |    16 +-
 arch/arm64/kvm/debug.c                             |    21 -
 arch/arm64/kvm/handle_exit.c                       |    14 +-
 arch/arm64/kvm/hyp/switch.c                        |    43 +-
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |    12 +-
 arch/arm64/kvm/sys_regs.c                          |    12 +-
 arch/arm64/kvm/sys_regs.h                          |     4 +
 arch/arm64/kvm/trace.h                             |    35 +
 arch/mips/include/asm/kvm_host.h                   |     2 +-
 arch/mips/kvm/mips.c                               |    29 +-
 arch/mips/kvm/mmu.c                                |     3 +-
 arch/powerpc/include/asm/hvcall.h                  |     1 +
 arch/powerpc/include/asm/kvm_book3s.h              |    23 +-
 arch/powerpc/include/asm/kvm_book3s_64.h           |    18 +-
 arch/powerpc/include/asm/kvm_host.h                |     5 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |    10 +-
 arch/powerpc/kernel/exceptions-64s.S               |     9 +
 arch/powerpc/kvm/book3s.c                          |     8 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |    12 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |   160 +-
 arch/powerpc/kvm/book3s_hv.c                       |    95 +-
 arch/powerpc/kvm/book3s_hv_nested.c                |   190 +-
 arch/powerpc/kvm/book3s_hv_rm_mmu.c                |     2 +-
 arch/powerpc/kvm/book3s_pr.c                       |     4 +-
 arch/powerpc/kvm/book3s_xics.c                     |    12 +-
 arch/powerpc/kvm/book3s_xive.c                     |    12 +-
 arch/powerpc/kvm/booke.c                           |     3 +-
 arch/powerpc/kvm/e500_mmu_host.c                   |     3 +-
 arch/powerpc/kvm/powerpc.c                         |    47 +-
 arch/powerpc/mm/fault.c                            |     1 +
 arch/s390/kvm/kvm-s390.c                           |    35 +-
 arch/x86/events/intel/pt.c                         |    60 +-
 arch/x86/events/intel/pt.h                         |    58 -
 arch/x86/hyperv/nested.c                           |    80 +
 arch/x86/include/asm/cpufeatures.h                 |     1 +
 arch/x86/include/asm/hyperv-tlfs.h                 |   335 +-
 arch/x86/include/asm/intel_pt.h                    |    26 +
 arch/x86/include/asm/kvm_host.h                    |    25 +-
 arch/x86/include/asm/mshyperv.h                    |    15 +
 arch/x86/include/asm/msr-index.h                   |    37 +
 arch/x86/include/asm/svm.h                         |     7 -
 arch/x86/include/asm/trace/hyperv.h                |    14 +
 arch/x86/include/asm/vmx.h                         |     9 +
 arch/x86/kernel/kvmclock.c                         |    15 +-
 arch/x86/kvm/Makefile                              |     2 +-
 arch/x86/kvm/cpuid.c                               |    31 +-
 arch/x86/kvm/hyperv.c                              |   305 +-
 arch/x86/kvm/hyperv.h                              |     4 +
 arch/x86/kvm/kvm_cache_regs.h                      |     2 +
 arch/x86/kvm/lapic.c                               |     5 +-
 arch/x86/kvm/mmu.c                                 |    98 +-
 arch/x86/kvm/paging_tmpl.h                         |     3 +-
 arch/x86/kvm/svm.c                                 |    68 +-
 arch/x86/kvm/trace.h                               |    10 +-
 arch/x86/kvm/vmx.c                                 | 15250 -------------------
 arch/x86/kvm/vmx/capabilities.h                    |   343 +
 arch/x86/kvm/{vmx_evmcs.h => vmx/evmcs.c}          |    78 +-
 arch/x86/kvm/vmx/evmcs.h                           |   202 +
 arch/x86/kvm/vmx/nested.c                          |  5719 +++++++
 arch/x86/kvm/vmx/nested.h                          |   282 +
 arch/x86/kvm/vmx/ops.h                             |   285 +
 arch/x86/kvm/{ => vmx}/pmu_intel.c                 |     0
 arch/x86/kvm/vmx/vmcs.h                            |   136 +
 arch/x86/kvm/vmx/vmcs12.c                          |   157 +
 arch/x86/kvm/vmx/vmcs12.h                          |   462 +
 .../vmcs_shadow_fields.h}                          |     0
 arch/x86/kvm/vmx/vmenter.S                         |    57 +
 arch/x86/kvm/vmx/vmx.c                             |  7935 ++++++++++
 arch/x86/kvm/vmx/vmx.h                             |   519 +
 arch/x86/kvm/x86.c                                 |   161 +-
 drivers/hv/hv.c                                    |     2 +-
 drivers/hv/hyperv_vmbus.h                          |    68 -
 include/kvm/arm_arch_timer.h                       |     4 -
 include/linux/compiler_attributes.h                |     9 +-
 include/linux/kvm_host.h                           |    12 +-
 include/uapi/linux/kvm.h                           |    19 +
 tools/kvm/kvm_stat/kvm_stat                        |     2 +-
 tools/testing/selftests/android/Makefile           |     2 +-
 tools/testing/selftests/futex/functional/Makefile  |     1 +
 tools/testing/selftests/gpio/Makefile              |     6 +-
 tools/testing/selftests/kvm/Makefile               |     5 +-
 tools/testing/selftests/kvm/clear_dirty_log_test.c |     2 +
 tools/testing/selftests/kvm/dirty_log_test.c       |   165 +-
 tools/testing/selftests/kvm/include/kvm_util.h     |     8 +
 .../testing/selftests/kvm/lib/aarch64/processor.c  |    18 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |    67 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |     1 +
 tools/testing/selftests/kvm/lib/ucall.c            |    36 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |     4 +-
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  |   157 +
 tools/testing/selftests/kvm/x86_64/state_test.c    |     4 +-
 tools/testing/selftests/lib.mk                     |     8 +-
 .../selftests/networking/timestamping/Makefile     |     1 +
 tools/testing/selftests/tc-testing/bpf/Makefile    |     1 +
 tools/testing/selftests/vm/Makefile                |     1 +
 virt/kvm/arm/arch_timer.c                          |    35 +-
 virt/kvm/arm/arm.c                                 |    47 +-
 virt/kvm/arm/hyp/vgic-v3-sr.c                      |     6 +-
 virt/kvm/arm/mmio.c                                |    11 +-
 virt/kvm/arm/mmu.c                                 |   390 +-
 virt/kvm/arm/trace.h                               |    18 +-
 virt/kvm/arm/vgic/vgic-mmio.c                      |    44 +-
 virt/kvm/arm/vgic/vgic.c                           |    13 +-
 virt/kvm/async_pf.c                                |     2 +-
 virt/kvm/kvm_main.c                                |   208 +-
 119 files changed, 19022 insertions(+), 16327 deletions(-)
 delete mode 100644 arch/x86/kvm/vmx.c
 create mode 100644 arch/x86/kvm/vmx/capabilities.h
 rename arch/x86/kvm/{vmx_evmcs.h => vmx/evmcs.c} (88%)
 create mode 100644 arch/x86/kvm/vmx/evmcs.h
 create mode 100644 arch/x86/kvm/vmx/nested.c
 create mode 100644 arch/x86/kvm/vmx/nested.h
 create mode 100644 arch/x86/kvm/vmx/ops.h
 rename arch/x86/kvm/{ => vmx}/pmu_intel.c (100%)
 create mode 100644 arch/x86/kvm/vmx/vmcs.h
 create mode 100644 arch/x86/kvm/vmx/vmcs12.c
 create mode 100644 arch/x86/kvm/vmx/vmcs12.h
 rename arch/x86/kvm/{vmx_shadow_fields.h => vmx/vmcs_shadow_fields.h} (100%)
 create mode 100644 arch/x86/kvm/vmx/vmenter.S
 create mode 100644 arch/x86/kvm/vmx/vmx.c
 create mode 100644 arch/x86/kvm/vmx/vmx.h
 create mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c



```
