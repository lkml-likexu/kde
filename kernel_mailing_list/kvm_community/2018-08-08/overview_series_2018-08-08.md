#### [PATCH 1/4] KVM: arm64: Remove non-existent AArch32 ICC_SGI1R encoding
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
ICC_SGI1R is a 64bit system register, even on AArch32. It is thus
pointless to have such an encoding in the 32bit cp15 array. Let's
drop it.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm64/kvm/sys_regs.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v4 01/12] KVM: hyperv: define VP assist page helpers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Ladi Prosek <lprosek@redhat.com>

The state related to the VP assist page is still managed by the LAPIC
code in the pv_eoi field.

Signed-off-by: Ladi Prosek <lprosek@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/hyperv.c | 23 +++++++++++++++++++++--
 arch/x86/kvm/hyperv.h |  4 ++++
 arch/x86/kvm/lapic.c  |  4 ++--
 arch/x86/kvm/lapic.h  |  2 +-
 arch/x86/kvm/x86.c    |  2 +-
 5 files changed, 29 insertions(+), 6 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Hi all,

Paolo pointed out a semantic conflict between the kvm tree and the tip
tree in

  arch/x86/kernel/kvm.c

between commit:

  368a540e0232 ("x86/kvmclock: Remove memblock dependency")

from the tip tree and commit:

  d63bae079b64 ("KVM: X86: Add kvm hypervisor init time platform setup callback")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

I applied the following (as suggested) after the automatic merge:

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Wed, 8 Aug 2018 13:48:34 +1000
Subject: [PATCH] kvm: x86: fix semantic conflict in platform init

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kernel/kvm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH net] vhost: reset metadata cache when initializing new IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
We need to reset metadata cache during new IOTLB initialization,
otherwise the stale pointers to previous IOTLB may be still accessed
which will lead a use after free.

Reported-by: syzbot+c51e6736a1bf614b3272@syzkaller.appspotmail.com
Fixes: f88949138058 ("vhost: introduce O(1) vq metadata cache")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH v8 01/22] s390/zcrypt: Add ZAPQ inline function.
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

```c
From: Harald Freudenberger <freude@de.ibm.com>

Added new inline function ap_pqap_zapq()
which is a C inline function wrapper for
the AP PQAP(ZAPQ) instruction.

Signed-off-by: Harald Freudenberger <freude@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/ap_asm.h |   19 +++++++++++++++++++
 1 files changed, 19 insertions(+), 0 deletions(-)

```
