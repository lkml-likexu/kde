
\n
static inline sccb_mask_t sccb_get_mask(u8 *masks, size_t len, int i)
static inline void sccb_set_mask(u8 *masks, size_t len, int i, sccb_mask_t val)
static inline void sclp_fill_core_info(struct sclp_core_info *info, struct read_cpu_info_sccb *sccb)
static inline int sclp_service_call(sclp_cmdw_t command, void *sccb)
static inline unsigned char sclp_ascebc(unsigned char ch)
static inline void sclp_ebcasc_str(unsigned char *str, int nr)
static inline void sclp_ascebc_str(unsigned char *str, int nr)
static inline struct gds_vector * sclp_find_gds_vector(void *start, void *end, u16 id)
static inline struct gds_subvector * sclp_find_gds_subvector(void *start, void *end, u8 key)
\n
      2 void *start
      2 void *end
      2 unsigned char *str
      2 u8 *masks
      2 size_t len
      2 int nr
      2 int i
      1 void *sccb
      1 unsigned char ch
      1 u8 key
      1 u16 id
      1 struct sclp_core_info *info
      1 struct read_cpu_info_sccb *sccb
      1 sclp_cmdw_t command
      1 sccb_mask_t val
