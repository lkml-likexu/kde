#### [GIT PULL] Please pull my kvm-ppc-fixes-5.2-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-5.2-1 tag to get a series of
commits which should go into 5.2 (i.e. via the master branch of the
kvm tree).  They are mostly fixes for the new code which allows guests
to access the XIVE interrupt controller on POWER9 machines directly,
and locking fixes to solve host deadlock issues.

It turns out that the PPC KVM code had been using the kvm->lock mutex
in several places where the vcpu mutex was already held.  Although
this is contrary to what Documentation/virtual/kvm/locking.txt says,
lockdep didn't complain about it in the past because we (apparently)
had no places where a vcpu mutex was taken with kvm->lock held.  Now
there is such a place, in the recently-added XIVE code.  Thus we now
need to fix those other places that take the locks in the wrong order.

Thanks,
Paul.

The following changes since commit cd6c84d8f0cdc911df435bb075ba22ce3c605b07:

  Linux 5.2-rc2 (2019-05-26 16:49:19 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-5.2-1

for you to fetch changes up to d724c9e54939a597592de3659541da11fc7aa112:

  KVM: PPC: Book3S HV: Restore SPRG3 in kvmhv_p9_guest_entry() (2019-05-30 14:00:54 +1000)

----------------------------------------------------------------
PPC KVM fixes for 5.2

- Several bug fixes for the new XIVE-native code.
- Replace kvm->lock by other mutexes in several places where we hold a
  vcpu mutex, to avoid lock order inversions.
- Fix a lockdep warning on guest entry for radix-mode guests.
- Fix a bug causing user-visible corruption of SPRG3 on the host.

----------------------------------------------------------------
Cédric Le Goater (7):
      KVM: PPC: Book3S HV: XIVE: Clear file mapping when device is released
      KVM: PPC: Book3S HV: XIVE: Do not test the EQ flag validity when resetting
      KVM: PPC: Book3S HV: XIVE: Fix the enforced limit on the vCPU identifier
      KVM: PPC: Book3S HV: XIVE: Introduce a new mutex for the XIVE device
      KVM: PPC: Book3S HV: XIVE: Do not clear IRQ data of passthrough interrupts
      KVM: PPC: Book3S HV: XIVE: Take the srcu read lock when accessing memslots
      KVM: PPC: Book3S HV: XIVE: Fix page offset when clearing ESB pages

Paul Mackerras (5):
      KVM: PPC: Book3S HV: Avoid touching arch.mmu_ready in XIVE release functions
      KVM: PPC: Book3S HV: Use new mutex to synchronize MMU setup
      KVM: PPC: Book3S: Use new mutex to synchronize access to rtas token list
      KVM: PPC: Book3S HV: Don't take kvm->lock around kvm_for_each_vcpu
      KVM: PPC: Book3S HV: Fix lockdep warning when entering guest on POWER9

Suraj Jitindar Singh (1):
      KVM: PPC: Book3S HV: Restore SPRG3 in kvmhv_p9_guest_entry()

 arch/powerpc/include/asm/kvm_host.h   |   2 +
 arch/powerpc/kvm/book3s.c             |   1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c   |  36 ++++++------
 arch/powerpc/kvm/book3s_hv.c          |  48 ++++++++++------
 arch/powerpc/kvm/book3s_rtas.c        |  14 ++---
 arch/powerpc/kvm/book3s_xive.c        |  55 +++++++++----------
 arch/powerpc/kvm/book3s_xive.h        |   1 +
 arch/powerpc/kvm/book3s_xive_native.c | 100 +++++++++++++++++++---------------
 8 files changed, 142 insertions(+), 115 deletions(-)
```
#### [PATCH 5.1 005/405] x86/kvm/pmu: Set AMDs virt PMU version to 1
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Borislav Petkov <bp@suse.de>

commit a80c4ec10ed9632c44c829452dc40a0443ff4e85 upstream.

After commit:

  672ff6cff80c ("KVM: x86: Raise #GP when guest vCPU do not support PMU")

my AMD guests started #GPing like this:

  general protection fault: 0000 [#1] PREEMPT SMP
  CPU: 1 PID: 4355 Comm: bash Not tainted 5.1.0-rc6+ #3
  Hardware name: QEMU Standard PC (i440FX + PIIX, 1996), BIOS 1.12.0-1 04/01/2014
  RIP: 0010:x86_perf_event_update+0x3b/0xa0

with Code: pointing to RDPMC. It is RDPMC because the guest has the
hardware watchdog CONFIG_HARDLOCKUP_DETECTOR_PERF enabled which uses
perf. Instrumenting kvm_pmu_rdpmc() some, showed that it fails due to:

  if (!pmu->version)
  	return 1;

which the above commit added. Since AMD's PMU leaves the version at 0,
that causes the #GP injection into the guest.

Set pmu->version arbitrarily to 1 and move it above the non-applicable
struct kvm_pmu members.

Signed-off-by: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Janakarajan Natarajan <Janakarajan.Natarajan@amd.com>
Cc: kvm@vger.kernel.org
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Mihai Carabas <mihai.carabas@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: stable@vger.kernel.org
Fixes: 672ff6cff80c ("KVM: x86: Raise #GP when guest vCPU do not support PMU")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kvm/pmu_amd.c |    2 +-
```
#### [PATCH] KVM: PPC: Book3S HV: Restore SPRG3 in kvmhv_p9_guest_entry()
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
The sprgs are a set of 4 general purpose sprs provided for software use.
SPRG3 is special in that it can also be read from userspace. Thus it is
used on linux to store the cpu and numa id of the process to speed up
syscall access to this information.

This register is overwritten with the guest value on kvm guest entry,
and so needs to be restored on exit again. Thus restore the value on
the guest exit path in kvmhv_p9_guest_entry().

Fixes: 95a6432ce9038 ("KVM: PPC: Book3S HV: Streamlined guest entry/exit path on P9 for radix guests")

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3 1/3] KVM: X86: Yield to IPI target if necessary
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

When sending a call-function IPI-many to vCPUs, yield if any of
the IPI target vCPUs was preempted, we just select the first
preempted target vCPU which we found since the state of target
vCPUs can change underneath and to avoid race conditions.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 Documentation/virtual/kvm/hypercalls.txt | 11 +++++++++++
 arch/x86/include/uapi/asm/kvm_para.h     |  1 +
 arch/x86/kernel/kvm.c                    | 21 +++++++++++++++++++++
 include/uapi/linux/kvm_para.h            |  1 +
 4 files changed, 34 insertions(+)

```
#### [RFC PATCH 01/11] mm: Move MAX_ORDER definition closer to pageblock_order
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

The definition of MAX_ORDER being contained in mmzone.h is problematic when
wanting to just get access to things like pageblock_order since
pageblock_order is defined on some architectures as being based on
MAX_ORDER and it isn't included in pageblock-flags.h.

Move the definition of MAX_ORDER into pageblock-flags.h so that it is
defined in the same header as pageblock_order. By doing this we don't need
to also include mmzone.h. The definition of MAX_ORDER will still be
accessible to any file that includes mmzone.h as it includes
pageblock-flags.h.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mmzone.h          |    8 --------
 include/linux/pageblock-flags.h |    8 ++++++++
 2 files changed, 8 insertions(+), 8 deletions(-)

```
#### [RFC QEMU PATCH] QEMU: Provide a interface for hinting based off of the balloon infrastructure
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

So this is meant to be a simplification of the existing balloon interface
to use for providing hints to what memory needs to be freed. I am assuming
this is safe to do as the deflate logic does not actually appear to do very
much other than tracking what subpages have been released and which ones
haven't.

I suspect this is still a bit crude and will need some more work.
Suggestions welcome.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 hw/virtio/trace-events                          |    1 
 hw/virtio/virtio-balloon.c                      |   85 +++++++++++++++++++++++
 include/hw/virtio/virtio-balloon.h              |    2 -
 include/standard-headers/linux/virtio_balloon.h |    1 
 4 files changed, 88 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] scsi_host: add support for request batching
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This allows a list of requests to be issued, with the LLD only writing
the hardware doorbell when necessary, after the last request was prepared.
This is more efficient if we have lists of requests to issue, particularly
on virtualized hardware, where writing the doorbell is more expensive than
on real hardware.

The use case for this is plugged IO, where blk-mq flushes a batch of
requests all at once.

The API is the same as for blk-mq, just with blk-mq concepts tweaked to
fit the SCSI subsystem API: the "last" flag in blk_mq_queue_data becomes
a flag in scsi_cmnd, while the queue_num in the commit_rqs callback is
extracted from the hctx and passed as a parameter.

The only complication is that blk-mq uses different plugging heuristics
depending on whether commit_rqs is present or not.  So we have two
different sets of blk_mq_ops and pick one depending on whether the
scsi_host template uses commit_rqs or not.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 drivers/scsi/scsi_lib.c  | 37 ++++++++++++++++++++++++++++++++++---
 include/scsi/scsi_cmnd.h |  1 +
 include/scsi/scsi_host.h | 16 ++++++++++++++--
 3 files changed, 49 insertions(+), 5 deletions(-)

```
#### [PATCHv5 1/3] vfio/mdev: Improve the create/remove sequence
##### From: Parav Pandit <parav@mellanox.com>

```c
This patch addresses below two issues and prepares the code to address
3rd issue listed below.

1. mdev device is placed on the mdev bus before it is created in the
vendor driver. Once a device is placed on the mdev bus without creating
its supporting underlying vendor device, mdev driver's probe() gets triggered.
However there isn't a stable mdev available to work on.

   create_store()
     mdev_create_device()
       device_register()
          ...
         vfio_mdev_probe()
        [...]
        parent->ops->create()
          vfio_ap_mdev_create()
            mdev_set_drvdata(mdev, matrix_mdev);
            /* Valid pointer set above */

Due to this way of initialization, mdev driver who wants to use the mdev,
doesn't have a valid mdev to work on.

2. Current creation sequence is,
   parent->ops_create()
   groups_register()

Remove sequence is,
   parent->ops->remove()
   groups_unregister()

However, remove sequence should be exact mirror of creation sequence.
Once this is achieved, all users of the mdev will be terminated first
before removing underlying vendor device.
(Follow standard linux driver model).
At that point vendor's remove() ops shouldn't fail because taking the
device off the bus should terminate any usage.

3. When remove operation fails, mdev sysfs removal attempts to add the
file back on already removed device. Following call trace [1] is observed.

[1] call trace:
kernel: WARNING: CPU: 2 PID: 9348 at fs/sysfs/file.c:327 sysfs_create_file_ns+0x7f/0x90
kernel: CPU: 2 PID: 9348 Comm: bash Kdump: loaded Not tainted 5.1.0-rc6-vdevbus+ #6
kernel: Hardware name: Supermicro SYS-6028U-TR4+/X10DRU-i+, BIOS 2.0b 08/09/2016
kernel: RIP: 0010:sysfs_create_file_ns+0x7f/0x90
kernel: Call Trace:
kernel: remove_store+0xdc/0x100 [mdev]
kernel: kernfs_fop_write+0x113/0x1a0
kernel: vfs_write+0xad/0x1b0
kernel: ksys_write+0x5a/0xe0
kernel: do_syscall_64+0x5a/0x210
kernel: entry_SYSCALL_64_after_hwframe+0x49/0xbe

Therefore, mdev core is improved in following ways.

1. Split the device registration/deregistration sequence so that some
things can be done between initialization of the device and hooking it
up to the bus respectively after deregistering it from the bus but
before giving up our final reference.
In particular, this means invoking the ->create() and ->remove()
callbacks in those new windows. This gives the vendor driver an
initialized mdev device to work with during creation.
At the same time, a bus driver who wish to bind to mdev driver also
gets initialized mdev device.

This follows standard Linux kernel bus and device model.

2. During remove flow, first remove the device from the bus. This
ensures that any bus specific devices are removed.
Once device is taken off the mdev bus, invoke remove() of mdev
from the vendor driver.

3. The driver core device model provides way to register and auto
unregister the device sysfs attribute groups at dev->groups.
Make use of dev->groups to let core create the groups and eliminate
code to avoid explicit groups creation and removal.

To ensure, that new sequence is solid, a below stack dump of a
process is taken who attempts to remove the device while device is in
use by vfio driver and user application.
This stack dump validates that vfio driver guards against such device
removal when device is in use.

 cat /proc/21962/stack
[<0>] vfio_del_group_dev+0x216/0x3c0 [vfio]
[<0>] mdev_remove+0x21/0x40 [mdev]
[<0>] device_release_driver_internal+0xe8/0x1b0
[<0>] bus_remove_device+0xf9/0x170
[<0>] device_del+0x168/0x350
[<0>] mdev_device_remove_common+0x1d/0x50 [mdev]
[<0>] mdev_device_remove+0x8c/0xd0 [mdev]
[<0>] remove_store+0x71/0x90 [mdev]
[<0>] kernfs_fop_write+0x113/0x1a0
[<0>] vfs_write+0xad/0x1b0
[<0>] ksys_write+0x5a/0xe0
[<0>] do_syscall_64+0x5a/0x210
[<0>] entry_SYSCALL_64_after_hwframe+0x49/0xbe
[<0>] 0xffffffffffffffff

This prepares the code to eliminate calling device_create_file() in
subsequent patch.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c    | 94 +++++++++-----------------------
 drivers/vfio/mdev/mdev_private.h |  2 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  2 +-
 3 files changed, 27 insertions(+), 71 deletions(-)

```
