#### [PATCH 1/7] PCI: Add define for the number of standard PCI BARs
##### From: Denis Efremov <efremov@linux.com>

```c
Code that iterates over all standard PCI BARs typically uses
PCI_STD_RESOURCE_END. However, it requires the "unusual" loop condition
"i <= PCI_STD_RESOURCE_END" rather than something more standard like
"i < PCI_STD_NUM_BARS".

This patch adds the definition PCI_STD_NUM_BARS which is equivalent to
"PCI_STD_RESOURCE_END + 1" and updates loop conditions to use it.

Signed-off-by: Denis Efremov <efremov@linux.com>
---
 drivers/pci/quirks.c          | 2 +-
 include/linux/pci.h           | 2 +-
 include/uapi/linux/pci_regs.h | 1 +
 3 files changed, 3 insertions(+), 2 deletions(-)

```
