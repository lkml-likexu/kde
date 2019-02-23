
\n
static ssize_t hwtype_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t raw_hwtype_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t depth_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t ap_functions_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t request_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t request_count_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t requestq_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t pendingq_count_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t modalias_show(struct device *dev, struct device_attribute *attr, char *buf)
static void ap_card_device_release(struct device *dev)
struct ap_card *ap_card_create(int id, int queue_depth, int raw_type, int comp_type, unsigned int functions)
\n
     10 struct device *dev
      9 struct device_attribute *attr
      8 char *buf
      1 unsigned int functions
      1 size_t count
      1 int raw_type
      1 int queue_depth
      1 int id
      1 int comp_type
      1 const char *buf
