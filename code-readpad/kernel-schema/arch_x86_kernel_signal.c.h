
\n
static void force_valid_ss(struct pt_regs *regs)
static int restore_sigcontext(struct pt_regs *regs, struct sigcontext __user *sc, unsigned long uc_flags)
int setup_sigcontext(struct sigcontext __user *sc, void __user *fpstate, struct pt_regs *regs, unsigned long mask)
static unsigned long align_sigframe(unsigned long sp)
static void __user * get_sigframe(struct k_sigaction *ka, struct pt_regs *regs, size_t frame_size, void __user **fpstate)
static int __setup_frame(int sig, struct ksignal *ksig, sigset_t *set, struct pt_regs *regs)
static int __setup_rt_frame(int sig, struct ksignal *ksig, sigset_t *set, struct pt_regs *regs)
return 0; } static unsigned long frame_uc_flags(struct pt_regs *regs)
static int __setup_rt_frame(int sig, struct ksignal *ksig, sigset_t *set, struct pt_regs *regs)
static int x32_setup_rt_frame(struct ksignal *ksig, compat_sigset_t *set, struct pt_regs *regs)
SYSCALL_DEFINE0(sigreturn)
SYSCALL_DEFINE0(rt_sigreturn)
static inline int is_ia32_compat_frame(struct ksignal *ksig)
static inline int is_ia32_frame(struct ksignal *ksig)
static inline int is_x32_frame(struct ksignal *ksig)
static int setup_rt_frame(struct ksignal *ksig, struct pt_regs *regs)
static void handle_signal(struct ksignal *ksig, struct pt_regs *regs)
static inline unsigned long get_nr_restart_syscall(const struct pt_regs *regs)
void do_signal(struct pt_regs *regs)
void signal_fault(struct pt_regs *regs, void __user *frame, char *where)
asmlinkage long sys32_x32_rt_sigreturn(void)
\n
     13 struct pt_regs *regs
      9 struct ksignal *ksig
      3 sigset_t *set
      3 int sig
      2 struct sigcontext __user *sc
      1 void __user *frame
      1 void __user **fpstate
      1 void __user *fpstate
      1 void
      1 unsigned long uc_flags
      1 unsigned long sp
      1 unsigned long mask
      1 struct k_sigaction *ka
      1 size_t frame_size
      1 sigreturn
      1 rt_sigreturn
      1 const struct pt_regs *regs
      1 compat_sigset_t *set
      1 char *where
