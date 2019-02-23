
\n
static inline bool kvm_is_error_hva(unsigned long addr)
static inline void _kvm_atomic_set_c0_guest_reg(unsigned long *reg, unsigned long val)
static inline void _kvm_atomic_clear_c0_guest_reg(unsigned long *reg, unsigned long val)
static inline void _kvm_atomic_change_c0_guest_reg(unsigned long *reg, unsigned long change, unsigned long val)
define __BUILD_KVM_RW_SAVED(name, type, _reg, sel)
\ static inline __KVMTtype kvm_read_sw_gc0_name(struct mips_coproc *cop0)
\ define __BUILD_KVM_RW_SAVED(name, type, _reg, sel)
\ static inline __KVMTtype kvm_read_sw_gc0_name(struct mips_coproc *cop0)
\return cop0->reg[(_reg)
][(sel)
];\ } \ static inline void kvm_write_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\cop0->reg[(_reg)
][(sel)
] |= val;\ } \ static inline void kvm_clear_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\cop0->reg[(_reg)
][(sel)
] |= val;\ } \ static inline void kvm_clear_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\cop0->reg[(_reg)
][(sel)
] &= ~val;\ } \ static inline void kvm_change_sw_gc0_name(struct mips_coproc *cop0, \__KVMTtype mask, \__KVMTtype val)
\ define __BUILD_KVM_ATOMIC_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_ATOMIC_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\_kvm_atomic_set_c0_guest_reg(&cop0->reg[(_reg)
][(sel)
], val)
; \ } \ static inline void kvm_clear_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_ATOMIC_SAVED(name, type, _reg, sel)
\ static inline void kvm_set_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\_kvm_atomic_set_c0_guest_reg(&cop0->reg[(_reg)
][(sel)
], val)
; \ } \ static inline void kvm_clear_sw_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\_kvm_atomic_clear_c0_guest_reg(&cop0->reg[(_reg)
][(sel)
], val)
; \ } \ static inline void kvm_change_sw_gc0_name(struct mips_coproc *cop0, \__KVMTtype mask, \__KVMTtype val)
\ define __BUILD_KVM_RW_VZ(name, type, _reg, sel)
\ static inline __KVMTtype kvm_read_vz_gc0_name(struct mips_coproc *cop0)
\ define __BUILD_KVM_RW_VZ(name, type, _reg, sel)
\ static inline __KVMTtype kvm_read_vz_gc0_name(struct mips_coproc *cop0)
\return read_gc0_name()
; \ } \ static inline void kvm_write_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_VZ(name, type, _reg, sel)
\ static inline void kvm_set_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_VZ(name, type, _reg, sel)
\ static inline void kvm_set_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\set_gc0_name(val)
;\ } \ static inline void kvm_clear_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\ define __BUILD_KVM_SET_VZ(name, type, _reg, sel)
\ static inline void kvm_set_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\set_gc0_name(val)
;\ } \ static inline void kvm_clear_vz_gc0_name(struct mips_coproc *cop0, \ __KVMTtype val)
\clear_gc0_name(val)
;\ } \ static inline void kvm_change_vz_gc0_name(struct mips_coproc *cop0, \__KVMTtype mask, \__KVMTtype val)
\ define __BUILD_KVM_SAVE_VZ(name, _reg, sel)
\ static inline void kvm_restore_gc0_name(struct mips_coproc *cop0)
\ define __BUILD_KVM_SAVE_VZ(name, _reg, sel)
\ static inline void kvm_restore_gc0_name(struct mips_coproc *cop0)
\write_gc0_name(cop0->reg[(_reg)
][(sel)
])
; \ } \ static inline void kvm_save_gc0_name(struct mips_coproc *cop0)
\ define __BUILD_KVM_RW_WRAP(name1, name2, type)
\ static inline __KVMTtype kvm_read_name1(struct mips_coproc *cop0)
\ define __BUILD_KVM_RW_WRAP(name1, name2, type)
\ static inline __KVMTtype kvm_read_name1(struct mips_coproc *cop0)
\return kvm_read_name2(cop0)
; \ } \ static inline void kvm_write_name1(struct mips_coproc *cop0, \__KVMTtype val)
\ define __BUILD_KVM_SET_WRAP(name1, name2, type)
\ static inline void kvm_set_name1(struct mips_coproc *cop0, \__KVMTtype val)
\ define __BUILD_KVM_SET_WRAP(name1, name2, type)
\ static inline void kvm_set_name1(struct mips_coproc *cop0, \__KVMTtype val)
\kvm_set_name2(cop0, val)
; \ } \ static inline void kvm_clear_name1(struct mips_coproc *cop0, \__KVMTtype val)
\ define __BUILD_KVM_SET_WRAP(name1, name2, type)
\ static inline void kvm_set_name1(struct mips_coproc *cop0, \__KVMTtype val)
\kvm_set_name2(cop0, val)
; \ } \ static inline void kvm_clear_name1(struct mips_coproc *cop0, \__KVMTtype val)
\kvm_clear_name2(cop0, val)
; \ } \ static inline void kvm_change_name1(struct mips_coproc *cop0, \ __KVMTtype mask, \ __KVMTtype val)
\ static inline bool kvm_mips_guest_can_have_fpu(struct kvm_vcpu_arch *vcpu)
static inline bool kvm_mips_guest_has_fpu(struct kvm_vcpu_arch *vcpu)
static inline bool kvm_mips_guest_can_have_msa(struct kvm_vcpu_arch *vcpu)
static inline bool kvm_mips_guest_has_msa(struct kvm_vcpu_arch *vcpu)
static inline bool kvm_is_ifetch_fault(struct kvm_vcpu_arch *vcpu)
\n
     36 struct mips_coproc *cop0
     23 sel
     19 _reg
     18 type
     18 \ __KVMTtype val
     15 name
      9 \__KVMTtype val
      6 val
      5 struct kvm_vcpu_arch *vcpu
      5 name2
      5 name1
      4 cop0
      3 unsigned long val
      3 unsigned long *reg
      3 \__KVMTtype mask
      3 &cop0->reg[_reg
      1 unsigned long change
      1 unsigned long addr
      1 \ __KVMTtype mask
      1 cop0->reg[_reg
      1 
