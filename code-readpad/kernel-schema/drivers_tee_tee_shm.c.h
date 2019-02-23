
EXPORT_SYMBOL_GPL(tee_shm_alloc);
EXPORT_SYMBOL_GPL(tee_shm_priv_alloc);
EXPORT_SYMBOL_GPL(tee_shm_register);
EXPORT_SYMBOL_GPL(tee_shm_free);
EXPORT_SYMBOL_GPL(tee_shm_va2pa);
EXPORT_SYMBOL_GPL(tee_shm_pa2va);
EXPORT_SYMBOL_GPL(tee_shm_get_va);
EXPORT_SYMBOL_GPL(tee_shm_get_pa);
EXPORT_SYMBOL_GPL(tee_shm_get_from_id);
EXPORT_SYMBOL_GPL(tee_shm_put);
\n
static void tee_shm_release(struct tee_shm *shm)
static struct sg_table *tee_shm_op_map_dma_buf(struct dma_buf_attachment*attach, enum dma_data_direction dir)
static void tee_shm_op_unmap_dma_buf(struct dma_buf_attachment *attach, struct sg_table *table, enum dma_data_direction dir)
static void tee_shm_op_release(struct dma_buf *dmabuf)
static void *tee_shm_op_map(struct dma_buf *dmabuf, unsigned long pgnum)
static int tee_shm_op_mmap(struct dma_buf *dmabuf, struct vm_area_struct *vma)
static struct tee_shm *__tee_shm_alloc(struct tee_context *ctx, struct tee_device *teedev, size_t size, u32 flags)
struct tee_shm *tee_shm_alloc(struct tee_context *ctx, size_t size, u32 flags)
struct tee_shm *tee_shm_priv_alloc(struct tee_device *teedev, size_t size)
struct tee_shm *tee_shm_register(struct tee_context *ctx, unsigned long addr, size_t length, u32 flags)
int tee_shm_get_fd(struct tee_shm *shm)
void tee_shm_free(struct tee_shm *shm)
int tee_shm_va2pa(struct tee_shm *shm, void *va, phys_addr_t *pa)
int tee_shm_pa2va(struct tee_shm *shm, phys_addr_t pa, void **va)
void *tee_shm_get_va(struct tee_shm *shm, size_t offs)
int tee_shm_get_pa(struct tee_shm *shm, size_t offs, phys_addr_t *pa)
struct tee_shm *tee_shm_get_from_id(struct tee_context *ctx, int id)
void tee_shm_put(struct tee_shm *shm)
\n
      8 struct tee_shm *shm
      4 struct tee_context *ctx
      3 u32 flags
      3 struct dma_buf *dmabuf
      3 size_t size
      2 struct tee_device *teedev
      2 size_t offs
      2 phys_addr_t *pa
      2 enum dma_data_direction dir
      1 void **va
      1 void *va
      1 unsigned long pgnum
      1 unsigned long addr
      1 tee_shm_va2pa
      1 tee_shm_register
      1 tee_shm_put
      1 tee_shm_priv_alloc
      1 tee_shm_pa2va
      1 tee_shm_get_va
      1 tee_shm_get_pa
      1 tee_shm_get_from_id
      1 tee_shm_free
      1 tee_shm_alloc
      1 struct vm_area_struct *vma
      1 struct sg_table *table
      1 struct dma_buf_attachment*attach
      1 struct dma_buf_attachment *attach
      1 size_t length
      1 phys_addr_t pa
      1 int id
