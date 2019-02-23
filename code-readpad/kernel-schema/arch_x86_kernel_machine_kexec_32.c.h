
\n
static void set_gdt(void *newgdt, __u16 limit)
static void load_segments(void)
static void machine_kexec_free_page_tables(struct kimage *image)
static int machine_kexec_alloc_page_tables(struct kimage *image)
static void machine_kexec_page_table_set_one(pgd_t *pgd, pmd_t *pmd, pte_t *pte, unsigned long vaddr, unsigned long paddr)
static void machine_kexec_prepare_page_tables(struct kimage *image)
int machine_kexec_prepare(struct kimage *image)
void machine_kexec_cleanup(struct kimage *image)
void machine_kexec(struct kimage *image)
void arch_crash_save_vmcoreinfo(void)
\n
      6 struct kimage *image
      2 void
      1 void *newgdt
      1 unsigned long vaddr
      1 unsigned long paddr
      1 __u16 limit
      1 pte_t *pte
      1 pmd_t *pmd
      1 pgd_t *pgd
