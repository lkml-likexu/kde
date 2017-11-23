

#### [PATCH 0/5] KVM: PPC: Book3S HV: Fix dirty page logging for a nested
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c

The following series fixes dirty page logging for when nested guests are being
run.

The dirty page state of an L1 guest was found to be inaccurate from an L0 point
of view when L1 was running guests. Also the dirty page state of an L2 guest
from an L1 point of view was inaccurate.

Fix this by:
- Ensuring nested-rmap entries are inserted correctly so that they can be
  retrieved.
- Ensuring that rc bits in the shadow page table are set correctly at creation
  time so that L1 is informed when pages are dirtied
- Ensuring that rc bits in the shadow page table are cleared when L0 clears
  them in an L1 pte so that the nested guest cannot continue to write to the
  page

Suraj Jitindar Singh (5):
  KVM: PPC: Book3S HV: Hold kvm->mmu_lock across updating nested pte rc
    bits
  KVM: PPC: Book3S HV: Align gfn to L1 page size when inserting
    nest-rmap entry
  KVM: PPC: Book3S HV: Apply combination of host and l1 pte rc for
    nested guest
  KVM: PPC: Book3S HV: Introduce kvmhv_update_nest_rmap_rc_list()
  KVM: PPC: Book3S HV: Keep rc bits in shadow pgtable in sync with host

 arch/powerpc/include/asm/kvm_book3s.h    |  2 +
 arch/powerpc/include/asm/kvm_book3s_64.h |  3 ++
 arch/powerpc/kvm/book3s_64_mmu_radix.c   | 30 +++++++++----
 arch/powerpc/kvm/book3s_hv_nested.c      | 74 +++++++++++++++++++++++++++++---
 4 files changed, 95 insertions(+), 14 deletions(-)
```
