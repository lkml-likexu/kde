#### [PATCH 1/3] vfio/platform: fix module_put call in error flow
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12265521
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1508FC433ED
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 19:21:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1DD560724
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 19:21:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1346055AbhERTW5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 15:22:57 -0400
Received: from mail-mw2nam12on2089.outbound.protection.outlook.com
 ([40.107.244.89]:64256
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S237739AbhERTW5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 15:22:57 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=PCp0+QtBpnHOoMRXx3j9LIAD5sfJJf/BafVvsgcWTDYUYBnqwYO7G7kQ+CRSv8wGWDQpYdgSgRn4O0JdBU2DPDVAu397r78glc7drgp8n7SmNKgUwsQZuJ/fAXG8qGqSfzQU6mW2/lc3p1Q9CiN4EAW0mNhfY6aFawmEm61TAwKf0MXjQSRa0CMAivIGop37hzvgfFtxtQGqMHdMj4J+QO4FuDl6j0DRtSI2plwUaFDz9aVAXYCAAWBEnbhl9R4weUTh0wGKt4yKGGKYyqekBP6HNi2gw11RTLJiIw1Rbk88xipR7s0uJT2mi6/cjIaoHjI352T92GuxGwNBnl2rPA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KcnTnGk4MKucZ5I2jfckFtN2j5CTu6Fp125uCcm022A=;
 b=RMGkE8DCHHEr/hTkwtfskGjE9NNS/Fm2fhfXD0UAVFCilkXt5P2yDIJsHEdF3FSYA97OWudJ/XncVKK7tfhzalNTZvM2N+Ru6eQEJKSanJUEW/m6d8GR4Kz8RMin+dV9jnFEb7vAx8ezEOhoeW72CgT8ooc2d+RYPx0p7Pbcb7qkRTeb+2K+C/9IEq/56pFYA73FEnh6CM+OwkOiCcE9XSGJHbYqekKdbcLbCcBO35P78GXXmKPgplpZFGbMZ8bz5VmzHQCEUsTdwEY/edOvDM7VuVasGvaDflmY+KV7Tc2WAftEE0BnDzfhxFO4OP1nLXeLO2ktMIJMP9MlGv1Kog==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.36) smtp.rcpttodomain=redhat.com smtp.mailfrom=nvidia.com;
 dmarc=pass (p=none sp=none pct=100) action=none header.from=nvidia.com;
 dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KcnTnGk4MKucZ5I2jfckFtN2j5CTu6Fp125uCcm022A=;
 b=X21r1NwuSPLcPFFOdVf2KYbqz2TYx6VhHC0cJyUGkYmuj+WF841VXMx1HjhlkFtj5m4snw9C1TNEgmyJBj/g6CbZP6Ii7Nu2tJu7QkXfp5kt/4l+xwTT1p79eT6MSnppfol2MQL042kVmHsVidlcs3/t1kea78RPym6nQtbZlRwZ1SvYU+6bDrvBFOmHQY2iu7x5NyK22X55SHDfMY0AF0bEWssFh2j670QX1kCFjjuOM5vTPD7QxROl23yc21e/cYUER+PMyVKHoDw3dZNoEKx1CzlvKgHnBXTzuQEwY+I0EL+2c4JzSZUqRvJzDE8LTvjUFRxj+00mIO2vZTr6+Q==
Received: from BN6PR18CA0013.namprd18.prod.outlook.com (2603:10b6:404:121::23)
 by MWHPR1201MB0255.namprd12.prod.outlook.com (2603:10b6:301:4f::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.26; Tue, 18 May
 2021 19:21:37 +0000
Received: from BN8NAM11FT049.eop-nam11.prod.protection.outlook.com
 (2603:10b6:404:121:cafe::2a) by BN6PR18CA0013.outlook.office365.com
 (2603:10b6:404:121::23) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4129.25 via Frontend
 Transport; Tue, 18 May 2021 19:21:37 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.36)
 smtp.mailfrom=nvidia.com; redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=pass action=none header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.36 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.36; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.36) by
 BN8NAM11FT049.mail.protection.outlook.com (10.13.177.157) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4129.25 via Frontend Transport; Tue, 18 May 2021 19:21:37 +0000
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Tue, 18 May
 2021 19:21:36 +0000
Received: from r-arch-stor02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Tue, 18 May 2021 19:21:34 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <jgg@nvidia.com>, <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <alex.williamson@redhat.com>
CC: <oren@nvidia.com>, <eric.auger@redhat.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/3] vfio/platform: fix module_put call in error flow
Date: Tue, 18 May 2021 22:21:31 +0300
Message-ID: <20210518192133.59195-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.18.1
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 1bc92793-59fa-41a6-e77e-08d91a322806
X-MS-TrafficTypeDiagnostic: MWHPR1201MB0255:
X-Microsoft-Antispam-PRVS: 
 <MWHPR1201MB02552E1D75670B5263B1B322DE2C9@MWHPR1201MB0255.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5236;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 EnCdjKX8zbDKGqgC70wKUCfx9tsi/qrDVCqXETqGZFweAL35MjU2ZWTTnQolM4UCb3kGVcQ487Ntx2TaTVyqg+l1/yov3yWziTlDvgmX8Yc8/VwwwwJUURQqkERm/0loo0Uqu6ye9IfFzkQOk7ngxA+sJpGMdawGUfkFskxHCRhjxo2l02N9ZKXeYhneyvnYOs5o0tbshLoC7X/DecVAvPmbkypdReY9NUOVxFGA6rDN4LXwbCCsMQuVJRkyrguox3FpfIwBgkTh6Kz1inOSIJJouAtydmvckk9EO79ACyfI4wc3PgQPlllB6NwR/RWueVm62/saFdYEmEKg/JKrjTW27Nb4G3+0BYCO6F4pteLE4w0GX8zv0mRkFHd+0ANPc2AhvBVgfSiVYse3F36WKagEC47E+sN6vwOguWcLXrFfm7H7GexseMNQXJfo5BJURJ0lBrzT0hQLQ2Q6gH0nBxpWtRBVxmGfjRizoQ4o1f5vOfjaVxCwEXVIGAsDsRBQoNAlcaMyLngcHGzAa3poadQL4NOXOU4e5hqLnZMsk2SivyZvE4gTBB5J678FjnOs4yGaWOMHxMm+QY7INxT39srxhUN08DinVoA4nOoE4sizsuGX9u2px/FO8npiHnbJU1qp180EqF5Mm4/GgpmT9w==
X-Forefront-Antispam-Report: 
 CIP:216.228.112.36;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid05.nvidia.com;CAT:NONE;SFS:(4636009)(376002)(396003)(136003)(39860400002)(346002)(36840700001)(46966006)(4326008)(356005)(70586007)(6666004)(7636003)(82740400003)(70206006)(36860700001)(426003)(5660300002)(478600001)(186003)(8676002)(4744005)(336012)(2616005)(47076005)(82310400003)(83380400001)(8936002)(54906003)(36756003)(316002)(36906005)(26005)(2906002)(86362001)(110136005)(107886003)(1076003);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 18 May 2021 19:21:37.0104
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 1bc92793-59fa-41a6-e77e-08d91a322806
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.36];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 BN8NAM11FT049.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MWHPR1201MB0255
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ->parent_module is the one that use in try_module_get. It should
also be the one the we use in module_put during vfio_platform_open().

Fixes: 32a2d71c4e808 ("vfio: platform: introduce vfio-platform-base module")

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---
 drivers/vfio/platform/vfio_platform_common.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/5] KVM: SVM: Drop unneeded CONFIG_X86_LOCAL_APIC check for AVIC
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12264943
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D0A0FC433ED
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 14:43:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7952611CC
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 14:43:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236931AbhEROpO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 10:45:14 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:48335 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236568AbhEROpN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 May 2021 10:45:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621349035;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=YyZqA/lEHopR022+gKHNImNj/1J/RllfZJqdZZCyKE8=;
        b=Qm/B4UTGfqpRapWU+letDU+kVDkLU5BMkEBsnBEI4ZGGNPjfgFGJnnTByo5qHc+gkDJlBk
        NnfqhRFk6PUXDM7HUszfqRAlhxZmnLsf1rN04dTzs40gdFlGiGppqCmOO3b/4ZPjgsI3iD
        0tWyiBElbO78TMzBkZ94SGVDFOYdL7o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-150-dNVZV9U-N7eTZ9Z8ya5iUg-1; Tue, 18 May 2021 10:43:51 -0400
X-MC-Unique: dNVZV9U-N7eTZ9Z8ya5iUg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CCFFA8049D1;
        Tue, 18 May 2021 14:43:48 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.194])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 91AFC1349A;
        Tue, 18 May 2021 14:43:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Kechen Lu <kechenl@nvidia.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/5] KVM: SVM: Drop unneeded CONFIG_X86_LOCAL_APIC check
 for AVIC
Date: Tue, 18 May 2021 16:43:35 +0200
Message-Id: <20210518144339.1987982-2-vkuznets@redhat.com>
In-Reply-To: <20210518144339.1987982-1-vkuznets@redhat.com>
References: <20210518144339.1987982-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AVIC dependency on CONFIG_X86_LOCAL_APIC is dead code since
commit e42eef4ba388 ("KVM: add X86_LOCAL_APIC dependency").

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/avic.c | 2 --
 arch/x86/kvm/svm/svm.c  | 4 +---
 2 files changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH v5 1/7] KVM: x86/mmu: Deduplicate rmap freeingFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12265237
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73506C433B4
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 17:34:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 59C5F61361
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 17:34:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1351172AbhERRfo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 13:35:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40990 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1346564AbhERRfk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 13:35:40 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 27118C061761
        for <kvm@vger.kernel.org>; Tue, 18 May 2021 10:34:20 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 d20-20020a25add40000b02904f8960b23e8so14526116ybe.6
        for <kvm@vger.kernel.org>; Tue, 18 May 2021 10:34:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=+sf6y3nv2ZCNMXtqDYEEUFgNmENQxF7tXN6LoZYjT6w=;
        b=PU5+p2NnY0u4ZuZWWlDMiOb5GYo4r0+qOUW247POD85mVHqQiV4MByP+516xA+ko2N
         /eF+jpmKfJWCWyS7Q4l2p6GRWAxftv+4SaTlD1Yugk4v+ULn+VBaqO2nq5bLS8hIEhT9
         Tg7RrVP/OYR+8R9yE1+KGIy29BlteCy4tRBeJnvgy6TE4Q2rQjs2q4Cobi4mJP+fHS4s
         ix7/OKNTcfbmyrksuvBL7t+oKlXF9zemZ8sK1SrqXMD+4rNEjHT3mHtzDvxLInriml6W
         YRRe6p+pwWm97JSG2jVcwOT0U0mlO/aX4HEHbPEJPxXpvig4tpNA//j6p5RqF4piBk76
         gfcA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=+sf6y3nv2ZCNMXtqDYEEUFgNmENQxF7tXN6LoZYjT6w=;
        b=lR1MKMYVL7pRapy+LykatQw2vrsbUW42fyaty6veExZt1o4u1JFLXmI2DrmMPgGazH
         77FYowDN5P5BhMa8J7EdghfPOEEx3jGnflzTg2nQb4bFHkkO0/zZpqNM7MnxCwsSUe3P
         hZBUJue7HzCjIkczwFg4VAW01sYSbKv3Y8WjeaLpLTg0PMn/jFWn85qU0/bJqV5Hz4+c
         rhuhQAt+j5dHhcESkdT+QRNcYfQlbjq4JHiXpqiqjmJgXjFQYqbAaqe6Iqmp2QLWzQ1j
         hCb+5FNpOLAnCIliFW916Mcrtg7AwTSk8dhHQRVwdI3/Tr141y8Kn0ngYhQW2nhG78YZ
         yXbA==
X-Gm-Message-State: AOAM530s1IRzvNZKFNITVHvKBxECywoJSBAY1kUG8xDdT6cEV/liogRo
        pR6yV2fO8/OQRe3mTJQjZAp3h0iPSbD1
X-Google-Smtp-Source: 
 ABdhPJyFg3C3gccSXGLVHaDl3yMQ2ccs5PyYFlbCOevTKAIcdWPUH93Yi7nwEn0Wy8SM+qElCtaO8jLNrmd1
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:2715:2de:868e:9db7])
 (user=bgardon job=sendgmr) by 2002:a25:6c0a:: with SMTP id
 h10mr8538112ybc.167.1621359259737; Tue, 18 May 2021 10:34:19 -0700 (PDT)
Date: Tue, 18 May 2021 10:34:08 -0700
In-Reply-To: <20210518173414.450044-1-bgardon@google.com>
Message-Id: <20210518173414.450044-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210518173414.450044-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH v5 1/7] KVM: x86/mmu: Deduplicate rmap freeing
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        David Hildenbrand <david@redhat.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Small code deduplication. No functional change expected.

Reviewed-by: David Hildenbrand <david@redhat.com>

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/x86.c | 19 +++++++++++--------
 1 file changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH v4 1/5] KVM: exit halt polling on need_resched() for both book3s and generic halt-polling
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12264681
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id A4DFDC433ED
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 12:01:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78BFA60FE9
	for <kvm@archiver.kernel.org>; Tue, 18 May 2021 12:01:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1348982AbhERMCz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 18 May 2021 08:02:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49392 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233662AbhERMCu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 May 2021 08:02:50 -0400
Received: from mail-pj1-x102a.google.com (mail-pj1-x102a.google.com
 [IPv6:2607:f8b0:4864:20::102a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 65F60C061573;
        Tue, 18 May 2021 05:01:32 -0700 (PDT)
Received: by mail-pj1-x102a.google.com with SMTP id
 j6-20020a17090adc86b02900cbfe6f2c96so1419317pjv.1;
        Tue, 18 May 2021 05:01:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=em3y75NXotaLU/AKtI4LMXPcEnf5Ld1kv/mHHILm70c=;
        b=V/p4lH/6d5UguGqICWMegLeErmFH7naXSe4DlY8l+O9zRNBHKkp8LUKd2lN4M2qCZ/
         Trfkad+GRBI0RamLpWK3ZyCmXmEqFbV6NJePLgTFCNJjgMHwGWgCRtKt00TIYG0joO4k
         anoh6qGD6DuPuv5gV77s2MQLWPIO5Kx3XOTx+XtklL587DU3TGpUjnvGY3qK9Ntrg/IG
         /cYtXr8tfUYW2Qkv/HpRerACyiOJdAlfcp0KaWDk0Yvlo+LjdkWl41LDnazF1MNDs5Bw
         HlfGiR1kq7LWa2iaXyCbebVh9T/ue0MEoJ69JYBlgMZ0z8HSU8xW2H/p7ngeQ7Cqy9ni
         eJLQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=em3y75NXotaLU/AKtI4LMXPcEnf5Ld1kv/mHHILm70c=;
        b=osG/hjTWDXsgCY9PgdzdlhEM9OlZzIHq+F1PmWpYyzmOZKKuoKD9Q13auMHnCGoK5B
         2yM0hc5Cgo+8QjUGtRE59skDh8Mua0FsTb2pnPuq+ZGiemUIqri6cDoFO9ITdwpcl/qh
         Hw32QwOH0dlztBCl3K/h6wpA8cjnEI7L5NyTWAghXn3yioj7jfoF2Y1KVq/VoHjBNUTv
         AioiQY4z/eJvsiZgFrHAYgCirjEJiKleEXpczWCvShONyqWPM4+wyhNugJDqw1InUX+Y
         gKb0JH55oSusiJTUz9cm0eeqwzAh3OrWX3E5QD20/trBoFxKjrOD6j7FchhE6VVUA6P6
         xr0w==
X-Gm-Message-State: AOAM5329CEqUv76cUaLUwUFubKkIzjj9ZkB5r3xycnMQqU2EEYVvUir9
        SgwLLUiehss3a4CVC+EJbru/M3OX+Q0=
X-Google-Smtp-Source: 
 ABdhPJzuaIu1kDieJYdkyutSSE1hKoGm9LjVD+Vi0D2+YlF331ZxLvgY6I3C4fUQhe3dRm4RAN44MQ==
X-Received: by 2002:a17:902:f203:b029:f0:d225:c6e4 with SMTP id
 m3-20020a170902f203b02900f0d225c6e4mr4271634plc.0.1621339291776;
        Tue, 18 May 2021 05:01:31 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.53])
        by smtp.googlemail.com with ESMTPSA id
 l20sm12757394pjq.38.2021.05.18.05.01.27
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 18 May 2021 05:01:31 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Ben Segall <bsegall@google.com>,
        Venkatesh Srinivas <venkateshs@chromium.org>,
        David Matlack <dmatlack@google.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Subject: [PATCH v4 1/5] KVM: exit halt polling on need_resched() for both
 book3s and generic halt-polling
Date: Tue, 18 May 2021 05:00:31 -0700
Message-Id: <1621339235-11131-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 262de4102c7bb8 (kvm: exit halt polling on need_resched()
as well), CFS_BANDWIDTH throttling will use resched_task() when there is just
one task to get the task to block. It was likely allowing VMs to overrun their
quota when halt polling. Due to PPC implements an arch specific halt polling
logic, we should add the need_resched() checking there as well. This
patch adds a helper function that to be shared between book3s and generic
halt-polling loop.

Reviewed-by: David Matlack <dmatlack@google.com>
Reviewed-by: Venkatesh Srinivas <venkateshs@chromium.org>
Cc: Ben Segall <bsegall@google.com>
Cc: Venkatesh Srinivas <venkateshs@chromium.org>
Cc: Jim Mattson <jmattson@google.com> 
Cc: David Matlack <dmatlack@google.com>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v3 -> v4:
 * rename to kvm_vcpu_can_poll
v2 -> v3:
 * add a helper function
v1 -> v2:
 * update patch description

 arch/powerpc/kvm/book3s_hv.c | 2 +-
 include/linux/kvm_host.h     | 2 ++
 virt/kvm/kvm_main.c          | 8 ++++++--
 3 files changed, 9 insertions(+), 3 deletions(-)

```
