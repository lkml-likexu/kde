#### [PATCH 1/1] KVM: x86: Return updated timer current count register from KVM_GET_LAPIC
##### From: Peter Shier <pshier@google.com>

```c
kvm_vcpu_ioctl_get_lapic (implements KVM_GET_LAPIC ioctl) does a bulk copy
of the LAPIC registers but must take into account that the one-shot and
periodic timer current count register is computed upon reads and is not
present in register state. When restoring LAPIC state (e.g. after
migration), restart timers from their their current count values at time of
save.

Note: When a one-shot timer expires, the code in arch/x86/kvm/lapic.c does
not zero the value of the LAPIC initial count register (emulating HW
behavior). If no other timer is run and pending prior to a subsequent
KVM_GET_LAPIC call, the returned register set will include the expired
one-shot initial count. On a subsequent KVM_SET_LAPIC call the code will
see a non-zero initial count and start a new one-shot timer using the
expired timer's count. This is a prior existing bug and will be addressed
in a separate patch. Thanks to jmattson@google.com for this find.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/lapic.c | 64 +++++++++++++++++++++++++++++++++++---------
 arch/x86/kvm/lapic.h |  7 ++++-
 2 files changed, 58 insertions(+), 13 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-4.20-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-4.20-1 tag to get a PPC KVM
update for 4.20.  There is one big new feature here, which is nested
virtualization support for radix guests on POWER9, plus a few other
fixes and improvements.

A lot of the commits here are also going to be merged in the powerpc
tree via the topic/ppc-kvm branch, in order to reduce conflicts
between the powerpc tree and the kvm tree.

Stephen Rothwell noted that there is a conflict between my
kvm-ppc-next tree and the kvm-arm tree, in that we have both allocated
the next free capability number (160).  It would be nice to get a
stable allocation for the new capability that I need (one which
reports/enables nested virtualization support for the HV KVM module)
so that the necessary QEMU patches can be submitted.

Thanks,
Paul.

The following changes since commit dd5bd0a65ff6f22a32b35ca3fa1bcf7a6bc7104f:

  Merge tag 'kvm-s390-next-4.20-1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD (2018-10-04 17:12:45 +0200)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-4.20-1

for you to fetch changes up to 901f8c3f6feb0225c14b3bc6237850fb921d2f2d:

  KVM: PPC: Book3S HV: Add NO_HASH flag to GET_SMMU_INFO ioctl result (2018-10-09 16:14:54 +1100)

----------------------------------------------------------------
PPC KVM update for 4.20.

The major new feature here is nested HV KVM support.  This allows the
HV KVM module to load inside a radix guest on POWER9 and run radix
guests underneath it.  These nested guests can run in supervisor mode
and don't require any additional instructions to be emulated, unlike
with PR KVM, and so performance is much better than with PR KVM, and
is very close to the performance of a non-nested guest.  A nested
hypervisor (a guest with nested guests) can be migrated to another
host and will bring all its nested guests along with it.  A nested
guest can also itself run guests, and so on down to any desired depth
of nesting.

Apart from that there are a series of updates for IOMMU handling from
Alexey Kardashevskiy, a "one VM per core" mode for HV KVM for
security-paranoid applications, and a small fix for PR KVM.

----------------------------------------------------------------
Alexey Kardashevskiy (5):
      KVM: PPC: Validate all tces before updating tables
      KVM: PPC: Inform the userspace about TCE update failures
      KVM: PPC: Validate TCEs against preregistered memory page sizes
      KVM: PPC: Propagate errors to the guest when failed instead of ignoring
      KVM: PPC: Remove redundand permission bits removal

Cameron Kaiser (1):
      KVM: PPC: Book3S PR: Exiting split hack mode needs to fixup both PC and LR

Michael Ellerman (1):
      Merge branch 'kvm-ppc-fixes' of paulus/powerpc into topic/ppc-kvm

Paul Mackerras (26):
      KVM: PPC: Book3S HV: Provide mode where all vCPUs on a core must be the same VM
      powerpc: Turn off CPU_FTR_P9_TM_HV_ASSIST in non-hypervisor mode
      KVM: PPC: Book3S: Simplify external interrupt handling
      KVM: PPC: Book3S HV: Remove left-over code in XICS-on-XIVE emulation
      KVM: PPC: Book3S HV: Move interrupt delivery on guest entry to C code
      KVM: PPC: Book3S HV: Extract PMU save/restore operations as C-callable functions
      KVM: PPC: Book3S HV: Simplify real-mode interrupt handling
      KVM: PPC: Book3S: Rework TM save/restore code and make it C-callable
      KVM: PPC: Book3S HV: Call kvmppc_handle_exit_hv() with vcore unlocked
      KVM: PPC: Book3S HV: Streamlined guest entry/exit path on P9 for radix guests
      KVM: PPC: Book3S HV: Handle hypervisor instruction faults better
      KVM: PPC: Book3S HV: Add a debugfs file to dump radix mappings
      KVM: PPC: Use ccr field in pt_regs struct embedded in vcpu struct
      KVM: PPC: Book3S HV: Use kvmppc_unmap_pte() in kvm_unmap_radix()
      KVM: PPC: Book3S HV: Framework and hcall stubs for nested virtualization
      KVM: PPC: Book3S HV: Nested guest entry via hypercall
      KVM: PPC: Book3S HV: Use XICS hypercalls when running as a nested hypervisor
      KVM: PPC: Book3S HV: Handle hypercalls correctly when nested
      KVM: PPC: Book3S HV: Use hypercalls for TLB invalidation when nested
      KVM: PPC: Book3S HV: Don't access HFSCR, LPIDR or LPCR when running nested
      KVM: PPC: Book3S HV: Add one-reg interface to virtual PTCR register
      KVM: PPC: Book3S HV: Allow HV module to load without hypervisor mode
      KVM: PPC: Book3S HV: Add nested shadow page tables to debugfs
      Merge remote-tracking branch 'remotes/powerpc/topic/ppc-kvm' into kvm-ppc-next
      KVM: PPC: Book3S HV: Add a VM capability to enable nested virtualization
      KVM: PPC: Book3S HV: Add NO_HASH flag to GET_SMMU_INFO ioctl result

Suraj Jitindar Singh (9):
      KVM: PPC: Book3S HV: Clear partition table entry on vm teardown
      KVM: PPC: Book3S HV: Make kvmppc_mmu_radix_xlate process/partition table agnostic
      KVM: PPC: Book3S HV: Refactor radix page fault handler
      KVM: PPC: Book3S HV: Handle page fault for a nested guest
      KVM: PPC: Book3S HV: Introduce rmap to track nested guest mappings
      KVM: PPC: Book3S HV: Implement H_TLB_INVALIDATE hcall
      KVM: PPC: Book3S HV: Invalidate TLB when nested vcpu moves physical cpu
      KVM: PPC: Book3S HV: Sanitise hv_regs on nested guest entry
      KVM: PPC: Book3S HV: Handle differing endianness for H_ENTER_NESTED

 Documentation/virtual/kvm/api.txt                  |   19 +
 arch/powerpc/include/asm/asm-prototypes.h          |   21 +
 arch/powerpc/include/asm/book3s/64/mmu-hash.h      |   12 +
 .../powerpc/include/asm/book3s/64/tlbflush-radix.h |    1 +
 arch/powerpc/include/asm/hvcall.h                  |   41 +
 arch/powerpc/include/asm/kvm_asm.h                 |    4 +-
 arch/powerpc/include/asm/kvm_book3s.h              |   45 +-
 arch/powerpc/include/asm/kvm_book3s_64.h           |  118 +-
 arch/powerpc/include/asm/kvm_book3s_asm.h          |    3 +
 arch/powerpc/include/asm/kvm_booke.h               |    4 +-
 arch/powerpc/include/asm/kvm_host.h                |   16 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |    8 +-
 arch/powerpc/include/asm/ppc-opcode.h              |    1 +
 arch/powerpc/include/asm/reg.h                     |    2 +
 arch/powerpc/include/uapi/asm/kvm.h                |    1 +
 arch/powerpc/kernel/asm-offsets.c                  |    5 +-
 arch/powerpc/kernel/cpu_setup_power.S              |    4 +-
 arch/powerpc/kvm/Makefile                          |    3 +-
 arch/powerpc/kvm/book3s.c                          |   46 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |    7 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |  718 ++++++++---
 arch/powerpc/kvm/book3s_64_vio.c                   |   89 +-
 arch/powerpc/kvm/book3s_64_vio_hv.c                |   81 +-
 arch/powerpc/kvm/book3s_emulate.c                  |   13 +-
 arch/powerpc/kvm/book3s_hv.c                       |  864 ++++++++++++-
 arch/powerpc/kvm/book3s_hv_builtin.c               |   92 +-
 arch/powerpc/kvm/book3s_hv_interrupts.S            |   95 +-
 arch/powerpc/kvm/book3s_hv_nested.c                | 1291 ++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_ras.c                   |   10 +
 arch/powerpc/kvm/book3s_hv_rm_xics.c               |   13 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            |  823 +++++++------
 arch/powerpc/kvm/book3s_hv_tm.c                    |    6 +-
 arch/powerpc/kvm/book3s_hv_tm_builtin.c            |    5 +-
 arch/powerpc/kvm/book3s_pr.c                       |    5 +-
 arch/powerpc/kvm/book3s_xics.c                     |   14 +-
 arch/powerpc/kvm/book3s_xive.c                     |   63 +
 arch/powerpc/kvm/book3s_xive_template.c            |    8 -
 arch/powerpc/kvm/bookehv_interrupts.S              |    8 +-
 arch/powerpc/kvm/emulate_loadstore.c               |    1 -
 arch/powerpc/kvm/powerpc.c                         |   15 +-
 arch/powerpc/kvm/tm.S                              |  250 ++--
 arch/powerpc/kvm/trace_book3s.h                    |    1 -
 arch/powerpc/mm/tlb-radix.c                        |    9 +
 include/uapi/linux/kvm.h                           |    2 +
 tools/perf/arch/powerpc/util/book3s_hv_exits.h     |    1 -
 45 files changed, 3933 insertions(+), 905 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_hv_nested.c
```
#### [PATCH v2 1/2] KVM: x86: hyperv: fix 'tlb_lush' typo
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Regardless of whether your TLB is lush or not it still needs flushing.

Reported-by: Roman Kagan <rkagan@virtuozzo.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/hyperv.c           | 6 +++---
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM/x86: Fix invvpid and invept register operand size in 64-bit mode
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Register operand size of invvpid and invept instruction in 64-bit mode
has always 64 bits. Adjust inline function argument type to reflect
correct size.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
