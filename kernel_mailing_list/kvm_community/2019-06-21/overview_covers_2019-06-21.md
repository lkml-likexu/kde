

#### [PATCH v6 0/3] KVM: x86: Enable user wait instructions
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
This patch has a dependency on https://lkml.org/lkml/2019/6/19/972

Changelog:
v6:
	add check msr_info->host_initiated in get/set msr(Xiaoyao)
	restore the atomic_switch_umwait_control_msr()(Xiaoyao)
v5:
	remove vmx_waitpkg_supported() to fix guest can rdmsr or wrmsr
	when the feature is off (Xiaoyao)
	rebase the patch because the kernel dependcy patch updated to
	v5: https://lkml.org/lkml/2019/6/19/972
v4:
	Set msr of IA32_UMWAIT_CONTROL can be 0 and add the check of
	reserved bit 1 (Radim and Xiaoyao)
	Use umwait_control_cached directly and add the IA32_UMWAIT_CONTROL
	in msrs_to_save[] to support migration (Xiaoyao)
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
 arch/x86/kernel/cpu/umwait.c    |  3 +-
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/vmx.c          | 53 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  3 ++
 arch/x86/kvm/x86.c              |  1 +
 7 files changed, 66 insertions(+), 3 deletions(-)
```
#### [PATCH RESEND v3 0/2] x86: Enable user wait instructions
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
https://lkml.org/lkml/2019/6/21/23

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
	Resend to update the dependcy KVM link:
	https://lkml.org/lkml/2019/6/21/23
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
#### [PATCH 00/59] KVM: arm64: ARMv8.3 Nested Virtualization support
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

I've taken over the maintenance of this series originally written by
Jintack and Christoffer. Since then, the series has been substantially
reworked, new features (and most probably bugs) have been added, and
the whole thing rebased multiple times. If anything breaks, please
blame me, and nobody else.

As you can tell, this is quite big. It is also remarkably incomplete
(we're missing many critical bits for fully emulate EL2), but the idea
is to start merging things early in order to reduce the maintenance
headache. What we want to achieve is that with NV disabled, there is
no performance overhead and no regression. The only thing I intend to
merge ASAP is the first patch in the series, because it should have
zero effect and is a reasonable cleanup.

The series is roughly divided in 4 parts: exception handling, memory
virtualization, interrupts and timers. There are of course some
dependencies, but you'll hopefully get the gist of it.

For the most courageous of you, I've put out a branch[1] containing this
and a bit more. Of course, you'll need some userspace. Andre maintains
a hacked version of kvmtool[1] that takes a --nested option, allowing
the guest to be started at EL2. You can run the whole stack in the
Foundation model. Don't be in a hurry ;-).

[1] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-wip-5.2-rc5
[2] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5

Andre Przywara (4):
  KVM: arm64: nv: Handle virtual EL2 registers in
    vcpu_read/write_sys_reg()
  KVM: arm64: nv: Save/Restore vEL2 sysregs
  KVM: arm64: nv: Handle traps for timer _EL02 and _EL2 sysregs
    accessors
  KVM: arm64: nv: vgic: Allow userland to set VGIC maintenance IRQ

Christoffer Dall (16):
  KVM: arm64: nv: Introduce nested virtualization VCPU feature
  KVM: arm64: nv: Reset VCPU to EL2 registers if VCPU nested virt is set
  KVM: arm64: nv: Allow userspace to set PSR_MODE_EL2x
  KVM: arm64: nv: Add nested virt VCPU primitives for vEL2 VCPU state
  KVM: arm64: nv: Handle trapped ERET from virtual EL2
  KVM: arm64: nv: Emulate PSTATE.M for a guest hypervisor
  KVM: arm64: nv: Trap EL1 VM register accesses in virtual EL2
  KVM: arm64: nv: Only toggle cache for virtual EL2 when SCTLR_EL2
    changes
  KVM: arm/arm64: nv: Support multiple nested stage 2 mmu structures
  KVM: arm64: nv: Implement nested Stage-2 page table walk logic
  KVM: arm64: nv: Handle shadow stage 2 page faults
  KVM: arm64: nv: Unmap/flush shadow stage 2 page tables
  KVM: arm64: nv: arch_timer: Support hyp timer emulation
  KVM: arm64: nv: vgic-v3: Take cpu_if pointer directly instead of vcpu
  KVM: arm64: nv: vgic: Emulate the HW bit in software
  KVM: arm64: nv: Add nested GICv3 tracepoints

Dave Martin (1):
  KVM: arm64: Migrate _elx sysreg accessors to msr_s/mrs_s

Jintack Lim (21):
  arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
  KVM: arm64: nv: Add EL2 system registers to vcpu context
  KVM: arm64: nv: Support virtual EL2 exceptions
  KVM: arm64: nv: Inject HVC exceptions to the virtual EL2
  KVM: arm64: nv: Trap SPSR_EL1, ELR_EL1 and VBAR_EL1 from virtual EL2
  KVM: arm64: nv: Trap CPACR_EL1 access in virtual EL2
  KVM: arm64: nv: Set a handler for the system instruction traps
  KVM: arm64: nv: Handle PSCI call via smc from the guest
  KVM: arm64: nv: Respect virtual HCR_EL2.TWX setting
  KVM: arm64: nv: Respect virtual CPTR_EL2.TFP setting
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV bit setting
  KVM: arm64: nv: Respect virtual HCR_EL2.TVM and TRVM settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV1 bit setting
  KVM: arm64: nv: Emulate EL12 register accesses from the virtual EL2
  KVM: arm64: nv: Configure HCR_EL2 for nested virtualization
  KVM: arm64: nv: Pretend we only support larger-than-host page sizes
  KVM: arm64: nv: Introduce sys_reg_desc.forward_trap
  KVM: arm64: nv: Rework the system instruction emulation framework
  KVM: arm64: nv: Trap and emulate AT instructions from virtual EL2
  KVM: arm64: nv: Trap and emulate TLBI instructions from virtual EL2
  KVM: arm64: nv: Nested GICv3 Support

Marc Zyngier (17):
  KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
  KVM: arm64: nv: Reset VMPIDR_EL2 and VPIDR_EL2 to sane values
  KVM: arm64: nv: Handle SPSR_EL2 specially
  KVM: arm64: nv: Refactor vcpu_{read,write}_sys_reg
  KVM: arm64: nv: Don't expose SVE to nested guests
  KVM: arm64: nv: Hide RAS from nested guests
  KVM: arm/arm64: nv: Factor out stage 2 page table data from struct kvm
  KVM: arm64: nv: Move last_vcpu_ran to be per s2 mmu
  KVM: arm64: nv: Don't always start an S2 MMU search from the beginning
  KVM: arm64: nv: Propagate CNTVOFF_EL2 to the virtual EL1 timer
  KVM: arm64: nv: Load timer before the GIC
  KVM: arm64: nv: Implement maintenance interrupt forwarding
  arm64: KVM: nv: Add handling of EL2-specific timer registers
  arm64: KVM: nv: Honor SCTLR_EL2.SPAN on entering vEL2
  arm64: KVM: nv: Handle SCTLR_EL2 RES0/RES1 bits
  arm64: KVM: nv: Restrict S2 RD/WR permissions to match the guest's
  arm64: KVM: nv: Allow userspace to request KVM_ARM_VCPU_NESTED_VIRT

 .../admin-guide/kernel-parameters.txt         |    4 +
 .../virtual/kvm/devices/arm-vgic-v3.txt       |    9 +
 arch/arm/include/asm/kvm_asm.h                |    5 +-
 arch/arm/include/asm/kvm_emulate.h            |    3 +
 arch/arm/include/asm/kvm_host.h               |   31 +-
 arch/arm/include/asm/kvm_hyp.h                |   25 +-
 arch/arm/include/asm/kvm_mmu.h                |   83 +-
 arch/arm/include/asm/kvm_nested.h             |    9 +
 arch/arm/include/uapi/asm/kvm.h               |    1 +
 arch/arm/kvm/hyp/switch.c                     |   11 +-
 arch/arm/kvm/hyp/tlb.c                        |   13 +-
 arch/arm64/include/asm/cpucaps.h              |    3 +-
 arch/arm64/include/asm/esr.h                  |    4 +-
 arch/arm64/include/asm/kvm_arm.h              |   28 +-
 arch/arm64/include/asm/kvm_asm.h              |    9 +-
 arch/arm64/include/asm/kvm_coproc.h           |    2 +-
 arch/arm64/include/asm/kvm_emulate.h          |  157 +-
 arch/arm64/include/asm/kvm_host.h             |  105 +-
 arch/arm64/include/asm/kvm_hyp.h              |   82 +-
 arch/arm64/include/asm/kvm_mmu.h              |   62 +-
 arch/arm64/include/asm/kvm_nested.h           |   68 +
 arch/arm64/include/asm/sysreg.h               |  143 +-
 arch/arm64/include/uapi/asm/kvm.h             |    2 +
 arch/arm64/kernel/cpufeature.c                |   26 +
 arch/arm64/kvm/Makefile                       |    4 +
 arch/arm64/kvm/emulate-nested.c               |  223 +++
 arch/arm64/kvm/guest.c                        |    6 +
 arch/arm64/kvm/handle_exit.c                  |   76 +-
 arch/arm64/kvm/hyp/Makefile                   |    1 +
 arch/arm64/kvm/hyp/at.c                       |  217 +++
 arch/arm64/kvm/hyp/switch.c                   |   86 +-
 arch/arm64/kvm/hyp/sysreg-sr.c                |  267 ++-
 arch/arm64/kvm/hyp/tlb.c                      |  129 +-
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c      |    2 +-
 arch/arm64/kvm/inject_fault.c                 |   12 -
 arch/arm64/kvm/nested.c                       |  551 +++++++
 arch/arm64/kvm/regmap.c                       |    4 +-
 arch/arm64/kvm/reset.c                        |    7 +
 arch/arm64/kvm/sys_regs.c                     | 1460 +++++++++++++++--
 arch/arm64/kvm/sys_regs.h                     |    6 +
 arch/arm64/kvm/trace.h                        |   58 +-
 include/kvm/arm_arch_timer.h                  |    6 +
 include/kvm/arm_vgic.h                        |   28 +-
 virt/kvm/arm/arch_timer.c                     |  158 +-
 virt/kvm/arm/arm.c                            |   62 +-
 virt/kvm/arm/hyp/vgic-v3-sr.c                 |   35 +-
 virt/kvm/arm/mmio.c                           |   12 +-
 virt/kvm/arm/mmu.c                            |  445 +++--
 virt/kvm/arm/trace.h                          |    6 +-
 virt/kvm/arm/vgic/vgic-init.c                 |   30 +
 virt/kvm/arm/vgic/vgic-kvm-device.c           |   22 +
 virt/kvm/arm/vgic/vgic-nested-trace.h         |  137 ++
 virt/kvm/arm/vgic/vgic-v2.c                   |   10 +-
 virt/kvm/arm/vgic/vgic-v3-nested.c            |  236 +++
 virt/kvm/arm/vgic/vgic-v3.c                   |   40 +-
 virt/kvm/arm/vgic/vgic.c                      |   74 +-
 56 files changed, 4683 insertions(+), 612 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/kvm/emulate-nested.c
 create mode 100644 arch/arm64/kvm/hyp/at.c
 create mode 100644 arch/arm64/kvm/nested.c
 create mode 100644 virt/kvm/arm/vgic/vgic-nested-trace.h
 create mode 100644 virt/kvm/arm/vgic/vgic-v3-nested.c
```
#### [PATCH v5 0/4] KVM: LAPIC: Implement Exitless Timer
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Dedicated instances are currently disturbed by unnecessary jitter due 
to the emulated lapic timers fire on the same pCPUs which vCPUs resident.
There is no hardware virtual timer on Intel for guest like ARM. Both 
programming timer in guest and the emulated timer fires incur vmexits.
This patchset tries to avoid vmexit which is incurred by the emulated 
timer fires in dedicated instance scenario. 

When nohz_full is enabled in dedicated instances scenario, the unpinned 
timer will be moved to the nearest busy housekeepers after commit
9642d18eee2cd (nohz: Affine unpinned timers to housekeepers) and commit 
444969223c8 ("sched/nohz: Fix affine unpinned timers mess"). However, 
KVM always makes lapic timer pinned to the pCPU which vCPU residents, the 
reason is explained by commit 61abdbe0 (kvm: x86: make lapic hrtimer 
pinned). Actually, these emulated timers can be offload to the housekeeping 
cpus since APICv is really common in recent years. The guest timer interrupt 
is injected by posted-interrupt which is delivered by housekeeping cpu 
once the emulated timer fires. 

The host admin should fine tuned, e.g. dedicated instances scenario w/ 
nohz_full cover the pCPUs which vCPUs resident, several pCPUs surplus 
for busy housekeeping, disable mwait/hlt/pause vmexits to keep in non-root  
mode, ~3% redis performance benefit can be observed on Skylake server.

w/o patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time   Avg time

EXTERNAL_INTERRUPT    42916    49.43%   39.30%   0.47us   106.09us   0.71us ( +-   1.09% )

w/ patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time         Avg time

EXTERNAL_INTERRUPT    6871     9.29%     2.96%   0.44us    57.88us   0.72us ( +-   4.02% )

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>

v4 -> v5:
 * update patch description in patch 1/4
 * feed latest apic->lapic_timer.expired_tscdeadline to kvm_wait_lapic_expire()
 * squash advance timer handling to patch 2/4

v3 -> v4:
 * drop the HRTIMER_MODE_ABS_PINNED, add kick after set pending timer
 * don't posted inject already-expired timer

v2 -> v3:
 * disarming the vmx preemption timer when posted_interrupt_inject_timer_enabled()
 * check kvm_hlt_in_guest instead

v1 -> v2:
 * check vcpu_halt_in_guest
 * move module parameter from kvm-intel to kvm
 * add housekeeping_enabled
 * rename apic_timer_expired_pi to kvm_apic_inject_pending_timer_irqs


Wanpeng Li (4):
  KVM: LAPIC: Make lapic timer unpinned
  KVM: LAPIC: Inject timer interrupt via posted interrupt
  KVM: LAPIC: Ignore timer migration when lapic timer is injected by pi
  KVM: LAPIC: Don't inject already-expired timer via posted interrupt

 arch/x86/kvm/lapic.c            | 68 +++++++++++++++++++++++++++--------------
 arch/x86/kvm/lapic.h            |  3 +-
 arch/x86/kvm/svm.c              |  2 +-
 arch/x86/kvm/vmx/vmx.c          |  5 +--
 arch/x86/kvm/x86.c              | 11 ++++---
 arch/x86/kvm/x86.h              |  2 ++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 ++++
 8 files changed, 67 insertions(+), 32 deletions(-)
```
#### [PATCH v14 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series is ready to be merged via nvdimm tree
 as discussed with Dan. We have ack/review on XFS, EXT4
 device mapper & VIRTIO patches.

 This version has fix for test bot build failure. Keeping
 all the existing r-o-bs. Jakob CCed also tested the patch
 series and confirmed the working of v9.
 ---

 This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [5] for virtio-pmem. Documented the impact of
 possible page cache side channel attacks with suggested
 countermeasures.

 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [7]
 on possible implications of page cache side channel attacks with 
 virtio pmem. After thorough analysis of details of known side 
 channel attacks, below are the suggestions:

 - Depends entirely on how host backing image file is mapped 
   into guest address space. 

 - virtio-pmem device emulation, by default shared mapping is used
   to map host backing file. It is recommended to use separate
   backing file at host side for every guest. This will prevent
   any possibility of executing common code from multiple guests
   and any chance of inferring guest local data based based on 
   execution time.

 - If backing file is required to be shared among multiple guests 
   it is recommended to don't support host page cache eviction 
   commands from the guest driver. This will avoid any possibility
   of inferring guest local data or host data from another guest. 

 - Proposed device specification [6] for virtio-pmem device with 
   details of possible security implications and suggested 
   countermeasures for device emulation.

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v13: [1] 
 - Rebased to Linux-5.2-rc5
 - Fix S390x build failure in patch 3
 - Fix for !CONFIG_DAX with dax_synchronous
 - Fix sparse warning in virtio patch 2

Changes from PATCH v12: [2] 
 - Minor changes(function name, dev_err -> dev_info & 
   make function static in virtio patch - [Cornelia]
 - Added r-o-b of Mike in patch 4

Changes from PATCH v11: 
 - Change implmentation for setting of synchronous DAX type
   for device mapper - [Mike] 

Changes from PATCH v10:
 - Rebased on Linux-5.2-rc4

Changes from PATCH v9:
 - Kconfig help text add two spaces - Randy
 - Fixed libnvdimm 'bio' include warning - Dan
 - virtio-pmem, separate request/resp struct and 
   move to uapi file with updated license - DavidH
 - Use virtio32* type for req/resp endianess - DavidH
 - Added tested-by & ack-by of Jakob
 - Rebased to 5.2-rc1

Changes from PATCH v8:
 - Set device mapper synchronous if all target devices support - Dan
 - Move virtio_pmem.h to nvdimm directory  - Dan
 - Style, indentation & better error messages in patch 2 - DavidH
 - Added MST's ack in patch 2.

Changes from PATCH v7:
 - Corrected pending request queue logic (patch 2) - Jakub Staroń
 - Used unsigned long flags for passing DAXDEV_F_SYNC (patch 3) - Dan
 - Fixed typo =>  vma 'flag' to 'vm_flag' (patch 4)
 - Added rob in patch 6 & patch 2

Changes from PATCH v6: 
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: 
  Changes suggested in by - [Cornelia, Yuval]
- Remove assignment chaining in virtio driver
- Better error message and remove not required free
- Check nd_region before use

  Changes suggested by - [Jan Kara]
- dax_synchronous() for !CONFIG_DAX
- Correct 'daxdev_mapping_supported' comment and non-dax implementation

  Changes suggested by - [Dan Williams]
- Pass meaningful flag 'DAXDEV_F_SYNC' to alloc_dax
- Gate nvdimm_flush instead of additional async parameter
- Move block chaining logic to flush callback than common nvdimm_flush
- Use NULL flush callback for generic flush for better readability [Dan, Jan]

- Use virtio device id 27 from 25(already used) - [MST]

Changes from PATCH v4:
- Factor out MAP_SYNC supported functionality to a common helper
				[Dave, Darrick, Jan]
- Comment, indentation and virtqueue_kick failure handle - Yuval Shaia

Changes from PATCH v3: 
- Use generic dax_synchronous() helper to check for DAXDEV_SYNC 
  flag - [Dan, Darrick, Jan]
- Add 'is_nvdimm_async' function
- Document page cache side channel attacks implications & 
  countermeasures - [Dave Chinner, Michael]

Changes from PATCH v2: 
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: 
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Pankaj Gupta (7):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   dm: dm: Enable synchronous dax
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/6/12/624
[2] https://lkml.org/lkml/2019/6/11/831
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://marc.info/?l=qemu-devel&m=155860751202202&w=2
[6] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[7] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   19 +++++
 drivers/md/dm-table.c            |   24 +++++--
 drivers/md/dm.c                  |    5 -
 drivers/md/dm.h                  |    5 +
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  125 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 ++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   55 +++++++++++++++++
 drivers/s390/block/dcssblk.c     |    2 
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   41 ++++++++++++
 include/linux/libnvdimm.h        |   10 ++-
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   35 ++++++++++
 22 files changed, 505 insertions(+), 34 deletions(-)
```
