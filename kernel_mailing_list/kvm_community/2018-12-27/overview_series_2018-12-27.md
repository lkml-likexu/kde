#### [PATCH]  kvm/eventfd : unnecessory conversion to bool
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
Conversion to bool is not needed in ioeventfd_in_range.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 virt/kvm/eventfd.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
