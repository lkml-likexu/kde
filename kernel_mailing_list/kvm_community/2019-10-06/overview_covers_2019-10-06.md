

#### [PATCH 0/3] KVM: arm64: Assorted PMU emulation fixes
##### From: maz@kernel.org
From: Marc Zyngier <maz@kernel.org>

```c
From patchwork Sun Oct  6 10:46:33 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11176277
Return-Path: <SRS0=sk/v=X7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A02DE13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Oct 2019 10:47:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E3722084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Oct 2019 10:47:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570358826;
	bh=5F1vOMzribkWPxS/i0/IDvYHGJESKxSllK/Tnob7QXY=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=hkRGOrKJSnRYAlgLbIBUiagRhTUH8RyeZ6KKli3U3rHftvAZEJ101bjFCxgLLc0oV
	 SDxO57JkuTsQtRW/sPw04vF/2LR7e9t9SwLsdSO3c9v8abzdIOJgYdRl7xeivEyEbf
	 2T2xDS/uYL247xT6T8FvWsRyEmrR36CEP+FvwQbs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726497AbfJFKq7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 6 Oct 2019 06:46:59 -0400
Received: from mail.kernel.org ([198.145.29.99]:38010 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726248AbfJFKq6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 6 Oct 2019 06:46:58 -0400
Received: from localhost.localdomain (82-132-217-85.dab.02.net
 [82.132.217.85])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 66D232084D;
        Sun,  6 Oct 2019 10:46:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1570358818;
        bh=5F1vOMzribkWPxS/i0/IDvYHGJESKxSllK/Tnob7QXY=;
        h=From:To:Cc:Subject:Date:From;
        b=xQlAvOWUndDfG+W9cFUCIMRr1I1Cp8uID0IDvLC6gmS8Y6pIi8kJYXLoYh7HYL3cD
         LC8H8dKP2tMYEGIMPAwrR/ssMZxpyd0ctFBtf+TbFXMYaCjl6nDMp1RD77NchJx70P
         V78sQp7xBgsYCEjDFcg62KQhDwSESd5erSE+aY44=
From: maz@kernel.org
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>,
        Andrew Murray <andrew.murray@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>
Subject: [PATCH 0/3] KVM: arm64: Assorted PMU emulation fixes
Date: Sun,  6 Oct 2019 11:46:33 +0100
Message-Id: <20191006104636.11194-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Zyngier <maz@kernel.org>

I recently came across a number of PMU emulation bugs, all which can
result in unexpected behaviours in an unsuspecting guest. The first
two patches already have been discussed on the list, but I'm including
them here as part of a slightly longer series. The last patch fixes an
issue that has been here from day one, where we confuse architectural
overflow of a counter and perf sampling period.

If nobody disagrees, I'll send them upstream shortly.

Marc Zyngier (3):
  KVM: arm64: pmu: Fix cycle counter truncation
  arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
  KVM: arm64: pmu: Reset sample period on overflow handling

 arch/arm64/kvm/sys_regs.c |  4 ++++
 virt/kvm/arm/pmu.c        | 34 ++++++++++++++++++++++++----------
 2 files changed, 28 insertions(+), 10 deletions(-)
```
