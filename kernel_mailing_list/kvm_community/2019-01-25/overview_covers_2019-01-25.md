

#### [PATCH 0/5] KVM: arm/arm64: Fix VCPU power management problems
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c

This series fixes a number of issues:

 - When powering on and resetting VCPUs, we can be preempted in the
   middle which can lead to guest system register corruption.

 - We were missing support for PSCI ON_PENDING when multiple VCPUs try
   to turn on a target VCPU at the same time.

 - Powering off a VCPU could race with powering on the same VCPU.

 - We unnecesarily panic'ed if we found a non-initialized guest system
   register.

The main approach to fixing all these problems is by using VCPU
requests.

See the individual patches for more details.

Christoffer Dall (3):
  KVM: arm/arm64: Reset the VCPU without preemption and vcpu state
    loaded
  KVM: arm/arm64: Require VCPU threads to turn them self off
  KVM: arm/arm64: Implement PSCI ON_PENDING when turning on VCPUs

Marc Zyngier (2):
  arm/arm64: KVM: Allow a VCPU to fully reset itself
  arm/arm64: KVM: Don't panic on failure to properly reset system
    registers

 arch/arm/include/asm/kvm_host.h   | 22 ++++++++++-
 arch/arm/kvm/coproc.c             |  4 +-
 arch/arm/kvm/reset.c              | 24 ++++++++++++
 arch/arm64/include/asm/kvm_host.h | 23 ++++++++++-
 arch/arm64/kvm/reset.c            | 50 +++++++++++++++++++++++-
 arch/arm64/kvm/sys_regs.c         |  4 +-
 virt/kvm/arm/arm.c                | 40 ++++++++++++++-----
 virt/kvm/arm/psci.c               | 64 +++++++++++++++----------------
 8 files changed, 177 insertions(+), 54 deletions(-)
```
#### [PATCH v2 0/2] tweak HYPERV_CPUID_ENLIGHTMENT_INFO
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Be more consistent with genuine Hyper-V: don't recommend using Enlightened
VMCS when it wasn't enabled, don't advertise reset via synthetic MSR.

Vitaly Kuznetsov (2):
  x86/kvm/hyper-v: don't recommend doing reset via synthetic MSR
  x86/kvm/hyper-v: recommend using eVMCS only when it is enabled

 arch/x86/kvm/hyperv.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)
```
#### [PATCH v2 0/2] KVM: arm/arm64: Add VCPU workarounds firmware register
##### From: Andre Przywara <andre.przywara@arm.com>

```c

Hi,

this is a try to address Dave's comments concerning the readability of
the compatiblitiy check of the protection levels.
If picks up the idea of creating a linear scale, where smaller values
mean less protection. Originally the suggestion was to use a signed
encoding, with "unknown" being 0. While this sounds neat, it turns out
to be not very readable and hard to communicate in the ABI
documentation. I don't think it's feasible to establish a forward
looking standard for each and every upcoming firmware workaround
register, so I just moved everything up to avoid negative values.

Please let me know if this makes more sense or what else could be done.

Regarding the states in "workaround 1": At the moment the host kernel side
only reports the availability of the SMC call. "Not available" could
mean both "not needed" or "not implemented (aka. vulnerable)".
If the kernel would separate the last two states, we could propagate
this in the firmware register.
So would we need this in the host side to allow migration from
"workaround available" to "always mitigated, no w/a needed"?

Cheers,
Andre

-----------------------------
Workarounds for Spectre variant 2 or 4 vulnerabilities require some help
from the firmware, so KVM implements an interface to provide that for
guests. When such a guest is migrated, we want to make sure we don't
loose the protection the guest relies on.

This introduces two new firmware registers in KVM's GET/SET_ONE_REG
interface, so userland can save the level of protection implemented by
the hypervisor and used by the guest. Upon restoring these registers,
we make sure we don't downgrade and reject any values that would mean
weaker protection.
The protection level is encoding in the lower 4 bits, with smaller
values indicating weaker protection.

Patch 1 implements the two firmware registers, patch 2 adds the
documentation.

ARM(32) is a bit of a pain (again), as the firmware register interface
is shared, but 32-bit does not implement all the workarounds.
For now I stuffed two wrappers into kvm_emulate.h, which doesn't sound
like the best solution. Happy to hear about better solutions.

This has been tested with a hack to allow faking the protection level
via a debugfs knob, then saving/restoring via some userland tool calling
the GET_ONE_REG/SET_ONE_REG ioctls.

Please have a look and comment!

Cheers,
Andre

Andre Przywara (2):
  KVM: arm/arm64: Add save/restore support for firmware workaround state
  KVM: doc: add API documentation on the KVM_REG_ARM_WORKAROUNDS
    register

 Documentation/virtual/kvm/arm/psci.txt |  21 +++++
 arch/arm/include/asm/kvm_emulate.h     |  10 +++
 arch/arm/include/uapi/asm/kvm.h        |   9 ++
 arch/arm64/include/asm/kvm_emulate.h   |  14 +++
 arch/arm64/include/uapi/asm/kvm.h      |   9 ++
 virt/kvm/arm/psci.c                    | 118 +++++++++++++++++++++----
 6 files changed, 165 insertions(+), 16 deletions(-)
```
#### [PATCH v3 00/33] KVM: VMX: Move vCPU-run to proper asm sub-routine
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM's assembly for transitioning to/from a VMX guest is currently
implemented via inline asm.  At best it can be called "inscrutable", at
worst, well, that can't be printed here.

This series' ultimate goal is to move the transition code to a proper
assembly sub-routine that can be directly invoked from C code.
Unsurprisingly, making that happen requires a large number of patches
to carefully disarm all of the booby traps hiding in the shadows.

This series does NOT apply directly on the official KVM branches, but
rather on the official branches plus the patch that splits out a small
amount of vmx_vcpu_run() code to a helper, __vmx_vcpu_run()[1].  Adding
the helper function fixes a bug for kernel v5.0, i.e. absolutely should
be applied before this series, and not accounting for that change would
result in non-trivial conflicts.

A few patches in this series are carried over from the back half of the
series that moved VM-Enter and VM-Exit to proper assembly[2], but is
versioned as a different series given the much more ambitious end goal.

v1: https://patchwork.kernel.org/cover/10771525/

v2: https://patchwork.kernel.org/cover/10779721/
  - Fully tested 32-bit, amazingly there was no breakage.
  - Use 'b' and '=b' for asm constraints instead of trying to get fancy
    with 'bl' and '=ebx'. [Paolo]
  - Rename explicit VCPU reg indicides to __VCPU_REGS_R*. [Paolo]
  - Add Jim and Konrad's Reviewed-by tags.

v3:
  - Add patch to zero out registers that are reloaded from the stack. [Paolo]
  - Let compiler choose reg for @vm_fail in nested early checks. [Jim]
  - Add more "Reviewed-by Jim" tags.
  - Split "Make the vCPU-run asm routine callable from C" into separate
    patches to make each incremental change bisect-friendly.

[1] https://patchwork.kernel.org/patch/10765309/
[2] https://patchwork.kernel.org/cover/10739549/

Sean Christopherson (33):
  KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
  KVM: nVMX: Check a single byte for VMCS "launched" in nested early
    checks
  KVM: VMX: Zero out *all* general purpose registers after VM-Exit
  KVM: VMX: Modify only RSP when creating a placeholder for guest's RCX
  KVM: VMX: Save RSI to an unused output in the vCPU-run asm blob
  KVM: VMX: Manually load RDX in vCPU-run asm blob
  KVM: VMX: Let the compiler save/load RDX during vCPU-run
  KVM: nVMX: Remove a rogue "rax" clobber from
    nested_vmx_check_vmentry_hw()
  KVM: nVMX: Drop STACK_FRAME_NON_STANDARD from
    nested_vmx_check_vmentry_hw()
  KVM: nVMX: Explicitly reference the scratch reg in nested early checks
  KVM: nVMX: Capture VM-Fail to a local var in
    nested_vmx_check_vmentry_hw()
  KVM: nVMX: Capture VM-Fail via CC_{SET,OUT} in nested early checks
  KVM: nVMX: Reference vmx->loaded_vmcs->launched directly
  KVM: nVMX: Let the compiler select the reg for holding HOST_RSP
  KVM: nVMX: Cache host_rsp on a per-VMCS basis
  KVM: VMX: Load/save guest CR2 via C code in __vmx_vcpu_run()
  KVM: VMX: Update VMCS.HOST_RSP via helper C function
  KVM: VMX: Pass "launched" directly to the vCPU-run asm blob
  KVM: VMX: Invert the ordering of saving guest/host scratch reg at
    VM-Enter
  KVM: VMX: Don't save guest registers after VM-Fail
  KVM: VMX: Use vcpu->arch.regs directly when saving/loading guest state
  KVM: x86: Explicitly #define the VCPU_REGS_* indices
  KVM: VMX: Use #defines in place of immediates in VM-Enter inline asm
  KVM: VMX: Create a stack frame in vCPU-run
  KVM: VMX: Move vCPU-run code to a proper assembly routine
  KVM: VMX: Fold __vmx_vcpu_run() back into vmx_vcpu_run()
  KVM: VMX: Rename ____vmx_vcpu_run() to __vmx_vcpu_run()
  KVM: VMX: Use RAX as the scratch register during vCPU-run
  KVM: VMX: Pass @launched to the vCPU-run asm via standard ABI regs
  KVM: VMX: Return VM-Fail from vCPU-run assembly via standard ABI reg
  KVM: VMX: Preserve callee-save registers in vCPU-run asm sub-routine
  KVM: VMX: Call vCPU-run asm sub-routine from C and remove clobbering
  KVM: VMX: Reorder clearing of registers in the vCPU-run assembly flow

 arch/x86/include/asm/kvm_host.h      |  33 +++---
 arch/x86/include/asm/kvm_vcpu_regs.h |  25 ++++
 arch/x86/kvm/vmx/nested.c            |  53 ++++-----
 arch/x86/kvm/vmx/vmcs.h              |   1 +
 arch/x86/kvm/vmx/vmenter.S           | 170 +++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c               | 160 +++----------------------
 arch/x86/kvm/vmx/vmx.h               |   3 +-
 7 files changed, 252 insertions(+), 193 deletions(-)
 create mode 100644 arch/x86/include/asm/kvm_vcpu_regs.h
```
#### [PATCH kvmtool 0/6] Various convenience fixes
##### From: Andre Przywara <andre.przywara@arm.com>

```c

As I found myself using kvmtool more often in the last weeks, I got more
and more annoyed by some smaller "ticks" that kvmtool shows.

So this is an attempt to post various smaller fixes I gathered up over
the years, but never found worth enough to send out:

- drop unnecessarily detailed debug output
- add /chosen/stdout-path node in .dtb
- honour make -s switch
- remove pointless kvmtool version number
- improve meaningless PMU error message
- introduce autodetection of supported GIC type

Please have a look!

Cheers,
Andre.

Andre Przywara (6):
  arm: turn pr_info() into pr_debug() messages
  arm: fdt: add stdout-path to /chosen node
  Makefile: support -s switch
  Makefile: Remove echoing of kvmtools version file
  arm: pmu: Improve PMU error reporting
  arm: Auto-detect guest GIC type

 Makefile                     | 16 +++++++++++++++-
 arm/fdt.c                    |  3 ++-
 arm/gic.c                    | 25 +++++++++++++++++++++++++
 arm/include/arm-common/gic.h |  1 +
 arm/kvm.c                    | 16 ++++++++--------
 arm/pmu.c                    |  2 +-
 util/KVMTOOLS-VERSION-GEN    |  1 -
 virtio/mmio.c                |  3 ++-
 8 files changed, 54 insertions(+), 13 deletions(-)
```
#### [PATCH 0/2] i386: arch_capabilities fixes + migratability
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c

This series works around KVM bugs that affect the arch_capabilities
feature.  One bug made the feature be enabled incorrect on AMD hosts,
and another one made the feature unsafe to enable on most Intel hosts.
With the work around, we can finally make arch_capabilities a migratable
feature.

Unfortunately, the work around has the side effect of making
arch_capabilities unavailable on hosts without hardware support for the
feature until one of the KVM bugs is fixed.

Eduardo Habkost (2):
  i386: kvm: Disable arch_capabilities if MSR can't be set
  i386: Make arch_capabilities migratable

 target/i386/cpu.c | 1 -
 target/i386/kvm.c | 9 +++++++++
 2 files changed, 9 insertions(+), 1 deletion(-)
```
