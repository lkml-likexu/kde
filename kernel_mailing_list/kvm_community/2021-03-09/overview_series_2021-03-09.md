#### [RFC PATCH v2 1/6] iommu: Evolve to support more scenarios of using IOPF
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12124221
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB7B5C433E9
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 06:23:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83E49652B2
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 06:23:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229872AbhCIGW6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 01:22:58 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:13075 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229530AbhCIGW0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 01:22:26 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DvlS86Y4MzMkgq;
        Tue,  9 Mar 2021 14:20:08 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Tue, 9 Mar 2021 14:22:15 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Eric Auger <eric.auger@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <linux-api@vger.kernel.org>
CC: Kevin Tian <kevin.tian@intel.com>, <yi.l.liu@intel.com>,
        Christoph Hellwig <hch@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Barry Song <song.bao.hua@hisilicon.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <zhukeqian1@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 1/6] iommu: Evolve to support more scenarios of using
 IOPF
Date: Tue, 9 Mar 2021 14:22:02 +0800
Message-ID: <20210309062207.505-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210309062207.505-1-lushenming@huawei.com>
References: <20210309062207.505-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch follows the discussion here:

https://lore.kernel.org/linux-acpi/YAaxjmJW+ZMvrhac@myrica/

In order to support more scenarios of using IOPF (mainly consider
the nested extension), besides keeping IOMMU_DEV_FEAT_IOPF as a
general capability for whether delivering faults through the IOMMU,
we extend iommu_register_fault_handler() with flags and introduce
IOPF_REPORT_FLAT and IOPF_REPORT_NESTED to describe the page fault
reporting capability under a specific configuration.
IOPF_REPORT_NESTED needs additional info to indicate which level/stage
is concerned since the fault client may be interested in only one
level.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 .../iommu/arm/arm-smmu-v3/arm-smmu-v3-sva.c   |  3 +-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c   | 11 ++--
 drivers/iommu/io-pgfault.c                    |  4 --
 drivers/iommu/iommu.c                         | 56 ++++++++++++++++++-
 include/linux/iommu.h                         | 21 ++++++-
 include/uapi/linux/iommu.h                    |  3 +
 6 files changed, 85 insertions(+), 13 deletions(-)

```
#### [kvm-unit-tests PATCH v5 1/6] s390x: css: Store CSS Characteristics
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12124963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60D2DC433E9
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 12:52:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3190F65274
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 12:52:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231243AbhCIMvk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 07:51:40 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:50182 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231273AbhCIMvZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Mar 2021 07:51:25 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 129CWbPK005213
        for <kvm@vger.kernel.org>; Tue, 9 Mar 2021 07:51:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=8XMcQeqnTkeZ3eySvJgaJlf5wjun0kUqA5lzqI4C8Gk=;
 b=WXQ1+fJmPP/A4LUjHXBfeC9KMGWbeqNtd+s6vScWu7Agm2K7BIIcO84bYYZFAFgtmXvE
 3amwZQ7mjlRiDypDW93svEzgKviN1VnLqozy8CDsU2ALzOQD8E7Ihe5kxl1FvJEir9i3
 qn6CCQqgjpr/9q4rCSYPkFyypqi8PzuuLtuZXNhoGsw8/oyxdLZU3NA3p8v2OcpmTx3M
 IiSkv1hkFoVZIHorAtkFqtmOQhP6vv2ciSm64p/eoWTgywA8gVnBtkuioiohDTtZ7z7G
 vjhy2xnq/b8ZoPETaDby7vKDBevJOtwsXnFKVGAfAjPTEXg2GXdF2YbNGnwNbBUF+U16 XQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3762wtkcwj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 07:51:25 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 129CWnfY005993
        for <kvm@vger.kernel.org>; Tue, 9 Mar 2021 07:51:24 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3762wtkcv2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Mar 2021 07:51:24 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 129CSLpi006719;
        Tue, 9 Mar 2021 12:51:22 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 3768urr0yb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Mar 2021 12:51:22 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 129CpJmJ17301828
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Mar 2021 12:51:19 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 262DD52050;
        Tue,  9 Mar 2021 12:51:19 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.156.215])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id D6A8052057;
        Tue,  9 Mar 2021 12:51:18 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v5 1/6] s390x: css: Store CSS Characteristics
Date: Tue,  9 Mar 2021 13:51:12 +0100
Message-Id: <1615294277-7332-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1615294277-7332-1-git-send-email-pmorel@linux.ibm.com>
References: <1615294277-7332-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-09_11:2021-03-08,2021-03-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 impostorscore=0 priorityscore=1501 adultscore=0 bulkscore=0 spamscore=0
 suspectscore=0 lowpriorityscore=0 phishscore=0 clxscore=1015 mlxscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103090062
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CSS characteristics exposes the features of the Channel SubSystem.
Let's use Store Channel Subsystem Characteristics to retrieve
the features of the CSS.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/css.h     | 66 ++++++++++++++++++++++++++++++++
 lib/s390x/css_lib.c | 93 ++++++++++++++++++++++++++++++++++++++++++++-
 s390x/css.c         |  8 ++++
 3 files changed, 166 insertions(+), 1 deletion(-)

```
#### [PATCH 01/10] vfio: Simplify the lifetime logic for vfio_device
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12126579
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C1E0C4332B
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 21:39:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E90B64FC6
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 21:39:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232064AbhCIVjI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 16:39:08 -0500
Received: from mail-bn7nam10on2073.outbound.protection.outlook.com
 ([40.107.92.73]:49607
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S231800AbhCIVi5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 16:38:57 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=V4YkKX7LgG/Z+7RqEJpiz7QFe1tZqSov20IJEBjdyZCUwTgpQeb+97knwB83WVPIO5tZtCQLqDMTWucu6ezslFm2gAa5RR33s6ozaUpRy8b78S++RViouIq+zhAkqWGNMgQouR4kAdoCfn8vIGV9vSEgeNq9c3NoSnNjmpir9KebKCIcQDn0vHg3ckBqZ7jTtannU8+tIvqknVDhOHVkCrQLyUTfGhME3gmO2/mbeXgHC0oA1DRbNXakwKt9orinqt55frgKngvxOsEzJzSwfato5Fkr+xDE69dX72SAHyRk1Im+KUj+kC6vSdmlsQ4UpOOHRHeZnmiGorIMiuDlwg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WZpCFJ7cCp6ZAqV2j9vkC6lIDX4134nSQAyR4xJGRzw=;
 b=OkFgMEpBqFRx0mxEtQ+YsvK6StXM9yq3hKaCFLYY0Se3YA9hcziKUJGXzDpV8672CDWl1xMu/5CORgDw5dR9S3jiizIAnCUb4CZrfff3tJuWzrFUYl0Trt3V+GhPSH+Vx9whHSih+826yGLwwzRrNZqsAr3iA3oSa5ihVHFBevtSZiG5UjRSt9fq5/SEoM+j93PacMFUfcKD2h87tLqoniQVg7FIq0WTqQpoajeJNDWvoBej8D3L2TV4fzZd4huWfdX7BbfHUgd1JnDPl0/HjdSgVYbZW+41S+t3fonNF/xfGUFYcFL6FJJSpqZw31D1bKN9a66GYfT4xg9E/uxgLQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=WZpCFJ7cCp6ZAqV2j9vkC6lIDX4134nSQAyR4xJGRzw=;
 b=e6aHmOf59BUo7VJeNDsIG66OmV4XYnkalWVlcrwV/0t7hxWPfyYlJ/LDysPQs6vLcOzydLa7gM0hs6YmfLsY/xxq8DyooJ1tIRYdBBMYJtxKCWIyCkjZXQq07ChfFnTh/aoBNSOosxzfnXh+7ossfoo1veA9VpjY7hVGlmnYshSS64FDmW/plBMMi2aboNzZAsr1+UWhHZr4UlIfBld9Uk+le+lhF6tbUuFaN3Mm0c0ZwVEZ9kMgFVHtIw/0k3EUrLtJdbr4iPgu7XHqFXK+epWlJzPzvNE8W9Hdg6tKotlJVDjgtcFYXHXVqC/xU9lL0nsas+nwylq+x1YeBfy7yg==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR1201MB2489.namprd12.prod.outlook.com (2603:10b6:3:e2::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17; Tue, 9 Mar
 2021 21:38:55 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3912.027; Tue, 9 Mar 2021
 21:38:55 +0000
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
Subject: [PATCH 01/10] vfio: Simplify the lifetime logic for vfio_device
Date: Tue,  9 Mar 2021 17:38:43 -0400
Message-Id: <1-v1-7355d38b9344+17481-vfio1_jgg@nvidia.com>
In-Reply-To: <0-v1-7355d38b9344+17481-vfio1_jgg@nvidia.com>
References: 
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: MN2PR20CA0010.namprd20.prod.outlook.com
 (2603:10b6:208:e8::23) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 MN2PR20CA0010.namprd20.prod.outlook.com (2603:10b6:208:e8::23) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Tue, 9 Mar 2021 21:38:53 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lJk44-00AVIa-M1; Tue, 09 Mar 2021 17:38:52 -0400
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 69dc1eec-6450-4876-d7f7-08d8e343bc70
X-MS-TrafficTypeDiagnostic: DM5PR1201MB2489:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1201MB24890C8905E11D12FF61CE78C2929@DM5PR1201MB2489.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 R30bNbO3gL67xSg38wlTqNoHgE5ZoIpRIPoPxCpWXspA+2/dbPfTP8Tu2KJJk6lZfJOLQyh1ALMsMZSsaeO8nEHYuZeVRq7V00lSxH44BtzLPtzIRjPrPnzDPJmG0xfWI7KG/8AwWQ/mlbNErTa9EasjOOqhZ2svuiwJ/DKAKlunUu2LZUCOqcUaatHxn5epMJVJOOhlhPJKK1YvT2Bg2lTWGiqHIHP8sixbnn5CofIZtTEqIGj0PVI0OXyTbIBwq/hbI67ne0WJsoHiRjiv41K3DDSbQ/fgfSdwXi7vsYh0LkazBB+I5HQVsn59qM/C2xFtknHtmfQHllJ50i8vhZ9WdivTIbES6YFU3djB0gJLJgB628mTi5BCc9pwjTfrjloiStXrLu1cRWr780qQ0svAGcDVKCwRBEEPqrXa8JpACPfijSmP7eHgU7HrsTU9f0DmmBjauQK47K8pijlHOpIbYHepwlmeBs0o5TggjK+bbA65rNPakwWHloKNORX4GHMcgEcYAzIAbkUSCwKXCOS3YGTzoxNFxfDwXZ5ztk9ncnWRz79WCFUK2F0Bhc3W
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(346002)(376002)(39860400002)(396003)(366004)(6666004)(26005)(36756003)(316002)(5660300002)(4326008)(478600001)(54906003)(110136005)(9746002)(426003)(66556008)(66476007)(2616005)(9786002)(8936002)(86362001)(186003)(2906002)(8676002)(107886003)(83380400001)(66946007)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 I5N7wTkM6m8XN/0hS3Q5g48kRtDmjYHX23/2lWvZ7AEidrvjo8pMIplls/k+6x3GLD5RVpizohAH1lYkQ9+Q2rDoWGmeMUStJW3Mh0y+q6E/FhzmWS56jV9lfgcW+cHd0QKKcmMbWWRtX4jIaE8Q4r1D4Qif5gyDQ2XQREuE/D6PFmkRAeT1bE/VctlAay21RJmETDuspC3zwelIeypmyQus6wvvkRDLtMym2kKa57XkqqQ52UhhUxBwJ9ZfLwObO5CBIpmLy4rVJ0f5SinIPNNpVBnbwVKYjWubvCUWVXhRdOR5+jy1avzOhyfCkjAToe6jxxx2IdTqy4vhow//m1qo9jVxSHrzeKBPvLCRmn7zPGeTRMxbcY9AfCrhFWk2OgvfoVoSyygndadkr/z8J8ZWTxiIEbOjef6/fHTuMsOTmexM3Qfz/cmkD04RqM1529MeK5V4R7i8+QkJXBSSu37jMfFeeSUgIP0MASXSHa0uN7oACunxw5gr4x5YEGP4fWyzK9QY5dFw83envY8nASTKlkvasyuMjrcvmmm0/hRthuvaXP5+LFKTBkda0Z5GBW5eW8SaFRZr30uBWnZUC4167waTJq74xvZky/ENVYF3IxGeCt0/ooIgSQcageWstdj2BFN3fuJJVdre3btfAOirg3vZiInLVE1KEfjvaUZkETD9Ix2SFSKtvFZCL9o30Hmsh78u9JU8c4Z5zZhjLpNb1j+83itz23PrqF5l67oROLRqv+7UHMm8qWMIu/Mc7C5EvIJqfBQ+GpYADMi7peT94CBy7InmUWWHGvGPgXQgnZus+J0oLqgrFUYS4N5DKP5kPyBpY4GdUAFgr6kbsW+Ypg9+0TP1AO0bW7g21Cf14me4CLEqjWqSxgE2aYHJVzDG4IuddD6IOA+D84xKfJhh6E+hJ4YOb4r7VHJ7Trb0ZDEB6nJaP2TcoAQG3WncqK291Mf37tnRasl1zk028yAXOypGfDZ8Mfsx1TEIrsdb5GNyWmp0QdPyWFJMPGjT3b3uBsm1yYGx1V5sytLEZiUoeqLUuTCt9gxnl2kD0bXihPCGtmLMNKErLFz37ek0NimvJ5TondgG64s5c1pz5RCZ6TdhJF7VGalMtWMcjulK/K3eqDH6CmuYMFPkP8LNUVJ57tVHPaN4X/KBOXGoDFLoVTIJFkkU251N4MRqa1yh0y/R5ywTWJUjSibQbTrep2NvC/i238/+0Q9pOmerxoJj1f5GYFxon+YRTEjGKbMs7/DlZkKDw758OmbaEbw1YAWM+Kh7NFG7GAND7LG73fK6qFYdlUuAGKm3G+vduDFx3EgseN8h/w42WbULqK6PA+weWc9pF1VMg8T/tc0j9Q==
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 69dc1eec-6450-4876-d7f7-08d8e343bc70
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Mar 2021 21:38:54.2148
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 E3Abc73AoLpGfuxOMXqr0NoOD3GippI3m83bJXlfyuUkKtUwvejs6t2izmyuSL2V
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1201MB2489
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_device is using a 'sleep until all refs go to zero' pattern for
its lifetime, but it is indirectly coded by repeatedly scanning the group
list waiting for the device to be removed on its own.

Switch this around to be a direct representation, use a refcount to count
the number of places that are blocking destruction and sleep directly on a
completion until that counter goes to zero. kfree the device after other
accesses have been excluded in vfio_del_group_dev(). This is a fairly
common Linux idiom.

This simplifies a couple of things:

- kref_put_mutex() is very rarely used in the kernel. Here it is being
  used to prevent a zero ref device from being seen in the group
  list. Instead allow the zero ref device to continue to exist in the
  device_list and use refcount_inc_not_zero() to exclude it once refs go
  to zero.

- get/putting the group while get/putting the device. The device already
  holds a reference to the group, set during vfio_group_create_device(),
  there is no need for extra reference traffic. Cleanly have the balancing
  group put in vfio_del_group_dev() before the kfree().

Clearly communicated lifetime rules are essential before we can embed the
struct vfio_device in other structures. This patch is organized so the
next patch will be able to alter the API to allow drivers to provide the
kfree.

Signed-off-by: Jason Gunthorpe <jgg@nvidia.com>
---
 drivers/vfio/vfio.c | 93 +++++++++++++++------------------------------
 1 file changed, 30 insertions(+), 63 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Fixup "Get active PCID only when writing a CR3 value"
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12123863
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5F604C433E9
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 02:20:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1D9DE652B4
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 02:20:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230512AbhCICTt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 21:19:49 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41962 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230516AbhCICTY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 21:19:24 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5B534C06175F
        for <kvm@vger.kernel.org>; Mon,  8 Mar 2021 18:19:24 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id o9so15134045yba.18
        for <kvm@vger.kernel.org>; Mon, 08 Mar 2021 18:19:24 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=jtA7dmTGM016o6c6Ho9LtE/Z/lpkYetz59Bx/2WDcjg=;
        b=q5QA+Mb1K6pSAOPJxCsSJRwnmdG0iBZJ/0J1vnIa5lqxWbZ6A69GJHEnauZ5IgHygX
         vXuDNkgMxkFIFhDBCc4ElWddoWjtMz/vpgDQaZs9GO65lSLeft9GFQU6l9c0LCtDqW03
         5oix+LVQ8fhx1UVeJYxUWDJnDBkqYjnkpa63NO5UZufKBQIr62P2mBij8iYjV4bDPXW1
         0tqExZVsU1jWJ7r5iv8edK7p/ZUBTXVNU3MmgptIbV7Qy/eU3NjmwoIsii7MMh2pUVGg
         jrUrmZWOuIiP6UL+aprfrks61l6tnKA3a9/uB8SjYPqJKfCyYA8dnK18sFf5fB1+tZj2
         NMLQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=jtA7dmTGM016o6c6Ho9LtE/Z/lpkYetz59Bx/2WDcjg=;
        b=TH3N8ebwZFZpPiDa0qsusUjn2xxJZksOLq69V65h0TlW9oTRZluXxr3Gk/qNAZ3U58
         BAHUtgowe9dVmQOUOs1ou4Wd6WjE9E8kF2f7HIj7xkIK3aN/zvgnGIKqNgjSMuyJghMO
         Kw1X4EQYbLCheFwGTIrDbkG/StqMW0gVnjNC/uupMWyeB+rEfSc95RsaDimyYknHmeHC
         LyIK9xyMqQPPOPkAi/cL6i6MZNJ935KH2KQ8ESeRgNk+m1zK2NNo+1weubV8N8USNMfg
         SqTa0Lm2st+DecPiq7j32MJlryWgTjz3V4mbSy+wB3/+rFPEuIf+gQwkQeIJ/Zp8UR+L
         2DHQ==
X-Gm-Message-State: AOAM5328Udo5abgfEmXWeHFkz4l6sSqiRZLa6YnCVlRhOcqexriP2o3o
        ppevxtOW7OiVpTIZ5TTZ5H3GYTGz4+4=
X-Google-Smtp-Source: 
 ABdhPJyolcHTtr/bnM1qT7DOGQ63cZOTUAxpJD1UnzUoyRRUgv2SN+e8rdURB0vGNH9IyglaCrIsI6KWLls=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:8:847a:d8b5:e2cc])
 (user=seanjc job=sendgmr) by 2002:a25:c6cb:: with SMTP id
 k194mr36721092ybf.27.1615256363614;
 Mon, 08 Mar 2021 18:19:23 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon,  8 Mar 2021 18:18:59 -0800
In-Reply-To: <20210309021900.1001843-1-seanjc@google.com>
Message-Id: <20210309021900.1001843-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210309021900.1001843-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 1/2] KVM: x86: Fixup "Get active PCID only when writing a CR3
 value"
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Fix SME and PCID, which got horribly mangled on application.

Fixes: a16241ae56fa ("KVM: x86: Get active PCID only when writing a CR3 value")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH 1/9] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12124381
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AA7CAC43331
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 08:34:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83939652B9
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 08:34:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230303AbhCIIeZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 03:34:25 -0500
Received: from mail-co1nam11on2052.outbound.protection.outlook.com
 ([40.107.220.52]:59872
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230112AbhCIIeO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 03:34:14 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=BkxA1xutPMYvvAm+C01fTRmFmZ0LaJhuzvQGQi9+nREs7Rif5YHkKgZX8FALd05mqZ+iMyvZtrfa+1lRaawYBAiM+7pYxyR+jAxsvqKvl3HUkVbH8zvyFvVgaQkc82RXgPpXTK592IWKUgl43Vv3xH2SgZ4A1IdSoz7isrSDVwgyyiLFOOzlLlbXJs7r9U/KPlJTyRZlnK7y5SggKzkOReSsMbz9KTEv4sg5WVoLLP+mXVtl8af10cwP54afRI62yKRej7w00XqTS54EIE2PmZ8ZhVP3FFE1rfjlATfrmon+63icbaNzClzQyfHyJ6IorRdwPuCCkOlgJY0C+AYitw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VOoeO+9FPJVvbWDwQUx7tjOUVKIcCTn6cS4IiPHKSOM=;
 b=TeHHY+iNk8uuQPbTHRa+oRDgE9nC9mTChkDJU6JVbzpe+AUwdLRzxDso7D9nEnRAHXRnvvEcQe1rT6j029oCqP4atwUkrXZtqzdMX4uvCMEx7xwTtZoGuuD9gSg36nS1AWtxKNoBv+sThcYnAGJtZUUKL2TslN3CY0kf3bbhLEkD/WK7DVpRVSz0J7kGLtMqqHDOyfir19Uybu+GarFkFS4DtBN2/SqNRAjK5+gQDx40uSEQzhm4m1TJz4zLSlzDZSDTfRGdrEBDSuPTkCoYCrFosRPSmB03n3H4O9ubdqC8hsRQSzm2+UnB3o8x9YXsqQR8TQ2QFNM+ZHGSs08MLQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.36) smtp.rcpttodomain=linux.ibm.com smtp.mailfrom=nvidia.com;
 dmarc=pass (p=none sp=none pct=100) action=none header.from=nvidia.com;
 dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=VOoeO+9FPJVvbWDwQUx7tjOUVKIcCTn6cS4IiPHKSOM=;
 b=Oj3mqYNeMs8XATzu6g5ZDWrw5cGTLePbW1OR+/XdQ+sVvTayDZbSDRtouVuYM+qKi33e9vbKh91aSAbMew+fqIvZmiNfQG0AF7gB4WccLX1AlxHR6MXULFbNOHGZZF9I3oi+DKnlI38anoMkFV/fqqcLPXXnKTpIUEHjkC7wML3SjmG1zr7b9bWRdmDOof0OEh4XxvjaBXHDu6kuuSRzcHEbNMyWEGUNHYh2b3RrbFMhE1zFFw99ukJVUaQm7GVlJ/Z80jnr2azlil0kaatfJrPvQ/2FqRbfgrJowu3ryPbss9t8O5vT3UJ5FBH3UrwPa5Js1b5j+/WBZnVibJHLCg==
Received: from DM3PR12CA0110.namprd12.prod.outlook.com (2603:10b6:0:55::30) by
 CY4PR12MB1301.namprd12.prod.outlook.com (2603:10b6:903:3e::17) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3890.23; Tue, 9 Mar 2021 08:34:11 +0000
Received: from DM6NAM11FT021.eop-nam11.prod.protection.outlook.com
 (2603:10b6:0:55:cafe::ac) by DM3PR12CA0110.outlook.office365.com
 (2603:10b6:0:55::30) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Tue, 9 Mar 2021 08:34:11 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.36)
 smtp.mailfrom=nvidia.com; linux.ibm.com; dkim=none (message not signed)
 header.d=none;linux.ibm.com; dmarc=pass action=none header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.36 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.36; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.36) by
 DM6NAM11FT021.mail.protection.outlook.com (10.13.173.76) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.3912.17 via Frontend Transport; Tue, 9 Mar 2021 08:34:10 +0000
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Tue, 9 Mar
 2021 08:34:09 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Tue, 9 Mar 2021 08:34:04 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <jgg@nvidia.com>, <alex.williamson@redhat.com>,
        <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <liranl@nvidia.com>, <oren@nvidia.com>, <tzahio@nvidia.com>,
        <leonro@nvidia.com>, <yarong@nvidia.com>, <aviadye@nvidia.com>,
        <shahafs@nvidia.com>, <artemp@nvidia.com>, <kwankhede@nvidia.com>,
        <ACurrid@nvidia.com>, <cjia@nvidia.com>, <yishaih@nvidia.com>,
        <mjrosato@linux.ibm.com>, <aik@ozlabs.ru>, <hch@lst.de>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH 1/9] vfio-pci: rename vfio_pci.c to vfio_pci_core.c
Date: Tue, 9 Mar 2021 08:33:49 +0000
Message-ID: <20210309083357.65467-2-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20210309083357.65467-1-mgurtovoy@nvidia.com>
References: <20210309083357.65467-1-mgurtovoy@nvidia.com>
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 80edac84-688a-415e-9864-08d8e2d61cd9
X-MS-TrafficTypeDiagnostic: CY4PR12MB1301:
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB1301D957E44698D855F95B9EDE929@CY4PR12MB1301.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4714;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 rxTFvQ/Z2w6ld0uo4j909wjLtUxroh3fRivum682i1tAIVBy1mW8eD9/J3XXg2EBC5XakkAeqU/79WSGOsrfnCGC6gIXNmAxuNONyTVy5r2nP3NtPbcF20+HRVI8+I88FL8q2OyxVcM/NKMH7/fpqgsSG2b5wf36E2CCnduJZOBo2sITzz+M0orMrA4a0vDHGQO+MZWe11BT+qSZ1Uk6FrDXhABX6NkZQ4d317o18Ju+KFH9fUQYFxE55ejSSUfJEz4bnHxErujlwLoP80J5vZ+loVDOG8P3VTZCzfSzI4/RhVZn1ImzMDl352zaXiTr39vZFmcvHRmzJ8PFC2G3fm5fS7nbevXY4M/KBAuXFGeDSkVkRduHfx65fH/UhkaUkbyoYThfAf1hWTwap6CmUNBO//YtAXeeZPtgKjkE6uboHaHUt4qKWW+c5BXZWnTyBnav+owKwVCBV6hEti5cQSVpiy0vPd7Lw/mg69aWM+0Tpd0UdFpZGtZI/g2S8TUbvI5T18FJDYV3tQBKG8sdsWr0RafOepBNCHVEYn7PAg4wuANPuW7I9jjg+6dRXLkpCIckFyHAjW9kfFP9/soH2QmYKGqSSpSV4RBZKP+BEZiO7aL+Rr2miCCt8T/L2BCvJGW7Uf22CAet6frJvM2kjh7YHdosIi5qGVHXelhiVSsasArUCmOpOwm6byw9MSC7
X-Forefront-Antispam-Report: 
 CIP:216.228.112.36;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid05.nvidia.com;CAT:NONE;SFS:(4636009)(39860400002)(396003)(136003)(376002)(346002)(46966006)(36840700001)(47076005)(7636003)(2906002)(107886003)(6666004)(36756003)(478600001)(82740400003)(8676002)(83380400001)(8936002)(26005)(336012)(356005)(186003)(2616005)(54906003)(110136005)(34020700004)(4326008)(86362001)(426003)(5660300002)(1076003)(70586007)(70206006)(82310400003)(36860700001)(316002);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Mar 2021 08:34:10.6636
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 80edac84-688a-415e-9864-08d8e2d61cd9
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.36];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT021.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1301
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a preparation patch for separating the vfio_pci driver to a
subsystem driver and a generic pci driver. This patch doesn't change any
logic.

Signed-off-by: Max Gurtovoy <mgurtovoy@nvidia.com>
---
 drivers/vfio/pci/Makefile                        | 2 +-
 drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} | 0
 2 files changed, 1 insertion(+), 1 deletion(-)
 rename drivers/vfio/pci/{vfio_pci.c => vfio_pci_core.c} (100%)

```
#### [PATCH v2 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12123759
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4F9CEC43619
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 01:40:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3458265259
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 01:40:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230395AbhCIBjk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 20:39:40 -0500
Received: from mga14.intel.com ([192.55.52.115]:62452 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230252AbhCIBjR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 20:39:17 -0500
IronPort-SDR: 
 4RFFH6sGIfY2QZcgfWtgHomssrDFDqcatGfBG9486PkibrnAZnjA2+t8JDdoZnZHH2EYkxFqBt
 2rImaX4auVyQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9917"; a="187500168"
X-IronPort-AV: E=Sophos;i="5.81,233,1610438400";
   d="scan'208";a="187500168"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 17:39:15 -0800
IronPort-SDR: 
 +k/69PLkzf6ZdcyqZq63nZYy75OodVdMp9njZO2XNiG3xMDa50Qujez/Mv8RoUth9ubLpIIu6i
 AP2xsOro2cCQ==
X-IronPort-AV: E=Sophos;i="5.81,233,1610438400";
   d="scan'208";a="447327136"
Received: from kzliu-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.128.38])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 17:39:10 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v2 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on
 SGX bit
Date: Tue,  9 Mar 2021 14:38:59 +1300
Message-Id: 
 <eaf02a594f0fb27ab3f358a0effef5519f4824e8.1615250634.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1615250634.git.kai.huang@intel.com>
References: <cover.1615250634.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH] Makefile: do not use "libgcc" for clangFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 12124049
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id E438BC433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 04:53:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B2F4065290
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 04:53:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229599AbhCIExX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 23:53:23 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:46744 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229793AbhCIExB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 23:53:01 -0500
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 97C1FC06174A
        for <kvm@vger.kernel.org>; Mon,  8 Mar 2021 20:53:01 -0800 (PST)
Received: by mail-pf1-x44a.google.com with SMTP id m4so7716492pfd.20
        for <kvm@vger.kernel.org>; Mon, 08 Mar 2021 20:53:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=g7IY8Tcrq5NLNN6TDDduO6XJePxJkfxYBv5xiq6DiHs=;
        b=DpULcv3v3UVNWYAf7whBKSa7An4eQZj6C83d3VgbfmD++AbA8vIt0W+nfGJRP1pfVi
         m8lGWs1pUBWSXJYBGisutPKE9RPQsw7/BYtLvEc5KhF22UW9WymiXRCTz1lLo211TzZx
         XnZ3O2AaJ7cOQA8G7m1wNGLxc4XugW1lb6Xg5EKxlBHHclD+2PFq6rU4GHFpHwWIzKbb
         00jXX61/XpCIgKXFUajBYJLAuDRZkn8XBf50B6rDVxOaJHWtNzgkxyfSto8FmJQBLfSc
         rtThQsmbpfbSymnprzj+8p8uv4pYo5xS7Mi9Q0hGeHX9royKu8j41Y+EmSP/Q3CKwIy9
         oOdA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=g7IY8Tcrq5NLNN6TDDduO6XJePxJkfxYBv5xiq6DiHs=;
        b=kSqnHqOydYfe1Hzvzf3QpgIbPhVW4r4cbXfHDibj4hyfoj9Dsw+i7E6HbYQfDThB/2
         LISDMziFZgH2eh3SYMU8iXMqb1MVirGHB+Qip8j81JgYwfqm68B0/BJlOYffGsdXhOzJ
         jPP2b9v/lRuTlDh5uwhwp/FIY0MQQmNYAUFAO074q+te2JU4zJGReRXbYeEpokWACLS/
         k8bOjAcmURWtBAPX/RLr63Isg6QP6HXUEspvN2ji9+WS2cxZX3PE7HXKx49kteV6yRSP
         vc8t4jdIn6artzqM+W1i2uw4IkSyzaSW7JE0zE2GUTap7vMsdtSc1HQBCOge91facHTm
         Yw3w==
X-Gm-Message-State: AOAM531tmA+FSC28qbkdgtt49/Pd1hpNo7/krBlbEADQwlnxeyOc0/9Q
        JaJlF06imSqFjLL+Yv7V7opGLCu0Q4hb8eNuTRuvFh0ymMCNQJhBf5evs+F0aZVeq1v6SMxo6z/
        i61nlb3bnCHL/9BT8crd0+NDWudguXAIfov7DFKrsNbK5uyVsTgqTKg==
X-Google-Smtp-Source: 
 ABdhPJzvF2vBZNfjF2t6Zq80JiFAgawfERpdIzTI4spvMWF6TFib6QAl1nIzNKFN99TP1VQX1rJFdngKfw==
Sender: "morbo via sendgmr" <morbo@fawn.svl.corp.google.com>
X-Received: from fawn.svl.corp.google.com
 ([2620:15c:2cd:202:ec92:b06d:3efe:189a])
 (user=morbo job=sendgmr) by 2002:a17:90a:a584:: with SMTP id
 b4mr2699996pjq.186.1615265580925; Mon, 08 Mar 2021 20:53:00 -0800 (PST)
Date: Mon,  8 Mar 2021 20:52:50 -0800
Message-Id: <20210309045250.3333311-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [kvm-unit-tests PATCH] Makefile: do not use "libgcc" for clang
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The -nostdlib flag disables the driver from adding libclang_rt.*.a
during linking. Adding a specific library to the command line then
causes the linker to report unresolved symbols, because the libraries
that resolve those symbols aren't automatically added. Turns out clang
doesn't need to specify that library.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 Makefile            | 6 ++++++
 arm/Makefile.common | 2 ++
 x86/Makefile.common | 2 ++
 3 files changed, 10 insertions(+)

```
#### [PATCH v2 1/4] KVM: x86: Fixup "Get active PCID only when writing a CR3 value"
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12126677
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70639C433E6
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 22:43:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4564664F48
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 22:43:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232127AbhCIWmb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 17:42:31 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52886 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231992AbhCIWmR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 17:42:17 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D2F44C06174A
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 14:42:16 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id a137so7631252qkb.20
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 14:42:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=jqjq7puvtL0+ga0HuFQpzwZNP4hDc6vknhUQK/X+oMw=;
        b=I0eo+9L92BVeyfv6dDH7KjilCQ4pfCjUMQHAfM5t8DT+rxH8lYDLUma2uZVpo2Br97
         7p7DtEumdV6Tmo+usLGGhysXjKj6dRROfrOYx+b15g54qb42SaQqwB/wcP+eV7TFghU9
         bTM0Gura1XQVSv7L5/xTQf/u4kQyqRI+1OvG5TsLh9mhwT+fKRMYL7yxTeYZDdCgz0j2
         f8+ceYieNVEM1BMTYu2x1nAkiMGuxC8LCuoegDLlGrYbhVXz+11U6Lr66dpyiU6aR0MM
         nQah7i1eTWSkctvdaop1gcfQ7Te9gnZaQ1BBonICq2HkuEVeudCJp9JbQA7HErhb62Q9
         hzGQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=jqjq7puvtL0+ga0HuFQpzwZNP4hDc6vknhUQK/X+oMw=;
        b=daKLNgtEt9Uyj7z7Vr3kDATKNLGodMdTzRlTv3XXeTdOJxsS4Sx+7ky2lfkkYZctL4
         8WQx8CHrqFN5VyzS1VPonXwFlEVizPNYKr5H+oj/sH6N9xJJNiVmozvj7IAiWcKyHhPT
         dmDCKIz0gifJmNVCp4ZjBX07FRlIeUmHx2SC48JlCIFCvzcEbHAni4p2J0gSZIlK0qww
         Sc1zho2h0W9PbhhUZwlQd2onU3F8fxol1Ay+Vr0k21O83Y8JAwzoxuQKTswWrG+dlNm+
         c8LKhWSK0SQ1Z4OGHQ8jsvpK+DHTZmPBY/KODlJR8nkYgA7XOsLaPEkClUOzEYWgXVOd
         afXg==
X-Gm-Message-State: AOAM5314g5Q4wOI+bvn2J9Jg80sXkAGmY1ZY2KgUXoQKBNRABIZd2h4j
        oZhAnOegKOPt490ecQYheqRjLEVPXu8=
X-Google-Smtp-Source: 
 ABdhPJwllIw+8NYZW3YKP9LbR1K0QGHsG4bfAG2l3fxbO2x2sl1+nVYjajHPSfEmZX67pEmhYIhAz+ospwA=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e4dd:6c31:9463:f8da])
 (user=seanjc job=sendgmr) by 2002:a05:6214:1744:: with SMTP id
 dc4mr351626qvb.40.1615329736032; Tue, 09 Mar 2021 14:42:16 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  9 Mar 2021 14:42:04 -0800
In-Reply-To: <20210309224207.1218275-1-seanjc@google.com>
Message-Id: <20210309224207.1218275-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210309224207.1218275-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v2 1/4] KVM: x86: Fixup "Get active PCID only when writing a
 CR3 value"
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Fix a merge conflict gone bad.

Fixes: a16241ae56fa ("KVM: x86: Get active PCID only when writing a CR3 value")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/svm.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH v2] x86/perf: Use RET0 as default for guest_get_msrs to handle "no PMU" case
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12126159
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
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0576C433E9
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 17:11:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C9A2B6523C
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 17:11:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231161AbhCIRKw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 12:10:52 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37372 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231273AbhCIRK1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 12:10:27 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 382B8C06175F
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 09:10:27 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id p136so17960498ybc.21
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 09:10:27 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=DoRgiyLjNklM6rtntPUZIImM3ULIR10XzAP+GnWM3ms=;
        b=jFhPiOfq/F44oTP4XYhhXZGvFEC5azXnCZH7dJWpHw1NutprxD5MKr8aXhx4dZgsfp
         N8aNwN1P6Hh2br5dchmerKJXmsuj3c1YFzX7ftRqXdUngf1SrqNsYwTxKAYyFKtyz9Zb
         lHTE3jdBXC6amjPxtjswpxEpXAjvcdT8Ly3tpMhLMhBfS5q+GuPjkOjf+99KuN2HKi0q
         3FyQs0KHmAWGrj6BSngs6oc3g2AAlXJC7dS+uROeBAcRxrrg4epyk5nNsAnRtUaEk8AP
         FurA1Lbd1Yi5LjuwFE5i+465qyid0YtqpWB4FGswR9T69qa1Sjid82hs7vKawfOUOlS3
         Iaqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=DoRgiyLjNklM6rtntPUZIImM3ULIR10XzAP+GnWM3ms=;
        b=XhWrgybiH7U6NejOfzLM2kPLBwQaW0crsMQFdgZuOUCpyVOdr6NBJ+EbNyITrlJVdO
         2fZ6ZipsFqG3iPgQGN3O9zutQDMkE3O/GEoTYlE8ylseH4uetY0WQdntgbE8AnpHI32z
         l3/ObhWW8uWUw3LOP/XnWQLDby7Flp4Q0qTXSphCCugk+EKWGXBxJGgUb6Vxpl2185g6
         nCBdhBdTlEAdmb2sC//PmgvkT7exfWU24EpeaUWHESyCHCEtAG1M0G0aYro7zGz5Xaip
         pQ4ujGKS7u2g5EFx7+w9I8+7qGBx+T/VfttnPh1Ed3/3hj1TEh5oS3Uj3ncEUDgtq6Su
         Fdcw==
X-Gm-Message-State: AOAM532aEJ9Rki5fKnnJQyxFJd53FMQA2OdOk57eMwNrH1y84KlDJ1k1
        TN/J6B3xvQa46NfWzWCCNyXVZmM2RG0=
X-Google-Smtp-Source: 
 ABdhPJyDJdVqKyWdxn0RWpoIwEArWFLUrCd9SVeGL7GSkVtsoUdPxf3VAk2FbtSI6aq3FCMSiY26zWBtKhU=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:8:847a:d8b5:e2cc])
 (user=seanjc job=sendgmr) by 2002:a25:bfc1:: with SMTP id
 q1mr39194688ybm.89.1615309826442;
 Tue, 09 Mar 2021 09:10:26 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  9 Mar 2021 09:10:19 -0800
Message-Id: <20210309171019.1125243-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v2] x86/perf: Use RET0 as default for guest_get_msrs to handle
 "no PMU" case
From: Sean Christopherson <seanjc@google.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>, x86@kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Like Xu <like.xu@linux.intel.com>,
        Dmitry Vyukov <dvyukov@google.com>,
        syzbot+cce9ef2dd25246f815ee@syzkaller.appspotmail.com
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Initialize x86_pmu.guest_get_msrs to return 0/NULL to handle the "nop"
case.  Patching in perf_guest_get_msrs_nop() during setup does not work
if there is no PMU, as setup bails before updating the static calls,
leaving x86_pmu.guest_get_msrs NULL and thus a complete nop.  Ultimately,
this causes VMX abort on VM-Exit due to KVM putting random garbage from
the stack into the MSR load list.

Add a comment in KVM to note that nr_msrs is valid if and only if the
return value is non-NULL.

Fixes: abd562df94d1 ("x86/perf: Use static_call for x86_pmu.guest_get_msrs")
Cc: Like Xu <like.xu@linux.intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Reported-by: Dmitry Vyukov <dvyukov@google.com>
Reported-by: syzbot+cce9ef2dd25246f815ee@syzkaller.appspotmail.com
Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

v2:
 - Use __static_call_return0 to return NULL instead of manually checking
   the hook at invocation.  [Peter]
 - Rebase to tip/sched/core, commit 4117cebf1a9f ("psi: Optimize task
   switch inside shared cgroups").


 arch/x86/events/core.c | 16 +++++-----------
 arch/x86/kvm/vmx/vmx.c |  2 +-
 2 files changed, 6 insertions(+), 12 deletions(-)

```
#### [PATCH v6 02/12] x86/paravirt: switch time pvops functions to use static_call()
##### From: Juergen Gross <jgross@suse.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Juergen Gross <jgross@suse.com>
X-Patchwork-Id: 12125349
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D3371C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 13:49:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AEBF650EC
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 13:49:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231389AbhCINsy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 08:48:54 -0500
Received: from mx2.suse.de ([195.135.220.15]:51340 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231162AbhCINsV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 08:48:21 -0500
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615297700;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1Xwm5mh2li/8IRrBrCYwfe2NBOuXxsvyUigtTvOh1lo=;
        b=t4cPsAYbcckAYG/qiEk71LYZZ8Z3aeLZ1K8c2a6Ypz+5ltsQALBFHjrtDmGkDMRxE+fnob
        xAUKcKfDsCQuOARcLh5vW9lYi1hCT4dD1/wK09AMrCsaOH3QVFXgF70djb8lWp4k7kSoJZ
        uG+aNmsB1Al+tic7UL1KXzx5itZCuzY=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id CC7ADAC8C;
        Tue,  9 Mar 2021 13:48:19 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, x86@kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org, kvm@vger.kernel.org
Cc: Juergen Gross <jgross@suse.com>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Subject: [PATCH v6 02/12] x86/paravirt: switch time pvops functions to use
 static_call()
Date: Tue,  9 Mar 2021 14:48:03 +0100
Message-Id: <20210309134813.23912-3-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210309134813.23912-1-jgross@suse.com>
References: <20210309134813.23912-1-jgross@suse.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The time pvops functions are the only ones left which might be
used in 32-bit mode and which return a 64-bit value.

Switch them to use the static_call() mechanism instead of pvops, as
this allows quite some simplification of the pvops implementation.

Signed-off-by: Juergen Gross <jgross@suse.com>
Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
V4:
- drop paravirt_time.h again
- don't move Hyper-V code (Michael Kelley)
V5:
- drop no longer needed Hyper-V modification (Michael Kelley)
- switch Arm and Arm64 to static_call(), too (kernel test robot)
V6:
- factor out common parts in Xen pv/pvh initialization (Boris Petkov)
---
 arch/arm/include/asm/paravirt.h       | 14 +++++---------
 arch/arm/kernel/paravirt.c            |  9 +++++++--
 arch/arm64/include/asm/paravirt.h     | 14 +++++---------
 arch/arm64/kernel/paravirt.c          | 13 +++++++++----
 arch/x86/Kconfig                      |  1 +
 arch/x86/include/asm/mshyperv.h       |  2 +-
 arch/x86/include/asm/paravirt.h       | 17 ++++++++++++++---
 arch/x86/include/asm/paravirt_types.h |  6 ------
 arch/x86/kernel/cpu/vmware.c          |  5 +++--
 arch/x86/kernel/kvm.c                 |  2 +-
 arch/x86/kernel/kvmclock.c            |  2 +-
 arch/x86/kernel/paravirt.c            | 16 ++++++++++++----
 arch/x86/kernel/tsc.c                 |  2 +-
 arch/x86/xen/time.c                   | 26 +++++++++++++-------------
 drivers/xen/time.c                    |  3 ++-
 15 files changed, 75 insertions(+), 57 deletions(-)

```
