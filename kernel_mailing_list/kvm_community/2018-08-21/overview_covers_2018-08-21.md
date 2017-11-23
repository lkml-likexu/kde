

#### [PATCH v4 00/10] migration: compression optimization
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Changelog in v4:
These changes are based on the suggestion from Peter Eric.
1) improve qapi's grammar
2) move calling flush_compressed_data to migration_bitmap_sync()
3) rename 'handle_pages' to 'target_page_count'

Note: there is still no clear way to fix handling the error condition
returned by ram_find_and_save_block(), i moved the patch to the end of
this series, hope it's good to help to merge this patchset

Xiao Guangrong (10):
  migration: do not wait for free thread
  migration: fix counting normal page for compression
  migration: introduce save_zero_page_to_file
  migration: drop the return value of do_compress_ram_page
  migration: move handle of zero page to the thread
  migration: hold the lock only if it is really needed
  migration: do not flush_compressed_data at the end of each iteration
  migration: fix calculating xbzrle_counters.cache_miss_rate
  migration: show the statistics of compression
  migration: handle the error condition properly

 hmp.c                 |  21 ++++
 include/qemu/queue.h  |   1 +
 migration/migration.c |  33 +++++
 migration/migration.h |   1 +
 migration/ram.c       | 329 +++++++++++++++++++++++++++++++++++---------------
 migration/ram.h       |   1 +
 qapi/migration.json   |  53 +++++++-
 7 files changed, 333 insertions(+), 106 deletions(-)
```
