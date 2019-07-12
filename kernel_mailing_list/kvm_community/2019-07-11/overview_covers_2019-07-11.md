

#### [PATCH v9 00/14] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

The IOMMU API is extended to support 3 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings
3) invalidate stage 1 related caches

3) is also used for SVA use case [1].

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.3.0-rc0-2stage-v9

References:
[1] [PATCH v4 00/22]  Shared virtual address IOMMU and VT-d support

History:

v8 -> v9:
- rebase on 5.3
- split iommu/vfio parts

v6 -> v8:
- Implement VFIO-PCI device specific interrupt framework

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (11):
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Dynamically allocate s1_cfg and s2_cfg
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Introduce __arm_smmu_tlb_inv_asid/s1_range_nosync
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults

Jacob Pan (1):
  iommu: Introduce attach/detach_pasid_table API

Jean-Philippe Brucker (1):
  iommu/arm-smmu-v3: Maintain a SID->device structure

Yi L Liu (1):
  iommu: Introduce cache_invalidate API

 drivers/iommu/arm-smmu-v3.c | 817 ++++++++++++++++++++++++++++++++----
 drivers/iommu/dma-iommu.c   | 139 +++++-
 drivers/iommu/iommu.c       |  66 +++
 include/linux/dma-iommu.h   |  16 +
 include/linux/iommu.h       |  52 +++
 include/uapi/linux/iommu.h  | 161 +++++++
 6 files changed, 1162 insertions(+), 89 deletions(-)
```
#### [PATCH v9 00/11] SMMUv3 Nested Stage Setup (VFIO part)
##### From: Eric Auger <eric.auger@redhat.com>

```c

This series brings the VFIO part of HW nested paging support
in the SMMUv3.

The series depends on:
[PATCH v9 00/14] SMMUv3 Nested Stage Setup (IOMMU part)
(https://www.spinics.net/lists/kernel/msg3187714.html)

3 new IOCTLs are introduced that allow the userspace to
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings
3) invalidate stage 1 related caches

They map onto the related new IOMMU API functions.

We introduce the capability to register specific interrupt
indexes (see [1]). A new DMA_FAULT interrupt index allows to register
an eventfd to be signaled whenever a stage 1 related fault
is detected at physical level. Also a specific region allows
to expose the fault records to the user space.

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v5.3.0-rc0-2stage-v9

It series includes Tina's patch steming from
[1] "[RFC PATCH v2 1/3] vfio: Use capability chains to handle device
specific irq" plus patches originally contributed by Yi.

History:

v8 -> v9:
- introduce specific irq framework
- single fault region
- iommu_unregister_device_fault_handler failure case not handled
  yet.

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (8):
  vfio: VFIO_IOMMU_SET_MSI_BINDING
  vfio/pci: Add VFIO_REGION_TYPE_NESTED region type
  vfio/pci: Register an iommu fault handler
  vfio/pci: Allow to mmap the fault queue
  vfio: Add new IRQ for DMA fault reporting
  vfio/pci: Add framework for custom interrupt indices
  vfio/pci: Register and allow DMA FAULT IRQ signaling
  vfio: Document nested stage control

Liu, Yi L (2):
  vfio: VFIO_IOMMU_SET_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

Tina Zhang (1):
  vfio: Use capability chains to handle device specific irq

 Documentation/vfio.txt              |  77 ++++++++
 drivers/vfio/pci/vfio_pci.c         | 283 ++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_intrs.c   |  62 ++++++
 drivers/vfio/pci/vfio_pci_private.h |  24 +++
 drivers/vfio/pci/vfio_pci_rdwr.c    |  45 +++++
 drivers/vfio/vfio_iommu_type1.c     | 166 ++++++++++++++++
 include/uapi/linux/vfio.h           | 109 ++++++++++-
 7 files changed, 747 insertions(+), 19 deletions(-)
```
#### [RFC v2 00/27] Kernel Address Space Isolation
##### From: Alexandre Chartre <alexandre.chartre@oracle.com>

```c

Hi,

This is version 2 of the "KVM Address Space Isolation" RFC. The code
has been completely changed compared to v1 and it now provides a generic
kernel framework which provides Address Space Isolation; and KVM is now
a simple consumer of that framework. That's why the RFC title has been
changed from "KVM Address Space Isolation" to "Kernel Address Space
Isolation".

Kernel Address Space Isolation aims to use address spaces to isolate some
parts of the kernel (for example KVM) to prevent leaking sensitive data
between hyper-threads under speculative execution attacks. You can refer
to the first version of this RFC for more context:

   https://lkml.org/lkml/2019/5/13/515

The new code is still a proof of concept. It is much more stable than v1:
I am able to run a VM with a full OS (and also a nested VM) with multiple
vcpus. But it looks like there are still some corner cases which cause the
system to crash/hang.

I am looking for feedback about this new approach where address space
isolation is provided by the kernel, and KVM is a just a consumer of this
new framework.


Changes
=======

- Address Space Isolation (ASI) is now provided as a kernel framework:
  interfaces for creating and managing an ASI are provided by the kernel,
  there are not implemented in KVM.

- An ASI is associated with a page-table, we don't use mm anymore. Entering
  isolation is done by just updating CR3 to use the ASI page-table. Exiting
  isolation restores CR3 with the CR3 value present before entering isolation.

- Isolation is exited at the beginning of any interrupt/exception handler,
  and on context switch.

- Isolation doesn't disable interrupt, but if an interrupt occurs the
  interrupt handler will exit isolation.

- The current stack is mapped when entering isolation and unmapped when
  exiting isolation.

- The current task is not mapped by default, but there's an option to map it.
  In such a case, the current task is mapped when entering isolation and
  unmap when exiting isolation.

- Kernel code mapped to the ASI page-table has been reduced to:
  . the entire kernel (I still need to test with only the kernel text)
  . the cpu entry area (because we need the GDT to be mapped)
  . the cpu ASI session (for managing ASI)
  . the current stack

- Optionally, an ASI can request the following kernel mapping to be added:
  . the stack canary
  . the cpu offsets (this_cpu_off)
  . the current task
  . RCU data (rcu_data)
  . CPU HW events (cpu_hw_events).

  All these optional mappings are used for KVM isolation.
  

Patches:
========

The proposed patches provides a framework for creating an Address Space
Isolation (ASI) (represented by a struct asi). The ASI has a page-table which
can be populated by copying mappings from the kernel page-table. The ASI can
then be entered/exited by switching between the kernel page-table and the
ASI page-table. In addition, any interrupt, exception or context switch
will automatically abort and exit the isolation. Finally patches use the
ASI framework to implement KVM isolation.

- 01-03: Core of the ASI framework: create/destroy ASI, enter/exit/abort
  isolation, ASI page-fault handler.

- 04-14: Functions to manage, populate and clear an ASI page-table.

- 15-20: ASI core mappings and optional mappings.

- 21: Make functions to read cr3/cr4 ASI aware

- 22-26: Use ASI in KVM to provide isolation for VMExit handlers.


API Overview:
=============
Here is a short description of the main ASI functions provided by the framwork.

struct asi *asi_create(int map_flags)

  Create an Address Space Isolation (ASI). map_flags can be used to specify
  optional kernel mapping to be added to the ASI page-table (for example,
  ASI_MAP_STACK_CANARY to map the stack canary).


void asi_destroy(struct asi *asi)

  Destroy an ASI.


int asi_enter(struct asi *asi)

  Enter isolation for the specified ASI. This switches from the kernel page-table
  to the page-table associated with the ASI.


void asi_exit(struct asi *asi)

  Exit isolation for the specified ASI. This switches back to the kernel
  page-table


int asi_map(struct asi *asi, void *ptr, unsigned long size);

  Copy kernel mapping to the specified ASI page-table.


void asi_unmap(struct asi *asi, void *ptr);

  Clear kernel mapping from the specified ASI page-table.


----
Alexandre Chartre (23):
  mm/x86: Introduce kernel address space isolation
  mm/asi: Abort isolation on interrupt, exception and context switch
  mm/asi: Handle page fault due to address space isolation
  mm/asi: Functions to track buffers allocated for an ASI page-table
  mm/asi: Add ASI page-table entry offset functions
  mm/asi: Add ASI page-table entry allocation functions
  mm/asi: Add ASI page-table entry set functions
  mm/asi: Functions to populate an ASI page-table from a VA range
  mm/asi: Helper functions to map module into ASI
  mm/asi: Keep track of VA ranges mapped in ASI page-table
  mm/asi: Functions to clear ASI page-table entries for a VA range
  mm/asi: Function to copy page-table entries for percpu buffer
  mm/asi: Add asi_remap() function
  mm/asi: Handle ASI mapped range leaks and overlaps
  mm/asi: Initialize the ASI page-table with core mappings
  mm/asi: Option to map current task into ASI
  rcu: Move tree.h static forward declarations to tree.c
  rcu: Make percpu rcu_data non-static
  mm/asi: Add option to map RCU data
  mm/asi: Add option to map cpu_hw_events
  mm/asi: Make functions to read cr3/cr4 ASI aware
  KVM: x86/asi: Populate the KVM ASI page-table
  KVM: x86/asi: Map KVM memslots and IO buses into KVM ASI

Liran Alon (3):
  KVM: x86/asi: Introduce address_space_isolation module parameter
  KVM: x86/asi: Introduce KVM address space isolation
  KVM: x86/asi: Switch to KVM address space on entry to guest

 arch/x86/entry/entry_64.S          |   42 ++-
 arch/x86/include/asm/asi.h         |  237 ++++++++
 arch/x86/include/asm/mmu_context.h |   20 +-
 arch/x86/include/asm/tlbflush.h    |   10 +
 arch/x86/kernel/asm-offsets.c      |    4 +
 arch/x86/kvm/Makefile              |    3 +-
 arch/x86/kvm/mmu.c                 |    2 +-
 arch/x86/kvm/vmx/isolation.c       |  231 ++++++++
 arch/x86/kvm/vmx/vmx.c             |   14 +-
 arch/x86/kvm/vmx/vmx.h             |   24 +
 arch/x86/kvm/x86.c                 |   68 +++-
 arch/x86/kvm/x86.h                 |    1 +
 arch/x86/mm/Makefile               |    2 +
 arch/x86/mm/asi.c                  |  459 +++++++++++++++
 arch/x86/mm/asi_pagetable.c        | 1077 ++++++++++++++++++++++++++++++++++++
 arch/x86/mm/fault.c                |    7 +
 include/linux/kvm_host.h           |    7 +
 kernel/rcu/tree.c                  |   56 ++-
 kernel/rcu/tree.h                  |   56 +--
 kernel/sched/core.c                |    4 +
 security/Kconfig                   |   10 +
 21 files changed, 2269 insertions(+), 65 deletions(-)
 create mode 100644 arch/x86/include/asm/asi.h
 create mode 100644 arch/x86/kvm/vmx/isolation.c
 create mode 100644 arch/x86/mm/asi.c
 create mode 100644 arch/x86/mm/asi_pagetable.c
```
#### [PATCH v3 0/5] Some vfio-ccw fixes
##### From: Farhan Ali <alifm@linux.ibm.com>

```c

Hi,

While trying to chase down the problem regarding the stacktraces,
I have also found some minor problems in the code.

Would appreciate any review or feedback regarding them.

Thanks
Farhan

ChangeLog
---------
v2 -> v3
   - Minor changes as suggested by Conny
   - Add Conny's reviewed-by tags
   - Add fixes tag for patch 4 and patch 5

v1 -> v2
   - Update docs for csch/hsch since we can support those
     instructions now (patch 5)
   - Fix the memory leak where we fail to free a ccwchain (patch 2)
   - Add fixes tag where appropriate.
   - Fix comment instead of the order when setting orb.cmd.c64 (patch 1)


Farhan Ali (5):
  vfio-ccw: Fix misleading comment when setting orb.cmd.c64
  vfio-ccw: Fix memory leak and don't call cp_free in cp_init
  vfio-ccw: Set pa_nr to 0 if memory allocation fails for pa_iova_pfn
  vfio-ccw: Don't call cp_free if we are processing a channel program
  vfio-ccw: Update documentation for csch/hsch

 Documentation/s390/vfio-ccw.rst | 31 ++++++++++++++++++++++++++++---
 drivers/s390/cio/vfio_ccw_cp.c  | 28 +++++++++++++++++-----------
 drivers/s390/cio/vfio_ccw_drv.c |  2 +-
 3 files changed, 46 insertions(+), 15 deletions(-)
```
#### [PATCH v3 0/2] KVM: nVMX: add tracepoints for nested VM-Enter
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Debugging VM-Enter failures has been the bane of my existence for years.
Seeing KVM's VMCS dump format pop up on a console triggers a Pavlovian
response of swear words and sighs.  As KVM's coverage of VM-Enter checks
improve, so too do the odds of being able to triage/debug a KVM (or any
other hypervisor) bug by running the bad KVM build as an L1 guest.

Improve support for using KVM to debug a buggy VMM by adding tracepoints
to capture the basic gist of a VM-Enter failure so that extracting said
information from KVM doesn't require attaching a debugger or modifying
L0 KVM to manually log failures.

The captured information is by no means complete or perfect, e.g. I'd
love to capture *exactly* why a consistency check failed, but logging
that level of detail would require invasive code changes and might even
act as a deterrent to adding more checks in KVM.

v3: Fix a minor snafu in the v2 rebase, and re-rebase to kvm/next
    (a45ff5994c9c, "Merge tag 'kvm-arm-for-5.3'...")

v2: Rebase to kvm/queue.

Sean Christopherson (2):
  KVM: nVMX: add tracepoint for failed nested VM-Enter
  KVM: nVMX: trace nested VM-Enter failures detected by H/W

 arch/x86/include/asm/vmx.h |  14 ++
 arch/x86/kvm/trace.h       |  22 +++
 arch/x86/kvm/vmx/nested.c  | 269 ++++++++++++++++++++-----------------
 arch/x86/kvm/x86.c         |   1 +
 4 files changed, 179 insertions(+), 127 deletions(-)
```
