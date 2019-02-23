
EXPORT_SYMBOL_GPL(dax_layout_busy_page);
EXPORT_SYMBOL_GPL(dax_writeback_mapping_range);
EXPORT_SYMBOL_GPL(__dax_zero_page_range);
EXPORT_SYMBOL_GPL(dax_iomap_rw);
EXPORT_SYMBOL_GPL(dax_iomap_fault);
EXPORT_SYMBOL_GPL(dax_finish_sync_fault);
\n
static inline unsigned int pe_order(enum page_entry_size pe_size)
static int __init init_dax_wait_table(void)
static unsigned long dax_to_pfn(void *entry)
static void *dax_make_entry(pfn_t pfn, unsigned long flags)
static bool dax_is_locked(void *entry)
static unsigned int dax_entry_order(void *entry)
static unsigned long dax_is_pmd_entry(void *entry)
static bool dax_is_pte_entry(void *entry)
static int dax_is_zero_entry(void *entry)
static int dax_is_empty_entry(void *entry)
static wait_queue_head_t *dax_entry_waitqueue(struct xa_state *xas, void *entry, struct exceptional_entry_key *key)
static int wake_exceptional_entry_func(wait_queue_entry_t *wait, unsigned int mode, int sync, void *keyp)
static void dax_wake_entry(struct xa_state *xas, void *entry, bool wake_all)
static void *get_unlocked_entry(struct xa_state *xas)
static void wait_entry_unlocked(struct xa_state *xas, void *entry)
static void put_unlocked_entry(struct xa_state *xas, void *entry)
static void dax_unlock_entry(struct xa_state *xas, void *entry)
static void *dax_lock_entry(struct xa_state *xas, void *entry)
static unsigned long dax_entry_size(void *entry)
static unsigned long dax_end_pfn(void *entry)
static void dax_associate_entry(void *entry, struct address_space *mapping, struct vm_area_struct *vma, unsigned long address)
static void dax_disassociate_entry(void *entry, struct address_space *mapping, bool trunc)
static struct page *dax_busy_page(void *entry)
dax_entry_t dax_lock_page(struct page *page)
void dax_unlock_page(struct page *page, dax_entry_t cookie)
static void *grab_mapping_entry(struct xa_state *xas, struct address_space *mapping, unsigned long size_flag)
struct page *dax_layout_busy_page(struct address_space *mapping)
static int __dax_invalidate_entry(struct address_space *mapping, pgoff_t index, bool trunc)
int dax_delete_mapping_entry(struct address_space *mapping, pgoff_t index)
int dax_invalidate_mapping_entry_sync(struct address_space *mapping, pgoff_t index)
static int copy_user_dax(struct block_device *bdev, struct dax_device *dax_dev, sector_t sector, size_t size, struct page *to, unsigned long vaddr)
static void *dax_insert_entry(struct xa_state *xas, struct address_space *mapping, struct vm_fault *vmf, void *entry, pfn_t pfn, unsigned long flags, bool dirty)
static inline unsigned long pgoff_address(pgoff_t pgoff, struct vm_area_struct *vma)
static void dax_entry_mkclean(struct address_space *mapping, pgoff_t index, unsigned long pfn)
static int dax_writeback_one(struct xa_state *xas, struct dax_device *dax_dev, struct address_space *mapping, void *entry)
int dax_writeback_mapping_range(struct address_space *mapping, struct block_device *bdev, struct writeback_control *wbc)
static sector_t dax_iomap_sector(struct iomap *iomap, loff_t pos)
static int dax_iomap_pfn(struct iomap *iomap, loff_t pos, size_t size, pfn_t *pfnp)
static vm_fault_t dax_load_hole(struct xa_state *xas, struct address_space *mapping, void **entry, struct vm_fault *vmf)
static bool dax_range_is_aligned(struct block_device *bdev, unsigned int offset, unsigned int length)
int __dax_zero_page_range(struct block_device *bdev, struct dax_device *dax_dev, sector_t sector, unsigned int offset, unsigned int size)
static loff_t dax_iomap_actor(struct inode *inode, loff_t pos, loff_t length, void *data, struct iomap *iomap)
ssize_t dax_iomap_rw(struct kiocb *iocb, struct iov_iter *iter, const struct iomap_ops *ops)
static vm_fault_t dax_fault_return(int error)
static bool dax_fault_is_synchronous(unsigned long flags, struct vm_area_struct *vma, struct iomap *iomap)
static vm_fault_t dax_iomap_pte_fault(struct vm_fault *vmf, pfn_t *pfnp, int *iomap_errp, const struct iomap_ops *ops)
static vm_fault_t dax_pmd_load_hole(struct xa_state *xas, struct vm_fault *vmf, struct iomap *iomap, void **entry)
static vm_fault_t dax_iomap_pmd_fault(struct vm_fault *vmf, pfn_t *pfnp, const struct iomap_ops *ops)
if (result == VM_FAULT_FALLBACK)
copied = 0;ops->iomap_end(inode, pos, PMD_SIZE, copied, iomap_flags, &iomap)
;}unlock_entry:dax_unlock_entry(&xas, entry)
;fallback: split_huge_pmd(vma, vmf->pmd, vmf->address)
; count_vm_event(THP_FAULT_FALLBACK)
;} out:trace_dax_pmd_fault_done(inode, vmf, max_pgoff, result)
;return result; } static vm_fault_t dax_iomap_pmd_fault(struct vm_fault *vmf, pfn_t *pfnp, const struct iomap_ops *ops)
vm_fault_t dax_iomap_fault(struct vm_fault *vmf, enum page_entry_size pe_size, pfn_t *pfnp, int *iomap_errp, const struct iomap_ops *ops)
static vm_fault_t dax_insert_pfn_mkwrite(struct vm_fault *vmf, pfn_t pfn, unsigned int order)
vm_fault_t dax_finish_sync_fault(struct vm_fault *vmf, enum page_entry_size pe_size, pfn_t pfn)
\n
     20 void *entry
     12 struct xa_state *xas
     12 struct address_space *mapping
      9 struct vm_fault *vmf
      5 struct iomap *iomap
      5 pfn_t *pfnp
      5 const struct iomap_ops *ops
      4 struct block_device *bdev
      4 pgoff_t index
      4 pfn_t pfn
      3 unsigned long flags
      3 struct vm_area_struct *vma
      3 struct dax_device *dax_dev
      3 loff_t pos
      3 enum page_entry_size pe_size
      2 void **entry
      2 unsigned int offset
      2 struct page *page
      2 size_t size
      2 sector_t sector
      2 int *iomap_errp
      2 inode
      2 bool trunc
      1 &xas
      1 wait_queue_entry_t *wait
      1 void *keyp
      1 void *data
      1 void
      1 vmf->pmd
      1 vmf->address
      1 vmf
      1 vma
      1 unsigned long vaddr
      1 unsigned long size_flag
      1 unsigned long pfn
      1 unsigned long address
      1 unsigned int size
      1 unsigned int order
      1 unsigned int mode
      1 unsigned int length
      1 THP_FAULT_FALLBACK
      1 struct writeback_control *wbc
      1 struct page *to
      1 struct kiocb *iocb
      1 struct iov_iter *iter
      1 struct inode *inode
      1 struct exceptional_entry_key *key
      1 result == VM_FAULT_FALLBACK
      1 result
      1 pos
      1 PMD_SIZE
      1 pgoff_t pgoff
      1 max_pgoff
      1 loff_t length
      1 iomap_flags
      1 &iomap
      1 int sync
      1 int error
      1 entry
      1 __dax_zero_page_range
      1 dax_writeback_mapping_range
      1 dax_layout_busy_page
      1 dax_iomap_rw
      1 dax_iomap_fault
      1 dax_finish_sync_fault
      1 dax_entry_t cookie
      1 copied
      1 bool wake_all
      1 bool dirty
