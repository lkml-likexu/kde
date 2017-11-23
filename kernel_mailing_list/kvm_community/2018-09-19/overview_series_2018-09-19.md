#### [RFC 01/14] s390/mm: Code cleanups
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Let's clean up leftovers before introducing new code.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/mm/gmap.c    | 8 ++++----
 arch/s390/mm/pgtable.c | 2 +-
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH][kvm-unit-test] nVMX x86: Check EPTP on vmentry of L2 guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following check needs to be enforced on vmentry of L2 guests:

    If the “enable EPT” VM-execution control is 1, the EPTP VM-execution
    control field must satisfy the following checks:

      — The EPT memory type (bits 2:0) must be a value supported by the
        processor as indicated in the IA32_VMX_EPT_VPID_CAP MSR.
      — Bits 5:3 (1 less than the EPT page-walk length) must be 3,
        indicating an EPT page-walk length of 4.
      — Bit 6 (enable bit for accessed and dirty flags for EPT) must be
        0 if bit 21 of the IA32_VMX_EPT_VPID_CAP MSR is read as 0,
	indicating that the processor does not support accessed and dirty
        flags for EPT.
      — Reserved bits 11:7 and 63:N (where N is the processor’s
        physical-address width) must all be 0.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
---
 x86/vmx.h       |   4 ++
 x86/vmx_tests.c | 179 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 183 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: Add prefixes to pgm interrupt checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
We need the information about which of the checks failed if there are
more than one and the prefixes provide that.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/cmm.c    |  4 ++++
 s390x/diag10.c | 23 +++++++++++++++++++++++
 s390x/gs.c     |  8 ++++++++
 s390x/iep.c    |  2 ++
 s390x/pfmf.c   |  2 ++
 s390x/skey.c   |  7 +++++++
 6 files changed, 46 insertions(+)

```
#### [kvm-unit-tests PATCH v2] s390x: Add prefixes to pgm interrupt checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
We need the information about which of the checks failed if there are
more than one and the prefixes provide that.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---

Moved prefix_push to expect_pgm_int() in iep.c

---
 s390x/cmm.c    |  4 ++++
 s390x/diag10.c | 23 +++++++++++++++++++++++
 s390x/gs.c     |  8 ++++++++
 s390x/iep.c    |  2 ++
 s390x/pfmf.c   |  2 ++
 s390x/skey.c   |  7 +++++++
 6 files changed, 46 insertions(+)

```
#### [PATCH] KVM: VMX: check nested state and CR4.VMXE against SMM
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
VMX cannot be enabled under SMM, check it when CR4 is set and when nested
virtualization state is restored.

This should fix some WARNs reported by syzkaller, mostly around
alloc_shadow_vmcs.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] KVM: VMX: immediately mark preemption timer expired only for zero value
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Sean Christopherson <sean.j.christopherson@intel.com>

A VMX preemption timer value of '0' at the time of VMEnter is
architecturally guaranteed to cause a VMExit prior to the CPU
executing any instructions in the guest.  This architectural
definition is in place to ensure that a previously expired timer
is correctly recognized by the CPU as it is possible for the timer
to reach zero and not trigger a VMexit due to a higher priority
VMExit being signalled instead, e.g. a pending #DB that morphs into
a VMExit.

Whether by design or coincidence, commit f4124500c2c1 ("KVM: nVMX:
Fully emulate preemption timer") special cased timer values of '0'
and '1' to ensure prompt delivery of the VMExit.  Unlike '0', a
timer value of '1' has no has no architectural guarantees regarding
when it is delivered.

Modify the timer emulation to trigger immediate VMExit if and only
if the timer value is '0', and document precisely why '0' is special.
Do this even if calibration of the virtual TSC failed, i.e. VMExit
will occur immediately regardless of the frequency of the timer.
Making only '0' a special case gives KVM leeway to be more aggressive
in ensuring the VMExit is injected prior to executing instructions in
the nested guest, and also eliminates any ambiguity as to why '1' is
a special case, e.g. why wasn't the threshold for a "short timeout"
set to 10, 100, 1000, etc...

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH v2]  kvm-unit-test: fix script output abnormal
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
./run_tests.sh
)ASS apic-split (50 tests;
)ASS ioapic-split (19 tests;
)ASS apic (50 tests;
)ASS ioapic (19 tests;
)ASS smptest (1 tests;
)ASS smptest3 (1 tests;

The problem come from commit 0f4f2acb2c880607518cb740a6aa06acafd05855
(x86: io: force carriage return on \n put to serial port). It maybe output
well in real hardware, but it let outputs to file with '\r'.

Changes v1 --> v2:
	changes in scripts/runtime.bash can affect other arch.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 lib/x86/io.c | 3 +++
 1 file changed, 3 insertions(+)

```
