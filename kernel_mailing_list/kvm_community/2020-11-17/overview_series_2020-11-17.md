#### 
##### 

```c
```
#### [PATCH 1/2] KVM: s390: Add memcg accounting to KVM allocations
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11912509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 41090C56202
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:10:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6FEC24654
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:10:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="f0IJnsFH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730131AbgKQPKd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 10:10:33 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:11852 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726883AbgKQPKc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 17 Nov 2020 10:10:32 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHF31kA158382;
        Tue, 17 Nov 2020 10:10:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=lW2n8NHdOTZaZ86asOyL8V5ecUGR/0zb4Nh+FscEGTw=;
 b=f0IJnsFH3KEZtkF79eAw6GszPgOldCeaodj3kjV2H4iSq/XVsTJ3BKWDvbRyJF7EFoZ6
 Qf+/iNoZy93MCY4eGmIu6oKJsew0i8qxmuwQ4miPuBB0zA7zwhiG8ufMCtOdUZPyBvGf
 LwRNGBLtXbBp9eiyvGVxO4nN60gEBOeA9D9LIzlxNm56fxoqszBuujfI6vhpxKwbhAAg
 swxz/TcVMbSwKCfTdyS5LVxhiZy3d6ouLq0MedfuBTItM+cMXnDNxxtlIg0NFN766E05
 dZLQQdO+YdtEcieZZgi4v7JA+OObnMGVudHRQGXeNy0X5HHeHut6BB6No+xxRTVFWQM0 8g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34ve31egp5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:10:29 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AHF3eOD165749;
        Tue, 17 Nov 2020 10:10:29 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34ve31egn2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:10:29 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHF7GRd028102;
        Tue, 17 Nov 2020 15:10:27 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 34t6v89nar-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 15:10:27 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AHFAO3I787060
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Nov 2020 15:10:24 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 52923A404D;
        Tue, 17 Nov 2020 15:10:24 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 37004A405D;
        Tue, 17 Nov 2020 15:10:24 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 17 Nov 2020 15:10:24 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id EFBD0E23AA; Tue, 17 Nov 2020 16:10:23 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Heiko Carstens <hca@linux.ibm.com>
Subject: [PATCH 1/2] KVM: s390: Add memcg accounting to KVM allocations
Date: Tue, 17 Nov 2020 16:10:22 +0100
Message-Id: <20201117151023.424575-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201117151023.424575-1-borntraeger@de.ibm.com>
References: <20201117151023.424575-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-17_04:2020-11-17,2020-11-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 mlxlogscore=999 suspectscore=2 bulkscore=0 clxscore=1015 impostorscore=0
 lowpriorityscore=0 spamscore=0 phishscore=0 adultscore=0
 priorityscore=1501 mlxscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2011170109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Almost all kvm allocations in the s390x KVM code can be attributed to
process that triggers the allocation (in other words, no global
allocation for other guests). This will help the memcg controller to do
the right decisions.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Heiko Carstens <hca@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/guestdbg.c  |  8 ++++----
 arch/s390/kvm/intercept.c |  2 +-
 arch/s390/kvm/interrupt.c | 10 +++++-----
 arch/s390/kvm/kvm-s390.c  | 20 ++++++++++----------
 arch/s390/kvm/priv.c      |  4 ++--
 arch/s390/kvm/pv.c        |  6 +++---
 arch/s390/kvm/vsie.c      |  4 ++--
 7 files changed, 27 insertions(+), 27 deletions(-)

```
#### [PATCH] KVM: SVM: fix error return code in svm_create_vcpu()
##### From: Chen Zhou <chenzhou10@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chen Zhou <chenzhou10@huawei.com>
X-Patchwork-Id: 11911219
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52DDEC6369E
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 02:50:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17B47246A5
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 02:50:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726211AbgKQCtz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 21:49:55 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:7546 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725554AbgKQCty (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 21:49:54 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4CZr4y23RgzhYvN;
        Tue, 17 Nov 2020 10:49:38 +0800 (CST)
Received: from localhost.localdomain.localdomain (10.175.113.25) by
 DGGEMS409-HUB.china.huawei.com (10.3.19.209) with Microsoft SMTP Server id
 14.3.487.0; Tue, 17 Nov 2020 10:49:42 +0800
From: Chen Zhou <chenzhou10@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>, <tglx@linutronix.de>,
        <mingo@redhat.com>
CC: <hpa@zytor.com>, <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <chenzhou10@huawei.com>
Subject: [PATCH] KVM: SVM: fix error return code in svm_create_vcpu()
Date: Tue, 17 Nov 2020 10:54:26 +0800
Message-ID: <20201117025426.167824-1-chenzhou10@huawei.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Originating-IP: [10.175.113.25]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix to return a negative error code from the error handling case
instead of 0 in function svm_create_vcpu(), as done elsewhere in this
function.

Fixes: f4c847a95654 ("KVM: SVM: refactor msr permission bitmap allocation")
Reported-by: Hulk Robot <hulkci@huawei.com>
Signed-off-by: Chen Zhou <chenzhou10@huawei.com>
---
 arch/x86/kvm/svm/svm.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [RFC PATCH 1/2] vfio-mdev: Wire in a request handler for mdev parent
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11911399
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 48F3AC388F9
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 03:21:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C558320A8B
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 03:21:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="PwQ5HxQS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726773AbgKQDVs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 22:21:48 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4476 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726698AbgKQDVr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 22:21:47 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AH31eYK183733;
        Mon, 16 Nov 2020 22:21:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=wi95DkoN/LqptZ2D70P+Xd4mjTpxpQUTFHnIc74W7zs=;
 b=PwQ5HxQSUN19p2VJcE1qckunYVpr6vQYX32UQs9E99mwWvK6Hdy44sVI2ZDmt7FQvaRS
 8N5jU7idq5SQX8RHf0TIK9+I4AjS7Wjoni/4/N3ayz2OOKAmQEr9xuW+Tr62S1Gp4trX
 SQtVPx5Pq5MUgPWca1WxzWSGrOEAD8/+lNLH7s2uQVWMt76v4eeq8r/KoCFaAYlt4riF
 9BH6RbRiIYogQ8K/2Fm67cfSzIq5pBh95cpZJHi3GtUDth61evxjnylRiO5BiOXBMRET
 Zj/f5aFZklnO0azVEKg7iTJRKVmgdnbZgoPDssBrqJ9Q1WC9H7DEaebQKopW3u5K3uZK gA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34v6348knc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 16 Nov 2020 22:21:46 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AH3JI9n043858;
        Mon, 16 Nov 2020 22:21:46 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34v6348kmy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 16 Nov 2020 22:21:45 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AH38G6Q003024;
        Tue, 17 Nov 2020 03:21:43 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06ams.nl.ibm.com with ESMTP id 34t6gh2ppt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 03:21:43 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AH3LeBs55837146
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Nov 2020 03:21:40 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C51804204B;
        Tue, 17 Nov 2020 03:21:40 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B2AC742045;
        Tue, 17 Nov 2020 03:21:40 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 17 Nov 2020 03:21:40 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 64D8BE0661; Tue, 17 Nov 2020 04:21:40 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Halil Pasic <pasic@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH 1/2] vfio-mdev: Wire in a request handler for mdev parent
Date: Tue, 17 Nov 2020 04:21:38 +0100
Message-Id: <20201117032139.50988-2-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201117032139.50988-1-farman@linux.ibm.com>
References: <20201117032139.50988-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-16_13:2020-11-13,2020-11-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 mlxscore=0
 lowpriorityscore=0 mlxlogscore=999 clxscore=1015 phishscore=0 adultscore=0
 impostorscore=0 spamscore=0 bulkscore=0 suspectscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011170020
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While performing some destructive tests with vfio-ccw, where the
paths to a device are forcible removed and thus the device itself
is unreachable, it is rather easy to end up in an endless loop in
vfio_del_group_dev() due to the lack of a request callback for the
associated device.

In this example, one MDEV (77c) is used by a guest, while another
(77b) is not. The symptom is that the iommu is detached from the
mdev for 77b, but not 77c, until that guest is shutdown:

    [  238.794867] vfio_ccw 0.0.077b: MDEV: Unregistering
    [  238.794996] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: Removing from iommu group 2
    [  238.795001] vfio_mdev 11f2d2bc-4083-431d-a023-eff72715c4f0: MDEV: detaching iommu
    [  238.795036] vfio_ccw 0.0.077c: MDEV: Unregistering
    ...silence...

Let's wire in the request call back to the mdev device, so that a hot
unplug can be (gracefully?) handled by the parent device at the time
the device is being removed.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/vfio/mdev/vfio_mdev.c | 11 +++++++++++
 include/linux/mdev.h          |  4 ++++
 2 files changed, 15 insertions(+)

```
#### [kvm-unit-tests PATCH 1/5] s390x: Add test_bit to library
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11912549
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBE7AC2D0E4
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:43:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 694D024655
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:43:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="FxynMDht"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726359AbgKQPnA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 10:43:00 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39984 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725790AbgKQPnA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 17 Nov 2020 10:43:00 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHFZjmX038571;
        Tue, 17 Nov 2020 10:42:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=x2yi4fJDdMNkHfFXG+j/iBOghv9oTBf7pzWJQZd8GEA=;
 b=FxynMDhtxMDvSVA6dOvYWkLKnfrv4VPfSRCTUg/kUb8zwCUch1odqr9shp0i5OSeXe5W
 /SAwGGSrTn0h+zIJDbzP/+1RCGs3QPP17E5HYPQfyVYKCeaZN8ein6IwwNY3gtncDHMd
 zkym74B37LWcHPmc/g9h64/s5GK0LSQmCyeIcaVdjZ/V8mwOId3n5ezqIqt1seSO34cK
 BUTkDfXRXL5YyqoGQrT6mo3dhv7J3Kh70DsZHp0wb2dNsku1GV7WpZEQkOE2o4bxVByk
 89ultcjSBFB8Kn3jtSQjSxvvuUtMULSCt4mMt9AlWXZsCWDfZiGptFu3VJks91ZZ0Wtb Vg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34vehfxde0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:42:59 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AHFaFKt042650;
        Tue, 17 Nov 2020 10:42:59 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34vehfxdd9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:42:58 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHFgWtw005677;
        Tue, 17 Nov 2020 15:42:56 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04ams.nl.ibm.com with ESMTP id 34t6v8b2h4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 15:42:56 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AHFgrGo43516368
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Nov 2020 15:42:53 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7790E4C059;
        Tue, 17 Nov 2020 15:42:53 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7DA7E4C046;
        Tue, 17 Nov 2020 15:42:52 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 17 Nov 2020 15:42:52 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 1/5] s390x: Add test_bit to library
Date: Tue, 17 Nov 2020 10:42:11 -0500
Message-Id: <20201117154215.45855-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201117154215.45855-1-frankja@linux.ibm.com>
References: <20201117154215.45855-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-17_04:2020-11-17,2020-11-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 lowpriorityscore=0 malwarescore=0 adultscore=0 suspectscore=1 spamscore=0
 mlxlogscore=999 phishscore=0 clxscore=1015 mlxscore=0 priorityscore=1501
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011170114
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Query/feature bits are commonly tested via MSB bit numbers on
s390. Let's add test bit functions, so we don't need to copy code to
test query bits.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/bitops.h   | 16 ++++++++++++++++
 lib/s390x/asm/facility.h |  3 ++-
 2 files changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH v4 01/34] x86/cpu: Add VM page flush MSR availablility as a CPUID feature
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11912955
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C99B9C56202
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 17:08:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6DE7924248
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 17:08:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="QZ2RagTC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728624AbgKQRIF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 12:08:05 -0500
Received: from mail-dm6nam12on2082.outbound.protection.outlook.com
 ([40.107.243.82]:43254
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726196AbgKQRIF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Nov 2020 12:08:05 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=P0XTVk+chRmekHfOT8VNr6ozY5bn/RB1u5K4Bzyp+bnu6Hb4fi5gs/IDkjNzDZIRHmcunpFgk9XwO2n0SD/0ApETZY8/2IuYIUuWseMtMvtIE3k9wIAZ+DwVHpdySsk3Vm4q77XmHFSylp2H05CbejKfrPEDOV7BZthj3GyRD6RWZuIAPFb8iVYxUkfclLd1rwV0ZqDgPDtsOuRWmoRH3bJIaZsJNbv9beRYSzdZWZimrgwrnF3G+o1ibVrj+EX/SFfgkdgtUKzggGZ1EXmq4miJcue5XU3t+r9HDFNyiq5QOV++P5LYdEJSw49LCtUGBQ++Fe27DcLtscKqiLU9AA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=KbRxlNP2Sa6UBphIlYhrvqLKxT5VOH5ri95/vPn9Q9Dxk5WcnVpCMlG9EzQd+WdpSC+hCO5L9JM/aFSuNm4sHKhhReX4j25wSHWibzgoQQZGJmakEbX6eFgG4jt5FZwOX2V9ODjEqjWUjMAYEMreoCVu5GRYCDlKX86OX+HXOz9MgDqveBZA67xKXItP4g9veVcXsC67KMdUI1nLmZhIRYaRaBp1or85t+oUOcGAOOqYonxQid7ETSYd+uyr3GgT0/QtQLCPhsdRTpp/dxNCf5mg8WDYubWYcbDqUsifwqEzpj2WdkgaZ/Ugx63QX3YpneEgvGj1zZQsRp4L5z12+A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=jIDSQVwBhceTkXrKGCJrfTL5U9e5STc9iqm9UuU3694=;
 b=QZ2RagTC4XgzAUJvQMYEDr+chGyyCqYyHm5yCh+5DD0CyAV/EkZJf4VOJMTQcYJQXQv5u89ksjUB2TvDDmsvqpxW8cg8tL9d1B+rD/NSENbolUabIglnHXP2wcc3y1s/dQGhUch8qseBuOZOa/cbsZLS4sVDR2G/TK9YCfRjr50=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR12MB1772.namprd12.prod.outlook.com (2603:10b6:3:107::10) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3541.25; Tue, 17 Nov 2020 17:07:58 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe%12]) with mapi id 15.20.3564.028; Tue, 17 Nov
 2020 17:07:58 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v4 01/34] x86/cpu: Add VM page flush MSR availablility as a
 CPUID feature
Date: Tue, 17 Nov 2020 11:07:04 -0600
Message-Id: 
 <4c43715b4efc7a4c8c120b4246198a069f81bce7.1605632857.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1605632857.git.thomas.lendacky@amd.com>
References: <cover.1605632857.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR22CA0010.namprd22.prod.outlook.com
 (2603:10b6:3:101::20) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR22CA0010.namprd22.prod.outlook.com (2603:10b6:3:101::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3564.28 via Frontend
 Transport; Tue, 17 Nov 2020 17:07:57 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a72ca651-735b-488c-0167-08d88b1b5511
X-MS-TrafficTypeDiagnostic: DM5PR12MB1772:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB17721EC6810BFB2CA62954DFECE20@DM5PR12MB1772.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 sjx40CJlBI5mH8sJZ0eQxUnK+pbe6Re0Eob6X6SFBZc/RZhl4hGWLMMYPqJgqzCCsTqXDZAnhhqn1AaM3i6OunDf21CqXjKw4GWVYd1+rAY3tbdmRrGRk93PB2Ww8lamLh1KH07LzzNuJAl0H2s40jSrGOLYVjjkWxuQGjKlWj3nd+/7Q6D4zFjR8j3Y/Ywc7TUbJJ3kriVHeSrSCvb/dcd6UFT4zfXQYZPRCbh4L7uKyrzGVScq6RD0pQaJ1KVJP4oe+oEz+sDFD+sA0xXyYlQVEGU8MEN/65jJAGOC+xie7Zv2dg5aDX8KzwjYhQoCwaHbI2qJJyWhoUBowkhVyw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(346002)(376002)(39860400002)(136003)(6486002)(66476007)(66946007)(8936002)(5660300002)(26005)(478600001)(66556008)(16526019)(6666004)(186003)(36756003)(86362001)(8676002)(316002)(956004)(52116002)(4326008)(54906003)(7696005)(7416002)(2616005)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 hpfKuoa34hW1hfcngx35eKIGmt6/R4LaFjm4sPkWaZWH+KjrEj58UnMghm81IH+M6y/WZBqT6uvUU3JexnR6cHVVKySGQDnGS0C3cxd28avN8Fmrrb97HFbUGcw+2pOl0nwyfC2/YtVlmknYWxvkg1lo2tfx35gVdiZCVAJZTvZHJtu5oD2kkmxnd2hRFu9KYn/x6Da1I9bJPGe4nXnkcCiRRXvwV8hdzYrf36t7t2P2vIWx5SHtQQdXUdcmy5vIUSR+D8ehYyznNDtXjVqyX30GNxCPnj79Fj/SfiMwhyP3T7JfA2AjxAUuvjxpemogZEhMcs/V3yZ3kz1Wi/tRNJ7DxJAQoTECjoCT/vAqriP/cke75vyUUVPYwGHmiXC05o261a4nBwmruYBu9gnZDXxqxdJK/BpNjr7plGd36veuCRpeOF0tqwJBtIxXjkGWBfMvXASC/G88J4qsNoIVyIvA8yFW4pc6wbhXLREYqfLNJbpAvfpdUnyYJ38Jfbo5br0LWTq6TRKx4DWQ6Nv2Y4ir7ar2P5tB68orr9p8M1w3sXzd3AS5kUTCBhjnSHATnzPz676SiM40eviVGSJa8LNqic5jjQoljrMzdY9lWOkdaK0rDbmv0ghpM+hFqcp2QItKtkrts9+xC7TuJIjMzw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a72ca651-735b-488c-0167-08d88b1b5511
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 17 Nov 2020 17:07:58.2879
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5czkLKAL+VvhidbT6o8ra+/k9Si7iOs9bVBvAfDE4vD/8vTXnJkH0zIcfBj0FwZykZt+qpUSAJBCjjTLV+c4Jg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1772
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

On systems that do not have hardware enforced cache coherency between
encrypted and unencrypted mappings of the same physical page, the
hypervisor can use the VM page flush MSR (0xc001011e) to flush the cache
contents of an SEV guest page. When a small number of pages are being
flushed, this can be used in place of issuing a WBINVD across all CPUs.

CPUID 0x8000001f_eax[2] is used to determine if the VM page flush MSR is
available. Add a CPUID feature to indicate it is supported and define the
MSR.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/include/asm/msr-index.h   | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 3 files changed, 3 insertions(+)

```
