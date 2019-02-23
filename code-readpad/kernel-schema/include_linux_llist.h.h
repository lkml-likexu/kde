
\n
static inline void init_llist_head(struct llist_head *list)
static inline bool llist_empty(const struct llist_head *head)
static inline struct llist_node *llist_next(struct llist_node *node)
extern bool llist_add_batch(struct llist_node *new_first, struct llist_node *new_last, struct llist_head *head)
;static inline bool llist_add(struct llist_node *new, struct llist_head *head)
static inline struct llist_node *llist_del_all(struct llist_head *head)
\n
      3 struct llist_head *head
      1 struct llist_node *node
      1 struct llist_node *new_last
      1 struct llist_node *new_first
      1 struct llist_node *new
      1 struct llist_head *list
      1 const struct llist_head *head
