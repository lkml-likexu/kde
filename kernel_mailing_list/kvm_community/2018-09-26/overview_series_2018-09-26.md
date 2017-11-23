#### [PATCH 1/2][KVM] nVMX x86: Add a check for reserved bits [11:0] of PML address
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, bits 11:0
of the PML address must be 0.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/include/asm/vmx.h | 2 ++
 arch/x86/kvm/vmx.c         | 3 ++-
 2 files changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v6 01/18] kvm: arm/arm64: Fix stage2_flush_memslot for 4 level page table
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
So far we have only supported 3 level page table with fixed IPA of
40bits, where PUD is folded. With 4 level page tables, we need
to check if the PUD entry is valid or not. Fix stage2_flush_memslot()
to do this check, before walking down the table.

Acked-by: Christoffer Dall <cdall@kernel.org>
Acked-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 virt/kvm/arm/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v3 01/20] KVM: nVMX: move host EFER consistency checks to VMFail path
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Invalid host state related to loading EFER on VMExit causes a
VMFail(VMXERR_ENTRY_INVALID_HOST_STATE_FIELD), not a VMExit.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx.c | 31 ++++++++++++++++---------------
 1 file changed, 16 insertions(+), 15 deletions(-)

```
#### [PATCH v6 1/7] KVM: x86: hyperv: enforce vp_index < KVM_MAX_VCPUS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Hyper-V TLFS (5.0b) states:

> Virtual processors are identified by using an index (VP index). The
> maximum number of virtual processors per partition supported by the
> current implementation of the hypervisor can be obtained through CPUID
> leaf 0x40000005. A virtual processor index must be less than the
> maximum number of virtual processors per partition.

Forbid userspace to set VP_INDEX above KVM_MAX_VCPUS. get_vcpu_by_vpidx()
can now be optimized to bail early when supplied vpidx is >= KVM_MAX_VCPUS.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/kvm/hyperv.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: introduce drop_spte_fast() when caller knows rmap_head
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
rmap_remove() would remove the sptep after locating the correct
rmap_head. While in several cases, the caller has already known the
correct rmap_head.

This patch introduce drop_spte_fast() which remove sptep directly
from rmap_head by pte_list_remove().

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/kvm/mmu.c | 13 ++++++++++---
 1 file changed, 10 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: remove check on nr_mmu_pages in kvm_arch_commit_memory_region()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
* nr_mmu_pages would be non-zero only if kvm->arch.n_requested_mmu_pages is
  non-zero.

* nr_mmu_pages is always non-zero, since kvm_mmu_calculate_mmu_pages()
  never return zero.

Based on these two reasons, we can merge the two *if* clause and use the
return value from kvm_mmu_calculate_mmu_pages() directly.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: remove check on rmap in for_each_slot_rmap_range()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
In loop for_each_slot_rmap_range(), slot_rmap_walk_okay() will check the
rmap before continue the loop body.

This patch removes the duplicate check on rmap in the loop body.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PULL 1/2] virtio/s390: avoid race on vcdev->config
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Halil Pasic <pasic@linux.ibm.com>

Currently we have a race on vcdev->config in virtio_ccw_get_config() and
in virtio_ccw_set_config().

This normally does not cause problems, as these are usually infrequent
operations. However, for some devices writing to/reading from the config
space can be triggered through sysfs attributes. For these, userspace can
force the race by increasing the frequency.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Cc: stable@vger.kernel.org
Message-Id: <20180925121309.58524-2-pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/virtio/virtio_ccw.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
