#### [PATCH 1/1] vhost: change the signature of __vhost_get_user_slow()
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Remove 'type' from the signature of __vhost_get_user_slow() as it is not
used.

Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
---
 drivers/vhost/vhost.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
