
\n
static inline bool p4_is_event_cascaded(u64 config)
static inline int p4_ht_config_thread(u64 config)
static inline u64 p4_set_ht_bit(u64 config)
static inline u64 p4_clear_ht_bit(u64 config)
static inline int p4_ht_active(void)
static inline int p4_ht_thread(int cpu)
static inline int p4_should_swap_ts(u64 config, int cpu)
static inline u32 p4_default_cccr_conf(int cpu)
static inline u32 p4_default_escr_conf(int cpu, int exclude_os, int exclude_usr)
\n
      5 u64 config
      4 int cpu
      1 void
      1 int exclude_usr
      1 int exclude_os
