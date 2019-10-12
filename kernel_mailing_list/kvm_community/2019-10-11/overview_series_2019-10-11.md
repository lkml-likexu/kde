#### [PATCH v2 1/5] KVM: VMX: Remove unneeded check for X86_FEATURE_XSAVEFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11186311
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CA12815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 19:41:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AB368218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 19:41:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="nrQWGXsc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729023AbfJKTlB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 15:41:01 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:55832 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728889AbfJKTlB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 15:41:01 -0400
Received: by mail-pf1-f202.google.com with SMTP id u21so5360778pfm.22
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 12:40:59 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=tFjCmwHNkWY/vtXdDAhqblK0COAto8NjIyTqKF2VaKg=;
        b=nrQWGXscB36hvzb/+9K7jjA9//3BNp4/XJGUu1wTuOMnB7lrh4qC+jT+4ACc6E3HEw
         PpIpv5zEFkKw4aPtu41WtWD/MRlfLLGzspdERee1zFBGNT00N6BtPHfi89d4Q20AGPBg
         Tg9OOzbzAWd1TLmnYMcnsh9omH7dlSa5FA8Uv/p3WCt1Izo26VR2tpdxJSxK/so+9wbF
         /Wf8HARNhZk+go8Q0D3UA4szvNF8rNMUCzz6C4n008782d+DAzaLKe8og1B1SLJHgB+q
         8guZgwBKuW0MRzZmc1qotHwsUk/qQFVAmH+oFs8x2goep8wkeigl6tq/XNokyJw8dvBF
         CkDQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=tFjCmwHNkWY/vtXdDAhqblK0COAto8NjIyTqKF2VaKg=;
        b=hs+o5XUmmJMc6qEg8JUTcLTdWoVG8unUrlAVbD7sl4PiDspmF8or221CeESrTxwPHJ
         7CgonJvspLp2KqUJSmXXW8dBKBP9ECx2FopueCClPqcUITTu9zf/uPTI2mdWfhgAvhzT
         d7sBuOyRic4ro1et6xWZefiCLW9zMijgGENHYrNcl59VpPFy8ToFQIsmnhcQNnRmztUW
         lR7ZtB4G1R/XeT+HIlyf1E0oHgjGPOM5s6CZDytgW+39t+bPEAQuj4r37idwKbn5NLLK
         b36M49P2nhjcDWDNZno5olmszG/zxEaG42wEsEkj7aZsgk8Vv8K97wEqcxFE3puHu9Fa
         vJiw==
X-Gm-Message-State: APjAAAXzhkLlC2sgRTZr316BeOsTpGIyTZXHKF8yK1ab1FYZnVauFWkt
        sdAlK52WVFDsMLt8z4aSMJ7vsvrplTw9ysMV
X-Google-Smtp-Source: 
 APXvYqxbt6TWtw0vLChkx71/BWcvtD1Nqihu/gC69YYt5qoaXWdLbuWCfCe7D+OUsa/4juRCdj35oFZzX5PoNRSi
X-Received: by 2002:a65:450c:: with SMTP id
 n12mr13571848pgq.394.1570822859060;
 Fri, 11 Oct 2019 12:40:59 -0700 (PDT)
Date: Fri, 11 Oct 2019 12:40:28 -0700
In-Reply-To: <20191011194032.240572-1-aaronlewis@google.com>
Message-Id: <20191011194032.240572-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20191011194032.240572-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [PATCH v2 1/5] KVM: VMX: Remove unneeded check for X86_FEATURE_XSAVE
From: Aaron Lewis <aaronlewis@google.com>
To: Babu Moger <Babu.Moger@amd.com>,
        Yang Weijiang <weijiang.yang@intel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Volume 4 of the SDM says that IA32_XSS is supported
"If(CPUID.(0DH, 1):EAX.[3] = 1", so only the X86_FEATURE_XSAVES check is
necessary.

Fixes: 4d763b168e9c5 ("KVM: VMX: check CPUID before allowing read/write of IA32_XSS")
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH v6 01/10] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11185411
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D58CB14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:00:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C083D21D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:00:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728230AbfJKM7l (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 08:59:41 -0400
Received: from foss.arm.com ([217.140.110.172]:59318 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727589AbfJKM7l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 08:59:41 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 570791000;
        Fri, 11 Oct 2019 05:59:40 -0700 (PDT)
Received: from e112269-lin.cambridge.arm.com (e112269-lin.cambridge.arm.com
 [10.1.194.43])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 554E73F6C4;
        Fri, 11 Oct 2019 05:59:38 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v6 01/10] KVM: arm64: Document PV-time interface
Date: Fri, 11 Oct 2019 13:59:21 +0100
Message-Id: <20191011125930.40834-2-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191011125930.40834-1-steven.price@arm.com>
References: <20191011125930.40834-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduce a paravirtualization interface for KVM/arm64 based on the
"Arm Paravirtualized Time for Arm-Base Systems" specification DEN 0057A.

This only adds the details about "Stolen Time" as the details of "Live
Physical Time" have not been fully agreed.

User space can specify a reserved area of memory for the guest and
inform KVM to populate the memory with information on time that the host
kernel has stolen from the guest.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.rst   | 77 +++++++++++++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt | 14 +++++
 2 files changed, 91 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst

diff --git a/Documentation/virt/kvm/arm/pvtime.rst b/Documentation/virt/kvm/arm/pvtime.rst
new file mode 100644
index 000000000000..de949933ec78
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.rst
@@ -0,0 +1,77 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defines a standard for paravirtualised time
+support for AArch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+* PV_TIME_FEATURES: 0xC5000020
+* PV_TIME_ST:       0xC5000021
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_TIME_FEATURES
+    ============= ========    ==========
+    Function ID:  (uint32)    0xC5000020
+    PV_call_id:   (uint32)    The function to query for support.
+                              Currently only PV_TIME_ST is supported.
+    Return value: (int64)     NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+    ============= ========    ==========
+
+PV_TIME_ST
+    ============= ========    ==========
+    Function ID:  (uint32)    0xC5000021
+    Return value: (int64)     IPA of the stolen time data structure for this
+                              VCPU. On failure:
+                              NOT_SUPPORTED (-1)
+    ============= ========    ==========
+
+The IPA returned by PV_TIME_ST should be mapped by the guest as normal memory
+with inner and outer write back caching attributes, in the inner shareable
+domain. A total of 16 bytes from the IPA returned are guaranteed to be
+meaningfully filled by the hypervisor (see structure below).
+
+PV_TIME_ST returns the structure for the calling VCPU.
+
+Stolen Time
+-----------
+
+The structure pointed to by the PV_TIME_ST hypercall is as follows:
+
++-------------+-------------+-------------+----------------------------+
+| Field       | Byte Length | Byte Offset | Description                |
++=============+=============+=============+============================+
+| Revision    |      4      |      0      | Must be 0 for version 1.0  |
++-------------+-------------+-------------+----------------------------+
+| Attributes  |      4      |      4      | Must be 0                  |
++-------------+-------------+-------------+----------------------------+
+| Stolen time |      8      |      8      | Stolen time in unsigned    |
+|             |             |             | nanoseconds indicating how |
+|             |             |             | much time this VCPU thread |
+|             |             |             | was involuntarily not      |
+|             |             |             | running on a physical CPU. |
++-------------+-------------+-------------+----------------------------+
+
+All values in the structure are stored little-endian.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+For the user space interface see Documentation/virt/kvm/devices/vcpu.txt
+section "3. GROUP: KVM_ARM_VCPU_PVTIME_CTRL".
+
```
#### [PATCH v3 2/4] arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11185355
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDB841709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C477A222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570797621;
	bh=azhX068/Llc0POTSFJ7hQa0blYq+N0fFcX/ZEjAr9sY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=LY7BsxebhG+APTaYb229GXhunA0sgWA54vv9w176PaFrd6FTt3tMJRQZLYBq+hYgJ
	 sw/1TAdMJ6JwNrd3RWgCvMM8560mDmeR2+cnpmRGL0wqduxST8uOR/Z3AVyFYac4jK
	 zew3BrUZgvwf6KrV7uDOMif2LtKee4pQc+3/AVtw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728159AbfJKMkU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 08:40:20 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:48534 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727907AbfJKMkT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Oct 2019 08:40:19 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iIuDP-00062U-G7; Fri, 11 Oct 2019 14:40:15 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Murray <andrew.murray@arm.com>
Subject: [PATCH v3 2/4] arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64
 systems
Date: Fri, 11 Oct 2019 13:39:52 +0100
Message-Id: <20191011123954.31378-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191011123954.31378-1-maz@kernel.org>
References: <20191011123954.31378-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 mark.rutland@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, andrew.murray@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Of PMCR_EL0.LC, the ARMv8 ARM says:

	"In an AArch64 only implementation, this field is RES 1."

So be it.

Fixes: ab9468340d2bc ("arm64: KVM: Add access handler for PMCR register")
Reviewed-by: Andrew Murray <andrew.murray@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: fix overflow of zero page refcount with ksm running
##### From: Zhuang Yanying <ann.zhuangyanying@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Zhuang Yanying <ann.zhuangyanying@huawei.com>
X-Patchwork-Id: 11185557
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 041A814DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:56:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2B57222C9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:56:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728220AbfJKN4b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 09:56:31 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:3738 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727589AbfJKN4b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 09:56:31 -0400
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 794F6F73EC90C1896BBA;
        Fri, 11 Oct 2019 21:56:29 +0800 (CST)
Received: from localhost (10.133.215.230) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Fri, 11 Oct 2019
 21:56:23 +0800
From: Zhuang Yanying <ann.zhuangyanying@huawei.com>
To: <ann.zhuangyanying@huawei.com>, <linfeng23@huawei.com>,
        <pbonzini@redhat.com>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
CC: <weiqi4@huawei.com>, <weidong.huang@huawei.com>
Subject: [PATCH] KVM: fix overflow of zero page refcount with ksm running
Date: Fri, 11 Oct 2019 21:56:17 +0800
Message-ID: <1570802177-21212-1-git-send-email-ann.zhuangyanying@huawei.com>
X-Mailer: git-send-email 1.9.5.msysgit.1
MIME-Version: 1.0
X-Originating-IP: [10.133.215.230]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are testing Virtual Machine with KSM on v5.4-rc2 kernel,
and found the zero_page refcount overflow.
The cause of refcount overflow is increased in try_async_pf
(get_user_page) without being decreased in mmu_set_spte()
while handling ept violation.
In kvm_release_pfn_clean(), only unreserved page will call
put_page. However, zero page is reserved.
So, as well as creating and destroy vm, the refcount of
zero page will continue to increase until it overflows.

step1:
echo 10000 > /sys/kernel/pages_to_scan/pages_to_scan
echo 1 > /sys/kernel/pages_to_scan/run
echo 1 > /sys/kernel/pages_to_scan/use_zero_pages

step2:
just create several normal qemu kvm vms.
And destroy it after 10s.
Repeat this action all the time.

After a long period of time, all domains hang because
of the refcount of zero page overflow.

Qemu print error log as follow:
 …
 error: kvm run failed Bad address
 EAX=00006cdc EBX=00000008 ECX=80202001 EDX=078bfbfd
 ESI=ffffffff EDI=00000000 EBP=00000008 ESP=00006cc4
 EIP=000efd75 EFL=00010002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
 ES =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 CS =0008 00000000 ffffffff 00c09b00 DPL=0 CS32 [-RA]
 SS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 DS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 FS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 GS =0010 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
 LDT=0000 00000000 0000ffff 00008200 DPL=0 LDT
 TR =0000 00000000 0000ffff 00008b00 DPL=0 TSS32-busy
 GDT=     000f7070 00000037
 IDT=     000f70ae 00000000
 CR0=00000011 CR2=00000000 CR3=00000000 CR4=00000000
 DR0=0000000000000000 DR1=0000000000000000 DR2=0000000000000000 DR3=0000000000000000
 DR6=00000000ffff0ff0 DR7=0000000000000400
 EFER=0000000000000000
 Code=00 01 00 00 00 e9 e8 00 00 00 c7 05 4c 55 0f 00 01 00 00 00 <8b> 35 00 00 01 00 8b 3d 04 00 01 00 b8 d8 d3 00 00 c1 e0 08 0c ea a3 00 00 01 00 c7 05 04
 …

Meanwhile, a kernel warning is departed.

 [40914.836375] WARNING: CPU: 3 PID: 82067 at ./include/linux/mm.h:987 try_get_page+0x1f/0x30
 [40914.836412] CPU: 3 PID: 82067 Comm: CPU 0/KVM Kdump: loaded Tainted: G           OE     5.2.0-rc2 #5
 [40914.836415] RIP: 0010:try_get_page+0x1f/0x30
 [40914.836417] Code: 40 00 c3 0f 1f 84 00 00 00 00 00 48 8b 47 08 a8 01 75 11 8b 47 34 85 c0 7e 10 f0 ff 47 34 b8 01 00 00 00 c3 48 8d 78 ff eb e9 <0f> 0b 31 c0 c3 66 90 66 2e 0f 1f 84 00 0
 0 00 00 00 48 8b 47 08 a8
 [40914.836418] RSP: 0018:ffffb4144e523988 EFLAGS: 00010286
 [40914.836419] RAX: 0000000080000000 RBX: 0000000000000326 RCX: 0000000000000000
 [40914.836420] RDX: 0000000000000000 RSI: 00004ffdeba10000 RDI: ffffdf07093f6440
 [40914.836421] RBP: ffffdf07093f6440 R08: 800000424fd91225 R09: 0000000000000000
 [40914.836421] R10: ffff9eb41bfeebb8 R11: 0000000000000000 R12: ffffdf06bbd1e8a8
 [40914.836422] R13: 0000000000000080 R14: 800000424fd91225 R15: ffffdf07093f6440
 [40914.836423] FS:  00007fb60ffff700(0000) GS:ffff9eb4802c0000(0000) knlGS:0000000000000000
 [40914.836425] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
 [40914.836426] CR2: 0000000000000000 CR3: 0000002f220e6002 CR4: 00000000003626e0
 [40914.836427] DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
 [40914.836427] DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
 [40914.836428] Call Trace:
 [40914.836433]  follow_page_pte+0x302/0x47b
 [40914.836437]  __get_user_pages+0xf1/0x7d0
 [40914.836441]  ? irq_work_queue+0x9/0x70
 [40914.836443]  get_user_pages_unlocked+0x13f/0x1e0
 [40914.836469]  __gfn_to_pfn_memslot+0x10e/0x400 [kvm]
 [40914.836486]  try_async_pf+0x87/0x240 [kvm]
 [40914.836503]  tdp_page_fault+0x139/0x270 [kvm]
 [40914.836523]  kvm_mmu_page_fault+0x76/0x5e0 [kvm]
 [40914.836588]  vcpu_enter_guest+0xb45/0x1570 [kvm]
 [40914.836632]  kvm_arch_vcpu_ioctl_run+0x35d/0x580 [kvm]
 [40914.836645]  kvm_vcpu_ioctl+0x26e/0x5d0 [kvm]
 [40914.836650]  do_vfs_ioctl+0xa9/0x620
 [40914.836653]  ksys_ioctl+0x60/0x90
 [40914.836654]  __x64_sys_ioctl+0x16/0x20
 [40914.836658]  do_syscall_64+0x5b/0x180
 [40914.836664]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
 [40914.836666] RIP: 0033:0x7fb61cb6bfc7

Signed-off-by: LinFeng <linfeng23@huawei.com>
Signed-off-by: Zhuang Yanying <ann.zhuangyanying@huawei.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V3 1/7] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11184971
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22AF017EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 08:17:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EFE7621A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 08:17:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726692AbfJKIRk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 04:17:40 -0400
Received: from mx1.redhat.com ([209.132.183.28]:54966 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726317AbfJKIRk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 04:17:40 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id B3BC618CB8E0;
        Fri, 11 Oct 2019 08:17:39 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-241.pek2.redhat.com [10.72.12.241])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F13B8100EBDE;
        Fri, 11 Oct 2019 08:17:07 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V3 1/7] mdev: class id support
Date: Fri, 11 Oct 2019 16:15:51 +0800
Message-Id: <20191011081557.28302-2-jasowang@redhat.com>
In-Reply-To: <20191011081557.28302-1-jasowang@redhat.com>
References: <20191011081557.28302-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.63]);
 Fri, 11 Oct 2019 08:17:40 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
the first driver could be virtio-mdev. This means we need to add
device class id support in bus match method to pair the mdev device
and mdev driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
device with the match method for mdev bus.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 Documentation/driver-api/vfio-mediated-device.rst |  7 ++++++-
 drivers/gpu/drm/i915/gvt/kvmgt.c                  |  1 +
 drivers/s390/cio/vfio_ccw_ops.c                   |  1 +
 drivers/s390/crypto/vfio_ap_ops.c                 |  1 +
 drivers/vfio/mdev/mdev_core.c                     | 11 +++++++++++
 drivers/vfio/mdev/mdev_driver.c                   | 14 ++++++++++++++
 drivers/vfio/mdev/mdev_private.h                  |  1 +
 drivers/vfio/mdev/vfio_mdev.c                     |  6 ++++++
 include/linux/mdev.h                              |  8 ++++++++
 include/linux/mod_devicetable.h                   |  8 ++++++++
 samples/vfio-mdev/mbochs.c                        |  1 +
 samples/vfio-mdev/mdpy.c                          |  1 +
 samples/vfio-mdev/mtty.c                          |  1 +
 13 files changed, 60 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/4] KVM: arm64: pmu: Fix cycle counter truncation
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11185347
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6E8414ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A83F6214E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:19 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570797619;
	bh=V53P7Vn0aPiKYwrOMap7wcByveXMeM32VmJKA4bI76s=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=yZILFZQLA57lA0KKNtTsHnLLG0wcLtXqJEwEViHSfCPeNetnYc7ISjqy4tIVcD/4Y
	 fq/Coz3ghP4fCyurIM7O4XRF6vNXyz77iRrycgML9FwcLBmdbNbb7f/8bYZv+jauYH
	 QgvEXqJynwItNGKWVPi+QlrpsVwC6KFLPdLLJvkQ=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728154AbfJKMkS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 08:40:18 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:44547 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728059AbfJKMkS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Oct 2019 08:40:18 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iIuDO-00062U-Tv; Fri, 11 Oct 2019 14:40:15 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Murray <andrew.murray@arm.com>
Subject: [PATCH v3 1/4] KVM: arm64: pmu: Fix cycle counter truncation
Date: Fri, 11 Oct 2019 13:39:51 +0100
Message-Id: <20191011123954.31378-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191011123954.31378-1-maz@kernel.org>
References: <20191011123954.31378-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 mark.rutland@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, andrew.murray@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a counter is disabled, its value is sampled before the event
is being disabled, and the value written back in the shadow register.

In that process, the value gets truncated to 32bit, which is adequate
for any counter but the cycle counter (defined as a 64bit counter).

This obviously results in a corrupted counter, and things like
"perf record -e cycles" not working at all when run in a guest...
A similar, but less critical bug exists in kvm_pmu_get_counter_value.

Make the truncation conditional on the counter not being the cycle
counter, which results in a minor code reorganisation.

Fixes: 80f393a23be6 ("KVM: arm/arm64: Support chained PMU counters")
Reviewed-by: Andrew Murray <andrew.murray@arm.com>
Reported-by: Julien Thierry <julien.thierry.kdev@gmail.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/pmu.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
#### [PATCH RFC v1 1/2] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11185523
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 353D014ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:46:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E276222D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:46:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728782AbfJKNqI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 09:46:08 -0400
Received: from mx1.redhat.com ([209.132.183.28]:45610 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728767AbfJKNqH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 09:46:07 -0400
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7FD68CA1FE
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 13:46:06 +0000 (UTC)
Received: by mail-qt1-f197.google.com with SMTP id z21so9417865qtq.21
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 06:46:06 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:in-reply-to;
        bh=4QQJmzFzcB+s98hCdlFYskwk8yd9+Vjxg/V7InxbF+w=;
        b=om2C3s4sPfyNDalj8muV8Mckm65NAxUxbJFJ/EJK7llFN02Fr1rDY+QhTc09gGNGCN
         1nRPk6pV6Cw9GPVvg4sSj0veW4Mwn2eqwB+580iq2dYu8CVUPuLlUvb2oXGal1Tq286i
         aRwAWIMuztaO048487UEiP1oogYeFD1w3Zr2+qcM4l1h6ANHEgL+zqjTfUHiPWu8a3Zl
         2XtTCcZjv6/VViYX+BKJBKVtK4xXeKdikr1jyIoNt7o3dJHiUoUkv85ygYp/UVbS6ePG
         7mAFIgeifuTnwZ0LEAEJai6f7PUSjQiFGVMADwYEASYIreIVnoZ8zyK15/vnBokDhDou
         N7WA==
X-Gm-Message-State: APjAAAWu7iaxsyqvkJqGmEtZ14U3btg0iF1IvFmtzBToSkDiLFsMYlWE
        lGK6qvi4oxtIOKQz4+ytO0oOe08iCZPLa6jS9e1UThTNIT2Gnu3eHU4Yf0Czza6tkKL1OEWf6Q4
        DXl7HbBVOt5rt
X-Received: by 2002:a05:6214:841:: with SMTP id
 dg1mr15842899qvb.55.1570801564973;
        Fri, 11 Oct 2019 06:46:04 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzsR4qL0IbkdqWA0+KkKg2ppd90RIWdUOTuTCDdYP0zUBqv/SGi1pdYD4XNDCPUozXGp2EouQ==
X-Received: by 2002:a05:6214:841:: with SMTP id
 dg1mr15842829qvb.55.1570801564334;
        Fri, 11 Oct 2019 06:46:04 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 w85sm4201550qkb.57.2019.10.11.06.46.01
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 11 Oct 2019 06:46:03 -0700 (PDT)
Date: Fri, 11 Oct 2019 09:45:59 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH RFC v1 1/2] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20191011134358.16912-2-mst@redhat.com>
References: <20191011134358.16912-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20191011134358.16912-1-mst@redhat.com>
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

To simplify benchmarking, I kept the old code
around so one can switch back and forth by
writing into a module parameter.
This will go away in the final submission.

This patch causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
Next patch gets us back the performance by adding batching.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/test.c  |  17 ++-
 drivers/vhost/vhost.c | 299 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 3 files changed, 327 insertions(+), 5 deletions(-)

```
#### [PATCH net 1/2] vsock: add half-closed socket details in the implementation notes
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11185441
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B161F14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:08:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C22121D56
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:08:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728550AbfJKNIK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 09:08:10 -0400
Received: from mx1.redhat.com ([209.132.183.28]:36798 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728537AbfJKNIJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 09:08:09 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7F4703067288;
        Fri, 11 Oct 2019 13:08:09 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-54.ams2.redhat.com
 [10.36.117.54])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5AE6160A9F;
        Fri, 11 Oct 2019 13:08:07 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        Jorgen Hansen <jhansen@vmware.com>,
        "David S. Miller" <davem@davemloft.net>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Adit Ranadive <aditr@vmware.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH net 1/2] vsock: add half-closed socket details in the
 implementation notes
Date: Fri, 11 Oct 2019 15:07:57 +0200
Message-Id: <20191011130758.22134-2-sgarzare@redhat.com>
In-Reply-To: <20191011130758.22134-1-sgarzare@redhat.com>
References: <20191011130758.22134-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.48]);
 Fri, 11 Oct 2019 13:08:09 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmci_transport never allowed half-closed socket on the host side.
Since we want to have the same behaviour across all transports, we
add a section in the "Implementation notes".

Cc: Jorgen Hansen <jhansen@vmware.com>
Cc: Adit Ranadive <aditr@vmware.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/af_vsock.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH RESEND v6 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11184945
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94BC41575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 07:41:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7EE872064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 07:41:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727675AbfJKHlJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 03:41:09 -0400
Received: from mga04.intel.com ([192.55.52.120]:5858 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727068AbfJKHlJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 03:41:09 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Oct 2019 00:41:09 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,283,1566889200";
   d="scan'208";a="194257169"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga007.fm.intel.com with ESMTP; 11 Oct 2019 00:41:07 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH RESEND v6 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
Date: Fri, 11 Oct 2019 15:41:02 +0800
Message-Id: <20191011074103.30393-2-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191011074103.30393-1-tao3.xu@intel.com>
References: <20191011074103.30393-1-tao3.xu@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

Changes in v6:
    - remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set.
    (Paolo)
---
 target/i386/cpu.c | 2 +-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 6 ++++++
 3 files changed, 8 insertions(+), 1 deletion(-)

```
