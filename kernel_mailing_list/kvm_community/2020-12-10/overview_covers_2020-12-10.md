

#### [PATCH 0/7] vfio: iommu_type1: Some fixes and optimization
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Dec 10 07:34:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11963585
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4ED21C433FE
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 07:39:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F142F23D23
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 07:39:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1733125AbgLJHgS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 02:36:18 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9573 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726267AbgLJHgS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 02:36:18 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cs5KN6PFMzM2xM;
        Thu, 10 Dec 2020 15:34:48 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.37) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.487.0; Thu, 10 Dec 2020 15:35:24 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>
CC: Joerg Roedel <joro@8bytes.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 0/7] vfio: iommu_type1: Some fixes and optimization
Date: Thu, 10 Dec 2020 15:34:18 +0800
Message-ID: <20201210073425.25960-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.37]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi folks,

This patch series aim to fix up or optimize some code about vfio
dirty log tracking.

patch   1: Optimize dirty log when unwind pin pages.
patch 2-3: Optimize promoting pinned_page_dirty_scope.
patch   4: Fix up dirty log missing when promote pinned_page_dirty_scope.
patch 5-7: Drop superfluous parameter "pgsize" of some functions.

Wish they improves the robustness of vfio dirty log tracking.

Thanks,
Keqian

Keqian Zhu (7):
  vfio: iommu_type1: Clear added dirty bit when unwind pin
  vfio: iommu_type1: Initially set the pinned_page_dirty_scope
  vfio: iommu_type1: Make an explicit "promote" semantic
  vfio: iommu_type1: Fix missing dirty page when promote pinned_scope
  vfio: iommu_type1: Drop parameter "pgsize" of
    vfio_dma_bitmap_alloc_all
  vfio: iommu_type1: Drop parameter "pgsize" of vfio_iova_dirty_bitmap.
  vfio: iommu_type1: Drop parameter "pgsize" of update_user_bitmap

 drivers/vfio/vfio_iommu_type1.c | 108 +++++++++++++++++++-------------
 1 file changed, 65 insertions(+), 43 deletions(-)
```
#### [PATCH v3 00/66] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Dec 10 15:58:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11965235
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56BA4C1B0E3
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 16:01:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17CEF23D39
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 16:01:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392189AbgLJQB3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 11:01:29 -0500
Received: from mail.kernel.org ([198.145.29.99]:59836 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2392107AbgLJQBM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 11:01:12 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1501523D50;
        Thu, 10 Dec 2020 16:00:30 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1knOMl-0008Di-V5; Thu, 10 Dec 2020 16:00:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH v3 00/66] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
 support
Date: Thu, 10 Dec 2020 15:58:56 +0000
Message-Id: <20201210160002.1407373-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, jintack@cs.columbia.edu, alexandru.elisei@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rework of the NV series that I posted 10 months ago[1], as a
lot of the KVM code has changed since, and the series apply anymore
(not that anybody really cares as the the HW is, as usual, made of
unobtainium...).

From the previous version:

- Integration with the new page-table code
- New exception injection code
- No more messing with the nVHE code
- No AArch32!!!!
- Rebased on v5.10-rc4 + kvmarm/next for 5.11

From a functionality perspective, you can expect a L2 guest to work,
but don't even think of L3, as we only partially emulate the
ARMv8.{3,4}-NV extensions themselves. Same thing for vgic, debug, PMU,
as well as anything that would require a Stage-1 PTW. What we want to
achieve is that with NV disabled, there is no performance overhead and
no regression.

The series is roughly divided in 5 parts: exception handling, memory
virtualization, interrupts and timers for ARMv8.3, followed by the
ARMv8.4 support. There are of course some dependencies, but you'll
hopefully get the gist of it.

For the most courageous of you, I've put out a branch[2]. Of course,
you'll need some userspace. Andre maintains a hacked version of
kvmtool[3] that takes a --nested option, allowing the guest to be
started at EL2. You can run the whole stack in the Foundation
model. Don't be in a hurry ;-).

And to be clear: although Jintack and Christoffer have written tons of
the stuff originaly, I'm the one responsible for breaking it!

[1] https://lore.kernel.org/r/20200211174938.27809-1-maz@kernel.org
[2] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-5.11.-WIP
[3] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5

Andre Przywara (1):
  KVM: arm64: nv: vgic: Allow userland to set VGIC maintenance IRQ

Christoffer Dall (15):
  KVM: arm64: nv: Introduce nested virtualization VCPU feature
  KVM: arm64: nv: Reset VCPU to EL2 registers if VCPU nested virt is set
  KVM: arm64: nv: Allow userspace to set PSR_MODE_EL2x
  KVM: arm64: nv: Add nested virt VCPU primitives for vEL2 VCPU state
  KVM: arm64: nv: Reset VMPIDR_EL2 and VPIDR_EL2 to sane values
  KVM: arm64: nv: Handle trapped ERET from virtual EL2
  KVM: arm64: nv: Emulate PSTATE.M for a guest hypervisor
  KVM: arm64: nv: Trap EL1 VM register accesses in virtual EL2
  KVM: arm64: nv: Only toggle cache for virtual EL2 when SCTLR_EL2
    changes
  KVM: arm64: nv: Implement nested Stage-2 page table walk logic
  KVM: arm64: nv: Unmap/flush shadow stage 2 page tables
  KVM: arm64: nv: arch_timer: Support hyp timer emulation
  KVM: arm64: nv: vgic: Emulate the HW bit in software
  KVM: arm64: nv: Add nested GICv3 tracepoints
  KVM: arm64: nv: Sync nested timer state with ARMv8.4

Jintack Lim (19):
  arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
  KVM: arm64: nv: Handle HCR_EL2.NV system register traps
  KVM: arm64: nv: Support virtual EL2 exceptions
  KVM: arm64: nv: Inject HVC exceptions to the virtual EL2
  KVM: arm64: nv: Trap SPSR_EL1, ELR_EL1 and VBAR_EL1 from virtual EL2
  KVM: arm64: nv: Trap CPACR_EL1 access in virtual EL2
  KVM: arm64: nv: Handle PSCI call via smc from the guest
  KVM: arm64: nv: Respect virtual HCR_EL2.TWX setting
  KVM: arm64: nv: Respect virtual CPTR_EL2.{TFP,FPEN} settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV bit setting
  KVM: arm64: nv: Respect virtual HCR_EL2.TVM and TRVM settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV1 bit setting
  KVM: arm64: nv: Emulate EL12 register accesses from the virtual EL2
  KVM: arm64: nv: Configure HCR_EL2 for nested virtualization
  KVM: arm64: nv: Introduce sys_reg_desc.forward_trap
  KVM: arm64: nv: Set a handler for the system instruction traps
  KVM: arm64: nv: Trap and emulate AT instructions from virtual EL2
  KVM: arm64: nv: Trap and emulate TLBI instructions from virtual EL2
  KVM: arm64: nv: Nested GICv3 Support

Marc Zyngier (31):
  KVM: arm64: nv: Add EL2 system registers to vcpu context
  KVM: arm64: nv: Add non-VHE-EL2->EL1 translation helpers
  KVM: arm64: nv: Handle virtual EL2 registers in
    vcpu_read/write_sys_reg()
  KVM: arm64: nv: Handle SPSR_EL2 specially
  KVM: arm64: nv: Handle HCR_EL2.E2H specially
  KVM: arm64: nv: Save/Restore vEL2 sysregs
  KVM: arm64: nv: Forward debug traps to the nested guest
  KVM: arm64: nv: Filter out unsupported features from ID regs
  KVM: arm64: nv: Hide RAS from nested guests
  KVM: arm64: nv: Support multiple nested Stage-2 mmu structures
  KVM: arm64: nv: Handle shadow stage 2 page faults
  KVM: arm64: nv: Restrict S2 RD/WR permissions to match the guest's
  KVM: arm64: nv: Fold guest's HCR_EL2 configuration into the host's
  KVM: arm64: nv: Add handling of EL2-specific timer registers
  KVM: arm64: nv: Load timer before the GIC
  KVM: arm64: nv: Don't load the GICv4 context on entering a nested
    guest
  KVM: arm64: nv: Implement maintenance interrupt forwarding
  KVM: arm64: nv: Allow userspace to request KVM_ARM_VCPU_NESTED_VIRT
  KVM: arm64: nv: Add handling of ARMv8.4-TTL TLB invalidation
  KVM: arm64: nv: Invalidate TLBs based on shadow S2 TTL-like
    information
  KVM: arm64: Allow populating S2 SW bits
  KVM: arm64: nv: Tag shadow S2 entries with nested level
  KVM: arm64: nv: Add include containing the VNCR_EL2 offsets
  KVM: arm64: Map VNCR-capable registers to a separate page
  KVM: arm64: nv: Move nested vgic state into the sysreg file
  KVM: arm64: Add ARMv8.4 Enhanced Nested Virt cpufeature
  KVM: arm64: nv: Synchronize PSTATE early on exit
  KVM: arm64: nv: Allocate VNCR page when required
  KVM: arm64: nv: Enable ARMv8.4-NV support
  KVM: arm64: nv: Fast-track 'InHost' exception returns
  KVM: arm64: nv: Fast-track EL1 TLBIs for VHE guests

 .../admin-guide/kernel-parameters.txt         |    4 +
 .../virt/kvm/devices/arm-vgic-v3.rst          |   12 +-
 arch/arm64/include/asm/cpucaps.h              |    2 +
 arch/arm64/include/asm/esr.h                  |    6 +
 arch/arm64/include/asm/kvm_arm.h              |   28 +-
 arch/arm64/include/asm/kvm_asm.h              |    4 +
 arch/arm64/include/asm/kvm_emulate.h          |  145 +-
 arch/arm64/include/asm/kvm_host.h             |  175 ++-
 arch/arm64/include/asm/kvm_hyp.h              |    2 +
 arch/arm64/include/asm/kvm_mmu.h              |   17 +-
 arch/arm64/include/asm/kvm_nested.h           |  152 ++
 arch/arm64/include/asm/kvm_pgtable.h          |   10 +
 arch/arm64/include/asm/sysreg.h               |  104 +-
 arch/arm64/include/asm/vncr_mapping.h         |   73 +
 arch/arm64/include/uapi/asm/kvm.h             |    2 +
 arch/arm64/kernel/cpufeature.c                |   35 +
 arch/arm64/kvm/Makefile                       |    4 +-
 arch/arm64/kvm/arch_timer.c                   |  189 ++-
 arch/arm64/kvm/arm.c                          |   34 +-
 arch/arm64/kvm/at.c                           |  231 ++++
 arch/arm64/kvm/emulate-nested.c               |  186 +++
 arch/arm64/kvm/guest.c                        |    6 +
 arch/arm64/kvm/handle_exit.c                  |   81 +-
 arch/arm64/kvm/hyp/exception.c                |   44 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h       |   31 +-
 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h    |   28 +-
 arch/arm64/kvm/hyp/nvhe/switch.c              |   10 +-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c           |    2 +-
 arch/arm64/kvm/hyp/pgtable.c                  |    6 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c               |    2 +-
 arch/arm64/kvm/hyp/vhe/switch.c               |  207 ++-
 arch/arm64/kvm/hyp/vhe/sysreg-sr.c            |  125 +-
 arch/arm64/kvm/hyp/vhe/tlb.c                  |   83 ++
 arch/arm64/kvm/inject_fault.c                 |   62 +-
 arch/arm64/kvm/mmu.c                          |  183 ++-
 arch/arm64/kvm/nested.c                       |  908 ++++++++++++
 arch/arm64/kvm/reset.c                        |   14 +-
 arch/arm64/kvm/sys_regs.c                     | 1226 ++++++++++++++++-
 arch/arm64/kvm/sys_regs.h                     |    6 +
 arch/arm64/kvm/trace_arm.h                    |   65 +-
 arch/arm64/kvm/vgic/vgic-init.c               |   30 +
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   22 +
 arch/arm64/kvm/vgic/vgic-nested-trace.h       |  137 ++
 arch/arm64/kvm/vgic/vgic-v3-nested.c          |  240 ++++
 arch/arm64/kvm/vgic/vgic-v3.c                 |   39 +-
 arch/arm64/kvm/vgic/vgic.c                    |   44 +
 arch/arm64/kvm/vgic/vgic.h                    |   10 +
 include/kvm/arm_arch_timer.h                  |    7 +
 include/kvm/arm_vgic.h                        |   16 +
 tools/arch/arm/include/uapi/asm/kvm.h         |    1 +
 50 files changed, 4890 insertions(+), 160 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/include/asm/vncr_mapping.h
 create mode 100644 arch/arm64/kvm/at.c
 create mode 100644 arch/arm64/kvm/emulate-nested.c
 create mode 100644 arch/arm64/kvm/nested.c
 create mode 100644 arch/arm64/kvm/vgic/vgic-nested-trace.h
 create mode 100644 arch/arm64/kvm/vgic/vgic-v3-nested.c
```
#### [PATCH v5 00/34] SEV-ES hypervisor support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Thu Dec 10 17:06:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11965689
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 359D0C4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:08:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D2A10221E3
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 17:08:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392477AbgLJRIe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 12:08:34 -0500
Received: from mail-bn8nam12on2064.outbound.protection.outlook.com
 ([40.107.237.64]:38097
        "EHLO NAM12-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392453AbgLJRIb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 12:08:31 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=VQrniI5wkHDUSp2gGCi1sq0E9pAG8JeiXsZDnKmJlGWoJGx7B9oCze4xzJ9t6iLnnoo17Vo5OOF1dpPksLHL8Gq3B3C1hm6cSuMoIC35oH5GrfB3Mbe2xlNktTjI7tT3yuuvvtwX7Kfdgo82cI77FkFN1G5GpKdDb5qK0xBgkJ/erIjuJa9LoB1aNrmsZHVcmzE4FvvsJqw08iCtNmkSmp17WyQ/upcb4wIIzXx8SubYW+Ehe9oJtu5DZO8wmfjiBRmUElJQFH45+WTU6hIAx1f7z66cemFGdtMJvMBO5W2Ch7lAT7bPpSqecymUr1h/u6OtFthoV8v+wxPVpJBS+g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z/DvzQL9xKzyTXbZYKjvi8n7XHaRooTRZc8KiicSfMk=;
 b=HEx9jwOfssW6Ol6jZ3DEX9OZwHdiUWJxovkYFNzVSiZSmUqRmuqOOSvp7l7miQNlyG4Lqs1tATYO11CvFenIWHei9hB/4hBMZIIyp1Dqz/NhnuBwbVdHOcfNKUMEiR/gYEikK5JV4SL424ETOrWold8LYHPZiO2eu6YIXXbsyjAwWMVKu+F2cbNt6+YufX/Kk8ZQanrk7Nj7VE5W/zWa+5tCAfhiPG0UoPm4g9ZwszndcvkJ0k2KVexrlr9ANEG3KDbm0+mQDECG2peYSdCNTxsf8dzuiv5UkDz10ULI1V/UoB1yXe4pZbejTf/i5Gc2NcKnLiOzTMPkyZuh+T4DyA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z/DvzQL9xKzyTXbZYKjvi8n7XHaRooTRZc8KiicSfMk=;
 b=3VDqiisRQZSohjJsIhdfpjAAmdDcddDmWXybZ4A9YfxIEjdn7nuA+FQcpBu/o7itB9dJMV5EyqzRogJ9Tt1BLAlG3gTs1vfHfpGSTz/1O2l/bmdUQThAuVB2mrHb5I/7HNZ7kKtXHyf1+LDRcPxm4lX3/8Liuf9NIevxD6RevgE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR12MB1493.namprd12.prod.outlook.com (2603:10b6:910:11::7) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12; Thu, 10 Dec
 2020 17:07:34 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d%8]) with mapi id 15.20.3632.021; Thu, 10 Dec 2020
 17:07:34 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v5 00/34] SEV-ES hypervisor support
Date: Thu, 10 Dec 2020 11:06:44 -0600
Message-Id: <cover.1607620037.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH0PR03CA0002.namprd03.prod.outlook.com
 (2603:10b6:610:b0::7) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 CH0PR03CA0002.namprd03.prod.outlook.com (2603:10b6:610:b0::7) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Thu, 10 Dec 2020 17:07:33 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 98aad429-7c2f-4a96-6c06-08d89d2e166f
X-MS-TrafficTypeDiagnostic: CY4PR12MB1493:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR12MB1493660C2358559FA8C1D596ECCB0@CY4PR12MB1493.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1417;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 LLERGHvM9ZExwdXp+I4HubkiwtLmjd5QlaWuRrRkLO19Or5S28qKhNaKqxMQ0+eLP3ThyW1UMqI0Yy2lce7p1vAOGD8DGpvkQDuJNHvcyiP46AayBxoIsNbyn+pN165WsGej2hgwFnLXvwlImxsc8j8ABE4D+jTW5EH58LZvZnHCdsQ1hoz6hJ6yBmk/uYY9YN/XSbedWrm05365lxeeqiX9bUd/1iTPWEMPBnSUFytnFsZz2vNqFum92IzDUDebxXr1apLVI2OZdYeNHSFcZ31rv3fa7DV5RqNEB48jlvgNMrUargOP9nAGXkhK8smjJ7UXth1upHhwYyy9wFPAUrTK6WxOoNFwayDfS28XO8ZmwXsUSSeHBM+OuNrDd4En8EcPssqA1euxH6h0OAr1cH1tklRgdIH7Qw9mHvpIdRuYn35GeYBFNnav1beK6ZEiGblTlzCrZz63ysM+K7UovA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(376002)(136003)(366004)(34490700003)(508600001)(7416002)(26005)(956004)(6486002)(2616005)(54906003)(7696005)(83380400001)(16526019)(66946007)(966005)(8936002)(186003)(52116002)(5660300002)(66476007)(8676002)(36756003)(86362001)(4326008)(6666004)(66556008)(2906002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 9tS0+3cs7vc1LNHkpGgwrZTt9MYe9s++5Wm2yadtu//lWbcmjR2hK1NZkcfDZpx76CYLbsxwsSHI9z9syv0A7BNNz0kJEbT9bY8s2teezClEymSpdmpv8c4ggiolyqHXuFVV98wbFqbQaDwGx06a18J2rf7cQKf2ZqkTvK3yO2ptV6TMgojvIysrj8JR6xAhAerNVlZy6cV4KOMb5EIEp0gbNt9hnyhKwqvI5J1WwPjEzM8S1Tee2PYue7mcs3kh9uDpaTtFGiDPhATl6kOCSZ5Iqd+llB2VwBlGoSy0ebitiYdIN7+7MX029QF6E3sTgAq1iXTQa7izNRZRBrlxi+XGAyhAFmPo41xfHHPUaIeUu8WRnt+EErq2HaK5i6eTZkreAM3NkqtwOt1rkLza5EvIMm8zMl/VMmoZ7oZ932oXx1nnGWkH4fIwChwl7KYYucS1/H5UcWY3OT6tD2b8NGDoJyKNJU7IlcV5vlxh+VbmK4wxH3mqk0hpbIe+G7X5gIpHvMGj9HWbP6tlByyCLZZvMTpQ5p7NuYI+NocjkR3w5JUU9aMs5FHj/i8FUG0I7CsGt/oTBOtmw8qcW9zVbwFmFnWzsALbyXB3LWpD0nZonSJwtWhHvxIohmki5n18TBYLlZYyXmX774KbMbyw4sHa/TfUHJnnZJoOmHegfl+l7O8LwBBVv1sVc3b27PiuQnm+Fgc6bhcdK8ZcF5T0ZmNZyQjEpvkJxNMpbWJ4k1yBHfpRA/mh5WwM3HeC6CgYwkeMzk29F6+RWkSwI2Q4tMAmHb9KJCKFX6ni0Dx05I5Ud3USQJMA4ORuouYtLlA0LlmRqFpwNkIS2c6Bz14Xe9KGxB9DGgUigGUDzVr3W77liEChNemQB+3laZxjtwNslVoAv5PHdPj/k2JqeKkVj123esiMSPGuLHcmouUJbr1OiBhytLAwD5uwQfLNOmfGUkHdL8RoLQeJx/3h/v66C7NmOcZSN8+ovl+XN1XRshIVkXNMkM0qaQmqpLhI+gTH
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Dec 2020 17:07:34.2742
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 98aad429-7c2f-4a96-6c06-08d89d2e166f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 crrh3Iamfq9Azl3J9VNBBtaZFS5/Zllp33FB2TZ3kDlWjH2EVwDUIS8hijtV7kUNX0qbGV/NutHb2mBGsi+6hA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR12MB1493
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for running SEV-ES guests under KVM.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

Under SEV-ES, a vCPU save area (VMSA) must be encrypted. SVM is updated to
build the initial VMSA and then encrypt it before running the guest. Once
encrypted, it must not be modified by the hypervisor. Modification of the
VMSA will result in the VMRUN instruction failing with a SHUTDOWN exit
code. KVM must support the VMGEXIT exit code in order to perform the
necessary functions required of the guest. The GHCB is used to exchange
the information needed by both the hypervisor and the guest.

Register data from the GHCB is copied into the KVM register variables and
accessed as usual during handling of the exit. Upon return to the guest,
updated registers are copied back to the GHCB for the guest to act upon.

There are changes to some of the intercepts that are needed under SEV-ES.
For example, CR0 writes cannot be intercepted, so the code needs to ensure
that the intercept is not enabled during execution or that the hypervisor
does not try to read the register as part of exit processing. Another
example is shutdown processing, where the vCPU cannot be directly reset.

Support is added to handle VMGEXIT events and implement the GHCB protocol.
This includes supporting standard exit events, like a CPUID instruction
intercept, to new support, for things like AP processor booting. Much of
the existing SVM intercept support can be re-used by setting the exit
code information from the VMGEXIT and calling the appropriate intercept
handlers.

Finally, to launch and run an SEV-ES guest requires changes to the vCPU
initialization, loading and execution.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
---

These patches are based on the KVM queue branch:
https://git.kernel.org/pub/scm/virt/kvm/kvm.git queue

dc924b062488 ("KVM: SVM: check CR4 changes against vcpu->arch")

A version of the tree can also be found at:
https://github.com/AMDESE/linux/tree/sev-es-v5
 This tree has one addition patch that is not yet part of the queue
 tree that is required to run any SEV guest:
 [PATCH] KVM: x86: adjust SEV for commit 7e8e6eed75e
 https://lore.kernel.org/kvm/20201130143959.3636394-1-pbonzini@redhat.com/

Changes from v4:
- Updated the tracking support for CR0/CR4

Changes from v3:
- Some krobot fixes.
- Some checkpatch cleanups.

Changes from v2:
- Update the freeing of the VMSA page to account for the encrypted memory
  cache coherency feature as well as the VM page flush feature.
- Update the GHCB dump function with a bit more detail.
- Don't check for RAX being present as part of a string IO operation.
- Include RSI when syncing from GHCB to support KVM hypercall arguments.
- Add GHCB usage field validation check.

Changes from v1:
- Removed the VMSA indirection support:
  - On LAUNCH_UPDATE_VMSA, sync traditional VMSA over to the new SEV-ES
    VMSA area to be encrypted.
  - On VMGEXIT VMEXIT, directly copy valid registers into vCPU arch
    register array from GHCB. On VMRUN (following a VMGEXIT), directly
    copy dirty vCPU arch registers to GHCB.
  - Removed reg_read_override()/reg_write_override() KVM ops.
- Added VMGEXIT exit-reason validation.
- Changed kvm_vcpu_arch variable vmsa_encrypted to guest_state_protected
- Updated the tracking support for EFER/CR0/CR4/CR8 to minimize changes
  to the x86.c code
- Updated __set_sregs to not set any register values (previously supported
  setting the tracked values of EFER/CR0/CR4/CR8)
- Added support for reporting SMM capability at the VM-level. This allows
  an SEV-ES guest to indicate SMM is not supported
- Updated FPU support to check for a guest FPU save area before using it.
  Updated SVM to free guest FPU for an SEV-ES guest during KVM create_vcpu
  op.
- Removed changes to the kvm_skip_emulated_instruction()
- Added VMSA validity checks before invoking LAUNCH_UPDATE_VMSA
- Minor code restructuring in areas for better readability

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>

Tom Lendacky (34):
  x86/cpu: Add VM page flush MSR availablility as a CPUID feature
  KVM: SVM: Remove the call to sev_platform_status() during setup
  KVM: SVM: Add support for SEV-ES capability in KVM
  KVM: SVM: Add GHCB accessor functions for retrieving fields
  KVM: SVM: Add support for the SEV-ES VMSA
  KVM: x86: Mark GPRs dirty when written
  KVM: SVM: Add required changes to support intercepts under SEV-ES
  KVM: SVM: Prevent debugging under SEV-ES
  KVM: SVM: Do not allow instruction emulation under SEV-ES
  KVM: SVM: Cannot re-initialize the VMCB after shutdown with SEV-ES
  KVM: SVM: Prepare for SEV-ES exit handling in the sev.c file
  KVM: SVM: Add initial support for a VMGEXIT VMEXIT
  KVM: SVM: Create trace events for VMGEXIT processing
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
  KVM: SVM: Create trace events for VMGEXIT MSR protocol processing
  KVM: SVM: Support MMIO for an SEV-ES guest
  KVM: SVM: Support string IO operations for an SEV-ES guest
  KVM: SVM: Add support for EFER write traps for an SEV-ES guest
  KVM: SVM: Add support for CR0 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR4 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR8 write traps for an SEV-ES guest
  KVM: x86: Update __get_sregs() / __set_sregs() to support SEV-ES
  KVM: SVM: Do not report support for SMM for an SEV-ES guest
  KVM: SVM: Guest FPU state save/restore not needed for SEV-ES guest
  KVM: SVM: Add support for booting APs for an SEV-ES guest
  KVM: SVM: Add NMI support for an SEV-ES guest
  KVM: SVM: Set the encryption mask for the SVM host save area
  KVM: SVM: Update ASID allocation to support SEV-ES guests
  KVM: SVM: Provide support for SEV-ES vCPU creation/loading
  KVM: SVM: Provide support for SEV-ES vCPU loading
  KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
  KVM: SVM: Provide support to launch and run an SEV-ES guest

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/include/asm/kvm_host.h    |  12 +-
 arch/x86/include/asm/msr-index.h   |   1 +
 arch/x86/include/asm/svm.h         |  40 +-
 arch/x86/include/uapi/asm/svm.h    |  28 +
 arch/x86/kernel/cpu/scattered.c    |   1 +
 arch/x86/kernel/cpu/vmware.c       |  12 +-
 arch/x86/kvm/Kconfig               |   3 +-
 arch/x86/kvm/kvm_cache_regs.h      |  51 +-
 arch/x86/kvm/svm/sev.c             | 933 +++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c             | 446 +++++++++++---
 arch/x86/kvm/svm/svm.h             | 166 ++++-
 arch/x86/kvm/svm/vmenter.S         |  50 ++
 arch/x86/kvm/trace.h               |  97 +++
 arch/x86/kvm/vmx/vmx.c             |   6 +-
 arch/x86/kvm/x86.c                 | 344 +++++++++--
 arch/x86/kvm/x86.h                 |   9 +
 17 files changed, 1962 insertions(+), 238 deletions(-)


base-commit: dc924b062488a0376aae41d3e0a27dc99f852a5e
```
#### [PATCH v5 00/34] SEV-ES hypervisor support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Thu Dec 10 17:09:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11965861
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 44FF8C4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:07:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B81923C44
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 18:07:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392575AbgLJRLR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 12:11:17 -0500
Received: from mail-dm6nam11on2069.outbound.protection.outlook.com
 ([40.107.223.69]:37494
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392493AbgLJRLN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 12:11:13 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Ml5ny42DvJmYfJmV5VdrSlL1suoYjkCCiuP0INDLUOSn9ynj74Uh2CE4qPnCFG8lFISx0y6xTzLVgMQYWQ58VzX4BCcDrQrZQm/YFP2eT7pgmZwdx4O3+8xeP1voS10xdHXmpdlUnrQEAU9dkDj63uH5bl9kZTwwy5LA1GY8yxxzkQo+gY3mtdpv8w1clNAH86d5v+a/uzde6iEM/vPTex+A6q6A9Ka8TjKU8zpQWqY14f3EgBGw7qIBAiim3gSlOXmaskAl15xK/IpR13YS2Os2WO0RcuT+6a/7ibjBgjELOrCiDK3y5J258I6ryp5JDN8VPfe5Vdh4rX0ATZqUyw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z/DvzQL9xKzyTXbZYKjvi8n7XHaRooTRZc8KiicSfMk=;
 b=PkHbTBkn7Wmurwta4YpdW5zz3+eH3R5P3n/5jD5pvFVi2kqQykDXHQfJgLmPDdyv+Kyqx8+Yimpd/Jdt775P2CPyNqHXZd82omMAnLO0XVDTPT5zf9cWvZwUi3Ec9dZO0l+j7nVcpXE/6GAWkCjd2DPk0SzZ11ZmGloRJxMMGYCyHPYznePWkr76XqoAGwyLRV0QAsTI8+6xGkPzEtYV8CgjErG/Ny/7jshrMP3/TAj8ZIWXK+DW2GcP2tGuY6Ioj0qoSLOs3aJxB1UlK2YTCMI2b+74XQLgCv5bG+9oYy8/nkm7Cwtz0LtPdyAqCUuSGeGokBURRZaAoO7jJiADNw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Z/DvzQL9xKzyTXbZYKjvi8n7XHaRooTRZc8KiicSfMk=;
 b=k8zyidoqk3Da59srDb3AuzuPYCjOQTN8nzYjZUy9CxV+XE/d1pGmJrab4I0Fn7nnWbNTC860dfP7V4MrwicVl5rZKavvm6rkYUHPclF3qcqFDNpUx/SH0jUcUYeqIBKvGdtLnTWiICxrtGXrALdH/YKu/wyDZQj/si9Eu0K5sSY=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1352.namprd12.prod.outlook.com (2603:10b6:903:3a::13)
 by CY4PR1201MB0168.namprd12.prod.outlook.com (2603:10b6:910:1d::9) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3632.22; Thu, 10 Dec
 2020 17:10:17 +0000
Received: from CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d]) by CY4PR12MB1352.namprd12.prod.outlook.com
 ([fe80::a10a:295e:908d:550d%8]) with mapi id 15.20.3632.021; Thu, 10 Dec 2020
 17:10:17 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v5 00/34] SEV-ES hypervisor support
Date: Thu, 10 Dec 2020 11:09:35 -0600
Message-Id: <cover.1607620209.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: CH0PR04CA0021.namprd04.prod.outlook.com
 (2603:10b6:610:76::26) To CY4PR12MB1352.namprd12.prod.outlook.com
 (2603:10b6:903:3a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 CH0PR04CA0021.namprd04.prod.outlook.com (2603:10b6:610:76::26) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Thu, 10 Dec 2020 17:10:16 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: a9866072-873b-4415-6ffb-08d89d2e77c0
X-MS-TrafficTypeDiagnostic: CY4PR1201MB0168:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR1201MB016863C27047549C41B29B1DECCB0@CY4PR1201MB0168.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:1417;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 jMf3R6//vSHxSn62G/fd0pcuJeRv2Mhi7bX0noA/oGepm10ZRCLwCKqi8maKbmEl3yZHrGVxOMmzGjDQifP7qflne0EImLS8hNX+a0xEKVla7KncL3VA3+F0wSl9iXHE2jpus8K0u8nkrLHqYDeFhuOXHCIFLuxZ9Icr4ZKwx7TFQWtsKXfdF2hySMJKjzXKFdYSYyayeiI1FBLR86+ehkKaYtyKgwqaJUE3jkTTrVtzwkYVe2J98QNGWESrqWrSFZaJhTCe6W19apiedMGZ4iv/sGCnWKJvr8j17zKa63a+Haqe2duJaGJeyKGFWp7J8og84QvvUK6n0XtaAX1KRl04tVBZfPN6mamaxzjZh899kEm2xkR/vP9WwryZiH0kRf7xoJO+mEjRlz8o3U2ZTwghFEZoQfk4Iw9HznhxbUtBBPYijBSlsLSOOMmsj5rIWd9zspPfEztvBgTss2cnBg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1352.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(136003)(346002)(376002)(36756003)(8676002)(6486002)(4326008)(66476007)(86362001)(7416002)(66946007)(7696005)(54906003)(6666004)(26005)(16526019)(34490700003)(66556008)(8936002)(83380400001)(966005)(186003)(2906002)(2616005)(52116002)(956004)(508600001)(5660300002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 jZtloFjBhIhNgk15jS037ybZYay4E2M65Os1ANL6lbsjmxj2EhfKGFuoItI/EIVw/hcqQJWim3+rZN2yicDeybKeRlrPS8WpvwXsUSZlC8NVJJw6PtFNcaP4tMC9xHY8/YRyaiqdN00/xwM3Hjpc27Oh4zZDuXpMK3VzWNIroWBgNz2jGuvBjrZkYYndAUXgTTBloQ6MkT0HPVcwm6ZlGLMx4SzlvIZ7JW4hubdnCZkwtF2qQQRR7l4/pahPKI9+cJDbCB+r5l+MXjqZVABAYmvMd0pMXTTOZ78qJbp80Y5fdBkXh8q3YeGuJIgg+kl4H8o/5JzXRfNWnyhyRY5yV+Qd0XOXVIwc7PHS8+TEJSALgQmb/nFhloT750ZOdFzYL5Ra1JI811FduXAyMvRF8UudIAMrqwb50fY9eQhnZMjOEW5w/Uh0J68zq7n+y8i4QoO0sTAAmSzKuo/IR48ez26Y0coGjdiQ5Py+MMhGtFfnkTes5aTdwT+Gp530oeOvshToCa8Xeo7719t4dn4tvXK/2DpTdLaJBp9qZUDkY5hOgDj5S9gIAkTSpL2apWSr7u8Xvczfv8SDXMWYsP3nrGGWVKWBRDWfbg+sLp3LwL5N3X+C+iXwDC4qT0LTeKmledQdqwbQ5JvJ9fdLE8MvLmT9m/uBY/FQ/sSSoCwL/6Euzyt+TFNLf3UscpgcrrE1pupynnAIsGtui/CORv1VhH1fKfEef8VQ5qfXPEbokY76SMTvZ9MxrU92kNtWKl+2tEksXw5lHcAHSwS5JQti3EDq1u2lTKSXP0DVv0ivuAWA73bMsMAMDk7C2RUO/yckMbAKgrJPXvhRqGEJh95uipuDk6s1hoXaKrohpdU1Mh277rnDng9dQe8jri2XXFMtqttSBQUrQX5LxGwpZyqIrEV9zrHN+zIEQ63/bf9MWMVptmkpppQVoX3rU4KuWhKB/fVn721aX0aCpj8004B/Mh/jsp5JEsv/GxfQHKmx2VT2s1d1T47t3uwd65n4kUQg
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1352.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 10 Dec 2020 17:10:17.5432
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 a9866072-873b-4415-6ffb-08d89d2e77c0
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 xdGcQu06biRhMXdx+YW3a70Hs3Mi1u3R+izdJRIh7nD5PCpMgDO13KnzFThSmGy8fSoKEcEQwdLvK9H2DDBXxQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR1201MB0168
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for running SEV-ES guests under KVM.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

Under SEV-ES, a vCPU save area (VMSA) must be encrypted. SVM is updated to
build the initial VMSA and then encrypt it before running the guest. Once
encrypted, it must not be modified by the hypervisor. Modification of the
VMSA will result in the VMRUN instruction failing with a SHUTDOWN exit
code. KVM must support the VMGEXIT exit code in order to perform the
necessary functions required of the guest. The GHCB is used to exchange
the information needed by both the hypervisor and the guest.

Register data from the GHCB is copied into the KVM register variables and
accessed as usual during handling of the exit. Upon return to the guest,
updated registers are copied back to the GHCB for the guest to act upon.

There are changes to some of the intercepts that are needed under SEV-ES.
For example, CR0 writes cannot be intercepted, so the code needs to ensure
that the intercept is not enabled during execution or that the hypervisor
does not try to read the register as part of exit processing. Another
example is shutdown processing, where the vCPU cannot be directly reset.

Support is added to handle VMGEXIT events and implement the GHCB protocol.
This includes supporting standard exit events, like a CPUID instruction
intercept, to new support, for things like AP processor booting. Much of
the existing SVM intercept support can be re-used by setting the exit
code information from the VMGEXIT and calling the appropriate intercept
handlers.

Finally, to launch and run an SEV-ES guest requires changes to the vCPU
initialization, loading and execution.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
---

These patches are based on the KVM queue branch:
https://git.kernel.org/pub/scm/virt/kvm/kvm.git queue

dc924b062488 ("KVM: SVM: check CR4 changes against vcpu->arch")

A version of the tree can also be found at:
https://github.com/AMDESE/linux/tree/sev-es-v5
 This tree has one addition patch that is not yet part of the queue
 tree that is required to run any SEV guest:
 [PATCH] KVM: x86: adjust SEV for commit 7e8e6eed75e
 https://lore.kernel.org/kvm/20201130143959.3636394-1-pbonzini@redhat.com/

Changes from v4:
- Updated the tracking support for CR0/CR4

Changes from v3:
- Some krobot fixes.
- Some checkpatch cleanups.

Changes from v2:
- Update the freeing of the VMSA page to account for the encrypted memory
  cache coherency feature as well as the VM page flush feature.
- Update the GHCB dump function with a bit more detail.
- Don't check for RAX being present as part of a string IO operation.
- Include RSI when syncing from GHCB to support KVM hypercall arguments.
- Add GHCB usage field validation check.

Changes from v1:
- Removed the VMSA indirection support:
  - On LAUNCH_UPDATE_VMSA, sync traditional VMSA over to the new SEV-ES
    VMSA area to be encrypted.
  - On VMGEXIT VMEXIT, directly copy valid registers into vCPU arch
    register array from GHCB. On VMRUN (following a VMGEXIT), directly
    copy dirty vCPU arch registers to GHCB.
  - Removed reg_read_override()/reg_write_override() KVM ops.
- Added VMGEXIT exit-reason validation.
- Changed kvm_vcpu_arch variable vmsa_encrypted to guest_state_protected
- Updated the tracking support for EFER/CR0/CR4/CR8 to minimize changes
  to the x86.c code
- Updated __set_sregs to not set any register values (previously supported
  setting the tracked values of EFER/CR0/CR4/CR8)
- Added support for reporting SMM capability at the VM-level. This allows
  an SEV-ES guest to indicate SMM is not supported
- Updated FPU support to check for a guest FPU save area before using it.
  Updated SVM to free guest FPU for an SEV-ES guest during KVM create_vcpu
  op.
- Removed changes to the kvm_skip_emulated_instruction()
- Added VMSA validity checks before invoking LAUNCH_UPDATE_VMSA
- Minor code restructuring in areas for better readability

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>

Tom Lendacky (34):
  x86/cpu: Add VM page flush MSR availablility as a CPUID feature
  KVM: SVM: Remove the call to sev_platform_status() during setup
  KVM: SVM: Add support for SEV-ES capability in KVM
  KVM: SVM: Add GHCB accessor functions for retrieving fields
  KVM: SVM: Add support for the SEV-ES VMSA
  KVM: x86: Mark GPRs dirty when written
  KVM: SVM: Add required changes to support intercepts under SEV-ES
  KVM: SVM: Prevent debugging under SEV-ES
  KVM: SVM: Do not allow instruction emulation under SEV-ES
  KVM: SVM: Cannot re-initialize the VMCB after shutdown with SEV-ES
  KVM: SVM: Prepare for SEV-ES exit handling in the sev.c file
  KVM: SVM: Add initial support for a VMGEXIT VMEXIT
  KVM: SVM: Create trace events for VMGEXIT processing
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
  KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
  KVM: SVM: Create trace events for VMGEXIT MSR protocol processing
  KVM: SVM: Support MMIO for an SEV-ES guest
  KVM: SVM: Support string IO operations for an SEV-ES guest
  KVM: SVM: Add support for EFER write traps for an SEV-ES guest
  KVM: SVM: Add support for CR0 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR4 write traps for an SEV-ES guest
  KVM: SVM: Add support for CR8 write traps for an SEV-ES guest
  KVM: x86: Update __get_sregs() / __set_sregs() to support SEV-ES
  KVM: SVM: Do not report support for SMM for an SEV-ES guest
  KVM: SVM: Guest FPU state save/restore not needed for SEV-ES guest
  KVM: SVM: Add support for booting APs for an SEV-ES guest
  KVM: SVM: Add NMI support for an SEV-ES guest
  KVM: SVM: Set the encryption mask for the SVM host save area
  KVM: SVM: Update ASID allocation to support SEV-ES guests
  KVM: SVM: Provide support for SEV-ES vCPU creation/loading
  KVM: SVM: Provide support for SEV-ES vCPU loading
  KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
  KVM: SVM: Provide support to launch and run an SEV-ES guest

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/include/asm/kvm_host.h    |  12 +-
 arch/x86/include/asm/msr-index.h   |   1 +
 arch/x86/include/asm/svm.h         |  40 +-
 arch/x86/include/uapi/asm/svm.h    |  28 +
 arch/x86/kernel/cpu/scattered.c    |   1 +
 arch/x86/kernel/cpu/vmware.c       |  12 +-
 arch/x86/kvm/Kconfig               |   3 +-
 arch/x86/kvm/kvm_cache_regs.h      |  51 +-
 arch/x86/kvm/svm/sev.c             | 933 +++++++++++++++++++++++++++--
 arch/x86/kvm/svm/svm.c             | 446 +++++++++++---
 arch/x86/kvm/svm/svm.h             | 166 ++++-
 arch/x86/kvm/svm/vmenter.S         |  50 ++
 arch/x86/kvm/trace.h               |  97 +++
 arch/x86/kvm/vmx/vmx.c             |   6 +-
 arch/x86/kvm/x86.c                 | 344 +++++++++--
 arch/x86/kvm/x86.h                 |   9 +
 17 files changed, 1962 insertions(+), 238 deletions(-)


base-commit: dc924b062488a0376aae41d3e0a27dc99f852a5e
```
#### [PATCH kvmtool 00/21] Unify I/O port and MMIO trap handling
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Thu Dec 10 14:28:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11966015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2E19C4361B
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 19:29:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 609D723101
	for <kvm@archiver.kernel.org>; Thu, 10 Dec 2020 19:29:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2393392AbgLJT3j (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 10 Dec 2020 14:29:39 -0500
Received: from foss.arm.com ([217.140.110.172]:44758 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390262AbgLJOaI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 10 Dec 2020 09:30:08 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EA4941FB;
        Thu, 10 Dec 2020 06:29:21 -0800 (PST)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.195.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 CE1443F718;
        Thu, 10 Dec 2020 06:29:20 -0800 (PST)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Marc Zyngier <maz@kernel.org>
Subject: [PATCH kvmtool 00/21] Unify I/O port and MMIO trap handling
Date: Thu, 10 Dec 2020 14:28:47 +0000
Message-Id: <20201210142908.169597-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment we use two separate code paths to handle exits for
KVM_EXIT_IO (ioport.c) and KVM_EXIT_MMIO (mmio.c), even though they
are semantically very similar. Because the trap handler callback routine
is different, devices need to decide on one conduit or need to provide
different handler functions for both of them.

This is not only unnecessary code duplication, but makes switching
devices from I/O port to MMIO a tedious task, even though there is no
real difference between the two, especially on ARM and PowerPC.

For ARM we aim at providing a flexible memory layout, and also have
trouble with the UART and RTC device overlapping with the PCI I/O area,
so it seems indicated to tackle this once and for all.

The first three patches do some cleanup, to simplify things later.

Patch 04/21 lays the groundwork, by extending mmio.c to be able to also
register I/O port trap handlers, using the same callback prototype as
we use for MMIO.

The next 14 patches then convert devices that use the I/O port
interface over to the new joint interface. This requires to rework
the trap handler routine to adhere to the same prototype as the existing
MMIO handlers. For most devices this is done in two steps: a first to
introduce the reworked handler routine, and a second to switch to the new
joint registration routine. For some devices the first step is trivial,
so it's done in one patch.

Patch 19/21 then retires the old I/O port interface, by removing ioport.c
and friends.

The final two patches switch the UART and the RTC device over to register
on the MMIO "bus", when running on ARM or arm64. This changes the
addresses to be at 16MB, so they are not in the PCI I/O area anymore.

Admittedly this goal can be achieved much simpler, by just having the
first three patches, and some more changes and ifdef's in the last two,
but I figured it would be good to clean up the I/O port mess for good.

Please have a look and comment!

Cheers,
Andre

Andre Przywara (21):
  ioport: Remove ioport__setup_arch()
  hw/serial: Use device abstraction for FDT generator function
  ioport: Retire .generate_fdt_node functionality
  mmio: Extend handling to include ioport emulation
  hw/i8042: Clean up data types
  hw/i8042: Refactor trap handler
  hw/i8042: Switch to new trap handlers
  x86/ioport: Refactor trap handlers
  x86/ioport: Switch to new trap handlers
  hw/rtc: Refactor trap handlers
  hw/rtc: Switch to new trap handler
  hw/vesa: Switch trap handling to use MMIO handler
  hw/serial: Refactor trap handler
  hw/serial: Switch to new trap handlers
  vfio: Refactor ioport trap handler
  vfio: Switch to new ioport trap handlers
  virtio: Switch trap handling to use MMIO handler
  pci: Switch trap handling to use MMIO handler
  Remove ioport specific routines
  hw/serial: ARM/arm64: Use MMIO at higher addresses
  hw/rtc: ARM/arm64: Use MMIO at higher addresses

 Makefile             |   1 -
 arm/ioport.c         |   5 -
 hw/i8042.c           |  88 ++++++----------
 hw/rtc.c             |  91 ++++++++---------
 hw/serial.c          | 166 +++++++++++++++++++-----------
 hw/vesa.c            |  19 +---
 include/kvm/i8042.h  |   1 -
 include/kvm/ioport.h |  25 -----
 include/kvm/kvm.h    |  42 +++++++-
 ioport.c             | 235 -------------------------------------------
 mips/kvm.c           |   5 -
 mmio.c               |  59 +++++++++--
 pci.c                |  82 +++++----------
 powerpc/ioport.c     |   6 --
 vfio/core.c          |  50 ++++-----
 virtio/pci.c         |  42 ++------
 x86/ioport.c         | 106 +++++++++----------
 17 files changed, 385 insertions(+), 638 deletions(-)
 delete mode 100644 ioport.c
```
