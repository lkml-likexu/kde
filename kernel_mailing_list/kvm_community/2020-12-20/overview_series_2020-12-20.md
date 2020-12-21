#### [GIT PULL] KVM changes for Linux 5.11
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11983845
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DDACC3526C
	for <kvm@archiver.kernel.org>; Sun, 20 Dec 2020 09:13:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CC9F230FE
	for <kvm@archiver.kernel.org>; Sun, 20 Dec 2020 09:13:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727043AbgLTJMq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 20 Dec 2020 04:12:46 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:58016 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726676AbgLTJMo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 20 Dec 2020 04:12:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1608455476;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=MNQXELdsMaG63QFCvKDDRIS959XgfvAVArESZ9XQlYs=;
        b=Tu1e0EwthAxAXbKFTuL8W9Pu7137A0pgBUM0ZzD5kO+bSVCXooGTIhvtCFpt0whPjZxGqj
        DDD7DIZWTLsj+pZ5X4KlEf1ftHDlUDvBDaRoLR5Rbl3WkecgBvi/MwftsBNMyViLTy+Jl2
        LW3ath02W91K1Z3QXWfL8RKpX9LAX1M=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-153-msdAnrb3PMqpN7ZfQcVciA-1; Sun, 20 Dec 2020 04:11:13 -0500
X-MC-Unique: msdAnrb3PMqpN7ZfQcVciA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DB5CF107ACE3;
        Sun, 20 Dec 2020 09:11:12 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6F63B5D9DB;
        Sun, 20 Dec 2020 09:11:12 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.11
Date: Sun, 20 Dec 2020 04:11:12 -0500
Message-Id: <20201220091112.1772425-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 701f49065e68741a26752e6ae235c02bcafa2424:

  arm64: mark __system_matches_cap as __maybe_unused (2020-12-03 16:54:57 +0000)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to d45f89f7437d0f2c8275b4434096164db106384d:

  KVM: SVM: fix 32-bit compilation (2020-12-16 13:08:21 -0500)

----------------------------------------------------------------
ARM:
* PSCI relay at EL2 when "protected KVM" is enabled
* New exception injection code
* Simplification of AArch32 system register handling
* Fix PMU accesses when no PMU is enabled
* Expose CSV3 on non-Meltdown hosts
* Cache hierarchy discovery fixes
* PV steal-time cleanups
* Allow function pointers at EL2
* Various host EL2 entry cleanups
* Simplification of the EL2 vector allocation

s390:
* memcg accouting for s390 specific parts of kvm and gmap
* selftest for diag318
* new kvm_stat for when async_pf falls back to sync

x86:
* Tracepoints for the new pagetable code from 5.10
* Catch VFIO and KVM irqfd events before userspace
* Reporting dirty pages to userspace with a ring buffer
* SEV-ES host support
* Nested VMX support for wait-for-SIPI activity state
* New feature flag (AVX512 FP16)
* New system ioctl to report Hyper-V-compatible paravirtualization features

Generic:
* Selftest improvements

----------------------------------------------------------------

Much x86 work was pushed out to 5.12, but ARM more than made up for it.

There is a very minor conflict in arch/x86/kvm/svm/svm.c, plus one in
arch/arm64/include/asm/kvm_asm.h because of a fix that was routed
through the arm64 tree.  The resolutions are at the end of this message.

Paolo


Aaron Lewis (2):
      selftests: kvm: Test MSR exiting to userspace
      selftests: kvm: Merge user_msr_test into userspace_msr_exit_test

Alex Shi (1):
      x86/kvm: remove unused macro HV_CLOCK_SIZE

Alexandru Elisei (1):
      KVM: arm64: Refuse to run VCPU if PMU is not initialized

Andrew Jones (7):
      KVM: selftests: Make vm_create_default common
      KVM: selftests: Introduce vm_create_[default_]_with_vcpus
      KVM: selftests: Also build dirty_log_perf_test on AArch64
      KVM: selftests: Make test skipping consistent
      KVM: selftests: x86: Set supported CPUIDs on default VM
      KVM: arm64: CSSELR_EL1 max is 13
      KVM: arm64: selftests: Filter out DEMUX registers

Ben Gardon (2):
      kvm: x86/mmu: Add existing trace points to TDP MMU
      kvm: x86/mmu: Add TDP MMU SPTE changed trace point

Cathy Avery (1):
      KVM: SVM: Move asid to vcpu_svm

Cathy Zhang (1):
      KVM: x86: Expose AVX512_FP16 for supported CPUID

Christian Borntraeger (3):
      KVM: s390: Add memcg accounting to KVM allocations
      s390/gmap: make gmap memcg aware
      KVM: s390: track synchronous pfault events in kvm_stat

Collin Walling (1):
      KVM: selftests: sync_regs test for diag318

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

David Woodhouse (5):
      sched/wait: Add add_wait_queue_priority()
      kvm/eventfd: Use priority waitqueue to catch events before userspace
      eventfd: Export eventfd_ctx_do_read()
      vfio/virqfd: Drain events from eventfd in virqfd_wakeup()
      kvm/eventfd: Drain events from eventfd in irqfd_wakeup()

Jim Mattson (1):
      kvm: x86: Sink cpuid update into vendor-specific set_cr4 functions

Keqian Zhu (2):
      KVM: arm64: Some fixes of PV-time interface document
      KVM: arm64: Use kvm_write_guest_lock when init stolen time

Kyung Min Park (1):
      x86: Enumerate AVX512 FP16 CPUID feature flag

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

Maxim Levitsky (1):
      KVM: x86: ignore SIPIs that are received while not in wait-for-sipi state

Paolo Bonzini (14):
      KVM: x86: fix apic_accept_events vs check_nested_events
      KVM: remove kvm_clear_guest_page
      selftests: kvm: keep .gitignore add to date
      KVM: selftests: always use manual clear in dirty_log_perf_test
      KVM: SVM: check CR4 changes against vcpu->arch
      KVM: nSVM: set fixed bits by hand
      KVM: x86: adjust SEV for commit 7e8e6eed75e
      KVM: x86: reinstate vendor-agnostic check on SPEC_CTRL cpuid bits
      Merge tag 'kvm-s390-next-5.11-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      KVM: x86: remove bogus #GP injection
      KVM: x86: use kvm_complete_insn_gp in emulating RDMSR/WRMSR
      KVM: x86: introduce complete_emulated_msr callback
      Merge tag 'kvmarm-5.11' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: SVM: fix 32-bit compilation

Peter Xu (9):
      KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
      KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
      KVM: X86: Implement ring-based dirty memory tracking
      KVM: Make dirty ring exclusive to dirty bitmap log
      KVM: Don't allocate dirty bitmap if dirty ring is enabled
      KVM: selftests: Introduce after_vcpu_run hook for dirty log test
      KVM: selftests: Add dirty ring buffer test
      KVM: selftests: Run dirty ring test asynchronously
      KVM: selftests: Add "-c" parameter to dirty log test

Sean Christopherson (6):
      KVM: VMX: Drop guest CPUID check for VMXE in vmx_set_cr4()
      KVM: VMX: Drop explicit 'nested' check from vmx_set_cr4()
      KVM: SVM: Drop VMXE check from svm_set_cr4()
      KVM: x86: Move vendor CR4 validity check to dedicated kvm_x86_ops hook
      KVM: x86: Return bool instead of int for CR4 and SREGS validity checks
      KVM: selftests: Verify supported CR4 bits can be set before KVM_SET_CPUID2

Shenming Lu (1):
      KVM: arm64: Delay the polling of the GICR_VPENDBASER.Dirty bit

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
      KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x002
      KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x004
      KVM: SVM: Add support for SEV-ES GHCB MSR protocol function 0x100
      KVM: SVM: Create trace events for VMGEXIT processing
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
      KVM: SVM: Add NMI support for an SEV-ES guest
      KVM: SVM: Set the encryption mask for the SVM host save area
      KVM: SVM: Update ASID allocation to support SEV-ES guests
      KVM: SVM: Provide support for SEV-ES vCPU creation/loading
      KVM: SVM: Provide support for SEV-ES vCPU loading
      KVM: SVM: Provide an updated VMRUN invocation for SEV-ES guests
      KVM: SVM: Provide support to launch and run an SEV-ES guest
      KVM: SVM: Add AP_JUMP_TABLE support in prep for AP booting

Uros Bizjak (2):
      KVM/VMX: Use TEST %REG,%REG instead of CMP $0,%REG in vmenter.S
      KVM/VMX/SVM: Move kvm_machine_check function to x86.h

Vitaly Kuznetsov (2):
      KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
      KVM: selftests: test KVM_GET_SUPPORTED_HV_CPUID as a system ioctl

Will Deacon (13):
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

Yadong Qi (1):
      KVM: x86: emulate wait-for-SIPI and SIPI-VMExit

 Documentation/admin-guide/kernel-parameters.txt    |  10 +
 Documentation/arm64/memory.rst                     |   2 +-
 Documentation/virt/kvm/api.rst                     | 116 ++-
 Documentation/virt/kvm/arm/pvtime.rst              |   4 +-
 arch/arm64/include/asm/cpucaps.h                   |   5 +-
 arch/arm64/include/asm/cpufeature.h                |   5 +
 arch/arm64/include/asm/el2_setup.h                 | 181 ++++
 arch/arm64/include/asm/kvm_arm.h                   |   1 +
 arch/arm64/include/asm/kvm_asm.h                   |  17 +-
 arch/arm64/include/asm/kvm_coproc.h                |  38 -
 arch/arm64/include/asm/kvm_emulate.h               |  70 +-
 arch/arm64/include/asm/kvm_host.h                  | 206 +++--
 arch/arm64/include/asm/kvm_hyp.h                   |   4 +-
 arch/arm64/include/asm/kvm_mmu.h                   | 110 +--
 arch/arm64/include/asm/mmu.h                       |  29 -
 arch/arm64/include/asm/percpu.h                    |   6 +
 arch/arm64/include/asm/sections.h                  |   1 +
 arch/arm64/include/asm/smp.h                       |   4 +-
 arch/arm64/include/asm/spectre.h                   |  65 ++
 arch/arm64/include/asm/sysreg.h                    |   1 +
 arch/arm64/include/asm/virt.h                      |  26 +
 arch/arm64/include/uapi/asm/kvm.h                  |   3 -
 arch/arm64/kernel/asm-offsets.c                    |   5 +
 arch/arm64/kernel/cpu_errata.c                     |  19 +-
 arch/arm64/kernel/cpufeature.c                     |  42 +-
 arch/arm64/kernel/head.S                           | 135 +--
 arch/arm64/kernel/image-vars.h                     |  11 +-
 arch/arm64/kernel/proton-pack.c                    |  84 +-
 arch/arm64/kernel/setup.c                          |   2 +-
 arch/arm64/kernel/vmlinux.lds.S                    |  10 +
 arch/arm64/kvm/Makefile                            |   4 +-
 arch/arm64/kvm/aarch32.c                           | 232 ------
 arch/arm64/kvm/arm.c                               | 281 +++++--
 arch/arm64/kvm/guest.c                             |  29 +-
 arch/arm64/kvm/handle_exit.c                       |  24 +-
 arch/arm64/kvm/hyp/Makefile                        |   2 +-
 arch/arm64/kvm/hyp/aarch32.c                       |   4 +-
 arch/arm64/kvm/hyp/exception.c                     | 331 ++++++++
 arch/arm64/kvm/hyp/hyp-entry.S                     |  71 +-
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h         |  62 ++
 arch/arm64/kvm/hyp/include/hyp/switch.h            |  17 +
 arch/arm64/kvm/hyp/include/nvhe/trap_handler.h     |  18 +
 arch/arm64/kvm/hyp/nvhe/Makefile                   |   5 +-
 arch/arm64/kvm/hyp/nvhe/host.S                     |  58 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S                 | 152 +++-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 | 243 ++++--
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |  40 +
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S                  |   1 +
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               | 324 ++++++++
 arch/arm64/kvm/hyp/nvhe/switch.c                   |   8 +-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c                |  11 -
 arch/arm64/kvm/hyp/smccc_wa.S                      |  32 -
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   2 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c                    |   2 +
 arch/arm64/kvm/hyp/vhe/Makefile                    |   2 +-
 arch/arm64/kvm/hyp/vhe/switch.c                    |   3 +
 arch/arm64/kvm/inject_fault.c                      | 167 ++--
 arch/arm64/kvm/mmio.c                              |   2 +-
 arch/arm64/kvm/mmu.c                               |   2 +-
 arch/arm64/kvm/pmu-emul.c                          |  19 +-
 arch/arm64/kvm/pvtime.c                            |   6 +-
 arch/arm64/kvm/regmap.c                            | 224 -----
 arch/arm64/kvm/reset.c                             |  57 +-
 arch/arm64/kvm/sys_regs.c                          | 390 +++------
 arch/arm64/kvm/sys_regs.h                          |   9 +-
 arch/arm64/kvm/va_layout.c                         | 104 ++-
 arch/arm64/kvm/vgic-sys-reg-v3.c                   |   4 -
 arch/arm64/kvm/vgic/vgic-v4.c                      |  12 +
 arch/arm64/kvm/vgic/vgic.c                         |   3 +
 arch/s390/include/asm/kvm_host.h                   |   1 +
 arch/s390/kvm/guestdbg.c                           |   8 +-
 arch/s390/kvm/intercept.c                          |   2 +-
 arch/s390/kvm/interrupt.c                          |  10 +-
 arch/s390/kvm/kvm-s390.c                           |  22 +-
 arch/s390/kvm/priv.c                               |   4 +-
 arch/s390/kvm/pv.c                                 |   6 +-
 arch/s390/kvm/vsie.c                               |   4 +-
 arch/s390/mm/gmap.c                                |  30 +-
 arch/x86/include/asm/cpufeatures.h                 |   2 +
 arch/x86/include/asm/kvm_host.h                    |  20 +-
 arch/x86/include/asm/msr-index.h                   |   1 +
 arch/x86/include/asm/svm.h                         |  40 +-
 arch/x86/include/asm/vmx.h                         |   1 +
 arch/x86/include/uapi/asm/kvm.h                    |   1 +
 arch/x86/include/uapi/asm/svm.h                    |  28 +
 arch/x86/include/uapi/asm/vmx.h                    |   2 +
 arch/x86/kernel/cpu/cpuid-deps.c                   |   1 +
 arch/x86/kernel/cpu/scattered.c                    |   1 +
 arch/x86/kernel/cpu/vmware.c                       |  12 +-
 arch/x86/kernel/kvmclock.c                         |   1 -
 arch/x86/kvm/Kconfig                               |   3 +-
 arch/x86/kvm/Makefile                              |   3 +-
 arch/x86/kvm/cpuid.c                               |   3 +-
 arch/x86/kvm/cpuid.h                               |  14 +
 arch/x86/kvm/hyperv.c                              |   6 +-
 arch/x86/kvm/hyperv.h                              |   4 +-
 arch/x86/kvm/kvm_cache_regs.h                      |  51 +-
 arch/x86/kvm/lapic.c                               |  45 +-
 arch/x86/kvm/mmu/mmu.c                             |  10 +-
 arch/x86/kvm/mmu/mmutrace.h                        |  29 +
 arch/x86/kvm/mmu/tdp_mmu.c                         |  16 +-
 arch/x86/kvm/mtrr.c                                |   6 +-
 arch/x86/kvm/svm/avic.c                            |   9 +-
 arch/x86/kvm/svm/nested.c                          |  11 +-
 arch/x86/kvm/svm/sev.c                             | 915 ++++++++++++++++++++-
 arch/x86/kvm/svm/svm.c                             | 469 ++++++++---
 arch/x86/kvm/svm/svm.h                             | 167 +++-
 arch/x86/kvm/svm/vmenter.S                         |  50 ++
 arch/x86/kvm/trace.h                               |  97 +++
 arch/x86/kvm/vmx/evmcs.c                           |   3 +-
 arch/x86/kvm/vmx/nested.c                          |  57 +-
 arch/x86/kvm/vmx/vmenter.S                         |   2 +-
 arch/x86/kvm/vmx/vmx.c                             | 171 ++--
 arch/x86/kvm/vmx/vmx.h                             |   2 +-
 arch/x86/kvm/x86.c                                 | 511 +++++++++---
 arch/x86/kvm/x86.h                                 |  31 +-
 drivers/firmware/psci/psci.c                       | 126 +--
 drivers/irqchip/irq-gic-v3-its.c                   |  12 +-
 drivers/irqchip/irq-gic-v4.c                       |  19 +
 drivers/vfio/virqfd.c                              |   3 +
 fs/eventfd.c                                       |   5 +-
 include/kvm/arm_pmu.h                              |   3 -
 include/kvm/arm_vgic.h                             |   1 +
 include/linux/eventfd.h                            |   6 +
 include/linux/irqchip/arm-gic-v4.h                 |   4 +
 include/linux/kvm_dirty_ring.h                     | 103 +++
 include/linux/kvm_host.h                           |  21 +-
 include/linux/psci.h                               |   9 +
 include/linux/wait.h                               |  12 +-
 include/trace/events/kvm.h                         |  63 ++
 include/uapi/linux/kvm.h                           |  56 +-
 kernel/sched/wait.c                                |  17 +-
 tools/testing/selftests/kvm/.gitignore             |   6 +-
 tools/testing/selftests/kvm/Makefile               |   5 +-
 tools/testing/selftests/kvm/aarch64/get-reg-list.c |  39 +-
 tools/testing/selftests/kvm/dirty_log_perf_test.c  |  55 +-
 tools/testing/selftests/kvm/dirty_log_test.c       | 344 +++++++-
 tools/testing/selftests/kvm/include/kvm_util.h     |  38 +-
 .../testing/selftests/kvm/include/perf_test_util.h |   4 -
 .../kvm/include/s390x/diag318_test_handler.h       |  13 +
 .../selftests/kvm/include/x86_64/processor.h       |  17 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |   4 -
 .../testing/selftests/kvm/lib/aarch64/processor.c  |  17 -
 tools/testing/selftests/kvm/lib/kvm_util.c         | 158 +++-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   4 +
 .../selftests/kvm/lib/s390x/diag318_test_handler.c |  82 ++
 tools/testing/selftests/kvm/lib/s390x/processor.c  |  22 -
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  32 -
 tools/testing/selftests/kvm/s390x/sync_regs_test.c |  16 +-
 .../testing/selftests/kvm/set_memory_region_test.c |   2 -
 .../selftests/kvm/x86_64/cr4_cpuid_sync_test.c     |   1 -
 tools/testing/selftests/kvm/x86_64/debug_regs.c    |   1 -
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   2 -
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  |  87 +-
 tools/testing/selftests/kvm/x86_64/kvm_pv_test.c   |   4 +-
 .../testing/selftests/kvm/x86_64/set_sregs_test.c  |  92 ++-
 tools/testing/selftests/kvm/x86_64/smm_test.c      |   2 -
 tools/testing/selftests/kvm/x86_64/state_test.c    |   1 -
 .../testing/selftests/kvm/x86_64/svm_vmcall_test.c |   1 -
 tools/testing/selftests/kvm/x86_64/tsc_msrs_test.c |   1 -
 tools/testing/selftests/kvm/x86_64/user_msr_test.c | 248 ------
 .../selftests/kvm/x86_64/userspace_msr_exit_test.c | 770 +++++++++++++++++
 .../selftests/kvm/x86_64/vmx_apic_access_test.c    |   1 -
 .../kvm/x86_64/vmx_close_while_nested_test.c       |   1 -
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c      |   1 -
 .../kvm/x86_64/vmx_preemption_timer_test.c         |  15 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c         |  21 +
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c     |   1 -
 virt/kvm/dirty_ring.c                              | 194 +++++
 virt/kvm/eventfd.c                                 |   9 +-
 virt/kvm/kvm_main.c                                | 170 +++-
 171 files changed, 7242 insertions(+), 2750 deletions(-)


+++ b/arch/arm64/include/asm/kvm_asm.h
@@@ -199,6 -198,14 +199,12 @@@ extern void __vgic_v3_init_lrs(void)
  
  extern u32 __kvm_get_mdcr_el2(void);
  
 -extern char __smccc_workaround_1_smc[__SMCCC_WORKAROUND_1_SMC_SZ];
 -
+ #if defined(GCC_VERSION) && GCC_VERSION < 50000
+ #define SYM_CONSTRAINT	"i"
+ #else
+ #define SYM_CONSTRAINT	"S"
+ #endif
+ 
  /*
   * Obtain the PC-relative address of a kernel symbol
   * s: symbol
+++ b/arch/x86/kvm/svm/svm.c
@@@ -1347,8 -1309,10 +1347,10 @@@ static int svm_create_vcpu(struct kvm_v
  		svm->avic_is_running = true;
  
  	svm->msrpm = svm_vcpu_alloc_msrpm();
- 	if (!svm->msrpm)
+ 	if (!svm->msrpm) {
+ 		err = -ENOMEM;
 -		goto error_free_vmcb_page;
 +		goto error_free_vmsa_page;
+ 	}
  
  	svm_vcpu_init_msrpm(vcpu, svm->msrpm);

```
