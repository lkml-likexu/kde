#### [PATCH v13 01/12] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12205709
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5D59DC433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 31B0A610EA
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:53:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233939AbhDOPyJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 11:54:09 -0400
Received: from mail-bn7nam10on2056.outbound.protection.outlook.com
 ([40.107.92.56]:15745
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231726AbhDOPyI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 11:54:08 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=bDgXXkpGdpduBZ/B0cbxxiaQ6XMsfROOoDuZCKu6QS1fiLLKxUjR9j0OsH9lgC1hCwgdo4Tk1NQ9U6gE9rX97HFIPitUwg82+dg17A3ONM1FUl4FJbiMkpph9S5a0Aq4/Ohj5u3WJWaRc8/6yKHGuJM3Jk82t5loA+6JDxp/fBKaSOx6PDJ1j03umJJqDHuYUFR4o2iRs8H12mCGpzegSX8n8nYL8+FnmjtKfq8rKgiUXjIn7C7+I+0yyNLeQtF383COaSb5UDlKrqv63VtVJWz4u0o1cE7PuPCBje7tiC4gbRkNo0Pj0AdpCd9cHAaapKCdniQ8g8HQDWHNIQT+pA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=oMSdzV4gDKpRhfmL9eXmwWWXAENhokaaDP5pZ/7coCq70MQYoDCWHAoexlZxDseHSLO5IFvUxtUPj1ebrNnr1U9XIwlVzE8T3MimUH0uwnZBNo0F8RS4S3MqxI4eHKIX0THuziW5qxxJX8FpMkd/R/QHD0W1FeU/n2XAZMuhHLMIo5Q8GVzhoJg5V6Ny3MiRq9phzg7dIclkbTMn1GhpHrjSHEVHmQvu6b03zRBZus4+ZuKn36MFB2ms0B5UTNtOVQpLKkNTKSwCTdzTQ/ppiLNVkIGG4ZBXFVOBI+2C5jI0D1uAx+KTooFdm9UqDhiYdOq3bqlXAsI6e44uXny+TA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=wLJv50LUh4B4c8/U5pHHudjCzGZ8tITqZFxf4alLIA4w4e47lLsIV35qOy9/J+4Efna3ukGZZ/yitRm/ps3Qkv/l1E5AydFp7KuXOricwD82/cGiPXYDmpCbQd2jPNSakHYetcAzHFu221/Zoi+oxQgFlmkex+p+9Sjxj9X/ZdI=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4384.namprd12.prod.outlook.com (2603:10b6:806:9f::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.16; Thu, 15 Apr
 2021 15:53:43 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%6]) with mapi id 15.20.4042.018; Thu, 15 Apr 2021
 15:53:43 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v13 01/12] KVM: SVM: Add KVM_SEV SEND_START command
Date: Thu, 15 Apr 2021 15:53:14 +0000
Message-Id: 
 <2f1686d0164e0f1b3d6a41d620408393e0a48376.1618498113.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1618498113.git.ashish.kalra@amd.com>
References: <cover.1618498113.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0161.namprd04.prod.outlook.com
 (2603:10b6:806:125::16) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN7PR04CA0161.namprd04.prod.outlook.com (2603:10b6:806:125::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.18 via Frontend
 Transport; Thu, 15 Apr 2021 15:53:42 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 6c671cd1-4deb-4c5b-20f7-08d90026a541
X-MS-TrafficTypeDiagnostic: SA0PR12MB4384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4384783AA409FAAEE2ED938F8E4D9@SA0PR12MB4384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 wSTTGRjOmF9r4zGJj7IjvfNi0uhN/dBdA80EO3+UNxTtDCf7NbfhajhGogbYlrlnrgfjndrdsuucCI/menihmID9u3xULIcpHQdDZwunnL8KFc+rlMsRQVedT9LXzbpWasRomP4Ac2of7PtxklvpSeDXjRfzUuALzwIrb9ISFs4QK7xusmL545Dq4kP2hojG5sTo4uyRRtc260i3Fz43WJNkbrFwKzcC/cI5KGCTIE6nxyuxr08cwOv7+g267z4PfmiUiaMM2JNB5tvvFvkxneyc9FoYUq0Saautd0ceMewQ3dCJgLb4tJCwFE0NfneAUrEKPBLQMAhAIftXWujxrqL5gzf/I1Z3PdGmt5J2QbxuMxnya3GOQhfrKZoMsYTI0cWSOrs0wSeNs2LhdWHOqAkRBKCnKtMk/0Eta0lwqY8LZnKNDr3FQsvNYGEqIFgVWHHiJoaP3cb9KT8UTAdLNKzOIlHKISd6YUGOS8fLEPysvHQfo1ouK6XRQGs7zRnYC/dS09V40xfyuifn2lIFynGEyuKIKHxPn5QDZdW1/KwCjLZzSsWQaRqtxEWjs/hJorR7H103YwCI3ySJLOZEAp2XIU1QNxFTm9qQgREIe+W/s7g1l0ED85c6EJb3vgxgGUMFQqDdN8T+JUmkgmBXMg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(346002)(136003)(376002)(39860400002)(366004)(2906002)(4326008)(83380400001)(6666004)(316002)(38350700002)(2616005)(38100700002)(36756003)(8676002)(956004)(8936002)(26005)(16526019)(7696005)(66946007)(186003)(66476007)(66556008)(478600001)(5660300002)(7416002)(52116002)(6486002)(86362001)(6916009);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?/+NMsKWNr6e0ghwuMoX2R3eY8w5Q+p?=
	=?utf-8?q?HPVbptvQkTpOrTb8GM/5ESCHNfQuWn4eONJ07OCYsK96sxzGEGd8zyjaYKM+zjlA0?=
	=?utf-8?q?KMyXt6zK6DlzRnQrXWJfMEb7So+W8eD70N2WV6odWAMpARqEYqIqwCsuOmG23nP4U?=
	=?utf-8?q?gBrRJ6DfAvGeBfpin3E+zvRlsmqdBt2ghX3YZ8EvZrl51lqa5q9iqbCnmfOLo0C+E?=
	=?utf-8?q?hc2zuuwmISKNGs+ATVFFIzWy2h3hsCtwR4ME7DDqCM+2fDHhGxu9uWCB/fPh10P4Q?=
	=?utf-8?q?8sllMgq3nDDuk4PNEnWeTFGiBf0nolkYb1zL84dslf1/0F0UD96pD5mcKGag3+AsN?=
	=?utf-8?q?mjqyY8Z75RZK3PH9/y2egrcQVhk7itfat1A7+AiS5hQY9xhowPSbKi4Uk2MICUXn/?=
	=?utf-8?q?eZ4lnu5PZVrHidPFXCbYh2+KqKEl3STd2utuDKPQuyG1v7cXroap3g/z2QOlbSp7l?=
	=?utf-8?q?/Y6YOldKdyiQn4zK2hGkXSphR6rymna3lqCMKZl/L8/w51Se20/PRNBDX9zFfhlnI?=
	=?utf-8?q?1pS2xmQMWH86ZKSnI+WsJ2Jo91ZJBBCEUHzu7uBNGkH+aeRI9y+AM6tFgR6eleyjD?=
	=?utf-8?q?Ksgae7St4i27gYcOIDN+pKrVrnbMGmID26v6mk6gkZ4Qh4k3cBPgOIJ+x1j45tqEk?=
	=?utf-8?q?UeBsx5v0rGwejQMaLGQIq+knHQi9or8PrJ9QvLgLb7uXypct0B6P9kCge6vPR025Y?=
	=?utf-8?q?PnvYSwSRdwdt1wvd7nsHms4Xs5MGuImsrLrhi2V5nL34pCZUYhjRWxpriYQNltxbD?=
	=?utf-8?q?mtlqcZhNWg2i/oluInyaSl+AbfiHG/DKr2+X+FyNmX/LnBzgiUAOZo8O+F6rJKWFi?=
	=?utf-8?q?2QtoezIs+pyEjg0lqoIdFK/MCUSHr2O87zlK91eBtof9HE4a3FV8714f7SfsqSoxY?=
	=?utf-8?q?Qq7tGMTAYo3TyQQjGuWZl1Dm/qsPFS8QIpfK8CyvDZ+gJrUXzik6H4Xov3uyZ9LXf?=
	=?utf-8?q?If13lgFLjC8oCyQYiqoxxRkzjSKvrauqDo0HEB9TFt7AlR21ROeRo8+RaPMxS5Obp?=
	=?utf-8?q?dNyelbu8BL4Y+zzog4Qk46ysswWSzq9tov8U3BVkPSfnT/gtNOsLjYms5CEPOMBoE?=
	=?utf-8?q?WYoJEq3bpbkVuq2HJI71tPQzR/xyyEX/o0k9PvRpFqfe80khQp/bt9lIjeO+SHxUf?=
	=?utf-8?q?zdEQpT2D+rlI521842hh3khgheQbtEHtnkVHL3l2kSPVC7wZYQzCSdri8QrszAko4?=
	=?utf-8?q?MvolN2L206h7q1iGkDc0F4WVmTC10G56lwxY22/0PI0hxNKDDz/G3maT7f0iWHwLJ?=
	=?utf-8?q?5qR/++Nn5kQ2aP?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6c671cd1-4deb-4c5b-20f7-08d90026a541
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 15 Apr 2021 15:53:43.3230
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 7XTjZAocLQtlGcEehXJXIM+mbV9YsBwQjCYo7NAiUeJVTPpMcdpivXvYVHOeqMJA9WiVR0KhwfS5hAB/RyLdLA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4384
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Reviewed-by: Steve Rutherford <srutherford@google.com>
Reviewed-by: Venu Busireddy <venu.busireddy@oracle.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  27 ++++
 arch/x86/kvm/svm/sev.c                        | 125 ++++++++++++++++++
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  12 ++
 4 files changed, 168 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/7] hyperv: Detect Nested virtualization support for SVM
##### From: Vineeth Pillai <viremana@linux.microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vineeth Pillai <viremana@linux.microsoft.com>
X-Patchwork-Id: 12205505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 41AF3C43462
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 279F4613C8
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:44:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233459AbhDONoW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 09:44:22 -0400
Received: from linux.microsoft.com ([13.77.154.182]:41532 "EHLO
        linux.microsoft.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233389AbhDONoV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 09:44:21 -0400
Received: from
 viremana-dev.fwjladdvyuiujdukmejncen4mf.xx.internal.cloudapp.net (unknown
 [13.66.132.26])
        by linux.microsoft.com (Postfix) with ESMTPSA id A2E4820B8002;
        Thu, 15 Apr 2021 06:43:57 -0700 (PDT)
DKIM-Filter: OpenDKIM Filter v2.11.0 linux.microsoft.com A2E4820B8002
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linux.microsoft.com;
        s=default; t=1618494237;
        bh=zgpGiyGDi60pFC4qD9nG0XS7yB8eDhV4EULVqhMuJOw=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=r013N2753/Bt4Mz7SOGaPTdZktqIW+RyyfknILC0UhlgvO2sy45QDHjH/numJGnm6
         1B74ebXrBxviT5EL//+CgA8XCGAkNTPP2xUOV8jFPMfIXuonIHKtDIVFml2juoyZWR
         8rnpghLmpk3IKeUPqs6ZUnskABrFtS6p3IndWIyo=
From: Vineeth Pillai <viremana@linux.microsoft.com>
To: Lan Tianyu <Tianyu.Lan@microsoft.com>,
        Michael Kelley <mikelley@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Wei Liu <wei.liu@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>
Cc: Vineeth Pillai <viremana@linux.microsoft.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "K. Y. Srinivasan" <kys@microsoft.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v2 1/7] hyperv: Detect Nested virtualization support for SVM
Date: Thu, 15 Apr 2021 13:43:36 +0000
Message-Id: 
 <9d12558549bc0c6f179b26f5b16c751bdfab3f74.1618492553.git.viremana@linux.microsoft.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <cover.1618492553.git.viremana@linux.microsoft.com>
References: <cover.1618492553.git.viremana@linux.microsoft.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Detect nested features exposed by Hyper-V if SVM is enabled.

Signed-off-by: Vineeth Pillai <viremana@linux.microsoft.com>
---
 arch/x86/kernel/cpu/mshyperv.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH v5 1/6] KVM: arm64: Introduce KVM_PGTABLE_S2_GUEST stage-2 flag
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12205203
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC176C433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 11:50:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B270061153
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 11:50:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232672AbhDOLvJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 07:51:09 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:15687 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232640AbhDOLvG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 07:51:06 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4FLcz76TfBzpYXf;
        Thu, 15 Apr 2021 19:47:47 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Thu, 15 Apr 2021 19:50:34 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Quentin Perret" <qperret@google.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>, <wanghaibin.wang@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v5 1/6] KVM: arm64: Introduce KVM_PGTABLE_S2_GUEST stage-2
 flag
Date: Thu, 15 Apr 2021 19:50:27 +0800
Message-ID: <20210415115032.35760-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210415115032.35760-1-wangyanan55@huawei.com>
References: <20210415115032.35760-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The stage-2 page table code in pgtable.c now is generally used for
guest stage-2 and host stage-2. There may be some different issues
between guest S2 page-table and host S2 page-table that we should
consider, e.g., whether CMOs are needed when creating a new mapping.

So introduce the KVM_PGTABLE_S2_GUEST flag to determine if we are
doing something about guest stage-2. This flag will be used in a
coming patch, in which we will move CMOs for guest to pgtable.c.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/kvm_pgtable.h | 38 ++++++++++++++++++----------
 arch/arm64/kvm/mmu.c                 |  3 ++-
 2 files changed, 26 insertions(+), 15 deletions(-)

```
#### [PATCH v4 1/2] kvm/arm64: Remove the creation time's mapping of MMIO regions
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12205593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE704C43461
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 14:03:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE62D611F1
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 14:03:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233364AbhDOOEK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 10:04:10 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:16926 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233257AbhDOOEJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 10:04:09 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FLgxq0bhHzkjn6;
        Thu, 15 Apr 2021 22:01:51 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.498.0; Thu, 15 Apr 2021 22:03:33 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v4 1/2] kvm/arm64: Remove the creation time's mapping of MMIO
 regions
Date: Thu, 15 Apr 2021 22:03:27 +0800
Message-ID: <20210415140328.24200-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210415140328.24200-1-zhukeqian1@huawei.com>
References: <20210415140328.24200-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MMIO regions may be unmapped for many reasons and can be remapped
by stage2 fault path. Map MMIO regions at creation time becomes a
minor optimization and makes these two mapping path hard to sync.

Remove the mapping code while keep the useful sanity check.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kvm/mmu.c | 38 +++-----------------------------------
 1 file changed, 3 insertions(+), 35 deletions(-)

```
#### [PATCH v3 1/9] context_tracking: Move guest exit context tracking to separate helpers
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12206183
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90DE1C433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 22:21:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B625610FC
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 22:21:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236712AbhDOWVl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 18:21:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57134 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236304AbhDOWVk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 18:21:40 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B5902C061574
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 15:21:16 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id w9so3970423ybw.7
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 15:21:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=2rHkFHcKdsKtPlphUZSPjmFsPrJ5FQMml9mM0e4W7Zc=;
        b=Sdv8k1IdZLOeBzPcIHjmgwJvr30lVQhykx0hvcsxfUl49I6CdmrwLkVbh3hV+Ki+lU
         9FgNVGTL6AhKmBPLLJsOtFvFnVAmd9es66AmtmX93zsZySZKpzLCQcstWKqR18p9xu1V
         A4SAYuvwFCZj+IFvJs55MwqCJ3rSkkS8OincKBNAMhgM9zYj7ywd9/eNQQk8yr2ATmah
         fXun1sJdo3rL8im+W9tt+twTRmtH/ASLsnxpA84IpCEoOfjOfsRXmg8gMsxVBKugvghq
         /EQcpFNjuzdNG9gjvw1gOUYvKGfYWCL1jr88Kg0XSNlF0/0+spGD+TtUWO2AwUlYXQst
         i2TQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=2rHkFHcKdsKtPlphUZSPjmFsPrJ5FQMml9mM0e4W7Zc=;
        b=Lkb+qO2qVdTFDDx3+avuF5WON5aLBBZiyEtFI/0x7oFd4yRaJsknl7iQ4HvRyfcckJ
         wcaWTurBBaV9KazHusxkZNHlggplDMq2SE3HbuRVyLnhAeDHNn1xGTwXv73NWWdv4x7Y
         UwRdugQL3bQBk0u3/F9gx9zP5Ky1uvXDsAsg1r5+zF2cpQ05TuMHODA85JksD1D/VZDu
         tlVBXCRfAQ1v5XriNBTOYUO++IgRC7qSWYL1USxFVlais5iQdjRBtjQZvToFYOgbcinh
         ssdZDV3bPNgoREP32KnrNlA7VNEMNbcBIJl03t8mboRyT72U1Qgg8qw+rmwYTe+b4V2t
         u+yA==
X-Gm-Message-State: AOAM533HRGgaGSaCXfNOWq36JqHYDM/PczJvT7G7rxDBj2ZmM7hRglG0
        l0Szg8Hf5gz9hyDf9GDw0yO38ymxegw=
X-Google-Smtp-Source: 
 ABdhPJxt/mukU9KkDXUa7r3vWCK3xUAeHdvtmdgfysot73ik6ImSoiiXCJDED9AESLevjYuAltjuZtEJn5U=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:6c93:ada0:6bbf:e7db])
 (user=seanjc job=sendgmr) by 2002:a25:e6c7:: with SMTP id
 d190mr6937056ybh.394.1618525275978;
 Thu, 15 Apr 2021 15:21:15 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 15 Apr 2021 15:20:58 -0700
In-Reply-To: <20210415222106.1643837-1-seanjc@google.com>
Message-Id: <20210415222106.1643837-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210415222106.1643837-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH v3 1/9] context_tracking: Move guest exit context tracking to
 separate helpers
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Michael Tokarev <mjt@tls.msk.ru>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Provide separate context tracking helpers for guest exit, the standalone
helpers will be called separately by KVM x86 in later patches to fix
tick-based accounting.

Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Sean Christopherson <seanjc@google.com>
Cc: Michael Tokarev <mjt@tls.msk.ru>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Co-developed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 include/linux/context_tracking.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: s390: fix guarded storage control register handling
##### From: Heiko Carstens <hca@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Heiko Carstens <hca@linux.ibm.com>
X-Patchwork-Id: 12204605
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 28AC8C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 08:01:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C2A6611F1
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 08:01:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231266AbhDOIB5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 04:01:57 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:13852 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230190AbhDOIB4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 15 Apr 2021 04:01:56 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13F7XvQ5152102;
        Thu, 15 Apr 2021 04:01:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=Iy+4HEBSF+6Bj1MzBbaPvov+Xtf3UDKQhBpPJ8i7LDw=;
 b=re0aowbxXwZsu8Y6GwmjiH+iLQxFENxjcoYfAuplBPNLiaWDQDxy2EzikGqbeYtOqMsw
 zdshtgZPPiyXjHygi+VG2tRBAQEHWvxDcKcV8ZDs7hufE0EmciNA5TnUBmk17YmN7i45
 yb7hLkwOAcCgIvVafsRwfURLXEDBsZFbNyw1a4Jm6hZy+A31XEFWK8v9RJ2ct+WycGrx
 AlOqZRMkBWUkw8PMH1ar6d9eBtcxaTNKsoXxLsOqrQ4Pv82GlCCYSWpsEuL7M0v8aUl4
 qdH7b8440+wqy1x/Q7R2chaO7brmYyKmwAstLDjx3XI5sfVYa11762mFBxF7RcdkS8v5 EQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37x13v8w1g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Apr 2021 04:01:33 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13F7YPS0153929;
        Thu, 15 Apr 2021 04:01:33 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37x13v8w0j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Apr 2021 04:01:33 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13F7qMaL030873;
        Thu, 15 Apr 2021 08:01:30 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04ams.nl.ibm.com with ESMTP id 37u3n8uqum-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Apr 2021 08:01:30 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13F815wT22479228
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 15 Apr 2021 08:01:05 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 60FD111C06E;
        Thu, 15 Apr 2021 08:01:27 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2C91011C064;
        Thu, 15 Apr 2021 08:01:27 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 15 Apr 2021 08:01:27 +0000 (GMT)
From: Heiko Carstens <hca@linux.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org
Subject: [PATCH] KVM: s390: fix guarded storage control register handling
Date: Thu, 15 Apr 2021 10:01:27 +0200
Message-Id: <20210415080127.1061275-1-hca@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: oW4X9HK-9CKK23m1Mb8WhFHrZfpUPmTT
X-Proofpoint-ORIG-GUID: hLD123nSDLfmqXYS4Ky0LkkimoaxWHCY
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-15_03:2021-04-15,2021-04-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 impostorscore=0
 suspectscore=0 phishscore=0 malwarescore=0 lowpriorityscore=0 adultscore=0
 mlxscore=0 spamscore=0 priorityscore=1501 clxscore=1015 mlxlogscore=624
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104150049
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

store_regs_fmt2() has an ordering problem: first the guarded storage
facility is enabled on the local cpu, then preemption disabled, and
then the STGSC (store guarded storage controls) instruction is
executed.

If the process gets scheduled away between enabling the guarded
storage facility and before preemption is disabled, this might lead to
a special operation exception and therefore kernel crash as soon as
the process is scheduled back and the STGSC instruction is executed.

Fixes: 4e0b1ab72b8a ("KVM: s390: gs support for kvm guests")
Cc: <stable@vger.kernel.org> # 4.12
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Heiko Carstens <hca@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/4] KVM: stats: Separate common stats from architecture specific ones
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12205675
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 01324C43470
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:20:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB0DB613C0
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 15:20:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234279AbhDOPUq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 11:20:46 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48912 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236918AbhDOPUS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 11:20:18 -0400
Received: from mail-qk1-x749.google.com (mail-qk1-x749.google.com
 [IPv6:2607:f8b0:4864:20::749])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EE1F2C061371
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 08:17:46 -0700 (PDT)
Received: by mail-qk1-x749.google.com with SMTP id 79so1710946qkm.20
        for <kvm@vger.kernel.org>; Thu, 15 Apr 2021 08:17:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=mlpq2JOS6LVo7hR/1JUgyMS7GDNYOTEdrZCVhgUJoZk=;
        b=C5QvjsMmtJ9feDzYR887MMwiqH1nEUYVC+yy6hcAyh86E+5yIP30YgA/UAHL1n3/Ja
         tQfHKpGCnul+SI1Bavpha03DyMiJwKHLYhflaVQn8JMwtRRN6htqpE0wXY9EF6c4dygY
         6ZWO8zY1nNOsCxh8CR1YLsTZcZGYsWOXwRpjS/VYT9v2m795COAo0zrjUUQ7ZZqfoZYi
         PxFn75NeQqA+TarRUdbDZami5XU/ATbqxhaMOaJidr7H29uo5FhZ3DO2tiwSftyp9MCk
         92wj85zNXV0iO8vVhgOCf0LyCuNf6yWNc8RQI7QmF37YKKcONa/OpoQUEq8TXtHTciYn
         fxug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=mlpq2JOS6LVo7hR/1JUgyMS7GDNYOTEdrZCVhgUJoZk=;
        b=d2XK3BGtWBSxcxDD8m6Q79IwTkKUKVUNDj1mwwxEOiVCDqy9Z4jfwLzN/yVAmH2eDT
         OJ6Hq7dwRHqdhwUq+TveCwbUHwqadkJlBBEeaR5U8VJxClpL2xs3bvNGm4tO6ZR081eB
         KcT6Ud43DFUPwTeCfiWpJ6S+7Iofg89oQVCOc8jjcIjcUTrbHTltOprdq1g8iM6HTAn9
         KhsJbuEx9fF/5q3XuBahJOZN2AmahBizOba5nWU2iJVLoH9pdpuwZTWk2iGBqOIblta3
         38cqbWAk1CUxr4pldkVkW42/gkBSK4gyoEHv9s6mS57c7Ng76wo/4ICa9Vw6nWBfy8J/
         gEaQ==
X-Gm-Message-State: AOAM531IXD8ob1vEERd3i6x8wFEkPbq9sov1PevFp4XIwjlMIG22QM8N
        Ze/8OdccCK2moxh9+BMrTdtdvb1B1bI/wJz7Je8XB3ByPgndv6NuQGr7oKTzW1BSoJgFYIx1HfO
        9twpzAFUM53mHsigyWFcXTJwyvNsNaTJrHWir+hpDlDWL4zsRxndYLBgvlIGIlanzsCypUBI=
X-Google-Smtp-Source: 
 ABdhPJwrC+nyGQM9VZ9qcUYBJx+Xihn39yLQfi83D/lOKULB5hUpQ+ZZwIdkvGHaw/py2K7TofFgNDQDY2eZkcldog==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:ad4:576e:: with SMTP id
 r14mr3740970qvx.13.1618499866086; Thu, 15 Apr 2021 08:17:46 -0700 (PDT)
Date: Thu, 15 Apr 2021 15:17:38 +0000
In-Reply-To: <20210415151741.1607806-1-jingzhangos@google.com>
Message-Id: <20210415151741.1607806-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210415151741.1607806-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH v2 1/4] KVM: stats: Separate common stats from architecture
 specific ones
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Put all common statistics in a separate structure to ease
statistics handling for the incoming new statistics API.

No functional change intended.

Signed-off-by: Jing Zhang <jingzhangos@google.com>
---
 arch/arm64/include/asm/kvm_host.h   |  9 ++-------
 arch/arm64/kvm/guest.c              | 12 ++++++------
 arch/mips/include/asm/kvm_host.h    |  9 ++-------
 arch/mips/kvm/mips.c                | 12 ++++++------
 arch/powerpc/include/asm/kvm_host.h |  9 ++-------
 arch/powerpc/kvm/book3s.c           | 12 ++++++------
 arch/powerpc/kvm/book3s_hv.c        | 12 ++++++------
 arch/powerpc/kvm/book3s_pr.c        |  2 +-
 arch/powerpc/kvm/book3s_pr_papr.c   |  2 +-
 arch/powerpc/kvm/booke.c            | 14 +++++++-------
 arch/s390/include/asm/kvm_host.h    |  9 ++-------
 arch/s390/kvm/kvm-s390.c            | 12 ++++++------
 arch/x86/include/asm/kvm_host.h     |  9 ++-------
 arch/x86/kvm/x86.c                  | 14 +++++++-------
 include/linux/kvm_host.h            |  5 +++++
 include/linux/kvm_types.h           | 12 ++++++++++++
 virt/kvm/kvm_main.c                 | 14 +++++++-------
 17 files changed, 80 insertions(+), 88 deletions(-)

```
#### [PATCH kvmtool] arm: Fail early if KVM_CAP_ARM_PMU_V3 is not supported
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12205475
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 562D0C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:17:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2E2C5611AC
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 13:17:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233088AbhDONRV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 09:17:21 -0400
Received: from foss.arm.com ([217.140.110.172]:45992 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230202AbhDONRV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 09:17:21 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EE92311B3;
        Thu, 15 Apr 2021 06:16:57 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 3B0E33F694;
        Thu, 15 Apr 2021 06:16:57 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: will@kernel.org, julien.thierry.kdev@gmail.com,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [PATCH kvmtool] arm: Fail early if KVM_CAP_ARM_PMU_V3 is not
 supported
Date: Thu, 15 Apr 2021 14:17:25 +0100
Message-Id: <20210415131725.105675-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pmu__generate_fdt_nodes() checks if the host has support for PMU in a guest
and prints a warning if that's not the case. However, this check is too
late because the function is called after the VCPU has been created, and
VCPU creation fails if KVM_CAP_ARM_PMU_V3 is not available with a rather
unhelpful error:

$ ./vm run -c1 -m64 -f selftest.flat --pmu
  # lkvm run --firmware selftest.flat -m 64 -c 1 --name guest-1039
  Info: Placing fdt at 0x80200000 - 0x80210000
  Fatal: Unable to initialise vcpu

Move the check for KVM_CAP_ARM_PMU_V3 to kvm_cpu__arch_init() before the
VCPU is created so the user can get a more useful error message. This
also matches the behaviour of KVM_CAP_ARM_EL1_32BIT.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/kvm-cpu.c | 4 ++++
 arm/pmu.c     | 5 -----
 2 files changed, 4 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: x86/mmu: Remove duplicate MMU trace log
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12204217
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 968D3C433ED
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:49:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67FF36124B
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:49:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229712AbhDODuT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 23:50:19 -0400
Received: from mga18.intel.com ([134.134.136.126]:39811 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229449AbhDODuS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 23:50:18 -0400
IronPort-SDR: 
 LcAS/FaFqN+QrwO3Pu3kAeuEQD+ZViLj/tQcipVulWvblxVIEXizIJFzzqm0vvPt04vOyeyXw/
 B9gyF6n93nEA==
X-IronPort-AV: E=McAfee;i="6200,9189,9954"; a="182284123"
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="182284123"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 20:49:55 -0700
IronPort-SDR: 
 WRhIuMztRvqgxOokaF65zXkWd3BBzqc93Tlm5UoyMWHsnWjlUx5nbtMy3w/E901X0YSlf3/xUv
 8FuMA6ruRl/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="452746853"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga002.fm.intel.com with ESMTP; 14 Apr 2021 20:49:54 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] KVM: x86/mmu: Remove duplicate MMU trace log
Date: Thu, 15 Apr 2021 12:01:41 +0800
Message-Id: <20210415040141.5218-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v5 01/16] perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake Server
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12204157
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5172CC433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:20:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 181E761158
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 03:20:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229768AbhDODUt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 23:20:49 -0400
Received: from mga11.intel.com ([192.55.52.93]:1119 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229763AbhDODUs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 23:20:48 -0400
IronPort-SDR: 
 pT0yoJZqlpIJMgk8pYWxHS1Ic8LeL3fjWVU25eOD7eUyXyORucQA1o7lxJFRdxg8fMRnY0Y9oM
 8Zk07IOEfvcQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9954"; a="191592805"
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="191592805"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 20:20:26 -0700
IronPort-SDR: 
 vTAQYnfuyIiOu6Yc4YFaqavlN/PFmeGmgbUPYV++vlSraIA+75JjI9H+3xyf/Y0u2v4uXmw8Id
 VN3hW4Nw64zw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="425013858"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 14 Apr 2021 20:20:22 -0700
From: Like Xu <like.xu@linux.intel.com>
To: peterz@infradead.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: andi@firstfloor.org, kan.liang@linux.intel.com,
        wei.w.wang@intel.com, eranian@google.com, liuxiangdong5@huawei.com,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        x86@kernel.org, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v5 01/16] perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake
 Server
Date: Thu, 15 Apr 2021 11:20:01 +0800
Message-Id: <20210415032016.166201-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210415032016.166201-1-like.xu@linux.intel.com>
References: <20210415032016.166201-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new hardware facility supporting guest PEBS is only available
on Intel Ice Lake Server platforms for now. KVM will check this field
through perf_get_x86_pmu_capability() instead of hard coding the cpu
models in the KVM code. If it is supported, the guest PBES capability
will be exposed to the guest.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/events/core.c            | 1 +
 arch/x86/events/intel/core.c      | 1 +
 arch/x86/events/perf_event.h      | 3 ++-
 arch/x86/include/asm/perf_event.h | 1 +
 4 files changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH 2/2] tools: do not include scripts/Kbuild.include
##### From: Masahiro Yamada <masahiroy@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Masahiro Yamada <masahiroy@kernel.org>
X-Patchwork-Id: 12204575
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2035DC433B4
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 07:32:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D8117610C8
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 07:32:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231292AbhDOHdT (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 03:33:19 -0400
Received: from condef-01.nifty.com ([202.248.20.66]:60330 "EHLO
        condef-01.nifty.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230090AbhDOHdS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 03:33:18 -0400
Received: from conuserg-12.nifty.com ([10.126.8.75])by condef-01.nifty.com
 with ESMTP id 13F7Tf74032587;
        Thu, 15 Apr 2021 16:29:54 +0900
Received: from localhost.localdomain (133-32-232-101.west.xps.vectant.ne.jp
 [133.32.232.101]) (authenticated)
        by conuserg-12.nifty.com with ESMTP id 13F7REfK011485;
        Thu, 15 Apr 2021 16:27:15 +0900
DKIM-Filter: OpenDKIM Filter v2.10.3 conuserg-12.nifty.com 13F7REfK011485
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nifty.com;
        s=dec2015msa; t=1618471637;
        bh=S3fDVUSMdnf8V+kxnVMGDGkdp8jWRQNGgMv5wUjnHkc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=N517H+eX8yGLr6xJUluj8A4xY1b9FBJN2FvNPhdKgdsjpKGfWNv50wQnTTJ5g0HES
         hNoiMh08DEo+IJ5zGDRy7I/3qDRClSWeMLO4+gSa77rspDf/y2TOuIXcYWIIwOns6N
         SeLXdHzuUFcpjF/FMpBGoVqW/jU+RgoqLNZUo5PE0iO+0pq+QSnahTgzOnTDw8FQUH
         8SsgAjaTENab7G/kGqtw3vWuBXiFBlZA7wiOCZLkMJv9lRuepD1N90V7EdnXtfykNC
         iWJLOxcqwthPzyVgne1TfuK/yY0iyhpcYdgiVrlsPErljM7U2UCu4fN4Oho3TgJorw
         ONUwqr60xISJg==
X-Nifty-SrcIP: [133.32.232.101]
From: Masahiro Yamada <masahiroy@kernel.org>
To: linux-kbuild@vger.kernel.org
Cc: Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Masahiro Yamada <masahiroy@kernel.org>,
        Alexei Starovoitov <ast@kernel.org>,
        Andrii Nakryiko <andrii@kernel.org>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Daniel Borkmann <daniel@iogearbox.net>,
        Harish <harish@linux.ibm.com>,
        John Fastabend <john.fastabend@gmail.com>,
        KP Singh <kpsingh@kernel.org>, Martin KaFai Lau <kafai@fb.com>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Paul Mackerras <paulus@samba.org>,
        Shuah Khan <shuah@kernel.org>,
        Song Liu <songliubraving@fb.com>, Yonghong Song <yhs@fb.com>,
        bpf@vger.kernel.org, clang-built-linux@googlegroups.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        netdev@vger.kernel.org
Subject: [PATCH 2/2] tools: do not include scripts/Kbuild.include
Date: Thu, 15 Apr 2021 16:27:00 +0900
Message-Id: <20210415072700.147125-2-masahiroy@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210415072700.147125-1-masahiroy@kernel.org>
References: <20210415072700.147125-1-masahiroy@kernel.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit d9f4ff50d2aa ("kbuild: spilt cc-option and friends to
scripts/Makefile.compiler"), some kselftests fail to build.

The tools/ directory opted out Kbuild, and went in a different
direction. They copy any kind of files to the tools/ directory
in order to do whatever they want to do in their world.

tools/build/Build.include mimics scripts/Kbuild.include, but some
tool Makefiles included the Kbuild one to import a feature that is
missing in tools/build/Build.include:

 - Commit ec04aa3ae87b ("tools/thermal: tmon: use "-fstack-protector"
   only if supported") included scripts/Kbuild.include from
   tools/thermal/tmon/Makefile to import the cc-option macro.

 - Commit c2390f16fc5b ("selftests: kvm: fix for compilers that do
   not support -no-pie") included scripts/Kbuild.include from
   tools/testing/selftests/kvm/Makefile to import the try-run macro.

 - Commit 9cae4ace80ef ("selftests/bpf: do not ignore clang
   failures") included scripts/Kbuild.include from
   tools/testing/selftests/bpf/Makefile to import the .DELETE_ON_ERROR
   target.

 - Commit 0695f8bca93e ("selftests/powerpc: Handle Makefile for
   unrecognized option") included scripts/Kbuild.include from
   tools/testing/selftests/powerpc/pmu/ebb/Makefile to import the
   try-run macro.

Copy what they want there, and stop including scripts/Kbuild.include
from the tool Makefiles.

Link: https://lore.kernel.org/lkml/86dadf33-70f7-a5ac-cb8c-64966d2f45a1@linux.ibm.com/
Fixes: d9f4ff50d2aa ("kbuild: spilt cc-option and friends to scripts/Makefile.compiler")
Reported-by: Janosch Frank <frankja@linux.ibm.com>
Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Masahiro Yamada <masahiroy@kernel.org>
---

 tools/testing/selftests/bpf/Makefile          |  3 ++-
 tools/testing/selftests/kvm/Makefile          | 12 +++++++++++-
 .../selftests/powerpc/pmu/ebb/Makefile        | 11 ++++++++++-
 tools/thermal/tmon/Makefile                   | 19 +++++++++++++++++--
 4 files changed, 40 insertions(+), 5 deletions(-)

```
#### [PATCH V2 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12204897
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E7F84C43470
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 09:59:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CEA71611AC
	for <kvm@archiver.kernel.org>; Thu, 15 Apr 2021 09:59:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232253AbhDOJ7Y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 15 Apr 2021 05:59:24 -0400
Received: from mga12.intel.com ([192.55.52.136]:65315 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232209AbhDOJ7V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 15 Apr 2021 05:59:21 -0400
IronPort-SDR: 
 02Pu6UObZ4W7jcFAMAOMKJnmm2dT3uIhRf6ND3m0Wtb55tmDr39KueYMMGRIZVBJi2apqOrWfQ
 Pwmx5BbR7+AA==
X-IronPort-AV: E=McAfee;i="6200,9189,9954"; a="174321437"
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="174321437"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2021 02:58:58 -0700
IronPort-SDR: 
 CP+XLAt/ruZ66tZse0MNcHsH47xkIq3kJARn797CqkxKU3olf7A0lK2aDf5p2n8l+sZPgJFCvE
 T7e8r81qOsdA==
X-IronPort-AV: E=Sophos;i="5.82,223,1613462400";
   d="scan'208";a="425123454"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Apr 2021 02:58:56 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
Date: Thu, 15 Apr 2021 17:53:34 +0800
Message-Id: <20210415095336.4792-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210415095336.4792-1-lingshan.zhu@intel.com>
References: <20210415095336.4792-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit deduces VIRTIO device ID as device type when probe,
then ifcvf_vdpa_get_device_id() can simply return the ID.
ifcvf_vdpa_get_features() and ifcvf_vdpa_get_config_size()
can work properly based on the device ID.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.h |  1 +
 drivers/vdpa/ifcvf/ifcvf_main.c | 30 ++++++++++++++++++------------
 2 files changed, 19 insertions(+), 12 deletions(-)

```
