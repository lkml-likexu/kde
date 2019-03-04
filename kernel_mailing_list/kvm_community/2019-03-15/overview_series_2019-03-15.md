#### [GIT PULL] KVM changes for 5.1 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit c3c7470c75566a077c8dc71dcf8f1948b8ddfab4:

  powerpc/kvm: Save and restore host AMR/IAMR/UAMOR (2019-02-22 13:41:13 +1100)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 4a605bc08e98381d8df61c30a4acb2eac15eb7da:

  kvm: vmx: fix formatting of a comment (2019-03-15 19:24:34 +0100)

A very late pull request due to some ugly factors that complicated this
merge window: a late discovery of a race condition, that disappeared for
me right after I started looking at it; a bunch of fixes for old bugs
that came in right during the merge window---I initially wanted to
sneak them in but ultimately chose to delay them to -rc2; and just life
being busy.

You'll see a lot of reverts in the commit list, but most of them
are really just dropping old code that we decided was a premature
optimization.  However, the last revert on top is actually what fixes
the above-mentioned race condition.

For completeness, the following patches are *not* in linux-next:

      Revert "KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()"
      kvm: vmx: fix formatting of a comment
      MAINTAINERS: Add KVM selftests to existing KVM entry
      KVM: doc: Document the life cycle of a VM and its resources

I know this isn't kosher, but it should be safe enough in this case.

On the good side, conflicts are few and very easily solved.  There is
a slightly strange one in arch/x86/kvm/vmx/vmx.h (pi_set_sn) where this
pull request should win.

Thanks,

Paolo
----------------------------------------------------------------
ARM: some cleanups, direct physical timer assignment, cache sanitization
for 32-bit guests

s390: interrupt cleanup, introduction of the Guest Information Block,
preparation for processor subfunctions in cpu models

PPC: bug fixes and improvements, especially related to machine checks
and protection keys

x86: many, many cleanups, including removing a bunch of MMU code for
unnecessary optimizations; plus AVIC fixes.

Generic: memcg accounting

----------------------------------------------------------------

Alexey Kardashevskiy (2):
      KVM: PPC: Release all hardware TCE tables attached to a group
      KVM: PPC: Book3S: Improve KVM reference counting

Andre Przywara (2):
      clocksource/arm_arch_timer: Store physical timer IRQ number for KVM on VHE
      KVM: arm/arm64: consolidate arch timer trap handlers

Ard Biesheuvel (2):
      arm64: KVM: Expose sanitised cache type register to guest
      arm64: KVM: Describe data or unified caches as having 1 set and 1 way

Ben Gardon (5):
      kvm: Add memcg accounting to KVM allocations
      kvm: x86: Add memcg accounting to KVM allocations
      kvm: svm: Add memcg accounting to KVM allocations
      kvm: vmx: Add memcg accounting to KVM allocations
      Revert "KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()"

Christian Borntraeger (2):
      KVM: s390: implement subfunction processor calls
      KVM: s390: add debug logging for cpu model subfunctions

Christoffer Dall (6):
      KVM: arm/arm64: Factor out VMID into struct kvm_vmid
      KVM: arm/arm64: Simplify bg_timer programming
      KVM: arm/arm64: timer: Rework data structures for multiple timers
      KVM: arm/arm64: arch_timer: Assign the phys timer on VHE systems
      KVM: arm/arm64: Rework the timer code to use a timer_map
      KVM: arm/arm64: Move kvm_is_write_fault to header file

Colin Ian King (1):
      KVM: arm/arm64: fix spelling mistake: "auxilary" -> "auxiliary"

Dave Martin (1):
      arm64: KVM: Fix architecturally invalid reset value for FPEXC32_EL2

Gustavo A. R. Silva (1):
      kvm: Use struct_size() in kmalloc()

Jordan Niethe (1):
      KVM: PPC: Book3S HV: Fix build failure without IOMMU support

Kai Huang (1):
      kvm, x86, mmu: Use kernel generic dynamic physical address mask

Lan Tianyu (1):
      Revert "KVM: Eliminate extra function calls in kvm_get_dirty_log_protect()"

Leo Yan (1):
      KVM: Minor cleanups for kvm_main.c

Liu Jingqi (2):
      KVM: x86: expose MOVDIRI CPU feature into VM.
      KVM: x86: expose MOVDIR64B CPU feature into VM.

Luwei Kang (1):
      KVM: x86: Sync the pending Posted-Interrupts

Marc Zyngier (9):
      arm/arm64: KVM: Introduce kvm_call_hyp_ret()
      arm64: KVM: Allow for direct call of HYP functions when using VHE
      arm64: KVM: Drop VHE-specific HYP call stub
      ARM: KVM: Teach some form of type-safety to kvm_call_hyp
      arm/arm64: KVM: Statically configure the host's view of MPIDR
      KVM: arm64: Fix ICH_ELRSR_EL2 sysreg naming
      KVM: arm64: Reuse sys_reg() macro when searching the trap table
      KVM: arm/arm64: arch_timer: Mark physical interrupt active when a virtual interrupt is pending
      KVM: arm/arm64: Update MAINTAINERS entries

Marcelo Tosatti (1):
      x86: kvmguest: use TSC clocksource if invariant TSC is exposed

Masahiro Yamada (4):
      KVM: PPC: Remove -I. header search paths
      KVM: arm/arm64: Fix TRACE_INCLUDE_PATH
      KVM: arm/arm64: Remove -I. header search paths
      KVM: arm/arm64: Prefix header search paths with $(srctree)/

Michael Mueller (16):
      KVM: s390: clarify kvm related kernel message
      KVM: s390: drop obsolete else path
      KVM: s390: make bitmap declaration consistent
      KVM: s390: move bitmap idle_mask into arch struct top level
      KVM: s390: coding style kvm_s390_gisa_init/clear()
      KVM: s390: use pending_irqs_no_gisa() where appropriate
      KVM: s390: remove kvm_s390_ from gisa static inline functions
      KVM: s390: introduce struct kvm_s390_gisa_interrupt
      s390/cio: add function chsc_sgib()
      KVM: s390: add the GIB and its related life-cyle functions
      KVM: s390: add kvm reference to struct sie_page2
      KVM: s390: add functions to (un)register GISC with GISA
      KVM: s390: kvm_s390_gisa_clear() now clears the IPM only
      KVM: s390: add gib_alert_irq_handler()
      KVM: s390: start using the GIB
      KVM: s390: fix possible null pointer dereference in pending_irqs()

Nir Weiner (3):
      KVM: grow_halt_poll_ns() should never shrink vCPU halt_poll_ns
      KVM: Expose the initial start value in grow_halt_poll_ns() as a module parameter
      KVM: Never start grow vCPU halt_poll_ns from value below halt_poll_ns_grow_start

Paolo Bonzini (10):
      selftests: kvm: add selftest for releasing VM file descriptor while in L2
      KVM: x86: cull apicv code when userspace irqchip is requested
      KVM: nVMX: remove useless is_protmode check
      KVM: x86: cleanup freeing of nested state
      KVM: nVMX: do not start the preemption timer hrtimer unnecessarily
      Merge tag 'kvm-ppc-next-5.1-1' of git://git.kernel.org/.../paulus/powerpc into kvm-next
      Merge tag 'kvm-s390-next-5.1-1' of git://git.kernel.org/.../kvms390/linux into kvm-next
      Merge tag 'kvmarm-for-v5.1' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-next
      Merge tag 'kvm-ppc-next-5.1-3' of git://git.kernel.org/.../paulus/powerpc into HEAD
      kvm: vmx: fix formatting of a comment

Paul Mackerras (4):
      KVM: PPC: Book3S PR: Add emulation for slbfee. instruction
      KVM: PPC: Book3S: Allow XICS emulation to work in nested hosts using XIVE
      Merge remote-tracking branch 'remotes/powerpc/topic/ppc-kvm' into kvm-ppc-next
      KVM: PPC: Fix compilation when KVM is not enabled

Pavel Tatashin (1):
      x86/kvmclock: set offset for kvm unstable clock

Sean Christopherson (65):
      KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
      KVM: nVMX: Check a single byte for VMCS "launched" in nested early checks
      KVM: VMX: Zero out *all* general purpose registers after VM-Exit
      KVM: VMX: Modify only RSP when creating a placeholder for guest's RCX
      KVM: VMX: Save RSI to an unused output in the vCPU-run asm blob
      KVM: VMX: Manually load RDX in vCPU-run asm blob
      KVM: VMX: Let the compiler save/load RDX during vCPU-run
      KVM: nVMX: Remove a rogue "rax" clobber from nested_vmx_check_vmentry_hw()
      KVM: nVMX: Drop STACK_FRAME_NON_STANDARD from nested_vmx_check_vmentry_hw()
      KVM: nVMX: Explicitly reference the scratch reg in nested early checks
      KVM: nVMX: Capture VM-Fail to a local var in nested_vmx_check_vmentry_hw()
      KVM: nVMX: Capture VM-Fail via CC_{SET,OUT} in nested early checks
      KVM: nVMX: Reference vmx->loaded_vmcs->launched directly
      KVM: nVMX: Let the compiler select the reg for holding HOST_RSP
      KVM: nVMX: Cache host_rsp on a per-VMCS basis
      KVM: VMX: Load/save guest CR2 via C code in __vmx_vcpu_run()
      KVM: VMX: Update VMCS.HOST_RSP via helper C function
      KVM: VMX: Pass "launched" directly to the vCPU-run asm blob
      KVM: VMX: Invert the ordering of saving guest/host scratch reg at VM-Enter
      KVM: VMX: Don't save guest registers after VM-Fail
      KVM: VMX: Use vcpu->arch.regs directly when saving/loading guest state
      KVM: x86: Explicitly #define the VCPU_REGS_* indices
      KVM: VMX: Use #defines in place of immediates in VM-Enter inline asm
      KVM: VMX: Create a stack frame in vCPU-run
      KVM: VMX: Move vCPU-run code to a proper assembly routine
      KVM: VMX: Fold __vmx_vcpu_run() back into vmx_vcpu_run()
      KVM: VMX: Rename ____vmx_vcpu_run() to __vmx_vcpu_run()
      KVM: VMX: Use RAX as the scratch register during vCPU-run
      KVM: VMX: Pass @launched to the vCPU-run asm via standard ABI regs
      KVM: VMX: Return VM-Fail from vCPU-run assembly via standard ABI reg
      KVM: VMX: Preserve callee-save registers in vCPU-run asm sub-routine
      KVM: VMX: Call vCPU-run asm sub-routine from C and remove clobbering
      KVM: VMX: Reorder clearing of registers in the vCPU-run assembly flow
      KVM: nVMX: Sign extend displacements of VMX instr's mem operands
      KVM: nVMX: Apply addr size mask to effective address for VMX instructions
      KVM: nVMX: Ignore limit checks on VMX instructions using flat segments
      KVM: Call kvm_arch_memslots_updated() before updating memslots
      KVM: x86/mmu: Detect MMIO generation wrap in any address space
      KVM: x86/mmu: Do not cache MMIO accesses while memslots are in flux
      KVM: Explicitly define the "memslot update in-progress" bit
      KVM: x86: Use a u64 when passing the MMIO gen around
      KVM: x86: Refactor the MMIO SPTE generation handling
      KVM: Remove the hack to trigger memslot generation wraparound
      KVM: Move the memslot update in-progress flag to bit 63
      KVM: x86/mmu: Move slot_level_*() helper functions up a few lines
      KVM: x86/mmu: Split remote_flush+zap case out of kvm_mmu_flush_or_zap()
      KVM: x86/mmu: Zap only the relevant pages when removing a memslot
      Revert "KVM: MMU: document fast invalidate all pages"
      Revert "KVM: MMU: drop kvm_mmu_zap_mmio_sptes"
      KVM: x86/mmu: Voluntarily reschedule as needed when zapping MMIO sptes
      KVM: x86/mmu: Remove is_obsolete() call
      Revert "KVM: MMU: reclaim the zapped-obsolete page first"
      Revert "KVM: MMU: collapse TLB flushes when zap all pages"
      Revert "KVM: MMU: zap pages in batch"
      Revert "KVM: MMU: add tracepoint for kvm_mmu_invalidate_all_pages"
      Revert "KVM: MMU: show mmu_valid_gen in shadow page related tracepoints"
      Revert "KVM: x86: use the fast way to invalidate all pages"
      KVM: x86/mmu: skip over invalid root pages when zapping all sptes
      KVM: x86/mmu: Voluntarily reschedule as needed when zapping all sptes
      Revert "KVM: MMU: fast invalidate all pages"
      KVM: x86/mmu: Differentiate between nr zapped and list unstable
      KVM: x86/mmu: WARN if zapping a MMIO spte results in zapping children
      KVM: x86/mmu: Consolidate kvm_mmu_zap_all() and kvm_mmu_zap_mmio_sptes()
      MAINTAINERS: Add KVM selftests to existing KVM entry
      KVM: doc: Document the life cycle of a VM and its resources

Shaokun Zhang (2):
      KVM: arm/arm64: Remove unused gpa_end variable
      KVM: arm/arm64: Remove unused timer variable

Suraj Jitindar Singh (3):
      KVM: PPC: Book3S HV: Optimise mmio emulation for devices on FAST_MMIO_BUS
      KVM: PPC: Book3S HV: Add KVM stat largepages_[2M/1G]
      KVM: PPC: Book3S: Add count cache flush parameters to kvmppc_get_cpu_char()

Suthikulpanit, Suravee (2):
      svm: Fix AVIC DFR and LDR handling
      svm: Fix improper check when deactivate AVIC

Yu Zhang (1):
      kvm: vmx: Fix typos in vmentry/vmexit control setting

Zenghui Yu (1):
      KVM: arm64: Fix comment for KVM_PHYS_SHIFT

wangbo (1):
      KVM: PPC: Book3S HV: Replace kmalloc_node+memset with kzalloc_node

 Documentation/virtual/kvm/api.txt                  |  17 +
 Documentation/virtual/kvm/halt-polling.txt         |  37 +-
 Documentation/virtual/kvm/mmu.txt                  |  41 +-
 MAINTAINERS                                        |  19 +-
 arch/arm/include/asm/arch_gicv3.h                  |   4 +-
 arch/arm/include/asm/kvm_emulate.h                 |   8 +
 arch/arm/include/asm/kvm_host.h                    |  53 +-
 arch/arm/include/asm/kvm_hyp.h                     |   4 +
 arch/arm/include/asm/kvm_mmu.h                     |   9 +-
 arch/arm/kvm/Makefile                              |   5 +-
 arch/arm/kvm/coproc.c                              |  23 +-
 arch/arm/kvm/hyp/cp15-sr.c                         |   1 -
 arch/arm/kvm/hyp/hyp-entry.S                       |   2 +-
 arch/arm/kvm/hyp/switch.c                          |   2 +-
 arch/arm/kvm/hyp/tlb.c                             |   4 +-
 arch/arm/kvm/interrupts.S                          |   4 +-
 arch/arm64/include/asm/kvm_emulate.h               |  12 +
 arch/arm64/include/asm/kvm_host.h                  |  48 +-
 arch/arm64/include/asm/kvm_hyp.h                   |   3 +-
 arch/arm64/include/asm/kvm_mmu.h                   |  13 +-
 arch/arm64/include/asm/sysreg.h                    |   7 +-
 arch/arm64/kvm/Makefile                            |   4 +-
 arch/arm64/kvm/debug.c                             |   2 +-
 arch/arm64/kvm/hyp.S                               |   3 -
 arch/arm64/kvm/hyp/hyp-entry.S                     |  12 -
 arch/arm64/kvm/hyp/sysreg-sr.c                     |   1 -
 arch/arm64/kvm/sys_regs.c                          | 168 ++++--
 arch/mips/include/asm/kvm_host.h                   |   2 +-
 arch/powerpc/include/asm/kvm_host.h                |   5 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |  14 +
 arch/powerpc/include/uapi/asm/kvm.h                |   2 +
 arch/powerpc/kvm/book3s.c                          |  13 +-
 arch/powerpc/kvm/book3s_32_mmu.c                   |   1 +
 arch/powerpc/kvm/book3s_64_mmu.c                   |  14 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |  18 +
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |  15 +-
 arch/powerpc/kvm/book3s_64_vio.c                   |   8 +-
 arch/powerpc/kvm/book3s_emulate.c                  |  18 +
 arch/powerpc/kvm/book3s_hv.c                       |  33 +-
 arch/powerpc/kvm/book3s_hv_builtin.c               |  14 +-
 arch/powerpc/kvm/book3s_hv_rm_xics.c               |   7 +
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            |  10 +
 arch/powerpc/kvm/book3s_rtas.c                     |   8 +-
 arch/powerpc/kvm/powerpc.c                         |  22 +-
 arch/s390/include/asm/cio.h                        |   1 +
 arch/s390/include/asm/irq.h                        |   1 +
 arch/s390/include/asm/isc.h                        |   1 +
 arch/s390/include/asm/kvm_host.h                   |  39 +-
 arch/s390/kernel/irq.c                             |   1 +
 arch/s390/kvm/interrupt.c                          | 431 +++++++++++++--
 arch/s390/kvm/kvm-s390.c                           | 190 ++++++-
 arch/s390/kvm/kvm-s390.h                           |   4 +-
 arch/x86/include/asm/kvm_host.h                    |  42 +-
 arch/x86/include/asm/kvm_vcpu_regs.h               |  25 +
 arch/x86/kernel/kvmclock.c                         |  20 +-
 arch/x86/kvm/cpuid.c                               |   2 +-
 arch/x86/kvm/hyperv.c                              |   2 +-
 arch/x86/kvm/i8254.c                               |   2 +-
 arch/x86/kvm/i8259.c                               |   2 +-
 arch/x86/kvm/ioapic.c                              |   2 +-
 arch/x86/kvm/lapic.c                               |   7 +-
 arch/x86/kvm/mmu.c                                 | 466 ++++++++--------
 arch/x86/kvm/mmu.h                                 |   1 -
 arch/x86/kvm/mmutrace.h                            |  42 +-
 arch/x86/kvm/page_track.c                          |   2 +-
 arch/x86/kvm/svm.c                                 | 120 ++--
 arch/x86/kvm/vmx/nested.c                          | 129 +++--
 arch/x86/kvm/vmx/vmcs.h                            |   1 +
 arch/x86/kvm/vmx/vmenter.S                         | 167 ++++++
 arch/x86/kvm/vmx/vmx.c                             | 188 ++-----
 arch/x86/kvm/vmx/vmx.h                             |  20 +-
 arch/x86/kvm/x86.c                                 |  32 +-
 arch/x86/kvm/x86.h                                 |   7 +-
 drivers/clocksource/arm_arch_timer.c               |  11 +-
 drivers/s390/cio/chsc.c                            |  37 ++
 drivers/s390/cio/chsc.h                            |   1 +
 include/clocksource/arm_arch_timer.h               |   1 +
 include/kvm/arm_arch_timer.h                       |  68 ++-
 include/linux/kvm_host.h                           |  24 +-
 tools/testing/selftests/kvm/.gitignore             |   1 +
 tools/testing/selftests/kvm/Makefile               |   1 +
 .../kvm/x86_64/vmx_close_while_nested_test.c       |  95 ++++
 virt/kvm/arm/arch_timer.c                          | 608 +++++++++++++++------
 virt/kvm/arm/arm.c                                 |  64 +--
 virt/kvm/arm/hyp/vgic-v3-sr.c                      |   2 +-
 virt/kvm/arm/mmu.c                                 |  20 +-
 virt/kvm/arm/trace.h                               | 107 +++-
 virt/kvm/arm/vgic/vgic-v3.c                        |   4 +-
 virt/kvm/coalesced_mmio.c                          |   3 +-
 virt/kvm/eventfd.c                                 |   7 +-
 virt/kvm/irqchip.c                                 |   4 +-
 virt/kvm/kvm_main.c                                | 103 ++--
 virt/kvm/vfio.c                                    |   4 +-
 93 files changed, 2623 insertions(+), 1199 deletions(-)
```
#### [PATCH v3 01/17] powerpc/xive: add OPAL extensions for the XIVE native exploitation support
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The support for XIVE native exploitation mode in Linux/KVM needs a
couple more OPAL calls to get and set the state of the XIVE internal
structures being used by a sPAPR guest.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---

 Changes since v2:
 
 - remove extra OPAL call definitions

 arch/powerpc/include/asm/opal-api.h           |  7 +-
 arch/powerpc/include/asm/opal.h               |  7 ++
 arch/powerpc/include/asm/xive.h               | 14 +++
 arch/powerpc/sysdev/xive/native.c             | 99 +++++++++++++++++++
 .../powerpc/platforms/powernv/opal-wrappers.S |  3 +
 5 files changed, 127 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Load LPID and Flush TLB on Secondary Radix Threads
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When running with independent threads off the main thread is responsible
for collecting secondary threads on the core and giving them vcpus to
run. These secondary threads spin in kvm_no_guest until they are given a
vcore to run and then take the kvmppc_hv_entry entry path from
kvm_secondary_got_guest. However this entry path doesn't load the guest
LPID for a radix guest, assuming it has already been loaded in
kvmppc_radix_check_need_tlb_flush() which would be called from
kvmppc_run_core when running in independent threads on mode. This means
that the guest runs with the host LPID which leads to an unhandleable mmu
fault giving:

KVM: Got unsupported MMU fault
error: kvm run failed Bad address
NIP c000000000028d50   LR c00000000004cad4 CTR 0000000000000000 XER 0000000000000000 CPU#0
MSR 8000000002089033 HID0 0000000000000000  HF 8000000000000000 iidx 3 didx 3
TB 00000000 00000000 DECR 0
GPR00 c00000000004cad4 c00000003e543a10 c00000000105ea00 000000000000c800
GPR04 0000000000000002 0000000000000000 0000000000000000 0000000000000000
GPR08 0000000000000000 000000000000a001 00000000a77784ea 0000000002001001
GPR12 0000000000000000 c000000001240000 c000000000010b50 0000000000000000
GPR16 0000000000000000 0000000000000000 0000000000000000 0000000000000000
GPR20 0000000000000000 0000000000000000 0000000000000000 c00000003fe7c800
GPR24 0000000000000000 0000000000000004 c0000000011044f8 0000000000000001
GPR28 0000000000000001 0000000000000000 c0000000011044fc 000000000000c336
CR 48000424  [ G  L  -  -  -  G  E  G  ]             RES ffffffffffffffff
 SRR0 c00000000000e708  SRR1 8000000002009033    PVR 00000000004e1202 VRSAVE 0000000000000000
SPRG0 0000000000000000 SPRG1 c000000001240000  SPRG2 0000000000000000  SPRG3 0000000000000000
SPRG4 0000000000000000 SPRG5 0000000000000000  SPRG6 0000000000000000  SPRG7 0000000000000000
HSRR0 0000000000000000 HSRR1 0000000000000000
 CFAR 0000000000000000
 LPCR 0000000003d6f41f
 PTCR 0000000000000000   DAR 0000000000000000  DSISR 0000000000000000

Also we fail to perform the tlb flush if this vcpu has moved to this
core from another physical core which could result in stale tlb entries
being used.

To fix this we call kvmppc_radix_check_need_tlb_flush() from the
secondary entry path as well. This will both set the guest LPID and
check if the tlb needs to be flushed.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/include/asm/kvm_ppc.h      |  2 ++
 arch/powerpc/kernel/asm-offsets.c       |  1 +
 arch/powerpc/kvm/book3s_hv.c            | 41 +++++----------------------------
 arch/powerpc/kvm/book3s_hv_builtin.c    | 32 +++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 25 ++++++++++++--------
 5 files changed, 57 insertions(+), 44 deletions(-)

```
#### [PATCH kvmtool v1 1/2] vfio-pci: Release INTx's guest to host eventfd properly
##### From: Leo Yan <leo.yan@linaro.org>

```c
The PCI device INTx uses event fd 'unmask_fd' to signal the deassertion
of the line from guest to host; but this eventfd isn't released properly
when disable INTx.

When disable INTx this patch firstly unbinds interrupt signal by calling
ioctl VFIO_DEVICE_SET_IRQS and then it uses the new added field
'unmask_fd' in struct vfio_pci_device to close event fd.

Signed-off-by: Leo Yan <leo.yan@linaro.org>
---
 include/kvm/vfio.h |  1 +
 vfio/pci.c         | 15 ++++++++++++---
 2 files changed, 13 insertions(+), 3 deletions(-)

```
#### [PATCH RFC] KVM: x86: svm: make sure NMI is injected after nmi_singlestep
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
I noticed that apic test from kvm-unit-tests always hangs on my EPYC 7401P,
the hanging test nmi-after-sti is trying to deliver 30000 NMIs and tracing
shows that we're sometimes able to deliver a few but never all.

When we're trying to inject an NMI we may fail to do so immediately for
various reasons, however, we still need to inject it so enable_nmi_window()
arms nmi_singlestep mode. #DB occurs as expected, but we're not checking
for pending NMIs before entering the guest and unless there's a different
event to process, the NMI will never get delivered.

Make KVM_REQ_EVENT request on the vCPU from db_interception() to make sure
pending NMIs are checked and possibly injected.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- RFC: I'm not sure this is not part of some bigger issue I'm missing.
---
 arch/x86/kvm/svm.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v5 01/22] driver core: add per device iommu param
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

DMA faults can be detected by IOMMU at device level. Adding a pointer
to struct device allows IOMMU subsystem to report relevant faults
back to the device driver for further handling.
For direct assigned device (or user space drivers), guest OS holds
responsibility to handle and respond per device IOMMU fault.
Therefore we need fault reporting mechanism to propagate faults beyond
IOMMU subsystem.

There are two other IOMMU data pointers under struct device today, here
we introduce iommu_param as a parent pointer such that all device IOMMU
data can be consolidated here. The idea was suggested here by Greg KH
and Joerg. The name iommu_param is chosen here since iommu_data has been used.

Suggested-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Reviewed-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Link: https://lkml.org/lkml/2017/10/6/81
---
 include/linux/device.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH V2] cpufreq: Call transition notifier only once for each policy
##### From: Viresh Kumar <viresh.kumar@linaro.org>

```c
Currently we call these notifiers once for each CPU of the policy->cpus
cpumask. It would be more optimal if the notifier can be called only
once and all the relevant information be provided to it. Out of the 24
drivers that register for the transition notifiers today, only 5 of them
do per-cpu updates and the callback for the rest can be called only once
for the policy without any impact.

This would also avoid multiple function calls to the notifier callbacks
and reduce multiple iterations of notifier core's code (which does
locking as well).

This patch adds pointer to the cpufreq policy to the struct
cpufreq_freqs, so the notifier callback has all the information
available to it with a single call. The five drivers which perform
per-cpu updates are updated to use the cpufreq policy. The freqs->cpu
field is redundant now and is removed.

Acked-by: David S. Miller <davem@davemloft.net> (sparc)
Signed-off-by: Viresh Kumar <viresh.kumar@linaro.org>
---
V1->V2:
- Add cpufreq policy instead of cpus in struct cpufreq_freqs.
- Use policy->cpus instead of related_cpus everywhere in order not to
  change the existing behavior.
- Merged all 7 patches into a single patch.
- Updated changlog and included Ack from David.

 arch/arm/kernel/smp.c       | 24 +++++++++++++++---------
 arch/arm/kernel/smp_twd.c   |  9 ++++++---
 arch/sparc/kernel/time_64.c | 28 ++++++++++++++++------------
 arch/x86/kernel/tsc.c       | 32 +++++++++++++++++++++-----------
 arch/x86/kvm/x86.c          | 31 ++++++++++++++++++++-----------
 drivers/cpufreq/cpufreq.c   | 19 ++++++++++---------
 include/linux/cpufreq.h     | 14 +++++++-------
 7 files changed, 95 insertions(+), 62 deletions(-)

```
#### [PATCH][v2] KVM: fix error handling in svm_cpu_init
##### From: Li RongQing <lirongqing@baidu.com>

```c
sd->save_area should be freed in error path
rename labels to make them readable suggested by Vitaly

Fixes: 70cd94e60c733 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1-->v2: rename labels to make them readable suggested by Vitaly

 arch/x86/kvm/svm.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
