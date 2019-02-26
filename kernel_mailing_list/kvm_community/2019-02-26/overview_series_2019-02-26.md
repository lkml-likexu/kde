#### [Update PATCH V3 1/10] X86/Hyper-V: Add parameter offset for hyperv_fill_flush_guest_mapping_list()
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add parameter offset to specify start position to add flush ranges in
guest address list of struct hv_guest_mapping_flush_list.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Update "offset" parameter's type of hyperv_fill_flush_guest_mapping_list()

 arch/x86/hyperv/nested.c        | 4 ++--
 arch/x86/include/asm/mshyperv.h | 2 +-
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
