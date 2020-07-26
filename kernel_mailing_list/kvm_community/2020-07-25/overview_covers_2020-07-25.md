

#### [PATCH 0/5 v2] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat Jul 25 03:26:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11684771
Return-Path: <SRS0=oNvx=BE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 966CB618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Jul 2020 03:27:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D510206C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Jul 2020 03:27:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="KP/fSyJz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726944AbgGYD05 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 23:26:57 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:47216 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726613AbgGYD05 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 23:26:57 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06P3GiXI091588;
        Sat, 25 Jul 2020 03:26:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=SRaAxkcNlWyEw1EgPM7VkjPo6ZqT1MUevOkH4aovnd0=;
 b=KP/fSyJzr9dRAXQdT7KAqBMSTKKHhxUVNhd+B8pbvb1NTZ3f0aCkD89OflO8jJoKws4n
 QN02QDa51u2WGAyjsyVkTGf1NXJtS957HHEpiDESPQDudrc36AzP4bXXqB3+lJ7bphRn
 7a6MwDdK0s7xSXovmpTAMiYjBCGD30qqTTUMMwRzQasa4TWX1wwZau7vabkTBtfEmATO
 4bdzKnQ3dGcYXZhMTAxtTTDm1Fq+Xc3a+2GERSmetQBx7LLivIPiOn5q1lwtQLe6wgRs
 XjdcVeJrrDMo/+WpfReBtuvEYQ/V2n1Ea7FsEvI0UeBk6VR8dpD0Gl+sqO5ogSiB4pXe 0w==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 32gcpkr0e6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 25 Jul 2020 03:26:52 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06P3MY7a083684;
        Sat, 25 Jul 2020 03:26:51 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 32gcj1rtp7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 25 Jul 2020 03:26:51 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 06P3QoIH014031;
        Sat, 25 Jul 2020 03:26:50 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Sat, 25 Jul 2020 03:26:50 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com
Subject: [PATCH 0/5 v2] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
 {vmx|svm}_nested_ops via macros
Date: Sat, 25 Jul 2020 03:26:33 +0000
Message-Id: <1595647598-53208-1-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9692
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 spamscore=0 phishscore=0
 mlxscore=0 mlxlogscore=692 malwarescore=0 bulkscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007250024
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9692
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxscore=0 bulkscore=0
 priorityscore=1501 phishscore=0 adultscore=0 malwarescore=0
 lowpriorityscore=0 impostorscore=0 clxscore=1015 mlxlogscore=701
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007250024
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1 -> v2:
	v2 has split v1 into five patches as follows:
		Patch# 1: Changes to kvm_x86_ops
		Patch# 2: Changes to svm_x86_ops
		Patch# 3: Changes to svm_nested_ops
		Patch# 4: Changes to vmx_x86_ops
		Patch# 5: Changes to vmx_nested_ops


[PATCH 1/5 v2] KVM: x86: Change names of some of the kvm_x86_ops
[PATCH 2/5 v2] KVM: SVM: Fill in conforming svm_x86_ops via macro
[PATCH 3/5 v2] KVM: nSVM: Fill in conforming svm_nested_ops via macro
[PATCH 4/5 v2] KVM: VMX: Fill in conforming vmx_x86_ops via macro
[PATCH 5/5 v2] KVM: nVMX: Fill in conforming vmx_nested_ops via macro

 arch/x86/include/asm/kvm_host.h |  12 +-
 arch/x86/kvm/svm/avic.c         |   4 +-
 arch/x86/kvm/svm/nested.c       |  18 +--
 arch/x86/kvm/svm/sev.c          |   6 +-
 arch/x86/kvm/svm/svm.c          | 218 ++++++++++++++++++------------------
 arch/x86/kvm/svm/svm.h          |   8 +-
 arch/x86/kvm/vmx/nested.c       |  26 +++--
 arch/x86/kvm/vmx/nested.h       |   2 +-
 arch/x86/kvm/vmx/vmx.c          | 238 ++++++++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.h          |   2 +-
 arch/x86/kvm/x86.c              |  22 ++--
 include/linux/kvm_host.h        |   2 +-
 virt/kvm/kvm_main.c             |   4 +-
 13 files changed, 285 insertions(+), 277 deletions(-)

Krish Sadhukhan (5):
      KVM: x86: Change names of some of the kvm_x86_ops functions to make them m
      KVM: SVM: Fill in conforming svm_x86_ops via macro
      KVM: nSVM: Fill in conforming svm_nested_ops via macro
      KVM: VMX: Fill in conforming vmx_x86_ops via macro
      KVM: nVMX: Fill in conforming vmx_nested_ops via macro
```
