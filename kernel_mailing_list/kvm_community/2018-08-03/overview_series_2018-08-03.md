#### [PATCH net-next] vhost: switch to use new message format
##### From: Jason Wang <jasowang@redhat.com>

```c
We use to have message like:

struct vhost_msg {
	int type;
	union {
		struct vhost_iotlb_msg iotlb;
		__u8 padding[64];
	};
};

Unfortunately, there will be a hole of 32bit in 64bit machine because
of the alignment. This leads a different formats between 32bit API and
64bit API. What's more it will break 32bit program running on 64bit
machine.

So fixing this by introducing a new message type with an explicit
32bit reserved field after type like:

struct vhost_msg_v2 {
	int type;
	__u32 reserved;
	union {
		struct vhost_iotlb_msg iotlb;
		__u8 padding[64];
	};
};

We will have a consistent ABI after switching to use this. To enable
this capability, introduce a new ioctl (VHOST_SET_BAKCEND_FEATURE) for
userspace to enable this feature (VHOST_BACKEND_F_IOTLB_V2).

Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/net.c        | 30 ++++++++++++++++++++
 drivers/vhost/vhost.c      | 71 ++++++++++++++++++++++++++++++++++------------
 drivers/vhost/vhost.h      | 11 ++++++-
 include/uapi/linux/vhost.h | 18 ++++++++++++
 4 files changed, 111 insertions(+), 19 deletions(-)

```
