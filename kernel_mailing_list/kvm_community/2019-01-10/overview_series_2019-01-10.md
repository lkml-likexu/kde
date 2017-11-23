#### [PATCH kvmtool v2 1/6] rtc: Initialize the Register D for MC146818 RTC
##### From: Julien Thierry <julien.thierry@arm.com>

```c
From: Sami Mujawar <sami.mujawar@arm.com>

Some software drivers check the VRT bit (BIT7) of Register D before
using the MC146818 RTC. Initialized the VRT bit in rtc__init() to
indicate that the RAM and time contents are valid.

Signed-off-by: Sami Mujawar <sami.mujawar@arm.com>
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
Reviewed-by: Andre Przywara <andre.przywara@arm.com>
---
 hw/rtc.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [GIT PULL] VFIO fixes for v5.0-rc2
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit bfeffd155283772bbe78c6a05dec7c0128ee500c:

  Linux 5.0-rc1 (2019-01-06 17:08:20 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.0-rc2

for you to fetch changes up to 58fec830fc19208354895d9832785505046d6c01:

  vfio/type1: Fix unmap overflow off-by-one (2019-01-08 09:31:28 -0700)

----------------------------------------------------------------
VFIO fixes for v5.0-rc2

 - Fix trace header include path for in-tree builds (Masahiro Yamada)

 - Fix overflow in unmap wrap-around test (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/type1: Fix unmap overflow off-by-one

Masahiro Yamada (1):
      vfio/pci: set TRACE_INCLUDE_PATH to fix the build error

 drivers/vfio/pci/trace.h        | 2 +-
 drivers/vfio/vfio_iommu_type1.c | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)
```
#### [PATCH kvmtool v2 01/13] ioeventfd: Fix removal of ioeventfd
##### From: Julien Thierry <julien.thierry@arm.com>

```c
From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

Fix three bugs that prevent removal of ioeventfds in KVM. Store the
flags in the right structure, check the datamatch parameter, and pass
the fd to KVM.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
---
 ioeventfd.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Initialize the physical allocator on mem init
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
The physical and virtual allocators can coexist, so we can initialize
the former and allocate pages without breaking VM alloc.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH 01/14] KVM: x86/mmu: Move slot_level_*() helper functions up a few lines
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
...so that kvm_mmu_invalidate_zap_pages_in_memslot() can utilize the
helpers in future patches.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c | 139 +++++++++++++++++++++++----------------------
 1 file changed, 70 insertions(+), 69 deletions(-)

```
#### [kvm-unit-tests PATCH v5 01/11] s390x: Add Sigp header file
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
The magic numbers for SIGP are not nice to read, so let's put them in
a new header file. Also move sigp_stop() there, it will later be
joined by more sigp functions and definitions.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/sigp.h | 60 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/io.c       | 11 +---------
 2 files changed, 61 insertions(+), 10 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h

diff --git a/lib/s390x/asm/sigp.h b/lib/s390x/asm/sigp.h
new file mode 100644
index 0000000..899a66b
--- /dev/null
+++ b/lib/s390x/asm/sigp.h
@@ -0,0 +1,60 @@
+/*
+ * SIGP related definitions.
+ *
+ * Copied from the Linux kernel file arch/s390/include/asm/sigp.h
+ *
+ * This work is licensed under the terms of the GNU GPL, version
+ * 2. See the COPYING file in the top-level directory.
+ */
+
+#ifndef _ASM_S390X_SIGP_H_
+#define _ASM_S390X_SIGP_H_
+
+/* SIGP order codes */
+#define SIGP_SENSE			1
+#define SIGP_EXTERNAL_CALL		2
+#define SIGP_EMERGENCY_SIGNAL		3
+#define SIGP_START			4
+#define SIGP_STOP			5
+#define SIGP_RESTART			6
+#define SIGP_STOP_AND_STORE_STATUS	9
+#define SIGP_INITIAL_CPU_RESET		11
+#define SIGP_CPU_RESET			12
+#define SIGP_SET_PREFIX			13
+#define SIGP_STORE_STATUS_AT_ADDRESS	14
+#define SIGP_SET_ARCHITECTURE		18
+#define SIGP_COND_EMERGENCY_SIGNAL	19
+#define SIGP_SENSE_RUNNING		21
+#define SIGP_SET_MULTI_THREADING	22
+#define SIGP_STORE_ADDITIONAL_STATUS	23
+
+/* SIGP condition codes */
+#define SIGP_CC_ORDER_CODE_ACCEPTED 0
+#define SIGP_CC_STATUS_STORED	    1
+#define SIGP_CC_BUSY		    2
+#define SIGP_CC_NOT_OPERATIONAL	    3
+
+/* SIGP cpu status bits */
+
+#define SIGP_STATUS_INVALID_ORDER	0x00000002UL
+#define SIGP_STATUS_CHECK_STOP		0x00000010UL
+#define SIGP_STATUS_STOPPED		0x00000040UL
+#define SIGP_STATUS_EXT_CALL_PENDING	0x00000080UL
+#define SIGP_STATUS_INVALID_PARAMETER	0x00000100UL
+#define SIGP_STATUS_INCORRECT_STATE	0x00000200UL
+#define SIGP_STATUS_NOT_RUNNING		0x00000400UL
+
+#ifndef __ASSEMBLER__
+
+static inline void sigp_stop(void)
+{
+	register unsigned long status asm ("1") = 0;
+	register unsigned long cpu asm ("2") = 0;
+
+	asm volatile(
+		"	sigp %0,%1,0(%2)\n"
+		: "+d" (status)  : "d" (cpu), "d" (SIGP_STOP) : "cc");
+}
+
+#endif /* __ASSEMBLER__ */
+#endif /* _ASM_S390X_SIGP_H_ */
```
#### [PATCH v1] vfio-mdev: Switch to use new generic UUID API
##### From: Andy Shevchenko <andriy.shevchenko@linux.intel.com>

```c
There are new types and helpers that are supposed to be used in new code.

As a preparation to get rid of legacy types and API functions do
the conversion here.

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Andy Shevchenko <andriy.shevchenko@linux.intel.com>
---
 drivers/vfio/mdev/mdev_core.c    | 15 +++++++--------
 drivers/vfio/mdev/mdev_private.h |  4 ++--
 drivers/vfio/mdev/mdev_sysfs.c   |  6 +++---
 include/linux/mdev.h             |  2 +-
 samples/vfio-mdev/mtty.c         | 17 +++++++----------
 5 files changed, 20 insertions(+), 24 deletions(-)

```
#### [PATCH v5 1/8] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, all DMA requests out of or to a subset of
a physical PCI device can be protected by the IOMMU. As a
result, there is a request in software to attach multiple
domains to a physical PCI device. One example of such use
model is the Intel Scalable IOV [1] [2]. The Intel vt-d
3.0 spec [3] introduces the scalable mode which enables
PASID granularity DMA isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs include:

* iommu_dev_has_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Check whether both IOMMU and device support IOMMU aux
    domain feature. Below aux-domain specific interfaces
    are available only after this returns true.

* iommu_dev_enable/disable_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Enable/disable device specific aux-domain feature.

* iommu_aux_attach_device(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_aux_detach_device(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_aux_get_pasid(domain, dev)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalable IOV needs
    to write this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

This has been updated with the latest proposal from Joerg
posted here [5].

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Joerg Roedel <joro@8bytes.org>

and some discussions can be found here [4] [5].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4
[5] https://www.spinics.net/lists/iommu/msg31874.html

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Suggested-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 80 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 61 +++++++++++++++++++++++++++++++++
 2 files changed, 141 insertions(+)

```
