
static bool __init pcpu_need_numa(void)
static void * __init pcpu_alloc_bootmem(unsigned int cpu, unsigned long size, unsigned long align)
static void * __init pcpu_fc_alloc(unsigned int cpu, size_t size, size_t align)
static void __init pcpu_fc_free(void *ptr, size_t size)
static int __init pcpu_cpu_distance(unsigned int from, unsigned int to)
static void __init pcpup_populate_pte(unsigned long addr)
static inline void setup_percpu_segment(int cpu)
void __init setup_per_cpu_areas(void)
   2 void
   2 unsigned int cpu
   2 size_t size
   1 void *ptr
   1 unsigned long size
   1 unsigned long align
   1 unsigned long addr
   1 unsigned int to
   1 unsigned int from
   1 size_t align
   1 int cpu
