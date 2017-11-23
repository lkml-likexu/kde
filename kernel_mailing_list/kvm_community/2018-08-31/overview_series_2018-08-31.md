#### [PATCH V5 1/4]  target-i386: introduce coalesced_pio kvm header update
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced_pio's struct and KVM_CAP_COALESCED_PIO header.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 accel/kvm/kvm-all.c       |  4 ++--
 linux-headers/linux/kvm.h | 11 +++++++++--
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH 1/3] nd: move nd_region to common header 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch moves nd_region definition to common header
include/linux/nd.h file. This is required for flush callback 
support for both virtio-pmem & pmem driver.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/nvdimm/nd.h | 39 ---------------------------------------
 include/linux/nd.h  | 40 ++++++++++++++++++++++++++++++++++++++++
 2 files changed, 40 insertions(+), 39 deletions(-)

```
#### [PATCH] qemu: Add virtio pmem device
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds virtio-pmem Qemu device.

 This device presents memory address range information to guest
 which is backed by file backend type. It acts like persistent
 memory device for KVM guest. Guest can perform read and 
 persistent write operations on this memory range with the help 
 of DAX capable filesystem.

 Persistent guest writes are assured with the help of virtio 
 based flushing interface. When guest userspace space performs 
 fsync on file fd on pmem device, a flush command is send to 
 Qemu over VIRTIO and host side flush/sync is done on backing 
 image file.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
Changes from RFC v3:
- Return EIO for host fsync failure instead of errno - Luiz, Stefan
- Change version for inclusion to Qemu 3.1 - Eric

Changes from RFC v2:
- Use aio_worker() to avoid Qemu from hanging with blocking fsync
  call - Stefan
- Use virtio_st*_p() for endianess - Stefan
- Correct indentation in qapi/misc.json - Eric

 hw/virtio/Makefile.objs                     |   3 +
 hw/virtio/virtio-pci.c                      |  44 +++++
 hw/virtio/virtio-pci.h                      |  14 ++
 hw/virtio/virtio-pmem.c                     | 241 ++++++++++++++++++++++++++++
 include/hw/pci/pci.h                        |   1 +
 include/hw/virtio/virtio-pmem.h             |  42 +++++
 include/standard-headers/linux/virtio_ids.h |   1 +
 qapi/misc.json                              |  26 ++-
 8 files changed, 371 insertions(+), 1 deletion(-)
 create mode 100644 hw/virtio/virtio-pmem.c
 create mode 100644 include/hw/virtio/virtio-pmem.h

```
#### [PATCH 1/3] s390/setup: set control program code via diag 318
##### From: Collin Walling <walling@linux.ibm.com>

```c
The s390x diagnose 318 instruction sets the control program name code (CPNC)
and control program version code (CPVC) to provide usefu information regarding
the OS during debugging. The CPNC is explicitly set to 4 to indicate a Linux/KVM
environment.

The CPVC is a 7-byte value containing:

 - 3-byte Linux version code
 - 3-byte distribution identifier set in the config file
 - 1-byte null

The distro ID is set by the Kconfig option "Distribution Identifier" under the
"Processors Type and Features" section.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Heiko Carstens <heiko.carstens@de.ibm.com>
---
 arch/s390/Kconfig              |  8 ++++++++
 arch/s390/include/asm/diag.h   | 12 ++++++++++++
 arch/s390/include/asm/sclp.h   |  1 +
 arch/s390/kernel/diag.c        |  1 +
 arch/s390/kernel/setup.c       | 23 +++++++++++++++++++++++
 drivers/s390/char/sclp_early.c |  6 +++++-
 6 files changed, 50 insertions(+), 1 deletion(-)

```
