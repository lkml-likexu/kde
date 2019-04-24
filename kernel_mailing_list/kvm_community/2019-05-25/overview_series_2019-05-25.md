#### [RFC PATCH 5/6] x86/mm/tlb: Flush remote and local TLBs concurrently
##### From: Nadav Amit <namit@vmware.com>

```c
To improve TLB shootdown performance, flush the remote and local TLBs
concurrently. Introduce flush_tlb_multi() that does so. The current
flush_tlb_others() interface is kept, since paravirtual interfaces need
to be adapted first before it can be removed. This is left for future
work. In such PV environments, TLB flushes are not performed, at this
time, concurrently.

Add a static key to tell whether this new interface is supported.

Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: x86@kernel.org
Cc: Juergen Gross <jgross@suse.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org
Cc: xen-devel@lists.xenproject.org
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 arch/x86/hyperv/mmu.c                 |  2 +
 arch/x86/include/asm/paravirt.h       |  8 +++
 arch/x86/include/asm/paravirt_types.h |  6 ++
 arch/x86/include/asm/tlbflush.h       |  6 ++
 arch/x86/kernel/kvm.c                 |  1 +
 arch/x86/kernel/paravirt.c            |  3 +
 arch/x86/mm/tlb.c                     | 80 +++++++++++++++++++++++----
 arch/x86/xen/mmu_pv.c                 |  2 +
 8 files changed, 96 insertions(+), 12 deletions(-)

```
