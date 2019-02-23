
\n
static inline__u64 generate_guest_id(__u64 d_info1, __u64 kernel_version, __u64 d_info2)
static inline void vmbus_signal_eom(struct hv_message *msg, u32 old_msg_type)
static inline u64 hv_do_hypercall(u64 control, void *input, void *output)
static inline u64 hv_do_fast_hypercall8(u16 code, u64 input1)
static inline u64 hv_do_fast_hypercall16(u16 code, u64 input1, u64 input2)
static inline u64 hv_do_rep_hypercall(u16 code, u16 rep_count, u16 varhead_size, void *input, void *output)
static inline struct hv_vp_assist_page *hv_get_vp_assist_page(unsigned int cpu)
static inline int hv_cpu_number_to_vp_number(int cpu_number)
static inline int cpumask_to_vpset(struct hv_vpset *vpset, const struct cpumask *cpus)
static inline struct hv_vp_assist_page *hv_get_vp_assist_page(unsigned int cpu)
static inline struct hv_vp_assist_page *hv_get_vp_assist_page(unsigned int cpu)
return NULL; } static inline int hyperv_flush_guest_mapping_range(u64 as, hyperv_fill_flush_list_func fill_func, void *data)
struct ms_hyperv_tsc_page *hv_get_tsc_page(void)
; static inline u64 hv_read_tsc_page_tsc(const struct ms_hyperv_tsc_page *tsc_pg, u64 *cur_tsc)
static inline u64 hv_read_tsc_page(const struct ms_hyperv_tsc_page *tsc_pg)
static inline struct ms_hyperv_tsc_page *hv_get_tsc_page(void)
static inline u64 hv_read_tsc_page_tsc(const struct ms_hyperv_tsc_page *tsc_pg, u64 *cur_tsc)
\n
      3 unsigned int cpu
      3 u16 code
      3 const struct ms_hyperv_tsc_page *tsc_pg
      2 void *output
      2 void *input
      2 void
      2 u64 input1
      2 u64 *cur_tsc
      1 void *data
      1 __u64 kernel_version
      1 u64 input2
      1 __u64 d_info2
      1 __u64 d_info1
      1 u64 control
      1 u64 as
      1 u32 old_msg_type
      1 u16 varhead_size
      1 u16 rep_count
      1 struct hv_vpset *vpset
      1 struct hv_message *msg
      1 int cpu_number
      1 hyperv_fill_flush_list_func fill_func
      1 const struct cpumask *cpus
