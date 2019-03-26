

#### [PATCH v4 0/2] Switch MSR_MISC_FEATURES_ENABLES and one optimization
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c

Patch 1 switches MSR_MISC_FEATURES_ENABLE between host and guest during
vcpu_{load,put} to avoid cpuid faulting and ring3mwait of host leaking
to guest. Because cpuid faulting eanbled in host may potentially cause guest
boot failure, and kvm doesn't expose ring3mwait to guest yet. 
Both two features shouldn't be leaked to guest.

Patch 2 optimizes the switch of MSR_MISC_FEATURES_ENABLES by avoiding WRMSR
whenever possible to save cycles.

==changelog==
v3->v4:
remove the helper function, and some code refine. per Sean Christopherson's
comments.

v2->v3:
- use msr_misc_features_shadow instead of reading hardware msr, from Sean
Christopherson
- avoid WRMSR whenever possible, from Sean Christopherson.

v1->v2: 
- move the save/restore of cpuid faulting bit to
vmx_prepare_swich_to_guest/vmx_prepare_swich_to_host to avoid every
vmentry RDMSR, based on Paolo's comment.

Xiaoyao Li (2):
  kvm/vmx: Switch MSR_MISC_FEATURES_ENABLES between host and guest
  x86/vmx: optimize MSR_MISC_FEATURES_ENABLES switch

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kernel/process.c       |  1 +
 arch/x86/kvm/vmx/vmx.c          | 17 +++++++++++++++++
 arch/x86/kvm/x86.c              | 11 ++++++++---
 4 files changed, 28 insertions(+), 3 deletions(-)
```
