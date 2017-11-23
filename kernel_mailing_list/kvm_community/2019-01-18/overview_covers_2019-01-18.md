

#### [kvm-unit-tests PATCH v6 00/11] s390x: Add cross hypervisor and disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks.

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console
    * Binary generation in Makefile

v6:
	* Added linemode sclp loop to print large strings
	* Fixed sclp read info locking
	* commit message fixups

v5:
	* Cleaned up linemode
	* Minor fixups and squash of sclp int and lock patches
	* Removed time patches, added phys alloc setup

v4:
	* Added sigp header file
	* Moved clearing to xgr instead of lm
	* Minor renames, comment additions

v3:
	* Rebased on David's SCLP fixes
	* Added binary generation make command
	* Split up cleanup and sclp common movement
	* Fixed whitespace problems
	* Added more comments
	* Added linemode buffer to get rid of line splits

v2:
	* Moved cleanup to the front and broadened patch
	* Split up SCLP patch into interrupt and linemode
	* Removed unneeded instructions
	* Improved comments and commit messages


Janosch Frank (11):
  s390x: Add Sigp header file
  s390x: Rename and cleanup sclp-ascii.c
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch and enable 64 bit addressing mode
  s390x: Add BSS clearing for non ELF boot
  s390x: Move common sclp data and functions to sclp.c
  s390x: Use interrupts in SCLP and add locking
  s390x: Add linemode console
  s390x: Add linemode buffer to fix newline on every print
  s390x: Add binary generation to makefile
  s390x: Initialize the physical allocator on mem init

 lib/s390x/asm/arch_def.h  |   1 +
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/asm/sigp.h      |  60 +++++++++++
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |  13 +--
 lib/s390x/sclp-ascii.c    |  68 ------------
 lib/s390x/sclp-console.c  | 260 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/sclp.c          |  83 ++++++++++++++-
 lib/s390x/sclp.h          |  62 ++++++++++-
 s390x/Makefile            |  13 ++-
 s390x/cstart64.S          |  41 +++++++-
 s390x/flat.lds            |  15 ++-
 12 files changed, 536 insertions(+), 94 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h
 delete mode 100644 lib/s390x/sclp-ascii.c
 create mode 100644 lib/s390x/sclp-console.c
```
#### [PATCH 00/29] KVM: VMX: Move vCPU-run to proper asm sub-routine
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
series that moved VM-Enter and VM-Exit to proper assembly[2].  So this
is sort of a V2, but with a much more ambitious end goal.

This series has not been tested whatsoever on i386, testing cycles would
be much appreciated.  Regardless, I'll work on configuring a 32-bit
environment to do proper testing.

Josh and Andi, I apologize for spamming your mailboxes.  I considered
excepting you from my auto-cc-all script, but I couldn't think of a
better way of saying "thank you" for providing me the opportunity to
expand my knowledge of inline asm. :-)  Joking aside, thank you for
pushing back, it was a worthwhile endeavor.

[1] https://patchwork.kernel.org/patch/10765309/
[2] https://patchwork.kernel.org/cover/10739549/

Sean Christopherson (29):
  KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
  KVM: nVMX: Check a single byte for VMCS "launched" in nested early
    checks
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
  KVM: VMX: Make the vCPU-run asm routine callable from C
  KVM: VMX: Reorder clearing of registers in the vCPU-run assembly flow

 arch/x86/include/asm/kvm_host.h      |  33 +++---
 arch/x86/include/asm/kvm_vcpu_regs.h |  26 +++++
 arch/x86/kvm/vmx/nested.c            |  53 ++++-----
 arch/x86/kvm/vmx/vmcs.h              |   1 +
 arch/x86/kvm/vmx/vmenter.S           | 159 ++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c               | 160 +++------------------------
 arch/x86/kvm/vmx/vmx.h               |   3 +-
 7 files changed, 242 insertions(+), 193 deletions(-)
 create mode 100644 arch/x86/include/asm/kvm_vcpu_regs.h
```
