

#### [PATCH 00/12] block/bio, fs: convert put_page() to put_user_page*()
##### From: john.hubbard@gmail.com
X-Google-Original-From: jhubbard@nvidia.com
From: John Hubbard <jhubbard@nvidia.com>

```c

From: John Hubbard <jhubbard@nvidia.com>

Hi,

This is mostly Jerome's work, converting the block/bio and related areas
to call put_user_page*() instead of put_page(). Because I've changed
Jerome's patches, in some cases significantly, I'd like to get his
feedback before we actually leave him listed as the author (he might
want to disown some or all of these).

I added a new patch, in order to make this work with Christoph Hellwig's
recent overhaul to bio_release_pages(): "block: bio_release_pages: use
flags arg instead of bool".

I've started the series with a patch that I've posted in another
series ("mm/gup: add make_dirty arg to put_user_pages_dirty_lock()"[1]),
because I'm not sure which of these will go in first, and this allows each
to stand alone.

Testing: not much beyond build and boot testing has been done yet. And
I'm not set up to even exercise all of it (especially the IB parts) at
run time.

Anyway, changes here are:

* Store, in the iov_iter, a "came from gup (get_user_pages)" parameter.
  Then, use the new iov_iter_get_pages_use_gup() to retrieve it when
  it is time to release the pages. That allows choosing between put_page()
  and put_user_page*().

* Pass in one more piece of information to bio_release_pages: a "from_gup"
  parameter. Similar use as above.

* Change the block layer, and several file systems, to use
  put_user_page*().

[1] https://lore.kernel.org/r/20190724012606.25844-2-jhubbard@nvidia.com
    And please note the correction email that I posted as a follow-up,
    if you're looking closely at that patch. :) The fixed version is
    included here.

John Hubbard (3):
  mm/gup: add make_dirty arg to put_user_pages_dirty_lock()
  block: bio_release_pages: use flags arg instead of bool
  fs/ceph: fix a build warning: returning a value from void function

Jérôme Glisse (9):
  iov_iter: add helper to test if an iter would use GUP v2
  block: bio_release_pages: convert put_page() to put_user_page*()
  block_dev: convert put_page() to put_user_page*()
  fs/nfs: convert put_page() to put_user_page*()
  vhost-scsi: convert put_page() to put_user_page*()
  fs/cifs: convert put_page() to put_user_page*()
  fs/fuse: convert put_page() to put_user_page*()
  fs/ceph: convert put_page() to put_user_page*()
  9p/net: convert put_page() to put_user_page*()

 block/bio.c                                |  81 ++++++++++++---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/hfi1/user_pages.c    |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   5 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   5 +-
 drivers/infiniband/sw/siw/siw_mem.c        |   8 +-
 drivers/vhost/scsi.c                       |  13 ++-
 fs/block_dev.c                             |  22 +++-
 fs/ceph/debugfs.c                          |   2 +-
 fs/ceph/file.c                             |  62 ++++++++---
 fs/cifs/cifsglob.h                         |   3 +
 fs/cifs/file.c                             |  22 +++-
 fs/cifs/misc.c                             |  19 +++-
 fs/direct-io.c                             |   2 +-
 fs/fuse/dev.c                              |  22 +++-
 fs/fuse/file.c                             |  53 +++++++---
 fs/nfs/direct.c                            |  10 +-
 include/linux/bio.h                        |  22 +++-
 include/linux/mm.h                         |   5 +-
 include/linux/uio.h                        |  11 ++
 mm/gup.c                                   | 115 +++++++++------------
 net/9p/trans_common.c                      |  14 ++-
 net/9p/trans_common.h                      |   3 +-
 net/9p/trans_virtio.c                      |  18 +++-
 24 files changed, 357 insertions(+), 170 deletions(-)
```
#### [PATCH 0/3] KVM: arm/arm64: Optimize lpi translation cache
##### From: Xiangyou Xie <xiexiangyou@huawei.com>

```c

Hello,

This patches are based on Marc Zyngier's branch
https://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git/log/?h=kvm-arm64/its-translation-cache

As follows:
(1) Introduce multiple LPI translation caches to reduce concurrency
(2) Removed the unnecessary vgic_its_invalidate_cache()
(3) Introduced vgic_cpu->pending and vgic_cpu->lowest, reducing
    vgic_cpu.ap_list_lock competition

Best Regards,

Xiangyou

Xiangyou Xie (3):
  KVM: arm/arm64: vgic-its: Introduce multiple LPI translation caches
  KVM: arm/arm64: vgic-its: Do not execute invalidate MSI-LPI
    translation cache on movi command
  KVM: arm/arm64: vgic: introduce vgic_cpu pending status and
    lowest_priority

 include/kvm/arm_vgic.h        |  18 +++-
 virt/kvm/arm/vgic/vgic-init.c |   6 +-
 virt/kvm/arm/vgic/vgic-its.c  | 201 ++++++++++++++++++++++++------------------
 virt/kvm/arm/vgic/vgic.c      |  40 +++++----
 4 files changed, 160 insertions(+), 105 deletions(-)
```
#### [PATCH 0/4] migration: fix migrate_cancel problems of multifd
##### From: Juan Quintela <quintela@redhat.com>

```c

- Just simplify patch 2 from Ivan
- Add patch 3 to cover everything.

Please review.

My plan is send the three of them for the update

Ivan Ren (3):
  migration: fix migrate_cancel leads live_migration thread endless loop
  migration: fix migrate_cancel leads live_migration thread hung forever
  migration: fix migrate_cancel multifd migration leads destination hung
    forever

Juan Quintela (1):
  migration: Make explicit that we are quitting multifd

 migration/ram.c | 66 ++++++++++++++++++++++++++++++++++++++++++-------
 1 file changed, 57 insertions(+), 9 deletions(-)
```
#### [PATCH v2 0/5] mm / virtio: Provide support for page hinting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This series provides an asynchronous means of hinting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as page hinting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of hinted pages in a given free area. When
the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page hinting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page hinting device and it will perform
the required action to make the pages "hinted", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a hinted buddy page instead of a standard
buddy page. The cycle then repeats with additional non-hinted pages being
pulled until the free areas all consist of hinted pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 79g on a 80g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. With that I have seen at most a 2% difference between the base
kernel without these patches and the patches with virtio-balloon disabled.
With the patches and virtio-balloon enabled with hinting the results
largely depend on the host kernel. On a 3.10 RHEL kernel I saw up to a 2%
drop in performance as I approached 16 threads, however on the the lastest
linux-next kernel I saw roughly a 4% to 5% improvement in performance for
all tests with 8 or more threads. I believe the difference seen is due to
the overhead for faulting pages back into the guest and zeroing of memory.

Patch 4 is a bit on the large side at about 600 lines of change, however
I really didn't see a good way to break it up since each piece feeds into
the next. So I couldn't add the statistics by themselves as it didn't
really make sense to add them without something that will either read or
increment/decrement them, or add the Hinted state without something that
would set/unset it. As such I just ended up adding the entire thing as
one patch. It makes it a bit bigger but avoids the issues in the previous
set where I was referencing things before they had been added.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved bounary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermedate array
Moved stats out of free_area, now in seperate area and pointed to from zone
Merged patch 5 into patch 4 to improve reviewability
Updated various code comments throughout
---

Alexander Duyck (5):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Hinted pages
      virtio-balloon: Add support for providing page hints to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   47 ++++++
 include/linux/mmzone.h              |  116 ++++++++------
 include/linux/page-flags.h          |    8 +
 include/linux/page_hinting.h        |  139 ++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  238 ++++++++++++++++++++--------
 mm/page_hinting.c                   |  298 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   24 ---
 mm/shuffle.h                        |   32 ++++
 14 files changed, 796 insertions(+), 133 deletions(-)
 create mode 100644 include/linux/page_hinting.h
 create mode 100644 mm/page_hinting.c

--
```
