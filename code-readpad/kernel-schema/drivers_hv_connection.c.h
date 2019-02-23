
EXPORT_SYMBOL_GPL(vmbus_connection);
EXPORT_SYMBOL_GPL(vmbus_proto_version);
EXPORT_SYMBOL_GPL(vmbus_set_event);
\n
static __u32 vmbus_get_next_version(__u32 current_version)
static int vmbus_negotiate_version(struct vmbus_channel_msginfo *msginfo, __u32 version)
int vmbus_connect(void)
void vmbus_disconnect(void)
struct vmbus_channel *relid2channel(u32 relid)
void vmbus_on_event(unsigned long data)
int vmbus_post_msg(void *buffer, size_t buflen, bool can_sleep)
void vmbus_set_event(struct vmbus_channel *channel)
\n
      2 void
      1 void *buffer
      1 vmbus_set_event
      1 vmbus_proto_version
      1 vmbus_connection
      1 unsigned long data
      1 __u32 version
      1 u32 relid
      1 __u32 current_version
      1 struct vmbus_channel_msginfo *msginfo
      1 struct vmbus_channel *channel
      1 size_t buflen
      1 bool can_sleep
