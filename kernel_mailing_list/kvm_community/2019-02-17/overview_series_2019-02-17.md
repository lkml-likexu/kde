#### [GIT PULL] KVM changes for Linux 5.0-rc7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit d13937116f1e82bf508a6325111b322c30c85eb9:

  Linux 5.0-rc6 (2019-02-10 14:42:20 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 98ae70cc476e833332a2c6bb72f941a25f0de226:

  kvm: vmx: Fix entry number check for add_atomic_switch_msr() (2019-02-14 16:22:20 +0100)

----------------------------------------------------------------
A somewhat bigger ARM update, and the usual smattering
of x86 bug fixes.

----------------------------------------------------------------
Christoffer Dall (2):
      KVM: arm/arm64: Reset the VCPU without preemption and vcpu state loaded
      KVM: arm/arm64: vgic: Always initialize the group of private IRQs

James Morse (1):
      KVM: arm64: Forbid kprobing of the VHE world-switch code

Julien Thierry (3):
      KVM: arm/arm64: vgic: Make vgic_irq->irq_lock a raw_spinlock
      KVM: arm/arm64: vgic: Make vgic_dist->lpi_list_lock a raw_spinlock
      KVM: arm/arm64: vgic: Make vgic_cpu->ap_list_lock a raw_spinlock

Luwei Kang (1):
      KVM: x86: Recompute PID.ON when clearing PID.SN

Marc Zyngier (4):
      arm64: KVM: Don't generate UNDEF when LORegion feature is present
      arm/arm64: KVM: Allow a VCPU to fully reset itself
      arm/arm64: KVM: Don't panic on failure to properly reset system registers
      arm: KVM: Add missing kvm_stage2_has_pmd() helper

Paolo Bonzini (1):
      Merge tag 'kvm-arm-fixes-for-5.0' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

Sean Christopherson (1):
      KVM: nVMX: Restore a preemption timer consistency check

Suzuki K Poulose (1):
      KVM: arm64: Relax the restriction on using stage2 PUD huge mapping

Vitaly Kuznetsov (1):
      x86/kvm/nVMX: read from MSR_IA32_VMX_PROCBASED_CTLS2 only when it is available

Xiaoyao Li (1):
      kvm: vmx: Fix entry number check for add_atomic_switch_msr()

 arch/arm/include/asm/kvm_host.h       |  10 +++
 arch/arm/include/asm/stage2_pgtable.h |   5 ++
 arch/arm/kvm/coproc.c                 |   4 +-
 arch/arm/kvm/reset.c                  |  24 +++++++
 arch/arm64/include/asm/kvm_host.h     |  11 ++++
 arch/arm64/kvm/hyp/switch.c           |   5 ++
 arch/arm64/kvm/hyp/sysreg-sr.c        |   5 ++
 arch/arm64/kvm/reset.c                |  50 +++++++++++++-
 arch/arm64/kvm/sys_regs.c             |  50 ++++++++------
 arch/x86/kvm/vmx/nested.c             |  12 +++-
 arch/x86/kvm/vmx/vmx.c                |  29 ++++-----
 arch/x86/kvm/vmx/vmx.h                |  10 +--
 arch/x86/kvm/x86.c                    |   2 +-
 include/kvm/arm_vgic.h                |   6 +-
 virt/kvm/arm/arm.c                    |  10 +++
 virt/kvm/arm/mmu.c                    |   9 ++-
 virt/kvm/arm/psci.c                   |  36 +++++------
 virt/kvm/arm/vgic/vgic-debug.c        |   4 +-
 virt/kvm/arm/vgic/vgic-init.c         |  30 +++++----
 virt/kvm/arm/vgic/vgic-its.c          |  22 +++----
 virt/kvm/arm/vgic/vgic-mmio-v2.c      |  14 ++--
 virt/kvm/arm/vgic/vgic-mmio-v3.c      |  12 ++--
 virt/kvm/arm/vgic/vgic-mmio.c         |  34 +++++-----
 virt/kvm/arm/vgic/vgic-v2.c           |   4 +-
 virt/kvm/arm/vgic/vgic-v3.c           |   8 +--
 virt/kvm/arm/vgic/vgic.c              | 118 +++++++++++++++++-----------------
 26 files changed, 331 insertions(+), 193 deletions(-)
```
