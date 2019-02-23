
\n
extern void task_numa_fault(int last_node, int node, int pages, int flags)
; extern pid_t task_numa_group_id(struct task_struct *p)
; extern void set_numabalancing_state(bool enabled)
; extern void task_numa_free(struct task_struct *p)
; extern bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
; static inline void task_numa_fault(int last_node, int node, int pages, int flags)
extern void task_numa_fault(int last_node, int node, int pages, int flags)
; extern pid_t task_numa_group_id(struct task_struct *p)
; extern void set_numabalancing_state(bool enabled)
; extern void task_numa_free(struct task_struct *p)
; extern bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
; static inline void task_numa_fault(int last_node, int node, int pages, int flags)
} static inline pid_t task_numa_group_id(struct task_struct *p)
extern void task_numa_fault(int last_node, int node, int pages, int flags)
; extern pid_t task_numa_group_id(struct task_struct *p)
; extern void set_numabalancing_state(bool enabled)
; extern void task_numa_free(struct task_struct *p)
; extern bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
; static inline void task_numa_fault(int last_node, int node, int pages, int flags)
} static inline pid_t task_numa_group_id(struct task_struct *p)
return 0; } static inline void set_numabalancing_state(bool enabled)
extern void task_numa_fault(int last_node, int node, int pages, int flags)
; extern pid_t task_numa_group_id(struct task_struct *p)
; extern void set_numabalancing_state(bool enabled)
; extern void task_numa_free(struct task_struct *p)
; extern bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
; static inline void task_numa_fault(int last_node, int node, int pages, int flags)
} static inline pid_t task_numa_group_id(struct task_struct *p)
return 0; } static inline void set_numabalancing_state(bool enabled)
} static inline void task_numa_free(struct task_struct *p)
extern void task_numa_fault(int last_node, int node, int pages, int flags)
; extern pid_t task_numa_group_id(struct task_struct *p)
; extern void set_numabalancing_state(bool enabled)
; extern void task_numa_free(struct task_struct *p)
; extern bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
; static inline void task_numa_fault(int last_node, int node, int pages, int flags)
} static inline pid_t task_numa_group_id(struct task_struct *p)
return 0; } static inline void set_numabalancing_state(bool enabled)
} static inline void task_numa_free(struct task_struct *p)
} static inline bool should_numa_migrate_memory(struct task_struct *p, struct page *page, int src_nid, int dst_cpu)
\n
     22 struct task_struct *p
     10 int pages
     10 int node
     10 int last_node
     10 int flags
      8 bool enabled
      6 struct page *page
      6 int src_nid
      6 int dst_cpu
