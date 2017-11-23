

#### [PATCH v2 0/7] This patch-set is to enable Guest CET support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

Control-flow Enforcement Technology (CET) provides protection against
return/jump-oriented programming (ROP) attacks. To make kvm Guest OS own
the capability, this patch-set is required. It enables CET related CPUID
report, xsaves/xrstors, vmx entry configuration etc. for Guest OS.

PATCH 1    : Define CET VMCS fields and bits.
PATCH 2/3  : Report CET feature support in CPUID.
PATCH 4    : Fix xsaves size calculation issue.
PATCH 5    : Pass through CET MSRs to Guest.
PATCH 6    : Set Guest CET state auto loading bit.
PATCH 7    : Enable CET xsaves bits support in XSS.

Changelog:
 v2:
 - Re-ordered patch sequence, combined one patch.
 - Added more description for CET related VMCS fields.
 - Added Host CET capability check while enabling Guest CET loading bit.
 - Added Host CET capability check while reporting Guest CPUID(EAX=7,
   EXC=0).
 - Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
 - Added Host and Guest XSS mask check while setting bits for Guest XSS.


Yang Weijiang (7):
  KVM:VMX: Define CET VMCS fields and bits
  KVM:CPUID: Define CET CPUID bits and CR4.CET master enable bit.
  KVM:CPUID: Add CPUID support for CET xsaves component query.
  KVM:CPUID: Fix xsaves area size calculation for CPUID.(EAX=0xD,ECX=1).
  KVM:VMX: Pass through host CET related MSRs to Guest.
  KVM:VMX: Load Guest CET via VMCS when CET is enabled in Guest
  KVM:X86: Enable MSR_IA32_XSS bit 11 and 12 for CET xsaves/xrstors.

 arch/x86/include/asm/kvm_host.h |  3 +-
 arch/x86/include/asm/vmx.h      |  8 ++++
 arch/x86/kvm/cpuid.c            | 67 ++++++++++++++++++++++++---------
 arch/x86/kvm/vmx.c              | 60 +++++++++++++++++++++++++++--
 arch/x86/kvm/x86.c              |  4 ++
 arch/x86/kvm/x86.h              |  4 ++
 6 files changed, 125 insertions(+), 21 deletions(-)
```
