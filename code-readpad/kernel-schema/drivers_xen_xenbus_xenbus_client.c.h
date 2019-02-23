
EXPORT_SYMBOL_GPL(xenbus_strstate);
EXPORT_SYMBOL_GPL(xenbus_watch_path);
EXPORT_SYMBOL_GPL(xenbus_watch_pathfmt);
EXPORT_SYMBOL_GPL(xenbus_switch_state);
EXPORT_SYMBOL_GPL(xenbus_frontend_closed);
EXPORT_SYMBOL_GPL(xenbus_dev_error);
EXPORT_SYMBOL_GPL(xenbus_dev_fatal);
EXPORT_SYMBOL_GPL(xenbus_grant_ring);
EXPORT_SYMBOL_GPL(xenbus_alloc_evtchn);
EXPORT_SYMBOL_GPL(xenbus_free_evtchn);
EXPORT_SYMBOL_GPL(xenbus_map_ring_valloc);
EXPORT_SYMBOL_GPL(xenbus_map_ring);
EXPORT_SYMBOL_GPL(xenbus_unmap_ring_vfree);
EXPORT_SYMBOL_GPL(xenbus_unmap_ring);
EXPORT_SYMBOL_GPL(xenbus_read_driver_state);
\n
const char *xenbus_strstate(enum xenbus_state state)
int xenbus_watch_path(struct xenbus_device *dev, const char *path, struct xenbus_watch *watch, void (*callback)
(struct xenbus_watch *, const char *, const char *)
)
int xenbus_watch_pathfmt(struct xenbus_device *dev, struct xenbus_watch *watch, void (*callback)
(struct xenbus_watch *, const char *, const char *)
, const char *pathfmt, ...)
static int __xenbus_switch_state(struct xenbus_device *dev, enum xenbus_state state, int depth)
int xenbus_switch_state(struct xenbus_device *dev, enum xenbus_state state)
int xenbus_frontend_closed(struct xenbus_device *dev)
static void xenbus_va_dev_error(struct xenbus_device *dev, int err, const char *fmt, va_list ap)
void xenbus_dev_error(struct xenbus_device *dev, int err, const char *fmt, ...)
void xenbus_dev_fatal(struct xenbus_device *dev, int err, const char *fmt, ...)
static void xenbus_switch_fatal(struct xenbus_device *dev, int depth, int err, const char *fmt, ...)
int xenbus_grant_ring(struct xenbus_device *dev, void *vaddr, unsigned int nr_pages, grant_ref_t *grefs)
int xenbus_alloc_evtchn(struct xenbus_device *dev, int *port)
int xenbus_free_evtchn(struct xenbus_device *dev, int port)
int xenbus_map_ring_valloc(struct xenbus_device *dev, grant_ref_t *gnt_refs, unsigned int nr_grefs, void **vaddr)
static int __xenbus_map_ring(struct xenbus_device *dev, grant_ref_t *gnt_refs, unsigned int nr_grefs, grant_handle_t *handles, phys_addr_t *addrs, unsigned int flags, bool *leaked)
struct map_ring_valloc_hvm static void xenbus_map_ring_setup_grant_hvm(unsigned long gfn, unsigned int goffset, unsigned int len, void *data)
static int xenbus_map_ring_valloc_hvm(struct xenbus_device *dev, grant_ref_t *gnt_ref, unsigned int nr_grefs, void **vaddr)
int xenbus_map_ring(struct xenbus_device *dev, grant_ref_t *gnt_refs, unsigned int nr_grefs, grant_handle_t *handles, unsigned long *vaddrs, bool *leaked)
int xenbus_unmap_ring_vfree(struct xenbus_device *dev, void *vaddr)
static int xenbus_map_ring_valloc_pv(struct xenbus_device *dev, grant_ref_t *gnt_refs, unsigned int nr_grefs, void **vaddr)
static int xenbus_unmap_ring_vfree_pv(struct xenbus_device *dev, void *vaddr)
struct unmap_ring_vfree_hvm static void xenbus_unmap_ring_setup_grant_hvm(unsigned long gfn, unsigned int goffset, unsigned int len, void *data)
static int xenbus_unmap_ring_vfree_hvm(struct xenbus_device *dev, void *vaddr)
int xenbus_unmap_ring(struct xenbus_device *dev, grant_handle_t *handles, unsigned int nr_handles, unsigned long *vaddrs)
enum xenbus_state xenbus_read_driver_state(const char *path)
void __init xenbus_ring_ops_init(void)
\n
     21 struct xenbus_device *dev
      5 unsigned int nr_grefs
      4 void *vaddr
      4 int err
      4 grant_ref_t *gnt_refs
      4 const char *fmt
      4 const char *
      3 void **vaddr
      3 grant_handle_t *handles
      3 enum xenbus_state state
      3 ...
      2 void *data
      2 void *callback
      2 unsigned long *vaddrs
      2 unsigned long gfn
      2 unsigned int len
      2 unsigned int goffset
      2 struct xenbus_watch *watch
      2 struct xenbus_watch *
      2 int depth
      2 const char *path
      2 bool *leaked
      1 xenbus_watch_pathfmt
      1 xenbus_watch_path
      1 xenbus_unmap_ring_vfree
      1 xenbus_unmap_ring
      1 xenbus_switch_state
      1 xenbus_strstate
      1 xenbus_read_driver_state
      1 xenbus_map_ring_valloc
      1 xenbus_map_ring
      1 xenbus_grant_ring
      1 xenbus_frontend_closed
      1 xenbus_free_evtchn
      1 xenbus_dev_fatal
      1 xenbus_dev_error
      1 xenbus_alloc_evtchn
      1 void
      1 va_list ap
      1 unsigned int nr_pages
      1 unsigned int nr_handles
      1 unsigned int flags
      1 phys_addr_t *addrs
      1 int *port
      1 int port
      1 grant_ref_t *grefs
      1 grant_ref_t *gnt_ref
