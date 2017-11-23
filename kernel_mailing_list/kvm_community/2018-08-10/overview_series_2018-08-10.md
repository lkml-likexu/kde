#### [PATCH 1/3] KVM: x86: Turbo bits in MSR_PLATFORM_INFOFrom: Drew Schmitt <dasch@google.com>
##### From: Drew Schmitt <dasch@google.com>

```c
Allow userspace to set turbo bits in MSR_PLATFORM_INFO. Previously, only
the CPUID faulting bit was settable. But now any bit in
MSR_PLATFORM_INFO would be settable.

Signed-off-by: Drew Schmitt <dasch@google.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v2 1/4] KVM: arm64: Remove non-existent AArch32 ICC_SGI1R encoding
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
ICC_SGI1R is a 64bit system register, even on AArch32. It is thus
pointless to have such an encoding in the 32bit cp15 array. Let's
drop it.

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/sys_regs.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [kvm-unit-test] nVMX x86: "external-interrupt exiting" must be set if "virtual-interrupt delivery" is set
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C,
the following check needs to be enforced on vmentry of L2 guests:

    If the "virtual-interrupt delivery" VM-execution control is 1, the
    "external-interrupt exiting" VM-execution control must be 1.

This unit-test validates the above vmentry check.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 46 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 46 insertions(+)

```
