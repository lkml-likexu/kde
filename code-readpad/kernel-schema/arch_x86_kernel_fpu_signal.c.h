
\n
static inline int check_for_xstate(struct fxregs_state __user *buf, void __user *fpstate, struct _fpx_sw_bytes *fx_sw)
static inline int save_fsave_header(struct task_struct *tsk, void __user *buf)
static inline int save_xstate_epilog(void __user *buf, int ia32_frame)
static inline int copy_fpregs_to_sigframe(struct xregs_state __user *buf)
int copy_fpstate_to_sigframe(void __user *buf, void __user *buf_fx, int size)
static inline void sanitize_restored_xstate(struct task_struct *tsk, struct user_i387_ia32_struct *ia32_env, u64 xfeatures, int fx_only)
static inline int copy_user_to_fpregs_zeroing(void __user *buf, u64 xbv, int fx_only)
static int __fpu__restore_sig(void __user *buf, void __user *buf_fx, int size)
static inline int xstate_sigframe_size(void)
int fpu__restore_sig(void __user *buf, int ia32_frame)
unsigned long fpu__alloc_mathframe(unsigned long sp, int ia32_frame, unsigned long *buf_fx, unsigned long *size)
return sp; }void fpu__init_prepare_fx_sw_frame(void)
\n
      6 void __user *buf
      3 int ia32_frame
      2 void __user *buf_fx
      2 void
      2 struct task_struct *tsk
      2 int size
      2 int fx_only
      1 void __user *fpstate
      1 unsigned long sp
      1 unsigned long *size
      1 unsigned long *buf_fx
      1 u64 xfeatures
      1 u64 xbv
      1 struct xregs_state __user *buf
      1 struct user_i387_ia32_struct *ia32_env
      1 struct fxregs_state __user *buf
      1 struct _fpx_sw_bytes *fx_sw
