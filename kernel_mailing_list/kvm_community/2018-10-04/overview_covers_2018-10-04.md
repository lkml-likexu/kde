

#### [Patch v2 0/3] Introduce a new pte_list_remove()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c

rmap_remove() would remove the sptep after locating the correct rmap_head.
While in several cases, the caller has already known the correct rmap_head.

This patch set tries to remove a spte from rmap_head directly.

The original discussion is posted at:

    https://patchwork.kernel.org/patch/10615385/

This version dose some change based on Paolo's comments:

  * rename the original pte_list_remove to __pte_list_remove
  * remove the *if* check on mmu_spte_clear_track_bits in new pte_list_remove
  * move mmu_spte_clear_track_bits before *if* branch in kvm_set_pte_rmapp

Wei Yang (3):
  KVM: x86: rename pte_list_remove to __pte_list_remove
  KVM: x86: a new pte_list_remove including mmu_spte_clear_track_bits
  KVM: x86: extract mmu_spte_clear_track_bits in the loop of
    kvm_set_pte_rmapp

 arch/x86/kvm/mmu.c | 31 +++++++++++++++++++------------
 1 file changed, 19 insertions(+), 12 deletions(-)
```
#### [Patch v3 0/3] Introduce a new pte_list_remove()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c

rmap_remove() would remove the sptep after locating the correct rmap_head.
While in several cases, the caller has already known the correct rmap_head.

This patch set tries to remove a spte from rmap_head directly.

The original discussion is posted at:

    https://patchwork.kernel.org/patch/10615385/

This version dose some change based on Paolo's comments:

  * rename the original pte_list_remove to __pte_list_remove
  * remove the *if* check on mmu_spte_clear_track_bits in new pte_list_remove
  * move mmu_spte_clear_track_bits before *if* branch in kvm_set_pte_rmapp

v3:
  * fix warning from checkpatch.pl in __pte_list_remove

Wei Yang (3):
  KVM: x86: rename pte_list_remove to __pte_list_remove
  KVM: x86: a new pte_list_remove including mmu_spte_clear_track_bits
  KVM: x86: extract mmu_spte_clear_track_bits in the loop of
    kvm_set_pte_rmapp

 arch/x86/kvm/mmu.c | 30 ++++++++++++++++++------------
 1 file changed, 18 insertions(+), 12 deletions(-)
```
#### [PATCH v4 00/32] KVM: PPC: Book3S HV: Nested HV virtualization
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

This patch series is against my kvm-ppc-fixes branch.

Changes in this version since version 3:

- Removed instruction emulation code.

- Validate parameter to H_SET_PARTITION_TABLE hcall.

- Minor changes in response to review comments.

Paul.

 Documentation/virtual/kvm/api.txt                  |   15 +
 arch/powerpc/include/asm/asm-prototypes.h          |   21 +
 arch/powerpc/include/asm/book3s/64/mmu-hash.h      |   12 +
 .../powerpc/include/asm/book3s/64/tlbflush-radix.h |    1 +
 arch/powerpc/include/asm/hvcall.h                  |   41 +
 arch/powerpc/include/asm/kvm_asm.h                 |    4 +-
 arch/powerpc/include/asm/kvm_book3s.h              |   45 +-
 arch/powerpc/include/asm/kvm_book3s_64.h           |  119 +-
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
 arch/powerpc/kvm/book3s_hv.c                       |  842 ++++++++++++-
 arch/powerpc/kvm/book3s_hv_builtin.c               |   92 +-
 arch/powerpc/kvm/book3s_hv_interrupts.S            |   95 +-
 arch/powerpc/kvm/book3s_hv_nested.c                | 1280 ++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_ras.c                   |   10 +
 arch/powerpc/kvm/book3s_hv_rm_xics.c               |   13 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            |  809 +++++++------
 arch/powerpc/kvm/book3s_hv_tm.c                    |    6 +-
 arch/powerpc/kvm/book3s_hv_tm_builtin.c            |    5 +-
 arch/powerpc/kvm/book3s_pr.c                       |    5 +-
 arch/powerpc/kvm/book3s_xics.c                     |   14 +-
 arch/powerpc/kvm/book3s_xive.c                     |   63 +
 arch/powerpc/kvm/book3s_xive_template.c            |    8 -
 arch/powerpc/kvm/bookehv_interrupts.S              |    8 +-
 arch/powerpc/kvm/emulate_loadstore.c               |    1 -
 arch/powerpc/kvm/powerpc.c                         |   12 +
 arch/powerpc/kvm/tm.S                              |  250 ++--
 arch/powerpc/kvm/trace_book3s.h                    |    1 -
 arch/powerpc/mm/tlb-radix.c                        |    9 +
 include/uapi/linux/kvm.h                           |    1 +
 tools/perf/arch/powerpc/util/book3s_hv_exits.h     |    1 -
 43 files changed, 3772 insertions(+), 835 deletions(-)
```
#### [PATCH 00/11 v3] x86: load FPU registers on return to userland
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c

This is a refurbished series originally started by by Rik van Riel. The
goal is load the FPU registers on return to userland and not on every
context switch. By this optimisation we can:
- avoid loading the registers if the task stays in kernel and does
  not return to userland
- make kernel_fpu_begin() cheaper: it only saves the registers on the
  first invocation. The second invocation does not need save them again.

To access the FPU registers in kernel we need:
- disable preemption to avoid that the scheduler switches tasks. By
  doing so it would set TIF_LOAD_FPU and the FPU registers would be not
  valid.
- disable BH because the softirq might use kernel_fpu_begin() and then
  set TIF_LOAD_FPU instead loading the FPU registers on completion.

v1…v3:
v2 was never posted. I followed the idea to completely decouple PKRU
from xstate. This didn't quite work and made a few things complicated. 
One obvious required fixup is copy_fpstate_to_sigframe() where the PKRU
state needs to be fiddled into xstate. This required another
xfeatures_mask so that the sanity checks were performed and
xstate_offsets would be computed. Additionally ptrace also reads/sets
xstate in order to get/set the register and PKRU is one of them. So this
would need some fiddle, too.
In v3 I dropped that decouple idea. I also learned that the wrpkru
instruction is not privileged and so caching it in kernel does not work.
Instead I keep PKRU in xstate area and load it at context switch time
while the remaining registers are deferred (until return to userland).
The offset of PKRU within xstate is enumerated at boot time so why not
use it.

This seems to work with my in-kernel test case and a userland test case
which use xmm registers. The pkey feature was tested in non kvm
accelerated qemu and it seems to work, too.

Sebastian
```
#### [PATCH 0/1] KVM: s390: fixup for vfio-ap
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

One fixup for vfio-ap spotted by smatch.

Christian Borntraeger (1):
  KVM: s390: fix locking for crypto setting error path

 arch/s390/kvm/kvm-s390.c | 16 ++++++++++++----
 1 file changed, 12 insertions(+), 4 deletions(-)
```
