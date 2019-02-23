
\n
static inline void clear_feature(struct cpuinfo_x86 *c, unsigned int feature)
static void do_clear_cpu_cap(struct cpuinfo_x86 *c, unsigned int feature)
void clear_cpu_cap(struct cpuinfo_x86 *c, unsigned int feature)
void setup_clear_cpu_cap(unsigned int feature)
\n
      4 unsigned int feature
      3 struct cpuinfo_x86 *c
