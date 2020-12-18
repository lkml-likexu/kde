

#### [PATCH v3 00/15] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1608197506;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=E7FpqkqnD5unmDeE4sjWFYeLFL2ZgXDe6/5+3YmBT64=;
        b=a9yFTfK79u+NFXUZ4zWV8aHPpDUcRPDVvBCcSa9sHMiOYeRnwQj4sILTaezMzm4EYJQG+K
        gWtQy41s+pv/TtoyNIh8/P2b5G/eZiIFhJyS9RJs098dCw6tqaN2AHvfO5MUEHUwEaUz34
        +nKJxIVkWwafsJ2frUmJ4ePnkcxTR4M=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id 44FF5B1A1;
        Thu, 17 Dec 2020 09:31:46 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Juri Lelli <juri.lelli@redhat.com>,
        Vincent Guittot <vincent.guittot@linaro.org>,
        Dietmar Eggemann <dietmar.eggemann@arm.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ben Segall <bsegall@google.com>, Mel Gorman <mgorman@suse.de>,
        Daniel Bristot de Oliveira <bristot@redhat.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>
Subject: [PATCH v3 00/15] x86: major paravirt cleanup
Date: Thu, 17 Dec 2020 10:31:18 +0100
Message-Id: <20201217093133.1507-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too, but that would require a major
header file disentangling.

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (14):
  x86/xen: use specific Xen pv interrupt entry for MCE
  x86/xen: use specific Xen pv interrupt entry for DF
  x86/pv: switch SWAPGS to ALTERNATIVE
  x86/xen: drop USERGS_SYSRET64 paravirt call
  x86: rework arch_local_irq_restore() to not use popf
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: support "not feature" and ALTERNATIVE_TERNARY
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

Peter Zijlstra (1):
  objtool: Alternatives vs ORC, the hard way

 arch/x86/Kconfig                       |   1 +
 arch/x86/entry/entry_32.S              |   4 +-
 arch/x86/entry/entry_64.S              |  26 ++-
 arch/x86/include/asm/alternative-asm.h |   3 +
 arch/x86/include/asm/alternative.h     |   7 +
 arch/x86/include/asm/cpufeatures.h     |   2 +
 arch/x86/include/asm/idtentry.h        |   6 +
 arch/x86/include/asm/irqflags.h        |  51 ++----
 arch/x86/include/asm/mshyperv.h        |  11 --
 arch/x86/include/asm/paravirt.h        | 157 ++++++------------
 arch/x86/include/asm/paravirt_time.h   |  38 +++++
 arch/x86/include/asm/paravirt_types.h  | 220 +++++++++----------------
 arch/x86/kernel/Makefile               |   3 +-
 arch/x86/kernel/alternative.c          |  59 ++++++-
 arch/x86/kernel/asm-offsets.c          |   7 -
 arch/x86/kernel/asm-offsets_64.c       |   3 -
 arch/x86/kernel/cpu/vmware.c           |   5 +-
 arch/x86/kernel/irqflags.S             |  11 --
 arch/x86/kernel/kvm.c                  |   3 +-
 arch/x86/kernel/kvmclock.c             |   3 +-
 arch/x86/kernel/paravirt.c             |  83 +++-------
 arch/x86/kernel/paravirt_patch.c       | 109 ------------
 arch/x86/kernel/tsc.c                  |   3 +-
 arch/x86/xen/enlighten_pv.c            |  36 ++--
 arch/x86/xen/irq.c                     |  23 ---
 arch/x86/xen/time.c                    |  12 +-
 arch/x86/xen/xen-asm.S                 |  52 +-----
 arch/x86/xen/xen-ops.h                 |   3 -
 drivers/clocksource/hyperv_timer.c     |   5 +-
 drivers/xen/time.c                     |   3 +-
 kernel/sched/sched.h                   |   1 +
 tools/objtool/check.c                  | 180 ++++++++++++++++++--
 tools/objtool/check.h                  |   5 +
 tools/objtool/orc_gen.c                | 178 +++++++++++++-------
 34 files changed, 627 insertions(+), 686 deletions(-)
 create mode 100644 arch/x86/include/asm/paravirt_time.h
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
#### [kvm-unit-tests PATCH 0/1] Don't access PMU when not present
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Dec 17 12:00:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11979671
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 47180C4361B
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 12:02:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 006F52396F
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 12:02:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726354AbgLQMB4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 07:01:56 -0500
Received: from foss.arm.com ([217.140.110.172]:60192 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726012AbgLQMBy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 07:01:54 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A19BA31B;
        Thu, 17 Dec 2020 04:01:08 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 10C3A3F66B;
        Thu, 17 Dec 2020 04:01:07 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [kvm-unit-tests PATCH 0/1] Don't access PMU when not present
Date: Thu, 17 Dec 2020 12:00:56 +0000
Message-Id: <20201217120057.88562-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Found this when reviewing the PMU undef patches [1], which will get merged
for 5.11 (Paolo accepted the pull request [2]).

This only happens if we try to run the PMU tests when creating a VCPU
*without* the PMU feature. I think qemu creates the VCPU by default with a
PMU and I don't know if or how that could be disabled. On the other hand,
kvmtool doesn't enable the feature by default, and you need the specify the
--pmu knob on the command line to enable guest PMU. I think this should
only affect kvmtool users.

For reference, this is what happens without the patch when I try to run a
PMU test on a host built from the kvmarm-5.11 tag from the pull request
(the --pmu knob is missing from the kvmtool command line):

$ lkvm run -c1 -m64 -f arm/pmu.flat -p cycle-counter 
  # lkvm run --firmware arm/pmu.flat -m 64 -c 1 --name guest-821
  Info: Placing fdt at 0x80200000 - 0x80210000
chr_testdev_init: chr-testdev: can't find a virtio-console
Unhandled exception ec=0 (UNKNOWN)
Vector: 4 (el1h_sync)
ESR_EL1:         02000000, ec=0 (UNKNOWN)
FAR_EL1: 1de7ec7edbadc0de (not valid)
Exception frame registers:
pc : [<000000008000b058>] lr : [<0000000080000084>] pstate: 00000000
sp : 000000008003ff60
x29: 0000000000000000 x28: 0000000000000000 
x27: 0000000000000000 x26: 0000000000000000 
x25: 0000000000000000 x24: 0000000000000000 
x23: 0000000000000000 x22: 0000000000000000 
x21: 0000000000000002 x20: 0000000080016a10 
x19: 0000000000000000 x18: 0000000000000000 
x17: 0000000000000000 x16: 0000000000000000 
x15: 0000000080040000 x14: 0000000080040000 
x13: 000000008003ff5c x12: 0000000000000058 
x11: 0000000000000064 x10: 000000008003ff0c 
x9 : 0000000000008400 x8 : 0000000000008008 
x7 : 0000000000000001 x6 : 0000000000000004 
x5 : 0000000000000000 x4 : 0000000080050003 
x3 : 0000000000000001 x2 : 0000000080016d38 
x1 : 0000000080016a10 x0 : 0000000000000002 

With the patch applied:

$ lkvm run -c1 -m64 -f arm/pmu.flat -p cycle-counter 
  # lkvm run --firmware arm/pmu.flat -m 64 -c 1 --name guest-1240
  Info: Placing fdt at 0x80200000 - 0x80210000
chr_testdev_init: chr-testdev: can't find a virtio-console
No PMU found, test skipped...
SUMMARY: 0 tests

[1] https://www.spinics.net/lists/kvm-arm/msg43347.html
[2] https://www.spinics.net/lists/kvm/msg231080.html

Alexandru Elisei (1):
  arm: pmu: Don't read PMCR if PMU is not present

 arm/pmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH v2 00/12] GIC fixes and improvements
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Dec 17 14:13:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11979807
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3935BC4361B
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:15:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E37732360D
	for <kvm@archiver.kernel.org>; Thu, 17 Dec 2020 14:15:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727147AbgLQOOz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 09:14:55 -0500
Received: from foss.arm.com ([217.140.110.172]:38384 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726998AbgLQOOz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 09:14:55 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 4C53D30E;
        Thu, 17 Dec 2020 06:14:09 -0800 (PST)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 5D1DB3F66B;
        Thu, 17 Dec 2020 06:14:08 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: andre.przywara@arm.com, eric.auger@redhat.com, yuzenghui@huawei.com
Subject: [kvm-unit-tests PATCH v2 00/12] GIC fixes and improvements
Date: Thu, 17 Dec 2020 14:13:48 +0000
Message-Id: <20201217141400.106137-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

What started this series is Andre's SPI and group interrupts tests [1],
which prompted me to attempt to rewrite check_acked() so it's more flexible
and not so complicated to review. When I was doing that I noticed that the
message passing pattern for accesses to the acked, bad_irq and bad_sender
arrays didn't look quite right, and that turned into the first 7 patches of
the series. Even though the diffs are relatively small, they are not
trivial and the reviewer can skip them for the more palatable patches that
follow. I would still appreciate someone having a look at the memory
ordering fixes.

Patch #8 ("Split check_acked() into two functions") is where check_acked()
is reworked with an eye towards supporting different timeout values or
silent reporting without adding too many arguments to check_acked().

After changing the IPI tests, I turned my attention to the LPI tests, which
followed the same memory synchronization patterns, but invented their own
interrupt handler and testing functions. Instead of redoing the work that I
did for the IPI tests, I decided to convert the LPI tests to use the same
infrastructure.

I ran tests on the following machines:

- Ampere EMAG: all arm64 tests 10,000+ times (combined) under qemu and
  kvmtool.

- rockpro64: the arm GICv2 and GICv3 tests 10,000+ times under kvmtool (I
  chose kvmtool because it's faster than qemu); the arm64 gic tests (GICv2
  and GICv3) 5000+ times with qemu (didn't realize that ./run_tests.sh -g
  gic doesn't include the its tests); the arm64 GICv2 and GICv3 and ITS
  tests under kvmtool 13,000+ times.

I  didn't see any issues.

Changes in v2:

* Gathered Reviewed-by tags, thank you for the feedback!

* Modified code comments in #1 ("lib: arm/arm64: gicv3: Add missing barrier
  when sending IPIs") as per review suggestions.

* Moved the barrier() in gicv2_ipi_send_self() from #3 ("arm/arm64: gic:
  Remove memory synchronization from ipi_clear_active_handler()") to #2
  ("lib: arm/arm64: gicv2: Add missing barrier when sending IPIs").

* Renamed #3, changed "[..] Remove memory synchronization [..]" to
  "[..] Remove SMP synchronization [..]".

* Moved the removal of smp_rmb() from check_spurious() from #5 ("arm/arm64:
  gic: Use correct memory ordering for the IPI test") to patch #7
  ("arm/arm64: gic: Wait for writes to acked or spurious to complete").

* Fixed typos in #8 ("arm/arm64: gic: Split check_acked() into two
  functions").

* Patch #10 ("arm64: gic: its-trigger: Don't trigger the LPI while it is
  pending") is new. It was added to fix an issue found in v1 [2].

* Patch #11 ("lib: arm64: gic-v3-its: Add wmb() barrier before INT
  command") is also new; it was split from #12 ("arm64: gic: Use IPI test
  checking for the LPI tests") following review comments.

* Removed the now redundant call to stats_reset() from its_prerequisites()
  in #12 ("arm64: gic: Use IPI test checking for the LPI tests").

[1] https://lists.cs.columbia.edu/pipermail/kvmarm/2019-November/037853.html
[2] https://www.spinics.net/lists/kvm-arm/msg43628.html

Alexandru Elisei (12):
  lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
  lib: arm/arm64: gicv2: Add missing barrier when sending IPIs
  arm/arm64: gic: Remove SMP synchronization from
    ipi_clear_active_handler()
  arm/arm64: gic: Remove unnecessary synchronization with stats_reset()
  arm/arm64: gic: Use correct memory ordering for the IPI test
  arm/arm64: gic: Check spurious and bad_sender in the active test
  arm/arm64: gic: Wait for writes to acked or spurious to complete
  arm/arm64: gic: Split check_acked() into two functions
  arm/arm64: gic: Make check_acked() more generic
  arm64: gic: its-trigger: Don't trigger the LPI while it is pending
  lib: arm64: gic-v3-its: Add wmb() barrier before INT command
  arm64: gic: Use IPI test checking for the LPI tests

 lib/arm/gic-v2.c           |   4 +
 lib/arm/gic-v3.c           |   6 +
 lib/arm64/gic-v3-its-cmd.c |   6 +
 arm/gic.c                  | 341 ++++++++++++++++++++-----------------
 4 files changed, 197 insertions(+), 160 deletions(-)
```
