#### [PATCH v2 1/8] crypto: ccp: Free SEV device if SEV init failsFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12186193
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02F91C43460
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 22:50:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B662E613D5
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 22:50:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344191AbhDFWuU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 18:50:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40058 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1344193AbhDFWuQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 18:50:16 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0FD90C061756
        for <kvm@vger.kernel.org>; Tue,  6 Apr 2021 15:50:08 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id x22so21770450ybi.1
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 15:50:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=9unnZdwnJBhmIr85WtW6opdl6PIonHCZIupIJTvjWiM=;
        b=TkbGpsapVhMM/9vNTvKB2L0fGV6FDhcQqCVGeETLXWxcwfezHG91/Q32wDXz4NNQzM
         nc0exNLd9sY6ryGmhhmyHB1RRJGT8Chj3tHZWlz8EP2ltZ2XznhwfwqVrVa8wOWGyxx7
         0q80IQ90Nro8z6l81DX7mZp32wgeHg/9fnbOVCWSN+TnbJo+T+psv21FIznZvp11IQSD
         7OO9fnXsMk0l7y7GljMe9yy4UhNrmsgXxl6Vnzk+LjeuD/C1qm4zOXUElsRpln+otQI5
         b1CaykelVe2JuM1a88H8nPQECvnwDlaUMgwiRCR90/JGzBaByfMcJAkkJv8tWLv1lKzC
         aw8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=9unnZdwnJBhmIr85WtW6opdl6PIonHCZIupIJTvjWiM=;
        b=A1+QTuyzXxG4SQoM5EL8BYIWBwMLcQApMmOecdZGKGHtZpmfsjsV6kj5wqC5XOcI1C
         7TBXWFAqcUqGRQ9cUhupxtzd/U4nGs28cQg5k2gu4vULT6I7anJXeQflJvZoRK/l47+U
         GO4g/R7wrPWx5E8v+J9RR3QnPkVsxaivBjQziUbamSr9yoEH3HAmOkmRndghfyGDXItc
         gdeh2fFYDKx6NeXZmiB0xFE6IOgVk5Fz4nOC7efpcRL33gmxfVZxXVkKFk9/JFlO1Yyw
         YEm5ufriYDN72sAF0zjdL8m7bB5/KodrrEsNnrf2b0zL+aDGm3WTKMbII1z8nDPrrQJy
         7KqQ==
X-Gm-Message-State: AOAM532vFTtFIC7cUMKUQ2nCLCEcpgF8OaTukFGHiGO8+xM0wa1fROzV
        AOF/7pbCDaL3Ix/B5fpuhMsiMSPrArU=
X-Google-Smtp-Source: 
 ABdhPJzlb0ZbdnN3YVCAvkv4hLaHNRneUSdCrOk9RA1gK+d59njBjzucCXv09ROJce8rsyMB2b1YQgaYp58=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:24a1:90fb:182b:777c])
 (user=seanjc job=sendgmr) by 2002:a25:b3c1:: with SMTP id
 x1mr517791ybf.506.1617749407346;
 Tue, 06 Apr 2021 15:50:07 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  6 Apr 2021 15:49:45 -0700
In-Reply-To: <20210406224952.4177376-1-seanjc@google.com>
Message-Id: <20210406224952.4177376-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210406224952.4177376-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH v2 1/8] crypto: ccp: Free SEV device if SEV init fails
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        John Allen <john.allen@amd.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-kernel@vger.kernel.org,
        Borislav Petkov <bp@suse.de>,
        Christophe Leroy <christophe.leroy@csgroup.eu>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Free the SEV device if later initialization fails.  The memory isn't
technically leaked as it's tracked in the top-level device's devres
list, but unless the top-level device is removed, the memory won't be
freed and is effectively leaked.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 drivers/crypto/ccp/sev-dev.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/4] KVM: x86: Fix a spurious -E2BIG in KVM_GET_EMULATED_CPUID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12184505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C8290C43460
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:27:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92CF3613C0
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:27:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240209AbhDFI1J (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 04:27:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57018 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240288AbhDFI1G (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 04:27:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617697619;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5pS0wh7N3KpBX2QM5qANzzkJZX1lhQrm39b/3Z7eSz4=;
        b=gavnwrK1Xn5MZoLVxDKa/P/rfjDkioEsJhkHE6tr9IChC5eFq+zkmPYj1rAD5QPzk5eQGk
        80M8De8rgVoXvKLz4FA0UMOWnXM+3G9SbhSWEbEq+x+zr6Ga0nXapNXO4Q0u6aYuE/GRwo
        amdc2WYSJUv/QF9AZW66MXbsFOM0Ufo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-567-5s6b4nFBMl-osbL7yVzetw-1; Tue, 06 Apr 2021 04:26:55 -0400
X-MC-Unique: 5s6b4nFBMl-osbL7yVzetw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BBA0C18C8C05;
        Tue,  6 Apr 2021 08:26:53 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-253.ams2.redhat.com
 [10.36.114.253])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CA9A25D9D0;
        Tue,  6 Apr 2021 08:26:49 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v3 1/4] KVM: x86: Fix a spurious -E2BIG in
 KVM_GET_EMULATED_CPUID
Date: Tue,  6 Apr 2021 10:26:39 +0200
Message-Id: <20210406082642.20115-2-eesposit@redhat.com>
In-Reply-To: <20210406082642.20115-1-eesposit@redhat.com>
References: <20210406082642.20115-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When retrieving emulated CPUID entries, check for an insufficient array
size if and only if KVM is actually inserting an entry.
If userspace has a priori knowledge of the exact array size,
KVM_GET_EMULATED_CPUID will incorrectly fail due to effectively requiring
an extra, unused entry.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/cpuid.c | 33 ++++++++++++++++-----------------
 1 file changed, 16 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: MIPS: Remove a "set but not used" variable
##### From: Huacai Chen <chenhuacai@loongson.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhuacai@loongson.cn>
X-Patchwork-Id: 12184027
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 496FEC433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 02:48:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 12DAB613A7
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 02:48:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243486AbhDFCsx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 5 Apr 2021 22:48:53 -0400
Received: from mail.kernel.org ([198.145.29.99]:58900 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233030AbhDFCsx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Apr 2021 22:48:53 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 21F1861396;
        Tue,  6 Apr 2021 02:48:43 +0000 (UTC)
From: Huacai Chen <chenhuacai@loongson.cn>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhuacai@loongson.cn>,
        kernel test robot <lkp@intel.com>
Subject: [PATCH] KVM: MIPS: Remove a "set but not used" variable
Date: Tue,  6 Apr 2021 10:49:11 +0800
Message-Id: <20210406024911.2008046-1-chenhuacai@loongson.cn>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This fix a build warning:

   arch/mips/kvm/vz.c: In function '_kvm_vz_restore_htimer':
>> arch/mips/kvm/vz.c:392:10: warning: variable 'freeze_time' set but not used [-Wunused-but-set-variable]
     392 |  ktime_t freeze_time;
         |          ^~~~~~~~~~~

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Huacai Chen <chenhuacai@loongson.cn>
---
 arch/mips/kvm/vz.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH 1/4] KVM: SVM: Don't set current_vmcb->cpu when switching vmcbFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12185593
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9F9D2C433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 17:18:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6FFF3610E8
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 17:18:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1346842AbhDFRSc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 13:18:32 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52456 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S244425AbhDFRSZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 13:18:25 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1E329C06174A
        for <kvm@vger.kernel.org>; Tue,  6 Apr 2021 10:18:17 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id l132so8049519ybl.23
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 10:18:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=oivDkQlUDQSvSEYmPed6OfkcBD+Dvdh/iwh7GoMJjX4=;
        b=ggRtauV+tbl//nJw9paxByj4LnhMRWjJS7yrReiQAs3GvtMi2oMAS3yC1IFT/CoHGe
         RbHKiJ1H2D6MEi7QYMNkil9+Aerk0FiECYeaBlD1QcAbi4iwn9qABTyT+fbass/ZEKZK
         3O42kT5OWCcSyNhlMLf8w3yu9VoxhzkZCASbdbh7Oux8hBaJRF3a1sV/BRnoro+fNLqL
         i4VaQRGWV/vRQ9Upp4+ARASsJyVGOZ+KYidRi4jgR08qmw6WiN5ol62J7MEE08WTqx5i
         tlJuZeYrMa/TcwXLNfLfk3XjGLKtoWUnYWpdeNyjNrxXxGTs90da8KmBkWR/SRjHyngM
         YnGA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=oivDkQlUDQSvSEYmPed6OfkcBD+Dvdh/iwh7GoMJjX4=;
        b=jskhY+gu7xns92h6jMmZYcuCojmEUkbed+XOGh+Vw+z7OvNtntMdGyt4EJdsoMiJJc
         hHFuOeojbTuxNDM6AmztaqgcW5b56Bi2VEHGnL8SpAN9TiBfODKfX2UdWuesB6yLKzAp
         7Y1pIksUWHgv3+K7PuTniyHYTl/G5zl11sFOpTTAdcE/LaMHFPJaVX8JNPO/I4Ol1gEc
         Tux353NurD5F4yYSHZPt9gYXm+miH2aBo32VayK32ph6Qd9jng2DCNNGmotRkwHtPdzh
         PU02BjNIxK2z22OLGhMCYdrZ4dZ/xvn3TNhCOlnc5kvorFCQyQ8GvJHCekgF0rjdSuHU
         jjVQ==
X-Gm-Message-State: AOAM530uaIy3DLPymnTsJtr/GqmVYYJk8iPjeHyURI+cGh9Q9ruB5eVN
        cTiAJGbLnWH+CQ+FDkeBgpuH539rbaE=
X-Google-Smtp-Source: 
 ABdhPJy4XKdA8GBJ3EDloaxSOG3D2OJARqprhnA3IlBhScNJSqLb4bKe9aTcFxXnCIMiMduIFXARkNbXC8Q=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:24a1:90fb:182b:777c])
 (user=seanjc job=sendgmr) by 2002:a05:6902:100d:: with SMTP id
 w13mr21865678ybt.489.1617729496367; Tue, 06 Apr 2021 10:18:16 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  6 Apr 2021 10:18:08 -0700
In-Reply-To: <20210406171811.4043363-1-seanjc@google.com>
Message-Id: <20210406171811.4043363-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210406171811.4043363-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH 1/4] KVM: SVM: Don't set current_vmcb->cpu when switching vmcb
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Cathy Avery <cavery@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Do not update the new vmcb's last-run cpu when switching to a different
vmcb.  If the vCPU is migrated between its last run and a vmcb switch,
e.g. for nested VM-Exit, then setting the cpu without marking the vmcb
dirty will lead to KVM running the vCPU on a different physical cpu with
stale clean bit settings.

                          vcpu->cpu    current_vmcb->cpu    hardware
  pre_svm_run()           cpu0         cpu0                 cpu0,clean
  kvm_arch_vcpu_load()    cpu1         cpu0                 cpu0,clean
  svm_switch_vmcb()       cpu1         cpu1                 cpu0,clean
  pre_svm_run()           cpu1         cpu1                 kaboom

Simply delete the offending code; unlike VMX, which needs to update the
cpu at switch time due to the need to do VMPTRLD, SVM only cares about
which cpu last ran the vCPU.

Fixes: af18fa775d07 ("KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb")
Cc: Cathy Avery <cavery@redhat.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH] KVM: X86: Count success and invalid yields
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12184527
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C1361C433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:32:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C893613BE
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 08:32:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239927AbhDFIcy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 04:32:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49382 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232822AbhDFIcw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 04:32:52 -0400
Received: from mail-pj1-x102f.google.com (mail-pj1-x102f.google.com
 [IPv6:2607:f8b0:4864:20::102f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AFE0CC06174A;
        Tue,  6 Apr 2021 01:32:41 -0700 (PDT)
Received: by mail-pj1-x102f.google.com with SMTP id
 kk2-20020a17090b4a02b02900c777aa746fso7260320pjb.3;
        Tue, 06 Apr 2021 01:32:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=IDxkuTbkM54Xm1Acge8AgpMHwOFsJk+F1h7AXGDseX4=;
        b=cSG6YBH2D0dnDpTEOvco0wOUCWTCMZZyT2LESFBnj7V7NcFMOtgyKjphIv4te74/vy
         g53XBfnJp/WLHiwxCgdkthf22Tzk3tVMBH/CMVO/KnCJc/sMziNzw67QWGNRbpjFFRKz
         LZH8TLtqYNJ3vwJP/F8xzg16FpULRYSmANSNIk44dMiDRvs83gGFQkuNcRM+xGgnhpIz
         bnHE7n1eXTWz0u/RhiqRoMlwJAWRz+4v7jSc3XHQERhfTfICABrCWlxLvvXIv/0F8JX+
         4RcgptrSo5glUKkXeWMt3nB+9oiWEbJYHgmpDGXBBOVqHY1fiHFOKjE2Qx42PKaWi0sV
         qg9Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=IDxkuTbkM54Xm1Acge8AgpMHwOFsJk+F1h7AXGDseX4=;
        b=nB/jwKy/uOlTvK2XUDE7s8WVTqkQY5dKpcu48Lmwe4b2VvwMB+s4uo2iiHqKVonGXW
         gXHbiekSVzwvTvM8nYORtss95CQS5ZzBt9l7AamRqijBMXgA/IlSsXOUcdggbjPFME6v
         DGSSZaWPNnUYZXwAzx1W6fHelMZ2gnaosbgWlybUvKZsmpkQZaQr6SuA6RBv5PgMbv/U
         /h2AdWkTJVoroOOgUFKHs/eRZcCr4h5wepxMnEwydFRzcbgS9apGbGfbiQi53J1Gbdw/
         7AOT+f/X5U75+DSwmgzz5t8Ajc2TOC/pfsbTecOT2eGEQwLlFuhDvIqNfpmPbBWRBjjs
         Ej+Q==
X-Gm-Message-State: AOAM533ioeCn5bms/yPJinPbQoutFAl1gOnP1UMgZ6Bh1bdJB4NBeQF5
        WsTDt0EkuBAsJ27EcwSED7rTL0mknfQ=
X-Google-Smtp-Source: 
 ABdhPJwsrMNhimh7AmIjFD12TWEarPGaBkgfFq8boNstUh+9CL4/MgCmE8I0BfiUI/DUb1PxHS2lTQ==
X-Received: by 2002:a17:902:7c8a:b029:e6:f010:a4f4 with SMTP id
 y10-20020a1709027c8ab02900e6f010a4f4mr27386180pll.17.1617697960930;
        Tue, 06 Apr 2021 01:32:40 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 u25sm17869165pgk.34.2021.04.06.01.32.37
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 06 Apr 2021 01:32:39 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Count success and invalid yields
Date: Tue,  6 Apr 2021 16:32:15 +0800
Message-Id: <1617697935-4158-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

To analyze some performance issues with lock contention and scheduling,
it is nice to know when directed yield are successful or failing.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/x86.c              | 26 ++++++++++++++++++++------
 2 files changed, 22 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86/mmu: preserve pending TLB flush across calls to kvm_tdp_mmu_zap_sp
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12185567
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ABA62C433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 16:25:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 71137613CC
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 16:25:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233255AbhDFQ0D (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 12:26:03 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:28933 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237498AbhDFQ0C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 12:26:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617726354;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=P7jEwhs3YhOUrc296WlQw+XsxeekSJAI8Ujivs9g9oE=;
        b=T9T2e1COY+9z8FeWseITXuevS+NHC1FE+VX1UhrlO5+6VuoTSgJ1vrRwZXO5oEV48E+urx
        KyucaSaI8wYSt7q9KTtAyKNo0tGc5SuHhoZmLrSMqHZLcUrkhZZpPIAmzGyd+dlg28ph/b
        IcDzUbONdY+1RvqCzZlC6EfKoUn60wo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-v_K6orFjMZOwmJxfQNqNzQ-1; Tue, 06 Apr 2021 12:25:52 -0400
X-MC-Unique: v_K6orFjMZOwmJxfQNqNzQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DE7E51005D4F;
        Tue,  6 Apr 2021 16:25:51 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 768F25D9DC;
        Tue,  6 Apr 2021 16:25:51 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, stable@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: preserve pending TLB flush across calls to
 kvm_tdp_mmu_zap_sp
Date: Tue,  6 Apr 2021 12:25:50 -0400
Message-Id: <20210406162550.3732490-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Right now, if a call to kvm_tdp_mmu_zap_sp returns false, the caller
will skip the TLB flush, which is wrong.  There are two ways to fix
it:

- since kvm_tdp_mmu_zap_sp will not yield and therefore will not flush
  the TLB itself, we could change the call to kvm_tdp_mmu_zap_sp to
  use "flush |= ..."

- or we can chain the flush argument through kvm_tdp_mmu_zap_sp down
  to __kvm_tdp_mmu_zap_gfn_range.

This patch does the former to simplify application to stable kernels.

Cc: seanjc@google.com
Fixes: 048f49809c526 ("KVM: x86/mmu: Ensure TLBs are flushed for TDP MMU during NX zapping")
Cc: <stable@vger.kernel.org> # 5.10.x: 048f49809c: KVM: x86/mmu: Ensure TLBs are flushed for TDP MMU during NX zapping
Cc: <stable@vger.kernel.org> # 5.10.x: 33a3164161: KVM: x86/mmu: Don't allow TDP MMU to yield when recovering NX pages
Cc: <stable@vger.kernel.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/mmu/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Remove unused function declaration
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12184259
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D19AC433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 06:35:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A7B36128B
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 06:35:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239459AbhDFGff (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 02:35:35 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:15484 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238603AbhDFGff (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 02:35:35 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FDyQJ5nhYzvQlY;
        Tue,  6 Apr 2021 14:33:12 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.498.0; Tue, 6 Apr 2021 14:35:13 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>
CC: <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>
Subject: [PATCH] KVM: x86: Remove unused function declaration
Date: Tue, 6 Apr 2021 14:35:04 +0800
Message-ID: <20210406063504.17552-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_mmu_slot_largepage_remove_write_access() is decared but not used,
just remove it.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/x86/include/asm/kvm_host.h | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v2 01/18] vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12185791
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F2A15C43460
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:40:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C3E67613DF
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:40:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235085AbhDFTk5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 15:40:57 -0400
Received: from mail-bn7nam10on2075.outbound.protection.outlook.com
 ([40.107.92.75]:17062
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S234185AbhDFTk4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 15:40:56 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=E2pB7Jmali0pSRayHDMfJ778tZc1x6b0LjIHvzTlkkuCFKG2xZ16tF3Lb9eNKSk5OeyeuzuTuud588XdUBRsv5E518apsZff5WgTdxSTGtMs0swZSEupdVWwYMJWXNMRYJ1amNIZQslsJp9hE/I52fzVcHG32fhEmSw08YhIIOx9I1pgr2jhZU2Sm66M1XA7zCZlvaXMRGKRM/1eOAQsO4S0egWhYvh+1bF6vQQF/3gCTLwv4PkTo1R/9a0dZ1IiE5FnXSlYdwX/EKG+AZ8emEdvbKfIuHIDb556tL9WlrnTgCZwNW9Zm06qWQlVUYg8RyE/T0w3TFwFwyEIHcB94Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jRKwuIDiB/9LGr712gfvhhC3/mHbTfvih7aqjvLh+bM=;
 b=Vi0Q/93dgJDy2+hp9qpDFopNl9vH+fEZBJQI/gBfhuJK65wO6UuxZEtp+Kt1Z3sRITsx12wlbsjDQKc3L6S+jv/3bPExQ6tyeFE9Tss9iuqT3WlxYmqMzMPG/LVavR+2U9byao/GYI6lUwUiia8wlDeSanKAOQ+2q2eIIki6zhk9MngzngI4qs6iVljQsGAAxy05qEx9v4CgL55v/CkCBY4hbjfS+QLqgTLLAiIXx1vVJAlHuucTfudyI/ecX1wUGH1mxvt1RHvLFt2eQxFZd3L9Xp7VWoP2TunxBz0uG0IG65vGsMKYRMmR7UkClKWoMp5nHcuPaJmj4jtiES7RNw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jRKwuIDiB/9LGr712gfvhhC3/mHbTfvih7aqjvLh+bM=;
 b=LgA5OokNvoKMOb/lci/6IcdwwlQfFWN9nF3UKbskGifWL1cCaTz2H31NxxTf6vj8VdkN9ul5WqttwCYNq/JSTCud6aU/cjJ/ml9GIPO8ZjToVZkHxf0N9dKCjLuOwTq8QnnSbaFVGfF7DLnjykEn05Wvg+qlsAAC5WSqSTB8BcIg44yYm/3jRj8jrMdczJtr2tC/LrCGMDmUCu471cS5hIBV6cyBpgrnizkf3iVMKW57rbc6sg7969F3o7nzPiXVTXMYtg9sAk6eD4v4zFyom9ZaE7SRXabxSAbKQreMwGrd3UrR/MXkm0+k7eDucZZH7Hhqo9lG+lU5GvXHPzCe7Q==
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB2859.namprd12.prod.outlook.com (2603:10b6:5:15d::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.27; Tue, 6 Apr
 2021 19:40:44 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3999.032; Tue, 6 Apr 2021
 19:40:43 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>,
        "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Gerd Hoffmann <kraxel@redhat.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v2 01/18] vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
Date: Tue,  6 Apr 2021 16:40:24 -0300
Message-Id: <1-v2-d36939638fc6+d54-vfio2_jgg@nvidia.com>
In-Reply-To: <0-v2-d36939638fc6+d54-vfio2_jgg@nvidia.com>
References: 
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: BL1PR13CA0281.namprd13.prod.outlook.com
 (2603:10b6:208:2bc::16) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0281.namprd13.prod.outlook.com (2603:10b6:208:2bc::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.8 via Frontend
 Transport; Tue, 6 Apr 2021 19:40:42 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lTrZ3-001mWr-SG; Tue, 06 Apr 2021 16:40:41 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 1d000c5f-37f3-444d-1d92-08d8f933dd9d
X-MS-TrafficTypeDiagnostic: DM6PR12MB2859:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB285999043B479196B49162A0C2769@DM6PR12MB2859.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:213;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Lf86X3ZS/gVWpOJJMzLJ/bdJ6R19Z8lwJOx4YBrVIhY5doZEmY3KonlBaQO9Ug82SHUH9uOXlCmis3pHA7/CZ+mtt6+Sgshj9APwD1CRQRqhsbkUy7BWDZ+ODVbY0sClRX6CiyZWr4KPas01erYrKwiUjWRvcQhL0dEXqv5xDQfnQVjr3wLTIqg41hhyGb1htGsMehnfbNRx7FleEeBvGOQWtAfaQZqs3Mo5lSDRxy+KufvVsUW8pywe6CTHdpX2rACXPilAhlc8kCnkQzrKtHUqNkqC8VdUcs0A20PMezne9fUCROLxUapcB5urEBPgW/WnIG+VcztJjGkdWsvvSNH4qZFjOUZP4rH7rNIDVYa5FNkgI1cQuBLeOhtAs3GtDsGAiSCIVvlGz0n34NZTpVKgYo/7npglP9VXcswNDZSYKE0kKGPuMdjBrN7h/UsdZ07aYYXansOmWCnj+77F6XqusYrvI+hjcBy/BqJZnzZrmTV5CDC/AWfUs0b+PLyw0aeeMXy4i3l43PPgEtrc8ZHBM5EloXAGu/XNmfJxFm1/53phabCteAl3xCZ1IG2USVF7CnforwhFfy/8wFh3sneG7Z+c9K9rZDlH1yIxjmh2O8LLPXJ9nH2qRqvifRGEYS5rBKH0YZ3q2eXUhgwKh++TLNhTqjmEd+dj/K5vCREkG8vYgQ3mln1/xUDugtzg
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(346002)(366004)(136003)(396003)(54906003)(86362001)(2616005)(26005)(8936002)(38100700001)(6862004)(66476007)(37006003)(426003)(66946007)(5660300002)(316002)(36756003)(66556008)(6636002)(2906002)(6666004)(107886003)(83380400001)(186003)(478600001)(4326008)(8676002)(9746002)(9786002)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 SgTnkydsReckRq+A6YCNPdgOaBlF5ozA+LRA43Lnt0CBwxDlnj2L82splB0BP/vhXD5Osbx+mjniJrfu9BZPPx1uSJDOHRp2dPsN4rpFiJ6Xc1WRtg1XqpPnNHrB+MCHzPXMT9YbpwP0eg9MAar/MEvcVt73tHhAFSpk9s5qNvSQY8bMmYy6vMC85ZEf/5MknTjMiPyMokIuROShvc/bAyOeKX6/NBaTqC/zOMncvv5Mtll8ZtUVzFbNJpenuXJqIm0LBcVUeBZNN0g7AoiDiDFu+vfX9iCbRL+InnKEy2trgCiaFZdS4TzN416PNUTb6CJJMJJzeXvCoz4uhVQwyBbWM+7faigPVleZWzjRDOkFDO9W7sXnRz28BOQ6zETTkV0xhRhJ2Mj9tBr3/Sss56bGpdNySzNq0UFPCfSePBO993tUk7eINubsTS67OYm5c0JUNjUjElRPehTkT+ZvkgLKCWa1jo5SQAFVwpaY0EbVkWfiQgMMQ/r0RF4R4TrZtsdrGe2cCcTNDel7gDQQT+oWub4zJZDa83Zm1biURD04DW1YgCBwadlwE0+Bc0WgjNRZW/2h8W5CM6Y1azFcp1nhi7RCbRi3xzrsJHUuBkWT36MVtfQl1gVWiuoIup1KsGJa9+57ADxZ8DvTmP0fF9cPBMEJMv8ckwyQ+/iB1pbT92+/UjVAvBAQ1aze37hokvLSbGWsjerZxAYKWh2wLMgMPBhMsexHOPHtLVyPOta4KrEULSL8sc9l9EOvtke/A12R5b5VvvV76p/thCv03VN4wn50zW6qZYaZXVdLKGIE/zuwfzy/4op5gC2RnqykmvxJiT9SY2V3CwfQJ//aa58qZ2ttSuqNbYftiLYfBgut2ECIlnQld80e3VdmdaVufHLKfxUSx9FvUUzP8UHa+ecB0Gr+ahfhuNs/xj69PjmjgbudQG0G/s9z4WH8zKrBj8dUyjNy+v3AeP8CGjUUyxQ0+IQT8FMvYnud1viO99vv56OBrxDBQ53jea+CxtTVXsS2tmsAdX3ssBRhAuphaozVRaTlM7P76z4x51wmaN62CdaRUprz9yuI1KxLvxrJu7qfUBmP376Cj/ODrD+TiXN7aHG8/wJ+QE6mq9sMHwE8TrCKt1JLBveEIZ4Uo2zbc4urhpKE1xtaa6XLxvkeV6hizcfJUDlltXjDWYxQ/DIxzfQqd07U+qY0wpRG0HGY0E3wd+zUmvbawe71bGJZd+if/gKKklU9GSgJqT8L44Ed0//1PLd51ZOpg29EKPYFD4CVrFsI+xTmBhsIbMTi9dcAwsOTezGDk2hb+UHDQN52k5OBrcaJORpKhRvswq3/dfv2tBzFdGPDA8XwCKhxig==
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 1d000c5f-37f3-444d-1d92-08d8f933dd9d
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 06 Apr 2021 19:40:43.2633
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 2I37RVnG7WQLnzLcEEtFKkCCPsERgX1+qDOE7nChPE4EpeGvUUbyB9tqo59c8HFM
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2859
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These should always be prefixed with static, otherwise compilation
will fail on non-modular builds with

ld: samples/vfio-mdev/mbochs.o:(.data+0x2e0): multiple definition of `mdev_type_attr_name'; samples/vfio-mdev/mdpy.o:(.data+0x240): first defined here

Fixes: a5e6e6505f38 ("sample: vfio bochs vbe display (host device for bochs-drm)")
Fixes: d61fc96f47fd ("sample: vfio mdev display - host device")
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 samples/vfio-mdev/mbochs.c | 10 +++++-----
 samples/vfio-mdev/mdpy.c   | 10 +++++-----
 2 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH v4 1/3] Linux headers: update from 5.12-rc3
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12184179
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E7B60C433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 05:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD14B613AD
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 05:39:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231852AbhDFFju (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 01:39:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10772 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232892AbhDFFjs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 01:39:48 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 1365X6NN109912;
        Tue, 6 Apr 2021 01:39:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XH41vIKQPXVPDTcuOx2GPyt+VwfndhJWpB7omC2dJ1U=;
 b=AlEGyS35hsdgs2+8ZO6UBBo4Fp8ZsSXNoG74eO0oRh7R3GQ+LKiNSXq9CsCBer6y8gZB
 T0f0lLUBeksO7sDmqTqr6nrIM5dVZOq8hDXz6asgOUJEGD96SFeTUcgQQikUHKV5LfkW
 yh/DFhUYRst8K36si5BDL7xx5MtsC2/tsQHdSAaKuqw3Iev3zeYG9CLD4C9czpPY9daM
 DN84njMyXbodisGSxfKaFgNDnqALHOIhN04ag8vVbIn31BGC/rIfjbvOsXjlzM014yzl
 n5P9Z37qci0aZuCq/5CgmCMoNttcOjKd1vmQs2JyjfHFqcBQxlc041DkrjovufJkhwQ/ FA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5kxfsbj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 01:39:16 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 1365YElG113166;
        Tue, 6 Apr 2021 01:39:16 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5kxfsau-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 01:39:16 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 1365avXP028929;
        Tue, 6 Apr 2021 05:39:14 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 37q2y9hu30-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 05:39:14 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 1365dBSF28115212
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 05:39:12 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D04DA5205A;
        Tue,  6 Apr 2021 05:39:11 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.40.1])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 9F9A35204F;
        Tue,  6 Apr 2021 05:39:08 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com, groug@kaod.org
Subject: [PATCH v4 1/3] Linux headers: update from 5.12-rc3
Date: Tue,  6 Apr 2021 11:08:31 +0530
Message-Id: <20210406053833.282907-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210406053833.282907-1-ravi.bangoria@linux.ibm.com>
References: <20210406053833.282907-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: h-AhuoaNyWOvfuB4TmbfDz9_9jNLQCu6
X-Proofpoint-GUID: QelGOR3lkd04-iqgpIxTmXgAg3cmu3Ei
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_01:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 mlxlogscore=999 suspectscore=0 phishscore=0 lowpriorityscore=0
 malwarescore=0 mlxscore=0 priorityscore=1501 spamscore=0 clxscore=1015
 bulkscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104030000 definitions=main-2104060037
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update against Linux 5.12-rc3

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 18 files changed, 161 insertions(+), 4 deletions(-)

```
#### [PATCH v15 01/13] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12185479
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BF2AEC43460
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 15:31:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 95A226139C
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 15:31:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1345715AbhDFPb4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 11:31:56 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:56512 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1345688AbhDFPbu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 11:31:50 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 136F8kZQ110125;
        Tue, 6 Apr 2021 11:31:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=eddZYayLgbK9LT7a0g2otyK+KzhpC5hr6wrwydXZlus=;
 b=O2YDa2BvMEAxVsU63EhvskycOfHtSYqbBMU1uAOjDZb0fGTot5TsSC2EY8eo7bOz4NAo
 4GA4I3jAsPW2rA/aiz1z7rs5kqqqSfEJAQAFpiVehwEDBxAjFtq/cqEXh5wkqlFJzewL
 NRFU6vE8ktICDOqGdqGZv3ILEl0yxGJevnRfCpZIX5yQKW2EU1WR19mM5ojISKt0lpvF
 clyZSj+hvwm3fdqNYRCPnUqmQ2zkH7750FMmHKE+MfWTSuqyN50IfSY60MQdCUFCBP0C
 Y+mR7NHAn2yiWjP1DQbZ8kQthxRo4p4WR/Ng+QChpOTLchI4Zh5ydP0d5WYNM4QJvNTa Zg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37q5eb6dax-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 11:31:40 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 136FFYxY129710;
        Tue, 6 Apr 2021 11:31:39 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37q5eb6da9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 11:31:39 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 136FM3x5002596;
        Tue, 6 Apr 2021 15:31:39 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma01wdc.us.ibm.com with ESMTP id 37q2q90r3q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 15:31:37 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 136FVYGP31982060
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 15:31:34 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5CB22BE053;
        Tue,  6 Apr 2021 15:31:34 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AF922BE051;
        Tue,  6 Apr 2021 15:31:32 +0000 (GMT)
Received: from cpe-172-100-182-241.stny.res.rr.com.com (unknown
 [9.85.175.110])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue,  6 Apr 2021 15:31:32 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>, stable@vger.kernel.org
Subject: [PATCH v15 01/13] s390/vfio-ap: fix circular lockdep when
 setting/clearing crypto masks
Date: Tue,  6 Apr 2021 11:31:10 -0400
Message-Id: <20210406153122.22874-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20210406153122.22874-1-akrowiak@linux.ibm.com>
References: <20210406153122.22874-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: Sol9zDNYMd2TtVmicGXzBOJytPz6ZBx8
X-Proofpoint-ORIG-GUID: G2er4JRwIL5Bu0R5W34c0tY6B-g_EtYP
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_04:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 priorityscore=1501 mlxscore=0 suspectscore=0 adultscore=0 phishscore=0
 bulkscore=0 mlxlogscore=999 clxscore=1015 spamscore=0 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104030000 definitions=main-2104060102
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
 drivers/s390/crypto/vfio_ap_ops.c     | 308 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 95 deletions(-)

```
#### [kvm-unit-tests PATCH v3 01/16] s390x: lib: css: disabling a subchannel
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12184395
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 936A2C433B4
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 07:41:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5412061241
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 07:41:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236431AbhDFHlK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 03:41:10 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:59216 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235371AbhDFHlI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 6 Apr 2021 03:41:08 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 1367Xn7T060651
        for <kvm@vger.kernel.org>; Tue, 6 Apr 2021 03:41:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=F/E0Lol3oE0vyXaaKVcHWp+H0qjNkRNBGzpkt+iBzmA=;
 b=AGMMOCJiRwa0lCaWSYt53l2ykXnqzMi1wA6pCyw/7DtVNfHICLsfOh/cYljAyi3mBghF
 BJLsT6cuInJM+b/uKZ2uc3a0gsYyxf6Ap843Xgfq0BlmoZQeiIKbW00Ea6l5N7NLDt40
 hgpFKG5ZXlPcHkAf9S2IB+EzqLSTZqI5PoUXQGzKgS2n4A5DlOt9QN0A6YQ2YqmrcM+l
 JAzWmD924luUlnjdTs37eJZ90Pit/DB/16jymq7yCpbsUjwgLckcCJGgeBJNFML3LuZZ
 NvCGN6XVePLy0AyowcibCBQHBXtroU8CLLdtmGm1Yj9KfTe1v9OAlcmdB1t6t7aU3YBz bA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5bys1m1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 03:41:01 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 1367euK6086779
        for <kvm@vger.kernel.org>; Tue, 6 Apr 2021 03:41:00 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37q5bys1kb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 03:41:00 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 1367Wm3x026067;
        Tue, 6 Apr 2021 07:40:58 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 37q2q5hwxr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 06 Apr 2021 07:40:58 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 1367etMQ32964958
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 6 Apr 2021 07:40:55 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 575904C040;
        Tue,  6 Apr 2021 07:40:55 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0B2C74C044;
        Tue,  6 Apr 2021 07:40:55 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.42.152])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  6 Apr 2021 07:40:54 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3 01/16] s390x: lib: css: disabling a
 subchannel
Date: Tue,  6 Apr 2021 09:40:38 +0200
Message-Id: <1617694853-6881-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1617694853-6881-1-git-send-email-pmorel@linux.ibm.com>
References: <1617694853-6881-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: Zv0kPxqqPypSp-oIKEzkFN0NONL3C7Gv
X-Proofpoint-ORIG-GUID: l-UEWGU4iqbkeSrLg28CJWoa9UQnh2vF
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-04-06_01:2021-04-01,2021-04-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 impostorscore=0
 mlxlogscore=999 priorityscore=1501 mlxscore=0 malwarescore=0
 lowpriorityscore=0 adultscore=0 phishscore=0 bulkscore=0 suspectscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104030000 definitions=main-2104060050
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some tests require to disable a subchannel.
Let's implement the css_disable() function.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/css.h     |  1 +
 lib/s390x/css_lib.c | 63 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 64 insertions(+)

```
#### [PATCH v1] vfio/type1: Remove the almost unused check in vfio_iommu_type1_unpin_pages
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12185337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 751DAC433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 13:50:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4966661246
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 13:50:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1344712AbhDFNuf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 09:50:35 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:16001 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S244186AbhDFNue (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 09:50:34 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FF83b4Yz0zPnX8;
        Tue,  6 Apr 2021 21:47:39 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.498.0; Tue, 6 Apr 2021 21:50:18 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v1] vfio/type1: Remove the almost unused check in
 vfio_iommu_type1_unpin_pages
Date: Tue, 6 Apr 2021 21:50:09 +0800
Message-ID: <20210406135009.1707-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The check i > npage at the end of vfio_iommu_type1_unpin_pages is unused
unless npage < 0, but if npage < 0, this function will return npage, which
should return -EINVAL instead. So let's just check the parameter npage at
the start of the function. By the way, replace unpin_exit with break.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: Explicitly use GFP_KERNEL_ACCOUNT for 'struct kvm_vcpu' allocations
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12185765
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3735C433ED
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:07:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D299613D5
	for <kvm@archiver.kernel.org>; Tue,  6 Apr 2021 19:07:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237341AbhDFTH4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 6 Apr 2021 15:07:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48258 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235663AbhDFTHy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Apr 2021 15:07:54 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EC2F0C061756
        for <kvm@vger.kernel.org>; Tue,  6 Apr 2021 12:07:44 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id h26so10747375qtm.13
        for <kvm@vger.kernel.org>; Tue, 06 Apr 2021 12:07:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=+A1SrmIwbZ1FSLGZhqe9uQgP9D/HiOqOM3+S6Gii/38=;
        b=PgvSfT+fXAh6dZEtkAl7gx/WHOeTCqQmX9nUeKPm/cvqfkmjneuEeb4Kp9aufNpibv
         Aumvo4Kbq52Wf9hTPWAWx6K9Y+OXz39yEgrMsoRIGgovP3A1H169jn13Gx3bKnxsWKkw
         fYwaUSyabMe37APColz5hhdt06HPXCkIg5JacdurEnfK37fY04fAKmA1q64wLGOpkqNp
         Dl4ksebaI8Gyg6yRIj16m4EPJH0o5kefoVuDxjYrX3Ow7hOtiD1aW5PmZJxT0bW6fP7n
         wybt+5efodRRVUwe0h3DRFZkGfPEa2SXu6QE4ecAvNAbtdQ3vMAyvJjW2N9Wbk8JqZjp
         /zBA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=+A1SrmIwbZ1FSLGZhqe9uQgP9D/HiOqOM3+S6Gii/38=;
        b=clCq7uYg6zNkciDWA59Cp6bp+NVGs1qWao60KjhOfuoQTYRL6kT1+luT28u4vj/Sz+
         de3ENRWhbkCPoFZvFQF+41Qbek0oaaunDbz28/eeKhFcxq1m/QXlsMedeS52g5lW3qP+
         +ZXZeRh8UnsaTxNvUz6Laj2HNxZBRtg6jB33wbMq6OrzRVDCxvOx5/yVwPRknbIiS3Qn
         HxHs9RqueN7tBGOG8qtKTmpyS7NXRhdKtnsxlJ08w+6xC9i95FciSJweKqBZ87LH21ja
         XX2VimpWmt0ehlBmJR+ZX7E91w1MnP1NSy5tpzSvFdUhJDDrPtNH8VoyaYXaGOOetTqM
         3gXQ==
X-Gm-Message-State: AOAM531H7O4tzP4s0filMm3F1AoLmv0dMWcKE4D0Ru9pjCsTDEjASj5V
        gNBukTvIb5BAHHpucg0lNmLGNSUX5w8=
X-Google-Smtp-Source: 
 ABdhPJy2JLGhNT9+ISmHitMjw/KB5xcpDEWYnlaJYLIyRoj+RvbqxxoOq7PeaACZwl0qjuByKmf1yiR7pFw=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:24a1:90fb:182b:777c])
 (user=seanjc job=sendgmr) by 2002:ad4:4e4e:: with SMTP id
 eb14mr14413638qvb.14.1617736064053;
 Tue, 06 Apr 2021 12:07:44 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  6 Apr 2021 12:07:40 -0700
Message-Id: <20210406190740.4055679-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.208.g409f899ff0-goog
Subject: [PATCH v2] KVM: Explicitly use GFP_KERNEL_ACCOUNT for 'struct
 kvm_vcpu' allocations
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Wanpeng Li <kernellwp@gmail.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use GFP_KERNEL_ACCOUNT when allocating vCPUs to make it more obvious that
that the allocations are accounted, to make it easier to audit KVM's
allocations in the future, and to be consistent with other cache usage in
KVM.

When using SLAB/SLUB, this is a nop as the cache itself is created with
SLAB_ACCOUNT.

When using SLOB, there are caveats within caveats.  SLOB doesn't honor
SLAB_ACCOUNT, so passing GFP_KERNEL_ACCOUNT will result in vCPU
allocations now being accounted.   But, even that depends on internal
SLOB details as SLOB will only go to the page allocator when its cache is
depleted.  That just happens to be extremely likely for vCPUs because the
size of kvm_vcpu is larger than the a page for almost all combinations of
architecture and page size.  Whether or not the SLOB behavior is by
design is unknown; it's just as likely that no SLOB users care about
accounding and so no one has bothered to implemented support in SLOB.
Regardless, accounting vCPU allocations will not break SLOB+KVM+cgroup
users, if any exist.

Cc: Wanpeng Li <kernellwp@gmail.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

v2: Drop the Fixes tag and rewrite the changelog since this is a nop when
    using SLUB or SLAB. [Wanpeng]

 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
