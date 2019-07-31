#### [PATCH v5 12/29] compat_ioctl: move drivers to compat_ptr_ioctl
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Each of these drivers has a copy of the same trivial helper function to
convert the pointer argument and then call the native ioctl handler.

We now have a generic implementation of that, so use it.

Acked-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Reviewed-by: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Reviewed-by: Jason Gunthorpe <jgg@mellanox.com>
Reviewed-by: Jiri Kosina <jkosina@suse.cz>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Acked-by: David S. Miller <davem@davemloft.net>
---
 drivers/char/ppdev.c              | 12 +---------
 drivers/char/tpm/tpm_vtpm_proxy.c | 12 +---------
 drivers/firewire/core-cdev.c      | 12 +---------
 drivers/hid/usbhid/hiddev.c       | 11 +--------
 drivers/hwtracing/stm/core.c      | 12 +---------
 drivers/misc/mei/main.c           | 22 +----------------
 drivers/mtd/ubi/cdev.c            | 36 +++-------------------------
 drivers/net/tap.c                 | 12 +---------
 drivers/staging/pi433/pi433_if.c  | 12 +---------
 drivers/usb/core/devio.c          | 16 +------------
 drivers/vfio/vfio.c               | 39 +++----------------------------
 drivers/vhost/net.c               | 12 +---------
 drivers/vhost/scsi.c              | 12 +---------
 drivers/vhost/test.c              | 12 +---------
 drivers/vhost/vsock.c             | 12 +---------
 fs/ceph/dir.c                     |  2 +-
 fs/ceph/file.c                    |  2 +-
 fs/ceph/super.h                   |  9 -------
 fs/fat/file.c                     | 13 +----------
 19 files changed, 22 insertions(+), 248 deletions(-)

```
#### [PATCH] KVM: Disable wake-affine vCPU process to mitigate lock holder preemption
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Wake-affine is a feature inside scheduler which we attempt to make processes 
running closely, it gains benefit mostly from cache-hit. When waker tries 
to wakup wakee, it needs to select cpu to run wakee, wake affine heuristic 
mays select the cpu which waker is running on currently instead of the prev 
cpu which wakee was last time running. 

However, in multiple VMs over-subscribe virtualization scenario, it increases 
the probability to incur vCPU stacking which means that the sibling vCPUs from 
the same VM will be stacked on one pCPU. I test three 80 vCPUs VMs running on 
one 80 pCPUs Skylake server(PLE is supported), the ebizzy score can increase 17% 
after disabling wake-affine for vCPU process. 

When qemu/other vCPU inject virtual interrupt to guest through waking up one 
sleeping vCPU, it increases the probability to stack vCPUs/qemu by scheduler
wake-affine. vCPU stacking issue can greately inceases the lock synchronization 
latency in a virtualized environment. This patch disables wake-affine vCPU 
process to mitigtate lock holder preemption.

Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 include/linux/sched.h | 1 +
 kernel/sched/fair.c   | 3 +++
 virt/kvm/kvm_main.c   | 1 +
 3 files changed, 5 insertions(+)

```
#### [PATCH 1/2] KVM: selftests: Implement ucall() for s390x
##### From: Thomas Huth <thuth@redhat.com>

```c
On s390x, we can neither exit via PIO nor MMIO, but have to use
an instruction like DIAGNOSE. While we're at it, rename UCALL_PIO
to UCALL_DEFAULT, since PIO only works on x86 anyway, and this
way we can re-use the "default" type for the DIAGNOSE exit on s390x.

Now that ucall() is implemented, we can use it in the sync_reg_test
on s390x, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +-
 tools/testing/selftests/kvm/lib/ucall.c       | 34 +++++++++++++++----
 .../selftests/kvm/s390x/sync_regs_test.c      |  6 ++--
 3 files changed, 32 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH] Force GCC version to 8.2 for compiling the ARM tests
##### From: Thomas Huth <thuth@redhat.com>

```c
The kvm-unit-tests are currently completely failing with GCC 9.1.
So let's use GCC 8.2 again for compiling the ARM tests to fix
the CI pipelines on gitlab.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/2] kvm-unit-test: x86: Implement a generic wrapper for cpuid/cpuid_indexed functions
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 lib/x86/processor.h | 143 ++++++++++++++++++++++++++++++++++----------
 1 file changed, 111 insertions(+), 32 deletions(-)

```
#### [PATCH 1/3] test-throttle: Fix uninitialized use of burst_length
##### From: Andrey Shinkevich <andrey.shinkevich@virtuozzo.com>

```c
ThrottleState::cfg of the static variable 'ts' is reassigned with the
local one in the do_test_accounting() and then is passed to the
throttle_account() with uninitialized member LeakyBucket::burst_length.

Signed-off-by: Andrey Shinkevich <andrey.shinkevich@virtuozzo.com>
---
 tests/test-throttle.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v2] KVM: X86: Use IPI shorthands in kvm guest when support
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

IPI shorthand is supported now by linux apic/x2apic driver, switch to 
IPI shorthand for all excluding self and all including self destination 
shorthand in kvm guest, to avoid splitting the target mask into several 
PV IPI hypercalls. This patch removes the kvm_send_ipi_all() and 
kvm_send_ipi_allbutself() since the callers in APIC codes have already 
taken care of apic_use_ipi_shorthand and fallback to ->send_IPI_mask
and ->send_IPI_mask_allbutself if it is false.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Nadav Amit <namit@vmware.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note: rebase against tip tree's x86/apic branch
v1 -> v2:
 * remove kvm_send_ipi_all() and kvm_send_ipi_allbutself()

 arch/x86/kernel/kvm.c | 12 ------------
 1 file changed, 12 deletions(-)

```
#### [PATCH net-next v5 1/5] vsock/virtio: limit the memory used per-socket
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Since virtio-vsock was introduced, the buffers filled by the host
and pushed to the guest using the vring, are directly queued in
a per-socket list. These buffers are preallocated by the guest
with a fixed size (4 KB).

The maximum amount of memory used by each socket should be
controlled by the credit mechanism.
The default credit available per-socket is 256 KB, but if we use
only 1 byte per packet, the guest can queue up to 262144 of 4 KB
buffers, using up to 1 GB of memory per-socket. In addition, the
guest will continue to fill the vring with new 4 KB free buffers
to avoid starvation of other sockets.

This patch mitigates this issue copying the payload of small
packets (< 128 bytes) into the buffer of last packet queued, in
order to avoid wasting memory.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vsock.c                   |  2 +
 include/linux/virtio_vsock.h            |  1 +
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 60 +++++++++++++++++++++----
 4 files changed, 55 insertions(+), 9 deletions(-)

```
