

#### [PATCH v3 0/3] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).
TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The dependency KVM patch link:
https://lkml.org/lkml/2019/5/24/138

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 +++-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h |  6 ++++
 arch/x86/kvm/vmx/vmx.c          | 56 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/power/umwait.c         |  3 +-
 7 files changed, 74 insertions(+), 3 deletions(-)
```
#### [PATCH RESEND v3 0/3] KVM: x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. If the instruction causes a delay, the amount
of time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay (the time to delay
relative to the VM’s timestamp counter). 

The release document ref below link:
Intel 64 and IA-32 Architectures Software Developer's Manual,
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf
This patch has a dependency on https://lkml.org/lkml/2019/6/7/1206

Changelog:
v3:
	Simplify the patches, expose user wait instructions when the
	guest has CPUID (Paolo)
	Use mwait_control_cached to avoid frequently rdmsr of
	IA32_UMWAIT_CONTROL (Paolo and Xiaoyao)
	Handle vm-exit for UMWAIT and TPAUSE as "never happen" (Paolo)
v2:
	Separated from the series https://lkml.org/lkml/2018/7/10/160
	Add provide a capability to enable UMONITOR, UMWAIT and TPAUSE 
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 +++-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h |  6 ++++
 arch/x86/kvm/vmx/vmx.c          | 56 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/power/umwait.c         |  3 +-
 7 files changed, 74 insertions(+), 3 deletions(-)
```
#### [PATCH v3 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The dependency KVM patch link:
https://lkml.org/lkml/2019/6/16/50

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  3 ++-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 17 +++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 42 insertions(+), 1 deletion(-)
```
