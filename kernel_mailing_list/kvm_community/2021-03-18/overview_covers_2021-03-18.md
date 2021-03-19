

#### [PATCH v5 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Thu Mar 18 12:08:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12148017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EA58CC43381
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:17:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C089D64F45
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:17:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230506AbhCRMQd (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:16:33 -0400
Received: from wforward4-smtp.messagingengine.com ([64.147.123.34]:52177 "EHLO
        wforward4-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230414AbhCRMQA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:16:00 -0400
Received: from compute4.internal (compute4.nyi.internal [10.202.2.44])
        by mailforward.west.internal (Postfix) with ESMTP id D42B11030;
        Thu, 18 Mar 2021 08:08:46 -0400 (EDT)
Received: from mailfrontend2 ([10.202.2.163])
  by compute4.internal (MEProxy); Thu, 18 Mar 2021 08:08:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm2; bh=ysZiObwgOVy+D+Sr9
        R4Hl9GG6VbFETnjrwlJvPxCrR8=; b=k7nyjL3SuNolyS4sQzvJu3DvGNZ4HRi7n
        wgusgb5cqGKY+6IN/gtOhP3JCGX8TQbS/5nSDILWVkHGZlDQyP0xFAQXO9N2V8eN
        4UwOyKcjrgf7IHf2nxt3qxTAGKxyaaM3kn3rGvE2Wk11jwWTgq5it86PtBs7ZNYn
        +67ndThEkQoZq25b9hOAAjhu5MQa+csivxV7aFVKywM8OncZMDsBSVcvR4vLPI3B
        +TzB7BDzHLMhg033yIsq0gjhVgf5NwtLLR63o/L+gMkp46T72ibl3rM7WSmCXtjX
        t0TIaEP8BGrJFVTjlFdREoILffLDo9oMonVn/F4pE5Ra7sQkMdhew==
X-ME-Sender: <xms:y0JTYALloevO1Q9ScAR1YlJdLOl9wvZBj3ni89UrQlJhJVderFradQ>
    <xme:y0JTYFRC5bvq391G8u3Xc0WWCr2oyG4l81kE-XsRSCxbvka0r5yb_WonzNYufiQkc
    kJqV9GoDf0G6Yd1EzM>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrudefiedgfeejucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffoggfgsedtkeertdertddtnecuhfhrohhmpeffrghvihguucfg
    ughmohhnughsohhnuceouggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrdgtoh
    hmqeenucggtffrrghtthgvrhhnpeduhfetvdfhgfeltddtgeelheetveeufeegteevtddu
    iedvgeejhfdukeegteehheenucfkphepkedurddukeejrddviedrvdefkeenucevlhhush
    htvghrufhiiigvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhmpegurghvihgurdgvughm
    ohhnughsohhnsehorhgrtghlvgdrtghomh
X-ME-Proxy: <xmx:y0JTYDqNdnQbWOCniV2QeHfj6moOJ0hExN-ruCN-dCc6UbJPCchweQ>
    <xmx:y0JTYDaGIMpEE6AsX8zesSyhbTgFT85prT6QADhi9Yxifi_iYdbkrg>
    <xmx:y0JTYOT3OLJjLcsBWoqQWlCwtFhBh6Ckrq7UNokRUAXezrQMk9N5Yg>
    <xmx:zkJTYJsLJTd05MSfEKZf-O_az24rTWm16-rkDrsmKWLLptDdIXcecNNeGMxRQoGc>
Received: from disaster-area.hh.sledj.net (disaster-area.hh.sledj.net
 [81.187.26.238])
        by mail.messagingengine.com (Postfix) with ESMTPA id B1D3D108006D;
        Thu, 18 Mar 2021 08:08:42 -0400 (EDT)
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id 4cd56965;
        Thu, 18 Mar 2021 12:08:41 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Wanpeng Li <wanpengli@tencent.com>, x86@kernel.org,
        Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH v5 0/5] KVM: x86: dump_vmcs: don't assume GUEST_IA32_EFER,
 show MSR autoloads/autosaves
Date: Thu, 18 Mar 2021 12:08:36 +0000
Message-Id: <20210318120841.133123-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
- Don't use vcpu->arch.efer when GUEST_IA32_EFER is not available (Paolo).
- Dump the MSR autoload/autosave lists (Paolo).

v3:
- Rebase to master.
- Check only the load controls (Sean).
- Always show the PTPRs from the VMCS if they exist (Jim/Sean).
- Dig EFER out of the MSR autoload list if it's there (Paulo).
- Calculate and show the effective EFER if it is not coming from
  either the VMCS or the MSR autoload list (Sean).

v4:
- Ensure that each changeset builds with just the previous set.

v5:
- Rebase.
- Remove some cruft from changeset comments.
- Add S-by as appropriate.

David Edmondson (5):
  KVM: x86: dump_vmcs should not assume GUEST_IA32_EFER is valid
  KVM: x86: dump_vmcs should not conflate EFER and PAT presence in VMCS
  KVM: x86: dump_vmcs should consider only the load controls of EFER/PAT
  KVM: x86: dump_vmcs should show the effective EFER
  KVM: x86: dump_vmcs should include the autoload/autostore MSR lists

 arch/x86/kvm/vmx/vmx.c | 58 +++++++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.h |  2 +-
 2 files changed, 42 insertions(+), 18 deletions(-)
```
#### [PATCH v2 00/11] KVM: arm64: Enable SVE support on nVHE systems
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Mar 18 12:25:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12148051
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CA4D6C433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:26:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 93C5F64F6C
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:26:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230398AbhCRM0W (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:26:22 -0400
Received: from mail.kernel.org ([198.145.29.99]:45294 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229745AbhCRMZp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 08:25:45 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0741D64F41;
        Thu, 18 Mar 2021 12:25:45 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lMrig-002OZW-QY; Thu, 18 Mar 2021 12:25:42 +0000
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: dave.martin@arm.com, daniel.kiss@arm.com,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        broonie@kernel.org, ascull@google.com, qperret@google.com,
        kernel-team@android.com
Subject: [PATCH v2 00/11] KVM: arm64: Enable SVE support on nVHE systems
Date: Thu, 18 Mar 2021 12:25:21 +0000
Message-Id: <20210318122532.505263-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 dave.martin@arm.com, daniel.kiss@arm.com, will@kernel.org,
 catalin.marinas@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, broonie@kernel.org, ascull@google.com,
 qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables SVE support for KVM on nVHE hardware (or more
likely, software models), and is an alternative to Daniel's patch[1]
which has gone through 3 versions, but still has a number of issues.

Instead of waiting for things to happen, I decided to try and see what
I could come up with.

The SVE save/restore is modelled after the SVE VHE flow, itself
closely following the FPSIMD flow:

- the guest traps to EL2 on first SVE access, and will not trap
  anymore until vcpu_put()

- ZCR_EL2 stays constant as long as the guest has SVE enabled

- once back on the host side, ZCR_EL2 is restored to its default value
  on first SVE access

Most of this series only repaints things so that VHE and nVHE look as
similar as possible, the ZCR_EL2 management being the most visible
exception. This results in a bunch of preparatory patches that aim at
making the code slightly more readable.

This has been tested on a FVP model with both VHE/nVHE configurations
using the string tests included with the "optimized-routines"
library[2].

Patches against 5.12-rc2.

* From v1 [3]:
  - Fixed __sve_save_state SYM_FUNC_END label
  - Turned the ZCR_EL2 reset hypercall into a host trap
  - Fixed SVE state mapping size
  - Correctly mask RES0 bits from ZCR_ELx
  - Introduced sve_cond_update_zcr_vq() as a ZCR_ELx update helper
  - Renamed vcpu_sve_vq() to vcpu_sve_max_vq()
  - Collected Acks from Will

[1] https://lore.kernel.org/r/20210302164850.3553701-1-daniel.kiss@arm.com
[2] https://github.com/ARM-software/optimized-routines
[3] https://lore.kernel.org/r/20210316101312.102925-1-maz@kernel.org

Daniel Kiss (1):
  KVM: arm64: Enable SVE support for nVHE

Marc Zyngier (10):
  KVM: arm64: Provide KVM's own save/restore SVE primitives
  KVM: arm64: Use {read,write}_sysreg_el1 to access ZCR_EL1
  KVM: arm64: Let vcpu_sve_pffr() handle HYP VAs
  KVM: arm64: Introduce vcpu_sve_vq() helper
  arm64: sve: Provide a conditional update accessor for ZCR_ELx
  KVM: arm64: Rework SVE host-save/guest-restore
  KVM: arm64: Map SVE context at EL2 when available
  KVM: arm64: Save guest's ZCR_EL1 before saving the FPSIMD state
  KVM: arm64: Trap host SVE accesses when the FPSIMD state is dirty
  KVM: arm64: Save/restore SVE state for nVHE

 arch/arm64/Kconfig                      |  7 ---
 arch/arm64/include/asm/fpsimd.h         |  9 +++
 arch/arm64/include/asm/fpsimdmacros.h   | 10 +++-
 arch/arm64/include/asm/kvm_host.h       | 21 ++-----
 arch/arm64/include/asm/kvm_hyp.h        |  2 +
 arch/arm64/kvm/arm.c                    |  5 --
 arch/arm64/kvm/fpsimd.c                 | 26 +++++++--
 arch/arm64/kvm/guest.c                  |  6 +-
 arch/arm64/kvm/hyp/fpsimd.S             | 10 ++++
 arch/arm64/kvm/hyp/include/hyp/switch.h | 77 ++++++++++++-------------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c      |  4 ++
 arch/arm64/kvm/hyp/nvhe/switch.c        | 13 +++--
 arch/arm64/kvm/reset.c                  |  4 --
 13 files changed, 109 insertions(+), 85 deletions(-)
```
#### [kvm-unit-tests RFC 0/2] scripts: Fix accel handling
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Mar 18 12:44:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12148137
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A6E7DC433DB
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:45:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 661F264F04
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:45:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231520AbhCRMp2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:45:28 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:36106 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231496AbhCRMpQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:45:16 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICXvSo071340
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=toWmj4aOy71vvdraiWF+P2rkLxHrW/0/nlu/hzKrLQA=;
 b=iUtoiPvLNhTUXmGZZxMteDyU3pioBJMVQLMWufQ+MRl1OQjEz/zlctbMoPsm8HFlNOEB
 u5OoNMjA4LNFVRsZW2LyknpVifnQUdG3+76jZiQmPkz6n/0Qz5k+s68GVD5Lm9gsXzK0
 Ossd8coBQnDJvU5SUpNxHTtqCZG9EbZ4hsx0mf3W9BaJuSVgu8vEvy+QXexzTn/Ha0I+
 unOj0ZJkKgTUtIcdotl+tdBtOXbbcrrQkA/gxjgxRXEjMWqPjV1UV3mwHK9fZ0Mc63J0
 651cxHVHZ8ZVkgITcZmwAmwJwbLHKc61EOLZvWGMPz3pjEakSRfPuM1b+knJvWTRZgJV BA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c2vp8058-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:15 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ICY4xJ072700
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 08:45:15 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c2vp804e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:45:15 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICSbPb007377;
        Thu, 18 Mar 2021 12:45:13 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 378n18ms02-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 12:45:13 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ICisE937224768
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 12:44:54 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D660942041;
        Thu, 18 Mar 2021 12:45:10 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 552A74204F;
        Thu, 18 Mar 2021 12:45:09 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.24.61])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 12:45:09 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: lvivier@redhat.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com, pbonzini@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests RFC 0/2] scripts: Fix accel handling
Date: Thu, 18 Mar 2021 12:44:58 +0000
Message-Id: <20210318124500.45447-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 phishscore=0 mlxlogscore=933 mlxscore=0
 bulkscore=0 suspectscore=0 spamscore=0 clxscore=1015 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running on a system without KVM but with a /dev/kvm file or when
/dev/kvm has the wrong permissions we will think that we have the kvm
accelerator because we only check if /dev/kvm exists. To fix that we
instead start a qemu with the kvm accel and check the exit value we
can check if kvm is available.

Also we only compare the accel specified in unittests.conf with the
env ACCEL. That won't help if we don't have kvm but a test has KVM as
a requirement in unittests.conf.

My bash knowledge is rather limited, so maybe there's a better
solution?

Janosch Frank (2):
  scripts: Check kvm availability by asking qemu
  scripts: Set ACCEL in run_tests.sh if empty

 arm/run               |  4 +--
 powerpc/run           |  4 +--
 run_tests.sh          |  6 +++++
 s390x/run             | 10 ++++---
 scripts/accel.bash    | 63 +++++++++++++++++++++++++++++++++++++++++++
 scripts/arch-run.bash | 63 ++-----------------------------------------
 scripts/runtime.bash  |  2 +-
 x86/run               |  4 +--
 8 files changed, 85 insertions(+), 71 deletions(-)
 create mode 100644 scripts/accel.bash
```
#### [kvm-unit-tests PATCH 0/3] scripts: Fix PV run handling
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Mar 18 12:50:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12148163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1BBFFC433E9
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:51:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D858964E28
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 12:51:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231201AbhCRMuv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 08:50:51 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:64562 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230169AbhCRMu3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 08:50:29 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICXbTe073086;
        Thu, 18 Mar 2021 08:50:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=wy7Ore6Cp8Ux222orPtud4aOxSWm5tRjOCOuomNuypA=;
 b=RuCxw1fnO+is0b6Qfg1x/De7moTE0oHyfBNOY6W99MoKOh66eSrdl4YAYwl+fFlIQEsr
 oo4rl/l7l6O/rt4M/tqNvLVaMr+vHfvzcwOX8ZOWYpViv/fNEL6Ko+j/TeVYvrxSYMUE
 rvtCYAHxgsT/6ypVnXWJHQbOnr0Ib3zjzh3aro5bQVgy83cQzB1m8iO7bWljvZbxZyUa
 //Vp3Rf5XxUJbW75zPS8FOZXg2Lrhh28lGLO4/pzd7sgJzKH+SOynNvnMvkQy7E/thfN
 DQctn2N7llASy9qnqgZkbJRF6ikhAvJxOZt3WcWby4UDjvzYXZ5lIpKd3mkcqg+/wMWf SQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37bnrn4fc7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:50:29 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ICXpUJ074455;
        Thu, 18 Mar 2021 08:50:28 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37bnrn4fbk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 08:50:28 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12ICmjXR007435;
        Thu, 18 Mar 2021 12:50:26 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 37b30p1m2s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 12:50:26 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12ICoOtI328306
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 12:50:24 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 87866A4053;
        Thu, 18 Mar 2021 12:50:24 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6A11CA4051;
        Thu, 18 Mar 2021 12:50:23 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.24.61])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 12:50:23 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/3] scripts: Fix PV run handling
Date: Thu, 18 Mar 2021 12:50:12 +0000
Message-Id: <20210318125015.45502-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 suspectscore=0
 bulkscore=0 mlxlogscore=999 phishscore=0 lowpriorityscore=0 malwarescore=0
 impostorscore=0 adultscore=0 spamscore=0 priorityscore=1501 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103180095
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are some issues that make our current PV handling in
run_tests.sh and s390x/run a bit awkward:

 * With ACCEL=tcg or if KVM is not available we will try to run PV
   tests which won't work
 * If a host key cert has been specified but it does not exists then
   the compilation will break

This series is based on the common script fixes I just sent out.

Janosch Frank (3):
  s390x: Don't run PV testcases under tcg
  configure: s390x: Check if the host key document exists
  s390x: run: Skip PV tests when tcg is the accelerator

 configure               | 5 +++++
 s390x/run               | 5 +++++
 scripts/s390x/func.bash | 3 +++
 3 files changed, 13 insertions(+)
```
#### [kvm-unit-tests PATCH v1 0/6] Testing SSCH, CSCH and HSCH for errors
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Mar 18 13:26:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12148245
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 78317C43381
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 13:27:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F7BF64F30
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 13:27:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230518AbhCRN0j (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 09:26:39 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39992 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229634AbhCRN0f (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 18 Mar 2021 09:26:35 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12ID60FB147611
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=07d9K59A7GE/IJ1a6zdRkn1UG/83ww2K8CdV7qUPkgo=;
 b=OW+QxRzfqUF1uHvfyTBFFR4u83EMrcpaKaIp9DvqBS3TQKoMYi695+2WcSQ0HZLyVpUN
 0bxH5WgB/k/q+FlJwCxQrA/0JfUNmJBguc9G/MsTYB3Ks6ndsLXvT7Z1mxpDm1Cv9eWj
 6qZJ3W4Fm7tRk6VTmT+NNXQxujLGFCMoAVKm6ovptfFNYALAM7syH6a3H0a6E1kEO57Q
 zZBLk7o9txolH0B2mxsbzKOYjKXH++K6hHk9LKOkc0yTBsQPo3hOd/Bl9QQQkXNP2NVM
 Y3g/8fEA9kMJU698ahJJyidIANVzq5sSCSqM2XLWg31GXqCyQg5R79hMCzK7K5uJBApD Rg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c6tf1ytd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:34 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12ID6dPq154526
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 09:26:34 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0b-001b2d01.pphosted.com with ESMTP id 37c6tf1yss-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 09:26:34 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12IDOccR016730;
        Thu, 18 Mar 2021 13:26:33 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04fra.de.ibm.com with ESMTP id 37b6xjgsx0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 18 Mar 2021 13:26:32 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12IDQD6v33948114
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 18 Mar 2021 13:26:13 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DB9C04C059;
        Thu, 18 Mar 2021 13:26:29 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FC4D4C058;
        Thu, 18 Mar 2021 13:26:29 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.64.4])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 18 Mar 2021 13:26:29 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v1 0/6] Testing SSCH, CSCH and HSCH for errors
Date: Thu, 18 Mar 2021 14:26:22 +0100
Message-Id: <1616073988-10381-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-18_07:2021-03-17,2021-03-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 lowpriorityscore=0 phishscore=0 priorityscore=1501 mlxscore=0
 suspectscore=0 bulkscore=0 clxscore=1015 adultscore=0 impostorscore=0
 malwarescore=0 mlxlogscore=691 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2103180097
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The goal of this series is to test some of the I/O instructions,
SSCH, CSCH and HSCH for errors like invalid parameters, addressing,
timing etc.
Testing about timing in QEMU/KVM is truncated to sending an instruction
before the status of the preceding instruction is cleared due ton
the QEMU serialization.

To be able to achieve these tests we we need to enhance the testing
environment with:

- new definitions for the SCSW control bits
- a new function to disable a subchannel
- handling multiple interrupts
- checking the reason of the interrupts
- deferring tsch outside of the interrupt routine

regards,
Pierre

Pierre Morel (6):
  s390x: lib: css: disabling a subchannel
  s390x: lib: css: SCSW bit definitions
  s390x: lib: css: upgrading IRQ handling
  s390x: lib: css: add expectations to wait for interrupt
  s390x: css: testing ssch error response
  s390x: css: testing clear and halt subchannel

 lib/s390x/css.h     |  55 ++++++++-
 lib/s390x/css_lib.c | 197 ++++++++++++++++++++++++++-----
 s390x/css.c         | 276 +++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 498 insertions(+), 30 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/4] Fix the devicetree parser for
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Thu Mar 18 18:07:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12148949
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC270C433E0
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:08:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A207264F10
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 18:08:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232443AbhCRSIL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 14:08:11 -0400
Received: from foss.arm.com ([217.140.110.172]:45646 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229469AbhCRSHy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 14:07:54 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7C6BB31B;
        Thu, 18 Mar 2021 11:07:54 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 87DCD3F70D;
        Thu, 18 Mar 2021 11:07:53 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, drjones@redhat.com, alexandru.elisei@arm.com,
        andre.przywara@arm.com, Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH v2 0/4] Fix the devicetree parser for
 stdout-path
Date: Thu, 18 Mar 2021 18:07:23 +0000
Message-Id: <20210318180727.116004-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This set of patches fixes the way we parse the stdout-path
property in the DT. The stdout-path property is used to set up
the console. Prior to this, the code ignored the fact that
stdout-path is made of the path to the uart node as well as
parameters. As a result, it would fail to find the relevant DT
node. In addition to minor fixes in the device tree code, this
series pulls a new version of libfdt from upstream.

v1: https://lore.kernel.org/kvm/20210316152405.50363-1-nikos.nikoleris@arm.com/

Changes in v2:
  - Added strtoul and minor fix in strrchr
  - Fixes in libfdt_clean
  - Minor fix in lib/libfdt/README

Thanks,

Nikos

Nikos Nikoleris (4):
  lib/string: Add strnlen, strrchr and strtoul
  libfdt: Pull v1.6.0
  Makefile: Remove overriding recipe for libfdt_clean
  devicetree: Parse correctly the stdout-path

 lib/libfdt/README            |   5 +-
 Makefile                     |  16 +-
 arm/Makefile.common          |   2 +-
 lib/libfdt/Makefile.libfdt   |  10 +-
 powerpc/Makefile.common      |   2 +-
 lib/libfdt/version.lds       |  24 +-
 lib/libfdt/fdt.h             |  53 +--
 lib/libfdt/libfdt.h          | 766 +++++++++++++++++++++++++-----
 lib/libfdt/libfdt_env.h      | 109 ++---
 lib/libfdt/libfdt_internal.h | 206 +++++---
 lib/stdlib.h                 |  12 +
 lib/string.h                 |   5 +-
 lib/devicetree.c             |  15 +-
 lib/libfdt/fdt.c             | 200 +++++---
 lib/libfdt/fdt_addresses.c   | 101 ++++
 lib/libfdt/fdt_check.c       |  74 +++
 lib/libfdt/fdt_empty_tree.c  |  48 +-
 lib/libfdt/fdt_overlay.c     | 881 +++++++++++++++++++++++++++++++++++
 lib/libfdt/fdt_ro.c          | 512 +++++++++++++++-----
 lib/libfdt/fdt_rw.c          | 231 +++++----
 lib/libfdt/fdt_strerror.c    |  53 +--
 lib/libfdt/fdt_sw.c          | 297 ++++++++----
 lib/libfdt/fdt_wip.c         |  90 ++--
 lib/string.c                 |  77 ++-
 24 files changed, 2948 insertions(+), 841 deletions(-)
 create mode 100644 lib/stdlib.h
 create mode 100644 lib/libfdt/fdt_addresses.c
 create mode 100644 lib/libfdt/fdt_check.c
 create mode 100644 lib/libfdt/fdt_overlay.c
```
#### [PATCH v2 0/4] KVM: x86: MSR filtering and related fixes
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Mar 18 22:43:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12149345
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B2850C433E6
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 22:44:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83A5964F11
	for <kvm@archiver.kernel.org>; Thu, 18 Mar 2021 22:44:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232625AbhCRWnw (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 18 Mar 2021 18:43:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49386 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230368AbhCRWnP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 18 Mar 2021 18:43:15 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9AF3AC06174A
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 15:43:15 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id p136so50604449ybc.21
        for <kvm@vger.kernel.org>; Thu, 18 Mar 2021 15:43:15 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=0DUdG6+uWcR80QCYp/6dg/L+XaUC6ThjbkuOe9VdQD4=;
        b=rAO86R5j7uv4k/gpsuCAsovgD5YfUhw4FLglkgm4h7+p85RHSq/nnDXbxvuRXggadC
         BhBBZEmGhaHL+67IutzvTP6EtzLXXsZaeuFsUkCZgli5NUv2jLmkH6lg4E21PpyvysaG
         KGbwfNrO+0clC0HPUZmed5uQrPxzZGVKNu2eqXfvvg1dpPzVLJ+bEjMNQPvYIGewY9+Z
         Pp/YP0CXLj+BhhIn6sZvC8lKusbU8LrJ72HIc4mqBg0pYNNnn4fsWgaFpTN7X5Wf0nnV
         Kg9O2wQ+6Al9VfEBv0JaCix/A/zW2G5aNUpVNJpdhBebPLbM8sB0nw1CYKVjCXYJPbsz
         SBWg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=0DUdG6+uWcR80QCYp/6dg/L+XaUC6ThjbkuOe9VdQD4=;
        b=EmAoRyoAUX5Dt4s2vH08M20ycpCppPb4zJ/HNnY6b9zRcSgj1ELfF6kkTFgRU1Cls+
         jmOGbJWaT871tVbI1jsInWeUqqaxBRQ+nOiZ41a2NvJ+319Znz0n7bbrkFIoXVLyrqC3
         LU2SehGhYHXhhVVY5/gsbIfjixQBaZw9p0BxDDe8NRii7og/gIv/+fZwB5SCfVw/Esph
         C8cFUwk+Cuy9d8FVgQ12VcKxCsDyArRMe+y0oiGg5U022p/UbguW/hlodgIHgvYlcZzo
         FWHUuqL3cKrlD9A6DPDJaTbcKlc1wue8FNS22V+Ew6TJ4QZkcM90XOLoMNE3VLUwNwz1
         2R9w==
X-Gm-Message-State: AOAM530nlx0IhEKoeihvghoEVubuXDVP6XPSEwGAZa9j9ox5mSBXMEO+
        Mk06nljS4kQDu0vnnqNW+GWIU8nTFU4=
X-Google-Smtp-Source: 
 ABdhPJyvkQoAFfVRCK5CJFRkWxaQyuTnUU/i5AYciu9HvCGCvlfImdoL2rAEO67g0ZMcWGsMZnS7Sssob3M=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:25e0:6b8b:f878:23d1])
 (user=seanjc job=sendgmr) by 2002:a25:bb41:: with SMTP id
 b1mr2306208ybk.249.1616107393323;
 Thu, 18 Mar 2021 15:43:13 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 18 Mar 2021 15:43:06 -0700
Message-Id: <20210318224310.3274160-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.rc2.261.g7f71774620-goog
Subject: [PATCH v2 0/4] KVM: x86: MSR filtering and related fixes
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Yuan Yao <yaoyuan0329os@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the MSR filtering implementation to treat a given filter instance
as an atomic unit, and to properly protect it with SRCU.

Fix two nVMX bugs related to MSR filtering (one directly, one indirectly),
and additional cleanup on top.

Regarding the macro insanity in patch 03, I verified the before and after
binary output for vmx_set_intercept_for_msr() was identical, again.  This
required wrapping "if (msr <= 0x1fff)" with (un)likely in both the before
and after versions; gcc made seemingly random choices without forcing it
to favor a specific branch.

v2:
  - Collect R-b. [Paolo, Alex].
  - Make the macro insanity slightly less insane. [Paolo]

v1: https://lkml.kernel.org/r/20210316184436.2544875-1-seanjc@google.com

Sean Christopherson (4):
  KVM: x86: Protect userspace MSR filter with SRCU, and set
    atomically-ish
  KVM: nVMX: Handle dynamic MSR intercept toggling
  KVM: VMX: Macrofy the MSR bitmap getters and setters
  KVM: nVMX: Clean up x2APIC MSR handling for L2

 Documentation/virt/kvm/api.rst  |   6 +-
 arch/x86/include/asm/kvm_host.h |  17 ++--
 arch/x86/kvm/vmx/nested.c       | 161 +++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.c          |  67 +------------
 arch/x86/kvm/vmx/vmx.h          |  28 ++++++
 arch/x86/kvm/x86.c              | 109 ++++++++++++---------
 6 files changed, 172 insertions(+), 216 deletions(-)
```
