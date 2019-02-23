
\n
struct device *mdev_parent_dev(struct mdev_device *mdev)
void *mdev_get_drvdata(struct mdev_device *mdev)
void mdev_set_drvdata(struct mdev_device *mdev, void *data)
struct device *mdev_dev(struct mdev_device *mdev)
struct mdev_device *mdev_from_dev(struct device *dev)
uuid_le mdev_uuid(struct mdev_device *mdev)
static struct mdev_parent *__find_parent_device(struct device *dev)
static void mdev_release_parent(struct kref *kref)
static inline struct mdev_parent *mdev_get_parent(struct mdev_parent *parent)
static inline void mdev_put_parent(struct mdev_parent *parent)
static int mdev_device_create_ops(struct kobject *kobj, struct mdev_device *mdev)
static int mdev_device_remove_ops(struct mdev_device *mdev, bool force_remove)
static int mdev_device_remove_cb(struct device *dev, void *data)
int mdev_register_device(struct device *dev, const struct mdev_parent_ops *ops)
void mdev_unregister_device(struct device *dev)
static void mdev_device_release(struct device *dev)
int mdev_device_create(struct kobject *kobj, struct device *dev, uuid_le uuid)
int mdev_device_remove(struct device *dev, bool force_remove)
static int __init mdev_init(void)
static void __exit mdev_exit(void)
\n
      8 struct device *dev
      7 struct mdev_device *mdev
      2 void *data
      2 void
      2 struct mdev_parent *parent
      2 struct kobject *kobj
      2 bool force_remove
      1 uuid_le uuid
      1 struct kref *kref
      1 const struct mdev_parent_ops *ops
