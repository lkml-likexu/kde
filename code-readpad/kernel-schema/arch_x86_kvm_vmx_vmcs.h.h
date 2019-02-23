
\n
static inline bool is_exception_n(u32 intr_info, u8 vector)
static inline bool is_debug(u32 intr_info)
static inline bool is_breakpoint(u32 intr_info)
static inline bool is_page_fault(u32 intr_info)
static inline bool is_invalid_opcode(u32 intr_info)
static inline bool is_gp_fault(u32 intr_info)
static inline bool is_machine_check(u32 intr_info)
static inline bool is_icebp(u32 intr_info)
static inline bool is_nmi(u32 intr_info)
static inline int vmcs_field_width(unsigned long field)
static inline int vmcs_field_readonly(unsigned long field)
\n
      9 u32 intr_info
      2 unsigned long field
      1 u8 vector
