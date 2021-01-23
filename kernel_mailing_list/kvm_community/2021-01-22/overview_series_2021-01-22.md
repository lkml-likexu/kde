#### [PATCH] KVM: nSVM: Assign boolean values to a bool variable
##### From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Li <abaci-bugfix@linux.alibaba.com>
X-Patchwork-Id: 12038295
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C14BC433E0
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 03:51:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF9CA22CAE
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 03:51:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726698AbhAVDuo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 22:50:44 -0500
Received: from out30-43.freemail.mail.aliyun.com ([115.124.30.43]:50331 "EHLO
        out30-43.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726030AbhAVDum (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 22:50:42 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R111e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=alimailimapcm10staff010182156082;MF=abaci-bugfix@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0UMUXRqj_1611287391;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:abaci-bugfix@linux.alibaba.com
 fp:SMTPD_---0UMUXRqj_1611287391)
          by smtp.aliyun-inc.com(127.0.0.1);
          Fri, 22 Jan 2021 11:49:56 +0800
From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
Subject: [PATCH] KVM: nSVM: Assign boolean values to a bool variable
Date: Fri, 22 Jan 2021 11:49:49 +0800
Message-Id: <1611287389-63591-1-git-send-email-abaci-bugfix@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warnings:

./arch/x86/kvm/svm/nested.c:752:2-32: WARNING: Assignment of
0/1 to bool variable.

./arch/x86/kvm/svm/nested.c:545:1-31: WARNING: Assignment of
0/1 to bool variable.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
---
 arch/x86/kvm/svm/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 01/13] KVM: SVM: Zero out the VMCB array used to track SEV ASID association
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12040415
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 000E3C433DB
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:24:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B215E23AFC
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:24:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730556AbhAVUYF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 15:24:05 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43530 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729227AbhAVUWf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 15:22:35 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B5F22C061788
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:21:54 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id g14so1685432qtu.13
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:21:54 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=na/73VMReTKtB9cBdzddT3dFufGs+FA2GpJ7zLFbNE0=;
        b=sR2mbkVcciaudaJO/zw/eEvj6Q7oBcRY0RAz4GWPIa6JEVX53Nzqlr8lncX51w1OwK
         NO1X6XCfd3jEzWpq6fGB2xVpt0Lg6NZcjz2/R7NlryJ1+POAaxFG/hxOvp9Of1+tWHHq
         imVj9l7I3JWun1lRk8K91cV3TZnqClWXRT6UYWdr/jxAI6FEGrGPoeDDnnk0qfzZKzA1
         kPQH9v+FcflIEL/D2/uwmccwELlbDWP59fh3wzE3ZQKsYfA2sunWnE9ge3/KoioYRyj8
         EE7Za1PS9leb0CUYRu8NGP+oDsMzNXNCg9pfBLIiFwlKXdGt1L+Clc0cRZH8UcWJxMam
         quJg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=na/73VMReTKtB9cBdzddT3dFufGs+FA2GpJ7zLFbNE0=;
        b=foxT6pm3PD8JssrnZprjBv6KOMRYDoyYwH1VKHrjnRlhMPAJf6JvO2tBXBmU1bxVQ4
         sOabOxsqcm3FIeO+0/6HvyaowpkwvddsW4SzMtv44m5djZf+7rTPrxpi/JHPt3rAFdF6
         cbtHSZOQtb0Y85fT0M+upw5WiRZbHXoDF8brPL4jYsmxqT7PfqLGJgosbfqiX9ZZNCEY
         /Faoy7DYpQijw3sPbZfhSR1uHLaYo1OBBrmF9BWQoA6IBvzwCZ9aIXLzFElw6N4UPdRh
         YLYDSEyZpUXSugejWD7FX0V+XMVGHj9fOZtO4VJ4dmgTY/zX5mH5RVbJlmVrs5kNyQIy
         qxPg==
X-Gm-Message-State: AOAM532hlZRe8i7mud+XcYdq+DYD23FmViE3dpPqN3+fAFpzafLWPna0
        q0S62rad6A8wY1V4GxOPr+FsWA6gMkk=
X-Google-Smtp-Source: 
 ABdhPJxpMPloC8ZCgmz7TNLfHDME7K98h9vup115ZsV8cJ44FAIvocqZSyO1jCbESrt7ZIEvDB6U30Llk7o=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a0c:becc:: with SMTP id
 f12mr2470648qvj.31.1611346913861;
 Fri, 22 Jan 2021 12:21:53 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 22 Jan 2021 12:21:32 -0800
In-Reply-To: <20210122202144.2756381-1-seanjc@google.com>
Message-Id: <20210122202144.2756381-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210122202144.2756381-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH v3 01/13] KVM: SVM: Zero out the VMCB array used to track SEV
 ASID association
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
        linux-kernel@vger.kernel.org, Borislav Petkov <bp@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Zero out the array of VMCB pointers so that pre_sev_run() won't see
garbage when querying the array to detect when an SEV ASID is being
associated with a new VMCB.  In practice, reading random values is all
but guaranteed to be benign as a false negative (which is extremely
unlikely on its own) can only happen on CPU0 on the first VMRUN and would
only cause KVM to skip the ASID flush.  For anything bad to happen, a
previous instance of KVM would have to exit without flushing the ASID,
_and_ KVM would have to not flush the ASID at any time while building the
new SEV guest.

Cc: Borislav Petkov <bp@suse.de>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Fixes: 70cd94e60c73 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86/mmu: improve robustness of some functions
##### From: Stephen Zhang <stephenzhangzsd@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Zhang <stephenzhangzsd@gmail.com>
X-Patchwork-Id: 12039011
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E35FCC433DB
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:21:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A7E9222DBF
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:21:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728025AbhAVLV0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 06:21:26 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39420 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727932AbhAVLUC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 06:20:02 -0500
Received: from mail-pg1-x52c.google.com (mail-pg1-x52c.google.com
 [IPv6:2607:f8b0:4864:20::52c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73634C06174A;
        Fri, 22 Jan 2021 03:19:00 -0800 (PST)
Received: by mail-pg1-x52c.google.com with SMTP id n25so3507577pgb.0;
        Fri, 22 Jan 2021 03:19:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=JGKZWLmZIaXZ0doM/i8zUq2DXA6jM2XCESou+2RqdlA=;
        b=U9yV8Yulx/4LOhdsH7ynYOJKlnHwgwg2gMNl2QmmOTdT2tXgaaTXyhz8Tsml3tOEI5
         NqIdEY5+dNecnL9gupHRda8nYiv+OW4nvNKnLT6Dq+X3ZkLGC8/E+0VZYGhY1dbkhYEN
         VOsxBgysdG2KezeTn7tT6XkKT0lIR7UGv+iJaLJUzp0ndVsuKPFtp/5rucVWHFJIqMBG
         lCJZhDO2/4aGnckrimgPqZqRgz4+ApEwe+G0Pc/n+0YXPtsinnrnRi9iiummaI1pV/s1
         AUT0pvOzYe7nCUBVWVV9nBoPqpWoxqK0oZN3V53Nba+h/xg4a9H0inJ1LY1LNddb1SlQ
         HU7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=JGKZWLmZIaXZ0doM/i8zUq2DXA6jM2XCESou+2RqdlA=;
        b=Uy+OiqCguEqGGA6OmoSPB8by08QGMss3ylT5bAEmJYUj5+5PT+WO6B/PUG8CYhaLtq
         //mtkyef0vAgCvd1Zh4798EYdIhGM2CjLu2iza0XxVpx221YGhw4oBftRRYp6YdPX/I7
         8kcUDNNPkkosKukmUEWG8bPssiF94GN2oX95eH2217E0RSc+nxJvZ7uTVTnlepPyMmZ5
         Z5MyEe7K+zLoV50PSh5JCDER6lC35wd9qEgaG+Xy2t6pNJ+8ZZRET8ZJGATbM1/5iSNb
         IH+0eq8ftEOKX5mWon6KMrg+Wt0YI15fY50f+HB4+5zerdoS8l+ZlrW4jB3RWCeEbFE1
         F0Pg==
X-Gm-Message-State: AOAM5320ebavQrORY7BrGU43Ohcat2DPslHBvV3GZXxWBL5E2StEoMbK
        +HRWPvDDAAY1J1Z6S1zIGaM=
X-Google-Smtp-Source: 
 ABdhPJxt5WMLt8cj+0AiYX17C2BZ/R9+T6CBaCic2Kf+mk6e10AqboFT0NLkQr2VDIJKC+o4k9vfog==
X-Received: by 2002:a63:794a:: with SMTP id u71mr4170608pgc.91.1611314340094;
        Fri, 22 Jan 2021 03:19:00 -0800 (PST)
Received: from localhost.localdomain ([125.227.22.95])
        by smtp.gmail.com with ESMTPSA id
 b11sm9521965pjg.27.2021.01.22.03.18.55
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 22 Jan 2021 03:18:59 -0800 (PST)
From: Stephen Zhang <stephenzhangzsd@gmail.com>
To: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Stephen Zhang <stephenzhangzsd@gmail.com>
Subject: [PATCH] KVM: x86/mmu: improve robustness of some functions
Date: Fri, 22 Jan 2021 19:18:43 +0800
Message-Id: <1611314323-2770-1-git-send-email-stephenzhangzsd@gmail.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the name of this function changes, you can easily
forget to modify the code in the corresponding place.
In fact, such errors already exist in spte_write_protect
 and spte_clear_dirty.

Signed-off-by: Stephen Zhang <stephenzhangzsd@gmail.com>
---
 arch/x86/kvm/mmu/mmu.c | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [RFC PATCH] kvm: arm64: Try stage2 block mapping for host device MMIO
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12038727
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7C6C7C4332E
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 09:23:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4488F239D4
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 09:23:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727098AbhAVIjx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 03:39:53 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11179 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727125AbhAVIiC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 03:38:02 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DMXdn4gT6zl8Rv;
        Fri, 22 Jan 2021 16:35:41 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Fri, 22 Jan 2021 16:37:01 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Will Deacon <will@kernel.org>,
        Marc Zyngier <maz@kernel.org>,
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
Subject: [RFC PATCH] kvm: arm64: Try stage2 block mapping for host device MMIO
Date: Fri, 22 Jan 2021 16:36:50 +0800
Message-ID: <20210122083650.21812-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MMIO region of a device maybe huge (GB level), try to use block
mapping in stage2 to speedup both map and unmap.

Especially for unmap, it performs TLBI right after each invalidation
of PTE. If all mapping is of PAGE_SIZE, it takes much time to handle
GB level range.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/include/asm/kvm_pgtable.h | 11 +++++++++++
 arch/arm64/kvm/hyp/pgtable.c         | 15 +++++++++++++++
 arch/arm64/kvm/mmu.c                 | 12 ++++++++----
 3 files changed, 34 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v5 1/3] s390x: pv: implement routine to share/unshare memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12039445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 17BC1C433E6
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 13:29:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCE1323437
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 13:29:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727882AbhAVN3K (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 08:29:10 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:19292 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727748AbhAVN2q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 22 Jan 2021 08:28:46 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10MD2NhR156136;
        Fri, 22 Jan 2021 08:27:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=IyKWwa0SIbFuGT3BagTy9vBpsnez7BJALMQ5s9Sn1Ks=;
 b=GTDPGgR+P7oMwI6evklvrnYS95tI+vcaT30uQnjXVvAUX9VhBAyjab3eEptac1E6vBiv
 k1uzXTe6DelGecAXdpLO3/igWtnO+CZSkqdEDOxBYVg3/lUnK0HcfOBb1Tsnym8VoTI1
 e33G4R8afjTuFSqrfHcL3N7+wOBEEUHQEd/S2jmF8t15LEj2WT+lxYzhrRs99wGPn4Td
 Ex6N7z1l4g3R9EnQRTL2x8tgQXGP1ZwxEGHSCZu2BYqnJ+EGfMuj+d0IPm6oEBXeFV2F
 jswx+tHFsDMp4rEDEFG90kmitkxEk8qLTO9jMah1r2c/+BnhIAjHJblpgSmDyfVVYwnN rA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 367xgu29ca-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10MD2P5R156345;
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 367xgu29bu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 08:27:48 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10MDRfFU017570;
        Fri, 22 Jan 2021 13:27:46 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06fra.de.ibm.com with ESMTP id 367k10ra9p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 22 Jan 2021 13:27:46 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10MDRhGp46989600
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 22 Jan 2021 13:27:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 48110A4057;
        Fri, 22 Jan 2021 13:27:43 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C7D5FA4040;
        Fri, 22 Jan 2021 13:27:42 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.82.252])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 22 Jan 2021 13:27:42 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v5 1/3] s390x: pv: implement routine to
 share/unshare memory
Date: Fri, 22 Jan 2021 14:27:38 +0100
Message-Id: <1611322060-1972-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611322060-1972-1-git-send-email-pmorel@linux.ibm.com>
References: <1611322060-1972-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-22_09:2021-01-21,2021-01-22 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 mlxlogscore=999 mlxscore=0 priorityscore=1501 suspectscore=0 spamscore=0
 adultscore=0 malwarescore=0 impostorscore=0 clxscore=1015 phishscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101220070
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When communicating with the host we need to share part of
the memory.

Let's implement the ultravisor calls for this.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Suggested-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/uv.h | 39 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 39 insertions(+)

```
#### [RFC PATCH v4 1/2] KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2 map
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12038871
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DA49C4332E
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 10:35:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43F6123A03
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 10:35:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727432AbhAVK0L (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 05:26:11 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11128 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727776AbhAVKOw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 05:14:52 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DMZp50VG5z15x19;
        Fri, 22 Jan 2021 18:13:01 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Fri, 22 Jan 2021 18:14:03 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v4 1/2] KVM: arm64: Adjust partial code of hyp stage-1 map
 and guest stage-2 map
Date: Fri, 22 Jan 2021 18:13:57 +0800
Message-ID: <20210122101358.379956-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210122101358.379956-1-wangyanan55@huawei.com>
References: <20210122101358.379956-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Procedures of hyp stage-1 map and guest stage-2 map are quite different,
but they are tied closely by function kvm_set_valid_leaf_pte().
So adjust the relative code for ease of code maintenance in the future.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/kvm/hyp/pgtable.c | 54 ++++++++++++++++++------------------
 1 file changed, 27 insertions(+), 27 deletions(-)

```
#### [PATCH v3 1/2] vfio/iommu_type1: Populate full dirty when detach non-pinned group
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12039103
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4D644C433DB
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:54:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 01A63239D4
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 11:54:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727184AbhAVLB3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 06:01:29 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11125 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727215AbhAVJ1o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 04:27:44 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DMYld4qd8z15vnr;
        Fri, 22 Jan 2021 17:25:49 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.498.0; Fri, 22 Jan 2021 17:26:48 +0800
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
Subject: [PATCH v3 1/2] vfio/iommu_type1: Populate full dirty when detach
 non-pinned group
Date: Fri, 22 Jan 2021 17:26:34 +0800
Message-ID: <20210122092635.19900-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210122092635.19900-1-zhukeqian1@huawei.com>
References: <20210122092635.19900-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a group with non-pinned-page dirty scope is detached with dirty
logging enabled, we should fully populate the dirty bitmaps at the
time it's removed since we don't know the extent of its previous DMA,
nor will the group be present to trigger the full bitmap when the user
retrieves the dirty bitmap.

Fixes: d6a4c185660c ("vfio iommu: Implementation of ioctl for dirty pages tracking")
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 17 ++++++++++++++++-
 1 file changed, 16 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] x86/cpufeatures: Assign dedicated feature word for CPUID_0x8000001F[EAX]
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12040431
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8BE4EC433E0
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:42:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4330723B04
	for <kvm@archiver.kernel.org>; Fri, 22 Jan 2021 20:42:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730609AbhAVUmM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 22 Jan 2021 15:42:12 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47648 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730427AbhAVUlj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Jan 2021 15:41:39 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DA291C061788
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:40:58 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id l10so6706938ybt.6
        for <kvm@vger.kernel.org>; Fri, 22 Jan 2021 12:40:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=a97iTxNZLtW8RYoTdFMgvqtoq+nhuLOg+I/3jH7GNgQ=;
        b=UyuUysvD0z1rdDGZQ474Z462JzSwb318nzi60gGIQkn5+ksvlaj6XQKKJ99pfAxGjD
         v6k1+6q6apQ0sKDEn1mIkdVt76EkyEbeQmYwNeVKK+4C4J7YSBZjweTe0P43ZfGY7MMH
         fnzLFrYnjP8TvuFPSkbAWl+gj0Y8459n0JmfSMgHMBOWFvkvv7BcADXBw/nizyqaLbBW
         ZAnnrVl4dN5dWUieukoE3U+qUkbzQEDMslnb5RZPwTq1mTLopVcZZ2Exw5s/szaPaXjm
         v9t1j7vhnR0Bp/HWqbY6zctJaWH8lXqTDNuaJLbHA3JIw4I6x1D41aLBf9JDzvK+K6bt
         7fcA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=a97iTxNZLtW8RYoTdFMgvqtoq+nhuLOg+I/3jH7GNgQ=;
        b=Qwy/7yV9SLEkMt/5XbQrncIRtnf8/aBF5uXf6Fa4CaMfOaZztpOHW4pmSyJl6N3O2O
         4A54jfXRf3iJZEEw5c7FaoooMgSRNE4T6VrPIQfBn793WxA7i+lWf3j26/kxzZVQcWMq
         WNuTjrvOaAaXBBsxXvsA7FGqIOubgqd79mJbT2pHcDl9c+PhRwNAv5mpqkSrRUzM6o7H
         7wediT9Fy7/EE/9PNrJ+tlCs0r6vPlifuBolfGBQDYAXbBcj/oYGEWiJPORhenHKxa19
         sRVOLrJ+CAjHa7h7igcDN3borCr+0+CXWanSoyGAsvjNQo5H7YJ7Oc5Pkr4C5rwxG6cr
         st3g==
X-Gm-Message-State: AOAM532AHaNZmUDqkWw5L835qtr/KGW72/hF/AY2dfLMgFVptzN31IVB
        mPmnkoclw+nr4g+XG1+eFpgVsXNlxMU=
X-Google-Smtp-Source: 
 ABdhPJxeq0GW6g1CrndcH8qwuFBy66YDcyKnUZSFUqq3/vfsJjkvaIagUvLr3oGz6tYUhkV9rqt2yTVM7Mw=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a05:6902:701:: with SMTP id
 k1mr8793245ybt.342.1611348058107; Fri, 22 Jan 2021 12:40:58 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 22 Jan 2021 12:40:46 -0800
In-Reply-To: <20210122204047.2860075-1-seanjc@google.com>
Message-Id: <20210122204047.2860075-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210122204047.2860075-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH v3 1/2] x86/cpufeatures: Assign dedicated feature word for
 CPUID_0x8000001F[EAX]
From: Sean Christopherson <seanjc@google.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Collect the scattered SME/SEV related feature flags into a dedicated
word.  There are now five recognized features in CPUID.0x8000001F.EAX,
with at least one more on the horizon (SEV-SNP).  Using a dedicated word
allows KVM to use its automagic CPUID adjustment logic when reporting
the set of supported features to userspace.

No functional change intended.

Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/include/asm/cpufeature.h              |  7 +++++--
 arch/x86/include/asm/cpufeatures.h             | 17 +++++++++++------
 arch/x86/include/asm/disabled-features.h       |  3 ++-
 arch/x86/include/asm/required-features.h       |  3 ++-
 arch/x86/kernel/cpu/common.c                   |  3 +++
 arch/x86/kernel/cpu/scattered.c                |  5 -----
 tools/arch/x86/include/asm/disabled-features.h |  3 ++-
 tools/arch/x86/include/asm/required-features.h |  3 ++-
 8 files changed, 27 insertions(+), 17 deletions(-)

```
