
\n
u64 op_x86_get_ctrl(struct op_x86_model_spec const *model, struct op_counter_config *counter_config)
static int profile_exceptions_notify(unsigned int val, struct pt_regs *regs)
static void nmi_cpu_save_registers(struct op_msrs *msrs)
static void nmi_cpu_start(void *dummy)
static int nmi_start(void)
static void nmi_cpu_stop(void *dummy)
static void nmi_stop(void)
static inline int has_mux(void)
inline int op_x86_phys_to_virt(int phys)
inline int op_x86_virt_to_phys(int virt)
static void nmi_shutdown_mux(void)
static int nmi_setup_mux(void)
static void nmi_cpu_setup_mux(int cpu, struct op_msrs const * const msrs)
static void nmi_cpu_save_mpx_registers(struct op_msrs *msrs)
static void nmi_cpu_restore_mpx_registers(struct op_msrs *msrs)
static void nmi_cpu_switch(void *dummy)
static int nmi_multiplex_on(void)
static int nmi_switch_event(void)
static inline void mux_init(struct oprofile_operations *ops)
static void mux_clone(int cpu)
static void free_msrs(void)
static int allocate_msrs(void)
static void nmi_cpu_setup(void)
static void nmi_cpu_restore_registers(struct op_msrs *msrs)
static void nmi_cpu_shutdown(void)
static int nmi_cpu_online(unsigned int cpu)
static int nmi_cpu_down_prep(unsigned int cpu)
static int nmi_create_files(struct dentry *root)
static int nmi_setup(void)
static void nmi_shutdown(void)
static int nmi_suspend(void)
static void nmi_resume(void)
static void __init init_suspend_resume(void)
static void exit_suspend_resume(void)
static int __init p4_init(char **cpu_type)
static int set_cpu_type(const char *str, const struct kernel_param *kp)
static int __init ppro_init(char **cpu_type)
int __init op_nmi_init(struct oprofile_operations *ops)
void op_nmi_exit(void)
\n
     18 void
      4 struct op_msrs *msrs
      3 void *dummy
      2 unsigned int cpu
      2 struct oprofile_operations *ops
      2 int cpu
      2 char **cpu_type
      1 unsigned int val
      1 struct pt_regs *regs
      1 struct op_x86_model_spec const *model
      1 struct op_msrs const * const msrs
      1 struct op_counter_config *counter_config
      1 struct dentry *root
      1 int virt
      1 int phys
      1 const struct kernel_param *kp
      1 const char *str
