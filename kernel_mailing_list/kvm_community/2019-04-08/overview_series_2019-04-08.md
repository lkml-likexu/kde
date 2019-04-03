#### [PATCH v4 1/3] vfio-pci: Release INTx's unmask eventfd properly
##### From: Leo Yan <leo.yan@linaro.org>

```c
The PCI device INTx uses event fd 'unmask_fd' to signal the deassertion
of the line from guest to host; but this eventfd isn't released properly
when disable INTx.

This patch firstly adds field 'unmask_fd' in struct vfio_pci_device for
storing unmask eventfd and close it when disable INTx.

Signed-off-by: Leo Yan <leo.yan@linaro.org>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 include/kvm/vfio.h | 1 +
 vfio/pci.c         | 2 ++
 2 files changed, 3 insertions(+)

```
