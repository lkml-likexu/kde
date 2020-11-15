#### [PATCH 1/5 v5] KVM: x86: Change names of some of the kvm_x86_ops functions to make them more semantical and readable
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11905341
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AAC3BC63777
	for <kvm@archiver.kernel.org>; Sat, 14 Nov 2020 01:50:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 60B7D2225D
	for <kvm@archiver.kernel.org>; Sat, 14 Nov 2020 01:50:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="hpYBHuTx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726288AbgKNBud (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 13 Nov 2020 20:50:33 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:44730 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725981AbgKNBuc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 13 Nov 2020 20:50:32 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AE1o7O7171657;
        Sat, 14 Nov 2020 01:50:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=Cm6XOO8cbo/PJmwZrYa3Do2ypmW6OxiOhWllufopg+U=;
 b=hpYBHuTxxNeXASDU1Q86cU/Jz1ls1e1R04nBij1uCnnX8JgN+imJN9vhrSuNWyNHdCC+
 8D0NfUmWi4HVmNhHvWrdIsstTBhB58+m0/mAHCl16zaOUeFlXBJBYT/qR1nyJ9nkcDKV
 FZloz+dE/nz/a3cE+Xwo771rI6oBTIB7a9TVZwZrwCSfPWSJIJA4Bn04iRB9H5ThwS2Y
 2rkuTAVWhu8ezMsePV98n0KI0kGQY+cBwaXrAiTIpEU0cp5t2i+X/2iWwUBZbNJcCd0j
 h6VcBbVuMsIOQmpbZgMKgMCP3Kw7ulyGsk56up31H3nHl62wHO9pqL6M9L+S7CgC4lf+ YA==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2130.oracle.com with ESMTP id 34t4rag2m2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 14 Nov 2020 01:50:06 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AE1jMjH065501;
        Sat, 14 Nov 2020 01:50:06 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 34t598sefj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 14 Nov 2020 01:50:06 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0AE1o50g009503;
        Sat, 14 Nov 2020 01:50:05 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 13 Nov 2020 17:50:04 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com, qemu-devel@nongnu.org
Subject: [PATCH 1/5 v5] KVM: x86: Change names of some of the kvm_x86_ops
 functions to make them more semantical and readable
Date: Sat, 14 Nov 2020 01:49:51 +0000
Message-Id: <20201114014955.19749-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20201114014955.19749-1-krish.sadhukhan@oracle.com>
References: <20201114014955.19749-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9804
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 spamscore=0
 mlxlogscore=999 suspectscore=4 malwarescore=0 mlxscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011140009
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9804
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 clxscore=1015
 malwarescore=0 impostorscore=0 lowpriorityscore=0 priorityscore=1501
 mlxlogscore=999 adultscore=0 phishscore=0 suspectscore=4 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011140009
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/arm64/include/asm/kvm_host.h   |  2 +-
 arch/mips/include/asm/kvm_host.h    |  2 +-
 arch/powerpc/include/asm/kvm_host.h |  2 +-
 arch/s390/kvm/kvm-s390.c            |  2 +-
 arch/x86/include/asm/kvm_host.h     | 18 ++++++++--------
 arch/x86/kvm/lapic.c                |  2 +-
 arch/x86/kvm/svm/nested.c           |  2 +-
 arch/x86/kvm/svm/svm.c              | 14 ++++++-------
 arch/x86/kvm/vmx/nested.c           |  2 +-
 arch/x86/kvm/vmx/vmx.c              | 10 ++++-----
 arch/x86/kvm/x86.c                  | 32 ++++++++++++++---------------
 include/linux/kvm_host.h            |  2 +-
 include/uapi/linux/kvm.h            |  6 +++---
 tools/include/uapi/linux/kvm.h      |  6 +++---
 virt/kvm/kvm_main.c                 |  4 ++--
 15 files changed, 53 insertions(+), 53 deletions(-)

```
