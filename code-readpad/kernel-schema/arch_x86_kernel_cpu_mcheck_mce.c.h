
EXPORT_SYMBOL_GPL(mce_inject_log);
EXPORT_SYMBOL_GPL(mce_register_decode_chain);
EXPORT_SYMBOL_GPL(mce_unregister_decode_chain);
EXPORT_SYMBOL_GPL(mce_is_memory_error);
EXPORT_SYMBOL_GPL(machine_check_poll);
EXPORT_SYMBOL_GPL(do_machine_check);
EXPORT_SYMBOL_GPL(mce_notify_irq);
EXPORT_SYMBOL_GPL(mcsafe_key);
void mce_setup(struct mce *m)
void mce_log(struct mce *m)
void mce_inject_log(struct mce *m)
void mce_register_decode_chain(struct notifier_block *nb)
void mce_unregister_decode_chain(struct notifier_block *nb)
static inline u32 ctl_reg(int bank)
static inline u32 status_reg(int bank)
static inline u32 addr_reg(int bank)
static inline u32 misc_reg(int bank)
static inline u32 smca_ctl_reg(int bank)
static inline u32 smca_status_reg(int bank)
static inline u32 smca_addr_reg(int bank)
static inline u32 smca_misc_reg(int bank)
static void __print_mce(struct mce *m)
static void print_mce(struct mce *m)
static void wait_for_panic(void)
static void mce_panic(const char *msg, struct mce *final, char *exp)
static int msr_to_offset(u32 msr)
static u64 mce_rdmsrl(u32 msr)
static void mce_wrmsrl(u32 msr, u64 v)
static inline void mce_gather_info(struct mce *m, struct pt_regs *regs)
int mce_available(struct cpuinfo_x86 *c)
static void mce_schedule_work(void)
static void mce_irq_work_cb(struct irq_work *entry)
static void mce_report_event(struct pt_regs *regs)
static int mce_usable_address(struct mce *m)
bool mce_is_memory_error(struct mce *m)
static bool mce_is_correctable(struct mce *m)
static bool cec_add_mce(struct mce *m)
static int mce_first_notifier(struct notifier_block *nb, unsigned long val, void *data)
static int srao_decode_notifier(struct notifier_block *nb, unsigned long val, void *data)
static int mce_default_notifier(struct notifier_block *nb, unsigned long val, void *data)
static void mce_read_aux(struct mce *m, int i)
bool machine_check_poll(enum mcp_flags flags, mce_banks_t *b)
static int mce_no_way_out(struct mce *m, char **msg, unsigned long *validp, struct pt_regs *regs)
static int mce_timed_out(u64 *t, const char *msg)
static void mce_reign(void)
static int mce_start(int *no_way_out)
static int mce_end(int order)
static void mce_clear_state(unsigned long *toclear)
static int do_memory_failure(struct mce *m)
static bool __mc_check_crashing_cpu(int cpu)
static void __mc_scan_banks(struct mce *m, struct mce *final, unsigned long *toclear, unsigned long *valid_banks, int no_way_out, int *worst)
void do_machine_check(struct pt_regs *regs, long error_code)
int memory_failure(unsigned long pfn, int flags)
static unsigned long mce_adjust_timer_default(unsigned long interval)
static void __start_timer(struct timer_list *t, unsigned long interval)
static void mce_timer_fn(struct timer_list *t)
void mce_timer_kick(unsigned long interval)
static void mce_timer_delete_all(void)
int mce_notify_irq(void)
static int __mcheck_cpu_mce_banks_init(void)
static int __mcheck_cpu_cap_init(void)
static void __mcheck_cpu_init_generic(void)
static void __mcheck_cpu_init_clear_banks(void)
static void quirk_sandybridge_ifu(int bank, struct mce *m, struct pt_regs *regs)
static int __mcheck_cpu_apply_quirks(struct cpuinfo_x86 *c)
static int __mcheck_cpu_ancient_init(struct cpuinfo_x86 *c)
static void __mcheck_cpu_init_early(struct cpuinfo_x86 *c)
static void mce_centaur_feature_init(struct cpuinfo_x86 *c)
static void __mcheck_cpu_init_vendor(struct cpuinfo_x86 *c)
static void __mcheck_cpu_clear_vendor(struct cpuinfo_x86 *c)
static void mce_start_timer(struct timer_list *t)
static void __mcheck_cpu_setup_timer(void)
static void __mcheck_cpu_init_timer(void)
static void unexpected_machine_check(struct pt_regs *regs, long error_code)
dotraplinkage void do_mce(struct pt_regs *regs, long error_code)
void mcheck_cpu_init(struct cpuinfo_x86 *c)
void mcheck_cpu_clear(struct cpuinfo_x86 *c)
static void __mce_disable_bank(void *arg)
void mce_disable_bank(int bank)
static int __init mcheck_enable(char *str)
int __init mcheck_init(void)
static void mce_disable_error_reporting(void)
static void vendor_disable_error_reporting(void)
static int mce_syscore_suspend(void)
static void mce_syscore_shutdown(void)
static void mce_syscore_resume(void)
static void mce_cpu_restart(void *data)
static void mce_restart(void)
static void mce_disable_cmci(void *data)
static void mce_enable_ce(void *all)
static inline struct mce_bank *attr_to_bank(struct device_attribute *attr)
static ssize_t show_bank(struct device *s, struct device_attribute *attr, char *buf)
static ssize_t set_bank(struct device *s, struct device_attribute *attr, const char *buf, size_t size)
static ssize_t set_ignore_ce(struct device *s, struct device_attribute *attr, const char *buf, size_t size)
static ssize_t set_cmci_disabled(struct device *s, struct device_attribute *attr, const char *buf, size_t size)
static ssize_t store_int_with_restart(struct device *s, struct device_attribute *attr, const char *buf, size_t size)
static void mce_device_release(struct device *dev)
static int mce_device_create(unsigned int cpu)
static void mce_device_remove(unsigned int cpu)
static void mce_disable_cpu(void)
static void mce_reenable_cpu(void)
static int mce_cpu_dead(unsigned int cpu)
static int mce_cpu_online(unsigned int cpu)
static int mce_cpu_pre_down(unsigned int cpu)
static __init void mce_init_banks(void)
static __init int mcheck_init_device(void)
static int __init mcheck_disable(char *str)
struct dentry *mce_get_debugfs_dir(void)
static void mce_reset(void)
static int fake_panic_get(void *data, u64 *val)
static int fake_panic_set(void *data, u64 val)
static int __init mcheck_debugfs_init(void)
static int __init mcheck_late_init(void)
  26 void
  15 struct mce *m
  10 int bank
   9 struct cpuinfo_x86 *c
   7 void *data
   7 struct pt_regs *regs
   6 struct device_attribute *attr
   5 unsigned int cpu
   5 struct notifier_block *nb
   5 struct device *s
   4 size_t size
   4 const char *buf
   3 unsigned long val
   3 unsigned long interval
   3 u32 msr
   3 struct timer_list *t
   3 long error_code
   2 unsigned long *toclear
   2 struct mce *final
   2 const char *msg
   2 char *str
   1 void *arg
   1 void *all
   1 unsigned long pfn
   1 unsigned long *validp
   1 unsigned long *valid_banks
   1 u64 val
   1 u64 v
   1 u64 *val
   1 u64 *t
   1 struct irq_work *entry
   1 struct device *dev
   1 mcsafe_key
   1 mce_unregister_decode_chain
   1 mce_register_decode_chain
   1 mce_notify_irq
   1 mce_is_memory_error
   1 mce_inject_log
   1 mce_banks_t *b
   1 machine_check_poll
   1 int order
   1 int no_way_out
   1 int i
   1 int flags
   1 int cpu
   1 int *worst
   1 int *no_way_out
   1 enum mcp_flags flags
   1 do_machine_check
   1 char *exp
   1 char *buf
   1 char **msg
