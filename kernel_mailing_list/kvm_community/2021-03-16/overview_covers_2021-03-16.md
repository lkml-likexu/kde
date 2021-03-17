

#### [kvm-unit-tests PATCH 0/6] s390x: uv: Extend guest test and add host
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Mar 16 09:16:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12141509
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1FA5BC4332B
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 09:20:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D45436500C
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 09:20:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235973AbhCPJUW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 05:20:22 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:50716 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S235954AbhCPJUE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Mar 2021 05:20:04 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12G93vjK125009;
        Tue, 16 Mar 2021 05:20:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=eOw77kQpWiRR6YWM8to7+u1ZLsalzFpmsK4j0hjUOMg=;
 b=iDRaq+EA7EwM5wIGhW0B1ekG4uAARneKJZQ+LCro6DslFSV2oSC2MdzfXSlu3gxvTtIS
 FoZKK1aIbizStNi804ETjHRelIFE9fNbm3GmZuYEnY7bIhfdQ3w44ybGLpQjM6qtHpzk
 yiATsbLLqcerNMFZNRvppcOL+KVniF9oH0GHWhqmSnEERV9h7ZxGGzjhIqGr02oDwYeM
 wC/VmU1c9OlwWdmdSJCFk3ZUnHJPzNw9c+4NBF6qO/aZ02vJGKSZBbhcitTGbyTxTpev
 s4AHJ1uT/EotrmFdJpWknO9KQ5lEE15gL0ixgfLvkuny1VqrGX5zIBdJo7PAL+di+8d5 iw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37arj1je5u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 05:20:03 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12G94O1l127260;
        Tue, 16 Mar 2021 05:20:02 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37arj1je57-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 05:20:02 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12G9CGdd005543;
        Tue, 16 Mar 2021 09:20:01 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 378mnh2pfv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Mar 2021 09:20:00 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12G9JwRh48300508
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Mar 2021 09:19:58 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 90D5E4C044;
        Tue, 16 Mar 2021 09:19:58 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 549904C052;
        Tue, 16 Mar 2021 09:19:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.146.129])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 16 Mar 2021 09:19:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH 0/6] s390x: uv: Extend guest test and add host
 test
Date: Tue, 16 Mar 2021 09:16:48 +0000
Message-Id: <20210316091654.1646-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-16_03:2021-03-15,2021-03-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0
 lowpriorityscore=0 malwarescore=0 mlxlogscore=999 adultscore=0 bulkscore=0
 mlxscore=0 spamscore=0 suspectscore=0 clxscore=1015 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103160063
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My stack of patches is starting to lean, so lets try to put some of
them upstream...

The first part is just additions to the UV guest test and a library
that makes checking the installed UV calls easier. Additionally we now
check for the proper UV share/unshare availability when allocating IO
memory instead of only relying on stfle 158.

The second part adds a UV host test with a large number UV of return
code checks. This is currently a guest 1 test.

Janosch Frank (6):
  s390x: uv-guest: Add invalid share location test
  s390x: Add more Ultravisor command structure definitions
  s390x: uv: Add UV lib
  s390x: Test for share/unshare call support before using them
  s390x: uv-guest: Test invalid commands
  s390x: Add UV host test

 lib/s390x/asm/uv.h    | 152 ++++++++++++-
 lib/s390x/io.c        |   2 +
 lib/s390x/malloc_io.c |   5 +-
 lib/s390x/uv.c        |  48 ++++
 lib/s390x/uv.h        |  10 +
 s390x/Makefile        |   2 +
 s390x/uv-guest.c      |  57 ++++-
 s390x/uv-host.c       | 513 ++++++++++++++++++++++++++++++++++++++++++
 8 files changed, 776 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/uv.c
 create mode 100644 lib/s390x/uv.h
 create mode 100644 s390x/uv-host.c
```
#### [PATCH 00/10] KVM: arm64: Enable SVE support on nVHE systems
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Mar 16 10:13:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12141685
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CFB31C433E6
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 10:14:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D1C664FAC
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 10:14:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236560AbhCPKNu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 06:13:50 -0400
Received: from mail.kernel.org ([198.145.29.99]:56456 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S236564AbhCPKNc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 06:13:32 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id C740D64F91;
        Tue, 16 Mar 2021 10:13:31 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lM6hd-001uep-Iw; Tue, 16 Mar 2021 10:13:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: dave.martin@arm.com, daniel.kiss@arm.com,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        broonie@kernel.org, kernel-team@android.com
Subject: [PATCH 00/10] KVM: arm64: Enable SVE support on nVHE systems
Date: Tue, 16 Mar 2021 10:13:02 +0000
Message-Id: <20210316101312.102925-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 dave.martin@arm.com, daniel.kiss@arm.com, will@kernel.org,
 catalin.marinas@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, broonie@kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables SVE support for KVM on nVHE hardware (or more
likely, software models), and is an alternative to Daniel's patch[1]
which has gone through 3 versions, but still has a number of issues.

Instead of waiting for things to happen, I decided to try and see what
I could come up with.

The SVE save/restore is modelled after the SVE VHE flow, itself
closely following the FPSIMD flow:

- the guest traps to EL2 on first SVE access, and will not trap
  anymore until vcpu_put()

- ZCR_EL2 stays constant as long as the guest has SVE enabled

- on vcpu_put(), ZCR_EL2 is restored to the default value

Most of this series only repaints things so that VHE and nVHE look as
similar as possible, the ZCR_EL2 management being the most visible
exception. This results in a bunch of preparatory patches that aim at
making the code slightly more readable.

This has been tested on a FVP model with both VHE.nVHE configurations
using the string tests included with the "optimized-routines"
library[2].

Patches against 5.12-rc2.

[1] https://lore.kernel.org/r/20210302164850.3553701-1-daniel.kiss@arm.com
[2] https://github.com/ARM-software/optimized-routines

Daniel Kiss (1):
  KVM: arm64: Enable SVE support for nVHE

Marc Zyngier (9):
  KVM: arm64: Provide KVM's own save/restore SVE primitives
  KVM: arm64: Use {read,write}_sysreg_el1 to access ZCR_EL1
  KVM: arm64: Let vcpu_sve_pffr() handle HYP VAs
  KVM: arm64: Introduce vcpu_sve_vq() helper
  KVM: arm64: Rework SVE host-save/guest-restore
  KVM: arm64: Map SVE context at EL2 when available
  KVM: arm64: Save guest's ZCR_EL1 before saving the FPSIMD state
  KVM: arm64: Add a nVHE-specific SVE VQ reset hypercall
  KVM: arm64: Save/restore SVE state for nVHE

 arch/arm64/Kconfig                      |  7 ---
 arch/arm64/include/asm/fpsimdmacros.h   | 10 +++-
 arch/arm64/include/asm/kvm_asm.h        |  1 +
 arch/arm64/include/asm/kvm_host.h       | 25 +++-----
 arch/arm64/include/asm/kvm_hyp.h        |  2 +
 arch/arm64/kvm/arm.c                    |  5 --
 arch/arm64/kvm/fpsimd.c                 | 31 ++++++++--
 arch/arm64/kvm/guest.c                  |  6 +-
 arch/arm64/kvm/hyp/fpsimd.S             | 10 ++++
 arch/arm64/kvm/hyp/include/hyp/switch.h | 78 ++++++++++++-------------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c      |  8 +++
 arch/arm64/kvm/hyp/nvhe/switch.c        |  4 +-
 arch/arm64/kvm/reset.c                  |  4 --
 13 files changed, 107 insertions(+), 84 deletions(-)
```
#### [RFC PATCH v2 0/2] kvm/arm64: Try stage2 block mapping for host
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Tue Mar 16 13:43:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12142237
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9BABBC433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 13:44:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69DA165053
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 13:44:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235408AbhCPNoE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 09:44:04 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:13968 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S235421AbhCPNoA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 09:44:00 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4F0Dwq1PWlzrXLl;
        Tue, 16 Mar 2021 21:42:03 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 16 Mar 2021 21:43:49 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Will Deacon <will@kernel.org>,
        Marc Zyngier <maz@kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 0/2] kvm/arm64: Try stage2 block mapping for host
 device MMIO
Date: Tue, 16 Mar 2021 21:43:36 +0800
Message-ID: <20210316134338.18052-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

We have two pathes to build stage2 mapping for MMIO regions.

Create time's path and stage2 fault path.

Patch#1 removes the creation time's mapping of MMIO regions
Patch#2 tries stage2 block mapping for host device MMIO at fault path

Thanks,
Keqian

Keqian Zhu (2):
  kvm/arm64: Remove the creation time's mapping of MMIO regions
  kvm/arm64: Try stage2 block mapping for host device MMIO

 arch/arm64/kvm/mmu.c | 80 +++++++++++++++++++++++---------------------
 1 file changed, 41 insertions(+), 39 deletions(-)
```
#### [PATCH v2 0/4] KVM: x86: hyper-v: TSC page fixes
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Mar 16 14:37:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12142301
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 837B5C433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 14:38:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CBA86507A
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 14:38:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235641AbhCPOht (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 10:37:49 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33792 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236594AbhCPOhn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Mar 2021 10:37:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615905462;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=sO8wOfaFpww1Pkf9LKzwqACIQFj4+/f0J+OBd7ThLW8=;
        b=bvPnZzN2wHhoD1oCLiPbvPWYj+WHq0f14S4YZihqMItkq/3nTDMwTLaaaBoG5o+j+yTqom
        TTkljd+qv5Z6BYYzse1oyzaLMdgZl1hc6/q+yl3JYgHjQL8ZLzr56wy1wg7Zf8t6Xs2DtW
        RwPXe1DMp1amASyE8MrtF9roTFF8TYc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-538-viAmmKXxOXuLsBsm8aeKJw-1; Tue, 16 Mar 2021 10:37:41 -0400
X-MC-Unique: viAmmKXxOXuLsBsm8aeKJw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 03F738015BD;
        Tue, 16 Mar 2021 14:37:40 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.229])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2B0C65D9DC;
        Tue, 16 Mar 2021 14:37:37 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Marcelo Tosatti <mtosatti@redhat.com>
Subject: [PATCH v2 0/4] KVM: x86: hyper-v: TSC page fixes
Date: Tue, 16 Mar 2021 15:37:32 +0100
Message-Id: <20210316143736.964151-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1:
- Invalidate TSC page from kvm_gen_update_masterclock() instead of calling
 kvm_hv_setup_tsc_page() for all vCPUs [Paolo]
- Set hv->hv_tsc_page_status = HV_TSC_PAGE_UNSET when TSC page is disabled
 with MSR write. Check both HV_TSC_PAGE_BROKEN/HV_TSC_PAGE_UNSET states
 in kvm_hv_setup_tsc_page()/kvm_hv_invalidate_tsc_page().
- Check for HV_TSC_PAGE_SET state instead of '!hv->tsc_ref.tsc_sequence' in
 get_time_ref_counter().

Original description:

I'm investigating an issue when Linux guest on nested Hyper-V on KVM 
(WSL2 on Win10 on KVM to be precise) hangs after L1 KVM is migrated. Trace
shows us that L2 is trying to set L1's Synthetic Timer and reacting to
this Hyper-V sets Synthetic Timer in KVM but the target value it sets is
always slightly in the past, this causes the timer to expire immediately
and an interrupt storm is thus observed. L2 is not making much forward
progress.

The issue is only observed when re-enlightenment is exposed to L1. KVM
doesn't really support re-enlightenment notifications upon migration,
userspace is supposed to expose it only when TSC scaling is supported
on the destination host. Without re-enlightenment exposed, Hyper-V will
not expose stable TSC page clocksource to its L2s. The issue is observed
when migration happens between hosts supporting TSC scaling. Rumor has it
that it is possible to reproduce the problem even when migrating locally
to the same host, though, I wasn't really able to.

The current speculation is that when Hyper-V is migrated, it uses stale
(cached) TSC page values to compute the difference between its own
clocksource (provided by KVM) and its guests' TSC pages to program
synthetic timers and in some cases, when TSC page is updated, this puts all
stimer expirations in the past. This, in its turn, causes an interrupt
storms (both L0-L1 and L1->L2 as Hyper-V mirrors stimer expirations into
L2).

The proposed fix is to skip updating TSC page clocksource when guest opted
for re-enlightenment notifications (PATCH4). Patches 1-3 are slightly
related fixes to the (mostly theoretical) issues I've stumbled upon while
working on the problem.

Vitaly Kuznetsov (4):
  KVM: x86: hyper-v: Limit guest to writing zero to
    HV_X64_MSR_TSC_EMULATION_STATUS
  KVM: x86: hyper-v: Prevent using not-yet-updated TSC page by secondary
    CPUs
  KVM: x86: hyper-v: Track Hyper-V TSC page status
  KVM: x86: hyper-v: Don't touch TSC page values when guest opted for
    re-enlightenment

 arch/x86/include/asm/kvm_host.h | 10 ++++
 arch/x86/kvm/hyperv.c           | 91 +++++++++++++++++++++++++++++----
 arch/x86/kvm/hyperv.h           |  1 +
 arch/x86/kvm/x86.c              |  2 +
 4 files changed, 94 insertions(+), 10 deletions(-)
```
#### [kvm-unit-tests PATCH 0/4] Fix the devicetree parser for stdout-path
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Tue Mar 16 15:24:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12142461
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC91AC433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:25:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 77B40650E1
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:25:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229618AbhCPPYh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 11:24:37 -0400
Received: from foss.arm.com ([217.140.110.172]:46148 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229526AbhCPPYM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 11:24:12 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 0783DD6E;
        Tue, 16 Mar 2021 08:24:12 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 2F3743F792;
        Tue, 16 Mar 2021 08:24:11 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH 0/4] Fix the devicetree parser for stdout-path
Date: Tue, 16 Mar 2021 15:24:01 +0000
Message-Id: <20210316152405.50363-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This set of patches fixes the way we parse the stdout-path which is
used to set up the console. Prior to this, the code ignored the fact
that stdout-path is made of the path to the uart node as well as
parameters and as a result it would fail to find the relevant DT
node. In addition to minor fixes in the device tree code, this series
pulls a new version of libfdt from upstream.

Thanks,

Nikos

Nikos Nikoleris (4):
  lib/string: add strnlen and strrchr
  libfdt: Pull v1.6.0
  Makefile: Avoid double definition of libfdt_clean
  devicetree: Parse correctly the stdout-path

 lib/libfdt/README            |   3 +-
 Makefile                     |  12 +-
 lib/libfdt/Makefile.libfdt   |  10 +-
 lib/libfdt/version.lds       |  24 +-
 lib/libfdt/fdt.h             |  53 +--
 lib/libfdt/libfdt.h          | 766 +++++++++++++++++++++++++-----
 lib/libfdt/libfdt_env.h      | 109 ++---
 lib/libfdt/libfdt_internal.h | 206 +++++---
 lib/string.h                 |   5 +-
 lib/devicetree.c             |  15 +-
 lib/libfdt/fdt.c             | 200 +++++---
 lib/libfdt/fdt_addresses.c   | 101 ++++
 lib/libfdt/fdt_check.c       |  74 +++
 lib/libfdt/fdt_empty_tree.c  |  48 +-
 lib/libfdt/fdt_overlay.c     | 881 +++++++++++++++++++++++++++++++++++
 lib/libfdt/fdt_ro.c          | 512 +++++++++++++++-----
 lib/libfdt/fdt_rw.c          | 231 +++++----
 lib/libfdt/fdt_strerror.c    |  53 +--
 lib/libfdt/fdt_sw.c          | 297 ++++++++----
 lib/libfdt/fdt_wip.c         |  90 ++--
 lib/string.c                 |  30 +-
 21 files changed, 2890 insertions(+), 830 deletions(-)
 create mode 100644 lib/libfdt/fdt_addresses.c
 create mode 100644 lib/libfdt/fdt_check.c
 create mode 100644 lib/libfdt/fdt_overlay.c
```
#### [PATCH 0/3] switch to unsafe_follow_pfn
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Tue Mar 16 15:33:00 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 12142515
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70260C433E9
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:33:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3F8D2650EB
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 15:33:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238127AbhCPPdZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 11:33:25 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36858 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237140AbhCPPdO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 11:33:14 -0400
Received: from mail-wm1-x335.google.com (mail-wm1-x335.google.com
 [IPv6:2a00:1450:4864:20::335])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A9434C06174A
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 08:33:13 -0700 (PDT)
Received: by mail-wm1-x335.google.com with SMTP id
 c76-20020a1c9a4f0000b029010c94499aedso1729235wme.0
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 08:33:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4MtyicSEo1IFZBpiFoiow7kzS1Jr8w9+zJmQTxAoVfE=;
        b=aOBu4s4YBTkov1on28kzZszJKza9hsa6v9IjY9CZuG1RXgyJINqB2YR9wqD8mrJsG5
         oW9CNdk48E00tfQFFqf7eabOXr4V6g1rSZIOZUrY2E9p4jZhOHsIqTc/Zrr2iIrrLpRW
         UO0d+H76OkhNjzww3mqsdcDytyEk8Lp3GsJCc=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4MtyicSEo1IFZBpiFoiow7kzS1Jr8w9+zJmQTxAoVfE=;
        b=POd+NIl6okqbHsmWJfoS+EhSczdJ7mgvVJImhm3e7Jf7JQ9lR9daxbIEqP7s1aM9se
         8/H8PSWwjNrD50rfCihSmowOs8+GuHmTT/v7bOGCl8bmoZr+k5eezS8XFTyFqxZ0BEe4
         KXdAYzpJzIoBTyznP2Npy2Ctxrgmo8R/iagGIrSsnUfM2oYr8WJBJo1eroundvL2DF3h
         DY1AWQIJ+EIl6xjbsvcHkj2hU/naGtxhV74A7yD6BPE24t0DQqCB8GWnn8c1U0d0qm3A
         JG/VlIWwVXUZHq9dsJg393MEm9/bJetNELe3EyHMa7xhc5kiq3Y+rtq+ms/ee3tSnkB9
         eQsQ==
X-Gm-Message-State: AOAM532Ygc4f+BNlYUH+UCux54EqUuO4qikli7dzBE4+AlSbVHwyXHFf
        I6EPscE0k+4QhjANCLA4+Poniw==
X-Google-Smtp-Source: 
 ABdhPJwLcv8LIcwpJj11nT7CjeCYw+rPcm7MmzmWjcj9F/IESEfr8FtSUIk9PgYxtf0usoMMx2lQNw==
X-Received: by 2002:a05:600c:2301:: with SMTP id
 1mr258796wmo.36.1615908792340;
        Tue, 16 Mar 2021 08:33:12 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 h22sm3985078wmb.36.2021.03.16.08.33.11
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 16 Mar 2021 08:33:11 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH 0/3] switch to unsafe_follow_pfn
Date: Tue, 16 Mar 2021 16:33:00 +0100
Message-Id: <20210316153303.3216674-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This are the leftovers from my pull that landed in 5.12:

https://lore.kernel.org/dri-devel/CAKMK7uHQ=6OJcRguCUtiB456RWdCfwSNEXV8pQsfsPodTJ6uxw@mail.gmail.com/

Only changes compared to the old submission are:
- dropped vfio and kvm patch
- add patch to just remove follow_pfn at the end

Assuming no objections I'd like to lande these three patches in my topic
branch for 5.13, for sufficient amounts of testing in linux-next before
the merge window.

Ack/review especially on the two mm patches very much thought after.

Cheers, Daniel

Daniel Vetter (3):
  mm: Add unsafe_follow_pfn
  media/videobuf1|2: Mark follow_pfn usage as unsafe
  mm: unexport follow_pfn

 drivers/media/common/videobuf2/frame_vector.c |  2 +-
 drivers/media/v4l2-core/videobuf-dma-contig.c |  2 +-
 include/linux/mm.h                            |  4 +-
 mm/memory.c                                   | 46 ++++++++++++-------
 mm/nommu.c                                    | 28 ++++++++---
 security/Kconfig                              | 13 ++++++
 6 files changed, 68 insertions(+), 27 deletions(-)
```
#### [PATCH 00/11] KVM: arm64: Initial host support for the Apple M1
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Mar 16 17:46:05 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12143349
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D0703C433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:47:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8EF3665125
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 17:47:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239251AbhCPRqz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 13:46:55 -0400
Received: from mail.kernel.org ([198.145.29.99]:39894 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S239087AbhCPRql (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 13:46:41 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E8DDE65120;
        Tue, 16 Mar 2021 17:46:40 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lMDmA-0021ao-ST; Tue, 16 Mar 2021 17:46:38 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Hector Martin <marcan@marcan.st>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com
Subject: [PATCH 00/11] KVM: arm64: Initial host support for the Apple M1
Date: Tue, 16 Mar 2021 17:46:05 +0000
Message-Id: <20210316174617.173033-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, marcan@marcan.st,
 mark.rutland@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I've spent the past few weekends trying to see how I could support the
M1 as a KVM host. It started by being pretty ugly, but the end result
is actually not too horrible.

Just a wee bit horrible.

The M1 has no GIC. And as everybody know, "KVM" stands for "The GIC
Emulator". Yes, Avi got the TLA wrong. Blame him.

It has no GIC, but it has a *partial* implementation of a vGICv3.
Which is not advertised by the CPU, because you can't have one without
the other. And it is partial because it cannot implement the automatic
HW interrupt deactivation trick (no GIC, remember?). But despite its
flaws, this gives us a fighting chance to expose something standard to
the guests.

"But how will the timers work?", I hear someone asking.

Well, that's a very good question. We rely on the GIC active state and
the HW-based deactivation to make the whole thing work, preventing a
pending timer interrupt from kicking us out of the guest, and
transparently re-enabling the interrupt when the guest EOIs it.

None of that can work on the M1, because (/all together now/) *it
doesn't have a GIC*!

What we can do instead is to fallback to regular masking on guest
entry, and rely on an exit on EOI to unmask the timer. Is that free?
No. Does it work? Yes! The trick is to make this as transparent as
possible to the rest of KVM so that the overhead is squarely on the M1
side. And my (very limited) testing indicates that this overhead is
pretty small.

Note that there is another way to implement the virtual timer: it
appears that this timer can be directly injected thanks to an IMPDEF
mechanism (HACR_EL2[20] + S3_5_15_1_2). It works fine, but:

- it is IMPDEF
- it is massively invasive for the GIC state machine
- it bloats the entry/exit fast path
- it forbids the implementation of GICR_ISPENDR0
- it doesn't work the physical timer
- it is IMPDEF

So scratch that, it doesn't work. I've kept the code for posterity,
but I don't think it is worth it. "Cute Embedded Nonsense Hack", to
quote someone.

This series is on top of Hector's latest drop[1], itself on top of the
FIQ enablement code gathered by Mark[2], plus 5.12-rc3 (which is
needed because this machine lacks an architectural PMU).

You will also need a bleeding edge userspace (qemu[3], kvmtool[4])
that configures the VM with a tiny IPA space (as the HW supports at
most 36 bits while KVM defaults to 40...).

[1] https://lore.kernel.org/r/20210304213902.83903-1-marcan@marcan.st
[2] https://lore.kernel.org/r/20210315115629.57191-1-mark.rutland@arm.com
[3] https://lore.kernel.org/r/20210310135218.255205-1-drjones@redhat.com
[4] https://lore.kernel.org/r/20210309163909.822149-1-maz@kernel.org

Marc Zyngier (11):
  irqchip/gic: Split vGIC probing information from the GIC code
  KVM: arm64: Handle physical FIQ as an IRQ while running a guest
  KVM: arm64: vgic: Be tolerant to the lack of maintenance interrupt
  KVM: arm64: vgic: Let an interrupt controller advertise lack of HW
    deactivation
  KVM: arm64: vgic: move irq->get_input_level into an ops structure
  KVM: arm64: vgic: Implement SW-driven deactivation
  KVM: arm64: timer: Refactor IRQ configuration
  KVM: arm64: timer: Add support for SW-based deactivation
  irqchip/apple-aic: Fix [un]masking of guest timers
  irqchip/apple-aic: Initialise SYS_APL_VM_TMR_FIQ_ENA_EL1 at boot time
  irqchip/apple-aic: Advertise some level of vGICv3 compatibility

 arch/arm64/kvm/arch_timer.c            | 153 ++++++++++++++++++++-----
 arch/arm64/kvm/hyp/hyp-entry.S         |   6 +-
 arch/arm64/kvm/vgic/vgic-init.c        |  33 +++++-
 arch/arm64/kvm/vgic/vgic-v2.c          |  19 ++-
 arch/arm64/kvm/vgic/vgic-v3.c          |  19 ++-
 arch/arm64/kvm/vgic/vgic.c             |  14 +--
 drivers/irqchip/irq-apple-aic.c        |  18 ++-
 drivers/irqchip/irq-gic-common.c       |  13 ---
 drivers/irqchip/irq-gic-common.h       |   2 -
 drivers/irqchip/irq-gic-v3.c           |   6 +-
 drivers/irqchip/irq-gic.c              |   6 +-
 include/kvm/arm_vgic.h                 |  41 +++++--
 include/linux/irqchip/arm-gic-common.h |  25 +---
 include/linux/irqchip/arm-vgic-info.h  |  43 +++++++
 14 files changed, 290 insertions(+), 108 deletions(-)
 create mode 100644 include/linux/irqchip/arm-vgic-info.h
```
#### [PATCH 0/4] KVM: x86: MSR filtering and related fixes
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Mar 16 18:44:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12143493
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6E3FC433E9
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 18:45:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C004D65139
	for <kvm@archiver.kernel.org>; Tue, 16 Mar 2021 18:45:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240082AbhCPSpM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Mar 2021 14:45:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50914 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234505AbhCPSoq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Mar 2021 14:44:46 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 42BCFC061756
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 11:44:46 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id f81so42580147yba.8
        for <kvm@vger.kernel.org>; Tue, 16 Mar 2021 11:44:46 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=B7pVfJtAzkpAW4g2RjA9F8Hx9jH9epVTR8buiCtjOQY=;
        b=IdEsbcouCphArUM6+1+XobihwWZocP60WYNQ4DKS/5AwQbJgTBuKe/m843KN+Hlqum
         rvUGFgkyRm4NIHHBX7VbABhnkub0YGM22LDSHVS0FcLSv7J8PMISZ29743QEgPHIZNCT
         abhSfEW+w43DCWYcO0xgndK0b4cMWBmMyDiOQdkkCyAfH1goeopGZynOl3EHl2Rkpy9p
         wF+/W1aDlhCB0Sn+DGpbQbVKPQJDqxiFvk6X0AB8hCvIHlMPEy8230mFyuEXMyQixJqQ
         7/7D8G2Wj+l4t2uLIenENHfL96u+yxGT/WXpw81B1qTL6WeEyRYmdodvqc7Y4SS6qQf7
         VE5g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=B7pVfJtAzkpAW4g2RjA9F8Hx9jH9epVTR8buiCtjOQY=;
        b=abuOUQllP3tGGhivechZdsTgtPGStY+A04AO9IZIlIsZGC6xwTdLd3dZ/xVFfjM1sJ
         der82pa18pFq4VY5UpF9J9Wy4idQOJamyeNEY1mM3dH90O01U15zfMci+eqG7B7ujZ8r
         QvCaSEuHPT1ZZj+OLZQM5UGeKNdzsyB3DuJ/LM4QmbLS4fzDZ+9uCcCai9RnI9V0gc8S
         DWQRfTk6Bx0hKzm1MX1xMa9xnIQDyq8xm4lFSWJHRrPb+kMHSx4IeMb/tliPuAJ3NU8x
         7fYBHJzYrQZYNXtpLDcU4IoxDtLYxOWQu2gSKu4PEbPA1gJqVNO1Akoz1Zy6Ymb955wP
         3hPw==
X-Gm-Message-State: AOAM533c4+vJXz50qcAmpVjHzn5bA8N3vrjEGu0niuUNU3A8TZ996P3L
        VFP4AJ+xpySfTelzkMAK4wUlmmnsqcs=
X-Google-Smtp-Source: 
 ABdhPJyekYTrFapZGgOnWObiCCFKwGHsizuQQ3hq48wnHVlvZApvgk42WrY4I/0k/TMh9fye+P0QgCtuAgI=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e113:95c2:2d1:e304])
 (user=seanjc job=sendgmr) by 2002:a25:bc41:: with SMTP id
 d1mr322696ybk.125.1615920285519;
 Tue, 16 Mar 2021 11:44:45 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue, 16 Mar 2021 11:44:32 -0700
Message-Id: <20210316184436.2544875-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH 0/4] KVM: x86: MSR filtering and related fixes
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Yuan Yao <yaoyuan0329os@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the MSR filtering implementation to treat a given filter instance
as an atomic unit, and to properly protect it with SRCU.

Fix two nVMX bugs related to MSR filtering (one directly, one indirectly),
and additional cleanup on top.

Regarding the macro insanity in patch 03, I verified the before and after
binary output for vmx_set_intercept_for_msr() was identical (this required
wrapping "if (msr <= 0x1fff)" with (un)likely in both the before and after
versions; gcc made seemingly random choices without forcing it to favor a
specific branch).

Sean Christopherson (4):
  KVM: x86: Protect userspace MSR filter with SRCU, and set
    atomically-ish
  KVM: nVMX: Handle dynamic MSR intercept toggling
  KVM: VMX: Macrofy the MSR bitmap getters and setters
  KVM: nVMX: Clean up x2APIC MSR handling for L2

 Documentation/virt/kvm/api.rst  |   6 +-
 arch/x86/include/asm/kvm_host.h |  17 ++--
 arch/x86/kvm/vmx/nested.c       | 161 +++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.c          |  67 +------------
 arch/x86/kvm/vmx/vmx.h          |  32 +++++++
 arch/x86/kvm/x86.c              | 109 ++++++++++++---------
 6 files changed, 176 insertions(+), 216 deletions(-)
```
