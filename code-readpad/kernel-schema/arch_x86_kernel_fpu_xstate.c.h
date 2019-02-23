
EXPORT_SYMBOL_GPL(cpu_has_xfeatures);
EXPORT_SYMBOL_GPL(get_xsave_addr);
\n
static const char *xfeature_names[] =void fpu__xstate_clear_all_cpu_caps(void)
int cpu_has_xfeatures(u64 xfeatures_needed, const char **feature_name)
static int xfeature_is_supervisor(int xfeature_nr)
static int xfeature_is_user(int xfeature_nr)
void fpstate_sanitize_xstate(struct fpu *fpu)
void fpu__init_cpu_xstate(void)
static int xfeature_enabled(enum xfeature xfeature)
static void __init setup_xstate_features(void)
static void __init print_xstate_feature(u64 xstate_mask)
static void __init print_xstate_features(void)
static int xfeature_is_aligned(int xfeature_nr)
static void __init setup_xstate_comp(void)
static void __init print_xstate_offset_size(void)
static void __init setup_init_fpu_buf(void)
static int xfeature_uncompacted_offset(int xfeature_nr)
static int xfeature_size(int xfeature_nr)
int using_compacted_format(void)
int validate_xstate_header(const struct xstate_header *hdr)
static void __xstate_dump_leaves(void)
static void check_xstate_against_struct(int nr)
static void do_extra_xstate_size_checks(void)
static unsigned int __init get_xsaves_size(void)
static unsigned int __init get_xsave_size(void)
static bool is_supported_xstate_size(unsigned int test_xstate_size)
static int init_xstate_size(void)
static void fpu__init_disable_system_xstate(void)
void __init fpu__init_system_xstate(void)
void fpu__resume_cpu(void)
static void *__raw_xsave_addr(struct xregs_state *xsave, int xstate_feature_mask)
return (void *)
xsave + xstate_comp_offsets[feature_nr]; }void *get_xsave_addr(struct xregs_state *xsave, int xstate_feature)
const void *get_xsave_field_ptr(int xsave_state)
define NR_VALID_PKRU_BITS (CONFIG_NR_PROTECTION_KEYS * 2)
define PKRU_VALID_MASK (NR_VALID_PKRU_BITS - 1)
int arch_set_user_pkey_access(struct task_struct *tsk, int pkey, unsigned long init_val)
static inline bool xfeatures_mxcsr_quirk(u64 xfeatures)
static inline void __copy_xstate_to_kernel(void *kbuf, const void *data, unsigned int offset, unsigned int size, unsigned int size_total)
int copy_xstate_to_kernel(void *kbuf, struct xregs_state *xsave, unsigned int offset_start, unsigned int size_total)
static inline int __copy_xstate_to_user(void __user *ubuf, const void *data, unsigned int offset, unsigned int size, unsigned int size_total)
int copy_xstate_to_user(void __user *ubuf, struct xregs_state *xsave, unsigned int offset_start, unsigned int size_total)
int copy_kernel_to_xstate(struct xregs_state *xsave, const void *kbuf)
int copy_user_to_xstate(struct xregs_state *xsave, const void __user *ubuf)
\n
     16 void
      6 struct xregs_state *xsave
      5 int xfeature_nr
      4 unsigned int size_total
      2 void __user *ubuf
      2 void *kbuf
      2 unsigned int size
      2 unsigned int offset_start
      2 unsigned int offset
      2 const void *data
      1 void *
      1 unsigned long init_val
      1 unsigned int test_xstate_size
      1 u64 xstate_mask
      1 u64 xfeatures_needed
      1 u64 xfeatures
      1 struct task_struct *tsk
      1 struct fpu *fpu
      1 NR_VALID_PKRU_BITS - 1
      1 int xstate_feature_mask
      1 int xstate_feature
      1 int xsave_state
      1 int pkey
      1 int nr
      1 get_xsave_addr
      1 enum xfeature xfeature
      1 cpu_has_xfeatures
      1 const void __user *ubuf
      1 const void *kbuf
      1 const struct xstate_header *hdr
      1 const char **feature_name
      1 CONFIG_NR_PROTECTION_KEYS * 2
