#### [PATCH kvmtool 1/9] qcow: Fix qcow1 exit fault
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
Even though qcow1 doesn't use the refcount table, the cleanup path still
attempts to iterate over its LRU list. Initialize the list to avoid a
segfault on exit.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 disk/qcow.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [GIT PULL 1/1] s390: vsie: Use effective CRYCBD.31 to check CRYCBD validity
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Pierre Morel <pmorel@linux.ibm.com>

When facility.76 MSAX3 is present for the guest we must issue a validity
interception if the CRYCBD is not valid.

The bit CRYCBD.31 is an effective field and tested at each guest level
and has for effect to mask the facility.76

It follows that if CRYCBD.31 is clear and AP is not in use  we do not
have to test the CRYCBD validatity even if facility.76 is present in the
host.

Fixes: 6ee74098201b ("KVM: s390: vsie: allow CRYCB FORMAT-0")
Cc: stable@vger.kernel.org

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reported-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Message-Id: <1549876849-32680-1-git-send-email-pmorel@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/vsie.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 01/22] driver core: add per device iommu param
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
#### [PATCH v2][kvm-unit-test nVMX]: Check Host Control Registers on vmentry of L2 guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following checks are performed on vmentry of L2 guests:

    - The CR0 field must not set any bit to a value not supported in VMX
      operation.
    - The CR4 field must not set any bit to a value not supported in VMX
      operation.
    - On processors that support Intel 64 architecture, the CR3 field must
      be such that bits 63:52 and bits in the range 51:32 beyond the
      processor’s physical-address width must be 0.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
---
 lib/x86/processor.h |  1 +
 x86/vmx_tests.c     | 94 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 95 insertions(+)

```
