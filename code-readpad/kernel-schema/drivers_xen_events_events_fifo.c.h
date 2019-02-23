
\n
static inline event_word_t *event_word_from_port(unsigned port)
static unsigned evtchn_fifo_max_channels(void)
static unsigned evtchn_fifo_nr_channels(void)
static int init_control_block(int cpu, struct evtchn_fifo_control_block *control_block)
static void free_unused_array_pages(void)
static void init_array_page(event_word_t *array_page)
static int evtchn_fifo_setup(struct irq_info *info)
static void evtchn_fifo_bind_to_cpu(struct irq_info *info, unsigned cpu)
static void evtchn_fifo_clear_pending(unsigned port)
static void evtchn_fifo_set_pending(unsigned port)
static bool evtchn_fifo_is_pending(unsigned port)
static bool evtchn_fifo_test_and_set_mask(unsigned port)
static void evtchn_fifo_mask(unsigned port)
static bool evtchn_fifo_is_masked(unsigned port)
static bool evtchn_fifo_is_masked(unsigned port)
event_word_t *word = event_word_from_port(port)
;return sync_test_bit(EVTCHN_FIFO_BIT(MASKED, word)
, BM(word)
)
; }static void clear_masked(volatile event_word_t *word)
static void evtchn_fifo_unmask(unsigned port)
static uint32_t clear_linked(volatile event_word_t *word)
static void handle_irq_for_port(unsigned port)
static void consume_one_event(unsigned cpu, struct evtchn_fifo_control_block *control_block, unsigned priority, unsigned long *ready, bool drop)
static void __evtchn_fifo_handle_events(unsigned cpu, bool drop)
static void evtchn_fifo_handle_events(unsigned cpu)
static void evtchn_fifo_resume(void)
static int evtchn_fifo_alloc_control_block(unsigned cpu)
static int xen_evtchn_cpu_prepare(unsigned int cpu)
static int xen_evtchn_cpu_dead(unsigned int cpu)
int __init xen_evtchn_fifo_init(void)
\n
     10 unsigned port
      5 void
      5 unsigned cpu
      2 word
      2 volatile event_word_t *word
      2 unsigned int cpu
      2 struct irq_info *info
      2 struct evtchn_fifo_control_block *control_block
      2 bool drop
      1 unsigned priority
      1 unsigned long *ready
      1 port
      1 int cpu
      1 EVTCHN_FIFO_BITMASKED
      1 event_word_t *array_page
