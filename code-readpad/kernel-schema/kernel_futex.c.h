
\n
static int __init setup_fail_futex(char *str)
static bool should_fail_futex(bool fshared)
static int __init fail_futex_debugfs(void)
static inline bool should_fail_futex(bool fshared)
static inline void futex_get_mm(union futex_key *key)
static inline void hb_waiters_inc(struct futex_hash_bucket *hb)
static inline void hb_waiters_dec(struct futex_hash_bucket *hb)
static inline int hb_waiters_pending(struct futex_hash_bucket *hb)
static struct futex_hash_bucket *hash_futex(union futex_key *key)
static inline int match_futex(union futex_key *key1, union futex_key *key2)
static void get_futex_key_refs(union futex_key *key)
static void drop_futex_key_refs(union futex_key *key)
static int get_futex_key(u32 __user *uaddr, int fshared, union futex_key *key, enum futex_access rw)
static inline void put_futex_key(union futex_key *key)
static int fault_in_user_writeable(u32 __user *uaddr)
static struct futex_q *futex_top_waiter(struct futex_hash_bucket *hb, union futex_key *key)
static int cmpxchg_futex_value_locked(u32 *curval, u32 __user *uaddr, u32 uval, u32 newval)
static int get_futex_value_locked(u32 *dest, u32 __user *from)
static int refill_pi_state_cache(void)
static struct futex_pi_state *alloc_pi_state(void)
static void get_pi_state(struct futex_pi_state *pi_state)
static void put_pi_state(struct futex_pi_state *pi_state)
void exit_pi_state_list(struct task_struct *curr)
static int attach_to_pi_state(u32 __user *uaddr, u32 uval, struct futex_pi_state *pi_state, struct futex_pi_state **ps)
static int handle_exit_race(u32 __user *uaddr, u32 uval, struct task_struct *tsk)
static int attach_to_pi_owner(u32 __user *uaddr, u32 uval, union futex_key *key, struct futex_pi_state **ps)
static int lookup_pi_state(u32 __user *uaddr, u32 uval, struct futex_hash_bucket *hb, union futex_key *key, struct futex_pi_state **ps)
static int lock_pi_update_atomic(u32 __user *uaddr, u32 uval, u32 newval)
static int futex_lock_pi_atomic(u32 __user *uaddr, struct futex_hash_bucket *hb, union futex_key *key, struct futex_pi_state **ps, struct task_struct *task, int set_waiters)
static void __unqueue_futex(struct futex_q *q)
static void mark_wake_futex(struct wake_q_head *wake_q, struct futex_q *q)
static int wake_futex_pi(u32 __user *uaddr, u32 uval, struct futex_pi_state *pi_state)
static inline void double_lock_hb(struct futex_hash_bucket *hb1, struct futex_hash_bucket *hb2)
static inline void double_unlock_hb(struct futex_hash_bucket *hb1, struct futex_hash_bucket *hb2)
static int futex_wake(u32 __user *uaddr, unsigned int flags, int nr_wake, u32 bitset)
static int futex_atomic_op_inuser(unsigned int encoded_op, u32 __user *uaddr)
static int futex_wake_op(u32 __user *uaddr1, unsigned int flags, u32 __user *uaddr2, int nr_wake, int nr_wake2, int op)
static inline void requeue_futex(struct futex_q *q, struct futex_hash_bucket *hb1, struct futex_hash_bucket *hb2, union futex_key *key2)
static inline void requeue_pi_wake_futex(struct futex_q *q, union futex_key *key, struct futex_hash_bucket *hb)
static int futex_proxy_trylock_atomic(u32 __user *pifutex, struct futex_hash_bucket *hb1, struct futex_hash_bucket *hb2, union futex_key *key1, union futex_key *key2, struct futex_pi_state **ps, int set_waiters)
static int futex_requeue(u32 __user *uaddr1, unsigned int flags, u32 __user *uaddr2, int nr_wake, int nr_requeue, u32 *cmpval, int requeue_pi)
static inline struct futex_hash_bucket *queue_lock(struct futex_q *q)
__acquires(&hb->lock)
static inline void queue_unlock(struct futex_hash_bucket *hb)
__releases(&hb->lock)
static inline void __queue_me(struct futex_q *q, struct futex_hash_bucket *hb)
static inline void queue_me(struct futex_q *q, struct futex_hash_bucket *hb)
__releases(&hb->lock)
static int unqueue_me(struct futex_q *q)
static void unqueue_me_pi(struct futex_q *q)
__releases(q->lock_ptr)
static int fixup_pi_state_owner(u32 __user *uaddr, struct futex_q *q, struct task_struct *argowner)
static int fixup_owner(u32 __user *uaddr, struct futex_q *q, int locked)
static void futex_wait_queue_me(struct futex_hash_bucket *hb, struct futex_q *q, struct hrtimer_sleeper *timeout)
static int futex_wait_setup(u32 __user *uaddr, u32 val, unsigned int flags, struct futex_q *q, struct futex_hash_bucket **hb)
static int futex_wait(u32 __user *uaddr, unsigned int flags, u32 val, ktime_t *abs_time, u32 bitset)
static long futex_wait_restart(struct restart_block *restart)
static int futex_lock_pi(u32 __user *uaddr, unsigned int flags, ktime_t *time, int trylock)
static int futex_unlock_pi(u32 __user *uaddr, unsigned int flags)
static inline int handle_early_requeue_pi_wakeup(struct futex_hash_bucket *hb, struct futex_q *q, union futex_key *key2, struct hrtimer_sleeper *timeout)
static int futex_wait_requeue_pi(u32 __user *uaddr, unsigned int flags, u32 val, ktime_t *abs_time, u32 bitset, u32 __user *uaddr2)
SYSCALL_DEFINE2(set_robust_list, struct robust_list_head __user *, head, size_t, len)
SYSCALL_DEFINE3(get_robust_list, int, pid, struct robust_list_head __user * __user *, head_ptr, size_t __user *, len_ptr)
static int handle_futex_death(u32 __user *uaddr, struct task_struct *curr, int pi)
static inline int fetch_robust_entry(struct robust_list __user **entry, struct robust_list __user * __user *head, unsigned int *pi)
void exit_robust_list(struct task_struct *curr)
long do_futex(u32 __user *uaddr, int op, u32 val, ktime_t *timeout, u32 __user *uaddr2, u32 val2, u32 val3)
SYSCALL_DEFINE6(futex, u32 __user *, uaddr, int, op, u32, val, struct __kernel_timespec __user *, utime, u32 __user *, uaddr2, u32, val3)
static inline int compat_fetch_robust_entry(compat_uptr_t *uentry, struct robust_list __user **entry, compat_uptr_t __user *head, unsigned int *pi)
static void __user *futex_uaddr(struct robust_list __user *entry, compat_long_t futex_offset)
void compat_exit_robust_list(struct task_struct *curr)
COMPAT_SYSCALL_DEFINE2(set_robust_list, struct compat_robust_list_head __user *, head, compat_size_t, len)
COMPAT_SYSCALL_DEFINE3(get_robust_list, int, pid, compat_uptr_t __user *, head_ptr, compat_size_t __user *, len_ptr)
COMPAT_SYSCALL_DEFINE6(futex, u32 __user *, uaddr, int, op, u32, val, struct old_timespec32 __user *, utime, u32 __user *, uaddr2, u32, val3)
static void __init futex_detect_cmpxchg(void)
static int __init futex_init(void)
\n
     21 u32 __user *uaddr
     14 struct futex_q *q
     12 struct futex_hash_bucket *hb
     11 union futex_key *key
      8 unsigned int flags
      7 u32 uval
      5 void
      5 struct futex_pi_state **ps
      4 union futex_key *key2
      4 u32 val
      4 u32 __user *uaddr2
      4 u32 __user *
      4 u32
      4 struct task_struct *curr
      4 struct futex_pi_state *pi_state
      4 struct futex_hash_bucket *hb2
      4 struct futex_hash_bucket *hb1
      4 int
      3 u32 bitset
      3 int nr_wake
      3 &hb->lock
      2 val3
      2 val
      2 utime
      2 unsigned int *pi
      2 union futex_key *key1
      2 uaddr2
      2 uaddr
      2 u32 __user *uaddr1
      2 u32 newval
      2 struct robust_list __user **entry
      2 struct hrtimer_sleeper *timeout
      2 set_robust_list
      2 pid
      2 op
      2 len_ptr
      2 len
      2 ktime_t *abs_time
      2 int set_waiters
      2 int op
      2 head_ptr
      2 head
      2 get_robust_list
      2 futex
      2 bool fshared
      1 unsigned int encoded_op
      1 u32 val3
      1 u32 val2
      1 u32 __user *pifutex
      1 u32 __user *from
      1 u32 *dest
      1 u32 *curval
      1 u32 *cmpval
      1 struct wake_q_head *wake_q
      1 struct task_struct *tsk
      1 struct task_struct *task
      1 struct task_struct *argowner
      1 struct robust_list __user * __user *head
      1 struct robust_list __user *entry
      1 struct robust_list_head __user * __user *
      1 struct robust_list_head __user *
      1 struct restart_block *restart
      1 struct old_timespec32 __user *
      1 struct __kernel_timespec __user *
      1 struct futex_hash_bucket **hb
      1 struct compat_robust_list_head __user *
      1 size_t __user *
      1 size_t
      1 q->lock_ptr
      1 ktime_t *timeout
      1 ktime_t *time
      1 int trylock
      1 int requeue_pi
      1 int pi
      1 int nr_wake2
      1 int nr_requeue
      1 int locked
      1 int fshared
      1 enum futex_access rw
      1 compat_uptr_t __user *head
      1 compat_uptr_t __user *
      1 compat_uptr_t *uentry
      1 compat_size_t __user *
      1 compat_size_t
      1 compat_long_t futex_offset
      1 char *str
