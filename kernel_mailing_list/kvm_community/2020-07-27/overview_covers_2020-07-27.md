

#### [kvm-unit-tests PATCH v2 0/3] PV tests part 1
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon Jul 27 09:54:12 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11686699
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D256A138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 09:54:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C179320809
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 09:54:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727775AbgG0Jya (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 05:54:30 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40228 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726140AbgG0Jya (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Jul 2020 05:54:30 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06R9XN3X094221;
        Mon, 27 Jul 2020 05:54:29 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32htsjuasc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 05:54:29 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06R9XYkh094604;
        Mon, 27 Jul 2020 05:54:29 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32htsjuarf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 05:54:28 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06R9qTul012138;
        Mon, 27 Jul 2020 09:54:26 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma04fra.de.ibm.com with ESMTP id 32gcpw98pr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 27 Jul 2020 09:54:26 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06R9sNmT26149208
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 27 Jul 2020 09:54:23 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8201F4C05C;
        Mon, 27 Jul 2020 09:54:23 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B29364C046;
        Mon, 27 Jul 2020 09:54:22 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 27 Jul 2020 09:54:22 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/3] PV tests part 1
Date: Mon, 27 Jul 2020 05:54:12 -0400
Message-Id: <20200727095415.494318-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-27_06:2020-07-27,2020-07-27 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 suspectscore=0
 priorityscore=1501 mlxlogscore=873 phishscore=0 lowpriorityscore=0
 bulkscore=0 malwarescore=0 mlxscore=0 spamscore=0 adultscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007270069
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's start bringing in some more PV related code.

Somehow I missed that we can also have a key in a exception new
PSW. The interesting bit is that if such a PSW is loaded on an
exception it will result in a specification exception and not a
special operation exception.

The third patch adds a basic guest UV call API test. It has mostly
been used for firmware testing but I also think it's good to have a
building block like this for more PV tests.


GIT: https://github.com/frankjaa/kvm-unit-tests/tree/queue

v2:
	* Page alloc instead of static memory reservation
	* Moved pgm cleanup function call to pgm handler
	* Commit message changes


Janosch Frank (3):
  s390x: Add custom pgm cleanup function
  s390x: skrf: Add exception new skey test and add test to unittests.cfg
  s390x: Ultravisor guest API test

 lib/s390x/asm/interrupt.h |   1 +
 lib/s390x/asm/uv.h        |  68 ++++++++++++++++
 lib/s390x/interrupt.c     |  10 +++
 s390x/Makefile            |   1 +
 s390x/skrf.c              |  80 +++++++++++++++++++
 s390x/unittests.cfg       |   7 ++
 s390x/uv-guest.c          | 159 ++++++++++++++++++++++++++++++++++++++
 7 files changed, 326 insertions(+)
 create mode 100644 lib/s390x/asm/uv.h
 create mode 100644 s390x/uv-guest.c
```
#### [PATCH 0/3] KVM: nVMX: tighten some KVM_SET_NESTED_STATE validity
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon Jul 27 13:39:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11686883
Return-Path: <SRS0=pIbL=BG=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 85968722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 13:39:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D0DE20FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Jul 2020 13:39:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HvOqeCeO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728169AbgG0Njl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 09:39:41 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:48766 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726620AbgG0Njl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Jul 2020 09:39:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595857180;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fYBBQADx7LsYm+yccVufp29aOZIIf/4uKblRdnXFZb8=;
        b=HvOqeCeObUBBeODUhlnbSNC4+l/fmKgBf5QDqLdtyES1tiZJnolLYHbyNWL1YlsMJWmB+H
        PP8okaXRDxVXcDP5z2uKcfnA8qdtWDPztyYskr5upqb0M34Rl2ogNLXwaAM4m9FAEMBxq6
        oAsqxK7fy9/BJ77NZQvVjspCf4wm0SM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-337-glqHWLosMyKK-wuLx4oP5g-1; Mon, 27 Jul 2020 09:39:38 -0400
X-MC-Unique: glqHWLosMyKK-wuLx4oP5g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2409679EC4;
        Mon, 27 Jul 2020 13:39:37 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F3FCF5D9F3;
        Mon, 27 Jul 2020 13:39:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, aaronlewis@google.com
Subject: [PATCH 0/3] KVM: nVMX: tighten some KVM_SET_NESTED_STATE validity
 checks
Date: Mon, 27 Jul 2020 09:39:31 -0400
Message-Id: <20200727133934.25482-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is a fix to the tests so that we can cover the new cases properly.
Patches 2-3 check for more cases of invalid nested state data.

Paolo

Paolo Bonzini (3):
  selftests: kvm: do not set guest mode flag
  KVM: nVMX: check for required but missing VMCS12 in
    KVM_SET_NESTED_STATE
  KVM: nVMX: check for invalid hdr.vmx.flags

 arch/x86/kvm/vmx/nested.c                     | 16 +++++--
 arch/x86/kvm/vmx/nested.h                     |  5 +++
 .../kvm/x86_64/vmx_set_nested_state_test.c    | 42 +++++++++++++++----
 3 files changed, 51 insertions(+), 12 deletions(-)
```
