#### [PATCH net] vhost: Fix Spectre V1 vulnerability
##### From: Jason Wang <jasowang@redhat.com>

```c
The idx in vhost_vring_ioctl() was controlled by userspace, hence a
potential exploitation of the Spectre variant 1 vulnerability.

Fixing this by sanitizing idx before using it to index d->vqs.

Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 2 ++
 1 file changed, 2 insertions(+)

```
