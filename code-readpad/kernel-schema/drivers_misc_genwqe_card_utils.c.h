
\n
int __genwqe_writeq(struct genwqe_dev *cd, u64 byte_offs, u64 val)
u64 __genwqe_readq(struct genwqe_dev *cd, u64 byte_offs)
int __genwqe_writel(struct genwqe_dev *cd, u64 byte_offs, u32 val)
u32 __genwqe_readl(struct genwqe_dev *cd, u64 byte_offs)
int genwqe_read_app_id(struct genwqe_dev *cd, char *app_name, int len)
void genwqe_init_crc32(void)
* Example: 4 bytes 0x01 0x02 0x03 0x04 with init=0xffffffff should* result in a crc32 of 0xf33cb7d3.** The existing kernel crc functions did not cover this polynom yet.** Return: crc32 checksum.*/ u32 genwqe_crc32(u8 *buff, size_t len, u32 init)
void *__genwqe_alloc_consistent(struct genwqe_dev *cd, size_t size, dma_addr_t *dma_handle)
void __genwqe_free_consistent(struct genwqe_dev *cd, size_t size, void *vaddr, dma_addr_t dma_handle)
static void genwqe_unmap_pages(struct genwqe_dev *cd, dma_addr_t *dma_list, int num_pages)
static int genwqe_map_pages(struct genwqe_dev *cd, struct page **page_list, int num_pages, dma_addr_t *dma_list)
static int genwqe_sgl_size(int num_pages)
int genwqe_alloc_sync_sgl(struct genwqe_dev *cd, struct genwqe_sgl *sgl, void __user *user_addr, size_t user_size, int write)
int genwqe_setup_sgl(struct genwqe_dev *cd, struct genwqe_sgl *sgl, dma_addr_t *dma_list)
int genwqe_free_sync_sgl(struct genwqe_dev *cd, struct genwqe_sgl *sgl)
static int genwqe_free_user_pages(struct page **page_list, unsigned int nr_pages, int dirty)
int genwqe_user_vmap(struct genwqe_dev *cd, struct dma_mapping *m, void *uaddr, unsigned long size)
int genwqe_user_vunmap(struct genwqe_dev *cd, struct dma_mapping *m)
u8 genwqe_card_type(struct genwqe_dev *cd)
int genwqe_card_reset(struct genwqe_dev *cd)
int genwqe_read_softreset(struct genwqe_dev *cd)
int genwqe_set_interrupt_capability(struct genwqe_dev *cd, int count)
void genwqe_reset_interrupt_capability(struct genwqe_dev *cd)
static int set_reg_idx(struct genwqe_dev *cd, struct genwqe_reg *r, unsigned int *i, unsigned int m, u32 addr, u32 idx, u64 val)
static int set_reg(struct genwqe_dev *cd, struct genwqe_reg *r, unsigned int *i, unsigned int m, u32 addr, u64 val)
int genwqe_read_ffdc_regs(struct genwqe_dev *cd, struct genwqe_reg *regs, unsigned int max_regs, int all)
int genwqe_ffdc_buff_size(struct genwqe_dev *cd, int uid)
int genwqe_ffdc_buff_read(struct genwqe_dev *cd, int uid, struct genwqe_reg *regs, unsigned int max_regs)
int genwqe_write_vreg(struct genwqe_dev *cd, u32 reg, u64 val, int func)
u64 genwqe_read_vreg(struct genwqe_dev *cd, u32 reg, int func)
int genwqe_base_clock_frequency(struct genwqe_dev *cd)
void genwqe_stop_traps(struct genwqe_dev *cd)
void genwqe_start_traps(struct genwqe_dev *cd)
\n
     29 struct genwqe_dev *cd
      4 u64 val
      4 u64 byte_offs
      3 struct genwqe_sgl *sgl
      3 int num_pages
      3 dma_addr_t *dma_list
      2 unsigned int max_regs
      2 unsigned int m
      2 unsigned int *i
      2 u32 reg
      2 u32 addr
      2 struct page **page_list
      2 struct genwqe_reg *regs
      2 struct genwqe_reg *r
      2 struct dma_mapping *m
      2 size_t size
      2 int uid
      2 int func
      1 void *vaddr
      1 void __user *user_addr
      1 void *uaddr
      1 void
      1 unsigned long size
      1 unsigned int nr_pages
      1 u8 *buff
      1 u32 val
      1 u32 init
      1 u32 idx
      1 size_t user_size
      1 size_t len
      1 int write
      1 int len
      1 int dirty
      1 int count
      1 int all
      1 dma_addr_t dma_handle
      1 dma_addr_t *dma_handle
      1 char *app_name
