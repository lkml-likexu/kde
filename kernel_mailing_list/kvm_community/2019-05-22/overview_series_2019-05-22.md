#### [PATCH v5 1/8] KVM: VMX: Define CET VMCS fields and control bits
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
CET(Control-flow Enforcement Technology) is an upcoming Intel® processor
family feature that blocks return/jump-oriented programming (ROP) attacks.
It provides the following capabilities to defend
against ROP/JOP style control-flow subversion attacks:

- Shadow Stack (SHSTK):
  A second stack for the program that is used exclusively for
  control transfer operations.

- Indirect Branch Tracking (IBT):
  Free branch protection to defend against jump/call oriented
  programming.

Several new CET MSRs are defined in kernel to support CET:
MSR_IA32_{U,S}_CET - MSRs to control the CET settings for user
mode and suervisor mode respectively.

MSR_IA32_PL{0,1,2,3}_SSP - MSRs to store shadow stack pointers for
CPL-0,1,2,3 levels.

MSR_IA32_INT_SSP_TAB - MSR to store base address of shadow stack
pointer table.

Two XSAVES state components are introduced for CET:
IA32_XSS:[bit 11] - bit for save/restor user mode CET states
IA32_XSS:[bit 12] - bit for save/restor supervisor mode CET states.

6 VMCS fields are introduced for CET, {HOST,GUEST}_S_CET is to store
CET settings in supervisor mode. {HOST,GUEST}_SSP is to store shadow
stack pointers in supervisor mode. {HOST,GUEST}_INTR_SSP_TABLE is to
store base address of shadow stack pointer table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host's CET MSRs are restored
from below VMCS fields at VM-Exit:
- HOST_S_CET
- HOST_SSP
- HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest's CET MSRs are loaded
from below VMCS fields at VM-Entry:
- GUEST_S_CET
- GUEST_SSP
- GUEST_INTR_SSP_TABLE

Apart from VMCS auto-load fields, KVM calls kvm_load_guest_fpu() and
kvm_put_guest_fpu() to save/restore the guest CET MSR states at
VM exit/entry. XSAVES/XRSTORS are executed underneath these functions
if they are supported. The CET xsave area is consolidated with other
XSAVE components in thread_struct.fpu field.

When context switch happens during task switch/interrupt/exception etc.,
Kernel also relies on above functions to switch CET states properly.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
---
 arch/x86/include/asm/vmx.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH] kvm: tests: Test that APICv is effectiveFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
This test determines whether a read from the local APIC ID register in an L1 guest is significantly faster than a read of the local APIC current count register (implying that APICv is effective).

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/include/timing.h  |  53 +++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  41 +++++
 .../testing/selftests/kvm/x86_64/apicv_test.c | 145 ++++++++++++++++++
 6 files changed, 244 insertions(+), 1 deletion(-)
 create mode 100644 tools/testing/selftests/kvm/include/timing.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/apicv_test.c

```
#### [PATCH kvm-unit-tests] vmx_tests: use enter_guest if guest state is valid
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Change one remaining call site where the guest state is valid as far as
PAT is concerned; we should abort on both an early vmentry failure
as well as an invalid guest state.

Suggested-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v1] KVM: x86: PMU WhitelistTo: pbonzini@redhat.com, rkrcmar@redhat.com
##### From: Eric Hankland <ehankland@google.com>

```c
- Add a VCPU ioctl that can control which events the guest can monitor.

Signed-off-by: ehankland <ehankland@google.com>
---
Some events can provide a guest with information about other guests or the
host (e.g. L3 cache stats); providing the capability to restrict access
to a "safe" set of events would limit the potential for the PMU to be used
in any side channel attacks. This change introduces a new vcpu ioctl that
sets an event whitelist. If the guest attempts to program a counter for
any unwhitelisted event, the kernel counter won't be created, so any
RDPMC/RDMSR will show 0 instances of that event.
---
 Documentation/virtual/kvm/api.txt | 16 +++++++++++
 arch/x86/include/asm/kvm_host.h   |  1 +
 arch/x86/include/uapi/asm/kvm.h   |  7 +++++
 arch/x86/kvm/pmu.c                | 44 +++++++++++++++++++++++++++++++
 arch/x86/kvm/pmu.h                |  3 +++
 arch/x86/kvm/pmu_amd.c            | 16 +++++++++++
 arch/x86/kvm/vmx/pmu_intel.c      | 16 +++++++++++
 arch/x86/kvm/x86.c                |  7 +++++
 include/uapi/linux/kvm.h          |  4 +++
 9 files changed, 114 insertions(+)

diff --git a/Documentation/virtual/kvm/api.txt
```
