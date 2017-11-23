

#### [PATCH 00/10] x86: PTE D Bit based dirty logging
##### From: Junaid Shahid <junaids@google.com>

```c

This patch series implements a new dirty logging mode utilizing the Dirty
bits in the SPTEs, when available, instead of relying on write protection.
On hosts that do not support PML, this can result in significant
improvement in VM performance for some workloads during the brownout phase
of a live migration when compared to write protection based dirty logging,
because of the elimination of all the VM exits on memory writes.

However, this new mode does incur additional time in the get_dirty_log
IOCTL because of having to scan all the SPTEs for dirtiness, which can
in some cases, result in slightly elongating the blackout time. Two
strategies can be used to mitigate that. The first, included in this
series, is to have the ability to dynamically switch between D Bit based
and write protection based dirty logging modes. Then the mode could be
switched to write protection just before entering blackout, thus incurring
less time in the get_dirty_log IOCTL during blackout, while keeping the
reduced overhead of the D Bit based mode during brownout. Secondly, the
scan in the get_dirty_log IOCTL can be parallelized, which results in that
IOCTL becoming faster for all modes. That patch series will be sent out
separately a little later.

The series also includes a couple of other minor dirty logging related
performance improvements, including removal of extra TLB flushes in one
instance and more efficient functions for testing/clearing Writable/Dirty
bits.

Junaid Shahid (10):
  kvm: mmu: spte_write_protect optimization
  kvm: mmu: Allow reading hardware dirty state from
    kvm_get_dirty_log_protect
  kvm: x86: mmu: Change __rmap_clear_dirty to
    __rmap_test_and_clear_dirty
  kvm: mmu: x86: Add dirty bit clearing notification hook
  kvm: x86: mmu: Remove extra TLB flush from vmx_slot_enable_log_dirty()
  kvm: x86: mmu: Use D bit for dirty logging
  kvm: x86: mmu: Per-VM dirty logging mode
  kvm: x86: mmu: Refactor kvm_mmu_slot_*_remove_write_access
  kvm: x86: mmu: Ability to switch dirty logging mode dynamically
  kvm: x86: mmu: Add IOCTLs to allow userspace to switch dirty logging
    mode

 Documentation/virtual/kvm/api.txt |  39 +++
 arch/mips/kvm/mmu.c               |  16 +-
 arch/x86/include/asm/kvm_host.h   |  27 ++-
 arch/x86/include/uapi/asm/kvm.h   |   5 +
 arch/x86/kvm/mmu.c                | 390 +++++++++++++++++++++++++-----
 arch/x86/kvm/mmu.h                |   3 +
 arch/x86/kvm/vmx.c                |  20 +-
 arch/x86/kvm/x86.c                |  54 ++++-
 include/linux/kvm_host.h          |   8 +-
 include/uapi/linux/kvm.h          |   3 +
 virt/kvm/arm/mmu.c                |   9 +-
 virt/kvm/kvm_main.c               |  21 +-
 12 files changed, 482 insertions(+), 113 deletions(-)
```
#### [kvm PATCH 0/2] kvm: vmalloc vmx vcpus
##### From: Marc Orr <marcorr@google.com>

```c

Patch series to allocate vmx vcpus with vmalloc() instead of kalloc().
This enables vendors to pack more VMs on a single host.

Marc Orr (2):
  mm: export __vmalloc_node_range()
  kvm: vmx: use vmalloc() to allocate vcpus

 arch/x86/kvm/vmx.c  | 98 +++++++++++++++++++++++++++++++++++++++++----
 mm/vmalloc.c        |  1 +
 virt/kvm/kvm_main.c | 28 +++++++------
 3 files changed, 107 insertions(+), 20 deletions(-)
```
#### [PATCH v3 00/13] KVM/X86: Introduce a new guest mapping interface
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

v3 -> v2:

- rebase
- Add a new patch to also fix the newly introducing shadow VMCS support for
  nested.

Filippo Sironi (1):
  X86/KVM: Handle PFNs outside of kernel reach when touching GPTEs

KarimAllah Ahmed (12):
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

 arch/x86/kvm/hyperv.c      |  28 ++++----
 arch/x86/kvm/paging_tmpl.h |  38 ++++++++---
 arch/x86/kvm/svm.c         |  97 +++++++++++++-------------
 arch/x86/kvm/vmx.c         | 167 +++++++++++++++++----------------------------
 arch/x86/kvm/x86.c         |  13 ++--
 include/linux/kvm_host.h   |   9 +++
 virt/kvm/kvm_main.c        |  50 ++++++++++++++
 7 files changed, 217 insertions(+), 185 deletions(-)
```
