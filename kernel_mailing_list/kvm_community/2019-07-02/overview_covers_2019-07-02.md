

#### [PATCH 0/3] KVM: nVMX: fixes for host get/set MSR
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

These are three small bugs that were found while implementing QEMU
support for user-specified VMX features.

Paolo

Paolo Bonzini (3):
  KVM: nVMX: include conditional controls in /dev/kvm KVM_GET_MSRS
  KVM: nVMX: allow setting the VMFUNC controls MSR
  KVM: nVMX: list VMX MSRs in KVM_GET_MSR_INDEX_LIST

 arch/x86/kvm/svm.c        |  1 +
 arch/x86/kvm/vmx/nested.c | 12 +++++++++++-
 arch/x86/kvm/vmx/vmx.c    |  2 ++
 arch/x86/kvm/x86.c        | 20 ++++++++++++++++++++
 4 files changed, 34 insertions(+), 1 deletion(-)
```
