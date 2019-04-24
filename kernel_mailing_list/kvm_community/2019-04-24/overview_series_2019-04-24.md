#### [RFC PATCH v1 01/10] KVM: SVM: Add KVM_SEV SEND_START commandThread-Topic: [RFC PATCH v1 01/10] KVM: SVM: Add KVM_SEV SEND_START command
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 .../virtual/kvm/amd-memory-encryption.rst     |  24 +++++
 arch/x86/kvm/svm.c                            | 101 ++++++++++++++++++
 include/uapi/linux/kvm.h                      |  12 +++
 3 files changed, 137 insertions(+)

```
#### [PATCH v2 1/7] KVM: s390: add vector enhancements facility 2 to cpumodel
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
If vector support is enabled, the vector enhancements facility 2
might also be enabled.
We can directly forward this facility to the guest if available
and VX is requested by user space.

Please note that user space can and will have the final decision
on the facility bits for a guests.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Allow xapic ID writes to silently fail
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to Intel SDM: "Some processors permit software to modify the
APIC ID.  However, the ability of software to modify the APIC ID is
processor model specific."

Allow this behavior not to cause failures.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/apic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: APIC: Add test for pending NMIs while NMIs are blocked
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Though explicit documentation is difficult to unearth, x86 guarantees
that exactly one NMI will be pended when NMIs are blocked.  The SDM
essentially calls this out in its section on handling NMIs in SMM:

  NMI interrupts are blocked upon entry to the SMI handler. If an NMI
  request occurs during the SMI handler, it is latched and serviced
  after the processor exits SMM. Only one NMI request will be latched
  during the SMI handler.

Add a test to send multiple NMIs from within an NMI handler to verify
that KVM correctly pends exactly *one* NMI when NMIs are blocked.

Cc: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/apic.c | 29 +++++++++++++++++++++++++++++
 1 file changed, 29 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Remove test_multiple_nmi()
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to the discussion in [1], expecting nested NMIs never to be
collapsed is wrong.

[1] https://marc.info/?l=kvm&m=145876994031502&w=2

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/apic.c | 70 ------------------------------------------------------
 1 file changed, 70 deletions(-)

```
#### [PATCH] KVM: vmx: clean up some debug output
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Smatch complains about this:

    arch/x86/kvm/vmx/vmx.c:5730 dump_vmcs()
    warn: KERN_* level not at start of string

The code should be using pr_cont() instead of pr_err().

Fixes: 9d609649bb29 ("KVM: vmx: print more APICv fields in dump_vmcs")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v8 01/15] x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c
cpu_caps_cleared[] and cpu_caps_set[] may not be aligned to unsigned long.
Atomic operations (i.e. set_bit() and clear_bit()) on the bitmaps may
access two cache lines (a.k.a. split lock) and cause the CPU to do a bus
lock to block all memory accesses from other processors to ensure
atomicity.

To avoid the overall performance degradation from the bus locking, align
the two variables to unsigned long.

Defining the variables as unsigned long may also fix the issue because
they will be naturally aligned to unsigned long. But that needs additional
code changes. Adding __aligned(unsigned long) is a simpler fix.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/kernel/cpu/common.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
