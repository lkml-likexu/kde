#### [GIT PULL] Second batch of KVM changes for 5.3 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 964a4eacef67503a1154f7e0a75f52fbdce52022:

  Merge tag 'dlm-5.3' of git://git.kernel.org/pub/scm/linux/kernel/git/teigland/linux-dlm (2019-07-12 17:37:53 -0700)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 30cd8604323dbaf20a80e797fe7057f5b02e394d:

  KVM: x86: Add fixed counters to PMU filter (2019-07-20 09:00:48 +0200)

----------------------------------------------------------------
Mostly bugfixes, but also:
- s390 support for KVM selftests
- LAPIC timer offloading to housekeeping CPUs
- Extend an s390 optimization for overcommitted hosts to all architectures
- Debugging cleanups and improvements

----------------------------------------------------------------
Arnd Bergmann (2):
      x86: kvm: avoid -Wsometimes-uninitized warning
      x86: kvm: avoid constant-conversion warning

Christian Borntraeger (1):
      KVM: selftests: enable pgste option for the linker on s390

Eric Hankland (1):
      KVM: x86: Add fixed counters to PMU filter

Jing Liu (1):
      KVM: x86: expose AVX512_BF16 feature to guest

Like Xu (2):
      KVM: x86/vPMU: reset pmc->counter to 0 for pmu fixed_counters
      KVM: x86/vPMU: refine kvm_pmu err msg when event creation failed

Liran Alon (2):
      KVM: nVMX: Ignore segment base for VMX memory operand when segment not FS or GS
      KVM: SVM: Fix detection of AMD Errata 1096

Paolo Bonzini (3):
      Merge tag 'kvm-s390-next-5.3-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      KVM: VMX: dump VMCS on failed entry
      KVM: nVMX: do not use dangling shadow VMCS after guest reset

Thomas Huth (7):
      KVM: selftests: Guard struct kvm_vcpu_events with __KVM_HAVE_VCPU_EVENTS
      KVM: selftests: Introduce a VM_MODE_DEFAULT macro for the default bits
      KVM: selftests: Align memory region addresses to 1M on s390x
      KVM: selftests: Add processor code for s390x
      KVM: selftests: Add the sync_regs test for s390x
      KVM: selftests: Move kvm_create_max_vcpus test to generic code
      KVM: selftests: Remove superfluous define from vmx.c

Wanpeng Li (4):
      KVM: LAPIC: Make lapic timer unpinned
      KVM: LAPIC: Inject timer interrupt via posted interrupt
      KVM: Boost vCPUs that are delivering interrupts
      KVM: s390: Use kvm_vcpu_wake_up in kvm_s390_vcpu_wakeup

Yi Wang (3):
      kvm: vmx: fix coccinelle warnings
      kvm: x86: some tsc debug cleanup
      kvm: x86: ioapic and apic debug macros cleanup

 Documentation/virtual/kvm/api.txt                  |  15 +-
 MAINTAINERS                                        |   2 +
 arch/s390/kvm/interrupt.c                          |  23 +-
 arch/x86/include/uapi/asm/kvm.h                    |   9 +-
 arch/x86/kvm/cpuid.c                               |  12 +-
 arch/x86/kvm/hyperv.c                              |  20 +-
 arch/x86/kvm/ioapic.c                              |  15 --
 arch/x86/kvm/lapic.c                               | 202 ++++++---------
 arch/x86/kvm/lapic.h                               |   1 +
 arch/x86/kvm/mmu.c                                 |   6 +-
 arch/x86/kvm/pmu.c                                 |  27 +-
 arch/x86/kvm/svm.c                                 |  42 +++-
 arch/x86/kvm/vmx/nested.c                          |  13 +-
 arch/x86/kvm/vmx/pmu_intel.c                       |  11 +-
 arch/x86/kvm/vmx/vmx.c                             |   6 +-
 arch/x86/kvm/x86.c                                 |  20 +-
 arch/x86/kvm/x86.h                                 |   2 +
 include/linux/kvm_host.h                           |   1 +
 include/linux/sched/isolation.h                    |   6 +
 kernel/sched/isolation.c                           |   6 +
 tools/testing/selftests/kvm/Makefile               |  14 +-
 tools/testing/selftests/kvm/include/kvm_util.h     |   8 +
 .../selftests/kvm/include/s390x/processor.h        |  22 ++
 .../kvm/{x86_64 => }/kvm_create_max_vcpus.c        |   2 +-
 .../testing/selftests/kvm/lib/aarch64/processor.c  |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |  23 +-
 tools/testing/selftests/kvm/lib/s390x/processor.c  | 278 +++++++++++++++++++++
 tools/testing/selftests/kvm/lib/x86_64/processor.c |   2 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       |   2 -
 tools/testing/selftests/kvm/s390x/sync_regs_test.c | 151 +++++++++++
 virt/kvm/kvm_main.c                                |  12 +-
 31 files changed, 723 insertions(+), 232 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/processor.h
 rename tools/testing/selftests/kvm/{x86_64 => }/kvm_create_max_vcpus.c (95%)
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/processor.c
 create mode 100644 tools/testing/selftests/kvm/s390x/sync_regs_test.c
```
