
\n
static void __init xen_parse_512gb(void)
static void __init xen_add_extra_mem(unsigned long start_pfn, unsigned long n_pfns)
static void __init xen_del_extra_mem(unsigned long start_pfn, unsigned long n_pfns)
unsigned long __ref xen_chk_extra_mem(unsigned long pfn)
void __init xen_inv_extra_mem(void)
static unsigned long __init xen_find_pfn_range(unsigned long *min_pfn)
static int __init xen_free_mfn(unsigned long mfn)
static void __init xen_set_identity_and_release_chunk(unsigned long start_pfn, unsigned long end_pfn, unsigned long nr_pages)
static void __init xen_update_mem_tables(unsigned long pfn, unsigned long mfn)
static void __init xen_do_set_identity_and_remap_chunk( unsigned long start_pfn, unsigned long size, unsigned long remap_pfn)
static unsigned long __init xen_set_identity_and_remap_chunk(unsigned long start_pfn, unsigned long end_pfn, unsigned long nr_pages, unsigned long remap_pfn)
static unsigned long __init xen_count_remap_pages(unsigned long start_pfn, unsigned long end_pfn, unsigned long nr_pages, unsigned long remap_pages)
static unsigned long __init xen_foreach_remap_area(unsigned long nr_pages, unsigned long (*func)
(unsigned long start_pfn, unsigned long end_pfn, unsigned long nr_pages, unsigned long last_val)
)
void __init xen_remap_memory(void)
static unsigned long __init xen_get_pages_limit(void)
static unsigned long __init xen_get_max_pages(void)
static void __init xen_align_and_add_e820_region(phys_addr_t start, phys_addr_t size, int type)
static void __init xen_ignore_unusable(void)
bool __init xen_is_e820_reserved(phys_addr_t start, phys_addr_t size)
phys_addr_t __init xen_find_free_area(phys_addr_t size)
static void __init xen_phys_memcpy(phys_addr_t dest, phys_addr_t src, phys_addr_t n)
static void __init xen_reserve_xen_mfnlist(void)
char * __init xen_memory_setup(void)
static void __init fiddle_vdso(void)
static int register_callback(unsigned type, const void *func)
void xen_enable_sysenter(void)
void xen_enable_syscall(void)
void __init xen_pvmmu_arch_setup(void)
void __init xen_arch_setup(void)
\n
     13 void
      7 unsigned long start_pfn
      5 unsigned long nr_pages
      4 unsigned long end_pfn
      3 phys_addr_t size
      2 unsigned long remap_pfn
      2 unsigned long pfn
      2 unsigned long n_pfns
      2 unsigned long mfn
      2 phys_addr_t start
      1 unsigned type
      1 unsigned long size
      1 unsigned long remap_pages
      1 unsigned long *min_pfn
      1 unsigned long last_val
      1 unsigned long *func
      1 phys_addr_t src
      1 phys_addr_t n
      1 phys_addr_t dest
      1 int type
      1 const void *func
