
define DEFINE_RAPL_FORMAT_ATTR(_var, _name, _format)
\ static ssize_t __rapl__var_show(struct kobject *kobj, \ struct kobj_attribute *attr, \ char *page)
\ static inline struct rapl_pmu *cpu_to_rapl_pmu(unsigned int cpu)
static inline u64 rapl_read_counter(struct perf_event *event)
static inline u64 rapl_scale(u64 v, int cfg)
static u64 rapl_event_update(struct perf_event *event)
static void rapl_start_hrtimer(struct rapl_pmu *pmu)
static enum hrtimer_restart rapl_hrtimer_handle(struct hrtimer *hrtimer)
static void rapl_hrtimer_init(struct rapl_pmu *pmu)
static void __rapl_pmu_event_start(struct rapl_pmu *pmu, struct perf_event *event)
static void rapl_pmu_event_start(struct perf_event *event, int mode)
static void rapl_pmu_event_stop(struct perf_event *event, int mode)
static int rapl_pmu_event_add(struct perf_event *event, int mode)
static void rapl_pmu_event_del(struct perf_event *event, int flags)
static int rapl_pmu_event_init(struct perf_event *event)
static void rapl_pmu_event_read(struct perf_event *event)
static ssize_t rapl_get_attr_cpumask(struct device *dev, struct device_attribute *attr, char *buf)
static int rapl_cpu_offline(unsigned int cpu)
static int rapl_cpu_online(unsigned int cpu)
static int rapl_check_hw_unit(bool apply_quirk)
static void __init rapl_advertise(void)
static void cleanup_rapl_pmus(void)
static int __init init_rapl_pmus(void)
static int __init rapl_pmu_init(void)
static void __exit intel_rapl_exit(void)
   9 struct perf_event *event
   5 void
   3 unsigned int cpu
   3 struct rapl_pmu *pmu
   3 int mode
   1 u64 v
   1 struct kobject *kobj
   1 struct hrtimer *hrtimer
   1 struct device_attribute *attr
   1 struct device *dev
   1 int flags
   1 int cfg
   1 char *buf
   1 bool apply_quirk
   1 _var
   1 _name
   1 _format
   1 \ struct kobj_attribute *attr
   1 \ char *page
