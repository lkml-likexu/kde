#### [PATCH v2 01/10] PCI: Add define for the number of standard PCI BARs
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
#### [PATCH v5 1/6] vfio: Define device specific irq type capability
##### From: Tina Zhang <tina.zhang@intel.com>

```c
Cap the number of irqs with fixed indexes and use capability chains
to chain device specific irqs.

Signed-off-by: Tina Zhang <tina.zhang@intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 include/uapi/linux/vfio.h | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH RFC 1/1] vfio-ccw: add some logging
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Usually, the common I/O layer logs various things into the s390
cio debug feature, which has been very helpful in the past when
looking at crash dumps. As vfio-ccw devices unbind from the
standard I/O subchannel driver, we lose some information there.

Let's introduce some vfio-ccw debug features and log some things
there. (Unfortunately we cannot reuse the cio debug feature from
a module.)

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c     | 50 ++++++++++++++++++++++++++--
 drivers/s390/cio/vfio_ccw_fsm.c     | 51 ++++++++++++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_ops.c     | 10 ++++++
 drivers/s390/cio/vfio_ccw_private.h | 17 ++++++++++
 4 files changed, 124 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio_pci: Replace pci_try_reset_function() with __pci_reset_function_locked() to ensure that the pci device configuration
##### From: hexin <hexin.op@gmail.com>

```c
In vfio_pci_enable(), save the device's initial configuration information
and then restore the configuration in vfio_pci_disable(). However, the
execution result is not the same. Since the pci_try_reset_function()
function saves the current state before resetting, the configuration
information restored by pci_load_and_free_saved_state() will be
overwritten. The __pci_reset_function_locked() function can be used
to prevent the configuration space from being overwritten.

Signed-off-by: hexin <hexin15@baidu.com>
Signed-off-by: Liu Qi <liuqi16@baidu.com>
Signed-off-by: Zhang Yu <zhangyu31@baidu.com>
---
 drivers/vfio/pci/vfio_pci.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
