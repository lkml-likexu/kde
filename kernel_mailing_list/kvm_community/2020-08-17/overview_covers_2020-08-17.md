

#### [RFC v2 0/2] add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Mon Aug 17 01:44:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11716271
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 731B0109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 01:43:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C2CB2075D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 01:43:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726444AbgHQBnA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 21:43:00 -0400
Received: from mga11.intel.com ([192.55.52.93]:61654 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726371AbgHQBm6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 21:42:58 -0400
IronPort-SDR: 
 nNiPLe5TSq9MN3mw+DZzhxHWpk34JxUA36F5KNMzM1xWovXvRwjs6HtHsdcaFUNamgHnJEL//h
 XUjcI/qpkR8A==
X-IronPort-AV: E=McAfee;i="6000,8403,9715"; a="152267100"
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="152267100"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Aug 2020 18:42:58 -0700
IronPort-SDR: 
 4BYtgEF5VWiZvdxpRg0rJlP1snIosYKYqDT02key2BLs69FlZlqgMX7ex+YmlRCu6BuC2CxlB8
 sapxYAjNwQUA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="471258529"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005.jf.intel.com with ESMTP; 16 Aug 2020 18:42:56 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC v2 0/2] add bus lock VM exit support
Date: Mon, 17 Aug 2020 09:44:57 +0800
Message-Id: <20200817014459.28782-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the support for bus lock VM exit in KVM. It is a sub-feature of bus
lock detection. Another sub-feature named bus lock debug exception is
blocked due to requirement to rework the HW design:
https://lore.kernel.org/lkml/87r1stmi1x.fsf@nanos.tec.linutronix.de/

In this patch series, the first patch applies Sean's refactor to
vcpu_vmx.exit_reason available at
https://patchwork.kernel.org/patch/11500659.
It is necessary as bus lock VM exit adds a new modifier bit(bit 26) in
exit_reason field in VMCS.

The second patch is the enabling work for bus lock VM exit. Add the
support to set the capability to enable bus lock vm exit. The current
implementation just exit to user space when handling the bus lock
detected in guest.

The concrete throttling policy in user space still needs to be
discussed. We can enforce ratelimit on bus lock in guest, just inject
some sleep time, or any other ideas?

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html


v1->v2 Changelogs:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.

Chenyi Qiang (1):
  KVM: VMX: Enable bus lock VM exit

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/include/asm/kvm_host.h    |  9 +++
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/include/asm/vmxfeatures.h |  1 +
 arch/x86/include/uapi/asm/kvm.h    |  1 +
 arch/x86/include/uapi/asm/vmx.h    |  4 +-
 arch/x86/kvm/vmx/capabilities.h    |  6 ++
 arch/x86/kvm/vmx/nested.c          | 42 ++++++++-----
 arch/x86/kvm/vmx/vmx.c             | 97 ++++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             | 25 +++++++-
 arch/x86/kvm/x86.c                 | 36 ++++++++++-
 arch/x86/kvm/x86.h                 |  5 ++
 include/uapi/linux/kvm.h           |  2 +
 12 files changed, 179 insertions(+), 50 deletions(-)
```
#### [RESEND RFC v2 0/2] add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Mon Aug 17 03:36:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11716375
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1301109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:34:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD3F8205CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:34:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726952AbgHQDeD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:34:03 -0400
Received: from mga04.intel.com ([192.55.52.120]:53823 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726385AbgHQDeD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:34:03 -0400
IronPort-SDR: 
 YIEa31w2swtxAqRNFC2VcIuSpRjC1bc2I1laB9FVuIoqlFZeNEighA1RlH2eA51OEHD9el+0Bx
 bHC9g54/ePfg==
X-IronPort-AV: E=McAfee;i="6000,8403,9715"; a="152033205"
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="152033205"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Aug 2020 20:34:02 -0700
IronPort-SDR: 
 PltlBRmDYfP48D4atAeBMnSdSCFuNuJtAkGrZLnksfFXSV/qsc/iEobDyooZkb6XAUgGi1yR2C
 PrCS7L9mYB/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,322,1592895600";
   d="scan'208";a="400075235"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by fmsmga001.fm.intel.com with ESMTP; 16 Aug 2020 20:34:00 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND RFC v2 0/2] add bus lock VM exit support
Date: Mon, 17 Aug 2020 11:36:02 +0800
Message-Id: <20200817033604.5836-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Resend to rebase on 5.9-rc1.
---

Add the support for bus lock VM exit in KVM. It is a sub-feature of bus
lock detection. Another sub-feature named bus lock debug exception is
blocked due to requirement to rework the HW design:
https://lore.kernel.org/lkml/87r1stmi1x.fsf@nanos.tec.linutronix.de/

In this patch series, the first patch applies Sean's refactor to
vcpu_vmx.exit_reason available at
https://patchwork.kernel.org/patch/11500659.
It is necessary as bus lock VM exit adds a new modifier bit(bit 26) in
exit_reason field in VMCS.

The second patch is the enabling work for bus lock VM exit. Add the
support to set the capability to enable bus lock vm exit. The current
implementation just exit to user space when handling the bus lock
detected in guest.

The concrete throttling policy in user space still needs to be
discussed. We can enforce ratelimit on bus lock in guest, just inject
some sleep time, or any other ideas?

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html


v1->v2 Changelogs:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.

Chenyi Qiang (1):
  KVM: VMX: Enable bus lock VM exit

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 arch/x86/include/asm/kvm_host.h    |  9 +++
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/include/asm/vmxfeatures.h |  1 +
 arch/x86/include/uapi/asm/kvm.h    |  1 +
 arch/x86/include/uapi/asm/vmx.h    |  4 +-
 arch/x86/kvm/vmx/capabilities.h    |  6 ++
 arch/x86/kvm/vmx/nested.c          | 42 ++++++++-----
 arch/x86/kvm/vmx/vmx.c             | 97 ++++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             | 25 +++++++-
 arch/x86/kvm/x86.c                 | 36 ++++++++++-
 arch/x86/kvm/x86.h                 |  5 ++
 include/uapi/linux/kvm.h           |  2 +
 12 files changed, 179 insertions(+), 50 deletions(-)
```
#### [PATCH 0/3] KVM: arm64: Some fixes and code adjustments for pvtime ST
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Mon Aug 17 03:37:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11716381
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D979618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:38:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 902E820708
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:38:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727068AbgHQDiS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:38:18 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:9743 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726420AbgHQDiQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:38:16 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 45AAB8ECA51EA1AF71C6;
        Mon, 17 Aug 2020 11:38:13 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 11:38:04 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Steven Price <steven.price@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 0/3] KVM: arm64: Some fixes and code adjustments for pvtime ST
Date: Mon, 17 Aug 2020 11:37:26 +0800
Message-ID: <20200817033729.10848-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During picking up pvtime LPT support for arm64, I do some trivial fixes for
pvtime ST.

Keqian Zhu (3):
  KVM: arm64: Some fixes of PV-time interface document
  KVM: uapi: Remove KVM_DEV_TYPE_ARM_PV_TIME in kvm_device_type
  KVM: arm64: Use kvm_write_guest_lock when init stolen time

 Documentation/virt/kvm/arm/pvtime.rst | 6 +++---
 arch/arm64/kvm/pvtime.c               | 6 +-----
 include/uapi/linux/kvm.h              | 2 --
 tools/include/uapi/linux/kvm.h        | 2 --
 4 files changed, 4 insertions(+), 12 deletions(-)
```
#### [PATCH 0/7] R4000 clock enhancements for Loongson
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
From patchwork Mon Aug 17 03:46:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11716401
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37FDB739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:47:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C36722B43
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 03:47:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="SeE8f4Bs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726888AbgHQDrl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Aug 2020 23:47:41 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38062 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726315AbgHQDrk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Aug 2020 23:47:40 -0400
Received: from vultr.net.flygoat.com (vultr.net.flygoat.com
 [IPv6:2001:19f0:6001:3633:5400:2ff:fe8c:553])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 58306C061388;
        Sun, 16 Aug 2020 20:47:40 -0700 (PDT)
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id B244B1FED2;
        Mon, 17 Aug 2020 03:47:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1597636056; bh=oWs/OR6uGAmxHxGeX7FqOfuNk1VxyUq9ikoG+zJSSlo=;
        h=From:To:Cc:Subject:Date:From;
        b=SeE8f4Bsk8v5HwBE92s2WK9WLsmYWvUXvxLjfOaOzszCjrx79qi3FPbEnCiaRsa9n
         /6ddDJ+tF5mM9foWZQbiDUJswvc4fUzFgsKCBJ5IT8ywjYbXREg9bFoeTJ+QBwrZ0O
         iHe1rePOJzxFY6rTuL4WtbAucL+4ZTix36nTA+tTzmPC0C0hkI6EVdqWieDkliuUgM
         4mrKC+qblbk4dmAy0UMKrXtMvuz0unwudD6IkBQCUBdsDFJf0FgdEPbuywPiVqOQhT
         zSE0ocSK6vWCx6KHK99NQs34WpGXnPOav3E9GU4wieOIXRrIHKSjP9E7hGUOlA5arQ
         X/J8G6CCAE4gg==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: linux-mips@vger.kernel.org
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>,
 Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
 Huacai Chen <chenhc@lemote.com>,
 Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
 Serge Semin <Sergey.Semin@baikalelectronics.ru>,
 Paul Burton <paulburton@kernel.org>, WANG Xuerui <git@xen0n.name>,
	=?utf-8?b?5ZGo55Cw5p2wIChaaG91IFlhbmppZSk=?=  <zhouyanjie@wanyeetech.com>,
 Liangliang Huang <huanglllzu@gmail.com>,
 afzal mohammed <afzal.mohd.ma@gmail.com>,
 "Peter Zijlstra (Intel)" <peterz@infradead.org>,
 Peter Xu <peterx@redhat.com>, Sergey Korolev <s.korolev@ndmsystems.com>,
 Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
 Marc Zyngier <maz@kernel.org>, Anup Patel <anup.patel@wdc.com>,
 Ming Lei <ming.lei@redhat.com>, Thomas Gleixner <tglx@linutronix.de>,
 Atish Patra <atish.patra@wdc.com>, Ulf Hansson <ulf.hansson@linaro.org>,
 Daniel Jordan <daniel.m.jordan@oracle.com>,
 Steven Price <steven.price@arm.com>, Mike Leach <mike.leach@linaro.org>,
 Michael Kelley <mikelley@microsoft.com>, linux-kernel@vger.kernel.org,
 kvm@vger.kernel.org
Subject: [PATCH 0/7] R4000 clock enhancements for Loongson
Date: Mon, 17 Aug 2020 11:46:39 +0800
Message-Id: <20200817034701.3515721-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.28.0.rc1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Jiaxun Yang (7):
  MIPS: sync-r4k: Rework to be many cores firendly
  MIPS: time: Use CPUHUP to handle r4k timer
  MIPS: Kconfig: Always select SYNC_R4K if both SMP and r4k timer is
    enabled
  MIPS: Loongson64: Remove custom count sync procudure
  MIPS: cevt-r4k: Don't handle IRQ if clockevent is not enabled
  MIPS: cevt-r4k: Enable intimer for Loongson CPUs with extimer
  MIPS: KVM: Don't use htimer when INTIMER is disabled

 arch/mips/Kconfig                    |  10 +-
 arch/mips/include/asm/cpu-features.h |   4 +
 arch/mips/include/asm/cpu.h          |   1 +
 arch/mips/include/asm/r4k-timer.h    |   5 -
 arch/mips/include/asm/smp.h          |   1 -
 arch/mips/include/asm/time.h         |  28 +++---
 arch/mips/kernel/cevt-r4k.c          |  65 ++++++++++--
 arch/mips/kernel/cpu-probe.c         |   6 +-
 arch/mips/kernel/smp.c               |   5 -
 arch/mips/kernel/sync-r4k.c          | 143 ++++++++++++---------------
 arch/mips/kernel/time.c              |  22 ++++-
 arch/mips/kvm/vz.c                   |   6 ++
 arch/mips/loongson64/smp.c           |  32 +-----
 include/linux/cpuhotplug.h           |   1 +
 14 files changed, 173 insertions(+), 156 deletions(-)
```
#### [RFC PATCH 0/5] KVM: arm64: Add pvtime LPT support
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Mon Aug 17 08:41:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11717069
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 276BD15E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 08:41:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A8F7207FB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 08:41:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727776AbgHQIld (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 04:41:33 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:45200 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726361AbgHQIl2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 04:41:28 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 724AC236C0FF1FBF5E6D;
        Mon, 17 Aug 2020 16:41:22 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 16:41:12 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [RFC PATCH 0/5] KVM: arm64: Add pvtime LPT support
Date: Mon, 17 Aug 2020 16:41:05 +0800
Message-ID: <20200817084110.2672-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This patch series picks up the LPT pvtime feature originally developed
by Steven Price: https://patchwork.kernel.org/cover/10726499/

Backgroud:

There is demand for cross-platform migration, which means we have to
solve different CPU features and arch counter frequency between hosts.
This patch series can solve the latter problem.

About LPT:

This implements support for Live Physical Time (LPT) which provides the
guest with a method to derive a stable counter of time during which the
guest is executing even when the guest is being migrated between hosts
with different physical counter frequencies.

Changes on Steven Price's work:
1. LPT structure: use symmatical semantics of scale multiplier, and use
   fraction bits instead of "shift" to make everything clear.
2. Structure allocation: host kernel does not allocates the LPT structure,
   instead it is allocated by userspace through VM attributes. The save/restore
   functionality can be removed.
3. Since LPT structure just need update once for each guest run, add a flag to
   indicate the update status. This has two benifits: 1) avoid multiple update
   by each vCPUs. 2) If the update flag is not set, then return NOT SUPPORT for
   coressponding guest HVC call.
4. Add VM device attributes interface for userspace configuration.
5. Add a base LPT read/write layer to reduce code.
6. Support ptimer scaling.
7. Support timer event stream translation.

Things need concern:
1. https://developer.arm.com/docs/den0057/a needs update.
2. If a guest fails to initialize and use LPT, when it migrates to a host with
   different native frequency, it will see the virtual counter jump. However
   this concern is not a problem.
   1) Guest does not support LPT or host does not enable LPT: we won't migrate
      guest to a host with different frequency.
   2) Guest kernel faces problem when initilize LPT: guest can not boot up, so
      counter jump is not a problem at this situation.


Patch 2 and 3 implement host KVM part.
Patch 4 and 5 implement guest driver part.

Keqian Zhu (5):
  KVM: arm64: Document pvtime LPT interface
  KVM: arm64: Support Live Physical Time reporting
  KVM: arm64: Provide VM device attributes for LPT time
  clocksource: arm_arch_timer: Add pvtime LPT initialization
  clocksource: arm_arch_timer: Use pvtime LPT

 Documentation/virt/kvm/arm/pvtime.rst |  78 +++++++++++--
 Documentation/virt/kvm/devices/vm.rst |  30 +++++
 arch/arm64/include/asm/arch_timer.h   | 179 ++++++++++++++++++++++++++--
 arch/arm64/include/asm/kvm_host.h     |  14 +++
 arch/arm64/include/uapi/asm/kvm.h     |   5 +
 arch/arm64/kvm/arm.c                  |  71 ++++++++++++
 arch/arm64/kvm/hypercalls.c           |   5 +
 arch/arm64/kvm/pvtime.c               | 212 +++++++++++++++++++++++++++++++++-
 drivers/clocksource/arm_arch_timer.c  | 120 +++++++++++++++----
 9 files changed, 669 insertions(+), 45 deletions(-)
```
#### [PATCH v2 0/2] KVM: arm64: Some fixes and code adjustments for pvtime
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Mon Aug 17 11:07:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11718023
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECE54138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 11:08:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE1F220738
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 11:08:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727898AbgHQLIM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 07:08:12 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:58546 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726617AbgHQLIG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 07:08:06 -0400
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 20E8964B12CB55BA6D23;
        Mon, 17 Aug 2020 19:08:01 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 19:07:50 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 0/2] KVM: arm64: Some fixes and code adjustments for pvtime
 ST
Date: Mon, 17 Aug 2020 19:07:26 +0800
Message-ID: <20200817110728.12196-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During picking up pvtime LPT support for arm64, I do some trivial fixes for
pvtime ST.

change log:

v2:
 - Add Andrew's and Steven's R-b.
 - Correct commit message of the first patch.
 - Drop the second patch.

Keqian Zhu (2):
  KVM: arm64: Some fixes of PV-time interface document
  KVM: arm64: Use kvm_write_guest_lock when init stolen time

 Documentation/virt/kvm/arm/pvtime.rst | 6 +++---
 arch/arm64/kvm/pvtime.c               | 6 +-----
 2 files changed, 4 insertions(+), 8 deletions(-)
```
#### [PATCH 0/2] clocksource: arm_arch_timer: Some fixes and code
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Mon Aug 17 12:24:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11718133
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E017618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 12:24:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C82B20658
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 12:24:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728211AbgHQMYi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 08:24:38 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:9750 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726265AbgHQMYg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 08:24:36 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 9E07146F75F97D4A4037;
        Mon, 17 Aug 2020 20:24:25 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS401-HUB.china.huawei.com (10.3.19.201) with Microsoft SMTP Server id
 14.3.487.0; Mon, 17 Aug 2020 20:24:18 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 0/2] clocksource: arm_arch_timer: Some fixes and code
 adjustment
Date: Mon, 17 Aug 2020 20:24:13 +0800
Message-ID: <20200817122415.6568-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During picking up pvtime LPT support for arm64, I found some trivial bugs for
arm arch_timer driver.

Keqian Zhu (2):
  clocksource: arm_arch_timer: Simplify and fix count reader code logic
  clocksource: arm_arch_timer: Correct fault programming of
    CNTKCTL_EL1.EVNTI

 arch/arm/include/asm/arch_timer.h    | 14 ++--------
 arch/arm64/include/asm/arch_timer.h  | 24 ++--------------
 drivers/clocksource/arm_arch_timer.c | 53 ++++++------------------------------
 3 files changed, 13 insertions(+), 78 deletions(-)
```
#### [PATCH v7 00/18] Add support for Nitro Enclaves
##### From: Andra Paraschiv <andraprs@amazon.com>

```c
From patchwork Mon Aug 17 13:09:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andra Paraschiv <andraprs@amazon.com>
X-Patchwork-Id: 11718205
Return-Path: <SRS0=mOyg=B3=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 403B4618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 13:10:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13DF620716
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Aug 2020 13:10:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="aAWVUMcq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728349AbgHQNKb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 09:10:31 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:47701 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727931AbgHQNKa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 09:10:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1597669828; x=1629205828;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=5et6dxPLC0TaATG3K/7oCdqF4oZ8dwdK8kNpRMEV1vU=;
  b=aAWVUMcqt9tE8o3uPsoGdrjTRaQFMXMCbx2t75jcT/JvL1wyVXgnWwXP
   riK3p5AHnNx9G06IdTCW9SL5jx+CedZJCmctL0CJ1HzMdnzO0fcijZj+/
   tIlgu2dk4IPW/eKdJCsPyCAndosFI4eVmVsROxNayWVEJP8lT4QycN96R
   s=;
X-IronPort-AV: E=Sophos;i="5.76,322,1592870400";
   d="scan'208";a="67311035"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-2c-c6afef2e.us-west-2.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 17 Aug 2020 13:10:25 +0000
Received: from EX13MTAUEA001.ant.amazon.com
 (pdx4-ws-svc-p6-lb7-vlan2.pdx.amazon.com [10.170.41.162])
        by email-inbound-relay-2c-c6afef2e.us-west-2.amazon.com (Postfix) with
 ESMTPS id 6E6EDA24C6;
        Mon, 17 Aug 2020 13:10:24 +0000 (UTC)
Received: from EX13D16EUB001.ant.amazon.com (10.43.166.28) by
 EX13MTAUEA001.ant.amazon.com (10.43.61.82) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 17 Aug 2020 13:10:23 +0000
Received: from 38f9d34ed3b1.ant.amazon.com (10.43.162.140) by
 EX13D16EUB001.ant.amazon.com (10.43.166.28) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 17 Aug 2020 13:10:14 +0000
From: Andra Paraschiv <andraprs@amazon.com>
To: linux-kernel <linux-kernel@vger.kernel.org>
CC: Anthony Liguori <aliguori@amazon.com>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Colm MacCarthaigh <colmmacc@amazon.com>,
        "David Duncan" <davdunc@amazon.com>,
        Bjoern Doebel <doebel@amazon.de>,
        "David Woodhouse" <dwmw@amazon.co.uk>,
        Frank van der Linden <fllinden@amazon.com>,
        Alexander Graf <graf@amazon.de>,
        Greg KH <gregkh@linuxfoundation.org>,
        "Karen Noel" <knoel@redhat.com>,
        Martin Pohlack <mpohlack@amazon.de>,
        Matt Wilson <msw@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Balbir Singh <sblbir@amazon.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Stefan Hajnoczi" <stefanha@redhat.com>,
        Stewart Smith <trawets@amazon.com>,
        "Uwe Dannowski" <uwed@amazon.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        kvm <kvm@vger.kernel.org>,
        ne-devel-upstream <ne-devel-upstream@amazon.com>,
        Andra Paraschiv <andraprs@amazon.com>
Subject: [PATCH v7 00/18] Add support for Nitro Enclaves
Date: Mon, 17 Aug 2020 16:09:45 +0300
Message-ID: <20200817131003.56650-1-andraprs@amazon.com>
X-Mailer: git-send-email 2.20.1 (Apple Git-117)
MIME-Version: 1.0
X-Originating-IP: [10.43.162.140]
X-ClientProxiedBy: EX13D16UWC003.ant.amazon.com (10.43.162.15) To
 EX13D16EUB001.ant.amazon.com (10.43.166.28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Nitro Enclaves (NE) is a new Amazon Elastic Compute Cloud (EC2) capability
that allows customers to carve out isolated compute environments within EC2
instances [1].

For example, an application that processes sensitive data and runs in a VM,
can be separated from other applications running in the same VM. This
application then runs in a separate VM than the primary VM, namely an enclave.

An enclave runs alongside the VM that spawned it. This setup matches low latency
applications needs. The resources that are allocated for the enclave, such as
memory and CPUs, are carved out of the primary VM. Each enclave is mapped to a
process running in the primary VM, that communicates with the NE driver via an
ioctl interface.

In this sense, there are two components:

1. An enclave abstraction process - a user space process running in the primary
VM guest that uses the provided ioctl interface of the NE driver to spawn an
enclave VM (that's 2 below).

There is a NE emulated PCI device exposed to the primary VM. The driver for this
new PCI device is included in the NE driver.

The ioctl logic is mapped to PCI device commands e.g. the NE_START_ENCLAVE ioctl
maps to an enclave start PCI command. The PCI device commands are then
translated into  actions taken on the hypervisor side; that's the Nitro
hypervisor running on the host where the primary VM is running. The Nitro
hypervisor is based on core KVM technology.

2. The enclave itself - a VM running on the same host as the primary VM that
spawned it. Memory and CPUs are carved out of the primary VM and are dedicated
for the enclave VM. An enclave does not have persistent storage attached.

The memory regions carved out of the primary VM and given to an enclave need to
be aligned 2 MiB / 1 GiB physically contiguous memory regions (or multiple of
this size e.g. 8 MiB). The memory can be allocated e.g. by using hugetlbfs from
user space [2][3]. The memory size for an enclave needs to be at least 64 MiB.
The enclave memory and CPUs need to be from the same NUMA node.

An enclave runs on dedicated cores. CPU 0 and its CPU siblings need to remain
available for the primary VM. A CPU pool has to be set for NE purposes by an
user with admin capability. See the cpu list section from the kernel
documentation [4] for how a CPU pool format looks.

An enclave communicates with the primary VM via a local communication channel,
using virtio-vsock [5]. The primary VM has virtio-pci vsock emulated device,
while the enclave VM has a virtio-mmio vsock emulated device. The vsock device
uses eventfd for signaling. The enclave VM sees the usual interfaces - local
APIC and IOAPIC - to get interrupts from virtio-vsock device. The virtio-mmio
device is placed in memory below the typical 4 GiB.

The application that runs in the enclave needs to be packaged in an enclave
image together with the OS ( e.g. kernel, ramdisk, init ) that will run in the
enclave VM. The enclave VM has its own kernel and follows the standard Linux
boot protocol.

The kernel bzImage, the kernel command line, the ramdisk(s) are part of the
Enclave Image Format (EIF); plus an EIF header including metadata such as magic
number, eif version, image size and CRC.

Hash values are computed for the entire enclave image (EIF), the kernel and
ramdisk(s). That's used, for example, to check that the enclave image that is
loaded in the enclave VM is the one that was intended to be run.

These crypto measurements are included in a signed attestation document
generated by the Nitro Hypervisor and further used to prove the identity of the
enclave; KMS is an example of service that NE is integrated with and that checks
the attestation doc.

The enclave image (EIF) is loaded in the enclave memory at offset 8 MiB. The
init process in the enclave connects to the vsock CID of the primary VM and a
predefined port - 9000 - to send a heartbeat value - 0xb7. This mechanism is
used to check in the primary VM that the enclave has booted.

If the enclave VM crashes or gracefully exits, an interrupt event is received by
the NE driver. This event is sent further to the user space enclave process
running in the primary VM via a poll notification mechanism. Then the user space
enclave process can exit.

Thank you.

Andra

[1] https://aws.amazon.com/ec2/nitro/nitro-enclaves/
[2] https://www.kernel.org/doc/Documentation/vm/hugetlbpage.txt
[3] https://lwn.net/Articles/807108/
[4] https://www.kernel.org/doc/html/latest/admin-guide/kernel-parameters.html
[5] https://man7.org/linux/man-pages/man7/vsock.7.html
---

Patch Series Changelog

The patch series is built on top of v5.9-rc1.

GitHub repo branch for the latest version of the patch series:

* https://github.com/andraprs/linux/tree/ne-driver-upstream-v7 

v6 -> v7

* Rebase on top of v5.9-rc1.
* Use the NE misc device parent field to get the NE PCI device.
* Update the naming and add more comments to make more clear the logic of
  handling full CPU cores and dedicating them to the enclave.
* Remove, for now, the dependency on ARM64 arch in Kconfig. x86 is currently
  supported, with Arm to come afterwards. The NE kernel driver can be currently
  built for aarch64 arch.
* Clarify in the ioctls documentation that the return value is -1 and errno is
  set on failure.
* Update the error code value for NE_ERR_INVALID_MEM_REGION_SIZE as it gets in
  user space as value 25 (ENOTTY) instead of 515. Update the NE custom error
  codes values range to not be the same as the ones defined in
  include/linux/errno.h, although these are not propagated to user space.
* Update the documentation to include references to the NE PCI device id and
  MMIO bar.
* Update check for duplicate user space memory regions to cover additional
  possible scenarios.
* Calculate the number of threads per core and not use smp_num_siblings that is
  x86 specific.
* v6: https://lore.kernel.org/lkml/20200805091017.86203-1-andraprs@amazon.com/

v5 -> v6

* Rebase on top of v5.8.
* Update documentation to kernel-doc format.
* Update sample to include the enclave image loading logic.
* Remove the ioctl to query API version.
* Check for invalid provided flags field via ioctl calls args.
* Check for duplicate provided user space memory regions.
* Check for aligned memory regions.
* Include, in the sample, usage info for NUMA-aware hugetlb config.
* v5: https://lore.kernel.org/lkml/20200715194540.45532-1-andraprs@amazon.com/

v4 -> v5

* Rebase on top of v5.8-rc5.
* Add more details about the ioctl calls usage e.g. error codes.
* Update the ioctl to set an enclave vCPU to not return a fd.
* Add specific NE error codes.
* Split the NE CPU pool in CPU cores cpumasks.
* Remove log on copy_from_user() / copy_to_user() failure.
* Release the reference to the NE PCI device on failure paths.
* Close enclave fd on copy_to_user() failure.
* Set empty string in case of invalid NE CPU pool sysfs value.
* Early exit on NE CPU pool setup if enclave(s) already running.
* Add more sanity checks for provided vCPUs e.g. maximum possible value.
* Split logic for checking if a vCPU is in pool / getting a vCPU from pool.
* Exit without unpinning the pages on NE PCI dev request failure.
* Add check for the memory region user space address alignment.
* Update the logic to set memory region to not have a hardcoded check for 2 MiB.
* Add arch dependency for Arm / x86.
* v4: https://lore.kernel.org/lkml/20200622200329.52996-1-andraprs@amazon.com/

v3 -> v4

* Rebase on top of v5.8-rc2.
* Add NE API version and the corresponding ioctl call.
* Add enclave / image load flags options.
* Decouple NE ioctl interface from KVM API.
* Remove the "packed" attribute and include padding in the NE data structures.
* Update documentation based on the changes from v4.
* Update sample to match the updates in v4.
* Remove the NE CPU pool init during NE kernel module loading.
* Setup the NE CPU pool at runtime via a sysfs file for the kernel parameter.
* Check if the enclave memory and CPUs are from the same NUMA node.
* Add minimum enclave memory size definition.
* v3: https://lore.kernel.org/lkml/20200525221334.62966-1-andraprs@amazon.com/ 

v2 -> v3

* Rebase on top of v5.7-rc7.
* Add changelog to each patch in the series.
* Remove "ratelimited" from the logs that are not in the ioctl call paths.
* Update static calls sanity checks.
* Remove file ops that do nothing for now.
* Remove GPL additional wording as SPDX-License-Identifier is already in place.
* v2: https://lore.kernel.org/lkml/20200522062946.28973-1-andraprs@amazon.com/

v1 -> v2

* Rebase on top of v5.7-rc6.
* Adapt codebase based on feedback from v1.
* Update ioctl number definition - major and minor.
* Add sample / documentation for the ioctl interface basic flow usage.
* Update cover letter to include more context on the NE overall.
* Add fix for the enclave / vcpu fd creation error cleanup path.
* Add fix reported by kbuild test robot <lkp@intel.com>.
* v1: https://lore.kernel.org/lkml/20200421184150.68011-1-andraprs@amazon.com/

---

Andra Paraschiv (18):
  nitro_enclaves: Add ioctl interface definition
  nitro_enclaves: Define the PCI device interface
  nitro_enclaves: Define enclave info for internal bookkeeping
  nitro_enclaves: Init PCI device driver
  nitro_enclaves: Handle PCI device command requests
  nitro_enclaves: Handle out-of-band PCI device events
  nitro_enclaves: Init misc device providing the ioctl interface
  nitro_enclaves: Add logic for creating an enclave VM
  nitro_enclaves: Add logic for setting an enclave vCPU
  nitro_enclaves: Add logic for getting the enclave image load info
  nitro_enclaves: Add logic for setting an enclave memory region
  nitro_enclaves: Add logic for starting an enclave
  nitro_enclaves: Add logic for terminating an enclave
  nitro_enclaves: Add Kconfig for the Nitro Enclaves driver
  nitro_enclaves: Add Makefile for the Nitro Enclaves driver
  nitro_enclaves: Add sample for ioctl interface usage
  nitro_enclaves: Add overview documentation
  MAINTAINERS: Add entry for the Nitro Enclaves driver

 Documentation/nitro_enclaves/ne_overview.rst  |   87 +
 .../userspace-api/ioctl/ioctl-number.rst      |    5 +-
 MAINTAINERS                                   |   13 +
 drivers/virt/Kconfig                          |    2 +
 drivers/virt/Makefile                         |    2 +
 drivers/virt/nitro_enclaves/Kconfig           |   20 +
 drivers/virt/nitro_enclaves/Makefile          |   11 +
 drivers/virt/nitro_enclaves/ne_misc_dev.c     | 1648 +++++++++++++++++
 drivers/virt/nitro_enclaves/ne_misc_dev.h     |   99 +
 drivers/virt/nitro_enclaves/ne_pci_dev.c      |  606 ++++++
 drivers/virt/nitro_enclaves/ne_pci_dev.h      |  327 ++++
 include/linux/nitro_enclaves.h                |   11 +
 include/uapi/linux/nitro_enclaves.h           |  337 ++++
 samples/nitro_enclaves/.gitignore             |    2 +
 samples/nitro_enclaves/Makefile               |   16 +
 samples/nitro_enclaves/ne_ioctl_sample.c      |  850 +++++++++
 16 files changed, 4035 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/nitro_enclaves/ne_overview.rst
 create mode 100644 drivers/virt/nitro_enclaves/Kconfig
 create mode 100644 drivers/virt/nitro_enclaves/Makefile
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_misc_dev.h
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.c
 create mode 100644 drivers/virt/nitro_enclaves/ne_pci_dev.h
 create mode 100644 include/linux/nitro_enclaves.h
 create mode 100644 include/uapi/linux/nitro_enclaves.h
 create mode 100644 samples/nitro_enclaves/.gitignore
 create mode 100644 samples/nitro_enclaves/Makefile
 create mode 100644 samples/nitro_enclaves/ne_ioctl_sample.c
```
