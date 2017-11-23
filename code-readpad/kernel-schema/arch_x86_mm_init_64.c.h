
EXPORT_SYMBOL_GPL(__supported_pte_mask);
static int __init nonx32_setup(char *str)
static void sync_global_pgds_l5(unsigned long start, unsigned long end)
static void sync_global_pgds_l4(unsigned long start, unsigned long end)
void sync_global_pgds(unsigned long start, unsigned long end)
static __ref void *spp_getpage(void)
static p4d_t *fill_p4d(pgd_t *pgd, unsigned long vaddr)
static pud_t *fill_pud(p4d_t *p4d, unsigned long vaddr)
static pmd_t *fill_pmd(pud_t *pud, unsigned long vaddr)
static pte_t *fill_pte(pmd_t *pmd, unsigned long vaddr)
static void __set_pte_vaddr(pud_t *pud, unsigned long vaddr, pte_t new_pte)
void set_pte_vaddr_p4d(p4d_t *p4d_page, unsigned long vaddr, pte_t new_pte)
void set_pte_vaddr_pud(pud_t *pud_page, unsigned long vaddr, pte_t new_pte)
void set_pte_vaddr(unsigned long vaddr, pte_t pteval)
pmd_t * __init populate_extra_pmd(unsigned long vaddr)
pte_t * __init populate_extra_pte(unsigned long vaddr)
static void __init __init_extra_mapping(unsigned long phys, unsigned long size, enum page_cache_mode cache)
void __init init_extra_mapping_wb(unsigned long phys, unsigned long size)
void __init init_extra_mapping_uc(unsigned long phys, unsigned long size)
void __init cleanup_highmap(void)
static unsigned long __meminit phys_pte_init(pte_t *pte_page, unsigned long paddr, unsigned long paddr_end, pgprot_t prot)
static unsigned long __meminit phys_pmd_init(pmd_t *pmd_page, unsigned long paddr, unsigned long paddr_end, unsigned long page_size_mask, pgprot_t prot)
static unsigned long __meminit phys_pud_init(pud_t *pud_page, unsigned long paddr, unsigned long paddr_end, unsigned long page_size_mask)
static unsigned long __meminit phys_p4d_init(p4d_t *p4d_page, unsigned long paddr, unsigned long paddr_end, unsigned long page_size_mask)
unsigned long __meminit kernel_physical_mapping_init(unsigned long paddr_start, unsigned long paddr_end, unsigned long page_size_mask)
void __init initmem_init(void)
void __init paging_init(void)
static void update_end_of_memory_vars(u64 start, u64 size)
int add_pages(int nid, unsigned long start_pfn, unsigned long nr_pages, struct vmem_altmap *altmap, bool want_memblock)
int arch_add_memory(int nid, u64 start, u64 size, struct vmem_altmap *altmap, bool want_memblock)
static void __meminit free_pagetable(struct page *page, int order)
static void __meminit free_hugepage_table(struct page *page, struct vmem_altmap *altmap)
static void __meminit free_pte_table(pte_t *pte_start, pmd_t *pmd)
static void __meminit free_pmd_table(pmd_t *pmd_start, pud_t *pud)
static void __meminit free_pud_table(pud_t *pud_start, p4d_t *p4d)
static void __meminit remove_pte_table(pte_t *pte_start, unsigned long addr, unsigned long end, bool direct)
static void __meminit remove_pmd_table(pmd_t *pmd_start, unsigned long addr, unsigned long end, bool direct, struct vmem_altmap *altmap)
static void __meminit remove_pud_table(pud_t *pud_start, unsigned long addr, unsigned long end, struct vmem_altmap *altmap, bool direct)
static void __meminit remove_p4d_table(p4d_t *p4d_start, unsigned long addr, unsigned long end, struct vmem_altmap *altmap, bool direct)
static void __meminit remove_pagetable(unsigned long start, unsigned long end, bool direct, struct vmem_altmap *altmap)
void __ref vmemmap_free(unsigned long start, unsigned long end, struct vmem_altmap *altmap)
static void __meminit kernel_physical_mapping_remove(unsigned long start, unsigned long end)
int __ref arch_remove_memory(u64 start, u64 size, struct vmem_altmap *altmap)
static void __init register_page_bootmem_info(void)
void __init mem_init(void)
void set_kernel_text_rw(void)
void set_kernel_text_ro(void)
void mark_rodata_ro(void)
int kern_addr_valid(unsigned long addr)
static unsigned long set_memory_block_size; int __init set_memory_block_size_order(unsigned int order)
static unsigned long probe_memory_block_size(void)
static unsigned long memory_block_size_probed; unsigned long memory_block_size_bytes(void)
static int __meminit vmemmap_populate_hugepages(unsigned long start, unsigned long end, int node, struct vmem_altmap *altmap)
int __meminit vmemmap_populate(unsigned long start, unsigned long end, int node, struct vmem_altmap *altmap)
void register_page_bootmem_memmap(unsigned long section_nr, struct page *start_page, unsigned long nr_pages)
void __meminit vmemmap_populate_print_last(void)
  12 void
  12 unsigned long end
  11 struct vmem_altmap *altmap
  10 unsigned long vaddr
   8 unsigned long start
   5 unsigned long paddr_end
   5 unsigned long addr
   5 bool direct
   4 unsigned long page_size_mask
   4 unsigned long paddr
   3 unsigned long size
   3 unsigned long phys
   3 u64 start
   3 u64 size
   3 pud_t *pud
   3 pte_t new_pte
   2 unsigned long nr_pages
   2 struct page *page
   2 pud_t *pud_start
   2 pud_t *pud_page
   2 pte_t *pte_start
   2 pmd_t *pmd_start
   2 pmd_t *pmd
   2 pgprot_t prot
   2 p4d_t *p4d_page
   2 p4d_t *p4d
   2 int node
   2 int nid
   2 bool want_memblock
   1 unsigned long start_pfn
   1 unsigned long section_nr
   1 unsigned long paddr_start
   1 unsigned int order
   1 struct page *start_page
   1 pte_t pteval
   1 pte_t *pte_page
   1 pmd_t *pmd_page
   1 pgd_t *pgd
   1 p4d_t *p4d_start
   1 int order
   1 enum page_cache_mode cache
   1 char *str
   1 __supported_pte_mask
