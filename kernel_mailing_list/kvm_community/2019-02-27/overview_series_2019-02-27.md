#### [PATCH] pwoerpc: Enable HTM capability for h_cede_tm testcase
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
The h_cede_tm case is specifically about an edge case with the H_CEDE
hypercall while using hardware transactional memory (HTM).  Current qemu
versions don't enable HTM instructions in guests by default, so we should
explicitly enable them in order to execute this test.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 powerpc/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
