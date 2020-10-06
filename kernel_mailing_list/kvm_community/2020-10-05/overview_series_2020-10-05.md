#### [PATCH 01/13] x86/apic: Use x2apic in guest kernels even with unusable CPUs.
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11816859
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FD5892C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 15:40:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52B1C2075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 15:40:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="WIhf+2hP"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728785AbgJEPkz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 11:40:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48710 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727484AbgJEP3A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Oct 2020 11:29:00 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2782FC0613A9;
        Mon,  5 Oct 2020 08:29:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=dED8vHaXb6tu8ZuPD0ZmCjPUI1h1W+XMTR/qU+F/+qA=;
 b=WIhf+2hPDPoXekPiE44xibj2Ky
        7et55tmHoeyyRNG0QSMj0O5uiSAe7fH8lIWeImmTUWXJdhFyoRUJXB2NwNoZbbeAloKEWiJMfHQqU
        AIMKGPslEj3EXYaAXJ2efV312g30akfbxdd94NCVvesfA+lM3kq3zvNdtxsqxF9/Ry24PGNy3DOnN
        M0+UoYi1eMNSQdhx3u8ONVLlE1M7LFwvKo8ohvojFdzPB5eUE1YvtgtK5YVUhKX3rmTRYhy9wvQc9
        lXsEnfgJEGO8zkIVdh2NviZGBnRsVPLQRABJmLuL/ywyUUQSbce+l4UxG8e4Lo1hjy8jkYOVj63gN
        W+5SSyrw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kPSQ5-0004MH-8v; Mon, 05 Oct 2020 15:28:57 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kPSQ4-0045QD-7l; Mon, 05 Oct 2020 16:28:56 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: iommu <iommu@lists.linux-foundation.org>,
        kvm <kvm@vger.kernel.org>, linux-hyperv@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH 01/13] x86/apic: Use x2apic in guest kernels even with
 unusable CPUs.
Date: Mon,  5 Oct 2020 16:28:44 +0100
Message-Id: <20201005152856.974112-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <77e64f977f559412f62b467fd062d051ea288f14.camel@infradead.org>
References: <77e64f977f559412f62b467fd062d051ea288f14.camel@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

If the BIOS has enabled x2apic mode, then leave it enabled and don't
fall back to xapic just because some CPUs can't be targeted.

Previously, if there are CPUs with APIC IDs > 255, the kernel will
disable x2apic and fall back to xapic. And then not use the additional
CPUs anyway, since xapic can't target them either.

In fact, xapic mode can target even *fewer* CPUs, since it can't use
the one with APIC ID 255 either. Using x2apic instead gives us at least
one more CPU without needing interrupt remapping in the guest.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/include/asm/apic.h        |  1 +
 arch/x86/kernel/apic/apic.c        | 18 ++++++++++++++----
 arch/x86/kernel/apic/x2apic_phys.c |  9 +++++++++
 3 files changed, 24 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: VMX: Fix x2APIC MSR intercept handling on !APICV platforms
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11817461
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E61EC112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 19:55:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D419621527
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 19:55:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729504AbgJETzw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 15:55:52 -0400
Received: from mga01.intel.com ([192.55.52.88]:42023 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729424AbgJETzw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Oct 2020 15:55:52 -0400
IronPort-SDR: 
 PcqCs+WCA38lv1njoTZGWKkjJPcX2ca6RnholZCh8/AELOwOC1JzY/liz8yPAfJobq66zY+Yt0
 fSm4sLescFeA==
X-IronPort-AV: E=McAfee;i="6000,8403,9765"; a="181660128"
X-IronPort-AV: E=Sophos;i="5.77,340,1596524400";
   d="scan'208";a="181660128"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Oct 2020 12:55:37 -0700
IronPort-SDR: 
 DbCMeOUhst1V5ODW4G0ihEwi7ZnnQ0aARCr7wK7vaGF+RFPiaUir8bElz/dTo4u2gU2TqX6Jkk
 ZnjIIuAyZG8g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,340,1596524400";
   d="scan'208";a="353550110"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 05 Oct 2020 12:55:36 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH 1/2] KVM: VMX: Fix x2APIC MSR intercept handling on !APICV
 platforms
Date: Mon,  5 Oct 2020 12:55:31 -0700
Message-Id: <20201005195532.8674-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201005195532.8674-1-sean.j.christopherson@intel.com>
References: <20201005195532.8674-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Xu <peterx@redhat.com>

Fix an inverted flag for intercepting x2APIC MSRs and intercept writes
by default, even when APICV is enabled.

Fixes: 3eb900173c71 ("KVM: x86: VMX: Prevent MSR passthrough when MSR access is denied")
Not-signed-off-by: Peter Xu <peterx@redhat.com>
[sean: added changelog]
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: filter guest NX capability for cpuid2
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11816735
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B39892C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 14:59:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0E5D820874
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 14:59:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726614AbgJEO7a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 10:59:30 -0400
Received: from out30-44.freemail.mail.aliyun.com ([115.124.30.44]:59701 "EHLO
        out30-44.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726567AbgJEO7a (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 5 Oct 2020 10:59:30 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R571e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04426;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0UB3KJNM_1601909961;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0UB3KJNM_1601909961)
          by smtp.aliyun-inc.com(127.0.0.1);
          Mon, 05 Oct 2020 22:59:22 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
Subject: [PATCH] KVM: x86: filter guest NX capability for cpuid2
Date: Mon,  5 Oct 2020 22:59:21 +0800
Message-Id: <20201005145921.84848-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.24.3 (Apple Git-128)
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Original KVM_SET_CPUID has removed NX on non-NX hosts as it did
before. but KVM_SET_CPUID2 does not. The two should be consistent.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/x86/kvm/cpuid.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] target/i386: Support up to 32768 CPUs without IRQ remappingFrom: David Woodhouse <dwmw2@infradead.org>
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11816693
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C638992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 14:18:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 771B620757
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 14:18:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="0aenLb1L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725994AbgJEOS3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 10:18:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37716 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725932AbgJEOS3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Oct 2020 10:18:29 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D7261C0613CE
        for <kvm@vger.kernel.org>; Mon,  5 Oct 2020 07:18:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:Date:Cc:To:
        From:Subject:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=n5Aik+8HqXQo4VS8CWv9//329A+WLNWB/5I26cclU14=;
 b=0aenLb1Lj/2xdziVy4yUFN0a/0
        qQF6ZrTAOo6mCpeiTKOU1uyYlqPHk++o81ad2OOAKpWlKkGMWJKaggdLH8tmREOjSKbkayg945sVj
        qgYtNtey+FC0SmaXIO5RUYyddnK+M6xyqzKBW4JzHniBLfvJe3CEqbHfe47ce3IIV2b5H7pYjJkQn
        LodSR3zZ80NsS6agyjOEMe5a80yTS+Jw5UBY29Kj2+ajq/UJ+cvg3MVemxVTXZixyBE3tSX6+VI7r
        JQRTl2Azixd6jx6IzKYuKE0TQpkjZ0gHqfZGOvfqNo4H0ZJC2M/cn4gt17QjS6BS0HFiNMWz/7XOn
        ZilcNWjA==;
Received: from 54-240-197-232.amazon.com ([54.240.197.232]
 helo=u3832b3a9db3152.ant.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kPRJl-0000Av-7o; Mon, 05 Oct 2020 14:18:21 +0000
Message-ID: <78097f9218300e63e751e077a0a5ca029b56ba46.camel@infradead.org>
Subject: [PATCH] target/i386: Support up to 32768 CPUs without IRQ remapping
From: David Woodhouse <dwmw2@infradead.org>
To: qemu-devel <qemu-devel@nongnu.org>
Cc: x86 <x86@kernel.org>, kvm <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Date: Mon, 05 Oct 2020 15:18:19 +0100
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The IOAPIC has an 'Extended Destination ID' field in its RTE, which maps
to bits 11-4 of the MSI address. Since those address bits fall within a
given 4KiB page they were historically non-trivial to use on real hardware.

The Intel IOMMU uses the lowest bit to indicate a remappable format MSI,
and then the remaining 7 bits are part of the index.

Where the remappable format bit isn't set, we can actually use the other
seven to allow external (IOAPIC and MSI) interrupts to reach up to 32768
CPUs instead of just the 255 permitted on bare metal.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 hw/i386/kvm/apic.c                          |  7 ++
 hw/i386/pc.c                                | 16 ++---
 include/standard-headers/asm-x86/kvm_para.h |  1 +
 target/i386/cpu.c                           |  5 +-
 target/i386/kvm.c                           | 74 +++++++++++++++------
 target/i386/kvm_i386.h                      |  2 +
 6 files changed, 75 insertions(+), 30 deletions(-)

```
#### [PATCH v6 01/10] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 157 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 193 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
