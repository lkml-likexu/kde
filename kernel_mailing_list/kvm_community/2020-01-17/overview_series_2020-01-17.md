#### [PATCH 1/4] KVM: x86: Handle TIF_NEED_FPU_LOAD in kvm_{load,put}_guest_fpu()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11338403
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33DF992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 06:26:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C649214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 06:26:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727018AbgAQG0j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 01:26:39 -0500
Received: from mga17.intel.com ([192.55.52.151]:14600 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726370AbgAQG0i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jan 2020 01:26:38 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 16 Jan 2020 22:26:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,329,1574150400";
   d="scan'208";a="424342472"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga005.fm.intel.com with ESMTP; 16 Jan 2020 22:26:30 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Derek Yerger <derek@djy.llc>,
        kernel@najdan.com, Thomas Lambertz <mail@thomaslambertz.de>,
        Rik van Riel <riel@surriel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Borislav Petkov <bp@suse.de>,
        Dave Hansen <dave.hansen@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH 1/4] KVM: x86: Handle TIF_NEED_FPU_LOAD in
 kvm_{load,put}_guest_fpu()
Date: Thu, 16 Jan 2020 22:26:25 -0800
Message-Id: <20200117062628.6233-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200117062628.6233-1-sean.j.christopherson@intel.com>
References: <20200117062628.6233-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Handle TIF_NEED_FPU_LOAD similar to how fpu__copy() handles the flag
when duplicating FPU state to a new task struct.  TIF_NEED_FPU_LOAD can
be set any time control is transferred out of KVM, be it voluntarily,
e.g. if I/O is triggered during a KVM call to get_user_pages, or
involuntarily, e.g. if softirq runs after an IRQ occurs.  Therefore,
KVM must account for TIF_NEED_FPU_LOAD whenever it is (potentially)
accessing CPU FPU state.

Fixes: 5f409e20b7945 ("x86/fpu: Defer FPU state load until return to userspace")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 27 ++++++++++++++++++++++++---
 1 file changed, 24 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/4] KVM: x86: Handle TIF_NEED_FPU_LOAD in kvm_{load,put}_guest_fpu()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11339703
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D660B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 19:34:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD84A2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 19:34:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729640AbgAQTet (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 14:34:49 -0500
Received: from mga18.intel.com ([134.134.136.126]:18185 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726897AbgAQTeh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Jan 2020 14:34:37 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Jan 2020 11:30:54 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,331,1574150400";
   d="scan'208";a="274474192"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Jan 2020 11:30:53 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Derek Yerger <derek@djy.llc>,
        kernel@najdan.com, Thomas Lambertz <mail@thomaslambertz.de>,
        Rik van Riel <riel@surriel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Borislav Petkov <bp@suse.de>,
        Dave Hansen <dave.hansen@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>
Subject: [PATCH v2 1/4] KVM: x86: Handle TIF_NEED_FPU_LOAD in
 kvm_{load,put}_guest_fpu()
Date: Fri, 17 Jan 2020 11:30:49 -0800
Message-Id: <20200117193052.1339-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200117193052.1339-1-sean.j.christopherson@intel.com>
References: <20200117193052.1339-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Handle TIF_NEED_FPU_LOAD similar to how fpu__copy() handles the flag
when duplicating FPU state to a new task struct.  TIF_NEED_FPU_LOAD can
be set any time control is transferred out of KVM, be it voluntarily,
e.g. if I/O is triggered during a KVM call to get_user_pages, or
involuntarily, e.g. if softirq runs after an IRQ occurs.  Therefore,
KVM must account for TIF_NEED_FPU_LOAD whenever it is (potentially)
accessing CPU FPU state.

Fixes: 5f409e20b7945 ("x86/fpu: Defer FPU state load until return to userspace")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 19 +++++++++++++++++--
 1 file changed, 17 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/9] s390x: smp: Cleanup smp.c
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11338727
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1BB513A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 10:46:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 871FA2082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 10:46:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727007AbgAQKqy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 05:46:54 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:58600 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726988AbgAQKqy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jan 2020 05:46:54 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00HAc5qn017754
        for <kvm@vger.kernel.org>; Fri, 17 Jan 2020 05:46:53 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xk0qt0s34-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 17 Jan 2020 05:46:53 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 17 Jan 2020 10:46:51 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 17 Jan 2020 10:46:49 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00HAkmaD51773676
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Jan 2020 10:46:48 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8FF67AE053;
        Fri, 17 Jan 2020 10:46:48 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EC11FAE045;
        Fri, 17 Jan 2020 10:46:46 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.184.110])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Jan 2020 10:46:46 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v3 1/9] s390x: smp: Cleanup smp.c
Date: Fri, 17 Jan 2020 05:46:32 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200117104640.1983-1-frankja@linux.ibm.com>
References: <20200117104640.1983-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20011710-4275-0000-0000-0000039872A5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20011710-4276-0000-0000-000038AC73BE
Message-Id: <20200117104640.1983-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-17_02:2020-01-16,2020-01-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 suspectscore=1 mlxlogscore=991
 impostorscore=0 adultscore=0 mlxscore=0 priorityscore=1501 bulkscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-2001170083
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's remove a lot of badly formatted code by introducing the
wait_for_flag() function.

Also let's remove some stray spaces.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/smp.c | 42 +++++++++++++++++++++++-------------------
 1 file changed, 23 insertions(+), 19 deletions(-)

```
#### [PATCH] selftests: KVM: AMD Nested SVM test infrastructure
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11339579
Return-Path: <SRS0=EZ3U=3G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 42E9F13A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 17:38:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04B262083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Jan 2020 17:38:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="I599wNZs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727519AbgAQRiH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Jan 2020 12:38:07 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:56611 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726897AbgAQRiG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Jan 2020 12:38:06 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579282685;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=QFOOgqhFsqI9DYUxxLxgxFud7Sg63z+qSXnoN965h98=;
        b=I599wNZsEKiid7gB6ULM6BS/SZj50QZKtG1Ewk8vNBWuY+EG+mRuJGIem34IOLqQxh28B6
        dnDz950bqGETOlT+qsyFBpIgK5/n/z6EKLoemLz65+v1TV13ai776b4Dlleqi3wFoGUaMl
        n5z81t87hmTCXoJZx+gFAXSrwXRcwlc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-101-nb6ld6TLOLuLWvRF-zwPuQ-1; Fri, 17 Jan 2020 12:38:03 -0500
X-MC-Unique: nb6ld6TLOLuLWvRF-zwPuQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id ACC44DB20;
        Fri, 17 Jan 2020 17:38:02 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-117-108.ams2.redhat.com
 [10.36.117.108])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 21B581BC6D;
        Fri, 17 Jan 2020 17:37:57 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com, vkuznets@redhat.com
Cc: thuth@redhat.com, drjones@redhat.com
Subject: [PATCH] selftests: KVM: AMD Nested SVM test infrastructure
Date: Fri, 17 Jan 2020 18:37:53 +0100
Message-Id: <20200117173753.21434-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the basic infrastructure needed to test AMD nested SVM.
This is largely copied from the KVM unit test infrastructure.
Three very basic tests come along, executed in sequence.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

Given the amount of code taken from KVM unit test, I would be
more than happy to transfer any authorship. Please let me know.
---
 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/include/x86_64/svm.h        | 390 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/x86_64/svm.c  | 211 ++++++++++
 tools/testing/selftests/kvm/x86_64/svm_test.c | 127 ++++++
 4 files changed, 730 insertions(+), 1 deletion(-)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/svm.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/svm_test.c

```
