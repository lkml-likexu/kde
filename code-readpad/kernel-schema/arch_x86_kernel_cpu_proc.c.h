
static void show_cpuinfo_core(struct seq_file *m, struct cpuinfo_x86 *c, unsigned int cpu)
static void show_cpuinfo_misc(struct seq_file *m, struct cpuinfo_x86 *c)
static void show_cpuinfo_misc(struct seq_file *m, struct cpuinfo_x86 *c)
seq_printf(m, "fdiv_bug\t: %s\n""f00f_bug\t: %s\n""coma_bug\t: %s\n""fpu\t\t: %s\n""fpu_exception\t: %s\n""cpuid level\t: %d\n""wp\t\t: yes\n", static_cpu_has_bug(X86_BUG_FDIV)
? "yes" : "no", static_cpu_has_bug(X86_BUG_F00F)
? "yes" : "no", static_cpu_has_bug(X86_BUG_COMA)
? "yes" : "no", static_cpu_has(X86_FEATURE_FPU)
? "yes" : "no", static_cpu_has(X86_FEATURE_FPU)
? "yes" : "no", c->cpuid_level)
; } static void show_cpuinfo_misc(struct seq_file *m, struct cpuinfo_x86 *c)
static int show_cpuinfo(struct seq_file *m, void *v)
static void *c_start(struct seq_file *m, loff_t *pos)
static void *c_next(struct seq_file *m, void *v, loff_t *pos)
static void c_stop(struct seq_file *m, void *v)
   8 struct seq_file *m
   4 struct cpuinfo_x86 *c
   3 void *v
   2 loff_t *pos
   2 X86_FEATURE_FPU
   1 unsigned int cpu
   1 static_cpu_has_bugX86_BUG_FDIV
   1 m
   1 X86_BUG_F00F
   1 X86_BUG_COMA
   1 "fdiv_bug\t: %s\n""f00f_bug\t: %s\n""coma_bug\t: %s\n""fpu\t\t: %s\n""fpu_exception\t: %s\n""cpuid level\t: %d\n""wp\t\t: yes\n"
