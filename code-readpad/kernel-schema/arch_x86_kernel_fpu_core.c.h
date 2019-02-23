
EXPORT_SYMBOL_GPL(kernel_fpu_begin);
EXPORT_SYMBOL_GPL(kernel_fpu_end);
EXPORT_SYMBOL_GPL(fpu__save);
EXPORT_SYMBOL_GPL(fpstate_init);
EXPORT_SYMBOL_GPL(fpu__initialize);
EXPORT_SYMBOL_GPL(fpu__restore);
\n
static void kernel_fpu_disable(void)
static void kernel_fpu_enable(void)
static bool kernel_fpu_disabled(void)
static bool interrupted_kernel_fpu_idle(void)
static bool interrupted_user_mode(void)
bool irq_fpu_usable(void)
static void __kernel_fpu_begin(void)
static void __kernel_fpu_end(void)
void kernel_fpu_begin(void)
void kernel_fpu_end(void)
void fpu__save(struct fpu *fpu)
static inline void fpstate_init_fstate(struct fregs_state *fp)
void fpstate_init(union fpregs_state *state)
int fpu__copy(struct fpu *dst_fpu, struct fpu *src_fpu)
void fpu__initialize(struct fpu *fpu)
void fpu__prepare_read(struct fpu *fpu)
void fpu__prepare_write(struct fpu *fpu)
void fpu__restore(struct fpu *fpu)
void fpu__drop(struct fpu *fpu)
static inline void copy_init_fpstate_to_fpregs(void)
void fpu__clear(struct fpu *fpu)
int fpu__exception_code(struct fpu *fpu, int trap_nr)
\n
     11 void
      8 struct fpu *fpu
      1 union fpregs_state *state
      1 struct fregs_state *fp
      1 struct fpu *src_fpu
      1 struct fpu *dst_fpu
      1 kernel_fpu_end
      1 kernel_fpu_begin
      1 int trap_nr
      1 fpu__save
      1 fpu__restore
      1 fpu__initialize
      1 fpstate_init
