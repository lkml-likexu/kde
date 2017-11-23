

#### [PATCH kernel 0/3] vfio/spapr_tce: Reworks for NVIDIA V100 + P9
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c

This is a third set of patches required for passing through NVIDIA V100
with coherent memory. The full patchset is here:
https://github.com/aik/linux/tree/nv2
The matching QEMU is here:
https://github.com/aik/qemu/tree/nv2

This implements a subdriver for NVIDIA V100 GPU with coherent memory and
NPU/ATS support available in the POWER9 CPU.

This does not address the interconnected GPUs, this will be posted as
a separate patchset in a few days.

This depends on:
[PATCH kernel 0/4] vfio/spapr_tce: Reworks for NVIDIA V100 + P9 passthrough (part 1)
[PATCH kernel 0/5] powerpc/powernv/npu: Reworks for NVIDIA V100 + P9 passthrough (part 2)
[PATCH kernel RFC 3/3] powerpc/pseries/iommu: Use memory@ nodes in max RAM address calculation

Please comment. Thanks.



Alexey Kardashevskiy (3):
  vfio_pci: Allow mapping extra regions
  vfio_pci: Allow regions to add own capabilities
  vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] [10de:1db1] subdriver

 drivers/vfio/pci/Makefile           |   1 +
 drivers/vfio/pci/vfio_pci_private.h |   8 +
 include/uapi/linux/vfio.h           |  18 ++
 drivers/vfio/pci/vfio_pci.c         |  51 ++++-
 drivers/vfio/pci/vfio_pci_nvlink2.c | 409 ++++++++++++++++++++++++++++++++++++
 drivers/vfio/pci/Kconfig            |   4 +
 6 files changed, 489 insertions(+), 2 deletions(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c
```
