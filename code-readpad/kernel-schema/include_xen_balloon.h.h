
\n
struct device; extern int register_xen_selfballooning(struct device *dev)
; static inline int register_xen_selfballooning(struct device *dev)
void xen_balloon_init(void)
; static inline void xen_balloon_init(void)
\n
      2 void
      2 struct device *dev
