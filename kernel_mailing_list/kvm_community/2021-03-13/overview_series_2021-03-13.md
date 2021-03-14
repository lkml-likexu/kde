#### [PATCH v2 01/14] vfio: Remove extra put/gets around vfio_device->group
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12136241
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4C551C4360C
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:57:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2EB1164F8F
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:57:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232956AbhCMA4f (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 19:56:35 -0500
Received: from mail-dm6nam12on2081.outbound.protection.outlook.com
 ([40.107.243.81]:44481
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S232257AbhCMA4Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 19:56:16 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=f3QmvPvZuZdXgxlsPsvfdnDGJYY7xhf2rIHGEmo1LtvZRFkIa3Uvksdy+Y8py+U6W/i8ivZ86OiabXLlVBAKTSXtyirEe2V68yStYKSAuQPw5+1ONhb0Cu8hPDX1hXxjElDBLPPxaTPyGhVAZS1A2GfclJdFSGg2xHFWVV90bcCXSW8uMI3r+8Pyam7kYs0eogQ9I5z51p6tcQJbRYp/gbA2KU4uyb1ts68XjggpWHln3lSlEIzlhDcbRwfjtmE3TwZsW11mgiWnwo3HA9b6rCsnC6hv1WnoU/wx1bwQ5MYgYCYJ3MEXwo1DMAVM2EDlg3Tfjsp0ZhNPGoOF7LJrqw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KiIyIwO7kq0WsbP/stKbgYgvl/RRRz075uzNy8ghGqU=;
 b=Yusi/BdGc2akABjOLKui1IBb5TqUHZV5DtpvlSPqAmJVSrZR8oxg/21EhviiZ0W2akYLpHtaLuPCSCBzhZnYhURtVnGtmOsuMsovnEoWOA0ioWFnn4sj049nxelfHtRDYvl7CUhQZNU1QonizcUau1+7lMfGwxzCj3TTkQwhf79F4oxCpCLs1+69ml0Cr4/TKT9uUut6XtW1ETFJa2DNOS7E6az563Pv7s2L/jw4So03ZOj3MDUBAGYr7vqIM6U3VpwWkVN+dNQEAxCBagjIozU8qb/CYJ16+6kH2F0+g9BsJnLpb05OghyWq0tTfomgIYgsRWHBV0fs5LBysTcrPw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=KiIyIwO7kq0WsbP/stKbgYgvl/RRRz075uzNy8ghGqU=;
 b=GZrlcfB+rmd5+arvlLiMNmImeH5/8uM8dYY6OZhr4t+2hJoqmFO4TIWFexYQdNeOzrLQZ2YjkRX6Of3a3ES/4gJvFmIgcaqaIT0orQVCAFkOAUbHRT0INkMbtcghoD0+2OYSzNulJSeO1My/cYcEw45uorugCgO2GiZEcWoYVJFY9JURETupu2cwIr8rRXWykx0Usu46e/5AcS2xgG77FsRI4qlYEUdRO/QNjJl7MjozdO2VBa6HElY0PCAWvwS6bf4X/ZzOnIar+DlMgY+J8Er6UoUMNHnd3R2ugS5lzXTD2G635cNJYH7z3Frg9Rc1RZUubK11wpcD6g8Kk2P0TQ==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM6PR12MB2940.namprd12.prod.outlook.com (2603:10b6:5:15f::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3933.31; Sat, 13 Mar
 2021 00:56:15 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3933.032; Sat, 13 Mar 2021
 00:56:15 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Daniel Vetter <daniel@ffwll.ch>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH v2 01/14] vfio: Remove extra put/gets around
 vfio_device->group
Date: Fri, 12 Mar 2021 20:55:53 -0400
Message-Id: <1-v2-20d933792272+4ff-vfio1_jgg@nvidia.com>
In-Reply-To: <0-v2-20d933792272+4ff-vfio1_jgg@nvidia.com>
References: 
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: BL1PR13CA0167.namprd13.prod.outlook.com
 (2603:10b6:208:2bd::22) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 BL1PR13CA0167.namprd13.prod.outlook.com (2603:10b6:208:2bd::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3955.11 via Frontend
 Transport; Sat, 13 Mar 2021 00:56:12 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lKsZa-00EMAl-O2; Fri, 12 Mar 2021 20:56:06 -0400
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: a2f89a1e-ddc2-483b-fbaf-08d8e5bacc0f
X-MS-TrafficTypeDiagnostic: DM6PR12MB2940:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB2940B7CD961EF9AD5020EA52C26E9@DM6PR12MB2940.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5797;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 OkbSiz5DKmDdxxixlQ5D3NEd6SQhl4Nwr9MsPqZ0jORR6+QSQ4vt2e/7APctEMNl1OQpaBVlaQoAz4FOYr538uDCan18v2gObs7SHumkF2dLY6gkFz4gPhtqdnGBoaAqSnevOoRWJ+a2LjlIIrwfdVUabqngpV2Op84ZMS40FQNl5y3C9Bm19D1AFYrzkAzZp+UtR4XEuf6avJbGEVsNNwp2Glm7b+GtkCmyXQCL+pAjoGeqWVqUtuJU+4gK6hds9iplKjlhXGUY1LHH0vdYcJhk6SpAUjbR9hYDQcEQlqh0tKxB5AVAXEhkWIm7o6opSJcRxe5QT1RPDPyK1+AxO4xRU8NVGDvy2igphmF5xtGjvNO37fMq7WjeVveQEHa7Yy1+vDAxR2E8kLsSsooCEqnJcJDF/Ddyf8WUX/ZWfJD15X4+Z5IKxpVliEkoUeFRCgicGqDiSwxP7AL7/TyAiQkVDb+Tiz+H3MFHbRpUsQD+9nldnPPcRphlE3Ixd0DM2Ob4XZoIbbK3sSzqgNByY1CfFqrq2aQdGVZFL3v8VT2y3IoWNNAlPmTMW/4Ea5wrrubySEhc1q1QhDC7+1WQa+nPSWwSTL390S7YfL2MrdA=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(376002)(396003)(136003)(366004)(346002)(9746002)(9786002)(8676002)(6666004)(4326008)(107886003)(54906003)(8936002)(5660300002)(36756003)(316002)(110136005)(83380400001)(66946007)(66556008)(186003)(26005)(66476007)(478600001)(2906002)(426003)(86362001)(2616005)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 q7xFN+pQ/7yjY26wP2x2FkSGX2sGIUD806jRqr2TiOxkt9c0KxwP84PdgumaAnOx8Pr1/fTC7tIjEXOwpV9cOmIBGySN+eeNuDiRaxQWrM8XT96UW1MCaE/pIwclpHh61zx/iD6kifii/55emoAqtcybS6LIC2g8lMyOoGaklM0+QgG5RXbfjVlhffFedeppuvjaqIFEHWw6eERzRqoexDY10fPrCfF+iLLIklqP5AUTl8hazXXzkKerYlb7xi2tNcJUoXLdZOjdNiI/VT4i95BicCFDZ+hQQZmJ9TTkA1FHZ4SFp1CIkY6ODgY7EqerQ8fuWCmPZn0i29ru4ek+4WjH1X6fkGoZ3ZZT2yCVx3bOkypCSQkKZ/v2dw05fGrHnF+UcWe2wlkGjOG38+MIjrC/Qp3zDHqyTIH5Ox4IMNHuJpu5OYJXg/0n+QNJiV82scO3RjE0gg9s/z4xsnsMT1djkt1Mmzw9afELRgUf/TexPVntBJwyvON73DG+Oq4Pmztsta52xc8HprWv8c96XZFY/Qf/paM4jta8rTdpDBNc9yqhLh58Eo+xO/tyKDY9vpCNhdZgcb+Zq1jVMmE9cOEkup5M0AJoFt5NzzAA962N0yNSBDnDcg4F2CHK5FhHBfq2NRnfq3jcX2bKlpmJuvWrn9y4SD3kXmpMOdW0l2qhJA2HjHVl3GBeLaYOZM1ZuTmC4kbEZFaHIl5DDjylxdnUEq/5ZZ61YRBTsih9aztEqlyBeAnUmktSLUslaQpbmRYztq8a/EC7mI7OG+Ogdx5C8pIc6xQDCIDU0eeoNV6/dGgfkAgDUyMPF6XuoHJzt/rmJWzBmcTTQbOWr9gbOn9Kmw3qq09qbHkoPOWfmal03fRWCjiEBC9rZUOMtARwV35N8b3e0m1KE7v3MVBpWBWxFJ7AGhGEC2GySL7UTNJ92VLcFlWTjXe8yN4GORk93bXW1GIi0RmQvVkMuPv1juLnfGi2+rrQv5pq3pPYuhGF1l9t9jIgVpsWdHhlzfaor/QkA5uado7njiOFkrbj4/vxBCDau7iJMOYGAMRkhRAIV66Nb6N0u4hEzxs1Bh4kYgno0BMr8ijKyH3Qy+iztPLfNdYn8NRmU6EY8UWIcba/yXGBl4BAgGM4kykdEwQ1oLhGB5KIPsORY41M1rX+gIswd0baEAG28UMOogyH2nbcWqZfExIn97V84jlGfOWp/jcTzGN3MkwtQehMCb7qn2+ct0xfX+ROszZbSu2+29dSC827LsHocERxRAsbnQNuRUJFCP3KseUdasVcWCEXAVlimq/NjaipnI+I71khUv4TfR25p3MFoLPw3rNzjpbT
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a2f89a1e-ddc2-483b-fbaf-08d8e5bacc0f
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Mar 2021 00:56:12.6290
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 ROdzgl/WGRpkVez3rSzhCh4zGo4a/Tz9JDvVkJkcqq1pC3jSpmegI+WDbKbLRy2T
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB2940
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
Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/vfio.c | 21 ++-------------------
 1 file changed, 2 insertions(+), 19 deletions(-)

```
#### [PATCH v4 1/6] irqchip/gic-v3-its: Add a cache invalidation right after vPE unmapping
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12136627
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9981AC433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 08:40:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DDB964F16
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 08:40:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230441AbhCMIj7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Mar 2021 03:39:59 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:13162 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231938AbhCMIjr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Mar 2021 03:39:47 -0500
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DyGJk0R9YzmWBR;
        Sat, 13 Mar 2021 16:37:26 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.498.0; Sat, 13 Mar 2021 16:39:38 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [PATCH v4 1/6] irqchip/gic-v3-its: Add a cache invalidation right
 after vPE unmapping
Date: Sat, 13 Mar 2021 16:38:55 +0800
Message-ID: <20210313083900.234-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210313083900.234-1-lushenming@huawei.com>
References: <20210313083900.234-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Zyngier <maz@kernel.org>

Since there may be a direct read from the CPU side to the VPT after
unmapping the vPE, we add a cache coherency maintenance at the end
of its_vpe_irq_domain_deactivate() to ensure the validity of the VPT
read later.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 drivers/irqchip/irq-gic-v3-its.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH] KVM: clean up the unused argument
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12136445
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67EDBC433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 05:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D41764F87
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 05:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231280AbhCMFKz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Mar 2021 00:10:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51108 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229852AbhCMFKs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Mar 2021 00:10:48 -0500
Received: from mail-pf1-x430.google.com (mail-pf1-x430.google.com
 [IPv6:2607:f8b0:4864:20::430])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 63A99C061574;
        Fri, 12 Mar 2021 21:10:48 -0800 (PST)
Received: by mail-pf1-x430.google.com with SMTP id x21so1939158pfa.3;
        Fri, 12 Mar 2021 21:10:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rZiHATcqAxSVuhRyTi2E5mTS4Xv1o3Mg3eeyKP3UZ5g=;
        b=V0LnVckIlEb6217KBYOSW05AESkEojvfEcUII/Z6pX0szMiyJ14AWYcYTWmqKRNgyW
         3+QuyBv4rbEV/DgVbMST/DLbSBUCRI46Ohluk+jzDpZlNywrZ7ZvSXOYVJT8CU0phqJa
         DvzcHXNMFzNm+cUPBU7yvwci1Ran08HuWWvyVYqiyeo7OMmeWNvC76TcqLYyWV/kNRSI
         iTRwlOnFjLKcDXa9EbqQV0KyILtNabSO6ppH71SEMBRM7rQ84xTanzotSexSaU9cVGrN
         kjWeJosqxiluyOdp2OmhG1jt1bF+ai7QsI7n85E2tR5cgFqQwNGYOqDWHMxLfH3RVOax
         sxmQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rZiHATcqAxSVuhRyTi2E5mTS4Xv1o3Mg3eeyKP3UZ5g=;
        b=gITQAuBGsjgZeqzMxaEHPoneuznKKuZyAqDSdV3YaD+uPX3ztnvs2HN6rIAgcwYVlw
         PeFVmTZDlOVEspxGW4em/XUwstVas9mtKSZsi/7xTxAzjF0o9BOA+nYAGhkFfG41GpGG
         AVLJ2aqtcKCbvlmjGTxUHtQ6ZFvGhc5HT+qsXeOZfEZfbFUabTkpaLtENIK8TgVoHZY2
         GdCzPcNev7hCw6MDx+OMIUuqIPMgtuTnSF4kinxBt5oTTb7D1AVT4na/oyTGSz6tfn8E
         /E8nnBvXJodsi1yGlfRzepimmtww+alOUQvaYPZSWMMnChzSsRxvtudC/ma9N+zqbyBR
         Y/Lw==
X-Gm-Message-State: AOAM530bUeiLrOEv2zhEEzB7IlW+hbFYtSxI9gncLZMWyqyIPCdS23RH
        nHIFZmJEtI3MXx7KET+zWHX+ZoVXWQ==
X-Google-Smtp-Source: 
 ABdhPJwwEf94/agw3SzyxHDnvwR/nCGIQ2OtwLhM46quNqQcjW29ycjh2H/lL7kY+uf03ZjkO0Dd4g==
X-Received: by 2002:aa7:9ecf:0:b029:1f4:f737:12d6 with SMTP id
 r15-20020aa79ecf0000b02901f4f73712d6mr1562865pfq.8.1615612247490;
        Fri, 12 Mar 2021 21:10:47 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 q95sm3541430pjq.20.2021.03.12.21.10.44
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 12 Mar 2021 21:10:47 -0800 (PST)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH] KVM: clean up the unused argument
Date: Sat, 13 Mar 2021 13:10:32 +0800
Message-Id: <20210313051032.4171-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

kvm_msr_ignored_check function never uses vcpu argument. Clean up the
function and invokers.

Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
 arch/x86/kvm/x86.c | 9 ++++-----
 1 file changed, 4 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: on 32-bit do not initialize memory above 2GB
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <nadav.amit@gmail.com>
X-Patchwork-Id: 12136557
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E78F0C433E0
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 07:35:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADEA564DFB
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 07:35:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232431AbhCMHfY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 13 Mar 2021 02:35:24 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53968 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231392AbhCMHe5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Mar 2021 02:34:57 -0500
Received: from mail-pj1-x1032.google.com (mail-pj1-x1032.google.com
 [IPv6:2607:f8b0:4864:20::1032])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 95A6AC061574
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 23:34:57 -0800 (PST)
Received: by mail-pj1-x1032.google.com with SMTP id
 x7-20020a17090a2b07b02900c0ea793940so11830082pjc.2
        for <kvm@vger.kernel.org>; Fri, 12 Mar 2021 23:34:57 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=3HgyLA1cm8PON8AANlntpjJCCSAi8+m9Kx2hbGBjvCk=;
        b=pmNjIHpVg1CP7Ub8WCe50fGc8P5D0xxNpFS0Pgu1fk2mVrcZROoiFLXPL5/omhH9W6
         TfQANfFtb4aX1gsU72ENTYTD/9ldMxioSQQY1Fm/KWQU6c2eRePf8LbLARwF9GNOkaiH
         PO9q0oCBr0fiqJXtLHMAP3fr+4EVjz21O2yRB6ZtbD7u4Zbo9IqLAUddCPLDTcCY8ijI
         M6UgTCsPaft8CyDfYPB5pCGYPSUa+KklCLzJPs49FzXHBoovzEbip9tx9feBR1+YJRKv
         fLB2+mCJcj0W4N3vthW/egQY9IoadwgrQOE5oRojgX8y+xWieRzWdWxaehQz7k4U9ZM7
         KD+A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=3HgyLA1cm8PON8AANlntpjJCCSAi8+m9Kx2hbGBjvCk=;
        b=pAY7PQEh8Pvt3/OmFHxuYPbqFdCPwAv/aDbn5TDciwp1XHFzqRhtnpJLTM+vCm7KDP
         dmMsNVgTpP3a88cMwxjhYqLOt73JPncJ1WXn7XYhS3IWQyU93PUtQYjm5xbXjjsnf21l
         KFxrwX/FtAg9A1/SfyA83p9Sqcf6oHN43qd3vHz5Q+8V/rFrUm4NfUiT1Y3wyrVUMMJA
         r58c+qCo808+kj7rFaY5SPx/JHSVuz85FK6EBMsfBzSK+YNNPUrSnJLV4RhE989eTkrn
         9eN9qyvfbBsZA74NrCyFsE77uZfWfTGmnp7EKodB3jk10GGKVq488Ld3f7x8OzKDABRT
         htAg==
X-Gm-Message-State: AOAM530BHo6WFSMgEIJzXenCrJfXFCe6OwAfxG1zEHXiO9s0OttYVDOE
        UXJIeXOUJXbOb8QC736RSJ0=
X-Google-Smtp-Source: 
 ABdhPJyZNv3HNA4qQy7WRYpHqA58GMlu5y3aXj43gY7aLTm87XBj1UVxYxlJFPc6FAlTRacebq9ZqQ==
X-Received: by 2002:a17:90b:228e:: with SMTP id
 kx14mr2386569pjb.71.1615620896804;
        Fri, 12 Mar 2021 23:34:56 -0800 (PST)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id
 gw20sm4097462pjb.3.2021.03.12.23.34.55
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 12 Mar 2021 23:34:56 -0800 (PST)
From: Nadav Amit <nadav.amit@gmail.com>
X-Google-Original-From: Nadav Amit
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Nadav Amit <namit@vmware.com>
Subject: [kvm-unit-tests PATCH] x86: on 32-bit do not initialize memory above
 2GB
Date: Fri, 12 Mar 2021 23:30:20 -0800
Message-Id: <20210313073020.36984-1-namit@vmware.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Nadav Amit <namit@vmware.com>

taskswitch2 test fails on certain configurations with more than 2GB of
memory.

The reason is that on i386, setup_mmu() creates a hole above 2GB and
does not map that area.

Do not initialize the memory above 2GB on i386.

Signed-off-by: Nadav Amit <namit@vmware.com>
---
 lib/x86/setup.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v2] x86/kvm: Fix broken irq restoration in kvm_wait
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12136215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7CBAEC433DB
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:52:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 498DA64F89
	for <kvm@archiver.kernel.org>; Sat, 13 Mar 2021 00:52:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232627AbhCMAwD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Mar 2021 19:52:03 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52292 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229523AbhCMAvh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Mar 2021 19:51:37 -0500
Received: from mail-pj1-x102a.google.com (mail-pj1-x102a.google.com
 [IPv6:2607:f8b0:4864:20::102a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D5BA9C061574;
        Fri, 12 Mar 2021 16:51:36 -0800 (PST)
Received: by mail-pj1-x102a.google.com with SMTP id
 q6-20020a17090a4306b02900c42a012202so11865649pjg.5;
        Fri, 12 Mar 2021 16:51:36 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=dRSHTuJXO3IQ/87o0yBBwkk9pun6bTQgoCwjJVxdHws=;
        b=qtiWt0VH65vYAQRqSWgkuE/sWwW3Ol15GPaIvTnOeXCaK2iMNYEvDf1RqkLjyOlDrr
         vk1YcWKcaDEg/422Y46tItRwFlerZY/G/uKQDigI7/NLg2GDacaBQcXEjAQVaVtnFRxU
         NexbK/b1wqT8fZWym+XTubm5aZqyu9lnQJXwg41rIhQ/ENgCFMIdynjt8fg+nSoRhD1Q
         tAmzOhgH8r2Ut7Jlbv0hXXhFAVnn982EnI4FgWeXZYQCJEE7XQGQItyQOQxOzA3hljTf
         usvhgpc/6ZTT1jb2jb7oRCh9O3BTGq/CavBULL+sBqXtVN8QEYGzuI/IeUd1nSzep8Vo
         vwGg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=dRSHTuJXO3IQ/87o0yBBwkk9pun6bTQgoCwjJVxdHws=;
        b=iL64SGp/uE2C+Gyhzy8UxRT7/VPpxLJRtca6coc4OXKuw4Nf++QsROClEHUidMS5Ra
         GfSETEsfqiglS5SI0yyttQRWBTTrjMzizNIwRPD+qUCNAmiDD0okmetkJGaH7qsLjTiY
         tNyEReOGwnzrPuf1s7u95obhSHJn6jXJngZ/UVFe1QMyasGXOeq+90ZOPjaN0uXZ2Wt0
         8uT0B8o00r4ldWnE4bO3Zt1pgxvnoJsnJYKyOF3fnjkBXI/1ncUlmWYY/mnxen9fLSn7
         YD2lbL+sz0tIKn/qlJL6QtVvq/rE+uWwgAoam/MJygAWHXWlW2T5YyRrEPnfuI5lU26t
         +Ulg==
X-Gm-Message-State: AOAM533EaxR59QFsPfm3HePXaKMZeH0ZG4B/nHrpmSGcbjwkdTwl/gWl
        dl7CueLpyysRa2QJU0HugS+KPbbDAf8=
X-Google-Smtp-Source: 
 ABdhPJx7CPOsQEzdnXkvuUX6xzBs+2dK2AAtC1rOSPg65XZ2aZYOJHwYyTFLUXpXCo6d4pEFVIc9yQ==
X-Received: by 2002:a17:902:eb11:b029:e4:a5c3:4328 with SMTP id
 l17-20020a170902eb11b02900e4a5c34328mr1084621plb.7.1615596696086;
        Fri, 12 Mar 2021 16:51:36 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 i10sm14380849pjm.1.2021.03.12.16.51.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 12 Mar 2021 16:51:35 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH v2] x86/kvm: Fix broken irq restoration in kvm_wait
Date: Sat, 13 Mar 2021 08:51:25 +0800
Message-Id: <1615596685-22269-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

After commit 997acaf6b4b59c (lockdep: report broken irq restoration), the guest 
splatting below during boot:

 raw_local_irq_restore() called with IRQs enabled
 WARNING: CPU: 1 PID: 169 at kernel/locking/irqflag-debug.c:10 warn_bogus_irq_restore+0x26/0x30
 Modules linked in: hid_generic usbhid hid
 CPU: 1 PID: 169 Comm: systemd-udevd Not tainted 5.11.0+ #25
 RIP: 0010:warn_bogus_irq_restore+0x26/0x30
 Call Trace:
  kvm_wait+0x76/0x90
  __pv_queued_spin_lock_slowpath+0x285/0x2e0
  do_raw_spin_lock+0xc9/0xd0
  _raw_spin_lock+0x59/0x70
  lockref_get_not_dead+0xf/0x50
  __legitimize_path+0x31/0x60
  legitimize_root+0x37/0x50
  try_to_unlazy_next+0x7f/0x1d0
  lookup_fast+0xb0/0x170
  path_openat+0x165/0x9b0
  do_filp_open+0x99/0x110
  do_sys_openat2+0x1f1/0x2e0
  do_sys_open+0x5c/0x80
  __x64_sys_open+0x21/0x30
  do_syscall_64+0x32/0x50
  entry_SYSCALL_64_after_hwframe+0x44/0xae

The irqflags handling in kvm_wait() which ends up doing:

	local_irq_save(flags);
	safe_halt();
	local_irq_restore(flags);

which triggered a new consistency checking, we generally expect 
local_irq_save() and local_irq_restore() to be pared and sanely 
nested, and so local_irq_restore() expects to be called with 
irqs disabled. 

This patch fixes it by playing local_irq_disable()/enable() directly.

Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * select the alternative fix

 arch/x86/kernel/kvm.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
