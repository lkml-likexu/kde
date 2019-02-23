
EXPORT_SYMBOL_GPL(perf_assign_events);
EXPORT_SYMBOL_GPL(events_sysfs_show);
EXPORT_SYMBOL_GPL(perf_get_x86_pmu_capability);
\n
u64 x86_perf_event_update(struct perf_event *event)
static int x86_pmu_extra_regs(u64 config, struct perf_event *event)
static bool reserve_pmc_hardware(void)
static void release_pmc_hardware(void)
static bool check_hw_exists(void)
static void hw_perf_event_destroy(struct perf_event *event)
void hw_perf_lbr_event_destroy(struct perf_event *event)
static inline int x86_pmu_initialized(void)
static inline int set_ext_hw_attr(struct hw_perf_event *hwc, struct perf_event *event)
int x86_reserve_hardware(void)
void x86_release_hardware(void)
int x86_add_exclusive(unsigned int what)
void x86_del_exclusive(unsigned int what)
int x86_setup_perfctr(struct perf_event *event)
static inline int precise_br_compat(struct perf_event *event)
int x86_pmu_max_precise(void)
int x86_pmu_hw_config(struct perf_event *event)
static int __x86_pmu_event_init(struct perf_event *event)
void x86_pmu_disable_all(void)
static void x86_pmu_disable(struct pmu *pmu)
void x86_pmu_enable_all(int added)
static inline int is_x86_event(struct perf_event *event)
static void perf_sched_init(struct perf_sched *sched, struct event_constraint **constraints, int num, int wmin, int wmax, int gpmax)
static void perf_sched_save_state(struct perf_sched *sched)
static bool perf_sched_restore_state(struct perf_sched *sched)
static bool __perf_sched_find_counter(struct perf_sched *sched)
static bool perf_sched_find_counter(struct perf_sched *sched)
static bool perf_sched_next_event(struct perf_sched *sched)
int perf_assign_events(struct event_constraint **constraints, int n, int wmin, int wmax, int gpmax, int *assign)
int x86_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
static int collect_events(struct cpu_hw_events *cpuc, struct perf_event *leader, bool dogrp)
static inline void x86_assign_hw_event(struct perf_event *event, struct cpu_hw_events *cpuc, int i)
int x86_perf_rdpmc_index(struct perf_event *event)
static inline int match_prev_assignment(struct hw_perf_event *hwc, struct cpu_hw_events *cpuc, int i)
static void x86_pmu_enable(struct pmu *pmu)
int x86_perf_event_set_period(struct perf_event *event)
void x86_pmu_enable_event(struct perf_event *event)
static int x86_pmu_add(struct perf_event *event, int flags)
static void x86_pmu_start(struct perf_event *event, int flags)
void perf_event_print_debug(void)
void x86_pmu_stop(struct perf_event *event, int flags)
static void x86_pmu_del(struct perf_event *event, int flags)
int x86_pmu_handle_irq(struct pt_regs *regs)
void perf_events_lapic_init(void)
static int perf_event_nmi_handler(unsigned int cmd, struct pt_regs *regs)
static int x86_pmu_prepare_cpu(unsigned int cpu)
static int x86_pmu_dead_cpu(unsigned int cpu)
static int x86_pmu_online_cpu(unsigned int cpu)
static int x86_pmu_starting_cpu(unsigned int cpu)
static int x86_pmu_dying_cpu(unsigned int cpu)
static void __init pmu_check_apic(void)
static void __init filter_events(struct attribute **attrs)
__init struct attribute **merge_attr(struct attribute **a, struct attribute **b)
ssize_t events_sysfs_show(struct device *dev, struct device_attribute *attr, char *page)
ssize_t events_ht_sysfs_show(struct device *dev, struct device_attribute *attr, char *page)
ssize_t x86_event_sysfs_show(char *page, u64 config, u64 event)
static int __init init_hw_perf_events(void)
static inline void x86_pmu_read(struct perf_event *event)
static void x86_pmu_start_txn(struct pmu *pmu, unsigned int txn_flags)
static void x86_pmu_cancel_txn(struct pmu *pmu)
static int x86_pmu_commit_txn(struct pmu *pmu)
cpuc->txn_flags = 0;perf_pmu_enable(pmu)
;return 0; }static void free_fake_cpuc(struct cpu_hw_events *cpuc)
static struct cpu_hw_events *allocate_fake_cpuc(void)
static int validate_event(struct perf_event *event)
static int validate_group(struct perf_event *event)
static int x86_pmu_event_init(struct perf_event *event)
static void refresh_pce(void *ignored)
static void x86_pmu_event_mapped(struct perf_event *event, struct mm_struct *mm)
static void x86_pmu_event_unmapped(struct perf_event *event, struct mm_struct *mm)
static int x86_pmu_event_idx(struct perf_event *event)
static ssize_t get_attr_rdpmc(struct device *cdev, struct device_attribute *attr, char *buf)
static ssize_t set_attr_rdpmc(struct device *cdev, struct device_attribute *attr, const char *buf, size_t count)
static ssize_t max_precise_show(struct device *cdev, struct device_attribute *attr, char *buf)
static void x86_pmu_sched_task(struct perf_event_context *ctx, bool sched_in)
void perf_check_microcode(void)
static int x86_pmu_check_period(struct perf_event *event, u64 value)
void arch_perf_update_userpage(struct perf_event *event, struct perf_event_mmap_page *userpg, u64 now)
void perf_callchain_kernel(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
static inline int valid_user_frame(const void __user *fp, unsigned long size)
static unsigned long get_segment_base(unsigned int segment)
static inline int perf_callchain_user32(struct pt_regs *regs, struct perf_callchain_entry_ctx *entry)
perf_callchain_store(entry, cs_base + frame.return_address)
; fp = compat_ptr(ss_base + frame.next_frame)
;}pagefault_enable()
;return 1; } static inline int perf_callchain_user32(struct pt_regs *regs, struct perf_callchain_entry_ctx *entry)
void perf_callchain_user(struct perf_callchain_entry_ctx *entry, struct pt_regs *regs)
static unsigned long code_segment_base(struct pt_regs *regs)
unsigned long perf_instruction_pointer(struct pt_regs *regs)
unsigned long perf_misc_flags(struct pt_regs *regs)
void perf_get_x86_pmu_capability(struct x86_pmu_capability *cap)
\n
     27 struct perf_event *event
     14 void
      9 struct pt_regs *regs
      6 struct perf_sched *sched
      5 unsigned int cpu
      5 struct pmu *pmu
      5 struct device_attribute *attr
      5 struct cpu_hw_events *cpuc
      4 struct perf_callchain_entry_ctx *entry
      4 int flags
      3 struct device *cdev
      3 char *page
      2 unsigned int what
      2 u64 config
      2 struct mm_struct *mm
      2 struct hw_perf_event *hwc
      2 struct event_constraint **constraints
      2 struct device *dev
      2 int wmin
      2 int wmax
      2 int n
      2 int i
      2 int gpmax
      2 int *assign
      2 char *buf
      1 void *ignored
      1 unsigned long size
      1 unsigned int txn_flags
      1 unsigned int segment
      1 unsigned int cmd
      1 u64 value
      1 u64 now
      1 u64 event
      1 struct x86_pmu_capability *cap
      1 struct perf_event_mmap_page *userpg
      1 struct perf_event *leader
      1 struct perf_event_context *ctx
      1 struct attribute **b
      1 struct attribute **attrs
      1 struct attribute **a
      1 ss_base + frame.next_frame
      1 size_t count
      1 pmu
      1 perf_get_x86_pmu_capability
      1 perf_assign_events
      1 int num
      1 int added
      1 events_sysfs_show
      1 entry
      1 cs_base + frame.return_address
      1 const void __user *fp
      1 const char *buf
      1 bool sched_in
      1 bool dogrp
      1 
