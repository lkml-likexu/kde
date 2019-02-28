#### [PATCH v4 01/17] x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c
cpu_caps_cleared and cpu_caps_set may not be aligned to unsigned long.
Atomic operations (i.e. set_bit and clear_bit) on the bitmaps may access
two cache lines (a.k.a. split lock) and lock bus to block all memory
accesses from other processors to ensure atomicity.

To avoid the overall performance degradation from the bus locking, align
the two variables to unsigned long.

Defining the variables as unsigned long may also fix the issue because
they are naturally aligned to unsigned long. But that needs additional
code changes. Adding __aligned(unsigned long) are simpler fixes.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
---
 arch/x86/kernel/cpu/common.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
