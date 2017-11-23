
define DEFINE_CSTATE_FORMAT_ATTR(_var, _name, _format)
\ static ssize_t __cstate__var_show(struct kobject *kobj, \ struct kobj_attribute *attr, \ char *page)
\ static ssize_t cstate_get_attr_cpumask(struct device *dev, struct device_attribute *attr, char *buf)
static int cstate_pmu_event_init(struct perf_event *event)
static inline u64 cstate_pmu_read_counter(struct perf_event *event)
static void cstate_pmu_event_update(struct perf_event *event)
static void cstate_pmu_event_start(struct perf_event *event, int mode)
static void cstate_pmu_event_stop(struct perf_event *event, int mode)
static void cstate_pmu_event_del(struct perf_event *event, int mode)
static int cstate_pmu_event_add(struct perf_event *event, int mode)
static int cstate_cpu_exit(unsigned int cpu)
static int cstate_cpu_init(unsigned int cpu)
static bool __init cstate_probe_msr(const unsigned long evmsk, int max, struct perf_cstate_msr *msr, struct attribute **attrs)
static int __init cstate_probe(const struct cstate_model *cm)
static inline void cstate_cleanup(void)
static int __init cstate_init(void)
static int __init cstate_pmu_init(void)
static void __exit cstate_pmu_exit(void)
   7 struct perf_event *event
   4 void
   4 int mode
   2 unsigned int cpu
   1 struct perf_cstate_msr *msr
   1 struct kobject *kobj
   1 struct device_attribute *attr
   1 struct device *dev
   1 struct attribute **attrs
   1 int max
   1 const unsigned long evmsk
   1 const struct cstate_model *cm
   1 char *buf
   1 _var
   1 _name
   1 _format
   1 \ struct kobj_attribute *attr
   1 \ char *page
