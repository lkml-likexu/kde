#### [PATCH]  Fix mm->owner point to a task that does not exists.
##### From: gchen.guomin@gmail.com

```c
From: guomin chen <gchen.guomin@gmail.com>

 Under normal circumstances,When do_exit exits, mm->owner will
 be updated on exit_mm(). but when the kernel process calls
 unuse_mm() and then exits,mm->owner cannot be updated. And it
 will point to a task that has been released.

 Below is my issue on vhost_net:
    A, B are two kernel processes(such as vhost_worker),
    C is a user space process(such as qemu), and all
    three use the mm of the user process C.
    Now, because user process C exits abnormally, the owner of this
    mm becomes A. When A calls unuse_mm and exits, this mm->ower
    still points to the A that has been released.
    When B accesses this mm->owner again, A has been released.

 Process A             Process B
 vhost_worker()        vhost_worker()
  ---------             ---------
  use_mm()              use_mm()
   ...
  unuse_mm()
     tsk->mm=NULL
   do_exit()            page fault
    exit_mm()           access mm->owner
   can't update owner   kernel Oops

                        unuse_mm()

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: <kvm@vger.kernel.org>
Cc: <virtualization@lists.linux-foundation.org>
Cc: <netdev@vger.kernel.org>
Cc: <linux-kernel@vger.kernel.org>
Signed-off-by: guomin chen <gchen.guomin@gmail.com>
---
 drivers/vhost/vhost.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH net V2 1/4] vhost: make sure used idx is seen before log in vhost_add_used_n()
##### From: Jason Wang <jasowang@redhat.com>

```c
We miss a write barrier that guarantees used idx is updated and seen
before log. This will let userspace sync and copy used ring before
used idx is update. Fix this by adding a barrier before log_write().

Fixes: 8dd014adfea6f ("vhost-net: mergeable buffers support")
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/4] KVM: PPC: Pass change type down to memslot commit function
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
From: Bharata B Rao <bharata@linux.ibm.com>

Currently, kvm_arch_commit_memory_region() gets called with a
parameter indicating what type of change is being made to the memslot,
but it doesn't pass it down to the platform-specific memslot commit
functions.  This adds the `change' parameter to the lower-level
functions so that they can use it in future.

Signed-off-by: Bharata B Rao <bharata@linux.vnet.ibm.com>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/kvm_ppc.h | 6 ++++--
 arch/powerpc/kvm/book3s.c          | 5 +++--
 arch/powerpc/kvm/book3s_hv.c       | 3 ++-
 arch/powerpc/kvm/book3s_pr.c       | 3 ++-
 arch/powerpc/kvm/powerpc.c         | 2 +-
 5 files changed, 12 insertions(+), 7 deletions(-)

```
#### [kvm-unit-test v2 1/4] KVM nVMX: Change the names of the functions test_vmcs_page_* to test_vmcs_addr_*
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
... because these functions can be used for any VMCS address and not just
     a page.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 65 ++++++++++++++++++++++++++++-----------------------------
 1 file changed, 32 insertions(+), 33 deletions(-)

```
#### [PATCH] MAINTAINERS/vfio-ccw: add Farhan and Eric, make Halil Reviewer
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Eric and Farhan will help with maintaining vfio-ccw.

Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>
Cc: Farhan Ali <alifm@linux.ibm.com>
Cc: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
Acked-by: Farhan Ali <alifm@linux.ibm.com>
Acked-by: Eric Farman <farman@linux.ibm.com>
---
 MAINTAINERS | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v4] x86/hyper-v: Mark TLFS structures packed
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
The TLFS structures are used for hypervisor-guest communication and must
exactly meet the specification.

Compilers can add alignment padding to structures or reorder struct members
for randomization and optimization, which would break the hypervisor ABI.

Mark the structures as packed to prevent this. 'struct hv_vp_assist_page'
and 'struct hv_enlightened_vmcs' need to be properly padded to support the
change.

Suggested-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
---
- Changes since v3:
 - Properly pad 'struct hv_vp_assist_page' and 'struct hv_enlightened_vmcs'.
 - Add Michael's Reviewed-by tag.

- This is a follow-up to my "[PATCH v2 0/4] x86/kvm/hyper-v: Implement
 Direct Mode for synthetic timers" series, as suggested by Thomas I'm
 routing it to KVM tree to avoid merge conflicts.
---
 arch/x86/include/asm/hyperv-tlfs.h | 57 ++++++++++++++++--------------
 1 file changed, 30 insertions(+), 27 deletions(-)

```
#### [PATCH v5 1/7] KVM: nVMX: Prepend "nested_vmx_" to check_vmentry_{pre,post}reqs()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
.. as they are used only in nested vmx context.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/kvm/vmx.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [PATCH] virtio-fs: fix semicolon.cocci warnings
##### From: kbuild test robot <fengguang.wu@intel.com>

```c
From: kbuild test robot <fengguang.wu@intel.com>

fs/fuse/virtio_fs.c:88:17-18: Unneeded semicolon


 Remove unneeded semicolon.

Generated by: scripts/coccinelle/misc/semicolon.cocci

Fixes: 065b4fe69a2b ("virtio-fs: Add VIRTIO_PCI_CAP_SHARED_MEMORY_CFG and utility to find them")
CC: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: kbuild test robot <fengguang.wu@intel.com>
---

url:    https://github.com/0day-ci/linux/commits/Vivek-Goyal/virtio-fs-shared-file-system-for-virtual-machines/20181211-103034
base:   https://git.kernel.org/pub/scm/linux/kernel/git/mszeredi/fuse.git for-next

 virtio_fs.c |    2 +-
```
#### [PATCH v2 1/5] VSOCK: support fill mergeable rx buffer in guest
##### From: jiangyiwen <jiangyiwen@huawei.com>

```c
In driver probing, if virtio has VIRTIO_VSOCK_F_MRG_RXBUF feature,
it will fill mergeable rx buffer, support for host send mergeable
rx buffer. It will fill a fixed size(PAGE_SIZE) everytime to
compact with small packet and big packet.

In addition, it also add one optimizations copied from virtio-net.c.
- Skb_page_frag_refill() which can use high order page and
  reduce the stress of page allocator.

Signed-off-by: Yiwen Jiang <jiangyiwen@huawei.com>
---
 include/linux/virtio_vsock.h     |   3 ++
 net/vmw_vsock/virtio_transport.c | 112 +++++++++++++++++++++++++++++++--------
 2 files changed, 92 insertions(+), 23 deletions(-)

```
#### [PATCH v2 1/2] x86/hyper-v: Stop caring about EOI for direct stimers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Turns out we over-engineered Direct Mode for stimers a bit: unlike
traditional stimers where we may want to try to re-inject the message upon
EOI, Direct Mode stimers just set the irq in APIC and kvm_apic_set_irq()
fails only when APIC is disabled (see APIC_DM_FIXED case in
__apic_accept_irq()). Remove the redundant part.

Suggested-by: Roman Kagan <rkagan@virtuozzo.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 36 +++---------------------------------
 1 file changed, 3 insertions(+), 33 deletions(-)

```
