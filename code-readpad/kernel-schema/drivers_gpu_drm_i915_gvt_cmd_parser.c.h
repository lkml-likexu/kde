
\n
static inline u32 get_opcode(u32 cmd, int ring_id)
static inline struct cmd_info *find_cmd_entry(struct intel_gvt *gvt, unsigned int opcode, int ring_id)
static inline struct cmd_info *get_cmd_info(struct intel_gvt *gvt, u32 cmd, int ring_id)
static inline u32 sub_op_val(u32 cmd, u32 hi, u32 low)
static inline void print_opcode(u32 cmd, int ring_id)
static inline u32 *cmd_ptr(struct parser_exec_state *s, int index)
static inline u32 cmd_val(struct parser_exec_state *s, int index)
static void parser_exec_state_dump(struct parser_exec_state *s)
static inline void update_ip_va(struct parser_exec_state *s)
static inline int ip_gma_set(struct parser_exec_state *s, unsigned long ip_gma)
static inline int ip_gma_advance(struct parser_exec_state *s, unsigned int dw_len)
static inline int get_cmd_length(struct cmd_info *info, u32 cmd)
static inline int cmd_length(struct parser_exec_state *s)
static bool is_shadowed_mmio(unsigned int offset)
static inline bool is_force_nonpriv_mmio(unsigned int offset)
static int force_nonpriv_reg_handler(struct parser_exec_state *s, unsigned int offset, unsigned int index, char *cmd)
static inline bool is_mocs_mmio(unsigned int offset)
static int mocs_cmd_reg_handler(struct parser_exec_state *s, unsigned int offset, unsigned int index)
static int cmd_reg_handler(struct parser_exec_state *s, unsigned int offset, unsigned int index, char *cmd)
static int cmd_handler_lri(struct parser_exec_state *s)
static int cmd_handler_lrr(struct parser_exec_state *s)
static int cmd_handler_lrm(struct parser_exec_state *s)
static int cmd_handler_srm(struct parser_exec_state *s)
static int cmd_handler_pipe_control(struct parser_exec_state *s)
static int cmd_handler_mi_user_interrupt(struct parser_exec_state *s)
static int cmd_advance_default(struct parser_exec_state *s)
static int cmd_handler_mi_batch_buffer_end(struct parser_exec_state *s)
static int gen8_decode_mi_display_flip(struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int skl_decode_mi_display_flip(struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int gen8_check_mi_display_flip(struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int gen8_update_plane_mmio_from_mi_display_flip( struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int decode_mi_display_flip(struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int check_mi_display_flip(struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int update_plane_mmio_from_mi_display_flip( struct parser_exec_state *s, struct mi_display_flip_command_info *info)
static int cmd_handler_mi_display_flip(struct parser_exec_state *s)
static bool is_wait_for_flip_pending(u32 cmd)
static int cmd_handler_mi_wait_for_event(struct parser_exec_state *s)
static unsigned long get_gma_bb_from_cmd(struct parser_exec_state *s, int index)
static inline int cmd_address_audit(struct parser_exec_state *s, unsigned long guest_gma, int op_size, bool index_mode)
static int cmd_handler_mi_store_data_imm(struct parser_exec_state *s)
static inline int unexpected_cmd(struct parser_exec_state *s)
static int cmd_handler_mi_semaphore_wait(struct parser_exec_state *s)
static int cmd_handler_mi_report_perf_count(struct parser_exec_state *s)
static int cmd_handler_mi_op_2e(struct parser_exec_state *s)
static int cmd_handler_mi_op_2f(struct parser_exec_state *s)
static int cmd_handler_mi_store_data_index(struct parser_exec_state *s)
static int cmd_handler_mi_clflush(struct parser_exec_state *s)
static int cmd_handler_mi_conditional_batch_buffer_end( struct parser_exec_state *s)
static int cmd_handler_mi_update_gtt(struct parser_exec_state *s)
static int cmd_handler_mi_flush_dw(struct parser_exec_state *s)
static void addr_type_update_snb(struct parser_exec_state *s)
static int copy_gma_to_hva(struct intel_vgpu *vgpu, struct intel_vgpu_mm *mm, unsigned long gma, unsigned long end_gma, void *va)
static int batch_buffer_needs_scan(struct parser_exec_state *s)
static int find_bb_size(struct parser_exec_state *s, unsigned long *bb_size)
static int perform_bb_shadow(struct parser_exec_state *s)
static int cmd_handler_mi_batch_buffer_start(struct parser_exec_state *s)
static void add_cmd_entry(struct intel_gvt *gvt, struct cmd_entry *e)
static int cmd_parser_exec(struct parser_exec_state *s)
static inline bool gma_out_of_range(unsigned long gma, unsigned long gma_head, unsigned int gma_tail)
static int command_scan(struct parser_exec_state *s, unsigned long rb_head, unsigned long rb_tail, unsigned long rb_start, unsigned long rb_len)
static int scan_workload(struct intel_vgpu_workload *workload)
static int scan_wa_ctx(struct intel_shadow_wa_ctx *wa_ctx)
static int shadow_workload_ring_buffer(struct intel_vgpu_workload *workload)
int intel_gvt_scan_and_shadow_ringbuffer(struct intel_vgpu_workload *workload)
static int shadow_indirect_ctx(struct intel_shadow_wa_ctx *wa_ctx)
static int combine_wa_ctx(struct intel_shadow_wa_ctx *wa_ctx)
int intel_gvt_scan_and_shadow_wa_ctx(struct intel_shadow_wa_ctx *wa_ctx)
static struct cmd_info *find_cmd_entry_any_ring(struct intel_gvt *gvt, unsigned int opcode, unsigned long rings)
static int init_cmd_table(struct intel_gvt *gvt)
static void clean_cmd_table(struct intel_gvt *gvt)
void intel_gvt_clean_cmd_parser(struct intel_gvt *gvt)
int intel_gvt_init_cmd_parser(struct intel_gvt *gvt)
\n
     47 struct parser_exec_state *s
      8 struct intel_gvt *gvt
      7 struct mi_display_flip_command_info *info
      6 unsigned int offset
      6 u32 cmd
      4 struct intel_shadow_wa_ctx *wa_ctx
      4 int ring_id
      3 unsigned int index
      3 struct intel_vgpu_workload *workload
      3 int index
      2 unsigned long gma
      2 unsigned int opcode
      2 char *cmd
      1 void *va
      1 unsigned long rings
      1 unsigned long rb_tail
      1 unsigned long rb_start
      1 unsigned long rb_len
      1 unsigned long rb_head
      1 unsigned long ip_gma
      1 unsigned long guest_gma
      1 unsigned long gma_head
      1 unsigned long end_gma
      1 unsigned long *bb_size
      1 unsigned int gma_tail
      1 unsigned int dw_len
      1 u32 low
      1 u32 hi
      1 struct intel_vgpu *vgpu
      1 struct intel_vgpu_mm *mm
      1 struct cmd_info *info
      1 struct cmd_entry *e
      1 int op_size
      1 bool index_mode
