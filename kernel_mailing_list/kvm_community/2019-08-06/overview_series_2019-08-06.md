#### [PATCH v8 01/14] perf/x86: fix the variable type of the lbr msrs
##### From: Wei Wang <wei.w.wang@intel.com>

```c
The msr variable type can be "unsigned int", which uses less memory than
the longer unsigned long. The lbr nr won't be a negative number, so make
it "unsigned int" as well.

Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andi Kleen <ak@linux.intel.com>
Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC PATCH 01/20] hostmem: Add hostmem-epc as a backend for SGX EPC
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
EPC (Enclave Page Cache) is a specialized type of memory used by Intel
SGX (Software Guard Extensions).  The SDM desribes EPC as:

    The Enclave Page Cache (EPC) is the secure storage used to store
    enclave pages when they are a part of an executing enclave. For an
    EPC page, hardware performs additional access control checks to
    restrict access to the page. After the current page access checks
    and translations are performed, the hardware checks that the EPC
    page is accessible to the program currently executing. Generally an
    EPC page is only accessed by the owner of the executing enclave or
    an instruction which is setting up an EPC page.

Because of its unique requirements, Linux manages EPC separately from
normal memory.  Similar to memfd, the device /dev/sgx/virt_epc can be
opened to obtain a file descriptor which can in turn be used to mmap()
EPC memory.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 backends/Makefile.objs |  1 +
 backends/hostmem-epc.c | 91 ++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 92 insertions(+)
 create mode 100644 backends/hostmem-epc.c

```
#### [PATCH] KVM: PPC: Book3S HV: XIVE: Free escalation interrupts before disabling the VP
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
When a vCPU is brought done, the XIVE VP is first disabled and then
the event notification queues are freed. When freeing the queues, we
check for possible escalation interrupts and free them also.

But when a XIVE VP is disabled, the underlying XIVE ENDs also are
disabled in OPAL. When an END is disabled, its ESB pages (ESn and ESe)
are disabled and loads return all 1s. Which means that any access on
the ESB page of the escalation interrupt will return invalid values.

When an interrupt is freed, the shutdown handler computes a 'saved_p'
field from the value returned by a load in xive_do_source_set_mask().
This value is incorrect for escalation interrupts for the reason
described above.

This has no impact on Linux/KVM today because we don't make use of it
but we will introduce in future changes a xive_get_irqchip_state()
handler. This handler will use the 'saved_p' field to return the state
of an interrupt and 'saved_p' being incorrect, softlockup will occur.

Fix the vCPU cleanup sequence by first freeing the escalation
interrupts if any, then disable the XIVE VP and last free the queues.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/kvm/book3s_xive.c        | 18 ++++++++++--------
 arch/powerpc/kvm/book3s_xive_native.c | 12 +++++++-----
 2 files changed, 17 insertions(+), 13 deletions(-)

```
#### [PATCH v1 1/2] vfio-mdev/mtty: Simplify interrupt generation
##### From: Parav Pandit <parav@mellanox.com>

```c
While generating interrupt, mdev_state is already available for which
interrupt is generated.
Instead of doing indirect way from state->device->uuid-> to searching
state linearly in linked list on every interrupt generation,
directly use the available state.

Hence, simplify the code to use mdev_state and remove unused helper
function with that.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 samples/vfio-mdev/mtty.c | 39 ++++++++-------------------------------
 1 file changed, 8 insertions(+), 31 deletions(-)

```
#### [PATCH v2] vfio: re-arrange vfio region definitions
##### From: Cornelia Huck <cohuck@redhat.com>

```c
It is easy to miss already defined region types. Let's re-arrange
the definitions a bit and add more comments to make it hopefully
a bit clearer.

No functional change.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
v1 -> v2:
  - moved all pci subtypes together
  - tweaked comments a bit more
---
 include/uapi/linux/vfio.h | 45 ++++++++++++++++++++++-----------------
 1 file changed, 26 insertions(+), 19 deletions(-)

```
#### [PATCH v2 1/5] x86: KVM: svm: don't pretend to advance RIP in case wrmsr_interception() results in #GP
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
svm->next_rip is only used by skip_emulated_instruction() and in case
kvm_set_msr() fails we rightfully don't do that. Move svm->next_rip
advancement to 'else' branch to avoid creating false impression that
it's always advanced (and make it look like rdmsr_interception()).

This is a preparatory change to removing hardcoded RIP advancement
from instruction intercepts, no functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
