#### [PATCH 1/4] KVM: x86: Add AMD SEV specific Hypercall3
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12219185
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E1E4C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 20:55:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C6FE6141C
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 20:55:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239429AbhDVUz7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 16:55:59 -0400
Received: from mail-mw2nam10on2083.outbound.protection.outlook.com
 ([40.107.94.83]:4386
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236851AbhDVUz6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 16:55:58 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ihYzj1KyF+R2qIlmdy+Cbn0r3XvoN/6UGy5Jh5PmRiWAWyaaQ5Tbh8GCbCQmk8y0T7xgtzfHri5zpYL8zZyDmn3Sk/UCunTFGbMNTx/u20dSe2USuADR66lGf9/veKNHSHn1M2PO1hm8JOY4hMVJzKVmv4hRalOGKs0UAG3V09LdMlRWqUYjck60lJ+O02dZDT+LRj2knWgUi2QMeIgv0yQdGVt7t5j4gqK/ojdny7XLPLTFKohg15UrUoLfy41jHJFhk9ZyaRjklSGXNFePMn/wbZpMiCO9gMk1t81ibKjVuZatChn78B6DhfVY0KrOBqftDcpRL3XwHr5KE56r1Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=djYOIZIAe+UUpzeBZtr/RMxOzG5cL+NruPXwZsscQuI=;
 b=iUr+YNq2lGi2pVeDjwZUXD6aNHOaz84tJEA4ZB6ts3V4+PTMUrzNPqL1B2PF2azGVpeq8or+q1jtJw9/QnEQJ+SPTUWhU0HosJJkVOUkGq9d2iAbhCxqwAnlD5oIj/qm6UiI75D7w23yjUGojIKNMGHuzieLhviHjCm7dTePqY8WgAVdj7W2V9XPdOnih9kYgjaLkh+KkoPoLUJ8wElNR5l1bVc/IVLPImkyrWyA3Fnu9zmVTfMZLPHxJWSvrinrI1Xndy1t0L6n+xGnOCEGFo5sgDtKBTurhcag3PoA+eV9BqP6nJUBr8SRfvk4J9cxoIEyi+h+X4jBBAw80BDpeA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=djYOIZIAe+UUpzeBZtr/RMxOzG5cL+NruPXwZsscQuI=;
 b=rty4HZjtL7o6H++9pS1E3JxG9eRKjgKk08oP3yCxRYUdJHZ0se0cV9tPgkww8fCr9gO+ax8NmTMcJJ2BR7ZNctEr3a76I0kVGn7C8OZ46oDHJMh6vLa/Ozf4/L2++O0+bmJNjLrEF+3G4nl5QP37Vrqi/oTw7o8mJMplUqq/dZs=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4510.namprd12.prod.outlook.com (2603:10b6:806:94::8) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.16; Thu, 22 Apr
 2021 20:55:18 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%7]) with mapi id 15.20.4065.021; Thu, 22 Apr 2021
 20:55:18 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH 1/4] KVM: x86: Add AMD SEV specific Hypercall3
Date: Thu, 22 Apr 2021 20:55:08 +0000
Message-Id: 
 <c33adc91aa57df258821f78224c0a2b73591423a.1619124613.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1619124613.git.ashish.kalra@amd.com>
References: <cover.1619124613.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0601CA0019.namprd06.prod.outlook.com
 (2603:10b6:803:2f::29) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN4PR0601CA0019.namprd06.prod.outlook.com (2603:10b6:803:2f::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21 via Frontend
 Transport; Thu, 22 Apr 2021 20:55:17 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: a707d165-cdba-4cdc-a5c4-08d905d0efa0
X-MS-TrafficTypeDiagnostic: SA0PR12MB4510:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB45106B092D0B7E83C013DB5B8E469@SA0PR12MB4510.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3513;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 b+9nIYVDp0t5JD7gkDr9gOFY+McH20zJbHw8juyiHlftpA9d8VKZH1l5AqmO123IyIdzokAax4fF+se7edefGU5PQuEiYc164NmANgcNO2vEuPryCHoycB3hzfoxBxX18VQuz6iJWBAYz6wyjR2Eycph/Dh2lclH/EJjPu99ApWX6lLtsj+cjYJaaMVwRGEjt0y18M4eQQ1C0BzPg4DQKFHH8nSQOTi6wD9j5ppHyh61wn6unp0+3UKHAIxQUd0adChbQRqm2W56xSntphuOT3k74Xex7CBbrffJI2tyaCJpC7huc+NDQnNIWjDv7RP6QRIBPCT8ErdP2MM90kglNdu/Ch3tPfKlQEWE3pgZdOqPkWerOSMKdj0/WfhUru0033z88tnUrSKtExb0Pj+7XaspT4AuCFqARBdGwKhMfVe2dksInO6YChOkRB/Qz7nF/JKBKdnS3t7nBREXlBcZmIA78j+D4zsC9Ibu3CZmhifcNGp5DnCA1YAn3bNK/KkGLf79r18vYzg7tKenkn5mbie5Oybslu4niCIsfI6WksvyhIzmL2dP8t+Lziuhwr7jRW7DKQISskf9JwQLxLnGw6L2FdxggkOzFcma5o82+UmpgqnYO+sndoyZnz0gG2g+hlcwQJ4tW9PLTwka91flFg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(396003)(376002)(39860400002)(366004)(346002)(6916009)(66476007)(36756003)(38100700002)(8936002)(956004)(5660300002)(38350700002)(4326008)(6486002)(26005)(16526019)(8676002)(478600001)(186003)(2616005)(7416002)(86362001)(2906002)(66946007)(52116002)(7696005)(316002)(6666004)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?GmkBqaYFkUISy4aYVGFSYZatUd42DO?=
	=?utf-8?q?hVjscL7cvHvhVYrcBAGCezpL3D796g7zVFzE5VDH98oQ9kQeUElh3EycMJe1EVsgE?=
	=?utf-8?q?kHBJKMbO98aSNm/tgpyJ+4FkQrcuPCDyDXt+r0cQEZBQura+ISpF97SeHlJFxoVKq?=
	=?utf-8?q?bykuLzdruKgHNMbcpOzq6HPAkAeP3f/RmtFFoO1sgzB2E7FtC4/cSouCtoRjLqm0A?=
	=?utf-8?q?JXh74NARwT6i8eGYjDzukZS1hcOZzqe9qXINBoCMcXfVvxbc16yT821L0VBJTKqm3?=
	=?utf-8?q?bV3b0Zjfys6gNiNDV84qcT09KwqDe5wgsvsc8RbXNosZABiACd+VtzbyhOZ0xi2FM?=
	=?utf-8?q?uN4C+mAnNrGE7zndKh7oZhhuWpJhaSD85bhCQiJFimwa2Nm7c4oncyR3vNsvQJdti?=
	=?utf-8?q?bYRurUhLLTjfBiwEuQ+/aMgRapedPU62PGf8XkRw2B2nk+S/RZmM/KMLTJpTL23ju?=
	=?utf-8?q?UJcvl5EqX3/XPaf2lC/1t2bU1GbUvW7RywSEP72qisEZNgmo0c6H96TZZVoazt+uW?=
	=?utf-8?q?DA7UXQfwp1Nm30mKd5i76PkeMS1x0keHUS6AfpVuL63soSS+CfKcUHFlq8skwfQy1?=
	=?utf-8?q?FbTZ5rA866SYA2g1qQ+EUEqkSqYFBQ33calPdP+GMwaKvTddklydPFCXG9ZOHXCqO?=
	=?utf-8?q?8YPcT3VYkN+qdEn8jUgym40+OTvox5tXYLQ2f6WkVyvmtz2t0NcOn8Wbiah6bR0yZ?=
	=?utf-8?q?cv/abpqGWXtDHEoWYzWX3TrJiytfjiES/JkoE0vgAqnKNnmy/b79v+Vig1v4tByuT?=
	=?utf-8?q?qRsQ6UzsKisV6cTvAYjYvPaCdYYXnbIzBJxH2Au0Qx/25TPR60aD0wSCpItciviIb?=
	=?utf-8?q?T0NDOaZFofLjB5fjXkj2illmce2hJSq3SMoo8rWP6l9Jcqw9IYSowdjK/UVTiYPdi?=
	=?utf-8?q?kXhubNwng5C5LAPNuVTLJfE+k6cuQ5/BUPGQRApMejZ5sKGNcwSvhzdyLXhsN+plN?=
	=?utf-8?q?6TFPvg4Xk9syFMd1L9mRZR/Fa2NgZGTJup56/R6aRO418uZv8cgoTSYXOc3dahDWy?=
	=?utf-8?q?sISU06qYRu0ldNuhk+nmWXVaNAOFKGW/mAiWvCgZWvAOfqm812Zrhj2jA/RwqhXIo?=
	=?utf-8?q?I0jQxIq8uWbDiPi0WSYNTEhPywbs6uHzJ/7RGhDwItTx6cYhJZHczBZJuwzapsKgN?=
	=?utf-8?q?i7SG38popjRbIr2TjtO5SSp+fATtEyedGdqBq/vHhZDW3EZpwqZFRlUnyTZ0HjcLh?=
	=?utf-8?q?BFsFv9q9bfUaGvNzWGFctcTqT37PmXEwg2qdx+//XH3gfckEOG4JyvWdF0wMViy3z?=
	=?utf-8?q?CF99AQD2fh7re/?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a707d165-cdba-4cdc-a5c4-08d905d0efa0
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2021 20:55:18.2514
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 D0qh8AaygUgNY91Y8mwP1dS7vLYDeW9SC8HHWvik6YxGQSNfMdLvxjjOxyq6luKw7WQXmHrkEY+XTZGLlw/7Sg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4510
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

KVM hypercall framework relies on alternative framework to patch the
VMCALL -> VMMCALL on AMD platform. If a hypercall is made before
apply_alternative() is called then it defaults to VMCALL. The approach
works fine on non SEV guest. A VMCALL would causes #UD, and hypervisor
will be able to decode the instruction and do the right things. But
when SEV is active, guest memory is encrypted with guest key and
hypervisor will not be able to decode the instruction bytes.

Add SEV specific hypercall3, it unconditionally uses VMMCALL. The hypercall
will be used by the SEV guest to notify encrypted pages to the hypervisor.

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
 arch/x86/include/asm/kvm_para.h | 12 ++++++++++++
 1 file changed, 12 insertions(+)

```
#### [PATCH 1/2] KVM: VMX: Keep registers read/write consistent with definition
##### From: Yang Zhong <yang.zhong@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Zhong <yang.zhong@intel.com>
X-Patchwork-Id: 12218149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0F422C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 10:05:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B510E6145A
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 10:05:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235776AbhDVKGI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 06:06:08 -0400
Received: from mga04.intel.com ([192.55.52.120]:61845 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230365AbhDVKGI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 06:06:08 -0400
IronPort-SDR: 
 Ra5cdHO+EnC+jI8TotVuI/Y38d+56wCkQxNG7HGyZIB/tmdZGNvknwi5wAkrEQszL+OYJbgz2C
 BGCL26cWg7jQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9961"; a="193741594"
X-IronPort-AV: E=Sophos;i="5.82,242,1613462400";
   d="scan'208";a="193741594"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2021 03:05:34 -0700
IronPort-SDR: 
 1dY0dZtYItqsDBSd4QVe4rceXdSVeWHvuwKWlec2TwK7z2K0Oks+alxsCUmH009Xf8uUwP534R
 29RFLsMB8HXw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,242,1613462400";
   d="scan'208";a="421317119"
Received: from icx-2s.bj.intel.com ([10.240.192.119])
  by fmsmga008.fm.intel.com with ESMTP; 22 Apr 2021 03:05:32 -0700
From: Yang Zhong <yang.zhong@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, yang.zhong@intel.com
Subject: [PATCH 1/2] KVM: VMX: Keep registers read/write consistent with
 definition
Date: Thu, 22 Apr 2021 17:34:35 +0800
Message-Id: <20210422093436.78683-2-yang.zhong@intel.com>
X-Mailer: git-send-email 2.29.2.334.gfaefdd61ec
In-Reply-To: <20210422093436.78683-1-yang.zhong@intel.com>
References: <20210422093436.78683-1-yang.zhong@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kvm_cache_regs.h file has defined inline functions for those general
purpose registers and pointer register read/write operations, we need keep
those related registers operations consistent with header file definition
in the VMX side.

Signed-off-by: Yang Zhong <yang.zhong@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH 1/4] docs: kvm: fix underline too short warning for KVM_SEV_RECEIVE_START
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12218913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB451C433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 16:39:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B9C6761409
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 16:39:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238011AbhDVQkY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 12:40:24 -0400
Received: from mail-co1nam11on2057.outbound.protection.outlook.com
 ([40.107.220.57]:61792
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S236627AbhDVQkW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 12:40:22 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RK2UQYFA2DrXKkQ+m91Dra79rZ23uTGHb68bz3IXwQnHCv52GzCG/eLr37utKO5H6R5SZUgUXguMHGKbwy4l7Y1o0Zcu6naSXR821gH+HAVQYET2WuGpzMnO3VbuMOtd1zOrCTP2hYFx1hKNVhffGSGjWscZLKqNE1eDXp0soiCJm988pZzGgne67wBbmTWAJMWx5ScZzIIaIMvqO8GMDVmdI6m4TYn9KruKGe1uaPSmoRTXl0qolRorLXOiyX76RCYN8jpCszKchtPyRn0wEcHqPoUK2n3dbfdONSo9rkdY5oS1l6luI6vkmPdi7uXoeIxAH0yjoOGg9c9XYilIiA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=suPWH9bl0K1+mahnGBn6QWxHfYVbSDId4Kaw+uxxWog=;
 b=nBvwEXHYF5BYOSHCI+XuG2CNK0p8PkBpYRwYQTxTN/4lGn+rcmWqYX6hauswKNvZcd8i0HKd+vTyEO8UShbvJCdIoGaXp8FEHlMLwYMxU4Cu+4vyqVuW/xhvR2xvqbI8w++WZyqrpUDh5NzpcKi8QTxfQFR5KOGdhgDxW2L2Fq2H9lA2RL9QSlBtuJn/PW4wKdncgXWis3PkzyDvYVMWoP4+ZTVpaVc68MGBFnlhXElB63PRPt4MA/KBNj8BFh5QKnJvhaz+t0LVdyfmuAdwsq7hiDRzEFf35UKd8m+du0JMVHyEIBftgFIDUlUYliN1uyEFTNm5fUzBpkPNwp2ixQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=suPWH9bl0K1+mahnGBn6QWxHfYVbSDId4Kaw+uxxWog=;
 b=b1RwjPw1a5hFd9j/qV9NNZMwzzaQ2vpArt5pg1EkbJtdYGcOr5ZLENc2+/UNCv/AtnqmUMf29qMvCtd00/bFtMmbJBuZjyOwwofHx88uAY9UL9K9rTryq3AfE+ZhMEgj/B+tDcPqsR5BrUqBc+ArGC7EFLx2QgfkE/fVMX/l8CQ=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SA0PR12MB4495.namprd12.prod.outlook.com (2603:10b6:806:70::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.19; Thu, 22 Apr
 2021 16:39:46 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.023; Thu, 22 Apr 2021
 16:39:46 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, sfr@canb.auug.org.au,
        Ashish.Kalra@amd.com, Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH 1/4] docs: kvm: fix underline too short warning for
 KVM_SEV_RECEIVE_START
Date: Thu, 22 Apr 2021 11:38:33 -0500
Message-Id: <20210422163836.27117-2-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210422163836.27117-1-brijesh.singh@amd.com>
References: <20210422163836.27117-1-brijesh.singh@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN2PR01CA0059.prod.exchangelabs.com (2603:10b6:800::27) To
 SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN2PR01CA0059.prod.exchangelabs.com (2603:10b6:800::27) with Microsoft SMTP
 Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20 via Frontend
 Transport; Thu, 22 Apr 2021 16:39:45 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 2cb90bb3-e98a-40e6-f541-08d905ad3cc5
X-MS-TrafficTypeDiagnostic: SA0PR12MB4495:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4495139D6D3A33B9349D6540E5469@SA0PR12MB4495.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4714;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Zvsn9QEoe4xcP3av5gp6yHnC3T18+wS7FjZWd0wPYkEcaXzm+l0BOmjNtugoeY/FT09Rk0lgXFi4Zh5XhOMS+le0Tjz+xuyGHINQfZzoOSDi9aHtQRtLOyG4z1uwKBe1YgkKfkKSwBTyw0XwLqq5swxX3Fd+uAuDByxUHA8aBZj/aaQM43olaKlEOrpefXnYymaw5eHNidFCxbiNX7UK+NEq/dIASVOE5l8iWBc7qK/E/JSWIImwlOu1/nh3qcLpb/rxaDcqGU28nT/q8UAupbv0FLCchj95TcPXMdBF7LXkBrKWYLiR/KxZ+VClNczUGQ5vQVhWchYJa3InmhfFvOhrOVS+VMPV44A7sW5zuGpy7m33beoIMXf0EHp6qdHdoeQrecQrGCPocpXaXwiONKw6VGrWbg/AasZZujESOfDT63wmhjx7GeVVs5Q5vkZnIr2d/XOrAZgWWXt/qzi6czLwyq+yTjPgKo9Q5Y5CiDuRsKiTSrEu13TZfCoMd/jH/qjbFSvCvIusu0J5tL6MeNJFCpm8XRVz09yUQkuYTA8Xg8js7O3bPE5XDQowxsjrif3znsDeaVNBbvDRHwsNgL6ENHnXfZa8pusVjFRK/bbXYjPBsLF/SA9LcGYBJk/AO1vl61JK5D6azIHYam0uZsLShyi+T4Afw013oWuQUQc=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(136003)(366004)(346002)(396003)(39850400004)(26005)(8676002)(66476007)(6486002)(4744005)(956004)(1076003)(16526019)(2616005)(36756003)(478600001)(4326008)(5660300002)(186003)(83380400001)(316002)(44832011)(38100700002)(38350700002)(6666004)(7696005)(66556008)(2906002)(86362001)(66946007)(8936002)(52116002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 tBDC5xr8cB4SRcKTLw4DCPkaz7tonT/1Ta4hbtMxpjsp4BEoOdQzJ9S4hGXhZ0fMbW77FkotiSdtJbfcAfAAwL9QIDZeA743eXz1VxDN5QrhRIiBHybtLyJesiihyd20AD/Ogg0ZgOqG4pHgqmhIk7sbgvivFiMotxqAc3+t7Lu9n4xddSyPM8HRxjwSy1kz3QeNMWqR5Te6ewDRT466e0kmg9XtLlA8qjuRruKef8c4sS4+tQjBaicPdyGsIIGYGprHYVD6rhAET9G7VKVEGZyA+cqnGPCoX5564m/l3ShbEXaKNMQzCljA6S7vAY+VohS7ZQW+mVym5NAQzKzjZ9fWRVf/8/KhqId0fM9f3UmzP/SpqF2+DLmQXn2DrIbnJzVeFOCxF5XPvPtfur+JeeycNHhEmoYuP5pGidxRwC2qxOjtszAuWco/ATmCx7oF3jY/n7AtukB8WCXW/+0COWshgo24SeP49nKkSpq86k0LFTVI30G8My4Fxge9+Fe01MZQZwhvGZZOYgnJf9jAsZi1dCR/qsIn+VgEmdVc2h73lAWKX/imz+z8p9icX3fppZEi8jXvuozZvSLeySY8ftiX09ZUfEGDbmQYk50BqWEksZCQg1o3BNETY53z+3Xnp0wXVBqqvlfyvHQ/Jqw6qaVf0ysJnPY0qZH7rVwU08JvcrYykI4rJtyM3+XySXRhLf+9EfRHq3rUA/JXj7UEDPMR+NAWKfpn9w7qsK05yW5GuSGfV4Sw55g82jtfbxLF+Sa7UtwMkW9HP/2CSPoJ1ohqKbLraWx4SAu+HFo3mOyFnGhM53Gt0lt9xXiJUEgOcRIvIpDM0xBO3/1WWcWF7p1zoM9gC1tMSwsXRYTcj7c7E0d8T9jBuImD8IieRJ7X766c7/IoHDkEBeiiLb3/dErMPDRfR0QBrFwaC2jjoOEo5a8Sy9/AWbphGOdj3iUpwqJpewsKsFE4rHC1/G4WbRlDn2AP4qH2bel9IFINfJD4k/jM4dax1xwZ8qXgyN4RQ2uZbC7yS8azsgFwdSUmqvUBkDq6m42ZWYelBZWO2+0PWkTqLRJfNJLjtIrdMF5meusjk6cdxA6dAr+fOJVJZ8wbzGyNF+VsedE/SOsQTiwphLcw8cydwMjUoPXWjEqm3Ym8BN9BGZWcSzoSIsPvdY8uH0h8cyJbALBSl+BKblBPxFBVP5N7XiocmeFoStIF6QQJPdzjMJwowFQFxjkz0OcwqUz8GPPICnZk/c77qg/gQu5Ix4v8M+e2ps4T+vS022oNEnNhWDm2+F5FeO2s/RDvArNkG4yt1hL4qlEEU/Fm+y60Q0G9vbGPRe/3WOjC
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2cb90bb3-e98a-40e6-f541-08d905ad3cc5
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2021 16:39:45.7962
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ivVo258cHORq6Kj1lsO4ESenGFZKkrCUERpbwOeteb1zwbv0le7zdl6Cha5u0sNl7xVh6hGUxhGimoXYaiauOQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4495
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes: af43cbbf954b ("KVM: SVM: Add support for KVM_SEV_RECEIVE_START command")
Reported-by: Stephen Rothwell <sfr@canb.auug.org.au>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 Documentation/virt/kvm/amd-memory-encryption.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] virtio: last minute fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12219219
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-25.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 120F8C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 22:20:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C4AFE61421
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 22:20:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239754AbhDVWVB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 18:21:01 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:55291 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236763AbhDVWU7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 22 Apr 2021 18:20:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619130022;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=tgQyxuFNIWv2WFwGCh6y2wdSkYdHkTXHx4X2Bpzjy2I=;
        b=HP+d12yBLmHIipwN9ACa6yrY4L8RxDcVHWE90COWvMT2redh/FX55Bi0zrc5JXHZ6VR1nr
        WlOn5DhHGv+pU0Gn2Zhl8Z4oyConXdvnA+e/xYVMaT30mWABtfnvWMqDbpHc95xEYGQw2k
        JSvFdhahPm+WK4CChyH8Itj3fA5Y+d4=
Received: from mail-ed1-f71.google.com (mail-ed1-f71.google.com
 [209.85.208.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-432-cxD-MhIfOU6ITGBgG-OYWw-1; Thu, 22 Apr 2021 18:20:21 -0400
X-MC-Unique: cxD-MhIfOU6ITGBgG-OYWw-1
Received: by mail-ed1-f71.google.com with SMTP id
 z3-20020a05640240c3b029037fb0c2bd3bso17651222edb.23
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 15:20:20 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=tgQyxuFNIWv2WFwGCh6y2wdSkYdHkTXHx4X2Bpzjy2I=;
        b=G8LZ38fdR/cqPXrQ1s+bDakX7zyYbRqG1avQRNFJVN7wvQ5nxszNHTKF8itwWP24NA
         6y/vwY832u+tKMepOW5W3FpIqPGSZfIcP4TELSILxED5+4dgwPeQgUPCxl0J5y917faX
         5fWcOaf64VuoQDleV6H6T2YQdrxqbXR9uzcNGZ2U2AALlG+4RJaraIIAAG+pK9GH41h5
         EVEu6WX5UDWNeS+i2YCJYNEpgT39G+bMLbfNiEabAYy36gbSIKxonxyHpW+UQs7pPVH9
         1QZJ3JWwcVwjrige4S+dNGloPr6u7ypBQbuy545TxoFDi+W8BX8Q9o3WFtwCqMF/shW7
         FZAg==
X-Gm-Message-State: AOAM5308JCFQ9dTJLKAmnsWk5D4YF7EOHHFHq9+dS6L4/8zOvvLtRtAZ
        1vCLOaq7UaIJEEZVTvnEojMqHo85jAG4e01ZrPN8Ab+aAkoYzSUTrjo1QmPSp1Oqm0cTwN4faPX
        +pa9b3bRJY1Q4
X-Received: by 2002:a05:6402:1912:: with SMTP id
 e18mr807275edz.184.1619130019727;
        Thu, 22 Apr 2021 15:20:19 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwJy1AtNvC1yqgjKWu6Iev/lJ2pAgqjtkiG2OyAAr4aeu8ke3P5mSsVUhBCU4b2QDNeMyBTxQ==
X-Received: by 2002:a05:6402:1912:: with SMTP id
 e18mr807263edz.184.1619130019602;
        Thu, 22 Apr 2021 15:20:19 -0700 (PDT)
Received: from redhat.com (212.116.168.114.static.012.net.il.
 [212.116.168.114])
        by smtp.gmail.com with ESMTPSA id
 u1sm3177747edv.90.2021.04.22.15.20.17
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 22 Apr 2021 15:20:18 -0700 (PDT)
Date: Thu, 22 Apr 2021 18:20:16 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        dan.carpenter@oracle.com, elic@nvidia.com, jasowang@redhat.com,
        lkp@intel.com, mst@redhat.com, stable@vger.kernel.org,
        xieyongji@bytedance.com
Subject: [GIT PULL] virtio: last minute fixes
Message-ID: <20210422182016-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit bc04d93ea30a0a8eb2a2648b848cef35d1f6f798:

  vdpa/mlx5: Fix suspend/resume index restoration (2021-04-09 12:08:28 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to be286f84e33da1a7f83142b64dbd86f600e73363:

  vdpa/mlx5: Set err = -ENOMEM in case dma_map_sg_attrs fails (2021-04-22 18:15:31 -0400)

----------------------------------------------------------------
virtio: last minute fixes

Very late in the cycle but both risky if left unfixed and more or less
obvious..

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (1):
      vdpa/mlx5: Set err = -ENOMEM in case dma_map_sg_attrs fails

Xie Yongji (1):
      vhost-vdpa: protect concurrent access to vhost device iotlb

 drivers/vdpa/mlx5/core/mr.c | 4 +++-
 drivers/vhost/vdpa.c        | 6 +++++-
 2 files changed, 8 insertions(+), 2 deletions(-)
```
#### [PATCH v5 01/15] KVM: SVM: Zero out the VMCB array used to track SEV ASID association
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217329
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84EF2C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:11:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F82761354
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:11:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234055AbhDVCMI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:12:08 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42906 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233976AbhDVCMG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:12:06 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 38AFEC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:11:32 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id
 h14-20020ac846ce0000b02901ba21d99130so6300914qto.13
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:11:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=es3BrEt/S0hj0elrM8cYzWujMT4DWRrvIdZx5ttB4mo=;
        b=rlXyrnFK0pqqsvHYF2rEC/rSf0+paRZxvod0CTuMJ5p3boxP32/+3hNxeIdLeJnXUv
         YYvxLUl/mqEKXMf+bs4laYvYIJnoUmTiFYMJvMEl8hZabkLViUmMl5lxaJtaBAb7q/m5
         ali8h8VO0aBEYnZHRlZV2izoqU75j8CBPhre58Ww4rdteSJ8wc/3VBcBwVXcbD1FSoK+
         iHEl5UEae68YZ7wT+hY5fBAg9z7ZnIBYY1MKC++wzvYpexgWV9pIJGAFtnJbdGbJagv4
         6pbOkBKe7Fak61U8K7pKSemcA2JIx4eP9BtLuZ7aBakRNIS3epfHhUhdrvtzMmiz+ijW
         nqrA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=es3BrEt/S0hj0elrM8cYzWujMT4DWRrvIdZx5ttB4mo=;
        b=T1tusJp78PlnlS2J3/qsr3reH+o21hppOZwKsvVxPcKvZ1tEhWu6ZShYEcG3tUnLUx
         kLqzuXa/RyPTnwqDG1PtCpbFZTDfu8vJgoKJqHJ9YIsWWgh17tpVeFMSYFtYZUtkBLLq
         zl5d/KdIni3DZ2JtZHDaRQVx9uL+P0bxkPwFCep39cMLt+/CkU+67+nLGMIAT4xcSSra
         Q7GQyFi+JxDEk5nfEPE70VYSzejXSNSg3LZGjCWhopBulc1ZRQLsU4R2QQ05ht90kbZf
         fl/RhBpxGS9lwPS+qyHlDOfVDWGboVFzyr//4+JN4o+YKQb/nLALqp9xnZfj+af1RPNC
         heTQ==
X-Gm-Message-State: AOAM532x0lwyI+NMybTxT6pqdcu8j/v+0fM4KYEXTY7Q8ZIoJlTrvvYx
        dRFCKdz5aRhGvx5XRWEc0U07cN2KBGA=
X-Google-Smtp-Source: 
 ABdhPJxiYCrJnCgureQBFXnyTKS0/Re5X2xbdqnEK6YpQ5OLkS7/63Tg/teL/Ifv9gMqblsCqfREmedXFyQ=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a0c:8521:: with SMTP id
 n30mr913189qva.53.1619057490787;
 Wed, 21 Apr 2021 19:11:30 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:11:11 -0700
In-Reply-To: <20210422021125.3417167-1-seanjc@google.com>
Message-Id: <20210422021125.3417167-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210422021125.3417167-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v5 01/15] KVM: SVM: Zero out the VMCB array used to track SEV
 ASID association
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Borislav Petkov <bp@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Zero out the array of VMCB pointers so that pre_sev_run() won't see
garbage when querying the array to detect when an SEV ASID is being
associated with a new VMCB.  In practice, reading random values is all
but guaranteed to be benign as a false negative (which is extremely
unlikely on its own) can only happen on CPU0 on the first VMRUN and would
only cause KVM to skip the ASID flush.  For anything bad to happen, a
previous instance of KVM would have to exit without flushing the ASID,
_and_ KVM would have to not flush the ASID at any time while building the
new SEV guest.

Cc: Borislav Petkov <bp@suse.de>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Fixes: 70cd94e60c73 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: svm: Skip NPT-only part of guest CR3 tests when NPT is disabled
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217411
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9A934C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:54:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6ADA361354
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:54:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233990AbhDVCz0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:55:26 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52606 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232618AbhDVCz0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:55:26 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 082D3C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:54:52 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 137-20020a250d8f0000b02904e7bf943359so18330178ybn.23
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:54:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=Jb1cdGutYwWw/givKmt3Bb+yg+wB2IwgsnaOdWfXOpU=;
        b=R0hKlBwz3cwKsOW3FhtoV33AWD+Lvy6eSAr8VoSJy6Q1fhJ1Ey9lBIOZ6oHDX45ABk
         8JzXU+ptDc1rkaJuxHoZAkxm6AP2Ivz7aLtMAyOnaUrwtR+gXRpYDdyjSe24htGbkR5Q
         Nlxi1MBB2joyB7x8PNjNg/2Wyi5K6XnEDJhJiXpNR8W4KJQ/jaIgy6xm9x20CUTPzpVz
         OpTgDH3nvblR6YDTv3+fk5oG+PsKRSSmdMzi5tAjLc2HmZlt6gt9unpNnHCQkdmDzg8M
         QMeO0dWMpLkVFcxapYJ7QqJZ7SDcgUfUaLHZhzvDKfw5NxBzIKpkNbiCQl1TFT01P352
         yEYw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=Jb1cdGutYwWw/givKmt3Bb+yg+wB2IwgsnaOdWfXOpU=;
        b=FalrZ6rVIEeMgxsQSFf5B8euVdYIjwbfv3SFqsLMG15iSuytpzhb9ApqJ0NtC9qou9
         7KDMFci+4DNKxRTvv5oTaVXz2vuJHJZFa0CuAVdNFaBCsMF/8GjlS0wNd9fEYT6It+F+
         Kop40oQF/1uZlVV1ID1562wJQiUwPPYHkJtyTLvk1MNriqPY8ePsJdvLzklKG8N6GE54
         WHTrfCrWU5tDmRhntLTbVXBbkw5rmKL+HqO+Y/s/g3lQKDAA07hewRUciGufhYB2cBV9
         o/g1ZOFsMXMyqflfabvWAQdL8cQXB8fSmbveTCAF35pOkU2D+qTQKwvg4Iz0dwy4W0dA
         eupw==
X-Gm-Message-State: AOAM530BW4SaNOfVzoCgQGmKdqZkAoyXhNIRITpRtHe9BCLDbR6AKUR6
        KvFZIXTFmfY4q+UnuwbHHxczjC+h1iU=
X-Google-Smtp-Source: 
 ABdhPJyThF/SMzswqaoyFI93YazXMDM/f91OEVBFWE803D202/HmOLSY1sZiW5WAAffRRinqQFGx7nHCJwc=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:aba9:: with SMTP id
 v38mr1680904ybi.67.1619060091313;
 Wed, 21 Apr 2021 19:54:51 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:54:48 -0700
Message-Id: <20210422025448.3475200-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [kvm-unit-tests PATCH] x86: svm: Skip NPT-only part of guest CR3
 tests when NPT is disabled
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Skip the sub-tests for guest CR3 that rely on NPT, unsurprisingly they
fail when running with NPT disabled.  Alternatively, the test could be
modified to poke into the legacy page tables, but obviously no one
actually cares that much about shadow paging.

Fixes: 6d0ecbf ("nSVM: Test non-MBZ reserved bits in CR3 in long mode and legacy PAE mode")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 x86/svm_tests.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH] KVM: VMX: Intercept FS/GS_BASE MSR accesses for 32-bit KVMFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217397
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id D80D9C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:38:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97D146142F
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:38:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234567AbhDVCjM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:39:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49096 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234493AbhDVCjL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:39:11 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2E286C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:38:35 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 s34-20020a252d620000b02904e34d3a48abso18194379ybe.13
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:38:35 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=xbd22aCtQRBPSIBux5x1ONfW3mzcaq+9oc3GdPhDL5A=;
        b=CQNZmCRn6tjpHmZXXODOgrYWhlhpa5V8QSPvAOYAmgGvNfkkZr0U7ML3JW+RkPYPPY
         +1rAfFq+0zB61kdoNZlgZM63U2qHKsUK9NzCEPuV0c4YwnmL4ih52ThlPHMCCxxHrwNr
         FeDr2TYhk3INAUrrQHwLF6HjW6P/uutql80C6h6UOlBP2xcWNtfYCXQd6Xa27tNRDVcH
         0tX/Y/0d79FaHQ654iTuI+fGRFAR6+QkXJIkoqTEMELekTkH8QWtjCgRL+him5ULG9Di
         DFoeWvq+L4DD0d9Qbo3aF/lyG9vG36/HovZbCetSNI1sJd7xA01c5R7D/ycfMcHzWw1r
         VKNQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=xbd22aCtQRBPSIBux5x1ONfW3mzcaq+9oc3GdPhDL5A=;
        b=Jew+5qmNNfR7f3JK/RwiK4DYqG/uQzx2LHCfIpRU22EhifOiJPaCzKN2Q2kHFj09k4
         re94NwEBbqMsryUuRGUxxHaQBoi2YwVZf5A7abrTpLJ3L69EMGb9G/QFMkcYvEBKtQRt
         UhoE68hBzuM+ELHJQrVkGlUQg91NBLXqLJl6hbuLMnXtlhXI6ETLrTIdEUHz2WYIGkK2
         uo0XT6C9zFC7sTF1co4g4/kS80tTuZ+JybS1rPIeup6CjqJCQnIeVmMRoV+AbwZ6OTtJ
         jXgQuNYMPcmDogPOU0f9STWoTlgk6f2goZ6D2hvvxO+Kvt3FpMJYnD/KNaFybKy+WQaq
         irKw==
X-Gm-Message-State: AOAM532+Q+yJZQikamwC2njMMek+izYPG4FRgV/Elq4LkX11FTex4LtB
        XpiAcQZtISbEi0aaTc+J6rEd8qDRobc=
X-Google-Smtp-Source: 
 ABdhPJzDJe6RG1R6CFv4PyI3kz6h2OZBhalOq3sWRQX107uJCy6Z9sEu6/7T5WqnCSiXcRX/RnlUnwRfW6o=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:2fc5:: with SMTP id
 v188mr1593060ybv.140.1619059114437;
 Wed, 21 Apr 2021 19:38:34 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:38:31 -0700
Message-Id: <20210422023831.3473491-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH] KVM: VMX: Intercept FS/GS_BASE MSR accesses for 32-bit KVM
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Disable pass-through of the FS and GS base MSRs for 32-bit KVM.  Intel's
SDM unequivocally states that the MSRs exist if and only if the CPU
supports x86-64.  FS_BASE and GS_BASE are mostly a non-issue; a clever
guest could opportunistically use the MSRs without issue.  KERNEL_GS_BASE
is a bigger problem, as a clever guest would subtly be broken if it were
migrated, as KVM disallows software access to the MSRs, and unlike the
direct variants, KERNEL_GS_BASE needs to be explicitly migrated as it's
not captured in the VMCS.

Fixes: 25c5f225beda ("KVM: VMX: Enable MSR Bitmap feature")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

Note, this breaks kvm-unit-tests on 32-bit KVM VMX due to the boot code
using WRMSR(MSR_GS_BASE).  But, the tests are already broken on SVM, and
have always been broken on SVM, which is honestly the main reason I
didn't just turn a blind eye.  :-)  I post the fix shortly.

 arch/x86/kvm/vmx/nested.c | 2 ++
 arch/x86/kvm/vmx/vmx.c    | 4 ++++
 2 files changed, 6 insertions(+)

```
#### [PATCH] KVM: X86: Fix always skip to boost kernel lock holder candidate for SEV-ES guests
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12218003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 13573C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 08:34:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C3DDC6144D
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 08:34:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235314AbhDVIfI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 04:35:08 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42704 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230285AbhDVIfH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 04:35:07 -0400
Received: from mail-pj1-x102c.google.com (mail-pj1-x102c.google.com
 [IPv6:2607:f8b0:4864:20::102c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B334BC06174A;
        Thu, 22 Apr 2021 01:34:32 -0700 (PDT)
Received: by mail-pj1-x102c.google.com with SMTP id nk8so7740493pjb.3;
        Thu, 22 Apr 2021 01:34:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=XPeASqzaMJ7Yo0kPhHuSWWnsg8QRwXioVRRRxxovsUM=;
        b=Yi05U8POcqAcJG1vqL+nMp1O7giLcji3FL66Zwkwr+j7LVAiJwHKC8v/WiGpB04nmy
         VgpUEK3CcRW8E7RBuZRWYADruImVGY5v8+V/mQvhHlV4FJJBzrmfMl8CcpC11C6OEEet
         sm6LnWUFDsJB1Cs7X3spzpVCzTdQB3UQxhgJnDfD/kr9fm8uNWYjhPFC3RXv+JteXd5d
         WUJcZNtUjxTiuxfoMMG2E4INMil/QWh1q3wFV1JPg/eazNh3xm7hNudh4/asuYguoznf
         I+Ieq/oca20j681cEv5NdE62Y8zFSyBU7oxR+CQJmCAQnimeCQ0xMQqWML4JdUkkFB4v
         nL/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=XPeASqzaMJ7Yo0kPhHuSWWnsg8QRwXioVRRRxxovsUM=;
        b=W6KnPoxky2/PVgdJufSqhZQb+YgxvAJDtKD07dKKZQLlKe6F0JeK76j+WQogVQbsno
         zZ630OrjJMW1sR77xMgUYZaukqpR+qo/ctUcX9IF7Hx2dtKrOV/fcvbDpMuWFNymmFBN
         yOL7kEu2+Wh1PQne3W5mW+smqgfZSFKW5yUlBTnsWc99wBLBZXY5ZXvfkN1j6QUx3hw+
         tCyHGvUTtxuiAq+cFMiaPUxnue+YbjzKsK5gNqlSa6LlK+iKJxoWx6Oe/pD63gpFhJv0
         CRGUcXnzUCIuLKDWBMbQB9BulX8vwKXeYN5eqh31AsSOF4zX5N74oYz0VgAhVfDaMaVe
         +aWA==
X-Gm-Message-State: AOAM5316NpeY0ElNavSi9Wex6ORPAhODTcffe+WDl9cCROpbDN5IMzWe
        KgAl6J5rERD3PtXok3P44I+O9DbpELY=
X-Google-Smtp-Source: 
 ABdhPJxvaOlO/fw+TXx7l4G7hUQJopQWzgDQMY+xZBAllPOdu44N1Qmff7QYS79eHap77JHljdrscw==
X-Received: by 2002:a17:902:7203:b029:e6:a8b1:8d37 with SMTP id
 ba3-20020a1709027203b02900e6a8b18d37mr2569664plb.44.1619080472080;
        Thu, 22 Apr 2021 01:34:32 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 a20sm1445908pfn.23.2021.04.22.01.34.29
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 22 Apr 2021 01:34:31 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: X86: Fix always skip to boost kernel lock holder
 candidate for SEV-ES guests
Date: Thu, 22 Apr 2021 16:34:19 +0800
Message-Id: <1619080459-30032-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Commit f1c6366e3043 ("KVM: SVM: Add required changes to support intercepts under 
SEV-ES") prevents hypervisor accesses guest register state when the guest is 
running under SEV-ES. The initial value of vcpu->arch.guest_state_protected
is false, it will not be updated in preemption notifiers after this commit which 
means that the kernel spinlock lock holder will always be skipped to boost. Let's 
fix it by always treating preempted is in the guest kernel mode, false positive 
is better than skip completely.

Fixes: f1c6366e3043 (KVM: SVM: Add required changes to support intercepts under SEV-ES)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 1/9] KVM: x86: Remove emulator's broken checks on CR0/CR3/CR4 loads
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217361
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E3F33C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:21:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB289613DC
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 02:21:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234340AbhDVCWN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 22:22:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45238 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234234AbhDVCWL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 22:22:11 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AD6D0C06138B
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:21:33 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 u3-20020a2509430000b02904e7f1a30cffso18210430ybm.8
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 19:21:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=mOGXDXzhpmjx3GQXAE3F8jbPyKEywOEsLX4Y9QabnGA=;
        b=GU+uTAsFDPr0l/vq7k1GGUfFG0HY63xcX5Yc3k+1WVkUkhlV2oO5V1JwVX8bEE0aBS
         mQndo+u+3ZaNchbjRiiF39LSRsv0my7vXosl7viM9rYXMSXfOZQBFzSd3S1x2aSDNnRK
         IUv6ZDjZxwHZNRNH0rGz3IxcW/JQrdgrhrZUz0mfN47Jzwfd6t/AiR9LR+X3E+JPRVl9
         h2oNFcwWD3p7tlB12ls6LLJ9kL24gUvlbuml5QTtbdoqKnhK0O1mRRWb8RB33UiQaKSu
         BLV7RQhh19lOJwYLvKPpQv8TtmI4DDzoXyP8uUx7OnBZu/K22M+Dyk6WMgyaFdgYtyZa
         XGyw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=mOGXDXzhpmjx3GQXAE3F8jbPyKEywOEsLX4Y9QabnGA=;
        b=hRIe2hyv5SJ0mY4AB3fqVuFjDEUbF14Yq1YRrk/12/kGkt3BQCJA47ByjJc6YT5PMW
         slt7S5+AcVaGtpMKR+gQg4KSKqFnxzZ6m78Drk43iJzXY/PBtQEdEIdCpw8GyntHKCPz
         GpZwHZF2H+gVHCS7tzQ8vq/kKs2Oht/UQGaOwfjDJrfEEYYcytk4vMnbeVWRTKC/EjfD
         w2MjLMWelsIP77qDV14fjFNjvoPhQdkH5OX89fjEyVjoiPxXWnFTNe/Zi+TuS25+WF4X
         PJCDwsuND0f4SpkvB9yUUT4O4UVHaA92t7YMQxVdmbBpL9J9uBsM0ZsKg8ybIjkvLlWi
         fGSg==
X-Gm-Message-State: AOAM531FkdkA7xGEPq7Z/McL+rA8I0hAgDhLloUB+wNfQ5PwBYYN5fEd
        ElAn+NUiKI9eQTlgmWPgrcSSr/Uc83U=
X-Google-Smtp-Source: 
 ABdhPJzk1VEX5RsnrgizC3w7WKpIWyjE7FzekhwM/pl5AX/kpTpBb+6bgSoManqeL0KyEcHO4He2vZribeE=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:e04b:: with SMTP id
 x72mr1418298ybg.337.1619058092969;
 Wed, 21 Apr 2021 19:21:32 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 19:21:20 -0700
In-Reply-To: <20210422022128.3464144-1-seanjc@google.com>
Message-Id: <20210422022128.3464144-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210422022128.3464144-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2 1/9] KVM: x86: Remove emulator's broken checks on
 CR0/CR3/CR4 loads
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Babu Moger <babu.moger@amd.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        David Woodhouse <dwmw@amazon.co.uk>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the emulator's checks for illegal CR0, CR3, and CR4 values, as
the checks are redundant, outdated, and in the case of SEV's C-bit,
broken.  The emulator manually calculates MAXPHYADDR from CPUID and
neglects to mask off the C-bit.  For all other checks, kvm_set_cr*() are
a superset of the emulator checks, e.g. see CR4.LA57.

Fixes: a780a3ea6282 ("KVM: X86: Fix reserved bits check for MOV to CR3")
Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/emulate.c | 68 +-----------------------------------------
 1 file changed, 1 insertion(+), 67 deletions(-)

```
#### [PATCH] KVM: x86: Properly handle APF vs disabled LAPIC situation
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12218101
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1A35BC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 09:29:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC8EA6145A
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 09:29:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235647AbhDVJab (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 05:30:31 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:41623 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235613AbhDVJa3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 22 Apr 2021 05:30:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619083794;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=3kZqpcpDryGiJYWT4WCPcehjl0P1U1v7NJiamcT4384=;
        b=AW3Yt1zXUqfNlqz4Ixh6sTw7uY1IxilsfopA7n62oL55nTs0jOphQENPgjLIYFfRXZacKV
        GrkrRoP2/AU5oIt1szd6M+VhUqgtmDaEdlc9xI87e474sLMs/KsV1qVIXN0WtbiA2xmc39
        xOOOJY9/0UHIRLGcA6GfYLji/EZcf/c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-nmeL2AHLNr2oNKkFuYW9ew-1; Thu, 22 Apr 2021 05:29:53 -0400
X-MC-Unique: nmeL2AHLNr2oNKkFuYW9ew-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B6DD5839A42;
        Thu, 22 Apr 2021 09:29:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.217])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 825CC10023AE;
        Thu, 22 Apr 2021 09:29:49 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Sebastien Boeuf <sebastien.boeuf@intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Properly handle APF vs disabled LAPIC situation
Date: Thu, 22 Apr 2021 11:29:48 +0200
Message-Id: <20210422092948.568327-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Async PF 'page ready' event may happen when LAPIC is (temporary) disabled.
In particular, Sebastien reports that when Linux kernel is directly booted
by Cloud Hypervisor, LAPIC is 'software disabled' when APF mechanism is
initialized. On initialization KVM tries to inject 'wakeup all' event and
puts the corresponding token to the slot. It is, however, failing to inject
an interrupt (kvm_apic_set_irq() -> __apic_accept_irq() -> !apic_enabled())
so the guest never gets notified and the whole APF mechanism gets stuck.
The same issue is likely to happen if the guest temporary disables LAPIC
and a previously unavailable page becomes available.

Do two things to resolve the issue:
- Avoid dequeuing 'page ready' events from APF queue when LAPIC is
  disabled.
- Trigger an attempt to deliver pending 'page ready' events when LAPIC
  becomes enabled (SPIV or MSR_IA32_APICBASE).

Reported-by: Sebastien Boeuf <sebastien.boeuf@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/lapic.c | 6 ++++++
 arch/x86/kvm/x86.c   | 2 +-
 2 files changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH 1/5] KVM: x86: Move reverse CPUID helpers to separate header file
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12217255
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id D65A8C43461
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:56:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD18760FE5
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:56:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242027AbhDVA5O (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 20:57:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54886 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240786AbhDVA5O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 20:57:14 -0400
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6808AC06138A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:56:40 -0700 (PDT)
Received: by mail-pl1-x64a.google.com with SMTP id
 59-20020a1709020241b02900e8de254a18so19151585plc.14
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:56:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XxDAh3fhzg5A8awaqIQozL0a7udxHE7UvhfJ/Wi4USQ=;
        b=OKzNJGs7evpkAgOjHMv/92KXILF1CXt1OoiqCa3/sFn+5Tiwyhbke+MVLj00a+QOQK
         W7Yrpe3/8/7w+6jmkjAWhZ6rim6es/ZqzjZjI5KtW92IgYhG/S4rtkcwxTm1jSctmdyw
         GzbCakasmyLuCDfYUgH5UCLR7gs8yvtx046Nv0VaRZ8TGXDSzFTNdbEDrqXAd9kUCK5u
         3JpGsusiKCfOpONHLg+mTBNwbCBZDCKX8gTLxqATf9O+QOjjYM4jCAFt16kCO7GTKdT8
         iEc7S5RdVChyd+fSHctUtWFA338V7T4HuaQ0p5zpR51sn6JCNbtXOzOMxUbOeWEXJwLQ
         z82g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XxDAh3fhzg5A8awaqIQozL0a7udxHE7UvhfJ/Wi4USQ=;
        b=eqC4pA8OWAH2y7PrZgpnhDIKwmgOcjoMy0pU0F/N8Nj+vI+os7dOqVlwXM2z9v2NxP
         I+xQG67E9nZvkpnVuTYpA0cLM83c+otuqHJrZMxs5LnwzTu6619MzG7gtNEcNpiO2N1i
         mHbDae2cBLfa+SZGMY2m5srcyg4J9OHuRlwkRuD5g8KGJ3E1XANgvTSn4Rn/kFWkmHG3
         HnTtNpFByjtTvQq6ipf/gdtdW3dB9wm5Y3rAe3xakm7xpxoCIH/LHkmWICJlv3lTz7Yw
         pGsJFjIOhsZgbuMulDRwRJGzAIAKLRyIUbM1Fj9viVk3BnyPqXr3LDCAWHqu3/fZ0Rrf
         31UA==
X-Gm-Message-State: AOAM533pviM0SJ6HhUfOuZ3oucLXamLRT0ziru4C1MQtZtWuIWO+NmIl
        Y2Pi0knVWKh0/zhdXBLiqPCr/tSG44Zlxw==
X-Google-Smtp-Source: 
 ABdhPJytWStGBaql7sF4DNf3GoW+tjXcAJaAsgYk0ZcCMM/ByrNRJa463UMEIpmgYtWq8wO9TgWiGOhfc+BiQA==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:aa7:87d5:0:b029:25a:b5f8:15ab with SMTP
 id i21-20020aa787d50000b029025ab5f815abmr861328pfo.22.1619052999831; Wed, 21
 Apr 2021 17:56:39 -0700 (PDT)
Date: Wed, 21 Apr 2021 17:56:22 -0700
In-Reply-To: <20210422005626.564163-1-ricarkol@google.com>
Message-Id: <20210422005626.564163-2-ricarkol@google.com>
Mime-Version: 1.0
References: <20210422005626.564163-1-ricarkol@google.com>
X-Mailer: git-send-email 2.31.1.368.gbe11c130af-goog
Subject: [PATCH 1/5] KVM: x86: Move reverse CPUID helpers to separate header
 file
From: Ricardo Koller <ricarkol@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>,
        linux-kernel@vger.kernel.org, clang-built-linux@googlegroups.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Split out the reverse CPUID machinery to a dedicated header file
so that KVM selftests can reuse the reverse CPUID definitions without
introducing any '#ifdef __KERNEL__' pollution.

Co-developed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Ricardo Koller <ricarkol@google.com>
---
 arch/x86/kvm/cpuid.h         | 177 +--------------------------------
 arch/x86/kvm/reverse_cpuid.h | 185 +++++++++++++++++++++++++++++++++++
 2 files changed, 186 insertions(+), 176 deletions(-)
 create mode 100644 arch/x86/kvm/reverse_cpuid.h

```
#### linux-next: build failure after merge of the cgroup tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B49B6C43460
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 06:31:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 764186144D
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 06:31:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234909AbhDVGbu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 02:31:50 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:33561 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229967AbhDVGbt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 02:31:49 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQncd5sz7z9sWD;
        Thu, 22 Apr 2021 16:31:13 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619073074;
        bh=il4ZXMNxnxf1r1lHcVDm4MNlaD/cBBNKZJyrLI7ywlA=;
        h=Date:From:To:Cc:Subject:From;
        b=BV8da9LS/ezueRAh5xIqL732gaQoWZoVPfSguGCz3vXlMNQf57/PSouIzZy6hQwtr
         kE7DRUg8pM/8pMpMzqutlvHqLB9Iv4mu70+nHZ17BX5vVdhFqfogedMyHasrqsdWH5
         tEZuSZzpyIQ3Q9nso2dYrEHmp/3EcQ50EaejJ/sZqQ0/6vKWwr7Ezwhu5uHs4JNu+e
         iLo/T/Q0Zl34Kdcu/TYytvdDf66+X12h13WCu6c7YEadSFLs6rNvPBoIntnSLbXbnJ
         Ss4ac+3vCc3604D9sUJRS20mZOt/mJKFFbf4/ctj8+hrgRjOGGqFnVtZTUuUXue3n0
         6Z1tvLoTRyViQ==
Date: Thu, 22 Apr 2021 16:31:13 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Tejun Heo <tj@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        KVM <kvm@vger.kernel.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vipin Sharma <vipinsh@google.com>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>
Subject: linux-next: build failure after merge of the cgroup tree
Message-ID: <20210422163113.31fdbc9b@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

After merging the cgroup tree, today's linux-next build (x86_64
allmodconfig) failed like this:

arch/x86/kvm/svm/sev.c: In function 'sev_asid_new':
arch/x86/kvm/svm/sev.c:118:12: error: invalid type argument of '->' (have 'int')
  118 |  type = sev->es_active ? MISC_CG_RES_SEV_ES : MISC_CG_RES_SEV;
      |            ^~
In file included from arch/x86/include/asm/bug.h:93,
                 from include/linux/bug.h:5,
                 from include/linux/mmdebug.h:5,
                 from include/linux/percpu.h:5,
                 from include/linux/context_tracking_state.h:5,
                 from include/linux/hardirq.h:5,
                 from include/linux/kvm_host.h:7,
                 from arch/x86/kvm/svm/sev.c:11:
arch/x86/kvm/svm/sev.c:119:13: error: invalid type argument of '->' (have 'int')
  119 |  WARN_ON(sev->misc_cg);
      |             ^~
arch/x86/kvm/svm/sev.c:119:2: note: in expansion of macro 'WARN_ON'
  119 |  WARN_ON(sev->misc_cg);
      |  ^~~~~~~
arch/x86/kvm/svm/sev.c:120:5: error: invalid type argument of '->' (have 'int')
  120 |  sev->misc_cg = get_current_misc_cg();
      |     ^~
arch/x86/kvm/svm/sev.c:121:36: error: invalid type argument of '->' (have 'int')
  121 |  ret = misc_cg_try_charge(type, sev->misc_cg, 1);
      |                                    ^~
arch/x86/kvm/svm/sev.c:123:18: error: invalid type argument of '->' (have 'int')
  123 |   put_misc_cg(sev->misc_cg);
      |                  ^~
arch/x86/kvm/svm/sev.c:124:6: error: invalid type argument of '->' (have 'int')
  124 |   sev->misc_cg = NULL;
      |      ^~
arch/x86/kvm/svm/sev.c:154:28: error: invalid type argument of '->' (have 'int')
  154 |  misc_cg_uncharge(type, sev->misc_cg, 1);
      |                            ^~
arch/x86/kvm/svm/sev.c:155:17: error: invalid type argument of '->' (have 'int')
  155 |  put_misc_cg(sev->misc_cg);
      |                 ^~
arch/x86/kvm/svm/sev.c:156:5: error: invalid type argument of '->' (have 'int')
  156 |  sev->misc_cg = NULL;
      |     ^~

Caused by commit

  7aef27f0b2a8 ("svm/sev: Register SEV and SEV-ES ASIDs to the misc controller")

interacting with commit

  9fa1521daafb ("KVM: SVM: Do not set sev->es_active until KVM_SEV_ES_INIT completes")

from the kvm tree.

I have applied the following for today, better suggestions welcome.

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Thu, 22 Apr 2021 16:13:34 +1000
Subject: [PATCH] fixup for "KVM: SVM: Do not set sev->es_active until KVM_SEV_ES_INIT completes"

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kvm/svm/sev.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### linux-next: manual merge of the cgroup tree with the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217695
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 58BE3C433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 05:54:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2A36061425
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 05:54:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234775AbhDVFyl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 01:54:41 -0400
Received: from ozlabs.org ([203.11.71.1]:49913 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234806AbhDVFyh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 01:54:37 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQmnc44mMz9sTD;
        Thu, 22 Apr 2021 15:53:56 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619070837;
        bh=BGZPYQkkrhZBKQnH/8AnrujpEbYer6hDxMUZS72H6e4=;
        h=Date:From:To:Cc:Subject:From;
        b=f8Sdg2jpgOZm3ETvhaBqhzh2fGNRPvOH7HcJ3kGq4wesKkELDZfgncJMVkZgLt+eD
         vS0ipQpTq9oSNkn3RMTcafzsQcnniCKxHwdtIQtEj+/4RFPLLCgJczSW7p2fDBsFUX
         zMiAhsPM8BG9G6NZTpW/CmfvxtUQVlaYHJHakw73VlEP1PMBc5C5QYPtLAoxHpft5T
         yYlGniklQBz66onN7adQBYUATthJgSSF3ZK6pZb5FQdkrtx8jvGEne7lf5omuF3rEZ
         kdD9hno/3KeaB1M9/Zosbijzwyn7rFr7AeVjnVkqUfFZgPKeV/ProH9Ddy9mwQE00m
         ljcErt3QFNm8g==
Date: Thu, 22 Apr 2021 15:53:55 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Tejun Heo <tj@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        KVM <kvm@vger.kernel.org>
Cc: Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Sean Christopherson <seanjc@google.com>,
        Vipin Sharma <vipinsh@google.com>
Subject: linux-next: manual merge of the cgroup tree with the kvm tree
Message-ID: <20210422155355.471c7751@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the cgroup tree got conflicts in:

  arch/x86/kvm/svm/sev.c

between commit:

  9fa1521daafb ("KVM: SVM: Do not set sev->es_active until KVM_SEV_ES_INIT completes")

from the kvm tree and commit:

  7aef27f0b2a8 ("svm/sev: Register SEV and SEV-ES ASIDs to the misc controller")

from the cgroup tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### linux-next: manual merge of the cgroup tree with the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217697
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AFF3DC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 05:57:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7855B61417
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 05:57:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234777AbhDVF6H (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 01:58:07 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:44511 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229923AbhDVF6D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 01:58:03 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQmsh0Pskz9sTD;
        Thu, 22 Apr 2021 15:57:28 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619071048;
        bh=sg9p+Yym4WtkPibvGln+BlE8RicUroqClBfSKpfPyY4=;
        h=Date:From:To:Cc:Subject:From;
        b=GoNHdzV6ijIt79lu9nIC7atw6SkqgdrUYlZMQG+2IVvYcZ2YILdsnp8M7pBwDa0Eh
         F8yOEsmioe9+Z2r4NidAS53Zasklj07lfrG3L6uxav2x4Htz6PkAzaj/xt2pCVF2R9
         BRa5AKLF6ClDLBEOxYS3lNuod1i52YtAfzUNFntDiefwsEQCEDZVRTt7vl3xMw/a04
         Ff+ug+rI0WoGfEURpOIulmEm65pPtnQVApfLY6Tl7gRWiWG0UBPx2l4XxNdvBQN6O8
         yM4955hchw2rH8y+j8IiZu5sCDyEKrRbCvbo2+J8dJ4d4mGbnGRAL02eqI4DsEA+nu
         3yd7Ls7aMlFDg==
Date: Thu, 22 Apr 2021 15:57:27 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Tejun Heo <tj@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        KVM <kvm@vger.kernel.org>
Cc: Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Nathan Tempelman <natet@google.com>,
        Vipin Sharma <vipinsh@google.com>
Subject: linux-next: manual merge of the cgroup tree with the kvm tree
Message-ID: <20210422155727.70ca2e49@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the cgroup tree got a conflict in:

  arch/x86/kvm/svm/svm.h

between commit:

  54526d1fd593 ("KVM: x86: Support KVM VMs sharing SEV context")

from the kvm tree and commit:

  7aef27f0b2a8 ("svm/sev: Register SEV and SEV-ES ASIDs to the misc controller")

from the cgroup tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### linux-next: manual merge of the kvm-arm tree with the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217627
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A32ACC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:40:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78F9561450
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:40:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229636AbhDVEkg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 00:40:36 -0400
Received: from ozlabs.org ([203.11.71.1]:53873 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229441AbhDVEkf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 00:40:35 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQl8G53X5z9sRf;
        Thu, 22 Apr 2021 14:39:57 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619066399;
        bh=gytcSQ0EK1A2/+Z/7YRsitFG89wvMlfVFxtZpQz7+Do=;
        h=Date:From:To:Cc:Subject:From;
        b=oi7ot3VlB0LJnu8c+jxixbdFRQPWaz1M5SDl2JQdE6yWZTeU4ngUXMbY1G1GXbzZ0
         SQtVxrOABbsDhhC0BsD0UoZG5jmkrx4zEevSHELyHHekwAuvrvF5h+KtTvvnHtufU/
         fH3ayb9bbe0MVRzvOgQFKbKzqbRxy4YDu7mq+hgFtptml9z7fmIiMMNcw0zduLRKqT
         RkDdUB3rwpSnspYdDR9+Bep4FzV8d6uU3ruK0crjkQRkJPwPx9Xzx1PkNsBL1azoTz
         eVO0NGPL4NjJltfxgUxjkSYq+YytjeSTA2KDbTxlEL4KtsobQDWp++k6wEKyU4szMd
         PRNBAQstqPvFg==
Date: Thu, 22 Apr 2021 14:39:56 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Christoffer Dall <cdall@cs.columbia.edu>,
        Marc Zyngier <maz@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>
Cc: Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jianyong Wu <jianyong.wu@arm.com>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>
Subject: linux-next: manual merge of the kvm-arm tree with the kvm tree
Message-ID: <20210422143956.5a43d00a@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm-arm tree got a conflict in:

  Documentation/virt/kvm/api.rst

between commit:

  24e7475f931a ("doc/virt/kvm: move KVM_CAP_PPC_MULTITCE in section 8")

from the kvm tree and commit:

  3bf725699bf6 ("KVM: arm64: Add support for the KVM PTP service")

from the kvm-arm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### linux-next: manual merge of the kvm-arm tree with the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217629
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4AA84C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:43:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2457261430
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:43:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229636AbhDVEnp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 00:43:45 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47992 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229441AbhDVEnp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 00:43:45 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C6932C06174A;
        Wed, 21 Apr 2021 21:43:10 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQlCv3cjKz9sRf;
        Thu, 22 Apr 2021 14:43:07 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619066588;
        bh=Syn3qr1PGDyaL7XmaVT1PyuJyg2wGJIrvrm3IwZB9/I=;
        h=Date:From:To:Cc:Subject:From;
        b=sjr939eeh1tu6S1HQ8xL1IF2UkOCCXHcRufsWcYgvMEgeihcYVUu+EmAVscVkXzva
         oPS4d2exLKuT1tf63ti42cBKqoWUUwuZuSj0NYjg28ARw+GmywYsOVGF0QbxH9aJsJ
         Ta8wJcASNcTEBOjOKx0F4HCSXOd9C1bKttVO7yXOzR0W3xKGmVHQNtwrRvsNTlTK/z
         qcWualdC+PUqz36zvQGaTxNbj3zx/qG1v4eOvisK+T2ZSVnEVn6nMIVr/1uXywf2ut
         cEI9C8rPR7we+t0WXUiYO62mQm8yxC2aYXibSZGcSeHFExjOuN3qIWb1isZuyoICVG
         yle9h+UC440iQ==
Date: Thu, 22 Apr 2021 14:43:06 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Christoffer Dall <cdall@cs.columbia.edu>,
        Marc Zyngier <maz@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>
Cc: Jianyong Wu <jianyong.wu@arm.com>, Kai Huang <kai.huang@intel.com>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Nathan Tempelman <natet@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Sean Christopherson <seanjc@google.com>
Subject: linux-next: manual merge of the kvm-arm tree with the kvm tree
Message-ID: <20210422144306.3ec8cfdb@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm-arm tree got a conflict in:

  include/uapi/linux/kvm.h

between commits:

  8b13c36493d8 ("KVM: introduce KVM_CAP_SET_GUEST_DEBUG2")
  fe7e948837f3 ("KVM: x86: Add capability to grant VM access to privileged SGX attribute")
  54526d1fd593 ("KVM: x86: Support KVM VMs sharing SEV context")

from the kvm tree and commit:

  3bf725699bf6 ("KVM: arm64: Add support for the KVM PTP service")

from the kvm-arm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### linux-next: manual merge of the kvm tree with Linus tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217623
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 57E90C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:29:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C6F961222
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:29:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229833AbhDVEaF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 00:30:05 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45026 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229561AbhDVEaE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 00:30:04 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8E726C06174A;
        Wed, 21 Apr 2021 21:29:29 -0700 (PDT)
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQkw52jX2z9sRf;
        Thu, 22 Apr 2021 14:29:25 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619065765;
        bh=S7qxoLL2mxanY8fwURHisQAFOqNZ2RlcleQrIk620V0=;
        h=Date:From:To:Cc:Subject:From;
        b=Zb6uhxXf2hONrLKwxnLkIbF2Sh2kwZ0g0r8Ao9o1gEKe2hi22rJ+UKrY7qx/+lhBS
         0SxKnMghLD48aYJwLfWYRGH2UivkhgElkf/PIusCXpLsueyOyG0jVcC1+e2jWEFUt9
         FtBDo/lSMROE6rNBk1Ttr9rioTueKzXyPhnEADnh1b/YjEirbeYCCezvYrQgP8UMVD
         xOPI3tI3yugflgV+oLf7ouegXMhY6x02gQW+/QN2G5ilMU+njl6v2BrjEiXVNdsouD
         9hVcmXD1YB6yljwJziisKZmq/PPouT7IMvB1xBFvDybQu4SUIA8//ypz/jSJA9ukpZ
         RwwwnQl9jZfcA==
Date: Thu, 22 Apr 2021 14:29:24 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>
Cc: Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Sean Christopherson <seanjc@google.com>
Subject: linux-next: manual merge of the kvm tree with Linus tree
Message-ID: <20210422142924.222f7216@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  Documentation/virt/kvm/api.rst

between commit:

  b318e8decf6b ("KVM: x86: Protect userspace MSR filter with SRCU, and set atomically-ish")

from Linus tree and commit:

  24e7475f931a ("doc/virt/kvm: move KVM_CAP_PPC_MULTITCE in section 8")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 12217625
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9EDDEC433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:31:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EEA661222
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 04:31:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230119AbhDVEbi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 00:31:38 -0400
Received: from ozlabs.org ([203.11.71.1]:55037 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229561AbhDVEbh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 00:31:37 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 4FQkxs3vqCz9sWK;
        Thu, 22 Apr 2021 14:30:57 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1619065861;
        bh=nrrjueQbJLgdff/uUfD6SBTPY8DEJYTf7uaFtxCIUK8=;
        h=Date:From:To:Cc:Subject:From;
        b=b8b+zTluZd0z2JjIQqelSzr8ILEsdpgJjpF09qTJnnzZhZNez7gYhy59bNjcc2mR2
         7tjj/amfOiKxjHvYYGfTD5uCBXYONp6ex1SzINLXcf0Hp2aLdHX/04o63MG+sDW5dk
         RTtiHfAxaaI3cXXKnQb6voyUtvpR9J6gNYplD/S0DpRsXKACHBylKH8+3lqTzgZ0O5
         EnYt0Vkd7Ffvyv3OcH6fJgmYDycMvR4WeB7u8QpYqtrneUrWYR73PsRsFQyO3TUQZT
         WWihwCjRWX+rJfjtn0oU0H5hGbqgxlgrbIfq+kHhLspz0tBodKSR7H6tYwlCFUlFN7
         ZKSGDxSPkzJpg==
Date: Thu, 22 Apr 2021 14:30:56 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@elte.hu>, "H. Peter Anvin" <hpa@zytor.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Ingo Molnar <mingo@kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Linux Next Mailing List <linux-next@vger.kernel.org>,
        Nadav Amit <namit@vmware.com>,
        Wanpeng Li <wanpengli@tencent.com>
Subject: linux-next: manual merge of the kvm tree with the tip tree
Message-ID: <20210422143056.62a3fee4@canb.auug.org.au>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kernel/kvm.c

between commit:

  4ce94eabac16 ("x86/mm/tlb: Flush remote and local TLBs concurrently")

from the tip tree and commit:

  2b519b5797d4 ("x86/kvm: Don't bother __pv_cpu_mask when !CONFIG_SMP")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH][next] KVM: x86: simplify zero'ing of entry->ebx
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin Ian King <colin.king@canonical.com>
X-Patchwork-Id: 12218555
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E71AAC433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 14:12:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF755613FB
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 14:12:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236943AbhDVOMj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 10:12:39 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:38375 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236357AbhDVOMi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 10:12:38 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1lZa3F-0007PO-FD; Thu, 22 Apr 2021 14:11:29 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH][next] KVM: x86: simplify zero'ing of entry->ebx
Date: Thu, 22 Apr 2021 15:11:29 +0100
Message-Id: <20210422141129.250525-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

Currently entry->ebx is being zero'd by masking itself with zero.
Simplify this by just assigning zero, cleans up static analysis
warning.

Addresses-Coverity: ("Bitwise-and with zero")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] uio/uio_pci_generic: fix return value changed in refactoring
##### From: =?utf-8?q?Martin_=C3=85gren?= <martin.agren@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Martin_=C3=85gren?= <martin.agren@gmail.com>
X-Patchwork-Id: 12219055
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4444BC433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 19:23:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06598613FB
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 19:23:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238811AbhDVTXr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 15:23:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45246 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236810AbhDVTXq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 15:23:46 -0400
Received: from mail-lf1-x12e.google.com (mail-lf1-x12e.google.com
 [IPv6:2a00:1450:4864:20::12e])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7920CC06174A;
        Thu, 22 Apr 2021 12:23:11 -0700 (PDT)
Received: by mail-lf1-x12e.google.com with SMTP id r128so46915693lff.4;
        Thu, 22 Apr 2021 12:23:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=e0qtyejBNKzVyasn4Fe/BMcM/76qCIWOHv2Y82nNLWI=;
        b=Tdmy9zQyWhw7hnnO0VhduA8oxlvWOkcJRDSIyRRniTAiJHGe0XVOenYhm2AyhfRIqm
         mrLNvK22x7sadJEj3AdfnKdzhmDu3GxgQw0wpTGPHJQ/VnmOy4GpScjDH+magYtO3T9q
         aK9Ds1nqMCUaEvynlDK0UTtMkOCQSBVXpmtZqngVNEAJL/tBtbGP1Cttg+zmk6uYXvQt
         pi2z9ZNo4/ljXgXK0xIP7U7G5FhrfKV5AX+7+y+6EnS50V9ma1ikrbyNigjP0xyERqdM
         Gp2SmaUn3bB/+220sXV3XlNG7S+1oVGTYKRB6lufkqw0ilJSfEGwWtJjr58zeW9O4rRe
         g77g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=e0qtyejBNKzVyasn4Fe/BMcM/76qCIWOHv2Y82nNLWI=;
        b=i3qJCb6AZA7PgpxYu1btfawWOigIfrRTxNxG3GHn4Ok7h3x86o0enT1u6EP+8ANx8O
         c4Leu3zj4RUKd/GhqjSUvUg8wxuuH5Wr9qXvuqtwgiBHIqyndJaqa030lXl5qwLQXPYs
         a/ZsvMZEQnAhMEV+jck2Ba88qKlonRf/juOZ12B4bi5M+yUlji8yf+OovTzZsmXap1hb
         lZjWKNRPA5vM0EFeXwfN0yBm4uTEFQOA2fK+h4B7R9MctRlbu7qdmBatJxIRcLZSKASv
         X5SJ/bN2OVgkRSt13W3E29hS0YgZKoMxevRWOUkS4PQUY0P/oIcIzG7n5dy9SOfwq+nj
         ElRA==
X-Gm-Message-State: AOAM5312F4eXbyol2JCP3XZYKKfmdN0LJdApPEtcWgy1aTlxHCrwo9IJ
        YtlS4/5mWAcr4kv8W3sHGylA02fu0cw=
X-Google-Smtp-Source: 
 ABdhPJzAqO9/q1cmEHfiCyXt8qiAuhD3vSrlqaW/Ezyg2zFVlBkgxMJU5FJuec/Ge7mWFLyRc6ieWQ==
X-Received: by 2002:a05:6512:3763:: with SMTP id
 z3mr3421761lft.487.1619119389723;
        Thu, 22 Apr 2021 12:23:09 -0700 (PDT)
Received: from localhost.localdomain (31-211-229-121.customers.ownit.se.
 [31.211.229.121])
        by smtp.gmail.com with ESMTPSA id
 e9sm347493lft.150.2021.04.22.12.23.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 22 Apr 2021 12:23:09 -0700 (PDT)
From: =?utf-8?q?Martin_=C3=85gren?= <martin.agren@gmail.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Michael S. Tsirkin" <mst@redhat.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alexandru Ardelean <alexandru.ardelean@analog.com>
Subject: [PATCH] uio/uio_pci_generic: fix return value changed in refactoring
Date: Thu, 22 Apr 2021 21:22:40 +0200
Message-Id: <20210422192240.1136373-1-martin.agren@gmail.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit ef84928cff58 ("uio/uio_pci_generic: use device-managed function
equivalents") was able to simplify various error paths thanks to no
longer having to clean up on the way out. Some error paths were dropped,
others were simplified. In one of those simplifications, the return
value was accidentally changed from -ENODEV to -ENOMEM. Restore the old
return value.

Fixes: ef84928cff58 ("uio/uio_pci_generic: use device-managed function equivalents")
Signed-off-by: Martin Ågren <martin.agren@gmail.com>
---
 This is my first contribution to the Linux kernel. Hints, suggestions,
 corrections and any other feedback welcome.

 drivers/uio/uio_pci_generic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: SVM: Delay restoration of host MSR_TSC_AUX until return to userspace
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217191
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E4C96C433B4
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:17:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9BF77613FB
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 00:17:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244166AbhDVASP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 20:18:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46384 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231363AbhDVASO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 20:18:14 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CD007C06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:17:39 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 o187-20020a2528c40000b02904e567b4bf7eso17910973ybo.10
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 17:17:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=TNz2FBkufKTcsHNiDDGsGzoST1t4D0jYYkLUrh9Lj04=;
        b=C52ABESOBrQ4hNk64m0bvImdImzscUFZkE9fKNI8cNC5fKiZBxy6+c88xmZQC5LQyN
         Urd/GAfviJZzejYGOvef1zX24doxtW3P/Vb57eG+/X0IdecFqG39RdglldYeb3SIAxxk
         Sxx+8fZx3wHFtRkr9fjiv2q0mJ+zknI3j+K+k69h0j1xlp/IY6J5MiL2YzTaDTpcDtF+
         kOTznXRepw+L5OGm0omSVRs0v9lokZiSwmnc79U62K/fqpHDwTSzWMe3rFiMYc2BjYxf
         dHDYDZa9ZcP2Zs8q0fchkfdBn8uMlVGUKNjrpGbBvm/CTmk/H+mI8zAhQa7ARIU2n5fH
         bezw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=TNz2FBkufKTcsHNiDDGsGzoST1t4D0jYYkLUrh9Lj04=;
        b=XwDg3Nrf4pGIqAaAhWzx6hwk0BAJdeINs941lRzl+Zq52kdWbckf/nBa5V2x8CFyJP
         x1HdpPdrThKr+l8K62uysVzDabb9YJdComaKjnDjxUd1tk4gJfSpKuUsFiAMi/Q1SjAj
         +wJeeQoKs2Nyyh7wwJ91ZmB+K0L3Zds3wwdud8yr78yvDLfP1/2Z3Tl0qyg7oiA5e+sd
         VaHsgYsGYkQ0kRb1UkXz9k/rocOpYnPNQryeDS9H4EVLu1d5BOBcMAmS1EjGgMmDya9u
         I/SVARR2h215OPcPIkwdYxxJEQxCjwXOf/gtD4qRZctH2+gC9hAhwhTG03ZfeoSa3h+a
         RaKg==
X-Gm-Message-State: AOAM530rsBqQNRQG1b34bwWMeH2RHte3+hzVvsM4GuSmcck2CNhDvHpQ
        v+D8m+Q+hVOvr6MFpg6uaeDitdUz+Oo=
X-Google-Smtp-Source: 
 ABdhPJxCA7boQtZvF+ipmEriSnoFhgjHaPGn/Kl5s0CwWWHcFjqB40SgM7QMqzcAJUaTzpOxLuzIOE0rnWk=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:7603:: with SMTP id
 r3mr873838ybc.272.1619050658986;
 Wed, 21 Apr 2021 17:17:38 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 17:17:36 -0700
Message-Id: <20210422001736.3255735-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v2] KVM: SVM: Delay restoration of host MSR_TSC_AUX until
 return to userspace
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use KVM's "user return MSRs" framework to defer restoring the host's
MSR_TSC_AUX until the CPU returns to userspace.  Add/improve comments to
clarify why MSR_TSC_AUX is intercepted on both RDMSR and WRMSR, and why
it's safe for KVM to keep the guest's value loaded even if KVM is
scheduled out.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---

v2: Rebased to kvm/queue (ish), commit 0e91d1992235 ("KVM: SVM: Allocate SEV
    command structures on local stack")
 
 arch/x86/kvm/svm/svm.c | 50 ++++++++++++++++++------------------------
 arch/x86/kvm/svm/svm.h |  7 ------
 2 files changed, 21 insertions(+), 36 deletions(-)

```
#### [kvm-unit-tests PATCH 01/14] x86/cstart: Don't use MSR_GS_BASE in 32-bit boot code
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12217427
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3D73EC433ED
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 03:05:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 002E161406
	for <kvm@archiver.kernel.org>; Thu, 22 Apr 2021 03:05:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234471AbhDVDFw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Apr 2021 23:05:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54838 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234340AbhDVDFt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Apr 2021 23:05:49 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 83EEBC06174A
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 20:05:11 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 u73-20020a25ab4f0000b0290410f38a2f81so18204349ybi.22
        for <kvm@vger.kernel.org>; Wed, 21 Apr 2021 20:05:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=nHcWdzb0XhQi4QlsO7LmwsFD16llxMgU/74d4ZRWlZw=;
        b=D2JzKJqHjJteWl3sof+pGV0S2zgDoGRVlLX7cwJQ0ayI9xM0VfVLyz3wzh0aAmD9kg
         ox79dwVivYa6R0m+9ZRqLi1clA7jeolvTu+gadAbyc2WtfuFq6xmicvG1FaZy6pDD/Kf
         tURIMAfcACywQAyft0l/LLABT7EkjpxONx7o/HAHHpZwnOqfJKYZwNspdpHMK2VGSvGm
         0n0barYVkTlHG81oeBrUmrBtrX5478buf7TLuhi8Pz5mKOcLmp8+wpvn6ht3yYjHBpec
         g26A5Rh9oaGAhGAqsnnxNzwhMEPw3LW4LceDrS+HwVlDPKkk1e00/3UOnFkFEWAKJJGO
         zuFw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=nHcWdzb0XhQi4QlsO7LmwsFD16llxMgU/74d4ZRWlZw=;
        b=ZssLiWoVqN9IG14mwVGo1azbiepkQpXAfqisEon0Sm/ID6e+ZZtE6TlNqjxt3/wWZo
         PvUzIlnPQkEZVCX17fOMowTELo9PmpRjUEh6bWQs1BIgJ4SrfmzrGpKHJ9brCdnz9pV+
         xHhdF+zWAZZX6HNjuKs0wJTKfATqjokyvyTlbsJarnc47ZtbGdkqRYJUoZfjUohtO3Yq
         KU0vc14bYtNPDemkdLeun5Ivqqkh1mIRVlXPHIfJzOLUDEm+gtIBZiuYl/tp+k5cdNND
         3an9Ss/iJRhcCMgjFeZnTWPSyMNJoPypmu8HnUPezY9/3X2D3oDvwG0HKIsvgS+R8417
         Td8w==
X-Gm-Message-State: AOAM532RDh7K/0d6Ap/O1RKSyHhNN5aL1blvfdbF91u8AzMur/QVG43u
        q07Au1/9EzEHodh1plXjXxLlMmj9/Xk=
X-Google-Smtp-Source: 
 ABdhPJxLbApf4tEVBeM51RtYEfuL5zZAymNJnucyaoJ8wGyx1OXt4Xn6ufLXYe09rp1WF7zYyXDIXK7kJg0=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a25:5d0:: with SMTP id
 199mr1584859ybf.56.1619060710852;
 Wed, 21 Apr 2021 20:05:10 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 21 Apr 2021 20:04:51 -0700
In-Reply-To: <20210422030504.3488253-1-seanjc@google.com>
Message-Id: <20210422030504.3488253-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210422030504.3488253-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [kvm-unit-tests PATCH 01/14] x86/cstart: Don't use MSR_GS_BASE in
 32-bit boot code
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Load the per-cpu GS.base for 32-bit build by building a temporary GDT
and loading a "real" segment.  Using MSR_GS_BASE is wrong and broken,
it's a 64-bit only MSR and does not exist on 32-bit CPUs.  The current
code works only because 32-bit KVM VMX incorrectly disables interception
of MSR_GS_BASE, and no one runs KVM on an actual 32-bit physical CPU,
i.e. the MSR exists in hardware and so everything "works".

32-bit KVM SVM is not buggy and correctly injects #GP on the WRMSR, i.e.
the tests have never worked on 32-bit SVM.

Fixes: dfe6cb6 ("Add 32 bit smp initialization code")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 x86/cstart.S | 28 +++++++++++++++++++++++-----
 1 file changed, 23 insertions(+), 5 deletions(-)

```
