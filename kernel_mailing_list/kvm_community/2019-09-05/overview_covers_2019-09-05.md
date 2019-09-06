

#### [PATCH v3 0/4] KVM: X86: Some tracepoint enhancements
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Thu Sep  5 02:36:12 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11132021
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A901C1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 02:36:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 91F49206BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 02:36:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729366AbfIECg3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 4 Sep 2019 22:36:29 -0400
Received: from mx1.redhat.com ([209.132.183.28]:57120 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728267AbfIECg3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 4 Sep 2019 22:36:29 -0400
Received: from mail-pf1-f197.google.com (mail-pf1-f197.google.com
 [209.85.210.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 60223182D
        for <kvm@vger.kernel.org>; Thu,  5 Sep 2019 02:36:29 +0000 (UTC)
Received: by mail-pf1-f197.google.com with SMTP id v15so706557pfe.7
        for <kvm@vger.kernel.org>; Wed, 04 Sep 2019 19:36:29 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=+eJV3E7CEyPbMu34xaIgaU3JSPlKajRTnFS7tmbRJtk=;
        b=hQJMAeE1g7qZoooyhsRUrJOAPtdZsxfwWatjbgenf3lpjYZHZLRYyMWPy0/GyEbGB6
         xwoj+63IedbSwRzYzvsoUtw16/hEpsIZmATHUz8SLBsFcW58Y9CiD4IqVMDKd5t1MfiW
         L0EbyAzPt5lHKUgsoI1+2u7ezXfDHDa/OVCgwgtoFaxk7W+YSS13jOzCO2Esa1I7EcDN
         /ZBogF6todYYz/K8gwQw5T6kp4DqAVVH35yZbgHsH0ZBq2pezbR/h+/xM9vipwCz8UOC
         U8+p1zaFTVNkbx97SA1IbPHDXkXJXVug6TI+cvcypDbAVFcSug2PwRGoLCbHn9SH7ehS
         CROg==
X-Gm-Message-State: APjAAAXyjN/KXaVD72PoKdeS6GobTRR8hxPtHWEHwSJTQcbj8VuXk1nB
        FEohVSf3cNtE6tfUqaByTucCqoa8MYB+K+JbOw0nVcYqhd5zwfAS8lsoN7sqfcc32zKy/aU06Jy
        RDt+y5IE1eLKx
X-Received: by 2002:a62:2d3:: with SMTP id 202mr1013667pfc.141.1567650988553;
        Wed, 04 Sep 2019 19:36:28 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzx71eeFT6dL7OSCTUDVdfMD8/EUHCs/7N3jRwZvsiHjEfDQi118LVrKauPmNizcCppky2hCg==
X-Received: by 2002:a62:2d3:: with SMTP id 202mr1013658pfc.141.1567650988377;
        Wed, 04 Sep 2019 19:36:28 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 v10sm326504pjk.23.2019.09.04.19.36.25
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 04 Sep 2019 19:36:27 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>, peterx@redhat.com
Subject: [PATCH v3 0/4] KVM: X86: Some tracepoint enhancements
Date: Thu,  5 Sep 2019 10:36:12 +0800
Message-Id: <20190905023616.29082-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
- use unsigned int for vcpu id [Sean]
- a new patch to fix ple_window type [Sean]

v2:
- fix commit messages, change format of ple window tracepoint [Sean]
- rebase [Wanpeng]

Each small patch explains itself.  I noticed them when I'm tracing
some IRQ paths and I found them helpful at least to me.

Please have a look.  Thanks,

Peter Xu (4):
  KVM: X86: Trace vcpu_id for vmexit
  KVM: X86: Remove tailing newline for tracepoints
  KVM: X86: Tune PLE Window tracepoint
  KVM: VMX: Change ple_window type to unsigned int

 arch/x86/kvm/svm.c     | 16 ++++++++--------
 arch/x86/kvm/trace.h   | 34 ++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.c | 18 ++++++++++--------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 arch/x86/kvm/x86.c     |  2 +-
 5 files changed, 34 insertions(+), 38 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/6] s390x: Add multiboot and smp
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Sep  5 10:39:45 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11132699
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEF5E112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:40:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C808822CF7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 10:40:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732848AbfIEKkH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 06:40:07 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:52190 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726162AbfIEKkH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 5 Sep 2019 06:40:07 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x85AcvF9075232
        for <kvm@vger.kernel.org>; Thu, 5 Sep 2019 06:40:06 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2utwrv87pc-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 05 Sep 2019 06:40:06 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 5 Sep 2019 11:40:04 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 5 Sep 2019 11:40:02 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x85AdbAb41746696
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 5 Sep 2019 10:39:37 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 476CD52050;
        Thu,  5 Sep 2019 10:40:01 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 86CE95204E;
        Thu,  5 Sep 2019 10:40:00 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/6] s390x: Add multiboot and smp
Date: Thu,  5 Sep 2019 12:39:45 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19090510-4275-0000-0000-0000036176B5
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19090510-4276-0000-0000-00003873BEA8
Message-Id: <20190905103951.36522-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-05_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=674 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909050106
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cross testing emulated instructions has in the past brought up some
issues on all available IBM Z hypervisors. So let's upstream the last
part of multiboot: sclp interrupts and line mode console.

SMP tests are a great way to excercise external interruptions, cpu
resets and sigp. The smp library is always initialized and provides
very rudimentary CPU management for now.

v2:
* Fixed cr0 masks
* Replaced gotos with loops
* Addressed other review comments

Janosch Frank (6):
  s390x: Use interrupts in SCLP and add locking
  s390x: Add linemode console
  s390x: Add linemode buffer to fix newline on every print
  s390x: Add initial smp code
  s390x: Prepare for external calls
  s390x: SMP test

 lib/s390x/asm/arch_def.h  |  13 ++
 lib/s390x/asm/interrupt.h |   5 +
 lib/s390x/asm/sigp.h      |  28 +++-
 lib/s390x/interrupt.c     |  28 +++-
 lib/s390x/io.c            |   5 +-
 lib/s390x/sclp-console.c  | 243 ++++++++++++++++++++++++++++++---
 lib/s390x/sclp.c          |  55 +++++++-
 lib/s390x/sclp.h          |  59 +++++++-
 lib/s390x/smp.c           | 276 ++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.h           |  51 +++++++
 s390x/Makefile            |   2 +
 s390x/cstart64.S          |   7 +
 s390x/smp.c               | 242 +++++++++++++++++++++++++++++++++
 s390x/unittests.cfg       |   4 +
 14 files changed, 991 insertions(+), 27 deletions(-)
 create mode 100644 lib/s390x/smp.c
 create mode 100644 lib/s390x/smp.h
 create mode 100644 s390x/smp.c
```
#### [PATCH 0/2] Revert and rework on the metadata accelreation
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Sep  5 12:27:34 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11133001
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5B0371395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 12:27:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 463492080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 12:27:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387806AbfIEM1o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 08:27:44 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52294 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726453AbfIEM1o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 08:27:44 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 93EF53001836;
        Thu,  5 Sep 2019 12:27:44 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-44.pek2.redhat.com [10.72.12.44])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DA1775D9E2;
        Thu,  5 Sep 2019 12:27:37 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Cc: netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jgg@mellanox.com, aarcange@redhat.com, jglisse@redhat.com,
        linux-mm@kvack.org
Subject: [PATCH 0/2] Revert and rework on the metadata accelreation
Date: Thu,  5 Sep 2019 20:27:34 +0800
Message-Id: <20190905122736.19768-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.40]);
 Thu, 05 Sep 2019 12:27:44 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi:

Per request from Michael and Jason, the metadata accelreation is
reverted in this version and rework in next version.

Please review.

Thanks

Jason Wang (2):
  Revert "vhost: access vq metadata through kernel virtual address"
  vhost: re-introducing metadata acceleration through kernel virtual
    address

 drivers/vhost/vhost.c | 202 +++++++++++++++++++++++++-----------------
 drivers/vhost/vhost.h |   8 +-
 2 files changed, 123 insertions(+), 87 deletions(-)
```
#### [PATCH 0/2] KVM: x86: Refactor MSR related helpers
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Sep  5 21:22:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11133959
Return-Path: <SRS0=qAVt=XA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40E5F1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 21:23:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2910B206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  5 Sep 2019 21:23:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389711AbfIEVW6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Sep 2019 17:22:58 -0400
Received: from mga03.intel.com ([134.134.136.65]:37535 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389217AbfIEVW5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Sep 2019 17:22:57 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Sep 2019 14:22:57 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,471,1559545200";
   d="scan'208";a="383038923"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga005.fm.intel.com with ESMTP; 05 Sep 2019 14:22:56 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: x86: Refactor MSR related helpers
Date: Thu,  5 Sep 2019 14:22:53 -0700
Message-Id: <20190905212255.26549-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Refactor x86's MSR accessors to reduce the amount of boilerplate code
required to get/set an MSR, and consolidate the RDMSR/WRMSR emulation
for VMX and SVM since the code is functionally identical.

Sean Christopherson (2):
  KVM: x86: Refactor up kvm_{g,s}et_msr() to simplify callers
  KVM: x86: Add kvm_emulate_{rd,wr}msr() to consolidate VXM/SVM code

 arch/x86/include/asm/kvm_host.h |   6 +-
 arch/x86/kvm/svm.c              |  34 +-------
 arch/x86/kvm/vmx/nested.c       |  22 ++---
 arch/x86/kvm/vmx/vmx.c          |  33 +-------
 arch/x86/kvm/x86.c              | 138 ++++++++++++++++++++------------
 5 files changed, 100 insertions(+), 133 deletions(-)
```
