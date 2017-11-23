#### [PATCH v2 1/4] balloon: Allow nested inhibitsFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
A simple true/false internal state does not allow multiple users.  Fix
this within the existing interface by converting to a counter, so long
as the counter is elevated, ballooning is inhibited.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 balloon.c |   13 ++++++++++---
 1 file changed, 10 insertions(+), 3 deletions(-)

```
#### [PATCH 2/2] x86/kvmclock: Mark kvm_get_preset_lpj() as __init
##### From: Dou Liyang <douly.fnst@cn.fujitsu.com>

```c
kvm_get_preset_lpj() just be called at kvmclock_init(), So mark it
 __init as well.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Dou Liyang <douly.fnst@cn.fujitsu.com>
Reviewed-by: Pavel Tatashin <pasha.tatashin@oracle.com>
---
 arch/x86/kernel/kvmclock.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [tip:x86/timers] x86/kvmclock: Mark kvm_get_preset_lpj() as __initGit-Commit-ID: 1088c6eef261939bda8346ec35b513790a2111d5
##### From: tip-bot for Dou Liyang <tipbot@zytor.com>

```c
Commit-ID:  1088c6eef261939bda8346ec35b513790a2111d5
Gitweb:     https://git.kernel.org/tip/1088c6eef261939bda8346ec35b513790a2111d5
Author:     Dou Liyang <douly.fnst@cn.fujitsu.com>
AuthorDate: Mon, 30 Jul 2018 15:54:21 +0800
Committer:  Thomas Gleixner <tglx@linutronix.de>
CommitDate: Mon, 30 Jul 2018 19:33:35 +0200

x86/kvmclock: Mark kvm_get_preset_lpj() as __init

kvm_get_preset_lpj() is only called from kvmclock_init(), so mark it __init
as well.

Signed-off-by: Dou Liyang <douly.fnst@cn.fujitsu.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Pavel Tatashin <pasha.tatashin@oracle.com>
Cc: <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc:   Radim Krčmář<rkrcmar@redhat.com>
Cc:  <kvm@vger.kernel.org>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Link: https://lkml.kernel.org/r/20180730075421.22830-3-douly.fnst@cn.fujitsu.com
---
 arch/x86/kernel/kvmclock.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
