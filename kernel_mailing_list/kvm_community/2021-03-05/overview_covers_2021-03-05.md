

#### [PATCH v2 00/17] KVM: x86/mmu: Lots of bug fixes
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Mar  5 01:10:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12117311
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8646C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:11:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A861D64F67
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 01:11:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229521AbhCEBLG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Mar 2021 20:11:06 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60816 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229436AbhCEBLF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Mar 2021 20:11:05 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 91CEAC061574
        for <kvm@vger.kernel.org>; Thu,  4 Mar 2021 17:11:05 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id a186so712053ybg.1
        for <kvm@vger.kernel.org>; Thu, 04 Mar 2021 17:11:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=JQj32MjsoOkFQgAa4dRvlgfsPVUAE2bdIFl0c0to9LI=;
        b=Ipbo52HC6kb61zCq1TqaOzcodnmP4A3+oLF5d4EY7YdMqapY7cDqY1zMePWCnXEyiK
         R1+6lFVHDwDin+Y7is5gabYeALsOH8nyaI978z430vam5oafunfX9xUBJK/I0BY0Ml8H
         aGubULvlQP/z3esxtjOv7LtOBkgXOeZ/abgYi3zTng0Ab+ch+nqauKOXWwWr0dpaDt2T
         VQPNcL/WK45ZFrIu0uDIgc2zU+bFQtMv+CMTf6kwNbJD4VdM+pjmi0wpn0buHKZL+RDE
         +76LU02R8rhjccX2ZfbPlIpTselpu5rT4hb3esySS2i8FcwSSFdPPqzmK/CkzmHw/vZy
         ItiQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=JQj32MjsoOkFQgAa4dRvlgfsPVUAE2bdIFl0c0to9LI=;
        b=OORLiSxM1j6Bxap7QkR+/vQiWRmcDL9yrGiKUlKp/wAbjlbworRL66R+x1BcaORjPq
         aKi3MnLSof394tnZ7ApzVrInwLWFhkIil5o0kIXYN9vljA7kAIax1ZCxkh+/OX1BJaRz
         XxSyli/4Cg903I41csKAYi+nM5+qOtQIa2sWoXESEYk72NDq3HmeKnEUuQZ4TguphkEv
         KIxwEo0tkCASGfF3cgmllK2rqpoEqg0EiKzgH5hjfeSneCI8Om8jcds0yJ8bFbNrqjTa
         9WFjkFZBfxq1C+TxP0wzQ6O3ULLRbhalnsCA1Pg1ZKkwD8fILNoLsNmhZEsHa7mJzymo
         U//Q==
X-Gm-Message-State: AOAM531rGa6GWs9MKei2IeGnkfiub0FjBVn9Q1ARmPfG3ywSrmzM1rZc
        mNdp7XWrxFf3NGNTxVL9146EsH29SP8=
X-Google-Smtp-Source: 
 ABdhPJyJ+Bog5SRGTPV/+GyISdqN2oduHDRYE/B34rx/eftGyz66dYWdH1dFwn0T+iZKZykB5xNkjJxYkus=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:40d8:: with SMTP id
 n207mr10059603yba.3.1614906664878;
 Thu, 04 Mar 2021 17:11:04 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Mar 2021 17:10:44 -0800
Message-Id: <20210305011101.3597423-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v2 00/17] KVM: x86/mmu: Lots of bug fixes
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix nested NPT (nSVM) with 32-bit L1 and SME with shadow paging, which
are completely broken.  Opportunistically fix theoretical bugs related to
prematurely reloading/unloading the MMU.

If nNPT is enabled, L1 can crash the host simply by using 32-bit NPT to
trigger a null pointer dereference on pae_root.

SME with shadow paging (including nNPT) fails to set the C-bit in the
shadow pages that don't go through standard MMU flows (PDPTPRs and the
PML4 used by nNPT to shadow legacy NPT).  It also failes to account for
CR3[63:32], and thus the C-bit, being ignored outside of 64-bit mode.

Patches 01 and 02 fix the null pointer bugs.

Patches 03-09 fix mostly-benign related memory leaks.

Patches 10-12 fix the SME shadow paging bugs, which are also what led me to
the nNPT null pointer bugs.

Patches 13 and 14 fix theoretical bugs with PTP_SWITCH and INVPCID that
I found when auditing flows that touch the MMU context.

Patches 14-17 do additional clean up to hopefully make it harder to
introduce bugs in the future.

On the plus side, I finally understand why KVM supports shadowing 2-level
page tables with 4-level page tables...

Based on kvm/queue, commit fe5f0041c026 ("KVM/SVM: Move vmenter.S exception
fixups out of line").  The null pointer fixes cherry-pick cleanly onto
kvm/master, haven't tried the other bug fixes (I doubt they're worth
backporting even though I tagged 'em with stable).

v2:
  - Collect a review from Ben (did not include his review of patch 03
    since the patch and its direct dependencies were changed).
  - Move pae_root and lm_root allocation to a separate helper to avoid
    sleeping via get_zeroed_page() while holding mmu_lock.
  - Add a patch to grab 'mmu' in a local variable.
  - Remove the BUILD_BUG_ON() in make_mmu_pages_available() since the
    final check wouldn't actually guarnatee 4 pages were "available".
    Instead, add a comment about the limit being soft.

v1:
  - https://lkml.kernel.org/r/20210302184540.2829328-1-seanjc@google.com
 
Sean Christopherson (17):
  KVM: nSVM: Set the shadow root level to the TDP level for nested NPT
  KVM: x86/mmu: Alloc page for PDPTEs when shadowing 32-bit NPT with
    64-bit
  KVM: x86/mmu: Capture 'mmu' in a local variable when allocating roots
  KVM: x86/mmu: Allocate the lm_root before allocating PAE roots
  KVM: x86/mmu: Allocate pae_root and lm_root pages in dedicated helper
  KVM: x86/mmu: Ensure MMU pages are available when allocating roots
  KVM: x86/mmu: Check PDPTRs before allocating PAE roots
  KVM: x86/mmu: Fix and unconditionally enable WARNs to detect PAE leaks
  KVM: x86/mmu: Use '0' as the one and only value for an invalid PAE
    root
  KVM: x86/mmu: Set the C-bit in the PDPTRs and LM pseudo-PDPTRs
  KVM: x86/mmu: Mark the PAE roots as decrypted for shadow paging
  KVM: SVM: Don't strip the C-bit from CR2 on #PF interception
  KVM: nVMX: Defer the MMU reload to the normal path on an EPTP switch
  KVM: x86: Defer the MMU unload to the normal path on an global INVPCID
  KVM: x86/mmu: Unexport MMU load/unload functions
  KVM: x86/mmu: Sync roots after MMU load iff load as successful
  KVM: x86/mmu: WARN on NULL pae_root or lm_root, or bad shadow root
    level

 arch/x86/include/asm/kvm_host.h |   3 -
 arch/x86/kvm/mmu.h              |   4 +
 arch/x86/kvm/mmu/mmu.c          | 273 ++++++++++++++++++++------------
 arch/x86/kvm/mmu/tdp_mmu.c      |  23 +--
 arch/x86/kvm/svm/svm.c          |   9 +-
 arch/x86/kvm/vmx/nested.c       |   9 +-
 arch/x86/kvm/x86.c              |   2 +-
 7 files changed, 192 insertions(+), 131 deletions(-)
```
#### [PATCH 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Fri Mar  5 14:19:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12118541
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 68589C43333
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 14:26:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 185556509C
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 14:26:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231168AbhCEOZj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 09:25:39 -0500
Received: from mga01.intel.com ([192.55.52.88]:51077 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229818AbhCEOZW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 09:25:22 -0500
IronPort-SDR: 
 LNWfaa1+t4uQpLCCQhpbfbue4ZatuykL+LHigGAEqGeMmZh1H+z1fx6zmX9Ze+eszgOvp3PIXn
 tCtCB3DR//4A==
X-IronPort-AV: E=McAfee;i="6000,8403,9914"; a="207392732"
X-IronPort-AV: E=Sophos;i="5.81,225,1610438400";
   d="scan'208";a="207392732"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Mar 2021 06:25:22 -0800
IronPort-SDR: 
 cvMtf/qQOEQUJs4oT5VIDPPc9+J+nEP1Rl0oxCchgqUgzRyIRAxKGrp6Y2NBDzG6S6+26RviPy
 JQ/zL0787pWg==
X-IronPort-AV: E=Sophos;i="5.81,225,1610438400";
   d="scan'208";a="408315609"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Mar 2021 06:25:19 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
Date: Fri,  5 Mar 2021 22:19:57 +0800
Message-Id: <20210305142000.18521-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-net
for vDPA

Zhu Lingshan (3):
  vDPA/ifcvf: get_vendor_id returns a device specific vendor id
  vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
  vDPA/ifcvf: bump version string to 1.0

 drivers/vdpa/ifcvf/ifcvf_base.h | 13 +++++++++----
 drivers/vdpa/ifcvf/ifcvf_main.c | 20 ++++++++++++++------
 2 files changed, 23 insertions(+), 10 deletions(-)
```
#### [PATCH v4 00/11] KVM: VMX: Clean up Hyper-V PV TLB flush
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Mar  5 18:31:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12119173
Return-Path: <SRS0=d8nC=ID=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2EA0C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:32:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 64EDB65085
	for <kvm@archiver.kernel.org>; Fri,  5 Mar 2021 18:32:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229976AbhCESbn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Mar 2021 13:31:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58260 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229781AbhCESb3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Mar 2021 13:31:29 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 63355C061574
        for <kvm@vger.kernel.org>; Fri,  5 Mar 2021 10:31:29 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id 131so3365700ybp.16
        for <kvm@vger.kernel.org>; Fri, 05 Mar 2021 10:31:29 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=ImkS2ZR1p3G/2SDQfJ8HrKEAKHalQx7zguwSD6QHvf4=;
        b=YL0vcJHfRYSHkVgKACDQ3L9PjVHPp6sLUYoXm52dI16ZcNixwN16BIaqK2VTUebMrx
         k9Ub3Qcdxi7iiVh09Oa/NA9pmYhmxbXDaAj9mILJLnRY9Bg3qsqb4QD/VvunbMITPzpK
         RCOWh+TJ6fCcI0HSV2J9RmapDBoIV8L1E/29CyG9lBO73bw+/swuwfsTJCJgna0dbiCF
         DDCbM8w0lxUuqT16PE5ypiiEn1nssV6QwBoZUmJhsxXsLAM8LPWsRJVt49Ki6TxkRo4N
         NjlrP2GpOEkmp4ACxKyG26+Ycr3jci/eL3ROrETC6KesZLiu3CkZetIqGZCRTSKSG6BP
         BAww==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=ImkS2ZR1p3G/2SDQfJ8HrKEAKHalQx7zguwSD6QHvf4=;
        b=EFO2xlGcTL6ic5FSc5UsFTKcbqbmqBvimyG+vQJtE5q03kWmXWUm+VICBL8NsNdSef
         uANhOKlwh7FWssuiH92qX/PjdTQhqd42RvxoxY5+HRick6s/mmElnHX5CwZPd3mPzDnH
         AygoDwSsS8ka9b51H1352G26Cnjy+ZlLP61k5S+PaNKnT3E8KRQ8w1CrcDnwwd5BesU8
         h2qtDauU0ELV7YDHnA8gqqi2ak+NTaXxai98/nmvDFxrFs+KxqlcYAl5gtSRTsrUeL4L
         49+cfhbx2py4+096n5h/zm2Jn1tBam8jILkOnCB5XZYdn/lbZM5AB6kQX8cIuLCuBziQ
         Tohw==
X-Gm-Message-State: AOAM53200/zGBI+p4fm404LtpCSOfbSiazmKkR+XgwyAA6sN6ar5hGoI
        VIwqkVLYDl2TtJIWhDeIvQtJk8MiRGY=
X-Google-Smtp-Source: 
 ABdhPJxkD12a1/MPoA7dPeZYo+wpri52SSaJlYIfFndPtwRa14t6bLCHd6V0p0YQqDRr1xe1rARfTwTbHf4=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:9857:be95:97a2:e91c])
 (user=seanjc job=sendgmr) by 2002:a25:aae2:: with SMTP id
 t89mr16583064ybi.63.1614969088683;
 Fri, 05 Mar 2021 10:31:28 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  5 Mar 2021 10:31:12 -0800
Message-Id: <20210305183123.3978098-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v4 00/11] KVM: VMX: Clean up Hyper-V PV TLB flush
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up KVM's PV TLB flushing when running with EPT on Hyper-V, i.e. as
a nested VMM.  No real goal in mind other than the sole patch in v1, which
is a minor change to avoid a future mixup when TDX also wants to define
.remote_flush_tlb.  Everything else is opportunistic clean up.

NOTE: Based on my NPT+SME bug fix series[*] due to multiple conflicts with
      non-trivial resolutions.

[*] https://lkml.kernel.org/r/20210305011101.3597423-1-seanjc@google.com


Patch 1 legitimately tested on VMX and SVM (including i386).  Patches 2+
smoke tested by hacking usage of the relevant flows without actually
routing to the Hyper-V hypercalls (partial hack-a-patch below).

-static inline int hv_remote_flush_root_ept(hpa_t root_ept,
+static inline int hv_remote_flush_root_ept(struct kvm *kvm, hpa_t root_ept,
                                           struct kvm_tlb_range *range)
 {
-       if (range)
-               return hyperv_flush_guest_mapping_range(root_ept,
-                               kvm_fill_hv_flush_list_func, (void *)range);
-       else
-               return hyperv_flush_guest_mapping(root_ept);
+       if (range) {
+               kvm_make_all_cpus_request(kvm, KVM_REQ_TLB_FLUSH);
+               return 0;
+       }
+
+       return -ENOMEM;
 }
 
 static int hv_remote_flush_tlb_with_range(struct kvm *kvm,
@@ -7753,8 +7754,7 @@ static __init int hardware_setup(void)
                vmx_x86_ops.update_cr8_intercept = NULL;
 
 #if IS_ENABLED(CONFIG_HYPERV)
-       if (ms_hyperv.nested_features & HV_X64_NESTED_GUEST_MAPPING_FLUSH
-           && enable_ept) {
+       if (enable_ept) {
                vmx_x86_ops.tlb_remote_flush = hv_remote_flush_tlb;
                vmx_x86_ops.tlb_remote_flush_with_range =
                                hv_remote_flush_tlb_with_range;

v4: 
  - Rebased to kvm/queue, commit fe5f0041c026 ("KVM/SVM: Move vmenter.S
    exception fixups out of line"), plus the aforementioned series.
  - Don't grab PCID for nested_cr3 (NPT). [Paolo]
  - Collect reviews. [Vitaly]

v3:
  - https://lkml.kernel.org/r/20201027212346.23409-1-sean.j.christopherson@intel.com
  - Add a patch to pass the root_hpa instead of pgd to vmx_load_mmu_pgd()
    and retrieve the active PCID only when necessary.  [Vitaly]
  - Selectively collects reviews (skipped a few due to changes). [Vitaly]
  - Explicitly invalidate hv_tlb_eptp instead of leaving it valid when
    the mismatch tracker "knows" it's invalid. [Vitaly]
  - Change the last patch to use "hv_root_ept" instead of "hv_tlb_pgd"
    to better reflect what is actually being tracked.

v2:
  - Rewrite everything.
  - https://lkml.kernel.org/r/20201020215613.8972-1-sean.j.christopherson@intel.com

v1: ???

Sean Christopherson (11):
  KVM: x86: Get active PCID only when writing a CR3 value
  KVM: VMX: Track common EPTP for Hyper-V's paravirt TLB flush
  KVM: VMX: Stash kvm_vmx in a local variable for Hyper-V paravirt TLB
    flush
  KVM: VMX: Fold Hyper-V EPTP checking into it's only caller
  KVM: VMX: Do Hyper-V TLB flush iff vCPU's EPTP hasn't been flushed
  KVM: VMX: Invalidate hv_tlb_eptp to denote an EPTP mismatch
  KVM: VMX: Don't invalidate hv_tlb_eptp if the new EPTP matches
  KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd
  KVM: VMX: Define Hyper-V paravirt TLB flush fields iff Hyper-V is
    enabled
  KVM: VMX: Skip additional Hyper-V TLB EPTP flushes if one fails
  KVM: VMX: Track root HPA instead of EPTP for paravirt Hyper-V TLB
    flush

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/mmu.h              |   4 +-
 arch/x86/kvm/svm/svm.c          |  10 ++-
 arch/x86/kvm/vmx/vmx.c          | 134 ++++++++++++++++++--------------
 arch/x86/kvm/vmx/vmx.h          |  19 ++---
 5 files changed, 92 insertions(+), 79 deletions(-)
```
