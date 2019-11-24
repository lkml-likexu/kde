#### [PATCH] KVM: arm: fix missing free_percpu_irq in kvm_timer_hyp_init()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11258715
Return-Path: <SRS0=IFH9=ZP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 851BE6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 Nov 2019 02:31:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 654FA20730
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 23 Nov 2019 02:31:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726666AbfKWCbM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 22 Nov 2019 21:31:12 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:6701 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725962AbfKWCbM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Nov 2019 21:31:12 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 4BE8A966CB0AAB32D4C5;
        Sat, 23 Nov 2019 10:31:09 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS411-HUB.china.huawei.com
 (10.3.19.211) with Microsoft SMTP Server id 14.3.439.0; Sat, 23 Nov 2019
 10:31:03 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>
CC: <linmiaohe@huawei.com>, <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH] KVM: arm: fix missing free_percpu_irq in kvm_timer_hyp_init()
Date: Sat, 23 Nov 2019 10:30:29 +0800
Message-ID: <1574476229-15448-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When host_ptimer_irq request irq resource failed, we forget
to release the host_vtimer_irq resource already requested.
Fix this missing irq release and other similar scenario.

Fixes: 9e01dc76be6a ("KVM: arm/arm64: arch_timer: Assign the phys timer on VHE systems")
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 virt/kvm/arm/arch_timer.c | 17 ++++++++++++-----
 1 file changed, 12 insertions(+), 5 deletions(-)

```
