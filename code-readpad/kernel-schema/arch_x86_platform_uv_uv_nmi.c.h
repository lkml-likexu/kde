
\n
static int param_get_local64(char *buffer, const struct kernel_param *kp)
static int param_set_local64(const char *val, const struct kernel_param *kp)
static int param_get_action(char *buffer, const struct kernel_param *kp)
static int param_set_action(const char *val, const struct kernel_param *kp)
static inline bool uv_nmi_action_is(const char *action)
static void uv_nmi_setup_mmrs(void)
static inline int uv_nmi_test_mmr(struct uv_hub_nmi_s *hub_nmi)
static inline void uv_local_mmr_clear_nmi(void)
static inline void uv_reassert_nmi(void)
static void uv_init_hubless_pch_io(int offset, int mask, int data)
static void uv_nmi_setup_hubless_intr(void)
static void uv_init_hubless_pch_d0(void)
static int uv_nmi_test_hubless(struct uv_hub_nmi_s *hub_nmi)
static int uv_test_nmi(struct uv_hub_nmi_s *hub_nmi)
static int uv_set_in_nmi(int cpu, struct uv_hub_nmi_s *hub_nmi)
static int uv_check_nmi(struct uv_hub_nmi_s *hub_nmi)
static inline void uv_clear_nmi(int cpu)
static void uv_nmi_nr_cpus_ping(void)
static void uv_nmi_cleanup_mask(void)
static int uv_nmi_wait_cpus(int first)
static void uv_nmi_wait(int master)
static void uv_nmi_dump_cpu_ip_hdr(void)
static void uv_nmi_dump_cpu_ip(int cpu, struct pt_regs *regs)
static void uv_nmi_dump_state_cpu(int cpu, struct pt_regs *regs)
static void uv_nmi_trigger_dump(int cpu)
static void uv_nmi_sync_exit(int master)
static void uv_nmi_action_health(int cpu, struct pt_regs *regs, int master)
static void uv_nmi_dump_state(int cpu, struct pt_regs *regs, int master)
static void uv_nmi_touch_watchdogs(void)
static void uv_nmi_kdump(int cpu, int master, struct pt_regs *regs)
static inline void uv_nmi_kdump(int cpu, int master, struct pt_regs *regs)
static inline int uv_nmi_kdb_reason(void)
static inline int uv_nmi_kdb_reason(void)
return KDB_REASON_SYSTEM_NMI; } static inline int uv_nmi_kdb_reason(void)
static void uv_call_kgdb_kdb(int cpu, struct pt_regs *regs, int master)
static inline void uv_call_kgdb_kdb(int cpu, struct pt_regs *regs, int master)
static int uv_handle_nmi(unsigned int reason, struct pt_regs *regs)
static int uv_handle_nmi_ping(unsigned int reason, struct pt_regs *regs)
static void uv_register_nmi_notifier(void)
void uv_nmi_init(void)
static void __init uv_nmi_setup_common(bool hubbed)
void __init uv_nmi_setup(void)
void __init uv_nmi_setup_hubless(void)
\n
     16 void
     11 int cpu
     10 struct pt_regs *regs
      8 int master
      5 struct uv_hub_nmi_s *hub_nmi
      4 const struct kernel_param *kp
      2 unsigned int reason
      2 const char *val
      2 char *buffer
      1 int offset
      1 int mask
      1 int first
      1 int data
      1 const char *action
      1 bool hubbed
