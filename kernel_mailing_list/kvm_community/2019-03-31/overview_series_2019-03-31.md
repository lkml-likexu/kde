#### [GIT PULL] KVM fixes for Linux 5.1-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 8c2ffd9174779014c3fe1f96d9dc3641d9175f00:

  Linux 5.1-rc2 (2019-03-24 14:02:26 -0700)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 690edec54cbaa0e98dc592aae6864272f48f3c84:

  Merge tag 'kvmarm-fixes-for-5.1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2019-03-28 19:07:30 +0100)

----------------------------------------------------------------

A collection of x86 and ARM bugfixes, and some improvements to documentation.

On top of this, a cleanup of kvm_para.h headers, which were exported by
some architectures even though they not support KVM at all.  This is
responsible for all the Kbuild changes in the diffstat.

----------------------------------------------------------------
Ben Gardon (1):
      kvm: mmu: Used range based flushing in slot_handle_level_range

Krish Sadhukhan (1):
      kvm: nVMX: Add a vmentry check for HOST_SYSENTER_ESP and HOST_SYSENTER_EIP fields

Marc Zyngier (4):
      KVM: arm64: Reset the PMU in preemptible context
      arm64: KVM: Always set ICH_HCR_EL2.EN if GICv4 is enabled
      KVM: arm/arm64: vgic-its: Take the srcu lock when writing to guest memory
      KVM: arm/arm64: vgic-its: Take the srcu lock when parsing the memslots

Masahiro Yamada (1):
      KVM: export <linux/kvm_para.h> and <asm/kvm_para.h> iif KVM is supported

Paolo Bonzini (2):
      Documentation: kvm: clarify KVM_SET_USER_MEMORY_REGION
      Merge tag 'kvmarm-fixes-for-5.1' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

Sean Christopherson (11):
      KVM: nVMX: Do not inherit quadrant and invalid for the root shadow EPT
      KVM: x86: fix handling of role.cr4_pae and rename it to 'gpte_size'
      KVM: doc: Fix incorrect word ordering regarding supported use of APIs
      KVM: Reject device ioctls from processes other than the VM's creator
      KVM: x86: Emulate MSR_IA32_ARCH_CAPABILITIES on AMD hosts
      KVM: x86: update %rip after emulating IO
      KVM: selftests: assert on exit reason in CR4/cpuid sync test
      KVM: selftests: explicitly disable PIE for tests
      KVM: selftests: disable stack protector for all KVM tests
      KVM: selftests: complete IO before migrating guest state
      KVM: doc: Document the life cycle of a VM and its resources

Sebastian Andrzej Siewior (1):
      kvm: don't redefine flags as something else

Singh, Brijesh (1):
      KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)

Suzuki K Poulose (2):
      KVM: arm/arm64: Enforce PTE mappings at stage2 when needed
      KVM: arm/arm64: Fix handling of stage2 huge mappings

Vitaly Kuznetsov (1):
      x86/kvm/hyper-v: avoid spurious pending stimer on vCPU init

Wei Yang (1):
      KVM: x86: remove check on nr_mmu_pages in kvm_arch_commit_memory_region()

Xiaoyao Li (1):
      kvm/x86: Move MSR_IA32_ARCH_CAPABILITIES to array emulated_msrs

YueHaibing (1):
      KVM: arm/arm64: vgic-its: Make attribute accessors static

Zenghui Yu (1):
      KVM: arm/arm64: Comments cleanup in mmu.c

 Documentation/virtual/kvm/api.txt                  |  77 +++++++++----
 Documentation/virtual/kvm/mmu.txt                  |  11 +-
 arch/alpha/include/asm/Kbuild                      |   1 +
 arch/alpha/include/uapi/asm/kvm_para.h             |   2 -
 arch/arc/include/asm/Kbuild                        |   1 +
 arch/arc/include/uapi/asm/Kbuild                   |   1 -
 arch/arm/include/asm/kvm_mmu.h                     |  11 ++
 arch/arm/include/asm/stage2_pgtable.h              |   2 +
 arch/arm/include/uapi/asm/Kbuild                   |   1 +
 arch/arm/include/uapi/asm/kvm_para.h               |   2 -
 arch/arm64/include/asm/kvm_mmu.h                   |  11 ++
 arch/arm64/kvm/reset.c                             |   6 +-
 arch/c6x/include/asm/Kbuild                        |   1 +
 arch/c6x/include/uapi/asm/Kbuild                   |   1 -
 arch/h8300/include/asm/Kbuild                      |   1 +
 arch/h8300/include/uapi/asm/Kbuild                 |   1 -
 arch/hexagon/include/asm/Kbuild                    |   1 +
 arch/hexagon/include/uapi/asm/kvm_para.h           |   2 -
 arch/ia64/include/asm/Kbuild                       |   1 +
 arch/ia64/include/uapi/asm/Kbuild                  |   1 -
 arch/m68k/include/asm/Kbuild                       |   1 +
 arch/m68k/include/uapi/asm/Kbuild                  |   1 -
 arch/microblaze/include/asm/Kbuild                 |   1 +
 arch/microblaze/include/uapi/asm/Kbuild            |   1 -
 arch/nios2/include/asm/Kbuild                      |   1 +
 arch/nios2/include/uapi/asm/Kbuild                 |   1 -
 arch/openrisc/include/asm/Kbuild                   |   1 +
 arch/openrisc/include/uapi/asm/Kbuild              |   1 -
 arch/parisc/include/asm/Kbuild                     |   1 +
 arch/parisc/include/uapi/asm/Kbuild                |   1 -
 arch/sh/include/asm/Kbuild                         |   1 +
 arch/sh/include/uapi/asm/Kbuild                    |   1 -
 arch/sparc/include/asm/Kbuild                      |   1 +
 arch/sparc/include/uapi/asm/kvm_para.h             |   2 -
 arch/unicore32/include/asm/Kbuild                  |   1 +
 arch/unicore32/include/uapi/asm/Kbuild             |   1 -
 arch/x86/include/asm/kvm_host.h                    |  10 +-
 arch/x86/kvm/hyperv.c                              |   9 +-
 arch/x86/kvm/mmu.c                                 |  54 ++++++---
 arch/x86/kvm/mmutrace.h                            |   4 +-
 arch/x86/kvm/svm.c                                 |  32 ++++++
 arch/x86/kvm/vmx/nested.c                          |   5 +
 arch/x86/kvm/vmx/vmx.c                             |  19 +---
 arch/x86/kvm/vmx/vmx.h                             |   1 -
 arch/x86/kvm/x86.c                                 |  59 +++++++---
 arch/xtensa/include/asm/Kbuild                     |   1 +
 arch/xtensa/include/uapi/asm/Kbuild                |   1 -
 include/uapi/linux/Kbuild                          |   2 +
 tools/testing/selftests/kvm/Makefile               |   4 +-
 tools/testing/selftests/kvm/include/kvm_util.h     |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  16 +++
 .../selftests/kvm/x86_64/cr4_cpuid_sync_test.c     |  35 +++---
 tools/testing/selftests/kvm/x86_64/state_test.c    |  18 ++-
 virt/kvm/arm/hyp/vgic-v3-sr.c                      |   4 +-
 virt/kvm/arm/mmu.c                                 | 125 ++++++++++++---------
 virt/kvm/arm/vgic/vgic-its.c                       |  31 +++--
 virt/kvm/arm/vgic/vgic-v3.c                        |   4 +-
 virt/kvm/arm/vgic/vgic.c                           |  14 ++-
 virt/kvm/eventfd.c                                 |   6 +-
 virt/kvm/kvm_main.c                                |   3 +
 60 files changed, 409 insertions(+), 201 deletions(-)
 delete mode 100644 arch/alpha/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/hexagon/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/sparc/include/uapi/asm/kvm_para.h
```
