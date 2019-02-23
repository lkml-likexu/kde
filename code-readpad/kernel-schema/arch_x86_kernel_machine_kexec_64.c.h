
\n
static void free_transition_pgtable(struct kimage *image)
static int init_transition_pgtable(struct kimage *image, pgd_t *pgd)
static void *alloc_pgt_page(void *data)
static int init_pgtable(struct kimage *image, unsigned long start_pgtable)
static void set_idt(void *newidt, u16 limit)
static void set_gdt(void *newgdt, u16 limit)
static void load_segments(void)
static int arch_update_purgatory(struct kimage *image)
return ret; } static inline int arch_update_purgatory(struct kimage *image)
int machine_kexec_prepare(struct kimage *image)
void machine_kexec_cleanup(struct kimage *image)
void machine_kexec(struct kimage *image)
void arch_crash_save_vmcoreinfo(void)
void *arch_kexec_kernel_image_load(struct kimage *image)
int arch_kexec_apply_relocations_add(struct purgatory_info *pi, Elf_Shdr *section, const Elf_Shdr *relsec, const Elf_Shdr *symtabsec)
static int kexec_mark_range(unsigned long start, unsigned long end, bool protect)
static void kexec_mark_crashkres(bool protect)
void arch_kexec_protect_crashkres(void)
void arch_kexec_unprotect_crashkres(void)
int arch_kexec_post_alloc_pages(void *vaddr, unsigned int pages, gfp_t gfp)
void arch_kexec_pre_free_pages(void *vaddr, unsigned int pages)
\n
      9 struct kimage *image
      4 void
      2 void *vaddr
      2 unsigned int pages
      2 u16 limit
      2 bool protect
      1 void *newidt
      1 void *newgdt
      1 void *data
      1 unsigned long start_pgtable
      1 unsigned long start
      1 unsigned long end
      1 struct purgatory_info *pi
      1 pgd_t *pgd
      1 gfp_t gfp
      1 Elf_Shdr *section
      1 const Elf_Shdr *symtabsec
      1 const Elf_Shdr *relsec
