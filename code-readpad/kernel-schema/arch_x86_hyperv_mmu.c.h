
\n
static inline int fill_gva_list(u64 gva_list[], int offset, unsigned long start, unsigned long end)
static void hyperv_flush_tlb_others(const struct cpumask *cpus, const struct flush_tlb_info *info)
static u64 hyperv_flush_tlb_others_ex(const struct cpumask *cpus, const struct flush_tlb_info *info)
void hyperv_setup_mmu_ops(void)
\n
      2 const struct flush_tlb_info *info
      2 const struct cpumask *cpus
      1 void
      1 unsigned long start
      1 unsigned long end
      1 u64 gva_list[]
      1 int offset
