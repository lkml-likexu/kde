
static int perf_evsel__no_extra_init(struct perf_evsel *evsel __maybe_unused)
static void perf_evsel__no_extra_fini(struct perf_evsel *evsel __maybe_unused)
int perf_evsel__object_config(size_t object_size, int (*init)
(struct perf_evsel *evsel)
, void (*fini)
(struct perf_evsel *evsel)
)
int __perf_evsel__sample_size(u64 sample_type)
static int __perf_evsel__calc_id_pos(u64 sample_type)
static int __perf_evsel__calc_is_pos(u64 sample_type)
void perf_evsel__calc_id_pos(struct perf_evsel *evsel)
void __perf_evsel__set_sample_bit(struct perf_evsel *evsel, enum perf_event_sample_format bit)
void __perf_evsel__reset_sample_bit(struct perf_evsel *evsel, enum perf_event_sample_format bit)
void perf_evsel__set_sample_id(struct perf_evsel *evsel, bool can_sample_identifier)
bool perf_evsel__is_function_event(struct perf_evsel *evsel)
void perf_evsel__init(struct perf_evsel *evsel, struct perf_event_attr *attr, int idx)
struct perf_evsel *perf_evsel__new_idx(struct perf_event_attr *attr, int idx)
static bool perf_event_can_profile_kernel(void)
struct perf_evsel *perf_evsel__new_cycles(bool precise)
struct perf_evsel *perf_evsel__newtp_idx(const char *sys, const char *name, int idx)
static const char *__perf_evsel__hw_name(u64 config)
static int perf_evsel__add_modifiers(struct perf_evsel *evsel, char *bf, size_t size)
static int perf_evsel__hw_name(struct perf_evsel *evsel, char *bf, size_t size)
static const char *__perf_evsel__sw_name(u64 config)
static int perf_evsel__sw_name(struct perf_evsel *evsel, char *bf, size_t size)
static int __perf_evsel__bp_name(char *bf, size_t size, u64 addr, u64 type)
static int perf_evsel__bp_name(struct perf_evsel *evsel, char *bf, size_t size)
bool perf_evsel__is_cache_op_valid(u8 type, u8 op)
int __perf_evsel__hw_cache_type_op_res_name(u8 type, u8 op, u8 result, char *bf, size_t size)
static int __perf_evsel__hw_cache_name(u64 config, char *bf, size_t size)
static int perf_evsel__hw_cache_name(struct perf_evsel *evsel, char *bf, size_t size)
static int perf_evsel__raw_name(struct perf_evsel *evsel, char *bf, size_t size)
const char *perf_evsel__name(struct perf_evsel *evsel)
const char *perf_evsel__group_name(struct perf_evsel *evsel)
int perf_evsel__group_desc(struct perf_evsel *evsel, char *buf, size_t size)
static void __perf_evsel__config_callchain(struct perf_evsel *evsel, struct record_opts *opts, struct callchain_param *param)
void perf_evsel__config_callchain(struct perf_evsel *evsel, struct record_opts *opts, struct callchain_param *param)
static void perf_evsel__reset_callgraph(struct perf_evsel *evsel, struct callchain_param *param)
static void apply_config_terms(struct perf_evsel *evsel, struct record_opts *opts, bool track)
static bool is_dummy_event(struct perf_evsel *evsel)
void perf_evsel__config(struct perf_evsel *evsel, struct record_opts *opts, struct callchain_param *callchain)
static int perf_evsel__alloc_fd(struct perf_evsel *evsel, int ncpus, int nthreads)
static int perf_evsel__run_ioctl(struct perf_evsel *evsel, int ioc, void *arg)
int perf_evsel__apply_filter(struct perf_evsel *evsel, const char *filter)
int perf_evsel__set_filter(struct perf_evsel *evsel, const char *filter)
static int perf_evsel__append_filter(struct perf_evsel *evsel, const char *fmt, const char *filter)
int perf_evsel__append_tp_filter(struct perf_evsel *evsel, const char *filter)
int perf_evsel__append_addr_filter(struct perf_evsel *evsel, const char *filter)
int perf_evsel__enable(struct perf_evsel *evsel)
int perf_evsel__disable(struct perf_evsel *evsel)
int perf_evsel__alloc_id(struct perf_evsel *evsel, int ncpus, int nthreads)
static void perf_evsel__free_fd(struct perf_evsel *evsel)
static void perf_evsel__free_id(struct perf_evsel *evsel)
static void perf_evsel__free_config_terms(struct perf_evsel *evsel)
void perf_evsel__close_fd(struct perf_evsel *evsel)
void perf_evsel__exit(struct perf_evsel *evsel)
void perf_evsel__delete(struct perf_evsel *evsel)
void perf_evsel__compute_deltas(struct perf_evsel *evsel, int cpu, int thread, struct perf_counts_values *count)
void perf_counts_values__scale(struct perf_counts_values *count, bool scale, s8 *pscaled)
static int perf_evsel__read_size(struct perf_evsel *evsel)
int perf_evsel__read(struct perf_evsel *evsel, int cpu, int thread, struct perf_counts_values *count)
static int perf_evsel__read_one(struct perf_evsel *evsel, int cpu, int thread)
static void perf_evsel__set_count(struct perf_evsel *counter, int cpu, int thread, u64 val, u64 ena, u64 run)
static int perf_evsel__process_group_data(struct perf_evsel *leader, int cpu, int thread, u64 *data)
static int perf_evsel__read_group(struct perf_evsel *leader, int cpu, int thread)
int perf_evsel__read_counter(struct perf_evsel *evsel, int cpu, int thread)
int __perf_evsel__read_on_cpu(struct perf_evsel *evsel, int cpu, int thread, bool scale)
static int get_group_fd(struct perf_evsel *evsel, int cpu, int thread)
static void __p_bits(char *buf, size_t size, u64 value, struct bit_names *bits)
static void __p_sample_type(char *buf, size_t size, u64 value)
static void __p_branch_sample_type(char *buf, size_t size, u64 value)
static void __p_read_format(char *buf, size_t size, u64 value)
int perf_event_attr__fprintf(FILE *fp, struct perf_event_attr *attr, attr__fprintf_f attr__fprintf, void *priv)
static int __open_attr__fprintf(FILE *fp, const char *name, const char *val, void *priv __maybe_unused)
static void perf_evsel__remove_fd(struct perf_evsel *pos, int nr_cpus, int nr_threads, int thread_idx)
static int update_fds(struct perf_evsel *evsel, int nr_cpus, int cpu_idx, int nr_threads, int thread_idx)
static bool ignore_missing_thread(struct perf_evsel *evsel, int nr_cpus, int cpu, struct thread_map *threads, int thread, int err)
int perf_evsel__open(struct perf_evsel *evsel, struct cpu_map *cpus, struct thread_map *threads)
void perf_evsel__close(struct perf_evsel *evsel)
int perf_evsel__open_per_cpu(struct perf_evsel *evsel, struct cpu_map *cpus)
int perf_evsel__open_per_thread(struct perf_evsel *evsel, struct thread_map *threads)
static int perf_evsel__parse_id_sample(const struct perf_evsel *evsel, const union perf_event *event, struct perf_sample *sample)
static inline bool overflow(const void *endp, u16 max_size, const void *offset, u64 size)
static int perf_event__check_size(union perf_event *event, unsigned int sample_size)
int perf_evsel__parse_sample(struct perf_evsel *evsel, union perf_event *event, struct perf_sample *data)
int perf_evsel__parse_sample_timestamp(struct perf_evsel *evsel, union perf_event *event, u64 *timestamp)
size_t perf_event__sample_event_size(const struct perf_sample *sample, u64 type, u64 read_format)
int perf_event__synthesize_sample(union perf_event *event, u64 type, u64 read_format, const struct perf_sample *sample)
struct tep_format_field *perf_evsel__field(struct perf_evsel *evsel, const char *name)
void *perf_evsel__rawptr(struct perf_evsel *evsel, struct perf_sample *sample, const char *name)
u64 format_field__intval(struct tep_format_field *field, struct perf_sample *sample, bool needs_swap)
u64 perf_evsel__intval(struct perf_evsel *evsel, struct perf_sample *sample, const char *name)
bool perf_evsel__fallback(struct perf_evsel *evsel, int err, char *msg, size_t msgsize)
static bool find_process(const char *name)
int perf_evsel__open_strerror(struct perf_evsel *evsel, struct target *target, int err, char *msg, size_t size)
struct perf_env *perf_evsel__env(struct perf_evsel *evsel)
static int store_evsel_ids(struct perf_evsel *evsel, struct perf_evlist *evlist)
int perf_evsel__store_ids(struct perf_evsel *evsel, struct perf_evlist *evlist)
  62 struct perf_evsel *evsel
  15 size_t size
  10 int thread
  10 int cpu
   9 char *bf
   6 const char *name
   5 const char *filter
   5 char *buf
   4 union perf_event *event
   4 u64 value
   4 struct record_opts *opts
   4 struct perf_sample *sample
   3 u64 type
   3 u64 sample_type
   3 u64 config
   3 struct thread_map *threads
   3 struct perf_event_attr *attr
   3 struct perf_counts_values *count
   3 struct callchain_param *param
   3 int nr_cpus
   3 int idx
   3 int err
   2 u8 type
   2 u8 op
   2 u64 read_format
   2 struct perf_evsel *leader
   2 struct perf_evsel *evsel __maybe_unused
   2 struct perf_evlist *evlist
   2 struct cpu_map *cpus
   2 int thread_idx
   2 int nthreads
   2 int nr_threads
   2 int ncpus
   2 enum perf_event_sample_format bit
   2 const struct perf_sample *sample
   2 char *msg
   2 bool scale
   2 FILE *fp
   1 void *priv __maybe_unused
   1 void *priv
   1 void *arg
   1 void
   1 unsigned int sample_size
   1 u8 result
   1 u64 val
   1 u64 size
   1 u64 run
   1 u64 ena
   1 u64 addr
   1 u64 *timestamp
   1 u64 *data
   1 u16 max_size
   1 struct tep_format_field *field
   1 struct target *target
   1 struct perf_sample *data
   1 struct perf_evsel *pos
   1 struct perf_evsel *counter
   1 struct callchain_param *callchain
   1 struct bit_names *bits
   1 size_t object_size
   1 size_t msgsize
   1 s8 *pscaled
   1 int ioc
   1 int cpu_idx
   1 int *init
   1 const void *offset
   1 const void *endp
   1 const union perf_event *event
   1 const struct perf_evsel *evsel
   1 const char *val
   1 const char *sys
   1 const char *fmt
   1 bool track
   1 bool precise
   1 bool needs_swap
   1 bool can_sample_identifier
   1 attr__fprintf_f attr__fprintf
   1 *fini
