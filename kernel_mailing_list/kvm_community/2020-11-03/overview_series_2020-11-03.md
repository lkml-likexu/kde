#### [PATCH 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from userspace
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11878437
Return-Path: <SRS0=IfBm=EJ=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C54D7C388F7
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 17:14:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7554D22264
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 17:14:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604423698;
	bh=dXEnHT3KBrFGBtDRncZU5JV1CSETwhjDLw19AwLEk8k=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=wDpYYLz4YJTdxAwB+Dcbkf6cUzxaFq8oDDoXqL63assRZqV80wSykIxQSGa8F+dnj
	 34wiuBvLT/PBwWVkPqGZy/+qbSewyfw1IH96+dExPApzHe54nA84lFPtgmrQ3nVOWF
	 sPfBsolrwO05FF2rsrGP5hkIkWFh2ZmyZ0taCgRU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728630AbgKCROy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 3 Nov 2020 12:14:54 -0500
Received: from mail.kernel.org ([198.145.29.99]:40626 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728292AbgKCROx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Nov 2020 12:14:53 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6DE7B21556;
        Tue,  3 Nov 2020 17:14:52 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604423692;
        bh=dXEnHT3KBrFGBtDRncZU5JV1CSETwhjDLw19AwLEk8k=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=PeZIp7Av4+Yq50chJTJKGK35HFT6CPIWadMgPJ1oHezTSUMzHgYuG0dIP4W6R2JhF
         nlTHTXulgTQOPJeFV9ZdY0atA197DPVGaf2yX+Zo+I0W8Wu114ntIQXWJMP7aD0cgo
         wmKPJGErVRq4uWdkUmmNHUbIhkxZ/+AZOanZb2DQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kZztS-007CyW-NV; Tue, 03 Nov 2020 17:14:50 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Peng Liang <liangpeng10@huawei.com>, Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from
 userspace
Date: Tue,  3 Nov 2020 17:14:43 +0000
Message-Id: <20201103171445.271195-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201103171445.271195-1-maz@kernel.org>
References: <20201103171445.271195-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, liangpeng10@huawei.com,
 will@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We now expose ID_AA64PFR0_EL1.CSV2=1 to guests running on hosts
that are immune to Spectre-v2, but that don't have this field set,
most likely because they predate the specification.

However, this prevents the migration of guests that have started on
a host the doesn't fake this CSV2 setting to one that does, as KVM
rejects the write to ID_AA64PFR0_EL2 on the grounds that it isn't
what is already there.

In order to fix this, allow userspace to set this field as long as
this doesn't result in a promising more than what is already there
(setting CSV2 to 0 is acceptable, but setting it to 1 when it is
already set to 0 isn't).

Fixes: e1026237f9067 ("KVM: arm64: Set CSV2 for guests on hardware unaffected by Spectre-v2")
Reported-by: Peng Liang <liangpeng10@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h |  2 ++
 arch/arm64/kvm/arm.c              | 16 +++++++++++++
 arch/arm64/kvm/sys_regs.c         | 38 +++++++++++++++++++++++++++----
 3 files changed, 52 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: check that clflushopt of an MMIO address succeeds
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 11878287
Return-Path: <SRS0=IfBm=EJ=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BAB69C2D0A3
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 16:09:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6134A22264
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 16:09:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="tB3D0CIQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727812AbgKCQJC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 3 Nov 2020 11:09:02 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:38914 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725993AbgKCQJB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Nov 2020 11:09:01 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0A3FtcFk168866
        for <kvm@vger.kernel.org>; Tue, 3 Nov 2020 16:09:00 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=BzyRShX+37XSMmw8RUqVfB2YPoE1HUlKjtCnZT+4haU=;
 b=tB3D0CIQ1uPCQwoze6bGxoFg1zjXdz9scrCatZ8YUxhQk7p8WmE7/VjO9Iyo/RaKHeI6
 QuDTzU4HuZd/TIObbFT5Le/0B+taZYVNxeZGaU3Kvp2jEKm0wOUl9Wn/uIPTcyuTsgtW
 UvzCU+SEZ3Yy9I03cLNIvOtoo1hIvB5yy4ShNd9CfYP8KdlQBKbjFsn8/mO9nZi4HMBi
 xYi4UbBHMR9EaLF+rQZiWb2/MPsMJXn/vaI9Voswe0AmP3soE19Sl1A07K/ANwrSt46H
 WMPuf5XydD5wupWcjahKMJ+FtKB8DhQhJeQzKCXqScu1xEtADeMmER/f9Whnqql2wTbW cw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 34hhvca359-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL)
        for <kvm@vger.kernel.org>; Tue, 03 Nov 2020 16:09:00 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0A3FsnX7126213
        for <kvm@vger.kernel.org>; Tue, 3 Nov 2020 16:09:00 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 34jf48pkvw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Tue, 03 Nov 2020 16:09:00 +0000
Received: from abhmp0018.oracle.com (abhmp0018.oracle.com [141.146.116.24])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0A3G8xIE001861
        for <kvm@vger.kernel.org>; Tue, 3 Nov 2020 16:08:59 GMT
Received: from disaster-area.hh.sledj.net (/81.187.26.238)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 03 Nov 2020 08:08:59 -0800
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id b0adc6ae;
        Tue, 3 Nov 2020 16:08:55 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: kvm@vger.kernel.org
Cc: David Edmondson <david.edmondson@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [kvm-unit-tests PATCH] x86: check that clflushopt of an MMIO address
 succeeds
Date: Tue,  3 Nov 2020 16:08:55 +0000
Message-Id: <20201103160855.261881-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9794
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0 mlxscore=0
 bulkscore=0 malwarescore=0 mlxlogscore=999 phishscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011030108
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9794
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=0
 impostorscore=0 malwarescore=0 priorityscore=1501 mlxlogscore=999
 bulkscore=0 phishscore=0 adultscore=0 mlxscore=0 lowpriorityscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011030108
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that the clflushopt instruction succeeds when applied to an
MMIO address at both cpl0 and cpl3.

Suggested-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
This is a test for the fix included in:
https://lore.kernel.org/r/20201103120400.240882-1-david.edmondson@oracle.com

 x86/Makefile.common   |  3 ++-
 x86/clflushopt_mmio.c | 58 +++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg     |  5 ++++
 3 files changed, 65 insertions(+), 1 deletion(-)
 create mode 100644 x86/clflushopt_mmio.c

```
#### [PATCH] KVM: x86: clflushopt should be treated as a no-op by emulation
##### From: David Edmondson <david.edmondson@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 11877283
Return-Path: <SRS0=IfBm=EJ=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8073BC4742C
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 12:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1CFBF22264
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 12:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="aLc618jU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728915AbgKCMHz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 3 Nov 2020 07:07:55 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:46802 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728146AbgKCMHz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Nov 2020 07:07:55 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0A3BxhkK075803;
        Tue, 3 Nov 2020 12:06:12 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=h9MFns4+YUM2WrMN1n/hdiPQQ9AmvoWKTdDk9TUNovM=;
 b=aLc618jUYvkIpc6amrRH57re+QonILrYfcHUpV7rkyFlfV9Usuo2GTt6h4OAhUJwXd5K
 81YnIXqlWBuCRrx6lGKPGXrhsZSIwWuvpsqJraedawh7s4AqMk6+XtqL3L57Yl0KErhE
 Xkx4hAi10CU1EZyloP+wwBjb3/oFTiiNMj4voujIa53reKmheIhH1nleLuYYfNwh6cy+
 PdOnVfTrE2GjxSZuV97+KixDqPEsJ5mn1e+VWHYN7jn8GDShkTn5NFRazsAg3/BXcOQo
 XQhzo7aLG3ctjQCBrRd+Dx9w/CQwtMHEdXA20zJ/ACt3TmKjjHs2TpomqAOGxZgVSqJq 1g==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by aserp2120.oracle.com with ESMTP id 34hhvc8ves-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 03 Nov 2020 12:06:11 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0A3C0fGM156489;
        Tue, 3 Nov 2020 12:04:11 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 34hw0df56d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 03 Nov 2020 12:04:11 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0A3C459J030210;
        Tue, 3 Nov 2020 12:04:05 GMT
Received: from disaster-area.hh.sledj.net (/81.187.26.238)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 03 Nov 2020 04:04:05 -0800
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 82f746cd;
        Tue, 3 Nov 2020 12:04:00 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Nadav Amit <namit@cs.technion.ac.il>, x86@kernel.org,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH] KVM: x86: clflushopt should be treated as a no-op by
 emulation
Date: Tue,  3 Nov 2020 12:04:00 +0000
Message-Id: <20201103120400.240882-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9793
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 mlxlogscore=906
 phishscore=0 bulkscore=0 spamscore=0 malwarescore=0 mlxscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011030083
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9793
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 suspectscore=1
 impostorscore=0 malwarescore=0 priorityscore=1501 mlxlogscore=933
 bulkscore=0 phishscore=0 adultscore=0 mlxscore=0 lowpriorityscore=0
 clxscore=1011 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2011030083
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The instruction emulator ignores clflush instructions, yet fails to
support clflushopt. Treat both similarly.

Fixes: 13e457e0eebf ("KVM: x86: Emulator does not decode clflush well")
Signed-off-by: David Edmondson <david.edmondson@oracle.com>
---
 arch/x86/kvm/emulate.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH v5] KVM: Check the allocation of pv cpu mask
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 11876345
Return-Path: <SRS0=IfBm=EJ=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 96A48C388F7
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 08:52:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3441022275
	for <kvm@archiver.kernel.org>; Tue,  3 Nov 2020 08:52:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mmHGeeOf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727529AbgKCIwm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 3 Nov 2020 03:52:42 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50858 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725968AbgKCIwm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Nov 2020 03:52:42 -0500
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BD001C0613D1;
        Tue,  3 Nov 2020 00:52:41 -0800 (PST)
Received: by mail-pg1-x542.google.com with SMTP id i7so11214671pgh.6;
        Tue, 03 Nov 2020 00:52:41 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x0V9Eqsw0P/c1uqnmbZIL7sQkwkXO9ZRETLMblzJ8gw=;
        b=mmHGeeOfpKkGy9BXLSA5CXBvj1YkjRIcKTdmituqmoxcsQkc/MaSlOf2gMGlU/PADh
         z0P4HpgvC3s9CIiP3T8sJuahEWTNB3j9eogiQo+kqAMCK58eQDF80XcGc0o3vY3Jj3y+
         cuBt8QUScSQu1vfWOef6m8SDoDvgfh7WbsKKIY01sRy56WhFWXMHqMjtIPeV88DCUHiU
         ky5y36SyCraqGgjwSfb+c4mhqWQPOJsGNLzV30NYpqON3PeK9eSuDZKPkoWK+4bXmFUF
         sF4GIKawTEPZ/wik8JHK/wxWqBJGVGa5SnHu0D7MzPKtJJVU4rj4O76awq5f5ZxTB0wG
         6o2g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x0V9Eqsw0P/c1uqnmbZIL7sQkwkXO9ZRETLMblzJ8gw=;
        b=eBRFSecLlF0uA8qKiuRvuBjed0gcev6/bnb62WQuR7jWHWIcAJbHaDbK9ey8fxAQ8r
         OF5IcYcLrarvZ1B5M+H9f44CDMn2MeAL6mAxKCkqqEYvjjnv5XqX7JZllBXSMOeiYgpY
         o7HfTIotObCaxudTjJPtm3+XJY2RYiHDPNELC1n9m3+oCfnkyX5gkLkqIUurZ/K2a6qk
         Z/5bAVgWJYW63IFRATqQAHdlUiyTvJQ7ba+b7ODzns2XyDIGqqDMWP1rGV8zrMYYxs5i
         pAdne5sYkZHfo4RMxE3O68TZwBsE83/gg5PnqBQ5xDN3zVx9MYOQs6KynOeFZJkEZUhT
         ahvQ==
X-Gm-Message-State: AOAM533bEsYdmlL8gA+bV002B8IE+L+jgXoYZV1ZvPM3MnqwxahjVl1O
        LIbzRRsbERvkn6iF6FWj8gHDQlKHsanFN8s=
X-Google-Smtp-Source: 
 ABdhPJxcq5b+6l9ITRsWB1Ya1KrxYn9ZW+9/FYoZ0RkoB4msCHH1juevPLTgR45sRW2PGWSk75YCkg==
X-Received: by 2002:a17:90b:384b:: with SMTP id
 nl11mr2799496pjb.126.1604393560956;
        Tue, 03 Nov 2020 00:52:40 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id
 q13sm15978340pfg.3.2020.11.03.00.52.37
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 03 Nov 2020 00:52:40 -0800 (PST)
From: lihaiwei.kernel@gmail.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v5] KVM: Check the allocation of pv cpu mask
Date: Tue,  3 Nov 2020 16:52:27 +0800
Message-Id: <20201103085227.25098-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Both 'kvm_send_ipi_mask_allbutself' and 'kvm_flush_tlb_others' are using
per-cpu __pv_cpu_mask. Init pv ipi ops only if the allocation succeeds and
check the cpumask in 'kvm_flush_tlb_others'.

Thanks to Vitaly Kuznetsov's tireless advice.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
v1 -> v2:
 * add CONFIG_SMP for kvm_send_ipi_mask_allbutself to prevent build error
v2 -> v3:
 * always check the allocation of __pv_cpu_mask in kvm_flush_tlb_others
v3 -> v4:
 * mov kvm_setup_pv_ipi to kvm_alloc_cpumask and get rid of kvm_apic_init
v4 -> v5:
 * remove kvm_apic_init as an empty function
 * define pv_ipi_supported() in !CONFIG_SMP case as 'false' to get rid of
 'alloc' variable
 * move kvm_setup_pv_ipi and define the implementation in CONFIG_SMP

 arch/x86/kernel/kvm.c | 75 +++++++++++++++++++++++++------------------
 1 file changed, 44 insertions(+), 31 deletions(-)

```
