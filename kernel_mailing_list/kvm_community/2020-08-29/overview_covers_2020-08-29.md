

#### [PATCH 0/3] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat Aug 29 00:48:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11743851
Return-Path: <SRS0=1t8w=CH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD670109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:48:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C4772207DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 29 Aug 2020 00:48:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="jhmRo6/7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726944AbgH2Asr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Aug 2020 20:48:47 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:34884 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726869AbgH2Asj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Aug 2020 20:48:39 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0V1r6087293;
        Sat, 29 Aug 2020 00:48:35 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=xFg/BQMz3bsVskq5cgWTmD6sFdOD/BuRzh/w00Bg8B8=;
 b=jhmRo6/7ZHMLaaYhzgKJlLe7Zyi/XYDfhpnANUHk5quEyAMd+fq1M6RtRnevvb/cWOZW
 gp5vfmNWvpX9nEVhqK9zzYyhN7tyZ/R9/Tg0gpjadRCljA0c21tjSnlpKW6cBIFKkLsp
 lGORLgjyvHavirAtbF54pEfnqX4l+Yq3LXmlc4IaYf3XnVSc/z+2zgQN+q08pngRFdnB
 pijPYrk6YtmaVNeAxJwXJIJqMPwXHyGjiRKdDiCu0al5K8Fjvnmw1sbLLKtoKLUXIqB0
 gh/wQesnpwqR/gsSzOEcjajwm43JNVKlEPtLtQNznOOUP3/5BhpjSyXRHhc6vVIfQMW7 Ng==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 336ht3pq4j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 29 Aug 2020 00:48:35 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07T0UQ8j015684;
        Sat, 29 Aug 2020 00:48:34 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 333ruh3wen-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 29 Aug 2020 00:48:34 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 07T0mWDM032676;
        Sat, 29 Aug 2020 00:48:33 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 28 Aug 2020 17:48:32 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 0/3] KVM: nSVM: Add checks for CR3 and CR4 reserved bits to
 svm_set_nested_state() and test CR3 non-MBZ reserved bits
Date: Sat, 29 Aug 2020 00:48:21 +0000
Message-Id: <20200829004824.4577-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=601
 phishscore=0
 bulkscore=0 suspectscore=1 spamscore=0 mlxscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008290000
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9727
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 adultscore=0 malwarescore=0
 phishscore=0 priorityscore=1501 clxscore=1015 suspectscore=1 spamscore=0
 impostorscore=0 mlxscore=0 mlxlogscore=592 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008290000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch# 1: Fixes the MBZ mask for CR3
Patch# 2: Adds checks for the reserved bits for CR3 and CR4 to
	  svm_set_nested_state() since these bits need to be checked before
	  VMRUN of the nested guest on the destination.
Patch# 3: Adds a test for the non-MBZ reserved bits in CR3 in long mode.


[PATCH 1/3] KVM: nSVM: CR3 MBZ bits are only 63:52
[PATCH 2/3] KVM: nSVM: Add check for CR3 and CR4 reserved bits to
[PATCH 3/3] nSVM: Test non-MBZ reserved bits in CR3 in long mode

 arch/x86/kvm/svm/nested.c | 51 +++++++++++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.h    |  2 +-
 2 files changed, 30 insertions(+), 23 deletions(-)

Krish Sadhukhan (2):
      KVM: nSVM: CR3 MBZ bits are only 63:52
      KVM: nSVM: Add check for CR3 and CR4 reserved bits to svm_set_nested_state()

 x86/svm.h       |  3 ++-
 x86/svm_tests.c | 54 +++++++++++++++++++++++++++++++++++++++++++++++-------
 2 files changed, 49 insertions(+), 8 deletions(-)

Krish Sadhukhan (1):
      KVM: nSVM: Test non-MBZ reserved bits in CR3 in long mode
```
