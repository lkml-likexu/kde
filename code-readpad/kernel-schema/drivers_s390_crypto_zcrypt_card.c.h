
\n
static ssize_t type_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t online_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t online_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t load_show(struct device *dev, struct device_attribute *attr, char *buf)
struct zcrypt_card *zcrypt_card_alloc(void)
void zcrypt_card_free(struct zcrypt_card *zc)
static void zcrypt_card_release(struct kref *kref)
void zcrypt_card_get(struct zcrypt_card *zc)
int zcrypt_card_put(struct zcrypt_card *zc)
int zcrypt_card_register(struct zcrypt_card *zc)
void zcrypt_card_unregister(struct zcrypt_card *zc)
\n
      5 struct zcrypt_card *zc
      4 struct device *dev
      4 struct device_attribute *attr
      3 char *buf
      1 void
      1 struct kref *kref
      1 size_t count
      1 const char *buf
