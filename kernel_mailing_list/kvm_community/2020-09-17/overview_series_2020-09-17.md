#### [PATCH 1/2] KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
##### From: Ying Fang <fangying1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ying Fang <fangying1@huawei.com>
X-Patchwork-Id: 11781305
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3627414F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:47:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1DF782075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:47:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726098AbgIQCq6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 22:46:58 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:60194 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726044AbgIQCqz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 22:46:55 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id B355FE72A94ED350DBC9;
        Thu, 17 Sep 2020 10:31:01 +0800 (CST)
Received: from localhost (10.174.185.104) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.487.0; Thu, 17 Sep 2020
 10:30:53 +0800
From: Ying Fang <fangying1@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <maz@kernel.org>
CC: <drjones@redhat.com>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <suzuki.poulose@arm.com>,
        <zhang.zhanghailiang@huawei.com>, <alex.chen@huawei.com>,
        Ying Fang <fangying1@huawei.com>
Subject: [PATCH 1/2] KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
Date: Thu, 17 Sep 2020 10:30:32 +0800
Message-ID: <20200917023033.1337-2-fangying1@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
In-Reply-To: <20200917023033.1337-1-fangying1@huawei.com>
References: <20200917023033.1337-1-fangying1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.185.104]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add KVM_CAP_ARM_MP_AFFINITY extension for userspace to check
whether KVM supports setting MPIDR on AArch64 platform. Thus
we can give userspace control over the MPIDR to present
cpu topology information.

Signed-off-by: Ying Fang <fangying1@huawei.com>
---
 Documentation/virt/kvm/api.rst | 8 ++++++++
 arch/arm64/kvm/arm.c           | 1 +
 include/uapi/linux/kvm.h       | 1 +
 3 files changed, 10 insertions(+)

```
#### [PATCH 1/2] vfio/pci: Remove redundant declaration of vfio_pci_driver
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11781427
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1ECA9618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:47:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 047552076C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:47:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726072AbgIQDr0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 23:47:26 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:12771 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726007AbgIQDrZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 23:47:25 -0400
X-Greylist: delayed 913 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 16 Sep 2020 23:47:24 EDT
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id B9C8432ED3D7CC57E10C;
        Thu, 17 Sep 2020 11:32:08 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.226) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.487.0; Thu, 17 Sep 2020 11:32:02 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <wanghaibin.wang@huawei.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH 1/2] vfio/pci: Remove redundant declaration of vfio_pci_driver
Date: Thu, 17 Sep 2020 11:31:27 +0800
Message-ID: <20200917033128.872-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.226]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was added by commit 137e5531351d ("vfio/pci: Add sriov_configure
support") and actually unnecessary. Remove it.

Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c | 1 -
 1 file changed, 1 deletion(-)

```
#### 
##### 

```c
```
#### [RFC PATCH 1/2] KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
##### From: Ying Fang <fangying1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ying Fang <fangying1@huawei.com>
X-Patchwork-Id: 11781315
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9BFF8112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:01:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 81A542075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 03:01:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726109AbgIQDBT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 23:01:19 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:12809 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725987AbgIQDBJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 23:01:09 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id D2AF9D77EE02DDBB6937;
        Thu, 17 Sep 2020 11:01:06 +0800 (CST)
Received: from localhost (10.174.185.104) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.487.0; Thu, 17 Sep 2020
 11:00:59 +0800
From: Ying Fang <fangying1@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <drjones@redhat.com>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <suzuki.poulose@arm.com>,
        <zhang.zhanghailiang@huawei.com>, <alex.chen@huawei.com>,
        Ying Fang <fangying1@huawei.com>
Subject: [RFC PATCH 1/2] KVM: arm64: add KVM_CAP_ARM_MP_AFFINITY extension
Date: Thu, 17 Sep 2020 11:00:52 +0800
Message-ID: <20200917030053.1747-2-fangying1@huawei.com>
X-Mailer: git-send-email 2.26.0.windows.1
In-Reply-To: <20200917030053.1747-1-fangying1@huawei.com>
References: <20200917030053.1747-1-fangying1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.185.104]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add KVM_CAP_ARM_MP_AFFINITY extension for userspace to check
whether KVM supports setting MPIDR on AArch64 platform. Thus
we can give userspace control over the MPIDR to present
cpu topology information.

Signed-off-by: Ying Fang <fangying1@huawei.com>
---
 Documentation/virt/kvm/api.rst | 8 ++++++++
 arch/arm64/kvm/arm.c           | 1 +
 include/uapi/linux/kvm.h       | 1 +
 3 files changed, 10 insertions(+)

```
#### [RFC v2 1/7] arm64: add a helper function to traverse arm64_ftr_regs
##### From: Peng Liang <liangpeng10@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peng Liang <liangpeng10@huawei.com>
X-Patchwork-Id: 11782361
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BD8D746
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 12:11:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 67D9D2087D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 12:11:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727014AbgIQMKf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 08:10:35 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:56542 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726845AbgIQMJl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Sep 2020 08:09:41 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 7D36B8D2574DD75760F7;
        Thu, 17 Sep 2020 20:09:29 +0800 (CST)
Received: from localhost.localdomain (10.175.104.175) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.487.0; Thu, 17 Sep 2020 20:09:22 +0800
From: Peng Liang <liangpeng10@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>
CC: <kvm@vger.kernel.org>, <maz@kernel.org>, <will@kernel.org>,
        <drjones@redhat.com>, <zhang.zhanghailiang@huawei.com>,
        <xiexiangyou@huawei.com>, Peng Liang <liangpeng10@huawei.com>
Subject: [RFC v2 1/7] arm64: add a helper function to traverse arm64_ftr_regs
Date: Thu, 17 Sep 2020 20:00:55 +0800
Message-ID: <20200917120101.3438389-2-liangpeng10@huawei.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200917120101.3438389-1-liangpeng10@huawei.com>
References: <20200917120101.3438389-1-liangpeng10@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.175.104.175]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we want to emulate ID registers, we need to initialize ID registers
firstly.  This commit is to add a helper function to traverse
arm64_ftr_regs so that we can initialize ID registers from
arm64_ftr_regs.

Signed-off-by: zhanghailiang <zhang.zhanghailiang@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/cpufeature.h |  2 ++
 arch/arm64/kernel/cpufeature.c      | 13 +++++++++++++
 2 files changed, 15 insertions(+)

```
#### [PATCH 1/1] KVM: x86: fix MSR_IA32_TSC read for nested migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11782267
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 93CF2112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 11:08:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A2522075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 11:08:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fPwK+M3z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726699AbgIQLIW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 07:08:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:29847 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726657AbgIQLH4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 07:07:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600340858;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=6jPa4Eca2QJFB9z/ho9ZCcjVgGtPPG1+kl3a+IvmFXI=;
        b=fPwK+M3z16gEQ24nJxtTsh2kU9gl8Oj/Ok8N6HMxOpPkqPpEGBpePA/kmRowrRIPgacKPJ
        +e4VLaThKoznD/0eEU6Vic4lSw/xjPG8UPThplBGJjk6l2xFhxgdLQLPaZhOVhAtnH+pU8
        TcxFaHq7XoWglv0fiP6EjobfpNRJnFU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-126-eyXnH01vO8ug49cAiWT_Bw-1; Thu, 17 Sep 2020 07:07:35 -0400
X-MC-Unique: eyXnH01vO8ug49cAiWT_Bw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4D08888EF01;
        Thu, 17 Sep 2020 11:07:33 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.187])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B233275142;
        Thu, 17 Sep 2020 11:07:29 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/1] KVM: x86: fix MSR_IA32_TSC read for nested migration
Date: Thu, 17 Sep 2020 14:07:23 +0300
Message-Id: <20200917110723.820666-2-mlevitsk@redhat.com>
In-Reply-To: <20200917110723.820666-1-mlevitsk@redhat.com>
References: <20200917110723.820666-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSR reads/writes should always access the L1 state, since the (nested)
hypervisor should intercept all the msrs it wants to adjust, and these
that it doesn't should be read by the guest as if the host had read it.

However IA32_TSC is an exception.Even when not intercepted, guest still
reads the value + TSC offset.
The write however does not take any TSC offset in the account.

This is documented in Intel's PRM and seems also to happen on AMD as well.

This creates a problem when userspace wants to read the IA32_TSC value and then
write it. (e.g for migration)

In this case it reads L2 value but write is interpreted as an L1 value.
To fix this make the userspace initiated reads of IA32_TSC return L1 value
as well.

Huge thanks to Dave Gilbert for helping me understand this very confusing
semantic of MSR writes.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH v4 1/2] KVM: add request KVM_REQ_OUT_OF_MEMORY
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11782131
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 96D5F59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 10:11:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 79ED121734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 10:11:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fxtebcD0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726557AbgIQKLP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 06:11:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:51920 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726598AbgIQKLD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 06:11:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600337461;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=sYHG4V6fy3u/g4UVdawRvlE3KZPiniHhZvdOnhelAps=;
        b=fxtebcD0wcUeBa/m8l1S3NCyfsy9sqBL1SzJ4QNIvEEKPNYdmherbpYXZhTkWFIG/pcr4h
        O/vt4rl5+pjTXevR4JXPlHIvVmpeJE8AsEfaLcf1R83v3yyC4J8waf0b3Py7oyo4BjPJh6
        n2i3rRTF/MQOJiv0VJacEbeNPX6RAzo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-108-yqSV6GPdOoWRQpRVufXO1Q-1; Thu, 17 Sep 2020 06:10:59 -0400
X-MC-Unique: yqSV6GPdOoWRQpRVufXO1Q-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4937F801AAB;
        Thu, 17 Sep 2020 10:10:58 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.187])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A4218101416F;
        Thu, 17 Sep 2020 10:10:54 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v4 1/2] KVM: add request KVM_REQ_OUT_OF_MEMORY
Date: Thu, 17 Sep 2020 13:10:47 +0300
Message-Id: <20200917101048.739691-2-mlevitsk@redhat.com>
In-Reply-To: <20200917101048.739691-1-mlevitsk@redhat.com>
References: <20200917101048.739691-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This request will be used in rare cases when emulation can't continue
due to being out of memory, to kill the current VM.

Currently only implemented for x86.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c       | 7 +++++++
 include/linux/kvm_host.h | 1 +
 2 files changed, 8 insertions(+)

```
#### [PATCH] KVM: SVM: Use a separate vmcb for the nested L2 guest
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11783471
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0441292C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 19:56:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7B4220725
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 19:56:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i9MI+ZgI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726859AbgIQT4e (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 15:56:34 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:26899 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726462AbgIQT4d (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 15:56:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600372588;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Ut7O3NkEwWpBwXOX1pTP8+dkrob9NfEBaRfr5cqbjfc=;
        b=i9MI+ZgIZcf7+iXUV5HLverbN25ccx5knxL967sZw/dk/Wq6jr/OfzcgTGE7PfkpRBLQS2
        QEYJj3QDRsML2ApiVqDSJAj/IJ4c2fyUoPloJhcH2I28flfB6Gdzd3BJl7tnpnouqZBtxQ
        +Qldokdov6H7VE6518OC+sGel2h7Ax8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-JPZS6PKDPey4lqM2hVHZ3A-1; Thu, 17 Sep 2020 15:23:10 -0400
X-MC-Unique: JPZS6PKDPey4lqM2hVHZ3A-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C94E818C89EF;
        Thu, 17 Sep 2020 19:23:07 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0EF495DA30;
        Thu, 17 Sep 2020 19:23:06 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH] KVM: SVM: Use a separate vmcb for the nested L2 guest
Date: Thu, 17 Sep 2020 15:23:06 -0400
Message-Id: <20200917192306.2080-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

svm->vmcb will now point to either a separate vmcb L1 ( not nested ) or L2 vmcb ( nested ).

Issues:

1) There is some wholesale copying of vmcb.save and vmcb.contol
   areas which will need to be refined.

2) There is a workaround in nested_svm_vmexit() where

   if (svm->vmcb01->control.asid == 0)
       svm->vmcb01->control.asid = svm->nested.vmcb02->control.asid;

   This was done as a result of the kvm selftest 'state_test'. In that
   test svm_set_nested_state() is called before svm_vcpu_run().
   The asid is assigned by svm_vcpu_run -> pre_svm_run for the current
   vmcb which is now vmcb02 as we are in nested mode subsequently
   vmcb01.control.asid is never set as it should be.

Tested:
kvm-unit-tests
kvm self tests

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 116 ++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.c    |  41 +++++++-------
 arch/x86/kvm/svm/svm.h    |  10 ++--
 3 files changed, 81 insertions(+), 86 deletions(-)

```
#### [PATCH RFC] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
##### From: yadong.qi@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Qi, Yadong" <yadong.qi@intel.com>
X-Patchwork-Id: 11781275
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1105E59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:32:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F22BC20715
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 02:32:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726134AbgIQCcW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Sep 2020 22:32:22 -0400
Received: from mga07.intel.com ([134.134.136.100]:27316 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726115AbgIQCcW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Sep 2020 22:32:22 -0400
X-Greylist: delayed 428 seconds by postgrey-1.27 at vger.kernel.org;
 Wed, 16 Sep 2020 22:32:21 EDT
IronPort-SDR: 
 DoQgVxg+pNPNCyhdfJXCdCnRlpNVgAW0mbZ4f7KYNxwpZC1+M6K7RMCB7U5j9bL3HnmwecFLLT
 Ylvz5x2Hibpg==
X-IronPort-AV: E=McAfee;i="6000,8403,9746"; a="223791703"
X-IronPort-AV: E=Sophos;i="5.76,434,1592895600";
   d="scan'208";a="223791703"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Sep 2020 19:25:12 -0700
IronPort-SDR: 
 uDz+ipUyDkh+CGmXVhJDknh9smuAUgciSMODoMrBIV48iO92bFx3mHpPjHtumLb4Ioujt/SxTz
 NXLcOEsJBmZQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,434,1592895600";
   d="scan'208";a="339287186"
Received: from yadong-antec.sh.intel.com ([10.239.158.61])
  by fmsmga002.fm.intel.com with ESMTP; 16 Sep 2020 19:25:08 -0700
From: yadong.qi@intel.com
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, liran.alon@oracle.com,
        nikita.leshchenko@oracle.com, chao.gao@intel.com,
        kevin.tian@intel.com, luhai.chen@intel.com, bing.zhu@intel.com,
        kai.z.wang@intel.com, yadong.qi@intel.com
Subject: [PATCH RFC] KVM: x86: emulate wait-for-SIPI and SIPI-VMExit
Date: Thu, 17 Sep 2020 10:25:01 +0800
Message-Id: <20200917022501.369121-1-yadong.qi@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yadong Qi <yadong.qi@intel.com>

Background: We have a lightweight HV, it needs INIT-VMExit and
SIPI-VMExit to wake-up APs for guests since it do not monitoring
the Local APIC. But currently virtual wait-for-SIPI(WFS) state
is not supported in KVM, so when running on top of KVM, the L1
HV cannot receive the INIT-VMExit and SIPI-VMExit which cause
the L2 guest cannot wake up the APs.

This patch is incomplete, it emulated wait-for-SIPI state by halt
the vCPU and emulated SIPI-VMExit to L1 when trapped SIPI signal
from L2. I am posting it RFC to gauge whether or not upstream
KVM is interested in emulating wait-for-SIPI state before
investing the time to finish the full support.

According to Intel SDM Chapter 25.2 Other Causes of VM Exits,
SIPIs cause VM exits when a logical processor is in
wait-for-SIPI state.

In this patch:
    1. introduce SIPI exit reason,
    2. introduce wait-for-SIPI state for nVMX,
    3. advertise wait-for-SIPI support to guest.

When L1 hypervisor is not monitoring Local APIC, L0 need to emulate
INIT-VMExit and SIPI-VMExit to L1 to emulate INIT-SIPI-SIPI for
L2. L2 LAPIC write would be traped by L0 Hypervisor(KVM), L0 should
emulate the INIT/SIPI vmexit to L1 hypervisor to set proper state
for L2's vcpu state.

Handle procdure:
Source vCPU:
    L2 write LAPIC.ICR(INIT).
    L0 trap LAPIC.ICR write(INIT): inject a latched INIT event to target
       vCPU.
Target vCPU:
    L0 emulate an INIT VMExit to L1 if is guest mode.
    L1 set guest VMCS, guest_activity_state=WAIT_SIPI, vmresume.
    L0 halt vCPU if (vmcs12.guest_activity_state == WAIT_SIPI).

Source vCPU:
    L2 write LAPIC.ICR(SIPI).
    L0 trap LAPIC.ICR write(INIT): inject a latched SIPI event to traget
       vCPU.
Target vCPU:
    L0 emulate an SIPI VMExit to L1 if (vmcs12.guest_activity_state ==
       WAIT_SIPI).
    L1 set CS:IP, guest_activity_state=ACTIVE, vmresume
    L0 resume to L2
    L2 start-up

Signed-off-by: Yadong Qi <yadong.qi@intel.com>
---
 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  2 ++
 arch/x86/kvm/lapic.c            |  5 +++--
 arch/x86/kvm/vmx/nested.c       | 25 +++++++++++++++++++++----
 4 files changed, 27 insertions(+), 6 deletions(-)

```
#### [PATCH v4 1/5] linux-headers: update against 5.9-rc5
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11782773
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1E6C6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 15:14:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61D5A20795
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 15:14:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="UhwG16US"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728052AbgIQPOu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 11:14:50 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:30908 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728013AbgIQPNz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 17 Sep 2020 11:13:55 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08HE2tYk065062;
        Thu, 17 Sep 2020 10:21:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=zn9EnFIjKg8WTPGvFiN2SskCBNygFk2yu12hoGAcYiM=;
 b=UhwG16USVzhZD55C4BucCZUwChFBzJpg7Z3Eq3FIfLJRh1WE8Rx7+mNR7AVxueDt26cF
 aBV8U9Fjsu+uI4wai54WXRISvruA6LK7wEKNKmKg66nqEH9cF+dQMoPEzJ0DWte2/pSr
 LDAHcIS+YOHr0gLSRY7Pjk0OgNDAWB6UDg+oIYkkag76CACzWW++x0jzjnmlNpe/kZm6
 M3LHesUmiYoxDtJqwasPJlNJy5VcgUp+fmdbPrqXW6KMNy4SaQnbTJDieu8REPe3egaZ
 F0MuHWX+ZwqF1llILJ5zJy5wmunDgsKCrxF633EpOtmErem6B50E23EWljH/siTC3Crm RQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33m6tcms0b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 10:21:11 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08HE3FUW066345;
        Thu, 17 Sep 2020 10:21:04 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33m6tcmrvn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 10:21:04 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08HEIRSB021852;
        Thu, 17 Sep 2020 14:20:57 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma02wdc.us.ibm.com with ESMTP id 33k67c4w0r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 17 Sep 2020 14:20:57 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 08HEKvDk54526368
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 17 Sep 2020 14:20:57 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DA1BCAC064;
        Thu, 17 Sep 2020 14:20:56 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0522BAC059;
        Thu, 17 Sep 2020 14:20:53 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.85.51])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 17 Sep 2020 14:20:52 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, thuth@redhat.com, pasic@linux.ibm.com,
        borntraeger@de.ibm.com, mst@redhat.com, pbonzini@redhat.com,
        philmd@redhat.com, qemu-s390x@nongnu.org, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH v4 1/5] linux-headers: update against 5.9-rc5
Date: Thu, 17 Sep 2020 10:20:41 -0400
Message-Id: <1600352445-21110-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1600352445-21110-1-git-send-email-mjrosato@linux.ibm.com>
References: <1600352445-21110-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-17_09:2020-09-16,2020-09-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 mlxscore=0
 suspectscore=0 bulkscore=0 mlxlogscore=999 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 impostorscore=0 spamscore=0
 clxscore=1015 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009170109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PLACEHOLDER as the kernel patch driving the need for this ("vfio iommu: Add
dma available capability") is not merged yet.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 include/standard-headers/drm/drm_fourcc.h          | 140 +++++++++++++++++++++
 include/standard-headers/linux/ethtool.h           |  87 +++++++++++++
 include/standard-headers/linux/input-event-codes.h |   3 +-
 include/standard-headers/linux/vhost_types.h       |  11 ++
 include/standard-headers/linux/virtio_9p.h         |   4 +-
 include/standard-headers/linux/virtio_blk.h        |  26 ++--
 include/standard-headers/linux/virtio_config.h     |   8 +-
 include/standard-headers/linux/virtio_console.h    |   8 +-
 include/standard-headers/linux/virtio_net.h        |   6 +-
 include/standard-headers/linux/virtio_scsi.h       |  20 +--
 linux-headers/asm-generic/unistd.h                 |   6 +-
 linux-headers/asm-mips/unistd_n32.h                |   1 +
 linux-headers/asm-mips/unistd_n64.h                |   1 +
 linux-headers/asm-mips/unistd_o32.h                |   1 +
 linux-headers/asm-powerpc/kvm.h                    |   5 +
 linux-headers/asm-powerpc/unistd_32.h              |   1 +
 linux-headers/asm-powerpc/unistd_64.h              |   1 +
 linux-headers/asm-s390/kvm.h                       |   7 +-
 linux-headers/asm-s390/unistd_32.h                 |   1 +
 linux-headers/asm-s390/unistd_64.h                 |   1 +
 linux-headers/asm-x86/unistd_32.h                  |   1 +
 linux-headers/asm-x86/unistd_64.h                  |   1 +
 linux-headers/asm-x86/unistd_x32.h                 |   1 +
 linux-headers/linux/kvm.h                          |  10 +-
 linux-headers/linux/vfio.h                         |  17 ++-
 linux-headers/linux/vhost.h                        |   2 +
 26 files changed, 327 insertions(+), 43 deletions(-)

```
#### [PATCH 1/3 v4] x86: AMD: Add hardware-enforced cache coherency as a CPUID feature
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11783583
Return-Path: <SRS0=G0gk=C2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF03D112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 21:25:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 93FB9214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Sep 2020 21:25:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="wEOcQdQM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726168AbgIQVZM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Sep 2020 17:25:12 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:33292 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725858AbgIQVZI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Sep 2020 17:25:08 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08HLFAlw012593;
        Thu, 17 Sep 2020 21:22:32 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=B/v9vNu+zU6hIEta/+tlEpVzUgGI6GPuyCPAg06RhJo=;
 b=wEOcQdQMpiA5HJh4e9nSiEyW9Xbz8aUc/5qXRsO7PxQ0mvqLRC7D0CWgZ8DLYKWnSyPw
 dYwCXhAN9AWLGlBRsiWJpz/EMD426iAUjv+hB0FOySuzjXcXkTytL6Y89W33BYbOt5MS
 uWt1s2uqnzyOzln5nsJd/6s88QQFDqwPhechW8tyZ+Z9/CUQnti8b+hkQbT7KtgZ8fE8
 /s5GKMH5QyMVnhxXgiYZofxHUIx5e3ZcatXfCczxerR2dBPR6VuRDXbp8zDkbJ4UP+6r
 Hhq+gduGwcwCwQMIODaPnPYGumyTuxnJNEDap4dQgYQT122QwZaN0yzsYiEgQ0RqzhLC AQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 33gp9mku7f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Thu, 17 Sep 2020 21:22:32 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 08HLBYGZ124386;
        Thu, 17 Sep 2020 21:22:32 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 33h88cge5c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 17 Sep 2020 21:22:31 +0000
Received: from abhmp0013.oracle.com (abhmp0013.oracle.com [141.146.116.19])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 08HLMQDA029051;
        Thu, 17 Sep 2020 21:22:26 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 17 Sep 2020 21:22:26 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, joro@8bytes.org,
        dave.hansen@linux.intel.com, luto@kernel.org, peterz@infradead.org,
        linux-kernel@vger.kernel.org, hpa@zytor.com
Subject: [PATCH 1/3 v4] x86: AMD: Add hardware-enforced cache coherency as a
 CPUID feature
Date: Thu, 17 Sep 2020 21:20:36 +0000
Message-Id: <20200917212038.5090-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200917212038.5090-1-krish.sadhukhan@oracle.com>
References: <20200917212038.5090-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9747
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 spamscore=0 adultscore=0
 suspectscore=1 phishscore=0 malwarescore=0 bulkscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009170158
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9747
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999
 adultscore=0 malwarescore=0 clxscore=1015 lowpriorityscore=0 phishscore=0
 spamscore=0 priorityscore=1501 suspectscore=1 impostorscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009170158
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In some hardware implementations, coherency between the encrypted and
unencrypted mappings of the same physical page is enforced. In such a system,
it is not required for software to flush the page from all CPU caches in the
system prior to changing the value of the C-bit for a page. This hardware-
enforced cache coherency is indicated by EAX[10] in CPUID leaf 0x8000001f.

Suggested-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/scattered.c    | 1 +
 2 files changed, 2 insertions(+)

```
