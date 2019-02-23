
\n
static inline uint64_t get_desc64_base(const struct desc64 *desc)
static inline uint64_t rdtsc(void)
static inline uint64_t rdtscp(uint32_t *aux)
static inline uint64_t rdmsr(uint32_t msr)
static inline void wrmsr(uint32_t msr, uint64_t value)
static inline uint16_t inw(uint16_t port)
static inline uint16_t get_es(void)
static inline uint16_t get_cs(void)
static inline uint16_t get_ss(void)
static inline uint16_t get_ds(void)
static inline uint16_t get_fs(void)
static inline uint16_t get_gs(void)
static inline uint16_t get_tr(void)
static inline uint64_t get_cr0(void)
static inline uint64_t get_cr3(void)
static inline uint64_t get_cr4(void)
static inline void set_cr4(uint64_t val)
static inline uint64_t get_gdt_base(void)
static inline uint64_t get_idt_base(void)
static inline void set_xmm(int n, unsigned long val)
typedef unsigned long v1di __attribute__ ((vector_size (8)
)
)
; static inline unsigned long get_xmm(int n)
static inline struct kvm_cpuid_entry2 * kvm_get_supported_cpuid_entry(uint32_t function)
\n
     13 void
      2 uint32_t msr
      2 int n
      1 vector_size 8
      1 unsigned long val
      1 uint64_t value
      1 uint64_t val
      1 uint32_t function
      1 uint32_t *aux
      1 uint16_t port
      1 const struct desc64 *desc
