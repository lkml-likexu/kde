#### [PATCH] KVM: lapic: Check for in-kernel LAPIC before deferencing apic pointer
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
...to avoid dereferencing a null pointer when querying the per-vCPU
timer advance.

Fixes: 39497d7660d98 ("KVM: lapic: Track lapic timer advance per vCPU")
Reported-by: syzbot+f7e65445a40d3e0e4ebf@syzkaller.appspotmail.com
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
 arch/x86/kvm/lapic.c | 3 ---
 arch/x86/kvm/x86.c   | 3 ++-
 2 files changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: XIVE: Clear escalation interrupt pointers on device close
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This adds code to ensure that after a XIVE or XICS-on-XIVE KVM device
is closed, KVM will not try to enable or disable any of the escalation
interrupts for the VCPUs.  We don't have to worry about races between
clearing the pointers and use of the pointers by the XIVE context
push/pull code, because the callers hold the vcpu->mutex, which is
also taken by the KVM_RUN code.  Therefore the vcpu cannot be entering
or exiting the guest concurrently.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_xive.c | 15 +++++++++++++++
 1 file changed, 15 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: XIVE: Prevent races when releasing device
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Now that we have the possibility of a XIVE or XICS-on-XIVE device being
released while the VM is still running, we need to be careful about
races and potential use-after-free bugs.  Although the kvmppc_xive
struct is not freed, but kept around for re-use, the kvmppc_xive_vcpu
structs are freed, and they are used extensively in both the XIVE native
and XICS-on-XIVE code.

There are various ways in which XIVE code gets invoked:

- VCPU entry and exit, which do push and pull operations on the XIVE hardware
- one_reg get and set functions (vcpu->mutex is held)
- XICS hypercalls (but only inside guest execution, not from
  kvmppc_pseries_do_hcall)
- device creation calls (kvm->lock is held)
- device callbacks - get/set attribute, mmap, pagefault, release/destroy
- set_mapped/clr_mapped calls (kvm->lock is held)
- connect_vcpu calls
- debugfs file read callbacks

Inside a device release function, we know that userspace cannot have an
open file descriptor referring to the device, nor can it have any mmapped
regions from the device.  Therefore the device callbacks are excluded,
as are the connect_vcpu calls (since they need a fd for the device).
Further, since the caller holds the kvm->lock mutex, no other device
creation calls or set/clr_mapped calls can be executing concurrently.

To exclude VCPU execution and XICS hypercalls, we temporarily set
kvm->arch.mmu_ready to 0.  This forces any VCPU task that is trying to
enter the guest to take the kvm->lock mutex, which is held by the caller
of the release function.  Then, sending an IPI to all other CPUs forces
any VCPU currently executing in the guest to exit.

Finally, we take the vcpu->mutex for each VCPU around the process of
cleaning up and freeing its XIVE data structures, in order to exclude
any one_reg get/set calls.

This patch does not address the races in the debugfs read callbacks.
They will be addressed in a later patch.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
Cedric,

I think we need this on top of your patch 17/17, since you are freeing
the kvmppc_xive_vcpu structs.  With this, we can probably also free
the kvmppc_xive struct, though I haven't yet completely satisfied
myself about that.  If you can see any entry point that I have missed
(other than the debugfs stuff), let me know.

I can either apply this on top of your series, or fold it into your
17/17, whichever you prefer.

 arch/powerpc/kvm/book3s_xive.c        | 44 ++++++++++++++++++++++++++++++-----
 arch/powerpc/kvm/book3s_xive_native.c | 40 +++++++++++++++++++++++++++----
 2 files changed, 74 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: s390: vsie: Do not shadow CRYCB when no AP and no keys
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
When the guest do not have AP instructions nor Key management
we should return without shadowing the CRYCB.

We did not check correctly in the past.

Fixes: b10bd9a256ae ("s390: vsie: Use effective CRYCBD.31 to check CRYCBD
validity")
Fixes: 6ee74098201b ("KVM: s390: vsie: allow CRYCB FORMAT-0")

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Tested-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/vsie.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: s390: vsie: Return correct values for Invalid CRYCB format
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Let's use the correct validity number.

Fixes: 55ded154b43 "KVM: s390: vsie: Allow CRYCB FORMAT-2"

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/vsie.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: selftests: make hyperv_cpuid test pass on AMD
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Enlightened VMCS is only supported on Intel CPUs but the test shouldn't
fail completely.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 01/10] virtio/s390: use vring_create_virtqueue
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
The commit 2a2d1382fe9d ("virtio: Add improved queue allocation API")
establishes a new way of allocating virtqueues (as a part of the effort
that taught DMA to virtio rings).

In the future we will want virtio-ccw to use the DMA API as well.

Let us switch from the legacy method of allocating virtqueues to
vring_create_virtqueue() as the first step into that direction.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 30 +++++++++++-------------------
 1 file changed, 11 insertions(+), 19 deletions(-)

```
#### [PATCH v2] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Some new systems have multiple software-visible die within each package.
Add support to expose Intel V2 Extended Topology Enumeration Leaf CPUID.1F.

Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---

==changelog==
v2:
- Apply cpuid.1f check rule on Intel SDM page 3-222 Vol.2A
- Add comment to handle 0x1f anf 0xb in common code
- Reduce check time in a descending-break style

v1: https://lkml.org/lkml/2019/4/22/28

 arch/x86/kvm/cpuid.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
#### [PATCH v3] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Add support to expose Intel V2 Extended Topology Enumeration Leaf for
some new systems with multiple software-visible die within each package.

When CPUID executes with EAX set to 1FH, the processor returns information
about extended topology enumeration data. Software must detect the presence
of CPUID leaf 1FH by verifying (a) the highest leaf index supported by
CPUID is >= 1FH, and (b) CPUID.1FH:EBX[15:0] reports a non-zero value.

Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

==changelog==
v3:
- Redefine commit message and comment

v2:
- Apply cpuid.1f check rule on Intel SDM page 3-222 Vol.2A
- Add comment to handle 0x1f anf 0xb in common code
- Reduce check time in a descending-break style

v1: https://lkml.org/lkml/2019/4/22/28

 arch/x86/kvm/cpuid.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v7 1/4] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

First of all we do not want to change existing behavior when
intercepting AP instructions without the SIE allowing the guest
to use AP instructions.

In this patch we only handle the AQIC interception allowed by
facility 65 which will be enabled when the complete interception
infrastructure will be present.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command and only this command.

But we want to be able to return a correct answer to the guest
even there is no VFIO AP driver in the kernel.
Therefor, we inject the correct exceptions from inside KVM for the
case the callback is not initialized, which happens when the vfio_ap
driver is not loaded.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.
If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h      |  7 +++
 arch/s390/kvm/priv.c                  | 86 +++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  2 +
 3 files changed, 95 insertions(+)

```
#### [PATCH v7 1/6] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  8 +++++++-
 6 files changed, 46 insertions(+), 12 deletions(-)

```
