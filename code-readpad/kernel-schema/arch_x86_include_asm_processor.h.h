
\n
static inline unsigned long long l1tf_pfn_limit(void)
extern int have_cpuid_p(void)
; static inline int have_cpuid_p(void)
extern int have_cpuid_p(void)
; static inline int have_cpuid_p(void)
return 1; }endif static inline void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
define native_cpuid_reg(reg)
\ static inline unsigned int native_cpuid_reg(unsigned int op)
\static inline unsigned long read_cr3_pa(void)
static inline unsigned long native_read_cr3_pa(void)
static inline void load_cr3(pgd_t *pgdir)
static inline unsigned long cpu_kernelmode_gs_base(int cpu)
static inline void arch_thread_struct_whitelist(unsigned long *offset, unsigned long *size)
static inline void native_set_iopl_mask(unsigned mask)
static inline void native_load_sp0(unsigned long sp0)
static inline void native_swapgs(void)
static inline unsigned long current_top_of_stack(void)
static inline bool on_thread_stack(void)
static inline void load_sp0(unsigned long sp0)
static inline void cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
static inline void cpuid_count(unsigned int op, int count, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
static inline unsigned int cpuid_eax(unsigned int op)
static inline unsigned int cpuid_ebx(unsigned int op)
static inline unsigned int cpuid_ecx(unsigned int op)
static inline unsigned int cpuid_edx(unsigned int op)
static __always_inline void rep_nop(void)
static __always_inline void cpu_relax(void)
static inline void sync_core(void)
static inline unsigned long get_debugctlmsr(void)
static inline void update_debugctlmsr(unsigned long debugctlmsr)
static inline void prefetch(const void *x)
static inline void prefetchw(const void *x)
static inline void spin_lock_prefetch(const void *x)
extern int mpx_enable_management(void)
; extern int mpx_disable_management(void)
; static inline int mpx_enable_management(void)
extern int mpx_enable_management(void)
; extern int mpx_disable_management(void)
; static inline int mpx_enable_management(void)
return -EINVAL; } static inline int mpx_disable_management(void)
static inline uint32_t hypervisor_cpuid_base(const char *sig, uint32_t leaves)
\n
     21 void
      7 unsigned int op
      3 unsigned int *edx
      3 unsigned int *ecx
      3 unsigned int *ebx
      3 unsigned int *eax
      3 const void *x
      2 unsigned long sp0
      1 unsigned mask
      1 unsigned long *size
      1 unsigned long *offset
      1 unsigned long debugctlmsr
      1 uint32_t leaves
      1 reg
      1 pgd_t *pgdir
      1 int cpu
      1 int count
      1 const char *sig
