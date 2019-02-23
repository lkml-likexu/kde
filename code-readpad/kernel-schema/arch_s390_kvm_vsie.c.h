
\n
static int set_validity_icpt(struct kvm_s390_sie_block *scb, __u16 reason_code)
static void prefix_unmapped(struct vsie_page *vsie_page)
static void prefix_unmapped_sync(struct vsie_page *vsie_page)
static void prefix_mapped(struct vsie_page *vsie_page)
static int prefix_is_mapped(struct vsie_page *vsie_page)
static void update_intervention_requests(struct vsie_page *vsie_page)
static int prepare_cpuflags(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
atomic_set(&scb_s->cpuflags, newflags)
;return 0; }static int setup_apcb10(struct kvm_vcpu *vcpu, struct kvm_s390_apcb1 *apcb_s, unsigned long apcb_o, struct kvm_s390_apcb1 *apcb_h)
static int setup_apcb00(struct kvm_vcpu *vcpu, unsigned long *apcb_s, unsigned long apcb_o, unsigned long *apcb_h)
static int setup_apcb11(struct kvm_vcpu *vcpu, unsigned long *apcb_s, unsigned long apcb_o, unsigned long *apcb_h)
static int setup_apcb(struct kvm_vcpu *vcpu, struct kvm_s390_crypto_cb *crycb_s, const u32 crycb_o, struct kvm_s390_crypto_cb *crycb_h, int fmt_o, int fmt_h)
static int shadow_crycb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void prepare_ibc(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void unshadow_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static int shadow_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
void kvm_s390_vsie_gmap_notifier(struct gmap *gmap, unsigned long start, unsigned long end)
static int map_prefix(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static int pin_guest_page(struct kvm *kvm, gpa_t gpa, hpa_t *hpa)
static void unpin_guest_page(struct kvm *kvm, gpa_t gpa, hpa_t hpa)
static void unpin_blocks(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static int pin_blocks(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void unpin_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page, gpa_t gpa)
static int pin_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page, gpa_t gpa)
static int inject_fault(struct kvm_vcpu *vcpu, __u16 code, __u64 vaddr, bool write_flag)
static int handle_fault(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void handle_last_fault(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static inline void clear_vsie_icpt(struct vsie_page *vsie_page)
static void retry_vsie_icpt(struct vsie_page *vsie_page)
static int handle_stfle(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static int do_vsie_run(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
__releases(vcpu->kvm->srcu)
__acquires(vcpu->kvm->srcu)
static void release_gmap_shadow(struct vsie_page *vsie_page)
static int acquire_gmap_shadow(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void register_shadow_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static void unregister_shadow_scb(struct kvm_vcpu *vcpu)
static int vsie_run(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
static struct vsie_page *get_vsie_page(struct kvm *kvm, unsigned long addr)
static void put_vsie_page(struct kvm *kvm, struct vsie_page *vsie_page)
int kvm_s390_handle_vsie(struct kvm_vcpu *vcpu)
void kvm_s390_vsie_init(struct kvm *kvm)
void kvm_s390_vsie_destroy(struct kvm *kvm)
void kvm_s390_vsie_kick(struct kvm_vcpu *vcpu)
\n
     26 struct vsie_page *vsie_page
     25 struct kvm_vcpu *vcpu
      6 struct kvm *kvm
      4 gpa_t gpa
      3 unsigned long apcb_o
      2 vcpu->kvm->srcu
      2 unsigned long *apcb_s
      2 unsigned long *apcb_h
      1 unsigned long start
      1 unsigned long end
      1 unsigned long addr
      1 __u64 vaddr
      1 __u16 reason_code
      1 __u16 code
      1 struct kvm_s390_sie_block *scb
      1 struct kvm_s390_crypto_cb *crycb_s
      1 struct kvm_s390_crypto_cb *crycb_h
      1 struct kvm_s390_apcb1 *apcb_s
      1 struct kvm_s390_apcb1 *apcb_h
      1 struct gmap *gmap
      1 &scb_s->cpuflags
      1 newflags
      1 int fmt_o
      1 int fmt_h
      1 hpa_t *hpa
      1 hpa_t hpa
      1 const u32 crycb_o
      1 bool write_flag
