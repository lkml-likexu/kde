

#### [PATCH 00/16] KVM: nVMX: add option to perform early consistency
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

For performance reasons, KVM defers many consistency checks to the
CPU, including checks that result in VMFail (as opposed to VMExit).
This behavior may be undesirable for some users since KVM detects
certain classes of VMFail only after it has processed guest state,
e.g. emulated MSR load-on-entry.  Because there is a strict ordering
between checks that cause VMFail and those that cause VMExit, i.e.
all VMFail checks are performed before any checks that cause VMExit,
we can detect all VMFail conditions via an early VMEnter that will
trigger a consistency check VMExit in the "success" path.

Inserting a pre-check VMEnter into the nested VMEnter code is not
a complex process in an of itself, but it requires a fair amount
of refactoring to split prepare_vmcs02() so that there is a point
where vmcs02 can pass the VMFail checks without requiring KVM to
process guest state.

During the refactoring and testing, a number of pre-existing bugs
(patches 1-4) and easy optimization points (patches 5-6 and 14)
were encountered.

Ideally, these patches would be split into 3-4 separate series,
especially the bug fix patches.  I smushed everything into a single
series because the early VMEnter code breaks without the bug fixes,
and the refactoring shuffles the same code.  For example, I thought
patch 14 "KVM: vmx: write HOST_IA32_EFER in vmx_set_constant_host_state()"
was a standalone patch and sent it as such before belatedly realizing
the early VMEnter was relying on the new behavior to set HOST_EFER.

Patch Synopsis:
  1-4:   bug fixes
  5-6:   optimizations
  7:     function rename
  8:     bug fix and refactoring
  9-12:  refactoring
  13:    bug fix
  14:    optimization and prereq for early consistency checks
  15-16: early consistency checks
  

Sean Christopherson (16):
  KVM: nVMX: move host EFER consistency checks to VMFail path
  KVM: nVMX: move vmcs12 EPTP consistency check to
    check_vmentry_prereqs()
  KVM: nVMX: use vm_exit_controls_init() to write exit controls for
    vmcs02
  KVM: nVMX: reset cache/shadows on nested consistency check VMExit
  KVM: vmx: do not unconditionally clear EFER switching
  KVM: nVMX: try to set EFER bits correctly when init'ing entry controls
  KVM: nVMX: rename enter_vmx_non_root_mode to
    nested_vmx_enter_non_root_mode
  KVM: nVMX: move check_vmentry_postreqs() call to
    nested_vmx_enter_non_root_mode()
  KVM: nVMX: assimilate nested_vmx_entry_failure() into
    nested_vmx_enter_non_root_mode()
  KVM: nVMX: split pieces of prepare_vmcs02() to prepare_vmcs02_early()
  KVM: nVMX: do early preparation of vmcs02 before
    check_vmentry_postreqs()
  KVM: nVMX: refactor inner section of nested_vmx_enter_non_root_mode()
  KVM: nVMX: do not skip VMEnter instruction that succeeds
  KVM: vmx: write HOST_IA32_EFER in vmx_set_constant_host_state()
  KVM: nVMX: add option to perform early consistency checks via H/W
  KVM: nVMX: WARN if nested run hits VMFail with early consistency
    checks enabled

 arch/x86/kvm/vmx.c | 780 ++++++++++++++++++++++++++++-----------------
 1 file changed, 481 insertions(+), 299 deletions(-)
```
