

#### [PATCH v6 0/8] Introduce support for Guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM modification is required to support Guest CET feature.
This patch serial implemented CET related CPUID/XSAVES enumeration, MSRs
and VMEntry configuration etc.so that Guest kernel can setup CET
runtime infrastructure based on them. Some MSRs and related feature
flags used in the patches reference the definitions in kernel patch.

CET kernel patches is here:
https://lkml.org/lkml/2019/6/6/1003
https://lkml.org/lkml/2019/6/6/1030
 
v5 -> v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

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
- Added Host and Guest XSS mask check while setting bits for Guest XSS.


PATCH 1    : Define CET VMCS fields and bits.
PATCH 2    : Add a helper function for CPUID(0xD, n>=1) enumeration.
PATCH 3    : Enumerate CET features/XSAVES in CPUID.
PATCH 4    : Pass through CET MSRs to Guest.
PATCH 5    : Load Guest CET states via VMCS.
PATCH 6    : Add CET bits setting in CR4 and IA32_XSS.
PATCH 7    : Load Guest FPU states for XSAVES managed MSRs.
PATCH 8    : Add user-space access interface for CET states.


Sean Christopherson (1):
  KVM: x86: Load Guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (7):
  KVM: VMX: Define CET VMCS fields and control bits
  KVM: x86: Add a helper function for CPUID(0xD,n>=1) enumeration
  KVM: x86: Implement CET CPUID enumeration for Guest
  KVM: VMX: Pass through CET related MSRs to Guest
  KVM: VMX: Load Guest CET via VMCS when CET is enabled in Guest
  KVM: x86: Add CET bits setting in CR4 and XSS
  KVM: x86: Add user-space access interface for CET MSRs

 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/include/asm/vmx.h      |   8 +++
 arch/x86/kvm/cpuid.c            | 107 +++++++++++++++++++++-----------
 arch/x86/kvm/vmx/vmx.c          |  83 +++++++++++++++++++++++--
 arch/x86/kvm/x86.c              |  29 ++++++++-
 arch/x86/kvm/x86.h              |   4 ++
 6 files changed, 193 insertions(+), 43 deletions(-)
```
#### [PATCH stable-4.19 0/2] KVM: nVMX: guest reset fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Few patches were recently marked for stable@ but commits are not
backportable as-is and require a few tweaks. Here is 4.19 stable backport.

Jan Kiszka (1):
  KVM: nVMX: Clear pending KVM_REQ_GET_VMCS12_PAGES when leaving nested

Paolo Bonzini (1):
  KVM: nVMX: do not use dangling shadow VMCS after guest reset

 arch/x86/kvm/vmx.c | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
```
#### [PATCH stable-5.1 0/3] KVM: x86: FPU and nested VMX guest reset fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Few patches were recently marked for stable@ but commits are not
backportable as-is and require a few tweaks. Here is 5.1 stable backport.

[PATCH2 of the series applies as-is, I have it here for completeness]

Jan Kiszka (1):
  KVM: nVMX: Clear pending KVM_REQ_GET_VMCS12_PAGES when leaving nested

Paolo Bonzini (2):
  KVM: nVMX: do not use dangling shadow VMCS after guest reset
  Revert "kvm: x86: Use task structs fpu field for user"

 arch/x86/include/asm/kvm_host.h |  7 ++++---
 arch/x86/kvm/vmx/nested.c       | 10 +++++++++-
 arch/x86/kvm/x86.c              |  4 ++--
 3 files changed, 15 insertions(+), 6 deletions(-)
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
```
#### [PATCH stable-5.2 0/3] KVM: x86: FPU and nested VMX guest reset fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Few patches were recently marked for stable@ but commits are not
backportable as-is and require a few tweaks. Here is 5.2 stable backport.

[PATCHes 2/3 of the series apply as-is, I have them here for completeness]

Jan Kiszka (1):
  KVM: nVMX: Clear pending KVM_REQ_GET_VMCS12_PAGES when leaving nested

Paolo Bonzini (2):
  KVM: nVMX: do not use dangling shadow VMCS after guest reset
  Revert "kvm: x86: Use task structs fpu field for user"

 arch/x86/include/asm/kvm_host.h |  7 ++++---
 arch/x86/kvm/vmx/nested.c       | 10 +++++++++-
 arch/x86/kvm/x86.c              |  4 ++--
 3 files changed, 15 insertions(+), 6 deletions(-)
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
```
#### [ v2 0/1] kvm-unit-tests: s390x: add check for mandatory
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

Let us start with all documented dependencies from chapter 4 of the POP.
we can add more tests later on. 

Christian Borntraeger (1):
  kvm-unit-tests: s390: add cpu model checks

 s390x/Makefile      |  1 +
 s390x/cpumodel.c    | 58 +++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |  3 +++
 3 files changed, 62 insertions(+)
 create mode 100644 s390x/cpumodel.c
```
#### [PATCH v3 00/10] KVM: arm/arm64: vgic: ITS translation cache
##### From: Marc Zyngier <maz@kernel.org>
From: Marc Zyngier <marc.zyngier@arm.com>

```c

From: Marc Zyngier <marc.zyngier@arm.com>

It recently became apparent[1] that our LPI injection path is not as
efficient as it could be when injecting interrupts coming from a VFIO
assigned device.

Although the proposed patch wasn't 100% correct, it outlined at least
two issues:

(1) Injecting an LPI from VFIO always results in a context switch to a
    worker thread: no good

(2) We have no way of amortising the cost of translating a DID+EID pair
    to an LPI number

The reason for (1) is that we may sleep when translating an LPI, so we
do need a context process. A way to fix that is to implement a small
LPI translation cache that could be looked up from an atomic
context. It would also solve (2).

This is what this small series proposes. It implements a very basic
LRU cache of pre-translated LPIs, which gets used to implement
kvm_arch_set_irq_inatomic. The size of the cache is currently
hard-coded at 16 times the number of vcpus, a number I have picked
under the influence of Ali Saidi. If that's not enough for you, blame
me, though.

Does it work? well, it doesn't crash, and is thus perfect. More
seriously, I don't really have a way to benchmark it directly, so my
observations are only indirect:

On a TX2 system, I run a 4 vcpu VM with an Ethernet interface passed
to it directly. From the host, I inject interrupts using debugfs. In
parallel, I look at the number of context switch, and the number of
interrupts on the host. Without this series, I get the same number for
both IRQ and CS (about half a million of each per second is pretty
easy to reach). With this series, the number of context switches drops
to something pretty small (in the low 2k), while the number of
interrupts stays the same.

Yes, this is a pretty rubbish benchmark, what did you expect? ;-)

Andre did run some benchmarks of his own, with some rather positive
results[2]. So I'm putting this out for people with real workloads to
try out and report what they see.

[1] https://lore.kernel.org/lkml/1552833373-19828-1-git-send-email-yuzenghui@huawei.com/
[2] https://www.spinics.net/lists/arm-kernel/msg742655.html

* From v2:

  - Added invalidation on turning the ITS off
  - Added invalidation on MAPC with V=0
  - Added Rb's from Eric

* From v1:

  - Fixed race on allocation, where the same LPI could be cached multiple times
  - Now invalidate the cache on vgic teardown, avoiding memory leaks
  - Change patch split slightly, general reshuffling
  - Small cleanups here and there
  - Rebased on 5.2-rc4

Marc Zyngier (10):
  KVM: arm/arm64: vgic: Add LPI translation cache definition
  KVM: arm/arm64: vgic: Add __vgic_put_lpi_locked primitive
  KVM: arm/arm64: vgic-its: Add MSI-LPI translation cache invalidation
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    specific commands
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    disabling LPIs
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on ITS
    disable
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on vgic
    teardown
  KVM: arm/arm64: vgic-its: Cache successful MSI->LPI translation
  KVM: arm/arm64: vgic-its: Check the LPI translation cache on MSI
    injection
  KVM: arm/arm64: vgic-irqfd: Implement kvm_arch_set_irq_inatomic

 include/kvm/arm_vgic.h           |   3 +
 virt/kvm/arm/vgic/vgic-init.c    |   5 +
 virt/kvm/arm/vgic/vgic-irqfd.c   |  36 +++++-
 virt/kvm/arm/vgic/vgic-its.c     | 207 +++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic-mmio-v3.c |   4 +-
 virt/kvm/arm/vgic/vgic.c         |  26 ++--
 virt/kvm/arm/vgic/vgic.h         |   5 +
 7 files changed, 270 insertions(+), 16 deletions(-)
```
