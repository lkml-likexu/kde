
\n
static inline unsigned long compat_psr_to_pstate(const unsigned long psr)
static inline unsigned long pstate_to_compat_psr(const unsigned long pstate)
static inline bool in_syscall(struct pt_regs const *regs)
static inline void forget_syscall(struct pt_regs *regs)
static inline u64 regs_get_register(struct pt_regs *regs, unsigned int offset)
static inline unsigned long pt_regs_read_reg(const struct pt_regs *regs, int r)
static inline void pt_regs_write_reg(struct pt_regs *regs, int r, unsigned long val)
static inline unsigned long kernel_stack_pointer(struct pt_regs *regs)
static inline unsigned long regs_return_value(struct pt_regs *regs)
static inline void procedure_link_pointer_set(struct pt_regs *regs, unsigned long val)
\n
      6 struct pt_regs *regs
      2 unsigned long val
      2 int r
      1 unsigned int offset
      1 struct pt_regs const *regs
      1 const unsigned long pstate
      1 const unsigned long psr
      1 const struct pt_regs *regs
