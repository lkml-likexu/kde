
\n
static unsigned int xen_io_apic_read(unsigned apic, unsigned reg)
static u32 xen_set_apic_id(unsigned int x)
static unsigned int xen_get_apic_id(unsigned long x)
static u32 xen_apic_read(u32 reg)
static void xen_apic_write(u32 reg, u32 val)
static u64 xen_apic_icr_read(void)
static void xen_apic_icr_write(u32 low, u32 id)
static u32 xen_safe_apic_wait_icr_idle(void)
static int xen_apic_probe_pv(void)
static int xen_madt_oem_check(char *oem_id, char *oem_table_id)
static int xen_id_always_valid(u32 apicid)
static int xen_id_always_registered(void)
static int xen_phys_pkg_id(int initial_apic_id, int index_msb)
static int xen_x86_32_early_logical_apicid(int cpu)
static void xen_noop(void)
static void xen_silent_inquire(int apicid)
static int xen_cpu_present_to_apicid(int cpu)
static void __init xen_apic_check(void)
pr_info("Switched APIC routing from %s to %s.\n", apic->name, xen_pv_apic.name)
;apic = &xen_pv_apic; } void __init xen_init_apic(void)
\n
      7 void
      2 u32 reg
      2 int cpu
      1 xen_pv_apic.name
      1 unsigned reg
      1 unsigned long x
      1 unsigned int x
      1 unsigned apic
      1 u32 val
      1 u32 low
      1 u32 id
      1 u32 apicid
      1 "Switched APIC routing from %s to %s.\n"
      1 int initial_apic_id
      1 int index_msb
      1 int apicid
      1 char *oem_table_id
      1 char *oem_id
      1 apic->name
