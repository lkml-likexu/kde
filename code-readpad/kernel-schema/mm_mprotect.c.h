
\n
static unsigned long change_pte_range(struct vm_area_struct *vma, pmd_t *pmd, unsigned long addr, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
static inline unsigned long change_pmd_range(struct vm_area_struct *vma, pud_t *pud, unsigned long addr, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
static inline unsigned long change_pud_range(struct vm_area_struct *vma, p4d_t *p4d, unsigned long addr, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
static inline unsigned long change_p4d_range(struct vm_area_struct *vma, pgd_t *pgd, unsigned long addr, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
static unsigned long change_protection_range(struct vm_area_struct *vma, unsigned long addr, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
unsigned long change_protection(struct vm_area_struct *vma, unsigned long start, unsigned long end, pgprot_t newprot, int dirty_accountable, int prot_numa)
static int prot_none_pte_entry(pte_t *pte, unsigned long addr, unsigned long next, struct mm_walk *walk)
static int prot_none_hugetlb_entry(pte_t *pte, unsigned long hmask, unsigned long addr, unsigned long next, struct mm_walk *walk)
static int prot_none_test(unsigned long addr, unsigned long next, struct mm_walk *walk)
static int prot_none_walk(struct vm_area_struct *vma, unsigned long start, unsigned long end, unsigned long newflags)
int mprotect_fixup(struct vm_area_struct *vma, struct vm_area_struct **pprev, unsigned long start, unsigned long end, unsigned long newflags)
static int do_mprotect_pkey(unsigned long start, size_t len, unsigned long prot, int pkey)
SYSCALL_DEFINE3(mprotect, unsigned long, start, size_t, len, unsigned long, prot)
SYSCALL_DEFINE4(pkey_mprotect, unsigned long, start, size_t, len, unsigned long, prot, int, pkey)
SYSCALL_DEFINE2(pkey_alloc, unsigned long, flags, unsigned long, init_val)
SYSCALL_DEFINE1(pkey_free, int, pkey)
\n
      8 unsigned long end
      8 unsigned long addr
      8 struct vm_area_struct *vma
      6 unsigned long
      6 pgprot_t newprot
      6 int prot_numa
      6 int dirty_accountable
      4 unsigned long start
      3 unsigned long next
      3 struct mm_walk *walk
      2 unsigned long newflags
      2 start
      2 size_t
      2 pte_t *pte
      2 prot
      2 pkey
      2 len
      2 int
      1 unsigned long prot
      1 unsigned long hmask
      1 struct vm_area_struct **pprev
      1 size_t len
      1 pud_t *pud
      1 pmd_t *pmd
      1 pkey_mprotect
      1 pkey_free
      1 pkey_alloc
      1 pgd_t *pgd
      1 p4d_t *p4d
      1 mprotect
      1 int pkey
      1 init_val
      1 flags
