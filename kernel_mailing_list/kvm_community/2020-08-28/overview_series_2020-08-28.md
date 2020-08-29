#### [PATCH 1/5] KVM: nVMX: Fix VMX controls MSRs setup when nested VMX enabled
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11742413
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 75CA1138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:54:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 602602075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:54:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728758AbgH1IyW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 04:54:22 -0400
Received: from mga17.intel.com ([192.55.52.151]:49188 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728357AbgH1IyS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 04:54:18 -0400
IronPort-SDR: 
 6K6yxi1qPBxGHRxORFCfpBBUTIurq/HYENa5bm3Jp/HcQQXshHUxMoJuhLiozGR2QunhVV7viP
 kpFTT+k9uWHQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9726"; a="136697492"
X-IronPort-AV: E=Sophos;i="5.76,363,1592895600";
   d="scan'208";a="136697492"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Aug 2020 01:54:17 -0700
IronPort-SDR: 
 FdBPY3Wb3ZnxKgIX5+W6fCAxdji7IEmbqsARIQhx0v9wPie+7yfoF1Znfgoln/HsRTB+nbC/9d
 PibXQYMbD3+Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,363,1592895600";
   d="scan'208";a="332483490"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga002.fm.intel.com with ESMTP; 28 Aug 2020 01:54:15 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 1/5] KVM: nVMX: Fix VMX controls MSRs setup when nested VMX
 enabled
Date: Fri, 28 Aug 2020 16:56:18 +0800
Message-Id: <20200828085622.8365-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200828085622.8365-1-chenyi.qiang@intel.com>
References: <20200828085622.8365-1-chenyi.qiang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM supports the nested VM_{EXIT, ENTRY}_LOAD_IA32_PERF_GLOBAL_CTRL and
VM_{ENTRY_LOAD, EXIT_CLEAR}_BNDCFGS, but they doesn't expose during
the setup of nested VMX controls MSR.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: LAPIC: Reset timer_advance_ns if timer mode switch
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11742017
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 656A816B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 01:35:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D04A208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 01:35:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fRHT5WZF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728256AbgH1BfU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 21:35:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48778 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726147AbgH1BfU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 21:35:20 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3E648C061264;
        Thu, 27 Aug 2020 18:35:20 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id 2so3561540pjx.5;
        Thu, 27 Aug 2020 18:35:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=rxAwjBtuOkOHsCKI2ATmMoWk7nn27DCJ9baRXRPv7gw=;
        b=fRHT5WZFbeMN+s2XVWB/NxbZCCyRDtI6J+tcc1/dyBOTnfX954wwDt3kriLkxSvyzM
         p5zo85HxXxh3wTjsQ5b57HMd4x6/sq0M8kmBRo24B5PfrwE+6rngKdYU22ZH2PmEsbYN
         tf/d/7IPgibKHH+/DjBwn8hyAZ6ccE2bFNzCoeUIrveT23AB7Dm/oPhej5AyFGNH2n1x
         vjDk6zWGOfx50Np0VhiAGPPImXpKlR48Zwo0HtQStzP7Lqll037XWBGQdX4JFpds/PZJ
         Zumtzf5UzA6ebwN2wGOVmZuYJzf6VXL9tw4eLOFGT8c7Bpo0X/aHtOGcS6ATBjvPFTta
         K5mw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=rxAwjBtuOkOHsCKI2ATmMoWk7nn27DCJ9baRXRPv7gw=;
        b=TnW/k6GBKS+pRvUvKMK9iEc6zal91lglHa9MraFXv6/cu0YJpd2EBZvatIZi2taYVR
         fWYLbjvIhNaXk0AtR+y577OKwdymLwASTDUOaUfkVcXir7RM3dRk1C3AzQqhZmMskPJa
         ACZQSQU9oCJLfpPDISSIKzCscbNA17SuExtnGAdu0yGmQxL3W7f0TN2rY2iw4zfvdq/V
         weY7sNpX6QouuZ0VZLXXaHDsaSJaMkD7MtSJBeiY1ZSt+MkcOcT4GW6DQlQe7SCmYj5k
         YSSyL8mPHgAHeDyTUchvQfeHTIrQWBJuF/f2CemrUIIAyMSQ1MST3Dg6jC9kDf3dWtGD
         Lf6Q==
X-Gm-Message-State: AOAM530nvCC7eAeX+v2189FXXY4zEyp919nQJ9eoob+L50KPcgUNRszA
        IbfHWnx/LL1u4NHOTeG2FnT2vAdOFBQ=
X-Google-Smtp-Source: 
 ABdhPJzariVnAqnB4Hk/D+KzhbrZIV+Xpa5zg7Et27t3/fcuC6vm7zCm93AbP6pLhCsbe69QM36Ehg==
X-Received: by 2002:a17:90a:d597:: with SMTP id
 v23mr352068pju.24.1598578519288;
        Thu, 27 Aug 2020 18:35:19 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 b6sm3309715pjz.33.2020.08.27.18.35.16
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 27 Aug 2020 18:35:18 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Reset timer_advance_ns if timer mode switch
Date: Fri, 28 Aug 2020 09:35:08 +0800
Message-Id: <1598578508-14134-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

per-vCPU timer_advance_ns should be set to 0 if timer mode is not tscdeadline 
otherwise we waste cpu cycles in the function lapic_timer_int_injected(), 
especially on AMD platform which doesn't support tscdeadline mode. We can 
reset timer_advance_ns to the initial value if switch back to tscdealine 
timer mode.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### KVM: x86: emulating RDPID failure shall return #UD rather than #GP
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11742073
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B79C13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 02:23:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5DD2020872
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 02:23:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728406AbgH1CXs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 22:23:48 -0400
Received: from mga14.intel.com ([192.55.52.115]:59192 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727124AbgH1CXr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 22:23:47 -0400
IronPort-SDR: 
 pB787b9SVTfxWrgsbQEwCJ5wjotTKH+lqJ/t4Lt8D+qRCX1jGLv0mOmTx6HBTwUw5fBpo8kcz8
 fnfYGDCm8aUQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9726"; a="155854187"
X-IronPort-AV: E=Sophos;i="5.76,362,1592895600";
   d="scan'208";a="155854187"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Aug 2020 19:23:46 -0700
IronPort-SDR: 
 7sl2RJih5fz+4j3xz5Ii1TF2EZ6NoXPDUZNOQ+4Iin7PK/Zme5IsgDZYw322s8keY5IRaGdvYf
 htjG+3THcSlQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,362,1592895600";
   d="scan'208";a="500863254"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by fmsmga005.fm.intel.com with ESMTP; 27 Aug 2020 19:23:45 -0700
From: Robert Hoo <robert.hu@linux.intel.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, kvm@vger.kernel.org
Cc: robert.hu@intel.com, Robert Hoo <robert.hu@linux.intel.com>
Subject: KVM: x86: emulating RDPID failure shall return #UD rather than #GP
Date: Fri, 28 Aug 2020 10:23:42 +0800
Message-Id: <1598581422-76264-1-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Per Intel's SDM, RDPID takes a #UD if it is unsupported, which is more or
less what KVM is emulating when MSR_TSC_AUX is not available.  In fact,
there are no scenarios in which RDPID is supposed to #GP.

Fixes: fb6d4d340e (KVM: x86: emulate RDPID)
Signed-off-by: Robert Hoo <robert.hu@linux.intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH] KVM: x86: Support write protect huge pages lazily
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11742367
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 258FD138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:12:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0EBC420C56
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 08:12:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728647AbgH1IMW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 04:12:22 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:34970 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728581AbgH1IMQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 04:12:16 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 99B9BB2BF2C7879FE501;
        Fri, 28 Aug 2020 16:12:13 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.487.0; Fri, 28 Aug 2020 16:12:06 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, Paolo Bonzini <pbonzini@redhat.com>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>,
        Keqian Zhu <zhukeqian1@huawei.com>
Subject: [RFC PATCH] KVM: x86: Support write protect huge pages lazily
Date: Fri, 28 Aug 2020 16:11:57 +0800
Message-ID: <20200828081157.15748-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently during enable dirty logging, if we're with init-all-set,
we just write protect huge pages and leave normal pages untouched,
for that we can enable dirty logging for these pages lazily.

It seems that enable dirty logging lazily for huge pages is feasible
too, which not only reduces the time of start dirty logging, also
greatly reduces side-effect on guest when there is high dirty rate.

(These codes are not tested, for RFC purpose :-) ).

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/x86/include/asm/kvm_host.h |  3 +-
 arch/x86/kvm/mmu/mmu.c          | 65 ++++++++++++++++++++++++++-------
 arch/x86/kvm/vmx/vmx.c          |  3 +-
 arch/x86/kvm/x86.c              | 22 +++++------
 4 files changed, 62 insertions(+), 31 deletions(-)

```
#### [PATCH V3] vfio dma_map/unmap: optimized for hugetlbfs pages
##### From: Ming Mao <maoming.maoming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ming Mao <maoming.maoming@huawei.com>
X-Patchwork-Id: 11742465
Return-Path: <SRS0=/qcN=CG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60BA013B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 09:27:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46F50208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Aug 2020 09:27:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728870AbgH1J1H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 05:27:07 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:10728 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728444AbgH1J1G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 05:27:06 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id BCEBCAE7B377A3557E6A;
        Fri, 28 Aug 2020 17:27:03 +0800 (CST)
Received: from localhost (10.174.151.129) by DGGEMS411-HUB.china.huawei.com
 (10.3.19.211) with Microsoft SMTP Server id 14.3.487.0; Fri, 28 Aug 2020
 17:26:57 +0800
From: Ming Mao <maoming.maoming@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        <alex.williamson@redhat.com>
CC: <cohuck@redhat.com>, <jianjay.zhou@huawei.com>,
        <weidong.huang@huawei.com>, <peterx@redhat.com>,
        <aarcange@redhat.com>, <wangyunjian@huawei.com>,
        Ming Mao <maoming.maoming@huawei.com>
Subject: [PATCH V3] vfio dma_map/unmap: optimized for hugetlbfs pages
Date: Fri, 28 Aug 2020 17:26:49 +0800
Message-ID: <20200828092649.853-1-maoming.maoming@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.151.129]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the original process of dma_map/unmap pages for VFIO-devices,
to make sure the pages are contiguous, we have to check them one by one.
As a result, dma_map/unmap could spend a long time.
Using the hugetlb pages, we can avoid this problem.
All pages in hugetlb pages are contiguous.And the hugetlb
page should not be split.So we can delete the for loops.

Signed-off-by: Ming Mao <maoming.maoming@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 393 +++++++++++++++++++++++++++++++-
 1 file changed, 382 insertions(+), 11 deletions(-)

```
