

#### [PATCH v2 0/2] rename function name and enable 32bit vcpu events
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c

Rename the kvm_arch_dev_ioctl_check_extension() to 
kvm_arch_vm_ioctl_check_extension, because the name
is not reasonable; 

Enable the 32 bit vcpu events support.

change since v1:
1. Update patch commit messages.


Dongjiu Geng (2):
  arm/arm64: KVM: rename function kvm_arch_dev_ioctl_check_extension()
  arm/arm64: KVM: enable 32 bits kvm vcpu events support

 arch/arm/include/asm/kvm_host.h   | 2 +-
 arch/arm64/include/asm/kvm_host.h | 2 +-
 arch/arm64/kvm/reset.c            | 5 ++---
 virt/kvm/arm/arm.c                | 3 ++-
 4 files changed, 6 insertions(+), 6 deletions(-)
```
#### [PATCH v5 00/33] KVM: PPC: Book3S HV: Nested HV virtualization
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

This patch series implements nested virtualization in the KVM-HV
module for radix guests on POWER9 systems.  Unlike PR KVM, nested
guests are able to run in supervisor mode, meaning that performance is
much better than with PR KVM, and is very close to the performance of
a non-nested guests for most things.

The way this works is that each nested guest is also a guest of the
real hypervisor, also known as the level 0 or L0 hypervisor, which
runs in the CPU's hypervisor mode.  Its guests are at level 1, and
when a L1 system wants to run a nested guest, it performs hypercalls
to L0 to set up a virtual partition table in its (L1's) memory and to
enter the L2 guest.  The L0 hypervisor maintains a shadow
partition-scoped page table for the L2 guest and demand-faults entries
into it by translating the L1 real addresses in the partition-scoped
page table in L1 memory into L0 real addresses and puts them in the
shadow partition-scoped page table for L2.

Essentially what this is doing is providing L1 with the ability to do
(some) hypervisor functions using paravirtualization; optionally,
TLB invalidations can be done through emulation of the tlbie
instruction rather than a hypercall.

Along the way, this implements a new guest entry/exit path for radix
guests on POWER9 systems which is written almost entirely in C and
does not do any of the inter-thread coordination that the existing
entry/exit path does.  It is only used for radix guests and when
indep_threads_mode=Y (the default).

The limitations of this scheme are:

- Host and all nested hypervisors and their guests must be in radix
  mode.

- Nested hypervisors cannot use indep_threads_mode=N.

- If the host (i.e. the L0 hypervisor) has indep_threads_mode=N then
  only one nested vcpu can be run on any core at any given time; the
  secondary threads will do nothing.

- A nested hypervisor can't use a smaller page size than the base page
  size of the hypervisor(s) above it.

- A nested hypervisor is limited to having at most 1023 guests below
  it, each of which can have at most NR_CPUS virtual CPUs (and the
  virtual CPU ids have to be < NR_CPUS as well).

This patch series is against the kvm tree's next branch.

Changes in this version since version 4:

- Added KVM_PPC_NO_HASH to flags field of struct kvm_ppc_smmu_info rather
  than disabling the KVM_PPC_GET_SMMU_INFO ioctl entirely.

- Make sure the hypercalls for controlling nested guests will fail if
  the guest is in HPT mode.

- Made the KVM_CAP_PPC_MMU_HASH_V3 capability report false in a nested
  hypervisor.

- Fixed a bug causing HPT guests to fail to execute real-mode
  hypercalls correctly.

- Fix crashes seen on VM exit or when switching from HPT to radix,
  due to leftover rmap values.

- Removed enable/disable flag from KVM_ENABLE_CAP on the
  KVM_CAP_PPC_NESTED_HV capability; it always enables.

- Fixed a bug causing memory corruption on nested guest startup,
  and a bug where we were never clearing bits in the cpu_in_guest
  cpumask.

- Simplified some code in kvmhv_run_single_vcpu.

Paul.

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
 arch/powerpc/include/asm/kvm_ppc.h                 |    4 +
 arch/powerpc/include/asm/ppc-opcode.h              |    1 +
 arch/powerpc/include/asm/reg.h                     |    2 +
 arch/powerpc/include/uapi/asm/kvm.h                |    1 +
 arch/powerpc/kernel/asm-offsets.c                  |    5 +-
 arch/powerpc/kernel/cpu_setup_power.S              |    4 +-
 arch/powerpc/kvm/Makefile                          |    3 +-
 arch/powerpc/kvm/book3s.c                          |   43 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |    7 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |  718 ++++++++---
 arch/powerpc/kvm/book3s_emulate.c                  |   13 +-
 arch/powerpc/kvm/book3s_hv.c                       |  852 ++++++++++++-
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
 43 files changed, 3806 insertions(+), 843 deletions(-)
```
#### [PATCH 0/2] KVM: x86: hyperv: PV IPI follow-up
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

This is a follow-up series to the previously merged "KVM: x86: hyperv:
PV IPI support for Windows guests". A couple of issues and suggestions
on how to make things better were expressed by Roman during v6 review.

Vitaly Kuznetsov (2):
  KVM: x86: hyperv: fix 'tlb_lush' typo
  KVM: x86: hyperv: optimize sparse VP set processing

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/hyperv.c           | 161 ++++++++++++--------------------
 2 files changed, 63 insertions(+), 100 deletions(-)
```
#### [PATCH v4 0/9] x86/kvm/nVMX: optimize MMU switch between L1 and L2
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Change since v3 [Sean Christopherson]:
- Add Reviewed-by tags (thanks!).
- Drop stale role initializer in kvm_calc_shadow_ept_root_page_role
  (interim change in PATCH4, the end result is the same).
- Use '!!' instead of '!= 0' for kvm_read_cr4_bits() readings.

Also, rebased to the current kvm/queue.

Original description:

Currently, when we switch from L1 to L2 (VMX) we do the following:
- Re-initialize L1 MMU as shadow EPT MMU (nested_ept_init_mmu_context())
- Re-initialize 'nested' MMU (nested_vmx_load_cr3() -> init_kvm_nested_mmu())

When we switch back we do:
- Re-initialize L1 MMU (nested_vmx_load_cr3() -> init_kvm_tdp_mmu())

This seems to be sub-optimal. Initializing MMU is expensive (thanks to
update_permission_bitmask(), update_pkru_bitmask(),..) Try solving the
issue by splitting L1-normal and L1-nested MMUs and checking if MMU reset
is really needed. This spares us about 1000 cpu cycles on nested vmexit.

Brief look at SVM makes me think it can be optimized the exact same way,
I'll do this in a separate series.

Paolo Bonzini (1):
  x86/kvm/mmu: get rid of redundant kvm_mmu_setup()

Vitaly Kuznetsov (8):
  x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
  x86/kvm/mmu.c: set get_pdptr hook in kvm_init_shadow_ept_mmu()
  x86/kvm/mmu.c: add kvm_mmu parameter to kvm_mmu_free_roots()
  x86/kvm/mmu: introduce guest_mmu
  x86/kvm/mmu: make space for source data caching in struct kvm_mmu
  x86/kvm/nVMX: introduce source data cache for
    kvm_init_shadow_ept_mmu()
  x86/kvm/mmu: check if tdp/shadow MMU reconfiguration is needed
  x86/kvm/mmu: check if MMU reconfiguration is needed in
    init_kvm_nested_mmu()

 arch/x86/include/asm/kvm_host.h |  44 +++-
 arch/x86/kvm/mmu.c              | 357 +++++++++++++++++++-------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +-
 arch/x86/kvm/paging_tmpl.h      |  15 +-
 arch/x86/kvm/svm.c              |  14 +-
 arch/x86/kvm/vmx.c              |  55 +++--
 arch/x86/kvm/x86.c              |  22 +-
 8 files changed, 322 insertions(+), 205 deletions(-)
```
#### [PATCH v2 0/4] KVM: nVMX: Various VPID fixes
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to fix various issues in nested VPID emulation.

The 1st patch fixes a bug that INVEPT was executed on L1<->L2
transitions to flush TLB but with the wrong EPTP because it hasn't been
loaded yet with the destination EPTP. The patch handles this issue
easily by just delaying vmx_flush_tlb() to be called after EPTP has been
set to destination by using KVM_REQ_TLB_FLUSH.

The 2nd patch fixes a bug in L0 emulation of INVVPID which can
use a wrong VPID02 in case KVM failed to allocate vmx->nested.vpid02.

The 3rd patch fixes a critical issue of invalidating wrong mappings from
TLB when performing VPID02 related invalidations. The issue is that these
invalidations mistakenly invalidates combined and guest-physical mappings
tagged by EPTP01 instead of invalidating linear and combined mappings
tagged by VPID02.

The 4rd patch optimizes L1<->L2 transitions by avoiding unnecessary TLB flush
in case L1 use both VPID and EPT and thus L0 can separate TLB entries of L1 and L2
by EPTP tag.

Regards,
-Liran
```
