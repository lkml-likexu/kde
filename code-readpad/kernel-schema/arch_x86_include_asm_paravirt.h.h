
\n
static inline unsigned long long paravirt_sched_clock(void)
static inline u64 paravirt_steal_clock(int cpu)
static inline void slow_down_io(void)
static inline void __flush_tlb(void)
static inline void __flush_tlb_global(void)
static inline void __flush_tlb_one_user(unsigned long addr)
static inline void flush_tlb_others(const struct cpumask *cpumask, const struct flush_tlb_info *info)
static inline void paravirt_tlb_remove_table(struct mmu_gather *tlb, void *table)
static inline void paravirt_arch_exit_mmap(struct mm_struct *mm)
static inline void load_sp0(unsigned long sp0)
static inline void __cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
static inline unsigned long paravirt_get_debugreg(int reg)
static inline unsigned long paravirt_get_debugreg(int reg)
return PVOP_CALL1(unsigned long, cpu.get_debugreg, reg)
; }define get_debugreg(var, reg)
var = paravirt_get_debugreg(reg)
static inline void set_debugreg(unsigned long val, int reg)
static inline unsigned long read_cr0(void)
static inline void write_cr0(unsigned long x)
static inline unsigned long read_cr2(void)
static inline void write_cr2(unsigned long x)
static inline unsigned long __read_cr3(void)
static inline void write_cr3(unsigned long x)
static inline void __write_cr4(unsigned long x)
static inline unsigned long read_cr8(void)
static inline void write_cr8(unsigned long x)
static inline void arch_safe_halt(void)
static inline void halt(void)
static inline void wbinvd(void)
static inline u64 paravirt_read_msr(unsigned msr)
static inline void paravirt_write_msr(unsigned msr, unsigned low, unsigned high)
static inline u64 paravirt_read_msr_safe(unsigned msr, int *err)
static inline int paravirt_write_msr_safe(unsigned msr, unsigned low, unsigned high)
static inline void wrmsrl(unsigned msr, u64 val)
static inline int rdmsrl_safe(unsigned msr, unsigned long long *p)
static inline unsigned long long paravirt_read_pmc(int counter)
static inline void paravirt_alloc_ldt(struct desc_struct *ldt, unsigned entries)
static inline void paravirt_free_ldt(struct desc_struct *ldt, unsigned entries)
static inline void load_TR_desc(void)
static inline void load_TR_desc(void)
PVOP_VCALL0(cpu.load_tr_desc)
; } static inline void load_gdt(const struct desc_ptr *dtr)
static inline void load_TR_desc(void)
PVOP_VCALL0(cpu.load_tr_desc)
; } static inline void load_gdt(const struct desc_ptr *dtr)
PVOP_VCALL1(cpu.load_gdt, dtr)
; } static inline void load_idt(const struct desc_ptr *dtr)
static inline void load_TR_desc(void)
PVOP_VCALL0(cpu.load_tr_desc)
; } static inline void load_gdt(const struct desc_ptr *dtr)
PVOP_VCALL1(cpu.load_gdt, dtr)
; } static inline void load_idt(const struct desc_ptr *dtr)
PVOP_VCALL1(cpu.load_idt, dtr)
; } static inline void set_ldt(const void *addr, unsigned entries)
static inline void load_TR_desc(void)
PVOP_VCALL0(cpu.load_tr_desc)
; } static inline void load_gdt(const struct desc_ptr *dtr)
PVOP_VCALL1(cpu.load_gdt, dtr)
; } static inline void load_idt(const struct desc_ptr *dtr)
PVOP_VCALL1(cpu.load_idt, dtr)
; } static inline void set_ldt(const void *addr, unsigned entries)
PVOP_VCALL2(cpu.set_ldt, addr, entries)
; } static inline unsigned long paravirt_store_tr(void)
define store_tr(tr)
((tr)
= paravirt_store_tr()
)
static inline void load_TLS(struct thread_struct *t, unsigned cpu)
static inline void load_gs_index(unsigned int gs)
static inline void write_ldt_entry(struct desc_struct *dt, int entry, const void *desc)
static inline void write_gdt_entry(struct desc_struct *dt, int entry, void *desc, int type)
static inline void write_idt_entry(gate_desc *dt, int entry, const gate_desc *g)
static inline void write_idt_entry(gate_desc *dt, int entry, const gate_desc *g)
PVOP_VCALL3(cpu.write_idt_entry, dt, entry, g)
; } static inline void set_iopl_mask(unsigned mask)
static inline void paravirt_activate_mm(struct mm_struct *prev, struct mm_struct *next)
static inline void paravirt_arch_dup_mmap(struct mm_struct *oldmm, struct mm_struct *mm)
static inline int paravirt_pgd_alloc(struct mm_struct *mm)
static inline void paravirt_pgd_free(struct mm_struct *mm, pgd_t *pgd)
static inline void paravirt_alloc_pte(struct mm_struct *mm, unsigned long pfn)
static inline void paravirt_alloc_pte(struct mm_struct *mm, unsigned long pfn)
PVOP_VCALL2(mmu.alloc_pte, mm, pfn)
; } static inline void paravirt_release_pte(unsigned long pfn)
static inline void paravirt_alloc_pmd(struct mm_struct *mm, unsigned long pfn)
static inline void paravirt_release_pmd(unsigned long pfn)
static inline void paravirt_alloc_pud(struct mm_struct *mm, unsigned long pfn)
static inline void paravirt_alloc_pud(struct mm_struct *mm, unsigned long pfn)
PVOP_VCALL2(mmu.alloc_pud, mm, pfn)
; } static inline void paravirt_release_pud(unsigned long pfn)
static inline void paravirt_alloc_p4d(struct mm_struct *mm, unsigned long pfn)
static inline void paravirt_release_p4d(unsigned long pfn)
static inline pte_t __pte(pteval_t val)
static inline pteval_t pte_val(pte_t pte)
static inline pgd_t __pgd(pgdval_t val)
static inline pgdval_t pgd_val(pgd_t pgd)
define__HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION static inline pte_t ptep_modify_prot_start(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline void ptep_modify_prot_commit(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte)
static inline void set_pte(pte_t *ptep, pte_t pte)
static inline void set_pte_at(struct mm_struct *mm, unsigned long addr, pte_t *ptep, pte_t pte)
static inline void set_pmd(pmd_t *pmdp, pmd_t pmd)
static inline pmd_t __pmd(pmdval_t val)
static inline pmdval_t pmd_val(pmd_t pmd)
static inline void set_pud(pud_t *pudp, pud_t pud)
if (sizeof(pudval_t)
> sizeof(long)
)
PVOP_VCALL3(mmu.set_pud, pudp, val, (u64)
val >> 32)
;else PVOP_VCALL2(mmu.set_pud, pudp, val)
; } static inline pud_t __pud(pudval_t val)
static inline pudval_t pud_val(pud_t pud)
static inline void pud_clear(pud_t *pudp)
static inline void set_p4d(p4d_t *p4dp, p4d_t p4d)
static inline p4d_t __p4d(p4dval_t val)
static inline p4dval_t p4d_val(p4d_t p4d)
static inline void __set_pgd(pgd_t *pgdp, pgd_t pgd)
static inline void p4d_clear(p4d_t *p4dp)
static inline void set_pte_atomic(pte_t *ptep, pte_t pte)
static inline void pte_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline void pmd_clear(pmd_t *pmdp)
static inline void pmd_clear(pmd_t *pmdp)
PVOP_VCALL1(mmu.pmd_clear, pmdp)
; } static inline void set_pte_atomic(pte_t *ptep, pte_t pte)
static inline void pte_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
static inline void pmd_clear(pmd_t *pmdp)
define__HAVE_ARCH_START_CONTEXT_SWITCH static inline void arch_start_context_switch(struct task_struct *prev)
static inline void arch_end_context_switch(struct task_struct *next)
define__HAVE_ARCH_ENTER_LAZY_MMU_MODE static inline void arch_enter_lazy_mmu_mode(void)
static inline void arch_leave_lazy_mmu_mode(void)
static inline void arch_flush_lazy_mmu_mode(void)
static inline void __set_fixmap(unsignedidx, phys_addr_t phys, pgprot_t flags)
static __always_inline void pv_queued_spin_lock_slowpath(struct qspinlock *lock, u32 val)
static __always_inline void pv_queued_spin_unlock(struct qspinlock *lock)
static __always_inline void pv_wait(u8 *ptr, u8 val)
static __always_inline void pv_kick(int cpu)
static __always_inline bool pv_vcpu_is_preempted(long cpu)
static inline notrace unsigned long arch_local_save_flags(void)
static inline notrace void arch_local_irq_restore(unsigned long f)
static inline notrace void arch_local_irq_disable(void)
static inline notrace void arch_local_irq_enable(void)
static inline notrace unsigned long arch_local_irq_save(void)
static inline void paravirt_arch_dup_mmap(struct mm_struct *oldmm, struct mm_struct *mm)
static inline void paravirt_arch_exit_mmap(struct mm_struct *mm)
\n
     24 void
     17 struct mm_struct *mm
     10 unsigned long pfn
      8 pte_t *ptep
      7 const struct desc_ptr *dtr
      6 unsigned msr
      6 unsigned long addr
      6 pte_t pte
      5 unsigned long x
      5 dtr
      4 unsigned entries
      4 pmd_t *pmdp
      4 int entry
      4 cpu.load_tr_desc
      3 reg
      3 int reg
      3 cpu.load_gdt
      2 val
      2 unsigned low
      2 unsigned high
      2 tr
      2 struct qspinlock *lock
      2 struct mm_struct *oldmm
      2 struct desc_struct *ldt
      2 struct desc_struct *dt
      2 pud_t *pudp
      2 pud_t pud
      2 pudp
      2 pmd_t pmd
      2 pgd_t pgd
      2 pfn
      2 p4d_t *p4dp
      2 p4d_t p4d
      2 mmu.set_pud
      2 mm
      2 int cpu
      2 gate_desc *dt
      2 cpu.load_idt
      2 const void *addr
      2 const gate_desc *g
      1 void *table
      1 void *desc
      1 var
      1 unsigned mask
      1 unsigned long val
      1 unsigned long sp0
      1 unsigned long long *p
      1 unsigned long f
      1 unsigned long
      1 unsigned int gs
      1 unsigned int *edx
      1 unsigned int *ecx
      1 unsigned int *ebx
      1 unsigned int *eax
      1 unsignedidx
      1 unsigned cpu
      1 u8 val
      1 u8 *ptr
      1 u64 val
      1 u64
      1 u32 val
      1 struct thread_struct *t
      1 struct task_struct *prev
      1 struct task_struct *next
      1 struct mmu_gather *tlb
      1 struct mm_struct *prev
      1 struct mm_struct *next
      1 sizeofpudval_t
      1 pudval_t val
      1 pteval_t val
      1 pmdval_t val
      1 pmdp
      1 phys_addr_t phys
      1 pgprot_t flags
      1 pgdval_t val
      1 pgd_t *pgdp
      1 pgd_t *pgd
      1 p4dval_t val
      1 mmu.pmd_clear
      1 mmu.alloc_pud
      1 mmu.alloc_pte
      1 long cpu
      1 long
      1 int type
      1 int *err
      1 int counter
      1 g
      1 entry
      1 entries
      1 dt
      1 cpu.write_idt_entry
      1 cpu.set_ldt
      1 cpu.get_debugreg
      1 const void *desc
      1 const struct flush_tlb_info *info
      1 const struct cpumask *cpumask
      1 addr
      1 
