

#### [PATCH 0/9] KVM: x86: Move common exit handlers to x86.c
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Feb  5 00:57:41 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12069087
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C2ADC433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:05:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D24F864DF8
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:05:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232533AbhBEBFX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 20:05:23 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48674 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232367AbhBEA6h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 19:58:37 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3354EC06178C
        for <kvm@vger.kernel.org>; Thu,  4 Feb 2021 16:57:57 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id c13so5079247ybg.8
        for <kvm@vger.kernel.org>; Thu, 04 Feb 2021 16:57:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=vymoThU2kZn6CShsxR9WgxAmamCnipq0tqheseyfNyU=;
        b=Ls6BzEgdqejASEjV5/w5AR50u/CZv61muIlLt0GQ2ojWO8i6hGBynOEZSDArnF1FzR
         2dbSfZwv6ZH5DQJwlNtMVei5B2XPvH00Xf3MQVCILq8o/LOYc7lC+2ezPIbY8g/oquMJ
         lac7TBntrO1Pl/+k2ssdsV/HedQ3dcQFVaD9GoQjlA1Ws7RXoW6Z3BmKto++IhtYyJ95
         k19hNhtCG3eiUOf6eTCaCnEg9eloccV/hbKQQimEOTALzXi1BzexD6Z5WF9IDYwGYUua
         L3bt92kLWSzWLiwzc1B1RwU4fIpuqy7PBELd4bZAjC5Q1p536+uvUTH+B6w0n/ovxEkl
         14Gg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=vymoThU2kZn6CShsxR9WgxAmamCnipq0tqheseyfNyU=;
        b=tlGfMLVVNa/IRj+aI5Jbo8ksF9Nt7xD5sQ6KX7JZrSrvPtYiiDfj1/n3iKSm+n3iyS
         fFjfXSdySxEHFePTybM2qroW8B85byIA3jUHpQBQTK0xAgksgUHZzbxyhX34z50AiUPQ
         gkECbtz0yynFEtKWzD0PyAA/sKHTyyjAuWxp/ruj3X6lIA+hu1k/65XodJV++wBoZYL0
         CzB9zcLOcG7V2gIQm3WJC/cLajcNBGjgOk/0Ac8cQ78oLtEgLo1Cyt0TUFli7ep5G7WO
         yJhKdhSM4RugFlplDckAkzY5Dm3/aozffwl7+ncjIY7x/HA0RNo5HfpZ1deL+NlEvjrD
         DjBg==
X-Gm-Message-State: AOAM532hC7zrRZ2x+by0ymf7t9MkXNpbCKOPY0p5BIxDCNolYJ5Tc6pe
        q0oScFXyLgaZEAKI8YcI2ZXbTAwtrJY=
X-Google-Smtp-Source: 
 ABdhPJxr2ZiQHdnP7iWR5rwAXD71zSddwZf08dhGIlcnW8ER/PinIIsK1p3Q4oaWC7eOshYMG7efHowQF5k=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f16f:a28e:552e:abea])
 (user=seanjc job=sendgmr) by 2002:a25:782:: with SMTP id
 124mr307947ybh.53.1612486676355;
 Thu, 04 Feb 2021 16:57:56 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Feb 2021 16:57:41 -0800
Message-Id: <20210205005750.3841462-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 0/9] KVM: x86: Move common exit handlers to x86.c
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jiri Kosina <trivial@kernel.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The main focus of this series is moving common exit handlers to x86.c,
to avoid duplicate code between SVM and VMX, and also to help prevent
silly divergences between SVM and VMX.

Except for patch 03, which is absolutely grotesque, the changes are
relatively small.

To allow wiring up the common handlers directly to SVM's exit handler
array, patch 03 changes the prototype for SVM's handlers to take @vcpu
instead of @svm.  That created a cascade effect where many helpers were
doing pointless conversions from vcpu->svm->vcpu, and cleaning up those
snowballed into a broader purging of svm->vcpu.  There are still quite a
few instances of svm->vcpu, but the ones remaining are at least
reasonable.  E.g. patterns like this were fairly common (though this was
the most egregious).

        static bool svm_get_nmi_mask(struct kvm_vcpu *vcpu)
        {
                struct vcpu_svm *svm = to_svm(vcpu);

                return !!(svm->vcpu.arch.hflags & HF_NMI_MASK);
        }

        static void svm_set_nmi_mask(struct kvm_vcpu *vcpu, bool masked)
        {
                struct vcpu_svm *svm = to_svm(vcpu);

                if (masked) {
                        svm->vcpu.arch.hflags |= HF_NMI_MASK;
                        if (!sev_es_guest(svm->vcpu.kvm))
                                svm_set_intercept(svm, INTERCEPT_IRET);
                } else {
                        svm->vcpu.arch.hflags &= ~HF_NMI_MASK;
                        if (!sev_es_guest(svm->vcpu.kvm))
                                svm_clr_intercept(svm, INTERCEPT_IRET);
                }
        }

This is based on kvm/queue, commit 4edbfa87f4f4 ("KVM: X86: Expose bus lock
debug exception to guest").  It should also apply fairly cleanly on
kvm/nested-svm, commit f8a5f661936a ("KVM: nSVM: Trace VM-Enter consistency
check failures").

Paolo, I based this on kvm/queue under the assumption it can all wait until
5.13.  I don't think there's anything urgent here, and the conflicts with
the stuff in kvm/nested-svm are annoying.  Let me know if you want me to
rebase anything/all to get something into 5.12, I know 5.12 is a little
light on x86 changes :-D.

Sean Christopherson (9):
  KVM: SVM: Move AVIC vCPU kicking snippet to helper function
  KVM: SVM: Remove an unnecessary forward declaration
  KVM: SVM: Pass @vcpu to exit handlers (and many, many other places)
  KVM: nSVM: Add VMLOAD/VMSAVE helper to deduplicate code
  KVM: x86: Move XSETBV emulation to common code
  KVM: x86: Move trivial instruction-based exit handlers to common code
  KVM: x86: Move RDPMC emulation to common code
  KVM: SVM: Don't manually emulate RDPMC if nrips=0
  KVM: SVM: Skip intercepted PAUSE instructions after emulation

 arch/x86/include/asm/kvm_host.h |   9 +-
 arch/x86/kvm/svm/avic.c         |  57 +--
 arch/x86/kvm/svm/nested.c       | 119 +++---
 arch/x86/kvm/svm/sev.c          |  27 +-
 arch/x86/kvm/svm/svm.c          | 629 ++++++++++++++------------------
 arch/x86/kvm/svm/svm.h          |  12 +-
 arch/x86/kvm/vmx/vmx.c          |  74 +---
 arch/x86/kvm/x86.c              |  62 +++-
 8 files changed, 447 insertions(+), 542 deletions(-)
```
#### [PATCH 0/2] KVM: x86: RSM emulation DR6/DR7 cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Feb  5 01:24:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12069091
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CFAB0C433E9
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:26:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9EF7D64E4E
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:26:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232678AbhBEBZn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 20:25:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54558 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232391AbhBEBZm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 20:25:42 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1CD0AC061786
        for <kvm@vger.kernel.org>; Thu,  4 Feb 2021 17:25:02 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id c12so5204649ybf.1
        for <kvm@vger.kernel.org>; Thu, 04 Feb 2021 17:25:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=sSBhb9eqWQBc8SXvyIWWKnWQ20mOkYO+ojRfnZ4S+p4=;
        b=RHNAftjmsyLsfPrpEGOp4VPdo6nk+wvX87kg/GaJOpUrjabdFRj0u8SCDDhDMMu9uw
         U48lkSHh2rwt5tOBbExHFkIO2wdIOsBJ2A7wLHE5iVap3wha9xqJPDb3Lk6ty2vtTcSD
         urRTwwUTAOTqTAt2j8PC1w3cQP6S6gPNjl86D5v333vaLJ74Gck8cg3TypjN1UmXHRGt
         uUXeo+xS8b+X9cpRqxGIShlz4+oike2q/ul98xHPujCK/HUNv2wXL72cnZbtcxCd+Mck
         CkYgN1HxUmuumr9Ursdo2vYzgMBwkaYcPU+++oYNPE/kvhh40QZ78mvAWHogbag2ajm9
         iuvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=sSBhb9eqWQBc8SXvyIWWKnWQ20mOkYO+ojRfnZ4S+p4=;
        b=uEaEIm+hQIU3gH3oIe+hZ1nIuTPiGM4EHcCLNG1zkA8zbglbmvfRHf2QPf5j8o75lf
         Lp2bqatQIT4aEnzE5/8+lELmXjOJTC7o5IEkTnI796eyh/WLv3hWSnindYyB/ER9KaoW
         i1JqiYQTm7LZAGhdZaCXge+/0emTR4jwI9RV6HBlnRxAcLHInfRpxgHupvyn6qEePEc6
         pdE+QMsLn8CPf2HyDXRddpshbZ5Gog+yLv3MpQPsUuKlIt4jDRNua3SnleMtZFfLGpjY
         LNu+EeoMx02AUKFNLWTID6R4OUJr9HKz8vGuavm+KdytEMgyU/HGn+VUUwrfikWHt5UQ
         f7MA==
X-Gm-Message-State: AOAM531m/TuzLgv69ttniZ/vGmEIDvo8WXI0ol+WZO+ArHX3rIJN9heW
        MGIFkzIGToLky0oxns+FrkyWsj0pYFs=
X-Google-Smtp-Source: 
 ABdhPJziN3SsXUqwEPFyO64AIHF3EG4tUw5R7K+dqK292O4+gMoPnijOCVp/7rRUjdIY48PF3yD6Ee65TKk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f16f:a28e:552e:abea])
 (user=seanjc job=sendgmr) by 2002:a25:24d7:: with SMTP id
 k206mr3003839ybk.68.1612488301389;
 Thu, 04 Feb 2021 17:25:01 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Feb 2021 17:24:56 -0800
Message-Id: <20210205012458.3872687-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 0/2] KVM: x86: RSM emulation DR6/DR7 cleanups
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

A cleanup and a bug fix (technically) in the RSM loading of DR6 and DR7 I
stumbled on when looking at the bus lock detect DR6 changes.

Sean Christopherson (2):
  KVM: x86: Remove misleading DR6/DR7 adjustments from RSM emulation
  KVM: x86: Restore all 64 bits of DR6 and DR7 during RSM on x86-64

 arch/x86/kvm/emulate.c | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)
```
#### [PATCH v4 0/5] KVM: PKS Virtualization support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Feb  5 08:37:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12069609
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A07C1C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:40:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F5D364E0B
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:40:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229866AbhBEIkh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 03:40:37 -0500
Received: from mga09.intel.com ([134.134.136.24]:19410 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229750AbhBEIeq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 03:34:46 -0500
IronPort-SDR: 
 FeCdQxe93Ab1vDsXQy3vwqXQ5eX8rxiYJ1z+iha1Omhlsonwo5nlYkfmZKG9BSADV1C+fIwFWF
 RhLwhSl6vjHg==
X-IronPort-AV: E=McAfee;i="6000,8403,9885"; a="181550683"
X-IronPort-AV: E=Sophos;i="5.81,154,1610438400";
   d="scan'208";a="181550683"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 00:34:00 -0800
IronPort-SDR: 
 gcyCPVjwdmD29JNIJ70FkW2fkUHXLGkYOMRuR6IzWewdO8HBRgCgQvwwiFkg+FmRIFRwgVlz8Z
 psIVrTt/05Kw==
X-IronPort-AV: E=Sophos;i="5.81,154,1610438400";
   d="scan'208";a="393761878"
Received: from chenyi-pc.sh.intel.com ([10.239.159.24])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 00:33:57 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/5] KVM: PKS Virtualization support
Date: Fri,  5 Feb 2021 16:37:01 +0800
Message-Id: <20210205083706.14146-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Protection Keys for Supervisor Pages(PKS) is a feature that extends the
Protection Keys architecture to support thread-specific permission
restrictions on supervisor pages.

PKS works similar to an existing feature named PKU(protecting user pages).
They both perform an additional check after all legacy access
permissions checks are done. If violated, #PF occurs and PFEC.PK bit will
be set. PKS introduces MSR IA32_PKRS to manage supervisor protection key
rights. The MSR contains 16 pairs of ADi and WDi bits. Each pair
advertises on a group of pages with the same key which is set in the
leaf paging-structure entries(bits[62:59]). Currently, IA32_PKRS is not
supported by XSAVES architecture.

This patchset aims to add the virtualization of PKS in KVM. It
implemented PKS CPUID enumeration, vmentry/vmexit configuration, MSR
exposure, nested supported etc. Currently, PKS is not yet supported for
shadow paging. 

PKS bare metal support:
https://lore.kernel.org/lkml/20201106232908.364581-1-ira.weiny@intel.com/

Detailed information about PKS can be found in the latest Intel 64 and
IA-32 Architectures Software Developer's Manual.
---

Changelogs:

v3->v4
- Make the MSR intercept and load-controls setting depend on CR4.PKS value
- shadow the guest pkrs and make it usable in PKS emultion
- add the cr4_pke and cr4_pks check in pkr_mask update
- squash PATCH 2 and PATCH 5 to make the dependencies read more clear
- v3: https://lore.kernel.org/lkml/20201105081805.5674-1-chenyi.qiang@intel.com/

v2->v3:
- No function changes since last submit
- rebase on the latest PKS kernel support:
  https://lore.kernel.org/lkml/20201102205320.1458656-1-ira.weiny@intel.com/
- add MSR_IA32_PKRS to the vmx_possible_passthrough_msrs[]
- RFC v2: https://lore.kernel.org/lkml/20201014021157.18022-1-chenyi.qiang@intel.com/

v1->v2:
- rebase on the latest PKS kernel support:
  https://github.com/weiny2/linux-kernel/tree/pks-rfc-v3
- add a kvm-unit-tests for PKS
- add the check in kvm_init_msr_list for PKRS
- place the X86_CR4_PKS in mmu_role_bits in kvm_set_cr4
- add the support to expose VM_{ENTRY, EXIT}_LOAD_IA32_PKRS in nested
  VMX MSR
- RFC v1: https://lore.kernel.org/lkml/20200807084841.7112-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (5):
  KVM: VMX: Introduce PKS VMCS fields
  KVM: X86: Expose PKS to guest
  KVM: MMU: Rename the pkru to pkr
  KVM: MMU: Add support for PKS emulation
  KVM: VMX: Enable PKS for nested VM

 arch/x86/include/asm/kvm_host.h | 17 +++---
 arch/x86/include/asm/pkeys.h    |  1 +
 arch/x86/include/asm/vmx.h      |  6 ++
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/mmu.h              | 23 ++++----
 arch/x86/kvm/mmu/mmu.c          | 81 +++++++++++++++------------
 arch/x86/kvm/vmx/capabilities.h |  6 ++
 arch/x86/kvm/vmx/nested.c       | 38 ++++++++++++-
 arch/x86/kvm/vmx/vmcs.h         |  1 +
 arch/x86/kvm/vmx/vmcs12.c       |  2 +
 arch/x86/kvm/vmx/vmcs12.h       |  6 +-
 arch/x86/kvm/vmx/vmx.c          | 99 +++++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h          |  1 +
 arch/x86/kvm/x86.c              | 11 +++-
 arch/x86/kvm/x86.h              |  8 +++
 arch/x86/mm/pkeys.c             |  6 ++
 include/linux/pkeys.h           |  4 ++
 17 files changed, 249 insertions(+), 64 deletions(-)
```
#### [PATCH 0/2] KVM: do not assume PTE is writable after follow_pfn
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Feb  5 10:32:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12069845
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E877EC433E6
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:37:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A00B264F46
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:37:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231551AbhBEKhG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 05:37:06 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59058 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231423AbhBEKed (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Feb 2021 05:34:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612521186;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3tCYr3yMCBn+1cr68bRRYsOLCo+XUlob/DqSt8WXr5I=;
        b=S1nbpEuYHgYpadquIrn/t8xWqUexL+mg8J22W841dAA9R7Dg5QRqZPLryu+2geV8ZCAFLP
        RfQJSjjycrO9lU1ChOXjtHzixt5SWyH0xp3HQvp4FlQoDP+dT2HIyluAWR0wYKYoCge76f
        ekhWTUH0D87Y1EhYE4hj86ck3GJ7Rt8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-99-O305z5ggNiaNLlETfouo-Q-1; Fri, 05 Feb 2021 05:33:02 -0500
X-MC-Unique: O305z5ggNiaNLlETfouo-Q-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BE16C107ACF8;
        Fri,  5 Feb 2021 10:33:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1C20919D9F;
        Fri,  5 Feb 2021 10:33:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jgg@ziepe.ca, linux-mm@kvack.org,
        Andrew Morton <akpm@linux-foundation.org>,
        dan.j.williams@intel.com
Subject: [PATCH 0/2] KVM: do not assume PTE is writable after follow_pfn
Date: Fri,  5 Feb 2021 05:32:57 -0500
Message-Id: <20210205103259.42866-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is the first step towards fixing KVM's usage of follow_pfn.
The immediate fix here is that KVM is not checking the writability of
the PFN, which actually dates back to way before the introduction of
follow_pfn in commit add6a0cd1c5b ("KVM: MMU: try to fix up page faults
before giving up", 2016-07-05).  There are more changes needed to
invalidate gfn-to-pfn caches from MMU notifiers, but this issue will
be tackled later.

A more fundamental issue however is that the follow_pfn function is
basically impossible to use correctly.  Almost all users for example
are assuming that the page is writable; KVM was not alone in this
mistake.  follow_pte, despite not being exported for modules, is a
far saner API.  Therefore, patch 1 simplifies follow_pte a bit and
makes it available to modules.

Please review and possibly ack for inclusion in the KVM tree,
thanks!

Paolo


Paolo Bonzini (2):
  mm: provide a sane PTE walking API for modules
  KVM: do not assume PTE is writable after follow_pfn

 arch/s390/pci/pci_mmio.c |  2 +-
 fs/dax.c                 |  5 +++--
 include/linux/mm.h       |  6 ++++--
 mm/memory.c              | 35 ++++++++++++++++++++++++++++++-----
 virt/kvm/kvm_main.c      | 15 ++++++++++++---
 5 files changed, 50 insertions(+), 13 deletions(-)
Reviewed-by: Peter Xu <peterx@redhat.com>
```
#### [PATCH v5 00/14] Add VFIO mediated device support and DEV-MSI support
##### From: Dave Jiang <dave.jiang@intel.com>

```c
From patchwork Fri Feb  5 20:52:53 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Dave Jiang <dave.jiang@intel.com>
X-Patchwork-Id: 12070903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 814E9C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 20:55:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 141DA64FB1
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 20:55:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233173AbhBETL6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 14:11:58 -0500
Received: from mga18.intel.com ([134.134.136.126]:6227 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233586AbhBETLO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 14:11:14 -0500
IronPort-SDR: 
 N8rosoZSrIN3n1L1OaA1rrmz/3I1sMiGESLFJLvGQCUPbO1SqGo7NOEy0yfP0bzniR2PHnp91a
 G5ge1YLp5w/Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9886"; a="169161978"
X-IronPort-AV: E=Sophos;i="5.81,156,1610438400";
   d="scan'208";a="169161978"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 12:52:54 -0800
IronPort-SDR: 
 OydNoMEQySfChi59hrH8Kgse9Penneee+remZqi1CKoDFQuCE2Z7yvqwkvL03iELQlC0BhThJC
 22Tg/LZqCuRA==
X-IronPort-AV: E=Sophos;i="5.81,156,1610438400";
   d="scan'208";a="373680327"
Received: from djiang5-desk3.ch.intel.com ([143.182.136.137])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 12:52:53 -0800
Subject: [PATCH v5 00/14] Add VFIO mediated device support and DEV-MSI support
 for the idxd driver
From: Dave Jiang <dave.jiang@intel.com>
To: alex.williamson@redhat.com, kwankhede@nvidia.com,
        tglx@linutronix.de, vkoul@kernel.org
Cc: megha.dey@intel.com, jacob.jun.pan@intel.com, ashok.raj@intel.com,
        jgg@mellanox.com, yi.l.liu@intel.com, baolu.lu@intel.com,
        kevin.tian@intel.com, sanjay.k.kumar@intel.com,
        tony.luck@intel.com, dan.j.williams@intel.com,
        eric.auger@redhat.com, parav@mellanox.com, netanelg@mellanox.com,
        shahafs@mellanox.com, pbonzini@redhat.com,
        dmaengine@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Date: Fri, 05 Feb 2021 13:52:53 -0700
Message-ID: 
 <161255810396.339900.7646244556839438765.stgit@djiang5-desk3.ch.intel.com>
User-Agent: StGit/0.23-29-ga622f1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Thomas, thank you for the previous reviews. I've made the appropriate
  changes based on your feedback. Please take a look again at patches 5 and
  11 for IMS setup. I'd really appreciate an ack if they look good.
- Dan and Vinod, I'd really appreciate it if you can review patches 1-3 for
  idxd driver bits and provide an ack if they look good.
- Alex and Kirti, I'd very much appreciate it if you can review the series
  and consider inclusion for 5.13 kernel if everything looks good.
Thank you all!

v5:
- Split out non driver IMS code to its own series.
- Removed device devsec detection code.
- Reworked irq_entries for IMS so emulated vector is also included.
- Reworked vidxd_send_interrupt() to take irq_entry directly (data ready for
  consumption) (Thomas)
- Removed pointer to msi_entry in irq_entries (Thomas)
- Removed irq_domain check on free entries (Thomas)
- Split out irqbypass management code (Thomas)
- Fix EXPORT_SYMBOL to EXPORT_SYMBOL_GPL (Thomas)
- Refactored code to use auxiliary bus (Jason)

v4:
dev-msi:
- Make interrupt remapping code more readable (Thomas)
- Add flush writes to unmask/write and reset ims slots (Thomas)
- Interrupt Message Storm-> Interrupt Message Store (Thomas)
- Merge in pasid programming code. (Thomas)

mdev:
- Fixed up domain assignment (Thomas)
- Define magic numbers (Thomas)
- Move siov detection code to PCI common (Thomas)
- Remove duplicated MSI entry info (Thomas)
- Convert code to use ims_slot (Thomas)
- Add explanation of pasid programming for IMS entry (Thomas)
- Add release int handle release support due to spec 1.1 update.

v3:
Dev-msi:
- No need to add support for 2 different dev-msi irq domains, a common
once can be used for both the cases(with IR enabled/disabled)
- Add arch specific function to specify additions to msi_prepare callback
instead of making the callback a weak function
- Call platform ops directly instead of a wrapper function
- Make mask/unmask callbacks as void functions
dev->msi_domain should be updated at the device driver level before
calling dev_msi_alloc_irqs()
dev_msi_alloc/free_irqs() cannot be used for PCI devices
Followed the generic layering scheme: infrastructure bits->arch
bits->enabling bits

Mdev:
- Remove set kvm group notifier (Yan Zhao)
- Fix VFIO irq trigger removal (Yan Zhao)
- Add mmio read flush to ims mask (Jason)

v2:
IMS (now dev-msi):
- With recommendations from Jason/Thomas/Dan on making IMS more generic:
- Pass a non-pci generic device(struct device) for IMS management instead of
mdev
- Remove all references to mdev and symbol_get/put
- Remove all references to IMS in common code and replace with dev-msi
- Remove dynamic allocation of platform-msi interrupts: no groups,no
new msi list or list helpers
- Create a generic dev-msi domain with and without interrupt remapping
enabled.
- Introduce dev_msi_domain_alloc_irqs and dev_msi_domain_free_irqs apis

mdev:
- Removing unrelated bits from SVA enabling that’s not necessary for
the submission. (Kevin)
- Restructured entire mdev driver series to make reviewing easier (Kevin)
- Made rw emulation more robust (Kevin)
- Removed uuid wq type and added single dedicated wq type (Kevin)
- Locking fixes for vdev (Yan Zhao)
- VFIO MSIX trigger fixes (Yan Zhao)

This code series will match the support of the 5.6 kernel (stage 1) driver
but on guest.

The code has dependency on IMS enabling code:
https://lore.kernel.org/linux-pci/1612385805-3412-1-git-send-email-megha.dey@intel.com/T/#t

Stage 1 of the driver has been accepted in v5.6 kernel. It supports dedicated
workqueue (wq) without Shared Virtual Memory (SVM) support.

Stage 2 of the driver supports shared wq and SVM and has been accepted in
kernel v5.11.

VFIO mediated device framework allows vendor drivers to wrap a portion of
device resources into virtual devices (mdev). Each mdev can be assigned
to different guest using the same set of VFIO uAPIs as assigning a
physical device. Accessing to the mdev resource is served with mixed
policies. For example, vendor drivers typically mark data-path interface
as pass-through for fast guest operations, and then trap-and-mediate the
control-path interface to avoid undesired interference between mdevs. Some
level of emulation is necessary behind vfio mdev to compose the virtual
device interface.

This series brings mdev to idxd driver to enable Intel Scalable IOV
(SIOV), a hardware-assisted mediated pass-through technology. SIOV makes
each DSA wq independently assignable through PASID-granular resource/DMA
isolation. It helps improve scalability and reduces mediation complexity
against purely software-based mdev implementations. Each assigned wq is
configured by host and exposed to the guest in a read-only configuration
mode, which allows the guest to use the wq w/o additional setup. This
design greatly reduces the emulation bits to focus on handling commands
from guests.

There are two possible avenues to support virtual device composition:
1. VFIO mediated device (mdev) or 2. User space DMA through char device
(or UACCE). Given the small portion of emulation to satisfy our needs
and VFIO mdev having the infrastructure already to support the device
passthrough, we feel that VFIO mdev is the better route. For more in depth
explanation, see documentation in Documents/driver-api/vfio/mdev-idxd.rst.

Introducing mdev types “1dwq-v1” type. This mdev type allows
allocation of a single dedicated wq from available dedicated wqs. After
a workqueue (wq) is enabled, the user will generate an uuid. On mdev
creation, the mdev driver code will find a dwq depending on the mdev
type. When the create operation is successful, the user generated uuid
can be passed to qemu. When the guest boots up, it should discover a
DSA device when doing PCI discovery.

For example of “1dwq-v1” type:
1. Enable wq with “mdev” wq type
2. A user generated uuid.
3. The uuid is written to the mdev class sysfs path:
echo $UUID > /sys/class/mdev_bus/0000\:00\:0a.0/mdev_supported_types/idxd-1dwq-v1/create
4. Pass the following parameter to qemu:
"-device vfio-pci,sysfsdev=/sys/bus/pci/devices/0000:00:0a.0/$UUID"

The wq exported through mdev will have the read only config bit set
for configuration. This means that the device does not require the
typical configuration. After enabling the device, the user must set the
WQ type and name. That is all is necessary to enable the WQ and start
using it. The single wq configuration is not the only way to create the
mdev. Multi wqs support for mdev will be in the future works.

The mdev utilizes Interrupt Message Store or IMS[3], a device-specific
MSI implementation, instead of MSIX for interrupts for the guest. This
preserves MSIX for host usages and also allows a significantly larger
number of interrupt vectors for guest usage.

The idxd driver implements IMS as on-device memory mapped unified
storage. Each interrupt message is stored as a DWORD size data payload
and a 64-bit address (same as MSI-X). Access to the IMS is through the
host idxd driver.

The idxd driver makes use of the generic IMS irq chip and domain which
stores the interrupt messages as an array in device memory. Allocation and
freeing of interrupts happens via the generic msi_domain_alloc/free_irqs()
interface. One only needs to ensure the interrupt domain is stored in
the underlying device struct.

[1]: https://lore.kernel.org/lkml/157965011794.73301.15960052071729101309.stgit@djiang5-desk3.ch.intel.com/
[2]: https://software.intel.com/en-us/articles/intel-sdm
[3]: https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[4]: https://software.intel.com/en-us/download/intel-data-streaming-accelerator-preliminary-architecture-specification
[5]: https://01.org/blogs/2019/introducing-intel-data-streaming-accelerator
[6]: https://intel.github.io/idxd/
[7]: https://github.com/intel/idxd-driver idxd-stage2.5
---

Dave Jiang (14):
      vfio/mdev: idxd: add theory of operation documentation for idxd mdev
      dmaengine: idxd: add IMS detection in base driver
      dmaengine: idxd: add device support functions in prep for mdev
      vfio/mdev: idxd: Add auxialary device plumbing for idxd mdev support
      vfio/mdev: idxd: add basic mdev registration and helper functions
      vfio/mdev: idxd: add mdev type as a new wq type
      vfio/mdev: idxd: add 1dwq-v1 mdev type
      vfio/mdev: idxd: add emulation rw routines
      vfio/mdev: idxd: prep for virtual device commands
      vfio/mdev: idxd: virtual device commands emulation
      vfio/mdev: idxd: ims setup for the vdcm
      vfio/mdev: idxd: add irq bypass for IMS vectors
      vfio/mdev: idxd: add new wq state for mdev
      vfio/mdev: idxd: add error notification from host driver to mediated device


 .../ABI/stable/sysfs-driver-dma-idxd          |    6 +
 MAINTAINERS                                   |    8 +-
 drivers/dma/idxd/Makefile                     |    2 +
 drivers/dma/idxd/cdev.c                       |    6 +-
 drivers/dma/idxd/device.c                     |  137 +-
 drivers/dma/idxd/idxd.h                       |   48 +-
 drivers/dma/idxd/init.c                       |   98 +-
 drivers/dma/idxd/irq.c                        |    8 +-
 drivers/dma/idxd/registers.h                  |   36 +-
 drivers/dma/idxd/sysfs.c                      |   33 +-
 drivers/vfio/mdev/Kconfig                     |   10 +
 drivers/vfio/mdev/Makefile                    |    1 +
 drivers/vfio/mdev/idxd/Makefile               |    4 +
 drivers/vfio/mdev/idxd/mdev.c                 | 1295 +++++++++++++++++
 drivers/vfio/mdev/idxd/mdev.h                 |  119 ++
 drivers/vfio/mdev/idxd/vdev.c                 | 1014 +++++++++++++
 drivers/vfio/mdev/idxd/vdev.h                 |   28 +
 include/uapi/linux/idxd.h                     |    2 +
 kernel/irq/msi.c                              |    2 +
 19 files changed, 2814 insertions(+), 43 deletions(-)
 create mode 100644 drivers/vfio/mdev/idxd/Makefile
 create mode 100644 drivers/vfio/mdev/idxd/mdev.c
 create mode 100644 drivers/vfio/mdev/idxd/mdev.h
 create mode 100644 drivers/vfio/mdev/idxd/vdev.c
 create mode 100644 drivers/vfio/mdev/idxd/vdev.h

--
```
