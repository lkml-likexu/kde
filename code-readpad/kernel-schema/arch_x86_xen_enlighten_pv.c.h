
\n
static void __init xen_banner(void)
static void __init xen_pv_init_platform(void)
static void __init xen_pv_guest_late_init(void)
bool xen_running_on_version_or_later(unsigned int major, unsigned int minor)
static void xen_cpuid(unsigned int *ax, unsigned int *bx, unsigned int *cx, unsigned int *dx)
static bool __init xen_check_mwait(void)
static bool __init xen_check_xsave(void)
static void __init xen_init_capabilities(void)
static void xen_set_debugreg(int reg, unsigned long val)
static unsigned long xen_get_debugreg(int reg)
static void xen_end_context_switch(struct task_struct *next)
static unsigned long xen_store_tr(void)
static void set_aliased_prot(void *v, pgprot_t prot)
static void xen_alloc_ldt(struct desc_struct *ldt, unsigned entries)
static void xen_free_ldt(struct desc_struct *ldt, unsigned entries)
static void xen_set_ldt(const void *addr, unsigned entries)
static void xen_load_gdt(const struct desc_ptr *dtr)
static void __init xen_load_gdt_boot(const struct desc_ptr *dtr)
static inline bool desc_equal(const struct desc_struct *d1, const struct desc_struct *d2)
static void load_TLS_descriptor(struct thread_struct *t, unsigned int cpu, unsigned int i)
static void xen_load_tls(struct thread_struct *t, unsigned int cpu)
static void xen_load_gs_index(unsigned int idx)
static void xen_write_ldt_entry(struct desc_struct *dt, int entrynum, const void *ptr)
static bool __ref get_trap_addr(void **addr, unsigned int ist)
static int cvt_gate_to_trap(int vector, const gate_desc *val, struct trap_info *info)
static void xen_write_idt_entry(gate_desc *dt, int entrynum, const gate_desc *g)
static void xen_convert_trap_info(const struct desc_ptr *desc, struct trap_info *traps)
void xen_copy_trap_info(struct trap_info *traps)
static void xen_load_idt(const struct desc_ptr *desc)
static void xen_write_gdt_entry(struct desc_struct *dt, int entry, const void *desc, int type)
static void __init xen_write_gdt_entry_boot(struct desc_struct *dt, int entry, const void *desc, int type)
static void xen_load_sp0(unsigned long sp0)
void xen_set_iopl_mask(unsigned mask)
static void xen_io_delay(void)
static unsigned long xen_read_cr0(void)
static void xen_write_cr0(unsigned long cr0)
static void xen_write_cr4(unsigned long cr4)
native_write_cr4(cr4)
; } static inline unsigned long xen_read_cr8(void)
native_write_cr4(cr4)
; } static inline unsigned long xen_read_cr8(void)
return 0; } static inline void xen_write_cr8(unsigned long val)
static u64 xen_read_msr_safe(unsigned int msr, int *err)
static int xen_write_msr_safe(unsigned int msr, unsigned low, unsigned high)
static u64 xen_read_msr(unsigned int msr)
static void xen_write_msr(unsigned int msr, unsigned low, unsigned high)
void __init xen_setup_vcpu_info_placement(void)
static void xen_restart(char *msg)
static void xen_machine_halt(void)
static void xen_machine_power_off(void)
static void xen_crash_shutdown(struct pt_regs *regs)
static unsigned char xen_get_nmi_reason(void)
static void __init xen_boot_params_init_edd(void)
static void __init xen_setup_gdt(int cpu)
static void __init xen_dom0_set_legacy_features(void)
asmlinkage __visible void __init xen_start_kernel(void)
static int xen_cpu_up_prepare_pv(unsigned int cpu)
static int xen_cpu_dead_pv(unsigned int cpu)
static uint32_t __init xen_platform_pv(void)
\n
     19 void
      4 unsigned int msr
      4 unsigned int cpu
      3 unsigned entries
      3 struct desc_struct *dt
      2 unsigned low
      2 unsigned long val
      2 unsigned high
      2 struct trap_info *traps
      2 struct thread_struct *t
      2 struct desc_struct *ldt
      2 int type
      2 int reg
      2 int entrynum
      2 int entry
      2 cr4
      2 const void *desc
      2 const struct desc_ptr *dtr
      2 const struct desc_ptr *desc
      1 void *v
      1 void **addr
      1 unsigned mask
      1 unsigned long sp0
      1 unsigned long cr4
      1 unsigned long cr0
      1 unsigned int minor
      1 unsigned int major
      1 unsigned int ist
      1 unsigned int idx
      1 unsigned int i
      1 unsigned int *dx
      1 unsigned int *cx
      1 unsigned int *bx
      1 unsigned int *ax
      1 struct trap_info *info
      1 struct task_struct *next
      1 struct pt_regs *regs
      1 pgprot_t prot
      1 int vector
      1 int *err
      1 int cpu
      1 gate_desc *dt
      1 const void *ptr
      1 const void *addr
      1 const struct desc_struct *d2
      1 const struct desc_struct *d1
      1 const gate_desc *val
      1 const gate_desc *g
      1 char *msg
