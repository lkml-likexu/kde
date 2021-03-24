#### [PATCH v3 01/14] vfio: Remove extra put/gets around vfio_device->group
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12158681
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4A2D3C433E3
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:16:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 137B2619C8
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:16:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233134AbhCWQPf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 12:15:35 -0400
Received: from mail-mw2nam10on2048.outbound.protection.outlook.com
 ([40.107.94.48]:9569
        "EHLO NAM10-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S233132AbhCWQPP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 12:15:15 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ItPLBrK3bn1IT4x00vSBt5zNbkjHHyKtZVf7hRvB+utrkHsRJxZcayLSkqUt5qPO58rM2di0BROtXTUI2RQ6o791m2ujLXytp84rrn796VtNJ1R5kA+RjAt4pkUoqGe6CCHqffQu2xLWgk44UeqInzoC4XWPj+9ozV8uU8cDAanJgPIOdBDnF8W33JeoF68zti7kLsEc3CH0FzAY+hWEDJL201uPy+l8uc1rSCP+vx7tPDSEXWXvCSPdtWeNeSkkMbsllObPhw7sqPz0Kyx4Dt9Ym3PDXnKxu+HudPB3eJsQF3Th9+zry1Zm4DinCNgBsRYwSBTbsBKc2bPtiZbzoQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=N0iRN/VSy2CWTtwWkvSUA0AnLu+cLQXXHj8mJqZo+SY=;
 b=VIO7HS6L9vzl4Oj0IRi0+7yLWmw8iUH49MrOPqwvthqCnqjnLc2Pl1pFI1OwvfYlWLWbX8qhOVuF3A514MMhbkQ1mfKdbjah0sBMjEbOlVsn/7W1EOCT266SbFMXvhJosihKyLwtfH6+qHLYtTawySbj4OijqX2B/YzQI3XWpYtGCiVk6rTEArKg9POBKREuPi/mxADM/N1TLkGscqrDKDchNVk93h+QZAqeLmpgcVTmCKtzvMrAR0xkyAB9uNnoxL2Z+vNXHnZGsWUJgx4ESU77kO5/a+HM1stLC55imoAHw6h5+aSSVpZvpYMJmcWxce6Hm2vPDqnjzL2gWxfTjg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=N0iRN/VSy2CWTtwWkvSUA0AnLu+cLQXXHj8mJqZo+SY=;
 b=LKdGbLqhv7pOwf4MA6ma2NeAYFa1qPgnLj+VAwfMgDouqrz0N5Tf1LthzADk+LoMaXL2nTootv6Px1RL4Tm3jk+3WeFsaWTXAh2UyqmrmHJG4iLGkGOSGrYTudHRmMf1JL2YzJ6m1TN6GK9n2FC/C4wTEKmfllsVePIjFn0PHTXpE1fyvCIvUvtcZ5jP4O8KDWBeY6wWYLa2j6LUc5SHB6iTgwG/0IZoIdGemBq28DLdHL4TPoe7ZV9dTsBY+mi3QtdV4zwsW/kFXgIlNpSpxjazyq/PaLg35qtvjagIRp8dRvWiCpUOM+ntPCbRr8f/57Q8L3C3cgd8VoheQhB7Gw==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR12MB2440.namprd12.prod.outlook.com (2603:10b6:4:b6::39) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3933.32; Tue, 23 Mar
 2021 16:15:08 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3955.027; Tue, 23 Mar 2021
 16:15:08 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>, kvm@vger.kernel.org
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Daniel Vetter <daniel@ffwll.ch>,
        Eric Auger <eric.auger@redhat.com>,
        Christoph Hellwig <hch@lst.de>,
        Kevin Tian <kevin.tian@intel.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v3 01/14] vfio: Remove extra put/gets around
 vfio_device->group
Date: Tue, 23 Mar 2021 13:14:53 -0300
Message-Id: <1-v3-225de1400dfc+4e074-vfio1_jgg@nvidia.com>
In-Reply-To: <0-v3-225de1400dfc+4e074-vfio1_jgg@nvidia.com>
References: 
X-Originating-IP: [206.223.160.26]
X-ClientProxiedBy: MN2PR19CA0031.namprd19.prod.outlook.com
 (2603:10b6:208:178::44) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (206.223.160.26) by
 MN2PR19CA0031.namprd19.prod.outlook.com (2603:10b6:208:178::44) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Tue, 23 Mar 2021 16:15:07 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lOjgQ-001aCP-Ae; Tue, 23 Mar 2021 13:15:06 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: cae0e79a-52c2-45b0-c9c7-08d8ee16d376
X-MS-TrafficTypeDiagnostic: DM5PR12MB2440:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB2440F8B43D80340F8302C415C2649@DM5PR12MB2440.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5797;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 3/li3MepplDXlga7QVIvMuQBVwImJl8aRKMcgD1Q4RzyO/249jcZuJv7ZXl8Bi59XM5LFDtEC12HEA5NzBzNjCoTNoRd2DYNvPUHNNbrPCgnTyW75f9X7HuQ9ovtC0tS8oqsl1x3vyuXcg+4m6waPMdUWgshPSuGaY0NoQgfRPDuFK4qawY4nTvArlMvZrAwpw7L/2HjmBBYqonZouGt6LlEzbyE30/+1TZqxieCm2pC5qDfq9Lt4nnd1GdF0fvJ8zVMrLLbKyfRIAaJsFBzpbCbRflmcntIjk1LTFIRnPHzROfKeZ2cgilQmQm+xMgsiXGaZdH44EUORCBNXAg2o0xrA8/A49wf2I4CtFL8U4WDHMY5Qq66AvqAU1UE41OwCZmaUg1W1szBWNyU+ZxIhYIx2q4eYQs+4mVPTQMKxqErLTL4i39T6iKh3RFHAbrLj6lif9zkmaotLawJDEs5HQ6lb6iCDOU9n2EfDK1GtLbM7zczWAtC782V/6bmn1zVvEd63D7p+2DKyzsgiczqsX2ikKmRkvJajXz1+L88lbbINikmTEvjsEHvpvfbpRbkGqcH8gUMtvKrfvNaZBgSngBu+20kVR18ro6SfRTdosoyjStb0goBEaPn/ySt2QLSUF8BjFujnF0VZROFhJEAKtX48BKOn1tVPuxJclM4p2+oryWJxCecKMh9IjnuamIr
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(396003)(376002)(39860400002)(136003)(66476007)(66556008)(186003)(36756003)(6666004)(86362001)(38100700001)(66946007)(4326008)(107886003)(8936002)(54906003)(9746002)(26005)(478600001)(426003)(8676002)(9786002)(83380400001)(2906002)(316002)(5660300002)(2616005)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 DdOGWTl+2osOuO2jpsAZSJQNEZCxvS++1CCeDDwolmtlBMY2hgjREpuyH39Pe81ICZTu6lPim4TrBjs8vvUbVmSsdAV9b/E302nR1yqc8XkIsWe91hODMX7OMDXrxmsDuUwf9ObNkHXRU+Ikjk1/pa/pJajznIrRUIWIruIQtonv0Ydg6MucA1XZCCNxnct4fZBuzOH0s2SO8w7kmTmdvmrMwIxwb0mDjIWw2qUpyskR1Ru00Xhr6JfcSYGWcHlhRiuyy/z0Zc/73T7Y29G/seEw4hpsyXy7WE7h5GfIEgod/h+4Z9LpXDMFswdV0zol7hv40Mvw9mbUaUr5SlZywQ4UIyQLjhVntYov/RuxWnhsXfpDd5b9s4KMNSOQ/7zxH92SmLWDqugDVtod2dCaaPIXY0ClDTWByxBZ/g+yroTOv5xI9tcXmo//PTicuwoN9H7nuuLZTv7F/6wYEpHaKbGL6ioO7YtO76DdSYAdXJJWKTpluJL+Eg6gbTDeq232Gxrw51FGwZYwmCN0Y5jpFJXWnyViTD2NMY49O31H/PUvsl4pfu1E15UUCnFSzTDK6hEflXuGrOmm58n0SCj94R3HEBAMJ/vcHn6gMLT7QDGj5evrB1/ShxhnArLnGV6PxCV1Bl2nqQfnESicFBMHYisG4J4lQBOhvZAP8il75f7teBoDYHHXfohsHkSlTs7wjtIL8QJ2aD4LnkKKcc6HuPu6x9cN+wrfF+q6jCC3h+K1hKLRiw99mnc3SxtoQqJ3JcQ0pkjZqbcKJS8rdryEDK7UkXYPOW3iiZxGe3V/5qF3jWkKbQIxGZTZbjYz4JBuAkJDWeYohrV3KS+04vaq1HyDdv0Fw7ctxFSPSIzLPmXDq1JLziP52HJx94hNTqTQbi5fDT41cAC6GVRAjjDNisd9RD68M5RIVQxFol85VQGNAA8iCEzNR8W2Zi1yNL93fmt3LJT8O5cKnDlJtEvYb7wtFpjwokdhwyclTk9NXPFfZn44Sn3vCJmnB+TLBSmtgTuuzdUi24T8rruxhVhyiOhhUsHQTJjudMVDL21ZnsMarSPqjDRFNeinUl6YSKXQcVa0bSA3WU1t3Dx6Im2BmBpzjBWJO8q6qETq6bDpY4M8q4YmjAqkvZkWknwyCdWZy1S+JynYbTANlM8SFnw8xaFBLutKoduD+ljH7iJoDPt7j9Wi6yxqvp9TMe+cVv8soOf4Z6OhOgl8NLRogNKjPqbLpBswcKLvmzVieYcYXXHJ6SythdzLYp4rAfVcuUfH2hqsd9seQE6GVkSLwnP8Hp/+pm/Uk0Ip62LFXq9/jG3AMvYArZuH5KLtMO+gEDep
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 cae0e79a-52c2-45b0-c9c7-08d8ee16d376
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 16:15:08.0731
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 3Kl3xHtr1LhdumUQ/z6aXi5XXReij1IF0Nbe12Go8+uYotfh92SO/oXiYLEaAfhE
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB2440
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_device->group value has a get obtained during
vfio_add_group_dev() which gets moved from the stack to vfio_device->group
in vfio_group_create_device().

The reference remains until we reach the end of vfio_del_group_dev() when
it is put back.

Thus anything that already has a kref on the vfio_device is guaranteed a
valid group pointer. Remove all the extra reference traffic.

It is tricky to see, but the get at the start of vfio_del_group_dev() is
actually pairing with the put hidden inside vfio_device_put() a few lines
below.

A later patch merges vfio_group_create_device() into vfio_add_group_dev()
which makes the ownership and error flow on the create side easier to
follow.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Kevin Tian <kevin.tian@intel.com>
Reviewed-by: Max Gurtovoy <mgurtovoy@nvidia.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/vfio.c | 21 ++-------------------
 1 file changed, 2 insertions(+), 19 deletions(-)

```
#### [PATCH] KVM: arm64: Fix CPU interface MMIO compatibility detection
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12158737
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 078C7C433C1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:24:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC33A6198C
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 16:24:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233062AbhCWQXj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 12:23:39 -0400
Received: from mail.kernel.org ([198.145.29.99]:40978 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233150AbhCWQXI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 12:23:08 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4B937619B8;
        Tue, 23 Mar 2021 16:23:08 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lOjoA-003LOd-7E; Tue, 23 Mar 2021 16:23:06 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Cc: Ard Biesheuvel <ardb@kernel.org>, kernel-team@android.com,
        Shameerali Kolothum Thodi
        <shameerali.kolothum.thodi@huawei.com>
Subject: [PATCH] KVM: arm64: Fix CPU interface MMIO compatibility detection
Date: Tue, 23 Mar 2021 16:23:01 +0000
Message-Id: <20210323162301.2049595-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, ardb@kernel.org,
 kernel-team@android.com, shameerali.kolothum.thodi@huawei.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In order to detect whether a GICv3 CPU interface is MMIO capable,
we switch ICC_SRE_EL1.SRE to 0 and check whether it sticks.

However, this is only possible if *ALL* of the HCR_EL2 interrupt
overrides are set, and the CPU is perfectly allowed to ignore
the write to ICC_SRE_EL1 otherwise. This leads KVM to pretend
that a whole bunch of ARMv8.0 CPUs aren't MMIO-capable, and
breaks VMs that should work correctly otherwise.

Fix this by setting IMO/FMO/IMO before touching ICC_SRE_EL1,
and clear them afterwards. This allows us to reliably detect
the CPU interface capabilities.

Cc: Shameerali Kolothum Thodi <shameerali.kolothum.thodi@huawei.com>
Fixes: 9739f6ef053f ("KVM: arm64: Workaround firmware wrongly advertising GICv2-on-v3 compatibility")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/hyp/vgic-v3-sr.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [RFC PATCH v5 01/10] tools headers: sync headers of asm-generic/hugetlb_encode.h
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12158017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4034EC433E5
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:53:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 11B67619C0
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:53:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231652AbhCWNxF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 09:53:05 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:14852 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231370AbhCWNwq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 09:52:46 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4F4Xnd6Vn4z92yW;
        Tue, 23 Mar 2021 21:50:45 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Tue, 23 Mar 2021 21:52:36 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kselftest@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Ben Gardon <bgardon@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Peter Xu <peterx@redhat.com>, "Ingo Molnar" <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v5 01/10] tools headers: sync headers of
 asm-generic/hugetlb_encode.h
Date: Tue, 23 Mar 2021 21:52:22 +0800
Message-ID: <20210323135231.24948-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210323135231.24948-1-wangyanan55@huawei.com>
References: <20210323135231.24948-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch syncs contents of tools/include/asm-generic/hugetlb_encode.h
and include/uapi/asm-generic/hugetlb_encode.h. Arch powerpc supports 16KB
hugepages and ARM64 supports 32MB/512MB hugepages. The corresponding mmap
flags have already been added in include/uapi/asm-generic/hugetlb_encode.h,
but not tools/include/asm-generic/hugetlb_encode.h.

Cc: Ingo Molnar <mingo@kernel.org>
Cc: Adrian Hunter <adrian.hunter@intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@redhat.com>
Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 tools/include/asm-generic/hugetlb_encode.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH kvm-unit-tests] compiler: Add builtin overflow flag
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12158107
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 90917C433E5
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EF4E619CC
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:59:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232034AbhCWN6y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 09:58:54 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:56863 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229508AbhCWN6I (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Mar 2021 09:58:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616507887;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=XzJmK4D7Fm6Tgm/8V9hEExZ1Vha0jtYTosH2Xs3SWKk=;
        b=GtDjPdJedzf0eAuHY4jyMXAGW1ZIxgGhxALpYy+xiHqcETcOEct5/jIYbPLYKDaSADrnWn
        MlaObSIhdgIPs35yt+GFO5Cs44G6bQ7ZoSSNS3MWtDvjCs2DSh/AAZrB4bIe20j9jawWvg
        polM9GUzKxh93sQW4+jukiELolvbXAk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-443-Zt63J2q_Mk-XBnIVqkCHqw-1; Tue, 23 Mar 2021 09:58:05 -0400
X-MC-Unique: Zt63J2q_Mk-XBnIVqkCHqw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6C5EB1007467
        for <kvm@vger.kernel.org>; Tue, 23 Mar 2021 13:58:04 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 28A9719C45;
        Tue, 23 Mar 2021 13:58:02 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH kvm-unit-tests] compiler: Add builtin overflow flag
Date: Tue, 23 Mar 2021 14:58:01 +0100
Message-Id: <20210323135801.295407-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Checking for overflow can difficult, but doing so may be a good
idea to avoid difficult to debug problems. Compilers that provide
builtins for overflow checking allow the checks to be simple
enough that we can use them more liberally. The idea for this
flag is to wrap a calculation that should have overflow checking,
allowing compilers that support it to give us some extra robustness.
For example,

  #ifdef COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW
      bool overflow = __builtin_mul_overflow(x, y, &z);
      assert(!overflow);
  #else
      /* Older compiler, hopefully we don't overflow... */
      z = x * y;
  #endif

Signed-off-by: Andrew Jones <drjones@redhat.com>
Acked-by: Thomas Huth <thuth@redhat.com>
---
 lib/linux/compiler.h | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [PATCH kvm-unit-tests v2] compiler: Add builtin overflow flag and predicate wrappers
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12158921
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C64D1C433C1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:55:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 797D3619C0
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:55:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231218AbhCWRzH (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 13:55:07 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:52782 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230035AbhCWRyf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Mar 2021 13:54:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616522074;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zRuszIT5rQbqYA0k4j2pUZ/qfqnNj6Z8T7IjpQIB3Ak=;
        b=d3k/erQqEG70aYT3pniYutDLO1J9z4zTlIrqgwYJO8ji4weXavwSV3GkhMePwWFiCBqpob
        /V6Y/pT3oRNzlJOzJCLrTZpLy82/YFgVdQCAOfZBXavhrv3CksY2MantzbP9WXjLME5EOz
        3Edbphc4O8NqpGppmEjbslJCOn9rQ2E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-9-UEOK9XM5MqWMwh_UVp-GKA-1; Tue, 23 Mar 2021 13:54:32 -0400
X-MC-Unique: UEOK9XM5MqWMwh_UVp-GKA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5F09D87A83F
        for <kvm@vger.kernel.org>; Tue, 23 Mar 2021 17:54:31 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4A9325DEAD;
        Tue, 23 Mar 2021 17:54:26 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, thuth@redhat.com
Subject: [PATCH kvm-unit-tests v2] compiler: Add builtin overflow flag and
 predicate wrappers
Date: Tue, 23 Mar 2021 18:54:24 +0100
Message-Id: <20210323175424.368223-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Checking for overflow can be difficult, but doing so may be a good
idea to avoid difficult to debug problems. Compilers that provide
builtins for overflow checking allow the checks to be simple
enough that we can use them more liberally. The idea for this
flag is to wrap a calculation that should have overflow checking,
allowing compilers that support it to give us some extra robustness.
For example,

  #ifdef COMPILER_HAS_GENERIC_BUILTIN_OVERFLOW
      bool overflow = __builtin_mul_overflow(x, y, &z);
      assert(!overflow);
  #else
      /* Older compiler, hopefully we don't overflow... */
      z = x * y;
  #endif

This is a bit ugly though, so when possible we can just use the
predicate wrappers, which have an always-false fallback, e.g.

  /* Old compilers won't assert on overflow. Oh, well... */
  assert(!check_mul_overflow(x, y));
  z = x * y;

Signed-off-by: Andrew Jones <drjones@redhat.com>
---

v2: Added predicate wrappers

 lib/linux/compiler.h | 33 +++++++++++++++++++++++++++++++++
 1 file changed, 33 insertions(+)

```
#### [PATCH] KVM: VMX: Check the corresponding bits according to the intel sdm
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12156661
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2A226C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 02:38:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E32936192E
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 02:38:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229591AbhCWChk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 22 Mar 2021 22:37:40 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36802 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229467AbhCWChj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 22 Mar 2021 22:37:39 -0400
Received: from mail-pf1-x42c.google.com (mail-pf1-x42c.google.com
 [IPv6:2607:f8b0:4864:20::42c])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 02102C061574;
        Mon, 22 Mar 2021 19:37:39 -0700 (PDT)
Received: by mail-pf1-x42c.google.com with SMTP id l123so12735132pfl.8;
        Mon, 22 Mar 2021 19:37:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ASe6LP2Gx6mtSgf1m3rb1TTywtdrTYLw0AlmuTfxiqU=;
        b=BxVy0iLYY1/oTq/rhBGHlTDypx3x0DqCOIiv/4JPzMpvLOpTWgzrcrzz1soaOjCoGB
         DDpLLEkNMOJN2WTKu2N7xw+MWIDSlXZO/AZ18vmSIpzp6PbfAepVMIknAQ1Bb4ZE+dUX
         mFPBsOzujrA0AiyUHZpRprJSVi97KNuZHs9m3gOOVSB4qF8ocUwhX9LJ+NajY1p5DYGD
         D/Ny/z/lBw7/7wxxsoOIRvE+83Wj/RnKPPZ1Z4pdGp5JXY73jYJziSKRwaH+/gYpTw6Y
         EEj6dvlPZyb6W/BbV3+lIEXj9L4Buch7AmFr2CGkfsKxMd/VssAvO3E3yLmdj2JvG8hG
         iK7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ASe6LP2Gx6mtSgf1m3rb1TTywtdrTYLw0AlmuTfxiqU=;
        b=P1PgRjYkZC23Z6hbWaMXmOea0EDdpcVSkod7gQrM03xZJdIbbvJoiVHZaW3Sm/x2T4
         yBcvLDUdrwBSrdNznvwDGBWNBK9Qu8J80zPOWgRRf1h2IHvZQt5X+JQOdFey/DnFnIng
         dKbInj5tFIkmGUPBD0XAwxtefs48oA/ftD5BXeHc5AsRGhDWAIq2C0XEzq1Zdts+T5KM
         9Z7tTWORonMAT6/xJ6t+S5eq8NCovm6+4my/Cx5DKHNOZMwaboyDoIwjEdGPUcQoSJGL
         jHCjLKuvCV3x8KYdOMB3m767i4aU4m+Nfo73ojkfbel6af24f7GVJ357i/mk7o7RgoiP
         Bzfw==
X-Gm-Message-State: AOAM533TRa9fquv6EB612WGxIHqqSsZFC4ngqhJcMnwLO6STWJn29nbj
        LfFPtswBGYjoaa5uqu9JVDRkgNO8Ow==
X-Google-Smtp-Source: 
 ABdhPJwmTx25ycrbKXHds+YVV/Bl8Smk1rJX/x6XZO20XF1ghvXHrCge5BdA7CoJRFpuv9ptPpzgtg==
X-Received: by 2002:a17:902:d706:b029:e6:90aa:24e0 with SMTP id
 w6-20020a170902d706b02900e690aa24e0mr2893731ply.42.1616467058203;
        Mon, 22 Mar 2021 19:37:38 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 w188sm4956568pfb.4.2021.03.22.19.37.35
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 22 Mar 2021 19:37:37 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: VMX: Check the corresponding bits according to the intel
 sdm
Date: Tue, 23 Mar 2021 10:37:26 +0800
Message-Id: <20210323023726.28343-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

According to IA-32 SDM Vol.3D "A.1 BASIC VMX INFORMATION", two inspections
are missing.
* Bit 31 is always 0. Earlier versions of this manual specified that the
VMCS revision identifier was a 32-bit field in bits 31:0 of this MSR. For
all processors produced prior to this change, bit 31 of this MSR was read
as 0.
* The values of bits 47:45 and bits 63:57 are reserved and are read as 0.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 ++++++++++++++
 1 file changed, 14 insertions(+)

```
#### [PATCH] KVM: x86/vPMU: Forbid writing to MSR_F15H_PERF MSRs when guest doesn't have X86_FEATURE_PERFCTR_CORE
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12157213
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56CE6C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 08:46:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 249E46198C
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 08:46:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229547AbhCWIpb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 04:45:31 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:33589 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229548AbhCWIpW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Mar 2021 04:45:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616489122;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=bWgjxBic5KxGRp4l3xszbSrPWge16zEazFDHmYAecQY=;
        b=QJa9LbTnr66aQ3lJZJXrICN6xEe/4IaU2gS9B50qya8qwPqqTSzKIDq2GrN2zmxUGmfS/R
        6L69Jdt22b5IHn56H3185TOenK9YcrmXG8bDWSN7llh1apjUXrz3XjF86OikyZPd1xhIIK
        LiyS62cP5D2fu7s0SSi2SlyD1MZxErY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-207-ODt21XKFOvWp4gOtUumWzA-1; Tue, 23 Mar 2021 04:45:20 -0400
X-MC-Unique: ODt21XKFOvWp4gOtUumWzA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D2E7183DD26;
        Tue, 23 Mar 2021 08:45:18 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 43A3A1F7;
        Tue, 23 Mar 2021 08:45:16 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Wei Huang <wei.huang2@amd.com>, Joerg Roedel <joro@8bytes.org>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/vPMU: Forbid writing to MSR_F15H_PERF MSRs when
 guest doesn't have X86_FEATURE_PERFCTR_CORE
Date: Tue, 23 Mar 2021 09:45:15 +0100
Message-Id: <20210323084515.1346540-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR_F15H_PERF_CTL0-5, MSR_F15H_PERF_CTR0-5 MSRs are only available when
X86_FEATURE_PERFCTR_CORE CPUID bit was exposed to the guest. KVM, however,
allows these MSRs unconditionally because kvm_pmu_is_valid_msr() ->
amd_msr_idx_to_pmc() check always passes and because kvm_pmu_set_msr() ->
amd_pmu_set_msr() doesn't fail.

In case of a counter (CTRn), no big harm is done as we only increase
internal PMC's value but in case of an eventsel (CTLn), we go deep into
perf internals with a non-existing counter.

Note, kvm_get_msr_common() just returns '0' when these MSRs don't exist
and this also seems to contradict architectural behavior which is #GP
(I did check one old Opteron host) but changing this status quo is a bit
scarier.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm/pmu.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH 01/18] vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12158935
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B2CF9C433EB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:56:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 874BC619CA
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 17:56:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231382AbhCWR4M (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 13:56:12 -0400
Received: from mail-dm6nam12on2060.outbound.protection.outlook.com
 ([40.107.243.60]:2016
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231189AbhCWRzk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 13:55:40 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=GAOf+1oGSRelp7WIo7pnputZ90iY0QGLXpcAs/Sb8iZFpa4eG0/W6z1uQfsPnMXnz9zg8vFZbwZy0A66z6Szce49CaN1CluEGcJJCPXY1nXkFepUfITKb1zhuoWjnN3WZuJnS35lX0cV7vV/lWPbXKPdTQb5bfNHyNanmXTx52uZtid1GyHeewG+hj0+45K+QMkVGt5OtrC6eHJAji6T5D3CLfpVFylE/9VzhYxKtwq5IENpnLu/j5AOWwdCTVaV9Tc+ni7sCVDRufd7qDSKaHcS1UrVw48vL5sbAQRW6xVKisZPOo60jGX//xCdbDcB0RincfQl8zUMG0BoxlVMWw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=N/HAznt68F6rbDQYGOO9tCbMJ1b8NHhHjawE7ou1i1U=;
 b=CUIKaTcCFWcJh9IsM9UFoebH0PvCmbZDM+lmMFTF6asrxpz+Sjy1l5p1tRDOX04OwEP9TwBHLqrd3VuKggtEpRMMPHQFDUHdWGswZWWSFCw7rknUhQIeArDo1Zb5l/JQTRVulC8I1Y2JZ5YxZRqAtBxx96az2NHA7nBZZgcyq55moQT01AJsHTxtDJfbKVWsOS0+weX7ImiZYsc1K0DexbwpC5F2lzC+GAAmn18V+FzhhSOIgQ20PMBppjDbgULdzMRFksT4CGI+NgHFiYH2ZWi9q4yzNMr0C23dprjBAS/jYiP111jVC+06mpkzo5cVOL06Ru3gCW80h85yQGz74w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=N/HAznt68F6rbDQYGOO9tCbMJ1b8NHhHjawE7ou1i1U=;
 b=A5F0+ZAuS+cDjIlzXXjEJH/sFy+2gY2odHdvpqwK5C+R1X7nb+pqnz2TbBneB9lz7Ry5IXMzw9FOl4Ru/Yjdint67GXqgVn5dd4emEQq/DrtzEvZSkuj5v5tiGSnukPAIcuhR/n6sEvyWPwPSXheSOSIwKW48TbvRPp2yycLXAEOKpVlex7Rhv5Modwm0BhX1tBy9xtMtMyPB8BvFzZm4dpO52EkgrHOB0f7iGGMrqgJJUxswfWVqttGy2gW6+KQlBfmzE+Rg+wkOgL8z17VJvfPNCHzYpJAA3zW49zCKBehaOSGpi3klYpowxl6EA0Zvd82irVUcoCMnABtVHs+Fw==
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB4483.namprd12.prod.outlook.com (2603:10b6:5:2a2::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.25; Tue, 23 Mar
 2021 17:55:38 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3955.027; Tue, 23 Mar 2021
 17:55:38 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: kvm@vger.kernel.org, Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>,
        "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Christoph Hellwig <hch@lst.de>,
        Gerd Hoffmann <kraxel@redhat.com>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH 01/18] vfio/mdev: Fix missing static's on MDEV_TYPE_ATTR's
Date: Tue, 23 Mar 2021 14:55:18 -0300
Message-Id: <1-v1-7dedf20b2b75+4f785-vfio2_jgg@nvidia.com>
In-Reply-To: <0-v1-7dedf20b2b75+4f785-vfio2_jgg@nvidia.com>
References: 
X-Originating-IP: [206.223.160.26]
X-ClientProxiedBy: BL0PR0102CA0012.prod.exchangelabs.com
 (2603:10b6:207:18::25) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (206.223.160.26) by
 BL0PR0102CA0012.prod.exchangelabs.com (2603:10b6:207:18::25) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18 via Frontend
 Transport; Tue, 23 Mar 2021 17:55:36 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lOlFf-001cgQ-5W; Tue, 23 Mar 2021 14:55:35 -0300
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 1afceb6a-6a7c-459f-de89-08d8ee24dd17
X-MS-TrafficTypeDiagnostic: DM6PR12MB4483:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB44837B157042989AD45CF181C2649@DM6PR12MB4483.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:213;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 KepQ0snNw0jlpS+gT3NzUfpbMYHvJBeEfFUVNLsB/cGmhj9q25S/i7xdyLGzg1odGmDswEtZx9JOyIZSe661FmDNzecK2ahBZuoO54RCdLZp4sDIDFMdbftfqmubi/G11+h2hntzsgQ0HUHxVY38g5Y8rIlbJzJxlPLasf7T41Qn1rlnlLjwuouOZmXtFHNgYXvBcY7WdMBWwaWSomnQ3AIrSQz2xvqlTAAbW6Tks3y+N/qN8eiwJu7QGEUN/4MHln7PLWvyO0pxBt0yayoNtOpLDvspm0iSdyEZRutz2Cl5YW0ROrR2EKzV5Dnnk8+YtxFo4Jp5cUJ47e4BlrQUUt3IGg9lvMkuLsxoOyVvV73W+N3jPKxyRcgcI6sOdJzLo4HovescAflVWxY+vN0azAAFuDfHgX2in6vi353Ds8i2QXlYoH/ew5MnNS/ZwaK+Wj5kLpcH7L0P4YXgiyD2EvU908XpUonDXfGxalmbiVKOw5XtqadBNWJePsZFsnK6hooNovjz7oIbeFVwD9nEGua7TmSB9aQLG+kOD5HdpD9W45EFGNqAmGGdDQbmMUw5O0JpdfYyTtj13zaNTl0SEV1NqO+Al2MWUYOzoKepKl1L1hvokEzSQGIzhy0WO+goZzMGWbcG6yszPVfvpdRK7a0c+feooyHMVAJz9lypGhkV6FWS0mRcdffPN0a3EtUD
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(376002)(366004)(39860400002)(136003)(396003)(346002)(186003)(26005)(36756003)(37006003)(5660300002)(38100700001)(66946007)(4326008)(66476007)(6666004)(2906002)(66556008)(54906003)(6636002)(478600001)(86362001)(316002)(8936002)(426003)(9746002)(6862004)(9786002)(107886003)(8676002)(2616005)(83380400001)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 nnOPZuHZ8jAf5Ds+zjNvWAlcGMh7HMAgpmgSDtR87fE6+SPvMpE8zQ//EsZXgw5GyZV1NxSWMvbmpfiAertzhQ5LNLDh69YHLfgC4BMcRBYJkHakbCqCRENm7gBGcEpJoEIGquvEm2Ex06wRbwoOdPEEYQ+1Se9+bph9EPKNej3DzIKbs/nmrgB6Jw6U+kl8jVaPL46SOs2Frdez6YW5Yo1gELii0x2VY+gySc0kk/IQ/iopnJZt/oQH+bp1uIJOy0J5Rp2C2isADZBoLWvBD2OMcrbv5K1oFymhekTxLVftlsO6xlRZde9UymV4lEyRPiiZ0wI9axvM5WbNEzXhmtfWsdbJJG1UduuCSU0DYGCsEi/TVaozUyWKZ9S08lmNVCpa+whALQI1ka50sVa/v8BlwxtMIUsdr/hjfICZu8VOJnRWORFyLF2Uk2OI9rcX/F5C0pKbNKW0xMk+aYFrCRBKEBs6ZQO+KBIEl1IrhGGbcpK71MWwSf9ZWoN3okkv4Zj1vcWap26Cs6Xm7DcL9bVVsz1Ad0byzrtwD5JxMjl8x+aXdtlGaDqFNAvMiJ0pD7JzT0Gj8gbDMe3y2xjvfdcqwee9kGoip19hrj8gA8mDuGO+ptAGJNaQnL71mfcepXURM/iyQGVBu2oD3hm61g2yMjQHVYAEurMOzbvM2+Nb4oI3XsFX+Gzh2OjDPKje5stkw/xoi1TTBNUgOI8wrctdYXRNQP3jilgX/ltiCHqn5lhx859K0tt7uzg95pGpggL+cEGdCF5Hu4SYzRpon+A98vK4UpUT3e0ZFeFnfHQq2sRHIHcbonRolJHyw0FVNp2oY4KICzwzlzax1X7v8/C06dpfNbHHXxZTVRvjYhKL4ogbe3gaaRrieAlvHOwdKtVefUyx7ssAGIuGcPZIJjOjQoiKGiBG89oCHi3DEJt2MdLq7HhIxamFZcZtKj531WumvZl/cRQbKvqTjf/xq4tc8xi/FeKCW3h6N/mjMBeOPQrY6/crq5GuZkAANDJbt4A4eM0Wsq+o9sJEKJFg2Pl9lHb1LkEm8AcNZGg5FTPZdWkshUxfYT0/7thSehaVawLAkCWlWk3pPooQev4Nxi6FAJQ09pUf4EApTT44p+3R5pF8HbjwWBn7g5u58/h6EDlz0IjBwT+h/sL24iTfjPXKF6sW+RiVPagykQHrd7+Y/CryKOX0vmHLgPHkHFiBytnbZ4uyNGSCiAA85HSTGe8j88+S5XWmBU237wQbbRAFoXo7MYGKku7QcHUSQC9bu7XvDZB9el/5vLJteOPWCAXEmWjKDIp456uHzF/LIYrnimMKtT/GPPIlHniISQvN
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 1afceb6a-6a7c-459f-de89-08d8ee24dd17
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 17:55:37.0976
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 qfsNatRpr2oLcF4ky/N4/TvregiI6OJp3AVGzE6YGdbGCeA2HaBk66PPzpARXSk+
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4483
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These should always be prefixed with static, otherwise compilation
will fail on non-modular builds with

ld: samples/vfio-mdev/mbochs.o:(.data+0x2e0): multiple definition of `mdev_type_attr_name'; samples/vfio-mdev/mdpy.o:(.data+0x240): first defined here

Fixes: a5e6e6505f38 ("sample: vfio bochs vbe display (host device for bochs-drm)")
Fixes: d61fc96f47fd ("sample: vfio mdev display - host device")
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 samples/vfio-mdev/mbochs.c | 10 +++++-----
 samples/vfio-mdev/mdpy.c   | 10 +++++-----
 2 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH 1/4 v5] KVM: nSVM: If VMRUN is single-stepped, queue the #DB intercept in nested_svm_vmexit()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12159037
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1E77C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 18:39:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7BBB4619C5
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 18:39:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232031AbhCWSjI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 14:39:08 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:44822 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231814AbhCWSiv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 14:38:51 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12NIOjDH166831;
        Tue, 23 Mar 2021 18:38:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references :
 content-transfer-encoding : content-type : mime-version;
 s=corp-2020-01-29; bh=oI+jRfUT8/LTeal7sxTiD5VotikYIf0caD3DMotVJEI=;
 b=Q/+nDaZK9aQdRBSq0Bk66zX9NLtTLCwUnoOD7Ea1aAYpxoY5FIkaBzaWTV+lm57bHsse
 TEI7AlinKEGKyGsjSr6Qr8yEE7HlDSFhSRGxlBhPfb/B2bcCFZ37j6UT6mgY6fqY+ZwQ
 L8tmd8vHxs89oUtU11W4e9nm0RXbjFaOq/SqII7EVhunqRfG/K9TxnfGgsvlp33xFl/1
 yNGbfS6/NJ8dCQScSuFButNYZ4uhwhSn+KLXbE5oNmNrpDjOnKzssjffcByOGkntt8cs
 lpLpWYYO6gCrCIiHRWM09wjPHThmZqUsfQA7l3+rmtxyNwjaLIAxhShvGYLM5VTxzeCo rw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 37d9pn0634-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Mar 2021 18:38:46 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 12NIQNs4075389;
        Tue, 23 Mar 2021 18:38:46 GMT
Received: from nam11-dm6-obe.outbound.protection.outlook.com
 (mail-dm6nam11lp2169.outbound.protection.outlook.com [104.47.57.169])
        by aserp3020.oracle.com with ESMTP id 37dtxym92t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 23 Mar 2021 18:38:45 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=c7t4nYJAxCjAKi7ZxmCiGCkDpYoo7/eaFQVsYqfu+mObX8fBS8Oh0iud1/wS8ImJJ+us5K3iedLOFJw7dFplZkGi0ZVek0FCTVmK97MSC8bpWgHclAOcmMp4TZx3+ku+1Q9o2gNMc4/VctdjW7eB33iUJcUszxEgXeiLx5z1bxXeOv75br1cFVw5+EbhqTy3Sk314V2vqbGdxZBVj2sCxG0OYGsSqFR+qBjkb+yXWZZu1F9YaX2rSFxJoV2+GLeoiDjcNynw5BQkxrOSp2cOe5Y6UscCv5NZ6u9Je+7kA7oa10Jw9hLEpVOMmbmSJTgjuoSjufS4x84yO7YJAMiynw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oI+jRfUT8/LTeal7sxTiD5VotikYIf0caD3DMotVJEI=;
 b=GfcDLA4zxOMBZ1bQPj3UxfeR0FQoV3HpZ7WfrDkQQKmckhIV9DyHjyir5ZJH0FmY3olN6ZRsZXdLqDphtoNSFViD0TcivLcU4+V2PY5CFsDyd1GmVpq9aJmh5+Z4GOFFx6l/KCPtI8oXrfLs/2VBiPeO0ru8CCu0MP+JD2yZ3We9mokIg46MbezHSTfwvxIxWMTnknAmgGLKnsQrkn+QGaEsRG6irRVVBIOJJnw8O8Ye7MDkcmlP2CC9oJ9Vz3j8Zk1KeFlb/zThWUz5UPWFyO8PTlCRnCKcfa7thZqH3fWfijMw5f++mq4U/pNnZssbeNsuSalfdXBl3/bsaHTWFg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=oI+jRfUT8/LTeal7sxTiD5VotikYIf0caD3DMotVJEI=;
 b=SrDJGs4QoPcG5H6vPQ3U+Yi7Z+XcvLkSx4jKjH0xLUAOSCm/ixV88zBb6RUzUmQF3k85x7M8U6RlurfLUTyHorInrP55/fK+2+N31OVt21JPzxVsiArB4VzVT91f+CYJ1KR9gCMcQKHFf/H/HeZHDN88xx8yhnoxua3IiHcHSTQ=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SA2PR10MB4508.namprd10.prod.outlook.com (2603:10b6:806:11d::16) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.18; Tue, 23 Mar
 2021 18:38:44 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::1871:3741:cc17:bcf7%7]) with mapi id 15.20.3955.025; Tue, 23 Mar 2021
 18:38:43 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 1/4 v5] KVM: nSVM: If VMRUN is single-stepped,
 queue the #DB intercept in nested_svm_vmexit()
Date: Tue, 23 Mar 2021 13:50:03 -0400
Message-Id: <20210323175006.73249-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210323175006.73249-1-krish.sadhukhan@oracle.com>
References: <20210323175006.73249-1-krish.sadhukhan@oracle.com>
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BY5PR20CA0008.namprd20.prod.outlook.com
 (2603:10b6:a03:1f4::21) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BY5PR20CA0008.namprd20.prod.outlook.com (2603:10b6:a03:1f4::21) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3977.24 via Frontend
 Transport; Tue, 23 Mar 2021 18:38:41 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: fdfe4f03-ebda-40cc-b982-08d8ee2ae1e2
X-MS-TrafficTypeDiagnostic: SA2PR10MB4508:
X-Microsoft-Antispam-PRVS: 
 <SA2PR10MB4508C55A53BFB3ABC09030B781649@SA2PR10MB4508.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 uAnlQnUXEDDWc2ezj73RGZrZlvg/ZbXjyu0KL1PAhpGpQlhzRCI/fqSGjwaNU3NvYgf2S6ATWaP1qXpEopHPphL3Zgw0NdtdoYCcasG5fzyfwkoRDizhHJnOhS+yr2bjkjtIxgVEpfSaAjObhwUooICDvTqWmVs8L+bDT7ewM8F0CkFQaODL7MgYzqTfOPKmPtHzw4IXiXHyjuNp9cmV4O+7zSWnkgZEUl3dEpLzxwzsDosOP4t0W5UyZElDiKuqnfS32X4DnvI+Y6bl0yam1ZRTxbbto7LgYFhnzJUchJAUgocv05w54rUko85H6x4ejzt6k4j8CYYFmZ3xS7BqxkJsdfFFn4U+SSmOwHgoW6ZOyukfumsDQ0GZ776qc4F2qiez6OFd2/pKIIFvl8FJF8DSQLjbn374VGbGXxkHBMY3aaDmXDQkAMrlDaF+mWWr7TAFKYc8AODrfmmI5vU+WwF7oDEkxev68FJT6+00Huw+T77QnyHKDIbeUmKvlGuykajxhKJrgJIpFyilLQUuV6KiMBgfqXCtopmbKl/AvijiZK0GVhYGJjXo8Xt18gSISfJ/otlsfZICAYeEGRyaY+5q4mgNcPGV6p3+gvjMcChLxuRiph0V0V5yCy8zE+iNnp6RmQ15UeD/lTyEOOYTWQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(396003)(39860400002)(376002)(346002)(136003)(366004)(44832011)(1076003)(16526019)(2906002)(316002)(2616005)(6486002)(5660300002)(83380400001)(38100700001)(66556008)(478600001)(66476007)(8936002)(66946007)(36756003)(6916009)(7696005)(86362001)(6666004)(8676002)(4326008)(52116002)(26005)(186003)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 3o88P0C0pyrZW6SqhSfeCcvbWD3xwMGYuSacvKsX/HPVQZZMLDfWeZZ0N5cZSI3GRw3eaWIi8fS+Bapj+3e86/1EnCSwZUEqOrmUrmjWKYviitv4QzTgBc7cdheiWpaEAzIKvNSir5/pG23x9Dud1D7gvIEQloiST3fHAx183zvPTv3X8ozGUWe+JfznPULCNDRv9lsu+pUBKzkCRe2NqT7zU8TmEaZmv0vRGrS8tmFdKgRtwh+GK1/Xkgkq6IH0arxM5GTdlMemO8mktJC8L8c3XzjChl3521KaFj+MS4N7T0zkPpH2InY1bToQG1EVUXMMzgMguArHXCa8XhBU2iBP7jlndmvHy2S8o92UPECzA+OFBOBSfzSQSU6jPAiGN+zqva9O00iuCM8zk++M9ACNwyLLaOm9M0NAXCS1K6pVFMNyZonKI4Q8WltcbLSLHo+y22+jaPivM8UiG7pdO+LZN0s1t6oLM7eiF6YWK3ZzPNoGXF7ZGxLTNzWeQ8V6/qHYr1X4R8soNRGpWTXtnjBEZy5DJ43wvQCN7d/r7F1j2c9cp+iV76O6nN/+FdYTEYcgtCTPeT+5zx6WQzZofQ0SiwYBMFS5NKeMA4RyV5NL0EXV/rfhsnVivTqfGiPyQoVPVyfSKRwkVBN86bHS3ivgOgnbZSHLyHHDvqCKHxZS0BLPILGMHIgRZWR7Xhv5xmY2nB+akZnreHnuYzlxOKkL5PS9w+YhLu4p5UY7+Ju1pzUuRnr7Skb86Vmu1O6ohJakFsARPG+r+iAGR03GRcbnpinz/+hbZAHTrKWgzQOMSKS4GWDXBO7vco06AouLvi6bvcWJZi8AhMAShzUl1cXSx4W+VhJz1WuIQq4ZaRPt9IEfz06I6X8P4He1+UFwtiQlXTaVqJ5iHDBwEC0kO0Mkd885JLLVOI6u/t+runnt4aiH7szgWmzwo9/FIRn/PM7u2b5CFNVDZVmbQSD8reU5ZszSA24V8law4OvXM1tJ6ou+YRWpHWdDf3akGnPW2PupLln31K8B77iA2+xrurU9b9H4AwWRks7a2OCJ/MBrEVN85CK7wYiONwygqXscNK4HNTgQLaFuqG33LdEc8i4cTWUXPfTDK5cXV1oOp4iVp/AbLJUMTH4+nB81CjOVxTlDu1Ud9YudD6RPpCnRHb+7pCdQmUFcvux/D/SPIcK+X6TERbhl//QqxA9ZYocdUz9xWNbeQfb8jpVZk5USxyuzIcTErjlkpdKvqxmHeInO4N/4LaqKYToWfHSg3Er9SX2sb9rXd2fHMjOUQDRzQzcZToMjKGEOCI7coVKi3f3ENzm1QLRsLLYrBRiZXFsl
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 fdfe4f03-ebda-40cc-b982-08d8ee2ae1e2
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 23 Mar 2021 18:38:43.9602
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 pIIoYDqTdx39spZRtsOOtRSUVhOTlS38c1aVpbKDB81bH/u59LeVA9ontDlO44AreJaVkIiWvMoayhc9q0VjgBnGXwBhApoC3E88Y303ZDQ=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA2PR10MB4508
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9932
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxlogscore=999
 malwarescore=0 phishscore=0 bulkscore=0 mlxscore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103230135
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9932
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 phishscore=0
 mlxlogscore=999 priorityscore=1501 impostorscore=0 bulkscore=0 spamscore=0
 adultscore=0 clxscore=1015 malwarescore=0 mlxscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103230135
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to APM, the #DB intercept for a single-stepped VMRUN must happen
after the completion of that instruction, when the guest does #VMEXIT to
the host. However, in the current implementation of KVM, the #DB intercept
for a single-stepped VMRUN happens after the completion of the instruction
that follows the VMRUN instruction. When the #DB intercept handler is
invoked, it shows the RIP of the instruction that follows VMRUN, instead of
of VMRUN itself. This is an incorrect RIP as far as single-stepping VMRUN
is concerned.

This patch fixes the problem by checking, in nested_svm_vmexit(), for the
condition that the VMRUN instruction is being single-stepped and if so,
queues the pending #DB intercept so that the #DB is accounted for before
we execute L1's next instruction.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oraacle.com>
---
 arch/x86/kvm/svm/nested.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH] selftests: kvm: make hardware_disable_test less verbose
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12157227
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 14D66C433C1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 08:54:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C17D060231
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 08:54:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229761AbhCWIxk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 04:53:40 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:34395 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229915AbhCWIxK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Mar 2021 04:53:10 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616489590;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=hwAolZy4s3g0O+tDHC689/78ebeI0EMXlZOQe6J+/Wk=;
        b=ABRicki0MK7rN+i28jCLQ7In2cZsJeDAR1gH3/4h8HD0IiLO1bg9I42yfYROS/gjgj2Q/Z
        NubTDFQG65GD/kWTeWdtUQpVGLqUa8/cPAomFRDVPwy2oAqDzjcJHJmpWUaxaSsZR2VQZC
        DawZaN1aEER3dHu/NHDusNw2cKdvY7w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-597-9gYoLGQ4MH25yAjgkcH__Q-1; Tue, 23 Mar 2021 04:53:08 -0400
X-MC-Unique: 9gYoLGQ4MH25yAjgkcH__Q-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6783080006E;
        Tue, 23 Mar 2021 08:53:06 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 875EA69324;
        Tue, 23 Mar 2021 08:53:04 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] selftests: kvm: make hardware_disable_test less verbose
Date: Tue, 23 Mar 2021 09:53:03 +0100
Message-Id: <20210323085303.1347449-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

hardware_disable_test produces 512 snippets like
...
 main: [511] waiting semaphore
 run_test: [511] start vcpus
 run_test: [511] all threads launched
 main: [511] waiting 368us
 main: [511] killing child

and this doesn't have much value, let's just drop these fprintf().
Restoring them for debugging purposes shouldn't be too hard.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/hardware_disable_test.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH v2] selftests: kvm: make hardware_disable_test less verbose
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12157381
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D786FC433E0
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 10:44:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF2C6619D1
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 10:44:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230339AbhCWKoC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 06:44:02 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:28460 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230345AbhCWKni (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 23 Mar 2021 06:43:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616496217;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=4UvLisLY3QVjpjoeO2+ShNqoiFem2kvMWqAPyPyr9MY=;
        b=h0ecbV3y60RvSjt18lTdq/q7PgYZ1vvhpPIWbrz94gPKX4iBsF2B4MO/P3iVZyjE7an8Ch
        gwW8gEH6oQRXTJMiVUp0ly9RUlpeVN5dE53dyYJ08VUWHlsIcu1OVri1GJcNQpTAsZKega
        /e3bpyOBJ3+xzUZ+jJ82YSPJwl3P0Eo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-363-pg-DBKDuOOmNOGVHi1kDeA-1; Tue, 23 Mar 2021 06:43:36 -0400
X-MC-Unique: pg-DBKDuOOmNOGVHi1kDeA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C3528593A0;
        Tue, 23 Mar 2021 10:43:34 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.59])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 654EE1A353;
        Tue, 23 Mar 2021 10:43:32 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Andrew Jones <drjones@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2] selftests: kvm: make hardware_disable_test less verbose
Date: Tue, 23 Mar 2021 11:43:31 +0100
Message-Id: <20210323104331.1354800-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

hardware_disable_test produces 512 snippets like
...
 main: [511] waiting semaphore
 run_test: [511] start vcpus
 run_test: [511] all threads launched
 main: [511] waiting 368us
 main: [511] killing child

and this doesn't have much value, let's print this info with pr_debug().

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/hardware_disable_test.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [RFC PATCH v7 01/22] af_vsock: update functions for connectible socket
##### From: Arseny Krasnov <arseny.krasnov@kaspersky.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arseny Krasnov <arseny.krasnov@kaspersky.com>
X-Patchwork-Id: 12157749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A8198C433DB
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:10:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6A352619BF
	for <kvm@archiver.kernel.org>; Tue, 23 Mar 2021 13:10:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231383AbhCWNJj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 23 Mar 2021 09:09:39 -0400
Received: from mx13.kaspersky-labs.com ([91.103.66.164]:46337 "EHLO
        mx13.kaspersky-labs.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231411AbhCWNJP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 23 Mar 2021 09:09:15 -0400
Received: from relay13.kaspersky-labs.com (unknown [127.0.0.10])
        by relay13.kaspersky-labs.com (Postfix) with ESMTP id 03B845216B8;
        Tue, 23 Mar 2021 16:09:08 +0300 (MSK)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=kaspersky.com;
        s=mail202102; t=1616504948;
        bh=6mKRrts4oV1cKdQ+DaGsBJr6pu1G5LW75JbNv3Kmwqg=;
        h=From:To:Subject:Date:Message-ID:MIME-Version:Content-Type;
        b=DaD764uK8T+l9GWWfGDao2R2g+us7zE1yRZ/XosnPC1rQlfchzWGyNG5VOz+h8fbv
         s3jectlkVuYhFtaeKzaBEtrGC5oK01J7vq7ECwJdbtiChME5qw9fs6Xr7sCHTxTWsh
         nFK99r3p9LlhVt6pVQBo12Kq8tBFeCQkIvUsaW4nWbkP+EuvwuKXqsli1qMR1s8ijL
         cm1qD5LxnvOPVUjnt2hhUNh1mR3uuOm3jjXmvnGeW2+b+XOzv9Z6un8E/hJOIvxtlp
         wZEUahj3nQCdEG5EZNRLWfkes0q8cp78YhT++7wGo7KPjZzDS0OhC3VdkNWP1zxrTL
         HkS18WNFxrlPw==
Received: from mail-hq2.kaspersky.com (unknown [91.103.66.206])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-SHA256 (128/128 bits))
        (Client CN "mail-hq2.kaspersky.com",
 Issuer "Kaspersky MailRelays CA G3" (verified OK))
        by mailhub13.kaspersky-labs.com (Postfix) with ESMTPS id 20DE9521708;
        Tue, 23 Mar 2021 16:09:07 +0300 (MSK)
Received: from arseniy-pc.avp.ru (10.64.68.128) by hqmailmbx3.avp.ru
 (10.64.67.243) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.2176.2; Tue, 23
 Mar 2021 16:09:06 +0300
From: Arseny Krasnov <arseny.krasnov@kaspersky.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        "David S. Miller" <davem@davemloft.net>,
        Jakub Kicinski <kuba@kernel.org>,
        Jorgen Hansen <jhansen@vmware.com>,
        Andra Paraschiv <andraprs@amazon.com>,
        Colin Ian King <colin.king@canonical.com>,
        Norbert Slusarek <nslusarek@gmx.net>,
        Jeff Vander Stoep <jeffv@google.com>,
        Alexander Popov <alex.popov@linux.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <stsp2@yandex.ru>, <arseny.krasnov@kaspersky.com>,
        <oxffffaa@gmail.com>
Subject: [RFC PATCH v7 01/22] af_vsock: update functions for connectible
 socket
Date: Tue, 23 Mar 2021 16:08:34 +0300
Message-ID: <20210323130837.2459550-1-arseny.krasnov@kaspersky.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210323130716.2459195-1-arseny.krasnov@kaspersky.com>
References: <20210323130716.2459195-1-arseny.krasnov@kaspersky.com>
MIME-Version: 1.0
X-Originating-IP: [10.64.68.128]
X-ClientProxiedBy: hqmailmbx2.avp.ru (10.64.67.242) To hqmailmbx3.avp.ru
 (10.64.67.243)
X-KSE-ServerInfo: hqmailmbx3.avp.ru, 9
X-KSE-AntiSpam-Interceptor-Info: scan successful
X-KSE-AntiSpam-Version: 5.9.20, Database issued on: 03/23/2021 12:55:25
X-KSE-AntiSpam-Status: KAS_STATUS_NOT_DETECTED
X-KSE-AntiSpam-Method: none
X-KSE-AntiSpam-Rate: 10
X-KSE-AntiSpam-Info: Lua profiles 162595 [Mar 23 2021]
X-KSE-AntiSpam-Info: LuaCore: 437 437 85ecb8eec06a7bf2f475f889e784f42bce7b4445
X-KSE-AntiSpam-Info: Version: 5.9.20.0
X-KSE-AntiSpam-Info: Envelope from: arseny.krasnov@kaspersky.com
X-KSE-AntiSpam-Info: {Prob_from_in_msgid}
X-KSE-AntiSpam-Info: {Tracking_from_domain_doesnt_match_to}
X-KSE-AntiSpam-Info: 
 d41d8cd98f00b204e9800998ecf8427e.com:7.1.1;arseniy-pc.avp.ru:7.1.1;127.0.0.199:7.1.2;kaspersky.com:7.1.1
X-KSE-AntiSpam-Info: Rate: 10
X-KSE-AntiSpam-Info: Status: not_detected
X-KSE-AntiSpam-Info: Method: none
X-KSE-Antiphishing-Info: Clean
X-KSE-Antiphishing-ScanningType: Deterministic
X-KSE-Antiphishing-Method: None
X-KSE-Antiphishing-Bases: 03/23/2021 12:58:00
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-Antivirus-Interceptor-Info: scan successful
X-KSE-Antivirus-Info: Clean, bases: 23.03.2021 11:46:00
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KSE-AttachmentFiltering-Interceptor-Info: no applicable attachment filtering
 rules found
X-KSE-BulkMessagesFiltering-Scan-Result: InTheLimit
X-KLMS-Rule-ID: 52
X-KLMS-Message-Action: clean
X-KLMS-AntiSpam-Status: not scanned, disabled by settings
X-KLMS-AntiSpam-Interceptor-Info: not scanned
X-KLMS-AntiPhishing: Clean, bases: 2021/03/23 11:43:00
X-KLMS-AntiVirus: Kaspersky Security for Linux Mail Server, version 8.0.3.30,
 bases: 2021/03/23 11:40:00 #16480199
X-KLMS-AntiVirus-Status: Clean, skipped
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This prepares af_vsock.c for SEQPACKET support: some functions such
as setsockopt(), getsockopt(), connect(), recvmsg(), sendmsg() are
shared between both types of sockets, so rename them in general
manner.

Signed-off-by: Arseny Krasnov <arseny.krasnov@kaspersky.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/af_vsock.c | 64 +++++++++++++++++++++-------------------
 1 file changed, 34 insertions(+), 30 deletions(-)

```
