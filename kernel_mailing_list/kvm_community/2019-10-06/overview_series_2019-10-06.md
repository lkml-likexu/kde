#### [PATCH 1/3] KVM: arm64: pmu: Fix cycle counter truncation
##### From: maz@kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11176279
Return-Path: <SRS0=sk/v=X7=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CAB301747
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Oct 2019 10:47:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A992F2084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  6 Oct 2019 10:47:06 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570358826;
	bh=BP1l8qRwdBHc2b0glDmUNsamGkZG1dNdWAdZx4mn8yc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=rbeSdxq8HyUqTkutuo0dUVrnNO0hGsw7uTAt78w8i8CgG2D+MZ8vkzc9nOw77DxN9
	 Y86UZnIvr8IQKrqh7IzJBPI2+Y2jyOMrfY9fsap619N1i3d6r7EUTrfE/R2UHfJo1n
	 MOtzubgvCjrIY9cKe6Mk1KdvsDhgBLzFQ7wMS0xU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726519AbfJFKrC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 6 Oct 2019 06:47:02 -0400
Received: from mail.kernel.org ([198.145.29.99]:38048 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726248AbfJFKrC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 6 Oct 2019 06:47:02 -0400
Received: from localhost.localdomain (82-132-217-85.dab.02.net
 [82.132.217.85])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1640E21479;
        Sun,  6 Oct 2019 10:46:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1570358822;
        bh=BP1l8qRwdBHc2b0glDmUNsamGkZG1dNdWAdZx4mn8yc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=h6Qx4aJw/nWwQAC8L/sKrb93GHAkb1BQJqdEWMG8dvovCAmixwSxGvx4AnecyF0Nw
         mKAGSs3M3Yy+o6xRhNodMge8uwM5yGuqYNkOn2un/VMl1TaX7AHmC5p9KZa/vDI4ko
         vH0BxBuzUEBrfz554CNWs9jbo1AJVmzh/Q2zS6xA=
From: maz@kernel.org
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>,
        Andrew Murray <andrew.murray@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>
Subject: [PATCH 1/3] KVM: arm64: pmu: Fix cycle counter truncation
Date: Sun,  6 Oct 2019 11:46:34 +0100
Message-Id: <20191006104636.11194-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191006104636.11194-1-maz@kernel.org>
References: <20191006104636.11194-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Marc Zyngier <maz@kernel.org>

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
Cc: Andrew Murray <andrew.murray@arm.com>
Reported-by: Julien Thierry <julien.thierry.kdev@gmail.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/pmu.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
