
\n
static inline void *proc_sys_poll_event(struct ctl_table_poll *poll)
struct ctl_table struct ctl_table_header static inline struct ctl_table_header *register_sysctl_table(struct ctl_table * table)
static inline struct ctl_table_header *register_sysctl_paths(const struct ctl_path *path, struct ctl_table *table)
static inline struct ctl_table_header *register_sysctl(const char *path, struct ctl_table *table)
static inline void unregister_sysctl_table(struct ctl_table_header * table)
static inline void setup_sysctl_set(struct ctl_table_set *p, struct ctl_table_root *root, int (*is_seen)
(struct ctl_table_set *)
)
\n
      2 struct ctl_table *table
      1 struct ctl_table * table
      1 struct ctl_table_set *p
      1 struct ctl_table_set *
      1 struct ctl_table_root *root
      1 struct ctl_table_poll *poll
      1 struct ctl_table_header * table
      1 int *is_seen
      1 const struct ctl_path *path
      1 const char *path
