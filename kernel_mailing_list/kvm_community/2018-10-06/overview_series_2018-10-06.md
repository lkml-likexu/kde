#### [PATCH v1 1/2] x86/cpufeature: Add facility to match microcode revisions
##### From: Andi Kleen <andi@firstfloor.org>

```c
From: Andi Kleen <ak@linux.intel.com>

For bug workarounds or checks it is useful to check for specific
microcode versions. Add a new table format to check for steppings
with min/max microcode revisions.

This does not change the existing x86_cpu_id because it's an ABI
shared with modutils, and also has quite difference requirements,
as in no wildcards, but everything has to be matched exactly.

Signed-off-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/include/asm/cpu_device_id.h | 22 ++++++++++++++
 arch/x86/kernel/cpu/match.c          | 43 ++++++++++++++++++++++++++++
 2 files changed, 65 insertions(+)

```
