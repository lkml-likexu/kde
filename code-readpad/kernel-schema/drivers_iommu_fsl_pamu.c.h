
\n
u32 pamu_get_max_subwin_cnt(void)
static struct paace *pamu_get_ppaace(int liodn)
int pamu_enable_liodn(int liodn)
int pamu_disable_liodn(int liodn)
static unsigned int map_addrspace_size_to_wse(phys_addr_t addrspace_size)
static unsigned int map_subwindow_cnt_to_wce(u32 subwindow_cnt)
static void pamu_init_ppaace(struct paace *ppaace)
static void pamu_init_spaace(struct paace *spaace)
static struct paace *pamu_get_spaace(struct paace *paace, u32 wnum)
static unsigned long pamu_get_fspi_and_allocate(u32 subwin_cnt)
void pamu_free_subwins(int liodn)
intpamu_update_paace_stash(int liodn, u32 subwin, u32 value)
int pamu_disable_spaace(int liodn, u32 subwin)
int pamu_config_ppaace(int liodn, phys_addr_t win_addr, phys_addr_t win_size, u32 omi, unsigned long rpn, u32 snoopid, u32 stashid, u32 subwin_cnt, int prot)
int pamu_config_spaace(int liodn, u32 subwin_cnt, u32 subwin, phys_addr_t subwin_size, u32 omi, unsigned long rpn, u32 snoopid, u32 stashid, int enable, int prot)
void get_ome_index(u32 *omi_index, struct device *dev)
u32 get_stash_id(u32 stash_dest_hint, u32 vcpu)
static void setup_qbman_paace(struct paace *ppaace, intpaace_type)
static void setup_omt(struct ome *omt)
static void get_pamu_cap_values(unsigned long pamu_reg_base)
static int setup_one_pamu(unsigned long pamu_reg_base, unsigned long pamu_reg_size, phys_addr_t ppaact_phys, phys_addr_t spaact_phys, phys_addr_t omt_phys)
static void setup_liodns(void)
static irqreturn_t pamu_av_isr(int irq, void *arg)
static int create_csd(phys_addr_t phys, size_t size, u32 csd_port_id)
static int fsl_pamu_probe(struct platform_device *pdev)
static __init int fsl_pamu_init(void)
\n
      8 int liodn
      3 void
      3 u32 subwin_cnt
      3 u32 subwin
      2 unsigned long rpn
      2 unsigned long pamu_reg_base
      2 u32 stashid
      2 u32 snoopid
      2 u32 omi
      2 struct paace *ppaace
      2 int prot
      1 void *arg
      1 unsigned long pamu_reg_size
      1 u32 wnum
      1 u32 vcpu
      1 u32 value
      1 u32 subwindow_cnt
      1 u32 stash_dest_hint
      1 u32 *omi_index
      1 u32 csd_port_id
      1 struct platform_device *pdev
      1 struct paace *spaace
      1 struct paace *paace
      1 struct ome *omt
      1 struct device *dev
      1 size_t size
      1 phys_addr_t win_size
      1 phys_addr_t win_addr
      1 phys_addr_t subwin_size
      1 phys_addr_t spaact_phys
      1 phys_addr_t ppaact_phys
      1 phys_addr_t phys
      1 phys_addr_t omt_phys
      1 phys_addr_t addrspace_size
      1 intpaace_type
      1 int irq
      1 int enable
