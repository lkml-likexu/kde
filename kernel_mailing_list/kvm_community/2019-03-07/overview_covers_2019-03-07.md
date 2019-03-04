

#### [PATCH kvmtool 00/16] Support PCI BAR configuration
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

This series add support for guests writting to PCI BARs. Edk2 does this
and is not aware of the "linux,pci-probe-only" property in the chosen node.

- Patches 1 to 3 do miscelaneous fixes
- Patch 4 fixes the way we deal with BAR sizing
- Patches 5 to 8 fixes the allocation/assignment of PCI IO BARs
- Patches 9 to 12 make it possible to remap ioport and mmio regions
  from vcpu threads, without pausing the entire VM
- Patches 13 to 16 adds the support for writting to BARs

Cheers,

Julien

-->

Julien Thierry (15):
  Makefile: Only compile vesa for archs that need it
  brlock: Always pass argument to br_read_lock/unlock
  brlock: fix build with KVM_BRLOCK_DEBUG
  ioport: pci: Move port allocations to PCI devices
  pci: Fix ioport allocation size
  arm/pci: Fix PCI IO region
  arm/pci: Do not use first PCI IO space bytes for devices
  brlock: Use rwlock instead of pause
  ref_cnt: Add simple ref counting API
  mmio: Allow mmio callbacks to be called without locking
  ioport: Allow ioport callbacks to be called without locking
  vfio: Add support for BAR configuration
  virtio/pci: Make memory and IO BARs independent
  virtio/pci: update virtio mapping when PCI BARs are reconfigured
  arm/fdt: Remove PCI probe only property

Sami Mujawar (1):
  pci: Fix BAR resource sizing arbitration

 Makefile                     |   3 +-
 arm/fdt.c                    |   1 -
 arm/include/arm-common/pci.h |   1 +
 arm/kvm.c                    |   3 +
 arm/pci.c                    |  24 ++++-
 hw/pci-shmem.c               |   3 +-
 hw/vesa.c                    |   4 +-
 include/kvm/brlock.h         |  21 +---
 include/kvm/ioport.h         |   5 -
 include/kvm/kvm.h            |   2 +
 include/kvm/pci.h            |   2 +
 include/kvm/ref_cnt.h        |  53 ++++++++++
 include/kvm/virtio-pci.h     |   1 +
 ioport.c                     |  80 ++++++++--------
 kvm.c                        |   4 +
 mmio.c                       |  30 ++++--
 pci.c                        |  59 +++++++++++-
 vfio/core.c                  |   6 +-
 vfio/pci.c                   |  82 +++++++++++++++-
 virtio/pci.c                 | 223 ++++++++++++++++++++++++++++++++++++-------
 20 files changed, 491 insertions(+), 116 deletions(-)
 create mode 100644 include/kvm/ref_cnt.h
---
1.9.1
```
