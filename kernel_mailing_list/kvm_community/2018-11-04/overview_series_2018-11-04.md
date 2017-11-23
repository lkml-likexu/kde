#### [PATCH V6 1/8] KVM: State whether memory should be freed in kvm_free_memslot
##### From: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>

```c
The conditions upon which kvm_free_memslot are kind of confusing,
it will be hard to extend memslot with allocatable data that needs to be
freed, so I replaced the current mechanism by the change flag, it states if
the memory slot should be freed or not.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>
---
 virt/kvm/kvm_main.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
