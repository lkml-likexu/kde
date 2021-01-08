

#### [PATCH 0/6] vfio/iommu_type1: Some optimizations about dirty tracking
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Jan  7 04:43:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12002883
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A5A17C433DB
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 04:46:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7726822CE3
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 04:46:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726882AbhAGEpQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 23:45:16 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:9966 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726684AbhAGEpQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Jan 2021 23:45:16 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DBDC84vtmzj2Xl;
        Thu,  7 Jan 2021 12:43:48 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.498.0; Thu, 7 Jan 2021 12:44:25 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, "Marc Zyngier" <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH 0/6] vfio/iommu_type1: Some optimizations about dirty tracking
Date: Thu, 7 Jan 2021 12:43:55 +0800
Message-ID: <20210107044401.19828-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

In patch series[1], I put forward some fixes and optimizations for
vfio_iommu_type1. This extracts and improves the optimization part
of it.

[1] https://lore.kernel.org/linux-iommu/20201210073425.25960-1-zhukeqian1@huawei.com/T/#t

Thanks,
Keqian


Keqian Zhu (6):
  vfio/iommu_type1: Make an explicit "promote" semantic
  vfio/iommu_type1: Ignore external domain when promote pinned_scope
  vfio/iommu_type1: Initially set the pinned_page_dirty_scope
  vfio/iommu_type1: Drop parameter "pgsize" of vfio_dma_bitmap_alloc_all
  vfio/iommu_type1: Drop parameter "pgsize" of vfio_iova_dirty_bitmap
  vfio/iommu_type1: Drop parameter "pgsize" of update_user_bitmap

 drivers/vfio/vfio_iommu_type1.c | 67 +++++++++++++--------------------
 1 file changed, 26 insertions(+), 41 deletions(-)
```
#### [PATCH 0/5] vfio/iommu_type1: Some fixes about dirty tracking
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Jan  7 09:28:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12003325
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFED0C433DB
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:30:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71AB42333F
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:30:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727155AbhAGJaM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 04:30:12 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:9971 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726607AbhAGJaL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 04:30:11 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DBLWw1P3dzj3Vw;
        Thu,  7 Jan 2021 17:28:44 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Thu, 7 Jan 2021 17:29:20 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        "Daniel Lezcano" <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH 0/5] vfio/iommu_type1: Some fixes about dirty tracking
Date: Thu, 7 Jan 2021 17:28:56 +0800
Message-ID: <20210107092901.19712-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

In patch series[1], I put forward some fixes and optimizations for
vfio_iommu_type1. This extracts and improves the fix part of it.

[1] https://lore.kernel.org/linux-iommu/20201210073425.25960-1-zhukeqian1@huawei.com/T/#t

Thanks,
Keqian

Keqian Zhu (5):
  vfio/iommu_type1: Fixes vfio_dma_populate_bitmap to avoid dirty lose
  vfio/iommu_type1: Populate dirty bitmap for new vfio_dma
  vfio/iommu_type1: Populate dirty bitmap when attach group
  vfio/iommu_type1: Carefully use unmap_unpin_all during dirty tracking
  vfio/iommu_type1: Move sanity_check_pfn_list to unmap_unpin_all

 drivers/vfio/vfio_iommu_type1.c | 107 +++++++++++++++++++++-----------
 1 file changed, 72 insertions(+), 35 deletions(-)
```
#### [PATCH v2 0/4] KVM: nSVM: few random fixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Jan  7 09:38:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12003355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 334ECC433E0
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:40:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F3A342333F
	for <kvm@archiver.kernel.org>; Thu,  7 Jan 2021 09:40:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727162AbhAGJkg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 04:40:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:44679 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725974AbhAGJkg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 Jan 2021 04:40:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610012349;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=0/UvIsE6v1FZ8l1jZ7AnILfXjsl6XgnZoeG7pEBoAX4=;
        b=UswIR7I3sqB3XTAOwxGLgnQiQKoS0jwtpuuz5jb4BnowznAXJhcj4IvLW2mSVOMoIGUNxI
        b1HgfR8lgiS8ZrF9u/UArC5rvXJJGTns+7FN5dvc7UDJjndoubbz/iG2eL+T04R0bRdqja
        pflpRpigdaaPVpHgbGdQEcSyKfr6t1Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-497-34FcIbIPMUOnL2sw4IGfiQ-1; Thu, 07 Jan 2021 04:39:06 -0500
X-MC-Unique: 34FcIbIPMUOnL2sw4IGfiQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 33CD9AFA80;
        Thu,  7 Jan 2021 09:39:04 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3966219D7D;
        Thu,  7 Jan 2021 09:38:55 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/4] KVM: nSVM: few random fixes
Date: Thu,  7 Jan 2021 11:38:50 +0200
Message-Id: <20210107093854.882483-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a series of fixes to nested SVM, that finally makes my kvm on kvm
stress test pass, and fix various other issues/regressions.

Patch 1 is a fix for recent regression related to code that delayed the nested
msr bitmap processing to the next vm entry, and started to crash the L1 after
my on demand nested state allocation patches.

The problem was that the code assumed that we will still be in the nested
guest mode on next vmentry after setting the nested state, but a pending event
can cause a nested vmexit prior to that.

Patch 2 makes KVM restore nested_run_pending flag on migration which fixes
various issues including potentially missed L1->L2 event injection
if migration happens while nested run is pending.

Patches 3,4 are few things I found while reviewing the nested migration code.
I don't have a reproducer for them.

Thanks a lot to Sean Christopherson for the review feedback on V1 of this
series, which is fully incorporated in this series.

Best regards,
	Maxim Levitsky

Maxim Levitsky (4):
  KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit
  KVM: nSVM: correctly restore nested_run_pending on migration
  KVM: nSVM: always leave the nested state first on KVM_SET_NESTED_STATE
  KVM: nSVM: mark vmcb as dirty when forcingly leaving the guest mode

 arch/x86/kvm/svm/nested.c | 12 ++++++++++++
 1 file changed, 12 insertions(+)
```
