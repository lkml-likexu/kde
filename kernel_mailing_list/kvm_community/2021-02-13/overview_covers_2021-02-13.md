

#### [PATCH 00/14] KVM: x86/mmu: Dirty logging fixes and improvements
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Sat Feb 13 00:50:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12086433
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93E2DC433E0
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:51:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6485561477
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 00:51:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232103AbhBMAvU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 19:51:20 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57974 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231699AbhBMAvC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 19:51:02 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 13BDCC061756
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:50:22 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id f3so1318090qtx.18
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 16:50:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=B4CJaxKFMc+dqDZ9nbv+QUPSRmvNDPY/ZFqR7df/PF0=;
        b=fL8hQzokABhTqNEOqbM/Ylp50TCYwNe7DpnzPcHsJQpyHAU76uRAiMCZ2DbbU+FSjW
         MmlQKPkPEtH8pEGQXpgf1Ei1IYerm5FlXoO9UTRcq7JW9WByA47I8cBVU3uC6+CCVje9
         HHyOJyZk4egFJxonkFQDBfdlHUksI5Gg6RVnRMpDYW3r9a4XWsttsNRZy0qsNqoY710T
         JWkdKnd5tSu5OxtPFfkUXTDAYO7riwxHqiANAgi1Ee6mCgr0VZ32g53B3yxfYmO9kWRO
         Hr3i4Ljcj3cnRsp89Vfqlom1clZD2Z2Xck32fZZTdjCQ4CUZ0mkKR3/4RLu0m9dqgadi
         Xh2Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=B4CJaxKFMc+dqDZ9nbv+QUPSRmvNDPY/ZFqR7df/PF0=;
        b=Zi4VunQ7551WqbAdF2jxBSQvNwrr/d2aMd8Yc8GKEofU68mnFCG11bUQbfWxXzFXZ4
         TGeeVKwCI+FQk3BKrWvXFE4kWelWnMOsDEICZfdNNfZ78EfcbD7ziRjdWd92argvrBu1
         tsmwg51pCaEgf9q0vVLdDo2zZey8tHP8V6fDZ8v7BcawHPw0p4uQJjFQt6Dxrag3ID1s
         UOFUI9sZMQ83riNbRh0fIhqI1GYpnCmEBS4WheDFCn5JD0+bnXaBmAk/W//crFbgkCap
         pQVE3tWy/QAkyLO2vCwQ+fbCiAMDduzqwyrUHbOLr2IduEJkETXlYMPFEEdJX+RdLvNY
         M/Dg==
X-Gm-Message-State: AOAM530Xy6jPeWyqr9H//QBWKdEzCL+bgIHFlnsuq2Pz7MKCH4jOzrXX
        Y3WLLTjqiIOpDhZH2MIgCSdjg9k+Gbk=
X-Google-Smtp-Source: 
 ABdhPJyudnIPApIy7Nm66X8yqyeGaOrIdBSvHRVveVNyzL3uEudKmIVxnTmngjCy4IoAK3JPNKBaxaAMohI=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b407:1780:13d2:b27])
 (user=seanjc job=sendgmr) by 2002:a05:6214:504:: with SMTP id
 v4mr5165665qvw.58.1613177421259; Fri, 12 Feb 2021 16:50:21 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 12 Feb 2021 16:50:01 -0800
Message-Id: <20210213005015.1651772-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 00/14] KVM: x86/mmu: Dirty logging fixes and improvements
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Makarand Sonare <makarandsonare@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo, this is more or less ready, but on final read-through before
sending I realized it would be a good idea to WARN during VM destruction
if cpu_dirty_logging_count is non-zero.  I wanted to get you this before
the 5.12 window opens in case you want the TDP MMU fixes for 5.12.  I'll
do the above change and retest next week (note, Monday is a US holiday).

On to the code...

This started out as a small tweak to collapsible SPTE zapping in the TDP
MMU, and ended up as a rather large overhaul of CPU dirty logging, a.k.a.
PML.

Four main highlights:

  - Do a more precise check on whether or not a SPTE should be zapped to
    rebuild it as a large page.
  - Disable PML when running L2.  PML is fully emulated for L1 VMMs, thus
    enabling PML in L2 can only hurt and never help.
  - Drop the existing PML kvm_x86_ops.  They're basically trampolines into
    the MMU, and IMO do far more harm than good.
  - Turn on PML only when it's needed instead of setting all dirty bits to
    soft disable PML.

What led me down the rabbit's hole of ripping out the existing PML
kvm_x86_ops isn't really shown here.  Prior to incorporating Makarand's
patch, which allowed for the wholesale remove of setting dirty bits,
I spent a bunch of time poking around the "set dirty bits" code.  My
original changes optimized that path to skip setting dirty bits in the
nested MMU, since the nested MMU relies on write-protection and not PML.
That in turn allowed the TDP MMU zapping to completely skip walking the
rmaps, but doing so based on a bunch of callbacks was a twisted mess.

Happily, those patches got dropped in favor of nuking the code entirely.

Ran selftest and unit tests, and migrated actual VMs on AMD and Intel,
with and without TDP MMU, and with and without EPT.  The AMD system I'm
testing on infinite loops on the reset vector due to a #PF when NPT is
disabled, so that didn't get tested.  That reproduces with kvm/next,
I'll dig into it next week (no idea if it's a KVM or hardware issue).

For actual migration, I ran kvm-unit-tests in L1 along with stress to
hammer memory, and verified migration was effectively blocked until the
stress threads were killed (I didn't feel like figuring out how to
throttle the VM).

Makarand Sonare (1):
  KVM: VMX: Dynamically enable/disable PML based on memslot dirty
    logging

Sean Christopherson (13):
  KVM: x86/mmu: Expand collapsible SPTE zap for TDP MMU to ZONE_DEVICE
    pages
  KVM: x86/mmu: Don't unnecessarily write-protect small pages in TDP MMU
  KVM: x86/mmu: Split out max mapping level calculation to helper
  KVM: x86/mmu: Pass the memslot to the rmap callbacks
  KVM: x86/mmu: Consult max mapping level when zapping collapsible SPTEs
  KVM: nVMX: Disable PML in hardware when running L2
  KVM: x86/mmu: Expand on the comment in
    kvm_vcpu_ad_need_write_protect()
  KVM: x86/mmu: Make dirty log size hook (PML) a value, not a function
  KVM: x86: Move MMU's PML logic to common code
  KVM: x86: Further clarify the logic and comments for toggling log
    dirty
  KVM: x86/mmu: Don't set dirty bits when disabling dirty logging w/ PML
  KVM: x86: Fold "write-protect large" use case into generic
    write-protect
  KVM: x86/mmu: Remove a variety of unnecessary exports

 arch/x86/include/asm/kvm-x86-ops.h |   6 +-
 arch/x86/include/asm/kvm_host.h    |  36 +----
 arch/x86/kvm/mmu/mmu.c             | 203 +++++++++--------------------
 arch/x86/kvm/mmu/mmu_internal.h    |   7 +-
 arch/x86/kvm/mmu/tdp_mmu.c         |  66 +---------
 arch/x86/kvm/mmu/tdp_mmu.h         |   3 +-
 arch/x86/kvm/vmx/nested.c          |  34 +++--
 arch/x86/kvm/vmx/vmx.c             |  94 +++++--------
 arch/x86/kvm/vmx/vmx.h             |   2 +
 arch/x86/kvm/x86.c                 | 145 +++++++++++++--------
 10 files changed, 230 insertions(+), 366 deletions(-)
```
#### [PATCH 0/9] KVM: x86: Fixes for (benign?) truncation bugs
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Sat Feb 13 01:05:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12086477
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D78AC433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 01:06:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35E8B64DF2
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 01:06:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232134AbhBMBGR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 20:06:17 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33026 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231699AbhBMBGI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 20:06:08 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 23537C061574
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 17:05:28 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id j128so1602866ybc.5
        for <kvm@vger.kernel.org>; Fri, 12 Feb 2021 17:05:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=QgASd7HymXzjEEBUQWt6fGnHVl+PB7ICzUP2iM3Rrog=;
        b=Tgygxik75WgrNARZrV/5F5ho2r1q1SBdQNic9CuSEBlCZFZP8DCDksNswPV0ke0Wrk
         3TdJSbrmfHLFiOPpsnA9jvJTdt/t2tSp5HZIT2tGjnQleO1DHaoVhO6EYO9uyKBZdxMR
         v2mBO6bq4otn26wi7JIzl3iCdfCPZIogwL9AhPwg8OAokLcIxFAj2GEvZ/iGjJv/QZsf
         AazciC9HWQ9px4fYON8kQyfB7/Ihe+M5hw9rVy9Ug4Go0DDUerKKRDYhlcLYPabvcWdU
         VLcZcdrMwPAdZjqY5gqtMfRH4IEe2CB3RLMR12WAO17pWkG7IMp4YtKqpOih8fKeC8A4
         iIMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=QgASd7HymXzjEEBUQWt6fGnHVl+PB7ICzUP2iM3Rrog=;
        b=HjEeKfPdyz4s/EsYt/vdnz26SpOZO4IMfmhDnqlrzCeHvNQExZxDYu6e2peppUM8Sv
         v4Q8OawSd5qZ2lzoFFW/SnFlUGOF9zQMhQy7Zi0JMbuIGDrRS5SwNtvu0KZnkczXa5fI
         rG9c8tyEBX9aI03Zi9u70QjCGo9JDFRMsix00+8K3tz5J+/Vs8mtoC0cC7CDB+3tVkQR
         IwcXVIJifoheMEjdb/41HCNFxpsU96qif5PeWXn9UkfnnjBxieU1AtcYYM9Fs1y3qmoM
         J7y6R36W6L24ioqjldfGOtgTGJq5o5i0zhM7zFEHKvQ2o/ZBKDPuE3c0Gji4fBnnmMu0
         LX2g==
X-Gm-Message-State: AOAM530sWgEdAVIESjSYry+D7S5yaBU3Q6DOGP9b1mSGLLeiAqN0sejr
        5xWYzHwXUEiofTpYaaVrI+jhoxazPjo=
X-Google-Smtp-Source: 
 ABdhPJwYPLHaHaSEOaf5FEJAASrdsX6q+bTh8H9y+wEWFBwMBk5QOY6FIa2H9hhe7TWUMlnMPGrYPUVKHyU=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b407:1780:13d2:b27])
 (user=seanjc job=sendgmr) by 2002:a25:b41:: with SMTP id
 62mr7713296ybl.34.1613178327442;
 Fri, 12 Feb 2021 17:05:27 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 12 Feb 2021 17:05:09 -0800
Message-Id: <20210213010518.1682691-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 0/9] KVM: x86: Fixes for (benign?) truncation bugs
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Babu Moger <babu.moger@amd.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        David Woodhouse <dwmw@amazon.co.uk>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patches 01 and 02 fix theoretical bugs related to loading CRs through
the emulator.  The rest of the patches are a bunch of small fixes for
cases where KVM reads/writes a 64-bit register outside of 64-bit mode.

I stumbled on this when puzzling over commit 0107973a80ad ("KVM: x86:
Introduce cr3_lm_rsvd_bits in kvm_vcpu_arch"), which stated that SEV
guests failed to boot on PCID-enabled hosts.  Why only PCID hosts?

After much staring, I realized that the initial CR3 load in
rsm_enter_protected_mode() would skip the MAXPHYADDR check due to the
vCPU not being in long mode.  But due to the ordering problems with
PCID, when PCID is enabled in the guest, the second load of CR3 would
be done with long mode enabled and thus hit the SEV C-bit bug.

Changing kvm_set_cr3() made me look at the callers, and seeing that
SVM didn't properly truncate the value made me look at everything else,
and here we are.

Note, I strongly suspect the emulator still has bugs.  But, unless the
guest is deliberately trying to hit these types of bugs, even the ones
fixed here, they're likely benign.  I figured I was more likely to break
something than I was to fix something by diving into the emulator, so I
left it alone.  For now. :-)

P.S. A few of the segmentation tests in kvm-unit-tests fail with
     unrestricted guest disabled, but those failure go back to at least
     v5.9.  I'll bisect 'em next week.

Sean Christopherson (9):
  KVM: x86: Remove emulator's broken checks on CR0/CR3/CR4 loads
  KVM: x86: Check CR3 GPA for validity regardless of vCPU mode
  KVM: SVM: Truncate GPR value for DR and CR accesses in !64-bit mode
  KVM: VMX: Truncate GPR value for DR and CR reads in !64-bit mode
  KVM: nVMX: Truncate bits 63:32 of VMCS field on nested check in
    !64-bit
  KVM: nVMX: Truncate base/index GPR value on address calc in !64-bit
  KVM: x86/xen: Drop RAX[63:32] when processing hypercall
  KVM: SVM: Use default rAX size for INVLPGA emulation
  KVM: x86: Rename GPR accessors to make mode-aware variants the
    defaults

 arch/x86/kvm/emulate.c        | 68 +----------------------------------
 arch/x86/kvm/kvm_cache_regs.h | 19 ++++++----
 arch/x86/kvm/svm/svm.c        | 11 ++++--
 arch/x86/kvm/vmx/nested.c     | 14 ++++----
 arch/x86/kvm/vmx/vmx.c        |  6 ++--
 arch/x86/kvm/x86.c            | 19 ++++++----
 arch/x86/kvm/x86.h            |  8 ++---
 7 files changed, 47 insertions(+), 98 deletions(-)
```
#### [RFC PATCH v5 00/26] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Sat Feb 13 13:28:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12086783
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0445CC433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 13:29:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7D6964E46
	for <kvm@archiver.kernel.org>; Sat, 13 Feb 2021 13:29:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229703AbhBMN3X (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Feb 2021 08:29:23 -0500
Received: from mga01.intel.com ([192.55.52.88]:30281 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229672AbhBMN3V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Feb 2021 08:29:21 -0500
IronPort-SDR: 
 R9VKivXYBsKYl173QNdGo2L7EHQskaHmgNoCdqPeh+8JnFyb9kA1iWxml5oFWGffNt2yC68BJR
 lk8vTG9TlrUA==
X-IronPort-AV: E=McAfee;i="6000,8403,9893"; a="201682344"
X-IronPort-AV: E=Sophos;i="5.81,176,1610438400";
   d="scan'208";a="201682344"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Feb 2021 05:28:39 -0800
IronPort-SDR: 
 ZlGz64bjU5OxLr0TP9p+5e5jQch2dzT2u21y9q0ZsYEawi+DES8Sq+lposPyWMOlc/GaPA07/w
 FNA1eR6Xm9Ww==
X-IronPort-AV: E=Sophos;i="5.81,176,1610438400";
   d="scan'208";a="398365933"
Received: from kshah-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.230.239])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Feb 2021 05:28:35 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH v5 00/26] KVM SGX virtualization support
Date: Sun, 14 Feb 2021 02:28:28 +1300
Message-Id: <cover.1613221549.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

--- Disclaimer ---

These patches were originally written by Sean Christopherson while at Intel.
Now that Sean has left Intel, I (Kai) have taken over getting them upstream.
This series needs more review before it can be merged.  It is being posted
publicly and under RFC so Sean and others can review it. X86 Maintainers are
safe ignoring it for now.

------------------

Hi all,

This series adds KVM SGX virtualization support. The first 14 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

Please help to review this series. Any feedback is highly appreciated.
Please let me know if I forgot to CC anyone, or anyone wants to be removed from
CC. Thanks in advance!

This series is based against tip/x86/sgx. You can also get the code from
upstream branch of kvm-sgx repo on github:

        https://github.com/intel/kvm-sgx.git upstream

It also requires Qemu changes to create VM with SGX support. You can find Qemu
repo here:

	https://github.com/intel/qemu-sgx.git upstream

Please refer to README.md of above qemu-sgx repo for detail on how to create
guest with SGX support. At meantime, for your quick reference you can use below
command to create SGX guest:

	#qemu-system-x86_64 -smp 4 -m 2G -drive file=<your_vm_image>,if=virtio \
		-cpu host,+sgx_provisionkey \
		-sgx-epc id=epc1,memdev=mem1 \
		-object memory-backend-epc,id=mem1,size=64M,prealloc

Please note that the SGX relevant part is:

		-cpu host,+sgx_provisionkey \
		-sgx-epc id=epc1,memdev=mem1 \
		-object memory-backend-epc,id=mem1,size=64M,prealloc

And you can change other parameters of your qemu command based on your needs.

=========
Changelog:

(Changelog here is for global changes. Please see each patch's changelog for
 changes made to specific patch.)

v4->v5 (No big update from v4):

 - Updated commit message of patch 4, per Jarkko.
 - Updated comments and commit msg for patch 3, per Dave and Sean.

v3->v4:

 - Removed Jarkko's first patch, which removes WARN() against EPC page's
   SGX_EPC_PAGE_RECLAIMER_TRACKED flag. Dave and Sean were not convinced, and
   Sean "tripped more than once in the past during one of the many rebases of
   the virtual EPC and EPC cgroup branches".
 - Switched the patch to introduce SGX1/SGX2 feature bits, and the patch to move
   SGX_LC to cpuid_deps[] table, per Jarkko. Now SGX_LC patch can be applied to
   existing upstream code directly, if needed.
 - Fixed two problems in one KVM patch (trap ECREATE) after review from Rick and
   Sean.
 - Some other minor changes, i.e. update new file's copyright to 2021.

Hi Dave, Sean, Paolo, Rick, and others,
 
 Btw, in last review, we identified that malicious guest can cause KVM to access
 EPC, which will trigger "page abort", which drops on write, and returns all
 ones on read. If I understand correctly, we agreed that a better option is to
 make memremap() deny EPC. However so far this series doesn't contain this work,
 since looks more discussion is required, and this work can be done
 independently from KVM SGX series.

v2->v3:

 - Split original "x86/cpufeatures: Add SGX1 and SGX2 sub-features" patch into
   two patches, by splitting moving SGX_LC bit also into cpuid-deps table logic
   into a separate patch 2:
       [RFC PATCH v3 01/27] x86/cpufeatures: Add SGX1 and SGX2 sub-features
       [RFC PATCH v3 02/27] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
 - Changed from /dev/sgx_virt_epc to /dev/sgx_vepc, per Jarkko. And accordingly,
   changed prefix 'sgx_virt_epc_xx' to 'sgx_vepc_xx' in various functions and
   structures.
 - Changed CONFIG_X86_SGX_VIRTUALIZATION to CONFIG_X86_SGX_KVM, per Dave. Couple
   of x86 patches and KVM patches are changed too due to the renaming.

v1->v2:

 - Refined this cover letter by addressing comments from Dave and Jarkko.
 - The original patch which introduced new X86_FEATURE_SGX1/SGX2 were replaced
   by 3 new patches from Sean, following Boris and Sean's discussion.
       [RFC PATCH v2 01/26] x86/cpufeatures: Add SGX1 and SGX2 sub-features
       [RFC PATCH v2 18/26] KVM: x86: Add support for reverse CPUID lookup of scattered features
       [RFC PATCH v2 19/26] KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
 - The original patch 1
       x86/sgx: Split out adding EPC page to free list to separate helper
   was replaced with 2 new patches from Jarkko
       [RFC PATCH v2 02/26] x86/sgx: Remove a warn from sgx_free_epc_page()
       [RFC PATCH v2 03/26] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
   addressing Jarkko's comments.
 - Moved modifying sgx_init() to always initialize sgx_virt_epc_init() out of
   patch
       x86/sgx: Introduce virtual EPC for use by KVM guests
   to a separate patch:
       [RFC PATCH v2 07/26] x86/sgx: Initialize virtual EPC driver even when SGX driver is disabled
   to address Dave's comment that patch ordering can be improved due to before
   patch "Allow SGX virtualization without Launch Control support", all SGX,
   including SGX virtualization, is actually disabled when SGX LC is not
   present.

=========
KVM SGX virtualization Overview

- Virtual EPC

SGX enclave memory is special and is reserved specifically for enclave use.
In bare-metal SGX enclaves, the kernel allocates enclave pages, copies data
into the pages with privileged instructions, then allows the enclave to start.
In this scenario, only initialized pages already assigned to an enclave are
mapped to userspace.

In virtualized environments, the hypervisor still needs to do the physical
enclave page allocation.  The guest kernel is responsible for the data copying
(among other things).  This means that the job of starting an enclave is now
split between hypervisor and guest.

This series introduces a new misc device: /dev/sgx_vepc.  This device allows
the host to map *uninitialized* enclave memory into userspace, which can then
be passed into a guest.

While it might be *possible* to start a host-side enclave with /dev/sgx_enclave
and pass its memory into a guest, it would be wasteful and convoluted.

Implement the *raw* EPC allocation in the x86 core-SGX subsystem via
/dev/sgx_vepc rather than in KVM.  Doing so has two major advantages:

  - Does not require changes to KVM's uAPI, e.g. EPC gets handled as
    just another memory backend for guests.

  - EPC management is wholly contained in the SGX subsystem, e.g. SGX
    does not have to export any symbols, changes to reclaim flows don't
    need to be routed through KVM, SGX's dirty laundry doesn't have to
    get aired out for the world to see, and so on and so forth.

The virtual EPC pages allocated to guests are currently not reclaimable.
Reclaiming EPC page used by enclave requires a special reclaim mechanism
separate from normal page reclaim, and that mechanism is not supported
for virutal EPC pages.  Due to the complications of handling reclaim
conflicts between guest and host, reclaiming virtual EPC pages is 
significantly more complex than basic support for SGX virtualization.

- Support SGX virtualization without SGX Flexible Launch Control

SGX hardware supports two "launch control" modes to limit which enclaves can
run.  In the "locked" mode, the hardware prevents enclaves from running unless
they are blessed by a third party.  In the unlocked mode, the kernel is in
full control of which enclaves can run.  The bare-metal SGX code refuses to
launch enclaves unless it is in the unlocked mode.

This sgx_virt_epc driver does not have such a restriction.  This allows guests
which are OK with the locked mode to use SGX, even if the host kernel refuses
to.

- Support exposing SGX2

Due to the same reason above, SGX2 feature detection is added to core SGX code
to allow KVM to expose SGX2 to guest, even currently SGX driver doesn't support
SGX2, because SGX2 can work just fine in guest w/o any interaction to host SGX
driver.

- Restricit SGX guest access to provisioning key

To grant guest being able to fully use SGX, guest needs to be able to access
provisioning key.  The provisioning key is sensitive, and accessing to it should
be restricted. In bare-metal driver, allowing enclave to access provisioning key
is restricted by being able to open /dev/sgx_provision.

Add a new KVM_CAP_SGX_ATTRIBUTE to KVM uAPI to extend above mechanism to KVM
guests as well.  When userspace hypervisor creates a new VM, the new cap is only
added to VM when userspace hypervisior is able to open /dev/sgx_provision,
following the same role as in bare-metal driver.  KVM then traps ECREATE from
guest, and only allows ECREATE with provisioning key bit to run when guest
supports KVM_CAP_SGX_ATTRIBUTE.


Jarkko Sakkinen (1):
  x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()

Kai Huang (3):
  x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
  x86/sgx: Initialize virtual EPC driver even when SGX driver is
    disabled
  x86/sgx: Add helper to update SGX_LEPUBKEYHASHn MSRs

Sean Christopherson (22):
  x86/cpufeatures: Add SGX1 and SGX2 sub-features
  x86/sgx: Add SGX_CHILD_PRESENT hardware error code
  x86/sgx: Introduce virtual EPC for use by KVM guests
  x86/cpu/intel: Allow SGX virtualization without Launch Control support
  x86/sgx: Expose SGX architectural definitions to the kernel
  x86/sgx: Move ENCLS leaf definitions to sgx_arch.h
  x86/sgx: Add SGX2 ENCLS leaf definitions (EAUG, EMODPR and EMODT)
  x86/sgx: Add encls_faulted() helper
  x86/sgx: Add helpers to expose ECREATE and EINIT to KVM
  x86/sgx: Move provisioning device creation out of SGX driver
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union
  KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
  KVM: x86: Define new #PF SGX error code bit
  KVM: x86: Add support for reverse CPUID lookup of scattered features
  KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
  KVM: VMX: Add basic handling of VM-Exit from SGX enclave
  KVM: VMX: Frame in ENCLS handler for SGX virtualization
  KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
  KVM: VMX: Add emulation of SGX Launch Control LE hash MSRs
  KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)
  KVM: VMX: Enable SGX virtualization for SGX1, SGX2 and LC
  KVM: x86: Add capability to grant VM access to privileged SGX
    attribute

 Documentation/virt/kvm/api.rst                |  23 +
 arch/x86/Kconfig                              |  12 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/asm/sgx.h                    |  19 +
 .../cpu/sgx/arch.h => include/asm/sgx_arch.h} |  20 +
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  69 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  21 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  93 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 353 +++++++++++++
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  70 ++-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 466 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 171 +++++--
 arch/x86/kvm/vmx/vmx.h                        |  27 +-
 arch/x86/kvm/x86.c                            |  24 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 33 files changed, 1498 insertions(+), 156 deletions(-)
 create mode 100644 arch/x86/include/asm/sgx.h
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx_arch.h} (96%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
