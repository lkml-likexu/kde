#### [PATCH 1/4] KVM: arm64: Annotate hyp NMI-related functions as __always_inline
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11632549
Return-Path: <SRS0=uYC6=AK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1510A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 29 Jun 2020 21:15:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F175120720
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 29 Jun 2020 21:15:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1593465322;
	bh=VdO0jQ/MssMzZwJ3Jmcy7j9yhjcRN0AurIn0itRbDB4=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=sfmz3RipZxy1OJvYHSPbzfl/crqR8fA7BMLkIP7ReVuG1VAdCqyRpqbnWxb2eFBlW
	 SJjMHWD1F1IqYLyoenGn9Zp3nptS3vM6yZQXGvJo/Tz1oN+Aqu86GB9ev7xIAIkrUu
	 gix4m4c7Ca94uFxZElI01stJOCcOQsSjBqulKvNY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726912AbgF2VPJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 29 Jun 2020 17:15:09 -0400
Received: from mail.kernel.org ([198.145.29.99]:42434 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729957AbgF2SzQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 29 Jun 2020 14:55:16 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 04EFD25592;
        Mon, 29 Jun 2020 16:25:34 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1593447934;
        bh=VdO0jQ/MssMzZwJ3Jmcy7j9yhjcRN0AurIn0itRbDB4=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=zzLChNvlDrQi+ZfF4CpY+8pP5YHckGR9bXphz2iJVJrvT0xNx03guK3euKdB8ey/p
         Aob+xKUnA2bGpyfza4nOvV7yN1TnVuNRsxal3ipw2bh8M4iNHopEaV+ZoKBk4Z7Awq
         +b8vSiEbWxZMtvvLzjtsY8a2kjo2IC5scsvOfFVE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jpwb6-007M5T-Gk; Mon, 29 Jun 2020 17:25:32 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        James Morse <james.morse@arm.com>,
        Steven Price <steven.price@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH 1/4] KVM: arm64: Annotate hyp NMI-related functions as
 __always_inline
Date: Mon, 29 Jun 2020 17:25:16 +0100
Message-Id: <20200629162519.825200-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200629162519.825200-1-maz@kernel.org>
References: <20200629162519.825200-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, james.morse@arm.com, steven.price@arm.com,
 yuzenghui@huawei.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexandru Elisei <alexandru.elisei@arm.com>

The "inline" keyword is a hint for the compiler to inline a function.  The
functions system_uses_irq_prio_masking() and gic_write_pmr() are used by
the code running at EL2 on a non-VHE system, so mark them as
__always_inline to make sure they'll always be part of the .hyp.text
section.

This fixes the following splat when trying to run a VM:

[   47.625273] Kernel panic - not syncing: HYP panic:
[   47.625273] PS:a00003c9 PC:0000ca0b42049fc4 ESR:86000006
[   47.625273] FAR:0000ca0b42049fc4 HPFAR:0000000010001000 PAR:0000000000000000
[   47.625273] VCPU:0000000000000000
[   47.647261] CPU: 1 PID: 217 Comm: kvm-vcpu-0 Not tainted 5.8.0-rc1-ARCH+ #61
[   47.654508] Hardware name: Globalscale Marvell ESPRESSOBin Board (DT)
[   47.661139] Call trace:
[   47.663659]  dump_backtrace+0x0/0x1cc
[   47.667413]  show_stack+0x18/0x24
[   47.670822]  dump_stack+0xb8/0x108
[   47.674312]  panic+0x124/0x2f4
[   47.677446]  panic+0x0/0x2f4
[   47.680407] SMP: stopping secondary CPUs
[   47.684439] Kernel Offset: disabled
[   47.688018] CPU features: 0x240402,20002008
[   47.692318] Memory Limit: none
[   47.695465] ---[ end Kernel panic - not syncing: HYP panic:
[   47.695465] PS:a00003c9 PC:0000ca0b42049fc4 ESR:86000006
[   47.695465] FAR:0000ca0b42049fc4 HPFAR:0000000010001000 PAR:0000000000000000
[   47.695465] VCPU:0000000000000000 ]---

The instruction abort was caused by the code running at EL2 trying to fetch
an instruction which wasn't mapped in the EL2 translation tables. Using
objdump showed the two functions as separate symbols in the .text section.

Fixes: 85738e05dc38 ("arm64: kvm: Unmask PMR before entering guest")
Cc: stable@vger.kernel.org
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: James Morse <james.morse@arm.com>
Link: https://lore.kernel.org/r/20200618171254.1596055-1-alexandru.elisei@arm.com
---
 arch/arm64/include/asm/arch_gicv3.h | 2 +-
 arch/arm64/include/asm/cpufeature.h | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
