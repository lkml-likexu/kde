#### [PATCH 1/2] KVM: x86: svm: Pass XSAVES to guest if available on host
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
X-Patchwork-Id: 11161527
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8723A76
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 21:37:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 64D7621D82
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 21:37:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728312AbfIYVhn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 17:37:43 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:38549 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728023AbfIYVhe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 17:37:34 -0400
Received: from localhost ([127.0.0.1] helo=flow.W.breakpoint.cc)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <bigeasy@linutronix.de>)
        id 1iDEyX-0002Dx-3W; Wed, 25 Sep 2019 23:37:29 +0200
From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 x86@kernel.org, Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Subject: [PATCH 1/2] KVM: x86: svm: Pass XSAVES to guest if available on host
Date: Wed, 25 Sep 2019 23:37:20 +0200
Message-Id: <20190925213721.21245-2-bigeasy@linutronix.de>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20190925213721.21245-1-bigeasy@linutronix.de>
References: <20190925213721.21245-1-bigeasy@linutronix.de>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In commit
   55412b2eda2b7 ("kvm: x86: Add kvm_x86_ops hook that enables XSAVES for guest")

XSAVES was enabled on VMX with a few additional tweaks and was always
disabled on SVM. Before ZEN XSAVES was not available so it made no
difference. With Zen it is possible to expose it to the guest if it is
available on the host.
I didn't find anything close to VMX's "VM-Execution Controls" and
exposing this flag based on the CPUID flags cause no harm so far.

Expose the XSAVES flag to the guest if the host supports it.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5] arm64: Add ARM64_WORKAROUND_1319367 for all A57 and A72 versions
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11160453
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7AE241709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 11:19:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5050A21D7C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 11:19:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1569410398;
	bh=VVYteh1fOgKDE1ieg/4QBB7FPFks2gh0ZgUYcIi8wA0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=L57346sxp6VZMrqtbwu2puxNXBmF0G8B7jiq8QdHxvn54hAM9h+cLuFmRp6Ir/CF7
	 /KSXTa67tRw2Zl9SoTEQz1KCLERGzWmKa8A+xAe5pWZ4YIxMYDsLqce4+OWZUUjjdB
	 gfWZ6a+F7ez5t5odoo97Ch+fCqYk5ZJ2JDojna4E=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390918AbfIYLT5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 07:19:57 -0400
Received: from foss.arm.com ([217.140.110.172]:46866 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725913AbfIYLT5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 07:19:57 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id F08381596;
        Wed, 25 Sep 2019 04:19:56 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B7D5D3F694;
        Wed, 25 Sep 2019 04:19:55 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Subject: [PATCH 1/5] arm64: Add ARM64_WORKAROUND_1319367 for all A57 and A72
 versions
Date: Wed, 25 Sep 2019 12:19:37 +0100
Message-Id: <20190925111941.88103-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190925111941.88103-1-maz@kernel.org>
References: <20190925111941.88103-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the EL2 vector hardening that is only selected for A57 and A72
so that the table can also be used for ARM64_WORKAROUND_1319367.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/cpucaps.h |  3 ++-
 arch/arm64/kernel/cpu_errata.c   | 13 ++++++++++---
 2 files changed, 12 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: LAPIC: Loose fluctuation filter for auto tune lapic_timer_advance_ns
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11160041
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D9831709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 05:47:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D3DB321D7B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 05:47:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="H3BMqCM4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2411782AbfIYFrR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 01:47:17 -0400
Received: from mail-pg1-f193.google.com ([209.85.215.193]:36410 "EHLO
        mail-pg1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404442AbfIYFrR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 01:47:17 -0400
Received: by mail-pg1-f193.google.com with SMTP id t14so2147063pgs.3;
        Tue, 24 Sep 2019 22:47:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=Eh8M+3jwlHqT1zqxVtZVbiy9DN02YJpr1pbJ56Y3aJw=;
        b=H3BMqCM4fpx9/r8aQmcQLoZfSDjG38Ori/JsBght9/0VcgPT6fMKJujT46xn536f3S
         gYDai1Q+094xJ6CPTlHxNccR31MfXKpYtdWnTWvoRTpqtYYARX6oXcJIsh+Cdtus/UsZ
         nl7RlKHtVBbiaaP1AejOcflL8rLCwv0Sk8i4Xo0YIiahEgpGgg2rTB528ZIdqTx2mdwM
         a1oCKGAtEIj3MVuINMM5/XAjM9Tnx70juFH6uG8/gw1KM0MzDUDdr54SwhB1/2wmZBiS
         IhfxRV1qSkekwhhOauK9dGD3+08Kn9XcA4dYBUQXenkeU0uXgw5+uiKAtqrUeX4c5iPW
         Qxiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=Eh8M+3jwlHqT1zqxVtZVbiy9DN02YJpr1pbJ56Y3aJw=;
        b=AUneuELG8Tj9rheBa2o9PQi+0JPBb/VbAj6CWw5pLq8tUY92BKLgp0cYFFWirRW+0E
         A9i/uOog3X/B5nNEG5u3ivtO2R2+ikEgiHjwlpYEMC/Tj118xCMvByEzXjvPOXyl+chq
         K367fc+Vh1oR54lBQ4hU+Jeseq2YNqM/TxQS4YPQrN2oJEgalgrH+hSeYnBnGzid3CVN
         I4TB+oEMg4IbUwpD4fDVmxfsOEgWmQAIKZ3IMcnGSAU65gYaMz7LzyMWCZlUPQtc0AeZ
         5EdYA949Dn+MTv81qWepWCqX214dWk8zLTAiBlLcRNsVKbagkjepT7TQraRK62aUZb9Q
         aluA==
X-Gm-Message-State: APjAAAVgzHEXz1gAfJck8ZeqG6V90REFUpu4vQF1rFt9OxdwYgaeDRH2
        z0nqBZ3AhLLB32SsPE+ekd7F9cgt
X-Google-Smtp-Source: 
 APXvYqzal/UUKYK2deJAe8JWlIx0ed7Hs3eIeBRQF4xuySPJ+8IKqG6brcmqHMwlOGPMTnYz61DwVQ==
X-Received: by 2002:a63:e24:: with SMTP id d36mr5060897pgl.143.1569390436340;
        Tue, 24 Sep 2019 22:47:16 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 k4sm1623829pjl.9.2019.09.24.22.47.13
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 24 Sep 2019 22:47:15 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Loose fluctuation filter for auto tune
 lapic_timer_advance_ns
Date: Wed, 25 Sep 2019 13:47:04 +0800
Message-Id: <1569390424-22031-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

5000 guest cycles delta is easy to encounter on desktop, per-vCPU 
lapic_timer_advance_ns always keeps at 1000ns initial value, lets 
loose fluctuation filter a bit to make auto tune can make some 
progress.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: cleanup and fix host 64-bit mode checks
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11161105
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94D961709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:34:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 729CE21D7A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:34:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="smygSNg9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389108AbfIYQev (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 12:34:51 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:33219 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725851AbfIYQeu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 12:34:50 -0400
Received: by mail-wr1-f66.google.com with SMTP id b9so7725985wrs.0;
        Wed, 25 Sep 2019 09:34:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=s+6/bt73F0nPkh+ms30j0ei78DCt1MwVFFVQl9AGl+A=;
        b=smygSNg9FtLOVqPacXXLuBqzZgNquwgf502lQnDrZZV5nuuo1H5s/ex7lbhjMHm7or
         W5f9sP6CfAj+zLQVBgnlN1BNRQ/Yiu10T/wrAw9PtG28Eo1CRYdl+oeO4TROcZzQS2WE
         gwrlNPb6xbDF/I7/AqayB1DVxtgWwm6oW+212q5UpYOTFsHGtpRbSfxhya14GvH7272F
         xF2+lsaLwAtHatm8iRhPM6GjMO0HOy/Lav8cY4AoZlp9nsHLgUnJQE6d3hAwA4UFEoXP
         kHb+O9tMEzdTX6lw0EXzCGtD23AqF+/TwTcoyhi/gSKJqU3FW7uNrqAnrBsso92RRSjy
         L0DQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=s+6/bt73F0nPkh+ms30j0ei78DCt1MwVFFVQl9AGl+A=;
        b=uZmx7b4QFSz0DPhpOGXmau4ueunQ4fmBukYnyHH5Wx0aemMq7K8b147ZLNuGZCGuu1
         PsE7xfmOBrZwtQ7zV2agv6PS39wJ/POvEP2Ouafi3tDFedFe404OY4M4MyXSeQ7mjJkk
         YzflGrgcJzNqYSQjQLKJQnpaRDufAqkCHe7nwQzxcBP3a++T/XBUSmxi4BU3ZdWTZuy7
         8rujjY9fEBkOuRxOdpmOiG5nw4WFUkA8uJ/Sy5M9NehHUyhXRspIgKoPsMN21ko+kJaM
         oAbWMQrKhMJs5wzViUhTA1MNKCA0tLexJg45x26wMBVss/iynnOecTfUFwcR5xqAOv3U
         gA4g==
X-Gm-Message-State: APjAAAVIQ6Ek0N7+KapieCSoO+7xpyCkIQGYKG6jTlr4sdhng1+qFSEN
        mNO4yyNrQvRW7VeOr413qewreHdI
X-Google-Smtp-Source: 
 APXvYqzG9uZ++lfYDbCS8zeD0orJK6Hij8TVimAq9rhTUfa9PhmpSpHL6h6GyA04sZa+N/qoS5hQMw==
X-Received: by 2002:a5d:4f86:: with SMTP id d6mr10247057wru.384.1569429288225;
        Wed, 25 Sep 2019 09:34:48 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b16sm9170000wrh.5.2019.09.25.09.34.47
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 25 Sep 2019 09:34:47 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH] KVM: nVMX: cleanup and fix host 64-bit mode checks
Date: Wed, 25 Sep 2019 18:34:46 +0200
Message-Id: <1569429286-35157-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM was incorrectly checking vmcs12->host_ia32_efer even if the "load
IA32_EFER" exit control was reset.  Also, some checks were not using
the new CC macro for tracing.

Cleanup everything so that the vCPU's 64-bit mode is determined
directly from EFER_LMA and the VMCS checks are based on that, which
matches section 26.2.4 of the SDM.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Fixes: 5845038c111db27902bc220a4f70070fe945871c
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 53 ++++++++++++++++++++---------------------------
 1 file changed, 22 insertions(+), 31 deletions(-)

```
#### [PATCH] KVM: selftests: fix ucall on x86
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11160651
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EC6514ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:12:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6664421655
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:12:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406177AbfIYNMt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 09:12:49 -0400
Received: from mx1.redhat.com ([209.132.183.28]:49858 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405921AbfIYNMs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 09:12:48 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 061A230860DA;
        Wed, 25 Sep 2019 13:12:48 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1FD7E5C1D4;
        Wed, 25 Sep 2019 13:12:43 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Jim Mattson <jmattson@google.com>, Thomas Huth <thuth@redhat.com>,
 Andrew Jones <drjones@redhat.com>, Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] KVM: selftests: fix ucall on x86
Date: Wed, 25 Sep 2019 15:12:42 +0200
Message-Id: <20190925131242.29986-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Wed, 25 Sep 2019 13:12:48 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit e8bb4755eea2("KVM: selftests: Split ucall.c into architecture
specific files") selftests which use ucall on x86 started segfaulting and
apparently it's gcc to blame: it "optimizes" ucall() function throwing away
va_start/va_end part because it thinks the structure is not being used.
Previously, it couldn't do that because the there was also MMIO version and
the decision which particular implementation to use was done at runtime.

With older gccs it's possible to solve the problem by adding 'volatile'
to 'struct ucall' but at least with gcc-8.3 this trick doesn't work.

'memory' clobber seems to do the job.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
s390 should, in theory, have the same problem. Thomas, Cornelia, could
you please take a look? Thanks!
---
 tools/testing/selftests/kvm/lib/x86_64/ucall.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PULL 01/17] s390x: Support PSW restart boot
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11161109
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D44D1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:37:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E0B7C21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:37:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390629AbfIYQh0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 12:37:26 -0400
Received: from mx1.redhat.com ([209.132.183.28]:47622 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389105AbfIYQhZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 12:37:25 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id B2A733091786;
        Wed, 25 Sep 2019 16:37:25 +0000 (UTC)
Received: from thuth.com (ovpn-116-109.ams2.redhat.com [10.36.116.109])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 99E4060BF1;
        Wed, 25 Sep 2019 16:37:22 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, =?utf-8?b?UmFk?=
	=?utf-8?b?aW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>
Subject: [kvm-unit-tests PULL 01/17] s390x: Support PSW restart boot
Date: Wed, 25 Sep 2019 18:36:58 +0200
Message-Id: <20190925163714.27519-2-thuth@redhat.com>
In-Reply-To: <20190925163714.27519-1-thuth@redhat.com>
References: <20190925163714.27519-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.41]);
 Wed, 25 Sep 2019 16:37:25 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Add a boot PSW to PSW restart new, so we can also boot via a PSW
restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Message-Id: <20190826163502.1298-2-frankja@linux.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/flat.lds | 14 +++++++++-----
 1 file changed, 9 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH v7 1/2] x86: nvmx: fix bug in __enter_guest()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11159881
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0632E112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 01:18:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D81B4214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 01:18:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="LwfQYnvK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391004AbfIYBS0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Sep 2019 21:18:26 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:55999 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390869AbfIYBS0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Sep 2019 21:18:26 -0400
Received: by mail-pg1-f202.google.com with SMTP id k18so2464298pgh.22
        for <kvm@vger.kernel.org>; Tue, 24 Sep 2019 18:18:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=G+PDXpZG3j8czW7fuE3YoYmyuQA+E6Wkrr/SlRmWll8=;
        b=LwfQYnvKBnFVa6RdgLaG3dNs3BVIqhmSmhBEPFNZNht/GBAI/oOzIHE3lwd9yveTQR
         FVhY2GLDTse8J2dHJFlWKs3BE8AqhmISHsO24UF4jJ2yI3zlo+ucaBb7fX3/WgVtcOJM
         uGCMazcpNGRM0lKRchlIY1T8n3zM5evMwH36WJwzyuupfsQiR68Zq8fRfxu5GPnX5UE1
         ZvmJ47H3NxcyD6ChOq5McK7IAC5wV4VYSlxA7EmvDRsEfCO6FPPweOKICqZzpUhFtn7D
         jYpNYTW11Zzsk4dBQdizRokAb22NmRRNPhtFacP+FbFSHtgPI+cXXbKwZ5lnwsB/sXmH
         Ugsg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=G+PDXpZG3j8czW7fuE3YoYmyuQA+E6Wkrr/SlRmWll8=;
        b=TqOKOSV1CX2CaW1d4EZgWYOv7qqx3AzHL/jKGkMYil8KXed+Q3AvBUm6ODEr5l2RkB
         uLttdrsEmcpT59zn+UN0wB8swuLr3n22mmGLv1HIYxvnqLaWfl32hYND6Xt5V2oDxqat
         nBdoimcNA4m5nfmKciCSnjAV57E2gaX3+kq99p55zhtSaFehCjIEeXJAcmhsjg2KQUBr
         j17FgkfIHPtGKJ55yCcRdrZAUoItIfqy4ENlNrkhgngwrRbm3JydTfX4v0xWzb1Uv1ow
         awWlTiCkf72wIrHNbHmZF50Z6uzLX3pYMbAgIba+VX2wJx4Mic4S/BUBJedwonbgZviY
         yfLw==
X-Gm-Message-State: APjAAAVexLOiyAKd8W5hF4rh8Tl4RUN66MvbhF7CZGXOBNGpd+jatYLR
        AaC0pH0MgsutcQ4kuizVuQxGenw7KM2y7NNidshh6a5FLhC9M1hGRxQD6JN/3q2EPj61yrx4sd6
        ZkprxFQN/4aec6FgzRsWRdJ9DImR20+wL8IlwzaYCj9hUEisUsgCkc/ZG9rz9
X-Google-Smtp-Source: 
 APXvYqwbddeU/C4Il3t9efyQP67aQJdyo77z9C9M7F86uv2+Kn7SDtl5FFQbx3W9tZuKfkNmE9PSvmFMfhlY
X-Received: by 2002:a65:628f:: with SMTP id f15mr6218457pgv.215.1569374305517;
 Tue, 24 Sep 2019 18:18:25 -0700 (PDT)
Date: Tue, 24 Sep 2019 18:18:20 -0700
Message-Id: <20190925011821.24523-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.444.g18eeb5a265-goog
Subject: [kvm-unit-tests PATCH v7 1/2] x86: nvmx: fix bug in __enter_guest()
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com, krish.sadhukhan@oracle.com,
        pbonzini@redhat.com, rkrcmar@redhat.com, dinechin@redhat.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__enter_guest() should only set the launched flag when a launch has
succeeded. Thus, don't set the launched flag when the VMX_ENTRY_FAILURE,
bit 31, is set in the VMCS exit reason.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Marc Orr <marcorr@google.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: vmx: fix a build warning in hv_enable_direct_tlbflush() on i386
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11160207
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 62B44112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 08:53:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 40AF921D80
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 08:53:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731870AbfIYIxq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 04:53:46 -0400
Received: from mx1.redhat.com ([209.132.183.28]:40292 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2387915AbfIYIxI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 04:53:08 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 226B010CC201;
        Wed, 25 Sep 2019 08:53:08 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6211C1001B08;
        Wed, 25 Sep 2019 08:53:06 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Jim Mattson <jmattson@google.com>, Tianyu Lan <Tianyu.Lan@microsoft.com>
Subject: [PATCH] KVM: vmx: fix a build warning in hv_enable_direct_tlbflush()
 on i386
Date: Wed, 25 Sep 2019 10:53:04 +0200
Message-Id: <20190925085304.24104-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.65]);
 Wed, 25 Sep 2019 08:53:08 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following was reported on i386:

  arch/x86/kvm/vmx/vmx.c: In function 'hv_enable_direct_tlbflush':
  arch/x86/kvm/vmx/vmx.c:503:10: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]

The particular pr_debug() causing it is more or less useless, let's just
remove it. Also, simplify the condition a little bit.

Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 ++++------
 1 file changed, 4 insertions(+), 6 deletions(-)

```
#### [PATCH] kvm: x86: Fix a spurious -E2BIG in __do_cpuid_funcFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11161197
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9469F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 18:17:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 73B8821D7A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 18:17:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FA5uQ8Sg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408531AbfIYSRZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 14:17:25 -0400
Received: from mail-pg1-f201.google.com ([209.85.215.201]:35916 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2408520AbfIYSRZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 14:17:25 -0400
Received: by mail-pg1-f201.google.com with SMTP id h36so284574pgb.3
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 11:17:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=SyIb+l6pQGF3TyBgzUjcF2mQipF7L2LaiCzGb8rB5Aw=;
        b=FA5uQ8Sg5EGdUz9kmzCTzZLwXWJQct8nVaYWVQFIlVIJ9T4jSoxgJLMK6e/EsJhfcU
         GF17PMNBNZdypDUxDjBPh1ube6c44x9WHDDv7jFdx4ZHRIPLw0QK7nUA9/AHHpzgsxXm
         xciHcx2U0fmzDq1HGt8CWC/j/s/upgNVmZ9wWCvu8RgZYNVrWTx055rQZJbke+PtPaAH
         VUzEHQ2XHX73sqO4aTG+S/8EZvqpbYGVgNloCp3onAWN+zPPxj4j7iN/QxZxzj7Csk3i
         z3/WD6nJ1Hg+CVv/4F3Qw1ljbruaKfGWFRKU3VrItgC+lg2flirIHgP/GdX/9NAPnm38
         qC8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=SyIb+l6pQGF3TyBgzUjcF2mQipF7L2LaiCzGb8rB5Aw=;
        b=KsMdEYddDOtwuq75zNnfSsFlKBWXhAbbhnJ6gpA0ybe/tnZbklhNlPgi51NRp0hrxq
         Ihpp+p6DhXQHkHw9jS4CoH6710Vb5CKK/6QpgDcjSFNSqXniU9LxjlglGhXt7XtPNwEW
         jEBcLxCCYmYOY/CBQdGWN36ur1zMPL1v9xnzdF1udcAI/23q9VOGGIEoG9Tq9xiqrraF
         DSwDM1DtjkFXu5Hsr+iwNCJ6h+S1MKYNW5kIV2lF6caGB8WGpfMZl8JCuom039+UzrU8
         t6Nqkn568JBGQ5oGwt1s4COfLWy07bg8FqmIXlB76UVZ7q+LXGNVapJgc+X01PaWeJh3
         7fFA==
X-Gm-Message-State: APjAAAWgzo21O5C03u6Yyv9SGDHnq/pF9Q0EBF5s9W7Zp8ow5c7rp9II
        UKkTW+SOxxjtEeMbTNdUcOszgzJE9Cgg4BV/VlOWpfuVuST4S8EenMuAwkrQc6a1a9bbxkRbwOm
        P2KwPmthJXoJPqrZysUBmjS7scQngiLbyXCqD+IoSiN1p6AnSTqr5p9w5U1BeE5g=
X-Google-Smtp-Source: 
 APXvYqzSsNtFCy3OhX0L6neA3KUUrNJUSqy6n0WIUCe68IEbtZ2iHW9rBPgtZV49tk0GqvzqWUnVmQMKAWFM3g==
X-Received: by 2002:a63:fc60:: with SMTP id r32mr697346pgk.160.1569435443997;
 Wed, 25 Sep 2019 11:17:23 -0700 (PDT)
Date: Wed, 25 Sep 2019 11:17:14 -0700
Message-Id: <20190925181714.176229-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [PATCH] kvm: x86: Fix a spurious -E2BIG in __do_cpuid_func
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't return -E2BIG from __do_cpuid_func when processing function 0BH
or 1FH and the last interesting subleaf occupies the last allocated
entry in the result array.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Fixes: 831bf664e9c1fc ("KVM: Refactor and simplify kvm_dev_ioctl_get_supported_cpuid")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c | 16 ++++++++++------
 1 file changed, 10 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] s390x: Add missing include in smp.h
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11160755
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9DFE314ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:56:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 85DEF21D7B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:56:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406878AbfIYN4g (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 09:56:36 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15302 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2406357AbfIYN4g (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Sep 2019 09:56:36 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8PDq2HA096474
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:56:34 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v88prtevk-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:56:34 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 25 Sep 2019 14:56:32 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 25 Sep 2019 14:56:30 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8PDuT1j31850608
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 25 Sep 2019 13:56:29 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 84454A405B;
        Wed, 25 Sep 2019 13:56:29 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DBC47A4062;
        Wed, 25 Sep 2019 13:56:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 25 Sep 2019 13:56:28 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 1/2] s390x: Add missing include in smp.h
Date: Wed, 25 Sep 2019 09:56:22 -0400
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190925135623.9740-1-frankja@linux.ibm.com>
References: <20190925135623.9740-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19092513-0016-0000-0000-000002B07C20
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092513-0017-0000-0000-000033114487
Message-Id: <20190925135623.9740-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-25_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=962 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909250140
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

smp.h uses struct lowcore and struct psw, which are defined in
asm/arch_def.h

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/smp.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH kvm-unit-tests 1/4] x86: vmx_tests: gate load guest PAT tests on the correct bit
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11161051
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C9EE514E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A8BD721D7B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 16:14:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Qdf8fwgk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2501928AbfIYQOc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 12:14:32 -0400
Received: from mail-wr1-f65.google.com ([209.85.221.65]:37591 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2501893AbfIYQOc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 12:14:32 -0400
Received: by mail-wr1-f65.google.com with SMTP id i1so7653719wro.4
        for <kvm@vger.kernel.org>; Wed, 25 Sep 2019 09:14:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=ejqQNMoRRAMOPTMnBY73/g20YxH+Gw85E8gBw9N3Y/k=;
        b=Qdf8fwgkYSPaShtkJqD6ILUQxwqOpCYK4A2U8aOftt9Ih9SkTbAU9D8kLgZoxHlL/0
         uk38TiQbn7RFI2gjb3Ifjy7gSZWjLDOyhaMCCUei1AlG0zmiQ6s/grhngk+C0QL21nHc
         lxSKZZeIMrafx3jW80uHYjXpS/769AsIDiMiKz5fycVGM4W4x6M70fnW5MH3ZIHjjwDO
         TcGk4+FDQa3ugJTy4eY3p6WXCRFbIBZ7UQW3/zPw3E+s1FjT04Dx91MOIqLN31xYcHIS
         +EmRp889M9008Y6UpL2HLJszpo88fWsTY9Ymk8IFLUR6O9rMJ7kGqz3MiO1a39A8DyTu
         h3ew==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=ejqQNMoRRAMOPTMnBY73/g20YxH+Gw85E8gBw9N3Y/k=;
        b=MWWl3bzAd2k6XZVynG3372h9EElxpY8cBqlhrjlrQRzKbJ6V4fjzV9Hhbh3kPoVq+S
         BS4HSmIq8G5hEUYoZtdsJzd6XFlB1nuBoA5ZJWXw3wGpLJjb8oB9h9fptTNXAo5h2dL/
         Z+SoFNXpE4d6fKB3vBs6/bkwxtgjDbMl93YjQBZVCc+2PHZ7GORZSKfScOiin5m/y2j+
         tE1jxtR/coMYcTwmd6Jb2ep96zpvqFvZCCbcVrC0BmC+VOBYurwdDUfvBJZa93Uw1j80
         AnqtZR/9A42NimmKxuuyvBsfNn/8TTomONKqSG9X8k2TkblkkGL2mgCAjGGouSLez48+
         6X9A==
X-Gm-Message-State: APjAAAXwnoH/D8gYWD5y8qlYzHqLnn6SUOFsuJXkyIdOqL5XHJzyJtbG
        BndD2hL4Sy2NAy5wsR9bkHmAziqb
X-Google-Smtp-Source: 
 APXvYqxGj5IuJFuiyT6keGWjixZfn2OZQZkQWiK5IokWpuBRZoGCMvd26pnI7BaZNF8Os5avfyf9Jg==
X-Received: by 2002:a05:6000:10c2:: with SMTP id
 b2mr9765331wrx.45.1569428069719;
        Wed, 25 Sep 2019 09:14:29 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 a71sm4055293wme.11.2019.09.25.09.14.28
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 25 Sep 2019 09:14:28 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH kvm-unit-tests 1/4] x86: vmx_tests: gate load guest PAT tests
 on the correct bit
Date: Wed, 25 Sep 2019 18:14:23 +0200
Message-Id: <1569428066-27894-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1569428066-27894-1-git-send-email-pbonzini@redhat.com>
References: <1569428066-27894-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The tests should check the "load PAT" entry control,
not the exit control.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: vmx: fix build warnings in hv_enable_direct_tlbflush() on i386
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11160685
Return-Path: <SRS0=acwS=XU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB7611599
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:30:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B39622146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Sep 2019 13:30:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406516AbfIYNaj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Sep 2019 09:30:39 -0400
Received: from mx1.redhat.com ([209.132.183.28]:19954 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2406503AbfIYNai (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Sep 2019 09:30:38 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7747710C051A;
        Wed, 25 Sep 2019 13:30:38 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CA9E81001B00;
        Wed, 25 Sep 2019 13:30:36 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Jim Mattson <jmattson@google.com>, Tianyu Lan <Tianyu.Lan@microsoft.com>
Subject: [PATCH v2] KVM: vmx: fix build warnings in
 hv_enable_direct_tlbflush() on i386
Date: Wed, 25 Sep 2019 15:30:35 +0200
Message-Id: <20190925133035.7576-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.65]);
 Wed, 25 Sep 2019 13:30:38 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following was reported on i386:

  arch/x86/kvm/vmx/vmx.c: In function 'hv_enable_direct_tlbflush':
  arch/x86/kvm/vmx/vmx.c:503:10: warning: cast from pointer to integer of different size [-Wpointer-to-int-cast]

pr_debugs() in this function are  more or less useless, let's just
remove them. evmcs->hv_vm_id can use 'unsigned long' instead of 'u64'.

Also, simplify the code a little bit.

Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 14 +++++---------
 1 file changed, 5 insertions(+), 9 deletions(-)

```
