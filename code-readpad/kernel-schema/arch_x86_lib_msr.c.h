
\n
struct msr *msrs_alloc(void)
void msrs_free(struct msr *msrs)
int msr_read(u32 msr, struct msr *m)
int msr_write(u32 msr, struct msr *m)
static inline int __flip_bit(u32 msr, u8 bit, bool set)
int msr_set_bit(u32 msr, u8 bit)
int msr_clear_bit(u32 msr, u8 bit)
void do_trace_write_msr(unsigned int msr, u64 val, int failed)
void do_trace_read_msr(unsigned int msr, u64 val, int failed)
void do_trace_rdpmc(unsigned counter, u64 val, int failed)
\n
      5 u32 msr
      3 u8 bit
      3 u64 val
      3 int failed
      2 unsigned int msr
      2 struct msr *m
      1 void
      1 unsigned counter
      1 struct msr *msrs
      1 bool set
