

#### [PATCH 0/5 v4] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Tue Nov 10 01:23:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11892867
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88F4AC2D0A3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:23:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1ECCC207D3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:23:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="D5Tpu6M2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731645AbgKJBXu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 20:23:50 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:37818 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731581AbgKJBXr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 20:23:47 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1KDRY138928;
        Tue, 10 Nov 2020 01:23:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=u3ugKtb/hD7qDBm+r+haai4+xBCusqnBiUb7VIooum0=;
 b=D5Tpu6M2VphEkHQWxNQ3HNfTL8BvPmGYCy//QKq4MwiSK7NAyG7wHbPHaw+RbtZi02aW
 d2XxgkkPMDIJpdT4PBE8LtQu0pqoNtAgvvhHGIeKPUJhrz4sgQb8STJGCISGl3xNsi28
 /eehGagtlPhzOwx+PDRqmcbOaIqMNq0YSCgciBX/OuGUPMoo7ivzjTK49Gtr8gdSu9Yw
 07TaHpOcuKWD32hbQOCBFy7qgbl4TgQyuWIFM3y3f1EoiQnenXY2uhI0BOkT1GPgEHtT
 +5eLJVYKQaZ1Hk2AxZQWbBSmWtmgDOjMbUvh2fNekT93WpBaIgBZT7MAk4VIoyHG7TYL Kw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 34nh3asa70-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 10 Nov 2020 01:23:33 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1K5A8023810;
        Tue, 10 Nov 2020 01:23:32 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 34p5gw4a00-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Nov 2020 01:23:32 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0AA1NVpG005460;
        Tue, 10 Nov 2020 01:23:31 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 09 Nov 2020 17:23:31 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com, qemu-devel@nongnu.org
Subject: [PATCH 0/5 v4] KVM: x86: Fill in conforming {vmx|svm}_x86_ops and
 {vmx|svm}_nested_ops via macros
Date: Tue, 10 Nov 2020 01:23:07 +0000
Message-Id: <20201110012312.20820-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=621 mlxscore=0
 spamscore=0 phishscore=0 adultscore=0 malwarescore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100008
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 priorityscore=1501
 clxscore=1011 malwarescore=0 mlxscore=0 spamscore=0 suspectscore=1
 mlxlogscore=635 impostorscore=0 phishscore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100008
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3 -> v4:
	1. v3 did not include a few x86_ops and x86_nested_ops in the macro
	   expansion process of function names. This set has covered all those
	   left-out ops.
	2. Patch# 6 from v3 has been dropped as those changes already exist in
	   QEMU source.


[PATCH 1/5 v4] KVM: x86: Change names of some of the kvm_x86_ops
[PATCH 2/5 v4] KVM: SVM: Fill in conforming svm_x86_ops via macro
[PATCH 3/5 v4] KVM: nSVM: Fill in conforming svm_nested_ops via macro
[PATCH 4/5 v4] KVM: VMX: Fill in conforming vmx_x86_ops via macro
[PATCH 5/5 v4] KVM: nVMX: Fill in conforming vmx_nested_ops via macro

 arch/arm64/include/asm/kvm_host.h   |   2 +-
 arch/mips/include/asm/kvm_host.h    |   2 +-
 arch/powerpc/include/asm/kvm_host.h |   2 +-
 arch/s390/kvm/kvm-s390.c            |   2 +-
 arch/x86/include/asm/kvm_host.h     |  16 +-
 arch/x86/kvm/lapic.c                |   2 +-
 arch/x86/kvm/pmu.h                  |   4 +-
 arch/x86/kvm/svm/avic.c             |  11 +-
 arch/x86/kvm/svm/nested.c           |  20 +--
 arch/x86/kvm/svm/pmu.c              |   2 +-
 arch/x86/kvm/svm/sev.c              |   4 +-
 arch/x86/kvm/svm/svm.c              | 296 ++++++++++++++++++++----------------
 arch/x86/kvm/svm/svm.h              |  15 +-
 arch/x86/kvm/vmx/evmcs.c            |   6 +-
 arch/x86/kvm/vmx/evmcs.h            |   4 +-
 arch/x86/kvm/vmx/nested.c           |  39 +++--
 arch/x86/kvm/vmx/pmu_intel.c        |   2 +-
 arch/x86/kvm/vmx/posted_intr.c      |   6 +-
 arch/x86/kvm/vmx/posted_intr.h      |   4 +-
 arch/x86/kvm/vmx/vmx.c              | 262 +++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h              |   4 +-
 arch/x86/kvm/x86.c                  |  41 ++---
 include/linux/kvm_host.h            |   2 +-
 include/uapi/linux/kvm.h            |   6 +-
 tools/include/uapi/linux/kvm.h      |   6 +-
 virt/kvm/kvm_main.c                 |   4 +-
 26 files changed, 405 insertions(+), 359 deletions(-)

Krish Sadhukhan (5):
      KVM: x86: Change names of some of the kvm_x86_ops functions to make them more semantical and readable
      KVM: SVM: Fill in conforming svm_x86_ops via macro
      KVM: nSVM: Fill in conforming svm_nested_ops via macro
      KVM: VMX: Fill in conforming vmx_x86_ops via macro
      KVM: nVMX: Fill in conforming vmx_nested_ops via macro
```
#### [PATCH v2 0/9] KVM: arm64: Kill the copro array
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Nov 10 13:36:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11894337
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 493BBC4742C
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:36:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE65521D40
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="HyF962h6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730939AbgKJNgb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 08:36:31 -0500
Received: from mail.kernel.org ([198.145.29.99]:49048 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729908AbgKJNga (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 08:36:30 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9C630206B6;
        Tue, 10 Nov 2020 13:36:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605015389;
        bh=lkIGiFv1b4/nNPUJbCd5QdY105G4U0sOjAEfhYSdOOg=;
        h=From:To:Cc:Subject:Date:From;
        b=HyF962h6OGyVJupnay/O799NbeCbLjWLLerrcTm01Bq3Ed3G1mELngwKqPdT/rzmi
         7s36TYAhcC7CMPWPKJR4tCOoiwt3fxA5pHxQXUzkKRuTL2bMD6hTInN861ZCJsfwfK
         ym6lKaCPjED6+ITuU66O4anrwC4m6gVRhYb5FrCs=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcTox-009SZy-Cm; Tue, 10 Nov 2020 13:36:27 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 0/9] KVM: arm64: Kill the copro array
Date: Tue, 10 Nov 2020 13:36:10 +0000
Message-Id: <20201110133619.451157-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since the very beginning of KVM/arm64, we represented the system
register file using a dual view: on one side the AArch64 state, on the
other a bizarre mapping of the AArch32 state onto the Aarch64
registers.

It was nice at the time as it allowed us to share some code with the
32bit port, and to come up with some creative bugs. But is was always
a hack, and we are now in a position to simplify the whole thing.

This series goes through the whole of the AArch32 cp14/15 register
file, and point each of them directly at their 64bit equivalent. For
the few cases where two 32bit registers share a 64bit counterpart, we
define which half of the register they map.

Finally, we drop a large number of definitions and state that have
become useless.

This series applies on top of the exception injection rework
previously posted [2].

* From v1 [1]:
  - Added initial patch to deal with TTBCR2
  - Fixed TCR_EL1 handling in inject_abt32()
  - Optimise for 64bit handling of sysreg access
  - Make most 32bit cp14 registers access the full 64bit register

[1] https://lore.kernel.org/r/20201102191609.265711-1-maz@kernel.org
[2] https://lore.kernel.org/r/20201102164045.264512-1-maz@kernel.org

Marc Zyngier (9):
  KVM: arm64: Introduce handling of AArch32 TTBCR2 traps
  KVM: arm64: Move AArch32 exceptions over to AArch64 sysregs
  KVM: arm64: Add AArch32 mapping annotation
  KVM: arm64: Map AArch32 cp15 register to AArch64 sysregs
  KVM: arm64: Map AArch32 cp14 register to AArch64 sysregs
  KVM: arm64: Drop is_32bit trap attribute
  KVM: arm64: Drop is_aarch32 trap attribute
  KVM: arm64: Drop legacy copro shadow register
  KVM: arm64: Drop kvm_coproc.h

 arch/arm64/include/asm/kvm_coproc.h |  38 -----
 arch/arm64/include/asm/kvm_host.h   |  73 +++------
 arch/arm64/kvm/arm.c                |   3 +-
 arch/arm64/kvm/guest.c              |   1 -
 arch/arm64/kvm/handle_exit.c        |   1 -
 arch/arm64/kvm/inject_fault.c       |  62 +++-----
 arch/arm64/kvm/reset.c              |   1 -
 arch/arm64/kvm/sys_regs.c           | 233 +++++++++++++---------------
 arch/arm64/kvm/sys_regs.h           |   9 +-
 arch/arm64/kvm/vgic-sys-reg-v3.c    |   4 -
 10 files changed, 151 insertions(+), 274 deletions(-)
 delete mode 100644 arch/arm64/include/asm/kvm_coproc.h
```
#### [PATCH v2 0/3] KVM: arm64: Another set of CSV2-related fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Nov 10 14:13:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11894413
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3B7E7C55ABD
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:13:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D83EB207D3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:13:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="eevBjJdx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730760AbgKJONP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 09:13:15 -0500
Received: from mail.kernel.org ([198.145.29.99]:34286 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730184AbgKJONP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 09:13:15 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BB782207E8;
        Tue, 10 Nov 2020 14:13:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605017594;
        bh=JIJiOB88U7qGpDmmoxCMenpTc0s/h87h3MJM7Q4ZwqA=;
        h=From:To:Cc:Subject:Date:From;
        b=eevBjJdxE5ATVifFoMcdFwRvrDrdPcf5A4Uq/2knK9AMjrV+rWkfyxDhEH01yIWef
         3klarVSpE4HXbH9ai0o4gTWeHp9jseRMkfwBjO6DSQaRxmLxSG8piSTXfX81nNjkn0
         bj3yquDDsN6Py/6sLS8LytdTTa4yjRyN7GGPZc8U=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcUOW-009T8Q-Da; Tue, 10 Nov 2020 14:13:12 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Peng Liang <liangpeng10@huawei.com>, Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 0/3] KVM: arm64: Another set of CSV2-related fixes
Date: Tue, 10 Nov 2020 14:13:05 +0000
Message-Id: <20201110141308.451654-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
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

This small series addresses a couple of Spectre-v2 related issues:

- Fix a live migration regression introduced with the setting of CSV2
  on systems that are not affected by Spectre-v2, but that don't
  directly expose it in ID_AA64PFR0_EL1

- Inject an UNDEF exception if the guest tries to access any of
  SCXTNUM_ELx, as we don't advertise it to guests.

Patches on top of 5.10-rc2.

* From v1:
  - Only register a new value for CSV2 on a valid write to ID_AA64PFR0_EL1
  - Delete even more code in patch #2

Marc Zyngier (3):
  KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from userspace
  KVM: arm64: Unify trap handlers injecting an UNDEF
  KVM: arm64: Handle SCXTNUM_ELx traps

 arch/arm64/include/asm/kvm_host.h |   2 +
 arch/arm64/include/asm/sysreg.h   |   4 ++
 arch/arm64/kvm/arm.c              |  16 +++++
 arch/arm64/kvm/sys_regs.c         | 111 ++++++++++++++++++------------
 4 files changed, 89 insertions(+), 44 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/2] arm: MMU extentions to enable litmus7
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Tue Nov 10 14:42:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11894467
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E2C6C388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:42:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C29020678
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:42:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731015AbgKJOm3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 09:42:29 -0500
Received: from foss.arm.com ([217.140.110.172]:56816 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730059AbgKJOm2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 09:42:28 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C6EA01063;
        Tue, 10 Nov 2020 06:42:27 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B9A9E3F718;
        Tue, 10 Nov 2020 06:42:26 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/2] arm: MMU extentions to enable litmus7
Date: Tue, 10 Nov 2020 14:42:04 +0000
Message-Id: <20201110144207.90693-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

litmus7 [1][2], a tool that we develop and use to test the memory
model on hardware, is building on kvm-unit-tests to encapsulate full
system tests and control address translation. This series extends the
kvm-unit-tests arm MMU API and adds two memory attributes to MAIR_EL1
to make them available to the litmus tests.

[1]: http://diy.inria.fr/doc/litmus.html
[2]: https://community.arm.com/developer/ip-products/processors/b/processors-ip-blog/posts/expanding-memory-model-tools-system-level-architecture

v1: https://lore.kernel.org/kvm/20201102115311.103750-1-nikos.nikoleris@arm.com/T/

Changes in v2:
  - Add comment on break-before-make in get_mmu_pte()
  - Signed-off-by tag from all co-authors
  - Minor formatting changes

Thanks,

Nikos

Luc Maranget (1):
  arm: Add mmu_get_pte() to the MMU API

Nikos Nikoleris (1):
  arm: Add support for the DEVICE_nGRE and NORMAL_WT memory types

 lib/arm/asm/mmu-api.h         |  1 +
 lib/arm64/asm/pgtable-hwdef.h |  2 ++
 lib/arm/mmu.c                 | 32 +++++++++++++++++++++-----------
 arm/cstart64.S                |  6 +++++-
 4 files changed, 29 insertions(+), 12 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/2] arm: MMU extentions to enable litmus7
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Tue Nov 10 18:09:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11894997
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3627BC388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 18:09:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E831520781
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 18:09:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727968AbgKJSJv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 13:09:51 -0500
Received: from foss.arm.com ([217.140.110.172]:59508 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726152AbgKJSJu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 13:09:50 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 556CF1063;
        Tue, 10 Nov 2020 10:09:50 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 53EEB3F7BB;
        Tue, 10 Nov 2020 10:09:49 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v3 0/2] arm: MMU extentions to enable litmus7
Date: Tue, 10 Nov 2020 18:09:22 +0000
Message-Id: <20201110180924.95106-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

litmus7 [1][2], a tool that we develop and use to test the memory
model on hardware, is building on kvm-unit-tests to encapsulate full
system tests and control address translation. This series extends the
kvm-unit-tests arm MMU API and adds two memory attributes to MAIR_EL1
to make them available to the litmus tests.

[1]: http://diy.inria.fr/doc/litmus.html
[2]: https://community.arm.com/developer/ip-products/processors/b/processors-ip-blog/posts/expanding-memory-model-tools-system-level-architecture

v1: https://lore.kernel.org/kvm/20201102115311.103750-1-nikos.nikoleris@arm.com/T/
v2: https://lore.kernel.org/kvm/20201110144207.90693-1-nikos.nikoleris@arm.com/T/#u

Changes in v3:
  - Moved comment on break-before make

Changes in v2:
  - Add comment on break-before-make in get_mmu_pte()
  - Signed-off-by tag from all co-authors
  - Minor formatting changes

Thanks,

Nikos

Luc Maranget (1):
  arm: Add mmu_get_pte() to the MMU API

Nikos Nikoleris (1):
  arm: Add support for the DEVICE_nGRE and NORMAL_WT memory types

 lib/arm/asm/mmu-api.h         |  1 +
 lib/arm64/asm/pgtable-hwdef.h |  2 ++
 lib/arm/mmu.c                 | 32 +++++++++++++++++++++-----------
 arm/cstart64.S                |  6 +++++-
 4 files changed, 29 insertions(+), 12 deletions(-)
```
#### [PATCH 0/8] KVM: selftests: Cleanups, take 2
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Tue Nov 10 20:47:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11895305
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 24F13C388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 20:48:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D133D20674
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 20:48:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cd4kUI1d"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727851AbgKJUsO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 15:48:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:24032 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725862AbgKJUsN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Nov 2020 15:48:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605041292;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=yD3ERpKzQDHedcF9/ZJkd6ntCshIVv0hhLeGQJV6/wY=;
        b=cd4kUI1dlARe3wIz5VFYmGdsbfLxkGDf71kD+wVY2eOnhVEEDN8Uh5nA7fYomMvSAVD1Rb
        73wXUygxn5Cei38INtQ2R61gIXoE3WDbY0cdfqaHnt+CWogmNc1EHLjcsOa+R9/oAmOWV8
        yfupPSVXIicujgLejeC8rgQxNZftM4U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-248-JNHkX94HMd-txTqm1rwpxA-1; Tue, 10 Nov 2020 15:48:10 -0500
X-MC-Unique: JNHkX94HMd-txTqm1rwpxA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A73CA87951F;
        Tue, 10 Nov 2020 20:48:09 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.179])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6B82910016DA;
        Tue, 10 Nov 2020 20:48:04 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH 0/8] KVM: selftests: Cleanups, take 2
Date: Tue, 10 Nov 2020 21:47:54 +0100
Message-Id: <20201110204802.417521-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up demand_paging_test, dirty_log_perf_test,
and dirty_log_test by factoring out common code, creating some new API
along the way.  It also splits include/perf_test_util.h into a more
conventional header and source pair. There's still some stuff I don't
like, for example the unbalanced ucall_uninit we now get for tests using
the perf_test API, but I'll maybe revisit that stuff again some other day.

I've tested on x86 and AArch64 (one config each), but not s390x.

Thanks,
drew


Andrew Jones (8):
  KVM: selftests: Update .gitignore
  KVM: selftests: Remove deadcode
  KVM: selftests: Factor out guest mode code
  KVM: selftests: Make vm_create_default common
  KVM: selftests: Introduce vm_create_[default_]_with_vcpus
  KVM: selftests: dirty_log_test: Remove create_vm
  KVM: selftests: Use vm_create_with_vcpus in create_vm
  KVM: selftests: Implement perf_test_util more conventionally

 tools/testing/selftests/kvm/.gitignore        |   2 +-
 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/demand_paging_test.c        | 115 +++--------
 .../selftests/kvm/dirty_log_perf_test.c       | 174 ++++-------------
 tools/testing/selftests/kvm/dirty_log_test.c  | 179 +++++-------------
 .../selftests/kvm/include/guest_modes.h       |  21 ++
 .../testing/selftests/kvm/include/kvm_util.h  |  42 +++-
 .../selftests/kvm/include/perf_test_util.h    | 170 +----------------
 .../selftests/kvm/lib/aarch64/processor.c     |  17 --
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 +++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  60 +++++-
 .../selftests/kvm/lib/perf_test_util.c        | 134 +++++++++++++
 .../selftests/kvm/lib/s390x/processor.c       |  22 ---
 .../selftests/kvm/lib/x86_64/processor.c      |  32 ----
 14 files changed, 451 insertions(+), 589 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c
 create mode 100644 tools/testing/selftests/kvm/lib/perf_test_util.c
```
