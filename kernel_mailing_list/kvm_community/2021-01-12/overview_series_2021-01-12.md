#### [PATCH 1/2] KVM: x86: Add emulation support for #GP triggered by VM instructions
##### From: Wei Huang <wei.huang2@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wei Huang <wei.huang2@amd.com>
X-Patchwork-Id: 12012485
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7083DC433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 06:38:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 05CED22AED
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 06:38:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733100AbhALGiH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 01:38:07 -0500
Received: from mail-bn8nam11on2050.outbound.protection.outlook.com
 ([40.107.236.50]:12071
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728761AbhALGiH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 01:38:07 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Gtwyt3WxZv6DkbBP7eE6vHy8RFu2v/cjtTo2l0fzP5fm44ZOQeRvl//TeOpEAIq5ZKDXcUNumDC63LHetoI/mqE/YysQ0sDyiuj4a6cLqbqpr4lUmS2f/RlSeaHNuNoEoERAfzU5FRAjy+yT/K8DK0fr03IYQYy/dJ7Q8hj0tVGwLRbXtE4sG/f0TJeWarAEcUra46BUCiJbPkxcyA3coB8NZeRcdJeg08IdLOLtmSDlrldk5ULcodeLLw2Cp9mYa3YpKM7jHsF9RFlmsGN5InZFKDbro2zSvCR46ZII859nxSzVV5Hz2Vd8aSbYOo4gAeIx0/vUIaTWaiDG9REdhA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YjM7bSN4PJGzswNu/kwmMEOxGXsI+pfEm/aZqFjgsXw=;
 b=KB2ipRP6/YOq02rkhoEXpnRXW0txT8V8Ru+IHEYy5ezDR2EsJWQoBecXcKrjvwb4YQjpznU+WPTV6W4CK9kyV9wUze4OLxY5FlJ2Vj/MyWh0k2HaW+kY2OpqPH8LiO59YPwuTSClbezyO4QZBqowzjBeJBW6TWmxD0ehtZzP97HPnoMfwt4ckxwVagcu4BkEqb7CYi3JmUEEZZT4cNZSCa22xJ/ylrtb/cczkHnJjgJUfdKWhRz+XPyj6OCs8q2IO2wD70e/lJ47oYMmPWhzTlQJi+Woj6RysgcV85axCZMwEaCDYtH0gITib1046H8VjZhQXn8x8M9nSYXuQUum7g==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YjM7bSN4PJGzswNu/kwmMEOxGXsI+pfEm/aZqFjgsXw=;
 b=zS3u6+Ud/07OKSRZO0PJw1/F1W6Y8BjFJ1oo8NqhkUNONN2LRgAFiSkcsoq4BMR4goyc5nl1GVvYmkAN888v4Strwbc4+OZwQGsE2rVkk4zH1pt6HbTGCAhZQv0LkzxwmVsbhjXMb8bM0UhBcVKxW2hluT+8bzJgloZ4jOC3ojY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from MWHPR12MB1502.namprd12.prod.outlook.com (2603:10b6:301:10::20)
 by MW2PR12MB2409.namprd12.prod.outlook.com (2603:10b6:907:9::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3742.6; Tue, 12 Jan
 2021 06:37:13 +0000
Received: from MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::4d9d:16b8:3399:ce90]) by MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::4d9d:16b8:3399:ce90%5]) with mapi id 15.20.3742.012; Tue, 12 Jan 2021
 06:37:13 +0000
From: Wei Huang <wei.huang2@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        vkuznets@redhat.com, seanjc@google.com, joro@8bytes.org,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, x86@kernel.org,
        jmattson@google.com, wanpengli@tencent.com, bsd@redhat.com,
        dgilbert@redhat.com, wei.huang2@amd.com, mlevitsk@redhat.com
Subject: [PATCH 1/2] KVM: x86: Add emulation support for #GP triggered by VM
 instructions
Date: Tue, 12 Jan 2021 00:37:02 -0600
Message-Id: <20210112063703.539893-1-wei.huang2@amd.com>
X-Mailer: git-send-email 2.29.2
X-Originating-IP: [70.113.46.183]
X-ClientProxiedBy: SN6PR05CA0007.namprd05.prod.outlook.com
 (2603:10b6:805:de::20) To MWHPR12MB1502.namprd12.prod.outlook.com
 (2603:10b6:301:10::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from weilaptop.redhat.com (70.113.46.183) by
 SN6PR05CA0007.namprd05.prod.outlook.com (2603:10b6:805:de::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.2 via Frontend
 Transport; Tue, 12 Jan 2021 06:37:11 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 3b7ecfb6-90e7-4e52-22a4-08d8b6c47f06
X-MS-TrafficTypeDiagnostic: MW2PR12MB2409:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MW2PR12MB2409E0E41C5FB8126A35620BCFAA0@MW2PR12MB2409.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:2803;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 SKjhv7EqMhSRAA2mEC8IjxSoSkcZaLUZh+DT7jfTI2Pk1S1P1eJ5naAuoGg0eXEjswbutYPn2uBm1BQxJPLAvggYptkmKsblxjdIOeQBAG1VANtwy6B7q/J4zI4qTgLUKvFtzxmZxZk/lhzNupQGXrXWfU0Pu5jZapCk/RCZ9U47wWjFFMDxiyFySTKLsJ6vMGseWmrXY9+RC3la33oNQX/TVd5Atp7c5FquLJcPsEL1M0p+azRaKAd+c9qBiLT39taxtejfmyu+jZzH0kN8yqHfEyehkZ+wi/MiolBDT9E2bZkbCX0z1CoBJ1EQTyjtZjQrbElpkitibC0T2AwercISGmNF0PT6h739bSECLcJxLKphQ6XY92Q7WGLx4IELgxa1SVfphMYdhgJ0nOlX0A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR12MB1502.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(136003)(376002)(366004)(396003)(39860400002)(86362001)(30864003)(6486002)(1076003)(16526019)(478600001)(6666004)(6512007)(52116002)(2906002)(956004)(2616005)(7416002)(316002)(83380400001)(8676002)(66476007)(66556008)(6506007)(4326008)(6916009)(8936002)(36756003)(186003)(26005)(5660300002)(66946007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 n4HOSI/J/mCBQyWY/8BT4lDUwoAzgNnF4py6R+vw1UowglDyx9ajZHm+ZkQCdJNftkCR0GDxP1dA1B7CUXRC41HEhrEXJJgv1TKkMa0FzhMU7mGHCsaQ54tMBEfuw4JS2U9+uqqYWcLwr2eBLkGuE3hnslRt6JEq1YfVMJrbRtomPSIAhvBS0mg5XpeB/eFQvg0/E1z3wUdfzFUNkE2ZL/CT7U4/Kn+5HDmmkHtgOJ9OBWNdusUxZ26ikxP6+Un/xm8/hhaMwUultfQ7z6Vioe+/GBUiv5u+yOxKq7E/IeFhF+yUpEVRKEGUIT+tJNYy6zJNrdlnBfbX6waptXoFvlz38iOk4PL8QI2IgKuFYn68/oIF0YGRMGcXZ/PNBsJe7NXlMN/yfWb7G96ZTYNk55qHggQrRiRP9NoO8c6/fXt4F/hwCCitYWKIh8OYrt8/xMugdk3rEg9/uBx/B6tbLFFVZ2aIPlsaBXG12FC2fk5IahgG04RFgXCc6ToSttKZbDd9eC1kSMQg0UdcwO5yD/E1yZesW1tV2xnyoxDpsdy2WyYKOX0LdcvWebKiiU4TJ9fz3pETeKltqL4R7BMEGg2ohNUVmINu9CAwlkiMxEAAk6MaM1anlx8Aq+QiDi7W81yifhMVMClGBBgbimSEysUcU6CFJQV0Fo53K54EwF/HsnprPpuXgMHQhUoA2pi5bNrVEognN7yd9YMDTrxfBPj8OQWn0bElOCkEOF2s1U0nJKA6R2mfJl2vBcTctaMOHJzkm4KTtDYbrss0XbVjNefXp4oAaGBGW1oPINGG6IwgGHU5SHDgZkU7Gl1URybYms/VgSZsEfKNfjuyx7EimuXRQ7IIcUa6UlwjLs8XScedNLf9KsiIh5X0/p4gUfeCAd/TjTJRtgamFbGkCVZW5fv09k851gSCPoRqLB1WdXfAngpsGr+PF+MT7z92PIqHeAlerjNGugaKaBUrX8MO0CYoHOqJxZQ3OqlP4jnnf8n5qo85mgmnPcVAH7UqwC/h
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: MWHPR12MB1502.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Jan 2021 06:37:13.2579
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 3b7ecfb6-90e7-4e52-22a4-08d8b6c47f06
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 jWYJLpuM+V72CXeRI9/v9P65sbx26HpRos8ALDOR8v/NywNatU2DFSVYc3k/nvNu
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MW2PR12MB2409
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bandan Das <bsd@redhat.com>

While running VM related instructions (VMRUN/VMSAVE/VMLOAD), some AMD
CPUs check EAX against reserved memory regions (e.g. SMM memory on host)
before checking VMCB's instruction intercept. If EAX falls into such
memory areas, #GP is triggered before VMEXIT. This causes problem under
nested virtualization. To solve this problem, KVM needs to trap #GP and
check the instructions triggering #GP. For VM execution instructions,
KVM emulates these instructions; otherwise it re-injects #GP back to
guest VMs.

Signed-off-by: Bandan Das <bsd@redhat.com>
Co-developed-by: Wei Huang <wei.huang2@amd.com>
Signed-off-by: Wei Huang <wei.huang2@amd.com>
---
 arch/x86/include/asm/kvm_host.h |   8 +-
 arch/x86/kvm/mmu.h              |   1 +
 arch/x86/kvm/mmu/mmu.c          |   7 ++
 arch/x86/kvm/svm/svm.c          | 157 +++++++++++++++++++-------------
 arch/x86/kvm/svm/svm.h          |   8 ++
 arch/x86/kvm/vmx/vmx.c          |   2 +-
 arch/x86/kvm/x86.c              |  37 +++++++-
 7 files changed, 146 insertions(+), 74 deletions(-)

```
#### [PATCH 01/24] locking/rwlocks: Add contention detection for rwlocksFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12014293
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 49507C433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 18:11:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0382722DFA
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 18:11:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390897AbhALSL3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 13:11:29 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56666 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728965AbhALSL2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 13:11:28 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 301E7C061795
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 10:10:48 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id a206so3309450ybg.0
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 10:10:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=AT/HhadsSLkfqA9qLz1yJR5FuwQcmEn0C1RS62FkcL4=;
        b=J6taq1Sz6FYVlN36xTqjFZYm8ABILYWAdx6QW+/38pCGCrYz20tUALul8pbOd9n36p
         LAOV3mpAkpmjGyhiZig7aW8hNRawkHmK78ZQxEatXnkFkA59sK1ah8WRiI+dJ3P8va9y
         LqRm6XmejkwIBKKJGlgFOAmnk1DqT/Dj73QmwBhl+XP0LiVRNBMs2pIX1hkhhi0Dxrpi
         pY2hscWTsqiGjTw41xoT9pvLdA1r5hw8EgvHsr+CMiwA6qo1Z4hUivfPMtFF0qHyoUp3
         tg+bdoqELmVaGx5N3TAgK7yTtBpTAd1SR1NMYn4jglYeSZtGRZ3ZkPTSMsGIzYdEUYK1
         PnuQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=AT/HhadsSLkfqA9qLz1yJR5FuwQcmEn0C1RS62FkcL4=;
        b=O2bx6RLNsuX6AwavRozUc4bycSqUUmLTXkFpq8NgBRB01Exqp6YLMlqGDpSXS53TDw
         DWRA/wH8Y0PTqYzIsdMt47xpV7uM4LC2G2+3glmHcc9108pR+FoLRuyOZGpRA58Kp4jo
         rdhIB/C2E/Fcow4c1XAeCXZ85lR7CDjdpQc1NGSWb8C2PJgcE6Eb5hCOZeLGkPW1slpe
         +QcGm3fRhTGqw5npVSU+sqKGUQ6Ylcxm4kXw7HehZxe0ALv/J6l+g8K7hcXNAwyRFeLI
         j3xqV55jf8KWwterHjaGy4z7bHCyTrZKHEXQjNqzzKiHlXX7OhuJsC3GNe+RR9hRF+Mg
         nbFg==
X-Gm-Message-State: AOAM532I2ZGm5MRpuIPmFheyNCSlMNt/wRdWZ8fLChuegUAYRkan6mde
        L3BB1GiWRKbX2uLwN427B1FxTVzIbc4W
X-Google-Smtp-Source: 
 ABdhPJwMFpkINzZX1JNlNkc/5A26Ivvmi4jtVWoQuEvFqtIF5atE7j6vpif9VmeLtHE+4jKwza0j7nuxl9ua
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a25:b28f:: with SMTP id
 k15mr996789ybj.67.1610475047360; Tue, 12 Jan 2021 10:10:47 -0800 (PST)
Date: Tue, 12 Jan 2021 10:10:18 -0800
In-Reply-To: <20210112181041.356734-1-bgardon@google.com>
Message-Id: <20210112181041.356734-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210112181041.356734-1-bgardon@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 01/24] locking/rwlocks: Add contention detection for rwlocks
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>,
        Ingo Molnar <mingo@redhat.com>, Will Deacon <will@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Davidlohr Bueso <dbueso@suse.de>,
        Waiman Long <longman@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

rwlocks do not currently have any facility to detect contention
like spinlocks do. In order to allow users of rwlocks to better manage
latency, add contention detection for queued rwlocks.

CC: Ingo Molnar <mingo@redhat.com>
CC: Will Deacon <will@kernel.org>
Acked-by: Peter Zijlstra <peterz@infradead.org>
Acked-by: Davidlohr Bueso <dbueso@suse.de>
Acked-by: Waiman Long <longman@redhat.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 include/asm-generic/qrwlock.h | 24 ++++++++++++++++++------
 include/linux/rwlock.h        |  7 +++++++
 2 files changed, 25 insertions(+), 6 deletions(-)

```
#### [PATCH v6 01/13] qom: Allow optional sugar props
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12012361
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E27F8C433DB
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 04:45:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A10E82250E
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 04:45:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731655AbhALEpy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 23:45:54 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52478 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731549AbhALEpx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 11 Jan 2021 23:45:53 -0500
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 15BE6C061575
        for <kvm@vger.kernel.org>; Mon, 11 Jan 2021 20:45:13 -0800 (PST)
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DFJ0R0ngvz9sVt; Tue, 12 Jan 2021 15:45:11 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1610426711;
        bh=PMr7j5j8OSe0AP5kUuFMOJLePX4fph0iQtNNjr88kFA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=IyO4CMvILkilCi0JWCARsw9pWVnpQQHUiZQFsB2oGz2nfa8rsaoBYdcfFilGtKEiS
         eYDM5xU7NaUQIOBuGqKAGFkxqtIBYGEf7gxhi+Yme2qQ8lm/hl8fEhmklp5VN2NVOb
         jyGaQxNdDWqaE2qR6z/WB1l/4/qRbYdZ5mpjdBS0=
From: David Gibson <david@gibson.dropbear.id.au>
To: pasic@linux.ibm.com, brijesh.singh@amd.com, pair@us.ibm.com,
        dgilbert@redhat.com, qemu-devel@nongnu.org
Cc: andi.kleen@intel.com, qemu-ppc@nongnu.org,
 Paolo Bonzini <pbonzini@redhat.com>, Marcelo Tosatti <mtosatti@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, Greg Kurz <groug@kaod.org>,
 frankja@linux.ibm.com, thuth@redhat.com,
 Christian Borntraeger <borntraeger@de.ibm.com>, mdroth@linux.vnet.ibm.com,
 richard.henderson@linaro.org, kvm@vger.kernel.org, =?utf-8?q?Daniel_P=2E_Be?=
	=?utf-8?q?rrang=C3=A9?= <berrange@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Eduardo Habkost <ehabkost@redhat.com>, david@redhat.com,
 Cornelia Huck <cohuck@redhat.com>, mst@redhat.com, qemu-s390x@nongnu.org,
 pragyansri.pathi@intel.com, jun.nakajima@intel.com, =?utf-8?q?Philippe_Math?=
	=?utf-8?q?ieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v6 01/13] qom: Allow optional sugar props
Date: Tue, 12 Jan 2021 15:44:56 +1100
Message-Id: <20210112044508.427338-2-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210112044508.427338-1-david@gibson.dropbear.id.au>
References: <20210112044508.427338-1-david@gibson.dropbear.id.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Greg Kurz <groug@kaod.org>

Global properties have an @optional field, which allows to apply a given
property to a given type even if one of its subclasses doesn't support
it. This is especially used in the compat code when dealing with the
"disable-modern" and "disable-legacy" properties and the "virtio-pci"
type.

Allow object_register_sugar_prop() to set this field as well.

Signed-off-by: Greg Kurz <groug@kaod.org>
Message-Id: <159738953558.377274.16617742952571083440.stgit@bahia.lan>
Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 include/qom/object.h |  3 ++-
 qom/object.c         |  4 +++-
 softmmu/rtc.c        |  3 ++-
 softmmu/vl.c         | 17 +++++++++++------
 4 files changed, 18 insertions(+), 9 deletions(-)

```
#### [PATCH] kvm: Fixes lack of KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 enabled check
##### From: Kunkun Jiang <jiangkunkun@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kunkun Jiang <jiangkunkun@huawei.com>
X-Patchwork-Id: 12012889
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F296C433DB
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 09:33:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 25ED722D58
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 09:33:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392594AbhALJcs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 04:32:48 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10651 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390802AbhALJcs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 04:32:48 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DFQLK10Nyz15rbR;
        Tue, 12 Jan 2021 17:31:05 +0800 (CST)
Received: from DESKTOP-6NKE0BC.china.huawei.com (10.174.185.210) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 12 Jan 2021 17:31:58 +0800
From: Kunkun Jiang <jiangkunkun@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH] kvm: Fixes lack of KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 enabled
 check
Date: Tue, 12 Jan 2021 17:29:42 +0800
Message-ID: <20210112092942.2310-1-jiangkunkun@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.210]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM_CLEAR_DIRTY_LOG ioctl lacks the check whether the capability
KVM_CAP_MANUAL_DIRTY_LOG_PROTECT is enabled or not. This may cause
some problems if userspace calls the KVM_CLEAR_DIRTY_LOG ioctl, but
dose't enable this capability. So we'd better to add it.

Fixes: 2a31b9db15353 ("kvm: introduce manual dirty log reprotect")
Signed-off-by: Kunkun Jiang <jiangkunkun@huawei.com>
---
 virt/kvm/kvm_main.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH 1/6] KVM: selftests: Rename timespec_diff_now to timespec_elapsed
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12014901
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F3B5C4332E
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 21:46:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4150F23122
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 21:46:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393373AbhALVoC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 16:44:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46388 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731073AbhALVn4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 16:43:56 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 97047C0617B1
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 13:42:59 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id 193so11508pfz.9
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 13:42:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=9gX0xmw3QVgb6vwQTxeDg6YDYooweR7Ig+LTagfAi6E=;
        b=X9i/NrVrFDmumiNEDo5X2Q0CFTpj8gaW5/lrMr/P1M1/haHq4CZrXUhJ+c7KDTtTUx
         kv1YYJugC02Trvh7WSITIA001Kd6/kRX3j2SeVQz2NWBfwrYBkJkk5pYvS5LXk1fItXG
         bGG//c6sr4c3VYyUUHaT0cTiRfTYTBOh+dOWOSGeSbOQE58YVZLGhonDYiwSl3KpyDhu
         NThAmqv+3gTAgtg/JLu1Yjk8lXb/4CscVR42NfN2P/VV/bHvJS9VdRf8RBbaaNwV0+ld
         Ih78W03wDL1lcu4t55/UPOyaTzliYVOEyJ4G//XXNi+HaeV5N+npTV3him7AP98mE8fh
         I3SA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=9gX0xmw3QVgb6vwQTxeDg6YDYooweR7Ig+LTagfAi6E=;
        b=k9NpKltv/eu41/3b8GR/uL7qZJbwxYYZQp8s1QFCkbfblaUdIAPyZ1IZ/JeqinTakG
         3enBfku1akT+ChO2si0KrcZCai2QayHf2YKyvngCflkR7OsNhdEikhAqiDSn+CuqUCUw
         ldLjQxcg1+qZd/sslJPFBDkdx1sRmDazR6JJgXl2ko8WfoExnzYyBk0NJY3XaA0K0OK5
         82rByhGwS+4g9vwxv92GDW+BwoXMtuk4RfxyJRB7RMqtca6XZx3nec5B0VgUtH+L0bR0
         aSVM7DRolC6QgmpJw9tcWcpr7xx8pFTls1aRpBExZ2VpDpxAJbBbPe28x4gblixQ5s0F
         mlrw==
X-Gm-Message-State: AOAM532hL7xcoXNG1e5edfOsTuFafismkkRVdCNmIOeIoJjFRPDFscXe
        QNkC+Nj/H0O5LsMzsqiPPAYyvbUIcUFr
X-Google-Smtp-Source: 
 ABdhPJy5NM8pW5xhHvPO3s1Twhqhl2icNpT6ZlCblCChXHHBpGF26Uw5k9GtfdCP8EGVXcYs5u4RbP0Pujti
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef4:a293])
 (user=bgardon job=sendgmr) by 2002:a62:7c01:0:b029:19e:1e23:1821 with SMTP id
 x1-20020a627c010000b029019e1e231821mr1131665pfc.72.1610487779107; Tue, 12 Jan
 2021 13:42:59 -0800 (PST)
Date: Tue, 12 Jan 2021 13:42:48 -0800
In-Reply-To: <20210112214253.463999-1-bgardon@google.com>
Message-Id: <20210112214253.463999-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210112214253.463999-1-bgardon@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH 1/6] KVM: selftests: Rename timespec_diff_now to
 timespec_elapsed
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Huth <thuth@redhat.com>, Jacob Xu <jacobhxu@google.com>,
        Makarand Sonare <makarandsonare@google.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In response to some earlier comments from Peter Xu, rename
timespec_diff_now to the much more sensible timespec_elapsed.

No functional change intended.

Reviewed-by: Jacob Xu <jacobhxu@google.com>
Reviewed-by: Makarand Sonare <makarandsonare@google.com>

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/demand_paging_test.c  |  8 ++++----
 tools/testing/selftests/kvm/dirty_log_perf_test.c | 14 +++++++-------
 tools/testing/selftests/kvm/include/test_util.h   |  2 +-
 tools/testing/selftests/kvm/lib/test_util.c       |  2 +-
 4 files changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH 1/2] KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12014063
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4AE8EC433DB
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 16:45:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0309B23107
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 16:45:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404959AbhALQop (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 11:44:45 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:53126 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2404845AbhALQop (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 11:44:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610469798;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=wGDTKeYzxrsl9FTH6Ik87RsmFf+MsbUCD0z98AUK1Cc=;
        b=QjwqV+iC3z/rfC0Lmpy6A8tbzU5lk9phFzRwLEGmenvCapIlHD5mR91y3kEJ0JYZw15/w5
        0b3nd7RbL5i94yOrTFlr3eJ4Ep0DhZ/VYbsGVowznjRLCT+dZnS9t7BGd7j8AuQkXnMI42
        Z3srQNybNZagLBlAWgTjoh0dTeYrbfM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-272-2ZHCZNHLPFWZzY70F-h-Jw-1; Tue, 12 Jan 2021 11:43:16 -0500
X-MC-Unique: 2ZHCZNHLPFWZzY70F-h-Jw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 13BEB18C89CF;
        Tue, 12 Jan 2021 16:43:15 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 75D5A5C1B4;
        Tue, 12 Jan 2021 16:43:14 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/2] KVM: nSVM: Track the physical cpu of the vmcb vmrun
 through the vmcb
Date: Tue, 12 Jan 2021 11:43:12 -0500
Message-Id: <20210112164313.4204-2-cavery@redhat.com>
In-Reply-To: <20210112164313.4204-1-cavery@redhat.com>
References: <20210112164313.4204-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch moves the physical cpu tracking from the vcpu
to the vmcb in svm_switch_vmcb. If either vmcb01 or vmcb02
change physical cpus from one vmrun to the next the vmcb's
previous cpu is preserved for comparison with the current
cpu and the vmcb is marked dirty if different. This prevents
the processor from using old cached data for a vmcb that may
have been updated on a prior run on a different processor.

It also moves the physical cpu check from svm_vcpu_load
to pre_svm_run as the check only needs to be done at run.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 28 ++++++++++++++++++++--------
 arch/x86/kvm/svm/svm.h |  1 +
 2 files changed, 21 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH v4 1/9] s390x: Add test_bit to library
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12013473
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 97939C433E6
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 13:22:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A67D22D58
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 13:22:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732775AbhALNV5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 08:21:57 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:57126 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729886AbhALNV4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 08:21:56 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10CDD7ws134359;
        Tue, 12 Jan 2021 08:21:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=2LJYac0SJdUeudi8lVHchq42sr3/3XaeFkP2reo3xbA=;
 b=XO7kxwQ3jmStR2sU3a3PshyDeM6APBMTGs5ES7x+oJ+7ft6gJTQGaYTNTg+7A7BgEssM
 oIrDohtaB6+BshmwxN/AlSy37OLshiV6QMKLZX/1MltH+nC2owdxyyYqsvAVOaRH4FOW
 dJq0Vdjy52tJWWam5C62U/I1BV45h+wnYelU2+sDrnx7ZBYFpEzp7yyXcc/sBCS0vVrY
 yk5jpl1aON4ZwFsSHoBnolGTgGSh+JBlfQPvJz6RDfNeR0tk8mt1ebhEJV9oZ2e2rO1B
 xSEs++MahlHflvzMFt9CJv8ZfP6yHwZzsRq25iCnZ/6Kgc/FcMaeQj9ejorHo0F60LLL YQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 361cey08m6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 08:21:16 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10CDEtF5142227;
        Tue, 12 Jan 2021 08:21:15 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 361cey08k7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 08:21:15 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10CDGirl000649;
        Tue, 12 Jan 2021 13:21:13 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06fra.de.ibm.com with ESMTP id 35y3rh9vuj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 12 Jan 2021 13:21:13 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10CDLA9745154640
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 12 Jan 2021 13:21:10 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 36AD54C04A;
        Tue, 12 Jan 2021 13:21:10 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6EBBE4C04E;
        Tue, 12 Jan 2021 13:21:09 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 12 Jan 2021 13:21:09 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v4 1/9] s390x: Add test_bit to library
Date: Tue, 12 Jan 2021 08:20:46 -0500
Message-Id: <20210112132054.49756-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210112132054.49756-1-frankja@linux.ibm.com>
References: <20210112132054.49756-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-12_07:2021-01-12,2021-01-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 spamscore=0
 phishscore=0 impostorscore=0 adultscore=0 priorityscore=1501 mlxscore=0
 malwarescore=0 clxscore=1015 mlxlogscore=999 bulkscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101120071
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Query/feature bits are commonly tested via MSB bit numbers on
s390. Let's add test bit functions, so we don't need to copy code to
test query bits.

The test_bit code has been taken from the kernel since most s390x KVM unit
test developers are used to them.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/bitops.h   | 26 ++++++++++++++++++++++++++
 lib/s390x/asm/facility.h |  3 ++-
 s390x/uv-guest.c         |  6 +++---
 3 files changed, 31 insertions(+), 4 deletions(-)

```
#### [RFC PATCH 1/7] skbuff: define field for hash report type
##### From: Yuri Benditovich <yuri.benditovich@daynix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuri Benditovich <yuri.benditovich@daynix.com>
X-Patchwork-Id: 12014741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNWANTED_LANGUAGE_BODY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFF6FC4332B
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 19:43:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EA272310A
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 19:43:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436552AbhALTnB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 14:43:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48368 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2406776AbhALTnA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 14:43:00 -0500
Received: from mail-wm1-x32c.google.com (mail-wm1-x32c.google.com
 [IPv6:2a00:1450:4864:20::32c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 293B8C0617A3
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 11:41:59 -0800 (PST)
Received: by mail-wm1-x32c.google.com with SMTP id 3so3228658wmg.4
        for <kvm@vger.kernel.org>; Tue, 12 Jan 2021 11:41:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=daynix-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=+hdtHCSFxGXzmG9zcdLMtsA9CM+yy9a1rXrTwefd0k4=;
        b=uDUgsIFWkCAbgZpUVsXjZnHVBtT5AU2g2Tu3bHmPpimoSMu5Pt0D9DUupyK66NiDmr
         SFEsFzaU9DeZGgsQNEmiMdYaft+Prt2oiSZp3IwXkNZcxt/HhMRiefuYPbdbHk207Kqk
         Ox0YHcUONluOucMlOfT29PUY08TWwE4IG1a6SaLfcUzRQriJ5ZteB9zJYi6UG87ywCfN
         JJHQnkpHwdqQk0KZ4i9o+jUIFEziT+WLlSsXAP0tJN8Igphnx/Aqlr/nyFJ/mvZPN5MB
         EXwGgSs6GpQKpUPrMqOtt2NwAzA19W1ixaml8FgEQbVfWvbklv/rk1W2DIbuFaxQ7f41
         yRmQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=+hdtHCSFxGXzmG9zcdLMtsA9CM+yy9a1rXrTwefd0k4=;
        b=r6rh2FZCNzEb7hwqDri03t3zyt1Xmp0DYuylFMfqfYZhbz1FIvMPmBcAwNAIPANuXc
         R7ceTErg/ObvEaFr0INqKE9wqwIGxf2W5Q0vLGuKtPiQCSzhGstO6Z3iH5HRX0NAEtq0
         SqxHV6U1/TJR4TE9idpRqxzuHWPGVfm70wTjXyCmMOjWxHkylAr8IVyCXObER8gpUlAU
         OyOsDi7o4oQgk5MsOAoYjx4xto3S2BXhx3ZKpusD+7Xw+En20lHnjvxF0IlezbgMVCOo
         bHcFbzvZquWKFbf3v6/iz7apf4uofDGeztT/aT2a8xgtAu+CCrog8LetVg96T4tgotW2
         xJCg==
X-Gm-Message-State: AOAM532BGC3B0HW2XLxMLAg314maJeUdta9cjHMMEmemQZArF8RXlnVP
        i1zpIEGxi09WjfWHbGtIgWzqAQ==
X-Google-Smtp-Source: 
 ABdhPJx/0woun/MhI7lJlAwq65ikInzHiKo9rw3lXUFvfj5s5Qs3xrAuB3tgEtBp9fISRu7oCo34FA==
X-Received: by 2002:a05:600c:2255:: with SMTP id
 a21mr809749wmm.122.1610480517946;
        Tue, 12 Jan 2021 11:41:57 -0800 (PST)
Received: from f2.redhat.com (bzq-79-183-72-147.red.bezeqint.net.
 [79.183.72.147])
        by smtp.gmail.com with ESMTPSA id
 z63sm4885315wme.8.2021.01.12.11.41.54
        (version=TLS1_2 cipher=ECDHE-ECDSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 12 Jan 2021 11:41:57 -0800 (PST)
From: Yuri Benditovich <yuri.benditovich@daynix.com>
To: davem@davemloft.net, kuba@kernel.org, mst@redhat.com,
        jasowang@redhat.com, ast@kernel.org, daniel@iogearbox.net,
        andrii@kernel.org, kafai@fb.com, songliubraving@fb.com, yhs@fb.com,
        john.fastabend@gmail.com, kpsingh@kernel.org,
        rdunlap@infradead.org, willemb@google.com, gustavoars@kernel.org,
        herbert@gondor.apana.org.au, steffen.klassert@secunet.com,
        nogikh@google.com, pablo@netfilter.org, decui@microsoft.com,
        cai@lca.pw, jakub@cloudflare.com, elver@google.com,
        pabeni@redhat.com, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, bpf@vger.kernel.org
Cc: yan@daynix.com
Subject: [RFC PATCH 1/7] skbuff: define field for hash report type
Date: Tue, 12 Jan 2021 21:41:37 +0200
Message-Id: <20210112194143.1494-2-yuri.benditovich@daynix.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210112194143.1494-1-yuri.benditovich@daynix.com>
References: <20210112194143.1494-1-yuri.benditovich@daynix.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Used by virtio-net receive side scaling

Signed-off-by: Yuri Benditovich <yuri.benditovich@daynix.com>
---
 include/linux/skbuff.h | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/2] drivers/misc: sysgenid: add system generation id driver
##### From: Adrian Catangiu <acatan@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Adrian Catangiu <acatan@amazon.com>
X-Patchwork-Id: 12013339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A9987C433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 12:18:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 612BE23107
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 12:18:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733050AbhALMRq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 07:17:46 -0500
Received: from smtp-fw-6002.amazon.com ([52.95.49.90]:21315 "EHLO
        smtp-fw-6002.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732299AbhALMRq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 07:17:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1610453861; x=1641989861;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=0ldrdKg26EexMTh8D0EIzFcuMjN4BVIAzO3jszvttOM=;
  b=S3JtMow/p+RgyApb9RchoUlCcxIbdqBiM/C08jEBQqQElqDyokJHdUei
   xuWTMKijscihzyimOiEVqn3HhCQcDGSkn0+ykwk6woBDUxJD65F6hWZIn
   /QdTWvDrGU7bIsDGjLmUEJmfEmZc47q8XsP3JQ8GNU4AUasnAFJ91GTpp
   Q=;
X-IronPort-AV: E=Sophos;i="5.79,341,1602547200";
   d="scan'208";a="77011780"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1d-5dd976cd.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6002.iad6.amazon.com with ESMTP;
 12 Jan 2021 12:16:46 +0000
Received: from EX13D08EUB004.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1d-5dd976cd.us-east-1.amazon.com (Postfix) with
 ESMTPS id EB1D9A1B73;
        Tue, 12 Jan 2021 12:16:43 +0000 (UTC)
Received: from uf6ed9c851f4556.ant.amazon.com (10.43.161.68) by
 EX13D08EUB004.ant.amazon.com (10.43.166.158) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 12 Jan 2021 12:16:29 +0000
From: Adrian Catangiu <acatan@amazon.com>
To: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <linux-s390@vger.kernel.org>
CC: <gregkh@linuxfoundation.org>, <graf@amazon.com>, <arnd@arndb.de>,
        <ebiederm@xmission.com>, <rppt@kernel.org>, <0x7f454c46@gmail.com>,
        <borntraeger@de.ibm.com>, <Jason@zx2c4.com>, <jannh@google.com>,
        <w@1wt.eu>, <colmmacc@amazon.com>, <luto@kernel.org>,
        <tytso@mit.edu>, <ebiggers@kernel.org>, <dwmw@amazon.co.uk>,
        <bonzini@gnu.org>, <sblbir@amazon.com>, <raduweis@amazon.com>,
        <corbet@lwn.net>, <mst@redhat.com>, <mhocko@kernel.org>,
        <rafael@kernel.org>, <pavel@ucw.cz>, <mpe@ellerman.id.au>,
        <areber@redhat.com>, <ovzxemul@gmail.com>, <avagin@gmail.com>,
        <ptikhomirov@virtuozzo.com>, <gil@azul.com>, <asmehra@redhat.com>,
        <dgunigun@redhat.com>, <vijaysun@ca.ibm.com>, <oridgar@gmail.com>,
        <ghammer@redhat.com>, Adrian Catangiu <acatan@amazon.com>
Subject: [PATCH v4 1/2] drivers/misc: sysgenid: add system generation id
 driver
Date: Tue, 12 Jan 2021 14:15:59 +0200
Message-ID: <1610453760-13812-2-git-send-email-acatan@amazon.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1610453760-13812-1-git-send-email-acatan@amazon.com>
References: <1610453760-13812-1-git-send-email-acatan@amazon.com>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.68]
X-ClientProxiedBy: EX13D50UWC001.ant.amazon.com (10.43.162.96) To
 EX13D08EUB004.ant.amazon.com (10.43.166.158)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Background and problem

The System Generation ID feature is required in virtualized or
containerized environments by applications that work with local copies
or caches of world-unique data such as random values, uuids,
monotonically increasing counters, etc.
Such applications can be negatively affected by VM or container
snapshotting when the VM or container is either cloned or returned to
an earlier point in time.

Furthermore, simply finding out about a system generation change is
only the starting point of a process to renew internal states of
possibly multiple applications across the system. This process could
benefit from a driver that provides an interface through which
orchestration can be easily done.

- Solution

The System Generation ID is a simple concept meant to alleviate the
issue by providing a monotonically increasing u32 counter that changes
each time the VM or container is restored from a snapshot.

The `sysgenid` driver exposes a monotonic incremental System Generation
u32 counter via a char-dev FS interface that provides sync and async
SysGen counter updates notifications. It also provides SysGen counter
retrieval and confirmation mechanisms.

The counter starts from zero when the driver is initialized and
monotonically increments every time the system generation changes.

The `sysgenid` driver exports the `void sysgenid_bump_generation()`
symbol which can be used by backend drivers to drive system generation
changes based on hardware events.
System generation changes can also be driven by userspace software
through a dedicated driver ioctl.

Userspace applications or libraries can then (a)synchronously consume
the system generation counter through the provided FS interface to make
any necessary internal adjustments following a system generation
update.

Signed-off-by: Adrian Catangiu <acatan@amazon.com>
---
 Documentation/misc-devices/sysgenid.rst | 240 +++++++++++++++++++++++++
 drivers/misc/Kconfig                    |  16 ++
 drivers/misc/Makefile                   |   1 +
 drivers/misc/sysgenid.c                 | 298 ++++++++++++++++++++++++++++++++
 include/uapi/linux/sysgenid.h           |  18 ++
 5 files changed, 573 insertions(+)
 create mode 100644 Documentation/misc-devices/sysgenid.rst
 create mode 100644 drivers/misc/sysgenid.c
 create mode 100644 include/uapi/linux/sysgenid.h

diff --git a/Documentation/misc-devices/sysgenid.rst b/Documentation/misc-devices/sysgenid.rst
new file mode 100644
index 0000000..0b31ccf
--- /dev/null
+++ b/Documentation/misc-devices/sysgenid.rst
@@ -0,0 +1,240 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+========
+SYSGENID
+========
+
+The System Generation ID feature is required in virtualized or
+containerized environments by applications that work with local copies
+or caches of world-unique data such as random values, UUIDs,
+monotonically increasing counters, etc.
+Such applications can be negatively affected by VM or container
+snapshotting when the VM or container is either cloned or returned to
+an earlier point in time.
+
+The System Generation ID is a simple concept meant to alleviate the
+issue by providing a monotonically increasing counter that changes
+each time the VM or container is restored from a snapshot.
+The driver for it lives at ``drivers/misc/sysgenid.c``.
+
+The ``sysgenid`` driver exposes a monotonic incremental System
+Generation u32 counter via a char-dev FS interface accessible through
+``/dev/sysgenid`` that provides sync and async SysGen counter updates
+notifications. It also provides SysGen counter retrieval and
+confirmation mechanisms.
+
+The counter starts from zero when the driver is initialized and
+monotonically increments every time the system generation changes.
+
+The ``sysgenid`` driver exports the ``void sysgenid_bump_generation()``
+symbol which can be used by backend drivers to drive system generation
+changes based on hardware events.
+System generation changes can also be driven by userspace software
+through a dedicated driver ioctl.
+
+Userspace applications or libraries can (a)synchronously consume the
+system generation counter through the provided FS interface, to make
+any necessary internal adjustments following a system generation update.
+
+Driver FS interface:
+
+``open()``:
+  When the device is opened, a copy of the current Sys-Gen-Id (counter)
+  is associated with the open file descriptor. The driver now tracks
+  this file as an independent *watcher*. The driver tracks how many
+  watchers are aware of the latest Sys-Gen-Id counter and how many of
+  them are *outdated*; outdated being those that have lived through
+  a Sys-Gen-Id change but not yet confirmed the new generation counter.
+
+``read()``:
+  Read is meant to provide the *new* system generation counter when a
+  generation change takes place. The read operation blocks until the
+  associated counter is no longer up to date, at which point the new
+  counter is provided/returned.
+  Nonblocking ``read()`` uses ``EAGAIN`` to signal that there is no
+  *new* counter value available. The generation counter is considered
+  *new* for each open file descriptor that hasn't confirmed the new
+  value following a generation change. Therefore, once a generation
+  change takes place, all ``read()`` calls will immediately return the
+  new generation counter and will continue to do so until the
+  new value is confirmed back to the driver through ``write()``.
+  Partial reads are not allowed - read buffer needs to be at least
+  ``sizeof(unsigned)`` in size.
+
+``write()``:
+  Write is used to confirm the up-to-date Sys Gen counter back to the
+  driver.
+  Following a VM generation change, all existing watchers are marked
+  as *outdated*. Each file descriptor will maintain the *outdated*
+  status until a ``write()`` confirms the up-to-date counter back to
+  the driver.
+  Partial writes are not allowed - write buffer should be exactly
+  ``sizeof(unsigned)`` in size.
+
+``poll()``:
+  Poll is implemented to allow polling for generation counter updates.
+  Such updates result in ``EPOLLIN`` polling status until the new
+  up-to-date counter is confirmed back to the driver through a
+  ``write()``.
+
+``ioctl()``:
+  The driver also adds support for tracking count of open file
+  descriptors that haven't acknowledged a generation counter update,
+  as well as a mechanism for userspace to *force* a generation update:
+
+  - SYSGENID_GET_OUTDATED_WATCHERS: immediately returns the number of
+    *outdated* watchers - number of file descriptors that were open
+    during a system generation change, and which have not yet confirmed
+    the new generation counter.
+  - SYSGENID_WAIT_WATCHERS: blocks until there are no more *outdated*
+    watchers, or if a ``timeout`` argument is provided, until the
+    timeout expires.
+    If the current caller is *outdated* or a generation change happens
+    while waiting (thus making current caller *outdated*), the ioctl
+    returns ``-EINTR`` to signal the user to handle event and retry.
+  - SYSGENID_FORCE_GEN_UPDATE: forces a generation counter increment.
+    It takes a ``minimum-generation`` argument which represents the
+    minimum value the generation counter will be incremented to. For
+    example if current generation is ``5`` and ``SYSGENID_FORCE_GEN_UPDATE(8)``
+    is called, the generation counter will increment to ``8``.
+    This IOCTL can only be used by processes with CAP_CHECKPOINT_RESTORE
+    or CAP_SYS_ADMIN capabilities.
+
+``mmap()``:
+  The driver supports ``PROT_READ, MAP_SHARED`` mmaps of a single page
+  in size. The first 4 bytes of the mapped page will contain an
+  up-to-date u32 copy of the system generation counter.
+  The mapped memory can be used as a low-latency generation counter
+  probe mechanism in critical sections - see examples.
+
+``close()``:
+  Removes the file descriptor as a system generation counter *watcher*.
+
+Example application workflows
+-----------------------------
+
+1) Watchdog thread simplified example::
+
+	void watchdog_thread_handler(int *thread_active)
+	{
+		unsigned genid;
+		int fd = open("/dev/sysgenid", O_RDWR | O_CLOEXEC, S_IRUSR | S_IWUSR);
+
+		do {
+			// read new gen ID - blocks until VM generation changes
+			read(fd, &genid, sizeof(genid));
+
+			// because of VM generation change, we need to rebuild world
+			reseed_app_env();
+
+			// confirm we're done handling gen ID update
+			write(fd, &genid, sizeof(genid));
+		} while (atomic_read(thread_active));
+
+		close(fd);
+	}
+
+2) ASYNC simplified example::
+
+	void handle_io_on_sysgenfd(int sysgenfd)
+	{
+		unsigned genid;
+
+		// read new gen ID - we need it to confirm we've handled update
+		read(fd, &genid, sizeof(genid));
+
+		// because of VM generation change, we need to rebuild world
+		reseed_app_env();
+
+		// confirm we're done handling the gen ID update
+		write(fd, &genid, sizeof(genid));
+	}
+
+	int main() {
+		int epfd, sysgenfd;
+		struct epoll_event ev;
+
+		epfd = epoll_create(EPOLL_QUEUE_LEN);
+
+		sysgenfd = open("/dev/sysgenid",
+		               O_RDWR | O_CLOEXEC | O_NONBLOCK,
+		               S_IRUSR | S_IWUSR);
+
+		// register sysgenid for polling
+		ev.events = EPOLLIN;
+		ev.data.fd = sysgenfd;
+		epoll_ctl(epfd, EPOLL_CTL_ADD, sysgenfd, &ev);
+
+		// register other parts of your app for polling
+		// ...
+
+		while (1) {
+			// wait for something to do...
+			int nfds = epoll_wait(epfd, events,
+				MAX_EPOLL_EVENTS_PER_RUN,
+				EPOLL_RUN_TIMEOUT);
+			if (nfds < 0) die("Error in epoll_wait!");
+
+			// for each ready fd
+			for(int i = 0; i < nfds; i++) {
+				int fd = events[i].data.fd;
+
+				if (fd == sysgenfd)
+					handle_io_on_sysgenfd(sysgenfd);
+				else
+					handle_some_other_part_of_the_app(fd);
+			}
+		}
+
+		return 0;
+	}
+
+3) Mapped memory polling simplified example::
+
+	/*
+	 * app/library function that provides cached secrets
+	 */
+	char * safe_cached_secret(app_data_t *app)
+	{
+		char *secret;
+		volatile unsigned *const genid_ptr = get_sysgenid_mapping(app);
+	again:
+		secret = __cached_secret(app);
+
+		if (unlikely(*genid_ptr != app->cached_genid)) {
+			app->cached_genid = *genid_ptr;
+			barrier();
+
+			// rebuild world then confirm the genid update (thru write)
+			rebuild_caches(app);
+
+			ack_sysgenid_update(app);
+
+			goto again;
+		}
+
+		return secret;
+	}
+
+4) Orchestrator simplified example::
+
+	/*
+	 * orchestrator - manages multiple applications and libraries used by
+	 * a service and tries to make sure all sensitive components gracefully
+	 * handle VM generation changes.
+	 * Following function is called on detection of a VM generation change.
+	 */
+	int handle_sysgen_update(int sysgen_fd, unsigned new_gen_id)
+	{
+		// pause until all components have handled event
+		pause_service();
+
+		// confirm *this* watcher as up-to-date
+		write(sysgen_fd, &new_gen_id, sizeof(unsigned));
+
+		// wait for all *others* for at most 5 seconds.
+		ioctl(sysgen_fd, VMGENID_WAIT_WATCHERS, 5000);
+
+		// all applications on the system have rebuilt worlds
+		resume_service();
+	}
```
#### [PATCH v1] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
##### From: Cindy Lu <lulu@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cindy Lu <lulu@redhat.com>
X-Patchwork-Id: 12012271
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70B45C433E0
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 02:48:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BF9922CE3
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 02:48:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730914AbhALCsZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 11 Jan 2021 21:48:25 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:27222 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726018AbhALCsX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 11 Jan 2021 21:48:23 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610419617;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Nd9vrsLoQ4eNomWd4y4aPcW+GO4/2gg4PZxpPi0r3GU=;
        b=U06+F5sJ+tXkb03krdulczKhOpuxD+zn1EiLapz++a2yn0mICbuJwKvnIhdzT8qOhLrORr
        EJerUc8NQHH5/nsg6RsF+n6Vj3jm752cyXjMjQDqy15SZSUmuxk+DF8P79V612x/WveNEN
        2WaMaR1AhT+syIDeQ1lM51gmNndNrwc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-360-FNMRMh49NGeqp52gcwiGEw-1; Mon, 11 Jan 2021 21:46:55 -0500
X-MC-Unique: FNMRMh49NGeqp52gcwiGEw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9B14F107ACF8;
        Tue, 12 Jan 2021 02:46:54 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-12-95.pek2.redhat.com [10.72.12.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F71A5B693;
        Tue, 12 Jan 2021 02:46:51 +0000 (UTC)
From: Cindy Lu <lulu@redhat.com>
To: lulu@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        lingshan.zhu@intel.com
Subject: [PATCH v1] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
Date: Tue, 12 Jan 2021 10:46:48 +0800
Message-Id: <20210112024648.31428-1-lulu@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

in vhost_vdpa_set_config_call, the cb.private should be vhost_vdpa.
this cb.private will finally use in vhost_vdpa_config_cb as
vhost_vdpa.Fix this issue

Signed-off-by: Cindy Lu <lulu@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
##### From: Cindy Lu <lulu@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cindy Lu <lulu@redhat.com>
X-Patchwork-Id: 12012443
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56BD3C433E6
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 05:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 18F77223E8
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 05:34:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733161AbhALFeS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 00:34:18 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:27079 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732730AbhALFeS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 00:34:18 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610429572;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3tdKW3SLUhCLxVY2DOdCzA12uRd5TyP8aBW/+yPnNmQ=;
        b=JC3b0Qu6xa2OvgxlH/WzDq8muGMQmyxzpnYX1FiN6CsLanNxAwlvvUkoemuvqnPucNGdXM
        F/fkAfC/SuTZmJa05/6ZRVCF7n0NuHpyYvq3Wxwg50W1mph3O3E4KYT1qcMkTEYyObbeC8
        X56lEbF76LgMxR1yHomaVb/Oq2rHS+w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-585-qI6e3ArVMbCdtWuQePZw8Q-1; Tue, 12 Jan 2021 00:32:50 -0500
X-MC-Unique: qI6e3ArVMbCdtWuQePZw8Q-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D80291842140;
        Tue, 12 Jan 2021 05:32:48 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-12-95.pek2.redhat.com [10.72.12.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7E0B510016F6;
        Tue, 12 Jan 2021 05:32:42 +0000 (UTC)
From: Cindy Lu <lulu@redhat.com>
To: lulu@redhat.com, jasowang@redhat.com, mst@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        lingshan.zhu@intel.com
Cc: stable@vger.kernel.org
Subject: [PATCH v2] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
Date: Tue, 12 Jan 2021 13:32:27 +0800
Message-Id: <20210112053227.8574-1-lulu@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In vhost_vdpa_set_config_call, the cb.private should be vhost_vdpa.
this cb.private will finally use in vhost_vdpa_config_cb as
vhost_vdpa. Fix this issue.

Signed-off-by: Cindy Lu <lulu@redhat.com>
---
 drivers/vhost/vdpa.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
##### From: Cindy Lu <lulu@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cindy Lu <lulu@redhat.com>
X-Patchwork-Id: 12012449
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7D4D3C433E9
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 05:38:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51FB622CE3
	for <kvm@archiver.kernel.org>; Tue, 12 Jan 2021 05:38:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732713AbhALFiK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 00:38:10 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:28541 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732578AbhALFiJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 12 Jan 2021 00:38:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610429802;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VH1DnjM7C34WcJYdUsZY2fXbHo1byMf7LCcAsLj7Uv8=;
        b=RhoS5SaRHW3Od+Zxb/4HowZ0x6SqFBLTWmoieWF7DpvhpLqrSdAWrH2KGtD/XzALPV+JIn
        s6lCG2punM8Y525jaUR+Ti9Noqh9L/Z+oOT21fxxv4Nx0LzStW3NOhtOmFHRMc8wfNgtg5
        nreYGGz0VGmgT5Cvl9mCR3z7Bt+G6/g=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-268-l5RWiJr-MDS2JphWcs2S1g-1; Tue, 12 Jan 2021 00:36:40 -0500
X-MC-Unique: l5RWiJr-MDS2JphWcs2S1g-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3B67C802B40;
        Tue, 12 Jan 2021 05:36:39 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-12-95.pek2.redhat.com [10.72.12.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 97A9B60BE2;
        Tue, 12 Jan 2021 05:36:32 +0000 (UTC)
From: Cindy Lu <lulu@redhat.com>
To: lulu@redhat.com, jasowang@redhat.com, mst@redhat.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        lingshan.zhu@intel.com
Cc: stable@vger.kernel.org
Subject: [PATCH v3] vhost_vdpa: fix the problem in vhost_vdpa_set_config_call
Date: Tue, 12 Jan 2021 13:36:29 +0800
Message-Id: <20210112053629.9853-1-lulu@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In vhost_vdpa_set_config_call, the cb.private should be vhost_vdpa.
this cb.private will finally use in vhost_vdpa_config_cb as
vhost_vdpa. Fix this issue.

Fixes: 776f395004d82 ("vhost_vdpa: Support config interrupt in vdpa")
Acked-by: Jason Wang <jasowang@redhat.com>
Signed-off-by: Cindy Lu <lulu@redhat.com>
---
 drivers/vhost/vdpa.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
