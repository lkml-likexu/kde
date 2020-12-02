#### [PATCH v2 1/9] KVM: x86: Add AMD SEV specific Hypercall3
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11941711
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60DC5C64E90
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 00:47:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1752E20809
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 00:47:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ACpLDEq+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730939AbgLAArJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 19:47:09 -0500
Received: from mail-bn8nam12on2071.outbound.protection.outlook.com
 ([40.107.237.71]:20033
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726316AbgLAArI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Nov 2020 19:47:08 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=QAdQ4wqLarmUB/jtW4hu4fAn/yoPMUCSAPguKo2pQbM0Am2X7TPykhPY+57gvZRYvxP+qsbBCYIxCSPraqYoe321bR2THIiK58bzLHsbXZ/mD3xebV/mQyQCljs5Ex5OC0SEiEW85dzgLywtH5DD+vP0fHHVuqpv8OB0h4+j/+yRx4U7vy+jPJYIRYF/Uv6xX6Zd5+L605va3VKasTYUm66TH5q2hCfeXURll+3m72EnBBe60qceGiLzrsSjWhJEaOmZWF7xET897DValooavUJTArC0S/Id7MkJQqqiFV/FvyWYVhIfIEZiEGatnuQ6b68y3tAhVpIAF7Zpl8i2oA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=djYOIZIAe+UUpzeBZtr/RMxOzG5cL+NruPXwZsscQuI=;
 b=Sh1wW+KUQpAU0eOUUEo9DGxv066uQJ1i7ne8mAxPl3UNLMvaPpqvgZJ+zj92B3FjWH2YWsZVOBOQoz0nP8jrDYVGXKLE2JJg6r85N0ccIlkJOr/37iIOml8EPcrPjOxR0PxPeBnBfZ8byI8Cqi1e8h8pLC4FZfUi9ZvmjOfWUSXO3koCm9THKa3qclvUsIuB0huLtNdBr2MIfJxY16+iHJonpOSQttejG24WH3mireQSo2sEkouPZrjrP7Dt5wmBvPcL9O6FzpBqh4gSOWvsTPYDQPCUf47gYKeuNVFnyFKxuYf6BR83j8SAYrH502S+5mdlvxtoLu62F6BBsm4vfA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=djYOIZIAe+UUpzeBZtr/RMxOzG5cL+NruPXwZsscQuI=;
 b=ACpLDEq+C++jhDTgzdp2Dldz5hJ5VJClvuC1ylXbZ9yejnW9olbiFpnVccgLCXO+FRi9kQymfSlFZAxZLV+Hq0THEt1f9r09en9TYsAhlkizZQmbYhD3YSLLlxDoRA0yPM1bkOx2A+J1SpjPlxHoKSTWADn/W3za6mQbQdvx0h8=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4573.namprd12.prod.outlook.com (2603:10b6:806:9c::24) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.22; Tue, 1 Dec
 2020 00:46:14 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3611.025; Tue, 1 Dec 2020
 00:46:14 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, brijesh.singh@amd.com,
        dovmurik@linux.vnet.ibm.com, tobin@ibm.com, jejb@linux.ibm.com,
        frankeh@us.ibm.com, dgilbert@redhat.com
Subject: [PATCH v2 1/9] KVM: x86: Add AMD SEV specific Hypercall3
Date: Tue,  1 Dec 2020 00:45:35 +0000
Message-Id: 
 <b6bc54ed6c8ae4444f3acf1ed4386010783ad386.1606782580.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1606782580.git.ashish.kalra@amd.com>
References: <cover.1606782580.git.ashish.kalra@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DS7PR03CA0097.namprd03.prod.outlook.com
 (2603:10b6:5:3b7::12) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DS7PR03CA0097.namprd03.prod.outlook.com (2603:10b6:5:3b7::12) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3611.26 via Frontend
 Transport; Tue, 1 Dec 2020 00:46:13 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b89d85f9-4c4d-45fa-8986-08d89592818e
X-MS-TrafficTypeDiagnostic: SA0PR12MB4573:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4573AA64664736C04FC65E188EF40@SA0PR12MB4573.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:3513;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 M+8tDGhh/qisGQzsVHvLuLkCd9GVg8ycvrmtM0HoUZwLTHx2TMjSJPvXtusS3dbTnQ/RjbmX5XcT8PRZOE3eJ/I4F/E3hH2L5QFjC+Z9tx6biQ3mc93b+mHWEZT4Nb9WWOjvji4rW6inj8qWUPSWh0EEayb8LI9JyNQyuzc273il+x4soOB2l91FmTL8WXF7eBQIZouiITvyDo6unbZ0oRGyVL9GG8V0SAUzgBmVRkEwQmLzNpBGxLRk46Wb1ca3Llk3W/jg2VLd5y6tVqFPr0ToDTCb7R8vMlWJFWMqaELNY0uIjMoTwHFpH+/NnzuBwexEx3oveHmVT27M0llw4A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(346002)(376002)(136003)(396003)(39860400002)(478600001)(6486002)(7696005)(316002)(4326008)(956004)(6666004)(8676002)(186003)(16526019)(8936002)(52116002)(66946007)(5660300002)(7416002)(2616005)(86362001)(26005)(2906002)(36756003)(66556008)(6916009)(66476007);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?PsA3PFI3dSg5v54/I0lW6nKo5SoaTk?=
	=?utf-8?q?L6hHqX4BnpZ39vzJMzOVp8UIczHADLmS+AJQRFj/BChZVqGegtYJK/aZNh0AAhqqj?=
	=?utf-8?q?iruvY1aenZXA5Irfs0tiiD3q9KJtQVDjGcDJdWNynn17zaFWVNWsWnXzWKRxGMsHb?=
	=?utf-8?q?8HeGT+gbaC7sldMXkvFX/aaMD1FmSlmQ3lxG8wJGxeOPCvMIHppt1OpQ3RKUngEM0?=
	=?utf-8?q?j900felB9Wn2iee90TJ+F0PRz2JMcmVJGL3RSPmvrV3T+CYMAss1ACSCcgIqs9vK0?=
	=?utf-8?q?wcuYHE6aUbv2sEzx/7ZYpspOnkEogFnJ/yRArzZcfuOG9atmXaXwJj64S8hjDcoMr?=
	=?utf-8?q?BGZoeKS3o2aKPGiGlzUD9o9Zgx3S4F0mTSzLqM8jVZjUj5IgusFXo8k+sRsGPnYvk?=
	=?utf-8?q?0Y/+XTTvu9xCV8ZhbMYXQylr3+Lv7CmPSA0NKsStBnoGMPuI5RaFeFGKw6Wm6jQy3?=
	=?utf-8?q?tm9Z0n66pWcK2RNisJ1+a1iH78byyUZ73KNAkjIjSc/VT8Vro/60YiGLJUgVDHYra?=
	=?utf-8?q?3XqDKCNkcp8mEeQ02XPSpVUlWCZKJ+XNkd3R7krDVuSkVEHQLOWMCtv09g0DblGsX?=
	=?utf-8?q?1Pppzvb859LgQ9hu+8GqWUvqN+91oiH0Ew7rst+RpqJ2zd8vN5jwOYaLfIlugN4mU?=
	=?utf-8?q?Z6lfpUckknUHdcN6WFlhBjzC8J9EJMb7PAtqtQCBmG2ljJGjktJeaVeWR+zxBnTll?=
	=?utf-8?q?1Gso27IVPwpr1dkXDdI5KDynYl+pmn9FISt6FyclnsyinCTiN7MUHKSIvUjcQQA+7?=
	=?utf-8?q?zdc3Vb3DhFr/uF4iHaH7qE2NyxizXbV1C7UmAGNdMDOnE9fKNGzwTSHyO2PUN8Pdf?=
	=?utf-8?q?mh5peJjlHIndCAqJ9DbyZW9vKBjKP8nD6miEEfvpL5g8fi7BwOv1vu9WnPD166Af7?=
	=?utf-8?q?eTjUrkJ8rzhBXi1zJE9xmak8lPYm35FNr+lnvy9aq38CkNOOO3qzfgE1BhObFBua1?=
	=?utf-8?q?0h9LOVEsI2JPHHmLZ3/?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b89d85f9-4c4d-45fa-8986-08d89592818e
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 01 Dec 2020 00:46:14.5910
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 PVWFKuADWpkSrv7Xba8xSEOA9Cix+/6Q7ELMttiaS/3GYG64dARwPt5kh5Cn+vXbQwx0ISuRpSWFudmVtbie1Q==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4573
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
#### [PATCH v3 1/1] vfio/type1: Add vfio_group_domain()
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11941747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F3097C71155
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 01:32:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3C9E2085B
	for <kvm@archiver.kernel.org>; Tue,  1 Dec 2020 01:32:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731176AbgLABcn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 30 Nov 2020 20:32:43 -0500
Received: from mga04.intel.com ([192.55.52.120]:24249 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726063AbgLABcn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 30 Nov 2020 20:32:43 -0500
IronPort-SDR: 
 238u+3EXx0FGTg/nL03cag/rXEPTr6ZXr6I4j+2e6b7NguuFRFFtYp5iPIS6l4cLqwqxTQaCXs
 pEHOXoGSOrUg==
X-IronPort-AV: E=McAfee;i="6000,8403,9821"; a="170178503"
X-IronPort-AV: E=Sophos;i="5.78,382,1599548400";
   d="scan'208";a="170178503"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Nov 2020 17:31:02 -0800
IronPort-SDR: 
 bdckBIAfENOt7pyp86oCzSrk4igrIIntskd0tH0TbhDy0SsgWsLlcW1F8lLym2VWLWMFYi9bY9
 b5tAiAafunCQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,382,1599548400";
   d="scan'208";a="434477472"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga001.fm.intel.com with ESMTP; 30 Nov 2020 17:30:58 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v3 1/1] vfio/type1: Add vfio_group_domain()
Date: Tue,  1 Dec 2020 09:23:28 +0800
Message-Id: <20201201012328.2465735-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the API for getting the domain from a vfio group. This could be used
by the physical device drivers which rely on the vfio/mdev framework for
mediated device user level access. The typical use case like below:

	unsigned int pasid;
	struct vfio_group *vfio_group;
	struct iommu_domain *iommu_domain;
	struct device *dev = mdev_dev(mdev);
	struct device *iommu_device = mdev_get_iommu_device(dev);

	if (!iommu_device ||
	    !iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
		return -EINVAL;

	vfio_group = vfio_group_get_external_user_from_dev(dev);
	if (IS_ERR_OR_NULL(vfio_group))
		return -EFAULT;

	iommu_domain = vfio_group_domain(vfio_group);
	if (IS_ERR_OR_NULL(iommu_domain)) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	pasid = iommu_aux_get_pasid(iommu_domain, iommu_device);
	if (pasid < 0) {
		vfio_group_put_external_user(vfio_group);
		return -EFAULT;
	}

	/* Program device context with pasid value. */
	...

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/vfio.c             | 18 ++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 23 +++++++++++++++++++++++
 include/linux/vfio.h            |  3 +++
 3 files changed, 44 insertions(+)

Change log:
 - v2: https://lore.kernel.org/linux-iommu/20201126012726.1185171-1-baolu.lu@linux.intel.com/
 - Changed according to comments @ https://lore.kernel.org/linux-iommu/20201130135725.70fdf17f@w520.home/
 - Fix a typo https://lore.kernel.org/linux-iommu/DM5PR11MB143560E51C84BAF83AE54AC0C3F90@DM5PR11MB1435.namprd11.prod.outlook.com/

```
