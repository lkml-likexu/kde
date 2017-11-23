#### [PATCH 1/2] [KVM] nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C,
the following check needs to be enforced on vmentry of L2 guests:

   - Bits 5:0 of the posted-interrupt descriptor address are all 0.
   - The posted-interrupt descriptor address does not set any bits
     beyond the processor's physical-address width.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH V3 1/2] kvm/x86 : add coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 include/uapi/linux/kvm.h  | 5 +++--
 virt/kvm/coalesced_mmio.c | 8 +++++---
 virt/kvm/kvm_main.c       | 2 ++
 3 files changed, 10 insertions(+), 5 deletions(-)

```
#### [PATCH net] vhost: correctly check the iova range when waking virtqueue
##### From: Jason Wang <jasowang@redhat.com>

```c
We don't wakeup the virtqueue if the first byte of pending iova range
is the last byte of the range we just got updated. This will lead a
virtqueue to wait for IOTLB updating forever. Fixing by correct the
check and wake up the virtqueue in this case.

Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Reported-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Tested-by: Peter Xu <peterx@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
The patch is needed for -stable.
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v1 1/4] s390x: user ctl_set/clear_bit for low address protection
##### From: David Hildenbrand <david@redhat.com>

```c
User the provided helper functions now.

Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h | 12 ++----------
 1 file changed, 2 insertions(+), 10 deletions(-)

```
#### [PATCH v1 1/7] tools/kvm_stat: fix python3 issues
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From: Stefan Raspl <stefan.raspl@de.ibm.com>

Python3 returns a float for a regular division - switch to a division
operator that returns an integer.
Furthermore, filters return a generator object instead of the actual
list - wrap result in yet another list, which makes it still work in
both, Python2 and 3.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
