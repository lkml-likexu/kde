#### [PATCH] KVM: arm64: Save/restore sp_el0 as part of __guest_enter
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11509809
Return-Path: <SRS0=4nXr=6J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24D0992C
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Apr 2020 09:43:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C8E820704
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 25 Apr 2020 09:43:54 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587807835;
	bh=zvYrOISsqhXXkpkz+TnXeLEkWvfF6n0Y6JOs4aslC1Y=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=VJS/75/rUOqDRbz6iNdZB6jT7ZfT05ZTQifMjbGJyNJ4IqVsHgM1hpv2SK4uCKJaF
	 vZkfymFv6pbjIwCb6BX2VyaxUL3te7nqnQiyi3moubjAjQs4vbeJOC+70Ko+YQhwTM
	 tqe5XfXM4k7xpTjV6oIbkxkSn4IM3UUiHKPfeUko=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726087AbgDYJnc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 25 Apr 2020 05:43:32 -0400
Received: from mail.kernel.org ([198.145.29.99]:45378 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726050AbgDYJnc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 25 Apr 2020 05:43:32 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 39A5220704;
        Sat, 25 Apr 2020 09:43:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587807811;
        bh=zvYrOISsqhXXkpkz+TnXeLEkWvfF6n0Y6JOs4aslC1Y=;
        h=From:To:Cc:Subject:Date:From;
        b=pm7FFlsmPkKp8TRBVHkn7sGO3WZwHKBkL8zyVIh59CSu7eHk0PQR6xoxnHgrJ9R3W
         eBrixxYSdRgIQCGCUKDbX396hH8AFk7mfOL5+aXT8Uzid50aBKXjUcyyeIyLxPzcjk
         yWzPZsttMPHCgUNPvCnNH8FICm+EU7luhE5eU8cY=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jSHLN-006HA5-DN; Sat, 25 Apr 2020 10:43:29 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Mark Rutland <mark.rutland@arm.com>
Subject: [PATCH] KVM: arm64: Save/restore sp_el0 as part of __guest_enter
Date: Sat, 25 Apr 2020 10:43:21 +0100
Message-Id: <20200425094321.162752-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, mark.rutland@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently save/restore sp_el0 in C code. This is a bit unsafe,
as a lot of the C code expects 'current' to be accessible from
there (and the opportunity to run kernel code in HYP is specially
great with VHE).

Instead, let's move the save/restore of sp_el0 to the assembly
code (in __guest_enter), making sure that sp_el0 is correct
very early on when we exit the guest, and is preserved as long
as possible to its host value when we enter the guest.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/hyp/entry.S     | 23 +++++++++++++++++++++++
 arch/arm64/kvm/hyp/sysreg-sr.c | 17 +++--------------
 2 files changed, 26 insertions(+), 14 deletions(-)

```
