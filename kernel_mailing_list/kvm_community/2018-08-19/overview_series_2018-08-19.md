#### [PATCH 1/2] kvm: leverage change to adjust slots->used_slots in update_memslots()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
update_memslots() is only called by __kvm_set_memory_region(), in which
change is calculated to indicate the following behavior. With this
information, it is not necessary to do the calculation again in
update_memslots().

By encoding the number of slot adjustment in the lowest byte of change,
the slots->used_slots adjustment is accomplished by one addition.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 include/linux/kvm_host.h | 11 +++++++----
 virt/kvm/kvm_main.c      | 14 ++++----------
 2 files changed, 11 insertions(+), 14 deletions(-)

```
