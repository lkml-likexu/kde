#### [kvm-unit-tests PATCH v2 1/2] arm: Add mmu_get_pte() to the MMU API
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11894465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89420C388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:42:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D56D20678
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:42:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731036AbgKJOmh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 09:42:37 -0500
Received: from foss.arm.com ([217.140.110.172]:56828 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730059AbgKJOmg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 09:42:36 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 29FE21063;
        Tue, 10 Nov 2020 06:42:36 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 F1E1B3F718;
        Tue, 10 Nov 2020 06:42:34 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com, Luc Maranget <Luc.Maranget@inria.fr>
Subject: [kvm-unit-tests PATCH v2 1/2] arm: Add mmu_get_pte() to the MMU API
Date: Tue, 10 Nov 2020 14:42:05 +0000
Message-Id: <20201110144207.90693-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201110144207.90693-1-nikos.nikoleris@arm.com>
References: <20201110144207.90693-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Luc Maranget <Luc.Maranget@inria.fr>

Add the mmu_get_pte() function that allows a test to get a pointer to
the PTE for a valid virtual address. Return NULL if the MMU is off.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Signed-off-by: Luc Maranget <Luc.Maranget@inria.fr>
Co-Developed-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu-api.h |  1 +
 lib/arm/mmu.c         | 32 +++++++++++++++++++++-----------
 2 files changed, 22 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH v3 1/2] arm: Add mmu_get_pte() to the MMU API
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 11894999
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 868F8C388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 18:09:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48F8120797
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 18:09:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730468AbgKJSJx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 13:09:53 -0500
Received: from foss.arm.com ([217.140.110.172]:59518 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726152AbgKJSJx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 13:09:53 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id AA620139F;
        Tue, 10 Nov 2020 10:09:52 -0800 (PST)
Received: from camtx2.cambridge.arm.com (camtx2.cambridge.arm.com [10.1.7.22])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 841D03F7BB;
        Tue, 10 Nov 2020 10:09:51 -0800 (PST)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: mark.rutland@arm.com, jade.alglave@arm.com, luc.maranget@inria.fr,
        andre.przywara@arm.com, alexandru.elisei@arm.com,
        drjones@redhat.com, Luc Maranget <Luc.Maranget@inria.fr>
Subject: [kvm-unit-tests PATCH v3 1/2] arm: Add mmu_get_pte() to the MMU API
Date: Tue, 10 Nov 2020 18:09:23 +0000
Message-Id: <20201110180924.95106-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201110180924.95106-1-nikos.nikoleris@arm.com>
References: <20201110180924.95106-1-nikos.nikoleris@arm.com>
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Luc Maranget <Luc.Maranget@inria.fr>

Add the mmu_get_pte() function that allows a test to get a pointer to
the PTE for a valid virtual address. Return NULL if the MMU is off.

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Signed-off-by: Luc Maranget <Luc.Maranget@inria.fr>
Co-Developed-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm/asm/mmu-api.h |  1 +
 lib/arm/mmu.c         | 32 +++++++++++++++++++++-----------
 2 files changed, 22 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from userspace
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11894409
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 88B3FC388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:13:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2D1D921741
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 14:13:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="0vxWZ+z3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730829AbgKJONQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 09:13:16 -0500
Received: from mail.kernel.org ([198.145.29.99]:34300 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730200AbgKJONP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 09:13:15 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CB7C520809;
        Tue, 10 Nov 2020 14:13:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605017595;
        bh=bd+IPKZMKInt675zofeivrm7fgS7ZAV/NpMGLLlvmlA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=0vxWZ+z3r9DnuELPB4xuG6Se1eozAlangS+aLw5Tbkq8CLq/KsnqDaPp+nmWUlkeA
         ZG1GRxrz0S0/jfK20JbWVh/fR54qVfpgc8dZUkNanSm7799ZftvkVZdK17vndyESf7
         n04PUOyzhtT7voe7z8Mn83FD4nQAPN+Mqa0dj4hQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcUOW-009T8Q-W5; Tue, 10 Nov 2020 14:13:13 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Peng Liang <liangpeng10@huawei.com>, Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 1/3] KVM: arm64: Allow setting of ID_AA64PFR0_EL1.CSV2 from
 userspace
Date: Tue, 10 Nov 2020 14:13:06 +0000
Message-Id: <20201110141308.451654-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201110141308.451654-1-maz@kernel.org>
References: <20201110141308.451654-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, liangpeng10@huawei.com,
 will@kernel.org, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We now expose ID_AA64PFR0_EL1.CSV2=1 to guests running on hosts
that are immune to Spectre-v2, but that don't have this field set,
most likely because they predate the specification.

However, this prevents the migration of guests that have started on
a host the doesn't fake this CSV2 setting to one that does, as KVM
rejects the write to ID_AA64PFR0_EL2 on the grounds that it isn't
what is already there.

In order to fix this, allow userspace to set this field as long as
this doesn't result in a promising more than what is already there
(setting CSV2 to 0 is acceptable, but setting it to 1 when it is
already set to 0 isn't).

Fixes: e1026237f9067 ("KVM: arm64: Set CSV2 for guests on hardware unaffected by Spectre-v2")
Reported-by: Peng Liang <liangpeng10@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Will Deacon <will@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h |  2 ++
 arch/arm64/kvm/arm.c              | 16 ++++++++++++
 arch/arm64/kvm/sys_regs.c         | 42 ++++++++++++++++++++++++++++---
 3 files changed, 56 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/9] KVM: arm64: Introduce handling of AArch32 TTBCR2 traps
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11894347
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 03806C55ABD
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:36:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9EBA9216C4
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:36:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=kernel.org header.i=@kernel.org
 header.b="dvyQyJF4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730714AbgKJNga (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 08:36:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:49066 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730124AbgKJNga (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 08:36:30 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E209220797;
        Tue, 10 Nov 2020 13:36:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1605015390;
        bh=UGunF+n2Tlt0+f7UsAUfC3s0o6hjEqARAiJkLJ6vA5U=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=dvyQyJF4QHUvQA1NA6ddifwbuuMbIM41NuMC4GA1RwtS9VUVTWmryxQPloi0VySPY
         76T85oHrChx5xAXgQlEIWH6XPhY5nlIAGpA21K3l26SacvLh+dKcUUF64dWSdylj2/
         e6JoiG6B4uhGtKmHGASsU67NFOMAJvJivAVfFVYI=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kcToy-009SZy-1d; Tue, 10 Nov 2020 13:36:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, stable@vger.kernel.org
Subject: [PATCH v2 1/9] KVM: arm64: Introduce handling of AArch32 TTBCR2 traps
Date: Tue, 10 Nov 2020 13:36:11 +0000
Message-Id: <20201110133619.451157-2-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201110133619.451157-1-maz@kernel.org>
References: <20201110133619.451157-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARMv8.2 introduced TTBCR2, which shares TCR_EL1 with TTBCR.
Gracefully handle traps to this register when HCR_EL2.TVM is set.

Cc: stable@vger.kernel.org
Reported-by: James Morse <james.morse@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_host.h | 1 +
 arch/arm64/kvm/sys_regs.c         | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH 1/8] KVM: selftests: Update .gitignore
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11895301
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1A3DCC388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 20:48:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C50AC20665
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 20:48:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G3UE6yol"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729862AbgKJUsP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 15:48:15 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:49715 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725862AbgKJUsP (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 10 Nov 2020 15:48:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605041294;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+LWKFbnQZ4OkBqCtzuiWjVMY5oOducQlCQCmPMmoI0c=;
        b=G3UE6yolC/wzLX2VAmed8Iuo6CoaX3nTfpfUWsJjVply5xdH+qBruA/3F0QGsc8Z4YX7LD
        KG8ypp0IbgJpY+RyzpUKgK6iTfC53ePrQP3iZAAk5wu969xXJ34gkv+Je0XoAUQfELvNOJ
        OPlDFn8AMQSt5+GXSSBuej8yCr2TIxw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-340-mz444-41N2KkWZ-O2y0kpw-1; Tue, 10 Nov 2020 15:48:13 -0500
X-MC-Unique: mz444-41N2KkWZ-O2y0kpw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E3CA864156;
        Tue, 10 Nov 2020 20:48:11 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.179])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 105E51002C28;
        Tue, 10 Nov 2020 20:48:09 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH 1/8] KVM: selftests: Update .gitignore
Date: Tue, 10 Nov 2020 21:47:55 +0100
Message-Id: <20201110204802.417521-2-drjones@redhat.com>
In-Reply-To: <20201110204802.417521-1-drjones@redhat.com>
References: <20201110204802.417521-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add x86_64/tsc_msrs_test and remove clear_dirty_log_test.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Ben Gardon <bgardon@google.com>
---
 tools/testing/selftests/kvm/.gitignore | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: SVM: Fix offset computation bug in __sev_dbg_decrypt().
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11895749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C0D09C388F7
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 22:42:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B464206B6
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 22:42:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="y2ykcCir"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732398AbgKJWmV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 17:42:21 -0500
Received: from mail-bn7nam10on2052.outbound.protection.outlook.com
 ([40.107.92.52]:58465
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1732314AbgKJWmT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 17:42:19 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=kb3x6IFEqMV/HRwf3A3GWdF1Y8/nhXMdD2VITh8h7zPyilrti5C498lf2zs4fwAefbTRg2DUiHR34rrP6podd7Fv8EfI6VAElf7LhW199gBkDE2LIYtwCzj3HQB87lixqse4Hs/Lp9zebdUvPW6kzLVCeEzKYWXM1tcgHHQBrTLf1ODDD4MD5/5/CrpHB6qCccafE5NW7TJceGgw+OSitV3uCQejO4UC3OXIJgfrR1v6t67BgrrAw1R4LlDKllC0wMkYNm3pOtHYS4y9WU3zEHHlvPqJtXOD286dQ9q37F9Lbs/jIeKReOMIeRxWGQCly+qesV7M/DbjUN3SQPDxpg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Ld1/j0FTxqs5JZoQ9D9m+PbpnGiTPmd+wXwhgKpzV4U=;
 b=Mutbevr51szV+QrCQvnMw4jyR8yqKn+gacSShrUp+0f7TjDdEmLr3KPAqdK13arxylWeqBqJ3b5u3aHCNfTim6TXBnllRCUIG6GpdkqdBEh4j+SpCKKp2iaFiQSAIHVuEHc4C5mEWKkmo36ws1gbG3QT/mzb3fR0lSb48ZSlyioOF3j3T2tlGyHNXFCnd2lYsA9nsfHpXGCeKPB4QdkIWnFC+l3FRqxanAsneUJpYTOq2geGjc6ijWS58m+nurmglgoVM4tSogwMaEo6JB3l6QM4VQoOShyNW+bQbdv8vs6bjXSUjfANItsEQZEZ9l3GoOpO9+lP9/bCP/plRV5Ncg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Ld1/j0FTxqs5JZoQ9D9m+PbpnGiTPmd+wXwhgKpzV4U=;
 b=y2ykcCirgBPox+MjgmaZqL9ry494aI05V/s5/CPPnZVoFk1Twu8vn7zM6EnWqgbtzOnPYNd42voBpJmyv4Zc+9XM1RVpEunW/5jQQJAzaFLBC7EEtBRnQLxU8ZjcFKt1viB9Y1G0SgFh7qrg4olQTu/uArYX8bSfbNs3H1/qUig=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SA0PR12MB4590.namprd12.prod.outlook.com (2603:10b6:806:93::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21; Tue, 10 Nov
 2020 22:42:17 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3541.025; Tue, 10 Nov 2020
 22:42:17 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        Brijesh.Singh@amd.com, x86@kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, ssg.sos.patches@amd.com
Subject: [PATCH] KVM: SVM: Fix offset computation bug in __sev_dbg_decrypt().
Date: Tue, 10 Nov 2020 22:42:05 +0000
Message-Id: <20201110224205.29444-1-Ashish.Kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM3PR14CA0131.namprd14.prod.outlook.com
 (2603:10b6:0:53::15) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM3PR14CA0131.namprd14.prod.outlook.com (2603:10b6:0:53::15) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3541.21 via Frontend
 Transport; Tue, 10 Nov 2020 22:42:16 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 5cc2c8e8-e647-4f8a-8da5-08d885c9e012
X-MS-TrafficTypeDiagnostic: SA0PR12MB4590:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4590F0504B1BFC3BC5FC9F278EE90@SA0PR12MB4590.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4714;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Gd8B2gGWYHcoJOH5M3DCHCggF/W3rWx9p+zxg2Q9tS6wLJtGE5AqtLaFhzdIurukNbHTkqcIaFseFRRBDeDUTjY8fmCMcaXvIEZovp0y79r2YKlvF5NX3hMiVqcak6QsEqxIgZsu6T5Skk39cDMD8XRoDIgVSS8p3jBbh6w1NEL1DoY1jirFSrWGn1Wq8VuYQ4njp1YhtN7WXZ3GNM8yaFQgi5gLHQBQchAN6AmA6KIl4vqEGwmMyZe/MZlO9HhrADnbqTXVG4VJPZjdZqQU+Y0cfv8PCAXSTwbUvk6asxXB6KZmvjrv0v/0Tmo/Dlkmua3n+ZF91n5CCLFIRyfCjg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(366004)(39850400004)(376002)(136003)(396003)(83380400001)(8936002)(2906002)(478600001)(26005)(186003)(16526019)(4326008)(316002)(956004)(2616005)(8676002)(52116002)(7696005)(6916009)(66556008)(66476007)(66946007)(6486002)(5660300002)(36756003)(86362001)(6666004)(1076003)(4744005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 zLPd967Hckv4v8+E4upnL572adzifry9RLyPlM3unIC7E9OuTxaWqLBIR/YbqFLTkVlp2UVMjYNL7j0hP3532hBjo6hoOGYE/lclhzshBlblK0n1oPeeX0x7dhNf1YGtAx5X3K3joFG/atoaEssLRLtB5naZ3nYzGK1UWA+8Jp8Qcb2DtyjvRslH4btR6QsVwIcg4Xa3psFH2UVOEa9yiZBa+E9CNL/qWs0OC/T0tpBjprfo4WF/nNl0AbeJFMIW35iYLCMzBQivKe+pbwloVuzXWG4PKJ7Vj7usLPO5KSCW00OPRMx+xJkB24r+ec7AVuy8axCHbUpNyIBo577wa7rOJvre32KWWm1IMSjsYxMveDZBTmJgzcGGcop5Y2ACK+ttfhgdoonWmnNCZKX8z9CTVE2P3r/svzkQggeS9AlVw0Ti4DVds9zwnq5sdCn4EnWkqdmuxDOTk/s6Mi6pI+Lx0iDUQovIo7NoI4rZU8S+1n+doPQU6tvJi6JlvBM5Shg6HfJ0TJ38If7VMGLpkGxvnAt/FG43AJc9gwPaJEe3waJywNsn0vcYXZcecz1/aByUI+ApRV1JIVzb/09yH61yTfjjWSRJkghYCcXrJdTrf9G4PJEeIN1n2duh2gCnF30tgao4OsK5ZeBhQzbXGSGLZroSGwrcFfSCe3F8rH4bTPRejjB6uKpDL36SU0UU70nIUQoiPmR1BKdKxxs7veOf9yNbLRaIa54aNVfTBHpFthITR0wCxXvOVF2WjQLRWfrGLp4foOQ4Pg3S1SK1mIz7ifw9Hpw1+hYHyXl60NnXSx2umfryIHhqhlDnoccTG47TKpsfs7khNMpaWtRXZCv6O77bkJ15aJvk5+M9Nv8YaoXRdTKR8bvGlF+nmKcXnN6Fk2/dlLdqycQcDw0Zpg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5cc2c8e8-e647-4f8a-8da5-08d885c9e012
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Nov 2020 22:42:16.8857
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 KCg1ONHlCSgiBNqFt5geaEFqPPea8uciczYoFln9I8N1bmKDe0rDxez/eVGEh2HXfbee/qftFF4fMNjp7YFcDw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4590
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

Fix offset computation in __sev_dbg_decrypt() to include the
source paddr before it is rounded down to be aligned to 16 bytes
as required by SEV API. This fixes incorrect guest memory dumps
observed when using qemu monitor.

Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 arch/x86/kvm/svm/sev.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5 v4] KVM: x86: Change names of some of the kvm_x86_ops functions to make them more semantical and readable
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11892883
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3AE02C2D0A3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:25:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D7772207D3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:25:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="gZ5wLe5s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730460AbgKJBZp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 20:25:45 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:43094 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729452AbgKJBZp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 20:25:45 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1JlM2134847;
        Tue, 10 Nov 2020 01:25:33 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=RfTNumpSEEH4ytP1ibwXcPjCeqUMXJxiPwdNHiSal3U=;
 b=gZ5wLe5saf2k7EbE8uUEKhE06l46KygDUU9fXF9kssqyPCyDgASshoMmY+c0yR9mKZmV
 uzbMp8KbVJITe+yDTaTPDo4wHVQFRJ6s8aYnPwEAB9qBJJ0H7nyHfs3KgyVwU/OCbaSJ
 NS9aofs3oqhsah0GZZ6urhi0UCmwZRkr5/cs6k1QM48AEoX9Kmr/6QbzFlZ4rubkqYXP
 KDGMgT9Jjj3Cns3jcYUK0SowTiOQCfSqwYgaJ74mV0zkRlSfY62WdvqAT1u5s1RzJDWp
 IOj7mRMm2kTxDIvT6R8QMdJjFXyYPJdHEqCqjz5DwGWplf56NFxbaTFWEx/k4st0X8eU nw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 34p72ef9na-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 10 Nov 2020 01:25:33 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1K7V3024070;
        Tue, 10 Nov 2020 01:23:33 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 34p5gw4a0r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Nov 2020 01:23:33 +0000
Received: from abhmp0016.oracle.com (abhmp0016.oracle.com [141.146.116.22])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 0AA1NWjf014143;
        Tue, 10 Nov 2020 01:23:32 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 09 Nov 2020 17:23:31 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com, vkuznets@redhat.com, qemu-devel@nongnu.org
Subject: [PATCH 1/5 v4] KVM: x86: Change names of some of the kvm_x86_ops
 functions to make them more semantical and readable
Date: Tue, 10 Nov 2020 01:23:08 +0000
Message-Id: <20201110012312.20820-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20201110012312.20820-1-krish.sadhukhan@oracle.com>
References: <20201110012312.20820-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999 mlxscore=0
 spamscore=0 phishscore=0 adultscore=0 malwarescore=0 suspectscore=4
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100008
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999 mlxscore=0
 malwarescore=0 suspectscore=4 lowpriorityscore=0 adultscore=0 phishscore=0
 priorityscore=1501 spamscore=0 impostorscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100008
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
 arch/x86/include/asm/kvm_host.h     | 16 +++++++--------
 arch/x86/kvm/lapic.c                |  2 +-
 arch/x86/kvm/svm/nested.c           |  2 +-
 arch/x86/kvm/svm/svm.c              | 14 +++++++-------
 arch/x86/kvm/vmx/nested.c           |  2 +-
 arch/x86/kvm/vmx/vmx.c              | 10 +++++-----
 arch/x86/kvm/x86.c                  | 30 ++++++++++++++---------------
 include/linux/kvm_host.h            |  2 +-
 include/uapi/linux/kvm.h            |  6 +++---
 tools/include/uapi/linux/kvm.h      |  6 +++---
 virt/kvm/kvm_main.c                 |  4 ++--
 15 files changed, 51 insertions(+), 51 deletions(-)

```
#### [PATCH] nVMX: Test 'Type' and 'S' portions of Access Rights field in guest segment registers
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11892897
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E6FEDC2D0A3
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:46:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 813D820789
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 01:46:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="BLgteSQ0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729847AbgKJBqO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 9 Nov 2020 20:46:14 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:37492 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725889AbgKJBqO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 9 Nov 2020 20:46:14 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1hj4o056466;
        Tue, 10 Nov 2020 01:46:08 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=i2jWfVMlK5gGnkaaFfcTgSOAhQ2y3N6KfAlSePc/E+A=;
 b=BLgteSQ0rIZVI7zQRVxTfa/uMhoyl0E8GtNCfuvbCign7uswWhJsDVtv8VL0EtTqwqd7
 wjTL7mewAXZQXy1D7coIr5YptkFxcf5qJvFwv/tjNpQyxFzwUyXuLF9ozXlgM5MrzeI2
 0w+y/0IZ/n8yMZRpG2B/sFXW/oPAUAR2lqFDtmzgrJiWOmbA/cJ+xK0ucvlwPT5riEjQ
 8ucUrZMCtzEFY2Ud5HofdI9e8WbFX2oH7pnXaD0ABBHSqqmXc1eLrT0PpRT7z0ZgNxmI
 jkbv6fWvor16HLOaH1+R7Q3Ys+3hGNzuIBtt8N0Oa9le4y+tLdGxM43uOj+PnOTYfGFm Xw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 34nkhks4q8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 10 Nov 2020 01:46:07 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0AA1e7Xt073227;
        Tue, 10 Nov 2020 01:46:07 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3030.oracle.com with ESMTP id 34p5gw504x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 10 Nov 2020 01:46:07 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0AA1k56T031572;
        Tue, 10 Nov 2020 01:46:05 GMT
Received: from sadhukhan-nvmx.osdevelopmeniad.oraclevcn.com (/100.100.230.226)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 09 Nov 2020 17:46:05 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        pbonzini@redhat.com
Subject: [PATCH] nVMX: Test 'Type' and 'S' portions of Access Rights field in
 guest segment registers
Date: Tue, 10 Nov 2020 01:45:56 +0000
Message-Id: <20201110014556.14913-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=999 mlxscore=0
 spamscore=0 phishscore=0 adultscore=0 malwarescore=0 suspectscore=1
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100011
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9800
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 priorityscore=1501
 mlxscore=0 suspectscore=1 mlxlogscore=999 lowpriorityscore=0 spamscore=0
 malwarescore=0 adultscore=0 clxscore=1015 bulkscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011100011
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Segment Registers" in Intel SDM vol 3C,
the following checks are performed on the Guest Segment Registers on vmentry
of nested guests:

    Access-rights field:
	— Bits 3:0 (Type):
	    - CS: The values allowed depend on the setting of the “unrestricted
	          guest” VM-execution control:
		    - If the control is 0, the Type must be 9, 11, 13, or 15
		      (accessed code segment).
		    - If the control is 1, the Type must be either 3 (read/write
		      accessed expand-up data segment) or one of 9, 11, 13, and
		      15 (accessed code segment).
	    - SS: If SS is usable, the Type must be 3 or 7 (read/write,
		  accessed data segment).
	    - DS, ES, FS, GS: The following checks apply if the register is
	      		      usable:
			- Bit 0 of the Type must be 1 (accessed).
			- If bit 3 of the Type is 1 (code segment), then bit 1
		  	  of the Type must be 1 (readable).
	— Bit 4 (S): If the register is CS or if the register is usable, S must
	  be 1.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx_tests.c | 165 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 165 insertions(+)

```
#### [PATCH] perf/intel: Remove Perfmon-v4 counter_freezing support
##### From: Peter Zijlstra <peterz@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Zijlstra <peterz@infradead.org>
X-Patchwork-Id: 11894653
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B42EC5517A
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 15:37:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CAE8E20795
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 15:37:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="1R3Tp8f8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731068AbgKJPhs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 10:37:48 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43184 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729794AbgKJPhs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 10:37:48 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0D8D7C0613CF;
        Tue, 10 Nov 2020 07:37:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=In-Reply-To:Content-Type:MIME-Version:
        References:Message-ID:Subject:Cc:To:From:Date:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=0Ag8YSfqUUAom5EDixyISX08GuKdtdVeG7iNICf4Baw=;
 b=1R3Tp8f8Fm8lLtp0ok+TpiT9fH
        WtLFIDCP7fU6BfP8z7Rp4vU6GgKCW6MgrDSaNTUtI2XZJmMo1C+tAFytajJBfZ37pDOCaH8okhOcR
        EBk7qznAnt9QDJi34mLvKi4KhfXRagqGR/jDFGUO6N/X1Z/xiVRNmKraiOACEcfcXnJBai2b4jDCD
        2rEtmjguJyk2JgaXPOQ9xjLE7wY+iG29+2UaWG9kuYYo+2K1qG4+mNIDIdxS8xJTvBvay93Qaup5x
        vjS6yNZPqN70f6ZTwgQ7vuH0AKmFu74ZzISmTnT3xeu5le6f/F9rDQ+WfvNDlY8/om7FDJalc7EtY
        VwVIHJqg==;
Received: from j217100.upc-j.chello.nl ([24.132.217.100]
 helo=noisy.programming.kicks-ass.net)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kcVi1-0005eD-RI; Tue, 10 Nov 2020 15:37:26 +0000
Received: from hirez.programming.kicks-ass.net
 (hirez.programming.kicks-ass.net [192.168.1.225])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (Client did not present a certificate)
        by noisy.programming.kicks-ass.net (Postfix) with ESMTPS id
 8779A300238;
        Tue, 10 Nov 2020 16:37:21 +0100 (CET)
Received: by hirez.programming.kicks-ass.net (Postfix, from userid 1000)
        id 6B4A92025CA28; Tue, 10 Nov 2020 16:37:21 +0100 (CET)
Date: Tue, 10 Nov 2020 16:37:21 +0100
From: Peter Zijlstra <peterz@infradead.org>
To: Like Xu <like.xu@linux.intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Kan Liang <kan.liang@linux.intel.com>, luwei.kang@intel.com,
        Thomas Gleixner <tglx@linutronix.de>, wei.w.wang@intel.com,
        Tony Luck <tony.luck@intel.com>,
        Stephane Eranian <eranian@google.com>,
        Mark Gross <mgross@linux.intel.com>,
        Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] perf/intel: Remove Perfmon-v4 counter_freezing support
Message-ID: <20201110153721.GQ2651@hirez.programming.kicks-ass.net>
References: <20201109021254.79755-1-like.xu@linux.intel.com>
 <20201110151257.GP2611@hirez.programming.kicks-ass.net>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20201110151257.GP2611@hirez.programming.kicks-ass.net>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On Tue, Nov 10, 2020 at 04:12:57PM +0100, Peter Zijlstra wrote:
> On Mon, Nov 09, 2020 at 10:12:37AM +0800, Like Xu wrote:
> > The Precise Event Based Sampling(PEBS) supported on Intel Ice Lake server
> > platforms can provide an architectural state of the instruction executed
> > after the instruction that caused the event. This patch set enables the
> > the PEBS via DS feature for KVM (also non) Linux guest on the Ice Lake.
> > The Linux guest can use PEBS feature like native:
> > 
> >   # perf record -e instructions:ppp ./br_instr a
> >   # perf record -c 100000 -e instructions:pp ./br_instr a
> > 
> > If the counter_freezing is not enabled on the host, the guest PEBS will
> > be disabled on purpose when host is using PEBS facility. By default,
> > KVM disables the co-existence of guest PEBS and host PEBS.
> 
> Uuhh, what?!? counter_freezing should never be enabled, its broken. Let
> me go delete all that code.
---
Subject: perf/intel: Remove Perfmon-v4 counter_freezing support

Perfmon-v4 counter freezing is fundamentally broken; remove this default
disabled code to make sure nobody uses it.

The feature is called Freeze-on-PMI in the SDM, and if it would do that,
there wouldn't actually be a problem, *however* it does something subtly
different. It globally disables the whole PMU when it raises the PMI,
not when the PMI hits.

This means there's a window between the PMI getting raised and the PMI
actually getting served where we loose events and this violates the
perf counter independence. That is, a counting event should not result
in a different event count when there is a sampling event co-scheduled.

This is known to break existing software.

Signed-off-by: Peter Zijlstra (Intel) <peterz@infradead.org>
---
 arch/x86/events/intel/core.c | 152 -------------------------------------------
 arch/x86/events/perf_event.h |   3 +-
 2 files changed, 1 insertion(+), 154 deletions(-)

```
#### [PATCH] vfio iommu type1: Improve vfio_iommu_type1_pin_pages performance
##### From: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>
X-Patchwork-Id: 11894379
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.2 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,HK_RANDOM_FROM,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_SANE_1 autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DFEA5C55ABD
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:42:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9180620797
	for <kvm@archiver.kernel.org>; Tue, 10 Nov 2020 13:42:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731018AbgKJNmi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 10 Nov 2020 08:42:38 -0500
Received: from szxga02-in.huawei.com ([45.249.212.188]:2492 "EHLO
        szxga02-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729832AbgKJNmh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Nov 2020 08:42:37 -0500
Received: from dggeme753-chm.china.huawei.com (unknown [172.30.72.53])
        by szxga02-in.huawei.com (SkyGuard) with ESMTP id 4CVpvR6PX3zQppv;
        Tue, 10 Nov 2020 21:42:27 +0800 (CST)
Received: from [10.174.184.120] (10.174.184.120) by
 dggeme753-chm.china.huawei.com (10.3.19.99) with Microsoft SMTP Server
 (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id
 15.1.1913.5; Tue, 10 Nov 2020 21:42:33 +0800
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        <alex.williamson@redhat.com>
CC: <kwankhede@nvidia.com>, <wu.wubin@huawei.com>,
        <maoming.maoming@huawei.com>, <xieyingtai@huawei.com>,
        <lizhengui@huawei.com>, <wubinfeng@huawei.com>,
        <xuxiaoyang2@huawei.com>
From: "xuxiaoyang (C)" <xuxiaoyang2@huawei.com>
Subject: [PATCH] vfio iommu type1: Improve vfio_iommu_type1_pin_pages
 performance
Message-ID: <2553f102-de17-b23b-4cd8-fefaf2a04f24@huawei.com>
Date: Tue, 10 Nov 2020 21:42:33 +0800
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:78.0) Gecko/20100101
 Thunderbird/78.3.2
MIME-Version: 1.0
Content-Language: en-GB
X-Originating-IP: [10.174.184.120]
X-ClientProxiedBy: dggeme710-chm.china.huawei.com (10.1.199.106) To
 dggeme753-chm.china.huawei.com (10.3.19.99)
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_iommu_type1_pin_pages is very inefficient because
it is processed page by page when calling vfio_pin_page_external.
Added contiguous_vaddr_get_pfn to process continuous pages
to reduce the number of loops, thereby improving performance.

Signed-off-by: Xiaoyang Xu <xuxiaoyang2@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 241 ++++++++++++++++++++++++++++----
 1 file changed, 214 insertions(+), 27 deletions(-)

--
2.19.1

```
