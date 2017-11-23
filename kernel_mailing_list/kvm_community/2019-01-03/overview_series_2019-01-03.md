#### [kvm-unit-tests PATCH v4 01/13] s390x: Add Sigp header file
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
The magic numbers for SIGP are not nice to read, so let's put them in
a new header file. Also move sigp_stop() there, it will later be
joined by more sigp functions and definitions.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/asm/sigp.h | 60 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/io.c       | 11 +---------
 2 files changed, 61 insertions(+), 10 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h

diff --git a/lib/s390x/asm/sigp.h b/lib/s390x/asm/sigp.h
new file mode 100644
index 0000000..899a66b
--- /dev/null
+++ b/lib/s390x/asm/sigp.h
@@ -0,0 +1,60 @@
+/*
+ * SIGP related definitions.
+ *
+ * Copied from the Linux kernel file arch/s390/include/asm/sigp.h
+ *
+ * This work is licensed under the terms of the GNU GPL, version
+ * 2. See the COPYING file in the top-level directory.
+ */
+
+#ifndef _ASM_S390X_SIGP_H_
+#define _ASM_S390X_SIGP_H_
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
+#endif /* _ASM_S390X_SIGP_H_ */
```
#### [PATCH v1 1/2] virtio-balloon: tweak config_changed implementation
##### From: Wei Wang <wei.w.wang@intel.com>

```c
virtio-ccw has deadlock issues with reading config registers inside the
interrupt context, so we tweak the virtballoon_changed implementation
by moving the config read operations into the related workqueue contexts.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/virtio_balloon.c | 54 ++++++++++++++++++++---------------------
 1 file changed, 26 insertions(+), 28 deletions(-)

```
#### [PATCH] virtio-ccw: wire up ->bus_name callback
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Return the bus id of the ccw proxy device. This makes 'ethtool -i'
show a more useful value than 'virtio' in the bus-info field.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH] x86: kvmguest: use TSC clocksource if invariant TSC is exposed
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
The invariant TSC bit has the following meaning:

"The time stamp counter in newer processors may support an enhancement,
referred to as invariant TSC. Processor's support for invariant TSC
is indicated by CPUID.80000007H:EDX[8]. The invariant TSC will run
at a constant rate in all ACPI P-, C-. and T-states. This is the
architectural behavior moving forward. On processors with invariant TSC
support, the OS may use the TSC for wall clock timer services (instead
of ACPI or HPET timers). TSC reads are much more efficient and do not
incur the overhead associated with a ring transition or access to a
platform resource."

IOW, TSC does not change frequency. In such case, and with 
TSC scaling hardware available to handle migration, it is possible
to use the TSC clocksource directly, whose system calls are 
faster.

Reduce the rating of kvmclock clocksource to allow TSC clocksource 
to be the default if invariant TSC is exposed.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

```
