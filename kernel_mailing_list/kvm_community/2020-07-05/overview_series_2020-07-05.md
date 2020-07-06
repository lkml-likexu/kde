#### [PATCH 1/2] x86: Expose SERIALIZE for supported cpuid
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11644753
Return-Path: <SRS0=HSsq=AQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9819D1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  5 Jul 2020 23:05:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 811EC20672
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  5 Jul 2020 23:05:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728200AbgGEXFP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 5 Jul 2020 19:05:15 -0400
Received: from mga03.intel.com ([134.134.136.65]:22784 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727894AbgGEXFO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 5 Jul 2020 19:05:14 -0400
IronPort-SDR: 
 VOVMWviFO37RDzzpSM0bmV6LXAaK9v2Z81m68Jc3Nx6KeF9KLxvR9cdtLo5DWGVnh41Ajs/TlE
 oLhhhX/IjmLA==
X-IronPort-AV: E=McAfee;i="6000,8403,9673"; a="147344300"
X-IronPort-AV: E=Sophos;i="5.75,317,1589266800";
   d="scan'208";a="147344300"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jul 2020 16:05:14 -0700
IronPort-SDR: 
 9LV4qFlyhOvhAOBOvB5Uq/5HXG6Xbdx9cDw/YOwQc5uGholCwoOrqfv5Uv06ywx+SbcBUciWWM
 8BbybVNyMZIA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,317,1589266800";
   d="scan'208";a="388043373"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by fmsmga001.fm.intel.com with ESMTP; 05 Jul 2020 16:05:10 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, ricardo.neri-calderon@linux.intel.com,
        kyung.min.park@intel.com, Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH 1/2] x86: Expose SERIALIZE for supported cpuid
Date: Mon,  6 Jul 2020 06:59:51 +0800
Message-Id: <1593989992-10019-2-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1593989992-10019-1-git-send-email-cathy.zhang@intel.com>
References: <1593989992-10019-1-git-send-email-cathy.zhang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SERIALIZE instruction is supported by intel processors,
like Sapphire Rapids. Expose it in KVM supported cpuid.

The SERIALIZE enumeration kernel patch link is as follows:
https://lore.kernel.org/patchwork/patch/1254757/

Signed-off-by: Cathy Zhang <cathy.zhang@intel.com>
---
 arch/x86/kvm/cpuid.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
