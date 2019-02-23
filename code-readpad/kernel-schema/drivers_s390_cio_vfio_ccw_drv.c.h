
\n
int vfio_ccw_sch_quiesce(struct subchannel *sch)
static void vfio_ccw_sch_io_todo(struct work_struct *work)
static void vfio_ccw_sch_irq(struct subchannel *sch)
static int vfio_ccw_sch_probe(struct subchannel *sch)
static int vfio_ccw_sch_remove(struct subchannel *sch)
static void vfio_ccw_sch_shutdown(struct subchannel *sch)
static int vfio_ccw_sch_event(struct subchannel *sch, int process)
static int __init vfio_ccw_sch_init(void)
static void __exit vfio_ccw_sch_exit(void)
\n
      6 struct subchannel *sch
      2 void
      1 struct work_struct *work
      1 int process
