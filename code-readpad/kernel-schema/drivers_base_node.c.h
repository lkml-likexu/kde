
static ssize_t node_read_cpumap(struct device *dev, bool list, char *buf)
static inline ssize_t node_read_cpumask(struct device *dev, struct device_attribute *attr, char *buf)
static inline ssize_t node_read_cpumask(struct device *dev, struct device_attribute *attr, char *buf)
return node_read_cpumap(dev, false, buf)
; } static inline ssize_t node_read_cpulist(struct device *dev, struct device_attribute *attr, char *buf)
define K(x)
((x)
<< (PAGE_SHIFT - 10)
)
static ssize_t node_read_meminfo(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t node_read_numastat(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t node_read_vmstat(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t node_read_distance(struct device *dev, struct device_attribute *attr, char *buf)
static inline bool hugetlb_register_node(struct node *node)
static inline void hugetlb_unregister_node(struct node *node)
void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
static void node_device_release(struct device *dev)
static int register_node(struct node *node, int num)
void unregister_node(struct node *node)
int register_cpu_under_node(unsigned int cpu, unsigned int nid)
int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
static int __ref get_nid_for_pfn(unsigned long pfn)
int register_mem_sect_under_node(struct memory_block *mem_blk, void *arg)
int unregister_mem_sect_under_nodes(struct memory_block *mem_blk, unsigned long phys_index)
int link_mem_sections(int nid, unsigned long start_pfn, unsigned long end_pfn)
static void node_hugetlb_work(struct work_struct *work)
static void init_node_hugetlb_work(int nid)
static int node_memory_callback(struct notifier_block *self, unsigned long action, void *arg)
!defined(CONFIG_HUGETLBFS)
static inline int node_memory_callback(struct notifier_block *self, unsigned long action, void *arg)
int __register_one_node(int nid)
void unregister_one_node(int nid)
static ssize_t print_nodes_state(enum node_states state, char *buf)
static ssize_t show_node_state(struct device *dev, struct device_attribute *attr, char *buf)
define NODE_CALLBACK_PRI 2static int __init register_node_type(void)
  10 struct device *dev
  10 char *buf
   8 struct device_attribute *attr
   4 struct node *node
   4 int nid
   3 void *arg
   2 x
   2 unsigned long action
   2 unsigned int nid
   2 unsigned int cpu
   2 struct notifier_block *self
   2 struct memory_block *mem_blk
   1 void
   1 unsigned long start_pfn
   1 unsigned long phys_index
   1 unsigned long pfn
   1 unsigned long end_pfn
   1 struct work_struct *work
   1 node_registration_func_t unregister
   1 node_registration_func_t doregister
   1 int num
   1 false
   1 enum node_states state
   1 dev
   1 buf
   1 bool list
   1 PAGE_SHIFT - 10
   1 CONFIG_HUGETLBFS
