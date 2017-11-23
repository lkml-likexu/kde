

#### [PATCH 0/2] KVM: arm64: Dynamic IPA cosmetic fixups
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

Here's a couple of tiny cleanups I'd like to queue on top of Suzuki's
series. They are purely cosmetic, and just aim at making the code
slightly more readable.

If nobody shouts, I'll stack them on top.

Thanks,

	M.

Marc Zyngier (2):
  KVM: arm/arm64: Rename kvm_arm_config_vm to kvm_arm_setup_stage2
  KVM: arm64: Drop __cpu_init_stage2 on the VHE path

 arch/arm/include/asm/kvm_host.h   |  6 +++++-
 arch/arm64/include/asm/kvm_arm.h  |  2 +-
 arch/arm64/include/asm/kvm_host.h |  2 +-
 arch/arm64/kvm/reset.c            |  2 +-
 virt/kvm/arm/arm.c                | 12 +++---------
 5 files changed, 11 insertions(+), 13 deletions(-)
```
#### [PATCH v3 0/9] x86/kvm/nVMX: optimize MMU switch between L1 and L2
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Change since v2 [Sean Christopherson]:
- Add Reviewed-by tags (thanks!).
- Move get_pdptr setting to nested_ept_init_mmu_context().
- Move kvm_mmu_free_roots() call to nested_release_vmcs12().
- In kvm_calc_shadow_ept_root_page_role() we need to inherit role
  from root_mmu so fields like .smap_andnot_wp, .smep_andnot_wp, ...
  remain correctly initialized.
- Use u32 for base_role instead of unsigned int in kvm_mmu_pte_write
- Split kvm_calc_mmu_role_common() into kvm_calc_mmu_role_common() and
  kvm_calc_mmu_role_ext().
- Rename 'mmu_init' parameter to 'base_only'.

Original description:

Currently, when we switch from L1 to L2 (VMX) we do the following:
- Re-initialize L1 MMU as shadow EPT MMU (nested_ept_init_mmu_context())
- Re-initialize 'nested' MMU (nested_vmx_load_cr3() -> init_kvm_nested_mmu())

When we switch back we do:
- Re-initialize L1 MMU (nested_vmx_load_cr3() -> init_kvm_tdp_mmu())

This seems to be sub-optimal. Initializing MMU is expensive (thanks to
update_permission_bitmask(), update_pkru_bitmask(),..) Try solving the
issue by splitting L1-normal and L1-nested MMUs and checking if MMU reset
is really needed. This spares us about 1000 cpu cycles on nested vmexit.

Brief look at SVM makes me think it can be optimized the exact same way,
I'll do this in a separate series.

Paolo Bonzini (1):
  x86/kvm/mmu: get rid of redundant kvm_mmu_setup()

Vitaly Kuznetsov (8):
  x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
  x86/kvm/mmu.c: set get_pdptr hook in kvm_init_shadow_ept_mmu()
  x86/kvm/mmu.c: add kvm_mmu parameter to kvm_mmu_free_roots()
  x86/kvm/mmu: introduce guest_mmu
  x86/kvm/mmu: make space for source data caching in struct kvm_mmu
  x86/kvm/nVMX: introduce source data cache for
    kvm_init_shadow_ept_mmu()
  x86/kvm/mmu: check if tdp/shadow MMU reconfiguration is needed
  x86/kvm/mmu: check if MMU reconfiguration is needed in
    init_kvm_nested_mmu()

 arch/x86/include/asm/kvm_host.h |  44 +++-
 arch/x86/kvm/mmu.c              | 357 +++++++++++++++++++-------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +-
 arch/x86/kvm/paging_tmpl.h      |  15 +-
 arch/x86/kvm/svm.c              |  14 +-
 arch/x86/kvm/vmx.c              |  55 +++--
 arch/x86/kvm/x86.c              |  22 +-
 8 files changed, 322 insertions(+), 205 deletions(-)
```
#### [PATCH 0/2] KVM: VMX: clean up virtual APIC control handling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The immediate goal of this series is to fix a VMWRITE warning that
occurs on older hardware due to accessing secondary exec controls
when the field is not supported[1].  While inspecting the related
code, I found that the offending commit that introduced the bug also
unintentionally changed nested guest behavior when the FlexPriority
module param is disabled.  KVM's handling of the FlexPriority param
is so inconsistent and unintuitive that removing the param altogether
seemed to be the simplest way to revert back to the previous behavior
while keeping its bugfix intact.

[1] https://bugzilla.redhat.com/show_bug.cgi?id=1632426

Sean Christopherson (2):
  KVM: VMX: remove kvm-intel.flexpriority module parameter
  KVM: VMX: check for existence of secondary exec controls before
    accessing

 .../admin-guide/kernel-parameters.txt         |  4 ---
 arch/x86/kvm/vmx.c                            | 26 ++++++-------------
 2 files changed, 8 insertions(+), 22 deletions(-)
```
