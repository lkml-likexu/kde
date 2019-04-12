#### [PATCH v6 01/17] powerpc/xive: add OPAL extensions for the XIVE native exploitation support
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The support for XIVE native exploitation mode in Linux/KVM needs a
couple more OPAL calls to get and set the state of the XIVE internal
structures being used by a sPAPR guest.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/opal-api.h        |  7 +-
 arch/powerpc/include/asm/opal.h            |  7 ++
 arch/powerpc/include/asm/xive.h            | 14 +++
 arch/powerpc/platforms/powernv/opal-call.c |  3 +
 arch/powerpc/sysdev/xive/native.c          | 99 ++++++++++++++++++++++
 5 files changed, 127 insertions(+), 3 deletions(-)

```
