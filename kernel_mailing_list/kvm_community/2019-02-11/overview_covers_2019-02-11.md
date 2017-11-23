

#### [PATCH 0/5] use pinned_vm instead of locked_vm to account pinned
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c

Hi,

This series converts users that account pinned pages with locked_vm to
account with pinned_vm instead, pinned_vm being the correct counter to
use.  It's based on a similar patch I posted recently[0].

The patches are based on rdma/for-next to build on Davidlohr Bueso's
recent conversion of pinned_vm to an atomic64_t[1].  Seems to make some
sense for these to be routed the same way, despite lack of rdma content?

All five of these places, and probably some of Davidlohr's conversions,
probably want to be collapsed into a common helper in the core mm for
accounting pinned pages.  I tried, and there are several details that
likely need discussion, so this can be done as a follow-on.

I'd appreciate a look at patch 5 especially since the accounting is
unusual no matter whether locked_vm or pinned_vm are used.

On powerpc, this was cross-compile tested only.

[0] http://lkml.kernel.org/r/20181105165558.11698-8-daniel.m.jordan@oracle.com
[1] http://lkml.kernel.org/r/20190206175920.31082-1-dave@stgolabs.net

Daniel Jordan (5):
  vfio/type1: use pinned_vm instead of locked_vm to account pinned pages
  vfio/spapr_tce: use pinned_vm instead of locked_vm to account pinned
    pages
  fpga/dlf/afu: use pinned_vm instead of locked_vm to account pinned
    pages
  powerpc/mmu: use pinned_vm instead of locked_vm to account pinned
    pages
  kvm/book3s: use pinned_vm instead of locked_vm to account pinned pages

 Documentation/vfio.txt              |  6 +--
 arch/powerpc/kvm/book3s_64_vio.c    | 35 +++++++---------
 arch/powerpc/mm/mmu_context_iommu.c | 43 ++++++++++---------
 drivers/fpga/dfl-afu-dma-region.c   | 50 +++++++++++-----------
 drivers/vfio/vfio_iommu_spapr_tce.c | 64 ++++++++++++++---------------
 drivers/vfio/vfio_iommu_type1.c     | 31 ++++++--------
 6 files changed, 104 insertions(+), 125 deletions(-)
```
