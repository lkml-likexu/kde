#### [PATCH v3 1/5] KVM: LAPIC: Extract adaptive tune timer advancement logic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Extract adaptive tune timer advancement logic to a single function.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 57 ++++++++++++++++++++++++++++++----------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [PATCH] KVM: selftests: Compile code with warnings enabled
##### From: Thomas Huth <thuth@redhat.com>

```c
So far the KVM selftests are compiled without any compiler warnings
enabled. That's quite bad, since we miss a lot of possible bugs this
way. Let's enable at least "-Wall" and some other useful warning flags
now.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 This patch fixes most of the warnings in the x86 code already - but
 for some warnings, I was not quite sure (e.g. about the need for the
 kvm_get_supported_cpuid_entry(1) in some tests), so I did not touch
 that code yet. I also did not check aarch64 yet. I'd be glad if
 someone who knows these parts of the code could have a look at the
 warnings there.

 tools/testing/selftests/kvm/Makefile                        | 4 +++-
 tools/testing/selftests/kvm/dirty_log_test.c                | 6 +++++-
 tools/testing/selftests/kvm/lib/kvm_util.c                  | 3 ---
 tools/testing/selftests/kvm/lib/x86_64/processor.c          | 4 +---
 tools/testing/selftests/kvm/x86_64/cr4_cpuid_sync_test.c    | 1 +
 tools/testing/selftests/kvm/x86_64/platform_info_test.c     | 1 -
 tools/testing/selftests/kvm/x86_64/smm_test.c               | 3 +--
 .../selftests/kvm/x86_64/vmx_close_while_nested_test.c      | 5 +----
 tools/testing/selftests/kvm/x86_64/vmx_tsc_adjust_test.c    | 5 ++---
 9 files changed, 14 insertions(+), 18 deletions(-)

```
#### [RFC PATCH 1/4] KVM: selftests: Guard struct kvm_vcpu_events with __KVM_HAVE_VCPU_EVENTS
##### From: Thomas Huth <thuth@redhat.com>

```c
The struct kvm_vcpu_events code is only available on certain architectures
(arm, arm64 and x86). To be able to compile kvm_util.c also for other
architectures, we've got to fence the code with __KVM_HAVE_VCPU_EVENTS.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 2 ++
 tools/testing/selftests/kvm/lib/kvm_util.c     | 2 ++
 2 files changed, 4 insertions(+)

```
#### [PATCH v1 1/6] x86/fpu: Introduce new fpu state for Intel processor trace
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Introduce new fpu state structure pt_state to save Intel
processor trace configuration. The upcoming using
XSAVES/XRSTORS to switch the Intel PT configuration
on VM-Entry/Exit will use this structure.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/include/asm/fpu/types.h | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
#### [PATCH net 1/4] vhost: introduce vhost_exceeds_weight()
##### From: Jason Wang <jasowang@redhat.com>

```c
We used to have vhost_exceeds_weight() for vhost-net to:

- prevent vhost kthread from hogging the cpu
- balance the time spent between TX and RX

This function could be useful for vsock and scsi as well. So move it
to vhost.c. Device must specify a weight which counts the number of
requests, or it can also specific a byte_weight which counts the
number of bytes that has been processed.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/net.c   | 22 ++++++----------------
 drivers/vhost/scsi.c  |  9 ++++++++-
 drivers/vhost/vhost.c | 20 +++++++++++++++++++-
 drivers/vhost/vhost.h |  5 ++++-
 drivers/vhost/vsock.c | 12 +++++++++++-
 5 files changed, 48 insertions(+), 20 deletions(-)

```
#### [PATCH RESEND] vsock/virtio: Initialize core virtio vsock before registering the driver
##### From: "Jorge E. Moreira" <jemoreira@google.com>

```c
Avoid a race in which static variables in net/vmw_vsock/af_vsock.c are
accessed (while handling interrupts) before they are initialized.

[    4.201410] BUG: unable to handle kernel paging request at ffffffffffffffe8
[    4.207829] IP: vsock_addr_equals_addr+0x3/0x20
[    4.211379] PGD 28210067 P4D 28210067 PUD 28212067 PMD 0
[    4.211379] Oops: 0000 [#1] PREEMPT SMP PTI
[    4.211379] Modules linked in:
[    4.211379] CPU: 1 PID: 30 Comm: kworker/1:1 Not tainted 4.14.106-419297-gd7e28cc1f241 #1
[    4.211379] Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS 1.10.2-1 04/01/2014
[    4.211379] Workqueue: virtio_vsock virtio_transport_rx_work
[    4.211379] task: ffffa3273d175280 task.stack: ffffaea1800e8000
[    4.211379] RIP: 0010:vsock_addr_equals_addr+0x3/0x20
[    4.211379] RSP: 0000:ffffaea1800ebd28 EFLAGS: 00010286
[    4.211379] RAX: 0000000000000002 RBX: 0000000000000000 RCX: ffffffffb94e42f0
[    4.211379] RDX: 0000000000000400 RSI: ffffffffffffffe0 RDI: ffffaea1800ebdd0
[    4.211379] RBP: ffffaea1800ebd58 R08: 0000000000000001 R09: 0000000000000001
[    4.211379] R10: 0000000000000000 R11: ffffffffb89d5d60 R12: ffffaea1800ebdd0
[    4.211379] R13: 00000000828cbfbf R14: 0000000000000000 R15: ffffaea1800ebdc0
[    4.211379] FS:  0000000000000000(0000) GS:ffffa3273fd00000(0000) knlGS:0000000000000000
[    4.211379] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[    4.211379] CR2: ffffffffffffffe8 CR3: 000000002820e001 CR4: 00000000001606e0
[    4.211379] DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
[    4.211379] DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
[    4.211379] Call Trace:
[    4.211379]  ? vsock_find_connected_socket+0x6c/0xe0
[    4.211379]  virtio_transport_recv_pkt+0x15f/0x740
[    4.211379]  ? detach_buf+0x1b5/0x210
[    4.211379]  virtio_transport_rx_work+0xb7/0x140
[    4.211379]  process_one_work+0x1ef/0x480
[    4.211379]  worker_thread+0x312/0x460
[    4.211379]  kthread+0x132/0x140
[    4.211379]  ? process_one_work+0x480/0x480
[    4.211379]  ? kthread_destroy_worker+0xd0/0xd0
[    4.211379]  ret_from_fork+0x35/0x40
[    4.211379] Code: c7 47 08 00 00 00 00 66 c7 07 28 00 c7 47 08 ff ff ff ff c7 47 04 ff ff ff ff c3 0f 1f 00 66 2e 0f 1f 84 00 00 00 00 00 8b 47 08 <3b> 46 08 75 0a 8b 47 04 3b 46 04 0f 94 c0 c3 31 c0 c3 90 66 2e
[    4.211379] RIP: vsock_addr_equals_addr+0x3/0x20 RSP: ffffaea1800ebd28
[    4.211379] CR2: ffffffffffffffe8
[    4.211379] ---[ end trace f31cc4a2e6df3689 ]---
[    4.211379] Kernel panic - not syncing: Fatal exception in interrupt
[    4.211379] Kernel Offset: 0x37000000 from 0xffffffff81000000 (relocation range: 0xffffffff80000000-0xffffffffbfffffff)
[    4.211379] Rebooting in 5 seconds..

Fixes: 22b5c0b63f32 ("vsock/virtio: fix kernel panic after device hot-unplug")
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Cc: Stefano Garzarella <sgarzare@redhat.com>
Cc: "David S. Miller" <davem@davemloft.net>
Cc: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org
Cc: kernel-team@android.com
Cc: stable@vger.kernel.org [4.9+]
Signed-off-by: Jorge E. Moreira <jemoreira@google.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 13 ++++++-------
 1 file changed, 6 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/3] s390/cio: Don't pin vfio pages for empty transfers
##### From: Eric Farman <farman@linux.ibm.com>

```c
The skip flag of a CCW offers the possibility of data not being
transferred, but is only meaningful for certain commands.
Specifically, it is only applicable for a read, read backward, sense,
or sense ID CCW and will be ignored for any other command code
(SA22-7832-11 page 15-64, and figure 15-30 on page 15-75).

(A sense ID is xE4, while a sense is x04 with possible modifiers in the
upper four bits.  So we will cover the whole "family" of sense CCWs.)

For those scenarios, since there is no requirement for the target
address to be valid, we should skip the call to vfio_pin_pages() and
rely on the IDAL address we have allocated/built for the channel
program.  The fact that the individual IDAWs within the IDAL are
invalid is fine, since they aren't actually checked in these cases.

Set pa_nr to zero when skipping the pfn_array_pin() call, since it is
defined as the number of pages pinned and is used to determine
whether to call vfio_unpin_pages() upon cleanup.

As we do this, since the pfn_array_pin() routine returns the number of
pages pinned, and we might not be doing that, the logic for converting
a CCW from direct-addressed to IDAL needs to ensure there is room for
one IDAW in the IDAL being built since a zero-length IDAL isn't great.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 55 ++++++++++++++++++++++++++++++----
 1 file changed, 50 insertions(+), 5 deletions(-)

```
