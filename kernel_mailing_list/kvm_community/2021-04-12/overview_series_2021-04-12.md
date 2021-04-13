#### [PATCH v12 01/13] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12198723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 74062C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:43:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D44B6121D
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:43:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237946AbhDLTn4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 15:43:56 -0400
Received: from mail-bn8nam08on2045.outbound.protection.outlook.com
 ([40.107.100.45]:21536
        "EHLO NAM04-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S237564AbhDLTnz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 15:43:55 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PlVDpDbK/34YOmg18pLqQF5aJUnrRxPGHx632YIDq3Vuql1QRU4tWg4D35pNYBhexRjeVNFwqcRgFjAyj8WQiy+dnUhNUVCxevrVgFEgPQToawa2S1rsnr/YC0HAah/9OrK3JMitPBbsDv4zUA20joWxITvXv/RwFyZ7F7X9CELowyo1hp2RAM1O6PIMef5N919GbzmIB3HNfTjKzjbqK2oWLSIfyaUzUc+5HhDIMTRZ1nTceymCmcZkeZupvDbfpyPNPZ5w2HD4pCnX24zWaAIYyTt2ALDp8QwyMhAg8n0xUTAW4XdmXbCzfpin6OZSqmulF8KlUegThyYdo33Xmw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=Ieyv+cmt8EmMt9/jprDxqWhTVNUbl+a61kd9HpamF2jEvvXTfzQWXHv/22guIlAYT9C0vmjAB4p46pjY/Xsk/XRGGRdkOevUT6PlWpEICT+tThtmTOyQ356aELlows71Z53ywtiqOWcptSIINleaY6+Tz1K5h1y2yI0lj7XyIyX9CLvpBpxIc1FhnfRbkfEypcTO6J2/SW1o2SKzviLg/vO2stLLIxOwuZq7dMWM+hJP8f296UXm50bZ5surWwNkGc75B78kykW1moAdAXIgr5C/+4zOc71caeAtN6LeqBnijOa2Jsjfsv4AeqDqgVkaa0nRHEdDFM/6INFCV9myqg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=vdOz2wgPBdZhkuOsaquMG/TTR8KZlX0DrtIxM467S0YbH/ZjDNcYzKYuf59PqIel4xd0zU5FPx5FjZvxY6JUwll9eej7Y+0tr6vEEgfM4jG/okNnGZ9tqhHJQy8KYj3qoQeEVG01JOQH5ZA05FovbKpyuiCv8gvkqcVm+Iwf2Ic=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2720.namprd12.prod.outlook.com (2603:10b6:805:70::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.16; Mon, 12 Apr
 2021 19:43:33 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%6]) with mapi id 15.20.4020.022; Mon, 12 Apr 2021
 19:43:32 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v12 01/13] KVM: SVM: Add KVM_SEV SEND_START command
Date: Mon, 12 Apr 2021 19:43:22 +0000
Message-Id: 
 <2f1686d0164e0f1b3d6a41d620408393e0a48376.1618254007.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1618254007.git.ashish.kalra@amd.com>
References: <cover.1618254007.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN7PR04CA0028.namprd04.prod.outlook.com
 (2603:10b6:806:f2::33) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN7PR04CA0028.namprd04.prod.outlook.com (2603:10b6:806:f2::33) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.16 via Frontend
 Transport; Mon, 12 Apr 2021 19:43:32 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 426dbf7d-c072-4ca9-a0a5-08d8fdeb412e
X-MS-TrafficTypeDiagnostic: SN6PR12MB2720:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB272026AEB140CDD0A2B07E688E709@SN6PR12MB2720.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ad3pns8phDZVFFm9oLAISKPYYzghdM58clpveeaU9IESQ5M4q5y+TPjbuOuMLZbiRnecUk43hUBgjn2fKEXNBhhtP7yb/vfz8z6NmGenWKPf/eWgCYnafDMSYvdokeiRug8zSXpc3+e9Ct+yUadsOkoPoBk4/NNflhQvE4mNAkiK5Cwr8ggyWYXJeCtbeZ7RyWmc4js7dTGLbIn5ISsCNH6uZstZzwD+iCSQkmEEeDXOxVKw6Zgz/qsXqLqfwCHIzlhJbqBsr/WzdmjCGZ49dNwEXDcnmsDfH2VIpb9+kO0T5OXOj5zRAOqI3DzgoMquFxOcttwBjk8vq9Y4sF8s131dK+WUoJSogaxvXiB08Siu+QMIDwdiNqEt0yJFPerL5qQ3mswFvn72nYfrvVEqYyDXafi3NFF+Rp4ABnN5NvHw8bWGA6mfL+nhwsOg0LfWlw2iDEWFENdPKW7you+rR3huGBrtVGmsNPVekxh9zEruiKhPa+YOUmlIhyMaKr7hfiNT5YMw39LorJ1+cGbPSM/iCjcYhNB/fISdB2PFJ0erT9UbF2SRLGYBygf8/EjuhYZa84B44Cfbp8z4nBFa1PNfL3ayMlLjsWWlxMXPvLi/+gL7DlQE3D4uFYN0yAPu6QHCsfJCmdWC7wbCM4h2Wc0g5VEj8FXsfnVSZ/Xw+es=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(396003)(136003)(346002)(376002)(39860400002)(86362001)(36756003)(83380400001)(38350700002)(38100700002)(4326008)(2906002)(6916009)(956004)(478600001)(316002)(5660300002)(66946007)(52116002)(7696005)(8936002)(8676002)(6486002)(66556008)(66476007)(16526019)(2616005)(26005)(6666004)(186003)(7416002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?1Z2PalwdfpSJlVJr8ondZTCdRsdUXF?=
	=?utf-8?q?h6hK9b1ZK/nzwgmOSQjN9bIBsmahdBtYEma5MJghmzj0BZYCJRjLWlOkfDIwu2qkW?=
	=?utf-8?q?IekinKcAMnZSCtQz9ITP/eqDMSMyeFgHlDJc027lcRNbY/mMAsD0scWjit26WFYrF?=
	=?utf-8?q?7ks/ne1AjtXuUwKvByRxUa+Qou2zgmyJvZj4MBfHTRGL7FASde72H5GnY/C973URp?=
	=?utf-8?q?24NW5I+3ipxlv954C0DarsHK/+opAYoa/20ikx1r+DiNR3YPFM2+Uqi/1ieIxOH0a?=
	=?utf-8?q?dSQvk8zauXTpsth6gp2Lz/8x1TG+V30CtEZXseRP1cE9mBAwkNzLTeI5M8DoEVz3j?=
	=?utf-8?q?JFQnoI6hH0EAEVD2xhSA+bTNevKZ2bDzupa8oWNW2Tn5cuwbApmJThjp8dnKkHSTU?=
	=?utf-8?q?vZVgLnfMk181JPBHYCgZpLRlvYoxH2kT6dOsAzKu6/8wl5C9oPAt2BarRDQlsf2W6?=
	=?utf-8?q?XFTp3UExPOYCp4i71OxaIV6FiF3MfLpIdZXsmExxXcvY4TlQDjIMz1uA57WsHNaQc?=
	=?utf-8?q?KdVZ/ho45EMf5t34BNb154qTDAkn5Tm+KDwdwdhgcDb9E78oFxl49/Lb9nforYUXW?=
	=?utf-8?q?4Z66kNV3109JOOm2GDkPwL530XIk4XlCoyCgtRIGKzyOBpo+QZ0ulPba9HOFpNi67?=
	=?utf-8?q?6fCX/R6SqQ/pjOVjN9wsM+Dx6pCtiHtoM0f6zjCQz41V1D93OYVmm7goENbIAA231?=
	=?utf-8?q?KqBp1H+lWcSC5XG7HB7SicSjwwWyIMDLnWF5oBox8YQvEBTkVSIKbM39JnJV05o3B?=
	=?utf-8?q?MwBwfGtdE6EZyWNAPEW5W6x80pmb87eSjyHLDtzGTpjV9ttYr7O74yikyPk50fwYF?=
	=?utf-8?q?UoEvIllwelv0sNIcALTyVu+yq9xEucKn2EkVL4RSmt1WTOey7FnQZTwBst11GNar8?=
	=?utf-8?q?y7v8Y/oKJuB9U39zcNfRiuLa5H4VjfBq+Y138QHKFNItxr66rowTY8uU+aM+5Cvsc?=
	=?utf-8?q?2ZZhgNMjGaPMA5XSGeqtR4vFtwRwmvVXzBK/wk2ZNjs0fNo0awyr0mG685lbbDt5i?=
	=?utf-8?q?TA1vhHIn3mVixlcWdYNnqJvR0OFoHATOM7U4D7HG1sCYfr+a1XSn0BQcGz0Jx5wcO?=
	=?utf-8?q?raeDavIjkiw8jzOjg5jPse09w3I3byfalLLQDT+NCa8eb967iq6jHqx7WqPvktp1v?=
	=?utf-8?q?ySmCOZs82Ncp2JvXYBg+OTNT3RxnQb8F+RCainbNVIA3TazAS4K6oCb5cW937TcAA?=
	=?utf-8?q?gkTN2/gQn9Xkwd7K9IBivn/lf7d2CJYybK8SXZAvXKWY7GTCBBF2s1bgVMBWSGpB9?=
	=?utf-8?q?cOaRCrkUn0fe2J?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 426dbf7d-c072-4ca9-a0a5-08d8fdeb412e
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Apr 2021 19:43:32.7960
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5NfTr4dWsPpDOFhv2XLn+BdvUfopEGBp2vL0qibOyrORb4Mc6yWiloxpIpE09Lch7i2Rrl12874MUF+j2H6e1Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2720
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
#### [PATCH RFC v5 01/12] linux-header: Update linux/kvm.h
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 12196943
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 51D67C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 06:53:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F857610C7
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 06:53:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236593AbhDLGxp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 02:53:45 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:16893 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229461AbhDLGxp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 02:53:45 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FJfXl6jN6zkdMr;
        Mon, 12 Apr 2021 14:51:35 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.498.0; Mon, 12 Apr 2021
 14:53:19 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <bin.meng@windriver.com>, <fanliang@huawei.com>,
        <wu.wubin@huawei.com>, <zhang.zhanghailiang@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v5 01/12] linux-header: Update linux/kvm.h
Date: Mon, 12 Apr 2021 14:52:35 +0800
Message-ID: <20210412065246.1853-2-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
In-Reply-To: <20210412065246.1853-1-jiangyifei@huawei.com>
References: <20210412065246.1853-1-jiangyifei@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update linux-headers/linux/kvm.h from
https://github.com/avpatel/linux/tree/riscv_kvm_v17.
Only use this header file, so here do not update all linux headers by
update-linux-headers.sh until above KVM series is accepted.

Signed-off-by: Yifei Jiang <jiangyifei@huawei.com>
Signed-off-by: Yipeng Yin <yinyipeng1@huawei.com>
---
 linux-headers/linux/kvm.h | 97 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 97 insertions(+)

```
#### [PATCH v2 1/4] KVM: x86: Move FPU register accessors into fpu.h
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12198529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 529C6C43460
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 17:02:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0A4E9611F2
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 17:02:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244183AbhDLRCh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 13:02:37 -0400
Received: from smtp-fw-6001.amazon.com ([52.95.48.154]:11532 "EHLO
        smtp-fw-6001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243396AbhDLRBe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 13:01:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1618246876; x=1649782876;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=cKk0OAbREUZmDCeFiWyFsrVwk/f3Wr9lxhDgovBejP8=;
  b=Y8P7SJDKJ+39PCx+xm056zz562NtioUiK73Sw4mNvWenHRFvQWQ3ioKt
   J/8OzCS+MnT+S8Jk456Z/L/NZwVRNVdadXmUGv4r6y3jsgrv0r8+MwJNb
   74icv6TAndrDrt7BviT6SNa863ykKDTL3EVeBH3apMGjWWkrY5JxUn0/r
   M=;
X-IronPort-AV: E=Sophos;i="5.82,216,1613433600";
   d="scan'208";a="106988217"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-807d4a99.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-6001.iad6.amazon.com with ESMTP;
 12 Apr 2021 17:01:09 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1a-807d4a99.us-east-1.amazon.com (Postfix) with
 ESMTPS id 5EA93A18AE;
        Mon, 12 Apr 2021 17:01:03 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.253) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 12 Apr 2021 17:00:54 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>,
        Alexander Graf <graf@amazon.com>,
        Evgeny Iakovlev <eyakovl@amazon.de>,
        Liran Alon <liran@amazon.com>,
        Ioannis Aslanidis <iaslan@amazon.de>,
        <linux-hyperv@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v2 1/4] KVM: x86: Move FPU register accessors into fpu.h
Date: Mon, 12 Apr 2021 19:00:14 +0200
Message-ID: 
 <5d2945df9dd807dca45ab256c88aeb4430ecf508.1618244920.git.sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1618244920.git.sidcha@amazon.de>
References: <cover.1618244920.git.sidcha@amazon.de>
MIME-Version: 1.0
X-Originating-IP: [10.43.161.253]
X-ClientProxiedBy: EX13D16UWB001.ant.amazon.com (10.43.161.17) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-v XMM fast hypercalls use XMM registers to pass input/output
parameters. To access these, hyperv.c can reuse some FPU register
accessors defined in emulator.c. Move them to a common location so both
can access them.

While at it, reorder the parameters of these accessor methods to make
them more readable.

Cc: Alexander Graf <graf@amazon.com>
Cc: Evgeny Iakovlev <eyakovl@amazon.de>
Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>
---
 arch/x86/kvm/emulate.c | 138 ++++++----------------------------------
 arch/x86/kvm/fpu.h     | 140 +++++++++++++++++++++++++++++++++++++++++
 2 files changed, 158 insertions(+), 120 deletions(-)
 create mode 100644 arch/x86/kvm/fpu.h

```
#### [GIT PULL 1/7] KVM: s390: Fix comment spelling in kvm_s390_vcpu_start()
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 12198451
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CEB64C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 16:06:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA9066134F
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 16:06:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243302AbhDLQGb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 12:06:31 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41246 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S243252AbhDLQGQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 12:06:16 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13CG3vrf016611;
        Mon, 12 Apr 2021 12:05:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : content-transfer-encoding
 : mime-version; s=pp1; bh=ATEshe8k928PibaQLa2a2U6E8anqabzsu3OrNRgQCk8=;
 b=p2NZBSw6Nt5pafYbnpDo7tjxONzzzS7dZfy1zCbQQ1Q7WwpVhzNXZ3NmNJRCT0qE5uwX
 xVcpjYZiI2K7ssJprsea1gAYooInQBT9Y1B358YNeiKqOvMvEKlo8rzT7maO17/ulPCv
 e9d7tUOLQV+kjVvo48PFo08+P4aKML0K0+vB+bJ7FjC32L/wZbLF3ANlruqGmZPW4vmf
 1smZ4iqZdD4qRrDwsuP6TOrvSgAKoUPf3r4s2j5y+h3EpG1VKr4CLPoQVmm5jmb1ZuVr
 vvPavkze07b2MLM9WTls00cuz09EG+5HUnfcSDrntcDwOf5yOY9wCvT2rtwsHDoshxiZ vg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vjtt7s3p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 12:05:52 -0400
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13CG4TLf019942;
        Mon, 12 Apr 2021 12:05:51 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vjtt7s2k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 12:05:51 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13CFprfZ029682;
        Mon, 12 Apr 2021 16:05:49 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03ams.nl.ibm.com with ESMTP id 37u3n89y1t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 16:05:49 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13CG5ktM57409848
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 16:05:46 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ACF584C046;
        Mon, 12 Apr 2021 16:05:46 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A29D74C058;
        Mon, 12 Apr 2021 16:05:46 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 12 Apr 2021 16:05:46 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 6199BE02A6; Mon, 12 Apr 2021 18:05:46 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Bhaskar Chowdhury <unixbhaskar@gmail.com>,
        Randy Dunlap <rdunlap@infradead.org>
Subject: [GIT PULL 1/7] KVM: s390: Fix comment spelling in
 kvm_s390_vcpu_start()
Date: Mon, 12 Apr 2021 18:05:39 +0200
Message-Id: <20210412160545.231194-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210412160545.231194-1-borntraeger@de.ibm.com>
References: <20210412160545.231194-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: J9DqRhg995KS7rA2OZ_QAdDLi1-DFBlT
X-Proofpoint-ORIG-GUID: uk1mVnzQOlfzzOX9silV3MyN-BDsJlDj
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-12_11:2021-04-12,2021-04-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 priorityscore=1501 impostorscore=0 suspectscore=0 bulkscore=0 adultscore=0
 mlxscore=0 mlxlogscore=900 clxscore=1015 phishscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104120102
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bhaskar Chowdhury <unixbhaskar@gmail.com>

s/oustanding/outstanding/

Signed-off-by: Bhaskar Chowdhury <unixbhaskar@gmail.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org>
Link: https://lore.kernel.org/r/20210213153227.1640682-1-unixbhaskar@gmail.com
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: arm/arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST read
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12198291
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE2CDC433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 15:00:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA5F26128E
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 15:00:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242453AbhDLPBJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 11:01:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:51813 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241096AbhDLPBJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 11:01:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618239650;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VNdKS9KNgagmrHQvjGL4Hvng5mswnO3U1Do4oQAu2Vo=;
        b=CRkvwHs5cdZwe2Y7eBBxafI/FD11R5smXyqfnJ+DovWDjLnFvnr/RR8OabvKwIbwGhNvTg
        0EN676r7Bx9zAzgiwx248f20txp1KIZknlDclXVMyKWy5q7D0jU9pmPqVNxy6oMT+19IRB
        z0VNFl5UvzqIB2s+3rthM0ho+okjTQg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-290-zHNgWqTNMCqnuTnLJSnPSQ-1; Mon, 12 Apr 2021 11:00:47 -0400
X-MC-Unique: zHNgWqTNMCqnuTnLJSnPSQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6E157108C317;
        Mon, 12 Apr 2021 15:00:43 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-253.ams2.redhat.com
 [10.36.113.253])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 95F165D6D1;
        Mon, 12 Apr 2021 15:00:39 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org,
        alexandru.elisei@arm.com, suzuki.poulose@arm.com,
        james.morse@arm.com
Cc: drjones@redhat.com, gshan@redhat.com
Subject: [PATCH] KVM: arm/arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST read
Date: Mon, 12 Apr 2021 17:00:34 +0200
Message-Id: <20210412150034.29185-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When reading the base address of the a REDIST region
through KVM_VGIC_V3_ADDR_TYPE_REDIST we expect the
redistributor region list to be populated with a single
element.

However list_first_entry() expects the list to be non empty.
Instead we should use list_first_entry_or_null which effectively
returns NULL if the list is empty.

Fixes: dbd9733ab674 ("KVM: arm/arm64: Replace the single rdist region by a list")
Cc: <Stable@vger.kernel.org> # v4.18+
Signed-off-by: Eric Auger <eric.auger@redhat.com>
Reported-by: Gavin Shan <gshan@redhat.com>
---
 arch/arm64/kvm/vgic/vgic-kvm-device.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] KVM: Destroy I/O bus devices on unregister failure _after_ sync'ing SRCU
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12198889
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D36D3C433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:20:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B179E6128E
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:20:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343685AbhDLWVQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 18:21:16 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45630 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1343666AbhDLWVP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 18:21:15 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EE2C0C061574
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 15:20:56 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id v6so14111079ybk.9
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 15:20:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=CWYLK1Nq956lXK6/CZyqJrTCFyW3FBgUwDisoyLnoZE=;
        b=JAJOXTeFhWLgvXICg+LDvObGR5FL/FNB/jnOfdao44BEDtwrf2fTtD5Z/B54TyJuvX
         f1m6IQUxQ2aKUsN94lnQWCqu0sUeG96gXdlcegV5bn/XXC3dw3nDZfING2MtRD75cZ3w
         qYyHV/nZZ03WqXdRKUz6oVzcUTiXUdZck/6yTI+lOjFyA00EjBqJqZSY4p5I8IxXTRnU
         45PFjbzpcYriIeK1vtUmjM0IR6Rl2fGlxE4tJGMzBCLeyTQZldelPq1wlsGTwXtlLl8w
         Yc6sEDtkNLqS+krwgsLIh3nByT9Vv94t8B64o/uyFxDIA2+o2QRMV1rHA/NbJH8WY/7E
         MlvQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=CWYLK1Nq956lXK6/CZyqJrTCFyW3FBgUwDisoyLnoZE=;
        b=LL67C6brFJVCh6AxVHkPF60t/qYE+VC7vKQmoIq7/yjsbTAVMr6CnDgn8lD1Qw2+Ce
         340OnpNSSmDXLLLfZrAYp9QPV+i4VoArvzJcW0iabmBXPioXxE8R0WzfS4Un1+qws4oS
         Z6+R1PI0d/YZOUb/47//iTkZYm0zuvwqDlZNbHImgUBuunu535pxCnCYMvJ3NDqXCpA1
         clMTtJV7u8iwrLbIhYQBuDJL4Allevt7qQJ+rmbTedWua0CktLBC9q9G0a5PAUVihDv+
         lsk0WvZExFfOIVQ7vnOSZUBhibG0dq3JHYTawcyRwFocg8hhGCVi3peEJadZytRHgZwc
         SIrA==
X-Gm-Message-State: AOAM533xQAU3W5o7UhxpAwS4YoyKQN9RV8r+YFvT/Vbbkzi8A9/DafVr
        6QI2V7w1ewC31h36/2rPNJW4GuGQY4g=
X-Google-Smtp-Source: 
 ABdhPJwIxmb+XLWgx2RW89d77jd3AkTM4I4lGPEqIzhsdt9VwOq9Ll4tWQyfrDSEqTTpMdlUCP0VUNzutpU=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f031:9c1c:56c7:c3bf])
 (user=seanjc job=sendgmr) by 2002:a25:cc3:: with SMTP id
 186mr40287194ybm.178.1618266056256;
 Mon, 12 Apr 2021 15:20:56 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon, 12 Apr 2021 15:20:48 -0700
In-Reply-To: <20210412222050.876100-1-seanjc@google.com>
Message-Id: <20210412222050.876100-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210412222050.876100-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH 1/3] KVM: Destroy I/O bus devices on unregister failure
 _after_ sync'ing SRCU
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Hao Sun <sunhao.th@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If allocating a new instance of an I/O bus fails when unregistering a
device, wait to destroy the device until after all readers are guaranteed
to see the new null bus.  Destroying devices before the bus is nullified
could lead to use-after-free since readers expect the devices on their
reference of the bus to remain valid.

Fixes: f65886606c2d ("KVM: fix memory leak in kvm_io_bus_unregister_dev()")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 virt/kvm/kvm_main.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH 1/7 v7] KVM: SVM: Define actual size of IOPM and MSRPM tables
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12198963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 666A7C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:45:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 444446121E
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:45:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343826AbhDLWpZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 18:45:25 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:51046 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S241908AbhDLWpX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 18:45:23 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13CMdkDw170807;
        Mon, 12 Apr 2021 22:45:02 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=Qt1atT6nGnA+nSM5q2cYpnvhJ0KIkqhsM4wVk4kPLxc=;
 b=ztF5i0F1PpPj8ICWLCE6y+k/IhYCBt6/WJk2jjgNfsyDaOMY+GHsFbDzSxjwu7g4643h
 YTPe/yacgWQXsdlYetMvKNWY/oh1sKiv7ylCxhKuthKjUmZKADoFwEhYAs6E+mJnQSwH
 /HM3CBsazmAmW0EgHr9O2wjEwuvxa4llKH9LSnyWjjL5h2XwG+rHpK80HsNQa3Fa+Wsv
 t8G0gjy8DqX2/K7i+JlyDh7Er+Sb4QFzbkxtqW/xKV1WLjx4S5clHKoD2Hx4bnXuc6Kq
 ipSk2krCLIIaw0/XBKFc5i2jufdIis8uaDxd4PbTI5hugWZQlManK1E3YwCIFKMdvLqj kQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 37u3ymd9gs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 22:45:02 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13CMdc4E167396;
        Mon, 12 Apr 2021 22:45:02 GMT
Received: from nam04-co1-obe.outbound.protection.outlook.com
 (mail-co1nam04lp2057.outbound.protection.outlook.com [104.47.45.57])
        by aserp3020.oracle.com with ESMTP id 37unwxy5sq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 22:45:01 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BiYFTJyaEDNgPdT0zZSAf6cmWKMkTEZs28K06pgeyZ1NghDEElfkhZJHszbezbF0LER0LTiN5AznhIl8uVziU+iRIJoTyRUVyVVRIiKjyY2w3ziG4SyNrRySyElLWIdJz/lr8xC3LUxccCUrb596vhig9hjmyid/Xt2pwvLqJPvk4aZ7lPkid/V+1Tdg0ciFlwzB9cMEseFu5p/tsd6Rvu+qfrTO9KJD8Xp64EPxlWKiI30dO/bF7mFumpGFzNXN7VYkAib80U7p5TL7x2CsNC2eOeCHFRQJyajDX3fUhbtQ0ilPcdI848rYlqcQbg+JBbJJo5W91+H+ji4h55/DEA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Qt1atT6nGnA+nSM5q2cYpnvhJ0KIkqhsM4wVk4kPLxc=;
 b=I0HMAbiSlMgbQ+jg9tf7+pMks7qoxVkA6RIQEffco6bVUDRY0+dI+xkRmcY9CyGBTeetGAVng0NLX2/kJ3a6rZJrHTp/dhHC8LTSL199WdDFeES7WzwqhXXj0vwbqAmhNhuTfk9JxlX0ahVO4V0uDEKHCwIEDoukrDrFlrIe8MraYEA8LS/YIMz1rplilNgr0TTr7CozQ0N9j4eU9OnMn1jAxcMBYRx8bP0+km1E53CmmXurWai/ESxuRwbZJn60MpgA02WdjNITcNzWb01rRo/0bJaCp8uA7+7OMjlrO/cbGT7KLPB4PsUUMYdH6u0fv45GL/ZgXHp5QoIAhuuNmA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Qt1atT6nGnA+nSM5q2cYpnvhJ0KIkqhsM4wVk4kPLxc=;
 b=ykdGwppETaM+Cd7fngZi8W2MnaSswSQNgFR0kZcfwqjZA2R5Rcqib2R20rXKl0kxnoeMyhqqke3Nd/6j/RKeAfvPb1bb74t6lD+HDy1jTLBDZNx+3cUSxt+e3w4a/SxrIgPX7w86amaLaupTpC03gVbTeMhnRHQtaABhchOSdgM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SN6PR10MB3088.namprd10.prod.outlook.com (2603:10b6:805:d3::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.22; Mon, 12 Apr
 2021 22:44:59 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.4020.022; Mon, 12 Apr 2021
 22:44:59 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/7 v7] KVM: SVM: Define actual size of IOPM and MSRPM tables
Date: Mon, 12 Apr 2021 17:56:05 -0400
Message-Id: <20210412215611.110095-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210412215611.110095-1-krish.sadhukhan@oracle.com>
References: <20210412215611.110095-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BYAPR06CA0058.namprd06.prod.outlook.com
 (2603:10b6:a03:14b::35) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BYAPR06CA0058.namprd06.prod.outlook.com (2603:10b6:a03:14b::35) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.17 via Frontend
 Transport; Mon, 12 Apr 2021 22:44:58 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: dae410ed-f50a-40ec-ee86-08d8fe049a5e
X-MS-TrafficTypeDiagnostic: SN6PR10MB3088:
X-Microsoft-Antispam-PRVS: 
 <SN6PR10MB3088F2B846EA91DA12DDB46A81709@SN6PR10MB3088.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 fkyMPBlH1k+l0j+ITmm8JeEowPlITBNjxKpM+wb42o9ZYQxvt1G3euhHFFMPVHiItsEdvS9muCMjZ6frCAbHp721Fh98ITL3g4vWmJpmu8POfsEMLhiI8i8z3hNzQbgRP2CKUD4XxShk4BG8N2CCkbtFyfKyY00FXDDa7e7UY+msWzMNbqmr2FeatRe1O/QXaYKAjVPvlEivhwNlpZ3GRoUMQYGWQvb+vPTTvfpLHBBbVkc1cvLC/XdTfxILzFekNsHo5y6Gm8cCBPySC2bORWGV4joLgBT0k40XtXCYV6V23HfKThJoXTFgj2nsTeEujQ8jQWo8vGFHCkypPeW2zZ9iSB+DDw9QtC6NbN8nYwfK9g8uW+Mwro7dLxbLjiPs6ughsDJEDsohJMLDp/VzKt+ZUqk9iwIYNTXnhy9fGAdsTtaQxPUMq2oVFxZgHEsRPfPOTZ3EhFLGSRECzUCI1EDIFbiKXeQoV1qXXrNqyddwq8vZnmxj63OCKI065QlkGLVErPsqreTaNYwYlO589vQNCB1po3DLTVeeALOS8BKw4qoJHv/Fl0maSZ/Ovy1gNjTPyUpSKpKHGIFTaEWBzGjQxYUTV+9WOuCl2xJXDM2KK+A6nMmSX3omOMdWOOTN5S1UwMK6X2AWufWg2TxhJcj79ugf0Srk5ChpY4wUbQ0=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(136003)(346002)(366004)(376002)(39860400002)(396003)(83380400001)(86362001)(2906002)(956004)(316002)(1076003)(6666004)(2616005)(478600001)(4326008)(8676002)(7696005)(36756003)(6486002)(52116002)(26005)(5660300002)(186003)(16526019)(44832011)(66946007)(66556008)(38100700002)(6916009)(38350700002)(8936002)(66476007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 DIwURMVuPL/x+jon2lM3qDz4ZeK9Q4xJknOfNPiY4SBGc+jQIMgNu4PsvRGsnslAJKgRFsUwT0Oydc0e9cPTv5erPUnLKaNxfEeYCYPBj3bwyHtkVbzJpVJdxSB3lZLAMCqwNcf6BBSQMg7EuJyMOdsV3uYhMtTgPcWJZtjch1n8ce8n/LdHrjPyMrJzZL0tqyE3lyrGS/iJyJFGgHEPQRrfvAYF53WZzAyxMloP5CCCQ4hzOntbk7/g2RJypcKz2J6xKZVfwmONRGt9VjfH8OzMaXZaEtir1OFNMBrtp88hT1pePzcv2jyakwHmvqhYhniaHkS5iOmaT2gKBFFuqq4eJp8mQNSnEN5bfQQzHidNcqAnKk4Rapzen8im+U49iWW6jteN/ZtSN85c+EZutfCZ4z4bO9Uwl65tcRPSz9x8RuElSOo8t+9I/3OUwxNj8iIMoCX5aVSZ/g4d2To+v6z2DweXbLQrcxNVUH8yD2VUh3a4A+IvTbvN/idKfKF1VyFTSzUGP9GO8thDVDwWt0y8iytYsp/N5O4TZtnf/XX77lPkGv//1z/fdig3jRtrVgCmhu0+bFTUQPLIOkRSQTIdUHxFle4snjbq2duiHrMgnRxIaQ22dS7gCon6HdJ+RaJAxnJCZ7ryUAahtX5MxPj4xLgdUobCckMHH547ZmEw6qI1hQYlU4WfK/dcq9zN3e5qarbZSOaNtCb/B36ZWdUcHG8j9pZFUUtdNOkX/xMrrT1itk6P/ewmPctGDbMy2lWG1e3R5AW+ZAPcH9tZUzRyedzNU/WQGAiuu61ZANkmZL0sqUWiqA+v9yEKvswnBklSv0gBvCiqhgtPhV4thDt+sbwcfxaHIqzVttmhpEpWM3XnH3hBEtsyOI6i4SPRYJ/VeVN1ko5RCGaknHoOcLEc+PJ7oRDVOX7Gnm9DNtFS+3Up2ByJvWv6g/7Qgx2CFHYTBIfz+vQQmwK3x9JOV1m8OKjW5x6/ybt6zio5J/8jnnqkUWJ95/5MmU+NJ8k1d4PKoCt4waKWgACC2iOPTnXrUAL9nRoweugC2FLZsO0hRn2IJs3c/CC002bq9sfYmAfhDOOzf8l98ydKc9wKSCkHxUEpTq8mGrlzdwksl4OrRmaeHd1uufHe31vYqzfOQACHqJur/AITBi0Css/uBgnFt7OGJdrzJ16Vz5ZnOQaU1XUhSDTjPnmOMIUBPRfXvxJ2R9Co3hNTVDk8V7SKAg42M/tt5ivMgc7rOwMpjjDsX4l+TaYAn8aHQlaGsHpqTR3uosF2qc45D9Pcb7VLkUNoCsBqeSOqQct/olETMyOxaeSq1fIDbM//23TI0Cgh
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 dae410ed-f50a-40ec-ee86-08d8fe049a5e
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Apr 2021 22:44:59.8041
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 eTYcRd46ahDbe4Lq0BWHfvq/fHdwFyGHrW558DpDVD4FKj6duxJHX91nB/IpkisVSTc7+fP+3udJl7rLTAp7ld9nRS8SxBvVH8RBb8d563o=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR10MB3088
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9952
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 suspectscore=0
 mlxscore=0 malwarescore=0 adultscore=0 bulkscore=0 spamscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104120146
X-Proofpoint-GUID: q9E_KlsPAMBV-ZODUvwACm_6wFYLe7EJ
X-Proofpoint-ORIG-GUID: q9E_KlsPAMBV-ZODUvwACm_6wFYLe7EJ
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9952
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 mlxlogscore=999 spamscore=0
 impostorscore=0 priorityscore=1501 lowpriorityscore=0 adultscore=0
 bulkscore=0 phishscore=0 suspectscore=0 malwarescore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104120146
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Define the actual size of the IOPM and MSRPM tables so that the actual size
can be used when initializing them and when checking the consistency of their
physical address.
These #defines are placed in svm.h so that they can be shared.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.c | 20 ++++++++++----------
 arch/x86/kvm/svm/svm.h |  3 +++
 2 files changed, 13 insertions(+), 10 deletions(-)

```
#### [PATCH v5 01/11] KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12196773
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4AF4CC433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 04:21:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14ADA6120A
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 04:21:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229879AbhDLEWM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 00:22:12 -0400
Received: from mga07.intel.com ([134.134.136.100]:53368 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229865AbhDLEWM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 00:22:12 -0400
IronPort-SDR: 
 OivJrluwVec8F0ZSL8xH0bhXcNQnliwHZGgRTXuiwdddxh5aUqyeyISw2yPt8owCFjO/tZfFbu
 cns8a1bpmZAQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9951"; a="258083739"
X-IronPort-AV: E=Sophos;i="5.82,214,1613462400";
   d="scan'208";a="258083739"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Apr 2021 21:21:54 -0700
IronPort-SDR: 
 /1PtQ6lEtz+xxvmcOCDOQDRSMQuDhdXF6/1T50uOup//IaOOCEK9xP2KV5G3/Gf+7tb4nPOTmy
 Ts5N/gtzoE9g==
X-IronPort-AV: E=Sophos;i="5.82,214,1613462400";
   d="scan'208";a="521030346"
Received: from rutujajo-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.212.194.203])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Apr 2021 21:21:51 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, linux-sgx@vger.kernel.org
Cc: seanjc@google.com, pbonzini@redhat.com, bp@alien8.de,
        jarkko@kernel.org, dave.hansen@intel.com, luto@kernel.org,
        rick.p.edgecombe@intel.com, haitao.huang@intel.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v5 01/11] KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}()
 for SGX (VMX)
Date: Mon, 12 Apr 2021 16:21:33 +1200
Message-Id: 
 <02f37708321bcdfaa2f9d41c8478affa6e84b04d.1618196135.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1618196135.git.kai.huang@intel.com>
References: <cover.1618196135.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Export the gva_to_gpa() helpers for use by SGX virtualization when
executing ENCLS[ECREATE] and ENCLS[EINIT] on behalf of the guest.
To execute ECREATE and EINIT, KVM must obtain the GPA of the target
Secure Enclave Control Structure (SECS) in order to get its
corresponding HVA.

Because the SECS must reside in the Enclave Page Cache (EPC), copying
the SECS's data to a host-controlled buffer via existing exported
helpers is not a viable option as the EPC is not readable or writable
by the kernel.

SGX virtualization will also use gva_to_gpa() to obtain HVAs for
non-EPC pages in order to pass user pointers directly to ECREATE and
EINIT, which avoids having to copy pages worth of data into the kernel.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kvm/x86.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/6] KVM: x86: add an emulation_reason to x86_emulate_instruction()
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12198021
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 53042C433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 13:09:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EE206128E
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 13:09:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241805AbhDLNKH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 09:10:07 -0400
Received: from wforward5-smtp.messagingengine.com ([64.147.123.35]:38679 "EHLO
        wforward5-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241764AbhDLNKE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 09:10:04 -0400
Received: from compute7.internal (compute7.nyi.internal [10.202.2.47])
        by mailforward.west.internal (Postfix) with ESMTP id 388C41646;
        Mon, 12 Apr 2021 09:09:44 -0400 (EDT)
Received: from mailfrontend2 ([10.202.2.163])
  by compute7.internal (MEProxy); Mon, 12 Apr 2021 09:09:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :in-reply-to:message-id:mime-version:references:subject:to
        :x-me-proxy:x-me-proxy:x-me-sender:x-me-sender:x-sasl-enc; s=
        fm2; bh=rxrObZQedU/z7tCgm77WVlD0YetrXNOgn2ee61sfp4A=; b=joNyhsO/
        3wrGui5X+5el2vu/d76fkIdTYIgjhtWpcos5V8fuUWdrIJtIBsItrBWU3ZNRBqVP
        BQLJngzpyReV6PH+1j9ezqNaeU0M/lIYD4fyVYF9URb9xR5NTiyU/0eCq13SI3H3
        sVqBAz0S12xkRrfIwx1chSdrj6CSiSreSYfadhNzSNh22nbCb84TkRIkA2iUQ5Ki
        z2Yeu2uaE8BVr+sOquxppdjbO9f0Ff6e5SfOjHqcSJOX77vn/oc/usKrKheNeNRd
        tcllnQPaiH89VjrzdcSu8Ez8RHLyVdkONUq/EqmntnLDO0HQC9xN9em/gGf9Knt2
        Z0P1SSI15HsCbQ==
X-ME-Sender: <xms:lkZ0YHhet6EMe3ntOBcMSjYkGIepSs4zy7zw4DRTDE03DuUGrnds4g>
    <xme:lkZ0YO8nw0-W32WlqIt9OFFxR4MJ7DAHqFTuvOAtR-prcf0QQYz62weS1G6sHpDcj
    fPCt-3pl2GUlQ65xRc>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrudekjedgiedvucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffojghfggfgsedtkeertdertddtnecuhfhrohhmpeffrghvihgu
    ucfgughmohhnughsohhnuceouggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrd
    gtohhmqeenucggtffrrghtthgvrhhnpedufeetjefgfefhtdejhfehtdfftefhteekhefg
    leehfffhiefhgeelgfejtdehkeenucfkphepkedurddukeejrddviedrvdefkeenucevlh
    hushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhmpegurghvihgurdgv
    ughmohhnughsohhnsehorhgrtghlvgdrtghomh
X-ME-Proxy: <xmx:lkZ0YGExVWz5KV53CtYLxQxZtEvovG7Q08ThJTXn0jDHzdHjyM3ApA>
    <xmx:lkZ0YJkw3Uxz6j5-BG1gtMDoBIM4v_TNnDnRZKw4zil5z8MwyQvxZA>
    <xmx:lkZ0YCYDJ9r9jCMZRPXfNCeMJL1U8-vjP_bUMrjAMnUKI01SKt0oCQ>
    <xmx:l0Z0YOtHNEL0XOeS9hqqQLN1uRaXPAIMpfrQxtnsxzpALB0BHAyZLY3Lmhoz4WVQ>
Received: from disaster-area.hh.sledj.net (disaster-area.hh.sledj.net
 [81.187.26.238])
        by mail.messagingengine.com (Postfix) with ESMTPA id 02AEE1080066;
        Mon, 12 Apr 2021 09:09:40 -0400 (EDT)
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id f21f3cb5;
        Mon, 12 Apr 2021 13:09:38 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH 1/6] KVM: x86: add an emulation_reason to
 x86_emulate_instruction()
Date: Mon, 12 Apr 2021 14:09:32 +0100
Message-Id: <20210412130938.68178-2-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210412130938.68178-1-david.edmondson@oracle.com>
References: <20210412130938.68178-1-david.edmondson@oracle.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joao Martins <joao.m.martins@oracle.com>

Emulation can happen for a variety of reasons, yet on error we have no
idea exactly what triggered it. Expand x86_emulate_instruction() to
carry an @emulation_reason argument.

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 arch/x86/kvm/mmu/mmu.c | 4 ++--
 arch/x86/kvm/x86.c     | 7 ++++---
 arch/x86/kvm/x86.h     | 3 ++-
 3 files changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH v5 1/3] Linux headers: update from 5.12-rc3
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12197795
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0E091C43460
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 11:45:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB7F26124C
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 11:45:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240550AbhDLLpr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 07:45:47 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40952 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240502AbhDLLpn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 07:45:43 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13CBXsLx034073;
        Mon, 12 Apr 2021 07:44:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XH41vIKQPXVPDTcuOx2GPyt+VwfndhJWpB7omC2dJ1U=;
 b=Tpxzw7+ji3uO2PJ9CijNg840tJxACKR0gLY8/6y6SrdI7Yyph2VFvrTC2OiMjp+fu0N5
 FImAnr68yYUCKsaYci/IADei1c3vt4oUCNkHV27t119Upc3Zuw0R4lNExQIuFoKdqwmH
 EBJOoh//0JX1N3SvYoC/1szzWBGNPXoLXuDwJ8XUBr37zdQF3cySMeBiGaTL4X9WTnsk
 Tn183YOCQ7zlrRmekiy7nC0xxTYja+TIswAmf9ytXt+tU3AEDqxTR3xQLhooA5ht0YDC
 IMnmzb6gm/3hKElLCvEM9uJ+zWYr9M/nsbVyVpo2qll2Ti0SZmCXe/sNhhVlOmHFkbii Tw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ushvs0su-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 07:44:47 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13CBZgC5040506;
        Mon, 12 Apr 2021 07:44:47 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ushvs0rt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 07:44:47 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13CBhIGU021621;
        Mon, 12 Apr 2021 11:44:45 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 37u3n88wvc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 11:44:44 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13CBigIS46203250
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 11:44:42 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 29EBBAE055;
        Mon, 12 Apr 2021 11:44:42 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D17A7AE045;
        Mon, 12 Apr 2021 11:44:38 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.37.145])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 12 Apr 2021 11:44:38 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com, groug@kaod.org
Subject: [PATCH v5 1/3] Linux headers: update from 5.12-rc3
Date: Mon, 12 Apr 2021 17:14:31 +0530
Message-Id: <20210412114433.129702-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <20210412114433.129702-1-ravi.bangoria@linux.ibm.com>
References: <20210412114433.129702-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: ziR8cwdBWjqTP8omL1y21yLw309mnuAc
X-Proofpoint-ORIG-GUID: T2freNY9MB-HOqZjTI8zYcDD7C1pF7Oy
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-12_09:2021-04-12,2021-04-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 bulkscore=0 clxscore=1015 mlxscore=0 malwarescore=0 suspectscore=0
 phishscore=0 adultscore=0 priorityscore=1501 impostorscore=0 spamscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104120079
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Update against Linux 5.12-rc3

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 18 files changed, 161 insertions(+), 4 deletions(-)

```
#### [PATCH v3] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL commandFrom: Steve Rutherford <srutherford@google.com>
##### From: Steve Rutherford <srutherford@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steve Rutherford <srutherford@google.com>
X-Patchwork-Id: 12198729
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0738AC433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5E1860C3D
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:44:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S245463AbhDLTov (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 15:44:51 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39508 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237467AbhDLTot (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 15:44:49 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AC88BC06174A
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 12:44:29 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id p75so7630863ybc.8
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 12:44:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=/8EkO2XpIPXcNEfhUs0PL9HjG4CvnSZ9tVEjZh4FrjQ=;
        b=S0iQUxgzZCycSQe3SNyXbIJuej2vlR0NuxrshrOGKhJLLvXPGhDyVZG8IQxuuItysR
         JvVFuwHey6/CIIEmRA3z0yoeyxsl51Y8A78QwLPge3ayY1LxPxecZTzGMQQ7f33wNKwn
         DcFM+V98n1ZzgZVsyXKKRQzZCHl03R25m3DcIGPNfOXxYJspv3HDKjRYd90bxOX5SzNq
         lwN7J3XdrE9Tmas/aIBtkkaWOB5U7o1c1IAdCAEjxMNYdxLP7o0bqrnxvPJYZVSpYu+9
         HzxBg6elw1AxIrzydhstSW4SvvFZQuxWVbQm3gpGCDNtGGzH0y3xJxSlfnROCbHaWmBX
         Ebcw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=/8EkO2XpIPXcNEfhUs0PL9HjG4CvnSZ9tVEjZh4FrjQ=;
        b=epbxuom5eLy+BHUMu0OkosNkSmXsPoBH0tKbJQRX19vKS4iVB5Wm/pPibe2OG4sivg
         n5jZktbOiYPn/jbfYbcwRSVrGRSIW5k6o+r/fm8x38WuonZUl1uuYT9g8eqlV+NF2av9
         uzPCbB/Wk5QxKTH7prTp19uTNpONy+qGRzxkm0QgWDQuti1Gp24jxnHxXl8FnvxkxViS
         wPP8ifDTjHlaLqtwbGpt69uueeOV7/ZFGQ0IYPq+2XohRskl2Egvb5kL4dzKDr5LqNGB
         zgcuuJroibJTMgqPu9dYSNJ/gFsk4Z+HULMYZNYaYRTfqG2VIVMTLzXZ7KxPuP/G7yta
         qGog==
X-Gm-Message-State: AOAM532C8M1V7z00vM3yYXvEl7UKJfs2ROH4gV7FZzuEgWBQ9KmX5xTV
        SM98Pfvy90GN2HyRXeaVRcL0H9BXjnkhrUxI7frgzsYP908eFSq/dmqnz6LuEqce8iowHA6tVCD
        bzv9GqgyxDDmdyrHjxw+MvMe1pPPWyYkTBJFABlzdDWjy78W3kDoQu7rzBhuh4bsv2XTebao=
X-Google-Smtp-Source: 
 ABdhPJwNI+9lyvZ0DJiIr2W5uyQ2D6wQHUegyqjJ6pJ+Q7kPEyT/XSIKzfs1B3pw2DkRPG7h7d0DT5MKnQ9V/YVSKQ==
X-Received: from riemann.sea.corp.google.com
 ([2620:15c:158:202:d03b:94af:33cb:27b9])
 (user=srutherford job=sendgmr) by 2002:a25:af0a:: with SMTP id
 a10mr39867011ybh.390.1618256668824; Mon, 12 Apr 2021 12:44:28 -0700 (PDT)
Date: Mon, 12 Apr 2021 12:44:08 -0700
Message-Id: <20210412194408.2458827-1-srutherford@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH v3] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL command
From: Steve Rutherford <srutherford@google.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, natet@google.com,
        Ashish.Kalra@amd.com, brijesh.singh@amd.com, pbonzini@redhat.com,
        Steve Rutherford <srutherford@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After completion of SEND_START, but before SEND_FINISH, the source VMM can
issue the SEND_CANCEL command to stop a migration. This is necessary so
that a cancelled migration can restart with a new target later.

Reviewed-by: Nathan Tempelman <natet@google.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Steve Rutherford <srutherford@google.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  9 ++++++++
 arch/x86/kvm/svm/sev.c                        | 23 +++++++++++++++++++
 drivers/crypto/ccp/sev-dev.c                  |  1 +
 include/linux/psp-sev.h                       | 10 ++++++++
 include/uapi/linux/kvm.h                      |  2 ++
 5 files changed, 45 insertions(+)

```
#### [PATCH] vfio/iommu_type1: Remove unused pinned_page_dirty_scope in vfio_iommu
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12196685
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE630C433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 02:44:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C494861206
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 02:44:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236640AbhDLCoy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 11 Apr 2021 22:44:54 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:16891 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235954AbhDLCox (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 11 Apr 2021 22:44:53 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4FJY1b2zRtzlWjc;
        Mon, 12 Apr 2021 10:42:43 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Mon, 12 Apr 2021 10:44:25 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
CC: <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [PATCH] vfio/iommu_type1: Remove unused pinned_page_dirty_scope in
 vfio_iommu
Date: Mon, 12 Apr 2021 10:44:15 +0800
Message-ID: <20210412024415.30676-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pinned_page_dirty_scope is optimized out by commit 010321565a7d
("vfio/iommu_type1: Mantain a counter for non_pinned_groups"),
but appears again due to some issues during merging branches.
We can safely remove it here.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---

However, I'm not clear about the root problem. Is there a bug in git?

---
 drivers/vfio/vfio_iommu_type1.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] vfio/pci: Add missing range check in vfio_pci_mmap
##### From: "Christian A. Ehrhardt" <lk@c--e.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Christian A. Ehrhardt" <lk@c--e.de>
X-Patchwork-Id: 12198879
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.2 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_SANE_1 autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 535D7C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 21:49:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2798661350
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 21:49:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241243AbhDLVte (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 17:49:34 -0400
Received: from pmg.in-ulm.de ([217.10.8.27]:43798 "EHLO pmg.in-ulm.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S240316AbhDLVte (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 17:49:34 -0400
X-Greylist: delayed 470 seconds by postgrey-1.27 at vger.kernel.org;
 Mon, 12 Apr 2021 17:49:34 EDT
Received: from pmg.in-ulm.de (localhost.localdomain [127.0.0.1])
        by pmg.in-ulm.de (Proxmox) with ESMTP id CFE1720C62
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 23:41:24 +0200 (CEST)
Received: from mail.in-ulm.de (unknown [217.10.8.10])
        by pmg.in-ulm.de (Proxmox) with SMTP
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 23:41:24 +0200 (CEST)
Received: (qmail 343850 invoked by uid 10524); 12 Apr 2021 21:41:24 -0000
Date: Mon, 12 Apr 2021 23:41:24 +0200
From: "Christian A. Ehrhardt" <lk@c--e.de>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org,
        Alex Williamson <alex.williamson@redhat.com>,
        Alexey Kardashevskiy <aik@ozlabs.ru>,
        David Gibson <david@gibson.dropbear.id.au>,
        Michael Ellerman <mpe@ellerman.id.au>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] vfio/pci: Add missing range check in vfio_pci_mmap
Message-ID: <20210412214124.GA241759@lisa.in-ulm.de>
References: <20210410230013.GC416417@lisa.in-ulm.de>
 <20210412140238.184e141f@omen>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20210412140238.184e141f@omen>
User-Agent: Mutt/1.5.20 (2009-06-14)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When mmaping an extra device region verify that the region index
derived from the mmap offset is valid.

Fixes: a15b1883fee1 ("vfio_pci: Allow mapping extra regions")
Cc: stable@vger.kernel.org
Signed-off-by: Christian A. Ehrhardt <lk@c--e.de>
---
 drivers/vfio/pci/vfio_pci.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost-vdpa: protect concurrent access to vhost device iotlb
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yongji Xie <xieyongji@bytedance.com>
X-Patchwork-Id: 12197509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 01FF3C43460
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 09:57:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CBD926120B
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 09:57:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242489AbhDLJ5T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 05:57:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50956 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S244782AbhDLJ4k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 05:56:40 -0400
Received: from mail-pf1-x430.google.com (mail-pf1-x430.google.com
 [IPv6:2607:f8b0:4864:20::430])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 60645C061363
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 02:55:49 -0700 (PDT)
Received: by mail-pf1-x430.google.com with SMTP id d124so8840256pfa.13
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 02:55:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=WGhAYrLlT6jJ3oarrFVLtGbJxuwlJT0uonwBC7CFB2c=;
        b=SYlBPXS/JHASqZqUy2bndiWwD9J64xNpFzs6QmK/6Jw9e+EqDlRqCak4xTqYyyAaXb
         Al84xZ3Eu6eZxwmq1TET2MmneFe9K2wVlz89JdKUfWe6Tbmk8FowfLEhXSV1HTM2oEcK
         xaQKh6dcWHuKQ0f2GqecgMP2uEgHZZj2cEG9umf3bqJMSZiaDX5+QUMCDzC/dpOiMaVH
         ALr5bIKUXbb7foGQFxhkDzsAloZPjTp8aZ7kBwWLCiffI1gn3VL9/BGX1/VbRu7DeT7B
         lcZT/oD92iq8q3TtAQ5xcR6VuX9noaKNCgzy1cn/b/Q7VT/STQVHJZzeOAq0XR1LJUCb
         mFrQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=WGhAYrLlT6jJ3oarrFVLtGbJxuwlJT0uonwBC7CFB2c=;
        b=uGuRAiLmuJ2x18pgknk4eeXOS/nSkbPLp2rYVVia9VzquXyAx3FuCwaiMUgVqafPTW
         WbRKAEDiLcR+rQjaPhmTaAUpExPxrZWGpgY80V77/y+Nme9Q71UjP/rqGKXS26Xn/wPD
         ds8jTjhr+USz11YJ2Y92sKyWnVJx77/dgq3cmI2BJI++5dUPrTszb1q84uu7k+Rml+Ss
         drpZcweINMpmoVnNCsNJb4v3iALUlkcfDZVMvs5Y4azwLrAG7SAr1kN/pABdFg1key9X
         0mYeFlZPjnIR/REaE2ZOwrrZaIT6kjSMMfxzS1GJZwIkQBNnl/zRl2lDSJtpMGkbQMW7
         rtiw==
X-Gm-Message-State: AOAM532GU7nD3UlVVQp//BauVF41lWyRHCHJJ8+jQC74m9w6hc9m8Yaq
        RVGe5Q4Bxct0IpOdV8g+qPr9
X-Google-Smtp-Source: 
 ABdhPJz5uYW2po0H7GJV6ejIQK6lDJip/OMuXP1SmWDv+/aL39+O72IuEqq1fcdU2YBURx0p/Ca3Jw==
X-Received: by 2002:a63:1266:: with SMTP id 38mr26228922pgs.427.1618221348945;
        Mon, 12 Apr 2021 02:55:48 -0700 (PDT)
Received: from localhost ([139.177.225.243])
        by smtp.gmail.com with ESMTPSA id
 h25sm6470647pfq.152.2021.04.12.02.55.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 12 Apr 2021 02:55:48 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, sgarzare@redhat.com
Cc: virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH] vhost-vdpa: protect concurrent access to vhost device iotlb
Date: Mon, 12 Apr 2021 17:55:12 +0800
Message-Id: <20210412095512.178-1-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Protect vhost device iotlb by vhost_dev->mutex. Otherwise,
it might cause corruption of the list and interval tree in
struct vhost_iotlb if userspace sends the VHOST_IOTLB_MSG_V2
message concurrently.

Fixes: 4c8cf318("vhost: introduce vDPA-based backend")
Cc: stable@vger.kernel.org
Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vdpa.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
