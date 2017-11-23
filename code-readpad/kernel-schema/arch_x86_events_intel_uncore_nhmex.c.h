
static void nhmex_uncore_msr_init_box(struct intel_uncore_box *box)
static void nhmex_uncore_msr_exit_box(struct intel_uncore_box *box)
static void nhmex_uncore_msr_disable_box(struct intel_uncore_box *box)
static void nhmex_uncore_msr_enable_box(struct intel_uncore_box *box)
static void nhmex_uncore_msr_disable_event(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_uncore_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
static int nhmex_bbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_bbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
static int nhmex_sbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_sbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
static bool nhmex_mbox_get_shared_reg(struct intel_uncore_box *box, int idx, u64 config)
static void nhmex_mbox_put_shared_reg(struct intel_uncore_box *box, int idx)
static u64 nhmex_mbox_alter_er(struct perf_event *event, int new_idx, bool modify)
static struct event_constraint * nhmex_mbox_get_constraint(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_mbox_put_constraint(struct intel_uncore_box *box, struct perf_event *event)
static int nhmex_mbox_extra_reg_idx(struct extra_reg *er)
static int nhmex_mbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
static u64 nhmex_mbox_shared_reg_config(struct intel_uncore_box *box, int idx)
static void nhmex_mbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_rbox_alter_er(struct intel_uncore_box *box, struct perf_event *event)
static struct event_constraint * nhmex_rbox_get_constraint(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_rbox_put_constraint(struct intel_uncore_box *box, struct perf_event *event)
static int nhmex_rbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
static void nhmex_rbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
void nhmex_uncore_cpu_init(void)
  22 struct intel_uncore_box *box
  16 struct perf_event *event
   3 int idx
   1 void
   1 u64 config
   1 struct extra_reg *er
   1 int new_idx
   1 bool modify
