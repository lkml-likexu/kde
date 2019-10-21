#### [PATCH 1/4] KVM: arm64: pmu: Fix cycle counter truncation
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11200869
Return-Path: <SRS0=kKt7=YN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BEFF614ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C1BF222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:39 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1571566299;
	bh=V53P7Vn0aPiKYwrOMap7wcByveXMeM32VmJKA4bI76s=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=TEsBLYMsyZJmHytVvWlx5a4Rr8qGIaz7kLKqfp/UdiI3nGqaNcbMsDCHDJbjIkk15
	 aJizWVHtvQNR/boNPzW4ref/B/YHEJ799eFMnj36vAUOBPx5Ckn6j/j2fT9so2bTKO
	 nU0xkLprK3SZ1U2lQkeaSWShMCAI0E7h3idV2ocA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726179AbfJTKLj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 06:11:39 -0400
Received: from mail.kernel.org ([198.145.29.99]:55342 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725893AbfJTKLi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 06:11:38 -0400
Received: from big-swifty.lan (78.163-31-62.static.virginmediabusiness.co.uk
 [62.31.163.78])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6929D222BD;
        Sun, 20 Oct 2019 10:11:35 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1571566297;
        bh=V53P7Vn0aPiKYwrOMap7wcByveXMeM32VmJKA4bI76s=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=peYUqeE2CB2w33fmbugervLQNX+GX31Uh5sbOoiIy1LVvBeTnM0OewPJuZ2QHh4fk
         +p8U85CFm+SrKBF+MQhBhnaWCIHAxHNbgKhplRjH8mHeC3qn+Ke5Lvgat8eFVrafJZ
         LGMMdfb/RiiK/jb3OMUP3kjM9ATxDcgxa6oOk1bA=
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Andrew Murray <andrew.murray@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 1/4] KVM: arm64: pmu: Fix cycle counter truncation
Date: Sun, 20 Oct 2019 11:11:26 +0100
Message-Id: <20191020101129.2612-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191020101129.2612-1-maz@kernel.org>
References: <20191020101129.2612-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a counter is disabled, its value is sampled before the event
is being disabled, and the value written back in the shadow register.

In that process, the value gets truncated to 32bit, which is adequate
for any counter but the cycle counter (defined as a 64bit counter).

This obviously results in a corrupted counter, and things like
"perf record -e cycles" not working at all when run in a guest...
A similar, but less critical bug exists in kvm_pmu_get_counter_value.

Make the truncation conditional on the counter not being the cycle
counter, which results in a minor code reorganisation.

Fixes: 80f393a23be6 ("KVM: arm/arm64: Support chained PMU counters")
Reviewed-by: Andrew Murray <andrew.murray@arm.com>
Reported-by: Julien Thierry <julien.thierry.kdev@gmail.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/pmu.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
#### [GIT PULL] KVM/arm fixes for 5.4-rc5
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11200867
Return-Path: <SRS0=kKt7=YN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F6AB139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0747F222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:36 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1571566297;
	bh=R9nxM6A3Yhddcl9A7C/26LLhq+KqjO+NyOwb1yqAA94=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=LAGGwOf4eIcNeXqUdP4+RI4LtnteQwdV+CkvpjRHta8TnTfUn/IibYRsLbpV+5b0Z
	 KTsM107Owpm3pQ08Umqm7xaQD1fFLWJHRC7DCEhaLpD0VM23fqbhO5F+FMjJsO5GZH
	 p8Ict+us70JuukcN5mZqkWd1IfUh3Vn+3n0DLHR8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726019AbfJTKLf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 06:11:35 -0400
Received: from mail.kernel.org ([198.145.29.99]:55320 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725893AbfJTKLf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 06:11:35 -0400
Received: from big-swifty.lan (78.163-31-62.static.virginmediabusiness.co.uk
 [62.31.163.78])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 89A342190F;
        Sun, 20 Oct 2019 10:11:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1571566294;
        bh=R9nxM6A3Yhddcl9A7C/26LLhq+KqjO+NyOwb1yqAA94=;
        h=From:To:Cc:Subject:Date:From;
        b=wZl1P5TR+YzkoKz8Z0Krfdf4skT5kHoKhxSmiYkJoZu/u3uDDGVRFMn0t4GTos/u9
         +masS9rK4tdB5WNUk7ko/gKMJTmaJTpuqTCTETNz91MjZ+XPLk1mF3T/760PDMMKB5
         cAFy5HjwCjjvImUIHXutqDnA9xTObx4YpNbz5uQk=
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Andrew Murray <andrew.murray@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM/arm fixes for 5.4-rc5
Date: Sun, 20 Oct 2019 11:11:25 +0100
Message-Id: <20191020101129.2612-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo, Radim,

Here's the latest (and hopefully last) set of KVM/arm fixes for
5.4. 4 patches exclusively covering our PMU emulation, which exhibited
several different flavours of brokenness.

Please pull,

	M.

The following changes since commit da0c9ea146cbe92b832f1b0f694840ea8eb33cce:

  Linux 5.4-rc2 (2019-10-06 14:27:30 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.4-2

for you to fetch changes up to 8c3252c06516eac22c4f8e2506122171abedcc09:

  KVM: arm64: pmu: Reset sample period on overflow handling (2019-10-20 10:47:07 +0100)

----------------------------------------------------------------
KVM/arm fixes for 5.4, take #2

Special PMU edition:

- Fix cycle counter truncation
- Fix cycle counter overflow limit on pure 64bit system
- Allow chained events to be actually functional
- Correct sample period after overflow

----------------------------------------------------------------
Marc Zyngier (4):
      KVM: arm64: pmu: Fix cycle counter truncation
      arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
      KVM: arm64: pmu: Set the CHAINED attribute before creating the in-kernel event
      KVM: arm64: pmu: Reset sample period on overflow handling

 arch/arm64/kvm/sys_regs.c |  4 ++++
 virt/kvm/arm/pmu.c        | 48 ++++++++++++++++++++++++++++++++++-------------
 2 files changed, 39 insertions(+), 13 deletions(-)

From patchwork Sun Oct 20 10:11:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11200871
Return-Path: <SRS0=kKt7=YN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6FC0014ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 434DB222D2
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 10:11:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1571566302;
	bh=azhX068/Llc0POTSFJ7hQa0blYq+N0fFcX/ZEjAr9sY=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=IqjatqmEhRH1ZieQNJHw2XNyoP0bx/eGnBNiNX8FhMXVqZq0Hhv6DlqVVX81y+M4n
	 GQn01IZzSMTB4VHF0fLxsUr7npdfzTPL8fnwsNLHwxA383FjflTJuQXOojbK0fL3+8
	 FYtkn4xYFCDGfUqZfLfwJP1lUpG2gMmJhJEMuWK8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726258AbfJTKLl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 06:11:41 -0400
Received: from mail.kernel.org ([198.145.29.99]:55366 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726212AbfJTKLl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 06:11:41 -0400
Received: from big-swifty.lan (78.163-31-62.static.virginmediabusiness.co.uk
 [62.31.163.78])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 481CB2190F;
        Sun, 20 Oct 2019 10:11:38 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1571566300;
        bh=azhX068/Llc0POTSFJ7hQa0blYq+N0fFcX/ZEjAr9sY=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=HCve6BGyoxxbhjwhXItirYvlpIK6Wp1TyfF5jyy3UCbpT9/+nOdAlaLZ8zMu0/aGb
         +aHMhQ0zj322GshIh/8gAma86d6kBcqUpIDuYVv/wsJdlMH59V/Xzt98xRKBr8bA3h
         JTE9WtuBVDzyPNYwjmo36ejQ9cKJGhNXKg9pR9hw=
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Andrew Murray <andrew.murray@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/4] arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64
 systems
Date: Sun, 20 Oct 2019 11:11:27 +0100
Message-Id: <20191020101129.2612-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191020101129.2612-1-maz@kernel.org>
References: <20191020101129.2612-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Of PMCR_EL0.LC, the ARMv8 ARM says:

	"In an AArch64 only implementation, this field is RES 1."

So be it.

Fixes: ab9468340d2bc ("arm64: KVM: Add access handler for PMCR register")
Reviewed-by: Andrew Murray <andrew.murray@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v3 2/4] KVM: VMX: Remove vmx->hv_deadline_tsc initialization from vmx_vcpu_setup()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11200663
Return-Path: <SRS0=kKt7=YN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 947F7139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 09:26:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7C6472064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 09:26:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726307AbfJTJ0J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 05:26:09 -0400
Received: from mga12.intel.com ([192.55.52.136]:39083 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726298AbfJTJ0J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 05:26:09 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Oct 2019 02:26:08 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,319,1566889200";
   d="scan'208";a="348494036"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by orsmga004.jf.intel.com with ESMTP; 20 Oct 2019 02:26:06 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v3 2/4] KVM: VMX: Remove vmx->hv_deadline_tsc initialization
 from vmx_vcpu_setup()
Date: Sun, 20 Oct 2019 17:10:59 +0800
Message-Id: <20191020091101.125516-3-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20191020091101.125516-1-xiaoyao.li@intel.com>
References: <20191020091101.125516-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

... It can be removed here because the same code is called later in
vmx_vcpu_reset() as the flow:

kvm_arch_vcpu_setup()
	-> kvm_vcpu_reset()
		-> vmx_vcpu_reset()

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v3 1/4] KVM: VMX: Write VPID to vmcs when creating vcpu
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11200657
Return-Path: <SRS0=kKt7=YN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 549D51575
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 09:26:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 330522064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 20 Oct 2019 09:26:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726263AbfJTJ0H (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 05:26:07 -0400
Received: from mga12.intel.com ([192.55.52.136]:39083 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725893AbfJTJ0G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 05:26:06 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Oct 2019 02:26:06 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,319,1566889200";
   d="scan'208";a="348494029"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by orsmga004.jf.intel.com with ESMTP; 20 Oct 2019 02:26:04 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/4] KVM: VMX: Write VPID to vmcs when creating vcpu
Date: Sun, 20 Oct 2019 17:10:58 +0800
Message-Id: <20191020091101.125516-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
In-Reply-To: <20191020091101.125516-1-xiaoyao.li@intel.com>
References: <20191020091101.125516-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the code that writes vmx->vpid to vmcs from vmx_vcpu_reset() to
vmx_vcpu_setup(), because vmx->vpid is allocated when creating vcpu and
never changed. So we don't need to update the vmcs.vpid when resetting
vcpu.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
