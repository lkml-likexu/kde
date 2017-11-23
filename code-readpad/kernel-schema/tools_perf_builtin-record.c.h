
static bool switch_output_signal(struct record *rec)
static bool switch_output_size(struct record *rec)
static bool switch_output_time(struct record *rec)
static int record__write(struct record *rec, struct perf_mmap *map __maybe_unused, void *bf, size_t size)
static int process_synthesized_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample __maybe_unused, struct machine *machine __maybe_unused)
static int record__pushfn(struct perf_mmap *map, void *to, void *bf, size_t size)
static void sig_handler(int sig)
static void sigsegv_handler(int sig)
static void record__sig_exit(void)
static int record__process_auxtrace(struct perf_tool *tool, struct perf_mmap *map, union perf_event *event, void *data1, size_t len1, void *data2, size_t len2)
static int record__auxtrace_mmap_read(struct record *rec, struct perf_mmap *map)
static int record__auxtrace_mmap_read_snapshot(struct record *rec, struct perf_mmap *map)
static int record__auxtrace_read_snapshot_all(struct record *rec)
static void record__read_auxtrace_snapshot(struct record *rec)
static int record__auxtrace_init(struct record *rec)
static inline int record__auxtrace_mmap_read(struct record *rec __maybe_unused, struct perf_mmap *map __maybe_unused)
static inline void record__read_auxtrace_snapshot(struct record *rec __maybe_unused)
static inline int auxtrace_record__snapshot_start(struct auxtrace_record *itr __maybe_unused)
static int record__auxtrace_init(struct record *rec __maybe_unused)
static int record__mmap_evlist(struct record *rec, struct perf_evlist *evlist)
static int record__mmap(struct record *rec)
static int record__open(struct record *rec)
static int process_sample_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct perf_evsel *evsel, struct machine *machine)
static int process_buildids(struct record *rec)
static void perf_event__synthesize_guest_os(struct machine *machine, void *data)
static int record__mmap_read_evlist(struct record *rec, struct perf_evlist *evlist, bool overwrite)
static int record__mmap_read_all(struct record *rec)
static void record__init_features(struct record *rec)
static void record__finish_output(struct record *rec)
static int record__synthesize_workload(struct record *rec, bool tail)
static int record__switch_output(struct record *rec, bool at_exit)
static void workload_exec_failed_signal(int signo __maybe_unused, siginfo_t *info, void *ucontext __maybe_unused)
int __weak perf_event__synth_time_conv(const struct perf_event_mmap_page *pc __maybe_unused, struct perf_tool *tool __maybe_unused, perf_event__handler_t process __maybe_unused, struct machine *machine __maybe_unused)
static const struct perf_event_mmap_page * perf_evlist__pick_pc(struct perf_evlist *evlist)
static const struct perf_event_mmap_page *record__pick_pc(struct record *rec)
static int record__synthesize(struct record *rec, bool tail)
static int __cmd_record(struct record *rec, int argc, const char **argv)
static void callchain_debug(struct callchain_param *callchain)
int record_opts__parse_callchain(struct record_opts *record, struct callchain_param *callchain, const char *arg, bool unset)
int record_parse_callchain_opt(const struct option *opt, const char *arg, int unset)
int record_callchain_opt(const struct option *opt, const char *arg __maybe_unused, int unset __maybe_unused)
static int perf_record_config(const char *var, const char *value, void *cb)
static int parse_clockid(const struct option *opt, const char *str, int unset)
static int record__parse_mmap_pages(const struct option *opt, const char *str, int unset __maybe_unused)
static void switch_output_size_warn(struct record *rec)
static int switch_output_setup(struct record *rec)
int cmd_record(int argc, const char **argv)
static void snapshot_sig_handler(int sig __maybe_unused)
static void alarm_sig_handler(int sig __maybe_unused)
  24 struct record *rec
   4 struct perf_mmap *map
   4 const struct option *opt
   3 union perf_event *event
   3 struct record *rec __maybe_unused
   3 struct perf_tool *tool
   3 struct perf_evlist *evlist
   2 void *bf
   2 struct perf_mmap *map __maybe_unused
   2 struct machine *machine __maybe_unused
   2 struct machine *machine
   2 struct callchain_param *callchain
   2 size_t size
   2 int unset __maybe_unused
   2 int unset
   2 int sig __maybe_unused
   2 int sig
   2 int argc
   2 const char *str
   2 const char *arg
   2 const char **argv
   2 bool tail
   1 void *ucontext __maybe_unused
   1 void *to
   1 void *data2
   1 void *data1
   1 void *data
   1 void *cb
   1 void
   1 struct record_opts *record
   1 struct perf_tool *tool __maybe_unused
   1 struct perf_sample *sample __maybe_unused
   1 struct perf_sample *sample
   1 struct perf_evsel *evsel
   1 struct auxtrace_record *itr __maybe_unused
   1 size_t len2
   1 size_t len1
   1 siginfo_t *info
   1 perf_event__handler_t process __maybe_unused
   1 int signo __maybe_unused
   1 const struct perf_event_mmap_page *pc __maybe_unused
   1 const char *var
   1 const char *value
   1 const char *arg __maybe_unused
   1 bool unset
   1 bool overwrite
   1 bool at_exit
