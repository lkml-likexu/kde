
\n
static inline int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
static inline void set_user_asce(struct mm_struct *mm)
static inline void clear_user_asce(void)
static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next, struct task_struct *tsk)
define finish_arch_post_lock_switch finish_arch_post_lock_switch static inline void finish_arch_post_lock_switch(void)
static inline void activate_mm(struct mm_struct *prev, struct mm_struct *next)
\n
      2 void
      2 struct task_struct *tsk
      2 struct mm_struct *prev
      2 struct mm_struct *next
      2 struct mm_struct *mm
