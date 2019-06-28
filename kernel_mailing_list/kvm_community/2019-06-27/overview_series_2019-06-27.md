#### [RFC PATCH v3 1/4] vfio: Define device specific irq type capability
##### From: Tina Zhang <tina.zhang@intel.com>

```c
Cap the number of irqs with fixed indexes and use capability chains
to chain device specific irqs.

Signed-off-by: Tina Zhang <tina.zhang@intel.com>
---
 include/uapi/linux/vfio.h | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2] x86: Remove assumptions on CR4.MCE
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
CR4.MCE might be set after boot. Remove the assertion that checks that
it is clear. Change the test to toggle the bit instead of setting it.

Cc: Marc Orr <marcorr@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx_tests.c | 27 +++++++++++++--------------
 1 file changed, 13 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Reset lapic after boot
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Do not assume that the local APIC is in a xAPIC mode after reset.
Instead reset it first, since it might be in x2APIC mode, from which a
transition in xAPIC is invalid.

To use reset_apic(), change it to use xapic_write(), in order to make safe to use
while apic_ops might change concurrently by x2apic_enable().

Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/x86/apic.c | 2 +-
 x86/cstart64.S | 2 ++
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Load segments after GDT loading
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Whenever we load the GDT, we need to reload the segment selectors so
their hidden data (base, limit, type, etc.) would be reloaded.

It appears that loading GS overwrites the GS bases, so reload GS base
after loading the segment to prevent per-cpu variable corruption.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/cstart64.S | 23 +++++++++++++++++------
 1 file changed, 17 insertions(+), 6 deletions(-)

```
#### [PATCH] kvm: x86: Pass through AMD_STIBP_ALWAYS_ON in GET_SUPPORTED_CPUID
##### From: Jim Mattson <jmattson@google.com>

```c
This bit is purely advisory. Passing it through to the guest indicates
that the virtual processor, like the physical processor, prefers that
STIBP is only set once during boot and not changed.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
