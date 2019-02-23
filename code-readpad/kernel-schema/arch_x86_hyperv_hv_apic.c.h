
\n
static u64 hv_apic_icr_read(void)
static void hv_apic_icr_write(u32 low, u32 id)
static u32 hv_apic_read(u32 reg)
static void hv_apic_write(u32 reg, u32 val)
static void hv_apic_eoi_write(u32 reg, u32 val)
static bool __send_ipi_mask_ex(const struct cpumask *mask, int vector)
static bool __send_ipi_mask(const struct cpumask *mask, int vector)
static bool __send_ipi_one(int cpu, int vector)
static void hv_send_ipi(int cpu, int vector)
static void hv_send_ipi_mask(const struct cpumask *mask, int vector)
static void hv_send_ipi_mask_allbutself(const struct cpumask *mask, int vector)
static void hv_send_ipi_allbutself(int vector)
static void hv_send_ipi_all(int vector)
static void hv_send_ipi_self(int vector)
void __init hv_apic_init(void)
\n
      9 int vector
      4 const struct cpumask *mask
      3 u32 reg
      2 void
      2 u32 val
      2 int cpu
      1 u32 low
      1 u32 id
