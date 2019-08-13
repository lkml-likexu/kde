#### [PATCH v5 QEMU 2/3] virtio-balloon: Add bit to notify guest of unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add a bit for the page reporting feature provided by virtio-balloon.

This patch should be replaced once the feature is added to the Linux kernel
and the bit is backported into this exported kernel header.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/standard-headers/linux/virtio_balloon.h |    1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5 QEMU 3/3] virtio-balloon: Provide a interface for unused page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Add support for what I am referring to as "unused page reporting".
Basically the idea is to function very similar to how the balloon works
in that we basically end up madvising the page as not being used. However
we don't really need to bother with any deflate type logic since the page
will be faulted back into the guest when it is read or written to.

This is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   46 ++++++++++++++++++++++++++++++++++--
 include/hw/virtio/virtio-balloon.h |    2 +-
 2 files changed, 45 insertions(+), 3 deletions(-)

```
#### [PATCH] kvm-unit-test: nVMX: Fix 95d6d2c32288 ("nVMX: Test Host Segment Registers and Descriptor Tables on vmentry of nested guests")
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Commit 95d6d2c32288 added a test for the Segment Selector VMCS field. That test
sets the "host address-space size" VM-exit control to zero and as a result, on
VM-exit the guest exits as 32-bit. Since vmx tests are 64-bit, this results in
a hardware error.
This patch also cleans up a few other areas in commit 95d6d2c32288, including
replacing make_non_canonical() with NONCANONICAL.

Reported-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Krish Sadhukhan <kris.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 lib/x86/processor.h |  5 ---
 x86/vmx_tests.c     | 76 ++++++++++++++++++++-------------------------
 2 files changed, 33 insertions(+), 48 deletions(-)

```
#### [RFC][Patch v12 1/2] mm: page_reporting: core infrastructure
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch introduces the core infrastructure for free page reporting in
virtual environments. It enables the kernel to track the free pages which
can be reported to its hypervisor so that the hypervisor could
free and reuse that memory as per its requirement.

While the pages are getting processed in the hypervisor (e.g.,
via MADV_DONTNEED), the guest must not use them, otherwise, data loss
would be possible. To avoid such a situation, these pages are
temporarily removed from the buddy. The amount of pages removed
temporarily from the buddy is governed by the backend(virtio-balloon
in our case).

To efficiently identify free pages that can to be reported to the
hypervisor, bitmaps in a coarse granularity are used. Only fairly big
chunks are reported to the hypervisor - especially, to not break up THP
in the hypervisor - "MAX_ORDER - 2" on x86, and to save space. The bits
in the bitmap are an indication whether a page *might* be free, not a
guarantee. A new hook after buddy merging sets the bits.

Bitmaps are stored per zone, protected by the zone lock. A workqueue
asynchronously processes the bitmaps, trying to isolate and report pages
that are still free. The backend (virtio-balloon) is responsible for
reporting these batched pages to the host synchronously. Once reporting/
freeing is complete, isolated pages are returned back to the buddy.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 include/linux/mmzone.h         |  11 ++
 include/linux/page_reporting.h |  63 +++++++
 mm/Kconfig                     |   6 +
 mm/Makefile                    |   1 +
 mm/page_alloc.c                |  42 ++++-
 mm/page_reporting.c            | 332 +++++++++++++++++++++++++++++++++
 6 files changed, 448 insertions(+), 7 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

```
#### [PATCH v5 1/6] mm: Adjust shuffle code to allow for future coalescing
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

This patch is meant to move the head/tail adding logic out of the shuffle
code and into the __free_one_page function since ultimately that is where
it is really needed anyway. By doing this we should be able to reduce the
overhead and can consolidate all of the list addition bits in one spot.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h |   12 --------
 mm/page_alloc.c        |   70 +++++++++++++++++++++++++++---------------------
 mm/shuffle.c           |   24 ----------------
 mm/shuffle.h           |   32 ++++++++++++++++++++++
 4 files changed, 71 insertions(+), 67 deletions(-)

```
#### [PATCH 1/2] KVM: PPC: Book3S HV: Fix race in re-enabling XIVE escalation interrupts
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Escalation interrupts are interrupts sent to the host by the XIVE
hardware when it has an interrupt to deliver to a guest VCPU but that
VCPU is not running anywhere in the system.  Hence we disable the
escalation interrupt for the VCPU being run when we enter the guest
and re-enable it when the guest does an H_CEDE hypercall indicating
it is idle.

It is possible that an escalation interrupt gets generated just as we
are entering the guest.  In that case the escalation interrupt may be
using a queue entry in one of the interrupt queues, and that queue
entry may not have been processed when the guest exits with an H_CEDE.
The existing entry code detects this situation and does not clear the
vcpu->arch.xive_esc_on flag as an indication that there is a pending
queue entry (if the queue entry gets processed, xive_esc_irq() will
clear the flag).  There is a comment in the code saying that if the
flag is still set on H_CEDE, we have to abort the cede rather than
re-enabling the escalation interrupt, lest we end up with two
occurrences of the escalation interrupt in the interrupt queue.

However, the exit code doesn't do that; it aborts the cede in the sense
that vcpu->arch.ceded gets cleared, but it still enables the escalation
interrupt by setting the source's PQ bits to 00.  Instead we need to
set the PQ bits to 10, indicating that an interrupt has been triggered.
We also need to avoid setting vcpu->arch.xive_esc_on in this case
(i.e. vcpu->arch.xive_esc_on seen to be set on H_CEDE) because
xive_esc_irq() will run at some point and clear it, and if we race with
that we may end up with an incorrect result (i.e. xive_esc_on set when
the escalation interrupt has just been handled).

It is extremely unlikely that having two queue entries would cause
observable problems; theoretically it could cause queue overflow, but
the CPU would have to have thousands of interrupts targetted to it for
that to be possible.  However, this fix will also make it possible to
determine accurately whether there is an unhandled escalation
interrupt in the queue, which will be needed by the following patch.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 23 ++++++++++++++++-------
 1 file changed, 16 insertions(+), 7 deletions(-)

```
#### [QEMU Patch 1/2] virtio-balloon: adding bit for page reporting support
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch will be replaced once the feature is merged into the
Linux kernel.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 include/standard-headers/linux/virtio_balloon.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] s390: vfio-ap: remove unnecessary calls to disable queue interrupts
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
When an AP queue is reset (zeroized), interrupts are disabled. The queue
reset function currently tries to disable interrupts unnecessarily. This patch
removes the unnecessary calls to disable interrupts after queue reset.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 13 +++++++++----
 1 file changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH v5 QEMU 1/3] virtio-ballon: Implement support for page poison tracking feature
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

We need to make certain to advertise support for page poison tracking if
we want to actually get data on if the guest will be poisoning pages. So
if free page hinting is active we should add page poisoning support and
let the guest disable it if it isn't using it.

Page poisoning will result in a page being dirtied on free. As such we
cannot really avoid having to copy the page at least one more time since
we will need to write the poison value to the destination. As such we can
just ignore free page hinting if page poisoning is enabled as it will
actually reduce the work we have to do.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/virtio-balloon.c         |   25 +++++++++++++++++++++----
 include/hw/virtio/virtio-balloon.h |    1 +
 2 files changed, 22 insertions(+), 4 deletions(-)

```
