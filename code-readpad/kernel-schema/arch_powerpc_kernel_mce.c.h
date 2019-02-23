
EXPORT_SYMBOL_GPL(machine_check_print_event_info);
\n
static void mce_set_error_info(struct machine_check_event *mce, struct mce_error_info *mce_err)
void save_mce_event(struct pt_regs *regs, long handled, struct mce_error_info *mce_err, uint64_t nip, uint64_t addr, uint64_t phys_addr)
int get_mce_event(struct machine_check_event *mce, bool release)
void release_mce_event(void)
void machine_check_ue_event(struct machine_check_event *evt)
void machine_check_queue_event(void)
irq_work_queue(&mce_event_process_work)
; }static void machine_process_ue_event(struct work_struct *work)
pfn = evt->u.ue_error.physical_address >>PAGE_SHIFT; memory_failure(pfn, 0)
;} else pr_warn("Failed to identify bad address from ""where the uncorrectable error (UE)
""was generated\n")
; }endif __this_cpu_dec(mce_ue_count)
;} }static void machine_check_process_queued_event(struct irq_work *work)
void machine_check_print_event_info(struct machine_check_event *evt, bool user_mode)
long machine_check_early(struct pt_regs *regs)
static int init_debug_trig_function(void)
long hmi_handle_debugtrig(struct pt_regs *regs)
long hmi_exception_realmode(struct pt_regs *regs)
\n
      4 struct pt_regs *regs
      3 void
      2 struct mce_error_info *mce_err
      2 struct machine_check_event *mce
      2 struct machine_check_event *evt
      1 uint64_t phys_addr
      1 uint64_t nip
      1 uint64_t addr
      1 struct work_struct *work
      1 struct irq_work *work
      1 pfn
      1 mce_ue_count
      1 &mce_event_process_work
      1 machine_check_print_event_info
      1 long handled
      1 "Failed to identify bad address from ""where the uncorrectable error UE
      1 bool user_mode
      1 bool release
      1 0
