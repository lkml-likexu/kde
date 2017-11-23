#### [PATCH v8 1/2] linux-headers: Update to kernel mainline commit 815f0ddb3
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Update our kernel headers to mainline commit
815f0ddb346c196018d4d8f8f55c12b83da1de3f
(include/linux/compiler*.h: make compiler-*.h mutually exclusive)

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
 include/standard-headers/linux/input.h |  9 +++++----
 linux-headers/asm-arm/kvm.h            | 13 +++++++++++++
 linux-headers/asm-arm64/kvm.h          | 13 +++++++++++++
 linux-headers/linux/kvm.h              |  1 +
 4 files changed, 32 insertions(+), 4 deletions(-)

```
#### [PATCH v2 01/18] KVM: nVMX: move host EFER consistency checks to VMFail path
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Invalid host state related to loading EFER on VMExit causes a
VMFail(VMXERR_ENTRY_INVALID_HOST_STATE_FIELD), not a VMExit.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx.c | 31 ++++++++++++++++---------------
 1 file changed, 16 insertions(+), 15 deletions(-)

```
#### [PATCH] KVM: x86: SVM: remove unused variable dst_vaddr_end
##### From: Colin King <colin.king@canonical.com>

```c
From: Colin Ian King <colin.king@canonical.com>

Variable dst_vaddr_end is being assigned but is never used hence it is
redundant and can be removed.

Cleans up clang warning:
variable 'dst_vaddr_end' set but not used [-Wunused-but-set-variable]

Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 arch/x86/kvm/svm.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2 1/3] x86/mm: Restructure sme_encrypt_kernel()
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Re-arrange the sme_encrypt_kernel() by moving the workarea map/unmap
logic in a separate static function. There are no logical changes in this
patch. The restructuring will allow us to expand the sme_encrypt_kernel
in future.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Cc: stable@vger.kernel.org
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: kvm@vger.kernel.org
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
---
 arch/x86/mm/mem_encrypt_identity.c | 160 ++++++++++++++++++++++++-------------
 1 file changed, 104 insertions(+), 56 deletions(-)

```
