
static void pic_lock(struct kvm_pic *s)
__acquires(&s->lock)
static void pic_unlock(struct kvm_pic *s)
__releases(&s->lock)
static void pic_clear_isr(struct kvm_kpic_state *s, int irq)
static inline int pic_set_irq1(struct kvm_kpic_state *s, int irq, int level)
static inline int get_priority(struct kvm_kpic_state *s, int mask)
static int pic_get_irq(struct kvm_kpic_state *s)
static void pic_update_irq(struct kvm_pic *s)
void kvm_pic_update_irq(struct kvm_pic *s)
int kvm_pic_set_irq(struct kvm_pic *s, int irq, int irq_source_id, int level)
void kvm_pic_clear_all(struct kvm_pic *s, int irq_source_id)
static inline void pic_intack(struct kvm_kpic_state *s, int irq)
int kvm_pic_read_irq(struct kvm *kvm)
static void kvm_pic_reset(struct kvm_kpic_state *s)
static void pic_ioport_write(void *opaque, u32 addr, u32 val)
static u32 pic_poll_read(struct kvm_kpic_state *s, u32 addr1)
static u32 pic_ioport_read(void *opaque, u32 addr)
static void elcr_ioport_write(void *opaque, u32 addr, u32 val)
static u32 elcr_ioport_read(void *opaque, u32 addr1)
static int picdev_write(struct kvm_pic *s, gpa_t addr, int len, const void *val)
static int picdev_read(struct kvm_pic *s, gpa_t addr, int len, void *val)
static int picdev_master_write(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, const void *val)
static int picdev_master_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, void *val)
static int picdev_slave_write(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, const void *val)
static int picdev_slave_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, void *val)
static int picdev_eclr_write(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, const void *val)
static int picdev_eclr_read(struct kvm_vcpu *vcpu, struct kvm_io_device *dev, gpa_t addr, int len, void *val)
static void pic_irq_request(struct kvm *kvm, int level)
int kvm_pic_init(struct kvm *kvm)
void kvm_pic_destroy(struct kvm *kvm)
   8 struct kvm_pic *s
   8 int len
   8 gpa_t addr
   7 struct kvm_kpic_state *s
   6 struct kvm_vcpu *vcpu
   6 struct kvm_io_device *dev
   4 void *val
   4 void *opaque
   4 struct kvm *kvm
   4 int irq
   4 const void *val
   3 u32 addr
   3 int level
   2 u32 val
   2 u32 addr1
   2 int irq_source_id
   2 &s->lock
   1 int mask
