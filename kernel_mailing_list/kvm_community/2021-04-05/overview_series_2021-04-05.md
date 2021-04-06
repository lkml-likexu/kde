#### [PATCH v11 01/13] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12182951
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A0E62C433B4
	for <kvm@archiver.kernel.org>; Mon,  5 Apr 2021 14:21:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7288E613B5
	for <kvm@archiver.kernel.org>; Mon,  5 Apr 2021 14:21:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241306AbhDEOVn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 5 Apr 2021 10:21:43 -0400
Received: from mail-bn8nam12on2078.outbound.protection.outlook.com
 ([40.107.237.78]:15969
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S237153AbhDEOVm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Apr 2021 10:21:42 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jUyr67wqGRCMr+gRODwwKsUNtbx7BzDSelI+Z9VMoKRRFAzRLfEEwU45XDKkOGuyw9LJWoDvV/iI0DSyFnqCgo4h2M88dng2e1+8BgijzudhXTqS3NYr1O33sM4PuLNnUYtynoCVV4isNhOK4YToRVG9F2oY2FhwVDctkTqSup1Cw/f6BGVw1eRLuTZY/yuj9lo9OcTcw0yPBLY0wlmRcdA9g+/izBU26Vp6lCHLTuKjtp1o5MELoIj+fiNHhQCiQpnb4SDteYlm/vZiwWu8RohsqcrR4xgxAiphQZ+N0IQA1qYgjPr4HLfQkNaKCflFy2fyI1PWU5j+KW19966NCQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=dwNnLNRUv5mOEGzwRlzT9gDjN/z4C9yWBsrrvrrgHoZa7J+BbpGr+DGX6ObWx7IJmmobz0kjfuQrd/yTcuJDcFDKJ1RduBVeaHV6rVIAqqjcr3+oeZ5sKWiv5+Ej+w70SFyjXurC9WwJ0GQWqfLe9L7qlTB/oAbkDQvE/la3KlW0S3lrF5hLyWGocSHMoloBdSg0bA+lFG0MX7y3BqnsqtkPxULSa9kUlX3Whmx/ywhuYchcd+nTvLK+c8viMvA1Nzp4YJPYc6VoqNu2s5lSwO5pCLBNEFIpiVFCc+nX+rgdRw6fzQGKZV0ESWR9UFkbNNa95pH3dWxdfJaFeXamqg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=p9+vMxeGG/Np/pHxZBLItVNVJH2aLDUxgz42hCBtD2c=;
 b=25FevdG+zUOahB3nPyieqa0f0Wh7/6/jO4F3jGuRdiz1mpBXtp/46AsB7gSqyVP9AVfVQqGL9rtXPtpchP0lyxbml7u0RUFHoFufR7kFpnZ7Jo1JhdafixHU4/1mUEB3wtsySjodNUlMZIpmeDWv/kk7LHvLode07Y2ImceicKo=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4557.namprd12.prod.outlook.com (2603:10b6:806:9d::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Mon, 5 Apr
 2021 14:21:34 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::24bb:3e53:c95e:cb8e%7]) with mapi id 15.20.3999.032; Mon, 5 Apr 2021
 14:21:34 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, srutherford@google.com,
        seanjc@google.com, venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v11 01/13] KVM: SVM: Add KVM_SEV SEND_START command
Date: Mon,  5 Apr 2021 14:21:24 +0000
Message-Id: 
 <2f1686d0164e0f1b3d6a41d620408393e0a48376.1617302792.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1617302792.git.ashish.kalra@amd.com>
References: <cover.1617302792.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA9PR03CA0001.namprd03.prod.outlook.com
 (2603:10b6:806:20::6) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SA9PR03CA0001.namprd03.prod.outlook.com (2603:10b6:806:20::6) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.27 via Frontend
 Transport; Mon, 5 Apr 2021 14:21:33 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 7f6f66aa-b896-4e6b-17bb-08d8f83e1db4
X-MS-TrafficTypeDiagnostic: SA0PR12MB4557:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4557626F0CE86A3A8377F1568E779@SA0PR12MB4557.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3826;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 p+Z6VjhV00tRpj4tD4KxMFBFu3zAZkXZ6VFL8pb+UbQX0NHFVn/BIkCkyZJ82XjFAZtDazjh5qLy6PrkvrEtPx+2n7DTf56VP+9bVTS58g4HCugkvslL6k9vahFca2QCxwaBdLzdrIONjYHmZxQU0XZvmy/DWWOiorTeL9iAWXnl1A2uk71TIZYstwQWJ5X5VutsHD3wNAQEg6IZvcBZbs48JrgHg+NJ99dF3OxwuRqmJ/ytV/B7O6LNyoEPeuNuQkNdK1H4NFINfKFHjUA6EIyAmGvv9RK33Q0ApGFhuU9XQmVTF/oij9IBlfvHqVmelIdwz2jHWwatgjEJwdush16R3U2yv84WU+UOHwXPjXrizZ3JjRypv0hfmcZTZVxmjuj5/O00TSx+4pyIHBlJi/YPeilDE90/FF8H7USk4Jk4slcedY1Xh8ERik/38qylFS8/o716fOIHG80uwj1f3k8XMlaJw42c6BeHw6nwSwrk9+jOqbPIz1PweWTyGxi0GXk7eBwpwYCz+n+F4X8dwR8PaPhlwFC0FdWT9ARI/583Bxgkoen2SRfYtKyey1dDd/okt8SQZMaZR5mWnV9qsfKeniRFb5ofXbrOkeo+q5a6gQimPjIvV6B6aRxvLgIghdxEk05NDU94dU0Yu6RQWbxRG+goBqmKZglI7+jbkQA=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39860400002)(346002)(136003)(366004)(376002)(956004)(6916009)(4326008)(52116002)(7696005)(8676002)(316002)(8936002)(36756003)(66556008)(26005)(5660300002)(66946007)(38100700001)(6666004)(83380400001)(2616005)(66476007)(478600001)(2906002)(16526019)(86362001)(186003)(6486002)(7416002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?73otMRskXsD17PG3jo0FYSYB4laI2P?=
	=?utf-8?q?4Cp5HLqtOP6GPp/FwMzvmYZChyOzY4//w7evWt18MLILxBqowY1Q4qgtLT43zlr96?=
	=?utf-8?q?tAM7Iz9KQ6lt8mX1BLb71hpkSCtgtgNvPRlGrl6VSEOBUZZXDB+6QcLdiHYybfD3O?=
	=?utf-8?q?yPaOHRZvgR5kqhFoN55S2SeUZJg13HOL+EZjUpBOXV9t/sG15vOkGmkDwWzEmbca0?=
	=?utf-8?q?mzv5kARAroioKwaCW349WAys7JLq9XEYXTl2a/DYnXt+qkfSiIJlXPFYXJrHv4ehw?=
	=?utf-8?q?DpKsFnppbXb99mwJqwdHcUd6jGNYFE0nSzdycuC8Ncm4MwjWPs+WUkvQIrXN3CJIE?=
	=?utf-8?q?n70gfpAxV6UJ/S1lr5fgPhfi+lV0ckJaB06ZIzF74sXuoZ783Fl3zP0PRinVxHM0y?=
	=?utf-8?q?y5IjFFS0qY9KIHkKjKqtdKNB7S2lGgoyMC+2Z2ecbb1RKgXCNm8ES2N/l2cwtLNrY?=
	=?utf-8?q?7cXKJSZreoahMLckwC76UyWYYMeKNv6gW1Z0aav882bNeryO0z//QSKrM1YnprXCx?=
	=?utf-8?q?8GuCWEox1jYRKsYURsVk8olUxk/xQ0d3oCHyPSzyRiXKuMeoA1kcKMrLO+rDMQ/ds?=
	=?utf-8?q?7nCUTigeuNSgILPJUa53vlOnvg7ATu3huCgL4/3GbREDpOwm3mf39gPUu90hCq4lZ?=
	=?utf-8?q?3kuWzlpe0kMaUcb9KRzxWsL1k3AxD0NhoPGrzGgIbweg/L0kROMw8U2yyRpZ+EGgj?=
	=?utf-8?q?b4tKxXBAuu2z1rKsjkhZauE16c59xUXKnhNMZqwveyVEBbNSo/9Jma/C8xvLCIb12?=
	=?utf-8?q?ScWTAzinHTgNDpsc7AKZEJzcnMFqc1gSWz3c8p3ZDFW0JwEJSji9h3v/ipMCV6rQX?=
	=?utf-8?q?gKcO7G2Md9QizvWM6Thr3NQ1Rbdcoke8nHvw0CoVsXH8/9u17rokrr7UqXvlWm//U?=
	=?utf-8?q?vi23BrXc+Hpvi58vOTsGRCEuh9Hyd+WOgad5xQkTCIAH4Jas8JJ4nnAbu4HWbC2qm?=
	=?utf-8?q?MdOaBVS+3lkRIXHkCXYavN5OdsjbEKbkaWzRJB0rlPsY7ffsZSKj9ykWcHv8KL1lJ?=
	=?utf-8?q?Y6rKHssWhrGru/XVbZ64zAtfs3XomXvHbcb0fx6OBcDDlWnP2JYaaicJtqxBmLn23?=
	=?utf-8?q?yejwyasuml8Jq5yTqT14TBzd67Q0BZ5nu552PJfB+EeWAgnzoqgJ23+nFGb/OSNWe?=
	=?utf-8?q?OEQz6ICxzj65e2xbFC5J0aDXaaFJM9GiZ1tvfdbblJiN+WFWq4ZqxS7G+SFjkl/+U?=
	=?utf-8?q?D6LaWOSXvtobVDT2jf9Oxgztvy6PA7QpCC1Fw6DFtvc2ChTEzcCzGGnJT+O+eKALU?=
	=?utf-8?q?XQmJWxr/6VY32K?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 7f6f66aa-b896-4e6b-17bb-08d8f83e1db4
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 05 Apr 2021 14:21:34.5306
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5/wNpaYDaTfii61WSH7CUhKSLea4HAWNquaMuxetL6RcVLf843SIXn4V26JMW3alE6utrEeTGbnNIRboQwx0Cg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4557
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
#### [PATCH v6 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12183273
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C101C43461
	for <kvm@archiver.kernel.org>; Mon,  5 Apr 2021 16:40:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E908B613BB
	for <kvm@archiver.kernel.org>; Mon,  5 Apr 2021 16:40:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242396AbhDEQkI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 5 Apr 2021 12:40:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:38118 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234030AbhDEQkG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 5 Apr 2021 12:40:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617640800;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=T++kfV6UZciWC8yKgENOTDcBheE14f6N7T7hHgmDxGg=;
        b=R4OFCLZIbbMBoQie5VVDj4THp3qvzhif5rRuhMboozbW2J5Uh4mPJzK3I/jgBECRIdfVvA
        +/JSmmFf8bY2CypOhgD/uYpg583moaytE0vRMk3i7xbmm+M3OYm6NEkPvFxjVFpD8ihleD
        EYuMZ9bR/a1o4KcrzU0AgSBzqH3WyFw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-329-zKywC754PBu6I7O8r3d9gg-1; Mon, 05 Apr 2021 12:39:58 -0400
X-MC-Unique: zKywC754PBu6I7O8r3d9gg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8AB3F84BA40;
        Mon,  5 Apr 2021 16:39:56 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-13.ams2.redhat.com [10.36.112.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E3B1519715;
        Mon,  5 Apr 2021 16:39:53 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com
Cc: james.morse@arm.com, suzuki.poulose@arm.com, shuah@kernel.org,
        pbonzini@redhat.com
Subject: [PATCH v6 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting
 RDIST base
Date: Mon,  5 Apr 2021 18:39:33 +0200
Message-Id: <20210405163941.510258-2-eric.auger@redhat.com>
In-Reply-To: <20210405163941.510258-1-eric.auger@redhat.com>
References: <20210405163941.510258-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_DEV_ARM_VGIC_GRP_ADDR group doc says we should return
-EEXIST in case the base address of the redist is already set.
We currently return -EINVAL.

However we need to return -EINVAL in case a legacy REDIST address
is attempted to be set while REDIST_REGIONS were set. This case
is discriminated by looking at the count field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
v3 -> v4:
- rewrite the test checking that we do not mix rdist region types

v1 -> v2:
- simplify the check sequence
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 14 +++++++-------
 1 file changed, 7 insertions(+), 7 deletions(-)

```
