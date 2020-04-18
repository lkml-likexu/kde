#### [kvm PATCH 1/2] KVM: nVMX - enable VMX preemption timer migrationFrom: Makarand Sonare <makarandsonare@google.com>
##### From: Makarand Sonare <makarandsonare@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11495931
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC369174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:35:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D053B2223C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:35:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="na6HeB+4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729132AbgDQSfT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 14:35:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45322 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729094AbgDQSfS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 14:35:18 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EECD9C061A0C
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:35:16 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id q11so2720098pfq.9
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:35:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=QQqAabiBFaz8mQ9VmW0Dl+mz5jUjATZVVCBZzR434Cc=;
        b=na6HeB+4EAvIxKTcfNzGBPTmnP86S3lU0FLQeHngy4Rv2mGdswiqquhdlUDDiTrcDC
         vpdqjPL04LL7zP+n6DloZdAPLKw64VbdRJ7npAogn3UAR9Z9dQO6SKCJiM8Us+aH0pAq
         ljhM4tOqEnlAHUyThGOKeKZYldQZ59og+xNJaRz+DjJbArf4qDwvDLdVvkrBgTOU0Ekg
         6IsPwj4nJt0OtZGUsHIyGjv53KDl9AZpvjB+Jnq8B6f0cE1F5DALBLdX/f0t0rVtJLXb
         NXh0vC4Tjr8vXBvzCiexPFaG2Axib/rtkrDkleDB26+RYnMMDIQBs9RRF3KyJHrcSB15
         LJBw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=QQqAabiBFaz8mQ9VmW0Dl+mz5jUjATZVVCBZzR434Cc=;
        b=OeB4fcSTnPobNlr8j0c49pBLN5FvD/SkYU0VQ4Bsik3OwmN0DI9h386CY/pH6t4UPa
         rl8AuzhmyywFcy1t/+QG9HUhc552XdP2T62AZ8y3qgff9LfPigtZCELotFAkTrhYAHde
         P2wjqk721BG7pI48XSgJiYKHjb86QdZoyyU8BgFl/yGxrJa4gejhRZfwuB//n3WRMrL8
         TbSUKOa+k2YQ7n1Gk/CfHK1PwXBjJnXUddPjUjc4b7vaF+pIzv9AiZb+3Hd/0enkBz0c
         PGaUx4PU5cO26aiMYvac00s3rrMb/ZFn9M2vhwSsYlPbPMdUnWeTsZj7ekZGhooW3AX7
         CEgA==
X-Gm-Message-State: AGi0Publ4QWIu5WqdzABlUGDVTNA6ekeG95Ov+FvvkaF9vVbb5VZCt8j
        RvHFjBiZ874p+b7kqkDyvW1BIRAl97f1d3OAyvgTMXngVapZLWliH264oFgyToeA/Ciq1weEKic
        PnAby7iL/+oEhGECE0eRxXbAIEyqydBZOUsw0wBBvNFhiOqeSKYLnNa3o0rVQcNeZEGtuSzHTDt
        om648=
X-Google-Smtp-Source: 
 APiQypJDow6DhpJK7KznRuTF7lt32GWYrtA7vfKl8i6qwMdRsINM+PE6AK88G0IvU2vJmNbw8I+GcvZcfk+kTcTfvu3X+Q==
X-Received: by 2002:a63:9902:: with SMTP id d2mr4350478pge.8.1587148516380;
 Fri, 17 Apr 2020 11:35:16 -0700 (PDT)
Date: Fri, 17 Apr 2020 11:34:51 -0700
In-Reply-To: <20200417183452.115762-1-makarandsonare@google.com>
Message-Id: <20200417183452.115762-2-makarandsonare@google.com>
Mime-Version: 1.0
References: <20200417183452.115762-1-makarandsonare@google.com>
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [kvm PATCH 1/2] KVM: nVMX - enable VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Add new field to hold preemption timer remaining until expiration
appended to struct kvm_vmx_nested_state_data. KVM_SET_NESTED_STATE restarts
timer using migrated state regardless of whether L1 sets
VM_EXIT_SAVE_VMX_PREEMPTION_TIMER.

Fixes: cf8b84f48a593 ("kvm: nVMX: Prepare for checkpointing L2 state")

Signed-off-by: Makarand Sonare <makarandsonare@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
Change-Id: I6446aba5a547afa667f0ef4620b1b76115bf3753
---
 Documentation/virt/kvm/api.rst        |  4 ++
 arch/x86/include/uapi/asm/kvm.h       |  2 +
 arch/x86/kvm/vmx/nested.c             | 62 +++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.h                |  1 +
 arch/x86/kvm/x86.c                    |  1 +
 include/uapi/linux/kvm.h              |  1 +
 tools/arch/x86/include/uapi/asm/kvm.h |  2 +
 7 files changed, 65 insertions(+), 8 deletions(-)

```
#### [PATCH] kvm: add capability for halt pollingFrom: Jon Cargille <jcargill@google.com>
##### From: Jon Cargille <jcargill@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Cargille <jcargill@google.com>
X-Patchwork-Id: 11496181
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA8EA14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 22:15:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA2DE20656
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 22:15:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="lRcq3dUu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728671AbgDQWPK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 18:15:10 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51052 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728459AbgDQWPI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 18:15:08 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D1C85C061A0F
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 15:15:08 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id w16so3043970plq.1
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 15:15:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=fUd4e7ib6miSI3t5irBL1ImGs5/WYOOO3j+GPX3G4w8=;
        b=lRcq3dUuEu5g2QMOkNKjKJkQrMD5KPtroJhHUhI1PIxhhGT/r5NRAqCueq6tDc/XTt
         aJ9rUaaUcg7abTz44b7JUfupMPrSgqg3bcCov2XaPBLBiLUuhYIsqLUbzTg7KwmXoqmX
         9tFdWZj4VetAfDGu3VVsbEQkIBHYfvBt5MppI6CVmE3eSgJ6RxqLlwUi45BWMaFG0u9M
         8hHVAUC9u/1Dj/BRlwe08QkG35bZtA0RoTbmyQCROtsBjWqEwjsHrR91dcil48pQ6BaA
         F9yFoCrgzLY0ttvkyN5WXkZTDlzq8ATCXbilIW951vO/4fPcSB96TkWVJxUFYSUdYsez
         XKCQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=fUd4e7ib6miSI3t5irBL1ImGs5/WYOOO3j+GPX3G4w8=;
        b=pFreq1QP3SlISCDpiApIzurm1NG7t60z6C12PRc8/bjWXBHPwwEgMdCogSuhWA63/0
         HFSe7hBGRaXtwYvjwxfZN2GAfmjmTRn5sfHSMHwWIJNuniA03I6ytcUN1OHwAy2ctR8D
         WZD5sD4fg7RRZ+6gfpLdu63fzCBHRDHiD2IVzVdkGUxM5VH3mwDaH3CJQ+mwwMACs2Ca
         QATgroRWAkOt9jkNyLr2KRDUGdHu/JyeygqYkPr8ZFGQyL8YR2PF9g84Cwip5EjffAbK
         Lpqo1wpR+C0ePuajaeudcSrkkqEKEokHOyOLEBq/ielK2euLcaaPphM61vmGEJ3HHtOi
         Mafg==
X-Gm-Message-State: AGi0PuYQ3J6sJqkACyJpJCDQidblazjhclyK5MANwD8rAgcXsIRwLoEj
        O0UrKowdtnazEA/Hkndy300PXjQwE+vvPg==
X-Google-Smtp-Source: 
 APiQypLSLh6jSBxbBtX2SkrqDIEjfwxQnKC5GoW9CO6XBLKWtU7T2gax2Vry4WQug150Tqnv8SHx8yFoe3ffkA==
X-Received: by 2002:a17:90a:210b:: with SMTP id
 a11mr7283677pje.31.1587161708131;
 Fri, 17 Apr 2020 15:15:08 -0700 (PDT)
Date: Fri, 17 Apr 2020 15:14:46 -0700
Message-Id: <20200417221446.108733-1-jcargill@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.1.301.g55bc3eb7cb9-goog
Subject: [PATCH] kvm: add capability for halt polling
From: Jon Cargille <jcargill@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: David Matlack <dmatlack@google.com>,
        Jon Cargille <jcargill@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Matlack <dmatlack@google.com>

KVM_CAP_HALT_POLL is a per-VM capability that lets userspace
control the halt-polling time, allowing halt-polling to be tuned or
disabled on particular VMs.

With dynamic halt-polling, a VM's VCPUs can poll from anywhere from
[0, halt_poll_ns] on each halt. KVM_CAP_HALT_POLL sets the
upper limit on the poll time.

Signed-off-by: David Matlack <dmatlack@google.com>
Signed-off-by: Jon Cargille <jcargill@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 Documentation/virt/kvm/api.rst | 17 +++++++++++++++++
 include/linux/kvm_host.h       |  1 +
 include/uapi/linux/kvm.h       |  1 +
 virt/kvm/kvm_main.c            | 19 +++++++++++++++----
 4 files changed, 34 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/6] KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11494459
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2A8815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 08:33:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88497221EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 08:33:39 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587112419;
	bh=exX30MBHh/JKazRWYTFyi87muy0zveZWPuO12yNLcOs=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=kSGS3YTodZJzWLyxagWpxtzuSlpt3SDv/ux2DjQYfcxkeJ/+noC7XNl3MHao3ClGJ
	 4RkFfMPcFMzyWNxEHV9TWDDplo3Z8s1g9qZcxZbN+HDR/iM2vBkGorLpWLFsOjSBEK
	 pTYjUg0Dzd7NkznKvYK11Lh0JkuxRQi/LkwCRupw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729779AbgDQIdj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 04:33:39 -0400
Received: from mail.kernel.org ([198.145.29.99]:59346 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729166AbgDQIdi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 04:33:38 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id ECB9921D95;
        Fri, 17 Apr 2020 08:33:37 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587112418;
        bh=exX30MBHh/JKazRWYTFyi87muy0zveZWPuO12yNLcOs=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=bsUphSa5EhVomRNPSzWZgVy1RjGUSl45SFjXYEHhDFIWXqPTt6YlJkc4p/mWHOEkK
         GSzixvy9j3t1gEJqmjmB3W1l2gNB3aSZFKL9luPn0+2/6YkXdqPDnf7zAbCbupiutK
         Y8D2fubSodxuCXjfgocWYeuF8r4Q61txv/traUWE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jPMRM-00473f-47; Fri, 17 Apr 2020 09:33:36 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>, Eric Auger <eric.auger@redhat.com>,
 Andre Przywara <Andre.Przywara@arm.com>, Julien Grall <julien@xen.org>,
 James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, stable@vger.kernel.org,
	=?utf-8?q?Andr=C3=A9_Przywara?= <andre.przywara@arm.com>
Subject: [PATCH v2 1/6] KVM: arm: vgic: Fix limit condition when writing to
 GICD_I[CS]ACTIVER
Date: Fri, 17 Apr 2020 09:33:14 +0100
Message-Id: <20200417083319.3066217-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
In-Reply-To: <20200417083319.3066217-1-maz@kernel.org>
References: <20200417083319.3066217-1-maz@kernel.org>
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
#### [PATCH 1/2] KVM: SVM: avoid infinite loop on NPF from bad address
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11495573
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 537B9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:39:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D13822209
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:39:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UeaX/l/2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726507AbgDQQiv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 12:38:51 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:58019 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726387AbgDQQis (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 12:38:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587141527;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=J7/+hu9xA4V/kb8irjtGYa6Qo9G4EJkKAhc6pSJfI0o=;
        b=UeaX/l/20GO3JBwzsoQIi8onTZ+diuiktMtOtbfHrMJ7O6KCyUtL7hbH4K/0jYba9P9I2+
        r5hWcAb7RKeYk3vyfjcGxRjVAtr62wnJ+I38mUcqJdat3+K8zfjRXlZIAra17Tx7hgFtyb
        p/nunvavmPec9WpdzyEl4z1jrLcReCg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-390-wpnn2rtMOUa9iepu47f1rA-1; Fri, 17 Apr 2020 12:38:45 -0400
X-MC-Unique: wpnn2rtMOUa9iepu47f1rA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 84C2E8024E2;
        Fri, 17 Apr 2020 16:38:44 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1846C5DA84;
        Fri, 17 Apr 2020 16:38:44 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH 1/2] KVM: SVM: avoid infinite loop on NPF from bad address
Date: Fri, 17 Apr 2020 12:38:42 -0400
Message-Id: <20200417163843.71624-2-pbonzini@redhat.com>
In-Reply-To: <20200417163843.71624-1-pbonzini@redhat.com>
References: <20200417163843.71624-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a nested page fault is taken from an address that does not have
a memslot associated to it, kvm_mmu_do_page_fault returns RET_PF_EMULATE
(via mmu_set_spte) and kvm_mmu_page_fault then invokes svm_need_emulation_on_page_fault.

The default answer there is to return false, but in this case this just
causes the page fault to be retried ad libitum.  Since this is not a
fast path, and the only other case where it is taken is an erratum,
just stick a kvm_vcpu_gfn_to_memslot check in there to detect the
common case where the erratum is not happening.

This fixes an infinite loop in the new set_memory_region_test.

Fixes: 05d5a4863525 ("KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)")
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/svm.c | 7 +++++++
 virt/kvm/kvm_main.c    | 1 +
 2 files changed, 8 insertions(+)

```
#### [PATCH] KVM: VMX: Improve handle_external_interrupt_irqoff inline assembly
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11494833
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33DDE912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 11:35:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16940221EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 11:35:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="IiIR5pDK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730352AbgDQLfn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 07:35:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36524 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-FAIL-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730267AbgDQLfm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 07:35:42 -0400
Received: from mail-wr1-x442.google.com (mail-wr1-x442.google.com
 [IPv6:2a00:1450:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E673EC061A0C
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 04:35:40 -0700 (PDT)
Received: by mail-wr1-x442.google.com with SMTP id u13so2678568wrp.3
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 04:35:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CMuJlUa2xrrUdubk63aMvSEJCfbQVxpKSxcLKYf9XCA=;
        b=IiIR5pDKCnqXiawSXT03bf2ycyGhGY/nBwnpPrkxfT561D/JL838BwwlyjmmuHrjBs
         kRg0p/hAIXKAnDmSExhVCFNisdp+R9YVWd2MAkVevF8F6pvjnrlbeRm2LnM629w/wIhg
         EbmcowHDmkyWhacu3VuVZ+iPKTx1VFV8Su2kcfasOW+90juRpoZ07e9KGKuNNp8gctyU
         E6pDo+t7zBPNRow62eM1+W6M4kPBF37HajZGguzpmL2/HpeFoEtJgL1ZLAab/8vANTNL
         7nbiWBP+pQulNsxrQJ/4AshwXf96g7157u/SqUeHxQhZZHEKIMe5vjrTpnX+hsygnCZH
         gqMQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=CMuJlUa2xrrUdubk63aMvSEJCfbQVxpKSxcLKYf9XCA=;
        b=b+mWrbWkt6oI9iYRM9EMw2unN9CPa3Uyc7PHU3786tlUj6MkyrMyM+AhtpzBSXmzLv
         J+buU784XOW7x4Gff5KSQ4yD8jgI8kcMaBQJu1eHsUMnKgvlNfLdbelDAVwe6fqEypgA
         uE7IHxM5aMDxhW0E2v+6NZ4xduSfv/rNRbVHu0CJDQPm4tFqzJV8qO0H8V7DWJNNEQPg
         VIt5JWFP/diribmOby4tAfBgdP2/6PIWtTgir1W/LQd/wbqbov/ulM2jZ8jKmuutg7kp
         Q3fZ56fzgyJNz+P+9KGKm6O3taM8r/FwyZNogTkgt/r899mMn1T7gZN4yy3eg3CIr1mH
         C3kg==
X-Gm-Message-State: AGi0PuaLa3D9LB8dMdM9Bitj/BilJMzjQQvvHZwW8Wac4K/HcmojDyG1
        bamSTm0uSzgapNK92h5tWN3svAtY37k=
X-Google-Smtp-Source: 
 APiQypKiKUrzaJLh70hbIcZXyqpe5BdSXRKmFoNvPY1Xjt8IvnyaroZFLgjKx0DLtOvY1tRcASNt9A==
X-Received: by 2002:adf:e98a:: with SMTP id h10mr3501530wrm.370.1587123339127;
        Fri, 17 Apr 2020 04:35:39 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 u15sm29655312wrn.46.2020.04.17.04.35.38
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 17 Apr 2020 04:35:38 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: VMX: Improve handle_external_interrupt_irqoff inline
 assembly
Date: Fri, 17 Apr 2020 13:35:24 +0200
Message-Id: <20200417113524.1280130-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Improve handle_external_interrupt_irqoff inline assembly in several ways:
- use __stringify to use __KERNEL_DS and __KERNEL_CS directly in assembler
- use %rsp instead of _ASM_SP, since we are in CONFIG_X86_64 part
- use $-16 immediate to align %rsp
- avoid earlyclobber by using "l" GCC input operand constraint
- avoid temporary by using current_stack_pointer

The patch introduces no functional change.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 19 ++++++-------------
 1 file changed, 6 insertions(+), 13 deletions(-)

```
#### [PATCH 1/3] KVM: x86: check_nested_events is never NULL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11495575
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F6AA912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:44:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 077872223C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 16:44:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bzU57dht"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726644AbgDQQoT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 12:44:19 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:32416 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725877AbgDQQoT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 17 Apr 2020 12:44:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587141858;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=1zf3L5Eiqysm5g8uOwD9B/4Ckh+3dv+ZAttkjbtK7fY=;
        b=bzU57dht5BUeyZfKDGye9e1/HoMzY9FkAYptVMOQw6gYxoFzUy0XL9TcRztI8fJC18hXYu
        iWuj4UMiYquYKyVKLandXY9xdJ7K73TQPvTrjJDNP/gVFdQesU2KFJwW+povlfd36y0jZj
        3OBmd62xLOjxkDdgzZBneS9VEA63V1s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-28-Pev9DEbNNVW3-99nIAHpJg-1; Fri, 17 Apr 2020 12:44:16 -0400
X-MC-Unique: Pev9DEbNNVW3-99nIAHpJg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4133B800D53;
        Fri, 17 Apr 2020 16:44:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AE81D10016E8;
        Fri, 17 Apr 2020 16:44:14 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH 1/3] KVM: x86: check_nested_events is never NULL
Date: Fri, 17 Apr 2020 12:44:11 -0400
Message-Id: <20200417164413.71885-2-pbonzini@redhat.com>
In-Reply-To: <20200417164413.71885-1-pbonzini@redhat.com>
References: <20200417164413.71885-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Both Intel and AMD now implement it, so there is no need to check if the
callback is implemented.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/8] vfio-ccw: Introduce new helper functions to free/destroy regions
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11494021
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D7550913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 02:30:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C576E221E9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 02:30:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729336AbgDQCaL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 16 Apr 2020 22:30:11 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:25400 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729306AbgDQCaJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 16 Apr 2020 22:30:09 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03H23LTp129679
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 22:30:09 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30f37agprb-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 16 Apr 2020 22:30:08 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Fri, 17 Apr 2020 03:30:01 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 17 Apr 2020 03:29:59 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03H2U2vZ48562372
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Apr 2020 02:30:02 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3300D5204E;
        Fri, 17 Apr 2020 02:30:02 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 209C652050;
        Fri, 17 Apr 2020 02:30:02 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id B0F7DE0271; Fri, 17 Apr 2020 04:30:01 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: linux-s390@vger.kernel.org, kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 1/8] vfio-ccw: Introduce new helper functions to
 free/destroy regions
Date: Fri, 17 Apr 2020 04:29:54 +0200
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200417023001.65006-1-farman@linux.ibm.com>
References: <20200417023001.65006-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20041702-0028-0000-0000-000003F9A44D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20041702-0029-0000-0000-000024BF5C8F
Message-Id: <20200417023001.65006-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-16_10:2020-04-14,2020-04-16 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 spamscore=0
 impostorscore=0 adultscore=0 priorityscore=1501 mlxlogscore=741
 suspectscore=2 malwarescore=0 lowpriorityscore=0 phishscore=0 bulkscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004170014
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Farhan Ali <alifm@linux.ibm.com>

Consolidate some of the cleanup code for the regions, so that
as more are added we reduce code duplication.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

Notes:
    v1->v2:
     - Add Conny's r-b
    
    v0->v1: [EF]
     - Commit message

 drivers/s390/cio/vfio_ccw_drv.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH v1 1/1] MAINTAINERS: add a reviewer for KVM/s390
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11495415
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63E4814B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 15:29:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55CD720936
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 15:29:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728542AbgDQP3p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 11:29:45 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:48584 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729038AbgDQP3p (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 11:29:45 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03HF3xOg133968
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:29:44 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30fdpnb33b-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 11:29:44 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Fri, 17 Apr 2020 16:29:37 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 17 Apr 2020 16:29:34 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03HFTbpi58916992
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Apr 2020 15:29:37 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 78B7411C04A;
        Fri, 17 Apr 2020 15:29:37 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 16A1711C050;
        Fri, 17 Apr 2020 15:29:37 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.0.99])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 17 Apr 2020 15:29:37 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: borntraeger@de.ibm.com, frankja@linux.ibm.com
Cc: pbonzini@redhat.com, cohuck@redhat.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v1 1/1] MAINTAINERS: add a reviewer for KVM/s390
Date: Fri, 17 Apr 2020 17:29:36 +0200
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20041715-0028-0000-0000-000003F9F9AD
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20041715-0029-0000-0000-000024BFB3E9
Message-Id: <20200417152936.772256-1-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-17_06:2020-04-17,2020-04-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 clxscore=1015
 malwarescore=0 phishscore=0 suspectscore=0 spamscore=0 bulkscore=0
 mlxlogscore=756 impostorscore=0 adultscore=0 lowpriorityscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004170118
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v9] virtio: force spec specified alignment on types
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11494417
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 16CF413B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 07:59:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED5E2214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 07:59:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="e95iTkLH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729573AbgDQH7p (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 03:59:45 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:58082 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729112AbgDQH7o (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 03:59:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587110382;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=pttTsXfJsO5qd96fUX4GjjyN7BeuHWmaGEZtAEZg4sw=;
        b=e95iTkLHqziq04e8cy8zr6wrbYPcnJUpfdkK+Ed9TORbj18pp5butqPNjwUhYgSJXGKnog
        dll6KB4+D1A9PHUwFcBA48ZLMt29VsCRZAIoSR3jme41jQk/beHvw6NHzlkQ69MHoHE8Gl
        BaWVAHUSD6ZUE3jo+RhKVvdgdcj+ETs=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-317-F5g3znBZMXu1bPCwuQep4w-1; Fri, 17 Apr 2020 03:59:39 -0400
X-MC-Unique: F5g3znBZMXu1bPCwuQep4w-1
Received: by mail-wr1-f72.google.com with SMTP id y1so605086wrp.5
        for <kvm@vger.kernel.org>; Fri, 17 Apr 2020 00:59:39 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=pttTsXfJsO5qd96fUX4GjjyN7BeuHWmaGEZtAEZg4sw=;
        b=EI6FiF1/EE9BZHgJ2oKbj0O5gN3fH8GDtmCiLzbARD5edzk0jpm0gdIXWnTb/BUbdR
         SrMEwAbFHDfQdy+zqkiWTYC4JNJ69tmavFSvgbptlg2A2inzMejmeKKyos5Cclw8jZlo
         i+S7lEcxAYLsJUeAC+PQLEoPaFDSS0qp3N1+djahuIIlwfvXtiCzUCFGiC3OT2x+CDJy
         Go+EkFGBCe+axzLMyuLjf0zE/N6prBsb7L7N3BBRxfYf1IwqdR/NhtXuDZFn4eR2g95o
         W1wG+co40NWKWoK+0Qdlv7CK76srkLida4G+3Y4P5X2VFieqkLyKNIUVy5RkmoalnCn+
         6hQw==
X-Gm-Message-State: AGi0PuaiXSH3QXzaiVz6ZqH56UoLIyRy6Q4h+I1Kn7Sew8Rmm2imXzjH
        xLjAkGEKekRqjqd/Z8TpeG4Gbr41/duaLlaHksCT4rrxZJgBi+W/uWK9LZlYGkkGw9cf3Oa6oQM
        /X0G4S20efkFC
X-Received: by 2002:a1c:9d84:: with SMTP id
 g126mr1898736wme.184.1587110378073;
        Fri, 17 Apr 2020 00:59:38 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypL7JfXhE5vFVj1kJeWaNlkc8YDs13yjfj3N/sFo8oSVy/wgjrWfOFrSOQ9Dg05aWCm/T5Fq4A==
X-Received: by 2002:a1c:9d84:: with SMTP id
 g126mr1898718wme.184.1587110377796;
        Fri, 17 Apr 2020 00:59:37 -0700 (PDT)
Received: from redhat.com (bzq-79-183-51-3.red.bezeqint.net. [79.183.51.3])
        by smtp.gmail.com with ESMTPSA id
 o28sm16416939wra.84.2020.04.17.00.59.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 17 Apr 2020 00:59:37 -0700 (PDT)
Date: Fri, 17 Apr 2020 03:59:34 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH v9] virtio: force spec specified alignment on types
Message-ID: <20200417075551.12291-1-mst@redhat.com>
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

I am still not sure this is even needed. Does compiler make
optimizations based on ABI alignment assumptions?


Changes from v8:
	- better commit log
	- go back to vring in UAPI

 drivers/vhost/vhost.h            |  6 ++---
 include/uapi/linux/virtio_ring.h | 38 +++++++++++++++++++++++---------
 2 files changed, 31 insertions(+), 13 deletions(-)

```
#### [PATCH 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
##### From: Jared Rossi <jrossi@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jared Rossi <jrossi@linux.ibm.com>
X-Patchwork-Id: 11495897
Return-Path: <SRS0=Q21y=6B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12802912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:27:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E71CF2223C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 17 Apr 2020 18:27:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730775AbgDQS13 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 17 Apr 2020 14:27:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:38406 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730407AbgDQS12 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 17 Apr 2020 14:27:28 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03HI3e5H132186;
        Fri, 17 Apr 2020 14:27:28 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30ffwsba02-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 14:27:28 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 03HI4BFj134177;
        Fri, 17 Apr 2020 14:27:27 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 30ffwsb9yq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 14:27:27 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 03HIQdOs032697;
        Fri, 17 Apr 2020 18:27:26 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma01dal.us.ibm.com with ESMTP id 30b5h7sad2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 17 Apr 2020 18:27:26 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 03HIRQ3E52167122
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 17 Apr 2020 18:27:26 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2F7E7AE05F;
        Fri, 17 Apr 2020 18:27:26 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EB9DCAE064;
        Fri, 17 Apr 2020 18:27:25 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.151.210])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri, 17 Apr 2020 18:27:25 +0000 (GMT)
From: Jared Rossi <jrossi@linux.ibm.com>
To: Eric Farman <farman@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/1] vfio-ccw: Enable transparent CCW IPL from DASD
Date: Fri, 17 Apr 2020 14:29:39 -0400
Message-Id: <20200417182939.11460-2-jrossi@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20200417182939.11460-1-jrossi@linux.ibm.com>
References: <20200417182939.11460-1-jrossi@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-17_08:2020-04-17,2020-04-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 suspectscore=2
 impostorscore=0 phishscore=0 spamscore=0 lowpriorityscore=0
 mlxlogscore=999 clxscore=1015 mlxscore=0 bulkscore=0 priorityscore=1501
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004170136
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove the explicit prefetch check when using vfio-ccw devices.
This check is not needed as all Linux channel programs are intended
to use prefetch and will be executed in the same way regardless.

Signed-off-by: Jared Rossi <jrossi@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c  | 16 ++++------------
 drivers/s390/cio/vfio_ccw_cp.h  |  2 +-
 drivers/s390/cio/vfio_ccw_fsm.c |  6 +++---
 3 files changed, 8 insertions(+), 16 deletions(-)

```
