#### [PATCH] KVM: nVMX: Allow restore nested-state to enable eVMCS when vCPU in SMM
##### From: Liran Alon <liran.alon@oracle.com>

```c
As comment in code specifies, SMM temporarily disables VMX so we cannot
be in guest mode, nor can VMLAUNCH/VMRESUME be pending.

However, code currently assumes that these are the only flags that can be
set on kvm_state->flags. This is not true as KVM_STATE_NESTED_EVMCS
can also be set on this field to signal that eVMCS should be enabled.

Therefore, fix code to check for guest-mode and pending VMLAUNCH/VMRESUME
explicitly.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Mark APR as reserved in x2APIC
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/apic.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] x86: Memory barrier before setting ICR
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
The wrmsr that is used in x2apic ICR programming does not behave as a
memory barrier. There is a hidden assumption that it is. Add an explicit
memory barrier for this reason.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/apic.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Remove assumptions on CR4.MCE
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
CR4.MCE might be set after boot. Remove the assertion that checks that
it is clear. Change the test to toggle the bit instead of setting it.

Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx_tests.c | 29 +++++++++++++++--------------
 1 file changed, 15 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Reset lapic after boot
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Do not assume that the local APIC is in a xAPIC mode after reset.
Instead reset it first, since it might be in x2APIC mode, from which a
transition in xAPIC is invalid.

Note that we do not use the existing disable_apic() for the matter,
since it also re-initializes apic_ops.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/cstart64.S | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: vmx: Consider CMCI enabled based on IA32_MCG_CAP[10]
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
CMCI is enabled if IA32_MCG_CAP[10] is set. VMX tests do not respect
this condition. Fix it.

Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx_tests.c | 19 ++++++++++++++-----
 1 file changed, 14 insertions(+), 5 deletions(-)

```
#### [PATCH v5 1/2] s390/setup: diag318: refactor struct
##### From: Collin Walling <walling@linux.ibm.com>

```c
The diag318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
