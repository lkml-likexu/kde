#### [PATCH 01/61] KVM: x86: Return -E2BIG when KVM_GET_SUPPORTED_CPUID hits max entries
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11361363
Return-Path: <SRS0=7ik9=3V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ABB7092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  1 Feb 2020 18:58:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 92B7020661
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  1 Feb 2020 18:58:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727166AbgBAS55 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 1 Feb 2020 13:57:57 -0500
Received: from mga05.intel.com ([192.55.52.43]:37509 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726664AbgBASw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 1 Feb 2020 13:52:26 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 01 Feb 2020 10:52:25 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,390,1574150400";
   d="scan'208";a="248075431"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 01 Feb 2020 10:52:25 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 01/61] KVM: x86: Return -E2BIG when KVM_GET_SUPPORTED_CPUID
 hits max entries
Date: Sat,  1 Feb 2020 10:51:18 -0800
Message-Id: <20200201185218.24473-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200201185218.24473-1-sean.j.christopherson@intel.com>
References: <20200201185218.24473-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a long-standing bug that causes KVM to return 0 instead of -E2BIG
when userspace's array is insufficiently sized.

Note, while the Fixes: tag is accurate with respect to the immediate
bug, it's likely that similar bugs in KVM_GET_SUPPORTED_CPUID existed
prior to the refactoring, e.g. Qemu contains a workaround for the broken
KVM_GET_SUPPORTED_CPUID behavior that predates the buggy commit by over
two years.  The Qemu workaround is also likely the main reason the bug
has gone unreported for so long.

Qemu hack:
  commit 76ae317f7c16aec6b469604b1764094870a75470
  Author: Mark McLoughlin <markmc@redhat.com>
  Date:   Tue May 19 18:55:21 2009 +0100

    kvm: work around supported cpuid ioctl() brokenness

    KVM_GET_SUPPORTED_CPUID has been known to fail to return -E2BIG
    when it runs out of entries. Detect this by always trying again
    with a bigger table if the ioctl() fills the table.

Fixes: 831bf664e9c1f ("KVM: Refactor and simplify kvm_dev_ioctl_get_supported_cpuid")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v5 1/7] s390x: smp: Cleanup smp.c
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11361133
Return-Path: <SRS0=7ik9=3V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29C94159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  1 Feb 2020 15:29:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1263F20723
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  1 Feb 2020 15:29:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726677AbgBAP3F (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 1 Feb 2020 10:29:05 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:3640 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726668AbgBAP3F (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 1 Feb 2020 10:29:05 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 011FGpK1030097
        for <kvm@vger.kernel.org>; Sat, 1 Feb 2020 10:29:04 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xw6qcf80m-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Sat, 01 Feb 2020 10:29:03 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Sat, 1 Feb 2020 15:29:01 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Sat, 1 Feb 2020 15:28:58 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 011FSviE54526000
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 1 Feb 2020 15:28:57 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B607652051;
        Sat,  1 Feb 2020 15:28:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.30.110])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id E74F85204E;
        Sat,  1 Feb 2020 15:28:56 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v5 1/7] s390x: smp: Cleanup smp.c
Date: Sat,  1 Feb 2020 10:28:45 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200201152851.82867-1-frankja@linux.ibm.com>
References: <20200201152851.82867-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20020115-0028-0000-0000-000003D68679
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20020115-0029-0000-0000-0000249ADAC6
Message-Id: <20200201152851.82867-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-01_03:2020-01-31,2020-02-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 bulkscore=0
 priorityscore=1501 mlxscore=0 suspectscore=1 malwarescore=0 clxscore=1015
 lowpriorityscore=0 impostorscore=0 spamscore=0 phishscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-1911200001
 definitions=main-2002010113
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's remove a lot of badly formatted code by introducing the
wait_for_flag() and set_flag functions.

Also let's remove some stray spaces and always set the tesflag before
using it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/smp.c | 55 ++++++++++++++++++++++++++++++++---------------------
 1 file changed, 33 insertions(+), 22 deletions(-)

```
