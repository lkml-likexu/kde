
\n
static void xen_pmu_arch_init(void)
static inline uint32_t get_fam15h_addr(u32 addr)
static inline bool is_amd_pmu_msr(unsigned int msr)
static int is_intel_pmu_msr(u32 msr_index, int *type, int *index)
static bool xen_intel_pmu_emulate(unsigned int msr, u64 *val, int type, int index, bool is_read)
static bool xen_amd_pmu_emulate(unsigned int msr, u64 *val, bool is_read)
bool pmu_msr_read(unsigned int msr, uint64_t *val, int *err)
bool pmu_msr_write(unsigned int msr, uint32_t low, uint32_t high, int *err)
static unsigned long long xen_amd_read_pmc(int counter)
static unsigned long long xen_intel_read_pmc(int counter)
unsigned long long xen_read_pmc(int counter)
int pmu_apic_update(uint32_t val)
static int xen_is_in_guest(void)
static int xen_is_user_mode(void)
static unsigned long xen_get_guest_ip(void)
static void xen_convert_regs(const struct xen_pmu_regs *xen_regs, struct pt_regs *regs, uint64_t pmu_flags)
irqreturn_t xen_pmu_irq_handler(int irq, void *dev_id)
bool is_xen_pmu(int cpu)
void xen_pmu_init(int cpu)
void xen_pmu_finish(int cpu)
\n
      5 unsigned int msr
      4 void
      3 int cpu
      3 int counter
      2 u64 *val
      2 int *err
      2 bool is_read
      1 void *dev_id
      1 uint64_t *val
      1 uint64_t pmu_flags
      1 uint32_t val
      1 uint32_t low
      1 uint32_t high
      1 u32 msr_index
      1 u32 addr
      1 struct pt_regs *regs
      1 int *type
      1 int type
      1 int irq
      1 int *index
      1 int index
      1 const struct xen_pmu_regs *xen_regs
