

#### [kvm-unit-tests PATCH v8 0/6] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Jan 20 18:42:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11342733
Return-Path: <SRS0=Yh5O=3J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8E621820
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jan 2020 18:43:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B14AC2253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jan 2020 18:43:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726951AbgATSnF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jan 2020 13:43:05 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58910 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726752AbgATSnF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Jan 2020 13:43:05 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00KIcjrY165777
        for <kvm@vger.kernel.org>; Mon, 20 Jan 2020 13:43:04 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xkxhx7u0q-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 20 Jan 2020 13:43:04 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Mon, 20 Jan 2020 18:43:01 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 20 Jan 2020 18:42:58 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00KIgvpE50724958
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 20 Jan 2020 18:42:57 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2A3C44C059;
        Mon, 20 Jan 2020 18:42:57 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E10294C04E;
        Mon, 20 Jan 2020 18:42:56 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 20 Jan 2020 18:42:56 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v8 0/6] s390x: SCLP Unit test
Date: Mon, 20 Jan 2020 19:42:50 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012018-0012-0000-0000-0000037F2437
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012018-0013-0000-0000-000021BB6205
Message-Id: <20200120184256.188698-1-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-20_08:2020-01-20,2020-01-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 phishscore=0 lowpriorityscore=0 malwarescore=0 suspectscore=1
 priorityscore=1501 bulkscore=0 adultscore=0 mlxscore=0 mlxlogscore=698
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001200156
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

v7 -> v8
* fixed existing stfl asm wrapper
* now using stfl asm wrapper in intercept.c
* patched the program interrupt handler to clear the sclp_busy bit
* removed now unnecessary expect_pgm_int from the unit test
v6 -> v7
* renamed spx() and stpx() wrappers to set_prefix and get_prefix
* set_prefix now takes a value and get_prefix now returns a value
* put back some inline assembly for spx and stpx as a consequence
* used LC_SIZE instead of 2 * PAGE_SIZE everywhere in the unit test
v5 -> v6
* fixed a bug in test_addressing
* improved comments in test_sccb_prefix
* replaced all inline assembly usages of spx and stpx with the wrappers
* added one more wrapper for test_one_sccb for read-only tests
v4 -> v5
* updated usage of report()
* added SPX and STPX wrappers to the library
* improved readability
* addressed some more comments
v3 -> v4
* export sclp_setup_int instead of copying it
* add more comments
* rename some more variables to improve readability
* improve the prefix test
* improved the invalid address test
* addressed further comments received during review
v2 -> v3
* generally improved the naming of variables
* added and fixed comments
* renamed test_one_run to test_one_simple
* added some const where needed
* addresed many more small comments received during review
v1 -> v2
* fix many small issues that came up during the first round of reviews
* add comments to each function
* use a static buffer for the SCCP template when used

Claudio Imbrenda (6):
  s390x: export sclp_setup_int
  s390x: sclp: add service call instruction wrapper
  s390x: lib: fix stfl wrapper asm
  s390x: lib: add SPX and STPX instruction wrapper
  s390x: lib: fix program interrupt handler if sclp_busy was set
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  26 +++
 lib/s390x/asm/facility.h |   2 +-
 lib/s390x/sclp.h         |   1 +
 lib/s390x/interrupt.c    |   5 +-
 lib/s390x/sclp.c         |   9 +-
 s390x/intercept.c        |  24 +-
 s390x/sclp.c             | 474 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   8 +
 9 files changed, 526 insertions(+), 24 deletions(-)
 create mode 100644 s390x/sclp.c
```
#### [kvm-unit-tests v2 0/2] README: Markdown fixes and improvements
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Mon Jan 20 19:43:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11342783
Return-Path: <SRS0=Yh5O=3J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE5BB921
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jan 2020 19:43:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CBC7B217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 20 Jan 2020 19:43:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f3+8kIZ7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726816AbgATTnU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jan 2020 14:43:20 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:25135 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726607AbgATTnU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 20 Jan 2020 14:43:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579549399;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=TyG55MTjUoBMLEG8BW8OKgWBWAsVlRkkQJTLyAKX0ZE=;
        b=f3+8kIZ7Dh0qz1nHiPwO+ZML7rjV05JBFhkmcwbtz/j8jmmMKdSqFg8xG4Dk0EV8EiB0xk
        /6bTnh1sAyNuM11zqMAkLo/6SLh5eOcybFpKEFq3zPxqz6/S3qM2iDniFeoBN/glStJKSq
        BiyE/svW8z8IAwXZvS01F6z79ub1Gr4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-250-P8q-FFlsN0qNlb69DTVUNg-1; Mon, 20 Jan 2020 14:43:17 -0500
X-MC-Unique: P8q-FFlsN0qNlb69DTVUNg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 83DD4804707
        for <kvm@vger.kernel.org>; Mon, 20 Jan 2020 19:43:16 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-78.gru2.redhat.com
 [10.97.116.78])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 857F15C1BB;
        Mon, 20 Jan 2020 19:43:13 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com
Subject: [kvm-unit-tests v2 0/2] README: Markdown fixes and improvements
Date: Mon, 20 Jan 2020 16:43:08 -0300
Message-Id: <20200120194310.3942-1-wainersm@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series does fix issues with formatting of the README's
markdown. On patch 02 is added a new section that describes
the test configuration file.

Changes v1 -> v2:
 - Keep markdown minimal while still fixing the formatting issues [drjones]
 - Sent new content on separate patch (added patch 02) [drjones]

v1: https://lore.kernel.org/kvm/20200116212054.4041-1-wainersm@redhat.com

Wainer dos Santos Moschetta (2):
  README: Fix markdown formatting
  README: Add intro about the configuration file

 README.md | 83 +++++++++++++++++++++++++++++++++----------------------
 1 file changed, 50 insertions(+), 33 deletions(-)
```
