
\n
static inline int printk_get_level(const char *buffer)
static inline const char *printk_skip_level(const char *buffer)
static inline const char *printk_skip_headers(const char *buffer)
static inline void console_silent(void)
static inline void console_verbose(void)
char *log_buf_addr_get(void)
; u32 log_buf_len_get(void)
; void log_buf_vmcoreinfo_setup(void)
; void __init setup_log_buf(int early)
; __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
; void dump_stack_print_info(const char *log_lvl)
; void show_regs_print_info(const char *log_lvl)
; extern asmlinkage void dump_stack(void)
__cold; extern void printk_safe_init(void)
; extern void printk_safe_flush(void)
; extern void printk_safe_flush_on_panic(void)
; static inline __printf(1, 0)
int vprintk(const char *s, va_list args)
char *log_buf_addr_get(void)
; u32 log_buf_len_get(void)
; void log_buf_vmcoreinfo_setup(void)
; void __init setup_log_buf(int early)
; __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
; void dump_stack_print_info(const char *log_lvl)
; void show_regs_print_info(const char *log_lvl)
; extern asmlinkage void dump_stack(void)
__cold; extern void printk_safe_init(void)
; extern void printk_safe_flush(void)
; extern void printk_safe_flush_on_panic(void)
; static inline __printf(1, 0)
int vprintk(const char *s, va_list args)
return 0; } static inline __printf(1, 2)
__cold int printk(const char *s, ...)
char *log_buf_addr_get(void)
; u32 log_buf_len_get(void)
; void log_buf_vmcoreinfo_setup(void)
; void __init setup_log_buf(int early)
; __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
; void dump_stack_print_info(const char *log_lvl)
; void show_regs_print_info(const char *log_lvl)
; extern asmlinkage void dump_stack(void)
__cold; extern void printk_safe_init(void)
; extern void printk_safe_flush(void)
; extern void printk_safe_flush_on_panic(void)
; static inline __printf(1, 0)
int vprintk(const char *s, va_list args)
return 0; } static inline __printf(1, 2)
__cold int printk(const char *s, ...)
return 0; } static inline __printf(1, 2)
__cold int printk_deferred(const char *s, ...)
char *log_buf_addr_get(void)
; u32 log_buf_len_get(void)
; void log_buf_vmcoreinfo_setup(void)
; void __init setup_log_buf(int early)
; __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
; void dump_stack_print_info(const char *log_lvl)
; void show_regs_print_info(const char *log_lvl)
; extern asmlinkage void dump_stack(void)
__cold; extern void printk_safe_init(void)
; extern void printk_safe_flush(void)
; extern void printk_safe_flush_on_panic(void)
; static inline __printf(1, 0)
int vprintk(const char *s, va_list args)
return 0; } static inline __printf(1, 2)
__cold int printk(const char *s, ...)
return 0; } static inline __printf(1, 2)
__cold int printk_deferred(const char *s, ...)
return 0; } static inline int printk_ratelimit(void)
char *log_buf_addr_get(void)
; u32 log_buf_len_get(void)
; void log_buf_vmcoreinfo_setup(void)
; void __init setup_log_buf(int early)
; __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
; void dump_stack_print_info(const char *log_lvl)
; void show_regs_print_info(const char *log_lvl)
; extern asmlinkage void dump_stack(void)
__cold; extern void printk_safe_init(void)
; extern void printk_safe_flush(void)
; extern void printk_safe_flush_on_panic(void)
; static inline __printf(1, 0)
int vprintk(const char *s, va_list args)
return 0; } static inline __printf(1, 2)
__cold int printk(const char *s, ...)
return 0; } static inline __printf(1, 2)
__cold int printk_deferred(const char *s, ...)
return 0; } static inline int printk_ratelimit(void)
return 0; } static inline bool printk_timed_ratelimit(unsigned long *caller_jiffies, unsigned int interval_msec)
static inline void wake_up_klogd(void)
static inline char *log_buf_addr_get(void)
static inline u32 log_buf_len_get(void)
static inline void log_buf_vmcoreinfo_setup(void)
static inline void setup_log_buf(int early)
static inline __printf(1, 2)
void dump_stack_set_arch_desc(const char *fmt, ...)
static inline void dump_stack_print_info(const char *log_lvl)
static inline void show_regs_print_info(const char *log_lvl)
static inline void dump_stack(void)
static inline void printk_safe_init(void)
static inline void printk_safe_flush(void)
static inline void printk_safe_flush_on_panic(void)
DUMP_PREFIX_NONE, DUMP_PREFIX_ADDRESS, DUMP_PREFIX_OFFSET }; extern int hex_dump_to_buffer(const void *buf, size_t len, int rowsize, int groupsize, char *linebuf, size_t linebuflen, bool ascii)
; extern void print_hex_dump(const char *level, const char *prefix_str, int prefix_type, int rowsize, int groupsize, const void *buf, size_t len, bool ascii)
;define print_hex_dump_bytes(prefix_str, prefix_type, buf, len)
\dynamic_hex_dump(prefix_str, prefix_type, 16, 1, buf, len, true)
extern void print_hex_dump_bytes(const char *prefix_str, int prefix_type, const void *buf, size_t len)
;endifstatic inline void print_hex_dump(const char *level, const char *prefix_str, int prefix_type, int rowsize, int groupsize, const void *buf, size_t len, bool ascii)
DUMP_PREFIX_NONE, DUMP_PREFIX_ADDRESS, DUMP_PREFIX_OFFSET }; extern int hex_dump_to_buffer(const void *buf, size_t len, int rowsize, int groupsize, char *linebuf, size_t linebuflen, bool ascii)
; extern void print_hex_dump(const char *level, const char *prefix_str, int prefix_type, int rowsize, int groupsize, const void *buf, size_t len, bool ascii)
;define print_hex_dump_bytes(prefix_str, prefix_type, buf, len)
\dynamic_hex_dump(prefix_str, prefix_type, 16, 1, buf, len, true)
extern void print_hex_dump_bytes(const char *prefix_str, int prefix_type, const void *buf, size_t len)
;endifstatic inline void print_hex_dump(const char *level, const char *prefix_str, int prefix_type, int rowsize, int groupsize, const void *buf, size_t len, bool ascii)
} static inline void print_hex_dump_bytes(const char *prefix_str, int prefix_type, const void *buf, size_t len)
define print_hex_dump_debug(prefix_str, prefix_type, rowsize, \ groupsize, buf, len, ascii)
\dynamic_hex_dump(prefix_str, prefix_type, rowsize, \ groupsize, buf, len, ascii)
elif defined(DEBUG)
define print_hex_dump_debug(prefix_str, prefix_type, rowsize, \ groupsize, buf, len, ascii)
\print_hex_dump(KERN_DEBUG, prefix_str, prefix_type, rowsize, \groupsize, buf, len, ascii)
static inline void print_hex_dump_debug(const char *prefix_str, int prefix_type, int rowsize, int groupsize, const void *buf, size_t len, bool ascii)
\n
     47 void
     20 1
     13 2
     13 ...
     12 const char *s
     12 const char *log_lvl
     10 size_t len
     10 const void *buf
      8 prefix_type
      8 prefix_str
      8 len
      8 int prefix_type
      8 const char *prefix_str
      8 buf
      7 int rowsize
      7 int groupsize
      7 bool ascii
      6 int early
      6 const char *fmt
      5 va_list args
      5 0
      4 rowsize
      4 const char *level
      4 ascii
      3 \ groupsize
      3 const char *buffer
      2 true
      2 size_t linebuflen
      2 char *linebuf
      2 16
      1 unsigned long *caller_jiffies
      1 unsigned int interval_msec
      1 KERN_DEBUG
      1 \groupsize
      1 DEBUG
