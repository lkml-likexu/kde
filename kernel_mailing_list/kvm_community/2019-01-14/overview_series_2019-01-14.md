#### [PATCH kernel] KVM: PPC: Fix compile when CONFIG_PPC_RADIX_MMU is not defined
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
This adds some stubs for hash only configs.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 .../include/asm/book3s/64/tlbflush-radix.h    | 30 +++++++++++++++----
 1 file changed, 24 insertions(+), 6 deletions(-)

```
