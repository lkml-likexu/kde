#### [GIT PULL] KVM fixes for 5.2-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit cd6c84d8f0cdc911df435bb075ba22ce3c605b07:

  Linux 5.2-rc2 (2019-05-26 16:49:19 -0700)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to f8d221d2e0e1572d0d60174c118e3554d1aa79fa:

  Merge tag 'kvm-s390-master-5.2-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-master (2019-06-01 00:49:02 +0200)

----------------------------------------------------------------

Fixes for PPC and s390.

----------------------------------------------------------------
Christian Borntraeger (1):
      kvm: fix compile on s390 part 2

Cédric Le Goater (7):
      KVM: PPC: Book3S HV: XIVE: Clear file mapping when device is released
      KVM: PPC: Book3S HV: XIVE: Do not test the EQ flag validity when resetting
      KVM: PPC: Book3S HV: XIVE: Fix the enforced limit on the vCPU identifier
      KVM: PPC: Book3S HV: XIVE: Introduce a new mutex for the XIVE device
      KVM: PPC: Book3S HV: XIVE: Do not clear IRQ data of passthrough interrupts
      KVM: PPC: Book3S HV: XIVE: Take the srcu read lock when accessing memslots
      KVM: PPC: Book3S HV: XIVE: Fix page offset when clearing ESB pages

Paolo Bonzini (2):
      Merge tag 'kvm-ppc-fixes-5.2-1' of git://git.kernel.org/.../paulus/powerpc into kvm-master
      Merge tag 'kvm-s390-master-5.2-2' of git://git.kernel.org/.../kvms390/linux into kvm-master

Paul Mackerras (5):
      KVM: PPC: Book3S HV: Avoid touching arch.mmu_ready in XIVE release functions
      KVM: PPC: Book3S HV: Use new mutex to synchronize MMU setup
      KVM: PPC: Book3S: Use new mutex to synchronize access to rtas token list
      KVM: PPC: Book3S HV: Don't take kvm->lock around kvm_for_each_vcpu
      KVM: PPC: Book3S HV: Fix lockdep warning when entering guest on POWER9

Suraj Jitindar Singh (1):
      KVM: PPC: Book3S HV: Restore SPRG3 in kvmhv_p9_guest_entry()

Thomas Huth (1):
      KVM: s390: Do not report unusabled IDs via KVM_CAP_MAX_VCPU_ID

 arch/mips/kvm/mips.c                  |   3 +
 arch/powerpc/include/asm/kvm_host.h   |   2 +
 arch/powerpc/kvm/book3s.c             |   1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c   |  36 ++++++------
 arch/powerpc/kvm/book3s_hv.c          |  48 ++++++++++------
 arch/powerpc/kvm/book3s_rtas.c        |  14 ++---
 arch/powerpc/kvm/book3s_xive.c        |  55 +++++++++----------
 arch/powerpc/kvm/book3s_xive.h        |   1 +
 arch/powerpc/kvm/book3s_xive_native.c | 100 +++++++++++++++++++---------------
 arch/powerpc/kvm/powerpc.c            |   3 +
 arch/s390/kvm/kvm-s390.c              |   1 +
 arch/x86/kvm/x86.c                    |   3 +
 virt/kvm/arm/arm.c                    |   3 +
 virt/kvm/kvm_main.c                   |   4 +-
 14 files changed, 157 insertions(+), 117 deletions(-)
```
