
\n
int ipte_lock_held(struct kvm_vcpu *vcpu)
static void ipte_lock_simple(struct kvm_vcpu *vcpu)
static void ipte_unlock_simple(struct kvm_vcpu *vcpu)
static void ipte_lock_siif(struct kvm_vcpu *vcpu)
static void ipte_unlock_siif(struct kvm_vcpu *vcpu)
void ipte_lock(struct kvm_vcpu *vcpu)
void ipte_unlock(struct kvm_vcpu *vcpu)
static int ar_translation(struct kvm_vcpu *vcpu, union asce *asce, u8 ar, enum gacc_mode mode)
static int trans_exc(struct kvm_vcpu *vcpu, int code, unsigned long gva, u8 ar, enum gacc_mode mode, enum prot_type prot)
static int get_vcpu_asce(struct kvm_vcpu *vcpu, union asce *asce, unsigned long ga, u8 ar, enum gacc_mode mode)
static int deref_table(struct kvm *kvm, unsigned long gpa, unsigned long *val)
static unsigned long guest_translate(struct kvm_vcpu *vcpu, unsigned long gva, unsigned long *gpa, const union asce asce, enum gacc_mode mode, enum prot_type *prot)
static inline int is_low_address(unsigned long ga)
static int low_address_protection_enabled(struct kvm_vcpu *vcpu, const union asce asce)
static int guest_page_range(struct kvm_vcpu *vcpu, unsigned long ga, u8 ar, unsigned long *pages, unsigned long nr_pages, const union asce asce, enum gacc_mode mode)
int access_guest(struct kvm_vcpu *vcpu, unsigned long ga, u8 ar, void *data, unsigned long len, enum gacc_mode mode)
int access_guest_real(struct kvm_vcpu *vcpu, unsigned long gra, void *data, unsigned long len, enum gacc_mode mode)
int guest_translate_address(struct kvm_vcpu *vcpu, unsigned long gva, u8 ar, unsigned long *gpa, enum gacc_mode mode)
int check_gva_range(struct kvm_vcpu *vcpu, unsigned long gva, u8 ar, unsigned long length, enum gacc_mode mode)
int kvm_s390_check_low_addr_prot_real(struct kvm_vcpu *vcpu, unsigned long gra)
static int kvm_s390_shadow_tables(struct gmap *sg, unsigned long saddr, unsigned long *pgt, int *dat_protection, int *fake)
int kvm_s390_shadow_fault(struct kvm_vcpu *vcpu, struct gmap *sg, unsigned long saddr)
\n
     19 struct kvm_vcpu *vcpu
      9 enum gacc_mode mode
      7 u8 ar
      4 unsigned long gva
      4 unsigned long ga
      3 const union asce asce
      2 void *data
      2 unsigned long saddr
      2 unsigned long len
      2 unsigned long gra
      2 unsigned long *gpa
      2 union asce *asce
      2 struct gmap *sg
      1 unsigned long *val
      1 unsigned long *pgt
      1 unsigned long *pages
      1 unsigned long nr_pages
      1 unsigned long length
      1 unsigned long gpa
      1 struct kvm *kvm
      1 int *fake
      1 int *dat_protection
      1 int code
      1 enum prot_type *prot
      1 enum prot_type prot
