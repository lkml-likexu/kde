

#### [PATCH V5 0/4] Fix kvm misconceives NVDIMM pages as reserved mmio
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c

For device specific memory space, when we move these area of pfn to
memory zone, we will set the page reserved flag at that time, some of
these reserved for device mmio, and some of these are not, such as
NVDIMM pmem.

Now, we map these dev_dax or fs_dax pages to kvm for DIMM/NVDIMM
backend, since these pages are reserved. the check of
kvm_is_reserved_pfn() misconceives those pages as MMIO. Therefor, we
introduce 2 page map types, MEMORY_DEVICE_FS_DAX/MEMORY_DEVICE_DEV_DAX,
to indentify these pages are from NVDIMM pmem. and let kvm treat these
as normal pages.

Without this patch, Many operations will be missed due to this
mistreatment to pmem pages. For example, a page may not have chance to
be unpinned for KVM guest(in kvm_release_pfn_clean); not able to be
marked as dirty/accessed(in kvm_set_pfn_dirty/accessed) etc.

V1:
https://lkml.org/lkml/2018/7/4/91

V2:
https://lkml.org/lkml/2018/7/10/135

V3:
https://lkml.org/lkml/2018/8/9/17

V4:
https://lkml.org/lkml/2018/8/22/17

V5:
[PATCH V3 1/4] Reviewed-by: David / Acked-by: Pankaj
[PATCH V3 2/4] Reviewed-by: Jan
[PATCH V3 3/4] Acked-by: Jan
[PATCH V3 4/4] Added "Acked-by: Pankaj", Added in-line comments: Dave

Zhang Yi (4):
  kvm: remove redundant reserved page check
  mm: introduce memory type MEMORY_DEVICE_DEV_DAX
  mm: add a function to differentiate the pages is from DAX device
    memory
  kvm: add a check if pfn is from NVDIMM pmem.

 drivers/dax/pmem.c       |  1 +
 include/linux/memremap.h |  8 ++++++++
 include/linux/mm.h       | 12 ++++++++++++
 virt/kvm/kvm_main.c      | 24 ++++++++++++++++--------
 4 files changed, 37 insertions(+), 8 deletions(-)
```
#### [PATCH v6 0/5] x86: Fix SEV guest regression
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

Brijesh Singh (5):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: fix sme_populate_pgd() to update page flags
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute in shared variables
  x86/kvm: Avoid dynamic allocation of pvclock data when SEV is active

 arch/x86/include/asm/mem_encrypt.h |  10 ++
 arch/x86/kernel/head64.c           |  11 ++
 arch/x86/kernel/kvmclock.c         |  18 ++-
 arch/x86/kernel/vmlinux.lds.S      |  20 ++++
 arch/x86/mm/init.c                 |   3 +
 arch/x86/mm/mem_encrypt.c          |  10 ++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 7 files changed, 240 insertions(+), 64 deletions(-)
```
