#### [PATCH 01/12] fd: add a new __anon_inode_getfd helper
##### From: Christoph Hellwig <hch@lst.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoph Hellwig <hch@lst.de>
X-Patchwork-Id: 11536893
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B554C1862
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 15:36:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A30021974
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 15:36:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=infradead.org header.i=@infradead.org header.b="srCBSzZw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727907AbgEHPgm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 11:36:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58388 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726636AbgEHPgk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 11:36:40 -0400
Received: from bombadil.infradead.org (bombadil.infradead.org
 [IPv6:2607:7c80:54:e::133])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AE5C2C061A0C;
        Fri,  8 May 2020 08:36:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209; h=Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:Sender
        :Reply-To:Content-Type:Content-ID:Content-Description;
        bh=6EYCyTrFxa9+uQHjnJOrj9adSL4387IIusv8CGn+u5c=;
 b=srCBSzZwpa/R8vT9FGb8MSiNzT
        Qqn1uYSRLBeu5tyD/4XSsT0mYDn4lLbRdOf4moLFs/SGTwShV9DVJofzbIoBQmBoBJiCsWqkwHDqS
        6ifMQM06Uy05ogqQUznA5cW2YOrFFIeJ5LsIJcSd7jpMi1tvx7P3FtVwCveS1aikMR4WbSiyK0LT7
        /969LGJr0wCQLH7KzkFKs+MMOy8JW/daxQoggK4NgoMsrtAgwQEv7YMXtPvYU5W4jXBe7XEl/OQ1p
        uHAT3dFwh9mYW4W9MObM6CGHUmn/fWgH3Ylz2U2jryjURgP+RE+6QKq4EsiRP1gW7DDlgIA4OYoga
        wlnUSMRw==;
Received: from [2001:4bb8:180:9d3f:90d7:9df8:7cd:3504] (helo=localhost)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1jX53I-00047B-4u; Fri, 08 May 2020 15:36:40 +0000
From: Christoph Hellwig <hch@lst.de>
To: Alexander Viro <viro@zeniv.linux.org.uk>
Cc: linux-integrity@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-gpio@vger.kernel.org, dri-devel@lists.freedesktop.org,
        linux-rdma@vger.kernel.org, kvm@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, io-uring@vger.kernel.org,
        netdev@vger.kernel.org, bpf@vger.kernel.org
Subject: [PATCH 01/12] fd: add a new __anon_inode_getfd helper
Date: Fri,  8 May 2020 17:36:23 +0200
Message-Id: <20200508153634.249933-2-hch@lst.de>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200508153634.249933-1-hch@lst.de>
References: <20200508153634.249933-1-hch@lst.de>
MIME-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <hch@infradead.org> by
 bombadil.infradead.org. See http://www.infradead.org/rpr.html
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a helper that is equivalent to anon_inode_getfd minus the final
fd_install.

Signed-off-by: Christoph Hellwig <hch@lst.de>
---
 fs/anon_inodes.c            | 41 ++++++++++++++++++++++---------------
 include/linux/anon_inodes.h |  2 ++
 2 files changed, 26 insertions(+), 17 deletions(-)

```
#### [PATCH RESEND v26 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11535259
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C5F00912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 02:17:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B8EA420CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 02:17:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727086AbgEHCRw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 22:17:52 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:4343 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726930AbgEHCRv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 22:17:51 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 4C25BBB27AEB7C00B24F;
        Fri,  8 May 2020 10:17:46 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.487.0; Fri, 8 May 2020
 10:17:36 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <pbonzini@redhat.com>,
        <fam@euphon.net>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>, <qemu-devel@nongnu.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH RESEND v26 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a
 common macro
Date: Fri, 8 May 2020 10:19:21 +0800
Message-ID: <20200508021930.37955-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200508021930.37955-1-gengdongjiu@huawei.com>
References: <20200508021930.37955-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
Change since v25:
1. Address Peter's comments to add a proper doc-comment comment for
   UUID_LE macros.
---
 hw/acpi/nvdimm.c    | 10 +++-------
 include/qemu/uuid.h | 27 +++++++++++++++++++++++++++
 2 files changed, 30 insertions(+), 7 deletions(-)

```
#### [PATCH v2 1/3] arch/x86: Rename config X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11537603
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2FF7139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 21:10:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8032321974
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 21:10:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="p6a20qPH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728028AbgEHVJ7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 17:09:59 -0400
Received: from mail-bn7nam10on2080.outbound.protection.outlook.com
 ([40.107.92.80]:35172
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728008AbgEHVJ6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 17:09:58 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=NMCmFovLDeveDYXuFuTgjswQJbgXuPgAOWpOMpYLzPJq6tk3tTxpbwHW9MPBmu9Icl+kmWrJPVzyNGbM8pDvpWaM/ojoYcwc9kjZKcZ5NwkpM430Sup68s1IHNJwItz2RrKc9NAVShu3BESAQAO+mQLRsmqxbPl4sUDYy2KacBlItx85bTUgp8Pv588sAFixnJm1lEOY1hI9UmhG+M8DCARGFeYCgmGWBOnOBIGejpc5ttA9NCi1ytTw0Tv5hDsTNaUa/a41SO4qeWMXwm7Vi7Kb86cxveEJ7NOiED0PShgpgqDpvVviZwYO5ZvKyN/y7DhVRJjPiUl8TnYIwvbE7w==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H6BM1Fj+9KNZqI86h1czJgGqCVjHllZBjPktMGOOYX8=;
 b=ocMVRXlJKsIlXthxG4sjn4RVFLkHcH1QVW3UhcWlRnrzZ63aohEHQn/yto1IG12SxQRnueiWfCvVcBhuL2Lnn1+tvDqe+hRnBSHNYyw2NmZsZKur+BBdE3229lwryKJi7qXaE47Hk3ggNDJJWDfkOPSUJ1cZI0XvIYcUo+7FUTZCj4MGUCCKwUxLhLw+37wK9sf6dNfsjaO/z3Ka9vbLDJM2Ubep9p2FFx6sVXV1zwpmP8Lz6kSC7vjQCaacxvvxdOwvZT/7Fv/5EXTao9D6E1R2TUm3qwVuUxw1VwBh8yWy7SwDjZ69dCNEcRyY7sTFRvGjMlcpqJQQhFYwLFMaEA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=H6BM1Fj+9KNZqI86h1czJgGqCVjHllZBjPktMGOOYX8=;
 b=p6a20qPH+tUmoVhvvUbCzYfdIB9VzpAPq7YuBqaS95G+hoR7HtocoqQok8xLenz/O9jTKf7jbPX8uGh7X7NLlLkPYTaLxEw0EHFLZhRkj7l+udaPRwCKXJiBkcuJ7gkAxHVua4hoIFZwtZBv7/rr3ObCogb31PZqJmEpf9aVQMM=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2591.namprd12.prod.outlook.com (2603:10b6:802:30::32) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.33; Fri, 8 May
 2020 21:09:50 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::c0f:2938:784f:ed8d%7]) with mapi id 15.20.2979.028; Fri, 8 May 2020
 21:09:50 +0000
Subject: [PATCH v2 1/3] arch/x86: Rename config
 X86_INTEL_MEMORY_PROTECTION_KEYS to generic x86
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Fri, 08 May 2020 16:09:48 -0500
Message-ID: <158897218827.22378.8098826900779101384.stgit@naples-babu.amd.com>
In-Reply-To: 
 <158897190718.22378.3974700869904223395.stgit@naples-babu.amd.com>
References: <158897190718.22378.3974700869904223395.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN6PR16CA0037.namprd16.prod.outlook.com
 (2603:10b6:805:ca::14) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN6PR16CA0037.namprd16.prod.outlook.com (2603:10b6:805:ca::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26 via Frontend
 Transport; Fri, 8 May 2020 21:09:48 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 209b255d-0eae-4266-9eb2-08d7f3942545
X-MS-TrafficTypeDiagnostic: SN1PR12MB2591:|SN1PR12MB2591:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB25918F18F792EE45FB119B7B95A20@SN1PR12MB2591.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-Forefront-PRVS: 039735BC4E
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 xZX39NnRRQJYxBygK1PNH8DgLd6ilvX2cDBJftALUz6n581habrolXpa83jBlpIgtyEILpJPJ3IrW/jK0XlOindSgQuQMZmCNBOcv8+gwlvIGybKJPcb0a5NCrJNl1kjyQErPYwqa/asG7mQ/djrP2GMlWUVfWSM/Pm9HLU+YeDxVIRsN0GpHTvt/ijNXNlvuXUiv6eZLT5WYNH7s2/jmzrUH+2KWCWAu5nUVHGLnoglZksUMq+G0xTEDzzu/HjX0gDFU8G5mCpCBObDTNkSd+zE6nQ0UGhZ+AQJAFwb2TIMDcJ58bGePoJkoagXzB1qXG9T9hohIQx0K3C/PIsBT9fqZ5CRRKlhHUv9vHbkkFPM23BrP6tFIdIHHqzm9JwoAJ7N7zVUUxs2BC0bnd8n4TcpDaHcNzKOyVOJM8YhctUPAwDAT1jcwAXm9L5tk+7hgmNr0f0eB3DwBbhTRhg34gX7GJpT4r3HVYZzGgCk0F92YQ7BGvZOsFLFsqdeDkUoaQo4D75qCLd8GQByg5cssah9i0dpQ2WlQrR7TlLZ4Po=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(39860400002)(376002)(346002)(136003)(396003)(366004)(33430700001)(7406005)(16526019)(4326008)(7696005)(7416002)(186003)(26005)(66556008)(8936002)(52116002)(316002)(66946007)(66476007)(33440700001)(2906002)(44832011)(956004)(478600001)(55016002)(5660300002)(8676002)(103116003)(86362001)(41533002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 aeuR8dD88RUIheAG81aL0rAkb5Rp6mEMtbORAoxFb4kOwS38lkzD4/fkyTebRPNdNA5PxStaO2yQnFVHjYWlNmkICj/xdCJyHnRZoo1NhwW0LMbDyrTPlH4cBz3vgHUXPBT6b2Np3LHaVK5JVELJq+HNU/aJf6WpmK0doohyCFfLiGe7CmC5ZHbCCrAIZeFVlcXn0YOch0pbfIexn1ktLDdrNX7Od+tdZEI3zHkYZs3ThD9VGaAkGDmD5ZHy/E04JheuEbGY603gQbdanPIVmiYjMXBq3tvVKpnBN+e2I4DlhUnZRrZi+soi1gFhoNia93jW6urVsykhhZifIY0EKUEPy3jV4hA5q5TbMTGpPHfSuOi0RSXossZCBb7/gjfR8c+JbYNnN18nNVFOnRZ/E9cZRFtLwUQXS8Cvr24vGJjTnTLCldz+5lgeAAo/jAID/jXcj2YgD9/PKRGg7jyTc4QieG8ES69PIkvo+aFm0ZI=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 209b255d-0eae-4266-9eb2-08d7f3942545
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 08 May 2020 21:09:50.4971
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 68gDKH6WBOcHxyDpiL4gK7RjRm/LE76X2AmX5yMLsnTVwU8nhoII8QzhRKFEK9IV
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2591
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature.

So, rename X86_INTEL_MEMORY_PROTECTION_KEYS to X86_MEMORY_PROTECTION_KEYS.

No functional changes.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 Documentation/core-api/protection-keys.rst     |    3 ++-
 arch/x86/Kconfig                               |   11 +++++++++--
 arch/x86/include/asm/disabled-features.h       |    4 ++--
 arch/x86/include/asm/mmu.h                     |    2 +-
 arch/x86/include/asm/mmu_context.h             |    4 ++--
 arch/x86/include/asm/pgtable.h                 |    4 ++--
 arch/x86/include/asm/pgtable_types.h           |    2 +-
 arch/x86/include/asm/special_insns.h           |    2 +-
 arch/x86/include/uapi/asm/mman.h               |    2 +-
 arch/x86/kernel/cpu/common.c                   |    2 +-
 arch/x86/mm/Makefile                           |    2 +-
 arch/x86/mm/pkeys.c                            |    2 +-
 scripts/headers_install.sh                     |    2 +-
 tools/arch/x86/include/asm/disabled-features.h |    4 ++--
 14 files changed, 27 insertions(+), 19 deletions(-)

```
#### [PATCH 4.4 026/312] MIPS: KVM: Fix translation of MFC0 ErrCtl
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg KH <gregkh@linuxfoundation.org>
X-Patchwork-Id: 11536453
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BCE415AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 12:38:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8246B24959
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 12:38:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588941526;
	bh=4RRrK7MglMPlDjzWMyuZn/iF6F0PRJ7h/i9OJjOr3GE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=SYLlQGVHQVmUP3YvjsGV3rjw/BPl4nd8uaVb0aiWX5qwHTaG0VnuLjTJigVpVwQA1
	 OydZdFvVyYgFF3FbwCnsGiKfwA//fQIpblxujFVxlmWyWKJnGe2J5P1LX7x3xX9UrC
	 6c374GKatpOEO/gUEbDh6CwwT0P6mzTuWEMUy6K4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728465AbgEHMip (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 08:38:45 -0400
Received: from mail.kernel.org ([198.145.29.99]:55058 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728441AbgEHMik (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 08:38:40 -0400
Received: from localhost (83-86-89-107.cable.dynamic.v4.ziggo.nl
 [83.86.89.107])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 50A882495F;
        Fri,  8 May 2020 12:38:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588941518;
        bh=4RRrK7MglMPlDjzWMyuZn/iF6F0PRJ7h/i9OJjOr3GE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=U1P2KxEuuZJCt7TSyJYbmZdxUZhpbrAU0Ejopw2DgDY4IobmM2vg6vcGavVh1uqUw
         3E5wz4D90VZ/YFOFivEZVh9KtV077TiSOrlP2pRJJySQA2IDY2MVstqUzsEtQzHLGn
         NAg8CxAlQEK3Cn00AzkhSblkdqAzvTXjtZVCXrlI=
From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
To: linux-kernel@vger.kernel.org
Cc: Greg Kroah-Hartman <gregkh@linuxfoundation.org>, stable@vger.kernel.org,
 James Hogan <james.hogan@imgtec.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Ralf Baechle <ralf@linux-mips.org>, linux-mips@linux-mips.org,
 kvm@vger.kernel.org
Subject: [PATCH 4.4 026/312] MIPS: KVM: Fix translation of MFC0 ErrCtl
Date: Fri,  8 May 2020 14:30:17 +0200
Message-Id: <20200508123126.325941201@linuxfoundation.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200508123124.574959822@linuxfoundation.org>
References: <20200508123124.574959822@linuxfoundation.org>
User-Agent: quilt/0.66
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: James Hogan <james.hogan@imgtec.com>

commit 66ffc50c480e7ab6ad5642f47276435a8873c31a upstream.

The MIPS KVM dynamic translation is meant to translate "MFC0 rt, ErrCtl"
instructions into "ADD rt, zero, zero" to zero the destination register,
however the rt register number was copied into rt of the ADD instruction
encoding, which is the 2nd source operand. This results in "ADD zero,
zero, rt" which is a no-op, so only the first execution of each such
MFC0 from ErrCtl will actually read 0.

Fix the shift to put the rt from the MFC0 encoding into the rd field of
the ADD.

Fixes: 50c8308538dc ("KVM/MIPS32: Binary patching of select privileged instructions.")
Signed-off-by: James Hogan <james.hogan@imgtec.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Ralf Baechle <ralf@linux-mips.org>
Cc: linux-mips@linux-mips.org
Cc: kvm@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/mips/kvm/dyntrans.c |    2 +-
```
#### [PATCH] kvm: add halt-polling cpu usage statsFrom: Jon Cargille <jcargill@google.com>
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11537339
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D72C6913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 18:22:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE920218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 18:22:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FxsJIw9N"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727116AbgEHSWw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 14:22:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56208 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726636AbgEHSWw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 14:22:52 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 47DC8C061A0C
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 11:22:52 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id w15so3057812ybp.16
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 11:22:52 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=36cGNYe6ShNCgmX+2LiEk2mbNEtHey09nCarODUPKds=;
        b=FxsJIw9Nqt2of5gMxoaFw1W5hQiw5NOsyI94lqgC266bKDNILq19UgSG5w7PXgRrbE
         tEnk/LbN8OeWhjwpNc3yIX06DHU3sX6I2Z6qayc2vyGJItJmHiv9Aw+67amIEZKFoEtI
         nLqj/LPIDOfTuflYf8wkrXz+YzA+NP9Lxq+KFL2UwshmYHeqUA97Qdzrgk8lN03yFNNI
         yRfLGzrUGvnWMf3zG/6CgdxABRGaZERY2CqLmrgb+FVZ8uM8VPR0a49PWW3gzC0rrfBD
         70/ixtsW+4oHQDTfIW8regY68iFqpFaraMprEo+4jwC7Cc5Mkf4zD3ahYoo734Bbcq4v
         AgzA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=36cGNYe6ShNCgmX+2LiEk2mbNEtHey09nCarODUPKds=;
        b=OT5HydHilwubTwNC/g70RDWy8v7V78fQlctEZMSsMNY2QwXWh+dX6+gBKpMFsseupo
         0Pz1b9BuJq9x6aZdi7wJe4Z7HrxnF4nKrGCMlO5m/yfYB/RnH2UqbGzTnlr7w5Azrtau
         VSE5Tf5bX/9iu2L+22KaH0ynq+J2H9w1LBlz3vJ5qLcoYFBlZrOvI/S0RKVGlzTUZRE9
         CxY4vWR4cMm3khAmHbUAYQCr08/quGSmtCNoXubc/vOAz11couBGllnuySbHgKjiqcml
         G6sTKsTNvNsRX4XKN+I0KJGCuvENpv15nxZkQcaXZ0C10hLJvMOiDe+B2dvdMxgZEH89
         lhyw==
X-Gm-Message-State: AGi0Pubcab+CwrcMtnaw7+DK97fIGFCEWIwtjriQ8EsBQ/zJiYaXvPQl
        +yNlL++5mJJhwRoqsmlst41q8qH/i8umXg==
X-Google-Smtp-Source: 
 APiQypKHnac9ibG0+zijqvOKATCu+FaUpuVnT1jlsq4K4eTgwmg4aYoNgIvp73R9IMCdQXmZuESLz5iLNgpzhw==
X-Received: by 2002:a25:b9c5:: with SMTP id y5mr6305255ybj.421.1588962171430;
 Fri, 08 May 2020 11:22:51 -0700 (PDT)
Date: Fri,  8 May 2020 11:22:40 -0700
Message-Id: <20200508182240.68440-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [PATCH] kvm: add halt-polling cpu usage stats
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: David Matlack <dmatlack@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Matlack <dmatlack@google.com>

Two new stats for exposing halt-polling cpu usage:
halt_poll_success_ns
halt_poll_fail_ns

Thus sum of these 2 stats is the total cpu time spent polling. "success"
means the VCPU polled until a virtual interrupt was delivered. "fail"
means the VCPU had to schedule out (either because the maximum poll time
was reached or it needed to yield the CPU).

To avoid touching every arch's kvm_vcpu_stat struct, only update and
export halt-polling cpu usage stats if we're on x86.

Exporting cpu usage as a u64 and in nanoseconds means we will overflow at
~500 years, which seems reasonably large.

Signed-off-by: David Matlack <dmatlack@google.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/x86.c              |  2 ++
 virt/kvm/kvm_main.c             | 20 +++++++++++++++++---
 3 files changed, 21 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: pmu: Test full-width counter writes support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11535943
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADB10139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 08:32:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AB2E21473
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 08:32:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727096AbgEHIcb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 04:32:31 -0400
Received: from mga09.intel.com ([134.134.136.24]:5577 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726616AbgEHIca (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 04:32:30 -0400
IronPort-SDR: 
 esev7ramki06kiNr1weLUIDshzpzj9CFNepVIRXx6uBsXfyalMxh2unXyqoqhScErwibqRnHXW
 4DVPROgwgLkQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2020 01:32:29 -0700
IronPort-SDR: 
 gI2CTkFMXk+5nNqVGFDQsCcRd6yrhvwLekHSvtX5sma2RcReehdVaVaPLUHhRf13T8A83LETmz
 kYL6dILcy88Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,366,1583222400";
   d="scan'208";a="305365410"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by FMSMGA003.fm.intel.com with ESMTP; 08 May 2020 01:32:27 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [kvm-unit-tests PATCH] x86: pmu: Test full-width counter writes
 support
Date: Fri,  8 May 2020 16:32:18 +0800
Message-Id: <20200508083218.120559-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200508083218.120559-1-like.xu@linux.intel.com>
References: <20200508083218.120559-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the full-width writes capability is set, use the alternative MSR
range to write larger sign counter values (up to GP counter width).

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 lib/x86/msr.h |   1 +
 x86/pmu.c     | 125 ++++++++++++++++++++++++++++++++++++++++----------
 2 files changed, 102 insertions(+), 24 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: VMX: Add a VMX-preemption timer expiration test
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11537553
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5DAD181
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:39:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29B8D2184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:39:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="aRYoiHzx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727088AbgEHUjn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 16:39:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49452 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726883AbgEHUjm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 16:39:42 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 8477EC061A0C
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 13:39:42 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id n22so3294541qtp.15
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 13:39:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=VL335T+eqD2/ZBcv6CJbEsGdKB/CUVQDdXI0UV5ucn0=;
        b=aRYoiHzxy6SVHTf7dDLxOnfbIxX8CO74SxEIwvJ6BY9+nTaQlpEWRGz/yfIL4xRnbT
         87CD82MCbLu5MgtNhv1PLFFyyvax94xb6HNuWwWBa0J/dQkth5BrYgENlLmoVQ+UI3Uk
         QqMhlVxF8Fgy3LH1zYls+t5VzFD2faKLBjqwyw6KmRWWJqQB4CBs80XZjc8cPvPzeyj1
         TpRhbDGZbN3Gz53Ltk3aG7gSzkEuXs4QGkZFP8GzYBb7NkOqBYDqu4jrWrj2iTVvXdaI
         LQBP+NBEtysKiKBSgOkmnGwVi9SvRYo63D63Okg8fRD1X3IkSSuoRLCh7g48Bem7ozXy
         XH4Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=VL335T+eqD2/ZBcv6CJbEsGdKB/CUVQDdXI0UV5ucn0=;
        b=p69rK7fO94EqRYE1PcH9W9qNBHA4bctt8ANM34l/1kMWTVvQ0+/jeOX4xNY2ZdR5tN
         CxlZmNmhvmeBLH10e016C46hXUUUYfow0i+ElT46H5dQ6kCg3cGUuFeoz5NQj35dI4ME
         GF67u66uuvjwEO0UerxukefhxQUycAW3giPy3AUrNBXHIR9NryQ92wYiuceDQNIFpad3
         7laf6zK+jjQYo39u85L6DZIIV3/ocUdeiQAZuIa1HEZtkk8IuTv2EsW8lellGArZhoMB
         gCD2MFfGB6xhQBuXOZ8T8oST6Rs8o5OGfKMWC6g4gd56CnebNUj3lBkeOhOonyP/Ab4o
         3lZQ==
X-Gm-Message-State: AGi0PuZmWdb0mY3aWBlPqfQE5ztBKgFD9p+6alJBMGb7cP1WQPhNYyTX
        CWfffpH4lMmiqsNfmUYVoLvM6vHs09ruL2tDh1Lb3Ds+Bs33KRPEXmzSkLQ7wR1dvwEiKqE4eT0
        YJW7i/5r4zIdG7p/ZJNnGyvGnHSJoK2bilD+CV8G7JW0JLxAT76Pu5raveklOzuI=
X-Google-Smtp-Source: 
 APiQypJQ4vTDQ09rua+3iAAyxw11ZthdaLMY8rdnELWJS6FXrGVYbS2Dwx0z5W1PuCQVo7M18ulRDxcAXnZVXA==
X-Received: by 2002:a05:6214:8e9:: with SMTP id
 dr9mr4758232qvb.84.1588970381555;
 Fri, 08 May 2020 13:39:41 -0700 (PDT)
Date: Fri,  8 May 2020 13:39:38 -0700
Message-Id: <20200508203938.88508-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [kvm-unit-tests PATCH] x86: VMX: Add a VMX-preemption timer
 expiration test
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the VMX-preemption timer is activated, code executing in VMX
non-root operation should never be able to record a TSC value beyond
the deadline imposed by adding the scaled VMX-preemption timer value
to the first TSC value observed by the guest after VM-entry.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 lib/x86/processor.h | 23 +++++++++++++
 x86/vmx.h           | 21 ++++++++++++
 x86/vmx_tests.c     | 81 +++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 125 insertions(+)

```
#### [PATCH] kvm: x86 mmu: avoid mmu_page_hash lookup for direct_map-only VM
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11537341
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1B7B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 18:24:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8310A24953
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 18:24:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="EsInb96P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727082AbgEHSYa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 14:24:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56466 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726756AbgEHSY3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 14:24:29 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B571FC061A0C
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 11:24:29 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id n7so3060151ybh.13
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 11:24:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=1V7q5o/ItajItDx2fBMJH7Cm/96EukZlRI5pzOV5Nh0=;
        b=EsInb96PWReVQg3NpHEVUBr/5zp2mwXiQdj8C/5KnpjyUPjK/GVTmMZr/3tf2YpiF6
         nCUDpMXRvZu2cZRjHsoMqjonTZQ6QPmtElreMhkQ+SBFvqcYTqY9XriUhCNSLKGAeAWV
         cRFj6xoNF7XP0I1iTYbFALuMgSrB87IIx5RnbfwFdV2FnCtMdLl2zOSRLqG1mqJb7+7e
         O9ZBP/LlJBy2ODeomKEFpGbSwe+rxGoqGykCcIGCveC+QC8Am4Ln9Ea+DRZQmQ3qzb94
         si2Ehl6+ry3xT78xc0UxSbXVamCqGl0b8VuHUWFPvZOA9mly58BrZilrUn0lh6dFYwxn
         Ef1w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=1V7q5o/ItajItDx2fBMJH7Cm/96EukZlRI5pzOV5Nh0=;
        b=jtlIz+S4jB8x80Wn4unB3fnj8EjdKvn3rss3IV2M5Ai3MDcvQdywswL0yAj8ciAaqY
         tj7UPNOrUpsZB7sNXysTb99R0t6lv+2qtpZYNvCGcHfMpQrpSwd36ctJQWRrDtrS8A+F
         SIPnbjFpGpcJNVyIU+gQPiGSYGdj88HrjWSa7PTUw9161Yqvdy2ZkES5yBWTWXY46cI2
         aQ+w3xUJCFCxm8YTVXtNs8pnT2qSLNOVh4bVhiGYDWYd/FxxxsBmcPJMkfHJx43Vf+Mn
         Ls+yDcDhagO1WyOu07sEC7/cLXRdMUxq1R9ZQWzcyni8nRSv9fEjCh/ZKSk67gKTHXPX
         pZ4w==
X-Gm-Message-State: AGi0PuYVNaakwH34aEYC9dID0SNgy9+eaD7Vq7R0No73YaV4bWyt2SxZ
        fpbmkQjhOYc7KpjYojSh3Yp9jzuYCB/ZGA==
X-Google-Smtp-Source: 
 APiQypKJdA2qSGfKe9pCHnZTDpUzjjbVa8/7G8r1CHKpUvyWadRcy0iS07qo8g1yjey1kHax0zr+qD5q6+heBA==
X-Received: by 2002:a25:d757:: with SMTP id o84mr6996891ybg.144.1588962268930;
 Fri, 08 May 2020 11:24:28 -0700 (PDT)
Date: Fri,  8 May 2020 11:24:25 -0700
Message-Id: <20200508182425.69249-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [PATCH] kvm: x86 mmu: avoid mmu_page_hash lookup for direct_map-only
 VM
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Peter Feiner <pfeiner@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Feiner <pfeiner@google.com>

Optimization for avoiding lookups in mmu_page_hash. When there's a
single direct root, a shadow page has at most one parent SPTE
(non-root SPs have exactly one; the root has none). Thus, if an SPTE
is non-present, it can be linked to a newly allocated SP without
first checking if the SP already exists.

This optimization has proven significant in batch large SP shattering
where the hash lookup accounted for 95% of the overhead.

Signed-off-by: Peter Feiner <pfeiner@google.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_host.h | 13 ++++++++
 arch/x86/kvm/mmu/mmu.c          | 55 +++++++++++++++++++--------------
 2 files changed, 45 insertions(+), 23 deletions(-)

```
#### [PATCH] KVM: x86: Move definition of __ex to kvm_host.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11535675
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13F7515AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 06:28:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F053620870
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 06:28:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="aVK1uqUl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726689AbgEHG2P (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 02:28:15 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57408 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726009AbgEHG2P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 02:28:15 -0400
Received: from mail-wm1-x342.google.com (mail-wm1-x342.google.com
 [IPv6:2a00:1450:4864:20::342])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C59B6C05BD43
        for <kvm@vger.kernel.org>; Thu,  7 May 2020 23:28:14 -0700 (PDT)
Received: by mail-wm1-x342.google.com with SMTP id u16so9337776wmc.5
        for <kvm@vger.kernel.org>; Thu, 07 May 2020 23:28:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=JKemrS/nzNf0fJmxK8GiyXOkbcPtsp55SlKT7ZKdxkk=;
        b=aVK1uqUlziSJOYj9tAQs1q/ny43Tj8h/SlRP9iNrV+9Hh0zc4XZVXZ1piMNHxdruUs
         wUt4k/tez67ABbSxmHNMqUWoVH/3HLUHi1CkYnzKTUmbAcUxfTxHb+8nciaf6qCtJ9NJ
         HE17gb87QQudszJS7PCtm7H60muaBB5KgsaHfILi6ywL5k9KyngTK68P+R+4H7FXxaGJ
         0TzyNGQNinC7AHP3U+5lj5fHhSccZAYX5z6p6pOqkftMS5Ud4LINenOoY3YzB4FBzUw9
         MJIeN4/LV3c/50TOBbB0CQRBiYokz/XKaykr2ySDpV5Lxyao8b9wLHJPbWQ53QIeTutz
         orjA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=JKemrS/nzNf0fJmxK8GiyXOkbcPtsp55SlKT7ZKdxkk=;
        b=C4vwS5UM3FVGWuz89e2PqFCMIREMC5+F0+nN0PBt+8HFoyZRsEdq0wKtd/Lyail/aS
         2jW5F7mw2tlMA7bLeSeEGickqkZQacM2EKvwBNogLPYzk/zMj9B5ZB+Y1ya9dcUAcLmU
         iIb0nIHXF6iIqeI11XnFpQVbrzMnNrCDZgC6CK/0PBTsq2ERHyJ5cKQdDdC3L69eM1y4
         X7cIm5mK28s7qOzjOYDiaW425fC0Ux505xs9+V+8UwawPLDlopds7cRwuXxeXW9JGUiA
         FEsdxV8t3Wp4Z3efSywl+txBs8bMi70Kibz5ypWvsu468z16AWGl1wXlLFEKT2Dfnemv
         9BzQ==
X-Gm-Message-State: AGi0PuZ9rShvgQYWhMTzZSgTUkgf4VZ338oAbWU86Ea3D3Lc2tspLxqj
        +pAs55/siSVsyrDymvd5h3GwPz1VRpg=
X-Google-Smtp-Source: 
 APiQypIYA9aYUj7KHJpu9f3gXejqXxO3Ocld5Ir0ds4cw/hdkLJ11cPkg4YHvVGykOTW0cOV69M+OQ==
X-Received: by 2002:a1c:7513:: with SMTP id o19mr11790871wmc.9.1588919291092;
        Thu, 07 May 2020 23:28:11 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id r11sm99873wrv.14.2020.05.07.23.28.09
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 07 May 2020 23:28:10 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: x86: Move definition of __ex to kvm_host.h
Date: Fri,  8 May 2020 08:27:53 +0200
Message-Id: <20200508062753.10889-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the definition of __ex to a common include to be
shared between VMX and SVM.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/include/asm/kvm_host.h | 2 ++
 arch/x86/kvm/svm/svm.c          | 2 --
 arch/x86/kvm/vmx/ops.h          | 2 --
 3 files changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Use VMCALL and VMMCALL mnemonics in kvm_para.h
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11536353
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C666E139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 11:23:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF606208CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 11:23:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="fMYmUryV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726811AbgEHLXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 07:23:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47046 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726618AbgEHLXY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 07:23:24 -0400
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 61AFCC05BD43
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 04:23:24 -0700 (PDT)
Received: by mail-wr1-x444.google.com with SMTP id y3so1441111wrt.1
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 04:23:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=bWU6zlynIfW1qhiMuwM2Wph5uDsDlfbABaGeEVTQWfU=;
        b=fMYmUryVpDa9Czd920mdsI5wH3fvqg0UXkKauH8ZH4w3Js888m/+EEIE/0BqRTHltP
         6mb3nRbgJoBru8144W7Fs0SLiQT6GfQRrFN07SaUIXow5H25SoAxv0+rpYKaSBFYqXsU
         vszxFX88V+ilRSx6YHPBbc4HeoP24imuslBw78OHNYXD8e7Nwen5SWuHg5c+0F4sHYt2
         RdngWhXtDzpPhNryCowJZyV3K32BWlnaP87Q6HTxBsqs2g6VuNZnvb+33CtXwXHYsY3T
         wxxf3YBselWW3FWZtOc3YyQe7jAWTh9EuVKj2RwlYhDjozC0pXYF6EZNw0UXUdYbH2EN
         r/FA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=bWU6zlynIfW1qhiMuwM2Wph5uDsDlfbABaGeEVTQWfU=;
        b=YXoUOEMrkxBfNjYnIruj/WGyAsweUm1dcb2liwSmGdWGIV/iy7Dn76UElJ0jZS86pU
         SdSimT7TyJIbSzUjfjfNqkh8Pf5uClEUAv9h4GIL0BtZThQex6m6ZhacwdiCCHYzTiuc
         yclQNhiWJl8f1Rfur2A1kRQC+fqBio/VXT1GWUIiW5PKK7fAy70efEW8X+UwT6QEvV3b
         yPPlx0gbZb3Y+WFiW7i504CCVuhmlaVmKLh8Aw5HOso5QHU0hX0WfMtQKEmTT/cCUEvn
         AULF5QzSICStjguq1M+vAlcDWMoER3a0UCgA6gI++ReCAZfuvmGWCzlWO1MNgjGYh1S7
         HYGA==
X-Gm-Message-State: AGi0PuZbybC2AHWGARVYfdAKWhEnyz7NP1yjBgwuX9PTR2znLQfMH26n
        LPhwak/NlGIXqLHnreBxzVPwQJU7aWQ=
X-Google-Smtp-Source: 
 APiQypL+amOT71OXAYlZlxzEDBJCWZ0wAdYZVVZ6wDv5LXbjFTQqsQUDmiP251PupGULSgyyfi0myw==
X-Received: by 2002:adf:b1c9:: with SMTP id r9mr2554304wra.271.1588937002851;
        Fri, 08 May 2020 04:23:22 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 p7sm2569854wrf.31.2020.05.08.04.23.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 08 May 2020 04:23:21 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] KVM: x86: Use VMCALL and VMMCALL mnemonics in kvm_para.h
Date: Fri,  8 May 2020 13:23:05 +0200
Message-Id: <20200508112305.215742-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current minimum required version of binutils is 2.23,
which supports VMCALL and VMMCALL instruction mnemonics.

Replace the byte-wise specification of VMCALL and
VMMCALL with these proper mnemonics.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
CC: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_para.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: nVMX: Really make emulated nested preemption timer pinned
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11537547
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CC54781
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:37:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B391B2184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 20:37:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Qk7wdSMs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727100AbgEHUhA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 16:37:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49014 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726811AbgEHUhA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 8 May 2020 16:37:00 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6F335C061A0C
        for <kvm@vger.kernel.org>; Fri,  8 May 2020 13:37:00 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id j4so3535353ybj.20
        for <kvm@vger.kernel.org>; Fri, 08 May 2020 13:37:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=Qcb4vvcQqRXsDBmKyBIQkPZTiuE/XsF+tWw9+Q+7+I0=;
        b=Qk7wdSMsN5vkbs1NfrrX4UKqwjbWzalid1t69mr1A/Q/Q6B8d/wND5S285btB7y1MK
         PWoULzyfLqq7yUCfYmmBV4GitfC8aY5/hDsix5zpZghRJSb6jzDyuNKwt8vtd78o4NVM
         e9eJLqqFSUIUKs1OZXu0s66Isaeo/1+hp5wMH+1DGjLHnMWDL6+GpJbwji7Gcx2pB7bl
         TKV6NeplKgjKeDkEQ4jB5ULWeMboLQODRfJFl958H+lt+kFY6TL+pEMVjmfdPznnUPmf
         G8djp0QvjD2+Rzv2GoEN48gIqkekQUWm+Wsq/kKQMd02zIALC8MEABPnEEYiSJZL30q+
         IgWw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=Qcb4vvcQqRXsDBmKyBIQkPZTiuE/XsF+tWw9+Q+7+I0=;
        b=I8norwl+JvuiQtew2Flz7DpNf167iE7A5cIQFizaoQkafTY//O9YP0OdXJjt0JN1Gg
         zc5k4c78egzKJ9ay+8kJoCfXMzNDdUb9DQEq1MuNPWrwwin3GygCUXWLIZDINKYE5Zva
         LbO3uDGPnGUyqe7X62mWHFOjABE/3FJZ/bkzSANOpSaqTu2W92z4yzVxRrZSJaLIhfif
         vnDhyl52AIAeKvUvr3FJWtZwiPFZRNCLlgHvlKVPsassVMPXOZyPVrlv0MhgKsA+Bs4b
         ERVBuYBKD/D8bxAdT6eBr2PxF/NoVrYxGuYZes/yi0nPNUphy8WCi8FrwYt+0SSMSOrJ
         8sIQ==
X-Gm-Message-State: AGi0PuYbdtbqQzin2C+bqjVerYpkGzw1tRV4QST6M46A5pncNBcOwH6G
        SQXiDT/LGnKECUU5rk4lfZuQDxujg+4s5OyiPumdKupC4IkRiv8dEeQwWqXSZbZgyVB88EkRfNr
        Z3YTAYhiHFoMXKN/3UsuVK6paTMCpAgkBYR5wvSzTs/25/RBuladwxWzCBiviHZw=
X-Google-Smtp-Source: 
 APiQypLLg2dj+v1i92RV4I4X9Okba9Ag3baU2Adrb5e5XceLCXCuLRYuq1IX6g5Y7lVid8C2citxOzJjh/nxKQ==
X-Received: by 2002:a25:9a42:: with SMTP id r2mr7472703ybo.281.1588970219625;
 Fri, 08 May 2020 13:36:59 -0700 (PDT)
Date: Fri,  8 May 2020 13:36:41 -0700
In-Reply-To: <20200508203643.85477-1-jmattson@google.com>
Message-Id: <20200508203643.85477-2-jmattson@google.com>
Mime-Version: 1.0
References: <20200508203643.85477-1-jmattson@google.com>
X-Mailer: git-send-email 2.26.2.645.ge9eca65c58-goog
Subject: [PATCH 1/3] KVM: nVMX: Really make emulated nested preemption timer
 pinned
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PINNED bit is ignored by hrtimer_init. It is only considered when
starting the timer.

When the hrtimer isn't pinned to the same logical processor as the
vCPU thread to be interrupted, the emulated VMX-preemption timer
often fails to adhere to the architectural specification.

Fixes: f15a75eedc18e ("KVM: nVMX: make emulated nested preemption timer pinned")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] KVM: x86/pmu: Support full width counting
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11535941
Return-Path: <SRS0=ySRk=6W=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A77E414B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 08:32:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F64C208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  8 May 2020 08:32:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726843AbgEHIc3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 04:32:29 -0400
Received: from mga09.intel.com ([134.134.136.24]:5577 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726616AbgEHIc3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 04:32:29 -0400
IronPort-SDR: 
 +oJ4+65JHV1Vq7QARSz2SCltQcOl9NCXNVmLBw9GpqxH1MxDAHln8XQhHjDL/Ryanb6MwgN7c3
 Ukp1K04RZpag==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2020 01:32:27 -0700
IronPort-SDR: 
 Qr93mbw7sD4NFF4KyDDh79AGWmK7UbL+Qcn2E8aCIkCtt1Aag5pbO+RTirJ3SJR7oQwyml3tA4
 xPiK+8R3GkJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,366,1583222400";
   d="scan'208";a="305365397"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by FMSMGA003.fm.intel.com with ESMTP; 08 May 2020 01:32:25 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v3] KVM: x86/pmu: Support full width counting
Date: Fri,  8 May 2020 16:32:17 +0800
Message-Id: <20200508083218.120559-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel CPUs have a new alternative MSR range (starting from MSR_IA32_PMC0)
for GP counters that allows writing the full counter width. Enable this
range from a new capability bit (IA32_PERF_CAPABILITIES.FW_WRITE[bit 13]).

The guest would query CPUID to get the counter width, and sign extends
the counter values as needed. The traditional MSRs always limit to 32bit,
even though the counter internally is larger (usually 48 bits).

When the new capability is set, use the alternative range which do not
have these restrictions. This lowers the overhead of perf stat slightly
because it has to do less interrupts to accumulate the counter value.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h | 11 +++++++++
 arch/x86/kvm/vmx/pmu_intel.c    | 42 +++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.c          |  3 +++
 arch/x86/kvm/x86.c              |  1 +
 6 files changed, 55 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/9] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 160 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 196 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
