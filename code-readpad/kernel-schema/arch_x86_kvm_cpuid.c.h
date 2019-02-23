
EXPORT_SYMBOL_GPL(kvm_mpx_supported);
EXPORT_SYMBOL_GPL(cpuid_query_maxphyaddr);
EXPORT_SYMBOL_GPL(kvm_find_cpuid_entry);
EXPORT_SYMBOL_GPL(kvm_cpuid);
EXPORT_SYMBOL_GPL(kvm_emulate_cpuid);
\n
static u32 xstate_required_size(u64 xstate_bv, bool compacted)
bool kvm_mpx_supported(void)
u64 kvm_supported_xcr0(void)
int kvm_update_cpuid(struct kvm_vcpu *vcpu)
static int is_efer_nx(void)
static void cpuid_fix_nx_cap(struct kvm_vcpu *vcpu)
int cpuid_query_maxphyaddr(struct kvm_vcpu *vcpu)
int kvm_vcpu_ioctl_set_cpuid(struct kvm_vcpu *vcpu, struct kvm_cpuid *cpuid, struct kvm_cpuid_entry __user *entries)
int kvm_vcpu_ioctl_set_cpuid2(struct kvm_vcpu *vcpu, struct kvm_cpuid2 *cpuid, struct kvm_cpuid_entry2 __user *entries)
int kvm_vcpu_ioctl_get_cpuid2(struct kvm_vcpu *vcpu, struct kvm_cpuid2 *cpuid, struct kvm_cpuid_entry2 __user *entries)
static void cpuid_mask(u32 *word, int wordnum)
static void do_cpuid_1_ent(struct kvm_cpuid_entry2 *entry, u32 function, u32 index)
static int __do_cpuid_ent_emulated(struct kvm_cpuid_entry2 *entry, u32 func, u32 index, int *nent, int maxnent)
static inline int __do_cpuid_ent(struct kvm_cpuid_entry2 *entry, u32 function, u32 index, int *nent, int maxnent)
static int do_cpuid_ent(struct kvm_cpuid_entry2 *entry, u32 func, u32 idx, int *nent, int maxnent, unsigned int type)
static bool is_centaur_cpu(const struct kvm_cpuid_param *param)
static bool sanity_check_entries(struct kvm_cpuid_entry2 __user *entries, __u32 num_entries, unsigned int ioctl_type)
int kvm_dev_ioctl_get_cpuid(struct kvm_cpuid2 *cpuid, struct kvm_cpuid_entry2 __user *entries, unsigned int type)
static int move_to_next_stateful_cpuid_entry(struct kvm_vcpu *vcpu, int i)
static int is_matching_cpuid_entry(struct kvm_cpuid_entry2 *e, u32 function, u32 index)
struct kvm_cpuid_entry2 *kvm_find_cpuid_entry(struct kvm_vcpu *vcpu, u32 function, u32 index)
static struct kvm_cpuid_entry2* check_cpuid_limit(struct kvm_vcpu *vcpu, u32 function, u32 index)
bool kvm_cpuid(struct kvm_vcpu *vcpu, u32 *eax, u32 *ebx, u32 *ecx, u32 *edx, bool check_limit)
int kvm_emulate_cpuid(struct kvm_vcpu *vcpu)
\n
     11 struct kvm_vcpu *vcpu
      6 u32 index
      5 u32 function
      4 struct kvm_cpuid_entry2 __user *entries
      4 struct kvm_cpuid_entry2 *entry
      3 void
      3 struct kvm_cpuid2 *cpuid
      3 int *nent
      3 int maxnent
      2 unsigned int type
      2 u32 func
      1 unsigned int ioctl_type
      1 u64 xstate_bv
      1 u32 *word
      1 __u32 num_entries
      1 u32 idx
      1 u32 *edx
      1 u32 *ecx
      1 u32 *ebx
      1 u32 *eax
      1 struct kvm_cpuid_entry __user *entries
      1 struct kvm_cpuid_entry2 *e
      1 struct kvm_cpuid *cpuid
      1 kvm_mpx_supported
      1 kvm_find_cpuid_entry
      1 kvm_emulate_cpuid
      1 kvm_cpuid
      1 int wordnum
      1 int i
      1 cpuid_query_maxphyaddr
      1 const struct kvm_cpuid_param *param
      1 bool compacted
      1 bool check_limit
