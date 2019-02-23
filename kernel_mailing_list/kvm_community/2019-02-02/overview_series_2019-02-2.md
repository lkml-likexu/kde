#### [PATCH] Revert "KVM: Eliminate extra function calls in kvm_get_dirty_log_protect()"
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

The value of "dirty_bitmap[i]" is already check before setting its value
to mask. The following check of "mask" is redundant. The check of "mask" was
introduced by commit 58d2930f4ee3(("KVM: Eliminate extra function calls in
kvm_get_dirty_log_protect()"). This patch is to revert the patch.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 virt/kvm/kvm_main.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH V2 1/10] X86/Hyper-V: Add parameter offset for hyperv_fill_flush_guest_mapping_list()
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add parameter offset to specify start position to add flush ranges in
guest address list of struct hv_guest_mapping_flush_list.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
arch/x86/hyperv/nested.c        | 4 ++--
 arch/x86/include/asm/mshyperv.h | 2 +-
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
