#### [PATCH v2] vfio_pci: Replace pci_try_reset_function() with __pci_reset_function_locked() to ensure that the pci device configuration
##### From: hexin <hexin.op@gmail.com>

```c
In vfio_pci_enable(), save the device's initial configuration information
and then restore the configuration in vfio_pci_disable(). However, the
execution result is not the same. Since the pci_try_reset_function()
function saves the current state before resetting, the configuration
information restored by pci_load_and_free_saved_state() will be
overwritten. The __pci_reset_function_locked() function can be used
to prevent the configuration space from being overwritten.

Fixes: 890ed578df82 ("vfio-pci: Use pci "try" reset interface")
Signed-off-by: hexin <hexin15@baidu.com>
Signed-off-by: Liu Qi <liuqi16@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
---
 drivers/vfio/pci/vfio_pci.c | 17 +++++++++++++----
 1 file changed, 13 insertions(+), 4 deletions(-)

```
