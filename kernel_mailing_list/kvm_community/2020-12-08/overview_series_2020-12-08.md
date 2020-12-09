#### [PATCH v9 01/18] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11959905
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22F85C2BB48
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 22:05:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0BFC923AC4
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 22:05:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730754AbgLHWFD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 17:05:03 -0500
Received: from mail-dm6nam10on2062.outbound.protection.outlook.com
 ([40.107.93.62]:37153
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1730739AbgLHWFC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Dec 2020 17:05:02 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=eShcA53hVoYDJyFyd2d6Kl+U65ko/f0DRh/nz6Y8fxAFCw34+LFGsUghIl6CK5UmQcddBsJ35kmC218exJEJhi+oI6EzAEmvBis2g94SBeUZMIbnoRzO2Bebba6/BtysFzoqkUk988eJ35be552kIRIPTh1NGEOCrOQ7TphCJB8PgD028CkPF3ecsAiFeO5ex+axBtgyipB/bfbRnsHUuuth11/g171Jdu6mUSniF3qIYOKklsfUt2gqTusZ0HyGrw1WQKvUlCd7ywAV4s50AalFLukgk4iXk6ly09u67UAa4QOiaMdSmQkbQ9oJE5fmEMzANe/HJB4Pl/BDkTqg+A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZLuRQUgfGdBflyqEaDs9Jkt2i6psVdRmX5pDNuT531I=;
 b=cxPW7hNIzQWp61yyPgS+QOAFcmvXeBMzV0lx0jnZqC9B9aECXGYu4zEYBjx2AYIboNtrdP8K5O+KSuvPKH7ck8YQwtEyB8yaS7kDauz1RgCNKxIHWPBXbbL7WEUlXPpjUezzs9sBE8fGHopic+HTVDUb9tmOjrUOR/U14/Zm3NZACkSGgqqMATEUlqns/hSNYECM12ahhXbXXVRMefn6Ix6Y74iyBY/f+uNwuPRnFtbtMCWHUM6a7U+JCHXiYzfYYcezULgSDWMfx4R4YYoYW00Bgb+2JCKrO2g8g1iW0+kP73YPte+ODO3m45EYNPp9lK7kd833d0EBHRkAll12/Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ZLuRQUgfGdBflyqEaDs9Jkt2i6psVdRmX5pDNuT531I=;
 b=R+qyDO4DMxVe9qImuv5hOfpyBUf0afNtsZgX/2fHdeir6GUTLyF2fdLKKxGapMmQcj0Q2V/Ni67jGNqEbStxcg1qRe3bDSjRtsqhqGFY3JTLzYZvb/RMwyfJ8zC3iGVesvyEaJioIZIAkoace+zHlg+AL+OStgQZYytYzvus4SY=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4365.namprd12.prod.outlook.com (2603:10b6:806:96::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.17; Tue, 8 Dec
 2020 22:04:06 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3632.021; Tue, 8 Dec 2020
 22:04:06 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, srutherford@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v9 01/18] KVM: SVM: Add KVM_SEV SEND_START command
Date: Tue,  8 Dec 2020 22:03:56 +0000
Message-Id: 
 <813ea518ab74252cd66565fe87975dcbdf15b3f3.1607460588.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1607460588.git.ashish.kalra@amd.com>
References: <cover.1607460588.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0701CA0032.namprd07.prod.outlook.com
 (2603:10b6:803:2d::12) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN4PR0701CA0032.namprd07.prod.outlook.com (2603:10b6:803:2d::12) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.18 via Frontend
 Transport; Tue, 8 Dec 2020 22:04:06 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 2913bee2-3362-4061-3f18-08d89bc52ecb
X-MS-TrafficTypeDiagnostic: SA0PR12MB4365:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB436597735CE2308EE596EDC48ECD0@SA0PR12MB4365.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 G2wbGfz9diPPGiNnQzER8Pwf/Y+o1owrQb9uvU2xjEZwdIUPeXsTHlA7hqGEnjK8BCttonq3qosA1Ef88RIK6lghCyV4ZzgDPpn5ZD5LVgwe6WG6+CjRc6Evqa8pJA4A85dNV0kA0pZyFUBkfpy5pl3E+EoW7oyB1Fa3m0B96AlbjASlf/L+Rb44gPqn2Dk5SBKWxb0pXOmsc2guI4plx/yzzF+c1lMFXJ4PdWOY+/yXb5QccAxuz7PIH7/KhhVv8xMrRYi8V21Q4OLOdMvWu8WVmHcWrYz+KYxmftqA2LvgA1x1xDnZNcehPSvLH9u0x/ehuzIfmVxnWkPEjHehOBD5UDYJ+5OwPGanVl9hNlsKz5DeckWdl27cLTacWevD
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(346002)(366004)(136003)(7696005)(508600001)(6666004)(66476007)(66574015)(66556008)(4326008)(66946007)(52116002)(5660300002)(186003)(2906002)(6916009)(34490700003)(86362001)(2616005)(16526019)(26005)(956004)(7416002)(8936002)(36756003)(6486002)(8676002)(83380400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?iZJtTQSJsj6vmi8Ly65phmjVwoewg/?=
	=?utf-8?q?ufyY++IPtIX20TCD+zZuRE/Ymz5BzaZoAy8zXHdTLJC4t7vNiOcGjI2bbtXXNcd03?=
	=?utf-8?q?qK0vJUqpAbjlDUv2OysnqKzfVgNdHZpBKSxgCALPtGKjEXZ2O5mCxPgv/mz7wGLkd?=
	=?utf-8?q?YHxY2VetkHF6UpvhBXvuNXBOavLZk/ptkiyrfLAddCL0jLXT0YrlXVdsgCE3xWTC4?=
	=?utf-8?q?iQInZZWK2M7QEDVP0AHonL14nbP9cmQCr9eiVJGOiVbSl3eO3530gdciE19ZXZhsU?=
	=?utf-8?q?q3YoXduECL00gGq7IbXjIeikJOo/NNQ8sZRXrQGincvAm9qCpathu2wUJw9kzpOSR?=
	=?utf-8?q?0TDd/X2fwVuAz+MzEthDlUeQWCzlV9U8xMhPLQkrNXDXFhlLVWxF6ojrgXoWg21NE?=
	=?utf-8?q?1g9Xh3M1l7ZVqVLKuwEevfDUuxbyIGo30EEkuBjp0SrJmzu06k1qSc/0uHecX9QjG?=
	=?utf-8?q?UAwT7MnHSEkC8Mleb+w/apIe8Wi5byuAiVw45TjaYdGl/r0jHHV2nlIIbspocpddJ?=
	=?utf-8?q?vwhbgpGWHhtjQCfdtyGF8C9oA33IhOzsC4AbYEO9CLGnt1FEhjYDzO3koWUZCUssj?=
	=?utf-8?q?yHDgw7I6R09XrveNmFPeCSrO4F7Vuy3WHgYNunE/m+roLU4JzmO5WG76vag/nJVd9?=
	=?utf-8?q?7fchSXByVACQrpN06iordgmv4M17cck6HfOlqk94gNNIIZn+vnQLFgNWE4rEFXjiO?=
	=?utf-8?q?FyrowKcQhqcKpweLLqiKC9/xBb0UUoG/LQtgVWZn2rmJv9DyfZ913SSqHvfevlb/u?=
	=?utf-8?q?IfgLV34NCYGY/2mq/W39b+MV3ciPZtTOP53AgUkBcI9+UaRWWq278ubH/xUZsTEGF?=
	=?utf-8?q?kUhfD9Jdq/LqkhdN9OTC3CP6X5GHCDipk99CbqnXYOYN9CoNoulz22SexTWUbK/rv?=
	=?utf-8?q?PYW5Llc4T8uB2n6wfo2hTqkcl3TA36+ZLaUr7Wwxqzj6uWL2CemimgwvMF9WAgOJA?=
	=?utf-8?q?wamzwSGGnaFMaXQtajz?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 Dec 2020 22:04:06.8060
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2913bee2-3362-4061-3f18-08d89bc52ecb
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Qd9W1NL/hw4a+lvKRLP9u2f9ABFs0cBedMHRaVZzATDS+dVhzPYWhtcMi127WeABS38UBlqeSa7FX+iEVN0lZQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4365
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
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
#### [Patch v2 1/2] cgroup: SVM: Add Encryption ID controllerFrom: Vipin Sharma <vipinsh@google.com>
##### From: Vipin Sharma <vipinsh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 11959815
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id BED14C4167B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:37:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8496C23B5F
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:37:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730005AbgLHVgt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 16:36:49 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49698 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726114AbgLHVgt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Dec 2020 16:36:49 -0500
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0C367C0617A6
        for <kvm@vger.kernel.org>; Tue,  8 Dec 2020 13:36:08 -0800 (PST)
Received: by mail-qv1-xf49.google.com with SMTP id m3so15202875qvw.5
        for <kvm@vger.kernel.org>; Tue, 08 Dec 2020 13:36:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=XhF5Hcc6koONhkWDQpHUqS395Llh4/sgpQP6VulQGUU=;
        b=Oam+VD+MNzs23sqT4/pWUG4RPE8321OvwxZHYq3AWTzjmcqI3tFstcSk3DaXMQzy8G
         VNTkZeXwWVpiidvPLQfACUOtNqF/9hMCfiOIV+HJLbLe9wjuVQujD/bfCZiXPCqeIF0w
         HZOE4CfMecoPpZ/b9NHxJ2aUlGlzV5bSlde4m+OGbn4O4BLQlquc8kpQTKdtCnxskX94
         KLIhKFhY3Qq/IlmkyyN4vqSzAVqAdvRjnW9XwFc5YoZYBW4ai7EnQWqIQBGG83kGZljs
         K7uXi1636ZmnCoTQ8FOizhpq/xH/ZewsmbTtqBJcjAO/Hrjy6A/pNHuq7WinaJwydRiz
         E3nw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XhF5Hcc6koONhkWDQpHUqS395Llh4/sgpQP6VulQGUU=;
        b=qwATaiMzyQIaUVTIlhORYglLZeSF2g3oY6oC0SDNVaFUQaIHuX0wdXbtJpF21rYIbv
         +bc6BY6E/Ug9FugPoh+dZsxs9FhbeQ0L2M8vyHVxezs61ZbfBeMpoRuR4fyBkJzXOE/C
         ewd4CNb1KjWbA2mH3u82cypvfciQdDtP6Nr8wBbcmloDyR/yOB6zwNqAzDIRR925Tn7D
         WUT/Eb3xltL7a5muNu/CwBwv3jxfOmT1tCd9RVOMVzQ2KjNv8BoJlEaoKw1ivVLodKDA
         KkbKdTLu8kguKVmFcXcbe9l+98rIrYAeA+7x3b+PVSNLaSxUNXQ64UaZZW1Sd6gLp8Uq
         jPuw==
X-Gm-Message-State: AOAM531OZRCfAXJweFfihxkFcRN5EQTuQTPuie3kzvXD/90PsLRWh/DA
        QzZAQOJUFamjRxIZSGGTOwLDlPp6qZEi
X-Google-Smtp-Source: 
 ABdhPJyIc4GgpUbmNcKmbE0TWlCzpJelQZRXkSG8BXyvghiZAkOqJx94UdyCbSNX+ZDDwnGOZvXpkqLzE5Ov
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:ad4:5192:: with SMTP id
 b18mr3638093qvp.46.1607463366983; Tue, 08 Dec 2020 13:36:06 -0800 (PST)
Date: Tue,  8 Dec 2020 13:35:30 -0800
In-Reply-To: <20201208213531.2626955-1-vipinsh@google.com>
Message-Id: <20201208213531.2626955-2-vipinsh@google.com>
Mime-Version: 1.0
References: <20201208213531.2626955-1-vipinsh@google.com>
X-Mailer: git-send-email 2.29.2.576.ga3fc446d84-goog
Subject: [Patch v2 1/2] cgroup: SVM: Add Encryption ID controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hardware memory encryption is available on multiple generic CPUs. For
example AMD has Secure Encrypted Virtualization (SEV) and SEV -
Encrypted State (SEV-ES).

These memory encryptions are useful in creating encrypted virtual
machines (VMs) and user space programs.

There are limited number of encryption IDs that can be used
simultaneously on a machine for encryption. This generates a need for
the system admin to track, limit, allocate resources, and optimally
schedule VMs and user workloads in the cloud infrastructure. Some
malicious programs can exhaust all of these resources on a host causing
starvation of other workloads.

Encryption ID controller allows control of these resources using
Cgroups.

Controller is enabled by CGROUP_ENCRYPTION_IDS config option.
Encryption controller provide 3 interface files for each encryption ID
type. For example, in SEV:

1. encryption_ids.sev.stat
	Shown only at the root cgroup. Displays total SEV IDs available
	on the platform and current usage count.
2. encrpytion_ids.sev.max
	Sets the maximum usage of SEV IDs in the cgroup.
3. encryption_ids.sev.current
	Current usage of SEV IDs in the cgroup and its children.

Other ID types can be easily added in the controller in the same way.

Signed-off-by: Vipin Sharma <vipinsh@google.com>
Reviewed-by: David Rientjes <rientjes@google.com>
Reviewed-by: Dionna Glaze <dionnaglaze@google.com>
---
 arch/x86/kvm/svm/sev.c                |  28 +-
 include/linux/cgroup_subsys.h         |   4 +
 include/linux/encryption_ids_cgroup.h |  70 +++++
 include/linux/kvm_host.h              |   4 +
 init/Kconfig                          |  14 +
 kernel/cgroup/Makefile                |   1 +
 kernel/cgroup/encryption_ids.c        | 430 ++++++++++++++++++++++++++
 7 files changed, 544 insertions(+), 7 deletions(-)
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c

```
#### [PATCH 1/2] Enumerate AVX512 FP16 CPUID feature flag
##### From: Kyung Min Park <kyung.min.park@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kyung Min Park <kyung.min.park@intel.com>
X-Patchwork-Id: 11957483
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D3E39C4167B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 03:56:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B5E923A5F
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 03:56:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726903AbgLHD4a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 22:56:30 -0500
Received: from mga14.intel.com ([192.55.52.115]:59706 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726556AbgLHD4a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 22:56:30 -0500
IronPort-SDR: 
 4bap6LJ9XyrO89KUGzw447xJzLX16Qtg8D16T+ztHbArfNdwWKIKUVPhgHz2lTWiXKTNA2HjSF
 Y6uovgLArv+Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9828"; a="173060180"
X-IronPort-AV: E=Sophos;i="5.78,401,1599548400";
   d="scan'208";a="173060180"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Dec 2020 19:55:35 -0800
IronPort-SDR: 
 nvu23G2qECChJTtgThqTte/uySMynDEZAW3ErrvTP74P9lLCwnVcbuKlTKjyTAxbe68EorHFUQ
 s5xHgsHIFkFg==
X-IronPort-AV: E=Sophos;i="5.78,401,1599548400";
   d="scan'208";a="363469717"
Received: from km-skylake-client-platform.sc.intel.com ([10.3.52.146])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Dec 2020 19:55:34 -0800
From: Kyung Min Park <kyung.min.park@intel.com>
To: x86@kernel.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com, joro@8bytes.org, vkuznets@redhat.com,
        wanpengli@tencent.com, kyung.min.park@intel.com,
        cathy.zhang@intel.com
Subject: [PATCH 1/2] Enumerate AVX512 FP16 CPUID feature flag
Date: Mon,  7 Dec 2020 19:34:40 -0800
Message-Id: <20201208033441.28207-2-kyung.min.park@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201208033441.28207-1-kyung.min.park@intel.com>
References: <20201208033441.28207-1-kyung.min.park@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Enumerate AVX512 Half-precision floating point (FP16) CPUID feature
flag. Compared with using FP32, using FP16 cut the number of bits
required for storage in half, reducing the exponent from 8 bits to 5,
and the mantissa from 23 bits to 10. Using FP16 also enables developers
to train and run inference on deep learning models fast when all
precision or magnitude (FP32) is not needed.

A processor supports AVX512 FP16 if CPUID.(EAX=7,ECX=0):EDX[bit 23]
is present. The AVX512 FP16 requires AVX512BW feature be implemented
since the instructions for manipulating 32bit masks are associated with
AVX512BW.

The only in-kernel usage of this is kvm passthrough. The CPU feature
flag is shown as "avx512_fp16" in /proc/cpuinfo.

Signed-off-by: Kyung Min Park <kyung.min.park@intel.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Reviewed-by: Tony Luck <tony.luck@intel.com>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/cpuid-deps.c   | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH] KVM: Documentation: Update description of KVM_{GET,CLEAR}_DIRTY_LOG
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11957553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBF58C193FE
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 04:36:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 732E123A5E
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 04:36:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726141AbgLHEfw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 23:35:52 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:9393 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726028AbgLHEfv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 23:35:51 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4CqnQP2rH8z7BGD;
        Tue,  8 Dec 2020 12:34:37 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.179) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Tue, 8 Dec 2020 12:34:59 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <pbonzini@redhat.com>, <kvm@vger.kernel.org>
CC: <corbet@lwn.net>, <wanghaibin.wang@huawei.com>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH] KVM: Documentation: Update description of
 KVM_{GET,CLEAR}_DIRTY_LOG
Date: Tue, 8 Dec 2020 12:34:39 +0800
Message-ID: <20201208043439.895-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.179]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update various words, including the wrong parameter name and the vague
description of the usage of "slot" field.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 Documentation/virt/kvm/api.rst | 16 +++++++---------
 1 file changed, 7 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] s390x: Move to GPL 2 and SPDX license identifiers
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11958773
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CC13EC4167B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 15:09:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AAA623A75
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 15:09:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729972AbgLHPJ5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 10:09:57 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:62130 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729726AbgLHPJ4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Dec 2020 10:09:56 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8EwqgK066202;
        Tue, 8 Dec 2020 10:09:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=p/t4f5senrkSw1O+e/bV0NyWu+aCZNsR9XNRRFTRXlg=;
 b=qrBlDIn6eK3fjKxV4Aum3Tq4U0HGI1ypuQTqQZ/a7dRigDunQPNigUu/Zq/99V+aALNx
 BSxdYM0biFLWe4QTASht43ZlaBRAmRhIl9zrNsgSa14HEFx28IS4aEgV62ibbF/Svzno
 axCB6INFfHe8+KsxzYKryuzDHSbAus9U+nV3RjoK87z8WsHcHLw7Rh167FO2bwaSV5wD
 8DRtWwb3sqoc+22BXLTNUlaOWvwh3uWMnWiA+orDepd9EfmQ0L6PNB1OUPE0Z0LECpJE
 udwdL16X8S2OpiTEN43Ny/dFpCPT7Ej2hTpdGUrVU5Wp2jpgw8SK6z5gm7DbHGugY9Jy kg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35aany2rvp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 10:09:14 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B8ExFu6068511;
        Tue, 8 Dec 2020 10:09:14 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35aany2rut-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 10:09:13 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8F9CqS018349;
        Tue, 8 Dec 2020 15:09:12 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06fra.de.ibm.com with ESMTP id 3581fhhvu6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 15:09:12 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B8F99T033358300
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 8 Dec 2020 15:09:09 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8F46FAE055;
        Tue,  8 Dec 2020 15:09:09 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F0FFDAE058;
        Tue,  8 Dec 2020 15:09:08 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  8 Dec 2020 15:09:08 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 1/2] s390x: Move to GPL 2 and SPDX license
 identifiers
Date: Tue,  8 Dec 2020 10:09:01 -0500
Message-Id: <20201208150902.32383-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201208150902.32383-1-frankja@linux.ibm.com>
References: <20201208150902.32383-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-08_09:2020-12-08,2020-12-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=1 phishscore=0 mlxlogscore=999 spamscore=0 mlxscore=0
 priorityscore=1501 clxscore=1015 bulkscore=0 impostorscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012080086
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the past we had some issues when developers wanted to use code
snippets or constants from the kernel in a test or in the library. To
remedy that the s390x maintainers decided to move all files to GPL
2 (if possible).

At the same time let's move to SPDX identifiers as they are much nicer
to read.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/cmm.c       | 4 +---
 s390x/cpumodel.c  | 4 +---
 s390x/css.c       | 4 +---
 s390x/cstart64.S  | 4 +---
 s390x/diag10.c    | 4 +---
 s390x/diag288.c   | 4 +---
 s390x/diag308.c   | 5 +----
 s390x/emulator.c  | 4 +---
 s390x/gs.c        | 4 +---
 s390x/iep.c       | 4 +---
 s390x/intercept.c | 4 +---
 s390x/pfmf.c      | 4 +---
 s390x/sclp.c      | 4 +---
 s390x/selftest.c  | 4 +---
 s390x/skey.c      | 4 +---
 s390x/skrf.c      | 4 +---
 s390x/smp.c       | 4 +---
 s390x/sthyi.c     | 4 +---
 s390x/sthyi.h     | 4 +---
 s390x/stsi.c      | 4 +---
 s390x/uv-guest.c  | 4 +---
 s390x/vector.c    | 4 +---
 22 files changed, 22 insertions(+), 67 deletions(-)

```
#### [PATCH 01/17] target/mips: Introduce ase_msa_available() helper
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11957257
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B7B51C4361B
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 00:37:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F9E8238EB
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 00:37:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728712AbgLHAhw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 7 Dec 2020 19:37:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50408 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728689AbgLHAhw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Dec 2020 19:37:52 -0500
Received: from mail-ej1-x644.google.com (mail-ej1-x644.google.com
 [IPv6:2a00:1450:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9CD71C0617B0
        for <kvm@vger.kernel.org>; Mon,  7 Dec 2020 16:37:11 -0800 (PST)
Received: by mail-ej1-x644.google.com with SMTP id ga15so22187456ejb.4
        for <kvm@vger.kernel.org>; Mon, 07 Dec 2020 16:37:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=3nQ2rq5dw00RN3ISHz847HNPzVTdJvTY+D4+K8lpZUM=;
        b=O6uCHU2nt9XOgHKby483Y1sNEgW9zJgaE8hSa8WQWYgH66G6t7hlJbK2MH5lk+LFwN
         o1Qlnt2501GAvmbCTl7B9MwtCzBVK2TpKTFypwDbmjxFe/y30J0jJ28WlsC8JaQSZIxH
         ocj81ieDaVgREldsWZrOdhUoAA+9W2hnZIHaaMSPktKI0OA9S+CI3vSEmfkGucYVgYJZ
         eA2PV7Cn4wmwQKMIcKsdsIlIf1s0wkcGBZFrBKkbNITyizVDfx5rGyGy/4HMycsqtXsi
         lobwTUTDvEGqNjiePtcpkVKjn2hHm7v18PMFCV3r6PwO9oEDKyKPshn/QIGF5RyjO2Dt
         izow==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=3nQ2rq5dw00RN3ISHz847HNPzVTdJvTY+D4+K8lpZUM=;
        b=P7RFETfuaRh83EpAc6Ewlj/Ret+opTXSs64TRDX9PQR7GF2EYnKKcned6o1CrO99zH
         QhPc/5FymJPspA8tCpLgtslo0+r7Mn86aI2cyR0umDDNYjfdbHJXtjZtf322yec+2XmT
         Sna1dQckgrxn3ugqyN8xzmdCS4aw+G0NbWCosUC0naN6aFotF7ldlnMuxBfGr+VK78Yd
         htN5h35ZpSTp4ycm/df8uSq3pNTtaFb9i4ozUTEWFN/v1L1kce0Sdmx0eVNhGQS0BQPV
         XwxUO0rtLwQaEH8kUgmnUY3a32j1xDaix5Rgq5VDokeoXaIOOy8A6RIJLnnuBF6dTh1C
         fJww==
X-Gm-Message-State: AOAM5300gFy+0HFwF1UE4PN+yHSpSaqkhpqZ+iK9d9vbRYXduUpdi1nV
        2TYtVz5VQkD6DB62A7i0cLM=
X-Google-Smtp-Source: 
 ABdhPJxMESd4QPMEdVDiXLWmRmAHveLm75pKdNMT0gidZNPbzqokGnxte7sQEw5ftElnbdGNm96S1Q==
X-Received: by 2002:a17:906:a106:: with SMTP id
 t6mr21575903ejy.63.1607387830419;
        Mon, 07 Dec 2020 16:37:10 -0800 (PST)
Received: from x1w.redhat.com (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 x15sm15114272edj.91.2020.12.07.16.37.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Dec 2020 16:37:09 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>,
 kvm@vger.kernel.org, Richard Henderson <richard.henderson@linaro.org>,
 Aurelien Jarno <aurelien@aurel32.net>, Huacai Chen <chenhuacai@kernel.org>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH 01/17] target/mips: Introduce ase_msa_available() helper
Date: Tue,  8 Dec 2020 01:36:46 +0100
Message-Id: <20201208003702.4088927-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201208003702.4088927-1-f4bug@amsat.org>
References: <20201208003702.4088927-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of accessing CP0_Config3 directly and checking
the 'MSA Present' bit, introduce an explicit helper,
making the code easier to read.

Reviewed-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 target/mips/cpu.h       |  6 ++++++
 target/mips/kvm.c       | 12 ++++++------
 target/mips/translate.c |  8 +++-----
 3 files changed, 15 insertions(+), 11 deletions(-)

```
#### [PATCH] tools/kvm_stat: Exempt time-based counters
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11959761
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60973C433FE
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:12:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D6D023B1A
	for <kvm@archiver.kernel.org>; Tue,  8 Dec 2020 21:12:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728495AbgLHVL7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 8 Dec 2020 16:11:59 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28562 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726222AbgLHVL7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Dec 2020 16:11:59 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8L3YvX124516
        for <kvm@vger.kernel.org>; Tue, 8 Dec 2020 16:11:17 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=NUKTl7y3bzATptUYlxKPLeunh5t4ViwNFw7VQPU2MUg=;
 b=NWiMM7J6+OXuyg0WfY+fIkH1V3M/MIodNybKzWmbQyclVmS/E/yAEnenONU30WNbJkc+
 UYER2ak0aDV+768bT4LvC0YpjmGZaSBcC9yksYzfvIMV5Nt3o3KmjisJxD3JSorDjtD0
 sZvxHM3T12ZpJQIYcujfc+ftMnzVkYQlmyIKv0DASkitpeZUzGwUkdToncU0HYKRp+ZL
 x+eon6i/an/o22lVCX1HidjUE56wvAs9Yr7QlOfXSsdCubLvwRylnti12hJZkSJ8ltic
 tVo9yk0b1YqAbcG4NVYAYDIlyK5csQxQwjTOXZY8jmBSdxLxImfGdxze7XGyNBU2ijmO Mg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359s0s9uxa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 08 Dec 2020 16:11:17 -0500
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B8L5Ix5139378
        for <kvm@vger.kernel.org>; Tue, 8 Dec 2020 16:11:17 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 359s0s9uwh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 16:11:17 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B8L86Z4007820;
        Tue, 8 Dec 2020 21:11:15 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03fra.de.ibm.com with ESMTP id 3581u8nt3u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 08 Dec 2020 21:11:15 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B8L8gZ752625740
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 8 Dec 2020 21:08:42 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6225A405F;
        Tue,  8 Dec 2020 21:08:42 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9030BA4054;
        Tue,  8 Dec 2020 21:08:42 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  8 Dec 2020 21:08:42 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, pbonzini@redhat.com
Subject: [PATCH] tools/kvm_stat: Exempt time-based counters
Date: Tue,  8 Dec 2020 22:08:29 +0100
Message-Id: <20201208210829.101324-1-raspl@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-08_15:2020-12-08,2020-12-08 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 adultscore=0 clxscore=1011 mlxlogscore=940 lowpriorityscore=0
 suspectscore=1 spamscore=0 malwarescore=0 bulkscore=0 mlxscore=0
 phishscore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2012080126
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Stefan Raspl <raspl@de.ibm.com>

The new counters halt_poll_success_ns and halt_poll_fail_ns do not count
events. Instead they provide a time, and mess up our statistics. Therefore,
we should exclude them.
Removal is currently implemented with an exempt list. If more counters like
these appear, we can think about a more general rule like excluding all
fields name "*_ns", in case that's a standing convention.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
Tested-and-reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
