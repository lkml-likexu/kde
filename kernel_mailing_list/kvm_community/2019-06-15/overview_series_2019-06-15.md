#### [PATCH] KVM: improve definition of KVM_GET/SET_NESTED_STATE structs
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Liran sent me a patch with a large overhaul of the
KVM_GET/SET_NESTED_STATE structs.  However, I am wary of changing the
userspace ABI in backwards-incompatible ways, so here is the bare minimum
that is needed to achieve the same functionality.

Namely, the format of VMX nested state is detailed in a struct, and is
accessible through struct kvm_vmx_nested_state.  Unfortunately, to avoid
changing the size of the structs it has to be accessed as "vmx.data[0]"
rather than just "vmx.data".

Also, the values of the "format" field are defined as macros, which is
easy and not controversial.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/uapi/asm/kvm.h | 11 +++++++++++
 arch/x86/kvm/vmx/nested.c       |  3 +++
 2 files changed, 14 insertions(+)

```
