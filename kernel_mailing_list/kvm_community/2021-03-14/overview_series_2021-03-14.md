#### [GIT PULL] KVM fixes for 5.12-rc3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12137213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DADAFC433DB
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 08:38:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A7B6A64E64
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 08:38:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235022AbhCNIiU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 14 Mar 2021 04:38:20 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:35560 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235014AbhCNIiQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 14 Mar 2021 04:38:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615711095;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Q5htzpqStR00s3GjmGcznA1WFQEWyNZWX9JW1434yRU=;
        b=N+Au5Xqgp3+DNz3HmP0P2CexcFjAKMb0xp1xMvG2ELTFtRg0JIsjP727FGJ4CmUV9x+Fl3
        x0iVIl4vElWn7FPmt+NRlIrKgkMIsFL3WZudsA30EgK0v1efeGSLSTy+n1b1FAYHizvt8U
        8O9NDipUPkiuxSIOsGpANvx9M9qX6Q4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-190-hqttKa4sNCK4wgkoW0wM-w-1; Sun, 14 Mar 2021 04:38:13 -0400
X-MC-Unique: hqttKa4sNCK4wgkoW0wM-w-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 56216107ACCD;
        Sun, 14 Mar 2021 08:38:12 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 067A519635;
        Sun, 14 Mar 2021 08:38:11 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for 5.12-rc3
Date: Sun, 14 Mar 2021 04:38:11 -0400
Message-Id: <20210314083811.1431665-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9e46f6c6c959d9bb45445c2e8f04a75324a0dfd0:

  KVM: SVM: Clear the CR4 register on reset (2021-03-02 14:39:11 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 35737d2db2f4567106c90060ad110b27cb354fa4:

  KVM: LAPIC: Advancing the timer expiration on guest initiated write (2021-03-12 13:18:52 -0500)

----------------------------------------------------------------
More fixes for ARM and x86.

----------------------------------------------------------------
Andrew Scull (1):
      KVM: arm64: Fix nVHE hyp panic host context restore

Jia He (1):
      KVM: arm64: Fix range alignment when walking page tables

Marc Zyngier (7):
      KVM: arm64: Turn kvm_arm_support_pmu_v3() into a static key
      KVM: arm64: Don't access PMSELR_EL0/PMUSERENR_EL0 when no PMU is available
      KVM: arm64: Rename __vgic_v3_get_ich_vtr_el2() to __vgic_v3_get_gic_config()
      KVM: arm64: Workaround firmware wrongly advertising GICv2-on-v3 compatibility
      KVM: arm64: Ensure I-cache isolation between vcpus of a same VM
      KVM: arm64: Reject VM creation when the default IPA size is unsupported
      KVM: arm64: Fix exclusive limit for IPA size

Muhammad Usama Anjum (2):
      kvm: x86: use NULL instead of using plain integer as pointer
      kvm: x86: annotate RCU pointers

Sami Tolvanen (1):
      KVM: arm64: Don't use cbz/adr with external symbols

Sean Christopherson (3):
      KVM: x86: Ensure deadline timer has truly expired before posting its IRQ
      KVM: SVM: Connect 'npt' module param to KVM's internal 'npt_enabled'
      KVM: x86/mmu: Skip !MMU-present SPTEs when removing SP in exclusive mode

Suzuki K Poulose (1):
      KVM: arm64: nvhe: Save the SPE context early

Wanpeng Li (2):
      KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
      KVM: LAPIC: Advancing the timer expiration on guest initiated write

Will Deacon (1):
      KVM: arm64: Avoid corrupting vCPU context register in guest exit

 Documentation/virt/kvm/api.rst          |  3 +++
 arch/arm64/include/asm/kvm_asm.h        |  8 +++----
 arch/arm64/include/asm/kvm_hyp.h        |  8 ++++++-
 arch/arm64/kernel/image-vars.h          |  3 +++
 arch/arm64/kvm/arm.c                    |  7 +++++-
 arch/arm64/kvm/hyp/entry.S              |  8 ++++---
 arch/arm64/kvm/hyp/include/hyp/switch.h |  9 +++++---
 arch/arm64/kvm/hyp/nvhe/debug-sr.c      | 12 ++++++++--
 arch/arm64/kvm/hyp/nvhe/host.S          | 15 +++++++------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c      | 12 +++++-----
 arch/arm64/kvm/hyp/nvhe/switch.c        | 14 +++++++++---
 arch/arm64/kvm/hyp/nvhe/tlb.c           |  3 ++-
 arch/arm64/kvm/hyp/pgtable.c            |  1 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c         | 40 +++++++++++++++++++++++++++++++--
 arch/arm64/kvm/hyp/vhe/tlb.c            |  3 ++-
 arch/arm64/kvm/mmu.c                    |  3 +--
 arch/arm64/kvm/perf.c                   | 10 +++++++++
 arch/arm64/kvm/pmu-emul.c               | 10 ---------
 arch/arm64/kvm/reset.c                  | 12 ++++++----
 arch/arm64/kvm/vgic/vgic-v3.c           | 12 +++++++---
 arch/x86/include/asm/kvm_host.h         |  4 ++--
 arch/x86/kernel/kvmclock.c              | 19 ++++++++--------
 arch/x86/kvm/lapic.c                    | 12 +++++++++-
 arch/x86/kvm/mmu/tdp_mmu.c              | 11 +++++++++
 arch/x86/kvm/svm/svm.c                  | 25 +++++++++++----------
 arch/x86/kvm/x86.c                      |  2 +-
 include/kvm/arm_pmu.h                   |  9 ++++++--
 27 files changed, 194 insertions(+), 81 deletions(-)
```
#### [PATCH v4 01/11] perf/x86/intel: Fix the comment about guest LBR support on KVM
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12137461
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 377AEC433E6
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 16:01:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 033DA64EB6
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 16:01:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234091AbhCNQAo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 14 Mar 2021 12:00:44 -0400
Received: from mga14.intel.com ([192.55.52.115]:7144 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234000AbhCNQA1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 14 Mar 2021 12:00:27 -0400
IronPort-SDR: 
 OVHdDJDy761aUVz4NoFLlpG4uDoeeGp9PvrRzDTHod5skRaHsnNeXddh0kPmJOdDIsYKaj7+Qx
 Pm1ZH49cI29Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="188360683"
X-IronPort-AV: E=Sophos;i="5.81,248,1610438400";
   d="scan'208";a="188360683"
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Mar 2021 09:00:27 -0700
IronPort-SDR: 
 rHulesa4GWG3LXQatPywhm6YX639LoH5hnEwNnxYhjw9VPvP0WQD8jeo5aHCTUGCguu+tK3lBt
 wKDcqn22juWw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,248,1610438400";
   d="scan'208";a="439530609"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by FMSMGA003.fm.intel.com with ESMTP; 14 Mar 2021 09:00:24 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>,
        Kan Liang <kan.liang@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Andi Kleen <ak@linux.intel.com>
Subject: [PATCH v4 01/11] perf/x86/intel: Fix the comment about guest LBR
 support on KVM
Date: Sun, 14 Mar 2021 23:52:14 +0800
Message-Id: <20210314155225.206661-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210314155225.206661-1-like.xu@linux.intel.com>
References: <20210314155225.206661-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Starting from v5.12, KVM reports guest LBR and extra_regs support
when the host has relevant support. Just delete this part of the
comment and fix a typo.

Cc: Kan Liang <kan.liang@linux.intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
Reviewed-by: Kan Liang <kan.liang@linux.intel.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/events/intel/core.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2] x86: Update guest LBR tests for Architectural LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12137481
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB4C3C43603
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 16:01:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA16C64EB6
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 16:01:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234610AbhCNQBe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 14 Mar 2021 12:01:34 -0400
Received: from mga14.intel.com ([192.55.52.115]:7174 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234204AbhCNQA7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 14 Mar 2021 12:00:59 -0400
IronPort-SDR: 
 9tOJP9ZjFj851vNfqCLTlKRQQbKySFl5/ZZoF4xS5KrDayVdZG5izXHpURYf9pqGKajSXlzFh6
 at/f76iHmg6w==
X-IronPort-AV: E=McAfee;i="6000,8403,9923"; a="188360768"
X-IronPort-AV: E=Sophos;i="5.81,248,1610438400";
   d="scan'208";a="188360768"
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Mar 2021 09:00:59 -0700
IronPort-SDR: 
 FNMvPAvA+DKd0ZQmS4Cd+TtQTo84gtyvQf+j2PfXugx6KgwKs+fI8J2kpf8eWToFruM+FnzpZw
 YvGHTwjTfF4g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,248,1610438400";
   d="scan'208";a="439530752"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by FMSMGA003.fm.intel.com with ESMTP; 14 Mar 2021 09:00:56 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v2] x86: Update guest LBR tests for Architectural LBR
Date: Sun, 14 Mar 2021 23:52:25 +0800
Message-Id: <20210314155225.206661-13-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210314155225.206661-1-like.xu@linux.intel.com>
References: <20210314155225.206661-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This unit-test is intended to test the basic KVM's support for
Architectural LBRs which is a Architectural performance monitor
unit (PMU) feature on Intel processors including negative testing
on the MSR LBR_DEPTH values.

If the LBR bit is set to 1 in the MSR_ARCH_LBR_CTL, the processor
will record a running trace of the most recent branches guest
taken in the LBR entries for guest to read.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 x86/pmu_lbr.c | 88 +++++++++++++++++++++++++++++++++++++++++++++------
 1 file changed, 79 insertions(+), 9 deletions(-)

```
#### [PATCH] vfio: pci: Spello fix in the file vfio_pci.c
##### From: Bhaskar Chowdhury <unixbhaskar@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bhaskar Chowdhury <unixbhaskar@gmail.com>
X-Patchwork-Id: 12137193
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1DEC0C433E0
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 06:12:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D33B164E84
	for <kvm@archiver.kernel.org>; Sun, 14 Mar 2021 06:12:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230088AbhCNFc1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 14 Mar 2021 00:32:27 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51992 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229514AbhCNFbp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 14 Mar 2021 00:31:45 -0500
Received: from mail-qt1-x82f.google.com (mail-qt1-x82f.google.com
 [IPv6:2607:f8b0:4864:20::82f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7D791C061574;
        Sat, 13 Mar 2021 21:31:45 -0800 (PST)
Received: by mail-qt1-x82f.google.com with SMTP id r14so6999349qtt.7;
        Sat, 13 Mar 2021 21:31:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=pt2qdmEDjVSEplThpxjXlBTKYUfK3U6l0UtYEmF5juA=;
        b=LH7DgidSNjqwOPZ+7U0UkXVMWk8qgATc9lVh/wu6WFPKqMU5XZIgiUA5Cc0G+qlr67
         PjAU4SMmyNqT6jUE1w91Ih6z9PQSOp7Ufok2PbM4QXlTCVlMSgGYJv62neC6Fvi4SL9v
         CEvOgtJvTaXDG6EIWJJYSJCIR5QOL+8Zie4wwOUDXwJgslyrgHqSXiwMJyQTcjoHbi9L
         wn22Aiw8B7IlT+TMdT5vvWx7We4voyyilyDpQkK2xR3M4BKNQLOKo6oS0WHoAK+Yi8ko
         Ki/cDbmbcTfGfitPLrT+2PO4/0f5Q3ST+xlSpaBqM2jeRJfpYscuDUfb4XatdyO8P9Vd
         KJgQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=pt2qdmEDjVSEplThpxjXlBTKYUfK3U6l0UtYEmF5juA=;
        b=cMH78blmSRK5L0pmMKplKtkiMvXIohINtfWG1qlgPGyAwTH61uh/gFukflWSp6OQ7f
         sLxn6qs7bu7xjoa23JXDeIoGbfGrjtdiZ1Eracxg4vKiZkDfvItd07BnHB/srZmaQSrF
         4J/2VUTd4r0VUHd8T0y9pC9MFg4xC3F6b6XoMeDZgTSjoLyS+9bGHDtMC+DWPMclJjLS
         c2RZk9Gcr7iaNZ4strAekzPNR1HMBvSrQfKkY+KZ7IV9/7L8/3wwkjtGPNq76AS2XRKe
         G3uSwcl469c2F2mZ7+URF1R2guD7XcSQsTXHrXhL/R/iyT0Ui2ap9iZSMKsHfMxW0Rk8
         F4Rw==
X-Gm-Message-State: AOAM533mK0Odyk/yWiDFcamkdxpTOYcb06aj1kTZvt63lnDryX0GCn1c
        6qJ24NhXYm1hIHyDKB42eB8=
X-Google-Smtp-Source: 
 ABdhPJx4xEdu1pcTey9WTXS+ph+qH+nrmlxv7BzqERauCq5YGrPqJQqKhrCVCozDakqpm59ea4AfxQ==
X-Received: by 2002:ac8:d85:: with SMTP id s5mr18246201qti.390.1615699904167;
        Sat, 13 Mar 2021 21:31:44 -0800 (PST)
Received: from localhost.localdomain ([37.19.198.30])
        by smtp.gmail.com with ESMTPSA id
 d24sm8425145qkl.49.2021.03.13.21.31.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 13 Mar 2021 21:31:43 -0800 (PST)
From: Bhaskar Chowdhury <unixbhaskar@gmail.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        kevin.tian@intel.com, akpm@linux-foundation.org, peterx@redhat.com,
        giovanni.cabiddu@intel.com, walken@google.com, jannh@google.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: rdunlap@infradead.org, Bhaskar Chowdhury <unixbhaskar@gmail.com>
Subject: [PATCH] vfio: pci: Spello fix in the file vfio_pci.c
Date: Sun, 14 Mar 2021 10:59:25 +0530
Message-Id: <20210314052925.3560-1-unixbhaskar@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s/permision/permission/

Signed-off-by: Bhaskar Chowdhury <unixbhaskar@gmail.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org>
---
 drivers/vfio/pci/vfio_pci.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--
2.26.2

```
