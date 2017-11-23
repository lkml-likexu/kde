

#### [PATCH v2 0/2] KVM: x86: hyperv: PV IPI follow-up
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v1:
- Use KVM_HV_MAX_SPARSE_VCPU_SET_BITS = DIV_ROUND_UP(KVM_MAX_VCPUS, 64)
  instead of (KVM_MAX_VCPUS / 64) [Paolo Bonzini]
- Add Roman's Reviewed-by: tags to both patches, hope they stand with the
  above mentioned change in PATCH2.

This is a follow-up series to the previously merged "KVM: x86: hyperv:
PV IPI support for Windows guests". A couple of issues and suggestions
on how to make things better were expressed by Roman during v6 review.

Vitaly Kuznetsov (2):
  KVM: x86: hyperv: fix 'tlb_lush' typo
  KVM: x86: hyperv: optimize sparse VP set processing

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/hyperv.c           | 165 +++++++++++++-------------------
 2 files changed, 67 insertions(+), 100 deletions(-)
```
