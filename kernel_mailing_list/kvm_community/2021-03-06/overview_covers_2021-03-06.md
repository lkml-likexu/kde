

#### [PATCH v4 00/14] KVM: SVM: Misc SEV cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Sat Mar  6 01:58:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12119659
Return-Path: <SRS0=4/uW=IE=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8627FC433E0
	for <kvm@archiver.kernel.org>; Sat,  6 Mar 2021 02:00:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53CE764E4B
	for <kvm@archiver.kernel.org>; Sat,  6 Mar 2021 02:00:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229960AbhCFB7j (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 20:59:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41244 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229672AbhCFB7S (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 20:59:18 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C359AC061760
        for <kvm@vger.kernel.org>; Fri,  5 Mar 2021 17:59:17 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id f81so4583823yba.8
        for <kvm@vger.kernel.org>; Fri, 05 Mar 2021 17:59:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=z7jhFDxZM9VTyPoGFztEXoUOfIVmvLNL9K69yw2EqzA=;
        b=Q8U7Cb261MgpP1c9JoyQYEQIXZcdAAJXcuEmrXNKtBg1h9M5Wt19jMulmazXjobo3c
         9uVeRmNPZYrgdIHaz5UWc1PsqexJYOSstPOvFCfYIjkTYZ7JmAk0387DR8M8sTJDebli
         zHCXVmmFKmyQz4rvlCHvfgGiPfYyxabEWikWztKqglgztT91lUBmLguMyIH5gMfgkBwL
         WudxOq9aO9qusWf3iHNusmBxtG5AVVccyoQTvIdlLCx3cYeDhnjDoff7+fg+iBY3ub4B
         deE9kWyX/Csa6rbkp6o6LArPA6FnQQKvKHLGjKQbB3T/6qnoQyf860Or+EIZ8yE9JuJy
         ntTA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=z7jhFDxZM9VTyPoGFztEXoUOfIVmvLNL9K69yw2EqzA=;
        b=RGxfheNRqZhaLJyZ3YdorR5dF11MRjKeEbRNk69BJgMIOTqa3Js9NOWkzZUhI3sXfq
         qw5CwYgopaUtavaDBiEc4K6NwajKBzxrt7peoS9Q/yJM2YmrKi+FBZxnREEtxfHUPo9s
         aThAmqS3uuMENzor1RnBXaTPG/knPSInCDTkVpDpYRhzlmZHCFjE7wD0yvQABdrrwctQ
         4fQArGu9cd4lWcsa7fVw7urDK/LYGb3FLLw2cqs03A4Bo+5aAuH3CtRxTkuQv5qRHJYf
         8vke4hznJYg4DyqLK4gc+baPDiS2d13GqyxyVduW2FDPz8hlUYQwvrawkwL765JwhQhr
         YXrQ==
X-Gm-Message-State: AOAM530eO7Vv9sh5pihoVpUZqoutZ87CzzD9tijqyVonuQ8EpINiV3aN
        MF9UYYBkpetd08sUZV3y6cO7nwrfwLk=
X-Google-Smtp-Source: 
 ABdhPJzjGIFz5Hr/RnjHu369C+hLDQpYspgyW5RTyRX/kcJz0x2C1AC4CE2WUWsJ5ltoDZiQDkNa76v4gIk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:fc04:f9df:1efb:bf0c])
 (user=seanjc job=sendgmr) by 2002:a25:420e:: with SMTP id
 p14mr18702645yba.371.1614995956849;
 Fri, 05 Mar 2021 17:59:16 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Mar 2021 17:58:51 -0800
Message-Id: <20210306015905.186698-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v4 00/14] KVM: SVM: Misc SEV cleanups
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

Minor bug fixes and refactorings of SEV related code, mainly to clean up
the KVM code for tracking whether or not SEV and SEV-ES are enabled.  E.g.
KVM has both sev_es and svm_sev_enabled(), and a global 'sev' flag while
also using 'sev' as a local variable in several places.

Based kvm/master, v5.12-rc1-dontuse.

v4:
 - Reinstate the patch to override CPUID.0x8000_001F.
 - Properly configure the CPUID.0x8000_001F override. [Paolo]
 - Rebase to v5.12-rc1-dontuse.
v3:
 - Drop two patches: add a dedicated feature word for CPUID_0x8000001F,
   and use the new word to mask host CPUID in KVM.  I'll send these as a
   separate mini-series so that Boris can take them through tip.
 - Add a patch to remove dependency on
   CONFIG_AMD_MEM_ENCRYPT_ACTIVE_BY_DEFAULT. [Boris / Paolo]
 - Use kcalloc() instead of an open-coded equivalent. [Tom]
 - Nullify sev_asid_bitmap when freeing it during setup. [Tom]
 - Add a comment in sev_hardware_teardown() to document why it's safe to
   query the ASID bitmap without taking the lock. [Tom]
 - Collect reviews. [Tom and Brijesh]
v2:
 - Remove the kernel's sev_enabled instead of renaming it to sev_guest.
 - Fix various build issues. [Tom]
 - Remove stable tag from the patch to free sev_asid_bitmap.  Keeping the
   bitmap on failure is truly only a leak once svm_sev_enabled() is
   dropped later in the series.  It's still arguably a fix since KVM will
   unnecessarily keep memory, but it's not stable material. [Tom]
 - Collect one Ack. [Tom]

v1:
 - https://lkml.kernel.org/r/20210109004714.1341275-1-seanjc@google.com

Sean Christopherson (14):
  KVM: SVM: Zero out the VMCB array used to track SEV ASID association
  KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
  KVM: SVM: Move SEV module params/variables to sev.c
  KVM: x86: Do not advertise SME, VM_PAGE_FLUSH, or unknown features
  x86/sev: Drop redundant and potentially misleading 'sev_enabled'
  KVM: SVM: Append "_enabled" to module-scoped SEV/SEV-ES control
    variables
  KVM: SVM: Condition sev_enabled and sev_es_enabled on
    CONFIG_KVM_AMD_SEV=y
  KVM: SVM: Enable SEV/SEV-ES functionality by default (when supported)
  KVM: SVM: Unconditionally invoke sev_hardware_teardown()
  KVM: SVM: Explicitly check max SEV ASID during sev_hardware_setup()
  KVM: SVM: Move SEV VMCB tracking allocation to sev.c
  KVM: SVM: Drop redundant svm_sev_enabled() helper
  KVM: SVM: Remove an unnecessary prototype declaration of
    sev_flush_asids()
  KVM: SVM: Skip SEV cache flush if no ASIDs have been used

 arch/x86/include/asm/mem_encrypt.h |  1 -
 arch/x86/kvm/cpuid.c               |  6 +++
 arch/x86/kvm/cpuid.h               |  1 +
 arch/x86/kvm/svm/sev.c             | 72 +++++++++++++++++++++---------
 arch/x86/kvm/svm/svm.c             | 35 +++++----------
 arch/x86/kvm/svm/svm.h             |  8 +---
 arch/x86/mm/mem_encrypt.c          | 12 +++--
 arch/x86/mm/mem_encrypt_identity.c |  1 -
 8 files changed, 74 insertions(+), 62 deletions(-)
```
