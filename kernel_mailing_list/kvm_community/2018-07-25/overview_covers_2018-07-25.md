

#### [PATCH v3 0/6] KVM: nVMX: Enlightened VMCS for Hyper-V on KVM
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v2:
- Rebase to the current kvm/queue.
- Simplify clean fields check in prepare_vmcs02{,_full} and
  copy_enlightened_to_vmcs12() by resetting the clean fields mask in
  nested_vmx_handle_enlightened_vmptrld() when we switch from one L2 guest
  to another [Paolo Bonzini]
- Cope with the newly introduced vmx_get_nested_state() by returning
  -ENOTSUPP when eVMCS is in use. We'll do proper nested state save/restore
  later.

Description:

This is an initial implementation of Enlightened VMCS for nested Hyper-V on
KVM. Using it helps to spare 1500 cpu cycles for nested vmexit (tight cpuid
loop in WS2016 with Hyper-V role on KVM: 15200 cycles -> 13700 cycles).

Ladi Prosek (1):
  KVM: hyperv: define VP assist page helpers

Vitaly Kuznetsov (5):
  KVM: VMX: refactor evmcs_sanitize_exec_ctrls()
  KVM: nVMX: add KVM_CAP_HYPERV_ENLIGHTENED_VMCS capability
  KVM: nVMX: add enlightened VMCS state
  KVM: nVMX: implement enlightened VMPTRLD and VMCLEAR
  KVM: nVMX: optimize prepare_vmcs02{,_full} for Enlightened VMCS case

 arch/x86/include/asm/kvm_host.h |   3 +
 arch/x86/kvm/hyperv.c           |  23 +-
 arch/x86/kvm/hyperv.h           |   4 +
 arch/x86/kvm/lapic.c            |   4 +-
 arch/x86/kvm/lapic.h            |   2 +-
 arch/x86/kvm/svm.c              |   9 +
 arch/x86/kvm/vmx.c              | 824 +++++++++++++++++++++++++++++++++-------
 arch/x86/kvm/x86.c              |  17 +-
 include/uapi/linux/kvm.h        |   1 +
 9 files changed, 737 insertions(+), 150 deletions(-)
```
