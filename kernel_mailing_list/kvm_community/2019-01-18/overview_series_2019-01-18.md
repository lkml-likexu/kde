#### [PATCH 01/29] KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The vCPU-run asm blob does a manual comparison of a VMCS' launched
status to execute the correct VM-Enter instruction, i.e. VMLAUNCH vs.
VMRESUME.  The launched flag is a bool, which is a typedef of _Bool.
C99 does not define an exact size for _Bool, stating only that is must
be large enough to hold '0' and '1'.  Most, if not all, compilers use
a single byte for _Bool, including gcc[1].

Originally, 'launched' was of type 'int' and so the asm blob used 'cmpl'
to check the launch status.  When 'launched' was moved to be stored on a
per-VMCS basis, struct vcpu_vmx's "temporary" __launched flag was added
in order to avoid having to pass the current VMCS into the asm blob.
The new  '__launched' was defined as a 'bool' and not an 'int', but the
'cmp' instruction was not updated.

This has not caused any known problems, likely due to compilers aligning
variables to 4-byte or 8-byte boundaries and KVM zeroing out struct
vcpu_vmx during allocation.  I.e. vCPU-run accesses "junk" data, it just
happens to always be zero and so doesn't affect the result.

[1] https://gcc.gnu.org/ml/gcc-patches/2000-10/msg01127.html

Fixes: d462b8192368 ("KVM: VMX: Keep list of loaded VMCSs, instead of vcpus")
Cc: <stable@vger.kernel.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Sync the pending Posted-Interrupts
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Some Posted-Interrupts from passthrough devices may be lost or
overwritten when the vCPU is in runnable state.

The SN (Suppress Notification) of PID (Posted Interrupt Descriptor) will
be set when the vCPU is preempted (vCPU in KVM_MP_STATE_RUNNABLE state
but not running on physical CPU). If a posted interrupt coming at this
time, the irq remmaping facility will set the bit of PIR (Posted
Interrupt Requests) but ON (Outstanding Notification).
So this interrupt can't be sync to APIC virtualization register and
will not be handled by Guest because ON is zero.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v6 01/11] s390x: Add Sigp header file
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
The magic numbers for SIGP are not nice to read, so let's put them in
a new header file. Also move sigp_stop() there, it will later be
joined by more sigp functions and definitions.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/sigp.h | 60 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/io.c       | 11 +---------
 2 files changed, 61 insertions(+), 10 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h

diff --git a/lib/s390x/asm/sigp.h b/lib/s390x/asm/sigp.h
new file mode 100644
index 0000000..fbd94fc
--- /dev/null
+++ b/lib/s390x/asm/sigp.h
@@ -0,0 +1,60 @@
+/*
+ * SIGP related definitions.
+ *
+ * Copied from the Linux kernel file arch/s390/include/asm/sigp.h
+ *
+ * This work is licensed under the terms of the GNU GPL, version
+ * 2.
+ */
+
+#ifndef ASM_S390X_SIGP_H
+#define ASM_S390X_SIGP_H
+
+/* SIGP order codes */
+#define SIGP_SENSE			1
+#define SIGP_EXTERNAL_CALL		2
+#define SIGP_EMERGENCY_SIGNAL		3
+#define SIGP_START			4
+#define SIGP_STOP			5
+#define SIGP_RESTART			6
+#define SIGP_STOP_AND_STORE_STATUS	9
+#define SIGP_INITIAL_CPU_RESET		11
+#define SIGP_CPU_RESET			12
+#define SIGP_SET_PREFIX			13
+#define SIGP_STORE_STATUS_AT_ADDRESS	14
+#define SIGP_SET_ARCHITECTURE		18
+#define SIGP_COND_EMERGENCY_SIGNAL	19
+#define SIGP_SENSE_RUNNING		21
+#define SIGP_SET_MULTI_THREADING	22
+#define SIGP_STORE_ADDITIONAL_STATUS	23
+
+/* SIGP condition codes */
+#define SIGP_CC_ORDER_CODE_ACCEPTED 0
+#define SIGP_CC_STATUS_STORED	    1
+#define SIGP_CC_BUSY		    2
+#define SIGP_CC_NOT_OPERATIONAL	    3
+
+/* SIGP cpu status bits */
+
+#define SIGP_STATUS_INVALID_ORDER	0x00000002UL
+#define SIGP_STATUS_CHECK_STOP		0x00000010UL
+#define SIGP_STATUS_STOPPED		0x00000040UL
+#define SIGP_STATUS_EXT_CALL_PENDING	0x00000080UL
+#define SIGP_STATUS_INVALID_PARAMETER	0x00000100UL
+#define SIGP_STATUS_INCORRECT_STATE	0x00000200UL
+#define SIGP_STATUS_NOT_RUNNING		0x00000400UL
+
+#ifndef __ASSEMBLER__
+
+static inline void sigp_stop(void)
+{
+	register unsigned long status asm ("1") = 0;
+	register unsigned long cpu asm ("2") = 0;
+
+	asm volatile(
+		"	sigp %0,%1,0(%2)\n"
+		: "+d" (status)  : "d" (cpu), "d" (SIGP_STOP) : "cc");
+}
+
+#endif /* __ASSEMBLER__ */
+#endif /* ASM_S390X_SIGP_H */
```
