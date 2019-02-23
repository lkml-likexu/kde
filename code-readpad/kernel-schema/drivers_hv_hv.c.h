
\n
int hv_init(void)
int hv_post_message(union hv_connection_id connection_id, enum hv_message_type message_type, void *payload, size_t payload_size)
static void hv_stimer0_isr(void)
static int hv_ce_set_next_event(unsigned long delta, struct clock_event_device *evt)
static int hv_ce_shutdown(struct clock_event_device *evt)
static int hv_ce_set_oneshot(struct clock_event_device *evt)
static void hv_init_clockevent_device(struct clock_event_device *dev, int cpu)
int hv_synic_alloc(void)
void hv_synic_free(void)
int hv_synic_init(unsigned int cpu)
void hv_synic_clockevents_cleanup(void)
int hv_synic_cleanup(unsigned int cpu)
\n
      5 void
      3 struct clock_event_device *evt
      2 unsigned int cpu
      1 void *payload
      1 unsigned long delta
      1 union hv_connection_id connection_id
      1 struct clock_event_device *dev
      1 size_t payload_size
      1 int cpu
      1 enum hv_message_type message_type
