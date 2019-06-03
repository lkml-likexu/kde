

#### [RFC PATCH v2 0/3] Deliver vGPU page flip events to userspace
##### From: Tina Zhang <tina.zhang@intel.com>

```c

This series tries to send the vGPU page flip events to userspace, which
can be used by QEMU UI for rendering and display with the latest guest
framebuffers.

v2: Use VFIO irq chain to get eventfds from userspace instead of adding
a new ABI. (Alex)

v1: https://patchwork.kernel.org/cover/10962341/


Tina Zhang (3):
  vfio: Use capability chains to handle device specific irq
  drm/i915/gvt: Leverage irq capability chain to get eventfd
  drm/i915/gvt: Send plane flip events to user space

 drivers/gpu/drm/i915/gvt/display.c   |  10 +-
 drivers/gpu/drm/i915/gvt/gvt.h       |   4 +
 drivers/gpu/drm/i915/gvt/handlers.c  |  20 ++-
 drivers/gpu/drm/i915/gvt/hypercall.h |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c     | 208 +++++++++++++++++++++++++--
 drivers/gpu/drm/i915/gvt/mpt.h       |  16 +++
 include/uapi/linux/vfio.h            |  23 ++-
 7 files changed, 268 insertions(+), 14 deletions(-)
```
#### [PATCH v3 0/4] KVM: Unify mmu_memory_cache functionality across
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c

We currently have duplicated functionality for the mmu_memory_cache used
to pre-allocate memory for the page table manipulation code which cannot
allocate memory while holding spinlocks.  This functionality is
duplicated across x86, arm/arm64, and mips.

There were recently a debate of modifying the arm code to be more in
line with the x86 code and some discussions around changing the page
flags used for allocation.  This series should make it easier to take a
uniform approach across architectures.

While there's not a huge amount of code sharing, we come out with a net
gain.

Only tested on arm/arm64, and only compile-tested on x86 and mips.

Changes since v2:
 - Simplified kalloc flag definitions as per Paolo's review comment.

Changes since v1:
 - Split out rename from initial x86 patch to have separate patches to
   move the logic to common code and to rename.
 - Introduce KVM_ARCH_WANT_MMU_MEMCACHE to avoid compile breakage on
   architectures that don't use this functionality.
 - Rename KVM_NR_MEM_OBJS to KVM_MMU_NR_MEMCACHE_OBJS

Christoffer Dall (4):
  KVM: x86: Move mmu_memory_cache functions to common code
  KVM: x86: Rename mmu_memory_cache to kvm_mmu_memcache
  KVM: arm/arm64: Move to common kvm_mmu_memcache infrastructure
  KVM: mips: Move to common kvm_mmu_memcache infrastructure

 arch/arm/include/asm/kvm_host.h      | 13 +---
 arch/arm/include/asm/kvm_mmu.h       |  2 +-
 arch/arm/include/asm/kvm_types.h     | 11 ++++
 arch/arm64/include/asm/kvm_host.h    | 13 +---
 arch/arm64/include/asm/kvm_mmu.h     |  2 +-
 arch/arm64/include/asm/kvm_types.h   | 12 ++++
 arch/mips/include/asm/kvm_host.h     | 15 +----
 arch/mips/include/asm/kvm_types.h    | 11 ++++
 arch/mips/kvm/mips.c                 |  2 +-
 arch/mips/kvm/mmu.c                  | 54 +++-------------
 arch/powerpc/include/asm/kvm_types.h |  5 ++
 arch/s390/include/asm/kvm_types.h    |  5 ++
 arch/x86/include/asm/kvm_host.h      | 17 +----
 arch/x86/include/asm/kvm_types.h     | 11 ++++
 arch/x86/kvm/mmu.c                   | 97 ++++++----------------------
 arch/x86/kvm/paging_tmpl.h           |  4 +-
 include/linux/kvm_host.h             | 11 ++++
 include/linux/kvm_types.h            | 13 ++++
 virt/kvm/arm/arm.c                   |  2 +-
 virt/kvm/arm/mmu.c                   | 68 +++++--------------
 virt/kvm/kvm_main.c                  | 60 +++++++++++++++++
 21 files changed, 198 insertions(+), 230 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_types.h
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
```
