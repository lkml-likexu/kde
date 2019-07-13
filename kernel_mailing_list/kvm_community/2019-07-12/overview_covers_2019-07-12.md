

#### [kvm-unit-tests PATCH v2 0/3] tscdeadline_latency: Some fixes of
##### From: Peter Xu <zhexu@redhat.com>
X-Google-Original-From: Peter Xu <peterx@redhat.com>

```c

The previous version only contain patch 1 but when at it I noticed
more ways to hang it... so let's fix them all up...

v2:
- use safe_halt() as suggested [Sean]
- added two more patches

Peter Xu (3):
  tscdeadline_latency: Check condition first before loop
  tscdeadline_latency: Limit size
  tscdeadline_latency: Stop timer when reach max loop

 x86/tscdeadline_latency.c | 27 +++++++++++++++++----------
 1 file changed, 17 insertions(+), 10 deletions(-)
```
#### [PATCH v7 0/3] KVM: x86: Enable user wait instructions
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

Changelog:
v7:
	Add nested support for user wait instructions (Paolo)
	Use the test on vmx->secondary_exec_control to replace
	guest_cpuid_has (Paolo)
v6:
	add check msr_info->host_initiated in get/set msr(Xiaoyao)
	restore the atomic_switch_umwait_control_msr()(Xiaoyao)

Tao Xu (3):
  KVM: x86: add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: handle vm-exit for UMWAIT and TPAUSE

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 ++-
 arch/x86/kernel/cpu/umwait.c    |  3 +-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/nested.c       |  4 ++
 arch/x86/kvm/vmx/vmx.c          | 69 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  9 +++++
 arch/x86/kvm/x86.c              |  1 +
 8 files changed, 92 insertions(+), 3 deletions(-)
```
