#### [PATCH 1/2] KVM: arm/arm64: Only skip MMIO insn once
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11112067
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 136DD1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD7952082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1566578141;
	bh=5O+Aa0BGrHvPzzjFxMtTqxenZbPJvuLEBvni5H3GmiE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=P1dLg/QmRQK7ZAVvuP1WBrGBzhXXOYBgLQpUgftpKRppY02Og9gW+k2fUzWK6ssYE
	 JoCrXEkdOp8cV0F+4m3KN87HWXD5orXfMajI/mlqJEbEjjSguLk87tcBLXUnlwhjux
	 IbzNbu3k5x7ddKB7L0p4kA1Pe9GksImFZOQtD2TU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436781AbfHWQfj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 12:35:39 -0400
Received: from foss.arm.com ([217.140.110.172]:37010 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389827AbfHWQfh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 12:35:37 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5D7E928;
        Fri, 23 Aug 2019 09:35:37 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 AC01A3F246;
        Fri, 23 Aug 2019 09:35:35 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andre Przywara <andre.przywara@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Dave Martin <dave.martin@arm.com>,
        Julien Grall <julien.grall@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 1/2] KVM: arm/arm64: Only skip MMIO insn once
Date: Fri, 23 Aug 2019 17:35:15 +0100
Message-Id: <20190823163516.179768-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190823163516.179768-1-maz@kernel.org>
References: <20190823163516.179768-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

If after an MMIO exit to userspace a VCPU is immediately run with an
immediate_exit request, such as when a signal is delivered or an MMIO
emulation completion is needed, then the VCPU completes the MMIO
emulation and immediately returns to userspace. As the exit_reason
does not get changed from KVM_EXIT_MMIO in these cases we have to
be careful not to complete the MMIO emulation again, when the VCPU is
eventually run again, because the emulation does an instruction skip
(and doing too many skips would be a waste of guest code :-) We need
to use additional VCPU state to track if the emulation is complete.
As luck would have it, we already have 'mmio_needed', which even
appears to be used in this way by other architectures already.

Fixes: 0d640732dbeb ("arm64: KVM: Skip MMIO insn after emulation")
Acked-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/mmio.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [GIT PULL] KVM/arm updates for 5.3-rc6
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11112063
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 963421399
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6B39B2082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1566578137;
	bh=9/Ga/gY/4DodONFOysFXqlnV2abLZqyyzG+7T1oXTQs=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=YcdSvWCuv79zfLwFO4Ze7VZGMbddQ3cWSl22Ds7I421OB8XrEZEJ5bs+82JxFbox3
	 Ked/BAa/nEEDwIW2u6exrcHl0ztKWGy7vxMaPHsoisrEaJ+VlXhrj3NOKd3W2oqbQn
	 FWa5G83WWoKd9i/917hbAa3bDWEW0SmaRE5C+cyw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436731AbfHWQfg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 12:35:36 -0400
Received: from foss.arm.com ([217.140.110.172]:36998 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389827AbfHWQfg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 12:35:36 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 769F328;
        Fri, 23 Aug 2019 09:35:35 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 C53193F246;
        Fri, 23 Aug 2019 09:35:33 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andre Przywara <andre.przywara@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Dave Martin <dave.martin@arm.com>,
        Julien Grall <julien.grall@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm updates for 5.3-rc6
Date: Fri, 23 Aug 2019 17:35:14 +0100
Message-Id: <20190823163516.179768-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo, Radim,

One (hopefully last) set of fixes for KVM/arm for 5.3: an embarassing
MMIO emulation regression, and a UBSAN splat. Oh well...

Please pull,

       M.

The following changes since commit 16e604a437c89751dc626c9e90cf88ba93c5be64:

  KVM: arm/arm64: vgic: Reevaluate level sensitive interrupts on enable (2019-08-09 08:07:26 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.3-3

for you to fetch changes up to 2e16f3e926ed48373c98edea85c6ad0ef69425d1:

  KVM: arm/arm64: VGIC: Properly initialise private IRQ affinity (2019-08-23 17:23:01 +0100)

----------------------------------------------------------------
KVM/arm fixes for 5.3, take #3

- Don't overskip instructions on MMIO emulation
- Fix UBSAN splat when initializing PPI priorities

----------------------------------------------------------------
Andre Przywara (1):
      KVM: arm/arm64: VGIC: Properly initialise private IRQ affinity

Andrew Jones (1):
      KVM: arm/arm64: Only skip MMIO insn once

 virt/kvm/arm/mmio.c           |  7 +++++++
 virt/kvm/arm/vgic/vgic-init.c | 30 ++++++++++++++++++++----------
 2 files changed, 27 insertions(+), 10 deletions(-)

From patchwork Fri Aug 23 16:35:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11112069
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DBA9A1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BAF2221726
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 16:35:41 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1566578141;
	bh=Q6JaWtZbUkVEAtSydl7bb5cp6lWS6Y3PwQCQXZzN95s=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=X4tslAmXE17SDTNI5R/IxpZOJL9oqYG5TVgw2XJq9BNwzrB5ZNxsnJM/wVnLaR0t3
	 mgqYodBCLVb0/DRW1GOsexrl0k8ct1t5lMYqK1P+OzLIzcA08YA6rPdy2aGrU1zYQ8
	 8wUieYn1Brci/Z7lUM6qs95BjFNUhAgveFjyEt4o=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436777AbfHWQfk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 12:35:40 -0400
Received: from foss.arm.com ([217.140.110.172]:37024 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2436778AbfHWQfj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 12:35:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 454FA1570;
        Fri, 23 Aug 2019 09:35:39 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 94A4B3F246;
        Fri, 23 Aug 2019 09:35:37 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andre Przywara <andre.przywara@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Dave Martin <dave.martin@arm.com>,
        Julien Grall <julien.grall@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 2/2] KVM: arm/arm64: VGIC: Properly initialise private IRQ
 affinity
Date: Fri, 23 Aug 2019 17:35:16 +0100
Message-Id: <20190823163516.179768-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190823163516.179768-1-maz@kernel.org>
References: <20190823163516.179768-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andre Przywara <andre.przywara@arm.com>

At the moment we initialise the target *mask* of a virtual IRQ to the
VCPU it belongs to, even though this mask is only defined for GICv2 and
quickly runs out of bits for many GICv3 guests.
This behaviour triggers an UBSAN complaint for more than 32 VCPUs:
------
[ 5659.462377] UBSAN: Undefined behaviour in virt/kvm/arm/vgic/vgic-init.c:223:21
[ 5659.471689] shift exponent 32 is too large for 32-bit type 'unsigned int'
------
Also for GICv3 guests the reporting of TARGET in the "vgic-state" debugfs
dump is wrong, due to this very same problem.

Because there is no requirement to create the VGIC device before the
VCPUs (and QEMU actually does it the other way round), we can't safely
initialise mpidr or targets in kvm_vgic_vcpu_init(). But since we touch
every private IRQ for each VCPU anyway later (in vgic_init()), we can
just move the initialisation of those fields into there, where we
definitely know the VGIC type.

On the way make sure we really have either a VGICv2 or a VGICv3 device,
since the existing code is just checking for "VGICv3 or not", silently
ignoring the uninitialised case.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reported-by: Dave Martin <dave.martin@arm.com>
Tested-by: Julien Grall <julien.grall@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/vgic/vgic-init.c | 30 ++++++++++++++++++++----------
 1 file changed, 20 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: arm/arm64: vgic: Use a single IO device per redistributor
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11112141
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E9931398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 17:33:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EEAE82173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 17:33:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403863AbfHWRdt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 13:33:49 -0400
Received: from mx1.redhat.com ([209.132.183.28]:38602 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2403837AbfHWRds (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 13:33:48 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id C7002308624A;
        Fri, 23 Aug 2019 17:33:47 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-105.ams2.redhat.com
 [10.36.116.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BD8255D9CA;
        Fri, 23 Aug 2019 17:33:41 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: yuzenghui@huawei.com, zhang.zhanghailiang@huawei.com,
        wanghaibin.wang@huawei.com, james.morse@arm.com,
        qemu-arm@nongnu.org, julien.thierry.kdev@gmail.com,
        suzuki.poulose@arm.com, peter.maydell@linaro.org,
        andre.przywara@arm.com
Subject: [PATCH] KVM: arm/arm64: vgic: Use a single IO device per
 redistributor
Date: Fri, 23 Aug 2019 19:33:30 +0200
Message-Id: <20190823173330.23342-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.49]);
 Fri, 23 Aug 2019 17:33:48 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment we use 2 IO devices per GICv3 redistributor: one
one for the RD_base frame and one for the SGI_base frame.

Instead we can use a single IO device per redistributor (the 2
frames are contiguous). This saves slots on the KVM_MMIO_BUS
which is currently limited to NR_IOBUS_DEVS (1000).

This change allows to instantiate up to 512 redistributors and may
speed the guest boot with a large number of VCPUs.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 include/kvm/arm_vgic.h           |  1 -
 virt/kvm/arm/vgic/vgic-init.c    |  1 -
 virt/kvm/arm/vgic/vgic-mmio-v3.c | 81 ++++++++++----------------------
 3 files changed, 24 insertions(+), 59 deletions(-)

```
#### [PATCH] KVM: VMX: Handle single-step #DB for EMULTYPE_SKIP on EPT misconfig
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11112387
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0ABBC1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 21:31:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DCB4921897
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 21:31:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436926AbfHWVbT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 17:31:19 -0400
Received: from mga18.intel.com ([134.134.136.126]:57174 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2436922AbfHWVbS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 17:31:18 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Aug 2019 14:31:16 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,422,1559545200";
   d="scan'208";a="263302315"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga001.jf.intel.com with ESMTP; 23 Aug 2019 14:31:15 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Handle single-step #DB for EMULTYPE_SKIP on EPT
 misconfig
Date: Fri, 23 Aug 2019 14:31:15 -0700
Message-Id: <20190823213115.31908-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX's EPT misconfig flow to handle fast-MMIO path falls back to decoding
the instruction to determine the instruction length when running as a
guest (Hyper-V doesn't fill VMCS.VM_EXIT_INSTRUCTION_LEN because it's
technically not defined for EPT misconfigs).  Rather than implement the
slow skip in VMX's generic skip_emulated_instruction(),
handle_ept_misconfig() directly calls kvm_emulate_instruction() with
EMULTYPE_SKIP, which intentionally doesn't do single-step detection, and
so handle_ept_misconfig() misses a single-step #DB.

Rework the EPT misconfig fallback case to route it through
kvm_skip_emulated_instruction() so that single-step #DBs and interrupt
shadow updates are handled automatically.  I.e. make VMX's slow skip
logic match SVM's and have the SVM flow not intentionally avoid the
shadow update.

Alternatively, the handle_ept_misconfig() could manually handle single-
step detection, but that results in EMULTYPE_SKIP having split logic for
the interrupt shadow vs. single-step #DBs, and split emulator logic is
largely what led to this mess in the first place.

Modifying SVM to mirror VMX flow isn't really an option as SVM's case
isn't limited to a specific exit reason, i.e. handling the slow skip in
skip_emulated_instruction() is mandatory for all intents and purposes.

Drop VMX's skip_emulated_instruction() wrapper since it can now fail,
and instead WARN if it fails unexpectedly, e.g. if exit_reason somehow
becomes corrupted.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Fixes: d391f12070672 ("x86/kvm/vmx: do not use vm-exit instruction length for fast MMIO when running nested")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

*** LOOK HERE ***

This patch applies on top my recent emulation cleanup[1][2] as it has
non-trivial conflicts, dealing with those seemed like a waste of time,
and this doesn't seem like a candidate for stable.  Let me know if you'd
prefer it to be respun without the dependency.

Sadly/ironically, this unwinds some of the logic that was recently
added by Vitaly at my suggestion.  Hindsight is 20/20 and all that...

[1] https://lkml.kernel.org/r/20190823010709.24879-1-sean.j.christopherson@intel.com
[2] https://patchwork.kernel.org/cover/11110331/

 arch/x86/kvm/svm.c     | 17 +++++++-------
 arch/x86/kvm/vmx/vmx.c | 52 ++++++++++++++++++------------------------
 arch/x86/kvm/x86.c     |  6 ++++-
 3 files changed, 36 insertions(+), 39 deletions(-)

```
#### [PATCH] KVM: x86: Don't update RIP or do single-step on faulting emulation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11112381
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 29C6B1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 20:55:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 11DF122CE3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 20:55:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392958AbfHWUzq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 23 Aug 2019 16:55:46 -0400
Received: from mga14.intel.com ([192.55.52.115]:48804 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2392742AbfHWUzq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 23 Aug 2019 16:55:46 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Aug 2019 13:55:45 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,422,1559545200";
   d="scan'208";a="330833026"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga004.jf.intel.com with ESMTP; 23 Aug 2019 13:55:45 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Nadav Amit <nadav.amit@gmail.com>,
        Andy Lutomirski <luto@kernel.org>
Subject: [PATCH] KVM: x86: Don't update RIP or do single-step on faulting
 emulation
Date: Fri, 23 Aug 2019 13:55:44 -0700
Message-Id: <20190823205544.24052-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't advance RIP or inject a single-step #DB if emulation signals a
fault.  This logic applies to all state updates that are conditional on
clean retirement of the emulation instruction, e.g. updating RFLAGS was
previously handled by commit 38827dbd3fb85 ("KVM: x86: Do not update
EFLAGS on faulting emulation").

Not advancing RIP is likely a nop, i.e. ctxt->eip isn't updated with
ctxt->_eip until emulation "retires" anyways.  Skipping #DB injection
fixes a bug reported by Andy Lutomirski where a #UD on SYSCALL due to
invalid state with RFLAGS.RF=1 would loop indefinitely due to emulation
overwriting the #UD with #DB and thus restarting the bad SYSCALL over
and over.

Cc: Nadav Amit <nadav.amit@gmail.com>
Cc: stable@vger.kernel.org
Reported-by: Andy Lutomirski <luto@kernel.org>
Fixes: 663f4c61b803 ("KVM: x86: handle singlestep during emulation")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

Note, this has minor conflict with my recent series to cleanup the
emulator return flows[*].  The end result should look something like:

                if (!ctxt->have_exception ||
                    exception_type(ctxt->exception.vector) == EXCPT_TRAP) {
                        kvm_rip_write(vcpu, ctxt->eip);
                        if (r && ctxt->tf)
                                r = kvm_vcpu_do_singlestep(vcpu);
                        __kvm_set_rflags(vcpu, ctxt->eflags);
                }

[*] https://lkml.kernel.org/r/20190823010709.24879-1-sean.j.christopherson@intel.com

 arch/x86/kvm/x86.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [RESEND PATCH 01/13] KVM: x86: Relocate MMIO exit stats counting
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11110333
Return-Path: <SRS0=ITOr=WT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C924414DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 01:08:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B179C23402
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 23 Aug 2019 01:08:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387545AbfHWBIW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 22 Aug 2019 21:08:22 -0400
Received: from mga01.intel.com ([192.55.52.88]:37991 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732613AbfHWBHL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 22 Aug 2019 21:07:11 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 22 Aug 2019 18:07:10 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,419,1559545200";
   d="scan'208";a="186733486"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Aug 2019 18:07:10 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RESEND PATCH 01/13] KVM: x86: Relocate MMIO exit stats counting
Date: Thu, 22 Aug 2019 18:06:57 -0700
Message-Id: <20190823010709.24879-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190823010709.24879-1-sean.j.christopherson@intel.com>
References: <20190823010709.24879-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the stat.mmio_exits update into x86_emulate_instruction().  This is
both a bug fix, e.g. the current update flows will incorrectly increment
mmio_exits on emulation failure, and a preparatory change to set the
stage for eliminating EMULATE_DONE and company.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu.c     | 2 --
 arch/x86/kvm/vmx/vmx.c | 1 -
 arch/x86/kvm/x86.c     | 2 ++
 3 files changed, 2 insertions(+), 3 deletions(-)

```
