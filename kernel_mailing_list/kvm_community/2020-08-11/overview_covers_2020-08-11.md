

#### [PATCH 0/2] KVM: arm64: Fix sleeping while atomic BUG() on OOM
##### From: Will Deacon <will@kernel.org>

```c
From patchwork Tue Aug 11 10:27:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Will Deacon <will@kernel.org>
X-Patchwork-Id: 11709033
Return-Path: <SRS0=hsEk=BV=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8EBE513A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 10:27:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7548C2078E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Aug 2020 10:27:36 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1597141656;
	bh=KrsjJEn9/AAscGALbBQiNYwkr+CsOr9idxLrWL4e3TE=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ii/mVq+lnJr9EnQx2sJkH0S2WLuNRqY2y/K1HVneOrUYn/XoFtCnHU9bR6/kWun4q
	 0A+ToTy0cmgxX1jsg83vPq6uMelWWwi07y7/ur25w5A+4RmamzdjEH1n7Q/i3y4RMx
	 nBPc+TMA9/wkAOFH2Nbo8g1XR0o5LD/g42ScqASs=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728621AbgHKK1c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 06:27:32 -0400
Received: from mail.kernel.org ([198.145.29.99]:54438 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728390AbgHKK1c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 06:27:32 -0400
Received: from localhost.localdomain (236.31.169.217.in-addr.arpa
 [217.169.31.236])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A195F20656;
        Tue, 11 Aug 2020 10:27:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1597141651;
        bh=KrsjJEn9/AAscGALbBQiNYwkr+CsOr9idxLrWL4e3TE=;
        h=From:To:Cc:Subject:Date:From;
        b=PIKF5mZGoH+YEC5q1fL4nAJGN7PAFK+DseTN0XF1YN5njXxltvV+cT5aht3Kp8pGf
         TXYgvj9cDwRixGojJZO7lIXkdb3f4GLCxSFLcy+GZKd+x5wgMr1ll3l8xV4kzh3vd4
         7yJCn5KKWmuA405P8Fb/MnoX1F8fILd5+A1QL5VE=
From: Will Deacon <will@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Marc Zyngier <maz@kernel.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        James Morse <james.morse@arm.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH 0/2] KVM: arm64: Fix sleeping while atomic BUG() on OOM
Date: Tue, 11 Aug 2020 11:27:23 +0100
Message-Id: <20200811102725.7121-1-will@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

While stress-testing my arm64 stage-2 page-table rewrite [1], I ran into
a sleeping while atomic BUG() during OOM that I can reproduce with
mainline.

The problem is that the arm64 page-table code periodically calls
cond_resched_lock() when unmapping the stage-2 page-tables, but in the
case of OOM, this occurs in atomic context.

These couple of patches (based on 5.8) propagate the flags from the MMU
notifier range structure, which in turn indicate whether or not blocking
is permitted.

Cheers,

Will

[1] https://android-kvm.googlesource.com/linux/+/refs/heads/topic/pgtable

Cc: Marc Zyngier <maz@kernel.org>
Cc: Suzuki K Poulose <suzuki.poulose@arm.com>
Cc: James Morse <james.morse@arm.com>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>

--->8

Will Deacon (2):
  KVM: Pass MMU notifier range flags to kvm_unmap_hva_range()
  KVM: arm64: Only reschedule if MMU_NOTIFIER_RANGE_BLOCKABLE is not set

 arch/arm64/include/asm/kvm_host.h   |  2 +-
 arch/arm64/kvm/mmu.c                | 19 ++++++++++++++-----
 arch/mips/include/asm/kvm_host.h    |  2 +-
 arch/mips/kvm/mmu.c                 |  3 ++-
 arch/powerpc/include/asm/kvm_host.h |  3 ++-
 arch/powerpc/kvm/book3s.c           |  3 ++-
 arch/powerpc/kvm/e500_mmu_host.c    |  3 ++-
 arch/x86/include/asm/kvm_host.h     |  3 ++-
 arch/x86/kvm/mmu/mmu.c              |  3 ++-
 virt/kvm/kvm_main.c                 |  3 ++-
 10 files changed, 30 insertions(+), 14 deletions(-)
```
