#### [PATCH 1/2] kvm: x86: Refine kvm_write_tsc synchronization generations
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11605997
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF457912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 23:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96DA920644
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 23:07:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="qNvgE9pA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726652AbgFOXH5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 19:07:57 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33510 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725960AbgFOXH5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 19:07:57 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0234BC061A0E
        for <kvm@vger.kernel.org>; Mon, 15 Jun 2020 16:07:57 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id h18so15502420qkj.13
        for <kvm@vger.kernel.org>; Mon, 15 Jun 2020 16:07:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=xcoRC3ukd3JVnqlPGdKawsU/brIQlrTI1XM8BxAKzo0=;
        b=qNvgE9pA0YdBpFN8P5+egecHo526fpmt4Uq5HFPR05TM3ek+tBUrzY5I8/GhaFUmqX
         W5+Y3ispf43Wy5mGsPVD376WYegQvJZIC+fGK+DRmDIBcpRP5L6iiA5mALQzocGKULRi
         aHdDBgVE68TvwuTLKapsXEY9ma3QjdBv5t3x8ehV6JV6JznyPyfV+QxE0iPJzXa8hqN+
         ZHsgDwftz6xx9FBwL9AD059zyFWG/yWEwWbGXL6z7PfuPWV9zrogxR480iPmE4W3rtyT
         3V9U6Xsh6bIRFeKjdeKLwEV4DiybfJyvYr6eKOjUBPqNWxywWj1G9V4EbGMVGLzU2gLK
         4EMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=xcoRC3ukd3JVnqlPGdKawsU/brIQlrTI1XM8BxAKzo0=;
        b=FXZnRkHKZwdxwq85FyIrxgYEgi97x8BvkxAaQV0RZP+qmrTKh0HYXKsjyG5jwd6u9R
         vCrx4/SXZn/gcn/N/ivverFoKCME34F+AlxlATJHbPGX+0Zc5ojoB5TbKMg8E4zhu2HS
         FNjnkFavlMIlqoDdzWk3vPTUvRpJ6R0rZK/MtZPMSyBYXGq8aK2UeI7WSTZp+TBFPdHJ
         cdDhH6AGXPSuRw4vL9vqSe68t2kKbIbAh4E1ll8fH41ktRfQu8tv0k/c6gRHf4Hop6eq
         evUHcYGdDmvuJGGW97ZmIKFmMZnluhvmHbThvGtiGy7MhrbfhwS6W6780Zu7cHQGHi4Z
         c6Zw==
X-Gm-Message-State: AOAM5303SrfEGzC+o/7C5JQ0Sssvp/mQtPmItWGG8HWN8pnmg+1ubCAN
        yZU6ae2XnIZiwxQJGWItOj9IoGPOOdIM5WJ06o7/wKnoFUvS/Ex89YtNkEh7w1JqGdKa/FPDT21
        rLBOmic3jTtxmHu++ZJqM5ax9UF8+oduyJgUd1T58k5LnmKlCCKD4YT4bOns1iWc=
X-Google-Smtp-Source: 
 ABdhPJy7/o7amkHHEBR+jxgFfk29OJ/uSYG4K0BSuLhWRqEMXkXcD7V3eNPH7A2RdX2rL1zYdGwXX/z69lxehw==
X-Received: by 2002:a05:6214:10e1:: with SMTP id
 q1mr84631qvt.78.1592262476058;
 Mon, 15 Jun 2020 16:07:56 -0700 (PDT)
Date: Mon, 15 Jun 2020 16:07:49 -0700
Message-Id: <20200615230750.105008-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.290.gba653c62da-goog
Subject: [PATCH 1/2] kvm: x86: Refine kvm_write_tsc synchronization
 generations
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Start a new TSC synchronization generation whenever the
IA32_TIME_STAMP_COUNTER MSR is written on a vCPU that has already
participated in the current TSC synchronization generation.

Previously, it was not possible to restore the IA32_TIME_STAMP_COUNTER
MSR to a value less than the TSC frequency. Since vCPU initialization
sets the IA32_TIME_STAMP_COUNTER MSR to zero, a subsequent
KVM_SET_MSRS ioctl that attempted to write a small value to the
IA32_TIME_STAMP_COUNTER MSR was viewed as an attempt at TSC
synchronization. Notably, this was the case even for single vCPU VMs,
which were always synchronized.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 13 +++++--------
 1 file changed, 5 insertions(+), 8 deletions(-)

```
#### [PATCH 1/4] KVM: arm64: Enable Pointer Authentication at EL2 if available
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11604183
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3B0321392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 08:20:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A1DD20739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 08:20:10 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592209210;
	bh=3JOu3whXJHagX3A5FXu4YOyMwg0buhIfq0J6saBPEWM=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=WJ6zOby/xKkK49ZY/20IF7b1YW4v0tzhahrQDOBGlZa5257qWlqGHn8/NYMTWiRnu
	 lachxfGBaoKMh0p0YJm/scZCMW3d/uoeGm1uhAyeWCLD3pgZk/JuqkQKpu8ROtdR0Y
	 2u+K4Bod/rt8DuUXdTE5G02AjJKeRkmrKB+anq8s=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728761AbgFOIUG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 04:20:06 -0400
Received: from mail.kernel.org ([198.145.29.99]:39142 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728426AbgFOIUF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 04:20:05 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0CA85206E2;
        Mon, 15 Jun 2020 08:20:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592209205;
        bh=3JOu3whXJHagX3A5FXu4YOyMwg0buhIfq0J6saBPEWM=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=MSVi3gmPR9xUm2rCakwEj3nJ130UF203cE4RAlDZuI/haaRGRkXWZNddLJefxqnsZ
         V0TFhXghmCZq4V9HsILYwivR5UaqASj/PZe163BnLIJDF5hNmTXWy1sNbEHfZLzoil
         nTRsqhvhoxu5nK9fr7nRde30rwecznbQbbHFG94Q=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=wait-a-minute.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jkkLb-0031ew-Ju; Mon, 15 Jun 2020 09:20:03 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH 1/4] KVM: arm64: Enable Pointer Authentication at EL2 if
 available
Date: Mon, 15 Jun 2020 09:19:51 +0100
Message-Id: <20200615081954.6233-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200615081954.6233-1-maz@kernel.org>
References: <20200615081954.6233-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While initializing EL2, switch Pointer Authentication if detected
from EL1. We use the EL1-provided keys though.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Andrew Scull <ascull@google.com>
---
 arch/arm64/kvm/hyp-init.S | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v2 01/17] KVM: arm64: Factor out stage 2 page table data from struct kvm
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11604991
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4D815913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 13:27:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FE17207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 13:27:45 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592227665;
	bh=M9LpFcvG8ZW1BsEh3St5h215XBxQUQjrBXD//1DguhA=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=RqtdVU/spqow9h8NajwLCSq/HI+7DMmTIBdN3pqg5/7MGFeii5dYyyci9gh89j5Q0
	 Vxw0YkIPb1XftZLyZG0prNSFw6cYAJvi8GVTvVxevcd3ptuRMChU91cZrtD7wqri/F
	 s67NA7gCzSOk0d9RBk1eAQpkiic7OS50rKLXEsuE=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730446AbgFON1n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 09:27:43 -0400
Received: from mail.kernel.org ([198.145.29.99]:58488 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730145AbgFON1j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 09:27:39 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1BDF1207BB;
        Mon, 15 Jun 2020 13:27:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592227658;
        bh=M9LpFcvG8ZW1BsEh3St5h215XBxQUQjrBXD//1DguhA=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=jRmV4lK3TLKtBRrZ0d/C4ht1GEmNJw/Y3U8IihjNvXLauFlE0087LTGPyCASlQX4J
         NUOrwHKCfrTegcURL0qoCLG7G41H9Hv+GYq6CH6IwuQrJ1LxER24kcGrTcidOttaaj
         Zm3LwsodWGKeGYEqUsPFaaz1pqgxog6x4D5gbIGk=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jkp9E-0036w9-DF; Mon, 15 Jun 2020 14:27:36 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        George Cherian <gcherian@marvell.com>,
        "Zengtao (B)" <prime.zeng@hisilicon.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2 01/17] KVM: arm64: Factor out stage 2 page table data from
 struct kvm
Date: Mon, 15 Jun 2020 14:27:03 +0100
Message-Id: <20200615132719.1932408-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200615132719.1932408-1-maz@kernel.org>
References: <20200615132719.1932408-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, Dave.Martin@arm.com, jintack@cs.columbia.edu,
 alexandru.elisei@arm.com, gcherian@marvell.com, prime.zeng@hisilicon.com,
 ascull@google.com, will@kernel.org, catalin.marinas@arm.com,
 mark.rutland@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christoffer Dall <christoffer.dall@arm.com>

As we are about to reuse our stage 2 page table manipulation code for
shadow stage 2 page tables in the context of nested virtualization, we
are going to manage multiple stage 2 page tables for a single VM.

This requires some pretty invasive changes to our data structures,
which moves the vmid and pgd pointers into a separate structure and
change pretty much all of our mmu code to operate on this structure
instead.

The new structure is called struct kvm_s2_mmu.

There is no intended functional change by this patch alone.

Reviewed-by: James Morse <james.morse@arm.com>
[Designed data structure layout in collaboration]
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Co-developed-by: Marc Zyngier <maz@kernel.org>
[maz: Moved the last_vcpu_ran down to the S2 MMU structure as well]
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h  |   7 +-
 arch/arm64/include/asm/kvm_host.h |  32 +++-
 arch/arm64/include/asm/kvm_mmu.h  |  16 +-
 arch/arm64/kvm/arm.c              |  36 ++--
 arch/arm64/kvm/hyp/switch.c       |   8 +-
 arch/arm64/kvm/hyp/tlb.c          |  52 +++---
 arch/arm64/kvm/mmu.c              | 278 +++++++++++++++++-------------
 7 files changed, 233 insertions(+), 196 deletions(-)

```
#### [PATCH] KVM: async_pf: change kvm_setup_async_pf()/kvm_arch_setup_async_pf() return type to bool
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11604673
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 99D8A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:13:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 81A5E2083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:13:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PWfwzkXr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729975AbgFOMNv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 08:13:51 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:29393 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729947AbgFOMNn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Jun 2020 08:13:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592223221;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VF/bKvZ3DQHEsMfrPd1x4vxGKYtMws61vYLWQVeHqIA=;
        b=PWfwzkXrEH8SEyO9Y+dvC+zInuZQq/hOz/gaB0VLPtFpKgJIV823zIgdg7V9f55MChrvqq
        PRrtd1GbfxY0lrDWZUGUf1+JC+OErbr+r1N9f1habAs0r74+CfYA4Zv1xM74JVJL0kT5sb
        jqR/BGeOeDd0m7bsxcf0sGNPW4JRgdk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-261-yHHbBN9xOa6F1x-56JI5Aw-1; Mon, 15 Jun 2020 08:13:39 -0400
X-MC-Unique: yHHbBN9xOa6F1x-56JI5Aw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A5932108BD0F;
        Mon, 15 Jun 2020 12:13:37 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.105])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 949BE60C47;
        Mon, 15 Jun 2020 12:13:35 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Vivek Goyal <vgoyal@redhat.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: async_pf: change
 kvm_setup_async_pf()/kvm_arch_setup_async_pf() return type to bool
Date: Mon, 15 Jun 2020 14:13:34 +0200
Message-Id: <20200615121334.91300-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unlike normal 'int' functions returning '0' on success, kvm_setup_async_pf()/
kvm_arch_setup_async_pf() return '1' when a job to handle page fault
asynchronously was scheduled and '0' otherwise. To avoid the confusion
change return type to 'bool'.

No functional change intended.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 20 +++++++++-----------
 arch/x86/kvm/mmu/mmu.c   |  4 ++--
 include/linux/kvm_host.h |  4 ++--
 virt/kvm/async_pf.c      | 16 ++++++++++------
 4 files changed, 23 insertions(+), 21 deletions(-)

```
#### [PATCH] kvm: i386: allow TSC to differ by NTP correction bounds without TSC scaling
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 11604645
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48B1092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:10:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 318AE206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:10:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YuMC37me"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729733AbgFOMK2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 08:10:28 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:24027 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729630AbgFOMK2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Jun 2020 08:10:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592223026;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=dEcd7Ou8Wc2IM9OEpa2krlue9KWBHBJ5MmJhN3pvDxo=;
        b=YuMC37mek9wHDTiwqXe4u03LUWfyTT3sGB4GmU33hmkSmTzxuvVa7rs5lMFspSc/+8zTAc
        ZFK8gacO2YsveDS49HkbI2qSDlaarp/Hqz4Enz0M3Edc/FKKkxTfJzj+D6nGDkV5afWNzo
        9hbyABH0wM7M9ba9qCoLtAdwJ5elcDw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-196-reJFroX6NsCuo-629NVw0Q-1; Mon, 15 Jun 2020 08:10:24 -0400
X-MC-Unique: reJFroX6NsCuo-629NVw0Q-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DCEE68C23B8;
        Mon, 15 Jun 2020 12:09:52 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-3.gru2.redhat.com [10.97.112.3])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 5F61C80883;
        Mon, 15 Jun 2020 12:09:52 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 31640430716A; Mon, 15 Jun 2020 09:01:27 -0300 (-03)
Date: Mon, 15 Jun 2020 09:01:27 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: qemu-devel <qemu-devel@nongnu.org>, kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>
Subject: [PATCH] kvm: i386: allow TSC to differ by NTP correction bounds
 without TSC scaling
Message-ID: <20200615120127.GB224592@fuller.cnet>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Linux TSC calibration procedure is subject to small variations
(its common to see +-1 kHz difference between reboots on a given CPU, for example).

So migrating a guest between two hosts with identical processor can fail, in case 
of a small variation in calibrated TSC between them.

Allow a conservative 250ppm error between host TSC and VM TSC frequencies,
rather than requiring an exact match. NTP daemon in the guest can
correct this difference.

Also change migration to accept this bound.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

```
#### [PATCH] KVM: MIPS: Fix a build error for !CPU_LOONGSON64
##### From: Huacai Chen <chenhc@lemote.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Huacai Chen <chenhc@lemote.com>
X-Patchwork-Id: 11603929
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D20C814E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 06:55:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B96C32067B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 06:55:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="MG2ddZSz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728475AbgFOGzi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 02:55:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52494 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728422AbgFOGzh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 02:55:37 -0400
Received: from mail-pj1-x1041.google.com (mail-pj1-x1041.google.com
 [IPv6:2607:f8b0:4864:20::1041])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 65D03C061A0E;
        Sun, 14 Jun 2020 23:55:37 -0700 (PDT)
Received: by mail-pj1-x1041.google.com with SMTP id i12so6375472pju.3;
        Sun, 14 Jun 2020 23:55:37 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=Mp3XO3Na1QTIvxdf9SelVMciyJHSxvV4qQlUSTKYIto=;
        b=MG2ddZSzOuekSNoUjlMPvQvWY+r4kHTFqYbtyeHlMNtDb+6OD16d5LgjKdHGlXJuhl
         NobjgGxUHoMZMaGiZ3rU66m1fD/PWnm8HVBkmQ2TWaLJY10qQdvUr5QRP+mSGjZUIp4b
         IltN74+zPN60an6dWoocAnv7XNGPOrceMJF3TsfqQNbqCSjCVJjkHlwnAU7e6yn7xgr1
         qOZBtdhzOaHFsF4nfB3p6Gv726gF6FXMZEq5UTh1QvGTxZE7IAL5suNd5NRFZDC0Exll
         XlBbvC18oJkOfLJu+cxSzOVmoeB7a+ovEhL45yI8aK3BiqiQknNbztmY5RZlMN00PWHs
         PKJg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=Mp3XO3Na1QTIvxdf9SelVMciyJHSxvV4qQlUSTKYIto=;
        b=Q0gEzzvUpfWEdx9tklh1wjUEcwNUIQSasfsCblapYZkJ9/O0bc8MXFzvotehKIx6u6
         wCpnSGXrd99ym63MAgrYlONfr43JB9CB0eGQs5YLpdCD4bPZTyVwtvADJVly+fX1CQ47
         GI8pcRIT3yzJth2G7uIyXWpxYkzEckixNMe6+swtIPapXLOHLwfkUZQRus24S3oqEPBr
         dk5aDCaIpqfxzpthkHzGZ8004vQqPZ+S990Jw0a/uNMMgM1LI6yv0xVFYo/9ukLMPj8F
         P97USr4iCGLpAeAXsUdjrteZy/r3UKqTlfqM0PKq0hNlajw6AafariFKp9MISosdpU2O
         8lLg==
X-Gm-Message-State: AOAM531a2p21xFcH8lv0G0DQtkTz/oQi0sxGI3Kq15liX+fYsa+1ibjm
        QvzphgqbBDbV2nwvDj28lZrFhExP20FKiQ==
X-Google-Smtp-Source: 
 ABdhPJzYOysVmo0LJNGKXOWn7wSz1H3h3OB0X6nkDA+Qh5Qcx9wQTKdRLmdfmnYJy++R2kUQTOHC9Q==
X-Received: by 2002:a17:90a:36aa:: with SMTP id
 t39mr9934780pjb.185.1592204136968;
        Sun, 14 Jun 2020 23:55:36 -0700 (PDT)
Received: from software.domain.org (28.144.92.34.bc.googleusercontent.com.
 [34.92.144.28])
        by smtp.gmail.com with ESMTPSA id
 c8sm11453123pjn.16.2020.06.14.23.55.34
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Sun, 14 Jun 2020 23:55:36 -0700 (PDT)
From: Huacai Chen <chenhc@lemote.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        Fuxin Zhang <zhangfx@lemote.com>,
        Huacai Chen <chenhuacai@gmail.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>
Subject: [PATCH] KVM: MIPS: Fix a build error for !CPU_LOONGSON64
Date: Mon, 15 Jun 2020 14:56:55 +0800
Message-Id: <1592204215-28704-1-git-send-email-chenhc@lemote.com>
X-Mailer: git-send-email 2.7.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During the KVM merging progress, a CONFIG_CPU_LOONGSON64 guard in commit
7f2a83f1c2a941ebfee53 ("KVM: MIPS: Add CPUCFG emulation for Loongson-3")
is missing by accident. So add it to avoid building error.

Fixes: 7f2a83f1c2a941ebfee53 ("KVM: MIPS: Add CPUCFG emulation for Loongson-3")
Reported-by: kernel test robot <lkp@intel.com>
Signed-off-by: Huacai Chen <chenhc@lemote.com>
---
 arch/mips/kvm/mips.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM: MIPS: fix spelling mistake "Exteneded" -> "Extended"
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin King <colin.king@canonical.com>
X-Patchwork-Id: 11604201
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A7A71392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 08:26:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7AE982068E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 08:26:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728875AbgFOI0k (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 04:26:40 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:59045 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728162AbgFOI0k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 04:26:40 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1jkkRw-00013P-LO; Mon, 15 Jun 2020 08:26:36 +0000
From: Colin King <colin.king@canonical.com>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Huacai Chen <chenhc@lemote.com>, linux-mips@vger.kernel.org,
        kvm@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: MIPS: fix spelling mistake "Exteneded" -> "Extended"
Date: Mon, 15 Jun 2020 09:26:36 +0100
Message-Id: <20200615082636.7004-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.27.0.rc0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

There is a spelling mistake in a couple of kvm_err messages. Fix them.

Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 arch/mips/kvm/emulate.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: allow TSC to differ by NTP correction bounds without TSC scaling
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 11604643
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31D1992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:10:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1982920714
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:10:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aA7NvU+k"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729713AbgFOMK1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 08:10:27 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:32337 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728285AbgFOMK0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Jun 2020 08:10:26 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1592223025;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=UZ63vXCgEw6WAGyH4uprnPcFrCOxEXqlq7oGooz1Q4U=;
        b=aA7NvU+kBwtDOQTP68UR+24et4gS4T2BnwqWtRp0hi824e8I7GKWjjj6yzrNR4JIcXMClM
        UtpX6Op/E9m4UOorePJoVzKCZfgGAg+KAaiH0HHg29mm2b3ktMo9RNxdL3Q2dHeq/Ag4cg
        eGbItaU/Z2VZDgBLiEAc7lQMDm1LRoU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-299-yEsnVqOkN4i-qY-2bLIasw-1; Mon, 15 Jun 2020 08:10:21 -0400
X-MC-Unique: yEsnVqOkN4i-qY-2bLIasw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6AFF8107BF05
        for <kvm@vger.kernel.org>; Mon, 15 Jun 2020 12:09:52 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-3.gru2.redhat.com [10.97.112.3])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 2E9155D9DA;
        Mon, 15 Jun 2020 12:09:52 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 0A0E341807D1; Mon, 15 Jun 2020 08:59:53 -0300 (-03)
Date: Mon, 15 Jun 2020 08:59:53 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm-devel <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH] KVM: x86: allow TSC to differ by NTP correction bounds
 without TSC scaling
Message-ID: <20200615115952.GA224592@fuller.cnet>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Linux TSC calibration procedure is subject to small variations
(its common to see +-1 kHz difference between reboots on a given CPU, for example).

So migrating a guest between two hosts with identical processor can fail, in case
of a small variation in calibrated TSC between them.

Allow a conservative 250ppm error between host TSC and VM TSC frequencies,
rather than requiring an exact match. NTP daemon in the guest can
correct this difference.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

```
#### [PATCH v2 1/1] s390: virtio: let arch accept devices without IOMMU feature
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11604765
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6DA514E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:39:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B0D80206D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 12:39:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729898AbgFOMji (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 08:39:38 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:30254 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728326AbgFOMjf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Jun 2020 08:39:35 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05FBVRG0024033;
        Mon, 15 Jun 2020 08:39:32 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31mx4p2mr6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 08:39:32 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05FCCg4K177670;
        Mon, 15 Jun 2020 08:39:32 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0b-001b2d01.pphosted.com with ESMTP id 31mx4p2mqb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 08:39:31 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05FCLkmd000950;
        Mon, 15 Jun 2020 12:39:30 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma02fra.de.ibm.com with ESMTP id 31mpe89esy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 12:39:29 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05FCdRj463701102
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 15 Jun 2020 12:39:27 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 27CC3A405F;
        Mon, 15 Jun 2020 12:39:27 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 959D3A4054;
        Mon, 15 Jun 2020 12:39:26 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.1.141])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 15 Jun 2020 12:39:26 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v2 1/1] s390: virtio: let arch accept devices without IOMMU
 feature
Date: Mon, 15 Jun 2020 14:39:24 +0200
Message-Id: <1592224764-1258-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1592224764-1258-1-git-send-email-pmorel@linux.ibm.com>
References: <1592224764-1258-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-15_01:2020-06-15,2020-06-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 priorityscore=1501 mlxlogscore=906 suspectscore=1 impostorscore=0
 adultscore=0 lowpriorityscore=0 mlxscore=0 bulkscore=0
 cotscore=-2147483648 spamscore=0 phishscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2006150093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture protecting the guest memory against unauthorized host
access may want to enforce VIRTIO I/O device protection through the
use of VIRTIO_F_IOMMU_PLATFORM.

Let's give a chance to the architecture to accept or not devices
without VIRTIO_F_IOMMU_PLATFORM.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/mm/init.c     | 6 ++++++
 drivers/virtio/virtio.c | 9 +++++++++
 include/linux/virtio.h  | 2 ++
 3 files changed, 17 insertions(+)

```
#### [kvm-unit-tests PATCH v9 01/12] s390x: Use PSW bits definitions in cstart
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11604453
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 690CF618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 09:32:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 575CC206B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 09:32:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729402AbgFOJcU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 05:32:20 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:45266 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729352AbgFOJcS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Jun 2020 05:32:18 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 05F9BogK014198;
        Mon, 15 Jun 2020 05:32:17 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31p5eu9mn0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 05:32:14 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 05F8RA6l061226;
        Mon, 15 Jun 2020 05:32:12 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 31p5eu9mju-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 05:32:12 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 05F9Lae9012944;
        Mon, 15 Jun 2020 09:32:06 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 31mpe7u8w5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Jun 2020 09:32:05 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 05F9W3GT3211662
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 15 Jun 2020 09:32:03 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7B08152075;
        Mon, 15 Jun 2020 09:32:03 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.1.141])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 1FF3152073;
        Mon, 15 Jun 2020 09:32:03 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v9 01/12] s390x: Use PSW bits definitions in
 cstart
Date: Mon, 15 Jun 2020 11:31:50 +0200
Message-Id: <1592213521-19390-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1592213521-19390-1-git-send-email-pmorel@linux.ibm.com>
References: <1592213521-19390-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-06-15_01:2020-06-15,2020-06-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 cotscore=-2147483648
 adultscore=0 mlxlogscore=999 mlxscore=0 priorityscore=1501 phishscore=0
 lowpriorityscore=0 impostorscore=0 clxscore=1015 malwarescore=0
 suspectscore=1 bulkscore=0 spamscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2006150066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch defines the PSW bits EA/BA used to initialize the PSW masks
for exceptions.

Since some PSW mask definitions exist already in arch_def.h we add these
definitions there.
We move all PSW definitions together and protect assembler code against
C syntax.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/arch_def.h | 15 +++++++++++----
 s390x/cstart64.S         | 15 ++++++++-------
 2 files changed, 19 insertions(+), 11 deletions(-)

```
#### [PATCH v2] KVM: arm64: Allow in-atomic injection of SPIs
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11605707
Return-Path: <SRS0=Gi8X=74=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B1F8960D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 20:39:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 968DD207D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 15 Jun 2020 20:39:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1592253547;
	bh=G3kx7gmxUbYjMZujOdTgVsLt+bvnDQ4dZNfve9RFnlk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=La+NFH722vt/R46mfmhLVZkZJ3E8vdFKuDxLH10+kvKk6HuaTP7uXOYOSgc88VgUV
	 dycx+fQooKiMvo8m5xTAdUoYSV9/5Z9TDuG69LPSOsm9ncK13ohcxEn9IJ9esdP7ir
	 CvKuwyS7PwSWZau8D5k0fNX0F5HxE3eyOhFTSqXw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731581AbgFOUjG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 15 Jun 2020 16:39:06 -0400
Received: from mail.kernel.org ([198.145.29.99]:46196 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728346AbgFOUjF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Jun 2020 16:39:05 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8D9142078E;
        Mon, 15 Jun 2020 20:39:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1592253544;
        bh=G3kx7gmxUbYjMZujOdTgVsLt+bvnDQ4dZNfve9RFnlk=;
        h=From:To:Cc:Subject:Date:From;
        b=hbeSjzVU1xGOS4JUuRdRRivUGCZtnAK3/1Mi7AdM0dFxbIlDquwWgRGgJk9elc6RK
         ZAvejcacP6lB+rH/i8FHrct33CahwXAecKzBCB4b7SMS1FBFMmN+vfuOpJK5Dyp8qE
         2SGqkn4qmSXBvT1oNMcHN2XapvUrv3nj+nEk6TD4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=wait-a-minute.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jkvsl-003EcH-0j; Mon, 15 Jun 2020 21:39:03 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: yuzenghui@huawei.com, eric.auger@redhat.com,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v2] KVM: arm64: Allow in-atomic injection of SPIs
Date: Mon, 15 Jun 2020 21:38:44 +0100
Message-Id: <20200615203844.14793-1-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, yuzenghui@huawei.com, eric.auger@redhat.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a system that uses SPIs to implement MSIs (as it would be
the case on a GICv2 system exposing a GICv2m to its guests),
we deny the possibility of injecting SPIs on the in-atomic
fast-path.

This results in a very large amount of context-switches
(roughly equivalent to twice the interrupt rate) on the host,
and suboptimal performance for the guest (as measured with
a test workload involving a virtio interface backed by vhost-net).
Given that GICv2 systems are usually on the low-end of the spectrum
performance wise, they could do without the aggravation.

We solved this for GICv3+ITS by having a translation cache. But
SPIs do not need any extra infrastructure, and can be immediately
injected in the virtual distributor as the locking is already
heavy enough that we don't need to worry about anything.

This halves the number of context switches for the same workload.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
* From v1:
  - Drop confusing comment (Zenghui, Eric)
  - Now consistently return -EWOULDBLOCK when unable to inject (Eric)
  - Don't inject if the vgic isn't initialized yet (Eric)

 arch/arm64/kvm/vgic/vgic-irqfd.c | 24 +++++++++++++++++++-----
 arch/arm64/kvm/vgic/vgic-its.c   |  3 +--
 2 files changed, 20 insertions(+), 7 deletions(-)

```
