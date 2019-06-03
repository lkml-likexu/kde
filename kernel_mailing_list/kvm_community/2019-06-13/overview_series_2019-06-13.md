#### [patch 1/5] drivers/cpuidle: add cpuidle-haltpoll driverReferences: <20190613224532.949768676@redhat.com>
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Add a cpuidle driver that calls the architecture default_idle routine.

To be used in conjunction with the haltpoll governor.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 arch/x86/kernel/process.c          |    2 -
 drivers/cpuidle/Kconfig            |    9 +++++
 drivers/cpuidle/Makefile           |    1 
 drivers/cpuidle/cpuidle-haltpoll.c |   65 +++++++++++++++++++++++++++++++++++++
 4 files changed, 76 insertions(+), 1 deletion(-)

Index: linux-2.6.git/arch/x86/kernel/process.c
===================================================================
--- linux-2.6.git.orig/arch/x86/kernel/process.c	2019-06-13 16:19:27.877064340 -0400
+++ linux-2.6.git/arch/x86/kernel/process.c	2019-06-13 16:19:48.795544892 -0400
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
--- linux-2.6.git.orig/drivers/cpuidle/Kconfig	2019-06-13 16:19:27.878064316 -0400
+++ linux-2.6.git/drivers/cpuidle/Kconfig	2019-06-13 18:41:40.599912671 -0400
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
--- linux-2.6.git.orig/drivers/cpuidle/Makefile	2019-06-13 16:19:27.878064316 -0400
+++ linux-2.6.git/drivers/cpuidle/Makefile	2019-06-13 16:19:48.796544867 -0400
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
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-13 18:41:39.305933413 -0400
@@ -0,0 +1,65 @@
+// SPDX-License-Identifier: GPL-2.0
+/*
+ * cpuidle driver for haltpoll governor.
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
+#include <linux/sched/idle.h>
+
+static int default_enter_idle(struct cpuidle_device *dev,
+			      struct cpuidle_driver *drv, int index)
+{
+	if (current_clr_polling_and_test()) {
+		local_irq_enable();
+		return index;
+	}
+	default_idle();
+	return index;
+}
+
+static struct cpuidle_driver haltpoll_driver = {
+	.name = "haltpoll",
+	.owner = THIS_MODULE,
+	.states = {
+		{ /* entry 0 is for polling */ },
+		{
+			.enter			= default_enter_idle,
+			.exit_latency		= 0,
+			.target_residency	= 0,
+			.power_usage		= -1,
+			.name			= "haltpoll idle",
+			.desc			= "default architecture idle",
+		},
+	},
+	.safe_state_index = 0,
+	.state_count = 2,
+};
+
+static int __init haltpoll_init(void)
+{
+	struct cpuidle_driver *drv = &haltpoll_driver;
+
+	cpuidle_poll_state_init(drv);
+
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

From patchwork Thu Jun 13 22:45:34 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10993779
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F76F14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:13 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 733AC26CFF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:13 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 6768C271CB; Thu, 13 Jun 2019 22:55:13 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=unavailable version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 09927274D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727019AbfFMWzM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Jun 2019 18:55:12 -0400
Received: from mx1.redhat.com ([209.132.183.28]:35274 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726201AbfFMWzL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Jun 2019 18:55:11 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 85BF359454;
        Thu, 13 Jun 2019 22:55:10 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F10CE1001B2E;
        Thu, 13 Jun 2019 22:55:06 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 011C2105186;
        Thu, 13 Jun 2019 19:53:04 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5DMr38O025934;
        Thu, 13 Jun 2019 19:53:03 -0300
Message-ID: <20190613225022.969533311@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 13 Jun 2019 18:45:34 -0400
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
Subject: [patch 2/5] cpuidle: add get_poll_time callback
References: <20190613224532.949768676@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-15
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.39]);
 Thu, 13 Jun 2019 22:55:10 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Add a "get_poll_time" callback to the cpuidle_governor structure,
and change poll state to poll for that amount of time.

Provide a default method for it, while allowing individual governors
to override it.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 drivers/cpuidle/cpuidle.c    |   40 ++++++++++++++++++++++++++++++++++++++++
 drivers/cpuidle/poll_state.c |   11 ++---------
 include/linux/cpuidle.h      |    8 ++++++++
 3 files changed, 50 insertions(+), 9 deletions(-)

Index: linux-2.6.git/drivers/cpuidle/cpuidle.c
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/cpuidle.c	2019-06-13 17:57:33.111185824 -0400
+++ linux-2.6.git/drivers/cpuidle/cpuidle.c	2019-06-13 18:09:48.158500660 -0400
@@ -362,6 +362,46 @@
 }
 
 /**
+ * cpuidle_default_poll_time - default routine used to return poll time
+ * governors can override it if necessary
+ *
+ * @drv:   the cpuidle driver tied with the cpu
+ * @dev:   the cpuidle device
+ *
+ */
+static u64 cpuidle_default_poll_time(struct cpuidle_driver *drv,
+				     struct cpuidle_device *dev)
+{
+	int i;
+
+	for (i = 1; i < drv->state_count; i++) {
+		if (drv->states[i].disabled || dev->states_usage[i].disable)
+			continue;
+
+		return (u64)drv->states[i].target_residency * NSEC_PER_USEC;
+	}
+
+	return TICK_NSEC;
+}
+
+/**
+ * cpuidle_get_poll_time - tell the polling driver how much time to poll,
+ *			   in nanoseconds.
+ *
+ * @drv: the cpuidle driver tied with the cpu
+ * @dev: the cpuidle device
+ *
+ */
+u64 cpuidle_get_poll_time(struct cpuidle_driver *drv,
+			  struct cpuidle_device *dev)
+{
+	if (cpuidle_curr_governor->get_poll_time)
+		return cpuidle_curr_governor->get_poll_time(drv, dev);
+
+	return cpuidle_default_poll_time(drv, dev);
+}
+
+/**
  * cpuidle_install_idle_handler - installs the cpuidle idle loop handler
  */
 void cpuidle_install_idle_handler(void)
Index: linux-2.6.git/drivers/cpuidle/poll_state.c
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/poll_state.c	2019-06-13 17:57:33.111185824 -0400
+++ linux-2.6.git/drivers/cpuidle/poll_state.c	2019-06-13 18:01:19.846944820 -0400
@@ -20,16 +20,9 @@
 	local_irq_enable();
 	if (!current_set_polling_and_test()) {
 		unsigned int loop_count = 0;
-		u64 limit = TICK_NSEC;
-		int i;
+		u64 limit;
 
-		for (i = 1; i < drv->state_count; i++) {
-			if (drv->states[i].disabled || dev->states_usage[i].disable)
-				continue;
-
-			limit = (u64)drv->states[i].target_residency * NSEC_PER_USEC;
-			break;
-		}
+		limit = cpuidle_get_poll_time(drv, dev);
 
 		while (!need_resched()) {
 			cpu_relax();
Index: linux-2.6.git/include/linux/cpuidle.h
===================================================================
--- linux-2.6.git.orig/include/linux/cpuidle.h	2019-06-13 17:57:33.111185824 -0400
+++ linux-2.6.git/include/linux/cpuidle.h	2019-06-13 18:01:19.846944820 -0400
@@ -132,6 +132,8 @@
 extern int cpuidle_enter(struct cpuidle_driver *drv,
 			 struct cpuidle_device *dev, int index);
 extern void cpuidle_reflect(struct cpuidle_device *dev, int index);
+extern u64 cpuidle_get_poll_time(struct cpuidle_driver *drv,
+				 struct cpuidle_device *dev);
 
 extern int cpuidle_register_driver(struct cpuidle_driver *drv);
 extern struct cpuidle_driver *cpuidle_get_driver(void);
@@ -166,6 +168,9 @@
 				struct cpuidle_device *dev, int index)
 {return -ENODEV; }
 static inline void cpuidle_reflect(struct cpuidle_device *dev, int index) { }
+extern u64 cpuidle_get_poll_time(struct cpuidle_driver *drv,
+				 struct cpuidle_device *dev)
+{return 0; }
 static inline int cpuidle_register_driver(struct cpuidle_driver *drv)
 {return -ENODEV; }
 static inline struct cpuidle_driver *cpuidle_get_driver(void) {return NULL; }
@@ -246,6 +251,9 @@
 					struct cpuidle_device *dev,
 					bool *stop_tick);
 	void (*reflect)		(struct cpuidle_device *dev, int index);
+
+	u64 (*get_poll_time)	(struct cpuidle_driver *drv,
+					struct cpuidle_device *dev);
 };
 
 #ifdef CONFIG_CPU_IDLE

From patchwork Thu Jun 13 22:45:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10993793
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98EA376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:25 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 89B6C22376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:25 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 7DC25271CB; Thu, 13 Jun 2019 22:55:25 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 9DD6922376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727501AbfFMWzX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Jun 2019 18:55:23 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41638 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727136AbfFMWzP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Jun 2019 18:55:15 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 800288830C;
        Thu, 13 Jun 2019 22:55:15 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E8FC06085B;
        Thu, 13 Jun 2019 22:55:14 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 8B5AF105188;
        Thu, 13 Jun 2019 19:53:04 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5DMr4Kb025935;
        Thu, 13 Jun 2019 19:53:04 -0300
Message-ID: <20190613225023.011025297@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 13 Jun 2019 18:45:35 -0400
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
Subject: [patch 3/5] cpuidle: add haltpoll governor
References: <20190613224532.949768676@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-15
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.28]);
 Thu, 13 Jun 2019 22:55:15 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

The cpuidle_haltpoll governor, in conjunction with the haltpoll cpuidle
driver, allows guest vcpus to poll for a specified amount of time before
halting.
This provides the following benefits to host side polling:

        1) The POLL flag is set while polling is performed, which allows
           a remote vCPU to avoid sending an IPI (and the associated
           cost of handling the IPI) when performing a wakeup.

        2) The VM-exit cost can be avoided.

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
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)      1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)       4.53   (-5%)

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 Documentation/virtual/guest-halt-polling.txt |   79 ++++++++++++
 drivers/cpuidle/Kconfig                      |   11 +
 drivers/cpuidle/governors/Makefile           |    1 
 drivers/cpuidle/governors/haltpoll.c         |  175 +++++++++++++++++++++++++++
 4 files changed, 266 insertions(+)

Index: linux-2.6.git/drivers/cpuidle/Kconfig
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/Kconfig	2019-06-13 18:05:46.456294042 -0400
+++ linux-2.6.git/drivers/cpuidle/Kconfig	2019-06-13 18:14:58.981570277 -0400
@@ -33,6 +33,17 @@
 	  Some workloads benefit from using it and it generally should be safe
 	  to use.  Say Y here if you are not happy with the alternatives.
 
+config CPU_IDLE_GOV_HALTPOLL
+	bool "Haltpoll governor (for virtualized systems)"
+	depends on KVM_GUEST
+	help
+	  This governor implements haltpoll idle state selection, to be
+	  used in conjunction with the haltpoll cpuidle driver, allowing
+	  for polling for a certain amount of time before entering idle
+	  state.
+
+	  Some virtualized workloads benefit from using it.
+
 config DT_IDLE_STATES
 	bool
 
Index: linux-2.6.git/drivers/cpuidle/governors/Makefile
===================================================================
--- linux-2.6.git.orig/drivers/cpuidle/governors/Makefile	2019-06-13 18:05:46.456294042 -0400
+++ linux-2.6.git/drivers/cpuidle/governors/Makefile	2019-06-13 18:10:53.861444033 -0400
@@ -6,3 +6,4 @@
 obj-$(CONFIG_CPU_IDLE_GOV_LADDER) += ladder.o
 obj-$(CONFIG_CPU_IDLE_GOV_MENU) += menu.o
 obj-$(CONFIG_CPU_IDLE_GOV_TEO) += teo.o
+obj-$(CONFIG_CPU_IDLE_GOV_HALTPOLL) += haltpoll.o
Index: linux-2.6.git/drivers/cpuidle/governors/haltpoll.c
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/drivers/cpuidle/governors/haltpoll.c	2019-06-13 18:12:46.581615748 -0400
@@ -0,0 +1,175 @@
+// SPDX-License-Identifier: GPL-2.0
+/*
+ * haltpoll.c - haltpoll idle governor
+ *
+ * Copyright 2019 Red Hat, Inc. and/or its affiliates.
+ *
+ * This work is licensed under the terms of the GNU GPL, version 2.  See
+ * the COPYING file in the top-level directory.
+ *
+ * Authors: Marcelo Tosatti <mtosatti@redhat.com>
+ */
+
+#include <linux/kernel.h>
+#include <linux/cpuidle.h>
+#include <linux/time.h>
+#include <linux/ktime.h>
+#include <linux/hrtimer.h>
+#include <linux/tick.h>
+#include <linux/sched.h>
+#include <linux/module.h>
+#include <linux/kvm_para.h>
+
+static unsigned int guest_halt_poll_us __read_mostly = 200;
+module_param(guest_halt_poll_us, uint, 0644);
+
+/* division factor to shrink halt_poll_us */
+static unsigned int guest_halt_poll_shrink __read_mostly = 2;
+module_param(guest_halt_poll_shrink, uint, 0644);
+
+/* multiplication factor to grow per-cpu halt_poll_us */
+static unsigned int guest_halt_poll_grow __read_mostly = 2;
+module_param(guest_halt_poll_grow, uint, 0644);
+
+/* value in us to start growing per-cpu halt_poll_us */
+static unsigned int guest_halt_poll_grow_start __read_mostly = 50;
+module_param(guest_halt_poll_grow_start, uint, 0644);
+
+/* allow shrinking guest halt poll */
+static bool guest_halt_poll_allow_shrink __read_mostly = true;
+module_param(guest_halt_poll_allow_shrink, bool, 0644);
+
+struct haltpoll_device {
+	int		last_state_idx;
+	unsigned int	halt_poll_us;
+};
+
+static DEFINE_PER_CPU_ALIGNED(struct haltpoll_device, hpoll_devices);
+
+/**
+ * haltpoll_select - selects the next idle state to enter
+ * @drv: cpuidle driver containing state data
+ * @dev: the CPU
+ * @stop_tick: indication on whether or not to stop the tick
+ */
+static int haltpoll_select(struct cpuidle_driver *drv,
+			   struct cpuidle_device *dev,
+			   bool *stop_tick)
+{
+	struct haltpoll_device *hdev = this_cpu_ptr(&hpoll_devices);
+
+	if (!drv->state_count) {
+		*stop_tick = false;
+		return 0;
+	}
+
+	if (hdev->halt_poll_us == 0)
+		return 1;
+
+	/* Last state was poll? */
+	if (hdev->last_state_idx == 0) {
+		/* Halt if no event occurred on poll window */
+		if (dev->poll_time_limit == true)
+			return 1;
+
+		*stop_tick = false;
+		/* Otherwise, poll again */
+		return 0;
+	}
+
+	*stop_tick = false;
+	/* Last state was halt: poll */
+	return 0;
+}
+
+static void adjust_haltpoll_us(unsigned int block_us,
+			       struct haltpoll_device *dev)
+{
+	unsigned int val;
+
+	/* Grow cpu_halt_poll_us if
+	 * cpu_halt_poll_us < block_ns < guest_halt_poll_us
+	 */
+	if (block_us > dev->halt_poll_us && block_us <= guest_halt_poll_us) {
+		val = dev->halt_poll_us * guest_halt_poll_grow;
+
+		if (val < guest_halt_poll_grow_start)
+			val = guest_halt_poll_grow_start;
+		if (val > guest_halt_poll_us)
+			val = guest_halt_poll_us;
+
+		dev->halt_poll_us = val;
+	} else if (block_us > guest_halt_poll_us &&
+		   guest_halt_poll_allow_shrink) {
+		unsigned int shrink = guest_halt_poll_shrink;
+
+		val = dev->halt_poll_us;
+		if (shrink == 0)
+			val = 0;
+		else
+			val /= shrink;
+		dev->halt_poll_us = val;
+	}
+}
+
+/**
+ * haltpoll_reflect - update variables and update poll time
+ * @dev: the CPU
+ * @index: the index of actual entered state
+ */
+static void haltpoll_reflect(struct cpuidle_device *dev, int index)
+{
+	struct haltpoll_device *hdev = this_cpu_ptr(&hpoll_devices);
+
+	hdev->last_state_idx = index;
+
+	if (index != 0)
+		adjust_haltpoll_us(dev->last_residency, hdev);
+}
+
+/**
+ * haltpoll_enable_device - scans a CPU's states and does setup
+ * @drv: cpuidle driver
+ * @dev: the CPU
+ */
+static int haltpoll_enable_device(struct cpuidle_driver *drv,
+				  struct cpuidle_device *dev)
+{
+	struct haltpoll_device *hdev = &per_cpu(hpoll_devices, dev->cpu);
+
+	memset(hdev, 0, sizeof(struct haltpoll_device));
+
+	return 0;
+}
+
+/**
+ * haltpoll_get_poll_time - return amount of poll time
+ * @drv: cpuidle driver
+ * @dev: the CPU
+ */
+static u64 haltpoll_get_poll_time(struct cpuidle_driver *drv,
+				struct cpuidle_device *dev)
+{
+	struct haltpoll_device *hdev = &per_cpu(hpoll_devices, dev->cpu);
+
+	return hdev->halt_poll_us * NSEC_PER_USEC;
+}
+
+static struct cpuidle_governor haltpoll_governor = {
+	.name =			"haltpoll",
+	.rating =		21,
+	.enable =		haltpoll_enable_device,
+	.select =		haltpoll_select,
+	.reflect =		haltpoll_reflect,
+	.get_poll_time =	haltpoll_get_poll_time,
+};
+
+static int __init init_haltpoll(void)
+{
+	if (kvm_para_available())
+		return cpuidle_register_governor(&haltpoll_governor);
+
+	return 0;
+}
+
+postcore_initcall(init_haltpoll);
Index: linux-2.6.git/Documentation/virtual/guest-halt-polling.txt
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/Documentation/virtual/guest-halt-polling.txt	2019-06-13 18:16:22.414262777 -0400
@@ -0,0 +1,79 @@
+Guest halt polling
+==================
+
+The cpuidle_haltpoll driver, with the haltpoll governor, allows
+the guest vcpus to poll for a specified amount of time before
+halting.
+This provides the following benefits to host side polling:
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
+The basic logic as follows: A global value, guest_halt_poll_us,
+is configured by the user, indicating the maximum amount of
+time polling is allowed. This value is fixed.
+
+Each vcpu has an adjustable guest_halt_poll_us
+("per-cpu guest_halt_poll_us"), which is adjusted by the algorithm
+in response to events (explained below).
+
+Module Parameters
+=================
+
+The haltpoll governor has 5 tunable module parameters:
+
+1) guest_halt_poll_us:
+Maximum amount of time, in microseconds, that polling is
+performed before halting.
+
+Default: 200
+
+2) guest_halt_poll_shrink:
+Division factor used to shrink per-cpu guest_halt_poll_us when
+wakeup event occurs after the global guest_halt_poll_us.
+
+Default: 2
+
+3) guest_halt_poll_grow:
+Multiplication factor used to grow per-cpu guest_halt_poll_us
+when event occurs after per-cpu guest_halt_poll_us
+but before global guest_halt_poll_us.
+
+Default: 2
+
+4) guest_halt_poll_grow_start:
+The per-cpu guest_halt_poll_us eventually reaches zero
+in case of an idle system. This value sets the initial
+per-cpu guest_halt_poll_us when growing. This can
+be increased from 10, to avoid misses during the initial
+growth stage:
+
+10, 20, 40, ... (example assumes guest_halt_poll_grow=2).
+
+Default: 50
+
+5) guest_halt_poll_allow_shrink:
+
+Bool parameter which allows shrinking. Set to N
+to avoid it (per-cpu guest_halt_poll_us will remain
+high once achieves global guest_halt_poll_us value).
+
+Default: Y
+
+The module parameters can be set from the debugfs files in:
+
+	/sys/module/haltpoll/parameters/
+
+Further Notes
+=============
+
+- Care should be taken when setting the guest_halt_poll_us parameter as a
+large value has the potential to drive the cpu usage to 100% on a machine which
+would be almost entirely idle otherwise.
+

From patchwork Thu Jun 13 22:45:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10993781
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CFAD14BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:14 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 5EC4D26CFF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:14 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 52A8C271FD; Thu, 13 Jun 2019 22:55:14 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id CD5D626CFF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726978AbfFMWzL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Jun 2019 18:55:11 -0400
Received: from mx1.redhat.com ([209.132.183.28]:40404 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725884AbfFMWzL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Jun 2019 18:55:11 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 870053082AED;
        Thu, 13 Jun 2019 22:55:10 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F10731001B2B;
        Thu, 13 Jun 2019 22:55:06 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 1B84B105189;
        Thu, 13 Jun 2019 19:53:05 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5DMr49e025938;
        Thu, 13 Jun 2019 19:53:04 -0300
Message-ID: <20190613225023.067845318@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 13 Jun 2019 18:45:36 -0400
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
Subject: [patch 4/5] kvm: x86: add host poll control msrs
References: <20190613224532.949768676@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-15
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Thu, 13 Jun 2019 22:55:10 +0000 (UTC)
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
--- linux-2.6.git.orig/Documentation/virtual/kvm/msr.txt	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/Documentation/virtual/kvm/msr.txt	2019-06-13 18:42:06.149503132 -0400
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
--- linux-2.6.git.orig/arch/x86/include/asm/kvm_host.h	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/arch/x86/include/asm/kvm_host.h	2019-06-13 18:42:06.149503132 -0400
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
--- linux-2.6.git.orig/arch/x86/include/uapi/asm/kvm_para.h	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/arch/x86/include/uapi/asm/kvm_para.h	2019-06-13 18:42:06.150503116 -0400
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
--- linux-2.6.git.orig/arch/x86/kvm/Kconfig	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/arch/x86/kvm/Kconfig	2019-06-13 18:42:06.150503116 -0400
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
--- linux-2.6.git.orig/arch/x86/kvm/cpuid.c	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/arch/x86/kvm/cpuid.c	2019-06-13 18:42:06.150503116 -0400
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
--- linux-2.6.git.orig/arch/x86/kvm/x86.c	2019-06-13 18:41:40.127920237 -0400
+++ linux-2.6.git/arch/x86/kvm/x86.c	2019-06-13 18:42:06.151503100 -0400
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
@@ -8877,6 +8889,10 @@
 	msr.host_initiated = true;
 	kvm_write_tsc(vcpu, &msr);
 	vcpu_put(vcpu);
+
+	/* poll control enabled by default */
+	vcpu->arch.msr_kvm_poll_control = 1;
+
 	mutex_unlock(&vcpu->mutex);
 
 	if (!kvmclock_periodic_sync)
@@ -9951,6 +9967,13 @@
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

From patchwork Thu Jun 13 22:45:37 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 10993789
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 827BA14BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:21 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 7106E20881
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:21 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 6438626222; Thu, 13 Jun 2019 22:55:21 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id D992920881
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Jun 2019 22:55:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727495AbfFMWzT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Jun 2019 18:55:19 -0400
Received: from mx1.redhat.com ([209.132.183.28]:42420 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727130AbfFMWzQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Jun 2019 18:55:16 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 757532F8BF7;
        Thu, 13 Jun 2019 22:55:15 +0000 (UTC)
Received: from amt.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DDF562D1AB;
        Thu, 13 Jun 2019 22:55:14 +0000 (UTC)
Received: from amt.cnet (localhost [127.0.0.1])
        by amt.cnet (Postfix) with ESMTP id 9BA3610518C;
        Thu, 13 Jun 2019 19:53:05 -0300 (BRT)
Received: (from marcelo@localhost)
        by amt.cnet (8.14.7/8.14.7/Submit) id x5DMr5BB025939;
        Thu, 13 Jun 2019 19:53:05 -0300
Message-ID: <20190613225023.119126969@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 13 Jun 2019 18:45:37 -0400
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
Subject: [patch 5/5] cpuidle-haltpoll: disable host side polling when kvm
 virtualized
References: <20190613224532.949768676@redhat.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-15
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.38]);
 Thu, 13 Jun 2019 22:55:15 +0000 (UTC)
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
 drivers/cpuidle/cpuidle-haltpoll.c      |   10 ++++++-
 include/linux/cpuidle_haltpoll.h        |   16 ++++++++++++
 5 files changed, 82 insertions(+), 1 deletion(-)

Index: linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h
===================================================================
--- /dev/null	1970-01-01 00:00:00.000000000 +0000
+++ linux-2.6.git/arch/x86/include/asm/cpuidle_haltpoll.h	2019-06-13 18:42:06.891491238 -0400
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
--- linux-2.6.git.orig/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-13 18:41:39.305933413 -0400
+++ linux-2.6.git/drivers/cpuidle/cpuidle-haltpoll.c	2019-06-13 18:42:06.892491222 -0400
@@ -14,6 +14,7 @@
 #include <linux/cpuidle.h>
 #include <linux/module.h>
 #include <linux/sched/idle.h>
+#include <linux/cpuidle_haltpoll.h>
 
 static int default_enter_idle(struct cpuidle_device *dev,
 			      struct cpuidle_driver *drv, int index)
@@ -46,15 +47,22 @@
 
 static int __init haltpoll_init(void)
 {
+	int ret;
 	struct cpuidle_driver *drv = &haltpoll_driver;
 
 	cpuidle_poll_state_init(drv);
 
-	return cpuidle_register(&haltpoll_driver, NULL);
+	ret = cpuidle_register(&haltpoll_driver, NULL);
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
+++ linux-2.6.git/include/linux/cpuidle_haltpoll.h	2019-06-13 18:42:06.892491222 -0400
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
--- linux-2.6.git.orig/arch/x86/Kconfig	2019-06-13 18:41:39.305933413 -0400
+++ linux-2.6.git/arch/x86/Kconfig	2019-06-13 18:42:06.893491206 -0400
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
--- linux-2.6.git.orig/arch/x86/kernel/kvm.c	2019-06-13 18:41:39.305933413 -0400
+++ linux-2.6.git/arch/x86/kernel/kvm.c	2019-06-13 18:42:06.893491206 -0400
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
#### [PATCH v2 01/20] hw/i386/pc: Use unsigned type to index arrays
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Reviewed-by: Li Qiang <liq3ea@gmail.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/i386/pc.c         | 5 +++--
 include/hw/i386/pc.h | 2 +-
 2 files changed, 4 insertions(+), 3 deletions(-)

```
#### [PATCH] kvm: nVMX: Remove unnecessary sync_roots from handle_inveptFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
When L0 is executing handle_invept(), the TDP MMU is active. Emulating
an L1 INVEPT does require synchronizing the appropriate shadow EPT
root(s), but a call to kvm_mmu_sync_roots in this context won't do
that. Similarly, the hardware TLB and paging-structure-cache entries
associated with the appropriate shadow EPT root(s) must be flushed,
but requesting a TLB_FLUSH from this context won't do that either.

How did this ever work? KVM always does a sync_roots and TLB flush (in
the correct context) when transitioning from L1 to L2. That isn't the
best choice for nested VM performance, but it effectively papers over
the mistakes here.

Remove the unnecessary operations and leave a comment to try to do
better in the future.

Reported-by: Junaid Shahid <junaids@google.com>
Fixes: bfd0a56b90005f ("nEPT: Nested INVEPT")
Cc: Xiao Guangrong <xiaoguangrong@linux.vnet.ibm.com>
Cc: Nadav Har'El <nyh@il.ibm.com>
Cc: Jun Nakajima <jun.nakajima@intel.com>
Cc: Xinhao Xu <xinhao.xu@intel.com>
Cc: Yang Zhang <yang.z.zhang@Intel.com>
Cc: Gleb Natapov <gleb@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by Peter Shier <pshier@google.com>
Reviewed-by: Junaid Shahid <junaids@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: nVMX: use correct clean fields when copying from eVMCS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Unfortunately, a couple of mistakes were made while implementing
Enlightened VMCS support, in particular, wrong clean fields were
used in copy_enlightened_to_vmcs12():
- exception_bitmap is covered by CONTROL_EXCPN;
- vm_exit_controls/pin_based_vm_exec_control/secondary_vm_exec_control
  are covered by CONTROL_GRP1.

Fixes: 945679e301ea0 ("KVM: nVMX: add enlightened VMCS state")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Radim Krčmář <rkrcmar@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: fix syntax error
##### From: Naresh Kamboju <naresh.kamboju@linaro.org>

```c
This patch fixes this build error,
kvm-unit-tests/lib/x86/processor.h:497:45: error: expected ‘)’ before ‘;’ token
  return !!((cpuid(0x80000001).d & (1 << 20));
           ~                                 ^
                                             )

Signed-off-by: Naresh Kamboju <naresh.kamboju@linaro.org>
---
 lib/x86/processor.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] x86: re-enable asyncpf test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The asyncpf test failed but that was just because it needs more memory than the
default.  Fix that and enable it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/unittests.cfg | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: clean up conditions for asynchronous page fault handling
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Even when asynchronous page fault is disabled, KVM does not want to pause
the host if a guest triggers a page fault; instead it will put it into
an artificial HLT state that allows running other host processes while
allowing interrupt delivery into the guest.

However, the way this feature is triggered is a bit confusing.
First, it is not used for page faults while a nested guest is
running: but this is not an issue since the artificial halt
is completely invisible to the guest, either L1 or L2.  Second,
it is used even if kvm_halt_in_guest() returns true; in this case,
the guest probably should not pay the additional latency cost of the
artificial halt, and thus we should handle the page fault in a
completely synchronous way.

By introducing a new function kvm_can_deliver_async_pf, this patch
commonizes the code that chooses whether to deliver an async page fault
(kvm_arch_async_page_not_present) and the code that chooses whether a
page fault should be handled synchronously (kvm_can_do_async_pf).

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.c | 13 ------------
 arch/x86/kvm/x86.c | 59 ++++++++++++++++++++++++++++++++++++++++++++----------
 2 files changed, 48 insertions(+), 24 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Allocate PAE root array when using SVM's 32-bit NPT
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
SVM's Nested Page Tables (NPT) reuses x86 paging for the host-controlled
page walk.  For 32-bit KVM, this means PAE paging is used even when TDP
is enabled, i.e. the PAE root array needs to be allocated.

Fixes: ee6268ba3a68 ("KVM: x86: Skip pae_root shadow allocation if tdp enabled")
Cc: stable@vger.kernel.org
Reported-by: Jiri Palecek <jpalecek@web.de>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Jiri, can you please test this patch?  I haven't actually verified this
fixes the bug due to lack of SVM hardware.

 arch/x86/kvm/mmu.c | 16 ++++++++++------
 1 file changed, 10 insertions(+), 6 deletions(-)

```
#### [PATCH 4/9] x86/mm/tlb: Flush remote and local TLBs concurrently
##### From: Nadav Amit <namit@vmware.com>

```c
To improve TLB shootdown performance, flush the remote and local TLBs
concurrently. Introduce flush_tlb_multi() that does so. The current
flush_tlb_others() interface is kept, since paravirtual interfaces need
to be adapted first before it can be removed. This is left for future
work. In such PV environments, TLB flushes are not performed, at this
time, concurrently.

Add a static key to tell whether this new interface is supported.

Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: x86@kernel.org
Cc: Juergen Gross <jgross@suse.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org
Cc: xen-devel@lists.xenproject.org
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 arch/x86/hyperv/mmu.c                 |  2 +
 arch/x86/include/asm/paravirt.h       |  8 +++
 arch/x86/include/asm/paravirt_types.h |  6 +++
 arch/x86/include/asm/tlbflush.h       |  6 +++
 arch/x86/kernel/kvm.c                 |  1 +
 arch/x86/kernel/paravirt.c            |  3 ++
 arch/x86/mm/tlb.c                     | 71 ++++++++++++++++++++++-----
 arch/x86/xen/mmu_pv.c                 |  2 +
 8 files changed, 87 insertions(+), 12 deletions(-)

```
#### [PATCH net-next] vsock: correct removal of socket from the listThread-Topic: [PATCH net-next] vsock: correct removal of socket from the list
##### From: Sunil Muthuswamy <sunilmut@microsoft.com>

```c
The current vsock code for removal of socket from the list is both
subject to race and inefficient. It takes the lock, checks whether
the socket is in the list, drops the lock and if the socket was on the
list, deletes it from the list. This is subject to race because as soon
as the lock is dropped once it is checked for presence, that condition
cannot be relied upon for any decision. It is also inefficient because
if the socket is present in the list, it takes the lock twice.

Signed-off-by: Sunil Muthuswamy <sunilmut@microsoft.com>
---
 net/vmw_vsock/af_vsock.c | 38 +++++++-------------------------------
 1 file changed, 7 insertions(+), 31 deletions(-)

```
#### [PATCH v4 1/7] s390: vfio-ap: Refactor vfio_ap driver probe and remove callbacks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
In order to limit the number of private mdev functions called from the
vfio_ap device driver as well as to provide a landing spot for dynamic
configuration code related to binding/unbinding AP queue devices to/from
the vfio_ap driver, the following changes are being introduced:

* Move code from the vfio_ap driver's probe callback into a function
  defined in the mdev private operations file.

* Move code from the vfio_ap driver's remove callback into a function
  defined in the mdev private operations file.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 27 ++++++++++-----------------
 drivers/s390/crypto/vfio_ap_ops.c     | 28 ++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  6 +++---
 3 files changed, 41 insertions(+), 20 deletions(-)

```
#### [PATCH v2] KVM: x86: clean up conditions for asynchronous page fault handling
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Even when asynchronous page fault is disabled, KVM does not want to pause
the host if a guest triggers a page fault; instead it will put it into
an artificial HLT state that allows running other host processes while
allowing interrupt delivery into the guest.

However, the way this feature is triggered is a bit confusing.
First, it is not used for page faults while a nested guest is
running: but this is not an issue since the artificial halt
is completely invisible to the guest, either L1 or L2.  Second,
it is used even if kvm_halt_in_guest() returns true; in this case,
the guest probably should not pay the additional latency cost of the
artificial halt, and thus we should handle the page fault in a
completely synchronous way.

By introducing a new function kvm_can_deliver_async_pf, this patch
commonizes the code that chooses whether to deliver an async page fault
(kvm_arch_async_page_not_present) and the code that chooses whether a
page fault should be handled synchronously (kvm_can_do_async_pf).

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.c | 13 -------------
 arch/x86/kvm/x86.c | 47 ++++++++++++++++++++++++++++++++++++++++++-----
 2 files changed, 42 insertions(+), 18 deletions(-)

```
#### [PATCH 01/43] KVM: VMX: Fix handling of #MC that occurs during VM-Entry
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Sean Christopherson <sean.j.christopherson@intel.com>

A previous fix to prevent KVM from consuming stale VMCS state after a
failed VM-Entry inadvertantly blocked KVM's handling of machine checks
that occur during VM-Entry.

Per Intel's SDM, a #MC during VM-Entry is handled in one of three ways,
depending on when the #MC is recognoized.  As it pertains to this bug
fix, the third case explicitly states EXIT_REASON_MCE_DURING_VMENTRY
is handled like any other VM-Exit during VM-Entry, i.e. sets bit 31 to
indicate the VM-Entry failed.

If a machine-check event occurs during a VM entry, one of the following occurs:
 - The machine-check event is handled as if it occurred before the VM entry:
        ...
 - The machine-check event is handled after VM entry completes:
        ...
 - A VM-entry failure occurs as described in Section 26.7. The basic
   exit reason is 41, for "VM-entry failure due to machine-check event".

Explicitly handle EXIT_REASON_MCE_DURING_VMENTRY as a one-off case in
vmx_vcpu_run() instead of binning it into vmx_complete_atomic_exit().
Doing so allows vmx_vcpu_run() to handle VMX_EXIT_REASONS_FAILED_VMENTRY
in a sane fashion and also simplifies vmx_complete_atomic_exit() since
VMCS.VM_EXIT_INTR_INFO is guaranteed to be fresh.

Fixes: b060ca3b2e9e7 ("kvm: vmx: Handle VMLAUNCH/VMRESUME failure properly")
Cc: Jim Mattson <jmattson@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 20 ++++++++------------
 1 file changed, 8 insertions(+), 12 deletions(-)

```
