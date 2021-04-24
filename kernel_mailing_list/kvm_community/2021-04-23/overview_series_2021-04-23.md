#### [PATCH v2 1/4] KVM: x86: invert KVM_HYPERCALL to default to VMMCALL
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12220819
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62013C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 15:58:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2FAA860C40
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 15:58:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230294AbhDWP7P (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 11:59:15 -0400
Received: from mail-bn8nam12on2089.outbound.protection.outlook.com
 ([40.107.237.89]:21216
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S243068AbhDWP7O (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 11:59:14 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ksJe6jpa9G4Wn17zN63uA/b78ftNWToON2m7Z5eUCO6uaGfpeuoU6NfAYVxeGGtTbVlNgsaLz/PTwNzEYSL5idjO1NBFW8oASpzAe1GJn0mcpHRTguyIdNzVmVe0qhEKqvwG3Ik+MaKsMU+tFVlFcD5bUCguiAOuIGb1DV5yrUKA53LG4LQyYWaAg1MHhg5OplxLuafbMdqnjGIw1HkWyOBgUJfPH6KmipfMqMvokQ8dK1vktS0et/wSNKocUaAXkWHyMQLUus5qYyC68NswxtTZdb/uAoaWsxqICbMg0qMSbDAKF/kRGDpgNAHk2ukyQg+Y89tfSHdW7tGKYm7yow==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kbX6VSM3gY2hDVfwBpZ4zpupPxEYMewOcFc83mr9Buc=;
 b=R9lmtPX7MT0btvU3RwwN/U5raVb3P9EYLI6jSeh0VOxFUfVldHZ80rn6fYoK8CXUqG1b9BwA7YEJHfg5WuGVsLEvItebsISgKv61yrlxsPa9n9VEYbkiLU0SmZGR7W1cHx5BCvORvx94epmmVBk6k7w/zhfm9k8vYlbrH7vgLpMZ5U+Mn3d+e1d6vVSIqcGqDQlCZYF097BM2kJRsrYbM737NmzfKyTDkN6JVw+pA90xFEmVF7H8JHwtvpOC1api2YUaXNKKb+tpkyXRb7jX3vGorHKqlaMjOy72HBLi+192yvnEP1kBkWYib9zt8MSVXISKLfOFIBCEY1IH2nl2CQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kbX6VSM3gY2hDVfwBpZ4zpupPxEYMewOcFc83mr9Buc=;
 b=VOeRUdY+jJpQmXKGXaWCdUm42qZ3WD/44A8HCSxtyMjNiEjQgogznL13JgxaGevG/qmoumqTxxchMiHQRF6IPaKE8oVujVHhcO3jQedjteZHzr1kScJUVgPOUe5eWHo3FlabllPnCLfbb8eesQyCeTHBk9xEsWOlNB1kVHA71ps=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2639.namprd12.prod.outlook.com (2603:10b6:805:75::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.18; Fri, 23 Apr
 2021 15:58:34 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%7]) with mapi id 15.20.4065.025; Fri, 23 Apr 2021
 15:58:34 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v2 1/4] KVM: x86: invert KVM_HYPERCALL to default to VMMCALL
Date: Fri, 23 Apr 2021 15:58:24 +0000
Message-Id: 
 <76ad1a3f7ce817e8d269a6d58293fc128678affc.1619193043.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1619193043.git.ashish.kalra@amd.com>
References: <cover.1619193043.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0078.namprd11.prod.outlook.com
 (2603:10b6:806:d2::23) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SA0PR11CA0078.namprd11.prod.outlook.com (2603:10b6:806:d2::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.21 via Frontend
 Transport; Fri, 23 Apr 2021 15:58:34 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 5d28f07b-add5-4ab9-f28b-08d90670a639
X-MS-TrafficTypeDiagnostic: SN6PR12MB2639:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2639E3F467017B9E309AFA848E459@SN6PR12MB2639.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5516;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 mkziyzWRth5e/CaMoZEhdZUXWWMzGWDCvc2cm3unEbW4nZnKKAbicBArySox2X/nfCGUEBFZYVR5KWCBlmsQJNJpf/bWyQxMQ/83kAMfc81wSDNWuq60av7hgg+zDV0qD0Kj7lSZ1dY7Lr5VkopMODhY1ew8Lk7S40wN/Z1GjF5fEadQqus8GxgRoARtpHSLTMr/0AdMQTwUtXadZ1OBzFRJ6yo+9lCW7naByqa5D/aq2lh3wREdXACxOQv/JFYnvJznJ9Oz35GczL26FeqVq2HPuZOS2oeztx5ywQi4L2VD8L5Y4cHhuii+dgzOPCmQ6ghtSEcwb0BRYVlCReO1RYNoZaKKnL974tAXM/KT/gZsH3KUDuvTQ+mBKpdp/w9ubYWeve1EG5XeJhg6Ucf4+8jF9uAFc/ZJ8QJtWeLCF4sEi9smoZV/bbpPV/ELxWiSkSbu6+/huWfAYZNPHEpAYKx58RwWM8vJGltm3zdYV+CwINjeK+YKI0lkbi2bIWozsKbyuDUicMlFDaIsatxnyyatnh2iezRcwuGK9h1Ql9HVTG48Aq2ZmlX+kJ8VCYR/+YNOP4Mn5C6afVybWD9Mib0mLLf7jwEcsjFdszqbSrC15pmvuRwebWZwhgoQVpMXRwPGptvcSbQOsFDZaAXANsrG5JfwYBvNR0MDE0Sl77A=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(136003)(346002)(396003)(376002)(39850400004)(66556008)(66946007)(6916009)(4326008)(478600001)(956004)(8936002)(26005)(186003)(316002)(6666004)(7416002)(52116002)(2616005)(6486002)(8676002)(5660300002)(2906002)(38100700002)(83380400001)(38350700002)(36756003)(66476007)(16526019)(86362001)(7696005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 62ZnAa/BMWbdQBtPHfdu3bve5+E3xVbAqTIWScI1++cZ6bVja530mGioQuMR2bSZ6uTpXYr8CI9utUb79O5CkQpKiKrcP7yIuAAxzfse5qLb5OP5F2DzHvkb/5mFj73RlgHBdCTTa7vWPqFpwJlaqVUkE2DgsO1F0r7QxKt3gETE54q5pu2U/xoue9Et9rWqpn0qPL4QZ4pLhfgwJQS6vu25ecb8leHTDlaVtpoYwkiU3WD7/7FgEmFrPBMLJxhSd9C7GEbzxg/fPrh2f1xP87u3k0a8F+WqTex2I33kZaMqR1gn6BDEq/gl6vKvDF4rC3OQqSPfg5rh8iwlJOhFoOwZJR+/cdzL6DEbjLSo81ZpLvoMeTWPS9CJv4tOD5no+9DkoLs5/pv5YuzY6xBAhwysNBuxziT0CjJzhAIvaup3g2BJjosOscP2/p6E8+SkKwsGoiAMsqReAE7+r3YS2S+v4PQqu/HnpC5aqmt+Y2p29fF6qtv2UuUFdXVNlpxoPjqFplbmGkYNtSG2nkdGSQqGuV+D9GBEkYqMZ0lFYayRYP/HfaUVTtCP1daqSw5NDQoOohkFubFA2r31rKhQeo8EV+0IoPXjzJq9PmEiM2hgtBNqz6H7QAnueurbXKr75P13KWPFadmho50xXwk/Yh31gP2Ebvw1KccVgfJNMFz6NR6HzNAd0qLoN/ESg9ZqrTuFTodfGEv89wPe+QLB4OP37cRwiUl2QJJ7ncqINrbjFgSQbPcVKXQldUzKDlCiRh9z/uSb4GKzP7FXmF9wzf7XnA6lgHK2dhAfx7qgYG8te2n+VIg6l8MhWHpxr1jf9z9X6IbHZCRNmuFQDEzQ86rVMb4NIHOnhkbXXM6FVD8mhgIa8Fci/jckvirdi1jpVilpnR3B7u+AUdxB0gV88hG2CfCbPTec5zaGHdCHm/Pe8yU1uE2XwZryLHgfAF5Yx/DoPkok7ypTdSX3uoKlV2uXsU8d3NYyo7s4Km94DZeXAb33azrHLPcX03ZbOAFj4uw8xEJo8JbEtUytqLf2o9GAA2OX44Ao/RsSEmXLJDT1tNs1l91y/VwlQn5mo5tcVxsydinKmEqv45Gt0DsCX2U72rTqUxGyP3120XimkgRtKIcgKxM6rtwImZPjcWN+r0lTIJVuILwb9lha8EG3QFYHGzDX2W9L5cOC9Zsyq/AxDMwMU9/bsQByIE+9u/naqeCwXcb0UwrFmUdTz8EViFmOfPUggjrSYUltwv2+w3RnVRYIlCq32SF9dyRILR9sdZGShfdGKmsRfeXjLp52sgQ2JDNTPtdXDZuT2Q9N5p5XATvYRDM8H3c1HkdKIIMY
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5d28f07b-add5-4ab9-f28b-08d90670a639
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Apr 2021 15:58:34.8612
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 hNe+5IaySuLt9JjE2WuQtsAPe894mu3G6FPi8LTZZMYX+VA0gZfaJbVWExcifJM/CJEFAJu6+GygavBrTyNkKQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2639
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

KVM hypercall framework relies on alternative framework to patch the
VMCALL -> VMMCALL on AMD platform. If a hypercall is made before
apply_alternative() is called then it defaults to VMCALL. The approach
works fine on non SEV guest. A VMCALL would causes #UD, and hypervisor
will be able to decode the instruction and do the right things. But
when SEV is active, guest memory is encrypted with guest key and
hypervisor will not be able to decode the instruction bytes.

So invert KVM_HYPERCALL and X86_FEATURE_VMMCALL to default to VMMCALL
and opt into VMCALL.

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
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 arch/x86/include/asm/kvm_para.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH V2 1/7] virtio-ring: maintain next in extra state for packed virtqueue
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 12219839
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EA980C433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:10:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B684F6128A
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:10:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241378AbhDWILJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 04:11:09 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:38982 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241361AbhDWILI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Apr 2021 04:11:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619165432;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=OdzRn3Pr0rYI0rGRBMCl0SRE17R3Lml0KXCJ6hRRlik=;
        b=XVaoCC92jaSW7OUytdNwnYw9K/I4yHK3xU7FGr83xS8abP6ZAFdNxBtrL3+UY23lD51UAc
        MeiehOL5XZhmIs/JFG3MpL9aG1e4UKrip/NzPI2YBHYS8GAoMcQwtvMrbia/Q13cV0As7P
        umicPxxViRzHYkpxVQ2jcMNaRAgA+QM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-445-LEtF0w2zOQWjQREk2-Cjcg-1; Fri, 23 Apr 2021 04:10:28 -0400
X-MC-Unique: LEtF0w2zOQWjQREk2-Cjcg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ADC6F107ACC7;
        Fri, 23 Apr 2021 08:10:26 +0000 (UTC)
Received: from localhost.localdomain (ovpn-13-225.pek2.redhat.com
 [10.72.13.225])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B49A45C541;
        Fri, 23 Apr 2021 08:10:07 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, xieyongji@bytedance.com,
        stefanha@redhat.com, file@sect.tu-berlin.de, ashish.kalra@amd.com,
        konrad.wilk@oracle.com, kvm@vger.kernel.org, hch@infradead.org
Subject: [RFC PATCH V2 1/7] virtio-ring: maintain next in extra state for
 packed virtqueue
Date: Fri, 23 Apr 2021 16:09:36 +0800
Message-Id: <20210423080942.2997-2-jasowang@redhat.com>
In-Reply-To: <20210423080942.2997-1-jasowang@redhat.com>
References: <20210423080942.2997-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch moves next from vring_desc_state_packed to
vring_desc_desc_extra_packed. This makes it simpler to let extra state
to be reused by split virtqueue.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/virtio/virtio_ring.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [GIT PULL] KVM/arm64 updates for 5.13
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12220157
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 29580C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 11:36:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3AAD61409
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 11:36:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S242185AbhDWLgv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 07:36:51 -0400
Received: from mail.kernel.org ([198.145.29.99]:47746 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236905AbhDWLgr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 07:36:47 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5D6E361409;
        Fri, 23 Apr 2021 11:36:10 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lZu6S-0093oH-0E; Fri, 23 Apr 2021 12:36:08 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andre Przywara <andre.przywara@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Andrew Scull <ascull@google.com>,
        Anshuman Khandual <anshuman.khandual@arm.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Daniel Kiss <daniel.kiss@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Jianyong Wu <jianyong.wu@arm.com>,
        Jon Hunter <jonathanh@nvidia.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Quentin Perret <qperret@google.com>,
        Richard Cochran <richardcochran@gmail.com>,
        Shenming Lu <lushenming@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Will Deacon <will@kernel.org>,
        Xiaofei Tan <tanxiaofei@huawei.com>,
        Xu Jia <xujia39@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 updates for 5.13
Date: Fri, 23 Apr 2021 12:35:44 +0100
Message-Id: <20210423113544.1726204-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 andre.przywara@arm.com, drjones@redhat.com, ascull@google.com,
 anshuman.khandual@arm.com, ardb@kernel.org, catalin.marinas@arm.com,
 daniel.kiss@arm.com, dbrazdil@google.com, eric.auger@redhat.com,
 gshan@redhat.com, james.morse@arm.com, jianyong.wu@arm.com,
 jonathanh@nvidia.com, julien.thierry.kdev@gmail.com, zhukeqian1@huawei.com,
 mark.rutland@arm.com, mathieu.poirier@linaro.org, qperret@google.com,
 richardcochran@gmail.com, lushenming@huawei.com, suzuki.poulose@arm.com,
 tglx@linutronix.de, will@kernel.org, tanxiaofei@huawei.com,
 xujia39@huawei.com, yuzenghui@huawei.com, linux-kernel@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the rather large pull request for 5.13. Changes are all over
the map, but the big ticket items are the S2 host isolation when
running in protected mode, the save/restore support for GICv4.1 and
guest SVE support in nVHE mode. Plenty of fixes too.

Note that this pull request drags a number of branches from other
trees in order to avoid conflicts and make people's life easier:

- the Coresight ETE/TRBE branch, as it is intertwined with the KVM
  tracing support

- the arm64 vhe-only branch that deals with broken CPUs such as the
  Apple M1

- the arm64 neon-softirqs-disabled that improves the support for
  FP processing

You will still get a couple of conflicts with the KVM tree, but these
are absolutely trivial to resolve.

Please pull,

	M.

The following changes since commit 1e28eed17697bcf343c6743f0028cc3b5dd88bf0:

  Linux 5.12-rc3 (2021-03-14 14:41:02 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.13

for you to fetch changes up to 9a8aae605b80fc0a830cdce747eed48e11acc067:

  Merge branch 'kvm-arm64/kill_oprofile_dependency' into kvmarm-master/next (2021-04-22 13:41:49 +0100)

----------------------------------------------------------------
KVM/arm64 updates for Linux 5.13

New features:

- Stage-2 isolation for the host kernel when running in protected mode
- Guest SVE support when running in nVHE mode
- Force W^X hypervisor mappings in nVHE mode
- ITS save/restore for guests using direct injection with GICv4.1
- nVHE panics now produce readable backtraces
- Guest support for PTP using the ptp_kvm driver
- Performance improvements in the S2 fault handler
- Alexandru is now a reviewer (not really a new feature...)

Fixes:
- Proper emulation of the GICR_TYPER register
- Handle the complete set of relocation in the nVHE EL2 object
- Get rid of the oprofile dependency in the PMU code (and of the
  oprofile body parts at the same time)
- Debug and SPE fixes
- Fix vcpu reset

----------------------------------------------------------------
Alexandru Elisei (4):
      Documentation: KVM: Document KVM_GUESTDBG_USE_HW control flag for arm64
      KVM: arm64: Initialize VCPU mdcr_el2 before loading it
      KVM: arm64: Don't print warning when trapping SPE registers
      KVM: arm64: Don't advertise FEAT_SPE to guests

Andrew Scull (5):
      bug: Remove redundant condition check in report_bug
      bug: Factor out a getter for a bug's file line
      bug: Assign values once in bug_get_file_line()
      KVM: arm64: Use BUG and BUG_ON in nVHE hyp
      KVM: arm64: Log source when panicking from nVHE hyp

Anshuman Khandual (5):
      arm64: Add TRBE definitions
      coresight: core: Add support for dedicated percpu sinks
      coresight: sink: Add TRBE driver
      Documentation: coresight: trbe: Sysfs ABI description
      Documentation: trace: Add documentation for TRBE

Ard Biesheuvel (3):
      arm64: assembler: remove conditional NEON yield macros
      arm64: assembler: introduce wxN aliases for wN registers
      arm64: fpsimd: run kernel mode NEON with softirqs disabled

Daniel Kiss (1):
      KVM: arm64: Enable SVE support for nVHE

David Brazdil (1):
      KVM: arm64: Support PREL/PLT relocs in EL2 code

Eric Auger (11):
      KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
      KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
      KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
      KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
      docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
      KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
      kvm: arm64: vgic-v3: Introduce vgic_v3_free_redist_region()
      KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
      KVM: selftests: aarch64/vgic-v3 init sequence tests
      KVM: selftests: vgic_init kvm selftests fixup
      KVM: arm/arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST read

Gavin Shan (3):
      KVM: arm64: Hide kvm_mmu_wp_memory_region()
      KVM: arm64: Use find_vma_intersection()
      KVM: arm64: Don't retrieve memory slot again in page fault handler

Jianyong Wu (4):
      ptp: Reorganize ptp_kvm.c to make it arch-independent
      clocksource: Add clocksource id for arm arch counter
      KVM: arm64: Add support for the KVM PTP service
      ptp: arm/arm64: Enable ptp_kvm for arm/arm64

Jon Hunter (1):
      ptp: Don't print an error if ptp_kvm is not supported

Marc Zyngier (50):
      KVM: arm64: Provide KVM's own save/restore SVE primitives
      KVM: arm64: Use {read,write}_sysreg_el1 to access ZCR_EL1
      KVM: arm64: Let vcpu_sve_pffr() handle HYP VAs
      KVM: arm64: Introduce vcpu_sve_vq() helper
      arm64: sve: Provide a conditional update accessor for ZCR_ELx
      KVM: arm64: Rework SVE host-save/guest-restore
      KVM: arm64: Map SVE context at EL2 when available
      KVM: arm64: Save guest's ZCR_EL1 before saving the FPSIMD state
      KVM: arm64: Trap host SVE accesses when the FPSIMD state is dirty
      KVM: arm64: Save/restore SVE state for nVHE
      arm64: Use INIT_SCTLR_EL1_MMU_OFF to disable the MMU on CPU restart
      KVM: arm64: Use INIT_SCTLR_EL2_MMU_OFF to disable the MMU on KVM teardown
      KVM: arm64: Turn SCTLR_ELx_FLAGS into INIT_SCTLR_EL2_MMU_ON
      KVM: arm64: Force SCTLR_EL2.WXN when running nVHE
      KVM: arm64: Fix host's ZCR_EL2 restore on nVHE
      Merge tag 'v5.12-rc3' into kvm-arm64/host-stage2
      irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping
      KVM: arm64: Generate final CTR_EL0 value when running in Protected mode
      KVM: arm64: Drop the CPU_FTR_REG_HYP_COPY infrastructure
      KVM: arm64: Elect Alexandru as a replacement for Julien as a reviewer
      KVM: arm64: Mark the kvmarm ML as moderated for non-subscribers
      KVM: arm64: Fix table format for PTP documentation
      Merge remote-tracking branch 'coresight/next-ETE-TRBE' into kvmarm-master/next
      arm64: cpufeature: Allow early filtering of feature override
      arm64: Cope with CPUs stuck in VHE mode
      arm64: Get rid of CONFIG_ARM64_VHE
      KVM: arm64: Clarify vcpu reset behaviour
      KVM: arm64: Fully zero the vcpu state on reset
      Merge branch 'kvm-arm64/debug-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/host-stage2' into kvmarm-master/next
      Merge branch 'kvm-arm64/memslot-fixes' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-panic-info' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-sve' into kvmarm-master/next
      Merge branch 'kvm-arm64/nvhe-wxn' into kvmarm-master/next
      Merge branch 'kvm-arm64/ptp' into kvmarm-master/next
      Merge branch 'kvm-arm64/vgic-5.13' into kvmarm-master/next
      Merge branch 'kvm-arm64/vlpi-save-restore' into kvmarm-master/next
      Merge remote-tracking branch 'arm64/for-next/vhe-only' into kvmarm-master/next
      Merge remote-tracking branch 'arm64/for-next/neon-softirqs-disabled' into kvmarm-master/next
      Merge remote-tracking branch 'coresight/next-ETE-TRBE' into kvmarm-master/next
      bug: Provide dummy version of bug_get_file_line() when !GENERIC_BUG
      Merge branch 'kvm-arm64/nvhe-panic-info' into kvmarm-master/next
      Merge branch 'kvm-arm64/ptp' into kvmarm-master/next
      KVM: arm64: Divorce the perf code from oprofile helpers
      arm64: Get rid of oprofile leftovers
      s390: Get rid of oprofile leftovers
      sh: Get rid of oprofile leftovers
      perf: Get rid of oprofile leftovers
      Merge branch 'kvm-arm64/kill_oprofile_dependency' into kvmarm-master/next

Quentin Perret (35):
      KVM: arm64: Initialize kvm_nvhe_init_params early
      KVM: arm64: Avoid free_page() in page-table allocator
      KVM: arm64: Factor memory allocation out of pgtable.c
      KVM: arm64: Introduce a BSS section for use at Hyp
      KVM: arm64: Make kvm_call_hyp() a function call at Hyp
      KVM: arm64: Allow using kvm_nvhe_sym() in hyp code
      KVM: arm64: Introduce an early Hyp page allocator
      KVM: arm64: Stub CONFIG_DEBUG_LIST at Hyp
      KVM: arm64: Introduce a Hyp buddy page allocator
      KVM: arm64: Enable access to sanitized CPU features at EL2
      KVM: arm64: Provide __flush_dcache_area at EL2
      KVM: arm64: Factor out vector address calculation
      arm64: asm: Provide set_sctlr_el2 macro
      KVM: arm64: Prepare the creation of s1 mappings at EL2
      KVM: arm64: Elevate hypervisor mappings creation at EL2
      KVM: arm64: Use kvm_arch for stage 2 pgtable
      KVM: arm64: Use kvm_arch in kvm_s2_mmu
      KVM: arm64: Set host stage 2 using kvm_nvhe_init_params
      KVM: arm64: Refactor kvm_arm_setup_stage2()
      KVM: arm64: Refactor __load_guest_stage2()
      KVM: arm64: Refactor __populate_fault_info()
      KVM: arm64: Make memcache anonymous in pgtable allocator
      KVM: arm64: Reserve memory for host stage 2
      KVM: arm64: Sort the hypervisor memblocks
      KVM: arm64: Always zero invalid PTEs
      KVM: arm64: Use page-table to track page ownership
      KVM: arm64: Refactor the *_map_set_prot_attr() helpers
      KVM: arm64: Add kvm_pgtable_stage2_find_range()
      KVM: arm64: Introduce KVM_PGTABLE_S2_NOFWB stage 2 flag
      KVM: arm64: Introduce KVM_PGTABLE_S2_IDMAP stage 2 flag
      KVM: arm64: Provide sanitized mmfr* registers at EL2
      KVM: arm64: Wrap the host with a stage 2
      KVM: arm64: Page-align the .hyp sections
      KVM: arm64: Disable PMU support in protected mode
      KVM: arm64: Protect the .hyp sections from the host

Shenming Lu (4):
      irqchip/gic-v3-its: Drop the setting of PTZ altogether
      KVM: arm64: GICv4.1: Add function to get VLPI state
      KVM: arm64: GICv4.1: Try to save VLPI state in save_pending_tables
      KVM: arm64: GICv4.1: Give a chance to save VLPI state

Suzuki K Poulose (17):
      KVM: arm64: Hide system instruction access to Trace registers
      KVM: arm64: Disable guest access to trace filter controls
      perf: aux: Add flags for the buffer format
      perf: aux: Add CoreSight PMU buffer formats
      arm64: Add support for trace synchronization barrier
      KVM: arm64: Handle access to TRFCR_EL1
      KVM: arm64: Move SPE availability check to VCPU load
      arm64: KVM: Enable access to TRBE support for host
      coresight: etm4x: Move ETM to prohibited region for disable
      coresight: etm-perf: Allow an event to use different sinks
      coresight: Do not scan for graph if none is present
      coresight: etm4x: Add support for PE OS lock
      coresight: ete: Add support for ETE sysreg access
      coresight: ete: Add support for ETE tracing
      dts: bindings: Document device tree bindings for ETE
      coresight: etm-perf: Handle stale output handles
      dts: bindings: Document device tree bindings for Arm TRBE

Thomas Gleixner (1):
      time: Add mechanism to recognize clocksource in time_get_snapshot

Wang Wensheng (1):
      KVM: arm64: Fix error return code in init_hyp_mode()

Wei Yongjun (2):
      coresight: core: Make symbol 'csdev_sink' static
      coresight: trbe: Fix return value check in arm_trbe_register_coresight_cpu()

Will Deacon (5):
      arm64: lib: Annotate {clear, copy}_page() as position-independent
      KVM: arm64: Link position-independent string routines into .hyp.text
      arm64: kvm: Add standalone ticket spinlock implementation for use at hyp
      arm/arm64: Probe for the presence of KVM hypervisor
      KVM: arm64: Advertise KVM UID to guests via SMCCC

Xiaofei Tan (1):
      arm64: sve: Provide sve_cond_update_zcr_vq fallback when !ARM64_SVE

Xu Jia (1):
      KVM: arm64: Make symbol '_kvm_host_prot_finalize' static

Zenghui Yu (2):
      KVM: arm64: GICv4.1: Restore VLPI pending state to physical side
      KVM: arm64: Fix Function ID typo for PTP_KVM service

 .../ABI/testing/sysfs-bus-coresight-devices-trbe   |   14 +
 Documentation/admin-guide/kernel-parameters.txt    |    3 +-
 Documentation/devicetree/bindings/arm/ete.yaml     |   75 ++
 Documentation/devicetree/bindings/arm/trbe.yaml    |   49 +
 Documentation/trace/coresight/coresight-trbe.rst   |   38 +
 Documentation/virt/kvm/api.rst                     |   25 +-
 Documentation/virt/kvm/arm/index.rst               |    1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst             |   25 +
 Documentation/virt/kvm/devices/arm-vgic-its.rst    |    2 +-
 Documentation/virt/kvm/devices/arm-vgic-v3.rst     |    2 +-
 MAINTAINERS                                        |    6 +-
 arch/arm/include/asm/hypervisor.h                  |    3 +
 arch/arm64/Kconfig                                 |   20 -
 arch/arm64/crypto/aes-modes.S                      |    2 +-
 arch/arm64/crypto/sha1-ce-core.S                   |    2 +-
 arch/arm64/crypto/sha2-ce-core.S                   |    2 +-
 arch/arm64/crypto/sha3-ce-core.S                   |    4 +-
 arch/arm64/crypto/sha512-ce-core.S                 |    2 +-
 arch/arm64/include/asm/assembler.h                 |  129 +--
 arch/arm64/include/asm/barrier.h                   |    1 +
 arch/arm64/include/asm/cpufeature.h                |   17 +
 arch/arm64/include/asm/el2_setup.h                 |   13 +
 arch/arm64/include/asm/fpsimd.h                    |   11 +
 arch/arm64/include/asm/fpsimdmacros.h              |   10 +-
 arch/arm64/include/asm/hyp_image.h                 |    7 +
 arch/arm64/include/asm/hypervisor.h                |    3 +
 arch/arm64/include/asm/kvm_arm.h                   |    3 +
 arch/arm64/include/asm/kvm_asm.h                   |    9 +
 arch/arm64/include/asm/kvm_host.h                  |   46 +-
 arch/arm64/include/asm/kvm_hyp.h                   |   14 +-
 arch/arm64/include/asm/kvm_mmu.h                   |   25 +-
 arch/arm64/include/asm/kvm_pgtable.h               |  164 ++-
 arch/arm64/include/asm/pgtable-prot.h              |    4 +-
 arch/arm64/include/asm/sections.h                  |    1 +
 arch/arm64/include/asm/sysreg.h                    |   59 +-
 arch/arm64/kernel/asm-offsets.c                    |    5 +
 arch/arm64/kernel/cpu-reset.S                      |    5 +-
 arch/arm64/kernel/cpufeature.c                     |   11 +-
 arch/arm64/kernel/fpsimd.c                         |    4 +-
 arch/arm64/kernel/head.S                           |   39 +-
 arch/arm64/kernel/hyp-stub.S                       |   13 +-
 arch/arm64/kernel/idreg-override.c                 |   26 +-
 arch/arm64/kernel/image-vars.h                     |   34 +-
 arch/arm64/kernel/vmlinux.lds.S                    |   74 +-
 arch/arm64/kvm/arm.c                               |  216 +++-
 arch/arm64/kvm/debug.c                             |  116 +-
 arch/arm64/kvm/fpsimd.c                            |   26 +-
 arch/arm64/kvm/guest.c                             |    6 +-
 arch/arm64/kvm/handle_exit.c                       |   45 +
 arch/arm64/kvm/hyp/Makefile                        |    2 +-
 arch/arm64/kvm/hyp/fpsimd.S                        |   10 +
 arch/arm64/kvm/hyp/include/hyp/switch.h            |  107 +-
 arch/arm64/kvm/hyp/include/nvhe/early_alloc.h      |   14 +
 arch/arm64/kvm/hyp/include/nvhe/gfp.h              |   68 ++
 arch/arm64/kvm/hyp/include/nvhe/mem_protect.h      |   36 +
 arch/arm64/kvm/hyp/include/nvhe/memory.h           |   51 +
 arch/arm64/kvm/hyp/include/nvhe/mm.h               |   96 ++
 arch/arm64/kvm/hyp/include/nvhe/spinlock.h         |   92 ++
 arch/arm64/kvm/hyp/nvhe/Makefile                   |    9 +-
 arch/arm64/kvm/hyp/nvhe/cache.S                    |   13 +
 arch/arm64/kvm/hyp/nvhe/debug-sr.c                 |   56 +-
 arch/arm64/kvm/hyp/nvhe/early_alloc.c              |   54 +
 arch/arm64/kvm/hyp/nvhe/gen-hyprel.c               |   18 +
 arch/arm64/kvm/hyp/nvhe/host.S                     |   18 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S                 |   54 +-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 |   75 +-
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |    6 +-
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S                  |    1 +
 arch/arm64/kvm/hyp/nvhe/mem_protect.c              |  279 +++++
 arch/arm64/kvm/hyp/nvhe/mm.c                       |  173 +++
 arch/arm64/kvm/hyp/nvhe/page_alloc.c               |  195 ++++
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               |    4 +-
 arch/arm64/kvm/hyp/nvhe/setup.c                    |  214 ++++
 arch/arm64/kvm/hyp/nvhe/stub.c                     |   22 +
 arch/arm64/kvm/hyp/nvhe/switch.c                   |   26 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c                      |    4 +-
 arch/arm64/kvm/hyp/pgtable.c                       |  410 +++++--
 arch/arm64/kvm/hyp/reserved_mem.c                  |  113 ++
 arch/arm64/kvm/hyp/vhe/switch.c                    |    4 +-
 arch/arm64/kvm/hypercalls.c                        |   80 +-
 arch/arm64/kvm/mmu.c                               |  136 ++-
 arch/arm64/kvm/perf.c                              |    7 +-
 arch/arm64/kvm/pmu-emul.c                          |    2 +-
 arch/arm64/kvm/pmu.c                               |    8 +-
 arch/arm64/kvm/reset.c                             |   51 +-
 arch/arm64/kvm/sys_regs.c                          |   16 +
 arch/arm64/kvm/va_layout.c                         |    7 +
 arch/arm64/kvm/vgic/vgic-init.c                    |   12 +-
 arch/arm64/kvm/vgic/vgic-its.c                     |    6 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c              |    7 +-
 arch/arm64/kvm/vgic/vgic-mmio-v3.c                 |   81 +-
 arch/arm64/kvm/vgic/vgic-mmio.c                    |   10 +-
 arch/arm64/kvm/vgic/vgic-v3.c                      |   66 +-
 arch/arm64/kvm/vgic/vgic-v4.c                      |   38 +
 arch/arm64/kvm/vgic/vgic.h                         |    2 +
 arch/arm64/lib/clear_page.S                        |    4 +-
 arch/arm64/lib/copy_page.S                         |    4 +-
 arch/arm64/mm/init.c                               |    3 +
 arch/s390/kernel/perf_event.c                      |   21 -
 arch/sh/kernel/perf_event.c                        |   18 -
 drivers/clocksource/arm_arch_timer.c               |   36 +
 drivers/firmware/psci/psci.c                       |    2 +
 drivers/firmware/smccc/Makefile                    |    2 +-
 drivers/firmware/smccc/kvm_guest.c                 |   50 +
 drivers/firmware/smccc/smccc.c                     |    1 +
 drivers/hwtracing/coresight/Kconfig                |   24 +-
 drivers/hwtracing/coresight/Makefile               |    1 +
 drivers/hwtracing/coresight/coresight-core.c       |   29 +-
 drivers/hwtracing/coresight/coresight-etm-perf.c   |  119 +-
 drivers/hwtracing/coresight/coresight-etm4x-core.c |  161 ++-
 .../hwtracing/coresight/coresight-etm4x-sysfs.c    |   19 +-
 drivers/hwtracing/coresight/coresight-etm4x.h      |   83 +-
 drivers/hwtracing/coresight/coresight-platform.c   |    6 +
 drivers/hwtracing/coresight/coresight-priv.h       |    3 +
 drivers/hwtracing/coresight/coresight-trbe.c       | 1157 ++++++++++++++++++++
 drivers/hwtracing/coresight/coresight-trbe.h       |  152 +++
 drivers/irqchip/irq-gic-v3-its.c                   |   18 +-
 drivers/perf/arm_pmu.c                             |   30 -
 drivers/ptp/Kconfig                                |    2 +-
 drivers/ptp/Makefile                               |    2 +
 drivers/ptp/ptp_kvm_arm.c                          |   28 +
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c}        |   85 +-
 drivers/ptp/ptp_kvm_x86.c                          |   97 ++
 include/kvm/arm_pmu.h                              |    4 +
 include/kvm/arm_vgic.h                             |    1 +
 include/linux/arm-smccc.h                          |   41 +
 include/linux/bug.h                                |   10 +
 include/linux/clocksource.h                        |    6 +
 include/linux/clocksource_ids.h                    |   12 +
 include/linux/coresight.h                          |   13 +
 include/linux/perf_event.h                         |    2 -
 include/linux/ptp_kvm.h                            |   19 +
 include/linux/timekeeping.h                        |   12 +-
 include/uapi/linux/kvm.h                           |    1 +
 include/uapi/linux/perf_event.h                    |   13 +-
 kernel/events/core.c                               |    5 -
 kernel/time/clocksource.c                          |    2 +
 kernel/time/timekeeping.c                          |    1 +
 lib/bug.c                                          |   54 +-
 tools/testing/selftests/kvm/.gitignore             |    1 +
 tools/testing/selftests/kvm/Makefile               |    1 +
 tools/testing/selftests/kvm/aarch64/vgic_init.c    |  551 ++++++++++
 tools/testing/selftests/kvm/include/kvm_util.h     |    9 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   75 ++
 144 files changed, 6298 insertions(+), 856 deletions(-)
 create mode 100644 Documentation/ABI/testing/sysfs-bus-coresight-devices-trbe
 create mode 100644 Documentation/devicetree/bindings/arm/ete.yaml
 create mode 100644 Documentation/devicetree/bindings/arm/trbe.yaml
 create mode 100644 Documentation/trace/coresight/coresight-trbe.rst
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/early_alloc.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/gfp.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/mem_protect.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/memory.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/mm.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/spinlock.h
 create mode 100644 arch/arm64/kvm/hyp/nvhe/cache.S
 create mode 100644 arch/arm64/kvm/hyp/nvhe/early_alloc.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/mem_protect.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/mm.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/page_alloc.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/setup.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/stub.c
 create mode 100644 arch/arm64/kvm/hyp/reserved_mem.c
 create mode 100644 drivers/firmware/smccc/kvm_guest.c
 create mode 100644 drivers/hwtracing/coresight/coresight-trbe.c
 create mode 100644 drivers/hwtracing/coresight/coresight-trbe.h
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
 create mode 100644 include/linux/ptp_kvm.h
 create mode 100644 tools/testing/selftests/kvm/aarch64/vgic_init.c
```
#### [PATCH] KVM: hyper-v: Add new exit reason HYPERV_OVERLAY
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12219963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 989D4C433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 09:06:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 58859611BE
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 09:06:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241059AbhDWJGq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 05:06:46 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:18163 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229456AbhDWJGq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 05:06:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1619168771; x=1650704771;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=SiScQ0H7s9eUAFp0xeJC3NL931O8+l8uIOp8XRXepRo=;
  b=dfJNz87vkmsVK2TzSdO6OWgMR3OySfQ6YWSCmFM3j5b8oeIAB3+qGMIt
   7apu0EViaw9ytWqewWcKbNDiY9itZEfN4zNKOol3UxXI3FfLo0MZOprQN
   OgY9W5egBXC+icx5CF+szUqgMThheul6P2zs2fcy9TpksarNOZ6qVk3by
   Q=;
X-IronPort-AV: E=Sophos;i="5.82,245,1613433600";
   d="scan'208";a="103552215"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1a-67b371d8.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-4101.iad4.amazon.com with ESMTP;
 23 Apr 2021 09:04:03 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan3.iad.amazon.com [10.40.163.38])
        by email-inbound-relay-1a-67b371d8.us-east-1.amazon.com (Postfix) with
 ESMTPS id 96519A1760;
        Fri, 23 Apr 2021 09:03:58 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.160.209) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Fri, 23 Apr 2021 09:03:51 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>
CC: Alexander Graf <graf@amazon.com>,
        Evgeny Iakovlev <eyakovl@amazon.de>,
        Liran Alon <liran@amazon.com>,
        Ioannis Aslanidis <iaslan@amazon.de>,
        Siddharth Chandrasekaran <sidcha@amazon.de>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: hyper-v: Add new exit reason HYPERV_OVERLAY
Date: Fri, 23 Apr 2021 11:03:33 +0200
Message-ID: <20210423090333.21910-1-sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.160.209]
X-ClientProxiedBy: EX13D17UWB002.ant.amazon.com (10.43.161.141) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hypercall code page is specified in the Hyper-V TLFS to be an overlay
page, ie., guest chooses a GPA and the host _places_ a page at that
location, making it visible to the guest and the existing page becomes
inaccessible. Similarly when disabled, the host should _remove_ the
overlay and the old page should become visible to the guest.

Currently KVM directly patches the hypercall code into the guest chosen
GPA. Since the guest seldom moves the hypercall code page around, it
doesn't see any problems even though we are corrupting the exiting data
in that GPA.

VSM API introduces more complex overlay workflows during VTL switches
where the guest starts to expect that the existing page is intact. This
means we need a more generic approach to handling overlay pages: add a
new exit reason KVM_EXIT_HYPERV_OVERLAY that exits to userspace with the
expectation that a page gets overlaid there.

In the interest of maintaing userspace exposed behaviour, add a new KVM
capability to allow the VMMs to enable this if they can handle the
hypercall page in userspace.

Signed-off-by: Siddharth Chandrasekaran <sidcha@amazon.de>

CR: https://code.amazon.com/reviews/CR-49011379
---
 arch/x86/include/asm/kvm_host.h |  4 ++++
 arch/x86/kvm/hyperv.c           | 25 ++++++++++++++++++++++---
 arch/x86/kvm/x86.c              |  5 +++++
 include/uapi/linux/kvm.h        | 10 ++++++++++
 4 files changed, 41 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] KVM: selftests: Add exception handling support for aarch64
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12219531
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52D8EC433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 04:04:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28B5161425
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 04:04:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231542AbhDWEEk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 00:04:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46074 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229717AbhDWEEj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 00:04:39 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 40462C061574
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 21:04:02 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 s34-20020a252d620000b02904e34d3a48abso22632819ybe.13
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 21:04:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=YiVwtBVL/pOUXDA1kClnzHrI3XyPs8Rvvwwd0LrXoL4=;
        b=AkvMQr2HAbsRNL2vcxQ6E6RhfJu1qrPwlp1Q9SPuVbUfiTxzVIX06FZhzYs2Pgqu5V
         YE2zv+wuUCxKbWLsFgmnIMmnZz04ZXTTXYF8/x41miMA8kcSlio3KSYik7FbfITE0y2A
         KrcIofSeRqOMdwZTkJW6z0znihMokgEf7V17Plrp8fJRAPuS4lKt21VxcnbgMEsulhsv
         s2pBPNNgTS+0UphTDjJtF8U5mdP+AF72iM0PUmkKyLc3ksyCj/bkVw9JYzj+xqggU1lD
         yDFsEya/21cZJdgUC3LG2MheUkmlQbbkCCNLTM/8xmoIuYODjc2uIzHIpd7GQ9/DpxfD
         wumQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=YiVwtBVL/pOUXDA1kClnzHrI3XyPs8Rvvwwd0LrXoL4=;
        b=CGjTxZJYWwyeGaCNh9v0T2kVYFH1GqcWOEA5v+MVyl5eemU/vRlW1WlRkSpR53ZIWp
         5jGfVZBaC23XOugxSP2xC5bF0jlFjVXd4oXnly1mhECpmEtFa4+5TO1qPkkcIyK9UpbI
         4gwYoM0LTuVee6YjdttzMuPY8QQLUE+SSvbk7c2FIsOdrPlkGbr6oDxVC4yI2+us3o5s
         KKDWpRXsXqv1l/ttuTo4nFe5QyL3Yc9XHfq4kw4sZ3tVp3UKPkawnhLGxq80NfLsB6T5
         TKD54SUBMyP7lu0Ic0dsqf8Ug8W1KoTyu9A9n+KsAOkgalWikZjBnhj9ONnXKFQtOyBA
         Z5gQ==
X-Gm-Message-State: AOAM532dcuvF459G9eW+rf2vettDnBHIOnm3fgOvksiQ6bvLav4QxKij
        hovTlfoJMDOkSFZMryYKYJ2Z2QgKVjR4ddYcAfcQhfE4gErOR6+dM4tR7FXzp4k08x/LIISdyeH
        EEUYal/sB7telXxXW7zfidXUeZpx2BzFzL8rqhdH8slTw1VVG5ZE+l4dFzaodKsI=
X-Google-Smtp-Source: 
 ABdhPJyFCWJFP9wUa3EEhaotFzFlHuSo2vPOiQWFas8rbajb6F+czhSpzglPQ3wUJRlNwXJKTz71oqDQPLlbQQ==
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a25:9085:: with SMTP id
 t5mr1887813ybl.26.1619150641488; Thu, 22 Apr 2021 21:04:01 -0700 (PDT)
Date: Thu, 22 Apr 2021 21:03:49 -0700
In-Reply-To: <20210423040351.1132218-1-ricarkol@google.com>
Message-Id: <20210423040351.1132218-2-ricarkol@google.com>
Mime-Version: 1.0
References: <20210423040351.1132218-1-ricarkol@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 1/3] KVM: selftests: Add exception handling support for
 aarch64
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, maz@kernel.org, drjones@redhat.com,
        alexandru.elisei@arm.com, eric.auger@redhat.com,
        Ricardo Koller <ricarkol@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the infrastructure needed to enable exception handling in aarch64
selftests. The exception handling defaults to an unhandled-exception
handler which aborts the test, just like x86. These handlers can be
overridden by calling vm_handle_exception with a (vector, error-code)
tuple. The unhandled exception reporting from the guest is done using
the new ucall UCALL_UNHANDLED.

Signed-off-by: Ricardo Koller <ricarkol@google.com>
---
 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/include/aarch64/processor.h |  69 ++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 .../selftests/kvm/lib/aarch64/handlers.S      | 104 ++++++++++++++++++
 .../selftests/kvm/lib/aarch64/processor.c     |  56 ++++++++++
 5 files changed, 231 insertions(+), 1 deletion(-)
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/handlers.S

```
#### [PATCH v3 1/4] KVM: stats: Separate common stats from architecture specific ones
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12221285
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 94E65C433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 18:17:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC84D6144E
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 18:17:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S243691AbhDWSSN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 14:18:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36624 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243663AbhDWSSJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 14:18:09 -0400
Received: from mail-pg1-x54a.google.com (mail-pg1-x54a.google.com
 [IPv6:2607:f8b0:4864:20::54a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D17EBC061342
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 11:17:32 -0700 (PDT)
Received: by mail-pg1-x54a.google.com with SMTP id
 l25-20020a6357190000b02901f6df0d646eso14808698pgb.23
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 11:17:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=z7nOqoBuBd/HJQelkrkLUY/pK3p8iDNYYejTmmONi40=;
        b=MkWD70OMLzAIWeg6dKWmlaXMgdo/ZMN2Vc+YyzFWyLN67LPTjqrYgO7zaytyndabNQ
         lCzzTmOO5OCckiObqnwVRTRR8HIfw1ko6sZV+0G4U8y1PFzj/qDL6KTSsAdpQwvG29CL
         P1OkoBLeRxWvQYCHCZBFTQ2gaUgIWZHn9fO7O9HKk16IbiYDseW5DCrGjN8jcIhhDXEr
         q1jkAnMBvMkNvjLPjbPjuttgYLGbOwMhfpOjsQnh0JeBtnXrsJnOoXtH0J2FS3oTTtGO
         zzjzTYCxmY0JyXgj3M+Q4PNZZwQuzKVeycnYIYLFrMi3RvHQrE2ksxdwRr7ulaXlEQtZ
         /+AA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=z7nOqoBuBd/HJQelkrkLUY/pK3p8iDNYYejTmmONi40=;
        b=D73lBEPN3OkBxodQi6aDI7BiZcuwsEFwp6gSNfikTNyIuOPd8M06KGNfdRBFKIPcxc
         Xg9vL2hNLGy3kUJzir/fVMNYxnP1vTWjjomrcqpxoH68GwCA3J8Q0KVjWhZsZeqY1q58
         i5r0LeFFJaEUXHGRr3Y5zyU/d5RXFLfB/U3yVqcNzbp+M1W/RL+HdKfB93oy7QcNJ5ZK
         n4pLfIrDjiskCOEw6sDzbyLEVk+/oFZGRVWoqLG59yHK0a9VG5zN/GSBSWSo7tEFd6pu
         pjj5c2cEBUIvpdRB3TT9WsEr31L+q3MeqMMBM+GhfAlDUUEco6b5/xdOBXrrn2VWJlCH
         2HSw==
X-Gm-Message-State: AOAM532aKyQ32pfdfGzs3Ep//X3Qi8HiS/XmkxkZCwpOIP5CGw313iwq
        k6X+NLX4JsQTwsDBE6NCRgqE40/WLUX4U5A1RlIPJclV/yzax9OmwT3jQxzHsuIMEbshfGsPDxH
        BL72R0p227wYlQVXf9qpnKYxYMM17122rv08L0CZ26dD9NS/XO+hRbkzzRnNCF17yte2DMr8=
X-Google-Smtp-Source: 
 ABdhPJw/wREr0Xz19k+5QVbbx6n5dcpwP/U3Urh2CtsGpp/vpZrjKMkgEkZNApgrPAwmBBkwb087bgOb7xrRSphp6A==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a17:902:7795:b029:ec:b1ca:de75 with
 SMTP id o21-20020a1709027795b02900ecb1cade75mr5279074pll.70.1619201852048;
 Fri, 23 Apr 2021 11:17:32 -0700 (PDT)
Date: Fri, 23 Apr 2021 18:17:24 +0000
In-Reply-To: <20210423181727.596466-1-jingzhangos@google.com>
Message-Id: <20210423181727.596466-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210423181727.596466-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v3 1/4] KVM: stats: Separate common stats from architecture
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
#### [PATCH kvm-unit-tests] nSVM: Test addresses of MSR and IO permissions maps
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12219729
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C8E9C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 06:53:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1B97611ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 06:53:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240699AbhDWGyQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 02:54:16 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:32008 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236806AbhDWGyP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Apr 2021 02:54:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619160819;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/2UnVx5VtX3OfRIVJ/IURmI0gb2kX8kbuxn/wS3RET8=;
        b=FlAjuRBv+DvHcpANQDxvvzL4yMS6oKWLM0DGZksz7OX/E6qgBwtT1WGsF3FnUr6Q+5K4DX
        EJMX/+iaK82L6sYYvGc+aeWkOPoqGt81Pl+Iuxl27qpZzhwzZMiMTMwV3sgPUtB1VG7fTd
        fG1GatrhLyr9evNmARLR0IHaU2BlYD0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-591-eJUaEOAHNMagwUnNp9SOEw-1; Fri, 23 Apr 2021 02:53:36 -0400
X-MC-Unique: eJUaEOAHNMagwUnNp9SOEw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9967E107ACE8;
        Fri, 23 Apr 2021 06:53:35 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 55CF8369A;
        Fri, 23 Apr 2021 06:53:35 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH kvm-unit-tests] nSVM: Test addresses of MSR and IO permissions
 maps
Date: Fri, 23 Apr 2021 02:53:34 -0400
Message-Id: <20210423065334.1701680-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

According to section "Canonicalization and Consistency Checks" in APM vol 2,
the following guest state is illegal:

    "The MSR or IOIO intercept tables extend to a physical address that
     is greater than or equal to the maximum supported physical address.
     The VMRUN instruction ignores the lower 12 bits of the address
     specified in the VMCB."

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Message-Id: <20210412215611.110095-8-krish.sadhukhan@oracle.com>
[Fix the test so that it passes when VMRUN does ignore the lower 12
 bits of the address. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm_tests.c | 79 ++++++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 78 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] x86/cstart: Don't use MSR_GS_BASE in 32-bit boot code
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12219731
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 726EDC433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 06:53:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BDAC613F5
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 06:53:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240744AbhDWGyY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 02:54:24 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37828 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240743AbhDWGyX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 23 Apr 2021 02:54:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619160827;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=YXcaDNtwz3ucxJL+QAv1pl2x/JuMrGE4EhM2LwyjCSc=;
        b=SY9NwrA48EXHZNsC03qXWCEQsBeQKHQgCUphSVcK4tvbVR49I4Uj42QqtQi+poGO1BiHHg
        gkNSKjae9qiSw0piu6GnSeDQZ4qoIsn++VXtbjg/8u8kN3CynBr2YEMsG17DIDTd2fgF/C
        Gf9b8Oj5jAtfenfCvfkh+DMxP+9XlGg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-21-D7xAQQpiPn2L_dZvxmilZw-1; Fri, 23 Apr 2021 02:53:44 -0400
X-MC-Unique: D7xAQQpiPn2L_dZvxmilZw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 56E86343A2;
        Fri, 23 Apr 2021 06:53:43 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0DEED10016FE;
        Fri, 23 Apr 2021 06:53:42 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <seanjc@google.com>
Subject: [PATCH kvm-unit-tests] x86/cstart: Don't use MSR_GS_BASE in 32-bit
 boot code
Date: Fri, 23 Apr 2021 02:53:42 -0400
Message-Id: <20210423065342.1701726-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add per-cpu selectors to the GDT, and set GS_BASE by
loading a "real" segment.  Using MSR_GS_BASE is wrong and broken,
it's a 64-bit only MSR and does not exist on 32-bit CPUs.  The current
code works only because 32-bit KVM VMX incorrectly disables interception
of MSR_GS_BASE, and no one runs KVM on an actual 32-bit physical CPU,
i.e. the MSR exists in hardware and so everything "works".

32-bit KVM SVM is not buggy and correctly injects #GP on the WRMSR, i.e.
the tests have never worked on 32-bit SVM.

While at it, tweak the TSS setup to look like the percpu setup; both
are setting up the address field of the descriptor.

Fixes: dfe6cb6 ("Add 32 bit smp initialization code")
Reported-by: Sean Christopherson <seanjc@google.com>
Message-Id: <20210422030504.3488253-2-seanjc@google.com>
[Patch rewritten, keeping Sean's commit message. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/desc.c |  3 ++-
 lib/x86/desc.h |  5 +++--
 x86/cstart.S   | 35 ++++++++++++++++++++++-------------
 3 files changed, 27 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: VMX: Invert the inlining of MSR interception helpersFrom: Sean Christopherson <seanjc@google.com>
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12221845
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1F821C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:25:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F10876146B
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:25:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232624AbhDWWTx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 18:19:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:32982 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231881AbhDWWTx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 18:19:53 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4AFEAC06174A
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:19:16 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 7-20020a5b01070000b02904ed6442e5f6so2722175ybx.23
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:19:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=ZeMCYbj1aYDCT611v/iAK4CU8ivRbdiEyLm96+1Ix7Y=;
        b=Pt7uCfyTVNCA6uCGkxBae7hS3KK28MR5DU5pV8ZnuvpsWobv3JBSznmaRbPFnLNN/Q
         kyBauWTh5Xh3/0ZkaC6GOjMxbPzrUE4JvpP/9zvhYHmdWokTzlvueNplDesUnRiKy/jX
         NN7yPceYTYp+fYhMcUkQZ7MAGZ3s4fvXkShN10CSJw0zWvEt3/anC8TEDrVBpVsi6KcA
         ugZ3QjcNg7Z5+MdKOzzPgrrS5yDr0SlP5RZkfVENDiILKX4IBKtHeR7lhmTcVLHhJBYK
         YWpeLLjVF0MZFj8VYFzAyPiWfu09VoT6VCz13wVSjhOsGKFy1pDkUtxvDdySdYTBvkAY
         n4gA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=ZeMCYbj1aYDCT611v/iAK4CU8ivRbdiEyLm96+1Ix7Y=;
        b=EI7m+99N+BRBrA4OwlPQ8VBXd0Aj/+JarDrtVh9zPL+V6rrPmsmrwpPrFzM6uEHvbw
         FyLFA+kY7OgJk5NP1GCar91WWBHqkZ249AD6dCe6gN3b7MLpzE/aYK4b4jl01MV/3p7B
         CSe8LZ+r59GSHgIs/i12vtw1rQ96rqnthAnMkj+NqqfDogRGO4FyOnnMNWIc99r8OaO4
         ShjKl8iBxSbW5ldVwVsYIzjwV/sLDTz8nPpuq+N0gzOt4W92bE+ow55tzUVn7/Pmt2aP
         L975LDsSgfgw51Fn9k4UIRajvoH6sy7imAakkKc67s4NAbPI5RX1mB53ARXXoFK6fNIU
         JNZQ==
X-Gm-Message-State: AOAM5309kN94z5zczM7U+DFw7EkPJzajBMkplyQWcLCHqgHcU1nidEVx
        HkkSC4b3AE79gMjSpsZrMtcm5eVa2Ek=
X-Google-Smtp-Source: 
 ABdhPJzg0VE4zv3xkrjxBhvKB/coMS12ngomMzmKvcqVHJBKUcZUJ1+Wd24Az2sIhxMZFu4d217A5rp39pY=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:ad52:3246:e190:f070])
 (user=seanjc job=sendgmr) by 2002:a25:840c:: with SMTP id
 u12mr8338990ybk.345.1619216355427;
 Fri, 23 Apr 2021 15:19:15 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 23 Apr 2021 15:19:12 -0700
Message-Id: <20210423221912.3857243-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH] KVM: VMX: Invert the inlining of MSR interception helpers
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

Invert the inline declarations of the MSR interception helpers between
the wrapper, vmx_set_intercept_for_msr(), and the core implementations,
vmx_{dis,en}able_intercept_for_msr().  Letting the compiler _not_
inline the implementation reduces KVM's code footprint by ~3k bytes.

Back when the helpers were added in commit 904e14fb7cb9 ("KVM: VMX: make
MSR bitmaps per-VCPU"), both the wrapper and the implementations were
__always_inline because the end code distilled down to a few conditionals
and a bit operation.  Today, the implementations involve a variety of
checks and bit ops in order to support userspace MSR filtering.

Furthermore, the vast majority of calls to manipulate MSR interception
are not performance sensitive, e.g. vCPU creation and x2APIC toggling.
On the other hand, the one path that is performance sensitive, dynamic
LBR passthrough, uses the wrappers, i.e. is largely untouched by
inverting the inlining.

In short, forcing the low level MSR interception code to be inlined no
longer makes sense.

No functional change intended.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 17 ++---------------
 arch/x86/kvm/vmx/vmx.h | 15 +++++++++++++--
 2 files changed, 15 insertions(+), 17 deletions(-)

```
#### [PATCH] KVM: VMX: use EPT_VIOLATION_GVA_TRANSLATED instead of 0x100
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12219319
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B3C9C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:24:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE98D613DE
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:24:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239918AbhDWAZM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 20:25:12 -0400
Received: from mga02.intel.com ([134.134.136.20]:7405 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235569AbhDWAZL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 20:25:11 -0400
IronPort-SDR: 
 2A4duPhjG5MLKH5i8Xrp90Y7zsglru3FHlfQ5NMuXd5ZYO3KkKKfS7ZJMLUconstkOlwqnKPM4
 J2DBfX1Wlwaw==
X-IronPort-AV: E=McAfee;i="6200,9189,9962"; a="183125090"
X-IronPort-AV: E=Sophos;i="5.82,244,1613462400";
   d="scan'208";a="183125090"
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2021 17:24:35 -0700
IronPort-SDR: 
 fJZ8e6UdDzJpDNR+R6q2UUyN8U/dVGRTqPLIRlZjT0mt4WURHD3qu/VfZhG2+qVKsK3qeyGBAs
 GYwYyu+ieVLA==
X-IronPort-AV: E=Sophos;i="5.82,244,1613462400";
   d="scan'208";a="421573241"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by fmsmga008-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2021 17:24:35 -0700
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Cc: isaku.yamahata@gmail.com,
        Isaku Yamahata <isaku.yamahata@intel.com>,
        Yao Yuan <yuan.yao@intel.com>
Subject: [PATCH] KVM: VMX: use EPT_VIOLATION_GVA_TRANSLATED instead of 0x100
Date: Thu, 22 Apr 2021 17:22:29 -0700
Message-Id: 
 <724e8271ea301aece3eb2afe286a9e2e92a70b18.1619136576.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use symbolic value, EPT_VIOLATION_GVA_TRANSLATED, instead of 0x100
in handle_ept_violation().

Signed-off-by: Yao Yuan <yuan.yao@intel.com>
Signed-off-by: Isaku Yamahata <isaku.yamahata@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: nVMX: Drop obsolete (and pointless) pdptrs_changed() check
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12219265
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0ADA9C43460
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:06:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D8FDD61155
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 00:06:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239930AbhDWAHU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 22 Apr 2021 20:07:20 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50868 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235691AbhDWAHS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Apr 2021 20:07:18 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 665B0C061574
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 17:06:43 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id
 s8-20020a5b04480000b029049fb35700b9so22197446ybp.5
        for <kvm@vger.kernel.org>; Thu, 22 Apr 2021 17:06:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=lASHK+mshsNE6LJP7Zp6NlK5R8UQDK0WUI+mht9WyPE=;
        b=nR8t0PkGYw/2A/kvZCxu8TfVsllhGN5jOk7SvtzvsvBN+Tx3hsA3m7H2B/lA9cyoKy
         GMPQqsT8Ufna//5YSSNqhXz7CMeDFiBY6DMf3Mzn6p2FqJLDDEJJ1VbCqnHmj4r95II3
         kFxNHKjI68ahJRvg2xZLwaC3dyAMIqG3aiDKkZLNjbEw1rZzjqpIfnCVM/g2URB4/Gu8
         rUFeGo+YNLUy6UChPG6ksDUtNmFBvbtISKq75LvNpIQQax5aHt0S22AwuUvdVc2xjek+
         n+zW3wej9JKPjp4cQ0mD+CJyYmCeTtlV8S3/lT0Vsl8ZWCawIQl55kAx7/MtuXxOPiKt
         l6sg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=lASHK+mshsNE6LJP7Zp6NlK5R8UQDK0WUI+mht9WyPE=;
        b=SWyISeMrhLjNd1NNWyox4pkaOyNKuf9s8edtb5dLBX1GGiui9E+Ulu7y0T1YHg0vot
         HEbZqGN87+ya3j0wnjoEG5I4yTYNfrmBGvfQe8TlbCa4ik/+EwbMPmzi69NkGnvhaj/Y
         bnOFKULEI6X2sZUtJmi2FB7GB1zvPocQbPBYfLm2p9BHsNRMahjUAHMNLzaDofX4WC4p
         ttxSsg4TIjSF26zkWsov9S70e9rLcAxpOMgbSWYieH5TkvyXgWB9O05HFMtBUdqCnpVF
         1rSK/55Ti1Eadjg16x82yY8DEQwq5ukPXZ5T6tAuPP3iK2VoIVbNSN/D1SobTFONq3qH
         73qQ==
X-Gm-Message-State: AOAM530SetAx/QtIab8rOUYSrVD0rd3H2QrnkAFbdk675eyJgBEWKjxA
        kGR/FQ0zGvebxFFwKQUG5y9olKSg2lU=
X-Google-Smtp-Source: 
 ABdhPJy7d9MnSiTtuKa3JHkCqRIujr96wSnEQOCKmysEuCLbTdPmBdl16HXOQgwFsTodV7qVQbg9XHlS9gA=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e012:374c:592:6194])
 (user=seanjc job=sendgmr) by 2002:a5b:611:: with SMTP id
 d17mr1784818ybq.421.1619136402687;
 Thu, 22 Apr 2021 17:06:42 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 22 Apr 2021 17:06:34 -0700
In-Reply-To: <20210423000637.3692951-1-seanjc@google.com>
Message-Id: <20210423000637.3692951-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210423000637.3692951-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH 1/4] KVM: nVMX: Drop obsolete (and pointless) pdptrs_changed()
 check
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

Remove the pdptrs_changed() check when loading L2's CR3.  The set of
available registers is always reset when switching VMCSes (see commit
e5d03de5937e, "KVM: nVMX: Reset register cache (available and dirty
masks) on VMCS switch"), thus the "are PDPTRs available" check will
always fail.  And even if it didn't fail, reading guest memory to check
the PDPTRs is just as expensive as reading guest memory to load 'em.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/vmx/nested.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH v3 1/4] KVM: SVM: Inject #GP on guest MSR_TSC_AUX accesses if RDTSCP unsupported
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12221939
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6CEC5C433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:34:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E09861131
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 22:34:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244139AbhDWWfK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 18:35:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36212 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237189AbhDWWe4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 18:34:56 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EB8E1C06175F
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:34:13 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 u3-20020a2509430000b02904e7f1a30cffso25965937ybm.8
        for <kvm@vger.kernel.org>; Fri, 23 Apr 2021 15:34:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=v1Exyl3dWucGDOE9RB7t5VjbkFrC7Sen6ZzJflRKQCo=;
        b=NQNFaYhStGsu5IDFNW+4tcsMQ9oxw8ww6l7ZuV2jrrMlLeeHY2ZIyFdMLsJw6hAC2u
         3yHVM0nOt3isla3mrMpwZXmJQQolCZoqR+LMQJHLvPdMmQTsuOtqs6RTixNzHxfgYZ7g
         J5fcyQSyr36Vowf6b4MgeWCiJX98Dyj46GNHwK5t1rBmZK8ne7D/yCYnnqqCf/O1ilyl
         NYBobajDtpV34S8VSQixBahj0gAiPDNA0SaU5w+8pueSORa1PkFUHEZJ7pUIkozP1GTz
         bfuCsTQNavwgf/eroUbAiJi2v4Sele/SZD5grKLwIoymYE51sbISIFt+ef+0HDNBuKbN
         m94g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=v1Exyl3dWucGDOE9RB7t5VjbkFrC7Sen6ZzJflRKQCo=;
        b=U8UsOFp9ZF+nWbjqJ2Tj4+8nIiFVOd54XnuL2CsRYifXbKaFl7Q8o7J8XQ0AYWz3GL
         N5MvYuGhgiEk/R+2VSKbR0wa9j6bzsRfWGXIXxirw5q1jmIbSKWPCTlV1MOZXyxiIfv5
         11whIDbCrolLfZ20iJF0fcNgJXtkw+T1hR5xxDWv6e5vgJD07PH4O8d1/gvlzOWYlH6E
         b76uxwBH1x6xcRggDfXC8X1Wutpop572jEhnKjUkWJO6nDcEMY3KXfGZqBA3iA8PcnP/
         /om+qQ0xAECmaX8Q3LRLu7KaIEzdBCJbr4XE5/krcJ9Spz8Shp1kGM342aCCdtjEZStP
         KcbQ==
X-Gm-Message-State: AOAM530NkfzgjPI7f+jStyrLk2ujjNeBAoup/S13S+4XUHAEBacmFbl1
        JeYpvrozcng0M6h86uI/t6Oer8Xgcxc=
X-Google-Smtp-Source: 
 ABdhPJySKzlNI+fLnsfzovBIYlbDkcXXjqw5Nnkem92Rqin8d+lBerGODSH1OHydVWtZfpwc/mg4TuhuPns=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:ad52:3246:e190:f070])
 (user=seanjc job=sendgmr) by 2002:a25:3c1:: with SMTP id
 184mr641459ybd.76.1619217253258;
 Fri, 23 Apr 2021 15:34:13 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri, 23 Apr 2021 15:34:01 -0700
In-Reply-To: <20210423223404.3860547-1-seanjc@google.com>
Message-Id: <20210423223404.3860547-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210423223404.3860547-1-seanjc@google.com>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
Subject: [PATCH v3 1/4] KVM: SVM: Inject #GP on guest MSR_TSC_AUX accesses if
 RDTSCP unsupported
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reiji Watanabe <reijiw@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Inject #GP on guest accesses to MSR_TSC_AUX if RDTSCP is unsupported in
the guest's CPUID model.

Fixes: 46896c73c1a4 ("KVM: svm: add support for RDTSCP")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH] KVM: x86/xen: Take srcu lock when accessing kvm_memslots()
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12219741
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 25104C43461
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 07:11:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EAF08613F6
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 07:11:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241033AbhDWHMO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 03:12:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58688 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240743AbhDWHMO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 03:12:14 -0400
Received: from mail-pj1-x102a.google.com (mail-pj1-x102a.google.com
 [IPv6:2607:f8b0:4864:20::102a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DC723C061574;
        Fri, 23 Apr 2021 00:11:36 -0700 (PDT)
Received: by mail-pj1-x102a.google.com with SMTP id lr7so6497008pjb.2;
        Fri, 23 Apr 2021 00:11:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=HqJMjNWqtxCZEtFIyBmota7lpGm+rHS29SEa78vm9uw=;
        b=nKpRcIzrlcMWE/JIaAcQTt+sIk18JhHn3VNFy/+7A9crEFQKaRl/4ybysLR+RyzWLv
         JADj1GVyf+KH+Urzx3u5AYD/LI3Am90W0VLjwrlqt1MjdYsxAFsNg6wRnBOldXFZU6op
         pjdemQY94oHgbZbVAKj7ozhdOvRP1FBzfUuQekdQroOA4QtwScShv5ana/u+uckRBjjq
         NuJMKjOA0AGJii22hwhKlFmiql0z2ZNaQjCiH2+qSTfElfbYBC6oFqSeNBptRfzyR1mf
         HP6rCBZDhI6XTyQOMpc/OrXgtVfp0CEmEjd+zeLTrUNlmOpIysxCHKhEvkvOyO476Jwv
         h0rA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=HqJMjNWqtxCZEtFIyBmota7lpGm+rHS29SEa78vm9uw=;
        b=qdDK7zNTxo6uR5OV0rzMfXfeBFsIMUnoFNygU4NRVJpkZ/2rU7xMcNDYZugKcDNYcH
         6wDP49raSaGd8hPyJGRcxHZ/DNSN/P997XIuuy5g2uncfIJ4HOQuqHSzT/RGyhRTzwQ8
         vx5CZDws/JlvohgZWs7bJPtbNjr+22bKAU9PBXQwQ2PdhEthtHuQl7DGyXzZ/0rxpI5+
         CBwLh5oLuhHV7ikqWJCXMk0VFVqxoJnxU8OpESnXpywtEEpeJVi+yijW4x/g/uXdPpmm
         BQQtnWQyEJgE9UtvizNuH6T6TxeYP+56p5vUzg8TFHMn3s8UJX9XhkK4hrP3+io/06qL
         8Ttg==
X-Gm-Message-State: AOAM530+Qv7OphOFLrhmPZwrq9fe2t36HcaxCIID36CgjN4Q2Pgc2scG
        2287NhsCo9hxkFNWk0eqH1T4g1BW7pM=
X-Google-Smtp-Source: 
 ABdhPJwD5pvvAJW0GH6EobdDrhDTk3dYtqLbuFADme2Js6GZdjV8gfbMGPInO9bDebAZqhHaFrR4hQ==
X-Received: by 2002:a17:90b:e0b:: with SMTP id
 ge11mr4219103pjb.127.1619161896302;
        Fri, 23 Apr 2021 00:11:36 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 gj13sm6605427pjb.57.2021.04.23.00.11.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 23 Apr 2021 00:11:35 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: x86/xen: Take srcu lock when accessing kvm_memslots()
Date: Fri, 23 Apr 2021 15:11:23 +0800
Message-Id: <1619161883-5963-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

kvm_memslots() will be called by kvm_write_guest_offset_cached() so 
take the srcu lock.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/xen.c | 18 ++++++++++++++----
 1 file changed, 14 insertions(+), 4 deletions(-)

```
#### [PATCH] mips/kvm: Use BUG_ON instead of if condition followed by BUG
##### From: zhouchuangao <zhouchuangao@vivo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?b?5ZGo5Lyg6auY?= <zhouchuangao@vivo.com>
X-Patchwork-Id: 12219893
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 08627C433B4
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:35:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2B5F61459
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:35:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241568AbhDWIfy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 04:35:54 -0400
Received: from mail-m118208.qiye.163.com ([115.236.118.208]:50452 "EHLO
        mail-m118208.qiye.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S241550AbhDWIfx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 04:35:53 -0400
Received: from ubuntu.localdomain (unknown [36.152.145.182])
        by mail-m118208.qiye.163.com (Hmail) with ESMTPA id D00C1E0141;
        Fri, 23 Apr 2021 16:35:15 +0800 (CST)
From: zhouchuangao <zhouchuangao@vivo.com>
To: Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: zhouchuangao <zhouchuangao@vivo.com>
Subject: [PATCH] mips/kvm: Use BUG_ON instead of if condition followed by BUG
Date: Fri, 23 Apr 2021 01:35:09 -0700
Message-Id: <1619166910-70744-1-git-send-email-zhouchuangao@vivo.com>
X-Mailer: git-send-email 2.7.4
X-HM-Spam-Status: e1kfGhgUHx5ZQUtXWQgYFAkeWUFZS1VLWVdZKFlBSE83V1ktWUFJV1kPCR
        oVCBIfWUFZQ0kZSlYdSUNJShodSE4ZTBlVEwETFhoSFyQUDg9ZV1kWGg8SFR0UWUFZT0tIVUpKS0
        hKTFVLWQY+
X-HM-Sender-Digest: e1kMHhlZQR0aFwgeV1kSHx4VD1lBWUc6NBQ6ISo5LT8VOAxWOjYhS00d
        QhQaCkNVSlVKTUpCSk1NQkpNSE5NVTMWGhIXVQETFA4YEw4aFRwaFDsNEg0UVRgUFkVZV1kSC1lB
        WUhNVUpOSVVKT05VSkNJWVdZCAFZQUpMQks3Bg++
X-HM-Tid: 0a78fdde6dbf2c17kusnd00c1e0141
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

BUG_ON uses unlikely in if(), it can be optimized at compile time.

Usually, the condition in if() is not satisfied. In my opinion,
this can improve the efficiency of the multi-stage pipeline.

Signed-off-by: zhouchuangao <zhouchuangao@vivo.com>
---
 arch/mips/kvm/tlb.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH 01/12] vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12221971
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1228FC433ED
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 23:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9FF961466
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 23:03:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237320AbhDWXEP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 19:04:15 -0400
Received: from mail-mw2nam10on2080.outbound.protection.outlook.com
 ([40.107.94.80]:21184
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S237075AbhDWXEA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 19:04:00 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FGhTtYdC1xPV5x0MhlthzhzC22Cd8TCHfmyp4bNeARDGpSulb4ZSX1fOB93SNYO/fuijd6spQNFG5uKW9lLtTk759Hu482hq4lLdcl9wu7/N+F8udhx+J0GOTF3yptrmQJG1ThFy7/9ilszCc1iTmkc+Au3vmU0e4Srng4MEuw4NCwyiSG97aHmUOdO13zNXZxW2CXbyJ6A2pQ+CgkPllm1JCkhkUw1Ba1+gyX9JZROPnOKyIpU9pS7AZKxkQxv8KY1okoM6CONVCDiavj0xiiB2Fg3MV2/0s6U8zWnI2zeFu+BSwOAV1ZVSE60V3S175/X4KypNoMuU2fxzCVU5Ew==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=DAl1RpTrWqN5LZrV77LcK5OTpSV7Yj94D2r3e03JiG0=;
 b=j+WQrdXVd7A0yL5sfB9RiNJNoJqm4F+NZ+JlDi1/6UriVYoL+aWSzoLXtpvBOmt8lU6eowflTFzgXmRZMdTtDE0YegfCh8zrc+ZnsOHFopEPoujzeW9/+EIz8yNpff05J/ihjlpvJT3N5NJpq3c/+c/4OCPjUd76bm1TDX3jZjmWWdraDSXol3IVoG/JOASqkPvx2i41Z8Mo1GHjkl5Jq0/iBWdt03CWA1dgA1E6wtV7z4EEG05S54tpPPP9ZwF6qQuLiiza/s11PfYaEQH7hAUMSZf1VBtHzw1mBzmnHSawuQ5JFKT0Dp1Kirp2pGhWRfkTvT1UmA1aZw9VvT+9Rg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=DAl1RpTrWqN5LZrV77LcK5OTpSV7Yj94D2r3e03JiG0=;
 b=X5Jy1+ReBcns6rK1PQ/OAjh+5vEQsf90IdwgZ2tISBZdcgAQbFn3RE3KLXLszDAuVjQg6JqcPWMtSvmv6ZPNWLzrQPw4TCSWPQo1UZXz+gHlaX6qhk527athctokTIU3pEV7qpvA2z9ClGjolKh4OXIfwbF4uvyf66o2yCGK+mwN37oOYkf12Pv9pp/N5GXuxWLH7GaaWEGhResNWCsegIRSnU7Xgu8sB9RDLCqv0Vs6xMt+78DB4ej99nzuCssjgMgARXl9Z1fiFXPueL3FwIYDMMGPP/ZPXhrBrsgAB6JKiuHP0sXi4+NR8xXP1AkNGlnQqORYnC/U/VF3IqhBZg==
Authentication-Results: linux.ie; dkim=none (message not signed)
 header.d=none;linux.ie; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB3513.namprd12.prod.outlook.com (2603:10b6:5:18a::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.24; Fri, 23 Apr
 2021 23:03:15 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.4065.023; Fri, 23 Apr 2021
 23:03:15 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: David Airlie <airlied@linux.ie>,
        Tony Krowiak <akrowiak@linux.ibm.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Daniel Vetter <daniel@ffwll.ch>,
        dri-devel@lists.freedesktop.org, Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        intel-gfx@lists.freedesktop.org,
        Jani Nikula <jani.nikula@linux.intel.com>,
        Joonas Lahtinen <joonas.lahtinen@linux.intel.com>,
        kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org, linux-s390@vger.kernel.org,
        Halil Pasic <pasic@linux.ibm.com>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH 01/12] vfio/mdev: Remove CONFIG_VFIO_MDEV_DEVICE
Date: Fri, 23 Apr 2021 20:02:58 -0300
Message-Id: <1-v1-d88406ed308e+418-vfio3_jgg@nvidia.com>
In-Reply-To: <0-v1-d88406ed308e+418-vfio3_jgg@nvidia.com>
References: 
X-Originating-IP: [47.55.113.94]
X-ClientProxiedBy: MN2PR03CA0023.namprd03.prod.outlook.com
 (2603:10b6:208:23a::28) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (47.55.113.94) by
 MN2PR03CA0023.namprd03.prod.outlook.com (2603:10b6:208:23a::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.22 via Frontend
 Transport; Fri, 23 Apr 2021 23:03:12 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1la4pJ-00CHzQ-Sr; Fri, 23 Apr 2021 20:03:09 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 987eeaea-ffa1-4b72-292c-08d906abf841
X-MS-TrafficTypeDiagnostic: DM6PR12MB3513:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB351364686C5B2D51BA14B331C2459@DM6PR12MB3513.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 MfjuNpE2vY8jseRQZRK1FJHxMK4wrm+LQjHe2V8wd+/fuXS9xAoGO5T/IJU6atybzzokUyC0tONV0qYeIyBNsfxO069TKXs6U6L572HaoZsfbDcqMdwsVGIx8McMKVPzY2hldiTD15ATKKdT6cYphdzPK+SYAP/4PvWK+ryCXkGe4INt2IJVdM3VI186vwwNJKZXFVUTXIkx9ccObBdKyMbHNig7tluSYCLRotU/PkpQjnfGyv73ddnbkH2y/VyNVo95KjKN0eio/eFYDXiQZFsEgDk10jKxQPwvG8XMOy4D/ErP2gR9vaydVeDkXhCI2rBosLLMgW82JN83hLzXOFBcs7zLqTbjU4F1Ya+TUNW9ONhHvouEd8WxyUJX1c7HL7E1trTYa/yeDMpXhdWvIVBDJXbTuc5Msu8FBlJCXNXdtPp/IdYvarytX5WPlKs6DpE1gq8k4vKOxJdDBaCLx0m3iYor1MPi8d+l3m6DaTcp/n4+/dBsrsCHQrX/yzFY6CIQe1RZiZ4LjZYELK3JyLmj87cVWGG55xZIoDCbSy/tRTe8dKOjEe8WPd/pD1EJClRxk/mI5Ga6grfOEl0WSlm9p6F5xZ7bzhPBPQNB1fM5eU2QnZ95iP0z9+GCKIVL2LnAZlS29hY5CSyMH27VbjDE1RHi/vqcuqNV+7wG+FI=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(396003)(39860400002)(366004)(346002)(136003)(36756003)(66556008)(26005)(66476007)(107886003)(426003)(8936002)(83380400001)(921005)(9786002)(5660300002)(186003)(86362001)(9746002)(54906003)(38100700002)(2616005)(316002)(8676002)(7416002)(2906002)(4326008)(110136005)(66946007)(6666004)(478600001)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 hysLrLiltE4oQlNogxns20AtdqhTUwwSwB9iZ9lsQLS6vqc7OqYILVkLtv745QO0SYPjgA+TyTB+ZgUhQimGTN11vP48+wSSDWQo6OO9MJDV5bpirUFS+vHGjOMkxBHQJHRGCyRQsxN8UlwuptYtir5A1RkJus5ph/AV5aP2q5UBlnw7FoS9RUPf4VgKQjAKDsY0eScEPCef2TbzjphccsbbUbMr2RXg7bhJvw5qviKRLpE095tYJZk7AEUbUBsLnQSsmRdWeEoW3VSf+KAMx61zMcBaSKMuXhW+LVAo79a8ms6k+cNNdH05SRxjmBVxhxIqvpztQzwoIvd8qkohrImWm4HDU55m+NKX0KCZdL+5zv7Prm3o2DqWKoN8ZQ3Idsq9IE2v0a6Q16/PSr7Mduj5lEUMvoxKHZGKEfRHxnIK1X4y9szsLl95wehSJLs5hsKkjG3SNnAFrUiwjxeJNmyhrfBgQbsjylq5uivAR1I8O9BH4Nfc2qWAnrch1eWzH+gIMAlkrogxgk+3pQOlURjB8jfI8mV7cjiOM+RgR2LwfnwPZ7b8KfIKiK0pSmoOSaXVMn+gOXkwyZ8ttOQdYRjzxYGWF8EmmPkTzyVfZ91G0fspwFe7sz9TqVYuBQLC031EbSz1GamLqFKEzP+9aNb6a8f/wCWepklqLrVwgleHx2+AGDuJ3BgM00rZSIa0w6ZAw/3otxEQkSidnyYHy5g86mY9pgcM89VMKNNs/Ozq65f1t/Xj/dgCsuHSgkCN26hBtfElaXAfz/IGOEupkm8yg27Xo87coD6PKtsMHeQDFhszTvp2mVdE8sKuq+78PhZINLuoC8CsgctWNuzasa9EOmpEDPjl1z0O24jfPGrFbdpkdDkBBFicl5lROaXx6wDluJf4kx8YxowsaTTxcJONxYJgRzDdfpElTzwG1TGL0YfU1zi/VqRMXYdKuU7Syvg7ZhbVgKIMKE3rkI5EQ9B4iuOrTYlr9lnfR4uyywrW4iSEFNHNxIOirtytpeFPX677KQ69UiWt8gQGBANFjsIBkaKykSG5gyBsUEGPPhlJ1RFZAdItvVDyxzfGWz4LVNTcTiW80A1cP9g0CXh1oRxZsCyXIYcPRqYxviLxdElPWMALIntQu4wroHfdAXaPhrvvRV9QZX5nwIRcUGQqCIbX85y3eq2qbMvPLQn91i9xz24YtfNzWvkwVqhcEUeikGu2fBqmOedhdB6yPEjiuQ51qoSfWRFwCQAtZRJgo3nCT3+JLVs4LlEFaciB+u7FZawZ+IHvmJuFe8RB8wdfxHRnQa8PDHjbF6Ur3ZACGqCam8StzAFEwIpkiXSsXXvw
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 987eeaea-ffa1-4b72-292c-08d906abf841
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Apr 2021 23:03:12.8537
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 OZ7ZPacrzbFmx0cmW9bQDKIoOQ79lfpw4AEgHSl1Afhy+SQ/tjEZEAOde2NaQWK+
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3513
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For some reason the vfio_mdev shim mdev_driver has its own module and
kconfig. As the next patch requires access to it from mdev.ko merge the
two modules together and remove VFIO_MDEV_DEVICE.

A later patch deletes this driver entirely.

This also fixes a misuse of kconfig in the samples which prevented the
samples from being built in.

Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 Documentation/s390/vfio-ap.rst   |  1 -
 arch/s390/Kconfig                |  2 +-
 drivers/gpu/drm/i915/Kconfig     |  2 +-
 drivers/vfio/mdev/Kconfig        |  7 -------
 drivers/vfio/mdev/Makefile       |  3 +--
 drivers/vfio/mdev/mdev_core.c    | 16 ++++++++++++++--
 drivers/vfio/mdev/mdev_private.h |  2 ++
 drivers/vfio/mdev/vfio_mdev.c    | 24 +-----------------------
 samples/Kconfig                  |  6 +++---
 9 files changed, 23 insertions(+), 40 deletions(-)

```
#### [PATCH v2] KVM: x86/xen: Take srcu lock when accessing kvm_memslots()
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12219877
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C78C8C43460
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:23:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EA236141C
	for <kvm@archiver.kernel.org>; Fri, 23 Apr 2021 08:23:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241361AbhDWIYH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 23 Apr 2021 04:24:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46410 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230059AbhDWIYF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Apr 2021 04:24:05 -0400
Received: from mail-pl1-x631.google.com (mail-pl1-x631.google.com
 [IPv6:2607:f8b0:4864:20::631])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78B51C061574;
        Fri, 23 Apr 2021 01:23:28 -0700 (PDT)
Received: by mail-pl1-x631.google.com with SMTP id p16so20915719plf.12;
        Fri, 23 Apr 2021 01:23:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=rJls36wmWapo3qvKYvXIZESml4N0oAcI82yv0aWi8Zo=;
        b=tlZ3+VmVJgvoiB7BlALO1QgnB7apv1jxZ/roqgKjhDd8v7w+3XCuX3KKsTzURoauX7
         jcQOilCZb2wZmF9Kn4z3TdKGuo1Nntklx637Jfs3xlwtOSwcVDeUZys26OwMTTd03m8b
         Dp2YHfS3jsPZ4hxP2jZXU9tU0GiyDUV/qMnxmSC9n58KDFuhs2iY10k0SQD3diX+OTXb
         eBzR8fN8n3y9/OATUcHUEjMccCrhI3PNw59hkpbs2m5OLUDBOl1wIwzNkp/EXV5MoKLK
         kQbg048W5rTj1D2kXivCMd7m6iLmzjg5l5NiTZ0YpOpStshQNaGNrxem0NAyGQnll77G
         UD7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=rJls36wmWapo3qvKYvXIZESml4N0oAcI82yv0aWi8Zo=;
        b=mUiwmWA2JmuKk/+V8zq7sLGvVOGb7Wh6VqFbrO+/udhZG6KLHAIOC+oSNlXqeWGqjD
         j5dvaL03yX5xWxvqQ0jtwLAWVRjuPK9pMSaqRGSJYGYKIGLpriAM81vqdz/v/DrxyzMD
         Vhy/qd1AJOTivpbTqh+AyeX9vsTftCYBupOfCd83Rb/Y+fh3duNEOc5XJdOBt3POaDi4
         0FgnF0Nzfd+CIVRIASvH2GNIxbSaSSz7qIZ6aCyYLlEZI71lOq+i04emFKOvzAcvhYQq
         rjppzyDddeJ4kneqMyIcxxGTEfIAN2m3IQVDJJdpyqu6xD+MnDCo4VSdqmoCcYdqKAbZ
         zsfA==
X-Gm-Message-State: AOAM531mBLtRm9FX8EKEZ+bjGq1zb/QZtkc1/2HTpdnGoPCxjGeWQx6/
        blT7HXdT2WOAsoahkvwXIqOFfiFVTco=
X-Google-Smtp-Source: 
 ABdhPJx8rlLvieJFLdb68pZVfQ4X0tABu9WIsS0hK2O5SMgBs+3DDHEfjafsPSyVFR5V1Pj7YCUj2w==
X-Received: by 2002:a17:90a:a895:: with SMTP id
 h21mr3191124pjq.13.1619166207837;
        Fri, 23 Apr 2021 01:23:27 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 b7sm4096181pfi.42.2021.04.23.01.23.25
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 23 Apr 2021 01:23:27 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2] KVM: x86/xen: Take srcu lock when accessing kvm_memslots()
Date: Fri, 23 Apr 2021 16:23:20 +0800
Message-Id: <1619166200-9215-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

kvm_memslots() will be called by kvm_write_guest_offset_cached() so we should 
take the srcu lock. Let's pull the srcu lock operation from kvm_steal_time_set_preempted() 
again to fix xen part.

Fixes: 30b5c851af7 (KVM: x86/xen: Add support for vCPU runstate information)
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/x86.c | 20 +++++++++-----------
 1 file changed, 9 insertions(+), 11 deletions(-)

```
