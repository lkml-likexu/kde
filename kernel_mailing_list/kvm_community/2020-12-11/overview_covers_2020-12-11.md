

#### [kvm-unit-tests PATCH v3 0/8] s390x: Add SIE library and simple test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Fri Dec 11 10:00:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11967805
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBE78C1B0D8
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 10:03:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92A0223F5B
	for <kvm@archiver.kernel.org>; Fri, 11 Dec 2020 10:03:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405056AbgLKKDM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 11 Dec 2020 05:03:12 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49712 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2394097AbgLKKCV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Dec 2020 05:02:21 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BB9WKAI015205;
        Fri, 11 Dec 2020 05:01:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=jm1Wz+7uCmMFGFuVx03ju+NXEmbbsvR6bqKaAk98stY=;
 b=PEhV1z7AVz6LefFv0uE3JmFN9t0VlgTTQqHwC7MbpnTE6ofbaz3ejnSResb7xOp84PKB
 07NpT0Qs28Rqzd6GazGGMiDcRHqA3Ha7FPJsCVDt80MH7zDLrVGhNNVVGyiV2VBbSG1U
 mQ65HNeCt7xpPuDHLHU7oATUz1jbYe+8cWJEXsDHYAD7fakxt+dqYncw4hPhnc1Ql6lm
 QBDFU0AVlBlrB27VOZrJF/hk9A+jmQvmPpFM2OT9/rQI9C+1TpLYNKYHuyftiYGCcgHP
 InZJljN0qsSc60PIjBQhuB+hU9WlVmioLxMKiyhgR/xdqpV2wc1w1s5oZX2Vzht8fCOv 9w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35c5gf1xra-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 05:01:34 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BB9WUHh015971;
        Fri, 11 Dec 2020 05:01:34 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35c5gf1xqf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 05:01:34 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BB9rS7b005897;
        Fri, 11 Dec 2020 10:01:32 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 3581fhpv6q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 11 Dec 2020 10:01:32 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0BBA1TfO28246304
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 11 Dec 2020 10:01:29 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F10EFA4055;
        Fri, 11 Dec 2020 10:01:28 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3903BA4053;
        Fri, 11 Dec 2020 10:01:28 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 11 Dec 2020 10:01:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH v3 0/8] s390x: Add SIE library and simple test
Date: Fri, 11 Dec 2020 05:00:31 -0500
Message-Id: <20201211100039.63597-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-11_01:2020-12-09,2020-12-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 bulkscore=0
 lowpriorityscore=0 phishscore=0 adultscore=0 priorityscore=1501
 suspectscore=0 impostorscore=0 malwarescore=0 clxscore=1015 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012110057
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

v3:
	* Rebased on re-license patches
	* Split assembly
	* Now using ICPT_* constants
	* Added read_info asserts
	* Fixed missing spin_lock() in smp.c lib
	* Replaced duplicated code in sie test with generic intercept test
	* Replaced uv-guest.x bit testing with test_bit_inv()
	* Some other minor cleanups

Gitlab:
https://gitlab.com/frankja/kvm-unit-tests/-/tree/sie

CI:
https://gitlab.com/frankja/kvm-unit-tests/-/pipelines/228396011

Janosch Frank (8):
  s390x: Add test_bit to library
  s390x: Consolidate sclp read info
  s390x: SCLP feature checking
  s390x: Split assembly and move to s390x/asm/
  s390x: sie: Add SIE to lib
  s390x: sie: Add first SIE test
  s390x: Add diag318 intercept test
  s390x: Fix sclp.h style issues

 lib/s390x/asm-offsets.c    |  13 +++
 lib/s390x/asm/arch_def.h   |   7 ++
 lib/s390x/asm/bitops.h     |  26 +++++
 lib/s390x/asm/facility.h   |   3 +-
 lib/s390x/interrupt.c      |   7 ++
 lib/s390x/io.c             |   2 +
 lib/s390x/sclp.c           |  52 ++++++++--
 lib/s390x/sclp.h           | 178 ++++++++++++++++++---------------
 lib/s390x/sie.h            | 197 +++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.c            |  27 +++--
 s390x/Makefile             |   9 +-
 s390x/{ => asm}/cstart64.S | 119 +---------------------
 s390x/asm/lib.S            | 121 +++++++++++++++++++++++
 s390x/asm/macros.S         |  77 +++++++++++++++
 s390x/intercept.c          |  19 ++++
 s390x/sie.c                | 113 +++++++++++++++++++++
 s390x/unittests.cfg        |   3 +
 s390x/uv-guest.c           |   6 +-
 18 files changed, 754 insertions(+), 225 deletions(-)
 create mode 100644 lib/s390x/sie.h
 rename s390x/{ => asm}/cstart64.S (50%)
 create mode 100644 s390x/asm/lib.S
 create mode 100644 s390x/asm/macros.S
 create mode 100644 s390x/sie.c
```
