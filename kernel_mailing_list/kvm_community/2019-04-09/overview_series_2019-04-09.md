#### [PATCH net] vhost: reject zero size iova range
##### From: Jason Wang <jasowang@redhat.com>

```c
We used to accept zero size iova range which will lead a infinite loop
in translate_desc(). Fixing this by failing the request in this case.

Reported-by: syzbot+d21e6e297322a900c128@syzkaller.appspotmail.com
Fixes: 6b1e6cc7 ("vhost: new device IOTLB API")
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
