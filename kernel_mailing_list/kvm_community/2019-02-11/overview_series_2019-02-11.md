#### [PATCH kernel] vfio/spapr_tce: Skip unsetting already unset table
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
VFIO TCE IOMMU v2 owns IOMMU tables so when detach a IOMMU group from
a container, we need to unset those from a group so we call unset_window()
so do we unconditionally. We also unset tables when removing a DMA window
via the VFIO_IOMMU_SPAPR_TCE_REMOVE ioctl.

The window removal checks if the table actually exists (hidden inside
tce_iommu_find_table()) but the group detaching does not so the user
may see duplicating messages:
pci 0009:03     : [PE# fd] Removing DMA window #0
pci 0009:03     : [PE# fd] Removing DMA window #1
pci 0009:03     : [PE# fd] Removing DMA window #0
pci 0009:03     : [PE# fd] Removing DMA window #1

At the moment this is not a problem as the second invocation
of unset_window() writes zeroes to the HW registers again and exits early
as there is no table.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---

When doing VFIO PCI hot unplug, first we remove the DMA window and
set container->tables[num] - this is a first couple of messages.
Then we detach the group and then we see another couple of the same
messages which confused myself.
---
 drivers/vfio/vfio_iommu_spapr_tce.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH kvmtool v3] arm: Auto-detect guest GIC type
##### From: Andre Przywara <andre.przywara@arm.com>

```c
At the moment kvmtool always tries to instantiate a virtual GICv2
interrupt controller for the guest, and fails with some scary error
message if that doesn't work.
The user has then to manually specify "--irqchip=gicv3", which is not
really obvious.
With the advent of more GICv3-only machines, let's try to be more
clever and implement some auto-detection of the GIC type needed:
We try gicv3-its, gicv3, gicv2m and gicv2, in that order. The first one
succeeding wins.
For GICv2 machines the first two will always fail.
On GICv3 machines offering GICv2 compatibility we used to prefer a
virtual GICv2 in the guest, but these days the GICv3 support both in
guests and in KVM is equally mature and wide-spread, so we should use
the GICv3 emulation for the guest as well.

This algorithm is in effect is there is no explicit --irqchip parameter
on the command line. We still allow the GIC type to be set explicitly.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/gic.c                    | 16 ++++++++++++++++
 arm/include/arm-common/gic.h |  1 +
 2 files changed, 17 insertions(+)

```
#### [PATCH 1/5] vfio/type1: use pinned_vm instead of locked_vm to account pinned pages
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Beginning with bc3e53f682d9 ("mm: distinguish between mlocked and pinned
pages"), locked and pinned pages are accounted separately.  Type1
accounts pinned pages to locked_vm; use pinned_vm instead.

pinned_vm recently became atomic and so no longer relies on mmap_sem
held as writer: delete.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---
 drivers/vfio/vfio_iommu_type1.c | 31 ++++++++++++-------------------
 1 file changed, 12 insertions(+), 19 deletions(-)

```
#### [PATCH v2] s390: vsie: Use effective CRYCBD.31 to check CRYCBD validity
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
When facility.76 MSAX3 is present for the guest we must issue a validity
interception if the CRYCBD is not valid.

The bit CRYCBD.31 is an effective field and tested at each guest
level and has for effect to mask the facility.76

It follows that if CRYCBD.31 is clear and AP is not in use  we do not
have to test the CRYCBD validatity even facility.76 is present in the
host.

Fixes: 6ee74098201b ("KVM: s390: vsie: allow CRYCB FORMAT-0")
Cc: stable@vger.kernel.org

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reported-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/vsie.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/4] kvm: Add memcg accounting to KVM allocationsFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
There are many KVM kernel memory allocations which are tied to the life of
the VM process and should be charged to the VM process's cgroup. If the
allocations aren't tied to the process, the OOM killer will not know
that killing the process will free the associated kernel memory.
Add __GFP_ACCOUNT flags to many of the allocations which are not yet being
charged to the VM process's cgroup.

Tested:
	Ran all kvm-unit-tests on a 64 bit Haswell machine, the patch
	introduced no new failures.
	Ran a kernel memory accounting test which creates a VM to touch
	memory and then checks that the kernel memory allocated for the
	process is within certain bounds.
	With this patch we account for much more of the vmalloc and slab memory
	allocated for the VM.

There remain a few allocations which should be charged to the VM's
cgroup but are not. In they include:
        vcpu->run
        kvm->coalesced_mmio_ring
There allocations are unaccounted in this patch because they are mapped
to userspace, and accounting them to a cgroup causes problems. This
should be addressed in a future patch.

Signed-off-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Shakeel Butt <shakeelb@google.com>
---
 virt/kvm/coalesced_mmio.c |  3 ++-
 virt/kvm/eventfd.c        |  7 ++++---
 virt/kvm/irqchip.c        |  4 ++--
 virt/kvm/kvm_main.c       | 29 +++++++++++++++--------------
 virt/kvm/vfio.c           |  4 ++--
 5 files changed, 25 insertions(+), 22 deletions(-)

```
#### [PATCH] vfio/pci: Restore device state on PM transitionFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
PCI core handles save and restore of device state around reset, but
when using pci_set_power_state() we can unintentionally trigger a soft
reset of the device, where PCI core only restores the BAR state.  If
we're using vfio-pci's idle D3 support to try to put devices into low
power when unused, this might trigger a reset when the device is woken
for use.  Also power state management by the user, or within a guest,
can put the device into D3 power state with potentially limited
ability to restore the device if it should undergo a reset.  The PCI
spec does not define the extent of a soft reset and many devices
reporting soft reset on D3->D0 transition do not undergo a PCI config
space reset.  It's therefore assumed safe to unconditionally restore
the remainder of the state if the device indicates soft reset
support, even on a user initiated wakeup.

Implement a wrapper in vfio-pci to tag devices reporting PM reset
support, save their state on transitions into D3 and restore on
transitions back to D0.

Reported-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c         |   71 +++++++++++++++++++++++++++++++----
 drivers/vfio/pci/vfio_pci_config.c  |    2 -
 drivers/vfio/pci/vfio_pci_private.h |    6 +++
 3 files changed, 70 insertions(+), 9 deletions(-)

```
