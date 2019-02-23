
\n
extern void generic_apic_probe(void)
; static inline void generic_apic_probe(void)
extern void __inquire_remote_apic(int apicid)
; static inline void __inquire_remote_apic(int apicid)
static inline void default_inquire_remote_apic(int apicid)
static inline bool apic_from_smp_config(void)
static inline void native_apic_mem_write(u32 reg, u32 v)
static inline u32 native_apic_mem_read(u32 reg)
static inline bool apic_is_x2apic_enabled(void)
static inline int apic_force_enable(unsigned long addr)
extern int apic_is_clustered_box(void)
; static inline int apic_is_clustered_box(void)
static inline void x2apic_wrmsr_fence(void)
static inline void native_apic_msr_write(u32 reg, u32 v)
static inline void native_apic_msr_eoi_write(u32 reg, u32 v)
static inline u32 native_apic_msr_read(u32 reg)
static inline void native_x2apic_wait_icr_idle(void)
static inline u32 native_safe_x2apic_wait_icr_idle(void)
static inline void native_x2apic_icr_write(u32 low, u32 id)
static inline u64 native_x2apic_icr_read(void)
extern int x2apic_mode; extern int x2apic_phys; extern void __init check_x2apic(void)
; extern void x2apic_setup(void)
; static inline int x2apic_enabled(void)
static inline u32 apic_read(u32 reg)
static inline void apic_write(u32 reg, u32 val)
static inline void apic_eoi(void)
static inline u64 apic_icr_read(void)
static inline void apic_icr_write(u32 low, u32 high)
static inline void apic_wait_icr_idle(void)
static inline u32 safe_apic_wait_icr_idle(void)
static inline void ack_APIC_irq(void)
static inline unsigned default_get_apic_id(unsigned long x)
static inline unsigned int read_apic_id(void)
static inline void entering_irq(void)
static inline void entering_ack_irq(void)
static inline void ipi_entering_ack_irq(void)
static inline void exiting_irq(void)
static inline void exiting_ack_irq(void)
\n
     24 void
      7 u32 reg
      3 u32 v
      3 int apicid
      2 u32 low
      1 unsigned long x
      1 unsigned long addr
      1 u32 val
      1 u32 id
      1 u32 high
