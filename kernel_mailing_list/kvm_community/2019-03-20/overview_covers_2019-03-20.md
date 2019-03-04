

#### [PATCH kvmtool v2 0/3] vfio-pci: Support INTx mode re-enabling
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

So this patch is to support INTx mode re-enabling; 0001/0002 patches
are only minor fixing up for eventfd releasing and remove useless FDs
reservation for INTx.  0003 patch is the core patch for supporting
INTx mode re-enabling, when kvmtool detects MSI is disabled it
rollbacks to INTx mode.

This patch set has been tested on Juno-r2 board.

Leo Yan (3):
  vfio-pci: Release INTx's unmask eventfd properly
  vfio-pci: Remove useless FDs reservation in vfio_pci_enable_intx()
  vfio-pci: Re-enable INTx mode when disable MSI/MSIX

 include/kvm/vfio.h |  1 +
 vfio/pci.c         | 61 +++++++++++++++++++++++++++++++++++++---------
 2 files changed, 50 insertions(+), 12 deletions(-)
```
#### [PATCH v4 00/17] KVM: PPC: Book3S HV: add XIVE native exploitation
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

On the POWER9 processor, the XIVE interrupt controller can control
interrupt sources using MMIOs to trigger events, to EOI or to turn off
the sources. Priority management and interrupt acknowledgment is also
controlled by MMIO in the CPU presenter sub-engine.

PowerNV/baremetal Linux runs natively under XIVE but sPAPR guests need
special support from the hypervisor to do the same. This is called the
XIVE native exploitation mode and today, it can be activated under the
PowerPC Hypervisor, pHyp. However, Linux/KVM lacks XIVE native support
and still offers the old interrupt mode interface using a KVM device
implementing the XICS hcalls over XIVE.

The following series is proposal to add the same support under KVM.

A new KVM device is introduced for the XIVE native exploitation
mode. It reuses most of the XICS-over-XIVE glue implementation
structures which are internal to KVM but has a completely different
interface. A set of KVM device ioctls provide support for the
hypervisor calls, all handled in QEMU, to configure the sources and
the event queues. From there, all interrupt control is transferred to
the guest which can use MMIOs.

These MMIO regions (ESB and TIMA) are exposed to guests in QEMU,
similarly to VFIO, and the associated VMAs are populated dynamically
with the appropriate pages using a fault handler. These are now
implemented using mmap()s of the KVM device fd.

Migration has its own specific needs regarding memory. The patchset
provides a specific control to quiesce XIVE before capturing the
memory. The save and restore of the internal state is based on the
same ioctls used for the hcalls.

On a POWER9 sPAPR machine, the Client Architecture Support (CAS)
negotiation process determines whether the guest operates with a
interrupt controller using the XICS legacy model, as found on POWER8,
or in XIVE exploitation mode. Which means that the KVM interrupt
device should be created at run-time, after the machine has started.
This requires extra support from KVM to destroy KVM devices. It is
introduced at the end of the patchset as it still requires some
attention and a XIVE-only VM would not need.

This is based on 5.1-rc1 and should be a candidate for 5.2 now. The
OPAL patches have not yet been merged.


GitHub trees available here :
 
QEMU sPAPR:

  https://github.com/legoater/qemu/commits/xive-next
  
Linux/KVM:

  https://github.com/legoater/linux/commits/xive-5.1

OPAL:

  https://github.com/legoater/skiboot/commits/xive

Thanks,

C.

Caveats :

 - We should introduce a set of definitions common to XIVE and XICS
 - The XICS-over-XIVE device file book3s_xive.c could be renamed to
   book3s_xics_on_xive.c or book3s_xics_p9.c
 - The XICS-over-XIVE device has locking issues in the setup. 

Changes since v3:

 - removed a couple of useless includes
 - fix the test ont the initial setting of the EQ toggle bit : 0 -> 1
 - renamed qsize to qshift
 - renamed qpage to qaddr
 - checked host page size
 - limited flags to KVM_XIVE_EQ_ALWAYS_NOTIFY to fit sPAPR specs
 - Fixed xive_timaval description in documentation

Changes since v2:

 - removed extra OPAL call definitions
 - removed ->q_order setting. Only useful in the XICS-on-XIVE KVM
   device which allocates the EQs on behalf of the guest.
 - returned -ENXIO when VP base is invalid
 - made use of the xive_vp() macro to compute VP identifiers
 - reworked locking in kvmppc_xive_native_connect_vcpu() to fix races 
 - stop advertising KVM_CAP_PPC_IRQ_XIVE as support is not fully
   available yet
 - fixed comment on XIVE IRQ number space
 - removed usage of the __x_* macros
 - fixed locking on source block
 - fixed comments on the KVM device attribute definitions
 - handled MASKED EAS configuration
 - fixed check on supported EQ size to restrict to 64K pages
 - checked kvm_eq.flags that need to be zero
 - removed the OPAL call when EQ qtoggle bit and index are zero. 
 - reduced the size of kvmppc_one_reg timaval attribute to two u64s
 - stopped returning of the OS CAM line value
 
Changes since v1:

 - Better documentation (was missing)
 - Nested support. XIVE not advertised on non PowerNV platforms. This
   is a good way to test the fallback on QEMU emulated devices.
 - ESB and TIMA special mapping done using the KVM device fd
 - All hcalls moved to QEMU. Dropped the patch moving the hcall flags.
 - Reworked of the KVM device ioctl controls to support hcalls and
   migration needs to capture/save states
 - Merged the control syncing XIVE and marking the EQ page dirty
 - Fixed passthrough support using the KVM device file address_space
   to clear the ESB pages from the mapping
 - Misc enhancements and fixes 

Cédric Le Goater (17):
  powerpc/xive: add OPAL extensions for the XIVE native exploitation
    support
  KVM: PPC: Book3S HV: add a new KVM device for the XIVE native
    exploitation mode
  KVM: PPC: Book3S HV: XIVE: introduce a new capability
    KVM_CAP_PPC_IRQ_XIVE
  KVM: PPC: Book3S HV: XIVE: add a control to initialize a source
  KVM: PPC: Book3S HV: XIVE: add a control to configure a source
  KVM: PPC: Book3S HV: XIVE: add controls for the EQ configuration
  KVM: PPC: Book3S HV: XIVE: add a global reset control
  KVM: PPC: Book3S HV: XIVE: add a control to sync the sources
  KVM: PPC: Book3S HV: XIVE: add a control to dirty the XIVE EQ pages
  KVM: PPC: Book3S HV: XIVE: add get/set accessors for the VP XIVE state
  KVM: introduce a 'mmap' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: add a TIMA mapping
  KVM: PPC: Book3S HV: XIVE: add a mapping for the source ESB pages
  KVM: PPC: Book3S HV: XIVE: add passthrough support
  KVM: PPC: Book3S HV: XIVE: activate XIVE exploitation mode
  KVM: introduce a KVM_DESTROY_DEVICE ioctl
  KVM: PPC: Book3S HV: XIVE: clear the vCPU interrupt presenters

 arch/powerpc/include/asm/kvm_host.h        |    2 +
 arch/powerpc/include/asm/kvm_ppc.h         |   32 +
 arch/powerpc/include/asm/opal-api.h        |    7 +-
 arch/powerpc/include/asm/opal.h            |    7 +
 arch/powerpc/include/asm/xive.h            |   17 +
 arch/powerpc/include/uapi/asm/kvm.h        |   46 +
 arch/powerpc/kvm/book3s_xive.h             |   36 +
 include/linux/kvm_host.h                   |    1 +
 include/uapi/linux/kvm.h                   |   10 +
 arch/powerpc/kvm/book3s.c                  |   31 +-
 arch/powerpc/kvm/book3s_xics.c             |   19 +
 arch/powerpc/kvm/book3s_xive.c             |  170 ++-
 arch/powerpc/kvm/book3s_xive_native.c      | 1205 ++++++++++++++++++++
 arch/powerpc/kvm/powerpc.c                 |   37 +
 arch/powerpc/platforms/powernv/opal-call.c |    3 +
 arch/powerpc/sysdev/xive/native.c          |  110 ++
 virt/kvm/kvm_main.c                        |   52 +
 Documentation/virtual/kvm/api.txt          |   29 +
 Documentation/virtual/kvm/devices/xive.txt |  197 ++++
 arch/powerpc/kvm/Makefile                  |    2 +-
 20 files changed, 1953 insertions(+), 60 deletions(-)
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
```
#### [PATCH v13 00/20] arm64: untag user pointers passed to the kernel
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

Memory syscalls (mmap, mprotect, etc.) don't do user memory accesses but
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

This patchset has been merged into the Pixel 2 kernel tree and is now
being used to enable testing of Pixel 2 phones with HWASan.

Thanks!

[1] http://clang.llvm.org/docs/HardwareAssistedAddressSanitizerDesign.html

[2] https://github.com/lucvoo/sparse-dev/commit/5f960cb10f56ec2017c128ef9d16060e0145f292

[3] https://lkml.org/lkml/2019/3/18/819

[4] https://community.arm.com/processors/b/blog/posts/arm-a-profile-architecture-2018-developments-armv85a

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

Andrey Konovalov (20):
  uaccess: add untagged_addr definition for other arches
  arm64: untag user pointers in access_ok and __uaccess_mask_ptr
  lib, arm64: untag user pointers in strn*_user
  mm, arm64: untag user pointers passed to memory syscalls
  mm, arm64: untag user pointers in mm/gup.c
  mm, arm64: untag user pointers in get_vaddr_frames
  fs, arm64: untag user pointers in copy_mount_options
  fs, arm64: untag user pointers in fs/userfaultfd.c
  net, arm64: untag user pointers in tcp_zerocopy_receive
  kernel, arm64: untag user pointers in prctl_set_mm*
  tracing, arm64: untag user pointers in seq_print_user_ip
  uprobes, arm64: untag user pointers in find_active_uprobe
  bpf, arm64: untag user pointers in stack_map_get_build_id_offset
  drm/amdgpu, arm64: untag user pointers in amdgpu_ttm_tt_get_user_pages
  drm/radeon, arm64: untag user pointers in radeon_ttm_tt_pin_userptr
  IB/mlx4, arm64: untag user pointers in mlx4_get_umem_mr
  media/v4l2-core, arm64: untag user pointers in
    videobuf_dma_contig_user_get
  tee/optee, arm64: untag user pointers in check_mem_type
  vfio/type1, arm64: untag user pointers in vaddr_get_pfn
  selftests, arm64: add a selftest for passing tagged pointers to kernel

 arch/arm64/include/asm/uaccess.h              | 10 +++--
 drivers/gpu/drm/amd/amdgpu/amdgpu_ttm.c       |  5 ++-
 drivers/gpu/drm/radeon/radeon_ttm.c           |  5 ++-
 drivers/infiniband/hw/mlx4/mr.c               |  7 +--
 drivers/media/v4l2-core/videobuf-dma-contig.c |  9 ++--
 drivers/tee/optee/call.c                      |  1 +
 drivers/vfio/vfio_iommu_type1.c               |  2 +
 fs/namespace.c                                |  2 +-
 fs/userfaultfd.c                              |  5 +++
 include/linux/mm.h                            |  4 ++
 ipc/shm.c                                     |  2 +
 kernel/bpf/stackmap.c                         |  6 ++-
 kernel/events/uprobes.c                       |  2 +
 kernel/sys.c                                  | 44 +++++++++++++------
 kernel/trace/trace_output.c                   |  5 ++-
 lib/strncpy_from_user.c                       |  3 +-
 lib/strnlen_user.c                            |  3 +-
 mm/frame_vector.c                             |  2 +
 mm/gup.c                                      |  4 ++
 mm/madvise.c                                  |  2 +
 mm/mempolicy.c                                |  5 +++
 mm/migrate.c                                  |  1 +
 mm/mincore.c                                  |  2 +
 mm/mlock.c                                    |  5 +++
 mm/mmap.c                                     |  7 +++
 mm/mprotect.c                                 |  1 +
 mm/mremap.c                                   |  2 +
 mm/msync.c                                    |  2 +
 net/ipv4/tcp.c                                |  2 +
 tools/testing/selftests/arm64/.gitignore      |  1 +
 tools/testing/selftests/arm64/Makefile        | 11 +++++
 .../testing/selftests/arm64/run_tags_test.sh  | 12 +++++
 tools/testing/selftests/arm64/tags_test.c     | 21 +++++++++
 33 files changed, 159 insertions(+), 36 deletions(-)
 create mode 100644 tools/testing/selftests/arm64/.gitignore
 create mode 100644 tools/testing/selftests/arm64/Makefile
 create mode 100755 tools/testing/selftests/arm64/run_tags_test.sh
 create mode 100644 tools/testing/selftests/arm64/tags_test.c
```
#### [RFC PATCH 0/1] KVM: PPC: Inform userspace about singlestep support
##### From: Fabiano Rosas <farosas@linux.ibm.com>

```c

I am looking for a way to inform userspace about the lack of an
implementation in KVM HV for single stepping of instructions
(KVM_GUESTDGB_SINGLESTEP bit from SET_GUEST_DEBUG ioctl).

This will be used by QEMU to decide whether to attempt a call to the
set_guest_debug ioctl (for BookE, KVM PR) or fallback to a QEMU only
implementation (for KVM HV).

QEMU thread:
http://patchwork.ozlabs.org/cover/1049811/

My current proposal is to introduce a ppc-specific capability for
this. However I'm not sure if this would be better as a cap common for
all architectures or even if it should report on all of the possible
set_guest_debug flags to cover for the future.

Please comment. Thanks.


Fabiano Rosas (1):
  KVM: PPC: Report single stepping capability

 arch/powerpc/kvm/powerpc.c | 5 +++++
 include/uapi/linux/kvm.h   | 1 +
 2 files changed, 6 insertions(+)
---
2.20.1
```
