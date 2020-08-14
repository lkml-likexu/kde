

#### [RFC 0/4] kvm: arm64: emulate ID registers
##### From: Peng Liang <liangpeng10@huawei.com>

```c
From patchwork Thu Aug 13 06:05:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11711693
Return-Path: <SRS0=IfgN=BX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28DED722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 06:14:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1569120656
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Aug 2020 06:14:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726081AbgHMGOM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Aug 2020 02:14:12 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:40222 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725954AbgHMGOM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Aug 2020 02:14:12 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 544B24AC5B9D6D66A30A;
        Thu, 13 Aug 2020 14:14:09 +0800 (CST)
Received: from localhost.localdomain (10.175.104.175) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Thu, 13 Aug 2020 14:14:00 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <zhang.zhanghailiang@huawei.com>, <xiexiangyou@huawei.com>,
        Peng Liang <liangpeng10@huawei.com>
Subject: [RFC 0/4] kvm: arm64: emulate ID registers
Date: Thu, 13 Aug 2020 14:05:13 +0800
Message-ID: <20200813060517.2360048-1-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.18.4
MIME-Version: 1.0
X-Originating-IP: [10.175.104.175]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In AArch64, guest will read the same values of the ID regsiters with
host.  Both of them read the values from arm64_ftr_regs.  This patch
series add support to emulate and configure ID registers so that we can
control the value of ID registers that guest read.

Peng Liang (4):
  arm64: add a helper function to traverse arm64_ftr_regs
  kvm: arm64: emulate the ID registers
  kvm: arm64: make ID registers configurable
  kvm: arm64: add KVM_CAP_ARM_CPU_FEATURE extension

 arch/arm64/include/asm/cpufeature.h |  2 ++
 arch/arm64/include/asm/kvm_host.h   |  2 ++
 arch/arm64/kernel/cpufeature.c      | 13 ++++++++
 arch/arm64/kvm/arm.c                | 21 ++++++++++++
 arch/arm64/kvm/sys_regs.c           | 50 ++++++++++++++++++++++-------
 include/uapi/linux/kvm.h            | 12 +++++++
 6 files changed, 89 insertions(+), 11 deletions(-)
```
