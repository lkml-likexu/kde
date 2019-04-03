#### [PATCH 01/27] x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a preparation for the removal of the ->initialized member in the
fpu struct.
__fpu__restore_sig() is deactivating the FPU via fpu__drop() and then
setting manually ->initialized followed by fpu__restore(). The result is
that it is possible to manipulate fpu->state and the state of registers
won't be saved/restored on a context switch which would overwrite
fpu->state.

Don't access the fpu->state while the content is read from user space
and examined / sanitized. Use a temporary kmalloc() buffer for the
preparation of the FPU registers and once the state is considered okay,
load it. Should something go wrong, return with an error and without
altering the original FPU registers.

The removal of "fpu__initialize()" is a nop because fpu->initialized is
already set for the user task.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/fpu/signal.h |  2 +-
 arch/x86/kernel/fpu/regset.c      |  5 ++--
 arch/x86/kernel/fpu/signal.c      | 40 ++++++++++++-------------------
 3 files changed, 18 insertions(+), 29 deletions(-)

```
#### [PATCH 1/4 v3][KVM nVMX]: Check "load IA32_PAT" VM-exit control on vmentry
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on Host Control Registers and MSRs" in Intel
SDM vol 3C, the following check is performed on vmentry:

    If the "load IA32_PAT" VM-exit control is 1, the value of the field
    for the IA32_PAT MSR must be one that could be written by WRMSR
    without fault at CPL 0. Specifically, each of the 8 bytes in the
    field must have one of the values 0 (UC), 1 (WC), 4 (WT), 5 (WP),
    6 (WB), or 7 (UC-).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH] KVM: x86: svm: make sure NMI is injected after nmi_singlestep
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
I noticed that apic test from kvm-unit-tests always hangs on my EPYC 7401P,
the hanging test nmi-after-sti is trying to deliver 30000 NMIs and tracing
shows that we're sometimes able to deliver a few but never all.

When we're trying to inject an NMI we may fail to do so immediately for
various reasons, however, we still need to inject it so enable_nmi_window()
arms nmi_singlestep mode. #DB occurs as expected, but we're not checking
for pending NMIs before entering the guest and unless there's a different
event to process, the NMI will never get delivered.

Make KVM_REQ_EVENT request on the vCPU from db_interception() to make sure
pending NMIs are checked and possibly injected.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- I have to admit my RFC didn't gain much popularity, re-sending as
 non-RFC.
---
 arch/x86/kvm/svm.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 1/1] vfio: Fix WARNING "do not call blocking ops when !TASK_RUNNING"
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
vfio_dev_present() which is the condition to
wait_event_interruptible_timeout(), will call vfio_group_get_device
and try to acquire the mutex group->device_lock.

wait_event_interruptible_timeout() will set the state of the current
task to TASK_INTERRUPTIBLE, before doing the condition check. This
means that we will try to accquire the mutex while already in a
sleeping state. The scheduler warns us by giving the following
warning:

[ 4050.264464] ------------[ cut here ]------------
[ 4050.264508] do not call blocking ops when !TASK_RUNNING; state=1 set at [<00000000b33c00e2>] prepare_to_wait_event+0x14a/0x188
[ 4050.264529] WARNING: CPU: 12 PID: 35924 at kernel/sched/core.c:6112 __might_sleep+0x76/0x90
....

 4050.264756] Call Trace:
[ 4050.264765] ([<000000000017bbaa>] __might_sleep+0x72/0x90)
[ 4050.264774]  [<0000000000b97edc>] __mutex_lock+0x44/0x8c0
[ 4050.264782]  [<0000000000b9878a>] mutex_lock_nested+0x32/0x40
[ 4050.264793]  [<000003ff800d7abe>] vfio_group_get_device+0x36/0xa8 [vfio]
[ 4050.264803]  [<000003ff800d87c0>] vfio_del_group_dev+0x238/0x378 [vfio]
[ 4050.264813]  [<000003ff8015f67c>] mdev_remove+0x3c/0x68 [mdev]
[ 4050.264825]  [<00000000008e01b0>] device_release_driver_internal+0x168/0x268
[ 4050.264834]  [<00000000008de692>] bus_remove_device+0x162/0x190
[ 4050.264843]  [<00000000008daf42>] device_del+0x1e2/0x368
[ 4050.264851]  [<00000000008db12c>] device_unregister+0x64/0x88
[ 4050.264862]  [<000003ff8015ed84>] mdev_device_remove+0xec/0x130 [mdev]
[ 4050.264872]  [<000003ff8015f074>] remove_store+0x6c/0xa8 [mdev]
[ 4050.264881]  [<000000000046f494>] kernfs_fop_write+0x14c/0x1f8
[ 4050.264890]  [<00000000003c1530>] __vfs_write+0x38/0x1a8
[ 4050.264899]  [<00000000003c187c>] vfs_write+0xb4/0x198
[ 4050.264908]  [<00000000003c1af2>] ksys_write+0x5a/0xb0
[ 4050.264916]  [<0000000000b9e270>] system_call+0xdc/0x2d8
[ 4050.264925] 4 locks held by sh/35924:
[ 4050.264933]  #0: 000000001ef90325 (sb_writers#4){.+.+}, at: vfs_write+0x9e/0x198
[ 4050.264948]  #1: 000000005c1ab0b3 (&of->mutex){+.+.}, at: kernfs_fop_write+0x1cc/0x1f8
[ 4050.264963]  #2: 0000000034831ab8 (kn->count#297){++++}, at: kernfs_remove_self+0x12e/0x150
[ 4050.264979]  #3: 00000000e152484f (&dev->mutex){....}, at: device_release_driver_internal+0x5c/0x268
[ 4050.264993] Last Breaking-Event-Address:
[ 4050.265002]  [<000000000017bbaa>] __might_sleep+0x72/0x90
[ 4050.265010] irq event stamp: 7039
[ 4050.265020] hardirqs last  enabled at (7047): [<00000000001cee7a>] console_unlock+0x6d2/0x740
[ 4050.265029] hardirqs last disabled at (7054): [<00000000001ce87e>] console_unlock+0xd6/0x740
[ 4050.265040] softirqs last  enabled at (6416): [<0000000000b8fe26>] __udelay+0xb6/0x100
[ 4050.265049] softirqs last disabled at (6415): [<0000000000b8fe06>] __udelay+0x96/0x100
[ 4050.265057] ---[ end trace d04a07d39d99a9f9 ]---

Let's fix this as described in the article https://lwn.net/Articles/628628/.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---

I have already tested in my environment and the warning goes 
away for me with this patch. But appreciate further testing
and review feedback on the patch.

Thanks
Farhan


ChangeLog
---------
v1 -> v2
   - Keep the same behavior as before, so the task goes into
     TASK_UNINTERRUPTIBLE state after being interrupted once

---

 drivers/vfio/vfio.c | 20 +++++++++++++-------
 1 file changed, 13 insertions(+), 7 deletions(-)

```
#### [PATCH v4 1/5] ibnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

This also handles asynchronous flush requests from the block layer
by creating a child bio and chaining it with parent bio.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 14 ++++++++-----
 drivers/nvdimm/region_devs.c | 38 ++++++++++++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  8 +++++++-
 6 files changed, 59 insertions(+), 12 deletions(-)

```
#### [PATCH v6 01/20] x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c
cpu_caps_cleared and cpu_caps_set may not be aligned to unsigned long.
Atomic operations (i.e. set_bit and clear_bit) on the bitmaps may access
two cache lines (a.k.a. split lock) and lock the bus to block all memory
accesses from other processors to ensure atomicity.

To avoid the overall performance degradation from the bus locking, align
the two variables to unsigned long.

Defining the variables as unsigned long may also fix the issue because
they are naturally aligned to unsigned long. But that needs additional
code changes. Adding __aligned(unsigned long) is a simpler fix.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
---
 arch/x86/kernel/cpu/common.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
