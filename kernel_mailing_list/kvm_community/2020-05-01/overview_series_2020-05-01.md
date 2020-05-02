#### [PATCH 1/4] KVM: arm64: Delete duplicated label in invalid_vector
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11522373
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1227913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 10:12:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A79AF21973
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 10:12:16 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588327936;
	bh=QYiBh6HpiYyWl4I9Yb5aCaWR/B9ybjQ0TBfRZS8/OFk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=N6GIDLO/nEX8/ylCzSiC3EPVcCvOjsg31wQVkxjRDJGqdNiMwD4MimG70UqpiHHuv
	 ss8/b0KeQh7JfuLVZx0zH/Oh/ocEbPCz+vX0cYD+5z/zMKUWZ1DmwzdBGA8JTRqcZR
	 egFplHLXytcpDCfBJcHc124sj+3SlzR0wV1EX32s=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728497AbgEAKMP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 06:12:15 -0400
Received: from mail.kernel.org ([198.145.29.99]:37008 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728430AbgEAKMO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 06:12:14 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 918732173E;
        Fri,  1 May 2020 10:12:13 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588327933;
        bh=QYiBh6HpiYyWl4I9Yb5aCaWR/B9ybjQ0TBfRZS8/OFk=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=GRtKiHgJRORNUzXs6UmL3jB54JteyePLhF5dICggsTIuK7n9dUd+W5Xqs29iostQ6
         F41yOulUTKi+BGcm8l1LC7KR1pV/AT+KwMQuJhQtkLE+wVstilHZ/R5RHhF3DC17Pf
         YtfysgP4nkrZduRC9W6G9k9fwhtTL44elao8u4q8=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jUSeR-008J3K-UM; Fri, 01 May 2020 11:12:12 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>,
        Fangrui Song <maskray@google.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 1/4] KVM: arm64: Delete duplicated label in invalid_vector
Date: Fri,  1 May 2020 11:12:01 +0100
Message-Id: <20200501101204.364798-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200501101204.364798-1-maz@kernel.org>
References: <20200501101204.364798-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 maskray@google.com, mark.rutland@arm.com, ndesaulniers@google.com,
 will@kernel.org, yuzenghui@huawei.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Fangrui Song <maskray@google.com>

SYM_CODE_START defines \label , so it is redundant to define \label again.
A redefinition at the same place is accepted by GNU as
(https://sourceware.org/git/?p=binutils-gdb.git;a=commit;h=159fbb6088f17a341bcaaac960623cab881b4981)
but rejected by the clang integrated assembler.

Fixes: 617a2f392c92 ("arm64: kvm: Annotate assembly using modern annoations")
Signed-off-by: Fangrui Song <maskray@google.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Tested-by: Nick Desaulniers <ndesaulniers@google.com>
Reviewed-by: Nick Desaulniers <ndesaulniers@google.com>
Link: https://github.com/ClangBuiltLinux/linux/issues/988
Link: https://lore.kernel.org/r/20200413231016.250737-1-maskray@google.com
---
 arch/arm64/kvm/hyp/hyp-entry.S | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] docs: kvm: Fix KVM_KVMCLOCK_CTRL API doc
##### From: Joshua Abraham <j.abraham1776@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joshua Abraham <j.abraham1776@gmail.com>
X-Patchwork-Id: 11523193
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 64643912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 19:34:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B112218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 19:34:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="l+M6ffx8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727025AbgEATeL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 15:34:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51644 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726475AbgEATeK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 1 May 2020 15:34:10 -0400
Received: from mail-qk1-x743.google.com (mail-qk1-x743.google.com
 [IPv6:2607:f8b0:4864:20::743])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id BC8A4C061A0C;
        Fri,  1 May 2020 12:34:10 -0700 (PDT)
Received: by mail-qk1-x743.google.com with SMTP id i7so1916422qkl.12;
        Fri, 01 May 2020 12:34:10 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:date:to:cc:subject:message-id:mime-version:content-disposition
         :user-agent;
        bh=kfVrPN6y9lsLFf6FqSXZapvj2RnD4kAcpEoqz9NVXVA=;
        b=l+M6ffx8Kub9ieJ5klTStggW2FMVS0kYfyOWyBXasFLngqRD92GB65VNCbXOh9HInw
         N55Re0WbtaIF7p2xBP/aunGnncfJ5xuyVUnDSuA0BKbZZk1FFgjLLeDiwUU/iRvSKrML
         EVVPH1W/I7tFsiclreaRCVEz+6rsvPjLKIarZ/HiGcXv6ilvX9bz3tZW7glktxoNU49g
         xA6U+500y+XE8Q1NEpvWOFA0tIRepTIgbMVezuv+ncVPzOJlI+43OdbHKkM8VM7mEtQD
         1EmQQ+e+rfj398T+qSu4Vyh3pco/q/GOn47Pc1Fa1SGKcutwsrVXAxmjTcY60eZEPfi7
         6PPw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:date:to:cc:subject:message-id:mime-version
         :content-disposition:user-agent;
        bh=kfVrPN6y9lsLFf6FqSXZapvj2RnD4kAcpEoqz9NVXVA=;
        b=RiR9Bd/sY271g5N3kEvSWp6fHh5+Wc5l/uL9mdsHB25sT6kgIDoBH9p+wL79DN5r+v
         acRlkEMkdgm6ESs9Ptkyy/g3rsO57uRxTDSlWNfksLvWkVt4Do+9omrTS6Msqp3F7Sa7
         JtU9Xjw96sLhym3Ymv6ez/4Cfu9p7L9AdYY/j2JovFcWdQINLVZgw1DmjPjW2REOO8v6
         NbiWx8Wv97bj2v6cUrzShmtEpgeACQLTJRBbp+9sc3poNA8+YF8YpOHW6qBkrWNqV2z3
         KhZqMwrGztY38SPLJxz1o8/AFnC1oxMGnPpx3hbvggIRnqUbNHuKMTEKa64QAJmaq1Ec
         zcCQ==
X-Gm-Message-State: AGi0PuZ8zMmRuow+chfy/I/DbOIOQD1k5IV5pTLQSumxNJRUdANCy5M+
        AGVtD43pWxLujsTDtKBnoovH1Vc5/Gtczw==
X-Google-Smtp-Source: 
 APiQypJZPCbu5MQXz1ynhnhYrfqdUD4mueLaxvwiSauDlRPwu+3OvCoXPzjHW1cMBypPaUjLvyck1w==
X-Received: by 2002:a05:620a:2199:: with SMTP id
 g25mr648855qka.147.1588361649910;
        Fri, 01 May 2020 12:34:09 -0700 (PDT)
Received: from josh-ZenBook ([70.32.0.110])
        by smtp.gmail.com with ESMTPSA id u7sm3334136qkc.1.2020.05.01.12.34.08
        (version=TLS1_2 cipher=ECDHE-ECDSA-CHACHA20-POLY1305 bits=256/256);
        Fri, 01 May 2020 12:34:09 -0700 (PDT)
From: Joshua Abraham <j.abraham1776@gmail.com>
X-Google-Original-From: Joshua Abraham <sinisterpatrician@gmail.com>
Date: Fri, 1 May 2020 15:34:06 -0400
To: pbonzini@redhat.com
Cc: corbet@lwn.net, kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, j.abraham1776@gmail.com
Subject: [PATCH] docs: kvm: Fix KVM_KVMCLOCK_CTRL API doc
Message-ID: <20200501193404.GA19745@josh-ZenBook>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM_KVMCLOCK_CTRL ioctl signals to supported KVM guests
that the hypervisor has paused it. This updates the documentation 
to reflect that the guest, not the host is notified by this API.

Signed-off-by: Joshua Abraham <j.abraham1776@gmail.com>
---
 Documentation/virt/kvm/api.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm fixes for 5.7, take #2
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11522381
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4827B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 10:12:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3145E2192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 10:12:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588327940;
	bh=MklRYqz2k5cgg9fDxl/d5X5Bx725+ZQ/Ik6viwGxla4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=nk8+xhJmIfHmHMDFazI+AjfXYg25Exduq+7mTLDp6JeRaceuk6vecuXiMXo8/nd6z
	 t7KpevJN3Uh/qRfFJbmXvyGy3J8CKLdfJjw5cyPtcaswGwkEgbwFNqPnnO4NWvOveh
	 Dq9PfDFTcM8qAGpPW+UW91Rl0XiOSjj7xjOlCBtE=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728480AbgEAKMO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 06:12:14 -0400
Received: from mail.kernel.org ([198.145.29.99]:36968 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728268AbgEAKMN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 06:12:13 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id CC8272071C;
        Fri,  1 May 2020 10:12:12 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588327932;
        bh=MklRYqz2k5cgg9fDxl/d5X5Bx725+ZQ/Ik6viwGxla4=;
        h=From:To:Cc:Subject:Date:From;
        b=X1YhUQCCR6e8QRgIEHrOJrY2OLaP82i20DIb+Jk+ZKCeEwwvw3Zpb0ro3VcUTEhw4
         gaaZNfih7lrLfPOWi2d/T3xjcde6aAizPmXuK+c1j7yME1SY2dNkQt0+ZatzQuPJ+W
         LFZ0qpF5NDxuEBSFW5mNfRKLlY02LLeFJT5i58ac=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jUSeR-008J3K-7D; Fri, 01 May 2020 11:12:11 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>,
        Fangrui Song <maskray@google.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Nick Desaulniers <ndesaulniers@google.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm fixes for 5.7, take #2
Date: Fri,  1 May 2020 11:12:00 +0100
Message-Id: <20200501101204.364798-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, drjones@redhat.com,
 maskray@google.com, mark.rutland@arm.com, ndesaulniers@google.com,
 will@kernel.org, yuzenghui@huawei.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

This is the second batch of KVM/arm fixes for 5.7. A compilation fix,
a GICv4.1 fix, plus a couple of sanity checks (SP_EL0 save/restore,
and the sanitising of AArch32 registers).

Note that the pull request I sent a week ago[1] is still valid, and
that this new series is built on top of the previous one.

Please pull,

	M.

[1] https://lore.kernel.org/kvm/20200423154009.4113562-1-maz@kernel.org/

The following changes since commit 446c0768f5509793a0e527a439d4866b24707b0e:

  Merge branch 'kvm-arm64/vgic-fixes-5.7' into kvmarm-master/master (2020-04-23 16:27:33 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.7-2

for you to fetch changes up to 0225fd5e0a6a32af7af0aefac45c8ebf19dc5183:

  KVM: arm64: Fix 32bit PC wrap-around (2020-05-01 09:51:08 +0100)

----------------------------------------------------------------
KVM/arm fixes for Linux 5.7, take #2

- Fix compilation with Clang
- Correctly initialize GICv4.1 in the absence of a virtual ITS
- Move SP_EL0 save/restore to the guest entry/exit code
- Handle PC wrap around on 32bit guests, and narrow all 32bit
  registers on userspace access

----------------------------------------------------------------
Fangrui Song (1):
      KVM: arm64: Delete duplicated label in invalid_vector

Marc Zyngier (3):
      KVM: arm64: Save/restore sp_el0 as part of __guest_enter
      KVM: arm64: vgic-v4: Initialize GICv4.1 even in the absence of a virtual ITS
      KVM: arm64: Fix 32bit PC wrap-around

 arch/arm64/kvm/guest.c           |  7 +++++++
 arch/arm64/kvm/hyp/entry.S       | 23 +++++++++++++++++++++++
 arch/arm64/kvm/hyp/hyp-entry.S   |  1 -
 arch/arm64/kvm/hyp/sysreg-sr.c   | 17 +++--------------
 virt/kvm/arm/hyp/aarch32.c       |  8 ++++++--
 virt/kvm/arm/vgic/vgic-init.c    |  9 ++++++++-
 virt/kvm/arm/vgic/vgic-mmio-v3.c |  3 ++-
 7 files changed, 49 insertions(+), 19 deletions(-)
```
#### [GIT PULL] VFIO fixes for v5.7-rc4
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11523341
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 027EC913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:51:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DEA5021775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:51:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="WEugK8bG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726692AbgEAVvA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 17:51:00 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:41702 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726045AbgEAVvA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 1 May 2020 17:51:00 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588369859;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=6K9N0GoO7o+fp5KFhAqVxNdfg4MrM4tfiBE4omn4UAM=;
        b=WEugK8bGX6RwId9hKqADQejNspjNYwftyfJd+19DP86hi347iCxxppLFioHuWmvP5IAWt5
        /RV9uVMCzWsbnpSEnszbDVTgXPUkMOkGslRhEOotMCSsq57okj9QG7FgmkVI/QHZxxYjye
        B9Xadf0fXyJNjgFbYPyugT4vkn15MVI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-259-sMW5MDQdPf2jRstx2gYxqQ-1; Fri, 01 May 2020 17:50:56 -0400
X-MC-Unique: sMW5MDQdPf2jRstx2gYxqQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B1EF845F;
        Fri,  1 May 2020 21:50:55 +0000 (UTC)
Received: from x1.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 74DF210016EB;
        Fri,  1 May 2020 21:50:55 +0000 (UTC)
Date: Fri, 1 May 2020 15:50:54 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [GIT PULL] VFIO fixes for v5.7-rc4
Message-ID: <20200501155054.39bdad7e@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit ae83d0b416db002fe95601e7f97f64b59514d936:

  Linux 5.7-rc2 (2020-04-19 14:35:30 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.7-rc4

for you to fetch changes up to 5cbf3264bc715e9eb384e2b68601f8c02bb9a61d:

  vfio/type1: Fix VA->PA translation for PFNMAP VMAs in vaddr_get_pfn() (2020-04-23 12:10:01 -0600)

----------------------------------------------------------------
VFIO fixes for v5.7-rc4

 - copy_*_user validity check for new vfio_dma_rw interface (Yan Zhao)

 - Fix a potential math overflow (Yan Zhao)

 - Use follow_pfn() for calculating PFNMAPs (Sean Christopherson)

----------------------------------------------------------------
Sean Christopherson (1):
      vfio/type1: Fix VA->PA translation for PFNMAP VMAs in vaddr_get_pfn()

Yan Zhao (2):
      vfio: checking of validity of user vaddr in vfio_dma_rw
      vfio: avoid possible overflow in vfio_iommu_type1_pin_pages

 drivers/vfio/vfio_iommu_type1.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)
```
#### [PATCH RFC 1/1] KVM: x86: add KVM_HC_UCALL hypercallFrom: Forrest Yuan Yu <yuanyu@google.com>
##### From: Forrest Yuan Yu <yuanyu@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Forrest Yuan Yu <yuanyu@google.com>
X-Patchwork-Id: 11523145
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E87AF1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 18:52:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C7564208DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 18:52:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ENp+jrNH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730403AbgEASwm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 14:52:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45164 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730074AbgEASwm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 1 May 2020 14:52:42 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 09906C061A0C
        for <kvm@vger.kernel.org>; Fri,  1 May 2020 11:52:42 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id i13so13139188ybl.13
        for <kvm@vger.kernel.org>; Fri, 01 May 2020 11:52:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=1OJhjIpUBl8ad63qNEszYk13rd+seOQrgj/fLGOHDLU=;
        b=ENp+jrNHDHEnFCUrs34p9XHzbIgaMGONWxhx86Fff6SGhFqcaF2zvmYIrZq1+dqm/v
         XQWdpdfP2jj0HIvvmoDooKXSxkL054VqBSEMYtbAP1T57Q/U/WTJw+ZKJPvvT/Fg94bH
         pn3yy/VEhb0ccDMs2kv7dYqS57a8kshinug/Nnl8NGxB9vD4NEkyzhoKnnA2IoGMrNmf
         zXL5m3fbw2BCKnnlSgvUKUDlmwpYm0y9m5BQBX/pLXrjqF2x+N7AbQZtZRSKQ1EYeB7v
         EMmJbQhq9ri/OV0aeAbzgm7BNjafSqvJ7z096/u5wDLpKr/fm6nvuE4qXBW8Or2Re7oW
         5VHA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=1OJhjIpUBl8ad63qNEszYk13rd+seOQrgj/fLGOHDLU=;
        b=FU+Fbbl1Av9bR5GJxdD9muHsxAv/LXUMPJD/JXPrfdKancTDfKX2e39EfLw0O8fUnV
         G2OYEWET+0T8ceyj/DcZ/UQETRKnRStxGIGwt86dt4NppDZgOkEbHMuRs/wI/fIjAUd3
         M6AlUsCEA5LGtl3S5dyZrGiCtedf/KgYsy7BhteulHjndJE4jT3UWRHhsrRC2qfZSXx5
         9TChzIoE+Mu2n/fd8v7AUhgz5WD1NFmPDDhNs06eUdAFx9LH2e/9CK/ADH7O/GNPBKZ2
         eMGgK0CabqHUEr4BvDhCiuoD9CUie6QKDPTcPUVfcRurn1HHOpUeDhhddOF/x3gNOpqP
         +U+w==
X-Gm-Message-State: AGi0PubG2wlG0abkp3oI6TiWoCZZkuEwoIJ7QW2MkqEtTUeLjhebxiUr
        6V8A/r3Lx+Qc61y3ujlRHQ8oWg1AMxGaqhXZGcK6v6dXzaM0hKDZKZOTgzieVIgh8PtloQE7n+c
        zNEbUggH/n9EhO5cKvJ+1+BR+OpEJOW01ryCfdazTqF/yV0Ylf17UR84ixA==
X-Google-Smtp-Source: 
 APiQypILvf65C7JFDilAloSEwV+u5hcCkePgCHAcvWSsYxY1r3g7IFi/sMeBdsbjU7abQidDEo2NCB03KR8=
X-Received: by 2002:a25:bd50:: with SMTP id p16mr8254556ybm.436.1588359160988;
 Fri, 01 May 2020 11:52:40 -0700 (PDT)
Date: Fri,  1 May 2020 11:51:47 -0700
In-Reply-To: <20200501185147.208192-1-yuanyu@google.com>
Message-Id: <20200501185147.208192-2-yuanyu@google.com>
Mime-Version: 1.0
References: <20200501185147.208192-1-yuanyu@google.com>
X-Mailer: git-send-email 2.26.2.526.g744177e7f7-goog
Subject: [PATCH RFC 1/1] KVM: x86: add KVM_HC_UCALL hypercall
From: Forrest Yuan Yu <yuanyu@google.com>
To: kvm@vger.kernel.org
Cc: Forrest Yuan Yu <yuanyu@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The purpose of this new hypercall is to exchange message between
guest and hypervisor. For example, a guest may want to ask hypervisor
to harden security by setting restricted access permission on guest
SLAT entry. In this case, the guest can use this hypercall to send
a message to the hypervisor which will do its job and send back
anything it wants the guest to know.

Signed-off-by: Forrest Yuan Yu <yuanyu@google.com>
---
 Documentation/virt/kvm/api.rst                |  15 +-
 Documentation/virt/kvm/cpuid.rst              |   3 +
 Documentation/virt/kvm/hypercalls.rst         |  14 ++
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/include/uapi/asm/kvm_para.h          |   1 +
 arch/x86/kvm/x86.c                            |  39 +++-
 include/uapi/linux/kvm.h                      |   1 +
 include/uapi/linux/kvm_para.h                 |   1 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/hypercall_ucall.c    | 195 ++++++++++++++++++
 11 files changed, 264 insertions(+), 8 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/hypercall_ucall.c

```
#### [PATCH v2] docs: kvm: Fix KVM_KVMCLOCK_CTRL API doc
##### From: Joshua Abraham <j.abraham1776@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joshua Abraham <j.abraham1776@gmail.com>
X-Patchwork-Id: 11523379
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D18D7912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 22:36:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B97252184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 22:36:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="tmyby0m5"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726654AbgEAWg3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 18:36:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51988 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726344AbgEAWg2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 18:36:28 -0400
Received: from mail-qt1-x844.google.com (mail-qt1-x844.google.com
 [IPv6:2607:f8b0:4864:20::844])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B751CC061A0C;
        Fri,  1 May 2020 15:36:28 -0700 (PDT)
Received: by mail-qt1-x844.google.com with SMTP id s30so9190201qth.2;
        Fri, 01 May 2020 15:36:28 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:date:to:cc:subject:message-id:mime-version:content-disposition
         :user-agent;
        bh=//VBQlgz2QErWHs4KuQV+SD3b0MIBzsXmXLMl95zhSM=;
        b=tmyby0m5RDw9evb17SgY8Fd/Zj4gSnKLPkGIJ7GZiXa1nWbs1C5Zq4GUq5qcp9rkh+
         60AMcevYkZHMZnecNjHbrjtg0EToaP7PchW/S3TYQzEBiRhAsRWVC90QSt7jQhP7qU9G
         yfQNbeMxsq1ca4lQjaF/J+qpaI2BLrd0vXi6UKY5e3BJSaPs3j3KbA2Pr8jRs3A6eUF/
         hWuBw3KQfgzR7MntRCdS+BzluOY2ZLfOy2zkqa1FGVDvf0jO+M2/5RU1ZBYxPtGW/g+Y
         GX+LoueomxFdWudz5mFA1E9vg07z9h8D4pLb4c2eW8PHIDRwIUlYYJAJj/xZx1vz8nhJ
         DlSQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:date:to:cc:subject:message-id:mime-version
         :content-disposition:user-agent;
        bh=//VBQlgz2QErWHs4KuQV+SD3b0MIBzsXmXLMl95zhSM=;
        b=bKBTRb8hhHAop4/21RmlJ2rCEfIduodq/4tJbyt/vTWu+0WpQZpfDHwsxP4hXoUagu
         gxB6ouaoqAHuuKhXa2HWicWbENSOeJ8xb1SfSA8q4af2hgpidKN7Mjeg0Gg+ap1LrZtN
         3Jv1WqQ7MH6r4Woty4EwziJLSegIWx3zE0fAdX+fmFXfXNppdlFgzQv06ezXzTWXWZvu
         8zkq8jEwSDPwDrpLONW6/jCPvhVNGFgUbOW2VaXdcGzPV5GFR5b+eL66oUYFskqMGdjT
         0Kch16JIjJyj7etkruM+frAUnV1kP8B3/kHuyC5qfSkEyYduXRpJR8da7nazoTLth8P8
         jU4A==
X-Gm-Message-State: AGi0PuZmKzPZ5puyOHxL2Cs5N3m6z4PHKvvLiY0Flh7i/tXqFvUdWET+
        ro78khn+OwgR4sCgU2EcDrM=
X-Google-Smtp-Source: 
 APiQypIPWHr5FoUb18G1X2SssTCIF+/SQKgp8wAoZR4JVUZTJuz+DvKbfIG42v83pL/M+W2M6g1DBw==
X-Received: by 2002:ac8:7ca2:: with SMTP id z2mr6151676qtv.122.1588372587911;
        Fri, 01 May 2020 15:36:27 -0700 (PDT)
Received: from josh-ZenBook ([70.32.0.110])
        by smtp.gmail.com with ESMTPSA id
 q62sm2629934qke.22.2020.05.01.15.36.26
        (version=TLS1_2 cipher=ECDHE-ECDSA-CHACHA20-POLY1305 bits=256/256);
        Fri, 01 May 2020 15:36:26 -0700 (PDT)
From: Joshua Abraham <j.abraham1776@gmail.com>
X-Google-Original-From: Joshua Abraham <sinisterpatrician@gmail.com>
Date: Fri, 1 May 2020 18:36:24 -0400
To: pbonzini@redhat.com
Cc: corbet@lwn.net, kvm@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, j.abraham1776@gmail.com
Subject: [PATCH v2] docs: kvm: Fix KVM_KVMCLOCK_CTRL API doc
Message-ID: <20200501223624.GA25826@josh-ZenBook>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM_KVMCLOCK_CTRL ioctl signals to supported KVM guests
that the hypervisor has paused it. Update the documentation to
reflect that the guest is notified by this API.

Signed-off-by: Joshua Abraham <sinisterpatrician@gmail.com>
---
Changes in v2:
    - Re-word documentation to be clearer. Also fix a small grammar
      error.

 Documentation/virt/kvm/api.rst | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Skip IBPB when switching between vmcs01 and vmcs02
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11522851
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7CEFA92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 16:31:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EAD624953
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 16:31:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729581AbgEAQbT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 12:31:19 -0400
Received: from mga18.intel.com ([134.134.136.126]:34079 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728443AbgEAQbT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 12:31:19 -0400
IronPort-SDR: 
 W5sDEKIs7gx6q57Zw/agA/E19Qt/IYxLuPV/v/5g7tJu8TK7yAikEc/cBCkU16Ixkse2k/L4ih
 hEbd/uaK5roA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 May 2020 09:31:18 -0700
IronPort-SDR: 
 cpEtsaaOrcMa0T8NEjZHyuf7OcEaONkNfLXa6DIHBYIQTqjUCVND3/OmJiIN40xVxl9pVTHgus
 2PfpTHNI7yKw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,340,1583222400";
   d="scan'208";a="262131602"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga006.jf.intel.com with ESMTP; 01 May 2020 09:31:18 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        KarimAllah Raslan <karahmed@amazon.de>
Subject: [PATCH v2] KVM: nVMX: Skip IBPB when switching between vmcs01 and
 vmcs02
Date: Fri,  1 May 2020 09:31:17 -0700
Message-Id: <20200501163117.4655-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Skip the Indirect Branch Prediction Barrier that is triggered on a VMCS
switch when running with spectre_v2_user=on/auto if the switch is
between two VMCSes in the same guest, i.e. between vmcs01 and vmcs02.
The IBPB is intended to prevent one guest from attacking another, which
is unnecessary in the nested case as it's the same guest from KVM's
perspective.

This all but eliminates the overhead observed for nested VMX transitions
when running with CONFIG_RETPOLINE=y and spectre_v2_user=on/auto, which
can be significant, e.g. roughly 3x on current systems.

Reported-by: Alexander Graf <graf@amazon.com>
Cc: KarimAllah Raslan <karahmed@amazon.de>
Cc: stable@vger.kernel.org
Fixes: 15d45071523d ("KVM/x86: Add IBPB support")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

v2: Pass a boolean to indicate a nested VMCS switch and instead WARN if
    the buddy VMCS is not already loaded.  [Alex]

Paolo, feel free to drop the WARN_ON_ONCE() if you think it's overkill.
I'm 50/50 as to whether it's useful or just a waste of cycles.  Figured
it'd be easier for you to delete a line of code while applying than to add
and test a new WARN.

 arch/x86/kvm/vmx/nested.c | 3 ++-
 arch/x86/kvm/vmx/vmx.c    | 7 ++++---
 arch/x86/kvm/vmx/vmx.h    | 2 +-
 3 files changed, 7 insertions(+), 5 deletions(-)

```
#### [PATCH v2] vhost: vsock: kick send_pkt worker once device is started
##### From: Jia He <justin.he@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jia He <justin.he@arm.com>
X-Patchwork-Id: 11522043
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA00281
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 04:39:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CCA8F20731
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 04:39:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728232AbgEAEi5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 00:38:57 -0400
Received: from foss.arm.com ([217.140.110.172]:36242 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726153AbgEAEi4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 00:38:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id CB9871FB;
        Thu, 30 Apr 2020 21:38:55 -0700 (PDT)
Received: from localhost.localdomain (entos-thunderx2-02.shanghai.arm.com
 [10.169.138.57])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 29EC83F73D;
        Thu, 30 Apr 2020 21:38:52 -0700 (PDT)
From: Jia He <justin.he@arm.com>
To: Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Kaly Xin <Kaly.Xin@arm.com>,
        Jia He <justin.he@arm.com>
Subject: [PATCH v2] vhost: vsock: kick send_pkt worker once device is started
Date: Fri,  1 May 2020 12:38:40 +0800
Message-Id: <20200501043840.186557-1-justin.he@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ning Bo reported an abnormal 2-second gap when booting Kata container [1].
The unconditional timeout was caused by VSOCK_DEFAULT_CONNECT_TIMEOUT of
connecting from the client side. The vhost vsock client tries to connect
an initializing virtio vsock server.

The abnormal flow looks like:
host-userspace           vhost vsock                       guest vsock
==============           ===========                       ============
connect()     -------->  vhost_transport_send_pkt_work()   initializing
   |                     vq->private_data==NULL
   |                     will not be queued
   V
schedule_timeout(2s)
                         vhost_vsock_start()  <---------   device ready
                         set vq->private_data

wait for 2s and failed
connect() again          vq->private_data!=NULL         recv connecting pkt

Details:
1. Host userspace sends a connect pkt, at that time, guest vsock is under
   initializing, hence the vhost_vsock_start has not been called. So
   vq->private_data==NULL, and the pkt is not been queued to send to guest
2. Then it sleeps for 2s
3. After guest vsock finishes initializing, vq->private_data is set
4. When host userspace wakes up after 2s, send connecting pkt again,
   everything is fine.

As suggested by Stefano Garzarella, this fixes it by additional kicking the
send_pkt worker in vhost_vsock_start once the virtio device is started. This
makes the pending pkt sent again.

After this patch, kata-runtime (with vsock enabled) boot time is reduced
from 3s to 1s on a ThunderX2 arm64 server.

[1] https://github.com/kata-containers/runtime/issues/1917

Reported-by: Ning Bo <n.b@live.com>
Suggested-by: Stefano Garzarella <sgarzare@redhat.com>
Signed-off-by: Jia He <justin.he@arm.com>
Reviewed-by: Stefano Garzarella <sgarzare@redhat.com>
---
v2: new solution suggested by Stefano Garzarella

 drivers/vhost/vsock.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH 1/3] vfio/type1: Support faulting PFNMAP vmasFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11523299
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 442AF13B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:39:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2CF742184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:39:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="COeXvT7/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727047AbgEAVj3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 17:39:29 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:33707 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726762AbgEAVj2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 1 May 2020 17:39:28 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588369167;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Eckl6hH0AbgL49kEhmxA8Bwx9T7n/rxh8xbcvWxSc1I=;
        b=COeXvT7/wJdq0K5kZGtA9pOYN+23VcAm1cxUw732BAkgT8wfqNjbgkqR/FWgHgt+OvSC+F
        5b2ECtypDKq1PPkIlD9uvHk5KHxR25wF1YZD3iwyrADoPKs9H4h6TKOLE6NcUtYiFP3935
        Mrdlfz4oTaz3avHviaOYkGBKUej9yrQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-472-VGPdlWLBMt22sw6NqGdmiw-1; Fri, 01 May 2020 17:39:15 -0400
X-MC-Unique: VGPdlWLBMt22sw6NqGdmiw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 189B345F;
        Fri,  1 May 2020 21:39:14 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6E9195D9CA;
        Fri,  1 May 2020 21:39:08 +0000 (UTC)
Subject: [PATCH 1/3] vfio/type1: Support faulting PFNMAP vmas
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com, jgg@ziepe.ca,
        peterx@redhat.com
Date: Fri, 01 May 2020 15:39:08 -0600
Message-ID: <158836914801.8433.9711545991918184183.stgit@gimli.home>
In-Reply-To: <158836742096.8433.685478071796941103.stgit@gimli.home>
References: <158836742096.8433.685478071796941103.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c |   36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
#### [PATCH] vfio-pci: Mask cap zeroFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11523305
Return-Path: <SRS0=uSm/=6P=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F3CDE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:41:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DB901216FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  1 May 2020 21:41:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XOE7VHvx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726782AbgEAVlc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 1 May 2020 17:41:32 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:49576 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726045AbgEAVlc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 1 May 2020 17:41:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588369291;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=na8QnBz7W2Ii0eveaJBlRsX241pOL+BoPANtqMrwttE=;
        b=XOE7VHvxJxQc4nCQ88aGNprK4Vn3G1piZHMccoF68UoVgQ2qAbZjfJRc4wzupbtD1y0cmU
        5AzyRzirTkLqR/YnNPi2UAnnVT89N7uwzE4peG/Z5JtpCCKjsdiW7PRwwtIVEsnPCzRuog
        0Ymv3oWvLkAMsbAxu8IB4oHUiUrRcwE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-503-3SfWvdkbNrmSPRf_Im86qw-1; Fri, 01 May 2020 17:41:29 -0400
X-MC-Unique: 3SfWvdkbNrmSPRf_Im86qw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5DC7A100CCC3;
        Fri,  1 May 2020 21:41:28 +0000 (UTC)
Received: from gimli.home (ovpn-113-95.phx2.redhat.com [10.3.113.95])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 14AE55C1B0;
        Fri,  1 May 2020 21:41:25 +0000 (UTC)
Subject: [PATCH] vfio-pci: Mask cap zero
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, cohuck@redhat.com
Date: Fri, 01 May 2020 15:41:24 -0600
Message-ID: <158836927527.9272.16785800801999547009.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no PCI spec defined capability with ID 0, therefore we don't
expect to find it in a capability chain and we use this index in an
internal array for tracking the sizes of various capabilities to handle
standard config space.  Therefore if a device does present us with a
capability ID 0, we mark our capability map with nonsense that can
trigger conflicts with other capabilities in the chain.  Ignore ID 0
when walking the capability chain, handling it as a hidden capability.

Seen on an NVIDIA Tesla T4.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_config.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
