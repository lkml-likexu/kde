#### [PATCH] KVM: x86: fix warning Using plain integer as NULL pointer
##### From: Hariprasad Kelam <hariprasad.kelam@gmail.com>

```c
Changed passing argument as "0 to NULL" which resolves below sparse warning

arch/x86/kvm/x86.c:3096:61: warning: Using plain integer as NULL pointer

Signed-off-by: Hariprasad Kelam <hariprasad.kelam@gmail.com>
Reviewed-by: Mukesh Ojha <mojha@codeaurora.org>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
