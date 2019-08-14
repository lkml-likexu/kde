

#### [PATCH v2 0/3] powerpc/xive: Fix race condition leading to host
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

This series fixes a race condition that has been observed in testing
on POWER9 machines running KVM guests.  An interrupt being freed by
free_irq() can have an instance present in a XIVE interrupt queue,
which can then be presented to the generic interrupt code after the
data structures for it have been freed, leading to a variety of
crashes and hangs.

This series is based on current upstream kernel source plus Cédric Le
Goater's patch "KVM: PPC: Book3S HV: XIVE: Free escalation interrupts
before disabling the VP", which is a pre-requisite for this series.
As it touches both KVM and generic PPC code, this series will probably
go in via Michael Ellerman's powerpc tree.

V2 of this patch series adds a patch fixing a bug noticed by Cédric,
and also fixes a bug in patch 1/2 of the v1 series.

Paul.

 arch/powerpc/include/asm/xive.h         |  8 +++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 38 +++++++++-----
 arch/powerpc/kvm/book3s_xive.c          | 42 +++++++++++++++-
 arch/powerpc/kvm/book3s_xive.h          |  2 +
 arch/powerpc/kvm/book3s_xive_native.c   |  6 +++
 arch/powerpc/sysdev/xive/common.c       | 87 ++++++++++++++++++++++++---------
 6 files changed, 146 insertions(+), 37 deletions(-)
```
#### [PATCH v4 0/7] x86: KVM: svm: get rid of hardcoded instructions
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v3 [Sean Christopherson]:
- add Reviewed-by tag to PATCH5
- __skip_emulated_instruction()/skip_emulated_instruction() split,
  'unlikely(r != EMULATE_DONE)' in PATCH2
- Make nested_svm_vmrun() return an int in PATCH6 (moved from PATCH7)
- Avoid weird-looking 'if (rc) return ret' in PATCH7

Original description:

Jim rightfully complains that hardcoding instuctions lengths is not always
correct: additional (redundant) prefixes can be used. Luckily, the ugliness
is mostly harmless: modern AMD CPUs support NRIP_SAVE feature but I'd like
to clean things up and sacrifice speed in favor of correctness.

Vitaly Kuznetsov (7):
  x86: KVM: svm: don't pretend to advance RIP in case
    wrmsr_interception() results in #GP
  x86: kvm: svm: propagate errors from skip_emulated_instruction()
  x86: KVM: clear interrupt shadow on EMULTYPE_SKIP
  x86: KVM: add xsetbv to the emulator
  x86: KVM: svm: remove hardcoded instruction length from intercepts
  x86: KVM: svm: eliminate weird goto from vmrun_interception()
  x86: KVM: svm: eliminate hardcoded RIP advancement from
    vmrun_interception()

 arch/x86/include/asm/kvm_emulate.h |   3 +-
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/emulate.c             |  23 ++++++-
 arch/x86/kvm/svm.c                 | 100 +++++++++++++----------------
 arch/x86/kvm/vmx/vmx.c             |  16 ++++-
 arch/x86/kvm/x86.c                 |  13 +++-
 6 files changed, 92 insertions(+), 65 deletions(-)
```
