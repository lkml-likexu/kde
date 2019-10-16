#### [PATCH v19 1/5] hw/arm/virt: Introduce a RAS machine option
##### From: Xiang Zheng <zhengxiang9@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiang Zheng <zhengxiang9@huawei.com>
X-Patchwork-Id: 11190419
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D68315AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:03:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 063E4218DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:03:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732426AbfJOODB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 10:03:01 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:3773 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732416AbfJOODA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 10:03:00 -0400
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 305DAD86F79D72C0877C;
        Tue, 15 Oct 2019 22:02:57 +0800 (CST)
Received: from HGHY4Z004218071.china.huawei.com (10.133.224.57) by
 DGGEMS410-HUB.china.huawei.com (10.3.19.210) with Microsoft SMTP Server id
 14.3.439.0; Tue, 15 Oct 2019 22:02:46 +0800
From: Xiang Zheng <zhengxiang9@huawei.com>
To: <pbonzini@redhat.com>, <mst@redhat.com>, <imammedo@redhat.com>,
        <shannon.zhaosl@gmail.com>, <peter.maydell@linaro.org>,
        <lersek@redhat.com>, <james.morse@arm.com>,
        <gengdongjiu@huawei.com>, <mtosatti@redhat.com>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <jonathan.cameron@huawei.com>,
        <xuwei5@huawei.com>, <kvm@vger.kernel.org>,
        <qemu-devel@nongnu.org>, <qemu-arm@nongnu.org>,
        <linuxarm@huawei.com>
CC: <zhengxiang9@huawei.com>, <wanghaibin.wang@huawei.com>
Subject: [PATCH v19 1/5] hw/arm/virt: Introduce a RAS machine option
Date: Tue, 15 Oct 2019 22:01:36 +0800
Message-ID: <20191015140140.34748-2-zhengxiang9@huawei.com>
X-Mailer: git-send-email 2.15.1.windows.2
In-Reply-To: <20191015140140.34748-1-zhengxiang9@huawei.com>
References: <20191015140140.34748-1-zhengxiang9@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.133.224.57]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Dongjiu Geng <gengdongjiu@huawei.com>

RAS Virtualization feature is not supported now, so add a RAS machine
option and disable it by default.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Signed-off-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/arm/virt.c         | 23 +++++++++++++++++++++++
 include/hw/arm/virt.h |  1 +
 2 files changed, 24 insertions(+)

```
#### [PATCH v6 1/5] Revert "KVM: X86: Fix setup the virt_spin_lock_key before static key get initialized"
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11189575
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D61914E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 01:22:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5E64321925
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 01:22:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="QHutwQe0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727453AbfJOBWJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 21:22:09 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:43332 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727011AbfJOBWJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 21:22:09 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F1ENab020114;
        Tue, 15 Oct 2019 01:19:47 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2019-08-05;
 bh=Rba9xErGxwUOOcVXLsuAqyh9LPvNTmKNCGcbMviKams=;
 b=QHutwQe0QynFPLhWhntUiulAcR/rIgytbG17sJdB6uPK69w3U3jziPJT/eSRzd2JvWq9
 eH54OB/MILbxuE3pREaHHkzUHgjBM6UMVdrA3trCK2pmyJizcPFrbqQawsml27Bi44Nv
 0brq+4WujMm7g8AZLcBUIPX0BqDWCl1zBFF+df5M0ujXvRa/okbm+l0Kh+ZV8KzXWsr+
 tyiqG7hn2zoM+Ir+u9b52Vf2wLuvQ8scgqe51DVl7b7WQcvuGbfA8fcuXNksJ/NsL14M
 68yvBwv2JxO7tnMYT8ggRbSBVECpqrzVjaD7p1SPj0F1ixObGu5sj12dKNVR7rarN0lx 0A==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2vk7fr48qa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 01:19:47 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F1IYj5129321;
        Tue, 15 Oct 2019 01:19:46 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3030.oracle.com with ESMTP id 2vks07txqb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 01:19:46 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x9F1Jdn5030242;
        Tue, 15 Oct 2019 01:19:41 GMT
Received: from z2.cn.oracle.com (/10.182.70.159)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 14 Oct 2019 18:19:39 -0700
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: vkuznets@redhat.com, linux-hyperv@vger.kernel.org,
        kvm@vger.kernel.org, kys@microsoft.com, haiyangz@microsoft.com,
        sthemmin@microsoft.com, sashal@kernel.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, pbonzini@redhat.com,
        rkrcmar@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        boris.ostrovsky@oracle.com, jgross@suse.com,
        sstabellini@kernel.org, peterz@infradead.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH v6 1/5] Revert "KVM: X86: Fix setup the virt_spin_lock_key
 before static key get initialized"
Date: Tue, 15 Oct 2019 09:19:23 +0800
Message-Id: <1571102367-31595-2-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1571102367-31595-1-git-send-email-zhenzhong.duan@oracle.com>
References: <1571102367-31595-1-git-send-email-zhenzhong.duan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150010
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150010
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This reverts commit 34226b6b70980a8f81fff3c09a2c889f77edeeff.

Commit 8990cac6e5ea ("x86/jump_label: Initialize static branching
early") adds jump_label_init() call in setup_arch() to make static
keys initialized early, so we could use the original simpler code
again.

The similar change for XEN is in commit 090d54bcbc54 ("Revert
"x86/paravirt: Set up the virt_spin_lock_key after static keys get
initialized"")

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krcmar <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
---
 arch/x86/kernel/kvm.c | 12 +++---------
 1 file changed, 3 insertions(+), 9 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH v5 1/6] psci: Export psci_ops.conduit symbol as modules will use it.
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11190051
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8659C14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 10:49:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 66A1921D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 10:49:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731298AbfJOKs7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 06:48:59 -0400
Received: from foss.arm.com ([217.140.110.172]:35096 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731261AbfJOKs7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 06:48:59 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A1C1E1000;
        Tue, 15 Oct 2019 03:48:58 -0700 (PDT)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 CC5393F68E;
        Tue, 15 Oct 2019 03:48:53 -0700 (PDT)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [PATCH v5 1/6] psci: Export psci_ops.conduit symbol as modules will
 use it.
Date: Tue, 15 Oct 2019 18:48:17 +0800
Message-Id: <20191015104822.13890-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191015104822.13890-1-jianyong.wu@arm.com>
References: <20191015104822.13890-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If arm_smccc_1_1_invoke used in modules, psci_ops.conduit should
be export.

Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 drivers/firmware/psci/psci.c | 6 ++++++
 include/linux/arm-smccc.h    | 2 +-
 include/linux/psci.h         | 1 +
 3 files changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 01/32] hw/i386: Remove obsolete LoadStateHandler::load_state_old handlers
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11190929
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF4AC1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:27:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9ED1720873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:27:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728634AbfJOQ12 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 12:27:28 -0400
Received: from mx1.redhat.com ([209.132.183.28]:64031 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728521AbfJOQ12 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 12:27:28 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id BEB018E1CF1;
        Tue, 15 Oct 2019 16:27:27 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-204-35.brq.redhat.com [10.40.204.35])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id BB9AE19C58;
        Tue, 15 Oct 2019 16:27:20 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Aleksandar Markovic <amarkovic@wavecomp.com>,
 Aurelien Jarno <aurelien@aurel32.net>, Eduardo Habkost <ehabkost@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Igor Mammedov <imammedo@redhat.com>,
 Anthony Perard <anthony.perard@citrix.com>,
 Stefano Stabellini <sstabellini@kernel.org>, Paul Durrant <paul@xen.org>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>,
 xen-devel@lists.xenproject.org, Laurent Vivier <lvivier@redhat.com>,
 "Michael S. Tsirkin" <mst@redhat.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Richard Henderson <rth@twiddle.net>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Peter Maydell <peter.maydell@linaro.org>
Subject: [PATCH 01/32] hw/i386: Remove obsolete
 LoadStateHandler::load_state_old handlers
Date: Tue, 15 Oct 2019 18:26:34 +0200
Message-Id: <20191015162705.28087-2-philmd@redhat.com>
In-Reply-To: <20191015162705.28087-1-philmd@redhat.com>
References: <20191015162705.28087-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.69]);
 Tue, 15 Oct 2019 16:27:27 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These devices implemented their load_state_old() handler 10 years
ago, previous to QEMU v0.12.
Since commit cc425b5ddf removed the pc-0.10 and pc-0.11 machines,
we can drop this code.

Note: the mips_r4k machine started to use the i8254 device just
after QEMU v0.5.0, but the MIPS machine types are not versioned,
so there is no migration compatibility issue removing this handler.

Suggested-by: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 hw/acpi/piix4.c         | 40 ---------------------------------
 hw/intc/apic_common.c   | 49 -----------------------------------------
 hw/pci-host/piix.c      | 25 ---------------------
 hw/timer/i8254_common.c | 40 ---------------------------------
 4 files changed, 154 deletions(-)

```
#### [PATCH 1/2 v2] KVM: nVMX: Defer error from VM-entry MSR-load area to until after hardware verifies VMCS guest state-area
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11189545
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B4932139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:41:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81FBD21D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:41:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Z3+RF4ry"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727135AbfJOAlS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:41:18 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:49666 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726756AbfJOAlR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:41:17 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0djo9007608;
        Tue, 15 Oct 2019 00:40:50 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-type : content-transfer-encoding; s=corp-2019-08-05;
 bh=vecuqv4EPetue9qcGGpXFHUK3lYI74uuK8qDduzgvjg=;
 b=Z3+RF4ryN4qUDXCFRx06T0NGLSGF0Ag+TBWjeEcghnJgiSwjfzODz4RCecu19cT0qsFV
 lDq0e6buExdk3B5PjyWv32P7JaBoIpRN9iZZs/fP32wFZfCltk9UfSG3ZcollLeV1L0I
 7CMMkaOTCgUvTJBkQYR5bX19/y7J2lbcrsab3PCoNEZ7ABfWPsbF3SzJciqlJRwwL9Zt
 EJ+8nloYHduNxdVkJCmgiF17FyrmvbJRh8dtuzFk81rFA3lPlKXMkFHZKsj/Kgiea49o
 iDbkrBXtcP49oLQpmfV8y3lwjZQCEkttPpzL8T7ezLOnzTOUx/hNCvOxKcrQcblAB42C Wg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2vk68uc9sh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:40:50 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0cKIi081021;
        Tue, 15 Oct 2019 00:40:49 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2vkrbkvg2d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:40:49 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x9F0emD4010621;
        Tue, 15 Oct 2019 00:40:48 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 15 Oct 2019 00:40:47 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, jmattson@google.com
Subject: [PATCH 1/2 v2] KVM: nVMX: Defer error from VM-entry MSR-load area to
 until after hardware verifies VMCS guest state-area
Date: Mon, 14 Oct 2019 20:04:45 -0400
Message-Id: <20191015000446.8099-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191015000446.8099-1-krish.sadhukhan@oracle.com>
References: <20191015000446.8099-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150005
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150005
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section “VM Entries” in Intel SDM vol 3C, VM-entry checks are
performed in a certain order. Checks on MSRs that are loaded on VM-entry
from VM-entry MSR-load area, should be done after verifying VMCS controls,
host-state area and guest-state area. As KVM relies on CPU hardware to
perform some of these checks, we need to defer VM-exit due to invalid
VM-entry MSR-load area to until after CPU hardware completes the earlier
checks and is ready to do VMLAUNCH/VMRESUME.

In order to defer errors arising from invalid VM-entry MSR-load area in
vmcs12, we set up a single invalid entry, which is illegal according to
section "Loading MSRs in Intel SDM vol 3C, in VM-entry MSR-load area of
vmcs02. This will cause the CPU hardware to VM-exit with "VM-entry failure
due to MSR loading" after it completes checks on VMCS controls, host-state
area and guest-state area. We reflect a synthesized Exit Qualification to
our guest.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 34 +++++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/nested.h | 15 +++++++++++++--
 arch/x86/kvm/vmx/vmx.c    | 18 ++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h    |  6 ++++++
 4 files changed, 68 insertions(+), 5 deletions(-)

```
#### [PATCH 1/4] kvm-unit-test: VMX: Replace hard-coded exit instruction length
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11189549
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9CF217D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:52:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C120121882
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:52:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="PvQeyWpY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727183AbfJOAwp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:52:45 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:58634 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726773AbfJOAwp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:52:45 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0nILK014310;
        Tue, 15 Oct 2019 00:52:38 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=q+YiKeIY2xF6EGM7ufhqqTMFE16YcJb84j67MEUh+Ic=;
 b=PvQeyWpYrqlyjwTL9uXgZrXn0kd9AlVATI1tnZ3xkfmTVGsTE3Eae2R41GpRb4RrC54C
 HtssdsgeFqGHnFZYC/OalW+hp+nfq5gKsY94zI+KboB1zMxpdqkv3HP3mX1nXmBtb0RV
 SJA6sowNVJiMwLDya8LRMRj9LvftfTMfc7ffQdtqlLsK+ml3G8+vhwpUH5iHjz59Qtlo
 VhyGqZnst+fm+J2XUZLrZY+MGe7uieE5qCutRcHMX7akqB21/MvzGW0AiTYnV3023IUT
 6KR+V+EforyI8hy+tiOZCph34ClpAFIPFyrmY+P40j9Uup1PTXzwpsQs6OIBoxau0CTb 9w==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2vk68ucax3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:52:38 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x9F0mCvh029357;
        Tue, 15 Oct 2019 00:52:38 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2vkry7hbvy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 15 Oct 2019 00:52:37 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x9F0qaLk020535;
        Tue, 15 Oct 2019 00:52:36 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 15 Oct 2019 00:52:36 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com, jmattson@google.com
Subject: [PATCH 1/4] kvm-unit-test: VMX: Replace hard-coded exit instruction
 length
Date: Mon, 14 Oct 2019 20:16:30 -0400
Message-Id: <20191015001633.8603-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191015001633.8603-1-krish.sadhukhan@oracle.com>
References: <20191015001633.8603-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=13
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=740
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1910150007
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9410
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=13 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=823 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1910150007
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

..with value read from EXI_INST_LEN field.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 x86/vmx_tests.c | 18 ++++++++++++++----
 1 file changed, 14 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests v2 PATCH 1/2] lib: use a status enum for reporting pass/fail
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11191643
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6CCF113BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 20:46:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 488FC20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 20:46:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="k6bvWpl+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388006AbfJOUqN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 16:46:13 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:39432 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727673AbfJOUqN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 16:46:13 -0400
Received: by mail-pf1-f201.google.com with SMTP id b13so16866110pfp.6
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 13:46:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=PHU3S8UkmZlEWDDACryJAggjnd+j8fKXKUj4kaokT1g=;
        b=k6bvWpl+ugwFOqGDgu4F/3D3YCFSzLJvWy6NehP1566IJ/9Hvhktfm9tFFGbH4AaX1
         BLmtA2w8obi5HdwAcu9gyRDXygk7502O29YYHVYGVdpgt64G2w/IraYRNJfgKistAO1H
         ApGvPRxVGkWBPcmmxp2scFE7q5k3sHoJc2WZ5B11FNNnwYoX/jLvwAtlIVjIkKcATuLF
         NQ784iuEaVlEm4CBqJMk1GqtyWEFBLfMHLghNIUqZolXoIiJGMrwpnQbp5hh52RocCut
         AQywBTvSsO/L7TTm69ZdkeKpNYkEXlnqL1U8N17E94OlDaxUcqgVZGM6cThbRLFrdXQA
         0tFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=PHU3S8UkmZlEWDDACryJAggjnd+j8fKXKUj4kaokT1g=;
        b=AynRL73nU3c5EUa+rpgq/F9+VqZ2jVRvq6T3dRJbFz4L6z5awRE0VqDhXFaHpqXJzt
         8uOTO1PCeNdox2qg3bbxtlmukA/cMGgy6UllwrOov4bs3shGrZjAZWspxph+ugaD6v9T
         WngoOKfSdPOzlx3s8AepbVv8feyvNWQWV0kZCIXi4OatuDB576JsaZvVF4Xk9aL0RQYw
         SqUIDGUqEZamapOWxktE9NFkUpAv6OGonm/Eq6TuaNV9Mn7FlKMaUYtHyzVuvDozkaaq
         R0voJPzj+Mls28RUrrTWbMu9dVN0C83xPuqgpY4sPbAjv2LLDrp62cVkzvMl1W3stMCT
         xNxg==
X-Gm-Message-State: APjAAAX4DQymV1g5aTcpSi01l7wNCeAHnSFM0DTwZTmVjXEWJvdghXAn
        lgeYKN8PC4wPLcyw37BcTChcmdphRhXmMOvxgkviNLmxP9eF4M3WgfUK3X0PpcTs5b/3nq1xxlr
        4CYHQVL8Yk8V1I1qrsSDJuETlZhISShxL7bt+hxpMIW/9eqY6VkiO3g==
X-Google-Smtp-Source: 
 APXvYqxel6aWp6RFarfN6fwhfOh6ejXJp4N/6FYncVOX4wGo05dnLdNldhMDuEKnEI1/6m68VeTSz1CaHA==
X-Received: by 2002:a63:e1f:: with SMTP id d31mr22089103pgl.379.1571172371730;
 Tue, 15 Oct 2019 13:46:11 -0700 (PDT)
Date: Tue, 15 Oct 2019 13:46:02 -0700
In-Reply-To: <20191015204603.47845-1-morbo@google.com>
Message-Id: <20191015204603.47845-2-morbo@google.com>
Mime-Version: 1.0
References: <20191012074454.208377-1-morbo@google.com>
 <20191015204603.47845-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests v2 PATCH 1/2] lib: use a status enum for reporting
 pass/fail
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com,
        thuth@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some values passed into "report" as "pass/fail" are larger than the
size of the parameter. Instead use a status enum so that the size of the
argument no longer matters.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 lib/libcflat.h | 13 +++++++++++--
 lib/report.c   | 24 ++++++++++++------------
 2 files changed, 23 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/4] x86: emulator: use "SSE2" for the target
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11189523
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A88C417E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:04:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 86B4B217F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:04:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="AfQKpBPq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726876AbfJOAEV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:04:21 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:35913 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726866AbfJOAEV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:04:21 -0400
Received: by mail-pg1-f202.google.com with SMTP id h36so13764800pgb.3
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 17:04:19 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=AfQKpBPqVxVR2G3jH4Mlo8pegG6UJSeiv7z9GCBcry/fq3zmZ8zQUloTMGWfrhsl3M
         cvnYmJrwRmhPxuar7QmF+nJE3I5oOtjaFeecMtaxJ62DPuDf7Zwqt9uNt/7A9H2jPjf6
         nQjCJsGuHzjBav5o0KrOaHl0rGV+Lp67Teo+MFmDXyUx0vZ9+LeD5tqkUYZiEcrUfa/C
         YQQMEhutnU8ooSmScr5P+4i1cuusbZHvol3BCw59inHo9xRIw04ltsY8JBPmqPgRSwOP
         Mg5ILit4LQhUmWWa3tfxLunohk+AICIwV63bi5Y/grf7gjtQ7hyV73Rwt/OYZ/q53LBW
         QhiQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=A4dsUSQI/X7gMuFCMinZV7TulIv6evYZAanpDugJOLpmY/RtJFAv4VS+wC46X0AJqw
         124RZkCejdHUXtzy3daSb4MFGrSFOTKNEE3sP3B4+3Tx384A7nDO0YfTlFFRLho/cccT
         1j5h6fI0XfXPvwm1/fmH8nXeLH+exjxduCqG9eGwzzi6EVUTrRm13y3VX5+O7iIy8Mqw
         wRbzGxacIDsSgrsFo26nIDRQxAZe4FdZdxm3szs5gnaXu2R+07SlRhaE7WvULnr7lM+E
         vhiWEFuNtU/+O9igZlwQwXEEppt3qWXHjDnvmsZU/G1yy90jEbXB2i8i7ye4dLMhvcVu
         kXWg==
X-Gm-Message-State: APjAAAUGEAxWJhsDainhDQtfYrwyi5vx+0P90FsZLIhTYJ8j2A+P1Pve
        3udQEMwTuC7lUwJjz9AW+XM3J2HBJMxwkzBcZp3mNnk787qKUafqpQvrU8j1rd/zU9aBtovjpv0
        bpw5w/v0EEh11qrDPa0QcRvn70S02mJnYAIL361gaxT+afTY7tqu07w==
X-Google-Smtp-Source: 
 APXvYqx8bfPydciDwflNH+VlBKlpBk07ttlrWJioJiuXHGiOlvJmY2hYSiXQ88lZT4UBRGS6Tcy4f64yRw==
X-Received: by 2002:a63:1e59:: with SMTP id
 p25mr35134433pgm.361.1571097858628;
 Mon, 14 Oct 2019 17:04:18 -0700 (PDT)
Date: Mon, 14 Oct 2019 17:04:08 -0700
In-Reply-To: <20191015000411.59740-1-morbo@google.com>
Message-Id: <20191015000411.59740-2-morbo@google.com>
Mime-Version: 1.0
References: <20191010183506.129921-1-morbo@google.com>
 <20191015000411.59740-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH v2 1/4] x86: emulator: use "SSE2" for the
 target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PULL] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11191743
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E99314DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 21:19:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4781A20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 21:19:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727211AbfJOVTP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 17:19:15 -0400
Received: from mx1.redhat.com ([209.132.183.28]:34326 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726335AbfJOVTO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 17:19:14 -0400
Received: from mail-qt1-f200.google.com (mail-qt1-f200.google.com
 [209.85.160.200])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id CFDC1368E2
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 21:19:14 +0000 (UTC)
Received: by mail-qt1-f200.google.com with SMTP id n59so22573065qtd.8
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 14:19:14 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=dL6rRUzanF/mngAS+r+PSLw0RQ+CPB/xDAExf30z58I=;
        b=BRL2iG8IPbjCW3wiT7AjoMxJTeT59CZoRV1CQDOyRRm3pbgnGt460TDfCB9enm6k6+
         GEYpcG2OuWEfT1LRdbB8aS/GluTPLLd0TSpCeT8o2+mc8EzXcwdL7MVR5XpY2S9CkomY
         4RmC4r0jOqHr+oR/aW9aYbgT9+V/adtWhUlEks2PZrNVRgR9L4M8PuAWNoHSeWSCMtXI
         XLfK1Ja18J8Zd0/dtLP20/sCZRVlxRsuGLY5rk0UNFTVPt58QlSdytJJ84BRy5ui8SJz
         aQLg9nHT2RypDqKkoRe2pCcXR1kX8MmKKEIlbE0j21dHKvxsKI+PVyc/JsFLsO2nwAcS
         Kn+Q==
X-Gm-Message-State: APjAAAUnXk3o5y0Rpl7XgjxGAoCx0HGEYSKyiKabLp1RiWEUyHwsNj1T
        zGXecPdY4aefOQ2Fev4u8qwE7c/0+Vjig4hoznelUDOlzfQAbdVXODRIi+PACGdnRy4OU/P5B5h
        4rVFm0jIr6XHx
X-Received: by 2002:a0c:f612:: with SMTP id r18mr38402297qvm.56.1571174353652;
        Tue, 15 Oct 2019 14:19:13 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzMCqTGbwZd7p8eXtvsCO6t1D+F0697yJqDJ1oBBJZwAb7HGPZvXklyA5piJoGL8p8xGUaolQ==
X-Received: by 2002:a0c:f612:: with SMTP id r18mr38402264qvm.56.1571174353431;
        Tue, 15 Oct 2019 14:19:13 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 q44sm14292649qtk.16.2019.10.15.14.19.10
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 15 Oct 2019 14:19:12 -0700 (PDT)
Date: Tue, 15 Oct 2019 17:19:08 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        jan.kiszka@web.de, mst@redhat.com
Subject: [PULL] vhost: cleanups and fixes
Message-ID: <20191015171908-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit da0c9ea146cbe92b832f1b0f694840ea8eb33cce:

  Linux 5.4-rc2 (2019-10-06 14:27:30 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 245cdd9fbd396483d501db83047116e2530f245f:

  vhost/test: stop device before reset (2019-10-13 09:38:27 -0400)

----------------------------------------------------------------
virtio: fixes

Some minor bugfixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Michael S. Tsirkin (3):
      tools/virtio: more stubs
      tools/virtio: xen stub
      vhost/test: stop device before reset

 drivers/vhost/test.c             | 2 ++
 tools/virtio/crypto/hash.h       | 0
 tools/virtio/linux/dma-mapping.h | 2 ++
 tools/virtio/xen/xen.h           | 6 ++++++
 4 files changed, 10 insertions(+)
 create mode 100644 tools/virtio/crypto/hash.h
 create mode 100644 tools/virtio/xen/xen.h
```
#### [PATCH 1/4] KVM: VMX: rename {vmx,nested_vmx}_vcpu_setup functions
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11191221
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2295C1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:55:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0CD1D217D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 16:55:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388338AbfJOQzd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 12:55:33 -0400
Received: from mga11.intel.com ([192.55.52.93]:46844 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726362AbfJOQza (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 12:55:30 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 15 Oct 2019 09:55:30 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,300,1566889200";
   d="scan'208";a="201811351"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by FMSMGA003.fm.intel.com with ESMTP; 15 Oct 2019 09:55:28 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] KVM: VMX: rename {vmx,nested_vmx}_vcpu_setup functions
Date: Wed, 16 Oct 2019 00:40:30 +0800
Message-Id: <20191015164033.87276-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20191015164033.87276-1-xiaoyao.li@intel.com>
References: <20191015164033.87276-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rename {vmx,nested_vmx}_vcpu_setup to {vmx,nested_vmx}_vmcs_setup,
to match what they really do.

No functional change.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 arch/x86/kvm/vmx/nested.h | 2 +-
 arch/x86/kvm/vmx/vmx.c    | 9 +++------
 3 files changed, 5 insertions(+), 8 deletions(-)

```
#### [PATCH V2 1/2] linux headers: update against Linux 5.4-rc2
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11190545
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D7632912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:36:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A65420854
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 14:36:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Ov0yHb5k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732765AbfJOOgZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 10:36:25 -0400
Received: from mail-pl1-f194.google.com ([209.85.214.194]:37769 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732734AbfJOOgZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 10:36:25 -0400
Received: by mail-pl1-f194.google.com with SMTP id u20so9702720plq.4
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 07:36:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=wZh677+pLYfT7Nth5oMeUYsjvXgYmTkpkEHZHSrS44o=;
        b=Ov0yHb5kET81rpZ4ee3Zi7MyEl6rTPzYLS+eZqGcpl8r9UHnB3WkaWuUI/hOVDIgzL
         rdMPO4JbQdix2CGwisvm0KB+catcdpf4b6Cy6JgFgBGzZOIM830TkmW1JgTaemmypSJD
         6vUOFP/iGV5P4kgtvNhuPP14e8lwJENWMoINuyMhePD6fHgDvb7+4a6dzBrEqarLfbXy
         bxeYBcsIUaOo7vVfW1SytWW6VixDd5IwrH6MvvDkR+Ev6ulnVVPyPnFLE60rNDeHPPIo
         JGEhxfetis0xiI9z6xoyrt8RmW8pZ6wi7EuaptcLzaDoRsApNu3SL+F/0Uvabq5jaCT6
         i0oQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=wZh677+pLYfT7Nth5oMeUYsjvXgYmTkpkEHZHSrS44o=;
        b=XziRRMDtSYjYRxzXmePSY/YaLpNgtKDpmG0DTxNxAXb0JCEqz0TcwHe5HdRqowXGbk
         b85Yn5+LVedvNMFTgAKyGqIGbcbFqf+yaJmoS7vrkLS1Vh4FDqd2T6zfPunMovYyL9aW
         fsyqMbw9xjUPADlivoaiZyHo9VBPhw5tfOhVahnIA71wZOCff8SojPip8CM/jI8gxj75
         ZHxLbIeP4+GIzfCA2noVY7qd0XwQm8sHz0zYBpAz1NIcYzVj7MU8t2K4ZPNIyfcIHiA/
         3F17r+SdwhrCLOPL+tm56b+d0pXdMLgBKHJCh5JidKbTGNBoF40AeGEaVJUphhWsOtjO
         JcxQ==
X-Gm-Message-State: APjAAAUD5qea00w33CJ1JtfLuYzlXQLT5vjN7+5FBluruc86XHeKn4qB
        JeRNcue/uVhOBvUBc9SguQ0=
X-Google-Smtp-Source: 
 APXvYqxBeOtaH3QAK3g+dKjheCpzjhjkPYQ7Eba0ukrHmv8dVI1m3IN/y0fNyFHrTOkUsFSUlNuWbg==
X-Received: by 2002:a17:902:8bc4:: with SMTP id
 r4mr34347876plo.341.1571150183564;
        Tue, 15 Oct 2019 07:36:23 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 v43sm4913165pjb.1.2019.10.15.07.36.19
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 15 Oct 2019 07:36:22 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: mst@redhat.com, cohuck@redhat.com, pbonzini@redhat.com,
        rth@twiddle.net, ehabkost@redhat.com, mtosatti@redhat.com,
        vkuznets@redhat.com, rkagan@virtuozzo.com
Cc: Tianyu Lan <Tianyu.Lan@microsoft.com>, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH V2 1/2] linux headers: update against Linux 5.4-rc2
Date: Tue, 15 Oct 2019 22:36:09 +0800
Message-Id: <20191015143610.31857-2-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
In-Reply-To: <20191015143610.31857-1-Tianyu.Lan@microsoft.com>
References: <20191015143610.31857-1-Tianyu.Lan@microsoft.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

commit da0c9ea146cbe92b832f1b0f694840ea8eb33cce

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
 include/standard-headers/asm-x86/bootparam.h |  2 +
 include/standard-headers/asm-x86/kvm_para.h  |  1 +
 include/standard-headers/linux/ethtool.h     | 24 ++++++++++
 include/standard-headers/linux/pci_regs.h    | 19 +++++++-
 include/standard-headers/linux/virtio_ids.h  |  2 +
 include/standard-headers/linux/virtio_pmem.h |  6 +--
 linux-headers/asm-arm/kvm.h                  | 16 ++++++-
 linux-headers/asm-arm/unistd-common.h        |  2 +
 linux-headers/asm-arm64/kvm.h                | 21 +++++++-
 linux-headers/asm-generic/mman-common.h      | 18 ++++---
 linux-headers/asm-generic/mman.h             | 10 ++--
 linux-headers/asm-generic/unistd.h           | 10 +++-
 linux-headers/asm-mips/mman.h                |  3 ++
 linux-headers/asm-mips/unistd_n32.h          |  2 +
 linux-headers/asm-mips/unistd_n64.h          |  2 +
 linux-headers/asm-mips/unistd_o32.h          |  2 +
 linux-headers/asm-powerpc/mman.h             |  6 +--
 linux-headers/asm-powerpc/unistd_32.h        |  2 +
 linux-headers/asm-powerpc/unistd_64.h        |  2 +
 linux-headers/asm-s390/kvm.h                 |  6 +++
 linux-headers/asm-s390/unistd_32.h           |  2 +
 linux-headers/asm-s390/unistd_64.h           |  2 +
 linux-headers/asm-x86/kvm.h                  | 28 ++++++++---
 linux-headers/asm-x86/unistd.h               |  2 +-
 linux-headers/asm-x86/unistd_32.h            |  2 +
 linux-headers/asm-x86/unistd_64.h            |  2 +
 linux-headers/asm-x86/unistd_x32.h           |  2 +
 linux-headers/linux/kvm.h                    | 12 ++++-
 linux-headers/linux/psp-sev.h                |  5 +-
 linux-headers/linux/vfio.h                   | 71 ++++++++++++++++++++--------
 30 files changed, 225 insertions(+), 59 deletions(-)

```
#### [PATCH v4] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11189537
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9439615AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:15:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D0AE2089C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 00:15:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="hU105J9t"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726895AbfJOANW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 20:13:22 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:49492 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726876AbfJOANW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 20:13:22 -0400
Received: by mail-pf1-f201.google.com with SMTP id i28so14510594pfq.16
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 17:13:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=iGDRzknINDn0+B93DptfXcI+TwD7kEgqFN68Grd2F8Y=;
        b=hU105J9tpqf9aT0TOAEBRqoIhUmNDvDXnttHVWK11xUoDdpwHT0Tb3a+k5y8GZNB+a
         1Y7NqlGjL2iAQRyVA1+tTb6C5Zg5rA1TIMz8eHG7fjnbkmUebM2kRn+LoGoZx7Z0//tu
         o6y9gGWWxsXMEuhosWpnmvC1zONFMzQ5hQfJYnS89TE7iIXlJPMAjhcugbZzf8yKpR6K
         AkXHSm9IiEmZauYcVS2gPVpkWsV+/+Y1+MepEAm3vzAyFhUWdkxh2Mg2WUxP3eyxvD6x
         NBnCsV7vvIouFaZ746UwX7Evv1+fxg7gEtR4NP3hgCQ7FThWfTsBbFCD+kka+6xVr8SQ
         ElWQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=iGDRzknINDn0+B93DptfXcI+TwD7kEgqFN68Grd2F8Y=;
        b=bhVIJ6z4dk6cn3gdzlouAs8cjv9zvikf35tr3QC23Dq7wxMk5XVzBfHcN7KiLjbD+B
         a9EcBaZ4csWenBaP2QgaCLOEdaBURNMJM1dEgovDNBVH3MAAO5Yo0hgcRM4TaftwMo5W
         1rlqT9/KpSVDb5yyqwHCBAKcorFP6f3/PzxKtm751Y8qf37/hAOYZjgcdiJU4n1PRkhN
         7s2cCzkhruYzTCDlX58g1gHSgmDJoiE3aWz0HVZu408J8DWtRnT9LNXSRocwT35GluDw
         Qjqc8ILnp7rGWlLijE3pS7UD6JneCz+T0fQWwJH/SUfNK5b96klvilndjw5GWFlvmbko
         DGKA==
X-Gm-Message-State: APjAAAXX1kLp0ehjVM/kL97EsZU9S7iNH2MfB2kF4H00+arpP2Rh/50y
        +YmFUElSBzvdpA7SS4gpQhxgT+uyVk5IK9wzAdLm/YhkXfEi0r98jNk+oO7336dK7wHxnB58UYB
        a1Sft+fWANDbTDwxww0VcNpz2W8duQuRQxpgf10o1+WKAZ63b8uvVqI2kbqpi5I0=
X-Google-Smtp-Source: 
 APXvYqyN7Kg2qR0orsXOte5Y3fdXctBv5m74xHUd/xFHdFVLyOlPij+jzmF6FRY/G00Zu2DieBfrO4xseTbjPw==
X-Received: by 2002:a63:1511:: with SMTP id v17mr35070452pgl.34.1571098399231;
 Mon, 14 Oct 2019 17:13:19 -0700 (PDT)
Date: Mon, 14 Oct 2019 17:13:04 -0700
Message-Id: <20191015001304.2304-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [PATCH v4] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the "virtualize APIC accesses" VM-execution control is set in the
VMCS, the APIC virtualization hardware is triggered when a page walk
in VMX non-root mode terminates at a PTE wherein the address of the 4k
page frame matches the APIC-access address specified in the VMCS. On
hardware, the APIC-access address may be any valid 4k-aligned physical
address.

KVM's nVMX implementation enforces the additional constraint that the
APIC-access address specified in the vmcs12 must be backed by
a "struct page" in L1. If not, L0 will simply clear the "virtualize
APIC accesses" VM-execution control in the vmcs02.

The problem with this approach is that the L1 guest has arranged the
vmcs12 EPT tables--or shadow page tables, if the "enable EPT"
VM-execution control is clear in the vmcs12--so that the L2 guest
physical address(es)--or L2 guest linear address(es)--that reference
the L2 APIC map to the APIC-access address specified in the
vmcs12. Without the "virtualize APIC accesses" VM-execution control in
the vmcs02, the APIC accesses in the L2 guest will directly access the
APIC-access page in L1.

When there is no mapping whatsoever for the APIC-access address in L1,
the L2 VM just loses the intended APIC virtualization. However, when
the APIC-access address is mapped to an MMIO region in L1, the L2
guest gets direct access to the L1 MMIO device. For example, if the
APIC-access address specified in the vmcs12 is 0xfee00000, then L2
gets direct access to L1's APIC.

Since this vmcs12 configuration is something that KVM cannot
faithfully emulate, the appropriate response is to exit to userspace
with KVM_INTERNAL_ERROR_EMULATION.

Fixes: fe3ef05c7572 ("KVM: nVMX: Prepare vmcs02 from vmcs01 and vmcs12")
Reported-by: Dan Cross <dcross@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v3 -> v4: Changed enum enter_vmx_status to enum nvmx_vmentry_status;
          clarified debug message in nested_get_vmcs12_pages();
          moved nested_vmx_enter_non_root_mode() error handling in
	  nested_vmx_run() out-of-line
v2 -> v3: Added default case to new switch in nested_vmx_run
v1 -> v2: Added enum enter_vmx_status

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 65 +++++++++++++++++++--------------
 arch/x86/kvm/vmx/nested.h       | 13 ++++++-
 arch/x86/kvm/x86.c              |  8 +++-
 4 files changed, 56 insertions(+), 32 deletions(-)

```
#### [PATCH v5] KVM: nVMX: Don't leak L1 MMIO regions to L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11191345
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3D39D14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 17:44:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E1F420873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 17:44:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="M91s3QfT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727327AbfJORoT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 13:44:19 -0400
Received: from mail-pl1-f202.google.com ([209.85.214.202]:34331 "EHLO
        mail-pl1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726038AbfJORoS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 13:44:18 -0400
Received: by mail-pl1-f202.google.com with SMTP id 70so12525674ple.1
        for <kvm@vger.kernel.org>; Tue, 15 Oct 2019 10:44:18 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Pj7EJ/s+9Kdru3qVsTpipfhWySxdmFUXdi38jGAkWaU=;
        b=M91s3QfTNSD2A1aTfAentlt5eCqInU8BDMFdAQl8YZsVeNYWc87WGB24pJbWiE3tJV
         qNuYFfTw6aUIO3gswM8fz9YDWw5Apvjqh1O7lX0v/x/ynnc5qA+WaijgoGZBLssaJccD
         jaTePeg6mbUEQ8UOuGjVXV5CNKuVouo/K4GHj3abXfTUiJX16WyZEYNt47PIuB12w/Ks
         n85si44Zac6h0K+uCWDMx3ez0BqyTLMN9c82dSQO4mJA/lYVgPNO3AQxYcUZxQ7vbbPl
         M2yT7+syya6hC2yVITZ00i0tI5eeTnHgD3XBkH9nATrq5f22emhHLaZjtdY4QVgemJ9E
         D7Xg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Pj7EJ/s+9Kdru3qVsTpipfhWySxdmFUXdi38jGAkWaU=;
        b=rZWCbi0GRuI8y8lgZJyqjKXQzi6GsMPOy5eIpPxNuGclZ/YdStRTse+GWUcjGCQtAR
         4IB4w6zjMwTZDD7dc6QoanjWgsd57anBQIHlp0ymgXhHCJE3VtBJbw+VXY5s+J/uagR9
         CvV+feFjdzIrRLPp5DSLq00xb6GFcxOYwz0abzJlXifNp8SngzOB1ziuRJ9vz3NpMORC
         9aZqi74Lvx1b93n/GEPrfhKSfpYURsEg7oPASEMCg/CRFmMZXBSqejf52GH4rJyifqDj
         7aO7bbNV12mVQ6RmOWhkCCCDLbIiyYuw0E9VcRcY4Mdx6rnkDFW7uFExcxbBDJvCJRbM
         ZoDQ==
X-Gm-Message-State: APjAAAUd4SoYgKhVA4JxFgwqOZ3aTYCNOAujGsjIn3w0cXRSORxZ/rPl
        2sHssnFXrREREqCvVKC8AN9MqZ42AbBEucNsiUX2igWeV0i5w59nDDZP9SRv11gUjEt3OHU6xrx
        KkiowHcyKlT/DuDGriwan7zCFLvgWcRdtd81fShXWeA+UNXdndbPLqbS+Axh6q10=
X-Google-Smtp-Source: 
 APXvYqxT4RXntVrT1LOcAbktxIQqO9uVHUU3qUgtjnnkhQPVsDqFo92xDH0HnLHC48q/zg2M98o9fj8JhgxonQ==
X-Received: by 2002:a65:5a8c:: with SMTP id c12mr2612169pgt.140.1571161457144;
 Tue, 15 Oct 2019 10:44:17 -0700 (PDT)
Date: Tue, 15 Oct 2019 10:44:05 -0700
Message-Id: <20191015174405.163723-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [PATCH v5] KVM: nVMX: Don't leak L1 MMIO regions to L2
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Liran Alon <liran.alon@oracle.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Dan Cross <dcross@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the "virtualize APIC accesses" VM-execution control is set in the
VMCS, the APIC virtualization hardware is triggered when a page walk
in VMX non-root mode terminates at a PTE wherein the address of the 4k
page frame matches the APIC-access address specified in the VMCS. On
hardware, the APIC-access address may be any valid 4k-aligned physical
address.

KVM's nVMX implementation enforces the additional constraint that the
APIC-access address specified in the vmcs12 must be backed by
a "struct page" in L1. If not, L0 will simply clear the "virtualize
APIC accesses" VM-execution control in the vmcs02.

The problem with this approach is that the L1 guest has arranged the
vmcs12 EPT tables--or shadow page tables, if the "enable EPT"
VM-execution control is clear in the vmcs12--so that the L2 guest
physical address(es)--or L2 guest linear address(es)--that reference
the L2 APIC map to the APIC-access address specified in the
vmcs12. Without the "virtualize APIC accesses" VM-execution control in
the vmcs02, the APIC accesses in the L2 guest will directly access the
APIC-access page in L1.

When there is no mapping whatsoever for the APIC-access address in L1,
the L2 VM just loses the intended APIC virtualization. However, when
the APIC-access address is mapped to an MMIO region in L1, the L2
guest gets direct access to the L1 MMIO device. For example, if the
APIC-access address specified in the vmcs12 is 0xfee00000, then L2
gets direct access to L1's APIC.

Since this vmcs12 configuration is something that KVM cannot
faithfully emulate, the appropriate response is to exit to userspace
with KVM_INTERNAL_ERROR_EMULATION.

Fixes: fe3ef05c7572 ("KVM: nVMX: Prepare vmcs02 from vmcs01 and vmcs12")
Reported-by: Dan Cross <dcross@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v4 -> v5: Concatenated two lines
v3 -> v4: Changed enum enter_vmx_status to enum nvmx_vmentry_status;
          clarified debug message in nested_get_vmcs12_pages();
          moved nested_vmx_enter_non_root_mode() error handling in
          nested_vmx_run() out-of-line
v2 -> v3: Added default case to new switch in nested_vmx_run
v1 -> v2: Added enum enter_vmx_status

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/vmx/nested.c       | 64 ++++++++++++++++++---------------
 arch/x86/kvm/vmx/nested.h       | 13 ++++++-
 arch/x86/kvm/x86.c              |  8 +++--
 4 files changed, 55 insertions(+), 32 deletions(-)

```
#### [PATCH] vfio/type1: Initialize resv_msi_base
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11190647
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E3761575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 15:17:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 66F9E217D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 15:17:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733243AbfJOPQ4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 11:16:56 -0400
Received: from 8bytes.org ([81.169.241.247]:47630 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725991AbfJOPQ4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 11:16:56 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 6EC60398; Tue, 15 Oct 2019 17:16:54 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Joerg Roedel <jroedel@suse.de>
Subject: [PATCH] vfio/type1: Initialize resv_msi_base
Date: Tue, 15 Oct 2019 17:16:50 +0200
Message-Id: <20191015151650.30788-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

After enabling CONFIG_IOMMU_DMA on X86 a new warning appears when
compiling vfio:

drivers/vfio/vfio_iommu_type1.c: In function ‘vfio_iommu_type1_attach_group’:
drivers/vfio/vfio_iommu_type1.c:1827:7: warning: ‘resv_msi_base’ may be used uninitialized in this function [-Wmaybe-uninitialized]
   ret = iommu_get_msi_cookie(domain->domain, resv_msi_base);
   ~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The warning is a false positive, because the call to iommu_get_msi_cookie()
only happens when vfio_iommu_has_sw_msi() returned true. And that only
happens when it also set resv_msi_base.

But initialize the variable anyway to get rid of the warning.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vsock/virtio: remove unused 'work' field from 'struct virtio_vsock_pkt'
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11190633
Return-Path: <SRS0=XGHp=YI=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC0E114DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 15:01:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9517A2086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 15 Oct 2019 15:01:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733203AbfJOPBA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 15 Oct 2019 11:01:00 -0400
Received: from mx1.redhat.com ([209.132.183.28]:53448 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726523AbfJOPA7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 15 Oct 2019 11:00:59 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id C47B9308A98C;
        Tue, 15 Oct 2019 15:00:59 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-116-56.ams2.redhat.com
 [10.36.116.56])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6CE31194BE;
        Tue, 15 Oct 2019 15:00:52 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org, Stefan Hajnoczi <stefanha@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org
Subject: [PATCH] vsock/virtio: remove unused 'work' field from 'struct
 virtio_vsock_pkt'
Date: Tue, 15 Oct 2019 17:00:51 +0200
Message-Id: <20191015150051.104631-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.41]);
 Tue, 15 Oct 2019 15:00:59 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'work' field was introduced with commit 06a8fc78367d0
("VSOCK: Introduce virtio_vsock_common.ko")
but it is never used in the code, so we can remove it to save
memory allocated in the per-packet 'struct virtio_vsock_pkt'

Suggested-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 include/linux/virtio_vsock.h | 1 -
 1 file changed, 1 deletion(-)

```
