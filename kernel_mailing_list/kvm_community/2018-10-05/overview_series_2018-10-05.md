#### [PATCH 1/1][kvm-unit-test] nVMX x86: Check enable-EPT on vmentry of L2 guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following check needs to be enforced on vmentry of L2 guests:

  If the "unrestricted guest" VM-execution control is 1, the "enable EPT"
  VM-execution control must also be 1.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 x86/vmx_tests.c | 56 ++++++++++++++++++++++++++++++++++++++++++--------------
 1 file changed, 42 insertions(+), 14 deletions(-)

```
#### [GIT PULL] KVM changes for 4.19-rc7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Greg,

The following changes since commit a27fb6d983c7b5bb0129ae4d7a7c81758173bfab:

  Merge tag 'for-linus' of git://git.kernel.org/pub/scm/virt/kvm/kvm (2018-09-21 16:21:42 +0200)

are available in the git repository at:


  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to cc906f07d7d569a30bb6f0baf8f80b2968353dc9:

  Merge tag 'kvm-ppc-fixes-4.19-3' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into kvm-master (2018-10-05 09:39:53 +0200)

----------------------------------------------------------------

x86 and PPC bugfixes, mostly introduced in 4.19-rc1.

----------------------------------------------------------------
Liran Alon (3):
      KVM: nVMX: Do not expose MPX VMX controls when guest MPX disabled
      KVM: x86: Do not use kvm_x86_ops->mpx_supported() directly
      KVM: nVMX: Fix emulation of VM_ENTRY_LOAD_BNDCFGS

Paolo Bonzini (4):
      KVM: x86: never trap MSR_KERNEL_GS_BASE
      KVM: VMX: hide flexpriority from guest when disabled at the module level
      kvm: nVMX: fix entry with pending interrupt if APICv is enabled
      Merge tag 'kvm-ppc-fixes-4.19-3' of git://git.kernel.org/.../paulus/powerpc into kvm-master

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Avoid crash from THP collapse during radix page fault

Sean Christopherson (2):
      KVM: x86: fix L1TF's MMIO GFN calculation
      KVM: VMX: check for existence of secondary exec controls before accessing

Stefan Raspl (1):
      tools/kvm_stat: cut down decimal places in update interval dialog

 arch/powerpc/kvm/book3s_64_mmu_radix.c |  10 +++
 arch/x86/kvm/mmu.c                     |  24 +++++-
 arch/x86/kvm/vmx.c                     | 137 ++++++++++++++++++---------------
 arch/x86/kvm/x86.c                     |   2 +-
 tools/kvm/kvm_stat/kvm_stat            |   2 +-
 5 files changed, 108 insertions(+), 67 deletions(-)
```
#### [GIT PULL] Please pull my kvm-ppc-fixes-4.19-3 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-4.19-3 tag to get one commit
that fixes a host crash that I have seen when a page fault on a radix
guest on POWER9 happens concurrently with a THP collapse operation.
The bug is only in 4.19-rc and hence the fix does not need to be
backported to any stable kernel tree.

Thanks,
Paul.

The following changes since commit 71d29f43b6332badc5598c656616a62575e83342:

  KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size (2018-09-12 08:50:50 +1000)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-4.19-3

for you to fetch changes up to 6579804c431712d56956a63b1a01509441cc6800:

  KVM: PPC: Book3S HV: Avoid crash from THP collapse during radix page fault (2018-10-04 14:51:11 +1000)

----------------------------------------------------------------
Third set of PPC KVM fixes for 4.19

One patch here, fixing a potential host crash introduced (or at least
exacerbated) by a previous fix for corruption relating to radix guest
page faults and THP operations.

----------------------------------------------------------------
Paul Mackerras (1):
      KVM: PPC: Book3S HV: Avoid crash from THP collapse during radix page fault

 arch/powerpc/kvm/book3s_64_mmu_radix.c | 10 ++++++++++
 1 file changed, 10 insertions(+)
```
#### [PATCH v1 1/2] KVM: s390: Tracing APCB changes
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
kvm_arch_crypto_set_masks is a new function to centralize
the setup the APCB masks inside the CRYCB SIE satelite.

To trace APCB mask changes, we add KVM_EVENT() tracing to
both kvm_arch_crypto_set_masks and kvm_arch_crypto_clear_masks.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/kvm_host.h |  2 ++
 arch/s390/kvm/kvm-s390.c         | 41 ++++++++++++++++++++++++++++++++++++++++
 2 files changed, 43 insertions(+)

```
#### [PATCH] KVM: X86: Add missing KVM_AMD dependency
##### From: Guenter Roeck <linux@roeck-us.net>

```c
Building an image with KVM_AMD=y, CRYPTO_DEV_SP_PSP=y, and
CRYPTO_DEV_CCP_DD=m fails with the following error messages.

arch/x86/kvm/svm.c:6287: undefined reference to `sev_issue_cmd_external_user'
arch/x86/kvm/svm.o: In function `sev_unbind_asid':
arch/x86/kvm/svm.c:1747: undefined reference to `sev_guest_deactivate'
arch/x86/kvm/svm.c:1750: undefined reference to `sev_guest_df_flush'
arch/x86/kvm/svm.c:1759: undefined reference to `sev_guest_decommission'

Analysis shows that commit 59414c9892208 ("KVM: SVM: Add support for
KVM_SEV_LAUNCH_START command") added a dependency of KVM_AMD on
CRYPTO_DEV_CCP_DD if CRYPTO_DEV_SP_PSP is enabled: If CRYPTO_DEV_CCP_DD
is built as module, KVM_AMD must be built as module as well.

Fixes: 59414c9892208 ("KVM: SVM: Add support for KVM_SEV_LAUNCH_START command")
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Borislav Petkov <bp@suse.de>
Signed-off-by: Guenter Roeck <linux@roeck-us.net>
---
 arch/x86/kvm/Kconfig | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] s390: vfio-ap: make local functions and data static
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
no functional change, just hygiene.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/crypto/vfio_ap_drv.c |  4 ++--
 drivers/s390/crypto/vfio_ap_ops.c | 20 ++++++++++----------
 2 files changed, 12 insertions(+), 12 deletions(-)

```
#### [PATCH] s390: vfio-ap: trace the update of APCB masks
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Define a tracing function to trace in the KVM trace buffer
and trace the changes of the APCB masks.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c     | 22 ++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  4 ++++
 2 files changed, 26 insertions(+)

```
#### [PATCH v2] virtio-gpu: add VIRTIO_GPU_F_EDID feature
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c
The feature allows the guest request an EDID blob (describing monitor
capabilities) for a given scanout (aka virtual monitor connector).

It brings a new command message, which has just a scanout field (beside
the standard virtio-gpu header) and a response message which carries the
EDID data.

Signed-off-by: Gerd Hoffmann <kraxel@redhat.com>
---
 include/uapi/linux/virtio_gpu.h | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
