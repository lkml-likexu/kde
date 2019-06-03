#### [patch 1/3] drivers/cpuidle: add cpuidle-haltpoll driverReferences: <20190611194054.878923294@amt.cnet>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
The cpuidle_haltpoll driver allows the guest vcpus to poll for a specified
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
 Documentation/virtual/guest-halt-polling.txt |   96 +++++++++++++++++
 arch/x86/kernel/process.c                    |    2 
 drivers/cpuidle/Kconfig                      |    9 +
 drivers/cpuidle/Makefile                     |    1 
 drivers/cpuidle/cpuidle-haltpoll.c           |  145 +++++++++++++++++++++++++++
 5 files changed, 252 insertions(+), 1 deletion(-)

Index: linux-2.6.git/Documentation/virtual/guest-halt-polling.txt
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/Documentation/virtual/guest-halt-polling.txt	2019-06-11 16:38:55.072877644 -0300
@@ -0,0 +1,96 @@
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
+	2) The VM-exit cost can be avoided.
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
+
+Maximum amount of time, in nanoseconds, that polling is
+performed before halting.
+
+Default: 0
+
+2) guest_halt_poll_shrink:
+
+Division factor used to shrink per-cpu guest_halt_poll_ns when
+wakeup event occurs after the global guest_halt_poll_ns.
+
+Default: 2
+
+3) guest_halt_poll_grow:
+
+Multiplication factor used to grow per-cpu guest_halt_poll_ns
+when event occurs after per-cpu guest_halt_poll_ns
+but before global guest_halt_poll_ns.
+
+Default: 2
+
+4) guest_halt_poll_grow_start:
+
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
+Host and guest polling
+======================
+
+KVM also performs host side polling (that is, it can poll for a certain
+amount of time before halting) on behalf of guest vcpus.
+
+Modern hosts support poll control MSRs, which are used by
+cpuidle_haltpoll to disable host side polling on a per-VM basis.
+
+If the KVM host does not support this interface, then both guest side
+and host side polling can be performed, which can incur extra CPU and
+energy consumption. One might consider disabling host side polling
+manually if upgrading to a new host is not an option.
+
+Further Notes
+=============
+
+Care should be taken when setting the guest_halt_poll_ns parameter
+as a large value has the potential to drive the cpu usage to 100% on a
+machine which would be almost entirely idle otherwise.
+
Index: linux-2.6.git/arch/x86/kernel/process.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kernel/process.c	2019-06-11 12:14:37.731286353 -0300
+++ linux-2.6.git/arch/x86/kernel/process.c	2019-06-11 12:14:44.699424799 -0300
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
--- linux-2.6.git.orig/drivers/cpuidle/Kconfig	2019-06-11 12:14:37.731286353 -0300
+++ linux-2.6.git/drivers/cpuidle/Kconfig	2019-06-11 16:38:13.984060707 -0300
@@ -51,6 +51,15 @@
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
 endif
 
 config ARCH_NEEDS_CPU_IDLE_COUPLED
Index: linux-2.6.git/drivers/cpuidle/Makefile
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/Makefile	2019-06-11 12:14:37.731286353 -0300
+++ linux-2.6.git/drivers/cpuidle/Makefile	2019-06-11 12:14:44.700424819 -0300
@@ -7,6 +7,7 @@
 obj-$(CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED) += coupled.o
 obj-$(CONFIG_DT_IDLE_STATES)		  += dt_idle_states.o
 obj-$(CONFIG_ARCH_HAS_CPU_RELAX)	  += poll_state.o
+obj-$(CONFIG_HALTPOLL_CPUIDLE)		  += cpuidle-haltpoll.o
 
 ##################################################################################
 # ARM SoC drivers
Index: linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-11 16:37:23.328053569 -0300
@@ -0,0 +1,145 @@
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
+#include <linux/sched/clock.h>
+#include <linux/sched/idle.h>
+
+static unsigned int guest_halt_poll_ns __read_mostly = 200000;
+module_param(guest_halt_poll_ns, uint, 0644);
+
+/* division factor to shrink halt_poll_ns */
+static unsigned int guest_halt_poll_shrink __read_mostly = 2;
+module_param(guest_halt_poll_shrink, uint, 0644);
+
+/* multiplication factor to grow per-cpu halt_poll_ns */
+static unsigned int guest_halt_poll_grow __read_mostly = 2;
+module_param(guest_halt_poll_grow, uint, 0644);
+
+/* value in ns to start growing per-cpu halt_poll_ns */
+static unsigned int guest_halt_poll_grow_start __read_mostly = 10000;
+module_param(guest_halt_poll_grow_start, uint, 0644);
+
+/* value in ns to start growing per-cpu halt_poll_ns */
+static bool guest_halt_poll_allow_shrink __read_mostly = true;
+module_param(guest_halt_poll_allow_shrink, bool, 0644);
+
+static DEFINE_PER_CPU(unsigned int, halt_poll_ns);
+
+static void adjust_haltpoll_ns(unsigned int block_ns,
+			       unsigned int *cpu_halt_poll_ns)
+{
+	unsigned int val;
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
+}
+
+static int haltpoll_enter_idle(struct cpuidle_device *dev,
+			       struct cpuidle_driver *drv, int index)
+{
+	unsigned int *cpu_halt_poll_ns;
+	unsigned long long start, now, block_ns;
+	int cpu = smp_processor_id();
+
+	cpu_halt_poll_ns = per_cpu_ptr(&halt_poll_ns, cpu);
+
+	if (current_set_polling_and_test()) {
+		local_irq_enable();
+		goto out;
+	}
+
+	start = sched_clock();
+	local_irq_enable();
+	for (;;) {
+		if (need_resched()) {
+			current_clr_polling();
+			goto out;
+		}
+
+		now = sched_clock();
+		if (now - start > *cpu_halt_poll_ns)
+			break;
+
+		cpu_relax();
+	}
+
+	local_irq_disable();
+	if (current_clr_polling_and_test()) {
+		local_irq_enable();
+		goto out;
+	}
+
+	default_idle();
+	block_ns = sched_clock() - start;
+	adjust_haltpoll_ns(block_ns, cpu_halt_poll_ns);
+
+out:
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

From patchwork Tue Jun 11 19:40:56 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10988253
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A8CD413AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:36 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 981CA28783
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:36 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 8C76228789; Tue, 11 Jun 2019 19:42:36 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 0DE442877F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405705AbfFKTme (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Jun 2019 15:42:34 -0400
Received: from mx1.redhat.com ([209.132.183.28]:45168 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389150AbfFKTmd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Jun 2019 15:42:33 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id D48823082B15;
        Tue, 11 Jun 2019 19:42:32 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 181AC1001B03;
        Tue, 11 Jun 2019 19:42:30 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 3811A105153;
        Tue, 11 Jun 2019 16:42:15 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5BJgE7h011942;
        Tue, 11 Jun 2019 16:42:14 -0300
Message-Id: <20190611194107.343397521@amt.cnet>
User-Agent: quilt/0.60-1
Date: Tue, 11 Jun 2019 16:40:56 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Radim Krcmar <rkrcmar@redhat.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Wanpeng Li <kernellwp@gmail.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Raslan KarimAllah <karahmed@amazon.de>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-pm@vger.kernel.org, Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 2/3] kvm: x86: add host poll control msrs
References: <20190611194054.878923294@amt.cnet>
Content-Disposition: inline; filename=02-pollcontrol-host.patch
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Tue, 11 Jun 2019 19:42:32 +0000 (UTC)
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
 arch/x86/kvm/x86.c                   |   22 ++++++++++++++++++++++
 6 files changed, 38 insertions(+), 1 deletion(-)

Index: linux-2.6.git/Documentation/virtual/kvm/msr.txt
===================================================================
--- linux-2.6.git.orig/Documentation/virtual/kvm/msr.txt	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/Documentation/virtual/kvm/msr.txt	2019-06-11 16:04:09.917453903 -0300
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
--- linux-2.6.git.orig/arch/x86/include/asm/kvm_host.h	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/arch/x86/include/asm/kvm_host.h	2019-06-11 16:04:09.917453903 -0300
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
--- linux-2.6.git.orig/arch/x86/include/uapi/asm/kvm_para.h	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/arch/x86/include/uapi/asm/kvm_para.h	2019-06-11 16:04:09.917453903 -0300
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
--- linux-2.6.git.orig/arch/x86/kvm/Kconfig	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/arch/x86/kvm/Kconfig	2019-06-11 16:04:09.917453903 -0300
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
--- linux-2.6.git.orig/arch/x86/kvm/cpuid.c	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/arch/x86/kvm/cpuid.c	2019-06-11 16:04:09.918453923 -0300
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
--- linux-2.6.git.orig/arch/x86/kvm/x86.c	2019-06-11 15:54:16.500695464 -0300
+++ linux-2.6.git/arch/x86/kvm/x86.c	2019-06-11 16:04:48.002209329 -0300
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
@@ -9948,6 +9964,12 @@
 }
 EXPORT_SYMBOL_GPL(kvm_vector_hashing_enabled);
 
+bool kvm_arch_no_poll(struct kvm_vcpu *vcpu)
+{
+	return (vcpu->arch.msr_kvm_poll_control & 1) == 0;
+}
+EXPORT_SYMBOL_GPL(kvm_arch_no_poll);
+
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_exit);
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_fast_mmio);
 EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_inj_virq);

From patchwork Tue Jun 11 19:40:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10988247
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 564631708
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:35 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 4651F2877F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:35 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 39F4428783; Tue, 11 Jun 2019 19:42:35 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id AED322877F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Jun 2019 19:42:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391554AbfFKTmd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Jun 2019 15:42:33 -0400
Received: from mx1.redhat.com ([209.132.183.28]:35966 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2391042AbfFKTmd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Jun 2019 15:42:33 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E22E859474;
        Tue, 11 Jun 2019 19:42:32 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 18205614D9;
        Tue, 11 Jun 2019 19:42:30 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id C8BFC105157;
        Tue, 11 Jun 2019 16:42:15 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5BJgFEK011943;
        Tue, 11 Jun 2019 16:42:15 -0300
Message-Id: <20190611194107.423384855@amt.cnet>
User-Agent: quilt/0.60-1
Date: Tue, 11 Jun 2019 16:40:57 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Radim Krcmar <rkrcmar@redhat.com>,
        Andrea Arcangeli <aarcange@redhat.com>,
        "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Wanpeng Li <kernellwp@gmail.com>,
        Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
        Raslan KarimAllah <karahmed@amazon.de>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-pm@vger.kernel.org, Marcelo Tosatti <mtosatti@redhat.com>
Subject: [patch 3/3] cpuidle-haltpoll: disable host side polling when kvm
 virtualized
References: <20190611194054.878923294@amt.cnet>
Content-Disposition: inline; filename=03-pollcontrol-guest.patch
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.39]);
 Tue, 11 Jun 2019 19:42:33 +0000 (UTC)
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
 arch/x86/kernel/kvm.c                   |   42 ++++++++++++++++++++++++++++++++
 drivers/cpuidle/cpuidle-haltpoll.c      |    9 ++++++
 include/linux/cpuidle_haltpoll.h        |   16 ++++++++++++
 5 files changed, 81 insertions(+), 1 deletion(-)

Index: linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h	2019-06-11 16:05:13.024705702 -0300
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
--- linux-2.6.git.orig/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-11 16:04:02.000000000 -0300
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-11 16:05:41.711274798 -0300
@@ -15,6 +15,7 @@
 #include <linux/module.h>
 #include <linux/sched/clock.h>
 #include <linux/sched/idle.h>
+#include <linux/cpuidle_haltpoll.h>
 
 static unsigned int guest_halt_poll_ns __read_mostly = 200000;
 module_param(guest_halt_poll_ns, uint, 0644);
@@ -130,11 +131,17 @@
 
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
+++ linux-2.6.git/include/linux/cpuidle_haltpoll.h	2019-06-11 16:05:13.025705722 -0300
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
--- linux-2.6.git.orig/arch/x86/Kconfig	2019-06-11 15:53:31.000000000 -0300
+++ linux-2.6.git/arch/x86/Kconfig	2019-06-11 16:05:13.026705742 -0300
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
--- linux-2.6.git.orig/arch/x86/kernel/kvm.c	2019-06-11 15:53:31.000000000 -0300
+++ linux-2.6.git/arch/x86/kernel/kvm.c	2019-06-11 16:05:13.026705742 -0300
@@ -853,3 +853,45 @@
 }
 
 #endif	/* CONFIG_PARAVIRT_SPINLOCKS */
+
+#ifdef CONFIG_ARCH_CPUIDLE_HALTPOLL
+
+static void kvm_disable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 0);
+}
+
+static void kvm_enable_host_haltpoll(void *i)
+{
+	wrmsrl(MSR_KVM_POLL_CONTROL, 1);
+}
+
+void arch_haltpoll_enable(void)
+{
+	if (!kvm_para_has_feature(KVM_FEATURE_POLL_CONTROL)) {
+		printk(KERN_ERR "kvm: host does not support poll control\n");
+		printk(KERN_ERR "kvm: host upgrade recommended\n");
+		return;
+	}
+
+	preempt_disable();
+	/* Enable guest halt poll disables host halt poll */
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
+	/* Enable guest halt poll disables host halt poll */
+	kvm_enable_host_haltpoll(NULL);
+	smp_call_function(kvm_enable_host_haltpoll, NULL, 1);
+	preempt_enable();
+}
+EXPORT_SYMBOL_GPL(arch_haltpoll_disable);
+#endif
```
#### [GIT PULL] VFIO fixes for v5.2-rc5
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit f2c7c76c5d0a443053e94adb9f0918fa2fb85c3a:

  Linux 5.2-rc3 (2019-06-02 13:55:33 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.2-rc5

for you to fetch changes up to 5715c4dd66a315515eedef3fc4cbe1bf4620f009:

  vfio/mdev: Synchronize device create/remove with parent removal (2019-06-06 12:32:37 -0600)

----------------------------------------------------------------
VFIO fixes for v5.2-rc5

 - Fix mdev device create/remove paths to provide initialized device for
   parent driver create callback and correct ordering of device removal
   from bus prior to initiating removal by parent.  Also resolve races
   between parent removal and device create/remove paths. (Parav Pandit)

----------------------------------------------------------------
Parav Pandit (3):
      vfio/mdev: Improve the create/remove sequence
      vfio/mdev: Avoid creating sysfs remove file on stale device removal
      vfio/mdev: Synchronize device create/remove with parent removal

 drivers/vfio/mdev/mdev_core.c    | 136 ++++++++++++++++++---------------------
 drivers/vfio/mdev/mdev_private.h |   4 +-
 drivers/vfio/mdev/mdev_sysfs.c   |   6 +-
 3 files changed, 69 insertions(+), 77 deletions(-)
```
#### [PATCH v2 1/9] KVM: arm/arm64: vgic: Add LPI translation cache definition
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Add the basic data structure that expresses an MSI to LPI
translation as well as the allocation/release hooks.

THe size of the cache is arbitrarily defined as 4*nr_vcpus.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 include/kvm/arm_vgic.h        |  3 +++
 virt/kvm/arm/vgic/vgic-init.c |  5 ++++
 virt/kvm/arm/vgic/vgic-its.c  | 49 +++++++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic.h      |  2 ++
 4 files changed, 59 insertions(+)

```
#### [PATCH v3 1/4] KVM: LAPIC: Make lapic timer unpinned when timer is injected by pi
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Make lapic timer unpinned when timer is injected by posted-interrupt,
the emulated timer can be offload to the housekeeping cpus.

The host admin should fine tuned, e.g. dedicated instances scenario 
w/ nohz_full cover the pCPUs which vCPUs resident, several pCPUs 
surplus for housekeeping, disable mwait/hlt/pause vmexits to occupy 
the pCPUs, fortunately preemption timer is disabled after mwait is 
exposed to guest which makes emulated timer offload can be possible. 

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c            | 20 ++++++++++++++++----
 arch/x86/kvm/lapic.h            |  1 +
 arch/x86/kvm/vmx/vmx.c          |  3 ++-
 arch/x86/kvm/x86.c              |  5 +++++
 arch/x86/kvm/x86.h              |  2 ++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 ++++++
 7 files changed, 34 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/5] KVM: X86: Dynamic allocate core residency msr state
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Dynamic allocate core residency msr state. MSR_CORE_C1_RES is unreadable 
except for ATOM platform, so it is ignore here.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h | 11 +++++++++++
 arch/x86/kvm/vmx/vmx.c          |  5 +++++
 2 files changed, 16 insertions(+)

```
#### [PATCH v4 1/3] KVM: X86: Yield to IPI target if necessary
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

When sending a call-function IPI-many to vCPUs, yield if any of
the IPI target vCPUs was preempted, we just select the first
preempted target vCPU which we found since the state of target
vCPUs can change underneath and to avoid race conditions.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 Documentation/virtual/kvm/hypercalls.txt | 11 +++++++++++
 arch/x86/include/uapi/asm/kvm_para.h     |  1 +
 arch/x86/kernel/kvm.c                    | 21 +++++++++++++++++++++
 include/uapi/linux/kvm_para.h            |  1 +
 4 files changed, 34 insertions(+)

```
#### [PATCH V2] include: linux: Regularise the use of FIELD_SIZEOF macro
##### From: Shyam Saini <shyam.saini@amarulasolutions.com>

```c
Currently, there are 3 different macros, namely sizeof_field, SIZEOF_FIELD
and FIELD_SIZEOF which are used to calculate the size of a member of
structure, so to bring uniformity in entire kernel source tree lets use
FIELD_SIZEOF and replace all occurrences of other two macros with this.

For this purpose, redefine FIELD_SIZEOF in include/linux/stddef.h and
tools/testing/selftests/bpf/bpf_util.h and remove its defination from
include/linux/kernel.h

In favour of FIELD_SIZEOF, this patch also deprecates other two similar
macros sizeof_field and SIZEOF_FIELD.

For code compatibility reason, retain sizeof_field macro as a wrapper macro
to FIELD_SIZEOF

Signed-off-by: Shyam Saini <shyam.saini@amarulasolutions.com>
---
Changelog:

V1->V2
- Consolidate previous patch 1 and 2 into single patch
- For code compatibility reason, retain sizeof_field macro as a
  wrapper macro to FIELD_SIZEOF
 
 arch/arm64/include/asm/processor.h                 | 10 +++++-----
 arch/mips/cavium-octeon/executive/cvmx-bootmem.c   |  9 +--------
 drivers/gpu/drm/i915/gvt/scheduler.c               |  2 +-
 drivers/net/ethernet/mellanox/mlxsw/spectrum_fid.c |  4 ++--
 fs/befs/linuxvfs.c                                 |  2 +-
 fs/ext2/super.c                                    |  2 +-
 fs/ext4/super.c                                    |  2 +-
 fs/freevxfs/vxfs_super.c                           |  2 +-
 fs/orangefs/super.c                                |  2 +-
 fs/ufs/super.c                                     |  2 +-
 include/linux/kernel.h                             |  9 ---------
 include/linux/slab.h                               |  2 +-
 include/linux/stddef.h                             | 17 ++++++++++++++---
 kernel/fork.c                                      |  2 +-
 kernel/utsname.c                                   |  2 +-
 net/caif/caif_socket.c                             |  2 +-
 net/core/skbuff.c                                  |  2 +-
 net/ipv4/raw.c                                     |  2 +-
 net/ipv6/raw.c                                     |  2 +-
 net/sctp/socket.c                                  |  4 ++--
 tools/testing/selftests/bpf/bpf_util.h             | 22 +++++++++++++++++++---
 virt/kvm/kvm_main.c                                |  2 +-
 22 files changed, 58 insertions(+), 47 deletions(-)

```
#### [PATCH v12 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
#### [PATCH] x86/hyperv: Disable preemption while setting reenlightenment vector
##### From: Dmitry Safonov <dima@arista.com>

```c
KVM support may be compiled as dynamic module, which triggers the
following splat on modprobe:

 KVM: vmx: using Hyper-V Enlightened VMCS
 BUG: using smp_processor_id() in preemptible [00000000] code: modprobe/466 caller is debug_smp_processor_id+0x17/0x19
 CPU: 0 PID: 466 Comm: modprobe Kdump: loaded Not tainted 4.19.43 #1
 Hardware name: Microsoft Corporation Virtual Machine/Virtual Machine, BIOS 090007  06/02/2017
 Call Trace:
  dump_stack+0x61/0x7e
  check_preemption_disabled+0xd4/0xe6
  debug_smp_processor_id+0x17/0x19
  set_hv_tscchange_cb+0x1b/0x89
  kvm_arch_init+0x14a/0x163 [kvm]
  kvm_init+0x30/0x259 [kvm]
  vmx_init+0xed/0x3db [kvm_intel]
  do_one_initcall+0x89/0x1bc
  do_init_module+0x5f/0x207
  load_module+0x1b34/0x209b
  __ia32_sys_init_module+0x17/0x19
  do_fast_syscall_32+0x121/0x1fa
  entry_SYSENTER_compat+0x7f/0x91

The easiest solution seems to be disabling preemption while setting up
reenlightment MSRs. While at it, fix hv_cpu_*() callbacks.

Fixes: 93286261de1b4 ("x86/hyperv: Reenlightenment notifications
support")

Cc: Andy Lutomirski <luto@kernel.org>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Cathy Avery <cavery@redhat.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: "Michael Kelley (EOSG)" <Michael.H.Kelley@microsoft.com>
Cc: Mohammed Gamal <mmorsy@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Roman Kagan <rkagan@virtuozzo.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>

Cc: devel@linuxdriverproject.org
Cc: kvm@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org
Cc: x86@kernel.org
Reported-by: Prasanna Panchamukhi <panchamukhi@arista.com>
Signed-off-by: Dmitry Safonov <dima@arista.com>
---
 arch/x86/hyperv/hv_init.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
