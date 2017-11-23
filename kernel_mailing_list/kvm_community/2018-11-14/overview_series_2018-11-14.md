#### [v2] uio/uio_pci_generic: Disable bus-mastering on releaseFrom: Venkatesh Srinivas <venkateshs@google.com>
##### From: Venkatesh Srinivas <venkateshs@google.com>

```c
Userspace code using uio_pci_generic may enable bus-mastering by
directly manipulating a PCI device's command register. If a userspace
program enables bus-mastering but exits/crashes uncleanly, bus-
mastering will still be enabled and stale DMA addresses may be
programmed and live in the device.

Disable bus-mastering unconditionally on last close of a UIO PCI fd
to avoid this. If the device did not have bus-mastering enabled,
pci_clear_master() is a no-op.

Signed-off-by: Venkatesh Srinivas <venkateshs@google.com>
Reviewed-by: Bjorn Helgaas <bhelgaas@google.com>
Reviewed-by: Catherine Sullivan <csully@google.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/uio/uio_pci_generic.c | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
