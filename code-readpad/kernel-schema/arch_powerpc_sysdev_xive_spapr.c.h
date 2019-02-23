
\n
static int xive_irq_bitmap_add(int base, int count)
static int __xive_irq_bitmap_alloc(struct xive_irq_bitmap *xibm)
static int xive_irq_bitmap_alloc(void)
static void xive_irq_bitmap_free(int irq)
static unsigned int plpar_busy_delay_time(long rc)
static unsigned int plpar_busy_delay(int rc)
static long plpar_int_reset(unsigned long flags)
static long plpar_int_get_source_info(unsigned long flags, unsigned long lisn, unsigned long *src_flags, unsigned long *eoi_page, unsigned long *trig_page, unsigned long *esb_shift)
static long plpar_int_set_source_config(unsigned long flags, unsigned long lisn, unsigned long target, unsigned long prio, unsigned long sw_irq)
static long plpar_int_get_queue_info(unsigned long flags, unsigned long target, unsigned long priority, unsigned long *esn_page, unsigned long *esn_size)
static long plpar_int_set_queue_config(unsigned long flags, unsigned long target, unsigned long priority, unsigned long qpage, unsigned long qsize)
static long plpar_int_sync(unsigned long flags, unsigned long lisn)
static long plpar_int_esb(unsigned long flags, unsigned long lisn, unsigned long offset, unsigned long in_data, unsigned long *out_data)
static u64 xive_spapr_esb_rw(u32 lisn, u32 offset, u64 data, bool write)
static int xive_spapr_populate_irq_data(u32 hw_irq, struct xive_irq_data *data)
static int xive_spapr_configure_irq(u32 hw_irq, u32 target, u8 prio, u32 sw_irq)
static int xive_spapr_configure_queue(u32 target, struct xive_q *q, u8 prio, __be32 *qpage, u32 order)
static int xive_spapr_setup_queue(unsigned int cpu, struct xive_cpu *xc, u8 prio)
static void xive_spapr_cleanup_queue(unsigned int cpu, struct xive_cpu *xc, u8 prio)
static bool xive_spapr_match(struct device_node *node)
static int xive_spapr_get_ipi(unsigned int cpu, struct xive_cpu *xc)
static void xive_spapr_put_ipi(unsigned int cpu, struct xive_cpu *xc)
static void xive_spapr_shutdown(void)
static void xive_spapr_update_pending(struct xive_cpu *xc)
static void xive_spapr_eoi(u32 hw_irq)
static void xive_spapr_setup_cpu(unsigned int cpu, struct xive_cpu *xc)
static void xive_spapr_teardown_cpu(unsigned int cpu, struct xive_cpu *xc)
static void xive_spapr_sync_source(u32 hw_irq)
static bool xive_get_max_prio(u8 *max_prio)
bool __init xive_spapr_init(void)
\n
      7 unsigned long flags
      7 struct xive_cpu *xc
      6 unsigned int cpu
      4 unsigned long lisn
      4 u8 prio
      4 u32 hw_irq
      3 void
      3 unsigned long target
      2 unsigned long priority
      2 u32 target
      1 unsigned long *trig_page
      1 unsigned long sw_irq
      1 unsigned long *src_flags
      1 unsigned long qsize
      1 unsigned long qpage
      1 unsigned long prio
      1 unsigned long *out_data
      1 unsigned long offset
      1 unsigned long in_data
      1 unsigned long *esn_size
      1 unsigned long *esn_page
      1 unsigned long *esb_shift
      1 unsigned long *eoi_page
      1 u8 *max_prio
      1 u64 data
      1 u32 sw_irq
      1 u32 order
      1 u32 offset
      1 u32 lisn
      1 struct xive_q *q
      1 struct xive_irq_data *data
      1 struct xive_irq_bitmap *xibm
      1 struct device_node *node
      1 long rc
      1 int rc
      1 int irq
      1 int count
      1 int base
      1 bool write
      1 __be32 *qpage
