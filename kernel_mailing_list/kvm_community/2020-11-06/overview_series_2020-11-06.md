#### [PATCH 1/5] KVM: arm64: Fix build error in user_mem_abort()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11887383
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF231C55178
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DD162222B
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604681080;
	bh=T36IPLbT9cJ/XPnSJhoaXKK5mtHaqKLZC6nvg9TC1Ek=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=bD0WlO7zWWYuH1Bp9dLnEbuBTmCX7CaJnD5490uDsFeAGBvF5gh6yzqrNQvOGdDRU
	 V6i6aTNTD96GCzDvsdhi5SzY2QvZXHBaIoUK8PRH4oA4PVdSk5aPpDuv+DFltNPkx/
	 RwrnrRVxD2sOfx9fWJ2PTxpEWh5iGUy979BiY7PY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726880AbgKFQoi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 11:44:38 -0500
Received: from mail.kernel.org ([198.145.29.99]:51562 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726415AbgKFQoi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 11:44:38 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id DFEF821556;
        Fri,  6 Nov 2020 16:44:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604681078;
        bh=T36IPLbT9cJ/XPnSJhoaXKK5mtHaqKLZC6nvg9TC1Ek=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Ola4f9kKMahL1JQDf/UuLWtvgFviVPCONE9o/bIL9H3q8cKIg6gYkQ29h7DoGfk0A
         wT+LXaTpsF6jSgvlZ+29oDAbVIsJVUmo2D6MqUKgTwd1I6R/SdTGPqsiz6RsRNWP6J
         sGDWKgyrpAFGVN0VWI3FqJ4Hs3vIs+jORoCJfLqU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kb4qq-008FYW-3X; Fri, 06 Nov 2020 16:44:36 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>, Eric Auger <eric.auger@redhat.com>,
 Gavin Shan <gshan@redhat.com>, =?utf-8?b?5byg5Lic5pet?= <xu910121@sina.com>,
 dave.martin@arm.com, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 1/5] KVM: arm64: Fix build error in user_mem_abort()
Date: Fri,  6 Nov 2020 16:44:12 +0000
Message-Id: <20201106164416.326787-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201106164416.326787-1-maz@kernel.org>
References: <20201106164416.326787-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 eric.auger@redhat.com, gshan@redhat.com, xu910121@sina.com,
 dave.martin@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Gavin Shan <gshan@redhat.com>

The PUD and PMD are folded into PGD when the following options are
enabled. In that case, PUD_SHIFT is equal to PMD_SHIFT and we fail
to build with the indicated errors:

   CONFIG_ARM64_VA_BITS_42=y
   CONFIG_ARM64_PAGE_SHIFT=16
   CONFIG_PGTABLE_LEVELS=3

   arch/arm64/kvm/mmu.c: In function ‘user_mem_abort’:
   arch/arm64/kvm/mmu.c:798:2: error: duplicate case value
     case PMD_SHIFT:
     ^~~~
   arch/arm64/kvm/mmu.c:791:2: note: previously used here
     case PUD_SHIFT:
     ^~~~

This fixes the issue by skipping the check on PUD huge page when PUD
and PMD are folded into PGD.

Fixes: 2f40c46021bbb ("KVM: arm64: Use fallback mapping sizes for contiguous huge page sizes")
Reported-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Gavin Shan <gshan@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201103003009.32955-1-gshan@redhat.com
---
 arch/arm64/kvm/mmu.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v5 1/4] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11886419
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5D40FC388F2
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 09:01:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03B5520665
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 09:01:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726632AbgKFJBE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 04:01:04 -0500
Received: from mga09.intel.com ([134.134.136.24]:4550 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725835AbgKFJBB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 04:01:01 -0500
IronPort-SDR: 
 nyxaDs5rlJ/jIuoWQTJVK2EQ5zjnJzC5T9G0WuFgZYHQgLhDFiJSzJwFS3Ky68ruieYXzIcxeg
 V/HDWOs52uIA==
X-IronPort-AV: E=McAfee;i="6000,8403,9796"; a="169670233"
X-IronPort-AV: E=Sophos;i="5.77,456,1596524400";
   d="scan'208";a="169670233"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Nov 2020 01:00:58 -0800
IronPort-SDR: 
 HwwOisCIpUueVUF9xnxmzT1WEBbmO0GaBwD73AT/4hJ2Otauku5xG0xd7MVj1QkqWpEBM5c/kM
 k/fzxwzu29Qw==
X-IronPort-AV: E=Sophos;i="5.77,456,1596524400";
   d="scan'208";a="472000291"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga004-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Nov 2020 01:00:55 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v5 1/4] KVM: VMX: Convert vcpu_vmx.exit_reason to a union
Date: Fri,  6 Nov 2020 17:03:12 +0800
Message-Id: <20201106090315.18606-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201106090315.18606-1-chenyi.qiang@intel.com>
References: <20201106090315.18606-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Convert vcpu_vmx.exit_reason from a u32 to a union (of size u32).  The
full VM_EXIT_REASON field is comprised of a 16-bit basic exit reason in
bits 15:0, and single-bit modifiers in bits 31:16.

Historically, KVM has only had to worry about handling the "failed
VM-Entry" modifier, which could only be set in very specific flows and
required dedicated handling.  I.e. manually stripping the FAILED_VMENTRY
bit was a somewhat viable approach.  But even with only a single bit to
worry about, KVM has had several bugs related to comparing a basic exit
reason against the full exit reason store in vcpu_vmx.

Upcoming Intel features, e.g. SGX, will add new modifier bits that can
be set on more or less any VM-Exit, as opposed to the significantly more
restricted FAILED_VMENTRY, i.e. correctly handling everything in one-off
flows isn't scalable.  Tracking exit reason in a union forces code to
explicitly choose between consuming the full exit reason and the basic
exit, and is a convenient way to document and access the modifiers.

No functional change intended.

Cc: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 42 +++++++++++++++---------
 arch/x86/kvm/vmx/vmx.c    | 68 ++++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    | 25 +++++++++++++-
 3 files changed, 86 insertions(+), 49 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.10, take #2
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11887381
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 197E2C388F2
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B03D522227
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:39 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604681079;
	bh=9iUTO9V9vPdMlxcyJuoPtkCPdy41zNPPUWFKgP7BkOw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=Oi9ECxsJ/rjzMlsxvTVgI6/DeiihM5NUgJawlnz2BJaZp77+TLS1pmUaEFDSplf2w
	 yM8MF3+vRHo3X0leRNlvD9XyRD7U3HS27hNqpvPEqQOJsE3xex51ukq1heAsJXqjTs
	 S80q7OxLBB2FbhEakoNhKx45wy9yc4+ycDgvpcIM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727108AbgKFQoj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 11:44:39 -0500
Received: from mail.kernel.org ([198.145.29.99]:51546 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726074AbgKFQoi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 11:44:38 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A6EC12151B;
        Fri,  6 Nov 2020 16:44:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604681077;
        bh=9iUTO9V9vPdMlxcyJuoPtkCPdy41zNPPUWFKgP7BkOw=;
        h=From:To:Cc:Subject:Date:From;
        b=Ks7WKJLle02cLYsQQgyk9w62RINaerwNRmf10+VjBh95ZlWfrm9S5PwzeMdxzqy6b
         MkiAzpGRo7AaPEc+d0tTlsaq5nniQCwhRlvZRK+H1ZqVn8LHC5NALxTs+qMSMA7kTl
         2QIL16ALCeSJKNm50eH6Dn714OpONcvRV/WdPuOw=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kb4qp-008FYW-Fr; Fri, 06 Nov 2020 16:44:35 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>, Eric Auger <eric.auger@redhat.com>,
 Gavin Shan <gshan@redhat.com>, =?utf-8?b?5byg5Lic5pet?= <xu910121@sina.com>,
 dave.martin@arm.com, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.10, take #2
Date: Fri,  6 Nov 2020 16:44:11 +0000
Message-Id: <20201106164416.326787-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 eric.auger@redhat.com, gshan@redhat.com, xu910121@sina.com,
 dave.martin@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the second set of fixes for 5.10. A compilation fix for
non-48bit VA builds and a live migration regressions are on the menu
this time. I have another set of regression fixes brewing, but in the
meantime this will fit nicely in mainline.

Please pull,

	M.

The following changes since commit 22f553842b14a1289c088a79a67fb479d3fa2a4e:

  KVM: arm64: Handle Asymmetric AArch32 systems (2020-10-30 16:06:22 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.10-2

for you to fetch changes up to c512298eed0360923d0cbc4a1f30bc0509af0d50:

  KVM: arm64: Remove AA64ZFR0_EL1 accessors (2020-11-06 16:00:29 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for v5.10, take #2

- Fix compilation error when PMD and PUD are folded
- Fix regresssion of the RAZ behaviour of ID_AA64ZFR0_EL1

----------------------------------------------------------------
Andrew Jones (4):
      KVM: arm64: Don't hide ID registers from userspace
      KVM: arm64: Consolidate REG_HIDDEN_GUEST/USER
      KVM: arm64: Check RAZ visibility in ID register accessors
      KVM: arm64: Remove AA64ZFR0_EL1 accessors

Gavin Shan (1):
      KVM: arm64: Fix build error in user_mem_abort()

 arch/arm64/kvm/mmu.c      |   2 +
 arch/arm64/kvm/sys_regs.c | 108 ++++++++++++++--------------------------------
 arch/arm64/kvm/sys_regs.h |  16 +++----
 3 files changed, 43 insertions(+), 83 deletions(-)

From patchwork Fri Nov  6 16:44:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11887389
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A8EE8C5517A
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55E632224A
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604681081;
	bh=t0K1Uzu+49PExG7zsJdALxOgNu8sv7rz5YDcQXoVCJY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=TCook22OOMnDiZdkd0P/yWvTsBQP2N7p8pg6vLG8ysSnh9BGzrlfnfaWcFRTzEIJM
	 Hh7DwDjeHX5qRpyvXr/0mnJ2kYsGHB2cz33fVHWVCuCcLQUghPvLcE3BJl2hWZUCzW
	 x8ey3lsglicfYVg5ZZH3eUuyba4AWPxDIpvTGADQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727270AbgKFQok (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 11:44:40 -0500
Received: from mail.kernel.org ([198.145.29.99]:51592 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726415AbgKFQoj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 11:44:39 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8B5F9217A0;
        Fri,  6 Nov 2020 16:44:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604681078;
        bh=t0K1Uzu+49PExG7zsJdALxOgNu8sv7rz5YDcQXoVCJY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=y0Knw6SXwkuIvEg2uWUQ/PrrwXU0Cup7lBqjLmSlH3uf72/RKpQZ9dOI4ig17Uf4E
         NF9jRnOkkDZgCzsf1c4qRUJIXZQfhuFdoWmvBf85dshrgexy8qMYW6oFU70shSl1hx
         13TGB/J7sIsA7MVpBxI3o7/48OIJ/3RYjg/9oYjs=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kb4qq-008FYW-NV; Fri, 06 Nov 2020 16:44:36 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>, Eric Auger <eric.auger@redhat.com>,
 Gavin Shan <gshan@redhat.com>, =?utf-8?b?5byg5Lic5pet?= <xu910121@sina.com>,
 dave.martin@arm.com, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
 stable@vger.kernel.org
Subject: [PATCH 2/5] KVM: arm64: Don't hide ID registers from userspace
Date: Fri,  6 Nov 2020 16:44:13 +0000
Message-Id: <20201106164416.326787-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201106164416.326787-1-maz@kernel.org>
References: <20201106164416.326787-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 eric.auger@redhat.com, gshan@redhat.com, xu910121@sina.com,
 dave.martin@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

ID registers are RAZ until they've been allocated a purpose, but
that doesn't mean they should be removed from the KVM_GET_REG_LIST
list. So far we only have one register, SYS_ID_AA64ZFR0_EL1, that
is hidden from userspace when its function, SVE, is not present.

Expose SYS_ID_AA64ZFR0_EL1 to userspace as RAZ when SVE is not
implemented. Removing the userspace visibility checks is enough
to reexpose it, as it will already return zero to userspace when
SVE is not present. The register already behaves as RAZ for the
guest when SVE is not present.

Fixes: 73433762fcae ("KVM: arm64/sve: System register context switch and access support")
Reported-by: 张东旭 <xu910121@sina.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Cc: stable@vger.kernel.org#v5.2+
Link: https://lore.kernel.org/r/20201105091022.15373-2-drjones@redhat.com
---
 arch/arm64/kvm/sys_regs.c | 18 +-----------------
 1 file changed, 1 insertion(+), 17 deletions(-)

```
#### [PATCH v14 01/13] KVM: x86: Report XSS as an MSR to be saved if there are supported features
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11885623
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DEA2C4742C
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 01:06:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF02D2078E
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 01:06:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732920AbgKFBGP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 5 Nov 2020 20:06:15 -0500
Received: from mga18.intel.com ([134.134.136.126]:38177 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730895AbgKFBGP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Nov 2020 20:06:15 -0500
IronPort-SDR: 
 JAJPrEjjqNDGIO+MnRXRmQFygsnShQDMhaL6YT++RSqt2/U/YN56vRPKmuO18shbFZmfDrqxMF
 LOk680jaWUQw==
X-IronPort-AV: E=McAfee;i="6000,8403,9796"; a="157264655"
X-IronPort-AV: E=Sophos;i="5.77,454,1596524400";
   d="scan'208";a="157264655"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 17:06:14 -0800
IronPort-SDR: 
 Q4hvVxaRqSr/I/a5GXXIZA7j94gfYRLGTF9YOG3AjfbmpoA6FRvheyuvAzfvslRseOQtHGIxeo
 kTkDXvXjmXQQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,454,1596524400";
   d="scan'208";a="471874430"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.156])
  by orsmga004.jf.intel.com with ESMTP; 05 Nov 2020 17:06:12 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com
Subject: [PATCH v14 01/13] KVM: x86: Report XSS as an MSR to be saved if there
 are supported features
Date: Fri,  6 Nov 2020 09:16:25 +0800
Message-Id: <20201106011637.14289-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20201106011637.14289-1-weijiang.yang@intel.com>
References: <20201106011637.14289-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Add MSR_IA32_XSS to the list of MSRs reported to userspace if
supported_xss is non-zero, i.e. KVM supports at least one XSS based
feature.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: remove kvm_clear_guest_page
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11886795
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 04019C5517A
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 10:25:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 93C6E20720
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 10:25:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VSZbBYUB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726918AbgKFKZ0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 05:25:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24149 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726813AbgKFKZZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Nov 2020 05:25:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604658324;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rzIGS6pP6lZWtk6SQ8xr2MVcGhW0ibnx4UquLJftED4=;
        b=VSZbBYUBuQinlppbMy5K+664LCZwnmArxmoxG//XQBtGGARWEG1jAnRBj++UF+cXhl58im
        i8jNa1uHzp6nN3dxiYV82l+4sQYmGRu1tIrOirmnDCwLFZ7ljuNwCdbMwhwp7esarEtmDk
        6R2cPZcVwsgtM0uuj2AHrnMnvuQIHLU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-7-x8h7qqNrOmm7t1TuMTU4mg-1; Fri, 06 Nov 2020 05:25:22 -0500
X-MC-Unique: x8h7qqNrOmm7t1TuMTU4mg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 45DA01868416;
        Fri,  6 Nov 2020 10:25:21 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 024B519C4F;
        Fri,  6 Nov 2020 10:25:17 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH] KVM: remove kvm_clear_guest_page
Date: Fri,  6 Nov 2020 05:25:17 -0500
Message-Id: <20201106102517.664773-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_clear_guest_page is not used anymore after "KVM: X86: Don't track dirty
for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]", except from kvm_clear_guest.
We can just inline it in its sole user.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h |  1 -
 virt/kvm/kvm_main.c      | 11 ++---------
 2 files changed, 2 insertions(+), 10 deletions(-)

```
#### [PATCH 5/5] KVM: arm64: Remove AA64ZFR0_EL1 accessors
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11887385
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1EED7C388F2
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD2F522241
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 16:44:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604681082;
	bh=MxmBxdTqSNyaIiaHEHjj6oQDH7cYA7bcMmR2qQ3oQdU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=VuBJ0QzJhTOxgxvBSVwo9szVObR8UQQ3V4HXq9bi4eS7zDiMvj8dN7J+YNgovuI2M
	 5qOQZycl/JrLC+2KL9wGHFOmXzfhI2qYmGE0wjizVYwh9OK3pfrhhD5WRw5UGKNoa8
	 xrF7VvqAos/hfZgO6sMKSDIKhMUlqGrnCTSGqpdk=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727356AbgKFQol (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 11:44:41 -0500
Received: from mail.kernel.org ([198.145.29.99]:51696 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726415AbgKFQol (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 11:44:41 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 69B3422203;
        Fri,  6 Nov 2020 16:44:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604681080;
        bh=MxmBxdTqSNyaIiaHEHjj6oQDH7cYA7bcMmR2qQ3oQdU=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Ewv8wIbAVqIuoWReAh75l3bjiOcV6UNdCFAccmIHFHgv5spKhsh6Jcs0lmb+P0NSO
         aEi4QknKa+RDAqOQauzR2ZomXT4mO6502isrGgtR1MpKL0l9n+dxbc2qxK+lG4lV70
         zyJ8yMWCa9fqwOxOkVSW6VMImlQ2re/JDPHGIkP8=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kb4qs-008FYW-Io; Fri, 06 Nov 2020 16:44:38 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>, Eric Auger <eric.auger@redhat.com>,
 Gavin Shan <gshan@redhat.com>, =?utf-8?b?5byg5Lic5pet?= <xu910121@sina.com>,
 dave.martin@arm.com, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 5/5] KVM: arm64: Remove AA64ZFR0_EL1 accessors
Date: Fri,  6 Nov 2020 16:44:16 +0000
Message-Id: <20201106164416.326787-6-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201106164416.326787-1-maz@kernel.org>
References: <20201106164416.326787-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 eric.auger@redhat.com, gshan@redhat.com, xu910121@sina.com,
 dave.martin@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

The AA64ZFR0_EL1 accessors are just the general accessors with
its visibility function open-coded. It also skips the if-else
chain in read_id_reg, but there's no reason not to go there.
Indeed consolidating ID register accessors and removing lines
of code make it worthwhile.

Remove the AA64ZFR0_EL1 accessors, replacing them with the
general accessors for sanitized ID registers.

No functional change intended.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201105091022.15373-5-drjones@redhat.com
---
 arch/arm64/kvm/sys_regs.c | 61 +++++++--------------------------------
 1 file changed, 11 insertions(+), 50 deletions(-)

```
#### [PATCH] mm, kvm: account kvm_vcpu_mmap to kmemcgFrom: Shakeel Butt <shakeelb@google.com>
##### From: Shakeel Butt <shakeelb@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shakeel Butt <shakeelb@google.com>
X-Patchwork-Id: 11888051
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.4 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A956C5517A
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 20:29:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1AEE921D7F
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 20:29:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qxK63C85"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728410AbgKFU3e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 15:29:34 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44316 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728237AbgKFU3e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 15:29:34 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C46F3C0613D2
        for <kvm@vger.kernel.org>; Fri,  6 Nov 2020 12:29:33 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id e19so1725637qtq.17
        for <kvm@vger.kernel.org>; Fri, 06 Nov 2020 12:29:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=ULc2QwdCH5im+pfEGHCAJt9dFDUjORAmMg0iMDdD/ZE=;
        b=qxK63C85+mLWqUM6fF6ufmuq09cUwYZSbRvdqXOVlKWkYTVHLWgKHZPW23Sgbbpsut
         J/dtITSGF8n2ylyWL2J9oazEIkmB5z36lETuij7i6T4x90ka4hoRiMp+aJSiHe5hR7Qm
         cYwBLWMnyNt7WRI+pi7pWUPKuW5krdqFEjpBcH9aLwC3eZv4Mlwd+483rDk01xUiWOPA
         YOboDY+r4fchGJs6SogwqO9pRRdrR/wihlrcAt3wzN7FILrUxhYUpL5uDNEEDCicu449
         vkBz2bGesJpH1iphht0MRywvktZwKa/xSxTJh38piWQ4q5tWgTV+bb+bGUip3QSEVU9v
         vFgQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=ULc2QwdCH5im+pfEGHCAJt9dFDUjORAmMg0iMDdD/ZE=;
        b=rhEoR/6D8vX4TOQ+2LkzcUbZQu9R+ryjMgPUtvgJ9qFB2KWtm6yakUUmR5vtmPMzHZ
         cysb9XetbzHSlLK3aePDzubUCV4MVrriRPZMFAsXYvyDnqkN8Sggkyry6I10j65324gJ
         B9hACiPC9nlwgqww/Fp0ASz7yYxdH8b4qBHXpLba2+WuDE1sveHmM3y31BDEerEmi70e
         9koyYEdcGYYthgLymStCQL+6ZvHDwGFIccwM932G2W4qA4EbetfyM0pCNkWudRSXrGEG
         EOx52GUkKFAQlPXz4L4pC8Iu2PtEms2bGUgBycEPOXRDuBLfjcWzKgTc7ZWVY4gRNDrv
         d5Iw==
X-Gm-Message-State: AOAM530zqDtkpddlp0vSF9TwOUHDgJzKO8dtiMd4YSpVD8SiUY3l1qyz
        3ebLdoqNMbYYCPjq+jOb+yk9SAEDU3vouQ==
X-Google-Smtp-Source: 
 ABdhPJzRtuBmM7hT4n/AykR+FlOUggYbVMe/LDkuyotS0xBuSPRCU2hzDublBhwIcsnZ8iR6EFpEw7C4KtLO4Q==
Sender: "shakeelb via sendgmr" <shakeelb@shakeelb.svl.corp.google.com>
X-Received: from shakeelb.svl.corp.google.com
 ([2620:15c:2cd:202:a28c:fdff:fee8:36f0])
 (user=shakeelb job=sendgmr) by 2002:ac8:6e8b:: with SMTP id
 c11mr3303614qtv.2.1604694572860; Fri, 06 Nov 2020 12:29:32 -0800 (PST)
Date: Fri,  6 Nov 2020 12:29:23 -0800
Message-Id: <20201106202923.2087414-1-shakeelb@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.1.341.ge80a0c044ae-goog
Subject: [PATCH] mm, kvm: account kvm_vcpu_mmap to kmemcg
From: Shakeel Butt <shakeelb@google.com>
To: Roman Gushchin <guro@fb.com>, Johannes Weiner <hannes@cmpxchg.org>,
        Michal Hocko <mhocko@suse.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Paolo Bonzini <pbonzini@redhat.com>, linux-mm@kvack.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Shakeel Butt <shakeelb@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A VCPU of a VM can allocate couple of pages which can be mmap'ed by the
user space application. At the moment this memory is not charged to the
memcg of the VMM. On a large machine running large number of VMs or
small number of VMs having large number of VCPUs, this unaccounted
memory can be very significant. So, charge this memory to the memcg of
the VMM. Please note that lifetime of these allocations corresponds to
the lifetime of the VMM.

Signed-off-by: Shakeel Butt <shakeelb@google.com>
Acked-by: Roman Gushchin <guro@fb.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---

This patch has dependency on Roman's patch series "mm: allow mapping
accounted kernel pages to userspace".

 arch/s390/kvm/kvm-s390.c  | 2 +-
 arch/x86/kvm/x86.c        | 2 +-
 virt/kvm/coalesced_mmio.c | 2 +-
 virt/kvm/kvm_main.c       | 2 +-
 4 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 2/2] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
##### From: yadong.qi@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Qi, Yadong" <yadong.qi@intel.com>
X-Patchwork-Id: 11886223
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8239DC388F2
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 06:51:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EE68206A4
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 06:51:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726339AbgKFGvn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 01:51:43 -0500
Received: from mga09.intel.com ([134.134.136.24]:59061 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725842AbgKFGvm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Nov 2020 01:51:42 -0500
IronPort-SDR: 
 A9dVzy4xvPfkOip7KLYns/KWOiW5+FWnwhY/BYirUta3N8VajjT/+NVLz9zosyKRVEmoD6H2e9
 mJI6Lj7oc6lw==
X-IronPort-AV: E=McAfee;i="6000,8403,9796"; a="169659862"
X-IronPort-AV: E=Sophos;i="5.77,455,1596524400";
   d="scan'208";a="169659862"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Nov 2020 22:51:41 -0800
IronPort-SDR: 
 d0svsbFeVXli8MM2DmxpPXMh5BrJfU0WnQ5OPni4sTnq33S0tq8mnxCVYzD6CGFzUVphqZ8mMz
 HMtOVySzfOcw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,455,1596524400";
   d="scan'208";a="364087368"
Received: from yadong-antec.sh.intel.com ([10.239.158.61])
  by FMSMGA003.fm.intel.com with ESMTP; 05 Nov 2020 22:51:40 -0800
From: yadong.qi@intel.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, yadong.qi@intel.com
Subject: [PATCH v2 2/2] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
Date: Fri,  6 Nov 2020 14:51:22 +0800
Message-Id: <20201106065122.403183-1-yadong.qi@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yadong Qi <yadong.qi@intel.com>

Background: We have a lightweight HV, it needs INIT-VMExit and
SIPI-VMExit to wake-up APs for guests since it do not monitor
the Local APIC. But currently virtual wait-for-SIPI(WFS) state
is not supported in nVMX, so when running on top of KVM, the L1
HV cannot receive the INIT-VMExit and SIPI-VMExit which cause
the L2 guest cannot wake up the APs.

According to Intel SDM Chapter 25.2 Other Causes of VM Exits,
SIPIs cause VM exits when a logical processor is in
wait-for-SIPI state.

In this patch:
    1. introduce SIPI exit reason,
    2. introduce wait-for-SIPI state for nVMX,
    3. advertise wait-for-SIPI support to guest.

When L1 hypervisor is not monitoring Local APIC, L0 need to emulate
INIT-VMExit and SIPI-VMExit to L1 to emulate INIT-SIPI-SIPI for
L2. L2 LAPIC write would be traped by L0 Hypervisor(KVM), L0 should
emulate the INIT/SIPI vmexit to L1 hypervisor to set proper state
for L2's vcpu state.

Handle procdure:
Source vCPU:
    L2 write LAPIC.ICR(INIT).
    L0 trap LAPIC.ICR write(INIT): inject a latched INIT event to target
       vCPU.
Target vCPU:
    L0 emulate an INIT VMExit to L1 if is guest mode.
    L1 set guest VMCS, guest_activity_state=WAIT_SIPI, vmresume.
    L0 set vcpu.mp_state to INIT_RECEIVED if (vmcs12.guest_activity_state
       == WAIT_SIPI).

Source vCPU:
    L2 write LAPIC.ICR(SIPI).
    L0 trap LAPIC.ICR write(INIT): inject a latched SIPI event to traget
       vCPU.
Target vCPU:
    L0 emulate an SIPI VMExit to L1 if (vcpu.mp_state == INIT_RECEIVED).
    L1 set CS:IP, guest_activity_state=ACTIVE, vmresume.
    L0 resume to L2.
    L2 start-up.

Signed-off-by: Yadong Qi <yadong.qi@intel.com>
Message-Id: <20200922052343.84388-1-yadong.qi@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
v1->v2:
 * sync_vmcs02_to_vmcs12(): set vmcs12->guest_activity_state to WAIT_SIPI
   if vcpu's mp_state is INIT_RECEIVED state.
---
 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  2 ++
 arch/x86/kvm/vmx/nested.c       | 55 ++++++++++++++++++++++++---------
 3 files changed, 44 insertions(+), 14 deletions(-)

```
#### [PATCH] x86/kvm: remove unused macro HV_CLOCK_SIZE
##### From: Alex Shi <alex.shi@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Shi <alex.shi@linux.alibaba.com>
X-Patchwork-Id: 11886391
Return-Path: <SRS0=V6CK=EM=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0894EC55178
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 08:39:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A882120B80
	for <kvm@archiver.kernel.org>; Fri,  6 Nov 2020 08:39:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726443AbgKFIjh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 6 Nov 2020 03:39:37 -0500
Received: from out30-56.freemail.mail.aliyun.com ([115.124.30.56]:56903 "EHLO
        out30-56.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725830AbgKFIjh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Nov 2020 03:39:37 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R171e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=alimailimapcm10staff010182156082;MF=alex.shi@linux.alibaba.com;NM=1;PH=DS;RN=13;SR=0;TI=SMTPD_---0UEPYmPR_1604651973;
Received: from aliy80.localdomain(mailfrom:alex.shi@linux.alibaba.com
 fp:SMTPD_---0UEPYmPR_1604651973)
          by smtp.aliyun-inc.com(127.0.0.1);
          Fri, 06 Nov 2020 16:39:33 +0800
From: Alex Shi <alex.shi@linux.alibaba.com>
To: hpa@zytor.com
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] x86/kvm: remove unused macro HV_CLOCK_SIZE
Date: Fri,  6 Nov 2020 16:39:23 +0800
Message-Id: <1604651963-10067-1-git-send-email-alex.shi@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This macro is useless, and could cause gcc warning:
arch/x86/kernel/kvmclock.c:47:0: warning: macro "HV_CLOCK_SIZE" is not
used [-Wunused-macros]
Let's remove it.

Signed-off-by: Alex Shi <alex.shi@linux.alibaba.com>
Cc: Paolo Bonzini <pbonzini@redhat.com> 
Cc: Sean Christopherson <sean.j.christopherson@intel.com> 
Cc: Vitaly Kuznetsov <vkuznets@redhat.com> 
Cc: Wanpeng Li <wanpengli@tencent.com> 
Cc: Jim Mattson <jmattson@google.com> 
Cc: Joerg Roedel <joro@8bytes.org> 
Cc: Thomas Gleixner <tglx@linutronix.de> 
Cc: Ingo Molnar <mingo@redhat.com> 
Cc: Borislav Petkov <bp@alien8.de> 
Cc: x86@kernel.org 
Cc: "H. Peter Anvin" <hpa@zytor.com> 
Cc: kvm@vger.kernel.org 
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kernel/kvmclock.c | 1 -
 1 file changed, 1 deletion(-)

```
