#### [PATCH v3 1/4] balloon: Allow multiple inhibit users
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
A simple true/false internal state does not allow multiple users.  Fix
this within the existing interface by converting to a counter, so long
as the counter is elevated, ballooning is inhibited.

Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 balloon.c | 13 ++++++++++---
 1 file changed, 10 insertions(+), 3 deletions(-)

```
#### [PATCH v3 01/10] migration: do not wait for free thread
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

Instead of putting the main thread to sleep state to wait for
free compression thread, we can directly post it out as normal
page that reduces the latency and uses CPUs more efficiently

A parameter, compress-wait-thread, is introduced, it can be
enabled if the user really wants the old behavior

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 hmp.c                 |  8 ++++++++
 migration/migration.c | 21 +++++++++++++++++++++
 migration/migration.h |  1 +
 migration/ram.c       | 45 ++++++++++++++++++++++++++-------------------
 qapi/migration.json   | 23 ++++++++++++++++++-----
 5 files changed, 74 insertions(+), 24 deletions(-)

```
