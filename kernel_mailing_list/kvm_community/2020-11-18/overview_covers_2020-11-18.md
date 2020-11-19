

#### [PATCH 0/2] Fix and MAINTAINER update for 5.10
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Wed Nov 18 09:39:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11914669
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 08403C5519F
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 09:39:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9614F206FA
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 09:39:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="hpP2DwEW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726483AbgKRJju (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 04:39:50 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:55446 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725814AbgKRJjt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Nov 2020 04:39:49 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AI9Xfgh023727;
        Wed, 18 Nov 2020 04:39:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=u54aAQWoLPMzEIvVZIw+FkSBkit07Cum0WnKaE4yIw8=;
 b=hpP2DwEW0F+gOsEQCTUYcqbGyORJuMCkzYFXk8rMB3eFQBfJsytMicBF5oGvwifyybQN
 ipb61tNZurjbgCag6dN6yWF5GlUnWe8+hmkf+cIFW0VLvh0V7BKk7hbZVy20K9YcA5Bj
 YkTO66tDtRApHpMbxQ9RN2NwooMkqPGjZelkF+eALoJSH+T0gpdfTOqE6bqPh6H2MXX0
 NqFVkHmDZdApLPnsK/ExSNsrW7G2zwcX8tmyNxKgKHx5Bhw0k9ms/2Mkt5ZyZeybBPiq
 qV8EJiNR+zI4wZlDt/Z5b2houS/Wc8vvHj/iSPPcEY6KGjuAJEjn0bm0qiR8bqj6Dr6p GQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34w0sh8gcw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 04:39:48 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AI9YEKf027330;
        Wed, 18 Nov 2020 04:39:48 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34w0sh8gc6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 04:39:47 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AI9auNr018334;
        Wed, 18 Nov 2020 09:39:46 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 34t6v8bye2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 18 Nov 2020 09:39:46 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AI9dhse35389926
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 18 Nov 2020 09:39:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 805EEA4040;
        Wed, 18 Nov 2020 09:39:43 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F27AA4051;
        Wed, 18 Nov 2020 09:39:43 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Wed, 18 Nov 2020 09:39:43 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 35618E23AF; Wed, 18 Nov 2020 10:39:43 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Heiko Carstens <hca@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>
Subject: [PATCH 0/2] Fix and MAINTAINER update for 5.10
Date: Wed, 18 Nov 2020 10:39:40 +0100
Message-Id: <20201118093942.457191-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-18_04:2020-11-17,2020-11-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 bulkscore=0 impostorscore=0 mlxscore=0 adultscore=0 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 suspectscore=0 clxscore=1015
 mlxlogscore=524 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011180062
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Conny, David,

your chance for quick feedback. I plan to send a pull request for kvm
master soon.

I have agreed with Heiko to carry this via the KVM tree as
this is KVM s390 specific.

Christian Borntraeger (2):
  s390/uv: handle destroy page legacy interface
  MAINTAINERS: add uv.c also to KVM/s390

 MAINTAINERS           | 1 +
 arch/s390/kernel/uv.c | 9 ++++++++-
 2 files changed, 9 insertions(+), 1 deletion(-)
Acked-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
```
#### [PATCH v13 00/15] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Wed Nov 18 11:21:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11914835
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77307C5519F
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 11:22:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 101E5246A6
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 11:22:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="a8BsEnMr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727200AbgKRLWP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 06:22:15 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29091 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726677AbgKRLWP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Nov 2020 06:22:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605698534;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=JkykavBXCXxc/Cc+EpSfpWb6eYs51ekKp9L7LE1iLx4=;
        b=a8BsEnMrTFyehj4YOzyc9yRHvyjaqCcSy99J1KOH5D+kQTKyU06NIAh63y7fpaDhAuitlK
        pEP3hDkFk3Ehda7zWcdEU+ZC2VM99Yc1CkU9bN4hv1DZdR/4ww0jRwFxnbfz5IJV3+JyZR
        nbdXOhGS8s4IpkduF1+nXEHBAPqJFVA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-11-XmM7ArIhOz2XA7mA8hwAKw-1; Wed, 18 Nov 2020 06:22:10 -0500
X-MC-Unique: XmM7ArIhOz2XA7mA8hwAKw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A11DC873079;
        Wed, 18 Nov 2020 11:22:07 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-104.ams2.redhat.com
 [10.36.115.104])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 46D9F51512;
        Wed, 18 Nov 2020 11:21:54 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com,
        alex.williamson@redhat.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com, yuzenghui@huawei.com
Subject: [PATCH v13 00/15] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Wed, 18 Nov 2020 12:21:36 +0100
Message-Id: <20201118112151.25412-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

The IOMMU API is extended to support 2 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/5.10-rc4-2stage-v13
(including the VFIO part in his last version: v11)

The series includes a patch from Jean-Philippe. It is better to
review the original patch:
[PATCH v8 2/9] iommu/arm-smmu-v3: Maintain a SID->device structure

The VFIO series is sent separately.

History:

v12 -> v13:
- fixed compilation issue with CONFIG_ARM_SMMU_V3_SVA
  reported by Shameer. This urged me to revisit patch 4 into
  iommu/smmuv3: Allow s1 and s2 configs to coexist where
  s1_cfg and s2_cfg are not dynamically allocated anymore.
  Instead I use a new set field in existing structs
- fixed 2 others config checks
- Updated "iommu/arm-smmu-v3: Maintain a SID->device structure"
  according to the last version

v11 -> v12:
- rebase on top of v5.10-rc4

Eric Auger (14):
  iommu: Introduce attach/detach_pasid_table API
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Allow s1 and s2 configs to coexist
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults
  iommu/smmuv3: Accept configs with more than one context descriptor
  iommu/smmuv3: Add PASID cache invalidation per PASID

Jean-Philippe Brucker (1):
  iommu/arm-smmu-v3: Maintain a SID->device structure

 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 659 ++++++++++++++++++--
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h | 103 ++-
 drivers/iommu/dma-iommu.c                   | 142 ++++-
 drivers/iommu/iommu.c                       | 105 ++++
 include/linux/dma-iommu.h                   |  16 +
 include/linux/iommu.h                       |  41 ++
 include/uapi/linux/iommu.h                  |  54 ++
 7 files changed, 1042 insertions(+), 78 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/1] x86: test clflushopt of MMIO address
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Wed Nov 18 12:11:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 11914995
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 62F47C63697
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 12:13:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 04975246AB
	for <kvm@archiver.kernel.org>; Wed, 18 Nov 2020 12:13:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="0XX3CN6R"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726954AbgKRMNf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 18 Nov 2020 07:13:35 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:58520 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726714AbgKRMNe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Nov 2020 07:13:34 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AICAGB5010026
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:13:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=W7v0tmK1TCLDpLJZ2EE4JMHNPz7sXtOKQcinlqs8uxg=;
 b=0XX3CN6RGdeSBUEupJbfZjPARMdilMGxtlILcFM26B3vgXQH0Cvry9M2dEha8vM/Huqs
 Z0KPDoa4XBnWxpONqRztRoyFRMTvdLAj0swUDXZu72rGkd43BI8TKvKdPsHFFOWTYflT
 jvmfrxmwvA+JmvTr4IDR1AqMdiWe9kmyKbg8Qy/jJ5L273/1IxFWsPzfXVZZ3YfM+HOy
 QyKQSyz937oXHDY6X1xfn9tnib50SSMSs5ysrPY4y7l4T7NvEkVBSfJlBgGCQvEi8hhM
 8CdSiYopRHphozBP6EALQUwwTDIoV0a5v9Vzf9gI/hvV4vcO2RvZJ48tERl3vFm12OYW 9Q==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 34t4rayv0w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL)
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:13:33 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AICAbY4115662
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:32 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 34ts5xeg5k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:32 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0AICBVxB022588
        for <kvm@vger.kernel.org>; Wed, 18 Nov 2020 12:11:31 GMT
Received: from disaster-area.hh.sledj.net (/81.187.26.238)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 18 Nov 2020 04:11:31 -0800
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 2a888b2a;
        Wed, 18 Nov 2020 12:11:29 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: kvm@vger.kernel.org
Cc: David Edmondson <david.edmondson@oracle.com>
Subject: [kvm-unit-tests PATCH v2 0/1] x86: test clflushopt of MMIO address
Date: Wed, 18 Nov 2020 12:11:28 +0000
Message-Id: <20201118121129.6276-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9808
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0 phishscore=0
 suspectscore=1 mlxscore=0 malwarescore=0 bulkscore=0 mlxlogscore=961
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011180087
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9808
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 clxscore=1015
 malwarescore=0 impostorscore=0 lowpriorityscore=0 priorityscore=1501
 mlxlogscore=992 adultscore=0 phishscore=0 suspectscore=1 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011180087
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Kernel fix was merged in 51b958e5aeb1e18c00332e0b37c5d4e95a3eff84.

v2:
- Use HPET rather than the PCI test device (Nadav Amit).

David Edmondson (1):
  x86: check that clflushopt of an MMIO address succeeds

 x86/Makefile.common   |  3 ++-
 x86/clflushopt_mmio.c | 45 +++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg     |  5 +++++
 3 files changed, 52 insertions(+), 1 deletion(-)
 create mode 100644 x86/clflushopt_mmio.c
```
