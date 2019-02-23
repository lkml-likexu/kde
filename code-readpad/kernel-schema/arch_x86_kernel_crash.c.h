
EXPORT_SYMBOL_GPL(crash_vmclear_loaded_vmcss);
\n
static inline void cpu_crash_vmclear_loaded_vmcss(void)
static void kdump_nmi_callback(int cpu, struct pt_regs *regs)
void kdump_nmi_shootdown_cpus(void)
void crash_smp_send_stop(void)
void crash_smp_send_stop(void)
void native_machine_crash_shutdown(struct pt_regs *regs)
static int get_nr_ram_ranges_callback(struct resource *res, void *arg)
static struct crash_mem *fill_up_crash_elf_data(void)
static int elf_header_exclude_ranges(struct crash_mem *cmem)
static int prepare_elf64_ram_headers_callback(struct resource *res, void *arg)
static int prepare_elf_headers(struct kimage *image, void **addr, unsigned long *sz)
static int add_e820_entry(struct boot_params *params, struct e820_entry *entry)
static int memmap_entry_callback(struct resource *res, void *arg)
static int memmap_exclude_ranges(struct kimage *image, struct crash_mem *cmem, unsigned long long mstart, unsigned long long mend)
int crash_setup_memmap_entries(struct kimage *image, struct boot_params *params)
static int determine_backup_region(struct resource *res, void *arg)
int crash_load_segments(struct kimage *image)
\n
      5 void
      4 void *arg
      4 struct resource *res
      4 struct kimage *image
      2 struct pt_regs *regs
      2 struct crash_mem *cmem
      2 struct boot_params *params
      1 void **addr
      1 unsigned long *sz
      1 unsigned long long mstart
      1 unsigned long long mend
      1 struct e820_entry *entry
      1 int cpu
      1 crash_vmclear_loaded_vmcss
