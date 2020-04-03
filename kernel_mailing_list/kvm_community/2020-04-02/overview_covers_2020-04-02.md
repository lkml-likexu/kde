

#### [PATCH v2 0/3] tools/kvm_stat: add logfile support
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From patchwork Thu Apr  2 08:57:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11470373
Return-Path: <SRS0=vumV=5S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FB121392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 08:57:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 87CD220CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 08:57:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387792AbgDBI5O (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Apr 2020 04:57:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:6060 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728612AbgDBI5N (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 2 Apr 2020 04:57:13 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0328YO9U108207
        for <kvm@vger.kernel.org>; Thu, 2 Apr 2020 04:57:12 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 304swspmj0-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 02 Apr 2020 04:57:12 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <raspl@linux.ibm.com>;
        Thu, 2 Apr 2020 09:56:54 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 2 Apr 2020 09:56:51 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0328v6Qx57999492
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 2 Apr 2020 08:57:06 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 766D4A4051;
        Thu,  2 Apr 2020 08:57:06 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4BFEAA4057;
        Thu,  2 Apr 2020 08:57:06 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  2 Apr 2020 08:57:06 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH v2 0/3] tools/kvm_stat: add logfile support
Date: Thu,  2 Apr 2020 10:57:02 +0200
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
x-cbid: 20040208-0016-0000-0000-000002FCD22A
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20040208-0017-0000-0000-000033609ABD
Message-Id: <20200402085705.61155-1-raspl@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-02_01:2020-03-31,2020-04-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=1
 bulkscore=0 clxscore=1015 lowpriorityscore=0 mlxlogscore=991 phishscore=0
 adultscore=0 impostorscore=0 malwarescore=0 priorityscore=1501 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2004020073
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Next attempt to come up with support for logfiles that can be combined
with a solution for rotating logs.
Adding another patch to skip records with all zeros to preserve space.

Changes in v2:
- Addressed feedback from patch review
- Beefed up man page descriptions of --csv and --log-to-file (fixing
  a glitch in the former)
- Use a metavar for -L in the --help output


Stefan Raspl (3):
  tools/kvm_stat: add command line switch '-z' to skip zero records
  tools/kvm_stat: Add command line switch '-L' to log to file
  tools/kvm_stat: add sample systemd unit file

 tools/kvm/kvm_stat/kvm_stat         | 84 ++++++++++++++++++++++++-----
 tools/kvm/kvm_stat/kvm_stat.service | 16 ++++++
 tools/kvm/kvm_stat/kvm_stat.txt     | 15 +++++-
 3 files changed, 101 insertions(+), 14 deletions(-)
 create mode 100644 tools/kvm/kvm_stat/kvm_stat.service
```
#### [kvm-unit-tests PATCH v8 00/13] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Thu Apr  2 14:52:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11470907
Return-Path: <SRS0=vumV=5S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B0011668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 14:52:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED29320757
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 14:52:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RB59wdcU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388760AbgDBOwr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Apr 2020 10:52:47 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20300 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1732598AbgDBOwq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Apr 2020 10:52:46 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585839166;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=V5Kw0rzsF+uN7oZ/ix5qLdtcjmsaTXjUInee5I5wEVg=;
        b=RB59wdcUqKhNq+9BX8k0bA4IJbRaIbzhIXlsGqKq0FfyAURSiYZ8esHHyvIPSl4yVQfQSw
        3bRmE7/KW/ZLa2y9YA873s7UN6rCXfH1A274KuAVZT6+wGFO67dyM1di7z+QfNx5Juzizr
        AYoT7P2TQX1/kX1pIIHt6uYTuwTSd6Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-492-WuIbVq8sP_agJfh56bxLPQ-1; Thu, 02 Apr 2020 10:52:42 -0400
X-MC-Unique: WuIbVq8sP_agJfh56bxLPQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 793018024D1;
        Thu,  2 Apr 2020 14:52:40 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-58.ams2.redhat.com [10.36.112.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8F6295D9C9;
        Thu,  2 Apr 2020 14:52:31 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v8 00/13] arm/arm64: Add ITS tests
Date: Thu,  2 Apr 2020 16:52:14 +0200
Message-Id: <20200402145227.20109-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
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

The series can be fount at:
https://github.com/eauger/kut/tree/its-v8

Applies on top of arm/queue.

Best Regards

Eric

History:

v7 -> v8:
- take into account last comments from Zenghui and collected
  his R-bs

v6 -> v7:
- Fixed issue reported by Drew in its-migrate-unmapped-collection (a collection
  could be allocated twice depending on the SMP value)
- Integrated changes prepared by Drew
- Use for_each_present_cpu()

v5 -> v6:
- Took into account Zenghui's comments, mostly functional: see invidual
  history logs
- fix wrong assert!

v4 -> v5:
- 32b stubs moved back to arm/gic.c
- some changes reordering
- minor style issues

v3 -> v4:
- addressed comments from Drew and Zenghui
- added "page_alloc: Introduce get_order()"
- removed "arm: gic: Provide per-IRQ helper functions"
- ITS files moved to lib64
- and many more, see individual logs

v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

Execution:
x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Eric Auger (13):
  libcflat: Add other size defines
  page_alloc: Introduce get_order()
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: Commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 454 ++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/alloc_page.c           |   7 +-
 lib/alloc_page.h           |   1 +
 lib/arm/asm/gic-v3-its.h   |  27 +++
 lib/arm/asm/gic-v3.h       |  29 +++
 lib/arm/asm/gic.h          |   1 +
 lib/arm/asm/processor.h    |   2 +
 lib/arm/gic-v3.c           |  78 +++++++
 lib/arm/gic.c              |  40 +++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h | 174 ++++++++++++++
 lib/arm64/gic-v3-its-cmd.c | 459 +++++++++++++++++++++++++++++++++++++
 lib/arm64/gic-v3-its.c     | 171 ++++++++++++++
 lib/libcflat.h             |   3 +
 18 files changed, 1486 insertions(+), 31 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm64/asm/gic-v3-its.h
 create mode 100644 lib/arm64/gic-v3-its-cmd.c
 create mode 100644 lib/arm64/gic-v3-its.c
```
#### [PATCH 0/3] x86: KVM: VMX: Add basic split-lock #AC handling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Apr  2 15:55:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11471087
Return-Path: <SRS0=vumV=5S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 648B21668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 15:56:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 422B120757
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 15:56:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389325AbgDBP4v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Apr 2020 11:56:51 -0400
Received: from mga06.intel.com ([134.134.136.31]:50591 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389618AbgDBP4v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Apr 2020 11:56:51 -0400
IronPort-SDR: 
 Bg/mpS8NduwrtGlxKS1TB2XNC7o3imN/846LvE3avKky3cYU75ab9SobGeBXHf3xeG1XVl4ZKp
 CpwGIfDbJzDQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Apr 2020 08:56:49 -0700
IronPort-SDR: 
 jyOiuXukMJhwojIPNuzpfJ9nU3RopoRR/yNMidbUYgAtGsQVDkUlYbJPSk/0GofpqJEnUBPx+z
 dZ40IbSFVtFw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,336,1580803200";
   d="scan'208";a="396413079"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga004.jf.intel.com with ESMTP; 02 Apr 2020 08:56:49 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>
Cc: x86@kernel.org, "Kenneth R . Crudup" <kenny@panix.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>,
        Nadav Amit <namit@vmware.com>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jessica Yu <jeyu@kernel.org>,
        Steven Rostedt <rostedt@goodmis.org>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/3] x86: KVM: VMX: Add basic split-lock #AC handling
Date: Thu,  2 Apr 2020 08:55:51 -0700
Message-Id: <20200402155554.27705-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200402124205.334622628@linutronix.de>
References: <20200402124205.334622628@linutronix.de>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

First three patches from Xiaoyao's series to add split-lock #AC support
in KVM.

Xiaoyao Li (3):
  KVM: x86: Emulate split-lock access as a write in emulator
  x86/split_lock: Refactor and export handle_user_split_lock() for KVM
  KVM: VMX: Extend VMX's #AC interceptor to handle split lock #AC in
    guest

 arch/x86/include/asm/cpu.h  |  4 ++--
 arch/x86/kernel/cpu/intel.c |  7 ++++---
 arch/x86/kernel/traps.c     |  2 +-
 arch/x86/kvm/vmx/vmx.c      | 30 +++++++++++++++++++++++++++---
 arch/x86/kvm/x86.c          | 12 +++++++++++-
 5 files changed, 45 insertions(+), 10 deletions(-)
```
#### [PATCH v1 0/5] KVM: s390: vsie: fixes and cleanups.
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Thu Apr  2 18:48:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11471249
Return-Path: <SRS0=vumV=5S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E91001668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 18:48:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C199020719
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Apr 2020 18:48:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="O1td6uof"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388971AbgDBSs3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Apr 2020 14:48:29 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:45895 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732214AbgDBSs3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 2 Apr 2020 14:48:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585853308;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=in1JW2F7wVAjQuehuFAsT9rFLhWovQC510FWxPd6gOY=;
        b=O1td6uofzPDkkf8DBUfSMRG6TqLjXt4ED6F5Zj5J+V+BQn2ytmedCQZ+qeV7bhdgHU86Gg
        uoROf294H8qj0IfGr9UDOKtScC2lGLweQQeETBoQIe9gPPnJEck54j7R50WueEawPlU9ti
        PtriJx2um3O/hEhRYzwFLl/wHDIrF2k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-284-U1l9J9PpNNeAqadNNHj6-Q-1; Thu, 02 Apr 2020 14:48:26 -0400
X-MC-Unique: U1l9J9PpNNeAqadNNHj6-Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0FD031926DA0;
        Thu,  2 Apr 2020 18:48:25 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-29.ams2.redhat.com [10.36.114.29])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 90D1E60BF4;
        Thu,  2 Apr 2020 18:48:20 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>
Subject: [PATCH v1 0/5] KVM: s390: vsie: fixes and cleanups.
Date: Thu,  2 Apr 2020 20:48:14 +0200
Message-Id: <20200402184819.34215-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some vsie/gmap fixes and two cleanups/improvements.

Patch #1 fixes an issue reported by Janosch. It was never observed so far,
because KVM usually doesn't use a region 1 table for it's guest (unless
memory would be exceeding something like 16 EB, which isn't even supported
by the HW). Older QEMU+KVM or other hypervisors can trigger this.

Patch #2 fixes a code path that probably was never taken and will most
probably not be taken very often in the future - unless somebody really
messes up the page tables for a guest (or writes a test for it). At some
point, a test case for this would be nice.

Patch #3 fixes a rare possible race. Don't think this is stable material.

Gave it some testing with my limited access to somewhat-fast s390x
machines. Booted a Linux kernel, supplying all possible number of
page table hiearchies.

David Hildenbrand (5):
  KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks
  KVM: s390: vsie: Fix delivery of addressing exceptions
  KVM: s390: vsie: Fix possible race when shadowing region 3 tables
  KVM: s390: vsie: Move conditional reschedule
  KVM: s390: vsie: gmap_table_walk() simplifications

 arch/s390/kvm/vsie.c |  4 ++--
 arch/s390/mm/gmap.c  | 14 ++++++++++----
 2 files changed, 12 insertions(+), 6 deletions(-)
```
