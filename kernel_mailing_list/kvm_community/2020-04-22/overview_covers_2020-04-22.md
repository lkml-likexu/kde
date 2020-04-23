

#### [PATCH v3 -tip 0/5] kvm: Use rcuwait for vcpu blocking
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id 8CB67AC46;
        Wed, 22 Apr 2020 04:11:42 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: bigeasy@linutronix.de, peterz@infradead.org, rostedt@goodmis.org,
        torvalds@linux-foundation.org, will@kernel.org,
        joel@joelfernandes.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, dave@stgolabs.net
Subject: [PATCH v3 -tip 0/5] kvm: Use rcuwait for vcpu blocking
Date: Tue, 21 Apr 2020 21:07:34 -0700
Message-Id: <20200422040739.18601-1-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following is an updated revision of the kvm vcpu to rcuwait conversion[0],
following the work on completions using simple waitqueues.

Changes from v2:
  - new patch 3 which adds prepare_to_rcuwait and finish_rcu helpers.
  - fixed broken sleep and tracepoint semantics in patch 4. (Marc and Paolo)
  
This has only been run tested on x86 but compile tested on mips, powerpc
and arm32. 

This series applies on top of current -tip.

[0] https://lore.kernel.org/lkml/20200320085527.23861-3-dave@stgolabs.net/

Thanks!

Davidlohr Bueso (5):
  rcuwait: Fix stale wake call name in comment
  rcuwait: Let rcuwait_wake_up() return whether or not a task was awoken
  rcuwait: Introduce prepare_to and finish_rcuwait
  kvm: Replace vcpu->swait with rcuwait
  sched/swait: Reword some of the main description

 arch/mips/kvm/mips.c                  |  6 ++----
 arch/powerpc/include/asm/kvm_book3s.h |  2 +-
 arch/powerpc/include/asm/kvm_host.h   |  2 +-
 arch/powerpc/kvm/book3s_hv.c          | 22 ++++++++--------------
 arch/powerpc/kvm/powerpc.c            |  2 +-
 arch/x86/kvm/lapic.c                  |  2 +-
 include/linux/kvm_host.h              | 10 +++++-----
 include/linux/rcuwait.h               | 23 +++++++++++++++++------
 include/linux/swait.h                 | 23 +++++------------------
 kernel/exit.c                         |  9 ++++++---
 virt/kvm/arm/arch_timer.c             |  2 +-
 virt/kvm/arm/arm.c                    |  9 +++++----
 virt/kvm/async_pf.c                   |  3 +--
 virt/kvm/kvm_main.c                   | 19 +++++++++----------
 14 files changed, 63 insertions(+), 71 deletions(-)
```
#### [PATCH 00/26] KVM: arm64: Preliminary NV patches
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Apr 22 12:00:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11503589
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D39D1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:00:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F91120882
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:00:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587556858;
	bh=cjNtiZiSfG8NCNGrLmoyucuhnBDcnLMQHlTpx9c+/rQ=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=fYerzxQcRSPD0A0M0/tF6XFr65IDxERHsVYmWZ2vVs6BIHQL5hjY8lIoCXVOxqZ7z
	 zGRmDIoo/mDQ9eL616/JSfBHjU8e5K2Oy9GvcbaL2dUm5taILm4fsKirTHsC4LUyiG
	 d0VLc77NU/efGJNXUC3PvciL8FXKuqOaJekzvXNg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726988AbgDVMA5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 08:00:57 -0400
Received: from mail.kernel.org ([198.145.29.99]:43752 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726043AbgDVMA5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 08:00:57 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 45B3D20780;
        Wed, 22 Apr 2020 12:00:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587556856;
        bh=cjNtiZiSfG8NCNGrLmoyucuhnBDcnLMQHlTpx9c+/rQ=;
        h=From:To:Cc:Subject:Date:From;
        b=NCoygnjpF76Otji5EmVvuJDE0QdIRz2Fim66ksOD9SzJprbT6vIp/3C0kUNbb2y0G
         P9h/3TxTnhcDvtYzGc6pmq++7JXvFqDt+tJaQXnvjuTvkCcJQecQrAZYj8mqCiCZsx
         laibgAPSq3EHmqsHQ6zH+wY4BjvSqpearnncm5PY=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jRE3i-005UI7-JR; Wed, 22 Apr 2020 13:00:54 +0100
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
Subject: [PATCH 00/26] KVM: arm64: Preliminary NV patches
Date: Wed, 22 Apr 2020 13:00:24 +0100
Message-Id: <20200422120050.3693593-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
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

Hi all,

In order not to repeat the 90+ patch series that resulted in a
deafening silence last time, I've extracted a smaller set of patches
that form the required dependencies that allow the rest of the 65 NV
patches to be added on top. Yes, it is that bad.

The one real feature here is support for the ARMv8.4-TTL extension at
Stage-2 only. The reason to support it is that it helps the hypervisor
a lot when it comes to finding out how much to invalidate. It is thus
always "supported" with NV.

The rest doesn't contain any functionality change. Most of it reworks
existing data structures and adds new accessors for the things that
get moved around. The reason for this is that:

- With NV, we end-up with multiple Stage-2 MMU contexts per VM instead
  of a single one. This requires we divorce struct kvm from the S2 MMU
  configuration. Of course, we stick with a single MMU context for now.

- With ARMv8.4-NV, a number of system register accesses are turned
  into memory accesses into the so-called VNCR page. It is thus
  convenient to make this VNCR page part of the vcpu context and avoid
  copying data back and forth. For this to work, we need to make sure
  that all the VNCR-aware sysregs are moved into our per-vcpu sys_regs
  array instead of leaving in other data structures (the timers, for
  example). The VNCR page itself isn't introduced with these patches.

- As some of these data structures change, we need a way to isolate
  the userspace ABI from such change.

- The exception generation code is also reworked to prepare the
  addition of EL2 exceptions.

There is also a number of cleanups that were in the full fat series
that I decided to move early to get them out of the way.

The whole this is a bit of a mix of vaguely unrelated "stuff", but it
all comes together if you look at the final series[1]. This applies on
top of v5.7-rc1.

I haven't applied any of the Tested-by: tags, as the series keeps
changing. Please keep testing though!

[1] https://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git/log/?h=kvm-arm64/nv-5.7-rc1-WIP

Christoffer Dall (2):
  KVM: arm64: Factor out stage 2 page table data from struct kvm
  KVM: arm64: vgic-v3: Take cpu_if pointer directly instead of vcpu

Marc Zyngier (24):
  KVM: arm64: Check advertised Stage-2 page size capability
  KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
  arm64: Detect the ARMv8.4 TTL feature
  arm64: Document SW reserved PTE/PMD bits in Stage-2 descriptors
  arm64: Add level-hinted TLB invalidation helper
  KVM: arm64: Add a level hint to __kvm_tlb_flush_vmid_ipa
  KVM: arm64: Use TTL hint in when invalidating stage-2 translations
  KVM: arm64: Refactor vcpu_{read,write}_sys_reg
  KVM: arm64: Add missing reset handlers for PMU emulation
  KVM: arm64: Move sysreg reset check to boot time
  KVM: arm64: Introduce accessor for ctxt->sys_reg
  KVM: arm64: hyp: Use ctxt_sys_reg/__vcpu_sys_reg instead of raw
    sys_regs access
  KVM: arm64: sve: Use __vcpu_sys_reg() instead of raw sys_regs access
  KVM: arm64: pauth: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: debug: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: Don't use empty structures as CPU reset state
  KVM: arm64: Make struct kvm_regs userspace-only
  KVM: arm64: Move ELR_EL1 to the system register array
  KVM: arm64: Move SP_EL1 to the system register array
  KVM: arm64: Disintegrate SPSR array
  KVM: arm64: Move SPSR_EL1 to the system register array
  KVM: arm64: timers: Rename kvm_timer_sync_hwstate to
    kvm_timer_sync_user
  KVM: arm64: timers: Move timer registers to the sys_regs file
  KVM: arm64: Parametrize exception entry with a target EL

 arch/arm64/include/asm/cpucaps.h        |   3 +-
 arch/arm64/include/asm/kvm_asm.h        |   6 +-
 arch/arm64/include/asm/kvm_emulate.h    |  37 +---
 arch/arm64/include/asm/kvm_host.h       |  71 +++++--
 arch/arm64/include/asm/kvm_hyp.h        |  30 +--
 arch/arm64/include/asm/kvm_mmu.h        |  27 ++-
 arch/arm64/include/asm/pgtable-hwdef.h  |   2 +
 arch/arm64/include/asm/stage2_pgtable.h |   9 +
 arch/arm64/include/asm/sysreg.h         |   4 +
 arch/arm64/include/asm/tlbflush.h       |  30 +++
 arch/arm64/kernel/asm-offsets.c         |   3 +-
 arch/arm64/kernel/cpufeature.c          |  19 ++
 arch/arm64/kvm/fpsimd.c                 |   6 +-
 arch/arm64/kvm/guest.c                  |  79 ++++++-
 arch/arm64/kvm/handle_exit.c            |  17 +-
 arch/arm64/kvm/hyp/debug-sr.c           |  18 +-
 arch/arm64/kvm/hyp/entry.S              |   3 +-
 arch/arm64/kvm/hyp/switch.c             |  31 ++-
 arch/arm64/kvm/hyp/sysreg-sr.c          | 160 +++++++-------
 arch/arm64/kvm/hyp/tlb.c                |  51 +++--
 arch/arm64/kvm/inject_fault.c           |  75 +++----
 arch/arm64/kvm/regmap.c                 |  37 +++-
 arch/arm64/kvm/reset.c                  |  60 ++++--
 arch/arm64/kvm/sys_regs.c               | 215 ++++++++++---------
 include/kvm/arm_arch_timer.h            |  13 +-
 include/kvm/arm_vgic.h                  |   5 +-
 virt/kvm/arm/arch_timer.c               | 157 +++++++++++---
 virt/kvm/arm/arm.c                      |  40 ++--
 virt/kvm/arm/hyp/vgic-v3-sr.c           |  33 +--
 virt/kvm/arm/mmu.c                      | 267 +++++++++++++-----------
 virt/kvm/arm/trace.h                    |   8 +-
 virt/kvm/arm/vgic/vgic-v2.c             |  10 +-
 virt/kvm/arm/vgic/vgic-v3.c             |  14 +-
 virt/kvm/arm/vgic/vgic.c                |  25 ++-
 34 files changed, 942 insertions(+), 623 deletions(-)
```
#### [PATCH v2 0/7] clean up redundant 'kvm_run' parameters
##### From: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>

```c
From patchwork Wed Apr 22 12:58:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianjia Zhang <tianjia.zhang@linux.alibaba.com>
X-Patchwork-Id: 11503801
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D28F15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:59:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EB6720857
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 12:59:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727125AbgDVM7Q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 08:59:16 -0400
Received: from out30-54.freemail.mail.aliyun.com ([115.124.30.54]:50913 "EHLO
        out30-54.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725924AbgDVM7P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 22 Apr 2020 08:59:15 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R641e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e01355;MF=tianjia.zhang@linux.alibaba.com;NM=1;PH=DS;RN=37;SR=0;TI=SMTPD_---0TwKABpW_1587560291;
Received: from localhost(mailfrom:tianjia.zhang@linux.alibaba.com
 fp:SMTPD_---0TwKABpW_1587560291)
          by smtp.aliyun-inc.com(127.0.0.1);
          Wed, 22 Apr 2020 20:58:11 +0800
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
Subject: [PATCH v2 0/7] clean up redundant 'kvm_run' parameters
Date: Wed, 22 Apr 2020 20:58:03 +0800
Message-Id: <20200422125810.34847-1-tianjia.zhang@linux.alibaba.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the current kvm version, 'kvm_run' has been included in the 'kvm_vcpu'
structure. Earlier than historical reasons, many kvm-related function
parameters retain the 'kvm_run' and 'kvm_vcpu' parameters at the same time.
This patch does a unified cleanup of these remaining redundant parameters.

This series of patches has completely cleaned the architecture of
arm64, mips, ppc, and s390 (no such redundant code on x86). Due to
the large number of modified codes, a separate patch is made for each
platform. On the ppc platform, there is also a redundant structure
pointer of 'kvm_run' in 'vcpu_arch', which has also been cleaned
separately.
---
v2 change:
  s390 retains the original variable name and minimizes modification.

Tianjia Zhang (7):
  KVM: s390: clean up redundant 'kvm_run' parameters
  KVM: arm64: clean up redundant 'kvm_run' parameters
  KVM: PPC: Remove redundant kvm_run from vcpu_arch
  KVM: PPC: clean up redundant 'kvm_run' parameters
  KVM: PPC: clean up redundant kvm_run parameters in assembly
  KVM: MIPS: clean up redundant 'kvm_run' parameters
  KVM: MIPS: clean up redundant kvm_run parameters in assembly

 arch/arm64/include/asm/kvm_coproc.h      |  12 +--
 arch/arm64/include/asm/kvm_host.h        |  11 +--
 arch/arm64/include/asm/kvm_mmu.h         |   2 +-
 arch/arm64/kvm/handle_exit.c             |  36 +++----
 arch/arm64/kvm/sys_regs.c                |  13 ++-
 arch/mips/include/asm/kvm_host.h         |  32 +------
 arch/mips/kvm/emulate.c                  |  59 ++++--------
 arch/mips/kvm/entry.c                    |  15 +--
 arch/mips/kvm/mips.c                     |  14 +--
 arch/mips/kvm/trap_emul.c                | 114 ++++++++++-------------
 arch/mips/kvm/vz.c                       |  26 ++----
 arch/powerpc/include/asm/kvm_book3s.h    |  16 ++--
 arch/powerpc/include/asm/kvm_host.h      |   1 -
 arch/powerpc/include/asm/kvm_ppc.h       |  27 +++---
 arch/powerpc/kvm/book3s.c                |   4 +-
 arch/powerpc/kvm/book3s.h                |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c      |  12 +--
 arch/powerpc/kvm/book3s_64_mmu_radix.c   |   4 +-
 arch/powerpc/kvm/book3s_emulate.c        |  10 +-
 arch/powerpc/kvm/book3s_hv.c             |  64 ++++++-------
 arch/powerpc/kvm/book3s_hv_nested.c      |  12 +--
 arch/powerpc/kvm/book3s_interrupts.S     |  17 ++--
 arch/powerpc/kvm/book3s_paired_singles.c |  72 +++++++-------
 arch/powerpc/kvm/book3s_pr.c             |  33 ++++---
 arch/powerpc/kvm/booke.c                 |  39 ++++----
 arch/powerpc/kvm/booke.h                 |   8 +-
 arch/powerpc/kvm/booke_emulate.c         |   2 +-
 arch/powerpc/kvm/booke_interrupts.S      |   9 +-
 arch/powerpc/kvm/bookehv_interrupts.S    |  10 +-
 arch/powerpc/kvm/e500_emulate.c          |  15 ++-
 arch/powerpc/kvm/emulate.c               |  10 +-
 arch/powerpc/kvm/emulate_loadstore.c     |  32 +++----
 arch/powerpc/kvm/powerpc.c               |  72 +++++++-------
 arch/powerpc/kvm/trace_hv.h              |   6 +-
 arch/s390/kvm/kvm-s390.c                 |  37 +++++---
 virt/kvm/arm/arm.c                       |   6 +-
 virt/kvm/arm/mmio.c                      |  11 ++-
 virt/kvm/arm/mmu.c                       |   5 +-
 38 files changed, 396 insertions(+), 474 deletions(-)
```
#### [PATCH v3 0/6] KVM: arm: vgic fixes for 5.7
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Apr 22 16:18:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11504201
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AACC92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 16:19:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4083D214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 16:19:23 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1587572363;
	bh=7VEPAypFNkCLCXVaH5VuvuZA8Ena++dogWtuuNEmwT4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=fDs7YDEawRoobpoMu97LMgd8K8ibkqKMjMbGKkZCQdS8WQ1kcZ1gG9oxfgnn/1ACl
	 GS3nXx+bOaZxlKzzuJvpT5abMp/kjFgVanQDJ99ccAXNbN74WP2QqXL30V6xkIUfpU
	 YGpu+um+/bNPjHVJi2W22oktOQYnLQoOrPc7ToWI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726724AbgDVQTW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 12:19:22 -0400
Received: from mail.kernel.org ([198.145.29.99]:39200 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726466AbgDVQTV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 12:19:21 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E25242076E;
        Wed, 22 Apr 2020 16:19:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1587572361;
        bh=7VEPAypFNkCLCXVaH5VuvuZA8Ena++dogWtuuNEmwT4=;
        h=From:To:Cc:Subject:Date:From;
        b=xcvSTJokq2ZrkNRcIv6uVgGazPlia+USShG5kmef9EYj0VeDChVzz3C9tW4jvqKY9
         yMBsuRARGHoDHUycJA7mPKlYAJwALXoiEApfJDXWcOQTb8FvcIHvpDKywYvgg4WUYR
         JqzNUC+vMd8nSYqNltqt+AqS14K3OPRa2vbMRlMw=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jRI5n-005Ynp-6B; Wed, 22 Apr 2020 17:19:19 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        Andre Przywara <Andre.Przywara@arm.com>,
        Julien Grall <julien@xen.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v3 0/6] KVM: arm: vgic fixes for 5.7
Date: Wed, 22 Apr 2020 17:18:38 +0100
Message-Id: <20200422161844.3848063-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, yuzenghui@huawei.com,
 eric.auger@redhat.com, Andre.Przywara@arm.com, julien@xen.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here's a few vgic fixes I've been piling on during the merge window,
plus a couple that Zenghui contributed, and which I added to the mix.

The first patch is a silly off-by-one bug in the ACTIVE handling code,
where we miss fail to stop the guest if writing to the first set of
GICv2 SPIs. Oopsie boo.

The second patch improves the handling of the ACTIVE registers, which
we never synchronise on the read side (the distributor state can only
be updated when the vcpu exits). Let's fix it the same way we do it on
the write side (stop-the-world, read, restart). Yes, this is
expensive.

The following two patches deal with an issue where we consider the HW
state of an interrupt when responding to a userspace access. We should
never do this, as the guest shouldn't be running at this stage and if
it is, it is absolutely fine to return random bits to userspace. It
could also be that there is no active guest context at this stage, and
you end up with an Oops, which nobody really enjoys.

The last two patches fix a couple of memory leaks.

* From v2:
  - Now handle userspace access to GICv2 GICD_I{S,C}PENDR, which never
    really worked (pointed out by James)
  - Collected tags from Andre and James

Marc Zyngier (4):
  KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
  KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER
    read
  KVM: arm: vgic: Only use the virtual state when userspace accesses
    enable bits
  KVM: arm: vgic-v2: Only use the virtual state when userspace accesses
    pending bits

Zenghui Yu (2):
  KVM: arm64: vgic-v3: Retire all pending LPIs on vcpu destroy
  KVM: arm64: vgic-its: Fix memory leak on the error path of
    vgic_add_lpi()

 virt/kvm/arm/vgic/vgic-init.c    |   6 +
 virt/kvm/arm/vgic/vgic-its.c     |  11 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c |  16 ++-
 virt/kvm/arm/vgic/vgic-mmio-v3.c |  28 ++--
 virt/kvm/arm/vgic/vgic-mmio.c    | 228 +++++++++++++++++++++++--------
 virt/kvm/arm/vgic/vgic-mmio.h    |  19 +++
 6 files changed, 230 insertions(+), 78 deletions(-)
```
#### [PATCH v2 0/4] Split hyperv-tlfs.h into generic and arch specific
##### From: Michael Kelley <mikelley@microsoft.com>

```c
From patchwork Wed Apr 22 19:57:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Kelley <mikelley@microsoft.com>
X-Patchwork-Id: 11504449
Return-Path: <SRS0=k2wD=6G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC4DF14DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 19:58:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C008D21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 22 Apr 2020 19:58:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=microsoft.com header.i=@microsoft.com
 header.b="VbmCpBhd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726516AbgDVT6i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 15:58:38 -0400
Received: from mail-dm6nam11on2109.outbound.protection.outlook.com
 ([40.107.223.109]:6625
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726380AbgDVT6i (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 15:58:38 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=DA+ehh3tPQ0Yi3G0CzR/g1+8yMOqHkzfgepW/4SIQbE7pGbxt/V3GenoxtLiEC7yJa7Vx/HdJbcGTzIDvWTzVL7Ms+588KCT2W0+v05mdZdcxW896XnixM33DnRPpsun53M4gTkeiEOGAqvtmZCjDf7NfjfDsm046sl012bc+9t41+JpvVxxapydRDBDtsnQgQfn9mMJOS2XBpFzU280Lz1NBeXv/vzhplGaZrT85dI1fLDlpKLHbwI8dt4GA/T/R8FJAKr5S1KLQ/6xmZHSsksd1wP8/sBjmqu8CXS/qyOngUyGPRI7mWLwPmPD9RV7hMWRnw6wY4nyxhn61SRmGw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K/AVLmRdzyCxMOHHy2Y8kYout/ihcg0sWK74rWgP0tk=;
 b=D31wGoVB/Zn4GNDH+T6v6faJhRfuXBlQfEjpsQvDKX9lsPR3fpx5WQuOB0F0P7y1h7WQXXANgfuwrykoMgu2dbVxRKSVtSxO0IpDdi1xa3CbJqFU4Us1X7PwnqVjJ4DNM1W9ZFMoXjiVvOptCNO2QIMn0XIbf5TaLz+PWAgV948x/8gOeSIeLfH4dQ7aM+UNVcr94ZVKVT48+URQFCaTbHc5FZmDC8WX18fZlXgcNa602Ekh9Zp3hCEf92z/briZPXlySEvEs5zG0nQdGNP1BupF+VpV1OYxDCb3cRUjZGUSToHt1fJoPGIhj44zVGMcmLXK8KuT4Z/brOrriYBMXg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=microsoft.com; dmarc=pass action=none
 header.from=microsoft.com; dkim=pass header.d=microsoft.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K/AVLmRdzyCxMOHHy2Y8kYout/ihcg0sWK74rWgP0tk=;
 b=VbmCpBhdfY1vgg6qf6yqKtVipQcPO7y7oAAomsixPOUPlOIBkpc2tdTxRu15YFzcRe7/9O6f5v+bnwBPkej/Svff1/dDpdS5s7/jdUYr6QuMCo5vl6SvU1DL8ik5Sz4sIbS51KZQxwbtgbClYnaEAldYC2b7PjkM7Rp1M4zcnv4=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=mikelley@microsoft.com;
Received: from BN6PR21MB0178.namprd21.prod.outlook.com (2603:10b6:404:94::12)
 by BN6PR21MB0148.namprd21.prod.outlook.com (2603:10b6:404:93::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2958.2; Wed, 22 Apr
 2020 19:58:34 +0000
Received: from BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec]) by BN6PR21MB0178.namprd21.prod.outlook.com
 ([fe80::a97c:360c:9ed2:12ec%11]) with mapi id 15.20.2958.001; Wed, 22 Apr
 2020 19:58:34 +0000
From: Michael Kelley <mikelley@microsoft.com>
To: kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        wei.liu@kernel.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, x86@kernel.org, hpa@zytor.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org
Cc: mikelley@microsoft.com
Subject: [PATCH v2 0/4] Split hyperv-tlfs.h into generic and arch specific
 files
Date: Wed, 22 Apr 2020 12:57:33 -0700
Message-Id: <20200422195737.10223-1-mikelley@microsoft.com>
X-Mailer: git-send-email 2.18.2
X-ClientProxiedBy: MWHPR19CA0078.namprd19.prod.outlook.com
 (2603:10b6:320:1f::16) To BN6PR21MB0178.namprd21.prod.outlook.com
 (2603:10b6:404:94::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from MHKdev.corp.microsoft.com (167.220.2.108) by
 MWHPR19CA0078.namprd19.prod.outlook.com (2603:10b6:320:1f::16) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2937.13 via Frontend
 Transport; Wed, 22 Apr 2020 19:58:32 +0000
X-Mailer: git-send-email 2.18.2
X-Originating-IP: [167.220.2.108]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 6672d878-4d91-4111-2943-08d7e6f78a17
X-MS-TrafficTypeDiagnostic: BN6PR21MB0148:|BN6PR21MB0148:|BN6PR21MB0148:
X-MS-Exchange-Transport-Forked: True
X-LD-Processed: 72f988bf-86f1-41af-91ab-2d7cd011db47,ExtAddr
X-Microsoft-Antispam-PRVS: 
 <BN6PR21MB0148D71E3BFC1A20DCC127E7D7D20@BN6PR21MB0148.namprd21.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6790;
X-Forefront-PRVS: 03818C953D
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:BN6PR21MB0178.namprd21.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(346002)(136003)(396003)(366004)(376002)(39860400002)(81156014)(82960400001)(8936002)(10290500003)(4326008)(26005)(82950400001)(5660300002)(107886003)(956004)(2616005)(478600001)(66556008)(66946007)(66476007)(6486002)(1076003)(86362001)(316002)(8676002)(2906002)(16526019)(186003)(36756003)(52116002)(7696005)(7416002)(41533002)(921003);DIR:OUT;SFP:1102;
Received-SPF: None (protection.outlook.com: microsoft.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 UnyelGc10ZdLFjXmVQ9c3MIg5hDWMbiVhRo81RRdDi0+3kp4V4XBytlSH+UDeoOxsDPtZP4vNR+fJtwysEovW+2Fu3cOooYRx+H6LrQ5wtZGxz+P9LwKjNkzO+8tRQALQKYJxUmBHKoZCCpUnSFH6gbJgl4rWDLbripIF5YCgxHcs4hvDXVCZP5CryxZY2A9JNdDM3irg7kN2Aa9fOmcSPd+6B/wvqr5LUzZMsQCbXutogHVbdpBNbYV/Qw+DkUeXC95yNw+scGWd7zB+ei2GuIOmkrmhfPxtaRr11krIOWjrne09E7QRHG89wLWV3LimUPWxfdzVGrUBe8nboZ8FFH0q/YKySYIP47E3up4EvIIVpoklnbruxEXfBuORxY91MYmLiegRy1zWkGgGjlnsxXXTauxUUPrFEDokm87b92alaxDcR9LF2sqgyqi+aHZYbzudUqVRQ5Sy5cmprkqOh2+cxzSStDuV2s1Ano8/KKmeGGft2LrbuYdjYM5tW03
X-MS-Exchange-AntiSpam-MessageData: 
 Bk4DO3Xs7JfFvCHGn20ME44TPd6dALa70cubwbNQWnTeCzpruSWgM6vugvzJSDBNDQE2EBgAxFJOI7u4hPMtcQDzjxwmPntQ8PIY2yD+jFHgMLEpo8ycjP+npm9C+GmGi2+EEAQfelKpjVdnNr56z/xGz8gXYXSEWQm/kQi/p4sW1sHedI52pxbV5HO5+rxpjZEVNzfssLayWkr13WIH20aeDnT74bgJtC1A0TVSTnjE1VhgPsXl2XML3KRJ3oVnM1WosI4U8EZ4roNLqSDh+Ymex7mSx+Ku7FAQqefqEosf1ta7HC7SF/JteYMm22jZTppsUT4wcw46inK4pg8LiN7ZcLvA0p/iGUPBidw8JwqsBMGbm26F8cXh3G+N4+XQGwAki5FeE2PGkitQwEEXrkvJDoH041i1cjryA3XuLfKLB5sIdI3LgXy+ZwZn+GUby5/tkfTim2uJj8ndzmKNotcwhYczTJH4PWlmn0oQ3TQirua4mI20x+zjYUZJQo+nzU7vPnNt2OqSx8kClaD5RHrA0uXg1M3IQanWkVzWfsym29h/o5/34jA90Ny5Qp6senTcKNVFtH2lj3h5KIiNjSRPxxMA6IVdoCxWevB1bUmEjI59n6sp3/zQipHDEaNTwToDSlw5n4TtaiR/1hE7xmBRKAAA2XDgDQSvPnGwtqCrljqy2UXBZOVM6SZRgMeuIK5Q52b9mA0KKpwHSmQ15Pa2+nAJU81NsGBqrRREN1JyZWpthVaYGItsa4bQs6IXxni8cBxjggrSpJoeWijuNkNrDf6MxBiIkf1p5KzlZVM=
X-OriginatorOrg: microsoft.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6672d878-4d91-4111-2943-08d7e6f78a17
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 22 Apr 2020 19:58:34.6637
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 72f988bf-86f1-41af-91ab-2d7cd011db47
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 R+GUTL3f+uQ/v0SqGcPGpq3DETVK+RGtlvQwhW7ldgcUc0dg0lKudW9uBM6JghBPVHrH8sK65Yy/EJKnTm7qSQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BN6PR21MB0148
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series splits hyperv-tlfs.h into architecture independent and
architecture specific files so that the arch independent portion can
be shared between the x86/x64 and ARM64 code for Hyper-V.  While the
Hyper-V team has not released a version of the TLFS document that
clearly specifies which portions of the interface are arch independent,
we can make a fairly good assessment based on implementation work done
to support Linux guests on Hyper-V on ARM64, and on private communication
with the Hyper-V team.  Definitions are considered arch independent if
they are implemented by Hyper-V on both architectures (x86/x64 and ARM64),
even if they are currently needed by Linux code only on one architecture.

Many definitions in hyperv-tlfs.h have historically contained "X64" in the
name, which doesn't make sense for architecture independent definitions.
While many of the occurrences of "X64" have already been removed, some
still remain in definitions that should be arch independent. The
split removes the "X64" from the definitions so that the arch
independent hyper-tlfs.h has no occurrences of "X64". However, to
keep this patch set separate from a wider change in the names, aliases
are added in the x86/x64 specific hyperv-tlfs.h so that existing code
continues to compile.  The definitions can be fixed throughout the code
in a more incremental fashion in separate patches, and then the aliases
can be removed.

Where it is not clear if definitions are arch independent, they have been
kept in the x86/x64 specific file. The Hyper-V team is aiming to have a
version of the TLFS document covering ARM64 by the end of calendar 2020,
so additional definitions may be moved into the arch independent portion
after the new TLFS document is released.

The first two patches in the series clean up the existing hyperv-tlfs.h
file a bit by removing duplicate or unnecessary definitions so they are
not propagated across the split. The third patch does the split, and the
fourth patch adds new definitions that are needed on ARM64 but are generic.

These changes have no functional impact.

These patches are built against linux-next-20200415
---

Changes in v2:
* Improved definitions for Get/SetVpRegisters hypercalls in
  include/asm-generic/hyperv-tlfs.h in Patch 4 [Vitaly Kuznetsov]
* Updated MAINTAINERS with new file in Patch 3


Michael Kelley (4):
  KVM: x86: hyperv: Remove duplicate definitions of Reference TSC Page
  x86/hyperv: Remove HV_PROCESSOR_POWER_STATE #defines
  x86/hyperv: Split hyperv-tlfs.h into arch dependent and independent
    files
  asm-generic/hyperv: Add definitions for Get/SetVpRegister hypercalls

 MAINTAINERS                        |   1 +
 arch/x86/include/asm/hyperv-tlfs.h | 472 +++------------------------
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/hyperv.c              |   4 +-
 include/asm-generic/hyperv-tlfs.h  | 493 +++++++++++++++++++++++++++++
 5 files changed, 533 insertions(+), 439 deletions(-)
 create mode 100644 include/asm-generic/hyperv-tlfs.h
```
