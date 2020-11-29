#### [PATCH 1/2] arm64: Make the Meltdown mitigation state available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11938379
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6E23BC8301C
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4202D21D40
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="fINe9zgg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388768AbgK1Vto (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 28 Nov 2020 16:49:44 -0500
Received: from mail.kernel.org ([198.145.29.99]:50808 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732875AbgK1TEe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Nov 2020 14:04:34 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8ED2422409;
        Sat, 28 Nov 2020 12:47:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1606567625;
        bh=lnhjrd1BY+4XT/salWuXAQXDGdluOebgvvtHAouCinc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=fINe9zgg4BEo7DfBbGMcvdXT8bPDtBIBZgP6f6gxVZpUYSoriqEFshlbY+fjTA0A6
         QsBCMpyTQAtpWVlYOyszH/w67Itf4NHxOXc9OoMTYyOJLehFCg7qOxqG98YkGtV5uy
         NgE5A5J2H092MPpM2lp/0URKigLApTzWr8KgVVZc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kizd1-00EHHF-S1; Sat, 28 Nov 2020 12:47:04 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 1/2] arm64: Make the Meltdown mitigation state available
Date: Sat, 28 Nov 2020 12:46:58 +0000
Message-Id: <20201128124659.669578-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201128124659.669578-1-maz@kernel.org>
References: <20201128124659.669578-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Our Meltdown mitigation state isn't exposed outside of cpufeature.c,
contrary to the rest of the Spectre mitigation state. As we are going
to use it in KVM, expose a arm64_get_meltdown_state() helper which
returns the same possible values as arm64_get_spectre_v?_state().

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/spectre.h |  2 ++
 arch/arm64/kernel/cpufeature.c   | 20 +++++++++++++++++---
 2 files changed, 19 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/2] irqchip/gic-v4.1: Reduce the delay time of the poll on the GICR_VPENDBASER.Dirty bit
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 11937809
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3F6ABC64E7D
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 17:59:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0D46922456
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 17:59:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732123AbgK1R7A (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 28 Nov 2020 12:59:00 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:8526 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1733144AbgK1R4j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Nov 2020 12:56:39 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cjtsh1WnPzhj5H;
        Sat, 28 Nov 2020 22:19:20 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.187.74) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.487.0; Sat, 28 Nov 2020 22:19:33 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        "Jason Cooper" <jason@lakedaemon.net>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Eric Auger <eric.auger@redhat.com>,
        Christoffer Dall <christoffer.dall@arm.com>
CC: <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v2 1/2] irqchip/gic-v4.1: Reduce the delay time of the poll on
 the GICR_VPENDBASER.Dirty bit
Date: Sat, 28 Nov 2020 22:18:56 +0800
Message-ID: <20201128141857.983-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20201128141857.983-1-lushenming@huawei.com>
References: <20201128141857.983-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.74]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 10 delay_us of the poll on the GICR_VPENDBASER.Dirty bit is too
high, which might greatly affect the total scheduling latency of a
vCPU in our measurement. So we reduce it to 1 to lessen the impact.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 drivers/irqchip/irq-gic-v3-its.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Reinstate userspace hypercall supportFrom: David Woodhouse <dwmw2@infradead.org>
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11938371
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.2 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_SANE_2 autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AE28FC64E8A
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A97721D40
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="ueo0x5db"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726152AbgK1Vtm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 28 Nov 2020 16:49:42 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33822 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728509AbgK1SA2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Nov 2020 13:00:28 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5C254C02A1A5
        for <kvm@vger.kernel.org>; Sat, 28 Nov 2020 06:21:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:Date:Cc:To:
        From:Subject:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=AeBJc+e8OUEXilt5ZFeyUNpkWH7vDGBtJ9JMBH6p/5U=;
 b=ueo0x5db9XtswDUJrMFxScOiUw
        77V1IECJXVrq0PE2ieDs0nqwT2tExN+cNGJYDX+54v+7A3Zsp5GAQ2DMugmvof7bMyIDvBOuXtXJU
        yXZzHvqxN/9hPxmb2Pq4cArnr22kEAANC07FxejJO7SP1RSbcEmNOQ2XxwMrQhWsiQHT6Z7jO5kpJ
        VCdJqmfleGLqa6/htcUigc/bUrl6GUwIMYt6LF5xrujXKv84wPH+LlRiagKtXI1hpvGA9UI51ySTP
        AVxoiXNn7i5rszrNkEfdktW26EgHlsfN0wCz6DTF85DZR51lRdemBhKfJkmV6ZxVVxzqOL4P8XKu/
        EM+AoJXw==;
Received: from 54-240-197-236.amazon.com ([54.240.197.236]
 helo=freeip.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kj15v-0005WU-Rb; Sat, 28 Nov 2020 14:21:00 +0000
Message-ID: <1bde4a992be29581e559f7a57818e206e11f84f5.camel@infradead.org>
Subject: [PATCH] KVM: x86: Reinstate userspace hypercall support
From: David Woodhouse <dwmw2@infradead.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Date: Sat, 28 Nov 2020 14:20:58 +0000
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

For supporting Xen guests we really want to be able to use vmcall/vmmcall
for hypercalls as Xen itself does. Reinstate the KVM_EXIT_HYPERCALL
support that Anthony ripped out in 2007.

Yes, we *could* make it work with KVM_EXIT_IO if we really had to, but
that makes it guest-visible and makes it distinctly non-trivial to do
live migration from Xen because we'd have to update the hypercall page(s)
(which are at unknown locations) as well as dealing with any guest RIP
which happens to be *in* a hypercall page at the time.

We also actively want to *prevent* the KVM hypercalls from suddenly
becoming available to guests which think they are Xen guests, which
this achieves too.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
Should this test work OK on AMD? I see a separate test which is
explicitly testing VMCALL on AMD, which makes me suspect it's expected
to work as well as VMMCALL?

Do we have the test infrastructure for running 32-bit guests easily?

 Documentation/virt/kvm/api.rst                | 23 +++--
 arch/x86/include/asm/kvm_host.h               |  1 +
 arch/x86/kvm/x86.c                            | 46 +++++++++
 include/uapi/linux/kvm.h                      |  1 +
 tools/include/uapi/linux/kvm.h                | 57 ++++++++++-
 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  1 +
 .../selftests/kvm/x86_64/user_vmcall_test.c   | 94 +++++++++++++++++++
 8 files changed, 214 insertions(+), 10 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_vmcall_test.c

```
