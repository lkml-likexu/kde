#### [PATCH 1/3] selftests/x86: Test SYSCALL and SYSENTER manually with TF set
##### From: Andy Lutomirski <luto@kernel.org>

```c
Make sure that we exercise both variants of the nasty
TF-in-compat-syscall regardless of what vendor's CPU is running the
tests.

Also change the intentional signal after SYSCALL to use ud2, which
is a lot more comprehensible.

This crashes the kernel due to an FSGSBASE bug right now.

This test *also* detects a bug in KVM when run on an Intel host.
KVM people, feel free to use it to help debug.  There's a bunch of
code in this test to warn instead of infinite looping when the bug
gets triggered.

Reported-by: Vegard Nossum <vegard.nossum@oracle.com>
Cc: "Bae, Chang Seok" <chang.seok.bae@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Andy Lutomirski <luto@kernel.org>
---
 tools/testing/selftests/x86/Makefile          |   5 +-
 .../testing/selftests/x86/syscall_arg_fault.c | 112 +++++++++++++++++-
 2 files changed, 110 insertions(+), 7 deletions(-)

```
#### [PATCH] Documentation: kvm: document CPUID bit for MSR_KVM_POLL_CONTROL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/cpuid.txt | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 4.14 22/43] x86/speculation: Allow guests to use SSBD even if host does not
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>

commit c1f7fec1eb6a2c86d01bc22afce772c743451d88 upstream.

The bits set in x86_spec_ctrl_mask are used to calculate the guest's value
of SPEC_CTRL that is written to the MSR before VMENTRY, and control which
mitigations the guest can enable.  In the case of SSBD, unless the host has
enabled SSBD always on mode (by passing "spec_store_bypass_disable=on" in
the kernel parameters), the SSBD bit is not set in the mask and the guest
can not properly enable the SSBD always on mitigation mode.

This has been confirmed by running the SSBD PoC on a guest using the SSBD
always on mitigation mode (booted with kernel parameter
"spec_store_bypass_disable=on"), and verifying that the guest is vulnerable
unless the host is also using SSBD always on mode. In addition, the guest
OS incorrectly reports the SSB vulnerability as mitigated.

Always set the SSBD bit in x86_spec_ctrl_mask when the host CPU supports
it, allowing the guest to use SSBD whether or not the host has chosen to
enable the mitigation in any of its modes.

Fixes: be6fcb5478e9 ("x86/bugs: Rework spec_ctrl base and mask logic")
Signed-off-by: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: bp@alien8.de
Cc: rkrcmar@redhat.com
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Link: https://lkml.kernel.org/r/1560187210-11054-1-git-send-email-alejandro.j.jimenez@oracle.com
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kernel/cpu/bugs.c |   11 ++++++++++-
```
#### [PATCH 4.19 41/72] x86/speculation: Allow guests to use SSBD even if host does not
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>

commit c1f7fec1eb6a2c86d01bc22afce772c743451d88 upstream.

The bits set in x86_spec_ctrl_mask are used to calculate the guest's value
of SPEC_CTRL that is written to the MSR before VMENTRY, and control which
mitigations the guest can enable.  In the case of SSBD, unless the host has
enabled SSBD always on mode (by passing "spec_store_bypass_disable=on" in
the kernel parameters), the SSBD bit is not set in the mask and the guest
can not properly enable the SSBD always on mitigation mode.

This has been confirmed by running the SSBD PoC on a guest using the SSBD
always on mitigation mode (booted with kernel parameter
"spec_store_bypass_disable=on"), and verifying that the guest is vulnerable
unless the host is also using SSBD always on mode. In addition, the guest
OS incorrectly reports the SSB vulnerability as mitigated.

Always set the SSBD bit in x86_spec_ctrl_mask when the host CPU supports
it, allowing the guest to use SSBD whether or not the host has chosen to
enable the mitigation in any of its modes.

Fixes: be6fcb5478e9 ("x86/bugs: Rework spec_ctrl base and mask logic")
Signed-off-by: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: bp@alien8.de
Cc: rkrcmar@redhat.com
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Link: https://lkml.kernel.org/r/1560187210-11054-1-git-send-email-alejandro.j.jimenez@oracle.com
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kernel/cpu/bugs.c |   11 ++++++++++-
```
#### [PATCH 5.1 21/55] x86/speculation: Allow guests to use SSBD even if host does not
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>

commit c1f7fec1eb6a2c86d01bc22afce772c743451d88 upstream.

The bits set in x86_spec_ctrl_mask are used to calculate the guest's value
of SPEC_CTRL that is written to the MSR before VMENTRY, and control which
mitigations the guest can enable.  In the case of SSBD, unless the host has
enabled SSBD always on mode (by passing "spec_store_bypass_disable=on" in
the kernel parameters), the SSBD bit is not set in the mask and the guest
can not properly enable the SSBD always on mitigation mode.

This has been confirmed by running the SSBD PoC on a guest using the SSBD
always on mitigation mode (booted with kernel parameter
"spec_store_bypass_disable=on"), and verifying that the guest is vulnerable
unless the host is also using SSBD always on mode. In addition, the guest
OS incorrectly reports the SSB vulnerability as mitigated.

Always set the SSBD bit in x86_spec_ctrl_mask when the host CPU supports
it, allowing the guest to use SSBD whether or not the host has chosen to
enable the mitigation in any of its modes.

Fixes: be6fcb5478e9 ("x86/bugs: Rework spec_ctrl base and mask logic")
Signed-off-by: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: bp@alien8.de
Cc: rkrcmar@redhat.com
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Link: https://lkml.kernel.org/r/1560187210-11054-1-git-send-email-alejandro.j.jimenez@oracle.com
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/kernel/cpu/bugs.c |   11 ++++++++++-
```
#### [PATCH] KVM: LAPIC: Fix pending interrupt in IRR blocked by software disable LAPIC
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Thomas reported that:

 | Background:
 | 
 |    In preparation of supporting IPI shorthands I changed the CPU offline
 |    code to software disable the local APIC instead of just masking it.
 |    That's done by clearing the APIC_SPIV_APIC_ENABLED bit in the APIC_SPIV
 |    register.
 | 
 | Failure:
 | 
 |    When the CPU comes back online the startup code triggers occasionally
 |    the warning in apic_pending_intr_clear(). That complains that the IRRs
 |    are not empty.
 | 
 |    The offending vector is the local APIC timer vector who's IRR bit is set
 |    and stays set.
 | 
 | It took me quite some time to reproduce the issue locally, but now I can
 | see what happens.
 | 
 | It requires apicv_enabled=0, i.e. full apic emulation. With apicv_enabled=1
 | (and hardware support) it behaves correctly.
 | 
 | Here is the series of events:
 | 
 |     Guest CPU
 | 
 |     goes down
 | 
 |       native_cpu_disable()		
 | 
 | 			apic_soft_disable();
 | 
 |     play_dead()
 | 
 |     ....
 | 
 |     startup()
 | 
 |       if (apic_enabled())
 |         apic_pending_intr_clear()	<- Not taken
 | 
 |      enable APIC
 | 
 |         apic_pending_intr_clear()	<- Triggers warning because IRR is stale
 | 
 | When this happens then the deadline timer or the regular APIC timer -
 | happens with both, has fired shortly before the APIC is disabled, but the
 | interrupt was not serviced because the guest CPU was in an interrupt
 | disabled region at that point.
 | 
 | The state of the timer vector ISR/IRR bits:
 | 
 |     	     	       	        ISR     IRR
 | before apic_soft_disable()    0	      1
 | after apic_soft_disable()     0	      1
 | 
 | On startup		      		 0	      1
 | 
 | Now one would assume that the IRR is cleared after the INIT reset, but this
 | happens only on CPU0.
 | 
 | Why?
 | 
 | Because our CPU0 hotplug is just for testing to make sure nothing breaks
 | and goes through an NMI wakeup vehicle because INIT would send it through
 | the boots-trap code which is not really working if that CPU was not
 | physically unplugged.
 | 
 | Now looking at a real world APIC the situation in that case is:
 | 
 |     	     	       	      	ISR     IRR
 | before apic_soft_disable()    0	      1
 | after apic_soft_disable()     0	      1
 | 
 | On startup		      		 0	      0
 | 
 | Why?
 | 
 | Once the dying CPU reenables interrupts the pending interrupt gets
 | delivered as a spurious interupt and then the state is clear.
 | 
 | While that CPU0 hotplug test case is surely an esoteric issue, the APIC
 | emulation is still wrong, Even if the play_dead() code would not enable
 | interrupts then the pending IRR bit would turn into an ISR .. interrupt
 | when the APIC is reenabled on startup.


From SDM 10.4.7.2 Local APIC State After It Has Been Software Disabled
* Pending interrupts in the IRR and ISR registers are held and require
  masking or handling by the CPU.

In Thomas's testing, hardware cpu will not respect soft disable LAPIC 
when IRR has already been set or APICv posted-interrupt is in flight, 
so we can skip soft disable APIC checking when clearing IRR and set ISR,
continue to respect soft disable APIC when attempting to set IRR.

Reported-by: Rong Chen <rong.a.chen@intel.com>
Reported-by: Feng Tang <feng.tang@intel.com>
Reported-by: Thomas Gleixner <tglx@linutronix.de>
Tested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Rong Chen <rong.a.chen@intel.com>
Cc: Feng Tang <feng.tang@intel.com>
Cc: stable@vger.kernel.org
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: nVMX: include conditional controls in /dev/kvm KVM_GET_MSRS
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Some secondary controls are automatically enabled/disabled based on the CPUID
values that are set for the guest.  However, they are still available at a
global level and therefore should be present when KVM_GET_MSRS is sent to
/dev/kvm.

Fixes: 1389309c811 ("KVM: nVMX: expose VMX capabilities for nested hypervisors to userspace", 2018-02-26)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio-ccw: Fix the conversion of Format-0 CCWs to Format-1
##### From: Eric Farman <farman@linux.ibm.com>

```c
When processing Format-0 CCWs, we use the "len" variable as the
number of CCWs to convert to Format-1.  But that variable
contains zero here, and is not a meaningful CCW count until
ccwchain_calc_length() returns.  Since that routine requires and
expects Format-1 CCWs to identify the chaining behavior, the
format conversion must be done first.

Convert the 2KB we copied even if it's more than we need.

Fixes: 7f8e89a8f2fd ("vfio-ccw: Factor out the ccw0-to-ccw1 transition")
Reported-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
