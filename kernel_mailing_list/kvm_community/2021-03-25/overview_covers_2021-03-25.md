

#### [PATCH for-stable-5.10 0/2] Backport for- Work around firmware
##### From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>

```c
From patchwork Thu Mar 25 09:14:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shameerali Kolothum Thodi
 <shameerali.kolothum.thodi@huawei.com>
X-Patchwork-Id: 12163565
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA5DEC433E3
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:16:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 979FF61A2A
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:16:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229873AbhCYJPl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:15:41 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:14894 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229801AbhCYJPR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 05:15:17 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4F5fXy13N9zlVtH;
        Thu, 25 Mar 2021 17:13:38 +0800 (CST)
Received: from S00345302A-PC.china.huawei.com (10.47.26.249) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.498.0; Thu, 25 Mar 2021 17:15:07 +0800
From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <stable@vger.kernel.org>
CC: <maz@kernel.org>, <pbonzini@redhat.com>, <linuxarm@huawei.com>
Subject: [PATCH for-stable-5.10 0/2] Backport for- Work around firmware
 wrongly advertising GICv2 compatibility
Date: Thu, 25 Mar 2021 09:14:22 +0000
Message-ID: <20210325091424.26348-1-shameerali.kolothum.thodi@huawei.com>
X-Mailer: git-send-email 2.12.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.47.26.249]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Backport 2 patches that are required on ARM64 platforms having
firmware wrongly advertising GICv2 compatibility.

Patch 1 has nvhe related conflict resolution while patch 2 is
cleanly applied.

Tested on HiSilicon D06 platform.

Marc Zyngier (2):
  KVM: arm64: Rename __vgic_v3_get_ich_vtr_el2() to
    __vgic_v3_get_gic_config()
  KVM: arm64: Workaround firmware wrongly advertising GICv2-on-v3
    compatibility

 arch/arm64/include/asm/kvm_asm.h   |  4 +--
 arch/arm64/kvm/hyp/nvhe/hyp-main.c |  4 +--
 arch/arm64/kvm/hyp/vgic-v3-sr.c    | 40 ++++++++++++++++++++++++++++--
 arch/arm64/kvm/vgic/vgic-v3.c      | 12 ++++++---
 4 files changed, 51 insertions(+), 9 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/8] Testing SSCH, CSCH and HSCH for errors
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Mar 25 09:38:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12163641
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2A68FC433E8
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:40:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0050861A3C
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 09:40:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230134AbhCYJj4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 05:39:56 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:44826 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229879AbhCYJjO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 05:39:14 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12P9YKw2168406
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=oh+j/snZUCtMHYB/MmSkEOoqubIfPJSMPMQd9uHSFxU=;
 b=T+WXsLIddG1SAinzupiQ5X1TsK48S8jz8s/vEFSFkfiador6ToiU479+YJkj2w6VAFOC
 ozFb/rs+EJ6w7srLA4LMyUVCHDhyyHQxI8POZGts6e06NPkcs/IOgWAAaYRa/G3jAn4y
 blwAAycxb1vXla/mMEDt5uMcDqAvOTaQcNVji/u3C5xjrHNTh/j9ujhiStnuwK4mN7Pe
 avRm7vUOT5k9YX5C02IWpoucAHStjUGh81Y5CFrqlg8XiqFTLEYViYQb9KFMYGZWoyK4
 PxoemezdyMqjnccLfe3A7OO2VjnyaoZw9qe0jigmOGm+He6aL8cEZ/G2Az3PLsvaNU/B Fw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ghp0s2c9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:13 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12P9YNEm168595
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 05:39:13 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37ghp0s2bk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 05:39:13 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12P9Slni020238;
        Thu, 25 Mar 2021 09:39:11 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 37df68csn0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 09:39:11 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12P9d9W341025820
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 09:39:09 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E28D511C04C;
        Thu, 25 Mar 2021 09:39:08 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A1E9D11C066;
        Thu, 25 Mar 2021 09:39:08 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.41.31])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 09:39:08 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/8] Testing SSCH, CSCH and HSCH for errors
Date: Thu, 25 Mar 2021 10:38:59 +0100
Message-Id: <1616665147-32084-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_02:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=0 mlxscore=0 clxscore=1015 priorityscore=1501 malwarescore=0
 adultscore=0 impostorscore=0 bulkscore=0 phishscore=0 mlxlogscore=999
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103250072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The goal of this series is to test some of the I/O instructions,
SSCH, CSCH and HSCH for errors like invalid parameters, addressing,
timing etc.
We can not test the sending of an instruction before the last instruction
has been proceeded by QEMU due to the QEMU serialization but we can 
check the behavior of an instruction if it is started before the status
of the last instruction is read.

To do this we first separate the waiting for the interruption and the
checking of the IRB and enable the subchannel without an I/O ISC to
avoid interruptions at this subchannel and second, we add an argument
to the routine in charge to check the IRB representing the expected
SCSW control field of the IRB.

We also need several other enhancements to the testing environment:

- definitions for the SCSW control bits
- a new function to disable a subchannel
- a macro to simplify skiping tests when no device is present
  (I know the warning about return in macro, can we accept it?)

In the new tests we assume that all the test preparation is working and
use asserts for all function for which we do not expect a failure.

regards,
Pierre


Pierre Morel (8):
  s390x: lib: css: disabling a subchannel
  s390x: lib: css: SCSW bit definitions
  s390x: css: simplify skipping tests on no device
  s390x: lib: css: separate wait for IRQ and check I/O completion
  s390x: lib: css: add SCSW ctrl expectations to check I/O completion
  s390x: css: testing ssch error response
  s390x: css: testing halt subchannel
  s390x: css: testing clear subchannel

 lib/s390x/css.h     |  35 +++++-
 lib/s390x/css_lib.c | 104 ++++++++++++++++--
 s390x/css.c         | 251 ++++++++++++++++++++++++++++++++++++++++----
 3 files changed, 363 insertions(+), 27 deletions(-)
```
#### [PATCH v5 0/1] s390/vfio-ap: fix circular lockdep when starting
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Thu Mar 25 12:46:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12164045
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F039EC433E2
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:47:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD09761A2B
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 12:47:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229524AbhCYMq5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 08:46:57 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:57950 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230043AbhCYMqy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 08:46:54 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCXTQa100868;
        Thu, 25 Mar 2021 08:46:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=81z+BR2YioPu6Y6pMoWaSPjcoO05O8RLN39gLy3H59U=;
 b=AP21OXZcQT5WoqWnXAATAGMjM5W4QhR25GFvofJXxSvY9IDnFeoCX993KIaWZa0Vz+2q
 51e6tYStk1n0D2CgPMfvHiSdO4YCeV2v3ry/Icu/QnNncp0QW6UCet0jOBPc7RaipNso
 GaoG/ZB5Tp8BluN5F/g3Q3DVSSWdcob33k3GaqncvVn3XvQo+jWyokpec6S9cP23qflq
 v3I1B99jGJCSNdmDzZJVs/j+yi0uosrLQGoeCCgEXfx/ZoR2I+F7aQxEFbUtEqjmdI9+
 Hmyi4ctUbmg9Leomh6V1XJvVjHB02zgqR+X35pV+IZEPP1obIh1cyXmv5NGx7dR7GSXg KA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ghn1pbny-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 08:46:52 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12PCYmbA110000;
        Thu, 25 Mar 2021 08:46:52 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37ghn1pbnf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 08:46:52 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12PCkfqJ002811;
        Thu, 25 Mar 2021 12:46:51 GMT
Received: from b03cxnp07027.gho.boulder.ibm.com
 (b03cxnp07027.gho.boulder.ibm.com [9.17.130.14])
        by ppma02dal.us.ibm.com with ESMTP id 37d9an6yua-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 25 Mar 2021 12:46:51 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp07027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12PCknHw19071268
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 25 Mar 2021 12:46:49 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D4FA3136059;
        Thu, 25 Mar 2021 12:46:49 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 93175136053;
        Thu, 25 Mar 2021 12:46:48 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.150.254])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 25 Mar 2021 12:46:48 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v5 0/1] s390/vfio-ap: fix circular lockdep when starting
Date: Thu, 25 Mar 2021 08:46:39 -0400
Message-Id: <20210325124640.23995-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-25_03:2021-03-24,2021-03-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 suspectscore=0 mlxlogscore=999 spamscore=0 clxscore=1015 bulkscore=0
 impostorscore=0 malwarescore=0 adultscore=0 phishscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103250093
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

*Commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated") introduced a change that results in a circular
lockdep when a Secure Execution guest that is configured with
crypto devices is started. The problem resulted due to the fact that the
patch moved the setting of the guest's AP masks within the protection of
the matrix_dev->lock when the vfio_ap driver is notified that the KVM
pointer has been set. Since it is not critical that setting/clearing of
the guest's AP masks be done under the matrix_dev->lock when the driver
is notified, the masks will not be updated under the matrix_dev->lock.
The lock is necessary for the setting/unsetting of the KVM pointer,
however, so that will remain in place.

The dependency chain for the circular lockdep resolved by this patch
is (in reverse order):

2:	vfio_ap_mdev_group_notifier:	kvm->lock
					matrix_dev->lock

1:	handle_pqap:			matrix_dev->lock
	kvm_vcpu_ioctl:			vcpu->mutex

0:	kvm_s390_cpus_to_pv:		vcpu->mutex
	kvm_vm_ioctl:  			kvm->lock

Please note:
-----------
* If checkpatch is run against this patch series, you may
  get a "WARNING: Unknown commit id 'f21916ec4826', maybe rebased or not
  pulled?" message. The commit 'f21916ec4826', however, is definitely
  in the master branch on top of which this patch series was built, so
  I'm not sure why this message is being output by checkpatch.
* All acks granted from previous review of this patch have been removed
  due to the fact that this patch introduces non-trivial changes (see
  change log below).

Change log v4=> v5:
------------------
* In vfio_ap_mdev_ioctl() function:
  - Verify matrix_mdev is not NULL before doing reset
  - Do reset regardless matrix_mdev->kvm is NULL or not

Change log v3=> v4:
------------------
* In vfio_ap_mdev_set_kvm() function, moved the setting of
  matrix_mdev->kvm_busy just prior to unlocking matrix_dev->lock.

* Reset queues regardless of regardless of the value of matrix_mdev->kvm
  in response to the VFIO_DEVICE_RESET ioctl.

Change log v2=> v3:
------------------
* Added two fields - 'bool kvm_busy' and 'wait_queue_head_t wait_for_kvm'
  to struct ap_matrix_mdev. The former indicates that the KVM
  pointer is in the process of being updated and the second allows a
  function that needs access to the KVM pointer to wait until it is
  no longer being updated. Resolves problem of synchronization between
  the functions that change the KVM pointer value and the functions that
  required access to it.

Change log v1=> v2:
------------------
* No longer holding the matrix_dev->lock prior to setting/clearing the
  masks supplying the AP configuration to a KVM guest.
* Make all updates to the data in the matrix mdev that is used to manage
  AP resources used by the KVM guest in the vfio_ap_mdev_set_kvm()
  function instead of the group notifier callback.
* Check for the matrix mdev's KVM pointer in the vfio_ap_mdev_unset_kvm()
  function instead of the vfio_ap_mdev_release() function.

Tony Krowiak (1):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks

 drivers/s390/crypto/vfio_ap_ops.c     | 309 ++++++++++++++++++--------
 drivers/s390/crypto/vfio_ap_private.h |   2 +
 2 files changed, 215 insertions(+), 96 deletions(-)
---
2.21.3
```
#### [PATCH kvm-unit-tests 0/2] arm64: One fix and one improvement
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Thu Mar 25 15:56:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12164531
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C4DCC433DB
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 15:57:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6FAB61A1A
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 15:57:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229519AbhCYP51 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 11:57:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:51536 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229695AbhCYP5H (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 25 Mar 2021 11:57:07 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616687825;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=lD6wjnjJ9XnwU0ytJNLAVFancBc+NQ/9UGYPYbmVH8g=;
        b=hiEBl7K5lPTA1XywhnGkAo/2Wb/zZkBK+Yl8jGb6/8Z3NebLPMUHzNgGSrKUcEb/+PBpQb
        f+C/m+itT+oggk+HKRS7elJ/V33JzHr8wHCLQIMQUAWetEpVWWrAMPnYE1/Q/jA+0/Jjqc
        livwXHF3F52cnqk9XVrTDEi2YKkHq6c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-272-ZFRVf2SKM9KBOAqVfpB-oQ-1; Thu, 25 Mar 2021 11:57:01 -0400
X-MC-Unique: ZFRVf2SKM9KBOAqVfpB-oQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B31D7807904;
        Thu, 25 Mar 2021 15:57:00 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.194.23])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E9B3E5D749;
        Thu, 25 Mar 2021 15:56:58 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: nikos.nikoleris@arm.com, alexandru.elisei@arm.com
Subject: [PATCH kvm-unit-tests 0/2] arm64: One fix and one improvement
Date: Thu, 25 Mar 2021 16:56:55 +0100
Message-Id: <20210325155657.600897-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the loading of argc. Nikos reported an issue with its alignment
while testing target-efi (aligned to four bytes is OK, as long as we
only load four bytes like we should). Also, take a patch developed
while working on target-efi which can make debugging a bit more
convenient (by doing some subtraction for the test developer).

Andrew Jones (2):
  arm64: argc is an int
  arm64: Output PC load offset on unhandled exceptions

 arm/cstart64.S        | 2 +-
 arm/flat.lds          | 1 +
 lib/arm64/processor.c | 7 +++++++
 3 files changed, 9 insertions(+), 1 deletion(-)
```
#### [PATCH v2 0/3] KVM: x86/mmu: Fix TLB flushing bugs in TDP MMU
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Mar 25 20:01:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12164973
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D0729C433C1
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:02:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A273561A36
	for <kvm@archiver.kernel.org>; Thu, 25 Mar 2021 20:02:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230270AbhCYUBx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 25 Mar 2021 16:01:53 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38790 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230042AbhCYUBX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 25 Mar 2021 16:01:23 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78AB5C06174A
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 13:01:23 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id a1so4692695qkn.11
        for <kvm@vger.kernel.org>; Thu, 25 Mar 2021 13:01:23 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=OPHCEnv3IH5HETxShRsKAPF8udKnECk6wv4oHyblTuE=;
        b=BeKSruwHWTA4iEPdpdv8zEnockAVt0H6lVRsdLVGy1ARx/rQo9+bQfI8FB5R7ca4B7
         Ad7V67Vox0OAwiKdMGfa2qX7ghT59Av/Sy5AfDbjoeTFQgD+Sh6DEHVZeMO0HkcQo0J3
         5UOzagrJC0pkuJXeGO6LKICwkWMCu5lzxniRU093oZqronMoWUb2/gdQLtSw71PdpY3V
         eD/IQSY0WYoP0SLbXcWAyh6m9KzUArB7dVwgKKu6J5uBCrLu0Mj5hronPOTlgHy7BGtR
         KTPLyBqYqODwlcMQZhmthuuX1CzTNsZ74cSEIJsWgG6KJoPtxPS3K5cEj0f2Cq5HyMJk
         PNtA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=OPHCEnv3IH5HETxShRsKAPF8udKnECk6wv4oHyblTuE=;
        b=LUKoOqmUtzKqpG/8dtyxdGGIr/dJ7KoM9Zw4cNcIPdFODI/07hlTDA03kpOowEya3D
         3LgWQZ9OZI/4+y4IG7Zmm2tgV7RflRUCkvze9d/e77cqKFZWed5cGRfFiYeox6GT4Bzt
         5KRaFCuPHJKxHqr42bW65g3EKxu7zFKZanpZVgpB6vOaqVWTujbPxhezfEHmdVw3e9cX
         R2lJoOUxfELJu738Q+8f1SV83T8/9KDjoI0HyrjpFt91Rp9wCIaHWI4sOZPzxi38mhvp
         PD3QOZq9IPh4AY5XLTAa4F2e51Ubxtdsmbjrfn/u83kdoD8eXluY1AArGKyk4F34cAZt
         keXQ==
X-Gm-Message-State: AOAM5301ipv+hEg62gkYlki7UBden2aqKfQOh3eZ3bkpEHu5PH5WQuDk
        0QcfMQOmYRjl3YSK8jUguVWwivIg0io=
X-Google-Smtp-Source: 
 ABdhPJx+c2hqxP76WsAheoxmp/+Z8PsVvpwZCAHUHbhEJTX8ymTXvaKwyhSoBOkmsppO8Rve+FVcIAebtPI=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:b1bb:fab2:7ef5:fc7d])
 (user=seanjc job=sendgmr) by 2002:a05:6214:425:: with SMTP id
 a5mr10117188qvy.55.1616702482646; Thu, 25 Mar 2021 13:01:22 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 25 Mar 2021 13:01:16 -0700
Message-Id: <20210325200119.1359384-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH v2 0/3] KVM: x86/mmu: Fix TLB flushing bugs in TDP MMU
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two bug fixes and a clean up involving the TDP MMU, found by inspection.

Patch 1 fixes a bug where KVM yields, e.g. due to lock contention, without
performing a pending TLB flush that was required from a previous root.

Patch 2 fixes a much more egregious bug where it fails to handle TDP MMU
flushes in NX huge page recovery.

Patch 3 explicitly disallows yielding in the TDP MMU to prevent a similar
bug to patch 1 from sneaking in.

v2:
 - Collect a review. [Ben]
 - Disallowing yielding instead of feeding "flush" into the TDP MMU. [Ben]
 - Move the yielding logic to a separate patch since it's not strictly a
   bug fix and it's standalone anyways (the flush feedback loop was not).

v1:
 - https://lkml.kernel.org/r/20210319232006.3468382-1-seanjc@google.com

Sean Christopherson (3):
  KVM: x86/mmu: Ensure TLBs are flushed when yielding during GFN range
    zap
  KVM: x86/mmu: Ensure TLBs are flushed for TDP MMU during NX zapping
  KVM: x86/mmu: Don't allow TDP MMU to yield when recovering NX pages

 arch/x86/kvm/mmu/mmu.c     |  9 +++++----
 arch/x86/kvm/mmu/tdp_mmu.c | 26 ++++++++++++++------------
 arch/x86/kvm/mmu/tdp_mmu.h | 23 ++++++++++++++++++++++-
 3 files changed, 41 insertions(+), 17 deletions(-)
```
