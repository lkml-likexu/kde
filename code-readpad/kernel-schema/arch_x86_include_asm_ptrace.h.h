
\n
static inline unsigned long regs_return_value(struct pt_regs *regs)
static inline void regs_set_return_value(struct pt_regs *regs, unsigned long rc)
static inline int user_mode(struct pt_regs *regs)
static inline int v8086_mode(struct pt_regs *regs)
static inline bool user_64bit_mode(struct pt_regs *regs)
extern unsigned long kernel_stack_pointer(struct pt_regs *regs)
; static inline unsigned long kernel_stack_pointer(struct pt_regs *regs)
static inline unsigned long regs_get_register(struct pt_regs *regs, unsigned int offset)
static inline int regs_within_kernel_stack(struct pt_regs *regs, unsigned long addr)
static inline unsigned long *regs_get_kernel_stack_nth_addr(struct pt_regs *regs, unsigned int n)
static inline unsigned long regs_get_kernel_stack_nth(struct pt_regs *regs, unsigned int n)
static inline unsigned long regs_get_kernel_argument(struct pt_regs *regs, unsigned int n)
\n
     12 struct pt_regs *regs
      3 unsigned int n
      1 unsigned long rc
      1 unsigned long addr
      1 unsigned int offset
