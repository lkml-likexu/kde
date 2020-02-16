#### [PATCH] KVM: x86: Fix print format and coding style
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11383707
Return-Path: <SRS0=g/6+=4D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD46813A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 15 Feb 2020 02:43:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD333206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 15 Feb 2020 02:43:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727705AbgBOCnE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 14 Feb 2020 21:43:04 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:50706 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727416AbgBOCnE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 14 Feb 2020 21:43:04 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 836E95F4E3E86090DA44;
        Sat, 15 Feb 2020 10:43:00 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.439.0; Sat, 15 Feb 2020
 10:42:54 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: Fix print format and coding style
Date: Sat, 15 Feb 2020 10:44:22 +0800
Message-ID: <1581734662-970-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Use %u to print u32 var and correct some coding style.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/i8254.c      | 2 +-
 arch/x86/kvm/mmu/mmu.c    | 3 +--
 arch/x86/kvm/vmx/nested.c | 2 +-
 3 files changed, 3 insertions(+), 4 deletions(-)

```
