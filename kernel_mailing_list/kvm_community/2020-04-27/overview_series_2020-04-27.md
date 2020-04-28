#### [PATCH v4 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11511115
Return-Path: <SRS0=SmUC=6L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 526A71392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 04:35:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4087721D94
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 04:35:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726516AbgD0EfY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 00:35:24 -0400
Received: from out30-133.freemail.mail.aliyun.com ([115.124.30.133]:60589
 "EHLO
        out30-133.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726350AbgD0EfX (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Apr 2020 00:35:23 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R911e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01419;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=38;SR=0;TI=SMTPD_---0TwkAhX3_1587962115;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TwkAhX3_1587962115)
          by smtp.aliyun-inc.com(127.0.0.1);
          Mon, 27 Apr 2020 12:35:15 +0800
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
        christoffer.dall@arm.com, peterx@redhat.com, thuth@redhat.com,
        chenhuacai@gmail.com
Cc: kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-mips@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        tianjia.zhang@linux.alibaba.com
Subject: [PATCH v4 1/7] KVM: s390: clean up redundant 'kvm_run' parameters
Date: Mon, 27 Apr 2020 12:35:08 +0800
Message-Id: <20200427043514.16144-2-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200427043514.16144-1-tianjia.zhang@linux.alibaba.com>
References: <20200427043514.16144-1-tianjia.zhang@linux.alibaba.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. For historical reasons, many kvm-related function parameters
retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time. This
patch does a unified cleanup of these remaining redundant parameters.

Signed-off-by: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
---
 arch/s390/kvm/kvm-s390.c | 23 +++++++++++++++--------
 1 file changed, 15 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: arm64: Make KVM_CAP_MAX_VCPUS compatible with the selected GIC version
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11512311
Return-Path: <SRS0=SmUC=6L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9196C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 79BF9206B9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:15:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587996927;
	bh=f3vNbHktBCG4AIFM+J82uH7K2+5LPw+EtC296Bu7NO0=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=tYO6RvY4P3jP1Oz6WQzVVcDC6dPwxqqMs6wx1lUE38gXeyP3NmzEBka07U7ktaD4i
	 aqh3XJnbgrT28c/0UO/PXfKAdzxSgvK+iPIDnFTszAMmc0LXl7bFvJolQfyhsJmNak
	 SMo5xbIvgQ0Nbjp0z1hp4IFLLGNkKqFomWRs7YRs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727817AbgD0OP0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 10:15:26 -0400
Received: from mail.kernel.org ([198.145.29.99]:43098 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726651AbgD0OP0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 10:15:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 81C80206B6;
        Mon, 27 Apr 2020 14:15:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587996925;
        bh=f3vNbHktBCG4AIFM+J82uH7K2+5LPw+EtC296Bu7NO0=;
        h=From:To:Cc:Subject:Date:From;
        b=Z/9qBzOa7bnNJb/C7CIh3o/YKWthaFBmAhRQGNXDUjhmjzuX8ZNXzLGvEXi/+VJHr
         ofw+c6RwQa0n1TGST9hROO4SS6UMkI/ZszR8RcTaZIpHuY8FO8MdYnoy+4To4WZLi7
         jQ+Lk+a609ihrGU1sX04c/rNqhwAMT/xOiBE6eAU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jT4Xb-006kbg-O7; Mon, 27 Apr 2020 15:15:23 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Ard Biesheuvel <ardb@kernel.org>
Subject: [PATCH] KVM: arm64: Make KVM_CAP_MAX_VCPUS compatible with the
 selected GIC version
Date: Mon, 27 Apr 2020 15:15:07 +0100
Message-Id: <20200427141507.284985-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ardb@kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_CAP_MAX_VCPUS always return the maximum possible number of
VCPUs, irrespective of the selected interrupt controller. This
is pretty misleading for userspace that selects a GICv2 on a GICv3
system that supports v2 compat: It always gets a maximum of 512
VCPUs, even if the effective limit is 8. The 9th VCPU will fail
to be created, which is unexpected as far as userspace is concerned.

Fortunately, we already have the right information stashed in the
kvm structure, and we can return it as requested.

Reported-by: Ard Biesheuvel <ardb@kernel.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/arm.c | 15 ++++++++++-----
 1 file changed, 10 insertions(+), 5 deletions(-)

```
#### [PATCH][kvmtool] kvm: Request VM specific limits instead of system-wide ones
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11512315
Return-Path: <SRS0=SmUC=6L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6050392A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:17:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44329206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:17:52 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587997072;
	bh=CSSnDMC5PzLW9Ty/t6vNkRAXv5DRYOcczqebb1dCB8w=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=i7Z7E6ZtrUyHJSYVekxy2AZCfXB61Azqf4OnZuip3OFZdyBsq/iavXw/kg6unn4DV
	 5m+ZCFHECNM4LEG71LRsu0uwZX1YAFbQihqNP/U8tzcP51uy/WYCDdNNN/Yi546hpD
	 ps1VuXWbEDjX/Ahpu/iIq1ea1sm49fr/jxh/XL+k=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727943AbgD0ORv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 10:17:51 -0400
Received: from mail.kernel.org ([198.145.29.99]:44442 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726651AbgD0ORv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 10:17:51 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 63460206B6;
        Mon, 27 Apr 2020 14:17:50 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587997070;
        bh=CSSnDMC5PzLW9Ty/t6vNkRAXv5DRYOcczqebb1dCB8w=;
        h=From:To:Cc:Subject:Date:From;
        b=pzItXPTziBM5cfmNXO7kDO4LK36WFULj6A7TjQQnL4oRHAcho6MAGywU/VzBc2dPh
         4FQeR5lP2RXyYOKWneuAeGRzQaBrFaATmt9Eun8Qbn6OX0fADcX3ZpLeJbi9UEMRNu
         70GmJmp62lCh+0GfHqpNab9UNF1d11/vl78T4whA=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jT4Zw-006kdf-Qq; Mon, 27 Apr 2020 15:17:48 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Andre Przywara <Andre.Przywara@arm.com>,
        Ard Biesheuvel <ardb@kernel.org>
Subject: [PATCH][kvmtool] kvm: Request VM specific limits instead of
 system-wide ones
Date: Mon, 27 Apr 2020 15:17:38 +0100
Message-Id: <20200427141738.285217-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 will@kernel.org, Andre.Przywara@arm.com, ardb@kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On arm64, the maximum number of vcpus is constrained by the type
of interrupt controller that has been selected (GICv2 imposes a
limit of 8 vcpus, while GICv3 currently has a limit of 512).

It is thus important to request this limit on the VM file descriptor
rather than on the one that corresponds to /dev/kvm, as the latter
is likely to return something that doesn't take the constraints into
account.

Reported-by: Ard Biesheuvel <ardb@kernel.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 kvm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RESEND PATCH] KVM: x86/pmu: Support full width counting
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11511331
Return-Path: <SRS0=SmUC=6L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 038C1912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 07:23:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E418C208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 07:22:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726719AbgD0HW4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 03:22:56 -0400
Received: from mga18.intel.com ([134.134.136.126]:21447 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726407AbgD0HW4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 27 Apr 2020 03:22:56 -0400
IronPort-SDR: 
 8Bdx+mITLVhmosy5c8Omz2S1GbTtMh0YB04ow1/9x63F2YSUQWcx2/f2wzDpypTuzW0mQMcODa
 FMNwLRYaBdPQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 Apr 2020 00:22:55 -0700
IronPort-SDR: 
 /n3zHjQ+Pv2v1hw++y3auFQ6d6e26xnf/XjpUBfomwRrThcUCOblFbFkM6jCOmKvP1TnAzg0xo
 +WxG+ihL7QjQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,323,1583222400";
   d="scan'208";a="458717516"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 27 Apr 2020 00:22:53 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [RESEND PATCH] KVM: x86/pmu: Support full width counting
Date: Mon, 27 Apr 2020 15:19:22 +0800
Message-Id: <20200427071922.86257-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jim & Sean,

Do you mind helping review this little feature for vPMU?

The related specification in the Intel SDM is "18.2.6 Full-Width Writes to
Performance Counter Registers" and related kernel commit is 069e0c3c40581.

If there is anything needs to be improved, please let me know. 

Thanks,
Like Xu

----

Intel CPUs have a new alternative MSR range (starting from MSR_IA32_PMC0)
for GP counters that allows writing the full counter width. Enable this
range from a new capability bit (IA32_PERF_CAPABILITIES.FW_WRITE[bit 13]).

The guest would query CPUID to get the counter width, and sign extends
the counter values as needed. The traditional MSRs always limit to 32bit,
even though the counter internally is larger (usually 48 bits).

When the new capability is set, use the alternative range which do not
have these restrictions. This lowers the overhead of perf stat slightly
because it has to do less interrupts to accumulate the counter value.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx/capabilities.h | 15 +++++++++++++++
 arch/x86/kvm/vmx/pmu_intel.c    | 32 ++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.c          |  2 ++
 arch/x86/kvm/x86.c              |  8 ++++++++
 5 files changed, 54 insertions(+), 4 deletions(-)

```
#### [RFC PATCH 1/5] refcount, kref: add dec-and-test wrappers for rw_semaphores
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11512329
Return-Path: <SRS0=SmUC=6L=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7245A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:18:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A1D7206BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 27 Apr 2020 14:18:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Xg7rSLly"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727977AbgD0OSk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 27 Apr 2020 10:18:40 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:33916 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727898AbgD0OSi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 27 Apr 2020 10:18:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1587997116;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=rZxH84mqOgKUCIrltch+dX9fSv+/5ZQHenb5aSxFeqI=;
        b=Xg7rSLlyFYnXSg/aTrHwztLBD0X4ikGOFi4rYP8umxCoXr/ftO2uGRAJePrFjHNrQrgNTQ
        NLTBEm+RrVVkUnb3jnGIh2hi8nonLL60RvzYHM6OAnKIKhvp6AReQ7SlVszgNk/lIZZJeZ
        44IjryV4xXaDUg6oR+fiMVWy3WoNlgA=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-287-6BeQEZjOPkCbEoISM84jaw-1; Mon, 27 Apr 2020 10:18:27 -0400
X-MC-Unique: 6BeQEZjOPkCbEoISM84jaw-1
Received: by mail-wm1-f72.google.com with SMTP id j5so7214418wmi.4
        for <kvm@vger.kernel.org>; Mon, 27 Apr 2020 07:18:27 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=rZxH84mqOgKUCIrltch+dX9fSv+/5ZQHenb5aSxFeqI=;
        b=K+yIiELlulw4EWwH47N+qUbH1dOlT9JKM5JCTDE8IFjDeOTBHdWVcWTnbCr7aJfoYq
         G5uQ/COF5F/BzoIH9a9OZtRh1TcVtd2m3E3L3NyWmymw1vWJNa/E+ptrGa/7PkVd2vvM
         OsjK+/9AGDoU40vegWsmLdWb4WoSIc2tQgXaRRNza/1zSzpCvUCkyYVDSjk72KgH8/4+
         bwlcmNRsN7D1CMNEnuUFBzv+UggMJJFnkKTg3mYnNjsp4MyfxrPp9klBUBm3jxEjYzAB
         mHfBggZM9pFf20AcOU8rNFdWWEihngPIOeiMpBBXl0yM8Fdr3N/AGdNI3nFgkjhW+hte
         qAkA==
X-Gm-Message-State: AGi0PuametpJXMzQ+k4pW36nongFZ0T9ozHECfvRLLOWUp9dcB1oxsS/
        A7iSdsdikl+wFusUjAirKEYOTQ9jn35qLRlyVgVE6rx/GP6cKDaKh41PCKrpy9IV0TrMbTG6/EG
        P4Hxh7BCyXko+
X-Received: by 2002:a5d:5229:: with SMTP id i9mr20226226wra.369.1587997105764;
        Mon, 27 Apr 2020 07:18:25 -0700 (PDT)
X-Google-Smtp-Source: 
 APiQypJ2mzAfAvgNc5tkRv8j6wCds01EzaWcBsdB1ns7Ni6rVvdogJtNeYjoRzA+wfMM26qrttwXeQ==
X-Received: by 2002:a5d:5229:: with SMTP id i9mr20226201wra.369.1587997105578;
        Mon, 27 Apr 2020 07:18:25 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.207])
        by smtp.gmail.com with ESMTPSA id
 1sm15914570wmz.13.2020.04.27.07.18.24
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 27 Apr 2020 07:18:24 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org, mst@redhat.com,
        borntraeger@de.ibm.com, Paolo Bonzini <pbonzini@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [RFC PATCH 1/5] refcount,
 kref: add dec-and-test wrappers for rw_semaphores
Date: Mon, 27 Apr 2020 16:18:12 +0200
Message-Id: <20200427141816.16703-2-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.2
In-Reply-To: <20200427141816.16703-1-eesposit@redhat.com>
References: <20200427141816.16703-1-eesposit@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similar to the existing functions that take a mutex or spinlock if and
only if a reference count is decremented to zero, these new function
take an rwsem for writing just before the refcount reaches 0 (and
call a user-provided function in the case of kref_put_rwsem).

These will be used for statsfs_source data structures, which are
protected by an rw_semaphore to allow concurrent sysfs reads.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 include/linux/kref.h     | 11 +++++++++++
 include/linux/refcount.h |  2 ++
 lib/refcount.c           | 32 ++++++++++++++++++++++++++++++++
 3 files changed, 45 insertions(+)

```
