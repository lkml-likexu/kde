
\n
static ssize_t online_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t online_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t load_show(struct device *dev, struct device_attribute *attr, char *buf)
void zcrypt_queue_force_online(struct zcrypt_queue *zq, int online)
struct zcrypt_queue *zcrypt_queue_alloc(size_t max_response_size)
void zcrypt_queue_free(struct zcrypt_queue *zq)
static void zcrypt_queue_release(struct kref *kref)
void zcrypt_queue_get(struct zcrypt_queue *zq)
int zcrypt_queue_put(struct zcrypt_queue *zq)
int zcrypt_queue_register(struct zcrypt_queue *zq)
void zcrypt_queue_unregister(struct zcrypt_queue *zq)
\n
      6 struct zcrypt_queue *zq
      3 struct device *dev
      3 struct device_attribute *attr
      2 char *buf
      1 struct kref *kref
      1 size_t max_response_size
      1 size_t count
      1 int online
      1 const char *buf
