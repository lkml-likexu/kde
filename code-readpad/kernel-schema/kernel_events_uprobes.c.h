
EXPORT_SYMBOL_GPL(uprobe_unregister);
EXPORT_SYMBOL_GPL(uprobe_register);
static bool valid_vma(struct vm_area_struct *vma, bool is_register)
static unsigned long offset_to_vaddr(struct vm_area_struct *vma, loff_t offset)
static loff_t vaddr_to_offset(struct vm_area_struct *vma, unsigned long vaddr)
static int __replace_page(struct vm_area_struct *vma, unsigned long addr, struct page *old_page, struct page *new_page)
bool __weak is_swbp_insn(uprobe_opcode_t *insn)
bool __weak is_trap_insn(uprobe_opcode_t *insn)
static void copy_from_page(struct page *page, unsigned long vaddr, void *dst, int len)
static void copy_to_page(struct page *page, unsigned long vaddr, const void *src, int len)
static int verify_opcode(struct page *page, unsigned long vaddr, uprobe_opcode_t *new_opcode)
int uprobe_write_opcode(struct arch_uprobe *auprobe, struct mm_struct *mm, unsigned long vaddr, uprobe_opcode_t opcode)
int __weak set_swbp(struct arch_uprobe *auprobe, struct mm_struct *mm, unsigned long vaddr)
int __weak set_orig_insn(struct arch_uprobe *auprobe, struct mm_struct *mm, unsigned long vaddr)
static struct uprobe *get_uprobe(struct uprobe *uprobe)
static void put_uprobe(struct uprobe *uprobe)
static int match_uprobe(struct uprobe *l, struct uprobe *r)
static struct uprobe *__find_uprobe(struct inode *inode, loff_t offset)
static struct uprobe *find_uprobe(struct inode *inode, loff_t offset)
static struct uprobe *__insert_uprobe(struct uprobe *uprobe)
static struct uprobe *insert_uprobe(struct uprobe *uprobe)
static struct uprobe *alloc_uprobe(struct inode *inode, loff_t offset)
static void consumer_add(struct uprobe *uprobe, struct uprobe_consumer *uc)
static bool consumer_del(struct uprobe *uprobe, struct uprobe_consumer *uc)
static int __copy_insn(struct address_space *mapping, struct file *filp, void *insn, int nbytes, loff_t offset)
static int copy_insn(struct uprobe *uprobe, struct file *filp)
static int prepare_uprobe(struct uprobe *uprobe, struct file *file, struct mm_struct *mm, unsigned long vaddr)
static inline bool consumer_filter(struct uprobe_consumer *uc, enum uprobe_filter_ctx ctx, struct mm_struct *mm)
static bool filter_chain(struct uprobe *uprobe, enum uprobe_filter_ctx ctx, struct mm_struct *mm)
static int install_breakpoint(struct uprobe *uprobe, struct mm_struct *mm, struct vm_area_struct *vma, unsigned long vaddr)
static int remove_breakpoint(struct uprobe *uprobe, struct mm_struct *mm, unsigned long vaddr)
static inline bool uprobe_is_active(struct uprobe *uprobe)
static inline bool uprobe_is_active(struct uprobe *uprobe)
return !RB_EMPTY_NODE(&uprobe->rb_node)
; }static void delete_uprobe(struct uprobe *uprobe)
static inline struct map_info *free_map_info(struct map_info *info)
static struct map_info * build_map_info(struct address_space *mapping, loff_t offset, bool is_register)
static int register_for_each_vma(struct uprobe *uprobe, struct uprobe_consumer *new)
static void __uprobe_unregister(struct uprobe *uprobe, struct uprobe_consumer *uc)
void uprobe_unregister(struct inode *inode, loff_t offset, struct uprobe_consumer *uc)
static int __uprobe_register(struct inode *inode, loff_t offset, struct uprobe_consumer *uc)
int uprobe_register(struct inode *inode, loff_t offset, struct uprobe_consumer *uc)
int uprobe_apply(struct inode *inode, loff_t offset, struct uprobe_consumer *uc, bool add)
static int unapply_uprobe(struct uprobe *uprobe, struct mm_struct *mm)
static struct rb_node * find_node_in_range(struct inode *inode, loff_t min, loff_t max)
static void build_probe_list(struct inode *inode, struct vm_area_struct *vma, unsigned long start, unsigned long end, struct list_head *head)
int uprobe_mmap(struct vm_area_struct *vma)
static bool vma_has_uprobes(struct vm_area_struct *vma, unsigned long start, unsigned long end)
void uprobe_munmap(struct vm_area_struct *vma, unsigned long start, unsigned long end)
static int xol_add_vma(struct mm_struct *mm, struct xol_area *area)
static struct xol_area *__create_xol_area(unsigned long vaddr)
static struct xol_area *get_xol_area(void)
void uprobe_clear_state(struct mm_struct *mm)
void uprobe_start_dup_mmap(void)
void uprobe_end_dup_mmap(void)
void uprobe_dup_mmap(struct mm_struct *oldmm, struct mm_struct *newmm)
static unsigned long xol_take_insn_slot(struct xol_area *area)
static unsigned long xol_get_insn_slot(struct uprobe *uprobe)
static void xol_free_insn_slot(struct task_struct *tsk)
void __weak arch_uprobe_copy_ixol(struct page *page, unsigned long vaddr, void *src, unsigned long len)
unsigned long __weak uprobe_get_swbp_addr(struct pt_regs *regs)
unsigned long uprobe_get_trap_addr(struct pt_regs *regs)
static struct return_instance *free_ret_instance(struct return_instance *ri)
void uprobe_free_utask(struct task_struct *t)
static struct uprobe_task *get_utask(void)
static int dup_utask(struct task_struct *t, struct uprobe_task *o_utask)
static void uprobe_warn(struct task_struct *t, const char *msg)
static void dup_xol_work(struct callback_head *work)
void uprobe_copy_process(struct task_struct *t, unsigned long flags)
static unsigned long get_trampoline_vaddr(void)
static void cleanup_return_instances(struct uprobe_task *utask, bool chained, struct pt_regs *regs)
static void prepare_uretprobe(struct uprobe *uprobe, struct pt_regs *regs)
static int pre_ssout(struct uprobe *uprobe, struct pt_regs *regs, unsigned long bp_vaddr)
bool uprobe_deny_signal(void)
static void mmf_recalc_uprobes(struct mm_struct *mm)
static int is_trap_at_addr(struct mm_struct *mm, unsigned long vaddr)
static struct uprobe *find_active_uprobe(unsigned long bp_vaddr, int *is_swbp)
static void handler_chain(struct uprobe *uprobe, struct pt_regs *regs)
static void handle_uretprobe_chain(struct return_instance *ri, struct pt_regs *regs)
static struct return_instance *find_next_ret_chain(struct return_instance *ri)
static void handle_trampoline(struct pt_regs *regs)
bool __weak arch_uprobe_ignore(struct arch_uprobe *aup, struct pt_regs *regs)
bool __weak arch_uretprobe_is_alive(struct return_instance *ret, enum rp_check ctx, struct pt_regs *regs)
static void handle_swbp(struct pt_regs *regs)
static void handle_singlestep(struct uprobe_task *utask, struct pt_regs *regs)
void uprobe_notify_resume(struct pt_regs *regs)
int uprobe_pre_sstep_notifier(struct pt_regs *regs)
int uprobe_post_sstep_notifier(struct pt_regs *regs)
static int __init init_uprobes(void)
  21 struct uprobe *uprobe
  15 struct pt_regs *regs
  13 unsigned long vaddr
  13 struct mm_struct *mm
  10 loff_t offset
   9 struct vm_area_struct *vma
   9 struct inode *inode
   8 struct uprobe_consumer *uc
   7 void
   4 struct task_struct *t
   4 struct page *page
   3 unsigned long start
   3 unsigned long end
   3 struct return_instance *ri
   3 struct arch_uprobe *auprobe
   2 uprobe_opcode_t *insn
   2 unsigned long bp_vaddr
   2 struct xol_area *area
   2 struct uprobe_task *utask
   2 struct file *filp
   2 struct address_space *mapping
   2 int len
   2 enum uprobe_filter_ctx ctx
   2 bool is_register
   1 void *src
   1 void *insn
   1 void *dst
   1 uprobe_unregister
   1 uprobe_register
   1 uprobe_opcode_t opcode
   1 uprobe_opcode_t *new_opcode
   1 unsigned long len
   1 unsigned long flags
   1 unsigned long addr
   1 struct uprobe_task *o_utask
   1 struct uprobe_consumer *new
   1 struct uprobe *r
   1 struct uprobe *l
   1 struct task_struct *tsk
   1 struct return_instance *ret
   1 struct page *old_page
   1 struct page *new_page
   1 struct mm_struct *oldmm
   1 struct mm_struct *newmm
   1 struct map_info *info
   1 struct list_head *head
   1 struct file *file
   1 struct callback_head *work
   1 struct arch_uprobe *aup
   1 loff_t min
   1 loff_t max
   1 int nbytes
   1 int *is_swbp
   1 enum rp_check ctx
   1 const void *src
   1 const char *msg
   1 bool chained
   1 bool add
   1 &uprobe->rb_node
