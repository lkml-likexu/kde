
\n
static cycles_t numachip2_timer_read(struct clocksource *cs)
static int numachip2_set_next_event(unsigned long delta, struct clock_event_device *ced)
static void numachip_timer_interrupt(void)
static __init void numachip_timer_each(struct work_struct *work)
static int __init numachip_timer_init(void)
\n
      2 void
      1 unsigned long delta
      1 struct work_struct *work
      1 struct clocksource *cs
      1 struct clock_event_device *ced
