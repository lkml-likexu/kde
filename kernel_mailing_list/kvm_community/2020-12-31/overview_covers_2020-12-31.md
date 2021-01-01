

#### [PATCH 0/9] x86/virt: KVM: x86: Exception handling fixes/cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Dec 31 00:26:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 11993793
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A54F4C433DB
	for <kvm@archiver.kernel.org>; Thu, 31 Dec 2020 00:28:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67A8E21973
	for <kvm@archiver.kernel.org>; Thu, 31 Dec 2020 00:28:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726547AbgLaA2F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 30 Dec 2020 19:28:05 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60354 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726289AbgLaA2E (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Dec 2020 19:28:04 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70FBCC061573
        for <kvm@vger.kernel.org>; Wed, 30 Dec 2020 16:27:24 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id w8so31234409ybj.14
        for <kvm@vger.kernel.org>; Wed, 30 Dec 2020 16:27:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=nVNkPdtrx1pwYAnHz8fVa4ArTvLcKWdQz2N8fgjsYlM=;
        b=L0O4vl41jxnecCnVk0EWmu28x4N/hKzJ0akivHyV4IV9xyaU7e7EsZR766gERgfDM1
         MSTYIhErSO+ttCt1GCuxqu/6z4j74wEbVhEdtnLcfx+oNTNAvn1Hn7D3r/xAeGLaVOip
         jnQ1gH01F6/lNqJy1Lu0ZnPRD5KcuH2DjHgbJBv8I8n8Mqh9XF3vuHFq6DiN5BwXOWJW
         XRuZCGTJRXIYMbaVwK/ZrDFE7p/EfgbZoVb2mBm44SsI6ZBrP+t0P6+9I8+6zcFKQnH1
         WcS0wxDWQ9KQkeoMwCKl3chaXMM/765TBfof9gSPcxjakaVbrdoeDufOy/n3sVjFKKSp
         o7Ow==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=nVNkPdtrx1pwYAnHz8fVa4ArTvLcKWdQz2N8fgjsYlM=;
        b=qOH3Si/JuUPscRbhcuO/mEqFvdberG+eYd4R415x/23bUB3BeigCrlAyXairMhPnO0
         c6uLIwMCkGTFfDTO5XOg3fniNfd4lDtHkKOcmAgTAdoifQ3/MAYPphfYT8SKNZxpWP9P
         3JUuQ+4GLshdh/jYkRlTTu21Ce+mlZNaoMONqreCbCcJ3Bsol3Lrtu261JHN6EcEvQnF
         yVcqxoY4b9V+VIy66kqSrHnsVk9s0LxpfrXsFVK2sZjdXWIIj8kAuV1nNd7zYRXpcxTO
         /IflWAlYRsAnzhK6/8rdFm7n/MupPTsHLlC3qekN0FxGOfl3Wivu54YbNTM4GwwoPrxW
         oH4Q==
X-Gm-Message-State: AOAM531aIpBBvC7gnylqEVVNpOWuxGBGoFQh/7d4rE3l7JQ95Hb4I2R1
        K5gidMEi6xF7RYvGfwIHrJnlbRNcB4Q=
X-Google-Smtp-Source: 
 ABdhPJx5QnpnlhcOcBUNeZBAOJ8GALDkMb+HgNFOlORprDIX+e9KbOgwSKgWQbjQzrivQTkLmx/F07Dd2Wk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:16c5:: with SMTP id
 188mr79343598ybw.62.1609374443673;
 Wed, 30 Dec 2020 16:27:23 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 30 Dec 2020 16:26:53 -0800
Message-Id: <20201231002702.2223707-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [PATCH 0/9] x86/virt: KVM: x86: Exception handling fixes/cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        "David P . Reed" <dpreed@deepplum.com>,
        Randy Dunlap <rdunlap@infradead.org>,
        Uros Bizjak <ubizjak@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a conglomeration of three previous series/patches and a bit
of new code.  None of the previous series are directly related, but they
are all needed to achieve the overarching goal of nuking
__kvm_handle_fault_on_reboot(), which is a rather ugly inline asm macro
that has the unfortunate side effect of inserting in-line JMP+CALL
sequences.

Patches 1-3 are resurrected from a series by David Reed[1] to fix VMXOFF
bugs in the reboot flows.

Patch 4 is a patch from Uros Bizjak to get rid of custom inline asm in
nested VMX.  This already received Paolo's "Queued, thanks." blessing,
but has not been pushed to kvm.git.  It's included here as there is an
indirect dependency in patch 8.

Patches 5-6 are minor tweaks to KVM's VMX{ON/OFF} paths to use the
kernel's now-fault-tolerant VMXOFF instead of KVM's custom asm.

Patch 7 replaces SVM's __ex()/__kvm_handle_fault_on_reboot() with more
tailored asm goto macros, similar to the existing VMX asm_vmx*() macros.
This is largely an excuse to get rid of __kvm_handle_fault_on_reboot();
the actual benefits of removing JMP+CALL are likely negligible as SVM only
has a few uses of the macro (versus VMX's bajillion VMREADs/VMWRITEs).

Patch 8 removes __ex()/__kvm_handle_fault_on_reboot().

Patch 9 is a very trimmed down version of a different patch from Uros[3],
which cleaned up the __ex()/__kvm_handle_fault_on_reboot() code, as
opposed to zapping them entirely.

[1] https://lkml.kernel.org/r/20200704203809.76391-1-dpreed@deepplum.com
[2] https://lkml.kernel.org/r/20201029134145.107560-1-ubizjak@gmail.com
[3] https://lkml.kernel.org/r/20201221194800.46962-1-ubizjak@gmail.com

David P. Reed (1):
  x86/virt: Mark flags and memory as clobbered by VMXOFF

Sean Christopherson (6):
  x86/virt: Eat faults on VMXOFF in reboot flows
  x86/reboot: Force all cpus to exit VMX root if VMX is supported
  KVM: VMX: Move Intel PT shenanigans out of VMXON/VMXOFF flows
  KVM: VMX: Use the kernel's version of VMXOFF
  KVM: SVM: Use asm goto to handle unexpected #UD on SVM instructions
  KVM: x86: Kill off __ex() and __kvm_handle_fault_on_reboot()

Uros Bizjak (2):
  KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw
  KVM: x86: Move declaration of kvm_spurious_fault() to x86.h

 arch/x86/include/asm/kvm_host.h | 25 --------------
 arch/x86/include/asm/virtext.h  | 25 ++++++++++----
 arch/x86/kernel/reboot.c        | 30 ++++++-----------
 arch/x86/kvm/svm/sev.c          |  5 ++-
 arch/x86/kvm/svm/svm.c          | 18 +---------
 arch/x86/kvm/svm/svm_ops.h      | 59 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/nested.c       | 32 ++----------------
 arch/x86/kvm/vmx/vmenter.S      |  2 +-
 arch/x86/kvm/vmx/vmx.c          | 28 ++++++----------
 arch/x86/kvm/vmx/vmx.h          |  1 +
 arch/x86/kvm/vmx/vmx_ops.h      |  4 +--
 arch/x86/kvm/x86.c              |  9 ++++-
 arch/x86/kvm/x86.h              |  2 ++
 13 files changed, 117 insertions(+), 123 deletions(-)
 create mode 100644 arch/x86/kvm/svm/svm_ops.h
```
