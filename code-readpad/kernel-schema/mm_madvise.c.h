
\n
static int madvise_need_mmap_write(int behavior)
static long madvise_behavior(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end, int behavior)
static int swapin_walk_pmd_entry(pmd_t *pmd, unsigned long start, unsigned long end, struct mm_walk *walk)
static void force_swapin_readahead(struct vm_area_struct *vma, unsigned long start, unsigned long end)
static void force_shm_swapin_readahead(struct vm_area_struct *vma, unsigned long start, unsigned long end, struct address_space *mapping)
static long madvise_willneed(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end)
static void madvise_free_page_range(struct mmu_gather *tlb, struct vm_area_struct *vma, unsigned long addr, unsigned long end)
static int madvise_free_single_vma(struct vm_area_struct *vma, unsigned long start_addr, unsigned long end_addr)
static long madvise_dontneed_single_vma(struct vm_area_struct *vma, unsigned long start, unsigned long end)
static long madvise_dontneed_free(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end, int behavior)
static long madvise_remove(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end)
static int madvise_inject_error(int behavior, unsigned long start, unsigned long end)
static long madvise_vma(struct vm_area_struct *vma, struct vm_area_struct **prev, unsigned long start, unsigned long end, int behavior)
static bool madvise_behavior_valid(int behavior)
SYSCALL_DEFINE3(madvise, unsigned long, start, size_t, len_in, int, behavior)
\n
     11 unsigned long end
     10 unsigned long start
     10 struct vm_area_struct *vma
      6 int behavior
      5 struct vm_area_struct **prev
      1 unsigned long start_addr
      1 unsigned long end_addr
      1 unsigned long addr
      1 unsigned long
      1 struct mm_walk *walk
      1 struct mmu_gather *tlb
      1 struct address_space *mapping
      1 start
      1 size_t
      1 pmd_t *pmd
      1 madvise
      1 len_in
      1 int
      1 behavior
