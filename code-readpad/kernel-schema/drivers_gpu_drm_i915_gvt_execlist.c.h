
\n
static int ring_id_to_context_switch_event(int ring_id)
static void switch_virtual_execlist_slot(struct intel_vgpu_execlist *execlist)
static void emulate_execlist_status(struct intel_vgpu_execlist *execlist)
static void emulate_csb_update(struct intel_vgpu_execlist *execlist, struct execlist_context_status_format *status, bool trigger_interrupt_later)
static int emulate_execlist_ctx_schedule_out( struct intel_vgpu_execlist *execlist, struct execlist_ctx_descriptor_format *ctx)
static struct intel_vgpu_execlist_slot *get_next_execlist_slot( struct intel_vgpu_execlist *execlist)
static int emulate_execlist_schedule_in(struct intel_vgpu_execlist *execlist, struct execlist_ctx_descriptor_format ctx[2])
static int prepare_execlist_workload(struct intel_vgpu_workload *workload)
static int complete_execlist_workload(struct intel_vgpu_workload *workload)
static int submit_context(struct intel_vgpu *vgpu, int ring_id, struct execlist_ctx_descriptor_format *desc, bool emulate_schedule_in)
int intel_vgpu_submit_execlist(struct intel_vgpu *vgpu, int ring_id)
static void init_vgpu_execlist(struct intel_vgpu *vgpu, int ring_id)
static void clean_execlist(struct intel_vgpu *vgpu, unsigned long engine_mask)
static void reset_execlist(struct intel_vgpu *vgpu, unsigned long engine_mask)
static int init_execlist(struct intel_vgpu *vgpu, unsigned long engine_mask)
\n
      6 struct intel_vgpu *vgpu
      6 struct intel_vgpu_execlist *execlist
      4 int ring_id
      3 unsigned long engine_mask
      2 struct intel_vgpu_workload *workload
      1 struct execlist_ctx_descriptor_format *desc
      1 struct execlist_ctx_descriptor_format ctx[2]
      1 struct execlist_ctx_descriptor_format *ctx
      1 struct execlist_context_status_format *status
      1 bool trigger_interrupt_later
      1 bool emulate_schedule_in
