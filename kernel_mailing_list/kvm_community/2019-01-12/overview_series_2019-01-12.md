#### [PATCH] KVM: MMU: fast cleanup D bit based on fast write protect
##### From: Zhuangyanying <ann.zhuangyanying@huawei.com>

```c
From: Zhuang Yanying <ann.zhuangyanying@huawei.com>

Recently I tested live-migration with large-memory guests, find vcpu may hang for a long time while starting migration, such as 9s for 2048G(linux-4.20.1+qemu-3.1.0).
The reason is memory_global_dirty_log_start() taking too long, and the vcpu is waiting for BQL. The page-by-page D bit clearup is the main time consumption.
I think that the idea of "KVM: MMU: fast write protect" by xiaoguangrong, especially the function kvm_mmu_write_protect_all_pages(), is very helpful.
After a little modifcation, on his patch, can solve this problem, 9s to 0.5s.

At the begining of live migration, write protection is only applied to the top-level SPTE. Then the write from vm trigger the EPT violation, with for_each_shadow_entry write protection is performed at dirct_map.
Finally the Dirty bit of the target page(at level 1 page table) is cleared, and the dirty page tracking is started. Of coure, the page where GPA is located is marked dirty when mmu_set_spte.
A similar implementation on xen, just emt instead of write protection.

What do you think about this solution?
---
 mmu.c | 5 ++++-
 vmx.c | 3 +--
 2 files changed, 5 insertions(+), 3 deletions(-)

```
