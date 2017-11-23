

#### [PATCH v2 0/3] optimize waiting for free thread to do compression
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Changelog in v2:
squash 'compress-wait-thread-adaptive' into 'compress-wait-thread' based
on peter's suggestion


Currently we have two behaviors if all threads are busy to do compression,
the main thread mush wait one of them becoming free if @compress-wait-thread
set to on or the main thread can directly return without wait and post
the page out as normal one

Both of them have its profits and short-comes, however, if the bandwidth is
not limited extremely so that compression can not use out all of it bandwidth,
at the same time, the migration process is easily throttled if we posted too
may pages as normal pages. None of them can work properly under this case

In order to use the bandwidth more effectively, we introduce the third
behavior, adaptive, which make the main thread wait
if there is no bandwidth left or let the page go out as normal page if there
has enough bandwidth to make sure the migration process will not be
throttled

Another patch introduces a new statistic, pages-per-second, as bandwidth
or mbps is not enough to measure the performance of posting pages out as
we have compression, xbzrle, which can significantly reduce the amount of
the data size, instead, pages-per-second is the one we want

Performance data
================
We have limited the bandwidth to 300

                                Used Bandwidth     Pages-per-Second
compress-wait-thread = on         951.66 mbps         131784

compress-wait-thread = off        2491.74 mbps        93495
compress-wait-thread-adaptive     1982.94 mbps        162529
   = on


Xiao Guangrong (3):
  migration: introduce pages-per-second
  migration: fix memory leak when updating tls-creds and tls-hostname
  migration: introduce adaptive model for waiting thread

 hmp.c                 |   8 ++-
 migration/migration.c | 137 +++++++++++++++++++++++++++++++++++++++++---------
 migration/migration.h |  21 ++++++++
 migration/ram.c       | 122 ++++++++++++++++++++++++++++++++++++++++----
 qapi/migration.json   |  44 +++++++++++-----
 5 files changed, 281 insertions(+), 51 deletions(-)
```
