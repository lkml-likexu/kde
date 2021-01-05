#### [RFC PATCH v2 1/4] KVM: arm64: GICv4.1: Add function to get VLPI state
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 11996307
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3F6CBC433E0
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 08:17:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E994C20784
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 08:17:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726562AbhADIRl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 03:17:41 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:9952 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726163AbhADIRk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 03:17:40 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4D8T3f5CKTzj2BH;
        Mon,  4 Jan 2021 16:16:14 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.196) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Mon, 4 Jan 2021 16:16:50 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [RFC PATCH v2 1/4] KVM: arm64: GICv4.1: Add function to get VLPI
 state
Date: Mon, 4 Jan 2021 16:16:10 +0800
Message-ID: <20210104081613.100-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210104081613.100-1-lushenming@huawei.com>
References: <20210104081613.100-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.196]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With GICv4.1 and the vPE unmapped, which indicates the invalidation
of any VPT caches associated with the vPE, we can get the VLPI state
by peeking at the VPT. So we add a function for this.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 arch/arm64/kvm/vgic/vgic-v4.c | 24 ++++++++++++++++++++++++
 arch/arm64/kvm/vgic/vgic.h    |  1 +
 2 files changed, 25 insertions(+)

```
#### [PATCH] KVM: Documentation: rectify rst markup in KVM_GET_SUPPORTED_HV_CPUID
##### From: Lukas Bulwahn <lukas.bulwahn@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lukas Bulwahn <lukas.bulwahn@gmail.com>
X-Patchwork-Id: 11996469
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 53BBBC433DB
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 10:00:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 27CDE20780
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 10:00:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726178AbhADKAa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 05:00:30 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45956 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725830AbhADKAa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 05:00:30 -0500
Received: from mail-wm1-x32f.google.com (mail-wm1-x32f.google.com
 [IPv6:2a00:1450:4864:20::32f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B068EC061574;
        Mon,  4 Jan 2021 01:59:49 -0800 (PST)
Received: by mail-wm1-x32f.google.com with SMTP id y23so18728792wmi.1;
        Mon, 04 Jan 2021 01:59:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=K5SA1Kqz0dt8CUajBPOd9U9d9H1oNPjs6B9I4sOCihg=;
        b=s/ndwmXPjggdbAmH8nqLSw+5NLZoYG0yiBdSUadb61dYmcBPO1+VTHoKQ7iDsge4PD
         VMkeS4AL6TNM5gNMY50C450CXct9J2X2Iam2lsvGQw4qOgZRFrNFl8mxw97xbENJ7GrK
         BaL0J8Bsb+UE+IwYXu89+2fk3uYTRLfRMZzEgs1h6xpErc9QcxA5eCExmxn+tqTEtOHK
         vZohNzMNBax92I9VU+iJyK4wFYZSgsduWuT9C8QBV4olifjt34uG4QZVVKOcVxY7WLU8
         a3yWLhtFvj7as2tbIgydyhfaDB6st6/k19iV2pebM3SDNiOcEmb8KMCAiB/TZcyopHt1
         moNQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=K5SA1Kqz0dt8CUajBPOd9U9d9H1oNPjs6B9I4sOCihg=;
        b=LffyVqKqM6siqrt4+3FoL2cixXGW3+7cpw/Cr1iuogceSgTbhxCuIo4gnZs7ezYQW8
         WsbjiHrKnc4DqUi5hDtkZDixIJgIcxFBKlNMQbRXQ+H3rH1jHSmtT/ju3Pq/X/c/k8Fx
         0qP/TmrRI41bkNFYS0CvjIw+vRzH35RUH9OyEiQXxrjzRz1Xk2DTK8n8t68uIL/qFWdk
         J7nxzzjHcuI79YHKXfdHrGr9H8yqYp5EF4yC3Ljm0C6VxyHkaVQ5U0a8aKV2iHnEO8rz
         hIW3gXsCMbn8nroiiwxsHIRORrqG6+TzuqXxWB5Dn+phLpJP1v2AlZnexazyv63OY9vM
         Zrfw==
X-Gm-Message-State: AOAM531t44wma4tB7A/LxWD3Wb6lXXMFqquisRrmvz0D6jRk1xMGmxck
        LQeKO6aLRvQ7jIQuEWSQeZk=
X-Google-Smtp-Source: 
 ABdhPJxHcxk8Zms1qD+WtiLwvK1ZD5IQG8mz5G59lWDzup0lUO9dL59+ZWr+7qzzSVZajuoxy8/KZA==
X-Received: by 2002:a05:600c:214a:: with SMTP id
 v10mr25791435wml.138.1609754388432;
        Mon, 04 Jan 2021 01:59:48 -0800 (PST)
Received: from felia.fritz.box ([2001:16b8:2da9:600:3101:95d1:b0b:2d5a])
        by smtp.gmail.com with ESMTPSA id
 b9sm35572840wmd.32.2021.01.04.01.59.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 04 Jan 2021 01:59:47 -0800 (PST)
From: Lukas Bulwahn <lukas.bulwahn@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Randy Dunlap <rdunlap@infradead.org>,
        linux-kernel@vger.kernel.org,
        Lukas Bulwahn <lukas.bulwahn@gmail.com>
Subject: [PATCH] KVM: Documentation: rectify rst markup in
 KVM_GET_SUPPORTED_HV_CPUID
Date: Mon,  4 Jan 2021 10:59:38 +0100
Message-Id: <20210104095938.24838-1-lukas.bulwahn@gmail.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit c21d54f0307f ("KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID
as a system ioctl") added an enumeration in the KVM_GET_SUPPORTED_HV_CPUID
documentation improperly for rst, and caused new warnings in make htmldocs:

  Documentation/virt/kvm/api.rst:4536: WARNING: Unexpected indentation.
  Documentation/virt/kvm/api.rst:4538: WARNING: Block quote ends without a blank line; unexpected unindent.

Fix that issue and another historic rst markup issue from the initial
rst conversion in the KVM_GET_SUPPORTED_HV_CPUID documentation.

Signed-off-by: Lukas Bulwahn <lukas.bulwahn@gmail.com>
---
applies cleanly on v5.11-rc2 and next-20210104

Jonathan, please pick this minor doc warning fixup.

 Documentation/virt/kvm/api.rst | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v3 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11996721
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 99B19C433E6
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 13:24:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 725CF22286
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 13:24:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727104AbhADNXs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 08:23:48 -0500
Received: from mga07.intel.com ([134.134.136.100]:23246 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726670AbhADNXs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 08:23:48 -0500
IronPort-SDR: 
 9p3odE7WzXEoN1Zibw7uN85UZP1GWYftErRYavq70538zRR0H9tXZ29dbpVNRB5MaHEW8+xqjv
 d4VL03y9+A8g==
X-IronPort-AV: E=McAfee;i="6000,8403,9853"; a="241034281"
X-IronPort-AV: E=Sophos;i="5.78,474,1599548400";
   d="scan'208";a="241034281"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jan 2021 05:22:02 -0800
IronPort-SDR: 
 PbsYVrggunTjJG9WroORn0Ml13OzSR3mXiaXkiAvZFtOdX8wJDGHdAqzeGGtir0tpmzqr7PoNM
 F9D+0dJXJcyw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,474,1599548400";
   d="scan'208";a="461944514"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga001.fm.intel.com with ESMTP; 04 Jan 2021 05:21:58 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, eranian@google.com,
        kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Andi Kleen <andi@firstfloor.org>,
        Kan Liang <kan.liang@linux.intel.com>, wei.w.wang@intel.com,
        luwei.kang@intel.com, linux-kernel@vger.kernel.org
Subject: [PATCH v3 01/17] KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when
 vPMU is enabled
Date: Mon,  4 Jan 2021 21:15:26 +0800
Message-Id: <20210104131542.495413-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210104131542.495413-1-like.xu@linux.intel.com>
References: <20210104131542.495413-1-like.xu@linux.intel.com>
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
#### [PATCH v5.1 27/34] KVM: SVM: Add support for booting APs in an SEV-ES guest
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11997543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88E16C433DB
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 20:21:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3261A22273
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 20:21:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727916AbhADUVJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 15:21:09 -0500
Received: from mail-bn8nam12on2081.outbound.protection.outlook.com
 ([40.107.237.81]:39169
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727814AbhADUVI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 15:21:08 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jMIuqcQpFNEHiQie9VkHM3ldtzxuHXQTodsmvCvbfLKgKa0c/nx1CRgOVdmiPeEtSW2TfQzutPI/a27qTu3dE7AwrQtpW4lkLWwhDC1WCZZkwbeOe6ZrlWBgIBZBykIChjQ1rY99a4qAEIzEuZJa/M/8unsNXNrYjpqdzB1XEEaN4sREr4TtQ3GXa9bdrdgfRd8OomJbFIBCIEGnE9IFm0zO1lNqaHY6YfJPxN6gQ5QYyTuimYkOMtx0Lspu5tooW1s5Fgk0+YB1/pD/SH3ejCvV7sATf6HBegtnD3AmLFvthK9PPIk9W/AcjLpRGaXiROoURAQAItc2Ujmz5wslRw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Yn13YlU2z6nyPHkkTK3qxGAAfKBZrfs5leeI/s8x5O8=;
 b=E3DPnmVfndKTu1ImtGyP4uxQQoIfctlGmThizSuH6jIQI2gzJ872MvMkDyruvqCxvWGwxg/opRZvmfRuapf+6L/fuUi4xhNbj9idraeapI1/4D/uGNibcFR/APQy+oKtdEyFci7rZIm77iGmBplE19rwf1P9XFCozIx4kVCIxASePRQ35N2LQyHhvp4I7JBGJ3+Ma+DwNoL2xT/LcV9Zat+BvvlD4GTKGpvx5+LQII0rklRihQOuJOOVkkAMZ21hJPTm6WdosBozuMs+XrKlBgJ9bFj9lJArtoARLhAP9XtIanTW5PXxstHufD8FJXSrCEYpvifU3zIJ4KxB0eykrw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Yn13YlU2z6nyPHkkTK3qxGAAfKBZrfs5leeI/s8x5O8=;
 b=E4o+O1Sf5L0Hu8sfXlN7FI3+KsyI/Ww2RzsRLLxzfRFTRbZpXVejbvpCxJe6Uy8FyS5sC3Q8yWiLR55rAJpzoc7cCYVIbK7SVat0mVLUWJyRKWjWf8jHTpc5jx4NBs50DRPkXYmjkKI7pthiTNrnEC7ho5MFb6FNc4Jm8lBPVCU=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR12MB4679.namprd12.prod.outlook.com (2603:10b6:4:a2::37) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3700.27; Mon, 4 Jan 2021 20:20:13 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::d95e:b9d:1d6a:e845]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::d95e:b9d:1d6a:e845%12]) with mapi id 15.20.3721.024; Mon, 4 Jan 2021
 20:20:13 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v5.1 27/34] KVM: SVM: Add support for booting APs in an SEV-ES
 guest
Date: Mon,  4 Jan 2021 14:20:01 -0600
Message-Id: 
 <e8fbebe8eb161ceaabdad7c01a5859a78b424d5e.1609791600.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: 
 <47d11ed1c1a48ab71858fc3cde766bf67a4612d1.1607620209.git.thomas.lendacky@amd.com>
References: 
 <47d11ed1c1a48ab71858fc3cde766bf67a4612d1.1607620209.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0801CA0007.namprd08.prod.outlook.com
 (2603:10b6:803:29::17) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN4PR0801CA0007.namprd08.prod.outlook.com (2603:10b6:803:29::17) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3721.20 via Frontend
 Transport; Mon, 4 Jan 2021 20:20:12 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 73b582f5-f2e0-4826-f017-08d8b0ee2457
X-MS-TrafficTypeDiagnostic: DM5PR12MB4679:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB4679C55083E912D6BEEF5BBBECD20@DM5PR12MB4679.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6430;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 BMaks64dcmlVFeP/Jl2TNqLMnzu3p9dS+fSRQfIiLiOP4NpXyVmatPFPIaNJ02ITmjaMqp5NWTPCs3L9NB1DHLY7PWFuOIoR4z344g2E8qse+sV7CBk9oKqzJRyB6PTeAV6t3ABNEcGRpuiz+62U240aTmRk2yMQ+kWH59xSwZ8jgBoKAy5mGxoHI8zGLjDlB943uC5ZGGf7OKR7epjGFouoTIW0vcD3jOqEDVl86bZDbGj/cUG8cn5E+Nio49+6+cH5KwLFFwBSePkQlrAzlw8M3PMsS7+3Ak70RLDA9kNpEcaiL5Ea38P9oaLfFpNnUck+h8RnvlXHRl44bgD12A0+YKfKNAMI+HO1tAK70QmKgedq2imkJrrAujG+osSFXTVTrPYrDEIuToGAwx+2wQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(396003)(136003)(366004)(346002)(8676002)(54906003)(36756003)(5660300002)(4326008)(16526019)(8936002)(316002)(956004)(2616005)(2906002)(6486002)(86362001)(26005)(7416002)(83380400001)(186003)(52116002)(6666004)(66476007)(7696005)(66556008)(66946007)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 MuMCxmjxQ4OoJ2aO2Kvb9lt7cJ7bL5DrmsVcSu3Zhnm/LDU8eGVuli3iD6r9yXqg1vd6AQl4Rjpv6f7vP1buN60qI27ER5G3T5GvhldP7hQgetQujEv73qsfb1XmIUWe7zL6wl0vK3SReqwQEm+2sgj3VVEmZ8lF895KtiaXEi6h2xQ1COP1aUcIZb9s4vkUS6QfOehKDYiTx1ICRBk/lJBLHUWz/01qY49PJUTb59z6nD08JakwSPWujp/8YxrVKjekr+iW9xM/24sQMpAF2nPRZFpRjqL6H+/TKUF1oSIpMVNfEevNlV0MokHj/DSYLnmoWaKsEWRyEnemnnz89jP9JTPdz6hkPI15zLVn+HuPvk4xj/ncorB+POX6psDMVboqc1A6TXYM9KUsGUYMxjywBW4/2gZEAo4YK8m1YUE9f72NLybea3MsKUDkXYMigdZXhFrkernLD0wdBzcw3GN11PxPPObQv9r9CW6P7o7DikDE9wKtyTFffZ8REwF6DduRpo6F8P508VHX1UV1U/PaoyQB7SGLiDjSTnlCAKb9WdibJ02DANOnEdvQZ2Z9t7eDPfHb9R8mDcjavj4KOtfPRHTNR4uw3zzQ28pAdhRdM9c/Elazf73gFC7PDLVsj0Ikd48D25SzFuK0rJMQOEz7JuNjRTz19izJKJfm55nsISgoYD+CSLuMZurtvm8HkSbgzb5vIy/mOzHd4vfzs5F5UIN79fqs/F7lPgTk1u3ja22fAboR1oXYaEgqaknL7Xw0qMAzSM0Qwakv2/vsH3cMZVaK5Mdkwin971jqgNTw4QA75M1K8ngbO6Jhb8f9iYy5q8oNSjHDzpjxIFIWR9wrZudrj1mm1kky7cNrC2GdnIMEaIGvIwf3+P5bmAuOTPs4XhZ85r4sALBjffc9t/SKREYQ92KK2IRgUBoO9dNyhsGr55SlLeUFYcopodouQO3iM6RAwtrvU1bpMcSumCnHG8CCr2jLqsCY5LAknAJDs08QW8MIbOjI6s2TOviM
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Jan 2021 20:20:12.9373
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 73b582f5-f2e0-4826-f017-08d8b0ee2457
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 BkKmV+njnjUHvHf2f1AxYoOeR2e+slf7etRUhxq31kAxgd/SAg6BKkN8BCYDG9JG9zL3eZCukC1ISpr7xd1R1Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB4679
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Typically under KVM, an AP is booted using the INIT-SIPI-SIPI sequence,
where the guest vCPU register state is updated and then the vCPU is VMRUN
to begin execution of the AP. For an SEV-ES guest, this won't work because
the guest register state is encrypted.

Following the GHCB specification, the hypervisor must not alter the guest
register state, so KVM must track an AP/vCPU boot. Should the guest want
to park the AP, it must use the AP Reset Hold exit event in place of, for
example, a HLT loop.

First AP boot (first INIT-SIPI-SIPI sequence):
  Execute the AP (vCPU) as it was initialized and measured by the SEV-ES
  support. It is up to the guest to transfer control of the AP to the
  proper location.

Subsequent AP boot:
  KVM will expect to receive an AP Reset Hold exit event indicating that
  the vCPU is being parked and will require an INIT-SIPI-SIPI sequence to
  awaken it. When the AP Reset Hold exit event is received, KVM will place
  the vCPU into a simulated HLT mode. Upon receiving the INIT-SIPI-SIPI
  sequence, KVM will make the vCPU runnable. It is again up to the guest
  to then transfer control of the AP to the proper location.

  To differentiate between an actual HLT and an AP Reset Hold, a new MP
  state is introduced, KVM_MP_STATE_AP_RESET_HOLD, which the vCPU is
  placed in upon receiving the AP Reset Hold exit event. Additionally, to
  communicate the AP Reset Hold exit event up to userspace (if needed), a
  new exit reason is introduced, KVM_EXIT_AP_RESET_HOLD.

A new x86 ops function is introduced, vcpu_deliver_sipi_vector, in order
to accomplish AP booting. For VMX, vcpu_deliver_sipi_vector is set to the
original SIPI delivery function, kvm_vcpu_deliver_sipi_vector(). SVM adds
a new function that, for non SEV-ES guests, invokes the original SIPI
delivery function, kvm_vcpu_deliver_sipi_vector(), but for SEV-ES guests,
implements the logic above.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/lapic.c            |  2 +-
 arch/x86/kvm/svm/sev.c          | 22 ++++++++++++++++++++++
 arch/x86/kvm/svm/svm.c          | 10 ++++++++++
 arch/x86/kvm/svm/svm.h          |  2 ++
 arch/x86/kvm/vmx/vmx.c          |  2 ++
 arch/x86/kvm/x86.c              | 26 +++++++++++++++++++++-----
 include/uapi/linux/kvm.h        |  2 ++
 8 files changed, 63 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM/SVM: add support for SEV attestation command
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 11996937
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DEAD6C433E6
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 15:19:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A99E8221E5
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 15:19:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727550AbhADPTD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 10:19:03 -0500
Received: from mail-mw2nam10on2079.outbound.protection.outlook.com
 ([40.107.94.79]:22784
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727375AbhADPTD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 10:19:03 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RFT1BzH3VIalFOuqOvFz2q7yWmgKDqvb8p8DDOvTK7OjYS2eK2T0tojU1/Px2YH2xs7Ig1tPJnexlrZI6k68v4ZcRXqccDdQlea4esh8+Rvc6JPTmeaz1gd0xonMwFaVi0tvGJvKH7xpxl0zDJAtYEjG65FNwNXJ8FH1nVzepmF66EtxT7RenrlbilRcm7dHq1dN6Ctcmlq9AWQ8YHW/HR6J7ymje9D6zlhqZzJEbfugEQg51IS17JyZmfbDIGDLM5eNWaQi5UmS4nPwnLK6omu6/LripBVZhkVyoXhM5NBMIqSCCHtNY9CETKC/06g1cT/AySIkhhzRPNiKrcIVZA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Q+529ZXrdpzI5ti9EzZmRk7VhLaTGsQTBuDjeGdkRfY=;
 b=B+CoGeDUP88hwdHhx31SchcsYUn+e5uJtbn62RYBvIrWtZLDSJi2mQPBXtN61GHjcqR+2Rv7/JvUoLpFgVcVsQEQiWIMmb2SqZb6PtuJrSvclUhkNqsEiK5Z1yiGceYs/zIOFlaTfs676uO6Dlx1AvID7IWKDkpgp1i0h1h5lZ6BO+3VIXRm1Ti6vEY2Suw2/3V8B/Wr7uA6QRWaYo4abVUOcnW+TCx9OgsJfcrmeRysHYg69TCU49pgEZw934GRFo5E2nq1z52WRTj08YB7v+vCEpwiHz9yWabXCJfN74FraVODg7V5sKJgWkYGUbCtC2Hj+SdZveVbwEsEuf8X+w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Q+529ZXrdpzI5ti9EzZmRk7VhLaTGsQTBuDjeGdkRfY=;
 b=xChUYL8IAEBFeScPDHKPm6yDLsCy0PdzkDHRDISHelr/e2nj8syZM0iqCXxAyg3BQuXrTCEu842wcSg5BGWju0U4AX8ZSw7fw66CPcLr2OhkChI7R1+ZRfrqCORoWzk0jEleeAlhuSZxEroyVT22xJi7ns9+aQmQd9Dd3O1JyG8=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SN6PR12MB2719.namprd12.prod.outlook.com (2603:10b6:805:6c::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3721.21; Mon, 4 Jan
 2021 15:18:05 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::18a2:699:70b3:2b8a%6]) with mapi id 15.20.3721.024; Mon, 4 Jan 2021
 15:18:05 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Brijesh Singh <brijesh.singh@amd.com>,
        James Bottomley <jejb@linux.ibm.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>,
        David Rientjes <rientjes@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Borislav Petkov <bp@alien8.de>,
        John Allen <john.allen@amd.com>,
        Herbert Xu <herbert@gondor.apana.org.au>,
        linux-crypto@vger.kernel.org
Subject: [PATCH v2] KVM/SVM: add support for SEV attestation command
Date: Mon,  4 Jan 2021 09:17:49 -0600
Message-Id: <20210104151749.30248-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA9PR13CA0110.namprd13.prod.outlook.com
 (2603:10b6:806:24::25) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SA9PR13CA0110.namprd13.prod.outlook.com (2603:10b6:806:24::25) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.4 via Frontend
 Transport; Mon, 4 Jan 2021 15:18:05 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 1a9f8aaf-4a8a-4306-fb89-08d8b0c3efa0
X-MS-TrafficTypeDiagnostic: SN6PR12MB2719:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2719C80BF3C4E198705AD14FE5D20@SN6PR12MB2719.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Eqa9uNHVxaNiZ3aGnxMD52HozRzoNKmNqvVo7oY/QPD+tCFvQROVyRUvRdeCduvXZc5jqboCLwwzS3T/QQFI2B4ptiXBLTaAooAbC1vhQaspwHQbFF+wLbVZoP/oioGR0rUk0AKy0hZyGamKCPAPM7PsXDK3q5y+BSHpyqYdXTCv2AzPnb1yAHnxnlxcx40G31ZyFWl/Wr5YilBmyAKA57vtlteDDQVibDHz22OTy8ekcT4I0ZaA4+q9UDKN9h9XBEeparBEzqwYPSE3or958ldwxZ9T3zxKmTkuHn6KnceNdz7vZkmYCNMsJDLfHNu6sM4gEInuoCqHuU3KTGTusWWdA3LB1OiPQDtq2Z9kBHZWgIPy+Xnm550/2XAW6pAx9ZGAjpX1d5AWWeLDNN6XMg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(346002)(366004)(376002)(136003)(7696005)(52116002)(66476007)(66556008)(66946007)(44832011)(6666004)(26005)(8676002)(316002)(186003)(6486002)(54906003)(16526019)(36756003)(8936002)(478600001)(4326008)(956004)(2616005)(2906002)(86362001)(83380400001)(1076003)(5660300002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 oQS6HOsf1pXvAQq1enkbWPr3tuhx0OT0OlwAao0XnU4+MdKmsMu8HTvdJZ3olQXOmiJHoMf3JRUTj/np0GgKrOpCDIbQgiHhXx79nro1izBw/wzy1BFKoWPq0ETjqjIiVtHRmPfAajuJZFzLonCnU2BVtK3W8HsrJugfnHnFWh0u7T3UI33c9sIVhsAQO9C3Hg95JueMOUBA9XUtJE7VL0LqUrD/56wYfo/DrQaUBJzG7CjAxYhNUbcnkEIM/jb8qP7KSfzaZ7edCXkW+5bKLqyloXJ83g1UZ2OzZw0DsPXrK20Esph620cJtdZwulV5RpP1E5N2uF/fwCo6cYQEUjeJHM25U9AWMkZIk56LG6gbJ/tj7itJMRW72IxF/TDaYVV7iJB1VTatYw1cIF7oW/yRDdBYuE6fGyz9ppNIQX6TCfoyuIH4Z0Js8sES3XMwlh4iAb+xx1kXDhE8Cp/0qICIOgoo5t5rcn21YHmLMwAQecZ9tlEXgPDZ4AzL2zop+DyFv4ycuCOMB71FlymkcT4LuUrJnar6l6xst6BvbuWtR8jW6AmMRTlYKlncBMLB8dTt5rkh6p9MKRAulOb4wvgHgTcO22UtFnYBOAbpC87lGllCOSpSZT6gsE3I0NC9eW/p/PdrPt8wFUespmUbYnWJa4KOOAsKJydhQVd9pjHnxL3zQtFF4xSyKJ98A8DGdhWyCH2V8SMxnqUlDa/aD/u4gAhKmKEpk1+IUpXh7Zl4PD2gAt8jPbU6Xlj1eP4qNTPIX58UvL5SHWpHQNYC7Xb2ocFCZVrvpvlai5zQF9hiM84hMUvO0qeORdbyaSzZBJGfXBghSmohWLZkntSQtDH58WlKFix3kgt71al7w18CWVZhFfMsHzp+KDV8TLbnwXlZ5K4oZ5uKSh9JWHGzsTa2D9xHkcEkSaJX3IlYcWhZchWy9mgqPXlQnaMfrgYxvdhuSeEsXf7KZzSAn7WacFwKUcSAwtTdMSeJ3iJLUI8=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Jan 2021 15:18:05.7921
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 1a9f8aaf-4a8a-4306-fb89-08d8b0c3efa0
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6WNVfO5lDpdOXKBMrx+P2yXSyyrHHlgojQVvoKMZUDT+aaVacbizOqKHlkwEHFoPm6kKBwkSvXuns0XjLdUW2Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2719
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV FW version >= 0.23 added a new command that can be used to query
the attestation report containing the SHA-256 digest of the guest memory
encrypted through the KVM_SEV_LAUNCH_UPDATE_{DATA, VMSA} commands and
sign the report with the Platform Endorsement Key (PEK).

See the SEV FW API spec section 6.8 for more details.

Note there already exist a command (KVM_SEV_LAUNCH_MEASURE) that can be
used to get the SHA-256 digest. The main difference between the
KVM_SEV_LAUNCH_MEASURE and KVM_SEV_ATTESTATION_REPORT is that the latter
can be called while the guest is running and the measurement value is
signed with PEK.

Cc: James Bottomley <jejb@linux.ibm.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Cc: David Rientjes <rientjes@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: John Allen <john.allen@amd.com>
Cc: Herbert Xu <herbert@gondor.apana.org.au>
Cc: linux-crypto@vger.kernel.org
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
Acked-by: David Rientjes <rientjes@google.com>
Tested-by: James Bottomley <jejb@linux.ibm.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
v2:
  * Fix documentation typo

 .../virt/kvm/amd-memory-encryption.rst        | 21 ++++++
 arch/x86/kvm/svm/sev.c                        | 71 +++++++++++++++++++
 drivers/crypto/ccp/sev-dev.c                  |  1 +
 include/linux/psp-sev.h                       | 17 +++++
 include/uapi/linux/kvm.h                      |  8 +++
 5 files changed, 118 insertions(+)

```
