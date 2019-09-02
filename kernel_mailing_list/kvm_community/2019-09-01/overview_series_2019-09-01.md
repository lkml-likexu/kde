#### [PATCH 1/3] arm64: KVM: Drop hyp_alternate_select for checking for ARM64_WORKAROUND_834220
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11125749
Return-Path: <SRS0=mDu4=W4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD9CF1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  1 Sep 2019 21:12:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A1A9621897
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  1 Sep 2019 21:12:59 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1567372379;
	bh=zEzu+Afci48pT4puhUiKenD2+v7ngr6dLpu8yBplUCY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=cyBnYSxyXt9GmFL0xBc512CsN+cO4wcJbuGia8ibNuOZ/s9fBJzSssyNDCbk8BUZC
	 0DW0npj11GIUm5Vm8S/1NcdO+vx7TUP1VdzveEgNvUGP2AvhjubuRJCc+0ef4XqQ4g
	 NxN/8lR7MYvDXVwFXyI2CHfESHAtkiuIaXaEaNJY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729118AbfIAVM6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 1 Sep 2019 17:12:58 -0400
Received: from foss.arm.com ([217.140.110.172]:46424 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728891AbfIAVM6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Sep 2019 17:12:58 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EB155360;
        Sun,  1 Sep 2019 14:12:57 -0700 (PDT)
Received: from why.lan (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 9A22C3F718;
        Sun,  1 Sep 2019 14:12:56 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 1/3] arm64: KVM: Drop hyp_alternate_select for checking for
 ARM64_WORKAROUND_834220
Date: Sun,  1 Sep 2019 22:12:35 +0100
Message-Id: <20190901211237.11673-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190901211237.11673-1-maz@kernel.org>
References: <20190901211237.11673-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no reason for using hyp_alternate_select when checking
for ARM64_WORKAROUND_834220, as each of the capabilities is
also backed by a static key. Just replace the KVM-specific
construct with cpus_have_const_cap(ARM64_WORKAROUND_834220).

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/hyp/switch.c | 17 ++---------------
 1 file changed, 2 insertions(+), 15 deletions(-)

```
