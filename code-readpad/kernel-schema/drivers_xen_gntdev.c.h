
\n
bool gntdev_account_mapped_pages(int count)
static void gntdev_print_maps(struct gntdev_priv *priv, char *text, int text_index)
static void gntdev_free_map(struct gntdev_grant_map *map)
struct gntdev_grant_map *gntdev_alloc_map(struct gntdev_priv *priv, int count, int dma_flags)
void gntdev_add_map(struct gntdev_priv *priv, struct gntdev_grant_map *add)
static struct gntdev_grant_map *gntdev_find_map_index(struct gntdev_priv *priv, int index, int count)
void gntdev_put_map(struct gntdev_priv *priv, struct gntdev_grant_map *map)
static int find_grant_ptes(pte_t *pte, pgtable_t token, unsigned long addr, void *data)
static int set_grant_ptes_as_special(pte_t *pte, pgtable_t token, unsigned long addr, void *data)
int gntdev_map_grant_pages(struct gntdev_grant_map *map)
static int __unmap_grant_pages(struct gntdev_grant_map *map, int offset, int pages)
static int unmap_grant_pages(struct gntdev_grant_map *map, int offset, int pages)
static void gntdev_vma_open(struct vm_area_struct *vma)
static void gntdev_vma_close(struct vm_area_struct *vma)
static struct page *gntdev_vma_find_special_page(struct vm_area_struct *vma, unsigned long addr)
static bool in_range(struct gntdev_grant_map *map, unsigned long start, unsigned long end)
static int unmap_if_in_range(struct gntdev_grant_map *map, unsigned long start, unsigned long end, bool blockable)
static int mn_invl_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void mn_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int gntdev_open(struct inode *inode, struct file *flip)
static int gntdev_release(struct inode *inode, struct file *flip)
static long gntdev_ioctl_map_grant_ref(struct gntdev_priv *priv, struct ioctl_gntdev_map_grant_ref __user *u)
static long gntdev_ioctl_unmap_grant_ref(struct gntdev_priv *priv, struct ioctl_gntdev_unmap_grant_ref __user *u)
static long gntdev_ioctl_get_offset_for_vaddr(struct gntdev_priv *priv, struct ioctl_gntdev_get_offset_for_vaddr __user *u)
static long gntdev_ioctl_notify(struct gntdev_priv *priv, void __user *u)
static int gntdev_get_page(struct gntdev_copy_batch *batch, void __user *virt, bool writeable, unsigned long *gfn)
static void gntdev_put_pages(struct gntdev_copy_batch *batch)
static int gntdev_copy(struct gntdev_copy_batch *batch)
static int gntdev_grant_copy_seg(struct gntdev_copy_batch *batch, struct gntdev_grant_copy_segment *seg, s16 __user *status)
static long gntdev_ioctl_grant_copy(struct gntdev_priv *priv, void __user *u)
static long gntdev_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
static int gntdev_mmap(struct file *flip, struct vm_area_struct *vma)
static int __init gntdev_init(void)
static void __exit gntdev_exit(void)
\n
     10 struct gntdev_priv *priv
      7 struct gntdev_grant_map *map
      4 struct vm_area_struct *vma
      4 struct gntdev_copy_batch *batch
      4 struct file *flip
      3 unsigned long addr
      3 int count
      2 void __user *u
      2 void *data
      2 void
      2 unsigned long start
      2 unsigned long end
      2 struct mmu_notifier *mn
      2 struct inode *inode
      2 pte_t *pte
      2 pgtable_t token
      2 int pages
      2 int offset
      1 void __user *virt
      1 unsigned long *gfn
      1 unsigned long arg
      1 unsigned int cmd
      1 struct mm_struct *mm
      1 struct ioctl_gntdev_unmap_grant_ref __user *u
      1 struct ioctl_gntdev_map_grant_ref __user *u
      1 struct ioctl_gntdev_get_offset_for_vaddr __user *u
      1 struct gntdev_grant_map *add
      1 struct gntdev_grant_copy_segment *seg
      1 s16 __user *status
      1 int text_index
      1 int index
      1 int dma_flags
      1 const struct mmu_notifier_range *range
      1 char *text
      1 bool writeable
      1 bool blockable
