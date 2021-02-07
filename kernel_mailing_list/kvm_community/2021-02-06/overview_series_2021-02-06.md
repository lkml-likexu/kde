#### [PATCH] KVM: SVM: Delay restoration of host MSR_TSC_AUX until return to userspace
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12071755
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 616C3C433E0
	for <kvm@archiver.kernel.org>; Sat,  6 Feb 2021 02:58:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2285664F51
	for <kvm@archiver.kernel.org>; Sat,  6 Feb 2021 02:58:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231785AbhBFC5u (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 21:57:50 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37420 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229835AbhBFCbz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 21:31:55 -0500
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8E152C08EE5E
        for <kvm@vger.kernel.org>; Fri,  5 Feb 2021 16:32:29 -0800 (PST)
Received: by mail-qk1-x749.google.com with SMTP id u66so7293105qkd.13
        for <kvm@vger.kernel.org>; Fri, 05 Feb 2021 16:32:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=pp8fidxQDUFla17Oiws2IWIbULFigNiSSfGs09JA2vk=;
        b=b18RVzQAnJVFPbIGZXNu0CUWEM+61tFcDjq8Je09drj6fLcNJTF1NaXKxkkMLUkr6L
         hLhW6mZaPUnoLEVlClJ8a/YZ09VuBKt643gRBGpG86g3ufH5iEwsVXMRDM+HUP+pv7Q6
         8W39vR6OWGTMsifsOtyYyDQQwO2wRjwXOWkcJNVPlsRJWtkH713+vbzEcxV809UrG21N
         IxFczrmXiUVIc+yF3SGWL2C7IBJB9Unw0NVIsuWLLljk+3a2EEoF0UpL33QCRmBAYO95
         cf2/zuoWem4+PoL3tzj9G0Smo0zWg5qnsxcSgqlXA01D+BuIu9hmydC3TcxboGNgvDOK
         ottg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=pp8fidxQDUFla17Oiws2IWIbULFigNiSSfGs09JA2vk=;
        b=oPaInUjsTPfXTwNGSyjVp62PLXaXLaJ8MouPMpNpFzv9XHEo45/IxpILQYkHbueWik
         v4NNQpNETGZirWfoNL/k0bOtA27e2wYsya5VpDWNM2hFAliwUggNImuMFDEOs9qV+t4c
         /2VlRWVB4Oup1OE9A6HvKQaT6cdF5fY/BZsyqstRzNUeg+7H4rz5QAVixztfPWMceUaW
         jN3Y/mE3SZU0ny9DkIAhPsM86Ge/oS/T8D0OWTe4w+uBUYnRYwDxZrnMis18RvNY3Dae
         d1VQ2nJt5KjIs51XERormgZJ8CBq0f5ElMBQF+pIb947o5qXiMYxD6sYl2XxkFOYtTRe
         Q7Gg==
X-Gm-Message-State: AOAM532UoVsqtHQjnNBcrNE3XK/X36PQD0b1Eqj5dpKGZfv60tWHSC9L
        Y7YvVinhpOf8QdhvOfp8oQveBeFlohM=
X-Google-Smtp-Source: 
 ABdhPJyNOekQxKxWr22DCjEyGNcytvgr4nXfqY1cTHSIF2dulDCnKdFw/f5Ec8jjKbcfP7TsurNgQtrPFpY=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:d169:a9f7:513:e5])
 (user=seanjc job=sendgmr) by 2002:ad4:4993:: with SMTP id
 t19mr6916734qvx.41.1612571548281;
 Fri, 05 Feb 2021 16:32:28 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Feb 2021 16:32:24 -0800
Message-Id: <20210206003224.302728-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] KVM: SVM: Delay restoration of host MSR_TSC_AUX until return
 to userspace
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use KVM's "user return MSRs" framework to defer restoring the host's
MSR_TSC_AUX until the CPU returns to userspace.  Add/improve comments to
clarify why MSR_TSC_AUX is intercepted on both RDMSR and WRMSR, and why
it's safe for KVM to keep the guest's value loaded even if KVM is
scheduled out.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 50 ++++++++++++++++++------------------------
 arch/x86/kvm/svm/svm.h |  7 ------
 2 files changed, 21 insertions(+), 36 deletions(-)

```
