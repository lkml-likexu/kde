#### [PATCH 1/2] KVM: LAPIC: Fix updating DFR missing apic map recalculation
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11723295
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA841739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 08:57:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AED59207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 08:57:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="RaUObfPy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727935AbgHSI5J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 04:57:09 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55020 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727114AbgHSIzn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 04:55:43 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0B331C061342;
        Wed, 19 Aug 2020 01:55:41 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id y6so10506842plt.3;
        Wed, 19 Aug 2020 01:55:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=nDuiQiXTW962b08Ia0CPUyPMivpXBTRFVOWfM281t2I=;
        b=RaUObfPy9UGdUIMrmSu4v87RasnxOvjPoiDncMq5aYZjysFwPh6YqhgU4iv93cylyn
         6RiJkNEaH4sDneCCrfnuE/KV0QI0wS8QPKXaTUAfY9th/MDkoj34WxdhG5dYgejmGC2W
         CwzXXVGEDQdC9HFn1Y4hGYfwlwSLfU2IGVgMMobwATo4JiHupC1dav8/ZPt4Bgsc8DeI
         uA4zQXbLq+oBLGrUq/AodY6T7xCEOuF+MuiIXVhs6/9aglNYHhrwUE/Aad5ZOqTcVZ7M
         z8R+lzf+PjZnyuQ19L1PkpAJWvM+Y6K+z7UHtntlkzapeqOXbz+Tl6VjUOgaz5rXFi7k
         c+VA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=nDuiQiXTW962b08Ia0CPUyPMivpXBTRFVOWfM281t2I=;
        b=Ct3JjnRL1m1BBKlsfGq0ICsRSp+yO7HfHSOwRxjyFUu3445nzmnCvzo41T2ydCcIfC
         TVKMYVxe30NT4VpLtQs5tVhf1+4DNJ5gUU9fUnqSjXvS5kG7jdambitPy1qw0giLcM4f
         t7wPk4Qc+xMezMQ8QVbV5cnzTwkXV2ccnu5j3nFAGO7PDqb77o+jLap4e5Or34WQ++en
         PuND8jZeTGURE3S2Rk4naICvyj0qdJJmeXDBxFdoKCsjavsiyOCwvycZRwkuEIqpVCxW
         vd1jweMVh6zKc3Am1HbNM12TGytmYwGKHcHhMJD03yvZxytPMvYs4b3Pza7WOcT/Y4XQ
         Jylw==
X-Gm-Message-State: AOAM5324nQ16BgW/dOtI3C73sqot5y1H8F34ag93R5i8awM+/b7B15MR
        gJLWW+ieBiGHps2ChsCwnuwTeV3oZyc=
X-Google-Smtp-Source: 
 ABdhPJyZ2JC161afsEyKpInkW87mBHllTI27riaA07jogoWCDLFoujX/REj5Fq8SGRgRid1pyYIwRQ==
X-Received: by 2002:a17:90a:9405:: with SMTP id
 r5mr3416942pjo.74.1597827341075;
        Wed, 19 Aug 2020 01:55:41 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 m15sm20209991pgr.2.2020.08.19.01.55.38
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 19 Aug 2020 01:55:40 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH 1/2] KVM: LAPIC: Fix updating DFR missing apic map
 recalculation
Date: Wed, 19 Aug 2020 16:55:26 +0800
Message-Id: <1597827327-25055-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

There is missing apic map recalculation after updating DFR, if it is 
INIT RESET, in x2apic mode, local apic is software enabled before. 
This patch fix it by introducing the function kvm_apic_set_dfr() to 
be called in INIT RESET handling path.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 15 ++++++++++-----
 1 file changed, 10 insertions(+), 5 deletions(-)

```
#### [PATCH v6 5/7] KVM: arm64: pmu: Make overflow handler NMI safe
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11724179
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 17157138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 13:35:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0460620866
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 13:35:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728594AbgHSNd5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 09:33:57 -0400
Received: from foss.arm.com ([217.140.110.172]:36962 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728531AbgHSNdk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 09:33:40 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EF6A71396;
        Wed, 19 Aug 2020 06:33:39 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D647C3F71F;
        Wed, 19 Aug 2020 06:33:37 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org
Cc: mark.rutland@arm.com, maz@kernel.org, will@kernel.org,
        catalin.marinas@arm.com, swboyd@chromium.org,
        sumit.garg@linaro.org, Julien Thierry <julien.thierry@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Marc Zyngier <marc.zyngier@arm.com>,
        Will Deacon <will.deacon@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Pouloze <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [PATCH v6 5/7] KVM: arm64: pmu: Make overflow handler NMI safe
Date: Wed, 19 Aug 2020 14:34:17 +0100
Message-Id: <20200819133419.526889-6-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200819133419.526889-1-alexandru.elisei@arm.com>
References: <20200819133419.526889-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Julien Thierry <julien.thierry@arm.com>

kvm_vcpu_kick() is not NMI safe. When the overflow handler is called from
NMI context, defer waking the vcpu to an irq_work queue.

Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: James Morse <james.morse@arm.com>
Cc: Suzuki K Pouloze <suzuki.poulose@arm.com>
Cc: kvm@vger.kernel.org
Cc: kvmarm@lists.cs.columbia.edu
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arch/arm64/kvm/pmu-emul.c | 25 ++++++++++++++++++++++++-
 include/kvm/arm_pmu.h     |  1 +
 2 files changed, 25 insertions(+), 1 deletion(-)

```
#### [Patch v2 1/4] KVM:MMU: Introduce the pin_page() callback
##### From: eric van tassell <Eric.VanTassell@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: eric van tassell <Eric.VanTassell@amd.com>
X-Patchwork-Id: 11724409
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27FD21575
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 15:17:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F13F220885
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 15:17:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="doyoLTjh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728664AbgHSPRT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 11:17:19 -0400
Received: from mail-bn7nam10on2044.outbound.protection.outlook.com
 ([40.107.92.44]:48186
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726899AbgHSPRH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 11:17:07 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=QWWAcdH4KXUZKQzT6yc7tnQTHG2eps9E/YMxztDc0piKCbjAxxdDRsQc4JvPKHApCVQoOfDAHNALfrsGaZqmR7pQzyCC0W+InMJAXd5U/5R7CeGwUOrxJdBF01d4pgzFRDspLLL4+zmElpB8B5fDD/EzvOIjf334Pox3FBtL0ioAATch+fTU4tMp7u48WWBdb/y+TaGQrjIw045PkY9obALrGE06kpi38Y1y/NGk2OBUlLMaGWsCxegcO9S3Mp1+ly9rUK1DXFKG7yhncikf8to/SZvmaqHuJJCeOb50meETa8SsxxIZxiFa7UHancRxS9G6G0XR+BF+R0VzGLZUQg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VaKGJyweKaytkfpqj2e0PU0xmX+dpQkYsSUqtutHKgM=;
 b=i4rUieP1mMQ1BptpDPHu9684l65XG1HPPfGjlqF6Q0YJenpHQYOxNoA2zgwd7GBV6XDXT73wtvE+J8LnpdYbAs8+wYD6+YbvEnO0j8QHSn5VSokaJDtamedTFtALZgXRU2F19J1Sj7y+QLtAB+lcptJ1hkViKXaR2jY1SLsXmnUxHgm++PPyHIFic2xkCYgPHGKa7EbN450XCRd3FKbfcAgljnkN7Qu+rQ+n09TqzH9JAgj8Lzahk549FweCJ7ODCKBnEYPLtotiKIKUTZV6/NZz973gv4KYso16wgn141IVPi6EWwf1dICXSKgzibsvtDcXgKpKd0Rh6gSE+4AoIQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VaKGJyweKaytkfpqj2e0PU0xmX+dpQkYsSUqtutHKgM=;
 b=doyoLTjhf4f6bkTV8ZxaIIhLjkVF6GLQi32PlnckP/WsbfMo3jNB6rRDubk0zCJBQNq3RzyPz7PSmZ2RdhI+GEPshidxnpvSZHwSs/Gcj72yVyySzA7o5AqTjy00jlHwnoaNF0R/wginSCLmD8AZapudjCzAO8xobPgDKD+4bpM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1307.namprd12.prod.outlook.com (2603:10b6:3:79::21) by
 DM6PR12MB3227.namprd12.prod.outlook.com (2603:10b6:5:18d::14) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3305.24; Wed, 19 Aug 2020 15:16:57 +0000
Received: from DM5PR12MB1307.namprd12.prod.outlook.com
 ([fe80::15d7:c2da:d92a:2162]) by DM5PR12MB1307.namprd12.prod.outlook.com
 ([fe80::15d7:c2da:d92a:2162%11]) with mapi id 15.20.3283.028; Wed, 19 Aug
 2020 15:16:57 +0000
From: eric van tassell <Eric.VanTassell@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, bp@alien8.de, hpa@zytor.com,
        mingo@redhat.com, jmattson@google.com, joro@8bytes.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        tglx@linutronix.de, vkuznets@redhat.com, wanpengli@tencent.com,
        x86@kernel.org, rientjes@google.com, junaids@google.com,
        evantass@amd.com
Subject: [Patch v2 1/4] KVM:MMU: Introduce the pin_page() callback
Date: Wed, 19 Aug 2020 10:17:39 -0500
Message-Id: <20200819151742.7892-2-Eric.VanTassell@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200819151742.7892-1-Eric.VanTassell@amd.com>
References: <20200819151742.7892-1-Eric.VanTassell@amd.com>
X-ClientProxiedBy: DM5PR19CA0045.namprd19.prod.outlook.com
 (2603:10b6:3:9a::31) To DM5PR12MB1307.namprd12.prod.outlook.com
 (2603:10b6:3:79::21)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from evt-speedway-83bc.amd.com (165.204.78.2) by
 DM5PR19CA0045.namprd19.prod.outlook.com (2603:10b6:3:9a::31) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3305.24 via Frontend
 Transport; Wed, 19 Aug 2020 15:16:56 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 9f639cf6-edbf-4ff1-2d0f-08d84452e9dc
X-MS-TrafficTypeDiagnostic: DM6PR12MB3227:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB3227543FC5E01C5F0A77E098E75D0@DM6PR12MB3227.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 GaSvrHAMZGNVvPkRrTSrfj189Dc22maaJdbBVJslHIp61o4JKf+N69Zg5oMrW0q17fieSYNvu0m3SGzsL6hKEqtLFbaLwGWjhm9JaZ+NKYcaob+yI7vednSyj5XA7J4mpd42RKQdVVI/nTMpoT7ys5TD9clg0V5KkIuHYRwJdywtjybg5MaTt1zpyrzGvVHCJPSj5lpO4rdUX90Y16a/bDWzkTmm3UBDxGAn6Spo0197obO4635zdNuzBxZQnXrlOkk8jNJMF8SCElc24OZCMndBf59II8c06Z7W8eQpg3ieTiYQPDPEnX5thdqlEuWZ
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1307.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(136003)(396003)(366004)(39860400002)(66556008)(66476007)(8676002)(66946007)(26005)(86362001)(1076003)(5660300002)(478600001)(6486002)(36756003)(316002)(83380400001)(6666004)(7416002)(2906002)(8936002)(6916009)(4326008)(2616005)(7696005)(16526019)(52116002)(186003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 E357RBRZowO273PDBhEUmo+B2tNkvt26FTm0WMJwPZlPWlTE2Y9/4JZ4x+x1+ZEBkppQ2me1IPwBVSGsWeQaS3jcoGI/k/G/RgB/s/L70Vi02EbtCS6dwuoElSAlWywhgrlt8ab3q+0zN0pbUo5YSiDjrs/wGDqgJkzwoJ7czfoBJBT1f+eV3c1NpuxJpyxppJSJdFdkQ1H6E/0LWD0q1lBGJZg77O3mu4OVWU1ieW93tMUxsx76Ly17Av+K2LrM9nUTMFSNAElkJL7dLu0VocZXtAuXHxjf/QZsjainoyVyodOmV6hkaqPwWm7VIKhXlDOlz9i2Lcu09uD+OQ62TIuvFU+5LzI8jwtxKvYW69p6Oi1QKeMESSWsfAgph/ZdJD9sAS13lYSr1wI7mgogqT4KqO3Ik9qyiXL3TZ2Dpc8PlaAI36daY3Na9MSBNgn1/6fTJyXGJiVDTS0CixS0bgrVFvoQl7anMYh1EZzTa040tp+3osRERmFPb+57Ok2R9gIHNVnWV87PExgnzi1QSWiB2XKU+8XGaAjBc/EVfNdzQ7KzrJxWXJTC8sQ8Uo9L800EHPSLtDnwTt6gTYslX1eeN4P2b8KtX9lBnDi34vw/0Ky9M+DCIeZdvIHo2kesfRa7ZeZBsYooL7e4hcj43g==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9f639cf6-edbf-4ff1-2d0f-08d84452e9dc
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1307.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 19 Aug 2020 15:16:57.6612
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 2mt7HUv/gDMoA1yakRHrbZTxzzn2JjJi+3n6K37wElrhcAfIMSLYdYX4epJrFfioR2INDElMomlDlOFro0DtRg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3227
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This generic callback will be called just before setting the spte.

Check the return code where not previously checked since this operation can
return an error.

Defer pinning of SEV guest pages until they're used in order to reduce SEV
guest startup time by eliminating the compute cycles required to pin all
the pages up front. Additionally, we want to reduce memory pressure due to
guests that reserve but only sparsely access a large amount of memory.

Co-developed-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: eric van tassell <Eric.VanTassell@amd.com>
---
 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/mmu/mmu.c          | 30 ++++++++++++++++++++++++++----
 arch/x86/kvm/mmu/paging_tmpl.h  | 27 ++++++++++++++++-----------
 3 files changed, 45 insertions(+), 15 deletions(-)

```
#### [PATCH] docs: kvm: fix referenced ioctl symbol
##### From: Connor Kuehl <ckuehl@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Connor Kuehl <ckuehl@redhat.com>
X-Patchwork-Id: 11725055
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D6F9E14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 21:20:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCD4B20888
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 21:20:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aAO2YJ89"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727093AbgHSVUA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 17:20:00 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:43638 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726689AbgHSVT6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Aug 2020 17:19:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597871997;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=d8aaFslZMGhZl5AC1zF/8lKFp9QgGd2sl23QtosnVQs=;
        b=aAO2YJ898gJTDzy7m6xXzq7tZhLOi+z4ki8tHhYLkx455sDzGlCXrjIYYv6IFVXv1bMkmN
        OybTV9KA/NNbEe5hqC826IXX0a8Q5KtiWBFpNYPqug14vKTVSRC5lIaBVBWA+DUKSiq2lD
        z6eEkyMeazEZKs7iQzblzy/CUvBjDMw=
Received: from mail-qv1-f71.google.com (mail-qv1-f71.google.com
 [209.85.219.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-36-G6S4uz8KMA6Hy3mRV26AuQ-1; Wed, 19 Aug 2020 17:19:55 -0400
X-MC-Unique: G6S4uz8KMA6Hy3mRV26AuQ-1
Received: by mail-qv1-f71.google.com with SMTP id k17so16500515qvj.12
        for <kvm@vger.kernel.org>; Wed, 19 Aug 2020 14:19:55 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=d8aaFslZMGhZl5AC1zF/8lKFp9QgGd2sl23QtosnVQs=;
        b=D830bdIfrpk/vLGVCPZ3ljBd589rZ1KpKTksKK5TViAFSIAlI9OyEqJp0Tg3kg0dfj
         KvKnv1Ue/OlUGUyqJ0fsnPT2lGHYcdm2MQeV0CTxw+dMlnbVi2QJZJukLXxyq9cLWOvp
         FBaijIbcsLsdiQgX/461A5QQDw6W1CSzUfof73tDipb2Qiwe5BB4ok3ho3UTuKpnfzVK
         2Nr8w/5FcmlGfCYFvfhuUI30qkVNC8zLOA5K9BjpACVhlg5JRiGWEdfe2ZuyAWWFIQxr
         Di3mVqiHVLArKUn8H5wiu9gOLpO0L2Yv2oOVfF/j9hK0chavGnjTGQieeWq4mHIHPA3j
         TRKw==
X-Gm-Message-State: AOAM531FGoYNu0NZtSnvwOvJySZkyT/cMJ7mFE23CSRDkGRtUO+byal2
        +mj+ilpU7iFaHb4wuO2FYk5cSwEvQnfank3n7jGLRftrylOfzHvsTDb5l7JbUMp0oCkLvQZti7r
        HAKMsMMB7815L
X-Received: by 2002:a0c:b52b:: with SMTP id d43mr176167qve.158.1597871995082;
        Wed, 19 Aug 2020 14:19:55 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwZf9ipn4932x+sExi1EY3BDhNG2nHiznmd/NazsmDhrrID6yRlma/qKP18WfWZY0hWvSKjuw==
X-Received: by 2002:a0c:b52b:: with SMTP id d43mr176150qve.158.1597871994866;
        Wed, 19 Aug 2020 14:19:54 -0700 (PDT)
Received: from redhat.redhat.com (ip68-103-222-6.ks.ok.cox.net.
 [68.103.222.6])
        by smtp.gmail.com with ESMTPSA id
 d198sm25876478qke.129.2020.08.19.14.19.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 19 Aug 2020 14:19:54 -0700 (PDT)
From: Connor Kuehl <ckuehl@redhat.com>
To: corbet@lwn.net, pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] docs: kvm: fix referenced ioctl symbol
Date: Wed, 19 Aug 2020 16:19:52 -0500
Message-Id: <20200819211952.251984-1-ckuehl@redhat.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The actual symbol that is exported and usable is
'KVM_MEMORY_ENCRYPT_OP', not 'KVM_MEM_ENCRYPT_OP'

$ git grep -l KVM_MEM_ENCRYPT_OP
Documentation/virt/kvm/amd-memory-encryption.rst

$ git grep -l KVM_MEMORY_ENCRYPT_OP
Documentation/virt/kvm/api.rst
arch/x86/kvm/x86.c
include/uapi/linux/kvm.h
tools/include/uapi/linux/kvm.h

While we're in there, update the KVM API category for
KVM_MEMORY_ENCRYPT_OP. It is called on a VM file descriptor.

Signed-off-by: Connor Kuehl <ckuehl@redhat.com>
---
 Documentation/virt/kvm/amd-memory-encryption.rst | 6 +++---
 Documentation/virt/kvm/api.rst                   | 2 +-
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [GIT PULL] VFIO fix for v5.9-rc2
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11724961
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1821138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 19:04:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 887A82083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 19:04:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="D3GPfmQm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726640AbgHSTE1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 15:04:27 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:39812 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725997AbgHSTE1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 15:04:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597863866;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=sqbCREBbabhpyfGFi+VXhTJ7T5nvH5EOefWiEBNhsWM=;
        b=D3GPfmQmDzVh/R4WmBqZRP4psILc/qbD+rxh0USse29fwllAgoZ9jTu30Vibwy9MLFHOP5
        xF3G+Zct8H+bc73EHtvFbuSZ3lsYAc+7ffMlur60uZbPuL3rF1S1e/Uy84NEjLLbD0Oe4G
        YIqh3tRM8ElUWJQwmfWWstY4kjOyScs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-502-d2fSpksPMeWwlhNrmsvBzA-1; Wed, 19 Aug 2020 15:04:24 -0400
X-MC-Unique: d2fSpksPMeWwlhNrmsvBzA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CDE46801ADD;
        Wed, 19 Aug 2020 19:04:22 +0000 (UTC)
Received: from x1.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 94AA1100AE55;
        Wed, 19 Aug 2020 19:04:22 +0000 (UTC)
Date: Wed, 19 Aug 2020 13:04:22 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [GIT PULL] VFIO fix for v5.9-rc2
Message-ID: <20200819130422.357ea56c@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 9123e3a74ec7b934a4a099e98af6a61c2f80bbf5:

  Linux 5.9-rc1 (2020-08-16 13:04:57 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.9-rc2

for you to fetch changes up to aae7a75a821a793ed6b8ad502a5890fb8e8f172d:

  vfio/type1: Add proper error unwind for vfio_iommu_replay() (2020-08-17 11:09:13 -0600)

----------------------------------------------------------------
VFIO fixes for v5.9-rc2

 - Fix lockdep issue reported for recursive read-lock (Alex Williamson)

 - Fix missing unwind in type1 replay function (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (2):
      vfio-pci: Avoid recursive read-lock usage
      vfio/type1: Add proper error unwind for vfio_iommu_replay()

 drivers/vfio/pci/vfio_pci_private.h |   2 +
 drivers/vfio/pci/vfio_pci_rdwr.c    | 120 ++++++++++++++++++++++++++++--------
 drivers/vfio/vfio_iommu_type1.c     |  71 +++++++++++++++++++--
 3 files changed, 164 insertions(+), 29 deletions(-)
```
#### [PATCH v10 1/9] x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11722645
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40D0E913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 06:49:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 32B60208C7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 06:49:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726876AbgHSGrW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 02:47:22 -0400
Received: from mga02.intel.com ([134.134.136.20]:36074 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726435AbgHSGrQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 02:47:16 -0400
IronPort-SDR: 
 H+jCP1FCpMPb+FfVOVmMeTEPfggoKVRA/GN/mWOgmmr2qziOBndNDQ92K3XJUeLRQoQ15eLw9i
 MerlpQqYWHfQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9717"; a="142873170"
X-IronPort-AV: E=Sophos;i="5.76,330,1592895600";
   d="scan'208";a="142873170"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 18 Aug 2020 23:47:15 -0700
IronPort-SDR: 
 nDtdpQEtjW6bR6NbnhJShYKoWr8/YTIylohsfGMpZfvj0J7JyKo7zlBcN1Ts3a7hvxtlH1LgZo
 HihV6B2x7OwA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,330,1592895600";
   d="scan'208";a="310679252"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga002.jf.intel.com with ESMTP; 18 Aug 2020 23:47:12 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>, peterz@infradead.org,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Tony Luck <tony.luck@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v10 1/9] x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
Date: Wed, 19 Aug 2020 14:46:59 +0800
Message-Id: <20200819064707.1033569-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200819064707.1033569-1-xiaoyao.li@intel.com>
References: <20200819064707.1033569-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TIF_SLD can only be set if a user space thread hits split lock and
sld_state == sld_warn. This flag is set to indicate SLD (split lock
detection) is turned off for the thread, so rename it to
TIF_SLD_DISABLED, which is pretty self explaining.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/thread_info.h | 6 +++---
 arch/x86/kernel/cpu/intel.c        | 6 +++---
 arch/x86/kernel/process.c          | 2 +-
 3 files changed, 7 insertions(+), 7 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: vmx: Add test for MTF on a guest MOV-to-CR0 that enables PAE
##### From: Peter Shier <pshier@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Shier <pshier@google.com>
X-Patchwork-Id: 11725045
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA127913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 20:56:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9FA772083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 20:56:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=google.com header.i=@google.com header.b="iaKO6wj6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726729AbgHSU4u (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 16:56:50 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53964 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725997AbgHSU4t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 16:56:49 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 859AAC061757
        for <kvm@vger.kernel.org>; Wed, 19 Aug 2020 13:56:48 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id g127so27035662ybf.11
        for <kvm@vger.kernel.org>; Wed, 19 Aug 2020 13:56:48 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=yZP3U83x8vAX3cajGXc7z0/Dm8SIVm4GFRQ0yFeq1A4=;
        b=iaKO6wj6RPrDOY3RYFZJse7CCdC728/2ZJKEGTHh6Ac4aGVqqx+1EuRgdn1YwQWfhh
         jkqp9VferUrXEFELcNsSaRlZnJDHxjE2zNQz3YoItWLUvXJKCxEh4Yiw6TFweSVP/Vl2
         Wr+bRoMA0CcB4/dAcSd++FKUBSLFUkjOQ8+cQqamZZ0rRniap0EwEXVIzNvDj2W3HdY4
         G6hU15Hzeo1xHZfKB86fVt5TLDQ9hTWI9OguoRk8FC2eN9CGJFBKixawP9A/9oCYvjY7
         CPZP9OKoPHFF8sf+tSRegNulo/BhcDErpNIkDD8xO8ICqT/wUBMH0ozPf6PXjVXb5Br6
         NiEQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=yZP3U83x8vAX3cajGXc7z0/Dm8SIVm4GFRQ0yFeq1A4=;
        b=Glb6XZverj9LdAAApxiAofCYB0OrYzRkEpgQjAtHy/+z5E5jzUH6602ywClpaaoFCZ
         dydjxQGShs8j27senX9RsKlieaDon2rWUm6zNTvdqJzpHelYUMmu245HyDEWgYEEu8d6
         0vDBObGyhLS6WLTQU4sfvwT+mBEHcrUETRLzZNPGnhkIFfMsVKEKGgHp557UIq2rVSNQ
         RBEf2kzTJteUZp3xGCVfs+r/qEBcEV3t0ukX3JQDiMGRlOHRbxYRRulJ66c0UjIHXNdM
         g5TQVEz2S4SeA1/3/BiiBHV5ifINiZYbGqeb5vrEFf2TzN+sWu69maI6B3lV8gVIOQ5A
         GeAg==
X-Gm-Message-State: AOAM530yhVmTnGAM2VwKK021SqFOjM6Cw/k/REiVpeBNGWeyAWdwxddC
        GAX+AvqMTqBCkQuWp372go8fI2p4PjEoFCjrQ4/AxZmT01Jx/y9eTZMX9PGLjI5QNvEGihfxQyr
        DeOls/yTRzm2cuKR1rB5q13hqewtnIS62NPNAQOAAOX4PfTMuDKYf/Hh4wg==
X-Google-Smtp-Source: 
 ABdhPJw1smN9VGqmP6TL7p5/87iv2Rw4wgd8RyVx4KPOpCPohh2becu2eYVKVqwaiacI19sawRGBgMo6RvU=
X-Received: from pshier-linuxworkstation.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fee1:c360]) (user=pshier job=sendgmr) by
 2002:a25:cbc5:: with SMTP id b188mr398390ybg.268.1597870606758; Wed, 19 Aug
 2020 13:56:46 -0700 (PDT)
Date: Wed, 19 Aug 2020 13:56:33 -0700
Message-Id: <20200819205633.1393378-1-pshier@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [kvm-unit-tests PATCH v2] x86: vmx: Add test for MTF on a guest
 MOV-to-CR0 that enables PAE
From: Peter Shier <pshier@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that when L2 guest enables PAE paging and L0 intercept of L2
MOV to CR0 reflects MTF exit to L1, subsequent resume to L2 correctly
preserves PDPTE array specified by L2 CR3.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by:   Peter Shier <pshier@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
---
 lib/x86/asm/page.h |   8 +++
 x86/vmx_tests.c    | 173 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 181 insertions(+)

```
#### [PATCH v9 1/2] virtio: let arch advertise guest's memory access restrictions
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11724589
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2A1E13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 16:23:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9958020882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 16:23:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="SIhilIqP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726970AbgHSQXl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 12:23:41 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28488 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726578AbgHSQXf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Aug 2020 12:23:35 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07JG6Uh7150306;
        Wed, 19 Aug 2020 12:23:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=6ZXC6je36oLn1mYnJGIyGlD/M949prKxH1odvFRZD8I=;
 b=SIhilIqPcIK/aa38dBwqYbgY4nOTXzoymB1voFpIt8xsh3vY5fX/J1XeV4pH0hU8+tpM
 E2rgqNsNXzTOp8NJ6BnYHOg3ue6eR48aZe309ndWmEzW1L+mz8GUqtCkLYwb+ogYESHI
 HFDFKAFCcEF+D/YubPgrfqr2vtGCC03oU1xwMSY+vmwFNs8v7K6sR3x4B00d6uiKhZ6b
 +bvS2CRCFlWsV0m3LZoAlGvZGiSx0FSS5boZP8XtuS3rYv89py3jGVuMVuTxMWYHSpbf
 xRejIk4ZH7UMzEe4uCUe5b8cmbTdM+LeVy4lxIeqQSYnD+L/CwtNZvZJ8MNnQjxET3t2 1g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304sxje3s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 12:23:26 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07JG7nkV151688;
        Wed, 19 Aug 2020 12:23:26 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3304sxje34-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 12:23:25 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07JGEmgA014897;
        Wed, 19 Aug 2020 16:23:24 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 3304cc23p5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 19 Aug 2020 16:23:23 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07JGNLGY23790036
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 19 Aug 2020 16:23:21 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 21C4B5204E;
        Wed, 19 Aug 2020 16:23:21 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.33.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 7A80752050;
        Wed, 19 Aug 2020 16:23:20 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v9 1/2] virtio: let arch advertise guest's memory access
 restrictions
Date: Wed, 19 Aug 2020 18:23:17 +0200
Message-Id: <1597854198-2871-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1597854198-2871-1-git-send-email-pmorel@linux.ibm.com>
References: <1597854198-2871-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-19_09:2020-08-19,2020-08-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 adultscore=0
 mlxscore=0 malwarescore=0 spamscore=0 mlxlogscore=999 lowpriorityscore=0
 bulkscore=0 phishscore=0 impostorscore=0 suspectscore=1 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008190133
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may restrict host access to guest memory.

Provide a new Kconfig entry the architecture can select,
CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS, when it provides
the arch_has_restricted_virtio_memory_access callback to advertise
VIRTIO common code when the architecture restricts memory access
from the host.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h |  9 +++++++++
 3 files changed, 30 insertions(+)

```
#### [PATCH v2 1/7] target: rename all *_do_interupt functions to _do_interrupt_locked
##### From: Robert Foley <robert.foley@linaro.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Foley <robert.foley@linaro.org>
X-Patchwork-Id: 11724847
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6974C618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 18:30:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 37D5420658
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 18:30:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linaro.org header.i=@linaro.org
 header.b="jG083Qm5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726676AbgHSSa1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 14:30:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59440 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726435AbgHSSaT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Aug 2020 14:30:19 -0400
Received: from mail-pj1-x1043.google.com (mail-pj1-x1043.google.com
 [IPv6:2607:f8b0:4864:20::1043])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EF97FC061757
        for <kvm@vger.kernel.org>; Wed, 19 Aug 2020 11:30:18 -0700 (PDT)
Received: by mail-pj1-x1043.google.com with SMTP id c10so1486694pjn.1
        for <kvm@vger.kernel.org>; Wed, 19 Aug 2020 11:30:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=cERuJlDV7NTRJGjVkGRVTXHsJwTCTvANBx0F7hdApoA=;
        b=jG083Qm53OvAj42qYBCvVWCmcwHXtDKpasaDzAQmY3lywgaRZRzHb/e29tvVtmkvXy
         FAZwasPgbUHj9xhO1S3eslPmb4RXNK9PdYldzYMPPYZ2xbam9KU1rLkLoaV8oLZWV2cf
         mq0kAiqtR6+CQ0cx4HODpbOmMWIBGtDAcB2GgLDEt5J8zs54bOZuqU7CW1mvcZVNweUX
         sqpojq9JaKZBDUmWxOTKSfHAS2WSnMOQE6rKSNbiFmiU3PITGp0q56HJjyjQsYiFxxUm
         l6ZabPQlojxJxWGehCde6biDlYZxr4tEy8+8/jsOFo8bTPHO/L8fbQDJYzLI5IqeS65Z
         VNLA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=cERuJlDV7NTRJGjVkGRVTXHsJwTCTvANBx0F7hdApoA=;
        b=FS3li36iAu5SiGPKqzhL2c2Q7nUyX82hYdZWt40W1cNUXP1jwcNLElQNgRC6EWpROV
         sqp4CWhXoiXGeZFySig3xVf/FJrX0qzp26TNZF+GyCULCLNFpcR1LSIn6YlNjKZpjE9P
         ssE2wIWSEBLqWtia1cN3viciRhrl4QyUL1nzyXP413PTbY9XW8ekYhwULLsAcjBvVvJi
         RkX5eL5kz5mPplDkaFAfzvs98HxFaw2KbmDUg7IwH2OVulSSYVQlGUaV6ltOvIFCreq6
         adu3btYdr62arupbi4pNi+/t3cBRkjQCxKPX8f4Wo9yiu/VgbXGT12JSNLA0mx8EFTEu
         9OLg==
X-Gm-Message-State: AOAM531fANHeahj4BO8kmHJcH6aOXG4TCpZasN8dD1a9aG1wXBOBmuUZ
        xf1VFmIwNDnRFSNjej+8S3ZuZg==
X-Google-Smtp-Source: 
 ABdhPJz1Yvg8PSds4SVRrKCdwayuTg8Gc6KVcPFext56h6Uj0VZWXBPwzVbvHOl/clSvO15Z7KjYtg==
X-Received: by 2002:a17:902:6bc2:: with SMTP id
 m2mr19368856plt.114.1597861817962;
        Wed, 19 Aug 2020 11:30:17 -0700 (PDT)
Received: from Rfoley-MA01.hsd1.ma.comcast.net
 (c-73-47-162-176.hsd1.ma.comcast.net. [73.47.162.176])
        by smtp.gmail.com with ESMTPSA id
 p20sm220766pjg.44.2020.08.19.11.30.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 19 Aug 2020 11:30:16 -0700 (PDT)
From: Robert Foley <robert.foley@linaro.org>
To: qemu-devel@nongnu.org
Cc: alex.bennee@linaro.org, pbonzini@redhat.com,
        peter.puhov@linaro.org, robert.foley@linaro.org,
        David Gibson <david@gibson.dropbear.id.au>,
        Richard Henderson <rth@twiddle.net>,
        Peter Maydell <peter.maydell@linaro.org>,
        Michael Rolnik <mrolnik@gmail.com>,
        Sarah Harris <S.E.Harris@kent.ac.uk>,
        "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Michael Walle <michael@walle.cc>,
        Laurent Vivier <laurent@vivier.eu>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Aurelien Jarno <aurelien@aurel32.net>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
        Anthony Green <green@moxielogic.com>,
        Chris Wulff <crwulff@gmail.com>, Marek Vasut <marex@denx.de>,
        Stafford Horne <shorne@gmail.com>,
        Palmer Dabbelt <palmer@dabbelt.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Sagar Karandikar <sagark@eecs.berkeley.edu>,
        Bastian Koppelmann <kbastian@mail.uni-paderborn.de>,
        Yoshinori Sato <ysato@users.sourceforge.jp>,
        Cornelia Huck <cohuck@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Mark Cave-Ayland <mark.cave-ayland@ilande.co.uk>,
        Artyom Tarasenko <atar4qemu@gmail.com>,
        Guan Xuetao <gxt@mprc.pku.edu.cn>,
        Max Filippov <jcmvbkbc@gmail.com>,
        qemu-ppc@nongnu.org (open list:sPAPR),
        qemu-arm@nongnu.org (open list:ARM TCG CPUs),
        kvm@vger.kernel.org (open list:Overall KVM CPUs),
        qemu-riscv@nongnu.org (open list:RISC-V TCG CPUs),
        qemu-s390x@nongnu.org (open list:S390 general arch...)
Subject: [PATCH v2 1/7] target: rename all *_do_interupt functions to
 _do_interrupt_locked
Date: Wed, 19 Aug 2020 14:28:50 -0400
Message-Id: <20200819182856.4893-2-robert.foley@linaro.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200819182856.4893-1-robert.foley@linaro.org>
References: <20200819182856.4893-1-robert.foley@linaro.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The rename of all *_do_interrupt functions to *_do_interrupt_locked
is preparation for pushing the BQL lock around these functions
down into the per-arch implementation of *_do_interrupt.
In a later patch which pushes down the lock, we will add
a new *_do_interrupt function which grabs the BQL and calls to
*_do_interrupt_locked.

This is the first patch in a series of transitions to move the
BQL down into the do_interrupt per arch function.  This set of
transitions is needed to maintain bisectability.

The purpose of this set of changes is to set the groundwork
so that an arch could move towards removing
the BQL from the cpu_handle_interrupt/exception paths.

This approach was suggested by Paolo Bonzini.
For reference, here are key posts in the discussion, explaining
the reasoning/benefits of this approach.

https://lists.gnu.org/archive/html/qemu-devel/2020-08/msg00784.html
https://lists.gnu.org/archive/html/qemu-devel/2020-08/msg01517.html
https://lists.gnu.org/archive/html/qemu-devel/2020-07/msg08731.html
https://lists.gnu.org/archive/html/qemu-devel/2020-08/msg00044.html

Signed-off-by: Robert Foley <robert.foley@linaro.org>
---
 hw/ppc/spapr_events.c           |  2 +-
 target/alpha/cpu.c              |  2 +-
 target/alpha/cpu.h              |  2 +-
 target/alpha/helper.c           |  4 ++--
 target/arm/cpu.c                |  2 +-
 target/arm/cpu.h                |  4 ++--
 target/arm/cpu_tcg.c            |  2 +-
 target/arm/helper.c             |  2 +-
 target/arm/m_helper.c           |  2 +-
 target/avr/cpu.c                |  2 +-
 target/avr/cpu.h                |  2 +-
 target/avr/helper.c             |  2 +-
 target/cris/cpu.c               | 12 ++++++------
 target/cris/cpu.h               |  4 ++--
 target/cris/helper.c            | 10 +++++-----
 target/hppa/cpu.c               |  2 +-
 target/hppa/cpu.h               |  2 +-
 target/hppa/int_helper.c        |  4 ++--
 target/i386/cpu.c               |  2 +-
 target/i386/cpu.h               |  2 +-
 target/i386/seg_helper.c        |  2 +-
 target/lm32/cpu.c               |  2 +-
 target/lm32/cpu.h               |  2 +-
 target/lm32/helper.c            |  4 ++--
 target/m68k/cpu.c               |  2 +-
 target/m68k/cpu.h               |  2 +-
 target/m68k/op_helper.c         |  4 ++--
 target/microblaze/cpu.c         |  2 +-
 target/microblaze/cpu.h         |  2 +-
 target/microblaze/helper.c      |  6 +++---
 target/mips/cpu.c               |  2 +-
 target/mips/helper.c            |  4 ++--
 target/mips/internal.h          |  2 +-
 target/moxie/cpu.c              |  2 +-
 target/moxie/cpu.h              |  2 +-
 target/moxie/helper.c           |  2 +-
 target/nios2/cpu.c              |  4 ++--
 target/nios2/cpu.h              |  2 +-
 target/nios2/helper.c           |  4 ++--
 target/openrisc/cpu.c           |  2 +-
 target/openrisc/cpu.h           |  2 +-
 target/openrisc/interrupt.c     |  4 ++--
 target/ppc/cpu.h                |  2 +-
 target/ppc/excp_helper.c        |  4 ++--
 target/ppc/kvm.c                |  2 +-
 target/ppc/translate_init.inc.c |  2 +-
 target/riscv/cpu.c              |  2 +-
 target/riscv/cpu.h              |  2 +-
 target/riscv/cpu_helper.c       |  4 ++--
 target/rx/cpu.c                 |  2 +-
 target/rx/cpu.h                 |  2 +-
 target/rx/helper.c              |  4 ++--
 target/s390x/cpu.c              |  2 +-
 target/s390x/excp_helper.c      |  6 +++---
 target/s390x/internal.h         |  2 +-
 target/sh4/cpu.c                |  2 +-
 target/sh4/cpu.h                |  2 +-
 target/sh4/helper.c             |  6 +++---
 target/sparc/cpu.c              |  4 ++--
 target/sparc/cpu.h              |  2 +-
 target/sparc/int32_helper.c     |  2 +-
 target/sparc/int64_helper.c     |  2 +-
 target/tilegx/cpu.c             |  6 +++---
 target/unicore32/cpu.c          |  2 +-
 target/unicore32/cpu.h          |  2 +-
 target/unicore32/helper.c       |  2 +-
 target/unicore32/softmmu.c      |  2 +-
 target/xtensa/cpu.c             |  2 +-
 target/xtensa/cpu.h             |  2 +-
 target/xtensa/exc_helper.c      |  6 +++---
 70 files changed, 103 insertions(+), 103 deletions(-)

```
#### [PATCH v3 03/18] virtio: Add get_shm_region method
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11725153
Return-Path: <SRS0=Yqqy=B5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6443F1744
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 22:23:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D29F20888
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Aug 2020 22:23:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VpZvoGgb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727902AbgHSWXB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Aug 2020 18:23:01 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:36689 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727879AbgHSWVI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Aug 2020 18:21:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597875667;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zV4eGv1HmKEw4dEdYXRQk1b4dOpAiZN4WqAP4p4F6ZQ=;
        b=VpZvoGgb6vGgOFSoPIGh9slZmVOSWEZgV8PmmmwOsxCARvekSTsLM1xWIxY4x//Pguwdiy
        bpQyMRH9xzvy+4zxhx/lG7Dxd1Xb0a2+0eLwgFy4mg8GGX3zQOOTf8eDwCMKZ29++/57Eh
        1HTyaGm2yBHgjiGfWGs24FriO1groT8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-558-ol9Li3MSNCuugzCmQy-YSw-1; Wed, 19 Aug 2020 18:21:02 -0400
X-MC-Unique: ol9Li3MSNCuugzCmQy-YSw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E74B2425CC;
        Wed, 19 Aug 2020 22:21:00 +0000 (UTC)
Received: from horse.redhat.com (ovpn-115-197.rdu2.redhat.com [10.10.115.197])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5F50C5C896;
        Wed, 19 Aug 2020 22:20:54 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id D2A592255A0; Wed, 19 Aug 2020 18:20:53 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-nvdimm@lists.01.org, virtio-fs@redhat.com
Cc: vgoyal@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, dan.j.williams@intel.com,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v3 03/18] virtio: Add get_shm_region method
Date: Wed, 19 Aug 2020 18:19:41 -0400
Message-Id: <20200819221956.845195-4-vgoyal@redhat.com>
In-Reply-To: <20200819221956.845195-1-vgoyal@redhat.com>
References: <20200819221956.845195-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sebastien Boeuf <sebastien.boeuf@intel.com>

Virtio defines 'shared memory regions' that provide a continuously
shared region between the host and guest.

Provide a method to find a particular region on a device.

Signed-off-by: Sebastien Boeuf <sebastien.boeuf@intel.com>
Signed-off-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Cc: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>
---
 include/linux/virtio_config.h | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
