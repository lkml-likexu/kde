

#### [PATCH kvmtool 0/3] Fix GCC 8 warnings
##### From: Anisse Astier <aastier@freebox.fr>

```c

Hi,

This patch series fixes a few warnings when building kvmtool with GCC8.
I'm not sure it's the best solution for each case.

Note that kvmtool was removed from Debian testing following these
warnings (but it's using an old version):
https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=897777

I do not know why it wasn't built with WERROR=0 instead.

Regards,

Anisse
---
Anisse Astier (3):
  builtin-run: Fix warning when resolving path
  virtio: fix warning on strncpy
  kvmtool: 9p: fix overapping snprintf

 builtin-run.c | 4 +++-
 virtio/9p.c   | 9 ++++++++-
 virtio/net.c  | 4 ++--
 3 files changed, 13 insertions(+), 4 deletions(-)
```
#### [PATCH 0/4] KVM: MMU: fast cleanup D bit based on fast write protect
##### From: Zhuangyanying <ann.zhuangyanying@huawei.com>
From: Zhuang Yanying <ann.zhuangyanying@huawei.com>

```c

From: Zhuang Yanying <ann.zhuangyanying@huawei.com>

Recently I tested live-migration with large-memory guests, find vcpu may hang for a long time while starting migration, such as 9s for 2048G(linux-5.0.0-rc2+qemu-3.1.0).
The reason is memory_global_dirty_log_start() taking too long, and the vcpu is waiting for BQL. The page-by-page D bit clearup is the main time consumption.
I think that the idea of "KVM: MMU: fast write protect" by xiaoguangrong, especially the function kvm_mmu_write_protect_all_pages(), is very helpful.
After a little modifcation, on his patch, can solve this problem, 9s to 0.5s.

At the begining of live migration, write protection is only applied to the top-level SPTE. Then the write from vm trigger the EPT violation, with for_each_shadow_entry write protection is performed at dirct_map.
Finally the Dirty bit of the target page(at level 1 page table) is cleared, and the dirty page tracking is started. Of coure, the page where GPA is located is marked dirty when mmu_set_spte.
A similar implementation on xen, just emt instead of write protection.

What do you think about this solution?

Xiao Guangrong (3):
  KVM: MMU: correct the behavior of mmu_spte_update_no_track
  KVM: MMU: introduce possible_writable_spte_bitmap
  KVM: MMU: introduce kvm_mmu_write_protect_all_pages

Zhuang Yanying (1):
  KVM: MMU: fast cleanup D bit based on fast write protect

 arch/x86/include/asm/kvm_host.h |  25 +++-
 arch/x86/kvm/mmu.c              | 259 ++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/mmu.h              |   1 +
 arch/x86/kvm/paging_tmpl.h      |  13 +-
 arch/x86/kvm/vmx/vmx.c          |   3 +-
 5 files changed, 286 insertions(+), 15 deletions(-)
```
#### [PATCH 0/2] x86/kvm/hyper-v: fix KVM_CAP_HYPERV_ENLIGHTENED_VMCS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Commit e2e871ab2f02 ("x86/kvm/hyper-v: Introduce nested_get_evmcs_version()
helper") broke KVM_CAP_HYPERV_ENLIGHTENED_VMCS: the returned evmcs version
is always zero now. Fix the issue and add a check to evmcs selftest.

The offending commit is in 5.0-rc1, it would be great if the fix could be
queued before 5.0.

Vitaly Kuznetsov (2):
  x86/kvm/hyper-v: nested_enable_evmcs() sets vmcs_version incorrectly
  KVM: selftests: check returned evmcs version range

 arch/x86/kvm/vmx/evmcs.c                        | 7 ++++---
 tools/testing/selftests/kvm/x86_64/evmcs_test.c | 6 ++++++
 2 files changed, 10 insertions(+), 3 deletions(-)
```
