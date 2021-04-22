#### [PATCH v6 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12215695
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52B3EC43461
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 08:53:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 263D061457
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 08:53:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237749AbhDUIyY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 04:54:24 -0400
Received: from mga17.intel.com ([192.55.52.151]:11339 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S237743AbhDUIyY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 04:54:24 -0400
IronPort-SDR: 
 BtwEPJ8l3w58AaJmsRF3nD5gjKkiEpfQS6xxAZ0SNiSrWSTcGCr9mqqHshqt9GLeaCquQbfJyL
 M1b+TK+q6AEg==
X-IronPort-AV: E=McAfee;i="6200,9189,9960"; a="175771762"
X-IronPort-AV: E=Sophos;i="5.82,238,1613462400";
   d="scan'208";a="175771762"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Apr 2021 01:53:51 -0700
IronPort-SDR: 
 1TaJH9odD8WyZghrygGsUhXd2IJic5uINhpsmHQ/JaDdrCXZNWBXvf7qMLupibp9x+ePSk1FUl
 F/Yh1G0A78Og==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,238,1613462400";
   d="scan'208";a="455253034"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga002.fm.intel.com with ESMTP; 21 Apr 2021 01:53:49 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v6 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Wed, 21 Apr 2021 17:05:50 +0800
Message-Id: <20210421090552.10403-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210421090552.10403-1-weijiang.yang@intel.com>
References: <20210421090552.10403-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These fields are rarely updated by L1 QEMU/KVM, sync them when L1 is trying to
read/write them and after they're changed. If CET guest entry-load bit is not
set by L1 guest, migrate them to L2 manaully.

Opportunistically remove one blank line in previous patch.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/nested.c | 31 +++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 3 files changed, 34 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/7] hyperv: Detect Nested virtualization support for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12216197
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D1E0CC43460
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 14:07:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9622361453
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 14:07:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243341AbhDUOHk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 10:07:40 -0400
Received: from linux.microsoft.com ([13.77.154.182]:36990 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243325AbhDUOHi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 10:07:38 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id BB3C320B8002;
        Wed, 21 Apr 2021 07:07:04 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com BB3C320B8002
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1619014024;
        bh=Ej89Qm9LLMSPxt8OXtylVuc32Z7Yd+HfBt+EQT9qOcM=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=e1hmnl5o7jJjdPHO+UTWuZZfRw6460kHg7YwZrt8dptet2McqPR/Pl9m8lewDv5Zj
         a4ABS+9+myFvA0jjAxPyihFnGMPyE1ng5SlXP+1FpLVbz4Vtbpg0LAWXevVXm+XitC
         kBOJtjq0/g1lZ1VwRbtu0gp2T+Y22a9j6g4AiJOE=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v3 1/7] hyperv: Detect Nested virtualization support for SVM
Date: Wed, 21 Apr 2021 14:06:48 +0000
Message-Id: 
 <9d832252e556f4eddacf9a2b33008fbcf993a44b.1619013347.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1619013347.git.viremana@linux.microsoft.com>
References: <cover.1619013347.git.viremana@linux.microsoft.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Previously, to detect nested virtualization enlightenment support,
we were using HV_X64_ENLIGHTENED_VMCS_RECOMMENDED feature bit of
HYPERV_CPUID_ENLIGHTMENT_INFO.EAX CPUID as docuemented in TLFS:
 "Bit 14: Recommend a nested hypervisor using the enlightened VMCS
  interface. Also indicates that additional nested enlightenments
  may be available (see leaf 0x4000000A)".

Enlightened VMCS, however, is an Intel only feature so the above
detection method doesn't work for AMD. So, use the
HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS.EAX CPUID information ("The
maximum input value for hypervisor CPUID information.") and this
works for both AMD and Intel.

Signed-off-by: Vineeth Pillai <viremana@linux.microsoft.com>
---
 arch/x86/kernel/cpu/mshyperv.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] update git tree location in MAINTAINERS to point at gitlab
##### From: Jacob Xu <jacobhxu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jacob Xu <jacobhxu@google.com>
X-Patchwork-Id: 12216891
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-31.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C4891C433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 19:16:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8897E61450
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 19:16:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240701AbhDUTRA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 15:17:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37206 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238683AbhDUTQ7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 15:16:59 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 07885C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 12:16:25 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 7-20020ac857070000b02901ba5c36e1b2so4613328qtw.21
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 12:16:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=v9nnmhaI+3rKYZNnvHToip4vX0d2kEHOoU/kzhzuhTM=;
        b=AMabSozBmKeff/PUqvU59eFGi+ala00I1aQqc19T2c/5xLzpov3n707ew+ymjPB1sj
         MP2eemyPUbTh/vk8fqT2pK1Ul1IX++H/9xEWydOoR5eMqphlKP1va6Li649oNwA0X4Ly
         crL7rszkmINQCQ3P372Q2+ktCmyFwbI3hwlMS3Qz+9CBu4Rdnwel5U2TXbAqeFwc9SSM
         Dco5bbKKT9rVvj0Ysh81npSSvoBUWa7Zas5xlfoK3x4ecs9l9i5mk7RDnrKJoHqtoX9r
         oapPF6uZ8jfRSn9eYEJ26i1wdIBeOTvhkmcxOg78jBdszoEKXOWhxFbn5YoAPgyTMQBy
         G6sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=v9nnmhaI+3rKYZNnvHToip4vX0d2kEHOoU/kzhzuhTM=;
        b=frmAdM64ktx6Sp1SM2mXcQfD7pv69WjfkDe2lX36rmhFy1wTYCircV1t0cV5rGpCk7
         vnYx4Us6qA2FTsK15hdNSVFfIEmY+odrZn61IzaRcpmxkkHQCUB2/cgjm0IyCJpPQ9y1
         haqX05YbG87Uap7FbV0S2yuSHxj38jw8DRhwVeLNQEfOWLpqLQX0Y6Yqx5VAE3MMtnsJ
         tTD1jY1senhVEGzfNnQoKmc7yeNV2Wk8ZCwI/TtTfrKeu2QbNpg0XsnvR5jsYwoeOYih
         GH5wkGu/WQP/uLlnJF/2JibCxSehGTpqmuRlvH5cM7blvLAZEq29xn+rCz4v/OJQSKmW
         IoOg==
X-Gm-Message-State: AOAM532dmHmmq13ocN6g/TM8i1pBSxDOYDxrEqzu+V9NtmAxNAKqW5PA
        qrlI7MQ3rBjsM3MrQmlHmjgvmtiyGPUjVQ==
X-Google-Smtp-Source: 
 ABdhPJwEm59yKHSwRJZrAiy3eX/j5n4rX/eKQT0sxP7Z1aDiYtBu6QPvi2MT5syZntyZtt/QJ9PPdYKXyz31gg==
X-Received: from mhmmm.sea.corp.google.com
 ([2620:15c:100:202:c919:a1bb:1eab:984c])
 (user=jacobhxu job=sendgmr) by 2002:a0c:b3c8:: with SMTP id
 b8mr30930406qvf.17.1619032584254; Wed, 21 Apr 2021 12:16:24 -0700 (PDT)
Date: Wed, 21 Apr 2021 12:16:11 -0700
Message-Id: <20210421191611.2557051-1-jacobhxu@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [kvm-unit-tests PATCH] update git tree location in MAINTAINERS to
 point at gitlab
From: Jacob Xu <jacobhxu@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Jacob Xu <jacobhxu@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MAINTAINERS file appears to have been forgotten during the migration
to gitlab from the kernel.org. Let's update it now.

Signed-off-by: Jacob Xu <jacobhxu@google.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Fix implicit enum conversion goof in scattered reverse CPUID code
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12215275
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F1DBC433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 01:09:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09FDA6141C
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 01:08:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233947AbhDUBJb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 21:09:31 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51318 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233836AbhDUBJa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 21:09:30 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 136A7C061763
        for <kvm@vger.kernel.org>; Tue, 20 Apr 2021 18:08:58 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 e65-20020a25e7440000b02904ecfeff1ed8so2538539ybh.19
        for <kvm@vger.kernel.org>; Tue, 20 Apr 2021 18:08:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=yreWuj6mbfdz2hyYXXMbP0/DSYeQPnhKZL0KcCdj5RA=;
        b=ZbDT9mkvb5FK7FzLr7cfj2U79ll5HDNS55F9gFZCf1XL+zG4bER5KOmpLo+luFBH1y
         z6wx2wRtBQhLMzugVmjygM8c+UaZPwB+F/91Yu6mHwe7Jid7BCant0asWBzggzZcrXSI
         CK6w7nugeazI5joXFIfVIVrMehCfvKOhjVt7bKrvdCtcAFOgnJobdETedO7AHEFuQke+
         fXil1H0AWX07UX0+278pdG6jkXSCk39dn6YWMo2ypw052A1On/OYkGUVq7hmucyudBRO
         uqII9Af0fXBBrUcs1ChZIo8b1KR/REgE6OtCTU2nZom6Qy/dcipBIPSKMOE+G0nx9Vax
         6vIw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=yreWuj6mbfdz2hyYXXMbP0/DSYeQPnhKZL0KcCdj5RA=;
        b=BO9ONb/rKqBek0zijUgTQJP70AbsvuY8MkP468EMKxOgm+gg+ZTvincbM2N2lczOmJ
         cIH11e4a4x0DABNrE7jGWtVj/ATK44a61CNn0r1YSGK0tGbU7skDrh8TT7uj1xgD2zVJ
         ig4wg909f0/FpmyQuomzIik5yFBbFxzcM4t6vE61SrF3DclmA47H3N0djbEiJC/R087F
         jPcH0AqTtLlcZBM08qADKGsrCNEH9FXZNZSPpCNG3G9vCCkmsCBufUveiyaoT6xip2bY
         QiN6+aNrjcpA/aaEuOEG6wnERfqFCM1FX0oYuDDUnK1n2+O7KoD1DoHogrxY6rxl0rET
         zm+g==
X-Gm-Message-State: AOAM5319hvBg6ser/baU8Sw9f6/TQAWJKbdCUmwyvvb7SHZR6DVg36/6
        z2OMp0sbDP4Gprakn7F8a7jx6DHRpko=
X-Google-Smtp-Source: 
 ABdhPJx0KB0ZGkUiqj3A1BLGcno/kXT67zz5NuprBq16lIqKPtuL+i3wvD5/JWILMhKvqSlKgkvs7O/Df/E=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:a116:ecd1:5e88:1d40])
 (user=seanjc job=sendgmr) by 2002:a25:d051:: with SMTP id
 h78mr28826991ybg.497.1618967337262;
 Tue, 20 Apr 2021 18:08:57 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 20 Apr 2021 18:08:50 -0700
Message-Id: <20210421010850.3009718-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH] KVM: x86: Fix implicit enum conversion goof in scattered
 reverse CPUID code
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        clang-built-linux@googlegroups.com, linux-kernel@vger.kernel.org,
        Kai Huang <kai.huang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Take "enum kvm_only_cpuid_leafs" in scattered specific CPUID helpers
(which is obvious in hindsight), and use "unsigned int" for leafs that
can be the kernel's standard "enum cpuid_leaf" or the aforementioned
KVM-only variant.  Loss of the enum params is a bit disapponting, but
gcc obviously isn't providing any extra sanity checks, and the various
BUILD_BUG_ON() assertions ensure the input is in range.

This fixes implicit enum conversions that are detected by clang-11.

Fixes: 4e66c0cb79b7 ("KVM: x86: Add support for reverse CPUID lookup of scattered features")
Cc: Kai Huang <kai.huang@intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
Reviewed-by: Nathan Chancellor <nathan@kernel.org>
Tested-by: Nathan Chancellor <nathan@kernel.org>
---

Hopefully it's not too late to squash this...

 arch/x86/kvm/cpuid.c | 5 +++--
 arch/x86/kvm/cpuid.h | 2 +-
 2 files changed, 4 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/2] KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12216673
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 306C4C433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 17:37:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EDD0F6113B
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 17:37:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244804AbhDURiJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 13:38:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:30427 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S244790AbhDURiI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 21 Apr 2021 13:38:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619026654;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=T+C3tBmxlj3Ck1rJs8rCiHYuQKpr1tRXoF5sXcWv7z8=;
        b=M1xRw2aKWZ/3apy0SH4Ziaekx8yy6fFTGKCg2d1vvm2pbfIdHmpG176UNcLvrbutnPG7fl
        LriIv3Y3zPFJ0rTDxZfm6jeOm4PBVuQAq1ixk8Wu23xFizTqbh24BqUGiUJWFTLV9Wv+9L
        Aw1kOu0RtqgGPMczO7SXjXEakHhbXbU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-217-pBON5cLAOZaSc6YcIF7sFw-1; Wed, 21 Apr 2021 13:37:24 -0400
X-MC-Unique: pBON5cLAOZaSc6YcIF7sFw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 387DE513A;
        Wed, 21 Apr 2021 17:37:22 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2C8ED10016FE;
        Wed, 21 Apr 2021 17:37:18 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, srutherford@google.com, joro@8bytes.org,
        brijesh.singh@amd.com, thomas.lendacky@amd.com,
        venu.busireddy@oracle.com, Ashish Kalra <ashish.kalra@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@suse.de>,
        x86@kernel.org
Subject: [PATCH v2 1/2] KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
Date: Wed, 21 Apr 2021 13:37:15 -0400
Message-Id: <20210421173716.1577745-2-pbonzini@redhat.com>
In-Reply-To: <20210421173716.1577745-1-pbonzini@redhat.com>
References: <20210421173716.1577745-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

This hypercall is used by the SEV guest to notify a change in the page
encryption status to the hypervisor. The hypercall should be invoked
only when the encryption attribute is changed from encrypted -> decrypted
and vice versa. By default all guest pages are considered encrypted.

The hypercall exits to userspace to manage the guest shared regions and
integrate with the userspace VMM's migration code.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
Co-developed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
Message-Id: <93d7f2c2888315adc48905722574d89699edde33.1618498113.git.ashish.kalra@amd.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/api.rst        | 19 ++++++++++++++
 Documentation/virt/kvm/cpuid.rst      |  5 ++++
 Documentation/virt/kvm/hypercalls.rst | 15 +++++++++++
 arch/x86/include/asm/kvm_host.h       |  2 ++
 arch/x86/include/uapi/asm/kvm_para.h  |  1 +
 arch/x86/kvm/x86.c                    | 36 +++++++++++++++++++++++++++
 include/uapi/linux/kvm.h              |  1 +
 include/uapi/linux/kvm_para.h         |  1 +
 8 files changed, 80 insertions(+)

```
#### [PATCH] KVM: x86: Take advantage of kvm_arch_dy_has_pending_interrupt()
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12215343
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 06FC5C433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:25:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C16AF61418
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:25:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234648AbhDUD0F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 23:26:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52436 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233874AbhDUD0B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 20 Apr 2021 23:26:01 -0400
Received: from mail-pg1-x52d.google.com (mail-pg1-x52d.google.com
 [IPv6:2607:f8b0:4864:20::52d])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EEDA6C06174A;
        Tue, 20 Apr 2021 20:25:25 -0700 (PDT)
Received: by mail-pg1-x52d.google.com with SMTP id f29so28405466pgm.8;
        Tue, 20 Apr 2021 20:25:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ne5KPOc7SK9cFqWFpyxYwHEZ6kioC/3SR/ZzT9KLMRw=;
        b=bC+IVxfoTSFfaDW5+PbOlxCYWpspTKXhw7XjqjL9tQynWSzMX1xAtbobFyke73dfrC
         GpUmqJR+0YeN5eN5+ulxFikZlYTfPYNzx9qjKcA/4M359vigw/FVlbHfxvrH2TIFB2KQ
         G6jF1WZOlObT2KGIr5tsQIMLMawOzBtZEcl3k2ZEPowG8MPo+Lx4b+LDyRy8OhM56yP9
         0hGCGX8W27NkwttkmiujnK93biBEq50+e3Wl5/mAXQMKNmXtUcUHkUHAlvH9tUkBx6Jg
         gyYrDYqr8quiR66C8AKQbxpUjsYmwJn/CZLCFO01EIy4hX4xHcL6cW2rrGb6Suh17y7D
         +A4w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ne5KPOc7SK9cFqWFpyxYwHEZ6kioC/3SR/ZzT9KLMRw=;
        b=K4x3gdhpzpYVJ2nCuprQfiG8Mi0on2dgP2Ur5jX7CQI9SMbvNNY6dRUEQbs4+CfFqb
         trPuE7pRPcSFPEXH/7H6dbRbsSlzhdGi+6nfbR7xT6xDqmd79kSz/kLTXI4xiN3IsJF9
         lYlQRtgHqdo27ucS/WyfpatoHw9Uvlxcy29dohvWNnKXA1DuWMBXVwy6rfVi1jsmXuZy
         HTZmWddzJ5xDNIsqXCtgYRXpTP20aPT7U580rqyjyzIwQO34GshSbr2kkfhFdz8su3SR
         sD6nk8CcqZK2fxI4pYIoRaSWltl3hGQWOVm6DZSlShvi3Vyx01KiFjr7MZI5RJrSdCjb
         jmdg==
X-Gm-Message-State: AOAM533nFNXtShOBQqNALwlsMvL0LY/ywcpV9Dz+OUFVisngcFpEwSxv
        2vpAjqMNPcoWk/xXNdgrWEZA0d1oZA==
X-Google-Smtp-Source: 
 ABdhPJycyImxuKTqrEcAMsiMSfP0zKusz02+ZQPZgefe+TPwP9sGqzabZozhVvHrMM7s7CgfEEMRTQ==
X-Received: by 2002:a05:6a00:882:b029:24b:afda:acfa with SMTP id
 q2-20020a056a000882b029024bafdaacfamr27665486pfj.72.1618975525185;
        Tue, 20 Apr 2021 20:25:25 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 u24sm367150pga.78.2021.04.20.20.25.22
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 20 Apr 2021 20:25:24 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: x86: Take advantage of
 kvm_arch_dy_has_pending_interrupt()
Date: Wed, 21 Apr 2021 11:25:13 +0800
Message-Id: <20210421032513.1921-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

`kvm_arch_dy_runnable` checks the pending_interrupt as the code in
`kvm_arch_dy_has_pending_interrupt`. So take advantage of it.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/x86.c | 21 +++++++++------------
 1 file changed, 9 insertions(+), 12 deletions(-)

```
#### [RFC PATCH 1/2] Prevent CFS from ignoring boost requests from KVM
##### From: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
X-Patchwork-Id: 12216355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DD8AEC43461
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 15:10:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6CCC61426
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 15:10:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243856AbhDUPKs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 11:10:48 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38254 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243869AbhDUPJQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 11:09:16 -0400
Received: from mail-pl1-x62b.google.com (mail-pl1-x62b.google.com
 [IPv6:2607:f8b0:4864:20::62b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CC5AFC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 08:08:43 -0700 (PDT)
Received: by mail-pl1-x62b.google.com with SMTP id y1so6160396plg.11
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 08:08:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=sslab.ics.keio.ac.jp; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Po+qU5dt1Yy0qa7l0uLxYfVEa6vaR5MZXziHwyuHotE=;
        b=PjBH4jQpqFomkLLvOghdtR74zlVVWCzB2L0YShXJND9ZnlX8hieIAcB+2yTU3uQivD
         kQLlukUypPVt0QqJcSXSvMMHHLPjc96l/C18P0yw6q2L4jgDBdDDpMzmEzGxYtVNniTr
         /6Npjz1b5YyeGLTBqOVPNxLtW2VoUWjEHE0I0=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Po+qU5dt1Yy0qa7l0uLxYfVEa6vaR5MZXziHwyuHotE=;
        b=fAFdzg1jL/VojmYQldHvyea0IH/DG8WPGHvruyKkepsBQE4Ixd3Y38XjCnMSRNd0XH
         nDtE6enJEmL3wCjD6umcqaVzkmP8nGmi+BT63S3KKZCCg0ZxL96IJtnQiLzJjHto0QXL
         yP7x78jn3PCVBqBBgISCv6V9EFUWf2L4eyrbkElgMTGY2/t8xtdrAOgi5jelC7352U9g
         8i1Px4ErPntl+Ayx25NY6jdyCkbQmPggZQ5VEhH4Bbfz1M7U5t/fUvyp79OIWQ7Q9QsK
         pkl2FQyc4CFtnPo4Z0+NvJq8YxpAbU/x35E/jVjJwwB/VO5hXTu2X7IfzSPV5DjbK4m2
         LxUw==
X-Gm-Message-State: AOAM532/Q7az98rAHZXrh5hlcwtfKPpIKEkGA4voC9Kc/wNuPQD0Uwy9
        zzCFzn22IitGNmFMQGmtUyj2qA==
X-Google-Smtp-Source: 
 ABdhPJxO2nklRU+cnCq7i+1CU3Nv+qx5VABYKq49QlAFdEnVK8MK/+u8WDfFC8K14cmZdzkD5yGiLQ==
X-Received: by 2002:a17:902:9685:b029:e9:abc1:7226 with SMTP id
 n5-20020a1709029685b02900e9abc17226mr34832987plp.64.1619017723394;
        Wed, 21 Apr 2021 08:08:43 -0700 (PDT)
Received: from haraichi.dnlocal (113x36x239x145.ap113.ftth.ucom.ne.jp.
 [113.36.239.145])
        by smtp.googlemail.com with ESMTPSA id
 f3sm5432553pjo.3.2021.04.21.08.08.40
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 21 Apr 2021 08:08:42 -0700 (PDT)
From: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        David Hildenbrand <david@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pl@sslab.ics.keio.ac.jp,
        kono@sslab.ics.keio.ac.jp,
        Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
Subject: [RFC PATCH 1/2] Prevent CFS from ignoring boost requests from KVM
Date: Thu, 22 Apr 2021 00:08:30 +0900
Message-Id: <20210421150831.60133-2-kentaishiguro@sslab.ics.keio.ac.jp>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210421150831.60133-1-kentaishiguro@sslab.ics.keio.ac.jp>
References: <20210421150831.60133-1-kentaishiguro@sslab.ics.keio.ac.jp>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit increases the vruntime of yielded vCPU to boost a vCPU instead
of the yielded vCPU when two vCPUs are in the same VM. This change avoids
the situation where scheduling the boosted vCPU is too unfair.

Cc: David Hildenbrand <david@redhat.com>
Signed-off-by: Kenta Ishiguro <kentaishiguro@sslab.ics.keio.ac.jp>
---
 kernel/sched/fair.c | 31 +++++++++++++++++++++++++++++++
 1 file changed, 31 insertions(+)

```
#### [RFC PATCH 1/7] virtio-ring: maintain next in extra state for packed virtqueue
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12215329
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1CCFC433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:21:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4DEC60E0B
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 03:21:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234770AbhDUDWY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 20 Apr 2021 23:22:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:43673 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234707AbhDUDWT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 20 Apr 2021 23:22:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618975306;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=OdzRn3Pr0rYI0rGRBMCl0SRE17R3Lml0KXCJ6hRRlik=;
        b=R0Zxb8oR0rDMuGhyo2iPKkr65rLOIiFt00nwzy1hxtXiDipZvUpZ9RgMe1yNL1+W/cYGqN
        Uc5YQjQeuTwuQkP1FvK/a3ZjzbxxdnfqlN4d9tPac/KnAjB40vPuIFk7W/wZFJtVx7SBk9
        R/xwspIv+PBkXP8QsprUV8Sl9Sp66Y0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-562-0FUvAeeUNxqC5sFm2_2Kpg-1; Tue, 20 Apr 2021 23:21:39 -0400
X-MC-Unique: 0FUvAeeUNxqC5sFm2_2Kpg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4842888EF23;
        Wed, 21 Apr 2021 03:21:38 +0000 (UTC)
Received: from localhost.localdomain (ovpn-13-189.pek2.redhat.com
 [10.72.13.189])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 120565B4A6;
        Wed, 21 Apr 2021 03:21:31 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, xieyongji@bytedance.com,
        stefanha@redhat.com, file@sect.tu-berlin.de, ashish.kalra@amd.com,
        martin.radev@aisec.fraunhofer.de, konrad.wilk@oracle.com,
        kvm@vger.kernel.org
Subject: [RFC PATCH 1/7] virtio-ring: maintain next in extra state for packed
 virtqueue
Date: Wed, 21 Apr 2021 11:21:11 +0800
Message-Id: <20210421032117.5177-2-jasowang@redhat.com>
In-Reply-To: <20210421032117.5177-1-jasowang@redhat.com>
References: <20210421032117.5177-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch moves next from vring_desc_state_packed to
vring_desc_desc_extra_packed. This makes it simpler to let extra state
to be reused by split virtqueue.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/virtio/virtio_ring.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [PATCH v2 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12216075
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 922BEC43460
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 12:28:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5ABA960233
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 12:28:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239819AbhDUM3T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 08:29:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58680 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239784AbhDUM3N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 08:29:13 -0400
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 593DCC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 05:28:40 -0700 (PDT)
Received: by mail-pf1-x44a.google.com with SMTP id
 a7-20020a62bd070000b029025434d5ead4so10102734pff.0
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 05:28:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=hti6/C7S7vW6DIR+6O+Sa2M6tGrNZI+uifII3BY38yI=;
        b=cxsmCugqcjA3V9ytn6+rhLxHK5qhBVgFYmWzATlcRDwv0LD0m9Yu6NF41h1AUclASZ
         4IH7Yc+p6kAPWpKp4OdLVputZGFU5oxLXsaK6/Rh2I5ItontxCqqOlkVjhoykPGhHdFy
         ekZhoRR773mG26R9QcGq/1YiCFto7/Nii9m0yiqa3DozzK8/SS6C1M/ycErDHSm0+4O3
         sDoCoL9Gw4eYtBpTn2KU/K9Yib/obGTr86z0wuUmuPQo6cHTJ84xyWyHColK2T+yeIBz
         QeCpPvv4UCk/3egkO/5C/AU9h0GDLErBofyLk7LdgWljmrCYqq27SXEUTz6wzH9rGLHp
         kfNA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=hti6/C7S7vW6DIR+6O+Sa2M6tGrNZI+uifII3BY38yI=;
        b=W3/Q621Qx0Bd+2mm2ZeXQ2bhha+1+MupzTNKwMWnMZQzQxOy1o5KGvGUkb2Sx/0aq7
         NUUqJErHqGnTKykcvjBIy+0nTH1SxIe3tyChNDaX2048Xc3yvpvBQqOz0cV9VZjT9OfN
         momU+Oi8esfKwfbuWDC+ZRSTxYdSbuCMonV4xSDDLzcKzzcHESIuTMs8gCRs5jnZfAwM
         IzHf4N6pnL1+PHOiRv6qvXoFQs5JMjh+Ct8l5js1k8wfT3/x8ZMfUyyrvKaF0XV77B+k
         7RwVcLRtuPr0QKAnmYjCXvFa89oFdMIpQrOyNGRtBKpRtX1cTK53SH5glP3GoElG6Nc1
         DX4Q==
X-Gm-Message-State: AOAM530F6nY4W7wq5cEtyILjnglWw2x/VaYxbISRUhfGuZPNm7tiANLF
        G14rkRcjeQ9x20sUMEiQfnXlNetie5lEQzw7
X-Google-Smtp-Source: 
 ABdhPJyRoIYoZpdyl7BZPuUKSep7mTSH08UBbVmFjyjH6ikGybxlgYE6j8uWW76HyJ2kJaTZhjiyV9dmtX2JY7+P
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:218c:70d5:29b9:db76])
 (user=aaronlewis job=sendgmr) by 2002:a17:90a:8d82:: with SMTP id
 d2mr10708592pjo.200.1619008119827; Wed, 21 Apr 2021 05:28:39 -0700 (PDT)
Date: Wed, 21 Apr 2021 05:28:32 -0700
Message-Id: <20210421122833.3881993-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com
Cc: jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 Documentation/virt/kvm/api.rst  | 19 ++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 35 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++++
 5 files changed, 102 insertions(+), 4 deletions(-)

```
#### [PATCH v3 1/2] kvm: x86: Allow userspace to handle emulation errorsFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12216493
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 960AEC433ED
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 16:23:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FCA961430
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 16:23:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235040AbhDUQYU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 12:24:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54990 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S244360AbhDUQYS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 12:24:18 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E721BC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 09:23:44 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id
 s143-20020a3745950000b029028274263008so9951969qka.9
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 09:23:44 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=v6KRGpvHA5kdUOrG7zY3ACuTyyuyPjea589LWWdzYZg=;
        b=eQTFPiyfY/vCXbbW2+LgHABAsK/OLsNC6FpyW+TCFkc6CCL3WOkWuu/RwMYy/1wDoS
         LqrbMKZ62TAw2zB+HxPxi2Z2e7ubcmCPodZ1/tgaqTvb9XdiZGY6aaT2QKYaby6933PH
         P73uWVI5/F8g72Tr/c7qkDDC/bzkvtzYOpXXkRzhnFqIWgVR9tmFlCxbM7AO2fYHP1SA
         EzNCUcbiuZPGiwnHoAZNZKj1qxxRLnWf/gEAbcq5n3eK4glpkz+jwmNRZRkRjW0FeGMf
         S4EGEnI9JjftDh/qUI1xhiiQIKf/0s/ztlB45sRgA+uOnohTmuOM5SE7zFr++ePd0mw4
         iuzA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=v6KRGpvHA5kdUOrG7zY3ACuTyyuyPjea589LWWdzYZg=;
        b=hWwVgySakBG66a06VPmENjcnUR0fqG+9R6OjPhF2VNqy5cMTpOAs2C/D/M3LLjH9MG
         UDgjBi7CWAdXCzVY+9+BkMyWxhipyHK59/AYSLdsP6e3xU85DARuYdeJ3rnnaWCf8jt6
         w+aBAtbCiC9AmH5GnQvK6trOTQNYUACP3iHsVc2Ltoer6w71Y81tXjvBTI/XFWaDOHjs
         Ig5FAiAMNivpjRuUPx6Za5cDZ6usxXXPe9xY7AyCNOYKAWZR9HS9deiBnbNFNqXA8VK8
         /7JC3nX5/ioMZHmqWf+m30VUgcRClT0uBLXrHundKwnr99x/l1eBMqgAZUq/Sy3IoLM2
         uMqA==
X-Gm-Message-State: AOAM532yuW6G0/KhXag/YylwjI7C9+wZQTZiG4UC0FKISKWq5qihG6TC
        /GJTo0m396IBjxyh9ZMt2BTReasvSsdhk0ij
X-Google-Smtp-Source: 
 ABdhPJy8j14cf7zfznlIkGP/wgLy40wBz42wzCMniYhMeV97HtDhXvuMwBt19pg02Vv0FjQZtO++15dN93XFS5t+
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:218c:70d5:29b9:db76])
 (user=aaronlewis job=sendgmr) by 2002:a05:6214:104a:: with SMTP id
 l10mr32649246qvr.5.1619022224050; Wed, 21 Apr 2021 09:23:44 -0700 (PDT)
Date: Wed, 21 Apr 2021 09:22:25 -0700
Message-Id: <20210421162225.3924641-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v3 1/2] kvm: x86: Allow userspace to handle emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com
Cc: jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a fallback mechanism to the in-kernel instruction emulator that
allows userspace the opportunity to process an instruction the emulator
was unable to.  When the in-kernel instruction emulator fails to process
an instruction it will either inject a #UD into the guest or exit to
userspace with exit reason KVM_INTERNAL_ERROR.  This is because it does
not know how to proceed in an appropriate manner.  This feature lets
userspace get involved to see if it can figure out a better path
forward.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 Documentation/virt/kvm/api.rst  | 18 +++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 ++++++
 arch/x86/kvm/x86.c              | 35 +++++++++++++++++++++++++++++----
 include/uapi/linux/kvm.h        | 23 ++++++++++++++++++++++
 tools/include/uapi/linux/kvm.h  | 23 ++++++++++++++++++++++
 5 files changed, 101 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio/mdev: remove unnecessary NULL check in mbochs_create()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 12216139
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C9A83C433B4
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 13:29:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A28A61451
	for <kvm@archiver.kernel.org>; Wed, 21 Apr 2021 13:29:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242368AbhDUNaa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 09:30:30 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:59340 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S242362AbhDUNa2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 09:30:28 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13LDTq8A191778;
        Wed, 21 Apr 2021 13:29:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=x7XxM5gBTlzGvvXoEooc9Z5gsaqRPidEWmbGH2Zkug0=;
 b=Qf/NqzXiIuq8Cgc55/wweNC6nr0fA3E+cyHis08qGcmUdBZtcLJOsZ1vibR9fMIIokBX
 ViVwuVPwzmZG+ywc4FeUux36IZMAEQFxiSgzqViewm2HhDxWXbV7k1KT1Wbu6oh1Lr/g
 Cp+ZLpepWflQvOm5gsrnWi5wzii8MA0gLWZCADq/PBWnd7uUg/gNiEXls4cFHu6BvNxm
 7PuLwZ7XDBTBvgJpvCxOlfcaqXW6VccoAESO2cExhvQerBAKT1gdqA/afKrS4pvbLOIk
 KNYzMoJ160aq+MHKuE1s+nAhSrtvouan4t2ImmSgCjqbLXw6fevHaY0Y4uGoya84wgDA jw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2130.oracle.com with ESMTP id 37yn6cabug-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 21 Apr 2021 13:29:52 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13LDJwD0177263;
        Wed, 21 Apr 2021 13:29:44 GMT
Received: from pps.reinject (localhost [127.0.0.1])
        by userp3020.oracle.com with ESMTP id 3809eu97n0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 21 Apr 2021 13:29:44 +0000
Received: from userp3020.oracle.com (userp3020.oracle.com [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 13LDTiq0012637;
        Wed, 21 Apr 2021 13:29:44 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 3809eu97m6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 21 Apr 2021 13:29:44 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 13LDTgWN000330;
        Wed, 21 Apr 2021 13:29:42 GMT
Received: from mwanda (/102.36.221.92)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 21 Apr 2021 06:29:41 -0700
Date: Wed, 21 Apr 2021 16:29:36 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Kirti Wankhede <kwankhede@nvidia.com>,
        Jason Gunthorpe <jgg@ziepe.ca>
Cc: Alex Williamson <alex.williamson@redhat.com>, kvm@vger.kernel.org,
        kernel-janitors@vger.kernel.org
Subject: [PATCH] vfio/mdev: remove unnecessary NULL check in mbochs_create()
Message-ID: <YIAowNYCOCNu+xhm@mwanda>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
X-Proofpoint-GUID: G56WWe1uv1YPfgNyI46pq8Gn3Pq884By
X-Proofpoint-ORIG-GUID: G56WWe1uv1YPfgNyI46pq8Gn3Pq884By
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9961
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 priorityscore=1501
 bulkscore=0 suspectscore=0 impostorscore=0 mlxscore=0 lowpriorityscore=0
 clxscore=1011 spamscore=0 mlxlogscore=999 adultscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104210105
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This NULL check is no longer required because "type" now points to
an element in a non-NULL array.

Fixes: 3d3a360e570616 ("vfio/mbochs: Use mdev_get_type_group_id()")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: Jason Gunthorpe <jgg@nvidia.com>
---
 samples/vfio-mdev/mbochs.c | 2 --
 samples/vfio-mdev/mdpy.c | 3 +--
 2 files changed, 1 insertion(+), 4 deletions(-)

```
