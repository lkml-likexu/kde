#### [PATCH 01/13] KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12007821
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 816BBC433E0
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 00:48:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D2F923AC0
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 00:48:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726469AbhAIAsT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 19:48:19 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39876 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726120AbhAIAsS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 19:48:18 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E5E4C061757
        for <kvm@vger.kernel.org>; Fri,  8 Jan 2021 16:47:38 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id k7so17298169ybm.13
        for <kvm@vger.kernel.org>; Fri, 08 Jan 2021 16:47:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=vDh4eKmFYAmn/pACCaUYHAK8byzvJFHct+dqDkZvWfA=;
        b=Ab+7KA0qdYGMnAlMWUILK6GjCUGeaAGIXD1IgpqBsA+n84nWw3Hu9UJnAsDhcSgg/E
         vJOCJ/HYzKN3TK4VsDF1VD7KLG8mLeDQRhDcT/kpC2PCxVmj2Z7uaDzGYH5nX5ZdUMZf
         XpVCD90r9FJ+UE30VWduFe/RfljbpsZsnAfgsv7S0aiICdA3UzSwRxKpPUpuj9e+5Y9V
         6prkzbU2veqaKHV6H7tNxm/EMvVW2ciZFiXMxv65XkiRkO7M3shcIHwtk6Buxg1s6qzM
         ZCQLN2K5UHdNrLG4UL2Ouikn2MEiZVvNbSExcgR501mWeMJRWw3BtRLva4c5x2SnJLr1
         wn2A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=vDh4eKmFYAmn/pACCaUYHAK8byzvJFHct+dqDkZvWfA=;
        b=fQdRWMSqJLNF1PpDidFy/ub2eUwu+MVjZQw9UnzZnrbiY2ZH8B2dIlI2rmFmKKh5rr
         8DUnUBTNlYS1UZMBu3xtjdsqSG+kJKII5tGOqyfrtfEP1Ab6kaFQoc12We5UqACWHmc3
         5IF+hZnx2gwnOGEuaV6rVUmYt6REZZj6CXJ5528LST+SoqAsGog9bAXCFQZwuLx+Byc7
         ENCNhs+B8AzkINtQppiNlbS7pS30SM9P6c1lkgWg0l+fagTOFWU7uSxXomw3CBpqtw20
         PwflK9obekXeRVaI8TO4qCP1INiPD0ucMjj8nj/2OD83telKNjv8LUWbf3kfqphnaxBu
         djkQ==
X-Gm-Message-State: AOAM5304bhUwz2ZHGlgl3+Brods/eaiCjGvbyUu31GqBscjwAE/VvWxt
        u7lrSgAm6utgmFHn9tDp0Yr0ato9xRg=
X-Google-Smtp-Source: 
 ABdhPJzFpFPedRE22hMJwVQdeGOf/7DAB6URy8FyAahzhV7B7CbCorTQlmBb0br5xFhkKkBa7AoYbUOolUU=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a05:6902:6d4:: with SMTP id
 m20mr9411689ybt.434.1610153257450; Fri, 08 Jan 2021 16:47:37 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  8 Jan 2021 16:47:02 -0800
In-Reply-To: <20210109004714.1341275-1-seanjc@google.com>
Message-Id: <20210109004714.1341275-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210109004714.1341275-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 01/13] KVM: SVM: Free sev_asid_bitmap during init if SEV setup
 fails
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Borislav Petkov <bp@suse.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Free sev_asid_bitmap if the reclaim bitmap allocation fails, othwerise
it will be leaked as sev_hardware_teardown() frees the bitmaps if and
only if SEV is fully enabled (which obviously isn't the case if SEV
setup fails).

Fixes: 33af3a7ef9e6 ("KVM: SVM: Reduce WBINVD/DF_FLUSH invocations")
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/sev.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: x86: Mark __kvm_vcpu_halt() as static
##### From: Souptick Joarder <jrdr.linux@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Souptick Joarder <jrdr.linux@gmail.com>
X-Patchwork-Id: 12007907
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1717C433E0
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 03:10:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 624A223A82
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 03:10:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726363AbhAIDKT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 22:10:19 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42002 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725836AbhAIDKT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 22:10:19 -0500
Received: from mail-pl1-x634.google.com (mail-pl1-x634.google.com
 [IPv6:2607:f8b0:4864:20::634])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D0403C061573;
        Fri,  8 Jan 2021 19:09:38 -0800 (PST)
Received: by mail-pl1-x634.google.com with SMTP id j1so6689141pld.3;
        Fri, 08 Jan 2021 19:09:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=fQoQ591DRcLcx1zBs38ERO9HILV+4vRtO0mx9yq+xxk=;
        b=tK95k3WSzIGI2ktKiBx/Yc2pT7JqIGFuxCw9xB4BZuzRqqVyOjo5wqbw2kJa+N9TAj
         3QTR1pST+DQNZBN4e/mKgdsIH2xNsWQ+yShoDArGGiLmot5XUFUTOffPFVRSxiAghoKc
         XiJ3KGdV/Eoe7t9BN/4LTx90ecVcH0u6p22e1EqURknTRS01ft2TW9oq/qCq3ggKdWfQ
         HC0nOPLfqpZH7PErVqqQHy1TRcromD8X3xGDHWmfZdQqABwFQMXP6Spl+T9kcbRTjCZx
         425ZxzG7mEYTpG1/l+aFIf58+fl75ExTQMgtrrkBMc9BjIYBhMXcizVYShC6zQkLIDrH
         zASA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=fQoQ591DRcLcx1zBs38ERO9HILV+4vRtO0mx9yq+xxk=;
        b=HfEn/G611Ix6hH6eAEYpsuKAK+8diz1oj/vbhJSkmrmP/mINSaawb345clTqICsT1L
         eOTVU6M/OVecxsQfn0s3DHXnmHQc5Cg1/BkuUieDhdX1p/MFiuI7vRfjP5i19UogwOnd
         POVafrX61N6Wedn7IGq9PmDAiLLxIzV/wmM8e+gsLBte07fgOMss71P7ynILsP5mMR+V
         FICJXS7zqcGfTFSOKXkdeOirrY1QtKTCI+jmCZWy2pYyAV7YUrCTIg7MdsvPae4ba7CL
         ityOTj3UOL7ZqOyzaniRbHfsrmmrLsQKIcfTdpMyc72NRNMSoqFEg4sLCPY1HCmBNDAH
         KvgQ==
X-Gm-Message-State: AOAM533ESsJqMKh6ce3bwnemkBTnkbAHhi1TuSXSP1g8ybkGatsX2ogP
        dP5HuwHD0ddOQ0DeFdvW+bE=
X-Google-Smtp-Source: 
 ABdhPJzZtqIcJB2oop8heybvKQtx+XyKUJjT/k/OeanQ/dLSyo21ZUmO1VK/VMQtHgGn5L0F/j8NqA==
X-Received: by 2002:a17:90a:2ec1:: with SMTP id
 h1mr7034337pjs.18.1610161778311;
        Fri, 08 Jan 2021 19:09:38 -0800 (PST)
Received: from jordon-HP-15-Notebook-PC.domain.name ([122.171.171.27])
        by smtp.gmail.com with ESMTPSA id
 9sm10258074pfn.188.2021.01.08.19.09.34
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 08 Jan 2021 19:09:37 -0800 (PST)
From: Souptick Joarder <jrdr.linux@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Souptick Joarder <jrdr.linux@gmail.com>
Subject: [PATCH] kvm: x86: Mark __kvm_vcpu_halt() as static
Date: Sat,  9 Jan 2021 08:39:32 +0530
Message-Id: <1610161772-5144-1-git-send-email-jrdr.linux@gmail.com>
X-Mailer: git-send-email 1.9.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Kernel test robot throws below warning ->

>> arch/x86/kvm/x86.c:7979:5: warning: no previous prototype for
>> '__kvm_vcpu_halt' [-Wmissing-prototypes]
    7979 | int __kvm_vcpu_halt(struct kvm_vcpu *vcpu, int state, int
reason)
         |     ^~~~~~~~~~~~~~~

Marking __kvm_vcpu_halt() as static as it is used inside this file.

Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Souptick Joarder <jrdr.linux@gmail.com>
---
 arch/x86/kvm/x86.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
