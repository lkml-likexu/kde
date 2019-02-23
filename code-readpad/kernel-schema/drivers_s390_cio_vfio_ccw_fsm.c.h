
\n
static int fsm_io_helper(struct vfio_ccw_private *private)
static void fsm_notoper(struct vfio_ccw_private *private, enum vfio_ccw_event event)
static void fsm_nop(struct vfio_ccw_private *private, enum vfio_ccw_event event)
static void fsm_io_error(struct vfio_ccw_private *private, enum vfio_ccw_event event)
static void fsm_io_busy(struct vfio_ccw_private *private, enum vfio_ccw_event event)
static void fsm_disabled_irq(struct vfio_ccw_private *private, enum vfio_ccw_event event)
cio_disable_subchannel(sch)
; } inline struct subchannel_id get_schid(struct vfio_ccw_private *p)
static void fsm_io_request(struct vfio_ccw_private *private, enum vfio_ccw_event event)
static void fsm_irq(struct vfio_ccw_private *private, enum vfio_ccw_event event)
\n
      8 struct vfio_ccw_private *private
      7 enum vfio_ccw_event event
      1 struct vfio_ccw_private *p
      1 sch
