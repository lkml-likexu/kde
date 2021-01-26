#### [PATCH] KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest mode for VMX
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12043793
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0E14EC43381
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 17:22:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D192622C9E
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 17:22:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730998AbhAYRW2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 12:22:28 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:58507 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730983AbhAYRWW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 25 Jan 2021 12:22:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611595248;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fLkc6jBByIwZj+y5K87dwsdh1F4jKYYT1Ucr0DYgAHo=;
        b=JSz+kWrF7JdTWLywWEoC79i2KB12gfE3CMN+enJHjDY5LHqCzSLk81BKSd5PI0/cZfAMAl
        3xt2pYk8oW2Ok/D7b3NXL+5QBBmErIj6g/X4U1qdBBlLnc3HsBT6zZd4rTlvhd90CGiXKd
        F7n5zDZeBomaP1tvTop59M41iEsGh4g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-400-BsjjSMAxOdS1oRXxbwGosw-1; Mon, 25 Jan 2021 12:20:46 -0500
X-MC-Unique: BsjjSMAxOdS1oRXxbwGosw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B643559;
        Mon, 25 Jan 2021 17:20:45 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 663E55D9DB;
        Mon, 25 Jan 2021 17:20:45 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Subject: [PATCH] KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest
 mode for VMX
Date: Mon, 25 Jan 2021 12:20:44 -0500
Message-Id: <20210125172044.1360661-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX also uses KVM_REQ_GET_NESTED_STATE_PAGES for the Hyper-V eVMCS,
which may need to be loaded outside guest mode.  Therefore we cannot
WARN in that case.

However, that part of nested_get_vmcs12_pages is _not_ needed at
vmentry time.  Split it out of KVM_REQ_GET_NESTED_STATE_PAGES handling,
so that both vmentry and migration (and in the latter case, independent
of is_guest_mode) do the parts that are needed.

Cc: <stable@vger.kernel.org> # 5.10.x: f2c7ef3ba: KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES
Cc: <stable@vger.kernel.org> # 5.10.x
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c |  3 +++
 arch/x86/kvm/vmx/nested.c | 32 ++++++++++++++++++++++++++------
 arch/x86/kvm/x86.c        |  4 +---
 3 files changed, 30 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: x86/mmu: consider the hva in mmu_notifer retry
##### From: David Stevens <stevensd@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12042987
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C7D1C433E0
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 06:46:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD24F224DE
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 06:45:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726772AbhAYGpx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 01:45:53 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57320 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726854AbhAYGnc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 01:43:32 -0500
Received: from mail-pj1-x1034.google.com (mail-pj1-x1034.google.com
 [IPv6:2607:f8b0:4864:20::1034])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B3696C0613D6
        for <kvm@vger.kernel.org>; Sun, 24 Jan 2021 22:42:45 -0800 (PST)
Received: by mail-pj1-x1034.google.com with SMTP id u4so8007301pjn.4
        for <kvm@vger.kernel.org>; Sun, 24 Jan 2021 22:42:45 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=14Bj46XsmXbx8plhZIOf6y+coaN/fUKX0SPBaGuWf7g=;
        b=K+fEZGRQSbFrMb6wpHc6SmH0r9YjxxbhSOFrGK58eer8lhC15uhhxYdXkoFfOnIokM
         ShizDBmMZx2ZoD5i7bGeHdmqBpHgAIxp9Lla9dEPI1+s266i+9fAKebNZ4SpZlulRt+5
         ta0T+HzD4ymvq7xdjdAyz/vUWgEe76ciMAIH8=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=14Bj46XsmXbx8plhZIOf6y+coaN/fUKX0SPBaGuWf7g=;
        b=kBOyTjFAXlLAaOUTnS1MOUyx6B1MYdfbmPdW4H40s26Sdu9G/icPksUk9aOb4FvG6G
         4FUkbmBW1LVle+jgmOp2kOd+kbxLekeJHnHSxmz28vQkb/hBevleSN0YifRE38IGx2mi
         5FJqTxRzF9pP6bIEmr+iMFqushOsFDRMG1999nmAcmHs7pWgMp0+wW+UW/xImwBT6inb
         FfEvbfChbnK0+/ayWVFeL9nA+Tz48a0NxIdhPRCUY5RzYH48PXOxdWCohyrSE7Ivs8r0
         Wk3EsSRX7SG3NghmQ90aLTDnoH8eLSqi32tW3JcKaFwDyBIGxoHNsLAxDRf9p0OXfu2P
         RKIQ==
X-Gm-Message-State: AOAM530pofz97MyK/llI12gx5Tq50Hb40/6Mqp3XgKStAnwAMbQ63RoZ
        n8/4axq/NVb6CqIzudvRrxFG/wtySAb6/Q==
X-Google-Smtp-Source: 
 ABdhPJw2Koj77z3eEz0N0rMl8RJZzwBQ86hcwevAAQ4aIZlPMfH8PvMZ5rre+Io8LdeOagBw+lsCUw==
X-Received: by 2002:a17:90a:a44:: with SMTP id
 o62mr20286765pjo.209.1611556965293;
        Sun, 24 Jan 2021 22:42:45 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:f693:9fff:fef4:a930])
        by smtp.gmail.com with ESMTPSA id
 n8sm17935062pjo.18.2021.01.24.22.42.42
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Sun, 24 Jan 2021 22:42:44 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, David Stevens <stevensd@chromium.org>
Subject: [PATCH] KVM: x86/mmu: consider the hva in mmu_notifer retry
Date: Mon, 25 Jan 2021 15:42:34 +0900
Message-Id: <20210125064234.2078146-1-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Stevens <stevensd@chromium.org>

Use the range passed to mmu_notifer's invalidate_range_start to prevent
spurious page fault retries due to changes in unrelated host virtual
addresses. This has the secondary effect of greatly reducing the
likelihood of extreme latency when handing a page fault due to another
thread having been preempted while modifying host virtual addresses.

Signed-off-by: David Stevens <stevensd@chromium.org>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/x86/kvm/mmu/mmu.c                 | 16 ++++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h         |  7 ++++---
 include/linux/kvm_host.h               | 22 +++++++++++++++++++++-
 virt/kvm/kvm_main.c                    | 22 ++++++++++++++++++----
 6 files changed, 55 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: X86: use vzalloc() instead of vmalloc/memset
##### From: Tian Tao <tiantao6@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tian Tao <tiantao6@hisilicon.com>
X-Patchwork-Id: 12042885
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 151AAC433E0
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 03:58:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CDBCF225A9
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 03:58:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726894AbhAYD6a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 24 Jan 2021 22:58:30 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11855 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726677AbhAYD63 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 Jan 2021 22:58:29 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DPGJK3ZDJz7Z5S;
        Mon, 25 Jan 2021 11:56:33 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Mon, 25 Jan 2021 11:57:41 +0800
From: Tian Tao <tiantao6@hisilicon.com>
To: <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>
Subject: [PATCH] KVM: X86: use vzalloc() instead of vmalloc/memset
Date: Mon, 25 Jan 2021 11:57:25 +0800
Message-ID: <1611547045-13669-1-git-send-email-tiantao6@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

fixed the following warning：
/virt/kvm/dirty_ring.c:70:20-27: WARNING: vzalloc should be used for
ring -> dirty_gfns, instead of vmalloc/memset.

Signed-off-by: Tian Tao <tiantao6@hisilicon.com>
---
 virt/kvm/dirty_ring.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH RESEND] kvm: mmu.h: delete duplicated word
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 12044293
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9B007C433E6
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 20:35:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EC1D22597
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 20:35:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732261AbhAYUf0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 15:35:26 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39924 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732295AbhAYUfL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 15:35:11 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6AB32C061573;
        Mon, 25 Jan 2021 12:34:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:Content-Type:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=WiGs1qgslmQVm39ErD8FtEC6YDu9ozQcsFkJHMOI2oc=;
 b=eZ8aDB5ZjP439EyzjUsxb2Omrs
        pv4125X9udbw90Pa8WcK+X5aWTVUx97W7l0D2xai6lRWw+hg6ECKbzarQnqRk/n/6xr97uDVUvFm1
        pH6Yduz5vyjw2NSWX/jn4b70SgPSavVvFzhvAnoNk/0c+FuLRd0jnnBcdZUhJeF0V2V5FCnDaQcRU
        FDQqcZ9hXIYRNn5DHmTc7NGLq7maKunmcaj2pf6vcxTyYzqzpcl9bw8ZVd/1vxNwjUZ0zfhzVPmMb
        zfXpWVog6L4xZ73AmCYoYMHS6sjvOyzaUhHqeRCyDKlWW/aXd67qofS528Mdxm0YEF0Ortj3eyvNY
        zxNO1Xfw==;
Received: from [2601:1c0:6280:3f0::7650] (helo=merlin.infradead.org)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1l48Z7-0003zB-RN; Mon, 25 Jan 2021 20:34:26 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH RESEND] kvm: mmu.h: delete duplicated word
Date: Mon, 25 Jan 2021 12:34:19 -0800
Message-Id: <20210125203420.26069-1-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete the repeated word "is".

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 arch/x86/kvm/mmu.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200720.orig/arch/x86/kvm/mmu.h
+++ linux-next-20200720/arch/x86/kvm/mmu.h
@@ -191,7 +191,7 @@ static inline u8 permission_fault(struct
 		* PKRU defines 32 bits, there are 16 domains and 2
 		* attribute bits per domain in pkru.  pte_pkey is the
 		* index of the protection domain, so pte_pkey * 2 is
-		* is the index of the first bit for the domain.
+		* the index of the first bit for the domain.
 		*/
 		pkru_bits = (vcpu->arch.pkru >> (pte_pkey * 2)) & 3;
 
```
#### [PATCH RESEND] kvm: paging_tmpl.h: delete duplicated word
##### From: Randy Dunlap <rdunlap@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Randy Dunlap <rdunlap@infradead.org>
X-Patchwork-Id: 12044295
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 629D7C433DB
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 20:35:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2FBA522510
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 20:35:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732319AbhAYUfl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 15:35:41 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39984 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732312AbhAYUfZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 15:35:25 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9D1C7C06174A;
        Mon, 25 Jan 2021 12:34:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Content-Transfer-Encoding:MIME-Version:
        Message-Id:Date:Subject:Cc:To:From:Sender:Reply-To:Content-Type:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=VitMP7uQjz9q5/byuL/XQS+Y0BC50vmbZT4y0BkkwD4=;
 b=pfinHIg0p/BZA0xPXP07v1YLs7
        ZCWeUta2AxCC7QHY9GApahX9cBD02CDPsSGyuSkxV5NiCqUXGtgaWGPQeE9Yxg5DStxQv0YxybAvf
        MJfr12bw+/V2/mxkSHRjlmpezsjabfL5qcQKLeILZsxByhVnMKLMf6SF/Y4C4HPT3v8DgTXNAQOVe
        K+tbWjF8YXz0Afv0hsqxDV0dS20nCGt/CsSNaK+jQAPXAzC3u6IJQAUwn1K5VGx+VLryqzaUECAkB
        JBREAdjpTVet1/28EU0y1Gx1Nh6EbfN5R9LIXIP1dfHmA0ssGzux1hXySREI7s5BqjV7WADZxq6oB
        9KAzyTZA==;
Received: from [2601:1c0:6280:3f0::7650] (helo=merlin.infradead.org)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1l48ZO-00040L-4p; Mon, 25 Jan 2021 20:34:42 +0000
From: Randy Dunlap <rdunlap@infradead.org>
To: linux-kernel@vger.kernel.org
Cc: Randy Dunlap <rdunlap@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH RESEND] kvm: paging_tmpl.h: delete duplicated word
Date: Mon, 25 Jan 2021 12:34:36 -0800
Message-Id: <20210125203436.26149-1-rdunlap@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Delete the repeated word "to".

Signed-off-by: Randy Dunlap <rdunlap@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
---
 arch/x86/kvm/mmu/paging_tmpl.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

--- linux-next-20200720.orig/arch/x86/kvm/mmu/paging_tmpl.h
+++ linux-next-20200720/arch/x86/kvm/mmu/paging_tmpl.h
@@ -478,7 +478,7 @@ error:
 
 #if PTTYPE == PTTYPE_EPT
 	/*
-	 * Use PFERR_RSVD_MASK in error_code to to tell if EPT
+	 * Use PFERR_RSVD_MASK in error_code to tell if EPT
 	 * misconfiguration requires to be injected. The detection is
 	 * done by is_rsvd_bits_set() above.
 	 *
```
#### [RFC PATCH v1 3/4] vfio: Try to enable IOPF for VFIO devices
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12043119
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 19501C433E0
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 09:32:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AACF722CF6
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 09:32:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726696AbhAYJbz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 04:31:55 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11862 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726680AbhAYJ31 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 04:29:27 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DPP6m65prz7Znb;
        Mon, 25 Jan 2021 17:03:44 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.186.182) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Mon, 25 Jan 2021 17:04:48 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Eric Auger <eric.auger@redhat.com>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Kevin Tian <kevin.tian@intel.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [RFC PATCH v1 3/4] vfio: Try to enable IOPF for VFIO devices
Date: Mon, 25 Jan 2021 17:04:01 +0800
Message-ID: <20210125090402.1429-4-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210125090402.1429-1-lushenming@huawei.com>
References: <20210125090402.1429-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.186.182]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If IOMMU_DEV_FEAT_IOPF is set for the VFIO device, which means that
the delivering of page faults of this device from the IOMMU is enabled,
we register the VFIO page fault handler to complete the whole faulting
path (HW+SW). And add a iopf_enabled field in struct vfio_device to
record it.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 drivers/vfio/vfio.c | 20 ++++++++++++++++++++
 1 file changed, 20 insertions(+)

```
#### [PATCH v2 1/7] KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12043355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 18230C433E0
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 12:43:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C41FE22D04
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 12:43:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728219AbhAYMmg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 07:42:36 -0500
Received: from mail.kernel.org ([198.145.29.99]:38396 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728049AbhAYMkc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 07:40:32 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id C3EE0225AC;
        Mon, 25 Jan 2021 12:26:43 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l40x8-009sBu-1k; Mon, 25 Jan 2021 12:26:42 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com,
        Peter Maydell <peter.maydell@linaro.org>
Subject: [PATCH v2 1/7] KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
Date: Mon, 25 Jan 2021 12:26:32 +0000
Message-Id: <20210125122638.2947058-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210125122638.2947058-1-maz@kernel.org>
References: <20210125122638.2947058-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, kernel-team@android.com,
 peter.maydell@linaro.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The AArch32 CP14 DBGDIDR has bit 15 set to RES1, which our current
emulation doesn't set. Just add the missing bit.

Reported-by: Peter Maydell <peter.maydell@linaro.org>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio/iommu_type1: Mantainance a counter for non_pinned_groups
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12042851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 57C14C433E6
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 02:47:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30A2B227BF
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 02:47:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726700AbhAYCrg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 24 Jan 2021 21:47:36 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:11435 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726601AbhAYCre (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 Jan 2021 21:47:34 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DPDkp1PRwzjBfN;
        Mon, 25 Jan 2021 10:45:54 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.498.0; Mon, 25 Jan 2021 10:46:45 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <iommu@lists.linux-foundation.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>
CC: Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        "James Morse" <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH] vfio/iommu_type1: Mantainance a counter for non_pinned_groups
Date: Mon, 25 Jan 2021 10:46:42 +0800
Message-ID: <20210125024642.14604-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With this counter, we never need to traverse all groups to update
pinned_scope of vfio_iommu.

Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 40 +++++----------------------------
 1 file changed, 5 insertions(+), 35 deletions(-)

```
#### [RFC PATCH v3 02/13] af_vsock: prepare 'vsock_connectible_recvmsg()'
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12043345
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7674AC433E0
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 12:26:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29138225AB
	for <kvm@archiver.kernel.org>; Mon, 25 Jan 2021 12:26:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728002AbhAYM0Y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 25 Jan 2021 07:26:24 -0500
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:58670 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728031AbhAYMZw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Jan 2021 07:25:52 -0500
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 317C152170D;
        Mon, 25 Jan 2021 14:12:07 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail; t=1611573127;
        bh=PQvxSXikVxKrVvCVMuElHDDXYoRL/SJwgxpXVZlaTv4=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=J0l4ZiKz2VgdK3yjznbepmRpPcf6NdweTVPUbzSW690fZ6WdY4zh1Iem9uRBJwB2b
         PAqNHShidV+0h1UoLQ4hUeZxLoMhoEyMox4OJaUq5SfEanvijsgAz833M3pYMUW7pf
         NJuKXLs2QRbisd3RQxSsZWZM5jz+bypphN04a5XI=
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id D3FD7521738;
        Mon, 25 Jan 2021 14:12:06 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.64.121) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2044.4; Mon, 25
 Jan 2021 14:12:06 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Arseny Krasnov <arseny.krasnov@kaspersky.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Colin Ian King <colin.king@canonical.com>,
        Jeff Vander Stoep <jeffv@google.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <oxffffaa@gmail.com>
Subject: [RFC PATCH v3 02/13] af_vsock: prepare 'vsock_connectible_recvmsg()'
Date: Mon, 25 Jan 2021 14:11:57 +0300
Message-ID: <20210125111200.598103-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210125110903.597155-1-arseny.krasnov@kaspersky.com>
References: <20210125110903.597155-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.64.121]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.16, Database issued on: 01/25/2021 10:59:54
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 161363 [Jan 25 2021]
X-KSE-AntiSpam-Info: LuaCore: 421 421 33a18ad4049b4a5e5420c907b38d332fafd06b09
X-KSE-AntiSpam-Info: Version: 5.9.16.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_date, moscow}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 arseniy-pc.avp.ru:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1;d41d8cd98f00b204e9800998ecf8427e.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 01/25/2021 11:02:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 1/25/2021 10:11:00 AM
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/01/25 10:04:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/01/25 05:31:00 #16022694
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This prepares 'vsock_connectible_recvmg()' to call SEQPACKET receive
loop:
1) Some shared check left in this function, then socket type
   specific receive loop is called.
2) Stream receive loop is moved to separate function.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
---
 net/vmw_vsock/af_vsock.c | 242 ++++++++++++++++++++++-----------------
 1 file changed, 138 insertions(+), 104 deletions(-)

```
