
\n
static inline int __must_check class_create_file(struct class *class, const struct class_attribute *attr)
static inline void class_remove_file(struct class *class, const struct class_attribute *attr)
extern void *__devres_alloc_node(dr_release_t release, size_t size, gfp_t gfp, int nid, const char *name)
__malloc;define devres_alloc(release, size, gfp)
\__devres_alloc_node(release, size, gfp, NUMA_NO_NODE, release)
define devres_alloc_node(release, size, gfp, nid)
\__devres_alloc_node(release, size, gfp, nid, release)
extern void *devres_alloc_node(dr_release_t release, size_t size, gfp_t gfp, int nid)
__malloc; static inline void *devres_alloc(dr_release_t release, size_t size, gfp_t gfp)
extern void *devm_kmalloc(struct device *dev, size_t size, gfp_t gfp)
__malloc; extern __printf(3, 0)
char *devm_kvasprintf(struct device *dev, gfp_t gfp, const char *fmt, va_list ap)
__malloc; extern __printf(3, 4)
char *devm_kasprintf(struct device *dev, gfp_t gfp, const char *fmt, ...)
__malloc; static inline void *devm_kzalloc(struct device *dev, size_t size, gfp_t gfp)
extern void *devm_kmalloc(struct device *dev, size_t size, gfp_t gfp)
__malloc; extern __printf(3, 0)
char *devm_kvasprintf(struct device *dev, gfp_t gfp, const char *fmt, va_list ap)
__malloc; extern __printf(3, 4)
char *devm_kasprintf(struct device *dev, gfp_t gfp, const char *fmt, ...)
__malloc; static inline void *devm_kzalloc(struct device *dev, size_t size, gfp_t gfp)
return devm_kmalloc(dev, size, gfp | __GFP_ZERO)
; } static inline void *devm_kmalloc_array(struct device *dev, size_t n, size_t size, gfp_t flags)
return devm_kmalloc(dev, bytes, flags)
; } static inline void *devm_kcalloc(struct device *dev, size_t n, size_t size, gfp_t flags)
static inline int devm_add_action_or_reset(struct device *dev, void (*action)
(void *)
, void *data)
static inline void device_connections_add(struct device_connection *cons)
static inline void device_connections_remove(struct device_connection *cons)
static inline struct device *kobj_to_dev(struct kobject *kobj)
static inline bool device_iommu_mapped(struct device *dev)
static inline const char *dev_name(const struct device *dev)
static inline int dev_to_node(struct device *dev)
static inline int dev_to_node(struct device *dev)
return dev->numa_node; } static inline void set_dev_node(struct device *dev, int node)
static inline int dev_to_node(struct device *dev)
return dev->numa_node; } static inline void set_dev_node(struct device *dev, int node)
dev->numa_node = node; } static inline int dev_to_node(struct device *dev)
static inline int dev_to_node(struct device *dev)
return dev->numa_node; } static inline void set_dev_node(struct device *dev, int node)
dev->numa_node = node; } static inline int dev_to_node(struct device *dev)
return -1; } static inline void set_dev_node(struct device *dev, int node)
static inline struct irq_domain *dev_get_msi_domain(const struct device *dev)
static inline void dev_set_msi_domain(struct device *dev, struct irq_domain *d)
static inline void *dev_get_drvdata(const struct device *dev)
static inline void dev_set_drvdata(struct device *dev, void *data)
static inline struct pm_subsys_data *dev_to_psd(struct device *dev)
static inline unsigned int dev_get_uevent_suppress(const struct device *dev)
static inline void dev_set_uevent_suppress(struct device *dev, int val)
static inline int device_is_registered(struct device *dev)
static inline void device_enable_async_suspend(struct device *dev)
static inline void device_disable_async_suspend(struct device *dev)
static inline bool device_async_suspend_enabled(struct device *dev)
static inline void dev_pm_syscore_device(struct device *dev, bool val)
static inline void dev_pm_set_driver_flags(struct device *dev, u32 flags)
static inline bool dev_pm_test_driver_flags(struct device *dev, u32 flags)
static inline void device_lock(struct device *dev)
static inline int device_lock_interruptible(struct device *dev)
static inline int device_trylock(struct device *dev)
static inline void device_unlock(struct device *dev)
static inline void device_lock_assert(struct device *dev)
static inline struct device_node *dev_of_node(struct device *dev)
static inline bool device_supports_offline(struct device *dev)
static inline int dev_num_vf(struct device *dev)
static inline void *dev_get_platdata(const struct device *dev)
static inline int __must_check device_add_group(struct device *dev, const struct attribute_group *grp)
static inline void device_remove_group(struct device *dev, const struct attribute_group *grp)
static inline __printf(3, 0)
int dev_vprintk_emit(int level, const struct device *dev, const char *fmt, va_list args)
static inline __printf(3, 0)
int dev_vprintk_emit(int level, const struct device *dev, const char *fmt, va_list args)
static inline __printf(3, 4)
int dev_printk_emit(int level, const struct device *dev, const char *fmt, ...)
static inline void __dev_printk(const char *level, const struct device *dev, struct va_format *vaf)
static inline void __dev_printk(const char *level, const struct device *dev, struct va_format *vaf)
static inline __printf(3, 4)
void dev_printk(const char *level, const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_alert(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_alert(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_err(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_alert(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_err(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_warn(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_alert(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_err(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_warn(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_notice(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_emerg(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_crit(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_alert(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_err(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_warn(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_notice(const struct device *dev, const char *fmt, ...)
static inline __printf(2, 3)
void _dev_info(const struct device *dev, const char *fmt, ...)
define module_driver(__driver, __register, __unregister, ...)
\ static int __init __driver_init(void)
\ define module_driver(__driver, __register, __unregister, ...)
\ static int __init __driver_init(void)
\return __register(&(__driver)
, __VA_ARGS__)
; \ } \ module_init(__driver_init)
; \ static void __exit __driver_exit(void)
\ define builtin_driver(__driver, __register, ...)
\ static int __init __driver_init(void)
\ \n
     43 struct device *dev
     39 const struct device *dev
     36 const char *fmt
     36 3
     35 ...
     28 2
     11 gfp_t gfp
      9 size_t size
      6 release
      5 size
      4 void
      4 int node
      4 gfp
      4 4
      4 0
      3 __register
      3 int level
      3 dr_release_t release
      3 __driver
      3 const char *level
      2 va_list args
      2 va_list ap
      2 __unregister
      2 u32 flags
      2 struct va_format *vaf
      2 struct device_connection *cons
      2 struct class *class
      2 size_t n
      2 nid
      2 int nid
      2 gfp_t flags
      2 dev
      2 const struct class_attribute *attr
      2 const struct attribute_group *grp
      1 void *data
      1 void *action
      1 void *
      1 struct kobject *kobj
      1 struct irq_domain *d
      1 NUMA_NO_NODE
      1 int val
      1 gfp | __GFP_ZERO
      1 flags
      1 __driver_init
      1 &__driver
      1 const char *name
      1 bytes
      1 bool val
