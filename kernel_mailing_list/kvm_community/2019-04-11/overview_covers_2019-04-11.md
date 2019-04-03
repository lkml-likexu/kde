

#### [PATCH 0/2] KVM: PPC: Book3S HV: add XIVE native exploitation mode
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c

Hello,

Here is a little series fixing the larger series "KVM: PPC: Book3S HV:
add XIVE native exploitation mode" that can be found here :

   http://patchwork.ozlabs.org/cover/1083513/

It adds a new 'release' method to the KVM device operation which, when
defined, is called when the file descriptor of the device is closed.
It acts as a replacement of the 'destroy' method.

These two patches replaces patch 16 :

   http://patchwork.ozlabs.org/patch/1083517/

Thanks,

C.

Cédric Le Goater (2):
  KVM: introduce a 'release' method for KVM devices
  KVM: PPC: Book3S HV: XIVE: replace the 'destroy' method by 'release'

 arch/powerpc/include/asm/kvm_host.h   |  1 +
 arch/powerpc/kvm/book3s_xive.h        |  1 +
 include/linux/kvm_host.h              |  9 +++
 arch/powerpc/kvm/book3s_xive.c        | 82 +++++++++++++++++++++++++--
 arch/powerpc/kvm/book3s_xive_native.c | 30 ++++++++--
 arch/powerpc/kvm/powerpc.c            |  9 +++
 virt/kvm/kvm_main.c                   | 13 +++++
 7 files changed, 134 insertions(+), 11 deletions(-)
```
#### [PATCH 0/3] kvm: selftests fixes and a new smm_test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

It turns out that the remaining issue in smm_test was in the test itself.
Here is the result...

Paolo

Paolo Bonzini (2):
  selftests: kvm/evmcs_test: complete I/O before migrating guest state
  selftests: kvm: fix for compilers that do not support -no-pie

Vitaly Kuznetsov (1):
  selftests: kvm: add a selftest for SMM

 tools/testing/selftests/kvm/Makefile               |   9 +-
 .../selftests/kvm/include/x86_64/processor.h       |  27 ++++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   5 +
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  20 ++-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   5 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c      | 157 +++++++++++++++++++++
 tools/testing/selftests/kvm/x86_64/state_test.c    |  15 +-
 7 files changed, 215 insertions(+), 23 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_test.c
```
#### [PATCH v6 0/7] KVM: nVMX Add IA32_PAT consistency checks
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

This is a continuation of Krish's series, which has suffered a teeny
tiny bit of scope creep (sorry Krish).  This is essentially a new series,
e.g. only the actual PAT-related patches, which haven't changed since v2,
are retained from previous versions.  But, to avoid unnecessary conflicts
I'm resending everything in one happy series.

The direction change relative to v5 is to self-document the top-level
consistency check functions by a) renaming the functions and b) using a
dedicated parameter to "return" the failure information, as suggested by
Paolo.  Previous versions had been taking the approach of using the return
value itself to document that a failed "postreqs" leads to a VM-Exit,
which was simply putting lipstick on a pig.

Krish Sadhukhan (2):
  Check "load IA32_PAT" VM-exit control on vmentry
  Check "load IA32_PAT" VM-entry control on vmentry

Sean Christopherson (5):
  KVM: nVMX: Move guest non-reg state checks to VM-Exit path
  KVM: nVMX: Rename and split top-level consistency checks to match SDM
  KVM: nVMX: Set VM-{Fail,Exit} failure info via params, not return val
  KVM: nVMX: Collapse nested_check_host_control_regs() into its caller
  KVM: nVMX: Return -EINVAL when signaling failure in VM-Entry helpers

 arch/x86/kvm/vmx/nested.c | 150 +++++++++++++++++++++-----------------
 1 file changed, 82 insertions(+), 68 deletions(-)
```
#### [PATCH 0/7] s390: vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c

This patch series extends the crypto adapter pass-through support to 
provide safeguards against inadvertent sharing of AP resources between
guests and/or the host, and to implement more of the s390 AP
architecture related to provisioning and dynamic configuration of
AP resources.

Tony Krowiak (7):
  s390: zcrypt: driver callback to indicate resource in use
  s390: vfio-ap: implement in-use callback for vfio_ap driver
  s390: vfio-ap: allow assignment of unavailable AP resources to mdev
    device
  s390: vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390: vfio-ap: wait for queue empty on queue reset
  s390: vfio-ap: handle dynamic config/deconfig of AP adapter
  s390: vfio-ap: update documentation

 Documentation/s390/vfio-ap.txt        | 147 +++++++++++----
 arch/s390/include/asm/kvm_host.h      |   2 +
 arch/s390/kvm/kvm-s390.c              |  37 ++++
 drivers/s390/crypto/ap_bus.c          | 138 ++++++++++++++-
 drivers/s390/crypto/ap_bus.h          |   3 +
 drivers/s390/crypto/vfio_ap_drv.c     |  39 +++-
 drivers/s390/crypto/vfio_ap_ops.c     | 324 +++++++++++++++-------------------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 8 files changed, 471 insertions(+), 221 deletions(-)
```
