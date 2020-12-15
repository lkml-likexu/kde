#### [GIT PULL] KVM/arm64 updates for 5.11
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11972617
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D75F8C2BB48
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:50:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 91E74221EF
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:50:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2438801AbgLNRuW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 12:50:22 -0500
Received: from mail.kernel.org ([198.145.29.99]:54278 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2440510AbgLNRuM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 12:50:12 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 19CD121534;
        Mon, 14 Dec 2020 17:49:30 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1koryR-001EtV-Lu; Mon, 14 Dec 2020 17:49:27 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        David Brazdil <dbrazdil@google.com>,
        James Morse <james.morse@arm.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Shenming Lu <lushenming@huawei.com>,
        Steven Price <steven.price@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm64 updates for 5.11
Date: Mon, 14 Dec 2020 17:48:48 +0000
Message-Id: <20201214174848.1501502-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, catalin.marinas@arm.com, dbrazdil@google.com,
 james.morse@arm.com, zhukeqian1@huawei.com, mark.rutland@arm.com,
 lushenming@huawei.com, steven.price@arm.com, will@kernel.org,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, linux-arm-kernel@lists.infradead.org,
 kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the initial set of KVM/arm64 updates for 5.11. The most notable
change is the "PSCI relay" at EL2, which is the first "user visible"
feature required by the Protected KVM effort. The rest is a mixed bag
of architecture compliance (PMU accesses when no PMU is present, cache
hierarchy discovery), cleanups (EL2 vector allocation, AArch32 sysreg
handling), internal rework (exception injection, EL2 function
pointers), and general improvements (advertising CSV3, reduced GICv4
entry latency).

Note that this pull request comes with some additional bonuses in the
shape of a shared branch with the arm64 tree (arm64/for-next/uaccess),
as it was conflicting *very* badly with the new PSCI relay code.

I already have a bunch of fixes earmarked for after the merge window,
but that is probably something for another year!

Happy Christmas (and please pull)!

	M.

The following changes since commit 09162bc32c880a791c6c0668ce0745cf7958f576:

  Linux 5.10-rc4 (2020-11-15 16:44:31 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.11

for you to fetch changes up to 3a514592b698588326924625b6948a10c35fadd5:

  Merge remote-tracking branch 'origin/kvm-arm64/psci-relay' into kvmarm-master/next (2020-12-09 10:00:24 +0000)

----------------------------------------------------------------
KVM/arm64 updates for Linux 5.11

- PSCI relay at EL2 when "protected KVM" is enabled
- New exception injection code
- Simplification of AArch32 system register handling
- Fix PMU accesses when no PMU is enabled
- Expose CSV3 on non-Meltdown hosts
- Cache hierarchy discovery fixes
- PV steal-time cleanups
- Allow function pointers at EL2
- Various host EL2 entry cleanups
- Simplification of the EL2 vector allocation

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm64: Refuse to run VCPU if PMU is not initialized

Andrew Jones (2):
      KVM: arm64: CSSELR_EL1 max is 13
      KVM: arm64: selftests: Filter out DEMUX registers

David Brazdil (26):
      KVM: arm64: Add kvm-arm.mode early kernel parameter
      KVM: arm64: Add ARM64_KVM_PROTECTED_MODE CPU capability
      psci: Support psci_ops.get_version for v0.1
      psci: Split functions to v0.1 and v0.2+ variants
      psci: Replace psci_function_id array with a struct
      psci: Add accessor for psci_0_1_function_ids
      arm64: Make cpu_logical_map() take unsigned int
      arm64: Extract parts of el2_setup into a macro
      KVM: arm64: Remove vector_ptr param of hyp-init
      KVM: arm64: Move hyp-init params to a per-CPU struct
      KVM: arm64: Init MAIR/TCR_EL2 from params struct
      KVM: arm64: Add .hyp.data..ro_after_init ELF section
      KVM: arm64: Support per_cpu_ptr in nVHE hyp code
      KVM: arm64: Create nVHE copy of cpu_logical_map
      KVM: arm64: Add SMC handler in nVHE EL2
      KVM: arm64: Bootstrap PSCI SMC handler in nVHE EL2
      KVM: arm64: Add offset for hyp VA <-> PA conversion
      KVM: arm64: Forward safe PSCI SMCs coming from host
      KVM: arm64: Extract __do_hyp_init into a helper function
      KVM: arm64: Add function to enter host from KVM nVHE hyp code
      KVM: arm64: Intercept host's CPU_ON SMCs
      KVM: arm64: Intercept host's CPU_SUSPEND PSCI SMCs
      KVM: arm64: Intercept host's SYSTEM_SUSPEND PSCI SMCs
      KVM: arm64: Keep nVHE EL2 vector installed
      KVM: arm64: Trap host SMCs in protected mode
      KVM: arm64: Fix EL2 mode availability checks

Keqian Zhu (2):
      KVM: arm64: Some fixes of PV-time interface document
      KVM: arm64: Use kvm_write_guest_lock when init stolen time

Marc Zyngier (47):
      KVM: arm64: Add kimg_hyp_va() helper
      KVM: arm64: Turn host HVC handling into a dispatch table
      KVM: arm64: Don't adjust PC on SError during SMC trap
      KVM: arm64: Move kvm_vcpu_trap_il_is32bit into kvm_skip_instr32()
      KVM: arm64: Make kvm_skip_instr() and co private to HYP
      KVM: arm64: Move PC rollback on SError to HYP
      KVM: arm64: Move VHE direct sysreg accessors into kvm_host.h
      KVM: arm64: Add basic hooks for injecting exceptions from EL2
      KVM: arm64: Inject AArch64 exceptions from HYP
      KVM: arm64: Inject AArch32 exceptions from HYP
      KVM: arm64: Remove SPSR manipulation primitives
      KVM: arm64: Consolidate exception injection
      KVM: arm64: Get rid of the AArch32 register mapping code
      KVM: arm64: Introduce handling of AArch32 TTBCR2 traps
      KVM: arm64: Move AArch32 exceptions over to AArch64 sysregs
      KVM: arm64: Add AArch32 mapping annotation
      KVM: arm64: Map AArch32 cp15 register to AArch64 sysregs
      KVM: arm64: Map AArch32 cp14 register to AArch64 sysregs
      KVM: arm64: Drop is_32bit trap attribute
      KVM: arm64: Drop is_aarch32 trap attribute
      KVM: arm64: Drop legacy copro shadow register
      KVM: arm64: Drop kvm_coproc.h
      KVM: arm64: Patch kimage_voffset instead of loading the EL1 value
      KVM: arm64: Simplify __kvm_enable_ssbs()
      KVM: arm64: Avoid repetitive stack access on host EL1 to EL2 exception
      Merge branch 'kvm-arm64/el2-pc' into kvmarm-master/next
      Merge branch 'kvm-arm64/copro-no-more' into kvmarm-master/next
      Merge branch 'kvm-arm64/host-hvc-table' into kvmarm-master/next
      KVM: arm64: Add kvm_vcpu_has_pmu() helper
      KVM: arm64: Set ID_AA64DFR0_EL1.PMUVer to 0 when no PMU support
      KVM: arm64: Refuse illegal KVM_ARM_VCPU_PMU_V3 at reset time
      KVM: arm64: Inject UNDEF on PMU access when no PMU configured
      KVM: arm64: Remove PMU RAZ/WI handling
      KVM: arm64: Remove dead PMU sysreg decoding code
      KVM: arm64: Gate kvm_pmu_update_state() on the PMU feature
      KVM: arm64: Get rid of the PMU ready state
      Merge branch 'kvm-arm64/pmu-undef' into kvmarm-master/next
      Merge branch 'kvm-arm64/vector-rework' into kvmarm-master/next
      Merge branch 'kvm-arm64/cache-demux' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.11' into kvmarm-master/next
      arm64: Make the Meltdown mitigation state available
      KVM: arm64: Advertise ID_AA64PFR0_EL1.CSV3=1 if the CPUs are Meltdown-safe
      Merge remote-tracking branch 'origin/kvm-arm64/csv3' into kvmarm-master/queue
      Merge remote-tracking branch 'arm64/for-next/uaccess' into HEAD
      Merge remote-tracking branch 'origin/kvm-arm64/misc-5.11' into kvmarm-master/queue
      KVM: arm64: Fix nVHE boot on VHE systems
      Merge remote-tracking branch 'origin/kvm-arm64/psci-relay' into kvmarm-master/next

Mark Rutland (18):
      arm64: uaccess: move uao_* alternatives to asm-uaccess.h
      arm64: ensure ERET from kthread is illegal
      arm64: add C wrappers for SET_PSTATE_*()
      arm64: head.S: rename el2_setup -> init_kernel_el
      arm64: head.S: cleanup SCTLR_ELx initialization
      arm64: head.S: always initialize PSTATE
      arm64: sdei: move uaccess logic to arch/arm64/
      arm64: sdei: explicitly simulate PAN/UAO entry
      arm64: uaccess: rename privileged uaccess routines
      arm64: uaccess: simplify __copy_user_flushcache()
      arm64: uaccess: refactor __{get,put}_user
      arm64: uaccess: split user/kernel routines
      arm64: uaccess cleanup macro naming
      arm64: uaccess: remove set_fs()
      arm64: uaccess: remove addr_limit_user_check()
      arm64: uaccess: remove redundant PAN toggling
      arm64: uaccess: remove vestigal UAO support
      arm64: mark __system_matches_cap as __maybe_unused

Shenming Lu (1):
      KVM: arm64: Delay the polling of the GICR_VPENDBASER.Dirty bit

Will Deacon (17):
      arm64: alternatives: Split up alternative.h
      arm64: cpufeatures: Add capability for LDAPR instruction
      arm64: alternatives: Remove READ_ONCE() usage during patch operation
      arm64: lto: Strengthen READ_ONCE() to acquire when CONFIG_LTO=y
      KVM: arm64: Remove redundant Spectre-v2 code from kvm_map_vector()
      KVM: arm64: Tidy up kvm_map_vector()
      KVM: arm64: Move kvm_get_hyp_vector() out of header file
      KVM: arm64: Make BP hardening globals static instead
      KVM: arm64: Move BP hardening helpers into spectre.h
      KVM: arm64: Re-jig logic when patching hardened hyp vectors
      KVM: arm64: Allocate hyp vectors statically
      arm64: spectre: Rename ARM64_HARDEN_EL2_VECTORS to ARM64_SPECTRE_V3A
      arm64: spectre: Consolidate spectre-v3a detection
      KVM: arm64: Remove redundant hyp vectors entry
      KVM: arm64: Move 'struct kvm_arch_memory_slot' out of uapi/
      KVM: arm64: Remove kvm_arch_vm_ioctl_check_extension()
      KVM: arm64: Remove unused __extended_idmap_trampoline() prototype

 Documentation/admin-guide/kernel-parameters.txt    |  10 +
 Documentation/arm64/memory.rst                     |   2 +-
 Documentation/virt/kvm/arm/pvtime.rst              |   4 +-
 arch/arm64/Kconfig                                 |  25 +-
 arch/arm64/include/asm/alternative-macros.h        | 217 ++++++++++++
 arch/arm64/include/asm/alternative.h               | 267 +-------------
 arch/arm64/include/asm/asm-uaccess.h               |  31 +-
 arch/arm64/include/asm/cpucaps.h                   |   8 +-
 arch/arm64/include/asm/cpufeature.h                |  20 +-
 arch/arm64/include/asm/el2_setup.h                 | 181 ++++++++++
 arch/arm64/include/asm/exec.h                      |   1 -
 arch/arm64/include/asm/futex.h                     |   8 +-
 arch/arm64/include/asm/insn.h                      |   3 +-
 arch/arm64/include/asm/kvm_arm.h                   |   1 +
 arch/arm64/include/asm/kvm_asm.h                   |  17 +-
 arch/arm64/include/asm/kvm_coproc.h                |  38 --
 arch/arm64/include/asm/kvm_emulate.h               |  70 +---
 arch/arm64/include/asm/kvm_host.h                  | 206 ++++++++---
 arch/arm64/include/asm/kvm_hyp.h                   |   4 +-
 arch/arm64/include/asm/kvm_mmu.h                   | 110 +++---
 arch/arm64/include/asm/mmu.h                       |  29 --
 arch/arm64/include/asm/percpu.h                    |   6 +
 arch/arm64/include/asm/processor.h                 |   4 +-
 arch/arm64/include/asm/ptrace.h                    |   8 +-
 arch/arm64/include/asm/rwonce.h                    |  73 ++++
 arch/arm64/include/asm/sections.h                  |   1 +
 arch/arm64/include/asm/smp.h                       |   4 +-
 arch/arm64/include/asm/spectre.h                   |  65 ++++
 arch/arm64/include/asm/sysreg.h                    |  23 +-
 arch/arm64/include/asm/thread_info.h               |  10 +-
 arch/arm64/include/asm/uaccess.h                   | 174 ++++-----
 arch/arm64/include/asm/virt.h                      |  26 ++
 arch/arm64/include/uapi/asm/kvm.h                  |   3 -
 arch/arm64/kernel/alternative.c                    |   7 +-
 arch/arm64/kernel/armv8_deprecated.c               |   4 +-
 arch/arm64/kernel/asm-offsets.c                    |   8 +-
 arch/arm64/kernel/cpu_errata.c                     |  19 +-
 arch/arm64/kernel/cpufeature.c                     |  88 +++--
 arch/arm64/kernel/entry.S                          |  19 +-
 arch/arm64/kernel/head.S                           | 180 +++-------
 arch/arm64/kernel/image-vars.h                     |  11 +-
 arch/arm64/kernel/process.c                        |  29 +-
 arch/arm64/kernel/proton-pack.c                    |  89 ++---
 arch/arm64/kernel/sdei.c                           |  33 +-
 arch/arm64/kernel/setup.c                          |   2 +-
 arch/arm64/kernel/signal.c                         |   3 -
 arch/arm64/kernel/sleep.S                          |   2 +-
 arch/arm64/kernel/suspend.c                        |   1 -
 arch/arm64/kernel/vdso/Makefile                    |   2 +-
 arch/arm64/kernel/vdso32/Makefile                  |   2 +-
 arch/arm64/kernel/vmlinux.lds.S                    |  12 +-
 arch/arm64/kvm/Makefile                            |   4 +-
 arch/arm64/kvm/aarch32.c                           | 232 ------------
 arch/arm64/kvm/arm.c                               | 281 ++++++++++++---
 arch/arm64/kvm/guest.c                             |  29 +-
 arch/arm64/kvm/handle_exit.c                       |  24 +-
 arch/arm64/kvm/hyp/Makefile                        |   2 +-
 arch/arm64/kvm/hyp/aarch32.c                       |   4 +-
 arch/arm64/kvm/hyp/exception.c                     | 331 +++++++++++++++++
 arch/arm64/kvm/hyp/hyp-entry.S                     |  71 ++--
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h         |  62 ++++
 arch/arm64/kvm/hyp/include/hyp/switch.h            |  17 +
 arch/arm64/kvm/hyp/include/nvhe/trap_handler.h     |  18 +
 arch/arm64/kvm/hyp/nvhe/Makefile                   |   5 +-
 arch/arm64/kvm/hyp/nvhe/host.S                     |  58 ++-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S                 | 152 +++++---
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 | 243 ++++++++-----
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |  40 +++
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S                  |   1 +
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               | 324 +++++++++++++++++
 arch/arm64/kvm/hyp/nvhe/switch.c                   |   8 +-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c                |  11 -
 arch/arm64/kvm/hyp/smccc_wa.S                      |  32 --
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   2 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c                    |   2 +
 arch/arm64/kvm/hyp/vhe/Makefile                    |   2 +-
 arch/arm64/kvm/hyp/vhe/switch.c                    |   3 +
 arch/arm64/kvm/inject_fault.c                      | 167 +++------
 arch/arm64/kvm/mmio.c                              |   2 +-
 arch/arm64/kvm/mmu.c                               |   2 +-
 arch/arm64/kvm/pmu-emul.c                          |  19 +-
 arch/arm64/kvm/pvtime.c                            |   6 +-
 arch/arm64/kvm/regmap.c                            | 224 ------------
 arch/arm64/kvm/reset.c                             |  57 +--
 arch/arm64/kvm/sys_regs.c                          | 390 ++++++++-------------
 arch/arm64/kvm/sys_regs.h                          |   9 +-
 arch/arm64/kvm/va_layout.c                         | 104 +++++-
 arch/arm64/kvm/vgic-sys-reg-v3.c                   |   4 -
 arch/arm64/kvm/vgic/vgic-v4.c                      |  12 +
 arch/arm64/kvm/vgic/vgic.c                         |   3 +
 arch/arm64/lib/clear_user.S                        |   8 +-
 arch/arm64/lib/copy_from_user.S                    |   8 +-
 arch/arm64/lib/copy_in_user.S                      |  16 +-
 arch/arm64/lib/copy_to_user.S                      |   8 +-
 arch/arm64/lib/mte.S                               |   6 +-
 arch/arm64/lib/uaccess_flushcache.c                |   4 +-
 arch/arm64/mm/fault.c                              |   5 -
 arch/arm64/mm/proc.S                               |   2 +-
 drivers/firmware/arm_sdei.c                        |  14 -
 drivers/firmware/psci/psci.c                       | 126 ++++---
 drivers/irqchip/irq-gic-v3-its.c                   |  12 +-
 drivers/irqchip/irq-gic-v4.c                       |  19 +
 include/kvm/arm_pmu.h                              |   3 -
 include/kvm/arm_vgic.h                             |   1 +
 include/linux/irqchip/arm-gic-v4.h                 |   4 +
 include/linux/psci.h                               |   9 +
 tools/testing/selftests/kvm/aarch64/get-reg-list.c |  39 ++-
 107 files changed, 3110 insertions(+), 2291 deletions(-)
 create mode 100644 arch/arm64/include/asm/alternative-macros.h
 create mode 100644 arch/arm64/include/asm/el2_setup.h
 delete mode 100644 arch/arm64/include/asm/kvm_coproc.h
 create mode 100644 arch/arm64/include/asm/rwonce.h
 delete mode 100644 arch/arm64/kvm/aarch32.c
 create mode 100644 arch/arm64/kvm/hyp/exception.c
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h
 create mode 100644 arch/arm64/kvm/hyp/include/nvhe/trap_handler.h
 create mode 100644 arch/arm64/kvm/hyp/nvhe/hyp-smp.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/psci-relay.c
 delete mode 100644 arch/arm64/kvm/hyp/smccc_wa.S
 delete mode 100644 arch/arm64/kvm/regmap.c
```
#### [PATCH v3 01/17] KVM: Fix arguments to kvm_{un,}map_gfn()
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11971553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EC270C2BB40
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 08:40:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A6750206C1
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 08:40:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2439438AbgLNIky (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 03:40:54 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47570 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2439410AbgLNIkx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 03:40:53 -0500
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 5A1D8C061257
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 00:39:12 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=nlfk7fo9/eeQqoeGTfsdj4FxMlsVP85cXV+6FJSJYMM=;
 b=JgFdAIQrimZBWMpqFIlNVa7Zz7
        KKKpnpxMJ0dYDJlQ1+MpRiSigCbOOzbgL4Vv5gmUcLA8UgfJFx2kwO+QHr1ftPzc+sRvy+7wdDmAz
        INJICs1a27fitqqKEApeWB4Wtb+WTpOGedvWszP5G5vpUPGmuNNwB84bsHn0Xvr7FI1XtpCVg8rnY
        CLCtojYtcoeKB2+1IWNg5+CtLksh/n5BQKahcXmeQAXiKuA2M/A3poxHDm8LaL9KbFL92437WUnU6
        hC2vkMFt4fb+0BiOXaSrZtR3bBGeP/1nG4KimkfgeFkDJjiOOxGCC7T84GNeqe11xGYc9qczO+csp
        fZZhuUsg==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kojNs-0006lM-Kq; Mon, 14 Dec 2020 08:39:08 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kojNr-008SxW-J1; Mon, 14 Dec 2020 08:39:07 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com
Subject: [PATCH v3 01/17] KVM: Fix arguments to kvm_{un,}map_gfn()
Date: Mon, 14 Dec 2020 08:38:49 +0000
Message-Id: <20201214083905.2017260-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201214083905.2017260-1-dwmw2@infradead.org>
References: <20201214083905.2017260-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

It shouldn't take a vcpu.

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/kvm/x86.c       | 8 ++++----
 include/linux/kvm_host.h | 4 ++--
 virt/kvm/kvm_main.c      | 8 ++++----
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH 1/3] KVM: x86: remove bogus #GP injection
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11972723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2B61C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:37:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 48A57224D1
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:37:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408872AbgLNShX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 13:37:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38254 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2440904AbgLNSeV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Dec 2020 13:34:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607970775;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+NmuioRXdPzhZhBnp7tfLVLDUjPrKAJC+sD5oIOuUZ8=;
        b=I1qjgVwhUAszkGoXtwgiFs5O9gIM5UTXpSklVmb2z3HQTpCSYH+qttrnJhU9rYY7OfAeuW
        bVKDLBnwPN/aZPoMFrxTPbNJi4RwJ9exI0r1YI4nWdJheQpw+rLoMax5HsY49mtJijTm7J
        M9vm6vL+mbl2LZPs91rOJM3Q7SzQnts=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-210-mS9S5NL_NwCzwSqmJfjVqg-1; Mon, 14 Dec 2020 13:32:53 -0500
X-MC-Unique: mS9S5NL_NwCzwSqmJfjVqg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A7BDA1007315;
        Mon, 14 Dec 2020 18:32:52 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 20C841042A7C;
        Mon, 14 Dec 2020 18:32:52 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Alexander Graf <graf@amazon.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH 1/3] KVM: x86: remove bogus #GP injection
Date: Mon, 14 Dec 2020 13:32:48 -0500
Message-Id: <20201214183250.1034541-2-pbonzini@redhat.com>
In-Reply-To: <20201214183250.1034541-1-pbonzini@redhat.com>
References: <20201214183250.1034541-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no need to inject a #GP from kvm_mtrr_set_msr, kvm_emulate_wrmsr will
handle it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/mtrr.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
#### [RFC v3 1/2] vfio/platform: add support for msi
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11972615
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	UNWANTED_LANGUAGE_BODY,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EAB90C2BB48
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AB6D5221EF
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408820AbgLNRsK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 12:48:10 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47246 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1731282AbgLNRqP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 12:46:15 -0500
Received: from mail-pf1-x435.google.com (mail-pf1-x435.google.com
 [IPv6:2607:f8b0:4864:20::435])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 873E0C061793
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 09:45:34 -0800 (PST)
Received: by mail-pf1-x435.google.com with SMTP id f9so12497765pfc.11
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 09:45:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=mime-version:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=UenM37lmodjiB6QmDFlmWzNtX75/O38PCHVxXC9Tk0A=;
        b=EcAMIBMZUYk8eRj5Smjue1JFqe7ourqOPjmI/UlMxT7sA4/9YRwCK6Wdw+1T9qqZAl
         igo6SSIeDHitdmLrHXYaJy/dFovuvBho9HM/uuG86R7tjmHrJaVDdYlXp9gffpNQrXcX
         4sfrSLcltinUY/DhgbCu6Jj0ipwcPbAeyfIro=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=mime-version:x-gm-message-state:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=UenM37lmodjiB6QmDFlmWzNtX75/O38PCHVxXC9Tk0A=;
        b=BcLVZFwInMBnya5lKIURh+47ENQE40EfRRHsmdBOuG7kDChafHazoKNWQzLAGxyfor
         3PzqS/4g+E6ZfrZj0PF+EV5l19189ow9b6pUbJKb9GtydwE75vrn4HlS0FJkJmyLl7LS
         z4QI4zNI90TcV8swg03bxGGbfPyqBr71HwDa0bjC8EyR3nyNb3U5/5wHNhCxDoQWyqeh
         3RpHCO+vta4GvwBruax10sYR2xn4m1nMfMENBV962w+XPUennythgNef6j32vlL2RiWE
         +rqXpQn02SmVju7kbjQUAocQCVSLyB6ZyN/bDUbVqA2UyroFS0EKstxZsUrUY6vJl4sU
         SHUw==
MIME-Version: 1.0
X-Gm-Message-State: AOAM532cvvzRpPv3mCNI0/n1JRblaMTfaF7jRpBNYvcvmB7TWcRmA60m
        Xz5/CCGQNXAmUueSWHVp3zQ/9c3MrdGEMJVB1mytIkVWQ5oN6QYd8AV095RVgzGcpKWxYMJqpCv
        TUn4=
X-Google-Smtp-Source: 
 ABdhPJxf958fcFXu5aP/lMOjPztpGBYMLRiNAQGjmruLXEx2L9f5hqeNlD6g/zhKtr/nAfFzK4pdqA==
X-Received: by 2002:a62:8683:0:b029:1a3:9879:c326 with SMTP id
 x125-20020a6286830000b02901a39879c326mr10890941pfd.72.1607967933743;
        Mon, 14 Dec 2020 09:45:33 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 m8sm6658131pgg.78.2020.12.14.09.45.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 14 Dec 2020 09:45:32 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC v3 1/2] vfio/platform: add support for msi
Date: Mon, 14 Dec 2020 23:15:13 +0530
Message-Id: <20201214174514.22006-2-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201214174514.22006-1-vikas.gupta@broadcom.com>
References: <20201124161646.41191-1-vikas.gupta@broadcom.com>
 <20201214174514.22006-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSI support for platform devices.The MSI block
is added as an extended IRQ which exports caps
VFIO_IRQ_INFO_CAP_TYPE and VFIO_IRQ_INFO_CAP_MSI_DESCS.

Signed-off-by: Vikas Gupta <vikas.gupta@broadcom.com>
---
 drivers/vfio/platform/vfio_platform_common.c  | 179 +++++++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 260 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  32 +++
 include/uapi/linux/vfio.h                     |  44 +++
 4 files changed, 496 insertions(+), 19 deletions(-)

```
#### [PATCH v2 01/16] target/mips: Inline cpu_state_reset() in mips_cpu_reset()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11972725
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1741C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:38:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A660722525
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 18:38:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408894AbgLNSil (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 13:38:41 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55378 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2408883AbgLNSi2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 13:38:28 -0500
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 30D1CC061793
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 10:37:48 -0800 (PST)
Received: by mail-wm1-x341.google.com with SMTP id 3so16186139wmg.4
        for <kvm@vger.kernel.org>; Mon, 14 Dec 2020 10:37:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=PkbswluQKWjRx3dBtHaGXoEp5nk30ZYfIfOdkw/Z4mE=;
        b=so87HLcUDeHLMSRrrBIoaQWUwBf8G3+RiGUHx0pXI0M8i8oVclm5u38oWxGVU+nRE9
         H1/I+bkvfeohZvPRDLGNrptdMb+bS/XgK3I3hemaCE4VuYbp+oP8+OEm6BaxdYpVWC5q
         7kdq8C+VkX1BkPWurVnCHTbxnFpB1RkgtRNapuqHjZDaFp5gokompzmmnRBHp7irMovG
         HplSBu+h5qd5YPQpXjbyjrz2Qx+8dbFmeEToshnQT5AEFmjWT8/8pf5RXYihAN8NPqqV
         XW+aOXYWZUP/uJ/OYB3uskd5w4ddXWksjA52rV84hF4Rzc6VUX3VxpFwzSY8JvoiQx3F
         TryQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references:mime-version:content-transfer-encoding;
        bh=PkbswluQKWjRx3dBtHaGXoEp5nk30ZYfIfOdkw/Z4mE=;
        b=UI89hgdL5ad2wwoZyquraF7rzcMQH0rqtMizGceRnufjEEN92OAVdJYsXS2NILSajH
         SOfAcjLHrxsNHpEsS0vRJn4cbE0dMolpxMbc8JeRtPiDUykX0ximEuZwR8u2pRRyB+ln
         X+xmVpyVQhiY2754fxruyCSLdCu4Z7A+3eh6OAcrXkA/4kKLNXsXkquGfIZCkPCVd5bc
         i7eo8/fTIyiRtbUtQnJXUxkwai+UtSCWfnuqXxNoTKIfYnuT1z5wEN+CZzpv4PobTCuQ
         7JKSKmv5IlKSlsBjSi15Q0SGHcEWCAjtrq/hT2vP+FZeBuavNeAGQDuy3QCmRUYwW7al
         MLOA==
X-Gm-Message-State: AOAM530R8i2JuEUxycXQdq9heHRhR0w6PJrBqRfyx97xNQEOBvNmGHdt
        J5p7pkirnIhtzquTVmJhdKo=
X-Google-Smtp-Source: 
 ABdhPJwGXLAxo6yN+sLIdbUznMxVePFYOVX87wckAVWiT7wsnNmHFrE3HhgsbKkK5tMFh6Kt4WouSg==
X-Received: by 2002:a1c:2c83:: with SMTP id
 s125mr29306057wms.161.1607971067021;
        Mon, 14 Dec 2020 10:37:47 -0800 (PST)
Received: from localhost.localdomain (101.red-88-21-206.staticip.rima-tde.net.
 [88.21.206.101])
        by smtp.gmail.com with ESMTPSA id
 y7sm33139083wmb.37.2020.12.14.10.37.45
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 14 Dec 2020 10:37:46 -0800 (PST)
Sender: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
  <philippe.mathieu.daude@gmail.com>
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, Aurelien Jarno <aurelien@aurel32.net>,
 Huacai Chen <chenhuacai@kernel.org>,
 Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
 Jiaxun Yang <jiaxun.yang@flygoat.com>, Laurent Vivier <laurent@vivier.eu>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v2 01/16] target/mips: Inline cpu_state_reset() in
 mips_cpu_reset()
Date: Mon, 14 Dec 2020 19:37:24 +0100
Message-Id: <20201214183739.500368-2-f4bug@amsat.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201214183739.500368-1-f4bug@amsat.org>
References: <20201214183739.500368-1-f4bug@amsat.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 target/mips/cpu.c | 26 +++++++++-----------------
 1 file changed, 9 insertions(+), 17 deletions(-)

```
#### [PATCH v2] KVM: SVM: use vmsave/vmload for saving/restoring additional host state
##### From: Michael Roth <michael.roth@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 11972613
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C04D4C4361B
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 742F321D7F
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 17:48:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408649AbgLNRnD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 12:43:03 -0500
Received: from mail-mw2nam12hn2204.outbound.protection.outlook.com
 ([52.100.167.204]:16033
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2502546AbgLNRmk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 12:42:40 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=FTHz+sEONGQmVIXnhTEg6Zz296K2DVorrJrKV+D7Gg1atqoAoOm1EGgOqaOUzkgVssXFE5135B2SPl5B528MqXDAfFou4FlzUSwwabF81AG7dzEVoSU8wDv+PPm5NG0VPNKWIGfqcbVGoKY4YeXaNZJVSgJaeiUVvv6gdqRL5ec7P7zhVNukyrw+SC2/DAuyD76b/wRMWi3PooDAuBA/MB50KDXCnGyWptC+TyP/hTM2duSBpXYrId2gjZA2TCFqVxwa5Fw4twHKN4hgx/Y/DyTA2nlyRgHw+W+8AesGlbYhR8km1LUtu6GTkfwhOxOWBWzGDP8zz0fkUbI3MBCV2Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yrbeWcVtwTsAGiLUmOQuK3TdmVGLrbLQkgfpcjG4iNc=;
 b=dN8AmXb3Ccp4T0xk3HHn9x2QjXn+8YzGy4TZCnGWBR9eMKomia65UbBq3Y+/PzPmpwjGWzL/qnoG+GFlrxvPafixPpbLpfeWBySeEoocajS4XWpn/rGOemC02axuLjjrWNf1VQHvcuixgNBdDdR1dzticDRQKLUv4/OQgw6y2JKnN6HXgHuEC2RU81zToUCMOPjDoAIhBvCMCH2zUxeSZNF6kEE2s+r3Wg4U3Q4xEAkQRxCTYTAJv3Zl45h2fgRx1odjEcC/t/SdyRdmqPnd0QL8SkAnZhRwkggAFsdPS64R4xWNallAvKMvECUM4kss6rmu34J8WvP1XMH97Q3NuQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=yrbeWcVtwTsAGiLUmOQuK3TdmVGLrbLQkgfpcjG4iNc=;
 b=keVGLXoioU0kQH9sBOm02ioD4eNWfDk/14u970ohVwaBFD3CCk4xoKfQasRnuSBnAlF7A2XbZSx2L0qUDEw1oxdv7m+Yt5WnfSUzcQwvyNLPmY1IvJ+vaaxAXCQDOap49pMlnm7jAeT1i/PvlKPzB2rw4L71w138j23tFAs/Moc=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from BY5PR12MB4131.namprd12.prod.outlook.com (2603:10b6:a03:212::13)
 by BY5PR12MB4275.namprd12.prod.outlook.com (2603:10b6:a03:20a::18) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.13; Mon, 14 Dec
 2020 17:41:50 +0000
Received: from BY5PR12MB4131.namprd12.prod.outlook.com
 ([fe80::2432:5fa6:a1f:61f0]) by BY5PR12MB4131.namprd12.prod.outlook.com
 ([fe80::2432:5fa6:a1f:61f0%4]) with mapi id 15.20.3654.025; Mon, 14 Dec 2020
 17:41:50 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v2] KVM: SVM: use vmsave/vmload for saving/restoring
 additional host state
Date: Mon, 14 Dec 2020 11:41:27 -0600
Message-Id: <20201214174127.1398114-1-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [165.204.54.211]
X-ClientProxiedBy: YT1PR01CA0006.CANPRD01.PROD.OUTLOOK.COM (2603:10b6:b01::19)
 To BY5PR12MB4131.namprd12.prod.outlook.com (2603:10b6:a03:212::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.54.211) by
 YT1PR01CA0006.CANPRD01.PROD.OUTLOOK.COM (2603:10b6:b01::19) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3654.12 via Frontend
 Transport; Mon, 14 Dec 2020 17:41:49 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 6627b056-216b-4f9a-0f43-08d8a05789b1
X-MS-TrafficTypeDiagnostic: BY5PR12MB4275:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <BY5PR12MB42756839A38541C0AA57A83895C70@BY5PR12MB4275.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 KgYdG/SxYP4eLVfvHxU1i26fX1jOslmGbK17T8IRW5ivXgX1owMNvvPApbvAY62NWZyfofxqUONpCkX3Dv8YNIoS5HFrTlHLTv7U9RYBi7kiuSlM/PZFAwed8D1eFNMCb8EbsZ4tstVZILfh2sHEM3Vflvfl0+1HojfwiSQ/6/Zz1yatrMt6n+fIyCoGlUQ6m9Kt7rp0L4mtqQkWsQ9HczzHvBD/gncrsbiY45I6SllX44J3TEZQxnp9/ie6acwa3cjSLjMzVcgNNpcg9YznhDdAogIKovjzgBfq0ctJFUCFGqbEwMWETraPZqEXYf3/PPmcsbX3uRFk59lKqguo2B9Jc980qEvou2rFYG+OtZmsI2Pv3YZE0ZvG01xcmya23ej/SBCAC3swkyVG7JG0KFuwHmq352NgReWAEOnKkqHJh9DFtTuYdgMd1c9GwM5esAtvSm2lxWWVbIjHmuG8o5ctxpX3bZc5LQndNkEE1f2NCcRLXNsnfMOMqa6WL20MyUnwaln9mm7MAajDs7fTLcJV36jVqovlJO9fNVgAogN8vPCgQWnkj7o3ueGDfmctHuZWIa6OicKf/nSGTsm9bhz7Sr1+v2n9gGMPN03n8VGalULU2UEjeFmyS7jJKupvDmHpgrDo02hO6fV0O+jT6VedNOq4dHhJTQ77rLXojt94NmOyhxufPW6e2DUqAXM71WkCCIT6sNfMANVPeN/3mQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:BY5PR12MB4131.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(136003)(346002)(376002)(366004)(54906003)(6916009)(36756003)(26005)(44832011)(1076003)(7416002)(4326008)(52116002)(66476007)(6486002)(186003)(5660300002)(34490700003)(83380400001)(6496006)(86362001)(16526019)(8676002)(66946007)(66556008)(508600001)(2906002)(956004)(6666004)(2616005)(8936002)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 RXoMBHxnD9y+2SA+grjH5LVUjXKUFOkWAC8NuzYNMfBYurcWyJeuMEaHsqz3JcFVvc5GzU9TbnDtkIYpN5ahs3ZX54Igju8ZH4MuFhr/02oC17ZcYtdP412jUT9bhCMVlV5NIsIkbbO4bvHQfAkVx0X388yLqYLiMrh48wH8gH82yT4msfyLVA8Bslyvlqve0cWyRfohWOnxhlsg266IeHOehCeqLWR+Ga+6n8XP7b1+OXc5YXdhzPQycQ4DSG+jZSaPLOFVbQRgaa0rWVeUrguJzm8yBxsHw2+n3w0BYbbA7G1gCCxJY5ECJ94E7Ik70cjy3p4Lmu2kw+czNuy67a3qlPXljja/wLjVgS745fG0fTSk5y6atsvNLXwLwIEzbHn8LYhF6qu74vbkhP6h2na12SKNEdmVnNnLYkIUWi2M6g+l2rPScSU9JLImRZlcGi7ryDgLALnk+XQ33JxpBe/kc6TnXS0dj3lCrfFCD6OeL/ONwxDjIB/cSvlHZX1SQFiqPUYFJsvR5m8TMSwL++qAKFxqYybT6j2lk70U+hXByXOSE/hY6ORSUwRTQMO9FT3sRZNFDcescnQBpfClH0JyhWpVlOWKFvoOIEqTtMiwbSHqdS5qbavm/ndA5s4I24K5ygHjUV4dhsN9nUXLhgvzSsl/0dNSb+VaLVGwTAnS4wTVUTdDZXjessCrXMyWPLz8q2QQxQ1IFKl2GYSscLZew0e4ICFxYQkIyvfQEdoO+33P5hVH+fh9FVCeOGMhOuQmgu/m2hGFM9KF7FdzXF0dXMoA9N/C9BuIDA/ayo0FM7iCzNciT59ZFf5ybIIuaq/PK3KoN3xD0IuzzZLCHgR56eOAck1zuMXdjrjJl/4NTdmrmJMc78w+qkiySFumtFh7wan1nB+lUEE21IcdUyOlK6yg/rxCc7bUbD1vcnzfqc6bnZ7jiI7n0EouO+8Et0LBJSMvpsdejITz57f7ITKJO7KOD5/vKr9e+zQaDtfS/n9DJq1QwWYd6hvv4a4O
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-AuthSource: BY5PR12MB4131.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 14 Dec 2020 17:41:50.4501
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6627b056-216b-4f9a-0f43-08d8a05789b1
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 cgeusDRQxdjjVEzyzLiL9Qgh/o3JrdvtEV1Q28jDq1AkEI8XB6T9t2CuxNUtP3+KBR+FnosycFFDuCZMVmE81g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BY5PR12MB4275
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Using a guest workload which simply issues 'hlt' in a tight loop to
generate VMEXITs, it was observed (on a recent EPYC processor) that a
significant amount of the VMEXIT overhead measured on the host was the
result of MSR reads/writes in svm_vcpu_load/svm_vcpu_put according to
perf:

  67.49%--kvm_arch_vcpu_ioctl_run
          |
          |--23.13%--vcpu_put
          |          kvm_arch_vcpu_put
          |          |
          |          |--21.31%--native_write_msr
          |          |
          |           --1.27%--svm_set_cr4
          |
          |--16.11%--vcpu_load
          |          |
          |           --15.58%--kvm_arch_vcpu_load
          |                     |
          |                     |--13.97%--svm_set_cr4
          |                     |          |
          |                     |          |--12.64%--native_read_msr

Most of these MSRs relate to 'syscall'/'sysenter' and segment bases, and
can be saved/restored using 'vmsave'/'vmload' instructions rather than
explicit MSR reads/writes. In doing so there is a significant reduction
in the svm_vcpu_load/svm_vcpu_put overhead measured for the above
workload:

  50.92%--kvm_arch_vcpu_ioctl_run
          |
          |--19.28%--disable_nmi_singlestep
          |
          |--13.68%--vcpu_load
          |          kvm_arch_vcpu_load
          |          |
          |          |--9.19%--svm_set_cr4
          |          |          |
          |          |           --6.44%--native_read_msr
          |          |
          |           --3.55%--native_write_msr
          |
          |--6.05%--kvm_inject_nmi
          |--2.80%--kvm_sev_es_mmio_read
          |--2.19%--vcpu_put
          |          |
          |           --1.25%--kvm_arch_vcpu_put
          |                     native_write_msr

Quantifying this further, if we look at the raw cycle counts for a
normal iteration of the above workload (according to 'rdtscp'),
kvm_arch_vcpu_ioctl_run() takes ~4600 cycles from start to finish with
the current behavior. Using 'vmsave'/'vmload', this is reduced to
~2800 cycles, a savings of 39%.

While this approach doesn't seem to manifest in any noticeable
improvement for more realistic workloads like UnixBench, netperf, and
kernel builds, likely due to their exit paths generally involving IO
with comparatively high latencies, it does improve overall overhead
of KVM_RUN significantly, which may still be noticeable for certain
situations. It also simplifies some aspects of the code.

With this change, explicit save/restore is no longer needed for the
following host MSRs, since they are documented[1] as being part of the
VMCB State Save Area:

  MSR_STAR, MSR_LSTAR, MSR_CSTAR,
  MSR_SYSCALL_MASK, MSR_KERNEL_GS_BASE,
  MSR_IA32_SYSENTER_CS,
  MSR_IA32_SYSENTER_ESP,
  MSR_IA32_SYSENTER_EIP,
  MSR_FS_BASE, MSR_GS_BASE

and only the following MSR needs individual handling in
svm_vcpu_put/svm_vcpu_load:

  MSR_TSC_AUX

We could drop the host_save_user_msrs array/loop and instead handle
MSR read/write of MSR_TSC_AUX directly, but we leave that for now as
a potential follow-up.

Since 'vmsave'/'vmload' also handles the LDTR and FS/GS segment
registers (and associated hidden state)[2], some of the code
previously used to handle this is no longer needed, so we drop it
as well.

The first public release of the SVM spec[3] also documents the same
handling for the host state in question, so we make these changes
unconditionally.

Also worth noting is that we 'vmsave' to the same page that is
subsequently used by 'vmrun' to record some host additional state. This
is okay, since, in accordance with the spec[2], the additional state
written to the page by 'vmrun' does not overwrite any fields written by
'vmsave'. This has also been confirmed through testing (for the above
CPU, at least).

[1] AMD64 Architecture Programmer's Manual, Rev 3.33, Volume 2, Appendix B, Table B-2
[2] AMD64 Architecture Programmer's Manual, Rev 3.31, Volume 3, Chapter 4, VMSAVE/VMLOAD
[3] Secure Virtual Machine Architecture Reference Manual, Rev 3.01

Suggested-by: Tom Lendacky <thomas.lendacky@amd.com>
Signed-off-by: Michael Roth <michael.roth@amd.com>
---
v2:
* rebase on latest kvm/next
* move VMLOAD to just after vmexit so we can use it to handle all FS/GS
  host state restoration and rather than relying on loadsegment() and
  explicit write to MSR_GS_BASE (Andy)
* drop 'host' field from struct vcpu_svm since it is no longer needed
  for storing FS/GS/LDT state (Andy)
---
 arch/x86/kvm/svm/svm.c | 44 ++++++++++++++++--------------------------
 arch/x86/kvm/svm/svm.h | 14 +++-----------
 2 files changed, 20 insertions(+), 38 deletions(-)

```
#### [PATCH v2] kvm: Take into account the unaligned section size when preparing bitmap
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11972015
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C961CC1B0E3
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 11:39:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 919A922CB9
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 11:39:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405872AbgLNLjb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 06:39:31 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:9876 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2392388AbgLNLja (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Dec 2020 06:39:30 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4CvfXD08TLz7DrK;
        Mon, 14 Dec 2020 19:38:04 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.174.185.179) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Mon, 14 Dec 2020 19:38:31 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <qemu-devel@nongnu.org>, <pbonzini@redhat.com>
CC: <kvm@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>, Peter Xu <peterx@redhat.com>
Subject: [PATCH v2] kvm: Take into account the unaligned section size when
 preparing bitmap
Date: Mon, 14 Dec 2020 19:37:06 +0800
Message-ID: <20201214113706.1553-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.185.179]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The kernel KVM_CLEAR_DIRTY_LOG interface has align requirement on both the
start and the size of the given range of pages. We have been careful to
handle the unaligned cases when performing CLEAR on one slot. But it seems
that we forget to take the unaligned *size* case into account when
preparing bitmap for the interface, and we may end up clearing dirty status
for pages outside of [start, start + size). As an example,

    // psize = qemu_real_host_page_size;
    // slot.start_addr = 0;
    // slot.memory_size = 64 * psize;

    kvm_log_clear_one_slot(slot, as, 0 * psize, 32 * psize);   --> [1]

So the @size is not aligned with 64 pages. With [1], we'll clear dirty
status for all 64 pages within this slot whilst the caller only wants to
clear the former 32 pages.

If the size is unaligned, let's go through the slow path to manipulate a
temp bitmap for the interface so that we won't bother with those unaligned
bits at the end of bitmap.

I don't think this can happen in practice since the upper layer would
provide us with the alignment guarantee. But kvm-all shouldn't rely on it.
Carefully handle it in case someday we'll hit it.

Acked-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
* From v1:
  - Squash the misbehave example into commit message
  - Add Peter's Acked-by

 accel/kvm/kvm-all.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v3] s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11972503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1F005C2BB48
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 16:57:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D850F22510
	for <kvm@archiver.kernel.org>; Mon, 14 Dec 2020 16:57:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2440239AbgLNQ5L (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 14 Dec 2020 11:57:11 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:9052 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2440222AbgLNQ5L (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Dec 2020 11:57:11 -0500
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0BEGWTZ1101299;
        Mon, 14 Dec 2020 11:56:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=3cyEYzE/Ow9jjL5B0Midoc9R0devhKEwKmZgd6sWhps=;
 b=eiQl7vhk9jFLkLddfp8cXLY/6HuGWJXBbyL5UVOys5M1ZApqLhS5ik4BZRmfTY/L3Kca
 KHSGSYCq8WGlO71YM+i20lktVaQ9Y90qaTc4Akg8Tn5VgtaprAXAhcDTj24tT/CY/S/2
 VMzRMTnomrE/bbCacbkjm5IhYtz8vwB7SGZPeRC+dCNxJVYOo/DiOP+mxTGcetb3Uo0X
 9Wyprm3tY4qdS9WMf1FGjRFDMLYY+igsd/cqd2+5cO4UtV3tPj9xq/2P9u5Eqf9eOFaI
 Sgrspr0yGMXkY4oDb2KrP1nD+CBzzDJehUuz/GX2uL1WnTegJ1/PmITIneSCTyw/RM+b 1w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35ebcg19hy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Dec 2020 11:56:26 -0500
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0BEGXNbQ106437;
        Mon, 14 Dec 2020 11:56:26 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35ebcg19hm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Dec 2020 11:56:26 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0BEGc13f018796;
        Mon, 14 Dec 2020 16:56:25 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma04wdc.us.ibm.com with ESMTP id 35cng8s9rm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 14 Dec 2020 16:56:25 +0000
Received: from b01ledav002.gho.pok.ibm.com (b01ledav002.gho.pok.ibm.com
 [9.57.199.107])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0BEGuPFn28180968
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 14 Dec 2020 16:56:25 GMT
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E8DE5124053;
        Mon, 14 Dec 2020 16:56:24 +0000 (GMT)
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 414E3124052;
        Mon, 14 Dec 2020 16:56:24 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.193.150])
        by b01ledav002.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 14 Dec 2020 16:56:24 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, gregkh@linuxfoundation.org,
        sashal@kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v3] s390/vfio-ap: clean up vfio_ap resources when KVM pointer
 invalidated
Date: Mon, 14 Dec 2020 11:56:17 -0500
Message-Id: <20201214165617.28685-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2020-12-14_06:2020-12-11,2020-12-14 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 lowpriorityscore=0
 spamscore=0 mlxlogscore=999 suspectscore=0 clxscore=1015 bulkscore=0
 phishscore=0 priorityscore=1501 impostorscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012140111
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vfio_ap device driver registers a group notifier with VFIO when the
file descriptor for a VFIO mediated device for a KVM guest is opened to
receive notification that the KVM pointer is set (VFIO_GROUP_NOTIFY_SET_KVM
event). When the KVM pointer is set, the vfio_ap driver takes the
following actions:
1. Stashes the KVM pointer in the vfio_ap_mdev struct that holds the state
   of the mediated device.
2. Calls the kvm_get_kvm() function to increment its reference counter.
3. Sets the function pointer to the function that handles interception of
   the instruction that enables/disables interrupt processing.
4. Sets the masks in the KVM guest's CRYCB to pass AP resources through to
   the guest.

In order to avoid memory leaks, when the notifier is called to receive
notification that the KVM pointer has been set to NULL, the vfio_ap device
driver should reverse the actions taken when the KVM pointer was set.

Fixes: 258287c994de ("s390: vfio-ap: implement mediated device open callback")
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 29 ++++++++++++++++++++---------
 1 file changed, 20 insertions(+), 9 deletions(-)

```
