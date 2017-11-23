#### [GIT PULL] KVM fixes for 5.0-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit d7393226d15add056285c8fc86723d54d7e0c77d:

  Merge tag 'for-linus' of git://git.kernel.org/pub/scm/linux/kernel/git/rdma/rdma (2019-01-18 17:17:20 +1200)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to b2869f28e1476cd705bb28c58fd01b0bd661bb99:

  KVM: x86: Mark expected switch fall-throughs (2019-01-25 19:29:36 +0100)

----------------------------------------------------------------
Quite a few fixes for x86: nested virtualization save/restore, AMD nested virtualization
and virtual APIC, 32-bit fixes, an important fix to restore operation on older
processors, and a bunch of hyper-v bugfixes.  Several are marked stable.

There are also fixes for GCC warnings and for a GCC/objtool interaction.

----------------------------------------------------------------
Alexander Popov (1):
      KVM: x86: Fix single-step debugging

Ben Gardon (1):
      kvm: selftests: Fix region overlap check in kvm_util

Gustavo A. R. Silva (1):
      KVM: x86: Mark expected switch fall-throughs

Masahiro Yamada (1):
      KVM: x86: fix TRACE_INCLUDE_PATH and remove -I. header search paths

Sean Christopherson (4):
      KVM: VMX: Use the correct field var when clearing VM_ENTRY_LOAD_IA32_PERF_GLOBAL_CTRL
      KVM: x86: Fix PV IPIs for 32-bit KVM host
      KVM: x86: WARN_ONCE if sending a PV IPI returns a fatal error
      KVM: VMX: Move vmx_vcpu_run()'s VM-Enter asm blob to a helper function

Suravee Suthikulpanit (2):
      svm: Add warning message for AVIC IPI invalid target
      svm: Fix AVIC incomplete IPI emulation

Tom Roeder (1):
      kvm: x86/vmx: Use kzalloc for cached_vmcs12

Vitaly Kuznetsov (6):
      x86/kvm/hyper-v: don't announce GUEST IDLE MSR support
      x86/kvm/hyper-v: don't recommend doing reset via synthetic MSR
      x86/kvm/hyper-v: recommend using eVMCS only when it is enabled
      KVM: nSVM: clear events pending from svm_complete_interrupts() when exiting to L1
      x86/kvm/hyper-v: nested_enable_evmcs() sets vmcs_version incorrectly
      KVM: selftests: check returned evmcs version range

Yi Wang (1):
      kvm: vmx: fix some -Wmissing-prototypes warnings

 arch/x86/kernel/kvm.c                           |   7 +-
 arch/x86/kvm/Makefile                           |   4 -
 arch/x86/kvm/hyperv.c                           |   7 +-
 arch/x86/kvm/lapic.c                            |   2 +
 arch/x86/kvm/mmu.c                              |   1 +
 arch/x86/kvm/svm.c                              |  31 +++--
 arch/x86/kvm/trace.h                            |   2 +-
 arch/x86/kvm/vmx/evmcs.c                        |   7 +-
 arch/x86/kvm/vmx/nested.c                       |  14 ++-
 arch/x86/kvm/vmx/vmx.c                          | 147 +++++++++++++-----------
 arch/x86/kvm/x86.c                              |   8 +-
 tools/testing/selftests/kvm/lib/kvm_util.c      |   9 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c |   6 +
 13 files changed, 130 insertions(+), 115 deletions(-)
```
