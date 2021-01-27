#### [RFC PATCH v1 1/5] arm64: cpufeature: Detect the ARMv8.4 TTRem feature
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12046651
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BDB98C433E0
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:43:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 818B72255F
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:43:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391958AbhAZNnM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:43:12 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:11446 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404851AbhAZNmz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 08:42:55 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DQ7DT5z5yzjCXS;
        Tue, 26 Jan 2021 21:41:13 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 26 Jan 2021 21:42:05 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, Marc Zyngier <maz@kernel.org>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v1 1/5] arm64: cpufeature: Detect the ARMv8.4 TTRem
 feature
Date: Tue, 26 Jan 2021 21:41:58 +0800
Message-ID: <20210126134202.381996-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210126134202.381996-1-wangyanan55@huawei.com>
References: <20210126134202.381996-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ARMv8.4 TTRem feature offers 3 levels of support when changing block
size without changing any other parameters that are listed as requiring
use of break-before-make.

With level 0 supported, software must use break-before-make to avoid the
possible hardware problems. With level 1 supported, besides use of BBM,
software can also make use of the nT block translation entry. With level
2 supported, besides approaches of BBM and nT, software can also directly
change block size, but TLB conflicts possibly occur as a result.

We have found a place where TTRem can be used to improve the performance
in guest stage-2 translation. So detact the TTRem feature here.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/cpucaps.h |  3 ++-
 arch/arm64/kernel/cpufeature.c   | 10 ++++++++++
 2 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH] Fix unsynchronized access to sev members through svm_register_enc_region
##### From: Peter Gonda <pgonda@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Gonda <pgonda@google.com>
X-Patchwork-Id: 12048525
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7A0D3C43332
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:48:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5762E2065D
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:48:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730020AbhAZWqc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 17:46:32 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46520 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2394998AbhAZSzY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 13:55:24 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F0896C061793
        for <kvm@vger.kernel.org>; Tue, 26 Jan 2021 10:54:43 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id s64so13862987yba.20
        for <kvm@vger.kernel.org>; Tue, 26 Jan 2021 10:54:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=9to2H1cFYXc/ftlNkKuCOfsyg9/5wBUz/ls+mCyWEZs=;
        b=prBxemVJehhr0+ZWWH2Ff2UiFP29igURLHodMPi/TM2u4RHYrY9xUrlIet1xwv1ERy
         0yz92AuhxZF1kWnoy1Rm5s1k2zzxBPmbXGFrpj/Iq9TaOTkvbgWZj5SzZr4IbwG8MdDo
         7Y2wBFrQHWU9rrzG6TzOlGp8dGCn9LO/hVTGFEb6AFyC0jwo/V4ErXjPFgN9/zPTGqyr
         +1+k12S61GWluYFqqQjq30p++UegS0gltsnBC6Aj0BQN7D2SCjqoEdXhRlpWojNUXg3W
         Ei5C1V208AABLK0nt+z56pwLNzeeKxvZGyluoh1pUIhE+7opFnXLSlJxJJ+p+wXePRWx
         zcZA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=9to2H1cFYXc/ftlNkKuCOfsyg9/5wBUz/ls+mCyWEZs=;
        b=Eqp06j/2yjCNczI7eVcZ22joXetSHLSyXkvGq3S+5fd4tDDZ/t46l4ZeaoB0PVHKRs
         2r+1Z4JhQHOpJxv9UXkDS+CLKvb16kDytTi0VpTTMcTTrFfJpngFm3AVAnRvKItTwr+v
         G/NpaYROG6SiKJq16XlFU2y+42xW1Eb+YQ4ZtTXsXAvXM2SSBpE0+HR0vBiWZw6jdlkr
         plDWT+lJR4iZrRh97wTHo8fDfsZ0/UNIjp2TlUutSTswubL0gCVFeNj5Bjing8N9s+0q
         f59aK3ODKfg+3ktKlZAdGBufE18sRBIfYDERsmbmS5+OzTgKtSUAmnWI2AsK1vs4bEWe
         Frug==
X-Gm-Message-State: AOAM532l+Flk1xnp3ICX6jWXFG0hm5MSszUUbHXhcFlfRRjRkCk46HTU
        /JX2Xmlu6atWFBKx6/oeTLi6MNrUa7BELQ3cF6N4nlxERYgAcsk0C2qOIqtrsGL8Q5jx7gKxWqM
        8Pm0dx2mCf2q4X+FLmNwt0jiVtsXg/tw1euXcoTdp65Nyr+/AQfnxgoM1cg==
X-Google-Smtp-Source: 
 ABdhPJzDEQyw5qWF7Q4CXz78wHuuKbrWi6ACFbxCOYGxyVmyE0CnwCycuL3z1GtTxNOM8sB4xSdS9OC6s+k=
Sender: "pgonda via sendgmr" <pgonda@pgonda1.kir.corp.google.com>
X-Received: from pgonda1.kir.corp.google.com
 ([2620:0:1008:11:f693:9fff:fef4:e3a2])
 (user=pgonda job=sendgmr) by 2002:a25:2351:: with SMTP id
 j78mr10191650ybj.495.1611687283114;
 Tue, 26 Jan 2021 10:54:43 -0800 (PST)
Date: Tue, 26 Jan 2021 10:54:30 -0800
Message-Id: <20210126185431.1824530-1-pgonda@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
Subject: [PATCH] Fix unsynchronized access to sev members through
 svm_register_enc_region
From: Peter Gonda <pgonda@google.com>
To: kvm@vger.kernel.org
Cc: Peter Gonda <pgonda@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <seanjc@google.com>, x86@kernel.org,
        stable@vger.kernel.org, linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

sev_pin_memory assumes that callers hold the kvm->lock. This was true for
all callers except svm_register_enc_region since it does not originate
from svm_mem_enc_op. Also added lockdep annotation to help prevent
future regressions.

Tested: Booted SEV enabled VM on host.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Sean Christopherson <seanjc@google.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: stable@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 116a2214c5173 (KVM: SVM: Pin guest memory when SEV is active)
Signed-off-by: Peter Gonda <pgonda@google.com>
---
 arch/x86/kvm/svm.c | 16 +++++++++-------
 1 file changed, 9 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/4] KVM: x86: Factor out x86 instruction emulation with decoding
##### From: Wei Huang <wei.huang2@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wei Huang <wei.huang2@amd.com>
X-Patchwork-Id: 12045829
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4E19AC433DB
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 08:21:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF12922B3B
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 08:21:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389814AbhAZIU7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 03:20:59 -0500
Received: from mail-bn8nam08on2064.outbound.protection.outlook.com
 ([40.107.100.64]:61696
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2389802AbhAZIUe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 03:20:34 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=VpSHifjG8KnY5fK3Hkuw3w2y/HqJXqGKMjLaj4n5CeY/Qa0e283prfE5gn+HxDcRMNDoug2a6LPkPl8Jr7iJJjqFJPuiW8AZg8XH0/j1wul9tz2SaUJ58jE24UypTEk/Bklp7yDofrBeNwzYHryVX4YycdLshoJ5Ht1y7Xmc1g4+UUNxD8ANgQVZS/dWG7c65OvBiJTzVXZtInJbR7vTi16TNRNoup8lr5HgrHRVtusSkLikJw+sKYT8N9MF+BH9UA2lqUxbnBmn3jWJMjAP2GgCLUOOm1yl1EWfBAM5YhWLQTbTfJvjKu/UAVtyK8SR5RYOp+qbukgknEQQfcvouA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zrh/yP3QuebLz4N2MRDY6SWrEwvZslYWV2sm2NvlQM4=;
 b=NE6FvyoKHvxlYwwx4Q5Br2uGXUXoIvxZ4S8Fe2rkTAuEDlqpeqqAHIFeDfOF8clEF2lXNo7hzJSIbNbLvTGy+f4PcKv/zj8L8i6Z9WbnJXsViOx/MPKibk7rOcEajAX6Smn+wHhlbqstpvGx/Vh80R+siee/Aol9Pto6SjNDARqr79rZy3VTTVgNTWXbJ5u0Qkm9DHt3zprkqyp04SbPD+JJG8TIEYx2wNiKSq1VQhPfANgH2BEwY7sN6WWhNx510wC0z/w713Z2OiRTS7okVT0eqi30znhHWKzIlAEVcJR6ZEBaLfVbSAY/J2h42hINBgumV0bs2+K3KlQZsmulhA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zrh/yP3QuebLz4N2MRDY6SWrEwvZslYWV2sm2NvlQM4=;
 b=OP+zlrZ+fnHRXNc1Ux4Pi4EozldcImXBy9+Pf1wgLV6d5B9BMsBXrj3CUIZ7/ush5sdhZwb67OCHAK5H/I6js9rFSA71UZHdCx5sR37vjxg9YzwdEJ5lpT9tFASiPFVfFpC4V3MkGYznicfTwcSRaGkmAshIZtmrSoMWNaBMInE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1494.namprd12.prod.outlook.com (2603:10b6:910:f::22)
 by CY4PR1201MB0214.namprd12.prod.outlook.com (2603:10b6:910:25::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10; Tue, 26 Jan
 2021 08:19:05 +0000
Received: from CY4PR12MB1494.namprd12.prod.outlook.com
 ([fe80::25d2:a078:e7b:a819]) by CY4PR12MB1494.namprd12.prod.outlook.com
 ([fe80::25d2:a078:e7b:a819%11]) with mapi id 15.20.3784.017; Tue, 26 Jan 2021
 08:19:05 +0000
From: Wei Huang <wei.huang2@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        vkuznets@redhat.com, mlevitsk@redhat.com, seanjc@google.com,
        joro@8bytes.org, bp@alien8.de, tglx@linutronix.de,
        mingo@redhat.com, x86@kernel.org, jmattson@google.com,
        wanpengli@tencent.com, bsd@redhat.com, dgilbert@redhat.com,
        luto@amacapital.net, wei.huang2@amd.com
Subject: [PATCH v3 1/4] KVM: x86: Factor out x86 instruction emulation with
 decoding
Date: Tue, 26 Jan 2021 03:18:28 -0500
Message-Id: <20210126081831.570253-2-wei.huang2@amd.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210126081831.570253-1-wei.huang2@amd.com>
References: <20210126081831.570253-1-wei.huang2@amd.com>
X-Originating-IP: [66.187.233.206]
X-ClientProxiedBy: AM8P192CA0010.EURP192.PROD.OUTLOOK.COM
 (2603:10a6:20b:21b::15) To CY4PR12MB1494.namprd12.prod.outlook.com
 (2603:10b6:910:f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from amd-daytona-06.khw1.lab.eng.bos.redhat.com (66.187.233.206) by
 AM8P192CA0010.EURP192.PROD.OUTLOOK.COM (2603:10a6:20b:21b::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.12 via Frontend
 Transport; Tue, 26 Jan 2021 08:19:00 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0dbbbf28-39ce-4de4-090c-08d8c1d30b8d
X-MS-TrafficTypeDiagnostic: CY4PR1201MB0214:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR1201MB02141FD4E4ACE00FFF6BAF14CFBC0@CY4PR1201MB0214.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 QQPHmmp2Bq/+9+uPalZ+6VnYFcXSlcbCPUkUR7L7HfNZke0HCDV1irPHD7mDTyjc9ENTiwHrOxjgWlygFPDjyOu/anmjABSk2L6xvOO4Nr0f3JVelCZ3uly2metiwQ8DX349lom12dJXr0TQof3YtHQ/lhpJSaiS5kVXm0Mmolw3RADYEXgyiYtwVUXePvwLAiYVd4KKf3FC30ZBk7Lf8PYEXCeVaGzv4eGyBi1GN8UgsTaw4ROcVpe+awXEIN2IJR96HTDFO3NVJV1acXql2CClcae/IkKYZO+yAiZhGVX5kOVKVmrFEoi9zDOu2pxybisRxc39XXpL1bS/AejoRUt8rwf+Ne+yJ7hZK6kEqpxIV+mELUkJ1sUHCziDdwbgDMMYoYT95McLyX2uOlhYJQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1494.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(346002)(376002)(396003)(136003)(36756003)(66556008)(6486002)(8676002)(66476007)(66946007)(52116002)(86362001)(5660300002)(6512007)(2906002)(956004)(186003)(26005)(16526019)(478600001)(6666004)(83380400001)(8936002)(4326008)(6916009)(316002)(6506007)(7416002)(1076003)(2616005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 mxhWXDMXaMtscx1caINMsTj3kusyIt+FWM1bkm8hqja8MGNXZDa5H/0JUgLfgkRiltrRW5A6UVOoqy9QSf4Nc10h8FPeQoNG2c32zieuU+vn+AgUt/roqXb3t3tULhS/L3gOqEyQJd41t3Aej2pl2k0izE/9AKL644bVcLl8XW4SzFv1Kn0C3p7KQW+3i26HxSgaQmusv4+hKHw1PFQwa1YBOHQNFYCwPd46GCeMcVnlmNkroFw7ADxuwc+MIj+f8rFjGB0PjFVU582zEZ+QD4HjI2sWYdWqIoeFP5yTypyGM7L9IHJ4f92coCHPJaiu2+RGoBv9aAc8x0mjKC9mnBtYWR0oNlI9szkaCaCFQrWGxcLbpMXB7Mw/VXlsC4v1sjlQG/J2OXWwfeU535hskt8W04w07IZ1UltsKrWeEtDm3e7tPXSVnAPrI1qIlGjSOQTgMJGXa1Y2hDXzlOV7MiQ/+TDO/1lOfNKhkkBBbLWnZvFeEferknv2J+UtaSluKLaKtBpRki4aHWSluKg3S1CJkO/AnNZ7mGD/zE+IqzZP8FyK63T1URQk3qWv38boXh3nDtuyMpp71t3vj2v5Amagb9T1yNjFpWvFCAVjpdqZP5AwoyrvXt3mu6+SxmPDq9TL8T7WQOxbOMVOywroxlnLx7W9nE+MWtjovbky63jcG2lmnVkPkvYNKMDSC+n+XowYtqc3r126EmwadPHX+XQHAiispwzWJIkO2Y7T2WnjyjEZAeOKjz7yKmnqh0lEMJAJVhyLbqWDi9cyJStzjU+ulB+ZU/PYvMIz34Hu/NGjDd4RiwruX3rD4F6DqpEl+m94B894U4c1W6HmfcmTfoOhoa+u5kFH7/4I8t9B+Jq8OeIVR2lqt5tTBExSXbYGpXKuOevOq5eCrRwlvXbj/GT85BlVn8+8vlmcHSSw+FTPHOoOqxwZ6zuRmdFI4kG8JMrBh2N6hLFHCNoBOr2As4WEPEnLTfNXb02VdBkRVcPtj65rKYuq7SOYAGIHyjMLzkRNJJKYQRA2iGvfv4PcJA0XrEf7TrkPOocREqJgLfUPRVzC/WuSieOyA1QzZcNO
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0dbbbf28-39ce-4de4-090c-08d8c1d30b8d
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1494.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Jan 2021 08:19:05.1746
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 X/qaKaTcCnzwui7LgSvxhq/jc9hWOMMqZNYrhwKG0aAzdtTx7Zm64evYe4SDnhR1
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR1201MB0214
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the instruction decode part out of x86_emulate_instruction() for it
to be used in other places. Also kvm_clear_exception_queue() is moved
inside the if-statement as it doesn't apply when KVM are coming back from
userspace.

Co-developed-by: Bandan Das <bsd@redhat.com>
Signed-off-by: Bandan Das <bsd@redhat.com>
Signed-off-by: Wei Huang <wei.huang2@amd.com>
---
 arch/x86/kvm/x86.c | 62 +++++++++++++++++++++++++++++-----------------
 arch/x86/kvm/x86.h |  2 ++
 2 files changed, 41 insertions(+), 23 deletions(-)

```
#### [RFC PATCH 1/7] arm64: cpufeature: Add API to report system support of HWDBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12046543
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9961AC433E6
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:16:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B04923109
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:16:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391884AbhAZNQR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:16:17 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:11504 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391781AbhAZMp6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 07:45:58 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DQ5yR0MSnzjDYt;
        Tue, 26 Jan 2021 20:43:59 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 26 Jan 2021 20:45:02 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <xiexiangyou@huawei.com>, <zhengchuan@huawei.com>,
        <yubihong@huawei.com>
Subject: [RFC PATCH 1/7] arm64: cpufeature: Add API to report system support
 of HWDBM
Date: Tue, 26 Jan 2021 20:44:38 +0800
Message-ID: <20210126124444.27136-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210126124444.27136-1-zhukeqian1@huawei.com>
References: <20210126124444.27136-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Though we already has a cpu capability named ARM64_HW_DBM, it's a
LOCAL_CPU cap and conditionally compiled by CONFIG_ARM64_HW_AFDBM.

This reports the system wide support of HW_DBM.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/include/asm/cpufeature.h | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [RFC PATCH v3 01/27] x86/cpufeatures: Add SGX1 and SGX2 sub-features
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12047357
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 21CF2C433E0
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 16:15:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5A9C20756
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 16:15:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404388AbhAZQOv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 11:14:51 -0500
Received: from mga02.intel.com ([134.134.136.20]:57480 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2391156AbhAZJb1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 04:31:27 -0500
IronPort-SDR: 
 raz4TiSzaajOjBbF7OoKMqfg+cMLq0CAp8sk4P1wttQ3JBIpE5xVNCX2U7ABE+NSoghkMULcbI
 fzx90xwRDRxA==
X-IronPort-AV: E=McAfee;i="6000,8403,9875"; a="166973508"
X-IronPort-AV: E=Sophos;i="5.79,375,1602572400";
   d="scan'208";a="166973508"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jan 2021 01:30:36 -0800
IronPort-SDR: 
 fBD8ARPYAO9dksR7VxexITMKAOVAjyD2MkGX0XkNCLLgbtf29vfyM3X8NvL8UPoU1GrUQ/8dAu
 HKMm07lLQCDQ==
X-IronPort-AV: E=Sophos;i="5.79,375,1602572400";
   d="scan'208";a="577747458"
Received: from ravivisw-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.254.124.51])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jan 2021 01:30:32 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [RFC PATCH v3 01/27] x86/cpufeatures: Add SGX1 and SGX2 sub-features
Date: Tue, 26 Jan 2021 22:30:16 +1300
Message-Id: 
 <aefe8025b615f75eae3ff891f08191bf730b3c99.1611634586.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1611634586.git.kai.huang@intel.com>
References: <cover.1611634586.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <seanjc@google.com>

Add SGX1 and SGX2 feature flags, via CPUID.0x12.0x0.EAX, as scattered
features, since adding a new leaf for only two bits would be wasteful.
As part of virtualizing SGX, KVM will expose the SGX CPUID leafs to its
guest, and to do so correctly needs to query hardware and kernel support
for SGX1 and SGX2.

Signed-off-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
v2->v3:

- Split moving SGX_LC to cpuid-deps table logic into separate patch.

---
 arch/x86/include/asm/cpufeatures.h | 2 ++
 arch/x86/kernel/cpu/cpuid-deps.c   | 2 ++
 arch/x86/kernel/cpu/scattered.c    | 2 ++
 3 files changed, 6 insertions(+)

```
#### [PATCH v2 01/15] selftests: kvm: Move kvm_get_supported_hv_cpuid() to common code
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12046707
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CADCC433DB
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:56:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CF3C229C9
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:56:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405501AbhAZN4g (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:56:36 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:35582 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2405093AbhAZNtv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 Jan 2021 08:49:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611668905;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5zMyeAIJV4DWJz8SQHo1S/srnhlPuLS/oU/oJkunMYQ=;
        b=Et865z3pET30s3WqX7syDLRVB+QLML3WYGjx8zN4mOzmQnR9fk1uNy4HPmdwvg4bEIhRNQ
        lIBKJsMBPClVLNf1YIp89N2H5GQnh2qJFreEM5RTxDsJ4M6oT0m9G1rpviXyCsWsv647r1
        +UWcuCruA5gyVeto69j6YnpxtosRtU0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-47-yGlWJgiVNCWnp2l4oSbTJQ-1; Tue, 26 Jan 2021 08:48:23 -0500
X-MC-Unique: yGlWJgiVNCWnp2l4oSbTJQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 27411107ACFA;
        Tue, 26 Jan 2021 13:48:22 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.204])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 78A9E5D9C2;
        Tue, 26 Jan 2021 13:48:20 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2 01/15] selftests: kvm: Move kvm_get_supported_hv_cpuid() to
 common code
Date: Tue, 26 Jan 2021 14:48:02 +0100
Message-Id: <20210126134816.1880136-2-vkuznets@redhat.com>
In-Reply-To: <20210126134816.1880136-1-vkuznets@redhat.com>
References: <20210126134816.1880136-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_get_supported_hv_cpuid() may come handy in all Hyper-V related tests.
Split it off hyperv_cpuid test, create system-wide and vcpu versions.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../selftests/kvm/include/x86_64/processor.h  |  3 ++
 .../selftests/kvm/lib/x86_64/processor.c      | 33 +++++++++++++++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 31 ++---------------
 3 files changed, 39 insertions(+), 28 deletions(-)

```
#### [PATCH v6 2/6] sev/i386: Require in-kernel irqchip support for SEV-ES guests
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12048477
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C97EAC433E6
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:39:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B5FF204EF
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:39:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729329AbhAZWh3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 17:37:29 -0500
Received: from mail-co1nam11on2068.outbound.protection.outlook.com
 ([40.107.220.68]:13408
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392634AbhAZRjJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 12:39:09 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jmJOQlcjcAYJbTkGHvBCeeYD4JUF1uR4JCMsUetjz3r1NqkVgWtmXW9/iFCOsrf2rodIP7D/i8Wb6B3ctawSQSoPGCTe8mlsmDgFZ90MAM7MPCBwxvaWaShdztoNKIVsYWkoEwb5CEkuOGE5SvnUp0ENjIwUKBxgXCa73HCeF9+vDJ0xoAgJb6YlOTCW1EXC6IX+8UrZpjgynRGirnL9SSj27aAzwjsGPaqqCVlki39F3teU9H9lgx9nPUv31BJyymk9xD7rjr4XxthX/rntfhZSykePBbkwW8RJu15Qzta4PcK0Zolj7qpYFuDCwbU4JfmyZWk+cpQjjpJ3DujyCw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8WjCjqNwQxZDZUw3moMX0D0fUfH7UK2ltKPE5+az78M=;
 b=P2iTDyC1hB2DGVhsHArgE/Szr+AT2JHHzvYokqB8tuTaLiYZxhYvsYdmGcoAdJiF3EvcwjwelaZxxwFIpbboE+4e0Qv7HlYFZWloagfkWlno1+BpB070mYq48GWrCPc5SR6KvP7wBfJu0B/zOU7Qb/JPC2hRKQATXEVSEq4hqb2XpDNOu6We3raS9Ew1MoyJz+CfVknMRNHqqv2khiImsTvHiqqtbFwTC/oJBn48HqlUw7kuFnyDB6tkKYhZb4UaW1TEd4cAy2mgtlE60bAjWjdWfv8s8UFVKIhPz39WyhdM425vCK2Ktwrp1VdKFSuwVHfJBDvGjYsgVZqSZ0097Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8WjCjqNwQxZDZUw3moMX0D0fUfH7UK2ltKPE5+az78M=;
 b=rrxLVoOrlJOvHungGonvso6PeUVFEHlWY4TP3OaUPPdY1jdx5ABwZugF3wKhdb8lDOUWJo4fO4Iw5WHO0rItC+X8F1oE6LAGJ8fmt8L4O4hPDclZDDN1097X8dfP7W/4hurF8C34dU5UkrZlYw3y+PcF5GUETm2zoQupvcOvrdM=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4153.namprd12.prod.outlook.com (2603:10b6:5:212::22) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3784.13; Tue, 26 Jan 2021 17:37:21 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::cc15:4b1f:9f84:6914]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::cc15:4b1f:9f84:6914%4]) with mapi id 15.20.3784.019; Tue, 26 Jan 2021
 17:37:21 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Richard Henderson <richard.henderson@linaro.org>
Subject: [PATCH v6 2/6] sev/i386: Require in-kernel irqchip support for SEV-ES
 guests
Date: Tue, 26 Jan 2021 11:36:45 -0600
Message-Id: 
 <e9aec5941e613456f0757f5a73869cdc5deea105.1611682609.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <cover.1611682609.git.thomas.lendacky@amd.com>
References: <cover.1611682609.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0220.namprd04.prod.outlook.com
 (2603:10b6:806:127::15) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN7PR04CA0220.namprd04.prod.outlook.com (2603:10b6:806:127::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.12 via Frontend
 Transport; Tue, 26 Jan 2021 17:37:20 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a1aff093-a15c-4b33-6458-08d8c22108eb
X-MS-TrafficTypeDiagnostic: DM6PR12MB4153:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4153661131D6CA766B71253BECBC9@DM6PR12MB4153.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:989;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Z4vwzT5MnsnRGPnwAlXM32A5MhJ+oQ+tx2huGnt3MhB1jK9B4IoDEQlQBVBbjgLb9PaF73I7OWxGsl48d8jscSveertwa3RuZdi8NSvT3Xp4hBbotg6fHE5koCpcXCwVaT27grva8nnT9WCBiMKSmlKXOzbA20C4u8ggnjXLWg0+MaUsgRttykGb+9wxV04KNQ45wlJXgn7HN7sP8NLTTqolnAoWqQNalJ3sfXEwYFvObXoXs2Gx+ZVlGkoY9sT3LczLmvw2KSpaS29vUXwsrSYpRpf0npJgNgm2dj4/pnPpqajqoUEmTodvbkvMTR1X4Zf+acrqEyPdKy6tPOBl4GOLfU8d2y62/olH0jMirRZNYxBnCAivdT2PhRoqHxhrcXc4ul6d8w7RqFlO/64+Bg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(376002)(396003)(346002)(136003)(8676002)(7696005)(52116002)(478600001)(6666004)(7416002)(4326008)(2906002)(66476007)(316002)(54906003)(5660300002)(26005)(2616005)(956004)(86362001)(36756003)(186003)(16526019)(6486002)(66946007)(8936002)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 rpnfQcbS9IUw046Y/QXgUGeERf5Uf7rOeSX3KZPoWcNj0hLWvM2OpFPBTFpbHIAa1qDdvOqebDaz+GmrOrfs9hUBmQrzENtS7qfXeND6t3I8mTUWdPIe1fqTaCSYQ87OgBhGsuYzRztziwAzGGyQzY6TvfDqE4eXpXz4iKC8yH+/a31jlPneQEmmN7kOcbuUps5A4y2PVMdttAIL/d4TKwCjWNTjWe+L2KrNcJxh5Cs5jcK5tlTS3izJlyMYSVnX7dvNdItqzK8Y/qgnh2yfJZJZ0fFtPQriKcpSbH+Sqgsz5DoONepu3ax1Cix+WLIb+wJ1aIyg4MwGuDt6WIXbd0vX4Jk0003pnLNPpZSwlVy2SgggMWLyeNEvc6J69/wcUvabs/cVh0Fb77TK18m1x3/18wm4gFJOV2FHD2z+3D/7TUHpW+NVINrYli0+8/yVHqqWy+NKrdCtRu4vhfylMx3at2BYNz+nqKzCID2B3bmZDuF1XPuPEYnRD3NV2+CuP/lDDzJzzyTQ/knp00bAV2HAiw+l8HzH/Bgw2Vn0AlwKGKeThxmH9kxY26PvIO8kLuzk0xnkqDEO5FyBx2Chf+1NBPBTPpymp6eP6IsUkjTv3p+PtM8xQkKX95LYILwEnHQla7WGK3kA+Un8ykECpKqFB9uc5NjJFKlrdLo/1JU1y1WNfoP119Mxz0I8CDnlPnlkOkH2+7ubUfiN8X0WCJKt4HwWPeeCZznqaKd2cMFSTcXeFRc4GV0kNpKfngk8xS9AADdC7QCi2QA3Rly9lbFM6QpTSCEzcP8ocYdcbt6D7HYA0GZKFLvJxZVSDbOru9Dav9pOLMP2cholFd6gXquqFpKHbpO/md/rK+Hcg9ouwATqYo4nrooufA/pJdSB/pyxj1XitLKkGvpTbosv5eTj9iC4gX+AImbWBu76n5sAEsSEciTjyE2h4YLR/lBX6lIPp+YaGrfjHc3MNu5M0xlnZpUM2c213NVrk0waLz4MHoqJQo55nnT3duCm5zcd4xwUTb7OQP9dF6/6ENXG3U46ngTAEIl5qaqAO5djmUxFar1fSypBnRKrjdlBdvGs
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a1aff093-a15c-4b33-6458-08d8c22108eb
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Jan 2021 17:37:21.3968
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ChVEYz/Svh/X/msvDkfd92a2AJyma/f7jxB3BGvMau2zFElGKlWTYeDrkjdqIAiLVPM9Curg6F8lpXR3dfDMbg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4153
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

In prep for AP booting, require the use of in-kernel irqchip support. This
lessens the Qemu support burden required to boot APs.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Richard Henderson <richard.henderson@linaro.org>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 target/i386/sev.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v2] KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest mode for VMX
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12045323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4AE6C43219
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 05:21:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F7AD229C4
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 05:21:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732164AbhAZFUf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 00:20:35 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:41282 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732273AbhAZBfb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 25 Jan 2021 20:35:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611624841;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=aoPNVJItjntzvSmEbIkhipMW6l3+xUofRDwTaAUWaf0=;
        b=OOksBQERAjwdUvvS5mzM911L7TrglQOagwJHUMcd/sqKc2I3vQQADWtoLs5wD5YQgAO5yY
        UwaHQRbpN0E/nlC16KxF22Fsnw9vm0dsCsrTY+1Lc0YOHXTj+PTcPHpA4omr0rpa9ObaFc
        V8UAXJ1feNr70dTi7V5hIRf29BCIy8A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-484-2R8Fn7WwMwG4HhUGCCL5yA-1; Mon, 25 Jan 2021 19:43:08 -0500
X-MC-Unique: 2R8Fn7WwMwG4HhUGCCL5yA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9E498C28A;
        Tue, 26 Jan 2021 00:43:07 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 246E35D9DB;
        Tue, 26 Jan 2021 00:43:07 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com, stable@vger.kernel.org
Subject: [PATCH v2] KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside
 guest mode for VMX
Date: Mon, 25 Jan 2021 19:43:06 -0500
Message-Id: <20210126004306.1442975-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX also uses KVM_REQ_GET_NESTED_STATE_PAGES for the Hyper-V eVMCS,
which may need to be loaded outside guest mode.  Therefore we cannot
WARN in that case.

However, that part of nested_get_vmcs12_pages is _not_ needed at
vmentry time.  Split it out of KVM_REQ_GET_NESTED_STATE_PAGES handling,
so that both vmentry and migration (and in the latter case, independent
of is_guest_mode) do the parts that are needed.

Cc: <stable@vger.kernel.org> # 5.10.x: f2c7ef3ba: KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES
Cc: <stable@vger.kernel.org> # 5.10.x
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c |  3 +++
 arch/x86/kvm/vmx/nested.c | 31 +++++++++++++++++++++++++------
 arch/x86/kvm/x86.c        |  4 +---
 3 files changed, 29 insertions(+), 9 deletions(-)

```
#### [PATCH v3] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
##### From: Cindy Lu <lulu@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cindy Lu <lulu@redhat.com>
X-Patchwork-Id: 12047877
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73603C433DB
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 19:02:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BEDA22228
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 19:02:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727839AbhAZRFA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 12:05:00 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:47526 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732781AbhAZHRv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 Jan 2021 02:17:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611645379;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=yIlOP1z9vmdG98LkyGhO2vFGnoyUBAuXU0XkS/MGEis=;
        b=XZRBanOROXjvGT86XL5Tm+8SD+hmsy/M30kFh4XrW6K6K3GuQEDameyOSYI+pdRr/W6m4K
        79aGtkTmGvK1UxqPMt5GFgCn2/pKWaf8gestnENXLmN49PkWBR7mgF8Nnz3MpUNEqVZMAX
        XBIRImtRM0oLa2rR0HJk+hWODnUeKhU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-89-aLjSun_bOb2qfWCJd3owGA-1; Tue, 26 Jan 2021 02:16:17 -0500
X-MC-Unique: aLjSun_bOb2qfWCJd3owGA-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C17F190B2A1;
        Tue, 26 Jan 2021 07:16:16 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-12-115.pek2.redhat.com [10.72.12.115])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B044E5D74E;
        Tue, 26 Jan 2021 07:16:10 +0000 (UTC)
From: Cindy Lu <lulu@redhat.com>
To: lulu@redhat.com, jasowang@redhat.com, mst@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: stable@vger.kernel.org
Subject: [PATCH v3] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
Date: Tue, 26 Jan 2021 15:16:07 +0800
Message-Id: <20210126071607.31487-1-lulu@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In vhost_vdpa_set_config_call, the cb.private should be vhost_vdpa.
this cb.private will finally use in vhost_vdpa_config_cb as
vhost_vdpa. Fix this issue.

Cc: stable@vger.kernel.org
Fixes: 776f395004d82 ("vhost_vdpa: Support config interrupt in vdpa")
Signed-off-by: Cindy Lu <lulu@redhat.com>
---
 drivers/vhost/vdpa.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
