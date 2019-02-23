
EXPORT_SYMBOL_GPL(x86_spec_ctrl_base);
EXPORT_SYMBOL_GPL(x86_virt_spec_ctrl);
EXPORT_SYMBOL_GPL(l1tf_mitigation);
EXPORT_SYMBOL_GPL(l1tf_vmx_mitigation);
\n
void __init check_bugs(void)
void x86_virt_spec_ctrl(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl, bool setguest)
static void x86_amd_ssb_disable(void)
bool retpoline_module_ok(bool has_retpoline)
static inline const char *spectre_v2_module_string(void)
static inline bool match_option(const char *arg, int arglen, const char *opt)
static void __init spec_v2_user_print_cond(const char *reason, bool secure)
static enum spectre_v2_user_cmd __init spectre_v2_parse_user_cmdline(enum spectre_v2_mitigation_cmd v2_cmd)
static void __init spectre_v2_user_select_mitigation(enum spectre_v2_mitigation_cmd v2_cmd)
static void __init spec_v2_print_cond(const char *reason, bool secure)
static enum spectre_v2_mitigation_cmd __init spectre_v2_parse_cmdline(void)
static void __init spectre_v2_select_mitigation(void)
static void update_stibp_msr(void * __unused)
static void update_stibp_strict(void)
static void update_indir_branch_cond(void)
void arch_smt_update(void)
static enum ssb_mitigation_cmd __init ssb_parse_cmdline(void)
static enum ssb_mitigation __init __ssb_select_mitigation(void)
static void ssb_select_mitigation(void)
static void task_update_spec_tif(struct task_struct *tsk)
static int ssb_prctl_set(struct task_struct *task, unsigned long ctrl)
static int ib_prctl_set(struct task_struct *task, unsigned long ctrl)
int arch_prctl_spec_ctrl_set(struct task_struct *task, unsigned long which, unsigned long ctrl)
void arch_seccomp_spec_mitigate(struct task_struct *task)
static int ssb_prctl_get(struct task_struct *task)
static int ib_prctl_get(struct task_struct *task)
int arch_prctl_spec_ctrl_get(struct task_struct *task, unsigned long which)
void x86_spec_ctrl_setup_ap(void)
static void override_cache_bits(struct cpuinfo_x86 *c)
static void __init l1tf_select_mitigation(void)
static int __init l1tf_cmdline(char *str)
static ssize_t l1tf_show_state(char *buf)
return sprintf(buf, "%s; VMX: %s, SMT %s\n", L1TF_DEFAULT_MSG, l1tf_vmx_states[l1tf_vmx_mitigation], sched_smt_active()
? "vulnerable" : "disabled")
; } static ssize_t l1tf_show_state(char *buf)
static char *stibp_state(void)
static char *ibpb_state(void)
static ssize_t cpu_show_common(struct device *dev, struct device_attribute *attr, char *buf, unsigned int bug)
ssize_t cpu_show_meltdown(struct device *dev, struct device_attribute *attr, char *buf)
ssize_t cpu_show_spectre_v1(struct device *dev, struct device_attribute *attr, char *buf)
ssize_t cpu_show_spectre_v2(struct device *dev, struct device_attribute *attr, char *buf)
ssize_t cpu_show_spec_store_bypass(struct device *dev, struct device_attribute *attr, char *buf)
ssize_t cpu_show_l1tf(struct device *dev, struct device_attribute *attr, char *buf)
\n
     15 void
      8 char *buf
      7 struct task_struct *task
      6 struct device *dev
      6 struct device_attribute *attr
      3 unsigned long ctrl
      2 unsigned long which
      2 enum spectre_v2_mitigation_cmd v2_cmd
      2 const char *reason
      2 bool secure
      1 x86_virt_spec_ctrl
      1 x86_spec_ctrl_base
      1 void * __unused
      1 unsigned int bug
      1 u64 guest_virt_spec_ctrl
      1 u64 guest_spec_ctrl
      1 "%s; VMX: %s
      1 struct task_struct *tsk
      1 struct cpuinfo_x86 *c
      1 SMT %s\n"
      1 sched_smt_active
      1 l1tf_vmx_states[l1tf_vmx_mitigation]
      1 l1tf_vmx_mitigation
      1 l1tf_mitigation
      1 L1TF_DEFAULT_MSG
      1 int arglen
      1 const char *opt
      1 const char *arg
      1 char *str
      1 buf
      1 bool setguest
      1 bool has_retpoline
