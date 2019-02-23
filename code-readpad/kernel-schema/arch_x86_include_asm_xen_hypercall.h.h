
\n
static inline long xen_single_call(unsigned int call, unsigned long a1, unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5)
static inline long privcmd_call(unsigned int call, unsigned long a1, unsigned long a2, unsigned long a3, unsigned long a4, unsigned long a5)
static inline int HYPERVISOR_set_trap_table(struct trap_info *table)
static inline int HYPERVISOR_mmu_update(struct mmu_update *req, int count, int *success_count, domid_t domid)
static inline int HYPERVISOR_mmuext_op(struct mmuext_op *op, int count, int *success_count, domid_t domid)
static inline int HYPERVISOR_set_gdt(unsigned long *frame_list, int entries)
static inline int HYPERVISOR_callback_op(int cmd, void *arg)
static inline int HYPERVISOR_sched_op(int cmd, void *arg)
static inline long HYPERVISOR_set_timer_op(u64 timeout)
static inline int HYPERVISOR_mca(struct xen_mc *mc_op)
static inline int HYPERVISOR_platform_op(struct xen_platform_op *op)
static inline int HYPERVISOR_set_debugreg(int reg, unsigned long value)
static inline unsigned long HYPERVISOR_get_debugreg(int reg)
static inline int HYPERVISOR_update_descriptor(u64 ma, u64 desc)
static inline long HYPERVISOR_memory_op(unsigned int cmd, void *arg)
static inline int HYPERVISOR_multicall(void *call_list, uint32_t nr_calls)
static inline int HYPERVISOR_update_va_mapping(unsigned long va, pte_t new_val, unsigned long flags)
static inline int HYPERVISOR_event_channel_op(int cmd, void *arg)
static inline int HYPERVISOR_xen_version(int cmd, void *arg)
static inline int HYPERVISOR_console_io(int cmd, int count, char *str)
static inline int HYPERVISOR_physdev_op(int cmd, void *arg)
static inline int HYPERVISOR_grant_table_op(unsigned int cmd, void *uop, unsigned int count)
static inline int HYPERVISOR_vm_assist(unsigned int cmd, unsigned int type)
static inline int HYPERVISOR_vcpu_op(int cmd, int vcpuid, void *extra_args)
static inline int HYPERVISOR_set_segment_base(int reg, unsigned long value)
static inline int HYPERVISOR_suspend(unsigned long start_info_mfn)
static inline unsigned long __must_check HYPERVISOR_hvm_op(int op, void *arg)
static inline int HYPERVISOR_tmem_op(struct tmem_op *op)
static inline int HYPERVISOR_xenpmu_op(unsigned int op, void *arg)
static inline int HYPERVISOR_dm_op(domid_t dom, unsigned int nr_bufs, struct xen_dm_op_buf *bufs)
static inline void MULTI_fpu_taskswitch(struct multicall_entry *mcl, int set)
static inline void MULTI_update_va_mapping(struct multicall_entry *mcl, unsigned long va, pte_t new_val, unsigned long flags)
static inline void MULTI_update_descriptor(struct multicall_entry *mcl, u64 maddr, struct desc_struct desc)
static inline void MULTI_mmu_update(struct multicall_entry *mcl, struct mmu_update *req, int count, int *success_count, domid_t domid)
static inline void MULTI_mmuext_op(struct multicall_entry *mcl, struct mmuext_op *op, int count, int *success_count, domid_t domid)
static inline void MULTI_stack_switch(struct multicall_entry *mcl, unsigned long ss, unsigned long esp)
\n
      8 void *arg
      7 int cmd
      6 struct multicall_entry *mcl
      5 int count
      4 int *success_count
      4 domid_t domid
      3 unsigned int cmd
      3 int reg
      2 unsigned long value
      2 unsigned long va
      2 unsigned long flags
      2 unsigned long a5
      2 unsigned long a4
      2 unsigned long a3
      2 unsigned long a2
      2 unsigned long a1
      2 unsigned int call
      2 struct mmu_update *req
      2 struct mmuext_op *op
      2 pte_t new_val
      1 void *uop
      1 void *extra_args
      1 void *call_list
      1 unsigned long start_info_mfn
      1 unsigned long ss
      1 unsigned long *frame_list
      1 unsigned long esp
      1 unsigned int type
      1 unsigned int op
      1 unsigned int nr_bufs
      1 unsigned int count
      1 uint32_t nr_calls
      1 u64 timeout
      1 u64 maddr
      1 u64 ma
      1 u64 desc
      1 struct xen_platform_op *op
      1 struct xen_mc *mc_op
      1 struct xen_dm_op_buf *bufs
      1 struct trap_info *table
      1 struct tmem_op *op
      1 struct desc_struct desc
      1 int vcpuid
      1 int set
      1 int op
      1 int entries
      1 domid_t dom
      1 char *str
