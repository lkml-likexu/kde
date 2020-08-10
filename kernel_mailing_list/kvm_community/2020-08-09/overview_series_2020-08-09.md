#### [PATCH v3 1/2] x86/cpufeatures: Enumerate TSX suspend load address tracking instructions
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11706581
Return-Path: <SRS0=HRIp=BT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B8FAA14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  9 Aug 2020 07:53:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2392206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  9 Aug 2020 07:53:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726389AbgHIHxM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 9 Aug 2020 03:53:12 -0400
Received: from mga07.intel.com ([134.134.136.100]:53373 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725710AbgHIHxL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 9 Aug 2020 03:53:11 -0400
IronPort-SDR: 
 mc0sXcztmsG6TbshN+di4GYfWtwb9bVTab+ZUtplOwsCONXt93yDkBJjWaHMuTA5LG10iK7D3B
 gCtD+7ixatNQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9707"; a="217734911"
X-IronPort-AV: E=Sophos;i="5.75,452,1589266800";
   d="scan'208";a="217734911"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Aug 2020 00:53:10 -0700
IronPort-SDR: 
 ROJUI9kAaze0P+6ua+c5uThmM20YGEjU9EAd3D5UJS1OkT8aefhIz0vCPLxgfLQ2d4k3OLGoyC
 yt2lDDBYyoqQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,452,1589266800";
   d="scan'208";a="277033476"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by fmsmga008.fm.intel.com with ESMTP; 09 Aug 2020 00:53:05 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        gregkh@linuxfoundation.org, tglx@linutronix.de,
        tony.luck@intel.com, dave.hansen@intel.com,
        kyung.min.park@intel.com, ricardo.neri-calderon@linux.intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        jpoimboe@redhat.com, ak@linux.intel.com, ravi.v.shankar@intel.com,
        Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH v3 1/2] x86/cpufeatures: Enumerate TSX suspend load address
 tracking instructions
Date: Sun,  9 Aug 2020 15:47:21 +0800
Message-Id: <1596959242-2372-2-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1596959242-2372-1-git-send-email-cathy.zhang@intel.com>
References: <1596959242-2372-1-git-send-email-cathy.zhang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Kyung Min Park <kyung.min.park@intel.com>

Intel TSX suspend load tracking instructions aim to give a way to
choose which memory accesses do not need to be tracked in the TSX
read set. Add TSX suspend load tracking CPUID feature flag TSXLDTRK
for enumeration.

A processor supports Intel TSX suspend load address tracking if
CPUID.0x07.0x0:EDX[16] is present. Two instructions XSUSLDTRK, XRESLDTRK
are available when this feature is present.

The CPU feature flag is shown as "tsxldtrk" in /proc/cpuinfo.

This instruction is currently documented in the the latest "extensions"
manual (ISE). It will appear in the "main" manual (SDM) in the future.

Signed-off-by: Kyung Min Park <kyung.min.park@intel.com>
Signed-off-by: Cathy Zhang <cathy.zhang@intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
---
Changes since v2:
 * Shorten documentation names for readability. Links to documentation
   can be found in the cover letter. (Dave Hansen)
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
