
EXPORT_SYMBOL_GPL(static_key_initialized);
\n
static int __init set_reset_devices(char *str)
static bool __init obsolete_checksetup(char *line)
static int __init debug_kernel(char *str)
static int __init quiet_kernel(char *str)
static int __init loglevel(char *str)
static int __init repair_env_string(char *param, char *val, const char *unused, void *arg)
static int __init set_init_arg(char *param, char *val, const char *unused, void *arg)
static int __init unknown_bootoption(char *param, char *val, const char *unused, void *arg)
static int __init init_setup(char *str)
static int __init rdinit_setup(char *str)
static void __init setup_command_line(char *command_line)
noinline void __ref rest_init(void)
static int __init do_early_param(char *param, char *val, const char *unused, void *arg)
void __init parse_early_options(char *cmdline)
void __init parse_early_param(void)
void __init __weak smp_setup_processor_id(void)
if THREAD_SIZE >= PAGE_SIZE void __init __weak thread_stack_cache_init(void)
static void __init initcall_debug_enable(void)
; static inline void initcall_debug_enable(void)
static void __init mm_init(void)
void __init __weak arch_call_rest_init(void)
asmlinkage __visible void __init start_kernel(void)
static void __init do_ctors(void)
static int __init initcall_blacklist(char *str)
static bool __init_or_module initcall_blacklisted(initcall_t fn)
return false; } static int __init initcall_blacklist(char *str)
static bool __init_or_module initcall_blacklisted(initcall_t fn)
static __init_or_module void trace_initcall_start_cb(void *data, initcall_t fn)
static __init_or_module void trace_initcall_finish_cb(void *data, initcall_t fn, int ret)
static void __init initcall_debug_enable(void)
ret = register_trace_initcall_start(trace_initcall_start_cb, &initcall_calltime)
;ret |= register_trace_initcall_finish(trace_initcall_finish_cb, &initcall_calltime)
;WARN(ret, "Failed to register initcall tracepoints\n")
; } define do_trace_initcall_start trace_initcall_start define do_trace_initcall_finish trace_initcall_finish static inline void do_trace_initcall_start(initcall_t fn)
ret = register_trace_initcall_start(trace_initcall_start_cb, &initcall_calltime)
;ret |= register_trace_initcall_finish(trace_initcall_finish_cb, &initcall_calltime)
;WARN(ret, "Failed to register initcall tracepoints\n")
; } define do_trace_initcall_start trace_initcall_start define do_trace_initcall_finish trace_initcall_finish static inline void do_trace_initcall_start(initcall_t fn)
if (!initcall_debug)
return;trace_initcall_start_cb(&initcall_calltime, fn)
; } static inline void do_trace_initcall_finish(initcall_t fn, int ret)
int __init_or_module do_one_initcall(initcall_t fn)
static void __init do_initcall_level(int level)
static void __init do_initcalls(void)
static void __init do_basic_setup(void)
static void __init do_pre_smp_initcalls(void)
static int run_init_process(const char *init_filename)
static int try_to_run_init_process(const char *init_filename)
bool rodata_enabled __ro_after_init = true; static int __init set_debug_rodata(char *str)
static void mark_readonly(void)
static void mark_readonly(void)
rcu_barrier()
; mark_rodata_ro()
; rodata_test()
;} else pr_info("Kernel memory protection disabled.\n")
; } static inline void mark_readonly(void)
static int __ref kernel_init(void *unused)
static noinline void __init kernel_init_freeable(void)
\n
     18 void
      9 char *str
      8 initcall_t fn
      5 &initcall_calltime
      4 void *arg
      4 const char *unused
      4 char *val
      4 char *param
      3 
      2 void *data
      2 trace_initcall_start_cb
      2 trace_initcall_finish_cb
      2 ret
      2 int ret
      2 "Failed to register initcall tracepoints\n"
      2 const char *init_filename
      1 void *unused
      1 static_key_initialized
      1 "Kernel memory protection disabled.\n"
      1 int level
      1 !initcall_debug
      1 fn
      1 char *line
      1 char *command_line
      1 char *cmdline
