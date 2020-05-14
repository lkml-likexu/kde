#### [PATCH Kernel v19 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11547217
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE0F7739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 20:38:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D768520675
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 20:38:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="GRUnDYKy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728139AbgEMUiA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 16:38:00 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:15831 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728109AbgEMUiA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 16:38:00 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebc5a1e0001>; Wed, 13 May 2020 13:35:42 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 13 May 2020 13:37:59 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 13 May 2020 13:37:59 -0700
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 13 May
 2020 20:37:59 +0000
Received: from kwankhede-dev.nvidia.com (172.20.13.39) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 13 May 2020 20:37:52 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v19 1/8] vfio: UAPI for migration interface for device
 state
Date: Thu, 14 May 2020 01:34:32 +0530
Message-ID: <1589400279-28522-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589400279-28522-1-git-send-email-kwankhede@nvidia.com>
References: <1589400279-28522-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589402143; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=GRUnDYKyarrNBI3Cu+bvrjmsJjiPwNO0HDGapiUC/oZcIG8K7UHsCrapqHb1bWCdq
         mwl4hinRMXS/i3PeFkQ0lcWK3Up3KRKOwDUaHHJLV9skN23u81t9DxgbkesNJ1Rya6
         2ozGWhchWSUOx4yesY3JdbG08p5tm7IWdkkW54HE41uDtIw13khEJiHtkbzzvRuZAQ
         3OSo1BaKOQjJgJxjBtMZQOuQeT6gf8ITNtNmFsuL2B6ynlQS6B7NS47/1JN9fEnt9b
         L12g3/Rm6xV+y1cGJA9HchVo+RmNJJ8bieVk/h7+zRLXDf2SYt5NfMaXHFgjcikaSI
         bFFiS11vTjijQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH] KVM: arm64: Move virt/kvm/arm to arch/arm64
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11545723
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B293F81
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 10:40:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 852F5206D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 10:40:50 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1589366450;
	bh=xmNqrvhFEg/PA/9PFSmpiwzUyItVTgti4dfYA8Tv02c=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=uWdwDApNjEgo3MUdZn3yHRRoIvzNHeLQXeFb+VfXm7Th7eJtMPxtm/LQqa144lz0i
	 I8XVwx+fl+hjvzOgf/cN1mHzjWnQcYt8WdAUjnhx4Yfu0OgdeO9kjv22fcieAb6xi+
	 oslEFitWJpojKsVvmAFFQ4Q+J/PfR+qmKySwqGz0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730671AbgEMKkt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 06:40:49 -0400
Received: from mail.kernel.org ([198.145.29.99]:57496 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727918AbgEMKkt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 06:40:49 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id AD90820673;
        Wed, 13 May 2020 10:40:47 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1589366448;
        bh=xmNqrvhFEg/PA/9PFSmpiwzUyItVTgti4dfYA8Tv02c=;
        h=From:To:Cc:Subject:Date:From;
        b=QVO9ot1V6ovx2DoUc+MdkrYpRdKQJeenV+4ZXgWMKt6qx6S/iK8/7ZLomaunJlait
         SQzrpbORHnnx48rg+Mt4A8gIGz1TgaP/L9Xecfas9o9To0V9STO6n7SoLsEgwOxh/L
         xahDiqDPUC2Zswi86pjmKTmO5Z8pBoO2wwEa/FpM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jYoof-00BwW7-Gq; Wed, 13 May 2020 11:40:45 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>
Subject: [PATCH] KVM: arm64: Move virt/kvm/arm to arch/arm64
Date: Wed, 13 May 2020 11:40:34 +0100
Message-Id: <20200513104034.74741-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that the 32bit KVM/arm host is a distant memory, let's move the
whole of the KVM/arm64 code into the arm64 tree.

As they said in the song: Welcome Home (Sanitarium).

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
---
 MAINTAINERS                                   |   1 -
 arch/arm64/kvm/Makefile                       |  44 ++--
 {virt/kvm/arm => arch/arm64/kvm}/aarch32.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/arm.c        |   2 +-
 arch/arm64/kvm/handle_exit.c                  |   2 +-
 arch/arm64/kvm/hyp/Makefile                   |   9 +-
 .../kvm/arm => arch/arm64/kvm}/hyp/aarch32.c  |   0
 .../kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c |   0
 .../arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c   |   4 -
 {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/mmio.c       |   0
 {virt/kvm/arm => arch/arm64/kvm}/mmu.c        |   0
 {virt/kvm/arm => arch/arm64/kvm}/perf.c       |   0
 .../arm/pmu.c => arch/arm64/kvm/pmu-emul.c    |   0
 {virt/kvm/arm => arch/arm64/kvm}/psci.c       |   0
 {virt/kvm/arm => arch/arm64/kvm}/pvtime.c     |   0
 arch/arm64/kvm/trace.h                        | 216 +-----------------
 .../arm/trace.h => arch/arm64/kvm/trace_arm.h |  11 +-
 arch/arm64/kvm/trace_handle_exit.h            | 215 +++++++++++++++++
 arch/arm64/kvm/vgic-sys-reg-v3.c              |   2 +-
 {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h |   2 +-
 .../arm => arch/arm64/kvm}/vgic/vgic-debug.c  |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-init.c   |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-irqfd.c  |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-its.c    |   0
 .../arm64/kvm}/vgic/vgic-kvm-device.c         |   0
 .../arm64/kvm}/vgic/vgic-mmio-v2.c            |   0
 .../arm64/kvm}/vgic/vgic-mmio-v3.c            |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-mmio.c   |   0
 .../arm => arch/arm64/kvm}/vgic/vgic-mmio.h   |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c |   0
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c |   2 -
 .../kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c  |   0
 {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h  |   0
 36 files changed, 253 insertions(+), 257 deletions(-)
 rename {virt/kvm/arm => arch/arm64/kvm}/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arch_timer.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/arm.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/aarch32.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/timer-sr.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hyp/vgic-v3-sr.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/hypercalls.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmio.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/mmu.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/perf.c (100%)
 rename virt/kvm/arm/pmu.c => arch/arm64/kvm/pmu-emul.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/psci.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/pvtime.c (100%)
 rename virt/kvm/arm/trace.h => arch/arm64/kvm/trace_arm.h (97%)
 create mode 100644 arch/arm64/kvm/trace_handle_exit.h
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/trace.h (93%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-debug.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-init.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-irqfd.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-its.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-kvm-device.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v2.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio-v3.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-mmio.h (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v2.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v3.c (99%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic-v4.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.c (100%)
 rename {virt/kvm/arm => arch/arm64/kvm}/vgic/vgic.h (100%)

```
#### [PATCH] KVM: arm64: Simplify __kvm_timer_set_cntvoff implementation
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11545933
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23343912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 12:15:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0ABCC23126
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 12:15:45 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1589372145;
	bh=OFXMCfgg4QqvOju+IW8sguzu0zPnRXnwQP6ptWcD06o=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=JCzE5tXmGD9/DaB6awoMPJzJ+t4W/R5ck+teZlo3E8i7e+AU5+0rxSSG0e25b/tkC
	 UTJ+jDRR0AHx3W+mSaYv1eHP9AzBk+UrWIrc7XMP1mvJBUG5fYGN3hSNC473YQ0TRT
	 vEZ9sGaHXTAZmTFIcueSs39xlbNbpBaA7otRIvac=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731762AbgEMMPo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 08:15:44 -0400
Received: from mail.kernel.org ([198.145.29.99]:55658 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726020AbgEMMPn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 08:15:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 06B57206D6;
        Wed, 13 May 2020 12:15:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1589372143;
        bh=OFXMCfgg4QqvOju+IW8sguzu0zPnRXnwQP6ptWcD06o=;
        h=From:To:Cc:Subject:Date:From;
        b=V7AbQPKgWJK6PakqeqU1LoITqszt4ASQ0z0pTXUY0NNsOaMoL9t0daWUpgx4oLM0Y
         2ht5Hbpe+SAGdYjs1pamcS00ro46OAHdHHR0JUoJe1EmRtvmlrhAYJYvBroFwq2sIl
         c2rj3Urk/Mqqdmgzmt2UAuD0Kjsmsplvns3EUbJM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jYqIX-00BxoR-Df; Wed, 13 May 2020 13:15:41 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH] KVM: arm64: Simplify __kvm_timer_set_cntvoff implementation
Date: Wed, 13 May 2020 13:15:37 +0100
Message-Id: <20200513121537.77546-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now that this function isn't constrained by the 32bit PCS,
let's simplify it by taking a single 64bit offset instead
of two 32bit parameters.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h |  2 +-
 virt/kvm/arm/arch_timer.c        | 12 +-----------
 virt/kvm/arm/hyp/timer-sr.c      |  3 +--
 3 files changed, 3 insertions(+), 14 deletions(-)

```
#### [PATCH] KVM: arm64: Use cpus_have_final_cap for has_vhe()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11545711
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4846F81
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 10:38:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30A93206D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 10:38:35 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1589366315;
	bh=cdyohDfzAVPN7ZxH8h6kx+enid172A/O+6QoKrrtYpc=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=g6edxvvw9B5ifMPH8jV5MbD7LQWdaBjRpRJRUf6TTl4x78z3cbvUCZaWOTBhCJ3T7
	 W7Vio+zObKV+tnEESIHkgSyzsfUJ7nnEDqZoTsQfVk1X9wV8Mzr9JyHJnRsv0xzeH7
	 fnhnMGsIQUFgpb8puOKZeu35bc+wRIMEviSpqazY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730564AbgEMKie (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 06:38:34 -0400
Received: from mail.kernel.org ([198.145.29.99]:55580 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727812AbgEMKid (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 06:38:33 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 63E1B20673;
        Wed, 13 May 2020 10:38:33 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1589366313;
        bh=cdyohDfzAVPN7ZxH8h6kx+enid172A/O+6QoKrrtYpc=;
        h=From:To:Cc:Subject:Date:From;
        b=RbMjCO9SXAqknjxiUGZwh8QO3U0+rOXlcjUgomVg6pkSSuRp8vMEuijB++gkwTiQm
         iUL8RdibNcRr/qeWWNALIs8RCT7HI6RFzeUdUhZPmllkrIjeux51bpCmNUXwdOGT3w
         y2ImlUqdypdvejXUQgWygyNP0o/w63XtgrmpBNIE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jYomV-00BwQw-Kz; Wed, 13 May 2020 11:38:31 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        dbrazdil@google.com
Subject: [PATCH] KVM: arm64: Use cpus_have_final_cap for has_vhe()
Date: Wed, 13 May 2020 11:38:28 +0100
Message-Id: <20200513103828.74580-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, dbrazdil@google.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By the time we start using the has_vhe() helper, we have long
discovered whether we are running VHE or not. It thus makes
sense to use cpus_have_final_cap() instead of cpus_have_const_cap(),
which leads to a small text size reduction.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/virt.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V5 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to cpu_asid_mask(&boot_cpu_data)
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11545357
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A8D0C14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 08:42:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FC2B20740
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 08:42:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="EIAEu13s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732355AbgEMImr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 04:42:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38716 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732346AbgEMImq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 04:42:46 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 75189C061A0E;
        Wed, 13 May 2020 01:42:46 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id f4so483808pgi.10;
        Wed, 13 May 2020 01:42:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=EIAEu13s66oW9k6Vovao7G9E5SdbVttY2FcvhrhrOpALX1xzdvK/fi/5tSU7AchDrp
         xjLtTXSaYOXC++MtKSG6XSfRi9Uzq1LWgosZxGGJVrmIj7S2PUe4+KOYCVyOlSGXf3Be
         5v1Bo79980xaF8uzo7M0mIugK/BM3uAyVAKwwKiYNjrikkAKXa7FfnwfkUi8ED3Svk3O
         3fv+F72WDxYp7zS9Iii1kCYc+5Ibvam78ju91GWMfRjrXyfbpkW3BlgP3k/AMXBl8izp
         2t73getaNkWaFmZAXSG2AAIwrOUt9mMyFAfFh+Umi9i+CdOWtpfaR1sTnPHEQ9Pyb9M2
         +AjQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=j/OSBdV9DXY2ETWsIc3eeYNxFXzAjwLns12YdEbp9AY=;
        b=T5msJx6rRbsJyoQgLf7HovOv1bNZ//ti8yrhRChYtzX5znKZlK5Lqlf70kW24MTAyU
         QP/yr2Cc1l4JN2GIX0kiTLAomRz3sEHs6HHlRjWXn7Tz6kA0kTCDJ14Ui3OsJlk8skN8
         3e5Tqlqal5epyB0d1O9c1oFm3oKGvG6QWzWD4iNYbo0XXAFSjDjk22zOw5NYdttrLwyR
         wItWSGNx2Kzd47Fe04wAa+6Pvs9zjW4QSdVDxfaPWq7SyqXKpAO3XWbgI3a7BvDp12V1
         /rseUDoflppdR+SfX2t+T0RSpCHa+2CAsOlc69tIuSg7nXXW/6pMGUSdijq+KuSCb+5m
         ynTw==
X-Gm-Message-State: AGi0PuYGcYG13ybuini5cpXlZU0Gpb5XRFQdQSVdMtTpnX+TxBCYodlv
        UIiiC9PLAwIQm1gC3WOZfxc=
X-Google-Smtp-Source: 
 APiQypLiGdoKvwZ0R+yNy9cOCSzPNjj0ev7QHPZckQlRMXmZf3SX1Uw+A0KESJ2kE5bzKLnnJnjwgA==
X-Received: by 2002:a63:f90a:: with SMTP id h10mr23319344pgi.57.1589359366020;
        Wed, 13 May 2020 01:42:46 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 o21sm14645570pjr.37.2020.05.13.01.42.42
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 13 May 2020 01:42:45 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Xing Li <lixing@loongson.cn>, stable@vger.kernel.org,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH V5 01/15] KVM: MIPS: Define KVM_ENTRYHI_ASID to
 cpu_asid_mask(&boot_cpu_data)
Date: Wed, 13 May 2020 16:42:32 +0800
Message-Id: <1589359366-1669-2-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589359366-1669-1-git-send-email-chenhc@lemote.com>
References: <1589359366-1669-1-git-send-email-chenhc@lemote.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Xing Li <lixing@loongson.cn>

The code in decode_config4() of arch/mips/kernel/cpu-probe.c

        asid_mask = MIPS_ENTRYHI_ASID;
        if (config4 & MIPS_CONF4_AE)
                asid_mask |= MIPS_ENTRYHI_ASIDX;
        set_cpu_asid_mask(c, asid_mask);

set asid_mask to cpuinfo->asid_mask.

So in order to support variable ASID_MASK, KVM_ENTRYHI_ASID should also
be changed to cpu_asid_mask(&boot_cpu_data).

Cc: stable@vger.kernel.org
Reviewed-by: Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Signed-off-by: Xing Li <lixing@loongson.cn>
[Huacai: Change current_cpu_data to boot_cpu_data for optimization]
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86/access: Fix phys-bits parameter
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11546541
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F3C5739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:24:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B6AD20708
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:24:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bLcetm6+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388982AbgEMOYH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 10:24:07 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:58585 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388790AbgEMOYH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 10:24:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589379846;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IOf09kqTTqRGDeH0c/dw1Ro4AhpeqWaMooBGpCchpFQ=;
        b=bLcetm6+BTQnkWcyJXogLoPNRwMbGmM5xYjG011gRCiYuondeEA3dn0Yt5Ttj812yz7wx0
        AU/R74dazF9wxfE6Th8itVqO8wUe6VL5rGqUSrzWQ30+a2KIY0Sm+wRt9wg6iulConL7Xi
        kLwxsGIMeVIal3QXpUQ4tvZUxSfN7lg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-159-KNwAzmxAMb2sjRjXWFnuTw-1; Wed, 13 May 2020 10:24:04 -0400
X-MC-Unique: KNwAzmxAMb2sjRjXWFnuTw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F58C18FE863
        for <kvm@vger.kernel.org>; Wed, 13 May 2020 14:24:03 +0000 (UTC)
Received: from localhost.localdomain.com (unknown [10.40.208.32])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6728038D;
        Wed, 13 May 2020 14:23:57 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: thuth@redhat.com, vkuznets@redhat.com,
        Mohammed Gamal <mgamal@redhat.com>
Subject: [kvm-unit-tests PATCH] x86/access: Fix phys-bits parameter
Date: Wed, 13 May 2020 16:23:41 +0200
Message-Id: <20200513142341.774831-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some QEMU versions don't support setting phys-bits argument directly.
This causes breakage to Travis CI. Work around the bug by setting
host-phys-bits=on

Fixes: 1a296ac170f ("x86: access: Add tests for reserved bits of guest physical address")

Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Mohammed Gamal <mgamal@redhat.com>
Tested-by: Thomas Huth <thuth@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v5 36/38] samples: vfio-mdev/mbochs: fix common struct sg_table related issues
##### From: Marek Szyprowski <m.szyprowski@samsung.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marek Szyprowski <m.szyprowski@samsung.com>
X-Patchwork-Id: 11546191
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E09C415AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 13:40:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2978C21534
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 13:34:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=samsung.com header.i=@samsung.com
 header.b="cYmrTQQO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388310AbgEMNd5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 09:33:57 -0400
Received: from mailout1.w1.samsung.com ([210.118.77.11]:59085 "EHLO
        mailout1.w1.samsung.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388038AbgEMNdZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 09:33:25 -0400
Received: from eucas1p2.samsung.com (unknown [182.198.249.207])
        by mailout1.w1.samsung.com (KnoxPortal) with ESMTP id
 20200513133324euoutp01614e9121a5c5d73849f95cf3e1ad86bf~Omcho7YXF2196121961euoutp01-
        for <kvm@vger.kernel.org>; Wed, 13 May 2020 13:33:24 +0000 (GMT)
DKIM-Filter: OpenDKIM Filter v2.11.0 mailout1.w1.samsung.com
 20200513133324euoutp01614e9121a5c5d73849f95cf3e1ad86bf~Omcho7YXF2196121961euoutp01-
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=samsung.com;
        s=mail20170921; t=1589376804;
        bh=4Z3VX9b95pVvmo5Br0ewCVmZiro3PYcbGcBRCw5/dy0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=cYmrTQQOJQJYIxLbJOjPRjT9kBusZQNHJQBiSPgPHs/jpKQUf8agJzNoBWzwpY1IY
         fC4VkozQemM4WeoUyvG1roOv2ofSd5giJkVaW6SmMFPnBp+B/1X0Oq4yiffK9UfGYa
         /JbRDd0MyqdQQCzALACo3pidCdqOFiFtqAm7zPW4=
Received: from eusmges1new.samsung.com (unknown [203.254.199.242]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTP id
        20200513133324eucas1p142c8a86befd97cefee286cdf022951dc~OmchRgFjH0785407854eucas1p1H;
        Wed, 13 May 2020 13:33:24 +0000 (GMT)
Received: from eucas1p1.samsung.com ( [182.198.249.206]) by
        eusmges1new.samsung.com (EUCPMTA) with SMTP id FB.D5.61286.427FBBE5;
 Wed, 13
        May 2020 14:33:24 +0100 (BST)
Received: from eusmtrp1.samsung.com (unknown [182.198.249.138]) by
        eucas1p1.samsung.com (KnoxPortal) with ESMTPA id
        20200513133323eucas1p1519f5901d2a4ee85b781fcc36e9601f7~OmchAzpyr2351423514eucas1p1e;
        Wed, 13 May 2020 13:33:23 +0000 (GMT)
Received: from eusmgms2.samsung.com (unknown [182.198.249.180]) by
        eusmtrp1.samsung.com (KnoxPortal) with ESMTP id
        20200513133323eusmtrp10172f55b09fa88e4e962360e4035a246~OmchAHACf1050610506eusmtrp1h;
        Wed, 13 May 2020 13:33:23 +0000 (GMT)
X-AuditID: cbfec7f2-f0bff7000001ef66-89-5ebbf724c6de
Received: from eusmtip1.samsung.com ( [203.254.199.221]) by
        eusmgms2.samsung.com (EUCPMTA) with SMTP id BF.47.07950.327FBBE5;
 Wed, 13
        May 2020 14:33:23 +0100 (BST)
Received: from AMDC2765.digital.local (unknown [106.120.51.73]) by
        eusmtip1.samsung.com (KnoxPortal) with ESMTPA id
        20200513133323eusmtip16dd11117bccd96d7b870b4e361de6129~OmcgSp9Av0693306933eusmtip1N;
        Wed, 13 May 2020 13:33:23 +0000 (GMT)
From: Marek Szyprowski <m.szyprowski@samsung.com>
To: dri-devel@lists.freedesktop.org, iommu@lists.linux-foundation.org,
        linaro-mm-sig@lists.linaro.org, linux-kernel@vger.kernel.org
Cc: Marek Szyprowski <m.szyprowski@samsung.com>,
        Christoph Hellwig <hch@lst.de>,
        Robin Murphy <robin.murphy@arm.com>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        linux-arm-kernel@lists.infradead.org,
        David Airlie <airlied@linux.ie>,
        Daniel Vetter <daniel@ffwll.ch>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH v5 36/38] samples: vfio-mdev/mbochs: fix common struct
 sg_table related issues
Date: Wed, 13 May 2020 15:32:43 +0200
Message-Id: <20200513133245.6408-36-m.szyprowski@samsung.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200513133245.6408-1-m.szyprowski@samsung.com>
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA0WSa0hTYRzGeXcuOy5Pnabgi0XS0MgolxR6RMtCPxxSog+BEKWuPKjpvOw4
        TSFamRVTlyahmZqYoum8tmZoeSudpZmpmddqaBcFzbxikbbtaH37vc//eXj+78tLIGIdZk+E
        R8WxiihZpAQXofqO1Z4DjiuNgQfrnwnp9J5XAro2pxqj1/WZCD2w9AOnH1W0C+jCZk86724s
        revKB/TigFFA100MYnR/Qx5OV74cF9Ktc5PYMZLRFmgB83y5EGXqlz9jzKdUg4B5XHyFGV2b
        QJisoVLANA6rcCY9eRZnNLpywCzU7Tq15YzIK4SNDI9nFdKjwaKwOVUHHmMUX2pSr2AqMLRN
        DawISB2GbzsaUDUQEWKqDEDN12HAHxYBbJyoxs0uMbUA4Id7bpuJd92ZQt5UCuCgdgHhTaZE
        WruPmXHKFapn1JawLZUCYGe6tTmAUIMCOPNnFjMPbKhg2F3ZLjQzSjlBo0FrYZI6Aq+maIR8
        mwOsqGmxFFiZ9OmxZpTXm4Sw8D7Jsy+8XXsT49kGTht0G9mdsCsrzXI3SCUDaOypFPKHNAD7
        r+UA3uUJx3p+mVYlTOs5w+oGKS8fh9/XZ1GzDKmtcGhmu1lGTHhHn43wMglv3RDz7j0w11D1
        r7a1tw/hmYFF+qmNx3oBYElOAZIBHHL/lxUCUA7sWCUnD2U51yg2wYWTyTllVKjLhWh5HTD9
        pa41w/xTsNR3vg1QBJBYk/RIY6AYk8VzifI2AAlEYkuerDZJZIgsMYlVRAcplJEs1wZ2EKjE
        jjxUNHVOTIXK4tgIlo1hFZtTAWFlrwJ2MSspfWpdgPe2Ip94Zzf6Y2cpuBjB/Xbxl/bimQEt
        vW7eSbspqV/o5GvdqKEk/qej/k1lnWeNJtVPOuK/JBStFjx0yC/2SKqNPZu57p4aNMoNP/AY
        VZ52KXNwytqvRqtOXM4p8bV9r1//In8yn6Fq+TaeUER2el3P7l1yd98rQbkwmes+RMHJ/gIq
        KpNhRwMAAA==
X-Brightmail-Tracker: 
 H4sIAAAAAAAAA+NgFprOIsWRmVeSWpSXmKPExsVy+t/xu7rK33fHGUyYq2fRe+4kk8XGGetZ
        Lf5vm8hsceXrezaLlauPMlks2G9tMWdqocWW03MZLb5cechksenxNVaLy7vmsFmsPXKX3eLg
        hyesDrwea+atYfTY+20Bi8f2bw9YPe53H2fy2Lyk3uP2v8fMHpNvLGf02H2zgc2jt/kdm0ff
        llWMHp83yQVwR+nZFOWXlqQqZOQXl9gqRRtaGOkZWlroGZlY6hkam8daGZkq6dvZpKTmZJal
        FunbJehlfGg4xlbwUKhiX9d31gbGG/xdjJwcEgImEhfPTGTvYuTiEBJYyihxas4EVoiEjMTJ
        aQ1QtrDEn2tdbBBFnxglNp1+xQ6SYBMwlOh6C5EQEehklJjW/REswSxwj0li7zo/EFtYIE7i
        0K0+JhCbRUBV4uHxNWA1vAK2Eo2tfewQG+QlVm84wAxicwLFX93ZzwJiCwnkS+xdvI9tAiPf
        AkaGVYwiqaXFuem5xUZ6xYm5xaV56XrJ+bmbGIGRsu3Yzy07GLveBR9iFOBgVOLhtbi1O06I
        NbGsuDL3EKMEB7OSCK/feqAQb0piZVVqUX58UWlOavEhRlOgoyYyS4km5wOjOK8k3tDU0NzC
        0tDc2NzYzEJJnLdD4GCMkEB6YklqdmpqQWoRTB8TB6dUA+M0pa8bnhzbMbOm4AFTgdZ+9dam
        VLsem4M/q0U/OCiZTbbPm3K+yuCF3cyoZqFv/b//PK3LcP6hlGVSHplUPnFPgwOv6pK9KYIv
        WPWyLmU4ikxd6vRWQSE2mvWbWmLkhLhb+2xkA1+mrcuTYxXZzJ+1VPbT4mUtL47FSu85cUho
        WcNFjktNXkosxRmJhlrMRcWJAIhhNxSqAgAA
X-CMS-MailID: 20200513133323eucas1p1519f5901d2a4ee85b781fcc36e9601f7
X-Msg-Generator: CA
X-RootMTR: 20200513133323eucas1p1519f5901d2a4ee85b781fcc36e9601f7
X-EPHeader: CA
CMS-TYPE: 201P
X-CMS-RootMailID: 20200513133323eucas1p1519f5901d2a4ee85b781fcc36e9601f7
References: <20200513132114.6046-1-m.szyprowski@samsung.com>
        <20200513133245.6408-1-m.szyprowski@samsung.com>
        <CGME20200513133323eucas1p1519f5901d2a4ee85b781fcc36e9601f7@eucas1p1.samsung.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Documentation/DMA-API-HOWTO.txt states that the dma_map_sg() function
returns the number of the created entries in the DMA address space.
However the subsequent calls to the dma_sync_sg_for_{device,cpu}() and
dma_unmap_sg must be called with the original number of the entries
passed to the dma_map_sg().

struct sg_table is a common structure used for describing a non-contiguous
memory buffer, used commonly in the DRM and graphics subsystems. It
consists of a scatterlist with memory pages and DMA addresses (sgl entry),
as well as the number of scatterlist entries: CPU pages (orig_nents entry)
and DMA mapped pages (nents entry).

It turned out that it was a common mistake to misuse nents and orig_nents
entries, calling DMA-mapping functions with a wrong number of entries or
ignoring the number of mapped entries returned by the dma_map_sg()
function.

To avoid such issues, lets use a common dma-mapping wrappers operating
directly on the struct sg_table objects and use scatterlist page
iterators where possible. This, almost always, hides references to the
nents and orig_nents entries, making the code robust, easier to follow
and copy/paste safe.

While touching this code, also add missing call to dma_unmap_sgtable.

Signed-off-by: Marek Szyprowski <m.szyprowski@samsung.com>
---
For more information, see '[PATCH v5 00/38] DRM: fix struct sg_table nents
vs. orig_nents misuse' thread:
https://lore.kernel.org/linux-iommu/20200513132114.6046-1-m.szyprowski@samsung.com/T/
---
 samples/vfio-mdev/mbochs.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v6 1/2] s390/setup: diag318: refactor struct
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11547397
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1A4A0138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:17:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDD7B205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:17:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731051AbgEMWRW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 18:17:22 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:35452 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730827AbgEMWRU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 May 2020 18:17:20 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04DM24XL074564;
        Wed, 13 May 2020 18:17:20 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 310jtydbss-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 18:17:19 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04DM2Lja076328;
        Wed, 13 May 2020 18:17:19 -0400
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 310jtydbrs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 18:17:19 -0400
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04DMEshv015237;
        Wed, 13 May 2020 22:17:17 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma04wdc.us.ibm.com with ESMTP id 3100ubj0gy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 22:17:17 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 04DMHFTp53936534
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 May 2020 22:17:15 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D0363AC059;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A7878AC05E;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.196.213])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 13 May 2020 22:17:15 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v6 1/2] s390/setup: diag318: refactor struct
Date: Wed, 13 May 2020 18:15:56 -0400
Message-Id: <20200513221557.14366-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200513221557.14366-1-walling@linux.ibm.com>
References: <20200513221557.14366-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-13_09:2020-05-13,2020-05-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 impostorscore=0 adultscore=0 phishscore=0 spamscore=0 mlxlogscore=999
 cotscore=-2147483648 malwarescore=0 suspectscore=0 mlxscore=0
 lowpriorityscore=0 clxscore=1015 bulkscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005130184
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The diag318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH v2] i386/kvm: fix a use-after-free when vcpu plug/unplug
##### From: Pan Nengyuan <pannengyuan@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Pan Nengyuan <pannengyuan@huawei.com>
X-Patchwork-Id: 11545231
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D328112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 07:02:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F34162176D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 07:02:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729578AbgEMHCV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 03:02:21 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:37986 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726020AbgEMHCV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 03:02:21 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id D2CC1BA2BD7B96820548;
        Wed, 13 May 2020 15:02:15 +0800 (CST)
Received: from opensource.huawei.com (10.175.100.98) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.487.0; Wed, 13 May 2020 15:02:05 +0800
From: Pan Nengyuan <pannengyuan@huawei.com>
To: <pbonzini@redhat.com>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>
CC: <kvm@vger.kernel.org>, <qemu-devel@nongnu.org>,
        <zhang.zhanghailiang@huawei.com>, <euler.robot@huawei.com>,
        Pan Nengyuan <pannengyuan@huawei.com>
Subject: [PATCH v2] i386/kvm: fix a use-after-free when vcpu plug/unplug
Date: Wed, 13 May 2020 09:26:30 -0400
Message-ID: <20200513132630.13412-1-pannengyuan@huawei.com>
X-Mailer: git-send-email 2.18.2
MIME-Version: 1.0
X-Originating-IP: [10.175.100.98]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we hotplug vcpus, cpu_update_state is added to vm_change_state_head
in kvm_arch_init_vcpu(). But it forgot to delete in kvm_arch_destroy_vcpu() after
unplug. Then it will cause a use-after-free access. This patch delete it in
kvm_arch_destroy_vcpu() to fix that.

Reproducer:
    virsh setvcpus vm1 4 --live
    virsh setvcpus vm1 2 --live
    virsh suspend vm1
    virsh resume vm1

The UAF stack:
==qemu-system-x86_64==28233==ERROR: AddressSanitizer: heap-use-after-free on address 0x62e00002e798 at pc 0x5573c6917d9e bp 0x7fff07139e50 sp 0x7fff07139e40
WRITE of size 1 at 0x62e00002e798 thread T0
    #0 0x5573c6917d9d in cpu_update_state /mnt/sdb/qemu/target/i386/kvm.c:742
    #1 0x5573c699121a in vm_state_notify /mnt/sdb/qemu/vl.c:1290
    #2 0x5573c636287e in vm_prepare_start /mnt/sdb/qemu/cpus.c:2144
    #3 0x5573c6362927 in vm_start /mnt/sdb/qemu/cpus.c:2150
    #4 0x5573c71e8304 in qmp_cont /mnt/sdb/qemu/monitor/qmp-cmds.c:173
    #5 0x5573c727cb1e in qmp_marshal_cont qapi/qapi-commands-misc.c:835
    #6 0x5573c7694c7a in do_qmp_dispatch /mnt/sdb/qemu/qapi/qmp-dispatch.c:132
    #7 0x5573c7694c7a in qmp_dispatch /mnt/sdb/qemu/qapi/qmp-dispatch.c:175
    #8 0x5573c71d9110 in monitor_qmp_dispatch /mnt/sdb/qemu/monitor/qmp.c:145
    #9 0x5573c71dad4f in monitor_qmp_bh_dispatcher /mnt/sdb/qemu/monitor/qmp.c:234

Reported-by: Euler Robot <euler.robot@huawei.com>
Signed-off-by: Pan Nengyuan <pannengyuan@huawei.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
Reviewed-by: Igor Mammedov <imammedo@redhat.com>
---
- v2: remove unnecessary set vmsentry to null(there is no non-null check).
---
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 +++-
 2 files changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v5] arch/x86: Update config and kernel doc for MPK feature on AMD
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11547413
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E267D739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:39:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9284E20727
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 22:39:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="UGAI+dBG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731245AbgEMWjV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 18:39:21 -0400
Received: from mail-bn8nam11on2053.outbound.protection.outlook.com
 ([40.107.236.53]:6245
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726383AbgEMWjU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 May 2020 18:39:20 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jh9mi38oWdT4qaNoM7t/TDW819utlCnX/S9DiWm9rX4ke3JC9AJ7jsJ8tvp+KLypdXFEQap+/6LnG+k9drkC3Qqb8xwrzx1iv/YMWwPLOggesiA1vf/UJGvlKoDbkM1qNNc4Gb25Nofy2Pa2p1ixQUpN0kGAJ3bo70iGbgvNyTBWTvKZxrjVbqZd2cxKdAcgB4wMa4LIAHHDlDnCS5uEVC2mUlIivM92eD2oucFM8DqXMgsb9Mlo0hkgK6Rp3GrAY7QkPtnBUpPvIrefKYrhryhLkAfPTl/zn+6fFycIvaARepG0JsKQvsJ6ygvYwT0z2+Pf3JWCj6uuc/AXMUIfAA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KOKQEhjUABWFW0n7d4Bj/cCmFjo0RfDzIO2VOYgMYJg=;
 b=nzxFJg34BJ6qjMv8YrQqyVusGM+mOi/Oi8XLZxJ+QFGGxqDUHKDWIlyzDdoEk3OFiK8+w6GqShwW6XtiPmFsoAmE9qrGJ1648T1q2XjI41G0v512hGpGoWN3H3tfpngsrfPjM6naa7T0UvNGQX6AdHB3VhbZlAQHYc3PCeEqgj/S3ZZmTdDlZvQyRjlxAA9QkhrkUNZRxMIqveYWMG7oI0URY2k9aBb5el1bUFpwRX/lVzWjjPvoQUkHMJZSILDFvbbOFIRJaWaSxOKZekMnmaFthSg97YftMXy/7pbqFPOzxpbk2yS36zm1O0E2RMioQEPdxSJCSFOF4f6PyDtfoQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KOKQEhjUABWFW0n7d4Bj/cCmFjo0RfDzIO2VOYgMYJg=;
 b=UGAI+dBGjqv72x7I1RgKJBi8kcnvqcH8qVNMMr/M8GQn8Memf6LFoFcY3lL+4VDO0NZqq8nCk3j9nibHDozNhB61CjIOtAngsd8uhO+5zlk0ppO6emQTV6z7FXLLDeiouZK4Wk1fWBccrE49SNru/n0rcIHcwOcvacPDDz2sknw=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2446.namprd12.prod.outlook.com (2603:10b6:802:26::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.33; Wed, 13 May
 2020 22:39:15 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d%7]) with mapi id 15.20.3000.022; Wed, 13 May 2020
 22:39:15 +0000
Subject: [PATCH v5] arch/x86: Update config and kernel doc for MPK feature
 on AMD
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Wed, 13 May 2020 17:39:12 -0500
Message-ID: 
 <158940940570.47998.17107695356894054769.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN6PR16CA0065.namprd16.prod.outlook.com
 (2603:10b6:805:ca::42) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN6PR16CA0065.namprd16.prod.outlook.com (2603:10b6:805:ca::42) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3000.25 via Frontend
 Transport; Wed, 13 May 2020 22:39:13 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2c6196de-9975-44e1-3326-08d7f78e76fa
X-MS-TrafficTypeDiagnostic: SN1PR12MB2446:|SN1PR12MB2446:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB244660428B3C6562C0B2B51495BF0@SN1PR12MB2446.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-Forefront-PRVS: 0402872DA1
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 eqOKuYx8zrboFNiWL/Jq4C0N4bswDZk9pOyqZrue/JtGBLiJjCHzTwnNFeZW+RyqRJCs9aJf0cprJi+bpZEbGgrS9Wz8PGS3Szd/JCc1ZAG56mZT16sr25gmmW6Aj8SHMZGNtiwhdYeh0ikd0iE7ht6ObFQ2p5EwJp1k/K8wuQrQdkKBlOFtkH8KXxtD00XRBWDwDNtfubuEODddJK3ewLcpIwzY9dZ5eZB14i5KHKmhrNoi7lSls164XyvUrWjsFsYU83loqzv7TomZHoRdQzwxJA3ECRG7jC9R6qHwQ5DAIr/uJuE1F6jptF2dG9KbfXKTy+ga+/nAuILFmpDUTAjxvgPQydETL303heoLt44znbY45lGXSj5jJcjgQbsgFHroqlHKiTjsurWnbvPrj6+H0UmTyQv701kOS4MDofP+gzi8iDhMyPQotGamWelcafeJaI444eh9DERxrQo3uwxtdtT2YxpbwCxrAHnESj5QBMK0j/xoT8NVkSDEAPbPBtqh5eV0BeGHapqwwVTur+uUTVQJtksiDjSkmOPAmQz+MGJy48N/671gmozFtogiK7gPFe4rwfgDAd3inMv49ia1lfUR9AmiCuixql3SYYo=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(39860400002)(366004)(376002)(396003)(346002)(136003)(33430700002)(86362001)(956004)(4326008)(66946007)(66476007)(316002)(15650500001)(478600001)(966005)(7406005)(5660300002)(55016002)(44832011)(103116003)(16526019)(2906002)(66556008)(33440700001)(7416002)(52116002)(186003)(26005)(8676002)(8936002)(7696005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Te2c0w/UONxt+i/vwCA+gx9uoCZ4HHZnUeR8OobVhuTLbGSvU64u/gASYGPdM5iM29bNipVIhsPTL9lg/lxWVvM7RBrIRUvSCi4FP/3dUDDRq4XCVfIeR0upin7XtFayYVKcTjWr6D5B50FaCWLHm5+fBmHdzhZosUTXTs63yYddE3+zMwQaEU3HWPcxmlLH4AhLXI8jiJRJPyfOw2ANidt2Oqgy+MWnYipkM5Sj1Db++ZB4GnHKg8/P9EOL9Uj7wPSrz4Cml9uHmYC3Kx+nd2mpjEz31nY13erYRZTOE7tGi1H1cTUwHii12KurJ4vW214I9AIkyI1w92E3UGQmAQ/NS/oCl8w9w3B/3eRbe+8rKKgPg8o6X9ELK/2mmkWr6I7y36SfN5lYQLecuE1C/2ENmO6fkUB6nIxmAUkQDT0fvbqvkZdDfVeunLlSo/r0bSPRIQv37rxk8hdSl/0MbXF/ycB/VtNaoP1gR2b0QXQ=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2c6196de-9975-44e1-3326-08d7f78e76fa
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 May 2020 22:39:15.2488
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 +jcWV/2sScrmsSCKzStOuzo+vmY/EDf8oMCu1U53TQe1v9gbmXh19eWR1xMxTiXu
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2446
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature.

Add a generic X86_MEMORY_PROTECTION_KEYS config shadowing
X86_INTEL_MEMORY_PROTECTION_KEYS and update the kernel
documentation.

No functional changes.

Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Dave Hansen <dave.hansen@linux.intel.com>
---
v5:
 - Just submiting the first config update patch. Paulo said he already queued
   patch 2 & 3.
 - This patch addresses the few text changes suggested by Dave Hansen.

v4:
https://lore.kernel.org/lkml/158932780954.44260.4292038705292213548.stgit@naples-babu.amd.com/
- Removed all the source changes related to config parameter.
    Just kept the doc cahnges and add new config parameter
    X86_MEMORY_PROTECTION_KEYS which shadows X86_INTEL_MEMORY_PROTECTION_KEYS.
 - Minor change in feature detection in kvm/cpuid.c 

v3:
  https://lore.kernel.org/lkml/158923982830.20128.14580309786525588408.stgit@naples-babu.amd.com/#r
  - Fixed the problem Jim Mattson pointed out which can cause pkru
    resources to get corrupted during host and guest switches. 
  - Moved the PKU feature detection code from VMX.c to common code.
  
v2:
  https://lore.kernel.org/lkml/158897190718.22378.3974700869904223395.stgit@naples-babu.amd.com/
  - Introduced intermediate config option X86_MEMORY_PROTECTION_KEYS to
    avoid user propmpts. Kept X86_INTEL_MEMORY_PROTECTION_KEYS as is.
    Eventually, we will be moving to X86_MEMORY_PROTECTION_KEYS after
    couple of kernel revisions. 
  - Moved pkru data structures to kvm_vcpu_arch. Moved save/restore pkru
    to kvm_load_host_xsave_state/kvm_load_guest_xsave_state.

v1:
  https://lore.kernel.org/lkml/158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com/


 Documentation/core-api/protection-keys.rst |    5 +++--
 arch/x86/Kconfig                           |   11 +++++++++--
 2 files changed, 12 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v2 1/4] vfio-ccw: Do not reset FSM state for unsolicited interrupts
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11546553
Return-Path: <SRS0=Sfx5=63=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40624739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:29:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAE102065C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 May 2020 14:29:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389002AbgEMO3q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 May 2020 10:29:46 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:29118 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388740AbgEMO3o (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 May 2020 10:29:44 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04DEA8Ig071505;
        Wed, 13 May 2020 10:29:44 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3101m23555-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 10:29:43 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04DEA8Q3071527;
        Wed, 13 May 2020 10:29:43 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3101m2353k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 10:29:43 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04DEL0s0030083;
        Wed, 13 May 2020 14:29:39 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma01fra.de.ibm.com with ESMTP id 3100ubgq3w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 May 2020 14:29:38 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04DETaji25690322
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 May 2020 14:29:36 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0938642049;
        Wed, 13 May 2020 14:29:36 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F33A042042;
        Wed, 13 May 2020 14:29:35 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 13 May 2020 14:29:35 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id A6917E02BA; Wed, 13 May 2020 16:29:35 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v2 1/4] vfio-ccw: Do not reset FSM state for unsolicited
 interrupts
Date: Wed, 13 May 2020 16:29:31 +0200
Message-Id: <20200513142934.28788-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200513142934.28788-1-farman@linux.ibm.com>
References: <20200513142934.28788-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-13_06:2020-05-13,2020-05-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 phishscore=0 mlxscore=0 suspectscore=0 malwarescore=0 clxscore=1015
 mlxlogscore=762 adultscore=0 priorityscore=1501 lowpriorityscore=0
 impostorscore=0 cotscore=-2147483648 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005130121
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The interrupt handler in vfio_ccw_sch_io_todo() presumes that every
interrupt should reset the FSM state back to IDLE. But this means
that an unsolicited interrupt will cause the FSM to be reset, such
that an in-flight I/O (either still being built, or out on the wire)
will cause a solicited interrupt for which vfio-ccw is no longer
expecting.

Example IRB, while state=CP_PROCESSING:

  irb.w0=00c00011 irb.cpa=02f420f8 irb.w2=85000000

Simply check that the interrupt is solicited before touching the
FSM state.

Fixes: bbe37e4cb8970 ("vfio: ccw: introduce a finite state machine")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
