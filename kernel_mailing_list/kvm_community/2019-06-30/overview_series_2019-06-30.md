#### [PATCH] kvm: arm: Promote KVM_ARM_TARGET_CORTEX_A7 to generic V7 core
##### From: Jan Kiszka <jan.kiszka@web.de>

```c
From: Jan Kiszka <jan.kiszka@siemens.com>

The only difference between the currently supported A15 and A7 target
cores is the reset state of bit 11 in SCTLR. This bit is RES1 or RAO/WI
in other ARM cores, including ARMv8 ones. By promoting A7 to a generic
default target, this allows to use yet unsupported core types. E.g.,
this enables KVM on the A72 of the RPi4.

Signed-off-by: Jan Kiszka <jan.kiszka@siemens.com>
---
 arch/arm/include/uapi/asm/kvm.h                |  1 +
 arch/arm/kvm/Makefile                          |  2 +-
 arch/arm/kvm/{coproc_a7.c => coproc_generic.c} | 18 +++++++++---------
 arch/arm/kvm/guest.c                           |  4 +---
 arch/arm/kvm/reset.c                           |  5 +----
 5 files changed, 13 insertions(+), 17 deletions(-)
 rename arch/arm/kvm/{coproc_a7.c => coproc_generic.c} (70%)

--
2.16.4

```
