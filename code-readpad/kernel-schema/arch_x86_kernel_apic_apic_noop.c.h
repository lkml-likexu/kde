
\n
static int noop_wakeup_secondary_cpu(int apicid, unsigned long start_eip)
static u32 noop_safe_apic_wait_icr_idle(void)
static u64 noop_apic_icr_read(void)
static int noop_phys_pkg_id(int cpuid_apic, int index_msb)
static unsigned int noop_get_apic_id(unsigned long x)
static int noop_probe(void)
static int noop_apic_id_registered(void)
static u32 noop_apic_read(u32 reg)
static void noop_apic_write(u32 reg, u32 v)
static int noop_x86_32_early_logical_apicid(int cpu)
\n
      4 void
      2 u32 reg
      1 unsigned long x
      1 unsigned long start_eip
      1 u32 v
      1 int index_msb
      1 int cpuid_apic
      1 int cpu
      1 int apicid
