
\n
static bool kvmppc_is_split_real(struct kvm_vcpu *vcpu)
static void kvmppc_fixup_split_real(struct kvm_vcpu *vcpu)
static void kvmppc_core_vcpu_load_pr(struct kvm_vcpu *vcpu, int cpu)
static void kvmppc_core_vcpu_put_pr(struct kvm_vcpu *vcpu)
void kvmppc_copy_to_svcpu(struct kvm_vcpu *vcpu)
static void kvmppc_recalc_shadow_msr(struct kvm_vcpu *vcpu)
void kvmppc_copy_from_svcpu(struct kvm_vcpu *vcpu)
void kvmppc_save_tm_sprs(struct kvm_vcpu *vcpu)
void kvmppc_restore_tm_sprs(struct kvm_vcpu *vcpu)
static void kvmppc_handle_lost_math_exts(struct kvm_vcpu *vcpu)
void kvmppc_save_tm_pr(struct kvm_vcpu *vcpu)
void kvmppc_restore_tm_pr(struct kvm_vcpu *vcpu)
static int kvmppc_core_check_requests_pr(struct kvm_vcpu *vcpu)
static void do_kvm_unmap_hva(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_unmap_hva_range_pr(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_age_hva_pr(struct kvm *kvm, unsigned long start, unsigned long end)
static int kvm_test_age_hva_pr(struct kvm *kvm, unsigned long hva)
static void kvm_set_spte_hva_pr(struct kvm *kvm, unsigned long hva, pte_t pte)
static void kvmppc_set_msr_pr(struct kvm_vcpu *vcpu, u64 msr)
void kvmppc_set_pvr_pr(struct kvm_vcpu *vcpu, u32 pvr)
static void kvmppc_patch_dcbz(struct kvm_vcpu *vcpu, struct kvmppc_pte *pte)
static bool kvmppc_visible_gpa(struct kvm_vcpu *vcpu, gpa_t gpa)
int kvmppc_handle_pagefault(struct kvm_run *run, struct kvm_vcpu *vcpu, ulong eaddr, int vec)
void kvmppc_giveup_ext(struct kvm_vcpu *vcpu, ulong msr)
void kvmppc_giveup_fac(struct kvm_vcpu *vcpu, ulong fac)
static int kvmppc_handle_ext(struct kvm_vcpu *vcpu, unsigned int exit_nr, ulong msr)
static void kvmppc_handle_lost_ext(struct kvm_vcpu *vcpu)
void kvmppc_trigger_fac_interrupt(struct kvm_vcpu *vcpu, ulong fac)
static void kvmppc_emulate_fac(struct kvm_vcpu *vcpu, ulong fac)
static int kvmppc_handle_fac(struct kvm_vcpu *vcpu, ulong fac)
void kvmppc_set_fscr(struct kvm_vcpu *vcpu, u64 fscr)
static void kvmppc_setup_debug(struct kvm_vcpu *vcpu)
static void kvmppc_clear_debug(struct kvm_vcpu *vcpu)
static int kvmppc_exit_pr_progint(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int exit_nr)
int kvmppc_handle_exit_pr(struct kvm_run *run, struct kvm_vcpu *vcpu, unsigned int exit_nr)
static int kvm_arch_vcpu_ioctl_get_sregs_pr(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int kvm_arch_vcpu_ioctl_set_sregs_pr(struct kvm_vcpu *vcpu, struct kvm_sregs *sregs)
static int kvmppc_get_one_reg_pr(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
static void kvmppc_set_lpcr_pr(struct kvm_vcpu *vcpu, u64 new_lpcr)
static int kvmppc_set_one_reg_pr(struct kvm_vcpu *vcpu, u64 id, union kvmppc_one_reg *val)
static struct kvm_vcpu *kvmppc_core_vcpu_create_pr(struct kvm *kvm, unsigned int id)
static void kvmppc_core_vcpu_free_pr(struct kvm_vcpu *vcpu)
static int kvmppc_vcpu_run_pr(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
static int kvm_vm_ioctl_get_dirty_log_pr(struct kvm *kvm, struct kvm_dirty_log *log)
static void kvmppc_core_flush_memslot_pr(struct kvm *kvm, struct kvm_memory_slot *memslot)
static int kvmppc_core_prepare_memory_region_pr(struct kvm *kvm, struct kvm_memory_slot *memslot, const struct kvm_userspace_memory_region *mem)
static void kvmppc_core_commit_memory_region_pr(struct kvm *kvm, const struct kvm_userspace_memory_region *mem, const struct kvm_memory_slot *old, const struct kvm_memory_slot *new, enum kvm_mr_change change)
static void kvmppc_core_free_memslot_pr(struct kvm_memory_slot *free, struct kvm_memory_slot *dont)
static int kvmppc_core_create_memslot_pr(struct kvm_memory_slot *slot, unsigned long npages)
static int kvm_vm_ioctl_get_smmu_info_pr(struct kvm *kvm, struct kvm_ppc_smmu_info *info)
static int kvm_configure_mmu_pr(struct kvm *kvm, struct kvm_ppc_mmuv3_cfg *cfg)
static int kvm_vm_ioctl_get_smmu_info_pr(struct kvm *kvm, struct kvm_ppc_smmu_info *info)
static int kvmppc_core_init_vm_pr(struct kvm *kvm)
static void kvmppc_core_destroy_vm_pr(struct kvm *kvm)
static int kvmppc_core_check_processor_compat_pr(void)
static long kvm_arch_vm_ioctl_pr(struct file *filp, unsigned int ioctl, unsigned long arg)
int kvmppc_book3s_init_pr(void)
void kvmppc_book3s_exit_pr(void)
\n
     37 struct kvm_vcpu *vcpu
     15 struct kvm *kvm
      4 ulong fac
      3 void
      3 unsigned long start
      3 unsigned long end
      3 unsigned int exit_nr
      3 struct kvm_run *run
      2 unsigned long hva
      2 union kvmppc_one_reg *val
      2 ulong msr
      2 u64 id
      2 struct kvm_sregs *sregs
      2 struct kvm_ppc_smmu_info *info
      2 struct kvm_memory_slot *memslot
      2 const struct kvm_userspace_memory_region *mem
      1 unsigned long npages
      1 unsigned long arg
      1 unsigned int ioctl
      1 unsigned int id
      1 ulong eaddr
      1 u64 new_lpcr
      1 u64 msr
      1 u64 fscr
      1 u32 pvr
      1 struct kvm_run *kvm_run
      1 struct kvmppc_pte *pte
      1 struct kvm_ppc_mmuv3_cfg *cfg
      1 struct kvm_memory_slot *slot
      1 struct kvm_memory_slot *free
      1 struct kvm_memory_slot *dont
      1 struct kvm_dirty_log *log
      1 struct file *filp
      1 pte_t pte
      1 int vec
      1 int cpu
      1 gpa_t gpa
      1 enum kvm_mr_change change
      1 const struct kvm_memory_slot *old
      1 const struct kvm_memory_slot *new
