#### [kvm-unit-tests PATCH 1/2] arm64: Add support for configuring the translation granule
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11873659
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF6C8C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:34:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CA08223AC
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:34:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728494AbgKBLey (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 06:34:54 -0500
Received: from foss.arm.com ([217.140.110.172]:58100 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728608AbgKBLeu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 06:34:50 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 52DF31042;
        Mon,  2 Nov 2020 03:34:48 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 507C03F66E;
        Mon,  2 Nov 2020 03:34:47 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH 1/2] arm64: Add support for configuring the
 translation granule
Date: Mon,  2 Nov 2020 11:34:43 +0000
Message-Id: <20201102113444.103536-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201102113444.103536-1-nikos.nikoleris@arm.com>
References: <20201102113444.103536-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make the translation granule configurable for arm64. arm64 supports
page sizes of 4K, 16K and 64K. By default, arm64 is configured with
64K pages. configure has been extended with a new argument:

 --page-shift=(12|14|16)

which allows the user to set the page shift and therefore the page
size for arm64. Using the --page-shift for any other architecture
results an error message.

To allow for smaller page sizes and 42b VA, this change adds support
for 4-level and 3-level page tables. At compile time, we determine how
many levels in the page tables we needed.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 configure                     | 26 +++++++++++++
 lib/arm/asm/page.h            |  4 ++
 lib/arm/asm/pgtable-hwdef.h   |  4 ++
 lib/arm/asm/pgtable.h         |  6 +++
 lib/arm/asm/thread_info.h     |  4 +-
 lib/arm64/asm/page.h          | 25 ++++++++++---
 lib/arm64/asm/pgtable-hwdef.h | 38 +++++++++++++------
 lib/arm64/asm/pgtable.h       | 69 +++++++++++++++++++++++++++++++++--
 lib/arm/mmu.c                 | 26 ++++++++-----
 arm/cstart64.S                | 10 ++++-
 10 files changed, 180 insertions(+), 32 deletions(-)

```
#### [kvm-unit-tests PATCH 2/2] arm: Add support for the DEVICE_nGRE and NORMAL_WT memory types
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11873753
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AFDB9C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B987222B9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728607AbgKBLxR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 06:53:17 -0500
Received: from foss.arm.com ([217.140.110.172]:58366 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728297AbgKBLxQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 06:53:16 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1A69530E;
        Mon,  2 Nov 2020 03:53:16 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 35E0B3F66E;
        Mon,  2 Nov 2020 03:53:15 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH 2/2] arm: Add support for the DEVICE_nGRE and
 NORMAL_WT memory types
Date: Mon,  2 Nov 2020 11:53:11 +0000
Message-Id: <20201102115311.103750-3-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201102115311.103750-1-nikos.nikoleris@arm.com>
References: <20201102115311.103750-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm64/asm/pgtable-hwdef.h | 2 ++
 arm/cstart64.S                | 6 +++++-
 2 files changed, 7 insertions(+), 1 deletion(-)

```
#### [RFC v3 01/12] arm64: Add a helper function to traverse arm64_ftr_regs
##### From: Peng Liang <liangpeng10@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11872915
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB3BAC55179
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 03:37:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EB6C221FC
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 03:37:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727718AbgKBDhM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 1 Nov 2020 22:37:12 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:7394 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727694AbgKBDhM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Nov 2020 22:37:12 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4CPdrj3QvSz6ytt;
        Mon,  2 Nov 2020 11:37:09 +0800 (CST)
Received: from localhost.localdomain (10.175.124.27) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Mon, 2 Nov 2020 11:37:02 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <drjones@redhat.com>, <zhang.zhanghailiang@huawei.com>,
        <xiexiangyou@huawei.com>, Peng Liang <liangpeng10@huawei.com>
Subject: [RFC v3 01/12] arm64: Add a helper function to traverse
 arm64_ftr_regs
Date: Mon, 2 Nov 2020 11:34:11 +0800
Message-ID: <20201102033422.657391-2-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201102033422.657391-1-liangpeng10@huawei.com>
References: <20201102033422.657391-1-liangpeng10@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.124.27]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we want to emulate ID registers, we need to initialize ID registers
firstly.  This commit is to add a helper function to traverse
arm64_ftr_regs so that we can initialize ID registers from
arm64_ftr_regs.

Signed-off-by: zhanghailiang <zhang.zhanghailiang@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/cpufeature.h |  2 ++
 arch/arm64/kernel/cpufeature.c      | 13 +++++++++++++
 2 files changed, 15 insertions(+)

```
#### [PATCH 1/8] KVM: arm64: Move AArch32 exceptions over to AArch64 sysregs
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875069
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BD7E5C2D0A3
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F69422268
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:19 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344579;
	bh=ArWFBoK0fRQku7Ixro39jAGqWAPrMQvy0PpraNIOiA0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=p15XSoZ5rO7o5friUgRBqwUQaW5ZIxnbUJoeanXmIansgsqM/SDsRqgKQ7If1v/Zn
	 rt6rpUyo4uodIf+3WI9aDZN8kmeSG5IEVVbM0rIQbwLcjJXLrWaUD3+VutK7zGchel
	 DG/we8xek0Z+aqqS8PmurpX9zGqQcx0lNYWWHTd4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726518AbgKBTQS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:18 -0500
Received: from mail.kernel.org ([198.145.29.99]:60272 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725791AbgKBTQR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:17 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9C5642225E;
        Mon,  2 Nov 2020 19:16:15 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344575;
        bh=ArWFBoK0fRQku7Ixro39jAGqWAPrMQvy0PpraNIOiA0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=aTalKTQOzsoIcqJTNcdFWelDURIMQRP2hAwYF5ArRJ22GTesagAqw/3Kocidf0mhv
         eLhC745L7k0MGSpIflzdaY3KuAwcoo+9U94/qEug+/Ig5e6G13qwrkxJnnxm8K5vtq
         BwmIkKpNbsDkmdlfFc6IDS26QgppZHZeca+j8rNk=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJN-006nxn-Ls; Mon, 02 Nov 2020 19:16:13 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 1/8] KVM: arm64: Move AArch32 exceptions over to AArch64
 sysregs
Date: Mon,  2 Nov 2020 19:16:02 +0000
Message-Id: <20201102191609.265711-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102191609.265711-1-maz@kernel.org>
References: <20201102191609.265711-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The use of the AArch32-specific accessors have always been a bit
annoying on 64bit, and it is time for a change.

Let's move the AArch32 exception injection over to the AArch64 encoding,
which requires us to split the two halves of FAR_EL1 into DFAR and IFAR.
This enables us to drop the preempt_disable() games on VHE, and to kill
the last user of the vcpu_cp15() macro.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h |  1 -
 arch/arm64/kvm/inject_fault.c     | 62 ++++++++++---------------------
 2 files changed, 20 insertions(+), 43 deletions(-)

```
#### [PATCH v2 01/11] KVM: arm64: Don't adjust PC on SError during SMC trap
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11874469
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44375C4742C
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 16:41:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03C41223B0
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 16:41:08 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604335269;
	bh=LbFIUMvh/XxufxroOMxcM/bchWyuyq7+XF1PJEMLgS8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=ydD2xsdzoZ4/UEc2QOo4OFb8DuZ2vMumo3lSrL8guLaXblL5lFKRuQblOkZoRcz3L
	 d0Zy/QtixutuheM8m6bXhLaRlKIi5iNnVPnswpHe6dAodBdTkPqLKyAzFNKiPUQ8Xw
	 bzTXP/0hsRA/gZIJBZE+4d1Go5X5fZ3qJEhaOrgs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727192AbgKBQlH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 11:41:07 -0500
Received: from mail.kernel.org ([198.145.29.99]:46708 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727181AbgKBQlH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 11:41:07 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5229A222BA;
        Mon,  2 Nov 2020 16:41:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604335266;
        bh=LbFIUMvh/XxufxroOMxcM/bchWyuyq7+XF1PJEMLgS8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=RK3T0X4yVX6/eJyxwqJSid6WzMcZDAf3cmXcoKfJPi6NgeLJym0ciXpl2GqYmzX13
         frNKnTaiQu0EXja4bCZhUFXouIxZYLFGzNE4hzxFfHgRpS8A16fmbD3WV0vp95Kj32
         W9lTB8xqYXH+fIFxQH4BDAkqUSoG2b6/7QNcUVfY=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZctE-006jJf-IK; Mon, 02 Nov 2020 16:41:04 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Quentin Perret <qperret@google.com>,
        David Brazdil <dbrazdil@google.com>, kernel-team@android.com
Subject: [PATCH v2 01/11] KVM: arm64: Don't adjust PC on SError during SMC
 trap
Date: Mon,  2 Nov 2020 16:40:35 +0000
Message-Id: <20201102164045.264512-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102164045.264512-1-maz@kernel.org>
References: <20201102164045.264512-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, mark.rutland@arm.com, qperret@google.com,
 dbrazdil@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On SMC trap, the prefered return address is set to that of the SMC
instruction itself. It is thus wrong to try and roll it back when
an SError occurs while trapping on SMC. It is still necessary on
HVC though, as HVC doesn't cause a trap, and sets ELR to returning
*after* the HVC.

It also became apparent that there is no 16bit encoding for an AArch32
HVC instruction, meaning that the displacement is always 4 bytes,
no matter what the ISA is. Take this opportunity to simplify it.

Acked-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/handle_exit.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH v2 1/3] KVM: selftests: Add aarch64 get-reg-list test
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11875009
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 852DEC2D0A3
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:03:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2880522243
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:03:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G1gSgURU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726423AbgKBTDe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:03:34 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42768 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726189AbgKBTDe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Nov 2020 14:03:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604343809;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tLi0mkmyL37d/Hqs0YLzICtRdg2xi0vohTWYYe1nieE=;
        b=G1gSgURUmaqgCCu2L+NGjWXpUv2XnZmdl3Q/E4EOegbsvLiqaeI/lnuwyncyDrSousv6zq
        6FgL/lCUfZXMyZbWaELL79SkMBFogvLodUojJqSX6UX1/HhH2yt6CwBaBYPxFuswHgFXRC
        YoJYfTCESIWOV5I58yYl17yp2gONBzY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-485-iM2dGjNrNg2KSAvuRfE5Fg-1; Mon, 02 Nov 2020 14:03:13 -0500
X-MC-Unique: iM2dGjNrNg2KSAvuRfE5Fg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 210766D240;
        Mon,  2 Nov 2020 19:03:12 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.222])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DEC665B4D7;
        Mon,  2 Nov 2020 19:03:03 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, Dave.Martin@arm.com,
        peter.maydell@linaro.org, eric.auger@redhat.com
Subject: [PATCH v2 1/3] KVM: selftests: Add aarch64 get-reg-list test
Date: Mon,  2 Nov 2020 20:02:51 +0100
Message-Id: <20201102190253.50575-2-drjones@redhat.com>
In-Reply-To: <20201102190253.50575-1-drjones@redhat.com>
References: <20201102190253.50575-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check for KVM_GET_REG_LIST regressions. The blessed list was
created by running on v4.15 with the --core-reg-fixup option.
The following script was also used in order to annotate system
registers with their names when possible. When new system
registers are added the names can just be added manually using
the same grep.

while read reg; do
	if [[ ! $reg =~ ARM64_SYS_REG ]]; then
		printf "\t$reg\n"
		continue
	fi
	encoding=$(echo "$reg" | sed "s/ARM64_SYS_REG(//;s/),//")
	if ! name=$(grep "$encoding" ../../../../arch/arm64/include/asm/sysreg.h); then
		printf "\t$reg\n"
		continue
	fi
	name=$(echo "$name" | sed "s/.*SYS_//;s/[\t ]*sys_reg($encoding)$//")
	printf "\t$reg\t/* $name */\n"
done < <(aarch64/get-reg-list --core-reg-fixup --list)

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/aarch64/get-reg-list.c      | 665 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  29 +
 5 files changed, 697 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list.c

```
#### [kvm-unit-tests PATCH 1/2] arm: Add mmu_get_pte() to the MMU API
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11873755
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5803AC00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07ED1222B9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 11:53:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728579AbgKBLxQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 06:53:16 -0500
Received: from foss.arm.com ([217.140.110.172]:58358 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728297AbgKBLxP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 06:53:15 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 01E0B31B;
        Mon,  2 Nov 2020 03:53:15 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 011333F66E;
        Mon,  2 Nov 2020 03:53:13 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        Luc Maranget <Luc.Maranget@inria.fr>
Subject: [kvm-unit-tests PATCH 1/2] arm: Add mmu_get_pte() to the MMU API
Date: Mon,  2 Nov 2020 11:53:10 +0000
Message-Id: <20201102115311.103750-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201102115311.103750-1-nikos.nikoleris@arm.com>
References: <20201102115311.103750-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Luc Maranget <Luc.Maranget@inria.fr>

Add the mmu_get_pte() function that allows a test to get a pointer to
the PTE for a valid virtual address. Return NULL if the MMU is off.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu-api.h |  1 +
 lib/arm/mmu.c         | 23 ++++++++++++++---------
 2 files changed, 15 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: VMX: Enable Notify VM exit
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11873035
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02897C00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 06:14:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5ECA22265
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 06:14:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728068AbgKBGOv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 01:14:51 -0500
Received: from mga01.intel.com ([192.55.52.88]:29661 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725208AbgKBGOv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 01:14:51 -0500
IronPort-SDR: 
 73bBoKCeK7UZPLhktv5oNXITlROVlJP755h5iv1wHxmrU6aUvbHDXazAif4aaAN3rR9C41W3sy
 dcEVY9ZUPa7A==
X-IronPort-AV: E=McAfee;i="6000,8403,9792"; a="186669766"
X-IronPort-AV: E=Sophos;i="5.77,444,1596524400";
   d="scan'208";a="186669766"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Nov 2020 22:14:50 -0800
IronPort-SDR: 
 8b703zXJzhYrXVZk+ziuGihKQyo6OX9XG+juqTGPlI8tHT6yrvo9B0TZY63jgx1qHGw5Pv4cpX
 PNKllSpvhqhg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,444,1596524400";
   d="scan'208";a="526576042"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.33])
  by fmsmga006.fm.intel.com with ESMTP; 01 Nov 2020 22:14:47 -0800
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Tao Xu <tao3.xu@intel.com>, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH] KVM: VMX: Enable Notify VM exit
Date: Mon,  2 Nov 2020 14:14:45 +0800
Message-Id: <20201102061445.191638-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are some cases that malicious virtual machines can cause CPU stuck
(event windows don't open up), e.g., infinite loop in microcode when
nested #AC (CVE-2015-5307). No event window obviously means no events,
e.g. NMIs, SMIs, and IRQs will all be blocked, may cause the related
hardware CPU can't be used by host or other VM.

To resolve those cases, it can enable a notify VM exit if no
event window occur in VMX non-root mode for a specified amount of
time (notify window).

Expose a module param for setting notify window, default setting it to
the time as 1/10 of periodic tick, and user can set it to 0 to disable
this feature.

TODO:
1. The appropriate value of notify window.
2. Another patch to disable interception of #DB and #AC when notify
VM-Exiting is enabled.

Co-developed-by: Xiaoyao Li <xiaoyao.li@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/vmx.h         |  7 +++++
 arch/x86/include/asm/vmxfeatures.h |  1 +
 arch/x86/include/uapi/asm/vmx.h    |  4 ++-
 arch/x86/kvm/vmx/capabilities.h    |  6 +++++
 arch/x86/kvm/vmx/vmx.c             | 42 +++++++++++++++++++++++++++++-
 include/uapi/linux/kvm.h           |  2 ++
 6 files changed, 60 insertions(+), 2 deletions(-)

```
#### [PATCH 7/8] KVM: arm64: Drop legacy copro shadow register
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875071
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F02BBC2D0A3
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A338F22268
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344587;
	bh=AtpHV5wJJBOkeD5f6w+jY11UMjEHrUBXFJL1igD+zkI=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=ztmQ8iiGO1efp4tHl8Z2PIVZKhYyBAi5nVpAOx+A0nj88I6iIaJT0XeWK64cSg7er
	 USM3plB4IFGA8XEehevFl/AreKpzNBIB1xXJTHNC/hNirJurCRK3qsyr1HS2HVbwuW
	 JZPoFc5VuqJztPh9i7HbiMoXNNkB+H1UJ+uKYeuc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726645AbgKBTQ0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:26 -0500
Received: from mail.kernel.org ([198.145.29.99]:60436 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726470AbgKBTQS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:18 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id EB1E3223BD;
        Mon,  2 Nov 2020 19:16:17 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344578;
        bh=AtpHV5wJJBOkeD5f6w+jY11UMjEHrUBXFJL1igD+zkI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=0pvE1sKeW1L+qzNsQK/0YHwWk7u1rbm8sZJk/1krRYY3zdvKnfxWVA/QMkQhdxB4h
         0+BsdUHyad2Fb/wYGDnRPVDXBmWftY0olFVos4pYFF8Ltajkk9yoGCUi69xuEQMror
         /N649VM3KaLy3tw7GEhwmcY+ETc2XARkooFuuNew=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJQ-006nxn-5p; Mon, 02 Nov 2020 19:16:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 7/8] KVM: arm64: Drop legacy copro shadow register
Date: Mon,  2 Nov 2020 19:16:08 +0000
Message-Id: <20201102191609.265711-8-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102191609.265711-1-maz@kernel.org>
References: <20201102191609.265711-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Finally remove one of the biggest 32bit legacy: the copro shadow
mapping. We won't missit.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 47 +------------------------------
 1 file changed, 1 insertion(+), 46 deletions(-)

```
#### [PATCH 2/8] KVM: arm64: Add AArch32 mapping annotation
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875075
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8429BC00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21684223C6
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344578;
	bh=/vSypgHV3ppGf3VM+3b9Uw3XIcZP+Wgme9h2xxf4rZk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=BiR01uD8y9t+XX7KMpHg3JI4GP9flgJsBlh1QD5xZtGfw7ahc0Plu2t9zF64HSULN
	 RLjZlr3bJMsyg8mNJhvINpHCncMCczfMog/aWR1N0CvCWSfx5bNyCSiQ1cOCGVVvp2
	 U4k4gWWVOHT37H9Ovy6XMaOKezp2mpB3glkW+Gbg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726236AbgKBTQR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:17 -0500
Received: from mail.kernel.org ([198.145.29.99]:60292 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725809AbgKBTQQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:16 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id D25C022268;
        Mon,  2 Nov 2020 19:16:15 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344576;
        bh=/vSypgHV3ppGf3VM+3b9Uw3XIcZP+Wgme9h2xxf4rZk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Jeit1NMHhX4xxwzPds+AWo/WCs7knZm/wlcZzqEKKmDomnYeQkAHx89yAyZOvJgOh
         A9QTftl8eyR8VgstIFAL7SFsnPGmQ0Z0R1Oz8Dpiy2/T1LWSuzSCX8JzumwiaUuAmr
         roc9B0thDHMJ0rj+myJXbYJKk1+F1RUBByRuP1lI=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJO-006nxn-2w; Mon, 02 Nov 2020 19:16:14 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 2/8] KVM: arm64: Add AArch32 mapping annotation
Date: Mon,  2 Nov 2020 19:16:03 +0000
Message-Id: <20201102191609.265711-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102191609.265711-1-maz@kernel.org>
References: <20201102191609.265711-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to deal with the few AArch32 system registers that map to
only a particular half of their AArch64 counterpart (such as DFAR
and IFAR being colocated in FAR_EL1), let's add an optional annotation
to the sysreg descriptor structure, indicating whether a register
maps to the upper or lower 32bits of a register.

Nothing is using these annotation yet.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.h | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH 8/8] KVM: arm64: Drop kvm_coproc.h
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875073
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DDEDC4742C
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCEAE22275
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344588;
	bh=C4GctCoQeP0UtgS9icsWKNG04r7fIKZ7Rd5moRwXfkI=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=G1ihSX8vxa3yQp6ms+qiV/ErGBS12m60epouhX/qpzk7NzoKqLPG3vD5Gdg+M29rp
	 YOrvnYamyeUsTEDy93D06HdwK24XDNbfzqFq5zEnZffMVAeaPi+VdIMUndIybAIgdW
	 PveXZBzoaLWNTFVqcZrOUiV/DD4fHj0hpCa2NqXY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726625AbgKBTQ0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:26 -0500
Received: from mail.kernel.org ([198.145.29.99]:60364 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725824AbgKBTQT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:19 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 51900223FB;
        Mon,  2 Nov 2020 19:16:18 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344578;
        bh=C4GctCoQeP0UtgS9icsWKNG04r7fIKZ7Rd5moRwXfkI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=07vQGTmM/Yfvg+MJtrk/bz29xMyZBYg4qoMIU60b2Mg1QH4V94y7gVWCqjLu8bJhe
         zz2p0wfLXUdkwzo5ZMg0TFUzAo7nDnE6Gm9b+MnErFbfCAjoETYVhlO9Dy7e/AnSAW
         d/QYpZ/jiinJ3d4JEfLlWU3V9ZSaqilJ4gRFNECQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJQ-006nxn-Il; Mon, 02 Nov 2020 19:16:16 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 8/8] KVM: arm64: Drop kvm_coproc.h
Date: Mon,  2 Nov 2020 19:16:09 +0000
Message-Id: <20201102191609.265711-9-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102191609.265711-1-maz@kernel.org>
References: <20201102191609.265711-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_coproc.h used to serve as a compatibility layer for the files
shared between the 32 and 64 bit ports.

Another one bites the dust...

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_coproc.h | 38 -----------------------------
 arch/arm64/include/asm/kvm_host.h   | 17 +++++++++++++
 arch/arm64/kvm/arm.c                |  3 +--
 arch/arm64/kvm/guest.c              |  1 -
 arch/arm64/kvm/handle_exit.c        |  1 -
 arch/arm64/kvm/reset.c              |  1 -
 arch/arm64/kvm/sys_regs.c           |  1 -
 7 files changed, 18 insertions(+), 44 deletions(-)
 delete mode 100644 arch/arm64/include/asm/kvm_coproc.h

diff --git a/arch/arm64/include/asm/kvm_coproc.h b/arch/arm64/include/asm/kvm_coproc.h
```
#### [PATCH 3/8] KVM: arm64: Map AArch32 cp15 register to AArch64 sysregs
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11875077
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 868E8C55179
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2687B22268
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 19:16:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604344590;
	bh=9LeLkrQsFwr/CWyCUnFcQ5bVDi76kiR9hv/l2nTZdOY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=hlfGWgAwuXn4mNj2+dB/IQKxUfV5zgJ8/7e2jurPYYHlo5hklU9zaGixbmRmcN2/M
	 uDcIcR965Xu4s+Xvh50t7Y0avo2y30Ibt2Jm6m1snIASPtKzIjQZU9eysYhY0QxB83
	 c5TmIK0PrfXjd0dSzGZw6asLfX4nlRcGk2276KD0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726473AbgKBTQS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 14:16:18 -0500
Received: from mail.kernel.org ([198.145.29.99]:60330 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725824AbgKBTQR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 14:16:17 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 445F222275;
        Mon,  2 Nov 2020 19:16:16 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604344576;
        bh=9LeLkrQsFwr/CWyCUnFcQ5bVDi76kiR9hv/l2nTZdOY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=hwRF+r1Z2QVa5gzOhydwm0zlEsfrEm5NWiSCpUdtvfj4pZsu7pF0/icDgjwhd/gGZ
         fwPm8MnYduvE2MVLvR4vedTHC0LuRkqYVaVV+cWrCakvIWC9KQqdjDFiGzA2Na0zgS
         Vm/vM7dlAKeXKitPQeWp7DQYqsuLHHr9zv+ZqqNo=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZfJO-006nxn-Fj; Mon, 02 Nov 2020 19:16:14 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 3/8] KVM: arm64: Map AArch32 cp15 register to AArch64 sysregs
Date: Mon,  2 Nov 2020 19:16:04 +0000
Message-Id: <20201102191609.265711-4-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201102191609.265711-1-maz@kernel.org>
References: <20201102191609.265711-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move all the cp15 registers over to their AArch64 counterpart.
This requires the annotation of a few of them (such as the usual
DFAR/IFAR vs FAR_EL1), and a new helper that generates mask/shift
pairs for the various configurations.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 107 +++++++++++++++++++++-----------------
 1 file changed, 58 insertions(+), 49 deletions(-)

```
#### [PATCH v2 1/8] mm: slab: provide krealloc_array()
##### From: Bartosz Golaszewski <brgl@bgdev.pl>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bartosz Golaszewski <brgl@bgdev.pl>
X-Patchwork-Id: 11874219
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0B531C388F2
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 15:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BAC3522226
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 15:21:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=bgdev-pl.20150623.gappssmtp.com
 header.i=@bgdev-pl.20150623.gappssmtp.com header.b="hf6tvqnc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726523AbgKBPUr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 10:20:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56696 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726491AbgKBPUq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 10:20:46 -0500
Received: from mail-wm1-x343.google.com (mail-wm1-x343.google.com
 [IPv6:2a00:1450:4864:20::343])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BD021C061A48
        for <kvm@vger.kernel.org>; Mon,  2 Nov 2020 07:20:44 -0800 (PST)
Received: by mail-wm1-x343.google.com with SMTP id e2so9869796wme.1
        for <kvm@vger.kernel.org>; Mon, 02 Nov 2020 07:20:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bgdev-pl.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=//ohTnlCNdzVCN7+X/oV4S8f/hxX7VdQ1OV3L6uwfhQ=;
        b=hf6tvqncwp3fkOIckHP3XNhZspBIs+DJCE72k4fKwWNNEV8tVYATPrk61RVN2LLtoy
         wyuT8kZJhciWHJYnIywhLp+tPKS38UhRZoDdJRNvydyfnF4jPWOOLNFaCIa5fWpPbqiE
         CPEcfMQCT8yeENUO+TRhPv8NZwnqBa/5qBgOFPacWV7BhHFuUJ5ASnX9vmHxuqU/2Ygy
         yl+QCczTs9fSAAWT/g0PiS+PxK7jWNW2R3D8R0j5FcPe+c2M0+55tW8i3tKhxnOrTffM
         d3zN4lSBg/UxZjb51Fwl4foaEs43EhxOe1ue2FxQvf65j62JS7V+E/ior/FALPI70AY8
         3BnQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=//ohTnlCNdzVCN7+X/oV4S8f/hxX7VdQ1OV3L6uwfhQ=;
        b=kCw5AwzAdtSxxsp3Ve24r61gF8jnOJfNSNJhb9t2sENg1/06nxMONLrhYDlu3nNGaP
         mKxoBf8i0QuGtv34zBK115WFITdjUjq/kxbkTVz99owjLRMcH7qYjCz7EaVZWN9Z2Ni+
         GHeX+TuwM1ICfETtTyAGPG2PWd/xloLPHSX2g/6hwufXIBPlV/kjn8emdc2hp9g/t4Ad
         Pr/jma/iwxVPgO0DgWViU5vt1VdbtgGJmuF8LT28/2aUpTY/Y1VxE962TkMb9B9879V8
         ZVqJmYl6frgCrONRHNd0YAD/+k4o7dMgL4rR06Vdz2xVnokH8v7wWqLFxDNaBlKjEUCr
         8veA==
X-Gm-Message-State: AOAM5319UoZrV1K9c2SGKXtgPACHLNfdDDzUlaG6yALV5mU2uiTa/VY3
        vNjQZp+fJJVbEvoPz4cA1559Bw==
X-Google-Smtp-Source: 
 ABdhPJxGlAsjxjuqTsCnImH4txzUDEh+1CeV9f1Ji5E5b7hmF0/rUwH1lj/uHarBz/RRB7bv+TJwGA==
X-Received: by 2002:a7b:cf25:: with SMTP id m5mr18034156wmg.124.1604330443460;
        Mon, 02 Nov 2020 07:20:43 -0800 (PST)
Received: from debian-brgl.home (amarseille-656-1-4-167.w90-8.abo.wanadoo.fr.
 [90.8.158.167])
        by smtp.gmail.com with ESMTPSA id
 b18sm15138014wmj.41.2020.11.02.07.20.41
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 02 Nov 2020 07:20:42 -0800 (PST)
From: Bartosz Golaszewski <brgl@bgdev.pl>
To: Andy Shevchenko <andriy.shevchenko@linux.intel.com>,
 Sumit Semwal <sumit.semwal@linaro.org>,
 Gustavo Padovan <gustavo@padovan.org>,
 =?utf-8?q?Christian_K=C3=B6nig?= <christian.koenig@amd.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>, Borislav Petkov <bp@alien8.de>,
 Tony Luck <tony.luck@intel.com>, James Morse <james.morse@arm.com>,
 Robert Richter <rric@kernel.org>,
 Maarten Lankhorst <maarten.lankhorst@linux.intel.com>,
 Maxime Ripard <mripard@kernel.org>, Thomas Zimmermann <tzimmermann@suse.de>,
 David Airlie <airlied@linux.ie>, Daniel Vetter <daniel@ffwll.ch>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 Linus Walleij <linus.walleij@linaro.org>,
 "Michael S . Tsirkin" <mst@redhat.com>, Jason Wang <jasowang@redhat.com>,
 Christoph Lameter <cl@linux.com>, Pekka Enberg <penberg@kernel.org>,
 David Rientjes <rientjes@google.com>, Joonsoo Kim <iamjoonsoo.kim@lge.com>,
 Andrew Morton <akpm@linux-foundation.org>, Jaroslav Kysela <perex@perex.cz>,
 Takashi Iwai <tiwai@suse.com>
Cc: linux-media@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-gpio@vger.kernel.org,
        kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-mm@kvack.org,
        alsa-devel@alsa-project.org,
        Bartosz Golaszewski <bgolaszewski@baylibre.com>,
        Vlastimil Babka <vbabka@suse.cz>
Subject: [PATCH v2 1/8] mm: slab: provide krealloc_array()
Date: Mon,  2 Nov 2020 16:20:30 +0100
Message-Id: <20201102152037.963-2-brgl@bgdev.pl>
X-Mailer: git-send-email 2.29.1
In-Reply-To: <20201102152037.963-1-brgl@bgdev.pl>
References: <20201102152037.963-1-brgl@bgdev.pl>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bartosz Golaszewski <bgolaszewski@baylibre.com>

When allocating an array of elements, users should check for
multiplication overflow or preferably use one of the provided helpers
like: kmalloc_array().

There's no krealloc_array() counterpart but there are many users who use
regular krealloc() to reallocate arrays. Let's provide an actual
krealloc_array() implementation.

While at it: add some documentation regarding krealloc.

Signed-off-by: Bartosz Golaszewski <bgolaszewski@baylibre.com>
Acked-by: Vlastimil Babka <vbabka@suse.cz>
---
 Documentation/core-api/memory-allocation.rst |  4 ++++
 include/linux/slab.h                         | 18 ++++++++++++++++++
 2 files changed, 22 insertions(+)

```
#### [PATCH v2] KVM: selftests: Add get featured msrs test case
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11874883
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D72CC00A89
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 18:28:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 301E822245
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 18:28:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gqjUNsFD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725882AbgKBS2k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 13:28:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:47814 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725805AbgKBS2j (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 2 Nov 2020 13:28:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604341718;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=9YpQmMFcKiBaEPkaIebjDurDXYdtTD2oSKBxgB9b1i0=;
        b=gqjUNsFDvAFWMDP9+hMgNmw5sIhhMdgIQ3sSyzH1v61Tq01BZmyOiyOWPPeULQjFnUAT29
        aMpWOsWgOLlbK8Nolw2VKLJuT0hliZjOHW6gZZVEhoLVFJ33TkIvOS6UsdWykCV4Tzm6lE
        Vn/6bn2OKriP7LtBKo6LRK2jgd5lFvw=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-1-I2owJLAKP0GPDzrz9uvRiQ-1; Mon, 02 Nov 2020 13:28:36 -0500
X-MC-Unique: I2owJLAKP0GPDzrz9uvRiQ-1
Received: by mail-qt1-f197.google.com with SMTP id i15so8535983qti.7
        for <kvm@vger.kernel.org>; Mon, 02 Nov 2020 10:28:36 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=9YpQmMFcKiBaEPkaIebjDurDXYdtTD2oSKBxgB9b1i0=;
        b=dSQty4x1blZTWLv5jGD9uJHjP6YBKLYaISBfDfATFCroN/9wm65V/0P02AF3H0zdG/
         UfDvuzzFtf86F/2q3gmoOZtq+/Vc0x0c8ERHSXD6J/2YBMiECtJMyA2fqwCjaX3e+Vqf
         UYk3TbYkpAlsftmKApZjj4xnZ6GX3beG08ZKl/PknA0pVAdqf3BVRxwYSCuwNXjTFy3y
         mX/pMdWGUHdrAyDJBIi1mmp7SOerN4oZ0Y835IzALc4ewIQbdO+AbkD5sxOSclGPq9x4
         +vgEJlhJNaCI2f+LLi0nX7xAjxyI+HGuXZTLd5edW9s0CGWgkuLFfL7vHoDQrEC/xWfn
         3kOw==
X-Gm-Message-State: AOAM532JA1WAXqKVCjJy7DdLO3PbE02I2vZMidzBCYvGUy4EnUe9oxjv
        jmnG3BOECbHZR1J/V3sr2LBvaYwZCW0MIY2ruV3k2RiguPNGauG7D2fFk+u6/zHSxqB6DJc2N5F
        CZuk32qT6svLA
X-Received: by 2002:a0c:9004:: with SMTP id o4mr23573397qvo.17.1604341715647;
        Mon, 02 Nov 2020 10:28:35 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJx9bRiuM9PVcEQYq1Cr0KOflbD/zGBnxCe9k1OD7WGCmbl7jWVYzc6pAAHo4SsxfUxMRmUNWQ==
X-Received: by 2002:a0c:9004:: with SMTP id o4mr23573371qvo.17.1604341715392;
        Mon, 02 Nov 2020 10:28:35 -0800 (PST)
Received: from xz-x1.redhat.com
 (bras-vprn-toroon474qw-lp130-20-174-93-89-196.dsl.bell.ca. [174.93.89.196])
        by smtp.gmail.com with ESMTPSA id
 p13sm8431476qkj.58.2020.11.02.10.28.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 02 Nov 2020 10:28:34 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v2] KVM: selftests: Add get featured msrs test case
Date: Mon,  2 Nov 2020 13:28:33 -0500
Message-Id: <20201102182833.20382-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Try to fetch any supported featured msr.  Currently it won't fail, so at least
we can check against valid ones (which should be >0).

This reproduces the issue [1] too by trying to fetch one invalid msr there.

[1] https://bugzilla.kernel.org/show_bug.cgi?id=209845

Signed-off-by: Peter Xu <peterx@redhat.com>
---
v2:
- rename kvm_vm_get_feature_msrs to be prefixed with "_" [Vitaly, Drew]
- drop the fix patch since queued with a better version
---
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 14 +++++
 .../testing/selftests/kvm/x86_64/state_test.c | 58 +++++++++++++++++++
 3 files changed, 75 insertions(+)

```
#### [PATCH v2] nitro_enclaves: Fixup type and simplify logic of the poll mask setup
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Paraschiv, Andra-Irina" <andraprs@amazon.com>
X-Patchwork-Id: 11874705
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D487FC388F9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 17:36:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BEE2208A9
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 17:36:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="X694F9Aq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727842AbgKBRgq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 12:36:46 -0500
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:5473 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727395AbgKBRgq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 12:36:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1604338605; x=1635874605;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=63PIJXKLFwrFkRjowWo20b8DPKycpZ23Q/BMc+ghSfk=;
  b=X694F9AqmVjeRErGig164uYjTV3JWrVduqTWXdEHKtiKOBesHF4yQ/pF
   fsMLPkHmNUHi/VViVzhoWHM5nnAXQ/M+q36ZknxvYvL/vxClYEmuPj7pX
   5V5xZ82koqslXRVCxC/6h2/GEk32K9kGoSFWX5kOPCakSwiiteZCUdKJH
   c=;
X-IronPort-AV: E=Sophos;i="5.77,445,1596499200";
   d="scan'208";a="62248451"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-out-4101.iad4.amazon.com with ESMTP;
 02 Nov 2020 17:36:38 +0000
Received: from EX13D16EUB003.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-7d76a15f.us-east-1.amazon.com (Postfix) with
 ESMTPS id 0F334A21C2;
        Mon,  2 Nov 2020 17:36:36 +0000 (UTC)
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.160.229) by
 EX13D16EUB003.ant.amazon.com (10.43.166.99) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 2 Nov 2020 17:36:27 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Karen Noel <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v2] nitro_enclaves: Fixup type and simplify logic of the poll
 mask setup
Date: Mon, 2 Nov 2020 19:36:22 +0200
Message-ID: <20201102173622.32169-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.160.229]
X-ClientProxiedBy: EX13D34UWC002.ant.amazon.com (10.43.162.137) To
 EX13D16EUB003.ant.amazon.com (10.43.166.99)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update the assigned value of the poll result to be EPOLLHUP instead of
POLLHUP to match the __poll_t type.

While at it, simplify the logic of setting the mask result of the poll
function.

Changelog

v1 -> v2

* Simplify the mask setting logic from the poll function.

Signed-off-by: Andra Paraschiv <andraprs@amazon.com>
Reported-by: kernel test robot <lkp@intel.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 drivers/virt/nitro_enclaves/ne_misc_dev.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH v3] vfio/pci: Bypass IGD init in case of -ENODEV
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 11873353
Return-Path: <SRS0=3TlJ=EI=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4AD7C388F2
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 10:06:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 216E62225E
	for <kvm@archiver.kernel.org>; Mon,  2 Nov 2020 10:06:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728226AbgKBKG3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 2 Nov 2020 05:06:29 -0500
Received: from mga01.intel.com ([192.55.52.88]:47414 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728004AbgKBKG3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Nov 2020 05:06:29 -0500
IronPort-SDR: 
 HE8E9QULEDf2ch5+Wsg7z+OgUV1LESyi9krEynIAc1XAEEpHzWWRvUcFs+1RvV1tJGNVuFFu4m
 KQperzu9iWJA==
X-IronPort-AV: E=McAfee;i="6000,8403,9792"; a="186692421"
X-IronPort-AV: E=Sophos;i="5.77,444,1596524400";
   d="scan'208";a="186692421"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Nov 2020 02:06:28 -0800
IronPort-SDR: 
 dOcdvCG/tii0EzWUK+yCLhpjz/Z99X5uQxcVBlpB+z/PyrSQ+5MNTAlzS3z2R9arPLoXhtVH3D
 /RFj2QOzDdTA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,444,1596524400";
   d="scan'208";a="336121710"
Received: from cfl-host.sh.intel.com ([10.239.158.142])
  by orsmga002.jf.intel.com with ESMTP; 02 Nov 2020 02:06:26 -0800
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Xiong Zhang <xiong.y.zhang@intel.com>,
        Hang Yuan <hang.yuan@linux.intel.com>,
        Stuart Summers <stuart.summers@intel.com>
Subject: [PATCH v3] vfio/pci: Bypass IGD init in case of -ENODEV
Date: Tue,  3 Nov 2020 02:01:20 +0800
Message-Id: <20201102180120.25319-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
In-Reply-To: <20200929161038.15465-1-fred.gao@intel.com>
References: <20200929161038.15465-1-fred.gao@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bypass the IGD initialization when -ENODEV returns,
that should be the case if opregion is not available for IGD
or within discrete graphics device's option ROM,
or host/lpc bridge is not found.

Then use of -ENODEV here means no special device resources found
which needs special care for VFIO, but we still allow other normal
device resource access.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: Xiong Zhang <xiong.y.zhang@intel.com>
Cc: Hang Yuan <hang.yuan@linux.intel.com>
Cc: Stuart Summers <stuart.summers@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
