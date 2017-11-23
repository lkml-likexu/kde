

#### [PATCH V2 0/8] KVM: PPC: Implement passthrough of emulated devices
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c

This patch series allows for emulated devices to be passed through to nested
guests, irrespective of at which level the device is being emulated.

Note that the emulated device must be using dma, not virtio.

For example, passing through an emulated e1000:

1. Emulate the device at L(n) for L(n+1)

qemu-system-ppc64 -netdev type=user,id=net0 -device e1000,netdev=net0

2. Assign the VFIO-PCI driver at L(n+1)

echo vfio-pci > /sys/bus/pci/devices/0000:00:00.0/driver_override
echo 0000:00:00.0 > /sys/bus/pci/drivers/e1000/unbind
echo 0000:00:00.0 > /sys/bus/pci/drivers/vfio-pci/bind
chmod 666 /dev/vfio/0

3. Pass the device through from L(n+1) to L(n+2)

qemu-system-ppc64 -device vfio-pci,host=0000:00:00.0

4. L(n+2) can now access the device which will be emulated at L(n)

V1 -> V2:
1/8: None
2/8: None
3/8: None
4/8: None
5/8: None
6/8: Account for L1 differing in endianess in kvmppc_complete_mmio_load()
7/8: None
8/8: None

Suraj Jitindar Singh (8):
  KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
  KVM: PPC: Book3S HV: Add function kvmhv_vcpu_is_radix()
  KVM: PPC: Book3S HV: Implement functions to access quadrants 1 & 2
  KVM: PPC: Add load_from_eaddr and store_to_eaddr to the kvmppc_ops
    struct
  KVM: PPC: Update kvmppc_st and kvmppc_ld to use quadrants
  KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L2
    guest
  KVM: PPC: Introduce new hcall H_COPY_TOFROM_GUEST to access quadrants
    1 & 2
  KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L3
    guest

 arch/powerpc/include/asm/hvcall.h        |   1 +
 arch/powerpc/include/asm/kvm_book3s.h    |  10 ++-
 arch/powerpc/include/asm/kvm_book3s_64.h |  13 ++++
 arch/powerpc/include/asm/kvm_host.h      |   3 +
 arch/powerpc/include/asm/kvm_ppc.h       |   4 ++
 arch/powerpc/kernel/exceptions-64s.S     |   9 +++
 arch/powerpc/kvm/book3s_64_mmu_radix.c   |  97 ++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv.c             |  58 ++++++++++++++--
 arch/powerpc/kvm/book3s_hv_nested.c      | 114 +++++++++++++++++++++++++++++--
 arch/powerpc/kvm/powerpc.c               |  30 +++++++-
 arch/powerpc/mm/fault.c                  |   1 +
 11 files changed, 325 insertions(+), 15 deletions(-)
```
#### [PATCH net 0/4] Fix various issue of vhost
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series tries to fix various issues of vhost:

- Patch 1 adds a missing write barrier between used idx updating and
  logging.
- Patch 2-3 brings back the protection of device IOTLB through vq
  mutex, this fixes possible use after free in device IOTLB entries.
- Patch 4 fixes the diry page logging when device IOTLB is
  enabled. We should done through GPA instead of GIOVA, this was done
  through logging through iovec and traversing GPA->HPA list for the
  GPA.

Please consider them for -stable.

Thanks

Jason Wang (4):
  vhost: make sure used idx is seen before log in vhost_add_used_n()
  vhost_net: rework on the lock ordering for busy polling
  Revert "net: vhost: lock the vqs one by one"
  vhost: log dirty page correctly

 drivers/vhost/net.c   |  21 +++++++--
 drivers/vhost/vhost.c | 101 ++++++++++++++++++++++++++++++++++--------
 drivers/vhost/vhost.h |   3 +-
 3 files changed, 102 insertions(+), 23 deletions(-)
```
#### [PATCH 00/52] [RFC] virtio-fs: shared file system for virtual
##### From: Vivek Goyal <vgoyal@redhat.com>

```c

Hi,

Here are RFC patches for virtio-fs. Looking for feedback on this approach.

These patches should apply on top of 4.20-rc5. We have also put code for
various components here.

https://gitlab.com/virtio-fs

Problem Description
===================
We want to be able to take a directory tree on the host and share it with
guest[s]. Our goal is to be able to do it in a fast, consistent and secure
manner. Our primary use case is kata containers, but it should be usable in
other scenarios as well.

Containers may rely on local file system semantics for shared volumes,
read-write mounts that multiple containers access simultaneously.  File
system changes must be visible to other containers with the same consistency
expected of a local file system, including mmap MAP_SHARED.

Existing Solutions
==================
We looked at existing solutions and virtio-9p already provides basic shared
file system functionality although does not offer local file system semantics,
causing some workloads and test suites to fail. In addition, virtio-9p
performance has been an issue for Kata Containers and we believe this cannot
be alleviated without major changes that do not fit into the 9P protocol.

Design Overview
===============
With the goal of designing something with better performance and local file
system semantics, a bunch of ideas were proposed.

- Use fuse protocol (instead of 9p) for communication between guest
  and host. Guest kernel will be fuse client and a fuse server will
  run on host to serve the requests. Benchmark results (see below) are
  encouraging and show this approach performs well (2x to 8x improvement
  depending on test being run).

- For data access inside guest, mmap portion of file in QEMU address
  space and guest accesses this memory using dax. That way guest page
  cache is bypassed and there is only one copy of data (on host). This
  will also enable mmap(MAP_SHARED) between guests.

- For metadata coherency, there is a shared memory region which contains
  version number associated with metadata and any guest changing metadata
  updates version number and other guests refresh metadata on next
  access. This is still experimental and implementation is not complete.

How virtio-fs differs from existing approaches
==============================================
The unique idea behind virtio-fs is to take advantage of the co-location
of the virtual machine and hypervisor to avoid communication (vmexits).

DAX allows file contents to be accessed without communication with the
hypervisor. The shared memory region for metadata avoids communication in
the common case where metadata is unchanged.

By replacing expensive communication with cheaper shared memory accesses,
we expect to achieve better performance than approaches based on network
file system protocols. In addition, this also makes it easier to achieve
local file system semantics (coherency).

These techniques are not applicable to network file system protocols since
the communications channel is bypassed by taking advantage of shared memory
on a local machine. This is why we decided to build virtio-fs rather than
focus on 9P or NFS.

HOWTO
======
We have put instructions on how to use it here.

https://virtio-fs.gitlab.io/

Caching Modes
=============
Like virtio-9p, different caching modes are supported which determine the
coherency level as well. The “cache=FOO” and “writeback” options control the
level of coherence between the guest and host filesystems. The “shared” option
only has an effect on coherence between virtio-fs filesystem instances
running inside different guests.

- cache=none
  metadata, data and pathname lookup are not cached in guest. They are always
  fetched from host and any changes are immediately pushed to host.

- cache=always
  metadata, data and pathname lookup are cached in guest and never expire.

- cache=auto
  metadata and pathname lookup cache expires after a configured amount of time
  (default is 1 second). Data is cached while the file is open (close to open
  consistency).

- writeback/no_writeback
  These options control the writeback strategy.  If writeback is disabled,
  then normal writes will immediately be synchronized with the host fs. If
  writeback is enabled, then writes may be cached in the guest until the file
  is closed or an fsync(2) performed. This option has no effect on mmap-ed
  writes or writes going through the DAX mechanism.

- shared/no_shared
  These options control the  use of the shared version table. If shared mode
  is enabled then metadata and pathname lookup is cached in guest, but is
  refreshed due to changes in another virtio-fs instance.

DAX 
===
- dax can be turned on/off when mounting virtio-fs inside guest.

WHAT WORKS
==========
- As of now primarily cache options none, auto and always are working.
  shared option is still being worked on.

- Dax on/off seems to work. It does not seem to be as fast as we were
  expecting it to be. Still need to look into optimization opportunities.

TODO
====
- Complete "cache=shared" implementation.
- Look into improving performance for dax. It seems slow.
- Lot of bug fixing, cleanup and performance improvement. 

RESULTS
=======
- pjdfstests are passing. Have tried cache=none/auto/always and dax on/off).
  
  https://github.com/pjd/pjdfstest

  (one symlink test fails and that seems to be due xfs on host. Yet to
   look into it).

- We have run some basic tests and compared with virtio-9p and it seems
  to be faster. I ran "smallfile" utility and a simple fio job to test
  mmap performance.

Test Setup
-----------
- A fedora 28 host with 32G RAM, 2 sockets (6 cores per socket, 2
  threads per core)

- Using a PCIE SSD at host as backing store.

- Created a VM with 16 VCPUS and 6GB memory. A 2GB cache window (for dax
  mmap).
  
fio mmap
--------
Wrote simple fio job to run mmap and READ. Ran test on 1 file and 4
files and different caching modes. File size is 4G. Dropped cache in
guest before each run. Cache on host was untouched. So data on host must
have been cached. These results are average of 3 runs.

		cache mode 	1-file(one thread) 	4-files(4 threads)

virtio-9p	mmap		28 MB/s			140 MB/s
virtio-fs	none + dax	126 MB/s		501 MB/s


virtio-9p	loose	 	31 MB/s			135 MB/s
virtio-fs	always		235 MB/s		858 MB/s
virtio-fs	always + dax	121 MB/s		487 MB/s


smallfile
---------
https://github.com/distributed-system-analysis/smallfile

I basically ran bunch of operations like create, ls-l, read, append,
rename and delete-renamed and measured performance over 3 runs and
took average. Dropped cache after before each operation started
running. Used effectively following command for each operation.

# python smallfile_cli.py --operation create --threads 8 --file-size 1024 --files 2048 --top <test-dir>


		cache mode 	operation	(files/sec) 

virtio-9p	none		create		194
virtio-fs	none		create		714

virtio-9p	mmap		create		201
virtio-fs	none + dax	create		759

virtio-9p	loose		create		16
virtio-fs	always		create          685
virtio-fs	always + dax	create		735

virtio-9p	none		ls-l		2038
virtio-fs	none		ls-l		4615

virtio-9p	mmap		ls-l		2087	
virtio-fs	none + dax	ls-l		4616

virtio-9p	loose		ls-l		1619
virtio-fs	always		ls-l		13571
virtio-fs	always + dax	ls-l		12626

virtio-9p	none		read		199
virtio-fs	none		read		1405

virtio-9p	mmap		read		203	
virtio-fs	none + dax	read		1345

virtio-9p	loose		read		207
virtio-fs	always		read		1436
virtio-fs	always + dax	read		1368

virtio-9p	none		append		197
virtio-fs	none		append		717

virtio-9p	mmap		append		200	
virtio-fs	none + dax	append		645

virtio-9p	loose		append		16	
virtio-fs	always		append		651	
virtio-fs	always + dax	append		704	

virtio-9p	none		rename		2442
virtio-fs	none		rename		5797

virtio-9p	mmap		rename		2518	
virtio-fs	none + dax	rename		6386

virtio-9p	loose		rename		4178
virtio-fs	always		rename		15834
virtio-fs	always + dax	rename		15529

Thanks
Vivek

Dr. David Alan Gilbert (5):
  virtio-fs: Add VIRTIO_PCI_CAP_SHARED_MEMORY_CFG and utility to find
    them
  virito-fs: Make dax optional
  virtio: Free fuse devices on umount
  virtio-fs: Retrieve shm capabilities for version table
  virtio-fs: Map using the values from the capabilities

Miklos Szeredi (8):
  fuse: simplify fuse_fill_super_common() calling
  fuse: delete dentry if timeout is zero
  fuse: multiplex cached/direct_io/dax file operations
  virtio-fs: pass version table pointer to fuse
  fuse: don't crash if version table is NULL
  fuse: add shared version support (virtio-fs only)
  fuse: shared version cleanups
  fuse: fix fuse_permission() for the default_permissions case

Stefan Hajnoczi (17):
  fuse: add skeleton virtio_fs.ko module
  fuse: add probe/remove virtio driver
  fuse: rely on mutex_unlock() barrier instead of fput()
  fuse: extract fuse_fill_super_common()
  virtio_fs: get mount working
  fuse: export fuse_end_request()
  fuse: export fuse_len_args()
  fuse: add fuse_iqueue_ops callbacks
  fuse: process requests queues
  fuse: export fuse_get_unique()
  fuse: implement FUSE_FORGET for virtio-fs
  virtio_fs: Set up dax_device
  dax: remove block device dependencies
  fuse: add fuse_conn->dax_dev field
  fuse: map virtio_fs DAX window BAR
  fuse: Implement basic DAX read/write support commands
  fuse: add DAX mmap support

Vivek Goyal (22):
  virtio-fs: Retrieve shm capabilities for cache
  virtio-fs: Map cache using the values from the capabilities
  Limit number of pages returned by direct_access()
  fuse: Introduce fuse_dax_mapping
  Create a list of free memory ranges
  fuse: Introduce setupmapping/removemapping commands
  Introduce interval tree basic data structures
  fuse: Maintain a list of busy elements
  Do fallocate() to grow file before mapping for file growing writes
  dax: Pass dax_dev to dax_writeback_mapping_range()
  fuse: Define dax address space operations
  fuse, dax: Take ->i_mmap_sem lock during dax page fault
  fuse: Add logic to free up a memory range
  fuse: Add logic to do direct reclaim of memory
  fuse: Kick worker when free memory drops below 20% of total ranges
  Dispatch FORGET requests later instead of dropping them
  Release file in process context
  fuse: Do not block on inode lock while freeing memory range
  fuse: Reschedule dax free work if too many EAGAIN attempts
  fuse: Wait for memory ranges to become free
  fuse: Take inode lock for dax inode truncation
  fuse: Clear setuid bit even in direct I/O path

 drivers/dax/super.c             |    3 +-
 fs/dax.c                        |   23 +-
 fs/ext4/inode.c                 |    2 +-
 fs/fuse/Kconfig                 |   11 +
 fs/fuse/Makefile                |    1 +
 fs/fuse/cuse.c                  |    3 +-
 fs/fuse/dev.c                   |   80 ++-
 fs/fuse/dir.c                   |  282 +++++++--
 fs/fuse/file.c                  | 1012 +++++++++++++++++++++++++++--
 fs/fuse/fuse_i.h                |  234 ++++++-
 fs/fuse/inode.c                 |  278 ++++++--
 fs/fuse/readdir.c               |   12 +-
 fs/fuse/virtio_fs.c             | 1336 +++++++++++++++++++++++++++++++++++++++
 fs/splice.c                     |    3 +-
 fs/xfs/xfs_aops.c               |    2 +-
 include/linux/dax.h             |    6 +-
 include/linux/fs.h              |    2 +
 include/uapi/linux/fuse.h       |   39 ++
 include/uapi/linux/virtio_fs.h  |   46 ++
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_pci.h |   10 +
 21 files changed, 3151 insertions(+), 235 deletions(-)
 create mode 100644 fs/fuse/virtio_fs.c
 create mode 100644 include/uapi/linux/virtio_fs.h
```
#### [PATCH v2 0/7] x86/kvm/hyper-v: Implement KVM_GET_SUPPORTED_HV_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v1:
- Add Michael's R-b tags.
- Document KVM_GET_SUPPORTED_HV_CPUID and KVM_CAP_HYPERV_CPUID.
- Fix error handling in kvm_vcpu_ioctl_get_hv_cpuid().
- Check for -E2BIG in the selftest. PATCH6 is added to support the change.

As suggested by Paolo, introduce new KVM_GET_SUPPORTED_HV_CPUID returning
all Hyper-V CPUID feature leaves, this way we won't need to add a new
KVM_CAP_HYPERV_* for every new Hyper-V enlightenment we implement in
KVM.

(Using the existing KVM_GET_SUPPORTED_CPUID doesn't seem to be possible:
Hyper-V CPUID feature leaves intersect with KVM's (e.g. 0x40000000,
0x40000001) and we would probably confuse userspace in case we decide to
return these twice).

This patch series also does some housekeeping work in hyperv-tlfs.h, adds a
simple selftest (that's how I actually checked that the newly added ioctl
works) and removes recently added KVM_CAP_HYPERV_STIMER_DIRECT before it's
too late.

Vitaly Kuznetsov (7):
  x86/hyper-v: Do some housekeeping in hyperv-tlfs.h
  x86/hyper-v: Drop HV_X64_CONFIGURE_PROFILER definition
  x86/kvm/hyper-v: Introduce nested_get_evmcs_version() helper
  x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID
  x86/kvm/hyper-v: Drop KVM_CAP_HYPERV_STIMER_DIRECT
  KVM: selftests: implement an unchecked version of vcpu_ioctl()
  KVM: selftests: Add hyperv_cpuid test

 Documentation/virtual/kvm/api.txt             |  57 ++++++
 arch/x86/include/asm/hyperv-tlfs.h            | 185 +++++++++---------
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/kvm/hyperv.c                         | 125 +++++++++++-
 arch/x86/kvm/hyperv.h                         |   2 +
 arch/x86/kvm/svm.c                            |   7 +
 arch/x86/kvm/vmx.c                            |  24 ++-
 arch/x86/kvm/x86.c                            |  21 +-
 include/uapi/linux/kvm.h                      |   5 +-
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  14 +-
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 157 +++++++++++++++
 13 files changed, 493 insertions(+), 108 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c
```
#### [PATCH 0/2] x86: kvm: hyperv: assorted fixes for SynIC timers
##### From: Roman Kagan <rkagan@virtuozzo.com>

```c

A couple of patches addressing long-standing non-critical issues in
Hyper-V SynIC timers.

Note: the series will need rebasing once Vitaly Kuznetsov's
"x86/hyper-v: move synic/stimer control structures definitions to
hyperv-tlfs.h" lands.

Roman Kagan (2):
  x86: kvm: hyperv: simplify SynIC message delivery
  x86: kvm: hyperv: don't retry message delivery for periodic timers

 arch/x86/kvm/hyperv.c | 113 ++++++++++++++++++++----------------------
 1 file changed, 53 insertions(+), 60 deletions(-)
```
#### [PATCH v9 0/7] KVM: x86: Allow Qemu/KVM to use PVH entry point
##### From: Maran Wilson <maran.wilson@oracle.com>

```c

For certain applications it is desirable to rapidly boot a KVM virtual
machine. In cases where legacy hardware and software support within the
guest is not needed, Qemu should be able to boot directly into the
uncompressed Linux kernel binary without the need to run firmware.

There already exists an ABI to allow this for Xen PVH guests and the ABI
is supported by Linux and FreeBSD:

   https://xenbits.xen.org/docs/unstable/misc/pvh.html

This patch series would enable Qemu to use that same entry point for
booting KVM guests.

Changes from v8:

 * Removed unused KVM_GUEST_PVH symbol.

Changes from v7:

 (No functional changes from v7 other than rebasing to latest upstream) 
 * Added Review-by tags as provided by Juergen Gross (1,2,3,6,7)
 * Rebasing to upstream 4.18 caused a minor conflict in patch 4 that had
   to be hand merged due to this patch:
      1fe8388 xen: share start flags between PV and PVH
   I just had to make sure we were accounting for the xen_start_flags
   in the new code path.
 * Rebasing to upstream 4.20-rc4 caused a few minor conflicts in patches
   2,3,5,7 that needed to be resolved by hand. The conflicts were due to
   upstream non-functional code cleanup changes in arch/x86/xen/Makefile
   and arch/x86/platform/pvh/enlighten.c due to these patches:
      28c11b0 x86/xen: Move pv irq related functions under CONFIG_XEN_PV
              umbrella
      357d291 x86/xen: Fix boot loader version reported for PVH guests
      3cfa210 xen: don't include <xen/xen.h> from <asm/io.h> and
              <asm/dma-mapping.h>
 * Qemu and qboot RFC patches have been posted to show one example of how
   this functionality can be used. Some preliminary numbers are available
   in those cover letters showing the KVM guest boot time improvement.
      Qemu:
      http://lists.nongnu.org/archive/html/qemu-devel/2018-12/msg00957.html
      qboot:
      http://lists.nongnu.org/archive/html/qemu-devel/2018-12/msg00953.html

Changes from v6:

 * Addressed issues caught by the kbuild test robot:
    - Restored an #include line that had been dropped by mistake (patch 4)
    - Removed a pair of #include lines that were no longer needed in a
      common code file and causing problems for certain 32-bit configs
      (patchs 4 and 7)

Changes from v5:

 * The interface changes to the x86/HVM start info layout have
   now been accepted into the Xen tree.
 * Rebase and merge upstream PVH file changes.
 * (Patch 6) Synced up to the final version of the header file that was
             acked and pulled into the Xen tree.
 * (Patch 1) Fixed typo and removed redundant "def_bool n" line.

Changes from v4:

Note: I've withheld Juergen's earlier "Reviewed-by" tags from patches
1 and 7 since there were minor changes (mostly just addition of
CONFIG_KVM_GUEST_PVH as requested) that came afterwards.

 * Changed subject prefix from RFC to PATCH
 * Added CONFIG_KVM_GUEST_PVH as suggested
 * Relocated the PVH common files to
   arch/x86/platform/pvh/{enlighten.c,head.S}
 * Realized I also needed to move the objtool override for those files
 * Updated a few code comments per reviewer feedback
 * Sent out a patch of the hvm_start_info struct changes against the Xen
   tree since that is the canonical copy of the header. Discussions on
   that thread have resulted in some (non-functional) updates to
   start_info.h (patch 6/7) and those changes are reflected here as well
   in order to keep the files in sync. The header file has since been
   ack'ed for the Xen tree by Jan Beulich.

Changes from v3:

 * Implemented Juergen's suggestion for refactoring and moving the PVH
   code so that CONFIG_XEN is no longer required for booting KVM guests
   via the PVH entry point.
   Functionally, nothing has changed from V3 really, but the patches
   look completely different now because of all the code movement and
   refactoring. Some of these patches can be combined, but I've left
   them very small in some cases to make the refactoring and code
   movement easier to review.
   My approach for refactoring has been to create a PVH entry layer that
   still has understanding and knowledge about Xen vs non-Xen guest types
   so that it can make run time decisions to handle either case, as
   opposed to going all the way and re-writing it to be a completely
   hypervisor agnostic and architecturally pure layer that is separate
   from guest type details. The latter seemed a bit overkill in this
   situation. And I've handled the complexity of having to support
   Qemu/KVM boot of kernels compiled with or without CONFIG_XEN via a
   pair of xen specific __weak routines that can be overridden in kernels
   that support Xen guests. Importantly, the __weak routines are for
   xen specific code only (not generic "guest type" specific code) so
   there is no clashing between xen version of the strong routine and,
   say, a KVM version of the same routine. But I'm sure there are many
   ways to skin this cat, so I'm open to alternate suggestions if there
   is a compelling reason for not using __weak in this situation.

Changes from v2:

 * All structures (including memory map table entries) are padded and
   aligned to an 8 byte boundary.

 * Removed the "packed" attributes and made changes to comments as
   suggested by Jan.

Changes from v1:

 * Adopted Paolo's suggestion for defining a v2 PVH ABI that includes the
   e820 map instead of using the second module entry to pass the table.

 * Cleaned things up a bit to reduce the number of xen vs non-xen special
   cases.


Maran Wilson (7):
  xen/pvh: Split CONFIG_XEN_PVH into CONFIG_PVH and CONFIG_XEN_PVH
  xen/pvh: Move PVH entry code out of Xen specific tree
  xen/pvh: Create a new file for Xen specific PVH code
  xen/pvh: Move Xen specific PVH VM initialization out of common file
  xen/pvh: Move Xen code for getting mem map via hcall out of common
    file
  xen/pvh: Add memory map pointer to hvm_start_info struct
  KVM: x86: Allow Qemu/KVM to use PVH entry point

 MAINTAINERS                                     |   1 +
 arch/x86/Kbuild                                 |   2 +
 arch/x86/Kconfig                                |   6 ++
 arch/x86/kernel/head_64.S                       |   2 +-
 arch/x86/platform/pvh/Makefile                  |   5 +
 arch/x86/platform/pvh/enlighten.c               | 137 ++++++++++++++++++++++++
 arch/x86/{xen/xen-pvh.S => platform/pvh/head.S} |   0
 arch/x86/xen/Kconfig                            |   3 +-
 arch/x86/xen/Makefile                           |   2 -
 arch/x86/xen/enlighten_pvh.c                    |  94 ++++------------
 include/xen/interface/hvm/start_info.h          |  63 ++++++++++-
 include/xen/xen.h                               |   3 +
 12 files changed, 237 insertions(+), 81 deletions(-)
 create mode 100644 arch/x86/platform/pvh/Makefile
 create mode 100644 arch/x86/platform/pvh/enlighten.c
 rename arch/x86/{xen/xen-pvh.S => platform/pvh/head.S} (100%)
```
