#### [PATCH 1/2] KVM: arm64: PMU: Fix per-CPU access in preemptible context
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11645441
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C61031709
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 11:05:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEF0F20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 11:05:36 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1594033536;
	bh=pNwXVAMDXVJlIpm6TO8om9y6iGboItUmVHhsv43zIi0=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=mrHMpTcxm2v0SvTDsYLAQwi7gluZBQ83alrAOvdezoD2cfMysS68FsA0yt0NMklGR
	 O7TEg6hr2C4uQu1WKP2TMNZMvL3A4SpnGnazd+6TGNs6LG7LqlNVzcFtKuREz3XijH
	 uZQyS8ryF/hdnZIg71RjJc3DGYNmHDoebQ4enlcc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728878AbgGFLFf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 07:05:35 -0400
Received: from mail.kernel.org ([198.145.29.99]:57690 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728697AbgGFLFf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 07:05:35 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 767952073E;
        Mon,  6 Jul 2020 11:05:34 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1594033534;
        bh=pNwXVAMDXVJlIpm6TO8om9y6iGboItUmVHhsv43zIi0=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=YbQDW/lcnduuDKC8kaeWjsU5cTyH+Qwz4b/f+LWIOMadaiDAfbAp4ayIwKyy1YEF+
         QdSct6GVOwoeY4bmBgshAH0xCERJ6xxWC9IYm8v54KK1OtR9PX4iDw/PRh1zCf2ffZ
         6yCXO9WnwIVZ6AOCNmbzMAnSc44UxpbkSrkZ/zXM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jsOwG-009Qgb-UX; Mon, 06 Jul 2020 12:05:33 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andrew Scull <ascull@google.com>,
        Andrew Murray <amurray@thegoodpenguin.co.uk>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 1/2] KVM: arm64: PMU: Fix per-CPU access in preemptible
 context
Date: Mon,  6 Jul 2020 12:05:20 +0100
Message-Id: <20200706110521.1615794-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200706110521.1615794-1-maz@kernel.org>
References: <20200706110521.1615794-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, ascull@google.com,
 amurray@thegoodpenguin.co.uk, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 07da1ffaa137 ("KVM: arm64: Remove host_cpu_context
member from vcpu structure") has, by removing the host CPU
context pointer, exposed that kvm_vcpu_pmu_restore_guest
is called in preemptible contexts:

[  266.932442] BUG: using smp_processor_id() in preemptible [00000000] code: qemu-system-aar/779
[  266.939721] caller is debug_smp_processor_id+0x20/0x30
[  266.944157] CPU: 2 PID: 779 Comm: qemu-system-aar Tainted: G            E     5.8.0-rc3-00015-g8d4aa58b2fe3 #1374
[  266.954268] Hardware name: amlogic w400/w400, BIOS 2020.04 05/22/2020
[  266.960640] Call trace:
[  266.963064]  dump_backtrace+0x0/0x1e0
[  266.966679]  show_stack+0x20/0x30
[  266.969959]  dump_stack+0xe4/0x154
[  266.973338]  check_preemption_disabled+0xf8/0x108
[  266.977978]  debug_smp_processor_id+0x20/0x30
[  266.982307]  kvm_vcpu_pmu_restore_guest+0x2c/0x68
[  266.986949]  access_pmcr+0xf8/0x128
[  266.990399]  perform_access+0x8c/0x250
[  266.994108]  kvm_handle_sys_reg+0x10c/0x2f8
[  266.998247]  handle_exit+0x78/0x200
[  267.001697]  kvm_arch_vcpu_ioctl_run+0x2ac/0xab8

Note that the bug was always there, it is only the switch to
using percpu accessors that made it obvious.
The fix is to wrap these accesses in a preempt-disabled section,
so that we sample a coherent context on trap from the guest.

Fixes: 435e53fb5e21 ("arm64: KVM: Enable VHE support for :G/:H perf event modifiers")
Cc:: Andrew Murray <amurray@thegoodpenguin.co.uk>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/pmu.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM changes for Linux 5.8-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11646269
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 51880739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 17:15:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 391E32070C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 17:15:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CxicBgcS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729616AbgGFRP3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 13:15:29 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:25050 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729386AbgGFRP3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 13:15:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594055727;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=WIAp4BksQMI/icBTHgBCKYMTMos5fdTsYz6Un13kkXc=;
        b=CxicBgcSmeoHCXGkN008UBxAxkBOdRcDAI9X9WYRMr6kFu3jEbZvw6nDUxg/MpiyF5/iQK
        ZzSDNAK4SY0Zz8kctydpKX4g0v9H/DyhXLTCS2DIkSBjNrMUYMki+hOgd4OHyQM8SZSsDb
        VR22IfcfRaIb8+RoLP2/VtI7ykXgf2M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-414-Hr9AEiglOwy8YY02x3x5rg-1; Mon, 06 Jul 2020 13:15:25 -0400
X-MC-Unique: Hr9AEiglOwy8YY02x3x5rg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 44E78804001;
        Mon,  6 Jul 2020 17:15:24 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E39955C1B2;
        Mon,  6 Jul 2020 17:15:23 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.8-rc5
Date: Mon,  6 Jul 2020 13:15:23 -0400
Message-Id: <20200706171523.12441-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit e4553b4976d1178c13da295cb5c7b21f55baf8f9:

  KVM: VMX: Remove vcpu_vmx's defunct copy of host_pkru (2020-06-23 06:01:29 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 8038a922cf9af5266eaff29ce996a0d1b788fc0d:

  Merge tag 'kvmarm-fixes-5.8-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2020-07-06 13:05:38 -0400)

----------------------------------------------------------------
Bugfixes and a one-liner patch to silence sparse.

----------------------------------------------------------------

I'm going on vacation so my next pull request should be for rc8
or 5.8-final.  If something really bad comes up, you might get
KVM changes straight from architecture maintainers, but things
seems calm on both the 5.7 and 5.8 fronts so that should not
happen.

Thanks,

Paolo

Alexandru Elisei (1):
      KVM: arm64: Annotate hyp NMI-related functions as __always_inline

Andrew Jones (1):
      KVM: arm64: pvtime: Ensure task delay accounting is enabled

Andrew Scull (1):
      KVM: arm64: Stop clobbering x0 for HVC_SOFT_RESTART

Christian Borntraeger (1):
      KVM: s390: reduce number of IO pins to 1

Marc Zyngier (2):
      KVM: arm64: vgic-v4: Plug race between non-residency and v4.1 doorbell
      KVM: arm64: PMU: Fix per-CPU access in preemptible context

Paolo Bonzini (5):
      Merge tag 'kvm-s390-master-5.8-3' of git://git.kernel.org/.../kvms390/linux into kvm-master
      KVM: x86: bit 8 of non-leaf PDPEs is not reserved
      Merge tag 'kvmarm-fixes-5.8-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      kvm: use more precise cast and do not drop __user
      Merge tag 'kvmarm-fixes-5.8-3' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

Sean Christopherson (3):
      KVM: x86: Inject #GP if guest attempts to toggle CR4.LA57 in 64-bit mode
      KVM: x86: Mark CR4.TSD as being possibly owned by the guest
      KVM: VMX: Use KVM_POSSIBLE_CR*_GUEST_BITS to initialize guest/host masks

Steven Price (1):
      KVM: arm64: Fix kvm_reset_vcpu() return code being incorrect with SVE

Wanpeng Li (1):
      KVM: X86: Fix async pf caused null-ptr-deref

 arch/arm64/include/asm/arch_gicv3.h |  2 +-
 arch/arm64/include/asm/cpufeature.h |  2 +-
 arch/arm64/kvm/hyp-init.S           | 11 +++++++----
 arch/arm64/kvm/pmu.c                |  7 ++++++-
 arch/arm64/kvm/pvtime.c             | 15 ++++++++++++---
 arch/arm64/kvm/reset.c              | 10 +++++++---
 arch/arm64/kvm/vgic/vgic-v4.c       |  8 ++++++++
 arch/s390/include/asm/kvm_host.h    |  8 ++++----
 arch/x86/kvm/kvm_cache_regs.h       |  2 +-
 arch/x86/kvm/mmu/mmu.c              |  2 +-
 arch/x86/kvm/vmx/nested.c           |  4 ++--
 arch/x86/kvm/vmx/vmx.c              | 13 +++++--------
 arch/x86/kvm/x86.c                  |  5 +++++
 drivers/irqchip/irq-gic-v3-its.c    |  8 ++++++++
 virt/kvm/kvm_main.c                 |  3 ++-
 15 files changed, 70 insertions(+), 30 deletions(-)
```
#### [PATCH v3 01/17] KVM: arm64: Factor out stage 2 page table data from struct kvm
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11645661
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D8A2B60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 12:54:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD29C208D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 12:54:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1594040097;
	bh=HrLX06M6wTECV6EOA8uUREkgOt6d/jEJQV8nKpZYEJ8=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=0jQGB7pXCswGdFhRUMRzRCpgneET1brAykhitdImbGvkS28tjvHaW5Q0666+FZ1vx
	 OyyXk1GZWARSKYRBPmBISB3CsENU0llSCjBjCLFZJX2+tFfJ394oLDfEh9seMjG2cZ
	 9Z4JzGkjd7/NRPv8S3yv98d/PtDVlZKYShGmR6gw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729154AbgGFMy5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 08:54:57 -0400
Received: from mail.kernel.org ([198.145.29.99]:40550 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728973AbgGFMy4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 08:54:56 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1E44B20771;
        Mon,  6 Jul 2020 12:54:53 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1594040093;
        bh=HrLX06M6wTECV6EOA8uUREkgOt6d/jEJQV8nKpZYEJ8=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=Ko34VTJs/2T/RqgLLhgAWrHCfxctHhfh+gP+tkcJYNMcLXFYQWXm1QrdmXMq8nG5U
         m+TgfQAcpnLa60j/YGaN6vS4v9V4vV5JbG0GqD6msDiAfe9b/CPzxcT5N5ryQLpW4w
         XwOeifVYSQ/OYi9K9trlbTo4TzHyyPls0dtMHhcE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jsQe3-009SCo-GU; Mon, 06 Jul 2020 13:54:51 +0100
From: Marc Zyngier <maz@kernel.org>
To: Catalin Marinas <catalin.marinas@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        George Cherian <gcherian@marvell.com>,
        "Zengtao (B)" <prime.zeng@hisilicon.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v3 01/17] KVM: arm64: Factor out stage 2 page table data from
 struct kvm
Date: Mon,  6 Jul 2020 13:54:09 +0100
Message-Id: <20200706125425.1671020-2-maz@kernel.org>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20200706125425.1671020-1-maz@kernel.org>
References: <20200706125425.1671020-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: catalin.marinas@arm.com,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, andre.przywara@arm.com, christoffer.dall@arm.com,
 Dave.Martin@arm.com, jintack@cs.columbia.edu, alexandru.elisei@arm.com,
 gcherian@marvell.com, prime.zeng@hisilicon.com, ascull@google.com,
 will@kernel.org, mark.rutland@arm.com, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christoffer Dall <christoffer.dall@arm.com>

As we are about to reuse our stage 2 page table manipulation code for
shadow stage 2 page tables in the context of nested virtualization, we
are going to manage multiple stage 2 page tables for a single VM.

This requires some pretty invasive changes to our data structures,
which moves the vmid and pgd pointers into a separate structure and
change pretty much all of our mmu code to operate on this structure
instead.

The new structure is called struct kvm_s2_mmu.

There is no intended functional change by this patch alone.

Reviewed-by: James Morse <james.morse@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
[Designed data structure layout in collaboration]
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Co-developed-by: Marc Zyngier <maz@kernel.org>
[maz: Moved the last_vcpu_ran down to the S2 MMU structure as well]
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h        |   7 +-
 arch/arm64/include/asm/kvm_host.h       |  32 ++-
 arch/arm64/include/asm/kvm_mmu.h        |  16 +-
 arch/arm64/kvm/arm.c                    |  36 +--
 arch/arm64/kvm/hyp/include/hyp/switch.h |   4 +-
 arch/arm64/kvm/hyp/nvhe/switch.c        |   2 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c           |  33 ++-
 arch/arm64/kvm/hyp/vhe/switch.c         |   2 +-
 arch/arm64/kvm/hyp/vhe/tlb.c            |  26 +--
 arch/arm64/kvm/mmu.c                    | 280 +++++++++++++-----------
 10 files changed, 240 insertions(+), 198 deletions(-)

```
#### [PATCH] MIPS: KVM: Convert a fallthrough comment to fallthrough
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11644813
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2CF9492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 01:53:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14D072074F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 01:53:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="fin3r9Dj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728623AbgGFBxQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 5 Jul 2020 21:53:16 -0400
Received: from vultr.net.flygoat.com ([149.28.68.211]:40388 "EHLO
        vultr.net.flygoat.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728528AbgGFBxQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 5 Jul 2020 21:53:16 -0400
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id 64C721FEF9;
        Mon,  6 Jul 2020 01:45:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1593999947; bh=JUtweFfIfUaNiYWjrOM8eKxxOZSb4TtblpLjczU23ew=;
        h=From:To:Cc:Subject:Date:From;
        b=fin3r9Djg/W7oG7Nqju+dTO8ryvScgWU1OaLZNfrVmAOnm9tcP4hjbjx4Fs+9+k4b
         ZC9ZYnfwu2OiVq54JqtSFtAKT/YpWVhHl0HdPyeyfA+EbRujv4khPnKiX1Jd+J0ZPN
         PO0Vpggp611ezJW9SGCLO/H0cs6w9sV6iZxCekoSXaupHqYeZdTr32K375DOv1+l2V
         9cQRtnkXdsnI+pFTwZ+Zn261t1k4TCPCwCAYO7vBavgUvxbiuafOLuwhk9nzb8rbVL
         e9EneMkAS0Biu3AtEmKTx5UudS6a5XqBxiLbTW10Luabq3mwXCz6Aj3GmmjP0M2JnU
         C7hcQJ8uvFx/A==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: kvm@vger.kernel.org
Cc: chenhc@lemote.com, aleksandar.qemu.devel@gmail.com,
        linux-mips@vger.kernel.org, tsbogend@alpha.franken.de,
        Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH] MIPS: KVM: Convert a fallthrough comment to fallthrough
Date: Mon,  6 Jul 2020 09:45:34 +0800
Message-Id: <20200706014534.352509-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is a fallthrough comment being forgotten,
GCC complains about it:

arch/mips/kvm/emulate.c: In function kvm_mips_emulate_load:
arch/mips/kvm/emulate.c:1936:21: error: this statement may fall through
 1936 |   vcpu->mmio_needed = 1; /* unsigned */
      |   ~~~~~~~~~~~~~~~~~~^~~
arch/mips/kvm/emulate.c:1939:2: note: here
 1939 |  case lw_op:

Just fix it.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
---
 arch/mips/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/4] lib/vmalloc: fix pages count local variable to be size_t
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11646133
Return-Path: <SRS0=fXy1=AR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D06F613B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 16:43:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C0673206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  6 Jul 2020 16:43:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729695AbgGFQnf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 12:43:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56540 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729553AbgGFQnf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 6 Jul 2020 12:43:35 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 066GY641185664
        for <kvm@vger.kernel.org>; Mon, 6 Jul 2020 12:43:34 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 322ndvfqhp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 06 Jul 2020 12:43:34 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 066Ggcn7016894
        for <kvm@vger.kernel.org>; Mon, 6 Jul 2020 12:43:33 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 322ndvfqf4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 06 Jul 2020 12:43:33 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 066GQ4a0004634;
        Mon, 6 Jul 2020 16:43:27 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 322hd7tgve-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 06 Jul 2020 16:43:27 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 066GhPGZ60227738
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 6 Jul 2020 16:43:25 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7BAF111C04A;
        Mon,  6 Jul 2020 16:43:25 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0E89D11C054;
        Mon,  6 Jul 2020 16:43:25 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.9.164])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  6 Jul 2020 16:43:24 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, thuth@redhat.com, david@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/4] lib/vmalloc: fix pages count local
 variable to be size_t
Date: Mon,  6 Jul 2020 18:43:21 +0200
Message-Id: <20200706164324.81123-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200706164324.81123-1-imbrenda@linux.ibm.com>
References: <20200706164324.81123-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-06_15:2020-07-06,2020-07-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=0
 clxscore=1015 cotscore=-2147483648 mlxlogscore=999 impostorscore=0
 phishscore=0 lowpriorityscore=0 malwarescore=0 adultscore=0
 priorityscore=1501 bulkscore=0 spamscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007060120
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since size is of type size_t, size >> PAGE_SHIFT might still be too big
for a normal unsigned int.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 lib/vmalloc.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/9] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 160 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 196 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
