#### [PATCH v2] KVM: SVM: Mark SEV launch secret pages as dirty.From: Cfir Cohen <cfir@google.com>
##### From: Cfir Cohen <cfir@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cfir Cohen <cfir@google.com>
X-Patchwork-Id: 11706215
Return-Path: <SRS0=I84l=BS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 961C414DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  8 Aug 2020 00:37:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 74F9C22D6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  8 Aug 2020 00:37:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ZbCKesn1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726384AbgHHAhy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 7 Aug 2020 20:37:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54072 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726200AbgHHAhv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 Aug 2020 20:37:51 -0400
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 53611C061756
        for <kvm@vger.kernel.org>; Fri,  7 Aug 2020 17:37:51 -0700 (PDT)
Received: by mail-pg1-x549.google.com with SMTP id e3so2695425pgs.3
        for <kvm@vger.kernel.org>; Fri, 07 Aug 2020 17:37:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=qAWBHy/YDwId+EQliujOzvzt7GbHETyF7ZMnV7H8r4I=;
        b=ZbCKesn1vTPY1aHBijollqglxQcxq5k+YuhetvBKh0GklCvIt4ThY4Rk5dGH5baAd9
         bwda8nPqy9p8Zq4zs2JhLSHt5LBithwKbXS5HtyfG2yGdghjNPUkP98CDX9/Q1rAmhCZ
         q1c4WyB2E+9DTAKUwKSmL+PgduqDo50uVJiULU5t2dPkXaCkcSVxDRBpz5YDO4Q2oCPH
         kYkrjOg2SzYtL58uL4bRhc3Z0Amf+NDPgv5ZfAvxBGMV/MiXOeL8aWfsKGV815Mt0Vjj
         FCIH2gRlXfn+MtVJKxhcrk65rxyNGDkJ3UepUyryM5VSrtZKAGiSB/CM0PjWqUzXWfB3
         wXfQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=qAWBHy/YDwId+EQliujOzvzt7GbHETyF7ZMnV7H8r4I=;
        b=qtUTaCzDtKeaOC6YyPGL8UKp78n5gYfUETCQsxDv+aeuUOGsOJzJFC0gbNO1/+ehw9
         iNxtZbE8UpymF1FzrJROMPa5KOBZZiP/4oeBKjNyDThVtNzgHgCoOtd0SMQs5MYME4J1
         X4MfVcrDV/JGnfGUMJcJReAAMwHFvyLYqS3tNSrlv3MAm53YiiU4eITGwiEACr+msd7/
         Fj6mjHMnyziB2j0JGOV0af3t4oL1vSxp2+e1ORGexfV0lScfA0QcfwzAIFYT9mAOKldu
         dRbdTN6IUVKgq8NtKhS6NXuFgNXjc4jb0SxLPOZrK9nShLru71SW7C6L8Vvat8IjUpKd
         fcHg==
X-Gm-Message-State: AOAM531CGt/kYZZmTaKKBlqd8moFCtQWDNevwhB5NAMxbkPYp9KtTqLG
        psajWpo5qrLQGcV5xQLhOpZ6T16B4je2/nYXR2g/xsn/y/mPEvsOpjbLPnByUTOTI/qQzYDhVJW
        qp5aNEwJ0a9zRhXy2e0g7bKq+WRTtlske64pKOlj79TJvJ/S6cX5s
X-Google-Smtp-Source: 
 ABdhPJz2ntewJM4SNFgvJLgp2ChRpBaoUTmjHDtlsktdAVNUMdI1n/Z7oy9JwmiOKi4FiLZ1l0AT6kas
X-Received: by 2002:a17:90b:4a0a:: with SMTP id
 kk10mr15916872pjb.30.1596847070432;
 Fri, 07 Aug 2020 17:37:50 -0700 (PDT)
Date: Fri,  7 Aug 2020 17:37:46 -0700
In-Reply-To: <20200807012303.3769170-1-cfir@google.com>
Message-Id: <20200808003746.66687-1-cfir@google.com>
Mime-Version: 1.0
References: <20200807012303.3769170-1-cfir@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v2] KVM: SVM: Mark SEV launch secret pages as dirty.
From: Cfir Cohen <cfir@google.com>
To: "kvm @ vger . kernel . org" <kvm@vger.kernel.org>,
        Lendacky Thomas <thomas.lendacky@amd.com>,
        Singh Brijesh <brijesh.singh@amd.com>
Cc: Grimm Jon <Jon.Grimm@amd.com>,
        David Rientjes <rientjes@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        linux-kernel@vger.kernel.org, Cfir Cohen <cfir@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The LAUNCH_SECRET command performs encryption of the
launch secret memory contents. Mark pinned pages as
dirty, before unpinning them.
This matches the logic in sev_launch_update_data().

Signed-off-by: Cfir Cohen <cfir@google.com>
---
Changelog since v1:
 - Updated commit message.

 arch/x86/kvm/svm/sev.c | 15 ++++++++++++++-
 1 file changed, 14 insertions(+), 1 deletion(-)

```
