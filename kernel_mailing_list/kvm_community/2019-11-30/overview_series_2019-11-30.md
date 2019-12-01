#### [PATCH v3] KVM: vgic: Use wrapper function to lock/unlock all vcpus in kvm_vgic_create()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11267823
Return-Path: <SRS0=cxnS=ZW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDAE7109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 30 Nov 2019 02:46:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D33D5217BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 30 Nov 2019 02:46:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727198AbfK3Cp3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 29 Nov 2019 21:45:29 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:50510 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727177AbfK3Cp2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 29 Nov 2019 21:45:28 -0500
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 96812B9628629FE8062D;
        Sat, 30 Nov 2019 10:45:25 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.439.0; Sat, 30 Nov 2019
 10:45:17 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <maz@kernel.org>, <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <suzuki.poulose@arm.com>, <christoffer.dall@arm.com>,
        <catalin.marinas@arm.com>, <eric.auger@redhat.com>,
        <gregkh@linuxfoundation.org>, <will@kernel.org>,
        <andre.przywara@arm.com>, <tglx@linutronix.de>
CC: <steven.price@arm.com>, <linmiaohe@huawei.com>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v3] KVM: vgic: Use wrapper function to lock/unlock all vcpus
 in kvm_vgic_create()
Date: Sat, 30 Nov 2019 10:45:18 +0800
Message-ID: <1575081918-11401-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Use wrapper function lock_all_vcpus()/unlock_all_vcpus()
in kvm_vgic_create() to remove duplicated code dealing
with locking and unlocking all vcpus in a vm.

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Steven Price <steven.price@arm.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
-v2:
	Fix some spelling mistake in patch title and commit log.
-v3:
	Remove the comment that no longer makes sense.
---
 virt/kvm/arm/vgic/vgic-init.c | 19 ++++---------------
 1 file changed, 4 insertions(+), 15 deletions(-)

```
