#### [PATCH 01/18] KVM: arm64: Don't access PMCR_EL0 when no PMU is available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12003593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9FC9CC433E0
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7157523125
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727707AbhAGLV7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 06:21:59 -0500
Received: from mail.kernel.org ([198.145.29.99]:35570 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727016AbhAGLV7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 06:21:59 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7FFEE23125;
        Thu,  7 Jan 2021 11:21:18 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kxTLw-005p1o-Nt; Thu, 07 Jan 2021 11:21:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Nathan Chancellor <natechancellor@gmail.com>,
        Qian Cai <qcai@redhat.com>,
        Shannon Zhao <shannon.zhao@linux.alibaba.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 01/18] KVM: arm64: Don't access PMCR_EL0 when no PMU is
 available
Date: Thu,  7 Jan 2021 11:20:44 +0000
Message-Id: <20210107112101.2297944-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210107112101.2297944-1-maz@kernel.org>
References: <20210107112101.2297944-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 catalin.marinas@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 mark.rutland@arm.com, natechancellor@gmail.com, qcai@redhat.com,
 shannon.zhao@linux.alibaba.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We reset the guest's view of PMCR_EL0 unconditionally, based on
the host's view of this register. It is however legal for an
implementation not to provide any PMU, resulting in an UNDEF.

The obvious fix is to skip the reset of this shadow register
when no PMU is available, sidestepping the issue entirely.
If no PMU is available, the guest is not able to request
a virtual PMU anyway, so not doing nothing is the right thing
to do!

It is unlikely that this bug can hit any HW implementation
though, as they all provide a PMU. It has been found using nested
virt with the host KVM not implementing the PMU itself.

Fixes: ab9468340d2bc ("arm64: KVM: Add access handler for PMCR register")
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201210083059.1277162-1-maz@kernel.org
---
 arch/arm64/kvm/sys_regs.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [GIT PULL] KVM/arm64 fixes for 5.11, take #1
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12003591
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 05DCFC433DB
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC3F623125
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727717AbhAGLV7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 06:21:59 -0500
Received: from mail.kernel.org ([198.145.29.99]:35538 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726925AbhAGLV6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 06:21:58 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E3407221E9;
        Thu,  7 Jan 2021 11:21:17 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kxTLv-005p1o-Sg; Thu, 07 Jan 2021 11:21:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Nathan Chancellor <natechancellor@gmail.com>,
        Qian Cai <qcai@redhat.com>,
        Shannon Zhao <shannon.zhao@linux.alibaba.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.11, take #1
Date: Thu,  7 Jan 2021 11:20:43 +0000
Message-Id: <20210107112101.2297944-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 catalin.marinas@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 mark.rutland@arm.com, natechancellor@gmail.com, qcai@redhat.com,
 shannon.zhao@linux.alibaba.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Happy New Year!

Here's a first set of fixes for 5.11, most of which are just
cleanups. I may have some more meaty stuff next week, but let's ease
back into it as gently as possible...

Please pull,

	M.

The following changes since commit 3a514592b698588326924625b6948a10c35fadd5:

  Merge remote-tracking branch 'origin/kvm-arm64/psci-relay' into kvmarm-master/next (2020-12-09 10:00:24 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.11-1

for you to fetch changes up to 45ba7b195a369f35cb39094fdb32efe5908b34ad:

  arm64: cpufeature: remove non-exist CONFIG_KVM_ARM_HOST (2021-01-05 13:22:07 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.11, take #1

- VM init cleanups
- PSCI relay cleanups
- Kill CONFIG_KVM_ARM_PMU
- Fixup __init annotations
- Fixup reg_to_encoding()
- Fix spurious PMCR_EL0 access

----------------------------------------------------------------
Alexandru Elisei (5):
      KVM: Documentation: Add arm64 KVM_RUN error codes
      KVM: arm64: arch_timer: Remove VGIC initialization check
      KVM: arm64: Move double-checked lock to kvm_vgic_map_resources()
      KVM: arm64: Update comment in kvm_vgic_map_resources()
      KVM: arm64: Remove redundant call to kvm_pmu_vcpu_reset()

David Brazdil (6):
      KVM: arm64: Prevent use of invalid PSCI v0.1 function IDs
      KVM: arm64: Use lm_alias in nVHE-only VA conversion
      KVM: arm64: Skip computing hyp VA layout for VHE
      KVM: arm64: Minor cleanup of hyp variables used in host
      KVM: arm64: Remove unused includes in psci-relay.c
      KVM: arm64: Move skip_host_instruction to adjust_pc.h

Marc Zyngier (6):
      KVM: arm64: Don't access PMCR_EL0 when no PMU is available
      KVM: arm64: Declutter host PSCI 0.1 handling
      KVM: arm64: Consolidate dist->ready setting into kvm_vgic_map_resources()
      KVM: arm64: Fix hyp_cpu_pm_{init,exit} __init annotation
      KVM: arm64: Remove spurious semicolon in reg_to_encoding()
      KVM: arm64: Replace KVM_ARM_PMU with HW_PERF_EVENTS

Shannon Zhao (1):
      arm64: cpufeature: remove non-exist CONFIG_KVM_ARM_HOST

 Documentation/virt/kvm/api.rst             |  9 ++++-
 arch/arm64/include/asm/kvm_host.h          | 23 ++++++++++++
 arch/arm64/kernel/cpufeature.c             |  2 +-
 arch/arm64/kernel/smp.c                    |  2 +-
 arch/arm64/kvm/Kconfig                     |  8 ----
 arch/arm64/kvm/Makefile                    |  2 +-
 arch/arm64/kvm/arch_timer.c                |  7 ++--
 arch/arm64/kvm/arm.c                       | 32 +++++++++-------
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h |  9 +++++
 arch/arm64/kvm/hyp/nvhe/hyp-main.c         | 12 +-----
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c          |  6 +--
 arch/arm64/kvm/hyp/nvhe/psci-relay.c       | 59 +++++++++++-------------------
 arch/arm64/kvm/pmu-emul.c                  |  2 -
 arch/arm64/kvm/sys_regs.c                  |  6 ++-
 arch/arm64/kvm/va_layout.c                 |  7 ++--
 arch/arm64/kvm/vgic/vgic-init.c            | 11 +++++-
 arch/arm64/kvm/vgic/vgic-v2.c              | 20 +++-------
 arch/arm64/kvm/vgic/vgic-v3.c              | 21 +++--------
 include/kvm/arm_pmu.h                      |  2 +-
 19 files changed, 122 insertions(+), 118 deletions(-)

From patchwork Thu Jan  7 11:20:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12003599
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0E34BC433E0
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDECE23125
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:22:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727779AbhAGLWB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 06:22:01 -0500
Received: from mail.kernel.org ([198.145.29.99]:35602 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726925AbhAGLWB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 06:22:01 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8BC7223142;
        Thu,  7 Jan 2021 11:21:19 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kxTLx-005p1o-K7; Thu, 07 Jan 2021 11:21:17 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Nathan Chancellor <natechancellor@gmail.com>,
        Qian Cai <qcai@redhat.com>,
        Shannon Zhao <shannon.zhao@linux.alibaba.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 02/18] KVM: arm64: Prevent use of invalid PSCI v0.1 function
 IDs
Date: Thu,  7 Jan 2021 11:20:45 +0000
Message-Id: <20210107112101.2297944-3-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210107112101.2297944-1-maz@kernel.org>
References: <20210107112101.2297944-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 catalin.marinas@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 mark.rutland@arm.com, natechancellor@gmail.com, qcai@redhat.com,
 shannon.zhao@linux.alibaba.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Brazdil <dbrazdil@google.com>

PSCI driver exposes a struct containing the PSCI v0.1 function IDs
configured in the DT. However, the struct does not convey the
information whether these were set from DT or contain the default value
zero. This could be a problem for PSCI proxy in KVM protected mode.

Extend config passed to KVM with a bit mask with individual bits set
depending on whether the corresponding function pointer in psci_ops is
set, eg. set bit for PSCI_CPU_SUSPEND if psci_ops.cpu_suspend != NULL.

Previously config was split into multiple global variables. Put
everything into a single struct for convenience.

Reported-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: David Brazdil <dbrazdil@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201208142452.87237-2-dbrazdil@google.com
---
 arch/arm64/include/asm/kvm_host.h    | 20 +++++++++++
 arch/arm64/kvm/arm.c                 | 14 +++++---
 arch/arm64/kvm/hyp/nvhe/psci-relay.c | 53 +++++++++++++++++++++-------
 3 files changed, 70 insertions(+), 17 deletions(-)

```
#### [PATCH v2 1/4] KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12003359
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 68A69C433E9
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:40:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38A912333E
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:40:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727254AbhAGJkk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 04:40:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:36152 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725974AbhAGJkk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Jan 2021 04:40:40 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610012354;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=NxSMAaCU1+Ace6MFz6Sw2uCAGbOsmC/c4cEEXACLBU0=;
        b=dKjTCMerh1hi7vEvDnCGxRP5I8Sen4iIXGYfzShsIDrMz/QNHcwGns1E+j6ModsvWqf5YO
        MUKSFik0tNVUGKAYsafxsms9/c+aUMV90eMoomWb8QeeLBY76pQJNXUDFbNG05+PZqX1z1
        d8jFHXWyoQfjl3HK4FlpLFjUkeGQCFU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-579-I16WtAcZMLqPnyUM8YngAg-1; Thu, 07 Jan 2021 04:39:12 -0500
X-MC-Unique: I16WtAcZMLqPnyUM8YngAg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9400918C89C4;
        Thu,  7 Jan 2021 09:39:10 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9BDD219714;
        Thu,  7 Jan 2021 09:39:03 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/4] KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on
 nested vmexit
Date: Thu,  7 Jan 2021 11:38:51 +0200
Message-Id: <20210107093854.882483-2-mlevitsk@redhat.com>
In-Reply-To: <20210107093854.882483-1-mlevitsk@redhat.com>
References: <20210107093854.882483-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is possible to exit the nested guest mode, entered by
svm_set_nested_state prior to first vm entry to it (e.g due to pending event)
if the nested run was not pending during the migration.

In this case we must not switch to the nested msr permission bitmap.
Also add a warning to catch similar cases in the future.

Fixes: a7d5c7ce41ac1 ("KVM: nSVM: delay MSR permission processing to first nested VM run")

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PULL 01/66] target/mips: Add CP0 Config0 register definitions for MIPS3 ISA
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 12005015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D3A6C433E0
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 22:23:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E225823601
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 22:23:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727553AbhAGWXm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 17:23:42 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45912 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725944AbhAGWXm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 17:23:42 -0500
Received: from mail-wr1-x430.google.com (mail-wr1-x430.google.com
 [IPv6:2a00:1450:4864:20::430])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2A72AC0612F5
        for <kvm@vger.kernel.org>; Thu,  7 Jan 2021 14:23:02 -0800 (PST)
Received: by mail-wr1-x430.google.com with SMTP id t30so7148942wrb.0
        for <kvm@vger.kernel.org>; Thu, 07 Jan 2021 14:23:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=fW0mwAJFoILMKm9wYoK9XOOf/CSaqeng2a0yxdXuwlk=;
        b=AH6CvUU40CZjmLEhU77ijgxJ0hPcSMVJ2GzOlTsKVCyXCFn5YpBwssc/U0Qs/dA6hn
         G0d9aoDgsdMQhvNtJj+FOu1D6AoghLx7jVtVuZrB3juWVTd/6kOmcUQlTsoVh8QCwF8/
         dK9th7CfpxglazqSCFZEEGkjpywpTrx5RlstQS5rsnMWHGN9VwYfJHutIBLLyU4g1gVN
         XLNCObf8hgaAVGAsdzAKclkUfGIUc80m3ZOe2pMrJ6+Idto37dbwYx7qd1okKyi8EXNv
         UKxvhPOXw+lyHe2I+u9lYHLl7HNcCZpvhT995xNTOOryONIvDtZ4aTEFrBCVbnTuG9kn
         e5pw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=fW0mwAJFoILMKm9wYoK9XOOf/CSaqeng2a0yxdXuwlk=;
        b=TSqx1Aj6S3HHIY+G8K2fbyHzT0nddS8q7TQsNIVkNGhISXn7kxcDvnnMnfc/W8aOGJ
         JoUI+6jz9pL09Mb+HlPllxNE3hCOnZ1HXjY8QxOdAX1X6J2vEVHJPPYVdNm8w52sCr9m
         /V4xPLOaqP8jdedJg8sqkBfRZ7WbodZ9UKk/nu658wTXDDwgs2THeUeyk8tUqjm+iy2k
         TA9nlKrYwTJqmWUeeUoCa2BWQwsVSaRoR1Byyt0tWvdLzDKNfLzZwUu7fuDSqTSsiaKw
         Kb8hK4aMRfuxBbMm2wvTqLPkJS7Yb6DQuVg8/GLSD7pMhMaANV6LWZ3azPYtaYWBXLL4
         zoYA==
X-Gm-Message-State: AOAM53121l2S5h+N+GH+Uhj7jOCv+qr366omOssrD/OGh8pkzx1nyn5q
        BVBCPsZ+bEJ33CT9vbG2P5s=
X-Google-Smtp-Source: 
 ABdhPJxClHvusZYqPYf/w2zXO0+Cg3NpWMcgUHjWirXKV2TwoH7uxBpXmD1ODQrmjp71U9B2+y3JdQ==
X-Received: by 2002:adf:80ae:: with SMTP id 43mr705077wrl.50.1610058180999;
        Thu, 07 Jan 2021 14:23:00 -0800 (PST)
Received: from x1w.redhat.com (241.red-88-10-103.dynamicip.rima-tde.net.
 [88.10.103.241])
        by smtp.gmail.com with ESMTPSA id
 s20sm8990109wmj.46.2021.01.07.14.22.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 07 Jan 2021 14:23:00 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: libvir-list@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
 Laurent Vivier <laurent@vivier.eu>, kvm@vger.kernel.org,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Aurelien Jarno <aurelien@aurel32.net>,
 Huacai Chen <chenhuacai@kernel.org>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paul Burton <paulburton@kernel.org>,
 Richard Henderson <richard.henderson@linaro.org>
Subject: [PULL 01/66] target/mips: Add CP0 Config0 register definitions for
 MIPS3 ISA
Date: Thu,  7 Jan 2021 23:21:48 +0100
Message-Id: <20210107222253.20382-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210107222253.20382-1-f4bug@amsat.org>
References: <20210107222253.20382-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MIPS3 and MIPS32/64 ISA use different definitions
for the CP0 Config0 register.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
Message-Id: <20201201132817.2863301-2-f4bug@amsat.org>
---
 target/mips/cpu.h | 10 +++++++++-
 1 file changed, 9 insertions(+), 1 deletion(-)

```
#### [PATCH] uio: uio_pci_generic: don't fail probe if pdev->irq equals to IRQ_NOTCONNECTED
##### From: =?utf-8?b?5p2O5o23?= <jie6.li@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?5p2O5o23?= <jie6.li@samsung.com>
X-Patchwork-Id: 12003641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C7740C433E6
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:32:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8416323120
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 11:32:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727460AbhAGLcz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 06:32:55 -0500
Received: from mailout1.samsung.com ([203.254.224.24]:26037 "EHLO
        mailout1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726229AbhAGLcy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 06:32:54 -0500
Received: from epcas5p4.samsung.com (unknown [182.195.41.42])
        by mailout1.samsung.com (KnoxPortal) with ESMTP id
 20210107113211epoutp01ac9d7bee716a0d7239e314d386e297f8~X796cCKIO2582825828epoutp01B
        for <kvm@vger.kernel.org>; Thu,  7 Jan 2021 11:32:11 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.samsung.com
 20210107113211epoutp01ac9d7bee716a0d7239e314d386e297f8~X796cCKIO2582825828epoutp01B
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1610019131;
        bh=Y5ImB5VQtfD9pDutmko4zwevF00ehKGnHWp7AUBRc0E=;
        h=Subject:Reply-To:From:To:CC:Date:References:From;
        b=KV/2C/46bco6D8hPTNk5DldzyUlIv5ALKlF+OKrZ2JdKToIwJO8EMoTV4EB24FF9x
         WjayU8Wc0hgglu+zU7wDN9038YwO45MHmqVdIiNZP8CWhvkpN+OxRsVWW/aK7Nbw+g
         6iWERtM49OsFCYR5dJYzCmPiJIWAI9z46r9xIFuw=
Received: from epsnrtp3.localdomain (unknown [182.195.42.164]) by
        epcas5p1.samsung.com (KnoxPortal) with ESMTP id
        20210107113210epcas5p19d377f7b6ba3de7aa3e69ecc1e6cd169~X795eAF2u2849628496epcas5p1M;
        Thu,  7 Jan 2021 11:32:10 +0000 (GMT)
Received: from epsmges5p1new.samsung.com (unknown [182.195.40.193]) by
        epsnrtp3.localdomain (Postfix) with ESMTP id 4DBPGJ1nlRz4x9Pw;
 Thu,  7 Jan
        2021 11:32:08 +0000 (GMT)
X-AuditID: b6c32a49-8bfff70000013d42-af-5ff6f1385c4f
Received: from epcas5p1.samsung.com ( [182.195.41.39]) by
        epsmges5p1new.samsung.com (Symantec Messaging Gateway) with SMTP id
        D0.CD.15682.831F6FF5; Thu,  7 Jan 2021 20:32:08 +0900 (KST)
Mime-Version: 1.0
Subject: [PATCH] uio: uio_pci_generic: don't fail probe if pdev->irq equals
 to IRQ_NOTCONNECTED
Reply-To: jie6.li@samsung.com
Sender: =?utf-8?b?5p2O5o23?= <jie6.li@samsung.com>
From: =?utf-8?b?5p2O5o23?= <jie6.li@samsung.com>
To: "mst@redhat.com" <mst@redhat.com>,
        "gregkh@linuxfoundation.org" <gregkh@linuxfoundation.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: =?utf-8?b?6rmA6rK97IKw?= <ks0204.kim@samsung.com>,
 =?utf-8?b?5L2V5YW0?= <xing84.he@samsung.com>,
 =?utf-8?b?5ZCV6auY6aOe?= <gaofei.lv@samsung.com>
X-Priority: 3
X-Content-Kind-Code: NORMAL
X-Drm-Type: N,general
X-Msg-Generator: Mail
X-Msg-Type: PERSONAL
X-Reply-Demand: N
Message-ID: <20210107113207epcms5p268119bdd826f36a0e5e488a5476f82ca@epcms5p2>
Date: Thu, 07 Jan 2021 19:32:07 +0800
X-CMS-MailID: 20210107113207epcms5p268119bdd826f36a0e5e488a5476f82ca
CMS-TYPE: 105P
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFvrCKsWRmVeSWpSXmKPExsWy7bCmuq7Fx2/xBi/buSx2Ld7IYtG8eD2b
        xexprewWR/dwWMyZWmhxedccNov/v16xWpyd8IHVYm+fjwOnx/65a9g93u+7yubRt2UVo8fn
        TXIBLFE5NhmpiSmpRQqpecn5KZl56bZK3sHxzvGmZgaGuoaWFuZKCnmJuam2Si4+AbpumTlA
        hygplCXmlAKFAhKLi5X07WyK8ktLUhUy8otLbJVSC1JyCgyNCvSKE3OLS/PS9ZLzc60MDQyM
        TIEqE3Iy+rbtYCs4wl3x/v8NpgbGW5xdjJwcEgImEn+OtzOC2EICuxkl/l606mLk4OAVEJT4
        u0MYJCwskCixtOszC0SJrMSth9eZIOJGEmfaesHibAIGEt0rr7J2MXJxiAhcYJR4fPc0M4jD
        LDCdUWLfjPtsEMt4JWa0P2WBsKUlti/fyghhi0rcXP2WHcZ+f2w+VFxEovXeWWYIW1Diwc/d
        UHEZid62m6wgh0oI1EvMOy8EsktCoINRYsrU81C7zCUu7moAu5RXwFei7f8FFpB6FgFVibUt
        6hAlLhJ7zraArWUWkJfY/nYOM0gJs4CmxPpd+hBhPone30+YYK7fMQ/GVpSYfW4X1CfiEi/f
        PYK6zENiz7pp0OAMlDi3YgrrBEa5WYgQnYVk2SyEZQsYmVcxSqYWFOempxabFhjmpZYjR+Mm
        RnDy0/LcwXj3wQe9Q4xMHIyHGCU4mJVEeC2OfYkX4k1JrKxKLcqPLyrNSS0+xGgK9OhEZinR
        5Hxg+s0riTc0NTIzM7A0MDW2MDNUEufdYfAgXkggPbEkNTs1tSC1CKaPiYNTqoEp2/uyWnuW
        1v2OeSm/T0/tkdxUV/t5w+8FEoeaF/c811u/RHeWsvifU80rAisKL7yfMW/Gos5jAi6/eutU
        zdSaA2MOLt1f+PH/6Ya/ujayplPmpknYqp85OvH/uSaF36+eLXylplmx5YHf6o7gD5OktOse
        BB3x4rt14P/2UwLKnhNTXvqEzJByMtogLXO/bLvxPIHy9Qy17wP5Lni1O2TwTK5gaPG29GU4
        cyBmsvpHz4Xtoj5hvOlChlc/Jr86fLJabsNRW+ls+0NmCapMgi6Vu7jaVnBamxn9yJ9xT6Ru
        hsfV031RN7U+7W9se8q5Oi3Ga0pFZPcKATOXFp9tSu+4H13hXnMw7lTekYpTG+8osRRnJBpq
        MRcVJwIACLTuJAcEAAA=
DLP-Filter: Pass
X-CFilter-Loop: Reflected
X-CMS-RootMailID: 20210107113207epcms5p268119bdd826f36a0e5e488a5476f82ca
References: 
 <CGME20210107113207epcms5p268119bdd826f36a0e5e488a5476f82ca@epcms5p2>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From 0fbcd7e386898d829d3000d094358a91e626ee4a Mon Sep 17 00:00:00 2001
From: Jie Li <jie6.li@samsung.com>
Date: Mon, 7 Dec 2020 08:05:07 +0800
Subject: [PATCH] uio: uio_pci_generic: don't fail probe if pdev->irq equals to
 IRQ_NOTCONNECTED

Some devices use 255 as default value of Interrupt Line register, and this
maybe causes pdev->irq is set as IRQ_NOTCONNECTED in some scenarios. For
example, NVMe controller connects to Intel Volume Management Device (VMD).
In this situation, IRQ_NOTCONNECTED means INTx line is not connected, not
fault. If bind uio_pci_generic to these devices, uio frame will return
-ENOTCONN through request_irq.

This patch allows binding uio_pci_generic to device with dev->irq of
IRQ_NOTCONNECTED.

Signed-off-by: Jie Li <jie6.li@samsung.com>
Acked-by: Kyungsan Kim <ks0204.kim@samsung.com>
---
 drivers/uio/uio_pci_generic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/2] KVM: x86/mmu: Ensure TDP MMU roots are freed after yield
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12002505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8FBAAC433E6
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 00:20:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 646B122E03
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 00:20:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726701AbhAGAUV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 19:20:21 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36548 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725792AbhAGAUU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Jan 2021 19:20:20 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 18936C06136F
        for <kvm@vger.kernel.org>; Wed,  6 Jan 2021 16:19:40 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id x74so4220169qkb.12
        for <kvm@vger.kernel.org>; Wed, 06 Jan 2021 16:19:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=YAdMZ4HVtsNign4zck7MQfm5DpVic4jEJ5rVA3Cqe+I=;
        b=CmXcwBZJAfbCWX7/Zs58wTI0vo1u9HDZQ8ZtZrSWLI7giiVKMzDztOCJ1dHXIj55Fc
         n8Gl/FFNXiXEEu9Tzg0E+HT8Qq7gUkAMlXk1OGuk9O1PPJztSyvlugWSSvgIUxbBUHRd
         tL7cmhDmvGt0ml3bb1/X+YsX+ueWHrIpme0j58W3TvIP3RPrvByjwwFKxh6VcfmXwwC4
         ZyV4YjmpOe5Hs8hjbp3PsvDIoOwzq55Cd1iwEfB4ME3JT0jaeUfHgRThKaTuxU3gOrUo
         qrk9QlRixlww+fQG0Ki0gUnrkqpnfd/J+Wm3dW75EbaODtGhlpdonuKszaVO5zg/r9sJ
         x0cA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=YAdMZ4HVtsNign4zck7MQfm5DpVic4jEJ5rVA3Cqe+I=;
        b=Kkb8VYKbIJeECk6xbyzBs8FiQpyOzbFXoaKGE5dSHukQ68cm02DRUDTO9K4zZ/ts4y
         rhHpqAwE0YIda27+/2goT2e07+twrg9ZlmSRWhl2eumW+vMQTNTtwNfNix77GCKQjMxu
         QC0U3mOTjklslrwnWVNukaFAzOZJa4VE1QduhBnU9MVVxo25ftD1914KP6LtpN97rOO9
         LGU2UVXNvcGfehwPz58kIfov6mBXnF+0XQRj+vgSg0nA5S/H4zB/sRJRP4vMXM/Lg3eB
         +sP3MerJImW0p7bGcw76RD6PrgUg4zTvg7c/12vvytmpfkEUO+9FdRNEG/XLDPKzA9q9
         gWRg==
X-Gm-Message-State: AOAM530fMgBpb7eDYOT1ad4Bj0Fv83LmmyWuiF1QWCsRQEonFzkTTpxJ
        WquYYNs/DsQMJAqduUm57BxU2SI7/l/G
X-Google-Smtp-Source: 
 ABdhPJxEkku8a+6wi9WjxvTTJwJ5v53TvGkOS97Cgu2NLffiOTWVa/Iz+FrJoh+ZwOXUOP4D9fjRXln5nBYo
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a0c:e651:: with SMTP id
 c17mr6479465qvn.34.1609978779192; Wed, 06 Jan 2021 16:19:39 -0800 (PST)
Date: Wed,  6 Jan 2021 16:19:34 -0800
Message-Id: <20210107001935.3732070-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [PATCH v3 1/2] KVM: x86/mmu: Ensure TDP MMU roots are freed after
 yield
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        "Maciej S . Szmigiero" <maciej.szmigiero@oracle.com>,
        Leo Hou <leohou1402@gmail.com>, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Many TDP MMU functions which need to perform some action on all TDP MMU
roots hold a reference on that root so that they can safely drop the MMU
lock in order to yield to other threads. However, when releasing the
reference on the root, there is a bug: the root will not be freed even
if its reference count (root_count) is reduced to 0.

To simplify acquiring and releasing references on TDP MMU root pages, and
to ensure that these roots are properly freed, move the get/put operations
into another TDP MMU root iterator macro.

Moving the get/put operations into an iterator macro also helps
simplify control flow when a root does need to be freed. Note that using
the list_for_each_entry_safe macro would not have been appropriate in
this situation because it could keep a pointer to the next root across
an MMU lock release + reacquire, during which time that root could be
freed.

Reported-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Fixes: faaf05b00aec ("kvm: x86/mmu: Support zapping SPTEs in the TDP MMU")
Fixes: 063afacd8730 ("kvm: x86/mmu: Support invalidate range MMU notifier for TDP MMU")
Fixes: a6a0b05da9f3 ("kvm: x86/mmu: Support dirty logging for the TDP MMU")
Fixes: 14881998566d ("kvm: x86/mmu: Support disabling dirty logging for the tdp MMU")
Signed-off-by: Ben Gardon <bgardon@google.com>
Tested-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
Reviewed-by: Sean Christopherson <seanjc@google.com> 
---
 arch/x86/kvm/mmu/tdp_mmu.c | 104 +++++++++++++++++--------------------
 1 file changed, 48 insertions(+), 56 deletions(-)

```
#### [PATCH 1/5] vfio/iommu_type1: Fixes vfio_dma_populate_bitmap to avoid dirty lose
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12003329
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B1E04C4332B
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:30:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73A9B2333F
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:30:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727857AbhAGJac (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 04:30:32 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10556 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727785AbhAGJab (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 04:30:31 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DBLWb5xgWzMGSd;
        Thu,  7 Jan 2021 17:28:27 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Thu, 7 Jan 2021 17:29:29 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH 1/5] vfio/iommu_type1: Fixes vfio_dma_populate_bitmap to avoid
 dirty lose
Date: Thu, 7 Jan 2021 17:28:57 +0800
Message-ID: <20210107092901.19712-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210107092901.19712-1-zhukeqian1@huawei.com>
References: <20210107092901.19712-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Defer checking whether vfio_dma is of fully-dirty in update_user_bitmap
is easy to lose dirty log. For example, after promoting pinned_scope of
vfio_iommu, vfio_dma is not considered as fully-dirty, then we may lose
dirty log that occurs before vfio_iommu is promoted.

The key point is that pinned-dirty is not a real dirty tracking way, it
can't continuously track dirty pages, but just restrict dirty scope. It
is essentially the same as fully-dirty. Fully-dirty is of full-scope and
pinned-dirty is of pinned-scope.

So we must mark pinned-dirty or fully-dirty after we start dirty tracking
or clear dirty bitmap, to ensure that dirty log is marked right away.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty pages tracking")
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 33 ++++++++++++++++++++++-----------
 1 file changed, 22 insertions(+), 11 deletions(-)

```
#### [PATCH 1/6] vfio/iommu_type1: Make an explicit "promote" semantic
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12002881
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 05A23C4332E
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 04:45:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDC6923142
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 04:45:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727129AbhAGEpS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 23:45:18 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:9965 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726641AbhAGEpR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Jan 2021 23:45:17 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DBDC85hsHzj2pY;
        Thu,  7 Jan 2021 12:43:48 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.498.0; Thu, 7 Jan 2021 12:44:26 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, "Marc Zyngier" <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH 1/6] vfio/iommu_type1: Make an explicit "promote" semantic
Date: Thu, 7 Jan 2021 12:43:56 +0800
Message-ID: <20210107044401.19828-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210107044401.19828-1-zhukeqian1@huawei.com>
References: <20210107044401.19828-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we want to promote the pinned_page_dirty_scope of vfio_iommu,
we call the "update" function to visit all vfio_group, but when we
want to downgrade this, we can set the flag as false directly.

So we'd better make an explicit "promote" semantic to the "update"
function. BTW, if vfio_iommu already has been promoted, then return
early.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 30 ++++++++++++++----------------
 1 file changed, 14 insertions(+), 16 deletions(-)

```
