
\n
static inline int reset_control_reset(struct reset_control *rstc)
static inline int reset_control_assert(struct reset_control *rstc)
static inline int reset_control_deassert(struct reset_control *rstc)
static inline int reset_control_status(struct reset_control *rstc)
static inline void reset_control_put(struct reset_control *rstc)
static inline int __device_reset(struct device *dev, bool optional)
static inline struct reset_control *__of_reset_control_get(struct device_node *node, const char *id, int index, bool shared, bool optional)
static inline struct reset_control *__reset_control_get(struct device *dev, const char *id, int index, bool shared, bool optional)
static inline struct reset_control *__devm_reset_control_get(struct device *dev, const char *id, int index, bool shared, bool optional)
static inline struct reset_control * devm_reset_control_array_get(struct device *dev, bool shared, bool optional)
static inline struct reset_control * of_reset_control_array_get(struct device_node *np, bool shared, bool optional)
static inline int reset_control_get_count(struct device *dev)
static inline int __must_check device_reset(struct device *dev)
static inline int device_reset_optional(struct device *dev)
static inline struct reset_control * __must_check reset_control_get_exclusive(struct device *dev, const char *id)
static inline struct reset_control *reset_control_get_shared(struct device *dev, const char *id)
static inline struct reset_control *reset_control_get_optional_exclusive(struct device *dev, const char *id)
static inline struct reset_control *reset_control_get_optional_shared(struct device *dev, const char *id)
static inline struct reset_control *of_reset_control_get_exclusive( struct device_node *node, const char *id)
static inline struct reset_control *of_reset_control_get_shared( struct device_node *node, const char *id)
static inline struct reset_control *of_reset_control_get_exclusive_by_index(struct device_node *node, int index)
static inline struct reset_control *of_reset_control_get_shared_by_index(struct device_node *node, int index)
static inline struct reset_control * __must_check devm_reset_control_get_exclusive(struct device *dev, const char *id)
static inline struct reset_control *devm_reset_control_get_shared(struct device *dev, const char *id)
static inline struct reset_control *devm_reset_control_get_optional_exclusive(struct device *dev, const char *id)
static inline struct reset_control *devm_reset_control_get_optional_shared(struct device *dev, const char *id)
static inline struct reset_control * devm_reset_control_get_exclusive_by_index(struct device *dev, int index)
static inline struct reset_control * devm_reset_control_get_shared_by_index(struct device *dev, int index)
static inline struct reset_control *of_reset_control_get( struct device_node *node, const char *id)
static inline struct reset_control *of_reset_control_get_by_index( struct device_node *node, int index)
static inline struct reset_control *devm_reset_control_get( struct device *dev, const char *id)
static inline struct reset_control *devm_reset_control_get_optional( struct device *dev, const char *id)
static inline struct reset_control *devm_reset_control_get_by_index( struct device *dev, int index)
static inline struct reset_control * devm_reset_control_array_get_exclusive(struct device *dev)
static inline struct reset_control * devm_reset_control_array_get_shared(struct device *dev)
static inline struct reset_control * devm_reset_control_array_get_optional_exclusive(struct device *dev)
static inline struct reset_control * devm_reset_control_array_get_optional_shared(struct device *dev)
static inline struct reset_control * of_reset_control_array_get_exclusive(struct device_node *node)
static inline struct reset_control * of_reset_control_array_get_shared(struct device_node *node)
static inline struct reset_control * of_reset_control_array_get_optional_exclusive(struct device_node *node)
static inline struct reset_control * of_reset_control_array_get_optional_shared(struct device_node *node)
\n
     24 struct device *dev
     16 const char *id
     11 struct device_node *node
      9 int index
      6 bool optional
      5 struct reset_control *rstc
      5 bool shared
      1 struct device_node *np
