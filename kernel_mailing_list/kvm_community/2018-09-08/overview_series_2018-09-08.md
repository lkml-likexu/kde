#### [GIT PULL] KVM fixes for Linux 4.19-rc3
##### From: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>

```c
Linus,

The following changes since commit 57361846b52bc686112da6ca5368d11210796804:

  Linux 4.19-rc2 (2018-09-02 14:37:30 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm tags/for-linus

for you to fetch changes up to bdf7ffc89922a52a4f08a12f7421ea24bb7626a0:

  KVM: LAPIC: Fix pv ipis out-of-bounds access (2018-09-07 18:38:43 +0200)

----------------------------------------------------------------
KVM fixes for 4.19-rc3

ARM:
 - Fix a VFP corruption in 32-bit guest
 - Add missing cache invalidation for CoW pages
 - Two small cleanups

s390:
 - Fallout from the hugetlbfs support: pfmf interpretion and locking
 - VSIE: fix keywrapping for nested guests

PPC:
 - Fix a bug where pages might not get marked dirty, causing
   guest memory corruption on migration,
 - Fix a bug causing reads from guest memory to use the wrong guest
   real address for very large HPT guests (>256G of memory), leading to
   failures in instruction emulation.

x86:
 - Fix out of bound access from malicious pv ipi hypercalls (introduced
   in rc1)
 - Fix delivery of pending interrupts when entering a nested guest,
   preventing arbitrarily late injection
 - Sanitize kvm_stat output after destroying a guest
 - Fix infinite loop when emulating a nested guest page fault
   and improve the surrounding emulation code
 - Two minor cleanups

----------------------------------------------------------------
Colin Ian King (1):
      KVM: SVM: remove unused variable dst_vaddr_end

Janosch Frank (2):
      KVM: s390: Fix pfmf and conditional skey emulation
      KVM: s390: Properly lock mm context allow_gmap_hpage_1m setting

Liran Alon (1):
      KVM: nVMX: Fix loss of pending IRQ/NMI before entering L2

Marc Zyngier (3):
      KVM: arm/arm64: Clean dcache to PoC when changing PTE due to CoW
      arm64: KVM: Only force FPEXC32_EL2.EN if trapping FPSIMD
      KVM: Remove obsolete kvm_unmap_hva notifier backend

Paul Mackerras (2):
      KVM: PPC: Book3S HV: Use correct pagesize in kvm_unmap_radix()
      KVM: PPC: Book3S HV: Don't truncate HPTE index in xlate function

Pierre Morel (1):
      KVM: s390: vsie: copy wrapping keys to right place

Radim Krčmář (3):
      Merge tag 'kvm-ppc-fixes-4.19-1' of git://git.kernel.org/.../paulus/powerpc
      Merge tag 'kvm-s390-master-4.19-1' of git://git.kernel.org/.../kvms390/linux
      Merge tag 'kvm-arm-fixes-for-v4.19-v2' of git://git.kernel.org/.../kvmarm/kvmarm

Sean Christopherson (8):
      KVM: VMX: Do not allow reexecute_instruction() when skipping MMIO instr
      KVM: x86: SVM: Set EMULTYPE_NO_REEXECUTE for RSM emulation
      KVM: x86: Invert emulation re-execute behavior to make it opt-in
      KVM: x86: Merge EMULTYPE_RETRY and EMULTYPE_ALLOW_REEXECUTE
      KVM: x86: Default to not allowing emulation retry in kvm_mmu_page_fault
      KVM: x86: Do not re-{try,execute} after failed emulation in L2
      KVM: x86: Rename emulate_instruction() to kvm_emulate_instruction()
      KVM: x86: Unexport x86_emulate_instruction()

Stefan Raspl (7):
      tools/kvm_stat: fix python3 issues
      tools/kvm_stat: fix handling of invalid paths in debugfs provider
      tools/kvm_stat: fix updates for dead guests
      tools/kvm_stat: don't reset stats when setting PID filter for debugfs
      tools/kvm_stat: handle guest removals more gracefully
      tools/kvm_stat: indicate dead guests as such
      tools/kvm_stat: re-animate display of dead guests

Steven Price (1):
      arm64: KVM: Remove pgd_lock

Vitaly Kuznetsov (1):
      KVM: nVMX: avoid redundant double assignment of nested_run_pending

Wanpeng Li (1):
      KVM: LAPIC: Fix pv ipis out-of-bounds access

 arch/arm/include/asm/kvm_host.h        |  1 -
 arch/arm64/include/asm/kvm_host.h      |  4 +--
 arch/arm64/kvm/hyp/switch.c            |  9 ++++--
 arch/mips/include/asm/kvm_host.h       |  1 -
 arch/mips/kvm/mmu.c                    | 10 ------
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  6 ++--
 arch/s390/include/asm/mmu.h            |  8 ++++-
 arch/s390/kvm/kvm-s390.c               |  2 ++
 arch/s390/kvm/priv.c                   | 30 ++++++++++-------
 arch/s390/kvm/vsie.c                   |  3 +-
 arch/x86/include/asm/kvm_host.h        | 22 ++++---------
 arch/x86/kvm/lapic.c                   | 27 ++++++++++++----
 arch/x86/kvm/mmu.c                     | 26 ++++++++-------
 arch/x86/kvm/svm.c                     | 19 ++++++-----
 arch/x86/kvm/vmx.c                     | 43 ++++++++++++++++++-------
 arch/x86/kvm/x86.c                     | 28 +++++++++++++---
 arch/x86/kvm/x86.h                     |  2 ++
 tools/kvm/kvm_stat/kvm_stat            | 59 ++++++++++++++++++++++++++++------
 virt/kvm/arm/mmu.c                     | 21 +++++-------
 virt/kvm/arm/trace.h                   | 15 ---------
 21 files changed, 204 insertions(+), 134 deletions(-)
```
