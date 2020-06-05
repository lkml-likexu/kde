

#### [PATCH 0/3] kvm: arm64: Pointer Authentication handling fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Jun  4 13:33:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11587959
Return-Path: <SRS0=83j6=7R=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DB721392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 13:34:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E697E20835
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  4 Jun 2020 13:34:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591277646;
	bh=rcP0ID3sZv+j+DKkPTrcUriG90Uun00qknLwobPg9EU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ut0JTnpAELeZFy7u2Ug7+/AIMp5n704HyXFbIe1qv2IiyLQ9XOYbmDZg90SXVjj7y
	 wZswsc5Fy9x/k+dLVL0N/N2Gp4thv3fkgKbzM49KHBs0aZs9vR1L0mG/HhEG/kCrFH
	 b3oyvMq/8ggCHHyNX+z573P2FBpqCNXDs5uTO2AA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728607AbgFDNeG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 4 Jun 2020 09:34:06 -0400
Received: from mail.kernel.org ([198.145.29.99]:36164 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728550AbgFDNeF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Jun 2020 09:34:05 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 099E120772;
        Thu,  4 Jun 2020 13:34:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591277645;
        bh=rcP0ID3sZv+j+DKkPTrcUriG90Uun00qknLwobPg9EU=;
        h=From:To:Cc:Subject:Date:From;
        b=PNA+5znUqtVizpteIx5iiQH+oJlxiDqad2kOGfq9Qemb6XNvFMSy8+8BhCaCxVeYF
         DuC1RWChGU82A86yA3iGVXIOGL7Ke90uWaxbkMVFnsbCI86sf594bpQ2s6Wy1we3xu
         1LTE4mL0vo8yyu7tdIuAujVsdbNWI+0X6xczLYIk=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jgq0R-000G3O-GP; Thu, 04 Jun 2020 14:34:03 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com
Subject: [PATCH 0/3] kvm: arm64: Pointer Authentication handling fixes
Date: Thu,  4 Jun 2020 14:33:51 +0100
Message-Id: <20200604133354.1279412-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, will@kernel.org,
 catalin.marinas@arm.com, mark.rutland@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I recently discovered that the Pointer Authentication (PtrAuth)
handling code in KVM is busted, and has been for a while. The main
issue is that the we save the host's keys from a preemptible
context. Things will go wrong at some point.

In order to address this, the first patch move the saving of the
host's keys to vcpu_load(). It is done eagerly, which is a bore, but
is at least safe. This is definitely stable material.

The following two patches are adding an optimisation and a fix for a
corner case: we handle key saving and HCR massaging as a fixup, much
like the FPSIMD code. This subsequently allows us to deal with the
ugly case of a guest enabling PtrAuth despite it not being advertised,
resulting in PAC instructions UNDEF'ing while they should be NOPs.

This has been very lightly tested on a model.

Marc Zyngier (3):
  KVM: arm64: Save the host's PtrAuth keys in non-preemptible context
  KVM: arm64: Handle PtrAuth traps early
  KVM: arm64: Enforce PtrAuth being disabled if not advertized

 arch/arm64/include/asm/kvm_emulate.h |  6 ---
 arch/arm64/kvm/arm.c                 |  3 +-
 arch/arm64/kvm/handle_exit.c         | 38 ---------------
 arch/arm64/kvm/hyp/switch.c          | 73 ++++++++++++++++++++++++++++
 arch/arm64/kvm/sys_regs.c            | 13 ++---
 5 files changed, 80 insertions(+), 53 deletions(-)
```
