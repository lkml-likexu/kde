

#### [PATCH v5 0/8] Introduce support for Guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: shadow stack (SHSTK) and indirect branch tracking (IBT).

KVM modification is required to support Guest CET feature.
This patch serial implemented CET related CPUID/XSAVES enumeration, MSRs 
and VMEntry configuration etc.so that Guest kernel can setup CET
runtime infrastructure based on them. Some MSRs and related feature
flags used in the patches reference the definitions in kernel patch.

CET kernel patch is here:
https://lkml.org/lkml/2018/11/20/225.

PATCH 1    : Define CET VMCS fields and bits.
PATCH 2/3  : Enumerate CET features/XSAVES in CPUID.
PATCH 4    : Fix xsaves size calculation issue.
PATCH 5    : Pass through CET MSRs to Guest.
PATCH 6    : Set Guest auto loading bit for CET.
PATCH 7    : Load Guest FPU states for XSAVES managed MSRs.
PATCH 8    : Add user-space access interface for CET states.


 v4 -> v5:
  - Rebase patch to kernel v5.1.
  - Wrap CPUID(0xD, n>=1) code to a helper function.
  - Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
  - Add Co-developed-by expression in patch description.
  - Refine patch description.

 v3 -> v4:
 - Add Sean's patch for loading Guest fpu state before access XSAVES
   managed CET MSRs.
 - Melt down CET bits setting into CPUID configuration patch.
 - Add VMX interface to query Host XSS.
 - Check Host and Guest XSS support bits before set Guest XSS.
 - Make Guest SHSTK and IBT feature enabling independent.
 - Do not report CET support to Guest when Host CET feature is Disabled.

 v2 -> v3:
 - Modified patches to make Guest CET independent to Host enabling.
 - Added patch 8 to add user space access for Guest CET MSR access.
 - Modified code comments and patch description to reflect changes.

 v1 -> v2:
 - Re-ordered patch sequence, combined one patch.
 - Added more description for CET related VMCS fields.
 - Added Host CET capability check while enabling Guest CET loading bit.
 - Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
 - Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
 - Added Host and Guest XSS mask check while
   setting bits for Guest XSS.

Sean Christopherson (1):
  KVM: x86: Load Guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (7):
  KVM: VMX: Define CET VMCS fields and control bits
  KVM: x86: Implement CET CPUID support for Guest
  KVM: x86: Fix XSAVE size calculation issue
  KVM: VMX: Pass through CET related MSRs to Guest
  KVM: VMX: Load Guest CET via VMCS when CET is enabled in Guest
  KVM: x86: Allow Guest to set supported bits in XSS
  KVM: x86: Add user-space access interface for CET MSRs

 arch/x86/include/asm/kvm_host.h  |   5 +-
 arch/x86/include/asm/msr-index.h |   2 +
 arch/x86/include/asm/vmx.h       |   8 +++
 arch/x86/kvm/cpuid.c             | 109 +++++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.c           |  83 +++++++++++++++++++++--
 arch/x86/kvm/x86.c               |  29 +++++++-
 arch/x86/kvm/x86.h               |   4 ++
 7 files changed, 197 insertions(+), 43 deletions(-)
```
