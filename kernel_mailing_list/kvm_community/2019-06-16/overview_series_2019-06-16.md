#### [PATCH RESEND v3 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 arch/x86/include/asm/vmx.h      | 1 +
 arch/x86/kvm/cpuid.c            | 2 +-
 arch/x86/kvm/vmx/capabilities.h | 6 ++++++
 arch/x86/kvm/vmx/vmx.c          | 4 ++++
 4 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Modify struct kvm_nested_state to have explicit fields for data
##### From: Liran Alon <liran.alon@oracle.com>

```c
Improve the KVM_{GET,SET}_NESTED_STATE structs by detailing the format
of VMX nested state data in a struct.

In order to avoid changing the ioctl values of
KVM_{GET,SET}_NESTED_STATE, there is a need to preserve
sizeof(struct kvm_nested_state). This is done by defining the data
struct as "data.vmx[0]". It was the most elegant way I found to
preserve struct size while still keeping struct readable and easy to
maintain. It does have a misfortunate side-effect that now it has to be
accessed as "data.vmx[0]" rather than just "data.vmx".

Because we are already modifying these structs, I also modified the
following:
* Define the "format" field values as macros.
* Rename vmcs_pa to vmcs12_pa for better readability.
* Add stub structs for AMD SVM.

Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 Documentation/virtual/kvm/api.txt | 44 +++++++++++------
 arch/x86/include/uapi/asm/kvm.h   | 41 +++++++++++-----
 arch/x86/kvm/vmx/nested.c         | 79 +++++++++++++++++--------------
 3 files changed, 103 insertions(+), 61 deletions(-)

```
#### [PATCH v3 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 arch/x86/include/asm/vmx.h      | 1 +
 arch/x86/kvm/cpuid.c            | 2 +-
 arch/x86/kvm/vmx/capabilities.h | 6 ++++++
 arch/x86/kvm/vmx/vmx.c          | 4 ++++
 4 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH v3 2/3] KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMWAIT and TPAUSE instructions use IA32_UMWAIT_CONTROL at MSR index E1H
to determines the maximum time in TSC-quanta that the processor can reside
in either C0.1 or C0.2.

This patch emulates MSR IA32_UMWAIT_CONTROL in guest and differentiate
IA32_UMWAIT_CONTROL between host and guest. The variable
mwait_control_cached in arch/x86/power/umwait.c caches the MSR value, so
this patch uses it to avoid frequently rdmsr of IA32_UMWAIT_CONTROL.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 arch/x86/kvm/vmx/vmx.c  | 36 ++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h  |  3 +++
 arch/x86/power/umwait.c |  3 ++-
 3 files changed, 41 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

changes in v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
