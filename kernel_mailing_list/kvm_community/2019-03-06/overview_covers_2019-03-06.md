

#### [RFC PATCH V2 0/5] vhost: accelerate metadata access through vmap()
##### From: Jason Wang <jasowang@redhat.com>

```c

This series tries to access virtqueue metadata through kernel virtual
address instead of copy_user() friends since they had too much
overheads like checks, spec barriers or even hardware feature
toggling. This is done through setup kernel address through vmap() and
resigter MMU notifier for invalidation.

Test shows about 24% improvement on TX PPS. TCP_STREAM doesn't see
obvious improvement.

Thanks

Changes from V4:
- use invalidate_range() instead of invalidate_range_start()
- track dirty pages
Changes from V3:
- don't try to use vmap for file backed pages
- rebase to master
Changes from V2:
- fix buggy range overlapping check
- tear down MMU notifier during vhost ioctl to make sure invalidation
  request can read metadata userspace address and vq size without
  holding vq mutex.
Changes from V1:
- instead of pinning pages, use MMU notifier to invalidate vmaps and
  remap duing metadata prefetch
- fix build warning on MIPS

Jason Wang (5):
  vhost: generalize adding used elem
  vhost: fine grain userspace memory accessors
  vhost: rename vq_iotlb_prefetch() to vq_meta_prefetch()
  vhost: introduce helpers to get the size of metadata area
  vhost: access vq metadata through kernel virtual address

 drivers/vhost/net.c   |   6 +-
 drivers/vhost/vhost.c | 434 ++++++++++++++++++++++++++++++++++++++++++++------
 drivers/vhost/vhost.h |  18 ++-
 3 files changed, 407 insertions(+), 51 deletions(-)
```
#### [RFC][Patch v9 0/6] KVM: Guest Free Page Hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c

The following patch-set proposes an efficient mechanism for handing freed memory between the guest and the host. It enables the guests with no page cache to rapidly free and reclaims memory to and from the host respectively.

Benefit:
With this patch-series, in our test-case, executed on a single system and single NUMA node with 15GB memory, we were able to successfully launch 5 guests(each with 5 GB memory) when page hinting was enabled and 3 without it. (Detailed explanation of the test procedure is provided at the bottom under Test - 1).

Changelog in v9:
	* Guest free page hinting hook is now invoked after a page has been merged in the buddy.
        * Free pages only with order FREE_PAGE_HINTING_MIN_ORDER(currently defined as MAX_ORDER - 1) are captured.
	* Removed kthread which was earlier used to perform the scanning, isolation & reporting of free pages.
	* Pages, captured in the per cpu array are sorted based on the zone numbers. This is to avoid redundancy of acquiring zone locks.
        * Dynamically allocated space is used to hold the isolated guest free pages.
        * All the pages are reported asynchronously to the host via virtio driver.
        * Pages are returned back to the guest buddy free list only when the host response is received.

Pending items:
        * Make sure that the guest free page hinting's current implementation doesn't break hugepages or device assigned guests.
	* Follow up on VIRTIO_BALLOON_F_PAGE_POISON's device side support. (It is currently missing)
        * Compare reporting free pages via vring with vhost.
        * Decide between MADV_DONTNEED and MADV_FREE.
	* Analyze overall performance impact due to guest free page hinting.
	* Come up with proper/traceable error-message/logs.

Tests:
1. Use-case - Number of guests we can launch

	NUMA Nodes = 1 with 15 GB memory
	Guest Memory = 5 GB
	Number of cores in guest = 1
	Workload = test allocation program allocates 4GB memory, touches it via memset and exits.
	Procedure =
	The first guest is launched and once its console is up, the test allocation program is executed with 4 GB memory request (Due to this the guest occupies almost 4-5 GB of memory in the host in a system without page hinting). Once this program exits at that time another guest is launched in the host and the same process is followed. We continue launching the guests until a guest gets killed due to low memory condition in the host.

	Results:
	Without hinting = 3
	With hinting = 5

2. Hackbench
	Guest Memory = 5 GB 
	Number of cores = 4
	Number of tasks		Time with Hinting	Time without Hinting
	4000			19.540			17.818
```
