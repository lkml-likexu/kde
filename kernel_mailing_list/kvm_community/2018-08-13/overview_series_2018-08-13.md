#### [PATCH 01/37] arm64: KVM: Add support for Stage-2 control of memory types and cacheability
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Up to ARMv8.3, the combinaison of Stage-1 and Stage-2 attributes
results in the strongest attribute of the two stages.  This means
that the hypervisor has to perform quite a lot of cache maintenance
just in case the guest has some non-cacheable mappings around.

ARMv8.4 solves this problem by offering a different mode (FWB) where
Stage-2 has total control over the memory attribute (this is limited
to systems where both I/O and instruction fetches are coherent with
the dcache). This is achieved by having a different set of memory
attributes in the page tables, and a new bit set in HCR_EL2.

On such a system, we can then safely sidestep any form of dcache
management.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Reviewed-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/include/asm/cpucaps.h      |  3 ++-
 arch/arm64/include/asm/kvm_arm.h      |  1 +
 arch/arm64/include/asm/kvm_emulate.h  |  2 ++
 arch/arm64/include/asm/kvm_mmu.h      | 27 +++++++++++++++++++++------
 arch/arm64/include/asm/memory.h       |  7 +++++++
 arch/arm64/include/asm/pgtable-prot.h | 14 ++++++++++++--
 arch/arm64/include/asm/sysreg.h       |  1 +
 arch/arm64/kernel/cpufeature.c        | 20 ++++++++++++++++++++
 virt/kvm/arm/mmu.c                    |  4 ++++
 9 files changed, 70 insertions(+), 9 deletions(-)

```
#### [PATCH v9 01/22] s390/zcrypt: Add ZAPQ inline function.
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

```c
From: Harald Freudenberger <freude@de.ibm.com>

Added new inline function ap_pqap_zapq()
which is a C inline function wrapper for
the AP PQAP(ZAPQ) instruction.

Signed-off-by: Harald Freudenberger <freude@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/ap_asm.h |   19 +++++++++++++++++++
 1 files changed, 19 insertions(+), 0 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86: Turbo bits in MSR_PLATFORM_INFOFrom: Drew Schmitt <dasch@google.com>
##### From: Drew Schmitt <dasch@google.com>

```c
Allow userspace to set turbo bits in MSR_PLATFORM_INFO. Previously, only
the CPUID faulting bit was settable. But now any bit in
MSR_PLATFORM_INFO would be settable. This can be used, for example, to
convey frequency information about the platform on which the guest is
running.

Signed-off-by: Drew Schmitt <dasch@google.com>
---
v1 -> v2:
- added more background to commit message
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
