
EXPORT_SYMBOL_GPL(force_irqthreads);
EXPORT_SYMBOL_GPL(irq_set_affinity_hint);
EXPORT_SYMBOL_GPL(irq_set_affinity_notifier);
EXPORT_SYMBOL_GPL(irq_set_vcpu_affinity);
EXPORT_SYMBOL_GPL(disable_hardirq);
EXPORT_SYMBOL_GPL(irq_set_parent);
EXPORT_SYMBOL_GPL(irq_wake_thread);
EXPORT_SYMBOL_GPL(setup_irq);
EXPORT_SYMBOL_GPL(remove_irq);
EXPORT_SYMBOL_GPL(request_any_context_irq);
EXPORT_SYMBOL_GPL(enable_percpu_irq);
EXPORT_SYMBOL_GPL(irq_percpu_is_enabled);
EXPORT_SYMBOL_GPL(disable_percpu_irq);
EXPORT_SYMBOL_GPL(free_percpu_irq);
EXPORT_SYMBOL_GPL(__request_percpu_irq);
EXPORT_SYMBOL_GPL(irq_get_irqchip_state);
EXPORT_SYMBOL_GPL(irq_set_irqchip_state);
\n
static int __init setup_forced_irqthreads(char *arg)
static void __synchronize_hardirq(struct irq_desc *desc)
bool synchronize_hardirq(unsigned int irq)
void synchronize_irq(unsigned int irq)
static bool __irq_can_set_affinity(struct irq_desc *desc)
int irq_can_set_affinity(unsigned int irq)
bool irq_can_set_affinity_usr(unsigned int irq)
void irq_set_thread_affinity(struct irq_desc *desc)
static void irq_validate_effective_affinity(struct irq_data *data)
int irq_do_set_affinity(struct irq_data *data, const struct cpumask *mask, bool force)
static inline int irq_set_affinity_pending(struct irq_data *data, const struct cpumask *dest)
irqd_set_move_pending(data)
;irq_copy_pending(desc, dest)
;return 0; } static inline int irq_set_affinity_pending(struct irq_data *data, const struct cpumask *dest)
static int irq_try_set_affinity(struct irq_data *data, const struct cpumask *dest, bool force)
int irq_set_affinity_locked(struct irq_data *data, const struct cpumask *mask, bool force)
int __irq_set_affinity(unsigned int irq, const struct cpumask *mask, bool force)
int irq_set_affinity_hint(unsigned int irq, const struct cpumask *m)
static void irq_affinity_notify(struct work_struct *work)
int irq_set_affinity_notifier(unsigned int irq, struct irq_affinity_notify *notify)
int irq_setup_affinity(struct irq_desc *desc)
if (cpumask_intersects(&mask, nodemask)
)
cpumask_and(&mask, &mask, nodemask)
;}ret = irq_do_set_affinity(&desc->irq_data, &mask, false)
;raw_spin_unlock(&mask_lock)
;return ret; }int irq_setup_affinity(struct irq_desc *desc)
int irq_select_affinity_usr(unsigned int irq)
int irq_set_vcpu_affinity(unsigned int irq, void *vcpu_info)
void __disable_irq(struct irq_desc *desc)
static int __disable_irq_nosync(unsigned int irq)
void disable_irq_nosync(unsigned int irq)
void disable_irq(unsigned int irq)
bool disable_hardirq(unsigned int irq)
void __enable_irq(struct irq_desc *desc)
void enable_irq(unsigned int irq)
static int set_irq_wake_real(unsigned int irq, unsigned int on)
int irq_set_irq_wake(unsigned int irq, unsigned int on)
int can_request_irq(unsigned int irq, unsigned long irqflags)
int __irq_set_trigger(struct irq_desc *desc, unsigned long flags)
int irq_set_parent(int irq, int parent_irq)
static irqreturn_t irq_default_primary_handler(int irq, void *dev_id)
static irqreturn_t irq_nested_primary_handler(int irq, void *dev_id)
static irqreturn_t irq_forced_secondary_handler(int irq, void *dev_id)
static int irq_wait_for_interrupt(struct irqaction *action)
static void irq_finalize_oneshot(struct irq_desc *desc, struct irqaction *action)
static void irq_thread_check_affinity(struct irq_desc *desc, struct irqaction *action)
static irqreturn_t irq_forced_thread_fn(struct irq_desc *desc, struct irqaction *action)
static irqreturn_t irq_thread_fn(struct irq_desc *desc, struct irqaction *action)
static void wake_threads_waitq(struct irq_desc *desc)
static void irq_thread_dtor(struct callback_head *unused)
static void irq_wake_secondary(struct irq_desc *desc, struct irqaction *action)
static int irq_thread(void *data)
void irq_wake_thread(unsigned int irq, void *dev_id)
static int irq_setup_forced_threading(struct irqaction *new)
static int irq_request_resources(struct irq_desc *desc)
static void irq_release_resources(struct irq_desc *desc)
static int setup_irq_thread(struct irqaction *new, unsigned int irq, bool secondary)
static int __setup_irq(unsigned int irq, struct irq_desc *desc, struct irqaction *new)
int setup_irq(unsigned int irq, struct irqaction *act)
static struct irqaction *__free_irq(struct irq_desc *desc, void *dev_id)
void remove_irq(unsigned int irq, struct irqaction *act)
const void *free_irq(unsigned int irq, void *dev_id)
int request_threaded_irq(unsigned int irq, irq_handler_t handler, irq_handler_t thread_fn, unsigned long irqflags, const char *devname, void *dev_id)
int request_any_context_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev_id)
void enable_percpu_irq(unsigned int irq, unsigned int type)
bool irq_percpu_is_enabled(unsigned int irq)
void disable_percpu_irq(unsigned int irq)
static struct irqaction *__free_percpu_irq(unsigned int irq, void __percpu *dev_id)
void remove_percpu_irq(unsigned int irq, struct irqaction *act)
void free_percpu_irq(unsigned int irq, void __percpu *dev_id)
int setup_percpu_irq(unsigned int irq, struct irqaction *act)
int __request_percpu_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *devname, void __percpu *dev_id)
int irq_get_irqchip_state(unsigned int irq, enum irqchip_irq_state which, bool *state)
int irq_set_irqchip_state(unsigned int irq, enum irqchip_irq_state which, bool val)
\n
     35 unsigned int irq
     18 struct irq_desc *desc
      8 void *dev_id
      6 struct irq_data *data
      6 struct irqaction *action
      4 struct irqaction *act
      4 int irq
      4 bool force
      3 void __percpu *dev_id
      3 unsigned long flags
      3 struct irqaction *new
      3 &mask
      3 irq_handler_t handler
      3 const struct cpumask *mask
      3 const struct cpumask *dest
      2 unsigned long irqflags
      2 unsigned int on
      2 nodemask
      2 enum irqchip_irq_state which
      2 const char *devname
      1 void *vcpu_info
      1 void *data
      1 unsigned int type
      1 struct work_struct *work
      1 struct irq_affinity_notify *notify
      1 struct callback_head *unused
      1 setup_irq
      1 __request_percpu_irq
      1 request_any_context_irq
      1 remove_irq
      1 &mask_lock
      1 irq_wake_thread
      1 irq_set_vcpu_affinity
      1 irq_set_parent
      1 irq_set_irqchip_state
      1 irq_set_affinity_notifier
      1 irq_set_affinity_hint
      1 irq_percpu_is_enabled
      1 irq_handler_t thread_fn
      1 irq_get_irqchip_state
      1 int parent_irq
      1 free_percpu_irq
      1 force_irqthreads
      1 false
      1 enable_percpu_irq
      1 disable_percpu_irq
      1 disable_hardirq
      1 dest
      1 &desc->irq_data
      1 desc
      1 data
      1 cpumask_intersects&mask
      1 const struct cpumask *m
      1 const char *name
      1 char *arg
      1 bool val
      1 bool *state
      1 bool secondary
