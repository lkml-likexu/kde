#### [PATCH V4 1/4] kvm: remove redundant reserved page check
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c
PageReserved() is already checked inside kvm_is_reserved_pfn(),
remove it from kvm_set_pfn_dirty().

Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yu <yu.c.zhang@linux.intel.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Pankaj Gupta <pagupta@redhat.com>
---
 virt/kvm/kvm_main.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-fixes-4.19-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-4.19-1 tag to get two small
fixes which should go into 4.19.

Thanks,
Paul.

The following changes since commit fd8ca6dac9b45db8503cf508880edd63e039e2f2:

  KVM/x86: Use CC_SET()/CC_OUT in arch/x86/kvm/vmx.c (2018-08-06 18:18:41 +0200)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-4.19-1

for you to fetch changes up to 46dec40fb741f00f1864580130779aeeaf24fb3d:

  KVM: PPC: Book3S HV: Don't truncate HPTE index in xlate function (2018-08-20 16:05:45 +1000)

----------------------------------------------------------------
PPC KVM fixes for 4.19

Two small fixes for KVM on POWER machines; one fixes a bug where pages
might not get marked dirty, causing guest memory corruption on migration,
and the other fixes a bug causing reads from guest memory to use the
wrong guest real address for very large HPT guests (>256G of memory),
leading to failures in instruction emulation.

----------------------------------------------------------------
Paul Mackerras (2):
      KVM: PPC: Book3S HV: Use correct pagesize in kvm_unmap_radix()
      KVM: PPC: Book3S HV: Don't truncate HPTE index in xlate function

 arch/powerpc/kvm/book3s_64_mmu_hv.c    | 2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 6 +++---
 2 files changed, 4 insertions(+), 4 deletions(-)
```
#### [GIT PULL] Second batch of KVM changes for 4.19-rc1
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit ad1d69735878a6bf797705b5d2a20316d35e1113:

  Merge tag 'fuse-update-4.19' of git://git.kernel.org/pub/scm/linux/kernel/git/mszeredi/fuse (2018-08-21 18:47:36 -0700)

are available in the git repository at:


  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 0027ff2a75f9dcf0537ac0a65c5840b0e21a4950:

  KVM: VMX: fixes for vmentry_l1d_flush module parameter (2018-08-22 16:48:39 +0200)

----------------------------------------------------------------
ARM: Support for Group0 interrupts in guests, Cache management
optimizations for ARMv8.4 systems, Userspace interface for RAS, Fault
path optimization, Emulated physical timer fixes, Random cleanups

x86: fixes for L1TF, a new test case, non-support for SGX (inject the
right exception in the guest), a lockdep false positive

----------------------------------------------------------------

Since you mentioned this in the past as something you'd like to be told
about, don't read too much into the commit dates; I added some last-minute
stable Ccs.

Arnd Bergmann (1):
      x86: kvm: avoid unused variable warning

Christoffer Dall (13):
      KVM: arm/arm64: Fix vgic init race
      KVM: arm/arm64: vgic: Define GICD_IIDR fields for GICv2 and GIv3
      KVM: arm/arm64: vgic: Keep track of implementation revision
      KVM: arm/arm64: vgic: GICv2 IGROUPR should read as zero
      KVM: arm/arm64: vgic: Add group field to struct irq
      KVM: arm/arm64: vgic: Signal IRQs using their configured group
      KVM: arm/arm64: vgic: Permit uaccess writes to return errors
      KVM: arm/arm64: vgic: Return error on incompatible uaccess GICD_IIDR writes
      KVM: arm/arm64: vgic: Allow configuration of interrupt groups
      KVM: arm/arm64: vgic: Let userspace opt-in to writable v2 IGROUPR
      KVM: arm/arm64: vgic: Update documentation of the GIC devices wrt IIDR
      KVM: arm/arm64: Fix potential loss of ptimer interrupts
      KVM: arm/arm64: Fix lost IRQs from emulated physcial timer when blocked

Dongjiu Geng (3):
      arm/arm64: KVM: Add KVM_GET/SET_VCPU_EVENTS
      arm64: KVM: export the capability to set guest SError syndrome
      KVM: Documentation: rename the capability of KVM_CAP_ARM_SET_SERROR_ESR

Gustavo A. R. Silva (1):
      KVM: arm: Use true and false for boolean values

James Morse (2):
      KVM: arm64: Share the parts of get/set events useful to 32bit
      KVM: arm: Add 32bit get/set events support

Jia He (2):
      KVM: arm/arm64: vgic: Move DEBUG_SPINLOCK_BUG_ON to vgic.h
      KVM: arm/arm64: vgic: Do not use spin_lock_irqsave/restore with irq disabled

Kees Cook (1):
      KVM: arm64: vgic-its: Remove VLA usage

Marc Zyngier (13):
      arm64: KVM: Add support for Stage-2 control of memory types and cacheability
      arm64: KVM: Handle Set/Way CMOs as NOPs if FWB is present
      arm64: KVM: Avoid marking pages as XN in Stage-2 if CTR_EL0.DIC is set
      KVM: arm/arm64: Consolidate page-table accessors
      KVM: arm/arm64: Stop using the kernel's {pmd,pud,pgd}_populate helpers
      KVM: arm/arm64: Remove unnecessary CMOs when creating HYP page tables
      KVM: arm/arm64: Enable adaptative WFE trapping
      KVM: arm/arm64: vgic-debug: Show LPI status
      arm64: KVM: Cleanup tpidr_el2 init on non-VHE
      KVM: arm64: Remove non-existent AArch32 ICC_SGI1R encoding
      KVM: arm/arm64: vgic-v3: Add core support for Group0 SGIs
      KVM: arm64: vgic-v3: Add support for ICC_SGI0R_EL1 and ICC_ASGI1R_EL1 accesses
      KVM: arm: vgic-v3: Add support for ICC_SGI0R and ICC_ASGI1R accesses

Mark Rutland (1):
      KVM: arm/arm64: vgic: Fix possible spectre-v1 write in vgic_mmio_write_apr()

Paolo Bonzini (2):
      Merge tag 'kvmarm-for-v4.19' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: VMX: fixes for vmentry_l1d_flush module parameter

Peter Xu (5):
      tools: introduce test_and_clear_bit
      kvm: selftest: unify the guest port macros
      kvm: selftest: include the tools headers
      kvm: selftest: pass in extra memory when create vm
      kvm: selftest: add dirty logging test

Punit Agrawal (2):
      KVM: arm/arm64: Skip updating PMD entry if no change
      KVM: arm/arm64: Skip updating PTE entry if no change

Sean Christopherson (2):
      KVM: vmx: Add defines for SGX ENCLS exiting
      KVM: vmx: Inject #UD for SGX ENCLS instruction in guest

Thomas Gleixner (1):
      KVM: x86: SVM: Call x86_spec_ctrl_set_guest/host() with interrupts disabled

Yi Wang (1):
      x86/kvm/vmx: Fix coding style in vmx_setup_l1d_flush()

 Documentation/virtual/kvm/api.txt                 |  80 +++++-
 Documentation/virtual/kvm/devices/arm-vgic-v3.txt |   8 +
 Documentation/virtual/kvm/devices/arm-vgic.txt    |  15 +-
 arch/arm/include/asm/kvm_emulate.h                |  12 +-
 arch/arm/include/asm/kvm_host.h                   |   5 +
 arch/arm/include/asm/kvm_mmu.h                    |  14 +-
 arch/arm/include/uapi/asm/kvm.h                   |  13 +
 arch/arm/kvm/coproc.c                             |  25 +-
 arch/arm/kvm/guest.c                              |  23 ++
 arch/arm64/include/asm/cpucaps.h                  |   3 +-
 arch/arm64/include/asm/kvm_arm.h                  |   1 +
 arch/arm64/include/asm/kvm_emulate.h              |  17 ++
 arch/arm64/include/asm/kvm_host.h                 |  28 +-
 arch/arm64/include/asm/kvm_mmu.h                  |  35 ++-
 arch/arm64/include/asm/memory.h                   |   7 +
 arch/arm64/include/asm/pgtable-prot.h             |  24 +-
 arch/arm64/include/asm/sysreg.h                   |   3 +
 arch/arm64/include/uapi/asm/kvm.h                 |  13 +
 arch/arm64/kernel/cpufeature.c                    |  20 ++
 arch/arm64/kvm/guest.c                            |  33 +++
 arch/arm64/kvm/hyp-init.S                         |   6 +-
 arch/arm64/kvm/hyp/sysreg-sr.c                    |   5 -
 arch/arm64/kvm/inject_fault.c                     |   6 +-
 arch/arm64/kvm/reset.c                            |   4 +
 arch/arm64/kvm/sys_regs.c                         |  54 +++-
 arch/x86/include/asm/vmx.h                        |   3 +
 arch/x86/kvm/svm.c                                |   8 +-
 arch/x86/kvm/vmx.c                                |  72 +++--
 arch/x86/kvm/x86.c                                |   4 +-
 include/kvm/arm_vgic.h                            |   9 +-
 include/linux/irqchip/arm-gic-v3.h                |  10 +
 include/linux/irqchip/arm-gic.h                   |  11 +
 include/uapi/linux/kvm.h                          |   1 +
 tools/include/linux/bitmap.h                      |  17 ++
 tools/testing/selftests/kvm/Makefile              |   5 +-
 tools/testing/selftests/kvm/cr4_cpuid_sync_test.c |  32 +--
 tools/testing/selftests/kvm/dirty_log_test.c      | 308 ++++++++++++++++++++++
 tools/testing/selftests/kvm/include/kvm_util.h    |  45 +++-
 tools/testing/selftests/kvm/include/test_util.h   |   2 -
 tools/testing/selftests/kvm/lib/kvm_util.c        |  58 ++++
 tools/testing/selftests/kvm/lib/x86.c             |  18 +-
 tools/testing/selftests/kvm/set_sregs_test.c      |   2 +-
 tools/testing/selftests/kvm/state_test.c          |  32 +--
 tools/testing/selftests/kvm/sync_regs_test.c      |  21 +-
 tools/testing/selftests/kvm/vmx_tsc_adjust_test.c |  43 +--
 virt/kvm/arm/arch_timer.c                         |  15 +-
 virt/kvm/arm/arm.c                                |  51 ++++
 virt/kvm/arm/mmu.c                                |  87 ++++--
 virt/kvm/arm/vgic/vgic-debug.c                    |  50 +++-
 virt/kvm/arm/vgic/vgic-init.c                     |  24 +-
 virt/kvm/arm/vgic/vgic-its.c                      |  27 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c                  |  66 ++++-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                  |  72 +++--
 virt/kvm/arm/vgic/vgic-mmio.c                     |  56 +++-
 virt/kvm/arm/vgic/vgic-mmio.h                     |  25 +-
 virt/kvm/arm/vgic/vgic-v2.c                       |  10 +-
 virt/kvm/arm/vgic/vgic-v3.c                       |  13 +-
 virt/kvm/arm/vgic/vgic.c                          |  19 +-
 virt/kvm/arm/vgic/vgic.h                          |   7 +
 59 files changed, 1372 insertions(+), 305 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/dirty_log_test.c
```
#### [PATCH] KVM: s390: vsie: Consolidate CRYCB validation
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Currently when shadowing the CRYCB on SIE entrance, the validation
tests the following:
- accept only FORMAT1 or FORMAT2
- test if MSAext facility (76) is installed
- accept the CRYCB if no keys are used
- verifies that the CRYCB format1 is inside a page
- verifies that the CRYCB origin is not 0

This is not following the architecture.

On SIE entrance, the CRYCB must be validated before accepting
any of its entries.

Let's do the validation in the right order and also verify
correctly the FORMAT2 CRYCB.

The testing of facility MSAext3 (76) is not useful as it is
already tested by kvm_crypto_init() to set FORMAT1.

The testing of a null CRYCB origin must be done what ever
the format of the guest3 CRYCB is.

The CRYCB must be contained inside a page, but the CRYCB size
depends on the CRYCB format.
Lets test what the guest2 initialized, we can not trust it to have
done things right.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/kvm/vsie.c | 35 +++++++++++++++++++++++++----------
 1 file changed, 25 insertions(+), 10 deletions(-)

```
#### [PATCH v2 1/5] KVM: s390: vsie: BUG correction by shadow_crycb
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Copy the key mask to the right offset inside the shadow CRYCB

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/vsie.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/5] tools: introduce test_and_clear_bit
##### From: Peter Xu <peterx@redhat.com>

```c
We have test_and_set_bit but not test_and_clear_bit.  Add it.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/include/linux/bitmap.h | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
#### [PATCH] KVM: VMX: fixes for vmentry_l1d_flush module parameter
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Two bug fixes:

1) missing entries in the l1d_param array; this can cause a host crash
if an access attempts to reach the missing entry. Future-proof the get
function against any overflows as well.  However, the two entries
VMENTER_L1D_FLUSH_EPT_DISABLED and VMENTER_L1D_FLUSH_NOT_REQUIRED must
not be accepted by the parse function, so disable them there.

2) invalid values must be rejected even if the CPU does not have the
bug, so test for them before checking boot_cpu_has(X86_BUG_L1TF)

... and a small refactoring, since the .cmd field is redundant with
the index in the array.

Reported-by: Bandan Das <bsd@redhat.com>
Cc: stable@vger.kernel.org
Fixes: a7b9020b06ec6d7c3f3b0d4ef1a9eba12654f4f7
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Tested-by: Jack Wang <jinpu.wang@profitbricks.com>
---
 arch/x86/kvm/vmx.c | 26 ++++++++++++++++----------
 1 file changed, 16 insertions(+), 10 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Do not re-{try,execute} after failed emulation in L2
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Commit a6f177efaa58 ("KVM: Reenter guest after emulation failure if
due to access to non-mmio address") added reexecute_instruction() to
handle the scenario where two (or more) vCPUS race to write a shadowed
page, i.e. reexecute_instruction() is intended to return true if and
only if the instruction being emulated was accessing a shadowed page.
As L0 is only explicitly shadowing L1 tables, an emulation failure of
a nested VM instruction cannot be due to a race to write a shadowed
page and so should never be re-executed.

This fixes an issue where an "MMIO" emulation failure[1] in L2 is all
but guaranteed to result in an infinite loop when TDP is enabled.
Because "cr2" is actually an L2 GPA when TDP is enabled, calling
kvm_mmu_gva_to_gpa_write() to translate cr2 in the non-direct mapped
case (L2 is never direct mapped) will almost always yield UNMAPPED_GVA
and cause reexecute_instruction() to immediately return true.

Way back when, commit 68be0803456b ("KVM: x86: never re-execute
instruction with enabled tdp") changed reexecute_instruction() to
always return false when using TDP under the assumption that KVM would
only get into the emulator for MMIO.  Commit 95b3cf69bdf8 ("KVM: x86:
let reexecute_instruction work for tdp") effectively reverted that
behavior in order to handle the scenario where emulation failed due to
an access from L1 to the shadow page tables for L2, but it didn't
account for the case where emulation failed in L2 with TDP enabled.

All of the above logic also applies to retry_instruction(), added by
commit 1cb3f3ae5a38 ("KVM: x86: retry non-page-table writing
instructions").  An indefinite loop in retry_instruction() should be
impossible as it protects against retrying the same instruction over
and over, but it's still correct to not retry an L2 instruction in
the first place.

[1] This issue was encountered after commit 3a2936dedd20 ("kvm: mmu:
    Don't expose private memslots to L2") changed the page fault path
    to return KVM_PFN_NOSLOT when translating an L2 access to a
    prive memslot.  Returning KVM_PFN_NOSLOT is semantically correct
    when we want to hide a memslot from L2, i.e. there effectively is
    no defined memory region for L2, but it has the unfortunate side
    effect of making KVM think the GFN is a MMIO page, thus triggering
    emulation.  The failure occurred with in-development code that
    deliberately exposed a private memslot to L2, which L2 accessed
    with an instruction that is not emulated by KVM.

Fixes: 95b3cf69bdf8 ("KVM: x86: let reexecute_instruction work for tdp")
Fixes: 1cb3f3ae5a38 ("KVM: x86: retry non-page-table writing instructions")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Cc: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 arch/x86/kvm/x86.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v4 RESEND 1/5] KVM: x86: hyperv: enforce vp_index < KVM_MAX_VCPUS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Hyper-V TLFS (5.0b) states:

> Virtual processors are identified by using an index (VP index). The
> maximum number of virtual processors per partition supported by the
> current implementation of the hypervisor can be obtained through CPUID
> leaf 0x40000005. A virtual processor index must be less than the
> maximum number of virtual processors per partition.

Forbid userspace to set VP_INDEX above KVM_MAX_VCPUS. get_vcpu_by_vpidx()
can now be optimized to bail early when supplied vpidx is >= KVM_MAX_VCPUS.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/kvm/hyperv.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH v2] KVM: leverage change to adjust slots->used_slots in update_memslots()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
update_memslots() is only called by __kvm_set_memory_region(), in which
"change" is calculated and indicates how to adjust slots->used_slots

  * increase by one if it is KVM_MR_CREATE
  * decrease by one if it is KVM_MR_DELETE
  * not change for others

This patch adjusts slots->used_slots in update_memslots() based on "change"
value instead of re-calculate those states again.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
v2: use switch on change instead of encode the adjustment in it.
    add warning in case the status is not correct

---
 virt/kvm/kvm_main.c | 23 ++++++++++++++---------
 1 file changed, 14 insertions(+), 9 deletions(-)

```
#### [PATCH v2] KVM: nVMX: restore host state in nested_vmx_vmexit for VMFail
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A VMEnter that VMFails (as opposed to VMExits) does not touch host
state beyond registers that are explicitly noted in the VMFail path,
e.g. EFLAGS.  Host state does not need to be loaded because VMFail
is only signaled for consistency checks that occur before the CPU
starts to load guest state, i.e. there is no need to restore any
state as nothing has been modified.  But in the case where a VMFail
is detected by hardware and not by KVM (due to deferring consistency
checks to hardware), KVM has already loaded some amount of guest
state.  Luckily, "loaded" only means loaded to KVM's software model,
i.e. vmcs01 has not been modified.  So, unwind our software model to
the pre-VMEntry host state.

Not restoring host state in this VMFail path leads to a variety of
failures because we end up with stale data in vcpu->arch, e.g. CR0,
CR4, EFER, etc... will all be out of sync relative to vmcs01.  Any
significant delta in the stale data is all but guaranteed to crash
L1, e.g. emulation of SMEP, SMAP, UMIP, WP, etc... will be wrong.

An alternative to this "soft" reload would be to load host state from
vmcs12 as if we triggered a VMExit (as opposed to VMFail), but that is
wildly inconsistent with respect to the VMX architecture, e.g. an L1
VMM with separate VMExit and VMFail paths would explode.

Note that this approach does not mean KVM is 100% accurate with
respect to VMX hardware behavior, even at an architectural level
(the exact order of consistency checks is microarchitecture specific).
But 100% emulation accuracy isn't the goal (with this patch), rather
the goal is to be consistent in the information delivered to L1, e.g.
a VMExit should not fall-through VMENTER, and a VMFail should not jump
to HOST_RIP.

This technically reverts commit "5af4157388ad (KVM: nVMX: Fix mmu
context after VMLAUNCH/VMRESUME failure)", but retains the core
aspects of that patch, just in an open coded form due to the need to
pull state from vmcs01 instead of vmcs12.  Restoring host state
resolves a variety of issues introduced by commit "4f350c6dbcb9
(kvm: nVMX: Handle deferred early VMLAUNCH/VMRESUME failure properly)",
which remedied the incorrect behavior of treating VMFail like VMExit
but in doing so neglected to restore arch state that had been modified
prior to attempting nested VMEnter.

A sample failure that occurs due to stale vcpu.arch state is a fault
of some form while emulating an LGDT (due to emulated UMIP) from L1
after a failed VMEntry to L3, in this case when running the KVM unit
test test_tpr_threshold_values in L1.  L0 also hits a WARN in this
case due to a stale arch.cr4.UMIP.

L1:
  BUG: unable to handle kernel paging request at ffffc90000663b9e
  PGD 276512067 P4D 276512067 PUD 276513067 PMD 274efa067 PTE 8000000271de2163
  Oops: 0009 [#1] SMP
  CPU: 5 PID: 12495 Comm: qemu-system-x86 Tainted: G        W         4.18.0-rc2+ #2
  Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS 0.0.0 02/06/2015
  RIP: 0010:native_load_gdt+0x0/0x10

  ...

  Call Trace:
   load_fixmap_gdt+0x22/0x30
   __vmx_load_host_state+0x10e/0x1c0 [kvm_intel]
   vmx_switch_vmcs+0x2d/0x50 [kvm_intel]
   nested_vmx_vmexit+0x222/0x9c0 [kvm_intel]
   vmx_handle_exit+0x246/0x15a0 [kvm_intel]
   kvm_arch_vcpu_ioctl_run+0x850/0x1830 [kvm]
   kvm_vcpu_ioctl+0x3a1/0x5c0 [kvm]
   do_vfs_ioctl+0x9f/0x600
   ksys_ioctl+0x66/0x70
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x4f/0x100
   entry_SYSCALL_64_after_hwframe+0x44/0xa9

L0:
  WARNING: CPU: 2 PID: 3529 at arch/x86/kvm/vmx.c:6618 handle_desc+0x28/0x30 [kvm_intel]
  ...
  CPU: 2 PID: 3529 Comm: qemu-system-x86 Not tainted 4.17.2-coffee+ #76
  Hardware name: Intel Corporation Kabylake Client platform/KBL S
  RIP: 0010:handle_desc+0x28/0x30 [kvm_intel]

  ...

  Call Trace:
   kvm_arch_vcpu_ioctl_run+0x863/0x1840 [kvm]
   kvm_vcpu_ioctl+0x3a1/0x5c0 [kvm]
   do_vfs_ioctl+0x9f/0x5e0
   ksys_ioctl+0x66/0x70
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x49/0xf0
   entry_SYSCALL_64_after_hwframe+0x44/0xa9

Fixes: 5af4157388ad (KVM: nVMX: Fix mmu context after VMLAUNCH/VMRESUME failure)
Fixes: 4f350c6dbcb9 (kvm: nVMX: Handle deferred early VMLAUNCH/VMRESUME failure properly)
Cc: Jim Mattson <jmattson@google.com>
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Wanpeng Li <wanpeng.li@hotmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2: Rebased to latest kvm/nest, addressed a few issues in the commit
    message.


 arch/x86/kvm/vmx.c | 173 +++++++++++++++++++++++++++++++++++++++------
 1 file changed, 153 insertions(+), 20 deletions(-)

```
#### [PATCH] x86/kvm/vmx: Fix GPF on reading vmentry_l1d_flush
##### From: =?iso-2022-jp?b?TUlOT1VSQSBNYWtvdG8gLyAbJEJMJzE6GyhCIBskQj8/GyhC?=

```c
When EPT is not enabled, reading
/sys/module/kvm_intel/parameters/vmentry_l1d_flush causes
general protection fault in vmentry_l1d_flush_get() due to
access beyond the end of the array vmentry_l1d_param[].

Signed-off-by: Minoura Makoto <minoura@valinux.co.jp>
Tested-by: Jack Wang <jinpu.wang@profitbricks.com>
---
 arch/x86/include/asm/vmx.h | 1 +
 arch/x86/kvm/vmx.c         | 4 +++-
 2 files changed, 4 insertions(+), 1 deletion(-)

```
