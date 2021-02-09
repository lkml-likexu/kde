#### [RFC PATCH 1/2] KVM: selftests: Add a macro to get string of vm_mem_backing_src_type
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12074495
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AB328C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:12:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5BA9464E7A
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:12:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231445AbhBHJM0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 04:12:26 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:12488 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230484AbhBHJJu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 04:09:50 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DZ0Xf2sm8zjL4s;
        Mon,  8 Feb 2021 17:07:30 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Mon, 8 Feb 2021 17:08:45 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        "Andrew Jones" <drjones@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ben Gardon <bgardon@google.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH 1/2] KVM: selftests: Add a macro to get string of
 vm_mem_backing_src_type
Date: Mon, 8 Feb 2021 17:08:40 +0800
Message-ID: <20210208090841.333724-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210208090841.333724-1-wangyanan55@huawei.com>
References: <20210208090841.333724-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a macro to get string of the backing source memory type, so that
application can add choices for source types in the help() function,
and users can specify which type to use for testing.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 tools/testing/selftests/kvm/include/kvm_util.h | 3 +++
 tools/testing/selftests/kvm/lib/kvm_util.c     | 8 ++++++++
 2 files changed, 11 insertions(+)

```
#### [PATCH] drm/i915/gvt/kvmgt: Fix the build failure in kvmgt.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yu Zhang <yu.c.zhang@linux.intel.com>
X-Patchwork-Id: 12075115
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D31D4C4332B
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:15:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EB1464E37
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:15:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232929AbhBHLOz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 06:14:55 -0500
Received: from mga03.intel.com ([134.134.136.65]:51226 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232902AbhBHLMu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 06:12:50 -0500
IronPort-SDR: 
 cYFfbF7VRHtIBDypg/2E+s2fYln3If/hP8+ufgskeXVObsy4rUD8GULEHdDoa29Qp4EG+niYEw
 LxSuglM/gcGQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9888"; a="181760489"
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="181760489"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 03:11:00 -0800
IronPort-SDR: 
 tQPxxlIxpgU2syF+t+y9/8vgr96RxgVSdqB1ryYM3UPrbvR2D4MYql2e8nyZDkEvcykN4FKdS0
 hOIBPdZZ0vHg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="395345985"
Received: from zhangyu-optiplex-7040.bj.intel.com ([10.238.154.148])
  by orsmga008.jf.intel.com with ESMTP; 08 Feb 2021 03:10:56 -0800
From: Yu Zhang <yu.c.zhang@linux.intel.com>
To: zhenyuw@linux.intel.com, zhi.a.wang@intel.com
Cc: jani.nikula@linux.intel.com, joonas.lahtinen@linux.intel.com,
        rodrigo.vivi@intel.com, airlied@linux.ie, daniel@ffwll.ch,
        intel-gvt-dev@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org, dri-devel@lists.freedesktop.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] drm/i915/gvt/kvmgt: Fix the build failure in kvmgt.
Date: Tue,  9 Feb 2021 02:52:10 +0800
Message-Id: <20210208185210.6002-1-yu.c.zhang@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, commit 531810caa9f4 ("KVM: x86/mmu: Use
an rwlock for the x86 MMU") replaced KVM's mmu_lock
with type rwlock_t. This will cause a build failure
in kvmgt, which uses the same lock when trying to add/
remove some GFNs to/from the page tracker. Fix it with
write_lock/unlocks in kvmgt.

Reported-by: Stephen Rothwell <sfr@canb.auug.org.au>
Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
---
 drivers/gpu/drm/i915/gvt/kvmgt.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH for 4.19] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Peter Gonda <pgonda@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 12076033
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 913FDC433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 16:51:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37B4164E8F
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 16:51:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234562AbhBHQut (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 11:50:49 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44664 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234681AbhBHQtZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 11:49:25 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C83CFC06178C
        for <kvm@vger.kernel.org>; Mon,  8 Feb 2021 08:48:44 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id z10so10944256pfa.1
        for <kvm@vger.kernel.org>; Mon, 08 Feb 2021 08:48:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=CWLS3iCdl7avu6UrS/4a9Q7lCozs1sxuZ+Q+3TdBAr4=;
        b=MkS/AQpsy4KJi2RAXDyDVdKnFaGcb8SW96N1xaxNIG/R8e6YcwlBQ9vh0t51rhuofi
         i2vBYteTnMD+u7upnr9YfcoJu3W8ZaYEvYWAQArs9ud8ocrYGqh9b6UKHfUE0aTX2nd+
         X7EQW1I5ERB5Wy2/NAVTjwKHNbol9Y4O97ag3nwYL6j0+jshBjpP0zCchaUV1eomWmUm
         gU1ntF6fsqDAWh40hku88WgSOyoCs6I8fVL/b22dS+pJLvCZ9gVrCi5QEWlnU2rpV7Hk
         yDcUZ0z49g+Fy7AdPfB8khbpopSxyhugyzcqDYjYRFCRfOSB3i2a3ZzHLoQinzIaMpVG
         n3zA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=CWLS3iCdl7avu6UrS/4a9Q7lCozs1sxuZ+Q+3TdBAr4=;
        b=kxY4SFw1qupP4vwErba5Q+dMe65lCQ7kcskWf8jeEnNv20Se7km7u86jCFvb9UI32m
         j+u1swR+P7h1aqoMOr9THDsrfk2kZUShOnwStrfxOGxtXLsN+aKWv+NrADxq1Ww2gjq9
         VKnRmZMeQ0MHWK9BaesZHQ3XF6UlujIbPjF51vZ0dKUxaTu0FrBHkM3K0G6ThuZFCMaR
         2fEMIDe7ioVSRQgCYBpztSV0ErtnEj6O6a2X68bnXmOwbOIzaKTj+yFTo1+oheHLj2Jm
         OwoM67dlO/hYeA3PpSQJDRzALkXU9l+ijuB5MrX2Lfhs7N7ZjDDBpwRwLFuXFqv5xGAK
         k0/A==
X-Gm-Message-State: AOAM532tbYCP2UDZ6AXjlUjPCa+fWVEKMwTy6apOIpp9pIsJ74IRhV+r
        TsC3EBGKKGIQ8ppZikxhBLqk1sc9nP4=
X-Google-Smtp-Source: 
 ABdhPJzsbIldQf/8UDs4hDwDDcUOVrtcG212tLSgbSxhCz6lTXYVMBAf80R68i/GgR8Gx2bdiBy8lRKlNSg=
Sender: "pgonda via sendgmr" <pgonda@pgonda1.kir.corp.google.com>
X-Received: from pgonda1.kir.corp.google.com
 ([2620:0:1008:11:588:a801:402d:d5e5])
 (user=pgonda job=sendgmr) by 2002:a17:902:9009:b029:dc:52a6:575 with SMTP id
 a9-20020a1709029009b02900dc52a60575mr16415595plp.57.1612802924247; Mon, 08
 Feb 2021 08:48:44 -0800 (PST)
Date: Mon,  8 Feb 2021 08:48:40 -0800
Message-Id: <20210208164840.769333-1-pgonda@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH for 4.19] Fix unsynchronized access to sev members through
 svm_register_enc_region
From: Peter Gonda <pgonda@google.com>
To: stable@vger.kernel.org
Cc: Peter Gonda <pgonda@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 19a23da53932bc8011220bd8c410cb76012de004 upstream.

Grab kvm->lock before pinning memory when registering an encrypted
region; sev_pin_memory() relies on kvm->lock being held to ensure
correctness when checking and updating the number of pinned pages.

Add a lockdep assertion to help prevent future regressions.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 1e80fdc09d12 ("KVM: SVM: Pin guest memory when SEV is active")
Signed-off-by: Peter Gonda <pgonda@google.com>

V2
 - Fix up patch description
 - Correct file paths svm.c -> sev.c
 - Add unlock of kvm->lock on sev_pin_memory error

V1
 - https://lore.kernel.org/kvm/20210126185431.1824530-1-pgonda@google.com/

Message-Id: <20210127161524.2832400-1-pgonda@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 18 +++++++++++-------
 1 file changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH for 5.4] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Peter Gonda <pgonda@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 12076035
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA7DDC433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 16:51:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9C96B64E8F
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 16:51:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234610AbhBHQvI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 11:51:08 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44780 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234687AbhBHQt4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 11:49:56 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F1381C061794
        for <kvm@vger.kernel.org>; Mon,  8 Feb 2021 08:48:57 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id f6so11004475pfn.6
        for <kvm@vger.kernel.org>; Mon, 08 Feb 2021 08:48:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=CWLS3iCdl7avu6UrS/4a9Q7lCozs1sxuZ+Q+3TdBAr4=;
        b=h63zsE4ezN6OCZsuKkcFUpv5B4yvCpCVEuK32I4ib8AUnfahsxf/fPZ7KtlM2O2YHt
         CwUiwX5vUz6lb6ueS7j8/BzB78EcrGvf/HcN0Ikw0iq2ZVYCL2r3jcA5bQpSHTMMR/+z
         EEC12b0bfkYfdrIukt/4St/vkL5K29wqi12l6LG+6hlfmgOrh746Z66PUmosCqxtc1Hp
         fPE+JPm7qf6VJTJawhgpdyHKuWC0NPZzTKy14W2hWLuP8SEJd99gD6LUbIhZjI9wiKul
         NCl+xxl3SMvFn16Iv7jxa9dIoBj5F9457+1yRY/GfRdfjUfA4Ukg7NWoP+QMjNWJBGWg
         mcYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=CWLS3iCdl7avu6UrS/4a9Q7lCozs1sxuZ+Q+3TdBAr4=;
        b=lsFKPiiDYuvt+MRsizzS5Twf/WicEGR3XnNcsEc2QnGt+r1FkJY/WJzHrsWqOVgWMf
         rgYb9MfTXIHAuZrCRo3yzFiOx7rmHBFeCYYDA6u1VzDLHN53c21gOe43Dq8oxgr/ewjD
         FGhDYED4h5YIK710ZSYPqRs9OSewQgnnlWuv2MEpGMaYw115IhrnLWHMjdZfLRvv+lct
         N+zO8uu6PyoJE/vzcllM9sNohJ84BMDZ6IOafocQoOfS459Q+sZ3rq+3pNYDfV5rcwGA
         jKUTr8mBL9MfMYylRYLqMlbCnNbbKPY/zDDRoDMTevAi1CdrOP9W7DZhIl3+uSm9z6xP
         6phQ==
X-Gm-Message-State: AOAM530X6YgZqN+MSRvGFfM4u5N0sY3ITV8aZZdWLCyIW53kn+VDEUIQ
        sI+KluG+h22YZOMxQLjkJB3IRm2vDLA=
X-Google-Smtp-Source: 
 ABdhPJyrMNiN0ra//SFWELFPtCPbNLOL3F1BSTGyIONMn9Zwnqqz5JsBarlztfEaJUc/8S4FKFvEAwb7Iys=
Sender: "pgonda via sendgmr" <pgonda@pgonda1.kir.corp.google.com>
X-Received: from pgonda1.kir.corp.google.com
 ([2620:0:1008:11:588:a801:402d:d5e5])
 (user=pgonda job=sendgmr) by 2002:aa7:91cf:0:b029:1cb:1c6f:b77d with SMTP id
 z15-20020aa791cf0000b02901cb1c6fb77dmr18651925pfa.74.1612802937434; Mon, 08
 Feb 2021 08:48:57 -0800 (PST)
Date: Mon,  8 Feb 2021 08:48:55 -0800
Message-Id: <20210208164855.772287-1-pgonda@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH for 5.4] Fix unsynchronized access to sev members through
 svm_register_enc_region
From: Peter Gonda <pgonda@google.com>
To: stable@vger.kernel.org
Cc: Peter Gonda <pgonda@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 19a23da53932bc8011220bd8c410cb76012de004 upstream.

Grab kvm->lock before pinning memory when registering an encrypted
region; sev_pin_memory() relies on kvm->lock being held to ensure
correctness when checking and updating the number of pinned pages.

Add a lockdep assertion to help prevent future regressions.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 1e80fdc09d12 ("KVM: SVM: Pin guest memory when SEV is active")
Signed-off-by: Peter Gonda <pgonda@google.com>

V2
 - Fix up patch description
 - Correct file paths svm.c -> sev.c
 - Add unlock of kvm->lock on sev_pin_memory error

V1
 - https://lore.kernel.org/kvm/20210126185431.1824530-1-pgonda@google.com/

Message-Id: <20210127161524.2832400-1-pgonda@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 18 +++++++++++-------
 1 file changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH 5.10 077/120] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
X-Patchwork-Id: 12075929
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D62C0C433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 15:29:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9565A64E56
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 15:29:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231809AbhBHP3g (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 10:29:36 -0500
Received: from mail.kernel.org ([198.145.29.99]:36948 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233450AbhBHP1F (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 10:27:05 -0500
Received: by mail.kernel.org (Postfix) with ESMTPSA id D412964F1D;
        Mon,  8 Feb 2021 15:15:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=linuxfoundation.org;
        s=korg; t=1612797343;
        bh=Z3NwpbMc3+FIymIKdL8oJDqLuu31Dr0homPLMdONXjA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=WvMpiH69yDeoHwNFKuJuh/o+eXxNenyXbA0UxBt6ZCH6GyAvZTwks4HmGpSynPSbK
         +1TkT5YRpu53+gvUGGw2RuvkzQzHM9UV8m0vIdumI8MR8QhBqV6ThlTw/pCHwwJuVj
         bbYsvyKd/JiBz6jIVx6ZJTJalrv7qFScGi99wdmA=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        stable@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        kvm@vger.kernel.org, Peter Gonda <pgonda@google.com>
Subject: [PATCH 5.10 077/120] Fix unsynchronized access to sev members through
 svm_register_enc_region
Date: Mon,  8 Feb 2021 16:01:04 +0100
Message-Id: <20210208145821.479412648@linuxfoundation.org>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210208145818.395353822@linuxfoundation.org>
References: <20210208145818.395353822@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Gonda <pgonda@google.com>

commit 19a23da53932bc8011220bd8c410cb76012de004 upstream.

Grab kvm->lock before pinning memory when registering an encrypted
region; sev_pin_memory() relies on kvm->lock being held to ensure
correctness when checking and updating the number of pinned pages.

Add a lockdep assertion to help prevent future regressions.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 1e80fdc09d12 ("KVM: SVM: Pin guest memory when SEV is active")
Signed-off-by: Peter Gonda <pgonda@google.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

V2
 - Fix up patch description
 - Correct file paths svm.c -> sev.c
 - Add unlock of kvm->lock on sev_pin_memory error

V1
 - https://lore.kernel.org/kvm/20210126185431.1824530-1-pgonda@google.com/

Message-Id: <20210127161524.2832400-1-pgonda@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/sev.c |   17 ++++++++++-------
```
#### [PATCH v18 1/7] arm/arm64: Probe for the presence of KVM hypervisor
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12075417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 54B57C433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 13:41:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FE966186A
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 13:41:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229720AbhBHNlc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 08:41:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:59036 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229706AbhBHNlR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 08:41:17 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 07DAF64DE9;
        Mon,  8 Feb 2021 13:40:36 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l96mI-00Cn0C-6K; Mon, 08 Feb 2021 13:40:34 +0000
From: Marc Zyngier <maz@kernel.org>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com, seanjc@google.com,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com, lorenzo.pieralisi@arm.com,
        sudeep.holla@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        kernel-team@android.com
Subject: [PATCH v18 1/7] arm/arm64: Probe for the presence of KVM hypervisor
Date: Mon,  8 Feb 2021 13:40:23 +0000
Message-Id: <20210208134029.3269384-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210208134029.3269384-1-maz@kernel.org>
References: <20210208134029.3269384-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: netdev@vger.kernel.org, yangbo.lu@nxp.com,
 john.stultz@linaro.org, tglx@linutronix.de, pbonzini@redhat.com,
 seanjc@google.com, richardcochran@gmail.com, Mark.Rutland@arm.com,
 will@kernel.org, suzuki.poulose@arm.com, Andre.Przywara@arm.com,
 steven.price@arm.com, lorenzo.pieralisi@arm.com, sudeep.holla@arm.com,
 linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, Steve.Capper@arm.com,
 justin.he@arm.com, jianyong.wu@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

Although the SMCCC specification provides some limited functionality for
describing the presence of hypervisor and firmware services, this is
generally applicable only to functions designated as "Arm Architecture
Service Functions" and no portable discovery mechanism is provided for
standard hypervisor services, despite having a designated range of
function identifiers reserved by the specification.

In an attempt to avoid the need for additional firmware changes every
time a new function is added, introduce a UID to identify the service
provider as being compatible with KVM. Once this has been established,
additional services can be discovered via a feature bitmap.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
[maz: move code to its own file, plug it into PSCI]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201209060932.212364-2-jianyong.wu@arm.com
---
 arch/arm/include/asm/hypervisor.h   |  3 ++
 arch/arm64/include/asm/hypervisor.h |  3 ++
 drivers/firmware/psci/psci.c        |  2 ++
 drivers/firmware/smccc/Makefile     |  2 +-
 drivers/firmware/smccc/kvm_guest.c  | 50 +++++++++++++++++++++++++++++
 drivers/firmware/smccc/smccc.c      |  1 +
 include/linux/arm-smccc.h           | 25 +++++++++++++++
 7 files changed, 85 insertions(+), 1 deletion(-)
 create mode 100644 drivers/firmware/smccc/kvm_guest.c

```
#### [RFC PATCH 1/4] KVM: arm64: Move the clean of dcache to the map handler
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12075149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7296AC433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:29:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1E16B64E30
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:29:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232969AbhBHL2l (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 06:28:41 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:12462 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233043AbhBHLXo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 06:23:44 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DZ3Wj6nB9zjK1c;
        Mon,  8 Feb 2021 19:21:53 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.498.0; Mon, 8 Feb 2021 19:22:53 +0800
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
Subject: [RFC PATCH 1/4] KVM: arm64: Move the clean of dcache to the map
 handler
Date: Mon, 8 Feb 2021 19:22:47 +0800
Message-ID: <20210208112250.163568-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210208112250.163568-1-wangyanan55@huawei.com>
References: <20210208112250.163568-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently uniformly clean dcache in user_mem_abort() before calling the
fault handlers, if we take a translation fault and the pfn is cacheable.
But if there are concurrent translation faults on the same page or block,
clean of dcache for the first time is necessary while the others are not.

By moving clean of dcache to the map handler, we can easily identify the
conditions where CMOs are really needed and avoid the unnecessary ones.
As it's a time consuming process to perform CMOs especially when flushing
a block range, so this solution reduces much load of kvm and improve the
efficiency of creating mappings.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 16 --------------
 arch/arm64/kvm/hyp/pgtable.c     | 38 ++++++++++++++++++++------------
 arch/arm64/kvm/mmu.c             | 14 +++---------
 3 files changed, 27 insertions(+), 41 deletions(-)

```
#### [RFC PATCH v4 01/26] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12074985
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1DCD2C43381
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 10:59:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C89A364E88
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 10:59:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232532AbhBHK7L (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 05:59:11 -0500
Received: from mga12.intel.com ([192.55.52.136]:12406 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229482AbhBHKzR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 05:55:17 -0500
IronPort-SDR: 
 J0bpbQlWSWxl/VDO8hhQt1qHbz/258o6W5t3ue5fUvBRg7HSxKAmEFrrmACdpgs6jEBsEqdlmI
 rC8gdEM/h6Jw==
X-IronPort-AV: E=McAfee;i="6000,8403,9888"; a="160848436"
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="160848436"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 02:54:26 -0800
IronPort-SDR: 
 orGDpGs+hGtjow9s1rUhvWUjBnI+3rAOYL5ZrOH1AIEcI7FSywQoKSB3RU8xEr2sAaNqS2921+
 DLR9WESVnuYA==
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="374450953"
Received: from jaeminha-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.11.62])
  by orsmga002-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 02:54:23 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH v4 01/26] x86/cpufeatures: Make SGX_LC feature bit depend
 on SGX bit
Date: Mon,  8 Feb 2021 23:54:05 +1300
Message-Id: 
 <8e6a1963b3666215223c247193e5a3e09a8c3698.1612777752.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1612777752.git.kai.huang@intel.com>
References: <cover.1612777752.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---

Hi Jarkko, Dave,

I had your Acked-by in v3. Jarkko said this patch should be before the patch
which introduced SGX1/SGX2 bit, since it is improvement of existing code, so I
switched the order. I assumed I can still have your Acked-by because code change
was just due to patch re-ordering.

v3->v4:

 - Changed patch order with the patch that introduced new SGX1/SGX2 bits, since
   it is improvement of existing code, per Jarkko.
---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] gitlab-ci.yml: Add new s390x targets to run tests with TCG and KVM accel
##### From: Marcelo Bandeira Condotta <mbandeir@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Bandeira Condotta <mbandeir@redhat.com>
X-Patchwork-Id: 12075815
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 78D04C43381
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 15:05:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3707B64EC9
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 15:05:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231961AbhBHPFk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 10:05:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32783 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232363AbhBHPEQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Feb 2021 10:04:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612796557;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=U4vE6QO9gJ7FHiO0oK3chDBjSo4heyDGI9neiMKhD6U=;
        b=QkeUgdFzg8sNhWR02rnc3KqzlerqLOZ1mW/r6VAOzIm+dV4kadqPxJIWei8806G0iAG3f+
        IUmLEFiS/lBWdSyad2wxJunidsy6qMlkmSHn6IGZxhAAfmswCeIhEgaxVVeKOeVf6Azr98
        cF/rDQ9/ILBNOkIUSGPsjSt3me6FjaE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-37-p9TqOEBLPSK4Az4vTLNDVw-1; Mon, 08 Feb 2021 10:02:34 -0500
X-MC-Unique: p9TqOEBLPSK4Az4vTLNDVw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9FDA18030CD
        for <kvm@vger.kernel.org>; Mon,  8 Feb 2021 15:02:33 +0000 (UTC)
Received: from mbandeir.redhat.com (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 37E825D9E4;
        Mon,  8 Feb 2021 15:02:28 +0000 (UTC)
From: Marcelo Bandeira Condotta <mbandeir@redhat.com>
To: pbonzini@redhat.com, thuth@redhat.com, kvm@vger.kernel.org
Cc: Marcelo Bandeira Condotta <mcondotta@redhat.com>
Subject: [kvm-unit-tests PATCH] gitlab-ci.yml: Add new s390x targets to run
 tests with TCG and KVM accel
Date: Mon,  8 Feb 2021 12:02:27 -0300
Message-Id: <20210208150227.178953-1-mbandeir@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marcelo Bandeira Condotta <mcondotta@redhat.com>

A new s390x z15 VM provided by IBM Community Cloud will be used to run
the s390x KVM Unit tests natively with both TCG and KVM accel options.

Signed-off-by: Marcelo Bandeira Condotta <mbandeir@redhat.com>
Acked-by: Thomas Huth <thuth@redhat.com>
---
 .gitlab-ci.yml | 28 ++++++++++++++++++++++++++++
 1 file changed, 28 insertions(+)

```
#### [PATCH] KVM: Use kvm_pfn_t for local PFN variable in hva_to_pfn_remapped()
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12076475
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C788C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 20:21:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB52664E59
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 20:21:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236766AbhBHUVU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 15:21:20 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33678 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236716AbhBHUU0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 15:20:26 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 65DCCC06178A
        for <kvm@vger.kernel.org>; Mon,  8 Feb 2021 12:19:44 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id dr7so120217qvb.22
        for <kvm@vger.kernel.org>; Mon, 08 Feb 2021 12:19:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=c92WD9tBjIN6OOgkPtPsSt2AYdNEujBjskOjMLRrrjI=;
        b=wAql08sQVg8gABzEOZq6pnXO7zG/92jQFGKp6eugdemTbEjm4IL0/Lb+dByjT9sfhN
         bjrPlvAKbj0oKas5ZqV4PV56jUcAei5nYjw5vJr6mG5xdB4wZk/JcHuHUioTCwKRaSdH
         CJzxvvBlsaMq8ms4VQHX21CJcx+1rWOKfToT9ALVbjNAX97uhylRuuwIbn7USVcM6H/V
         u6YsQqV0rBFRXWoILzy3Q/BkgFUMRBdVjg9XmKfKKp7sJYhoeMXuLxY9l5LbdxwGv1I7
         EBzHC9tN987u4Q6Ixgn0WNBiw2/2BDxQI5v/Axz/egNhPcQU3LK2dUoaVTjSdEiOBElE
         9JzQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc:content-transfer-encoding;
        bh=c92WD9tBjIN6OOgkPtPsSt2AYdNEujBjskOjMLRrrjI=;
        b=RzvWSWajrSEmb81J0oW5iuuIgVHo7OMSj2ksAvv79IGh60dPtm2CMRbRzTVGEOuJlG
         Zn2IqJKVmB3QmJLG+Njz8J+1gLMohJy/MniUmF4N9JOb+x6/I4Pir0dcPZpTh7Ljj+mP
         w+K3yM9pM9IWTyMtmqCew4A4U1+ezTQt2gzEGxREe5U1wtlvbKTvXLV0bZuvj1+Ra3IS
         iC1rSFW/f0Rv0kiLa5aY9mFmgI7W7r8I7G1kZQsHqMOzX5NNN7aHSsec8LKhQDztoP6r
         8Aa36Pq211pasbcN+eexOPo5pbVP2tIwC02jBaL3LLX6biCIXRIydaCtEUSzaC7d0j8u
         +3UA==
X-Gm-Message-State: AOAM531QznqapCvfzaSBPb1+JqmLWsrqJwmNrf3bTwyX3uQ/4+rDy6K6
        nEca+1TQRyPpFwHYR11O8IT7AsAfQ60=
X-Google-Smtp-Source: 
 ABdhPJwD9shv2X/SfBHMf5rkLqrlBt/yFuFy7BTxCqki+QSLka36BUA4rdWxltPGE4NO9eUMY8h7zFBUa+M=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e4db:abc1:a5c0:9dbc])
 (user=seanjc job=sendgmr) by 2002:a05:6214:125:: with SMTP id
 w5mr17608903qvs.20.1612815583538; Mon, 08 Feb 2021 12:19:43 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon,  8 Feb 2021 12:19:40 -0800
Message-Id: <20210208201940.1258328-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] KVM: Use kvm_pfn_t for local PFN variable in
 hva_to_pfn_remapped()
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use kvm_pfn_t, a.k.a. u64, for the local 'pfn' variable when retrieving
a so called "remapped" hva/pfn pair.  In theory, the hva could resolve to
a pfn in high memory on a 32-bit kernel.

This bug was inadvertantly exposed by commit bd2fae8da794 ("KVM: do not
assume PTE is writable after follow_pfn"), which added an error PFN value
to the mix, causing gcc to comlain about overflowing the unsigned long.

  arch/x86/kvm/../../../virt/kvm/kvm_main.c: In function ‘hva_to_pfn_remapped’:
  include/linux/kvm_host.h:89:30: error: conversion from ‘long long unsigned int’
                                  to ‘long unsigned int’ changes value from
                                  ‘9218868437227405314’ to ‘2’ [-Werror=overflow]
   89 | #define KVM_PFN_ERR_RO_FAULT (KVM_PFN_ERR_MASK + 2)
      |                              ^
virt/kvm/kvm_main.c:1935:9: note: in expansion of macro ‘KVM_PFN_ERR_RO_FAULT’

Cc: stable@vger.kernel.org
Fixes: add6a0cd1c5b ("KVM: MMU: try to fix up page faults before giving up")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

I don't actually know that it's possible for a remapped pfn to be a 64-bit
value on a stock kernel.  But, backporting a one-liner is far easier and
safer than trying to audit all possible flows.  :-)

 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/xen: Use hva_t for holding hypercall page addressFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12076473
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 187C6C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 20:16:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAD0464E66
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 20:16:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235050AbhBHUQP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 15:16:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60914 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236724AbhBHUPq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 15:15:46 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C1D9BC06178B
        for <kvm@vger.kernel.org>; Mon,  8 Feb 2021 12:15:05 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id 203so18150184ybz.2
        for <kvm@vger.kernel.org>; Mon, 08 Feb 2021 12:15:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc
         :content-transfer-encoding;
        bh=mgnW8xfhzGkssYeGVKL8OKFJiT7oGpD36C+YLUEs9TA=;
        b=oigVJzIQtqcKIBZDm0qdX4NdpwQ6YShdcaV1o/xGRooB0gzajPVvjJq100lfrHrhcF
         T1pAdffB/uYeXuzx8TjxhlctRkOCQNo+TvMT+jo0Psl6fEIomkdO8xDPV0fPEsZIvwcw
         MtFM6u/CauFDs+hv3kFBxRW1JcJidoQhvvUvZyqMtHXLQsxtboN9ldAuWxgpZ8p/sa1v
         wifOxro9QPDE9Qp1SxByCmaBO9S5m64s4BiVREWoczYgOx82VXGfCixwlSytf/woCu4B
         Wm8J1QB9vurDXXZDL1VWdJvnw8vCkYkyBUUC0OQ3TimAOxjR/QZJV6m+PMKwU9pbFMmc
         edag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc:content-transfer-encoding;
        bh=mgnW8xfhzGkssYeGVKL8OKFJiT7oGpD36C+YLUEs9TA=;
        b=RRDrMxmX9DF5fM94wNv6LsaxqL88Q9NgnoAwZI0MVpEGxYNQg1kDij1bxDtjYGbSoi
         fTSqB3AcIzaSVfPSzl5wPeF9AFgoLyCtXrFTzWCelmn6YMncZxE2lb57GUROcTzh2NML
         JMMbZhY0qG4FfVG+yhVLA38J3w1oGYTr7D52/FYghOp0ConjYkJ14/viA/kt3ZnMEBAm
         EtdFd39FBK7EL+Jw1cdYXRPEQ2FjHkjigqQOm9Ut8/XUnfmn8zn4v5aBw8U6x/1R6Bgi
         nKIxI9+YU8vjaX0FHuWc4yeGdju3A5AJPipsVuvlUikNsTbhPCpkJ8keu1Ohp/Sn3GmC
         oxtQ==
X-Gm-Message-State: AOAM532KwFl6Qkqsbb/meyvoz0RdkIGgPqFbCq+mTNonMwtmCv7owuPj
        PD42+dyTy+o7vO8OKq3oo3NnK8pOTik=
X-Google-Smtp-Source: 
 ABdhPJw5y94S/wkdoGcsPKRP3Sy9BcFPhMape3rkfsMv3JYDBQ5F2mL/8AP6qLKHSFk15a98gta66uPQySk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e4db:abc1:a5c0:9dbc])
 (user=seanjc job=sendgmr) by 2002:a5b:745:: with SMTP id
 s5mr27855419ybq.265.1612815305037;
 Mon, 08 Feb 2021 12:15:05 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon,  8 Feb 2021 12:15:02 -0800
Message-Id: <20210208201502.1239867-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] KVM: x86/xen: Use hva_t for holding hypercall page address
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Joao Martins <joao.m.martins@oracle.com>,
        David Woodhouse <dwmw@amazon.co.uk>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use hva_t, a.k.a. unsigned long, for the local variable that holds the
hypercall page address.  On 32-bit KVM, gcc complains about using a u64
due to the implicit cast from a 64-bit value to a 32-bit pointer.

  arch/x86/kvm/xen.c: In function ‘kvm_xen_write_hypercall_page’:
  arch/x86/kvm/xen.c:300:22: error: cast to pointer from integer of
                             different size [-Werror=int-to-pointer-cast]
  300 |   page = memdup_user((u8 __user *)blob_addr, PAGE_SIZE);

Cc: Joao Martins <joao.m.martins@oracle.com>
Cc: David Woodhouse <dwmw@amazon.co.uk>
Fixes: 23200b7a30de ("KVM: x86/xen: intercept xen hypercalls if enabled")
Signed-off-by: Sean Christopherson <seanjc@google.com>
Acked-by: David Woodhouse <dwmw@amazon.co.uk>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
---
 arch/x86/kvm/xen.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH net] vsock/virtio: update credit only if socket is not closed
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12075797
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7CF05C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 14:48:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 351AB64DD5
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 14:48:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232195AbhBHOrY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 09:47:24 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:40068 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232762AbhBHOqf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Feb 2021 09:46:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612795510;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=wDyz1IFDSEAOIerG7E7i9OIec2MQQzh/7MUoQ35aflI=;
        b=cFb32JV560wVXBz9LG6xx0n0qngVWx8faTQEVacBMhRwbAQiStTiwthcz8gUOzm1wjhDkE
        4VmZ5tkZjhRZtU7fk6Y//c9b2yvE51t++wFDf011Jp+Rdxa91L2Y9UjobBc0AGk5GiBNd0
        3OgtyKFMZhe14vx/ZEXRP8SAXJYvROc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-580-h0NjNB0VO72XsLi_FX5LlQ-1; Mon, 08 Feb 2021 09:45:08 -0500
X-MC-Unique: h0NjNB0VO72XsLi_FX5LlQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4EC11801975;
        Mon,  8 Feb 2021 14:45:07 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-115-25.ams2.redhat.com
 [10.36.115.25])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E2FBD5D740;
        Mon,  8 Feb 2021 14:44:55 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: kuba@kernel.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        "David S. Miller" <davem@davemloft.net>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        Asias He <asias@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.vnet.ibm.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>
Subject: [PATCH net] vsock/virtio: update credit only if socket is not closed
Date: Mon,  8 Feb 2021 15:44:54 +0100
Message-Id: <20210208144454.84438-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the socket is closed or is being released, some resources used by
virtio_transport_space_update() such as 'vsk->trans' may be released.

To avoid a use after free bug we should only update the available credit
when we are sure the socket is still open and we have the lock held.

Fixes: 06a8fc78367d ("VSOCK: Introduce virtio_vsock_common.ko")
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 net/vmw_vsock/virtio_transport_common.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL v9 01/13] qom: Allow optional sugar props
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12073963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4494EC433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 06:06:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B21964E0B
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 06:06:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229631AbhBHGGZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 01:06:25 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:54865 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229587AbhBHGGX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 01:06:23 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DYwVs0Tvmz9sVs; Mon,  8 Feb 2021 17:05:40 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1612764341;
        bh=uMV7Stmyuv13sOhlodiLYMsOXgTeJ6kZaiH7Z9qlkfI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=dUeovss7hC4U+8JILXsXFPv3T/Z89gVRJlc9gZzLIGfEk3ZB2wJxr1mmDuAqbN6Va
         ma30jsPcZXwrO96/9IlU849t6FgcJQnOWyrGDLQ5YECGcI4suC0kAq3m0KZabhs1zu
         FG+AuC7xJkbrJuYb4+Cr/eBDKxXiJN6y5w3AmpUc=
From: David Gibson <david@gibson.dropbear.id.au>
To: pasic@linux.ibm.com, dgilbert@redhat.com, pair@us.ibm.com,
        qemu-devel@nongnu.org, brijesh.singh@amd.com
Cc: ehabkost@redhat.com, mtosatti@redhat.com, mst@redhat.com,
 jun.nakajima@intel.com, kvm@vger.kernel.org,
 Richard Henderson <richard.henderson@linaro.org>, qemu-s390x@nongnu.org,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, pbonzini@redhat.com,
 frankja@linux.ibm.com, andi.kleen@intel.com, cohuck@redhat.com,
 Thomas Huth <thuth@redhat.com>, borntraeger@de.ibm.com,
 mdroth@linux.vnet.ibm.com, David Gibson <david@gibson.dropbear.id.au>,
	=?utf-8?q?Daniel_P=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 qemu-ppc@nongnu.org, David Hildenbrand <david@redhat.com>,
 Greg Kurz <groug@kaod.org>, pragyansri.pathi@intel.com, =?utf-8?q?Philippe_?=
	=?utf-8?q?Mathieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PULL v9 01/13] qom: Allow optional sugar props
Date: Mon,  8 Feb 2021 17:05:26 +1100
Message-Id: <20210208060538.39276-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210208060538.39276-1-david@gibson.dropbear.id.au>
References: <20210208060538.39276-1-david@gibson.dropbear.id.au>
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
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/qom/object.h |  3 ++-
 qom/object.c         |  4 +++-
 softmmu/rtc.c        |  3 ++-
 softmmu/vl.c         | 17 +++++++++++------
 4 files changed, 18 insertions(+), 9 deletions(-)

```
#### [PULL v9 01/13] qom: Allow optional sugar props
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12074003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34D27C433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 06:08:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F009864E27
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 06:08:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229704AbhBHGIi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 01:08:38 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47744 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229793AbhBHGIL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 01:08:11 -0500
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AB764C06121F
        for <kvm@vger.kernel.org>; Sun,  7 Feb 2021 22:07:41 -0800 (PST)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DYwY55Cz7z9sVs; Mon,  8 Feb 2021 17:07:37 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1612764457;
        bh=uMV7Stmyuv13sOhlodiLYMsOXgTeJ6kZaiH7Z9qlkfI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=qKlLlggx8k8ZH5bs2/3qtiMxQ2QRBII2kDwmbYsluIkTk0uWO7PU7nm0+5fS2SDQc
         9ql6fTfjZkT6DBBqiOHMLPQYIm8yLhnBDX9MsA2FPqSnrxeQ621jkYh1ndiI5kBD86
         Sdi6yaQ1Y/oCUji4bLCmV20i55opY5Qx6VyCdr5I=
From: David Gibson <david@gibson.dropbear.id.au>
To: pair@us.ibm.com, qemu-devel@nongnu.org, peter.maydell@linaro.org,
        dgilbert@redhat.com, brijesh.singh@amd.com, pasic@linux.ibm.com
Cc: richard.henderson@linaro.org, ehabkost@redhat.com, cohuck@redhat.com,
 david@redhat.com, berrange@redhat.com, mtosatti@redhat.com,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, mst@redhat.com,
 borntraeger@de.ibm.com, mdroth@linux.vnet.ibm.com,
 Paolo Bonzini <pbonzini@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, jun.nakajima@intel.com,
 frankja@linux.ibm.com, pragyansri.pathi@intel.com, kvm@vger.kernel.org,
 qemu-ppc@nongnu.org, Thomas Huth <thuth@redhat.com>, andi.kleen@intel.com,
 Greg Kurz <groug@kaod.org>, qemu-s390x@nongnu.org, =?utf-8?q?Philippe_Mathi?=
	=?utf-8?q?eu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PULL v9 01/13] qom: Allow optional sugar props
Date: Mon,  8 Feb 2021 17:07:23 +1100
Message-Id: <20210208060735.39838-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210208060735.39838-1-david@gibson.dropbear.id.au>
References: <20210208060735.39838-1-david@gibson.dropbear.id.au>
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
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/qom/object.h |  3 ++-
 qom/object.c         |  4 +++-
 softmmu/rtc.c        |  3 ++-
 softmmu/vl.c         | 17 +++++++++++------
 4 files changed, 18 insertions(+), 9 deletions(-)

```
#### [PATCH v1] kvm: x86: Revise guest_fpu xcomp_bv field
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 12074137
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7832FC433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 07:30:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25E2964E76
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 07:30:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229851AbhBHHam (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 02:30:42 -0500
Received: from mga03.intel.com ([134.134.136.65]:32276 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229608AbhBHHal (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 02:30:41 -0500
IronPort-SDR: 
 VQu+7EA7SUiUxWGk91libdkM03jyburFS/UilediU/ZS5h4xBS1XkxvTBuqwFkSViREXNf43x9
 TgCnj7HmLB/w==
X-IronPort-AV: E=McAfee;i="6000,8403,9888"; a="181736692"
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="181736692"
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Feb 2021 23:28:55 -0800
IronPort-SDR: 
 XFU5j01Wyd9Xl9CirZrzX3awEEYk9O/BrVwj5noMPi6TE3nTY3u+dDvdRkvo11bz1iFUznwxDb
 cc9043pRazDA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="398280466"
Received: from vmmteam.bj.intel.com ([10.240.193.86])
  by orsmga007.jf.intel.com with ESMTP; 07 Feb 2021 23:28:52 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: pbonzini@redhat.com
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v1] kvm: x86: Revise guest_fpu xcomp_bv field
Date: Mon,  8 Feb 2021 11:16:59 -0500
Message-Id: <20210208161659.63020-1-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.18.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bit 63 of the XCOMP_BV field indicates that the save area is in the
compacted format and the remaining bits indicate the states that have
space allocated in the save area, not only user states. Since
fpstate_init() has initialized xcomp_bv, let's just use that.

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---
 arch/x86/kvm/x86.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: x86/mmu: Make HVA handler retpoline-friendly
##### From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
X-Patchwork-Id: 12076279
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 08305C433E6
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 18:54:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AE6B564E74
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 18:54:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233895AbhBHSx6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 13:53:58 -0500
Received: from vps-vb.mhejs.net ([37.28.154.113]:60334 "EHLO vps-vb.mhejs.net"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233253AbhBHSwh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 13:52:37 -0500
Received: from MUA
        by vps-vb.mhejs.net with esmtps
 (TLS1.2:ECDHE-RSA-AES256-GCM-SHA384:256)
        (Exim 4.93.0.4)
        (envelope-from <mail@maciej.szmigiero.name>)
        id 1l9BdK-00044c-5D; Mon, 08 Feb 2021 19:51:38 +0100
From: "Maciej S. Szmigiero" <mail@maciej.szmigiero.name>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: x86/mmu: Make HVA handler retpoline-friendly
Date: Mon,  8 Feb 2021 19:51:32 +0100
Message-Id: 
 <732d3fe9eb68aa08402a638ab0309199fa89ae56.1612810129.git.maciej.szmigiero@oracle.com>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: "Maciej S. Szmigiero" <maciej.szmigiero@oracle.com>

When retpolines are enabled they have high overhead in the inner loop
inside kvm_handle_hva_range() that iterates over the provided memory area.

Let's mark this function and its TDP MMU equivalent __always_inline so
compiler will be able to change the call to the actual handler function
inside each of them into a direct one.

This significantly improves performance on the unmap test on the existing
kernel memslot code (tested on a Xeon 8167M machine):
30 slots in use:
Test       Before   After     Improvement
Unmap      0.0353s  0.0334s   5%
Unmap 2M   0.00104s 0.000407s 61%

509 slots in use:
Test       Before   After     Improvement
Unmap      0.0742s  0.0740s   None
Unmap 2M   0.00221s 0.00159s  28%

Looks like having an indirect call in these functions (and, so, a
retpoline) might have interfered with unrolling of the whole loop in the
CPU.

Signed-off-by: Maciej S. Szmigiero <maciej.szmigiero@oracle.com>
---
Changes from v1:
    * Switch from static dispatch to __always_inline annotation.
    
    * Separate this patch from the rest of log(n) memslot code changes.
    
    * Redo benchmarks.

 arch/x86/kvm/mmu/mmu.c     | 21 +++++++++++----------
 arch/x86/kvm/mmu/tdp_mmu.c | 16 +++++++++++-----
 2 files changed, 22 insertions(+), 15 deletions(-)

```
#### [PATCH v3] vfio/pci: Add support for opregion v2.1+
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 12074471
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,
	DATE_IN_FUTURE_06_12,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0421C433DB
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:10:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B53264E85
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:10:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231169AbhBHJK0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 04:10:26 -0500
Received: from mga01.intel.com ([192.55.52.88]:45686 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230490AbhBHJIh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 04:08:37 -0500
IronPort-SDR: 
 DBaXbfe9ml+333f4DjT8dEL8CB9AoU8xcfSAYGwqd9e1MKntOq7VC4lmDMEwvCRJ/NPzH18bSy
 CbmTCCpZ0T+A==
X-IronPort-AV: E=McAfee;i="6000,8403,9888"; a="200738516"
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="200738516"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 01:07:49 -0800
IronPort-SDR: 
 59sSfZShLRivi3I6v7lffwC0oPbnHYRA9rwSCZKSJMXaPNTLGO5KxQnPI8NDPJIXKR/EIpd3Ew
 wStPteCVH3RA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="435564128"
Received: from cfl-host.sh.intel.com ([10.239.158.118])
  by orsmga001.jf.intel.com with ESMTP; 08 Feb 2021 01:07:47 -0800
From: Fred Gao <fred.gao@intel.com>
To: kvm@vger.kernel.org, intel-gfx@lists.freedesktop.org
Cc: Fred Gao <fred.gao@intel.com>,
        Zhenyu Wang <zhenyuw@linux.intel.com>,
        Swee Yee Fonn <swee.yee.fonn@intel.com>
Subject: [PATCH v3] vfio/pci: Add support for opregion v2.1+
Date: Tue,  9 Feb 2021 01:02:53 +0800
Message-Id: <20210208170253.29968-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
In-Reply-To: <20210118123834.5991-1-fred.gao@intel.com>
References: <20210118123834.5991-1-fred.gao@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before opregion version 2.0 VBT data is stored in opregion mailbox #4,
However, When VBT data exceeds 6KB size and cannot be within mailbox #4
starting from opregion v2.0+, Extended VBT region, next to opregion, is
used to hold the VBT data, so the total size will be opregion size plus
extended VBT region size.

since opregion v2.0 with physical host VBT address should not be
practically available for end user, it is not supported.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Signed-off-by: Swee Yee Fonn <swee.yee.fonn@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci_igd.c | 49 +++++++++++++++++++++++++++++++++
 1 file changed, 49 insertions(+)

```
