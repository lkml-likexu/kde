
\n
int regset_fpregs_active(struct task_struct *target, const struct user_regset *regset)
int regset_xregset_fpregs_active(struct task_struct *target, const struct user_regset *regset)
int xfpregs_get(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, void *kbuf, void __user *ubuf)
int xfpregs_set(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, const void *kbuf, const void __user *ubuf)
int xstateregs_get(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, void *kbuf, void __user *ubuf)
int xstateregs_set(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, const void *kbuf, const void __user *ubuf)
static inline unsigned short twd_i387_to_fxsr(unsigned short twd)
static inline u32 twd_fxsr_to_i387(struct fxregs_state *fxsave)
void convert_from_fxsr(struct user_i387_ia32_struct *env, struct task_struct *tsk)
int fpregs_get(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, void *kbuf, void __user *ubuf)
int fpregs_set(struct task_struct *target, const struct user_regset *regset, unsigned int pos, unsigned int count, const void *kbuf, const void __user *ubuf)
int dump_fpu(struct pt_regs *regs, struct user_i387_struct *ufpu)
\n
      8 struct task_struct *target
      8 const struct user_regset *regset
      6 unsigned int pos
      6 unsigned int count
      3 void __user *ubuf
      3 void *kbuf
      3 const void __user *ubuf
      3 const void *kbuf
      1 unsigned short twd
      1 struct user_i387_struct *ufpu
      1 struct user_i387_ia32_struct *env
      1 struct task_struct *tsk
      1 struct pt_regs *regs
      1 struct fxregs_state *fxsave
