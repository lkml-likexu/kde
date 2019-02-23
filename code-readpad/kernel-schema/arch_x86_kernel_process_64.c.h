
EXPORT_SYMBOL_GPL(save_fsgs_for_kvm);
EXPORT_SYMBOL_GPL(start_thread);
EXPORT_SYMBOL_GPL(set_personality_ia32);
\n
void __show_regs(struct pt_regs *regs, enum show_regs_mode mode)
void release_thread(struct task_struct *dead_task)
static __always_inline void save_base_legacy(struct task_struct *prev_p, unsigned short selector, enum which_selector which)
static __always_inline void save_fsgs(struct task_struct *task)
void save_fsgs_for_kvm(void)
static __always_inline void loadseg(enum which_selector which, unsigned short sel)
static __always_inline void load_seg_legacy(unsigned short prev_index, unsigned long prev_base, unsigned short next_index, unsigned long next_base, enum which_selector which)
static __always_inline void x86_fsgsbase_load(struct thread_struct *prev, struct thread_struct *next)
static unsigned long x86_fsgsbase_read_task(struct task_struct *task, unsigned short selector)
unsigned long x86_fsbase_read_task(struct task_struct *task)
unsigned long x86_gsbase_read_task(struct task_struct *task)
void x86_fsbase_write_task(struct task_struct *task, unsigned long fsbase)
void x86_gsbase_write_task(struct task_struct *task, unsigned long gsbase)
int copy_thread_tls(unsigned long clone_flags, unsigned long sp, unsigned long arg, struct task_struct *p, unsigned long tls)
static void start_thread_common(struct pt_regs *regs, unsigned long new_ip, unsigned long new_sp, unsigned int _cs, unsigned int _ss, unsigned int _ds)
void start_thread(struct pt_regs *regs, unsigned long new_ip, unsigned long new_sp)
void compat_start_thread(struct pt_regs *regs, u32 new_ip, u32 new_sp)
__visible __notrace_funcgraph struct task_struct * __switch_to(struct task_struct *prev_p, struct task_struct *next_p)
void set_personality_64bit(void)
static void __set_personality_x32(void)
static void __set_personality_ia32(void)
void set_personality_ia32(bool x32)
static long prctl_map_vdso(const struct vdso_image *image, unsigned long addr)
long do_arch_prctl_64(struct task_struct *task, int option, unsigned long arg2)
SYSCALL_DEFINE2(arch_prctl, int, option, unsigned long, arg2)
COMPAT_SYSCALL_DEFINE2(arch_prctl, int, option, unsigned long, arg2)
unsigned long KSTK_ESP(struct task_struct *task)
\n
      8 struct task_struct *task
      4 void
      4 struct pt_regs *regs
      3 enum which_selector which
      2 unsigned short selector
      2 unsigned long new_sp
      2 unsigned long new_ip
      2 unsigned long
      2 struct task_struct *prev_p
      2 option
      2 int
      2 arg2
      2 arch_prctl
      1 unsigned short sel
      1 unsigned short prev_index
      1 unsigned short next_index
      1 unsigned long tls
      1 unsigned long sp
      1 unsigned long prev_base
      1 unsigned long next_base
      1 unsigned long gsbase
      1 unsigned long fsbase
      1 unsigned long clone_flags
      1 unsigned long arg2
      1 unsigned long arg
      1 unsigned long addr
      1 unsigned int _ss
      1 unsigned int _ds
      1 unsigned int _cs
      1 u32 new_sp
      1 u32 new_ip
      1 struct thread_struct *prev
      1 struct thread_struct *next
      1 struct task_struct *p
      1 struct task_struct *next_p
      1 struct task_struct *dead_task
      1 start_thread
      1 set_personality_ia32
      1 save_fsgs_for_kvm
      1 int option
      1 enum show_regs_mode mode
      1 const struct vdso_image *image
      1 bool x32
