

#### [PATCH 0/4 v2] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Sep 28 07:20:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11803075
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44EB4618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:23:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 281DC221E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 07:23:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="QCZtw2V7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726522AbgI1HXL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 03:23:11 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:54482 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725290AbgI1HXK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 28 Sep 2020 03:23:10 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08S7Jtco168897;
        Mon, 28 Sep 2020 07:23:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=d7ZEO5jR7hJyMp821h2Wa5X71XbFJtbszhz+p47YXkc=;
 b=QCZtw2V7qj3icgc8fdhReaVM2kPsmXoaMmfrDWDOC06/jPV+g4yurEKxGzWj+woGFu4C
 iWWRL11uQL9wd/ebQsOzXVrCJqRCOm+EtxypSqJoVy7prMlB7s3iH3zLibB4vEWCY8+G
 eX/X3yYbfZ4QdPKBuAiFtZpwvcVgu7tCmXgFVbGtX0V4stvDPkbtyCHgiKDh6Jl3oTTe
 MQO2rRM9+hq7F/B68gNXPiA06dnoHNI0lReymd8tfg/MO/kFBnCaXF+Z1PtdhHIhWlrL
 JakL13vFCVSCez+eMGZPqPGsG8OKshb+p4lweuepcGwn27+Q9/ccW2OcrGRm4FvbLl/G nw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2130.oracle.com with ESMTP id 33su5akgy4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 28 Sep 2020 07:23:07 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08S7KMiZ187025;
        Mon, 28 Sep 2020 07:21:06 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3020.oracle.com with ESMTP id 33tfhvwkya-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 28 Sep 2020 07:21:06 +0000
Received: from abhmp0017.oracle.com (abhmp0017.oracle.com [141.146.116.23])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 08S7L6KR024050;
        Mon, 28 Sep 2020 07:21:06 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 28 Sep 2020 00:21:06 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 0/4 v2] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
 svm_set_nested_state() and test CR3 non-MBZ reserved bits
Date: Mon, 28 Sep 2020 07:20:39 +0000
Message-Id: <20200928072043.9359-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9757
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxlogscore=591 bulkscore=0
 phishscore=0 malwarescore=0 adultscore=0 suspectscore=1 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009280061
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9757
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=597
 suspectscore=1
 lowpriorityscore=0 spamscore=0 clxscore=1015 mlxscore=0 impostorscore=0
 malwarescore=0 phishscore=0 adultscore=0 bulkscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009280061
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	1. Patch# 2 has added checks for DR6, DR7 and EFER to
	   SVM_SET_NESTED_STATE path.
	2. Patch# 4 is a new addition. It has added missing checks for EFER
	   to nested_vmcb_checks().

[PATCH 1/4 v2] KVM: nSVM: CR3 MBZ bits are only 63:52
[PATCH 2/4 v2] KVM: nSVM: Add check for reserved bits for CR3, CR4, DR6,
[PATCH 3/4 v2] KVM: nSVM: Test non-MBZ reserved bits in CR3 in long mode
[PATCH 4/4 v2] KVM: nSVM: nested_vmcb_checks() needs to check all bits of

 arch/x86/kvm/svm/nested.c | 58 ++++++++++++++++++++++++++++-------------------
 arch/x86/kvm/svm/svm.h    |  2 +-
 2 files changed, 36 insertions(+), 24 deletions(-)

Krish Sadhukhan (3):
      KVM: nSVM: CR3 MBZ bits are only 63:52
      KVM: nSVM: Add check for reserved bits for CR3, CR4, DR6, DR7 and EFER to 
svm_set_nested_state()
      KVM: nSVM: nested_vmcb_checks() needs to check all bits of EFER

 x86/svm.h       |  3 ++-
 x86/svm_tests.c | 52 ++++++++++++++++++++++++++++++++++++++++++++++------
 2 files changed, 48 insertions(+), 7 deletions(-)

Krish Sadhukhan (1):
      KVM: nSVM: Test non-MBZ reserved bits in CR3 in long mode
```
#### [PATCH 0/2] KVM: nSVM: do not access MSR permission bitmap before
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Mon Sep 28 11:51:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11803559
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B33B36CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:52:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 975EB2100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 11:52:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QgAbH5Xs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726596AbgI1Lvu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 07:51:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:27458 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726564AbgI1Lvu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 07:51:50 -0400
Dkim-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601293909;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=vxB4Elj1Nndu0kAFuc8Y1iPA4beSknlsdeTyCEnHbQI=;
        b=QgAbH5Xs4YMtXT2mAyr0cQ/2a28qYxZRwyZBI1DkczvUtqEOwJOQ7LeNihgqXABqOBiCBM
        Kps/8jTqA5Atx4DCR/7FfivLQuJInkgL+7ALr1xQ6QrgdMINSZyaED2BWMTpG9pbtxn1h/
        yfNkPud0u23QyoHjL5y94eI266QvU3o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-264-EsuNcFYqNSepjckz9hM-LA-1; Mon, 28 Sep 2020 07:51:47 -0400
X-MC-Unique: EsuNcFYqNSepjckz9hM-LA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 49CC7100559B;
        Mon, 28 Sep 2020 11:51:45 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E910B19D7D;
        Mon, 28 Sep 2020 11:51:44 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mlevitsk@redhat.com
Subject: [PATCH 0/2] KVM: nSVM: do not access MSR permission bitmap before
 KVM_RUN
Date: Mon, 28 Sep 2020 07:51:42 -0400
Message-Id: <20200928115144.2446240-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similar to what we need to do for VMX, the MSR permission bitmap
should not be accessed until the first KVM_RUN.  This is important
because the memory map might not be up-to-date at the time of
KVM_SET_NESTED_STATE.

Paolo Bonzini (2):
  KVM: x86: rename KVM_REQ_GET_VMCS12_PAGES
  KVM: nSVM: delay MSR permission processing to first nested VM run

 arch/x86/include/asm/kvm_host.h |  4 ++--
 arch/x86/kvm/svm/nested.c       | 20 ++++++++++++++++++--
 arch/x86/kvm/vmx/nested.c       |  8 ++++----
 arch/x86/kvm/x86.c              |  4 ++--
 4 files changed, 26 insertions(+), 10 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/4] s390x: css: pv: css test adaptation for
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Sep 28 14:23:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11803907
Return-Path: <SRS0=x+XD=DF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1CE42618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 14:23:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC2FD21D46
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 28 Sep 2020 14:23:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="r1lVjEDU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726558AbgI1OXp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 28 Sep 2020 10:23:45 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:38292 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726327AbgI1OXp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 28 Sep 2020 10:23:45 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08SE2RmA090294;
        Mon, 28 Sep 2020 10:23:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=XRXRkWlANitcZgKg896dnP8UeTTtQftCziZtY5iTuV8=;
 b=r1lVjEDUQ4QEEs3T0cxtWEL6XsxI6uIzLS/UbioGcDpJA38TmQxGguHhXbk4CuXJ8D2b
 Q5zZfzOh4hm+J5k12BlMK3QACHy+ZiB+DJbXd0MWYVR45x5yUsurTkMSfrXdOOXCSEi+
 wbflvh6kYoNomezjKDfB+nGQqmR0+4wrmeCEy2jZIWjxjo8pl0hOP0bUdLU2x7TExAvf
 RHChVeXl743sKo+4LCxd0j7HHGWnx76EbrQJh0Rr20dTRrtwcEzuYwaIhpk0y4HOd54w
 Buq4AJx/v3/+FDilMzYONS5ZEStvsxbx0mvi3Q5FoYA8qBdrR8IwyqndhrqLP/3uaDpL BA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ufvy441x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 10:23:44 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08SE2tcb092161;
        Mon, 28 Sep 2020 10:23:44 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33ufvy4410-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 10:23:43 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08SENDwW009075;
        Mon, 28 Sep 2020 14:23:41 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 33u5r9gmee-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 28 Sep 2020 14:23:41 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08SENcUM31719790
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 28 Sep 2020 14:23:39 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C5DF042049;
        Mon, 28 Sep 2020 14:23:38 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6BD474203F;
        Mon, 28 Sep 2020 14:23:38 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.66.164])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 28 Sep 2020 14:23:38 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/4] s390x: css: pv: css test adaptation for
 PV
Date: Mon, 28 Sep 2020 16:23:33 +0200
Message-Id: <1601303017-8176-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-28_14:2020-09-28,2020-09-28 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 mlxscore=0 lowpriorityscore=0 clxscore=1015 adultscore=0 spamscore=0
 bulkscore=0 mlxlogscore=999 malwarescore=0 priorityscore=1501
 suspectscore=3 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009280108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

I send a v2 even I got not a lot of answers for v1 because:
1 I forgot the kvm-unit-test header
2 the patch on uv.h was very bad
3 I saw some stupid errors I can correct myself like
  to zero the allocated page before use or free it on error.

That said, here what is done:

To adapt the CSS I/O tests to protected virtualisation we need
utilities to:

1- allocate the I/O buffers in a private page (patch 3)
   It must be in a dedicated page to avoid exporting code or
   guest private data to the host.

2- share  the I/O buffer with the host (patch 2)

3- be sure to allocate memory under 2Gb (patch 1)

The 3 first patches are the implementation of the tools,
patch 4 is the modification of the css.c test for PV.

regards,
Pierre

Pierre Morel (4):
  memory: allocation in low memory
  s390x: pv: implement routine to share/unshare memory
  s390x: define UV compatible I/O allocation
  s390x: css: pv: css test adaptation for PV

 lib/alloc_dma_page.c  | 57 +++++++++++++++++++++++++++++++++++++++++++
 lib/alloc_dma_page.h  | 24 ++++++++++++++++++
 lib/s390x/asm/uv.h    | 50 +++++++++++++++++++++++++++++++++++++
 lib/s390x/css.h       |  3 +--
 lib/s390x/css_lib.c   | 28 ++++++---------------
 lib/s390x/malloc_io.c | 49 +++++++++++++++++++++++++++++++++++++
 lib/s390x/malloc_io.h | 18 ++++++++++++++
 lib/s390x/sclp.c      |  2 ++
 s390x/Makefile        |  2 ++
 s390x/css.c           | 35 +++++++++++++++++---------
 10 files changed, 235 insertions(+), 33 deletions(-)
 create mode 100644 lib/alloc_dma_page.c
 create mode 100644 lib/alloc_dma_page.h
 create mode 100644 lib/s390x/malloc_io.c
 create mode 100644 lib/s390x/malloc_io.h
```
