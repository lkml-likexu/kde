
EXPORT_SYMBOL_GPL(xen_hvm_need_lapic);
\n
void xen_hvm_init_shared_info(void)
static void __init reserve_shared_info(void)
static void __init xen_hvm_init_mem_mapping(void)
static void __init init_hvm_pv_info(void)
static void xen_hvm_shutdown(void)
static void xen_hvm_crash_shutdown(struct pt_regs *regs)
static int xen_cpu_up_prepare_hvm(unsigned int cpu)
static int xen_cpu_dead_hvm(unsigned int cpu)
static void __init xen_hvm_guest_init(void)
static bool xen_nopv; static __init int xen_parse_nopv(char *arg)
bool xen_hvm_need_lapic(void)
static uint32_t __init xen_platform_hvm(void)
static __init void xen_hvm_guest_late_init(void)
\n
      9 void
      2 unsigned int cpu
      1 xen_hvm_need_lapic
      1 struct pt_regs *regs
      1 char *arg
