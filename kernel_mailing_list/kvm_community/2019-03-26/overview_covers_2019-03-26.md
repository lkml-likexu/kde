

#### [PATCH kvmtool v3 0/3] vfio-pci: Support INTx mode re-enabling
##### From: Leo Yan <leo.yan@linaro.org>

```c

When enable vfio-pci mode for NIC driver on Juno board, the IRQ is
failed to forward properly from host to guest, finally root caused this
issue is related with kvmtool cannot re-enable INTx mode properly.

So the basic working flow to reproduce this issue is as below:

    Host             Guest
-------------  --------------------
  INTx mode
                 MSI enable failed in NIC driver
                 MSI disable in NIC driver
                 Switch back to INTx mode --> kvmtool doesn't support

So this patch is to support INTx mode re-enabling; patch 0001 is one
minor fixing up for eventfd releasing; patch 0002 introduces a new
function vfio_pci_init_intx() which is used to finish INTx one-time
initialisation; patch 0003 is the core patch for support INTx mode
re-enabling, when kvmtool detects MSI is disabled it rollbacks to INTx
mode.

This patch set has been tested on Juno-r2 board.

== Changes for V3 ==
* Add new function vfio_pci_init_intx() for one-time initialisation.
* Simplized INTx re-enabling (don't change irq_line anymore at the
  runtime).


Leo Yan (3):
  vfio-pci: Release INTx's unmask eventfd properly
  vfio-pci: Add new function for INTx one-time initialisation
  vfio-pci: Re-enable INTx mode when disable MSI/MSIX

 include/kvm/vfio.h |   1 +
 vfio/pci.c         | 108 +++++++++++++++++++++++++++++----------------
 2 files changed, 72 insertions(+), 37 deletions(-)
```
#### [PATCH v6 0/8] mmu notifier provide context informations
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

(Andrew this apply on top of my HMM patchset as otherwise you will have
 conflict with changes to mm/hmm.c)

Changes since v5:
    - drop KVM bits waiting for KVM people to express interest if they
      do not then i will post patchset to remove change_pte_notify as
      without the changes in v5 change_pte_notify is just useless (it
      it is useless today upstream it is just wasting cpu cycles)
    - rebase on top of lastest Linus tree

Previous cover letter with minor update:


Here i am not posting users of this, they already have been posted to
appropriate mailing list [6] and will be merge through the appropriate
tree once this patchset is upstream.

Note that this serie does not change any behavior for any existing
code. It just pass down more information to mmu notifier listener.

The rational for this patchset:

CPU page table update can happens for many reasons, not only as a
result of a syscall (munmap(), mprotect(), mremap(), madvise(), ...)
but also as a result of kernel activities (memory compression, reclaim,
migration, ...).

This patch introduce a set of enums that can be associated with each
of the events triggering a mmu notifier:

    - UNMAP: munmap() or mremap()
    - CLEAR: page table is cleared (migration, compaction, reclaim, ...)
    - PROTECTION_VMA: change in access protections for the range
    - PROTECTION_PAGE: change in access protections for page in the range
    - SOFT_DIRTY: soft dirtyness tracking

Being able to identify munmap() and mremap() from other reasons why the
page table is cleared is important to allow user of mmu notifier to
update their own internal tracking structure accordingly (on munmap or
mremap it is not longer needed to track range of virtual address as it
becomes invalid). Without this serie, driver are force to assume that
every notification is an munmap which triggers useless trashing within
drivers that associate structure with range of virtual address. Each
driver is force to free up its tracking structure and then restore it
on next device page fault. With this serie we can also optimize device
page table update [6].

More over this can also be use to optimize out some page table updates
like for KVM where we can update the secondary MMU directly from the
callback instead of clearing it.

ACKS AMD/RADEON https://lkml.org/lkml/2019/2/1/395
ACKS RDMA https://lkml.org/lkml/2018/12/6/1473

Cheers,
Jérôme

[1] v1 https://lkml.org/lkml/2018/3/23/1049
[2] v2 https://lkml.org/lkml/2018/12/5/10
[3] v3 https://lkml.org/lkml/2018/12/13/620
[4] v4 https://lkml.org/lkml/2019/1/23/838
[5] v5 https://lkml.org/lkml/2019/2/19/752
[6] patches to use this:
    https://lkml.org/lkml/2019/1/23/833
    https://lkml.org/lkml/2019/1/23/834
    https://lkml.org/lkml/2019/1/23/832
    https://lkml.org/lkml/2019/1/23/831

Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: linux-mm@kvack.org
Cc: Christian König <christian.koenig@amd.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Jani Nikula <jani.nikula@linux.intel.com>
Cc: Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alex Deucher <alexander.deucher@amd.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ben Skeggs <bskeggs@redhat.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>

Jérôme Glisse (8):
  mm/mmu_notifier: helper to test if a range invalidation is blockable
  mm/mmu_notifier: convert user range->blockable to helper function
  mm/mmu_notifier: convert mmu_notifier_range->blockable to a flags
  mm/mmu_notifier: contextual information for event enums
  mm/mmu_notifier: contextual information for event triggering
    invalidation v2
  mm/mmu_notifier: use correct mmu_notifier events for each invalidation
  mm/mmu_notifier: pass down vma and reasons why mmu notifier is
    happening v2
  mm/mmu_notifier: mmu_notifier_range_update_to_read_only() helper

 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  |  8 ++--
 drivers/gpu/drm/i915/i915_gem_userptr.c |  2 +-
 drivers/gpu/drm/radeon/radeon_mn.c      |  4 +-
 drivers/infiniband/core/umem_odp.c      |  5 +-
 drivers/xen/gntdev.c                    |  6 +--
 fs/proc/task_mmu.c                      |  3 +-
 include/linux/mmu_notifier.h            | 63 +++++++++++++++++++++++--
 kernel/events/uprobes.c                 |  3 +-
 mm/hmm.c                                |  6 +--
 mm/huge_memory.c                        | 14 +++---
 mm/hugetlb.c                            | 12 +++--
 mm/khugepaged.c                         |  3 +-
 mm/ksm.c                                |  6 ++-
 mm/madvise.c                            |  3 +-
 mm/memory.c                             | 25 ++++++----
 mm/migrate.c                            |  5 +-
 mm/mmu_notifier.c                       | 12 ++++-
 mm/mprotect.c                           |  4 +-
 mm/mremap.c                             |  3 +-
 mm/oom_kill.c                           |  3 +-
 mm/rmap.c                               |  6 ++-
 virt/kvm/kvm_main.c                     |  3 +-
 22 files changed, 147 insertions(+), 52 deletions(-)
```
