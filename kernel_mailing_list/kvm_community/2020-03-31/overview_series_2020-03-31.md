#### [PATCH 01/15] KVM: arm64: Use the correct timer structure to access the physical counter
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11467715
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BB4217EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 59BFA2145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:12 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585657032;
	bh=UKESaLDxPSB+InQ4SQPbwyW9ucmZcRKTBMCbcB6rK4g=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=wyIYCxP6QwXJGY1PKfHLn4a7a7gbo1ZpYRrgFeMka/bcZElY/9r4iQgpzetGHy8a+
	 BVkSzIaJa+GK3DHNaK+FnEeOxb7216jqdUDmvpbPVwAjYUhvXtcoKwHQWJsvGRpGHr
	 o/s38GR4GFbGL+A2gWn40XqmmV6lbXlXGZCASnjo=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730646AbgCaMRL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 08:17:11 -0400
Received: from mail.kernel.org ([198.145.29.99]:51850 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730473AbgCaMRL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 08:17:11 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6BDEB20838;
        Tue, 31 Mar 2020 12:17:10 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585657030;
        bh=UKESaLDxPSB+InQ4SQPbwyW9ucmZcRKTBMCbcB6rK4g=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=taBmYvmLZWGx0pkjt4cFtCG9PLHTIX4i1zlg+ZJGDF6bA6QHl0SNR3wVSibiHykxu
         3C0qz9oCVqzb50KYOYCyzi6sUQZ+r0QR7Xc2xobkt0YEkBkZE+WOheDhQHkwGkiMdS
         B042cFXcaiKfuBEPEaR7RI8bZijWCJ7z8E3mOhyQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jJFpM-00HBlI-MS; Tue, 31 Mar 2020 13:17:08 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Arnd Bergmann <arnd@arndb.de>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        KarimAllah Ahmed <karahmed@amazon.de>,
        Linus Walleij <linus.walleij@linaro.org>,
        Olof Johansson <olof@lixom.net>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 01/15] KVM: arm64: Use the correct timer structure to access
 the physical counter
Date: Tue, 31 Mar 2020 13:16:31 +0100
Message-Id: <20200331121645.388250-2-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200331121645.388250-1-maz@kernel.org>
References: <20200331121645.388250-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, arnd@arndb.de,
 catalin.marinas@arm.com, christoffer.dall@arm.com, eric.auger@redhat.com,
 karahmed@amazon.de, linus.walleij@linaro.org, olof@lixom.net,
 vladimir.murzin@arm.com, will@kernel.org, yuzenghui@huawei.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: KarimAllah Ahmed <karahmed@amazon.de>

Use the physical timer structure when reading the physical counter
instead of using the virtual timer structure. Thankfully, nothing is
accessing this code path yet (at least not until we enable save/restore
of the physical counter). It doesn't hurt for this to be correct though.

Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
[maz: amended commit log]
Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Zenghui Yu <yuzenghui@huawei.com>
Fixes: 84135d3d18da ("KVM: arm/arm64: consolidate arch timer trap handlers")
Link: https://lore.kernel.org/r/1584351546-5018-1-git-send-email-karahmed@amazon.de
---
 virt/kvm/arm/arch_timer.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm updates for Linux 5.7
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11467713
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2052892C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E9584208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585657032;
	bh=F2K4f2e4n0MRNDdO8Chjt10dQUBdb5AxXSgbnvLKozc=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=OIXfETMAFfO4//miMhkEYjjWQik9xgIwNa0lVpri9N2MdK1xwiQ97E4iERsgFy8/e
	 hM05GhdBhmGebnNdtImxxtQe98pDvaeFcb+XaucOAhcdxUoEJ2afFpwCy2IgKdJAQZ
	 XxNVHjKfdabwVC21f6HjNOgZq86xbfc/IBBY83Cg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730604AbgCaMRL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 08:17:11 -0400
Received: from mail.kernel.org ([198.145.29.99]:51814 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730380AbgCaMRK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 08:17:10 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9188D20714;
        Tue, 31 Mar 2020 12:17:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585657029;
        bh=F2K4f2e4n0MRNDdO8Chjt10dQUBdb5AxXSgbnvLKozc=;
        h=From:To:Cc:Subject:Date:From;
        b=2AB5UCxbjIpn8b/N4rORh7uuvYIGKvWS/mL+/amkOrj5EW4b+l7tbZWMHdYl4npI1
         x47HjS4BedkoUT39IsIAUvK3hhwNIWftSCpfg9RtJ270NK1NsNqLNV4+QhUUUVUzSm
         Cp3vJZxfZoQDe6slQ21Fie/hAOQC9EjvcwCsQjC8=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jJFpL-00HBlI-QV; Tue, 31 Mar 2020 13:17:07 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Arnd Bergmann <arnd@arndb.de>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        KarimAllah Ahmed <karahmed@amazon.de>,
        Linus Walleij <linus.walleij@linaro.org>,
        Olof Johansson <olof@lixom.net>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm updates for Linux 5.7
Date: Tue, 31 Mar 2020 13:16:30 +0100
Message-Id: <20200331121645.388250-1-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, arnd@arndb.de,
 catalin.marinas@arm.com, christoffer.dall@arm.com, eric.auger@redhat.com,
 karahmed@amazon.de, linus.walleij@linaro.org, olof@lixom.net,
 vladimir.murzin@arm.com, will@kernel.org, yuzenghui@huawei.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Here's the main set of KVM/arm updates for Linux 5.7. Two items on the menu
this time:

- Support for GICv4.1, which allows for the direct injection of more
  interrupt classes than GICv4.0, and a much more sensible set of
  interactions with the hypervisor.

- Removal of the 32bit host support. It has been a fun ride, but with a
  general lack of interest as well as the 32bit Linux/ARM port being in "odd
  fixes" mode, there is little point in pretending that we care (100% of the
  activity is in the arm64 camp). This will, over time, result in cleaner
  code (less pointless abstractions) and be easier for arm64 to gain new
  features.

Please note that pulling from this tag will drag the GICv4.1 dependencies,
as they are part a shared branch between the irqchip and kvmarm trees. These
patches are already in Linus' tree as of this morning.

Please pull,

	M.

The following changes since commit 009384b38034111bf2c0c7bfb2740f5bd45c176c:

  irqchip/gic-v4.1: Eagerly vmap vPEs (2020-03-24 12:15:51 +0000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git kvmarm-5.7

for you to fetch changes up to 463050599742a89e0508355e626e032e8d0dab8d:

  Merge tag 'kvm-arm-removal' into kvmarm-master/next (2020-03-24 17:43:53 +0000)

----------------------------------------------------------------
KVM/arm updates for Linux 5.7

- GICv4.1 support
- 32bit host removal

----------------------------------------------------------------
KarimAllah Ahmed (1):
      KVM: arm64: Use the correct timer structure to access the physical counter

Marc Zyngier (16):
      arm: Unplug KVM from the build system
      arm: Remove KVM from config files
      arm: Remove 32bit KVM host support
      arm: Remove HYP/Stage-2 page-table support
      arm: Remove GICv3 vgic compatibility macros
      arm: Remove the ability to set HYP vectors outside of the decompressor
      MAINTAINERS: RIP KVM/arm
      KVM: arm64: GICv4.1: Let doorbells be auto-enabled
      KVM: arm64: GICv4.1: Add direct injection capability to SGI registers
      KVM: arm64: GICv4.1: Allow SGIs to switch between HW and SW interrupts
      KVM: arm64: GICv4.1: Plumb SGI implementation selection in the distributor
      KVM: arm64: GICv4.1: Reload VLPI configuration on distributor enable/disable
      KVM: arm64: GICv4.1: Allow non-trapping WFI when using HW SGIs
      KVM: arm64: GICv4.1: Expose HW-based SGIs in debugfs
      Merge branch 'kvm-arm64/gic-v4.1' into kvmarm-master/next
      Merge tag 'kvm-arm-removal' into kvmarm-master/next

 Documentation/virt/kvm/arm/hyp-abi.rst |    5 +
 MAINTAINERS                            |    5 +-
 arch/arm/Kconfig                       |    2 -
 arch/arm/Makefile                      |    1 -
 arch/arm/configs/axm55xx_defconfig     |    2 -
 arch/arm/include/asm/arch_gicv3.h      |  114 ---
 arch/arm/include/asm/kvm_arm.h         |  239 ------
 arch/arm/include/asm/kvm_asm.h         |   77 --
 arch/arm/include/asm/kvm_coproc.h      |   36 -
 arch/arm/include/asm/kvm_emulate.h     |  372 --------
 arch/arm/include/asm/kvm_host.h        |  456 ----------
 arch/arm/include/asm/kvm_hyp.h         |  127 ---
 arch/arm/include/asm/kvm_mmu.h         |  435 ----------
 arch/arm/include/asm/kvm_ras.h         |   14 -
 arch/arm/include/asm/pgtable-3level.h  |   20 -
 arch/arm/include/asm/pgtable.h         |    9 -
 arch/arm/include/asm/sections.h        |    6 +-
 arch/arm/include/asm/stage2_pgtable.h  |   75 --
 arch/arm/include/asm/virt.h            |   17 -
 arch/arm/include/uapi/asm/kvm.h        |  314 -------
 arch/arm/kernel/asm-offsets.c          |   11 -
 arch/arm/kernel/hyp-stub.S             |   39 +-
 arch/arm/kernel/vmlinux-xip.lds.S      |    8 -
 arch/arm/kernel/vmlinux.lds.S          |    8 -
 arch/arm/kernel/vmlinux.lds.h          |   10 -
 arch/arm/kvm/Kconfig                   |   59 --
 arch/arm/kvm/Makefile                  |   43 -
 arch/arm/kvm/coproc.c                  | 1455 --------------------------------
 arch/arm/kvm/coproc.h                  |  130 ---
 arch/arm/kvm/coproc_a15.c              |   39 -
 arch/arm/kvm/coproc_a7.c               |   42 -
 arch/arm/kvm/emulate.c                 |  166 ----
 arch/arm/kvm/guest.c                   |  387 ---------
 arch/arm/kvm/handle_exit.c             |  175 ----
 arch/arm/kvm/hyp/Makefile              |   34 -
 arch/arm/kvm/hyp/banked-sr.c           |   70 --
 arch/arm/kvm/hyp/cp15-sr.c             |   72 --
 arch/arm/kvm/hyp/entry.S               |  121 ---
 arch/arm/kvm/hyp/hyp-entry.S           |  295 -------
 arch/arm/kvm/hyp/s2-setup.c            |   22 -
 arch/arm/kvm/hyp/switch.c              |  242 ------
 arch/arm/kvm/hyp/tlb.c                 |   68 --
 arch/arm/kvm/hyp/vfp.S                 |   57 --
 arch/arm/kvm/init.S                    |  157 ----
 arch/arm/kvm/interrupts.S              |   36 -
 arch/arm/kvm/irq.h                     |   16 -
 arch/arm/kvm/reset.c                   |   86 --
 arch/arm/kvm/trace.h                   |   86 --
 arch/arm/kvm/vgic-v3-coproc.c          |   27 -
 arch/arm/mach-exynos/Kconfig           |    2 +-
 arch/arm/mm/mmu.c                      |   26 -
 arch/arm64/include/asm/kvm_emulate.h   |    3 +-
 arch/arm64/include/asm/kvm_host.h      |    1 +
 include/kvm/arm_vgic.h                 |    3 +
 virt/kvm/arm/arch_timer.c              |    2 +-
 virt/kvm/arm/arm.c                     |    8 +
 virt/kvm/arm/vgic/vgic-debug.c         |   14 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c       |   81 +-
 virt/kvm/arm/vgic/vgic-mmio.c          |   88 +-
 virt/kvm/arm/vgic/vgic-v3.c            |    2 +
 virt/kvm/arm/vgic/vgic-v4.c            |  107 ++-
 virt/kvm/arm/vgic/vgic.h               |    1 +
 62 files changed, 311 insertions(+), 6314 deletions(-)
 delete mode 100644 arch/arm/include/asm/kvm_arm.h
 delete mode 100644 arch/arm/include/asm/kvm_asm.h
 delete mode 100644 arch/arm/include/asm/kvm_coproc.h
 delete mode 100644 arch/arm/include/asm/kvm_emulate.h
 delete mode 100644 arch/arm/include/asm/kvm_host.h
 delete mode 100644 arch/arm/include/asm/kvm_hyp.h
 delete mode 100644 arch/arm/include/asm/kvm_mmu.h
 delete mode 100644 arch/arm/include/asm/kvm_ras.h
 delete mode 100644 arch/arm/include/asm/stage2_pgtable.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm.h
 delete mode 100644 arch/arm/kvm/Kconfig
 delete mode 100644 arch/arm/kvm/Makefile
 delete mode 100644 arch/arm/kvm/coproc.c
 delete mode 100644 arch/arm/kvm/coproc.h
 delete mode 100644 arch/arm/kvm/coproc_a15.c
 delete mode 100644 arch/arm/kvm/coproc_a7.c
 delete mode 100644 arch/arm/kvm/emulate.c
 delete mode 100644 arch/arm/kvm/guest.c
 delete mode 100644 arch/arm/kvm/handle_exit.c
 delete mode 100644 arch/arm/kvm/hyp/Makefile
 delete mode 100644 arch/arm/kvm/hyp/banked-sr.c
 delete mode 100644 arch/arm/kvm/hyp/cp15-sr.c
 delete mode 100644 arch/arm/kvm/hyp/entry.S
 delete mode 100644 arch/arm/kvm/hyp/hyp-entry.S
 delete mode 100644 arch/arm/kvm/hyp/s2-setup.c
 delete mode 100644 arch/arm/kvm/hyp/switch.c
 delete mode 100644 arch/arm/kvm/hyp/tlb.c
 delete mode 100644 arch/arm/kvm/hyp/vfp.S
 delete mode 100644 arch/arm/kvm/init.S
 delete mode 100644 arch/arm/kvm/interrupts.S
 delete mode 100644 arch/arm/kvm/irq.h
 delete mode 100644 arch/arm/kvm/reset.c
 delete mode 100644 arch/arm/kvm/trace.h
 delete mode 100644 arch/arm/kvm/vgic-v3-coproc.c

From patchwork Tue Mar 31 12:16:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11467717
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F60A14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3EE962145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 12:17:13 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585657033;
	bh=twI+FrhMAk/LCQP/xGXohCa10/7aYbpXUmUJDbB9Bfc=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=2bSK6QNozvO9h0zMSmg9OLjJV2bjNiE8pFYLB0rqj+TulBN9PxTFVouveGw215CiS
	 z44UKYi1SS48SVMqUAWt+kJ8uGzjDZG5toaiDdrMgVAkQPcLZK1fbM92yfYYJVXUoU
	 eEihG7/cxHY1PTwl4VwXSw7C0U8AmaALy7SvtJ1Y=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730662AbgCaMRM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 08:17:12 -0400
Received: from mail.kernel.org ([198.145.29.99]:51888 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730380AbgCaMRM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 08:17:12 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4C3EE20848;
        Tue, 31 Mar 2020 12:17:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585657031;
        bh=twI+FrhMAk/LCQP/xGXohCa10/7aYbpXUmUJDbB9Bfc=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=CxikxnfTRAqv+N2cVrFMz8nFFqVt3OJ9YQzX7PsXES/4hGfMO3W+PIy8Oy5XFJt4g
         egm7KJeN87t8yYeRuNHX01MHHrtW/u8yLVBZwV7XEA/OKMbTMH+uICHASL1BEWTveN
         Pw7fMeTJ3brGnwQwj/g7r4kmWj5VNsh53mLHCbvU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jJFpN-00HBlI-Jc; Tue, 31 Mar 2020 13:17:09 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Arnd Bergmann <arnd@arndb.de>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        KarimAllah Ahmed <karahmed@amazon.de>,
        Linus Walleij <linus.walleij@linaro.org>,
        Olof Johansson <olof@lixom.net>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 02/15] arm: Unplug KVM from the build system
Date: Tue, 31 Mar 2020 13:16:32 +0100
Message-Id: <20200331121645.388250-3-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200331121645.388250-1-maz@kernel.org>
References: <20200331121645.388250-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, arnd@arndb.de,
 catalin.marinas@arm.com, christoffer.dall@arm.com, eric.auger@redhat.com,
 karahmed@amazon.de, linus.walleij@linaro.org, olof@lixom.net,
 vladimir.murzin@arm.com, will@kernel.org, yuzenghui@huawei.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we're about to drop KVM/arm on the floor, carefully unplug
it from the build system.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Acked-by: Olof Johansson <olof@lixom.net>
Acked-by: Arnd Bergmann <arnd@arndb.de>
Acked-by: Will Deacon <will@kernel.org>
Acked-by: Vladimir Murzin <vladimir.murzin@arm.com>
Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Acked-by: Linus Walleij <linus.walleij@linaro.org>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/Kconfig             | 2 --
 arch/arm/Makefile            | 1 -
 arch/arm/mach-exynos/Kconfig | 2 +-
 3 files changed, 1 insertion(+), 4 deletions(-)

```
#### [PATCH v8 01/14] KVM: X86: Change parameter for fast_page_fault tracepoint
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11468259
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 26EFF92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:00:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 04904207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:00:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GO+8PA/K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727627AbgCaTAO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:00:14 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:49625 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726295AbgCaTAN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 15:00:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585681212;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=GO+8PA/KdDHQqj2lPSUe2/KuzG47nqbm8j6XfBRl3s90dve8YCpPAJAahf7jIxhmvyo2Z+
        hZtYSxAMyBHUwBqTdOu/x0WbGbQsNdt44BGrfT73p07pZEjMRiX24MqGKrtHPCddP4lVjm
        qtPld3QGpZ7qUiEEtdKOAeqrWGjBd5A=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-73-YYb3VtZ4PXW-_EfU9QqxvQ-1; Tue, 31 Mar 2020 15:00:10 -0400
X-MC-Unique: YYb3VtZ4PXW-_EfU9QqxvQ-1
Received: by mail-wr1-f72.google.com with SMTP id v17so9307934wro.21
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 12:00:10 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=zL6sq31OFwBXF/RS7PK1GArrpq69jRR45bepTSw46TU=;
        b=EHRmOWrV+9YUaFPycnvZEeLoDyIcVeV8ZvaXR8CW830pgmnjz/ft8RIBwY5x58/xKV
         YOQ4jyHZJEY8Sc9bh8Y7biqPS1QN0uJC93xoMeNO5Xi0mu8XmvbDCXWx1qdNIHY2WkKK
         PYpV2u/YYn65ux/ywAQsK9Ulyxieazvf5tijqp/3oWT73UPTkD6p3jf1Y4ZUQzC23T3O
         eIv4czfd2Auhph8xA/II7xEm8DbmWq4gXG7hV1zalwvVH7jo4UadC18z/LQHeUA4ggEl
         6CfYZFaJAnxXb7WMrz9cZdaii2YBTIfnxMpoGUwq1opWLv3ccYtn5gAkV1JnVMjvOlYP
         kd+w==
X-Gm-Message-State: ANhLgQ3QkLejWn209NEUXFRyICr9OqAiPEf1JGC0U8FpdREu3npGueWt
        cmVbS0wGuf1Ph/XbIpT8lq27TH2jue+mLwMoS9a/q7Ju4+qx5MBZ/jHLipFkcCsIsDBFeZ99Mn4
        tfTrj+UH3TwNf
X-Received: by 2002:adf:b186:: with SMTP id q6mr21784782wra.253.1585681209639;
        Tue, 31 Mar 2020 12:00:09 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vuw1mD28p3JHof9YrDOHCb6+VgxgT119t2q54QLWIHZ0l4+T/QIDJWlvKoTTEJJxE9mpkLKdQ==
X-Received: by 2002:adf:b186:: with SMTP id q6mr21784753wra.253.1585681209403;
        Tue, 31 Mar 2020 12:00:09 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 h10sm29018467wrq.33.2020.03.31.12.00.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 31 Mar 2020 12:00:08 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Kevin Tian <kevin.tian@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>, peterx@redhat.com
Subject: [PATCH v8 01/14] KVM: X86: Change parameter for fast_page_fault
 tracepoint
Date: Tue, 31 Mar 2020 14:59:47 -0400
Message-Id: <20200331190000.659614-2-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200331190000.659614-1-peterx@redhat.com>
References: <20200331190000.659614-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It would be clearer to dump the return value to know easily on whether
did we go through the fast path for handling current page fault.
Remove the old two last parameters because after all the old/new sptes
were dumped in the same line.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
#### [PATCH] KVM: MIPS: fix compilation
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11467979
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B200159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 15:48:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7831D20848
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 15:48:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KxNPvEdB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731080AbgCaPr5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 11:47:57 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:36204 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1730635AbgCaPr5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 11:47:57 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585669676;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=JZtZSbKo5LIE2USs8ZYw0MKFj7vPTw9aUaKq/XN8w6g=;
        b=KxNPvEdBUo23UzmjFTIyZ4QFSqeDAsMNRhZ2JYMqW0Yoe8ZrlxDh4FLJXTbXlt9o3iBXDe
        vehWY5mbDWq8GW7yUwndW1kVOGU+B3gRwXNH/vnXrH96by7HDvkOWCPzWEttmwL3Fnhaps
        ASd66qq8oRBShngx61T//LSQyTswdy8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-107-tCcb4IJzNseAWG37EiM-yA-1; Tue, 31 Mar 2020 11:47:54 -0400
X-MC-Unique: tCcb4IJzNseAWG37EiM-yA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1812C149C0;
        Tue, 31 Mar 2020 15:47:53 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BD76060BE2;
        Tue, 31 Mar 2020 15:47:49 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: linux-mips@vger.kernel.org, peterx@redhat.com, rppt@linux.ibm.com
Subject: [PATCH] KVM: MIPS: fix compilation
Date: Tue, 31 Mar 2020 11:47:49 -0400
Message-Id: <20200331154749.5457-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 31168f033e37 is correct that pud_index() & __pud_offset() are the same
when pud_index() is actually provided, however it does not take into account
the __PAGETABLE_PUD_FOLDED case.  Provide kvm_pud_index so that MIPS KVM
compiles.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/mips/kvm/mmu.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: SVM: Split svm_vcpu_run inline assembly to a separate file.
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11468325
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AEA717EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:51:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2D6D02080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:51:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="HG+FWu/E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730014AbgCaTvT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:51:19 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:39527 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726411AbgCaTvT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 15:51:19 -0400
Received: by mail-wm1-f66.google.com with SMTP id e9so4297977wme.4
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 12:51:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XS70HuyfnfDWUuokOJC2p9A8chTyL8w8PwgHYlhSinM=;
        b=HG+FWu/E8Ecjv6NCw/SlluIZgoabFwyvTqQCPXh4OSDAAtmcc32hA4ifWzb5qCrKNk
         KXKnsLbBLp3f9dXhv7JIux+nxgJY+BmzAB6de4eWuvQAAm3Rc4anKPIOTy4jL6NAVpcR
         1kQqbUdVZ7evLLXeZd97GWf8ogrmRnH8FhwhOVXiXuKL//9rbPflf4MXLvGOeCQowI8I
         CWlL6fdKHrK57ocNgE/w+QlFgQEYxea6WoHqTIm4+va09jOaVDSld/YRGirrH01kI9IR
         4YSKS4l8NEEejTkYyO+vBRtIVLemdsgRE65VC2WV3CZsUBsUWKGnBsxbF8i1Vg7rNIRk
         waGg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=XS70HuyfnfDWUuokOJC2p9A8chTyL8w8PwgHYlhSinM=;
        b=pLDcnCiMeMNzlab4tcMHvE1z8pPT5tM97u5lAv7Mi+h7VCp+YvvCoktQ7erUBHXNON
         dlnBoDAUhpknxtYt67uxcK9zeJmEn3y3Np5ySr3GTiwDEMotDk1yzGlCcjYUrrJro4ml
         f6AXH98jV+Gj1iFP4lteKk8k1tOAdDuPx5IfdtJI450e8PLFIfP7oitgi0mXrM9s+Xrb
         IdmacIDDEoSosj6xfovrWPO33G/nlkyRYeZYfr82lXAYxGdPSE4Z1FAl6rhj9VxAOkdi
         ASDUbpRGVXcEtXnUF7tMrVgd9KHnf+/3HMBzwPl9JX7JLILp/yqU7656JpsEnRKLLENf
         cz/Q==
X-Gm-Message-State: AGi0PuaePbVfGfmCRrh2rPrJmJk0ES5SNiSfwmoEgVhp58lmOVR8RL3j
        3XjoYCJswXmYm/CtNRJqEnrUQwwAXV4=
X-Google-Smtp-Source: 
 APiQypJjFe8Hj0rgwaQRTKOFyXBechsIEwi+QswqQWl6WGepmgzDXKr0TIKA4qXLMtzz5gs+1tfWIQ==
X-Received: by 2002:a1c:7412:: with SMTP id p18mr488519wmc.11.1585684275471;
        Tue, 31 Mar 2020 12:51:15 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 v7sm25598576wrs.96.2020.03.31.12.51.14
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 31 Mar 2020 12:51:14 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Uros Bizjak <ubizjak@gmail.com>
Subject: [PATCH] KVM: SVM: Split svm_vcpu_run inline assembly to a separate
 file.
Date: Tue, 31 Mar 2020 21:51:08 +0200
Message-Id: <20200331195108.71490-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The compiler (GCC) does not like the situation, where there is inline
assembly block that clobbers all available machine registers in the
middle of the function. This situation can be found in function
svm_vcpu_run in file kvm/vmx.c and results in many register spills and
fills to/from stack frame.

This patch fixes the issue with the same approach as was done for
VMX some time ago. The big inline assembly is moved to a separate
assembly .S file, taking into account all ABI requirements.

There are two main benefits of the above approach:

* elimination of several register spills and fills to/from stack
frame, and consequently smaller function .text size. The binary size
of svm_vcpu_run is lowered from 2019 to 1626 bytes.

* more efficient access to a register save array. Currently, register
save array is accessed as:

    7b00:    48 8b 98 28 02 00 00     mov    0x228(%rax),%rbx
    7b07:    48 8b 88 18 02 00 00     mov    0x218(%rax),%rcx
    7b0e:    48 8b 90 20 02 00 00     mov    0x220(%rax),%rdx

and passing ia pointer to a register array as an argument to a function one gets:

  12:    48 8b 48 08              mov    0x8(%rax),%rcx
  16:    48 8b 50 10              mov    0x10(%rax),%rdx
  1a:    48 8b 58 18              mov    0x18(%rax),%rbx

As a result, the total size, considering that the new function size is 229
bytes, gets lowered by 164 bytes.

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/Makefile      |   2 +-
 arch/x86/kvm/svm.c         |  92 +--------------------
 arch/x86/kvm/svm_vmenter.S | 162 +++++++++++++++++++++++++++++++++++++
 3 files changed, 166 insertions(+), 90 deletions(-)
 create mode 100644 arch/x86/kvm/svm_vmenter.S

```
#### [RFC PATCH v3 1/8] update_headers: Sync-up ABI headers with Linux-5.6-rc5
##### From: Anup Patel <anup.patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11467431
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8091217EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 10:54:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49D74208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 10:54:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="MtP+hOqf";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="ZfBoQhoo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731039AbgCaKyM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 06:54:12 -0400
Received: from esa1.hgst.iphmx.com ([68.232.141.245]:22753 "EHLO
        esa1.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731032AbgCaKyL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 06:54:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1585652050; x=1617188050;
  h=from:to:cc:subject:date:message-id:in-reply-to:
   references:mime-version;
  bh=hCV9cdc6Fp3NqQWL8aKVi01/VI6R+pVpC+IF2Y9q/OI=;
  b=MtP+hOqfXDe8KnSqU6Z85Khpzr7BAKlXypLgBNG7mIj1SSt8cSuJB5iy
   sHUz8nviWJpWGI4aXkydWNbweq9JehpxfAbMPC1lpaNkMee4/lMaGJ1G4
   M1tTHMJRU2eIWQqWz9EeBEUOoZ89qE87A/BvdZCezlbx55T+lCqqkJW1K
   jUtnnU11r6BJTWW0zMedR0XSpW1ATKy4vUZXZ5VkS0ndhxlMFmmPtIRTd
   JAjDBgfm+I8jekLFxg+cwqVCjLYKd68VylXmbiBwMVlJmXNnJAXWB9smm
   aib2tg+DEzc5YADgwY9KCGtWccJcwvQv5GVHEAYBEOwM/ZTHlH5utpdHP
   g==;
IronPort-SDR: 
 Dy6l8dC4BdEMxcguyn79jkIG0fkZeC96jrZ0Ft3Q+SJh6DyUbSBMykeQ3wRJpFJn9lgplASaVY
 5uctOcE7CaFiVn74xidFeXf1F6rSAvQ5NMFcSwHSc3kRU7VgJU7j8wm9bNyLH5Rkiy1tyxwwkl
 u8JmJVMjR58WUrFUMKFugvyMTWxUg1Aghi5pyVr45kXkqfNWOzJtiAwMynj0CN+SBLjxuIGoS6
 EJqUQT2EZ8fPRloveRGO+eVvTOC583xfuOLaAfdabu/arNIOmwgXe8F2ce1ZwCTnCaMEejMzfK
 KWc=
X-IronPort-AV: E=Sophos;i="5.72,327,1580745600";
   d="scan'208";a="242563784"
Received: from mail-mw2nam10lp2109.outbound.protection.outlook.com (HELO
 NAM10-MW2-obe.outbound.protection.outlook.com) ([104.47.55.109])
  by ob1.hgst.iphmx.com with ESMTP; 31 Mar 2020 18:54:09 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=YhvzdeYktTBRUX9Eghf0JUjbL1M/vezV7XndnJZt56A5E6N/YNVPyGEsxRN4dfrcmhg3HfHsu2zS3VbR4FOU6dSzE+IxXque/KgFK7z2Jp8HgUSiEPmjfFC9FWGFcWkjICGZ3oH0Uh/wizZ9R8v0OV+GJ2MigiqiNr2ohD0U7y6zXSWW7IszJCJGv/5M1W71pJcnL8CEcS3uVdP5VtGi9XFgsYcM3bOJv3313pMAhDc8A8Wv4wZF2Jtx2/mBMdEbpTvP9FQCZLVYb6P99sXbBnuINcYAso9e8lc9DQWrZSqR5WH5Mq+EuVgxf6XAqh0+To2diWVEQVSHwKspS94E1Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=q3GwJpWVBw/WimHmjjjeXlHbjuEa7ggS6BIIQQtF8oo=;
 b=R3f/q7bjgUciaI4UyZIxKS2AfqDvPnj7hsu07wxApJzYh5APVE0O6sMub6HZJPaKggBnVzEvbmIYQqDIDEUHGF+JTmJCVYq1FUaBmFM0vcUc46PPS3jfjf6WaRGUScOXASxYxwsJJh0jVFWPE+UDA0FXytHnuIoOGYjzHi/ZTUfhrIFOpqMddDw5OXicmNLL59MkBsqPEBlLbM634ajYz4d6ZJgoIsUPQKLMyE6jIWjzl+kVD959q6uzTl/EMcFYgib42+EwM4Ftayd51YpYHFmHzPYiE2QGrX/8iXrEiR5V9gcv540jbt7EOIFBgsYORH64mmUqXWVY+KjQVgFKOg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=q3GwJpWVBw/WimHmjjjeXlHbjuEa7ggS6BIIQQtF8oo=;
 b=ZfBoQhooT7cE/IID4nZ6wLhR07NndUpU7swmAesChH96aM0jwdVAmKbRW+FwT3+uVdHD3qZRmnJR8sMYlU56xfYw5WIoE6PEhPbESk+h/r5X6V+2+Xh1ihbbaYYZeQPU1wrigscd6zhLTE1ouD+iuxVOnUU3ZAgVjrEhqkr28YM=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
 by MN2PR04MB7088.namprd04.prod.outlook.com (2603:10b6:208:1e1::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.20; Tue, 31 Mar
 2020 10:54:08 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::159d:10c9:f6df:64c8%6]) with mapi id 15.20.2856.019; Tue, 31 Mar 2020
 10:54:08 +0000
From: Anup Patel <anup.patel@wdc.com>
To: Will Deacon <will.deacon@arm.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Atish Patra <atish.patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Anup Patel <anup@brainfault.org>, kvm@vger.kernel.org,
        kvm-riscv@lists.infradead.org, Anup Patel <anup.patel@wdc.com>
Subject: [RFC PATCH v3 1/8] update_headers: Sync-up ABI headers with
 Linux-5.6-rc5
Date: Tue, 31 Mar 2020 16:23:26 +0530
Message-Id: <20200331105333.52296-2-anup.patel@wdc.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200331105333.52296-1-anup.patel@wdc.com>
References: <20200331105333.52296-1-anup.patel@wdc.com>
X-ClientProxiedBy: BM1PR0101CA0049.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:19::11) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from wdc.com (49.207.59.117) by
 BM1PR0101CA0049.INDPRD01.PROD.OUTLOOK.COM (2603:1096:b00:19::11) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2856.20 via Frontend
 Transport; Tue, 31 Mar 2020 10:54:05 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [49.207.59.117]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 526ba48e-811a-4d71-0cca-08d7d561d687
X-MS-TrafficTypeDiagnostic: MN2PR04MB7088:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <MN2PR04MB7088547C09C7A2FE34A2AE118DC80@MN2PR04MB7088.namprd04.prod.outlook.com>
WDCIPOUTBOUND: EOP-TRUE
X-MS-Oob-TLC-OOBClassifiers: OLM:1247;
X-Forefront-PRVS: 0359162B6D
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:MN2PR04MB6061.namprd04.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(10019020)(4636009)(346002)(39860400002)(366004)(396003)(136003)(376002)(8886007)(1006002)(6666004)(2906002)(478600001)(316002)(7696005)(52116002)(36756003)(6916009)(54906003)(16526019)(81156014)(8676002)(186003)(2616005)(81166006)(1076003)(8936002)(55016002)(44832011)(5660300002)(956004)(66946007)(66556008)(86362001)(26005)(4326008)(66476007)(55236004);DIR:OUT;SFP:1102;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 uk7rUDHul7yLGBXCWFvNo8PkAo9iRwifCEYKqq//MlVKbl9mdecR/agzjCPrqf9LJQjgWBcheu84xSSK0BAVLHTCuDglSC6YIICXcaVs70X3rZx5VRsWMEDYcYMfC1hgsGlC54zyjRW6b/nMoUA0dXeidwavOTGjhsveNfgtT/vv2llfBQTDYKLqFV27zRL5cStVkVpghRX3H7m2wYrF0P6U2XVr6nvqiZzCLafgQGwHbi39OETQ3j9rPPh3nbMbYodDbUqOZRs4o4Jetn+yFUb7lz1/OhbmrIcWc1Gqm8/Siq85KibbzPe57FXcam7Gze+IU/KB0rr1bcB+jTvNEuNgRLeqQxkwcyV0ezGAwpRzLzADC39jmkwjdNrNPIAcXQbFjwn52WFJ58hDRYVTTjp6GvHs3OKoFoVjHxlmvkb5KlzREnm8kwj/jdYEzvc1
X-MS-Exchange-AntiSpam-MessageData: 
 d1vjy7PCloNaVyxx+eTVpxyhznSB9m77+WDupFbaUBH3A2gci/kcD0IlNmtM7h/vmmmEcS2bVHK8tTGUES+PHaYyGao1d+JjN5HLECaxd25/hMgkc1b8NXtlDV3L4hYHUXVZ/Wp+dQ10gKBCQ/0RQw==
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 526ba48e-811a-4d71-0cca-08d7d561d687
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 31 Mar 2020 10:54:08.7461
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Q7T9Hb6Y3YVyIYCasKbC0/xALguS4uWk5qt5aSdLfj19y0uY2+3mFsHZ/wbqV5BDKERilzyvZOtWKqcwGVvE+g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB7088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We sync-up all ABI headers with Linux-5.6-rc5. This will allow
us to use ONE_REG interface for KVMTOOL RISC-V port.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 arm/aarch32/include/asm/kvm.h |  7 +++++--
 arm/aarch64/include/asm/kvm.h | 21 +++++++++++++++++----
 include/linux/kvm.h           | 30 ++++++++++++++++++++++++++++++
 powerpc/include/asm/kvm.h     |  3 +++
 x86/include/asm/kvm.h         |  1 +
 5 files changed, 56 insertions(+), 6 deletions(-)

```
#### [PATCH 1/4] kvm: Add capability to be able to report async pf error to guest
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11468315
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F1F8B913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:40:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BC4A120776
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:40:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LqcKas9p"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728493AbgCaTkc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:40:32 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:48252 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727740AbgCaTkc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 15:40:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585683630;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=7evanx/JUXfji21NZZBHbn76ofL2zUbOkCQZCYcXArk=;
        b=LqcKas9pJr5SCx638hTXTNuzjx/w5ivQD0MjOqSLls+bQP8iafNjQIvB49ne1KeutVetOu
        56haRtTKnS7CVjOmM8IU3YXThJaLEUf4/TRR+23OhFAuDqMzmEvZPQ57fGkLoSoeMwa1If
        lQhcLbSjsstHej/EZCEWX+uOKyGhxCs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-34-acg85Hg7Mpuo67cZAyxyUQ-1; Tue, 31 Mar 2020 15:40:27 -0400
X-MC-Unique: acg85Hg7Mpuo67cZAyxyUQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E879C193579E;
        Tue, 31 Mar 2020 19:40:26 +0000 (UTC)
Received: from horse.redhat.com (ovpn-118-184.phx2.redhat.com [10.3.118.184])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3079862697;
        Tue, 31 Mar 2020 19:40:21 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 604F22202B3; Tue, 31 Mar 2020 15:40:20 -0400 (EDT)
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs@redhat.com, miklos@szeredi.hu, stefanha@redhat.com,
        dgilbert@redhat.com, vgoyal@redhat.com, aarcange@redhat.com,
        dhildenb@redhat.com
Subject: [PATCH 1/4] kvm: Add capability to be able to report async pf error
 to guest
Date: Tue, 31 Mar 2020 15:40:08 -0400
Message-Id: <20200331194011.24834-2-vgoyal@redhat.com>
In-Reply-To: <20200331194011.24834-1-vgoyal@redhat.com>
References: <20200331194011.24834-1-vgoyal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As of now asynchronous page fault mecahanism assumes host will always be
successful in resolving page fault. So there are only two states, that
is page is not present and page is ready.

If a page is backed by a file and that file has been truncated (as
can be the case with virtio-fs), then page fault handler on host returns
-EFAULT.

As of now async page fault logic does not look at error code (-EFAULT)
returned by get_user_pages_remote() and returns PAGE_READY to guest.
Guest tries to access page and page fault happnes again. And this
gets kvm into an infinite loop. (Killing host process gets kvm out of
this loop though).

This patch adds another state to async page fault logic which allows
host to return error to guest. Once guest knows that async page fault
can't be resolved, it can send SIGBUS to host process (if user space
was accessing the page in question).

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     |  4 ++++
 Documentation/virt/kvm/msr.rst       | 11 ++++++++---
 arch/x86/include/asm/kvm_host.h      |  3 +++
 arch/x86/include/asm/kvm_para.h      |  4 ++--
 arch/x86/include/uapi/asm/kvm_para.h |  3 +++
 arch/x86/kernel/kvm.c                | 29 +++++++++++++++++++++++++---
 arch/x86/kvm/cpuid.c                 |  3 ++-
 arch/x86/kvm/mmu/mmu.c               |  2 +-
 arch/x86/kvm/x86.c                   | 13 +++++++++----
 include/linux/kvm_host.h             |  1 +
 virt/kvm/async_pf.c                  |  6 ++++--
 11 files changed, 63 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: x86: move kvm_create_vcpu_debugfs after last failure point
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11468463
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 86DD9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 22:42:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 63C1721D6C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 22:42:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="qFpsBADr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731345AbgCaWm3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 18:42:29 -0400
Received: from mail-wr1-f67.google.com ([209.85.221.67]:34012 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727955AbgCaWm2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 18:42:28 -0400
Received: by mail-wr1-f67.google.com with SMTP id 65so28275790wrl.1;
        Tue, 31 Mar 2020 15:42:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=1jsuwtxuUphpE0RZhef4PDISQgTlLi4Ca2smnB8QhUI=;
        b=qFpsBADrpxeqLat60SC4r8eFLqa9EQpyfUJ0PHJjOUDv77WE2TTxgmJJIvqryxuVqE
         VIRRwBBYy8UymCCCsmMqHyLxeegl8aHL1M186n9xpumZduxYHgPAkyLPCGgRW7tupUbx
         nUobJ22z7KXcOaqDf52le4WcqjXXJ7CK24z6WBMVsc/jZ8h8J/h3R2UKchatYLniqYKw
         Yg6DWBaPlwL+w7vTkHkz9QbOtYo0W05KsdcCIvSOrPMhvHWiTmKtYyVfTJYpYRT4x8UZ
         AVbqszIl251A+i2FjHwie8m0X8hECIZ6M7c/RUXHWIXefEkCY2YqMi6SrtjDqOEUKrUf
         aXYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=1jsuwtxuUphpE0RZhef4PDISQgTlLi4Ca2smnB8QhUI=;
        b=VeADCdpQvFHtHfq1HTJ+hD7Gl1J0K7T6anCuIvcFyqFZC8y+Z507lQEOtU3kRHczn6
         qAvZ8Qn215S+SazVZr+ei/Wl4kj5JzvTny6jqLrrWpoE4uq+GBOfl7mv8/1H+SzmDtoo
         0/gZRwWc4Dwc2FRhuJGl75bIYPG60Rtg7vKsmOerBukseVcgXu7nBGO9WVehoLDjQEsS
         Ha+scq4wUt53jmI/4m3Yo/9S/r65QUcW2RYSEX2sTo/+D9DCXG6uDbrOjAp3LLQMJXc+
         QztYY6oLAbB1yzVbnMZiAM+gGXWASIGdI+wC4t+DNxgF0HGyR8zHJoTI+iO7m5ttbYG0
         060w==
X-Gm-Message-State: ANhLgQ1pD4lpwh9jnQGjWby7rLA7oexhcF/LGnQbVMt4FYDSO02ruMAz
        kZ87RUJlzzrJlgILtBcSr1LzCLm0BtI=
X-Google-Smtp-Source: 
 ADFU+vvRoF9pFdVcJa9cMPcXPxkqycsPt/wZshyxiR0NL1tLIR0+e5n+OF7X4t22pk3doCclhV3r9g==
X-Received: by 2002:adf:9dca:: with SMTP id q10mr22166975wre.11.1585694545103;
        Tue, 31 Mar 2020 15:42:25 -0700 (PDT)
Received: from donizetti.redhat.com ([2001:b07:6468:f312:b55d:5ed2:8a41:41ea])
        by smtp.gmail.com with ESMTPSA id
 q13sm275388wrg.21.2020.03.31.15.42.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 31 Mar 2020 15:42:24 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: eesposit@redhat.com
Subject: [PATCH] KVM: x86: move kvm_create_vcpu_debugfs after last failure
 point
Date: Wed,  1 Apr 2020 00:42:22 +0200
Message-Id: <20200331224222.393439-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The placement of kvm_create_vcpu_debugfs is more or less irrelevant, since
it cannot fail and userspace should not care about the debugfs entries until
it knows the vcpu has been created.  Moving it after the last failure
point removes the need to remove the directory when unwinding the creation.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH 1/3] tools/kvm_stat: add command line switch '-z' to skip zero records
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11468331
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94C0715AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:00:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 737E520787
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 20:00:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730095AbgCaUAv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 16:00:51 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64712 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729210AbgCaUAv (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 16:00:51 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02VJWgxC116103
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 16:00:50 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 303wrwjmyy-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 16:00:50 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <raspl@linux.ibm.com>;
        Tue, 31 Mar 2020 21:00:34 +0100
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 31 Mar 2020 21:00:32 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02VK0i9K35061792
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 31 Mar 2020 20:00:44 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BFFFEA405C;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9ED22A4054;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 31 Mar 2020 20:00:44 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3] tools/kvm_stat: add command line switch '-z' to skip zero
 records
Date: Tue, 31 Mar 2020 22:00:40 +0200
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200331200042.2026-1-raspl@linux.ibm.com>
References: <20200331200042.2026-1-raspl@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20033120-0016-0000-0000-000002FBD95B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033120-0017-0000-0000-0000335F9A3A
Message-Id: <20200331200042.2026-2-raspl@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-03-31_07:2020-03-31,2020-03-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 mlxlogscore=999 clxscore=1015 bulkscore=0 malwarescore=0 suspectscore=1
 phishscore=0 priorityscore=1501 spamscore=0 adultscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003310160
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Stefan Raspl <raspl@de.ibm.com>

When running in logging mode, skip records with all zeros (=empty records)
to preserve space when logging to files.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat     | 47 +++++++++++++++++++++++++--------
 tools/kvm/kvm_stat/kvm_stat.txt |  4 +++
 2 files changed, 40 insertions(+), 11 deletions(-)

```
#### [PATCH v2 1/1] vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]
##### From: Sam Bobroff <sbobroff@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sam Bobroff <sbobroff@linux.ibm.com>
X-Patchwork-Id: 11466707
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F0AB912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 04:13:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0632520748
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 04:13:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726299AbgCaENC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 00:13:02 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:5542 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725809AbgCaENC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 00:13:02 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02V47IIq161990
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 00:13:01 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 303wrvrwsn-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 31 Mar 2020 00:13:00 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <sbobroff@linux.ibm.com>;
        Tue, 31 Mar 2020 05:12:52 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 31 Mar 2020 05:12:49 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02V4Ctaw46596210
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 31 Mar 2020 04:12:55 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2BB99A404D;
        Tue, 31 Mar 2020 04:12:55 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C9B27A4055;
        Tue, 31 Mar 2020 04:12:54 +0000 (GMT)
Received: from ozlabs.au.ibm.com (unknown [9.192.253.14])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 31 Mar 2020 04:12:54 +0000 (GMT)
Received: from osmium.ibmuc.com (unknown [9.211.70.38])
        (using TLSv1.2 with cipher DHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by ozlabs.au.ibm.com (Postfix) with ESMTPSA id E32E2A01F9;
        Tue, 31 Mar 2020 15:12:46 +1100 (AEDT)
From: Sam Bobroff <sbobroff@linux.ibm.com>
To: kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Cc: aik@ozlabs.ru
Subject: [PATCH v2 1/1] vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]
Date: Tue, 31 Mar 2020 15:12:46 +1100
X-Mailer: git-send-email 2.22.0.216.g00a2a96fc9
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20033104-0012-0000-0000-0000039B5A44
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20033104-0013-0000-0000-000021D864CB
Message-Id: 
 <6183bf8ec2dd0433f213e081911ab8fd5cac2dcb.1585627961.git.sbobroff@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-03-31_01:2020-03-30,2020-03-31 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 mlxlogscore=999 clxscore=1011 bulkscore=0 malwarescore=0 suspectscore=0
 phishscore=0 priorityscore=1501 spamscore=0 adultscore=0 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003310030
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Older versions of skiboot only provide a single value in the device
tree property "ibm,mmio-atsd", even when multiple Address Translation
Shoot Down (ATSD) registers are present. This prevents NVLink2 devices
(other than the first) from being used with vfio-pci because vfio-pci
expects to be able to assign a dedicated ATSD register to each NVLink2
device.

However, ATSD registers can be shared among devices. This change
allows vfio-pci to fall back to sharing the register at index 0 if
necessary.

Fixes: 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver")
Signed-off-by: Sam Bobroff <sbobroff@linux.ibm.com>
Reviewed-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
Patch set v2:
Patch 1/1: vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]
- Removed unnecessary warning.
- Added Fixes tag.

Patch set v1:
Patch 1/1: vfio-pci/nvlink2: Allow fallback to ibm,mmio-atsd[0]

 drivers/vfio/pci/vfio_pci_nvlink2.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost: make CONFIG_VHOST depend on CONFIG_EVENTFD
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11466629
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37EDE1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 02:29:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 13F23206F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 02:29:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZROjGUyh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729703AbgCaC3P (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 30 Mar 2020 22:29:15 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:20806 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727524AbgCaC3P (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 30 Mar 2020 22:29:15 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585621753;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=bMxprIBQqQRMXCnOZLQWsN8Wcsho2mjRA6po32bViiM=;
        b=ZROjGUyhp/XJoryGgDh+VKlm67r702ceiU3hYXeYXEiWKzECHngRYfwNdSiBoXynzpRfYV
        GBCq015y3U2OlCG00/9zcV8XOxA8YR0DEwW4FxOrgd28tsB9j/Q4/0coQCJzPE3WUNdnPY
        pBd2N+X1znRS01QdJXMj7h7HlvDiu7U=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-304-ZKHOHFzsO8yWiccJCaSzJg-1; Mon, 30 Mar 2020 22:29:11 -0400
X-MC-Unique: ZKHOHFzsO8yWiccJCaSzJg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 873B38017CE;
        Tue, 31 Mar 2020 02:29:10 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-115.pek2.redhat.com [10.72.12.115])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C0C0D5DA60;
        Tue, 31 Mar 2020 02:29:04 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        Randy Dunlap <rdunlap@infradead.org>
Subject: [PATCH] vhost: make CONFIG_VHOST depend on CONFIG_EVENTFD
Date: Tue, 31 Mar 2020 10:29:02 +0800
Message-Id: <20200331022902.12229-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit ec9d8449a99b ("vhost: refine vhost and vringh kconfig"),
CONFIG_VHOST could be enabled independently. This means we need make
CONFIG_VHOST depend on CONFIG_EVENTFD, otherwise we break compiling
without CONFIG_EVENTFD.

Reported-by: Randy Dunlap <rdunlap@infradead.org>
Fixes: ec9d8449a99b ("vhost: refine vhost and vringh kconfig")
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Randy Dunlap <rdunlap@infradead.org> # build-tested
---
 drivers/vhost/Kconfig | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/8] vhost: Create accessors for virtqueues private_data
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11468171
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DDD13912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 18:00:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B22E1214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 18:00:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gb9R5Yr8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727677AbgCaSAZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 14:00:25 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:23894 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726403AbgCaSAZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 31 Mar 2020 14:00:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585677623;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ejq1qV0bZ7JSSzHx+BezIAPlzBsCmIZo0gnP311dA2E=;
        b=gb9R5Yr8Cv/ZT3fJ9VfkehQ8ZpLfm2c7wKXXyE4Cd5mO0+vgn1A6hHQcwcObubQYqP2rdP
        fOkLCodGWH+sA++J+edW0tEW+rvSCZgKtfMx9M7QjZlBLvIxXRozoDCeXOnQWXbo1B27BS
        z3HntV5JRsHf8Im7bA4X+nEbI7O9i7M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-sZyTbHyOOkO-4k3-p-BSeg-1; Tue, 31 Mar 2020 14:00:20 -0400
X-MC-Unique: sZyTbHyOOkO-4k3-p-BSeg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B8475107ACC7;
        Tue, 31 Mar 2020 18:00:18 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-92.ams2.redhat.com
 [10.36.112.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2926F608E7;
        Tue, 31 Mar 2020 18:00:15 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
	=?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 kvm list <kvm@vger.kernel.org>, Halil Pasic <pasic@linux.ibm.com>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 Cornelia Huck <cohuck@redhat.com>, Stephen Rothwell <sfr@canb.auug.org.au>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH v2 1/8] vhost: Create accessors for virtqueues private_data
Date: Tue, 31 Mar 2020 19:59:59 +0200
Message-Id: <20200331180006.25829-2-eperezma@redhat.com>
In-Reply-To: <20200331180006.25829-1-eperezma@redhat.com>
References: <20200331180006.25829-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 drivers/vhost/net.c   | 28 +++++++++++++++-------------
 drivers/vhost/vhost.h | 28 ++++++++++++++++++++++++++++
 drivers/vhost/vsock.c | 14 +++++++-------
 3 files changed, 50 insertions(+), 20 deletions(-)

```
#### [PATCH v3 1/8] vhost: Create accessors for virtqueues private_data
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Eugenio Perez Martin <eperezma@redhat.com>
X-Patchwork-Id: 11468299
Return-Path: <SRS0=G+Gb=5Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5938A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:28:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 23DF5212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 31 Mar 2020 19:28:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="eLapzvi0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729974AbgCaT2X (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 31 Mar 2020 15:28:23 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:31944 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729153AbgCaT2W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 31 Mar 2020 15:28:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585682900;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=FxAXCiTCZfPvNLBLEG0KFEFRm0rsHUjtPX41vvdno7o=;
        b=eLapzvi0QCKK0ClRdNzVcI2mjr8HknCih0P6kR1IjKfUpj2MjtWM9uoGg32UEpo/Ri29cw
        +ZEnaECzhVdbd3vz9IvAYz41y5H+GZzI0rSsZuf72hMM72+vvoN/YRZ6rlDL9pBi+tZiXG
        ob1j9b9nrg102A2N2jfHwiThL1veThA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-444-cOwCB58kPi-YOwmhQfoQgg-1; Tue, 31 Mar 2020 15:28:17 -0400
X-MC-Unique: cOwCB58kPi-YOwmhQfoQgg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8F8611005513;
        Tue, 31 Mar 2020 19:28:15 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-112-92.ams2.redhat.com
 [10.36.112.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 52DFE8EA1A;
        Tue, 31 Mar 2020 19:28:13 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Stephen Rothwell <sfr@canb.auug.org.au>, kvm list <kvm@vger.kernel.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Halil Pasic <pasic@linux.ibm.com>, Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH v3 1/8] vhost: Create accessors for virtqueues private_data
Date: Tue, 31 Mar 2020 21:27:57 +0200
Message-Id: <20200331192804.6019-2-eperezma@redhat.com>
In-Reply-To: <20200331192804.6019-1-eperezma@redhat.com>
References: <20200331192804.6019-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
---
 drivers/vhost/net.c   | 28 +++++++++++++++-------------
 drivers/vhost/scsi.c  | 14 +++++++-------
 drivers/vhost/test.c  | 10 +++++-----
 drivers/vhost/vhost.h | 27 +++++++++++++++++++++++++++
 drivers/vhost/vsock.c | 14 +++++++-------
 5 files changed, 61 insertions(+), 32 deletions(-)

```
