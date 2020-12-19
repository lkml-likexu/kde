#### [PATCH] genirq/msi: Initialize msi_alloc_info to zero for msi_prepare API
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11981211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E320EC4361B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 06:02:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0FFF23A57
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 06:02:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730159AbgLRGBo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 01:01:44 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9538 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725870AbgLRGBn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Dec 2020 01:01:43 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cxyrk026gzhrg4;
        Fri, 18 Dec 2020 14:00:22 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.179) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Fri, 18 Dec 2020 14:00:50 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <maz@kernel.org>,
        <tglx@linutronix.de>
CC: <kvm@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] genirq/msi: Initialize msi_alloc_info to zero for msi_prepare
 API
Date: Fri, 18 Dec 2020 14:00:39 +0800
Message-ID: <20201218060039.1770-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.179]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 5fe71d271df8 ("irqchip/gic-v3-its: Tag ITS device as shared if
allocating for a proxy device"), some of the devices are wrongly marked as
"shared" by the ITS driver on systems equipped with the ITS(es). The
problem is that the @info->flags may not be initialized anywhere and we end
up looking at random bits on the stack. That's obviously not good.

The straightforward fix is to properly initialize msi_alloc_info inside the
.prepare callback of affected MSI domains (its-pci-msi, its-platform-msi,
etc). We can also perform the initialization in IRQ core layer for
msi_domain_prepare_irqs() API and it looks much neater to me.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---

This was noticed when I was playing with the assigned devices on arm64 and
VFIO failed to enable MSI-X vectors for almost all VFs (CCed kvm list in
case others will hit the same issue). It turned out that these VFs are
marked as "shared" by mistake and have trouble with the following sequence:

	pci_alloc_irq_vectors(pdev, 1, 1, flag);
	pci_free_irq_vectors(pdev);
	pci_alloc_irq_vectors(pdev, 1, 2, flag); --> we can only get
						     *one* vector

But besides VFIO, I guess there are already some devices get into trouble
at probe time and can't work properly.

 kernel/irq/msi.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/3] KVM: selftests: Factor out guest mode code
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11982073
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1DFAC2D0E4
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC70423AC2
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727714AbgLROTS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 09:19:18 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:52318 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727684AbgLROTR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 18 Dec 2020 09:19:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608301068;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=p/vALLVpbV9Mj/xEQnfcKMpU8N7Q3pl/LoSF2oFfjeg=;
        b=Wd4XNTen3OGRq0UU8kohGq+STy/BoygKK9Rc7+F5UjbkTjDqTCBZIF9V2RRZJh8xsdZLIt
        b/yt39MmQnK/vPKhGZqq7Cw3lhi1hLs2kpY2xkJSxpHiwU5lnsFxt9F6JMhLfgbl6gvoAS
        ucq/WIAUlTqxHzijIGT2dp72cOZtlhY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-582-5I545U88No2JjBnoN_msHQ-1; Fri, 18 Dec 2020 09:17:46 -0500
X-MC-Unique: 5I545U88No2JjBnoN_msHQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CAABD1005504;
        Fri, 18 Dec 2020 14:17:45 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2C18D2CFB1;
        Fri, 18 Dec 2020 14:17:40 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v4 1/3] KVM: selftests: Factor out guest mode code
Date: Fri, 18 Dec 2020 15:17:32 +0100
Message-Id: <20201218141734.54359-2-drjones@redhat.com>
In-Reply-To: <20201218141734.54359-1-drjones@redhat.com>
References: <20201218141734.54359-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

demand_paging_test, dirty_log_test, and dirty_log_perf_test have
redundant guest mode code. Factor it out.

Also, while adding a new include, remove the ones we don't need.

Reviewed-by: Ben Gardon <bgardon@google.com>
Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/demand_paging_test.c        | 107 ++++-----------
 .../selftests/kvm/dirty_log_perf_test.c       | 121 +++++------------
 tools/testing/selftests/kvm/dirty_log_test.c  | 125 ++++++------------
 .../selftests/kvm/include/guest_modes.h       |  21 +++
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 ++++++++++
 6 files changed, 189 insertions(+), 257 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c

```
#### [kvm-unit-tests PATCH] arm64: microbench: fix unexpected PPI
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11981311
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 084E7C4361B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 07:17:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5A0E23A23
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 07:16:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727184AbgLRHQn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 02:16:43 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:9903 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726103AbgLRHQn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Dec 2020 02:16:43 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4Cy0WF2G7Zz7D0b;
        Fri, 18 Dec 2020 15:15:21 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.192) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Fri, 18 Dec 2020 15:15:49 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH] arm64: microbench: fix unexpected PPI
Date: Fri, 18 Dec 2020 15:15:42 +0800
Message-ID: <20201218071542.15368-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.192]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For the origin value of CNTV_CVAL_EL0 architecturally UNKNOWN, we may
receive an unexpected PPI before we actual trigger the timer interrupt.
So we should set ARCH_TIMER_CTL_IMASK in timer_prep.

Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
---
 arm/micro-bench.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: change in pv_eoi_get_pending() to make code more readable
##### From: Stephen Zhang <stephenzhangzsd@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Zhang <stephenzhangzsd@gmail.com>
X-Patchwork-Id: 11981395
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 45A7BC4361B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 07:52:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C5A523A1E
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 07:52:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732803AbgLRHw1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 02:52:27 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55488 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728221AbgLRHw1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Dec 2020 02:52:27 -0500
Received: from mail-pg1-x530.google.com (mail-pg1-x530.google.com
 [IPv6:2607:f8b0:4864:20::530])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DD1B9C0617A7;
        Thu, 17 Dec 2020 23:51:46 -0800 (PST)
Received: by mail-pg1-x530.google.com with SMTP id e2so831287pgi.5;
        Thu, 17 Dec 2020 23:51:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=5VSd6QhQzMHF1/sHiWkO/Om8MKHK55gKlP12xsEBAQc=;
        b=nPBYwnZnRDnkzJLG8ciezDh0ioFE9cM89K0LjVQum+nNKuQstWKAG7QiTA7vMg6lQg
         9EUaItPu8ZBnTx3BPYkiMpJMbmkbBMSOoryssx7uOdJJaX0NCEcPnCfyCKht1waGJQj8
         4joG31cVQcaZ2KW+7/Rxp5sa9MvndWOLhlNDd2NNtlXuHECSl9m28Ygw1aFy3/zvZqd8
         r0BVCOexaAGbwFD5k5mYlSoJI8yHSEO60znBOtCqQ8+IbJa7hqT+9iCGxs7HZTY+8810
         gRVCtPEpUuqPuTX7tZit7DjBIPhrdW9QeCX2hYhTfyPEmaFSlzSrpHMfonc7dVcQpUYm
         E1nA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=5VSd6QhQzMHF1/sHiWkO/Om8MKHK55gKlP12xsEBAQc=;
        b=n2Q4qHqVGyOFJjo9+DYAFWtuVlNBhIi4aXifEHxYDV33QFNOdQ2w3TWYY3R1UguoDP
         G36wpFCvkSKyqdFW3UPQ4MIf14RfFAqpRKgpgIZtDRi4e0yJaTFBHOQ6pBhHMI1EvqjK
         eRex2vD0CSzY5QhRmBXwDgpz3hZC5mOQyjpe7UoZjZZBakYMi//W70uX4ZBY30k8IHlt
         WeMj8tOrtfFDP519watDw2R4IizCkxVGbHiCBeQl8BqW7wo6gbxYdUEehYF+vV/Gw4kz
         Xgo/UUVBu5y8rXwshC3rX8ygg9G4790V1tYUFOR9NHNI22QZVsMEpbgZ1/Hn5f1ZgzjI
         flhQ==
X-Gm-Message-State: AOAM5332Bxjd28QN/m+gSYe2dYjoei6QyojFpNnTsTBbqnLzWxuyBrLi
        ia417Hf0uamGTOCv7sgX5qxc3kY0sgLvbw==
X-Google-Smtp-Source: 
 ABdhPJwN60C1OBDKtOWnVAb2bUt5aw9uehpe+VcCZyCCKra2T2YrFYOgjtohyT6ba2gMmuPdaFsOkA==
X-Received: by 2002:a62:fc86:0:b029:19d:9943:c843 with SMTP id
 e128-20020a62fc860000b029019d9943c843mr2641438pfh.71.1608277906531;
        Thu, 17 Dec 2020 23:51:46 -0800 (PST)
Received: from localhost.localdomain
 (ec2-18-162-59-208.ap-east-1.compute.amazonaws.com. [18.162.59.208])
        by smtp.gmail.com with ESMTPSA id
 v125sm8373699pgv.6.2020.12.17.23.51.42
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 17 Dec 2020 23:51:46 -0800 (PST)
From: Stephen Zhang <stephenzhangzsd@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Stephen Zhang <stephenzhangzsd@gmail.com>
Subject: [PATCH] KVM: x86: change in pv_eoi_get_pending() to make code more
 readable
Date: Fri, 18 Dec 2020 15:51:37 +0800
Message-Id: <1608277897-1932-1-git-send-email-stephenzhangzsd@gmail.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Stephen Zhang <stephenzhangzsd@gmail.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: x86/mmu: Use -1 to flag an undefined spte in get_mmio_spte()
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 11981049
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id BA43CC2BBD4
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 00:32:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C97423372
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 00:32:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727144AbgLRAch (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 19:32:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44656 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727137AbgLRAcf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 19:32:35 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 35E97C06138C
        for <kvm@vger.kernel.org>; Thu, 17 Dec 2020 16:31:55 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id h75so488221ybg.18
        for <kvm@vger.kernel.org>; Thu, 17 Dec 2020 16:31:55 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=78xBxovk70v/fvyU3yhuNQMatP3jPljZeMZVBSc56LA=;
        b=B3R1PQgtNPMxojroBSUthuq4U69no1BV6LHzwIpnP2Sj6puZN3CnpVw+zhGmvxrl0q
         JTXB9JGhODmdNX7TioHy+s5pqQnnqQCPalfctnvEjgn5W9qwjUhUZaExbvBaq7kdOC/r
         SLzRgMkzeohdkhNl847qO3lxdKxwJOXZGcG6R/rkTTQnM+VF70b+CZ6bjYt+85ZGZJTC
         T5tIgphJmEhFlbNu6kTE1h5HXZb8q+Csr2CYJulyeZivzdoh53oNuOTOHul26Xth1BDJ
         II5PlL23t5CZGoqldm2PcxCBrvabKIGbnXjvsLlK2j0K7p0yj4Yr1vW+CGiC9cttDbda
         HM5Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=78xBxovk70v/fvyU3yhuNQMatP3jPljZeMZVBSc56LA=;
        b=ABKHKFFsoXURaGDlYleIKVGWWghHu91f8ZuCOMHy21GTdjjFGWB6xoVWBXUvHedgze
         3JHpBZqow6CYGOwwSl8yhdKtmIHCycQCCaPAsR6CjqifnDqqps2N4zBBisB4DsUlHkci
         x0KuqdF6fhRFfKq1v8IvtJhEkf/rJn/Te5cbYdg7lxLiVMBpLKuhjZSW3yx/1BYgLgrS
         MNDkN4cxPb3Ps94obOAxlttrI88aJyrHTTqP2XmqAYcah1QwS+Y7cVcY6uve9j2WoNK/
         Mg+J/oBrMnGt+VF3VI4G9HwScMIkrrzT0sbaecCBb8YswHc6HgNrt0lc6QELVcDGZKs/
         J2HQ==
X-Gm-Message-State: AOAM5307JNqEyEWTcKfIt/nVdcRZmT1/Qq98A7EVVVnZWcdfiGcKHufM
        4AfnwC+Npw3Q4NVCxu+Ql7tkrhTsAgU=
X-Google-Smtp-Source: 
 ABdhPJw0//qXhDKO4cdyBbLqZZOdyHdbbb4ewFr2vGZyeBU7kHgf2afeFksObT5u3Pgo2wDrgOG863zVrws=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:db81:: with SMTP id
 g123mr2924808ybf.277.1608251514431;
 Thu, 17 Dec 2020 16:31:54 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 17 Dec 2020 16:31:36 -0800
In-Reply-To: <20201218003139.2167891-1-seanjc@google.com>
Message-Id: <20201218003139.2167891-2-seanjc@google.com>
Mime-Version: 1.0
References: <20201218003139.2167891-1-seanjc@google.com>
X-Mailer: git-send-email 2.29.2.684.gfbc64c5ab5-goog
Subject: [PATCH 1/4] KVM: x86/mmu: Use -1 to flag an undefined spte in
 get_mmio_spte()
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Richard Herbert <rherbert@sympatico.ca>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Return -1 from the get_walk() helpers if the shadow walk doesn't fill at
least one spte, which can theoretically happen if the walk hits a
not-present PTPDR.  Returning the root level in such a case will cause
get_mmio_spte() to return garbage (uninitialized stack data).  In
practice, such a scenario should be impossible as KVM shouldn't get a
reserved-bit page fault with a not-present PDPTR.

Note, using mmu->root_level in get_walk() is wrong for other reasons,
too, but that's now a moot point.

Fixes: 95fb5b0258b7 ("kvm: x86/mmu: Support MMIO in the TDP MMU")
Cc: Ben Gardon <bgardon@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c     | 7 ++++++-
 arch/x86/kvm/mmu/tdp_mmu.c | 2 +-
 2 files changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM/x86: Move definition of __ex to x86.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11981963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34455C35296
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 12:13:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0748F23443
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 12:13:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727422AbgLRMMz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 07:12:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38938 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727416AbgLRMMx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Dec 2020 07:12:53 -0500
Received: from mail-ed1-x532.google.com (mail-ed1-x532.google.com
 [IPv6:2a00:1450:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CFA6BC0611CE;
        Fri, 18 Dec 2020 04:11:53 -0800 (PST)
Received: by mail-ed1-x532.google.com with SMTP id y24so1435658edt.10;
        Fri, 18 Dec 2020 04:11:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fpfHgLjNqUef0wN0lc7+nNzCiw4Mf77uS73mqGKZnIM=;
        b=mCkVQjDpB6nuKIaWx8YJljXcOY94LkJ5nKGV8N08bV1bxTNGuPBSeyEA7vA83YccO5
         8SHhceT0oQJtyM4+hihCu6p3LQabHOp05TLVcAjJvxFU5XGY7cWaXEgkDmAksyy2I0+g
         GQXz2py0/u5nox0lGpJiIPgfXnZNrOHaaFMIu+Fb18rcfUbMCFCYs8sIxgvEnRmLL5tZ
         /50BZ79EQpqx+fpGZoWK7mxElPkr6BA3JPXIhjAFvx9USGSVqIWmJGe1pWcvoLugr6qe
         9dcUQ1QlESgvPSqMg4H3BkdqE0G8lsuKMYBV+ZH6ljEQjdTq9JqSj+kiFq84xv6DrS91
         e0sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fpfHgLjNqUef0wN0lc7+nNzCiw4Mf77uS73mqGKZnIM=;
        b=BhjkzMydxt6vMnpRp51S0KLDw3so1MqdEMVkt65ufS7mi1Ftt6AELy56BlUfrp0eIx
         otd+sjMf3fxB/eFB6//h2MI8Ynk8lgjxDPUiUGrMoh6YOIMrNL0IwAb8GClbjAesLUYT
         CE/SUftwQwEPxH6iL0lhBIQs7blSQYoZfJHWD6/bRVFgLAlnWwLfQAUq+8sISFJ3VGjx
         eS0d8Q53PV3LZoN/SQNa7JtQakL2N/cCzJCcYHGJoOvzavZpub7ZntWas63kLu15nySe
         0Ktlp8FSXXvcx1vVjNs3G79Mo2knGRF6m5BbL2rUQ+Exfp392u0RmxZEl/hX8JtLTuz+
         VsWA==
X-Gm-Message-State: AOAM531vm/luIYPS9r1cc61dgIFur75Slz0Itn+Ll2/iQrkpcxC7CNLn
        UVQKA2zNDDhWTruwqMRPj7FwOZiC6PFntw==
X-Google-Smtp-Source: 
 ABdhPJzfkGsxDIrFIIAEvsjC2QCxFCNKemW4SsggW8Fc3JEQLPdbEflH3gID8c3dDMLijzQHBOqdjw==
X-Received: by 2002:aa7:ca03:: with SMTP id y3mr4106732eds.87.1608293512052;
        Fri, 18 Dec 2020 04:11:52 -0800 (PST)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 i13sm15852716edu.22.2020.12.18.04.11.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 18 Dec 2020 04:11:51 -0800 (PST)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH] KVM/x86: Move definition of __ex to x86.h
Date: Fri, 18 Dec 2020 13:11:46 +0100
Message-Id: <20201218121146.432286-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Merge __kvm_handle_fault_on_reboot with its sole user
and move the definition of __ex to a common include to be
shared between VMX and SVM.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/include/asm/kvm_host.h | 25 -------------------------
 arch/x86/kvm/svm/svm.c          |  2 --
 arch/x86/kvm/vmx/vmx_ops.h      |  4 +---
 arch/x86/kvm/x86.h              | 23 +++++++++++++++++++++++
 4 files changed, 24 insertions(+), 30 deletions(-)

```
#### linux-next: manual merge of the kvm tree with the arm64-fixes tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11981079
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3C039C2BBCD
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 02:48:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 07A6023A7B
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 02:48:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732463AbgLRCsd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 17 Dec 2020 21:48:33 -0500
Received: from ozlabs.org ([203.11.71.1]:57001 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726851AbgLRCsc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Dec 2020 21:48:32 -0500
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4CxtZZ1Hvjz9sWR;
        Fri, 18 Dec 2020 13:47:50 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1608259670;
        bh=9kLtd9vZRVb0Bzbu/us9QjmM3pXtlm84GlIUkd9FX7o=;
        h=Date:From:To:Cc:Subject:From;
        b=uZfdmiUHzYNu+cxFXGM/P0qEivh5ZpvXsloSwyFWIMSbpIhK6zxaX8EZieGJDEksM
         eZSsQljpZRXskqU6qgGot0dRN+rZSFhNzosAMbGd9x2Dc7BxcRxGfZoNe8Gj61Twwc
         jXBKc14aEZmSJor0sPWU+58J8/G5YTSGQLnplmcO7ASQs42cgjgqbuRPRFLV8SYHmb
         3O73EwWUYWRT4KJ69RbDHKE86SoObvbIQ6EkjFKcwzB3XxfECZeWG9ECiNwpX4ViCj
         HWwEFfs0UofEXtaGj5dlfAGhvEd8qjrXvat1GmGETbraYP7IU7P5a6CBufanmBKGaR
         kv4mrrNk5aDoA==
Date: Fri, 18 Dec 2020 13:47:39 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>
Cc: Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Marc Zyngier <maz@kernel.org>
Subject: linux-next: manual merge of the kvm tree with the arm64-fixes tree
Message-ID: <20201218134739.45973671@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/arm64/include/asm/kvm_asm.h

between commit:

  9fd339a45be5 ("arm64: Work around broken GCC 4.9 handling of "S" constraint")

from the arm64-fixes tree and commit:

  b881cdce77b4 ("KVM: arm64: Allocate hyp vectors statically")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH v1 1/4] s390/kvm: VSIE: stop leaking host addresses
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11982069
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B62A2C2BBCF
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9149323AC2
	for <kvm@archiver.kernel.org>; Fri, 18 Dec 2020 14:19:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727351AbgLROTA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 18 Dec 2020 09:19:00 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:35302 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725883AbgLROS7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 18 Dec 2020 09:18:59 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BIECwCW154079;
        Fri, 18 Dec 2020 09:18:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=aKpVq/XXmlbmksUUEQfZRzUNkWSdVwgJWNs4QCIYb+g=;
 b=nI5N54pkILIUWO0+CSWtEeTDjgUtNWAWt/0npRSu/Oq56JHn6NyyScdNGCMnm3/P+SdQ
 /Em0YSOo5llQa5hbwE8aLyfQQgqV2OLcpoReFj7WtpwdJW/IKW/u50ubagIIpUUEH6Q2
 DlPmc/RICla61G0tgPHa4l/fhwSMtiFaUx/lLupebOP6ihALdqkkQeV4Ln4VQsPkmsBr
 JZPEg6YuKSn3MqE0BU0KSpFfg1+FfqQFFEx+/jQWHECb8cgnF+J9y2B3CepmAZwSpZhL
 +1oYVi2qYdbxitll5VaF+SdgDWD0oaluE2g8mMKaB2Ci8hFZDX117zEQ/v4wg1W1lms0 Bg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35gx01850p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 09:18:17 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BIEDn4F155745;
        Fri, 18 Dec 2020 09:18:17 -0500
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35gx018501-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 09:18:17 -0500
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BIEIFSh012363;
        Fri, 18 Dec 2020 14:18:15 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma02fra.de.ibm.com with ESMTP id 35cng889na-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 18 Dec 2020 14:18:15 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BIEICcK37224838
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 18 Dec 2020 14:18:12 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A298DA405B;
        Fri, 18 Dec 2020 14:18:12 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 453EDA4064;
        Fri, 18 Dec 2020 14:18:12 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.12.102])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 18 Dec 2020 14:18:12 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH v1 1/4] s390/kvm: VSIE: stop leaking host addresses
Date: Fri, 18 Dec 2020 15:18:08 +0100
Message-Id: <20201218141811.310267-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201218141811.310267-1-imbrenda@linux.ibm.com>
References: <20201218141811.310267-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-18_09:2020-12-18,2020-12-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 phishscore=0 spamscore=0 mlxlogscore=999
 impostorscore=0 malwarescore=0 adultscore=0 clxscore=1011 mlxscore=0
 bulkscore=0 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2012180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The addresses in the SIE control block of the host should not be
forwarded to the guest. They are only meaningful to the host, and
moreover it would be a clear security issue.

Subsequent patches will actually put the right values in the guest SIE
control block.

Fixes: a3508fbe9dc6d ("KVM: s390: vsie: initial support for nested virtualization")
Cc: stable@vger.kernel.org
Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/kvm/vsie.c | 5 -----
 1 file changed, 5 deletions(-)

```
