
static inline struct perf_evsel_script *evsel_script(struct perf_evsel *evsel)
static struct perf_evsel_script *perf_evsel_script__new(struct perf_evsel *evsel, struct perf_data *data)
static void perf_evsel_script__delete(struct perf_evsel_script *es)
static int perf_evsel_script__fprintf(struct perf_evsel_script *es, FILE *fp)
static inline int output_type(unsigned int type)
static inline unsigned int attr_type(unsigned int type)
static bool output_set_by_user(void)
static const char *output_field2str(enum perf_output_field field)
static int perf_evsel__do_check_stype(struct perf_evsel *evsel, u64 sample_type, const char *sample_msg, enum perf_output_field field, bool allow_user_set)
static int perf_evsel__check_stype(struct perf_evsel *evsel, u64 sample_type, const char *sample_msg, enum perf_output_field field)
static int perf_evsel__check_attr(struct perf_evsel *evsel, struct perf_session *session)
static void set_print_ip_opts(struct perf_event_attr *attr)
static int perf_session__check_output_opt(struct perf_session *session)
static int perf_sample__fprintf_iregs(struct perf_sample *sample, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_uregs(struct perf_sample *sample, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_start(struct perf_sample *sample, struct thread *thread, struct perf_evsel *evsel, u32 type, FILE *fp)
static inline char mispred_str(struct branch_entry *br)
static int perf_sample__fprintf_brstack(struct perf_sample *sample, struct thread *thread, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_brstacksym(struct perf_sample *sample, struct thread *thread, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_brstackoff(struct perf_sample *sample, struct thread *thread, struct perf_event_attr *attr, FILE *fp)
static int grab_bb(u8 *buffer, u64 start, u64 end, struct machine *machine, struct thread *thread, bool *is64bit, u8 *cpumode, bool last)
static int ip__fprintf_jump(uint64_t ip, struct branch_entry *en, struct perf_insn *x, u8 *inbuf, int len, int insn, FILE *fp)
static int ip__fprintf_sym(uint64_t addr, struct thread *thread, u8 cpumode, int cpu, struct symbol **lastsym, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_brstackinsn(struct perf_sample *sample, struct thread *thread, struct perf_event_attr *attr, struct machine *machine, FILE *fp)
static int perf_sample__fprintf_addr(struct perf_sample *sample, struct thread *thread, struct perf_event_attr *attr, FILE *fp)
static int perf_sample__fprintf_callindent(struct perf_sample *sample, struct perf_evsel *evsel, struct thread *thread, struct addr_location *al, FILE *fp)
static int perf_sample__fprintf_insn(struct perf_sample *sample, struct perf_event_attr *attr, struct thread *thread, struct machine *machine, FILE *fp)
static int perf_sample__fprintf_bts(struct perf_sample *sample, struct perf_evsel *evsel, struct thread *thread, struct addr_location *al, struct machine *machine, FILE *fp)
static const char *sample_flags_to_name(u32 flags)
static int perf_sample__fprintf_flags(u32 flags, FILE *fp)
static int sample__fprintf_bpf_output(enum binary_printer_ops op, unsigned int val, void *extra, FILE *fp)
static int perf_sample__fprintf_bpf_output(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_spacing(int len, int spacing, FILE *fp)
static int perf_sample__fprintf_pt_spacing(int len, FILE *fp)
static int perf_sample__fprintf_synth_ptwrite(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth_mwait(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth_pwre(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth_exstop(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth_pwrx(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth_cbr(struct perf_sample *sample, FILE *fp)
static int perf_sample__fprintf_synth(struct perf_sample *sample, struct perf_evsel *evsel, FILE *fp)
static int perf_evlist__max_name_len(struct perf_evlist *evlist)
static int data_src__fprintf(u64 data_src, FILE *fp)
static void script_print_metric(struct perf_stat_config *config __maybe_unused, void *ctx, const char *color, const char *fmt, const char *unit, double val)
static void script_new_line(struct perf_stat_config *config __maybe_unused, void *ctx)
static void perf_sample__fprint_metric(struct perf_script *script, struct thread *thread, struct perf_evsel *evsel, struct perf_sample *sample, FILE *fp)
static void process_event(struct perf_script *script, struct perf_sample *sample, struct perf_evsel *evsel, struct addr_location *al, struct machine *machine)
static void __process_stat(struct perf_evsel *counter, u64 tstamp)
static void process_stat(struct perf_evsel *counter, u64 tstamp)
static void process_stat_interval(u64 tstamp)
static void setup_scripting(void)
static int flush_scripting(void)
static int cleanup_scripting(void)
static int process_sample_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct perf_evsel *evsel, struct machine *machine)
static int process_attr(struct perf_tool *tool, union perf_event *event, struct perf_evlist **pevlist)
static int process_comm_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_namespaces_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_fork_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
return 0; } static int process_exit_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_mmap_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_mmap2_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_switch_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static int process_lost_event(struct perf_tool *tool, union perf_event *event, struct perf_sample *sample, struct machine *machine)
static void sig_handler(int sig __maybe_unused)
static void perf_script__fclose_per_event_dump(struct perf_script *script)
static int perf_script__fopen_per_event_dump(struct perf_script *script)
static int perf_script__setup_per_event_dump(struct perf_script *script)
static void perf_script__exit_per_event_dump_stats(struct perf_script *script)
static int __cmd_script(struct perf_script *script)
static struct script_spec *script_spec__new(const char *spec, struct scripting_ops *ops)
static void script_spec__add(struct script_spec *s)
static struct script_spec *script_spec__find(const char *spec)
int script_spec_register(const char *spec, struct scripting_ops *ops)
static struct scripting_ops *script_spec__lookup(const char *spec)
static void list_available_languages(void)
static int parse_scriptname(const struct option *opt __maybe_unused, const char *str, int unset __maybe_unused)
static int parse_output_fields(const struct option *opt __maybe_unused, const char *arg, int unset __maybe_unused)
static struct script_desc *script_desc__new(const char *name)
static void script_desc__delete(struct script_desc *s)
static void script_desc__add(struct script_desc *s)
static struct script_desc *script_desc__find(const char *name)
static struct script_desc *script_desc__findnew(const char *name)
static const char *ends_with(const char *str, const char *suffix)
static int read_script_info(struct script_desc *desc, const char *filename)
static char *get_script_root(struct dirent *script_dirent, const char *suffix)
static int list_available_scripts(const struct option *opt __maybe_unused, const char *s __maybe_unused, int unset __maybe_unused)
static int check_ev_match(char *dir_name, char *scriptname, struct perf_session *session)
int find_scripts(char **scripts_array, char **scripts_path_array)
static char *get_script_path(const char *script_root, const char *suffix)
static bool is_top_script(const char *script_path)
static int has_required_arg(char *script_path)
static int have_cmd(int argc, const char **argv)
static void script__setup_sample_type(struct perf_script *script)
static int process_stat_round_event(struct perf_session *session, union perf_event *event)
static int process_stat_config_event(struct perf_session *session __maybe_unused, union perf_event *event)
static int set_maps(struct perf_script *script)
static int process_thread_map_event(struct perf_session *session, union perf_event *event)
static int process_cpu_map_event(struct perf_session *session, union perf_event *event)
static int process_feature_event(struct perf_session *session, union perf_event *event)
static int perf_script__process_auxtrace_info(struct perf_session *session, union perf_event *event)
int cmd_script(int argc, const char **argv)
  30 struct perf_sample *sample
  28 FILE *fp
  16 union perf_event *event
  14 struct machine *machine
  12 struct thread *thread
  12 struct perf_evsel *evsel
  10 struct perf_tool *tool
  10 struct perf_event_attr *attr
   9 struct perf_script *script
   8 struct perf_session *session
   5 void
   4 const char *spec
   3 u64 tstamp
   3 struct addr_location *al
   3 int unset __maybe_unused
   3 int len
   3 enum perf_output_field field
   3 const struct option *opt __maybe_unused
   3 const char *suffix
   3 const char *name
   2 void *ctx
   2 unsigned int type
   2 u64 sample_type
   2 u32 flags
   2 struct scripting_ops *ops
   2 struct script_desc *s
   2 struct perf_stat_config *config __maybe_unused
   2 struct perf_evsel_script *es
   2 struct perf_evsel *counter
   2 int argc
   2 const char *str
   2 const char *sample_msg
   2 const char **argv
   1 void *extra
   1 unsigned int val
   1 uint64_t ip
   1 uint64_t addr
   1 u8 cpumode
   1 u8 *inbuf
   1 u8 *cpumode
   1 u8 *buffer
   1 u64 start
   1 u64 end
   1 u64 data_src
   1 u32 type
   1 struct symbol **lastsym
   1 struct script_spec *s
   1 struct script_desc *desc
   1 struct perf_session *session __maybe_unused
   1 struct perf_insn *x
   1 struct perf_evlist *evlist
   1 struct perf_evlist **pevlist
   1 struct perf_data *data
   1 struct dirent *script_dirent
   1 struct branch_entry *en
   1 struct branch_entry *br
   1 int spacing
   1 int sig __maybe_unused
   1 int insn
   1 int cpu
   1 enum binary_printer_ops op
   1 double val
   1 const char *unit
   1 const char *script_root
   1 const char *script_path
   1 const char *s __maybe_unused
   1 const char *fmt
   1 const char *filename
   1 const char *color
   1 const char *arg
   1 char *scriptname
   1 char *script_path
   1 char *dir_name
   1 char **scripts_path_array
   1 char **scripts_array
   1 bool last
   1 bool allow_user_set
   1 bool *is64bit
