

#### [PATCH v2 0/4] KVM: arm/arm64: vgic-v3: Group0 SGI support
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

Although we now have Group0 support, we still miss support for Group0
SGIs (which amounts to handling ICC_SGI0R_EL1 and ICC_ASGI1R_EL1
traps), and this small series adds such support.

I appreciate this is *very* late for 4.19, yet I'd like to take it in
as they complement Christoffer's Group0 support, and It'd be annoying
to have something incomplete in 4.19.

Please shout if you spot something that doesn't look quite right.

Thanks,

	M.

* From v1:
  - Clarified the condition for which a G1 SGI can be queued
  - Added ABs abd RBs from Christoffer and Eric

Marc Zyngier (4):
  KVM: arm64: Remove non-existent AArch32 ICC_SGI1R encoding
  KVM: arm/arm64: vgic-v3: Add core support for Group0 SGIs
  KVM: arm64: vgic-v3: Add support for ICC_SGI0R_EL1 and ICC_ASGI1R_EL1
    accesses
  KVM: arm: vgic-v3: Add support for ICC_SGI0R and ICC_ASGI1R accesses

 arch/arm/kvm/coproc.c            | 25 ++++++++++++++++++-
 arch/arm64/include/asm/sysreg.h  |  2 ++
 arch/arm64/kvm/sys_regs.c        | 43 +++++++++++++++++++++++++++++---
 include/kvm/arm_vgic.h           |  2 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c | 19 +++++++++++---
 5 files changed, 81 insertions(+), 10 deletions(-)
```
