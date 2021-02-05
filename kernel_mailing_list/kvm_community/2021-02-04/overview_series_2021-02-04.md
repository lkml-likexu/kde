#### [PATCH v10 01/16] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12065843
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 32333C433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:37:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE43F64F6A
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:37:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234016AbhBDAhd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 19:37:33 -0500
Received: from mail-dm6nam12on2045.outbound.protection.outlook.com
 ([40.107.243.45]:57185
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233343AbhBDAhb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 19:37:31 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PG6DZUIPfP2TRdYCy8oAe8BEMV9XSizNPN7LRd+7kEryA+p7I6SzyRwDpL+3b5ABAh4JuMzgh55hV5NwrDsyn/BFJ4GCkU0qabiOOtttc5CFuoldwuHzTyLnokUZmIVLv58v17F4L9kU7LttCk3tkg4EnR2g7zXD8rfl3FjjSHp8pA+4ESzASGXSlh+87Z1lKRxfw0d8856ja5A5zufOQclyVK6aYMLrbWLxtFhSniEMkrdVAhiXHajeFeXSkYM+vHr08IdaNFqSXL1bbKkdAMKQvsG2rCgbthZ6i2t+9A6HaRb2bhksKgdmztWbTBUA6qLn07nF7fmkj7knzdTtHA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rV4tmI0JPaYZJop2XHUnckbXZPG53Y5sV70d3NFdtGA=;
 b=gqrzIgA+UQdatomxFzH7sSn6+Rccfc12zIS2rkuLOneEtKOYuNv6ZU1q7XAjahZ9Kz0Hba5Ya2ES6741YiZEcIe0jyNDeUlpmcTj8DrZy8/hWC1StnQUYfULIbRKxYO2wIX68MddSRKFwVugMiJ+A2YsYA4IF4EYi3xi8+TyEbF5xgP0VhxPgRCza5YCr79QqDlgUB5m0xE49RJjDxrFb8woMFwYHt4LAlmpIst+L2J3FXvYR0q+VLibTEG/yonSpvDi+bkSFiesfb6lvFUUO3n6DF0LOQnZI3G4PaIfONZ3PeOfAz5KXlTJDKx+RlpMlZNMcSdZxBWo8wHGNfKZjA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=rV4tmI0JPaYZJop2XHUnckbXZPG53Y5sV70d3NFdtGA=;
 b=jDlu6dDaITZVML39wfUtffxErxEoNAT9UejaVmCxVZPRzARKtmZLWGGY4WWEL14Nq321VBGv5cza0xM5Qri1NLPhTCsDtu0RYZ/VueJ4087EoHi3eQdjL0LNmGTQ2OGCnNe2AODA9UwGVVWsOaHCqkwDLZLF3TS/v9tgtR4JDWM=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4384.namprd12.prod.outlook.com (2603:10b6:806:9f::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16; Thu, 4 Feb
 2021 00:36:37 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e%7]) with mapi id 15.20.3805.028; Thu, 4 Feb 2021
 00:36:37 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, srutherford@google.com,
        seanjc@google.com, venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v10 01/16] KVM: SVM: Add KVM_SEV SEND_START command
Date: Thu,  4 Feb 2021 00:36:28 +0000
Message-Id: 
 <48c18d02e68856fcc667dc95c965132f42080fb3.1612398155.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1612398155.git.ashish.kalra@amd.com>
References: <cover.1612398155.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0071.namprd11.prod.outlook.com
 (2603:10b6:806:d2::16) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SA0PR11CA0071.namprd11.prod.outlook.com (2603:10b6:806:d2::16) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.17 via Frontend
 Transport; Thu, 4 Feb 2021 00:36:37 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: e9a6b339-b1db-4224-8eba-08d8c8a4ee8e
X-MS-TrafficTypeDiagnostic: SA0PR12MB4384:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4384E38FBB1AF02A78A18BA78EB39@SA0PR12MB4384.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ZtNHZNn8ydwiSDhducu4+bgmRccLQ2Wm1u4M4swGFz8mnuGyK5qnIIwIBsO459ZvkrhKydsn1AV0xRw4S1lGG9NySLFzVHPCJb9zfsdOeOHGdu1bouVRbmAVhGS+qvJW7B6r/zKzZ/NSAdANeRhtD3d2Hmx33E0RWa/hMQHsGROfhrvnnq3c2TWaU/B4yOxatsZcNH+SDYeRSkxsJ5EWjM+GdTXqXucLiDvRalakBrW9sW56uOkD4M3sJGa9OrqlaEGfmkrUpPi5iW+KBVtF08LyHMbItXDecvy/2ogxAuyhjs5tYpr0A5AAP7hLZYKeCnSQ0SVOUpWPWMrZkVXhDLcTlJUND0mC7YwgRX0LQ2PSdksXuYXHUderWW/fP7pWM9yb1Dzt9+IkkL2Gc2r873yl9WaEHK2BtIbYFoHpX/jZP6wHz64xynu9VBmU/70CiPOkHHOabzBlU7f9bS+wZPRMXYqZ5f7Hi+K0m0jffr2Fmn8J66etX/gnJSXVdO2xFzZa8caVxS/G435RWOVjnw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(39850400004)(366004)(346002)(376002)(396003)(8936002)(4326008)(66556008)(86362001)(6666004)(66476007)(2906002)(186003)(478600001)(26005)(6916009)(6486002)(5660300002)(52116002)(16526019)(36756003)(7696005)(7416002)(66946007)(83380400001)(8676002)(956004)(2616005)(66574015)(316002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?1LZzPy2pH6N1X70235KQT/ti0Bgnrm?=
	=?utf-8?q?uYL8l9/Kp+c7yvX/Ff/rNwZEE0wjNkEeFN5aT+8+8LksK2XQhJB4UZmrMGrQGIjvl?=
	=?utf-8?q?at5LvBWxBCxTJf059em8E/uuim+8qygzMTfvWyjD6fSg/lXKfoS4vKCgN/JrMnNvc?=
	=?utf-8?q?ovw+BFjGdva8zMRXJDiFObhR1DOMRUMdqqRBooGthh7OLPnReILY+h4srJ79BKliJ?=
	=?utf-8?q?xwr4SbsyYWK9cBHSSQkKpn92lI1GzWTPl8yul1VkiY5M6ZtlGoybxPjUOPa+1lTM5?=
	=?utf-8?q?zDkNr2z9iwnBfseH9DG9aOyqFEuUW+cYmsNeem9rO/h1rvrGC6GkwuMcNippYayGh?=
	=?utf-8?q?xfixvMde76Wbl9dbHeVNFFWEonvLRQ/7x2OICMcaQqNQdGiKCiUwKwi/xiuDvPJVE?=
	=?utf-8?q?olyYRYy7yVfYfrwXezQneHTrJzDL2fLqe9q75gJzPk3/MEIxfVzcrjBxD+d6icHVH?=
	=?utf-8?q?/EEnRwKo11UHCITmhkhc77903JNVkM75gidLyWhnlwYLnYXlEWRVflC5Iy3kpdntS?=
	=?utf-8?q?mAeeYuvn1veo83sfpxCgZS7lDN6lfVeh+vlaeFAtKKXwM9cFGC4oYNPg67ML3cIRy?=
	=?utf-8?q?JTMRyS85q/i8BY84hFPwKkPz3ZKkYSicSLBA+k2HYYMOZacWDzFcYDhF3I+I/1a8g?=
	=?utf-8?q?xRz1smJ/u8VHyvJeb5CVBiWL64tC0X7VsPOk8ERVg3IwjI7ASWzPSjvqSNxMPXsm+?=
	=?utf-8?q?SuTB1AlznUhbXw596QfEAjBM0+cOu7qHAgxnFBliRe/josukt6KA6QvX2zisiZcmP?=
	=?utf-8?q?tgrQtPG57Pz0b+y7av2RU2Ua6x9ElwP4UGAmPeFUnt5v4nkYa4lGHRZ1WhMjHNBCM?=
	=?utf-8?q?+Q++Sl9XkS7c+o+jESwrCjHjhxzdg7BzTUI1xTqyZTG10Fo5msQ/lvQpElfTgfmfY?=
	=?utf-8?q?4rFZwOCVhyon0A0i0Qur8YssX92Rhfz+0bHEQlDLyfs/6BMoMaX/EN4YoysqpkwRC?=
	=?utf-8?q?127y20WEN2Fb4T5V9YJ9HYdL8FsaHhalEssvpKhouiXyrGndcVCF9+hLLr0SB0U/e?=
	=?utf-8?q?bT1OzDxskWaWoSPpuchefRheZ0wF2uneTn5Uo2kHXihwqByGZjJAwpK0V1W78dy9k?=
	=?utf-8?q?Zj8CRHEJwetHueYqIkU/USXjhFyDHqqJKPYi7pH/hO+GfbNeq9x8U01yPC0aQkr4B?=
	=?utf-8?q?PGW0xoIVKgH10R0LhZI6KLtjjB66T93g7XSZFahNrLQyfpBlr2xsllaxiVnS0K2Jh?=
	=?utf-8?q?BC/TzUYpflrOhF7UgG15gZHQK+ETuEh65YxH0U9eiHQKlBx1YEYGikUbRECXe1wAl?=
	=?utf-8?q?cjwaqbBAz5QrQt?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 e9a6b339-b1db-4224-8eba-08d8c8a4ee8e
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 Feb 2021 00:36:37.7026
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 kdDpSJrbYif1TIZMWpFU9qIsepUEdN9FeqezCZ6jZY8AOed1eTz/6r0oBuGc41h4s83mvsKPYYR8CdFYgkISww==
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
#### [PATCH v2 1/6] RISC-V: Mark the existing SBI v0.1 implementation as legacy
##### From: Atish Patra <atish.patra@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Atish Patra <atish.patra@wdc.com>
X-Patchwork-Id: 12066317
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.6 required=3.0 tests=BAYES_00,DKIM_INVALID,
	DKIM_SIGNED,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23869C433E0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 05:34:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CD0FD64DF0
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 05:34:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231530AbhBDFeL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 00:34:11 -0500
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:38831 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230322AbhBDFeC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 00:34:02 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1612416841; x=1643952841;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version:content-transfer-encoding;
  bh=KKoZm/yRaWYpbDjxNyImgz6OnxMRCIBlc1M6mN/Snb4=;
  b=ls1mwO3ObFWflehvMDiTOxWnhEo3rMPV3STbmPHztP6bFY+OLuPxCbPW
   AFoL+CvNsfWVF0fIgm3lZvCh0vjhS4+r+7PNqysPyiW+UVdAXo0mjOWXa
   MuqvOqehMrWhe2DeIdD5H/jaeyjYo3/qlZWNHzmqbWnabLmds5KmtvjP/
   gfqK5smtz1nr+UB5A0tIknuZl7NUkoMnk/Cp4LvA/p5cwDhGvVbsS7zEc
   mma7zY5F6uFjFW6qMR5BW3fGhhEl8Mn4ZDxXM9YNOrVRTJb41MNwbeJjK
   SDvhza/tci3SK973EvA2okueTQZxaOmoMRDcevNE2PGJ5SAZPYpmKcFGj
   A==;
IronPort-SDR: 
 3soR+W/kcUoUJJxHaEbz7lhn49813qTH65T39UoIPt7Zwq2Ykf3MC1mkfCHKp5S6Sdyk/td1s8
 6iwxI970H9woqaYbeN8wZcroJfd2F8Xx1Xl+U4WA2GBsg0XnCZmu1VhbRfKQIGGRbQgwoaOMeK
 1ohWNb9+N+6x/d6S0iwx8er2zSeLXXO/q/yEWQbkR0evL/10Zsjm6PawuOeNk1tPGIbsXs30e4
 xu3zyyIZP9MVb64Rx7tX9bJH8AF6wKXdYb6MO0W33U4B1+I39B3wk6o5SKwOpTNC5dJ48r52qL
 RjM=
X-IronPort-AV: E=Sophos;i="5.79,400,1602518400";
   d="scan'208";a="159086432"
Received: from uls-op-cesaip01.wdc.com (HELO uls-op-cesaep01.wdc.com)
 ([199.255.45.14])
  by ob1.hgst.iphmx.com with ESMTP; 04 Feb 2021 13:32:53 +0800
IronPort-SDR: 
 OBvI8pSho5MYsCVWNGNjHHVBVmIPmW0Lt1sg5eDgOaT/BFUFXXb/mZXuJ6Y5kWG9m0Z/+w+rzj
 mdmF9YX360lS2Pe5noJ/L9mMHmHXPhUVuRGWZGCRLgJjA9FcG89TjqasO96s380CadSGtc9vuE
 nV8d4qQ1MuTSVBCEGSYbnvfzyaIMAHV0fvyquLXWgRk5AfIHn6s3RBa6i8+KCTVCVnDoSAYSye
 Sas10/Msf6SZejGoV/+brG1vc0I1i52wGj9dhaOGb/Yikb67h0L6SsffWPrvT1B4OWdMQhAFSM
 YS1yrdHw51TKv4e5ooVStTxZ
Received: from uls-op-cesaip02.wdc.com ([10.248.3.37])
  by uls-op-cesaep01.wdc.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Feb 2021 21:16:53 -0800
IronPort-SDR: 
 alPokM4Ni8YztwJSBFlZvtaYzFjJvz7QCcB0erZK2+Wb5cT6Mxt0WIBRbZryZm9dHk7/ja734c
 iTWetN/DrwEXAgES68K1mA26oNtJjmfHnHm8tNkAYZrpHthQp/7vnQVuKszl3NcBv95wshIPR8
 lVGqwM3o1OEojPUJoT6s3idyEtiMJDP53bOOlrtmMl6H14ism29w38eII3CNSVCIJtgBOPKJ/I
 wg6+FWvGe426rpHzljdP2zQLHXBVyAN5sXdmX9XRzTo/a76bk+m/5/mvyfDqyqwT96hdU5FoA+
 8Q8=
WDCIronportException: Internal
Received: from cnf008142.ad.shared (HELO jedi-01.hgst.com) ([10.86.63.165])
  by uls-op-cesaip02.wdc.com with ESMTP; 03 Feb 2021 21:32:53 -0800
From: Atish Patra <atish.patra@wdc.com>
To: linux-kernel@vger.kernel.org
Cc: Atish Patra <atish.patra@wdc.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Anup Patel <anup.patel@wdc.com>,
        Kefeng Wang <wangkefeng.wang@huawei.com>,
        kvm-riscv@lists.infradead.org, kvm@vger.kernel.org,
        linux-riscv@lists.infradead.org,
        Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>
Subject: [PATCH v2 1/6] RISC-V: Mark the existing SBI v0.1 implementation as
 legacy
Date: Wed,  3 Feb 2021 21:32:34 -0800
Message-Id: <20210204053239.1609558-2-atish.patra@wdc.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210204053239.1609558-1-atish.patra@wdc.com>
References: <20210204053239.1609558-1-atish.patra@wdc.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The existing SBI specification impelementation follows v0.1 or legacy
specification. The latest specification known as v0.2 allows more
scalability and performance improvements.

Rename the existing implementation as legacy and provide a way to allow
future extensions.

Signed-off-by: Atish Patra <atish.patra@wdc.com>
---
 arch/riscv/include/asm/kvm_vcpu_sbi.h |  29 +++++
 arch/riscv/kvm/vcpu_sbi.c             | 149 ++++++++++++++++++++------
 2 files changed, 148 insertions(+), 30 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_sbi.h

diff --git a/arch/riscv/include/asm/kvm_vcpu_sbi.h b/arch/riscv/include/asm/kvm_vcpu_sbi.h
new file mode 100644
index 000000000000..5b3523a01bce
--- /dev/null
+++ b/arch/riscv/include/asm/kvm_vcpu_sbi.h
@@ -0,0 +1,29 @@
+/* SPDX-License-Identifier: GPL-2.0-only */
+/**
+ * Copyright (c) 2020 Western Digital Corporation or its affiliates.
+ *
+ * Authors:
+ *     Atish Patra <atish.patra@wdc.com>
+ */
+
+#ifndef __RISCV_KVM_VCPU_SBI_H__
+#define __RISCV_KVM_VCPU_SBI_H__
+
+#define KVM_SBI_VERSION_MAJOR 0
+#define KVM_SBI_VERSION_MINOR 2
+
+struct kvm_vcpu_sbi_extension {
+	unsigned long extid_start;
+	unsigned long extid_end;
+	/**
+	 * SBI extension handler. It can be defined for a given extension or group of
+	 * extension. But it should always return linux error codes rather than SBI
+	 * specific error codes.
+	 */
+	int (*handler)(struct kvm_vcpu *vcpu, struct kvm_run *run,
+		       unsigned long *out_val, struct kvm_cpu_trap *utrap,
+		       bool *exit);
+};
+
+const struct kvm_vcpu_sbi_extension *kvm_vcpu_sbi_find_ext(unsigned long extid);
+#endif /* __RISCV_KVM_VCPU_SBI_H__ */
```
#### [PATCH] KVM: SVM: Remove bogus WARN and emulation if guest #GPs with EFER.SVME=1
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12066123
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6228C433DB
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 02:36:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A598564F51
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 02:36:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234533AbhBDCgX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 21:36:23 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42628 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233928AbhBDCgV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 21:36:21 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EFE6FC0613D6
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 18:35:40 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id e62so1952777yba.5
        for <kvm@vger.kernel.org>; Wed, 03 Feb 2021 18:35:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=+Rhoed1XQepPnJf3F6uh773jLZ78lN8W7AVU2qB258o=;
        b=hyYr9tldNB35f9XCt4oiqOeUSNLxT3NzdiZyYRqw2VWSCllNgj7jm86k+RuoZo3WKC
         Q4U6sRpqW1+G9vn2tlCUnmHvyT5H+18d2QWAzl+Wr05TzOvImbvKjxLjMLjanHNltUBv
         Vlv//0aK+8HssbdNw2hanUTO9l8zEJupWTSUKoB2OcElbV4Q1j+sLzlK1ZmBrQwQYYPP
         UsaC1/czjkdIps5Xd7KXfnryrTz+4GuQZT8OuBP1TvjNj6NHkVQYjp0/MmdJ0JKrCuM4
         YMzNqdvDMd13Y7OwjUVX1lvwHxdiKQTWvtvXQ5eGLsgnzmbVykh/0Aj1aFFOh/ZBsP+M
         BPJg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=+Rhoed1XQepPnJf3F6uh773jLZ78lN8W7AVU2qB258o=;
        b=XliIVHAkz8cQSg3nitjmoUzPutzMs38/eEQ4gzQp1a+93nEtW/+MRSSKV0cbpj3Qb0
         I1DPXxr+0TIqqzhbwbg6bLcQfGWSwA6+VJA4+WwhT4pusvJQQim1J1hH478bTxEzPg1R
         GE2KRtUd8SaAHvjEd+YlM6tCYr/G4hEL//FHvC6kKJUluKmLOuo6L3Q130O5vm/7fqDQ
         j/8USGIxPh39P4UuczG+s7ASFE7ORna72AVAA6TGUbIEqMWPNgBpQnnSoCjEIF2ZCKx2
         fFZANuR3jTODea0WnTJodYkVdBiRCtoLUy9F531G/7py8XI/IHj65QlByzbl6sFcOBP3
         ZzhA==
X-Gm-Message-State: AOAM530ciDm4y/k3o5UvxwrDMvUMtw6KKSGTI5GcWGFllmHhjlf5UhuA
        Pab95Q8rEazxupKqbwt259vjyhnNsvs=
X-Google-Smtp-Source: 
 ABdhPJz31YtwdDoZ04CvFBL+71M8C0dpug36wp8GedSEwyhOz06UH9fTvuGaPWWibtMV0aUW3dA9nSUivBU=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:a9a0:e924:d161:b6cb])
 (user=seanjc job=sendgmr) by 2002:a25:4e07:: with SMTP id
 c7mr8588817ybb.288.1612406140095;
 Wed, 03 Feb 2021 18:35:40 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed,  3 Feb 2021 18:35:36 -0800
Message-Id: <20210204023536.3397005-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH] KVM: SVM: Remove bogus WARN and emulation if guest #GPs with
 EFER.SVME=1
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Bandan Das <bsd@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Immediately reinject #GP (if intercepted) if the VMware backdoor is
disabled and the instruction is not affected by the erratum that causes
bogus #GPs on SVM instructions.  It is completely reasonable for the
guest to take a #GP(0) with EFER.SVME=1, e.g. when probing an MSR, and
attempting emulation on an unknown instruction is obviously not good.

Fixes: b3f4e11adc7d ("KVM: SVM: Add emulation support for #GP triggered by SVM instructions")
Cc: Bandan Das <bsd@redhat.com>
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH 01/12] KVM: x86: Set so called 'reserved CR3 bits in LM mask' at vCPU reset
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12065797
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 229F3C433DB
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:02:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D506A64F46
	for <kvm@archiver.kernel.org>; Thu,  4 Feb 2021 00:02:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234104AbhBDACN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 3 Feb 2021 19:02:13 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37656 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234076AbhBDACJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 3 Feb 2021 19:02:09 -0500
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E01A5C061786
        for <kvm@vger.kernel.org>; Wed,  3 Feb 2021 16:01:28 -0800 (PST)
Received: by mail-qv1-xf49.google.com with SMTP id dj13so787148qvb.20
        for <kvm@vger.kernel.org>; Wed, 03 Feb 2021 16:01:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=xlob3SxVBzuk6VwhTKCHNdeQ5cEpkkL7dVmYnzLmun0=;
        b=pCmvpt0R661t/A0DjVN4wniue+VW7yOO9Lz/O/Xm7JfDLttlBTqYdxSlV4GkuGR9jU
         a9LIq3BEDUe05rDusUEU75qDQiaYVUHS5bzdEMX2FPjZg/CXoLDQt9rij4eoLs7LfDHp
         Ezuk43HAN3Mk/CHRnVJaAezIf+YKeVexCGCml8eMfx+1Q97YlZfVLpzkk8RmoTwuMjfU
         QtfryjianriFO4Q3xaHTUV4y+VfFuhfxjsiC4u2Tk2Sp4SXp/mStsWuD49fY5yi+naxC
         43HAuW+/GDYbShHoazRXNnYzbynTUSSiXnKWWUgeY9sHLK8j+MOEXQrBTX/OCDVzraAz
         LBJw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=xlob3SxVBzuk6VwhTKCHNdeQ5cEpkkL7dVmYnzLmun0=;
        b=WmLEmf3fFP0n1J93PQGbQz2UOrdvShsNf0zKQ0AkRrh69tS56MFyPUNeWmfVgjlWZX
         dU7MWyAwJ+IdghFYV9s2WGhBpettYFGS/TW+d7JhtrQ8aDAKWvOkTdpWjvLJpMIqWYiH
         Q+BernHmYU4qO/R3IhI8uptPX776zrtHX1MYIZSQgKqVJmBB6y0SKRod6emJVk8D0K5i
         xDFPBNHKCCNLkfDRxDFxsWtXL4k1V0iqhHqhPYiegakF2aPCCFb0+rikMk8iQzOaqSa/
         VBMi5+KfHw7AF9Pui8G3NNCSvW49sm3u0si+dwPvXPma2zb2iRDucpCXW7h4vzYWCJBv
         JiWQ==
X-Gm-Message-State: AOAM5330czn1lcZpfRb3rAX+aV01P2/q49dYUZLIg2pKNQj9AaLj4fTa
        6CAlfo12GJ1eP7vNzUloU/7//LBtHgQ=
X-Google-Smtp-Source: 
 ABdhPJwbxo0jhQm0FLX75tZWB7FNsV1Ul3pvxTbJF9kRwBzPSD9aQGisdB56VNOpsohROXiIsNxiNEsR3GQ=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:a9a0:e924:d161:b6cb])
 (user=seanjc job=sendgmr) by 2002:a0c:c78c:: with SMTP id
 k12mr5114776qvj.47.1612396888075;
 Wed, 03 Feb 2021 16:01:28 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed,  3 Feb 2021 16:01:06 -0800
In-Reply-To: <20210204000117.3303214-1-seanjc@google.com>
Message-Id: <20210204000117.3303214-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210204000117.3303214-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 01/12] KVM: x86: Set so called 'reserved CR3 bits in LM mask'
 at vCPU reset
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Rick Edgecombe <rick.p.edgecombe@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Set cr3_lm_rsvd_bits, which is effectively an invalid GPA mask, at vCPU
reset.  The reserved bits check needs to be done even if userspace never
configures the guest's CPUID model.

Cc: stable@vger.kernel.org
Fixes: 0107973a80ad ("KVM: x86: Introduce cr3_lm_rsvd_bits in kvm_vcpu_arch")
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
