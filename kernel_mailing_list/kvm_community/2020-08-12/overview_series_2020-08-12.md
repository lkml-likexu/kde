#### [GIT PULL] Second batch of KVM changes for Linux 5.9
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11710431
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 90AEC13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 08:29:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6E2CD20774
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 08:29:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="UDywF1x9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726891AbgHLI3q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 04:29:46 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:24523 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726182AbgHLI3p (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 04:29:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597220982;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pBHwdE4nrQbav59yrGa0031nQHXeparWUZMzi9PJWAY=;
        b=UDywF1x96DyCPXnjeC9GAZFDS2AuicxVf2wq55OFjgs24NOJl0DXdP867TSNtML/xnq0Qf
        VZqTeuL4M11k/UfwWpYvyJKn/38OaT9ms5pjboYkpIg0LOX29SksHVMxFlZLa8M0ekmxcB
        N33tsVo7AILdnWoHBF86CYQxs1fOgPY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-242-jXmo_KWuNcyv3IhbT3dsEg-1; Wed, 12 Aug 2020 04:29:40 -0400
X-MC-Unique: jXmo_KWuNcyv3IhbT3dsEg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B7A3A1DE1;
        Wed, 12 Aug 2020 08:29:39 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4357962672;
        Wed, 12 Aug 2020 08:29:39 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] Second batch of KVM changes for Linux 5.9
Date: Wed, 12 Aug 2020 04:29:38 -0400
Message-Id: <20200812082938.18976-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 06a81c1c7db9bd5de0bd38cd5acc44bb22b99150:

  Merge tag 'arm64-fixes' of git://git.kernel.org/pub/scm/linux/kernel/git/arm64/linux (2020-08-08 14:16:12 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e792415c5d3e0eb52527cce228a72e4392f8cae2:

  KVM: MIPS/VZ: Fix build error caused by 'kvm_run' cleanup (2020-08-11 07:19:41 -0400)

----------------------------------------------------------------
PPC:
* Improvements and bugfixes for secure VM support, giving reduced startup
  time and memory hotplug support.
* Locking fixes in nested KVM code
* Increase number of guests supported by HV KVM to 4094
* Preliminary POWER10 support

ARM:
* Split the VHE and nVHE hypervisor code bases, build the EL2 code
  separately, allowing for the VHE code to now be built with instrumentation
* Level-based TLB invalidation support
* Restructure of the vcpu register storage to accomodate the NV code
* Pointer Authentication available for guests on nVHE hosts
* Simplification of the system register table parsing
* MMU cleanups and fixes
* A number of post-32bit cleanups and other fixes

MIPS:
* compilation fixes

x86:
* bugfixes
* support for the SERIALIZE instruction

----------------------------------------------------------------
Alexander Graf (2):
      KVM: arm64: vgic-its: Change default outer cacheability for {PEND, PROP}BASER
      KVM: arm: Add trace name for ARM_NISV

Alexey Kardashevskiy (1):
      KVM: PPC: Protect kvm_vcpu_read_guest with srcu locks

Alistair Popple (1):
      KVM: PPC: Book3SHV: Enable support for ISA v3.1 guests

Andrew Scull (3):
      arm64: kvm: Remove kern_hyp_va from get_vcpu_ptr
      KVM: arm64: Handle calls to prefixed hyp functions
      KVM: arm64: Move hyp-init.S to nVHE

Christoffer Dall (1):
      KVM: arm64: Factor out stage 2 page table data from struct kvm

Cédric Le Goater (1):
      KVM: PPC: Book3S HV: Increase KVMPPC_NR_LPIDS on POWER8 and POWER9

David Brazdil (16):
      KVM: arm64: Fix symbol dependency in __hyp_call_panic_nvhe
      KVM: arm64: Move __smccc_workaround_1_smc to .rodata
      KVM: arm64: Add build rules for separate VHE/nVHE object files
      KVM: arm64: Use build-time defines in has_vhe()
      KVM: arm64: Build hyp-entry.S separately for VHE/nVHE
      KVM: arm64: Duplicate hyp/tlb.c for VHE/nVHE
      KVM: arm64: Split hyp/switch.c to VHE/nVHE
      KVM: arm64: Split hyp/debug-sr.c to VHE/nVHE
      KVM: arm64: Split hyp/sysreg-sr.c to VHE/nVHE
      KVM: arm64: Duplicate hyp/timer-sr.c for VHE/nVHE
      KVM: arm64: Compile remaining hyp/ files for both VHE/nVHE
      KVM: arm64: Remove __hyp_text macro, use build rules instead
      KVM: arm64: Lift instrumentation restrictions on VHE
      KVM: arm64: Make nVHE ASLR conditional on RANDOMIZE_BASE
      KVM: arm64: Substitute RANDOMIZE_BASE for HARDEN_EL2_VECTORS
      KVM: arm64: Ensure that all nVHE hyp code is in .hyp.text

Gavin Shan (1):
      KVM: arm64: Rename HSR to ESR

Huacai Chen (1):
      MIPS: VZ: Only include loongson_regs.h for CPU_LOONGSON64

James Morse (5):
      KVM: arm64: Drop the target_table[] indirection
      KVM: arm64: Tolerate an empty target_table list
      KVM: arm64: Move ACTLR_EL1 emulation to the sys_reg_descs array
      KVM: arm64: Remove target_table from exit handlers
      KVM: arm64: Remove the target table

Jiaxun Yang (1):
      MIPS: KVM: Convert a fallthrough comment to fallthrough

Jon Doron (1):
      x86/kvm/hyper-v: Synic default SCONTROL MSR needs to be enabled

Laurent Dufour (3):
      KVM: PPC: Book3S HV: Migrate hot plugged memory
      KVM: PPC: Book3S HV: Move kvmppc_svm_page_out up
      KVM: PPC: Book3S HV: Rework secure mem slot dropping

Marc Zyngier (28):
      KVM: arm64: Enable Address Authentication at EL2 if available
      KVM: arm64: Allow ARM64_PTR_AUTH when ARM64_VHE=n
      KVM: arm64: Allow PtrAuth to be enabled from userspace on non-VHE systems
      KVM: arm64: Check HCR_EL2 instead of shadow copy to swap PtrAuth registers
      KVM: arm64: Simplify PtrAuth alternative patching
      KVM: arm64: Allow in-atomic injection of SPIs
      Merge branch 'kvm-arm64/ttl-for-arm64' into HEAD
      KVM: arm64: Use TTL hint in when invalidating stage-2 translations
      KVM: arm64: Introduce accessor for ctxt->sys_reg
      KVM: arm64: hyp: Use ctxt_sys_reg/__vcpu_sys_reg instead of raw sys_regs access
      KVM: arm64: sve: Use __vcpu_sys_reg() instead of raw sys_regs access
      KVM: arm64: pauth: Use ctxt_sys_reg() instead of raw sys_regs access
      KVM: arm64: debug: Drop useless vpcu parameter
      KVM: arm64: Make struct kvm_regs userspace-only
      KVM: arm64: Move ELR_EL1 to the system register array
      KVM: arm64: Move SP_EL1 to the system register array
      KVM: arm64: Disintegrate SPSR array
      KVM: arm64: Move SPSR_EL1 to the system register array
      KVM: arm64: timers: Rename kvm_timer_sync_hwstate to kvm_timer_sync_user
      KVM: arm64: timers: Move timer registers to the sys_regs file
      KVM: arm64: Don't use has_vhe() for CHOOSE_HYP_SYM()
      Merge branch 'kvm-arm64/el2-obj-v4.1' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/pre-nv-5.9' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/ptrauth-nvhe' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/target-table-no-more' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/misc-5.9' into kvmarm-master/next-WIP
      Merge branch 'kvm-arm64/el2-obj-v4.1' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.9' into kvmarm-master/next

Paolo Bonzini (3):
      Merge tag 'kvmarm-5.9' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-next-5.6
      x86: Expose SERIALIZE for supported cpuid
      Merge tag 'kvm-ppc-next-5.9-1' of git://git.kernel.org/.../paulus/powerpc into kvm-next-5.6

Peng Hao (1):
      KVM: arm64: Drop long gone function parameter documentation

Ram Pai (4):
      KVM: PPC: Book3S HV: Fix function definition in book3s_hv_uvmem.c
      KVM: PPC: Book3S HV: Disable page merging in H_SVM_INIT_START
      KVM: PPC: Book3S HV: Track the state GFNs associated with secure VMs
      KVM: PPC: Book3S HV: In H_SVM_INIT_DONE, migrate remaining normal-GFNs to secure-GFNs

Sean Christopherson (1):
      KVM: x86: Don't attempt to load PDPTRs when 64-bit mode is enabled

Tianjia Zhang (1):
      KVM: PPC: Clean up redundant kvm_run parameters in assembly

Will Deacon (4):
      KVM: arm64: Rename kvm_vcpu_dabt_isextabt()
      KVM: arm64: Handle data and instruction external aborts the same way
      KVM: arm64: Don't skip cache maintenance for read-only memslots
      KVM: arm64: Move S1PTW S2 fault logic out of io_mem_abort()

Xingxing Su (1):
      KVM: MIPS/VZ: Fix build error caused by 'kvm_run' cleanup

 Documentation/powerpc/ultravisor.rst               |   3 +
 arch/arm64/Kconfig                                 |  20 +-
 arch/arm64/include/asm/kvm_asm.h                   |  75 +-
 arch/arm64/include/asm/kvm_coproc.h                |   8 -
 arch/arm64/include/asm/kvm_emulate.h               |  75 +-
 arch/arm64/include/asm/kvm_host.h                  |  94 ++-
 arch/arm64/include/asm/kvm_hyp.h                   |  15 +-
 arch/arm64/include/asm/kvm_mmu.h                   |  16 +-
 arch/arm64/include/asm/kvm_ptrauth.h               |  34 +-
 arch/arm64/include/asm/mmu.h                       |   7 -
 arch/arm64/include/asm/virt.h                      |  13 +-
 arch/arm64/kernel/asm-offsets.c                    |   3 +-
 arch/arm64/kernel/cpu_errata.c                     |   4 +-
 arch/arm64/kernel/image-vars.h                     |  54 ++
 arch/arm64/kvm/Kconfig                             |   2 +-
 arch/arm64/kvm/Makefile                            |   4 +-
 arch/arm64/kvm/arch_timer.c                        | 157 +++-
 arch/arm64/kvm/arm.c                               |  57 +-
 arch/arm64/kvm/fpsimd.c                            |   6 +-
 arch/arm64/kvm/guest.c                             |  79 +-
 arch/arm64/kvm/handle_exit.c                       |  32 +-
 arch/arm64/kvm/hyp/Makefile                        |  24 +-
 arch/arm64/kvm/hyp/aarch32.c                       |   8 +-
 arch/arm64/kvm/hyp/entry.S                         |   4 +-
 arch/arm64/kvm/hyp/fpsimd.S                        |   1 -
 arch/arm64/kvm/hyp/hyp-entry.S                     |  21 +-
 .../kvm/hyp/{debug-sr.c => include/hyp/debug-sr.h} |  88 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h            | 511 +++++++++++
 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h         | 193 +++++
 arch/arm64/kvm/hyp/nvhe/Makefile                   |  62 ++
 arch/arm64/kvm/hyp/nvhe/debug-sr.c                 |  77 ++
 arch/arm64/kvm/{ => hyp/nvhe}/hyp-init.S           |   5 +
 arch/arm64/kvm/hyp/nvhe/switch.c                   | 272 ++++++
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c                |  46 +
 arch/arm64/kvm/hyp/{ => nvhe}/timer-sr.c           |   6 +-
 arch/arm64/kvm/hyp/nvhe/tlb.c                      | 154 ++++
 arch/arm64/kvm/hyp/smccc_wa.S                      |  32 +
 arch/arm64/kvm/hyp/switch.c                        | 936 ---------------------
 arch/arm64/kvm/hyp/sysreg-sr.c                     | 333 --------
 arch/arm64/kvm/hyp/tlb.c                           | 242 ------
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   4 +-
 arch/arm64/kvm/hyp/vgic-v3-sr.c                    | 134 ++-
 arch/arm64/kvm/hyp/vhe/Makefile                    |  11 +
 arch/arm64/kvm/hyp/vhe/debug-sr.c                  |  26 +
 arch/arm64/kvm/hyp/vhe/switch.c                    | 219 +++++
 arch/arm64/kvm/hyp/vhe/sysreg-sr.c                 | 114 +++
 arch/arm64/kvm/hyp/vhe/timer-sr.c                  |  12 +
 arch/arm64/kvm/hyp/vhe/tlb.c                       | 162 ++++
 arch/arm64/kvm/inject_fault.c                      |   2 +-
 arch/arm64/kvm/mmio.c                              |   6 -
 arch/arm64/kvm/mmu.c                               | 311 ++++---
 arch/arm64/kvm/regmap.c                            |  37 +-
 arch/arm64/kvm/reset.c                             |  23 +-
 arch/arm64/kvm/sys_regs.c                          | 207 ++---
 arch/arm64/kvm/sys_regs_generic_v8.c               |  96 ---
 arch/arm64/kvm/trace_arm.h                         |   8 +-
 arch/arm64/kvm/va_layout.c                         |   2 +-
 arch/arm64/kvm/vgic/vgic-irqfd.c                   |  24 +-
 arch/arm64/kvm/vgic/vgic-its.c                     |   3 +-
 arch/arm64/kvm/vgic/vgic-mmio-v3.c                 |   2 +-
 arch/mips/kvm/emulate.c                            |   2 +-
 arch/mips/kvm/vz.c                                 |   5 +-
 arch/powerpc/include/asm/kvm_book3s_uvmem.h        |  14 +
 arch/powerpc/include/asm/kvm_ppc.h                 |   2 +-
 arch/powerpc/include/asm/reg.h                     |   4 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |   8 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |   4 +
 arch/powerpc/kvm/book3s_hv.c                       |  26 +-
 arch/powerpc/kvm/book3s_hv_nested.c                |  30 +-
 arch/powerpc/kvm/book3s_hv_uvmem.c                 | 700 +++++++++++----
 arch/powerpc/kvm/book3s_interrupts.S               |  56 +-
 arch/powerpc/kvm/book3s_pr.c                       |   9 +-
 arch/powerpc/kvm/book3s_rtas.c                     |   2 +
 arch/powerpc/kvm/booke.c                           |   9 +-
 arch/powerpc/kvm/booke_interrupts.S                |   9 +-
 arch/powerpc/kvm/bookehv_interrupts.S              |  10 +-
 arch/powerpc/kvm/powerpc.c                         |   5 +-
 arch/x86/kvm/cpuid.c                               |   3 +-
 arch/x86/kvm/hyperv.c                              |   1 +
 arch/x86/kvm/x86.c                                 |  24 +-
 include/kvm/arm_arch_timer.h                       |  13 +-
 include/trace/events/kvm.h                         |   2 +-
 scripts/kallsyms.c                                 |   1 +
 83 files changed, 3479 insertions(+), 2636 deletions(-)
 rename arch/arm64/kvm/hyp/{debug-sr.c => include/hyp/debug-sr.h} (66%)
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/switch.h
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h
 create mode 100644 arch/arm64/kvm/hyp/nvhe/Makefile
 create mode 100644 arch/arm64/kvm/hyp/nvhe/debug-sr.c
 rename arch/arm64/kvm/{ => hyp/nvhe}/hyp-init.S (95%)
 create mode 100644 arch/arm64/kvm/hyp/nvhe/switch.c
 create mode 100644 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c
 rename arch/arm64/kvm/hyp/{ => nvhe}/timer-sr.c (84%)
 create mode 100644 arch/arm64/kvm/hyp/nvhe/tlb.c
 create mode 100644 arch/arm64/kvm/hyp/smccc_wa.S
 delete mode 100644 arch/arm64/kvm/hyp/switch.c
 delete mode 100644 arch/arm64/kvm/hyp/sysreg-sr.c
 delete mode 100644 arch/arm64/kvm/hyp/tlb.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/Makefile
 create mode 100644 arch/arm64/kvm/hyp/vhe/debug-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/switch.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/sysreg-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/timer-sr.c
 create mode 100644 arch/arm64/kvm/hyp/vhe/tlb.c
 delete mode 100644 arch/arm64/kvm/sys_regs_generic_v8.c
```
#### [GIT PULL] VFIO updates for v5.9-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11710217
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31EF2109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 02:31:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1064220782
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 02:31:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="VDkqO16T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726483AbgHLCbw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 22:31:52 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:27488 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726235AbgHLCbv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 22:31:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1597199510;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=2EC38ghpNZUdwD9Qkzu2IPHuATHcILU8kmquKFz/u7E=;
        b=VDkqO16TdW2W5zKjHEnv2R4QUHcmeHYCCXkttG5ZoouOBTH6QRDdCuLEPBayIrGLRSDQqD
        CPV8yE0f6pykyzxrmMmTnQ+uPclgEF+ktkXy11YXyMAQvddaBs4alcYXVJ77fx6PZxRbIF
        EP+T8eNM0fREkGuJXv3/g10ew3pYO68=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-513-k48dE6NrNqaehmKFfqVikw-1; Tue, 11 Aug 2020 22:31:48 -0400
X-MC-Unique: k48dE6NrNqaehmKFfqVikw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BEC0857;
        Wed, 12 Aug 2020 02:31:47 +0000 (UTC)
Received: from x1.home (ovpn-112-71.phx2.redhat.com [10.3.112.71])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 861537AC68;
        Wed, 12 Aug 2020 02:31:47 +0000 (UTC)
Date: Tue, 11 Aug 2020 20:31:47 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
Subject: [GIT PULL] VFIO updates for v5.9-rc1
Message-ID: <20200811203147.1ad96351@x1.home>
Organization: Red Hat
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

The following changes since commit 92ed301919932f777713b9172e525674157e983d:

  Linux 5.8-rc7 (2020-07-26 14:14:06 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.9-rc1

for you to fetch changes up to ccd59dce1a21f473518bf273bdf5b182bab955b3:

  vfio/type1: Refactor vfio_iommu_type1_ioctl() (2020-07-27 13:46:13 -0600)

----------------------------------------------------------------
VFIO updates for v5.9-rc1

 - Inclusive naming updates (Alex Williamson)

 - Intel X550 INTx quirk (Alex Williamson)

 - Error path resched between unmaps (Xiang Zheng)

 - SPAPR IOMMU pin_user_pages() conversion (John Hubbard)

 - Trivial mutex simplification (Alex Williamson)

 - QAT device denylist (Giovanni Cabiddu)

 - type1 IOMMU ioctl refactor (Liu Yi L)

----------------------------------------------------------------
Alex Williamson (3):
      vfio: Cleanup allowed driver naming
      vfio/pci: Add Intel X550 to hidden INTx devices
      vfio/pci: Hold igate across releasing eventfd contexts

Giovanni Cabiddu (3):
      PCI: Add Intel QuickAssist device IDs
      vfio/pci: Add device denylist
      vfio/pci: Add QAT devices to denylist

John Hubbard (1):
      vfio/spapr_tce: convert get_user_pages() --> pin_user_pages()

Liu Yi L (1):
      vfio/type1: Refactor vfio_iommu_type1_ioctl()

Xiang Zheng (1):
      vfio/type1: Add conditional rescheduling after iommu map failed

 drivers/vfio/pci/vfio_pci.c         |  54 ++++-
 drivers/vfio/vfio.c                 |  13 +-
 drivers/vfio/vfio_iommu_spapr_tce.c |   4 +-
 drivers/vfio/vfio_iommu_type1.c     | 398 +++++++++++++++++++-----------------
 include/linux/pci_ids.h             |   6 +
 5 files changed, 282 insertions(+), 193 deletions(-)
```
#### [PATCH] KVM: nVMX: Add VM-Enter failed tracepoints for super early checks
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11711093
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6BC7116B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 18:06:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E55220771
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 18:06:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726574AbgHLSGS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 14:06:18 -0400
Received: from mga12.intel.com ([192.55.52.136]:43006 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726276AbgHLSGR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 14:06:17 -0400
IronPort-SDR: 
 FfZu0VQSB1bRIAF33KH8QyxXMRNMH9v7MGLC5u9oP6iL5MNIItLhN3Vz+lNvcEWq74XwzuayB1
 uxdhB+Fnoatg==
X-IronPort-AV: E=McAfee;i="6000,8403,9711"; a="133569778"
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="133569778"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Aug 2020 11:06:17 -0700
IronPort-SDR: 
 gfBVxQ/FtmJxLpgjUjBFChXbTpXK9Kt0h2RZ4a53+i8J8dUxU2h9rPcImy/kVmVmz2ye9VkHF3
 hqRDBVNsFxUQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="277908667"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 12 Aug 2020 11:06:17 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: Add VM-Enter failed tracepoints for super early
 checks
Date: Wed, 12 Aug 2020 11:06:15 -0700
Message-Id: <20200812180615.22372-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add tracepoints for the early consistency checks in nested_vmx_run().
The "VMLAUNCH vs. VMRESUME" check in particular is useful to trace, as
there is no architectural way to check VMCS.LAUNCH_STATE, and subtle
bugs such as VMCLEAR on the wrong HPA can lead to confusing errors in
the L1 VMM.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: nVMX: Morph notification vector IRQ on nested VM-Enter to pending PI
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11711091
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E93B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 17:51:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FC6620866
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 17:51:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726518AbgHLRvd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 13:51:33 -0400
Received: from mga11.intel.com ([192.55.52.93]:8711 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726013AbgHLRvc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 13:51:32 -0400
IronPort-SDR: 
 SetiZDw/HCyivUTQmI71Wi+DwV83LWLpBzQq87qJFMpfuwKEm6V+mkHq/GcGeNJNkCa3emO5ds
 yAppI9f+2Gug==
X-IronPort-AV: E=McAfee;i="6000,8403,9711"; a="151683229"
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="151683229"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Aug 2020 10:51:30 -0700
IronPort-SDR: 
 PaPn9eCBmBUz7md84VtPMA8A3zjis7ZWdVqCjt3lbfKIJiErQswbDanNY8VDImLLGFsDqt1LBW
 GkZ/ERpujdJw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="277905359"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 12 Aug 2020 10:51:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>
Subject: [PATCH] KVM: nVMX: Morph notification vector IRQ on nested VM-Enter
 to pending PI
Date: Wed, 12 Aug 2020 10:51:29 -0700
Message-Id: <20200812175129.12172-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On successful nested VM-Enter, check for pending interrupts and convert
the highest priority interrupt to a pending posted interrupt if it
matches L2's notification vector.  If the vCPU receives a notification
interrupt before nested VM-Enter (assuming L1 disables IRQs before doing
VM-Enter), the pending interrupt (for L1) should be recognized and
processed as a posted interrupt when interrupts become unblocked after
VM-Enter to L2.

This fixes a bug where L1/L2 will get stuck in an infinite loop if L1 is
trying to inject an interrupt into L2 by setting the appropriate bit in
L2's PIR and sending a self-IPI prior to VM-Enter (as opposed to KVM's
method of manually moving the vector from PIR->vIRR/RVI).  KVM will
observe the IPI while the vCPU is in L1 context and so won't immediately
morph it to a posted interrupt for L2.  The pending interrupt will be
seen by vmx_check_nested_events(), cause KVM to force an immediate exit
after nested VM-Enter, and eventually be reflected to L1 as a VM-Exit.
After handling the VM-Exit, L1 will see that L2 has a pending interrupt
in PIR, send another IPI, and repeat until L2 is killed.

Note, posted interrupts require virtual interrupt deliveriy, and virtual
interrupt delivery requires exit-on-interrupt, ergo interrupts will be
unconditionally unmasked on VM-Enter if posted interrupts are enabled.

Fixes: 705699a13994 ("KVM: nVMX: Enable nested posted interrupt processing")
Cc: stable@vger.kernel.org
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

I am by no means 100% confident this the a complete, correct fix.  I also
don't like exporting two low level LAPIC functions.  But, the fix does
appear to work as intended.

 arch/x86/kvm/lapic.c      | 7 +++++++
 arch/x86/kvm/lapic.h      | 1 +
 arch/x86/kvm/vmx/nested.c | 8 ++++++++
 3 files changed, 16 insertions(+)

```
#### [PATCH v2 1/2] KVM: x86/mmu: Move flush logic from mmu_page_zap_pte() to FNAME(invlpg)
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11711233
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6F82B618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:28:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6126520838
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:28:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726761AbgHLT2M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 15:28:12 -0400
Received: from mga18.intel.com ([134.134.136.126]:34390 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726512AbgHLT2B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 15:28:01 -0400
IronPort-SDR: 
 uXO1yVvLHv7LXUV6h9eUitPNVWd+7yqoBtOJl3dcGhSi4QOhIbDLdrMgtTfMxWmIR8SLnhluk0
 GmkKrTsm+keA==
X-IronPort-AV: E=McAfee;i="6000,8403,9711"; a="141673018"
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="141673018"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Aug 2020 12:28:00 -0700
IronPort-SDR: 
 lTLyLtOnWsbRG0K6ufIt+Ejwpz7anR2tyryDANJHRmbi1hgJHYhQzir8rdlyC6COWfJ/JJucph
 ulo/l2BqN3OA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,305,1592895600";
   d="scan'208";a="327304452"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga002.fm.intel.com with ESMTP; 12 Aug 2020 12:27:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Shier <pshier@google.com>,
        Ben Gardon <bgardon@google.com>
Subject: [PATCH v2 1/2] KVM: x86/mmu: Move flush logic from mmu_page_zap_pte()
 to FNAME(invlpg)
Date: Wed, 12 Aug 2020 12:27:57 -0700
Message-Id: <20200812192758.25587-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200812192758.25587-1-sean.j.christopherson@intel.com>
References: <20200812192758.25587-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the logic that controls whether or not FNAME(invlpg) needs to flush
fully into FNAME(invlpg) so that mmu_page_zap_pte() doesn't return a
value.  This allows a future patch to redefine the return semantics for
mmu_page_zap_pte() so that it can recursively zap orphaned child shadow
pages for nested TDP MMUs.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c         | 10 +++-------
 arch/x86/kvm/mmu/paging_tmpl.h |  7 +++++--
 2 files changed, 8 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: x86/pmu: Add '.exclude_hv = 1' for guest perf_event
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11710255
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E569138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 05:10:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 083BA20768
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 05:10:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726507AbgHLFJw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 01:09:52 -0400
Received: from mga02.intel.com ([134.134.136.20]:55625 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726264AbgHLFJv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 01:09:51 -0400
IronPort-SDR: 
 3VWtqI8RHhRNxYKPm6bz+5R2Q7LMoEygJNQLqsCALpcArhdSI/g1/WcSCE5XM4Dn3YY9bqB3yt
 k5Je4nCCZCXw==
X-IronPort-AV: E=McAfee;i="6000,8403,9710"; a="141729292"
X-IronPort-AV: E=Sophos;i="5.76,303,1592895600";
   d="scan'208";a="141729292"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Aug 2020 22:09:51 -0700
IronPort-SDR: 
 jV/u4H842sfXW8M/als+kPyHvjNbX23gNxcm6qen1ioionXCqgHWipvLZud5Fxj5v4NHS4f65y
 MWETPvQgc1pg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,303,1592895600";
   d="scan'208";a="332706627"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by FMSMGA003.fm.intel.com with ESMTP; 11 Aug 2020 22:09:48 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Jin@vger.kernel.org, Yao <yao.jin@linux.intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/pmu: Add '.exclude_hv = 1' for guest perf_event
Date: Wed, 12 Aug 2020 13:07:22 +0800
Message-Id: <20200812050722.25824-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To emulate PMC counter for guest, KVM would create an
event on the host with 'exclude_guest=0, exclude_hv=0'
which simply makes no sense and is utterly broken.

To keep perf semantics consistent, any event created by
pmc_reprogram_counter() should both set exclude_hv and
exclude_host in the KVM context.

Message-ID: <20200811084548.GW3982@worktop.programming.kicks-ass.net>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] MAINTAINERS: Add git tree for KVM/mips
##### From: Tiezhu Yang <yangtiezhu@loongson.cn>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiezhu Yang <yangtiezhu@loongson.cn>
X-Patchwork-Id: 11709953
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF8301392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 01:32:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D15D921744
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 01:32:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726705AbgHLBcR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 21:32:17 -0400
Received: from mail.loongson.cn ([114.242.206.163]:47554 "EHLO loongson.cn"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726564AbgHLBcP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 21:32:15 -0400
Received: from linux.localdomain (unknown [113.200.148.30])
        by mail.loongson.cn (Coremail) with SMTP id
 AQAAf9Dx392aRjNfgboHAA--.4254S2;
        Wed, 12 Aug 2020 09:32:12 +0800 (CST)
From: Tiezhu Yang <yangtiezhu@loongson.cn>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>
Cc: kvm@vger.kernel.org, linux-mips@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] MAINTAINERS: Add git tree for KVM/mips
Date: Wed, 12 Aug 2020 09:32:10 +0800
Message-Id: <1597195930-13613-1-git-send-email-yangtiezhu@loongson.cn>
X-Mailer: git-send-email 2.1.0
X-CM-TRANSID: AQAAf9Dx392aRjNfgboHAA--.4254S2
X-Coremail-Antispam: 1UD129KBjvdXoWrCr1UKr45Xr1DAryxZF43Wrg_yoWxXFb_CF
        47JayxWryrGrZrA3yvg3ZrKFyFq3y8JF93Z3ZFqwsFyas8tryYqrZFy3s7C34DCr4kCrWD
        Xay3Jwna9r43WjkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUIcSsGvfJTRUUUb2xYjsxI4VWxJwAYFVCjjxCrM7AC8VAFwI0_Jr0_Gr1l1xkIjI8I
        6I8E6xAIw20EY4v20xvaj40_Wr0E3s1l1IIY67AEw4v_Jr0_Jr4l8cAvFVAK0II2c7xJM2
        8CjxkF64kEwVA0rcxSw2x7M28EF7xvwVC0I7IYx2IY67AKxVW5JVW7JwA2z4x0Y4vE2Ix0
        cI8IcVCY1x0267AKxVWxJVW8Jr1l84ACjcxK6I8E87Iv67AKxVWxJVW8Jr1l84ACjcxK6I
        8E87Iv6xkF7I0E14v26r4UJVWxJr1le2I262IYc4CY6c8Ij28IcVAaY2xG8wAqx4xG64xv
        F2IEw4CE5I8CrVC2j2WlYx0E2Ix0cI8IcVAFwI0_Jrv_JF1lYx0Ex4A2jsIE14v26r1j6r
        4UMcvjeVCFs4IE7xkEbVWUJVW8JwACjcxG0xvY0x0EwIxGrwCY02Avz4vE14v_KwCF04k2
        0xvY0x0EwIxGrwCFx2IqxVCFs4IE7xkEbVWUJVW8JwC20s026c02F40E14v26r1j6r18MI
        8I3I0E7480Y4vE14v26r106r1rMI8E67AF67kF1VAFwI0_JF0_Jw1lIxkGc2Ij64vIr41l
        IxAIcVC0I7IYx2IY67AKxVWUJVWUCwCI42IY6xIIjxv20xvEc7CjxVAFwI0_Jr0_Gr1lIx
        AIcVCF04k26cxKx2IYs7xG6rW3Jr0E3s1lIxAIcVC2z280aVAFwI0_Jr0_Gr1lIxAIcVC2
        z280aVCY1x0267AKxVWUJVW8JbIYCTnIWIevJa73UjIFyTuYvjxU2lksDUUUU
X-CM-SenderInfo: p1dqw3xlh2x3gn0dqz5rrqw2lrqou0/
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is no git tree for KVM/mips in MAINTAINERS, it is not
convinent to rebase, add it.

Signed-off-by: Tiezhu Yang <yangtiezhu@loongson.cn>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] PCI: Introduce flag for detached virtual functions
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11710927
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EB1E109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 14:50:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63C3C20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 14:50:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="teV8h0Us"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726587AbgHLOuf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 10:50:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:46048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726503AbgHLOuc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 12 Aug 2020 10:50:32 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07CEX1S6118587;
        Wed, 12 Aug 2020 10:50:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=039f5qc7xIoBm0mLLd+ro4GakzTvU9FxjbxkKBFcWq4=;
 b=teV8h0UsYdgI4HNEedRDJddNbNxikRFFtFF1M5i2xyRxVt6mEvLDz9Q/YvHi72wCefM4
 zqVl+phDonHFY2H2vYMLaqiJ3sC8lXXi+ZwMTZOQbib64TntlGcvpPgVtA/kNsrREz8Z
 PBM/wM5IQm4t9QOLUb/FOqPwbha3meQQOElTsmdH5BXNA6EXuqjXc/Gg+1v0y6AI5DAR
 XkC3eTio3DiVpvnZBFEFZbrBlkUo/oDsDLuKmg3bRgYnck08eiFhAxfDFzn7LL4uDMQZ
 orBbQM5OPzuCLmnAGAdTc5fTvHytyN+f9mEjgwhmAYU6T0X/V6+Bq4593f4/Sif6NK97 WA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32utn91asb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 10:50:30 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07CEX9pq119294;
        Wed, 12 Aug 2020 10:50:29 -0400
Received: from ppma03dal.us.ibm.com (b.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.11])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32utn91arj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 10:50:29 -0400
Received: from pps.filterd (ppma03dal.us.ibm.com [127.0.0.1])
        by ppma03dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07CEjJVg011139;
        Wed, 12 Aug 2020 14:50:28 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma03dal.us.ibm.com with ESMTP id 32skp9awwv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 14:50:28 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 07CEoR6K42795350
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 Aug 2020 14:50:27 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B978228058;
        Wed, 12 Aug 2020 14:50:27 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4723828064;
        Wed, 12 Aug 2020 14:50:25 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.7.238])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed, 12 Aug 2020 14:50:24 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-pci@vger.kernel.org
Subject: [PATCH] PCI: Introduce flag for detached virtual functions
Date: Wed, 12 Aug 2020 10:50:17 -0400
Message-Id: <1597243817-3468-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1597243817-3468-1-git-send-email-mjrosato@linux.ibm.com>
References: <1597243817-3468-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-12_06:2020-08-11,2020-08-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 malwarescore=0 bulkscore=0 mlxscore=0 suspectscore=0 mlxlogscore=999
 clxscore=1015 impostorscore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008120104
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s390x has the notion of providing VFs to the kernel in a manner
where the associated PF is inaccessible other than via firmware.
These are not treated as typical VFs and access to them is emulated
by underlying firmware which can still access the PF.  After
abafbc55 however these detached VFs were no longer able to work
with vfio-pci as the firmware does not provide emulation of the
PCI_COMMAND_MEMORY bit.  In this case, let's explicitly recognize
these detached VFs so that vfio-pci can allow memory access to
them again.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Niklas Schnelle <schnelle@linux.ibm.com>
---
 arch/s390/pci/pci.c                | 8 ++++++++
 drivers/vfio/pci/vfio_pci_config.c | 3 ++-
 include/linux/pci.h                | 1 +
 3 files changed, 11 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests RFC v2 1/4] common.bash: run `cmd` only if a test case was found
##### From: Marc Hartmayer <mhartmay@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Hartmayer <mhartmay@linux.ibm.com>
X-Patchwork-Id: 11710527
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E912516B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 09:27:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CE91D20885
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 09:27:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Oe74AEmg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726722AbgHLJ1V (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 05:27:21 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:48194 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726962AbgHLJ1U (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 12 Aug 2020 05:27:20 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07C94OEN060825;
        Wed, 12 Aug 2020 05:27:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=0acSJCr1o0RQcfcNtXQDeitKyCbzJCGqJk1XWIvSBuQ=;
 b=Oe74AEmgEYBjZZMrrkOQ82qJILQ0iZnUXsKA6/+/Fdl1jOOGzyGvH50v/D+u/W6j43tV
 NityKHqCaYFBY5IgYHyiy1AW+BcYbqsaJriyRHQktcS+DIJVxSbiOPApv2stBT0kj2p/
 ZWO1L6Ki4meSmeQeefDlFfJoeLs8o245Md/weOHHBBouiPRsV3/glnKNdKmK30IWsS0U
 GSRaYYEJlWuFqoJPo46Mxz3qXaP3UIPtubEWxfwCI8CYguErIGNKMmlD3V3RkLKd6RrN
 jpgamP6GN5C8hBsDkk8mvONqMiroyUL4EJtrbAD/gObM4sZuTloUGekiHWtJMFqGmMXu bQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32utn8r23m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 05:27:20 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07C94WSS061446;
        Wed, 12 Aug 2020 05:27:19 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32utn8r232-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 05:27:19 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07C9LL7M032034;
        Wed, 12 Aug 2020 09:27:17 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma02fra.de.ibm.com with ESMTP id 32skp7tmea-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 09:27:17 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07C9REpY31195392
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 Aug 2020 09:27:14 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2690652052;
        Wed, 12 Aug 2020 09:27:14 +0000 (GMT)
Received: from marcibm.ibmuc.com (unknown [9.145.75.196])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id BB5085204F;
        Wed, 12 Aug 2020 09:27:13 +0000 (GMT)
From: Marc Hartmayer <mhartmay@linux.ibm.com>
To: <kvm@vger.kernel.org>
Cc: Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390@vger.kernel.org
Subject: [kvm-unit-tests RFC v2 1/4] common.bash: run `cmd` only if a test
 case was found
Date: Wed, 12 Aug 2020 11:27:02 +0200
Message-Id: <20200812092705.17774-2-mhartmay@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200812092705.17774-1-mhartmay@linux.ibm.com>
References: <20200812092705.17774-1-mhartmay@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-12_02:2020-08-11,2020-08-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 malwarescore=0 bulkscore=0 mlxscore=0 suspectscore=1 mlxlogscore=999
 clxscore=1015 impostorscore=0 priorityscore=1501 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008120064
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's only useful to run `cmd` in `for_each_unittest` if a test case
was found. This change allows us to remove the guards from the
functions `run_task` and `mkstandalone`.

Signed-off-by: Marc Hartmayer <mhartmay@linux.ibm.com>
---
 run_tests.sh            | 3 ---
 scripts/common.bash     | 8 ++++++--
 scripts/mkstandalone.sh | 4 ----
 3 files changed, 6 insertions(+), 9 deletions(-)

```
#### [PATCH v2 1/2] KVM: LAPIC: Return 0 when getting the tscdeadline timer if the lapic is hw disabled
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11710273
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95C4013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 06:31:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7047120768
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 06:31:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="la9ApehZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726718AbgHLGa5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 02:30:57 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57556 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726255AbgHLGa4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 02:30:56 -0400
Received: from mail-pl1-x643.google.com (mail-pl1-x643.google.com
 [IPv6:2607:f8b0:4864:20::643])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 84F93C06174A;
        Tue, 11 Aug 2020 23:30:56 -0700 (PDT)
Received: by mail-pl1-x643.google.com with SMTP id x15so633159plr.11;
        Tue, 11 Aug 2020 23:30:56 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=RZ3wedaw2pbYbDAfBKRfeJcZf90FJkT5dw1w3ok5Pjo=;
        b=la9ApehZUj8QpjB8DNp2LZ8oh/Ftor/yarN8eTh/oOZLMZGVTMtuTthMVo3Wq+H6kV
         GJwpfLM1Vkmq0aUotJn3WdTP/a1oocJa6Y4ZqhjFCETAYwEWVc1q3en+nFmt3IwZVXn1
         Qy6ACeGO+IROY1zslFKC0RkqvV6BgxeP3CEx4b5oAwVhhg+C3TVV+lCSVTSR0A70/QQI
         Sda7aq9f7nKARLqf/LiUDj84R2Iegn0y9ahFDNsobKl9So76il083ycfaaw/bPkyeiQy
         U8xuOSHHa+VkT7msSVPYIS/+Pql3hKFm+/HaIUKAW/mCakfAQqIH0JOXO+jdtYypB+Zp
         hQ7A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=RZ3wedaw2pbYbDAfBKRfeJcZf90FJkT5dw1w3ok5Pjo=;
        b=iLI84nKrFvjTiaRyuz9xtFkqYAF96fDmugdF6ITtctZE7tdx8HgTL0zbbAA9Na2pjP
         jJAMcWqHijhRCQPErQ6OmQvN7nu3KodcPwPBn5mWdYhkN5XU0icY2qq47T1oLQu/iZnO
         SNb7VRPCYvVcOIlaWxx5wmH6S4fl96V4uRD8QfY8lGZykeflpyz/V5xY8UjetM+fJlpd
         sWhtpyjZGxkBj4qFY/q7/Z1NbXIUiy/u1fD+ISL5pQ49t0otY4mvqGaYWcfGTGSybkqZ
         VkpY5mMDsCu6FP4Pd+dnwB7ICAMJJB7Fl3e2CYtYy7GlHSTz8CMkP/2gYAjTeC4Z/Uve
         G7Tw==
X-Gm-Message-State: AOAM533MQPFIJlq+g6quLCqVWEDa3Rf9KYWPMfKMA7mtr9FqKt+6S4P8
        YMJYKmGf+UBkxLaOf9OZyp+0ie4r
X-Google-Smtp-Source: 
 ABdhPJz2GTHROF746HCvaeRI/8TLGO0W+B7VK9k45cU+invz7Ps5RNo40/3liUZ3jGZWrViTACDiVg==
X-Received: by 2002:a17:902:bb82:: with SMTP id
 m2mr4034745pls.115.1597213854302;
        Tue, 11 Aug 2020 23:30:54 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 x20sm11117344pjp.3.2020.08.11.23.30.51
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Aug 2020 23:30:53 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 1/2] KVM: LAPIC: Return 0 when getting the tscdeadline
 timer if the lapic is hw disabled
Date: Wed, 12 Aug 2020 14:30:37 +0800
Message-Id: <1597213838-8847-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Return 0 when getting the tscdeadline timer if the lapic is hw disabled.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * fix indentation

 arch/x86/kvm/lapic.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2] PCI: Introduce flag for detached virtual functions
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11711197
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA240618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:21:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A205D20866
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 19:21:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Umr09MIS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726557AbgHLTVZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 15:21:25 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:42188 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726456AbgHLTVY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 12 Aug 2020 15:21:24 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07CJ7cf1102659;
        Wed, 12 Aug 2020 15:21:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=enACx+8V/NyPPGSVz771wzSV3YvsTDMU6YtG7K9pLkY=;
 b=Umr09MISMUYe4OKfL+/Z4+rzGP/2acwSoJ9/hDxEPXevBB4FW3+BrpFCXwglnqzJ+6vC
 VrXS2HxkH2Uec/lL48F3xm32XzlCxQ1ILczUYpJuMsM6foLCYdmJmrw8d4dH7fuh931Y
 2ptkTUyHAjHkTiOskxzs86ZAjG2aybWqH/XjHvM2Mu7r1j0Dv8MBKk9BlloDRLQcTObU
 MXR3BlXewuw5C0JvtOEy79+YIjho8sMieqAatPgP+W65HOOtXhqZHJGQX4tT/twqAlu/
 rk9/1chhjDGIHdQScl7fesnw/AthUW2QwAv4amhyqvSHzttGnvs6KO8OHqA8fdJTQ9Pz OA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32v7v0fmq5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 15:21:19 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07CJAC4P111835;
        Wed, 12 Aug 2020 15:21:18 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32v7v0fmpj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 15:21:18 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07CJ5xH6029333;
        Wed, 12 Aug 2020 19:21:18 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma03wdc.us.ibm.com with ESMTP id 32skp9by9q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 12 Aug 2020 19:21:17 +0000
Received: from b03ledav003.gho.boulder.ibm.com
 (b03ledav003.gho.boulder.ibm.com [9.17.130.234])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07CJLEur29098742
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 Aug 2020 19:21:14 GMT
Received: from b03ledav003.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 925206A04D;
        Wed, 12 Aug 2020 19:21:16 +0000 (GMT)
Received: from b03ledav003.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7950E6A047;
        Wed, 12 Aug 2020 19:21:15 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.7.238])
        by b03ledav003.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed, 12 Aug 2020 19:21:15 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, bhelgaas@google.com
Cc: schnelle@linux.ibm.com, pmorel@linux.ibm.com, mpe@ellerman.id.au,
        oohall@gmail.com, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-pci@vger.kernel.org
Subject: [PATCH v2] PCI: Introduce flag for detached virtual functions
Date: Wed, 12 Aug 2020 15:21:11 -0400
Message-Id: <1597260071-2219-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1597260071-2219-1-git-send-email-mjrosato@linux.ibm.com>
References: <1597260071-2219-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-12_15:2020-08-11,2020-08-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 bulkscore=0
 priorityscore=1501 malwarescore=0 suspectscore=0 mlxscore=0
 impostorscore=0 lowpriorityscore=0 spamscore=0 mlxlogscore=999
 phishscore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008120117
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

s390x has the notion of providing VFs to the kernel in a manner
where the associated PF is inaccessible other than via firmware.
These are not treated as typical VFs and access to them is emulated
by underlying firmware which can still access the PF.  After
abafbc55 however these detached VFs were no longer able to work
with vfio-pci as the firmware does not provide emulation of the
PCI_COMMAND_MEMORY bit.  In this case, let's explicitly recognize
these detached VFs so that vfio-pci can allow memory access to
them again.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 arch/s390/pci/pci.c                |  8 ++++++++
 drivers/vfio/pci/vfio_pci_config.c | 11 +++++++----
 include/linux/pci.h                |  1 +
 3 files changed, 16 insertions(+), 4 deletions(-)

```
#### [PATCH v3] nSVM: Test illegal combinations of EFER.LME, CR0.PG, CR0.PE and CR4.PAE in VMCB
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11709861
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1384618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 00:29:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA0722087C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 00:29:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="P17Iv2Wv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726750AbgHLA3s (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Aug 2020 20:29:48 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:42216 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726485AbgHLA3r (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Aug 2020 20:29:47 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07C0Ih45003408;
        Wed, 12 Aug 2020 00:29:45 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=n4dbQ/XCFjZvEExTUPt6UpTRlkMau3E9UKnX9elN3PA=;
 b=P17Iv2WvuGXtKKGLwSPxIOtXNtloM0TIRkFFOvEsCGOn2QP5x1sMtxXaHJo+Ohyb3TX7
 xZePM+7e3bzbSb+HbGt/oYJOZ1ihsBnuVJGQCMDRMS5cdYq0tIV+WTgXW8PTudtMTmVD
 qpvETtSGtZGbSqENI1Gpu/SpqEfRm9XNmZi1rP8qkA4luuWZximdZpgRzuMl5DzOiIqN
 P6o4VcDdsevmE1CJF0c7nYaZ3pJbXlyH0J5FfPBCdccZtYje0x4nkaH9HDVtgSECPr2d
 puDHBWmUWnkd19qBFJiyJBpIjjmVlqzU0kugjAHyBHcWV0zeao3rcgWZmfKMlPKFj3wP TQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 32t2ydp66g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 12 Aug 2020 00:29:44 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07C0DJ05131199;
        Wed, 12 Aug 2020 00:29:44 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 32t5y5cnbq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 12 Aug 2020 00:29:44 +0000
Received: from abhmp0006.oracle.com (abhmp0006.oracle.com [141.146.116.12])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 07C0Tgnp026388;
        Wed, 12 Aug 2020 00:29:43 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 12 Aug 2020 00:29:42 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH v3] nSVM: Test illegal combinations of EFER.LME, CR0.PG,
 CR0.PE and CR4.PAE in VMCB
Date: Wed, 12 Aug 2020 00:29:35 +0000
Message-Id: <20200812002935.48365-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200812002935.48365-1-krish.sadhukhan@oracle.com>
References: <20200812002935.48365-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9710
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 malwarescore=0
 suspectscore=1 mlxscore=0 adultscore=0 bulkscore=0 phishscore=0
 mlxlogscore=852 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008120000
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9710
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=834
 priorityscore=1501
 malwarescore=0 impostorscore=0 lowpriorityscore=0 mlxscore=0 bulkscore=0
 suspectscore=1 phishscore=0 adultscore=0 spamscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008120000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol. 2
the following guest state combinations are illegal:

	* EFER.LME and CR0.PG are both set and CR4.PAE is zero.
	* EFER.LME and CR0.PG are both non-zero and CR0.PE is zero.
	* EFER.LME, CR0.PG, CR4.PAE, CS.L, and CS.D are all non-zero

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/svm_tests.c | 44 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

```
#### [PATCH v2 2/2] KVM: LAPIC: Guarantee the timer is in tsc-deadline mode when setting
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11710275
Return-Path: <SRS0=6x24=BW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AEE531744
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 06:31:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9306620781
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 12 Aug 2020 06:31:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="McWIxxwy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726784AbgHLGa6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Aug 2020 02:30:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57562 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726255AbgHLGa5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Aug 2020 02:30:57 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7026CC06174A;
        Tue, 11 Aug 2020 23:30:57 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id d19so507812pgl.10;
        Tue, 11 Aug 2020 23:30:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=trdiW9zMK2+IQ+GVd+J+GTCed/wEwFJbqPAdAmO4NQc=;
        b=McWIxxwyUI5ufch4LIkF1S5bg//D2wlzd4FFDVqc5u2EhUYGX4lbN62eBnEo3RwTvQ
         yGnBt/WM2VMSnIf2SDHR1UqFKk2DcTtSHPzVwLlFkF1MUfrkAOYHzlRaNZ579TNhrtbJ
         MWAntXg0ohh5FuEhHgvk1py+VEbAXgLNlvSiFTSovAdvSy7ZurpIaOFOUAaYCN4/hRWu
         TILSkYMlHqSEuiS3CUYBmKSty54GDONwwYzpcOXrhBD57Ey0xXifvCINdkQ1SDRsePAz
         ileZlWUvN0OmCuQqqa1UXtMtgqFVztijFmoXNTvAlSaXRL9K38IJClQwq1iEpGFLmAZO
         1A8w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=trdiW9zMK2+IQ+GVd+J+GTCed/wEwFJbqPAdAmO4NQc=;
        b=I94oniRWatmuKZOnJO70UGoiaWNDZxbtY/qpxYEhWNf/9PfaNvw0pLob/P9k1CQQQt
         QGYhOhHV+lw9a3KznmSDA8+0xikw46ddKIueqBatpoKzMoKmEzQ/9sP+seVB5fxyTZZD
         CtmKF+4mYn52lzR7eqlp2P+QONre1ZxouevOGHQQoDORaaDAm1V3zOsVOmN8PnMftkBj
         LKU9ElgrlVutZ5odvwwlW6oanpxYwgOhHsSLde0Hcc7oQ5M3LyOmO4vTk0muxosgHKtz
         SJiikO2w57Gcw0b7h5Jh/6JSZN6zuicua8iaQvppf/RX3gDUrpXY5Q2xnbbDGWqW3ApK
         7gFA==
X-Gm-Message-State: AOAM533yrbKDb/g/8bLcJXiTDJ84giwcFOB993DBLdC24sKrsqlclrJU
        XekYOuo6ba8PlqfTpnonYD9Ngg6C
X-Google-Smtp-Source: 
 ABdhPJzL/MIq0NLmjZEk0XNv+fYrz44B+SR2oXueWwPzXe3QKuLLUU4KdBQM2nwd+mTArYONg34Tsg==
X-Received: by 2002:a63:e907:: with SMTP id i7mr3952408pgh.210.1597213856848;
        Tue, 11 Aug 2020 23:30:56 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 x20sm11117344pjp.3.2020.08.11.23.30.54
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Aug 2020 23:30:56 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 2/2] KVM: LAPIC: Guarantee the timer is in tsc-deadline
 mode when setting
Date: Wed, 12 Aug 2020 14:30:38 +0800
Message-Id: <1597213838-8847-2-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1597213838-8847-1-git-send-email-wanpengli@tencent.com>
References: <1597213838-8847-1-git-send-email-wanpengli@tencent.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Check apic_lvtt_tscdeadline() mode directly instead of apic_lvtt_oneshot()
and apic_lvtt_period() to guarantee the timer is in tsc-deadline mode when
wrmsr MSR_IA32_TSCDEADLINE.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * fix indentation

 arch/x86/kvm/lapic.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
