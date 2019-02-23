
\n
static inline int __stsch(struct subchannel_id schid, struct schib *addr)
int stsch(struct subchannel_id schid, struct schib *addr)
static inline int __msch(struct subchannel_id schid, struct schib *addr)
int msch(struct subchannel_id schid, struct schib *addr)
static inline int __tsch(struct subchannel_id schid, struct irb *addr)
int tsch(struct subchannel_id schid, struct irb *addr)
static inline int __ssch(struct subchannel_id schid, union orb *addr)
int ssch(struct subchannel_id schid, union orb *addr)
static inline int __csch(struct subchannel_id schid)
int csch(struct subchannel_id schid)
int tpi(struct tpi_info *addr)
int chsc(void *chsc_area)
static inline int __rsch(struct subchannel_id schid)
int rsch(struct subchannel_id schid)
static inline int __hsch(struct subchannel_id schid)
int hsch(struct subchannel_id schid)
static inline int __xsch(struct subchannel_id schid)
int xsch(struct subchannel_id schid)
int stcrw(struct crw *crw)
\n
     16 struct subchannel_id schid
      4 struct schib *addr
      2 union orb *addr
      2 struct irb *addr
      1 void *chsc_area
      1 struct tpi_info *addr
      1 struct crw *crw
