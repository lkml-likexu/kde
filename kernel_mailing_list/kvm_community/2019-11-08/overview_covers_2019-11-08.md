

#### [PATCH v4 0/4] Add support for capturing the highest observable L2
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Fri Nov  8 05:14:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11234091
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 873842D2C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 05:14:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 65BD521848
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 05:14:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="NcPYn+50"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726556AbfKHFOp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 00:14:45 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:43641 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725769AbfKHFOp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 00:14:45 -0500
Received: by mail-pg1-f202.google.com with SMTP id k7so3835099pgq.10
        for <kvm@vger.kernel.org>; Thu, 07 Nov 2019 21:14:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=PeNBNJQQEkZ4j/LYia2Xdkpd0UJijO32X6NLRJqeS/4=;
        b=NcPYn+50DVjAJuHAM5iGL7Ps1ovokhagbHf7v3yiOJX6+FyXBJVP5CeaJkIzfDsgDA
         D0nWyEAWItI6zKQCRsHpLtlUs9mK+p4kYeK/ge95xxA7WMfo4PXRJBDOVA/dkYdGHw+x
         2xET6jnbxRl/azMIMWDuvWXoRGK+DsVZ1oJ2XgC6hsiMravYHVzLPgr/nzo6zTKQnlwo
         7+Krte4e90Eb5EMP1jmXmH1eRMLi1t5aAvRcerm/AHNEcjpqLwvXQK8xQEkQDxb8dDQF
         hR91KEw77VzOV5erjVpW6zIQ5LgRKuOTdAODSLDvKN0HdeVKvpIUb7a58dV+9Iyfc2x/
         qP0g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=PeNBNJQQEkZ4j/LYia2Xdkpd0UJijO32X6NLRJqeS/4=;
        b=foGCsODZLRAEUQ/OdWprznJuTXhct0FYIRE01iBJ4cbm+XAOP1cC8XxZk93AOJDD4/
         DoHYzHiO9hcXmyi9sF0FnpeWXq6rLIxE5yhoJGNGCK3zrvKJugcRqYCSXUIhNMsQFHYX
         PbQG6pf0hyNSBR+bx3cilNo4KXPNonBBWqpUSKJ5dsZSyVyXM0A/cMLz1feI/xIra0mE
         vcZ0nJFAgpgG/KWZXwb5SO1QJJemoAP4BZfnhxHezQisHFJTHabMxT0D4GizE7/K28FG
         70dcQQhjSiKEbwC++Mpf6cMrzbCBviPRnmz3M9uOAJLorEC0pdZB3qdeQUTjpdCnqOnn
         sq+w==
X-Gm-Message-State: APjAAAXmnuIf1Kc6m73RCjxnUCWTMO+1PVXWyucWpe636YPCT2qq/LR8
        UpGypS8NUyJTQMj54x0WRbO/eQ5wOOZf/zPFhHcrDMPXTbvz/Ruz72AbBhdQFuKt5oY0Ry+AHyO
        r4WWMcfMPTlv+QypvOk9Tr386oouV2qaq41/oFPtkSq2z50QZ76lmowmBz1mH0Com4kfS
X-Google-Smtp-Source: 
 APXvYqwZJ1M5AciQl/CDMp99/qISf61yCzRDs+mLTg8zlpL1wpPvidrNZflgpTvqW2Drud36f9yYLbAEJyOFGHhP
X-Received: by 2002:a63:af13:: with SMTP id w19mr9120437pge.189.1573190084191;
 Thu, 07 Nov 2019 21:14:44 -0800 (PST)
Date: Thu,  7 Nov 2019 21:14:35 -0800
Message-Id: <20191108051439.185635-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [PATCH v4 0/4] Add support for capturing the highest observable L2
 TSC
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The L1 hypervisor may include the IA32_TIME_STAMP_COUNTER MSR in the
vmcs12 MSR VM-exit MSR-store area as a way of determining the highest
TSC value that might have been observed by L2 prior to VM-exit. The
current implementation does not capture a very tight bound on this
value.  To tighten the bound, add the IA32_TIME_STAMP_COUNTER MSR to the
vmcs02 VM-exit MSR-store area whenever it appears in the vmcs12 VM-exit
MSR-store area.  When L0 processes the vmcs12 VM-exit MSR-store area
during the emulation of an L2->L1 VM-exit, special-case the
IA32_TIME_STAMP_COUNTER MSR, using the value stored in the vmcs02
VM-exit MSR-store area to derive the value to be stored in the vmcs12
VM-exit MSR-store area.

v3 -> v4:
 - Squash the final commit with the previous one used to prepare the MSR-store
   area.  There is no need for this split after all.

v2 -> v3:
 - Rename NR_MSR_ENTRIES to NR_LOADSAVE_MSRS
 - Pull setup code for preparing the MSR-store area out of the final commit and
   put it in it's own commit (4/5).
 - Export vmx_find_msr_index() in the final commit instead of in commit 3/5 as
   it isn't until the final commit that we actually use it.

v1 -> v2:
 - Rename function nested_vmx_get_msr_value() to
   nested_vmx_get_vmexit_msr_value().
 - Remove unneeded tag 'Change-Id' from commit messages.

Aaron Lewis (4):
  kvm: nested: Introduce read_and_check_msr_entry()
  kvm: vmx: Rename NR_AUTOLOAD_MSRS to NR_LOADSTORE_MSRS
  kvm: vmx: Rename function find_msr() to vmx_find_msr_index()
  KVM: nVMX: Add support for capturing highest observable L2 TSC

 arch/x86/kvm/vmx/nested.c | 136 ++++++++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c    |  14 ++--
 arch/x86/kvm/vmx/vmx.h    |   9 ++-
 3 files changed, 131 insertions(+), 28 deletions(-)
```
#### [kvm-unit-tests PATCH 00/17] arm: gic: Test SPIs and interrupt groups
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Fri Nov  8 14:42:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11234975
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8297A1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 14:42:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BB6F222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 14:42:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726770AbfKHOmv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 09:42:51 -0500
Received: from foss.arm.com ([217.140.110.172]:44510 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726036AbfKHOmv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 09:42:51 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 877E546A;
        Fri,  8 Nov 2019 06:42:50 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 68F193F719;
        Fri,  8 Nov 2019 06:42:49 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [kvm-unit-tests PATCH 00/17] arm: gic: Test SPIs and interrupt groups
Date: Fri,  8 Nov 2019 14:42:23 +0000
Message-Id: <20191108144240.204202-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far the GIC testing was limited: we were only testing some MMIO
properties on a GICv2 and some IPI behaviour.
This series extends this to cover SPIs as well, also testing the
behaviour with the two interrupt groups the emulated GIC provides to us.

The first patch is an easy extension to allow some distributor MMIO
tests on GICv3 guests as well.
Patch 2 - 5 prepare the GIC testing framework to handle SPIs, also to
be able to check for interrupts *not* firing.
This is used in patch 6, which adds an IRQ test by using a software
triggered SPI. This also tests whether interrupt masking works, at least
using one of the many masking methods.
Patch 8 adds a test to cover multiple cores, to test the interrupt
target settings. Patch 7 avoids unneccesary output when triggering one IRQ
multiple times.
The remainder of the patches add code to differentiate the two interrupt
groups that the GIC provides. On bare-metal machines, typically having
some secure world code running, and using the typical dual-security-state
GIC configuration, we only ever have one group (group 1) available, so
Linux won't use this feature.
However our emulated GIC does not have a secure side (as we are running
in at most EL2), so both interrupt groups are available to a guest.
So the patches add support to program interrupts to belong to one or
another group, also program the virtual GIC to deliver group 0
interrupts as FIQs, and group 1 interrupts as IRQs.
We then do some tests to see whether this setup works as expected.

At the moment only QEMU using TCG passes these tests, the KVM VGIC
emulation fails to handle the group enable bits properly. Patches for
the kernel will be send shortly, this series acts as a verification test
for this feature (as normal world OSes won't probably use two groups).

Please have a look and comment. I am not particularly happy with patch
16, thrilled to hear any suggestions on how to handle this better.

Tested on arm/GICv2, arm64/GICv2 and arm64/GICv3, with and without the
corresponding KVM patches to fix the dual-group behaviour.

Cheers,
Andre

Andre Przywara (17):
  arm: gic: Enable GIC MMIO tests for GICv3 as well
  arm: gic: Generalise function names
  arm: gic: Provide per-IRQ helper functions
  arm: gic: Support no IRQs test case
  arm: gic: Prepare IRQ handler for handling SPIs
  arm: gic: Add simple shared IRQ test
  arm: gic: Extend check_acked() to allow silent call
  arm: gic: Add simple SPI MP test
  arm: gic: Add test for flipping GICD_CTLR.DS
  arm: gic: Check for writable IGROUPR registers
  arm: gic: Check for validity of both group enable bits
  arm: gic: Change gic_read_iar() to take group parameter
  arm: gic: Change write_eoir() to take group parameter
  arm: gic: Prepare for receiving GIC group 0 interrupts via FIQs
  arm: gic: Provide FIQ handler
  arm: gic: Prepare interrupt statistics for both groups
  arm: gic: Test Group0 SPIs

 arm/gic.c                  | 468 ++++++++++++++++++++++++++++++++-----
 arm/micro-bench.c          |   6 +-
 arm/pl031.c                |   4 +-
 arm/timer.c                |   4 +-
 arm/unittests.cfg          |  38 ++-
 lib/arm/asm/arch_gicv3.h   |  26 ++-
 lib/arm/asm/gic-v2.h       |  11 +-
 lib/arm/asm/gic-v3.h       |  12 +-
 lib/arm/asm/gic.h          |  13 +-
 lib/arm/asm/processor.h    |  10 +
 lib/arm/gic-v2.c           |  39 +++-
 lib/arm/gic-v3.c           |   2 +-
 lib/arm/gic.c              | 102 +++++++-
 lib/arm64/asm/arch_gicv3.h |  29 ++-
 lib/arm64/asm/processor.h  |  10 +
 lib/arm64/processor.c      |   2 +
 16 files changed, 685 insertions(+), 91 deletions(-)
```
#### [PATCH 0/3] kvm: arm: VGIC: Fix interrupt group enablement
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Fri Nov  8 17:49:49 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11235319
Return-Path: <SRS0=CHcm=ZA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E53CC1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 17:50:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CED69206A3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 Nov 2019 17:50:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730933AbfKHRt7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 Nov 2019 12:49:59 -0500
Received: from foss.arm.com ([217.140.110.172]:47714 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729775AbfKHRt7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Nov 2019 12:49:59 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1522431B;
        Fri,  8 Nov 2019 09:49:59 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D1ED93F719;
        Fri,  8 Nov 2019 09:49:57 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Marc Zyngier <maz@kernel.org>
Cc: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/3] kvm: arm: VGIC: Fix interrupt group enablement
Date: Fri,  8 Nov 2019 17:49:49 +0000
Message-Id: <20191108174952.740-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In KVM we emulate an ARM Generic Interrupt Controller with a "single
security state", which (unlike most GICs found in silicon) provides
a non-secure operating system with *two* interrupt groups.
Since on bare metal we typically have only one group available, Linux
does not actually care about the groups and will just use the one
provided.

However we claim to support the GIC architecture, and actually have code
to support two groups, so we should aim to support this properly.

As Marc pointed out recently, we don't honour the separate group enable
bits in the GICD_CTLR register, so a guest can't separately enable or
disable the two groups.

Fixing this unfortunately requires more than just to provide storage for
a second bit: So far we were treating the "groupX enable bit" as a
global distributor enable bit, preventing interrupts from being entered
into the list registers at all if the whole thing was disabled.
Now with two separate bits we might need to block one IRQ, while needing
to forward another one, so this neat trick does not work anymore.

Instead we slightly remodel our "interrupt forwarding" mechanism, to
actually get closer to the architecture: Before adding a pending IRQ to
the ap_list, we check whether its configured interrupt group is enabled.
If it's not, we don't add it to the ap_list (yet). Now when later this
group gets enabled, we need to rescan all (pending) IRQs, to add them to
the ap_list and forward them to the guest. This is not really cheap, but
fortunately wouldn't happen too often, so we refrain from employing any
super clever algorithm, at least for now.
Another solution would be to introduce a "disabled_group_list", where
pending, but group-disabled IRQs go to, let me know if I should explore
this further.

Patch 1 prepares the VGIC code to provide storage for the two enable
bits, also extends the MMIO handling to deal with the two bits.
For this patch we still block the "other" group, as we need the
rescanning algorithm in patch 2 to allow enabling of any group later on.
Patch 3 then enables the functionality, when everything is ready.
The split-up is mostly for review purposes, since I expect some
discussion about patch 2. Happy to merge the three into one once we
agreed on the approach.

There is a corresponding kvm-unit-test series to test the FIQ
functionality, since Linux itself won't use this.
This has been tested with Linux (for regressions) and with
kvm-unit-tests, on a GICv2/arm, GICv2/arm64 and GICv3/arm64 machine.

The kvm-unit-tests patches can be found here:
https://lists.cs.columbia.edu/pipermail/kvmarm/2019-November/037853.html
or in the following repo:
https://github.com/Andre-ARM/kvm-unit-tests/commits/gic-group0

This series here can also be found at:
git://linux-arm.org/linux-ap.git

Based on kvmarm/next, commit cd7056ae34af.

Please have a look!

Cheers,
Andre

Andre Przywara (3):
  kvm: arm: VGIC: Prepare for handling two interrupt groups
  kvm: arm: VGIC: Scan all IRQs when interrupt group gets enabled
  kvm: arm: VGIC: Enable proper Group0 handling

 include/kvm/arm_vgic.h           |   7 +-
 virt/kvm/arm/vgic/vgic-debug.c   |   2 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c |  23 +++---
 virt/kvm/arm/vgic/vgic-mmio-v3.c |  22 +++---
 virt/kvm/arm/vgic/vgic.c         | 130 ++++++++++++++++++++++++++++++-
 virt/kvm/arm/vgic/vgic.h         |   3 +
 6 files changed, 162 insertions(+), 25 deletions(-)
```
