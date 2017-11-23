

#### [PATCH v10 0/8] kvm: arm64: Support PUD hugepage at stage 2
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c

This series is an update to the PUD hugepage support previously posted
at [0]. This patchset adds support for PUD hugepages at stage 2 a
feature that is useful on cores that have support for large sized TLB
mappings (e.g., 1GB for 4K granule).

The patches are based on v4.20-rc4

The patches have been tested on AMD Seattle system with the following
hugepage sizes - 2M and 1G.

Right now the PUD hugepage for stage2 is only supported if the stage2
has 4 levels. i.e, with an IPA size of minimum 44bits with 4K pages.
This could be relaxed to stage2 with 3 levels, with the stage1 PUD huge
page mapped in the entry level of the stage2 (i.e, pgd). I have not
added the change here to keep this version stable w.r.t the previous
version. I could post a patch later after further discussions in the
list.


[0] https://patchwork.kernel.org/cover/10622379/

v9 -> v10
* Address comments on v9. Mainly converting BUG() => WARN_ON(1)
  in arm32 for PUD helpers.
* Dropped Suzuki's "Review" tags from the patches which were modified.

v8 -> v9

* Dropped bugfix patch 1 which has been merged

v7 -> v8

* Add kvm_stage2_has_pud() helper on arm32
* Rebased to v6 of 52bit dynamic IPA support

v6 -> v7

* Restrict thp check to exclude hugetlbfs pages - Patch 1
* Don't update PUD entry if there's no change - Patch 9
* Add check for PUD level in stage 2 - Patch 9

v5 -> v6

* Split Patch 1 to move out the refactoring of exec permissions on
  page table entries.
* Patch 4 - Initialise p*dpp pointers in stage2_get_leaf_entry()
* Patch 5 - Trigger a BUG() in kvm_pud_pfn() on arm

v4 -> v5:
* Patch 1 - Drop helper stage2_should_exec() and refactor the
  condition to decide if a page table entry should be marked
  executable
* Patch 4-6 - Introduce stage2_get_leaf_entry() and use it in this and
  latter patches
* Patch 7 - Use stage 2 accessors instead of using the page table
  helpers directly
* Patch 7 - Add a note to update the PUD hugepage support when number
  of levels of stage 2 tables differs from stage 1

v3 -> v4:
* Patch 1 and 7 - Don't put down hugepages pte if logging is enabled
* Patch 4-5 - Add PUD hugepage support for exec and access faults
* Patch 6 - PUD hugepage support for aging page table entries

v2 -> v3:
* Update vma_pagesize directly if THP [1/4]. Previsouly this was done
  indirectly via hugetlb
* Added review tag [4/4]

v1 -> v2:
* Create helper to check if the page should have exec permission [1/4]
* Fix broken condition to detect THP hugepage [1/4]
* Fix in-correct hunk resulting from a rebase [4/4]

Punit Agrawal (8):
  KVM: arm/arm64: Share common code in user_mem_abort()
  KVM: arm/arm64: Re-factor setting the Stage 2 entry to exec on fault
  KVM: arm/arm64: Introduce helpers to manipulate page table entries
  KVM: arm64: Support dirty page tracking for PUD hugepages
  KVM: arm64: Support PUD hugepage in stage2_is_exec()
  KVM: arm64: Support handling access faults for PUD hugepages
  KVM: arm64: Update age handlers to support PUD hugepages
  KVM: arm64: Add support for creating PUD hugepages at stage 2

 arch/arm/include/asm/kvm_mmu.h         |  61 +++++++
 arch/arm/include/asm/stage2_pgtable.h  |   5 +
 arch/arm64/include/asm/kvm_mmu.h       |  48 +++++
 arch/arm64/include/asm/pgtable-hwdef.h |   4 +
 arch/arm64/include/asm/pgtable.h       |   9 +
 virt/kvm/arm/mmu.c                     | 312 ++++++++++++++++++++++++---------
 6 files changed, 360 insertions(+), 79 deletions(-)
```
