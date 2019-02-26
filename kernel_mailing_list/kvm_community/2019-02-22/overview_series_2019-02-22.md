#### [PATCH 01/27] clocksource/arm_arch_timer: Store physical timer IRQ number for KVM on VHE
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Andre Przywara <andre.przywara@arm.com>

A host running in VHE mode gets the EL2 physical timer as its time
source (accessed using the EL1 sysreg accessors, which get re-directed
to the EL2 sysregs by VHE).

The EL1 physical timer remains unused by the host kernel, allowing us to
pass that on directly to a KVM guest and saves us from emulating this
timer for the guest on VHE systems.

Store the EL1 Physical Timer's IRQ number in
struct arch_timer_kvm_info on VHE systems to allow KVM to use it.

Acked-by: Daniel Lezcano <daniel.lezcano@linaro.org>
Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 drivers/clocksource/arm_arch_timer.c | 11 +++++++++--
 include/clocksource/arm_arch_timer.h |  1 +
 2 files changed, 10 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] s390/cio: Fix vfio-ccw handling of recursive TICs
##### From: Eric Farman <farman@linux.ibm.com>

```c
The routine ccwchain_calc_length() is tasked with looking at a
channel program, seeing how many CCWs are chained together by
the presence of the Chain-Command flag, and returning a count
to the caller.

Previously, it also considered a Transfer-in-Channel CCW as being
an appropriate mechanism for chaining.  The problem at the time
was that the TIC CCW will almost certainly not go to the next CCW
in memory (because the CC flag would be sufficient), and so
advancing to the next 8 bytes will cause us to read potentially
invalid memory.  So that comparison was removed, and the target
of the TIC is processed as a new chain.

This is fine when a TIC goes to a new chain (consider a NOP+TIC to
a channel program that is being redriven), but there is another
scenario where this falls apart.  A TIC can be used to "rewind"
a channel program, for example to find a particular record on a
disk with various orientation CCWs.  In this case, we DO want to
consider the memory after the TIC since the TIC will be skipped
once the requested criteria is met.  This is due to the Status
Modifier presented by the device, though software doesn't need to
operate on it beyond understanding the behavior change of how the
channel program is executed.

So to handle this, we will re-introduce the check for a TIC CCW
but limit it by examining the target of the TIC.  If the TIC
doesn't go back into the current chain, then current behavior
applies; we should stop counting CCWs and let the target of the
TIC be handled as a new chain.  But, if the TIC DOES go back into
the current chain, then we need to keep looking at the memory after
the TIC for when the channel breaks out of the TIC loop.  We can't
use tic_target_chain_exists() because the chain in question hasn't
been built yet, so we will redefine that comparison with some small
functions to make it more readable and to permit refactoring later.

Fixes: 405d566f98ae ("vfio-ccw: Don't assume there are more ccws after a TIC")
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---

The commit in question is queued in the s390/features branch for
the 5.1 merge window.
---
 drivers/s390/cio/vfio_ccw_cp.c | 37 ++++++++++++++++++++++++++++++++++++-
 1 file changed, 36 insertions(+), 1 deletion(-)

```
#### [GIT PULL 01/18] KVM: s390: clarify kvm related kernel message
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From: Michael Mueller <mimu@linux.ibm.com>

As suggested by our ID dept. here are some kernel message
updates.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [GIT PULL] KVM/arm updates for Linux v5.1
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

This is the KVM/arm updates for Linux v5.1, much smaller than expected, as
most of the stuff we were hoping to queue missed the merge window. Oh well,
5.2 will be "interesting".

This time, we have a bunch of changes that prepare the landing of the some
of the nested virt code, some optimisations on the timer emulation (direct
assignment of the physical timer on VHE systems), some better type-safety
checks for the HYP code, Set/Way optimisations for silly 32bit guests, and a
bunch of cleanups here and there. Oh, and a MAINTAINERS update to officially
mention that we have a set of dedicated reviewers working with us!

Note that the first patch hits code that is outside of the KVM tree, but
that Daniel has agreed to us taking directly given that it was required for
a lot of other things in this drop.

Please pull,

	M.

The following changes since commit 49a57857aeea06ca831043acbb0fa5e0f50602fd:

  Linux 5.0-rc3 (2019-01-21 13:14:44 +1300)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-for-v5.1

for you to fetch changes up to c88b093693ccbe41991ef2e9b1d251945e6e54ed:

  arm64: KVM: Fix architecturally invalid reset value for FPEXC32_EL2 (2019-02-22 09:59:20 +0000)

----------------------------------------------------------------
KVM/arm updates for Linux v5.1

- A number of pre-nested code rework
- Direct physical timer assignment on VHE systems
- kvm_call_hyp type safety enforcement
- Set/Way cache sanitisation for 32bit guests
- Build system cleanups
- A bunch of janitorial fixes

----------------------------------------------------------------
Andre Przywara (2):
      clocksource/arm_arch_timer: Store physical timer IRQ number for KVM on VHE
      KVM: arm/arm64: consolidate arch timer trap handlers

Ard Biesheuvel (2):
      arm64: KVM: Expose sanitised cache type register to guest
      arm64: KVM: Describe data or unified caches as having 1 set and 1 way

Christoffer Dall (6):
      KVM: arm/arm64: Factor out VMID into struct kvm_vmid
      KVM: arm/arm64: Simplify bg_timer programming
      KVM: arm/arm64: timer: Rework data structures for multiple timers
      KVM: arm/arm64: arch_timer: Assign the phys timer on VHE systems
      KVM: arm/arm64: Rework the timer code to use a timer_map
      KVM: arm/arm64: Move kvm_is_write_fault to header file

Colin Ian King (1):
      KVM: arm/arm64: fix spelling mistake: "auxilary" -> "auxiliary"

Dave Martin (1):
      arm64: KVM: Fix architecturally invalid reset value for FPEXC32_EL2

Marc Zyngier (9):
      arm/arm64: KVM: Introduce kvm_call_hyp_ret()
      arm64: KVM: Allow for direct call of HYP functions when using VHE
      arm64: KVM: Drop VHE-specific HYP call stub
      ARM: KVM: Teach some form of type-safety to kvm_call_hyp
      arm/arm64: KVM: Statically configure the host's view of MPIDR
      KVM: arm64: Fix ICH_ELRSR_EL2 sysreg naming
      KVM: arm64: Reuse sys_reg() macro when searching the trap table
      KVM: arm/arm64: arch_timer: Mark physical interrupt active when a virtual interrupt is pending
      KVM: arm/arm64: Update MAINTAINERS entries

Masahiro Yamada (3):
      KVM: arm/arm64: Fix TRACE_INCLUDE_PATH
      KVM: arm/arm64: Remove -I. header search paths
      KVM: arm/arm64: Prefix header search paths with $(srctree)/

Shaokun Zhang (2):
      KVM: arm/arm64: Remove unused gpa_end variable
      KVM: arm/arm64: Remove unused timer variable

Zenghui Yu (1):
      KVM: arm64: Fix comment for KVM_PHYS_SHIFT

 MAINTAINERS                          |  18 +-
 arch/arm/include/asm/arch_gicv3.h    |   4 +-
 arch/arm/include/asm/kvm_emulate.h   |   8 +
 arch/arm/include/asm/kvm_host.h      |  53 ++-
 arch/arm/include/asm/kvm_hyp.h       |   4 +
 arch/arm/include/asm/kvm_mmu.h       |   9 +-
 arch/arm/kvm/Makefile                |   5 +-
 arch/arm/kvm/coproc.c                |  23 +-
 arch/arm/kvm/hyp/cp15-sr.c           |   1 -
 arch/arm/kvm/hyp/hyp-entry.S         |   2 +-
 arch/arm/kvm/hyp/switch.c            |   2 +-
 arch/arm/kvm/hyp/tlb.c               |   4 +-
 arch/arm/kvm/interrupts.S            |   4 +-
 arch/arm64/include/asm/kvm_emulate.h |  12 +
 arch/arm64/include/asm/kvm_host.h    |  48 ++-
 arch/arm64/include/asm/kvm_hyp.h     |   3 +-
 arch/arm64/include/asm/kvm_mmu.h     |  13 +-
 arch/arm64/include/asm/sysreg.h      |   7 +-
 arch/arm64/kvm/Makefile              |   4 +-
 arch/arm64/kvm/debug.c               |   2 +-
 arch/arm64/kvm/hyp.S                 |   3 -
 arch/arm64/kvm/hyp/hyp-entry.S       |  12 -
 arch/arm64/kvm/hyp/sysreg-sr.c       |   1 -
 arch/arm64/kvm/sys_regs.c            | 168 ++++++----
 drivers/clocksource/arm_arch_timer.c |  11 +-
 include/clocksource/arm_arch_timer.h |   1 +
 include/kvm/arm_arch_timer.h         |  68 ++--
 virt/kvm/arm/arch_timer.c            | 608 ++++++++++++++++++++++++-----------
 virt/kvm/arm/arm.c                   |  64 ++--
 virt/kvm/arm/hyp/vgic-v3-sr.c        |   2 +-
 virt/kvm/arm/mmu.c                   |  18 +-
 virt/kvm/arm/trace.h                 | 107 +++++-
 virt/kvm/arm/vgic/vgic-v3.c          |   4 +-
 33 files changed, 909 insertions(+), 384 deletions(-)

From patchwork Fri Feb 22 16:25:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 10826531
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6546713B5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 22 Feb 2019 16:27:04 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 4DA58313C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 22 Feb 2019 16:27:04 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 3E174314D4; Fri, 22 Feb 2019 16:27:04 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id BDFFE313C6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 22 Feb 2019 16:27:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726984AbfBVQ1C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 22 Feb 2019 11:27:02 -0500
Received: from usa-sjc-mx-foss1.foss.arm.com ([217.140.101.70]:35886 "EHLO
        foss.arm.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726951AbfBVQ1C (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 22 Feb 2019 11:27:02 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.72.51.249])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3761080D;
        Fri, 22 Feb 2019 08:27:02 -0800 (PST)
Received: from big-swifty.lan (usa-sjc-mx-foss1.foss.arm.com [217.140.101.70])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1ACB53F5C1;
        Fri, 22 Feb 2019 08:26:56 -0800 (PST)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andre Przywara <andre.przywara@arm.com>,
        Ard Biesheuvel <ard.biesheuvel@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Colin Ian King <colin.king@canonical.com>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Dave Martin <Dave.Martin@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Masahiro Yamada <yamada.masahiro@socionext.com>,
        Shaokun Zhang <zhangshaokun@hisilicon.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 02/27] arm/arm64: KVM: Introduce kvm_call_hyp_ret()
Date: Fri, 22 Feb 2019 16:25:40 +0000
Message-Id: <20190222162605.5054-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190222162605.5054-1-marc.zyngier@arm.com>
References: <20190222162605.5054-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Until now, we haven't differentiated between HYP calls that
have a return value and those who don't. As we're about to
change this, introduce kvm_call_hyp_ret(), and change all
call sites that actually make use of a return value.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Acked-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm/include/asm/kvm_host.h   | 3 +++
 arch/arm64/include/asm/kvm_host.h | 1 +
 arch/arm64/kvm/debug.c            | 2 +-
 virt/kvm/arm/arm.c                | 2 +-
 virt/kvm/arm/vgic/vgic-v3.c       | 4 ++--
 5 files changed, 8 insertions(+), 4 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-5.1-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-5.1-1 tag to get a PPC KVM
update for 5.1.  There is nothing major in there, just a collection of
bug fixes and minor improvements.

Thanks,
Paul.

The following changes since commit d13937116f1e82bf508a6325111b322c30c85eb9:

  Linux 5.0-rc6 (2019-02-10 14:42:20 -0800)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.1-1

for you to fetch changes up to 0a0c50f771f577b05f5a1ac9867d296d02a5e51c:

  Merge remote-tracking branch 'remotes/powerpc/topic/ppc-kvm' into kvm-ppc-next (2019-02-22 13:52:30 +1100)

----------------------------------------------------------------
PPC KVM update for 5.1

There are no major new features this time, just a collection of bug
fixes and improvements in various areas, including machine check
handling and context switching of protection-key-related registers.

----------------------------------------------------------------
Alexey Kardashevskiy (2):
      KVM: PPC: Release all hardware TCE tables attached to a group
      KVM: PPC: Book3S: Improve KVM reference counting

Jordan Niethe (1):
      KVM: PPC: Book3S HV: Fix build failure without IOMMU support

Masahiro Yamada (1):
      KVM: PPC: Remove -I. header search paths

Michael Ellerman (2):
      KVM: PPC: Book3S HV: Context switch AMR on Power9
      powerpc/kvm: Save and restore host AMR/IAMR/UAMOR

Paul Mackerras (5):
      KVM: PPC: Book3S PR: Add emulation for slbfee. instruction
      KVM: PPC: Book3S: Allow XICS emulation to work in nested hosts using XIVE
      KVM: PPC: Book3S HV: Simplify machine check handling
      powerpc/64s: Better printing of machine check info for guest MCEs
      Merge remote-tracking branch 'remotes/powerpc/topic/ppc-kvm' into kvm-ppc-next

Suraj Jitindar Singh (2):
      KVM: PPC: Book3S HV: Optimise mmio emulation for devices on FAST_MMIO_BUS
      KVM: PPC: Book3S HV: Add KVM stat largepages_[2M/1G]

wangbo (1):
      KVM: PPC: Book3S HV: Replace kmalloc_node+memset with kzalloc_node

 arch/powerpc/include/asm/kvm_host.h     |  3 ++
 arch/powerpc/include/asm/kvm_ppc.h      | 17 +++++++-
 arch/powerpc/include/asm/mce.h          |  2 +-
 arch/powerpc/kernel/mce.c               |  8 ++--
 arch/powerpc/kvm/Makefile               |  5 ---
 arch/powerpc/kvm/book3s.c               | 20 ++++++---
 arch/powerpc/kvm/book3s_32_mmu.c        |  1 +
 arch/powerpc/kvm/book3s_64_mmu.c        | 14 ++++++
 arch/powerpc/kvm/book3s_64_mmu_hv.c     | 18 ++++++++
 arch/powerpc/kvm/book3s_64_mmu_radix.c  | 15 ++++++-
 arch/powerpc/kvm/book3s_64_vio.c        |  8 ++--
 arch/powerpc/kvm/book3s_emulate.c       | 18 ++++++++
 arch/powerpc/kvm/book3s_hv.c            | 47 +++++++++++++-------
 arch/powerpc/kvm/book3s_hv_builtin.c    | 14 +++---
 arch/powerpc/kvm/book3s_hv_ras.c        | 58 ++++++-------------------
 arch/powerpc/kvm/book3s_hv_rm_xics.c    |  7 +++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 76 +++++++++++++--------------------
 arch/powerpc/kvm/book3s_rtas.c          |  8 ++--
 arch/powerpc/kvm/powerpc.c              |  4 +-
 arch/powerpc/platforms/powernv/opal.c   |  2 +-
 20 files changed, 206 insertions(+), 139 deletions(-)
```
#### [GIT PULL] VFIO updates for v5.1-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

Sorry for the duplicate, botched the [GIT PULL] first time around.
This is for the next merge window.  Thanks!

The following changes since commit 8834f5600cf3c8db365e18a3d5cac2c2780c81e5:

  Linux 5.0-rc5 (2019-02-03 13:48:04 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.1-rc1

for you to fetch changes up to 0cfd027be1d6def4a462cdc180c055143af24069:

  vfio_pci: Enable memory accesses before calling pci_map_rom (2019-02-18 14:57:50 -0700)

----------------------------------------------------------------
VFIO updates for v5.1-rc1

 - Switch mdev to generic UUID API (Andy Shevchenko)

 - Fixup platform reset include paths (Masahiro Yamada)

 - Fix usage of MINORMASK (Chengguang Xu)

 - Remove noise from duplicate spapr table unsets (Alexey Kardashevskiy)

 - Restore device state after PM reset (Alex Williamson)

 - Ensure memory translation enabled for PCI ROM access (Eric Auger)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/pci: Restore device state on PM transition

Alexey Kardashevskiy (1):
      vfio/spapr_tce: Skip unsetting already unset table

Andy Shevchenko (1):
      vfio-mdev: Switch to use new generic UUID API

Chengguang Xu (4):
      vfio: expand minor range when registering chrdev region
      samples/vfio-mdev/mbochs: expand minor range when registering chrdev region
      samples/vfio-mdev/mdpy: expand minor range when registering chrdev region
      samples/vfio-mdev/mtty: expand minor range when registering chrdev region

Eric Auger (1):
      vfio_pci: Enable memory accesses before calling pci_map_rom

Masahiro Yamada (1):
      vfio: platform: reset: fix up include directives to remove ccflags-y

 drivers/vfio/mdev/mdev_core.c                      | 16 ++--
 drivers/vfio/mdev/mdev_private.h                   |  5 +-
 drivers/vfio/mdev/mdev_sysfs.c                     |  6 +-
 drivers/vfio/pci/vfio_pci.c                        | 90 ++++++++++++++++++----
 drivers/vfio/pci/vfio_pci_config.c                 |  2 +-
 drivers/vfio/pci/vfio_pci_private.h                |  6 ++
 drivers/vfio/platform/reset/Makefile               |  2 -
 .../vfio/platform/reset/vfio_platform_amdxgbe.c    |  2 +-
 .../vfio/platform/reset/vfio_platform_bcmflexrm.c  |  2 +-
 .../platform/reset/vfio_platform_calxedaxgmac.c    |  2 +-
 drivers/vfio/vfio.c                                |  8 +-
 drivers/vfio/vfio_iommu_spapr_tce.c                |  3 +-
 include/linux/mdev.h                               |  2 +-
 samples/vfio-mdev/mbochs.c                         |  8 +-
 samples/vfio-mdev/mdpy.c                           |  8 +-
 samples/vfio-mdev/mtty.c                           | 17 ++--
 16 files changed, 125 insertions(+), 54 deletions(-)
```
#### [PATCH v3 1/2] KVM: arm/arm64: Add save/restore support for firmware workaround state
##### From: Andre Przywara <andre.przywara@arm.com>

```c
KVM implements the firmware interface for mitigating cache speculation
vulnerabilities. Guests may use this interface to ensure mitigation is
active.
If we want to migrate such a guest to a host with a different support
level for those workarounds, migration might need to fail, to ensure that
critical guests don't loose their protection.

Introduce a way for userland to save and restore the workarounds state.
On restoring we do checks that make sure we don't downgrade our
mitigation level.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Steven Price <steven.price@arm.com>
---
 arch/arm/include/asm/kvm_emulate.h   |  10 +++
 arch/arm/include/uapi/asm/kvm.h      |  10 +++
 arch/arm64/include/asm/kvm_emulate.h |  14 ++++
 arch/arm64/include/uapi/asm/kvm.h    |   9 ++
 virt/kvm/arm/psci.c                  | 119 +++++++++++++++++++++++----
 5 files changed, 146 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: Minor cleanups for kvm_main.c
##### From: Leo Yan <leo.yan@linaro.org>

```c
This patch contains two minor cleanups: firstly it puts exported symbol
for kvm_io_bus_write() by following the function definition; secondly it
removes a redundant blank line.

Signed-off-by: Leo Yan <leo.yan@linaro.org>
---
 virt/kvm/kvm_main.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2 01/16] powerpc/xive: add OPAL extensions for the XIVE native exploitation support
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The support for XIVE native exploitation mode in Linux/KVM needs a
couple more OPAL calls to configure the sPAPR guest and to get/set the
state of the XIVE internal structures.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/opal-api.h           | 11 ++-
 arch/powerpc/include/asm/opal.h               |  7 ++
 arch/powerpc/include/asm/xive.h               | 14 +++
 arch/powerpc/sysdev/xive/native.c             | 99 +++++++++++++++++++
 .../powerpc/platforms/powernv/opal-wrappers.S |  3 +
 5 files changed, 130 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: SVM: fix boolreturn.cocci warnings
##### From: kbuild test robot <lkp@intel.com>

```c
From: kbuild test robot <lkp@intel.com>

arch/x86/kvm/vmx/vmx.c:7413:8-9: WARNING: return of 0/1 in function 'vmx_need_emulation_on_page_fault' with return type bool

 Return statements in functions returning bool should use
 true/false instead of 1/0.
Generated by: scripts/coccinelle/misc/boolreturn.cocci

Fixes: 4589eecce385 ("KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)")
CC: Singh, Brijesh <brijesh.singh@amd.com>
Signed-off-by: kbuild test robot <fengguang.wu@intel.com>
---

tree:   https://git.kernel.org/pub/scm/virt/kvm/kvm.git queue
head:   c36edbda86dd5ceeed2bfa94375286074cee72a4
commit: 4589eecce385c0bc5d3bd065ab850f00ef828356 [97/98] KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)

 vmx.c |    2 +-
```
#### [PATCH kvm-unit-tests v3] tap13: list testcases individually
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Stefan Raspl <raspl@linux.ibm.com>

The current tap13 support summarizes testcases on a rather coarse
granularity. Which sort of defeats the purpose, especially in CI
environments, where having results for individual tests to pinpoint
problems helps a lot.

To improve things, this patch makes TAP mode bypass print_result and extract
results for individual testcases as they are sent to the log file.  It then
introduces test case numbers and writes the plan at the end.

One could argue that post-processing the logs is a rather fragile approach.
Which is true - but apparently already the case, see e.g. extract_summary
in scripts/runtime.bash. Plus this is quite cheap, while a proper solution
would require to modify the kernels, so we can e.g. pass in a counter for
the test case number. And we would probably have to come up with reasonable
test case names, while this approach simply derives them from each test
output.

Before:
  $ ./run_tests.sh -t
  TAP version 13
  ok selftest-setup
  ok intercept
  ok emulator
  ok sieve
  ok sthyi
  ok skey
  ok diag10
  ok pfmf
  ok cmm
  ok vector
  ok gs # SKIP
  ok iep # SKIP
  1..12

After:
  $ ./run_tests.sh -t
  TAP version 13
  ok 1 - cmm: privileged: Program interrupt: expected(2)
  ok 2 - cmm: invalid ORC 8: Program interrupt: expected(6)
  ok 3 - diag10: lowcore freeing: 0x0000/0x0000: Program interrupt: expected(6)
  ok 4 - diag10: lowcore freeing: 0x1000/0x1000: Program interrupt: expected(6)
  ok 5 - diag10: lowcore freeing: 0x0000/0x1000: Program interrupt: expected(6)
  ok 6 - diag10: start/end: end < start: Program interrupt: expected(6)
  ok 7 - diag10: start/end: unaligned start: Program interrupt: expected(6)
  ok 8 - diag10: start/end: unaligned end: Program interrupt: expected(6)
  ok 9 - diag10: privileged: Program interrupt: expected(2)
  ok 10 - emulator: spm/ipm: cc=0,key=f: bit 32 and 33 set to zero
  ok 11 - emulator: spm/ipm: cc=0,key=f: bit 0-31, 40-63 unchanged
  ok 12 - emulator: spm/ipm: cc=0,key=f: cc and key applied
  ok 13 - emulator: spm/ipm: cc=1,key=9: bit 32 and 33 set to zero
  1..180
  [...]

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
[Almost rewritten, but still giving a lot of credit to Stefan. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 run_tests.sh         | 59 +++++++++++++++++++++++++++++++++++++++++++---------
 scripts/runtime.bash | 19 +++--------------
 2 files changed, 52 insertions(+), 26 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/2] tap13: list testcases individually
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
The current tap13 support summarizes testcases on a rather coarse
granularity. Which sort of defeats the purpose, especially in CI
environments, where having results for individual tests to pinpoint
problems helps a lot. Plus it can be convenient to have the plan in front
of the individual testcases.
This patch improves things by post-processing the log files, extracting
results for individual testcases, introduces test case numbers and puts the
plan in front of the test case results.
One could argue that post-processing the logs is a rather fragile approach.
Which is true - but apparently already the case, see e.g. extract_summary
in scripts/runtime.bash. Plus this is quite cheap, while a proper solution
would require to modify the kernels, so we can e.g. pass in a counter for
the test case number. And we would probably have to come up with reasonable
test case names, while this approach simply derives them from each test
output.

Before:
  $ ./run_tests.sh -t
  TAP version 13
  ok selftest-setup
  ok intercept
  ok emulator
  ok sieve
  ok sthyi
  ok skey
  ok diag10
  ok pfmf
  ok cmm
  ok vector
  ok gs # SKIP
  ok iep # SKIP
  1..12

After:
  $ ./run_tests.sh -t
  TAP version 13
  1..180
  ok 1 - cmm: privileged: Program interrupt: expected(2)
  ok 2 - cmm: invalid ORC 8: Program interrupt: expected(6)
  ok 3 - diag10: lowcore freeing: 0x0000/0x0000: Program interrupt: expected(6)
  ok 4 - diag10: lowcore freeing: 0x1000/0x1000: Program interrupt: expected(6)
  ok 5 - diag10: lowcore freeing: 0x0000/0x1000: Program interrupt: expected(6)
  ok 6 - diag10: start/end: end < start: Program interrupt: expected(6)
  ok 7 - diag10: start/end: unaligned start: Program interrupt: expected(6)
  ok 8 - diag10: start/end: unaligned end: Program interrupt: expected(6)
  ok 9 - diag10: privileged: Program interrupt: expected(2)
  ok 10 - emulator: spm/ipm: cc=0,key=f: bit 32 and 33 set to zero
  ok 11 - emulator: spm/ipm: cc=0,key=f: bit 0-31, 40-63 unchanged
  ok 12 - emulator: spm/ipm: cc=0,key=f: cc and key applied
  ok 13 - emulator: spm/ipm: cc=1,key=9: bit 32 and 33 set to zero
  [...]

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 run_tests.sh         | 10 +++++++---
 scripts/runtime.bash | 47 +++++++++++++++++++++++++++++++++++++++--------
 2 files changed, 46 insertions(+), 11 deletions(-)

```
#### [PATCH v7 1/9] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, subsets of a PCI function can be isolated
from each others by the IOMMU. As a result, there is a
request in software to attach multiple domains to a physical
PCI device. One example of such use model is the Intel
Scalable IOV [1] [2]. The Intel vt-d 3.0 spec [3] introduces
the scalable mode which enables PASID granularity DMA
isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs include:

* iommu_dev_has_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Detect both IOMMU and PCI endpoint devices supporting
    the feature (aux-domain here) without the host driver
    dependency.

* iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX)
  - Check the enabling status of the feature (aux-domain
    here). The aux-domain interfaces are available only
    if this returns true.
* iommu_dev_enable/disable_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Enable/disable device specific aux-domain feature.

* iommu_aux_attach_device(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_aux_detach_device(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_aux_get_pasid(domain, dev)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalable IOV needs
    to write this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

This has been updated with the latest proposal from Joerg
posted here [5].

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Joerg Roedel <joro@8bytes.org>

and some discussions can be found here [4] [5].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4
[5] https://www.spinics.net/lists/iommu/msg31874.html

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Suggested-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/iommu/iommu.c | 96 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 70 +++++++++++++++++++++++++++++++
 2 files changed, 166 insertions(+)

```
#### [PATCH v4 1/7] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command.

We inject the correct exceptions from inside KVM for the case the
callback is not initialized, which happens when the vfio_ap driver
is not loaded.

If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/kvm/priv.c             | 52 ++++++++++++++++++++++++++++++++++++++++
 2 files changed, 53 insertions(+)

```
#### [PATCH v7 2/9] iommu/vt-d: Move enable pasid out of CONFIG_INTEL_IOMMU_SVM
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
This moves intel_iommu_enable_pasid() out of the scope of
CONFIG_INTEL_IOMMU_SVM with more and more features requiring
pasid function.

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel-iommu.c | 22 +++++++---------------
 drivers/iommu/intel-svm.c   | 19 ++++++++++++++++++-
 include/linux/intel-iommu.h |  2 +-
 3 files changed, 26 insertions(+), 17 deletions(-)

```
#### VFIO updates for v5.1-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

An early pull request for the v5.1 merge window.

The following changes since commit 8834f5600cf3c8db365e18a3d5cac2c2780c81e5:

  Linux 5.0-rc5 (2019-02-03 13:48:04 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.1-rc1

for you to fetch changes up to 0cfd027be1d6def4a462cdc180c055143af24069:

  vfio_pci: Enable memory accesses before calling pci_map_rom (2019-02-18 14:57:50 -0700)

----------------------------------------------------------------
VFIO updates for v5.1-rc1

 - Switch mdev to generic UUID API (Andy Shevchenko)

 - Fixup platform reset include paths (Masahiro Yamada)

 - Fix usage of MINORMASK (Chengguang Xu)

 - Remove noise from duplicate spapr table unsets (Alexey Kardashevskiy)

 - Restore device state after PM reset (Alex Williamson)

 - Ensure memory translation enabled for PCI ROM access (Eric Auger)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/pci: Restore device state on PM transition

Alexey Kardashevskiy (1):
      vfio/spapr_tce: Skip unsetting already unset table

Andy Shevchenko (1):
      vfio-mdev: Switch to use new generic UUID API

Chengguang Xu (4):
      vfio: expand minor range when registering chrdev region
      samples/vfio-mdev/mbochs: expand minor range when registering chrdev region
      samples/vfio-mdev/mdpy: expand minor range when registering chrdev region
      samples/vfio-mdev/mtty: expand minor range when registering chrdev region

Eric Auger (1):
      vfio_pci: Enable memory accesses before calling pci_map_rom

Masahiro Yamada (1):
      vfio: platform: reset: fix up include directives to remove ccflags-y

 drivers/vfio/mdev/mdev_core.c                      | 16 ++--
 drivers/vfio/mdev/mdev_private.h                   |  5 +-
 drivers/vfio/mdev/mdev_sysfs.c                     |  6 +-
 drivers/vfio/pci/vfio_pci.c                        | 90 ++++++++++++++++++----
 drivers/vfio/pci/vfio_pci_config.c                 |  2 +-
 drivers/vfio/pci/vfio_pci_private.h                |  6 ++
 drivers/vfio/platform/reset/Makefile               |  2 -
 .../vfio/platform/reset/vfio_platform_amdxgbe.c    |  2 +-
 .../vfio/platform/reset/vfio_platform_bcmflexrm.c  |  2 +-
 .../platform/reset/vfio_platform_calxedaxgmac.c    |  2 +-
 drivers/vfio/vfio.c                                |  8 +-
 drivers/vfio/vfio_iommu_spapr_tce.c                |  3 +-
 include/linux/mdev.h                               |  2 +-
 samples/vfio-mdev/mbochs.c                         |  8 +-
 samples/vfio-mdev/mdpy.c                           |  8 +-
 samples/vfio-mdev/mtty.c                           | 17 ++--
 16 files changed, 125 insertions(+), 54 deletions(-)
```
#### [PATCH] x86/Hyper-V: Fix definition HV_MAX_FLUSH_REP_COUNT
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

The max flush rep count of HvFlushGuestPhysicalAddressList hypercall
is equal with how many entries of union hv_gpa_page_range can be populated
into the input parameter page. The origin code lacks parenthesis around
PAGE_SIZE - 2 * sizeof(u64). This patch is to fix it.

Cc: <stable@vger.kernel.org>
Fixs: cc4edae4b9(x86/hyper-v: Add HvFlushGuestAddressList hypercall support)
Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V3 1/10] X86/Hyper-V: Add parameter offset for hyperv_fill_flush_guest_mapping_list()
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add parameter offset to specify start position to add flush ranges in
guest address list of struct hv_guest_mapping_flush_list.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/hyperv/nested.c        | 4 ++--
 arch/x86/include/asm/mshyperv.h | 2 +-
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/kvm/mmu: fix switch between root and guest MMUs
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Commit 14c07ad89f4d ("x86/kvm/mmu: introduce guest_mmu") brought one subtle
change: previously, when switching back from L2 to L1, we were resetting
MMU hooks (like mmu->get_cr3()) in kvm_init_mmu() called from
nested_vmx_load_cr3() and now we do that in nested_ept_uninit_mmu_context()
when we re-target vcpu->arch.mmu pointer.
The change itself looks logical: if nested_ept_init_mmu_context() changes
something than nested_ept_uninit_mmu_context() restores it back. There is,
however, one thing: the following call chain:

 nested_vmx_load_cr3()
  kvm_mmu_new_cr3()
    __kvm_mmu_new_cr3()
      fast_cr3_switch()
        cached_root_available()

now happens with MMU hooks pointing to the new MMU (root MMU in our case)
while previously it was happening with the old one. cached_root_available()
tries to stash current root but it is incorrect to read current CR3 with
mmu->get_cr3(), we need to use old_mmu->get_cr3() which in case we're
switching from L2 to L1 is guest_mmu. (BTW, in shadow page tables case this
is a non-issue because we don't switch MMU).

While we could've tried to guess that we're switching between MMUs and call
the right ->get_cr3() from cached_root_available() this seems to be overly
complicated. Instead, just stash the corresponding CR3 when setting
root_hpa and make cached_root_available() use the stashed value.

Fixes: 14c07ad89f4d ("x86/kvm/mmu: introduce guest_mmu")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu.c              | 17 +++++++++++++----
 2 files changed, 14 insertions(+), 4 deletions(-)

```
#### [PATCH] x86/kvm/mmu: make mmu->prev_roots cache work for NPT case
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
I noticed that fast_cr3_switch() always fails when we switch back from L2
to L1 as it is not able to find a cached root. This is odd: host's CR3
usually stays the same, we expect to always follow the fast path. Turns
out the problem is that page role is always mismatched because
kvm_mmu_get_page() filters out cr4_pae when direct, the value is stored
in page header and later compared with new_role in cached_root_available().
As cr4_pae is always set in long mode prev_roots cache is dysfunctional.

The problem appeared after we introduced kvm_calc_mmu_role_common():
previously, we were only setting this bit for shadow MMU root but now
we set it for everything. Restore the original behavior.

Fixes: 7dcd57552008 ("x86/kvm/mmu: check if tdp/shadow MMU reconfiguration is needed")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
RFC:
Alternatively, I can suggest two solutions:
- Do not clear cr4_pae in kvm_mmu_get_page() and check direct on call sites
 (detect_write_misaligned(), get_written_sptes()).
- Filter cr4_pae out when direct in kvm_mmu_new_cr3().
The code in kvm_mmu_get_page() is very ancient, I'm afraid to touch it :=)
---
 arch/x86/kvm/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
