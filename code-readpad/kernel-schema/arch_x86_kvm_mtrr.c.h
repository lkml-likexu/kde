
EXPORT_SYMBOL_GPL(kvm_mtrr_valid);
EXPORT_SYMBOL_GPL(kvm_mtrr_get_guest_memory_type);
\n
static bool msr_mtrr_valid(unsigned msr)
static bool valid_pat_type(unsigned t)
static bool valid_mtrr_type(unsigned t)
bool kvm_mtrr_valid(struct kvm_vcpu *vcpu, u32 msr, u64 data)
static bool mtrr_is_enabled(struct kvm_mtrr *mtrr_state)
static bool fixed_mtrr_is_enabled(struct kvm_mtrr *mtrr_state)
static u8 mtrr_default_type(struct kvm_mtrr *mtrr_state)
static u8 mtrr_disabled_type(struct kvm_vcpu *vcpu)
static u64 fixed_mtrr_seg_unit_size(int seg)
static bool fixed_msr_to_seg_unit(u32 msr, int *seg, int *unit)
static void fixed_mtrr_seg_unit_range(int seg, int unit, u64 *start, u64 *end)
static int fixed_mtrr_seg_unit_range_index(int seg, int unit)
static int fixed_mtrr_seg_end_range_index(int seg)
static bool fixed_msr_to_range(u32 msr, u64 *start, u64 *end)
static int fixed_msr_to_range_index(u32 msr)
static int fixed_mtrr_addr_to_seg(u64 addr)
static int fixed_mtrr_addr_seg_to_range_index(u64 addr, int seg)
static u64 fixed_mtrr_range_end_addr(int seg, int index)
static void var_mtrr_range(struct kvm_mtrr_range *range, u64 *start, u64 *end)
static void update_mtrr(struct kvm_vcpu *vcpu, u32 msr)
static bool var_mtrr_range_is_valid(struct kvm_mtrr_range *range)
static void set_var_mtrr_msr(struct kvm_vcpu *vcpu, u32 msr, u64 data)
int kvm_mtrr_set_msr(struct kvm_vcpu *vcpu, u32 msr, u64 data)
int kvm_mtrr_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata)
void kvm_vcpu_mtrr_init(struct kvm_vcpu *vcpu)
static bool mtrr_lookup_fixed_start(struct mtrr_iter *iter)
static bool match_var_range(struct mtrr_iter *iter, struct kvm_mtrr_range *range)
static void __mtrr_lookup_var_next(struct mtrr_iter *iter)
static void mtrr_lookup_var_start(struct mtrr_iter *iter)
static void mtrr_lookup_fixed_next(struct mtrr_iter *iter)
static void mtrr_lookup_var_next(struct mtrr_iter *iter)
static void mtrr_lookup_start(struct mtrr_iter *iter)
static void mtrr_lookup_init(struct mtrr_iter *iter, struct kvm_mtrr *mtrr_state, u64 start, u64 end)
static bool mtrr_lookup_okay(struct mtrr_iter *iter)
static void mtrr_lookup_next(struct mtrr_iter *iter)
u8 kvm_mtrr_get_guest_memory_type(struct kvm_vcpu *vcpu, gfn_t gfn)
bool kvm_mtrr_check_gfn_range_consistency(struct kvm_vcpu *vcpu, gfn_t gfn, int page_num)
\n
     10 struct mtrr_iter *iter
      9 struct kvm_vcpu *vcpu
      8 u32 msr
      6 int seg
      4 struct kvm_mtrr *mtrr_state
      3 u64 *start
      3 u64 *end
      3 u64 data
      3 struct kvm_mtrr_range *range
      2 unsigned t
      2 u64 addr
      2 int unit
      2 gfn_t gfn
      1 unsigned msr
      1 u64 start
      1 u64 *pdata
      1 u64 end
      1 kvm_mtrr_valid
      1 kvm_mtrr_get_guest_memory_type
      1 int *unit
      1 int *seg
      1 int page_num
      1 int index
