
\n
defined(CONFIG_DYNAMIC_FTRACE)
const char * ftrace_mod_address_lookup(unsigned long addr, unsigned long *size, unsigned long *off, char **modname, char *sym)
; int ftrace_mod_get_kallsym(unsigned int symnum, unsigned long *value, char *type, char *name, char *module_name, int *exported)
; static inline const char * ftrace_mod_address_lookup(unsigned long addr, unsigned long *size, unsigned long *off, char **modname, char *sym)
defined(CONFIG_DYNAMIC_FTRACE)
const char * ftrace_mod_address_lookup(unsigned long addr, unsigned long *size, unsigned long *off, char **modname, char *sym)
; int ftrace_mod_get_kallsym(unsigned int symnum, unsigned long *value, char *type, char *name, char *module_name, int *exported)
; static inline const char * ftrace_mod_address_lookup(unsigned long addr, unsigned long *size, unsigned long *off, char **modname, char *sym)
return NULL; } static inline int ftrace_mod_get_kallsym(unsigned int symnum, unsigned long *value, char *type, char *name, char *module_name, int *exported)
static inline void stack_tracer_disable(void)
static inline void stack_tracer_enable(void)
extern int ftrace_modify_call(struct dyn_ftrace *rec, unsigned long old_addr, unsigned long addr)
;static inline int ftrace_modify_call(struct dyn_ftrace *rec, unsigned long old_addr, unsigned long addr)
extern void ftrace_disable_daemon(void)
; extern void ftrace_enable_daemon(void)
; static inline int ftrace_text_reserved(const void *start, const void *end)
extern void ftrace_disable_daemon(void)
; extern void ftrace_enable_daemon(void)
; static inline int ftrace_text_reserved(const void *start, const void *end)
return 0; } static inline unsigned long ftrace_location(unsigned long ip)
static inline bool is_ftrace_trampoline(unsigned long addr)
static inline void tracer_disable(void)
static inline int __ftrace_enabled_save(void)
static inline void __ftrace_enabled_restore(int enabled)
static inline unsigned long get_lock_parent_ip(void)
static inline void pause_graph_tracing(void)
static inline void unpause_graph_tracing(void)
static inline unsigned long ftrace_graph_ret_addr(struct task_struct *task, int *idx, unsigned long ret, unsigned long *retp)
static inline void set_tsk_trace_trace(struct task_struct *tsk)
static inline void clear_tsk_trace_trace(struct task_struct *tsk)
static inline int test_tsk_trace_trace(struct task_struct *tsk)
static inline void set_tsk_trace_graph(struct task_struct *tsk)
static inline void clear_tsk_trace_graph(struct task_struct *tsk)
static inline int test_tsk_trace_graph(struct task_struct *tsk)
\n
     11 void
      7 unsigned long addr
      6 struct task_struct *tsk
      4 unsigned long *size
      4 unsigned long *off
      4 char *sym
      4 char **modname
      3 unsigned long *value
      3 unsigned int symnum
      3 int *exported
      3 char *type
      3 char *name
      3 char *module_name
      2 unsigned long old_addr
      2 struct dyn_ftrace *rec
      2 const void *start
      2 const void *end
      2 CONFIG_DYNAMIC_FTRACE
      1 unsigned long *retp
      1 unsigned long ret
      1 unsigned long ip
      1 struct task_struct *task
      1 int *idx
      1 int enabled
