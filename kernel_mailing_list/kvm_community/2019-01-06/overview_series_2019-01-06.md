#### [PATCH V8 01/11] KVM: State whether memory should be freed in kvm_free_memslot
##### From: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>

```c
The conditions upon which kvm_free_memslot are kind of ad-hock,
it will be hard to extend memslot with allocatable data that needs to be
freed, so I replaced the current mechanism by clear flag that states if
the memory slot should be freed.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>
---
 virt/kvm/kvm_main.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
