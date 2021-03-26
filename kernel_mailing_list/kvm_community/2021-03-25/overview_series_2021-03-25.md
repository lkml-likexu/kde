#### [PATCH kvm-unit-tests 1/2] arm64: argc is an int
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12164533
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3E8D3C433C1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 15:57:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B9A661A21
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 15:57:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229642AbhCYP52 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 11:57:28 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29827 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229728AbhCYP5I (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 11:57:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616687828;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=b0//FBRo6OokAHUTq5nOdjoQhfXAjaYtHnLIY4ZWJ6U=;
        b=ZQ3ofn0Q7z/cRwXqcaiT/EO0SSqFEZwCfyUC/Gqwytg/sbWjYzTxJGJ1cllo2V+5zF6Zkf
        ToYa4aNj4yflkwItamZ1TsMgpmnOT3nDUrv8ViyAw6zkNnS5RZ+HeTtadFjqj/MLx89Iov
        yrXWL4h7BRBmUC1r/kmIY+ZAAMLTLCc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-303-z6Elz8moOMeskB22z9nwNA-1; Thu, 25 Mar 2021 11:57:03 -0400
X-MC-Unique: z6Elz8moOMeskB22z9nwNA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 98A961012EE0;
        Thu, 25 Mar 2021 15:57:02 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B2E05D736;
        Thu, 25 Mar 2021 15:57:01 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: nikos.nikoleris@arm.com, alexandru.elisei@arm.com
Subject: [PATCH kvm-unit-tests 1/2] arm64: argc is an int
Date: Thu, 25 Mar 2021 16:56:56 +0100
Message-Id: <20210325155657.600897-2-drjones@redhat.com>
In-Reply-To: <20210325155657.600897-1-drjones@redhat.com>
References: <20210325155657.600897-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If argc isn't aligned to eight bytes then loading it as if it's
eight bytes wide is a bad idea. It's only four bytes wide, so we
should only load four bytes.

Reported-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 arm/cstart64.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH for-stable-5.10 1/2] KVM: arm64: Rename __vgic_v3_get_ich_vtr_el2() to __vgic_v3_get_gic_config()
##### From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shameerali Kolothum Thodi
 <shameerali.kolothum.thodi@huawei.com>
X-Patchwork-Id: 12163567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1AE4AC433E6
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:16:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A2D261A0E
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:16:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229934AbhCYJPp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:15:45 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:13695 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229832AbhCYJP0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 05:15:26 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4F5fX06SNtznTqc;
        Thu, 25 Mar 2021 17:12:48 +0800 (CST)
Received: from S00345302A-PC.china.huawei.com (10.47.26.249) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.498.0; Thu, 25 Mar 2021 17:15:11 +0800
From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <stable@vger.kernel.org>
CC: <maz@kernel.org>, <pbonzini@redhat.com>, <linuxarm@huawei.com>
Subject: [PATCH for-stable-5.10 1/2] KVM: arm64: Rename
 __vgic_v3_get_ich_vtr_el2() to __vgic_v3_get_gic_config()
Date: Thu, 25 Mar 2021 09:14:23 +0000
Message-ID: <20210325091424.26348-2-shameerali.kolothum.thodi@huawei.com>
X-Mailer: git-send-email 2.12.0.windows.1
In-Reply-To: <20210325091424.26348-1-shameerali.kolothum.thodi@huawei.com>
References: <20210325091424.26348-1-shameerali.kolothum.thodi@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.47.26.249]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Zyngier <maz@kernel.org>

commit b9d699e2694d032aa8ecc15141f698ccb050dc95 upstream.

As we are about to report a bit more information to the rest of
the kernel, rename __vgic_v3_get_ich_vtr_el2() to the more
explicit __vgic_v3_get_gic_config().

No functional change.

Cc: stable@vger.kernel.org #5.10
Tested-by: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Message-Id: <20210305185254.3730990-7-maz@kernel.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
[Shameer: Back ported to 5.10]
Signed-off-by: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
---
 arch/arm64/include/asm/kvm_asm.h   | 4 ++--
 arch/arm64/kvm/hyp/nvhe/hyp-main.c | 4 ++--
 arch/arm64/kvm/hyp/vgic-v3-sr.c    | 7 ++++++-
 arch/arm64/kvm/vgic/vgic-v3.c      | 4 +++-
 4 files changed, 13 insertions(+), 6 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.12, take #3
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12163823
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 40741C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 11:46:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E217761A17
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 11:46:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230192AbhCYLpj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 07:45:39 -0400
Received: from mail.kernel.org ([198.145.29.99]:48374 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230093AbhCYLov (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 07:44:51 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id AB1BE6191D;
        Thu, 25 Mar 2021 11:44:50 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lPOPw-003jQY-B6; Thu, 25 Mar 2021 11:44:48 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Shameerali Kolothum Thodi
        <shameerali.kolothum.thodi@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 fixes for 5.12, take #3
Date: Thu, 25 Mar 2021 11:44:30 +0000
Message-Id: <20210325114430.940449-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, catalin.marinas@arm.com,
 mark.rutland@arm.com, shameerali.kolothum.thodi@huawei.com,
 suzuki.poulose@arm.com, will@kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's another set of fixes for KVM/arm64 in 5.12.

One patch fixes a GICv3 MMIO regression introduced when working around
a firmware bug. The last two patches prevent the guest from messing
with the ARMv8.4 tracing, a new feature that was introduced in 5.12.

Please pull,

	M.

The following changes since commit 1e28eed17697bcf343c6743f0028cc3b5dd88bf0:

  Linux 5.12-rc3 (2021-03-14 14:41:02 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.12-3

for you to fetch changes up to af22df997d71c32304d6835a8b690281063b8010:

  KVM: arm64: Fix CPU interface MMIO compatibility detection (2021-03-24 17:26:38 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.12, take #3

- Fix GICv3 MMIO compatibility probing
- Prevent guests from using the ARMv8.4 self-hosted tracing extension

----------------------------------------------------------------
Marc Zyngier (1):
      KVM: arm64: Fix CPU interface MMIO compatibility detection

Suzuki K Poulose (2):
      KVM: arm64: Hide system instruction access to Trace registers
      KVM: arm64: Disable guest access to trace filter controls

 arch/arm64/include/asm/kvm_arm.h | 1 +
 arch/arm64/kernel/cpufeature.c   | 1 -
 arch/arm64/kvm/debug.c           | 2 ++
 arch/arm64/kvm/hyp/vgic-v3-sr.c  | 9 +++++++++
 4 files changed, 12 insertions(+), 1 deletion(-)
```
#### [PATCH v4 03/25] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12163619
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11AD8C433E1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:32:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C62B561A13
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:32:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229904AbhCYJbm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:31:42 -0400
Received: from mga04.intel.com ([192.55.52.120]:55109 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229801AbhCYJbQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 05:31:16 -0400
IronPort-SDR: 
 l0wsgvFRYPWEqURZY2hlwrYIlYbua13ZUlhz2862gor5aTCXMVCPoQ9hcMNJRvQvrwX7j32yri
 1g7f+Xr2YxpA==
X-IronPort-AV: E=McAfee;i="6000,8403,9933"; a="188594239"
X-IronPort-AV: E=Sophos;i="5.81,277,1610438400";
   d="scan'208";a="188594239"
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2021 02:31:15 -0700
IronPort-SDR: 
 yLWD9+gztRO1m3vuBwerhVlcIeJBnLvC9t11uas0LGvHRhHZG33A758Ytzq9If3JWDBnGzVk3F
 0zfjNI44nYsg==
X-IronPort-AV: E=Sophos;i="5.81,277,1610438400";
   d="scan'208";a="593707776"
Received: from phanl-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.4.149])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2021 02:31:11 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v4 03/25] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
Date: Thu, 25 Mar 2021 22:30:57 +1300
Message-Id: <20210325093057.122834-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: 
 <062acb801926b2ade2f9fe1672afb7113453a741.1616136308.git.kai.huang@intel.com>
References: 
 <062acb801926b2ade2f9fe1672afb7113453a741.1616136308.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EREMOVE takes a page and removes any association between that page and
an enclave.  It must be run on a page before it can be added into
another enclave.  Currently, EREMOVE is run as part of pages being freed
into the SGX page allocator.  It is not expected to fail, as it would
indicate a use-after-free of EPC.  Rather than add the page back to the
pool of available EPC, the kernel intentionally leaks the page to avoid
additional errors in the future.

However, KVM does not track how guest pages are used, which means that
SGX virtualization use of EREMOVE might fail.  Specifically, it is
legitimate that EREMOVE returns SGX_CHILD_PRESENT for EPC assigned to
KVM guest, because KVM/kernel doesn't track SECS pages.

To allow SGX/KVM to introduce a more permissive EREMOVE helper and to
let the SGX virtualization code use the allocator directly, break out
the EREMOVE call from the SGX page allocator.  Rename the original
sgx_free_epc_page() to sgx_encl_free_epc_page(), indicating that it is
used to free EPC page assigned host enclave. Replace sgx_free_epc_page()
with sgx_encl_free_epc_page() in all call sites so there's no functional
change.

At the same time improve error message when EREMOVE fails, and add
documentation to explain to user what is the bug and suggest user what
to do when this bug happens, although extremely unlikely.

Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 Documentation/x86/sgx.rst       | 27 +++++++++++++++++++++++++++
 arch/x86/kernel/cpu/sgx/encl.c  | 32 +++++++++++++++++++++++++++-----
 arch/x86/kernel/cpu/sgx/encl.h  |  1 +
 arch/x86/kernel/cpu/sgx/ioctl.c |  6 +++---
 arch/x86/kernel/cpu/sgx/main.c  | 14 +++++---------
 arch/x86/kernel/cpu/sgx/sgx.h   |  5 +++++
 6 files changed, 68 insertions(+), 17 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86/mmu: Ensure TLBs are flushed when yielding during GFN range zap
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12164975
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7664FC433E0
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:02:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4979261A3C
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:02:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230292AbhCYUBy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 16:01:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38802 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230207AbhCYUB0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 16:01:26 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D2FC3C06175F
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 13:01:25 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id o129so7225476ybg.23
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 13:01:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=bMcMos9BxmswAdcj9I5H8fXsWRSXs/EVwTiHiGHOsOY=;
        b=PFM/CnLJfGE9dt84Qkxqh66Uem2KZM0cP8UlgtzjuZzda5Wsr8aIN/ldVweNiq9uD8
         qqnt6Qr3sT7znhbTP/skOFI4yeCtfdoe6jA8/zHhIJtcg2cZVkTf3bGz8r7T4glF2rWB
         3nZjbgVUufzgyX6RRI4Y8DpoN1Ao9VMRbdzRLO+8OxW2OtTBahxr2ogVs+pmGRo1Xo2G
         aOPV1+WCUSGxSewOLEyroXdq2n9t3BVmnPZYEXn58IgWLGfMXEtOOpiIEGHbmJdl/rfn
         sLBhweTJaxZmUE0ASGME+gv39+WJsL0GrHdKB5SRgoLmesMHqlnjy7LyqPiWqPalp8pL
         zEHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=bMcMos9BxmswAdcj9I5H8fXsWRSXs/EVwTiHiGHOsOY=;
        b=TQMG7krBSu542ayr1zyO/Big3FQb8+dZJO64Wyi2ik/Yt40feqZtMsosWkhqXnbZ72
         tPP88s5KFDbTrvzBtLc7dKRa9JczHLg8AwSpE4tP5EZx+w2DGrS+12soIFCgRnZcXBCN
         HlnjWgcjRcfSLtiPMGQriBS7Is5PoSm/cQkki8txOYTVSy1g8eYDW6of6J9al9PxuHvw
         WFucuFTk1DFQ1GJQ13Nrpq+BsP6/qBta4XRw/h4NmiC/4Qq02EaGQoXeEIcsQ12h9YSx
         nqGpTcRazU6hedfYRyuQJb0ndl/5Nnvk1a0tArwBPHsfff9bWmXtLujc40X6UoxEjLKX
         4cXw==
X-Gm-Message-State: AOAM532qxI++k4vhRFNkzntlt9M5SnfYd4LHpG7uaP2W3R0MANPRBPji
        qQCqSx3nBeZZKQMI5aIDf6HXp04j/oo=
X-Google-Smtp-Source: 
 ABdhPJwGQWNqRREIxqh6uPBp5V55wXs3SH7jUkm8iK1STOk7n7m/ZX9Hs1cFqPdAv1zSYhlzook0fe3o6oQ=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b1bb:fab2:7ef5:fc7d])
 (user=seanjc job=sendgmr) by 2002:a25:4444:: with SMTP id
 r65mr15099364yba.84.1616702485021;
 Thu, 25 Mar 2021 13:01:25 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Mar 2021 13:01:17 -0700
In-Reply-To: <20210325200119.1359384-1-seanjc@google.com>
Message-Id: <20210325200119.1359384-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210325200119.1359384-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH v2 1/3] KVM: x86/mmu: Ensure TLBs are flushed when yielding
 during GFN range zap
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When flushing a range of GFNs across multiple roots, ensure any pending
flush from a previous root is honored before yielding while walking the
tables of the current root.

Note, kvm_tdp_mmu_zap_gfn_range() now intentionally overwrites its local
"flush" with the result to avoid redundant flushes.  zap_gfn_range()
preserves and return the incoming "flush", unless of course the flush was
performed prior to yielding and no new flush was triggered.

Fixes: 1af4a96025b3 ("KVM: x86/mmu: Yield in TDU MMU iter even if no SPTES changed")
Cc: stable@vger.kernel.org
Reviewed-by: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 23 ++++++++++++-----------
 1 file changed, 12 insertions(+), 11 deletions(-)

```
#### [PATCH] MAINTAINERS: add backups for s390 vfio drivers
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 12164133
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNWANTED_LANGUAGE_BODY,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A148AC433C1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 13:42:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7877861A26
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 13:42:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230433AbhCYNmJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 09:42:09 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32036 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S230095AbhCYNmE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 09:42:04 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12PDWjXn009630;
        Thu, 25 Mar 2021 09:42:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version; s=pp1;
 bh=s+fdqLXlJZN9zhPNr5jqz7cIFYyY/irUMYt684eSHV4=;
 b=gyLV1z8WOcYoWNPuuqp9AcmDYVkKawEGR7I5no/gTmhUyvbC6EwsO7TDCpVMMJl1LaUu
 UpO5e8iekMzvKm6woOysu3nQtMeDoIzIq3SrrHRGSXjbv/NceJ5y/+CjL4OQxf/D5gLg
 W69hwvKE83ymCMizesX3AGdT5WQucWKjH6uIepS0Rkc6D9PDMKIUkGrcrpaEmUu+GYYR
 +r7MVO17RhzC++Vb+NlFyTfe7guQJFaCCUi69HVHy3BME7RBzI2GY7SYTfXCGV9kuNbu
 CvZTkLfzEESiGmvDfr1tiii9LDoKUvX+dw1m0ZOCfwAU9uLTTOwS60jh+CLHSxdSaj4/ aQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ggpksab7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 09:42:02 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12PDYweK023607;
        Thu, 25 Mar 2021 09:42:01 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ggpksaax-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 09:42:01 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12PDbQin031411;
        Thu, 25 Mar 2021 13:42:00 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma03wdc.us.ibm.com with ESMTP id 37d9dae0fg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 13:42:00 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 12PDfxLu19530020
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 13:41:59 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7697FAC05F;
        Thu, 25 Mar 2021 13:41:59 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6DAC2AC059;
        Thu, 25 Mar 2021 13:41:56 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.67.166])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 13:41:56 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, farman@linux.ibm.com,
        jjherne@linux.ibm.com, pasic@linux.ibm.com, akrowiak@linux.ibm.com,
        pmorel@linux.ibm.com, cohuck@redhat.com, hca@linux.ibm.com,
        gor@linux.ibm.com, alex.williamson@redhat.com
Subject: [PATCH] MAINTAINERS: add backups for s390 vfio drivers
Date: Thu, 25 Mar 2021 09:41:52 -0400
Message-Id: <1616679712-7139-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_03:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 priorityscore=1501 mlxscore=0 lowpriorityscore=0 mlxlogscore=999
 bulkscore=0 suspectscore=0 malwarescore=0 phishscore=0 adultscore=0
 clxscore=1011 impostorscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2103250101
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a backup for s390 vfio-pci, an additional backup for vfio-ccw
and replace the backup for vfio-ap as Pierre is focusing on other
areas.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Acked-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Eric Farman <farman@linux.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 MAINTAINERS | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PULL kvm-unit-tests] gitlab MR requested
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12164631
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 00A93C433C1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 16:58:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDC3461A2E
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 16:58:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229662AbhCYQ6I (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 12:58:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:39007 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230023AbhCYQ5t (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 12:57:49 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616691469;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=OkdD658SEO/NzvgjN3+K50bDns6ctvCU/OUXeGGvGOo=;
        b=CbplpYDHL2GNlln+MqWvlLwIWz+8UbQ4alzNI8F47oc+6oH5iNR7Bgezp3ggyfoCWWbebO
        zC55KM6WdhpDq6bYKwLjYslCc+WPfKZh2qX3DhxvkopQ+zoC6KylzOXdZDpKDrz7BBhWWJ
        h86VwOFhAg2ndMmkv9yQfkmUjHnVI4k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-360-ERdUVsXVNBu2GVrsEw_nLA-1; Thu, 25 Mar 2021 12:57:43 -0400
X-MC-Unique: ERdUVsXVNBu2GVrsEw_nLA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DB09E80006E;
        Thu, 25 Mar 2021 16:57:42 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7B41F5C3DF;
        Thu, 25 Mar 2021 16:57:39 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, alexandru.elisei@arm.com,
        nikos.nikoleris@arm.com, wangjingyi11@huawei.com
Subject: [PULL kvm-unit-tests] gitlab MR requested
Date: Thu, 25 Mar 2021 17:57:37 +0100
Message-Id: <20210325165737.604357-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 3054ca26152d01aed6e4a9b7dc03e447882aeccc:

  Merge branch 's390x-pull-2021-08-03' of https://gitlab.com/frankja/kvm-unit-tests.git into 'master' (2021-03-08 14:35:51 +0000)

are available in the Git repository at:

  https://gitlab.com/rhdrjones/kvm-unit-tests.git arm/queue

for you to fetch changes up to a09aa3fb909cf5be5a7bb0e0c1f2c36fdde2af94:

  arm64: Output PC load offset on unhandled exceptions (2021-03-25 17:26:05 +0100)

----------------------------------------------------------------
Alexandru Elisei (19):
      arm: pmu: Don't read PMCR if PMU is not present
      lib: arm/arm64: gicv3: Add missing barrier when sending IPIs
      lib: arm/arm64: gicv2: Document existing barriers when sending IPIs
      arm/arm64: gic: Remove SMP synchronization from ipi_clear_active_handler()
      arm/arm64: gic: Remove unnecessary synchronization with stats_reset()
      arm/arm64: gic: Use correct memory ordering for the IPI test
      arm/arm64: gic: Check spurious and bad_sender in the active test
      arm/arm64: gic: Wait for writes to acked or spurious to complete
      arm/arm64: gic: Split check_acked() into two functions
      arm/arm64: gic: Make check_acked() more generic
      arm64: gic: its-trigger: Don't trigger the LPI while it is pending
      arm64: gic: Use IPI test checking for the LPI tests
      configure: arm/arm64: Add --earlycon option to set UART type and address
      arm64: Remove unnecessary ISB when writing to SPSel
      arm/arm64: Remove dcache_line_size global variable
      arm/arm64: Remove unnecessary ISB when doing dcache maintenance
      lib: arm64: Consolidate register definitions to sysreg.h
      arm64: Configure SCTLR_EL1 at boot
      arm64: Disable TTBR1_EL1 translation table walks

Andrew Jones (4):
      compiler: Add builtin overflow flag and predicate wrappers
      arm/arm64: Zero BSS and stack at startup
      arm64: argc is an int
      arm64: Output PC load offset on unhandled exceptions

Jingyi Wang (1):
      arm64: microbench: fix unexpected PPI

Nikos Nikoleris (7):
      lib/string: Add strnlen, strrchr and strtoul
      libfdt: Pull v1.6.0
      Makefile: Remove overriding recipe for libfdt_clean
      devicetree: Parse correctly the stdout-path
      arm/arm64: Avoid calling cpumask_test_cpu for CPUs above nr_cpus
      arm/arm64: Read system registers to get the state of the MMU
      arm/arm64: Add sanity checks to the cpumask API

 Makefile                      |  16 +-
 arm/Makefile.common           |   2 +-
 arm/cstart.S                  |  39 +-
 arm/cstart64.S                |  53 ++-
 arm/flat.lds                  |   5 +
 arm/gic.c                     | 336 ++++++++--------
 arm/micro-bench.c             |   2 +-
 arm/pmu.c                     |   3 +-
 configure                     |  53 +++
 lib/arm/asm/assembler.h       |  53 +++
 lib/arm/asm/cpumask.h         |   7 +-
 lib/arm/asm/mmu-api.h         |   7 +-
 lib/arm/asm/processor.h       |   9 +-
 lib/arm/gic-v2.c              |   6 +
 lib/arm/gic-v3.c              |   6 +
 lib/arm/mmu.c                 |  20 +-
 lib/arm/processor.c           |   5 +
 lib/arm/setup.c               |   7 -
 lib/arm64/asm/arch_gicv3.h    |   6 -
 lib/arm64/asm/assembler.h     |  54 +++
 lib/arm64/asm/pgtable-hwdef.h |   1 +
 lib/arm64/asm/processor.h     |  18 +-
 lib/arm64/asm/sysreg.h        |  24 ++
 lib/arm64/processor.c         |  12 +
 lib/devicetree.c              |  15 +-
 lib/libfdt/Makefile.libfdt    |  10 +-
 lib/libfdt/README             |   5 +-
 lib/libfdt/fdt.c              | 200 ++++++----
 lib/libfdt/fdt.h              |  53 +--
 lib/libfdt/fdt_addresses.c    | 101 +++++
 lib/libfdt/fdt_check.c        |  74 ++++
 lib/libfdt/fdt_empty_tree.c   |  48 +--
 lib/libfdt/fdt_overlay.c      | 881 ++++++++++++++++++++++++++++++++++++++++++
 lib/libfdt/fdt_ro.c           | 512 ++++++++++++++++++------
 lib/libfdt/fdt_rw.c           | 231 ++++++-----
 lib/libfdt/fdt_strerror.c     |  53 +--
 lib/libfdt/fdt_sw.c           | 297 +++++++++-----
 lib/libfdt/fdt_wip.c          |  90 ++---
 lib/libfdt/libfdt.h           | 766 +++++++++++++++++++++++++++++++-----
 lib/libfdt/libfdt_env.h       | 109 +++---
 lib/libfdt/libfdt_internal.h  | 206 +++++++---
 lib/libfdt/version.lds        |  24 +-
 lib/linux/compiler.h          |  33 ++
 lib/stdlib.h                  |  13 +
 lib/string.c                  | 101 ++++-
 lib/string.h                  |   5 +-
 powerpc/Makefile.common       |   2 +-
 47 files changed, 3478 insertions(+), 1095 deletions(-)
 create mode 100644 lib/arm/asm/assembler.h
 create mode 100644 lib/arm64/asm/assembler.h
 create mode 100644 lib/libfdt/fdt_addresses.c
 create mode 100644 lib/libfdt/fdt_check.c
 create mode 100644 lib/libfdt/fdt_overlay.c
 create mode 100644 lib/stdlib.h
```
#### [PATCH v5 1/1] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12164047
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CE248C433E1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:48:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9FAC661A1F
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:48:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230439AbhCYMra (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 08:47:30 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:12722 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230415AbhCYMq4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 08:46:56 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCX0SY064871;
        Thu, 25 Mar 2021 08:46:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=yE/tgn8TsGGWfwZvscViVckPGKQ+BXrVjLXWphq5lls=;
 b=GKqKERtxS9u0mOmH91YGxVc/6yftJAQY3D2QvnGY+zWG1xKN49dWWAWcf+5m1DGKSmaD
 MkDIpAKEZ0O8te0kkvxk+H7b3tvIN9IHsxrNA9v4M9JKrgv9q9YI67Koq/5wkN6ucNXH
 gCL3ZVKF0RVAU7+BbPbxy4m62I22Uic8dUqwbf9kF3O3cqDL9a85bfK1CzC1u3+N9H9O
 1T9Kt0l7Hxm/PXQKA4/iIlluFap5qVyEWFLeWPsEG6qXBSjf+PSmyqeD7+2JkbBZ3F7O
 hidVfuLv0AYolEktoJzuOVnrf/NysDEodPSCo5x6mgiD3ND13BErc5AiH52rmk7Gzp/5 TA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37grmv3xc7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 08:46:54 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12PCYaJi073449;
        Thu, 25 Mar 2021 08:46:54 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37grmv3xbq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 08:46:54 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCRRuc030591;
        Thu, 25 Mar 2021 12:46:52 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma03wdc.us.ibm.com with ESMTP id 37d9dadnjc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 12:46:52 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12PCkpvU30343534
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 12:46:51 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 72BC1136051;
        Thu, 25 Mar 2021 12:46:51 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1C5BC136055;
        Thu, 25 Mar 2021 12:46:50 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.150.254])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 12:46:49 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v5 1/1] s390/vfio-ap: fix circular lockdep when
 setting/clearing crypto masks
Date: Thu, 25 Mar 2021 08:46:40 -0400
Message-Id: <20210325124640.23995-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20210325124640.23995-1-akrowiak@linux.ibm.com>
References: <20210325124640.23995-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_03:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 lowpriorityscore=0 spamscore=0 suspectscore=0 bulkscore=0 mlxlogscore=999
 mlxscore=0 phishscore=0 malwarescore=0 clxscore=1015 priorityscore=1501
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103250093
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch fixes a lockdep splat introduced by commit f21916ec4826
("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated").
The lockdep splat only occurs when starting a Secure Execution guest.
Crypto virtualization (vfio_ap) is not yet supported for SE guests;
however, in order to avoid this problem when support becomes available,
this fix is being provided.

The circular locking dependency was introduced when the setting of the
masks in the guest's APCB was executed while holding the matrix_dev->lock.
While the lock is definitely needed to protect the setting/unsetting of the
matrix_mdev->kvm pointer, it is not necessarily critical for setting the
masks; so, the matrix_dev->lock will be released while the masks are being
set or cleared.

Keep in mind, however, that another process that takes the matrix_dev->lock
can get control while the masks in the guest's APCB are being set or
cleared as a result of the driver being notified that the KVM pointer
has been set or unset. This could result in invalid access to the
matrix_mdev->kvm pointer by the intervening process. To avoid this
scenario, two new fields are being added to the ap_matrix_mdev struct:

struct ap_matrix_mdev {
	...
	bool kvm_busy;
	wait_queue_head_t wait_for_kvm;
   ...
};

The functions that handle notification that the KVM pointer value has
been set or cleared will set the kvm_busy flag to true until they are done
processing at which time they will set it to false and wake up the tasks on
the matrix_mdev->wait_for_kvm wait queue. Functions that require
access to matrix_mdev->kvm will sleep on the wait queue until they are
awakened at which time they can safely access the matrix_mdev->kvm
field.

Fixes: f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c     | 309 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 96 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/8] s390x: lib: css: disabling a subchannel
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12163639
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0BE68C433E4
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:40:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D89BC61934
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:40:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229533AbhCYJjz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:39:55 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:46970 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229461AbhCYJjO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 05:39:14 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12P9Xp49051000
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=ZpyJi2Gq+gX3DUflwv+yFRHfQtDPzyYMP7ZyBf1wSPo=;
 b=IztsAevd6hb0QWtHKCyiNm/ujDr0teiX3+ACMQsqce/9qPNQ8jhCnNvhlkKpOpfuUCiv
 W5nI2FGCYrrUpEaM/8ACUitZL15IXZhG/7NIpD9oavHnV47FDodIwMNwxyI1cQAy7MFM
 Y+w59VqlNfKazZcVkguAg6Z4ZaeSCTEaeEcFTnoKFw6B0V0bXtMUzg6i/5VP4yebwjdA
 i/fT+X0PxLQFUPVbkj33vGnEobV+6HA2sK1JXCRGYDQyzKDupT0sBHpAw8YiznuViGAb
 asupvEyrO4z8T1yRcdTSIbh+FbYKGdN8xV6tdPg470G6aXj4wz367M68DCz3i39a1RjZ tQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37gq0b1v5s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:14 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12P9XsWL051328
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:13 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37gq0b1v4m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 05:39:13 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12P9R9ml007119;
        Thu, 25 Mar 2021 09:39:12 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 37d99rd6y1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 09:39:12 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12P9d9h935979544
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 09:39:09 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3D2AF11C054;
        Thu, 25 Mar 2021 09:39:09 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EFF9611C05B;
        Thu, 25 Mar 2021 09:39:08 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.41.31])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 09:39:08 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/8] s390x: lib: css: disabling a subchannel
Date: Thu, 25 Mar 2021 10:39:00 +0100
Message-Id: <1616665147-32084-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1616665147-32084-1-git-send-email-pmorel@linux.ibm.com>
References: <1616665147-32084-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_02:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 bulkscore=0
 adultscore=0 priorityscore=1501 suspectscore=0 mlxscore=0 malwarescore=0
 mlxlogscore=999 phishscore=0 clxscore=1015 spamscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103250072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some tests require to disable a subchannel.
Let's implement the css_disable() function.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/css.h     |  1 +
 lib/s390x/css_lib.c | 67 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 68 insertions(+)

```
#### [PATCH] tools/kvm_stat: Add restart delay
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 12163969
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC1FAC433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:31:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A92A61A17
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:31:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229995AbhCYMai (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 08:30:38 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32200 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231244AbhCYMaM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 08:30:12 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCEK6Q191953
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 08:30:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=OCU5on0LmOLgCaV4hQezQCH2sdjoA4QqdpPkEafMZZU=;
 b=WvenQ51BkeLv3u/dbqLG1amtiC3GH6Qu42Kl3guGSRETOfa67c3OOmq6SMtXVTlJDfud
 Kxu2XqdLU86LZTBzWXOpaXcp1bCGVyew3TtOVT6vObSJmpsz9AbcUKkn0aElD3+mUoEz
 PxUOzzm+y6OZYWucIi6kJS+Dero1PkrUb9pDlbwLCYeCJ4CaV9ZnLvqxct7QijejgILj
 NOE32PsNjHSuYan/2KqcdB1iDI1dwK09QFstT3F6IKwxJmvae4stt+BiwXZs8IVk1asU
 Yzub+EeWgwVSQZ57vOQFVv9H+KrQOTH6y96N/bAOlcEQf8K0u6a4aNqe/7rrbjrLe+DH cw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37gpjv73ga-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 08:30:07 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12PCI5Z9018133
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 08:30:06 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37gpjv73f9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 08:30:06 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCSQ9m028433;
        Thu, 25 Mar 2021 12:30:04 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma01fra.de.ibm.com with ESMTP id 37d99xjtgw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 12:30:04 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12PCThnh26935662
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 12:29:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7EA40A405D;
        Thu, 25 Mar 2021 12:30:01 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4BF95A4053;
        Thu, 25 Mar 2021 12:30:01 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 12:30:01 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, pbonzini@redhat.com
Subject: [PATCH] tools/kvm_stat: Add restart delay
Date: Thu, 25 Mar 2021 13:29:49 +0100
Message-Id: <20210325122949.1433271-1-raspl@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_02:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxlogscore=999
 suspectscore=0 clxscore=1011 impostorscore=0 lowpriorityscore=0
 spamscore=0 mlxscore=0 phishscore=0 adultscore=0 malwarescore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103250091
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If this service is enabled and the system rebooted, Systemd's initial
attempt to start this unit file may fail in case the kvm module is not
loaded. Since we did not specify a delay for the retries, Systemd
restarts with a minimum delay a number of times before giving up and
disabling the service. Which means a subsequent kvm module load will
have kvm running without monitoring.
Adding a delay to fix this.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat.service | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5] vfio/pci: Add support for opregion v2.1+
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 12163571
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C51E1C433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:17:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9046661879
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:17:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229836AbhCYJQm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:16:42 -0400
Received: from mga12.intel.com ([192.55.52.136]:37019 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229576AbhCYJQd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 05:16:33 -0400
IronPort-SDR: 
 sw/+6bNSX4mAQ1rPiVVZOfjw/MhYNag6bXun6ll9WLiZCVPM07koFe0OrXHS+Zkd9MF4B0u2uW
 bbIU0h9mKpjw==
X-IronPort-AV: E=McAfee;i="6000,8403,9933"; a="170241098"
X-IronPort-AV: E=Sophos;i="5.81,277,1610438400";
   d="scan'208";a="170241098"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2021 02:16:33 -0700
IronPort-SDR: 
 NTFIndnYFO+inBmHE2s+rW7KAAK4EHsWZKzk6en68eLnL58eOfu8v5vDvHmWnWdYqfJxzoLUtl
 JWfipT+1Bvow==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,277,1610438400";
   d="scan'208";a="514538517"
Received: from cfl-host.sh.intel.com ([10.239.158.118])
  by fmsmga001.fm.intel.com with ESMTP; 25 Mar 2021 02:16:31 -0700
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Swee Yee Fonn <swee.yee.fonn@intel.com>
Subject: [PATCH v5] vfio/pci: Add support for opregion v2.1+
Date: Fri, 26 Mar 2021 01:09:53 +0800
Message-Id: <20210325170953.24549-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
In-Reply-To: <20210302130220.9349-1-fred.gao@intel.com>
References: <20210302130220.9349-1-fred.gao@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before opregion version 2.0 VBT data is stored in opregion mailbox #4,
but when VBT data exceeds 6KB size and cannot be within mailbox #4
then from opregion v2.0+, Extended VBT region, next to opregion is
used to hold the VBT data, so the total size will be opregion size plus
extended VBT region size.

Since opregion v2.0 with physical host VBT address would not be
practically available for end user and guest can not directly access
host physical address, so it is not supported.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Signed-off-by: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci_igd.c | 53 +++++++++++++++++++++++++++++++++
 1 file changed, 53 insertions(+)

```
#### [PATCH] vfio/type1: Empty batch for pfnmap pages
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Jordan <daniel.m.jordan@oracle.com>
X-Patchwork-Id: 12162611
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 007BBC433C1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 01:07:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C87C161A13
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 01:07:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232868AbhCYBGw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 24 Mar 2021 21:06:52 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:39704 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230191AbhCYBGi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 24 Mar 2021 21:06:38 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12P16M1F007896;
        Thu, 25 Mar 2021 01:06:22 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=XpOE8ZN+Go+AWUAQkjqsOhi4ZvQtbb6sgu81yXU0ItI=;
 b=GoXofFjiwJgFQQwSLqyAU5XKO5IwS8+4kVIz7GlRAwkJw0IL4NfNnluo8vZiALwOlP5f
 J/DZcRkA91N6yV4QfkxFugzyMOEV7+8Wh02iShozUWEIJ03EFSMRcQ1EI0LOJ2YkpgPD
 t/zxOkW17Rs/HwEYP7VvCdZzyzVvzp0k4OZ7UOL79wg16w3GW+8rQKsW9lzCWehoa/L+
 DO7uTXFaqsu0/y9Y2TxT/mcMOXznd4AekTSgDKIfb/GQ+Cs9uvZSveADSO3yhXjQJCrY
 BVIuxmZFjfLbHVtYu/gVDsQ9yjqTNA++snAHlb2r/D5ZnhgjuCd1KVW6uF8/u7b6UwI/ BQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 37d9pn4mpa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 01:06:22 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12P16F3c191037;
        Thu, 25 Mar 2021 01:06:21 GMT
Received: from nam02-dm3-obe.outbound.protection.outlook.com
 (mail-dm3nam07lp2044.outbound.protection.outlook.com [104.47.56.44])
        by userp3020.oracle.com with ESMTP id 37dttu21tq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 01:06:21 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=HABEH8AhrwgQaQTP/37c7zgDTxH5taRXocGSGe5Fg6xvqOcR6Obc9wRzCMSGagWi9tfxkYwLW1mvhBSIX0e1+5WBKLi7WPZUJoggGzcLKrHTtPEhCgCSRrXZVZgvTgYO1YW6VfHJmkGBDs4m+MmFB5mlNDruddaKnMfGCLrLymUUirhvv1+Bx9UfCsJu+L1Bns+r7EPtGUQZQx8hodNAqNJfgDQUrpeqC0SmfLnRNVUos7RX641/73nmQGBr3z0wz7plHWrJjpJk3fqyOMVmFNgDYHxY8WEstE8SfG3aIHPBoldXDpRzFABBDndvbnk/Uy+RcNdn/pLIPXalQU6lHQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=XpOE8ZN+Go+AWUAQkjqsOhi4ZvQtbb6sgu81yXU0ItI=;
 b=kcvmNjKIOG43OCk+dWhG6nQF/50JYkfcS3bsee0tjZPuQbHp74QC8uwITVpW1tYpxpsq/7sCcjR7MVto5hWs2iC0ZTjUAFxliGb8W+gCrr/0Xn2EfxjT3cBEkqXypMlGYb6sSgquOQfqWLjDQDWSNOTJHaVgYXAXWybXVwGb2H9plAxWQQl9ntWNdu/vo4+nDZHxjn+/cPQsjvSIKePZiljMvO+96+oedGMuiIk3dzCHdZprxvMZ8iitXP/cKYCe2jSrrWUecvnj9bJayw4yDDiON3stM2KhhragUx+U17RDXlGGTBEZqcalGYH3FG7uRgZJfE1odEoBm+5ywk9F3g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=XpOE8ZN+Go+AWUAQkjqsOhi4ZvQtbb6sgu81yXU0ItI=;
 b=NRfI+1ZYGJBN9Or6j7MmnnEIFz8f0M0ZG2OymZdYhSDWryS0Nf6aD6296LKCL4lxynlWa1nOJ8HryXANtmw2q5SdVB8CFalaSdPIr14S1NoE9D6iO1wIAJqSpE8b7GJk8KbmTHHPiBJfPY/w7goBuvhOPpNMFCLczpZRGupM3HU=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=oracle.com;
Received: from MWHPR10MB1774.namprd10.prod.outlook.com (2603:10b6:301:9::13)
 by MWHPR10MB1903.namprd10.prod.outlook.com (2603:10b6:300:10b::14) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24; Thu, 25 Mar
 2021 01:06:09 +0000
Received: from MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183]) by MWHPR10MB1774.namprd10.prod.outlook.com
 ([fe80::24eb:1300:dd70:4183%3]) with mapi id 15.20.3955.027; Thu, 25 Mar 2021
 01:06:09 +0000
From: Daniel Jordan <daniel.m.jordan@oracle.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Jason Gunthorpe <jgg@nvidia.com>,
        Matthew Wilcox <willy@infradead.org>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Steven Sistare <steven.sistare@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Daniel Jordan <daniel.m.jordan@oracle.com>
Subject: [PATCH] vfio/type1: Empty batch for pfnmap pages
Date: Wed, 24 Mar 2021 21:05:52 -0400
Message-Id: <20210325010552.185481-1-daniel.m.jordan@oracle.com>
X-Mailer: git-send-email 2.31.0
X-Originating-IP: [98.229.125.203]
X-ClientProxiedBy: BL1PR13CA0065.namprd13.prod.outlook.com
 (2603:10b6:208:2b8::10) To MWHPR10MB1774.namprd10.prod.outlook.com
 (2603:10b6:301:9::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (98.229.125.203) by
 BL1PR13CA0065.namprd13.prod.outlook.com (2603:10b6:208:2b8::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.10 via Frontend
 Transport; Thu, 25 Mar 2021 01:06:08 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: c1be3929-19ec-47ea-5b1d-08d8ef2a2cd2
X-MS-TrafficTypeDiagnostic: MWHPR10MB1903:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MWHPR10MB1903D4A7C38D325B4FEE7672D9629@MWHPR10MB1903.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2201;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 x4A7QFkZ6Phovfm/nn35GV+i2+7DeMuZBguWSU4czXE9VNJxRvy5gTAxdnXs89yChhD9NlmG6RcQqEZu5QTVKP8LvLejYewCE3cmakppQC1Po0QyaKMAfmoKrBspScRe+xEfXDshCXWYjU0Lr6gwqnTFG7EdmdAtfyaKLFWMFoxHpdTuw2btoljqC2MuI9bikHsW2ecJEmysX3RaQ4hiSpalzPhfXbvnRpvkLHfFsYyAvjD29w4y378mypjJZ6jD3dABNn288/AljIzOxH0sXYSmGn4w2kFnweg827QZYY9UFsm7W0LH8bOKw4DyPmBF4OyWrx5ANbIXTiWzokJh79cDGRHt6a22hsICnJg8WX6Plctj8O5msc5hJ6xMFXHKMm63NvJn26PZVfiKFPCuzLc9J05oJCVhINHdoivEXfd+IV88AQN6K5euaFT3mR+goD6yWcrU0ruDEG9RsvE7rJKDEk9l45RqJhj0ofyjC6GoMfAXGPKWmn1kO15V8ur25gc2OR/8y5XXkj6GOL8xmKC4xEvnpKguYmn3zulDHhyKP/rVKvHXnItLru9pm47L+UAPvOrnknneJCEZE1Jx63iYOSySUiJYiE+4VGt/N8pKKOpVAgzfh9xRpczLMbo/PqO2PXWM42WzSl+AopVAIip9nOzNHi64nM0p+CY5QqH3YyAD0mKFwJHZXSnFK4uyybsGmpdukSNPCIsaJcLlSIA5CsKkgkgoJxKO+Nm1s22PvYvGtdv94lBYTUzuwcYkhC/KLtV+c+zL45BjsWK+UQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR10MB1774.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(376002)(346002)(39860400002)(136003)(366004)(83380400001)(69590400012)(6666004)(107886003)(2906002)(186003)(86362001)(4326008)(54906003)(5660300002)(36756003)(26005)(38100700001)(66946007)(1076003)(8676002)(316002)(16526019)(956004)(6512007)(2616005)(110136005)(66476007)(103116003)(8936002)(66556008)(966005)(52116002)(6506007)(6486002)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 vXm17k0rID+qhzkzwpoIA9umX+Pqom8+q9a7JX2jKD4ClT3yZ6mRV3mhCbxgSNLwOYoauoWwhPtLPn8wp0XitLgUfuSLt8rlpgMbD5IRz5sWwPAXNJ/TjCUGuG6PSX9MTgT7qeZBjWW8cfHmdXspED6tKkZYMMC6D4mL1qhUSp94nKyw79xb7lq9p+i5WTkmaABiM9Qj4l7rMJ5BtTR3prAmcE38QMk4JTCLkcVO1ivrxm7CR80wZFJI+49vd6kiQTTYLTIMWVrQZUKO9764oXclcsIldO9e0nv9BOKsfoFNOwkRaT4jTJvaF2n/N34+weJb9QrRPl0U3g87QdAEMEIhtxlFhiTbqbjxRWIjBNU+eqQ0wK8LdPu1/NNT4JMFerJijR8l6lEigNee11lfvhHNHe/ca3siZZkOPN5+goJ7tBOm1/mNmv3zSCS2xRzuFUjlnKgE/n3OcNskSrJob24kunZg83Vj7kjiUX/PK83o+fjAbKedj0MqnySDuXngHPWTKLYfZaE9YjexA2+1eVFGNaZ2hLkuNSVqZl04iWOXV+Wp4dqJA7pUzvyUJKY5LqkWuOkz4bTjq6MDsDH4xLb26KlYuUlZxCRI/uGphBboqY1sQcMBDlaRYiKOLjwj3M1bpXRfDNyDX518u0V0fPKS4q3qnLkPLVS1+gOcBIF1MyJ3wquA/TvIT9ftAMtaVwbA8xMzOdocwlWHQU1eDCE9OtMR2+3mshNS1wEPjhEUF+QGBPM9bQDYxTUf/WR4mhZZS0wUt/jh5GMcN0lvY1m2rzLaXrNunD/S0q7c+KPsdvb6e5DDL3LwKJEzcIz9GEP3yK58zrWi1JK8FuulPc0gykoK1od0tpmo4mZT+Vxfuk04/Ju5MOirHI4AxXyQrXBDTmJn36HvNPK9pKsH+uoBtNvnwUDlh7Mchh+Z3asBLTsZatub4wPy+Az3HdRtwzaGVLZKXKppoR8qMK+iCZYJQEkAzAwc+3n17bIqZegAcsGT6ZKblBJdVNM0AX23cQIMt3SPXO3zSN8XZD14J1V+etb3EzqaW1e5GvTaad+cXysMLTPgO0a6K/V3vPaacj25Xit/uu4wjrtiz3YpM/BH7VtfsWsR3SCB6zEZt/uM4YT8LAuZiJ+JfuUBAP5CW8wSaGTLXuxejrVPDgiYV2eP7Qra42XYw/+QKNc1cywIVgqSYZTO792W5h667Nf8nR+EYWH+IdxHfi+MuvGMPvzo3ACiFoqQM+9cybglXPuAXyrTxWBDIrOvBCr6iXoq/RrFJ8Tj3xePOM9P0pFLtiqosWvYEjknAHP3087DuMdj2PwHU8nxGxfnxPKWzRfa
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c1be3929-19ec-47ea-5b1d-08d8ef2a2cd2
X-MS-Exchange-CrossTenant-AuthSource: MWHPR10MB1774.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 25 Mar 2021 01:06:09.6091
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 bccFwRsA/CvURH7Bzt/XGtWU+2Bx9tl20zTetWOkf4XiysPN30GA8I5GUtJ8ztljKueCobIn5+QNn7iT+tg3zPG1A5AQPo3HhBbl1zp149k=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MWHPR10MB1903
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9933
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 malwarescore=0 spamscore=0
 mlxscore=0 phishscore=0 suspectscore=0 mlxlogscore=999 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103250004
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9933
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 phishscore=0
 mlxlogscore=999 priorityscore=1501 impostorscore=0 bulkscore=0 spamscore=0
 adultscore=0 clxscore=1015 malwarescore=0 mlxscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103250004
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When vfio_pin_pages_remote() returns with a partial batch consisting of
a single VM_PFNMAP pfn, a subsequent call will unfortunately try
restoring it from batch->pages, resulting in vfio mapping the wrong page
and unbalancing the page refcount.

Prevent the function from returning with this kind of partial batch to
avoid the issue.  There's no explicit check for a VM_PFNMAP pfn because
it's awkward to do so, so infer it from characteristics of the batch
instead.  This may result in occasional false positives but keeps the
code simpler.

Fixes: 4d83de6da265 ("vfio/type1: Batch page pinning")
Link: https://lkml.kernel.org/r/20210323133254.33ed9161@omen.home.shazbot.org/
Reported-by: Alex Williamson <alex.williamson@redhat.com>
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
---

Alex, I couldn't immediately find a way to trigger this bug, but I can
run your test case if you like.

This is the minimal fix, but it should still protect all calls of
vfio_batch_unpin() from this problem.

 drivers/vfio/vfio_iommu_type1.c | 6 ++++++
 1 file changed, 6 insertions(+)


base-commit: 84196390620ac0e5070ae36af84c137c6216a7dc

```
#### [PATCH] x86/tlb: Flush global mappings when KAISER is disabled
##### From: Borislav Petkov <bp@alien8.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Borislav Petkov <bp@alien8.de>
X-Patchwork-Id: 12163677
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D866DC433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 10:30:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 87BBF61A25
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 10:30:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230125AbhCYKaH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 06:30:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55446 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230076AbhCYKaE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 06:30:04 -0400
Received: from mail.skyhub.de (mail.skyhub.de
 [IPv6:2a01:4f8:190:11c2::b:1457])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 37B19C06174A;
        Thu, 25 Mar 2021 03:30:03 -0700 (PDT)
Received: from zn.tnic (p200300ec2f0d5d00d5a461c7dd3b44f2.dip0.t-ipconnect.de
 [IPv6:2003:ec:2f0d:5d00:d5a4:61c7:dd3b:44f2])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.skyhub.de (SuperMail on ZX Spectrum 128k) with ESMTPSA id
 AFE6D1EC0501;
        Thu, 25 Mar 2021 11:30:00 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=alien8.de; s=dkim;
        t=1616668200;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:in-reply-to:in-reply-to:
  references:references;
        bh=CAkDP25OFlShJCPDxQST7B40b5DDqLE/vRJZQKviFIQ=;
        b=GdX96tqMBdFMRuPKse/S5u+Fn7yuJhdOOt6Xq+BUnlxv1nfU9Ouittcw4nMEYk0s4wgFjl
        KsRna7lhZb8xuvYmGalsy8QTFdA1sKAVvm+hnk69HcRvajVPAZOIa6v1N4s2mjyV2InLaD
        HOQj5Arosp7WG6MWL/Xs5JTqzLUsuQg=
Date: Thu, 25 Mar 2021 11:29:59 +0100
From: Borislav Petkov <bp@alien8.de>
To: Hugh Dickins <hughd@google.com>
Cc: Babu Moger <babu.moger@amd.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        kvm list <kvm@vger.kernel.org>, Joerg Roedel <joro@8bytes.org>,
        the arch/x86 maintainers <x86@kernel.org>,
        LKML <linux-kernel@vger.kernel.org>,
        Ingo Molnar <mingo@redhat.com>,
        "H . Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Makarand Sonare <makarandsonare@google.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] x86/tlb: Flush global mappings when KAISER is disabled
Message-ID: <20210325102959.GD31322@zn.tnic>
References: <2ca37e61-08db-3e47-f2b9-8a7de60757e6@amd.com>
 <20210311214013.GH5829@zn.tnic>
 <d3e9e091-0fc8-1e11-ab99-9c8be086f1dc@amd.com>
 <4a72f780-3797-229e-a938-6dc5b14bec8d@amd.com>
 <20210311235215.GI5829@zn.tnic>
 <ed590709-65c8-ca2f-013f-d2c63d5ee0b7@amd.com>
 <20210324212139.GN5010@zn.tnic>
 <alpine.LSU.2.11.2103241651280.9593@eggly.anvils>
 <alpine.LSU.2.11.2103241913190.10112@eggly.anvils>
 <20210325095619.GC31322@zn.tnic>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210325095619.GC31322@zn.tnic>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ok,

I tried to be as specific as possible in the commit message so that we
don't forget. Please lemme know if I've missed something.

Babu, Jim, I'd appreciate it if you ran this to confirm.

Thx.
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Babu Moger <babu.moger@amd.com>
Acked-by: Hugh Dickins <hughd@google.com>
Tested-by: Jim Mattson <jmattson@google.com>
---
From: Borislav Petkov <bp@suse.de>
Date: Thu, 25 Mar 2021 11:02:31 +0100

Jim Mattson reported that Debian 9 guests using a 4.9-stable kernel
are exploding during alternatives patching:

  kernel BUG at /build/linux-dqnRSc/linux-4.9.228/arch/x86/kernel/alternative.c:709!
  invalid opcode: 0000 [#1] SMP
  Modules linked in:
  CPU: 1 PID: 1 Comm: swapper/0 Not tainted 4.9.0-13-amd64 #1 Debian 4.9.228-1
  Hardware name: Google Google Compute Engine/Google Compute Engine, BIOS Google 01/01/2011
  Call Trace:
   swap_entry_free
   swap_entry_free
   text_poke_bp
   swap_entry_free
   arch_jump_label_transform
   set_debug_rodata
   __jump_label_update
   static_key_slow_inc
   frontswap_register_ops
   init_zswap
   init_frontswap
   do_one_initcall
   set_debug_rodata
   kernel_init_freeable
   rest_init
   kernel_init
   ret_from_fork

triggering the BUG_ON in text_poke() which verifies whether patched
instruction bytes have actually landed at the destination.

Further debugging showed that the TLB flush before that check is
insufficient because there could be global mappings left in the TLB,
leading to a stale mapping getting used.

I say "global mappings" because the hardware configuration is a new one:
machine is an AMD, which means, KAISER/PTI doesn't need to be enabled
there, which also means there's no user/kernel pagetables split and
therefore the TLB can have global mappings.

And the configuration is new one for a second reason: because that AMD
machine supports PCID and INVPCID, which leads the CPU detection code to
set the synthetic X86_FEATURE_INVPCID_SINGLE flag.

Now, __native_flush_tlb_single() does invalidate global mappings when
X86_FEATURE_INVPCID_SINGLE is *not* set and returns.

When X86_FEATURE_INVPCID_SINGLE is set, however, it invalidates the
requested address from both PCIDs in the KAISER-enabled case. But if
KAISER is not enabled and the machine has global mappings in the TLB,
then those global mappings do not get invalidated, which would lead to
the above mismatch from using a stale TLB entry.

So make sure to flush those global mappings in the KAISER disabled case.

Co-debugged by Babu Moger <babu.moger@amd.com>.

Reported-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Borislav Petkov <bp@suse.de>
Link: https://lkml.kernel.org/r/CALMp9eRDSW66%2BXvbHVF4ohL7XhThoPoT0BrB0TcS0cgk=dkcBg@mail.gmail.com
---
 arch/x86/include/asm/tlbflush.h | 11 +++++++----
 1 file changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/tlb: Flush global mappings when KAISER is disabled
##### From: Borislav Petkov <bp@alien8.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Borislav Petkov <bp@alien8.de>
X-Patchwork-Id: 12164981
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F867C433E4
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:10:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 251ED61A3A
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:10:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230166AbhCYUKI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 16:10:08 -0400
Received: from mail.skyhub.de ([5.9.137.197]:59234 "EHLO mail.skyhub.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230258AbhCYUJk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 16:09:40 -0400
Received: from zn.tnic (p200300ec2f0d5d0094e6cb0f12bb7e2a.dip0.t-ipconnect.de
 [IPv6:2003:ec:2f0d:5d00:94e6:cb0f:12bb:7e2a])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.skyhub.de (SuperMail on ZX Spectrum 128k) with ESMTPSA id
 683AF1EC0249;
        Thu, 25 Mar 2021 21:09:38 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=alien8.de; s=dkim;
        t=1616702978;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:in-reply-to:in-reply-to:
  references:references;
        bh=mlAyvCnXo3hHmcqDcLa0T0+zPXCZVaDSlZjjwBtnDCY=;
        b=lkUeFKqn1wgy3MlXzWs7hStJOpvfYU/tTSZ8zOYUwS80eXwWt0+AaAq/qbqRDdR2dOttQd
        qDNk+HsALrwZvtX6EmcdW2Za2ZTKQEsCyb3Mt3PHOVCOECvGRx+9zhFJMJcbCU35iY/y2o
        W7f4GxpgqWzgUzEAKvw/RJPN4HHJMLs=
Date: Thu, 25 Mar 2021 21:09:42 +0100
From: Borislav Petkov <bp@alien8.de>
To: stable <stable@vger.kernel.org>
Cc: Hugh Dickins <hughd@google.com>, Babu Moger <babu.moger@amd.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        kvm list <kvm@vger.kernel.org>, Joerg Roedel <joro@8bytes.org>,
        the arch/x86 maintainers <x86@kernel.org>,
        LKML <linux-kernel@vger.kernel.org>,
        Ingo Molnar <mingo@redhat.com>,
        "H . Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Makarand Sonare <makarandsonare@google.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] x86/tlb: Flush global mappings when KAISER is disabled
Message-ID: <20210325200942.GJ31322@zn.tnic>
References: <20210311214013.GH5829@zn.tnic>
 <d3e9e091-0fc8-1e11-ab99-9c8be086f1dc@amd.com>
 <4a72f780-3797-229e-a938-6dc5b14bec8d@amd.com>
 <20210311235215.GI5829@zn.tnic>
 <ed590709-65c8-ca2f-013f-d2c63d5ee0b7@amd.com>
 <20210324212139.GN5010@zn.tnic>
 <alpine.LSU.2.11.2103241651280.9593@eggly.anvils>
 <alpine.LSU.2.11.2103241913190.10112@eggly.anvils>
 <20210325095619.GC31322@zn.tnic>
 <20210325102959.GD31322@zn.tnic>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210325102959.GD31322@zn.tnic>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi stable folks,

the patch below fixes kernels 4.4 and 4.9 booting on AMD platforms with
PCID support. It doesn't have an upstream counterpart because it patches
the KAISER code which didn't go upstream. It applies fine to both of the
aforementioned kernels - please pick it up.

Thx.
---
From: Borislav Petkov <bp@suse.de>
Date: Thu, 25 Mar 2021 11:02:31 +0100
Subject: [PATCH] x86/tlb: Flush global mappings when KAISER is disabled

Jim Mattson reported that Debian 9 guests using a 4.9-stable kernel
are exploding during alternatives patching:

  kernel BUG at /build/linux-dqnRSc/linux-4.9.228/arch/x86/kernel/alternative.c:709!
  invalid opcode: 0000 [#1] SMP
  Modules linked in:
  CPU: 1 PID: 1 Comm: swapper/0 Not tainted 4.9.0-13-amd64 #1 Debian 4.9.228-1
  Hardware name: Google Google Compute Engine/Google Compute Engine, BIOS Google 01/01/2011
  Call Trace:
   swap_entry_free
   swap_entry_free
   text_poke_bp
   swap_entry_free
   arch_jump_label_transform
   set_debug_rodata
   __jump_label_update
   static_key_slow_inc
   frontswap_register_ops
   init_zswap
   init_frontswap
   do_one_initcall
   set_debug_rodata
   kernel_init_freeable
   rest_init
   kernel_init
   ret_from_fork

triggering the BUG_ON in text_poke() which verifies whether patched
instruction bytes have actually landed at the destination.

Further debugging showed that the TLB flush before that check is
insufficient because there could be global mappings left in the TLB,
leading to a stale mapping getting used.

I say "global mappings" because the hardware configuration is a new one:
machine is an AMD, which means, KAISER/PTI doesn't need to be enabled
there, which also means there's no user/kernel pagetables split and
therefore the TLB can have global mappings.

And the configuration is new one for a second reason: because that AMD
machine supports PCID and INVPCID, which leads the CPU detection code to
set the synthetic X86_FEATURE_INVPCID_SINGLE flag.

Now, __native_flush_tlb_single() does invalidate global mappings when
X86_FEATURE_INVPCID_SINGLE is *not* set and returns.

When X86_FEATURE_INVPCID_SINGLE is set, however, it invalidates the
requested address from both PCIDs in the KAISER-enabled case. But if
KAISER is not enabled and the machine has global mappings in the TLB,
then those global mappings do not get invalidated, which would lead to
the above mismatch from using a stale TLB entry.

So make sure to flush those global mappings in the KAISER disabled case.

Co-debugged by Babu Moger <babu.moger@amd.com>.

Reported-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Borislav Petkov <bp@suse.de>
Acked-by: Hugh Dickins <hughd@google.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Babu Moger <babu.moger@amd.com>
Tested-by: Jim Mattson <jmattson@google.com>
Link: https://lkml.kernel.org/r/CALMp9eRDSW66%2BXvbHVF4ohL7XhThoPoT0BrB0TcS0cgk=dkcBg@mail.gmail.com
---
 arch/x86/include/asm/tlbflush.h | 11 +++++++----
 1 file changed, 7 insertions(+), 4 deletions(-)

```
