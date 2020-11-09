#### [PATCH v2 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11890313
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4DD85C56202
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BE66206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729153AbgKICQz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 8 Nov 2020 21:16:55 -0500
Received: from mga01.intel.com ([192.55.52.88]:64875 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729125AbgKICQy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Nov 2020 21:16:54 -0500
IronPort-SDR: 
 9asik7ZeqCxYAszx8qL1EeLLOBOVd3Wsw8l5BQfZ539BLHpUcjCoXXB1kyeZciDwAJij09sFmD
 j7h5UFQy7UPw==
X-IronPort-AV: E=McAfee;i="6000,8403,9799"; a="187684547"
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="187684547"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Nov 2020 18:16:53 -0800
IronPort-SDR: 
 RHRTPYuFxvARrvejKIp3C65zMLqxBTSqZVLnnyLn0asaQ3RPDqho9kg8zBt7Um72ZJpZdoalGt
 48N1WQVw1H6w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="540646110"
Received: from e5-2699-v4-likexu.sh.intel.com ([10.239.48.39])
  by orsmga005.jf.intel.com with ESMTP; 08 Nov 2020 18:16:49 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Kan Liang <kan.liang@linux.intel.com>, luwei.kang@intel.com,
        Thomas Gleixner <tglx@linutronix.de>, wei.w.wang@intel.com,
        Tony Luck <tony.luck@intel.com>,
        Stephane Eranian <eranian@google.com>,
        Mark Gross <mgross@linux.intel.com>,
        Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when
 vPMU is enabled
Date: Mon,  9 Nov 2020 10:12:38 +0800
Message-Id: <20201109021254.79755-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20201109021254.79755-1-like.xu@linux.intel.com>
References: <20201109021254.79755-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Intel platforms, software may uses IA32_MISC_ENABLE[7]
bit to detect whether the performance monitoring facility
is supported in the processor.

It's dependent on the PMU being enabled for the guest and
a write to this PMU available bit will be ignored.

Cc: Yao Yuan <yuan.yao@intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 2 ++
 arch/x86/kvm/x86.c           | 1 +
 2 files changed, 3 insertions(+)

```
