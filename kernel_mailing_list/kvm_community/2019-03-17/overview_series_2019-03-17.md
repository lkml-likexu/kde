#### [RFC PATCH] KVM: arm/arm64: Enable direct irqfd MSI injection
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Currently, IRQFD on arm still uses the deferred workqueue mechanism
to inject interrupts into guest, which will likely lead to a busy
context-switching from/to the kworker thread. This overhead is for
no purpose (only in my view ...) and will result in an interrupt
performance degradation.

Implement kvm_arch_set_irq_inatomic() for arm/arm64 to support direct
irqfd MSI injection, by which we can get rid of the annoying latency.
As a result, irqfd MSI intensive scenarios (e.g., DPDK with high packet
processing workloads) will benefit from it.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---

It seems that only MSI will follow the IRQFD path, did I miss something?

This patch is still under test and sent out for early feedback. If I have
any mis-understanding, please fix me up and let me know. Thanks!

---
 virt/kvm/arm/vgic/trace.h      | 22 ++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic-irqfd.c | 21 +++++++++++++++++++++
 2 files changed, 43 insertions(+)

```
#### [PATCH v6 01/22] driver core: add per device iommu param
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

DMA faults can be detected by IOMMU at device level. Adding a pointer
to struct device allows IOMMU subsystem to report relevant faults
back to the device driver for further handling.
For direct assigned device (or user space drivers), guest OS holds
responsibility to handle and respond per device IOMMU fault.
Therefore we need fault reporting mechanism to propagate faults beyond
IOMMU subsystem.

There are two other IOMMU data pointers under struct device today, here
we introduce iommu_param as a parent pointer such that all device IOMMU
data can be consolidated here. The idea was suggested here by Greg KH
and Joerg. The name iommu_param is chosen here since iommu_data has been used.

Suggested-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Reviewed-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Link: https://lkml.org/lkml/2017/10/6/81
---
 include/linux/device.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH] virtio-fs: fix multiple tag support
##### From: Liu Bo <bo.liu@linux.alibaba.com>

```c
While doing memremap from pci_dev's system bus address to kernel virtual
address, we assign a wrong value to the %end of pgmap.res, which ends up
with a wrong resource size in the process of memremap, and that further
prevent the second virtiofs pci device from being probed successfully.

Signed-off-by: Liu Bo <bo.liu@linux.alibaba.com>
---
 fs/fuse/virtio_fs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
