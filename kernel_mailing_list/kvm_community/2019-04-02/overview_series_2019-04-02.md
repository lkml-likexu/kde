#### [PATCH 1/6] mm: change locked_vm's type from unsigned long to atomic64_t
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Taking and dropping mmap_sem to modify a single counter, locked_vm, is
overkill when the counter could be synchronized separately.

Make mmap_sem a little less coarse by changing locked_vm to an atomic,
the 64-bit variety to avoid issues with overflow on 32-bit systems.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
Cc: Alan Tull <atull@kernel.org>
Cc: Alexey Kardashevskiy <aik@ozlabs.ru>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Christoph Lameter <cl@linux.com>
Cc: Davidlohr Bueso <dave@stgolabs.net>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Moritz Fischer <mdf@kernel.org>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Wu Hao <hao.wu@intel.com>
Cc: <linux-mm@kvack.org>
Cc: <kvm@vger.kernel.org>
Cc: <kvm-ppc@vger.kernel.org>
Cc: <linuxppc-dev@lists.ozlabs.org>
Cc: <linux-fpga@vger.kernel.org>
Cc: <linux-kernel@vger.kernel.org>
---
 arch/powerpc/kvm/book3s_64_vio.c    | 14 ++++++++------
 arch/powerpc/mm/mmu_context_iommu.c | 15 ++++++++-------
 drivers/fpga/dfl-afu-dma-region.c   | 18 ++++++++++--------
 drivers/vfio/vfio_iommu_spapr_tce.c | 17 +++++++++--------
 drivers/vfio/vfio_iommu_type1.c     | 10 ++++++----
 fs/proc/task_mmu.c                  |  2 +-
 include/linux/mm_types.h            |  2 +-
 kernel/fork.c                       |  2 +-
 mm/debug.c                          |  5 +++--
 mm/mlock.c                          |  4 ++--
 mm/mmap.c                           | 18 +++++++++---------
 mm/mremap.c                         |  6 +++---
 12 files changed, 61 insertions(+), 52 deletions(-)

```
#### [PATCH] KVM: arm/arm64: vgic-v3: Retire pending interrupts on disabling LPIs
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
When disabling LPIs (for example on reset) at the redistributor
level, it is expected that LPIs that was pending in the CPU
interface are eventually retired.

Currently, this is not what is happening, and these LPIs will
stay in the ap_list, eventually being acknowledged by the vcpu
(which didn't quite expect this behaviour).

The fix is thus to retire these LPIs from the list of pending
interrupts as we disable LPIs.

Reported-by: Heyi Guo <guoheyi@huawei.com>
Fixes: 0e4e82f154e3 ("KVM: arm64: vgic-its: Enable ITS emulation as a virtual MSI controller")
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
Heyi,

Can you please give this alternative patch a go on your setup?
This should be a much better fit than my original hack.

Thanks,

        M.

 virt/kvm/arm/vgic/vgic-mmio-v3.c |  3 +++
 virt/kvm/arm/vgic/vgic.c         | 24 ++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic.h         |  1 +
 3 files changed, 28 insertions(+)

```
#### [PATCH] kvm: arm: Skip stage2 huge mappings for unaligned ipa backed by THP
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
With commit a80868f398554842b14, we no longer ensure that the
THP page is properly aligned in the guest IPA. Skip the stage2
huge mapping for unaligned IPA backed by transparent hugepages.

Fixes: a80868f398554842b14 ("KVM: arm/arm64: Enforce PTE mappings at stage2 when needed")
Reported-by: Eric Auger <eric.auger@redhat.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Chirstoffer Dall <christoffer.dall@arm.com>
Cc: Zenghui Yu <yuzenghui@huawei.com>
Cc: Zheng Xiang <zhengxiang9@huawei.com>
Tested-by: Eric Auger <eric.auger@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Tested-by: Andrew Murray <andrew.murray@arm.com>
---
 virt/kvm/arm/mmu.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: x86: Load SMRAM in a single shot when leaving SMM
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
RSM emulation is currently broken on VMX when the interrupted guest has
CR4.VMXE=1.  Rather than dance around the issue of HF_SMM_MASK being set
when loading SMSTATE into architectural state, ideally RSM emulation
itself would be reworked to clear HF_SMM_MASK prior to loading non-SMM
architectural state.

Ostensibly, the only motivation for having HF_SMM_MASK set throughout
the loading of state from the SMRAM save state area is so that the
memory accesses from GET_SMSTATE() are tagged with role.smm (though
arguably even that is unnecessary).  Load all of the SMRAM save state
area from guest memory at the beginning of RSM emulation, and load
state from the buffer instead of reading guest memory one-by-one.

This paves the way for clearing HF_SMM_MASK prior to loading state,
and also aligns RSM with the enter_smm() behavior, which fills a
buffer and writes SMRAM save state in a single go.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_emulate.h |   3 +-
 arch/x86/include/asm/kvm_host.h    |   5 +-
 arch/x86/kvm/emulate.c             | 149 ++++++++++++++---------------
 arch/x86/kvm/svm.c                 |  20 ++--
 arch/x86/kvm/vmx/vmx.c             |   2 +-
 arch/x86/kvm/x86.c                 |   5 +-
 6 files changed, 92 insertions(+), 92 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Skip EFER vs. guest CPUID checks for host-initiated writes
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
KVM allows userspace to violate consistency checks related to the
guest's CPUID model to some degree.  Generally speaking, userspace has
carte blanche when it comes to guest state so long as jamming invalid
state won't negatively affect the host.

Currently this is seems to be a non-issue as most of the interesting
EFER checks are missing, e.g. NX and LME, but those will be added
shortly.  Proactively exempt userspace from the CPUID checks so as not
to break userspace.

Note, the efer_reserved_bits check still applies to userspace writes as
that mask reflects the host's capabilities, e.g. KVM shouldn't allow a
guest to run with NX=1 if it has been disabled in the host.

Fixes: d80174745ba39 ("KVM: SVM: Only allow setting of EFER_SVME when CPUID SVM is set")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 37 ++++++++++++++++++++++++-------------
 1 file changed, 24 insertions(+), 13 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Don't clear EFER during SMM transitions for 32-bit vCPU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Neither AMD nor Intel CPUs have an EFER field in the legacy SMRAM save
state area, i.e. don't save/restore EFER across SMM transitions.  KVM
somewhat models this, e.g. doesn't clear EFER on entry to SMM if the
guest doesn't support long mode.  But during RSM, KVM unconditionally
clears EFER so that it can get back to pure 32-bit mode in order to
start loading CRs with their actual non-SMM values.

Clear EFER only when it will be written when loading the non-SMM state
so as to preserve bits that can theoretically be set on 32-bit vCPUs,
e.g. KVM always emulates EFER_SCE.

And because CR4.PAE is cleared only to play nice with EFER, wrap that
code in the long mode check as well.  Note, this may result in a
compiler warning about cr4 being consumed uninitialized.  Re-read CR4
even though it's technically unnecessary, as doing so allows for more
readable code and RSM emulation is not a performance critical path.

Fixes: 660a5d517aaab ("KVM: x86: save/load state on SMM switch")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/emulate.c | 21 +++++++++++----------
 1 file changed, 11 insertions(+), 10 deletions(-)

```
#### [PATCH v2] vfio/type1: Limit DMA mappings per containerFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Memory backed DMA mappings are accounted against a user's locked
memory limit, including multiple mappings of the same memory.  This
accounting bounds the number of such mappings that a user can create.
However, DMA mappings that are not backed by memory, such as DMA
mappings of device MMIO via mmaps, do not make use of page pinning
and therefore do not count against the user's locked memory limit.
These mappings still consume memory, but the memory is not well
associated to the process for the purpose of oom killing a task.

To add bounding on this use case, we introduce a limit to the total
number of concurrent DMA mappings that a user is allowed to create.
This limit is exposed as a tunable module option where the default
value of 64K is expected to be well in excess of any reasonable use
case (a large virtual machine configuration would typically only make
use of tens of concurrent mappings).

This fixes CVE-2019-3882.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Tested-by: Eric Auger <eric.auger@redhat.com>
---

v2: Remove unnecessary atomic, all runtime access occurs while
    holding vfio_iommu.lock.  Change to unsigned int since we're
    no longer bound by the atomic_t.

 drivers/vfio/vfio_iommu_type1.c |   14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [RFC v1 1/3] vfio-ccw: Do not call flush_workqueue while holding the spinlock
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
Currently we call flush_workqueue while holding the subchannel
spinlock. But flush_workqueue function can go to sleep, so
do not call the function while holding the spinlock.

Fixes the following bug:

[  285.203430] BUG: scheduling while atomic: bash/14193/0x00000002
[  285.203434] INFO: lockdep is turned off.
....
[  285.203485] Preemption disabled at:
[  285.203488] [<000003ff80243e5c>] vfio_ccw_sch_quiesce+0xbc/0x120 [vfio_ccw]
[  285.203496] CPU: 7 PID: 14193 Comm: bash Tainted: G        W
....
[  285.203504] Call Trace:
[  285.203510] ([<0000000000113772>] show_stack+0x82/0xd0)
[  285.203514]  [<0000000000b7a102>] dump_stack+0x92/0xd0
[  285.203518]  [<000000000017b8be>] __schedule_bug+0xde/0xf8
[  285.203524]  [<0000000000b95b5a>] __schedule+0x7a/0xc38
[  285.203528]  [<0000000000b9678a>] schedule+0x72/0xb0
[  285.203533]  [<0000000000b9bfbc>] schedule_timeout+0x34/0x528
[  285.203538]  [<0000000000b97608>] wait_for_common+0x118/0x1b0
[  285.203544]  [<0000000000166d6a>] flush_workqueue+0x182/0x548
[  285.203550]  [<000003ff80243e6e>] vfio_ccw_sch_quiesce+0xce/0x120 [vfio_ccw]
[  285.203556]  [<000003ff80245278>] vfio_ccw_mdev_reset+0x38/0x70 [vfio_ccw]
[  285.203562]  [<000003ff802458b0>] vfio_ccw_mdev_remove+0x40/0x78 [vfio_ccw]
[  285.203567]  [<000003ff801a499c>] mdev_device_remove_ops+0x3c/0x80 [mdev]
[  285.203573]  [<000003ff801a4d5c>] mdev_device_remove+0xc4/0x130 [mdev]
[  285.203578]  [<000003ff801a5074>] remove_store+0x6c/0xa8 [mdev]
[  285.203582]  [<000000000046f494>] kernfs_fop_write+0x14c/0x1f8
[  285.203588]  [<00000000003c1530>] __vfs_write+0x38/0x1a8
[  285.203593]  [<00000000003c187c>] vfs_write+0xb4/0x198
[  285.203597]  [<00000000003c1af2>] ksys_write+0x5a/0xb0
[  285.203601]  [<0000000000b9e270>] system_call+0xdc/0x2d8

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
