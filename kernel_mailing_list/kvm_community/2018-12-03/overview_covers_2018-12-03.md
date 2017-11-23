

#### [PATCH v4 00/14] KVM/X86: Introduce a new guest mapping interface
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c

Guest memory can either be directly managed by the kernel (i.e. have a "struct
page") or they can simply live outside kernel control (i.e. do not have a
"struct page"). KVM mostly support these two modes, except in a few places
where the code seems to assume that guest memory must have a "struct page".

This patchset introduces a new mapping interface to map guest memory into host
kernel memory which also supports PFN-based memory (i.e. memory without 'struct
page'). It also converts all offending code to this interface or simply
read/write directly from guest memory.

As far as I can see all offending code is now fixed except the APIC-access page
which I will handle in a seperate series along with dropping
kvm_vcpu_gfn_to_page and kvm_vcpu_gpa_to_page from the internal KVM API.

The current implementation of the new API uses memremap to map memory that does
not have a "struct page". This proves to be very slow for high frequency
mappings. Since this does not affect the normal use-case where a "struct page"
is available, the performance of this API will be handled by a seperate patch
series.

v3 -> v4:
- Rebase
- Add a new patch to also fix the newly introduced enhanced VMCS.

v2 -> v3:
- Rebase
- Add a new patch to also fix the newly introduced shadow VMCS.

Filippo Sironi (1):
  X86/KVM: Handle PFNs outside of kernel reach when touching GPTEs

KarimAllah Ahmed (13):
  X86/nVMX: handle_vmon: Read 4 bytes from guest memory
  X86/nVMX: handle_vmptrld: Copy the VMCS12 directly from guest memory
  X86/nVMX: Update the PML table without mapping and unmapping the page
  KVM: Introduce a new guest mapping API
  KVM/nVMX: Use kvm_vcpu_map when mapping the L1 MSR bitmap
  KVM/nVMX: Use kvm_vcpu_map when mapping the virtual APIC page
  KVM/nVMX: Use kvm_vcpu_map when mapping the posted interrupt
    descriptor table
  KVM/X86: Use kvm_vcpu_map in emulator_cmpxchg_emulated
  KVM/X86: hyperv: Use kvm_vcpu_map in synic_clear_sint_msg_pending
  KVM/X86: hyperv: Use kvm_vcpu_map in synic_deliver_msg
  KVM/nSVM: Use the new mapping API for mapping guest memory
  KVM/nVMX: Use kvm_vcpu_map for accessing the shadow VMCS
  KVM/nVMX: Use kvm_vcpu_map for accessing the enhanced VMCS

 arch/x86/kvm/hyperv.c      |  28 +++----
 arch/x86/kvm/paging_tmpl.h |  38 ++++++---
 arch/x86/kvm/svm.c         |  97 +++++++++++------------
 arch/x86/kvm/vmx.c         | 189 +++++++++++++++++----------------------------
 arch/x86/kvm/x86.c         |  13 ++--
 include/linux/kvm_host.h   |   9 +++
 virt/kvm/kvm_main.c        |  50 ++++++++++++
 7 files changed, 228 insertions(+), 196 deletions(-)
```
#### [PATCH RFC 0/3] Fix KVM misinterpreting Reserved page as an MMIO
##### From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

```c

I have loosely based this patch series off of the following patch series
from Zhang Yi:
https://lore.kernel.org/lkml/cover.1536342881.git.yi.z.zhang@linux.intel.com

The original set had attempted to address the fact that DAX pages were
treated like MMIO pages which had resulted in reduced performance. It
attempted to address this by ignoring the PageReserved flag if the page
was either a DEV_DAX or FS_DAX page.

I am proposing this as an alternative to that set. The main reason for this
is because I believe there are a few issues that were overlooked with that
original set. Specifically KVM seems to have two different uses for the
PageReserved flag. One being whether or not we can pin the memory, the other
being if we should be marking the pages as dirty or accessed. I believe
only the pinning really applies so I have split the uses of
kvm_is_reserved_pfn and updated the function uses to determine support for
page pinning to include a check of the pgmap to see if it supports pinning.
---

Alexander Duyck (3):
      kvm: Split use cases for kvm_is_reserved_pfn to kvm_is_refcounted_pfn
      mm: Add support for exposing if dev_pagemap supports refcount pinning
      kvm: Add additional check to determine if a page is refcounted


 arch/x86/kvm/mmu.c        |    6 +++---
 drivers/nvdimm/pfn_devs.c |    2 ++
 include/linux/kvm_host.h  |    2 +-
 include/linux/memremap.h  |    5 ++++-
 include/linux/mm.h        |   11 +++++++++++
 virt/kvm/kvm_main.c       |   34 +++++++++++++++++++++++++---------
 6 files changed, 46 insertions(+), 14 deletions(-)

--
```
#### [PATCH 0/3] mmu notifier contextual informations
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

This patchset add contextual information, why an invalidation is
happening, to mmu notifier callback. This is necessary for user
of mmu notifier that wish to maintains their own data structure
without having to add new fields to struct vm_area_struct (vma).

For instance device can have they own page table that mirror the
process address space. When a vma is unmap (munmap() syscall) the
device driver can free the device page table for the range.

Today we do not have any information on why a mmu notifier call
back is happening and thus device driver have to assume that it
is always an munmap(). This is inefficient at it means that it
needs to re-allocate device page table on next page fault and
rebuild the whole device driver data structure for the range.

Other use case beside munmap() also exist, for instance it is
pointless for device driver to invalidate the device page table
when the invalidation is for the soft dirtyness tracking. Or
device driver can optimize away mprotect() that change the page
table permission access for the range.

This patchset enable all this optimizations for device driver.
I do not include any of those in this serie but other patchset
i am posting will leverage this.


From code point of view the patchset is pretty simple, the first
two patches consolidate all mmu notifier arguments into a struct
so that it is easier to add/change arguments. The last patch adds
the contextual information (munmap, protection, soft dirty, clear,
...).

Cheers,
Jérôme

Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Felix Kuehling <felix.kuehling@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org

Jérôme Glisse (3):
  mm/mmu_notifier: use structure for invalidate_range_start/end callback
  mm/mmu_notifier: use structure for invalidate_range_start/end calls
  mm/mmu_notifier: contextual information for event triggering
    invalidation

 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  |  43 ++++-----
 drivers/gpu/drm/i915/i915_gem_userptr.c |  14 ++-
 drivers/gpu/drm/radeon/radeon_mn.c      |  16 ++--
 drivers/infiniband/core/umem_odp.c      |  20 ++---
 drivers/infiniband/hw/hfi1/mmu_rb.c     |  13 ++-
 drivers/misc/mic/scif/scif_dma.c        |  11 +--
 drivers/misc/sgi-gru/grutlbpurge.c      |  14 ++-
 drivers/xen/gntdev.c                    |  12 +--
 fs/dax.c                                |  11 ++-
 fs/proc/task_mmu.c                      |  10 ++-
 include/linux/mm.h                      |   4 +-
 include/linux/mmu_notifier.h            | 106 +++++++++++++++-------
 kernel/events/uprobes.c                 |  13 +--
 mm/hmm.c                                |  23 ++---
 mm/huge_memory.c                        |  58 ++++++------
 mm/hugetlb.c                            |  63 +++++++------
 mm/khugepaged.c                         |  13 +--
 mm/ksm.c                                |  26 +++---
 mm/madvise.c                            |  22 ++---
 mm/memory.c                             | 112 ++++++++++++++----------
 mm/migrate.c                            |  30 ++++---
 mm/mmu_notifier.c                       |  22 +++--
 mm/mprotect.c                           |  17 ++--
 mm/mremap.c                             |  14 +--
 mm/oom_kill.c                           |  20 +++--
 mm/rmap.c                               |  34 ++++---
 virt/kvm/kvm_main.c                     |  14 ++-
 27 files changed, 421 insertions(+), 334 deletions(-)
```
#### [PATCH 00/28]  KVM: VMX: Add "vmx" dir and shatter vmx.c
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The ultimate goal of this series is to break vmx.c's monopoly on all
things VMX so that it's size goes from utterly ludicrous to merely
ridiculous.  For the most part the patches are simply moving code
around.  There are a few actual code changes sprinkled in, primarily
to allow moving the nested code out of vmx.c without having to expose
variables unnecessarily.

Sean Christopherson (28):
  KVM: nVMX: Free the VMREAD/VMWRITE bitmaps if alloc_kvm_area() fails
  KVM: nVMX: Allocate and configure VM{READ,WRITE} bitmaps iff
    enable_shadow_vmcs
  KVM: VMX: Alphabetize the includes in vmx.c
  KVM: x86: Add requisite includes to kvm_cache_regs.h
  KVM: x86: Add requisite includes to hyperv.h
  KVM: VMX: Move VMX specific files to a "vmx" subdirectory
  KVM: VMX: rename vmx_shadow_fields.h to vmcs_shadow_fields.h
  KVM: VMX: Drop the "vmx" prefix from vmx_evmcs.h
  KVM: VMX: Move caching of MSR_IA32_XSS to hardware_setup()
  KVM: VMX: Properly handle dynamic VM Entry/Exit controls
  KVM: VMX: Pass vmx_capability struct to setup_vmcs_config()
  KVM: VMX: Move capabilities structs and helpers to dedicated file
  KVM: VMX: Expose various module param vars via capabilities.h
  KVM: VMX: Move VMCS definitions to dedicated file
  KVM: nVMX: Move vmcs12 code to dedicated files
  KVM: VMX: Move eVMCS code dedicated files
  KVM: VMX: Move VMX instruction wrappers to a dedicated header file
  KVM: VMX: Add vmx.h to hold VMX definitions and inline functions
  KVM: VMX: Move nested hardware/vcpu {un}setup to helper functions
  KVM: x86: nVMX: Allow nested_enable_evmcs to be NULL
  KVM: VMX: Move the hardware {un}setup functions to the bottom
  KVM: nVMX: Set callbacks for nested functions during hardware setup
  KVM: nVMX: Call nested_vmx_setup_ctls_msrs() iff @nested is true
  KVM: nVMX: Move "vmcs12 to shadow/evmcs sync" to helper function
  KVM: VMX: Expose misc variables needed for nested VMX
  KVM: VMX: Expose various getters and setters to nested VMX
  KVM: VMX: Expose nested_vmx_allowed() to nested VMX as a non-inline
  KVM: nVMX: Move nested code to dedicated files

 arch/x86/kvm/Makefile                         |     2 +-
 arch/x86/kvm/hyperv.h                         |     2 +
 arch/x86/kvm/kvm_cache_regs.h                 |     2 +
 arch/x86/kvm/vmx.c                            | 15290 ----------------
 arch/x86/kvm/vmx/capabilities.h               |   328 +
 arch/x86/kvm/{vmx_evmcs.h => vmx/evmcs.c}     |    47 +-
 arch/x86/kvm/vmx/evmcs.h                      |   198 +
 arch/x86/kvm/vmx/nested.c                     |  5703 ++++++
 arch/x86/kvm/vmx/nested.h                     |   282 +
 arch/x86/kvm/vmx/ops.h                        |   285 +
 arch/x86/kvm/{ => vmx}/pmu_intel.c            |     0
 arch/x86/kvm/vmx/vmcs.h                       |   136 +
 arch/x86/kvm/vmx/vmcs12.c                     |   157 +
 arch/x86/kvm/vmx/vmcs12.h                     |   462 +
 .../vmcs_shadow_fields.h}                     |     0
 arch/x86/kvm/vmx/vmx.c                        |  7392 ++++++++
 arch/x86/kvm/vmx/vmx.h                        |   602 +
 arch/x86/kvm/x86.c                            |     2 +
 18 files changed, 15570 insertions(+), 15320 deletions(-)
 delete mode 100644 arch/x86/kvm/vmx.c
 create mode 100644 arch/x86/kvm/vmx/capabilities.h
 rename arch/x86/kvm/{vmx_evmcs.h => vmx/evmcs.c} (94%)
 create mode 100644 arch/x86/kvm/vmx/evmcs.h
 create mode 100644 arch/x86/kvm/vmx/nested.c
 create mode 100644 arch/x86/kvm/vmx/nested.h
 create mode 100644 arch/x86/kvm/vmx/ops.h
 rename arch/x86/kvm/{ => vmx}/pmu_intel.c (100%)
 create mode 100644 arch/x86/kvm/vmx/vmcs.h
 create mode 100644 arch/x86/kvm/vmx/vmcs12.c
 create mode 100644 arch/x86/kvm/vmx/vmcs12.h
 rename arch/x86/kvm/{vmx_shadow_fields.h => vmx/vmcs_shadow_fields.h} (100%)
 create mode 100644 arch/x86/kvm/vmx/vmx.c
 create mode 100644 arch/x86/kvm/vmx/vmx.h
```
