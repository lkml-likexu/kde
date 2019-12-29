#### [PATCH v2] KVM: nVMX: vmread should not set rflags to specify success in case of #PF
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11311473
Return-Path: <SRS0=Bc0L=2S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A82FE14F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Dec 2019 06:24:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 83C00206E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 28 Dec 2019 06:24:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726165AbfL1GXy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 28 Dec 2019 01:23:54 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:8201 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725942AbfL1GXy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Dec 2019 01:23:54 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 43E9D6F2D5DB2AAD800A;
        Sat, 28 Dec 2019 14:23:51 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.439.0; Sat, 28 Dec 2019
 14:23:41 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <liran.alon@oracle.com>,
        <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <x86@kernel.org>
Subject: [PATCH v2] KVM: nVMX: vmread should not set rflags to specify success
 in case of #PF
Date: Sat, 28 Dec 2019 14:25:24 +0800
Message-ID: <1577514324-18362-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

In case writing to vmread destination operand result in a #PF, vmread
should not call nested_vmx_succeed() to set rflags to specify success.
Similar to as done in VMPTRST (See handle_vmptrst()).

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
v2:
	rephrase commit title & message
---
 arch/x86/kvm/vmx/nested.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
