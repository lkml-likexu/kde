#### [GIT PULL] KVM fixes for 5.0-rc8 or final
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit a3b22b9f11d9fbc48b0291ea92259a5a810e9438:

  Linux 5.0-rc7 (2019-02-17 18:46:40 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to de3ccd26fafc707b09792d9b633c8b5b48865315:

  KVM: MMU: record maximum physical address width in kvm_mmu_extended_role (2019-02-22 19:25:10 +0100)

----------------------------------------------------------------
Bug fixes.

----------------------------------------------------------------
Paolo Bonzini (1):
      Merge tag 'kvm-s390-master-5.0' of git://git.kernel.org/.../kvms390/linux into kvm-master

Pierre Morel (1):
      s390: vsie: Use effective CRYCBD.31 to check CRYCBD validity

Vitaly Kuznetsov (1):
      x86/kvm/mmu: fix switch between root and guest MMUs

Yu Zhang (2):
      kvm: x86: Return LA57 feature based on hardware capability
      KVM: MMU: record maximum physical address width in kvm_mmu_extended_role

 arch/s390/kvm/vsie.c            |  2 +-
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/cpuid.c            |  4 ++++
 arch/x86/kvm/mmu.c              | 18 ++++++++++++++----
 4 files changed, 21 insertions(+), 5 deletions(-)
```
