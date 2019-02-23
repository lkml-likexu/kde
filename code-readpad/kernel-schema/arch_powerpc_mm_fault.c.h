
\n
static inline bool notify_page_fault(struct pt_regs *regs)
static bool store_updates_sp(unsigned int inst)
static int __bad_area_nosemaphore(struct pt_regs *regs, unsigned long address, int si_code)
static noinline int bad_area_nosemaphore(struct pt_regs *regs, unsigned long address)
static int __bad_area(struct pt_regs *regs, unsigned long address, int si_code)
static noinline int bad_area(struct pt_regs *regs, unsigned long address)
static int bad_key_fault_exception(struct pt_regs *regs, unsigned long address, int pkey)
static noinline int bad_access(struct pt_regs *regs, unsigned long address)
static int do_sigbus(struct pt_regs *regs, unsigned long address, vm_fault_t fault)
static int mm_fault_error(struct pt_regs *regs, unsigned long addr, vm_fault_t fault)
static bool bad_kernel_fault(bool is_exec, unsigned long error_code, unsigned long address)
static bool bad_stack_expansion(struct pt_regs *regs, unsigned long address, struct vm_area_struct *vma, unsigned int flags, bool *must_retry)
static bool access_error(bool is_write, bool is_exec, struct vm_area_struct *vma)
static inline void cmo_account_page_fault(void)
static void sanity_check_fault(bool is_write, bool is_user, unsigned long error_code, unsigned long address)
static int __do_page_fault(struct pt_regs *regs, unsigned long address, unsigned long error_code)
int do_page_fault(struct pt_regs *regs, unsigned long address, unsigned long error_code)
void bad_page_fault(struct pt_regs *regs, unsigned long address, int sig)
\n
     13 unsigned long address
     13 struct pt_regs *regs
      4 unsigned long error_code
      2 vm_fault_t fault
      2 struct vm_area_struct *vma
      2 int si_code
      2 bool is_write
      2 bool is_exec
      1 void
      1 unsigned long addr
      1 unsigned int inst
      1 unsigned int flags
      1 int sig
      1 int pkey
      1 bool *must_retry
      1 bool is_user
