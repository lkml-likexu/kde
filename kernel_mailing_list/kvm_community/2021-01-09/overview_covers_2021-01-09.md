

#### [PATCH 00/13] KVM: SVM: Misc SEV cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Sat Jan  9 00:47:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12007823
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4774C433E9
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 00:48:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7283323A7C
	for <kvm@archiver.kernel.org>; Sat,  9 Jan 2021 00:48:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726430AbhAIAsQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 19:48:16 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39866 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726077AbhAIAsP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 19:48:15 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A3186C061573
        for <kvm@vger.kernel.org>; Fri,  8 Jan 2021 16:47:35 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id x17so17076498ybs.12
        for <kvm@vger.kernel.org>; Fri, 08 Jan 2021 16:47:35 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=8hF52DFU9DtjJAeBrt6aHyP3PJDWIayV3uFwaqHlzLg=;
        b=nnJNRLdoyQB+0+OUl0304jaKmajIHLmQloL2/KK9Y3OsTzvygUbzjY5k31ZSRafzFK
         KJ/6xsZ2Ma2pvNu8v06qwlJh2MI52snKKjQEVqJDvgSHGCLTJlvj+TqDhH7d8q16BK3I
         AbSYAPAlSKeYL88mWMCBWhPfgQYAs5zM9qpJRRQn/pGA0nmyYlgKTTiogqAQ8bckZsXN
         cuI6wPg4fvocfcfUoet8mDHzJTPWbYphlCrKwZwPYiksDD27EQ78TXGwh0JtreXgPj+u
         A1f/SbcPys2KDUyPMYdo8eGa1eKB4t4q0g8mYZzvn6mBkxcacmQmKZgYuTc5J+oUlvm1
         J/8g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=8hF52DFU9DtjJAeBrt6aHyP3PJDWIayV3uFwaqHlzLg=;
        b=nG0QJcdxv2mfLuN6SDqANmX6F5aLvcFI+2xZo5AXycLdWBmETVtamPAJHWjnubvQUF
         kmTua3CTXGxSSETSo8zInAurJqb7z7Xt6cRAvOYsjoiXV+9Mf+p9utRsA1VhM1ftfeZk
         +f/h20BMOKGGGD7Om9hO5mzi7ElGgMVS2XuHMAiHh2lfZuDoY/MucAYmqT9itWVC0xkO
         OYOpzanIIuRwBJxgoiCMSs/d516LJuemIz37Pbwue6YsxkP85rRfs+hBPMdABTE9t6uw
         TGOFy5oY9wdYWpNbO/T2oYTp+RabjGGhA6edhQzv07i76YfUKHdnXUG8yHkEoJTS3KRP
         j2Ew==
X-Gm-Message-State: AOAM533H0eNZj3AQ9NvQ7ToZRIMABXe6rEZeFpqL69Gh78QeKWjwVMTe
        Jh2j2VpqU6RW3QB2GL47TaYr9wTSD8Y=
X-Google-Smtp-Source: 
 ABdhPJyxHpfCKwNYTHkHQotTFg7LbG3tjQAxscDNUxL8aUeZCF7go19UoC7flVFhS3kQO5stNbuSpeRJCbM=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:3d7:: with SMTP id
 206mr9734090ybd.31.1610153254891;
 Fri, 08 Jan 2021 16:47:34 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  8 Jan 2021 16:47:01 -0800
Message-Id: <20210109004714.1341275-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 00/13] KVM: SVM: Misc SEV cleanups
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

Minor bug fixes and refactorings of SEV related code, mainly to clean up
the KVM code for tracking whether or not SEV and SEV-ES are enabled.  E.g.
KVM has both sev_es and svm_sev_enabled(), and a global 'sev' flag while
also using 'sev' as a local variable in several places.

Based on kvm/master, commit 872f36eb0b0f ("KVM: x86: __kvm_vcpu_halt can
be static").

Not super well tested, but AFAICT the feature detection is working as
expected.

Boris, this obviously touches on the KVM vs. kernel _cpu_has() stuff as
well.  My thought is that we can judge the SME/SEV features solely on
whether or the kernel wants to dedicated a word for 'em, and hash out what
to do with KVM at large in the SGX thread.

Sean Christopherson (13):
  KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
  KVM: SVM: Zero out the VMCB array used to track SEV ASID association
  KVM: SVM: Move SEV module params/variables to sev.c
  x86/cpufeatures: Assign dedicated feature word for AMD mem encryption
  KVM: x86: Override reported SME/SEV feature flags with host mask
  x86/sev: Rename global "sev_enabled" flag to "sev_guest"
  KVM: SVM: Append "_enabled" to module-scoped SEV/SEV-ES control
    variables
  KVM: SVM: Unconditionally invoke sev_hardware_teardown()
  KVM: SVM: Explicitly check max SEV ASID during sev_hardware_setup()
  KVM: SVM: Move SEV VMCB tracking allocation to sev.c
  KVM: SVM: Drop redundant svm_sev_enabled() helper
  KVM: SVM: Remove an unnecessary prototype declaration of
    sev_flush_asids()
  KVM: SVM: Skip SEV cache flush if no ASIDs have been used

 arch/x86/include/asm/cpufeature.h             |  7 +-
 arch/x86/include/asm/cpufeatures.h            | 17 +++--
 arch/x86/include/asm/disabled-features.h      |  3 +-
 arch/x86/include/asm/mem_encrypt.h            |  2 +-
 arch/x86/include/asm/required-features.h      |  3 +-
 arch/x86/kernel/cpu/common.c                  |  3 +
 arch/x86/kernel/cpu/scattered.c               |  5 --
 arch/x86/kvm/cpuid.c                          |  2 +
 arch/x86/kvm/cpuid.h                          |  1 +
 arch/x86/kvm/svm/sev.c                        | 64 +++++++++++++------
 arch/x86/kvm/svm/svm.c                        | 35 +++-------
 arch/x86/kvm/svm/svm.h                        |  8 +--
 arch/x86/mm/mem_encrypt.c                     |  4 +-
 arch/x86/mm/mem_encrypt_identity.c            |  2 +-
 .../arch/x86/include/asm/disabled-features.h  |  3 +-
 .../arch/x86/include/asm/required-features.h  |  3 +-
 16 files changed, 88 insertions(+), 74 deletions(-)
```
