
\n
static inline unsigned long mpx_bd_size_bytes(struct mm_struct *mm)
static inline unsigned long mpx_bt_size_bytes(struct mm_struct *mm)
static unsigned long mpx_mmap(unsigned long len)
static int mpx_insn_decode(struct insn *insn, struct pt_regs *regs)
int mpx_fault_info(struct mpx_fault_info *info, struct pt_regs *regs)
static __user void *mpx_get_bounds_dir(void)
int mpx_enable_management(void)
int mpx_disable_management(void)
static int mpx_cmpxchg_bd_entry(struct mm_struct *mm, unsigned long *curval, unsigned long __user *addr, unsigned long old_val, unsigned long new_val)
static int allocate_bt(struct mm_struct *mm, long __user *bd_entry)
static int do_mpx_bt_fault(void)
int mpx_handle_bd_fault(void)
static int mpx_resolve_fault(long __user *addr, int write)
static unsigned long mpx_bd_entry_to_bt_addr(struct mm_struct *mm, unsigned long bd_entry)
static int get_user_bd_entry(struct mm_struct *mm, unsigned long *bd_entry_ret, long __user *bd_entry_ptr)
static int get_bt_addr(struct mm_struct *mm, long __user *bd_entry_ptr, unsigned long *bt_addr_result)
static inline int bt_entry_size_bytes(struct mm_struct *mm)
static unsigned long mpx_get_bt_entry_offset_bytes(struct mm_struct *mm, unsigned long addr)
static inline unsigned long bd_entry_virt_space(struct mm_struct *mm)
static noinline int zap_bt_entries_mapping(struct mm_struct *mm, unsigned long bt_addr, unsigned long start_mapping, unsigned long end_mapping)
static unsigned long mpx_get_bd_entry_offset(struct mm_struct *mm, unsigned long addr)
static int unmap_entire_bt(struct mm_struct *mm, long __user *bd_entry, unsigned long bt_addr)
static int try_unmap_single_bt(struct mm_struct *mm, unsigned long start, unsigned long end)
static int mpx_unmap_tables(struct mm_struct *mm, unsigned long start, unsigned long end)
void mpx_notify_unmap(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long start, unsigned long end)
unsigned long mpx_unmapped_area_check(unsigned long addr, unsigned long len, unsigned long flags)
\n
     16 struct mm_struct *mm
      5 void
      3 unsigned long start
      3 unsigned long end
      3 unsigned long addr
      2 unsigned long len
      2 unsigned long bt_addr
      2 struct pt_regs *regs
      2 long __user *bd_entry_ptr
      2 long __user *bd_entry
      1 unsigned long __user *addr
      1 unsigned long start_mapping
      1 unsigned long old_val
      1 unsigned long new_val
      1 unsigned long flags
      1 unsigned long end_mapping
      1 unsigned long *curval
      1 unsigned long *bt_addr_result
      1 unsigned long *bd_entry_ret
      1 unsigned long bd_entry
      1 struct vm_area_struct *vma
      1 struct mpx_fault_info *info
      1 struct insn *insn
      1 long __user *addr
      1 int write
