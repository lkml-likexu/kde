
\n
static int ia32_restore_sigcontext(struct pt_regs *regs, struct sigcontext_32 __user *sc)
asmlinkage long sys32_sigreturn(void)
asmlinkage long sys32_rt_sigreturn(void)
static int ia32_setup_sigcontext(struct sigcontext_32 __user *sc, void __user *fpstate, struct pt_regs *regs, unsigned int mask)
static void __user *get_sigframe(struct ksignal *ksig, struct pt_regs *regs, size_t frame_size, void __user **fpstate)
int ia32_setup_frame(int sig, struct ksignal *ksig, compat_sigset_t *set, struct pt_regs *regs)
int ia32_setup_rt_frame(int sig, struct ksignal *ksig, compat_sigset_t *set, struct pt_regs *regs)
\n
      5 struct pt_regs *regs
      3 struct ksignal *ksig
      2 void
      2 struct sigcontext_32 __user *sc
      2 int sig
      2 compat_sigset_t *set
      1 void __user **fpstate
      1 void __user *fpstate
      1 unsigned int mask
      1 size_t frame_size
