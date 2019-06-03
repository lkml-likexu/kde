

#### [PATCH v16 00/16] arm64: untag user pointers passed to the kernel
##### From: Andrey Konovalov <andreyknvl@google.com>

```c

=== Overview

arm64 has a feature called Top Byte Ignore, which allows to embed pointer
tags into the top byte of each pointer. Userspace programs (such as
HWASan, a memory debugging tool [1]) might use this feature and pass
tagged user pointers to the kernel through syscalls or other interfaces.

Right now the kernel is already able to handle user faults with tagged
pointers, due to these patches:

1. 81cddd65 ("arm64: traps: fix userspace cache maintenance emulation on a
             tagged pointer")
2. 7dcd9dd8 ("arm64: hw_breakpoint: fix watchpoint matching for tagged
	      pointers")
3. 276e9327 ("arm64: entry: improve data abort handling of tagged
	      pointers")

This patchset extends tagged pointer support to syscall arguments.

As per the proposed ABI change [3], tagged pointers are only allowed to be
passed to syscalls when they point to memory ranges obtained by anonymous
mmap() or sbrk() (see the patchset [3] for more details).

For non-memory syscalls this is done by untaging user pointers when the
kernel performs pointer checking to find out whether the pointer comes
from userspace (most notably in access_ok). The untagging is done only
when the pointer is being checked, the tag is preserved as the pointer
makes its way through the kernel and stays tagged when the kernel
dereferences the pointer when perfoming user memory accesses.

Memory syscalls (mprotect, etc.) don't do user memory accesses but rather
deal with memory ranges, and untagged pointers are better suited to
describe memory ranges internally. Thus for memory syscalls we untag
pointers completely when they enter the kernel.

=== Other approaches

One of the alternative approaches to untagging that was considered is to
completely strip the pointer tag as the pointer enters the kernel with
some kind of a syscall wrapper, but that won't work with the countless
number of different ioctl calls. With this approach we would need a custom
wrapper for each ioctl variation, which doesn't seem practical.

An alternative approach to untagging pointers in memory syscalls prologues
is to inspead allow tagged pointers to be passed to find_vma() (and other
vma related functions) and untag them there. Unfortunately, a lot of
find_vma() callers then compare or subtract the returned vma start and end
fields against the pointer that was being searched. Thus this approach
would still require changing all find_vma() callers.

=== Testing

The following testing approaches has been taken to find potential issues
with user pointer untagging:

1. Static testing (with sparse [2] and separately with a custom static
   analyzer based on Clang) to track casts of __user pointers to integer
   types to find places where untagging needs to be done.

2. Static testing with grep to find parts of the kernel that call
   find_vma() (and other similar functions) or directly compare against
   vm_start/vm_end fields of vma.

3. Static testing with grep to find parts of the kernel that compare
   user pointers with TASK_SIZE or other similar consts and macros.

4. Dynamic testing: adding BUG_ON(has_tag(addr)) to find_vma() and running
   a modified syzkaller version that passes tagged pointers to the kernel.

Based on the results of the testing the requried patches have been added
to the patchset.

=== Notes

This patchset is meant to be merged together with "arm64 relaxed ABI" [3].

This patchset is a prerequisite for ARM's memory tagging hardware feature
support [4].

This patchset has been merged into the Pixel 2 & 3 kernel trees and is
now being used to enable testing of Pixel phones with HWASan.

Thanks!

[1] http://clang.llvm.org/docs/HardwareAssistedAddressSanitizerDesign.html

[2] https://github.com/lucvoo/sparse-dev/commit/5f960cb10f56ec2017c128ef9d16060e0145f292

[3] https://lkml.org/lkml/2019/3/18/819

[4] https://community.arm.com/processors/b/blog/posts/arm-a-profile-architecture-2018-developments-armv85a

Changes in v16:
- Moved untagging for memory syscalls from arm64 wrappers back to generic
  code.
- Dropped untagging for the following memory syscalls: brk, mmap, munmap;
  mremap (only dropped for new_address); mmap_pgoff (not used on arm64);
  remap_file_pages (deprecated); shmat, shmdt (work on shared memory).
- Changed kselftest to LD_PRELOAD a shared library that overrides malloc
  to return tagged pointers.
- Rebased onto 5.2-rc3.

Changes in v15:
- Removed unnecessary untagging from radeon_ttm_tt_set_userptr().
- Removed unnecessary untagging from amdgpu_ttm_tt_set_userptr().
- Moved untagging to validate_range() in userfaultfd code.
- Moved untagging to ib_uverbs_(re)reg_mr() from mlx4_get_umem_mr().
- Rebased onto 5.1.

Changes in v14:
- Moved untagging for most memory syscalls to an arm64 specific
  implementation, instead of doing that in the common code.
- Dropped "net, arm64: untag user pointers in tcp_zerocopy_receive", since
  the provided user pointers don't come from an anonymous map and thus are
  not covered by this ABI relaxation.
- Dropped "kernel, arm64: untag user pointers in prctl_set_mm*".
- Moved untagging from __check_mem_type() to tee_shm_register().
- Updated untagging for the amdgpu and radeon drivers to cover the MMU
  notifier, as suggested by Felix.
- Since this ABI relaxation doesn't actually allow tagged instruction
  pointers, dropped the following patches:
- Dropped "tracing, arm64: untag user pointers in seq_print_user_ip".
- Dropped "uprobes, arm64: untag user pointers in find_active_uprobe".
- Dropped "bpf, arm64: untag user pointers in stack_map_get_build_id_offset".
- Rebased onto 5.1-rc7 (37624b58).

Changes in v13:
- Simplified untagging in tcp_zerocopy_receive().
- Looked at find_vma() callers in drivers/, which allowed to identify a
  few other places where untagging is needed.
- Added patch "mm, arm64: untag user pointers in get_vaddr_frames".
- Added patch "drm/amdgpu, arm64: untag user pointers in
  amdgpu_ttm_tt_get_user_pages".
- Added patch "drm/radeon, arm64: untag user pointers in
  radeon_ttm_tt_pin_userptr".
- Added patch "IB/mlx4, arm64: untag user pointers in mlx4_get_umem_mr".
- Added patch "media/v4l2-core, arm64: untag user pointers in
  videobuf_dma_contig_user_get".
- Added patch "tee/optee, arm64: untag user pointers in check_mem_type".
- Added patch "vfio/type1, arm64: untag user pointers".

Changes in v12:
- Changed untagging in tcp_zerocopy_receive() to also untag zc->address.
- Fixed untagging in prctl_set_mm* to only untag pointers for vma lookups
  and validity checks, but leave them as is for actual user space accesses.
- Updated the link to the v2 of the "arm64 relaxed ABI" patchset [3].
- Dropped the documentation patch, as the "arm64 relaxed ABI" patchset [3]
  handles that.

Changes in v11:
- Added "uprobes, arm64: untag user pointers in find_active_uprobe" patch.
- Added "bpf, arm64: untag user pointers in stack_map_get_build_id_offset"
  patch.
- Fixed "tracing, arm64: untag user pointers in seq_print_user_ip" to
  correctly perform subtration with a tagged addr.
- Moved untagged_addr() from SYSCALL_DEFINE3(mprotect) and
  SYSCALL_DEFINE4(pkey_mprotect) to do_mprotect_pkey().
- Moved untagged_addr() definition for other arches from
  include/linux/memory.h to include/linux/mm.h.
- Changed untagging in strn*_user() to perform userspace accesses through
  tagged pointers.
- Updated the documentation to mention that passing tagged pointers to
  memory syscalls is allowed.
- Updated the test to use malloc'ed memory instead of stack memory.

Changes in v10:
- Added "mm, arm64: untag user pointers passed to memory syscalls" back.
- New patch "fs, arm64: untag user pointers in fs/userfaultfd.c".
- New patch "net, arm64: untag user pointers in tcp_zerocopy_receive".
- New patch "kernel, arm64: untag user pointers in prctl_set_mm*".
- New patch "tracing, arm64: untag user pointers in seq_print_user_ip".

Changes in v9:
- Rebased onto 4.20-rc6.
- Used u64 instead of __u64 in type casts in the untagged_addr macro for
  arm64.
- Added braces around (addr) in the untagged_addr macro for other arches.

Changes in v8:
- Rebased onto 65102238 (4.20-rc1).
- Added a note to the cover letter on why syscall wrappers/shims that untag
  user pointers won't work.
- Added a note to the cover letter that this patchset has been merged into
  the Pixel 2 kernel tree.
- Documentation fixes, in particular added a list of syscalls that don't
  support tagged user pointers.

Changes in v7:
- Rebased onto 17b57b18 (4.19-rc6).
- Dropped the "arm64: untag user address in __do_user_fault" patch, since
  the existing patches already handle user faults properly.
- Dropped the "usb, arm64: untag user addresses in devio" patch, since the
  passed pointer must come from a vma and therefore be untagged.
- Dropped the "arm64: annotate user pointers casts detected by sparse"
  patch (see the discussion to the replies of the v6 of this patchset).
- Added more context to the cover letter.
- Updated Documentation/arm64/tagged-pointers.txt.

Changes in v6:
- Added annotations for user pointer casts found by sparse.
- Rebased onto 050cdc6c (4.19-rc1+).

Changes in v5:
- Added 3 new patches that add untagging to places found with static
  analysis.
- Rebased onto 44c929e1 (4.18-rc8).

Changes in v4:
- Added a selftest for checking that passing tagged pointers to the
  kernel succeeds.
- Rebased onto 81e97f013 (4.18-rc1+).

Changes in v3:
- Rebased onto e5c51f30 (4.17-rc6+).
- Added linux-arch@ to the list of recipients.

Changes in v2:
- Rebased onto 2d618bdf (4.17-rc3+).
- Removed excessive untagging in gup.c.
- Removed untagging pointers returned from __uaccess_mask_ptr.

Changes in v1:
- Rebased onto 4.17-rc1.

Changes in RFC v2:
- Added "#ifndef untagged_addr..." fallback in linux/uaccess.h instead of
  defining it for each arch individually.
- Updated Documentation/arm64/tagged-pointers.txt.
- Dropped "mm, arm64: untag user addresses in memory syscalls".
- Rebased onto 3eb2ce82 (4.16-rc7).

Signed-off-by: Andrey Konovalov <andreyknvl@google.com>

Andrey Konovalov (16):
  uaccess: add untagged_addr definition for other arches
  arm64: untag user pointers in access_ok and __uaccess_mask_ptr
  lib, arm64: untag user pointers in strn*_user
  mm: untag user pointers in do_pages_move
  arm64: untag user pointers passed to memory syscalls
  mm, arm64: untag user pointers in mm/gup.c
  mm, arm64: untag user pointers in get_vaddr_frames
  fs, arm64: untag user pointers in copy_mount_options
  fs, arm64: untag user pointers in fs/userfaultfd.c
  drm/amdgpu, arm64: untag user pointers
  drm/radeon, arm64: untag user pointers in radeon_gem_userptr_ioctl
  IB, arm64: untag user pointers in ib_uverbs_(re)reg_mr()
  media/v4l2-core, arm64: untag user pointers in
    videobuf_dma_contig_user_get
  tee, arm64: untag user pointers in tee_shm_register
  vfio/type1, arm64: untag user pointers in vaddr_get_pfn
  selftests, arm64: add a selftest for passing tagged pointers to kernel

 arch/arm64/include/asm/uaccess.h              | 10 +++--
 .../gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c  |  2 +-
 drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c       |  2 +
 drivers/gpu/drm/radeon/radeon_gem.c           |  2 +
 drivers/infiniband/core/uverbs_cmd.c          |  4 ++
 drivers/media/v4l2-core/videobuf-dma-contig.c |  9 ++--
 drivers/tee/tee_shm.c                         |  1 +
 drivers/vfio/vfio_iommu_type1.c               |  2 +
 fs/namespace.c                                |  2 +-
 fs/userfaultfd.c                              | 22 +++++-----
 include/linux/mm.h                            |  4 ++
 lib/strncpy_from_user.c                       |  3 +-
 lib/strnlen_user.c                            |  3 +-
 mm/frame_vector.c                             |  2 +
 mm/gup.c                                      |  4 ++
 mm/madvise.c                                  |  2 +
 mm/mempolicy.c                                |  3 ++
 mm/migrate.c                                  |  1 +
 mm/mincore.c                                  |  2 +
 mm/mlock.c                                    |  4 ++
 mm/mprotect.c                                 |  2 +
 mm/mremap.c                                   |  2 +
 mm/msync.c                                    |  2 +
 tools/testing/selftests/arm64/.gitignore      |  1 +
 tools/testing/selftests/arm64/Makefile        | 22 ++++++++++
 .../testing/selftests/arm64/run_tags_test.sh  | 12 ++++++
 tools/testing/selftests/arm64/tags_lib.c      | 42 +++++++++++++++++++
 tools/testing/selftests/arm64/tags_test.c     | 18 ++++++++
 28 files changed, 163 insertions(+), 22 deletions(-)
 create mode 100644 tools/testing/selftests/arm64/.gitignore
 create mode 100644 tools/testing/selftests/arm64/Makefile
 create mode 100755 tools/testing/selftests/arm64/run_tags_test.sh
 create mode 100644 tools/testing/selftests/arm64/tags_lib.c
 create mode 100644 tools/testing/selftests/arm64/tags_test.c
```
#### [RFC][Patch v10 0/2] mm: Support for page hinting 
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c

This patch series proposes an efficient mechanism for communicating free memory
from a guest to its hypervisor. It especially enables guests with no page cache
(e.g., nvdimm, virtio-pmem) or with small page caches (e.g., ram > disk) to
rapidly hand back free memory to the hypervisor.
This approach has a minimal impact on the existing core-mm infrastructure.

Measurement results (measurement details appended to this email):
* With active page hinting, 3 more guests could be launched each of 5 GB(total 
5 vs. 2) on a 15GB (single NUMA) system without swapping.
* With active page hinting, on a system with 15 GB of (single NUMA) memory and
4GB of swap, the runtime of "memhog 6G" in 3 guests (run sequentially) resulted
in the last invocation to only need 37s compared to 3m35s without page hinting.

This approach tracks all freed pages of the order MAX_ORDER - 2 in bitmaps.
A new hook after buddy merging is used to set the bits in the bitmap.
Currently, the bits are only cleared when pages are hinted, not when pages are
re-allocated.

Bitmaps are stored on a per-zone basis and are protected by the zone lock. A
workqueue asynchronously processes the bitmaps as soon as a pre-defined memory
threshold is met, trying to isolate and report pages that are still free.

The isolated pages are reported via virtio-balloon, which is responsible for
sending batched pages to the host synchronously. Once the hypervisor processed
the hinting request, the isolated pages are returned back to the buddy.

The key changes made in this series compared to v9[1] are:
* Pages only in the chunks of "MAX_ORDER - 2" are reported to the hypervisor to
not break up the THP.
* At a time only a set of 16 pages can be isolated and reported to the host to
avoids any false OOMs.
* page_hinting.c is moved under mm/ from virt/kvm/ as the feature is dependent
on virtio and not on KVM itself. This would enable any other hypervisor to use
this feature by implementing virtio devices.
* The sysctl variable is replaced with a virtio-balloon parameter to
enable/disable page-hinting.

Pending items:
* Test device assigned guests to ensure that hinting doesn't break it.
* Follow up on VIRTIO_BALLOON_F_PAGE_POISON's device side support.
* Compare reporting free pages via vring with vhost.
* Decide between MADV_DONTNEED and MADV_FREE.
* Look into memory hotplug, more efficient locking, possible races when
disabling.
* Come up with proper/traceable error-message/logs.
* Minor reworks and simplifications (e.g., virtio protocol).

Benefit analysis:
1. Use-case - Number of guests that can be launched without swap usage
NUMA Nodes = 1 with 15 GB memory
Guest Memory = 5 GB
Number of cores in guest = 1
Workload = test allocation program allocates 4GB memory, touches it via memset
and exits.
Procedure =
The first guest is launched and once its console is up, the test allocation
program is executed with 4 GB memory request (Due to this the guest occupies
almost 4-5 GB of memory in the host in a system without page hinting). Once
this program exits at that time another guest is launched in the host and the
same process is followed. It is continued until the swap is not used.

Results:
Without hinting = 3, swap usage at the end 1.1GB.
With hinting = 5, swap usage at the end 0.

2. Use-case - memhog execution time
Guest Memory = 6GB
Number of cores = 4
NUMA Nodes = 1 with 15 GB memory
Process: 3 Guests are launched and the ‘memhog 6G’ execution time is monitored
one after the other in each of them.
Without Hinting - Guest1:47s, Guest2:53s, Guest3:3m35s, End swap usage: 3.5G
With Hinting - Guest1:40s, Guest2:44s, Guest3:37s, End swap usage: 0

Performance analysis:
1. will-it-scale's page_faul1:
Guest Memory = 6GB
Number of cores = 24

Without Hinting:
tasks,processes,processes_idle,threads,threads_idle,linear
0,0,100,0,100,0
1,315890,95.82,317633,95.83,317633
2,570810,91.67,531147,91.94,635266
3,826491,87.54,713545,88.53,952899
4,1087434,83.40,901215,85.30,1270532
5,1277137,79.26,916442,83.74,1588165
6,1503611,75.12,1113832,79.89,1905798
7,1683750,70.99,1140629,78.33,2223431
8,1893105,66.85,1157028,77.40,2541064
9,2046516,62.50,1179445,76.48,2858697
10,2291171,58.57,1209247,74.99,3176330
11,2486198,54.47,1217265,75.13,3493963
12,2656533,50.36,1193392,74.42,3811596
13,2747951,46.21,1185540,73.45,4129229
14,2965757,42.09,1161862,72.20,4446862
15,3049128,37.97,1185923,72.12,4764495
16,3150692,33.83,1163789,70.70,5082128
17,3206023,29.70,1174217,70.11,5399761
18,3211380,25.62,1179660,69.40,5717394
19,3202031,21.44,1181259,67.28,6035027
20,3218245,17.35,1196367,66.75,6352660
21,3228576,13.26,1129561,66.74,6670293
22,3207452,9.15,1166517,66.47,6987926
23,3153800,5.09,1172877,61.57,7305559
24,3184542,0.99,1186244,58.36,7623192

With Hinting:
0,0,100,0,100,0
1,306737,95.82,305130,95.78,306737
2,573207,91.68,530453,91.92,613474
3,810319,87.53,695281,88.58,920211
4,1074116,83.40,880602,85.48,1226948
5,1308283,79.26,1109257,81.23,1533685
6,1501987,75.12,1093661,80.19,1840422
7,1695300,70.99,1104207,79.03,2147159
8,1901523,66.85,1193613,76.90,2453896
9,2051288,62.73,1200913,76.22,2760633
10,2275771,58.60,1192992,75.66,3067370
11,2435016,54.48,1191472,74.66,3374107
12,2623114,50.35,1196911,74.02,3680844
13,2766071,46.22,1178589,73.02,3987581
14,2932163,42.10,1166414,72.96,4294318
15,3000853,37.96,1177177,72.62,4601055
16,3113738,33.85,1165444,70.54,4907792
17,3132135,29.77,1165055,68.51,5214529
18,3175121,25.69,1166969,69.27,5521266
19,3205490,21.61,1159310,65.65,5828003
20,3220855,17.52,1171827,62.04,6134740
21,3182568,13.48,1138918,65.05,6441477
22,3130543,9.30,1128185,60.60,6748214
23,3087426,5.15,1127912,55.36,7054951
24,3099457,1.04,1176100,54.96,7361688

[1] https://lkml.org/lkml/2019/3/6/413
```
#### [PATCHv6 0/3] vfio/mdev: Improve vfio/mdev core module
##### From: Parav Pandit <parav@mellanox.com>

```c

As we would like to use mdev subsystem for wider use case as
discussed in [1], [2] apart from an offline discussion.
This use case is also discussed with wider forum in [4] in track
'Lightweight NIC HW functions for container offload use cases'.

This series is prep-work and improves vfio/mdev module in following ways.

Patch-1 Improves the mdev create/remove sequence to match Linux
bus, device model
Patch-2 Avoid recreating remove file on stale device to eliminate
call trace
Patch-3 Fix race conditions of create/remove with parent removal.
This is improved version than using srcu as srcu can take seconds
to minutes.

This series is tested using
(a) mtty with VM using vfio_mdev driver for positive tests and device
removal while device in use by VM using vfio_mdev driver.

(b) mlx5 core driver using RFC patches [3] and internal patches.
Internal patches are large and cannot be combined with this prep-work
patches. It will posted once prep-work completes.

[1] https://www.spinics.net/lists/netdev/msg556978.html
[2] https://lkml.org/lkml/2019/3/7/696
[3] https://lkml.org/lkml/2019/3/8/819
[4] https://netdevconf.org/0x13/session.html?workshop-hardware-offload
---
Changelog:
---
v5->v6:
 - Fixed mdev leak on fail to acquire semaphore
 - Corrected access to accessed
 - Avoided using ret and directly checking try_lock result
v4->v5:
 - Addressed comments from Alex Williamson
 - Added comment around mdev_device_remove_common()
 - Added lockdep assert to catch any missing lock
 - Corrected 'system' to 'sequence' in 2nd patch commit log
 - Refactored mdev_device_remove_cb() to remove unused parent
 - Added Cornelia's Reviewed-by signature to already reviewed patches 1, 2.
v3->v4:
 - Addressed comments from Cornelia for unbalanced mutex_unlock
 - Correct typo of subsquent to subsequent in patch-1 commit log
 - Instead of using refcount and completion, using rwsem to synchronize
   between mdev creation/deletion and parent unregistration
v2->v3:
 - Addressed comment from Cornelia
 - Corrected several errors in commit log, updated commit log
 - Dropped already merged 7 patches
v1->v2:
 - Addressed comments from Alex
 - Rebased
 - Inserted the device checking loop in Patch-6 as original code
 - Added patch 7 to 10
 - Added fixes for race condition in create/remove with parent removal
   Patch-10 uses simplified refcount and completion, instead of srcu
   which might take seconds to minutes on busy system.
 - Added fix for device create/remove sequence to match
   Linux device, bus model
v0->v1:
 - Dropped device placement on bus sequence patch for this series
 - Addressed below comments from Alex, Kirti, Maxim.
 - Added Review-by tag for already reviewed patches.
 - Dropped incorrect patch of put_device().
 - Corrected Fixes commit tag for sysfs remove sequence fix
 - Split last 8th patch to smaller refactor and fixes patch
 - Following coding style commenting format
 - Fixed accidental delete of mutex_lock in mdev_unregister_device
 - Renamed remove helped to mdev_device_remove_common().
 - Rebased for uuid/guid change


Parav Pandit (3):
  vfio/mdev: Improve the create/remove sequence
  vfio/mdev: Avoid creating sysfs remove file on stale device removal
  vfio/mdev: Synchronize device create/remove with parent removal

 drivers/vfio/mdev/mdev_core.c    | 135 +++++++++++++++----------------
 drivers/vfio/mdev/mdev_private.h |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c   |   6 +-
 3 files changed, 68 insertions(+), 77 deletions(-)
```
#### [patch 0/3] cpuidle-haltpoll driver (v2)
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

The cpuidle-haltpoll driver allows the guest vcpus to poll for a specified
amount of time before halting. This provides the following benefits
to host side polling:

        1) The POLL flag is set while polling is performed, which allows
           a remote vCPU to avoid sending an IPI (and the associated
           cost of handling the IPI) when performing a wakeup.

        2) The HLT VM-exit cost can be avoided.

The downside of guest side polling is that polling is performed
even with other runnable tasks in the host.

Results comparing halt_poll_ns and server/client application
where a small packet is ping-ponged:

host                                        --> 31.33
halt_poll_ns=300000 / no guest busy spin    --> 33.40   (93.8%)
halt_poll_ns=0 / guest_halt_poll_ns=300000  --> 32.73   (95.7%)

For the SAP HANA benchmarks (where idle_spin is a parameter
of the previous version of the patch, results should be the
same):

hpns == halt_poll_ns

                          idle_spin=0/   idle_spin=800/    idle_spin=0/
                          hpns=200000    hpns=0            hpns=800000
DeleteC06T03 (100 thread) 1.76           1.71 (-3%)        1.78   (+1%)
InsertC16T02 (100 thread) 2.14           2.07 (-3%)        2.18   (+1.8%)
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)	   1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)	   4.53   (-5%)

V2:

- Move from x86 to generic code (Paolo/Christian).
- Add auto-tuning logic (Paolo).
- Add MSR to disable host side polling (Paolo).
```
