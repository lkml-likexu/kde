#### [PATCH kvmtool v2 1/9] qcow: Fix qcow1 exit fault
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
Even though qcow1 doesn't use the refcount table, the cleanup path still
attempts to iterate over its LRU list. Initialize the list to avoid a
segfault on exit.

Reviewed-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 disk/qcow.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [RFC PATCH kernel v2] powerpc/powernv: Isolate NVLinks between GV100GL on Witherspoon
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
The NVIDIA V100 SXM2 GPUs are connected to the CPU via PCIe links and
(on POWER9) NVLinks. In addition to that, GPUs themselves have direct
peer to peer NVLinks in groups of 2 to 4 GPUs. At the moment the POWERNV
platform puts all interconnected GPUs to the same IOMMU group.

However the user may want to pass individual GPUs to the userspace so
in order to do so we need to put them into separate IOMMU groups and
cut off the interconnects.

Thankfully V100 GPUs implement an interface to do by programming link
disabling mask to BAR0 of a GPU. Once a link is disabled in a GPU using
this interface, it cannot be re-enabled until the secondary bus reset is
issued to the GPU.

This adds an extra step to the secondary bus reset handler (the one used
for such GPUs) to block NVLinks to GPUs which do not belong to the same
group as the GPU being reset.

This adds a new "isolate_nvlink" kernel parameter to allow GPU isolation;
when enabled, every GPU gets its own IOMMU group. The new parameter is off
by default to preserve the existing behaviour.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
Changes:
v2:
* this is rework of [PATCH kernel RFC 0/2] vfio, powerpc/powernv: Isolate GV100GL
but this time it is contained in the powernv platform
---
 arch/powerpc/platforms/powernv/Makefile      |   2 +-
 arch/powerpc/platforms/powernv/pci.h         |   1 +
 arch/powerpc/platforms/powernv/eeh-powernv.c |   1 +
 arch/powerpc/platforms/powernv/npu-dma.c     |  24 +++-
 arch/powerpc/platforms/powernv/nvlinkgpu.c   | 131 +++++++++++++++++++
 5 files changed, 156 insertions(+), 3 deletions(-)
 create mode 100644 arch/powerpc/platforms/powernv/nvlinkgpu.c

```
#### [PATCH v3 1/3] mm: make dev_pagemap_mapping_shift() externally visible
##### From: Barret Rhoden <brho@google.com>

```c
KVM has a use case for determining the size of a dax mapping.  The KVM
code has easy access to the address and the mm; hence the change in
parameters.

Signed-off-by: Barret Rhoden <brho@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Dan Williams <dan.j.williams@intel.com>
---
 include/linux/mm.h  |  3 +++
 mm/memory-failure.c | 38 +++-----------------------------------
 mm/util.c           | 34 ++++++++++++++++++++++++++++++++++
 3 files changed, 40 insertions(+), 35 deletions(-)

```
#### [PATCH RFC 1/4] vsock/virtio: reduce credit update messages
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
In order to reduce the number of credit update messages,
we send them only when the space available seen by the
transmitter is less than VIRTIO_VSOCK_MAX_PKT_BUF_SIZE.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 include/linux/virtio_vsock.h            |  1 +
 net/vmw_vsock/virtio_transport_common.c | 14 +++++++++++---
 2 files changed, 12 insertions(+), 3 deletions(-)

```
