#### [PATCH v2 1/3] KVM: X86: Move handling of INVPCID types to x86From: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11608723
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C23F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:03:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 672BB214F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:03:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="EIaZJQUf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726414AbgFPWDo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 18:03:44 -0400
Received: from mail-dm6nam10on2087.outbound.protection.outlook.com
 ([40.107.93.87]:26966
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726397AbgFPWDo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 18:03:44 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jv+it1B7pbkP4rfp4CYvt+sSlq4v17xZF8PicswCvQDt+G/NuVTh5Y+c6z8BHuk9XGIJhY2T7N5is/FXs48Sg2ldVQQ75E7vGHpeEIrA4/15ENvXMqgpYTvH2BbiE7IQnyU2A13LlDrYRk9yz0FowNwnL+UgYpoehyO3YTV+zLOXtuZFdcSG/ntMIaKWUBbpLxZXkjGrguoYQfNHWOMTRTTm+VYk3SXnimvDKu0qQz1pK0prq1vjFj0Q43qulfJMBomSZbVtyv253UibLn5k0e6IB4/oTbtLlqIP1cj8haS/i2cpnW7MdiXwK6wAuDS1Q2BafCJ0AMqzdg81uFo3gA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YEBUmA5sOctOQ7RAonG8lN4Opt2pnHURJXk/mUicfDA=;
 b=eWN9Vlhju6aRsoTxENKs/0YRawduubL9dap9oBpWB8qi42tGJIobTeM1CdK3YfWPsKtxFp5moLGXyYdb5B2hS46ED5CVpdECSPedJg+cV38jHatnnrya6qY3e63/Cz7JxfTHXOZMcUM/p105+FOVnXUoziZIpua4aKGbcY5pZY4Q4WVcQ/PryqKiDQHM17TCZoiVthLYy0MBc3gHMDWgb7NCVJiLfefEZMIaxqtEkga3mMbZZww2lXqoQLRglA+B77gX1jKzZSwxBBmvKnwLNWPmjCjKewKBHPbMytPCZrGxoWJCqseuq2vxQfGD8NbchnJo3wBqTkhWswAYQd9Vkw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YEBUmA5sOctOQ7RAonG8lN4Opt2pnHURJXk/mUicfDA=;
 b=EIaZJQUfI9OJ6YE3kN9LZZzKSMy3nGPZQoZvHayJJTg8euhOPFpaWQs2KEPcX6ezapLjN6XDOjYwbsnBvR8OpoIT7gDj7IuQv3s0kw9N+XzNFvubJoP/UqdUc8JUG88dJIlW3tPx3T/JO0+sy+DpoB33MY3WxrFEoehX52K57vk=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB2622.namprd12.prod.outlook.com (2603:10b6:805:72::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.18; Tue, 16 Jun
 2020 22:03:38 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2%3]) with mapi id 15.20.3088.029; Tue, 16 Jun 2020
 22:03:38 +0000
Subject: [PATCH v2 1/3] KVM: X86: Move handling of INVPCID types to x86
From: Babu Moger <babu.moger@amd.com>
To: wanpengli@tencent.com, joro@8bytes.org, x86@kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, vkuznets@redhat.com,
        tglx@linutronix.de, jmattson@google.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Tue, 16 Jun 2020 17:03:36 -0500
Message-ID: <159234501692.6230.5105866433978454983.stgit@bmoger-ubuntu>
In-Reply-To: <159234483706.6230.13753828995249423191.stgit@bmoger-ubuntu>
References: <159234483706.6230.13753828995249423191.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: DM5PR16CA0001.namprd16.prod.outlook.com
 (2603:10b6:3:c0::11) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 DM5PR16CA0001.namprd16.prod.outlook.com (2603:10b6:3:c0::11) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.19 via Frontend
 Transport; Tue, 16 Jun 2020 22:03:37 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: d1145439-1343-4908-229c-08d812411faf
X-MS-TrafficTypeDiagnostic: SN6PR12MB2622:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB262222711AE86A26C07C6201959D0@SN6PR12MB2622.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-Forefront-PRVS: 04362AC73B
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 MLnamlxHXmaOFNRX4fuqqSmCg0zo5SeJiF8jYUX/uyw5zdN2OQwRmnn0+ljRmEbjIfVpytc/o7qFNP82S/T2+mMpE4ZEvXH/FNiAygpiO4ohb6Q5KV9fg/2qYTR1Q9BmJGM06q6ezRfkPx4R0FhwKyevLb1p+xrBDLUsXKwKqw/fdF2JZ+rv0MPn9LNpMwQKFOKxfqLZqGyNcLT4cJnz28hl2Ikb0cWdhe6mgpx08vGxZsN2M/AzWkx0H0QzG3HWAHTDWPWk6WpVbWuk22joFx7UL5b9ygh15QxlSqax+s49RRbeUDj1dpJ0bVWH1XDLuE+AZestZSXp9z2zwef85VG9v9d2uEmYErF0Zhx+o1HTOdWXN+JBBEor5RR0/K3i
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(7916004)(366004)(39860400002)(136003)(396003)(376002)(346002)(7416002)(8676002)(83380400001)(478600001)(5660300002)(16576012)(8936002)(186003)(4326008)(103116003)(16526019)(2906002)(316002)(26005)(66476007)(66946007)(66556008)(956004)(33716001)(6486002)(9686003)(44832011)(52116002)(86362001)(921003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 6QNrCNPV6HWFmUrbEKNG4+JgkhHkYqzhHlYZQkmtPYe27kDFMnEwvhvahOu1yMPrwZS+4I0TnI1edzlYMmxuVYfLKoALc/LlTU4h0hszbReoLvNHoTjn+W6ETghVB2xw94CRsHsIInhk13yhm5QPP4kLgFDgodtsWObQuyFbpKDqyy8MPTogFvZwM1Y7yPS2sTRdZYfghJxcS7iOcfeDzGBStsP9NMMwBmaSnpsTRzia/SsbW2MkAjJNdISNUOjdZNUHIPwfpvNRxgdO7AdGXKxqIp+RuLns7T3sFVkXeedFM3g49sW2UjCPhxzZL52ZUKGndidfr5VrrXVvsn+a+NOJuuhLnUX2D3fUKkK5UKIyl7TdLS3BiOFyg83XA2SbM0aRdKC8D/EFhstaRZL6AmSMAxgQmK9FH4teRrFDvXUks+El5EF89uGzWeR7o0iENCV8ar8lZSKOZN/XpZeFzvcPMGrLlKFSzzNoCoaT36k=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 d1145439-1343-4908-229c-08d812411faf
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Jun 2020 22:03:38.7550
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 vmj55qUTecJ3H62FZMvbyFX8cvZf02LgZjYpDeCq292LHKQGKvmVGd3PyXkgagTX
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2622
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INVPCID instruction handling is mostly same across both VMX and
SVM. So, move the code to common x86.c.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/kvm/vmx/vmx.c |   68 +----------------------------------------
 arch/x86/kvm/x86.c     |   79 ++++++++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h     |    3 +-
 3 files changed, 82 insertions(+), 68 deletions(-)

```
#### [PATCH 01/12] KVM: arm64: Add some basic functions to support hw DBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: zhukeqian <zhukeqian1@huawei.com>
X-Patchwork-Id: 11606987
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9695213B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 09:37:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8770C20786
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 09:37:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728260AbgFPJgR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 05:36:17 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:6337 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728250AbgFPJgP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 05:36:15 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id B02EF4A35D21C942F8BC;
        Tue, 16 Jun 2020 17:36:13 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.173.221.230) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Tue, 16 Jun 2020 17:36:04 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <liangpeng10@huawei.com>, <zhengxiang9@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 01/12] KVM: arm64: Add some basic functions to support hw DBM
Date: Tue, 16 Jun 2020 17:35:42 +0800
Message-ID: <20200616093553.27512-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200616093553.27512-1-zhukeqian1@huawei.com>
References: <20200616093553.27512-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.221.230]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prepare some basic functions to support hardware DBM for PTEs.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 36 ++++++++++++++++++++++++++++++++
 1 file changed, 36 insertions(+)

```
#### [PATCH] kvm: nVMX: flush TLB when decoded insn != VM-exit reasonFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11608741
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B13676A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:43:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8E0C6207E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 22:43:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bGdZAuvy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726025AbgFPWne (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 18:43:34 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54734 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725849AbgFPWne (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 18:43:34 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CC6E8C061573
        for <kvm@vger.kernel.org>; Tue, 16 Jun 2020 15:43:32 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id v15so223968qvm.2
        for <kvm@vger.kernel.org>; Tue, 16 Jun 2020 15:43:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=1ZS29LeX+3tvxr4Tw+LAYsKpl9FN0zDSujjFudjKbJQ=;
        b=bGdZAuvy5rOwnjAX9d4wyGzm0CnX0+lD7ClzAMndgj+qrBhgc5HjY9oZHMuI6dHP52
         9bE29dG6T2aQndRP95tWHfvNZWS/umrbje6gRxjpUN+Jwwg9jo3REkb3xfOxuvF4M4cg
         vvI7q8AHWNUdXt6GwwsejTQYOU0/W3fqUjwiB+WmShlgrRoGiT9R+KLgIPzRE5D7XqjD
         2Y6K53CJV+5XdXuNPGDZR6UeYvO2zihCwi2xZmJOo0sah3TvX+/kWpyIFkAgicrvjj+u
         vVzjz+T2frAPtNb/mlOrNz0aevldzm08mz9FuKS6729qjFjxSYy1OG/YCCqML+yXrdev
         7tYw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=1ZS29LeX+3tvxr4Tw+LAYsKpl9FN0zDSujjFudjKbJQ=;
        b=INyaqj4BhdaIE5rG6J0PgfYq1IKJafL7/H9k7tvZXNqXGUn/O4BADgUZI4xrny8UKr
         Y2ox0ImjuTQn8utLwvGmBP/Vjt3phAd+FT2Ji+CtWcTE1cK5gLU9qiTW6BXFpLH/Ezy3
         g6ORjxY+0QWE8aSae0lFcdrNJTsO2CV6XAG2eMdGn2ftbXuwHgv38FfwNAXRlic5hakr
         VuXPun7B7MSuosW2G01n3sX4S0HmjtstjEubjIwqJwyS2M5VUl12agM0ld8sq2PrV3lj
         2hmunVyC8FGNw9yREpIUSpslxqp9GFS5JpA7jKSqGE5IvFdlpAImG1J79W4ENdLLTAGr
         rtJA==
X-Gm-Message-State: AOAM530zHx1azKc71gYttwMsekMEgx1pFKK2h0+kXFRH5E/QAU5WR3/j
        /ToVYBee/ed3wtbeZJtnKRSH9TUZ3rm1ZNRiKENrJIFYpaS+kLwF8BgMuw82JzI+fpimRLtkcAl
        5ruFPI94ee6QTaPD9i5xGmN4kWAAtKfRt9CYBbQuHaCTFHTb8TSHfpUmFbw==
X-Google-Smtp-Source: 
 ABdhPJwm7FxidjZUR9hxNa4GxH27OP1BwC5fHRY1imNw5xCwm176YSy1ku28UHX9qndJjVNoOLGXv01fm3Y=
X-Received: by 2002:a05:6214:12cf:: with SMTP id
 s15mr4581045qvv.242.1592347411747;
 Tue, 16 Jun 2020 15:43:31 -0700 (PDT)
Date: Tue, 16 Jun 2020 22:43:05 +0000
Message-Id: <20200616224305.44242-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.290.gba653c62da-goog
Subject: [PATCH] kvm: nVMX: flush TLB when decoded insn != VM-exit reason
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Oliver Upton <oupton@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is possible for the instruction emulator to decode a different
instruction from what was implied by the VM-exit information provided by
hardware in vmcs02. Such is the case when the TLB entry for the guest's
IP is out of sync with the appropriate page-table mapping if page
installation isn't followed with a TLB flush.

Currently, KVM refuses to emulate in these scenarios, instead injecting
a #UD into L2. While this does address the security risk of
CVE-2020-2732, it could result in spurious #UDs to the L2 guest. Fix
this by instead flushing the TLB then resuming L2, allowing hardware to
generate the appropriate VM-exit to be reflected into L1.

Exceptional handling is also required for RSM and RDTSCP instructions.
RDTSCP could be emulated on hardware which doesn't support it,
therefore hardware will not generate a RDTSCP VM-exit on L2 resume. The
dual-monitor treatment of SMM is not supported in nVMX, which implies
that L0 should never handle a RSM instruction. Resuming the guest will
only result in another #UD. Avoid getting stuck in a loop with these
instructions by injecting a #UD for RSM and the appropriate VM-exit for
RDTSCP.

Fixes: 07721feee46b ("KVM: nVMX: Don't emulate instructions in guest mode")
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/emulate.c     |  2 ++
 arch/x86/kvm/kvm_emulate.h |  1 +
 arch/x86/kvm/vmx/vmx.c     | 68 ++++++++++++++++++++++++++++----------
 arch/x86/kvm/x86.c         |  2 +-
 4 files changed, 55 insertions(+), 18 deletions(-)

```
#### [PATCH] KVM: SVM: drop MSR_IA32_PERF_CAPABILITIES from emulated MSRs
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11608235
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF4E6913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:14:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D8CDD21475
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:14:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b/U4j28m"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732302AbgFPQOo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 12:14:44 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:56907 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732260AbgFPQOm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 12:14:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592324081;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=EGk4MDxuxjJxgEfnB6gIyOaKHUzMx57nfzVxFUf1flw=;
        b=b/U4j28mnQmJJ2K3ZZsm0kFoFZauhNVQWi91KqZiObYKmnSxwHnOTGNlUxvUVAm+Up9VPI
        mU+iLjzCDkwv9A0SIT6YKPmLVt4CmJ2j8f6U4UirpCAp9qmuzdGfXS4Za1xCMavVHWpU2L
        le6pg+Ywc8kZp3Ung2wBcWIrLEw7GYU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-460-KOglBjA_PZOFj8z9UPRzyA-1; Tue, 16 Jun 2020 12:14:39 -0400
X-MC-Unique: KOglBjA_PZOFj8z9UPRzyA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 22EC5100A69D;
        Tue, 16 Jun 2020 16:14:32 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.173])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0C6FF7CAA0;
        Tue, 16 Jun 2020 16:14:28 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Like Xu <like.xu@linux.intel.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: SVM: drop MSR_IA32_PERF_CAPABILITIES from emulated MSRs
Date: Tue, 16 Jun 2020 18:14:27 +0200
Message-Id: <20200616161427.375651-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

state_test/smm_test selftests are failing on AMD with:
"Unexpected result from KVM_GET_MSRS, r: 51 (failed MSR was 0x345)"

MSR_IA32_PERF_CAPABILITIES is an emulated MSR indeed but only on Intel,
make svm_has_emulated_msr() skip it so it is not returned by
KVM_GET_MSR_INDEX_LIST.

Fixes: 27461da31089 ("KVM: x86/pmu: Support full width counting")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PULL 01/12] Fix out-of-tree builds
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11608453
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E6F9D6A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 18:56:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C4DCE207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 18:56:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Wn8VUZkR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730301AbgFPS4d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 14:56:33 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:20072 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729994AbgFPS4b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 14:56:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592333790;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=QG4GcvBqyaMGQs6iL8I7UP/KbYkVhSk8WJz8geiWD8w=;
        b=Wn8VUZkRFImC8nVawRnoHcsIbEG8eKAIHOaCYF5Y7YGq+TjkupwrOPShnJEJzdmsrkfYO0
        kA4VRp0fhd2EFC2n0kilqv2jspVCsdXGQ3CBvRa2pzzLhej7dD4zfp2Vdq8CyBTNi/ENOj
        CFtinjcypHtPSpRpF0wdyrMSr2ywRlg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-1-YCtvSGvoOJyIIn9s_dqwXQ-1; Tue, 16 Jun 2020 14:56:28 -0400
X-MC-Unique: YCtvSGvoOJyIIn9s_dqwXQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D55CB80F5EA
        for <kvm@vger.kernel.org>; Tue, 16 Jun 2020 18:56:26 +0000 (UTC)
Received: from thuth.com (ovpn-114-128.ams2.redhat.com [10.36.114.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CAB207CAA8;
        Tue, 16 Jun 2020 18:56:25 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>
Subject: [kvm-unit-tests PULL 01/12] Fix out-of-tree builds
Date: Tue, 16 Jun 2020 20:56:11 +0200
Message-Id: <20200616185622.8644-2-thuth@redhat.com>
In-Reply-To: <20200616185622.8644-1-thuth@redhat.com>
References: <20200616185622.8644-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Since b16df9ee5f3b out-of-tree builds have been broken because we
started validating the newly user-configurable $erratatxt file
before linking it into the build dir. We fix this not by moving
the validation, but by removing the linking and instead using the
full path of the $erratatxt file. This allows one to keep that file
separate from the src and build dirs.

Fixes: b16df9ee5f3b ("arch-run: Add reserved variables to the default environ")
Reported-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Message-Id: <20200511070641.23492-1-drjones@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 configure | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: disable SSE on 32-bit hosts
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11607593
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2FF32618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 14:02:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F74A2071A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 14:02:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GyoiW6us"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729282AbgFPOCo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 10:02:44 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:20621 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729003AbgFPOCl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 10:02:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592316161;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=GUqpCaNzjY1hrjMIqzl3wKstWVQu95CSihxsh9IdoT8=;
        b=GyoiW6us3h729QtOoyNqg83z7PAfAy5ON/COzDWY1sN8nhZYtHUmhewrgWqHzpp7liJRss
        7M2W4sCbJeMqrpoSycNaamFchpFxOvOXwqloef5Kotqycj1UNXcw/jQ/5lTNbtbCp2Nnj1
        Ttnrvx8i06H3pyE+u2PG6x3CXW3BCRk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-329-qMmBIBchPnCwvNUgoMlwag-1; Tue, 16 Jun 2020 10:02:37 -0400
X-MC-Unique: qMmBIBchPnCwvNUgoMlwag-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 58ED31B2C9A5
        for <kvm@vger.kernel.org>; Tue, 16 Jun 2020 14:02:18 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E05515D9D7;
        Tue, 16 Jun 2020 14:02:17 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com
Subject: [PATCH kvm-unit-tests] x86: disable SSE on 32-bit hosts
Date: Tue, 16 Jun 2020 10:02:17 -0400
Message-Id: <20200616140217.104362-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On 64-bit hosts we are disabling SSE and SSE2.  Depending on the
compiler however it may use movq instructions for 64-bit transfers
even when targeting 32-bit processors; when CR4.OSFXSR is not set,
this results in an undefined opcode exception, so tell the compiler
to avoid those instructions on 32-bit hosts as well.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/Makefile.i386 | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] x86/pmu: Fix compilation on 32-bit hosts
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11607209
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFBE914DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 10:59:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AE4D6207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 10:59:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DlRr78wb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728420AbgFPK7t (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 06:59:49 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:22473 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728217AbgFPK7s (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 06:59:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592305188;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=VSb5JMG1sxeC0xJQaXKMewCIfOw5Nog4KVL7A45ysQk=;
        b=DlRr78wbg1IejgE0QWuf0038T1GKCUUWvuw8/LJhRtB0Bf0jNDbwAtj2owkGSuDPxnRF4h
        WcJA2rFeH6udgNDZe+M8WCsJfhsXMb14gBzI+IfBttlbNumYkFPD2U/rVDIkdl3o5nUhRt
        baOf7td1hePd4ONRNxDe+8M3ukW7ocE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-177-aQ9ly5QJOI-RNW31h3pRQw-1; Tue, 16 Jun 2020 06:59:44 -0400
X-MC-Unique: aQ9ly5QJOI-RNW31h3pRQw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A76F11009618;
        Tue, 16 Jun 2020 10:59:43 +0000 (UTC)
Received: from thuth.com (ovpn-114-128.ams2.redhat.com [10.36.114.128])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6813A19C71;
        Tue, 16 Jun 2020 10:59:42 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: like.xu@linux.intel.com, vkuznets@redhat.com
Subject: [kvm-unit-tests PATCH] x86/pmu: Fix compilation on 32-bit hosts
Date: Tue, 16 Jun 2020 12:59:40 +0200
Message-Id: <20200616105940.2907-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When building for 32-bit hosts, the compiler currently complains:

 x86/pmu.c: In function 'check_gp_counters_write_width':
 x86/pmu.c:490:30: error: left shift count >= width of type

Use the correct suffix to avoid this problem.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 x86/pmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: X86: Fix MSR range of APIC registers in X2APIC mode
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11606695
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF9CD913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 07:33:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A0B832078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 07:33:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727078AbgFPHdP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 03:33:15 -0400
Received: from mga05.intel.com ([192.55.52.43]:46469 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725710AbgFPHdP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 03:33:15 -0400
IronPort-SDR: 
 9kO8yEa9bIv+qkGyLCqMoy7mM6gWrOGfpzfNyEfyNy6xK8twKZpIhThI53k9WskcXxbs9F+kTa
 ONK/mXCd6BZg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Jun 2020 00:33:14 -0700
IronPort-SDR: 
 hFfb1kQV9mwaaKEDADpV9dTlNpLO4oG7L2F/uMb2dPpJGRWjNvR24A0jI3DhxCOr0cWiJN6ER6
 1Tkv++9zrW8Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,518,1583222400";
   d="scan'208";a="476339274"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by fmsmga005.fm.intel.com with ESMTP; 16 Jun 2020 00:33:10 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH] KVM: X86: Fix MSR range of APIC registers in X2APIC mode
Date: Tue, 16 Jun 2020 15:33:07 +0800
Message-Id: <20200616073307.16440-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Only MSR address range 0x800 through 0x8ff is architecturally reserved
and dedicated for accessing APIC registers in x2APIC mode.

Fixes: 0105d1a52640 ("KVM: x2apic interface to lapic")
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] kvm,x86: Force sync fault if previous attempts failed
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11608711
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2870013A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:49:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09D572082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:49:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b+GLksqh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726312AbgFPVtP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 17:49:15 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:29075 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725849AbgFPVtO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 17:49:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592344152;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=HJopFOxb2oxM6WdAq1omP3wKyWlk0t81tbJtj1deElA=;
        b=b+GLksqhNcP1Z0F1sXEEof3580ZAxXSvb6Kv+sO/39CtSRHfeceJ1E5jvrEDZ8RQO5lRcj
        s6tafEp38X4m2HelIGRqxwliuleqxp9NsyjA42S5UR6cg67SZiuMh2T5SyNZ2rjV0v+0WR
        Pk7ZY7aVK3aeJxRC10AlZMoE6cOIyHk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-274-9HvqEOY8M165iHPSCcEe1A-1; Tue, 16 Jun 2020 17:49:11 -0400
X-MC-Unique: 9HvqEOY8M165iHPSCcEe1A-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D315B18585C8;
        Tue, 16 Jun 2020 21:49:09 +0000 (UTC)
Received: from horse.redhat.com (ovpn-114-132.rdu2.redhat.com [10.10.114.132])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 510E419C71;
        Tue, 16 Jun 2020 21:49:03 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id C4B81225E4A; Tue, 16 Jun 2020 17:49:02 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, vgoyal@redhat.com, vkuznets@redhat.com,
        pbonzini@redhat.com, wanpengli@tencent.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/3] kvm,x86: Force sync fault if previous attempts failed
Date: Tue, 16 Jun 2020 17:48:45 -0400
Message-Id: <20200616214847.24482-2-vgoyal@redhat.com>
In-Reply-To: <20200616214847.24482-1-vgoyal@redhat.com>
References: <20200616214847.24482-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page fault error handling behavior in kvm seems little inconsistent when
page fault reports error. If we are doing fault synchronously
then we capture error (-EFAULT) returned by __gfn_to_pfn_memslot() and
exit to user space and qemu reports error, "error: kvm run failed Bad address".

But if we are doing async page fault, then async_pf_execute() will simply
ignore the error reported by get_user_pages_remote(). It is assumed that
page fault was successful and either a page ready event is injected in
guest or guest is brought out of artificial halt state and run again.
In both the cases when guest retries the instruction, it takes exit
again as page fault was not successful in previous attempt. And then
this infinite loop continues forever.

This patch tries to make this behavior consistent. That is instead of
getting into infinite loop of retrying page fault, exit to user space
and stop VM if page fault error happens. This can be improved by
injecting errors in guest when it is allowed. Later patches can
inject error when a process in guest triggered page fault and
in that case guest process will receive SIGBUS. Currently we don't
have a way to inject errors when guest is in kernel mode. Once we
have race free method to do so, we should be able to inject errors
and guest can do fixup_exception() if caller set it up so (virtio-fs).

When async pf encounters error then save that pfn and when next time
guest retries, do a sync fault instead of async fault. So that if error
is encountered, we exit to qemu and avoid infinite loop.

As of now only one error pfn is stored and that means it could be
overwritten before next a retry from guest happens. But this is
just a hint and if we miss it, some other time we will catch it.
If this becomes an issue, we could maintain an array of error
gfn later to help ease the issue.

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/x86.c              | 19 +++++++++++++++++--
 include/linux/kvm_host.h        |  1 +
 virt/kvm/async_pf.c             |  8 ++++++--
 6 files changed, 27 insertions(+), 6 deletions(-)

```
#### [RFC PATCH v3 1/3] vfio-ccw: Indicate if a channel_program is started
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11608551
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2BA986A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 172A720810
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730630AbgFPTvC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 15:51:02 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39810 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728144AbgFPTvB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 15:51:01 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJXbQk052836;
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q0rcf1sg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05GJYHB1055428;
        Tue, 16 Jun 2020 15:51:00 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q0rcf1ry-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:00 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJnkhm013461;
        Tue, 16 Jun 2020 19:50:58 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 31mpe7wv9a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 19:50:58 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05GJot6x31195158
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Jun 2020 19:50:55 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 736C542042;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5743942049;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id E9202E0145; Tue, 16 Jun 2020 21:50:54 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v3 1/3] vfio-ccw: Indicate if a channel_program is started
Date: Tue, 16 Jun 2020 21:50:51 +0200
Message-Id: <20200616195053.99253-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200616195053.99253-1-farman@linux.ibm.com>
References: <20200616195053.99253-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-16_12:2020-06-16,2020-06-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 malwarescore=0
 phishscore=0 priorityscore=1501 mlxlogscore=999 adultscore=0
 impostorscore=0 bulkscore=0 spamscore=0 clxscore=1015 suspectscore=2
 lowpriorityscore=0 cotscore=-2147483648 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006160138
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The interrupt path checks the FSM state when processing a final interrupt
(an interrupt that is neither subchannel active, nor device active),
to determine whether to call cp_free() and release the associated memory.
But, this does not fully close the window where a START comes in after a
HALT/CLEAR. If the START runs while the CLEAR interrupt is being processed,
the channel program struct will be allocated while the interrupt would be
considering whether or not to free it. If the FSM state is CP_PROCESSING,
then everything is fine. But if the START is able to issue its SSCH and get
a cc0, then the in-flight interrupt would have been for an unrelated
operation (perhaps none, if the subchannel was previously idle).

The channel_program struct has an "initialized" flag that is set early
in the fsm_io_request() flow, to simplify the various cp_*() accessors.
Let's extend this idea to include a "started" flag that announces that the
channel program has successfully been issued to hardware. With this, the
interrupt path can determine whether the final interrupt should also
release the cp resources instead of relying on a transient FSM state.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c  |  2 ++
 drivers/s390/cio/vfio_ccw_cp.h  |  1 +
 drivers/s390/cio/vfio_ccw_drv.c |  2 +-
 drivers/s390/cio/vfio_ccw_fsm.c | 11 +++++++++++
 4 files changed, 15 insertions(+), 1 deletion(-)

```
#### [PATCH v2] kvm: i386: allow TSC to differ by NTP correction bounds without TSC scaling
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 11608301
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81E656A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:58:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B00221475
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:58:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UzRJUaJP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729771AbgFPQ6v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 12:58:51 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:47817 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728861AbgFPQ6v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Jun 2020 12:58:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592326729;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=2naFO3eclxh//d8xCYs/AzrLY0N7rdJ2y7/KIjLVWcw=;
        b=UzRJUaJPme5r91VRJgYXgYtUPsdl17b9wngTILn3mxi8mP8L6hO6zCZx/5Ukkv6tfdL2uY
        DXC92PfwSaA98O6ygwqHnIL128QR7bzTidlFspavE85DxTGPg6//scQiqAOHwy4G+YjONK
        M20z6ZZ/owO48Nbi5QWKCyV+BsFvUXg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-456-5cKJ0fWnNB6C7W_m0zQ0sA-1; Tue, 16 Jun 2020 12:58:48 -0400
X-MC-Unique: 5cKJ0fWnNB6C7W_m0zQ0sA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2C09F80F5E5;
        Tue, 16 Jun 2020 16:58:47 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-9.gru2.redhat.com [10.97.112.9])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id DF1BF19C79;
        Tue, 16 Jun 2020 16:58:46 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 43FBB41887FC; Tue, 16 Jun 2020 13:58:05 -0300 (-03)
Date: Tue, 16 Jun 2020 13:58:05 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: qemu-devel <qemu-devel@nongnu.org>, kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>
Subject: [PATCH v2] kvm: i386: allow TSC to differ by NTP correction bounds
 without TSC scaling
Message-ID: <20200616165805.GA324612@fuller.cnet>
References: <20200615120127.GB224592@fuller.cnet>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200615120127.GB224592@fuller.cnet>
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Linux TSC calibration procedure is subject to small variations
(its common to see +-1 kHz difference between reboots on a given CPU, for example).

So migrating a guest between two hosts with identical processor can fail, in case 
of a small variation in calibrated TSC between them.

Allow a conservative 250ppm error between host TSC and VM TSC frequencies,
rather than requiring an exact match. NTP daemon in the guest can
correct this difference.

Also change migration to accept this bound.

KVM_SET_TSC_KHZ depends on a kernel interface change. Without this change,
the behaviour remains the same: in case of a different frequency 
between host and VM, KVM_SET_TSC_KHZ will fail and QEMU will exit.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---

v2: ensure behaviour is unchanged for older kernels and
    improve changelogs (Paolo)

```
#### [PATCH v2] KVM: x86: allow TSC to differ by NTP correction bounds without TSC scaling
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 11608237
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1C496A2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:15:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAB762071A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 16:15:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RJChc1jZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732333AbgFPQPT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 12:15:19 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:35407 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731536AbgFPQPQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 12:15:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592324115;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         in-reply-to:in-reply-to:references:references;
        bh=DZiLPWz8tGyf2nq5zcM61Q3toxd9Lry4Lg91Iu4Wmfo=;
        b=RJChc1jZd3AqYs2oLWQSog9jzaonM1tWv3UhwirdTSRAev4Pw1Xbnuu3LmRUMjfZlgY1NH
        ovO90e5fv8ZOArwmytoLIrZAdFSx2CPIyy3ozwo/mwoxTvPlCndtoivhACTRPx6FxyH4zx
        vWUFSj60lOXN8ehiKy0iWugc2uaxVEE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-350-wKsb1WAUP1yyDdZj35nrQg-1; Tue, 16 Jun 2020 12:15:13 -0400
X-MC-Unique: wKsb1WAUP1yyDdZj35nrQg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D869D5AEC7
        for <kvm@vger.kernel.org>; Tue, 16 Jun 2020 16:15:12 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-9.gru2.redhat.com [10.97.112.9])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 9C0457CAA0;
        Tue, 16 Jun 2020 16:15:12 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 622D041807CE; Tue, 16 Jun 2020 08:47:41 -0300 (-03)
Date: Tue, 16 Jun 2020 08:47:41 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm-devel <kvm@vger.kernel.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH v2] KVM: x86: allow TSC to differ by NTP correction bounds
 without TSC scaling
Message-ID: <20200616114741.GA298183@fuller.cnet>
References: <20200615115952.GA224592@fuller.cnet>
 <646f0beb-e050-ed2f-397b-a9afa2891e4f@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <646f0beb-e050-ed2f-397b-a9afa2891e4f@redhat.com>
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Linux TSC calibration procedure is subject to small variations
(its common to see +-1 kHz difference between reboots on a given CPU, for example).

So migrating a guest between two hosts with identical processor can fail, in case
of a small variation in calibrated TSC between them.

Without TSC scaling, the current kernel interface will either return an error
(if user_tsc_khz <= tsc_khz) or enable TSC catchup mode.

This change enables the following TSC tolerance check to
accept KVM_SET_TSC_KHZ within tsc_tolerance_ppm (which is 250ppm by default).

        /*
         * Compute the variation in TSC rate which is acceptable
         * within the range of tolerance and decide if the
         * rate being applied is within that bounds of the hardware
         * rate.  If so, no scaling or compensation need be done.
         */
        thresh_lo = adjust_tsc_khz(tsc_khz, -tsc_tolerance_ppm);
        thresh_hi = adjust_tsc_khz(tsc_khz, tsc_tolerance_ppm);
        if (user_tsc_khz < thresh_lo || user_tsc_khz > thresh_hi) {
                pr_debug("kvm: requested TSC rate %u falls outside tolerance [%u,%u]\n", user_tsc_khz, thresh_lo, thresh_hi);
                use_scaling = 1;
        }

NTP daemon in the guest can correct this difference (NTP can correct upto 500ppm).

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---

v2: improve changelog (Paolo Bonzini)

```
#### [RFC PATCH v3 2/3] vfio-ccw: Remove the CP_PENDING FSM state
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11608557
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3DF6D14E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 305552082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 19:51:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731100AbgFPTvD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 15:51:03 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41284 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730393AbgFPTvC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 15:51:02 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJXbnk052800;
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q0rcf1sn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05GJjgIj112890;
        Tue, 16 Jun 2020 15:51:01 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31q0rcf1s0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 15:51:00 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05GJo7ZY013895;
        Tue, 16 Jun 2020 19:50:58 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03ams.nl.ibm.com with ESMTP id 31mpe85vrg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Jun 2020 19:50:58 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05GJotTH64356560
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Jun 2020 19:50:55 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6FEF44C040;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 513F54C04E;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 16 Jun 2020 19:50:55 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id EBD64E027E; Tue, 16 Jun 2020 21:50:54 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v3 2/3] vfio-ccw: Remove the CP_PENDING FSM state
Date: Tue, 16 Jun 2020 21:50:52 +0200
Message-Id: <20200616195053.99253-3-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200616195053.99253-1-farman@linux.ibm.com>
References: <20200616195053.99253-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-16_12:2020-06-16,2020-06-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 malwarescore=0
 phishscore=0 priorityscore=1501 mlxlogscore=999 adultscore=0
 impostorscore=0 bulkscore=0 spamscore=0 clxscore=1015 suspectscore=2
 lowpriorityscore=0 cotscore=-2147483648 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006160138
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The FSM state is set to CP_PROCESSING when a START operation begins,
is set to CP_PENDING when a START operation is done (the SSCH
instruction gets a cc0), and is set back to IDLE when the final
interrupt is received (or if the START fails somehow). However, it is
categorically impossible to distinguish between interrupts when
other instructions can generate "final" interrupts via the async
region, so using this information for any decision-making at the
completion of an I/O is fraught with peril.

We could replace "CP_PENDING" with a generic "OPERATION_PENDING" state,
but it doesn't appear to buy us anything as far as knowing if we get
one interrupt for a START and another for a CLEAR, or if we just get
one interrupt for the CLEAR and the START never got off the ground.

So let's remove that entirely, and just move the FSM back to IDLE
once the START process completes.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c     |  3 ---
 drivers/s390/cio/vfio_ccw_fsm.c     | 16 +++-------------
 drivers/s390/cio/vfio_ccw_ops.c     |  3 +--
 drivers/s390/cio/vfio_ccw_private.h |  1 -
 4 files changed, 4 insertions(+), 19 deletions(-)

```
#### [PATCH] vfio/pci: Clear error and request eventfd ctx after releasing
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11608709
Return-Path: <SRS0=jnd6=75=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1566913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:26:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A880A208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Jun 2020 21:26:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jMOd9W8O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726387AbgFPV0p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Jun 2020 17:26:45 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:37961 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726134AbgFPV0p (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Jun 2020 17:26:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592342803;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=rfjyihg61U3ImXhyN/RZdOnqUBmVbpAphX1IIssGqq4=;
        b=jMOd9W8OZVUfbqdp/+zCeeWqPtazUN7tG6pOiknb4fD1/E5QRuM6T6f/m763lDxLnAxDBp
        I0QZlK0UcrEnLSPT/U2dHPs6mWSGwYBPIeTr562K43AzYylteLw5cZt4JusRdh9y3RnnW9
        XQrbs5OMYc3KKDLlRlNESBi3y4jtUEg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-140-iB73ybuIMlKdSBblkDt8xw-1; Tue, 16 Jun 2020 17:26:41 -0400
X-MC-Unique: iB73ybuIMlKdSBblkDt8xw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 853891512E0;
        Tue, 16 Jun 2020 21:26:40 +0000 (UTC)
Received: from gimli.home (ovpn-112-195.phx2.redhat.com [10.3.112.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C52A5D9D3;
        Tue, 16 Jun 2020 21:26:37 +0000 (UTC)
Subject: [PATCH] vfio/pci: Clear error and request eventfd ctx after
 releasing
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        cohuck@redhat.com, dwagner@suse.de, cai@lca.pw
Date: Tue, 16 Jun 2020 15:26:36 -0600
Message-ID: <159234276956.31057.6902954364435481688.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The next use of the device will generate an underflow from the
stale reference.

Cc: Qian Cai <cai@lca.pw>
Fixes: 1518ac272e78 ("vfio/pci: fix memory leaks of eventfd ctx")
Reported-by: Daniel Wagner <dwagner@suse.de>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c |    8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
