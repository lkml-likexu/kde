#### [PATCH v2 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11503767
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E7E2112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:58:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 78026217BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:58:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726454AbgDVM6W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 08:58:22 -0400
Received: from out30-45.freemail.mail.aliyun.com ([115.124.30.45]:50949 "EHLO
        out30-45.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725810AbgDVM6V (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Apr 2020 08:58:21 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R211e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01355;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0TwJzjgy_1587560292;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TwJzjgy_1587560292)
          by smtp.aliyun-inc.com(127.0.0.1);
          Wed, 22 Apr 2020 20:58:12 +0800
From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
To: pbonzini@redhat.com, tsbogend@alpha.franken.de, paulus@ozlabs.org,
        mpe@ellerman.id.au, benh@kernel.crashing.org,
        borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        hpa@zytor.com, maz@kernel.org, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v2 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
Date: Wed, 22 Apr 2020 20:58:04 +0800
Message-Id: <20200422125810.34847-2-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200422125810.34847-1-tianjia.zhang@linux.alibaba.com>
References: <20200422125810.34847-1-tianjia.zhang@linux.alibaba.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. Earlier than historical reasons, many kvm-related function
parameters retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time.
This patch does a unified cleanup of these remaining redundant parameters.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/s390/kvm/kvm-s390.c | 37 ++++++++++++++++++++++---------------
 1 file changed, 22 insertions(+), 15 deletions(-)

```
#### [PATCH 01/26] KVM: arm64: Check advertised Stage-2 page size capability
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11503591
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA52514B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:00:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90924208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:00:59 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587556859;
	bh=I732TSPQc9bSSFWvXROeC4qjohlGzkEaC6Z5VtQBTwo=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=hkkCoYQ69N49rU6o8HClWN/9bQ/7gJ3tYP46NU8YNUJ+TMo9Fg0jgSFA1F9Jru+Lx
	 bYNu5qiSsbEhwD/IdXqAyKIHF/XAj7XDTbNmsc0rqhPaxisdmJmUAGKI5o1IAACzST
	 4PgfblwLD61UfESCGYG3N1JP4pKri8Ev/ULWjZ/E=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728025AbgDVMA6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 08:00:58 -0400
Received: from mail.kernel.org ([198.145.29.99]:43792 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726477AbgDVMA6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 08:00:58 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 21EB520781;
        Wed, 22 Apr 2020 12:00:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587556857;
        bh=I732TSPQc9bSSFWvXROeC4qjohlGzkEaC6Z5VtQBTwo=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=BsU3EsqwyQFOrnctLzeLHMQxEkwKULRbhE6I1p008aroJY9Ynv1NQnl6yQ0pZ1JBV
         aHpbXsJkoyirFZd46RNf7IiPHH6Pywib299iMU6HmVbU3QwQSE1f8LXMKbGO6+S3Qx
         o3h/0dnp79hM8InLRUTyzmbCBHm9d3FmJCqOvJaw=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jRE3j-005UI7-FO; Wed, 22 Apr 2020 13:00:55 +0100
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
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 01/26] KVM: arm64: Check advertised Stage-2 page size
 capability
Date: Wed, 22 Apr 2020 13:00:25 +0100
Message-Id: <20200422120050.3693593-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
In-Reply-To: <20200422120050.3693593-1-maz@kernel.org>
References: <20200422120050.3693593-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, Dave.Martin@arm.com, jintack@cs.columbia.edu,
 alexandru.elisei@arm.com, gcherian@marvell.com, prime.zeng@hisilicon.com,
 will@kernel.org, catalin.marinas@arm.com, mark.rutland@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With ARMv8.5-GTG, the hardware (or more likely a hypervisor) can
advertise the supported Stage-2 page sizes.

Let's check this at boot time.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 arch/arm64/include/asm/kvm_host.h |  2 +-
 arch/arm64/include/asm/sysreg.h   |  3 +++
 arch/arm64/kernel/cpufeature.c    |  8 +++++++
 arch/arm64/kvm/reset.c            | 40 ++++++++++++++++++++++++++++---
 virt/kvm/arm/arm.c                |  4 +---
 5 files changed, 50 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/6] KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11504203
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9878F92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 16:19:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 811FA215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 16:19:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587572364;
	bh=5ARctdcnAgCfEyXFXi7xAyJcfvsKxIhqhVhZ9mavtZk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=pZiUVoczly0Oyi28Ol8szImvSU3HOSjgbxElnyT57XHFuUDdNHzxxE/wurVU1qmmz
	 Qk4U/sf41XM1tDJ5qdzMIR/ZrpAnRfa6L79sxo8fwy9MTiqBGCkf1ZYDpIBgoDEZKa
	 A4yhiAEm0HGqS/Ku8oifZlXIVsP9PxmPQhrM9aN0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726746AbgDVQTX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 12:19:23 -0400
Received: from mail.kernel.org ([198.145.29.99]:39254 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726466AbgDVQTW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 12:19:22 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2F1262082E;
        Wed, 22 Apr 2020 16:19:22 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587572362;
        bh=5ARctdcnAgCfEyXFXi7xAyJcfvsKxIhqhVhZ9mavtZk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=FYpiKsa5hAQ79WxRxdp0mSq6MxHafrj7k/7Ca/lH66jgxLbKjOzXshqHpmELn7XF/
         AywMuatkH4CdQLDHwUmyj3KG467EJBYNcTIz7eYe1R747Ba9uBvi5/wqCVdU4Rq5us
         6SKkV9a5AbvOY6JaG01Z5YTHUAwQE5kcVME8ediU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jRI5n-005Ynp-WB; Wed, 22 Apr 2020 17:19:20 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>, Eric Auger <eric.auger@redhat.com>,
 Andre Przywara <Andre.Przywara@arm.com>, Julien Grall <julien@xen.org>,
 James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, stable@vger.kernel.org,
	=?utf-8?q?Andr=C3=A9_Przywara?= <andre.przywara@arm.com>
Subject: [PATCH v3 1/6] KVM: arm: vgic: Fix limit condition when writing to
 GICD_I[CS]ACTIVER
Date: Wed, 22 Apr 2020 17:18:39 +0100
Message-Id: <20200422161844.3848063-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
In-Reply-To: <20200422161844.3848063-1-maz@kernel.org>
References: <20200422161844.3848063-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, yuzenghui@huawei.com,
 eric.auger@redhat.com, Andre.Przywara@arm.com, julien@xen.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 stable@vger.kernel.org, andre.przywara@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When deciding whether a guest has to be stopped we check whether this
is a private interrupt or not. Unfortunately, there's an off-by-one bug
here, and we fail to recognize a whole range of interrupts as being
global (GICv2 SPIs 32-63).

Fix the condition from > to be >=.

Cc: stable@vger.kernel.org
Fixes: abd7229626b93 ("KVM: arm/arm64: Simplify active_change_prepare and plug race")
Reported-by: André Przywara <andre.przywara@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/vgic/vgic-mmio.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm PATCH] KVM: nVMX - enable VMX preemption timer migrationFrom: Makarand Sonare <makarandsonare@google.com>
##### From: Makarand Sonare <makarandsonare@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11504559
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 411A51392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 20:50:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 24B812077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 20:50:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="UeMGIsT+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726497AbgDVUuz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 16:50:55 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48556 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725779AbgDVUuy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 16:50:54 -0400
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 38C10C03C1A9
        for <kvm@vger.kernel.org>; Wed, 22 Apr 2020 13:50:54 -0700 (PDT)
Received: by mail-pg1-x549.google.com with SMTP id f14so2770598pgj.15
        for <kvm@vger.kernel.org>; Wed, 22 Apr 2020 13:50:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=TPQ3bGO0IKyRspfv7+Z/kyY0wNMGCEFRQ6Ok4itlGas=;
        b=UeMGIsT++8OS4w14ROF5YDxsUmm5vBNeWxnx4DzFYW9BgMmsnxdnnbJ1quT0ocimiN
         8O5in2WEj+NofusKhsQMiRqHscqkq9+aJ+9iVscGW0uKLhobmiB8Ph5828qsXtwZSqZZ
         H7Y2NUF+Xc6qeRPm8wav58TcrIKjRO8yFvUtMm+GJJREmeVTzhGb9VsTGgS7tv3Aj956
         3BrfDkB4KA0Pv0ycwxJWeUOKGymV3qrgaWzC9DHRLvykXg6JylXdOBeVYs2rlwws40kD
         g2iQ6J814yn8cUpmoQ1PIkHU2OtGXCvYlChVywAj3PdvDGHsDLOAav/uAG1JTlFSS7d6
         pngQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=TPQ3bGO0IKyRspfv7+Z/kyY0wNMGCEFRQ6Ok4itlGas=;
        b=OEEBedUeF6cG54YkMc/coJAQYk1/5Lc6vonu3Wtm+O/ZsOKLr4NxIeNY3drJ0lVj4H
         lLtQwMdB64lH2s6QRfDhR6MV7cYhfvCtBwT8FtBsvN5ScdysMXJIavobOtk5oZIRzLor
         MBPJLDyO+GjT4BrZUF1HnnaGHYAZ+vCMHjZvB/+J++EaF50glzfCdC1Yn/JPng7gYbcM
         uC/vfK61kYJ4VcQ9P6Shk2ekI/pBguUmhAjQ3KFNaTSUebYaTe1ZMbgIX9l1RL6IOtJJ
         XZGML9LsDBJGll9MVJfp+NG8pD8UkiyGTFEbMNAoOWDk8eEGSWdC5lo6gEr5aCPsu/to
         fBJQ==
X-Gm-Message-State: AGi0PubKRm0R+N0L493nS6ChhDxOYRY1dIL6lzOXDk4vyW4GpV+irMn5
        9wmYR/X2IJnI9Mg8WdMTwlboLbPCD9BjEw5IqxbhVui/u5lpIPeng0cLDk96sKvZfHLrOOI+p+m
        282a5dqtjdlL1nhofalOn/zvp9991p6QGX8DjK8bM3UhuvixvFHq1mL3fAiFkbLe4erhrcNoXgW
        MQ0/I=
X-Google-Smtp-Source: 
 APiQypLxWH8tPRdRSUl/rZzwUdgfes/10kuYXjXnH3Y6a5ETSmvtlk64R5XVpMZ0mox6uiWLlukXYKTcdhK03gPM+hPRTw==
X-Received: by 2002:a17:90a:9e9:: with SMTP id 96mr628768pjo.41.1587588653517;
 Wed, 22 Apr 2020 13:50:53 -0700 (PDT)
Date: Wed, 22 Apr 2020 13:50:30 -0700
Message-Id: <20200422205030.84476-1-makarandsonare@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [kvm PATCH] KVM: nVMX - enable VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Add new field to hold preemption timer remaining until expiration
appended to struct kvm_vmx_nested_state_data. This is to prevent
the second (and later) VM-Enter after migration from restarting the timer
with wrong value. KVM_SET_NESTED_STATE restarts timer using migrated
state regardless of whether L1 sets VM_EXIT_SAVE_VMX_PREEMPTION_TIMER.

Fixes: cf8b84f48a593 ("kvm: nVMX: Prepare for checkpointing L2 state")

Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Makarand Sonare <makarandsonare@google.com>
Change-Id: I6446aba5a547afa667f0ef4620b1b76115bf3753
---
 Documentation/virt/kvm/api.rst        |  4 ++
 arch/x86/include/uapi/asm/kvm.h       |  2 +
 arch/x86/kvm/vmx/nested.c             | 59 +++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h                |  1 +
 arch/x86/kvm/x86.c                    |  1 +
 include/uapi/linux/kvm.h              |  1 +
 tools/arch/x86/include/uapi/asm/kvm.h |  2 +
 7 files changed, 63 insertions(+), 7 deletions(-)

```
#### [PATCH 1/5] rcuwait: Fix stale wake call name in comment
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Davidlohr Bueso <dave@stgolabs.net>
X-Patchwork-Id: 11502821
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 28366913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 04:11:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C1542075E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 04:11:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726442AbgDVELr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 00:11:47 -0400
Received: from mx2.suse.de ([195.135.220.15]:60012 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725808AbgDVELr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 00:11:47 -0400
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id 5F1ABAD5E;
        Wed, 22 Apr 2020 04:11:44 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: bigeasy@linutronix.de, peterz@infradead.org, rostedt@goodmis.org,
        torvalds@linux-foundation.org, will@kernel.org,
        joel@joelfernandes.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, dave@stgolabs.net,
        Davidlohr Bueso <dbueso@suse.de>
Subject: [PATCH 1/5] rcuwait: Fix stale wake call name in comment
Date: Tue, 21 Apr 2020 21:07:35 -0700
Message-Id: <20200422040739.18601-2-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
In-Reply-To: <20200422040739.18601-1-dave@stgolabs.net>
References: <20200422040739.18601-1-dave@stgolabs.net>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'trywake' name was renamed to simply 'wake', update the comment.

Signed-off-by: Davidlohr Bueso <dbueso@suse.de>
---
 kernel/exit.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### linux-next: manual merge of the kvm tree with the rcu tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11502797
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 095871392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 03:52:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D730F206EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 03:52:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="hjOwoZL8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726403AbgDVDwS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Apr 2020 23:52:18 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:45171 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726228AbgDVDwR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Apr 2020 23:52:17 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 496RMf0jKKz9sSg;
        Wed, 22 Apr 2020 13:52:14 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1587527535;
        bh=Ht2B9g7UeZlkPJ4YAiu9xxmmZjmqQOON7qrTD5NTcWU=;
        h=Date:From:To:Cc:Subject:From;
        b=hjOwoZL8NY5GqqQy3WlTAEVSC6Wg14/fHs9eTRiMvv/1VK+5tc6+n2MtPYDrOTElp
         CrAPYW15l3geQ8bIUqD/vs6PikvYN7C6TgQTKMgivh8VCyubg+hBHqO8MC8bL+KHbl
         dM8L/HOpBofi9+GBvhm2xPpLNuxOOPNNrJf+8Z6fywTu8RoQrj0rWeoHPceqwkjfr5
         qdp310u2SiyKsTrVGOrFv8ORtLZHIGRl40PkdiTDLtZ9xYnpN4qcvMb5QVQuxSC1GN
         jen18EHpr84ZR0oNljWw/msC6clRakkhff6O2EP9ImF6Ce7ps4GfmSBAUdBrtXjTdA
         nyB/GwC4ee7ZA==
Date: Wed, 22 Apr 2020 13:52:12 +1000
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paolo Bonzini <pbonzini@redhat.com>, KVM <kvm@vger.kernel.org>,
        "Paul E. McKenney" <paulmck@kernel.org>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
        Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
        Qian Cai <cai@lca.pw>, Wanpeng Li <wanpengli@tencent.com>
Subject: linux-next: manual merge of the kvm tree with the rcu tree
Message-ID: <20200422135212.74d72690@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kvm/svm/svm.c

between commit:

  c60e60a23f24 ("kvm/svm: Disable KCSAN for svm_vcpu_run()")

from the rcu tree and commit:

  a9ab13ff6e84 ("KVM: X86: Improve latency for single target IPI fastpath")

from the kvm tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [PATCH v2 1/4] KVM: x86: hyperv: Remove duplicate definitions of Reference TSC Page
##### From: Michael Kelley <mikelley@microsoft.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Kelley <mikelley@microsoft.com>
X-Patchwork-Id: 11504451
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 311111667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 19:58:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1480D215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 19:58:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=microsoft.com header.i=@microsoft.com
 header.b="V/MEbOp3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726380AbgDVT6n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 15:58:43 -0400
Received: from mail-dm6nam11on2109.outbound.protection.outlook.com
 ([40.107.223.109]:6625
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726158AbgDVT6k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 15:58:40 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=bBJ5CZQylruQAwGp8NGTYYw+gZxG72j2Mzstn7f30fO5wIFTaxxbHl6iFmHItSI6X60UYUKzuJpTer5eLmEoQYisbIZ4sZELMjgh48EhtqEEq8v1EalvK77xoUuK6BHqAVFqJQGKZ7fOLqdYI+X3bEzHkDdxJ52zfg6FFS09WQtWr/k2imV75QlnyVeikYfzqAXFtAZEIl82KazBn5BWY1IjKTs6uWT7uAKHK5pS3x1eUBa6Rv0qF6kGmY1hPXsn5uKXCROYrGEar+M1Zrs9UwyTlx80oeQtgyZ2fvdrUgCAp0xG0AICNynYItyA7aq6Q9kTG8tDK4SncCtF7q80vQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kZCGC1hl4qYHX9P4nKjkybcUPVyLM/057OCoaFiqEFM=;
 b=LrtjQhdKL74FlxtViBs5G9gZ3E6FdYe7sVRL2VDtL0CjDDOE+VFO/Mbw2/ha4z4V6MRImlb0Hbnaccy5JEAZFV0Lzqh0g+/+QaetRPYeZxtlW7GjVHagL8KKAbyNvrzTVCGgLmlfMi61r0x9oYb+aV+vegXuoRG6sokYnM6CrvSQ5Qm38e7iEn1GG3XonaeIneB7rPNs3waDT7SOuziWHGYOVV18AzBIiiuuTgagBt3BDBS6jcCO54j+N8bJkub7KWCyzsAi1Zd/j76aWTRS27icHDt72aDjIl7ULDrBqdzACjhzEiLyNWa01HFpV+vsOO82Git7wiiJMFI5sjy6jA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=microsoft.com; dmarc=pass action=none
 header.from=microsoft.com; dkim=pass header.d=microsoft.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=kZCGC1hl4qYHX9P4nKjkybcUPVyLM/057OCoaFiqEFM=;
 b=V/MEbOp35JygXGtbq6RQR2e7vd8mRQHOYMLEhp5CUtZkYBChsvFJsWMGJ9HlsjIycuHfXqxmr4nW6B8m/40LCBD5p2u9ptGgCz2j74vafp2sJKSs/1iooMerJ6LE1gdkliniMh55XhzK1QpYaWXp8mopIlkAi2qC3MgWVMoh1b4=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=mikelley@microsoft.com;
Received: from BN6PR21MB0178.namprd21.prod.outlook.com (2603:10b6:404:94::12)
 by BN6PR21MB0148.namprd21.prod.outlook.com (2603:10b6:404:93::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.2; Wed, 22 Apr
 2020 19:58:37 +0000
Received: from BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec]) by BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec%11]) with mapi id 15.20.2958.001; Wed, 22 Apr
 2020 19:58:37 +0000
From: Michael Kelley <mikelley@microsoft.com>
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        wei.liu@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Cc: mikelley@microsoft.com
Subject: [PATCH v2 1/4] KVM: x86: hyperv: Remove duplicate definitions of
 Reference TSC Page
Date: Wed, 22 Apr 2020 12:57:34 -0700
Message-Id: <20200422195737.10223-2-mikelley@microsoft.com>
X-Mailer: git-send-email 2.18.2
In-Reply-To: <20200422195737.10223-1-mikelley@microsoft.com>
References: <20200422195737.10223-1-mikelley@microsoft.com>
X-ClientProxiedBy: MWHPR19CA0078.namprd19.prod.outlook.com
 (2603:10b6:320:1f::16) To BN6PR21MB0178.namprd21.prod.outlook.com
 (2603:10b6:404:94::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from MHKdev.corp.microsoft.com (167.220.2.108) by
 MWHPR19CA0078.namprd19.prod.outlook.com (2603:10b6:320:1f::16) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.13 via Frontend
 Transport; Wed, 22 Apr 2020 19:58:35 +0000
X-Mailer: git-send-email 2.18.2
X-Originating-IP: [167.220.2.108]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 218d2491-aac4-47da-3a51-08d7e6f78b83
X-MS-TrafficTypeDiagnostic: BN6PR21MB0148:|BN6PR21MB0148:|BN6PR21MB0148:
X-MS-Exchange-Transport-Forked: True
X-LD-Processed: 72f988bf-86f1-41af-91ab-2d7cd011db47,ExtAddr
X-Microsoft-Antispam-PRVS: 
 <BN6PR21MB0148D628A502B54A68B622F7D7D20@BN6PR21MB0148.namprd21.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7219;
X-Forefront-PRVS: 03818C953D
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BN6PR21MB0178.namprd21.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(346002)(136003)(396003)(366004)(376002)(39860400002)(81156014)(82960400001)(8936002)(10290500003)(4326008)(26005)(82950400001)(5660300002)(107886003)(956004)(2616005)(478600001)(66556008)(66946007)(66476007)(6486002)(1076003)(86362001)(316002)(8676002)(2906002)(16526019)(186003)(36756003)(52116002)(7696005)(7416002)(921003);DIR:OUT;SFP:1102;
Received-SPF: None (protection.outlook.com: microsoft.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 1752yKqdsvkH1CkUQFwigt3CYVjSx8FN00WL1VNxyLtGhAsJg5+Dqs5zvPd+SDFY/B3DNv1tqXb9PDkRIEhliseTqqBwCM42yrfrw02F7WNc6/gZh1Cp8oVVOcLU+BU+qloYDYGBA7xFAxNGIRjGNI1o/CYY1wKxTI3dANSNuzqULsdhCv0uTFTSo9h2ENqzFBUVF/xv1XIFzqHR9zZHpCfQPKCB6A6JomHYPHDO4GUuzK/eNJ6jph9eQxbRAdEiIvLD/R7DOWN1Z/G0amLWcgaL6mBcH7cIn0C9Hrh0g57LDvdnGVnV7D6apD8V+9ixEAhYpGkVO23kroHFX/F3xskEA8SsRBMezg2N7+LrwIjPO0lXtqMaRdFi4AQsHReZb/4281+sGGEHVKk08mSzi2lTsEI7ypQVMiPsitZ//wkupOwxbgdgg+HjXItBk2qX7zNo3Wdx8Qet/ntjU0AhDpPn8trJM63RrB7PD8LLrL4=
X-MS-Exchange-AntiSpam-MessageData: 
 bz3U0syiuvEFTKQRnFLQwCoWB17AXxgkGadfo/mOKaox2WFIdMGRQtJZxe8kn+QvNQU/YkoTMLadt27wPRBbfZwintCC8h1/qToN32IInDqqZPJ59S9DcHAhyPKcfCdRWlnPDbSwrEiSdddTq2nFfRUNFvmfcShCai0/jW+lDDjkDHAAvZNupCpAOCom/iKjJpSVDhhCsHR/ZtKdaKdKara1rhzeEqpsPMAQpMOF9+rQGS1kUs/JEHmtMDu3aO71I+0XVoxXV4r7BEPjBCxZBDUFL6MCB75BgiQLsdd+4BQyoKHmjN/snddVZ01BzQsxqs5aKr9IFgo/ZrTgODaFdB2cHSX8N2cboeHBXwVDg4AU8ERBb8Di3LclyhyNzeIyGITc1RWH8N0Fqr/0yrjgVWS+AHVNbEGWbLyOk/NDc2liijgynI1Ey0c2vYOO88cjgSf+h9dQdLQp2vdSRA8dVx3mxRdfmJTVaiZcSMyqpNJ7PHgklZ8gCMBKeIAueei3rWUi5SXc0L9gSBZHlJspvnv1BO2jY0Qas8Y+BEDXlq+qSCkVQ+4v8Ff1AddzGFyizShuM1euO6gOMJZkPiD/Uf3m6c9/V/vjza47FEL3YpjnOsxwZvNTOjgdotr5XS7TcOYoHwMpG9hrylSF0YLzL2Gk2KicLZalNcp4HpyibK5FanCrqlzGW57ACem1V8vDLczdE+eKndaEnMd5w/YFd3OLyBYnQA2uR3nUge8aZLoF9t+nABym9uu4EdYLZK7XdDPL0vxZMaLvuJigSgI/9PfXz+HseNzA8+HftfMSBR0=
X-OriginatorOrg: microsoft.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 218d2491-aac4-47da-3a51-08d7e6f78b83
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2020 19:58:36.9637
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 72f988bf-86f1-41af-91ab-2d7cd011db47
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 EN0LugPXZvgmDhV1VLl6zf4D4qpOxn5F9PD/jOU3dR5nyBdBWbW62pO5ONTW+HeWZE3yVp8BGxoZu0LyYfQyzg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BN6PR21MB0148
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Hyper-V Reference TSC Page structure is defined twice. struct
ms_hyperv_tsc_page has padding out to a full 4 Kbyte page size. But
the padding is not needed because the declaration includes a union
with HV_HYP_PAGE_SIZE.  KVM uses the second definition, which is
struct _HV_REFERENCE_TSC_PAGE, because it does not have the padding.

Fix the duplication by removing the padding from ms_hyperv_tsc_page.
Fix up the KVM code to use it. Remove the no longer used struct
_HV_REFERENCE_TSC_PAGE.

There is no functional change.

Signed-off-by: Michael Kelley <mikelley@microsoft.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 8 --------
 arch/x86/include/asm/kvm_host.h    | 2 +-
 arch/x86/kvm/hyperv.c              | 4 ++--
 3 files changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH v4] virtio: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11504065
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65B0014B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 14:59:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 443D42098B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 14:59:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CpHvqBED"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727089AbgDVO7E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 10:59:04 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:43472 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726018AbgDVO7D (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Apr 2020 10:59:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587567541;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=FBH552ipbDuDcBz+NzQuT3xldOG131csNhHDA4JojNg=;
        b=CpHvqBEDEbV9b6Sc4JYBmNLwOMysUDe/BKJKTN1c5Mk3pa2x2pxbkpATaEkK/rFsZaY1fH
        5SIQ47pV6PASqu9vhFEo+uKUPwYDv/UtWPVJiPYeG21yLrsxhva7pGxZbL+5pIoTGNfGt8
        2M7+tTF2MwmfcXlGg2MnY06JBB1JcE0=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-364-sd_bU_JdPkqeHIfyGz9SIg-1; Wed, 22 Apr 2020 10:58:57 -0400
X-MC-Unique: sd_bU_JdPkqeHIfyGz9SIg-1
Received: by mail-wm1-f71.google.com with SMTP id q5so915843wmc.9
        for <kvm@vger.kernel.org>; Wed, 22 Apr 2020 07:58:57 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=FBH552ipbDuDcBz+NzQuT3xldOG131csNhHDA4JojNg=;
        b=ddYsLvfqBMhlKOKTqCtXR6oSPP3/bu/NbzbUUf+JLdY9m/oLaXfoF20ZVKvZlKB6po
         Tyy3IfxhyYSnhyRv5OIj6p+J0Y7/cBy1Whl/t0eKuB8bXJuXCySgc5O+va15G0MUGYWx
         82SpYyJkO8sUsrVR2/IRbwvg+ixaPcB4Lj0XQ8vOETOE0ojexxAx69dPM16SYLtrbJU6
         uF3PHWMyj4yH5574kHFuxSX9vza8MHtAh7zoBLK8FrnEv2eEIg8qNDR38oGnZE8cW2Cn
         N9VfAlcIdXrCAy0htxSaaMcFhgaYhyGzGcA+5b2nAZl2fYdWwxLQPhdgFdUuTLjCWjpn
         LksQ==
X-Gm-Message-State: AGi0PuYKpgK9m/0qorePT8CsCCVvVi7Fuxhy45WfwDVRmAe2PAMZFkzP
        7cPA7eeBVa3M4qM2gLAGqWbeMpYf5bB3ukitjz5/6H9HWBFXjGx+CYs9f972lB405sNFolV/IKG
        KLCbJwyFfL1jS
X-Received: by 2002:a7b:c759:: with SMTP id w25mr12028203wmk.68.1587567536052;
        Wed, 22 Apr 2020 07:58:56 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypLEDPGbJlcp27JEzrmkhkGVGhmFCX09zIMAUDQzDbGsjJetkC8OmekGJ4WtGHKHUc8vRzjP6w==
X-Received: by 2002:a7b:c759:: with SMTP id w25mr12028178wmk.68.1587567535740;
        Wed, 22 Apr 2020 07:58:55 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 h1sm8504291wme.42.2020.04.22.07.58.54
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 22 Apr 2020 07:58:55 -0700 (PDT)
Date: Wed, 22 Apr 2020 10:58:53 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v4] virtio: force spec specified alignment on types
Message-ID: <20200422145510.442277-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ring element addresses are passed between components with different
alignments assumptions. Thus, if guest/userspace selects a pointer and
host then gets and dereferences it, we might need to decrease the
compiler-selected alignment to prevent compiler on the host from
assuming pointer is aligned.

This actually triggers on ARM with -mabi=apcs-gnu - which is a
deprecated configuration, but it seems safer to handle this
generally.

Note that userspace that allocates the memory is actually OK and does
not need to be fixed, but userspace that gets it from guest or another
process does need to be fixed. The later doesn't generally talk to the
kernel so while it might be buggy it's not talking to the kernel in the
buggy way - it's just using the header in the buggy way - so fixing
header and asking userspace to recompile is the best we can do.

I verified that the produced kernel binary on x86 is exactly identical
before and after the change.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---

changes since v3:
	use __attribute__((aligned(X))) instead of __aligned,
	to avoid dependency on that macro

 drivers/vhost/vhost.c            |  8 +++---
 drivers/vhost/vhost.h            |  6 ++---
 drivers/vhost/vringh.c           |  6 ++---
 include/linux/vringh.h           |  6 ++---
 include/uapi/linux/virtio_ring.h | 46 ++++++++++++++++++++++++--------
 5 files changed, 48 insertions(+), 24 deletions(-)

```
