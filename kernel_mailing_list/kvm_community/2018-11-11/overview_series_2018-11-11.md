#### [PATCH tip/core/rcu 14/41] drivers/vhost: Replace synchronize_rcu_bh() with synchronize_rcu()
##### From: "Paul E. McKenney" <paulmck@linux.ibm.com>

```c
Now that synchronize_rcu() waits for bh-disable regions of code as well
as RCU read-side critical sections, synchronize_rcu_bh() can be replaced
by synchronize_rcu().  This commit therefore makes this change.

Signed-off-by: Paul E. McKenney <paulmck@linux.ibm.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: <kvm@vger.kernel.org>
Cc: <virtualization@lists.linux-foundation.org>
Cc: <netdev@vger.kernel.org>
---
 drivers/vhost/net.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
