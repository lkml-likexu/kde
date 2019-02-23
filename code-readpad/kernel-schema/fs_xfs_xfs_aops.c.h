
\n
struct block_device * xfs_find_bdev_for_inode(struct inode*inode)
struct dax_device * xfs_find_daxdev_for_inode(struct inode*inode)
static void xfs_finish_page_writeback(struct inode*inode, struct bio_vec*bvec, int error)
STATIC void xfs_destroy_ioend(struct xfs_ioend *ioend, int error)
static inline bool xfs_ioend_is_append(struct xfs_ioend *ioend)
STATIC int xfs_setfilesize_trans_alloc(struct xfs_ioend *ioend)
STATIC int __xfs_setfilesize(struct xfs_inode *ip, struct xfs_trans *tp, xfs_off_toffset, size_t size)
int xfs_setfilesize(struct xfs_inode *ip, xfs_off_toffset, size_t size)
STATIC int xfs_setfilesize_ioend(struct xfs_ioend *ioend, int error)
STATIC void xfs_end_io(struct work_struct *work)
STATIC void xfs_end_bio(struct bio*bio)
STATIC int xfs_map_blocks(struct xfs_writepage_ctx *wpc, struct inode*inode, loff_t offset)
STATIC int xfs_submit_ioend(struct writeback_control *wbc, struct xfs_ioend *ioend, int status)
static struct xfs_ioend * xfs_alloc_ioend(struct inode*inode, unsigned inttype, xfs_off_toffset, struct block_device *bdev, sector_tsector)
static void xfs_chain_bio(struct xfs_ioend *ioend, struct writeback_control *wbc, struct block_device *bdev, sector_tsector)
STATIC void xfs_add_to_ioend(struct inode*inode, xfs_off_toffset, struct page*page, struct iomap_page *iop, struct xfs_writepage_ctx *wpc, struct writeback_control *wbc, struct list_head *iolist)
STATIC void xfs_vm_invalidatepage(struct page*page, unsigned intoffset, unsigned intlength)
STATIC void xfs_aops_discard_page(struct page*page)
static int xfs_writepage_map(struct xfs_writepage_ctx *wpc, struct writeback_control *wbc, struct inode*inode, struct page*page, uint64_tend_offset)
STATIC int xfs_do_writepage(struct page*page, struct writeback_control *wbc, void *data)
STATIC int xfs_vm_writepage(struct page*page, struct writeback_control *wbc)
STATIC int xfs_vm_writepages(struct address_space *mapping, struct writeback_control *wbc)
STATIC int xfs_dax_writepages(struct address_space *mapping, struct writeback_control *wbc)
STATIC int xfs_vm_releasepage(struct page*page, gfp_t gfp_mask)
STATIC sector_t xfs_vm_bmap(struct address_space *mapping, sector_tblock)
STATIC int xfs_vm_readpage(struct file*unused, struct page*page)
STATIC int xfs_vm_readpages(struct file*unused, struct address_space *mapping, struct list_head *pages, unsignednr_pages)
static int xfs_iomap_swapfile_activate(struct swap_info_struct*sis, struct file *swap_file, sector_t *span)
\n
      8 struct writeback_control *wbc
      8 struct page*page
      7 struct inode*inode
      6 struct xfs_ioend *ioend
      4 xfs_off_toffset
      4 struct address_space *mapping
      3 struct xfs_writepage_ctx *wpc
      3 int error
      2 struct xfs_inode *ip
      2 struct file*unused
      2 struct block_device *bdev
      2 size_t size
      2 sector_tsector
      1 void *data
      1 unsignednr_pages
      1 unsigned inttype
      1 unsigned intoffset
      1 unsigned intlength
      1 uint64_tend_offset
      1 struct xfs_trans *tp
      1 struct work_struct *work
      1 struct swap_info_struct*sis
      1 struct list_head *pages
      1 struct list_head *iolist
      1 struct iomap_page *iop
      1 struct file *swap_file
      1 struct bio_vec*bvec
      1 struct bio*bio
      1 sector_t *span
      1 sector_tblock
      1 loff_t offset
      1 int status
      1 gfp_t gfp_mask
