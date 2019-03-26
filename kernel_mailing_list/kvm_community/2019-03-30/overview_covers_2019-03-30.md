

#### [PATCH v2 0/1] vfio: Use dev_printk() when possible
##### From: Bjorn Helgaas <helgaas@kernel.org>
From: Bjorn Helgaas <bhelgaas@google.com>

```c

From: Bjorn Helgaas <bhelgaas@google.com>

Use dev_printk() in VFIO when possible.

Changes from v1:
  - Add colons after __func__ names in vfio_platform_amdxgbe.c (thanks,
    Joe).
  - Use the correct struct device * in vfio_platform_amdxgbe.c (thanks,
    Eric).
  - Use pci_printk() when we know we have a PCI device.
  - Add pci_notice_ratelimited() for use in vfio_pci.c.
  - Define dev_fmt in vfio_pci.c to avoid dropping the KBUILD_MODNAME
    prefix when converting from pr_*() to pci_printk().  This also adds
    the prefix to the places that already used dev_printk().
  - Define dev_fmt in vfio_platform_common.c to avoid repeating "VFIO :" in
    messages (this also adds it to a few that didn't use the prefix).

Bjorn Helgaas (1):
  vfio: Use dev_printk() when possible

 drivers/vfio/pci/vfio_pci.c                   | 26 +++++++----------
 drivers/vfio/pci/vfio_pci_config.c            | 28 ++++++++----------
 .../platform/reset/vfio_platform_amdxgbe.c    |  5 ++--
 drivers/vfio/platform/vfio_platform_common.c  | 12 ++++----
 drivers/vfio/vfio.c                           | 29 +++++++++----------
 include/linux/pci.h                           |  3 ++
 6 files changed, 49 insertions(+), 54 deletions(-)
```
