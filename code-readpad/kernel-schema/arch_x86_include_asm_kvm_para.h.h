
\n
bool kvm_check_and_clear_guest_paused(void)
; static inline bool kvm_check_and_clear_guest_paused(void)
static inline long kvm_hypercall0(unsigned int nr)
static inline long kvm_hypercall1(unsigned int nr, unsigned long p1)
static inline long kvm_hypercall2(unsigned int nr, unsigned long p1, unsigned long p2)
static inline long kvm_hypercall3(unsigned int nr, unsigned long p1, unsigned long p2, unsigned long p3)
static inline long kvm_hypercall4(unsigned int nr, unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4)
void __init kvm_spinlock_init(void)
; static inline void kvm_spinlock_init(void)
static inline bool kvm_para_available(void)
static inline unsigned int kvm_arch_para_features(void)
static inline unsigned int kvm_arch_para_hints(void)
static inline u32 kvm_read_and_reset_pf_reason(void)
static inline void kvm_disable_steal_time(void)
\n
      9 void
      5 unsigned int nr
      4 unsigned long p1
      3 unsigned long p2
      2 unsigned long p3
      1 unsigned long p4
