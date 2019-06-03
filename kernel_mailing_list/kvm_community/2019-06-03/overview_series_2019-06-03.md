#### [PATCH v16 01/16] uaccess: add untagged_addr definition for other arches
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
To allow arm64 syscalls to accept tagged pointers from userspace, we must
untag them when they are passed to the kernel. Since untagging is done in
generic parts of the kernel, the untagged_addr macro needs to be defined
for all architectures.

Define it as a noop for architectures other than arm64.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Reviewed-by: Khalid Aziz <khalid.aziz@oracle.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 include/linux/mm.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [patch 1/3] drivers/cpuidle: add cpuidle-haltpoll driverReferences: <20190603225242.289109849@amt.cnet>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
The cpuidle_kvm driver allows the guest vcpus to poll for a specified
amount of time before halting. This provides the following benefits
to host side polling:

        1) The POLL flag is set while polling is performed, which allows
           a remote vCPU to avoid sending an IPI (and the associated
           cost of handling the IPI) when performing a wakeup.

        2) The HLT VM-exit cost can be avoided.

The downside of guest side polling is that polling is performed
even with other runnable tasks in the host.

Results comparing halt_poll_ns and server/client application
where a small packet is ping-ponged:

host                                        --> 31.33
halt_poll_ns=300000 / no guest busy spin    --> 33.40   (93.8%)
halt_poll_ns=0 / guest_halt_poll_ns=300000  --> 32.73   (95.7%)

For the SAP HANA benchmarks (where idle_spin is a parameter
of the previous version of the patch, results should be the
same):

hpns == halt_poll_ns

                          idle_spin=0/   idle_spin=800/    idle_spin=0/
                          hpns=200000    hpns=0            hpns=800000
DeleteC06T03 (100 thread) 1.76           1.71 (-3%)        1.78   (+1%)
InsertC16T02 (100 thread) 2.14           2.07 (-3%)        2.18   (+1.8%)
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)	   1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)	   4.53   (-5%)
---
 Documentation/virtual/guest-halt-polling.txt |   78 ++++++++++++
 arch/x86/kernel/process.c                    |    2 
 drivers/cpuidle/Kconfig                      |   10 +
 drivers/cpuidle/Makefile                     |    1 
 drivers/cpuidle/cpuidle-haltpoll-trace.h     |   65 ++++++++++
 drivers/cpuidle/cpuidle-haltpoll.c           |  172 +++++++++++++++++++++++++++
 6 files changed, 327 insertions(+), 1 deletion(-)

Index: linux-2.6.git/Documentation/virtual/guest-halt-polling.txt
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/Documentation/virtual/guest-halt-polling.txt	2019-06-03 19:31:36.003302371 -0300
@@ -0,0 +1,78 @@
+Guest halt polling
+==================
+
+The cpuidle_haltpoll driver allows the guest vcpus to poll for a specified
+amount of time before halting. This provides the following benefits
+to host side polling:
+
+	1) The POLL flag is set while polling is performed, which allows
+	   a remote vCPU to avoid sending an IPI (and the associated
+ 	   cost of handling the IPI) when performing a wakeup.
+
+	2) The HLT VM-exit cost can be avoided.
+
+The downside of guest side polling is that polling is performed
+even with other runnable tasks in the host.
+
+The basic logic as follows: A global value, guest_halt_poll_ns,
+is configured by the user, indicating the maximum amount of
+time polling is allowed. This value is fixed.
+
+Each vcpu has an adjustable guest_halt_poll_ns
+("per-cpu guest_halt_poll_ns"), which is adjusted by the algorithm
+in response to events (explained below).
+
+Module Parameters
+=================
+
+The cpuidle_haltpoll module has 5 tunable module parameters:
+
+1) guest_halt_poll_ns:
+Maximum amount of time, in nanoseconds, that polling is
+performed before halting.
+
+Default: 200000
+
+2) guest_halt_poll_shrink:
+Division factor used to shrink per-cpu guest_halt_poll_ns when
+wakeup event occurs after the global guest_halt_poll_ns.
+
+Default: 2
+
+3) guest_halt_poll_grow:
+Multiplication factor used to grow per-cpu guest_halt_poll_ns
+when event occurs after per-cpu guest_halt_poll_ns
+but before global guest_halt_poll_ns.
+
+Default: 2
+
+4) guest_halt_poll_grow_start:
+The per-cpu guest_halt_poll_ns eventually reaches zero
+in case of an idle system. This value sets the initial
+per-cpu guest_halt_poll_ns when growing. This can
+be increased from 10000, to avoid misses during the initial
+growth stage:
+
+10000, 20000, 40000, ... (example assumes guest_halt_poll_grow=2).
+
+Default: 10000
+
+5) guest_halt_poll_allow_shrink:
+
+Bool parameter which allows shrinking. Set to N
+to avoid it (per-cpu guest_halt_poll_ns will remain
+high once achieves global guest_halt_poll_ns value).
+
+Default: Y
+
+The module parameters can be set from the debugfs files in:
+
+	/sys/module/cpuidle_haltpoll/parameters/
+
+Further Notes
+=============
+
+- Care should be taken when setting the guest_halt_poll_ns parameter as a
+large value has the potential to drive the cpu usage to 100% on a machine which
+would be almost entirely idle otherwise.
+
Index: linux-2.6.git/arch/x86/kernel/process.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kernel/process.c	2019-05-29 14:46:14.527005582 -0300
+++ linux-2.6.git/arch/x86/kernel/process.c	2019-06-03 19:31:36.004302375 -0300
@@ -580,7 +580,7 @@
 	safe_halt();
 	trace_cpu_idle_rcuidle(PWR_EVENT_EXIT, smp_processor_id());
 }
-#ifdef CONFIG_APM_MODULE
+#if defined(CONFIG_APM_MODULE) || defined(CONFIG_HALTPOLL_CPUIDLE_MODULE)
 EXPORT_SYMBOL(default_idle);
 #endif
 
Index: linux-2.6.git/drivers/cpuidle/Kconfig
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/Kconfig	2019-05-29 14:46:14.668006053 -0300
+++ linux-2.6.git/drivers/cpuidle/Kconfig	2019-06-03 19:31:36.004302375 -0300
@@ -51,6 +51,16 @@
 source "drivers/cpuidle/Kconfig.powerpc"
 endmenu
 
+config HALTPOLL_CPUIDLE
+       tristate "Halt poll cpuidle driver"
+       depends on X86
+       default y
+       help
+         This option enables halt poll cpuidle driver, which allows to poll
+         before halting in the guest (more efficient than polling in the
+         host via halt_poll_ns for some scenarios).
+
+
 endif
 
 config ARCH_NEEDS_CPU_IDLE_COUPLED
Index: linux-2.6.git/drivers/cpuidle/Makefile
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/Makefile	2019-05-29 14:44:43.030700871 -0300
+++ linux-2.6.git/drivers/cpuidle/Makefile	2019-06-03 19:31:36.004302375 -0300
@@ -7,6 +7,7 @@
 obj-$(CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED) += coupled.o
 obj-$(CONFIG_DT_IDLE_STATES)		  += dt_idle_states.o
 obj-$(CONFIG_ARCH_HAS_CPU_RELAX)	  += poll_state.o
+obj-$(CONFIG_HALTPOLL_CPUIDLE)		  += cpuidle-haltpoll.o
 
 ##################################################################################
 # ARM SoC drivers
Index: linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll-trace.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll-trace.h	2019-06-03 19:31:36.005302378 -0300
@@ -0,0 +1,65 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#if !defined(_HALTPOLL_TRACE_H_) || defined(TRACE_HEADER_MULTI_READ)
+#define _HALTPOLL_TRACE_H_
+
+#include <linux/stringify.h>
+#include <linux/types.h>
+#include <linux/tracepoint.h>
+
+#undef TRACE_SYSTEM
+#define TRACE_SYSTEM cpuidle_haltpoll
+
+TRACE_EVENT(cpuidle_haltpoll_success,
+	    TP_PROTO(unsigned int cpu_halt_poll_ns, u64 block_ns),
+	    TP_ARGS(cpu_halt_poll_ns, block_ns),
+
+	    TP_STRUCT__entry(
+			     __field(unsigned int, cpu_halt_poll_ns)
+			     __field(u64,	   block_ns)
+			    ),
+
+	    TP_fast_assign(
+			   __entry->cpu_halt_poll_ns = cpu_halt_poll_ns;
+			   __entry->block_ns = block_ns;
+			  ),
+
+	    TP_printk("cpu_halt_poll_ns %u block_ns %lld",
+			  __entry->cpu_halt_poll_ns,
+			  __entry->block_ns)
+);
+
+TRACE_EVENT(cpuidle_haltpoll_fail,
+		TP_PROTO(unsigned int prev_cpu_halt_poll_ns,
+			 unsigned int cpu_halt_poll_ns,
+			 u64 block_ns),
+		TP_ARGS(prev_cpu_halt_poll_ns, cpu_halt_poll_ns, block_ns),
+
+		TP_STRUCT__entry(
+				__field(unsigned int, prev_cpu_halt_poll_ns)
+				__field(unsigned int, cpu_halt_poll_ns)
+				__field(u64,	   block_ns)
+				),
+
+		TP_fast_assign(
+			      __entry->prev_cpu_halt_poll_ns =
+					prev_cpu_halt_poll_ns;
+			      __entry->cpu_halt_poll_ns = cpu_halt_poll_ns;
+			      __entry->block_ns = block_ns;
+			      ),
+
+		TP_printk("prev_cpu_halt_poll_ns %u cpu_halt_poll_ns %u block_ns %lld",
+			      __entry->prev_cpu_halt_poll_ns,
+			      __entry->cpu_halt_poll_ns,
+			      __entry->block_ns)
+);
+
+#endif /* _HALTPOLL_TRACE_H_ */
+
+/* This part must be outside protection */
+#undef TRACE_INCLUDE_PATH
+#define TRACE_INCLUDE_PATH ../../drivers/cpuidle/
+#undef TRACE_INCLUDE_FILE
+#define TRACE_INCLUDE_FILE cpuidle-haltpoll-trace
+#include <trace/define_trace.h>
+
+
Index: linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-03 19:31:36.005302378 -0300
@@ -0,0 +1,172 @@
+// SPDX-License-Identifier: GPL-2.0
+/*
+ * cpuidle driver for halt polling.
+ *
+ * Copyright 2019 Red Hat, Inc. and/or its affiliates.
+ *
+ * This work is licensed under the terms of the GNU GPL, version 2.  See
+ * the COPYING file in the top-level directory.
+ *
+ * Authors: Marcelo Tosatti <mtosatti@redhat.com>
+ */
+
+#include <linux/init.h>
+#include <linux/cpuidle.h>
+#include <linux/module.h>
+#include <linux/timekeeping.h>
+#include <linux/sched/idle.h>
+#define CREATE_TRACE_POINTS
+#include "cpuidle-haltpoll-trace.h"
+
+unsigned int guest_halt_poll_ns = 200000;
+module_param(guest_halt_poll_ns, uint, 0644);
+
+/* division factor to shrink halt_poll_ns */
+unsigned int guest_halt_poll_shrink = 2;
+module_param(guest_halt_poll_shrink, uint, 0644);
+
+/* multiplication factor to grow per-cpu halt_poll_ns */
+unsigned int guest_halt_poll_grow = 2;
+module_param(guest_halt_poll_grow, uint, 0644);
+
+/* value in ns to start growing per-cpu halt_poll_ns */
+unsigned int guest_halt_poll_grow_start = 10000;
+module_param(guest_halt_poll_grow_start, uint, 0644);
+
+/* value in ns to start growing per-cpu halt_poll_ns */
+bool guest_halt_poll_allow_shrink = true;
+module_param(guest_halt_poll_allow_shrink, bool, 0644);
+
+static DEFINE_PER_CPU(unsigned int, halt_poll_ns);
+
+static void adjust_haltpoll_ns(unsigned int block_ns,
+			       unsigned int *cpu_halt_poll_ns)
+{
+	unsigned int val;
+	unsigned int prev_halt_poll_ns = *cpu_halt_poll_ns;
+
+	/* Grow cpu_halt_poll_ns if
+	 * cpu_halt_poll_ns < block_ns < guest_halt_poll_ns
+	 */
+	if (block_ns > *cpu_halt_poll_ns && block_ns <= guest_halt_poll_ns) {
+		val = *cpu_halt_poll_ns * guest_halt_poll_grow;
+
+		if (val < guest_halt_poll_grow_start)
+			val = guest_halt_poll_grow_start;
+		if (val > guest_halt_poll_ns)
+			val = guest_halt_poll_ns;
+
+		*cpu_halt_poll_ns = val;
+	} else if (block_ns > guest_halt_poll_ns &&
+		   guest_halt_poll_allow_shrink) {
+		unsigned int shrink = guest_halt_poll_shrink;
+
+		val = *cpu_halt_poll_ns;
+		if (shrink == 0)
+			val = 0;
+		else
+			val /= shrink;
+		*cpu_halt_poll_ns = val;
+	}
+
+	trace_cpuidle_haltpoll_fail(prev_halt_poll_ns, *cpu_halt_poll_ns,
+				    block_ns);
+}
+
+static int haltpoll_enter_idle(struct cpuidle_device *dev,
+			  struct cpuidle_driver *drv, int index)
+{
+	int do_halt = 0;
+	unsigned int *cpu_halt_poll_ns;
+	ktime_t start, now;
+	int cpu = smp_processor_id();
+
+	cpu_halt_poll_ns = per_cpu_ptr(&halt_poll_ns, cpu);
+
+	/* No polling */
+	if (guest_halt_poll_ns == 0) {
+		if (current_clr_polling_and_test()) {
+			local_irq_enable();
+			return index;
+		}
+		default_idle();
+		return index;
+	}
+
+	local_irq_enable();
+
+	now = start = ktime_get();
+	if (!current_set_polling_and_test()) {
+		ktime_t end_spin;
+
+		end_spin = ktime_add_ns(now, *cpu_halt_poll_ns);
+
+		while (!need_resched()) {
+			cpu_relax();
+			now = ktime_get();
+
+			if (!ktime_before(now, end_spin)) {
+				do_halt = 1;
+				break;
+			}
+		}
+	}
+
+	if (do_halt) {
+		u64 block_ns;
+
+		/*
+		 * No events while busy spin window passed,
+		 * halt.
+		 */
+		local_irq_disable();
+		if (current_clr_polling_and_test()) {
+			local_irq_enable();
+			return index;
+		}
+		default_idle();
+		block_ns = ktime_to_ns(ktime_sub(ktime_get(), start));
+		adjust_haltpoll_ns(block_ns, cpu_halt_poll_ns);
+	} else {
+		u64 block_ns = ktime_to_ns(ktime_sub(now, start));
+
+		trace_cpuidle_haltpoll_success(*cpu_halt_poll_ns, block_ns);
+		current_clr_polling();
+	}
+
+	return index;
+}
+
+static struct cpuidle_driver haltpoll_driver = {
+	.name = "haltpoll_idle",
+	.owner = THIS_MODULE,
+	.states = {
+		{ /* entry 0 is for polling */ },
+		{
+			.enter			= haltpoll_enter_idle,
+			.exit_latency		= 0,
+			.target_residency	= 0,
+			.power_usage		= -1,
+			.name			= "Halt poll",
+			.desc			= "Halt poll idle",
+		},
+	},
+	.safe_state_index = 0,
+	.state_count = 2,
+};
+
+static int __init haltpoll_init(void)
+{
+	return cpuidle_register(&haltpoll_driver, NULL);
+}
+
+static void __exit haltpoll_exit(void)
+{
+	cpuidle_unregister(&haltpoll_driver);
+}
+
+module_init(haltpoll_init);
+module_exit(haltpoll_exit);
+MODULE_LICENSE("GPL");
+MODULE_AUTHOR("Marcelo Tosatti <mtosatti@redhat.com>");
+

From patchwork Mon Jun  3 22:52:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10974063
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E20841880
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:23 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id CF0E02874A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:23 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id C2AF02875C; Mon,  3 Jun 2019 23:01:23 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 40CCB2875F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726521AbfFCXBW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Jun 2019 19:01:22 -0400
Received: from mx1.redhat.com ([209.132.183.28]:43908 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726349AbfFCXBW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Jun 2019 19:01:22 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 17AB2285B4;
        Mon,  3 Jun 2019 23:01:21 +0000 (UTC)
Received: from amt.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 59A251001DE0;
        Mon,  3 Jun 2019 23:01:20 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id AABE410515C;
        Mon,  3 Jun 2019 19:54:57 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x53MsvCh007683;
        Mon, 3 Jun 2019 19:54:57 -0300
Message-Id: <20190603225254.292226777@amt.cnet>
User-Agent: quilt/0.60-1
Date: Mon, 03 Jun 2019 19:52:44 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>, =?iso-8859-15?q?Radim_Kr=C4=8Dm=C3?=
	=?iso-8859-15?q?=A1=C5=99?=  <rkrcmar@redhat.com>,
 Andrea Arcangeli <aarcange@redhat.com>,
 "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>,
 Peter Zijlstra <peterz@infradead.org>, Wanpeng Li <kernellwp@gmail.com>,
 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
 Raslan KarimAllah <karahmed@amazon.de>,
 Boris Ostrovsky <boris.ostrovsky@oracle.com>,
 Ankur Arora <ankur.a.arora@oracle.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 2/3] kvm: x86: add host poll control msrs
References: <20190603225242.289109849@amt.cnet>
Content-Disposition: inline; filename=02-pollcontrol-host.patch
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.30]);
 Mon, 03 Jun 2019 23:01:21 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Add an MSRs which allows the guest to disable 
host polling (specifically the cpuidle-haltpoll, 
when performing polling in the guest, disables
host side polling).

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 Documentation/virtual/kvm/msr.txt    |    9 +++++++++
 arch/x86/include/asm/kvm_host.h      |    2 ++
 arch/x86/include/uapi/asm/kvm_para.h |    2 ++
 arch/x86/kvm/Kconfig                 |    1 +
 arch/x86/kvm/cpuid.c                 |    3 ++-
 arch/x86/kvm/x86.c                   |   23 +++++++++++++++++++++++
 6 files changed, 39 insertions(+), 1 deletion(-)

Index: linux-2.6.git/Documentation/virtual/kvm/msr.txt
===================================================================
--- linux-2.6.git.orig/Documentation/virtual/kvm/msr.txt	2018-05-18 15:40:19.697438928 -0300
+++ linux-2.6.git/Documentation/virtual/kvm/msr.txt	2019-06-03 19:37:49.618543527 -0300
@@ -273,3 +273,12 @@
 	guest must both read the least significant bit in the memory area and
 	clear it using a single CPU instruction, such as test and clear, or
 	compare and exchange.
+
+MSR_KVM_POLL_CONTROL: 0x4b564d05
+	Control host side polling.
+
+	data: Bit 0 enables (1) or disables (0) host halt poll
+	logic.
+	KVM guests can disable host halt polling when performing
+	polling themselves.
+
Index: linux-2.6.git/arch/x86/include/asm/kvm_host.h
===================================================================
--- linux-2.6.git.orig/arch/x86/include/asm/kvm_host.h	2019-05-29 14:46:14.516005546 -0300
+++ linux-2.6.git/arch/x86/include/asm/kvm_host.h	2019-06-03 19:37:49.619543530 -0300
@@ -755,6 +755,8 @@
 		struct gfn_to_hva_cache data;
 	} pv_eoi;
 
+	u64 msr_kvm_poll_control;
+
 	/*
 	 * Indicate whether the access faults on its page table in guest
 	 * which is set when fix page fault and used to detect unhandeable
Index: linux-2.6.git/arch/x86/include/uapi/asm/kvm_para.h
===================================================================
--- linux-2.6.git.orig/arch/x86/include/uapi/asm/kvm_para.h	2019-01-04 12:07:15.936947406 -0200
+++ linux-2.6.git/arch/x86/include/uapi/asm/kvm_para.h	2019-06-03 19:37:49.620543534 -0300
@@ -29,6 +29,7 @@
 #define KVM_FEATURE_PV_TLB_FLUSH	9
 #define KVM_FEATURE_ASYNC_PF_VMEXIT	10
 #define KVM_FEATURE_PV_SEND_IPI	11
+#define KVM_FEATURE_POLL_CONTROL	12
 
 #define KVM_HINTS_REALTIME      0
 
@@ -47,6 +48,7 @@
 #define MSR_KVM_ASYNC_PF_EN 0x4b564d02
 #define MSR_KVM_STEAL_TIME  0x4b564d03
 #define MSR_KVM_PV_EOI_EN      0x4b564d04
+#define MSR_KVM_POLL_CONTROL	0x4b564d05
 
 struct kvm_steal_time {
 	__u64 steal;
Index: linux-2.6.git/arch/x86/kvm/Kconfig
===================================================================
--- linux-2.6.git.orig/arch/x86/kvm/Kconfig	2019-05-29 14:46:14.530005593 -0300
+++ linux-2.6.git/arch/x86/kvm/Kconfig	2019-06-03 19:37:49.620543534 -0300
@@ -41,6 +41,7 @@
 	select PERF_EVENTS
 	select HAVE_KVM_MSI
 	select HAVE_KVM_CPU_RELAX_INTERCEPT
+	select HAVE_KVM_NO_POLL
 	select KVM_GENERIC_DIRTYLOG_READ_PROTECT
 	select KVM_VFIO
 	select SRCU
Index: linux-2.6.git/arch/x86/kvm/cpuid.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kvm/cpuid.c	2019-05-29 14:46:14.530005593 -0300
+++ linux-2.6.git/arch/x86/kvm/cpuid.c	2019-06-03 19:37:49.621543537 -0300
@@ -643,7 +643,8 @@
 			     (1 << KVM_FEATURE_PV_UNHALT) |
 			     (1 << KVM_FEATURE_PV_TLB_FLUSH) |
 			     (1 << KVM_FEATURE_ASYNC_PF_VMEXIT) |
-			     (1 << KVM_FEATURE_PV_SEND_IPI);
+			     (1 << KVM_FEATURE_PV_SEND_IPI) |
+			     (1 << KVM_FEATURE_POLL_CONTROL);
 
 		if (sched_info_on())
 			entry->eax |= (1 << KVM_FEATURE_STEAL_TIME);
Index: linux-2.6.git/arch/x86/kvm/x86.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kvm/x86.c	2019-05-29 14:46:14.537005616 -0300
+++ linux-2.6.git/arch/x86/kvm/x86.c	2019-06-03 19:37:49.624543547 -0300
@@ -1177,6 +1177,7 @@
 	MSR_IA32_POWER_CTL,
 
 	MSR_K7_HWCR,
+	MSR_KVM_POLL_CONTROL,
 };
 
 static unsigned num_emulated_msrs;
@@ -2628,6 +2629,14 @@
 			return 1;
 		break;
 
+	case MSR_KVM_POLL_CONTROL:
+		/* only enable bit supported */
+		if (data & (-1ULL << 1))
+			return 1;
+
+		vcpu->arch.msr_kvm_poll_control = data;
+		break;
+
 	case MSR_IA32_MCG_CTL:
 	case MSR_IA32_MCG_STATUS:
 	case MSR_IA32_MC0_CTL ... MSR_IA32_MCx_CTL(KVM_MAX_MCE_BANKS) - 1:
@@ -2877,6 +2886,9 @@
 	case MSR_KVM_PV_EOI_EN:
 		msr_info->data = vcpu->arch.pv_eoi.msr_val;
 		break;
+	case MSR_KVM_POLL_CONTROL:
+		msr_info->data = vcpu->arch.msr_kvm_poll_control;
+		break;
 	case MSR_IA32_P5_MC_ADDR:
 	case MSR_IA32_P5_MC_TYPE:
 	case MSR_IA32_MCG_CAP:
@@ -8874,6 +8886,10 @@
 	msr.host_initiated = true;
 	kvm_write_tsc(vcpu, &msr);
 	vcpu_put(vcpu);
+
+	/* poll control enabled by default */
+	vcpu->arch.msr_kvm_poll_control = 1;
+
 	mutex_unlock(&vcpu->mutex);
 
 	if (!kvmclock_periodic_sync)
@@ -9948,6 +9964,13 @@
 }
 EXPORT_SYMBOL_GPL(kvm_vector_hashing_enabled);
 
+bool kvm_arch_no_poll(struct kvm_vcpu *vcpu)
+{
+	return (vcpu->arch.msr_kvm_poll_control & 1) == 0;
+}
+EXPORT_SYMBOL_GPL(kvm_arch_no_poll);
+
+
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_exit);
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_fast_mmio);
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_inj_virq);

From patchwork Mon Jun  3 22:52:45 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10974067
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D6F215E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:26 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id EEAF52874A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:25 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id E26DF2875C; Mon,  3 Jun 2019 23:01:25 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 6E2352875F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Jun 2019 23:01:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726502AbfFCXBW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Jun 2019 19:01:22 -0400
Received: from mx1.redhat.com ([209.132.183.28]:40138 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726102AbfFCXBV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Jun 2019 19:01:21 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 133EB30821FF;
        Mon,  3 Jun 2019 23:01:21 +0000 (UTC)
Received: from amt.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 598D617154;
        Mon,  3 Jun 2019 23:01:20 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 55BB3105165;
        Mon,  3 Jun 2019 19:54:58 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x53MswxR007684;
        Mon, 3 Jun 2019 19:54:58 -0300
Message-Id: <20190603225254.360289262@amt.cnet>
User-Agent: quilt/0.60-1
Date: Mon, 03 Jun 2019 19:52:45 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>, =?iso-8859-15?q?Radim_Kr=C4=8Dm=C3?=
	=?iso-8859-15?q?=A1=C5=99?=  <rkrcmar@redhat.com>,
 Andrea Arcangeli <aarcange@redhat.com>,
 "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>,
 Peter Zijlstra <peterz@infradead.org>, Wanpeng Li <kernellwp@gmail.com>,
 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
 Raslan KarimAllah <karahmed@amazon.de>,
 Boris Ostrovsky <boris.ostrovsky@oracle.com>,
 Ankur Arora <ankur.a.arora@oracle.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 3/3] cpuidle-haltpoll: disable host side polling when kvm
 virtualized
References: <20190603225242.289109849@amt.cnet>
Content-Disposition: inline; filename=03-pollcontrol-guest.patch
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.47]);
 Mon, 03 Jun 2019 23:01:21 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

When performing guest side polling, it is not necessary to 
also perform host side polling. 

So disable host side polling, via the new MSR interface, 
when loading cpuidle-haltpoll driver.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 arch/x86/Kconfig                        |    7 +++++
 arch/x86/include/asm/cpuidle_haltpoll.h |    8 ++++++
 arch/x86/kernel/kvm.c                   |   40 ++++++++++++++++++++++++++++++++
 drivers/cpuidle/cpuidle-haltpoll.c      |    9 ++++++-
 include/linux/cpuidle_haltpoll.h        |   16 ++++++++++++
 5 files changed, 79 insertions(+), 1 deletion(-)

Index: linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h	2019-06-03 19:38:42.328718617 -0300
@@ -0,0 +1,8 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _ARCH_HALTPOLL_H
+#define _ARCH_HALTPOLL_H
+
+void arch_haltpoll_enable(void);
+void arch_haltpoll_disable(void);
+
+#endif
Index: linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-03 19:38:42.328718617 -0300
@@ -15,6 +15,7 @@
 #include <linux/module.h>
 #include <linux/timekeeping.h>
 #include <linux/sched/idle.h>
+#include <linux/cpuidle_haltpoll.h>
 #define CREATE_TRACE_POINTS
 #include "cpuidle-haltpoll-trace.h"
 
@@ -157,11 +158,17 @@
 
 static int __init haltpoll_init(void)
 {
-	return cpuidle_register(&haltpoll_driver, NULL);
+	int ret = cpuidle_register(&haltpoll_driver, NULL);
+
+	if (ret == 0)
+		arch_haltpoll_enable();
+
+	return ret;
 }
 
 static void __exit haltpoll_exit(void)
 {
+	arch_haltpoll_disable();
 	cpuidle_unregister(&haltpoll_driver);
 }
 
Index: linux-2.6.git/include/linux/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/include/linux/cpuidle_haltpoll.h	2019-06-03 19:41:57.293366260 -0300
@@ -0,0 +1,16 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _CPUIDLE_HALTPOLL_H
+#define _CPUIDLE_HALTPOLL_H
+
+#ifdef CONFIG_ARCH_CPUIDLE_HALTPOLL
+#include <asm/cpuidle_haltpoll.h>
+#else
+static inline void arch_haltpoll_enable(void)
+{
+}
+
+static inline void arch_haltpoll_disable(void)
+{
+}
+#endif
+#endif
Index: linux-2.6.git/arch/x86/Kconfig
===================================================================
--- linux-2.6.git.orig/arch/x86/Kconfig	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/arch/x86/Kconfig	2019-06-03 19:42:34.478489868 -0300
@@ -787,6 +787,7 @@
 	bool "KVM Guest support (including kvmclock)"
 	depends on PARAVIRT
 	select PARAVIRT_CLOCK
+	select ARCH_CPUIDLE_HALTPOLL
 	default y
 	---help---
 	  This option enables various optimizations for running under the KVM
@@ -795,6 +796,12 @@
 	  underlying device model, the host provides the guest with
 	  timing infrastructure such as time of day, and system time
 
+config ARCH_CPUIDLE_HALTPOLL
+        def_bool n
+        prompt "Disable host haltpoll when loading haltpoll driver"
+        help
+	  If virtualized under KVM, disable host haltpoll.
+
 config PVH
 	bool "Support for running PVH guests"
 	---help---
Index: linux-2.6.git/arch/x86/kernel/kvm.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kernel/kvm.c	2019-06-03 19:38:12.376619124 -0300
+++ linux-2.6.git/arch/x86/kernel/kvm.c	2019-06-03 19:40:14.359024312 -0300
@@ -853,3 +853,43 @@
 }
 
 #endif	/* CONFIG_PARAVIRT_SPINLOCKS */
+
+#ifdef CONFIG_ARCH_CPUIDLE_HALTPOLL
+
+void kvm_disable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 0);
+}
+
+void kvm_enable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 1);
+}
+
+void arch_haltpoll_enable(void)
+{
+	if (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL))
+		return;
+
+	preempt_disable();
+	/* Enabling guest halt poll disables host halt poll */
+	kvm_disable_host_haltpoll(NULL);
+	smp_call_function(kvm_disable_host_haltpoll, NULL, 1);
+	preempt_enable();
+}
+EXPORT_SYMBOL_GPL(arch_haltpoll_enable);
+
+void arch_haltpoll_disable(void)
+{
+	if (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL))
+		return;
+
+	preempt_disable();
+	/* Enabling guest halt poll disables host halt poll */
+	kvm_enable_host_haltpoll(NULL);
+	smp_call_function(kvm_enable_host_haltpoll, NULL, 1);
+	preempt_enable();
+}
+}
+EXPORT_SYMBOL_GPL(arch_haltpoll_disable);
+#endif
```
#### [PATCH kvm-unit-tests] arm64: timer: a few test improvements
##### From: Andrew Jones <drjones@redhat.com>

```c
1) Ensure set_timer_irq_enabled() clears the pending interrupt
   from the gic before proceeding with the next test.
2) Inform user we're about to wait for an interrupt - just in
   case we never come back...
3) Allow the user to choose just vtimer or just ptimer tests,
   or to reverse their order with -append 'ptimer vtimer'.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/timer.c | 17 +++++++++++++++--
 1 file changed, 15 insertions(+), 2 deletions(-)

```
#### [RFC][Patch v10 1/2] mm: page_hinting: core infrastructure
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch introduces the core infrastructure for free page hinting in
virtual environments. It enables the kernel to track the free pages which
can be reported to its hypervisor so that the hypervisor could
free and reuse that memory as per its requirement.

While the pages are getting processed in the hypervisor (e.g.,
via MADV_FREE), the guest must not use them, otherwise, data loss
would be possible. To avoid such a situation, these pages are
temporarily removed from the buddy. The amount of pages removed
temporarily from the buddy is governed by the backend(virtio-balloon
in our case).

To efficiently identify free pages that can to be hinted to the
hypervisor, bitmaps in a coarse granularity are used. Only fairly big
chunks are reported to the hypervisor - especially, to not break up THP
in the hypervisor - "MAX_ORDER - 2" on x86, and to save space. The bits
in the bitmap are an indication whether a page *might* be free, not a
guarantee. A new hook after buddy merging sets the bits.

Bitmaps are stored per zone, protected by the zone lock. A workqueue
asynchronously processes the bitmaps, trying to isolate and report pages
that are still free. The backend (virtio-balloon) is responsible for
reporting these batched pages to the host synchronously. Once reporting/
freeing is complete, isolated pages are returned back to the buddy.

There are still various things to look into (e.g., memory hotplug, more
efficient locking, possible races when disabling).

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 drivers/virtio/Kconfig       |   1 +
 include/linux/page_hinting.h |  46 +++++++
 mm/Kconfig                   |   6 +
 mm/Makefile                  |   2 +
 mm/page_alloc.c              |  17 +--
 mm/page_hinting.c            | 236 +++++++++++++++++++++++++++++++++++
 6 files changed, 301 insertions(+), 7 deletions(-)
 create mode 100644 include/linux/page_hinting.h
 create mode 100644 mm/page_hinting.c

```
#### [PULL 1/7] s390/cio: Update SCSW if it points to the end of the chain
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Eric Farman <farman@linux.ibm.com>

Per the POPs [1], when processing an interrupt the SCSW.CPA field of an
IRB generally points to 8 bytes after the last CCW that was executed
(there are exceptions, but this is the most common behavior).

In the case of an error, this points us to the first un-executed CCW
in the chain.  But in the case of normal I/O, the address points beyond
the end of the chain.  While the guest generally only cares about this
when possibly restarting a channel program after error recovery, we
should convert the address even in the good scenario so that we provide
a consistent, valid, response upon I/O completion.

[1] Figure 16-6 in SA22-7832-11.  The footnotes in that table also state
that this is true even if the resulting address is invalid or protected,
but moving to the end of the guest chain should not be a surprise.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Message-Id: <20190514234248.36203-2-farman@linux.ibm.com>
Reviewed-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [patch QEMU] kvm: i386: halt poll control MSR support
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Add support for halt poll control MSR: save/restore, migration 
and new feature name.

The purpose of this MSR is to allow the guest to disable
host halt poll.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

```
#### [QEMU PATCH] KVM: Support for page hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Enables QEMU to call madvise on the pages which are reported
by the guest kernel.

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 hw/virtio/trace-events                        |  1 +
 hw/virtio/virtio-balloon.c                    | 85 +++++++++++++++++++
 include/hw/virtio/virtio-balloon.h            |  2 +-
 include/qemu/osdep.h                          |  7 ++
 .../standard-headers/linux/virtio_balloon.h   |  1 +
 5 files changed, 95 insertions(+), 1 deletion(-)

```
#### [PATCH v1 1/1] vfio-ccw: Destroy kmem cache region on module exit
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
Free the vfio_ccw_cmd_region on module exit.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---

I guess I missed this earlier while reviewing, but should'nt 
we destroy the vfio_ccw_cmd_region on module exit, as well?

 drivers/s390/cio/vfio_ccw_drv.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCHv6 1/3] vfio/mdev: Improve the create/remove sequence
##### From: Parav Pandit <parav@mellanox.com>

```c
This patch addresses below two issues and prepares the code to address
3rd issue listed below.

1. mdev device is placed on the mdev bus before it is created in the
vendor driver. Once a device is placed on the mdev bus without creating
its supporting underlying vendor device, mdev driver's probe() gets triggered.
However there isn't a stable mdev available to work on.

   create_store()
     mdev_create_device()
       device_register()
          ...
         vfio_mdev_probe()
        [...]
        parent->ops->create()
          vfio_ap_mdev_create()
            mdev_set_drvdata(mdev, matrix_mdev);
            /* Valid pointer set above */

Due to this way of initialization, mdev driver who wants to use the mdev,
doesn't have a valid mdev to work on.

2. Current creation sequence is,
   parent->ops_create()
   groups_register()

Remove sequence is,
   parent->ops->remove()
   groups_unregister()

However, remove sequence should be exact mirror of creation sequence.
Once this is achieved, all users of the mdev will be terminated first
before removing underlying vendor device.
(Follow standard linux driver model).
At that point vendor's remove() ops shouldn't fail because taking the
device off the bus should terminate any usage.

3. When remove operation fails, mdev sysfs removal attempts to add the
file back on already removed device. Following call trace [1] is observed.

[1] call trace:
kernel: WARNING: CPU: 2 PID: 9348 at fs/sysfs/file.c:327 sysfs_create_file_ns+0x7f/0x90
kernel: CPU: 2 PID: 9348 Comm: bash Kdump: loaded Not tainted 5.1.0-rc6-vdevbus+ #6
kernel: Hardware name: Supermicro SYS-6028U-TR4+/X10DRU-i+, BIOS 2.0b 08/09/2016
kernel: RIP: 0010:sysfs_create_file_ns+0x7f/0x90
kernel: Call Trace:
kernel: remove_store+0xdc/0x100 [mdev]
kernel: kernfs_fop_write+0x113/0x1a0
kernel: vfs_write+0xad/0x1b0
kernel: ksys_write+0x5a/0xe0
kernel: do_syscall_64+0x5a/0x210
kernel: entry_SYSCALL_64_after_hwframe+0x49/0xbe

Therefore, mdev core is improved in following ways.

1. Split the device registration/deregistration sequence so that some
things can be done between initialization of the device and hooking it
up to the bus respectively after deregistering it from the bus but
before giving up our final reference.
In particular, this means invoking the ->create() and ->remove()
callbacks in those new windows. This gives the vendor driver an
initialized mdev device to work with during creation.
At the same time, a bus driver who wish to bind to mdev driver also
gets initialized mdev device.

This follows standard Linux kernel bus and device model.

2. During remove flow, first remove the device from the bus. This
ensures that any bus specific devices are removed.
Once device is taken off the mdev bus, invoke remove() of mdev
from the vendor driver.

3. The driver core device model provides way to register and auto
unregister the device sysfs attribute groups at dev->groups.
Make use of dev->groups to let core create the groups and eliminate
code to avoid explicit groups creation and removal.

To ensure, that new sequence is solid, a below stack dump of a
process is taken who attempts to remove the device while device is in
use by vfio driver and user application.
This stack dump validates that vfio driver guards against such device
removal when device is in use.

 cat /proc/21962/stack
[<0>] vfio_del_group_dev+0x216/0x3c0 [vfio]
[<0>] mdev_remove+0x21/0x40 [mdev]
[<0>] device_release_driver_internal+0xe8/0x1b0
[<0>] bus_remove_device+0xf9/0x170
[<0>] device_del+0x168/0x350
[<0>] mdev_device_remove_common+0x1d/0x50 [mdev]
[<0>] mdev_device_remove+0x8c/0xd0 [mdev]
[<0>] remove_store+0x71/0x90 [mdev]
[<0>] kernfs_fop_write+0x113/0x1a0
[<0>] vfs_write+0xad/0x1b0
[<0>] ksys_write+0x5a/0xe0
[<0>] do_syscall_64+0x5a/0x210
[<0>] entry_SYSCALL_64_after_hwframe+0x49/0xbe
[<0>] 0xffffffffffffffff

This prepares the code to eliminate calling device_create_file() in
subsequent patch.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c    | 94 +++++++++-----------------------
 drivers/vfio/mdev/mdev_private.h |  2 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  2 +-
 3 files changed, 27 insertions(+), 71 deletions(-)

```
