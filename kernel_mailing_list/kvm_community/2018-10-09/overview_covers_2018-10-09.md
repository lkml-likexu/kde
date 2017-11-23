

#### [PATCH 0/2] Trivial code refine for kvm_main.c
##### From: Wei Yang <richard.weiyang@gmail.com>

```c

Here is two patches to refine kvm_main.c a little.

The first one puts more words to explain the functionality of
gfn_to_hva_memslot_prot().

The second one tries to simplify the code in __gfn_to_pfn_memslot().

Wei Yang (2):
  KVM: refine the comment of function gfn_to_hva_memslot_prot()
  KVM: refine __gfn_to_pfn_memslot() a little

 virt/kvm/kvm_main.c | 26 +++++++++++++-------------
 1 file changed, 13 insertions(+), 13 deletions(-)
```
