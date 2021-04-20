#### [PATCH 1/2] KVM: x86/mmu: Wrap kvm_mmu_zap_all_fast TDP MMU code in ifdefs
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12212503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F2F5C433B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 18:37:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16E5761246
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 18:37:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241110AbhDSSiS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 14:38:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44986 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233002AbhDSSiR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Apr 2021 14:38:17 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A9FE0C06174A
        for <kvm@vger.kernel.org>; Mon, 19 Apr 2021 11:37:47 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id
 n7-20020a05620a2227b02902e3b6e9f887so2995210qkh.21
        for <kvm@vger.kernel.org>; Mon, 19 Apr 2021 11:37:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=+WY+blaIG7SHWZsjIU6gf30zUSW6OFhHYfMLmJiOTIs=;
        b=lsaPWWp1HFN4HCc1Ki750iUCiKMu3i+HX2sMUuf2qrhjuP56qdk34JuXrUNZ1jpTF+
         R+++3NN7WPymLlKHgr4F1arFPTZnetmeKoOZ5vv/d9K6C+C6rKcy7Mikrxu7chMS1cwg
         6SN7itDpaPomRZlF7UAGC6GOUQMCdddKiFpppxnJDfZsclcUtzdwfNOlTljqxFj+LRYE
         21Xil4UhrubR1HKWmGwBArPHPaNmssgE280bDJzSmzvhFvHzljjfkHCLUocc2r0emMbf
         ZZmYp0gJLLBO8Ww13k9UigPUDzQPSQyVQu6QDTj7tdP8GRlSWDsNk7VRoYON7c1NZQ02
         qrsw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=+WY+blaIG7SHWZsjIU6gf30zUSW6OFhHYfMLmJiOTIs=;
        b=YW97P8IFKJoMnhGud/hxeXseQJWek6sTRJZRlxz3Obl4dRrO1X/QsLoHrmONGFhHcX
         VfJYWGZtRbr5uqokgMvyY8mtmiQdAeRLmetiKVXu0udVMwnXlIQKuyMjh4hYRizI5yHW
         wZwlz04fBchs+qXYrZzwAWHJUVdjNlcvIE4Cfm2sujZS7Rhx6P1flDLCw4dfcejNGIZ4
         xA/V5Mr9aTI7HzctzhBTLf9TKaDl+zL2UVFohY7YIgwyGEnw//7V/z8FMZAx97lLKA7u
         6SqstxBIL2Ac0Hdd0NYbWR9BHumjR7QSs+E5WOHO0dy7ZtAQFt5/wSpFlbW0F+5Zc/D2
         S0dw==
X-Gm-Message-State: AOAM531xIVq57D/GgEmAHb0j9JlmYRrR/rJYFjsyoSFkpyZbhJVMpTAu
        N9XSsF51ztD/bPRR57xy9lmPojkp0XUo
X-Google-Smtp-Source: 
 ABdhPJyRmGq41hMP+eyXKSvMD7OtpBBDqs4Owh6WeIPOsPRLBMsNDfXvDtbkUXPv9fHrBPu5VU85136eSOYG
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:8c52:76ef:67d7:24b1])
 (user=bgardon job=sendgmr) by 2002:a0c:f744:: with SMTP id
 e4mr23222467qvo.5.1618857466814; Mon, 19 Apr 2021 11:37:46 -0700 (PDT)
Date: Mon, 19 Apr 2021 11:37:41 -0700
Message-Id: <20210419183742.901647-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH 1/2] KVM: x86/mmu: Wrap kvm_mmu_zap_all_fast TDP MMU code in
 ifdefs
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Robert Hu <robert.hu@intel.com>,
        Farrah Chen <farrah.chen@intel.com>,
        Danmei Wei <danmei.wei@intel.com>,
        Ben Gardon <bgardon@google.com>,
        kernel test robot <lkp@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TDP MMU code in kvm_mmu_zap_all_fast is only needed with
CONFIG_X86_64 and creates a build error without that setting. Since the
TDP MMU can only be enabled with CONFIG_X86_64, wrap those code blocks
in ifdefs.

Fixes: 1336c692abad ("KVM: x86/mmu: Fast invalidation for TDP MMU")

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH fixed] KVM: x86/mmu: Fast invalidation for TDP MMU
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12212771
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A17BCC433ED
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 22:04:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83B92613B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 22:04:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240782AbhDSWFS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 18:05:18 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:20350 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229683AbhDSWFS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 19 Apr 2021 18:05:18 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618869887;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=V9TpAWTBookZJPskzjveTp1z8A/eSlwxzMp8BsONQuM=;
        b=YUMeyJzotH61wDzJR6dhKsd7tW38vuH6ibXAnT1GKKLdQyocktye62ElHm3qi1+EW+NBux
        UuGAtE6Txc8LYDGEgctqhbef9KRjRxlySxGiS/dECN1zfpp3mWeDiybI0qNHbkelIg8c5P
        IHJIsYeXVcIpktBRSYmaw2VlZOTCylk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-153-NHFpKugXOCePt0TeBuQHBA-1; Mon, 19 Apr 2021 18:04:45 -0400
X-MC-Unique: NHFpKugXOCePt0TeBuQHBA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 94C5C1006C98;
        Mon, 19 Apr 2021 22:04:44 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3FFDA60C5C;
        Mon, 19 Apr 2021 22:04:44 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bgardon@google.com
Subject: [PATCH fixed] KVM: x86/mmu: Fast invalidation for TDP MMU
Date: Mon, 19 Apr 2021 18:04:43 -0400
Message-Id: <20210419220443.673911-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ben Gardon <bgardon@google.com>

Provide a real mechanism for fast invalidation by marking roots as
invalid so that their reference count will quickly fall to zero
and they will be torn down.

One negative side affect of this approach is that a vCPU thread will
likely drop the last reference to a root and be saddled with the work of
tearing down an entire paging structure. This issue will be resolved in
a later commit.

Signed-off-by: Ben Gardon <bgardon@google.com>
Message-Id: <20210401233736.638171-13-bgardon@google.com>
[Move the loop to tdp_mmu.c, otherwise compilation fails on 32-bit. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c     | 12 +++++++++---
 arch/x86/kvm/mmu/tdp_mmu.c | 17 +++++++++++++++++
 arch/x86/kvm/mmu/tdp_mmu.h |  5 +++++
 3 files changed, 31 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: selftests: Tweak time measurement flag in kvm_page_table_test
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12211407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CE321C433B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 10:50:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6BDD6101E
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 10:50:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232344AbhDSKub (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 06:50:31 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:17359 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231387AbhDSKua (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Apr 2021 06:50:30 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4FP3Rs3wJ0zBrRp;
        Mon, 19 Apr 2021 18:47:37 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.498.0; Mon, 19 Apr 2021 18:49:50 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH] KVM: selftests: Tweak time measurement flag in
 kvm_page_table_test
Date: Mon, 19 Apr 2021 18:49:47 +0800
Message-ID: <20210419104947.38544-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Also use CLOCK_MONOTONIC flag to get time in kvm_page_table_test.c,
since that's what all the kvm/selftests do currently. And this will
be consistent with function timespec_elapsed() in test_util.c.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 tools/testing/selftests/kvm/kvm_page_table_test.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH 01/30] asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED definition
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12212207
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D5114C433B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 16:01:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B3B2661285
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 16:01:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241935AbhDSQCN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 12:02:13 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49690 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241834AbhDSQCJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 19 Apr 2021 12:02:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618848098;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=PZ+0zhcDTaFwmCG/kAMsvBi4hL3KOk4LUgO56AJbCrk=;
        b=UsJwH+R+iblPN1zKvqWOWZV0xBkeuCLhd1+tUVBHaMnu6DDjWUcNfrJi2NDshtHznS7CL6
        xVz0ZSkKfc+PvAVOf+pCWgKLHqUdC1sYF8T1PGjdur1XetCA0YMy+G6VhQnUFtuSOQaVoa
        n9pDNfrYSgtO7KKNYKJMM/NSFleBOP0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-127-dt5EbmZ_Ote49UPo9_YSig-1; Mon, 19 Apr 2021 12:01:36 -0400
X-MC-Unique: dt5EbmZ_Ote49UPo9_YSig-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CCFE06D4E6;
        Mon, 19 Apr 2021 16:01:33 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D541C2C167;
        Mon, 19 Apr 2021 16:01:31 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Siddharth Chandrasekaran <sidcha@amazon.de>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/30] asm-generic/hyperv: add HV_STATUS_ACCESS_DENIED
 definition
Date: Mon, 19 Apr 2021 18:00:58 +0200
Message-Id: <20210419160127.192712-2-vkuznets@redhat.com>
In-Reply-To: <20210419160127.192712-1-vkuznets@redhat.com>
References: <20210419160127.192712-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From TLFSv6.0b, this status means: "The caller did not possess sufficient
access rights to perform the requested operation."

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Wei Liu <wei.liu@kernel.org>
---
 include/asm-generic/hyperv-tlfs.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH V4 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12210885
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F1B19C433B4
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 06:38:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D668760FDB
	for <kvm@archiver.kernel.org>; Mon, 19 Apr 2021 06:38:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232942AbhDSGjZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Apr 2021 02:39:25 -0400
Received: from mga12.intel.com ([192.55.52.136]:32762 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229630AbhDSGjY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Apr 2021 02:39:24 -0400
IronPort-SDR: 
 oVT9q37GsCqzuPPb+kzTNPvUNw0gm3uPWLZaRwtqIFeCPLaI/s65gueBCenRX6J+/3becEebaQ
 4rgyjyRdUkZA==
X-IronPort-AV: E=McAfee;i="6200,9189,9958"; a="174766096"
X-IronPort-AV: E=Sophos;i="5.82,233,1613462400";
   d="scan'208";a="174766096"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Apr 2021 23:38:55 -0700
IronPort-SDR: 
 yqwS8lMV8URXbMYC3Wo7Ip/2IbOv/etlP1Gpu+7MnKiv92pdiLbBRT/EUY9FB+FHNN/UD+a5EB
 uP8btBrpMx/A==
X-IronPort-AV: E=Sophos;i="5.82,233,1613462400";
   d="scan'208";a="523328535"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Apr 2021 23:38:53 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
Date: Mon, 19 Apr 2021 14:33:24 +0800
Message-Id: <20210419063326.3748-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210419063326.3748-1-lingshan.zhu@intel.com>
References: <20210419063326.3748-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit deduces VIRTIO device ID as device type when probe,
then ifcvf_vdpa_get_device_id() can simply return the ID.
ifcvf_vdpa_get_features() and ifcvf_vdpa_get_config_size()
can work properly based on the device ID.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.h |  1 +
 drivers/vdpa/ifcvf/ifcvf_main.c | 27 +++++++++++++++------------
 2 files changed, 16 insertions(+), 12 deletions(-)

```
