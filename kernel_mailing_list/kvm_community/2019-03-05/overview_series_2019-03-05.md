#### [PATCH 1/2] KVM: polling: add architecture backend to disable polling
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
There are cases where halt polling is unwanted. For example when running
KVM on an over committed LPAR we rather want to give back the CPU to
neighbour LPARs instead of polling. Let us provide a callback that
allows architectures to disable polling.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 include/linux/kvm_host.h | 10 ++++++++++
 virt/kvm/Kconfig         |  3 +++
 virt/kvm/kvm_main.c      |  2 +-
 3 files changed, 14 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86/apic: wait for wrap around in lapic timer periodic test
##### From: Evgeny Yakovlev <wrfsh@yandex-team.ru>

```c
We are seeing very rare test failures in apic/split-apic with the
following: "FAIL: TMCCT should be reset to the initial-count". We are
running on 4.14 kernels and this problem occurs sporadically although we
didn't try to reproduce it on any other stable kernel branch.

It looks like under KVM lapic timer in periodic mode may return several
consecutive 0 values in apic_get_tmccr when hrtimer async callback is still
restarting the hrtimer and recalculating expiration_time value but
apic_get_tmccr is seeing ktime_now() already ahead of (still old)
expiration_time value. After a couple of 0-es from TMCCR everything
goes back to normal.

This change forces test_apic_change_mode test to wait specifically for
lapic timer wrap around skipping zero TMCCR values in one case when we are
testing for timer in periodic mode to correctly reload TMCCR from TMICR.
If timer mode change is indeed broken and TMCCR is not reset then we
will see apic test timeout.

Signed-off-by: Evgeny Yakovlev <wrfsh@yandex-team.ru>
---
 x86/apic.c | 23 +++++++++++++++++++++--
 1 file changed, 21 insertions(+), 2 deletions(-)

```
#### [PATCH] vsock/virtio: fix kernel panic from virtio_transport_reset_no_sock
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
Previous to commit 22b5c0b63f32 ("vsock/virtio: fix kernel panic after device hot-unplug"),
vsock_core_init() was called from virtio_vsock_probe(). Now,
virtio_transport_reset_no_sock() can be called before vsock_core_init()
has the chance to run.

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
[Wed Feb 27 14:17:09 2019] CR2: 0000000000000110
[Wed Feb 27 14:17:09 2019] ---[ end trace baa35abd2e040fe5 ]---
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
---
 net/vmw_vsock/virtio_transport_common.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
