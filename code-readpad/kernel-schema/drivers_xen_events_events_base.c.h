
EXPORT_SYMBOL_GPL(irq_from_evtchn);
EXPORT_SYMBOL_GPL(notify_remote_via_irq);
EXPORT_SYMBOL_GPL(xen_irq_from_gsi);
EXPORT_SYMBOL_GPL(xen_pirq_from_irq);
EXPORT_SYMBOL_GPL(bind_evtchn_to_irq);
EXPORT_SYMBOL_GPL(bind_interdomain_evtchn_to_irq);
EXPORT_SYMBOL_GPL(xen_evtchn_nr_channels);
EXPORT_SYMBOL_GPL(bind_evtchn_to_irqhandler);
EXPORT_SYMBOL_GPL(bind_interdomain_evtchn_to_irqhandler);
EXPORT_SYMBOL_GPL(bind_virq_to_irqhandler);
EXPORT_SYMBOL_GPL(unbind_from_irqhandler);
EXPORT_SYMBOL_GPL(xen_set_irq_priority);
EXPORT_SYMBOL_GPL(evtchn_make_refcounted);
EXPORT_SYMBOL_GPL(evtchn_get);
EXPORT_SYMBOL_GPL(evtchn_put);
EXPORT_SYMBOL_GPL(xen_hvm_evtchn_do_upcall);
EXPORT_SYMBOL_GPL(xen_rebind_evtchn_to_cpu);
EXPORT_SYMBOL_GPL(xen_test_irq_shared);
EXPORT_SYMBOL_GPL(xen_set_callback_via);
\n
static void clear_evtchn_to_irq_row(unsigned row)
static void clear_evtchn_to_irq_all(void)
static int set_evtchn_to_irq(unsigned evtchn, unsigned irq)
int get_evtchn_to_irq(unsigned evtchn)
struct irq_info *info_for_irq(unsigned irq)
static int xen_irq_info_common_setup(struct irq_info *info, unsigned irq, enum xen_irq_type type, unsigned evtchn, unsigned short cpu)
static int xen_irq_info_evtchn_setup(unsigned irq, unsigned evtchn)
static int xen_irq_info_ipi_setup(unsigned cpu, unsigned irq, unsigned evtchn, enum ipi_vector ipi)
static int xen_irq_info_virq_setup(unsigned cpu, unsigned irq, unsigned evtchn, unsigned virq)
static int xen_irq_info_pirq_setup(unsigned irq, unsigned evtchn, unsigned pirq, unsigned gsi, uint16_t domid, unsigned char flags)
static void xen_irq_info_cleanup(struct irq_info *info)
unsigned int evtchn_from_irq(unsigned irq)
unsigned irq_from_evtchn(unsigned int evtchn)
int irq_from_virq(unsigned int cpu, unsigned int virq)
static enum ipi_vector ipi_from_irq(unsigned irq)
static unsigned virq_from_irq(unsigned irq)
static unsigned pirq_from_irq(unsigned irq)
static enum xen_irq_type type_from_irq(unsigned irq)
unsigned cpu_from_irq(unsigned irq)
unsigned int cpu_from_evtchn(unsigned int evtchn)
static bool pirq_check_eoi_map(unsigned irq)
static bool pirq_needs_eoi_flag(unsigned irq)
static void bind_evtchn_to_cpu(unsigned int chn, unsigned int cpu)
void notify_remote_via_irq(int irq)
static void xen_irq_init(unsigned irq)
static int __must_check xen_allocate_irqs_dynamic(int nvec)
static inline int __must_check xen_allocate_irq_dynamic(void)
static int __must_check xen_allocate_irq_gsi(unsigned gsi)
static void xen_free_irq(unsigned irq)
static void xen_evtchn_close(unsigned int port)
static void pirq_query_unmask(int irq)
static void eoi_pirq(struct irq_data *data)
static void mask_ack_pirq(struct irq_data *data)
static unsigned int __startup_pirq(unsigned int irq)
static unsigned int startup_pirq(struct irq_data *data)
static void shutdown_pirq(struct irq_data *data)
static void enable_pirq(struct irq_data *data)
static void disable_pirq(struct irq_data *data)
int xen_irq_from_gsi(unsigned gsi)
static void __unbind_from_irq(unsigned int irq)
int xen_bind_pirq_gsi_to_irq(unsigned gsi, unsigned pirq, int shareable, char *name)
int xen_allocate_pirq_msi(struct pci_dev *dev, struct msi_desc *msidesc)
int xen_bind_pirq_msi_to_irq(struct pci_dev *dev, struct msi_desc *msidesc, int pirq, int nvec, const char *name, domid_t domid)
int xen_destroy_irq(int irq)
int xen_irq_from_pirq(unsigned pirq)
int xen_pirq_from_irq(unsigned irq)
int bind_evtchn_to_irq(unsigned int evtchn)
static int bind_ipi_to_irq(unsigned int ipi, unsigned int cpu)
int bind_interdomain_evtchn_to_irq(unsigned int remote_domain, unsigned int remote_port)
static int find_virq(unsigned int virq, unsigned int cpu)
unsigned xen_evtchn_nr_channels(void)
int bind_virq_to_irq(unsigned int virq, unsigned int cpu, bool percpu)
static void unbind_from_irq(unsigned int irq)
int bind_evtchn_to_irqhandler(unsigned int evtchn, irq_handler_t handler, unsigned long irqflags, const char *devname, void *dev_id)
int bind_interdomain_evtchn_to_irqhandler(unsigned int remote_domain, unsigned int remote_port, irq_handler_t handler, unsigned long irqflags, const char *devname, void *dev_id)
int bind_virq_to_irqhandler(unsigned int virq, unsigned int cpu, irq_handler_t handler, unsigned long irqflags, const char *devname, void *dev_id)
int bind_ipi_to_irqhandler(enum ipi_vector ipi, unsigned int cpu, irq_handler_t handler, unsigned long irqflags, const char *devname, void *dev_id)
void unbind_from_irqhandler(unsigned int irq, void *dev_id)
int xen_set_irq_priority(unsigned irq, unsigned priority)
int evtchn_make_refcounted(unsigned int evtchn)
int evtchn_get(unsigned int evtchn)
void evtchn_put(unsigned int evtchn)
void xen_send_IPI_one(unsigned int cpu, enum ipi_vector vector)
static void __xen_evtchn_do_upcall(void)
void xen_evtchn_do_upcall(struct pt_regs *regs)
void xen_hvm_evtchn_do_upcall(void)
void rebind_evtchn_irq(int evtchn, int irq)
int xen_rebind_evtchn_to_cpu(int evtchn, unsigned tcpu)
static int set_affinity_irq(struct irq_data *data, const struct cpumask *dest, bool force)
static void enable_dynirq(struct irq_data *data)
static void disable_dynirq(struct irq_data *data)
static void ack_dynirq(struct irq_data *data)
static void mask_ack_dynirq(struct irq_data *data)
static int retrigger_dynirq(struct irq_data *data)
static void restore_pirqs(void)
static void restore_cpu_virqs(unsigned int cpu)
static void restore_cpu_ipis(unsigned int cpu)
void xen_clear_irq_pending(int irq)
if (VALID_EVTCHN(evtchn)
)
clear_evtchn(evtchn)
; } EXPORT_SYMBOL(xen_clear_irq_pending)
; void xen_set_irq_pending(int irq)
bool xen_test_irq_pending(int irq)
void xen_poll_irq_timeout(int irq, u64 timeout)
if (HYPERVISOR_sched_op(SCHEDOP_poll, &poll)
!= 0)
BUG()
;} } EXPORT_SYMBOL(xen_poll_irq_timeout)
;void xen_poll_irq(int irq)
int xen_test_irq_shared(int irq)
void xen_irq_resume(void)
int xen_set_callback_via(uint64_t via)
void xen_callback_vector(void)
void __init xen_init_IRQ(void)
\n
     19 unsigned irq
     12 struct irq_data *data
     10 unsigned int cpu
     10 int irq
      9 void
      7 unsigned int evtchn
      7 unsigned evtchn
      5 void *dev_id
      4 unsigned long irqflags
      4 unsigned int virq
      4 unsigned int irq
      4 unsigned gsi
      4 irq_handler_t handler
      4 const char *devname
      3 unsigned pirq
      2 unsigned int remote_port
      2 unsigned int remote_domain
      2 unsigned cpu
      2 struct pci_dev *dev
      2 struct msi_desc *msidesc
      2 struct irq_info *info
      2 int nvec
      2 int evtchn
      2 enum ipi_vector ipi
      1 xen_test_irq_shared
      1 xen_set_irq_priority
      1 xen_set_callback_via
      1 xen_rebind_evtchn_to_cpu
      1 xen_poll_irq_timeout
      1 xen_pirq_from_irq
      1 xen_irq_from_gsi
      1 xen_hvm_evtchn_do_upcall
      1 xen_evtchn_nr_channels
      1 xen_clear_irq_pending
      1 VALID_EVTCHNevtchn
      1 unsigned virq
      1 unsigned tcpu
      1 unsigned short cpu
      1 unsigned row
      1 unsigned priority
      1 unsigned int port
      1 unsigned int ipi
      1 unsigned int chn
      1 unsigned char flags
      1 unbind_from_irqhandler
      1 uint64_t via
      1 uint16_t domid
      1 u64 timeout
      1 struct pt_regs *regs
      1 &poll
      1 notify_remote_via_irq
      1 irq_from_evtchn
      1 int shareable
      1 int pirq
      1 HYPERVISOR_sched_opSCHEDOP_poll
      1 evtchn_put
      1 evtchn_make_refcounted
      1 evtchn_get
      1 evtchn
      1 enum xen_irq_type type
      1 enum ipi_vector vector
      1 domid_t domid
      1 const struct cpumask *dest
      1 const char *name
      1 char *name
      1 bool percpu
      1 bool force
      1 bind_virq_to_irqhandler
      1 bind_interdomain_evtchn_to_irqhandler
      1 bind_interdomain_evtchn_to_irq
      1 bind_evtchn_to_irqhandler
      1 bind_evtchn_to_irq
      1 
