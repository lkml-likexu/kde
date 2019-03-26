

#### [RFC PATCH 00/18] KVM: x86: clear HF_SMM_MASK before loading state
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Disclaimer: this is very much an RFC.  All patches are compile tested
only, the changelogs are non-existent and the order of the patches is
completely backwards in a lot of ways, e.g. the fix should really be
squeezed in much earlier.  I'd like to get feedback on the idea before
actually spending the effort to get it working.  Without further ado...

RSM emulation is currently broken on VMX when the interrupted guest has
CR4.VMXE=1.  There are a handful of ideas to fix the issue, but they are
all undesirable in some way, e.g. hacky, ugly, fragile, etc...

Rather than dance around the issue of HF_SMM_MASK being set when loading
SMSTATE into architectural state, rework RSM emulation itself to clear
HF_SMM_MASK prior to loading architectural state.  The basic concept is
to move the guts of em_rsm() out of the emulator and into x86.c as
leave_smm() so that leave_smm() can modify HF_SMM_MASK in a more granular
way, i.e. clear HF_SMM_MASK without triggerring kvm_smm_changed().

AFAICT, the only motivation for having HF_SMM_MASK set throughout is so
that the memory access from GET_SMSTATE() are tagged with role.smm (though
arguably even that is unnecessary).  This can be avoided by taking the
enter_smm() approach of reading all of SMSTATE into a buffer and then
loading state from the buffer.  Note, it's entirely possible this will
break horribly, commit 660a5d517aaa ("KVM: x86: save/load state on SMM
switch") does not provide any insight as to why enter_smm() buffers
memory while em_rsm() reads it piecemeal.

Almost all of the patches are unrelated cleanup to remove usage of
emulator function as much as possible, and to make leave_smm() mirror
enter_smm().

Lastly, even if this approach works, it likely makes sense to take
Vitaly's patch (to toggle HF_SMM_MASK when setting CR4 during RSM)
so that the actual fix less risky and can be easily backported.

Sean Christopherson (18):
  KVM: x86: Move emulation of RSM, i.e. leave_smm, out of emulator
  KVM: x86: Drop emulator_has_longmode()
  KVM: x86: Drop emulator_pre_leave_smm()
  KVM: x86: Drop emulator_set_hflags()
  KVM: x86: Add emulator_is_smm()
  KVM: x86: Add emulator_is_guest_mode()
  KVM: x86: Drop emulator_get_hflags()
  KVM: x86: Call set_nmi_mask() directly when leaving SMM
  KVM: x86: Call kvm_{get,set}_cr*() directly when leaving SMM
  KVM: x86: Call __kvm_set_dr() directly when leaving SMM
  KVM: x86: Call kvm_x86_ops.set_*dt() directly when leaving SMM
  KVM: x86: call emulator_set_msr() directly when leaving SMM
  KVM: x86: Drop x86_emulate_ops.read_phys()
  KVM: x86: Use kvm_set_segment() directly when leaving SMM
  KVM: x86: Invert passing of vcpu and ctxt when leaving SMM
  KVM: x86: Open code kvm_set_hflags
  KVM: x86: Load SMRAM in a single shot when leaving SMM
  KVM: x86: clear SMM flags before loading state while leaving SMM

 arch/x86/include/asm/kvm_emulate.h |  23 +-
 arch/x86/include/asm/kvm_host.h    |   5 +-
 arch/x86/kvm/emulate.c             | 310 +-----------------------
 arch/x86/kvm/svm.c                 |  30 +--
 arch/x86/kvm/vmx/vmx.c             |   4 +-
 arch/x86/kvm/x86.c                 | 377 ++++++++++++++++++++++++-----
 6 files changed, 348 insertions(+), 401 deletions(-)
```
