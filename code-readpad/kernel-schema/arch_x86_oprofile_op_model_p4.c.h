
\n
static inline void setup_num_counters(void)
static inline int addr_increment(void)
static unsigned int get_stagger(void)
static void p4_shutdown(struct op_msrs const * const msrs)
static int p4_fill_in_addresses(struct op_msrs * const msrs)
static void pmc_setup_one_p4_counter(unsigned int ctr)
static void p4_setup_ctrs(struct op_x86_model_spec const *model, struct op_msrs const * const msrs)
static int p4_check_ctrs(struct pt_regs * const regs, struct op_msrs const * const msrs)
static void p4_start(struct op_msrs const * const msrs)
static void p4_stop(struct op_msrs const * const msrs)
\n
      5 struct op_msrs const * const msrs
      3 void
      1 unsigned int ctr
      1 struct pt_regs * const regs
      1 struct op_x86_model_spec const *model
      1 struct op_msrs * const msrs
