#### [PATCH v2 RFC] x86/kvm/mmu: make mmu->prev_roots cache work for NPT case
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Alternative patch: remove the filtering from kvm_mmu_get_page() and check
for direct on call sites. cr4_pae setting in kvm_calc_mmu_role_common()
can be preserved for consistency.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
