
EXPORT_SYMBOL_GPL(pm_power_off);
\n
static int __init condev_setup(char *str)
static void __init set_preferred_console(void)
static int __init conmode_setup(char *str)
static void __init conmode_default(void)
static void __init setup_zfcpdump(void)
void machine_restart(char *command)
void machine_halt(void)
void machine_power_off(void)
static int __init parse_vmalloc(char *arg)
unsigned long stack_alloc(void)
void stack_free(unsigned long stack)
int __init arch_early_irq_init(void)
static int __init async_stack_realloc(void)
void __init arch_call_rest_init(void)
static void __init setup_lowcore(void)
static void __init setup_resources(void)
static void __init setup_memory_end(void)
static int kdump_mem_notifier(struct notifier_block *nb, unsigned long action, void *data)
static void reserve_memory_end(void)
static void reserve_oldmem(void)
static void remove_oldmem(void)
static void __init reserve_crashkernel(void)
static void __init reserve_initrd(void)
static void __init reserve_mem_detect_info(void)
static void __init free_mem_detect_info(void)
static void __init memblock_physmem_add(phys_addr_t start, phys_addr_t size)
static const char * __init get_mem_info_source(void)
static void __init memblock_add_mem_detect_info(void)
static void __init check_initrd(void)
static void __init reserve_kernel(void)
static void __init setup_memory(void)
static int __init setup_hwcaps(void)
static void __init setup_randomness(void)
static void __init setup_task_size(void)
void __init setup_arch(char **cmdline_p)
\n
     27 void
      2 char *str
      1 void *data
      1 unsigned long stack
      1 unsigned long action
      1 struct notifier_block *nb
      1 pm_power_off
      1 phys_addr_t start
      1 phys_addr_t size
      1 char *command
      1 char **cmdline_p
      1 char *arg
