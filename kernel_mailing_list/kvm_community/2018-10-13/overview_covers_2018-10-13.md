

#### [PATCH v2 0/2] kvm "fake DAX" device
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "fake DAX". 
 "fake DAX" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v1. Tested with Qemu side device 
 emulation for virtio-pmem [4]. 
 
 Details of project idea for 'fake DAX' flushing interface 
 is shared [2] & [3].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

   David Hildenbrand CCed also posted a modified version[5] of 
   qemu virtio-pmem code based on updated Qemu memory device API. 

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v1: [1]
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Changes from RFC v3
- Rebase to latest upstream - Luiz
- Call ndregion->flush in place of nvdimm_flush- Luiz
- kmalloc return check - Luiz
- virtqueue full handling - Stefan
- Don't map entire virtio_pmem_req to device - Stefan
- request leak, correct sizeof req- Stefan
- Move declaration to virtio_pmem.c

Changes from RFC v2:
- Add flush function in the nd_region in place of switching
  on a flag - Dan & Stefan
- Add flush completion function with proper locking and wait
  for host side flush completion - Stefan & Dan
- Keep userspace API in uapi header file - Stefan, MST
- Use LE fields & New device id - MST
- Indentation & spacing suggestions - MST & Eric
- Remove extra header files & add licensing - Stefan

Changes from RFC v1:
- Reuse existing 'pmem' code for registering persistent 
  memory and other operations instead of creating an entirely 
  new block driver.
- Use VIRTIO driver to register memory information with 
  nvdimm_bus and create region_type accordingly. 
- Call VIRTIO flush from existing pmem driver.

Pankaj Gupta (2):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver

[1] https://lkml.org/lkml/2018/8/31/407
[2] https://www.spinics.net/lists/kvm/msg149761.html
[3] https://www.spinics.net/lists/kvm/msg153095.html  
[4] https://lkml.org/lkml/2018/8/31/413
[5] https://marc.info/?l=qemu-devel&m=153555721901824&w=2

 drivers/acpi/nfit/core.c     |    8 ++--
 drivers/nvdimm/claim.c       |   12 ++++--
 drivers/nvdimm/nd.h          |    2 +
 drivers/nvdimm/pmem.c        |   24 +++++++++----
 drivers/nvdimm/region_devs.c |   76 ++++++++++++++++++++++++++++++++++++++++---
 include/linux/libnvdimm.h    |   10 ++++-
 6 files changed, 110 insertions(+), 22 deletions(-)
```
#### [PATCH V4 00/15] x86/KVM/Hyper-v: Add HV ept tlb range flush
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

```c

From: Lan Tianyu <Tianyu.Lan@microsoft.com>

For nested memory virtualization, Hyper-v doesn't set write-protect
L1 hypervisor EPT page directory and page table node to track changes 
while it relies on guest to tell it changes via HvFlushGuestAddressLlist
hypercall. HvFlushGuestAddressLlist hypercall provides a way to flush
EPT page table with ranges which are specified by L1 hypervisor.

If L1 hypervisor uses INVEPT or HvFlushGuestAddressSpace hypercall to
flush EPT tlb, Hyper-V will invalidate associated EPT shadow page table
and sync L1's EPT table when next EPT page fault is triggered.
HvFlushGuestAddressLlist hypercall helps to avoid such redundant EPT
page fault and synchronization of shadow page table.


Change since v3:
	1) Remove code of updating "tlbs_dirty" in kvm_flush_remote_tlbs_with_range()
	2) Remove directly tlb flush in the kvm_handle_hva_range()
	3) Move tlb flush in kvm_set_pte_rmapp() to kvm_mmu_notifier_change_pte()
	4) Combine Vitaly's "don't pass EPT configuration info to
vmx_hv_remote_flush_tlb()" fix

Change since v2:
       1) Fix comment in the kvm_flush_remote_tlbs_with_range()
       2) Move HV_MAX_FLUSH_PAGES and HV_MAX_FLUSH_REP_COUNT to
	hyperv-tlfs.h.
       3) Calculate HV_MAX_FLUSH_REP_COUNT in the macro definition
       4) Use HV_MAX_FLUSH_REP_COUNT to define length of gpa_list in
	struct hv_guest_mapping_flush_list.

Change since v1:
       1) Convert "end_gfn" of struct kvm_tlb_range to "pages" in order
          to avoid confusion as to whether "end_gfn" is inclusive or exlusive.
       2) Add hyperv tlb range struct and replace kvm tlb range struct
          with new struct in order to avoid using kvm struct in the hyperv
	  code directly.



Lan Tianyu (15):
  KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
  KVM/MMU: Add tlb flush with range helper function
  KVM: Replace old tlb flush function with new one to flush a specified
    range.
  KVM: Make kvm_set_spte_hva() return int
  KVM/MMU: Move tlb flush in kvm_set_pte_rmapp() to
    kvm_mmu_notifier_change_pte()
  KVM/MMU: Flush tlb directly in the kvm_set_pte_rmapp()
  KVM/MMU: Flush tlb directly in the kvm_zap_gfn_range()
  KVM/MMU: Flush tlb directly in kvm_mmu_zap_collapsible_spte()
  KVM: Add flush_link and parent_pte in the struct kvm_mmu_page
  KVM: Add spte's point in the struct kvm_mmu_page
  KVM/MMU: Replace tlb flush function with range list flush function
  x86/hyper-v: Add HvFlushGuestAddressList hypercall support
  x86/Hyper-v: Add trace in the
    hyperv_nested_flush_guest_mapping_range()
  KVM/VMX: Change hv flush logic when ept tables are mismatched.
  KVM/VMX: Add hv tlb range flush support

 arch/arm/include/asm/kvm_host.h     |   2 +-
 arch/arm64/include/asm/kvm_host.h   |   2 +-
 arch/mips/include/asm/kvm_host.h    |   2 +-
 arch/mips/kvm/mmu.c                 |   3 +-
 arch/powerpc/include/asm/kvm_host.h |   2 +-
 arch/powerpc/kvm/book3s.c           |   3 +-
 arch/powerpc/kvm/e500_mmu_host.c    |   3 +-
 arch/x86/hyperv/nested.c            |  85 ++++++++++++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h  |  32 +++++++++
 arch/x86/include/asm/kvm_host.h     |  12 +++-
 arch/x86/include/asm/mshyperv.h     |  16 +++++
 arch/x86/include/asm/trace/hyperv.h |  14 ++++
 arch/x86/kvm/mmu.c                  | 138 ++++++++++++++++++++++++++++++------
 arch/x86/kvm/paging_tmpl.h          |  10 ++-
 arch/x86/kvm/vmx.c                  |  70 +++++++++++++++---
 virt/kvm/arm/mmu.c                  |   6 +-
 virt/kvm/kvm_main.c                 |   5 +-
 17 files changed, 360 insertions(+), 45 deletions(-)
```
#### [PATCH V5 0/3] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is based on coalesced mmio and can be used for some port
like rtc port, pci-host config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest
access rtc frequently because of rtc as system tick. guest access rtc like
this: write register index to 0x70, then write or read data from 0x71.
writing 0x70 port is just as index and do nothing else. So we can use
coalesced pio to handle this scene to reduce VM-EXIT time.

When starting and closing a virtual machine, it will access pci-host config
port frequently. So setting these port as coalesced pio can reduce startup 
and shutdown time. 

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)


Peng Hao (3):
  kvm/x86 : add coalesced pio support
  kvm/x86 : add document for coalesced mmio
  kvm/x86 : add document for coalesced pio

 Documentation/virtual/kvm/api.txt             | 28 +++++++++++++++++++++++++++
 include/uapi/linux/kvm.h                      | 11 +++++++++--
 virt/kvm/coalesced_mmio.c                     | 12 +++++++++---
 virt/kvm/kvm_main.c                           |  2 ++
 4 files changed, 48 insertions(+), 5 deletions(-)
```
