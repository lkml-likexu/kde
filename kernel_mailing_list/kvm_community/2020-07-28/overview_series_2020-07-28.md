#### [PATCH 1/2] KVM: arm64: Prevent vcpu_has_ptrauth from generating OOL functions
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11688635
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B2B814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52CDC20A8B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1595924607;
	bh=iJ+8/MWn5KdaoZ81Y0HfDlr48qzak2k8kb91X6SO0S4=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=ebA034D9jE2owQJs68HU26/U436ow76iiL+7cRDxIttIVXy/ubgewOB+D7V9cbxmQ
	 +e+8uRuxW0ZFs9PPP2PqNv0Ee1+GU7g19fgkh8w7cQQVP4twjVrIewy+uNlp6Itwjs
	 jF6rYUhrl8MAp2IEAU96Ois9+56ozW2fVIkPNXGg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728037AbgG1IX0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 04:23:26 -0400
Received: from mail.kernel.org ([198.145.29.99]:49340 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727878AbgG1IXZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 04:23:25 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id F0B4820809;
        Tue, 28 Jul 2020 08:23:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1595924605;
        bh=iJ+8/MWn5KdaoZ81Y0HfDlr48qzak2k8kb91X6SO0S4=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=2uewzYw+Xs67HzTT2pJajyh1R5CYcRLNJBkQAy0ca72w4NYphAI5cXI/qsrZk+gbl
         oCAXjVjUAa24o1lA0ewSimmiTtPJPx2LWThxiP8+NgPur0ha3BJ5ydDIiw+ceqxwog
         +ToKOaROkXVQnHLz0hrkP8AmJqLeQgQWGrXs4Ar0=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1k0KtP-00FaXh-GW; Tue, 28 Jul 2020 09:23:23 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Nathan Chancellor <natechancellor@gmail.com>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [PATCH 1/2] KVM: arm64: Prevent vcpu_has_ptrauth from generating OOL
 functions
Date: Tue, 28 Jul 2020 09:22:54 +0100
Message-Id: <20200728082255.3864378-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200728082255.3864378-1-maz@kernel.org>
References: <20200728082255.3864378-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, natechancellor@gmail.com,
 ndesaulniers@google.com, qperret@google.com, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So far, vcpu_has_ptrauth() is implemented in terms of system_supports_*_auth()
calls, which are declared "inline". In some specific conditions (clang
and SCS), the "inline" very much turns into an "out of line", which
leads to a fireworks when this predicate is evaluated on a non-VHE
system (right at the beginning of __hyp_handle_ptrauth).

Instead, make sure vcpu_has_ptrauth gets expanded inline by directly
using the cpus_have_final_cap() helpers, which are __always_inline,
generate much better code, and are the only thing that make sense when
running at EL2 on a nVHE system.

Fixes: 29eb5a3c57f7 ("KVM: arm64: Handle PtrAuth traps early")
Reported-by: Nathan Chancellor <natechancellor@gmail.com>
Reported-by: Nick Desaulniers <ndesaulniers@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Tested-by: Nathan Chancellor <natechancellor@gmail.com>
Reviewed-by: Nathan Chancellor <natechancellor@gmail.com>
Link: https://lore.kernel.org/r/20200722162231.3689767-1-maz@kernel.org
---
 arch/arm64/include/asm/kvm_host.h | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.8, take #4
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11688633
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44AE814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CA1620FC3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:26 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1595924606;
	bh=s+JcctlNG0hHX2xEwi6C3ENfXMCtVb68JpHdq0Skmw4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=dhJJT9KnbQvHlScvDwfUlszyBrSYHSPS6xMm1J2oZ3j0GqCVwVyVcGjGVS2kceepb
	 Q2/36AP8hU14CZPe5eibmcHYT4DVZ3YSKIvdYPe12JGZ3RE4kp8nVb6gp4QtrXR+Iu
	 w8DiWsr/F0SE7xa+SgM/RAeiegjKL58EGLB4bols=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727978AbgG1IXZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 04:23:25 -0400
Received: from mail.kernel.org ([198.145.29.99]:49312 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727878AbgG1IXY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 04:23:24 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5E64A2075D;
        Tue, 28 Jul 2020 08:23:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1595924604;
        bh=s+JcctlNG0hHX2xEwi6C3ENfXMCtVb68JpHdq0Skmw4=;
        h=From:To:Cc:Subject:Date:From;
        b=FhwUUQidy339zU5Wogz7l7ZnPOqzOczutbqIH2gK1BTX5z0NE9l7Ve489HTCVByJR
         5FoMU64OWFU+Dy1nx65lqauBVZMUso+rxZB+85ve4BCguqOnD/Wqy9eerAg2rICaOl
         8x8WSiJjUkToSjV+fWon8nmzf7GyS8B66OyclbPA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1k0KtO-00FaXh-S3; Tue, 28 Jul 2020 09:23:23 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Nathan Chancellor <natechancellor@gmail.com>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 fixes for 5.8, take #4
Date: Tue, 28 Jul 2020 09:22:53 +0100
Message-Id: <20200728082255.3864378-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, natechancellor@gmail.com,
 ndesaulniers@google.com, qperret@google.com, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

This is the last batch of fixes for 5.8. One fixes a long standing MMU
issue, while the other addresses a more recent brekage with out-of-line
helpers in the nVHE code.

Please pull,

	M.

The following changes since commit b9e10d4a6c9f5cbe6369ce2c17ebc67d2e5a4be5:

  KVM: arm64: Stop clobbering x0 for HVC_SOFT_RESTART (2020-07-06 11:47:02 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.8-4

for you to fetch changes up to b757b47a2fcba584d4a32fd7ee68faca510ab96f:

  KVM: arm64: Don't inherit exec permission across page-table levels (2020-07-28 09:03:57 +0100)

----------------------------------------------------------------
KVM/arm64 fixes for Linux 5.8, take #3

- Fix a corner case of a new mapping inheriting exec permission without
  and yet bypassing invalidation of the I-cache
- Make sure PtrAuth predicates oinly generate inline code for the
  non-VHE hypervisor code

----------------------------------------------------------------
Marc Zyngier (1):
      KVM: arm64: Prevent vcpu_has_ptrauth from generating OOL functions

Will Deacon (1):
      KVM: arm64: Don't inherit exec permission across page-table levels

 arch/arm64/include/asm/kvm_host.h | 11 ++++++++---
 arch/arm64/kvm/mmu.c              | 11 ++++++-----
 2 files changed, 14 insertions(+), 8 deletions(-)

From patchwork Tue Jul 28 08:22:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11688637
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 659CC6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DB8C208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 08:23:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1595924608;
	bh=7J4ifTf3z4A0dVzuF6o8Muc/dgb2Mqij10g2be4Y9DE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=gLVqb3LIEJvPT8xfBePP0B1GSNaG4t7ksmvzzwE0/VCtMmdxxNR3fXwjF8p3CvIlP
	 lXQpOVgqY3LXmi4iHdgb7yvS2p7E5CT7iCoBEaO9czCYU2EPWlgL2rDqvbJeokAHZ4
	 HEp+obk7lOLi1o8RzQb3jKq6vF/6nu3JEayczYs8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728059AbgG1IX1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 04:23:27 -0400
Received: from mail.kernel.org ([198.145.29.99]:49382 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728017AbgG1IX0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 04:23:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A523B20838;
        Tue, 28 Jul 2020 08:23:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1595924605;
        bh=7J4ifTf3z4A0dVzuF6o8Muc/dgb2Mqij10g2be4Y9DE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=inLBOhOJkaD/rInFVr1UHi1jHUyuEcmkFu2RME7YqR8Z/cjTmNBcyc0T4SQKugqml
         Kd2psSirXcMv+m0Xz9GHST5fjl+MoyktTLW4hqNdAh7Ry3JB2jO0eQB7d2SQ250sSf
         TvEIhuEQxk5whTW4cm9PBhZrjnrSRKMQOtbRSX3U=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1k0KtQ-00FaXh-7H; Tue, 28 Jul 2020 09:23:24 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Nathan Chancellor <natechancellor@gmail.com>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, kernel-team@android.com,
        stable@vger.kernel.org
Subject: [PATCH 2/2] KVM: arm64: Don't inherit exec permission across
 page-table levels
Date: Tue, 28 Jul 2020 09:22:55 +0100
Message-Id: <20200728082255.3864378-3-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200728082255.3864378-1-maz@kernel.org>
References: <20200728082255.3864378-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, natechancellor@gmail.com,
 ndesaulniers@google.com, qperret@google.com, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

If a stage-2 page-table contains an executable, read-only mapping at the
pte level (e.g. due to dirty logging being enabled), a subsequent write
fault to the same page which tries to install a larger block mapping
(e.g. due to dirty logging having been disabled) will erroneously inherit
the exec permission and consequently skip I-cache invalidation for the
rest of the block.

Ensure that exec permission is only inherited by write faults when the
new mapping is of the same size as the existing one. A subsequent
instruction abort will result in I-cache invalidation for the entire
block mapping.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Tested-by: Quentin Perret <qperret@google.com>
Reviewed-by: Quentin Perret <qperret@google.com>
Cc: Marc Zyngier <maz@kernel.org>
Cc: <stable@vger.kernel.org>
Link: https://lore.kernel.org/r/20200723101714.15873-1-will@kernel.org
---
 arch/arm64/kvm/mmu.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-5.9-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11688285
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E7E72912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 05:52:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE83E21883
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 05:52:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="DfJJ9n0K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726913AbgG1FwV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 01:52:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40210 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726841AbgG1FwV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 01:52:21 -0400
Received: from ozlabs.org (ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3BFE6C061794;
        Mon, 27 Jul 2020 22:52:21 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1003)
        id 4BG5RR52nlz9sTk; Tue, 28 Jul 2020 15:52:19 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1595915539; bh=YdXzNj3yLITWMwct98Hrs/Ck+OqhvBxNa6tu3onfhmQ=;
        h=Date:From:To:Cc:Subject:From;
        b=DfJJ9n0KUqXuEohxRDafm3ceWLolNWIrUZGi/vBfITeTWk5KptXtRxcQ1bRHsH9HJ
         FkyI63nA8B64Exj2aBXZUFAmkYVektnMKYHV2eYUa26Fj6jHz25TtgDs3uRtbdWgR/
         VnWUiNaZ5MnbuctyQqDS0RPPXOThyQ00kJRsakHp5FXVmZsWlnnXYew4xro8Lz38Js
         hqVT95VHLJaQ3eM9rLIPDgMYJr/AGkL8Idi9HbzF+AbSWa6C/Y2fCv7GPTkNyCAqa+
         mc7bnBO2hZTS0SA06Gc2sk+Dk7SyyRhIuTZh5SwdCwsEmZUpz3XWIYLcfQNxIA/nvP
         tCz1xrxfssLsQ==
Date: Tue, 28 Jul 2020 15:51:00 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.9-1 tag
Message-ID: <20200728055100.GA2460422@thinks.paulus.ozlabs.org>
MIME-Version: 1.0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-next-5.9-1 tag to get a PPC KVM
update for 5.9.  It's another relatively small update this time, the
main thing being a series to improve the startup time for secure VMs
and make memory hotplug work in secure VMs.

Thanks,
Paul.

The following changes since commit b3a9e3b9622ae10064826dccb4f7a52bd88c7407:

  Linux 5.8-rc1 (2020-06-14 12:45:04 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.9-1

for you to fetch changes up to 81ab595ddd3c3036806b460526e1fbc5b271ff33:

  KVM: PPC: Book3S HV: Rework secure mem slot dropping (2020-07-28 12:34:52 +1000)

----------------------------------------------------------------
PPC KVM update for 5.9

- Improvements and bug-fixes for secure VM support, giving reduced startup
  time and memory hotplug support.
- Locking fixes in nested KVM code
- Increase number of guests supported by HV KVM to 4094
- Preliminary POWER10 support

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Protect kvm_vcpu_read_guest with srcu locks

Alistair Popple (1):
      KVM: PPC: Book3SHV: Enable support for ISA v3.1 guests

Cédric Le Goater (1):
      KVM: PPC: Book3S HV: Increase KVMPPC_NR_LPIDS on POWER8 and POWER9

Laurent Dufour (3):
      KVM: PPC: Book3S HV: Migrate hot plugged memory
      KVM: PPC: Book3S HV: Move kvmppc_svm_page_out up
      KVM: PPC: Book3S HV: Rework secure mem slot dropping

Ram Pai (4):
      KVM: PPC: Book3S HV: Fix function definition in book3s_hv_uvmem.c
      KVM: PPC: Book3S HV: Disable page merging in H_SVM_INIT_START
      KVM: PPC: Book3S HV: Track the state GFNs associated with secure VMs
      KVM: PPC: Book3S HV: In H_SVM_INIT_DONE, migrate remaining normal-GFNs to secure-GFNs

Tianjia Zhang (1):
      KVM: PPC: Clean up redundant kvm_run parameters in assembly

 Documentation/powerpc/ultravisor.rst        |   3 +
 arch/powerpc/include/asm/kvm_book3s_uvmem.h |  14 +
 arch/powerpc/include/asm/kvm_ppc.h          |   2 +-
 arch/powerpc/include/asm/reg.h              |   4 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c         |   8 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c      |   4 +
 arch/powerpc/kvm/book3s_hv.c                |  26 +-
 arch/powerpc/kvm/book3s_hv_nested.c         |  30 +-
 arch/powerpc/kvm/book3s_hv_uvmem.c          | 698 +++++++++++++++++++++-------
 arch/powerpc/kvm/book3s_interrupts.S        |  56 ++-
 arch/powerpc/kvm/book3s_pr.c                |   9 +-
 arch/powerpc/kvm/book3s_rtas.c              |   2 +
 arch/powerpc/kvm/booke.c                    |   9 +-
 arch/powerpc/kvm/booke_interrupts.S         |   9 +-
 arch/powerpc/kvm/bookehv_interrupts.S       |  10 +-
 arch/powerpc/kvm/powerpc.c                  |   5 +-
 16 files changed, 646 insertions(+), 243 deletions(-)
```
#### [RFC v9 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11688337
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9C02C138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:27:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C8D920829
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:27:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726920AbgG1G1j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 02:27:39 -0400
Received: from mga09.intel.com ([134.134.136.24]:37256 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726846AbgG1G1j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 02:27:39 -0400
IronPort-SDR: 
 lS/pYrWCxncY2PR1B8funfYmT4pfdLBgwuO+GDBTLOPqIzVEjeI8LjBxgL7BxyhjM2tjI1AfGv
 /cf+tPnb7jqw==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="152412003"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="152412003"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 23:27:31 -0700
IronPort-SDR: 
 iGDIAniPXISiidO0tcU6dHofc6XBpr10GOuaS5u6bEw2jRc5hsdfy+Q1893yAkHKU2fcEMdCMo
 A3n9U8WD9GIw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="394232781"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga001.fm.intel.com with ESMTP; 27 Jul 2020 23:27:30 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com, jasowang@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v9 01/25] scripts/update-linux-headers: Import iommu.h
Date: Mon, 27 Jul 2020 23:33:54 -0700
Message-Id: <1595918058-33392-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1595918058-33392-1-git-send-email-yi.l.liu@intel.com>
References: <1595918058-33392-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V4 1/6] vhost: introduce vhost_vring_call
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11688089
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1CF0E913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 04:28:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0DEEA206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 04:28:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726536AbgG1E2V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 00:28:21 -0400
Received: from mga05.intel.com ([192.55.52.43]:10247 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726445AbgG1E2V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 00:28:21 -0400
IronPort-SDR: 
 seyigC8IYik1TxQhNkz5WWQQT+EIklgRQAw4czchLC8MdnHy2nNGrIVtOqIe7/NHDzR2Alypwj
 S+4B8bAmz42g==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="236011083"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="236011083"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 21:28:16 -0700
IronPort-SDR: 
 445jUgAmKHIvxvMgX8xuOXOBNqCr+N+hhnCF9/aDKY6Y833Reyf4Ym4WUhhvk74K6D+Z1/Y9nK
 WO87qDnj3oHg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="290037177"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga006.jf.intel.com with ESMTP; 27 Jul 2020 21:28:10 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, alex.williamson@redhat.com, mst@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, eli@mellanox.com, shahafs@mellanox.com,
        parav@mellanox.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V4 1/6] vhost: introduce vhost_vring_call
Date: Tue, 28 Jul 2020 12:24:00 +0800
Message-Id: <20200728042405.17579-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200728042405.17579-1-lingshan.zhu@intel.com>
References: <20200728042405.17579-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit introduces struct vhost_vring_call which replaced
raw struct eventfd_ctx *call_ctx in struct vhost_virtqueue.
Besides eventfd_ctx, it contains a spin lock and an
irq_bypass_producer in its structure.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Suggested-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c  |  4 ++--
 drivers/vhost/vhost.c | 22 ++++++++++++++++------
 drivers/vhost/vhost.h |  9 ++++++++-
 3 files changed, 26 insertions(+), 9 deletions(-)

```
#### [PATCH kvm-unit-tests] arm64: Compile with -mno-outline-atomics
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11689067
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B039014B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 12:17:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9256A206D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 12:17:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GAeHemuL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728949AbgG1MR6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 08:17:58 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:44732 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728846AbgG1MR6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 28 Jul 2020 08:17:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595938676;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=HO4Ntmg3kwx+WcOk0iJR+OxS3yvS+0YEtkK0xDPBSYY=;
        b=GAeHemuLk99KCC9Z/075tsBzInqot/dF7eJOE9VkPA5Q6BSRZ3G7zbS3ocn81veCgWOZJB
        pbkHj6GN6cJ7/jEE7ytSnER2EtDYfkDCkWRxL3sO3dov9ssMQRgDgFytY8qVGujjm+0oOj
        efsJHYO8crRvuH82pZDGTMBGLY1sVqc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-508-erVVCjArPW-1yLLTTnUWUA-1; Tue, 28 Jul 2020 08:17:54 -0400
X-MC-Unique: erVVCjArPW-1yLLTTnUWUA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E685E1902EA0;
        Tue, 28 Jul 2020 12:17:53 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 77AD6712F2;
        Tue, 28 Jul 2020 12:17:52 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: alexandru.elisei@arm.com, pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] arm64: Compile with -mno-outline-atomics
Date: Tue, 28 Jul 2020 14:17:51 +0200
Message-Id: <20200728121751.15083-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

GCC 10.1.0 introduced the -moutline-atomics option which, when
enabled, use LSE instructions when the processor provides them.
The option is enabled by default and unfortunately causes the
following error at compile time:

 aarch64-linux-gnu-ld: /usr/lib/gcc/aarch64-linux-gnu/10.1.0/libgcc.a(lse-init.o): in function `init_have_lse_atomics':
 lse-init.c:(.text.startup+0xc): undefined reference to `__getauxval'

This is happening because we are linking against our own libcflat which
doesn't implement the function __getauxval().

Disable the use of the out-of-line functions by compiling with
-mno-outline-atomics.

Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 Makefile           | 11 +++++------
 arm/Makefile.arm64 |  3 +++
 2 files changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: Deflect unknown MSR accesses to user space
##### From: Alexander Graf <graf@amazon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11687831
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3EE8912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:45:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 85F3320809
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:45:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="eJ6lWWwn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726340AbgG1ApE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 20:45:04 -0400
Received: from smtp-fw-2101.amazon.com ([72.21.196.25]:44589 "EHLO
        smtp-fw-2101.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726237AbgG1ApE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jul 2020 20:45:04 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1595897101; x=1627433101;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=lOsLg4a8kvU0xW9o6gPY8lqBuILAGObzZ84ya1KWOk4=;
  b=eJ6lWWwnPMQQyBfdvQ3hgMbAos87KhC08F7QX3RgZWbwZ60KSeetx+LE
   1K7fIxvAGSVkMaVMa29xpD2nkguyEtQ+wc0mXLiJDeN9a7+J1IKccbfQC
   NZdTYbmQaITXx13a35z9BlH/GbIziR8Dld1+glULJREOAvvEp+or0HUEC
   g=;
IronPort-SDR: 
 pWJjWx0ZDm95t2PKEhLRiiIsJYmCs1mK3iSoCBKHWaZMvoR5Ye9X1TOtDY+DvEGRpLvxtieDr9
 QPny0tDUn+6w==
X-IronPort-AV: E=Sophos;i="5.75,404,1589241600";
   d="scan'208";a="44363014"
Received: from iad12-co-svc-p1-lb1-vlan2.amazon.com (HELO
 email-inbound-relay-1a-67b371d8.us-east-1.amazon.com) ([10.43.8.2])
  by smtp-border-fw-out-2101.iad2.amazon.com with ESMTP;
 28 Jul 2020 00:45:00 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1a-67b371d8.us-east-1.amazon.com (Postfix) with
 ESMTPS id 7835DA119D;
        Tue, 28 Jul 2020 00:44:57 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 28 Jul 2020 00:44:56 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.162.85) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Tue, 28 Jul 2020 00:44:54 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] KVM: x86: Deflect unknown MSR accesses to user space
Date: Tue, 28 Jul 2020 02:44:46 +0200
Message-ID: <20200728004446.932-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.162.85]
X-ClientProxiedBy: EX13D40UWA002.ant.amazon.com (10.43.160.149) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSRs are weird. Some of them are normal control registers, such as EFER.
Some however are registers that really are model specific, not very
interesting to virtualization workloads, and not performance critical.
Others again are really just windows into package configuration.

Out of these MSRs, only the first category is necessary to implement in
kernel space. Rarely accessed MSRs, MSRs that should be fine tunes against
certain CPU models and MSRs that contain information on the package level
are much better suited for user space to process. However, over time we have
accumulated a lot of MSRs that are not the first category, but still handled
by in-kernel KVM code.

This patch adds a generic interface to handle WRMSR and RDMSR from user
space. With this, any future MSR that is part of the latter categories can
be handled in user space.

Furthermore, it allows us to replace the existing "ignore_msrs" logic with
something that applies per-VM rather than on the full system. That way you
can run productive VMs in parallel to experimental ones where you don't care
about proper MSR handling.

Signed-off-by: Alexander Graf <graf@amazon.com>
---

As a quick example to show what this does, I implemented handling for MSR 0x35
(MSR_CORE_THREAD_COUNT) in QEMU on top of this patch set:

  https://github.com/agraf/qemu/commits/user-space-msr
---
 Documentation/virt/kvm/api.rst  | 60 ++++++++++++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  6 +++
 arch/x86/kvm/emulate.c          | 18 +++++++--
 arch/x86/kvm/x86.c              | 65 ++++++++++++++++++++++++++++++++-
 include/trace/events/kvm.h      |  2 +-
 include/uapi/linux/kvm.h        | 11 ++++++
 6 files changed, 155 insertions(+), 7 deletions(-)

```
#### [PATCH 1/6 v3] KVM: x86: Change names of some of the kvm_x86_ops functions to make them more semantical and readable
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11687817
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B2C5C14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:11:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8BDDA20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 00:11:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="JTiFTXid"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726455AbgG1ALO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Jul 2020 20:11:14 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:33096 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726139AbgG1ALO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Jul 2020 20:11:14 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06S07acF098851;
        Tue, 28 Jul 2020 00:11:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=gzG26fUgybyS8dix7buhvOlYBPA8wprnYlxU/Q8JmzY=;
 b=JTiFTXidXKVs3NeSuNTGVDF+YdBGoQSxmwIJVr+4+/F9o82pxhYyfIYcFYxoJhpQp3Ei
 ohkuDRkrV2NFbcr+QKeKBkxSOcOh+a6GXsNrNG596+3lOhsK7Y7LkUF8Dqpli1ANhITW
 40Ca211UBG/kBlJCE1mLlh+rzzapAsYxLH6zReHncpfwaw4LGhi5ehgSUcRxz4TjyRxB
 k0M2V3zS/q/+3g7/noE2RrNvk9RU6EWKIx3VNQHIOsVEd3eXA7wHkOLb/t20RrVdNrj1
 ESljplQcUn3B8gEwvhLPzu3P7FI9pOsMjQqX59BA+JVt8/lgkBdTC0jHAgX6P7amWtbZ ew==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 32hu1jcgnf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 28 Jul 2020 00:11:01 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 06S08elK157415;
        Tue, 28 Jul 2020 00:11:01 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3020.oracle.com with ESMTP id 32hu5rvkmm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 28 Jul 2020 00:11:01 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 06S0B0kE020208;
        Tue, 28 Jul 2020 00:11:00 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 27 Jul 2020 17:10:59 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com, qemu-devel@nongnu.org
Subject: [PATCH 1/6 v3] KVM: x86: Change names of some of the kvm_x86_ops
 functions to make them more semantical and readable
Date: Tue, 28 Jul 2020 00:10:45 +0000
Message-Id: <1595895050-105504-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1595895050-105504-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1595895050-105504-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9695
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 phishscore=0 bulkscore=0
 malwarescore=0 suspectscore=4 spamscore=0 mlxlogscore=999 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007270165
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9695
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 clxscore=1011
 mlxlogscore=999
 malwarescore=0 impostorscore=0 priorityscore=1501 spamscore=0 phishscore=0
 suspectscore=4 bulkscore=0 mlxscore=0 lowpriorityscore=0 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007270165
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/arm64/include/asm/kvm_host.h   |  2 +-
 arch/mips/include/asm/kvm_host.h    |  2 +-
 arch/powerpc/include/asm/kvm_host.h |  2 +-
 arch/s390/kvm/kvm-s390.c            |  2 +-
 arch/x86/include/asm/kvm_host.h     | 12 ++++++------
 arch/x86/kvm/svm/svm.c              | 12 ++++++------
 arch/x86/kvm/vmx/vmx.c              |  8 ++++----
 arch/x86/kvm/x86.c                  | 28 ++++++++++++++--------------
 include/linux/kvm_host.h            |  2 +-
 include/uapi/linux/kvm.h            |  6 +++---
 tools/include/uapi/linux/kvm.h      |  6 +++---
 virt/kvm/kvm_main.c                 |  4 ++--
 12 files changed, 43 insertions(+), 43 deletions(-)

```
#### [PATCH 1/3] KVM: x86: move kvm_vcpu_gfn_to_memslot() out of try_async_pf()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11689269
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5870F1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 14:38:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 40FF4206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 14:38:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gO5pbAQO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730484AbgG1OiE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 10:38:04 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:24801 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730470AbgG1OiA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 10:38:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1595947078;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tcz6xJruSZd06J4JeQP6Z/txJOVAN8x8GJXEVJsFQok=;
        b=gO5pbAQO0vY/sWlkUjHUFUIFm/2EujtSVP0VLnZcEUYohv1s4Uc6vdHT9w1YRVc3hs4685
        bUdrhNd3gHeYYUPH35jy10F1ltHiyqoSvKOpf4FLNvdcdD4YGoKYr2+ro8rUMVkh4IYyAT
        UH6GU8tCeYIREXAumMlM010gNTOkO98=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-421-zVbRciGGMe-6k7_0wCjbQw-1; Tue, 28 Jul 2020 10:37:57 -0400
X-MC-Unique: zVbRciGGMe-6k7_0wCjbQw-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B5F981005504;
        Tue, 28 Jul 2020 14:37:55 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.70])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0B69E7BD60;
        Tue, 28 Jul 2020 14:37:52 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Xu <peterx@redhat.com>, Michael Tsirkin <mst@redhat.com>,
        Julia Suvorova <jsuvorov@redhat.com>,
        Andy Lutomirski <luto@kernel.org>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/3] KVM: x86: move kvm_vcpu_gfn_to_memslot() out of
 try_async_pf()
Date: Tue, 28 Jul 2020 16:37:39 +0200
Message-Id: <20200728143741.2718593-2-vkuznets@redhat.com>
In-Reply-To: <20200728143741.2718593-1-vkuznets@redhat.com>
References: <20200728143741.2718593-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended. Slot flags will need to be analyzed
prior to try_async_pf() when KVM_MEM_PCI_HOLE is implemented.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c         | 14 ++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 13 insertions(+), 8 deletions(-)

```
#### [PATCH v2 1/3] KVM: LAPIC: Prevent setting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11688767
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DE5E138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 09:45:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B69320838
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 09:45:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="RfYnzTVa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728556AbgG1JpT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 05:45:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48162 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728197AbgG1JpR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 05:45:17 -0400
Received: from mail-pl1-x644.google.com (mail-pl1-x644.google.com
 [IPv6:2607:f8b0:4864:20::644])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 79CD0C061794;
        Tue, 28 Jul 2020 02:45:16 -0700 (PDT)
Received: by mail-pl1-x644.google.com with SMTP id u10so108778plr.7;
        Tue, 28 Jul 2020 02:45:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=YW61uT4gs7NLfpC0VAfH7u18rjoR4roJ54bakldbt1o=;
        b=RfYnzTVaaiIcgr+9v6Qpt+9Sn4A6BP7Q9yIcBs4oG6bfhviw+3JSTCk5bxF1v0Q9VP
         CUq/x8J/Q5xlyidW5jaxO5+QUJ1nIMYZT95rI6r8HwIvVYcixErDeg97g06HHpbEo/7F
         LwwNFv4NhVm7TKSdT4zHjQsYvZhtIh6u86VYKcMqCJCod6yK6Tl5nqYYVoMm8ubtdCGH
         quJmKGjBIogttIL6DsrSLmV1jPalEf2Fq+43Dty6I0iwCNBjfVc23hz+lt+1g9YQV+SJ
         3TP1vfw0eBPVO9iLug6dQSoZVxRimiRsV98IQ6Ahh8vFpJK16eXVvpLLG6ndwl95wNg4
         mHkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=YW61uT4gs7NLfpC0VAfH7u18rjoR4roJ54bakldbt1o=;
        b=S/277hyXeTjAkmgbQCqdwINDdJJWLN12opdg270kTVxjc18S4U4LlQqtNRp3h6DoqW
         hmfJBS0E/2aPOY8u+8/FBpk4qCPhilA6K8/8PPfbDTvB6bcbrTgDSwqpgtlFPEWBG7qy
         BhTPoxjwZO7hFV4s8dIuJweqwNCoyUm6dM+SSC74myDwWkaxja6c7KWPozLWrkSzSneB
         2VwBSSpbBL6P9S0Q1b1+rt53FtcW1BbtDGRh1knnfbDHtAoIrnagK3F1lOqhOW/TnZcy
         zCzjj15FAQ+mc7hPYH1bESIMp0kvcH9oSeew5I0/a65t/VTQIaLakn+SXfHAhIY8tF2W
         +3DA==
X-Gm-Message-State: AOAM5321UOlqULWQu45mXdZcC5m+wpiwPbc8Zadf7gKr3JvTSPkbg53F
        EroCfbUVz8I7Xqe4xn3dT4mrm2Nc
X-Google-Smtp-Source: 
 ABdhPJxD6tzllfcRVDmb1xoKhd2jMzTzXphKdkN4ooTcK2t2IBIzxcYpjGFm4Em3KQhe2BXXOgUfSA==
X-Received: by 2002:a17:90a:d30c:: with SMTP id
 p12mr3843893pju.4.1595929515664;
        Tue, 28 Jul 2020 02:45:15 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 r17sm17969173pfg.62.2020.07.28.02.45.12
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 28 Jul 2020 02:45:15 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, stable@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: LAPIC: Prevent setting the tscdeadline timer if
 the lapic is hw disabled
Date: Tue, 28 Jul 2020 17:45:04 +0800
Message-Id: <1595929506-9203-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Prevent setting the tscdeadline timer if the lapic is hw disabled.

Fixes: bce87cce88 (KVM: x86: consolidate different ways to test for in-kernel LAPIC)
Cc: <stable@vger.kernel.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v6 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11688303
Return-Path: <SRS0=Nuxp=BH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B284214B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:21:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98AB62250E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 28 Jul 2020 06:21:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727850AbgG1GVA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 28 Jul 2020 02:21:00 -0400
Received: from mga06.intel.com ([134.134.136.31]:26366 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727817AbgG1GU7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 28 Jul 2020 02:20:59 -0400
IronPort-SDR: 
 GJSciSUzwYNXqBsTC0fYaD1QvXmCi+X0t5suXuUw2T4TmRIIrQoDuEMK2GywVIEV3bgxOB71X5
 qD8/Vde2roIA==
X-IronPort-AV: E=McAfee;i="6000,8403,9695"; a="212681235"
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="212681235"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Jul 2020 23:20:55 -0700
IronPort-SDR: 
 4ESmEtAHDo+oAiqJBwmWisnUPbyQpTaa5NBvhStHj/O2hL60stvbP9JTrR4QkcLqUIouqoLUxI
 1D10wk8Kov6g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,405,1589266800";
   d="scan'208";a="320274380"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 27 Jul 2020 23:20:55 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, stefanha@gmail.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v6 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
Date: Mon, 27 Jul 2020 23:27:30 -0700
Message-Id: <1595917664-33276-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1595917664-33276-1-git-send-email-yi.l.liu@intel.com>
References: <1595917664-33276-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch refactors the vfio_iommu_type1_ioctl() to use switch instead of
if-else, and each command got a helper function.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Suggested-by: Christoph Hellwig <hch@infradead.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
v4 -> v5:
*) address comments from Eric Auger, add r-b from Eric.
---
 drivers/vfio/vfio_iommu_type1.c | 394 ++++++++++++++++++++++------------------
 1 file changed, 213 insertions(+), 181 deletions(-)

```
