#### [PATCH v2 1/2] KVM: arm64: Reject VM creation when the default IPA size is unsupported
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12127703
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89768C433E0
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 10:43:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44A9164FE8
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 10:43:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232729AbhCJKm5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 05:42:57 -0500
Received: from mail.kernel.org ([198.145.29.99]:42876 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232563AbhCJKmZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 05:42:25 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 64F4664FE1;
        Wed, 10 Mar 2021 10:42:24 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lJwII-000jdD-Jy; Wed, 10 Mar 2021 10:42:22 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Andrew Jones <drjones@redhat.com>,
        Eric Auger <eric.auger@redhat.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 1/2] KVM: arm64: Reject VM creation when the default IPA
 size is unsupported
Date: Wed, 10 Mar 2021 10:42:07 +0000
Message-Id: <20210310104208.3819061-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210310104208.3819061-1-maz@kernel.org>
References: <20210310104208.3819061-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 drjones@redhat.com, eric.auger@redhat.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm64 has forever used a 40bit default IPA space, partially
due to its 32bit heritage (where the only choice is 40bit).

However, there are implementations in the wild that have a *cough*
much smaller *cough* IPA space, which leads to a misprogramming of
VTCR_EL2, and a guest that is stuck on its first memory access
if userspace dares to ask for the default IPA setting (which most
VMMs do).

Instead, blundly reject the creation of such VM, as we can't
satisfy the requirements from userspace (with a one-off warning).
Also clarify the boot warning, and document that the VM creation
will fail when an unsupported IPA size is probided.

Although this is an ABI change, it doesn't really change much
for userspace:

- the guest couldn't run before this change, but no error was
  returned. At least userspace knows what is happening.

- a memory slot that was accepted because it did fit the default
  IPA space now doesn't even get a chance to be registered.

The other thing that is left doing is to convince userspace to
actually use the IPA space setting instead of relying on the
antiquated default.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 Documentation/virt/kvm/api.rst |  3 +++
 arch/arm64/kvm/reset.c         | 12 ++++++++----
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v2 1/3] KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12127449
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34DE9C433E0
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:44:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D442164FE3
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:44:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232349AbhCJJoJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 04:44:09 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:13903 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232154AbhCJJng (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 04:43:36 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DwRtg11m8zkX21;
        Wed, 10 Mar 2021 17:42:03 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Wed, 10 Mar 2021 17:43:22 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        "Julien Thierry" <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v2 1/3] KVM: arm64: Move CMOs from user_mem_abort to the
 fault handlers
Date: Wed, 10 Mar 2021 17:43:17 +0800
Message-ID: <20210310094319.18760-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210310094319.18760-1-wangyanan55@huawei.com>
References: <20210310094319.18760-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently uniformly perform CMOs of D-cache and I-cache in function
user_mem_abort() before calling the fault handlers. If we get concurrent
translation faults on the same IPA (page or block), CMOs for the first
time is necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the page table code.

So let's move both clean of D-cache and invalidation of I-cache to the
map path and move only invalidation of I-cache to the permission path.
Since the original APIs for CMOs in mmu.c are only called in function
user_mem_abort, we now also move them to pgtable.c.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 31 ---------------
 arch/arm64/kvm/hyp/pgtable.c     | 68 +++++++++++++++++++++++++-------
 arch/arm64/kvm/mmu.c             | 23 ++---------
 3 files changed, 57 insertions(+), 65 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH 1/4] arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on CPU restart
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12128223
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1FC5BC433E6
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E870B64F9F
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:27:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232952AbhCJP1T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 10:27:19 -0500
Received: from mail.kernel.org ([198.145.29.99]:49172 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231776AbhCJP1L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 10:27:11 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2BE5764F51;
        Wed, 10 Mar 2021 15:27:11 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lK0jt-000n3G-FX; Wed, 10 Mar 2021 15:27:09 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Will Deacon <will@kernel.org>, qperret@google.com,
        kernel-team@android.com
Subject: [PATCH 1/4] arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on
 CPU restart
Date: Wed, 10 Mar 2021 15:26:53 +0000
Message-Id: <20210310152656.3821253-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210310152656.3821253-1-maz@kernel.org>
References: <20210310152656.3821253-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of doing a RMW on SCTLR_EL1 to disable the MMU, use the
existing define that loads the right set of bits.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kernel/cpu-reset.S | 5 +----
 1 file changed, 1 insertion(+), 4 deletions(-)

```
#### [RFC PATCH 1/4] KVM: stats: Separate statistics name strings from debugfs code
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12126773
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50178C43619
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3FB3A65105
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231439AbhCJAbQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 19:31:16 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47992 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231367AbhCJAan (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 19:30:43 -0500
Received: from mail-io1-xd49.google.com (mail-io1-xd49.google.com
 [IPv6:2607:f8b0:4864:20::d49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B820AC061762
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 16:30:43 -0800 (PST)
Received: by mail-io1-xd49.google.com with SMTP id d8so11602057ion.10
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 16:30:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=w4HWO7BOc3rd93ENppTFarD1eUekczKbOeXBNH9YdnE=;
        b=ehzWMPESd1qEKYF5eIXAG8PO252zJXS5nxBQ6cL/dgn9nfrMa9XztHs6xQqzzmZRw1
         /vmJRDYFspuSWYNONt84tXe5Gu+XWSVpDS5/o/G8289D8bznR36qNIukjdSFnR236v6F
         lDW/d7rA405/eDJ1BDISM/F9ADuZhJCFV1zXwIKusXv5B03qHthdli8Qh8dqfE5iPUgH
         yf5v22t4HjFjfXnEYc8htmJBikGzI8CaWUSpNy0ECW/4vcqBKw8OO7hmsGF9RQIDx64m
         AUoIkz2MzIRG1fX85vhR9PCuMa+7RriKV/y9qtBeP8FIOHqqyYJTe7ySReBhXJalb+S6
         pgng==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=w4HWO7BOc3rd93ENppTFarD1eUekczKbOeXBNH9YdnE=;
        b=Mvmv5uvfm3bhIyiGA5RO/NgNDrp9p7KN4ZbGYnuxhmpHqnMRgeeFQZK8oyQE9/e5oY
         SrgnYUbJenRRADXNM97TCNzAEzhVjfj1AF7GBQ2LWKGMAYThwuayHgDaZdVS/s+iHMul
         hh7A8mYvvf/pwxZI1DCtm95PcZGNFSL/4QGW4W+XrAdddlIZqp4ln3g8jpn4Z/oBMYdp
         xKQcF5eosE+6/hqdmuzWVgsarJ/bAUo8Bte8LAWsMKlxb5luxTd7hJA+z8TGCjY9uIZ2
         BwSdf9IUrPSQVHMd9h2CWe0bCz+P8HgYT3tCI0yhy71yUBJkPgAcoJYtLnAPoBJo7MHA
         YKog==
X-Gm-Message-State: AOAM5317bZnoa6xBP/HAtnDsrCCxxaTUw9buFEuIUV7kAOZyhOQ+jy/u
        a6oqJefZ1MHdZknx9VNHsEGhC7I9izI06bc2/OlmM4fkW2G+hyz4JLFtHUyWd3Niw/QsBwlQ8Lm
        cW9kmapyDUdRCMSUFbbv6+mc3VmmATpzdRGKH93hMyR2uX+X+mCDymncmRtfFX5ypW/M8B6Y=
X-Google-Smtp-Source: 
 ABdhPJyRIDsfQsiUcP3akPSY+zemsgHPSz3ZV8SsEBVLSILX/2HwE0zgNRlxmwAlt7ilcx04LhvjxO/9BTJT4PSeEg==
X-Received: from jingzhangos.c.googlers.com
 ([fda3:e722:ac3:10:2b:ff92:c0a8:513])
 (user=jingzhangos job=sendgmr) by 2002:a5d:8c8f:: with SMTP id
 g15mr603463ion.162.1615336243044; Tue, 09 Mar 2021 16:30:43 -0800 (PST)
Date: Wed, 10 Mar 2021 00:30:21 +0000
In-Reply-To: <20210310003024.2026253-1-jingzhangos@google.com>
Message-Id: <20210310003024.2026253-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210310003024.2026253-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [RFC PATCH 1/4] KVM: stats: Separate statistics name strings from
 debugfs code
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVM ARM <kvmarm@lists.cs.columbia.edu>,
        Linux MIPS <linux-mips@vger.kernel.org>,
        KVM PPC <kvm-ppc@vger.kernel.org>,
        Linux S390 <linux-s390@vger.kernel.org>,
        Linux kselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prepare the statistics name strings for supporting binary format
aggregated statistics data retrieval.

No functional change intended.

Signed-off-by: Jing Zhang <jingzhangos@google.com>
---
 arch/arm64/kvm/guest.c    |  47 ++++--
 arch/mips/kvm/mips.c      | 114 ++++++++++----
 arch/powerpc/kvm/book3s.c | 107 +++++++++----
 arch/powerpc/kvm/booke.c  |  84 +++++++---
 arch/s390/kvm/kvm-s390.c  | 320 ++++++++++++++++++++++++++------------
 arch/x86/kvm/x86.c        | 127 ++++++++++-----
 include/linux/kvm_host.h  |  31 +++-
 7 files changed, 589 insertions(+), 241 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Skip !MMU-present SPTEs when removing SP in exclusive mode
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12126739
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 33CCEC433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E885164FF7
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 00:31:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231295AbhCJAai (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 19:30:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47944 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231332AbhCJAad (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 19:30:33 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5645BC06174A
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 16:30:33 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id e10so11453315qvr.17
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 16:30:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=ZbG3xZb8PBQgiaDoQSCf4y5RYRarcXuHOWtQzEo4Lp4=;
        b=us2FvwuKuUsnKtfzXb/jE9ZyNfz3iRwsk6KoFEfxEIznNEhIADvJky2H+nPDcHEZR/
         vll9/s0EeGTtsOotd350+EnFp+LlDw9a7VzG7Yzup0s7mN88cuVzSHHDWewX+PXJC3U0
         +WhZREu1Dw2O+ti0oRCiF+/PyGn5LBENAwy9wXS7g2VW4IVqT7PkYnyNeJ9A4YmGpCAC
         Ritx82nsW4Kpi/W6N1Sv557L3+x2JRRz6SkRU2WNSl6xG87d717YIRdK0HDQZlmj2MqU
         Hgs1pijsHPN8P3gS1o5ylJOoC4vYeIW/w+qjmVjrPzce/+GcqTGt3dqS0Qlao7bGwccb
         S2lQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=ZbG3xZb8PBQgiaDoQSCf4y5RYRarcXuHOWtQzEo4Lp4=;
        b=judCnNUA5jrEPUvnnPsathWTiPtgn83W+aO0rXozTEK8QuramftkBQ295rrRnLiUNu
         wkxWsJI9M5XMzbzXL2wkmsYV/Tj3d5V4qBhZP1buR64PCk+t3HhvVElcV1OO9jSoxV2n
         r4d95sT0eoKGoUFQN/nvuR6FDBBMs9LgWJi+Zn/dyca2GcekYIwM01myzQIvxRBoKb/M
         H6638L73dvOWdPPQF5QkhcSe/uQ9ie+Zskts5BuspKliSYGSWE+s2kY/1u1Cra74D7id
         P/BOV7bt4soM+HI+vYf/Idj/mvLDKO+e/YInD+raSY/pP/FaAIDNeePNRVTG0SMgYS26
         T4rQ==
X-Gm-Message-State: AOAM533lYxazTmL7Nu+FN3b6WcOyv/5u2+Y2766RW/NqK2+L2OCIY/7T
        KXEJr22y6b4JK/PS/fVU/gzWKdHfRWU=
X-Google-Smtp-Source: 
 ABdhPJz8JBsJ6DNuTmV245LAf4RiHcBxMThlSVNRRXuyrUb6m0zifQoo7EXUCGWd67jnrZzuYtZf609dG5c=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e4dd:6c31:9463:f8da])
 (user=seanjc job=sendgmr) by 2002:a0c:b71a:: with SMTP id
 t26mr558668qvd.38.1615336232507;
 Tue, 09 Mar 2021 16:30:32 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  9 Mar 2021 16:30:29 -0800
Message-Id: <20210310003029.1250571-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH] KVM: x86/mmu: Skip !MMU-present SPTEs when removing SP in
 exclusive mode
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

If mmu_lock is held for write, don't bother setting !PRESENT SPTEs to
REMOVED_SPTE when recursively zapping SPTEs as part of shadow page
removal.  The concurrent write protections provided by REMOVED_SPTE are
not needed, there are no backing page side effects to record, and MMIO
SPTEs can be left as is since they are protected by the memslot
generation, not by ensuring that the MMIO SPTE is unreachable (which
is racy with respect to lockless walks regardless of zapping behavior).

Skipping !PRESENT drastically reduces the number of updates needed to
tear down sparsely populated MMUs, e.g. when tearing down a 6gb VM that
didn't touch much memory, 6929/7168 (~96.6%) of SPTEs were '0' and could
be skipped.

Avoiding the write itself is likely close to a wash, but avoiding
__handle_changed_spte() is a clear-cut win as that involves saving and
restoring all non-volatile GPRs (it's a subtly big function), as well as
several conditional branches before bailing out.

Cc: Ben Gardon <bgardon@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v4 1/1] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12128189
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8FDD4C433E9
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:07:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6118F64F40
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 15:07:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232975AbhCJPGl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 10:06:41 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:15434 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231909AbhCJPGJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Mar 2021 10:06:09 -0500
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12AF3GjH026649;
        Wed, 10 Mar 2021 10:06:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=aK/i2hlLf7KyFUHTNJKHjKVM3X9d03P3OYHbihR43v4=;
 b=YmwylVAC6zIfnDLbBhUgYYS+vGpeHiUswPLPNCic4SKcqTL0VdaeXUuXdScOP9/bmWgt
 74xwekYJP1/gXvTzQeWa0eVB8wjYzJoHwq2oUF3FWUSJFTq6COKulJTjRCe71WfCpq8c
 t75x0uZTuBE89T9iOAmdDth8LeHydEryzyFpCIvRJO3xCh/7bMNj82JE+AkeK0QOkScV
 xRQ82QfcmC5wO9zmjk93uQp3odxT5L3O0S/EG50nzsu8pa+hyE5atrySQlnsE3NoYSE7
 iMysuZrAblEOEm+RKxmpYOAsHXzFxNThPIL/bNfpoWqd4lHKAuYibKNdJZxWIBCXcY50 tw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 376j2kxk4f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 10:06:08 -0500
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12AF4c8B043269;
        Wed, 10 Mar 2021 10:06:07 -0500
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 376j2kxk3h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 10:06:07 -0500
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12AF4B63003270;
        Wed, 10 Mar 2021 15:06:05 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma05wdc.us.ibm.com with ESMTP id 3768mvgnwx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Mar 2021 15:06:05 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 12AF65IP29163926
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 10 Mar 2021 15:06:05 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6D62428066;
        Wed, 10 Mar 2021 15:06:05 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7C1B02805C;
        Wed, 10 Mar 2021 15:06:04 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.150.254])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 10 Mar 2021 15:06:04 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com
Subject: [PATCH v4 1/1] s390/vfio-ap: fix circular lockdep when
 setting/clearing crypto masks
Date: Wed, 10 Mar 2021 10:05:59 -0500
Message-Id: <20210310150559.8956-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20210310150559.8956-1-akrowiak@linux.ibm.com>
References: <20210310150559.8956-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-10_09:2021-03-10,2021-03-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 bulkscore=0 phishscore=0 spamscore=0 impostorscore=0
 mlxlogscore=999 priorityscore=1501 clxscore=1015 mlxscore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103100073
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
---
 drivers/s390/crypto/vfio_ap_ops.c     | 309 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 96 deletions(-)

```
#### [PATCH v2] vfio/pci: Handle concurrent vma faultsFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12129053
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2CCBBC433E6
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 18:58:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCACC64F83
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 18:58:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233666AbhCJS6Z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 13:58:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:55105 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233422AbhCJS6T (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Mar 2021 13:58:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615402699;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZU6Kc8uQsaX+NELkZSTr0b1PNiA71McvIaFWuScfNKY=;
        b=VWHnPflVRPkeQZu/ZYmRf8aoHk/7CIBUaA4PhNo3rHNJKloMuKwmy7OvtAwZhzrqHyuFK2
        +3l12zo3AFDnKbiJSsX2dyesob3ZzyyoHW9g9ZSBkgurwPC5D6ib1/aClbbwNTUraCHmbm
        mSe74YPXRDWyjJCKtSveKLQ/8tdHdCA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-449-UhquQQhUN9KrgFjVbGda3A-1; Wed, 10 Mar 2021 13:58:17 -0500
X-MC-Unique: UhquQQhUN9KrgFjVbGda3A-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EC036801817;
        Wed, 10 Mar 2021 18:58:15 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C56D65D6D7;
        Wed, 10 Mar 2021 18:58:07 +0000 (UTC)
Subject: [PATCH v2] vfio/pci: Handle concurrent vma faults
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, jgg@nvidia.com,
        peterx@redhat.com, prime.zeng@hisilicon.com, cohuck@redhat.com
Date: Wed, 10 Mar 2021 11:58:07 -0700
Message-ID: <161540257788.10151.6284852774772157400.stgit@gimli.home>
User-Agent: StGit/0.21-2-g8ef5
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pci_mmap_fault() incorrectly makes use of io_remap_pfn_range()
from within a vm_ops fault handler.  This function will trigger a
BUG_ON if it encounters a populated pte within the remapped range,
where any fault is meant to populate the entire vma.  Concurrent
inflight faults to the same vma will therefore hit this issue,
triggering traces such as:

[ 1591.733256] kernel BUG at mm/memory.c:2177!
[ 1591.739515] Internal error: Oops - BUG: 0 [#1] PREEMPT SMP
[ 1591.747381] Modules linked in: vfio_iommu_type1 vfio_pci vfio_virqfd vfio pv680_mii(O)
[ 1591.760536] CPU: 2 PID: 227 Comm: lcore-worker-2 Tainted: G O 5.11.0-rc3+ #1
[ 1591.770735] Hardware name:  , BIOS HixxxxFPGA 1P B600 V121-1
[ 1591.778872] pstate: 40400009 (nZcv daif +PAN -UAO -TCO BTYPE=--)
[ 1591.786134] pc : remap_pfn_range+0x214/0x340
[ 1591.793564] lr : remap_pfn_range+0x1b8/0x340
[ 1591.799117] sp : ffff80001068bbd0
[ 1591.803476] x29: ffff80001068bbd0 x28: 0000042eff6f0000
[ 1591.810404] x27: 0000001100910000 x26: 0000001300910000
[ 1591.817457] x25: 0068000000000fd3 x24: ffffa92f1338e358
[ 1591.825144] x23: 0000001140000000 x22: 0000000000000041
[ 1591.832506] x21: 0000001300910000 x20: ffffa92f141a4000
[ 1591.839520] x19: 0000001100a00000 x18: 0000000000000000
[ 1591.846108] x17: 0000000000000000 x16: ffffa92f11844540
[ 1591.853570] x15: 0000000000000000 x14: 0000000000000000
[ 1591.860768] x13: fffffc0000000000 x12: 0000000000000880
[ 1591.868053] x11: ffff0821bf3d01d0 x10: ffff5ef2abd89000
[ 1591.875932] x9 : ffffa92f12ab0064 x8 : ffffa92f136471c0
[ 1591.883208] x7 : 0000001140910000 x6 : 0000000200000000
[ 1591.890177] x5 : 0000000000000001 x4 : 0000000000000001
[ 1591.896656] x3 : 0000000000000000 x2 : 0168044000000fd3
[ 1591.903215] x1 : ffff082126261880 x0 : fffffc2084989868
[ 1591.910234] Call trace:
[ 1591.914837]  remap_pfn_range+0x214/0x340
[ 1591.921765]  vfio_pci_mmap_fault+0xac/0x130 [vfio_pci]
[ 1591.931200]  __do_fault+0x44/0x12c
[ 1591.937031]  handle_mm_fault+0xcc8/0x1230
[ 1591.942475]  do_page_fault+0x16c/0x484
[ 1591.948635]  do_translation_fault+0xbc/0xd8
[ 1591.954171]  do_mem_abort+0x4c/0xc0
[ 1591.960316]  el0_da+0x40/0x80
[ 1591.965585]  el0_sync_handler+0x168/0x1b0
[ 1591.971608]  el0_sync+0x174/0x180
[ 1591.978312] Code: eb1b027f 540000c0 f9400022 b4fffe02 (d4210000)

Switch to using vmf_insert_pfn() to allow replacing mappings, and
include decrypted memory protection as formerly provided by
io_remap_pfn_range().  Tracking of vmas is also updated to
prevent duplicate entries.

Fixes: 11c4cd07ba11 ("vfio-pci: Fault mmaps to enable vma tracking")
Reported-by: Zeng Tao <prime.zeng@hisilicon.com>
Suggested-by: Zeng Tao <prime.zeng@hisilicon.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---

v2: Set decrypted pgprot in mmap, use non-_prot vmf_insert_pfn()
    as suggested by Jason G.

 drivers/vfio/pci/vfio_pci.c |   30 ++++++++++++++++++------------
 1 file changed, 18 insertions(+), 12 deletions(-)

```
#### [PATCH V3 1/6] vDPA/ifcvf: get_vendor_id returns a device specific vendor id
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12127353
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DD2DC433E0
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:06:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31E9964FE2
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 09:06:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232505AbhCJJGE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 04:06:04 -0500
Received: from mga03.intel.com ([134.134.136.65]:64352 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230156AbhCJJGC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 04:06:02 -0500
IronPort-SDR: 
 WvL3AhV9FgVx/hoshrlyhd91I235PLsrdaksrnIS19+GN3URZLZ4hfPpmRUYHLTnxJNaOW8NFL
 prDO9HYfdvxQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9917"; a="188461255"
X-IronPort-AV: E=Sophos;i="5.81,237,1610438400";
   d="scan'208";a="188461255"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 01:06:02 -0800
IronPort-SDR: 
 T85nlmfwjxlaXG2m59tn8p4maoCvmhmQd7FB1coXIb4ARwEeWrdJ9rWgpFVopgmyCaROAlbsEa
 XWKyrHMlHHbQ==
X-IronPort-AV: E=Sophos;i="5.81,237,1610438400";
   d="scan'208";a="410110283"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Mar 2021 01:06:00 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V3 1/6] vDPA/ifcvf: get_vendor_id returns a device specific
 vendor id
Date: Wed, 10 Mar 2021 17:00:47 +0800
Message-Id: <20210310090052.4762-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210310090052.4762-1-lingshan.zhu@intel.com>
References: <20210310090052.4762-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In this commit, ifcvf_get_vendor_id() will return
a device specific vendor id of the probed pci device
than a hard code.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_main.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH] vfio/pci: Handle concurrent vma faultsFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12128871
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D853EC433E6
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 17:54:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BDB164FAF
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 17:54:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233418AbhCJRx5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 12:53:57 -0500
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:40508 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233141AbhCJRxm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Mar 2021 12:53:42 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615398822;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=PuJS7Uwxjf6BC5NU8Y7Fju1Ajk5eXmk9D7KP7XIVI9E=;
        b=PYdhZt9RcIJVy+lJMjN72MeEqZcQgoUQn9jWNIvI141Nm81AUCG8INl3j0JE7Y54TIJKqO
        z427OpoiUEonIEQIgnlVntNvupvp1jah9YNRMv70gf61psm3S1thBtWuHUncTCIfBYW/HC
        jye2QlYMv9qV1bKbWbTibvYtPl4RBZw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-62-a6dvy-ReNKWEL7uMIW-mrg-1; Wed, 10 Mar 2021 12:53:38 -0500
X-MC-Unique: a6dvy-ReNKWEL7uMIW-mrg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 23ECE808259;
        Wed, 10 Mar 2021 17:53:37 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 04846E15C;
        Wed, 10 Mar 2021 17:53:29 +0000 (UTC)
Subject: [PATCH] vfio/pci: Handle concurrent vma faults
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, jgg@nvidia.com,
        peterx@redhat.com, prime.zeng@hisilicon.com, cohuck@redhat.com
Date: Wed, 10 Mar 2021 10:53:29 -0700
Message-ID: <161539852724.8302.17137130175894127401.stgit@gimli.home>
User-Agent: StGit/0.21-2-g8ef5
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_pci_mmap_fault() incorrectly makes use of io_remap_pfn_range()
from within a vm_ops fault handler.  This function will trigger a
BUG_ON if it encounters a populated pte within the remapped range,
where any fault is meant to populate the entire vma.  Concurrent
inflight faults to the same vma will therefore hit this issue,
triggering traces such as:

[ 1591.733256] kernel BUG at mm/memory.c:2177!
[ 1591.739515] Internal error: Oops - BUG: 0 [#1] PREEMPT SMP
[ 1591.747381] Modules linked in: vfio_iommu_type1 vfio_pci vfio_virqfd vfio pv680_mii(O)
[ 1591.760536] CPU: 2 PID: 227 Comm: lcore-worker-2 Tainted: G O 5.11.0-rc3+ #1
[ 1591.770735] Hardware name:  , BIOS HixxxxFPGA 1P B600 V121-1
[ 1591.778872] pstate: 40400009 (nZcv daif +PAN -UAO -TCO BTYPE=--)
[ 1591.786134] pc : remap_pfn_range+0x214/0x340
[ 1591.793564] lr : remap_pfn_range+0x1b8/0x340
[ 1591.799117] sp : ffff80001068bbd0
[ 1591.803476] x29: ffff80001068bbd0 x28: 0000042eff6f0000
[ 1591.810404] x27: 0000001100910000 x26: 0000001300910000
[ 1591.817457] x25: 0068000000000fd3 x24: ffffa92f1338e358
[ 1591.825144] x23: 0000001140000000 x22: 0000000000000041
[ 1591.832506] x21: 0000001300910000 x20: ffffa92f141a4000
[ 1591.839520] x19: 0000001100a00000 x18: 0000000000000000
[ 1591.846108] x17: 0000000000000000 x16: ffffa92f11844540
[ 1591.853570] x15: 0000000000000000 x14: 0000000000000000
[ 1591.860768] x13: fffffc0000000000 x12: 0000000000000880
[ 1591.868053] x11: ffff0821bf3d01d0 x10: ffff5ef2abd89000
[ 1591.875932] x9 : ffffa92f12ab0064 x8 : ffffa92f136471c0
[ 1591.883208] x7 : 0000001140910000 x6 : 0000000200000000
[ 1591.890177] x5 : 0000000000000001 x4 : 0000000000000001
[ 1591.896656] x3 : 0000000000000000 x2 : 0168044000000fd3
[ 1591.903215] x1 : ffff082126261880 x0 : fffffc2084989868
[ 1591.910234] Call trace:
[ 1591.914837]  remap_pfn_range+0x214/0x340
[ 1591.921765]  vfio_pci_mmap_fault+0xac/0x130 [vfio_pci]
[ 1591.931200]  __do_fault+0x44/0x12c
[ 1591.937031]  handle_mm_fault+0xcc8/0x1230
[ 1591.942475]  do_page_fault+0x16c/0x484
[ 1591.948635]  do_translation_fault+0xbc/0xd8
[ 1591.954171]  do_mem_abort+0x4c/0xc0
[ 1591.960316]  el0_da+0x40/0x80
[ 1591.965585]  el0_sync_handler+0x168/0x1b0
[ 1591.971608]  el0_sync+0x174/0x180
[ 1591.978312] Code: eb1b027f 540000c0 f9400022 b4fffe02 (d4210000)

Switch to using vmf_insert_pfn_prot() so that we can retain the
decrypted memory protection from io_remap_pfn_range(), but allow
concurrent page table updates.  Tracking of vmas is also updated to
prevent duplicate entries.

Fixes: 11c4cd07ba11 ("vfio-pci: Fault mmaps to enable vma tracking")
Reported-by: Zeng Tao <prime.zeng@hisilicon.com>
Suggested-by: Zeng Tao <prime.zeng@hisilicon.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---

Zeng Tao, I hope you don't mind me sending a new version to keep
this moving.  Testing and review appreciated, thanks!

 drivers/vfio/pci/vfio_pci.c |   30 ++++++++++++++++++------------
 1 file changed, 18 insertions(+), 12 deletions(-)

```
#### [PATCH v2 1/7] x86/boot/compressed/64: Cleanup exception handling before booting kernel
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12127299
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49415C43381
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 08:45:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00F2064FFD
	for <kvm@archiver.kernel.org>; Wed, 10 Mar 2021 08:45:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232330AbhCJIo2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Mar 2021 03:44:28 -0500
Received: from 8bytes.org ([81.169.241.247]:58258 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232363AbhCJIn5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Mar 2021 03:43:57 -0500
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id A6EE72ED;
        Wed, 10 Mar 2021 09:43:51 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v2 1/7] x86/boot/compressed/64: Cleanup exception handling
 before booting kernel
Date: Wed, 10 Mar 2021 09:43:19 +0100
Message-Id: <20210310084325.12966-2-joro@8bytes.org>
X-Mailer: git-send-email 2.30.1
In-Reply-To: <20210310084325.12966-1-joro@8bytes.org>
References: <20210310084325.12966-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Disable the exception handling before booting the kernel to make sure
any exceptions that happen during early kernel boot are not directed to
the pre-decompression code.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/boot/compressed/idt_64.c | 14 ++++++++++++++
 arch/x86/boot/compressed/misc.c   |  7 ++-----
 arch/x86/boot/compressed/misc.h   |  6 ++++++
 3 files changed, 22 insertions(+), 5 deletions(-)

```
