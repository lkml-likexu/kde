

#### [PATCH v2 00/27] KVM: x86/mmu: Remove fast invalidate mechanism
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

...and clean up the MMIO spte generation code.

=== Non-x86 Folks ===
Patch 01/27 (which you should also be cc'd on) changes the prototype for
a function that is defined by all architectures but only actually used
by x86.  Feel free to skip the rest of this cover letter.

=== x86 Folks ===
Though not explicitly stated, for all intents and purposes the fast
invalidate mechanism was added to speed up the scenario where removing
a memslot, e.g. when accessing PCI ROM, caused KVM to flush all shadow
entries[1].

The other use cases of "flush everything" are VM teardown and handling
MMIO generation overflow, neither of which is a performance critial
path (see "Other Uses" below).

For the memslot case, zapping all shadow entries is overkill, i.e. KVM
only needs to zap the entries associated with the memslot, but KVM has
historically used a big hammer because if all you have is a hammer,
everything looks like a nail.

Rather than zap all pages when removing a memslot, zap only the shadow
entries associated with said memslot.  I see a performance improvement
of ~5% when zapping only the pages for the deleted memslot when using a
slightly modified version of the original benchmark[2][3][4] (I don't
have easy access to a system with hundreds of gigs of memory).

$ cat shell.sh
        #!/bin/sh

        echo 3 > /proc/sys/vm/drop_caches
        ./mmtest -c 8 -m 2000 -e ./rom.sh

I.e. running 8 threads and 2gb of memory per thread, time in milliseconds:

Before: 89.117
After:  84.768


With the memslot use case gone, maintaining the fast invalidate path
adds a moderate amount of complexity but provides little to no value.
Furhtermore, its existence may give the impression that it's "ok" to zap
all shadow pages.  Remove the fast invalidate mechanism to simplify the
code and to discourage future code from zapping all pages as using such
a big hammer should be a last resort.

Unfortunately, simply reverting the fast invalidate code re-introduces
shortcomings in the previous code, notably that KVM may hold a spinlock
and not schedule for an extended period of time.  Releasing the lock to
voluntarily reschedule is perfectly doable, and for the VM teardown case
of "zap everything" it can be added with no additional changes since KVM
doesn't need to provide any ordering guarantees about sptes in that case.

For the MMIO case, KVM needs to prevent vCPUs from consuming stale sptes
created with an old generation number.  This should be a non-issue as
KVM is supposed to prevent consuming stale MMIO sptes regardless of the
zapping mechanism employed, releasing mmu_lock while zapping simply
makes it much more likely to hit any bug leading to stale spte usage.
As luck would have it, there are a number of corner cases in the MMIO
spte invalidation flow that could theoretically result in reusing stale
sptes.  So before reworking memslot zapping and reverting to the slow
invalidate mechanism, fix a number of bugs related to MMIO generations
and opportunistically clean up the memslots/MMIO generation code.


=== History ===
Flushing of shadow pages when removing a memslot was originally added
by commit 34d4cb8fca1f ("KVM: MMU: nuke shadowed pgtable pages and ptes
on memslot destruction"), and obviously emphasized functionality over
performance.  Commit 2df72e9bc4c5 ("KVM: split kvm_arch_flush_shadow")
added a path to allow flushing only the removed slot's shadow pages,
but x86 just redirected to the "zap all" flow.

Eventually, it became evident that zapping everything is slow, and so
x86 developed a more efficient hammer in the form of the fast invalidate
mechanism.

=== Other Uses ===
When a VM is being destroyed, either there are no active vcpus, i.e.
there's no lock contention, or the VM has ungracefully terminated, in
which case we want to reclaim its pages as quickly as possible, i.e.
not release the MMU lock if there are still CPUs executing in the VM.

The MMIO generation scenario is almost literally a one-in-a-million
occurrence, i.e. is not a performance sensitive scenario.

It's worth noting that prior to the "fast invalidate" series being
applied, there was actually another use case of kvm_mmu_zap_all() in
emulator_fix_hypercall() whose existence may have contributed to
improving the performance of "zap all" instead of avoiding it altogether.
But that usage was removed by the series itself in commit 758ccc89b83c
("KVM: x86: drop calling kvm_mmu_zap_all in emulator_fix_hypercall").

[1] https://lkml.kernel.org/r/1369960590-14138-1-git-send-email-xiaoguangrong@linux.vnet.ibm.com
[2] https://lkml.kernel.org/r/1368706673-8530-1-git-send-email-xiaoguangrong@linux.vnet.ibm.com
[3] http://lkml.iu.edu/hypermail/linux/kernel/1305.2/00277.html
[4] http://lkml.iu.edu/hypermail/linux/kernel/1305.2/00277/mmtest.tar.bz2

v1: https://patchwork.kernel.org/cover/10756579/
v2:
  - Fix a zap vs flush priority bug in kvm_mmu_remote_flush_or_zap() [me]
  - Voluntarily reschedule and/or drop mmu_lock as needed when zapping
    all sptes or all MMIO sptes [Paolo]
  - Add patches to clean up the memslots/MMIO generation code and fix
    a variety of theoretically corner case bugs


Sean Christopherson (27):
  KVM: Call kvm_arch_memslots_updated() before updating memslots
  KVM: x86/mmu: Detect MMIO generation wrap in any address space
  KVM: x86/mmu: Do not cache MMIO accesses while memslots are in flux
  KVM: Explicitly define the "memslot update in-progress" bit
  KVM: x86: Use a u64 when passing the MMIO gen around
  KVM: x86: Refactor the MMIO SPTE generation handling
  KVM: Remove the hack to trigger memslot generation wraparound
  KVM: Move the memslot update in-progress flag to bit 63
  KVM: x86/mmu: Move slot_level_*() helper functions up a few lines
  KVM: x86/mmu: Split remote_flush+zap case out of
    kvm_mmu_flush_or_zap()
  KVM: x86/mmu: Zap only the relevant pages when removing a memslot
  Revert "KVM: MMU: document fast invalidate all pages"
  Revert "KVM: MMU: drop kvm_mmu_zap_mmio_sptes"
  KVM: x86/mmu: Voluntarily reschedule as needed when zapping MMIO sptes
  KVM: x86/mmu: Remove is_obsolete() call
  Revert "KVM: MMU: reclaim the zapped-obsolete page first"
  Revert "KVM: MMU: collapse TLB flushes when zap all pages"
  Revert "KVM: MMU: zap pages in batch"
  Revert "KVM: MMU: add tracepoint for kvm_mmu_invalidate_all_pages"
  Revert "KVM: MMU: show mmu_valid_gen in shadow page related
    tracepoints"
  Revert "KVM: x86: use the fast way to invalidate all pages"
  KVM: x86/mmu: skip over invalid root pages when zapping all sptes
  KVM: x86/mmu: Voluntarily reschedule as needed when zapping all sptes
  Revert "KVM: MMU: fast invalidate all pages"
  KVM: x86/mmu: Differentiate between nr zapped and list unstable
  KVM: x86/mmu: WARN if zapping a MMIO spte results in zapping children
  KVM: x86/mmu: Consolidate kvm_mmu_zap_all() and
    kvm_mmu_zap_mmio_sptes()

 Documentation/virtual/kvm/mmu.txt   |  41 +--
 arch/mips/include/asm/kvm_host.h    |   2 +-
 arch/powerpc/include/asm/kvm_host.h |   2 +-
 arch/s390/include/asm/kvm_host.h    |   2 +-
 arch/x86/include/asm/kvm_host.h     |   9 +-
 arch/x86/kvm/mmu.c                  | 442 +++++++++++++---------------
 arch/x86/kvm/mmu.h                  |   1 -
 arch/x86/kvm/mmutrace.h             |  42 +--
 arch/x86/kvm/x86.c                  |   7 +-
 arch/x86/kvm/x86.h                  |   7 +-
 include/linux/kvm_host.h            |  23 +-
 virt/kvm/arm/mmu.c                  |   2 +-
 virt/kvm/kvm_main.c                 |  39 ++-
 13 files changed, 286 insertions(+), 333 deletions(-)
```
