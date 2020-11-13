#### [PATCH 1/1] vfio/type1: Add subdev_ioasid callback to vfio_iommu_driver_ops
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11899023
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C56B9C388F7
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 05:39:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 714BE2076E
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 05:39:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729541AbgKLFi4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 00:38:56 -0500
Received: from mga18.intel.com ([134.134.136.126]:53611 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726457AbgKLCbR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 21:31:17 -0500
IronPort-SDR: 
 1Vbx+1fYqMdm+i0eNsQuRrVP+w7/4XAzEjqjLlS60VZmAVBrSZEBV2Z+wX+yZ3mcOiDJWafhkl
 RBWBR/AGQI0Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9802"; a="158027947"
X-IronPort-AV: E=Sophos;i="5.77,471,1596524400";
   d="scan'208";a="158027947"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Nov 2020 18:31:14 -0800
IronPort-SDR: 
 RqmfoNvjRlzJ+AZ0ZVwfPxQdbl9++xpGWOTNcFQUqDkXqk2nSnkuemt/WizPYJwrPXhU8GCLmI
 pSM7JC62A6xg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,471,1596524400";
   d="scan'208";a="366450979"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by orsmga007.jf.intel.com with ESMTP; 11 Nov 2020 18:31:10 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH 1/1] vfio/type1: Add subdev_ioasid callback to
 vfio_iommu_driver_ops
Date: Thu, 12 Nov 2020 10:24:07 +0800
Message-Id: <20201112022407.2063896-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add API for getting the ioasid of a subdevice (vfio/mdev). This calls
into the backend IOMMU module to get the actual value or error number
if ioasid for subdevice is not supported. The physical device driver
implementations which rely on the vfio/mdev framework for mediated
device user level access could typically consume this interface like
below:

	struct device *dev = mdev_dev(mdev);
	unsigned int pasid;
	int ret;

	ret = vfio_subdev_ioasid(dev, &pasid);
	if (ret < 0)
		return ret;

         /* Program device context with pasid value. */
         ....

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/vfio.c             | 34 ++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 57 +++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  4 +++
 3 files changed, 95 insertions(+)

```
#### [PATCH 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from userspace
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11901913
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AF563C5519F
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:22:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 393602224A
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:22:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="jcvsLl3n"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727412AbgKLWWj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 17:22:39 -0500
Received: from mail.kernel.org ([198.145.29.99]:57730 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726108AbgKLWWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 17:22:39 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 03E4222201;
        Thu, 12 Nov 2020 22:22:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605219758;
        bh=ikfFZNVtjUtyQF8SBCZ0Dz3rwfiOAQDe8VeQcyYVico=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=jcvsLl3napnHvBJ7fww6zbXIz7iKOChbz22HhKf6Pih2mTY9Zt1fxNIDtWS3Bs3vH
         0JoA9Y8A7tDs0HPErJe3KXadLvAHuJ0QCM0DWwYXSA3XpN9VNkjwDFs0eN2b/27IKb
         tgomcGAxzuk0GZICirDf23I3COBwOxUWto6H5Z7I=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kdKzE-00ABHn-7R; Thu, 12 Nov 2020 22:22:36 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peng Liang <liangpeng10@huawei.com>, Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from
 userspace
Date: Thu, 12 Nov 2020 22:21:37 +0000
Message-Id: <20201112222139.466204-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201112222139.466204-1-maz@kernel.org>
References: <20201112222139.466204-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, liangpeng10@huawei.com,
 will@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kernel-team@android.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We now expose ID_AA64PFR0_EL1.CSV2=1 to guests running on hosts
that are immune to Spectre-v2, but that don't have this field set,
most likely because they predate the specification.

However, this prevents the migration of guests that have started on
a host the doesn't fake this CSV2 setting to one that does, as KVM
rejects the write to ID_AA64PFR0_EL2 on the grounds that it isn't
what is already there.

In order to fix this, allow userspace to set this field as long as
this doesn't result in a promising more than what is already there
(setting CSV2 to 0 is acceptable, but setting it to 1 when it is
already set to 0 isn't).

Fixes: e1026237f9067 ("KVM: arm64: Set CSV2 for guests on hardware unaffected by Spectre-v2")
Reported-by: Peng Liang <liangpeng10@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
Link: https://lore.kernel.org/r/20201110141308.451654-2-maz@kernel.org
---
 arch/arm64/include/asm/kvm_host.h |  2 ++
 arch/arm64/kvm/arm.c              | 16 ++++++++++++
 arch/arm64/kvm/sys_regs.c         | 42 ++++++++++++++++++++++++++++---
 3 files changed, 56 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Introduce mask_cr3_rsvd_bits to mask memory encryption bit
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11898865
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA511C4742C
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 01:52:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D13D2076E
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 01:52:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ukb7n55/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727842AbgKLBb4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 20:31:56 -0500
Received: from mail-dm6nam11on2054.outbound.protection.outlook.com
 ([40.107.223.54]:62305
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728061AbgKLA20 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 19:28:26 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=TM7ntXbpHdBfsb5g2ahkmSpX/fTsMBg4r99QNX6RPL34v7q6cxoNkNLpSgz6mz6HjZpU7cADDFKbW8vdX9aRKPlK2q8tQ+mC1bTk3AZ/QHIVo33cjKqJtp4XP5k5v/CjfFYsQx1rHGsT6yKc8Wk1xQzUvs+7el4LY4mMmUDIcHigOubCq1Nxr8r6UIXAtbIP2kg0m61djO2A4XcZlwrexY/N8E/zsGkR5aklg9JsSl+7s8jNZVPXcyw60x4///cJ34Y5qFhe0lnkinpRMPBUjRHwJJbrIQAz4pTq7unpcrEg7zzQF4tNs+QH7YOkvJp7ILzMIWvcKSP9wyD8X3S3Sg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=r0PZSI69jL+c1lpI8Sax5WEdK5iJzpeRzSv2b6GQz5I=;
 b=oPAje0R64EQpHxgL+Wl1lCzAJ8yvS+MOe4SMsRGfaOdnA52FYYMDkgpHnWv+EXTMm8bCw/eYxZ7Ju7lGKexP8FvejPFgqP+lWbx6Xz3p4QqhoYV+2S7L+dApTEr3bZYb5ng/VGDBfPLtd4eqYEisFSN2FaYzxDvKIrQFiJS8+GsZiBH8QfdtyJ3W3+i6/dq7AWWwGliLnyf9iCLAh8WrecIiQ4rAgSxGya6DcUQ09p99kI0ZSF6nnRssf/5cOQRO50tqQIjtq0b8qkmtrFAK3zWVoPC6DTcjrbSLpA4zGyNx5IgkZigxRw5Z6cmouo3oY+Fyz2tGMv1g1XzbyydzbA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=r0PZSI69jL+c1lpI8Sax5WEdK5iJzpeRzSv2b6GQz5I=;
 b=ukb7n55/EuOAy94TfRf6y/gzvWHddXTmjyWTKWWcPE1OOz5OOuoar2we1aCUUg7aN4a+bI1WePsR34c35PdIYbOwprF524Lmy5BgEQIgjsEdtVN/0+5QCjQ3CdAYyypmuyDlksKa8osMoCZDktUu6YBaSehav4h68HpbTnJsO74=
Authentication-Results: google.com; dkim=none (message not signed)
 header.d=none;google.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN6PR12MB4685.namprd12.prod.outlook.com (2603:10b6:805:b::20) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Thu, 12 Nov
 2020 00:28:21 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3541.026; Thu, 12 Nov 2020
 00:28:21 +0000
Subject: [PATCH 1/2] KVM: x86: Introduce mask_cr3_rsvd_bits to mask memory
 encryption bit
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: junaids@google.com, wanpengli@tencent.com, kvm@vger.kernel.org,
        joro@8bytes.org, x86@kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de, vkuznets@redhat.com,
        jmattson@google.com
Date: Wed, 11 Nov 2020 18:28:19 -0600
Message-ID: <160514089923.31583.15660520486272030205.stgit@bmoger-ubuntu>
In-Reply-To: <160514082171.31583.9995411273370528911.stgit@bmoger-ubuntu>
References: <160514082171.31583.9995411273370528911.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR07CA0125.namprd07.prod.outlook.com
 (2603:10b6:3:13e::15) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 DM5PR07CA0125.namprd07.prod.outlook.com (2603:10b6:3:13e::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Thu, 12 Nov 2020 00:28:20 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: b40dfe3a-64c8-4ef0-9489-08d886a1dbd1
X-MS-TrafficTypeDiagnostic: SN6PR12MB4685:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB4685C5E31ACA7BC747A6779F95E70@SN6PR12MB4685.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 4zoGRSAC+YIyxtGxIH/nm77iu0zojP87ljj3T6AAu1AUxpdDKfRM1EvxMH+WS5fUcnS8Mflgt0hB0XeqeHEmom7XPB8oexmYOPA+sG+gKthSI9N+ZvUvxuSKKqwpcZQmKSw8vs3dVC9YPQmd/Tnu0b1gXXkN9IT5IgpW4Gw0cVZ5xy+I2necpyVz3PZsK83dFPQdSOnYQ0l+BUPDYJDfxU0OUx0+VAXCvW53OLq6uouwWTYgF0euqOsI3kQGkIMJxw1sF08izpYtcrZVnfQbACLshcAqrC0ZbiudSafyOJ7EDYxcfbGxuMoC9vHzHg7H
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(7916004)(366004)(39860400002)(136003)(396003)(346002)(376002)(83380400001)(52116002)(186003)(9686003)(26005)(6916009)(7416002)(66946007)(44832011)(16576012)(33716001)(103116003)(956004)(66556008)(4326008)(66476007)(316002)(2906002)(16526019)(6486002)(5660300002)(478600001)(8676002)(8936002)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 KE7+Khfn3DD2DwKYm0pfoBykKtGn6Lge3/3BQdEMGUl6+4isfP9aQMEGTKBJ3a3JQ/8r9qLelPbwVXMLH8PCaWXBCpWvjQ7IXF9jgKiJ5s0wG6h06FrBlJxxsWWmoR9IgLBoRA654R8vQvg2YTWTlV1RnRCUWPI7YyMpwYV11hV7SkpaBSKCc/UaaU+wBN4zsvhtQAL+Qq6n+0vWPgWUQCrsJ9e4c27zdOTUatQTfH29TE+gmWbiRddYMDmcil6Qhdnx07Oa9atRYlgyjr+mecx/6oMfh1oqXyYQbZCg2pbUjHZssE03noW3wL+19RnTi0t/b8ZeZGLlV6SgCQbCflFUmQ/sMHqrUQhbVuPV6tbCBwE5OCxVaxS9sp9uqDuSGeCTcadXUV5H4kM/tC+1jmktwpdbL8ws7RMrvUGzXyMfgHQmchKhD9dWjuAjsgLJi9iVA7ZYL6B1UNYJPQKHE2f2VbfAwjTtqF3OGWtGzX4H2Uy8CMUQCg94/4BG0LGs/maRm4i4soQzyjCmO2QF+ED5l3LINH4ktPWpBLOsX4dnHfwQNKPQJ6WACjiR6g1eFN/c13WPkq7YFKIdjx+r51JvD4B3t1NWcVYdkvNojnAom5EEOdbTNX+IbNnXKhmQJVKWBT2RegCXuAaX7hkE2g==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 b40dfe3a-64c8-4ef0-9489-08d886a1dbd1
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Nov 2020 00:28:21.1675
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 j9CCsHPDuuDMTyEf/CqTKbo9NB58TyOrvskRBwX+mwvsaoGzhqbOhXi4SSV0OrIn
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB4685
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SEV guests fail to boot on a system that supports the PCID feature.

While emulating the RSM instruction, KVM reads the guest CR3
and calls kvm_set_cr3(). If the vCPU is in the long mode,
kvm_set_cr3() does a sanity check for the CR3 value. In this case,
it validates whether the value has any reserved bits set.
The reserved bit range is 63:cpuid_maxphysaddr(). When AMD memory
encryption is enabled, the memory encryption bit is set in the CR3
value. The memory encryption bit may fall within the KVM reserved
bit range, causing the KVM emulation failure.

Introduce a generic callback function that can be used to mask bits
within the CR3 value before being checked by kvm_set_cr3().

Fixes: a780a3ea628268b2 ("KVM: X86: Fix reserved bits check for MOV to CR3")
Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/include/asm/kvm_host.h |    2 ++
 arch/x86/kvm/svm/svm.c          |    6 ++++++
 arch/x86/kvm/vmx/vmx.c          |    6 ++++++
 arch/x86/kvm/x86.c              |    3 ++-
 4 files changed, 16 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: x86: Introduce cr3_lm_rsvd_bits in kvm_vcpu_archFrom: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11901895
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 830EDC5519F
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:18:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14ED222201
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 22:18:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="uwApJCM8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726050AbgKLWSB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 17:18:01 -0500
Received: from mail-dm6nam12on2056.outbound.protection.outlook.com
 ([40.107.243.56]:35937
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725894AbgKLWSA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 17:18:00 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=NLwogS2KucuCB82KAIneroQwZi6+NyTaZLpAVm+14MB6wyFWHK9CKaXr9eXB9MpIwhIQqxpofzgv2iPXlc7z2GUAzatckJLfVHD+/Flgnn+leRDiQJZDMFCdbHGS1Oh3+8Ail+ZJB7jkC8gO51yeKmNEUXRpeYRoukPHsLTjyjVVaLt5fwiFJWZ8AjNAyfF8eeMitm6n+oEW7pHP4aPrMS4XYsSNtvUrHKdONYgHfRJfZp2K6pBhygImKmdWfQdXbaL+BaYaBixWs866R8pi7ekkoVK6vANXaA+H6BETjiJL2PRws4HIrnONd+naPZjQ9bGXG4KD4c8TD3tS8Txe8Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ho/I97presCR0gzHfkvBn/U6m7Yxt4gD1SkyAqie6AI=;
 b=mKbneU4C/7Ko24pPc+hX9/cabrcnVid2RuoAtfpbk3UOBg1dzulwX7njSLLK1jYAA+HN/zu6r9r5FcQ710NmOT46nYLzLUPXbSuOuIm7UXo0S/QVvq+FIhQ6DBhoDP+rxuzdlPfcHO88sOcpnDYKT4PZ4DXZ13ol+glsMfez0WCE+aoG384/oAZk7OskxiFUzgvjv69MuSY8Ewxg5oU8NMiOWPnRulqd0ylTgFK9is4mmZohOyRxGQuMxg/cs5+iI6EBG6zAAJKBFgwDEtXMhNWHGBYbp1lHqBMmqGPsobHmNbE6XIEtH5hL3AP7DEYvGOFFvLqbbxNL6Pd0hOVGpQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ho/I97presCR0gzHfkvBn/U6m7Yxt4gD1SkyAqie6AI=;
 b=uwApJCM8RFwzcvxvZOVr4QYIqRxUQ7oFKnGXmnrTskFkaBXTS+D9aGxylVr+3TnJLJ4FA4Em3mn+/v/3tcfdQMgqsy3a27wZ7EycyDelqBkmlsBoYAmoZkzmNuvU6ayGpOTNFUqus9QVhW+fXC/7JaIEUPsNki5xcWSGYt0PjrU=
Authentication-Results: google.com; dkim=none (message not signed)
 header.d=none;google.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4445.namprd12.prod.outlook.com (2603:10b6:806:95::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Thu, 12 Nov
 2020 22:17:57 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::d877:baf6:9425:ece%3]) with mapi id 15.20.3541.026; Thu, 12 Nov 2020
 22:17:57 +0000
Subject: [PATCH v2 1/2] KVM: x86: Introduce cr3_lm_rsvd_bits in kvm_vcpu_arch
From: Babu Moger <babu.moger@amd.com>
To: pbonzini@redhat.com
Cc: junaids@google.com, wanpengli@tencent.com, kvm@vger.kernel.org,
        joro@8bytes.org, x86@kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, tglx@linutronix.de, vkuznets@redhat.com,
        jmattson@google.com
Date: Thu, 12 Nov 2020 16:17:56 -0600
Message-ID: <160521947657.32054.3264016688005356563.stgit@bmoger-ubuntu>
In-Reply-To: <160521930597.32054.4906933314022910996.stgit@bmoger-ubuntu>
References: <160521930597.32054.4906933314022910996.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN6PR04CA0088.namprd04.prod.outlook.com
 (2603:10b6:805:f2::29) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN6PR04CA0088.namprd04.prod.outlook.com (2603:10b6:805:f2::29) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Thu, 12 Nov 2020 22:17:57 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 198d7575-b613-44c0-ccb8-08d88758cf3a
X-MS-TrafficTypeDiagnostic: SA0PR12MB4445:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4445A4E8E0A6A20BB4BD625A95E70@SA0PR12MB4445.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 y40xjwGxMMjt2t+zg8AVVnwgJZ3Ai2M3AEawUPIAzUjvewa5b3U/45c6uj5k9X3VsGEVhlvIkEaueAM7RzWC7vPjQQCGXwk1RofZc3MClqcf/RbrBlaELJ5b6OYQPLXsBz3TrR1N5TxNDj9GkH7bkfRXalURyXpJHfROES/eiabKcLZXZUm4Jmqs45ndqw2Ma8mIvY+pZSguv/t4HtP/f5Ww81e9K8NdEq1RYSzeZFtlIQ/luS61ykTD+c7MNkX6JW1Nxw0qGIjW1wqxAsP8eHQIlaDoUItFZbHSeTDYGU+QYWI0OT+t3zdtgwobyfeNlbWsM6ddATn8t5q/f5UoLQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(4636009)(366004)(346002)(376002)(396003)(136003)(39860400002)(52116002)(33716001)(16576012)(9686003)(16526019)(8676002)(86362001)(6486002)(103116003)(478600001)(956004)(6916009)(2906002)(66476007)(8936002)(66556008)(316002)(7416002)(26005)(4326008)(83380400001)(44832011)(5660300002)(66946007)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 DjbDoBq67y2+93lCu/r7zJL3Igt1xVigX3R+WqdaCXMOuS/43owYGMs0UTD72M0dHjdoPn8LeD0qI0c1pwHBIHY9oF3QwK8+2sjPMG1rkc33LNyvEZpd8xH2eO0JgYK9C6EV0RlvVp53BoKM6V2Tr91L8WskdVhfeCgD0NiJ5yqa4lrxjs1ZPssd94BOyqdBNOnGIBguCwFI8hMhhMM2EIwDQwZW12DJokKDSL/1puK0GZQ0kdfvlPLRs8UJqjQ94JMa1RcvXvcBvn8hkLYklK95G3rC/oroywZiVoT2HhPM4WLYGQaOt8dOEU80T7Ol514sDVWKkJLBCu4A0yTBagnD6I6utYtaKVyw2k/cu9z2WJBJTDnOvf7ZysiBTw3o7yF7Q5pFTdQrSYQp48JUnGMHQyXw3UXXyhhn84yhMQgLih97zlxjUA7x6fZT/0X/b5wd+DDywukHzKeQK/XpVAMFYE5ISWzaZwc1DjRk7hAFkXXyhY/xlRJh3gqGPn2Rl7H1HOWxelQ1WUCqnw+/N7YHXoSN2HVXuw4HmYnY28FBC/DPKx+tapC5fe58ZPeRxBpUcALCcOK1llp2jJtUAV1pqRIvXSJleeTqH8Og0a1fPQb2hR5aouWnKarGQeolaLxJU8uYzJdwLuHsc+75FA==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 198d7575-b613-44c0-ccb8-08d88758cf3a
X-MS-Exchange-CrossTenant-AuthSource: SN1PR12MB2560.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Nov 2020 22:17:57.7913
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 rkN5tozXyu+VJKaahHDE8l8BDBg4hNikH53Hhb0QZmXT4ok74WfA57E0Kd5oOlCm
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4445
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SEV guests fail to boot on a system that supports the PCID feature.

While emulating the RSM instruction, KVM reads the guest CR3
and calls kvm_set_cr3(). If the vCPU is in the long mode,
kvm_set_cr3() does a sanity check for the CR3 value. In this case,
it validates whether the value has any reserved bits set. The
reserved bit range is 63:cpuid_maxphysaddr(). When AMD memory
encryption is enabled, the memory encryption bit is set in the CR3
value. The memory encryption bit may fall within the KVM reserved
bit range, causing the KVM emulation failure.

Introduce a new field cr3_lm_rsvd_bits in kvm_vcpu_arch which will
cache the reserved bits in the CR3 value. This will be initialized
to rsvd_bits(cpuid_maxphyaddr(vcpu), 63).

If the architecture has any special bits(like AMD SEV encryption bit)
that needs to be masked from the reserved bits, should be cleared
in vendor specific kvm_x86_ops.vcpu_after_set_cpuid handler.

Fixes: a780a3ea628268b2 ("KVM: X86: Fix reserved bits check for MOV to CR3")
Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/include/asm/kvm_host.h |    1 +
 arch/x86/kvm/cpuid.c            |    2 ++
 arch/x86/kvm/x86.c              |    2 +-
 3 files changed, 4 insertions(+), 1 deletion(-)

```
#### [RFC v1 1/3] vfio/platform: add support for msi
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11900917
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,T_TVD_MIME_NO_HEADERS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB856C6369E
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 18:01:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C8712223C
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 18:01:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=broadcom.com header.i=@broadcom.com
 header.b="QtWpuolF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726984AbgKLSBh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 13:01:37 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35110 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726426AbgKLR7K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 12:59:10 -0500
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 88836C061A49
        for <kvm@vger.kernel.org>; Thu, 12 Nov 2020 09:59:09 -0800 (PST)
Received: by mail-pf1-x441.google.com with SMTP id q5so5247370pfk.6
        for <kvm@vger.kernel.org>; Thu, 12 Nov 2020 09:59:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=PuUUU3p4QVu/Pg/pLrotXd8fVuKl/UFHWCvdQMnFV/A=;
        b=QtWpuolFjfwWayF+iM+Kx5bF9ELZg3e0z2vz7ZE3EnonI8SqN9JDCJ7amklQIUFErC
         5phfYVRzX+u8RVLCwrLIHaUy9bLTY/IitELKWrf2iZa6Z4SoSIE9NOvVM/CrXWx+2I4H
         g0k2q4p3Bu82m1zXEtFMFYmReiUmBmgQM9tlU=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=PuUUU3p4QVu/Pg/pLrotXd8fVuKl/UFHWCvdQMnFV/A=;
        b=awulOsso5FuYhEc4PAkNmzcc2Zuwz0cAJCR8JZOrjjiIXmxAxHc0BBueUsc8p5isjC
         uzSbZy5bGxG5IwYN7GOTob+5mr1GCAaotxeR4rbjnY/m7OhvD5IXF3x4Egigog2ukZkI
         0D5MVZHrKsvdpoBO5a1d/ywygoLkiXf2cnPAUZjLXvvlNt7hbVXkc0pfJoueA1UbVaeG
         xmu9C/jvaRQ20FcktDUDnNVDCynLrk3D6fZg55UQDFJJENg4+Jx1p140FZc0q/114Apq
         6zlyaNs0biyzwC35i5iL25cB2/1vUPx3Hk2pyc5tTluU0MwNM+ZsfBCpocnbS6H3XAic
         oRIA==
X-Gm-Message-State: AOAM532S1Uz68unJiib7EZLDTlqCQSUL66M/shu4RbhHiJgZEnrzoPxx
        jZRGy8fW7vb75eX3VJLXp0u76A==
X-Google-Smtp-Source: 
 ABdhPJy1GJBC7yz+eSn937IoFvW91G5+hjuiJAzTKYCu6D5Yy1VQny5ExJzX6Osa660WGp7YCp6G7A==
X-Received: by 2002:a63:a65:: with SMTP id z37mr518139pgk.361.1605203948839;
        Thu, 12 Nov 2020 09:59:08 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 r6sm7237894pjd.39.2020.11.12.09.59.05
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 12 Nov 2020 09:59:08 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC v1 1/3] vfio/platform: add support for msi
Date: Thu, 12 Nov 2020 23:28:50 +0530
Message-Id: <20201112175852.21572-2-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201112175852.21572-1-vikas.gupta@broadcom.com>
References: <20201105060257.35269-1-vikas.gupta@broadcom.com>
 <20201112175852.21572-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSI support for platform devices.

Signed-off-by: Vikas Gupta <vikas.gupta@broadcom.com>
---
 drivers/vfio/platform/vfio_platform_common.c  |  84 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 238 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  23 ++
 3 files changed, 331 insertions(+), 14 deletions(-)

```
#### [RFC] Further hack request_interrupt_window handling to work around kvm_cpu_has_interrupt() nesting breakage
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11900139
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_SANE_2 autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC58DC388F7
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 13:03:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30A4122201
	for <kvm@archiver.kernel.org>; Thu, 12 Nov 2020 13:03:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="OznJhtF0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728254AbgKLNDp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 12 Nov 2020 08:03:45 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45826 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728134AbgKLNDo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 12 Nov 2020 08:03:44 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 92E5EC0613D1
        for <kvm@vger.kernel.org>; Thu, 12 Nov 2020 05:03:44 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:Date:Cc:To:
        From:Subject:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=Ain4p74aeMuMv/rK1nTwcANb7HDsGwcGYCFm+acwIPs=;
 b=OznJhtF0JIUSvFlS3eDVIkPmPf
        APRItYNW4qkDjfWQeEI2wdUY1OHHYkG016G1rOWFGnZKwMw6BJxHAsiA24eNREtp0yXh7C5SAcYN/
        kK4mGvn99tQ9nlgg1kQNw8ZsNsGcymYdmfuEczixD2LitVMKb3zd4zcrtcODXWgvwLLwXATofd1CH
        wov2ZJIkqiQXSxUB5M7KrjGyow1R7CjC8ygkx7pmob13U6hhYocRgauxtUHgl7WIUJSsci7QEWUAL
        BjA/9F72fJjEOPltwZbKVP812jFeaOBt6anZpNzxR/fbAcOqoc1Q6c2mF6ELOE8Td/qPS64EQ5GEh
        HGl87orA==;
Received: from 54-240-197-238.amazon.com ([54.240.197.238]
 helo=u3832b3a9db3152.ant.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kdCGK-0006gt-0a; Thu, 12 Nov 2020 13:03:40 +0000
Message-ID: <62918f65ec78f8990278a6a0db0567968fa23e49.camel@infradead.org>
Subject: [RFC] Further hack request_interrupt_window handling to work around
 kvm_cpu_has_interrupt() nesting breakage
From: David Woodhouse <dwmw2@infradead.org>
To: kvm <kvm@vger.kernel.org>
Cc: "Sironi, Filippo" <sironi@amazon.de>,
        "Raslan, KarimAllah" <karahmed@amazon.de>
Date: Thu, 12 Nov 2020 13:03:38 +0000
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In kvm_cpu_has_interrupt() we see the following FIXME:

	/*
	 * FIXME: interrupt.injected represents an interrupt that it's
	 * side-effects have already been applied (e.g. bit from IRR
	 * already moved to ISR). Therefore, it is incorrect to rely
	 * on interrupt.injected to know if there is a pending
	 * interrupt in the user-mode LAPIC.
	 * This leads to nVMX/nSVM not be able to distinguish
	 * if it should exit from L2 to L1 on EXTERNAL_INTERRUPT on
	 * pending interrupt or should re-inject an injected
	 * interrupt.
	 */

I'm using nested VMX for testing, while I add split-irqchip support to
my VMM. I see the vCPU lock up when attempting to deliver an interrupt.

What seems to happen is that request_interrupt_window is set, causing
an immediate vmexit because an IRQ *can* be delivered. But then
kvm_vcpu_ready_for_interrupt_injection() returns false, because
kvm_cpu_has_interrupt() is true.

Because that returns false, the kernel just continues looping in
vcpu_run(), constantly vmexiting and going right back in.

This utterly naïve hack makes my L2 guest boot properly, by not
enabling the irq window when we were going to ignore the exit anyway.
Is there a better fix?

I must also confess I'm working on a slightly older kernel in L1, and
have forward-ported to a more recent tree without actually testing
because from inspection it looks like exactly the same issue still
exists.

```
