

#### [kvm-unit-tests PATCH v2 0/5] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Oct 25 17:06:29 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11212741
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41AB91390
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:06:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2AE9921D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:06:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2505790AbfJYRGo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 13:06:44 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10500 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2409759AbfJYRGn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Oct 2019 13:06:43 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9PH4BqR018501
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 13:06:42 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vv51d0955-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 13:06:41 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Fri, 25 Oct 2019 18:06:39 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 25 Oct 2019 18:06:37 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9PH6ZYH60817498
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 25 Oct 2019 17:06:35 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 62D47A405B;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2AC11A4053;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/5] s390x: SCLP Unit test
Date: Fri, 25 Oct 2019 19:06:29 +0200
X-Mailer: git-send-email 2.7.4
X-TM-AS-GCONF: 00
x-cbid: 19102517-4275-0000-0000-00000377A609
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102517-4276-0000-0000-0000388AD48D
Message-Id: <1572023194-14370-1-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-25_09:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=524 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910250157
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset contains some minor cleanup, some preparatory work and
then the SCLP unit test itself.

The unit test checks the following:
    
    * Correctly ignoring instruction bits that should be ignored
    * Privileged instruction check
    * Check for addressing exceptions
    * Specification exceptions:
      - SCCB size less than 8
      - SCCB unaligned
      - SCCB overlaps prefix or lowcore
      - SCCB address higher than 2GB
    * Return codes for
      - Invalid command
      - SCCB too short (but at least 8)
      - SCCB page boundary violation

v1 -> v2
* fix many small issues that came up during the first round of reviews
* add comments to each function
* use a static buffer for the SCCP template when used

Claudio Imbrenda (5):
  s390x: remove redundant defines
  s390x: improve error reporting for interrupts
  s390x: sclp: expose ram_size and max_ram_size
  s390x: sclp: add service call instruction wrapper
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  13 ++
 lib/s390x/sclp.h         |   4 +-
 lib/s390x/interrupt.c    |   4 +-
 lib/s390x/sclp.c         |  17 +-
 s390x/sclp.c             | 413 +++++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   3 +
 7 files changed, 445 insertions(+), 10 deletions(-)
 create mode 100644 s390x/sclp.c
```
