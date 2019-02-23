
\n
static inline int cpucap_default_scope(const struct arm64_cpu_capabilities *cap)
static inline bool cpucap_late_cpu_optional(const struct arm64_cpu_capabilities *cap)
static inline bool cpucap_late_cpu_permitted(const struct arm64_cpu_capabilities *cap)
static inline bool cpucap_multi_entry_cap_matches(const struct arm64_cpu_capabilities *entry, int scope)
static inline void cpucap_multi_entry_cap_cpu_enable(const struct arm64_cpu_capabilities *entry)
static inline bool cpu_have_feature(unsigned int num)
static inline bool __cpus_have_const_cap(int num)
static inline bool cpus_have_cap(unsigned int num)
static inline bool cpus_have_const_cap(int num)
static inline void cpus_set_cap(unsigned int num)
static inline int __attribute_const__ cpuid_feature_extract_signed_field_width(u64 features, int field, int width)
static inline int __attribute_const__ cpuid_feature_extract_signed_field(u64 features, int field)
static inline unsigned int __attribute_const__ cpuid_feature_extract_unsigned_field_width(u64 features, int field, int width)
static inline unsigned int __attribute_const__ cpuid_feature_extract_unsigned_field(u64 features, int field)
static inline u64 arm64_ftr_mask(const struct arm64_ftr_bits *ftrp)
static inline u64 arm64_ftr_reg_user_value(const struct arm64_ftr_reg *reg)
static inline int __attribute_const__ cpuid_feature_extract_field_width(u64 features, int field, int width, bool sign)
static inline int __attribute_const__ cpuid_feature_extract_field(u64 features, int field, bool sign)
static inline s64 arm64_ftr_value(const struct arm64_ftr_bits *ftrp, u64 val)
static inline bool id_aa64mmfr0_mixed_endian_el0(u64 mmfr0)
static inline bool id_aa64pfr0_32bit_el0(u64 pfr0)
static inline bool id_aa64pfr0_sve(u64 pfr0)
static inline bool cpu_supports_mixed_endian_el0(void)
static inline bool system_supports_32bit_el0(void)
static inline bool system_supports_4kb_granule(void)
static inline bool system_supports_64kb_granule(void)
static inline bool system_supports_16kb_granule(void)
static inline bool system_supports_mixed_endian_el0(void)
static inline bool system_supports_mixed_endian(void)
static inline bool system_supports_fpsimd(void)
static inline bool system_uses_ttbr0_pan(void)
static inline bool system_supports_sve(void)
static inline bool system_supports_cnp(void)
static inline bool system_supports_address_auth(void)
static inline bool system_supports_generic_auth(void)
static inline int arm64_get_ssbd_state(void)
static inline u32 id_aa64mmfr0_parange_to_phys_shift(int parange)
\n
     14 void
      6 u64 features
      6 int field
      3 unsigned int num
      3 int width
      3 const struct arm64_cpu_capabilities *cap
      2 u64 pfr0
      2 int num
      2 const struct arm64_ftr_bits *ftrp
      2 const struct arm64_cpu_capabilities *entry
      2 bool sign
      1 u64 val
      1 u64 mmfr0
      1 int scope
      1 int parange
      1 const struct arm64_ftr_reg *reg
