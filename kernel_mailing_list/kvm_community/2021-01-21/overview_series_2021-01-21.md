#### [PATCH 1/1] s390/vfio-ap: No need to disable IRQ after queue reset
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Halil Pasic <pasic@linux.ibm.com>
X-Patchwork-Id: 12035003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C9932C433E0
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:21:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 688B223877
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:21:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727338AbhAUHVi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 02:21:38 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:23472 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727315AbhAUHVL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 02:21:11 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10L73L2M143105;
        Thu, 21 Jan 2021 02:20:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=wS5GBDEocZ11XduwRcOrqMr8dN0POeiBwMSExeOtEio=;
 b=ckOqnqFdrmQ0Dt9iHEsgmSl1Gzrx6jAHvvigRcwND3AzaIuCMM/0dsieBl3PNk1r1DDW
 ehEL1UbM+oLa+KGVaTYwwpkneV0Z2SPFS7hXC6ybn/KtPu5vL8MZgz4yhci5Rr0qX02u
 I+p41DCXGsJA8+rmYKZkS3MS1rF+hnY8f9uG0YZhwnURYruk++T3/9ZjW6AMZa/B8uKY
 1Wmw6xvTPAAatNyc1ZYkzrSgcyY3/0xVaMSkM+4qmDeiBwz+uKAvA75IAioACI2l8tmM
 YEcYHfI0Qp0nLVcVc8ZDA0WacnkNy6OiwUej0sNKaw7IY0SC81SpxUw7bpSgvqpW5TDm 5Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3674kgrv1t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 02:20:24 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10L73O53143172;
        Thu, 21 Jan 2021 02:20:23 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3674kgrv18-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 02:20:23 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10L7IsDh023437;
        Thu, 21 Jan 2021 07:20:21 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 3668nwsd8n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 07:20:21 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10L7KIBJ38011306
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 07:20:18 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9701111C06C;
        Thu, 21 Jan 2021 07:20:18 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1946B11C04A;
        Thu, 21 Jan 2021 07:20:18 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 07:20:18 +0000 (GMT)
From: Halil Pasic <pasic@linux.ibm.com>
To: Tony Krowiak <akrowiak@linux.ibm.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Halil Pasic <pasic@linux.ibm.com>, stable@vger.kernel.org,
        Pierre Morel <pmorel@linux.ibm.com>,
        Harald Freudenberger <freude@linux.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        mjrosato@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com, frankja@linux.ibm.com,
        david@redhat.com
Subject: [PATCH 1/1] s390/vfio-ap: No need to disable IRQ after queue reset
Date: Thu, 21 Jan 2021 08:20:08 +0100
Message-Id: <20210121072008.76523-1-pasic@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_03:2021-01-20,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 impostorscore=0
 clxscore=1015 phishscore=0 mlxlogscore=999 malwarescore=0 suspectscore=0
 lowpriorityscore=0 adultscore=0 mlxscore=0 bulkscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101210035
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tony Krowiak <akrowiak@linux.ibm.com>

The queues assigned to a matrix mediated device are currently reset when:

* The VFIO_DEVICE_RESET ioctl is invoked
* The mdev fd is closed by userspace (QEMU)
* The mdev is removed from sysfs.

Immediately after the reset of a queue, a call is made to disable
interrupts for the queue. This is entirely unnecessary because the reset of
a queue disables interrupts, so this will be removed.

Furthermore, vfio_ap_irq_disable() does an unconditional PQAP/AQIC which
can result in a specification exception (when the corresponding facility
is not available), so this is actually a bugfix.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
[pasic@linux.ibm.com: minor rework before merging]
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Fixes: ec89b55e3bce ("s390: ap: implement PAPQ AQIC interception in kernel")
Cc: <stable@vger.kernel.org>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Since it turned out disabling the interrupts via PQAP/AQIC is not only
unnecesary but also buggy, we decided to put this patch, which
used to be apart of the series https://lkml.org/lkml/2020/12/22/757 on the fast
lane.

If the backports turn out to be a bother, which I hope won't be the case
not, I am happy to help with those.

---
 drivers/s390/crypto/vfio_ap_drv.c     |   6 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 100 ++++++++++++++++----------
 drivers/s390/crypto/vfio_ap_private.h |  12 ++--
 3 files changed, 69 insertions(+), 49 deletions(-)


base-commit: 9791581c049c10929e97098374dd1716a81fefcc

```
#### [PATCH 1/1] vhost scsi: allocate vhost_scsi with GFP_NOWAIT to avoid delay
##### From: Dongli Zhang <dongli.zhang@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongli Zhang <dongli.zhang@oracle.com>
X-Patchwork-Id: 12034697
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6754EC433E6
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 05:08:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0254C238EB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 05:08:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728570AbhAUFIL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 00:08:11 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:44272 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727550AbhAUFEg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Jan 2021 00:04:36 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10L520Af147649;
        Thu, 21 Jan 2021 05:03:45 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-type : mime-version;
 s=corp-2020-01-29; bh=zKlunICeRZRHzu7ogVf19W538S3T89UdmgDP0LASK8c=;
 b=V2D7Mq/Kh0ghlPOptODm5KhmfsGmZonFc0C+av3Kih/E+PBRoJWpEAb/ZSBm+3KoRwX2
 jRW7ANysBbp+Caqxln9PxYiFqxkahBmNAFdvJ1wZVhjgdir3wIJPEZgMLrw7MAP6+1n8
 UCUgR9EBy6ja5z81h5XqUkSyJv9qJwbgqQxmturqaYwYJLQDayJGldFQ4KU6SiPYvSJW
 3TqOL6XPymxZf2vpg/IhcBj2ygHEu2Les+R6bdiinNLPOXxVZFC7aX9MDu8rFQQ1yKgm
 WQ2vRfKeNUWZeVo2TBCoZmgKmw9wlTK+JzpwDp4yAc2QTaQ+0Ps/c00thjJfFd8ddlJ9 pw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 3668qmwhjm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 05:03:45 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10L4xqIk061313;
        Thu, 21 Jan 2021 05:01:45 GMT
Received: from nam02-cy1-obe.outbound.protection.outlook.com
 (mail-cys01nam02lp2052.outbound.protection.outlook.com [104.47.37.52])
        by aserp3020.oracle.com with ESMTP id 3668rf39p5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 05:01:45 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=naTgH9Wt0kPBxh9BA3gbwodVgzYphvap9rzX3jo7EO03xzzhsfTm6MmcOQhSZOdBqIZzQYqyllUZdNL24UmWzRnPQiVie2nQu7a35uBVLIk3BRSWkOoWB3RYZ6AgZEZ7X0qSUhRp3jtju1braN80NpGaAHd6aFsS81NDd89KY1fgpqPR0CoLAEKQIkZbpCdWYPtY3pZUGyU6x9HupPelURnoPgby/ejfODex/PYuE93YHpDPqde/eg+1MfdCM8KMLPLT+0dz4/fD4OtOeql0yBS/TSRfbbfh4iQ5GAFOukdlmK/qJySDxj3ExNC1yIvrCN/D2RKOAf+AUYGoqcpgBw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zKlunICeRZRHzu7ogVf19W538S3T89UdmgDP0LASK8c=;
 b=TGdeiLNkfQKhmmoJICeWl8VNO4J2CwrkLhYtQDoJ9th4sC+xYSoTN2dEvMXDaHLCbmUGhL+rz9V3++UnTNW00xEt/2NqjrVrW/iu/O4AtbB4v3c7dwsScKowJ1L8m2AEc5IlFedpB6hbzPZpVT59qKf4F+mV7siyW/2tNvCmLwDxcAIlPoEQ52RHCtD/i9vY3lb5a3ltdUunpwxGTTJDAN/5k+Ve2fZqEI1p+cFtuFz0ANRyoSPsVmrRNvNSLCCM2YiN1/acKCaSVJmOY7P317gwqw04DE+AgXPgpe4BYUH7eQ6LJKK+Kd7ZLloqI3g7yuEBk/Y+ssBF7rvbtsFtCw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=zKlunICeRZRHzu7ogVf19W538S3T89UdmgDP0LASK8c=;
 b=sClci4VlLwi48BwNEniuGAyKEFhxQ7J6LCVAHvdFZhkndPKUEz2Cu3Hyl83oOKUyNdBhpj/tP5uVuCYW/GMrWaQCphd16RuF6Oh1wfo8r1NnjSnaHwJIt+WCuYsf9KCsZ4gC0b6p5NSj1MsFWAIG0R5/alPJJMo9volC5G5viq0=
Authentication-Results: lists.linux-foundation.org; dkim=none (message not
 signed) header.d=none;lists.linux-foundation.org; dmarc=none action=none
 header.from=oracle.com;
Received: from BYAPR10MB2663.namprd10.prod.outlook.com (2603:10b6:a02:a9::20)
 by BYAPR10MB3255.namprd10.prod.outlook.com (2603:10b6:a03:156::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10; Thu, 21 Jan
 2021 05:01:43 +0000
Received: from BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::644d:92e4:7b5d:f8c1]) by BYAPR10MB2663.namprd10.prod.outlook.com
 ([fe80::644d:92e4:7b5d:f8c1%5]) with mapi id 15.20.3784.013; Thu, 21 Jan 2021
 05:01:43 +0000
From: Dongli Zhang <dongli.zhang@oracle.com>
To: virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, mst@redhat.com, jasowang@redhat.com,
        pbonzini@redhat.com, stefanha@redhat.com, joe.jin@oracle.com,
        aruna.ramakrishna@oracle.com
Subject: [PATCH 1/1] vhost scsi: allocate vhost_scsi with GFP_NOWAIT to avoid
 delay
Date: Wed, 20 Jan 2021 21:03:28 -0800
Message-Id: <20210121050328.7891-1-dongli.zhang@oracle.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [138.3.200.16]
X-ClientProxiedBy: CH0PR13CA0029.namprd13.prod.outlook.com
 (2603:10b6:610:b1::34) To BYAPR10MB2663.namprd10.prod.outlook.com
 (2603:10b6:a02:a9::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (138.3.200.16) by
 CH0PR13CA0029.namprd13.prod.outlook.com (2603:10b6:610:b1::34) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.8 via Frontend
 Transport; Thu, 21 Jan 2021 05:01:41 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 37813143-6823-431c-3364-08d8bdc9a542
X-MS-TrafficTypeDiagnostic: BYAPR10MB3255:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BYAPR10MB32558115C01C3555EDE28AB2F0A10@BYAPR10MB3255.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:519;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 n4ZHJ4jt1Oa6YWUrEvh0Sd1NOmREhKxD4e58V5DZPkbTK+ilv2+4rccYBfsEmmRfsM8tQSFzTR1lOsUNUnd+usPr+yXEJqys7jjxDwNo9AgENJm88hP3qbPz30EZhFeItxVZ8N6EgLr49z9UMCExLMTWvad0BEKLRBxqPgbg4FZ0SqjSLPHY8Teyq3wh29eR1SJoH6MwZYi/cJ4php5zZJn1OTFjdFxvJ6b4gZFaVN/UbH2GAolf9+RcztWh1WKQksgpWvUfxvLYWSXbqGw4FFo6UuWJxHyOHlaZzbjNPEUOSGVJc+y3r8PBo9jz3q20EjgQ51PU3blrFyqw2CNDFCbAhvKuMpzvWnEnvys5jIYekvHV1C5AnhczeYt5znQeUPuoZAfQgub+3klZRJvFIqEb10RDje0vJ0vuP0Bl5hmNAJ9dvevn2m9JCsch23eYMhGYMaZ+41AdGycxBViKLQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BYAPR10MB2663.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(346002)(136003)(396003)(366004)(376002)(39860400002)(5660300002)(86362001)(8936002)(36756003)(186003)(508600001)(2616005)(83380400001)(316002)(6506007)(66476007)(52116002)(956004)(66946007)(8676002)(4326008)(44832011)(107886003)(66556008)(2906002)(1076003)(69590400011)(6512007)(6666004)(26005)(16526019)(6486002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 s7dBf+6Bc4hmkHwqtALaDHXiuZk0nreKrdl5BTpoTqOcLJvlL0TlH7fBMfi7+umrQ22rSCafCIS3dulD9AOOCYxgHD9EHffcZgByO3VwYtczmYZ/mflYrSczlyZpfAY2b6PqMEQuVkzm8CCRaMF/u7RaUzTrOaLI8mq2lK6cLTnKlu1u6Yuz62HIApO3bfy0X647UQMdC3NPSD45N0WJPl/z+LJmxO9Hb8wEWuVqKT2hRINj4w+Cgr2lvRN0U4AbIYXIkuI081srCjMyO0WRsTde2iFNmXBWf1lQxtaNAoIqZfzIsc++wtUXb8x9vA7LpPgqV+TIDqo2qiy1lym04GL976O5YmPk6azdDcqDbZR50bG457b+flcIlUizNWKesN7fUEdWsSNtGTo89rfnCbllJx5gRdHnwNJUIoN0Eo2jYzqe4k9k8UXdCrU8UgOMQBqZEUzOtJ7HLNHeFKL1w6bdbzd8czRbhGEn96SxWBrerkqWLXsnDzk5AnGxQR9OJsiV/1RGJx1hwt9+JVXw+uQPZ4qbjSUiVTuQ68SemEe6Y2emx+BhHd9290Ytdc2bv0SbBv+I30G2tXV0w3My/tJmDbeOTbqKAhTpXegj0eH6B5lEcWMWGdC6LE/K56vughBNRVczV1/hCpa1K0p58kMfh4cSzw7TuOuzCkG9Pqoe+wVUTYv4QjpTIWepVwStunXev+4VWtmf6rl7gWmCSnNroXqELAi2PzOAyglvNkzWT1oW/O7FTrwnFKGA2OboKbXSBKQDuGO8G+2JlFJeRspQf4vfctaTRN8Wyym53+wpFQtPi1MdRzJAdovk311IW53Io7NIWX/aErIxy/QilmWicoVzzNKfivgLLED4ZC1MLAWIq2eIsOP7Bf5x3V+TyUqI6A+TRDFZGgPvcxsOABg9KOOcns/StJlMVg6lmtOA3eYUgbfLSBwxBMtGPftAycxpRZrDeERDbL8gV4Cq6gK8tUQyCOQ7CE6ANAbUxLc=
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 37813143-6823-431c-3364-08d8bdc9a542
X-MS-Exchange-CrossTenant-AuthSource: BYAPR10MB2663.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 21 Jan 2021 05:01:43.3779
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TNqSupVapbHCXJfqpXi5oGjpriUC1UrC6UX7/6Bup8tHPOcsI+AKWX5JqUC+mm8+q5g8JWyHh8ZE0zlweBWh3A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BYAPR10MB3255
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9870
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 spamscore=0 suspectscore=0
 adultscore=0 mlxlogscore=999 bulkscore=0 malwarescore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101210023
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9870
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 priorityscore=1501
 adultscore=0 impostorscore=0 mlxlogscore=999 spamscore=0 suspectscore=0
 phishscore=0 clxscore=1011 bulkscore=0 mlxscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101210023
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The size of 'struct vhost_scsi' is order-10 (~2.3MB). It may take long time
delay by kzalloc() to compact memory pages when there is a lack of
high-order pages. As a result, there is latency to create a VM (with
vhost-scsi) or to hotadd vhost-scsi-based storage.

The prior commit 595cb754983d ("vhost/scsi: use vmalloc for order-10
allocation") prefers to fallback only when really needed, while this patch
changes allocation to GFP_NOWAIT in order to avoid the delay caused by
memory page compact.

Cc: Aruna Ramakrishna <aruna.ramakrishna@oracle.com>
Cc: Joe Jin <joe.jin@oracle.com>
Signed-off-by: Dongli Zhang <dongli.zhang@oracle.com>
---
Another option is to rework by reducing the size of 'struct vhost_scsi',
e.g., by replacing inline vhost_scsi.vqs with just memory pointers while
each vhost_scsi.vqs[i] should be allocated separately. Please let me
know if that option is better.

 drivers/vhost/scsi.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [DRAFT RFC] ioeventfd/ioregionfd support in vfio-userThread-Topic: [DRAFT RFC] ioeventfd/ioregionfd support in vfio-user
##### From: John Levon <john.levon@nutanix.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Levon <john.levon@nutanix.com>
X-Patchwork-Id: 12036951
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,PDS_BAD_THREAD_QP_64,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C6AD3C433E6
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 16:31:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 72DB1239D4
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 16:31:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387847AbhAUQay (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 11:30:54 -0500
Received: from mx0a-002c1b01.pphosted.com ([148.163.151.68]:35694 "EHLO
        mx0a-002c1b01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1733264AbhAUQ3z (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 11:29:55 -0500
X-Greylist: delayed 1183 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 21 Jan 2021 11:29:53 EST
Received: from pps.filterd (m0127839.ppops.net [127.0.0.1])
        by mx0a-002c1b01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 10LG3LsP028599;
        Thu, 21 Jan 2021 08:09:12 -0800
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nutanix.com;
 h=from : to : subject
 : date : message-id : content-type : content-id :
 content-transfer-encoding : mime-version; s=proofpoint20171006;
 bh=Zjiqr8nfwvucEVZPHEElIOOdN7ztxYkwPFaaTBI3e9M=;
 b=IUUZWTBWIwvkdO96EtZjGzN2jpp1Z9cdf2fqslPHl3NBuUwAZvYzm1J5E1rDIwSkZpHu
 7PN9IdY7YozxKa6zgJeXR2CveC1j7i88LRXb/dn/chJVuS4EgykyR9eCuAzToTdPvO9E
 76kGkZNw6kTjAhyO8++kcisM3telHux+3ZyYx2k1kcX+FHIZFLxMDyZqE9iDmzmWQEV2
 3il/YhEjfCplmw3pDD0RFhwKiGQE+9n1eC7C8L3ov8cC0ZXPObmZVF625EC5TK/4jzjf
 fKxS+Sm0IQAOXuRearm4nx6uIFjnA+SXLms33Rl0hUufDvuuoUBBqleefkFW4o7k3REf fw==
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2100.outbound.protection.outlook.com [104.47.70.100])
        by mx0a-002c1b01.pphosted.com with ESMTP id 3668p9vqc4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 08:09:11 -0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=dzathp+sArlEIPN1+ntnWuHaRX5kVEzLkwdwNi9J8kTRejOXgZv9l2eU0vwRz3Do0BVDDhz7P1HgKgY+4o50pgcRo+yrQQMDP26Ki85eEPxfRTUAfn0Qfc9bl2h5DxdUOVV8f9KFghWuPAx72YARWcEdNnbxABdGQeKPnO6SYoUJnlQzmvebh+hcDUVF18yXmvU0vG0RH9GxCGNJI9Raj9TSE5D25VOryitcGZCX/vRjFb8q1hVqplJKR0QeXguP7K3b2X+MgNIHH/WLqDtLcH4twyq9ogldnAxQo7gLz2zDAH+ZZ9YgXkmmHg0KsVyoQvVPe9lVA4UGHn5fR6tNeA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Zjiqr8nfwvucEVZPHEElIOOdN7ztxYkwPFaaTBI3e9M=;
 b=cZH+Z1GhYJ3CjnN6hH7cgSqiwX6DGyyZ7EdND75/ZlrK9kwv/CSmfVg2dK4HPfm+Tbqgu8hc/U+HGzoJULzcx/9pRgptbWvGDj2AkWr8WVBVXcx6GDQ+FxH7+Sqg0StWbYcPuNeWY3tWNON4QIHwWfMtBhkR1VZ6qT0FEPnQCI5EKS/FR0r/316sRn2vRpxcYFUeKOm6r1PUdb9scTxXF0jICL55nRc1fWVK5cbBEqLMWVEKreZgmz9xRspZYI0kiRAEVPInuJtpIYw9HwPQNKaupVurDtkmDe8hTZt5brtWjtdk0+KH3cxO6zRxv+++K4jzTC09VF4/x1B9uO5btg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nutanix.com; dmarc=pass action=none header.from=nutanix.com;
 dkim=pass header.d=nutanix.com; arc=none
Received: from BL0PR02MB4580.namprd02.prod.outlook.com (2603:10b6:208:40::27)
 by BL0PR02MB3745.namprd02.prod.outlook.com (2603:10b6:207:43::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.11; Thu, 21 Jan
 2021 16:09:09 +0000
Received: from BL0PR02MB4580.namprd02.prod.outlook.com
 ([fe80::d853:efb7:2d8b:f191]) by BL0PR02MB4580.namprd02.prod.outlook.com
 ([fe80::d853:efb7:2d8b:f191%5]) with mapi id 15.20.3784.013; Thu, 21 Jan 2021
 16:09:09 +0000
From: John Levon <john.levon@nutanix.com>
To: "libvfio-user-devel@nongnu.org" <libvfio-user-devel@nongnu.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        "john.g.johnson@oracle.com" <john.g.johnson@oracle.com>,
        "qemu-devel@nongnu.org" <qemu-devel@nongnu.org>
Subject: [DRAFT RFC] ioeventfd/ioregionfd support in vfio-user
Thread-Topic: [DRAFT RFC] ioeventfd/ioregionfd support in vfio-user
Thread-Index: AQHW8A/A4RU7AycUJk25Cn4pd6oBpg==
Date: Thu, 21 Jan 2021 16:09:09 +0000
Message-ID: <20210121160905.GA314820@sent>
Accept-Language: en-GB, en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
authentication-results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=nutanix.com;
x-originating-ip: [88.98.93.30]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 2e4607d1-0576-4932-d710-08d8be26e292
x-ms-traffictypediagnostic: BL0PR02MB3745:
x-microsoft-antispam-prvs: 
 <BL0PR02MB3745DD868834FF6E7826334997A19@BL0PR02MB3745.namprd02.prod.outlook.com>
x-proofpoint-crosstenant: true
x-ms-oob-tlc-oobclassifiers: OLM:10000;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 BLj0Llqr6M7zxX8kX8KaHee5PInjWng9jie2ZJOZuoTBEHdMa40XYS3sJLa+n49Stp95Tx2yafcS5CgOngJjMtKkgt9W4+Pf7f6fx+gS/vBp0deT5rPfJjc90kPhAycNKDnrtsT0ZCZ1Mis+kthLEZAO/iMPfMbNCfxv/QZXH9AFTFSHGaRG4pFlFtGQrlgqLux3HeLILUo5c3kP9blPptmJpltdYaZE40guPUb695MCkFh1TBvjUdS+yamVRw5ssN26Jh+DpKbftpAXy+B425LFfeGCKgeAaNL1OlhvAO/ty1bIVuXnfxhSKCfr9/DkeSI3tzY1JCtzn43pQ++20TIt2u3fY70BuEIyAyyfYLE5uFa3nuXVvkFbGNtgqFoV4FszHxYwxcOiaXzGvQFC+Ml6XTfTb8ZTTFu368m7JLQOn48HUl+7OEGicvpLP5f67/d3nibvdnZsUI3jbrI3vRZZESupgTsQwIl+in79AesXK8ji8sa+kvCKROMCrJXMnFq82VbTi0jNcQcn/aRef1FPaSbz/xgjkJjDZJ9GThIRzrpbB1FYzsSWbFa2gSWx6hvpgKtFIL8NNq7AF0nvNhEu0MzT1jD0+2mOawNdaRw=
x-forefront-antispam-report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BL0PR02MB4580.namprd02.prod.outlook.com;PTR:;CAT:NONE;SFS:(7916004)(396003)(136003)(346002)(376002)(366004)(39860400002)(110136005)(83380400001)(8676002)(30864003)(316002)(5660300002)(33716001)(86362001)(8936002)(44832011)(76116006)(64756008)(186003)(26005)(91956017)(66556008)(66946007)(66476007)(66446008)(9686003)(478600001)(6486002)(2906002)(6512007)(1076003)(966005)(71200400001)(33656002)(6506007);DIR:OUT;SFP:1102;
x-ms-exchange-antispam-messagedata: 
 3Xve7U7bYFgy+oPTp5rCLlpnqKIy2banJZ+XJKboVw0HTn5RFyDWEgd6h9ioyJkYK5tFb55eyzseqkgn/NHeEeqr/uaVh57RXEPGQVzzeTdNrShAjxZ+YJDPe9B7k1qP42eg5uT4aF40wDeQ1ZN8VKsIbiatgd/+j+W/0hFhRSLaF+id/GUBcRympfis/mgHHSBRiRm/u33kYwNYzNBrO80+74qqrPUWSyXlToURXSjwbcMrvwJDaNt3oN2ESw18u7jc7xyuNKyyZRYVFDvDvSbRLv1GJfPi1hXPxed09mBVVXAxkqdptqWOCZnlQkydP6Hj6lP7TYL/+466r4YzJTdn3dzxkC4JbtS2Y2lgozaDyCrofb8eSSaUlihMNMMwF0puPLTZft1rZLR2U3vCuTLbUysNrTYX6iQedPEanv7AzWH7U23SBvD5cbHzPd4Dhoob8XgXIq02Fals4ueDonh4UAxu0jfg6Jl16QBkgTly3+/dNuiPPGxaKzScn/6pcskzQVMtaBQ34NP+Jn8CXuEsMT+UIp/SroIyiudkOUoCCnCvhzdbGMeU4xaCsMG+puRQCiTpbx3m7pWoC2PuxEr0hyyPylozcwBhoKtmZwup8s/kcVLjw3DOTZcZBPs2DGXB/9df/XtAUEhHF8pwZMzJ8w+zxdVjlsUVGUjWujgv0V3NLVPzbO1f+nKkgNKym5oUbch2fFw9oXjBVLHXksX7mcXI4OJnZkfLNUBYAxiKysnuubgBrqGeC4KcMn9yPgo/hhSYdeLLlV54urMepcz1IBNQynDQQGs4Rferrha9+xNR2R54Mzar+kdcx6/C+1gzTEvCz0C/p1t0mjU/kMEBogUNsKjg3fcRG55if5dPpJQnpknKNCJA4WIMuU3nN/O/O+aTHRZRJeS2z6jr6P6DxKUgeFfZ3gJpKGJ5mujrt3sjT9Wxv2cK96lsNQDgdyh8HFBLkQVpV43tSdgUA2O3zIHRTDkLrEJGqUC2u6pC5Nkf8snXU3RCeH+mUmZA7ZgbNdhtcAYIT2IzPJftTwWXDHQrzNhp99ylwk/ALABm+e3c/3WayblE9hwNPaBG
x-ms-exchange-transport-forked: True
Content-ID: <E18E53B5570D2644AB65B224EA875FB7@namprd02.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: nutanix.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-AuthSource: BL0PR02MB4580.namprd02.prod.outlook.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2e4607d1-0576-4932-d710-08d8be26e292
X-MS-Exchange-CrossTenant-originalarrivaltime: 21 Jan 2021 16:09:09.0804
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: bb047546-786f-4de1-bd75-24e5b6f79043
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 aD9a8YYdk0zp8TxtuyGccYOd7rNB7sXCACBCSXTvY7cD/hk9FYCxVjAt8hOzm5s4VXQddmaxeYgCJlRKRD83wg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BL0PR02MB3745
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_08:2021-01-21,2021-01-21 signatures=0
X-Proofpoint-Spam-Reason: safe
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi, please take a look. For context, this addition is against the current
https://github.com/nutanix/libvfio-user/blob/master/docs/vfio-user.rst
specification.

kvm@ readers: Stefan suggested this may be of interest from a VFIO point of
view, in case there is any potential cross-over in defining how to wire up these
fds.

Note that this is a new message instead of adding a new region capability to
VFIO_USER_DEVICE_GET_REGION_INFO: with a new capability, there's no way for the
server to know if ioeventfd/ioregionfd is actually used/requested by the client
(the client would just have to close those fds if it didn't want to use FDs). An
explicit new call is much clearer for this.

The ioregionfd feature itself is at proposal stage, so there's a good chance of
further changes depending on that.

I also have these pending issues so far:

1) I'm not familiar with CCW bus, so don't know if
KVM_IOEVENTFD_FLAG_VIRTIO_CCW_NOTIFY flag makes sense or is supportable in
vfio-user context

2) if ioregionfd subsumes all ioeventfd use cases, we can remove the distinction
from this API, and the client caller can translate to ioregionfd or ioeventfd as
needed

3) is it neccessary for the client to indicate support (e.g. lacking ioregionfd
support) ?

4) (ioregionfd issue) region_id is 4 bytes, which seems a little awkward from
the server side: this has to encode both the region ID as well as the offset of
the sub-region within that region. Can this be 64 bits wide?

thanks
john

(NB: I edited the diff so the new sections are more readable.)

 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 6                      |
+| Command      | 7                      |
 +--------------+------------------------+
 | Message size | 32                     |
 +--------------+------------------------+
@@ -1212,7 +1380,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 7                      |
+| Command      | 8                      |
 +--------------+------------------------+
 | Message size | 36 + any data          |
 +--------------+------------------------+
@@ -1370,7 +1538,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 8                      |
+| Command      | 9                      |
 +--------------+------------------------+
 | Message size | 32 + data size         |
 +--------------+------------------------+
@@ -1397,7 +1565,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 9                      |
+| Command      | 10                     |
 +--------------+------------------------+
 | Message size | 32 + data size         |
 +--------------+------------------------+
@@ -1424,7 +1592,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 10                     |
+| Command      | 11                     |
 +--------------+------------------------+
 | Message size | 28 + data size         |
 +--------------+------------------------+
@@ -1451,7 +1619,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 11                     |
+| Command      | 12                     |
 +--------------+------------------------+
 | Message size | 28 + data size         |
 +--------------+------------------------+
@@ -1478,7 +1646,7 @@ Message format
 +================+========================+
 | Message ID     | <ID>                   |
 +----------------+------------------------+
-| Command        | 12                     |
+| Command        | 13                     |
 +----------------+------------------------+
 | Message size   | 20                     |
 +----------------+------------------------+
@@ -1515,7 +1683,7 @@ Message format
 +==============+========================+
 | Message ID   | <ID>                   |
 +--------------+------------------------+
-| Command      | 13                     |
+| Command      | 14                     |
 +--------------+------------------------+
 | Message size | 16                     |
 +--------------+------------------------+
@@ -1537,7 +1705,7 @@ Message format
 +====================+========================+
 | Message ID         | <ID>                   |
 +--------------------+------------------------+
-| Command            | 14                     |
+| Command            | 15                     |
 +--------------------+------------------------+
 | Message size       | 16                     |
 +--------------------+------------------------+

```
#### [kvm-unit-tests PATCH v1 1/2] x86: smap: fix the test to work with new allocator
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12035771
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1BA93C433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 12:02:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC8CE2395B
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 12:02:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730616AbhAUMCK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 07:02:10 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:20206 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728218AbhAULTQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 06:19:16 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10LB2Bp6085099;
        Thu, 21 Jan 2021 06:18:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=kQyHjz/G9CDjM2bVCv5AXxuqpPGa1wPvklE7QzVEDEI=;
 b=M4ouzfSn5hX4v4vTclTGzB4EOF/Zt4TSvLjqvfrcykDs4KbDH81Q+su+RbMoUxJg0Ml5
 ZD1Vfkej/QNRsDsLCeCKqze12LBQshgrfW9TR50e3U8P76n2PuHOgs/z8uNqUwtga29Z
 pTgeHGTssZzWGVlL3PPnrh48nn3ygrbFFwJldnHRakvMxveuTUMGMZ7aAnsDj6tZLX7E
 Yg/pCmAHSwshDX2uD0/Uq66QnCK2RVHDKpZazJrs8ZZpjUVDWSQq2kO5JYs8RNKpbdcN
 d4FwAbBTAqGXp6zIOyAtQuK0ytVMphNSHtFL56sm6E+IEoL45P7d4nFRCV1LDYZC/VF/ Jg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3678ba8j3q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 06:18:31 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10LB2RMF087302;
        Thu, 21 Jan 2021 06:18:31 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 3678ba8j2e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 06:18:31 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10LBI5Ad016168;
        Thu, 21 Jan 2021 11:18:29 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 3668pask57-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 11:18:28 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10LBIK8B29294854
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 11:18:20 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9D879AE051;
        Thu, 21 Jan 2021 11:18:26 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 21649AE058;
        Thu, 21 Jan 2021 11:18:26 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.4.167])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 11:18:26 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, lvivier@redhat.com,
        nadav.amit@gmail.com, krish.sadhukhan@oracle.com,
        dmatlack@google.com, seanjc@google.com
Subject: [kvm-unit-tests PATCH v1 1/2] x86: smap: fix the test to work with
 new allocator
Date: Thu, 21 Jan 2021 12:18:07 +0100
Message-Id: <20210121111808.619347-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210121111808.619347-1-imbrenda@linux.ibm.com>
References: <20210121111808.619347-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_04:2021-01-21,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0
 priorityscore=1501 impostorscore=0 adultscore=0 malwarescore=0
 mlxlogscore=999 spamscore=0 bulkscore=0 suspectscore=0 mlxscore=0
 clxscore=1015 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2101210056
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The test used to simply take a chunk of memory and use it, hoping the
memory allocator would never touch it. The memory area used was exactly
at the beginning of the 16M boundary.

The new allocator stores metadata information there, and causes the
test to fail.

This patch uses the new features of the allocator to properly reserve
a memory block. To make things easier and cleaner, the memory area used
is now smaller and starts at 8M.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reported-by: David Matlack <dmatlack@google.com>
---
 x86/smap.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.11, take #2
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12037119
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02CA6C433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:02:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A7D5923A51
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:02:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387465AbhAUPtV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 10:49:21 -0500
Received: from mail.kernel.org ([198.145.29.99]:49948 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387554AbhAUPsG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Jan 2021 10:48:06 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 3963722C7B;
        Thu, 21 Jan 2021 15:47:26 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l2cB9-009E2f-Vg; Thu, 21 Jan 2021 15:47:24 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        Rick Edgecombe <rick.p.edgecombe@intel.com>,
        Steven Price <steven.price@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.11, take #2
Date: Thu, 21 Jan 2021 15:46:53 +0000
Message-Id: <20210121154653.2907836-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 catalin.marinas@arm.com, dbrazdil@google.com, rick.p.edgecombe@intel.com,
 steven.price@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kernel-team@android.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

This is the second batch of fixes for 5.11. Mostly PMU fixes,
but also a couple of memory tagging fixes as well as a PSCI
firmware workaround.

Please pull,

	M.

The following changes since commit 45ba7b195a369f35cb39094fdb32efe5908b34ad:

  arm64: cpufeature: remove non-exist CONFIG_KVM_ARM_HOST (2021-01-05 13:22:07 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.11-2

for you to fetch changes up to 139bc8a6146d92822c866cf2fd410159c56b3648:

  KVM: Forbid the use of tagged userspace addresses for memslots (2021-01-21 14:17:36 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.11, take #2

- Don't allow tagged pointers to point to memslots
- Filter out ARMv8.1+ PMU events on v8.0 hardware
- Hide PMU registers from userspace when no PMU is configured
- More PMU cleanups
- Don't try to handle broken PSCI firmware
- More sys_reg() to reg_to_encoding() conversions

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm64: Use the reg_to_encoding() macro instead of sys_reg()

David Brazdil (1):
      KVM: arm64: Allow PSCI SYSTEM_OFF/RESET to return

Marc Zyngier (4):
      KVM: arm64: Hide PMU registers from userspace when not available
      KVM: arm64: Simplify handling of absent PMU system registers
      KVM: arm64: Filter out v8.1+ events on v8.0 HW
      KVM: Forbid the use of tagged userspace addresses for memslots

Steven Price (1):
      KVM: arm64: Compute TPIDR_EL2 ignoring MTE tag

 Documentation/virt/kvm/api.rst       |  3 ++
 arch/arm64/kvm/arm.c                 |  3 +-
 arch/arm64/kvm/hyp/nvhe/psci-relay.c | 13 ++---
 arch/arm64/kvm/pmu-emul.c            | 10 ++--
 arch/arm64/kvm/sys_regs.c            | 93 ++++++++++++++++++++++--------------
 virt/kvm/kvm_main.c                  |  1 +
 6 files changed, 74 insertions(+), 49 deletions(-)
```
#### [PATCH v2 1/4] KVM: x86: Factor out x86 instruction emulation with decoding
##### From: Wei Huang <wei.huang2@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wei Huang <wei.huang2@amd.com>
X-Patchwork-Id: 12034909
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89C1FC433DB
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 06:57:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47FE82396F
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 06:57:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726294AbhAUG4w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 01:56:52 -0500
Received: from mail-eopbgr760075.outbound.protection.outlook.com
 ([40.107.76.75]:35598
        "EHLO NAM02-CY1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725967AbhAUG4p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 21 Jan 2021 01:56:45 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=V8SHMWAbvPwhGac0kpsbsiyI8v0ITK/5DIYYWgpDDaGw6rU7+1iS3iQ+BibCbszlJnP3pkd6gzqTWVycuCqGlswFdkHpbnd7SM72ropO3ZRKo3oHmWxWpWI1BRulUPmHNBnUeS1rbxFytmTm5sIInDlrnQhnLrukUf7NmyoCg+Nkm3zdAwqmqQ9zN+9SVUoxRcaJBGLWBt7bMkQAzydLkDHSPP8+cVJQrnbstUvVkIs3z1I/PK5Uwjq2KoJEG9+vwutZ1wr9bPxZhTcTLsFoCTMEuSeelVH8APYZ+pf1yQkjq07n7ZOXKNR+kqZyalOewJYS6OgDOXbPmmtaAHj/VA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=/u2e1NwXSIFY6408TR3E4ui0BK0d0t1eZ5AiNvDwuMM=;
 b=MCF1vuvFysDCntO17CN2K2eCabtGWaMm7d8JHBAgsHUcwy9iuNGGMrKiNOKqRdEzCD1f20SmsOcqFcR5Du1i/Wbr1UASc+1OWZCFoMtbDazb1lKEVpPqeZnvPzdLXsc/Yruu6ud/noyTQ8QYaWjt1W8QJbwTqZsaHNUxSH/TaK+INZEy3A4gWuN6JL6Z3XyoYnAz3mKudo12AW/kO37uzqwohc+nfn9VqDjo6z0Pa86g2PO9EgqW+8F8ITjsKv4ET1KFIXwdqpHgSRMaSyPmKYEXMKSKUvvW8mS3YCLPq4bLEFHGjBv8KeampzMa2HBnKzBBUBoUkD+XYFLo2DHefw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=/u2e1NwXSIFY6408TR3E4ui0BK0d0t1eZ5AiNvDwuMM=;
 b=dTI7u16VX0ZSigevAR6EntXyeTEceq8gCNta4+21KTP+y4fomDPR3q2TwtYqPsv4SNoMHfXOU9OS8UGgWr+BQolKQEbHfl8vTt5eebsc4iQE5tzOt8FvLvFyu24fGORNyksU47YRBGCaQ2FxoU9mY3vnID0h4PlLXJNBhLH1HIM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from MWHPR12MB1502.namprd12.prod.outlook.com (2603:10b6:301:10::20)
 by MW3PR12MB4441.namprd12.prod.outlook.com (2603:10b6:303:59::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.13; Thu, 21 Jan
 2021 06:56:09 +0000
Received: from MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::d06d:c93c:539d:5460]) by MWHPR12MB1502.namprd12.prod.outlook.com
 ([fe80::d06d:c93c:539d:5460%10]) with mapi id 15.20.3784.013; Thu, 21 Jan
 2021 06:56:09 +0000
From: Wei Huang <wei.huang2@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        vkuznets@redhat.com, mlevitsk@redhat.com, seanjc@google.com,
        joro@8bytes.org, bp@alien8.de, tglx@linutronix.de,
        mingo@redhat.com, x86@kernel.org, jmattson@google.com,
        wanpengli@tencent.com, bsd@redhat.com, dgilbert@redhat.com,
        luto@amacapital.net, wei.huang2@amd.com
Subject: [PATCH v2 1/4] KVM: x86: Factor out x86 instruction emulation with
 decoding
Date: Thu, 21 Jan 2021 01:55:05 -0500
Message-Id: <20210121065508.1169585-2-wei.huang2@amd.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210121065508.1169585-1-wei.huang2@amd.com>
References: <20210121065508.1169585-1-wei.huang2@amd.com>
X-Originating-IP: [66.187.233.206]
X-ClientProxiedBy: SG2PR0601CA0009.apcprd06.prod.outlook.com (2603:1096:3::19)
 To MWHPR12MB1502.namprd12.prod.outlook.com (2603:10b6:301:10::20)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from amd-daytona-06.khw1.lab.eng.bos.redhat.com (66.187.233.206) by
 SG2PR0601CA0009.apcprd06.prod.outlook.com (2603:1096:3::19) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.12 via Frontend
 Transport; Thu, 21 Jan 2021 06:56:00 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 37463c4a-4f8e-49c9-abfd-08d8bdd9a1b3
X-MS-TrafficTypeDiagnostic: MW3PR12MB4441:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MW3PR12MB4441E7400DB86CBA6CC476EBCFA19@MW3PR12MB4441.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 qPBvq8ahXDxjey6BYc+7Rq8nMkW+C91tnqPX5wIO9nIJDioAj1wmJLU09VuWBP3PYEYLTfeAU/0CfcQFpxX/6rOwaU/V4zCPdYPVSvpik3ZzHD6DHmbYoez59keJt0FdxmGdx5N3VpWMVmlzipGmm2fdBjnGEAkcok9ZBl190Smf37d9TxhpF2DacTfMaNh8+ic6mGpJm0YUXE70iP7+GA3TImBrVqgKYJbqOroWf48HlyBvJSabZ5xMxvNfc6BoHHTyZDDV3K0hYc2iRMjalJsdnv9dA6c7aoeYz7hxfl7NMd2gwqMTHU11vJKF3eyMpGDSh/q/OPYLoHc624MMjbmKokEtTLDLxhnjNwQ5VGHeSpMLJxrGNB8aR3BucyeNPSlpYN0Gw9praxKZs43iLA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MWHPR12MB1502.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(39860400002)(396003)(366004)(136003)(376002)(346002)(83380400001)(52116002)(8936002)(86362001)(6506007)(66476007)(6512007)(6916009)(2906002)(186003)(478600001)(4326008)(6486002)(16526019)(956004)(26005)(2616005)(36756003)(8676002)(1076003)(316002)(7416002)(5660300002)(66946007)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 uLOAEyE9FsQDBV1sNVWVgfg8L7g4z25jE9gOBH5TwF0C9IJSJ4ttHUch4LaNw59s7kQ3ORH+sIdDk9Fm+fhNnCpjpr8IEz7yMprGUjbaJbu186dJFiJuBQ/5hb073ZtcBASPSwKbRuy/sAVgxhALeQvWgJy1Hn1hkegq6cIM95Bfxxa7arwmsZ/DfsUAdFXUMR8PULEClP4J96lfmfVMp/rrYsBKHuUE9yHvCbPB6EvtE93njpT91/8CMRwLdM26ArGe4tGDiNo+YutfwZH3aO9QEqwEyKYTyph48JlnEENpuUnRVKFiAZE8lo6/ei9Wgy1okfA7C/92lAfnk1ARnY0+0jiN+iBdYttWzM6PPQOAyHvqPpEgKSXfMaiYb5ptsAQyrN6L6orJUhM+1SE89ror15WKGHX04ZPP7Zj1C2xDmdNUASuI2hh6AH+zl+VKZe10ALYR6kOo9CxDivWVYiEy05rWdBscUKRWbZ7v1TusY1tI1aoa6hb6lmeZ+1zAoaK/p2hUweFqxl9EjtxkV4L/P8VhvtOudjak/Q/03P0FW4WwZMXSFsGF1d7jzIs+K+vo1zty9ISKSOTVgTPrOfSqHd7iMdpdJYwBARJj9QXvaYE/43lXmNRlYylidIRiavYjeWnkFM0iAsqcVbosWtulAyxTvrVE4a9NeRU/ir1+l+zmdLbAyiJ8mbmqpwd/IE9qS1CEgMMDALmGpaWe8meJIi/pqG73M4NdMhfsDy1FQsOzDEshfXVbQOEtxg0fA2So2tD+jdn0AB/tRAx3ddr85+eeNbYlI1PSE/x6l79SgUPZsdYlQFSz5RRdtpBSftiFKYOzcFhT3JMudavlu/Y18eJQDVF73/6UqMGumONN0z0U3TxrQTfX/ODuVt/MBFhbg+7OIgLUszUhWB/IkclO4TXoXwsXVFSV/V+4DpohgCA9XeTIyIHGouux66qRVzfNuMyrjn2eF/C5CRxvtrDfmtnoXDQ6OhSoeMvdm4yagfJRKkL8aoTraZ3SK/RQ
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 37463c4a-4f8e-49c9-abfd-08d8bdd9a1b3
X-MS-Exchange-CrossTenant-AuthSource: MWHPR12MB1502.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 21 Jan 2021 06:56:09.5562
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 LRglpc6fglwsvcjVKKRorrzxuVLL+RQHcDrARB9Wv55asJEwOoMycnhfCvceVuHo
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MW3PR12MB4441
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the instruction decode part out of x86_emulate_instruction() for it
to be used in other places. Also kvm_clear_exception_queue() is moved
inside the if-statement as it doesn't apply when KVM are coming back from
userspace.

Co-developed-by: Bandan Das <bsd@redhat.com>
Signed-off-by: Bandan Das <bsd@redhat.com>
Signed-off-by: Wei Huang <wei.huang2@amd.com>
---
 arch/x86/kvm/x86.c | 63 +++++++++++++++++++++++++++++-----------------
 arch/x86/kvm/x86.h |  2 ++
 2 files changed, 42 insertions(+), 23 deletions(-)

```
#### [kvm-unit-tests PATCH] lib/s390x/sclp: Clarify that the CPUEntry array could be at a different spot
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 12034925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3F106C433E0
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:04:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F037423877
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:04:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727096AbhAUHEB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 02:04:01 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31731 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726477AbhAUHDj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 02:03:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611212533;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=k4womrgZC1t12zXUnXkUHJc1RDUUJ4HKh78lY5FVqYE=;
        b=gSKJYHqJm5MtrdesLSRQzmKhLJUFvxFn0xCAbUsIigGnb/zQMhblIusNgy6mtA1RZ+uK0j
        SeZZcIyelv7al3efygr8cl6IuhsJPM80XJ4QzNNsZfbwQcuRzVsDzrocSBaHrNE1nTG6u3
        CNTf8kgVFmoZHXHdOsUIveIOjsHtZSU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-261-q6Gp6TnFMlOIFURspEDrQQ-1; Thu, 21 Jan 2021 01:57:11 -0500
X-MC-Unique: q6Gp6TnFMlOIFURspEDrQQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1ACA9107ACE3;
        Thu, 21 Jan 2021 06:57:10 +0000 (UTC)
Received: from thuth.com (ovpn-112-82.ams2.redhat.com [10.36.112.82])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A9A9F9CA0;
        Thu, 21 Jan 2021 06:57:05 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Janosch Frank <frankja@linux.ibm.com>
Cc: David Hildenbrand <david@redhat.com>, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH] lib/s390x/sclp: Clarify that the CPUEntry
 array could be at a different spot
Date: Thu, 21 Jan 2021 07:57:03 +0100
Message-Id: <20210121065703.561444-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "struct CPUEntry entries[0]" in the ReadInfo structure is misleading
since the entries could be add a completely different spot. Replace it
by a proper comment instead.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp.h | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: vmx: Assign boolean values to a bool variable
##### From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Li <abaci-bugfix@linux.alibaba.com>
X-Patchwork-Id: 12035207
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 27466C433E9
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 08:53:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9F82239E4
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 08:53:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728176AbhAUIwo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 03:52:44 -0500
Received: from out4436.biz.mail.alibaba.com ([47.88.44.36]:43527 "EHLO
        out4436.biz.mail.alibaba.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728179AbhAUIt0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 03:49:26 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R261e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04400;MF=abaci-bugfix@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0UMPTpeq_1611218908;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:abaci-bugfix@linux.alibaba.com
 fp:SMTPD_---0UMPTpeq_1611218908)
          by smtp.aliyun-inc.com(127.0.0.1);
          Thu, 21 Jan 2021 16:48:32 +0800
From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
Subject: [PATCH] KVM: vmx: Assign boolean values to a bool variable
Date: Thu, 21 Jan 2021 16:48:26 +0800
Message-Id: <1611218906-71903-1-git-send-email-abaci-bugfix@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warnings:

./arch/x86/kvm/vmx/vmx.c:6798:1-27: WARNING: Assignment of 0/1
to bool variable.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
---
 arch/x86/kvm/vmx/vmx.c | 26 +++++++++++++-------------
 1 file changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH] kvm: x86/mmu: Assign boolean values to a bool variable
##### From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Li <abaci-bugfix@linux.alibaba.com>
X-Patchwork-Id: 12035005
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8360C433E0
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:22:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3E8223788
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 07:22:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727377AbhAUHWO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 02:22:14 -0500
Received: from out30-45.freemail.mail.aliyun.com ([115.124.30.45]:43804 "EHLO
        out30-45.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727303AbhAUHVE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 02:21:04 -0500
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R101e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=alimailimapcm10staff010182156082;MF=abaci-bugfix@linux.alibaba.com;NM=1;PH=DS;RN=13;SR=0;TI=SMTPD_---0UMOzPSM_1611213609;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:abaci-bugfix@linux.alibaba.com
 fp:SMTPD_---0UMOzPSM_1611213609)
          by smtp.aliyun-inc.com(127.0.0.1);
          Thu, 21 Jan 2021 15:20:13 +0800
From: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
Subject: [PATCH] kvm: x86/mmu: Assign boolean values to a bool variable
Date: Thu, 21 Jan 2021 15:20:07 +0800
Message-Id: <1611213607-4062-1-git-send-email-abaci-bugfix@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warnings:

./arch/x86/kvm/mmu/mmu.c:5829:2-9: WARNING: Assignment of 0/1
to bool variable.

./arch/x86/kvm/mmu/mmu.c:2505:1-11: WARNING: Assignment of 0/1
to bool variable.

./arch/x86/kvm/mmu/mmu.c:1814:1-11: WARNING: Assignment of 0/1
to bool variable.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Jiapeng Zhong <abaci-bugfix@linux.alibaba.com>
---
 arch/x86/kvm/mmu/mmu.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/2] s390: uv: Fix sysfs max number of VCPUs reporting
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12036593
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5D49FC433E0
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 15:19:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2231923A04
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 15:19:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732494AbhAUPSr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 10:18:47 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:23724 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732667AbhAUPPr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 10:15:47 -0500
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10LF3Glm103071;
        Thu, 21 Jan 2021 10:15:05 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=c+fsPbzkg+LCngvnZRAef2u+KiCv5D0R9OnF/tRwNg4=;
 b=NKNDEetSB3M4l0AG0jg/Td2jf1iPfl+ZoKiZizdkdeCMUwpsw9rvIM9zjYMZcNblrawf
 JH8W2pzB2uZPqy17BBIoS9gwHUn4VUEwwlSxH2cGzLMG8vE/T4UwuRoc6Sf0wW8OxF5v
 22H6TdI+4t8DIz6qtuDpqtQRcVhR6E5LmtAcpbT7l3sd5XdmUDZn86uB8h9PQ1N6OJYc
 Z5edUhK4uJa82CC2iIpOQ3iV311i0PyaPF1wR3HNo9+GA8rP4HMnSI3dvPQKij6XsK5C
 Q9pcLictoZl2BZcBPUsfQfn9fIDHga0/i8WPM0I+8ZdfWmbxxDbuVrpJ84hK7dmGhY9M RQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367br510ju-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 10:15:05 -0500
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10LF3HlK103102;
        Thu, 21 Jan 2021 10:15:05 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 367br510hp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 10:15:05 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10LFD2dG018595;
        Thu, 21 Jan 2021 15:15:02 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06ams.nl.ibm.com with ESMTP id 3668nwss45-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 15:15:02 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10LFF0bC13893896
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 15:15:00 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E033811C050;
        Thu, 21 Jan 2021 15:14:59 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D02CC11C052;
        Thu, 21 Jan 2021 15:14:58 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 15:14:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, gor@linux.ibm.com, hca@linux.ibm.com,
        mihajlov@linux.ibm.com
Subject: [PATCH v2 1/2] s390: uv: Fix sysfs max number of VCPUs reporting
Date: Thu, 21 Jan 2021 10:14:34 -0500
Message-Id: <20210121151436.417240-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210121151436.417240-1-frankja@linux.ibm.com>
References: <20210121151436.417240-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_08:2021-01-21,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 clxscore=1015
 priorityscore=1501 phishscore=0 adultscore=0 impostorscore=0
 malwarescore=0 lowpriorityscore=0 spamscore=0 mlxlogscore=999 mlxscore=0
 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101210081
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The number reported by the query is N-1 and I think people reading the
sysfs file would expect N instead. For users creating VMs there's no
actual difference because KVM's limit is currently below the UV's
limit.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Fixes: a0f60f8431999 ("s390/protvirt: Add sysfs firmware interface for Ultravisor information")
Cc: stable@vger.kernel.org
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/boot/uv.c        | 2 +-
 arch/s390/include/asm/uv.h | 4 ++--
 arch/s390/kernel/uv.c      | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v4 1/3] s390x: pv: implement routine to share/unshare memory
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12035323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0A4BC433E6
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 09:16:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F6D92395A
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 09:16:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726123AbhAUJPp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 04:15:45 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63084 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728508AbhAUJOP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 04:14:15 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10L92htO156301;
        Thu, 21 Jan 2021 04:13:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=1Jr/kjfOuL08Kj6328CD+2X9hiMaH/zoXULnI9YHL7o=;
 b=kf6gt8jmwa4gDfjJjej09fpqWvXkQA+wPWnv59UJibS9uYKBQGPAR5CVISRSmRza0i3D
 Ien4RgueoJpmz7VpHjWF6t6QO7nnYVSiPjvXs8C/U4UKY9/PnyOmWQSwL0tHugjNQakC
 okD/88FuIhLETUFpYoza1C7hleAWHJTUQgs/kECPm5PjYMt/fUckw3Bk45EVsjZSiw/O
 YKo97mqOwsRV2w6MpWDDwzE1tiWNHSsbS/bn0kucwMo7b/7Ufn5YK5Iei8GZMCtpRmaU
 if2y7lGMgfwQG4ZnTQk3VosmscT2NFxd3jcmAxhYBz0h69FB53+iPNDrQIgzjqo/qwPf 5A==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3674v13yma-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 04:13:20 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10L92p2j156938;
        Thu, 21 Jan 2021 04:13:20 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 3674v13yjj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 04:13:20 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10L96vGf022150;
        Thu, 21 Jan 2021 09:13:18 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 3668p0sfvg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 21 Jan 2021 09:13:18 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10L9DFTn37290432
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 21 Jan 2021 09:13:15 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 36D4E42049;
        Thu, 21 Jan 2021 09:13:15 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B4BA242047;
        Thu, 21 Jan 2021 09:13:14 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.36.14])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 21 Jan 2021 09:13:14 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com, drjones@redhat.com, pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v4 1/3] s390x: pv: implement routine to
 share/unshare memory
Date: Thu, 21 Jan 2021 10:13:10 +0100
Message-Id: <1611220392-22628-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1611220392-22628-1-git-send-email-pmorel@linux.ibm.com>
References: <1611220392-22628-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-21_03:2021-01-20,2021-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 suspectscore=0 phishscore=0 mlxscore=0 priorityscore=1501 impostorscore=0
 bulkscore=0 lowpriorityscore=0 clxscore=1015 malwarescore=0 adultscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101210045
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When communicating with the host we need to share part of
the memory.

Let's implement the ultravisor calls for this.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Suggested-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm/uv.h | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

```
#### [PATCH 1/2] KVM: nSVM: move nested vmrun tracepoint to enter_svm_guest_mode
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12037133
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 702DBC433E6
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D23323A59
	for <kvm@archiver.kernel.org>; Thu, 21 Jan 2021 17:15:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388660AbhAUROt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 21 Jan 2021 12:14:49 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:34242 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388484AbhAURMt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 21 Jan 2021 12:12:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611249060;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=s5rKUNjt01VoES9GlPh1WMo1aTJXvhTfji5QKEBauJY=;
        b=S5oBDeHaI8L36ju8jdgsp8XnidfBgxfe6wzpaWIb3YYs7TeDhvxYE7l+WuDvHb22PHN34Q
        VbdPvA+OJTkHfOau6MsLFZvpTrB9Ct33pEOmH9yKBWHLnXWRW7kCx5fHHgAbFviTB9YuvL
        QKFNfODNFLOWliCu2KHjLjbEaqvXWC4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-400-loOPaVgAOvKY3MyGNfQODg-1; Thu, 21 Jan 2021 12:10:58 -0500
X-MC-Unique: loOPaVgAOvKY3MyGNfQODg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 47C73802B42;
        Thu, 21 Jan 2021 17:10:56 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.32])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C3E2E6E41C;
        Thu, 21 Jan 2021 17:10:52 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>, x86@kernel.org,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/2] KVM: nSVM: move nested vmrun tracepoint to
 enter_svm_guest_mode
Date: Thu, 21 Jan 2021 19:10:42 +0200
Message-Id: <20210121171043.946761-2-mlevitsk@redhat.com>
In-Reply-To: <20210121171043.946761-1-mlevitsk@redhat.com>
References: <20210121171043.946761-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This way trace will capture all the nested mode entries
(including entries after migration, and from smm)

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 26 ++++++++++++++------------
 1 file changed, 14 insertions(+), 12 deletions(-)

```
