#### [PATCH v5 01/12] perf/x86: fix the variable type of the LBR MSRs
##### From: Wei Wang <wei.w.wang@intel.com>

```c
The MSR variable type can be "unsigned int", which uses less memory than
the longer unsigned long. The lbr nr won't be a negative number, so make
it "unsigned int" as well.

Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH][kvm-unit-test nVMX]: Check Host Control Registers on vmentry of L2 guests
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
 x86/vmx_tests.c     | 77 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 78 insertions(+)

```
#### [PATCH kvm-unit-tests] run_tests: allow specifying desired tests on the command line
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This is a simpler version of Sean Christopherson's patch, which also allows
specifying more than one test.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 run_tests.sh         | 2 ++
 scripts/runtime.bash | 4 ++++
 2 files changed, 6 insertions(+)

```
#### [PATCH] kvm: vmx: Fix entry nubmer check for add_atomic_switch_msr()
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
Commit ca83b4a7f2d068da79a0 ("x86/KVM/VMX: Add find_msr() helper function")
introduces the helper function find_msr(), which returns -ENOENT when
not find the msr in vmx->msr_autoload.guest/host. Correct checking contion
of no more available entry in vmx->msr_autoload.

Fixes: ca83b4a7f2d0 ("x86/KVM/VMX: Add find_msr() helper function")
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PULL 01/14] qapi: Fix qcow2 encryption doc typo
##### From: Laurent Vivier <laurent@vivier.eu>

```c
From: Eric Blake <eblake@redhat.com>

Present since commit b25b387f (2.10).

Signed-off-by: Eric Blake <eblake@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Message-Id: <20190206202848.16999-1-eblake@redhat.com>
Signed-off-by: Laurent Vivier <laurent@vivier.eu>
---
 qapi/block-core.json | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V4] KVM: x86: Sync the pending Posted-Interrupts
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Some Posted-Interrupts from passthrough devices may be lost or
overwritten when the vCPU is in runnable state.

The SN (Suppress Notification) of PID (Posted Interrupt Descriptor) will
be set when the vCPU is preempted (vCPU in KVM_MP_STATE_RUNNABLE state
but not running on physical CPU). If a posted interrupt coming at this
time, the irq remmaping facility will set the bit of PIR (Posted
Interrupt Requests) without ON (Outstanding Notification).
So this interrupt can't be sync to APIC virtualization register and
will not be handled by Guest because ON is zero.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 26 +++++++++++---------------
 arch/x86/kvm/vmx/vmx.h |  6 ++++++
 arch/x86/kvm/x86.c     |  2 +-
 3 files changed, 18 insertions(+), 16 deletions(-)

```
#### [PATCH v3 1/9] s390: vfio_ap: link the vfio_ap devices to the vfio_ap bus subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Libudev relies on having a subsystem link for non-root devices. To
avoid libudev (and potentially other userspace tools) choking on the
matrix device let us introduce a vfio_ap bus and with that the vfio_ap
bus subsytem, and make the matrix device reside within it.

We restrict the number of allowed devices to a single one.

Doing this we need to suppress the forced link from the matrix device to
the vfio_ap driver and we suppress the device_type we do not need
anymore.

Since the associated matrix driver is not the vfio_ap driver any more,
we have to change the search for the devices on the vfio_ap driver in
the function vfio_ap_verify_queue_reserved.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reported-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 63 +++++++++++++++++++++++++++++++----
 drivers/s390/crypto/vfio_ap_ops.c     |  4 +--
 drivers/s390/crypto/vfio_ap_private.h |  1 +
 3 files changed, 60 insertions(+), 8 deletions(-)

```
