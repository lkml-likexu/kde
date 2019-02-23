
EXPORT_SYMBOL_GPL(reset_controller_register);
EXPORT_SYMBOL_GPL(reset_controller_unregister);
EXPORT_SYMBOL_GPL(devm_reset_controller_register);
EXPORT_SYMBOL_GPL(reset_controller_add_lookup);
EXPORT_SYMBOL_GPL(reset_control_reset);
EXPORT_SYMBOL_GPL(reset_control_assert);
EXPORT_SYMBOL_GPL(reset_control_deassert);
EXPORT_SYMBOL_GPL(reset_control_status);
EXPORT_SYMBOL_GPL(__of_reset_control_get);
EXPORT_SYMBOL_GPL(__reset_control_get);
EXPORT_SYMBOL_GPL(reset_control_put);
EXPORT_SYMBOL_GPL(__devm_reset_control_get);
EXPORT_SYMBOL_GPL(__device_reset);
EXPORT_SYMBOL_GPL(of_reset_control_array_get);
EXPORT_SYMBOL_GPL(devm_reset_control_array_get);
EXPORT_SYMBOL_GPL(reset_control_get_count);
\n
static int of_reset_simple_xlate(struct reset_controller_dev *rcdev, const struct of_phandle_args *reset_spec)
int reset_controller_register(struct reset_controller_dev *rcdev)
void reset_controller_unregister(struct reset_controller_dev *rcdev)
static void devm_reset_controller_release(struct device *dev, void *res)
int devm_reset_controller_register(struct device *dev, struct reset_controller_dev *rcdev)
void reset_controller_add_lookup(struct reset_control_lookup *lookup, unsigned int num_entries)
static int reset_control_array_reset(struct reset_control_array *resets)
static int reset_control_array_assert(struct reset_control_array *resets)
static int reset_control_array_deassert(struct reset_control_array *resets)
static inline bool reset_control_is_array(struct reset_control *rstc)
int reset_control_reset(struct reset_control *rstc)
int reset_control_assert(struct reset_control *rstc)
int reset_control_deassert(struct reset_control *rstc)
int reset_control_status(struct reset_control *rstc)
static struct reset_control *__reset_control_get_internal( struct reset_controller_dev *rcdev, unsigned int index, bool shared)
static void __reset_control_release(struct kref *kref)
static void __reset_control_put_internal(struct reset_control *rstc)
struct reset_control *__of_reset_control_get(struct device_node *node, const char *id, int index, bool shared, bool optional)
static struct reset_controller_dev * __reset_controller_by_name(const char *name)
static struct reset_control * __reset_control_get_from_lookup(struct device *dev, const char *con_id, bool shared, bool optional)
struct reset_control *__reset_control_get(struct device *dev, const char *id, int index, bool shared, bool optional)
static void reset_control_array_put(struct reset_control_array *resets)
void reset_control_put(struct reset_control *rstc)
static void devm_reset_control_release(struct device *dev, void *res)
struct reset_control *__devm_reset_control_get(struct device *dev, const char *id, int index, bool shared, bool optional)
int __device_reset(struct device *dev, bool optional)
static int of_reset_control_get_count(struct device_node *node)
struct reset_control * of_reset_control_array_get(struct device_node *np, bool shared, bool optional)
struct reset_control * devm_reset_control_array_get(struct device *dev, bool shared, bool optional)
static int reset_control_get_count_from_lookup(struct device *dev)
int reset_control_get_count(struct device *dev)
\n
     10 struct device *dev
      7 struct reset_control *rstc
      7 bool shared
      7 bool optional
      5 struct reset_controller_dev *rcdev
      4 struct reset_control_array *resets
      3 int index
      3 const char *id
      2 void *res
      2 struct device_node *node
      1 unsigned int num_entries
      1 unsigned int index
      1 struct reset_control_lookup *lookup
      1 struct kref *kref
      1 struct device_node *np
      1 reset_control_status
      1 reset_control_reset
      1 reset_control_put
      1 reset_controller_unregister
      1 reset_controller_register
      1 reset_controller_add_lookup
      1 reset_control_get_count
      1 __reset_control_get
      1 reset_control_deassert
      1 reset_control_assert
      1 __of_reset_control_get
      1 of_reset_control_array_get
      1 devm_reset_controller_register
      1 __devm_reset_control_get
      1 devm_reset_control_array_get
      1 __device_reset
      1 const struct of_phandle_args *reset_spec
      1 const char *name
      1 const char *con_id
