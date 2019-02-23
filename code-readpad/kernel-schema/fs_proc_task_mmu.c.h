
\n
define SEQ_PUT_DEC(str, val)
\ seq_put_decimal_ull_width(m, str, (val)
<< (PAGE_SHIFT-10)
, 8)
void task_mem(struct seq_file *m, struct mm_struct *mm)
unsigned long task_vsize(struct mm_struct *mm)
unsigned long task_statm(struct mm_struct *mm, unsigned long *shared, unsigned long *text, unsigned long *data, unsigned long *resident)
static void hold_task_mempolicy(struct proc_maps_private *priv)
task_lock(task)
;priv->task_mempolicy = get_task_policy(task)
;mpol_get(priv->task_mempolicy)
;task_unlock(task)
; } static void release_task_mempolicy(struct proc_maps_private *priv)
task_lock(task)
;priv->task_mempolicy = get_task_policy(task)
;mpol_get(priv->task_mempolicy)
;task_unlock(task)
; } static void release_task_mempolicy(struct proc_maps_private *priv)
mpol_put(priv->task_mempolicy)
; } static void hold_task_mempolicy(struct proc_maps_private *priv)
task_lock(task)
;priv->task_mempolicy = get_task_policy(task)
;mpol_get(priv->task_mempolicy)
;task_unlock(task)
; } static void release_task_mempolicy(struct proc_maps_private *priv)
mpol_put(priv->task_mempolicy)
; } static void hold_task_mempolicy(struct proc_maps_private *priv)
} static void release_task_mempolicy(struct proc_maps_private *priv)
static void vma_stop(struct proc_maps_private *priv)
static struct vm_area_struct * m_next_vma(struct proc_maps_private *priv, struct vm_area_struct *vma)
static void m_cache_vma(struct seq_file *m, struct vm_area_struct *vma)
static void *m_start(struct seq_file *m, loff_t *ppos)
static void *m_next(struct seq_file *m, void *v, loff_t *pos)
static void m_stop(struct seq_file *m, void *v)
static int proc_maps_open(struct inode *inode, struct file *file, const struct seq_operations *ops, int psize)
static int proc_map_release(struct inode *inode, struct file *file)
static int do_maps_open(struct inode *inode, struct file *file, const struct seq_operations *ops)
static int is_stack(struct vm_area_struct *vma)
static void show_vma_header_prefix(struct seq_file *m, unsigned long start, unsigned long end, vm_flags_t flags, unsigned long long pgoff, dev_t dev, unsigned long ino)
static void show_map_vma(struct seq_file *m, struct vm_area_struct *vma)
static int show_map(struct seq_file *m, void *v)
static int pid_maps_open(struct inode *inode, struct file *file)
static void smaps_account(struct mem_size_stats *mss, struct page *page, bool compound, bool young, bool dirty, bool locked)
static int smaps_pte_hole(unsigned long addr, unsigned long end, struct mm_walk *walk)
static void smaps_pte_entry(pte_t *pte, unsigned long addr, struct mm_walk *walk)
static void smaps_pmd_entry(pmd_t *pmd, unsigned long addr, struct mm_walk *walk)
page = follow_trans_huge_pmd(vma, addr, pmd, FOLL_DUMP)
;if (IS_ERR_OR_NULL(page)
)
return;if (PageAnon(page)
)
mss->anonymous_thp += HPAGE_PMD_SIZE;else if (PageSwapBacked(page)
)
mss->shmem_thp += HPAGE_PMD_SIZE;else if (is_zone_device_page(page)
)
;else VM_BUG_ON_PAGE(1, page)
;smaps_account(mss, page, true, pmd_young(*pmd)
, pmd_dirty(*pmd)
, locked)
; } static void smaps_pmd_entry(pmd_t *pmd, unsigned long addr, struct mm_walk *walk)
static int smaps_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
static void show_smap_vma_flags(struct seq_file *m, struct vm_area_struct *vma)
static int smaps_hugetlb_range(pte_t *pte, unsigned long hmask, unsigned long addr, unsigned long end, struct mm_walk *walk)
static void smap_gather_stats(struct vm_area_struct *vma, struct mem_size_stats *mss)
static void __show_smap(struct seq_file *m, const struct mem_size_stats *mss)
static int show_smap(struct seq_file *m, void *v)
static int show_smaps_rollup(struct seq_file *m, void *v)
static int pid_smaps_open(struct inode *inode, struct file *file)
static int smaps_rollup_open(struct inode *inode, struct file *file)
static int smaps_rollup_release(struct inode *inode, struct file *file)
static inline void clear_soft_dirty(struct vm_area_struct *vma, unsigned long addr, pte_t *pte)
ptent = ptep_modify_prot_start(vma->vm_mm, addr, pte)
; ptent = pte_wrprotect(ptent)
; ptent = pte_clear_soft_dirty(ptent)
; ptep_modify_prot_commit(vma->vm_mm, addr, pte, ptent)
; ptent = pte_swp_clear_soft_dirty(ptent)
; set_pte_at(vma->vm_mm, addr, pte, ptent)
;} } static inline void clear_soft_dirty(struct vm_area_struct *vma, unsigned long addr, pte_t *pte)
static inline void clear_soft_dirty_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
set_pmd_at(vma->vm_mm, addr, pmdp, pmd)
; pmd = pmd_swp_clear_soft_dirty(pmd)
; set_pmd_at(vma->vm_mm, addr, pmdp, pmd)
;} } static inline void clear_soft_dirty_pmd(struct vm_area_struct *vma, unsigned long addr, pmd_t *pmdp)
static int clear_refs_pte_range(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int clear_refs_test_walk(unsigned long start, unsigned long end, struct mm_walk *walk)
static ssize_t clear_refs_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
static inline pagemap_entry_t make_pme(u64 frame, u64 flags)
static int add_to_pagemap(unsigned long addr, pagemap_entry_t *pme, struct pagemapread *pm)
static int pagemap_pte_hole(unsigned long start, unsigned long end, struct mm_walk *walk)
static pagemap_entry_t pte_to_pagemap_entry(struct pagemapread *pm, struct vm_area_struct *vma, unsigned long addr, pte_t pte)
static int pagemap_pmd_range(pmd_t *pmdp, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int pagemap_hugetlb_range(pte_t *ptep, unsigned long hmask, unsigned long addr, unsigned long end, struct mm_walk *walk)
static ssize_t pagemap_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
static int pagemap_open(struct inode *inode, struct file *file)
static int pagemap_release(struct inode *inode, struct file *file)
static void gather_stats(struct page *page, struct numa_maps *md, int pte_dirty, unsigned long nr_pages)
static struct page *can_gather_numa_stats(pte_t pte, struct vm_area_struct *vma, unsigned long addr)
static struct page *can_gather_numa_stats_pmd(pmd_t pmd, struct vm_area_struct *vma, unsigned long addr)
static int gather_pte_stats(pmd_t *pmd, unsigned long addr, unsigned long end, struct mm_walk *walk)
} while (pte++, addr += PAGE_SIZE, addr != end)
;pte_unmap_unlock(orig_pte, ptl)
;cond_resched()
;return 0; } static int gather_hugetlb_stats(pte_t *pte, unsigned long hmask, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int gather_hugetlb_stats(pte_t *pte, unsigned long hmask, unsigned long addr, unsigned long end, struct mm_walk *walk)
static int show_numa_map(struct seq_file *m, void *v)
static int pid_numa_maps_open(struct inode *inode, struct file *file)
\n
     20 unsigned long addr
     14 struct mm_walk *walk
     13 struct vm_area_struct *vma
     13 struct seq_file *m
     12 unsigned long end
     12 struct file *file
     10 struct inode *inode
      9 task
      9 struct proc_maps_private *priv
      6 void *v
      6 pte_t *pte
      6 addr
      5 vma->vm_mm
      5 ptent
      5 priv->task_mempolicy
      5 pmd_t *pmd
      4 unsigned long hmask
      4 pmd
      3 unsigned long start
      3 struct mm_struct *mm
      3 pte
      3 pmd_t *pmdp
      3 loff_t *ppos
      2 val
      2 struct page *page
      2 struct pagemapread *pm
      2 struct mem_size_stats *mss
      2 str
      2 size_t count
      2 pte_t pte
      2 pmdp
      2 page
      2 const struct seq_operations *ops
      1 vm_flags_t flags
      1 vma
      1 unsigned long *text
      1 unsigned long *shared
      1 unsigned long *resident
      1 unsigned long nr_pages
      1 unsigned long long pgoff
      1 unsigned long ino
      1 unsigned long *data
      1 u64 frame
      1 u64 flags
      1 true
      1 struct numa_maps *md
      1 ptl
      1 pte_t *ptep
      1 pte++
      1 pmd_young*pmd
      1 pmd_t pmd
      1 *pmd
      1 PageSwapBackedpage
      1 PAGE_SHIFT-10
      1 pagemap_entry_t *pme
      1 PageAnonpage
      1 orig_pte
      1 mss
      1 m
      1 loff_t *pos
      1 is_zone_device_pagepage
      1 IS_ERR_OR_NULLpage
      1 int pte_dirty
      1 int psize
      1 FOLL_DUMP
      1 dev_t dev
      1 const struct mem_size_stats *mss
      1 const char __user *buf
      1 char __user *buf
      1 bool young
      1 bool locked
      1 bool dirty
      1 bool compound
      1 addr += PAGE_SIZE
      1 addr != end
      1 1
      1 
