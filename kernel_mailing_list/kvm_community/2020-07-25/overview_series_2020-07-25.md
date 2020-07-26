#### [PATCH 1/5 v2] KVM: x86: Change names of some of the kvm_x86_ops functions to make them more semantical and readable
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11684779
Return-Path: <SRS0=oNvx=BE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EEC73618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Jul 2020 03:27:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC1FD206C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Jul 2020 03:27:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="y4YkVkgp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726953AbgGYD06 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 24 Jul 2020 23:26:58 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:47224 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726901AbgGYD06 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 24 Jul 2020 23:26:58 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06P3Hujv092043;
        Sat, 25 Jul 2020 03:26:52 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=Gn4F1mPu7ATLD+kgFaqjzZ6MYn7pkEJTpfYNVHPzGrE=;
 b=y4YkVkgpTmbMhgfAj4hv4xIXJLWAgka3pK3Y/Ixmd8w6/INHuuTwn24EyDNp2tuKdMyo
 3dFke8O8oTpWVi6jgOx7GGG9yOSbb37r713bRp7TIdYoY9h5wNQY7JmPkB7C3V0BJbB5
 9iJxzVBmhpv0PIPyB2xwnpKzkLhvDp7VqXJplSUx6dhyVJ+oSrQWuXQmhvPZ3PYUUP04
 F4l6ihD7jU7AbzTCGXofXnIM8YgL1wiQD8zUCjSNH17enofiVtvS0YIH3b7bu/nvgmJx
 pnYZTJgBDh3YZpVapt07PIeCMGa5+jcEvBdinn+bpl8G72JDNF0zyNKyJ+vUjmy6jbiC Sw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 32gcpkr0e7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 25 Jul 2020 03:26:52 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06P3DBF5099571;
        Sat, 25 Jul 2020 03:26:52 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 32g9uu8pyv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 25 Jul 2020 03:26:51 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 06P3QoC7017097;
        Sat, 25 Jul 2020 03:26:50 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Sat, 25 Jul 2020 03:26:50 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com
Subject: [PATCH 1/5 v2] KVM: x86: Change names of some of the kvm_x86_ops
 functions to make them more semantical and readable
Date: Sat, 25 Jul 2020 03:26:34 +0000
Message-Id: <1595647598-53208-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1595647598-53208-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1595647598-53208-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9692
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 spamscore=0 mlxscore=0
 adultscore=0 suspectscore=4 bulkscore=0 mlxlogscore=999 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007250024
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9692
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 mlxscore=0 bulkscore=0
 priorityscore=1501 phishscore=0 adultscore=0 malwarescore=0
 lowpriorityscore=0 impostorscore=0 clxscore=1015 mlxlogscore=999
 suspectscore=4 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007250024
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 12 ++++++------
 arch/x86/kvm/svm/svm.c          | 12 ++++++------
 arch/x86/kvm/vmx/vmx.c          |  8 ++++----
 arch/x86/kvm/x86.c              | 22 +++++++++++-----------
 include/linux/kvm_host.h        |  2 +-
 virt/kvm/kvm_main.c             |  4 ++--
 6 files changed, 30 insertions(+), 30 deletions(-)

```
