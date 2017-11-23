#### [PATCH 4.14 073/143] KVM: x86: Update the exit_qualification access bits while walking an address
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
4.14-stable review patch.  If anyone has any objections, please let me know.

------------------

[ Upstream commit ddd6f0e94d3153951580d5b88b9d97c7e26a0e00 ]

... to avoid having a stale value when handling an EPT misconfig for MMIO
regions.

MMIO regions that are not passed-through to the guest are handled through
EPT misconfigs. The first time a certain MMIO page is touched it causes an
EPT violation, then KVM marks the EPT entry to cause an EPT misconfig
instead. Any subsequent accesses to the entry will generate an EPT
misconfig.

Things gets slightly complicated with nested guest handling for MMIO
regions that are not passed through from L0 (i.e. emulated by L0
user-space).

An EPT violation for one of these MMIO regions from L2, exits to L0
hypervisor. L0 would then look at the EPT12 mapping for L1 hypervisor and
realize it is not present (or not sufficient to serve the request). Then L0
injects an EPT violation to L1. L1 would then update its EPT mappings. The
EXIT_QUALIFICATION value for L1 would come from exit_qualification variable
in "struct vcpu". The problem is that this variable is only updated on EPT
violation and not on EPT misconfig. So if an EPT violation because of a
read happened first, then an EPT misconfig because of a write happened
afterwards. The L0 hypervisor will still contain exit_qualification value
from the previous read instead of the write and end up injecting an EPT
violation to the L1 hypervisor with an out of date EXIT_QUALIFICATION.

The EPT violation that is injected from L0 to L1 needs to have the correct
EXIT_QUALIFICATION specially for the access bits because the individual
access bits for MMIO EPTs are updated only on actual access of this
specific type. So for the example above, the L1 hypervisor will keep
updating only the read bit in the EPT then resume the L2 guest. The L2
guest would end up causing another exit where the L0 *again* will inject
another EPT violation to L1 hypervisor with *again* an out of date
exit_qualification which indicates a read and not a write. Then this
ping-pong just keeps happening without making any forward progress.

The behavior of mapping MMIO regions changed in:

   commit a340b3e229b24 ("kvm: Map PFN-type memory regions as writable (if possible)")

... where an EPT violation for a read would also fixup the write bits to
avoid another EPT violation which by acciddent would fix the bug mentioned
above.

This commit fixes this situation and ensures that the access bits for the
exit_qualifcation is up to date. That ensures that even L1 hypervisor
running with a KVM version before the commit mentioned above would still
work.

( The description above assumes EPT to be available and used by L1
  hypervisor + the L1 hypervisor is passing through the MMIO region to the L2
  guest while this MMIO region is emulated by the L0 user-space ).

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: H. Peter Anvin <hpa@zytor.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Signed-off-by: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kvm/paging_tmpl.h | 11 +++++++++--
 1 file changed, 9 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: arm64: Clarify explanation of STAGE2_PGTABLE_LEVELS
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
In attempting to re-construct the logic for our stage 2 page table
layout I found the reaoning in the comment explaining how we calculate
the number of levels used for stage 2 page tables a bit backwards.

This commit attempts to clarify the comment, to make it slightly easier
to read without having the Arm ARM open on the right page.

While we're at it, fixup a typo in a comment that was recently changed.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm64/include/asm/stage2_pgtable.h | 17 ++++++++++-------
 virt/kvm/arm/mmu.c                      |  2 +-
 2 files changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: arm/arm64: Fix unintended stage 2 PMD mappings
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
There are two things we need to take care of when we create block
mappings in the stage 2 page tables:

  (1) The alignment within a PMD between the host address range and the
  guest IPA range must be the same, since otherwise we end up mapping
  pages with the wrong offset.

  (2) The head and tail of a memory slot may not cover a full block
  size, and we have to take care to not map those with block
  descriptors, since we could expose memory to the guest that the host
  did not intend to expose.

So far, we have been taking care of (1), but not (2), and our commentary
describing (1) was somewhat confusing.

This commit attempts to factor out the checks of both into a common
function, and if we don't pass the check, we won't attempt any PMD
mappings for neither hugetlbfs nor THP.

Note that we used to only check the alignment for THP, not for
hugetlbfs, but as far as I can tell the check needs to be applied to
both scenarios.

Cc: Ralph Palutke <ralph.palutke@fau.de>
Cc: Lukas Braun <koomi@moshbit.net>
Reported-by: Lukas Braun <koomi@moshbit.net>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulos@arm.com>
---
 virt/kvm/arm/mmu.c | 79 +++++++++++++++++++++++++++++++++++++---------
 1 file changed, 64 insertions(+), 15 deletions(-)

```
#### [RFC] vhost/vsock: fix use-after-free in network stack callers
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
If the network stack calls .send_pkt()/.cancel_pkt() during .release(),
a struct vhost_vsock use-after-free is possible.  This occurs because
.release() does not wait for other CPUs to stop using struct
vhost_vsock.

Switch to an RCU-enabled hashtable (indexed by guest CID) so that
.release() can wait for other CPUs by calling synchronize_rcu().  This
also eliminates vhost_vsock_lock acquisition in the data path so it
could have a positive effect on performance.

Reported-and-tested-by: syzbot+bd391451452fb0b93039@syzkaller.appspotmail.com
Reported-by: syzbot+e3e074963495f92a89ed@syzkaller.appspotmail.com
Reported-by: syzbot+d5a0a170c5069658b141@syzkaller.appspotmail.com
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
Hi Jason,
Thanks for encouraging me to try the RCU hashtable approach.  This patch
passes syzbot but I'm going to do some manual testing now.  Thoughts?

 drivers/vhost/vsock.c | 57 +++++++++++++++++++++++++------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: svm: Add debug registers intercepts testThread-Topic: [kvm-unit-tests PATCH] x86: svm: Add debug registers intercepts
##### From: "Tambe, William" <William.Tambe@amd.com>

```c
Test debug registers read and write intercepts.

Signed-off-by: William Tambe <william.tambe@amd.com>
---
 x86/svm.c | 118 ++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 118 insertions(+)

```
#### [PATCH kvmtool] virtio: Fix ordering of virt_queue__available()
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
After adding buffers to the virtio queue, the guest increments the avail
index. It then reads the event index to check if it needs to notify the
guest. If the event index corresponds to the previous avail value, then
the guest notifies the host. Otherwise it means that the guest is still
processing the queue and hasn't had a chance to increment the event
index yet. Once it gets there, the host will see the new avail index and
process the descriptors, so there is no need for a notification.

This is only guaranteed to work if both threads write and read the
indices in the right order. Currently a barrier is missing from
virt_queue__available(), and the host may not see an up-to-date value of
event index after writing avail.

             HOST            |           GUEST
                             |
                             |    write avail = 1
                             |    mb()
                             |    read event -> 0
        write event = 0      |      == prev_avail -> notify
        read avail -> 1      |
                             |
        write event = 1      |
        read avail -> 1      |
        wait()               |    write avail = 2
                             |    mb()
                             |    read event -> 0
                             |      != prev_avail -> no notification

By adding a memory barrier on the host side, we ensure that it doesn't
miss any notification.

Reviewed-By: Steven Price <steven.price@arm.com>
Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 include/kvm/virtio.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v2 kvmtool] virtio: Fix ordering of virt_queue__available()
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
After adding buffers to the virtio queue, the guest increments the avail
index. It then reads the event index to check if it needs to notify the
host. If the event index corresponds to the previous avail value, then
the guest notifies the host. Otherwise it means that the host is still
processing the queue and hasn't had a chance to increment the event
index yet. Once it gets there, the host will see the new avail index and
process the descriptors, so there is no need for a notification.

This is only guaranteed to work if both threads write and read the
indices in the right order. Currently a barrier is missing from
virt_queue__available(), and the host may not see an up-to-date value of
event index after writing avail.

             HOST            |           GUEST
                             |
                             |    write avail = 1
                             |    mb()
                             |    read event -> 0
        write event = 0      |      == prev_avail -> notify
        read avail -> 1      |
                             |
        write event = 1      |
        read avail -> 1      |
        wait()               |    write avail = 2
                             |    mb()
                             |    read event -> 0
                             |      != prev_avail -> no notification

By adding a memory barrier on the host side, we ensure that it doesn't
miss any notification.

Reviewed-By: Steven Price <steven.price@arm.com>
Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
v2: fix wording s/guest/host/
---
 include/kvm/virtio.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v3]  x86/kvmclock : convert to SPDX identifiers
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
Update the verbose license text with the matching SPDX 
license identifier.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kernel/kvmclock.c | 15 +--------------
 1 files changed, 1 insertions(+), 14 deletions(-)

```
#### [PATCH 1/1] Add vhost_blk driver
##### From: Vitaly Mayatskikh <v.mayatskih@gmail.com>

```c
This driver accelerates host side of virtio-blk.

Signed-off-by: Vitaly Mayatskikh <v.mayatskih@gmail.com>
---
 drivers/vhost/Kconfig  |  13 ++
 drivers/vhost/Makefile |   3 +
 drivers/vhost/blk.c    | 510 +++++++++++++++++++++++++++++++++++++++++
 3 files changed, 526 insertions(+)
 create mode 100644 drivers/vhost/blk.c

```
#### [PATCH 1/1] vhost: add per-vq worker thread
##### From: Vitaly Mayatskikh <v.mayatskih@gmail.com>

```c
This enables a near linear scaling in multiqueue cases.

First virtqueue still gets the worker created unconditionally,
the rest is postponed until the actual poll starts on the queue.

Signed-off-by: Vitaly Mayatskikh <v.mayatskih@gmail.com>
---
 drivers/vhost/vhost.c | 123 +++++++++++++++++++++++++++++++-----------
 drivers/vhost/vhost.h |  11 +++-
 2 files changed, 100 insertions(+), 34 deletions(-)

```
#### [kvm-unit-tests PATCH v1 1/2] x86: svm: Fix incorrect ordering within struct regs
##### From: "Tambe, William" <William.Tambe@amd.com>

```c
"struct regs" is used within x86/svm.c to describe
the memory region where SAVE_GPR_C saves registers.

The ordering within "struct regs" must be corrected
so that it matches how SAVE_GPR_C stores registers.

Signed-off-by: William Tambe <william.tambe@amd.com>
---
 x86/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
