

#### [PATCH RESEND v4 0/9] Enable Sub-page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

EPT-Based Sub-Page write Protection(SPP)is a HW capability which allows
Virtual Machine Monitor(VMM) to specify write-permission for guest
physical memory at a sub-page(128 byte) granularity. When this
capability is enabled, the CPU enforces write-access check for sub-pages
within a 4KB page.

The feature is targeted to provide fine-grained memory protection for
usages such as device virtualization, memory check-point and VM
introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), SPPT is referenced via a 64-bit control field
called Sub-Page Permission Table Pointer (SPPTP) which contains a
4K-aligned physical address.

Right now, only 4KB physical pages are supported for SPP. To enable SPP
for certain physical page, we need to first make the physical page
write-protected, then set bit 61 of the corresponding EPT leaf entry. 
While HW walks EPT, if bit 61 is set, it traverses SPPT with the guset
physical address to find out the sub-page permissions at the leaf entry.
If the corresponding bit is set, write to sub-page is permitted,
otherwise, SPP induced EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

SPP selftest patch:
https://lkml.org/lkml/2019/6/18/1197

Previous patch:
https://lkml.org/lkml/2019/6/6/695

Patch 1: Introduction to SPP.
Patch 2: Add SPP related flags and control bits.
Patch 3: Functions for SPPT setup.
Patch 4: Add SPP access bitmaps for memslots.
Patch 5: Low level implementation of SPP operations.
Patch 6: Implement User space access IOCTLs.
Patch 7: Handle SPP induced VMExit and EPT violation.
Patch 8: Enable lazy mode SPPT setup.
Patch 9: Handle memory remapping and reclaim.


Change logs:

V3 -> v4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

V2 -> V3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

V2 -> V1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 


Yang Weijiang (9):
  Documentation: Introduce EPT based Subpage Protection
  KVM: VMX: Add control flags for SPP enabling
  KVM: VMX: Implement functions for SPPT paging setup
  KVM: VMX: Introduce SPP access bitmap and operation functions
  KVM: VMX: Add init/set/get functions for SPP
  KVM: VMX: Introduce SPP user-space IOCTLs
  KVM: VMX: Handle SPP induced vmexit and page fault
  KVM: MMU: Enable Lazy mode SPPT setup
  KVM: MMU: Handle host memory remapping and reclaim

 Documentation/virtual/kvm/spp_kvm.txt | 173 ++++++++++
 arch/x86/include/asm/cpufeatures.h    |   1 +
 arch/x86/include/asm/kvm_host.h       |  26 +-
 arch/x86/include/asm/vmx.h            |  10 +
 arch/x86/include/uapi/asm/vmx.h       |   2 +
 arch/x86/kernel/cpu/intel.c           |   4 +
 arch/x86/kvm/mmu.c                    | 480 ++++++++++++++++++++++++++
 arch/x86/kvm/mmu.h                    |   1 +
 arch/x86/kvm/vmx/capabilities.h       |   5 +
 arch/x86/kvm/vmx/vmx.c                | 129 +++++++
 arch/x86/kvm/x86.c                    | 141 ++++++++
 include/linux/kvm_host.h              |   9 +
 include/uapi/linux/kvm.h              |  17 +
 13 files changed, 997 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
```
#### [PATCH V2 0/3] KVM/Hyper-V: Add Hyper-V direct tlb flush support
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

This patchset is to add Hyper-V direct tlb support in KVM. Hyper-V
in L0 can delegate L1 hypervisor to handle tlb flush request from
L2 guest when direct tlb flush is enabled in L1.

Patch 2 introduces new cap KVM_CAP_HYPERV_DIRECT_TLBFLUSH to enable
feature from user space. User space should enable this feature only
when Hyper-V hypervisor capability is exposed to guest and KVM profile
is hided. There is a parameter conflict between KVM and Hyper-V hypercall.
We hope L2 guest doesn't use KVM hypercall when the feature is
enabled. Detail please see comment of new API "KVM_CAP_HYPERV_DIRECT_TLBFLUSH"

Change since v1:
       - Fix offset issue in the patch 1.
       - Update description of KVM KVM_CAP_HYPERV_DIRECT_TLBFLUSH.

Tianyu Lan (2):
  x86/Hyper-V: Fix definition of struct hv_vp_assist_page
  KVM/Hyper-V: Add new KVM cap KVM_CAP_HYPERV_DIRECT_TLBFLUSH

Vitaly Kuznetsov (1):
  KVM/Hyper-V/VMX: Add direct tlb flush support

 Documentation/virtual/kvm/api.txt  | 12 ++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h | 24 +++++++++++++++++++-----
 arch/x86/include/asm/kvm_host.h    |  2 ++
 arch/x86/kvm/vmx/evmcs.h           |  2 ++
 arch/x86/kvm/vmx/vmx.c             | 38 ++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                 |  8 ++++++++
 include/linux/kvm_host.h           |  1 +
 include/uapi/linux/kvm.h           |  1 +
 8 files changed, 83 insertions(+), 5 deletions(-)
```
#### [PATCH 0/3] kvm: selftests: fixes for vmx_set_nested_state_test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

The vmx_set_nested_state_test test is failing in the top of the tree, due
to the change in KVM_STATE_NESTED_EVMCS semantics from commit 323d73a8ecad
("KVM: nVMX: Change KVM_STATE_NESTED_EVMCS to signal vmcs12 is copied
from eVMCS", 2019-06-26).  The expected behavior of the kernel has changed
slightly and the test should be changed to match the fix in the kernel.

Paolo

Paolo Bonzini (3):
  selftests: kvm: do not try running the VM in vmx_set_nested_state_test
  selftests: kvm: provide common function to enable eVMCS
  selftests: kvm: fix vmx_set_nested_state_test

 tools/testing/selftests/kvm/include/evmcs.h        |  2 ++
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 20 ++++++++++++++
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    | 15 ++--------
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  | 12 +++-----
 .../kvm/x86_64/vmx_set_nested_state_test.c         | 32 ++++++++++------------
 5 files changed, 42 insertions(+), 39 deletions(-)
```
