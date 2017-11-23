

#### [PATCH v3 0/3]: KVM: nVMX: Fix bugs in MPX VMX controls emulation
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to fix 3 issues in MPX VMX controls emulation.

The 1st patch makes sure that we don't expose MPX VMX controls to guest
in case vCPU doesn't support MPX (It is not exposed via CPUID).

The 2nd patch make sure we expose BNDCFGS MSR and virtualize MPX VMX controls
only in guest host MPX is enabled.

The 3nd patch fixes an issue in emulation of VM_ENTRY_LOAD_BNDCFGS.

Regards,
-Liran

v1->v2 Changes:
Fixed enter_vmx_non_root_mode() change to not vmcs_read(GUEST_BNDCFGS)
in case !vmx_mpx_supported() (Thanks to Sean J Christopherson)

v2->v3 Changes:
Added 2nd patch as suggested by Sean Christopherson)
```
#### [PATCH 0/2]: KVM: i386: Add support for save and restore nested state
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to add support for QEMU to be able to migrate VMs that
are running nested hypervisors. In order to do so, it utilizes the new
IOCTLs introduced in KVM commit 8fcc4b5923af ("kvm: nVMX: Introduce
KVM_CAP_NESTED_STATE") which were created for this purpose.

1st patch is not really related to the goal of the patch series. It just
makes CPUX86State->xsave_buf to be compiled only when needed (When
compiling with KVM or HVF CPU accelerator).

2nd patch adds the support to migrate VMs that are running nested
hypervisors.

Regards,
-Liran
```
#### [PATCH v9 0/2] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Changes since v8:
 - restore the C-bit before freeing unused decrypted memory
 - fix compiler warning when NR_CPUS=1

Changes since v7:
 - As per Thomas Gleixner suggestion move the decrypted data in .bss..decrypted section
 - remove the second auxiliary array from SEV case
 - allocate memory for pvclock data pointer early and map with C=0 for SEV case

Changes since v6:
 - improve commit messages
 - rename free_decrypted_mem -> mem_encrypt_free_decrypted_mem

Changes since v5:
 - rename hvclock_boot_dec -> hvclock_boot_aux.
 - rename section from .data..decrypted_aux -> .data..decrypted.aux.
 - use NR_CPUS instead of random number elements in hv_clock_aux variable.

Changes since v4:
 - define few static pages in .data..decrypted which can be used
   for cpus > HVC_BOOT_ARRAY_SIZE when SEV is active.

Changes since v3:
 - commit message improvements (based on Sean's feedback)

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (2):
  x86/mm: add .bss..decrypted section to hold shared variables
  x86/kvm: use __bss_decrypted attribute in shared variables

 arch/x86/include/asm/mem_encrypt.h |  7 +++++
 arch/x86/kernel/head64.c           | 16 ++++++++++++
 arch/x86/kernel/kvmclock.c         | 52 +++++++++++++++++++++++++++++++++++---
 arch/x86/kernel/vmlinux.lds.S      | 19 ++++++++++++++
 arch/x86/mm/init.c                 |  4 +++
 arch/x86/mm/mem_encrypt.c          | 24 ++++++++++++++++++
 6 files changed, 119 insertions(+), 3 deletions(-)
```
