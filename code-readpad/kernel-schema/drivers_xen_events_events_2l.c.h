
\n
static unsigned evtchn_2l_max_channels(void)
static void evtchn_2l_bind_to_cpu(struct irq_info *info, unsigned cpu)
static void evtchn_2l_clear_pending(unsigned port)
static void evtchn_2l_set_pending(unsigned port)
static bool evtchn_2l_is_pending(unsigned port)
static bool evtchn_2l_test_and_set_mask(unsigned port)
static void evtchn_2l_mask(unsigned port)
static void evtchn_2l_unmask(unsigned port)
static inline xen_ulong_t active_evtchns(unsigned int cpu, struct shared_info *sh, unsigned int idx)
static void evtchn_2l_handle_events(unsigned cpu)
irqreturn_t xen_debug_interrupt(int irq, void *dev_id)
static void evtchn_2l_resume(void)
void __init xen_evtchn_2l_init(void)
\n
      6 unsigned port
      3 void
      2 unsigned cpu
      1 void *dev_id
      1 unsigned int idx
      1 unsigned int cpu
      1 struct shared_info *sh
      1 struct irq_info *info
      1 int irq
