#### [RFC PATCH 1/7] vfio/spimdev: Add documents for WarpDrive framework
##### From: Kenneth Lee <nek.in.cn@gmail.com>

```c
From: Kenneth Lee <liguozhu@hisilicon.com>

WarpDrive is a common user space accelerator framework.  Its main component
in Kernel is called spimdev, Share Parent IOMMU Mediated Device. It exposes
the hardware capabilities to the user space via vfio-mdev. So processes in
user land can obtain a "queue" by open the device and direct access the
hardware MMIO space or do DMA operation via VFIO interface.

WarpDrive is intended to be used with Jean Philippe Brucker's SVA patchset
(it is still in RFC stage) to support multi-process. But This is not a must.
Without the SVA patches, WarpDrive can still work for one process for every
hardware device.

This patch add detail documents for the framework.

Signed-off-by: Kenneth Lee <liguozhu@hisilicon.com>
---
 Documentation/00-INDEX                |   2 +
 Documentation/warpdrive/warpdrive.rst | 153 ++++++
 Documentation/warpdrive/wd-arch.svg   | 732 ++++++++++++++++++++++++++
 Documentation/warpdrive/wd.svg        | 526 ++++++++++++++++++
 4 files changed, 1413 insertions(+)
 create mode 100644 Documentation/warpdrive/warpdrive.rst
 create mode 100644 Documentation/warpdrive/wd-arch.svg
 create mode 100644 Documentation/warpdrive/wd.svg

```
#### [PATCH] KVM: s390: Make huge pages unavailable in ucontrol vms
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
We currently do not notify all gmaps when using gmap_pmdp_xchg(), due
to locking constraints. This makes ucontrol vms, which is the only vm
type that creates multiple gmaps, incompatible with huge pages.

ucontrol vms are rather exotic and creating a new locking concept is
no easy task. Hence we return EINVAL when trying to active
KVM_CAP_S390_HPAGE_1M and report it as being not available when
checking for it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.vnet.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm/x86 : simplify the handle of invvpid function
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
When vpids are not supported or disabled, vpid_sync_context is just
a no-op including single-context type or global-context type. we
can just return in vpid_sync_context when vpid==0.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/vmx.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
