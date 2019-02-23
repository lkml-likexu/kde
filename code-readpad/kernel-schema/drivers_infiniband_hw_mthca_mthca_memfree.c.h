
\n
static void mthca_free_icm_pages(struct mthca_dev *dev, struct mthca_icm_chunk *chunk)
static void mthca_free_icm_coherent(struct mthca_dev *dev, struct mthca_icm_chunk *chunk)
void mthca_free_icm(struct mthca_dev *dev, struct mthca_icm *icm, int coherent)
static int mthca_alloc_icm_pages(struct scatterlist *mem, int order, gfp_t gfp_mask)
static int mthca_alloc_icm_coherent(struct device *dev, struct scatterlist *mem, int order, gfp_t gfp_mask)
struct mthca_icm *mthca_alloc_icm(struct mthca_dev *dev, int npages, gfp_t gfp_mask, int coherent)
int mthca_table_get(struct mthca_dev *dev, struct mthca_icm_table *table, int obj)
void mthca_table_put(struct mthca_dev *dev, struct mthca_icm_table *table, int obj)
void *mthca_table_find(struct mthca_icm_table *table, int obj, dma_addr_t *dma_handle)
int mthca_table_get_range(struct mthca_dev *dev, struct mthca_icm_table *table, int start, int end)
void mthca_table_put_range(struct mthca_dev *dev, struct mthca_icm_table *table, int start, int end)
struct mthca_icm_table *mthca_alloc_icm_table(struct mthca_dev *dev, u64 virt, int obj_size, int nobj, int reserved, int use_lowmem, int use_coherent)
void mthca_free_icm_table(struct mthca_dev *dev, struct mthca_icm_table *table)
static u64 mthca_uarc_virt(struct mthca_dev *dev, struct mthca_uar *uar, int page)
int mthca_map_user_db(struct mthca_dev *dev, struct mthca_uar *uar, struct mthca_user_db_table *db_tab, int index, u64 uaddr)
void mthca_unmap_user_db(struct mthca_dev *dev, struct mthca_uar *uar, struct mthca_user_db_table *db_tab, int index)
struct mthca_user_db_table *mthca_init_user_db_tab(struct mthca_dev *dev)
void mthca_cleanup_user_db_tab(struct mthca_dev *dev, struct mthca_uar *uar, struct mthca_user_db_table *db_tab)
int mthca_alloc_db(struct mthca_dev *dev, enum mthca_db_type type, u32 qn, __be32 **db)
void mthca_free_db(struct mthca_dev *dev, int type, int db_index)
int mthca_init_db_tab(struct mthca_dev *dev)
void mthca_cleanup_db_tab(struct mthca_dev *dev)
\n
     19 struct mthca_dev *dev
      6 struct mthca_icm_table *table
      4 struct mthca_uar *uar
      3 struct mthca_user_db_table *db_tab
      3 int obj
      3 gfp_t gfp_mask
      2 struct scatterlist *mem
      2 struct mthca_icm_chunk *chunk
      2 int start
      2 int order
      2 int index
      2 int end
      2 int coherent
      1 u64 virt
      1 u64 uaddr
      1 u32 qn
      1 struct mthca_icm *icm
      1 struct device *dev
      1 int use_lowmem
      1 int use_coherent
      1 int type
      1 int reserved
      1 int page
      1 int obj_size
      1 int npages
      1 int nobj
      1 int db_index
      1 enum mthca_db_type type
      1 dma_addr_t *dma_handle
      1 __be32 **db
