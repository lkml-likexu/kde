

#### [PATCH kvm-unit-tests 0/8]: x86: vmx: Test INIT processing in various
##### From: Liran Alon <liran.alon@oracle.com>

```c
From patchwork Thu Sep 19 12:52:03 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11152293
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 554EB13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 12:52:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 34A5C21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 12:52:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="FPCOUs+z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389554AbfISMwu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 08:52:50 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:46420 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389212AbfISMwu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 08:52:50 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8JCnVKU151063;
        Thu, 19 Sep 2019 12:52:27 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=Yy1xBvxcpFEBS2osp67zPm6WU06C8m2M9p0BlIWsEbA=;
 b=FPCOUs+zlcmEvQlZJGR+nO8irbP43kNfAJMmGOmlU769H1d/cNrALPZuso+DdEqGqRKb
 t8DowOGy1sPIQi/GNV4azc2PKeDDuifENLgdM/BAOEwQABq6wazxMhM5/oey63R2K4kK
 eVfGi74AEYxoYp8tDwAhvhonIZheSl4h66gQCUrH5gtmMr9M5EVe6/IJEPJu45dPrYHW
 7aSYk33O9MC6rR4rHT/8nzpaM3idRNle7eC+wCjBFQTlixsw+Y6271CsXfmj4U2rknW5
 Nw97G+pBVoLfVFt2iSq9yaQ6Sf+Ee5OvI/cFB6t7MDy+IGvxSvyxtcxPBUDmE94x+fEi NQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2v3vb4kpt9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 19 Sep 2019 12:52:27 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8JCmC2N178710;
        Thu, 19 Sep 2019 12:52:27 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 2v3vbs1kbq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 19 Sep 2019 12:52:27 +0000
Received: from abhmp0011.oracle.com (abhmp0011.oracle.com [141.146.116.17])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x8JCqQGv012161;
        Thu, 19 Sep 2019 12:52:26 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 19 Sep 2019 05:52:26 -0700
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com
Subject: [PATCH kvm-unit-tests 0/8]: x86: vmx: Test INIT processing in various
 CPU VMX states
Date: Thu, 19 Sep 2019 15:52:03 +0300
Message-Id: <20190919125211.18152-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9384
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=882
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1909190121
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9384
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=961 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1909190121
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch series aims to add a vmx test to verify the functionality
introduced by KVM commit:
4b9852f4f389 ("KVM: x86: Fix INIT signal handling in various CPU states")

The test verifies the following functionality:
1) An INIT signal received when CPU is in VMX operation
  is latched until it exits VMX operation.
2) If there is an INIT signal pending when CPU is in
  VMX non-root mode, it result in VMExit with (reason == 3).
3) Exit from VMX non-root mode on VMExit do not clear
  pending INIT signal in LAPIC.
4) When CPU exits VMX operation, pending INIT signal in
  LAPIC is processed.

In order to write such a complex test, the vmx tests framework was
enhanced to support using VMX in non BSP CPUs. This enhancement is
implemented in patches 1-7. The test itself is implemented at patch 8.
This enhancement to the vmx tests framework is a bit hackish, but
I believe it's OK because this functionality is rarely required by
other VMX tests.

Regards,
-Liran
Tested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
```
#### [RFC patch 00/15] entry: Provide generic implementation for host and
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Thu Sep 19 15:03:14 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11152799
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 03F981747
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 15:11:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D11C921A49
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 15:11:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389620AbfISPLQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 11:11:16 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:50049 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728720AbfISPJu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 11:09:50 -0400
Received: from localhost ([127.0.0.1] helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1iAy3w-0006n0-31; Thu, 19 Sep 2019 17:09:40 +0200
Message-Id: <20190919150314.054351477@linutronix.de>
User-Agent: quilt/0.65
Date: Thu, 19 Sep 2019 17:03:14 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Andy Lutomirski <luto@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org
Subject: [RFC patch 00/15] entry: Provide generic implementation for host and
 guest entry/exit work
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When working on a way to move out the posix cpu timer expiry out of the
timer interrupt context, I noticed that KVM is not handling pending task
work before entering a guest. A quick hack was to add that to the x86 KVM
handling loop. The discussion ended with a request to make this a generic
infrastructure possible with also moving the per arch implementations of
the enter from and return to user space handling generic.

  https://lore.kernel.org/r/89E42BCC-47A8-458B-B06A-D6A20D20512C@amacapital.net

You asked for it, so don't complain that you have to review it :)

The series implements the syscall enter/exit and the general exit to
userspace work handling along with the pre guest enter functionality.

The series converts x86 and ARM64. x86 is fully tested including selftests
etc. ARM64 is only compile tested for now as my only ARM64 testbox is not
available right now.

Thanks,

	tglx
---
 /Makefile                               |    3 
 arch/Kconfig                            |    3 
 arch/arm64/Kconfig                      |    1 
 arch/arm64/include/asm/kvm_host.h       |    1 
 arch/arm64/kernel/entry.S               |   18 -
 arch/arm64/kernel/ptrace.c              |   65 ------
 arch/arm64/kernel/signal.c              |   45 ----
 arch/arm64/kernel/syscall.c             |   49 ----
 arch/x86/Kconfig                        |    1 
 arch/x86/entry/common.c                 |  265 +-------------------------
 arch/x86/entry/entry_32.S               |   13 -
 arch/x86/entry/entry_64.S               |   12 -
 arch/x86/entry/entry_64_compat.S        |   21 --
 arch/x86/include/asm/signal.h           |    1 
 arch/x86/include/asm/thread_info.h      |    9 
 arch/x86/kernel/signal.c                |    2 
 arch/x86/kvm/x86.c                      |   17 -
 b/arch/arm64/include/asm/entry-common.h |   76 +++++++
 b/arch/x86/include/asm/entry-common.h   |  104 ++++++++++
 b/include/linux/entry-common.h          |  324 ++++++++++++++++++++++++++++++++
 b/kernel/entry/common.c                 |  220 +++++++++++++++++++++
 kernel/Makefile                         |    1 
 22 files changed, 776 insertions(+), 475 deletions(-)
```
