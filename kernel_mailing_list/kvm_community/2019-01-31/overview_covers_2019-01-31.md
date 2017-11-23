

#### [PATCH v7 00/15] KVM: s390: make use of the GIB
##### From: Michael Mueller <mimu@linux.ibm.com>

```c

The Guest Information Area (GIB) and its mechanics is part of
the AIV facility. It provides hardware support to process
Adapter Interruptions (AI) for pagable storage mode guests. 

Whenever a guest cannot process an AI because none of its
vcpus is running in SIE context, a GIB alert interruption is
sent to and handled by the host program to dispatch a vcpu of
the respective guest.

Eventually, the AI is handled by the guest.

v6->v7:
  patches 1/15 to 7/15
     prepare the existing Interruption and GISA code for
     the introduction of the GIB code. (kept from v6)
  patches 8/15 to 10/15
     kept from v6.
  patch 11/15
     kvm_s390_gisc_register() now uses a single conditional
     branch to extend IAM restore value and to set the IAM
     in GISA. 
  patch 12/15
     kvm_s390_clear_gisa() now refactored in its own patch.
  patch 13/15
     I'm keeping the 50 usec timer expiration as the statistic
     data shows a single timer restart only.
       gisa_get_ipm_or_restore_iam() now called when entering
     kvm_s390_handle_wait(). That saves some of the timer
     restarts.
       Some modifications in kvm_s390_gisa_destroy()
  patch 14/15
     kept from v6.
  patch 15/15
     additional test on non NULL gisa origin in pending_irqs()

v5->v6:
  Futher significant change was introduced with this version
  now:

  a) During the alert list processing now a hrtimer is
     started to kick an idle vcpu with open I/O interrupt
     mask. It then is restarted to monitor the interruption
     consumption and when the IPM is clean (no relevant
     ISCs pending anymore) atomically restores the IAM
     and don't restarts or if new ISCs arrive kick other
     idle vcpus.

  patches 1/13 to 7/13:
     prepare the existing Interruption and GISA code for
     the introduction of the GIB code.
  patches 8/13 to 10/13:
     kept from v5.
  patch 11/13:
     Some comments added.
  patch 12/13:
     Significatly changed due to the hrtimer control.
  patch 13/13:
     Basically kept from v5 except for a slight reordering
     that shortens the patch.

v4->v5:
  Between these two versions some significant change was
  introduced:

  a) During IPM look-up, the IAM gets atomically restored
     if the IPM is clean. (The main strategy is: As soon no
     airqs are pending anymore, get prepared for new ones
     arriving).

  b) Kick a set of vcpus in WAIT state, that will be able
     to handle all ISCs in IPM if possible. The main loop
     that processes the GIB alert list is unchanged.

  patches 1/15 to 6/15:
     prepare the existing Interruption and GISA code for
     the introduction of the GIB code.
  patches 7/15 to 9/15:
     kept from v4. 
  patch 10/15:
     restores the IAM in get_ipm() when clean on request
     with additional parameter irq_flags
  patch 12/15:
     modifies kvm_s390_deliver_pending_interrupts() such
     that the IAM is not restored during the deliverable_irqs()
     test as we are about to enter the SIE. Restoring the
     IAM would trigger the alert mechanism unnecessarily
     on SIE entry.
  patch 13/15:
     process_gib_alert_list() now triggers a minimal set
     of idle vcpus capable the handle all pending ISCs.
  patch 14/15:
     the wiring is logical similar to v4 but uses different
     routines
  patch 15/15: 
     kept from v4. 

v3->v4:
  The central change of v4 is that the metric "vcpus_in_sie"
  has been dropped. A least agressive IAM restore strategy
  is being followed now. The consequence is that potentially
  more GAL interruptions are to be handled by the host program.
  The assuption as made that as soon the first vcpu is trying
  to go into wait state, this could be the last vcpu being
  open for I/O interruptions. Thus, to not loose the initiative
  to deliver I/O interruptions as soon as possible, the IAM
  is restored. Adding better heuristics can be done in future.

  I expect this to be the last version of the series.
 
  patch 01/12: Kernel msg now printed when FLIC fails
               to register during arch inititialization.
  patch 03/12: Commit message slightly changed with the
  	       hint that gib initialization is called
	       by last patch of this serias.
  patch 09/12: IAM now restored during kvm_s390_handle_wait()
  patch 10/12: gib destroy case now handled upon unsuccessful
  	       arch inititialization.

All other patches are unchanged.

v2->v3:
  patch 01/12: Fixes a resource dealocation issue upon
  	       unsuccessful exit from kvm_arch_init().
	       It is relevant for patch 11/12 as well. 
  patch 08/12: The function process_gib_alert_list() has
               been rewritten to reduce the number of GAL
	       interruptions on the host for many guest
	       scenarios.
  patch 10/12: The IAM is now never cleared before SIE entry.
               It will be cleared by millicode as soon the
	       first guest interruption is made pending and
	       not directly processed in SIE. The IAM gets
	       restored as soon a vm is idle, i.e. no vcpu
	       of that guest is in SIE context anymore.
  patch 11/12: now integrates with new patch 01/12
  patch 12/12: This patch is just experimental and shall not
               be part of the final series.

The first patch of series v2: "leave AIs in IPM of GISA
during vcpu_pre_run()" has been dropped.

All other patches are unchanged.

v1->v2:
  patch 01/12: New patch. Tt can go also standalone without the
  	       rest of the GIB series presented here but is a
	       requirement 
  patch 03/12: kvm_s390_gib_init() now has a return code
  patch 06/12: unlink_gib_alert_list() now uses cmpxchg() instead
    	       of atomic_xchg()
  patch 08/12: New patch. Foctors out __find_vcpu_for_floating_irq()
  patch 09/12: process_gib_alert_list() has been simplified
               the GISA clear/destroy cases have been removed
  patch 11/12: kvm_s390_gisa_clear/destroy() now clear the IAM
               and process the alert list directly
	       The IAM now gets restored in vcpu_post_run() only if
	       the GISA is not in alert list
  patch 12/12: during kvm_arch_init() now the return code of
    	       kvm_s390_gib_init() is honored.

All other patches are unchanged.

Michael Mueller (15):
  KVM: s390: drop obsolete else path
  KVM: s390: make bitmap declaration consistent
  KVM: s390: move bitmap idle_mask into arch struct top level
  KVM: s390: coding style kvm_s390_gisa_init/clear()
  KVM: s390: use pending_irqs_no_gisa() where appropriate
  KVM: s390: remove kvm_s390_ from gisa static inline functions
  KVM: s390: introduce struct kvm_s390_gisa_interrupt
  s390/cio: add function chsc_sgib()
  KVM: s390: add the GIB and its related life-cyle functions
  KVM: s390: add kvm reference to struct sie_page2
  KVM: s390: add functions to (un)register GISC with GISA
  KVM: s390: kvm_s390_gisa_clear() now clears the IPM only
  KVM: s390: add gib_alert_irq_handler()
  KVM: s390: start using the GIB
  KVM: s390: fix possible null pointer dereference in pending_irqs()

 arch/s390/include/asm/cio.h      |   1 +
 arch/s390/include/asm/irq.h      |   1 +
 arch/s390/include/asm/isc.h      |   1 +
 arch/s390/include/asm/kvm_host.h |  36 +++-
 arch/s390/kernel/irq.c           |   1 +
 arch/s390/kvm/interrupt.c        | 431 +++++++++++++++++++++++++++++++++++----
 arch/s390/kvm/kvm-s390.c         |  13 +-
 arch/s390/kvm/kvm-s390.h         |   4 +-
 drivers/s390/cio/chsc.c          |  37 ++++
 drivers/s390/cio/chsc.h          |   1 +
 10 files changed, 480 insertions(+), 46 deletions(-)
```
#### [PATCH v2 0/3] KVM: Unify mmu_memory_cache functionality across
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c

We currently have duplicated functionality for the mmu_memory_cache used
to pre-allocate memory for the page table manipulation code which cannot
allocate memory while holding spinlocks.  This functionality is
duplicated across x86, arm/arm64, and mips.

There were recently a debate of modifying the arm code to be more in
line with the x86 code and some discussions around changing the page
flags used for allocation.  This series should make it easier to take a
uniform approach across architectures.

While there's not a huge amount of code sharing, we come out with a net
gain.

Only tested on arm/arm64, and only compile-tested on x86 and mips.

Changes since v1:
 - Split out rename from initial x86 patch to have separate patches to
   move the logic to common code and to rename.
 - Introduce KVM_ARCH_WANT_MMU_MEMCACHE to avoid compile breakage on
   architectures that don't use this functionality.
 - Rename KVM_NR_MEM_OBJS to KVM_MMU_NR_MEMCACHE_OBJS
---

Christoffer Dall (4):
  KVM: x86: Move mmu_memory_cache functions to common code
  KVM: x86: Rename mmu_memory_cache to kvm_mmu_memcache
  KVM: arm/arm64: Move to common kvm_mmu_memcache infrastructure
  KVM: mips: Move to common kvm_mmu_memcache infrastructure

 arch/arm/include/asm/kvm_host.h      | 13 +---
 arch/arm/include/asm/kvm_mmu.h       |  2 +-
 arch/arm/include/asm/kvm_types.h     | 12 ++++
 arch/arm64/include/asm/kvm_host.h    | 13 +---
 arch/arm64/include/asm/kvm_mmu.h     |  2 +-
 arch/arm64/include/asm/kvm_types.h   | 13 ++++
 arch/mips/include/asm/kvm_host.h     | 15 +----
 arch/mips/include/asm/kvm_types.h    | 12 ++++
 arch/mips/kvm/mips.c                 |  2 +-
 arch/mips/kvm/mmu.c                  | 54 +++-------------
 arch/powerpc/include/asm/kvm_types.h |  5 ++
 arch/s390/include/asm/kvm_types.h    |  5 ++
 arch/x86/include/asm/kvm_host.h      | 17 +----
 arch/x86/include/asm/kvm_types.h     | 12 ++++
 arch/x86/kvm/mmu.c                   | 97 ++++++----------------------
 arch/x86/kvm/paging_tmpl.h           |  4 +-
 include/linux/kvm_host.h             | 11 ++++
 include/linux/kvm_types.h            | 13 ++++
 virt/kvm/arm/arm.c                   |  2 +-
 virt/kvm/arm/mmu.c                   | 68 +++++--------------
 virt/kvm/kvm_main.c                  | 60 +++++++++++++++++
 21 files changed, 202 insertions(+), 230 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_types.h
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
```
#### [RFC PATCH 0/4] Restore change_pte optimization to its former glory
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

This patchset is on top of my patchset to add context information to
mmu notifier [1] you can find a branch with everything [2]. I have not
tested it but i wanted to get the discussion started. I believe it is
correct but i am not sure what kind of kvm test i can run to exercise
this.

The idea is that since kvm will invalidate the secondary MMUs within
invalidate_range callback then the change_pte() optimization is lost.
With this patchset everytime core mm is using set_pte_at_notify() and
thus change_pte() get calls then we can ignore the invalidate_range
callback altogether and only rely on change_pte callback.

Note that this is only valid when either going from a read and write
pte to a read only pte with same pfn, or from a read only pte to a
read and write pte with different pfn. The other side of the story
is that the primary mmu pte is clear with ptep_clear_flush_notify
before the call to change_pte.

Also with the mmu notifier context information [1] you can further
optimize other cases like mprotect or write protect when forking. You
can use the new context information to infer that the invalidation is
for read only update of the primary mmu and update the secondary mmu
accordingly instead of clearing it and forcing fault even for read
access. I do not know if that is an optimization that would bear any
fruit for kvm. It does help for device driver. You can also optimize
the soft dirty update.

Cheers,
Jérôme


[1] https://lore.kernel.org/linux-fsdevel/20190123222315.1122-1-jglisse@redhat.com/T/#m69e8f589240e18acbf196a1c8aa1d6fc97bd3565
[2] https://cgit.freedesktop.org/~glisse/linux/log/?h=kvm-restore-change_pte

Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@kernel.org>
Cc: Alexander Shishkin <alexander.shishkin@linux.intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Namhyung Kim <namhyung@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: kvm@vger.kernel.org

Jérôme Glisse (4):
  uprobes: use set_pte_at() not set_pte_at_notify()
  mm/mmu_notifier: use unsigned for event field in range struct
  mm/mmu_notifier: set MMU_NOTIFIER_USE_CHANGE_PTE flag where
    appropriate
  kvm/mmu_notifier: re-enable the change_pte() optimization.

 include/linux/mmu_notifier.h | 21 +++++++++++++++++++--
 kernel/events/uprobes.c      |  3 +--
 mm/ksm.c                     |  6 ++++--
 mm/memory.c                  |  3 ++-
 virt/kvm/kvm_main.c          | 16 ++++++++++++++++
 5 files changed, 42 insertions(+), 7 deletions(-)
```
#### [PATCH v6 00/14] KVM/X86: Introduce a new guest mapping interface
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c

Guest memory can either be directly managed by the kernel (i.e. have a "struct
page") or they can simply live outside kernel control (i.e. do not have a
"struct page"). KVM mostly support these two modes, except in a few places
where the code seems to assume that guest memory must have a "struct page".

This patchset introduces a new mapping interface to map guest memory into host
kernel memory which also supports PFN-based memory (i.e. memory without 'struct
page'). It also converts all offending code to this interface or simply
read/write directly from guest memory. Patch 2 is additionally fixing an
incorrect page release and marking the page as dirty (i.e. as a side-effect of
using the helper function to write).

As far as I can see all offending code is now fixed except the APIC-access page
which I will handle in a seperate series along with dropping
kvm_vcpu_gfn_to_page and kvm_vcpu_gpa_to_page from the internal KVM API.

The current implementation of the new API uses memremap to map memory that does
not have a "struct page". This proves to be very slow for high frequency
mappings. Since this does not affect the normal use-case where a "struct page"
is available, the performance of this API will be handled by a seperate patch
series.

So the simple way to use memory outside kernel control is:

1- Pass 'mem=' in the kernel command-line to limit the amount of memory managed 
   by the kernel.
2- Map this physical memory you want to give to the guest with:
   mmap("/dev/mem", physical_address_offset, ..)
3- Use the user-space virtual address as the "userspace_addr" field in
   KVM_SET_USER_MEMORY_REGION ioctl.

v5 -> v6:
- Added one extra patch to ensure that support for this mem= case is complete
  for x86.
- Added a helper function to check if the mapping is mapped or not.
- Added more comments on the struct.
- Setting ->page to NULL on unmap and to a poison ptr if unused during map
- Checking for map ptr before using it.
- Change kvm_vcpu_unmap to also mark page dirty for LM. That requires
  passing the vCPU pointer again to this function.

v4 -> v5:
- Introduce a new parameter 'dirty' into kvm_vcpu_unmap
- A horrible rebase due to nested.c :)
- Dropped a couple of hyperv patches as the code was fixed already as a
  side-effect of another patch.
- Added a new trivial cleanup patch.

v3 -> v4:
- Rebase
- Add a new patch to also fix the newly introduced enlightned VMCS.

v2 -> v3:
- Rebase
- Add a new patch to also fix the newly introduced shadow VMCS.

Filippo Sironi (1):
  X86/KVM: Handle PFNs outside of kernel reach when touching GPTEs

KarimAllah Ahmed (13):
  X86/nVMX: handle_vmon: Read 4 bytes from guest memory
  X86/nVMX: Update the PML table without mapping and unmapping the page
  KVM: Introduce a new guest mapping API
  X86/nVMX: handle_vmptrld: Use kvm_vcpu_map when copying VMCS12 from
    guest memory
  KVM/nVMX: Use kvm_vcpu_map when mapping the L1 MSR bitmap
  KVM/nVMX: Use kvm_vcpu_map when mapping the virtual APIC page
  KVM/nVMX: Use kvm_vcpu_map when mapping the posted interrupt
    descriptor table
  KVM/X86: Use kvm_vcpu_map in emulator_cmpxchg_emulated
  KVM/nSVM: Use the new mapping API for mapping guest memory
  KVM/nVMX: Use kvm_vcpu_map for accessing the shadow VMCS
  KVM/nVMX: Use kvm_vcpu_map for accessing the enlightened VMCS
  KVM/nVMX: Use page_address_valid in a few more locations
  kvm, x86: Properly check whether a pfn is an MMIO or not

 arch/x86/include/asm/e820/api.h |   1 +
 arch/x86/kernel/e820.c          |  18 ++++-
 arch/x86/kvm/mmu.c              |   5 +-
 arch/x86/kvm/paging_tmpl.h      |  38 +++++++---
 arch/x86/kvm/svm.c              |  97 ++++++++++++------------
 arch/x86/kvm/vmx/nested.c       | 160 +++++++++++++++-------------------------
 arch/x86/kvm/vmx/vmx.c          |  19 ++---
 arch/x86/kvm/vmx/vmx.h          |   9 ++-
 arch/x86/kvm/x86.c              |  14 ++--
 include/linux/kvm_host.h        |  28 +++++++
 virt/kvm/kvm_main.c             |  64 ++++++++++++++++
 11 files changed, 267 insertions(+), 186 deletions(-)
```
