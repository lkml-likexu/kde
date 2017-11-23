

#### [PATCH 0/3] vhost/scsi: Respond to control queue operations
##### From: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>

```c

This patch series causes vhost-scsi control queue TMF requests to be
explicitly rejected rather than implicitly ignored in order to prevent
a guest virito-scsi driver to wait indefinitely for a response to a SCSI
TMF request.

In addition, control queue address notification operations
(VIRTIO_SCSI_T_AN_*) get an effective no-op response.

Patch 1/3 implements a control queue handler modeled after the existing
request queue handler.  There is no commonality between the two handlers.

Patch 2/3 factors out the common processing code from the control queue
handler into separate routines.

Patch 3/3 modifies the request handler to use the common processing routines.  

Bijan Mottahedeh (3):
  vhost/scsi: Respond to control queue operations
  vhost/scsi: Extract common handling code from control queue handler
  vhost/scsi: Use common handling code in request queue handler

 drivers/vhost/scsi.c | 422 +++++++++++++++++++++++++++++++++++++++------------
 1 file changed, 326 insertions(+), 96 deletions(-)
```
#### [PATCH V2 00/13] x86/KVM/Hyper-v: Add HV ept tlb range flush
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c

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

Change since v1:
       1) Convert "end_gfn" of struct kvm_tlb_range to "pages" in order
          to avoid confusion as to whether "end_gfn" is inclusive or exlusive.
       2) Add hyperv tlb range struct and replace kvm tlb range struct
          with new struct in order to avoid using kvm struct in the hyperv
	  code directly.

Lan Tianyu (13):
  KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
  KVM/MMU: Add tlb flush with range helper function
  KVM: Replace old tlb flush function with new one to flush a specified
    range.
  KVM/MMU: Flush tlb directly in the kvm_handle_hva_range()
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

 arch/x86/hyperv/nested.c            | 104 ++++++++++++++++++++++++++
 arch/x86/include/asm/hyperv-tlfs.h  |  17 +++++
 arch/x86/include/asm/kvm_host.h     |  10 +++
 arch/x86/include/asm/mshyperv.h     |  16 ++++
 arch/x86/include/asm/trace/hyperv.h |  14 ++++
 arch/x86/kvm/mmu.c                  | 143 +++++++++++++++++++++++++++++++-----
 arch/x86/kvm/paging_tmpl.h          |  16 +++-
 arch/x86/kvm/vmx.c                  |  65 +++++++++++++---
 8 files changed, 354 insertions(+), 31 deletions(-)
```
#### [PATCH v2 0/2] vfio: add vgpu edid support
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c

Update vfio api, adapt mbochs sample driver.

v2: try region approach.

Gerd Hoffmann (2):
  vfio: add edid api for display (vgpu) devices.
  vfio: add edid support to mbochs sample driver

 include/uapi/linux/vfio.h  |  39 +++++++++++++++
 samples/vfio-mdev/mbochs.c | 115 +++++++++++++++++++++++++++++++++++++--------
 2 files changed, 135 insertions(+), 19 deletions(-)
```
#### [RFC v2 00/20] SMMUv3 Nested Stage Setup
##### From: Eric Auger <eric.auger@redhat.com>

```c

This series allows a virtualizer to program the nested stage mode.
This is useful when both the host and the guest are exposed with
an SMMUv3 and a PCI device is assigned to the guest using VFIO.

In this mode, the physical IOMMU must be programmed to translate
the two stages: the one set up by the guest (IOVA -> GPA) and the
one set up by the host VFIO driver as part of the assignment process
(GPA -> HPA).

On Intel, this is traditionnaly achieved by combining the 2 stages
into a single physical stage. However this relies on the capability
to trap on each guest translation structure update. This is possible
by using the VTD Caching Mode. Unfortunately the ARM SMMUv3 does
not offer a similar mechanism.

However, the ARM SMMUv3 architecture supports 2 physical stages! Those
were devised exactly with that use case in mind. Assuming the HW
implements both stages (optional), the guest now can use stage 1
while the host uses stage 2.

This assumes the virtualizer has means to propagate guest settings
to the host SMMUv3 driver. This series brings this VFIO/IOMMU
infrastructure.  Those services are:
- bind the guest stage 1 configuration to the stream table entry
- propagate guest TLB invalidations
- bind MSI IOVAs
- propagate faults collected at physical level up to the virtualizer

This series largely reuses the user API and infrastructure originally
devised for SVA/SVM and patches submitted by Jacob, Yi Liu, Tianyu in
[1-3] and Jean-Philippe [4].

This proof of concept also aims at illustrating how this API/infrastructure
would need to evolve to support this nested stage SMMUv3 use case.

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/v4.19-rc4-2stage-rfc-v2

This was tested on Qualcomm HW featuring SMMUv3 and with adapted QEMU
vSMMUv3.

References:
[1] [PATCH v5 00/23] IOMMU and VT-d driver support for Shared Virtual
    Address (SVA)
    https://lwn.net/Articles/754331/
[2] [RFC PATCH 0/8] Shared Virtual Memory virtualization for VT-d
    (VFIO part)
    https://lists.linuxfoundation.org/pipermail/iommu/2017-April/021475.html
[3] [RFC PATCH 0/3] VFIO: Report IOMMU fault event to userspace
    https://www.spinics.net/lists/kvm/msg145280.html
[4] [v2,00/40] Shared Virtual Addressing for the IOMMU
    https://patchwork.ozlabs.org/cover/912129/

History:

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (11):
  iommu: Introduce bind_guest_msi
  vfio: VFIO_IOMMU_BIND_MSI
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement bind_pasid_table
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Implement bind_guest_msi
  vfio: VFIO_IOMMU_SET_FAULT_EVENTFD
  vfio: VFIO_IOMMU_GET_FAULT_EVENTS
  vfio: Document nested stage control
  iommu/smmuv3: Report non recoverable faults

Jacob Pan (4):
  iommu: Introduce bind_pasid_table API
  iommu: introduce device fault data
  driver core: add per device iommu param
  iommu: introduce device fault report API

Jean-Philippe Brucker (2):
  iommu/arm-smmu-v3: Link domains and devices
  iommu/arm-smmu-v3: Maintain a SID->device structure

Liu, Yi L (3):
  iommu: Introduce cache_invalidate API
  vfio: VFIO_IOMMU_BIND_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

 Documentation/vfio.txt          |  60 ++++
 drivers/iommu/arm-smmu-v3.c     | 476 ++++++++++++++++++++++++++++++--
 drivers/iommu/dma-iommu.c       |  97 ++++++-
 drivers/iommu/iommu.c           | 196 ++++++++++++-
 drivers/vfio/vfio_iommu_type1.c | 269 ++++++++++++++++++
 include/linux/device.h          |   3 +
 include/linux/dma-iommu.h       |  11 +
 include/linux/iommu.h           | 134 ++++++++-
 include/uapi/linux/iommu.h      | 237 ++++++++++++++++
 include/uapi/linux/vfio.h       |  48 ++++
 10 files changed, 1501 insertions(+), 30 deletions(-)
 create mode 100644 include/uapi/linux/iommu.h
```
#### [PATCH v1 RESEND 0/9] x86/kvm/nVMX: optimize MMU switch between L1
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v1:
- Rebase to 4.19-rc5, no changes.

Original description:

Currently, when we switch from L1 to L2 (VMX) we do the following:
- Re-initialize L1 MMU as shadow EPT MMU (nested_ept_init_mmu_context())
- Re-initialize 'nested' MMU (nested_vmx_load_cr3() -> init_kvm_nested_mmu())

When we switch back we do:
- Re-initialize L1 MMU (nested_vmx_load_cr3() -> init_kvm_tdp_mmu())

This seems to be sub-optimal. Initializing MMU is expensive (thanks to
update_permission_bitmask(), update_pkru_bitmask(),..) Try solving the
issue by splitting L1-normal and L1-nested MMUs and checking if MMU reset
is really needed. This spares us about 1000 cpu cycles on nested vmexit.

Brief look at SVM makes me think it can be optimized the exact same way.
I'll do this in a separate series if nobody objects.

Paolo Bonzini (1):
  x86/kvm/mmu: get rid of redundant kvm_mmu_setup()

Vitaly Kuznetsov (8):
  x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
  x86/kvm/mmu.c: set get_pdptr hook in kvm_init_shadow_ept_mmu()
  x86/kvm/mmu.c: add kvm_mmu parameter to kvm_mmu_free_roots()
  x86/kvm/mmu: introduce guest_mmu
  x86/kvm/mmu: make space for source data caching in struct kvm_mmu
  x86/kvm/nVMX: introduce scache for kvm_init_shadow_ept_mmu
  x86/kvm/mmu: check if tdp/shadow MMU reconfiguration is needed
  x86/kvm/mmu: check if MMU reconfiguration is needed in
    init_kvm_nested_mmu()

 arch/x86/include/asm/kvm_host.h |  42 ++++-
 arch/x86/kvm/mmu.c              | 330 +++++++++++++++++++++++-----------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +-
 arch/x86/kvm/paging_tmpl.h      |  15 +-
 arch/x86/kvm/svm.c              |  14 +-
 arch/x86/kvm/vmx.c              |  46 +++---
 arch/x86/kvm/x86.c              |  22 +--
 8 files changed, 295 insertions(+), 194 deletions(-)
```
#### [PATCH 00/13] kvm: selftests: add aarch64 framework and dirty
##### From: Andrew Jones <drjones@redhat.com>

```c

This series provides KVM selftests that test dirty log tracking on
AArch64 for both 4K and 64K guest page sizes. Additionally the
framework provides an easy way to test dirty log tracking with the
recently posted dynamic IPA and 52bit IPA series[1].

The series breaks down into parts as follows:

 01-02: generalize guest code to host userspace exit support by
        introducing "ucalls" - hypercalls to userspace
 03-05: prepare common code for a new architecture
 06-07: add virtual memory setup support for AArch64
    08: add vcpu setup support for AArch64
    09: port the dirty log test to AArch64
 10-11: add 64K guest page size support for the dirty log test
 12-13: prepare the dirty log test to also test > 40-bit guest
        physical address setups by allowing the test memory
        region to be placed at the top of physical memory

[1] https://www.spinics.net/lists/arm-kernel/msg676819.html

Thanks,
drew


Andrew Jones (13):
  kvm: selftests: vcpu_setup: set cr4.osfxsr
  kvm: selftests: introduce ucall
  kvm: selftests: move arch-specific files to arch-specific locations
  kvm: selftests: add cscope make target
  kvm: selftests: tidy up kvm_util
  kvm: selftests: add vm_phy_pages_alloc
  kvm: selftests: add virt mem support for aarch64
  kvm: selftests: add vcpu support for aarch64
  kvm: selftests: port dirty_log_test to aarch64
  kvm: selftests: introduce new VM mode for 64K pages
  kvm: selftests: dirty_log_test: also test 64K pages on aarch64
  kvm: selftests: stop lying to aarch64 tests about PA-bits
  kvm: selftests: support high GPAs in dirty_log_test

 tools/testing/selftests/kvm/.gitignore        |  11 +-
 tools/testing/selftests/kvm/Makefile          |  36 +-
 tools/testing/selftests/kvm/dirty_log_test.c  | 374 +++++++++----
 .../selftests/kvm/include/aarch64/processor.h |  55 ++
 .../testing/selftests/kvm/include/kvm_util.h  | 166 +++---
 .../testing/selftests/kvm/include/sparsebit.h |   6 +-
 .../testing/selftests/kvm/include/test_util.h |   6 +-
 .../kvm/include/{x86.h => x86_64/processor.h} |  24 +-
 .../selftests/kvm/include/{ => x86_64}/vmx.h  |   6 +-
 .../selftests/kvm/lib/aarch64/processor.c     | 311 +++++++++++
 tools/testing/selftests/kvm/lib/assert.c      |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    | 499 +++++++-----------
 .../selftests/kvm/lib/kvm_util_internal.h     |  33 +-
 tools/testing/selftests/kvm/lib/ucall.c       | 144 +++++
 .../kvm/lib/{x86.c => x86_64/processor.c}     | 197 ++++++-
 .../selftests/kvm/lib/{ => x86_64}/vmx.c      |   4 +-
 .../kvm/{ => x86_64}/cr4_cpuid_sync_test.c    |  14 +-
 .../kvm/{ => x86_64}/set_sregs_test.c         |   2 +-
 .../selftests/kvm/{ => x86_64}/state_test.c   |  25 +-
 .../kvm/{ => x86_64}/sync_regs_test.c         |   2 +-
 .../kvm/{ => x86_64}/vmx_tsc_adjust_test.c    |  23 +-
 21 files changed, 1329 insertions(+), 611 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/aarch64/processor.h
 rename tools/testing/selftests/kvm/include/{x86.h => x86_64/processor.h} (98%)
 rename tools/testing/selftests/kvm/include/{ => x86_64}/vmx.h (99%)
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/processor.c
 create mode 100644 tools/testing/selftests/kvm/lib/ucall.c
 rename tools/testing/selftests/kvm/lib/{x86.c => x86_64/processor.c} (85%)
 rename tools/testing/selftests/kvm/lib/{ => x86_64}/vmx.c (99%)
 rename tools/testing/selftests/kvm/{ => x86_64}/cr4_cpuid_sync_test.c (91%)
 rename tools/testing/selftests/kvm/{ => x86_64}/set_sregs_test.c (98%)
 rename tools/testing/selftests/kvm/{ => x86_64}/state_test.c (90%)
 rename tools/testing/selftests/kvm/{ => x86_64}/sync_regs_test.c (99%)
 rename tools/testing/selftests/kvm/{ => x86_64}/vmx_tsc_adjust_test.c (91%)
Signed-off-by: Andrew Jones <drjones@redhat.com>
```
