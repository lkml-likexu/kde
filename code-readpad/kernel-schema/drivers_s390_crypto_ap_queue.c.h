
\n
static int ap_queue_enable_interruption(struct ap_queue *aq, void *ind)
static inline struct ap_queue_status __ap_send(ap_qid_t qid, unsigned long long psmid, void *msg, size_t length, unsigned int special)
int ap_send(ap_qid_t qid, unsigned long long psmid, void *msg, size_t length)
int ap_recv(ap_qid_t qid, unsigned long long *psmid, void *msg, size_t length)
static enum ap_wait ap_sm_nop(struct ap_queue *aq)
static struct ap_queue_status ap_sm_recv(struct ap_queue *aq)
static enum ap_wait ap_sm_read(struct ap_queue *aq)
static enum ap_wait ap_sm_suspend_read(struct ap_queue *aq)
static enum ap_wait ap_sm_write(struct ap_queue *aq)
static enum ap_wait ap_sm_read_write(struct ap_queue *aq)
static enum ap_wait ap_sm_reset(struct ap_queue *aq)
static enum ap_wait ap_sm_reset_wait(struct ap_queue *aq)
static enum ap_wait ap_sm_setirq_wait(struct ap_queue *aq)
enum ap_wait ap_sm_event(struct ap_queue *aq, enum ap_event event)
enum ap_wait ap_sm_event_loop(struct ap_queue *aq, enum ap_event event)
void ap_queue_suspend(struct ap_device *ap_dev)
void ap_queue_resume(struct ap_device *ap_dev)
static ssize_t request_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t request_count_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t requestq_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t pendingq_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t reset_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t reset_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t interrupt_show(struct device *dev, struct device_attribute *attr, char *buf)
static void ap_queue_device_release(struct device *dev)
struct ap_queue *ap_queue_create(ap_qid_t qid, int device_type)
void ap_queue_init_reply(struct ap_queue *aq, struct ap_message *reply)
void ap_queue_message(struct ap_queue *aq, struct ap_message *ap_msg)
void ap_cancel_message(struct ap_queue *aq, struct ap_message *ap_msg)
static void __ap_flush_queue(struct ap_queue *aq)
void ap_flush_queue(struct ap_queue *aq)
void ap_queue_remove(struct ap_queue *aq)
void ap_queue_reinit_state(struct ap_queue *aq)
\n
     19 struct ap_queue *aq
      8 struct device *dev
      7 struct device_attribute *attr
      5 char *buf
      4 ap_qid_t qid
      3 void *msg
      3 size_t length
      2 unsigned long long psmid
      2 struct ap_message *ap_msg
      2 struct ap_device *ap_dev
      2 size_t count
      2 enum ap_event event
      2 const char *buf
      1 void *ind
      1 unsigned long long *psmid
      1 unsigned int special
      1 struct ap_message *reply
      1 int device_type
