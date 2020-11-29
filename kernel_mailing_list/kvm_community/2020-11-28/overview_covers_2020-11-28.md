

#### [PATCH 0/2] KVM: arm64: Expose CSV3 to guests on running on
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Sat Nov 28 12:46:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11938375
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0093AC83014
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C37B921D40
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="dtsEoM1j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732670AbgK1Vtn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 28 Nov 2020 16:49:43 -0500
Received: from mail.kernel.org ([198.145.29.99]:48924 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732199AbgK1S7c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Nov 2020 13:59:32 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 79547223C7;
        Sat, 28 Nov 2020 12:47:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1606567625;
        bh=fnB3UrwreWz3sJGIlA6kos60u0AVN2W7lWnz1F1QPas=;
        h=From:To:Cc:Subject:Date:From;
        b=dtsEoM1jAO3kNJRwc8dSFjNYZHDw2+n4lN1ZUh1mKzpYKmzJ98hgLtg0BeVKBIEte
         2IAbF4XwG42xL1aT9mzmhMmoR4KS3Ww9FcrI0HAt3LS1veAIhX0v2xHiCpv2E1BC3b
         wUMtrY5JzhuMPVM57z4wNp6naLXdolpc6ZmP57K4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kizd1-00EHHF-CD; Sat, 28 Nov 2020 12:47:03 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 0/2] KVM: arm64: Expose CSV3 to guests on running on
 Meltdown-safe HW
Date: Sat, 28 Nov 2020 12:46:57 +0000
Message-Id: <20201128124659.669578-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
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

Will recently pointed out that when running on big-little systems that
are known not to be vulnerable to Metldown, guests are not presented
with the CSV3 property if the physical HW include a core that doesn't
have CSV3, despite being known to be safe (it is on the kpti_safe_list).

Since this is valuable information that can be cheaply given to the
guest, let's just do that. The scheme is the same as what we do for
CSV2, allowing userspace to change the default setting if this doesn't
advertise a safer setting than what the kernel thinks it is.

Marc Zyngier (2):
  arm64: Make the Meltdown mitigation state available
  KVM: arm64: Advertise ID_AA64PFR0_EL1.CSV3=1 if the CPUs are
    Meltdown-safe

 arch/arm64/include/asm/kvm_host.h |  1 +
 arch/arm64/include/asm/spectre.h  |  2 ++
 arch/arm64/kernel/cpufeature.c    | 20 +++++++++++++++++---
 arch/arm64/kvm/arm.c              |  6 ++++--
 arch/arm64/kvm/sys_regs.c         | 15 ++++++++++++---
 5 files changed, 36 insertions(+), 8 deletions(-)
```
#### [PATCH v2 0/2] KVM: arm64: Optimize the wait for the completion of
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Sat Nov 28 14:18:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 11938381
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0B2AAC8301F
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D553822240
	for <kvm@archiver.kernel.org>; Sat, 28 Nov 2020 22:19:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388622AbgK1Vtm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 28 Nov 2020 16:49:42 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9066 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732698AbgK1Rzn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Nov 2020 12:55:43 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4CjtsL68GZzLwH9;
        Sat, 28 Nov 2020 22:19:02 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.187.74) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.487.0; Sat, 28 Nov 2020 22:19:24 +0800
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
Subject: [PATCH v2 0/2] KVM: arm64: Optimize the wait for the completion of
 the VPT analysis
Date: Sat, 28 Nov 2020 22:18:55 +0800
Message-ID: <20201128141857.983-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.74]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right after a vPE is made resident, the code starts polling the
GICR_VPENDBASER.Dirty bit until it becomes 0, where the delay_us
is set to 10. But in our measurement, it takes only hundreds of
nanoseconds, or 1~2 microseconds, to finish parsing the VPT in most
cases. What's more, we found that the MMIO delay on GICv4.1 system
(HiSilicon) is about 10 times higher than that on GICv4.0 system in
kvm-unit-tests (the specific data is as follows).

                        |   GICv4.1 emulator   |  GICv4.0 emulator
mmio_read_user (ns)     |        12811         |        1598

After analysis, this is mainly caused by the 10 delay_us, so it might
really hurt performance.

To avoid this, we can set the delay_us to 1, which is more appropriate
in this situation and universal. Besides, we can delay the execution
of the polling, giving the GIC a chance to work in parallel with the CPU
on the entry path.

Shenming Lu (2):
  irqchip/gic-v4.1: Reduce the delay time of the poll on the
    GICR_VPENDBASER.Dirty bit
  KVM: arm64: Delay the execution of the polling on the
    GICR_VPENDBASER.Dirty bit

 arch/arm64/kvm/vgic/vgic-v4.c      | 16 ++++++++++++++++
 arch/arm64/kvm/vgic/vgic.c         |  3 +++
 drivers/irqchip/irq-gic-v3-its.c   | 18 +++++++++++++-----
 drivers/irqchip/irq-gic-v4.c       | 11 +++++++++++
 include/kvm/arm_vgic.h             |  3 +++
 include/linux/irqchip/arm-gic-v4.h |  4 ++++
 6 files changed, 50 insertions(+), 5 deletions(-)
```
