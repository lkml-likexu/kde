#### [PATCH] KVM: PPC: Book3S HV: Fix race between kvm_unmap_hva_range and MMU mode switch
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Testing has revealed an occasional crash which appears to be caused
by a race between kvmppc_switch_mmu_to_hpt and kvm_unmap_hva_range_hv.
The symptom is a NULL pointer dereference in __find_linux_pte() called
from kvm_unmap_radix() with kvm->arch.pgtable == NULL.

Looking at kvmppc_switch_mmu_to_hpt(), it does indeed clear
kvm->arch.pgtable (via kvmppc_free_radix()) before setting
kvm->arch.radix to NULL, and there is nothing to prevent
kvm_unmap_hva_range_hv() or the other MMU callback functions from
being called concurrently with kvmppc_switch_mmu_to_hpt() or
kvmppc_switch_mmu_to_radix().

This patch therefore adds calls to spin_lock/unlock on the kvm->mmu_lock
around the assignments to kvm->arch.radix, and makes sure that the
partition-scoped radix tree or HPT is only freed after changing
kvm->arch.radix.

This also takes the kvm->mmu_lock in kvmppc_rmap_reset() to make sure
that the clearing of each rmap array (one per memslot) doesn't happen
concurrently with use of the array in the kvm_unmap_hva_range_hv()
or the other MMU callbacks.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c |  3 +++
 arch/powerpc/kvm/book3s_hv.c        | 17 +++++++++++------
 2 files changed, 14 insertions(+), 6 deletions(-)

```
