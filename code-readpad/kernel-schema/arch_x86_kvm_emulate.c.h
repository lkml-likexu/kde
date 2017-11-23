
static ulong reg_read(struct x86_emulate_ctxt *ctxt, unsigned nr)
static ulong *reg_write(struct x86_emulate_ctxt *ctxt, unsigned nr)
static ulong *reg_rmw(struct x86_emulate_ctxt *ctxt, unsigned nr)
static void writeback_registers(struct x86_emulate_ctxt *ctxt)
static void invalidate_registers(struct x86_emulate_ctxt *ctxt)
static int emulator_check_intercept(struct x86_emulate_ctxt *ctxt, enum x86_intercept intercept, enum x86_intercept_stage stage)
static void assign_masked(ulong *dest, ulong src, ulong mask)
static void assign_register(unsigned long *reg, u64 val, int bytes)
static inline unsigned long ad_mask(struct x86_emulate_ctxt *ctxt)
static ulong stack_mask(struct x86_emulate_ctxt *ctxt)
static int stack_size(struct x86_emulate_ctxt *ctxt)
static inline unsigned long address_mask(struct x86_emulate_ctxt *ctxt, unsigned long reg)
static inline unsigned long register_address(struct x86_emulate_ctxt *ctxt, int reg)
static void masked_increment(ulong *reg, ulong mask, int inc)
static inline void register_address_increment(struct x86_emulate_ctxt *ctxt, int reg, int inc)
static void rsp_increment(struct x86_emulate_ctxt *ctxt, int inc)
static u32 desc_limit_scaled(struct desc_struct *desc)
static unsigned long seg_base(struct x86_emulate_ctxt *ctxt, int seg)
static int emulate_exception(struct x86_emulate_ctxt *ctxt, int vec, u32 error, bool valid)
static int emulate_db(struct x86_emulate_ctxt *ctxt)
static int emulate_gp(struct x86_emulate_ctxt *ctxt, int err)
static int emulate_ss(struct x86_emulate_ctxt *ctxt, int err)
static int emulate_ud(struct x86_emulate_ctxt *ctxt)
static int emulate_ts(struct x86_emulate_ctxt *ctxt, int err)
static int emulate_de(struct x86_emulate_ctxt *ctxt)
static int emulate_nm(struct x86_emulate_ctxt *ctxt)
static u16 get_segment_selector(struct x86_emulate_ctxt *ctxt, unsigned seg)
static void set_segment_selector(struct x86_emulate_ctxt *ctxt, u16 selector, unsigned seg)
static unsigned insn_alignment(struct x86_emulate_ctxt *ctxt, unsigned size)
static __always_inline int __linearize(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, unsigned *max_size, unsigned size, bool write, bool fetch, enum x86emul_mode mode, ulong *linear)
static int linearize(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, unsigned size, bool write, ulong *linear)
static inline int assign_eip(struct x86_emulate_ctxt *ctxt, ulong dst, enum x86emul_mode mode)
static inline int assign_eip_near(struct x86_emulate_ctxt *ctxt, ulong dst)
static int assign_eip_far(struct x86_emulate_ctxt *ctxt, ulong dst, const struct desc_struct *cs_desc)
static inline int jmp_rel(struct x86_emulate_ctxt *ctxt, int rel)
static int linear_read_system(struct x86_emulate_ctxt *ctxt, ulong linear, void *data, unsigned size)
static int linear_write_system(struct x86_emulate_ctxt *ctxt, ulong linear, void *data, unsigned int size)
static int segmented_read_std(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, void *data, unsigned size)
static int segmented_write_std(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, void *data, unsigned int size)
static int __do_insn_fetch_bytes(struct x86_emulate_ctxt *ctxt, int op_size)
static __always_inline int do_insn_fetch_bytes(struct x86_emulate_ctxt *ctxt, unsigned size)
static void *decode_register(struct x86_emulate_ctxt *ctxt, u8 modrm_reg, int byteop)
static int read_descriptor(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, u16 *size, unsigned long *address, int op_bytes)
static int em_bsf_c(struct x86_emulate_ctxt *ctxt)
static int em_bsr_c(struct x86_emulate_ctxt *ctxt)
static __always_inline u8 test_cc(unsigned int condition, unsigned long flags)
static void fetch_register_operand(struct operand *op)
static void read_sse_reg(struct x86_emulate_ctxt *ctxt, sse128_t *data, int reg)
static void write_sse_reg(struct x86_emulate_ctxt *ctxt, sse128_t *data, int reg)
static void read_mmx_reg(struct x86_emulate_ctxt *ctxt, u64 *data, int reg)
static void write_mmx_reg(struct x86_emulate_ctxt *ctxt, u64 *data, int reg)
static int em_fninit(struct x86_emulate_ctxt *ctxt)
static int em_fnstcw(struct x86_emulate_ctxt *ctxt)
static int em_fnstsw(struct x86_emulate_ctxt *ctxt)
static void decode_register_operand(struct x86_emulate_ctxt *ctxt, struct operand *op)
static void adjust_modrm_seg(struct x86_emulate_ctxt *ctxt, int base_reg)
static int decode_modrm(struct x86_emulate_ctxt *ctxt, struct operand *op)
static int decode_abs(struct x86_emulate_ctxt *ctxt, struct operand *op)
static void fetch_bit_operand(struct x86_emulate_ctxt *ctxt)
static int read_emulated(struct x86_emulate_ctxt *ctxt, unsigned long addr, void *dest, unsigned size)
static int segmented_read(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, void *data, unsigned size)
static int segmented_write(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, const void *data, unsigned size)
static int segmented_cmpxchg(struct x86_emulate_ctxt *ctxt, struct segmented_address addr, const void *orig_data, const void *data, unsigned size)
static int pio_in_emulated(struct x86_emulate_ctxt *ctxt, unsigned int size, unsigned short port, void *dest)
static int read_interrupt_descriptor(struct x86_emulate_ctxt *ctxt, u16 index, struct desc_struct *desc)
static void get_descriptor_table_ptr(struct x86_emulate_ctxt *ctxt, u16 selector, struct desc_ptr *dt)
static int get_descriptor_ptr(struct x86_emulate_ctxt *ctxt, u16 selector, ulong *desc_addr_p)
static int read_segment_descriptor(struct x86_emulate_ctxt *ctxt, u16 selector, struct desc_struct *desc, ulong *desc_addr_p)
static int write_segment_descriptor(struct x86_emulate_ctxt *ctxt, u16 selector, struct desc_struct *desc)
static int __load_segment_descriptor(struct x86_emulate_ctxt *ctxt, u16 selector, int seg, u8 cpl, enum x86_transfer_type transfer, struct desc_struct *desc)
static int load_segment_descriptor(struct x86_emulate_ctxt *ctxt, u16 selector, int seg)
static void write_register_operand(struct operand *op)
static int writeback(struct x86_emulate_ctxt *ctxt, struct operand *op)
static int push(struct x86_emulate_ctxt *ctxt, void *data, int bytes)
static int em_push(struct x86_emulate_ctxt *ctxt)
static int emulate_pop(struct x86_emulate_ctxt *ctxt, void *dest, int len)
static int em_pop(struct x86_emulate_ctxt *ctxt)
static int emulate_popf(struct x86_emulate_ctxt *ctxt, void *dest, int len)
static int em_popf(struct x86_emulate_ctxt *ctxt)
static int em_enter(struct x86_emulate_ctxt *ctxt)
static int em_leave(struct x86_emulate_ctxt *ctxt)
static int em_push_sreg(struct x86_emulate_ctxt *ctxt)
static int em_pop_sreg(struct x86_emulate_ctxt *ctxt)
static int em_pusha(struct x86_emulate_ctxt *ctxt)
static int em_pushf(struct x86_emulate_ctxt *ctxt)
static int em_popa(struct x86_emulate_ctxt *ctxt)
static int __emulate_int_real(struct x86_emulate_ctxt *ctxt, int irq)
int emulate_int_real(struct x86_emulate_ctxt *ctxt, int irq)
static int emulate_int(struct x86_emulate_ctxt *ctxt, int irq)
static int emulate_iret_real(struct x86_emulate_ctxt *ctxt)
static int em_iret(struct x86_emulate_ctxt *ctxt)
static int em_jmp_far(struct x86_emulate_ctxt *ctxt)
static int em_jmp_abs(struct x86_emulate_ctxt *ctxt)
static int em_call_near_abs(struct x86_emulate_ctxt *ctxt)
static int em_cmpxchg8b(struct x86_emulate_ctxt *ctxt)
static int em_ret(struct x86_emulate_ctxt *ctxt)
static int em_ret_far(struct x86_emulate_ctxt *ctxt)
static int em_ret_far_imm(struct x86_emulate_ctxt *ctxt)
static int em_cmpxchg(struct x86_emulate_ctxt *ctxt)
static int em_lseg(struct x86_emulate_ctxt *ctxt)
static int emulator_has_longmode(struct x86_emulate_ctxt *ctxt)
static void rsm_set_desc_flags(struct desc_struct *desc, u32 flags)
static int rsm_load_seg_32(struct x86_emulate_ctxt *ctxt, u64 smbase, int n)
static int rsm_load_seg_64(struct x86_emulate_ctxt *ctxt, u64 smbase, int n)
static int rsm_enter_protected_mode(struct x86_emulate_ctxt *ctxt, u64 cr0, u64 cr3, u64 cr4)
static int rsm_load_state_32(struct x86_emulate_ctxt *ctxt, u64 smbase)
static int rsm_load_state_64(struct x86_emulate_ctxt *ctxt, u64 smbase)
static int em_rsm(struct x86_emulate_ctxt *ctxt)
static void setup_syscalls_segments(struct x86_emulate_ctxt *ctxt, struct desc_struct *cs, struct desc_struct *ss)
static bool vendor_intel(struct x86_emulate_ctxt *ctxt)
static bool em_syscall_is_enabled(struct x86_emulate_ctxt *ctxt)
static int em_syscall(struct x86_emulate_ctxt *ctxt)
static int em_sysenter(struct x86_emulate_ctxt *ctxt)
static int em_sysexit(struct x86_emulate_ctxt *ctxt)
static bool emulator_bad_iopl(struct x86_emulate_ctxt *ctxt)
static bool emulator_io_port_access_allowed(struct x86_emulate_ctxt *ctxt, u16 port, u16 len)
static bool emulator_io_permited(struct x86_emulate_ctxt *ctxt, u16 port, u16 len)
static void string_registers_quirk(struct x86_emulate_ctxt *ctxt)
static void save_state_to_tss16(struct x86_emulate_ctxt *ctxt, struct tss_segment_16 *tss)
static int load_state_from_tss16(struct x86_emulate_ctxt *ctxt, struct tss_segment_16 *tss)
static int task_switch_16(struct x86_emulate_ctxt *ctxt, u16 tss_selector, u16 old_tss_sel, ulong old_tss_base, struct desc_struct *new_desc)
static void save_state_to_tss32(struct x86_emulate_ctxt *ctxt, struct tss_segment_32 *tss)
static int load_state_from_tss32(struct x86_emulate_ctxt *ctxt, struct tss_segment_32 *tss)
static int task_switch_32(struct x86_emulate_ctxt *ctxt, u16 tss_selector, u16 old_tss_sel, ulong old_tss_base, struct desc_struct *new_desc)
static int emulator_do_task_switch(struct x86_emulate_ctxt *ctxt, u16 tss_selector, int idt_index, int reason, bool has_error_code, u32 error_code)
int emulator_task_switch(struct x86_emulate_ctxt *ctxt, u16 tss_selector, int idt_index, int reason, bool has_error_code, u32 error_code)
static void string_addr_inc(struct x86_emulate_ctxt *ctxt, int reg, struct operand *op)
static int em_das(struct x86_emulate_ctxt *ctxt)
static int em_aam(struct x86_emulate_ctxt *ctxt)
static int em_aad(struct x86_emulate_ctxt *ctxt)
static int em_call(struct x86_emulate_ctxt *ctxt)
static int em_call_far(struct x86_emulate_ctxt *ctxt)
static int em_ret_near_imm(struct x86_emulate_ctxt *ctxt)
static int em_xchg(struct x86_emulate_ctxt *ctxt)
static int em_imul_3op(struct x86_emulate_ctxt *ctxt)
static int em_cwd(struct x86_emulate_ctxt *ctxt)
static int em_rdpid(struct x86_emulate_ctxt *ctxt)
static int em_rdtsc(struct x86_emulate_ctxt *ctxt)
static int em_rdpmc(struct x86_emulate_ctxt *ctxt)
static int em_mov(struct x86_emulate_ctxt *ctxt)
static int em_movbe(struct x86_emulate_ctxt *ctxt)
static int em_cr_write(struct x86_emulate_ctxt *ctxt)
static int em_dr_write(struct x86_emulate_ctxt *ctxt)
static int em_wrmsr(struct x86_emulate_ctxt *ctxt)
static int em_rdmsr(struct x86_emulate_ctxt *ctxt)
static int em_store_sreg(struct x86_emulate_ctxt *ctxt, int segment)
static int em_mov_rm_sreg(struct x86_emulate_ctxt *ctxt)
static int em_mov_sreg_rm(struct x86_emulate_ctxt *ctxt)
static int em_sldt(struct x86_emulate_ctxt *ctxt)
static int em_lldt(struct x86_emulate_ctxt *ctxt)
static int em_str(struct x86_emulate_ctxt *ctxt)
static int em_ltr(struct x86_emulate_ctxt *ctxt)
static int em_invlpg(struct x86_emulate_ctxt *ctxt)
static int em_clts(struct x86_emulate_ctxt *ctxt)
static int em_hypercall(struct x86_emulate_ctxt *ctxt)
static int emulate_store_desc_ptr(struct x86_emulate_ctxt *ctxt, void (*get)
(struct x86_emulate_ctxt *ctxt, struct desc_ptr *ptr)
)
static int em_sgdt(struct x86_emulate_ctxt *ctxt)
static int em_sidt(struct x86_emulate_ctxt *ctxt)
static int em_lgdt_lidt(struct x86_emulate_ctxt *ctxt, bool lgdt)
static int em_lgdt(struct x86_emulate_ctxt *ctxt)
static int em_lidt(struct x86_emulate_ctxt *ctxt)
static int em_smsw(struct x86_emulate_ctxt *ctxt)
static int em_lmsw(struct x86_emulate_ctxt *ctxt)
static int em_loop(struct x86_emulate_ctxt *ctxt)
static int em_jcxz(struct x86_emulate_ctxt *ctxt)
static int em_in(struct x86_emulate_ctxt *ctxt)
static int em_out(struct x86_emulate_ctxt *ctxt)
static int em_cli(struct x86_emulate_ctxt *ctxt)
static int em_sti(struct x86_emulate_ctxt *ctxt)
static int em_cpuid(struct x86_emulate_ctxt *ctxt)
static int em_sahf(struct x86_emulate_ctxt *ctxt)
static int em_lahf(struct x86_emulate_ctxt *ctxt)
static int em_bswap(struct x86_emulate_ctxt *ctxt)
static int em_clflush(struct x86_emulate_ctxt *ctxt)
static int em_movsxd(struct x86_emulate_ctxt *ctxt)
static int check_fxsr(struct x86_emulate_ctxt *ctxt)
static size_t __fxstate_size(int nregs)
static inline size_t fxstate_size(struct x86_emulate_ctxt *ctxt)
static int em_fxsave(struct x86_emulate_ctxt *ctxt)
static noinline int fxregs_fixup(struct fxregs_state *fx_state, const size_t used_size)
static int em_fxrstor(struct x86_emulate_ctxt *ctxt)
static bool valid_cr(int nr)
static int check_cr_read(struct x86_emulate_ctxt *ctxt)
static int check_cr_write(struct x86_emulate_ctxt *ctxt)
static int check_dr7_gd(struct x86_emulate_ctxt *ctxt)
static int check_dr_read(struct x86_emulate_ctxt *ctxt)
static int check_dr_write(struct x86_emulate_ctxt *ctxt)
static int check_svme(struct x86_emulate_ctxt *ctxt)
static int check_svme_pa(struct x86_emulate_ctxt *ctxt)
static int check_rdtsc(struct x86_emulate_ctxt *ctxt)
static int check_rdpmc(struct x86_emulate_ctxt *ctxt)
static int check_perm_in(struct x86_emulate_ctxt *ctxt)
static int check_perm_out(struct x86_emulate_ctxt *ctxt)
static unsigned imm_size(struct x86_emulate_ctxt *ctxt)
static int decode_imm(struct x86_emulate_ctxt *ctxt, struct operand *op, unsigned size, bool sign_extension)
static int decode_operand(struct x86_emulate_ctxt *ctxt, struct operand *op, unsigned d)
int x86_decode_insn(struct x86_emulate_ctxt *ctxt, void *insn, int insn_len)
bool x86_page_table_writing_insn(struct x86_emulate_ctxt *ctxt)
static bool string_insn_completed(struct x86_emulate_ctxt *ctxt)
static int flush_pending_x87_faults(struct x86_emulate_ctxt *ctxt)
static void fetch_possible_mmx_operand(struct x86_emulate_ctxt *ctxt, struct operand *op)
static int fastop(struct x86_emulate_ctxt *ctxt, void (*fop)
(struct fastop *)
)
void init_decode_cache(struct x86_emulate_ctxt *ctxt)
int x86_emulate_insn(struct x86_emulate_ctxt *ctxt)
void emulator_invalidate_register_cache(struct x86_emulate_ctxt *ctxt)
void emulator_writeback_register_cache(struct x86_emulate_ctxt *ctxt)
bool emulator_can_use_gpa(struct x86_emulate_ctxt *ctxt)
 197 struct x86_emulate_ctxt *ctxt
  11 unsigned size
  10 struct operand *op
   8 struct segmented_address addr
   7 u16 selector
   7 int reg
   6 void *data
   6 struct desc_struct *desc
   4 void *dest
   4 u64 smbase
   4 u16 tss_selector
   3 unsigned nr
   3 unsigned int size
   3 ulong dst
   3 int seg
   3 int irq
   3 int inc
   3 int err
   2 unsigned seg
   2 ulong old_tss_base
   2 ulong mask
   2 ulong linear
   2 ulong *linear
   2 ulong *desc_addr_p
   2 u64 *data
   2 u32 error_code
   2 u16 port
   2 u16 old_tss_sel
   2 u16 len
   2 struct tss_segment_32 *tss
   2 struct tss_segment_16 *tss
   2 struct desc_struct *new_desc
   2 sse128_t *data
   2 int reason
   2 int n
   2 int len
   2 int idt_index
   2 int bytes
   2 enum x86emul_mode mode
   2 const void *data
   2 bool write
   2 bool has_error_code
   1 void *insn
   1 void *get
   1 void *fop
   1 unsigned short port
   1 unsigned long reg
   1 unsigned long flags
   1 unsigned long addr
   1 unsigned long *reg
   1 unsigned long *address
   1 unsigned int condition
   1 unsigned d
   1 unsigned *max_size
   1 ulong src
   1 ulong *reg
   1 ulong *dest
   1 u8 modrm_reg
   1 u8 cpl
   1 u64 val
   1 u64 cr4
   1 u64 cr3
   1 u64 cr0
   1 u32 flags
   1 u32 error
   1 u16 index
   1 u16 *size
   1 struct fxregs_state *fx_state
   1 struct fastop *
   1 struct desc_struct *ss
   1 struct desc_struct *cs
   1 struct desc_ptr *ptr
   1 struct desc_ptr *dt
   1 int vec
   1 int segment
   1 int rel
   1 int op_size
   1 int op_bytes
   1 int nregs
   1 int nr
   1 int insn_len
   1 int byteop
   1 int base_reg
   1 enum x86_transfer_type transfer
   1 enum x86_intercept_stage stage
   1 enum x86_intercept intercept
   1 const void *orig_data
   1 const struct desc_struct *cs_desc
   1 const size_t used_size
   1 bool valid
   1 bool sign_extension
   1 bool lgdt
   1 bool fetch
