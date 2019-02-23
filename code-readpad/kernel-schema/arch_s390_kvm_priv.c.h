
\n
static int handle_ri(struct kvm_vcpu *vcpu)
int kvm_s390_handle_aa(struct kvm_vcpu *vcpu)
static int handle_gs(struct kvm_vcpu *vcpu)
int kvm_s390_handle_e3(struct kvm_vcpu *vcpu)
if (code == 0x49 || code == 0x4d)
return handle_gs(vcpu)
;else return -EOPNOTSUPP; }static int handle_set_clock(struct kvm_vcpu *vcpu)
static int handle_set_prefix(struct kvm_vcpu *vcpu)
static int handle_store_prefix(struct kvm_vcpu *vcpu)
static int handle_store_cpu_address(struct kvm_vcpu *vcpu)
int kvm_s390_skey_check_enable(struct kvm_vcpu *vcpu)
static int try_handle_skey(struct kvm_vcpu *vcpu)
static int handle_iske(struct kvm_vcpu *vcpu)
static int handle_rrbe(struct kvm_vcpu *vcpu)
define SSKE_NQ 0x8define SSKE_MR 0x4define SSKE_MC 0x2define SSKE_MB 0x1 static int handle_sske(struct kvm_vcpu *vcpu)
static int handle_ipte_interlock(struct kvm_vcpu *vcpu)
static int handle_test_block(struct kvm_vcpu *vcpu)
static int handle_tpi(struct kvm_vcpu *vcpu)
static int handle_tsch(struct kvm_vcpu *vcpu)
static int handle_io_inst(struct kvm_vcpu *vcpu)
static int handle_stfl(struct kvm_vcpu *vcpu)
int is_valid_psw(psw_t *psw)
int kvm_s390_handle_lpsw(struct kvm_vcpu *vcpu)
static int handle_lpswe(struct kvm_vcpu *vcpu)
static int handle_stidp(struct kvm_vcpu *vcpu)
static void handle_stsi_3_2_2(struct kvm_vcpu *vcpu, struct sysinfo_3_2_2 *mem)
static void insert_stsi_usr_data(struct kvm_vcpu *vcpu, u64 addr, u8 ar, u8 fc, u8 sel1, u16 sel2)
static int handle_stsi(struct kvm_vcpu *vcpu)
int kvm_s390_handle_b2(struct kvm_vcpu *vcpu)
static int handle_epsw(struct kvm_vcpu *vcpu)
static int handle_pfmf(struct kvm_vcpu *vcpu)
static inline int __do_essa(struct kvm_vcpu *vcpu, const int orc)
static int handle_essa(struct kvm_vcpu *vcpu)
int kvm_s390_handle_b9(struct kvm_vcpu *vcpu)
int kvm_s390_handle_lctl(struct kvm_vcpu *vcpu)
int kvm_s390_handle_stctl(struct kvm_vcpu *vcpu)
static int handle_lctlg(struct kvm_vcpu *vcpu)
static int handle_stctg(struct kvm_vcpu *vcpu)
int kvm_s390_handle_eb(struct kvm_vcpu *vcpu)
static int handle_tprot(struct kvm_vcpu *vcpu)
int kvm_s390_handle_e5(struct kvm_vcpu *vcpu)
static int handle_sckpf(struct kvm_vcpu *vcpu)
static int handle_ptff(struct kvm_vcpu *vcpu)
int kvm_s390_handle_01(struct kvm_vcpu *vcpu)
\n
     41 struct kvm_vcpu *vcpu
      1 vcpu
      1 u8 sel1
      1 u8 fc
      1 u8 ar
      1 u64 addr
      1 u16 sel2
      1 struct sysinfo_3_2_2 *mem
      1 psw_t *psw
      1 const int orc
      1 code == 0x49 || code == 0x4d
