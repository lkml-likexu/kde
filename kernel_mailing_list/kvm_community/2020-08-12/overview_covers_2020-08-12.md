

#### [kvm-unit-tests RFC v2 0/4] s390x: Add Protected VM support
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
From patchwork Wed Aug 12 09:27:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11710525
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C4712722
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 09:27:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ABA7F2087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 09:27:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="qtj/ccKb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727898AbgHLJ1U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 05:27:20 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:11124 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726595AbgHLJ1U (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 12 Aug 2020 05:27:20 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07C92vOC018455;
        Wed, 12 Aug 2020 05:27:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=+gTdxR6U0oFG7t/4d1maDhtNhplafuqA41t3kWJWwc0=;
 b=qtj/ccKbF3lukVNEVvP0RiqFsGhx9LpsvuxpuN1J6nTDDH/yU3OcURLYin1VyNb9dhy/
 q7vHkN+u8HzT3IsJFaiQR7WH+IbLGQczr47gXlIcTw7FbOL0DuUXbIczHCqA3cRS2Sk1
 OpcfDvd3NOsMDolACvAh64flOCKG0CbYAfnw3Djz7JyxSJS7wHELxszsGg1FnhkpBE2A
 tM3+gZjkKrUbd19U9YRqjSNZPU5gfc19WPfE+o4KqRXsad9/kG1ZgSK3jsQ0pkRIeq9N
 wzkEuqQhWNwtpc2J5ttkVJ+zOlF/rRUjiW8m/cs2QECV0trZR0TofWPLwnAqrYz+xMG4 bQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32uytmnk1w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 05:27:19 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07C93scV022544;
        Wed, 12 Aug 2020 05:27:19 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32uytmnk13-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 05:27:19 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07C9Kq94022264;
        Wed, 12 Aug 2020 09:27:16 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 32skp82m0q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 09:27:16 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07C9RDPX18743664
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 Aug 2020 09:27:13 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AAFB75206B;
        Wed, 12 Aug 2020 09:27:13 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.75.196])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 4BDCE52059;
        Wed, 12 Aug 2020 09:27:13 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests RFC v2 0/4] s390x: Add Protected VM support
Date: Wed, 12 Aug 2020 11:27:01 +0200
Message-Id: <20200812092705.17774-1-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-12_02:2020-08-11,2020-08-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 spamscore=0
 phishscore=0 impostorscore=0 suspectscore=0 lowpriorityscore=0
 clxscore=1011 malwarescore=0 priorityscore=1501 bulkscore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008120064
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for Protected Virtual Machine (PVM) tests. For starting a
PVM guest we must be able to generate a PVM image by using the
`genprotimg` tool from the s390-tools collection. This requires the
ability to pass a machine-specific host-key document, so the option
`--host-key-document` is added to the configure script.

Sorry it took so long to send the second version :/

For everybody's convenience there is a branch:
https://gitlab.com/mhartmay/kvm-unit-tests/-/tree/test_alternative

Changelog:
 RFC v1 -> RFC v2:
  + Remove `pv_support` option (Janosch, David)
  + Add some preliminary patches:
    - move "testname guard"
    - add support for architecture dependent functions
  + Add support for specifying a parmline file for the PV image
    generation. This is necessary for the `selftest` because the
    kernel cmdline set on the QEMU command line is ignored for PV
    guests

Marc Hartmayer (4):
  common.bash: run `cmd` only if a test case was found
  scripts: add support for architecture dependent functions
  run_tests/mkstandalone: add arch dependent function to
    `for_each_unittest`
  s390x: add Protected VM support

 README.md               |  3 ++-
 configure               |  8 ++++++++
 run_tests.sh            |  5 +----
 s390x/Makefile          | 17 +++++++++++++++--
 s390x/selftest.parmfile |  1 +
 s390x/unittests.cfg     |  1 +
 scripts/common.bash     | 26 ++++++++++++++++++++++++--
 scripts/mkstandalone.sh |  6 +-----
 scripts/s390x/func.bash | 18 ++++++++++++++++++
 9 files changed, 71 insertions(+), 14 deletions(-)
 create mode 100644 s390x/selftest.parmfile
 create mode 100644 scripts/s390x/func.bash
```
#### [PATCH v2 0/2] KVM: x86/mmu: Zap orphaned kids for nested TDP MMU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Aug 12 19:27:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11711231
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C77A5138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:28:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B9FDE2087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:28:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726686AbgHLT2C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 15:28:02 -0400
Received: from mga18.intel.com ([134.134.136.126]:34390 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726587AbgHLT2A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 15:28:00 -0400
IronPort-SDR: 
 zoXD7keQ3URsOwAfjv5Ebb2pKraph742aIu/rKwzfAAijEfiOrTnDhyaXmTO73XrvU6gBHk3P/
 L9k0Grsnqx5g==
X-IronPort-AV: E=McAfee;i="6000,8403,9711"; a="141673016"
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="141673016"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Aug 2020 12:27:59 -0700
IronPort-SDR: 
 /2rCWyevFd4pRorsikkBmd6R7lSJUGswtFRds8dYx9r1HVg3Y5eUzp0wDhDYBrEjwnyXchV502
 h9TMyZTPB0eA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="327304449"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga002.fm.intel.com with ESMTP; 12 Aug 2020 12:27:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Shier <pshier@google.com>,
        Ben Gardon <bgardon@google.com>
Subject: [PATCH v2 0/2] KVM: x86/mmu: Zap orphaned kids for nested TDP MMU
Date: Wed, 12 Aug 2020 12:27:56 -0700
Message-Id: <20200812192758.25587-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As promised, albeit a few days late.

Ben, I kept your performance numbers even though it this version has
non-trivial differences relative to what you tested.  I assume we'll need
a v3 anyways if this doesn't provide the advertised performance benefits.

Ben Gardon (1):
  KVM: x86/MMU: Recursively zap nested TDP SPs when zapping last/only
    parent

Sean Christopherson (1):
  KVM: x86/mmu: Move flush logic from mmu_page_zap_pte() to
    FNAME(invlpg)

 arch/x86/kvm/mmu/mmu.c         | 38 ++++++++++++++++++++++------------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 30 insertions(+), 15 deletions(-)
```
