

#### [PATCH 0/3] arm64: KVM: Kiss hyp_alternate_select() goodbye
##### From: Marc Zyngier <maz@kernel.org>

```c
From patchwork Sun Sep  1 21:12:34 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11125747
Return-Path: <SRS0=mDu4=W4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3EDB51399
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  1 Sep 2019 21:12:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D56A22CF7
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun,  1 Sep 2019 21:12:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1567372378;
	bh=fxnNTYTRajAiVeP624Hg7a5lJu+ZE69zPsUxPj5tOA8=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=0T0dZiiZsLMYsNCt2KW89zBpKynUlKxYXtwCRnP4c9ttd8o//3JWeiGt1XSD0+mSR
	 RszaPOi4B1sh48+PZEjY5DfQPwWBOm4zAo18CWDOuGksCNLG2Ny+a7/bee3mxbhK1I
	 A0RGjbAQRffgv7QbhEDwbKjkClMunWLPkNFk41d4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729012AbfIAVM5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 1 Sep 2019 17:12:57 -0400
Received: from foss.arm.com ([217.140.110.172]:46412 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728891AbfIAVM4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 1 Sep 2019 17:12:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 552DE28;
        Sun,  1 Sep 2019 14:12:56 -0700 (PDT)
Received: from why.lan (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 180C73F718;
        Sun,  1 Sep 2019 14:12:54 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH 0/3] arm64: KVM: Kiss hyp_alternate_select() goodbye
Date: Sun,  1 Sep 2019 22:12:34 +0100
Message-Id: <20190901211237.11673-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

hyp_alternate_select() is a leftover from the my second attempt at
supporting VHE (the first one was never merged, thankfully), and is
now an irrelevant relic. It was a way to patch function pointers
without having to dereference memory, a bit like static keys for
function calls.

Lovely idea, but since Christoffer mostly separated the VHE and !VHE
hypervisor paths, most of the uses of hyp_alternate_select() are
gone. What is left is two instances that are better replaced by
already existing static keys. One of the instances becomes
cpus_have_const_cap(), and the rest is a light sprinkling of
has_vhe().

So off it goes.

Marc Zyngier (3):
  arm64: KVM: Drop hyp_alternate_select for checking for
    ARM64_WORKAROUND_834220
  arm64: KVM: Replace hyp_alternate_select with has_vhe()
  arm64: KVM: Kill hyp_alternate_select()

 arch/arm64/include/asm/kvm_hyp.h | 24 ---------------------
 arch/arm64/kvm/hyp/switch.c      | 17 ++-------------
 arch/arm64/kvm/hyp/tlb.c         | 36 +++++++++++++++++++-------------
 3 files changed, 24 insertions(+), 53 deletions(-)
```
