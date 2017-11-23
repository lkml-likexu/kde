

#### [PATCH kernel v7 00/20] powerpc/powernv/npu,
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c

My bad, I was not cc-ing everyone but now with v7 I am, sorry about that.


This is for passing through NVIDIA V100 GPUs on POWER9 systems.
20/20 has the details of hardware setup.

This implements support for NVIDIA V100 GPU with coherent memory and
NPU/ATS support available in the POWER9 CPU. The aim is to support
unmodified vendor driver in the guest.

This is pushed to (both guest and host kernels):
https://github.com/aik/linux/tree/nv2

Matching qemu is pushed to github:
https://github.com/aik/qemu/tree/nv2

Skiboot bits are here:
https://github.com/aik/skiboot/tree/nv2

The individual patches have changelogs. v7 fixes compile warning
and updates a VFIO capability comment in 20/20.

Please comment. Thanks.



Alexey Kardashevskiy (20):
  powerpc/ioda/npu: Call skiboot's hot reset hook when disabling NPU2
  powerpc/mm/iommu/vfio_spapr_tce: Change mm_iommu_get to reference a
    region
  powerpc/vfio/iommu/kvm: Do not pin device memory
  powerpc/powernv: Move npu struct from pnv_phb to pci_controller
  powerpc/powernv/npu: Move OPAL calls away from context manipulation
  powerpc/pseries/iommu: Use memory@ nodes in max RAM address
    calculation
  powerpc/pseries/npu: Enable platform support
  powerpc/pseries: Remove IOMMU API support for non-LPAR systems
  powerpc/powernv/pseries: Rework device adding to IOMMU groups
  powerpc/iommu_api: Move IOMMU groups setup to a single place
  powerpc/powernv: Reference iommu_table while it is linked to a group
  powerpc/powernv/npu: Move single TVE handling to NPU PE
  powerpc/powernv/npu: Convert NPU IOMMU helpers to
    iommu_table_group_ops
  powerpc/powernv/npu: Add compound IOMMU groups
  powerpc/powernv/npu: Add release_ownership hook
  powerpc/powernv/npu: Check mmio_atsd array bounds when populating
  powerpc/powernv/npu: Fault user page into the hypervisor's pagetable
  vfio_pci: Allow mapping extra regions
  vfio_pci: Allow regions to add own capabilities
  vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver

 drivers/vfio/pci/Makefile                     |   1 +
 arch/powerpc/include/asm/iommu.h              |  17 +-
 arch/powerpc/include/asm/mmu_context.h        |  15 +-
 arch/powerpc/include/asm/pci-bridge.h         |   1 +
 arch/powerpc/include/asm/pci.h                |   4 +
 arch/powerpc/platforms/powernv/pci.h          |  30 +-
 drivers/vfio/pci/trace.h                      | 102 ++++
 drivers/vfio/pci/vfio_pci_private.h           |  20 +
 include/uapi/linux/vfio.h                     |  37 ++
 arch/powerpc/kernel/iommu.c                   |  69 +--
 arch/powerpc/kvm/book3s_64_vio.c              |  18 +-
 arch/powerpc/mm/mmu_context_iommu.c           | 110 +++-
 arch/powerpc/platforms/powernv/npu-dma.c      | 549 +++++++++++++++---
 arch/powerpc/platforms/powernv/pci-ioda-tce.c |   3 +-
 arch/powerpc/platforms/powernv/pci-ioda.c     | 237 ++++----
 arch/powerpc/platforms/powernv/pci.c          |  43 +-
 arch/powerpc/platforms/pseries/iommu.c        |  88 ++-
 arch/powerpc/platforms/pseries/pci.c          |  22 +
 drivers/vfio/pci/vfio_pci.c                   |  42 +-
 drivers/vfio/pci/vfio_pci_nvlink2.c           | 482 +++++++++++++++
 drivers/vfio/vfio_iommu_spapr_tce.c           |  64 +-
 drivers/vfio/pci/Kconfig                      |   6 +
 22 files changed, 1569 insertions(+), 391 deletions(-)
 create mode 100644 drivers/vfio/pci/trace.h
 create mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c
```
#### [PATCH kvmtool v3 0/9] arm: Allow the user to specify where the RAM
##### From: Julien Grall <julien.grall@arm.com>

```c

Hi all,

At the moment, a user is only able to specify the amount of RAM used by the
guest. Where the RAM will live is left to the software and hardcoded.

It could be useful for testing purpose to move the RAM in different place.
This series adds the possibility for the user to specify multiple RAM region.

The option -m/--mem is extended to specify the address using the following
format: <size>@<addr>. The option needs to be repeated as many times as the
number of RAM region in the guest layout.

For instance, if you want 512MB at 3GB and 512MB 4GB it would look like:
    -m 512@0xc0000000 -m 512@0x100000000

Note that the memory layout is not yet fully configurable by the user, so the
MMIO region is still living below 2GB. This means RAM cannot live in the
region 0-2GB. This could be changed in the future.

Cheers,

Julien Grall (7):
  kvm__arch_init: Don't pass hugetlbfs_path and ram_size in parameter
  virtio/scsi: Allow to use multiple banks
  Fold kvm__init_ram call in kvm__arch_init
  arm: Add an helper to sanitize KVM configuration
  arm: Move anything related to RAM initialization in kvm__init_ram
  Allow the user to specify where the RAM is placed in the memory
  arm: Add support for multi memory regions

Suzuki K Poulose (2):
  arm: Allow use of hugepage with 16K pagesize host
  kvmtool: Allow standard size specifiers for memory bank

 arm/aarch32/include/kvm/kvm-arch.h |   2 +-
 arm/aarch64/include/kvm/kvm-arch.h |   4 +-
 arm/fdt.c                          |  19 +++--
 arm/include/arm-common/kvm-arch.h  |  24 ++++--
 arm/kvm.c                          | 160 ++++++++++++++++++++++++++++++-------
 builtin-run.c                      | 129 +++++++++++++++++++++++++++---
 include/kvm/kvm-config.h           |  16 +++-
 include/kvm/kvm.h                  |  24 ++++--
 kvm.c                              |   8 +-
 mips/kvm.c                         |  47 ++++++-----
 powerpc/kvm.c                      |  33 +++++---
 virtio/scsi.c                      |  21 +++--
 x86/bios.c                         |   8 +-
 x86/kvm.c                          |  54 ++++++++-----
 14 files changed, 417 insertions(+), 132 deletions(-)
```
#### [RFC PATCH v5 00/20] VM introspection
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c

This patch series proposes a VM introspection subsystem for KVM (KVMi).

The previous RFC can be read here: https://marc.info/?l=kvm&m=151362403331566

This iteration brings, mostly:
  - an improved remote mapping (moved to the mm/ tree)
  - single-step support for #PF events and as an workaround to unimplemented
    instructions from the x86 emulator that may need to be handled on EPT
    violations VMEXITS
  - a new ioctl to allow the introspection tool to remove its hooks from
    guest before it is suspended or live migrated
  - more bugfixes and a lot of stability

Still not implemented yet (even if some are documented) are virtualized
exceptions, EPT views and SPP (Sub Page Protection).

We're still looking forward to add kvm unit tests for this VM
introspection system now that we've integrated it in our products and
in our internal tests framework.

Changes since v4:
  - move the new and improved remote mapping code to the mm/ tree
  - add two VM events (in addition to vCPU events) - KVMI_EVENT_CREATE_VCPU
        and KVMI_EVENT_UNHOOK - controlled by KVMI_CONTROL_VM_EVENTS
  - add KVM_INTROSPECTION_UNHOOK ioctl to support suspend, snapshot
        and live migration
  - use KVMI_PAUSE_ALL_VCPUS instead of KVMI_PAUSE_VCPU (temporarily)
  - fix the reinjection of guest breakpoints
  - add single-stepping
  - extend KVMI_EVENT_PF to support single-stepping and to reduce
        the number of events on REP prefixed instructions
  - allow the guest to update A/D bits when the page tables are tracked
        (write protected)
  - extend page tracking to pass the gva in addition to gpa
  - make small changes to the wire protocol (error codes, padding, names)
  - extend struct kvm_introspection (ioctl KVM_INTROSPECTION) with the guest's uuid
  - change the maximum message size to 4K (from 64K)
  - fix more bugs

Changes since v3:
  - move the accept/handshake worker to QEMU
  - extend and use the 'page_track' infrastructure to intercept page
    accesses during emulation
  - remove the 0x40000000-0x40001fff range from monitored MSR-s
  - make small changes to the wire protocol (error codes, padding, names)
  - simplify KVMI_PAUSE_VCPU
  - add new commands: KVMI_GET_MAP_TOKEN, KVMI_GET_XSAVE
  - add pat to KVMI_EVENT
  - document KVM_HC_MEM_MAP and KVM_HC_MEM_UNMAP hypercalls

Changes since v2:
  - make small changes to the wire protocol (eg. use kvmi_error_code
    with every command reply, a few renames, etc.)
  - removed '_x86' from x86 specific structure names. Architecture
    specific structures will have the same name.
  - drop KVMI_GET_MTRR_TYPE and KVMI_GET_MTRRS (use KVMI_SET_REGISTERS)
  - drop KVMI_EVENT_ACTION_SET_REGS (use KVMI_SET_REGISTERS)
  - remove KVMI_MAP_PHYSICAL_PAGE_TO_GUEST and KVMI_UNMAP_PHYSICAL_PAGE_FROM_GUEST
    (to be replaced by a token+hypercall pair)
  - extend KVMI_GET_VERSION with allowed commnd/event masks
  - replace KVMI_PAUSE_GUEST/KVMI_UNPAUSE_GUEST with KVMI_PAUSE_VCPU
  - replace KVMI_SHUTDOWN_GUEST with KVMI_EVENT_ACTION_CRASH
  - replace KVMI_GET_XSAVE_INFO with KVMI_GET_CPUID
  - merge KVMI_INJECT_PAGE_FAULT and KVMI_INJECT_BREAKPOINT
    in KVMI_INJECT_EXCEPTION
  - replace event reply flags with ALLOW/SKIP/RETRY/CRASH actions
  - make KVMI_SET_REGISTERS work with vCPU events only
  - add EPT view support in KVMI_GET_PAGE_ACCESS/KVMI_SET_PAGE_ACCESS
  - add support for multiple pages in KVMI_GET_PAGE_ACCESS/KVMI_SET_PAGE_ACCESS
  - add (back) KVMI_READ_PHYSICAL/KVMI_WRITE_PHYSICAL
  - add KVMI_CONTROL_VE
  - add cstar to KVMI_EVENT
  - add new events: KVMI_EVENT_VCPU_PAUSED, KVMI_EVENT_CREATE_VCPU, 
    KVMI_EVENT_DESCRIPTOR_ACCESS, KVMI_EVENT_SINGLESTEP
  - add new sections: "Introspection capabilities", "Live migrations",
    "Guest snapshots with memory", "Memory access safety"
  - document the hypercall used by the KVMI_EVENT_HYPERCALL command
    (was KVMI_EVENT_USER_CALL)

Changes since v1:
  - add documentation and ABI [Paolo, Jan]
  - drop all the other patches for now [Paolo]
  - remove KVMI_GET_GUESTS, KVMI_EVENT_GUEST_ON, KVMI_EVENT_GUEST_OFF,
    and let libvirt/qemu handle this [Stefan, Paolo]
  - change the license from LGPL to GPL [Jan]
  - remove KVMI_READ_PHYSICAL and KVMI_WRITE_PHYSICAL (not used anymore)
  - make the interface a little more consistent


Adalbert Lazăr (8):
  kvm: document the VM introspection ioctl-s and capability
  kvm: extend to accomodate the VM introspection subsystem
  kvm: add the VM introspection subsystem
  kvm: x86: hook in kvmi_msr_event()
  kvm: x86: hook in kvmi_breakpoint_event()
  kvm: x86: hook in kvmi_cr_event()
  kvm: x86: hook in kvmi_xsetbv_event()
  kvm: x86: handle the introspection hypercalls

Mihai DONTU (8):
  kvm: document the VM introspection API
  kvm: document the VM introspection hypercalls
  kvm: add the VM introspection API/ABI headers
  kvm: x86: do not unconditionally patch the hypercall instruction
    during emulation
  kvm: page track: add support for preread, prewrite and preexec
  kvm: x86: hook in the VM introspection subsystem
  kvm: x86: hook the single-step events
  kvm: x86: hook in kvmi_trap_event()

Mircea Cîrjaliu (2):
  mm: add support for remote mapping
  add memory map/unmap support for VM introspection on the guest side

Nicușor Cîțu (2):
  kvm: x86: add tracepoints for interrupt and exception injections
  kvm: x86: intercept accesses to IDTR, GDTR, LDTR and TR

 Documentation/virtual/kvm/api.txt        |   59 +
 Documentation/virtual/kvm/hypercalls.txt |   68 +-
 Documentation/virtual/kvm/kvmi.rst       | 1351 +++++++++++++
 arch/x86/Kconfig                         |    9 +
 arch/x86/include/asm/kvm_emulate.h       |    1 +
 arch/x86/include/asm/kvm_host.h          |   21 +-
 arch/x86/include/asm/kvm_page_track.h    |   33 +-
 arch/x86/include/asm/kvmi_guest.h        |   10 +
 arch/x86/include/asm/vmx.h               |    2 +
 arch/x86/include/uapi/asm/kvmi.h         |  234 +++
 arch/x86/kernel/Makefile                 |    1 +
 arch/x86/kernel/kvmi_mem_guest.c         |   26 +
 arch/x86/kvm/Kconfig                     |    6 +
 arch/x86/kvm/Makefile                    |    1 +
 arch/x86/kvm/emulate.c                   |    9 +-
 arch/x86/kvm/mmu.c                       |  168 +-
 arch/x86/kvm/mmu.h                       |    4 +
 arch/x86/kvm/page_track.c                |  147 +-
 arch/x86/kvm/svm.c                       |  133 +-
 arch/x86/kvm/trace.h                     |  118 +-
 arch/x86/kvm/vmx.c                       |  158 +-
 arch/x86/kvm/x86.c                       |  290 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c         |    2 +-
 include/linux/kvm_host.h                 |   15 +
 include/linux/kvmi.h                     |   86 +
 include/linux/mm.h                       |   13 +
 include/linux/rmap.h                     |    1 +
 include/linux/swait.h                    |   11 +
 include/trace/events/kvmi.h              |  665 +++++++
 include/uapi/linux/kvm.h                 |   12 +
 include/uapi/linux/kvm_para.h            |   11 +-
 include/uapi/linux/kvmi.h                |  192 ++
 kernel/signal.c                          |    1 +
 mm/Kconfig                               |    9 +
 mm/Makefile                              |    1 +
 mm/gup.c                                 |    1 +
 mm/huge_memory.c                         |    1 +
 mm/internal.h                            |    5 -
 mm/mempolicy.c                           |    1 +
 mm/mmap.c                                |    1 +
 mm/mmu_notifier.c                        |    1 +
 mm/pgtable-generic.c                     |    1 +
 mm/remote_mapping.c                      | 1438 ++++++++++++++
 mm/rmap.c                                |   39 +-
 mm/swapfile.c                            |    1 +
 virt/kvm/kvm_main.c                      |   34 +-
 virt/kvm/kvmi.c                          | 2246 ++++++++++++++++++++++
 virt/kvm/kvmi_int.h                      |  202 ++
 virt/kvm/kvmi_mem.c                      |  330 ++++
 virt/kvm/kvmi_mem_guest.c                |  364 ++++
 virt/kvm/kvmi_msg.c                      | 1278 ++++++++++++
 51 files changed, 9651 insertions(+), 160 deletions(-)
 create mode 100644 Documentation/virtual/kvm/kvmi.rst
 create mode 100644 arch/x86/include/asm/kvmi_guest.h
 create mode 100644 arch/x86/include/uapi/asm/kvmi.h
 create mode 100644 arch/x86/kernel/kvmi_mem_guest.c
 create mode 100644 include/linux/kvmi.h
 create mode 100644 include/trace/events/kvmi.h
 create mode 100644 include/uapi/linux/kvmi.h
 create mode 100644 mm/remote_mapping.c
 create mode 100644 virt/kvm/kvmi.c
 create mode 100644 virt/kvm/kvmi_int.h
 create mode 100644 virt/kvm/kvmi_mem.c
 create mode 100644 virt/kvm/kvmi_mem_guest.c
 create mode 100644 virt/kvm/kvmi_msg.c
```
#### [PATCH 00/11] KVM: VMX: Clean up VM-Enter/VM-Exit asm code
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Despite all but one patch being KVM cleanup, that one outlier is the
true catalyst for this series.  The outlier, patch 3/11, removes an
optimization tweak from the __noclone macro that was added by commit
95272c29378e ("compiler-gcc: disable -ftracer for __noclone functions")
to workaround a compiler error in KVM's esoteric VMX assembly code.

Unbeknownst at the time, using the __optimize__ attribute causes GCC
to reset to -O2 optimization defaults, which has several unintended
side effects including dropping -fno-omit-frame-pointer and preventing
GCC from properly inlining function calls due to the functions having
incompatible optimization attributes.

Patches 1/11 and 2/11 fix the offending KVM code and eliminate its
usage of __noclone, allowing patch 3/11 to remove "no-tracer" from the
__noclone macro.

Patches 4/11 and beyond are a mix of cleanup, fixes and optimizations
for a variety of low hanging fruit that were (unsurprisingly) revealed
when revisiting KVM's inline assembly blob.

FYI, I cc'd everyone involved for all patches up until the -ftracer
revert, after that I limited the cc/to list to KVM folks.

Sean Christopherson (11):
  KVM: VMX: Explicitly reference RCX as the vmx_vcpu pointer in asm
    blobs
  KVM: VMX: Move VM-Enter + VM-Exit handling to non-inline sub-routines
  Revert "compiler-gcc: disable -ftracer for __noclone functions"
  KVM: VMX: Modify only RSP when creating a placeholder for guest's RCX
  KVM: VMX: Save RSI to an unused output in vmx_vcpu_run() asm blob
  KVM: VMX: Manually load RDX in vmx_vcpu_run() asm blob
  KVM: VMX: Let the compiler save/load RDX around VM-Enter
  KVM: nVMX: Cache host_rsp on a per-VMCS basis
  KVM: nVMX: Add eVMCS support to nested_vmx_check_vmentry_hw()
  KVM: VMX: Add macros to handle HOST_RSP updates at VM-Enter
  KVM: nVMX: Remove a rogue "rax" clobber from
    nested_vmx_check_vmentry_hw()

 arch/x86/kvm/Makefile               |   2 +-
 arch/x86/kvm/vmx/nested.c           |  57 ++++---------
 arch/x86/kvm/vmx/vmcs.h             |   1 +
 arch/x86/kvm/vmx/vmenter.S          |  57 +++++++++++++
 arch/x86/kvm/vmx/vmx.c              | 127 +++++++++++++---------------
 arch/x86/kvm/vmx/vmx.h              |  30 ++++++-
 include/linux/compiler_attributes.h |   8 +-
 7 files changed, 164 insertions(+), 118 deletions(-)
 create mode 100644 arch/x86/kvm/vmx/vmenter.S
Reviewed-by: Andi Kleen <ak@linux.intel.com>
```
