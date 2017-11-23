

#### [PATCH net-next V2 0/3] basic in order support for vhost_net
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series implement basic in order feature support for
vhost_net. This feature requires both driver and device to use
descriptors in order which can simplify the implementation and
optimizaton for both side. The series also implement a simple
optimization that avoid read available ring. Test shows 10%
performance improvement at most.

More optimizations could be done on top.

Changes from V1:
- no code changes
- add result of SMAP off

Jason Wang (3):
  virtio: introduce in order feature bit
  vhost_net: support in order feature
  vhost: don't touch avail ring if in_order is negotiated

 drivers/vhost/net.c                |  6 ++++--
 drivers/vhost/vhost.c              | 19 ++++++++++++-------
 include/uapi/linux/virtio_config.h |  6 ++++++
 3 files changed, 22 insertions(+), 9 deletions(-)
```
#### [PATCH v5 00/13] KVM/X86: Introduce a new guest mapping interface
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c

Guest memory can either be directly managed by the kernel (i.e. have a "struct
page") or they can simply live outside kernel control (i.e. do not have a
"struct page"). KVM mostly support these two modes, except in a few places
where the code seems to assume that guest memory must have a "struct page".

This patchset introduces a new mapping interface to map guest memory into host
kernel memory which also supports PFN-based memory (i.e. memory without 'struct
page'). It also converts all offending code to this interface or simply
read/write directly from guest memory. Patch 2 is additionally fixing an
incorrect page release and marking the page as dirty (i.e. as a side-effect of
using the helper function to write).

As far as I can see all offending code is now fixed except the APIC-access page
which I will handle in a seperate series along with dropping
kvm_vcpu_gfn_to_page and kvm_vcpu_gpa_to_page from the internal KVM API.

The current implementation of the new API uses memremap to map memory that does
not have a "struct page". This proves to be very slow for high frequency
mappings. Since this does not affect the normal use-case where a "struct page"
is available, the performance of this API will be handled by a seperate patch
series.

v4 -> v5:
- Introduce a new parameter 'dirty' into kvm_vcpu_unmap
- A horrible rebase due to nested.c :)
- Dropped a couple of hyperv patches as the code was fixed already as a
  side-effect of another patch.
- Added a new trivial cleanup patch.

v3 -> v4:
- Rebase
- Add a new patch to also fix the newly introduced enlightned VMCS.

v2 -> v3:
- Rebase
- Add a new patch to also fix the newly introduced shadow VMCS.

Filippo Sironi (1):
  X86/KVM: Handle PFNs outside of kernel reach when touching GPTEs

KarimAllah Ahmed (12):
  X86/nVMX: handle_vmon: Read 4 bytes from guest memory
  X86/nVMX: Update the PML table without mapping and unmapping the page
  KVM: Introduce a new guest mapping API
  X86/nVMX: handle_vmptrld: Use kvm_vcpu_map when copying VMCS12 from
    guest memory
  KVM/nVMX: Use kvm_vcpu_map when mapping the L1 MSR bitmap
  KVM/nVMX: Use kvm_vcpu_map when mapping the virtual APIC page
  KVM/nVMX: Use kvm_vcpu_map when mapping the posted interrupt
    descriptor table
  KVM/X86: Use kvm_vcpu_map in emulator_cmpxchg_emulated
  KVM/nSVM: Use the new mapping API for mapping guest memory
  KVM/nVMX: Use kvm_vcpu_map for accessing the shadow VMCS
  KVM/nVMX: Use kvm_vcpu_map for accessing the enlightened VMCS
  KVM/nVMX: Use page_address_valid in a few more locations

 arch/x86/kvm/paging_tmpl.h |  38 ++++++++---
 arch/x86/kvm/svm.c         |  97 +++++++++++++--------------
 arch/x86/kvm/vmx/nested.c  | 160 ++++++++++++++++-----------------------------
 arch/x86/kvm/vmx/vmx.c     |  19 ++----
 arch/x86/kvm/vmx/vmx.h     |   9 ++-
 arch/x86/kvm/x86.c         |  13 ++--
 include/linux/kvm_host.h   |   9 +++
 virt/kvm/kvm_main.c        |  53 +++++++++++++++
 8 files changed, 217 insertions(+), 181 deletions(-)
```
#### [PATCH v1 0/2] Get DMA information from real IOMMU
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

The zPCI driver needs to get specific information from the host
IOMMU.
In this patch, the IOMMU DMA start and end usable addresses are
retrieved using the VFIO_IOMMU_GET_INFO iotcl by introducing
capabilities to the vfio_iommu_type1_info structure.

Pierre Morel (2):
  vfio:iommu: Use capabilities do report IOMMU informations
  vfio:iommu: Get DMA information from real IOMMU

 drivers/vfio/vfio_iommu_type1.c | 43 ++++++++++++++++++++++++++++++++++++++++-
 include/uapi/linux/vfio.h       |  9 +++++++++
 2 files changed, 51 insertions(+), 1 deletion(-)
```
#### [PATCH v3 0/5] kvm "virtio pmem" device
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v2. Tested with Qemu side device 
 emulation for virtio-pmem [6]. 
 
 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

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

   David Hildenbrand CCed also posted a modified version[6] of 
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

Changes from PATCH v2: [1]
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: [2]
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

Pankaj Gupta (5):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[2] https://lkml.org/lkml/2018/8/31/407
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=qemu-devel&m=153555721901824&w=2

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/super.c              |   17 +++++
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/pmem.c            |   15 +++-
 drivers/nvdimm/region_devs.c     |   45 +++++++++++++-
 drivers/nvdimm/virtio_pmem.c     |   84 ++++++++++++++++++++++++++
 drivers/virtio/Kconfig           |   10 +++
 drivers/virtio/Makefile          |    1 
 drivers/virtio/pmem.c            |  125 +++++++++++++++++++++++++++++++++++++++
 fs/ext4/file.c                   |   11 +++
 fs/xfs/xfs_file.c                |    8 ++
 include/linux/dax.h              |    9 ++
 include/linux/libnvdimm.h        |   11 +++
 include/linux/virtio_pmem.h      |   60 ++++++++++++++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 17 files changed, 406 insertions(+), 12 deletions(-)
```
#### [PATCH 0/3] arm64: KVM: Allow direct function calls on VHE
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

It recently appeared that the nasty hack we use to call a HYP function
on a non-VHE system has an interesting side effect on VHE: We wrap any
such call into a hypercall, losing any form of type checking between
the caller and the callee.

This isn't a big deal if you can guarantee to write code that is
always 100% correct, but it appears that I'm not you.

In order to restore some sanity, let's use the following property: On
a VHE system, it is always possible to call any function directly as
they live in the same address space. We can thus always emit a direct
call, and use a static key to flip from one to the other. As a bonus,
this also sanitizes !VHE systems as we always generate code for noth
revisions of the architecture.

Marc Zyngier (3):
  arm/arm64: KVM: Introduce kvm_call_hyp_ret()
  arm64: KVM: Allow for direct call of HYP functions when using VHE
  arm64: KVM: Drop VHE-specific HYP call stub

 arch/arm/include/asm/kvm_host.h   |  3 +++
 arch/arm64/include/asm/kvm_host.h | 31 ++++++++++++++++++++++++++++++-
 arch/arm64/kvm/debug.c            |  2 +-
 arch/arm64/kvm/hyp.S              |  3 ---
 arch/arm64/kvm/hyp/hyp-entry.S    | 12 ------------
 virt/kvm/arm/arm.c                |  2 +-
 virt/kvm/arm/vgic/vgic-v3.c       |  4 ++--
 7 files changed, 37 insertions(+), 20 deletions(-)
```
#### [PATCH v3 0/5] kvm "virtio pmem" device
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v2. Tested with Qemu side device 
 emulation for virtio-pmem [6]. 
 
 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

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

   David Hildenbrand CCed also posted a modified version[6] of 
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

Changes from PATCH v2: [1]
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: [2]
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

Pankaj Gupta (5):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[2] https://lkml.org/lkml/2018/8/31/407
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=qemu-devel&m=153555721901824&w=2

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/super.c              |   17 +++++
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/pmem.c            |   15 +++-
 drivers/nvdimm/region_devs.c     |   45 +++++++++++++-
 drivers/nvdimm/virtio_pmem.c     |   84 ++++++++++++++++++++++++++
 drivers/virtio/Kconfig           |   10 +++
 drivers/virtio/Makefile          |    1 
 drivers/virtio/pmem.c            |  125 +++++++++++++++++++++++++++++++++++++++
 fs/ext4/file.c                   |   11 +++
 fs/xfs/xfs_file.c                |    8 ++
 include/linux/dax.h              |    9 ++
 include/linux/libnvdimm.h        |   11 +++
 include/linux/virtio_pmem.h      |   60 ++++++++++++++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 17 files changed, 406 insertions(+), 12 deletions(-)
```
