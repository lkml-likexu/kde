#### [PATCH 1/2] KVM: Implement kvm_copy_guest() to perform copy of guest memory in place
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Implement the function kvm_copy_guest() to be used to perform a memory
copy from one guest physical address to another of a variable length.

This performs similar functionality as the kvm_read_guest() and
kvm_write_guest() functions, except both addresses point to guest memory.
This performs a copy in place using raw_copy_in_user() to avoid having to
buffer the data.

The guest memory can reside in different memslots and the copy length
can span memslots.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

I suspect additional checking may be required around the raw_copy_in_user()
call.

---
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 69 ++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 70 insertions(+)

```
#### [PATCH] KVM: arm: VGIC: properly initialise private IRQ affinity
##### From: Andre Przywara <andre.przywara@arm.com>

```c
At the moment we initialise the target *mask* of a virtual IRQ to the
VCPU it belongs to, even though this mask is only defined for GICv2 and
quickly runs out of bits for many GICv3 guests.
This behaviour triggers an UBSAN complaint for more than 32 VCPUs:
------
[ 5659.462377] UBSAN: Undefined behaviour in virt/kvm/arm/vgic/vgic-init.c:223:21
[ 5659.471689] shift exponent 32 is too large for 32-bit type 'unsigned int'
------
Also for GICv3 guests the reporting of TARGET in the "vgic-state" debugfs
dump is wrong, due to this very same problem.

Fix both issues by only initialising vgic_irq->targets for a vGICv2 guest,
and by initialising vgic_irq->mpdir for vGICv3 guests instead. We can't
use the actual MPIDR for that, as the VCPU's system register is not
initialised at this point yet. This is not really an issue, as ->mpidr
is just used for the debugfs output and the IROUTER MMIO register, which
does not exist in redistributors (dealing with SGIs and PPIs).

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reported-by: Dave Martin <dave.martin@arm.com>
---
 virt/kvm/arm/vgic/vgic-init.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [RFC][Patch v9 1/6] KVM: Guest free page hinting support
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch adds the following:
1. Functional skeleton for the guest implementation. It enables the
guest to maintain the PFN of head buddy free pages of order
FREE_PAGE_HINTING_MIN_ORDER (currently defined as MAX_ORDER - 1)
in a per-cpu array.
Guest uses guest_free_page_enqueue() to enqueue the free pages post buddy
merging to the above mentioned per-cpu array.
guest_free_page_try_hinting() is used to initiate hinting operation once
the collected entries of the per-cpu array reaches or exceeds
HINTING_THRESHOLD (128). Having larger array size(MAX_FGPT_ENTRIES = 256)
than HINTING_THRESHOLD allows us to capture more pages specifically when
guest_free_page_enqueue() is called from free_pcppages_bulk().
For now guest_free_page_hinting() just resets the array index to continue
capturing of the freed pages.
2. Enables the support for x86 architecture.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/Kbuild              |  2 +-
 arch/x86/kvm/Kconfig         |  8 +++
 arch/x86/kvm/Makefile        |  2 +
 include/linux/page_hinting.h | 15 ++++++
 mm/page_alloc.c              |  5 ++
 virt/kvm/page_hinting.c      | 98 ++++++++++++++++++++++++++++++++++++
 6 files changed, 129 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/page_hinting.h
 create mode 100644 virt/kvm/page_hinting.c

```
#### [RFC][QEMU Patch] KVM: Enable QEMU to free the pages hinted by the guest
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch enables QEMU to perform MADVISE_DONTNEED on the pages
reported by the guest.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 hw/virtio/trace-events                        |  1 +
 hw/virtio/virtio-balloon.c                    | 90 +++++++++++++++++++
 include/hw/virtio/virtio-balloon.h            |  2 +-
 .../standard-headers/linux/virtio_balloon.h   |  1 +
 4 files changed, 93 insertions(+), 1 deletion(-)

```
#### [PATCH 2/2] KVM: PPC: Book3S HV: Implement virtual mode H_PAGE_INIT handler
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Implement a virtual mode handler for the H_CALL H_PAGE_INIT which can be
used to zero or copy a guest page. The page is defined to be 4k and must
be 4k aligned.

The in-kernel handler halves the time to handle this H_CALL compared to
handling it in userspace.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

```
#### [PATCH v2] vsock/virtio: fix kernel panic from virtio_transport_reset_no_sock
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Previous to commit 22b5c0b63f32 ("vsock/virtio: fix kernel panic
after device hot-unplug"), vsock_core_init() was called from
virtio_vsock_probe(). Now, virtio_transport_reset_no_sock() can be called
before vsock_core_init() has the chance to run.

[Wed Feb 27 14:17:09 2019] BUG: unable to handle kernel NULL pointer dereference at 0000000000000110
[Wed Feb 27 14:17:09 2019] #PF error: [normal kernel read fault]
[Wed Feb 27 14:17:09 2019] PGD 0 P4D 0
[Wed Feb 27 14:17:09 2019] Oops: 0000 [#1] SMP PTI
[Wed Feb 27 14:17:09 2019] CPU: 3 PID: 59 Comm: kworker/3:1 Not tainted 5.0.0-rc7-390-generic-hvi #390
[Wed Feb 27 14:17:09 2019] Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS Ubuntu-1.8.2-1ubuntu1 04/01/2014
[Wed Feb 27 14:17:09 2019] Workqueue: virtio_vsock virtio_transport_rx_work [vmw_vsock_virtio_transport]
[Wed Feb 27 14:17:09 2019] RIP: 0010:virtio_transport_reset_no_sock+0x8c/0xc0 [vmw_vsock_virtio_transport_common]
[Wed Feb 27 14:17:09 2019] Code: 35 8b 4f 14 48 8b 57 08 31 f6 44 8b 4f 10 44 8b 07 48 8d 7d c8 e8 84 f8 ff ff 48 85 c0 48 89 c3 74 2a e8 f7 31 03 00 48 89 df <48> 8b 80 10 01 00 00 e8 68 fb 69 ed 48 8b 75 f0 65 48 33 34 25 28
[Wed Feb 27 14:17:09 2019] RSP: 0018:ffffb42701ab7d40 EFLAGS: 00010282
[Wed Feb 27 14:17:09 2019] RAX: 0000000000000000 RBX: ffff9d79637ee080 RCX: 0000000000000003
[Wed Feb 27 14:17:09 2019] RDX: 0000000000000001 RSI: 0000000000000002 RDI: ffff9d79637ee080
[Wed Feb 27 14:17:09 2019] RBP: ffffb42701ab7d78 R08: ffff9d796fae70e0 R09: ffff9d796f403500
[Wed Feb 27 14:17:09 2019] R10: ffffb42701ab7d90 R11: 0000000000000000 R12: ffff9d7969d09240
[Wed Feb 27 14:17:09 2019] R13: ffff9d79624e6840 R14: ffff9d7969d09318 R15: ffff9d796d48ff80
[Wed Feb 27 14:17:09 2019] FS:  0000000000000000(0000) GS:ffff9d796fac0000(0000) knlGS:0000000000000000
[Wed Feb 27 14:17:09 2019] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[Wed Feb 27 14:17:09 2019] CR2: 0000000000000110 CR3: 0000000427f22000 CR4: 00000000000006e0
[Wed Feb 27 14:17:09 2019] DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
[Wed Feb 27 14:17:09 2019] DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
[Wed Feb 27 14:17:09 2019] Call Trace:
[Wed Feb 27 14:17:09 2019]  virtio_transport_recv_pkt+0x63/0x820 [vmw_vsock_virtio_transport_common]
[Wed Feb 27 14:17:09 2019]  ? kfree+0x17e/0x190
[Wed Feb 27 14:17:09 2019]  ? detach_buf_split+0x145/0x160
[Wed Feb 27 14:17:09 2019]  ? __switch_to_asm+0x40/0x70
[Wed Feb 27 14:17:09 2019]  virtio_transport_rx_work+0xa0/0x106 [vmw_vsock_virtio_transport]
[Wed Feb 27 14:17:09 2019] NET: Registered protocol family 40
[Wed Feb 27 14:17:09 2019]  process_one_work+0x167/0x410
[Wed Feb 27 14:17:09 2019]  worker_thread+0x4d/0x460
[Wed Feb 27 14:17:09 2019]  kthread+0x105/0x140
[Wed Feb 27 14:17:09 2019]  ? rescuer_thread+0x360/0x360
[Wed Feb 27 14:17:09 2019]  ? kthread_destroy_worker+0x50/0x50
[Wed Feb 27 14:17:09 2019]  ret_from_fork+0x35/0x40
[Wed Feb 27 14:17:09 2019] Modules linked in: vmw_vsock_virtio_transport vmw_vsock_virtio_transport_common input_leds vsock serio_raw i2c_piix4 mac_hid qemu_fw_cfg autofs4 cirrus ttm drm_kms_helper syscopyarea sysfillrect sysimgblt fb_sys_fops virtio_net psmouse drm net_failover pata_acpi virtio_blk failover floppy

Fixes: 22b5c0b63f32 ("vsock/virtio: fix kernel panic after device hot-unplug")
Reported-by: Alexandru Herghelegiu <aherghelegiu@bitdefender.com>
Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
Co-developed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 22 +++++++++++++++-------
 1 file changed, 15 insertions(+), 7 deletions(-)

```
#### [RFC PATCH V2 1/5] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain
accessors. About 2% improvement of PPS were seen during vitio-user
txonly test.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
#### [PATCH] vhost: silence an unused-variable warning
##### From: Arnd Bergmann <arnd@arndb.de>

```c
On some architectures, the MMU can be disabled, leading to access_ok()
becoming an empty macro that does not evaluate its size argument,
which in turn produces an unused-variable warning:

drivers/vhost/vhost.c:1191:9: error: unused variable 's' [-Werror,-Wunused-variable]
        size_t s = vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX) ? 2 : 0;

Mark the variable as __maybe_unused to shut up that warning.

Signed-off-by: Arnd Bergmann <arnd@arndb.de>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
