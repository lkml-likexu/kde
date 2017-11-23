

#### [PATCH net V3 0/3] Fix various issue of vhost
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to fix various issues of vhost:

- Patch 1 adds a missing write barrier between used idx updating and
  logging.
- Patch 2-3 brings back the protection of device IOTLB through vq
  mutex, this fixes possible use after free in device IOTLB entries.

Please consider them for -stable.

Thanks

Changes from V2:
- drop dirty page fix and make it for net-next
Changes from V1:
- silent compiler warning for 32bit.
- use mutex_trylock() on slowpath instead of mutex_lock() even on fast
  path.

Jason Wang (3):
  vhost: make sure used idx is seen before log in vhost_add_used_n()
  vhost_net: switch to use mutex_trylock() in vhost_net_busy_poll()
  Revert "net: vhost: lock the vqs one by one"

 drivers/vhost/net.c   |  8 +++++++-
 drivers/vhost/vhost.c | 23 +++++++++++++++++++----
 2 files changed, 26 insertions(+), 5 deletions(-)
Acked-by: Michael S. Tsirkin <mst@redhat.com>
```
#### [PATCH 0/2] optimize waiting for free thread to do compression
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Currently we have two behaviors if all threads are busy to do compression,
the main thread mush wait one of them becoming free if @compress-wait-thread
set to on or the main thread can directly return without wait and post
the page out as normal one

Both of them have its profits and short-comes, however, if the bandwidth is
not limited extremely so that compression can not use out all of it bandwidth,
at the same time, the migration process is easily throttled if we posted too
may pages as normal pages. None of them can work properly under this case

In order to use the bandwidth more effectively, we introduce the third
behavior, compress-wait-thread-adaptive, which make the main thread wait
if there is no bandwidth left or let the page go out as normal page if there
has enough bandwidth to make sure the migration process will not be
throttled

Another patch introduces a new statistic, pages-per-second, as bandwidth
or mbps is not enough to measure the performance of posting pages out as
we have compression, xbzrle, which can significantly reduce the amount of
the data size, instead, pages-per-second if the one we want

Performance data
================
We have limited the bandwidth to 300

                                Used Bandwidth     Pages-per-Second
compress-wait-thread = on         951.66 mbps         131784

compress-wait-thread = off        2491.74 mbps        93495
compress-wait-thread-adaptive     1982.94 mbps        162529
   = on

Xiao Guangrong (2):
  migration: introduce compress-wait-thread-adaptive
  migration: introduce pages-per-second

 hmp.c                 |  13 ++++++
 migration/migration.c |  49 +++++++++++++++++++-
 migration/migration.h |  12 +++++
 migration/ram.c       | 124 ++++++++++++++++++++++++++++++++++++++++++++++----
 qapi/migration.json   |  31 +++++++++++--
 5 files changed, 215 insertions(+), 14 deletions(-)
```
#### [PATCH net-next 0/3] vhost: accelerate metadata access through vmap()
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to access virtqueue metadata through kernel virtual
address instead of copy_user() friends since they had too much
overheads like checks, spec barriers or even hardware feature
toggling.

Test shows about 24% improvement on TX PPS. It should benefit other
cases as well.

Please review

Jason Wang (3):
  vhost: generalize adding used elem
  vhost: fine grain userspace memory accessors
  vhost: access vq metadata through kernel virtual address

 drivers/vhost/vhost.c | 281 ++++++++++++++++++++++++++++++++++++++----
 drivers/vhost/vhost.h |  11 ++
 2 files changed, 266 insertions(+), 26 deletions(-)
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
```
#### [PATCH v3 0/3] mmu notifier contextual informations
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

Changes since v2:
 - fix build warning with CONFIG_MMU_NOTIFIER=n
 - fix make htmldocs warning

Changes since v1:
 - fix build with CONFIG_MMU_NOTIFIER=n
 - kernel docs


Original cover letter:

This patchset add contextual information, why an invalidation is
happening, to mmu notifier callback. This is necessary for user
of mmu notifier that wish to maintains their own data structure
without having to add new fields to struct vm_area_struct (vma).

For instance device can have they own page table that mirror the
process address space. When a vma is unmap (munmap() syscall) the
device driver can free the device page table for the range.

Today we do not have any information on why a mmu notifier call
back is happening and thus device driver have to assume that it
is always an munmap(). This is inefficient at it means that it
needs to re-allocate device page table on next page fault and
rebuild the whole device driver data structure for the range.

Other use case beside munmap() also exist, for instance it is
pointless for device driver to invalidate the device page table
when the invalidation is for the soft dirtyness tracking. Or
device driver can optimize away mprotect() that change the page
table permission access for the range.

This patchset enable all this optimizations for device driver.
I do not include any of those in this serie but other patchset
i am posting will leverage this.


From code point of view the patchset is pretty simple, the first
two patches consolidate all mmu notifier arguments into a struct
so that it is easier to add/change arguments. The last patch adds
the contextual information (munmap, protection, soft dirty, clear,
...).

Cheers,
Jérôme

Cc: Christian König <christian.koenig@amd.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>

Jérôme Glisse (3):
  mm/mmu_notifier: use structure for invalidate_range_start/end callback
    v2
  mm/mmu_notifier: use structure for invalidate_range_start/end calls v3
  mm/mmu_notifier: contextual information for event triggering
    invalidation v2

 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  |  47 ++++-----
 drivers/gpu/drm/i915/i915_gem_userptr.c |  14 ++-
 drivers/gpu/drm/radeon/radeon_mn.c      |  16 ++-
 drivers/infiniband/core/umem_odp.c      |  20 ++--
 drivers/infiniband/hw/hfi1/mmu_rb.c     |  13 +--
 drivers/misc/mic/scif/scif_dma.c        |  11 +-
 drivers/misc/sgi-gru/grutlbpurge.c      |  14 ++-
 drivers/xen/gntdev.c                    |  12 +--
 fs/dax.c                                |  15 ++-
 fs/proc/task_mmu.c                      |   8 +-
 include/linux/mm.h                      |   4 +-
 include/linux/mmu_notifier.h            | 132 ++++++++++++++++++------
 kernel/events/uprobes.c                 |  11 +-
 mm/hmm.c                                |  23 ++---
 mm/huge_memory.c                        |  58 +++++------
 mm/hugetlb.c                            |  54 +++++-----
 mm/khugepaged.c                         |  11 +-
 mm/ksm.c                                |  23 ++---
 mm/madvise.c                            |  22 ++--
 mm/memory.c                             | 103 +++++++++---------
 mm/migrate.c                            |  29 +++---
 mm/mmu_notifier.c                       |  22 ++--
 mm/mprotect.c                           |  16 +--
 mm/mremap.c                             |  11 +-
 mm/oom_kill.c                           |  17 +--
 mm/rmap.c                               |  32 +++---
 virt/kvm/kvm_main.c                     |  14 +--
 27 files changed, 406 insertions(+), 346 deletions(-)
```
