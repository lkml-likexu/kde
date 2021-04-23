

#### [PATCH 0/5] KVM: x86: Use kernel x86 cpuid utilities in KVM selftests
##### From: Ricardo Koller <ricarkol@google.com>

```c
From patchwork Thu Apr 22 00:56:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12217253
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8AEF9C433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:56:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5393761428
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:56:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241798AbhDVA5L (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 20:57:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54874 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240981AbhDVA5L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 20:57:11 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 20F9DC06138A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:56:37 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id
 e20-20020ad442b40000b029019aa511c767so14796670qvr.18
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:56:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=NzxbZ+GAahgmxduXaRkOwY3LO03b4qVXF2kZFZVIV+M=;
        b=EY/Bkrwt7EOV0vOcFdHrNNLfJEudSb/z5dFRNAUDXJY6GzahV2RUbyBuxe43j5Ba/c
         37spJaQTJBA0XFya0TgE4ej7IfVEGU101kUiAdOEvipDBhjCIMth9aD+rTPMJIdwPaPg
         hcn7HCpOfL+gSOCUrgHTnzfsgYufCUfBlSF79muCJ7O3urR5Xr191bTTgniB/VglLH3B
         7qRpKMq8OMdWCjkovJKPox5LSfC4Y5RaQeKkigl3WkCVqvCdBVXtbk9dquRZ4wkt7QI+
         ZhKMowSwhzz2u/Ubd4zQWQK5WtVPcIQ9RxH4LaNWB/NCG6JRXIfsAmTifEaDku7qKosz
         RVIg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=NzxbZ+GAahgmxduXaRkOwY3LO03b4qVXF2kZFZVIV+M=;
        b=VpMR/OIdTVx4BraOhfnTF2zICQoluoJaOWd+ntrLKBShklqsYns+Y/oEXFyQitUbBF
         ekv79GGzQ/9XXLNVBZacxoabfe1lK68xw0XHYWfgHoK/8yNbtshTmlqV7QAGYcC5o65E
         0n3f2NHu81md/JGxnX+onO6aqisI07c3/fW6jZSaWQYJiTZPhVqHVKS2dSvcoj6OAyar
         tOfu/A0XTCW3pXuV4EQdgYWekCHO0UqDBzlgb5l0jTEsWTonTMBV2cQBf4PC9VJRWBw1
         niUopfjHQuhipXafTd7ncA6Bb5DuI9aPBPti5oDs9d3thnm4Kb6fvUJkfA2Qa1JaQJqd
         4AMg==
X-Gm-Message-State: AOAM533IFuyeYe2+QaXTt9qejbdYjulcZ8ctx1gUeIG0cSiRhM2F5Jr5
        8TpH14Pypea81LwrVL4YwCN8WehtKDllzg==
X-Google-Smtp-Source: 
 ABdhPJxAui1HQQb7EtOlgCHADfQilI+gHPBuOzi2tKt6XDOLsse2UiM5wVgrbw2fJk3VLdwlUNTHNMLXKlLN7Q==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a0c:9ad7:: with SMTP id
 k23mr702884qvf.24.1619052996218; Wed, 21 Apr 2021 17:56:36 -0700 (PDT)
Date: Wed, 21 Apr 2021 17:56:21 -0700
Message-Id: <20210422005626.564163-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH 0/5] KVM: x86: Use kernel x86 cpuid utilities in KVM selftests
From: Ricardo Koller <ricarkol@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        linux-kernel@vger.kernel.org, clang-built-linux@googlegroups.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kernel has a set of utilities and definitions to deal with x86 cpu
features.  The x86 KVM selftests don't use them, and instead have
evolved to use differing and ad-hoc methods for checking features. The
advantage of the kernel feature definitions is that they use a format
that embeds the info needed to extract them from cpuid (function, index,
and register to use).

The first 3 patches massage the related cpuid header files in the kernel
side, then copy them into tools/ so they can be included by selftests.
The last 2 patches replace the tests checking for cpu features to use
the definitions and utilities introduced from the kernel.

Thanks,
Ricardo

Ricardo Koller (5):
  KVM: x86: Move reverse CPUID helpers to separate header file
  x86/cpu: Expose CPUID regs, leaf and index definitions to tools
  tools headers x86: Copy cpuid helpers from the kernel
  KVM: selftests: Introduce utilities for checking x86 features
  KVM: selftests: Use kernel x86 cpuid features format

 arch/x86/events/intel/pt.c                    |   1 +
 arch/x86/include/asm/cpufeature.h             |  23 +-
 arch/x86/include/asm/processor.h              |  11 -
 arch/x86/kernel/cpu/scattered.c               |   2 +-
 arch/x86/kernel/cpuid.c                       |   2 +-
 arch/x86/kvm/cpuid.h                          | 177 +-----------
 arch/x86/kvm/reverse_cpuid.h                  | 185 +++++++++++++
 tools/arch/x86/include/asm/cpufeature.h       | 257 ++++++++++++++++++
 tools/arch/x86/include/asm/cpufeatures.h      |   3 +
 .../selftests/kvm/include/x86_64/cpuid.h      |  61 +++++
 .../selftests/kvm/include/x86_64/processor.h  |  16 --
 .../kvm/include/x86_64/reverse_cpuid.h        | 185 +++++++++++++
 .../selftests/kvm/include/x86_64/svm_util.h   |  11 +-
 tools/testing/selftests/kvm/lib/x86_64/svm.c  |   6 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   5 +-
 tools/testing/selftests/kvm/steal_time.c      |   5 +-
 .../kvm/x86_64/cr4_cpuid_sync_test.c          |  23 +-
 .../selftests/kvm/x86_64/set_sregs_test.c     |  25 +-
 .../selftests/kvm/x86_64/vmx_pmu_msrs_test.c  |   8 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c    |   5 +-
 .../selftests/kvm/x86_64/xss_msr_test.c       |  10 +-
 21 files changed, 749 insertions(+), 272 deletions(-)
 create mode 100644 arch/x86/kvm/reverse_cpuid.h
 create mode 100644 tools/arch/x86/include/asm/cpufeature.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/cpuid.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/reverse_cpuid.h
```
#### [PATCH v5 00/15] KVM: SVM: Misc SEV cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Apr 22 02:11:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217327
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 21C69C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:11:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6021613C3
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:11:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233824AbhDVCME (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:12:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42894 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230259AbhDVCMD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:12:03 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ACCBEC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:11:29 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 n129-20020a2527870000b02904ed02e1aab5so6502169ybn.21
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:11:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=BgeeFXLae7p4tESr7C5iEIirYqJ/bWWbWSvsNXof9Mg=;
        b=CjnWcAI4QFKQZG0WldgHzCpcPsyGBnmDdq6p48/9ZU0hDve7babqNP2g4IWXLZPNOI
         Fmjug1K+dQvzxn7273w0d6QhBVhcbcGwlvwCc+2lWVD2Edgt9mOk9f0zjzmWK5w6DSh4
         zq1EXDdUzDWXIs3JHD7WPkPnNPggOVy/6mtL/GZNZ9pKXYY5dqK0SP2hXONRMJkEdBJQ
         6LYaXsuJP9ie+Qw1jtdvzCp/VfzpUa9ayL/PX+k+xbcXI6qVciRXg4Wp1WBe2G1tMJuG
         Pc3v9mQ+54qYMP/CVqr4UyaVH7sJRYW7ri/3QZkFmjeATDhr+6sWIfGhppqZy+Zrn3aU
         oHDw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=BgeeFXLae7p4tESr7C5iEIirYqJ/bWWbWSvsNXof9Mg=;
        b=tD1QPM7F5rYGDYOm/ukxYGnoX+T5vmPrrMO+p5NvMwO1FIvglWuY3ddKiKueCtsGJB
         K4/BmfNx3BqxZzDxFT0Ayd5HYTV9N8Qv4M8/sOAsCg2/NabSXahyJcNhifY6TPLhd9Ms
         taSLNAhDGzFyCCJYaJ81Z6QPFkKcJN6XWyM6ZkEQ+uWnkkxy9ci8Yz6f/bCVZQNycaMs
         y8Nhy/SJRAZP9nhGPHraHw+fHam5PaHVAG/Ucn/HYb5JkRcknnHmbUKiZxRY1Tji7TOq
         aVY9Fswr8Ck/plOQoK3zgb+Zv9BhLNEGCTMmFCGMCNBxBEt1B6xlf6/gp8BvISrSNfL/
         /Z7A==
X-Gm-Message-State: AOAM532r6wOBFjT4/+MEnDH88Fc0cQfRBoH38OadjkOzcR+vfEHFhlVU
        VxSV1GL7VRyGecVPCwoZNe2HwoqC00U=
X-Google-Smtp-Source: 
 ABdhPJzALDiRE9aA270oh7sykTY9Efj6ng96S+sITefYvCrazk1t93p9SRCc0wcrZvcAgc0Fn9Uqi59VR/I=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:7085:: with SMTP id
 l127mr1381469ybc.293.1619057488960;
 Wed, 21 Apr 2021 19:11:28 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:11:10 -0700
Message-Id: <20210422021125.3417167-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v5 00/15] KVM: SVM: Misc SEV cleanups
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

Based kvm/queue-ish, commit 0e91d1992235 ("KVM: SVM: Allocate SEV command
structures on local stack"), to avoid the conflicting CPUID.0x8000_001F
patch sitting in kvm/queue.

v5:
 - Use Paolo's version of the CPUID.0x8000_001F patch, with some of my
   goo on top.  Paolo gets credit by introducing fewer bugs; v4 missed
   the SEV/SEV-ES module params and used the wrong reverse-CPUID index...
 - Add a patch to disable SEV/SEV-ES if NPT is disabled.
 - Rebased, as above.
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

Paolo Bonzini (1):
  KVM: SEV: Mask CPUID[0x8000001F].eax according to supported features

Sean Christopherson (14):
  KVM: SVM: Zero out the VMCB array used to track SEV ASID association
  KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
  KVM: SVM: Disable SEV/SEV-ES if NPT is disabled
  KVM: SVM: Move SEV module params/variables to sev.c
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
 arch/x86/kvm/cpuid.c               |  8 ++-
 arch/x86/kvm/cpuid.h               |  1 +
 arch/x86/kvm/svm/sev.c             | 80 ++++++++++++++++++++++--------
 arch/x86/kvm/svm/svm.c             | 57 +++++++++------------
 arch/x86/kvm/svm/svm.h             |  9 +---
 arch/x86/mm/mem_encrypt.c          | 12 ++---
 arch/x86/mm/mem_encrypt_identity.c |  1 -
 8 files changed, 97 insertions(+), 72 deletions(-)
```
#### [PATCH v2 0/9] KVM: x86: Fixes for (benign?) truncation bugs
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Apr 22 02:21:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217359
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBE9DC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:21:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 879AD61452
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:21:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234069AbhDVCWH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:22:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45224 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230000AbhDVCWG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:22:06 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7D057C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:21:31 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 e13-20020a25d30d0000b02904ec4109da25so18092208ybf.7
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:21:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=rT4lxch1DR2GkeTff1L00Dgn8Fdap0zTJCYmiCzUm04=;
        b=cbcIiOk5g9BZdG2KVvbh+6RjHbqX9y7SeN0xmJONeDTbp0AU4mgpeZXGGc9onqiH7j
         ALVukuNejcJXSE9ZZsuEOXPMZ99xqJmbGkeb6NBt2OgJLu/kFxOGfJ9EfvIR7xrzNpTV
         aRubpMvyxW/RM1OS8WQKQgW4Ml+sha1KWodw1oDc3xgxIPvCvoWqZMPkQPuUkNslnPAk
         3C5iA+ki2W8awuG+lwnOa+tAEh4ZaK31XnNSZ5fthc/NNQ5S7IA3gGMNJGZwcMr+bIDR
         qb1U+4AF2f4X1HhS5v1oIv297Mf+ap3KPVfwObzRWk/ioW+d+Njju3yiAO1qw1nisDRV
         iB/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=rT4lxch1DR2GkeTff1L00Dgn8Fdap0zTJCYmiCzUm04=;
        b=jRLqjSfuumJ7K2jhwqH77RyI0pznEj0XGavFk0b5CmR2J2jIvfkNL58GvejRwpKgWz
         jpuxN6w76dNXYfkNzy8BPzZDyrFkG5whvmc8LymAN/WubwQhqRCe96ZlKC++EP1cP37Z
         hCRPCCEUfN61+PZsGWJIbFL+4J+zS0c8RLFDFBGhwMCnJvcCWmeGqldWD0olHEUIFZdz
         9T4d+QOYK+tOgAF3zjnhoUG5RUTIrF/2162j5BVS2IvMFjalEisOwO24sMH5MhF6Gnrp
         CSu8ULFIt01wxYI76HhxxsHXyu5tWNDhtR8aY3JVvY6T8xTXfdg11viRb7EYh1P+2T8/
         zN8w==
X-Gm-Message-State: AOAM532vHQhXFf8/WlMAo8OWxEa/D96emoziQkeOy/U82boa/YKDmoqK
        S8wESRvQnqD+1X7GdrbESxOSft4axaY=
X-Google-Smtp-Source: 
 ABdhPJwPERXJ8ChGU08WyQVlfjTE3keyNalrjLGd3NiD+Dg08UYAQFyjxuxKTcJElOjwYxuZY+YCeKBIh/4=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:b098:: with SMTP id
 f24mr1441373ybj.210.1619058090787;
 Wed, 21 Apr 2021 19:21:30 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:21:19 -0700
Message-Id: <20210422022128.3464144-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2 0/9] KVM: x86: Fixes for (benign?) truncation bugs
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

v2: Rebase to kvm/queue, commit 89a22e37c8c2 ("KVM: avoid "deadlock"
    between install_new_memslots and MMU notifier")

v1: https://lkml.kernel.org/r/20210213010518.1682691-1-seanjc@google.com

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
 arch/x86/kvm/svm/svm.c        | 12 +++++--
 arch/x86/kvm/vmx/nested.c     | 14 ++++----
 arch/x86/kvm/vmx/vmx.c        |  6 ++--
 arch/x86/kvm/x86.c            | 19 ++++++----
 arch/x86/kvm/x86.h            |  8 ++---
 7 files changed, 48 insertions(+), 98 deletions(-)
```
#### [kvm-unit-tests PATCH 00/14] x86: MSR_GS_BASE and friends
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Apr 22 03:04:50 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217425
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0EC13C433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 03:05:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D98A9613CD
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 03:05:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234007AbhDVDFo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 23:05:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54828 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232618AbhDVDFn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 23:05:43 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 64A56C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 20:05:09 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 o187-20020a2528c40000b02904e567b4bf7eso18377430ybo.10
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 20:05:09 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=GEE7iwBMh55ZA3nDYZ+A1ZRgLSr1EBOEkFXO00qCpVE=;
        b=ToZj3C/GTylu2ZEXzHw6Zet8SEH5L2AZLPoCjdVXz5Um1i5TrWh7J4O4GWeXkwJT1i
         eS3152Sp3bLZQghSNsczy50n53Z6Moq1kSC4V+qHEFR3zqbFL1GNnfFCu/fC7qu7SmiO
         4WbCuT1S40C4imNqj0aPs/3p3TEXxGt+6MUJ8GTRN5OYUO9cxcqrWhXP6v9L3QIpe9hL
         2HthvaYgssL7wc0ZXgKSiFBD6zQe94yZkjq/vObkSjNCPQY9bEnWaOKfBokyGWG4qO+S
         yl1pZe5LMmKwGLoVDRonzKh9la1KeX69F0ZRY79EVqoLickgCrCwtiCKRha/31AaB+R5
         efKQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=GEE7iwBMh55ZA3nDYZ+A1ZRgLSr1EBOEkFXO00qCpVE=;
        b=J/0B3Oy6vonGC1c7n3BwjXjMnSrvIXOMUuojUQnapmhYEZyD7TTc277RMSojbX/3IK
         lf4sbZl5YuTdHuIuaO7JGqfp1OLE6vAlj7wuxNmHnYR+YzJmpwLpnups8h0ungHtRSzT
         XKyUfyoF+c5HIgXWUihXZQ4rEidoopOOWIZ4W/Z9ak0u/85yKNRSrZQwUFvGmIf7r1iv
         87c1wkfuaSwMmuriLYJw4cvzvVvB7nnBL4RtI+uDK9SbitEg5qDwdHGh44gNuxXfo6ug
         9wQaFTGp0kMqKIDYqBhLQqrCkL39B9aZYXoP7M/tdMPsXTJi2lch1cX4R1pMIW0RF/hP
         KFTQ==
X-Gm-Message-State: AOAM533EmRSw8bfjuv/2rEvaax3hxcndl88P5NCkLxD0a1fbfOyNjvL2
        h3Y0HNvghFAYMkQLbE0WzW6Xf1heupA=
X-Google-Smtp-Source: 
 ABdhPJzoQ1UwbCADUhDub0Tt5++DII0c4YunbBfG4xsHkDLpPNn/keOxoxeFmjQuPfqTIWaAsFrCFga9N8o=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:b993:: with SMTP id
 r19mr1663455ybg.445.1619060708693;
 Wed, 21 Apr 2021 20:05:08 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 20:04:50 -0700
Message-Id: <20210422030504.3488253-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [kvm-unit-tests PATCH 00/14] x86: MSR_GS_BASE and friends
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix unit tests on 32-bit SVM, and on VMX if/when 32-bit VMX starts
rejecting MSR_GS_BASE accesses.

Fix a variety of semi-related bugs in the MSR test, rework the test to
make the code maintainable, and expand its test coverage.

Sean Christopherson (14):
  x86/cstart: Don't use MSR_GS_BASE in 32-bit boot code
  x86: msr: Exclude GS/FS_BASE MSRs from 32-bit builds
  x86: msr: Advertise GenuineIntel as vendor to play nice with SYSENTER
  x86: msr: Restore original MSR value after writing arbitrary test
    value
  x86: Force the compiler to retrieve exception info from per-cpu area
  x86: msr: Replace spaces with tabs in all of msr.c
  x86: msr: Use ARRAY_SIZE() instead of open coded equivalent
  x86: msr: Use the #defined MSR indices in favor of open coding the
    values
  x86: msr: Drop the explicit expected value
  x86: msr: Add builder macros to define MSR entries
  x86: msr: Pass msr_info instead of doing a lookup at runtime
  x86: msr: Verify 64-bit only MSRs fault on 32-bit hosts
  x86: msr: Test that always-canonical MSRs #GP on non-canonical value
  x86: msr: Verify that EFER.SCE can be written on 32-bit vCPUs

 lib/x86/desc.c      |   6 +-
 lib/x86/processor.h |  24 +++++++
 x86/cstart.S        |  28 ++++++--
 x86/msr.c           | 163 +++++++++++++++++++++-----------------------
 x86/unittests.cfg   |   5 ++
 x86/vmx_tests.c     |   2 -
 6 files changed, 131 insertions(+), 97 deletions(-)
```
#### [PATCH 0/2] Cleanup the registers read/write access
##### From: Yang Zhong <yang.zhong@intel.com>

```c
From patchwork Thu Apr 22 09:34:34 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 12218147
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12E66C433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 10:05:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C216661360
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 10:05:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235755AbhDVKGH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 06:06:07 -0400
Received: from mga04.intel.com ([192.55.52.120]:61845 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230365AbhDVKGH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 06:06:07 -0400
IronPort-SDR: 
 Ia94LpGtsiDT0kOxB8/UcjG4zHMPsIqwisy7b7lP0ujPVOmoLNZHgs4d61xfE4LCLDDK9bOEwj
 EEr9XbdjaRKA==
X-IronPort-AV: E=McAfee;i="6200,9189,9961"; a="193741589"
X-IronPort-AV: E=Sophos;i="5.82,242,1613462400";
   d="scan'208";a="193741589"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2021 03:05:32 -0700
IronPort-SDR: 
 vU0Siz1iLObUsc/WZqlp80/j2Jo2IwJwF6jN2WgiPdpgjworQrGkWDAWaJws5ZAM9Q9wjUI0Pr
 vPFRONUyKh8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,242,1613462400";
   d="scan'208";a="421317100"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga008.fm.intel.com with ESMTP; 22 Apr 2021 03:05:31 -0700
From: Yang Zhong <yang.zhong@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, yang.zhong@intel.com
Subject: [PATCH 0/2] Cleanup the registers read/write access
Date: Thu, 22 Apr 2021 17:34:34 +0800
Message-Id: <20210422093436.78683-1-yang.zhong@intel.com>
X-Mailer: git-send-email 2.29.2.334.gfaefdd61ec
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM has defined the GP registers and pointer register access
methods in the ./arch/x86/kvm/kvm_cache_regs.h file, but there are
still some GP and pointer registers access using older style. We
should keep those registers access consistent in vmx and svm.

Yang Zhong (2):
  KVM: VMX: Keep registers read/write consistent with definition
  KVM: SVM: Keep registers read/write consistent with definition

 arch/x86/kvm/svm/nested.c |  2 +-
 arch/x86/kvm/svm/sev.c    | 65 ++++++++++++++++++++-------------------
 arch/x86/kvm/svm/svm.c    | 20 ++++++------
 arch/x86/kvm/vmx/vmx.c    | 11 ++++---
 4 files changed, 50 insertions(+), 48 deletions(-)
```
#### [PATCH 0/4] Fix htmldocs warning seen after SEV migration patch merge
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
From patchwork Thu Apr 22 16:38:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12218911
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA676C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 16:39:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA23E6141C
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 16:39:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237929AbhDVQkX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 12:40:23 -0400
Received: from mail-co1nam11on2057.outbound.protection.outlook.com
 ([40.107.220.57]:61792
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236236AbhDVQkV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 12:40:21 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=WjbQrbHM24+FQE2bpTd1GA2bIOxSnsI3YeN0c7zQsNnserBxl1sAyUCV6m5INgzxF4mfeG887WiXEcF6dt0PvrsIcYVnPWJ5nqezDgQ9UZ6q9x85lSRnHV/a7yX8XZkTkuTFNd4KpQ4cgha1PHTiA0nxQWHz5/hZTozP4bKfGS0YNLC0jPl2astlFlAyyre5wqw6eHTQGBjMO0ZSo2P7+O4pN04DMDGBXyY+9sm+mIaiB4DUHDASrXU8v6d1TUi58Dxj7PB95PvARL6QbNTvprSxOo2h7yU+HOgLNUC9nXHM8Q0UAJvls1x1kRgzxUT5sIf5gahe09hYZrr5v4Igwg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=f8wo+Q7FxKV3AavXBxa670YdcVRdUTUmTcDBBHS75Co=;
 b=nbnb+L2dwEEcGTj4CFTzGD9jhPdwv7tdBSkZEOK+npZdMKij4eX+waZ/3c/TyA/iuMIXUUs4u8dNNg32jzex9LsR4szJIaht/baY0711CmE2vWLnR/9TL0uhTqM72ZOjFcFlGjZ5ubF9+fOMPEL18bEZZ9siHlNPOZ5NgJAXg8saIOgVNj88uLRn4TWPruzg/+4U0k2++nZt+9ddVCEYswZJfUMHXI3VWZGrkGi01c4ZB+OCUZ3CbdQbowLtNR7COsqFsSwY/FhecoWHpljYxML2b0nbtwOKM1iCIznR0SAOEvK0LlxsLgfXa56qPq60rrRm+14dL1uodKDPitpyZw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=f8wo+Q7FxKV3AavXBxa670YdcVRdUTUmTcDBBHS75Co=;
 b=XgC97j05+9PNNoN7gOjfAN10OGTCk82sqfYKuk9BRQ7zBvNH4wSKeL3NORJeiUN/+KOnRc+NUiNJ7DnfZg3nACzDD9//OHN5z+b38jGDBUmLPFDxcIKd0EblhDYzSiqEoS3P5KMXThNLKcFF+S4pfrSsO5YP0yMSawMD84gRaBY=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4495.namprd12.prod.outlook.com (2603:10b6:806:70::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.19; Thu, 22 Apr
 2021 16:39:45 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.023; Thu, 22 Apr 2021
 16:39:45 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, sfr@canb.auug.org.au,
        Ashish.Kalra@amd.com, Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH 0/4] Fix htmldocs warning seen after SEV migration patch merge
Date: Thu, 22 Apr 2021 11:38:32 -0500
Message-Id: <20210422163836.27117-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN2PR01CA0059.prod.exchangelabs.com (2603:10b6:800::27) To
 SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN2PR01CA0059.prod.exchangelabs.com (2603:10b6:800::27) with Microsoft SMTP
 Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20 via Frontend
 Transport; Thu, 22 Apr 2021 16:39:45 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: ee7ed65c-1100-41b0-9ed4-08d905ad3c83
X-MS-TrafficTypeDiagnostic: SA0PR12MB4495:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4495DC5A875D7D7AB7023626E5469@SA0PR12MB4495.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:131;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 jikdWISlHb7QLTcUDAqHcOT7x3aGngWE+MYmEHYNi/zhfWoaUgqm329QxcfS7tBeEHOU+/FwH5yY1Iuxenv/5AcoFkkXRSDHkiau6QtUX8zomQo3/woKvExkdbzmTMT2YNqJHgcZVCrymECNgnKkERWpAEIOwvCMELvHWTQol+RcopfuxxRP4bB6lN4eHv3r+QsyrVy6i/S+m6OHG8q4CTChAM3bLbyzy6IiWyKOmCt5I8w6vJvmfoKH5jNDz3SwVGivczQIlbQ3G0KfA542vAQGYLoO9qXMEarkeSrsRkSwP1OGikc/LCVPBU9TRa/niKsg6odQD5ATuAWLlkOe7x6rryVbBsI8thjWj4W/fhNKmhqA8AGriRBJ7U7icl5zcYuWy8C+SkUzx5QnNArfRHr8IjeahkufmQ6X28DhbFGiQSTTPoxZAT2tYjbhf6/NHegs6PMN5I3BznF9paHz2PCJNiBXofuUlLEgUE5lNzNBZmN+gNah9+BUtC3zcdryp2eHktlm/b5svNmXHDZ9gLoSEvhPjZxzPBwUtOTbhyFGgt3eIAcpTpc4Tmq73vS1I2u0BrQhoGZ8qO1HKrK2+3lWwmJ5sbSyzwSR6KbBVKl83XZlTyKp1VZB4Fo+FIeNdAzvUgesiLIog1kgOWfoGA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(136003)(366004)(346002)(396003)(39850400004)(26005)(8676002)(66476007)(6486002)(956004)(1076003)(16526019)(2616005)(36756003)(478600001)(4326008)(5660300002)(186003)(83380400001)(316002)(44832011)(38100700002)(38350700002)(6666004)(7696005)(66556008)(2906002)(86362001)(66946007)(8936002)(52116002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 bVn4rv95Y2fQFmJ1GtnczoACTD0rsggbY/3fY5XdJ1nQ2JbKGnlM646CY+hu3hEPkJ65Y+xdImTtQSlEE4T/gHTaYmGHiwf0lehRI8NoD/Do7g6yls5kJaX8UdubCyPRsH+z1n6mxMxsY3dpJTqyUjtX8jnbATM69I1bwzd3/mMCqzd07a+LMZS1KoRbk7Jq+dgZcSP/T0GtkoZhV6Xy6/XjJ37ZnJB4T3NUDwQOqwUfXBI6hR95eCU+lXEnwl0IGgA1J/8tNQtIDV1sFxdHX3Xt04PhXPccHxMXzEES8UxxkDKZuqJ5hb+eCvYD39Kxplm4aeVC+CIKVRLgyD1gHwx3MmHzCQTuOlTsoZfzxM/2nio5Zt+wDK7ntMp75qofP7+HxfvnAoS5Mdn9TYk7JwjWdStRjrF7q0fhAnDQsy1V8TNw7fIHwmBCysuXs9PTX5l/lyAG0mMfYdSwjrN+TS4ydL5SgjdPewhFMjDlHv1IAJoNe/leScYAjMUKATetJ7IP4RzafIyv+PPop011T7i768P0J6Ts8LRD0eCNQ0WhGJAJbx+n8JzaAXLetbALN2ooeBeSEdczocpKow4VVqon1eIUF0TTI7b2IPSa1GlaGaWDWkyX1vYVF2lLEswPOpsiFBr3XqlQs5iQHtp0TaFXj1j0C+Zyv2QUK/NictWPAZDS4OvL6a1AjbHr2cwK7yIzDCttdEBy7/4o5jrfwKk7tq7bbaLqJ4WPPnqwXTAZ05BNZKiwmS/zhAbYFNbmwgGrhAJwg7vxScgjMdjnDy5AcqTXyrBPTCOPFF5X0gxqSflRquoFTrr+q5DRrzfT/EZna7Hg7cZ2NZTdiQJdWrZkpCaK2gsQAhMRcrfwwxEpsfYFRKk/+eQnGRg3FQh2J0jKCfWO+pn0vvxog/C483eZJ7ZQYUVTKl/DXs7TpLbxKnvLj4eN3p+/XibX4eUQ2peScguQHYnaj/Rrk85XXLfxUdihpGr8pOaGiCYmWRRoff2easAuMxO+A1t+OAwnDHMV/iyHOuGjCc/62S2ufY4WCTt7bE/EU28GoZxvn7LQ+q0joN2Epdy0FOrjYSDGNiIAmWg0ILFx8lYQ16XAvlkjewE+X8Uope1y5i9QN5JLD+PxKn0Ar9vj5v4FOpIfxasBYFs/+mGnpe70hKfG2iSmVrLGuqJABoy9W66wbNkwJ5MikWlmuxs8hnSYd+5NrwKgwUZYYSpSh4a/uuW8crw6j9Kwiq4Zf5oDt4th+HXFMV+ipzph0uy6kt+ctMu+THno4G2pNGi5lAazIrwIa15g7iPmGJgzhNVQBVzB9LyMfC11WkDhSX8Ytu2RyOzR
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ee7ed65c-1100-41b0-9ed4-08d905ad3c83
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2021 16:39:45.3714
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 C8/37xCfNec6AVig44sofAaKOWzIG84pSilRIRK5sY5r4shY7jTMuz6fSMwpoVlMcY7eYdceRGA0S3wrOIu+bA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4495
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The make htmldocs reports the following warnings on kvm/next.

Documentation/virt/kvm/amd-memory-encryption.rst:308: WARNING: Inline emphasis start-string without end-string.
Documentation/virt/kvm/amd-memory-encryption.rst:310: WARNING: Inline emphasis start-string without end-string.
Documentation/virt/kvm/amd-memory-encryption.rst:313: WARNING: Inline emphasis start-string without end-string.
Documentation/virt/kvm/amd-memory-encryption.rst:316: WARNING: Inline emphasis start-string without end-string.
Documentation/virt/kvm/amd-memory-encryption.rst:319: WARNING: Inline emphasis start-string without end-string.
Documentation/virt/kvm/amd-memory-encryption.rst:321: WARNING: Definition list ends without a blank line; unexpected unindent.
Documentation/virt/kvm/amd-memory-encryption.rst:369: WARNING: Title underline too short.

15. KVM_SEV_RECEIVE_START
------------------------
Documentation/virt/kvm/amd-memory-encryption.rst:369: WARNING: Title underline too short.

15. KVM_SEV_RECEIVE_START
------------------------
Documentation/virt/kvm/amd-memory-encryption.rst:398: WARNING: Title underline too short.

16. KVM_SEV_RECEIVE_UPDATE_DATA
----------------------------
Documentation/virt/kvm/amd-memory-encryption.rst:398: WARNING: Title underline too short.

16. KVM_SEV_RECEIVE_UPDATE_DATA
----------------------------
Documentation/virt/kvm/amd-memory-encryption.rst:422: WARNING: Title underline too short.

17. KVM_SEV_RECEIVE_FINISH
------------------------
Documentation/virt/kvm/amd-memory-encryption.rst:422: WARNING: Title underline too short.

17. KVM_SEV_RECEIVE_FINISH
------------------------

Brijesh Singh (4):
  docs: kvm: fix underline too short warning for KVM_SEV_RECEIVE_START
  docs: kvm: fix underline too sort warning for
    KVM_SEV_RECEIVE_UPDATE_DATA
  docs: kvm: fix underline too short warning for KVM_SEV_RECEIVE_FINISH
  docs: kvm: fix inline emphasis string warning for KVM_SEV_SEND_START

 Documentation/virt/kvm/amd-memory-encryption.rst | 7 ++++---
 1 file changed, 4 insertions(+), 3 deletions(-)
```
#### [PATCH 0/4] Add guest support for SEV live migration.
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Thu Apr 22 20:54:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12219183
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8D33CC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 20:54:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50FB9613B0
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 20:54:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237018AbhDVUz2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 16:55:28 -0400
Received: from mail-eopbgr770054.outbound.protection.outlook.com
 ([40.107.77.54]:11278
        "EHLO NAM02-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236851AbhDVUz0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 16:55:26 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jcFECfJX8u29eSIwpyJQCPJY6Zncu2By/HVCqdiorrjBsuAZ/oKf9dYrYmzj4+6decN4VrwiUuWLTBocyN2rLLsyuIkLj9nwLq+wjV5OinQRepkwYVAm+O77CYGsnfM4BfqIiCTgwoKPwASKept9D0Xlxcy48Q/C4xfj6dzBrDHAO0gt4Tbvz51L9ChsRcK6LjLpx4rigSLD5yns5KT1/mAAontgvdNzAn6JdUaKPmP0txB5aonVs8apoOfbxc0QqkBxCmP6Q2huiDliV7E75nXfSd/NQcfEZfEdQDDpqqRsGex7W4wdu4itqjIULofWb8ZHFq6PHhhccMf1jBioXw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=tCeDn5PWshW/vrJfRIg9rDxwpkgYUZwIlTStmHkw8rs=;
 b=Ghv1KtmDhsimy69UQvjiG1FtbnMDYY2ix4MwDxqF6DjNjcVCx2y0nS1o7fVsA7tismnNdGzq5VYcIxRQARu2C+rEG2O3NnZalVl2BcaWQciyBt5ftjU+1fCOzQ/zI0KJVKV3q0QmvH33AW1SBq24Ufd6mJQqdvA4RjeHeVTySNp9nWcRSEc3KjmqCENK8Z7KU+A1ogst++wHj6S4Jjxw4z3Iwt82DYD7/RjfD0buie4DNhmcq4ujKzhQReFHieb/nrgTeNPgzZ9irdNPKF6wZ0CH6UJ8RMevGKHFrSjbu3tEA1GyaP6/7o+rljpD7R9EPiQcpoRqZ5AOsq+xgwX18w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=tCeDn5PWshW/vrJfRIg9rDxwpkgYUZwIlTStmHkw8rs=;
 b=x/OIQ/glhOpMJegdIMtDy93Ew/VYD2u7CuOM7/Vz/7aXBPoXbeNn05lj4+GJgR7YDHsrY0mfRKvXn9WjlJXGEg2CJb3t5rlaVGpEW0TX6Jseq32eNoxJibgyBy58lNiJWi+tpJJFlmzyxX5xArOnw3xDhMja96a8WbokyAyB6/o=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21; Thu, 22 Apr
 2021 20:54:46 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%7]) with mapi id 15.20.4065.021; Thu, 22 Apr 2021
 20:54:46 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH 0/4] Add guest support for SEV live migration.
Date: Thu, 22 Apr 2021 20:54:36 +0000
Message-Id: <cover.1619124613.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN1PR12CA0086.namprd12.prod.outlook.com
 (2603:10b6:802:21::21) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN1PR12CA0086.namprd12.prod.outlook.com (2603:10b6:802:21::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20 via Frontend
 Transport; Thu, 22 Apr 2021 20:54:45 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 526ff01d-e79b-4e6f-393d-08d905d0dc94
X-MS-TrafficTypeDiagnostic: SN6PR12MB2767:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB27679FF3FC4BFC49E4A30BE38E469@SN6PR12MB2767.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 PHZa1gOuz5WzdCXEGLY8GfnxMkyG3qoVDP/5M06DMvc2TIiNdvIpawyEy5nZYD69MLxfb3M4CZ2CYcHd3SGpaUOLQ3Ngb9zZ3qinBMiVPKC5+SbmtNihyCLWnDVLKi0oRmWX5pTlmUC54RHsp1skWBBdiSm9RTloumPOhVy748YIS7VNYpVqrWo8lSYWAQpywOy07gkg2+K09vJfEHBsZ3DOjYYa8HNSjfcwUum2GAQDcYx9L3bZ8+q6jMbaAk9vaqHqG9grb7xXF55kMv+VSRfxHhpBnaRvH/3UyRQBX4RW4ffTTxV9gW2E8PZ/e5Z6gP8aXV0pKRDH0BGcPv2/4lK66+ohmGGCpc+GuTDr2EtRdbpv51Y9WCIY0SR1rORRtI8VsrMwrryk3Kdw0HwolyuyNRKDGS84hAVEP2R1cokAdhOYKd/2InqbyggA49BJMeJVO/qp90m2fHfdCe8y1Oxmru5FPuQtJrtIaNmKY/22UD9SBVzld+7RvHKAoUM0iNn0fsFJL/0CK6E5NqC/v8F81cBiajmCAGPi9JmYLx5IT4AMK4aScljjG6mAkUrp3fhNBOTXk4auC1qO9fQ0UpxQuD2lsW4hP4BziGOwUgBdoyKc38QTjLUz+ViD89yIvcxoufaOdoDmnUItkHgbBQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(136003)(396003)(376002)(39860400002)(6916009)(86362001)(83380400001)(7696005)(6666004)(7416002)(5660300002)(26005)(66476007)(316002)(36756003)(186003)(956004)(8676002)(4326008)(52116002)(66556008)(38350700002)(66946007)(16526019)(6486002)(38100700002)(478600001)(8936002)(2616005)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?Rb/qu/U848ZtuZaaG0GfFpEx+MeI0Y?=
	=?utf-8?q?OBFH6uDI2atdka+FyXdztKk3d0B7PcbHjm9We+kSE4KAz7l/Jm/7KtHmb7AHzaVLB?=
	=?utf-8?q?IDEpp4g8UxQmwbLCRlAep7rPWJIUdXWTqfGgBZn9OSPd4On+6ZWI2NdqDjUhT35B1?=
	=?utf-8?q?JrMVkr1kC6dxXs8kGw84drmuHcs/9fJ0PewYj+ftjahaH8OyhPR0vqFGsevVg106H?=
	=?utf-8?q?huI7M5BdWwCtGZVgms0BR7ndR1Uma5+FHCoX4jvFwma9JwfVOvvwoj/J2zOpGYc/S?=
	=?utf-8?q?ls3qJ9xbRlIZub1dAA65MnXMKDI/OpDpu6qnEKMRoyF2KwFPMRqhLRq+aW0Ty2uuH?=
	=?utf-8?q?PQNC36WR2vtzEJsAeEAsAFMK+TtegB2JjclZS+Il/d2kZcpwoqwRTMlXSW+t8vbfj?=
	=?utf-8?q?jaL9rJl//Eg0USwlAdqPnXTeJ1vUmis7/NBOcigYhzrw2CKNRNSoD+yjnBK5jJ0a4?=
	=?utf-8?q?il/bl9xJsaayEKyH4ugX7bhOD4VIyi0oQ7e2h1FAd/HVGTgFh3d02zdiUH+FEJBHN?=
	=?utf-8?q?PrjwHlvFfSTO0k0y+pdXTsXY/nISP3LSup7eiDiFHMXZiBnaxA9xBAxgrfXz/KVRv?=
	=?utf-8?q?yCeuCfzPu1TyK7KcxoYsEm4KWSmN+hDY5vpemHrJz/yS7E0cFxM03HkbJwRHNO6Kl?=
	=?utf-8?q?sWUapaj2ngyDQCvqOR0QLw9vucYgvy3evllQAPGFDHn0OYkTTVXpwEYO+bnNgLd8j?=
	=?utf-8?q?GmagMtK5f2pum0NPxyDT3DBwMR+/JWwSGueRxSkbNCU07TJwftliteQyQmPneBo5Q?=
	=?utf-8?q?6j+a7AENT9xT2G+/dG9xMFNgxQWWlbtadpAh06dQHn/Go1dbRVgts/3yJuzYqv0/+?=
	=?utf-8?q?zzxwl9SqhxIJiF5QJunowG80SM32vHzGPY891cfHMKepPx2HE+XZ8pkrQUF1wX/c6?=
	=?utf-8?q?lbbON0n9KwAYD+gcp3JMtfrlRmDvRG6aUGCb2GOi1Hn0/e2DBXIu3eY9GgDO69A/P?=
	=?utf-8?q?8stOmf1nPOkzusqwi464MCnO6t+YlmHQhYRcdNP2UWCKNAsseQvfu8hEcDhZj9L/L?=
	=?utf-8?q?VvDWj41ijdue5kXvT9KzJNxSPjrGG5IxHSV0+RKq9jD2tvN6JtSnzJgloonONa0wH?=
	=?utf-8?q?Uuz0xfhB3UKhRLruUEwMJGe2Fu5GQgmba/6gepW0KljqVscqSXbRj8QaB/weOTs4Z?=
	=?utf-8?q?uqbtmFEfb502+1y/5EO81gPLcd/x75VlcaTG22kUwdfy2Hqy9bF+ID7EqDRlbXrCq?=
	=?utf-8?q?9aMRGOhoZXZJPbpZdXt/U4jSj0ar7Xbpzu72WIpTKOBha+HenPbi8wX6EBwhzG3BQ?=
	=?utf-8?q?27EkbPfbOWrzkT?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 526ff01d-e79b-4e6f-393d-08d905d0dc94
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2021 20:54:46.3162
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 vF1UmE7xRL+i82ecQEEpCqppuT7cNeaWJqaYGxBUxjLkfjm5PzOsYvILkyOlN9mqObJP1dCYphdYxS6qqXCNIQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2767
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series adds guest support for SEV live migration.

The patch series introduces a new hypercall. The guest OS can use this
hypercall to notify the page encryption status. If the page is encrypted
with guest specific-key then we use SEV command during the migration.
If page is not encrypted then fallback to default.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR.

Ashish Kalra (2):
  EFI: Introduce the new AMD Memory Encryption GUID.
  x86/kvm: Add guest support for detecting and enabling SEV Live
    Migration feature.

Brijesh Singh (2):
  KVM: x86: Add AMD SEV specific Hypercall3
  mm: x86: Invoke hypercall when page encryption status is changed

 arch/x86/include/asm/kvm_para.h       |  12 +++
 arch/x86/include/asm/mem_encrypt.h    |   4 +
 arch/x86/include/asm/paravirt.h       |   6 ++
 arch/x86/include/asm/paravirt_types.h |   2 +
 arch/x86/include/asm/set_memory.h     |   2 +
 arch/x86/kernel/kvm.c                 | 106 ++++++++++++++++++++++++++
 arch/x86/kernel/paravirt.c            |   1 +
 arch/x86/mm/mem_encrypt.c             |  72 ++++++++++++++---
 arch/x86/mm/pat/set_memory.c          |   7 ++
 include/linux/efi.h                   |   1 +
 10 files changed, 204 insertions(+), 9 deletions(-)
```
