
EXPORT_SYMBOL_GPL(kvm_async_pf_task_wait);
EXPORT_SYMBOL_GPL(kvm_async_pf_task_wake);
EXPORT_SYMBOL_GPL(kvm_read_and_reset_pf_reason);
EXPORT_SYMBOL_GPL(kvm_para_available);
static int __init parse_no_kvmapf(char *arg)
static int steal_acc = 1; static int __init parse_no_stealacc(char *arg)
static void kvm_io_delay(void)
static struct kvm_task_sleep_node *_find_apf_task(struct kvm_task_sleep_head *b, u32 token)
void kvm_async_pf_task_wait(u32 token, int interrupt_kernel)
static void apf_task_wake_one(struct kvm_task_sleep_node *n)
static void apf_task_wake_all(void)
void kvm_async_pf_task_wake(u32 token)
u32 kvm_read_and_reset_pf_reason(void)
dotraplinkage void do_async_page_fault(struct pt_regs *regs, unsigned long error_code)
static void __init paravirt_ops_setup(void)
static void kvm_register_steal_time(void)
static notrace void kvm_guest_apic_eoi_write(u32 reg, u32 val)
static void kvm_guest_cpu_init(void)
static void kvm_pv_disable_apf(void)
static void kvm_pv_guest_cpu_reboot(void *unused)
static int kvm_pv_reboot_notify(struct notifier_block *nb, unsigned long code, void *unused)
static u64 kvm_steal_clock(int cpu)
void kvm_disable_steal_time(void)
static inline void __set_percpu_decrypted(void *ptr, unsigned long size)
static void __init sev_map_percpu_data(void)
static void __send_ipi_mask(const struct cpumask *mask, int vector)
static void kvm_send_ipi_mask(const struct cpumask *mask, int vector)
static void kvm_send_ipi_mask_allbutself(const struct cpumask *mask, int vector)
static void kvm_send_ipi_allbutself(int vector)
static void kvm_send_ipi_all(int vector)
static void kvm_setup_pv_ipi(void)
static void __init kvm_smp_prepare_cpus(unsigned int max_cpus)
static void __init kvm_smp_prepare_boot_cpu(void)
static void kvm_guest_cpu_offline(void)
static int kvm_cpu_online(unsigned int cpu)
static int kvm_cpu_down_prepare(unsigned int cpu)
static void __init kvm_apf_trap_init(void)
static void kvm_flush_tlb_others(const struct cpumask *cpumask, const struct flush_tlb_info *info)
static void __init kvm_guest_init(void)
static noinline uint32_t __kvm_cpuid_base(void)
static inline uint32_t kvm_cpuid_base(void)
bool kvm_para_available(void)
unsigned int kvm_arch_para_features(void)
unsigned int kvm_arch_para_hints(void)
static uint32_t __init kvm_detect(void)
static void __init kvm_apic_init(void)
static void __init kvm_init_platform(void)
static __init int activate_jump_labels(void)
static __init int kvm_setup_pv_tlb_flush(void)
static void kvm_kick_cpu(int cpu)
static void kvm_wait(u8 *ptr, u8 val)
__visible bool __kvm_vcpu_is_preempted(long cpu)
void __init kvm_spinlock_init(void)
  25 void
   5 int vector
   3 u32 token
   3 const struct cpumask *mask
   2 void *unused
   2 unsigned int cpu
   2 int cpu
   2 char *arg
   1 void *ptr
   1 unsigned long size
   1 unsigned long error_code
   1 unsigned long code
   1 unsigned int max_cpus
   1 u8 val
   1 u8 *ptr
   1 u32 val
   1 u32 reg
   1 struct pt_regs *regs
   1 struct notifier_block *nb
   1 struct kvm_task_sleep_node *n
   1 struct kvm_task_sleep_head *b
   1 long cpu
   1 kvm_read_and_reset_pf_reason
   1 kvm_para_available
   1 kvm_async_pf_task_wake
   1 kvm_async_pf_task_wait
   1 int interrupt_kernel
   1 const struct flush_tlb_info *info
   1 const struct cpumask *cpumask
