#### [RFC PATCH V2 1/3] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain
accessors. About 2% improvement of PPS were seen during vitio-user
txonly test.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
#### [PATCH v1 1/2] virtio_pci: use queue idx instead of array idx to set up the vq
##### From: Wei Wang <wei.w.wang@intel.com>

```c
When find_vqs, there will be no vq[i] allocation if its corresponding
names[i] is NULL. For example, the caller may pass in names[i] (i=4)
with names[2] being NULL because the related feature bit is turned off,
so technically there are 3 queues on the device, and name[4] should
correspond to the 3rd queue on the device.

So we use queue_idx as the queue index, which is increased only when the
queue exists.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/virtio/virtio_pci_common.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
