
\n
extern int link_mem_sections(int nid, unsigned long start_pfn, unsigned long end_pfn)
; static inline int link_mem_sections(int nid, unsigned long start_pfn, unsigned long end_pfn)
static inline int register_one_node(int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
return 0; } static inline int unregister_one_node(int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
return 0; } static inline int unregister_one_node(int nid)
return 0; } static inline int register_cpu_under_node(unsigned int cpu, unsigned int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
return 0; } static inline int unregister_one_node(int nid)
return 0; } static inline int register_cpu_under_node(unsigned int cpu, unsigned int nid)
return 0; } static inline int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
return 0; } static inline int unregister_one_node(int nid)
return 0; } static inline int register_cpu_under_node(unsigned int cpu, unsigned int nid)
return 0; } static inline int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
return 0; } static inline int register_mem_sect_under_node(struct memory_block *mem_blk, void *arg)
extern void register_hugetlbfs_with_node(node_registration_func_t doregister, node_registration_func_t unregister)
;endif static inline int __register_one_node(int nid)
return 0; } static inline int register_one_node(int nid)
return 0; } static inline int unregister_one_node(int nid)
return 0; } static inline int register_cpu_under_node(unsigned int cpu, unsigned int nid)
return 0; } static inline int unregister_cpu_under_node(unsigned int cpu, unsigned int nid)
return 0; } static inline int register_mem_sect_under_node(struct memory_block *mem_blk, void *arg)
return 0; } static inline int unregister_mem_sect_under_nodes(struct memory_block *mem_blk, unsigned long phys_index)
static inline void register_hugetlbfs_with_node(node_registration_func_t reg, node_registration_func_t unreg)
\n
     21 int nid
      7 unsigned int nid
      7 unsigned int cpu
      7 node_registration_func_t unregister
      7 node_registration_func_t doregister
      3 struct memory_block *mem_blk
      2 void *arg
      2 unsigned long start_pfn
      2 unsigned long end_pfn
      1 unsigned long phys_index
      1 node_registration_func_t unreg
      1 node_registration_func_t reg
