#### [PATCH 4/6] KVM: Define Hygon SEV commands
##### From: Hao Feng <fenghao@hygon.cn>

```c
1. KVM_SEV_GM_GET_DIGEST
------------------------
The command is used to get the key digest from SEV firmware, guest
owner will check the key digest to see if the key negotiation is
successful or not.

2. KVM_SEV_GM_VERIFY_DIGEST
---------------------------
The command is used to send guest owner's key digest to SEV firmware,
firmware will check the key digest to see if the key negotiation is
successful or not.

Signed-off-by: Hao Feng <fenghao@hygon.cn>
---
 include/uapi/linux/kvm.h | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [PATCH v5 1/3] arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Recent commits added the explicit notion of "Not affected" to the state
of the Spectre v2 (aka. BP_HARDENING) workaround, where we just had
"needed" and "unknown" before.

Export this knowledge to the rest of the kernel and enhance the existing
kvm_arm_harden_branch_predictor() to report this new state as well.
Export this new state to guests when they use KVM's firmware interface
emulation.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arch/arm/include/asm/kvm_host.h     | 12 +++++++++---
 arch/arm64/include/asm/cpufeature.h |  6 ++++++
 arch/arm64/include/asm/kvm_host.h   | 16 ++++++++++++++--
 arch/arm64/kernel/cpu_errata.c      | 23 ++++++++++++++++++-----
 virt/kvm/arm/psci.c                 | 10 +++++++++-
 5 files changed, 56 insertions(+), 11 deletions(-)

```
#### [PATCH] KVM: nVMX: allow tests to use bad virtual-APIC page address
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
As mentioned in the comment, there are some special cases where we can simply
clear the TPR shadow bit from the CPU-based execution controls in the vmcs02.
Handle them so that we can remove some XFAILs from vmx.flat.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 25 ++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    |  2 +-
 arch/x86/kvm/vmx/vmx.h    |  2 ++
 3 files changed, 19 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: nVMX: always use early vmcs check when EPT is disabled
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The remaining failures of vmx.flat when EPT is disabled are caused by
incorrectly reflecting VMfails to the L1 hypervisor.  What happens is
that nested_vmx_restore_host_state corrupts the guest CR3, reloading it
with the host's shadow CR3 instead, because it blindly loads GUEST_CR3
from the vmcs01.

For simplicity let's just always use hardware VMCS checks when EPT is
disabled.  This way, nested_vmx_restore_host_state is not reached at
all (or at least shouldn't be reached).
Reported-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reported-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/uapi/asm/vmx.h |  1 +
 arch/x86/kvm/vmx/nested.c       | 22 ++++++++++++++++++++--
 2 files changed, 21 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests v2 PATCH] s390x: Add a test for the diagnose 0x308 hypercall
##### From: Thomas Huth <thuth@redhat.com>

```c
The original idea for this test is to have an easy way to check for a
problem that has been fixed in QEMU recently: QEMU simply aborted if this
diagnose call was called with an unsupported subcode (e.g. 2). The problem
has been fixed in QEMU commit 37dbd1f4d4805edcd18d94eb202bb3461b3cd52d
("Return specification exception for unimplemented diag 308 subcodes"),
and this test now should make sure that we do not regress here again.
While we're at it, also check whether LOAD NORMAL via subcode 1 works
correctly, whether the diagnose call is blocked correctly in problem state
and whether subcodes 5 and 6 are generating specification exceptions for
illegal parameters as expected.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v2: Use "epsw" in test_subcode1() to get the right upper bits of the PSW

 s390x/Makefile      |   1 +
 s390x/diag308.c     | 130 ++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |   3 +
 3 files changed, 134 insertions(+)
 create mode 100644 s390x/diag308.c

```
#### [kvm-unit-tests PATCH v2] x86: Remove INIT deassert
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

Currently, the INIT deassert is marked as an edge event instead of a
level, which is wrong. The deassert is actually not needed, as the
arbitration ID should have already been set after boot, and is not
affected by further INIT IPIs.

Remove the INIT deassert for these reasons.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/cstart.S   | 1 -
 x86/cstart64.S | 1 -
 2 files changed, 2 deletions(-)

```
#### [PATCH kvm-unit-tests] vmx: do not XFAIL for virtual-APIC address beyond RAM
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
We will allow this behavior for KVM in some specific cases
(CR8 load/store exits enabled, virtualize APIC accesses
disabled).  Ensure these specific values of the controls
are there in the VMCS, and remove the XFAIL.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: apic: Preserve APIC base and BSP bits during x2APIC tests
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
...and reset to xAPIC mode unless x2APIC was already enabled.  Make the
"APIC disabled to APIC enabled" a reported subtest so that it's
(slightly) more obviously that the vCPU is transitioning back to legacy
xAPIC mode and that the APIC was disabled via a previous subtest, i.e.
won't fault due to an illegal transition.

Note, reset_apic() is overkill since the vCPU is already in legacy xAPIC
mode, i.e. the test really just needs "apic_ops = &xapic_ops;".  But two
MSR accesses are negligible in the grand scheme and using reset_apic() is
less reliant on the exact flow of the test.

Reported-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/apic.c | 30 +++++++++++++++++++++---------
 1 file changed, 21 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Fix INIT during boot
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

INIT is a level event and the trigger mode should be marked as such. In
addition, the SDM says that INIT deassertion should specify the "all
including-self" shorthand.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/cstart64.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Prevent APIC base address from changing in test_enable_x2apic()
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

test_enable_x2apic() unintentionally changes the APIC base address to
zero and resets the BSP indication. This actually causes the local APIC
to overlap the IDT area, which is wrong. Prevent it from happening by
keeping the APIC base address and BSP-bit as it was before.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/apic.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: VMX: Nop emulation of MSR_IA32_POWER_CTL
##### From: Liran Alon <liran.alon@oracle.com>

```c
Since commits 668fffa3f838 ("kvm: better MWAIT emulation for guests”)
and 4d5422cea3b6 ("KVM: X86: Provide a capability to disable MWAIT intercepts”),
KVM was modified to allow an admin to configure certain guests to execute
MONITOR/MWAIT inside guest without being intercepted by host.

This is useful in case admin wishes to allocate a dedicated logical
processor for each vCPU thread. Thus, making it safe for guest to
completely control the power-state of the logical processor.

The ability to use this new KVM capability was introduced to QEMU by
commits 6f131f13e68d ("kvm: support -overcommit cpu-pm=on|off”) and
2266d4431132 ("i386/cpu: make -cpu host support monitor/mwait”).

However, exposing MONITOR/MWAIT to a Linux guest may cause it's intel_idle
kernel module to execute c1e_promotion_disable() which will attempt to
RDMSR/WRMSR from/to MSR_IA32_POWER_CTL to manipulate the "C1E Enable"
bit. This behaviour was introduced by commit
32e9518005c8 ("intel_idle: export both C1 and C1E”).

Becuase KVM doesn't emulate this MSR, running KVM with ignore_msrs=0
will cause the above guest behaviour to raise a #GP which will cause
guest to kernel panic.

Therefore, add support for nop emulation of MSR_IA32_POWER_CTL to
avoid #GP in guest in this scenario.

Future commits can optimise emulation further by reflecting guest
MSR changes to host MSR to provide guest with the ability to
fine-tune the dedicated logical processor power-state.

Reviewed-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++++++
 arch/x86/kvm/vmx/vmx.h | 2 ++
 arch/x86/kvm/x86.c     | 1 +
 3 files changed, 9 insertions(+)

```
#### [PATCH] KVM: vmx: print more APICv fields in dump_vmcs
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The SVI, RVI, virtual-APIC page address and APIC-access page address fields
were left out of dump_vmcs.  Add them.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH] x86: Fix allowed IA32_VMX_VMCS_ENUM values
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to the SDM, IA32_VMX_VMCS_ENUM indicates to software the
highest index value used in the encoding of any field supported by the
processor: Bits 9:1 contain the highest index value used for any VMCS
encoding.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86: Wait for self IPI
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

There is no architectural requirement that self-IPI would be received on
the next instruction after it is generated. Make the test more robust by
not requiring it, and instead wait for some time or until it is
received.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/apic.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
