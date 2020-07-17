

#### [RESEND PATCH v13 00/11] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Thu Jul 16 03:16:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11666589
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E2E6138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:18:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F3E5020791
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:18:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728189AbgGPDQ6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:16:58 -0400
Received: from mga06.intel.com ([134.134.136.31]:8143 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728149AbgGPDQ4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:16:56 -0400
IronPort-SDR: 
 1n3+rtKl315Fpj7xjL7c7EdpqVOBmZXVrlbcAynUN4EuST0RvSVFlJIC2ZRqF4w018/cru1jWs
 Fqf3HWyoVvjg==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="210844827"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="210844827"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:16:55 -0700
IronPort-SDR: 
 WcX57bLryolWS71PxD9B4xqX2K/v7gerMW1I+hLtAkpIn0FpDYDeDdu/htFLlZlhBrTI4PGhli
 88dsjn2ksdww==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="360910405"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga001.jf.intel.com with ESMTP; 15 Jul 2020 20:16:53 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [RESEND PATCH v13 00/11] Introduce support for guest CET feature
Date: Thu, 16 Jul 2020 11:16:16 +0800
Message-Id: <20200716031627.11492-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. There're two CET
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).
SHSTK is to prevent ROP programming and IBT is to prevent JOP programming.

Several parts in KVM have been updated to provide VM CET support, including:
CPUID/XSAVES config, MSR pass-through, user space MSR access interface, 
vmentry/vmexit config, nested VM etc. These patches have dependency on CET
kernel patches for xsaves support and CET definitions, e.g., MSR and related
feature flags.

CET kernel patches are here:
https://lkml.kernel.org/r/20200429220732.31602-1-yu-cheng.yu@intel.com

v13:
- Added CET definitions as a separate patch to facilitate KVM test.
- Disabled CET support in KVM if unrestricted_guest is turned off since
  in this case CET related instructions/infrastructure cannot be emulated
  well.
- Don't expose CET feature to guest if host kernel doesn't support CET.
- Rebased the series to v5.8-rc5, commit: 11ba468877bb

v12:
- Fixed a few issues per Sean and Paolo's review feeback.
- Refactored patches to make them properly arranged.
- Removed unnecessary hard-coded CET states for host/guest.
- Added compile-time assertions for vmcs_field_to_offset_table to detect
  mismatch of the field type and field encoding number.
- Added a custom MSR MSR_KVM_GUEST_SSP for guest active SSP save/restore.
- Rebased patches to 5.7-rc3.

v11:
- Fixed a guest vmentry failure issue when guest reboots.
- Used vm_xxx_control_{set, clear}bit() to avoid side effect, it'll
  clear cached data instead of pure VMCS field bits.
- Added vcpu->arch.guest_supported_xss dedidated for guest runtime mask,
  this avoids supported_xss overwritten issue caused by an old qemu.
- Separated vmentry/vmexit state setting with CR0/CR4 dependency check
  to make the patch more clear.
- Added CET VMCS states in dump_vmcs() for debugging purpose.
- Other refactor based on testing.
- This patch serial is built on top of below branch and CET kernel patches
  for seeking xsaves support:
  https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=cpu-caps

v10:
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.

Sean Christopherson (1):
  KVM: x86: Load guest fpu state when access MSRs managed by XSAVES

Yang Weijiang (10):
  KVM: x86: Include CET definitions for KVM test purpose
  KVM: VMX: Introduce CET VMCS fields and flags
  KVM: VMX: Set guest CET MSRs per KVM and host configuration
  KVM: VMX: Configure CET settings upon guest CR0/4 changing
  KVM: x86: Refresh CPUID once guest changes XSS bits
  KVM: x86: Add userspace access interface for CET MSRs
  KVM: VMX: Enable CET support for nested VM
  KVM: VMX: Add VMCS dump and sanity check for CET states
  KVM: x86: Add #CP support in guest exception dispatch
  KVM: x86: Enable CET virtualization and advertise CET to userspace

 arch/x86/include/asm/kvm_host.h      |   4 +-
 arch/x86/include/asm/vmx.h           |   8 +
 arch/x86/include/uapi/asm/kvm.h      |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |   7 +-
 arch/x86/kvm/cpuid.c                 |  28 ++-
 arch/x86/kvm/vmx/capabilities.h      |   5 +
 arch/x86/kvm/vmx/nested.c            |  34 ++++
 arch/x86/kvm/vmx/vmcs12.c            | 267 ++++++++++++++++-----------
 arch/x86/kvm/vmx/vmcs12.h            |  14 +-
 arch/x86/kvm/vmx/vmx.c               | 262 +++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   |  53 +++++-
 arch/x86/kvm/x86.h                   |   2 +-
 include/linux/kvm_host.h             |  32 ++++
 13 files changed, 590 insertions(+), 127 deletions(-)
```
#### [PATCH 0/9] KVM: x86: TDP level cleanups and shadow NPT fix
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Jul 16 03:41:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11666623
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAE26722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:42:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D28AF2076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:42:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728157AbgGPDlZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:41:25 -0400
Received: from mga11.intel.com ([192.55.52.93]:49384 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726905AbgGPDlZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:41:25 -0400
IronPort-SDR: 
 /rECrXmQotmxWnPcx0EoBt6V2wNPBDb2Z8LG1TYxqHOzKG0WytouaPiF++duP31wDYk9/IFbTx
 ptA1ef/0q3/w==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="147310947"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="147310947"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:41:24 -0700
IronPort-SDR: 
 7CSdzCyxxWWy3tQqd6zryT58WT1lkLoWGg/ZFMryPCvwMYmrGoyVST5LGfeq3X+BMNHUbM4vmj
 UfVSxyC6ZQXg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="316905467"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga008.jf.intel.com with ESMTP; 15 Jul 2020 20:41:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/9] KVM: x86: TDP level cleanups and shadow NPT fix
Date: Wed, 15 Jul 2020 20:41:13 -0700
Message-Id: <20200716034122.5998-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The primary purpose of this series is to implement a suggestion from Paolo
to have the MMU make the decision between 4 and 5 level EPT/TDP (when
5-level page tables are supported).  Having the MMU "own" the decision of
whether or not to use 5-level paging leads to a variety of nice cleanups,
and ultimately gets rid of another kvm_x86_ops.

Patch 1 is a fix for SVM's shadow NPT that is compile tested only.  I
don't know enough about the shadow NPT details to know if it's a "real"
bug or just a supericial oddity that can't actually cause problems.

"Remove temporary WARN on expected vs. actual EPTP level mismatch" could
easily be squashed with "Pull the PGD's level from the MMU instead of
recalculating it", I threw it in as a separate patch to provide a
bisection helper in case things go sideways.

Sean Christopherson (9):
  KVM: nSVM: Correctly set the shadow NPT root level in its MMU role
  KVM: x86/mmu: Add separate helper for shadow NPT root page role calc
  KVM: VMX: Drop a duplicate declaration of construct_eptp()
  KVM: VMX: Make vmx_load_mmu_pgd() static
  KVM: x86: Pull the PGD's level from the MMU instead of recalculating
    it
  KVM: VXM: Remove temporary WARN on expected vs. actual EPTP level
    mismatch
  KVM: x86: Dynamically calculate TDP level from max level and
    MAXPHYADDR
  KVM: x86/mmu: Rename max_page_level to max_huge_page_level
  KVM: x86: Specify max TDP level via kvm_configure_mmu()

 arch/x86/include/asm/kvm_host.h |  9 ++---
 arch/x86/kvm/cpuid.c            |  2 --
 arch/x86/kvm/mmu.h              | 10 ++++--
 arch/x86/kvm/mmu/mmu.c          | 63 +++++++++++++++++++++++++--------
 arch/x86/kvm/svm/nested.c       |  1 -
 arch/x86/kvm/svm/svm.c          |  8 ++---
 arch/x86/kvm/vmx/nested.c       |  2 +-
 arch/x86/kvm/vmx/vmx.c          | 31 +++++++---------
 arch/x86/kvm/vmx/vmx.h          |  6 ++--
 arch/x86/kvm/x86.c              |  1 -
 10 files changed, 81 insertions(+), 52 deletions(-)
```
#### [PATCH 0/3] KVM: VMX: Clean up RTIT MAXPHYADDR usage
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Jul 16 03:44:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11666627
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D450360D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:44:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5F3C2075F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 03:44:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728300AbgGPDoM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 15 Jul 2020 23:44:12 -0400
Received: from mga09.intel.com ([134.134.136.24]:54949 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726905AbgGPDoL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 15 Jul 2020 23:44:11 -0400
IronPort-SDR: 
 rrdjT8Kh/Aqb5wHcOYeYfj7aCSZMGB9dkkEbUef91a+mI/Z3NDDexkuude93/mlMxsGTibSQKt
 xYAUoy7eHsLQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="150699761"
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="150699761"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Jul 2020 20:44:10 -0700
IronPort-SDR: 
 cAuAFNKXBGmV5pOIWhocUCC1JqwEtI7ncH5HpTHwW4pvIncSzWWBL6s3nlNM4eeLeXygHnUdZ2
 PuMonLEU/veQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,357,1589266800";
   d="scan'208";a="282314257"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga003.jf.intel.com with ESMTP; 15 Jul 2020 20:44:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] KVM: VMX: Clean up RTIT MAXPHYADDR usage
Date: Wed, 15 Jul 2020 20:44:05 -0700
Message-Id: <20200716034408.6342-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Stop using cpuid_query_maxphyaddr() for a random RTIT MSR check and
unexport said function to discourage future use.

Sean Christopherson (3):
  KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
  KVM: VMX: Replace MSR_IA32_RTIT_OUTPUT_BASE_MASK with helper function
  KVM: x86: Unexport cpuid_query_maxphyaddr()

 arch/x86/kvm/cpuid.c   |  1 -
 arch/x86/kvm/vmx/vmx.c | 11 +++++++----
 2 files changed, 7 insertions(+), 5 deletions(-)
```
#### [kvm-unit-tests PATCH v13 0/9] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Jul 16 08:23:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11666869
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8B35C138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 08:23:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F2E620775
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 08:23:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727888AbgGPIXu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 04:23:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:40096 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725922AbgGPIXj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Jul 2020 04:23:39 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06G8LhVw162515;
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 329d9k0ykk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 04:23:36 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06G84CRv100416;
        Thu, 16 Jul 2020 04:23:35 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 329d9k0yjv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 04:23:35 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06G8JwYc015902;
        Thu, 16 Jul 2020 08:23:34 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma02fra.de.ibm.com with ESMTP id 327527wgh9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 16 Jul 2020 08:23:33 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06G8M8F162521690
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 16 Jul 2020 08:22:09 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A28654C044;
        Thu, 16 Jul 2020 08:23:31 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 286204C05A;
        Thu, 16 Jul 2020 08:23:31 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.61.186])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 16 Jul 2020 08:23:31 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v13 0/9] s390x: Testing the Channel Subsystem
 I/O
Date: Thu, 16 Jul 2020 10:23:20 +0200
Message-Id: <1594887809-10521-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-16_04:2020-07-16,2020-07-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxlogscore=999
 suspectscore=1 malwarescore=0 adultscore=0 mlxscore=0 lowpriorityscore=0
 priorityscore=1501 clxscore=1015 spamscore=0 phishscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007160058
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All,

This new respin of the series add modifications to
- patch 9: s390x: css: ssch/tsch with sense and interrupt
Other patches did not change.

Recall:

Goal of the series is to have a framework to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test program to define its own
interrupt handler. We need to do special work under interrupt like acknowledging
the interrupt.
  
This series presents three tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled, retrying a predefined count on failure
	to enable the channel
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analyzing the answer and expecting
        the Control unit type being 0x3832, a.k.a. virtio-ccw.
        Checks SSCH(READ) and IO-IRQ

Note:
- The following 5 patches are general usage and may be pulled first:
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt

- These 4 patches are really I/O oriented:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

Regards,
Pierre

Pierre Morel (9):
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

 lib/s390x/asm/arch_def.h |  14 ++
 lib/s390x/asm/time.h     |  50 ++++++
 lib/s390x/css.h          | 294 +++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 152 ++++++++++++++++++
 lib/s390x/css_lib.c      | 323 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/interrupt.c    |  23 ++-
 lib/s390x/interrupt.h    |   8 +
 s390x/Makefile           |   3 +
 s390x/css.c              | 150 ++++++++++++++++++
 s390x/cstart64.S         |  41 ++++-
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 12 files changed, 1060 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH V2 0/6] IRQ offloading for vDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Thu Jul 16 11:23:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11667179
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 264A1722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 11:27:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0EC552078C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 11:27:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728110AbgGPL1i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 07:27:38 -0400
Received: from mga03.intel.com ([134.134.136.65]:8123 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726350AbgGPL1i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jul 2020 07:27:38 -0400
IronPort-SDR: 
 xV2xPLtzzTvfoU1Val7CBl6MBpr367vLrC4pw7YvMBTpTNWIo5WOhB2FdLppJXwssMYF1Yh23+
 Bi5n7mxMkeUw==
X-IronPort-AV: E=McAfee;i="6000,8403,9683"; a="149350090"
X-IronPort-AV: E=Sophos;i="5.75,359,1589266800";
   d="scan'208";a="149350090"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Jul 2020 04:27:37 -0700
IronPort-SDR: 
 jIW0pVSPd9YOifcBmO2kcenGTvkvM/k72dY+Xq6a0AnDPgBKdN9CrLKYyCg/fcEUegZ+tep4nf
 4E5kfBa3HtoQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,359,1589266800";
   d="scan'208";a="460442794"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga005.jf.intel.com with ESMTP; 16 Jul 2020 04:27:34 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, alex.williamson@redhat.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, wanpengli@tencent.com,
        jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 0/6] IRQ offloading for vDPA
Date: Thu, 16 Jul 2020 19:23:43 +0800
Message-Id: <1594898629-18790-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intends to implement IRQ offloading for
vhost_vdpa.

By the feat of irq forwarding facilities like posted
interrupt on X86, irq bypass can  help deliver
interrupts to vCPU directly.

vDPA devices have dedicated hardware backends like VFIO
pass-throughed devices. So it would be possible to setup
irq offloading(irq bypass) for vDPA devices and gain
performance improvements.

In my testing, with this feature, we can save 0.1ms
in a ping between two VFs on average.

changes from V1:
(1)dropped vfio changes.
(3)removed KVM_HVAE_IRQ_BYPASS checks
(4)locking fixes
(5)simplified vhost_vdpa_update_vq_irq()
(6)minor improvements

Zhu Lingshan (6):
  vhost: introduce vhost_call_ctx
  kvm: detect assigned device via irqbypass manager
  vDPA: implement IRQ offloading helpers in vDPA core
  vhost_vdpa: implement IRQ offloading in vhost_vdpa
  ifcvf: replace irq_request/free with vDPA helpers
  irqbypass: do not start cons/prod when failed connect

 arch/x86/kvm/x86.c              | 10 ++++++--
 drivers/vdpa/ifcvf/ifcvf_main.c | 14 +++++++----
 drivers/vdpa/vdpa.c             | 42 +++++++++++++++++++++++++++++++++
 drivers/vhost/Kconfig           |  1 +
 drivers/vhost/vdpa.c            | 52 +++++++++++++++++++++++++++++++++++++++--
 drivers/vhost/vhost.c           | 22 ++++++++++++-----
 drivers/vhost/vhost.h           |  9 ++++++-
 include/linux/vdpa.h            | 13 +++++++++++
 virt/lib/irqbypass.c            | 16 ++++++++-----
 9 files changed, 157 insertions(+), 22 deletions(-)
```
#### [patch V3 00/13] entry, x86, kvm: Generic entry/exit functionality
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Thu Jul 16 18:22:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11668355
Return-Path: <SRS0=rfeS=A3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 221FF13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:50:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 060AE20787
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 16 Jul 2020 19:50:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="Gp0vrB0K";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="jaxV93x6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729572AbgGPTuo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Jul 2020 15:50:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40956 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728907AbgGPTuo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 16 Jul 2020 15:50:44 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E7B59C061755;
        Thu, 16 Jul 2020 12:50:43 -0700 (PDT)
Message-Id: <20200716182208.180916541@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1594929042;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=Bjj7oiuRW+Sn6djHD3J8UrXi90X+AdJC+ynLaAISnUE=;
        b=Gp0vrB0KO5JHo1WpPfLS4VlBjitnSx1+8FCvtPTxhCeJISgPK2egD963B4xmSCKJN6O5DY
        ZoLrDfFzyU/kvIxQZ+UUBWQSuCGhxLA1vWOjRDNDBJtyC3Pz4W3S7XLe5cgF5zg1fISWoh
        ISz6rBYpw+ZD2TYtS5Ulla0ykiGjli1tCwJXVEn9hHji7SitwrZwsU3ywBSkBcNL8C+0Ox
        g+V1IMYmNYqbtHtR2iqCR3/Tp2quLDij5FxOZ+yQe97Neh46bCZhs3xLrU5j+XDDSo3iBr
        w59+dRh0JsAeyUkJyLXfVszU5a7VOtAMouS3qgQKjpR1bEeKZsXrQ+OenRZM5A==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1594929042;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=Bjj7oiuRW+Sn6djHD3J8UrXi90X+AdJC+ynLaAISnUE=;
        b=jaxV93x6mgTMuZbylYxYwP8YAvSed8CXqXGojSoBxO64T7KbIky1sorctWMQAZEwZ3DgNy
        PYVdNiCSRZhrqoAA==
Date: Thu, 16 Jul 2020 20:22:08 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [patch V3 00/13] entry, x86, kvm: Generic entry/exit functionality
 for host and guest
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the 3rd version of preparing KVM to handle TIF_NOTIFY_RESUME before
exiting to guest mode.

The first attempt is available here:

    https://lore.kernel.org/r/20190801143250.370326052@linutronix.de

The second version which tried to provide generic infrastructure for KVM
can be found here:

    https://lore.kernel.org/r/20191023122705.198339581@linutronix.de

This started the whole discussion about entry code correctness which led to
the complete overhaul of the x86 entry code, non-instrumentable sections
and the other goodies which are in 5.8.

The remaining bits are rather straight forward:

  1) Move the entry/exit handling from x86 into generic code so other
     architectures can reuse the already proven to be correct code instead
     of duplicating the whole maze and creating slightly different beasts
     again.

     This utilizes the noinstr sections. The correctness of the confinement
     of non-instrumentable code can be verified with objtool on
     architectures which support it. The code code itself is clean.

  2) Provide generic work handling functionality for KVM
  
  3) Convert x86 over to use the generic entry/exit code

  4) Convert x86/KVM to use the generic work handling functionality.

#4 finally paves the way to move POSIX CPU timer heavy lifting out of
interrupt context into task work. Several hundred patches after the initial
attempt which was small and simple :)

The patches depend on:

    git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git x86/entry

The lot is also available from git:

    git://git.kernel.org/pub/scm/linux/kernel/git/tglx/devel.git x86/entry

The posix timer patches will be posted seperately as they are mostly
independent (except for the KVM task work detail).

The stub functions for the architecture specific parts which need to be
provided by architectures utilizing this are completely documented in the
corresponding header file which explains the diffstat.

Thanks,

	tglx

----
 arch/Kconfig                        |    3 
 arch/x86/Kconfig                    |    1 
 arch/x86/entry/common.c             |  632 ++----------------------------------
 arch/x86/entry/entry_32.S           |    2 
 arch/x86/entry/entry_64.S           |    2 
 arch/x86/include/asm/entry-common.h |  135 +++++++
 arch/x86/include/asm/idtentry.h     |   39 --
 arch/x86/include/asm/ptrace.h       |   15 
 arch/x86/include/asm/signal.h       |    1 
 arch/x86/include/asm/thread_info.h  |    5 
 arch/x86/kernel/cpu/mce/core.c      |    4 
 arch/x86/kernel/kvm.c               |    6 
 arch/x86/kernel/signal.c            |    2 
 arch/x86/kernel/traps.c             |   24 -
 arch/x86/kvm/Kconfig                |    1 
 arch/x86/kvm/vmx/vmx.c              |   11 
 arch/x86/kvm/x86.c                  |   15 
 arch/x86/mm/fault.c                 |    6 
 include/linux/entry-common.h        |  398 ++++++++++++++++++++++
 include/linux/entry-kvm.h           |   80 ++++
 include/linux/kvm_host.h            |    8 
 kernel/Makefile                     |    1 
 kernel/entry/Makefile               |    4 
 kernel/entry/common.c               |  364 ++++++++++++++++++++
 kernel/entry/kvm.c                  |   51 ++
 virt/kvm/Kconfig                    |    3 
 26 files changed, 1150 insertions(+), 663 deletions(-)
```
