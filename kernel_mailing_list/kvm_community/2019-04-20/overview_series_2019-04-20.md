#### [PATCH] KVM: Directly return result from kvm_arch_check_processor_compat()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Add a wrapper to invoke kvm_arch_check_processor_compat() so that the
boilerplate ugliness of checking virtualization support on all CPUs is
hidden from the arch specific code.  x86's implementation in particular
is quite heinous, as it unnecessarily propagates the out-param pattern
into kvm_x86_ops.

While the x86 specific issue could be resolved solely by changing
kvm_x86_ops, make the change for all architectures as returning a value
directly is prettier and technically more robust, e.g. s390 doesn't set
the out param, which could lead to subtle breakage in the (highly
unlikely) scenario where the out-param was not pre-initialized by the
caller.

Opportunistically annotate svm_check_processor_compat() with __init.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Tested on VMX only.

 arch/mips/kvm/mips.c             | 4 ++--
 arch/powerpc/kvm/powerpc.c       | 4 ++--
 arch/s390/include/asm/kvm_host.h | 1 -
 arch/s390/kvm/kvm-s390.c         | 5 +++++
 arch/x86/include/asm/kvm_host.h  | 2 +-
 arch/x86/kvm/svm.c               | 4 ++--
 arch/x86/kvm/vmx/vmx.c           | 8 ++++----
 arch/x86/kvm/x86.c               | 4 ++--
 include/linux/kvm_host.h         | 2 +-
 virt/kvm/arm/arm.c               | 4 ++--
 virt/kvm/kvm_main.c              | 9 ++++++---
 11 files changed, 27 insertions(+), 20 deletions(-)

```
#### [PATCH 1/5] KVM: VMX: Fix handling of #MC that occurs during VM-Entry
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A previous fix to prevent KVM from consuming stale VMCS state after a
failed VM-Entry inadvertantly blocked KVM's handling of machine checks
that occur during VM-Entry.

Per Intel's SDM, a #MC during VM-Entry is handled in one of three ways,
depending on when the #MC is recognoized.  As it pertains to this bug
fix, the third case explicitly states EXIT_REASON_MCE_DURING_VMENTRY
is handled like any other VM-Exit during VM-Entry, i.e. sets bit 31 to
indicate the VM-Entry failed.

If a machine-check event occurs during a VM entry, one of the following occurs:
 - The machine-check event is handled as if it occurred before the VM entry:
        ...
 - The machine-check event is handled after VM entry completes:
        ...
 - A VM-entry failure occurs as described in Section 26.7. The basic
   exit reason is 41, for "VM-entry failure due to machine-check event".

Explicitly handle EXIT_REASON_MCE_DURING_VMENTRY as a one-off case in
vmx_vcpu_run() instead of binning it into vmx_complete_atomic_exit().
Doing so allows vmx_vcpu_run() to handle VMX_EXIT_REASONS_FAILED_VMENTRY
in a sane fashion and also simplifies vmx_complete_atomic_exit() since
VMCS.VM_EXIT_INTR_INFO is guaranteed to be fresh.

Fixes: b060ca3b2e9e7 ("kvm: vmx: Handle VMLAUNCH/VMRESUME failure properly")
Cc: Jim Mattson <jmattson@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 20 ++++++++------------
 1 file changed, 8 insertions(+), 12 deletions(-)

```
#### [PATCH v2 2/8] s390: vfio-ap: sysfs interface to display guest CRYCB
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Introduces a sysfs interface on the matrix mdev device to display the
contents of the shadow of the guest's CRYCB

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 58 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 58 insertions(+)

```
#### [PATCH v2 1/8] s390: vfio-ap: maintain a shadow of the CRYCB in use by a guest
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
This patch introduces a shadow of the CRYCB being used by a guest. This
will enable to more effectively manage dynamic changes to the AP
resources installed on the host that may be assigned to an mdev device
and being used by a guest. For example:

* AP adapter cards can be dynamically added to and removed from the AP
  configuration via the SE or an SCLP command.

* AP resources that disappear and reappear due to hardware malfunctions.

* AP queues bound to and unbound from the vfio_ap device driver by a
  root user.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c     | 69 ++++++++++++++++++++++++++++++++---
 drivers/s390/crypto/vfio_ap_private.h |  2 +
 2 files changed, 65 insertions(+), 6 deletions(-)

```
