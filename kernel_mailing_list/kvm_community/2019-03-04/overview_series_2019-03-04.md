#### [Qemu-devel] [PATCH] x86: define a new MSR based feature word -- FEAT_CORE_CAPABILITY
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
MSR IA32_CORE_CAPABILITY is a feature-enumerating MSR, which
enumerates the capabilitiy of enabling detection of split locks (bit 5
of MSR_TEST_CTL).

MSR IA32_CORE_CAPABILITY can be enumerated by CPUID.0X7.0:EDX[30].

Related kernel patches can be found here:
https://lkml.org/lkml/2019/3/1/749
Patches 15-17 of kvm are exposing this feature to guest.

If host has split lock detection feature, we can expose it to guest by
using '-cpu host' with this patch and kernel's patches.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 target/i386/cpu.c | 22 +++++++++++++++++++++-
 target/i386/cpu.h |  3 +++
 target/i386/kvm.c |  9 +++++++++
 3 files changed, 33 insertions(+), 1 deletion(-)

```
