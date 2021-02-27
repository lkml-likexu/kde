

#### [PATCH 0/5] KVM: x86/mmu: Misc cleanups, mostly TDP MMU
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri Feb 26 01:03:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12105333
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 25896C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 01:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D43C864EC3
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 01:04:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229537AbhBZBE3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 20:04:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48706 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229993AbhBZBEN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 20:04:13 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8BC8EC06174A
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 17:03:33 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id v196so8377788ybv.3
        for <kvm@vger.kernel.org>; Thu, 25 Feb 2021 17:03:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=wTYAZE8l/zQPMkdzD7xsvIS6f4NgB+O0D1nsiwHUulE=;
        b=TxqkVa6Q/RFAQfK5SS9lz1EFq/h95m+FCP8+yX5UEZCc3xGG+dozfQEcvKUuO2ZRV8
         CaxYstOd+RXa1GhIT0nzmEgiVT3TiAHWmN/R6VTlmtyK026MgMkb3CzbgDSKYzE0bph8
         AHROcj0cQrdcxr1v4xHv/KQXUZpp7168JPeXL3RrTriDlybgkZoBXH3Prdl74xmVHWmK
         nEYjYLcPYHDWQscUwSa6ZJV/b4/Twjzw1BA/+Z3fufHCO+Z6RSzTg1C9uduDCP5poGqT
         bINRgPXuUwVoS/P2pmewKoV9J1l5BkM8q3IryrywUKkG61rw7uLdxZ2rRHqI57A3/JNP
         TUOw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=wTYAZE8l/zQPMkdzD7xsvIS6f4NgB+O0D1nsiwHUulE=;
        b=tJgXbxoIGXRtTiuFZU1UPDmnk6P6HCqWsCE3LpiOdDyGIeEHRB4MLu8TTbeQAH7vgJ
         tII1I1L3fK7veLUABtlhyHHxE2qxrGIF7FP/dn7hhu4I1JsfbFG1WhywdLrHBaPjnnlU
         m0ZpkbT7Chgs/KZzC2bypAT+VqRKmoVbEdbAM6+IpVMrx8rFWW2bGU15xJVmi8mr6XIB
         tnohlgwM/y56+a7AmVuiEUITcbFUQy2OVVC1Ink1moYzW2toy9xNT81su0R4fXje+DUl
         pq+fiDPF8iz0dxiT3tH4PbECexUTqCP2W2jro/lqT6ag8kTOLxbS5+V9UFrkZYZQaPeG
         XHag==
X-Gm-Message-State: AOAM530Ym4Y+FxaIDR+EVQFkHbFSVyA6GR5CDo8NcYIz20cCAKBKQ8Nj
        VYELXMUioibBvxkY5Z2XIA/U5OkBCwM=
X-Google-Smtp-Source: 
 ABdhPJx1I/DKz/d2vGPFiStKyjcq32wUL3PVrpnedWlv7bhpAr8F3TeftRKfJixHYbJLzoL/5ufr7zmZBU8=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:34c4:7c1d:f9ba:4576])
 (user=seanjc job=sendgmr) by 2002:a25:5ac2:: with SMTP id
 o185mr985108ybb.252.1614301412620;
 Thu, 25 Feb 2021 17:03:32 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Feb 2021 17:03:24 -0800
Message-Id: <20210226010329.1766033-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 0/5] KVM: x86/mmu: Misc cleanups, mostly TDP MMU
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Effectively belated code review of a few pieces of the TDP MMU.

Sean Christopherson (5):
  KVM: x86/mmu: Remove spurious TLB flush from TDP MMU's change_pte()
    hook
  KVM: x86/mmu: WARN if TDP MMU's set_tdp_spte() sees multiple GFNs
  KVM: x86/mmu: Use 'end' param in TDP MMU's test_age_gfn()
  KVM: x86/mmu: Add typedefs for rmap/iter handlers
  KVM: x86/mmu: Add convenience wrapper for acting on single hva in TDP
    MMU

 arch/x86/kvm/mmu/mmu.c     | 27 +++++++------------
 arch/x86/kvm/mmu/tdp_mmu.c | 54 ++++++++++++++++++++++----------------
 2 files changed, 41 insertions(+), 40 deletions(-)
```
#### [PATCH v7 0/6] Enable CET support for guest 
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Feb 26 02:20:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12105641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 80506C433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 02:10:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2311664EFA
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 02:10:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229598AbhBZCKI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Feb 2021 21:10:08 -0500
Received: from mga03.intel.com ([134.134.136.65]:38815 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229498AbhBZCKH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Feb 2021 21:10:07 -0500
IronPort-SDR: 
 YkgfKQUQ8X8qrUqsuJFY+NxLXO4cVQz5GLjJKSNO6lTjiaUKTJfAl4PgGC5maKwA+1s9Oodpti
 2LrpQ25T6qNw==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="185800989"
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="185800989"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Feb 2021 18:09:26 -0800
IronPort-SDR: 
 xOwwmjowfjV7aycmDHUcC2m3gRoi3SONIf7RDFAKjUpQRXe4oqDnD/qwg3zVOScMfnsfEnGbNy
 VtdFHPSr8NaA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.81,207,1610438400";
   d="scan'208";a="404679897"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.166])
  by orsmga008.jf.intel.com with ESMTP; 25 Feb 2021 18:09:24 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, richard.henderson@linaro.org,
        ehabkost@redhat.com, mtosatti@redhat.com,
        sean.j.christopherson@intel.com, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v7 0/6] Enable CET support for guest 
Date: Fri, 26 Feb 2021 10:20:52 +0800
Message-Id: <20210226022058.24562-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP). It includes two features:
Shadow Stack(SHSTK) and Indirect Branch Tracking(IBT).
This patch series is to enable CET related CPUID report, XSAVES/XRSTORS
support and MSR access etc. for guest.

Change in v7:
- Reverted part of XSAVE feature-word naming change per review feedback.
- Fixed an issue blocking SHSTK and IBT used as two independent features
  if OS just enables either of them.
- Other minor changes during testing and review.
- Rebased to 5.2.0 base.

CET KVM patches:
https://lkml.kernel.org/r/20210203113421.5759-1-weijiang.yang@intel.com

CET kernel patches:
https://lkml.kernel.org/r/20210217222730.15819-1-yu-cheng.yu@intel.com


Yang Weijiang (6):
  target/i386: Change XSAVE related feature-word names
  target/i386: Enable XSS feature enumeration for CPUID
  target/i386: Enable CET components support for XSAVES
  target/i386: Add user-space MSR access interface for CET
  target/i386: Add CET state support for guest migration
  target/i386: Advise CET bits in CPU/MSR feature words

 target/i386/cpu.c     | 113 +++++++++++++++++++++++------
 target/i386/cpu.h     |  55 ++++++++++++++-
 target/i386/kvm.c     |  72 +++++++++++++++++++
 target/i386/machine.c | 161 ++++++++++++++++++++++++++++++++++++++++++
 4 files changed, 379 insertions(+), 22 deletions(-)
```
#### [RFC PATCH v6 00/25] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Fri Feb 26 12:14:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12106535
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F23CFC433DB
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:15:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 934D364EF3
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 12:15:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230254AbhBZMPa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 07:15:30 -0500
Received: from mga09.intel.com ([134.134.136.24]:44724 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229947AbhBZMPQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 07:15:16 -0500
IronPort-SDR: 
 bIUFwaIIyawWlH5EIPNB6kW9wZgSMEJPaoNPVyHiiAqcPIfXCD/quZ/fMHL5gwPGc3iFYqZX7M
 /DTKTg5gy9aw==
X-IronPort-AV: E=McAfee;i="6000,8403,9906"; a="185979801"
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="185979801"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 04:14:31 -0800
IronPort-SDR: 
 i9cEm/zobPm9zvxi/LevDzF9vCMV1cq6LmMXl0vz70xylmYPZmFvancAuw7g9Ymq2JueodDvou
 ReqQ9essPFhg==
X-IronPort-AV: E=Sophos;i="5.81,208,1610438400";
   d="scan'208";a="598420290"
Received: from ciparjol-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.230.175])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 04:14:26 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH v6 00/25] KVM SGX virtualization support
Date: Sat, 27 Feb 2021 01:14:08 +1300
Message-Id: <cover.1614338774.git.kai.huang@intel.com>
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

This series is based against latest kvm/queue branch (+4 SGX patches reside on
tip/x86/sgx to avoid conflict on x86 part patches), since patch (KVM: VMX:
Convert vcpu_vmx.exit_reason to a union) in previous version (v5) has already
been merged via another series. Some other recent KVM patches also requires KVM
patches in this series to be rebased.

You can also get the code from upstream branch of kvm-sgx repo on github:

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

v5->v6:

 - Main change for x86 part patches is asm/sgx_arch.h is removed and merged to
   asm/sgx.h, based on Boris's suggestion, and this caused some minor changes to
   other patches due to header file name being different.
 - For KVM part patches, removed patch (KVM: VMX: Convert vcpu_vmx.exit_reason
   to a union), since it has already been merged to upstream KVM. Also rebased
   rest of KVM part patches based on latest KVM upstream code.

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

Sean Christopherson (21):
  x86/cpufeatures: Add SGX1 and SGX2 sub-features
  x86/sgx: Add SGX_CHILD_PRESENT hardware error code
  x86/sgx: Introduce virtual EPC for use by KVM guests
  x86/cpu/intel: Allow SGX virtualization without Launch Control support
  x86/sgx: Expose SGX architectural definitions to the kernel
  x86/sgx: Move ENCLS leaf definitions to sgx.h
  x86/sgx: Add SGX2 ENCLS leaf definitions (EAUG, EMODPR and EMODT)
  x86/sgx: Add encls_faulted() helper
  x86/sgx: Add helpers to expose ECREATE and EINIT to KVM
  x86/sgx: Move provisioning device creation out of SGX driver
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
 .../cpu/sgx/arch.h => include/asm/sgx.h}      |  50 +-
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  69 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  28 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  92 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 355 +++++++++++++
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  28 +-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 465 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 102 +++-
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  23 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 32 files changed, 1419 insertions(+), 116 deletions(-)
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx.h} (89%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [Patch V2 00/13] Introduce dev-msi and interrupt message store
##### From: Megha Dey <megha.dey@intel.com>

```c
From patchwork Fri Feb 26 20:11:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Megha Dey <megha.dey@intel.com>
X-Patchwork-Id: 12107279
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 548ABC433E0
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 20:13:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F8A964DA3
	for <kvm@archiver.kernel.org>; Fri, 26 Feb 2021 20:13:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230483AbhBZUNj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 26 Feb 2021 15:13:39 -0500
Received: from mga17.intel.com ([192.55.52.151]:35622 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230499AbhBZUMS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 26 Feb 2021 15:12:18 -0500
IronPort-SDR: 
 0VH7UVv6n/P8mi/L6jfGs265VWL+OxZobzsd9SvmD8AehOdVoe/Qh9DMvENQpLR4HtIG7p2zFq
 xyHVkfrfXxhw==
X-IronPort-AV: E=McAfee;i="6000,8403,9907"; a="165846877"
X-IronPort-AV: E=Sophos;i="5.81,209,1610438400";
   d="scan'208";a="165846877"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Feb 2021 12:11:11 -0800
IronPort-SDR: 
 cTSVECa2hdLFNJLim2z71HtSUBwJyst+3D5Qbkc7AVEojga5QGDHb/ASpd0egVH/tSElCl2ryW
 ISeqwpr9MxzA==
X-IronPort-AV: E=Sophos;i="5.81,209,1610438400";
   d="scan'208";a="405109413"
Received: from megha-z97x-ud7-th.sc.intel.com ([143.183.85.154])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-SHA;
 26 Feb 2021 12:11:10 -0800
From: Megha Dey <megha.dey@intel.com>
To: tglx@linutronix.de
Cc: linux-kernel@vger.kernel.org, dave.jiang@intel.com,
        ashok.raj@intel.com, kevin.tian@intel.com, dwmw@amazon.co.uk,
        x86@kernel.org, tony.luck@intel.com, dan.j.williams@intel.com,
        megha.dey@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        iommu@lists.linux-foundation.org, alex.williamson@redhat.com,
        bhelgaas@google.com, maz@kernel.org, linux-pci@vger.kernel.org,
        baolu.lu@linux.intel.com, ravi.v.shankar@intel.com
Subject: [Patch V2 00/13] Introduce dev-msi and interrupt message store
Date: Fri, 26 Feb 2021 12:11:04 -0800
Message-Id: <1614370277-23235-1-git-send-email-megha.dey@intel.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Provide support for device specific MSI implementations for devices which
have their own resource management and interrupt chip. These devices are
not related to PCI and contrary to platform MSI they do not share a
common resource and interrupt chip. They provide their own domain specific
resource management and interrupt chip.

On top of this, add support for Interrupt Message Store or IMS[1], which
is a scalable device specific interrupt mechanism to support devices which
may need more than 2048 interrupts. With IMS, there is theoretically no
upper bound on the number of interrupts a device can support. The normal
IMS use case is for guest usages but it can very well be used by host too.

Introduce a generic IMS irq chip and domain which stores the interrupt
messages as an array in device memory. Allocation and freeing of interrupts
happens via the generic msi_domain_alloc/free_irqs() interface. One only
needs to ensure the interrupt domain is stored in the underlying device struct.

These patches can be divided into following steps:

1. X86 specific preparation for device MSI
   x86/irq: Add DEV_MSI allocation type
   x86/msi: Rename and rework pci_msi_prepare() to cover non-PCI MSI

2. Generic device MSI infrastructure
   platform-msi: Provide default irq_chip:: Ack
   genirq/proc: Take buslock on affinity write
   genirq/msi: Provide and use msi_domain_set_default_info_flags()
   platform-msi: Add device MSI infrastructure
   irqdomain/msi: Provide msi_alloc/free_store() callbacks
   genirq: Set auxiliary data for an interrupt
   genirq/msi: Provide helpers to return Linux IRQ/dev_msi hw IRQ number

3. Interrupt Message Store (IMS) irq domain/chip implementation for device array
   irqchip: Add IMS (Interrupt Message Store) driver
   iommu/vt-d: Add DEV-MSI support

4. Add platform check for subdevice irq domain
   iommu: Add capability IOMMU_CAP_VIOMMU
   platform-msi: Add platform check for subdevice irq domain

The device IMS (Interrupt Message Storage) should not be enabled in any
virtualization environments unless there is a HYPERCALL domain which
makes the changes in the message store monitored by the hypervisor.[2]
As the initial step, we allow the IMS to be enabled only if we are
running on the bare metal. It's easy to enable IMS in the virtualization
environments if above preconditions are met in the future.

These patches have been tested with the IDXD driver:
        https://github.com/intel/idxd-driver idxd-stage2.5
Most of these patches are originally by Thomas:
        https://lore.kernel.org/linux-hyperv/20200826111628.794979401@linutronix.de/
and are rebased on latest kernel.

This patches series has undergone a lot of changes since first submitted as an RFC
in September 2019. I have divided the changes into 3 stages for better understanding:

Stage 1: Standalone RFC IMS series[3]
-------------------------------------
https://lore.kernel.org/lkml/1568338328-22458-1-git-send-email-megha.dey@linux.intel.com/
V1:
1. Extend existing platform-msi to support IMS
2. platform_msi_domain_alloc_irqs_group is introduced to allocate IMS
   interrupts, tagged with a group ID.
3. To free vectors of a particular group, platform_msi_domain_free_irqs_group
   API in introduced

Stage 2: dev-msi/IMS merged with Dave Jiang's IDXD series[2]
------------------------------------------------------------
V1: (changes from stage 1):
1. Introduced a new list for platform-msi descriptors
2. Introduced dynamic allocation for IMS interrupts
3. shifted creation of ims domain from arch/x86 to drivers/
4. Removed arch specific callbacks
5. Introduced enum platform_msi_type
6. Added more technical details to the cover letter
7. Merge common code between platform-msi.c and ims-msi.c
8. Introduce new structures platform_msi_ops and platform_msi_funcs
9. Addressed Andriy Shevchenko's comments on RFC V1 patch series
10. Dropped the dynamic group allocation scheme.
11. Use RCU lock instead of mutex lock to protect the device list

V2:
1. IMS made dev-msi
2. With recommendations from Jason/Thomas/Dan on making IMS more generic
3. Pass a non-pci generic device(struct device) for IMS management instead of mdev
4. Remove all references to mdev and symbol_get/put
5. Remove all references to IMS in common code and replace with dev-msi
6. Remove dynamic allocation of platform-msi interrupts: no groups,no
   new msi list or list helpers
7. Create a generic dev-msi domain with and without interrupt remapping enabled.
8. Introduce dev_msi_domain_alloc_irqs and dev_msi_domain_free_irqs apis

V3:
1. No need to add support for 2 different dev-msi irq domains, a common
   once can be used for both the cases(with IR enabled/disabled)
2. Add arch specific function to specify additions to msi_prepare callback
   instead of making the callback a weak function
3. Call platform ops directly instead of a wrapper function
4. Make mask/unmask callbacks as void functions
5. dev->msi_domain should be updated at the device driver level before
   calling dev_msi_alloc_irqs()
6. dev_msi_alloc/free_irqs() cannot be used for PCI devices
7. Followed the generic layering scheme: infrastructure bits->arch bits->enabling bits

V4:
1. Make interrupt remapping code more readable
2. Add flush writes to unmask/write and reset ims slots
3. Interrupt Message Storm-> Interrupt Message Store
4. Merge in pasid programming code.

Stage 3: Standalone dev-msi and IMS driver series
-------------------------------------------------
V1:(Changes from Stage 2 V4)[6]
1. Split dev-msi/IMS code from Dave Jiang’s IDXD patch series
2. Set the source-id of all dev-msi interrupt requests to the parent PCI device
3. Separated core irq code from IMS related code
4. Added missing set_desc ops to the IMS msi_domain_ops
5. Added more details in the commit message-test case for auxillary interrupt data
6. Updated the copyright year from 2020 to 2021
7. Updated cover letter
8. Add platform check for subdevice irq domain (Lu Baolu):
   V1->V2:
   - V1 patches:[4]
   - Rename probably_on_bare_metal() with on_bare_metal();
   - Some vendors might use the same name for both bare metal and virtual
     environment. Before we add vendor specific code to distinguish
     between them, let's return false in on_bare_metal(). This won't
     introduce any regression. The only impact is that the coming new
     platform msi feature won't be supported until the vendor specific code
     is provided.
   V2->V3:
   - V2 patches:[5]
   - Add all identified heuristics so far

V1->V2:
1. s/arch_support_pci_device_ims/arch_support_pci_device_msi/g
2. Remove CONFIG_DEVICE_MSI in arch/x86/pci/common.c
3. Added helper functions to get linux IRQ and dev-msi HW IRQ numbers
4. Change the caching mode logic from dynamic to static

Dave Jiang (1):
  genirq/msi: Provide helpers to return Linux IRQ/dev_msi hw IRQ number

Lu Baolu (2):
  iommu: Add capability IOMMU_CAP_VIOMMU_HINT
  platform-msi: Add platform check for subdevice irq domain

Megha Dey (3):
  genirq: Set auxiliary data for an interrupt
  iommu/vt-d: Add DEV-MSI support
  irqchip: Add IMS (Interrupt Message Store) driver

Thomas Gleixner (7):
  x86/irq: Add DEV_MSI allocation type
  x86/msi: Rename and rework pci_msi_prepare() to cover non-PCI MSI
  platform-msi: Provide default irq_chip:: Ack
  genirq/proc: Take buslock on affinity write
  genirq/msi: Provide and use msi_domain_set_default_info_flags()
  platform-msi: Add device MSI infrastructure
  irqdomain/msi: Provide msi_alloc/free_store() callbacks

 arch/x86/include/asm/hw_irq.h       |   1 +
 arch/x86/include/asm/msi.h          |   4 +-
 arch/x86/kernel/apic/msi.c          |  27 +++--
 arch/x86/pci/common.c               |  72 ++++++++++++
 drivers/base/platform-msi.c         | 141 ++++++++++++++++++++++++
 drivers/iommu/amd/iommu.c           |   2 +
 drivers/iommu/intel/iommu.c         |   5 +
 drivers/iommu/intel/irq_remapping.c |   6 +-
 drivers/iommu/virtio-iommu.c        |   9 ++
 drivers/irqchip/Kconfig             |  14 +++
 drivers/irqchip/Makefile            |   1 +
 drivers/irqchip/irq-ims-msi.c       | 211 ++++++++++++++++++++++++++++++++++++
 drivers/pci/controller/pci-hyperv.c |   2 +-
 drivers/pci/msi.c                   |   7 +-
 include/linux/interrupt.h           |   2 +
 include/linux/iommu.h               |   2 +
 include/linux/irq.h                 |   4 +
 include/linux/irqchip/irq-ims-msi.h |  68 ++++++++++++
 include/linux/irqdomain.h           |   1 +
 include/linux/msi.h                 |  41 +++++++
 kernel/irq/Kconfig                  |   4 +
 kernel/irq/manage.c                 |  38 ++++++-
 kernel/irq/msi.c                    |  79 ++++++++++++++
 23 files changed, 722 insertions(+), 19 deletions(-)
 create mode 100644 drivers/irqchip/irq-ims-msi.c
 create mode 100644 include/linux/irqchip/irq-ims-msi.h
```
