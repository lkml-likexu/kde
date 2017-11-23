#### [PATCH AUTOSEL 4.14 24/46] KVM: x86: Update the exit_qualification access bits while walking an address
##### From: Sasha Levin <sashal@kernel.org>

```c
From: KarimAllah Ahmed <karahmed@amazon.de>

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
#### [PATCH]  kvm/x86 : remove unused struct definition
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
structure svm_init_data is never used. So remove it.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/svm.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH v2 1/2] vfio: ccw: Merge BUSY and BOXED states
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
VFIO_CCW_STATE_BOXED and VFIO_CCW_STATE_BUSY have
identical actions for the same events.

Let's merge both into a single state to simplify the code.
We choose to keep VFIO_CCW_STATE_BUSY.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_fsm.c     | 7 +------
 drivers/s390/cio/vfio_ccw_private.h | 1 -
 2 files changed, 1 insertion(+), 7 deletions(-)

```
#### [PATCH v2 1/6] x86/kernel/hyper-v: xmm fast hypercall as guest
##### From: Isaku Yamahata <isaku.yamahata@gmail.com>

```c
hyper-v hypercall supports xmm fast hypercall
where argument is exchanged though regular/xmm registers.
This patch implements them and make use of them.
With this patch, hyperv/hv_apic.c and hyperv/mmu.c will use (xmm) fast
hypercall.

Signed-off-by: Isaku Yamahata <isaku.yamahata@gmail.com>
---
 arch/x86/hyperv/mmu.c               |   4 +-
 arch/x86/hyperv/nested.c            |   2 +-
 arch/x86/include/asm/hyperv-tlfs.h  |   3 +
 arch/x86/include/asm/mshyperv.h     | 176 ++++++++++++++++++++++++++++++++++--
 drivers/hv/hv.c                     |   3 +-
 drivers/pci/controller/pci-hyperv.c |   7 +-
 6 files changed, 179 insertions(+), 16 deletions(-)

```
