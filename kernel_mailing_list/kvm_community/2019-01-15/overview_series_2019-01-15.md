#### [PATCH] kvm, x86, mmu: Use kernel generic dynamic physical address mask
##### From: Kai Huang <kai.huang@linux.intel.com>

```c
AMD's SME/SEV is no longer the only case which reduces supported
physical address bits, since Intel introduced Multi-key Total Memory
Encryption (MKTME), which repurposes high bits of physical address as
keyID, thus effectively shrinks supported physical address bits. To
cover both cases (and potential similar future features), kernel MM
introduced generic dynamaic physical address mask instead of hard-coded
__PHYSICAL_MASK in 'commit 94d49eb30e854 ("x86/mm: Decouple dynamic
__PHYSICAL_MASK from AMD SME")'. KVM should use that too.

Change PT64_BASE_ADDR_MASK to use kernel dynamic physical address mask
when it is enabled, instead of sme_clr. PT64_DIR_BASE_ADDR_MASK is also
deleted since it is not used at all.

Signed-off-by: Kai Huang <kai.huang@linux.intel.com>
---
 arch/x86/kvm/mmu.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
