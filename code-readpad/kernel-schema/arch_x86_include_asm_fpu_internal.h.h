
\n
static __always_inline __pure bool use_xsaveopt(void)
static __always_inline __pure bool use_xsave(void)
static __always_inline __pure bool use_fxsr(void)
static inline void fpstate_init_xstate(struct xregs_state *xsave)
static inline void fpstate_init_fxstate(struct fxregs_state *fx)
static inline int copy_fregs_to_user(struct fregs_state __user *fx)
static inline int copy_fxregs_to_user(struct fxregs_state __user *fx)
static inline void copy_kernel_to_fxregs(struct fxregs_state *fx)
static inline int copy_user_to_fxregs(struct fxregs_state __user *fx)
static inline void copy_kernel_to_fregs(struct fregs_state *fx)
static inline int copy_user_to_fregs(struct fregs_state __user *fx)
static inline void copy_fxregs_to_kernel(struct fpu *fpu)
static inline void copy_xregs_to_kernel_booting(struct xregs_state *xstate)
static inline void copy_kernel_to_xregs_booting(struct xregs_state *xstate)
static inline void copy_xregs_to_kernel(struct xregs_state *xstate)
static inline void copy_kernel_to_xregs(struct xregs_state *xstate, u64 mask)
static inline int copy_xregs_to_user(struct xregs_state __user *buf)
static inline int copy_user_to_xregs(struct xregs_state __user *buf, u64 mask)
static inline int copy_fpregs_to_fpstate(struct fpu *fpu)
static inline void __copy_kernel_to_fpregs(union fpregs_state *fpstate, u64 mask)
static inline void copy_kernel_to_fpregs(union fpregs_state *fpstate)
static inline void __cpu_invalidate_fpregs_state(void)
static inline void __fpu_invalidate_fpregs_state(struct fpu *fpu)
static inline int fpregs_state_valid(struct fpu *fpu, unsigned int cpu)
static inline void fpregs_deactivate(struct fpu *fpu)
static inline void fpregs_activate(struct fpu *fpu)
static inline void switch_fpu_prepare(struct fpu *old_fpu, int cpu)
static inline void switch_fpu_finish(struct fpu *new_fpu, int cpu)
static inline void user_fpu_begin(void)
static inline u64 xgetbv(u32 index)
static inline void xsetbv(u32 index, u64 value)
\n
      6 struct fpu *fpu
      5 void
      4 struct xregs_state *xstate
      3 u64 mask
      2 union fpregs_state *fpstate
      2 u32 index
      2 struct xregs_state __user *buf
      2 struct fxregs_state __user *fx
      2 struct fxregs_state *fx
      2 struct fregs_state __user *fx
      2 int cpu
      1 unsigned int cpu
      1 u64 value
      1 struct xregs_state *xsave
      1 struct fregs_state *fx
      1 struct fpu *old_fpu
      1 struct fpu *new_fpu
