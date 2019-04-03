#### [PATCH 1/6 v4][KVM nVMX]: Check "load IA32_PAT" VM-exit control on vmentry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on Host Control Registers and MSRs" in Intel
SDM vol 3C, the following check is performed on vmentry:

    If the "load IA32_PAT" VM-exit control is 1, the value of the field
    for the IA32_PAT MSR must be one that could be written by WRMSR
    without fault at CPL 0. Specifically, each of the 8 bytes in the
    field must have one of the values 0 (UC), 1 (WC), 4 (WT), 5 (WP),
    6 (WB), or 7 (UC-).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [GIT PULL] KVM fixes for Linux 5.1-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 79a3aaa7b82e3106be97842dedfd8429248896e6:

  Linux 5.1-rc3 (2019-03-31 14:39:29 -0700)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to c73f4c998e1fd4249b9edfa39e23f4fda2b9b041:

  KVM: x86: nVMX: fix x2APIC VTPR read intercept (2019-04-05 21:08:30 +0200)

----------------------------------------------------------------
x86 fixes for overflows and other nastiness.

----------------------------------------------------------------
David Rientjes (2):
      kvm: svm: fix potential get_num_contig_pages overflow
      KVM: SVM: prevent DBG_DECRYPT and DBG_ENCRYPT overflow

Marc Orr (2):
      KVM: x86: nVMX: close leak of L0's x2APIC MSRs (CVE-2019-3887)
      KVM: x86: nVMX: fix x2APIC VTPR read intercept

 arch/x86/kvm/svm.c        | 22 +++++++++-----
 arch/x86/kvm/vmx/nested.c | 74 ++++++++++++++++++++++++++++-------------------
 2 files changed, 59 insertions(+), 37 deletions(-)
```
#### [GIT PULL] VFIO fixes for v5.1-rc4
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit 79a3aaa7b82e3106be97842dedfd8429248896e6:

  Linux 5.1-rc3 (2019-03-31 14:39:29 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.1-rc4

for you to fetch changes up to 492855939bdb59c6f947b0b5b44af9ad82b7e38c:

  vfio/type1: Limit DMA mappings per container (2019-04-03 12:43:05 -0600)

----------------------------------------------------------------
VFIO fixes for v5.1-rc4

 - Fix clang printk format errors (Louis Taylor)

 - Declare structure static to fix sparse warning (Wang Hai)

 - Limit user DMA mappings per container (CVE-2019-3882) (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/type1: Limit DMA mappings per container

Louis Taylor (1):
      vfio/pci: use correct format characters

Wang Hai (1):
      vfio/spapr_tce: Make symbol 'tce_iommu_driver_ops' static

 drivers/vfio/pci/vfio_pci.c         |  4 ++--
 drivers/vfio/vfio_iommu_spapr_tce.c |  2 +-
 drivers/vfio/vfio_iommu_type1.c     | 14 ++++++++++++++
 3 files changed, 17 insertions(+), 3 deletions(-)
```
#### [PATCH 1/2] KVM: x86: nVMX: close leak of L0's x2APIC MSRs (CVE-2019-3887)
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Marc Orr <marcorr@google.com>

The nested_vmx_prepare_msr_bitmap() function doesn't directly guard the
x2APIC MSR intercepts with the "virtualize x2APIC mode" MSR. As a
result, we discovered the potential for a buggy or malicious L1 to get
access to L0's x2APIC MSRs, via an L2, as follows.

1. L1 executes WRMSR(IA32_SPEC_CTRL, 1). This causes the spec_ctrl
variable, in nested_vmx_prepare_msr_bitmap() to become true.
2. L1 disables "virtualize x2APIC mode" in VMCS12.
3. L1 enables "APIC-register virtualization" in VMCS12.

Now, KVM will set VMCS02's x2APIC MSR intercepts from VMCS12, and then
set "virtualize x2APIC mode" to 0 in VMCS02. Oops.

This patch closes the leak by explicitly guarding VMCS02's x2APIC MSR
intercepts with VMCS12's "virtualize x2APIC mode" control.

The scenario outlined above and fix prescribed here, were verified with
a related patch in kvm-unit-tests titled "Add leak scenario to
virt_x2apic_mode_test".

Note, it looks like this issue may have been introduced inadvertently
during a merge---see 15303ba5d1cd.

Signed-off-by: Marc Orr <marcorr@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 72 +++++++++++++++++++++++++++++------------------
 1 file changed, 44 insertions(+), 28 deletions(-)

```
#### [PATCH kvm-unit-tests 1/6] Test nested APIC-register virtualization
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Marc Orr <marcorr@google.com>

This patch adds a test to validate the APIC-register virtualization
execution control with nested virtualization. Specific test cases
include: APIC-access virtualization, APIC-access virtualization with Use
TPR Shadow, and APIC-register virtualization.

Signed-off-by: Marc Orr <marcorr@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/apic.h  |   6 +
 x86/vmx_tests.c | 442 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 448 insertions(+)

```
