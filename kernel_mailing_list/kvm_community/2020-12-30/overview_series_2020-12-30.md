#### [PATCH] KVM: x86/pmu: Fix HW_REF_CPU_CYCLES event pseudo-encoding in intel_arch_events[]
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11993047
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C229C433E0
	for <kvm@archiver.kernel.org>; Wed, 30 Dec 2020 08:27:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEF94221F8
	for <kvm@archiver.kernel.org>; Wed, 30 Dec 2020 08:27:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726189AbgL3I0n (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 30 Dec 2020 03:26:43 -0500
Received: from mga12.intel.com ([192.55.52.136]:11883 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725814AbgL3I0n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Dec 2020 03:26:43 -0500
IronPort-SDR: 
 oUOqEKSaMeS0M8wIMgSA5J7J0WO3QDXyDxrFsQ6y+AlaMxBQ2JZPDISJyJFSdIhPlOz1zzBMIu
 aLfzl/M1Lbqg==
X-IronPort-AV: E=McAfee;i="6000,8403,9849"; a="155782236"
X-IronPort-AV: E=Sophos;i="5.78,460,1599548400";
   d="scan'208";a="155782236"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Dec 2020 00:24:58 -0800
IronPort-SDR: 
 3cU/plrV2HX4s6TlKqR1Lmqk3u84t/8rXSTA4+icQciHKVp2rYTKyOUMF+ijnjkyY0de0lKngw
 eqMB6hhPAYig==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,460,1599548400";
   d="scan'208";a="347693944"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga008.fm.intel.com with ESMTP; 30 Dec 2020 00:24:56 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Stephane Eranian <eranian@google.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/pmu: Fix HW_REF_CPU_CYCLES event pseudo-encoding in
 intel_arch_events[]
Date: Wed, 30 Dec 2020 16:19:16 +0800
Message-Id: <20201230081916.63417-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The HW_REF_CPU_CYCLES event on the fixed counter 2 is pseudo-encoded as
0x0300 in the intel_perfmon_event_map[]. Correct its usage.

Fixes: 62079d8a4312 ("KVM: PMU: add proper support for fixed counter 2")
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
