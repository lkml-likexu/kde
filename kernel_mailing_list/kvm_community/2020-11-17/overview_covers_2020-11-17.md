

#### [PATCH 0/2] KVM: s390: memcg awareness
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Tue Nov 17 15:10:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11912511
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B75DFC5519F
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:10:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6AA2624654
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:10:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="LgeCnxfb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729555AbgKQPKa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 10:10:30 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:60692 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726883AbgKQPK3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 17 Nov 2020 10:10:29 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHF2uUh167402;
        Tue, 17 Nov 2020 10:10:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=4UVWN0xema4KXC/lfxhqQdaMvSajT9kvkS5R0Z2Brkw=;
 b=LgeCnxfbgci86UPTpmglTlLM8s28ZyqPoKLkZg46E6u7k7xAecOpObrreaxDMIaHaCh+
 hKxkreRO9xtYa/2AG0rBGHhHfLJ76yxKmLoxUUfl4Uapp3gR5pu0gK87XFQnHuuDOddY
 1iFIaYAz+LoCbJtvP8ao4YfjZo7zQNI0SbInuDDM6BMP890BndPyhOe2xfK36U8PjE4i
 1l+CWo5Q3RR2a229k4cBtWsliTTbjvL0LTbn+kiPkL8szRLU89n/OUlHadSup+gkxWUz
 nkX36SASrVnQ/+Aw5uI8rHETDzwuY65yUAW8s8uuLM45HK5AuRvkKinv4wvN22HAke3o lg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34vd4q0a1k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:10:28 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AHF329q167937;
        Tue, 17 Nov 2020 10:10:28 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34vd4q0a0p-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:10:28 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHF8UYb003198;
        Tue, 17 Nov 2020 15:10:26 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma04ams.nl.ibm.com with ESMTP id 34t6v8b1qp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 15:10:26 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AHFAN5w37683494
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Nov 2020 15:10:24 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DBB754C050;
        Tue, 17 Nov 2020 15:10:23 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C83D64C040;
        Tue, 17 Nov 2020 15:10:23 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 17 Nov 2020 15:10:23 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 799F6E23AA; Tue, 17 Nov 2020 16:10:23 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>
Subject: [PATCH 0/2] KVM: s390: memcg awareness
Date: Tue, 17 Nov 2020 16:10:21 +0100
Message-Id: <20201117151023.424575-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-17_04:2020-11-17,2020-11-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 adultscore=0
 clxscore=1015 phishscore=0 mlxlogscore=730 priorityscore=1501 mlxscore=0
 lowpriorityscore=0 malwarescore=0 impostorscore=0 bulkscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011170109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This got somehow lost.  (so this is kind of a v2)
KVM does have memcg awareness. Lets implement this also for s390kvm
and gmap.

Christian Borntraeger (2):
  KVM: s390: Add memcg accounting to KVM allocations
  s390/gmap: make gmap memcg aware

 arch/s390/kvm/guestdbg.c  |  8 ++++----
 arch/s390/kvm/intercept.c |  2 +-
 arch/s390/kvm/interrupt.c | 10 +++++-----
 arch/s390/kvm/kvm-s390.c  | 20 ++++++++++----------
 arch/s390/kvm/priv.c      |  4 ++--
 arch/s390/kvm/pv.c        |  6 +++---
 arch/s390/kvm/vsie.c      |  4 ++--
 arch/s390/mm/gmap.c       | 30 +++++++++++++++---------------
 8 files changed, 42 insertions(+), 42 deletions(-)
```
#### [kvm-unit-tests PATCH 0/5] s390x: Add SIE library and simple test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Nov 17 15:42:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11912545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81E10C5519F
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:43:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CBCC238E6
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 15:43:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="qCQV7Srf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726302AbgKQPnA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 10:43:00 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34256 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725767AbgKQPm7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 17 Nov 2020 10:42:59 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHFWibm070855;
        Tue, 17 Nov 2020 10:42:59 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=ERJWrKqq4ZyO6mTIydb3k4QoL97E2UvynHRBDzBmMgU=;
 b=qCQV7SrfnUP5RsjDzLVD0sf05OAN0rsAvB+3hV93SwhfuPkkaOrHg+0nUiFvNoomFOPg
 NVplLICxvbaEFsDgyBoW+ynhRxeHrb9OmObRQZ7O6DLwgy3dfkxbDsKsSL7+yW9L3ico
 kBpxeTsJrec4nY/YCyZCrkYFuzLlFVZb6mG3/5BEOgzX1jxShAC9hzMKLHyYTlTnq9ne
 vp4sYJwh6oqG6x0dur34tBOyn41hw7M14sYJJcfPN3iecA/3vr5lX4c8/lNW1xGTjpuc
 05v6tQkbRtEvLU9cQ4ExfjKfptp8xsSTzvUWdC73N8pUtCyfa2HUqbYii3UPYi0eS1XM Zg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34vd6hscnf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:42:58 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AHFWu1o072237;
        Tue, 17 Nov 2020 10:42:58 -0500
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34vd6hscm7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 10:42:58 -0500
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AHFgWtv005677;
        Tue, 17 Nov 2020 15:42:55 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04ams.nl.ibm.com with ESMTP id 34t6v8b2h2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 17 Nov 2020 15:42:55 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AHFgqQH51577144
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 17 Nov 2020 15:42:52 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 568B24C044;
        Tue, 17 Nov 2020 15:42:52 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A33E74C040;
        Tue, 17 Nov 2020 15:42:51 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 17 Nov 2020 15:42:51 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 0/5] s390x: Add SIE library and simple test
Date: Tue, 17 Nov 2020 10:42:10 -0500
Message-Id: <20201117154215.45855-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-17_04:2020-11-17,2020-11-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 bulkscore=0
 suspectscore=0 impostorscore=0 adultscore=0 mlxscore=0 lowpriorityscore=0
 priorityscore=1501 malwarescore=0 phishscore=0 mlxlogscore=780
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011170112
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the absolute minimum needed to run VMs inside the KVM Unit
Tests. It's more of a base for other tests that I can't (yet) publish
than an addition of tests that check KVM functionality. However, I
wanted to decrease the number of WIP patches in my private
branch. Once the library is available maybe others will come and
extend the SIE test itself.

Yes, I have added VM management functionality like VM create/destroy,
etc but as it is not needed right now, I'd like to exclude it from
this patch set for now.

Gitlab:
https://gitlab.com/frankja/kvm-unit-tests/-/tree/sie

CI:
https://gitlab.com/frankja/kvm-unit-tests/-/pipelines/217336822

Janosch Frank (5):
  s390x: Add test_bit to library
  s390x: Consolidate sclp read info
  s390x: SCLP feature checking
  s390x: sie: Add SIE to lib
  s390x: sie: Add first SIE test

 lib/s390x/asm-offsets.c  |  13 +++
 lib/s390x/asm/arch_def.h |   7 ++
 lib/s390x/asm/bitops.h   |  16 ++++
 lib/s390x/asm/facility.h |   3 +-
 lib/s390x/interrupt.c    |   7 ++
 lib/s390x/io.c           |   2 +
 lib/s390x/sclp.c         |  48 ++++++++--
 lib/s390x/sclp.h         |  18 ++++
 lib/s390x/sie.h          | 197 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.c          |  23 ++---
 s390x/Makefile           |   1 +
 s390x/cstart64.S         |  56 +++++++++++
 s390x/sie.c              | 125 +++++++++++++++++++++++++
 13 files changed, 495 insertions(+), 21 deletions(-)
 create mode 100644 lib/s390x/sie.h
 create mode 100644 s390x/sie.c
```
#### [PATCH v4 00/34] SEV-ES hypervisor support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Tue Nov 17 17:07:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11912953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E0895C63697
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 17:08:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9699B24654
	for <kvm@archiver.kernel.org>; Tue, 17 Nov 2020 17:08:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="d/kRYDN1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728602AbgKQRH6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 17 Nov 2020 12:07:58 -0500
Received: from mail-dm6nam12on2044.outbound.protection.outlook.com
 ([40.107.243.44]:21025
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726196AbgKQRH6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Nov 2020 12:07:58 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=bnM7c5BwQ9NyzaeBsykKq9JNZb+SZIdNSWO9sLB8P03BAMUvydDBHhDhmKtFEz/sWCAxQqMOrLmptp7znCzuSOorNbpv2mbKNyInpuhFMVwtAe7qmlniscrYMl2yHp99woA3uPiOsIGxgyT+/6zTrb2o6VMnWhOwnzGv0OW+4q3Xj/hZz3ELxcfV0FS7Gd9ewn0Wzl0BvgbKtUdBxJK/779wLM5u2EIzSOIKlSD3rPf1hS4JoWLDqlsgg/mhw3d5Wr+1JzVFpAm+LCHB3KQAul8zNJ3P+HPfO+Qvuz7MazR783h5Ew7u+Z/2Kg0Lv9Gh3/bXMDptJp82ZVsYosPH6A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=QPq4P957Lt2TG0Cu4EqSX37L8K2BvOe+zhhY8IKFdeU=;
 b=ilGCNR615ngynEL/umkLI1XnqC+sr/S8vDOA+DbvLyy+iSrwmnMKg4Z39VWSzoWwhEJGvwBOp0oZilsAPljMDFNMPLul/iFTNJGq5L2RpmnO7PQM1ABNeLlIe6TuDpDq45X7SLoL9tTf4AFAGc2dC0QOajwqSxoi379JAYucMLPEio+n+cHadpVsNDxAdh4SFafadH/NT5kjtXzKGOfFDWhe1yDRHqLf70ZCqM6v5tPeDuXohYakJr9swd06jXqY58FwZv57xCSOl6heHGWq6pItv5Mkn4j94au3Dl7yIzeCP3H4Fypjw12ehM/WQu8sogc4uiUa5/IrILL/6VFGsA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=QPq4P957Lt2TG0Cu4EqSX37L8K2BvOe+zhhY8IKFdeU=;
 b=d/kRYDN1h2/+eVsIRfm0NIoDKLSRtLKt5yfPSeuGdGKei05P4VWbM7Wokl866ALBcaBHZb6vvjygr18t/Z9e/NzQUQ8X0oXl1Y4AIBxWGT7Q2QxKQl3fnrLuNRMWzM246pQN3TFMF/U/vLyXeZx+T9wDUzNAOmYX+sYNCOq6jak=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR12MB1772.namprd12.prod.outlook.com (2603:10b6:3:107::10) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3541.25; Tue, 17 Nov 2020 17:07:51 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::dcda:c3e8:2386:e7fe%12]) with mapi id 15.20.3564.028; Tue, 17 Nov
 2020 17:07:50 +0000
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
Subject: [PATCH v4 00/34] SEV-ES hypervisor support
Date: Tue, 17 Nov 2020 11:07:03 -0600
Message-Id: <cover.1605632857.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR18CA0065.namprd18.prod.outlook.com
 (2603:10b6:3:22::27) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR18CA0065.namprd18.prod.outlook.com (2603:10b6:3:22::27) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3564.28 via Frontend
 Transport; Tue, 17 Nov 2020 17:07:50 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 236cf3bc-f903-411f-59e3-08d88b1b5086
X-MS-TrafficTypeDiagnostic: DM5PR12MB1772:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB17724203438EE1AEBD691846ECE20@DM5PR12MB1772.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1417;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 fa0pgxhaAvG9LX2hMBLy0Wkdo87cVMgYTRsJDbY6+zOkrtv+wDXdlFQh8aw0lKYItbpqfeSytuQPX/8pwQEFMzqtQDKlRoT5UVAqDPKy6o0LwExw7IkY/dZrGOKPT+GT2w45ohKbT8dyySw/M9WocLTqShtSD6Uz5G2nyx7GPvH65GqWd6f99Q0WiBbHrwgAa0kjvpdsCE8HYZ+r+61u7dK2f8p53G4oXBYBNWuQSw/Mc5pHBBsc2hDLVAJ3AXf3uSvPKQRzWvwuPabUuluEuNPFLYYPJ6TGVtu272Hwi82MbXdQbwh1TYTMQdbtvtmBte0AY/pFUbQmbvzD7rndFdsJSFHpNsoW0/3eIkn3OssL5agm3RoIfFlnWLToQub3xPdmks5CDMlI+6g0KvVZ+A==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(346002)(376002)(39860400002)(136003)(6486002)(66476007)(66946007)(8936002)(83380400001)(5660300002)(26005)(478600001)(66556008)(16526019)(6666004)(186003)(36756003)(86362001)(8676002)(316002)(956004)(52116002)(4326008)(54906003)(7696005)(7416002)(2616005)(966005)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 v1cQ7quFotwsn0pv+paAmyizKouqKld1XzfeQOQhMXYtoZpiF6Blz3GQOo6GU4ZoJez7Lku8UFJVkU+GciZVi7p40/a8cA8YhzMuzpsh/xJyKjTa4O0y6h1Qvn1IvyzXcqHrZLS0AxQvJsjL1Itrnp+JGEg0wBdSwFmMpOJ2GDN6mFmEqmd3X5aQiepRxbk0EWZuv2tYMKw4dGkm+gMlQ3esitaEkbI97yZNjJdry3H+FvG7/M7/C2DcC5lA3Jt4SI3IAmqVWGKX/+RGGkEb8bg9appj7D4ER5LQmPjsckZWDfXSQlT263pNam1eobSKD1JCdH6/h23cVKGDxKTT4gwpPNv4mswCqTGIHClfgPJCCcAjkNgrUM3oBezo8uAMCnyRcWQVheQbWhebEA2L/SZUxBpGorDG7B8+o9+RdDQyzdL8Bn6UpMnuJO21AEadbkCZpX/SFjbyjxNU5Kd8wD1Z2tzFzUBNYJC0oJ4AAQpq7AZVG+3qzwh2WrsMzkVJ6wA5DCiuSbL7hgeLg+bg9j1A2t9Y1j6W5EIGD/qh9Dw8QE60xgC5P5YMlyOLKiwhBTQbkYQgzyi8QXu4HSXHZs9FC/ypszoWILI9akkO/sO+9FR6pQ0bHDzvk2pIPkFM1QVfCQCzVGufmcWgVkUR5w==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 236cf3bc-f903-411f-59e3-08d88b1b5086
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 17 Nov 2020 17:07:50.6384
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 0/lyJr/JBplWFuAFrlTB4IZfePofFylUeE8WiJXPpA7HrJDpzTPeuvv+PyqnXJHxfbpiQC5H52rdWHk61RTEmw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1772
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for running SEV-ES guests under KVM.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

Under SEV-ES, a vCPU save area (VMSA) must be encrypted. SVM is updated to
build the initial VMSA and then encrypt it before running the guest. Once
encrypted, it must not be modified by the hypervisor. Modification of the
VMSA will result in the VMRUN instruction failing with a SHUTDOWN exit
code. KVM must support the VMGEXIT exit code in order to perform the
necessary functions required of the guest. The GHCB is used to exchange
the information needed by both the hypervisor and the guest.

Register data from the GHCB is copied into the KVM register variables and
accessed as usual during handling of the exit. Upon return to the guest,
updated registers are copied back to the GHCB for the guest to act upon.

There are changes to some of the intercepts that are needed under SEV-ES.
For example, CR0 writes cannot be intercepted, so the code needs to ensure
that the intercept is not enabled during execution or that the hypervisor
does not try to read the register as part of exit processing. Another
example is shutdown processing, where the vCPU cannot be directly reset.

Support is added to handle VMGEXIT events and implement the GHCB protocol.
This includes supporting standard exit events, like a CPUID instruction
intercept, to new support, for things like AP processor booting. Much of
the existing SVM intercept support can be re-used by setting the exit
code information from the VMGEXIT and calling the appropriate intercept
handlers.

Finally, to launch and run an SEV-ES guest requires changes to the vCPU
initialization, loading and execution.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
---

These patches are based on the KVM next branch:
https://git.kernel.org/pub/scm/virt/kvm/kvm.git next

6d6a18fdde8b ("KVM: selftests: allow two iterations of dirty_log_perf_test")

A version of the tree can also be found at:
https://github.com/AMDESE/linux/tree/sev-es-v4

Changes from v3:
- Some krobot fixes.
- Some checkpatch cleanups.

Changes from v2:
- Update the freeing of the VMSA page to account for the encrypted memory
  cache coherency feature as well as the VM page flush feature.
- Update the GHCB dump function with a bit more detail.
- Don't check for RAX being present as part of a string IO operation.
- Include RSI when syncing from GHCB to support KVM hypercall arguments.
- Add GHCB usage field validation check.

Changes from v1:
- Removed the VMSA indirection support:
  - On LAUNCH_UPDATE_VMSA, sync traditional VMSA over to the new SEV-ES
    VMSA area to be encrypted.
  - On VMGEXIT VMEXIT, directly copy valid registers into vCPU arch
    register array from GHCB. On VMRUN (following a VMGEXIT), directly
    copy dirty vCPU arch registers to GHCB.
  - Removed reg_read_override()/reg_write_override() KVM ops.
- Added VMGEXIT exit-reason validation.
- Changed kvm_vcpu_arch variable vmsa_encrypted to guest_state_protected
- Updated the tracking support for EFER/CR0/CR4/CR8 to minimize changes
  to the x86.c code
- Updated __set_sregs to not set any register values (previously supported
  setting the tracked values of EFER/CR0/CR4/CR8)
- Added support for reporting SMM capability at the VM-level. This allows
  an SEV-ES guest to indicate SMM is not supported
- Updated FPU support to check for a guest FPU save area before using it.
  Updated SVM to free guest FPU for an SEV-ES guest during KVM create_vcpu
  op.
- Removed changes to the kvm_skip_emulated_instruction()
- Added VMSA validity checks before invoking LAUNCH_UPDATE_VMSA
- Minor code restructuring in areas for better readability

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>

Tom Lendacky (34):
  x86/cpu: Add VM page flush MSR availablility as a CPUID feature
  KVM: SVM: Remove the call to sev_platform_status() during setup
  KVM: SVM: Add support for SEV-ES capability in KVM
  KVM: SVM: Add GHCB accessor functions for retrieving fields
  KVM: SVM: Add support for the SEV-ES VMSA
  KVM: x86: Mark GPRs dirty when written
  KVM: SVM: Add required changes to support intercepts under SEV-ES
  KVM: SVM: Prevent debugging under SEV-ES
  KVM: SVM: Do not allow instruction emulation under SEV-ES
  KVM: SVM: Cannot re-initialize the VMCB after shutdown with SEV-ES
  KVM: SVM: Prepare for SEV-ES exit handling in the sev.c file
  KVM: SVM: Add initial support for a VMGEXIT VMEXIT
  KVM: SVM: Create trace events for VMGEXIT processing
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
  KVM: SVM: Create trace events for VMGEXIT MSR protocol processing
  KVM: SVM: Support MMIO for an SEV-ES guest
  KVM: SVM: Support string IO operations for an SEV-ES guest
  KVM: SVM: Add support for EFER write traps for an SEV-ES guest
  KVM: SVM: Add support for CR0 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR4 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR8 write traps for an SEV-ES guest
  KVM: x86: Update __get_sregs() / __set_sregs() to support SEV-ES
  KVM: SVM: Do not report support for SMM for an SEV-ES guest
  KVM: SVM: Guest FPU state save/restore not needed for SEV-ES guest
  KVM: SVM: Add support for booting APs for an SEV-ES guest
  KVM: SVM: Add NMI support for an SEV-ES guest
  KVM: SVM: Set the encryption mask for the SVM host save area
  KVM: SVM: Update ASID allocation to support SEV-ES guests
  KVM: SVM: Provide support for SEV-ES vCPU creation/loading
  KVM: SVM: Provide support for SEV-ES vCPU loading
  KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
  KVM: SVM: Provide support to launch and run an SEV-ES guest

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/include/asm/kvm_host.h    |  12 +-
 arch/x86/include/asm/msr-index.h   |   1 +
 arch/x86/include/asm/svm.h         |  40 +-
 arch/x86/include/uapi/asm/svm.h    |  28 +
 arch/x86/kernel/cpu/scattered.c    |   1 +
 arch/x86/kernel/cpu/vmware.c       |  12 +-
 arch/x86/kvm/Kconfig               |   3 +-
 arch/x86/kvm/cpuid.c               |   1 +
 arch/x86/kvm/kvm_cache_regs.h      |  51 +-
 arch/x86/kvm/svm/sev.c             | 933 +++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c             | 442 +++++++++++---
 arch/x86/kvm/svm/svm.h             | 166 ++++-
 arch/x86/kvm/svm/vmenter.S         |  50 ++
 arch/x86/kvm/trace.h               |  97 +++
 arch/x86/kvm/vmx/vmx.c             |   6 +-
 arch/x86/kvm/x86.c                 | 368 ++++++++++--
 arch/x86/kvm/x86.h                 |   9 +
 18 files changed, 1971 insertions(+), 250 deletions(-)


base-commit: 6d6a18fdde8b86b919b740ad629153de432d12a8
```
