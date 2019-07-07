#### [PATCH 1/3] Documentation: virtual: Add toctree hooks
##### From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

```c
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Added toctree hooks for indexing. Hooks added only for newly added files
or already existing files. 

The hook for the top of the tree will be added in a later patch series
when a few more substantial changes have been added. 

Signed-off-by: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
---
 Documentation/virtual/index.rst     | 18 ++++++++++++++++++
 Documentation/virtual/kvm/index.rst | 12 ++++++++++++
 2 files changed, 30 insertions(+)
 create mode 100644 Documentation/virtual/index.rst
 create mode 100644 Documentation/virtual/kvm/index.rst

diff --git a/Documentation/virtual/index.rst b/Documentation/virtual/index.rst
new file mode 100644
index 000000000000..19c9fa2266f4
--- /dev/null
+++ b/Documentation/virtual/index.rst
@@ -0,0 +1,18 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+===========================
+Linux Virtual Documentation
+===========================
+
+.. toctree::
+   :maxdepth: 2
+
+   kvm/index
+   paravirt_ops
+
+.. only:: html and subproject
+
+   Indices
+   =======
+
+   * :ref:`genindex`
diff --git a/Documentation/virtual/kvm/index.rst b/Documentation/virtual/kvm/index.rst
new file mode 100644
index 000000000000..ada224a511fe
--- /dev/null
+++ b/Documentation/virtual/kvm/index.rst
@@ -0,0 +1,12 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+===
+KVM
+===
+
+.. toctree::
+   :maxdepth: 2
+
+   amd-memory-encryption
+   cpuid
+   vcpu-requests

From patchwork Sat Jul  6 21:38:14 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
X-Patchwork-Id: 11033995
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9F1A13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  6 Jul 2019 21:39:07 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id C877B2838B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  6 Jul 2019 21:39:07 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id BCF6528446; Sat,  6 Jul 2019 21:39:07 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.0 required=2.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,RCVD_IN_DNSWL_HI autolearn=ham
	version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 0A3612838B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  6 Jul 2019 21:39:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727152AbfGFVi4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 6 Jul 2019 17:38:56 -0400
Received: from mail-lj1-f195.google.com ([209.85.208.195]:44108 "EHLO
        mail-lj1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727128AbfGFViz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 6 Jul 2019 17:38:55 -0400
Received: by mail-lj1-f195.google.com with SMTP id k18so12314886ljc.11
        for <kvm@vger.kernel.org>; Sat, 06 Jul 2019 14:38:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=eng.ucsd.edu; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=cjzJT+Ug2ljIH+eSeawQbtkAq5PwdGtNp/nTgDIdoFk=;
        b=V9Srk96lJmI+I1DCntkuM0AyIq6ydmZa6ScG2spce+9ttK+z+1D2dTgtpJneKqad4I
         1nm+O2GigCPMFDUSH8SIoQGioEnFRp/zcGYh4LhMc1Gk+7+JHELYRDCNQDJr3T9lH60t
         MftEk/rwA+slBTfPUjj/GdK83sD+mvFMftQQA=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=cjzJT+Ug2ljIH+eSeawQbtkAq5PwdGtNp/nTgDIdoFk=;
        b=K13rFORXLOS1cl2fc4w5cGdSEsQyhHVrz9UIClhcru9ora0CCMPhxJ5EXal+qWtsLA
         MZcqj5jrzr3lmi2CcamMsm8LtdFvjQnkA6Hr6hLmhxNcZ7XE0chcwlnxklFfqrXGB+uG
         vUyDQuJKFYJVMmtpJ//GZGwup1WtNLPKJWLcoxKwkQtuluKedPJiSd/kCHQ5j6BpRqaU
         07pr9+8r9KQ6+5beLikHm7liCj7d5OlXpPzsRJiYCP68y5sAuM7fUmAs+Lc6LY8OUusP
         klhY+Tfj3/l1JhT60YHtN0pPjxoPHyVV7GctSYJcQt4GCrKCy2wOmvRdGCYqKS1gcxgi
         PRqQ==
X-Gm-Message-State: APjAAAXRVK2D69KFI0bkJPnbhn6O8B4A5riani/PNS9YL7r672LHkqXy
        ZKeiobJ+6Ppz0eA2T6XdHnR3RQ==
X-Google-Smtp-Source: 
 APXvYqw3xRdjUvkdGLRSIcoY1bNsDkHY0zejAiAFzDMTkZ32HpoDR4zyyPJfjAlDbxXYX8e/J5l7jA==
X-Received: by 2002:a2e:9ec9:: with SMTP id h9mr5659575ljk.90.1562449132999;
        Sat, 06 Jul 2019 14:38:52 -0700 (PDT)
Received: from luke-XPS-13.home (77-255-206-190.adsl.inetia.pl.
 [77.255.206.190])
        by smtp.gmail.com with ESMTPSA id
 j3sm1322449lfp.34.2019.07.06.14.38.50
        (version=TLS1_3 cipher=AEAD-AES256-GCM-SHA384 bits=256/256);
        Sat, 06 Jul 2019 14:38:52 -0700 (PDT)
From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
X-Google-Original-From: Luke Nowakowski-Krijger <lnowakow@neg.ucsd.edu>
To: linux-kernel-mentees@lists.linuxfoundation.org
Cc: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>,
        pbonzini@redhat.com, rkrcmar@redhat.com, corbet@lwn.net,
        kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 2/3] Documentation: kvm: Convert cpuid.txt to .rst
Date: Sat,  6 Jul 2019 14:38:14 -0700
Message-Id: 
 <e8cd24f40cdd23ed116679f4c3cfcf8849879bb4.1562448500.git.lnowakow@eng.ucsd.edu>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <cover.1562448500.git.lnowakow@eng.ucsd.edu>
References: <cover.1562448500.git.lnowakow@eng.ucsd.edu>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>

Convert cpuid.txt to .rst format to be parsable by sphinx. 

Change format and spacing to make function definitions and return values
much more clear. Also added a table that is parsable by sphinx and makes
the information much more clean. 

Signed-off-by: Luke Nowakowski-Krijger <lnowakow@eng.ucsd.edu>
---
 Documentation/virtual/kvm/cpuid.rst | 99 +++++++++++++++++++++++++++++
 Documentation/virtual/kvm/cpuid.txt | 83 ------------------------
 2 files changed, 99 insertions(+), 83 deletions(-)
 create mode 100644 Documentation/virtual/kvm/cpuid.rst
 delete mode 100644 Documentation/virtual/kvm/cpuid.txt

diff --git a/Documentation/virtual/kvm/cpuid.rst b/Documentation/virtual/kvm/cpuid.rst
new file mode 100644
index 000000000000..1a03336a500e
--- /dev/null
+++ b/Documentation/virtual/kvm/cpuid.rst
@@ -0,0 +1,99 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+==============
+KVM CPUID bits
+==============
+
+:Author: Glauber Costa <glommer@redhat.com>, Red Hat Inc, 2010
+
+A guest running on a kvm host, can check some of its features using
+cpuid. This is not always guaranteed to work, since userspace can
+mask-out some, or even all KVM-related cpuid features before launching
+a guest.
+
+KVM cpuid functions are:
+
+function: **KVM_CPUID_SIGNATURE (0x40000000)**
+
+returns::
+ 
+   eax = 0x40000001
+   ebx = 0x4b4d564b
+   ecx = 0x564b4d56
+   edx = 0x4d
+
+Note that this value in ebx, ecx and edx corresponds to the string "KVMKVMKVM".
+The value in eax corresponds to the maximum cpuid function present in this leaf,
+and will be updated if more functions are added in the future.
+Note also that old hosts set eax value to 0x0. This should
+be interpreted as if the value was 0x40000001.
+This function queries the presence of KVM cpuid leafs.
+
+function: **define KVM_CPUID_FEATURES (0x40000001)**
+
+returns::
+
+          ebx, ecx
+          eax = an OR'ed group of (1 << flag)
+
+where ``flag`` is defined as below:
+
++--------------------------------+------------+---------------------------------+
+| flag                           | value      | meaning                         |
++================================+============+=================================+
+| KVM_FEATURE_CLOCKSOURCE        | 0          | kvmclock available at msrs      |
+|                                |            | 0x11 and 0x12                   |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_NOP_IO_DELAY       | 1          | not necessary to perform delays |
+|                                |            | on PIO operations               |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_MMU_OP             | 2          | deprecated                      |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_CLOCKSOURCE2       | 3          | kvmclock available at msrs      |
+|                                |            | 0x4b564d00 and 0x4b564d01       |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_ASYNC_PF           | 4          | async pf can be enabled by      |
+|                                |            | writing to msr 0x4b564d02       |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_STEAL_TIME         | 5          | steal time can be enabled by    |
+|                                |            | writing to msr 0x4b564d03       |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_PV_EOI             | 6          | paravirtualized end of interrupt|
+|                                |            | handler can be enabled by       |
+|                                |            | writing to msr 0x4b564d04.      |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_PV_UNHAULT         | 7          | guest checks this feature bit   |
+|                                |            | before enabling paravirtualized |
+|                                |            | spinlock support                |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_PV_TLB_FLUSH       | 9          | guest checks this feature bit   |
+|                                |            | before enabling paravirtualized |
+|                                |            | tlb flush                       |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_ASYNC_PF_VMEXIT    | 10         | paravirtualized async PF VM EXIT|
+|                                |            | can be enabled by setting bit 2 |
+|                                |            | when writing to msr 0x4b564d02  |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_PV_SEND_IPI        | 11         | guest checks this feature bit   |
+|                                |            | before enabling paravirtualized |
+|                                |            | sebd IPIs                       |
++--------------------------------+------------+---------------------------------+
+| KVM_FEATURE_CLOCSOURCE_STABLE  | 24         | host will warn if no guest-side |
+| _BIT                           |            | per-cpu warps are expeced in    |
+|                                |            | kvmclock                        |
++--------------------------------+------------+---------------------------------+
+
+::
+
+      edx = an OR'ed group of (1 << flag)
+
+Where ``flag`` here is defined as below:
+
++--------------------------------+------------+---------------------------------+
+| flag                           | value      | meaning                         |
++================================+============+=================================+
+| KVM_HINTS_REALTIME             | 0          | guest checks this feature bit to|
+|                                |            | determine that vCPUs are never  |
+|                                |            | preempted for an unlimited time |
+|                                |            | allowing optimizations          |
++--------------------------------+------------+---------------------------------+
diff --git a/Documentation/virtual/kvm/cpuid.txt b/Documentation/virtual/kvm/cpuid.txt
```
#### [PATCH] KVM: arm/arm64: Initialise host's MPIDRs by reading the actual register
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
As part of setting up the host context, we populate its
MPIDR by using cpu_logical_map(). It turns out that contrary
to arm64, cpu_logical_map() on 32bit ARM doesn't return the
*full* MPIDR, but a truncated version.

This leaves the host MPIDR slightly corrupted after the first
run of a VM, since we won't correctly restore the MPIDR on
exit. Oops.

Since we cannot trust cpu_logical_map(), let's adopt a different
strategy. We move the initialization of the host CPU context as
part of the per-CPU initialization (which, in retrospect, makes
a lot of sense), and directly read the MPIDR from the HW. This
is guaranteed to work on both arm and arm64.

Reported-by: Andre Przywara <Andre.Przywara@arm.com>
Fixes: 32f139551954 ("arm/arm64: KVM: Statically configure the host's view of MPIDR")
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_host.h   | 5 ++---
 arch/arm64/include/asm/kvm_host.h | 5 ++---
 virt/kvm/arm/arm.c                | 3 ++-
 3 files changed, 6 insertions(+), 7 deletions(-)

```
#### [PATCH v7 1/2] KVM: LAPIC: Make lapic timer unpinned
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Commit 61abdbe0bcc2 ("kvm: x86: make lapic hrtimer pinned") pinned the
lapic timer to avoid to wait until the next kvm exit for the guest to
see KVM_REQ_PENDING_TIMER set. There is another solution to give a kick
after setting the KVM_REQ_PENDING_TIMER bit, make lapic timer unpinned
will be used in follow up patches.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 8 ++++----
 arch/x86/kvm/x86.c   | 6 +-----
 2 files changed, 5 insertions(+), 9 deletions(-)

```
#### [PATCH] kvm: x86: Fix -Wmissing-prototypes warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We get a warning when build kernel W=1:

arch/x86/kvm/../../../virt/kvm/eventfd.c:48:1: warning: no previous prototype for ‘kvm_arch_irqfd_allowed’ [-Wmissing-prototypes]
 kvm_arch_irqfd_allowed(struct kvm *kvm, struct kvm_irqfd *args)
 ^

The reason is kvm_arch_irqfd_allowed is declared in arch/x86/kvm/irq.h,
which is not included by eventfd.c. Remove the declaration to kvm_host.h
can fix this.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/irq.h       | 1 -
 include/linux/kvm_host.h | 1 +
 2 files changed, 1 insertion(+), 1 deletion(-)

```
