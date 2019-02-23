
\n
static __u32 ext4_inode_csum(struct inode *inode, struct ext4_inode *raw, struct ext4_inode_info *ei)
static int ext4_inode_csum_verify(struct inode *inode, struct ext4_inode *raw, struct ext4_inode_info *ei)
static void ext4_inode_csum_set(struct inode *inode, struct ext4_inode *raw, struct ext4_inode_info *ei)
static inline int ext4_begin_ordered_truncate(struct inode *inode, loff_t new_size)
int ext4_inode_is_fast_symlink(struct inode *inode)
int ext4_truncate_restart_trans(handle_t *handle, struct inode *inode, int nblocks)
void ext4_evict_inode(struct inode *inode)
qsize_t *ext4_get_reserved_space(struct inode *inode)
void ext4_da_update_reserve_space(struct inode *inode, int used, int quota_claim)
static int __check_block_validity(struct inode *inode, const char *func, unsigned int line, struct ext4_map_blocks *map)
int ext4_issue_zeroout(struct inode *inode, ext4_lblk_t lblk, ext4_fsblk_t pblk, ext4_lblk_t len)
static void ext4_map_blocks_es_recheck(handle_t *handle, struct inode *inode, struct ext4_map_blocks *es_map, struct ext4_map_blocks *map, int flags)
int ext4_map_blocks(handle_t *handle, struct inode *inode, struct ext4_map_blocks *map, int flags)
static void ext4_update_bh_state(struct buffer_head *bh, unsigned long flags)
static int _ext4_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh, int flags)
int ext4_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh, int create)
int ext4_get_block_unwritten(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
static int ext4_get_block_trans(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int flags)
int ext4_dio_get_block(struct inode *inode, sector_t iblock, struct buffer_head *bh, int create)
static int ext4_dio_get_block_unwritten_async(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
static int ext4_dio_get_block_unwritten_sync(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
static int ext4_dio_get_block_overwrite(struct inode *inode, sector_t iblock, struct buffer_head *bh_result, int create)
struct buffer_head *ext4_getblk(handle_t *handle, struct inode *inode, ext4_lblk_t block, int map_flags)
struct buffer_head *ext4_bread(handle_t *handle, struct inode *inode, ext4_lblk_t block, int map_flags)
int ext4_bread_batch(struct inode *inode, ext4_lblk_t block, int bh_count, bool wait, struct buffer_head **bhs)
int ext4_walk_page_buffers(handle_t *handle, struct buffer_head *head, unsigned from, unsigned to, int *partial, int (*fn)
(handle_t *handle, struct buffer_head *bh)
)
int do_journal_get_write_access(handle_t *handle, struct buffer_head *bh)
static int ext4_block_write_begin(struct page *page, loff_t pos, unsigned len, get_block_t *get_block)
static int ext4_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
static int write_end_fn(handle_t *handle, struct buffer_head *bh)
static int ext4_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static void ext4_journalled_zero_new_buffers(handle_t *handle, struct page *page, unsigned from, unsigned to)
static int ext4_journalled_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static int ext4_da_reserve_space(struct inode *inode)
void ext4_da_release_space(struct inode *inode, int to_free)
static void ext4_da_page_release_reservation(struct page *page, unsigned int offset, unsigned int length)
static void mpage_release_unused_pages(struct mpage_da_data *mpd, bool invalidate)
static void ext4_print_free_blocks(struct inode *inode)
static int ext4_bh_delay_or_unwritten(handle_t *handle, struct buffer_head *bh)
static int ext4_insert_delayed_block(struct inode *inode, ext4_lblk_t lblk)
static int ext4_da_map_blocks(struct inode *inode, sector_t iblock, struct ext4_map_blocks *map, struct buffer_head *bh)
int ext4_da_get_block_prep(struct inode *inode, sector_t iblock, struct buffer_head *bh, int create)
static int bget_one(handle_t *handle, struct buffer_head *bh)
static int bput_one(handle_t *handle, struct buffer_head *bh)
static int __ext4_journalled_writepage(struct page *page, unsigned int len)
static int ext4_writepage(struct page *page, struct writeback_control *wbc)
static int mpage_submit_page(struct mpage_da_data *mpd, struct page *page)
static bool mpage_add_bh_to_extent(struct mpage_da_data *mpd, ext4_lblk_t lblk, struct buffer_head *bh)
static int mpage_process_page_bufs(struct mpage_da_data *mpd, struct buffer_head *head, struct buffer_head *bh, ext4_lblk_t lblk)
static int mpage_map_and_submit_buffers(struct mpage_da_data *mpd)
static int mpage_map_one_extent(handle_t *handle, struct mpage_da_data *mpd)
static int mpage_map_and_submit_extent(handle_t *handle, struct mpage_da_data *mpd, bool *give_up_on_write)
static int ext4_da_writepages_trans_blocks(struct inode *inode)
static int mpage_prepare_extent_to_map(struct mpage_da_data *mpd)
static int ext4_writepages(struct address_space *mapping, struct writeback_control *wbc)
static int ext4_dax_writepages(struct address_space *mapping, struct writeback_control *wbc)
static int ext4_nonda_switch(struct super_block *sb)
static int ext4_da_write_credits(struct inode *inode, loff_t pos, unsigned len)
static int ext4_da_write_begin(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned flags, struct page **pagep, void **fsdata)
static int ext4_da_should_update_i_disksize(struct page *page, unsigned long offset)
static int ext4_da_write_end(struct file *file, struct address_space *mapping, loff_t pos, unsigned len, unsigned copied, struct page *page, void *fsdata)
static void ext4_da_invalidatepage(struct page *page, unsigned int offset, unsigned int length)
int ext4_alloc_da_blocks(struct inode *inode)
static sector_t ext4_bmap(struct address_space *mapping, sector_t block)
static int ext4_readpage(struct file *file, struct page *page)
static int ext4_readpages(struct file *file, struct address_space *mapping, struct list_head *pages, unsigned nr_pages)
static void ext4_invalidatepage(struct page *page, unsigned int offset, unsigned int length)
static int __ext4_journalled_invalidatepage(struct page *page, unsigned int offset, unsigned int length)
static void ext4_journalled_invalidatepage(struct page *page, unsigned int offset, unsigned int length)
static int ext4_releasepage(struct page *page, gfp_t wait)
static bool ext4_inode_datasync_dirty(struct inode *inode)
static int ext4_iomap_begin(struct inode *inode, loff_t offset, loff_t length, unsigned flags, struct iomap *iomap)
static int ext4_iomap_end(struct inode *inode, loff_t offset, loff_t length, ssize_t written, unsigned flags, struct iomap *iomap)
static int ext4_end_io_dio(struct kiocb *iocb, loff_t offset, ssize_t size, void *private)
static ssize_t ext4_direct_IO_write(struct kiocb *iocb, struct iov_iter *iter)
static ssize_t ext4_direct_IO_read(struct kiocb *iocb, struct iov_iter *iter)
static ssize_t ext4_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
static int ext4_journalled_set_page_dirty(struct page *page)
static int ext4_set_page_dirty(struct page *page)
void ext4_set_aops(struct inode *inode)
static int __ext4_block_zero_page_range(handle_t *handle, struct address_space *mapping, loff_t from, loff_t length)
static int ext4_block_zero_page_range(handle_t *handle, struct address_space *mapping, loff_t from, loff_t length)
static int ext4_block_truncate_page(handle_t *handle, struct address_space *mapping, loff_t from)
int ext4_zero_partial_blocks(handle_t *handle, struct inode *inode, loff_t lstart, loff_t length)
int ext4_can_truncate(struct inode *inode)
int ext4_update_disksize_before_punch(struct inode *inode, loff_t offset, loff_t len)
static void ext4_wait_dax_page(struct ext4_inode_info *ei)
int ext4_break_layouts(struct inode *inode)
int ext4_punch_hole(struct inode *inode, loff_t offset, loff_t length)
int ext4_inode_attach_jinode(struct inode *inode)
int ext4_truncate(struct inode *inode)
static int __ext4_get_inode_loc(struct inode *inode, struct ext4_iloc *iloc, int in_mem)
int ext4_get_inode_loc(struct inode *inode, struct ext4_iloc *iloc)
static bool ext4_should_use_dax(struct inode *inode)
void ext4_set_inode_flags(struct inode *inode)
static blkcnt_t ext4_inode_blocks(struct ext4_inode *raw_inode, struct ext4_inode_info *ei)
static inline int ext4_iget_extra_inode(struct inode *inode, struct ext4_inode *raw_inode, struct ext4_inode_info *ei)
int ext4_get_projid(struct inode *inode, kprojid_t *projid)
static inline void ext4_inode_set_iversion_queried(struct inode *inode, u64 val)
static inline void ext4_inode_set_iversion_queried(struct inode *inode, u64 val)
if (unlikely(EXT4_I(inode)
->i_flags & EXT4_EA_INODE_FL)
)
inode_set_iversion_raw(inode, val)
;else inode_set_iversion_queried(inode, val)
; } static inline u64 ext4_inode_peek_iversion(const struct inode *inode)
struct inode *__ext4_iget(struct super_block *sb, unsigned long ino, ext4_iget_flags flags, const char *function, unsigned int line)
static int ext4_inode_blocks_set(handle_t *handle, struct ext4_inode *raw_inode, struct ext4_inode_info *ei)
static int other_inode_match(struct inode * inode, unsigned long ino, void *data)
static void ext4_update_other_inodes_time(struct super_block *sb, unsigned long orig_ino, char *buf)
static int ext4_do_update_inode(handle_t *handle, struct inode *inode, struct ext4_iloc *iloc)
int ext4_write_inode(struct inode *inode, struct writeback_control *wbc)
static void ext4_wait_for_tail_page_commit(struct inode *inode)
int ext4_setattr(struct dentry *dentry, struct iattr *attr)
int ext4_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
int ext4_file_getattr(const struct path *path, struct kstat *stat, u32 request_mask, unsigned int query_flags)
static int ext4_index_trans_blocks(struct inode *inode, int lblocks, int pextents)
static int ext4_meta_trans_blocks(struct inode *inode, int lblocks, int pextents)
int ext4_writepage_trans_blocks(struct inode *inode)
int ext4_chunk_trans_blocks(struct inode *inode, int nrblocks)
int ext4_mark_iloc_dirty(handle_t *handle, struct inode *inode, struct ext4_iloc *iloc)
int ext4_reserve_inode_write(handle_t *handle, struct inode *inode, struct ext4_iloc *iloc)
static int __ext4_expand_extra_isize(struct inode *inode, unsigned int new_extra_isize, struct ext4_iloc *iloc, handle_t *handle, int *no_expand)
static int ext4_try_to_expand_extra_isize(struct inode *inode, unsigned int new_extra_isize, struct ext4_iloc iloc, handle_t *handle)
int ext4_expand_extra_isize(struct inode *inode, unsigned int new_extra_isize, struct ext4_iloc *iloc)
int ext4_mark_inode_dirty(handle_t *handle, struct inode *inode)
void ext4_dirty_inode(struct inode *inode, int flags)
static int ext4_pin_inode(handle_t *handle, struct inode *inode)
int ext4_change_inode_journal_flag(struct inode *inode, int val)
static int ext4_bh_unmapped(handle_t *handle, struct buffer_head *bh)
vm_fault_t ext4_page_mkwrite(struct vm_fault *vmf)
vm_fault_t ext4_filemap_fault(struct vm_fault *vmf)
\n
     68 struct inode *inode
     28 handle_t *handle
     18 struct page *page
     15 struct buffer_head *bh
     12 struct address_space *mapping
     10 sector_t iblock
      8 struct mpage_da_data *mpd
      7 unsigned len
      7 struct file *file
      7 struct ext4_inode_info *ei
      7 struct ext4_iloc *iloc
      7 loff_t pos
      7 int create
      6 loff_t length
      5 unsigned int offset
      5 unsigned int length
      5 struct buffer_head *bh_result
      5 loff_t offset
      5 int flags
      4 unsigned flags
      4 struct writeback_control *wbc
      4 struct kiocb *iocb
      4 struct ext4_map_blocks *map
      4 ext4_lblk_t lblk
      3 void *fsdata
      3 unsigned int new_extra_isize
      3 unsigned copied
      3 struct super_block *sb
      3 struct iov_iter *iter
      3 struct ext4_inode *raw_inode
      3 struct ext4_inode *raw
      3 loff_t from
      3 ext4_lblk_t block
      2 void **fsdata
      2 val
      2 unsigned to
      2 unsigned long ino
      2 unsigned int query_flags
      2 unsigned int line
      2 unsigned from
      2 u64 val
      2 u32 request_mask
      2 struct vm_fault *vmf
      2 struct page **pagep
      2 struct kstat *stat
      2 struct iomap *iomap
      2 struct buffer_head *head
      2 int pextents
      2 int map_flags
      2 int lblocks
      2 inode
      2 const struct path *path
      1 void *private
      1 void *data
      1 unsigned nr_pages
      1 unsigned long orig_ino
      1 unsigned long offset
      1 unsigned long flags
      1 unsigned int len
      1 unlikelyEXT4_Iinode
      1 struct list_head *pages
      1 struct inode * inode
      1 struct iattr *attr
      1 struct ext4_map_blocks *es_map
      1 struct ext4_iloc iloc
      1 struct dentry *dentry
      1 struct buffer_head **bhs
      1 ssize_t written
      1 ssize_t size
      1 sector_t block
      1 loff_t new_size
      1 loff_t lstart
      1 loff_t len
      1 kprojid_t *projid
      1 int val
      1 int used
      1 int to_free
      1 int quota_claim
      1 int *partial
      1 int nrblocks
      1 int *no_expand
      1 int nblocks
      1 int in_mem
      1 int *fn
      1 int bh_count
      1 gfp_t wait
      1 get_block_t *get_block
      1 ext4_lblk_t len
      1 ext4_iget_flags flags
      1 ext4_fsblk_t pblk
      1 const struct inode *inode
      1 const char *function
      1 const char *func
      1 char *buf
      1 bool wait
      1 bool invalidate
      1 bool *give_up_on_write
