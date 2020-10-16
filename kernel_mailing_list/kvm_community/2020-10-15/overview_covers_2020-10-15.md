

#### [PATCH v2 0/2] DIAG 318 tests and fix
##### From: Collin Walling <walling@linux.ibm.com>

```c
From patchwork Thu Oct 15 19:59:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11840127
Return-Path: <SRS0=SCDt=DW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7066F14B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 19:59:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 215282072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 15 Oct 2020 19:59:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="alW8IqsS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392044AbgJOT7a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 15 Oct 2020 15:59:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28354 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2392040AbgJOT7a (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 15 Oct 2020 15:59:30 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09FJhNHR108651
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=4rNH/kSXbugYyucooL+bhUSNEEJOnfiXYfy0CKFG/8A=;
 b=alW8IqsSyQk8ug8lpBexH/OYCJ7ASr+/9f5LZ6rXtR9g1GuGE8Am9uqThwU33wu1M+RT
 2JgeUJ1wGkfPLYymXJakpivIpgWKaCbhhb0rCQcAyAyPviRVQLW8N/K1B5z4Vru4IN6t
 93bqr6r+4wlMiMAQXTWeLsROQi1O1wtSNjD1kG5A+qxJvM/PUlwHr0JkpKvnsYpI680B
 U/YJzpUexuLaQHxO+pb9v+skHWXbMyXBzZGIRuaOTg5fdz10pALp0nbDB/Y5DMTmpikW
 Vg6PzjKD9ILY7fYLJg+FHysCKDxvayp3P8nqdn0MPvyk8XzCfQ3x4nZhU+/lkAU7Gr7N Kw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 346vu38e7m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:29 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09FJjvx0117967
        for <kvm@vger.kernel.org>; Thu, 15 Oct 2020 15:59:28 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 346vu38e7e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Oct 2020 15:59:28 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09FJvwH7028679;
        Thu, 15 Oct 2020 19:59:28 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma02dal.us.ibm.com with ESMTP id 3434ka7ehf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 15 Oct 2020 19:59:27 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 09FJxQud43057414
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 15 Oct 2020 19:59:26 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9F37B7805F;
        Thu, 15 Oct 2020 19:59:26 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1DFAD7805C;
        Thu, 15 Oct 2020 19:59:26 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.130.217])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Thu, 15 Oct 2020 19:59:25 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com
Subject: [PATCH v2 0/2] DIAG 318 tests and fix
Date: Thu, 15 Oct 2020 15:59:11 -0400
Message-Id: <20201015195913.101065-1-walling@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-15_15:2020-10-14,2020-10-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 phishscore=0 adultscore=0 spamscore=0 impostorscore=0 priorityscore=1501
 malwarescore=0 mlxlogscore=807 suspectscore=1 mlxscore=0 bulkscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010150129
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two patches: one that fixes a case where the DIAG 318 info was not 
actually being reset during load normal, and another patch to inroduce
selftests for DIAG 318 -- which helped discover the aforementioned issue ;)

Collin Walling (2):
  s390/kvm: fix diag318 reset
  self_tests/kvm: sync_regs and reset tests for diag318

 arch/s390/kvm/kvm-s390.c                      |  2 +-
 tools/testing/selftests/kvm/Makefile          |  2 +-
 .../kvm/include/s390x/diag318_test_handler.h  | 13 +++
 .../kvm/lib/s390x/diag318_test_handler.c      | 82 +++++++++++++++++++
 tools/testing/selftests/kvm/s390x/resets.c    | 14 ++++
 .../selftests/kvm/s390x/sync_regs_test.c      | 16 +++-
 6 files changed, 126 insertions(+), 3 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/diag318_test_handler.h
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/diag318_test_handler.c
```
