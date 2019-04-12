

#### [PATCH 0/5] KVM: VMX: INTR, NMI and #MC cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

This series' primarily focus is to refine VMX's handling of INTRs, NMIs
and #MCs after a VM-Exit, making a few small optimizations and hopefully
resulting in more readable code.

There's also a bug fix related to handling #MCs that occur during VM-Entry
that was found by inspection when doing the aforementioned cleanup.

Sean Christopherson (5):
  KVM: VMX: Fix handling of #MC that occurs during VM-Entry
  KVM: VMX: Read cached VM-Exit reason to detect external interrupt
  KVM: VMX: Store the host kernel's IDT base in a global variable
  KVM: x86: Move kvm_{before,after}_interrupt() calls to vendor code
  KVM: VMX: Handle NMIs, #MCs and async #PFs in common irqs-disabled fn

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/svm.c              |   6 +-
 arch/x86/kvm/vmx/vmcs.h         |   6 ++
 arch/x86/kvm/vmx/vmx.c          | 111 +++++++++++++++++---------------
 arch/x86/kvm/vmx/vmx.h          |   1 -
 arch/x86/kvm/x86.c              |   4 +-
 6 files changed, 71 insertions(+), 59 deletions(-)
```
#### [PATCH v2 0/8] s390: vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c

This patch series extends the crypto adapter pass-through support to 
provide safeguards against inadvertent sharing of AP resources between
guests and/or the host, and to implement more of the s390 AP
architecture related to provisioning and dynamic configuration of
AP resources.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (8):
  s390: vfio-ap: maintain a shadow of the CRYCB in use by a guest
  s390: vfio-ap: sysfs interface to display guest CRYCB
  s390: vfio-ap: allow assignment of unavailable AP resources to mdev
    device
  s390: vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390: vfio-ap: wait for queue empty on queue reset
  s390: kvm: test CRYCB masks before setting them
  s390: vfio-ap: handle bind and unbind of AP queue device
  s390: vfio-ap: update documentation

 Documentation/s390/vfio-ap.txt        | 188 +++++++++++---
 arch/s390/kvm/kvm-s390.c              |  31 +++
 drivers/s390/crypto/vfio_ap_drv.c     |  16 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 449 ++++++++++++++++++++--------------
 drivers/s390/crypto/vfio_ap_private.h |   4 +
 5 files changed, 467 insertions(+), 221 deletions(-)
```
