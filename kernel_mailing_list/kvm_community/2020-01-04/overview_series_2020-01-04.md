#### [PATCH v2] KVM: SVM: Fix potential memory leak in svm_cpu_init()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11317587
Return-Path: <SRS0=32Vo=2Z=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD49B138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jan 2020 08:55:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8BCB9215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  4 Jan 2020 08:55:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726281AbgADIz2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 4 Jan 2020 03:55:28 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8677 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726078AbgADIz1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 4 Jan 2020 03:55:27 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 69F646AE1C445E4BB968;
        Sat,  4 Jan 2020 16:55:25 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS409-HUB.china.huawei.com
 (10.3.19.209) with Microsoft SMTP Server id 14.3.439.0; Sat, 4 Jan 2020
 16:55:14 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>,
        <liran.alon@oracle.com>
Subject: [PATCH v2] KVM: SVM: Fix potential memory leak in svm_cpu_init()
Date: Sat, 4 Jan 2020 16:56:49 +0800
Message-ID: <1578128209-12891-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When kmalloc memory for sd->sev_vmcbs failed, we forget to free the page
held by sd->save_area. Also get rid of the var r as '-ENOMEM' is actually
the only possible outcome here.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
-v2:
	drop var r as suggested by Vitaly
---
 arch/x86/kvm/svm.c | 13 ++++++-------
 1 file changed, 6 insertions(+), 7 deletions(-)

```
