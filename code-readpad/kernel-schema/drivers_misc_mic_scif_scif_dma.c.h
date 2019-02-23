
EXPORT_SYMBOL_GPL(scif_readfrom);
EXPORT_SYMBOL_GPL(scif_writeto);
EXPORT_SYMBOL_GPL(scif_vreadfrom);
EXPORT_SYMBOL_GPL(scif_vwriteto);
\n
int scif_reserve_dma_chan(struct scif_endpt *ep)
static void __scif_rma_destroy_tcw(struct scif_mmu_notif *mmn, u64 start, u64 len)
static void scif_rma_destroy_tcw(struct scif_mmu_notif *mmn, u64 start, u64 len)
static void scif_rma_destroy_tcw_ep(struct scif_endpt *ep)
static void __scif_rma_destroy_tcw_ep(struct scif_endpt *ep)
static bool scif_rma_tc_can_cache(struct scif_endpt *ep, size_t cur_bytes)
static void scif_mmu_notifier_release(struct mmu_notifier *mn, struct mm_struct *mm)
static int scif_mmu_notifier_invalidate_range_start(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void scif_mmu_notifier_invalidate_range_end(struct mmu_notifier *mn, const struct mmu_notifier_range *range)
static void scif_ep_unregister_mmu_notifier(struct scif_endpt *ep)
static void scif_init_mmu_notifier(struct scif_mmu_notif *mmn, struct mm_struct *mm, struct scif_endpt *ep)
static struct scif_mmu_notif * scif_find_mmu_notifier(struct mm_struct *mm, struct scif_endpt_rma_info *rma)
static struct scif_mmu_notif * scif_add_mmu_notifier(struct mm_struct *mm, struct scif_endpt *ep)
void scif_mmu_notif_handler(struct work_struct *work)
static bool scif_is_set_reg_cache(int flags)
static bool scif_is_set_reg_cache(int flags)
return !!(flags & SCIF_RMA_USECACHE)
; } static struct scif_mmu_notif * scif_find_mmu_notifier(struct mm_struct *mm, struct scif_endpt_rma_info *rma)
static struct scif_mmu_notif * scif_add_mmu_notifier(struct mm_struct *mm, struct scif_endpt *ep)
void scif_mmu_notif_handler(struct work_struct *work)
static bool scif_is_set_reg_cache(int flags)
static bool scif_rma_tc_can_cache(struct scif_endpt *ep, size_t cur_bytes)
static int scif_register_temp(scif_epd_t epd, unsigned long addr, size_t len, int prot, off_t *out_offset, struct scif_window **out_window)
static int scif_sync_dma(struct scif_hw_dev *sdev, struct dma_chan *chan, bool sync_wait)
static void scif_dma_callback(void *arg)
static int scif_async_dma(struct scif_hw_dev *sdev, struct dma_chan *chan)
static int scif_drain_dma_poll(struct scif_hw_dev *sdev, struct dma_chan *chan)
int scif_drain_dma_intr(struct scif_hw_dev *sdev, struct dma_chan *chan)
void scif_rma_destroy_windows(void)
void scif_rma_destroy_tcw_invalid(void)
static inline void *_get_local_va(off_t off, struct scif_window *window, size_t len)
static inline void *ioremap_remote(off_t off, struct scif_window *window, size_t len, struct scif_dev *dev, struct scif_window_iter *iter)
static inline void iounmap_remote(void *virt, size_t size, struct scif_copy_work *work)
static inline void scif_ordered_memcpy_toio(char *dst, const char *src, size_t count)
static inline void scif_unaligned_cpy_toio(char *dst, const char *src, size_t count, bool ordered)
static inline void scif_ordered_memcpy_fromio(char *dst, const char *src, size_t count)
static inline void scif_unaligned_cpy_fromio(char *dst, const char *src, size_t count, bool ordered)
dma_addr_t scif_off_to_dma_addr(struct scif_window *window, s64 off, size_t *nr_bytes, struct scif_window_iter *iter)
static void scif_rma_local_cpu_copy(s64 offset, struct scif_window *window, u8 *temp, size_t rem_len, bool to_temp)
static void scif_rma_completion_cb(void *data)
static int scif_rma_list_dma_copy_unaligned(struct scif_copy_work *work, u8 *temp, struct dma_chan *chan, bool src_local)
static int _scif_rma_list_dma_copy_aligned(struct scif_copy_work *work, struct dma_chan *chan)
static int scif_rma_list_dma_copy_aligned(struct scif_copy_work *work, struct dma_chan *chan)
static int scif_rma_list_cpu_copy(struct scif_copy_work *work)
static int scif_rma_list_dma_copy_wrapper(struct scif_endpt *epd, struct scif_copy_work *work, struct dma_chan *chan, off_t loffset)
static int scif_rma_copy(scif_epd_t epd, off_t loffset, unsigned long addr, size_t len, off_t roffset, int flags, enum scif_rma_dir dir, bool last_chunk)
int scif_readfrom(scif_epd_t epd, off_t loffset, size_t len, off_t roffset, int flags)
int scif_writeto(scif_epd_t epd, off_t loffset, size_t len, off_t roffset, int flags)
int scif_vreadfrom(scif_epd_t epd, void *addr, size_t len, off_t roffset, int flags)
int scif_vwriteto(scif_epd_t epd, void *addr, size_t len, off_t roffset, int flags)
\n
      9 struct scif_endpt *ep
      8 struct dma_chan *chan
      8 size_t len
      8 int flags
      6 struct scif_copy_work *work
      6 struct mm_struct *mm
      6 scif_epd_t epd
      5 off_t roffset
      4 struct scif_window *window
      4 struct scif_hw_dev *sdev
      4 size_t count
      4 off_t loffset
      4 const char *src
      4 char *dst
      3 struct scif_mmu_notif *mmn
      3 struct mmu_notifier *mn
      2 void *addr
      2 void
      2 unsigned long addr
      2 u8 *temp
      2 u64 start
      2 u64 len
      2 struct work_struct *work
      2 struct scif_window_iter *iter
      2 struct scif_endpt_rma_info *rma
      2 size_t cur_bytes
      2 off_t off
      2 const struct mmu_notifier_range *range
      2 bool ordered
      1 void *virt
      1 void *data
      1 void *arg
      1 struct scif_window **out_window
      1 struct scif_endpt *epd
      1 struct scif_dev *dev
      1 size_t size
      1 size_t rem_len
      1 size_t *nr_bytes
      1 scif_writeto
      1 scif_vwriteto
      1 scif_vreadfrom
      1 scif_readfrom
      1 s64 offset
      1 s64 off
      1 off_t *out_offset
      1 int prot
      1 flags & SCIF_RMA_USECACHE
      1 enum scif_rma_dir dir
      1 bool to_temp
      1 bool sync_wait
      1 bool src_local
      1 bool last_chunk
