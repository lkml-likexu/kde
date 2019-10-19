#### [PATCH v2 1/3] KVM: VMX: Move vmcs related resetting out of vmx_vcpu_reset()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11198027
Return-Path: <SRS0=/4Fr=YL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F229C112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 18 Oct 2019 09:52:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC31C222BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 18 Oct 2019 09:52:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2633165AbfJRJw1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 18 Oct 2019 05:52:27 -0400
Received: from mga17.intel.com ([192.55.52.151]:35375 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2633158AbfJRJw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Oct 2019 05:52:26 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Oct 2019 02:52:26 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,311,1566889200";
   d="scan'208";a="221689678"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by fmsmga004.fm.intel.com with ESMTP; 18 Oct 2019 02:52:25 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: VMX: Move vmcs related resetting out of
 vmx_vcpu_reset()
Date: Fri, 18 Oct 2019 17:37:21 +0800
Message-Id: <20191018093723.102471-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20191018093723.102471-1-xiaoyao.li@intel.com>
References: <20191018093723.102471-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move vmcs related codes into a new function vmx_vmcs_reset() from
vmx_vcpu_reset(). So that it's more clearer which data is related with
vmcs and can be held in vmcs.

Suggested-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 65 ++++++++++++++++++++++++------------------
 1 file changed, 37 insertions(+), 28 deletions(-)

```
#### [PATCH v2] KVM: SVM: Fix potential wrong physical id in avic_handle_ldr_update
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11197579
Return-Path: <SRS0=/4Fr=YL=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DBC3813B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 18 Oct 2019 06:36:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C6639222C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 18 Oct 2019 06:36:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2504439AbfJRGgK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 18 Oct 2019 02:36:10 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4720 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392014AbfJRGgJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 18 Oct 2019 02:36:09 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 670F2DC43CDADA423205;
        Fri, 18 Oct 2019 10:50:11 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Fri, 18 Oct 2019
 10:50:02 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>,
        <mingfangsen@huawei.com>
Subject: [PATCH v2] KVM: SVM: Fix potential wrong physical id in
 avic_handle_ldr_update
Date: Fri, 18 Oct 2019 10:50:31 +0800
Message-ID: <1571367031-6844-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Guest physical APIC ID may not equal to vcpu->vcpu_id in some case.
We may set the wrong physical id in avic_handle_ldr_update as we
always use vcpu->vcpu_id. Get physical APIC ID from vAPIC page
instead.
Export and use kvm_xapic_id here and in avic_handle_apic_id_update
as suggested by Vitaly.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/lapic.c | 5 -----
 arch/x86/kvm/lapic.h | 5 +++++
 arch/x86/kvm/svm.c   | 6 +++---
 3 files changed, 8 insertions(+), 8 deletions(-)

```
