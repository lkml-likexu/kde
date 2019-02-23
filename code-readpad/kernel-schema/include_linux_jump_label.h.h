
\n
static inline unsigned long jump_entry_code(const struct jump_entry *entry)
static inline unsigned long jump_entry_target(const struct jump_entry *entry)
static inline struct static_key *jump_entry_key(const struct jump_entry *entry)
static inline unsigned long jump_entry_code(const struct jump_entry *entry)
static inline unsigned long jump_entry_target(const struct jump_entry *entry)
static inline struct static_key *jump_entry_key(const struct jump_entry *entry)
static inline bool jump_entry_is_branch(const struct jump_entry *entry)
static inline bool jump_entry_is_init(const struct jump_entry *entry)
static inline void jump_entry_set_init(struct jump_entry *entry)
static __always_inline bool static_key_false(struct static_key *key)
static __always_inline bool static_key_true(struct static_key *key)
static inline int static_key_count(struct static_key *key)
static __always_inline void jump_label_init(void)
static __always_inline bool static_key_false(struct static_key *key)
static __always_inline bool static_key_true(struct static_key *key)
static inline void static_key_slow_inc(struct static_key *key)
static inline void static_key_slow_dec(struct static_key *key)
static inline int jump_label_text_reserved(void *start, void *end)
static inline int jump_label_apply_nops(struct module *mod)
static inline void static_key_enable(struct static_key *key)
static inline void static_key_disable(struct static_key *key)
\n
      9 struct static_key *key
      8 const struct jump_entry *entry
      1 void *start
      1 void *end
      1 void
      1 struct module *mod
      1 struct jump_entry *entry
