#### [PATCH v2 1/5] arm64: Add ARM64_WORKAROUND_1319367 for all A57 and A72 versions
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11200057
Return-Path: <SRS0=mHfo=YM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9183317EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Oct 2019 09:55:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70BB6222BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Oct 2019 09:55:48 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1571478948;
	bh=0ydo3zWocyZ2R1TjMk6U6Pm/YQU4lvknC5Dj+8pFO8I=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=lO/LnEXjiVyMUJChhnGPOMzlFwjaav3/JypmDV3pEjS2OHbXX1okAWwB6kndv42dQ
	 IDZGZ51S4Jp9qXXC9uGk0n70TX+DSttvR0aKehrgHD493q1XlZy5M+NDWZEiY+h/wA
	 K12m12h8XUg5UNRVz5XJSPYytQMG3ymlERvJkGGc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725802AbfJSJza (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Oct 2019 05:55:30 -0400
Received: from mail.kernel.org ([198.145.29.99]:53428 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725283AbfJSJza (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 19 Oct 2019 05:55:30 -0400
Received: from big-swifty.lan (78.163-31-62.static.virginmediabusiness.co.uk
 [62.31.163.78])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id C2EA4222CC;
        Sat, 19 Oct 2019 09:55:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1571478930;
        bh=0ydo3zWocyZ2R1TjMk6U6Pm/YQU4lvknC5Dj+8pFO8I=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Gywd3mq6ho0RcqzjTr5TjpZFv6g7TQInCq20wYBkqiI+t4T9pwUgtzUGKXpApuqFY
         4Y59074Z+gaoRT8b2na8QOPVVUmCPkaiRHwgXHTjppUePfaJK6Zjdc2Ny9ft6iaQRb
         q4TLIjgk+46OcepRBR4l7Uh57+53Ad4lQJQMg6ao=
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Mark Rutland <mark.rutland@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Subject: [PATCH v2 1/5] arm64: Add ARM64_WORKAROUND_1319367 for all A57 and
 A72 versions
Date: Sat, 19 Oct 2019 10:55:17 +0100
Message-Id: <20191019095521.31722-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191019095521.31722-1-maz@kernel.org>
References: <20191019095521.31722-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the EL2 vector hardening that is only selected for A57 and A72
so that the table can also be used for ARM64_WORKAROUND_1319367.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/cpucaps.h |  3 ++-
 arch/arm64/kernel/cpu_errata.c   | 13 ++++++++++---
 2 files changed, 12 insertions(+), 4 deletions(-)

```
