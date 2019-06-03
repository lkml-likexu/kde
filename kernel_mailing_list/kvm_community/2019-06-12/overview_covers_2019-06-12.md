

#### [PATCH v1 0/5] perf kvm: Add stat support on arm64
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c

'perf kvm stat report/record' generates a statistical analysis of KVM
events and can be used to analyze guest exit reasons. This series tries
to add stat support on arm64 (Port perf-kvm-stat to arm64 - this is
already supported on x86).

"record" enables recording of two pair of tracepoints:
 - "kvm:kvm_entry" and "kvm:kvm_exit"
 - "kvm:kvm_trap_enter" and "kvm:kvm_trap_exit"
"report" reports statistical analysis of guest exit&trap events.

To record kvm events on the host:
 # perf kvm stat record -a

To report kvm VM EXIT events:
 # perf kvm stat report --event=vmexit

To report kvm VM TRAP (synchronous exceptions) events:
 # perf kvm stat report --event=trap

More information can be found at tools/perf/Documentation/perf-kvm.txt.

* Patch 1-2 touch KVM/ARM side, with #1 is cleanup and #2 is preparation
  for perf-kvm-stat support.
* Patch 3-5 touch perf side.
* Patch 3 adds support for get_cpuid() function on arm64. *RFC!*
* Patch 4 adds support for perf-kvm-stat on arm64, with VM-EXIT events.
* Patch 5 adds support to report TRAP-EVENT events.

Any suggestions, comments and test results will be appreciated.

Thanks,
zenghui
---

Zenghui Yu (5):
  KVM: arm/arm64: Remove kvm_mmio_emulate tracepoint
  KVM: arm/arm64: Adjust entry/exit and trap related tracepoints
  perf tools arm64: Add support for get_cpuid() function
  perf,kvm/arm64: Add stat support on arm64
  perf,kvm/arm64: perf-kvm-stat to report VM TRAP

 arch/arm64/kvm/handle_exit.c                     |   3 +
 arch/arm64/kvm/trace.h                           |  35 +++++++
 tools/perf/arch/arm64/Makefile                   |   2 +
 tools/perf/arch/arm64/util/Build                 |   1 +
 tools/perf/arch/arm64/util/aarch64_guest_exits.h |  91 +++++++++++++++++
 tools/perf/arch/arm64/util/header.c              |  74 +++++++++-----
 tools/perf/arch/arm64/util/kvm-stat.c            | 125 +++++++++++++++++++++++
 virt/kvm/arm/arm.c                               |   4 +-
 virt/kvm/arm/trace.h                             |  42 ++------
 9 files changed, 317 insertions(+), 60 deletions(-)
 create mode 100644 tools/perf/arch/arm64/util/aarch64_guest_exits.h
 create mode 100644 tools/perf/arch/arm64/util/kvm-stat.c
```
#### [PATCH v3 0/5] KVM: LAPIC: Optimize timer latency further
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Advance lapic timer tries to hidden the hypervisor overhead between the 
host emulated timer fires and the guest awares the timer is fired. However, 
it just hidden the time between apic_timer_fn/handle_preemption_timer -> 
wait_lapic_expire, instead of the real position of vmentry which is 
mentioned in the orignial commit d0659d946be0 ("KVM: x86: add option to 
advance tscdeadline hrtimer expiration"). There is 700+ cpu cycles between 
the end of wait_lapic_expire and before world switch on my haswell desktop.

This patchset tries to narrow the last gap(wait_lapic_expire -> world switch), 
it takes the real overhead time between apic_timer_fn/handle_preemption_timer
and before world switch into consideration when adaptively tuning timer 
advancement. The patchset can reduce 40% latency (~1600+ cycles to ~1000+ 
cycles on a haswell desktop) for kvm-unit-tests/tscdeadline_latency when 
testing busy waits.

v2 -> v3:
 * expose 'kvm_timer.timer_advance_ns' to userspace
 * move the tracepoint below guest_exit_irqoff()
 * move wait_lapic_expire() before flushing the L1

v1 -> v2:
 * fix indent in patch 1/4
 * remove the wait_lapic_expire() tracepoint and expose by debugfs
 * move the call to wait_lapic_expire() into vmx.c and svm.c

Wanpeng Li (5):
  KVM: LAPIC: Extract adaptive tune timer advancement logic
  KVM: LAPIC: Fix lapic_timer_advance_ns parameter overflow
  KVM: LAPIC: Expose per-vCPU timer_advance_ns to userspace
  KVM: LAPIC: Delay trace advance expire delta
  KVM: LAPIC: Optimize timer latency further

 arch/x86/kvm/debugfs.c | 16 +++++++++++++
 arch/x86/kvm/lapic.c   | 62 +++++++++++++++++++++++++++++---------------------
 arch/x86/kvm/lapic.h   |  3 ++-
 arch/x86/kvm/svm.c     |  4 ++++
 arch/x86/kvm/vmx/vmx.c |  4 ++++
 arch/x86/kvm/x86.c     |  7 +++---
 6 files changed, 65 insertions(+), 31 deletions(-)
```
#### [PATCH v5 0/8] s390: virtio: support protected virtualization
##### From: Halil Pasic <pasic@linux.ibm.com>

```c

Enhanced virtualization protection technology may require the use of
bounce buffers for I/O. While support for this was built into the virtio
core, virtio-ccw wasn't changed accordingly.

Some background on technology (not part of this series) and the
terminology used.

* Protected Virtualization (PV):

Protected Virtualization guarantees, that non-shared memory of a  guest
that operates in PV mode private to that guest. I.e. any attempts by the
hypervisor or other guests to access it will result in an exception. If
supported by the environment (machine, KVM, guest VM) a guest can decide
to change into PV mode by doing the appropriate ultravisor calls.

* Ultravisor:

A hardware/firmware entity that manages PV guests, and polices access to
their memory. A PV guest prospect needs to interact with the ultravisor,
to enter PV mode, and potentially to share pages (for I/O which should
be encrypted by the guest). A guest interacts with the ultravisor via so
called ultravisor calls. A hypervisor needs to interact with the
ultravisor to facilitate interpretation, emulation and swapping. A
hypervisor  interacts with the ultravisor via ultravisor calls and via
the SIE state description. Generally the ultravisor sanitizes hypervisor
inputs so that the guest can not be corrupted (except for denial of
service.


What needs to be done
=====================

Thus what needs to be done to bring virtio-ccw up to speed with respect
to protected virtualization is:
* use some 'new' common virtio stuff
* make sure that virtio-ccw specific stuff uses shared memory when
  talking to the hypervisor (except control/communication blocks like ORB,
  these are handled by the ultravisor)
* make sure the DMA API does what is necessary to talk through shared
  memory if we are a protected virtualization guest.
* make sure the common IO layer plays along as well (airqs, sense).


Important notes
================

* This patch set is based on Martins features branch
 (git://git.kernel.org/pub/scm/linux/kernel/git/s390/linux.git branch
 'features').

* Documentation is still very sketchy. I'm committed to improving this,
  but I'm currently hampered by some dependencies currently.  

* The existing naming in the common infrastructure (kernel internal
  interfaces) is pretty much based on the AMD SEV terminology. Thus the
  names aren't always perfect. There might be merit to changing these
  names to more abstract ones. I did not put much thought into that at
  the current stage.

* Testing: Please use iommu_platform=on for any virtio devices you are
  going to test this code with (so virtio actually uses the DMA API).

@Sebastian: I kept your r-b on patch 2 "s390/cio: introduce DMA pools to
cio" despite the small changes pointed out below. Please do complain if
it ain't OK for you!

Change log
==========

v4 --> v5:
* work around dma_pool API not tolerating NULL dma pool (patch 4)
* make the genpool based dma pools API  tolerate NULL genpool (patch 2)
* fix typo (patch 2)
* fix unintended code move (patch 7)
* add more r-b's



v3 --> v4
* fixed cleanup in css_bus_init() (Connie)
* made cio.h include genalloc.h instead of a forward declaration
  (Connie)
* added comments about dma_mask/coherent_dma_mask values (Connie)
* fixed error handling in virtio_ccw_init() (Connie)
* got rid of the *vc_dma* wrappers (Connie)
* added some Reviewed-bys
* rebased on top of current master, no changes were necessary

v2 --> v3:
* patch 2/8
    potential cio_dma_pool_init() returning NULL issue fixed
    potential cio_gp_dma_create() returning NULL issue fixed
    warning issues with doc type comments fixed
    unused define statement removed 
* patch 3/8
    potential cio_gp_dma_create() returning NULL issue fixed
    whitespace issue fixed
    warning issues with doc type comments fixed
* patch 8/8
    potential cio_dma_zalloc() returning NULL issue fixed

v1 --> v2:
* patch "virtio/s390: use vring_create_virtqueue" went already upstream
* patch "virtio/s390: DMA support for virtio-ccw" went already upstream
* patch "virtio/s390: enable packed ring" went already upstream
* Made dev.dma_mask point to dev.coherent_dma_mask for css, subchannel
  and ccw devices.
* While rebasing 's390/airq: use DMA memory for adapter interrupts' the
  newly introduced kmem_cache  was replaced with an equivalent dma_pool;
  the kalloc() allocations are now replaced with cio_dma_zalloc()
  allocations to avoid wasting almost a full page.
* Made virtio-ccw use the new AIRQ_IV_CACHELINE flag.
* fixed all remaining checkpatch issues

RFC --> v1:
* Fixed bugs found by Connie (may_reduce and handling reduced,  warning,
  split move -- thanks Connie!).
* Fixed console bug found by Sebastian (thanks Sebastian!).
* Removed the completely useless duplicate of dma-mapping.h spotted by
  Christoph (thanks Christoph!).
* Don't use the global DMA pool for subchannel and ccw device
  owned memory as requested by Sebastian. Consequences:
	* Both subchannel and ccw devices have their dma masks
	now (both specifying 31 bit addressable)
	* We require at least 2 DMA pages per ccw device now, most of
	this memory is wasted though.
	* DMA memory allocated by virtio is also 31 bit addressable now
        as virtio uses the parent (which is the ccw device).
* Enabled packed ring.
* Rebased onto Martins feature branch; using the actual uv (ultravisor)
  interface instead of TODO comments.
* Added some explanations to the cover letter (Connie, David).
* Squashed a couple of patches together and fixed some text stuff. 

Halil Pasic (8):
  s390/mm: force swiotlb for protected virtualization
  s390/cio: introduce DMA pools to cio
  s390/cio: add basic protected virtualization support
  s390/airq: use DMA memory for adapter interrupts
  virtio/s390: use cacheline aligned airq bit vectors
  virtio/s390: add indirection to indicators access
  virtio/s390: use DMA memory for ccw I/O and classic notifiers
  virtio/s390: make airq summary indicators DMA

 arch/s390/Kconfig                   |   5 +
 arch/s390/include/asm/airq.h        |   2 +
 arch/s390/include/asm/ccwdev.h      |   4 +
 arch/s390/include/asm/cio.h         |  11 ++
 arch/s390/include/asm/mem_encrypt.h |  18 ++
 arch/s390/mm/init.c                 |  47 ++++++
 drivers/s390/cio/airq.c             |  37 +++--
 drivers/s390/cio/ccwreq.c           |   9 +-
 drivers/s390/cio/cio.h              |   2 +
 drivers/s390/cio/css.c              | 134 ++++++++++++++-
 drivers/s390/cio/device.c           |  68 ++++++--
 drivers/s390/cio/device_fsm.c       |  49 +++---
 drivers/s390/cio/device_id.c        |  20 ++-
 drivers/s390/cio/device_ops.c       |  21 ++-
 drivers/s390/cio/device_pgid.c      |  22 +--
 drivers/s390/cio/device_status.c    |  24 +--
 drivers/s390/cio/io_sch.h           |  20 ++-
 drivers/s390/virtio/virtio_ccw.c    | 246 +++++++++++++++-------------
 18 files changed, 538 insertions(+), 201 deletions(-)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h
```
#### [PATCH v17 00/15] arm64: untag user pointers passed to the kernel
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

The mmap and mremap (only new_addr) syscalls do not currently accept
tagged addresses. Architectures may interpret the tag as a background
colour for the corresponding vma.

Other memory syscalls (mprotect, etc.) don't do user memory accesses but
rather deal with memory ranges, and untagged pointers are better suited to
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

=== History

Changes in v17:
- The "uaccess: add noop untagged_addr definition" patch is dropped, as it
  was merged into upstream named as "uaccess: add noop untagged_addr
  definition".
- Merged "mm, arm64: untag user pointers in do_pages_move" into
  "mm, arm64: untag user pointers passed to memory syscalls".
- Added "arm64: Introduce prctl() options to control the tagged user
  addresses ABI" patch from Catalin.
- Add tags_lib.so to tools/testing/selftests/arm64/.gitignore.
- Added a comment clarifying untagged in mremap.
- Moved untagging back into mlx4_get_umem_mr() for the IB patch.

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

Andrey Konovalov (14):
  arm64: untag user pointers in access_ok and __uaccess_mask_ptr
  lib, arm64: untag user pointers in strn*_user
  mm, arm64: untag user pointers passed to memory syscalls
  mm, arm64: untag user pointers in mm/gup.c
  mm, arm64: untag user pointers in get_vaddr_frames
  fs, arm64: untag user pointers in copy_mount_options
  userfaultfd, arm64: untag user pointers
  drm/amdgpu, arm64: untag user pointers
  drm/radeon, arm64: untag user pointers in radeon_gem_userptr_ioctl
  IB/mlx4, arm64: untag user pointers in mlx4_get_umem_mr
  media/v4l2-core, arm64: untag user pointers in
    videobuf_dma_contig_user_get
  tee/shm, arm64: untag user pointers in tee_shm_register
  vfio/type1, arm64: untag user pointers in vaddr_get_pfn
  selftests, arm64: add a selftest for passing tagged pointers to kernel

Catalin Marinas (1):
  arm64: Introduce prctl() options to control the tagged user addresses
    ABI

 arch/arm64/include/asm/processor.h            |  6 ++
 arch/arm64/include/asm/thread_info.h          |  1 +
 arch/arm64/include/asm/uaccess.h              | 11 ++-
 arch/arm64/kernel/process.c                   | 67 +++++++++++++++++++
 .../gpu/drm/amd/amdgpu/amdgpu_amdkfd_gpuvm.c  |  2 +-
 drivers/gpu/drm/amd/amdgpu/amdgpu_gem.c       |  2 +
 drivers/gpu/drm/radeon/radeon_gem.c           |  2 +
 drivers/infiniband/hw/mlx4/mr.c               |  7 +-
 drivers/media/v4l2-core/videobuf-dma-contig.c |  9 +--
 drivers/tee/tee_shm.c                         |  1 +
 drivers/vfio/vfio_iommu_type1.c               |  2 +
 fs/namespace.c                                |  2 +-
 fs/userfaultfd.c                              | 22 +++---
 include/uapi/linux/prctl.h                    |  5 ++
 kernel/sys.c                                  | 16 +++++
 lib/strncpy_from_user.c                       |  3 +-
 lib/strnlen_user.c                            |  3 +-
 mm/frame_vector.c                             |  2 +
 mm/gup.c                                      |  4 ++
 mm/madvise.c                                  |  2 +
 mm/mempolicy.c                                |  3 +
 mm/migrate.c                                  |  2 +-
 mm/mincore.c                                  |  2 +
 mm/mlock.c                                    |  4 ++
 mm/mprotect.c                                 |  2 +
 mm/mremap.c                                   |  7 ++
 mm/msync.c                                    |  2 +
 tools/testing/selftests/arm64/.gitignore      |  2 +
 tools/testing/selftests/arm64/Makefile        | 22 ++++++
 .../testing/selftests/arm64/run_tags_test.sh  | 12 ++++
 tools/testing/selftests/arm64/tags_lib.c      | 62 +++++++++++++++++
 tools/testing/selftests/arm64/tags_test.c     | 18 +++++
 32 files changed, 282 insertions(+), 25 deletions(-)
 create mode 100644 tools/testing/selftests/arm64/.gitignore
 create mode 100644 tools/testing/selftests/arm64/Makefile
 create mode 100755 tools/testing/selftests/arm64/run_tags_test.sh
 create mode 100644 tools/testing/selftests/arm64/tags_lib.c
 create mode 100644 tools/testing/selftests/arm64/tags_test.c
```
#### [PATCH v13 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series is ready to be merged via nvdimm tree
 as discussed with Dan. We have ack/review on XFS, EXT4
 device mapper & VIRTIO patches.

 This version has minor changes in patch 2. Keeping all
 the existing r-o-bs. Jakob CCed also tested the patch
 series and confirmed the working of v9.
 ---

 This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [5] for virtio-pmem. Documented the impact of
 possible page cache side channel attacks with suggested
 countermeasures.

 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [7]
 on possible implications of page cache side channel attacks with 
 virtio pmem. After thorough analysis of details of known side 
 channel attacks, below are the suggestions:

 - Depends entirely on how host backing image file is mapped 
   into guest address space. 

 - virtio-pmem device emulation, by default shared mapping is used
   to map host backing file. It is recommended to use separate
   backing file at host side for every guest. This will prevent
   any possibility of executing common code from multiple guests
   and any chance of inferring guest local data based based on 
   execution time.

 - If backing file is required to be shared among multiple guests 
   it is recommended to don't support host page cache eviction 
   commands from the guest driver. This will avoid any possibility
   of inferring guest local data or host data from another guest. 

 - Proposed device specification [6] for virtio-pmem device with 
   details of possible security implications and suggested 
   countermeasures for device emulation.

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v12: [1] 
 - Minor changes(function name, dev_err -> dev_info & 
   make function static in virtio patch - [Cornelia]
 - Added r-o-b of Mike in patch 4

Changes from PATCH v11: [2] 
 - Change implmentation for setting of synchronous DAX type
   for device mapper - [Mike] 

Changes from PATCH v10:
 - Rebased on Linux-5.2-rc4

Changes from PATCH v9:
 - Kconfig help text add two spaces - Randy
 - Fixed libnvdimm 'bio' include warning - Dan
 - virtio-pmem, separate request/resp struct and 
   move to uapi file with updated license - DavidH
 - Use virtio32* type for req/resp endianess - DavidH
 - Added tested-by & ack-by of Jakob
 - Rebased to 5.2-rc1

Changes from PATCH v8:
 - Set device mapper synchronous if all target devices support - Dan
 - Move virtio_pmem.h to nvdimm directory  - Dan
 - Style, indentation & better error messages in patch 2 - DavidH
 - Added MST's ack in patch 2.

Changes from PATCH v7:
 - Corrected pending request queue logic (patch 2) - Jakub Staroń
 - Used unsigned long flags for passing DAXDEV_F_SYNC (patch 3) - Dan
 - Fixed typo =>  vma 'flag' to 'vm_flag' (patch 4)
 - Added rob in patch 6 & patch 2

Changes from PATCH v6: 
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: 
  Changes suggested in by - [Cornelia, Yuval]
- Remove assignment chaining in virtio driver
- Better error message and remove not required free
- Check nd_region before use

  Changes suggested by - [Jan Kara]
- dax_synchronous() for !CONFIG_DAX
- Correct 'daxdev_mapping_supported' comment and non-dax implementation

  Changes suggested by - [Dan Williams]
- Pass meaningful flag 'DAXDEV_F_SYNC' to alloc_dax
- Gate nvdimm_flush instead of additional async parameter
- Move block chaining logic to flush callback than common nvdimm_flush
- Use NULL flush callback for generic flush for better readability [Dan, Jan]

- Use virtio device id 27 from 25(already used) - [MST]

Changes from PATCH v4:
- Factor out MAP_SYNC supported functionality to a common helper
				[Dave, Darrick, Jan]
- Comment, indentation and virtqueue_kick failure handle - Yuval Shaia

Changes from PATCH v3: 
- Use generic dax_synchronous() helper to check for DAXDEV_SYNC 
  flag - [Dan, Darrick, Jan]
- Add 'is_nvdimm_async' function
- Document page cache side channel attacks implications & 
  countermeasures - [Dave Chinner, Michael]

Changes from PATCH v2: 
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: 
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Pankaj Gupta (7):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   dm: dm: Enable synchronous dax
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/6/11/831
[2] https://lkml.org/lkml/2019/6/10/209
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://marc.info/?l=qemu-devel&m=155860751202202&w=2
[6] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[7] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   19 +++++
 drivers/md/dm-table.c            |   24 +++++--
 drivers/md/dm.c                  |    5 -
 drivers/md/dm.h                  |    5 +
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  125 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 ++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   55 +++++++++++++++++
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   26 +++++++-
 include/linux/libnvdimm.h        |   10 ++-
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   35 ++++++++++
 21 files changed, 489 insertions(+), 33 deletions(-)
```
#### [v2, 0/4] x86 instruction emulator fuzzing
##### From: Sam Caccavale <samcacc@amazon.de>

```c

Dear all,

This series aims to provide an entrypoint for, and fuzz KVM's x86 instruction
emulator from userspace.  It mirrors Xen's application of the AFL fuzzer to
it's instruction emulator in the hopes of discovering vulnerabilities.
Since this entrypoint also allows arbitrary execution of the emulators code
from userspace, it may also be useful for testing.

The current 4 patches build the emulator and 2 harnesses: simple-harness is
an example of unit testing; afl-harness is a frontend for the AFL fuzzer.

Patches
=======

- 01: Builds and links afl-harness with the required kernel objects.
- 02: Introduces the minimal set of emulator operations and supporting code
to emulate simple instructions.
- 03: Demonstrates simple-harness as a unit test.
- 04: Adds scripts for install, running, and crash triage.

Any comments/suggestions are greatly appreciated.

Best,
Sam Caccavale

Sam Caccavale (4):
  Build target for emulate.o as a userspace binary
  Emulate simple x86 instructions in userspace
  Demonstrating unit testing via simple-harness
  Added scripts for filtering, building, deploying

 tools/Makefile                                |   9 +
 tools/fuzz/x86ie/.gitignore                   |   2 +
 tools/fuzz/x86ie/Makefile                     |  54 +++
 tools/fuzz/x86ie/README.md                    |  12 +
 tools/fuzz/x86ie/afl-harness.c                | 151 +++++++
 tools/fuzz/x86ie/common.h                     |  87 ++++
 tools/fuzz/x86ie/emulator_ops.c               | 398 ++++++++++++++++++
 tools/fuzz/x86ie/emulator_ops.h               | 120 ++++++
 tools/fuzz/x86ie/scripts/afl-many             |  28 ++
 tools/fuzz/x86ie/scripts/bin.sh               |  49 +++
 tools/fuzz/x86ie/scripts/build.sh             |  32 ++
 tools/fuzz/x86ie/scripts/coalesce.sh          |   6 +
 tools/fuzz/x86ie/scripts/deploy.sh            |   9 +
 tools/fuzz/x86ie/scripts/deploy_remote.sh     |   9 +
 tools/fuzz/x86ie/scripts/gen_output.sh        |  11 +
 tools/fuzz/x86ie/scripts/install_afl.sh       |  14 +
 .../fuzz/x86ie/scripts/install_deps_ubuntu.sh |   5 +
 tools/fuzz/x86ie/scripts/rebuild.sh           |   6 +
 tools/fuzz/x86ie/scripts/run.sh               |  10 +
 tools/fuzz/x86ie/scripts/summarize.sh         |   9 +
 tools/fuzz/x86ie/simple-harness.c             |  42 ++
 tools/fuzz/x86ie/stubs.c                      |  56 +++
 tools/fuzz/x86ie/stubs.h                      |  52 +++
 23 files changed, 1171 insertions(+)
 create mode 100644 tools/fuzz/x86ie/.gitignore
 create mode 100644 tools/fuzz/x86ie/Makefile
 create mode 100644 tools/fuzz/x86ie/README.md
 create mode 100644 tools/fuzz/x86ie/afl-harness.c
 create mode 100644 tools/fuzz/x86ie/common.h
 create mode 100644 tools/fuzz/x86ie/emulator_ops.c
 create mode 100644 tools/fuzz/x86ie/emulator_ops.h
 create mode 100755 tools/fuzz/x86ie/scripts/afl-many
 create mode 100755 tools/fuzz/x86ie/scripts/bin.sh
 create mode 100755 tools/fuzz/x86ie/scripts/build.sh
 create mode 100755 tools/fuzz/x86ie/scripts/coalesce.sh
 create mode 100644 tools/fuzz/x86ie/scripts/deploy.sh
 create mode 100755 tools/fuzz/x86ie/scripts/deploy_remote.sh
 create mode 100755 tools/fuzz/x86ie/scripts/gen_output.sh
 create mode 100755 tools/fuzz/x86ie/scripts/install_afl.sh
 create mode 100755 tools/fuzz/x86ie/scripts/install_deps_ubuntu.sh
 create mode 100755 tools/fuzz/x86ie/scripts/rebuild.sh
 create mode 100755 tools/fuzz/x86ie/scripts/run.sh
 create mode 100755 tools/fuzz/x86ie/scripts/summarize.sh
 create mode 100644 tools/fuzz/x86ie/simple-harness.c
 create mode 100644 tools/fuzz/x86ie/stubs.c
 create mode 100644 tools/fuzz/x86ie/stubs.h
---
2.17.1




Amazon Development Center Germany GmbH
Krausenstr. 38
10117 Berlin
Geschaeftsfuehrung: Christian Schlaeger, Ralf Herbrich
Eingetragen am Amtsgericht Charlottenburg unter HRB 149173 B
Sitz: Berlin
Ust-ID: DE 289 237 879
```
#### [RFC 00/10] Process-local memory allocations for hiding KVM secrets
##### From: Marius Hillenbrand <mhillenb@amazon.de>

```c

The Linux kernel has a global address space that is the same for any
kernel code. This address space becomes a liability in a world with
processor information leak vulnerabilities, such as L1TF. With the right
cache load gadget, an attacker-controlled hyperthread pair can leak
arbitrary data via L1TF. Disabling hyperthreading is one recommended
mitigation, but it comes with a large performance hit for a wide range
of workloads.

An alternative mitigation is to not make certain data in the kernel
globally visible, but only when the kernel executes in the context of
the process where this data belongs to.

This patch series proposes to introduce a region for what we call
process-local memory into the kernel's virtual address space. Page
tables and mappings in that region will be exclusive to one address
space, instead of implicitly shared between all kernel address spaces.
Any data placed in that region will be out of reach of cache load
gadgets that execute in different address spaces. To implement
process-local memory, we introduce a new interface kmalloc_proclocal() /
kfree_proclocal() that allocates and maps pages exclusively into the
current kernel address space. As a first use case, we move architectural
state of guest CPUs in KVM out of reach of other kernel address spaces.

The patch set is a prototype for x86-64 that we have developed on top of
kernel 4.20.17 (with cherry-picked commit d253ca0c3865 "x86/mm/cpa: Add
set_direct_map_*() functions"). I am aware that the integration with KVM
will see some changes while rebasing to 5.x. Patches 7 and 8, in
particular, help make patch 9 more readable, but will be dropped in
rebasing. We have tested the code on both Intel and AMDs, launching VMs
in a loop. So far, we have not done in-depth performance evaluation.
Impact on starting VMs was within measurement noise.
---

Julian Stecklina (2):
  kvm, vmx: move CR2 context switch out of assembly path
  kvm, vmx: move register clearing out of assembly path

Marius Hillenbrand (8):
  x86/mm/kaslr: refactor to use enum indices for regions
  x86/speculation, mm: add process local virtual memory region
  x86/mm, mm,kernel: add teardown for process-local memory to mm cleanup
  mm: allocate virtual space for process-local memory
  mm: allocate/release physical pages for process-local memory
  kvm/x86: add support for storing vCPU state in process-local memory
  kvm, vmx: move gprs to process local memory
  kvm, x86: move guest FPU state into process local memory

 Documentation/x86/x86_64/mm.txt         |  11 +-
 arch/x86/Kconfig                        |   1 +
 arch/x86/include/asm/kvm_host.h         |  40 ++-
 arch/x86/include/asm/page_64.h          |   4 +
 arch/x86/include/asm/pgtable_64_types.h |  12 +
 arch/x86/include/asm/proclocal.h        |  11 +
 arch/x86/kernel/head64.c                |   8 +
 arch/x86/kvm/Kconfig                    |  10 +
 arch/x86/kvm/kvm_cache_regs.h           |   4 +-
 arch/x86/kvm/svm.c                      | 104 +++++--
 arch/x86/kvm/vmx.c                      | 213 ++++++++++-----
 arch/x86/kvm/x86.c                      |  31 ++-
 arch/x86/mm/Makefile                    |   1 +
 arch/x86/mm/dump_pagetables.c           |   9 +
 arch/x86/mm/fault.c                     |  19 ++
 arch/x86/mm/kaslr.c                     |  63 ++++-
 arch/x86/mm/proclocal.c                 | 136 +++++++++
 include/linux/mm_types.h                |  13 +
 include/linux/proclocal.h               |  35 +++
 kernel/fork.c                           |   6 +
 mm/Makefile                             |   1 +
 mm/proclocal.c                          | 348 ++++++++++++++++++++++++
 security/Kconfig                        |  18 ++
 23 files changed, 978 insertions(+), 120 deletions(-)
 create mode 100644 arch/x86/include/asm/proclocal.h
 create mode 100644 arch/x86/mm/proclocal.c
 create mode 100644 include/linux/proclocal.h
 create mode 100644 mm/proclocal.c
```
