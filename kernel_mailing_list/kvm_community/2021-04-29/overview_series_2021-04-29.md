#### [PATCH kvm-unit-tests v3 1/8] arm/arm64: Reorganize cstart assembler
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12231563
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 54B04C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:41:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 096F56140C
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:41:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240824AbhD2Qmc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 12:42:32 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:43947 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233099AbhD2Qmb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Apr 2021 12:42:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619714504;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=TslnRqE0mRcJII5nyI9E9Ex8fm7/Lw2IOiNlNoFrCTk=;
        b=Lwdp8/YeN7TEAKSxUHWeCigBtBJypF4nheMDgZjhhxSFZYJEcHVOWqA6QsjPvMmtA9FSC5
        yEfdOCdO0tC7b2Uz+OEobO8/tzzb0ToZArsGf7EMxNjRK7PP0SoP6CrcknBFpEujooX1WC
        iAkXTrfsFQRWdkjn8Xa/i6noyxGokao=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-170-GXp_yXj1PUKliDdLCGsXTg-1; Thu, 29 Apr 2021 12:41:41 -0400
X-MC-Unique: GXp_yXj1PUKliDdLCGsXTg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5ED30107ACFB;
        Thu, 29 Apr 2021 16:41:40 +0000 (UTC)
Received: from gator.redhat.com (unknown [10.40.192.243])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D99DD5D6DC;
        Thu, 29 Apr 2021 16:41:38 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: alexandru.elisei@arm.com, nikos.nikoleris@arm.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests v3 1/8] arm/arm64: Reorganize cstart assembler
Date: Thu, 29 Apr 2021 18:41:23 +0200
Message-Id: <20210429164130.405198-2-drjones@redhat.com>
In-Reply-To: <20210429164130.405198-1-drjones@redhat.com>
References: <20210429164130.405198-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move secondary_entry helper functions out of .init and into .text,
since secondary_entry isn't run at at "init" time. Actually, anything
that is used after init time should be in .text, as we may not include
.init in some build configurations.

Reviewed-by Nikos Nikoleris <nikos.nikoleris@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 arm/cstart.S   | 66 +++++++++++++++++++++++++++++---------------------
 arm/cstart64.S | 18 ++++++++------
 2 files changed, 49 insertions(+), 35 deletions(-)

```
#### [RFC 1/2] vfio/pci: keep the prefetchable attribute of a BAR region in VMA
##### From: Shanker Donthineni <sdonthineni@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shanker R Donthineni <sdonthineni@nvidia.com>
X-Patchwork-Id: 12231547
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CDFBEC433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:29:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 97D306143B
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:29:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240839AbhD2Qaj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 12:30:39 -0400
Received: from mail-dm6nam11on2059.outbound.protection.outlook.com
 ([40.107.223.59]:38944
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S240824AbhD2Qai (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 12:30:38 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=HigXDxsrr9C3Lg9kfODmflrVI0DVvvGkuoc04TDVl7rJLoREscHLrd0kEqT3xg1F88bryehAHT2O5LPZDSwo5u9mf43F/IbB4cqy7pEfXL8zNCZKqaf1D2INXPZ2mA5kq3n6IZ59+VsQz8nQRzrwPCmYHCZxp3cHzxD6ZtNxoUzpP3KelY3IoKsMNvAbmurAzRcexJwqk99VBeSNrJjmIGlV0z7RsI2tOlV4+fDNn4eVNyDf+SMewP2kwf7f0uypdSdyYXiojqdOXfDJQN2yGgmMc0SyF+o1Fa7sOyn1I+s3ubOvUxksmpW1HSioxEIsNC43h0+Se9IL78scbHMOFA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qc1ZY0y/mmzxUignXhrkMhd0H8c12S9xVSQzGDOnvmI=;
 b=cFykG61wl4h6ScSZTVmYGy2oQG7vKqYT2JL5uaTD7uh6o+Wg02uOc+W/+vto1ZMSnP5cf/i8bphnkfvtq7uQeox0jveLs/wy1MRNTeX9vx/Hbrw+zCAdm5ghl2iGQNJI9cN0F7iVjPmQqg2oNGx1UMQOsaZ+Thi2Qt8aJpg2RuJ77fvagtr/UiTt+xAKjPFzeODKIk8PbfxSYUomRY98T1OZ0L3h1zhqjYMr+tggOEXCEsNBMm+wgfohOsbs5b9G3OgGTi6Mb91llr78h3B9HJqk9/DHJTw91ma/ayS+PuWqNJ7CO0MN0I1bcC9YhUkECMHaRvA0Ckws3rS4LH5lcg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.34) smtp.rcpttodomain=lists.cs.columbia.edu
 smtp.mailfrom=nvidia.com; dmarc=pass (p=none sp=none pct=100) action=none
 header.from=nvidia.com; dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=qc1ZY0y/mmzxUignXhrkMhd0H8c12S9xVSQzGDOnvmI=;
 b=iHrucmpRoNOuv1ch20G5La28U4gyu5ktOZmEtMRKUKbJJa+PlL0x9AH8NtS1V93jJdaR7KJzO+yW4WV5ySyAL/r2WGroohQUgCk5wKjsahWdlB2mKtbPnCFWqCW36MG4yeVrjafzGROtBiFXeLfdK6q3qbt1tpGydA4ld4AZQnzVVjYBhOTuQsRPYjCCuFNkKDaQqj55Z08gZkbQxD6bi35PQYbkgi2XN2eNZ4nCQf3QSBH2ntkjBVtGvCcyUGsJQQompS8ysCuKw2Tn4WHnI5imJDceAGLFCtJru8MeJsMtlDwCgSMO5jfN3Ezq17DS4XFWCq2nxgXItTA+BnrBzg==
Received: from DS7PR05CA0004.namprd05.prod.outlook.com (2603:10b6:5:3b9::9) by
 MN2PR12MB3279.namprd12.prod.outlook.com (2603:10b6:208:105::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.20; Thu, 29 Apr
 2021 16:29:49 +0000
Received: from DM6NAM11FT015.eop-nam11.prod.protection.outlook.com
 (2603:10b6:5:3b9:cafe::5f) by DS7PR05CA0004.outlook.office365.com
 (2603:10b6:5:3b9::9) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.8 via Frontend
 Transport; Thu, 29 Apr 2021 16:29:49 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.34)
 smtp.mailfrom=nvidia.com; lists.cs.columbia.edu; dkim=none (message not
 signed) header.d=none;lists.cs.columbia.edu; dmarc=pass action=none
 header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.34 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.34; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.34) by
 DM6NAM11FT015.mail.protection.outlook.com (10.13.172.133) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.4087.32 via Frontend Transport; Thu, 29 Apr 2021 16:29:49 +0000
Received: from SDONTHINENI-DESKTOP.nvidia.com (172.20.145.6) by
 HQMAIL107.nvidia.com (172.20.187.13) with Microsoft SMTP Server (TLS) id
 15.0.1497.2; Thu, 29 Apr 2021 16:29:47 +0000
From: Shanker Donthineni <sdonthineni@nvidia.com>
To: Marc Zyngier <maz@kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>
CC: Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>, Vikram Sethi <vsethi@nvidia.com>,
        Shanker Donthineni <sdonthineni@nvidia.com>,
        "Jason Sequeira" <jsequeira@nvidia.com>
Subject: [RFC 1/2] vfio/pci: keep the prefetchable attribute of a BAR region
 in VMA
Date: Thu, 29 Apr 2021 11:29:05 -0500
Message-ID: <20210429162906.32742-2-sdonthineni@nvidia.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210429162906.32742-1-sdonthineni@nvidia.com>
References: <20210429162906.32742-1-sdonthineni@nvidia.com>
MIME-Version: 1.0
X-Originating-IP: [172.20.145.6]
X-ClientProxiedBy: HQMAIL107.nvidia.com (172.20.187.13) To
 HQMAIL107.nvidia.com (172.20.187.13)
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 9a05a37d-ff50-4df9-2514-08d90b2c0257
X-MS-TrafficTypeDiagnostic: MN2PR12MB3279:
X-Microsoft-Antispam-PRVS: 
 <MN2PR12MB327973533D144AA452CBFB0BC75F9@MN2PR12MB3279.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 R5uV8e2n/TzbukeRD5bi7IhDHNlzBheZ0tv4afAb8qoH1xLRRFeXD+m+G9V1w/rPVQVZhb0UPaL5d0HXenU52hMhtRIKBP13Ag+sKbzxbL0bx2aZLLyltuqVjsdf3jWpvIw+AR6aKOBZnF7Lg8Yd9+LagWdE9+eC7gvBn03TACgRnT4Dw1rNJl1WbW+RHCZCDOTwC7nB7jifDWANDX8Fb2shiyXJ6r5cl+KK3ilEOrLz8kxNkRhiYSIEO7i5/1x/6LgAj41aXN52eI3Q6rg8Zak8PSXroqu8/haJFh8XwXP1eYqfKKWt4j7Rxsabb73iqyeiLimsAgWQPrQR9zdPXphINUJN7z0/skRibrf7xGgHYaPdrfpCQN1VBIUpLqDjMZkLH9ADut8ume6WP6ypRbjNivKN40c7c0nb6rNeEbXhTeuFWeXjjyREyX8TE9JYPCasnxpu9xnoq6OZi9+C5DyPfgb+457IGM6ZUB7+M7ahyiZrldUzim3O+mIuTsCDVibZp4v58j6g35YDGq/bX/6sBSi+HbZEBLemvQEFV3vDUFlJXgZtnFk3Qv7MmznqK+IkvI1b98wUzilAeelNYLZoGUpbedIm3mAmpAmK4XWr0yyafGVczsnUQCr2oFqWYFnOJTP9cdT0lE4pGGBOaQqbAspzfwApUuNMGsMHMnXaJMkmYwogeV/oQtoeyi+A
X-Forefront-Antispam-Report: 
 CIP:216.228.112.34;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid03.nvidia.com;CAT:NONE;SFS:(4636009)(396003)(136003)(346002)(39860400002)(376002)(46966006)(36840700001)(16526019)(336012)(110136005)(186003)(5660300002)(426003)(2906002)(2616005)(1076003)(36756003)(8936002)(70206006)(54906003)(107886003)(36860700001)(86362001)(6666004)(47076005)(26005)(316002)(7696005)(70586007)(8676002)(82310400003)(82740400003)(4326008)(7636003)(83380400001)(356005)(36906005)(478600001)(3714002);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Apr 2021 16:29:49.4348
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9a05a37d-ff50-4df9-2514-08d90b2c0257
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.34];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT015.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR12MB3279
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For pass-through device assignment, the ARM64 KVM hypervisor retrieves
the memory region properties physical address, size, and whether a
region backed with struct page or not from VMA. The prefetchable
attribute of a BAR region isn't visible to KVM to make an optimal
decision for stage2 attributes.

This patch updates vma->vm_page_prot and maps with write-combine
attribute if the associated BAR is prefetchable. For ARM64
pgprot_writecombine() is mapped to memory-type MT_NORMAL_NC which
has no side effects on reads and multiple writes can be combined.

Signed-off-by: Shanker Donthineni <sdonthineni@nvidia.com>
---
 drivers/vfio/pci/vfio_pci.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: exit halt polling on need_resched() as well
##### From: Venkatesh Srinivas <venkateshs@chromium.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Venkatesh Srinivas <venkateshs@chromium.org>
X-Patchwork-Id: 12231537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1737BC433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:22:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAEA36143B
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 16:22:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240822AbhD2QXj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 12:23:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37552 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240824AbhD2QXh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 12:23:37 -0400
Received: from mail-pl1-x636.google.com (mail-pl1-x636.google.com
 [IPv6:2607:f8b0:4864:20::636])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 43AEDC06138B
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 09:22:50 -0700 (PDT)
Received: by mail-pl1-x636.google.com with SMTP id a11so4147201plh.3
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 09:22:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rNKQky1/Pnzp033ZdzLSy1gbwgv/Gccj40dEtj5FDpQ=;
        b=hibuFhOx/LICnV8bWJWt26zjOulR0Bk+h06aknCeZPUayat5uMBozj6Y6URHdxOKmo
         oWCzLOM6a3wwgEM5/IxOEZ13a3PdYvVz8bBYuXVuxSLIhfbSzafbXqxngWI0Y/9iMyaK
         Ov3h8xcebcTNgy+EkIBXedpgumbo+xZkXAEd8=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rNKQky1/Pnzp033ZdzLSy1gbwgv/Gccj40dEtj5FDpQ=;
        b=UOKXlSE69XW2tT75rFn5+xYFGDyc/NQEEzFJRbg5a20Dcxf1Dh8zYzX/YGIpwfkbHC
         erAobah+/ceozTAR6hDxMoqjRWdabyW3CqlZ6SmpIqko4ysWQjENrrSGkLnWY8srOEMp
         GxUy+GhE1kUeMqnGlsyPfBQqk/YHZ366QedV8pUXza+v3aLWzhbuzzac5pi5CDmXQv+/
         ZIeapS/95BtyaI5xt+sjbhF3ZKHSQRR/Sw4YLMCIs9IjMh7Op0vemzb/Btk5A/fkLQ3W
         Owhu60eQ7KvzuFKCkrZ1qi6U45gU19XWGdrstLVry2D497a/Jf6tlYLPlVVMlv0xKioF
         Ay2g==
X-Gm-Message-State: AOAM533hGIWasPuierTLi64mkQTiamZRSbdQL8qNcU6nP3O2/Bpu+a0V
        Z+pIYRO/BP7KzTRimTNXUL4OIzahq1hyfw==
X-Google-Smtp-Source: 
 ABdhPJwRmjGWAAnhyPMGDR8T8D/x+9uZM1W3/KEjblGsi/sRhDjOvkBSEMhT6+veMKoprCjdmUF2rQ==
X-Received: by 2002:a17:90b:1bc1:: with SMTP id
 oa1mr670125pjb.46.1619713369563;
        Thu, 29 Apr 2021 09:22:49 -0700 (PDT)
Received: from portland.c.googlers.com.com
 (254.80.82.34.bc.googleusercontent.com. [34.82.80.254])
        by smtp.gmail.com with ESMTPSA id
 k13sm2884271pfc.50.2021.04.29.09.22.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Apr 2021 09:22:49 -0700 (PDT)
From: Venkatesh Srinivas <venkateshs@chromium.org>
To: kvm@vger.kernel.org, jmattson@google.com, pbonzini@redhat.com,
        dmatlack@google.com
Cc: Benjamin Segall <bsegall@google.com>,
        Venkatesh Srinivas <venkateshs@chromium.org>
Subject: [PATCH] kvm: exit halt polling on need_resched() as well
Date: Thu, 29 Apr 2021 16:22:34 +0000
Message-Id: <20210429162233.116849-1-venkateshs@chromium.org>
X-Mailer: git-send-email 2.31.1.498.g6c1eba8ee3d-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Benjamin Segall <bsegall@google.com>

single_task_running() is usually more general than need_resched()
but CFS_BANDWIDTH throttling will use resched_task() when there
is just one task to get the task to block. This was causing
long-need_resched warnings and was likely allowing VMs to
overrun their quota when halt polling.

Signed-off-by: Ben Segall <bsegall@google.com>
Signed-off-by: Venkatesh Srinivas <venkateshs@chromium.org>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 virt/kvm/kvm_main.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/4] KVM: stats: Separate common stats from architecture specific ones
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12231905
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D545C43603
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 20:37:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 35AFA6143F
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 20:37:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237110AbhD2Uig (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 16:38:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37182 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235220AbhD2Uid (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 16:38:33 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 774AFC06138F
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 13:37:46 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 a15-20020a05622a02cfb02901b5e54ac2e5so24848580qtx.4
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 13:37:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=14suypAhZWrTvUZ9nTnlmd/J0OIx8qi10cj8Bzcjk0o=;
        b=W3vbWYibcBictgt7A3BpbwqU2ChaQ7oJGKfqjjpdzb52KzG2DHlJ73zDjRXXelKSKk
         0bIR+bnksXva1PFzvSJvwf8DHW+sAK/9EsTcJeyVHqyp9k2Osw2DvY8DSwNxZTf7Zbp8
         ZdkGzf3TQkLRpXYOXGkNVufVIiQGqclCqf6o0tpostI2CjrqAryx8shzu6sVcXBmpyI8
         qaCR1cOG/50UGtPgqrIdX2QwRhN9LPeDO4+0ywB0/IVM+bd7XGtiwLeEaPNcLRzKZVPK
         JBYCqcRXIYQK3z22SviQyFD4j05bbRQ6xMRzkaSJ9Jtuzx7p4lRSxnwxLMAw312SfXMH
         tFMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=14suypAhZWrTvUZ9nTnlmd/J0OIx8qi10cj8Bzcjk0o=;
        b=fXaE2iImCMG84JAettNg2ujgwDn5amURa6M6Ybtci0NqlO3x+0WhrHRz5SNbbXL3mo
         PcHOKL7RRM/qshcRz9/V3gdUn6DyzEjm06iF0zv1ktEfVAKBWDAPlYwyZ0F+ChJaTOR7
         riL0NDS2HH1dhwGIrLJ5fjYIOCzR/ehhM75NctmDBU7iJnz2BydG4hTYHawjMUDBaijn
         cl0F735UuNv/9xdT0nDpfWf883fZn+1VMQwBsruCCyjkkXne0Dy0YXqT9Mm2l6IYvb2r
         Cbzlnf3xCGfruzYoDyoSUfqOvHNHTTEOwESOsxWkZ9CwQuuarBu/YAnznY0NCkdgjkUc
         5a2w==
X-Gm-Message-State: AOAM530ktN2wMmgNSWojd0qyky2+PSXS1nCzCHvx00isq+Ny5UjgNoyf
        mmeAxotcKaqdN70gYNkhOu/C2eP20Tu4E8+5Ki/BRx6K+32IcGW5shWO9G1zIoZKrUQeNOa/BUJ
        TU55NMpwL9TsDv/IL5JCNBcR6HJajNj2NAw6tsy9nIUxC51GotCO0WkuhZUN2xkii6Kod/TE=
X-Google-Smtp-Source: 
 ABdhPJw84FPYY5E3AbQSJGKW5SUkXjQu+JZYUGFKyjTw+80GpcffxhSHmEDG7zCL45U/8ZpkV+dultiA05HT1gFgaA==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a0c:99d9:: with SMTP id
 y25mr1759309qve.28.1619728665501; Thu, 29 Apr 2021 13:37:45 -0700 (PDT)
Date: Thu, 29 Apr 2021 20:37:37 +0000
In-Reply-To: <20210429203740.1935629-1-jingzhangos@google.com>
Message-Id: <20210429203740.1935629-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210429203740.1935629-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v4 1/4] KVM: stats: Separate common stats from architecture
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
#### [kvm-unit-tests PATCH v3] configure: arm: Replace --vmm with --target
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12231387
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA816C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 14:11:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6349C61420
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 14:11:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237419AbhD2OMO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 10:12:14 -0400
Received: from foss.arm.com ([217.140.110.172]:51400 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S235277AbhD2OMN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 10:12:13 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7B3C01FB;
        Thu, 29 Apr 2021 07:11:26 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 BC8BC3F73B;
        Thu, 29 Apr 2021 07:11:25 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v3] configure: arm: Replace --vmm with --target
Date: Thu, 29 Apr 2021 15:12:04 +0100
Message-Id: <20210429141204.51848-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The --vmm configure option was added to distinguish between the two virtual
machine managers that kvm-unit-tests supports for the arm and arm64
architectures, qemu or kvmtool. There are plans to make kvm-unit-tests work
as an EFI app, which will require changes to the way tests are compiled.
Instead of adding a new configure option specifically for EFI and have it
coexist with --vmm, or overloading the semantics of the existing --vmm
option, let's replace --vmm with the more generic name --target.

Since --target is only valid for arm and arm64, reject the option when it's
specified for another architecture, which is how --vmm should have behaved
from the start.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Changes in v3:

* Using --target for any architecture other than arm and arm64 generates an
  error.
* Don't generate the TARGET variable in config.mak for other architectures.
* Cosmetic changes to the commit message.

Changes in v2:

* Removed the RFC tag and cover letter.
* Removed --vmm entirely.

 configure | 32 +++++++++++++++++++++++---------
 1 file changed, 23 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: VMX: Fix a typo in comment around handle_vmx_instruction()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12230441
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C506C433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 04:23:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CCD0600CC
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 04:23:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236839AbhD2EXs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 00:23:48 -0400
Received: from mga01.intel.com ([192.55.52.88]:60569 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236230AbhD2EXr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 00:23:47 -0400
IronPort-SDR: 
 2ri/VPHsvYU4K5Ad8I+t5APa4qaPRtlIeJLuy9B4T/Bjqm/4qkUNORLfVQmjpYXiw/08PC+f0g
 45RbrPhjOqmA==
X-IronPort-AV: E=McAfee;i="6200,9189,9968"; a="217643620"
X-IronPort-AV: E=Sophos;i="5.82,258,1613462400";
   d="scan'208";a="217643620"
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 21:22:53 -0700
IronPort-SDR: 
 +46sYziGc1P2unbdLWaf+MGFGQ/RtbJflfMG9BETMwPbjQSQ4cUCxb+G1kmzVJyNMe1QmW3rmm
 N2wl/hJydfHQ==
X-IronPort-AV: E=Sophos;i="5.82,258,1613462400";
   d="scan'208";a="393732622"
Received: from savora-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.209.50.252])
  by fmsmga007-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 21:22:52 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Kai Huang <kai.huang@intel.com>
Subject: [PATCH] KVM: VMX: Fix a typo in comment around
 handle_vmx_instruction()
Date: Thu, 29 Apr 2021 16:22:37 +1200
Message-Id: <20210429042237.51280-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is nested_vmx_hardware_setup() which overwrites VMX instruction VM
exits handlers, but not nested_vmx_setup().  Fix the typo in comment.

Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/2] KVM: x86: Support write protect gfn with min_level
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12230371
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D0528C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 03:41:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4B76610A0
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 03:41:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236938AbhD2DmY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 28 Apr 2021 23:42:24 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:17823 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230072AbhD2DmW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Apr 2021 23:42:22 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4FW1Sm6l62zBtQm;
        Thu, 29 Apr 2021 11:39:04 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Thu, 29 Apr 2021 11:41:26 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Ben Gardon <bgardon@google.com>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v3 1/2] KVM: x86: Support write protect gfn with min_level
Date: Thu, 29 Apr 2021 11:41:14 +0800
Message-ID: <20210429034115.35560-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210429034115.35560-1-zhukeqian1@huawei.com>
References: <20210429034115.35560-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Under some circumstances, we just need to write protect large page
gfn. This gets prepared for write protecting large page lazily during
dirty log tracking.

None function and performance change expected.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/x86/kvm/mmu/mmu.c          |  9 +++++----
 arch/x86/kvm/mmu/mmu_internal.h |  3 ++-
 arch/x86/kvm/mmu/page_track.c   |  2 +-
 arch/x86/kvm/mmu/tdp_mmu.c      | 16 ++++++++++++----
 arch/x86/kvm/mmu/tdp_mmu.h      |  3 ++-
 5 files changed, 22 insertions(+), 11 deletions(-)

```
#### [PATCH v3 1/2] KVM: x86: add MSR_KVM_MIGRATION_CONTROL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12230979
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F074FC433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 10:47:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF9B061466
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 10:47:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240526AbhD2KsD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 06:48:03 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60132 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240469AbhD2KsB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Apr 2021 06:48:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1619693235;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=y/PX0WeAlS70FLjOp8WzYfhsjXzW9oamybcuRYPYrhU=;
        b=Ru+q0BKKh8rZ7T0KXZmlswktZIW1foO2NSptF5/woiwf/ieRiFl8LCDo5wsi1AqTLV3CZp
        mVwBNp5WPJBTw8XItya7YM0Q2Vm2iju3a97tYfFwPaMhESkUUY9PlYA51ZmKtD+S/Es88d
        Sy0U75NL3KfYuzeA68cnnTKMXywnaU8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-573-XOGKQh5NOmmNqPfjtR2TVw-1; Thu, 29 Apr 2021 06:47:11 -0400
X-MC-Unique: XOGKQh5NOmmNqPfjtR2TVw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A47938042A1;
        Thu, 29 Apr 2021 10:47:09 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0357F4EC68;
        Thu, 29 Apr 2021 10:47:08 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: srutherford@google.com, seanjc@google.com, joro@8bytes.org,
        brijesh.singh@amd.com, thomas.lendacky@amd.com,
        ashish.kalra@amd.com
Subject: [PATCH v3 1/2] KVM: x86: add MSR_KVM_MIGRATION_CONTROL
Date: Thu, 29 Apr 2021 06:47:06 -0400
Message-Id: <20210429104707.203055-2-pbonzini@redhat.com>
In-Reply-To: <20210429104707.203055-1-pbonzini@redhat.com>
References: <20210429104707.203055-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a new MSR that can be used to communicate whether the page
encryption status bitmap is up to date and therefore whether live
migration of an encrypted guest is possible.

The MSR should be processed by userspace if it is going to live
migrate the guest; the default implementation does nothing.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     |  3 +++
 Documentation/virt/kvm/msr.rst       |  9 +++++++++
 arch/x86/include/asm/kvm-x86-ops.h   |  1 +
 arch/x86/include/asm/kvm_host.h      |  1 +
 arch/x86/include/uapi/asm/kvm_para.h |  4 ++++
 arch/x86/kvm/cpuid.c                 |  3 ++-
 arch/x86/kvm/svm/svm.c               |  1 +
 arch/x86/kvm/vmx/vmx.c               |  7 +++++++
 arch/x86/kvm/x86.c                   | 14 ++++++++++++++
 9 files changed, 42 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86/mmu: Avoid unnecessary page table allocation in kvm_tdp_mmu_map()
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12230423
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA9E7C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 04:12:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC9BD61405
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 04:12:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237239AbhD2ENX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 00:13:23 -0400
Received: from mga01.intel.com ([192.55.52.88]:59903 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233053AbhD2ENX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 00:13:23 -0400
IronPort-SDR: 
 E7qnCvHrzfKsfoVVNVjl9Pa09FL98WwfkRrp+p8oXISMB3kTBscycSWn6BAgyOHdn58d2EnTgD
 1zh91BHKGeyg==
X-IronPort-AV: E=McAfee;i="6200,9189,9968"; a="217641754"
X-IronPort-AV: E=Sophos;i="5.82,258,1613462400";
   d="scan'208";a="217641754"
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 21:12:37 -0700
IronPort-SDR: 
 R6JlBqBXNxjXKXkVDgj2NAGbgnKw9sqHCl5eOC3IxqEqi/5e3F1fPQbMHjU876lRlfXkQn1g+y
 z01Dr+f563Cg==
X-IronPort-AV: E=Sophos;i="5.82,258,1613462400";
   d="scan'208";a="393727468"
Received: from savora-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.209.50.252])
  by fmsmga007-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 Apr 2021 21:12:35 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, bgardon@google.com, seanjc@google.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Kai Huang <kai.huang@intel.com>
Subject: [PATCH] KVM: x86/mmu: Avoid unnecessary page table allocation in
 kvm_tdp_mmu_map()
Date: Thu, 29 Apr 2021 16:12:26 +1200
Message-Id: <20210429041226.50279-1-kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In kvm_tdp_mmu_map(), while iterating TDP MMU page table entries, it is
possible SPTE has already been frozen by another thread but the frozen
is not done yet, for instance, when another thread is still in middle of
zapping large page.  In this case, the !is_shadow_present_pte() check
for old SPTE in tdp_mmu_for_each_pte() may hit true, and in this case
allocating new page table is unnecessary since tdp_mmu_set_spte_atomic()
later will return false and page table will need to be freed.  Add
is_removed_spte() check before allocating new page table to avoid this.

Signed-off-by: Kai Huang <kai.huang@intel.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v2 1/7] KVM: x86/mmu: Track if shadow MMU activeFrom: Ben Gardon <bgardon@google.com>
##### From: Ben Gardon <bgardon@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12231955
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id B35C2C433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 21:18:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A5F661445
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 21:18:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237327AbhD2VTk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 17:19:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46600 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236695AbhD2VTh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 17:19:37 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5FBDFC06138C
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 14:18:50 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 p8-20020a05622a0488b02901bab8dfa0c5so8198046qtx.1
        for <kvm@vger.kernel.org>; Thu, 29 Apr 2021 14:18:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=1wV27xnqMavGvIltGDlIu2K+7OVnrSqNChCOIi4TNS4=;
        b=jvknsd1iliMtr4R8A/dMkmpsg9lN29BvOtTtwdjUo3Pa2giCRJxUwhmEV6cDaxID4L
         /h+UxqoKiAa4UDtUIQhN8YogWmlGs4GTmkDd3f52tHXv9mHOHHcDMBEWc2QzfuAztd6i
         N5uO1J8zMpM8hHsI22gb5JIRYENVMalPPKejZJ+Zmxg+2L5N2kq+namxp0woSkyLY1KI
         vseeOyb9NmfVoW1k2dqo8MOXSgBBDGlnoE9j/GsZ8XD9yVKShb9uk9mEL1cHKLq6Ieoj
         Wkxw8LcorWTx0weBpHFHeD+6vxlNe94YZzcUVi355ABkpBrl7xxqP9gAfbxLzoy24HUj
         i/Vg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=1wV27xnqMavGvIltGDlIu2K+7OVnrSqNChCOIi4TNS4=;
        b=XxNY7o1zrgSeTO6aYLbEFqu9ETOf3bMuYW+dY5RCJW5cacbdbMDggq22rUO/mxAnW2
         xCuq0tBaYYHxg5CZGH9TR+qLePJT7AOoSj9JiMRZ1ExFnf0Yqc0Oq1Ac73vFmhmD1iCr
         qMRF1H8T7b8AmLVnIBm6+XOb3V/YBeyDv1KQGxPFkhxmUKFEMzK2AVuULN8ue/tbS+Uy
         98wsvn3H6lPPV9yG83k359oCGTLJHjFIVsZb+8RXqEgpo/nOfJZ6tioZng6P1SJqn9v4
         D+uWOjXMxah/w76zUw4IA4uNtvgWy8rbJ19av4wlZ1rlrKS9OZdY90DU0uNDYXttOr0h
         TEpQ==
X-Gm-Message-State: AOAM530Bzjq5Pdo4+2iebgYewDdOi8FcSVZ6iABJodsDhWtYjyyLgotu
        XTK3wPZQn0SwC00hwGo7e09sM2ZOh0HY
X-Google-Smtp-Source: 
 ABdhPJyY7Bg2F/dVUQmrpChxTdjTp6lJBGHFvWu78QERBqCawGmLq2EKPh/Rlez8bBdb3LyylM8lYUZYlKwO
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:1a18:9719:a02:56fb])
 (user=bgardon job=sendgmr) by 2002:a0c:ba1a:: with SMTP id
 w26mr2046434qvf.27.1619731129504; Thu, 29 Apr 2021 14:18:49 -0700 (PDT)
Date: Thu, 29 Apr 2021 14:18:27 -0700
In-Reply-To: <20210429211833.3361994-1-bgardon@google.com>
Message-Id: <20210429211833.3361994-2-bgardon@google.com>
Mime-Version: 1.0
References: <20210429211833.3361994-1-bgardon@google.com>
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH v2 1/7] KVM: x86/mmu: Track if shadow MMU active
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a field to each VM to track if the shadow / legacy MMU is actually
in use. If the shadow MMU is not in use, then that knowledge opens the
door to other optimizations which will be added in future patches.

Signed-off-by: Ben Gardon <bgardon@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu/mmu.c          | 10 +++++++++-
 arch/x86/kvm/mmu/mmu_internal.h |  2 ++
 arch/x86/kvm/mmu/tdp_mmu.c      |  6 ++++--
 arch/x86/kvm/mmu/tdp_mmu.h      |  4 ++--
 5 files changed, 19 insertions(+), 5 deletions(-)

```
#### [RFC PATCH] kvm/x86: Fix 'lpages' kvm stat for TDM MMUThread-Topic: Subject: [RFC PATCH] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
##### From: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>
X-Patchwork-Id: 12231257
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,PDS_BAD_THREAD_QP_64,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95CD9C433ED
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 12:46:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 680FC613FF
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 12:46:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237279AbhD2Mrk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 08:47:40 -0400
Received: from smtp-fw-4101.amazon.com ([72.21.198.25]:40277 "EHLO
        smtp-fw-4101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237050AbhD2Mrj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 08:47:39 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1619700413; x=1651236413;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=HOS0BVs2Yph8gEQGh2vvpwgdubvvvKzjdHeFOkb2D/I=;
  b=A31/jhxs1DOOGYEGgYL6aI6N74XMUYSMxdgJYoA9uNHjU7tpjDT4p/gg
   Jb45SIsM9CpnfeA39rC0HPw/rF6odQmwmNO2e5JEtF97YFj66QhnlB7HS
   iv8foRs/ICGTnr+haC0KfqE9RrShC3aYkxzJRefQS7S3/1gpwwKrcPO0O
   M=;
X-IronPort-AV: E=Sophos;i="5.82,259,1613433600";
   d="scan'208";a="104730971"
Received: from iad12-co-svc-p1-lb1-vlan3.amazon.com (HELO
 email-inbound-relay-1d-37fd6b3d.us-east-1.amazon.com) ([10.43.8.6])
  by smtp-border-fw-4101.iad4.amazon.com with ESMTP;
 29 Apr 2021 12:46:52 +0000
Received: from EX13D49EUA003.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1d-37fd6b3d.us-east-1.amazon.com (Postfix) with
 ESMTPS id 8AB4C2805E6;
        Thu, 29 Apr 2021 12:46:51 +0000 (UTC)
Received: from EX13D09EUA004.ant.amazon.com (10.43.165.157) by
 EX13D49EUA003.ant.amazon.com (10.43.165.222) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Thu, 29 Apr 2021 12:46:50 +0000
Received: from EX13D09EUA004.ant.amazon.com ([10.43.165.157]) by
 EX13D09EUA004.ant.amazon.com ([10.43.165.157]) with mapi id 15.00.1497.015;
 Thu, 29 Apr 2021 12:46:50 +0000
From: "Shahin, Md Shahadat Hossain" <shahinmd@amazon.de>
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
CC: "Szczepanek, Bartosz" <bsz@amazon.de>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "seanjc@google.com" <seanjc@google.com>,
        "bgardon@google.com" <bgardon@google.com>
Subject: Subject: [RFC PATCH] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
Thread-Topic: Subject: [RFC PATCH] kvm/x86: Fix 'lpages' kvm stat for TDM MMU
Thread-Index: AQHXPPVj2bcPJ2lBOUWRavYwOTNimg==
Date: Thu, 29 Apr 2021 12:46:50 +0000
Message-ID: <1619700409955.15104@amazon.de>
Accept-Language: en-GB, en-US
Content-Language: en-GB
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-ms-exchange-transport-fromentityheader: Hosted
x-originating-ip: [10.43.160.81]
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Large pages not being created properly may result in increased memory
access time. The 'lpages' kvm stat used to keep track of the current
number of large pages in the system, but with TDP MMU enabled the stat
is not showing the correct number.

This patch extends the lpages counter to cover the TDP case.

Signed-off-by: Md Shahadat Hossain Shahin <shahinmd@amazon.de>
Cc: Bartosz Szczepanek <bsz@amazon.de>
---
 arch/x86/kvm/mmu/tdp_mmu.c | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v2] vfio/mdev: remove unnecessary NULL check in mbochs_create()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 12230903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_SANE_1 autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1E8E3C433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 09:53:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DBD1B61462
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 09:53:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237417AbhD2Jy0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 05:54:26 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:45636 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231543AbhD2JyZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 05:54:25 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13T9XrGH131973;
        Thu, 29 Apr 2021 09:53:35 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2020-01-29;
 bh=zMqah14+OFnOSJ6UHqaQtZjQ2w6PI4tm2fnCNKK/fi0=;
 b=L5aJa2VqnQdAXIeIR4rtKZyFAcYavk8z8YWn2ggFvCR1cLxXOVyHE6cWJ/K2G64KBRBD
 tcVlDcrAZBV5ewDDRak5TaBGM4NCnlDacWGHTCL/xia6vgNKOOjbH9pWqDudRfUK/rSK
 2d5xef05cNs09OHeKIoiAaUA4zsjdqC27m+v7ANII/MAR2l08CVXV76RifYdrOmUBmmo
 ZFt34YoPA+B7bCtSFUk0ETxkuU0w2OizjNi3n9yG28sffJUC9S+9VYzfp8jHWQ6MTVHS
 tv7DPLFmQyOc9Qx+MpLG2eeJBdm7a+L+vpc6R37WLaqBV81RoyRo2J/65mwZRSv/0ofy 9Q==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 385aeq3spg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Apr 2021 09:53:35 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13T9UsFm180136;
        Thu, 29 Apr 2021 09:53:35 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 3848f0u8ak-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Apr 2021 09:53:34 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 13T9rXB0004611;
        Thu, 29 Apr 2021 09:53:33 GMT
Received: from kadam (/102.36.221.92)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 29 Apr 2021 09:53:33 +0000
Date: Thu, 29 Apr 2021 12:53:27 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Kirti Wankhede <kwankhede@nvidia.com>,
        Jason Gunthorpe <jgg@ziepe.ca>
Cc: Alex Williamson <alex.williamson@redhat.com>, kvm@vger.kernel.org,
        kernel-janitors@vger.kernel.org
Subject: [PATCH v2] vfio/mdev: remove unnecessary NULL check in
 mbochs_create()
Message-ID: <20210429095327.GY1981@kadam>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
User-Agent: Mutt/1.9.4 (2018-02-28)
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9968
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 phishscore=0 spamscore=0
 mlxlogscore=999 malwarescore=0 bulkscore=0 adultscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104290067
X-Proofpoint-ORIG-GUID: cJHDy9ASvbS2L6ec5T_3l35qXnZXxmI1
X-Proofpoint-GUID: cJHDy9ASvbS2L6ec5T_3l35qXnZXxmI1
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9968
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 impostorscore=0
 phishscore=0 spamscore=0 bulkscore=0 mlxscore=0 lowpriorityscore=0
 clxscore=1015 suspectscore=0 malwarescore=0 mlxlogscore=999
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104060000 definitions=main-2104290067
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Originally "type" could be NULL and these checks were required, but we
recently changed how "type" is assigned and that's no longer the case.
Now "type" points to an element in the middle of a non-NULL array.

Removing the checks does not affect runtime at all, but it makes the
code a little bit simpler to read.

Fixes: 3d3a360e570616 ("vfio/mbochs: Use mdev_get_type_group_id()")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
---
Update the commit message

 samples/vfio-mdev/mbochs.c | 2 --
 samples/vfio-mdev/mdpy.c | 3 +--
 2 files changed, 1 insertion(+), 4 deletions(-)

```
#### [PATCH v3] target/i386/sev: add support to query the attestation report
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Brijesh Singh <brijesh.singh@amd.com>
X-Patchwork-Id: 12231609
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7562FC433B4
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 17:07:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F4C1613CC
	for <kvm@archiver.kernel.org>; Thu, 29 Apr 2021 17:07:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235685AbhD2RIf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Apr 2021 13:08:35 -0400
Received: from mail-dm6nam12on2051.outbound.protection.outlook.com
 ([40.107.243.51]:51585
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233302AbhD2RIe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Apr 2021 13:08:34 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=KUa7q21ojmrvWnK+Kd1vzkYrxaJR41dXsqNM6ymRTJyEd9F9uccPn1+A90VOGC3/uNV1gTX92npVhEyhOoryT9Yax3G9xxpu6C17xrjFBIFgnFxSrpf3VX30mBD/RAJjuMBQn65uA+a9JOWlSKjBT6zanXn6Q4wBDErh+ru4pZgmasm42w546xd0E6CI9EygfjVhOYsmPktrE6fW31i1dEaRD5HDJf/xZWk1BuhovVi36rgKmGYvDeJxZ1ERTVI4UQLHqgNdGz+VRwF+9uD9N3rQuuk4j+PhUD8l+EY7WfFgyIbqenFv07RN49JTdbDo3xpogcNKZxhL1D+O0Zqrtg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MfP+hXLtn/ZK40u/FpMl1bjkQsH/6S/F1gjNY2ZUes0=;
 b=jtWlU0piZw0xFUB89aBWtVrxCfRoyLdnWr5eDFaGbtJj4ntuUG6vBINBAzjwt9XDQw+zqqrBKFMrLntSFYitYOqhzkPHfbQmlG0uZ8EYyqvFnaOk+nNtqbKO/5cUF/4pCoQoUkSmv/6+86EB6pRUmHfYZhyH9vtX9ZVmg5clv+TeASEf2+mulaDAY4z7ZSUMiByS3GWzc+l8Fnvpk6wtuHS3hzik/s7NNP8GBqHKzsjJDrOefLp4df6WITzzvlPZ0fux7FIYw9oRPCaKS5cM4QB9jtp87Qa9nVrNnu1couHQMjRrS78iiQfbxn+ycECVNbWSkPaxooJUg5AVN6FxwQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=MfP+hXLtn/ZK40u/FpMl1bjkQsH/6S/F1gjNY2ZUes0=;
 b=qB5QSMa8HAtCiLn4F9UzYdMGs/tJ4axlfbsWygZDzeLDX7TK+3dIH47l07TD1jzO3RbvG53793B8n/w7b/du2lCNNnKkDObLkbUjK+e+QheXlO7CrGG8rZ7YZSmti7gjMS1oOjPlMX+9mEF+FIHPkJzrH3rzVEg5eNPYeFYH9uI=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2718.namprd12.prod.outlook.com (2603:10b6:805:6f::22)
 by SN6PR12MB4671.namprd12.prod.outlook.com (2603:10b6:805:e::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4065.25; Thu, 29 Apr
 2021 17:07:44 +0000
Received: from SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94]) by SN6PR12MB2718.namprd12.prod.outlook.com
 ([fe80::9898:5b48:a062:db94%6]) with mapi id 15.20.4065.027; Thu, 29 Apr 2021
 17:07:44 +0000
From: Brijesh Singh <brijesh.singh@amd.com>
To: qemu-devel@nongnu.org
Cc: armbru@redhat.com, dgilbert@redhat.com,
        Brijesh Singh <brijesh.singh@amd.com>,
        James Bottomley <jejb@linux.ibm.com>,
        Tom Lendacky <Thomas.Lendacky@amd.com>,
        Eric Blake <eblake@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH v3] target/i386/sev: add support to query the attestation
 report
Date: Thu, 29 Apr 2021 12:07:28 -0500
Message-Id: <20210429170728.24322-1-brijesh.singh@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0201CA0037.namprd02.prod.outlook.com
 (2603:10b6:803:2e::23) To SN6PR12MB2718.namprd12.prod.outlook.com
 (2603:10b6:805:6f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from sbrijesh-desktop.amd.com (165.204.77.1) by
 SN4PR0201CA0037.namprd02.prod.outlook.com (2603:10b6:803:2e::23) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25 via Frontend
 Transport; Thu, 29 Apr 2021 17:07:44 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 9f875787-9f37-42e1-d097-08d90b314e30
X-MS-TrafficTypeDiagnostic: SN6PR12MB4671:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB4671AFBCE2E283AFC18BFA2CE55F9@SN6PR12MB4671.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1265;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 L7QRo26GgahcZoERItkFtWjzwBIBcbrugA0MYlWEiEgxPugYPHTHHmAmS6WHmVIAUGogyeAJRFVP3ioqbkPY7huxhVwqbCjcMpnvm0hPhp/l6BZ1k9qSoB+087/vn210LkkTOxFtftDGsjbsew2ayXYyZuh8J5/UQyQge7kIruQYplaF5stYJDIWgq0KtMqxQwxnGD4FYa4zj3Hgkqk1rX1mNu4Tb03wlb0fSVApEPI3PlBOrs+5B6HAZdkSFDUfw+/1+11Qkb0yIb88+owUYYMetEBQ8ybPFveC38vCVIw6bKJrdeTlddXcoM6M7NWOahaU2A1OueCWzpEsj35T/5nedjgLqjyC33uNLFba08fKw/0VsDeREnsnawZSYOHkV6yUbgvGdB9hJPTFxQpaZSJ3x+UABVnNIBD0HyG3OBN+Og4QlP11ZFVOhflHaPKXYDxMrg9/3VtJvQreN6O1jdluCMxtdxtmY484ERT6YRSkX99g7eKwKUMpFYKXOUisqkADRDrW7NpUaSuSAsHXMKHASV0teNlb18sFKonHnh5ISF0qU6c57MYqH1hZgSOE76OlWtC2YNu5rNeTML0chzU9mjYM3SnS7xk7C2RGKSx0qi+FbZtSwLwhuXJEV9ji5GP6/i7/b9FvsscE0d69+SVJT8DYD/65ewcPQ6iIRtk=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2718.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(396003)(376002)(366004)(39860400002)(346002)(66946007)(1076003)(26005)(7696005)(186003)(478600001)(38350700002)(6666004)(44832011)(16526019)(5660300002)(6486002)(66476007)(52116002)(2616005)(8676002)(8936002)(38100700002)(54906003)(86362001)(316002)(6916009)(66556008)(36756003)(2906002)(956004)(4326008)(83380400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 xRYGD18xvvub3t57nLgPBYNPJzi5DkIm54xeE7iUYRHiB2CeEBG7n8J1NSlugUvVxoZaqf57Qzubbxn5xkV2pfJxghKS9IqfOJgeZjWbEpyFlbjO3R0lqgIDVH7fTd2getdb9Jsm6/dukX9hpFZccOQxOuZtLcM0QnpkzOjBqFGyhaWnD/biieIWAcEoroL6zZ6kCSNrcOeSU5GuTAXMlxU6bxVop8pvcK8KYT8z2zj5yhpE2hfUh/uzhKwEGFWN00Hh6Ij1rNFVb6eWrdcoxdsrgrF9DzXDDf7Y0BCYnOPQYH0IPd2OBXjHCUqXkvXugXC49kNchBpcbU0faXSjUXNaceLP/7c6FXEZK/RNrJAONejSxWbaQtLPbjeQDgYrCtYlO/JimXH5FbGR//MuzfAj0qM3aoQwXvvLP1etU4uypSYCtpNxKIMWCl2YBpZn6mOiuXRL52Hhj5bjQ0tz88dykX978XPS7WnesNi4M3YNcYBK3+zRdueU5OUcU4p2MZuoaxbboyl/uN1kH7bvKbk0poWxfhotL/EjJszRLUEhErCUiYkRyxhxirSAYbV5ttaEggU4MkRCY9yf0k22GRLoJSUu9FZJRbBekYPkUZ9FDqap/Lfp5pcD4BE0OAI1XIBNVa4sWtOnv5Awa1pRNPJh1mq/TY9ilmz5OPqdBJg3yOyAoVWanz+PmYN+wtKIMiWkz7lOVK0yubgi5eoSNLfsogwQL9kIBvJjfPgP1X8txLf3hASLS2j7oiLEakQJ9EjnYBvQq6nY0eAMMtU5QmIAzJIL3zjQFkJT5viCkf/hj9oBp03U3scZP7fid4v16usdfzFpt2KUZpBub68NgPbY6s1RqDj4XV4drKUscVhAU1ZyrC8yVhTqwtyAc6fnUthxWr5g4nKw/b6hBnjsXOHNFWlt+62zNWbGYl0gyyw0FJLnCEo6q7iDbrSdrfT3x6Xz0xcKWS3s+8j7/IwDddddYJXh84FJwlgCZYVypWG15t8l/AXNUQoYNRJOrINyIaUcIAiFZreVUjB0fgQ7vStHwwFP36anethZjXjsO9FHKw0qChOC1NHJ28biUZeZzw6dK/uudD6oYOcZZI8+GSjoTczzuVu48s3DM0HvTLB5gXpVMcVLtYvtP08fwEjuyxxL9RrOx1uD223MelF/qCrWT7JZYbFMoJ08esyBAMzyADAPhLXSbpXGwK3EUPQdc9Mo+AnLXchAge5zPjkYRRFce0H78tiiK7cfKVF1ceNO6eZhJ63CDGei6FmXy8e7UYj44tQVjSPw5/WvsH4tfxJeWOzSLJpOPRmCVTYA9w9VeBkbsd/vtIATpi6iob9M
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9f875787-9f37-42e1-d097-08d90b314e30
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2718.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 29 Apr 2021 17:07:44.3770
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 prj/lKLvCh+7ZVsL+6kengo6Z9tBreWUHRUCa+SgPHgS/oGivMf0gJAjEmwevIio5N/e/Mg47CaFBcRnpGSIwg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB4671
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SEV FW >= 0.23 added a new command that can be used to query the
attestation report containing the SHA-256 digest of the guest memory
and VMSA encrypted with the LAUNCH_UPDATE and sign it with the PEK.

Note, we already have a command (LAUNCH_MEASURE) that can be used to
query the SHA-256 digest of the guest memory encrypted through the
LAUNCH_UPDATE. The main difference between previous and this command
is that the report is signed with the PEK and unlike the LAUNCH_MEASURE
command the ATTESATION_REPORT command can be called while the guest
is running.

Add a QMP interface "query-sev-attestation-report" that can be used
to get the report encoded in base64.

Cc: James Bottomley <jejb@linux.ibm.com>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
Cc: Eric Blake <eblake@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org
Reviewed-by: James Bottomley <jejb@linux.ibm.com>
Tested-by: James Bottomley <jejb@linux.ibm.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
v3:
  * free the buffer in error path.

v2:
  * add trace event.
  * fix the goto to return NULL on failure.
  * make the mnonce as a base64 encoded string

 linux-headers/linux/kvm.h |  8 +++++
 qapi/misc-target.json     | 38 ++++++++++++++++++++++
 target/i386/monitor.c     |  6 ++++
 target/i386/sev-stub.c    |  7 ++++
 target/i386/sev.c         | 67 +++++++++++++++++++++++++++++++++++++++
 target/i386/sev_i386.h    |  2 ++
 target/i386/trace-events  |  1 +
 7 files changed, 129 insertions(+)

```
