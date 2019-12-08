

#### [PATCH 0/6] remove unnecessary return val of kvm pit
##### From: linmiaohe <linmiaohe@huawei.com>
From: Miaohe Lin <linmiaohe@huawei.com>

```c
From patchwork Sat Dec  7 09:25:17 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11277293
Return-Path: <SRS0=f8QL=Z5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4F5614BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Dec 2019 09:26:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8D7FF21835
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Dec 2019 09:26:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726453AbfLGJZq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 7 Dec 2019 04:25:46 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:44760 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726196AbfLGJZp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 7 Dec 2019 04:25:45 -0500
Received: from DGGEMS409-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 2B0D329604AED8DAEFE3;
        Sat,  7 Dec 2019 17:25:42 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS409-HUB.china.huawei.com
 (10.3.19.209) with Microsoft SMTP Server id 14.3.439.0; Sat, 7 Dec 2019
 17:25:32 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH 0/6] remove unnecessary return val of kvm pit
Date: Sat, 7 Dec 2019 17:25:17 +0800
Message-ID: <1575710723-32094-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The return val of kvm pit function is always equal to 0, which means there
is no way to failed with this function. So remove the return val as it's
unnecessary to check against it. Also add BUILD_BUG_ON to guard against
channels size changed unexpectly.

Miaohe Lin (6):
  KVM: x86: remove always equal to 0 return val of
    kvm_vm_ioctl_get_pit()
  KVM: x86: remove always equal to 0 return val of
    kvm_vm_ioctl_set_pit()
  KVM: x86: remove always equal to 0 return val of
    kvm_vm_ioctl_get_pit2()
  KVM: x86: remove always equal to 0 return val of
    kvm_vm_ioctl_set_pit2()
  KVM: x86: check kvm_pit outside kvm_vm_ioctl_reinject()
  KVM: x86: remove always equal to 0 return val of
    kvm_vm_ioctl_reinject()

 arch/x86/kvm/x86.c | 46 +++++++++++++++++++++++-----------------------
 1 file changed, 23 insertions(+), 23 deletions(-)
```
