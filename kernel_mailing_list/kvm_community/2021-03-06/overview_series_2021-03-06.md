#### [PATCH v4 01/14] KVM: SVM: Zero out the VMCB array used to track SEV ASID association
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12119663
Return-Path: <SRS0=4/uW=IE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A8237C433E6
	for <kvm@archiver.kernel.org>; Sat,  6 Mar 2021 02:00:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 841B564E55
	for <kvm@archiver.kernel.org>; Sat,  6 Mar 2021 02:00:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229978AbhCFB7k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 20:59:40 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41252 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229701AbhCFB7U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 20:59:20 -0500
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E221FC06175F
        for <kvm@vger.kernel.org>; Fri,  5 Mar 2021 17:59:19 -0800 (PST)
Received: by mail-qv1-xf49.google.com with SMTP id h10so2911645qvf.19
        for <kvm@vger.kernel.org>; Fri, 05 Mar 2021 17:59:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=y0THIMpkur6+/Bj9ZSP2+9NkkxbkY6p2tIHGIaTzjYc=;
        b=RR2ofdzqdDJEfpTGPYWFAR7FmrxgkujmTTyYhg52C+RbNDiSQzJ9/Oeb3G9OGauPfz
         N4kGHVOi3Bqz/6k7gjCL0LaoFw+APfHFKLdiuEnWWjADJb36zLj9VId0gTDMOiL4fXVl
         6Ghu7Ij4ubMWSj/FlDEjAICmgKVn19fIxE2cJ+OTIgUPiUDTx9Q10ybvgKxzKVZHTP2p
         VGTY51Aqv9c57vA3IP0HxZOAFzw7FT/FsjRubwbpyh/Xe5C/nl+K47BncBiyqSIWFfnF
         57ByUAWrmTAp+uQ8G24U91WjUK+3aKgKGQGLaFX+atulVwAZXqla6Yb99NZgZj2td2kp
         Kuqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=y0THIMpkur6+/Bj9ZSP2+9NkkxbkY6p2tIHGIaTzjYc=;
        b=P74BfIdApr6mHO51W3VsR/6e41AMVvEFwtNF2a8SV3Lvi3TQqQJ+QHtOjZRPfDxfvm
         r3+wtKXruOh9dm42Zfk726jMerAgSyfgT3jp8iR5s7U9T1Wzydtb4KaqzVNXs4JPOn7r
         CpzKdMbfW1Den3sSbI8Pz/Gy2Q09whSyrX5PkrT7dge/iKOQflGmEOuIvLFuHdlExMne
         ZW0i8X6R3Pg9xnSKawf8iprvvdNEDtkdbeGdIqRKeir7qg+KMmH5ZN+sGqKocxwbVl/G
         GeK5ecg/tIoiuIiYYUVsBB5meikHH4RBIS51ysNHIP3hgiTVp7xy9oHWkkK4Mecr0jM1
         YJCw==
X-Gm-Message-State: AOAM531kD7LNeZDkLxO68i2z1vhTIYZALqeSFejcNODP4yZeog6xyWqv
        SgpTI8VHY8uPdWwCQpAA2gmLmUHjHZU=
X-Google-Smtp-Source: 
 ABdhPJy/04xIWQKM5doZWovlhW61e9m2oWCL5ySlbjt0CJz1yHoHULQZJBmHs8UshbQDP6IXBQNDFKyyYJE=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:fc04:f9df:1efb:bf0c])
 (user=seanjc job=sendgmr) by 2002:a05:6214:1909:: with SMTP id
 er9mr11880770qvb.5.1614995959126; Fri, 05 Mar 2021 17:59:19 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Mar 2021 17:58:52 -0800
In-Reply-To: <20210306015905.186698-1-seanjc@google.com>
Message-Id: <20210306015905.186698-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210306015905.186698-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v4 01/14] KVM: SVM: Zero out the VMCB array used to track SEV
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
