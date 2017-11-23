

#### [PATCH net-next V4 0/5] vhost: accelerate metadata access through
##### From: Jason Wang <jasowang@redhat.com>

```c

This series tries to access virtqueue metadata through kernel virtual
address instead of copy_user() friends since they had too much
overheads like checks, spec barriers or even hardware feature
toggling.

Test shows about 24% improvement on TX PPS. It should benefit other
cases as well.

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

 drivers/vhost/net.c   |   4 +-
 drivers/vhost/vhost.c | 441 +++++++++++++++++++++++++++++++++++++-----
 drivers/vhost/vhost.h |  15 +-
 mm/shmem.c            |   1 +
 4 files changed, 410 insertions(+), 51 deletions(-)
```
#### [PATCH 0/2] KVM: x86: Fix PV IPIs for 32-bit KVM host
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM's paravirtual IPI hypercall is completely broken on 32-bit hosts
due to the invocation of kvm_pv_send_ipi() being wrapped with
"#ifdef CONFIG_X86_64".  All evidence points to this being an
inadvertent change that was introduced in v2 of the series[1] when
kvm_pv_send_ipi() was reworked, e.g. the initial version[2] wired
up the function for all x86 flavors and kvm_pv_send_ipi() itself
differentiates between 32-bit and 64-bit hosts.

The second patch adds checks on the result of the PV IPI hypercall in
the guest to aid in triaging failures, e.g. when running on 32-bit KVM
hosts that have not been fixed.

[1] https://patchwork.kernel.org/patch/10500887/
[2] https://patchwork.kernel.org/patch/10496067/

Sean Christopherson (2):
  KVM: x86: Fix PV IPIs for 32-bit KVM host
  KVM: x86: WARN_ONCE if sending a PV IPI returns a fatal error

 arch/x86/kernel/kvm.c | 7 +++++--
 arch/x86/kvm/x86.c    | 2 +-
 2 files changed, 6 insertions(+), 3 deletions(-)
```
#### [PATCH v4 0/9] mmu notifier provide context informations
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

Hi Andrew, i see that you still have my event patch in you queue [1].
This patchset replace that single patch and is broken down in further
step so that it is easier to review and ascertain that no mistake were
made during mechanical changes. Here are the step:

    Patch 1 - add the enum values
    Patch 2 - coccinelle semantic patch to convert all call site of
              mmu_notifier_range_init to default enum value and also
              to passing down the vma when it is available
    Patch 3 - update many call site to more accurate enum values
    Patch 4 - add the information to the mmu_notifier_range struct
    Patch 5 - helper to test if a range is updated to read only

All the remaining patches are update to various driver to demonstrate
how this new information get use by device driver. I build tested
with make all and make all minus everything that enable mmu notifier
ie building with MMU_NOTIFIER=no. Also tested with some radeon,amd
gpu and intel gpu.

If they are no objections i believe best plan would be to merge the
the first 5 patches (all mm changes) through your queue for 5.1 and
then to delay driver update to each individual driver tree for 5.2.
This will allow each individual device driver maintainer time to more
thouroughly test this more then my own testing.

Note that i also intend to use this feature further in nouveau and
HMM down the road. I also expect that other user like KVM might be
interested into leveraging this new information to optimize some of
there secondary page table invalidation.

Here is an explaination on the rational for this patchset:


CPU page table update can happens for many reasons, not only as a result
of a syscall (munmap(), mprotect(), mremap(), madvise(), ...) but also
as a result of kernel activities (memory compression, reclaim, migration,
...).

This patch introduce a set of enums that can be associated with each of
the events triggering a mmu notifier. Latter patches take advantages of
those enum values.

- UNMAP: munmap() or mremap()
- CLEAR: page table is cleared (migration, compaction, reclaim, ...)
- PROTECTION_VMA: change in access protections for the range
- PROTECTION_PAGE: change in access protections for page in the range
- SOFT_DIRTY: soft dirtyness tracking

Being able to identify munmap() and mremap() from other reasons why the
page table is cleared is important to allow user of mmu notifier to
update their own internal tracking structure accordingly (on munmap or
mremap it is not longer needed to track range of virtual address as it
becomes invalid).

[1] https://www.ozlabs.org/~akpm/mmotm/broken-out/mm-mmu_notifier-contextual-information-for-event-triggering-invalidation-v2.patch

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
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>

Jérôme Glisse (9):
  mm/mmu_notifier: contextual information for event enums
  mm/mmu_notifier: contextual information for event triggering
    invalidation
  mm/mmu_notifier: use correct mmu_notifier events for each invalidation
  mm/mmu_notifier: pass down vma and reasons why mmu notifier is
    happening
  mm/mmu_notifier: mmu_notifier_range_update_to_read_only() helper
  gpu/drm/radeon: optimize out the case when a range is updated to read
    only
  gpu/drm/amdgpu: optimize out the case when a range is updated to read
    only
  gpu/drm/i915: optimize out the case when a range is updated to read
    only
  RDMA/umem_odp: optimize out the case when a range is updated to read
    only

 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  | 13 ++++++++
 drivers/gpu/drm/i915/i915_gem_userptr.c | 16 ++++++++++
 drivers/gpu/drm/radeon/radeon_mn.c      | 13 ++++++++
 drivers/infiniband/core/umem_odp.c      | 22 +++++++++++--
 fs/proc/task_mmu.c                      |  3 +-
 include/linux/mmu_notifier.h            | 42 ++++++++++++++++++++++++-
 include/rdma/ib_umem_odp.h              |  1 +
 kernel/events/uprobes.c                 |  3 +-
 mm/huge_memory.c                        | 14 +++++----
 mm/hugetlb.c                            | 11 ++++---
 mm/khugepaged.c                         |  3 +-
 mm/ksm.c                                |  6 ++--
 mm/madvise.c                            |  3 +-
 mm/memory.c                             | 25 +++++++++------
 mm/migrate.c                            |  5 ++-
 mm/mmu_notifier.c                       | 10 ++++++
 mm/mprotect.c                           |  4 ++-
 mm/mremap.c                             |  3 +-
 mm/oom_kill.c                           |  3 +-
 mm/rmap.c                               |  6 ++--
 20 files changed, 171 insertions(+), 35 deletions(-)
```
#### [PATCH 0/3] KVM: nVMX: Fix address calculations for VMX instrs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

VMX instructions directly cause VM-Exits, and so to emulate them for a
nested VMM, KVM manually calculates the address of memory operands of
VMX instructions as opposed to routing the entire instruction through
the emulator.

Unsurprisingly, there are bugs in the address calculations related to
truncating address based on mode and prefixes.  Patch 1/3 addresses the
most critical bug, which AFAICT causes a 100% failure rate when running
a 32-bit KVM as L1 on top of a 64-bit KVM as L0.  Patches 2/3 and 3/3
fix slightly more esoteric behavior that is unlikely to affect any real
world hypervisors.

Sean Christopherson (3):
  KVM: nVMX: Sign extend displacements of VMX instr's mem operands
  KVM: nVMX: Apply addr size mask to effective address for VMX
    instructions
  KVM: nVMX: Ignore limit checks on VMX instructions using flat segments

 arch/x86/kvm/vmx/nested.c | 41 ++++++++++++++++++++++++++++++++++-----
 1 file changed, 36 insertions(+), 5 deletions(-)
```
