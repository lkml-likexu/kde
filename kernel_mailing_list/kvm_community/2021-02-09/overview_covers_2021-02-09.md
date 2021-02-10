

#### [kvm-unit-tests PATCH 0/8] s390x: Cleanup exception register
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Feb  9 13:49:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12078267
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3B1B3C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:53:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02E3664EE6
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 13:53:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231997AbhBINw7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 08:52:59 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:58560 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231751AbhBINvb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 08:51:31 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119DbjF8080507;
        Tue, 9 Feb 2021 08:50:46 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=fWNH3/wURg9cls1XBO4/gYwHrbONTIGKlow+igCCR38=;
 b=tPu9uaCs7iGCATiqQjqISv8XoeQxKW2PZwKAmv5cEwWhREv1dzjGNP82zbp0rZG4/W6R
 7fY6T281OubFh005715MttwJXercTZYCi2ywQbHGHfvnDBWs/byeiuQ597Qgy/n8DRYQ
 4Y4jdMdf040fKR0fD6fd6HNq4d/uCeBmBQlV2dNOHiFpcvud5L/avOLQ3O7vLBdIVWR3
 DNTIWWGZE2Vw+R4zggw32vXEvZwIMCc4DhTP8lTi5Z7bJ46dhCUz+Lvy4KykBBm7fW3T
 6o8FaWNWX9I6TFud3D6MaTChysQ0qIpxgUr7IVkzW6iX05HGZnlUp8MLJu182S6KctW7 KA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36ku3211bh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 08:50:46 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119DaQOj075620;
        Tue, 9 Feb 2021 08:50:46 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36ku3211ap-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 08:50:46 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 1198Mn30025775;
        Tue, 9 Feb 2021 13:50:44 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06fra.de.ibm.com with ESMTP id 36hjch1r7u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 13:50:44 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119Dofec14483748
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 13:50:41 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2DF7DA4040;
        Tue,  9 Feb 2021 13:50:41 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7936DA4051;
        Tue,  9 Feb 2021 13:50:40 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 13:50:40 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        pmorel@linux.ibm.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 0/8] s390x: Cleanup exception register
 save/restore and implement backtrace
Date: Tue,  9 Feb 2021 08:49:17 -0500
Message-Id: <20210209134925.22248-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 phishscore=0 suspectscore=0 spamscore=0 priorityscore=1501 mlxscore=0
 mlxlogscore=999 malwarescore=0 bulkscore=0 adultscore=0 clxscore=1015
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090067
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Having two sets of macros for saving and restoring registers on
exceptions doesn't seem optimal to me. Therefore this patch set
removes the old macros that use the lowcore as storage in favor of the
stack using ones. At the same time we move over to generated offsets
instead of subtracting from the stack piece by piece. Changes to the
stack struct are easier that way.

Additionally let's add backtrace support and print the GRs on
exception so we get a bit more information when something goes wrong.

Janosch Frank (8):
  s390x: Fix fpc store address in RESTORE_REGS_STACK
  s390x: Fully commit to stack save area for exceptions
  RFC: s390x: Define STACK_FRAME_INT_SIZE macro
  s390x: Introduce and use CALL_INT_HANDLER macro
  s390x: Provide preliminary backtrace support
  s390x: Print more information on program exceptions
  s390x: Move diag308_load_reset to stack saving
  s390x: Remove SAVE/RESTORE_stack

 lib/s390x/asm-offsets.c   | 15 +++++--
 lib/s390x/asm/arch_def.h  | 29 ++++++++++---
 lib/s390x/asm/interrupt.h |  4 +-
 lib/s390x/interrupt.c     | 43 +++++++++++++++---
 lib/s390x/stack.c         | 20 ++++++---
 s390x/Makefile            |  1 +
 s390x/cpu.S               |  6 ++-
 s390x/cstart64.S          | 25 +++--------
 s390x/macros.S            | 91 +++++++++++++++++++--------------------
 9 files changed, 140 insertions(+), 94 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/4] s390: Add support for large pages
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb  9 14:38:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12078343
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 94AEAC433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:39:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4041E64E4F
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 14:39:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232187AbhBIOjd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 09:39:33 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:30438 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232073AbhBIOjX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 09:39:23 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119EZGEn052897;
        Tue, 9 Feb 2021 09:38:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=hXJYyxHSrJuhh5RhfOYW5auI8Vi9JDwjlDkvwP7NI6M=;
 b=cin/PQa7bAB4DRqcOrLHgwWGtI67ohzsBkten5f+2HbSto4DruMut9lfLaydQ3EBuk7E
 KFA/jnp2tSfW1pi1SPzKzn408NV0r1piMeOySaEYLq19Nr2YdmrLPFtmb8Z1GmZxuNOK
 yn0urNeq59PmB7siWjpHDHPteUYi4DwUjDzJj1hzSNTM73mrJuwlJcn3cn7+70WWpJIz
 ThoEevcvpniiQm+OegSG6uRJmlgVEr+o7SvWxJ+wWHquGkD0WMvCFxLSjD5Ut8wdpIZe
 licFIGmWrlzqDwPL8LTS04D+n2QhAecvH9qFB6iP5swPkardjkVrGMIWNNryexT5ci5w wQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kv9r8517-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:38:41 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119EZKEf053275;
        Tue, 9 Feb 2021 09:38:41 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36kv9r850a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 09:38:41 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119EXCw7002862;
        Tue, 9 Feb 2021 14:38:39 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma03ams.nl.ibm.com with ESMTP id 36hqda38q3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:38:38 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119Ecap137355974
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 14:38:36 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2F36611C052;
        Tue,  9 Feb 2021 14:38:36 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C2F4011C04A;
        Tue,  9 Feb 2021 14:38:35 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 14:38:35 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com,
        frankja@linux.ibm.com, cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 0/4] s390: Add support for large pages
Date: Tue,  9 Feb 2021 15:38:31 +0100
Message-Id: <20210209143835.1031617-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxlogscore=999
 mlxscore=0 impostorscore=0 bulkscore=0 lowpriorityscore=0
 priorityscore=1501 spamscore=0 clxscore=1015 malwarescore=0 suspectscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090072
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce support for large (1M) and huge (2G) pages.

Add a simple testcase for EDAT1 and EDAT2.

Claudio Imbrenda (4):
  libcflat: add SZ_1M and SZ_2G
  s390x: lib: fix and improve pgtable.h
  s390x: mmu: add support for large pages
  s390x: edat test

 s390x/Makefile          |   1 +
 lib/s390x/asm/pgtable.h |  38 ++++++-
 lib/libcflat.h          |   2 +
 lib/s390x/mmu.h         |  73 +++++++++++-
 lib/s390x/mmu.c         | 246 ++++++++++++++++++++++++++++++++++++----
 s390x/edat.c            | 238 ++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg     |   3 +
 7 files changed, 572 insertions(+), 29 deletions(-)
 create mode 100644 s390x/edat.c
```
#### [PATCH v3 0/2] s390/kvm: fix MVPG when in VSIE
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb  9 15:43:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12078483
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A16D5C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:43:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6ECA464E27
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 15:43:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232452AbhBIPnw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 10:43:52 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:36868 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S232048AbhBIPnu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 10:43:50 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119FWtSx137822;
        Tue, 9 Feb 2021 10:43:08 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=pFWhtR68s1PAGHruUgjhtP/yzN5SoaUai8t9k3e9yzk=;
 b=egIQrED65GAaqCXi2jSxZIoBsvand6HaOUGGPJZYYH1TOIBvF94fitPuK131OeE0geZV
 SnVeMyC2LghMOJacQGpS7sz0Qglxuv5/IgT/qzWkogAkAPtkbHeCklKB2A4ag7592seN
 19zAcJHASS3/ChJ2TfIMMZDyoHHBI4VIF7XpOtcAFoeN7eWym5FitRnj4lRu7Xbc5EcM
 IqXdoFK59DH8hSQLFlkw7NjW0VEInRiNHzUIgKy5STVOhkjYx/fSJEDNGptCqZE6WZgK
 6ZgFkF6doOeeosCvY8yM8GE5tLqZ535qN8xC2Sei15czTGbsxFIYrFILFLt4Nj4xfg+E Gw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kw0eh0r3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 10:43:08 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119FX8gE139388;
        Tue, 9 Feb 2021 10:43:08 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kw0eh0qc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 10:43:08 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119Femv3029748;
        Tue, 9 Feb 2021 15:43:06 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06fra.de.ibm.com with ESMTP id 36hjch1thw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 15:43:05 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119Fh3Nm40108316
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 15:43:03 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 25BA2AE056;
        Tue,  9 Feb 2021 15:43:03 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B5922AE045;
        Tue,  9 Feb 2021 15:43:02 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 15:43:02 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v3 0/2] s390/kvm: fix MVPG when in VSIE
Date: Tue,  9 Feb 2021 16:43:00 +0100
Message-Id: <20210209154302.1033165-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_03:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=750
 priorityscore=1501 lowpriorityscore=0 suspectscore=0 phishscore=0
 adultscore=0 impostorscore=0 clxscore=1015 malwarescore=0 spamscore=0
 mlxscore=0 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090079
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current handling of the MVPG instruction when executed in a nested
guest is wrong, and can lead to the nested guest hanging.

This patchset fixes the behaviour to be more architecturally correct,
and fixes the hangs observed.

v2->v3
* improved some comments
* improved some variable and parameter names for increased readability
* fixed missing handling of page faults in the MVPG handler
* small readability improvements

v1->v2
* complete rewrite

Claudio Imbrenda (2):
  s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
  s390/kvm: VSIE: correctly handle MVPG when in VSIE

 arch/s390/kvm/gaccess.c |  30 ++++++++++--
 arch/s390/kvm/gaccess.h |   5 +-
 arch/s390/kvm/vsie.c    | 101 ++++++++++++++++++++++++++++++++++++----
 3 files changed, 121 insertions(+), 15 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/3] s390x: mvpg test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb  9 18:51:51 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12078891
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B30A6C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 19:11:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B8FC64EB1
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 19:11:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233583AbhBITKV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 14:10:21 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:60776 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S233214AbhBIS73 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 13:59:29 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119IpMke018981
        for <kvm@vger.kernel.org>; Tue, 9 Feb 2021 13:52:00 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=2UiLDqbQnsfFi1gvlqx443uD2xxSL5E8UhLTwo3pHO8=;
 b=CSWHSiaBoc07TKVD6x9LyfIBcK1rn+yv7vPSRILaZHIH1XScZAnswvCDiFG0x4AClHQG
 5CQPy3QgJTAHMvq6nJrJcj7M66mJBH84NtwL9aaOqkoUy4iyRWswUvQr9ENgp+vrn6Ip
 XTehzBDevLE2oEtgt5cf7gASe9iniQkYQvDFPRZdAHzP+myKucM53bEhPLuOOfU9zBhB
 51VYKcPAa+hm3yAjjuzu87MDncklB4zXNiDHJGj0FgD+/iA4RROc3NKbDxldpWT4Ogc2
 /ckmKcHeAb8DfWLV6p2cl/HmC2Pjfz6dlFL0tBKHwNppUq7CTnqOLELY69qk/UFpWDLQ eA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kyhxgwnp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 09 Feb 2021 13:52:00 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119Ipx96025678
        for <kvm@vger.kernel.org>; Tue, 9 Feb 2021 13:51:59 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kyhxgwn6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 13:51:59 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119IknXL004313;
        Tue, 9 Feb 2021 18:51:58 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06ams.nl.ibm.com with ESMTP id 36j94wjy9k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 18:51:57 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 119IpjW925755974
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 18:51:45 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 188DFA4062;
        Tue,  9 Feb 2021 18:51:55 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A425EA405C;
        Tue,  9 Feb 2021 18:51:54 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.1.216])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 18:51:54 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v1 0/3] s390x: mvpg test
Date: Tue,  9 Feb 2021 19:51:51 +0100
Message-Id: <20210209185154.1037852-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_05:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 priorityscore=1501 clxscore=1015 malwarescore=0 adultscore=0
 lowpriorityscore=0 phishscore=0 bulkscore=0 mlxscore=0 spamscore=0
 impostorscore=0 mlxlogscore=708 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2102090086
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A simple unit test for the MVPG instruction.

The timeout is set to 10 seconds because the test should complete in a
fraction of a second even on busy machines. If the test is run in VSIE
and the host of the host is not handling MVPG properly, the test will
probably hang.

Testing MVPG behaviour in VSIE is the main motivation for this test.

Anything related to storage keys is not tested.

Claudio Imbrenda (3):
  s390x: introduce leave_pstate to leave userspace
  s390x: check for specific program interrupt
  s390x: mvpg: simple test

 s390x/Makefile            |   1 +
 lib/s390x/asm/arch_def.h  |   5 +
 lib/s390x/asm/interrupt.h |   1 +
 lib/s390x/interrupt.c     |  18 ++-
 s390x/mvpg.c              | 266 ++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg       |   4 +
 6 files changed, 293 insertions(+), 2 deletions(-)
 create mode 100644 s390x/mvpg.c
```
#### [PATCH 0/1] fix circular lockdep when staring SE guest
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Tue Feb  9 19:48:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12079271
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1D4E6C433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 21:46:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D0F7164EE0
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 21:46:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233567AbhBIVov (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 16:44:51 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:54794 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S234248AbhBIU6q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Feb 2021 15:58:46 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 119JXGqO091331;
        Tue, 9 Feb 2021 14:49:01 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=1gsPEt1/kDSSNflaImtKJVxcfOurcbBEdIG2t/N6F+8=;
 b=mo+TQXicVlL/ceoR6QmzmGuRiUkrHwCF1KsxgqYAJQWrKD+UkaBvCChXGlipYOdUFzAh
 8qkjbA2CftXI3LIIEvrwHmnLOrvMqWq+YarhtAiOYg0KccnnQFp7YRUB+UPJF7f57qlP
 EkNi+zmDwkCJs6eeSxf3QxcFGu37CAwHs+lVfCAzUy75jzczXTJNTd7tx5TDKqNlj7q9
 QXqUMcfnDb3LjFcvRu/3v6qJenNgZNWTkVyja1ed9raALR4QHow8UeQVBo9DoEvzpfaz
 cHhqRBhSBz9PNqbjgCRNdy9U/bUr9F8A4bpohK1sjXG6++3PxRNVVuea0C3zKMWCuNlj sA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kyx7t8na-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:49:01 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 119JXKuf091898;
        Tue, 9 Feb 2021 14:49:00 -0500
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36kyx7t8n6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 14:49:00 -0500
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 119Jgdpc003984;
        Tue, 9 Feb 2021 19:49:00 GMT
Received: from b01cxnp23034.gho.pok.ibm.com (b01cxnp23034.gho.pok.ibm.com
 [9.57.198.29])
        by ppma01dal.us.ibm.com with ESMTP id 36hjr9f50u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Feb 2021 19:49:00 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp23034.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 119JmxOf42729850
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Feb 2021 19:48:59 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2E4C6B2065;
        Tue,  9 Feb 2021 19:48:59 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8E612B205F;
        Tue,  9 Feb 2021 19:48:58 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.203.235])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue,  9 Feb 2021 19:48:58 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH 0/1] fix circular lockdep when staring SE guest
Date: Tue,  9 Feb 2021 14:48:29 -0500
Message-Id: <20210209194830.20271-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-09_06:2021-02-09,2021-02-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 impostorscore=0 malwarescore=0 suspectscore=0 spamscore=0 clxscore=1011
 bulkscore=0 mlxlogscore=999 lowpriorityscore=0 adultscore=0 mlxscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102090094
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated") introduced a change that results in a circular
locking dependency when a Secure Execution guest that is configured with
crypto devices is started. The problem resulted due to the fact that the
patch moved the setting of the guest's AP masks within the protection of
the matrix_dev->lock when the vfio_ap driver is notified that the KVM 
pointer has been set. Since it is not critical that setting/clearing of
the guest's AP masks when the driver is notified, the masks will not be
updated under the matrix_dev->lock. The lock is necessary for the
setting/unsetting of the KVM pointer, however, so that will remain in
place. 

The dependency chain for the circular lockdep resolved by this patch 
is:

#2	vfio_ap_mdev_group_notifier:	kvm->lock
					matrix_dev->lock

#1:	handle_pqap:			matrix_dev->lock
	kvm_vcpu_ioctl:			vcpu->mutex

#0:	kvm_s390_cpus_to_pv:		vcpu->mutex
	kvm_vm_ioctl:  			kvm->lock   

Tony Krowiak (1):
  s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks

 drivers/s390/crypto/vfio_ap_ops.c | 75 ++++++++++++++++++-------------
 1 file changed, 45 insertions(+), 30 deletions(-)
```
#### [PATCH v5 0/8] x86/tlb: Concurrent TLB flushes
##### From: Nadav Amit <nadav.amit@gmail.com>
X-Google-Original-From: Nadav Amit
From: Nadav Amit <namit@vmware.com>

```c
From patchwork Tue Feb  9 22:16:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nadav Amit <nadav.amit@gmail.com>
X-Patchwork-Id: 12079357
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EFC92C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 22:28:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BC18364DD5
	for <kvm@archiver.kernel.org>; Tue,  9 Feb 2021 22:28:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234468AbhBIW1c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 17:27:32 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58830 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234295AbhBIWVk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Feb 2021 17:21:40 -0500
Received: from mail-pf1-x429.google.com (mail-pf1-x429.google.com
 [IPv6:2607:f8b0:4864:20::429])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 896FFC0613D6;
        Tue,  9 Feb 2021 14:21:15 -0800 (PST)
Received: by mail-pf1-x429.google.com with SMTP id j12so12784197pfj.12;
        Tue, 09 Feb 2021 14:21:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=HjSiRe9FHCVaGCF52pKJiLElvBu049No/wtLMDAICXE=;
        b=ZPccq1cXTR6T3lt5wME8WuvLAa5mZge5Mw8wXRyQz0ElTK2dM1mAnAYXOysMgOvFTF
         M1Xw0/LEh9dW5Qkrenqg0x0Lv+vYZsYEyKugTwXm+DqKUU9BR7UzcXPZmO9XadLkecQv
         ApW9qLmbiPGG6qIUhUfOsDjkvmBBT3d1bIuWRorvesu1dHc8b0GYSrflEf1HFbYKj3Ps
         33QK4jBS3ZO5kHS9hN+Jy1KJAsWXHDkIkgvZxzA1ZM4RRCcfTprdS7m3wectpcSsxT5g
         gsp5xUecBmhB2lJcNcmkxhi49e7wSClMUrfkE5Gmy18NkLMWcoXbkUDEDX4QE6sQ9x5B
         IO6g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=HjSiRe9FHCVaGCF52pKJiLElvBu049No/wtLMDAICXE=;
        b=FV6cXMBHGwiiquu/OnSzfUlvoMdbODJFRlp4vGnOddJj+blyfhgzxPkOkwy3/N9oT1
         ALjS78fgEuKZ2gBsaxorqTOs9vJ/4bEBNzadZE5BfwwRSN/NM8xDAWFo72w9kWLmGjhF
         q/t1xNZEMO2UuQ3dGmm6T0GkyxdYHGOyqkQYox2Oqv7tj7FAFjJZ6BkmRTFIghWdJ3RU
         e4H/mQkKIutQzS1u9CBPDbDDX7cl4zhRjvLBHTuIZJwBNR/8ANv9TRHA7+LccStToeZE
         +vtQTpeQH/P1jQwcaXXW7kycQXs1f+L7MUGExknyopbNVorPFf0gvYXoh/IUeOtCare8
         UVPw==
X-Gm-Message-State: AOAM530uzLF8x8Gqefd9zhw+gTS1Q5o8M9rIMpV1RPHOa2+hGh6I4kCM
        BMGLTkMWGwIZZSC+iZdS5FapeKSJ4rybzg==
X-Google-Smtp-Source: 
 ABdhPJz3LfnWDYq7JINpREZUWfE+W5NwAF3qi+h7lRxojWAtxXFLj2+kpLvcsoQwwfGFKhWJBLAhPg==
X-Received: by 2002:a63:545f:: with SMTP id e31mr136017pgm.212.1612909274776;
        Tue, 09 Feb 2021 14:21:14 -0800 (PST)
Received: from sc2-haas01-esx0118.eng.vmware.com ([66.170.99.1])
        by smtp.gmail.com with ESMTPSA id v9sm58601pju.33.2021.02.09.14.21.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 09 Feb 2021 14:21:13 -0800 (PST)
From: Nadav Amit <nadav.amit@gmail.com>
X-Google-Original-From: Nadav Amit
To: Thomas Gleixner <tglx@linutronix.de>
Cc: linux-kernel@vger.kernel.org, Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Nadav Amit <namit@vmware.com>, Borislav Petkov <bp@alien8.de>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Ingo Molnar <mingo@redhat.com>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Juergen Gross <jgross@suse.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Rik van Riel <riel@surriel.com>,
        Sasha Levin <sashal@kernel.org>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        kvm@vger.kernel.org, linux-hyperv@vger.kernel.org,
        virtualization@lists.linux-foundation.org, x86@kernel.org,
        xen-devel@lists.xenproject.org
Subject: [PATCH v5 0/8] x86/tlb: Concurrent TLB flushes
Date: Tue,  9 Feb 2021 14:16:45 -0800
Message-Id: <20210209221653.614098-1-namit@vmware.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Nadav Amit <namit@vmware.com>

This is a respin of a rebased version of an old series, which I did not
follow, as I was preoccupied with personal issues (sorry).

The series improve TLB shootdown by flushing the local TLB concurrently
with remote TLBs, overlapping the IPI delivery time with the local
flush. Performance numbers can be found in the previous version [1].

The patches are essentially the same, but rebasing on the last version
required some changes. I left the reviewed-by tags - if anyone considers
it inappropriate, please let me know (and you have my apology).

[1] https://lore.kernel.org/lkml/20190823224153.15223-1-namit@vmware.com/

v4 -> v5:
* Rebase on 5.11
* Move concurrent smp logic to smp_call_function_many_cond() 
* Remove SGI-UV patch which is not needed anymore

v3 -> v4:
* Merge flush_tlb_func_local and flush_tlb_func_remote() [Peter]
* Prevent preemption on_each_cpu(). It is not needed, but it prevents
  concerns. [Peter/tglx]
* Adding acked-, review-by tags

v2 -> v3:
* Open-code the remote/local-flush decision code [Andy]
* Fix hyper-v, Xen implementations [Andrew]
* Fix redundant TLB flushes.

v1 -> v2:
* Removing the patches that Thomas took [tglx]
* Adding hyper-v, Xen compile-tested implementations [Dave]
* Removing UV [Andy]
* Adding lazy optimization, removing inline keyword [Dave]
* Restructuring patch-set

RFCv2 -> v1:
* Fix comment on flush_tlb_multi [Juergen]
* Removing async invalidation optimizations [Andy]
* Adding KVM support [Paolo]

Cc: Andy Lutomirski <luto@kernel.org>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Josh Poimboeuf <jpoimboe@redhat.com>
Cc: Juergen Gross <jgross@suse.com>
Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Rik van Riel <riel@surriel.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: x86@kernel.org
Cc: xen-devel@lists.xenproject.org

Nadav Amit (8):
  smp: Run functions concurrently in smp_call_function_many_cond()
  x86/mm/tlb: Unify flush_tlb_func_local() and flush_tlb_func_remote()
  x86/mm/tlb: Open-code on_each_cpu_cond_mask() for tlb_is_not_lazy()
  x86/mm/tlb: Flush remote and local TLBs concurrently
  x86/mm/tlb: Privatize cpu_tlbstate
  x86/mm/tlb: Do not make is_lazy dirty for no reason
  cpumask: Mark functions as pure
  x86/mm/tlb: Remove unnecessary uses of the inline keyword

 arch/x86/hyperv/mmu.c                 |  10 +-
 arch/x86/include/asm/paravirt.h       |   6 +-
 arch/x86/include/asm/paravirt_types.h |   4 +-
 arch/x86/include/asm/tlbflush.h       |  48 +++----
 arch/x86/include/asm/trace/hyperv.h   |   2 +-
 arch/x86/kernel/alternative.c         |   2 +-
 arch/x86/kernel/kvm.c                 |  11 +-
 arch/x86/mm/init.c                    |   2 +-
 arch/x86/mm/tlb.c                     | 177 +++++++++++++++-----------
 arch/x86/xen/mmu_pv.c                 |  11 +-
 include/linux/cpumask.h               |   6 +-
 include/trace/events/xen.h            |   2 +-
 kernel/smp.c                          | 148 +++++++++++----------
 13 files changed, 242 insertions(+), 187 deletions(-)
```
