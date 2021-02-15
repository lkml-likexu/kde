#### [GIT PULL] First batch of KVM changes for Linux 5.12
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12087293
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 28F72C433DB
	for <kvm@archiver.kernel.org>; Sun, 14 Feb 2021 17:30:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF36864E10
	for <kvm@archiver.kernel.org>; Sun, 14 Feb 2021 17:30:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229837AbhBNRa0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 14 Feb 2021 12:30:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:53315 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229759AbhBNRaU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 14 Feb 2021 12:30:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613323730;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mJNTtX4s1qBoY3u4p3ir1UnvA/3tMc4y2IumGyjFCQQ=;
        b=IKhcpARD8sXzqw0dbB1VPe0HQeg9hd+0EYtTiRhEnaED5YidfNhGydM1wf4kqAbXPamE/x
        819x0N4F3H/4opR9yowRxaWDCrFH7KVxRNXN7nGJicHb+JUCJGSo2Q9Q/DuPD5U3K1j+Sx
        zyXwpD+eyA3HtWW4JDuCkhRjqaLEa98=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-385-1SsbvHpEN9W5UBqEYTTvuw-1; Sun, 14 Feb 2021 12:28:48 -0500
X-MC-Unique: 1SsbvHpEN9W5UBqEYTTvuw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1B367107ACE3;
        Sun, 14 Feb 2021 17:28:47 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A2DCB5C241;
        Sun, 14 Feb 2021 17:28:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] First batch of KVM changes for Linux 5.12
Date: Sun, 14 Feb 2021 12:28:45 -0500
Message-Id: <20210214172845.1047934-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

I am sending an early pull request with the material that does not depend
on any bare metal changes, especially since ARM64 and PPC submaintainers
have already sent their stuff to me.

The following changes since commit 87aa9ec939ec7277b730786e19c161c9194cc8ca:

  KVM: x86/mmu: Fix TDP MMU zap collapsible SPTEs (2021-02-04 04:38:53 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 8c6e67bec3192f16fa624203c8131e10cc4814ba:

  Merge tag 'kvmarm-5.12' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2021-02-12 11:23:44 -0500)

----------------------------------------------------------------
x86:
- Support for userspace to emulate Xen hypercalls
- Raise the maximum number of user memslots
- Scalability improvements for the new MMU.  Instead of the complex
  "fast page fault" logic that is used in mmu.c, tdp_mmu.c uses an
  rwlock so that page faults are concurrent, but the code that can run
  against page faults is limited.  Right now only page faults take the
  lock for reading; in the future this will be extended to some
  cases of page table destruction.  I hope to switch the default MMU
  around 5.12-rc3 (some testing was delayed due to Chinese New Year).
- Cleanups for MAXPHYADDR checks
- Use static calls for vendor-specific callbacks
- On AMD, use VMLOAD/VMSAVE to save and restore host state
- Stop using deprecated jump label APIs
- Workaround for AMD erratum that made nested virtualization unreliable
- Support for LBR emulation in the guest
- Support for communicating bus lock vmexits to userspace
- Add support for SEV attestation command
- Miscellaneous cleanups

PPC:
- Support for second data watchpoint on POWER10
- Remove some complex workarounds for buggy early versions of POWER9
- Guest entry/exit fixes

ARM64
- Make the nVHE EL2 object relocatable
- Cleanups for concurrent translation faults hitting the same page
- Support for the standard TRNG hypervisor call
- A bunch of small PMU/Debug fixes
- Simplification of the early init hypercall handling

Non-KVM changes (with acks):
- Detection of contended rwlocks (implemented only for qrwlocks,
  because KVM only needs it for x86)
- Allow __DISABLE_EXPORTS from assembly code
- Provide a saner follow_pfn replacements for modules

----------------------------------------------------------------

Regarding conflicts, I would have expected git to figure it out,
but anyway the line in the pull request is the correct one:

<<<<<<< pull request (correct)
        vcpu->arch.reserved_gpa_bits = kvm_vcpu_reserved_gpa_bits_raw(vcpu);
=======
        vcpu->arch.cr3_lm_rsvd_bits = rsvd_bits(cpuid_maxphyaddr(vcpu), 63);
>>>>>>> 5.11

Thanks,

Paolo

Alexandru Elisei (1):
      KVM: arm64: Correct spelling of DBGDIDR register

Andrew Scull (1):
      KVM: arm64: Simplify __kvm_hyp_init HVC detection

Ard Biesheuvel (2):
      firmware: smccc: Add SMCCC TRNG function call IDs
      KVM: arm64: Implement the TRNG hypervisor call

Bandan Das (1):
      KVM: SVM: Add emulation support for #GP triggered by SVM instructions

Ben Gardon (30):
      KVM: selftests: Rename timespec_diff_now to timespec_elapsed
      KVM: selftests: Avoid flooding debug log while populating memory
      KVM: selftests: Convert iterations to int in dirty_log_perf_test
      KVM: selftests: Fix population stage in dirty_log_perf_test
      KVM: selftests: Add option to overlap vCPU memory access
      KVM: selftests: Add memslot modification stress test
      KVM: selftests: Add backing src parameter to dirty_log_perf_test
      KVM: selftests: Disable dirty logging with vCPUs running
      KVM: x86/mmu: change TDP MMU yield function returns to match cond_resched
      KVM: x86/mmu: Add comment on __tdp_mmu_set_spte
      KVM: x86/mmu: Add lockdep when setting a TDP MMU SPTE
      KVM: x86/mmu: Don't redundantly clear TDP MMU pt memory
      KVM: x86/mmu: Factor out handling of removed page tables
      KVM: x86/mmu: Fix braces in kvm_recover_nx_lpages
      KVM: x86/mmu: Merge flush and non-flush tdp_mmu_iter_cond_resched
      KVM: x86/mmu: Rename goal_gfn to next_last_level_gfn
      KVM: x86/mmu: Ensure forward progress when yielding in TDP MMU iter
      KVM: x86/mmu: Yield in TDU MMU iter even if no SPTES changed
      KVM: x86/mmu: Skip no-op changes in TDP MMU functions
      KVM: x86/mmu: Clear dirtied pages mask bit before early break
      KVM: x86/mmu: Protect TDP MMU page table memory with RCU
      locking/rwlocks: Add contention detection for rwlocks
      sched: Add needbreak for rwlocks
      sched: Add cond_resched_rwlock
      KVM: x86/mmu: Use an rwlock for the x86 MMU
      KVM: x86/mmu: Factor out functions to add/remove TDP MMU pages
      KVM: x86/mmu: Use atomic ops to set SPTEs in TDP MMU map
      KVM: x86/mmu: Flush TLBs after zap in TDP MMU PF handler
      KVM: x86/mmu: Mark SPTEs in disconnected pages as removed
      KVM: x86/mmu: Allow parallel page faults for the TDP MMU

Brijesh Singh (1):
      KVM/SVM: add support for SEV attestation command

Chenyi Qiang (4):
      KVM: X86: Reset the vcpu->run->flags at the beginning of vcpu_run
      KVM: VMX: Enable bus lock VM exit
      KVM: X86: Add the Document for KVM_CAP_X86_BUS_LOCK_EXIT
      KVM: X86: Rename DR6_INIT to DR6_ACTIVE_LOW

Cun Li (1):
      KVM: Stop using deprecated jump label APIs

David Brazdil (8):
      KVM: arm64: Rename .idmap.text in hyp linker script
      KVM: arm64: Set up .hyp.rodata ELF section
      KVM: arm64: Add symbol at the beginning of each hyp section
      KVM: arm64: Generate hyp relocation data
      KVM: arm64: Apply hyp relocations at runtime
      KVM: arm64: Fix constant-pool users in hyp
      KVM: arm64: Remove patching of fn pointers in hyp
      KVM: arm64: Remove hyp_symbol_addr

David P. Reed (1):
      x86/virt: Mark flags and memory as clobbered by VMXOFF

David Woodhouse (12):
      KVM: x86/xen: Fix __user pointer handling for hypercall page installation
      KVM: x86/xen: Move KVM_XEN_HVM_CONFIG handling to xen.c
      KVM: x86/xen: Add kvm_xen_enabled static key
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86/xen: Add KVM_XEN_VCPU_SET_ATTR/KVM_XEN_VCPU_GET_ATTR
      KVM: x86/xen: Add event channel interrupt vector upcall
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates
      KVM: x86/xen: Remove extra unlock in kvm_xen_hvm_set_attr()
      KVM: x86/xen: Allow reset of Xen attributes

Fabiano Rosas (2):
      KVM: PPC: Book3S HV: Save and restore FSCR in the P9 path
      KVM: PPC: Don't always report hash MMU capability for P9 < DD2.2

Jason Baron (3):
      KVM: X86: prepend vmx/svm prefix to additional kvm_x86_ops functions
      KVM: x86: introduce definitions to support static calls for kvm_x86_ops
      KVM: x86: use static calls to reduce kvm_x86_ops overhead

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: register vcpu time info region

Krish Sadhukhan (1):
      KVM: SVM: Replace hard-coded value with #define

Kyung Min Park (1):
      Enumerate AVX Vector Neural Network instructions

Like Xu (10):
      KVM: VMX: read/write MSR_IA32_DEBUGCTLMSR from GUEST_IA32_DEBUGCTL
      KVM: x86/vmx: Make vmx_set_intercept_for_msr() non-static
      KVM: vmx/pmu: Add PMU_CAP_LBR_FMT check when guest LBR is enabled
      KVM: vmx/pmu: Create a guest LBR event when vcpu sets DEBUGCTLMSR_LBR
      KVM: vmx/pmu: Pass-through LBR msrs when the guest LBR event is ACTIVE
      KVM: vmx/pmu: Reduce the overhead of LBR pass-through or cancellation
      KVM: vmx/pmu: Emulate legacy freezing LBRs on virtual PMI
      KVM: vmx/pmu: Release guest LBR event via lazy release mechanism
      KVM: vmx/pmu: Expose LBR_FMT in the MSR_IA32_PERF_CAPABILITIES
      selftests: kvm/x86: add test for pmu msr MSR_IA32_PERF_CAPABILITIES

Maciej S. Szmigiero (1):
      KVM: x86/mmu: Make HVA handler retpoline-friendly

Marc Zyngier (16):
      arm64: Drop workaround for broken 'S' constraint with GCC 4.9
      Merge branch 'arm64/for-next/misc' into kvm-arm64/hyp-reloc
      KVM: arm64: Make gen-hyprel endianness agnostic
      KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
      KVM: arm64: Fix AArch32 PMUv3 capping
      KVM: arm64: Add handling of AArch32 PCMEID{2,3} PMUv3 registers
      KVM: arm64: Refactor filtering of ID registers
      KVM: arm64: Limit the debug architecture to ARMv8.0
      KVM: arm64: Upgrade PMU support to ARMv8.4
      KVM: arm64: Use symbolic names for the PMU versions
      Merge tag 'kvmarm-fixes-5.11-2' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.12' into kvmarm-master/next
      Merge branch 'kvm-arm64/concurrent-translation-fault' into kvmarm-master/next
      Merge branch 'kvm-arm64/hyp-reloc' into kvmarm-master/next
      Merge branch 'kvm-arm64/rng-5.12' into kvmarm-master/next
      Merge branch 'kvm-arm64/pmu-debug-fixes-5.11' into kvmarm-master/next

Michael Roth (3):
      KVM: SVM: use vmsave/vmload for saving/restoring additional host state
      KVM: SVM: remove uneeded fields from host_save_users_msrs
      KVM: SVM: use .prepare_guest_switch() to handle CPU register save/setup

Nicholas Piggin (5):
      KVM: PPC: Book3S HV: Remove support for running HPT guest on RPT host without mixed mode support
      KVM: PPC: Book3S HV: Fix radix guest SLB side channel
      KVM: PPC: Book3S HV: No need to clear radix host SLB before loading HPT guest
      KVM: PPC: Book3S HV: Use POWER9 SLBIA IH=6 variant to clear SLB
      KVM: PPC: Book3S HV: Fix host radix SLB optimisation with hash guests

Paolo Bonzini (14):
      KVM: do not assume PTE is writable after follow_pfn
      KVM: x86/pmu: preserve IA32_PERF_CAPABILITIES across CPUID refresh
      KVM: vmx/pmu: Add PMU_CAP_LBR_FMT check when guest LBR is enabled
      KVM: move EXIT_FASTPATH_REENTER_GUEST to common code
      KVM: cleanup DR6/DR7 reserved bits checks
      KVM: x86: move kvm_inject_gp up from kvm_set_xcr to callers
      i915: kvmgt: the KVM mmu_lock is now an rwlock
      KVM: x86: compile out TDP MMU on 32-bit systems
      mm: provide a saner PTE walking API for modules
      KVM: x86: reading DR cannot fail
      KVM: x86: move kvm_inject_gp up from kvm_set_dr to callers
      Documentation: kvm: fix warning
      Merge tag 'kvm-ppc-next-5.12-1' of git://git.kernel.org/.../paulus/powerpc into HEAD
      Merge tag 'kvmarm-5.12' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Ensure radix guest has no SLB entries

Peter Shier (2):
      KVM: selftests: Test IPI to halted vCPU in xAPIC while backing page moves
      KVM: selftests: Add missing header file needed by xAPIC IPI tests

Quentin Perret (2):
      asm-generic: export: Stub EXPORT_SYMBOL with __DISABLE_EXPORTS
      KVM: arm64: Stub EXPORT_SYMBOL for nVHE EL2 code

Ravi Bangoria (4):
      KVM: PPC: Book3S HV: Allow nested guest creation when L0 hv_guest_state > L1
      KVM: PPC: Book3S HV: Rename current DAWR macros and variables
      KVM: PPC: Book3S HV: Add infrastructure to support 2nd DAWR
      KVM: PPC: Book3S HV: Introduce new capability for 2nd DAWR

Ricardo Koller (1):
      KVM: selftests: Add operand to vmsave/vmload/vmrun in svm.c

Sean Christopherson (34):
      KVM: x86: Remove obsolete disabling of page faults in kvm_arch_vcpu_put()
      KVM: x86: Take KVM's SRCU lock only if steal time update is needed
      KVM: x86/mmu: Use boolean returns for (S)PTE accessors
      KVM: x86: Zap the oldest MMU pages, not the newest
      KVM: x86/mmu: Remove the defunct update_pte() paging hook
      KVM: VMX: Convert vcpu_vmx.exit_reason to a union
      x86/apic: Export x2apic_mode for use by KVM in "warm" path
      KVM: VMX: Use x2apic_mode to avoid RDMSR when querying PI state
      x86/virt: Eat faults on VMXOFF in reboot flows
      x86/reboot: Force all cpus to exit VMX root if VMX is supported
      KVM: VMX: Move Intel PT shenanigans out of VMXON/VMXOFF flows
      KVM: VMX: Use the kernel's version of VMXOFF
      KVM: SVM: Use asm goto to handle unexpected #UD on SVM instructions
      KVM: x86: Set so called 'reserved CR3 bits in LM mask' at vCPU reset
      KVM: nSVM: Don't strip host's C-bit from guest's CR3 when reading PDPTRs
      KVM: x86: Add a helper to check for a legal GPA
      KVM: x86: Add a helper to handle legal GPA with an alignment requirement
      KVM: VMX: Use GPA legality helpers to replace open coded equivalents
      KVM: nSVM: Use common GPA helper to check for illegal CR3
      KVM: x86: SEV: Treat C-bit as legal GPA bit regardless of vCPU mode
      KVM: x86: Use reserved_gpa_bits to calculate reserved PxE bits
      KVM: x86/mmu: Add helper to generate mask of reserved HPA bits
      KVM: x86: Add helper to consolidate "raw" reserved GPA mask calculations
      KVM: Use kvm_pfn_t for local PFN variable in hva_to_pfn_remapped()
      KVM: x86/xen: Use hva_t for holding hypercall page address
      KVM: x86: Remove misleading DR6/DR7 adjustments from RSM emulation
      KVM: x86: Restore all 64 bits of DR6 and DR7 during RSM on x86-64
      KVM: SVM: Move AVIC vCPU kicking snippet to helper function
      KVM: SVM: Remove an unnecessary forward declaration
      KVM: selftests: Ignore recently added Xen tests' build output
      KVM: selftests: Fix size of memslots created by Xen tests
      KVM: selftests: Fix hex vs. decimal snafu in Xen test
      KVM: selftests: Don't bother mapping GVA for Xen shinfo test
      KVM: x86/xen: Explicitly pad struct compat_vcpu_info to 64 bytes

Stephen Zhang (1):
      KVM: x86/mmu: Add '__func__' in rmap_printk()

Tian Tao (1):
      KVM: X86: use vzalloc() instead of vmalloc/memset

Uros Bizjak (1):
      KVM/nVMX: Use __vmx_vcpu_run in nested_vmx_check_vmentry_hw

Vitaly Kuznetsov (18):
      selftest: kvm: x86: test KVM_GET_CPUID2 and guest visible CPUIDs against KVM_GET_SUPPORTED_CPUID
      selftests: kvm: Raise the default timeout to 120 seconds
      KVM: Raise the maximum number of user memslots
      selftests: kvm: Move kvm_get_supported_hv_cpuid() to common code
      selftests: kvm: Properly set Hyper-V CPUIDs in evmcs_test
      KVM: x86: hyper-v: Drop unused kvm_hv_vapic_assist_page_enabled()
      KVM: x86: hyper-v: Rename vcpu_to_hv_vcpu() to to_hv_vcpu()
      KVM: x86: hyper-v: Rename vcpu_to_synic()/synic_to_vcpu()
      KVM: x86: hyper-v: Rename vcpu_to_stimer()/stimer_to_vcpu()
      KVM: x86: hyper-v: Rename vcpu_to_hv_syndbg() to to_hv_syndbg()
      KVM: x86: hyper-v: Introduce to_kvm_hv() helper
      KVM: x86: hyper-v: Stop shadowing global 'current_vcpu' variable
      KVM: x86: hyper-v: Always use to_hv_vcpu() accessor to get to 'struct kvm_vcpu_hv'
      KVM: x86: hyper-v: Prepare to meet unallocated Hyper-V context
      KVM: x86: hyper-v: Allocate 'struct kvm_vcpu_hv' dynamically
      KVM: x86: hyper-v: Make Hyper-V emulation enablement conditional
      KVM: x86: hyper-v: Allocate Hyper-V context lazily
      KVM: x86: hyper-v: Drop hv_vcpu_to_vcpu() helper

Waiman Long (1):
      locking/arch: Move qrwlock.h include after qspinlock.h

Wei Huang (3):
      KVM: x86: Factor out x86 instruction emulation with decoding
      KVM: SVM: Add support for SVM instruction address check change
      KVM: SVM: Fix #GP handling for doubly-nested virtualization

Wei Yongjun (1):
      KVM: SVM: Make symbol 'svm_gp_erratum_intercept' static

YANG LI (1):
      x86: kvm: style: Simplify bool comparison

Yanan Wang (3):
      KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2 map
      KVM: arm64: Filter out the case of only changing permissions from stage-2 map path
      KVM: arm64: Mark the page dirty only if the fault is handled successfully

Yang Li (1):
      KVM: PPC: remove unneeded semicolon

Yang Zhong (1):
      KVM: Expose AVX_VNNI instruction to guset

 Documentation/virt/kvm/amd-memory-encryption.rst   |  21 +
 Documentation/virt/kvm/api.rst                     | 228 ++++++-
 Documentation/virt/kvm/locking.rst                 |   9 +-
 arch/arm64/include/asm/hyp_image.h                 |  29 +-
 arch/arm64/include/asm/kvm_asm.h                   |  26 -
 arch/arm64/include/asm/kvm_host.h                  |   3 +-
 arch/arm64/include/asm/kvm_mmu.h                   |  61 +-
 arch/arm64/include/asm/kvm_pgtable.h               |   5 +
 arch/arm64/include/asm/sections.h                  |   3 +-
 arch/arm64/include/asm/spinlock.h                  |   2 +-
 arch/arm64/include/asm/sysreg.h                    |   3 +
 arch/arm64/kernel/image-vars.h                     |   1 -
 arch/arm64/kernel/smp.c                            |   4 +-
 arch/arm64/kernel/vmlinux.lds.S                    |  18 +-
 arch/arm64/kvm/Makefile                            |   2 +-
 arch/arm64/kvm/arm.c                               |   7 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h            |   4 +-
 arch/arm64/kvm/hyp/nvhe/.gitignore                 |   2 +
 arch/arm64/kvm/hyp/nvhe/Makefile                   |  33 +-
 arch/arm64/kvm/hyp/nvhe/gen-hyprel.c               | 438 +++++++++++++
 arch/arm64/kvm/hyp/nvhe/host.S                     |  29 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S                 |  19 +-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c                 |  11 +-
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c                  |   4 +-
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S                  |   9 +-
 arch/arm64/kvm/hyp/nvhe/psci-relay.c               |  24 +-
 arch/arm64/kvm/hyp/pgtable.c                       |  83 +--
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   2 +-
 arch/arm64/kvm/hypercalls.c                        |   6 +
 arch/arm64/kvm/mmu.c                               |  13 +-
 arch/arm64/kvm/pmu-emul.c                          |  14 +-
 arch/arm64/kvm/sys_regs.c                          |  85 ++-
 arch/arm64/kvm/trng.c                              |  85 +++
 arch/arm64/kvm/va_layout.c                         |  34 +-
 arch/mips/include/asm/kvm_host.h                   |   1 -
 arch/mips/include/asm/spinlock.h                   |   2 +-
 arch/powerpc/include/asm/hvcall.h                  |  25 +-
 arch/powerpc/include/asm/kvm_book3s_asm.h          |  11 -
 arch/powerpc/include/asm/kvm_host.h                |   8 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |   2 +
 arch/powerpc/include/uapi/asm/kvm.h                |   2 +
 arch/powerpc/kernel/asm-offsets.c                  |   9 +-
 arch/powerpc/kvm/book3s_hv.c                       | 149 +++--
 arch/powerpc/kvm/book3s_hv_builtin.c               | 108 +---
 arch/powerpc/kvm/book3s_hv_nested.c                |  70 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            | 175 ++---
 arch/powerpc/kvm/booke.c                           |   2 +-
 arch/powerpc/kvm/powerpc.c                         |  14 +-
 arch/s390/include/asm/kvm_host.h                   |   1 -
 arch/s390/pci/pci_mmio.c                           |   4 +-
 arch/sparc/include/asm/spinlock_64.h               |   2 +-
 arch/x86/include/asm/cpufeatures.h                 |   2 +
 arch/x86/include/asm/kvm-x86-ops.h                 | 127 ++++
 arch/x86/include/asm/kvm_host.h                    |  89 ++-
 arch/x86/include/asm/virtext.h                     |  25 +-
 arch/x86/include/asm/vmx.h                         |   1 +
 arch/x86/include/asm/vmxfeatures.h                 |   1 +
 arch/x86/include/asm/xen/interface.h               |   3 +
 arch/x86/include/uapi/asm/kvm.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h                    |   4 +-
 arch/x86/kernel/apic/apic.c                        |   1 +
 arch/x86/kernel/reboot.c                           |  30 +-
 arch/x86/kvm/Makefile                              |   5 +-
 arch/x86/kvm/cpuid.c                               |  24 +-
 arch/x86/kvm/cpuid.h                               |  24 +-
 arch/x86/kvm/emulate.c                             |  14 +-
 arch/x86/kvm/hyperv.c                              | 343 ++++++----
 arch/x86/kvm/hyperv.h                              |  54 +-
 arch/x86/kvm/irq.c                                 |  10 +-
 arch/x86/kvm/kvm_cache_regs.h                      |  10 +-
 arch/x86/kvm/kvm_emulate.h                         |   2 +-
 arch/x86/kvm/lapic.c                               |  60 +-
 arch/x86/kvm/lapic.h                               |  20 +-
 arch/x86/kvm/mmu.h                                 |   8 +-
 arch/x86/kvm/mmu/mmu.c                             | 353 +++++-----
 arch/x86/kvm/mmu/mmu_audit.c                       |   8 +-
 arch/x86/kvm/mmu/mmu_internal.h                    |   7 +-
 arch/x86/kvm/mmu/page_track.c                      |   8 +-
 arch/x86/kvm/mmu/paging_tmpl.h                     |   8 +-
 arch/x86/kvm/mmu/spte.c                            |   2 +-
 arch/x86/kvm/mmu/spte.h                            |  33 +-
 arch/x86/kvm/mmu/tdp_iter.c                        |  46 +-
 arch/x86/kvm/mmu/tdp_iter.h                        |  21 +-
 arch/x86/kvm/mmu/tdp_mmu.c                         | 554 ++++++++++++----
 arch/x86/kvm/mmu/tdp_mmu.h                         |  32 +-
 arch/x86/kvm/mtrr.c                                |  12 +-
 arch/x86/kvm/pmu.c                                 |  10 +-
 arch/x86/kvm/pmu.h                                 |   2 +
 arch/x86/kvm/svm/avic.c                            |  35 +-
 arch/x86/kvm/svm/nested.c                          |   8 +-
 arch/x86/kvm/svm/sev.c                             | 104 ++-
 arch/x86/kvm/svm/svm.c                             | 303 +++++----
 arch/x86/kvm/svm/svm.h                             |  29 +-
 arch/x86/kvm/svm/svm_ops.h                         |  69 ++
 arch/x86/kvm/trace.h                               |  40 +-
 arch/x86/kvm/vmx/capabilities.h                    |  28 +-
 arch/x86/kvm/vmx/nested.c                          | 106 ++-
 arch/x86/kvm/vmx/pmu_intel.c                       | 294 ++++++++-
 arch/x86/kvm/vmx/posted_intr.c                     |   6 +-
 arch/x86/kvm/vmx/vmenter.S                         |   2 +-
 arch/x86/kvm/vmx/vmx.c                             | 282 ++++----
 arch/x86/kvm/vmx/vmx.h                             |  56 +-
 arch/x86/kvm/x86.c                                 | 718 +++++++++++----------
 arch/x86/kvm/x86.h                                 |  12 +-
 arch/x86/kvm/xen.c                                 | 431 +++++++++++++
 arch/x86/kvm/xen.h                                 |  78 +++
 arch/xtensa/include/asm/spinlock.h                 |   2 +-
 drivers/crypto/ccp/sev-dev.c                       |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c                   |  12 +-
 fs/dax.c                                           |   5 +-
 include/asm-generic/export.h                       |   2 +-
 include/asm-generic/qrwlock.h                      |  25 +-
 include/linux/arm-smccc.h                          |  31 +
 include/linux/kvm_host.h                           |  10 +-
 include/linux/mm.h                                 |   6 +-
 include/linux/psp-sev.h                            |  17 +
 include/linux/rwlock.h                             |   7 +
 include/linux/sched.h                              |  29 +
 include/uapi/linux/kvm.h                           |  74 +++
 include/xen/interface/xen.h                        |   4 +-
 kernel/locking/qrwlock.c                           |   1 -
 kernel/sched/core.c                                |  40 ++
 mm/memory.c                                        |  41 +-
 tools/arch/powerpc/include/uapi/asm/kvm.h          |   2 +
 tools/include/uapi/linux/kvm.h                     |   1 +
 tools/testing/selftests/kvm/.gitignore             |   6 +
 tools/testing/selftests/kvm/Makefile               |   6 +
 tools/testing/selftests/kvm/demand_paging_test.c   |  43 +-
 tools/testing/selftests/kvm/dirty_log_perf_test.c  |  92 +--
 tools/testing/selftests/kvm/include/kvm_util.h     |   6 -
 tools/testing/selftests/kvm/include/numaif.h       |  55 ++
 .../testing/selftests/kvm/include/perf_test_util.h |   7 +-
 tools/testing/selftests/kvm/include/test_util.h    |  16 +-
 .../selftests/kvm/include/x86_64/processor.h       |  41 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |   1 +
 tools/testing/selftests/kvm/lib/perf_test_util.c   |  31 +-
 tools/testing/selftests/kvm/lib/test_util.c        |  31 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c | 144 +++++
 tools/testing/selftests/kvm/lib/x86_64/svm.c       |   8 +-
 .../kvm/memslot_modification_stress_test.c         | 212 ++++++
 tools/testing/selftests/kvm/settings               |   1 +
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   3 +-
 .../testing/selftests/kvm/x86_64/get_cpuid_test.c  | 175 +++++
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c  |  31 +-
 .../selftests/kvm/x86_64/vmx_pmu_msrs_test.c       | 131 ++++
 .../testing/selftests/kvm/x86_64/xapic_ipi_test.c  | 544 ++++++++++++++++
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c | 167 +++++
 .../testing/selftests/kvm/x86_64/xen_vmcall_test.c | 149 +++++
 virt/kvm/dirty_ring.c                              |   8 +-
 virt/kvm/kvm_main.c                                |  54 +-
 virt/kvm/mmu_lock.h                                |  23 +
 151 files changed, 6686 insertions(+), 2066 deletions(-)
```
