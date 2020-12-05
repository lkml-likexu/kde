#### [PATCH 1/3] KVM: arm64: Fix memory leak on stage2 update of a valid PTE
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11952081
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0EABC4361B
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8469F22C9C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730088AbgLDSUl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 13:20:41 -0500
Received: from mail.kernel.org ([198.145.29.99]:45422 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729780AbgLDSUl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 13:20:41 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id EE9AD22C9C;
        Fri,  4 Dec 2020 18:20:00 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1klFgV-00G3EZ-5G; Fri, 04 Dec 2020 18:19:59 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Keqian Zhu <zhukeqian1@huawei.com>, Will Deacon <will@kernel.org>,
        Yanan Wang <wangyanan55@huawei.com>, kernel-team@android.com,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 1/3] KVM: arm64: Fix memory leak on stage2 update of a valid
 PTE
Date: Fri,  4 Dec 2020 18:19:12 +0000
Message-Id: <20201204181914.783445-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201204181914.783445-1-maz@kernel.org>
References: <20201204181914.783445-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, zhukeqian1@huawei.com,
 will@kernel.org, wangyanan55@huawei.com, kernel-team@android.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yanan Wang <wangyanan55@huawei.com>

When installing a new leaf PTE onto an invalid ptep, we need to
get_page(ptep) to account for the new mapping.

However, simply updating a valid PTE shouldn't result in any
additional refcounting, as there is new mapping. This otherwise
results in a page being forever wasted.

Address this by fixing-up the refcount in stage2_map_walker_try_leaf()
if the PTE was already valid, balancing out the later get_page()
in stage2_map_walk_leaf().

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
[maz: update commit message, add comment in the code]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
Link: https://lore.kernel.org/r/20201201201034.116760-2-wangyanan55@huawei.com
---
 arch/arm64/kvm/hyp/pgtable.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v3 1/2] clocksource: arm_arch_timer: Use stable count reader in erratum sne
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: zhukeqian <zhukeqian1@huawei.com>
X-Patchwork-Id: 11950817
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8839BC19425
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 07:33:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4374022581
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 07:33:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728664AbgLDHdF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 02:33:05 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9009 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726826AbgLDHdE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 02:33:04 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4CnPXm0T1wzhXvB;
        Fri,  4 Dec 2020 15:31:52 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.37) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.487.0; Fri, 4 Dec 2020 15:32:13 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Andrew Morton" <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v3 1/2] clocksource: arm_arch_timer: Use stable count reader
 in erratum sne
Date: Fri, 4 Dec 2020 15:31:25 +0800
Message-ID: <20201204073126.6920-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20201204073126.6920-1-zhukeqian1@huawei.com>
References: <20201204073126.6920-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.37]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In commit 0ea415390cd3 ("clocksource/arm_arch_timer: Use arch_timer_read_counter
to access stable counters"), we separate stable and normal count reader to omit
unnecessary overhead on systems that have no timer erratum.

However, in erratum_set_next_event_tval_generic(), count reader becomes normal
reader. This converts it to stable reader.

Fixes: 0ea415390cd3 ("clocksource/arm_arch_timer: Use arch_timer_read_counter to access stable counters")
Acked-by: Marc Zyngier <maz@kernel.org>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/clocksource/arm_arch_timer.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [for-6.0 v5 01/13] qom: Allow optional sugar props
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11950623
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A17D2C0018C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 05:45:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C9BA224BE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 05:45:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728121AbgLDFpA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 00:45:00 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:51703 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728108AbgLDFpA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 00:45:00 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4CnM8f6LNcz9sSs; Fri,  4 Dec 2020 16:44:18 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1607060658;
        bh=TI0InttZ4cpldxy+Is/TnhjLzGIsGHaeLN81S9U7Zsg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=D2OoZAh2yLriCG90unCBwKyMskSc/APR+ROuvB7A5a/UzSm3GKMPtumVEk+EN8dF9
         1N41Mi1ebQNPsiZtXIIjgDar2WWHr27OOQW+E/ox29F+dxRDxo7hORY+JZp+Vtkh7d
         bot4qHvcnMbfOtshTQnIjVYFywa38eiC5mOK9V7I=
From: David Gibson <david@gibson.dropbear.id.au>
To: pair@us.ibm.com, pbonzini@redhat.com, frankja@linux.ibm.com,
        brijesh.singh@amd.com, dgilbert@redhat.com, qemu-devel@nongnu.org
Cc: Eduardo Habkost <ehabkost@redhat.com>, qemu-ppc@nongnu.org,
        rth@twiddle.net, thuth@redhat.com, berrange@redhat.com,
        mdroth@linux.vnet.ibm.com, Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        david@redhat.com, Richard Henderson <richard.henderson@linaro.org>,
        borntraeger@de.ibm.com, David Gibson <david@gibson.dropbear.id.au>,
        cohuck@redhat.com, kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        pasic@linux.ibm.com, Greg Kurz <groug@kaod.org>
Subject: [for-6.0 v5 01/13] qom: Allow optional sugar props
Date: Fri,  4 Dec 2020 16:44:03 +1100
Message-Id: <20201204054415.579042-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201204054415.579042-1-david@gibson.dropbear.id.au>
References: <20201204054415.579042-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Greg Kurz <groug@kaod.org>

Global properties have an @optional field, which allows to apply a given
property to a given type even if one of its subclasses doesn't support
it. This is especially used in the compat code when dealing with the
"disable-modern" and "disable-legacy" properties and the "virtio-pci"
type.

Allow object_register_sugar_prop() to set this field as well.

Signed-off-by: Greg Kurz <groug@kaod.org>
Message-Id: <159738953558.377274.16617742952571083440.stgit@bahia.lan>
Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 include/qom/object.h |  3 ++-
 qom/object.c         |  4 +++-
 softmmu/vl.c         | 16 ++++++++++------
 3 files changed, 15 insertions(+), 8 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.10, take #5
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11952075
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CB7A0C433FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9F78322C9C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730105AbgLDSUl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 13:20:41 -0500
Received: from mail.kernel.org ([198.145.29.99]:45412 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729472AbgLDSUl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 13:20:41 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B9FF322B4E;
        Fri,  4 Dec 2020 18:20:00 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1klFgU-00G3EZ-ID; Fri, 04 Dec 2020 18:19:58 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Keqian Zhu <zhukeqian1@huawei.com>, Will Deacon <will@kernel.org>,
        Yanan Wang <wangyanan55@huawei.com>, kernel-team@android.com,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.10, take #5
Date: Fri,  4 Dec 2020 18:19:11 +0000
Message-Id: <20201204181914.783445-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, zhukeqian1@huawei.com,
 will@kernel.org, wangyanan55@huawei.com, kernel-team@android.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

A week ago, I was hoping being done with the 5.10 fixes. I should
obviously know better.

Thanks to Yanan's excellent work, we have another set of page table
fixes, all plugging issues introduced with our new page table code.
The problems range from memory leak to TLB conflicts, all of which are
serious enough to be squashed right away.

Are we done yet? Fingers crossed.

Please pull,

	M.

The following changes since commit 23bde34771f1ea92fb5e6682c0d8c04304d34b3b:

  KVM: arm64: vgic-v3: Drop the reporting of GICR_TYPER.Last for userspace (2020-11-17 18:51:09 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.10-5

for you to fetch changes up to 7d894834a305568a0168c55d4729216f5f8cb4e6:

  KVM: arm64: Add usage of stage 2 fault lookup level in user_mem_abort() (2020-12-02 09:53:29 +0000)

----------------------------------------------------------------
kvm/arm64 fixes for 5.10, take #5

- Don't leak page tables on PTE update
- Correctly invalidate TLBs on table to block transition
- Only update permissions if the fault level matches the
  expected mapping size

----------------------------------------------------------------
Yanan Wang (3):
      KVM: arm64: Fix memory leak on stage2 update of a valid PTE
      KVM: arm64: Fix handling of merging tables into a block entry
      KVM: arm64: Add usage of stage 2 fault lookup level in user_mem_abort()

 arch/arm64/include/asm/esr.h         |  1 +
 arch/arm64/include/asm/kvm_emulate.h |  5 +++++
 arch/arm64/kvm/hyp/pgtable.c         | 17 ++++++++++++++++-
 arch/arm64/kvm/mmu.c                 | 11 +++++++++--
 4 files changed, 31 insertions(+), 3 deletions(-)

From patchwork Fri Dec  4 18:19:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11952077
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 26532C4361A
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E663622C9C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:20:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730111AbgLDSUm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 13:20:42 -0500
Received: from mail.kernel.org ([198.145.29.99]:45458 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730095AbgLDSUl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 13:20:41 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 765C122C9F;
        Fri,  4 Dec 2020 18:20:01 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1klFgV-00G3EZ-Mo; Fri, 04 Dec 2020 18:19:59 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Keqian Zhu <zhukeqian1@huawei.com>, Will Deacon <will@kernel.org>,
        Yanan Wang <wangyanan55@huawei.com>, kernel-team@android.com,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 2/3] KVM: arm64: Fix handling of merging tables into a block
 entry
Date: Fri,  4 Dec 2020 18:19:13 +0000
Message-Id: <20201204181914.783445-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201204181914.783445-1-maz@kernel.org>
References: <20201204181914.783445-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, zhukeqian1@huawei.com,
 will@kernel.org, wangyanan55@huawei.com, kernel-team@android.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yanan Wang <wangyanan55@huawei.com>

When dirty logging is enabled, we collapse block entries into tables
as necessary. If dirty logging gets canceled, we can end-up merging
tables back into block entries.

When this happens, we must not only free the non-huge page-table
pages but also invalidate all the TLB entries that can potentially
cover the block. Otherwise, we end-up with multiple possible translations
for the same physical page, which can legitimately result in a TLB
conflict.

To address this, replease the bogus invalidation by IPA with a full
VM invalidation. Although this is pretty heavy handed, it happens
very infrequently and saves a bunch of invalidations by IPA.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
[maz: fixup commit message]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
Link: https://lore.kernel.org/r/20201201201034.116760-3-wangyanan55@huawei.com
---
 arch/arm64/kvm/hyp/pgtable.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH 01/15] KVM: Fix arguments to kvm_{un,}map_gfn()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11950323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 78BA7C0018C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 01:20:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 460D9224D4
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 01:20:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388368AbgLDBUN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 20:20:13 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56456 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388205AbgLDBUK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 20:20:10 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 09DD0C08E85E
        for <kvm@vger.kernel.org>; Thu,  3 Dec 2020 17:18:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=nlfk7fo9/eeQqoeGTfsdj4FxMlsVP85cXV+6FJSJYMM=;
 b=Z06/nG6wsbv0rgrdz49teJtMZe
        2a3vEiqEXIUdqnFf5nxKLzcZwdLO+uDbRi87+fFZGBwjoJzwG+UzA7Qe5vTnXhzBGkD4zVk9Q8AMy
        urZewtDbOI7ME3ShR00yTu9q+RTfKNAm0ZlGY+UwBp1jL7SK4TGoevC8gqbpxrDgf1ndiyzxF4hkK
        5j+So41fOF6ToOFL2aBiLVqawHoYacNimVjoI2MC0SYphQzA04+t5gggq2M3x3Vft91qUgW4uO7xO
        nkVkT07AydaudeEiX55o9RTdB4AGKj4odA8g0KVTIq7VhM85JWf/E2o2/sSBhSSTn79Uxd/GrpRQ1
        Olc9MkKg==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kkzkL-0002jx-8p; Fri, 04 Dec 2020 01:18:53 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kkzkK-00CS9k-6l; Fri, 04 Dec 2020 01:18:52 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH 01/15] KVM: Fix arguments to kvm_{un,}map_gfn()
Date: Fri,  4 Dec 2020 01:18:34 +0000
Message-Id: <20201204011848.2967588-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201204011848.2967588-1-dwmw2@infradead.org>
References: <20201204011848.2967588-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

It shouldn't take a vcpu.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c       | 8 ++++----
 include/linux/kvm_host.h | 4 ++--
 virt/kvm/kvm_main.c      | 8 ++++----
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH v2 1/2] arm64: Make the Meltdown mitigation state available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11952117
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B75DC4361A
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD30322C9C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:38:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730039AbgLDSi1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 13:38:27 -0500
Received: from mail.kernel.org ([198.145.29.99]:48484 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728475AbgLDSi1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 13:38:27 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8267E22C9C;
        Fri,  4 Dec 2020 18:37:46 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1klFxg-00G3Uh-Om; Fri, 04 Dec 2020 18:37:44 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Brazdil <dbarzdil@google.com>, kernel-team@android.com
Subject: [PATCH v2 1/2] arm64: Make the Meltdown mitigation state available
Date: Fri,  4 Dec 2020 18:37:08 +0000
Message-Id: <20201204183709.784533-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201204183709.784533-1-maz@kernel.org>
References: <20201204183709.784533-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 dbarzdil@google.com, kernel-team@android.com
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
#### [PATCH] KVM/SVM: add support for SEV attestation command
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 11952397
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 06FA9C4361B
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 21:30:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C758322AED
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 21:30:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387784AbgLDV3z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 16:29:55 -0500
Received: from mail-dm6nam11on2055.outbound.protection.outlook.com
 ([40.107.223.55]:55512
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727176AbgLDV3y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 16:29:54 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PUOfDAJiELDA1uPv/EQkXpqwI7lN8w4yohoUe/0iOETboGuJX4JQYYwdPEUMBfl30ZUQb2JcuRqEaOns3vGDfwLay+hMW44twE80u3tMwOdvKpSd26PI+JhditjwhfT4gp4bvYzLdmf5Kdy4EzlbLHrtM3reMF39kFbiBQif1w97mzbeeS6ve6YJ+5Kip/Psy6KErcC+ecg/LhxHQgQ5YuKfLV9FjepkOJwBBB0l0smF3LMpPJqUmvFvZ705HHwOkYIhRbE/vg4PBaN8nLEMZjSfG8nBlZcCspH2wY0tXRh4IrF3mAI+vYSimimqUWWQnGyaWytI1nRY0RbPZ6GVPg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5+3dsg26zcWEAFfGxMccFYO1iXI3xw/02umty3122hY=;
 b=JOGqvYicnt0sRtOI2tqzH1hjOPn9nD4mTNLBNYVbvlFXmHk1/xdQ7iPRdLjPY0PzSpsaKcnMODc7YVAYWRhczGA6awgRG6lNPQi5PSu6lvt3qXEQgsTLlX2nRBToVYKOT/EjDz1lvnU30Kg3Lz40ERerSJz3WCoMa2+6AYGGkdomcoHS9DgUj5pEaltYN8nh5Lls6mYYpyEPZTFkImgpCwFtgM320Fslof6tXaDA0GQ/AI9jVlFKL6fkkmPtiHZgmbe9MldK2ghkV589QEYI24Up3k6g989yWRrlm//FhLXyNHOYjK43v/vYdQRDxRV6MrDSxuSiZpuTuoCQVsyJ+Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5+3dsg26zcWEAFfGxMccFYO1iXI3xw/02umty3122hY=;
 b=KqatlDw2rIJBSMG8hQXC+B7gPDCWvp5kT856EClqmyciHQ83gjkrnKI24mZusCQ4Lt7Qy78Yw/uoFOil1G2LUIid0Fv9Q+/cVnxxKDIsI+/+OsCob8lQAExhiC3hzXTVKjmm7fGzfOnulE6lPfLmM7uIEDeMQ1zPaWbopKowxAE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4384.namprd12.prod.outlook.com (2603:10b6:806:9f::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17; Fri, 4 Dec
 2020 21:29:01 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a%6]) with mapi id 15.20.3632.021; Fri, 4 Dec 2020
 21:29:01 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, linux-doc@vger.kernel.org,
        Brijesh Singh <brijesh.singh@amd.com>,
        James Bottomley <jejb@linux.ibm.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>,
        David Rientjes <rientjes@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Borislav Petkov <bp@alien8.de>,
        John Allen <john.allen@amd.com>,
        Herbert Xu <herbert@gondor.apana.org.au>,
        linux-crypto@vger.kernel.org
Subject: [PATCH] KVM/SVM: add support for SEV attestation command
Date: Fri,  4 Dec 2020 15:28:47 -0600
Message-Id: <20201204212847.13256-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0401CA0039.namprd04.prod.outlook.com
 (2603:10b6:803:2a::25) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0401CA0039.namprd04.prod.outlook.com (2603:10b6:803:2a::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17 via Frontend
 Transport; Fri, 4 Dec 2020 21:29:01 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c979c4e3-97a4-41ee-2886-08d8989b9e30
X-MS-TrafficTypeDiagnostic: SA0PR12MB4384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4384B6247DCF1A21F082D293E5F10@SA0PR12MB4384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 PJJ5qf81Cpev0/6oWnEHAK/6t8IUI4nkleXZlw31je3I7RAzBGGt6Ew7cIPaORGuZ6cftBW7kgm2qNny5fjFkSlFOM9QWWJShxRMQRA36+jTNdDZAK1GUIjbgWI8uE94u33hXfy5q1qfaETNyEQgOTgZSZlRkmJATpsgI/fuJkT9oq9q+a6NiKFm0dzEQGCjCkIHga8MNyMMHAWI2OHxqrZyR1SxxJ15QgM6MyHrmCYvY6Ycsqjb7r+PRdYTV7Ip3xncARkownBbCgt6rS6FFClLSFwW4bajWM94lybG/d250mvjpJ1HK1sUZUW9jZVfVajNp1aBB1jTFm8HSAvaFw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(396003)(366004)(346002)(376002)(39860400002)(6486002)(54906003)(8676002)(316002)(4326008)(52116002)(2906002)(7696005)(2616005)(7416002)(8936002)(1076003)(5660300002)(6666004)(83380400001)(6916009)(478600001)(86362001)(956004)(16526019)(66556008)(36756003)(26005)(66476007)(44832011)(66946007)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 OD1sqorUcnJLoj10SlQCbCpBABhesB/vBNrwvWCLQiyxs/3LkWi/6fPsy2FMNQjgzEZxCjGFMU54Z0xZyFh//uorwUFNt6RyCEVXwLjQDPFaneZ8oxeGbGlSiz9AH85G528kqW+EtgpGWLnnqT3UcW2gvaQceROo86YBid1hU3YbT98bL7LsHdY1WyLU+1XrBrU0ziliakKNfJPmzzxEpnj1/aljw1amZ2G3YLT1V4Gbu5fAy0w5ndjKtwX3T1GRDkN1bVV1R0dOP4COonDeiON7zG0U2hB6I/UDjpipBFoktUOuhl+htB7fLdOuUj8QpjhMkmgDmVNploFDEotgHrQGFgXXmDDNmuVFFksdS0wcisEocGXfzRW8t45BtwvyY6nihfB0zxiXe+atTUqjDBbKSbMrTGL0pyS/apgfjOhdsl3rdCTjqJ41novFpBgoyo5JY3iq2InlIWB/biP46S+0NcVnpFE190ahq0no6w9hJ3YgndgZUe/oFhxez9rxYYrkGdl2ed+jxHorMLmYYh+43qA32t09C4X778iolcmMWMlw5im8q4I0AqmZG4gJSKm5QVbvcj8ei+yAC/v44PkoO+y59ThWfBK1VUuh7m5DzeWg9blxFa5WTbEsd0qI583B19bf8C/wXzOOQ2SmBj5Hy27bP2zhBLv+h0WALq1ryRzbLT9Tpk3g54/cU1Htx0uaxtLjCKunT8jM5ddatL3nUJV150Ge/taBg7zW3vlV1RaTIT3HsVMi3ODnI/kP5vatUxJBDbVPDgZ29lkq7dXbv178lyuXPgnQ58mDcIJ8P3VpL8OUSj2BQCCeA9kpRsK/Nkt+AkTp9UtI76pAagEwwheGdkis4MhP5dXrIdMNGJu4Jjh0x5j+72HhF23o98uJuWwOLsCtDP+rIf08sKGeupJmw9pUR7S9p/Rcz0f4j0JeiQiPll7SHrfvkEfnPoQhrsDXC1bnWw6NlT20m5u1wJ4J5G0VCv/N6rqDhxrPTd7x8FLssuDLuEqjSiTk
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c979c4e3-97a4-41ee-2886-08d8989b9e30
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Dec 2020 21:29:01.5933
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ghe1oi28ZUUnzUbGr7XOgqz6dsgGDxR9IDEyEIASg999IYVsvdt083bFavWPrpWq9VNUah4r3+h84KY+A+xW5A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4384
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV FW version >= 0.23 added a new command that can be used to query
the attestation report containing the SHA-256 digest of the guest memory
encrypted through the KVM_SEV_LAUNCH_UPDATE_{DATA, VMSA} commands and
sign the report with the Platform Endorsement Key (PEK).

See the SEV FW API spec section 6.8 for more details.

Note there already exist a command (KVM_SEV_LAUNCH_MEASURE) that can be
used to get the SHA-256 digest. The main difference between the
KVM_SEV_LAUNCH_MEASURE and KVM_SEV_ATTESTATION_REPORT is that the later
can be called while the guest is running and the measurement value is
signed with PEK.

Cc: James Bottomley <jejb@linux.ibm.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Cc: David Rientjes <rientjes@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: John Allen <john.allen@amd.com>
Cc: Herbert Xu <herbert@gondor.apana.org.au>
Cc: linux-crypto@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        | 21 ++++++
 arch/x86/kvm/svm/sev.c                        | 71 +++++++++++++++++++
 drivers/crypto/ccp/sev-dev.c                  |  1 +
 include/linux/psp-sev.h                       | 17 +++++
 include/uapi/linux/kvm.h                      |  8 +++
 5 files changed, 118 insertions(+)

```
#### [PATCH] selftests: kvm: Merge user_msr_test into userspace_msr_exit_test
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11952041
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E1BAC4361A
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 17:32:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3940022AAB
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 17:32:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730901AbgLDRc3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 12:32:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37624 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730871AbgLDRc3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 12:32:29 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D2CACC0613D1
        for <kvm@vger.kernel.org>; Fri,  4 Dec 2020 09:31:48 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id f2so5287750qvb.7
        for <kvm@vger.kernel.org>; Fri, 04 Dec 2020 09:31:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=Kk6uN6RdOO9FkBtUWfbuGzMO7nS5tfoalCD7WHECAH4=;
        b=PmqAXTMIVbnL/bSU58u9EVIIxfX0h9U+Gy16F1qYvItml6lCajNdAk/Oyno/5JZZ5L
         L3/r15T8ShNsXb34v5tKsbFnCge7WQqIefTVPn5cFm33MBLlvKtdMzxZvLyDMJ4CvwfP
         bDkk3sQjA+xnx0W6tMsO6dXL6mNE0hjRE0L9W3GV9kwLQvhixODIdfYjrv6pVM+Kkdhg
         GuKQZ0JwZf3S/+5WXKhTyTVzZf9s62BcoDPolBPU1DfV8v1IgUMVyP6lIkoIThkx5HeW
         zuT/9XD3jbsxidKgjhlpbccAVkn6p346BRoWyFSF6ter6Q713WUYCaW1jUooFaiTJpy1
         VSVw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=Kk6uN6RdOO9FkBtUWfbuGzMO7nS5tfoalCD7WHECAH4=;
        b=adZAyJnXU2v88uiNBfLBX1+5vayMDul89LTuhtBD8+qmxLOp7XHFEOyDQkBzEbsajJ
         jpajZsJk1n2rGsxbPct7aMGBUtlUza6B5PNHIxDn3nz3YV7zsSVIkAXoesQggvZZq3Sk
         dFsFfUXBp5QOoiNZIwtaQufJB2/w8CM0xijzDKeabJYsvPDYY2qOPTPE6hAps+1lprqq
         cWLiE6CPPbpo9c9k5+Fl9Z8aQ3rOV/t6i1xpwIfwOuI1wrwJ6e8pD8Hn/sl7cEIqO7ps
         3CFuidQN2tnpBl/RtCwj2BYGqyqO3WI7mDPkebnLc37+ippg/t+1+z+SjnBUx1F0KCcv
         luxg==
X-Gm-Message-State: AOAM531BiNl7XUVBfQ3dKmNvhraZCGY7O8XxCxX3uhFZPUhyU309MrE6
        l83jFBHepqnp32T/O7wOTcaHF3ErnlEWokqd
X-Google-Smtp-Source: 
 ABdhPJzMc38c+Ek5cgD8413fB/OTrFiJJV6aKUsCU8uP93AxITNzi3fbdeK2u+I/aR/pKMKg20A39HH0mLZM9Pj5
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:ad4:4432:: with SMTP id
 e18mr6450576qvt.57.1607103108011; Fri, 04 Dec 2020 09:31:48 -0800 (PST)
Date: Fri,  4 Dec 2020 09:25:31 -0800
Message-Id: <20201204172530.2958493-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [PATCH] selftests: kvm: Merge user_msr_test into
 userspace_msr_exit_test
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pbonzini@redhat.com, pshier@google.com, jmattson@google.com,
        kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both user_msr_test and userspace_msr_exit_test tests the functionality
of kvm_msr_filter.  Instead of testing this feature in two tests, merge
them together, so there is only one test for this feature.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   2 +-
 tools/testing/selftests/kvm/Makefile          |   2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |   2 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 248 ------
 .../kvm/x86_64/userspace_msr_exit_test.c      | 770 ++++++++++++++++++
 5 files changed, 774 insertions(+), 250 deletions(-)
 delete mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit_test.c

```
#### [PATCH] target/i386/sev: add the support to query the attestation report
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 11952401
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C2BC1C433FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 21:32:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 693D022AED
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 21:32:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727030AbgLDVcI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 16:32:08 -0500
Received: from mail-co1nam11on2083.outbound.protection.outlook.com
 ([40.107.220.83]:25824
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726534AbgLDVcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 16:32:07 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=maLWT1Nl1pip5XFcsJ6bHjYYfiF4vOoo96aW6ptPLWOeOGR0uSOYSIrdgJ0wPMA8y7Uz2uo9H8yR9u5K0hFPoYr1AQ2+FrYBrAI1O0piWr7AEGsYbTj7z3Y6D06YSYd3OlhqfcfFAF16A1UBL2LXALttU6WNu6mS+23qJbdPR8Ez8Na3QbpgAvCwihwWQGFRYmkTB+R215mVWAas4gQs1gwiVNlYX341F+L4E2G9D/pownpPp/JVhNHyojw3UYB7ZsappjBh+ob8OSl2jCqGOgGf00ELUOD34su3WFYVixE2tONupTBfCUEtmwD0PyzVxdEexvbtv/mnz0VqydX2Tg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cIFI4ju2A2xkxveYfptsHT7nH2HM2YPpf9lFfk5qebQ=;
 b=jA684B2tr5CCdV5lcSa2Cp5xxi1e89oQ4mQZn+x+yPb3bmfsAqZ1YRba7QriBoZDeXgicMO4BT5QxssPCYibe17j8h8DK5+Q39wXTYE4VemoFcRRcpLnCXsHBknrQr/eFPjnS+Nirumj66mn8JQs/kXI3SWEyCWnOAjHsrYFh5w9guzdANMEO9nQDLIICAVEO4eeZTmLguW5D9AK/O0XZWBEpB51Eb9ag+PwWqvXgFOmoGPFUTIs5qHnzpUq3rXlKblqCP1ayj8v0wHttfxI9Nc21ZmrbtR+NZtOxHouSbbJV0ZhNuZahJbKpZeRf7vgSqO80q5KbX/iPbIL3q0t/g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=cIFI4ju2A2xkxveYfptsHT7nH2HM2YPpf9lFfk5qebQ=;
 b=S/rJmTAUqxwN45fLR8OIATYDn/BCGM7VlTlUVvoPfkxgmJQj3wPBg/3qtOz5mFjKqLNfpfhUIoVEpgDsAUCeCuu7LZBe+xD34pttDRNEmvpVtWis2JxGUSHK1fhHDLlzjBW7TB+kdeKmSubqlyC121phAMZcE4GtJO02tGax+rg=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4431.namprd12.prod.outlook.com (2603:10b6:806:95::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.25; Fri, 4 Dec
 2020 21:31:14 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a%6]) with mapi id 15.20.3632.021; Fri, 4 Dec 2020
 21:31:14 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: qemu-devel@nongnu.org
Cc: Brijesh Singh <brijesh.singh@amd.com>,
        James Bottomley <jejb@linux.ibm.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>,
        Eric Blake <eblake@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH] target/i386/sev: add the support to query the attestation
 report
Date: Fri,  4 Dec 2020 15:31:01 -0600
Message-Id: <20201204213101.14552-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN6PR2101CA0022.namprd21.prod.outlook.com
 (2603:10b6:805:106::32) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN6PR2101CA0022.namprd21.prod.outlook.com (2603:10b6:805:106::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.2 via Frontend
 Transport; Fri, 4 Dec 2020 21:31:14 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 900d0ca3-73e0-4fa4-2a02-08d8989bed7b
X-MS-TrafficTypeDiagnostic: SA0PR12MB4431:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB44316D5BC2C7DBC26BE87DDCE5F10@SA0PR12MB4431.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1051;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ZEYzC0z5YTXs+gMM3lHulWrHOZMcrX2O4hZop15YmlC6BeXMyiDqdUBj5F+XiVjCMWOprkaSS7OXejA7LGDK2235O4ZSbkFqWAxzgng0MS+1rw74oeJBedsjc3wgo3BCf6XAHEOZFIA/eUINREHbPylOt4v5cVA30T0EGch+ucxU8QBedz1kO398UsNGZw+cshnjgwl6TV+BIyvnAIe6o6li1LOkyTxCJtFu9Nj2dg3WbCfpd3ZiMvi6oSU/A8kLDdux5wPmMfyos2CebYbmOB1hC6L0AdrXpcWDKZcDfMm60weLRMBOpHdBwe7pk25I
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(376002)(136003)(39860400002)(346002)(66946007)(52116002)(6666004)(8676002)(86362001)(66556008)(5660300002)(316002)(186003)(83380400001)(44832011)(6916009)(66476007)(8936002)(2616005)(7696005)(2906002)(54906003)(36756003)(16526019)(1076003)(4326008)(6486002)(478600001)(956004)(26005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 uS5/pglLyEPF25NM8MWpHYx9bpCt9FZ3lgIiz7ibpZOfILowqlInZNM48q7gznw0agHuuB6WMktl3dBKH9zSJIhKcKQQnwgLSWFXPD3DnhhRFKm0Q/HXWhOFRKhmiEVW7XopN8hOH919HkuLAKmQFB+QjB25cdjfL4ryk/6MRPrGeUTEEhtZCYLUxUuU0MFfU6CujKwTGLXN0PvD9NG8tCyabRvpdrZWfF7MUtX+wHmr2CxFiIEN6u1mjDEwPM+uqZcIEG9XRu1gGBgvBLn6zBm9xb0ttqdPbgga7LwhRp7PRiQy+3Y9Z8FGskCsvvVRH2hb7ChEne9ktJMLhOKKc8yqRwKRwxmnIPYHFzYcHi1QqfZWPT7oIlav/lamQfv6aq4lom/9OBAE4z1/BDOYokDHgo1Quxcioede65+PrwYJEyrl8vRKIfwoelYfJeumCOCIUxtqs6HHMwgopi/GgN99bpbRW9NOxs9v0DCHvmEh9wiQu+TK6rwuX1DjjqYxq5UP6a0jBp3sgLLsMKKx5/DbDaP/UVL7PKtL/suwM1gzD14B2lgAoN34VA66EbbQimDeH1kVoBXock6KmmILeZ6xI80xj4F5Th8Mn7RNcfvPFuSgM7Bl7wUutMsJjOmCR3J4ZUqVvUDRk/fk4Pu/OjtDEcA7Wm7n+q6N092oWk9JmEt1XjzRP6CjmNZC46vhxEUfnCy/ASEdbgj100XtrwnqthbjM/wZPSt6Ka8V3z9uJcrSl2QK41mp/mxrvbWZC08aHMAGUoA6N2jXhWG0HcXeLs3MNGiJafYwk7O+4B2gmDHQXnApdZ29tB0C20bTVDLPrdxjWIFRkoHRDyJxC9gTNcc9uSdLN2EBQELUln3ClwMs8AhdrWUlxijwJxOv4Y47kM57dayhXj7+284k5YucmyzmrQ3+nQant5Su6rCR93ALRhIrNwFhhGhjrKthBxyUcnhnu1EzRz9VztqFkSZzVOSyjq17DB2bIIwkvcJoem68mKzQr5uqaY/H1Ick
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 900d0ca3-73e0-4fa4-2a02-08d8989bed7b
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Dec 2020 21:31:14.5809
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 VJDfbrXXlRJTz2uKSjc+E01eNpODfJ2+fqloJaMOApecGJGn64wlyM/iNHarrDneRpZIpq3RhulDVngXIEcJ6g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4431
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV FW >= 0.23 added a new command that can be used to query the
attestation report containing the SHA-256 digest of the guest memory
and VMSA encrypted with the LAUNCH_UPDATE and sign it with the PEK.

Note, we already have a command (LAUNCH_MEASURE) that can be used to
query the SHA-256 digest of the guest memory encrypted through the
LAUNCH_UPDATE. The main difference between previous and this command
is that the report is signed with the PEK and unlike the LAUNCH_MEASURE
command the ATTESATION_REPORT command can be called while the guest
is running.

Add a QMP interface "query-sev-attestation-report" that can be used
to get the report encoded in base64.

Cc: James Bottomley <jejb@linux.ibm.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Cc: Eric Blake <eblake@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 linux-headers/linux/kvm.h |  8 ++++++
 qapi/misc-target.json     | 38 +++++++++++++++++++++++++++
 target/i386/monitor.c     |  6 +++++
 target/i386/sev-stub.c    |  7 +++++
 target/i386/sev.c         | 54 +++++++++++++++++++++++++++++++++++++++
 target/i386/sev_i386.h    |  2 ++
 6 files changed, 115 insertions(+)

```
#### [PATCH] vhost scsi: fix error return code in vhost_scsi_set_endpoint()
##### From: Zhang Changzhong <zhangchangzhong@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhang Changzhong <zhangchangzhong@huawei.com>
X-Patchwork-Id: 11951093
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11066C433FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 08:41:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4A19225AB
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 08:41:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729165AbgLDIkr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 03:40:47 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8687 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726395AbgLDIkr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 03:40:47 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4CnR2h12S5zkkrW;
        Fri,  4 Dec 2020 16:39:24 +0800 (CST)
Received: from compute.localdomain (10.175.112.70) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server (TLS)
 id 14.3.487.0; Fri, 4 Dec 2020 16:39:52 +0800
From: Zhang Changzhong <zhangchangzhong@huawei.com>
To: "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Mike Christie <michael.christie@oracle.com>,
        Maurizio Lombardi <mlombard@redhat.com>
CC: Zhang Changzhong <zhangchangzhong@huawei.com>,
        <virtualization@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] vhost scsi: fix error return code in
 vhost_scsi_set_endpoint()
Date: Fri, 4 Dec 2020 16:43:30 +0800
Message-ID: <1607071411-33484-1-git-send-email-zhangchangzhong@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.112.70]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix to return a negative error code from the error handling
case instead of 0, as done elsewhere in this function.

Fixes: 25b98b64e284 ("vhost scsi: alloc cmds per vq instead of session")
Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Zhang Changzhong <zhangchangzhong@huawei.com>
Reviewed-by: Mike Christie <michael.christie@oracle.com>
---
 drivers/vhost/scsi.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
