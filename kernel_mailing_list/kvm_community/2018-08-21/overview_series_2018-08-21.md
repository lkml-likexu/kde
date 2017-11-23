#### [PATCH] KVM: s390: vsie: BUG correction by shadow_crycb
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Copy the key mask to the right offset inside the shadow CRYCB

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/vsie.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 01/10] migration: do not wait for free thread
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

Instead of putting the main thread to sleep state to wait for
free compression thread, we can directly post it out as normal
page that reduces the latency and uses CPUs more efficiently

A parameter, compress-wait-thread, is introduced, it can be
enabled if the user really wants the old behavior

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
Reviewed-by: Juan Quintela <quintela@redhat.com>
---
 hmp.c                 |  8 ++++++++
 migration/migration.c | 21 +++++++++++++++++++++
 migration/migration.h |  1 +
 migration/ram.c       | 45 ++++++++++++++++++++++++++-------------------
 qapi/migration.json   | 27 ++++++++++++++++++++++-----
 5 files changed, 78 insertions(+), 24 deletions(-)

```
