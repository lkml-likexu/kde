

#### [PATCH v8 0/2] add support for VCPU event states
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c

Support for KVM_GET/SET_VCPU_EVENTS to get/set the SError exception
state, and support the state migration.

Now the VCPU event only includes the SError exception status, it can be
extended if needed. When do migration, If source machine has serror pending, 
the target machine is also needed to pend this serror regardless of whether
target machine can support to set the serror syndrome.

Dongjiu Geng (2):
  linux-headers: Update to kernel mainline commit 815f0ddb3
  target: arm: Add support for VCPU event states

 include/standard-headers/linux/input.h |  9 +++--
 linux-headers/asm-arm/kvm.h            | 13 +++++++
 linux-headers/asm-arm64/kvm.h          | 13 +++++++
 linux-headers/linux/kvm.h              |  1 +
 target/arm/cpu.h                       |  7 ++++
 target/arm/kvm64.c                     | 69 ++++++++++++++++++++++++++++++++++
 target/arm/machine.c                   | 22 +++++++++++
 7 files changed, 130 insertions(+), 4 deletions(-)
```
#### [PATCH v2 00/18] KVM: nVMX: add option to perform early consistency
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM currently defers many VMX consistency checks to the CPU, including
checks that result in VMFail (as opposed to VMExit).  This behavior
may be undesirable for some users since this means KVM detects certain
classes of VMFail only after it has processed guest state.  Because
there is a strict ordering between checks that cause VMFail and those
that cause VMExit, i.e. all VMFail checks are performed before any
checks that cause VMExit, we can detect all VMFail conditions via a
dry run of sorts.

The end goal of this series is to add an optional (param-controlled)
pre-run VMEnter into the nested_vmx_run() flow in order to perform
all VMFail consistency checks prior to actually running vmcs02.  By
itself, this is not a complex process, but getting KVM to a point
where the approach is viable requires a fair amount of refactoring,
e.g. to split prepare_vmcs02() so that there is a point where vmcs02
can pass the VMFail checks without first consuming guest state.

And while the goal (and subject) of this series is to enable early
consistency checks, the vast majority of the series deals with bug
fixes and cleanups in the nested VMX code.  During the refactoring
and testing, a number of pre-existing bugs, opportunities for code
cleanup and easy optimization points (which unconvered more bugs)
were encountered.

Ideally, these patches would be split into 3-4 separate series,
especially the bug fix patches.  I smushed everything into a single
series because the early VMEnter code breaks without the bug fixes
and the refactoring shuffles the same code, and some of the cleanup
and fixes are inter-dependent.

Patch Synopsis:
  1-4:   bug fixes
  5-6:   optimizations
  7:     function rename
  8:     bug fix and refactoring
  9-12:  refactoring
  13-14: bug fix
  15:    refactoring
  16:    optimization and prereq for early consistency checks
  17-18: early consistency checks

v1: https://www.spinics.net/lists/kvm/msg172795.html

v2:
  - rebased on tag kvm-4.19-2
  - added patch to skip instr in nested_vmx_{fail,succeed}

Sean Christopherson (18):
  KVM: nVMX: move host EFER consistency checks to VMFail path
  KVM: nVMX: move vmcs12 EPTP consistency check to
    check_vmentry_prereqs()
  KVM: nVMX: use vm_exit_controls_init() to write exit controls for
    vmcs02
  KVM: nVMX: reset cache/shadows on nested consistency check VMExit
  KVM: vmx: do not unconditionally clear EFER switching
  KVM: nVMX: try to set EFER bits correctly when init'ing entry controls
  KVM: nVMX: rename enter_vmx_non_root_mode to
    nested_vmx_enter_non_root_mode
  KVM: nVMX: move check_vmentry_postreqs() call to
    nested_vmx_enter_non_root_mode()
  KVM: nVMX: assimilate nested_vmx_entry_failure() into
    nested_vmx_enter_non_root_mode()
  KVM: nVMX: split pieces of prepare_vmcs02() to prepare_vmcs02_early()
  KVM: nVMX: do early preparation of vmcs02 before
    check_vmentry_postreqs()
  KVM: vVMX: rename label for post-enter_guest_mode consistency check
  KVM: nVMX: do not skip VMEnter instruction that succeeds
  KVM: nVMX: do not call nested_vmx_succeed() for consistency check
    VMExit
  KVM: nVMX: call kvm_skip_emulated_instruction in
    nested_vmx_{fail,succeed}
  KVM: vmx: write HOST_IA32_EFER in vmx_set_constant_host_state()
  KVM: nVMX: add option to perform early consistency checks via H/W
  KVM: nVMX: WARN if nested run hits VMFail with early consistency
    checks enabled

 arch/x86/kvm/vmx.c | 972 ++++++++++++++++++++++++++-------------------
 1 file changed, 556 insertions(+), 416 deletions(-)
```
#### [PATCH v2 0/3] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (3):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute when declaring shared variables

 arch/x86/include/asm/mem_encrypt.h |   6 +
 arch/x86/kernel/head64.c           |   9 ++
 arch/x86/kernel/kvmclock.c         |  30 ++++-
 arch/x86/kernel/vmlinux.lds.S      |  17 +++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 5 files changed, 227 insertions(+), 67 deletions(-)
```
