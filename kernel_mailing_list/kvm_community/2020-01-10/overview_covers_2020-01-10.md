

#### [kvm-unit-tests PATCH v2 00/16] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Jan 10 14:53:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11327509
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3912F921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 14:54:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 18D5E2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 14:54:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bXT8FW7W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728167AbgAJOy1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 09:54:27 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:48743 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728137AbgAJOy1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 09:54:27 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1578668065;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VexdPnxBGtP4m5sD088Fr2Z7oIrl6ON5vXnTAqxCkko=;
        b=bXT8FW7W23colUYzK3Tk5jCRYh4JV1zdnZ+HhZb6aK0AlOczWAO2p4qJQKg0SJw5yJIsVi
        iiFMcbAOoRArQVfDLz1T00WAPxI1c/lq+8zS9shc01xiV4+rYI22wvWxtBk0q0ah8Zi/p8
        UnWTpvsVSAJGuEzClHeCLmMIFxvPeQs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-139-R0oieHwYPCy7edteuUVVHg-1; Fri, 10 Jan 2020 09:54:22 -0500
X-MC-Unique: R0oieHwYPCy7edteuUVVHg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5A7EA801B3A;
        Fri, 10 Jan 2020 14:54:20 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-117-108.ams2.redhat.com
 [10.36.117.108])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A869082475;
        Fri, 10 Jan 2020 14:54:14 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 00/16] arm/arm64: Add ITS tests
Date: Fri, 10 Jan 2020 15:53:56 +0100
Message-Id: <20200110145412.14937-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found related
to the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

This series includes Andre's patch: "arm: gic: Provide
per-IRQ helper functions" [2]

test_migrate_unmapped_collection is currently failing with
upstream kernel. See [3].

The series can be fount at:
https://github.com/eauger/kut/tree/its-v2

Best Regards

Eric

History:
v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

[2] [kvm-unit-tests PATCH 00/17] arm: gic: Test SPIs and interrupt groups
    https://patchwork.kernel.org/cover/11234975/

[3] [PATCH] KVM: arm/arm64: vgic-its: Fix restoration of unmappedxi
    collections (https://lkml.org/lkml/2019/12/13/205)

Execution:
x For ITS migration testing use:
  ./run_tests.sh -g migration (blocks on TCG)

x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Andre Przywara (1):
  arm: gic: Provide per-IRQ helper functions

Eric Auger (15):
  libcflat: Add other size defines
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: Test BASER
  arm/arm64: ITS: Set the LPI config and pending tables
  arm/arm64: ITS: Init the command queue
  arm/arm64: ITS: Enable/Disable LPIs at re-distributor level
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.common        |   3 +-
 arm/gic.c                  | 446 ++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  39 ++++
 lib/arm/asm/gic-v3-its.h   | 177 +++++++++++++++
 lib/arm/asm/gic-v3.h       |  20 ++
 lib/arm/asm/gic.h          |  12 +
 lib/arm/gic-v3-its-cmd.c   | 453 +++++++++++++++++++++++++++++++++++++
 lib/arm/gic-v3-its.c       | 327 ++++++++++++++++++++++++++
 lib/arm/gic.c              | 132 ++++++++++-
 lib/arm/io.c               |  13 ++
 lib/arm64/asm/gic-v3-its.h |   1 +
 lib/libcflat.h             |   3 +
 13 files changed, 1600 insertions(+), 28 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm/gic-v3-its-cmd.c
 create mode 100644 lib/arm/gic-v3-its.c
 create mode 100644 lib/arm64/asm/gic-v3-its.h
```
#### [kvm-unit-tests PATCH v7 0/4] s390x: SCLP Unit test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Jan 10 18:40:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11328237
Return-Path: <SRS0=Qd/p=27=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46D28139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 18:41:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3022420842
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 10 Jan 2020 18:41:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728581AbgAJSk7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 10 Jan 2020 13:40:59 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15842 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727927AbgAJSk7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 10 Jan 2020 13:40:59 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00AIbI4K066516
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 13:40:57 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xerexcw3c-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 10 Jan 2020 13:40:57 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Fri, 10 Jan 2020 18:40:55 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 10 Jan 2020 18:40:53 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00AIepne48038082
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 10 Jan 2020 18:40:51 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6C1F5AE053;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 30101AE051;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.108])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 10 Jan 2020 18:40:51 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v7 0/4] s390x: SCLP Unit test
Date: Fri, 10 Jan 2020 19:40:46 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011018-0008-0000-0000-0000034854E2
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011018-0009-0000-0000-00004A689F5A
Message-Id: <20200110184050.191506-1-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-10_01:2020-01-10,2020-01-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 lowpriorityscore=0 malwarescore=0 suspectscore=1 clxscore=1015 bulkscore=0
 mlxscore=0 adultscore=0 priorityscore=1501 phishscore=0 mlxlogscore=876
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001100150
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

Claudio Imbrenda (4):
  s390x: export sclp_setup_int
  s390x: sclp: add service call instruction wrapper
  s390x: lib: add SPX and STPX instruction wrapper
  s390x: SCLP unit test

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |  26 +++
 lib/s390x/sclp.h         |   1 +
 lib/s390x/sclp.c         |   9 +-
 s390x/intercept.c        |  23 +-
 s390x/sclp.c             | 472 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   8 +
 7 files changed, 518 insertions(+), 22 deletions(-)
 create mode 100644 s390x/sclp.c
```
