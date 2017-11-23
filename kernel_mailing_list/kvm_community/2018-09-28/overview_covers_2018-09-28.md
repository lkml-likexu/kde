

#### [kvm-unit-tests PATCH 0/4] Compile with -Wmissing-prototypes and
##### From: Thomas Huth <thuth@redhat.com>

```c

Compiling with -Wmissing-prototypes and -Wstrict-prototypes should help
us to make sure that implementations always match the prototypes in
the headers, so we hopefully can avoid some bugs in the future this way.

Thomas Huth (4):
  x86: Declare local functions as "static" and specify argument types
  x86: Add missing prototypes and mark more local functions as static
  s390x: Make code compilable with -Wmissing-prototypes and
    -Wstrict-prototypes
  Makefile: Compile with -Wmissing-prototypes and -Wstrict-prototypes

 Makefile              |  1 +
 lib/s390x/asm/float.h |  2 +-
 lib/s390x/mmu.c       |  1 +
 lib/x86/desc.c        |  5 +++++
 lib/x86/setup.c       |  4 +++-
 x86/cmpxchg8b.c       |  2 +-
 x86/eventinj.c        |  6 ++++--
 x86/kvmclock.c        | 11 ++++++-----
 x86/pku.c             |  3 ++-
 x86/smap.c            |  1 +
 x86/taskswitch2.c     | 12 +++++++-----
 x86/tsc.c             |  4 ++--
 x86/umip.c            |  6 +++---
 x86/vmx.c             |  6 +++---
 14 files changed, 40 insertions(+), 24 deletions(-)
```
#### [PATCH v2 00/33] KVM: PPC: Book3S HV: Nested HV virtualization
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
(some) hypervisor functions using a mix of instruction emulation and
paravirtualization.

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
  it, each of which can have at most NR_CPUS virtual CPUs.

Changes in this version since version 1 (the RFC series):

- Rebased onto the kvm tree master branch.

- Added hypercall to do TLB invalidations and code to use it.

- Implemented a different method to ensure the build can succeed when
  CONFIG_PPC_PSERIES=n.

- Fixed bugs relating to interrupt and doorbell handling.

- Reimplemented the rmap code to use much less memory.

- Changed some names, comments and code based on review feedback.

- Handle the case when L0 and L1 are of different endianness.

- More santization of the register values provided by L1.

- Fixed bugs that prevented nested guests from successfully running
  guests under them (double nesting).

- Fixed a bug relating to the max_nested_lpid computation.

- Fixed a bug causing continual HDSI interrupts when a page of a page
  table or process table got paged out.

Paul.

 Documentation/virtual/kvm/api.txt                  |   15 +
 arch/powerpc/include/asm/asm-prototypes.h          |   21 +
 arch/powerpc/include/asm/book3s/64/mmu-hash.h      |   12 +
 .../powerpc/include/asm/book3s/64/tlbflush-radix.h |    1 +
 arch/powerpc/include/asm/hvcall.h                  |   41 +
 arch/powerpc/include/asm/kvm_asm.h                 |    4 +-
 arch/powerpc/include/asm/kvm_book3s.h              |   49 +-
 arch/powerpc/include/asm/kvm_book3s_64.h           |  119 +-
 arch/powerpc/include/asm/kvm_book3s_asm.h          |    3 +
 arch/powerpc/include/asm/kvm_booke.h               |    4 +-
 arch/powerpc/include/asm/kvm_host.h                |   16 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |    4 +
 arch/powerpc/include/asm/ppc-opcode.h              |    1 +
 arch/powerpc/include/asm/reg.h                     |    3 +
 arch/powerpc/include/uapi/asm/kvm.h                |    1 +
 arch/powerpc/kernel/asm-offsets.c                  |    5 +-
 arch/powerpc/kernel/cpu_setup_power.S              |    4 +-
 arch/powerpc/kvm/Makefile                          |    3 +-
 arch/powerpc/kvm/book3s.c                          |   43 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |    7 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |  720 ++++++++---
 arch/powerpc/kvm/book3s_emulate.c                  |   13 +-
 arch/powerpc/kvm/book3s_hv.c                       |  923 ++++++++++++--
 arch/powerpc/kvm/book3s_hv_builtin.c               |   92 +-
 arch/powerpc/kvm/book3s_hv_interrupts.S            |   95 +-
 arch/powerpc/kvm/book3s_hv_nested.c                | 1318 ++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_ras.c                   |   10 +
 arch/powerpc/kvm/book3s_hv_rm_xics.c               |   13 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            |  809 ++++++------
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
 43 files changed, 3866 insertions(+), 867 deletions(-)
```
