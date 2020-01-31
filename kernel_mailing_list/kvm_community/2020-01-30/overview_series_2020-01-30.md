#### [PATCH 01/23] KVM: arm64: Only sign-extend MMIO up to register width
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11357963
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5E6F513B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 13:26:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 322CF2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 13:26:13 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1580390773;
	bh=OhoS0JanLTIxVzTGAKDyNXY3oCD/f0UsDdcPTiRDT8s=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=uOgaj6fnUIT1O/1xaBuxnFFLFto0fQ3qaIFgX3v0+aKwBbw2dq/9wDa7SY0OCI6As
	 41bc1c5hn2KhDyJrYdtw4RPIpRtyupa6SCJ8v/aTTfl4opGqf0W2bT5ulONgDnpw5+
	 FHV+DIUw6sNXw50xVn4m4QN56v89O/nG8UD0xJc0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727272AbgA3N0M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 08:26:12 -0500
Received: from mail.kernel.org ([198.145.29.99]:45542 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727132AbgA3N0L (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 08:26:11 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 16E0D2083E;
        Thu, 30 Jan 2020 13:26:10 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1580390770;
        bh=OhoS0JanLTIxVzTGAKDyNXY3oCD/f0UsDdcPTiRDT8s=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=DdU75f+3ELw66IIp8E7L6aUqnGFFtL1DLdNBC+YFFOG0RzLCAeAotvkuD3NSF+8XR
         J7tIRQKjKc9KOQxY4ifUpi3w+hYHHzLgqQjmYoMsNL5/BD0nstFKpg6KK9OkOcsuOi
         1zCh62cyu52RBFNc/OgDzQpRim4ENzrK262oM2Bg=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1ix9pg-002BmW-Br; Thu, 30 Jan 2020 13:26:08 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Andrew Murray <andrew.murray@arm.com>,
        Beata Michalska <beata.michalska@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Gavin Shan <gshan@redhat.com>,
        Haibin Wang <wanghaibin.wang@huawei.com>,
        James Morse <james.morse@arm.com>,
        Mark Brown <broonie@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Russell King <rmk+kernel@armlinux.org.uk>,
        Shannon Zhao <shannon.zhao@linux.alibaba.com>,
        Steven Price <steven.price@arm.com>,
        Will Deacon <will@kernel.org>,
        YueHaibing <yuehaibing@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, stable@vger.kernel.org
Subject: [PATCH 01/23] KVM: arm64: Only sign-extend MMIO up to register width
Date: Thu, 30 Jan 2020 13:25:36 +0000
Message-Id: <20200130132558.10201-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200130132558.10201-1-maz@kernel.org>
References: <20200130132558.10201-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 drjones@redhat.com, andrew.murray@arm.com, beata.michalska@linaro.org,
 christoffer.dall@arm.com, eric.auger@redhat.com, gshan@redhat.com,
 wanghaibin.wang@huawei.com, james.morse@arm.com, broonie@kernel.org,
 mark.rutland@arm.com, rmk+kernel@armlinux.org.uk,
 shannon.zhao@linux.alibaba.com, steven.price@arm.com, will@kernel.org,
 yuehaibing@huawei.com, yuzenghui@huawei.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christoffer Dall <christoffer.dall@arm.com>

On AArch64 you can do a sign-extended load to either a 32-bit or 64-bit
register, and we should only sign extend the register up to the width of
the register as specified in the operation (by using the 32-bit Wn or
64-bit Xn register specifier).

As it turns out, the architecture provides this decoding information in
the SF ("Sixty-Four" -- how cute...) bit.

Let's take advantage of this with the usual 32-bit/64-bit header file
dance and do the right thing on AArch64 hosts.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Cc: stable@vger.kernel.org
Link: https://lore.kernel.org/r/20191212195055.5541-1-christoffer.dall@arm.com
---
 arch/arm/include/asm/kvm_emulate.h   | 5 +++++
 arch/arm/include/asm/kvm_mmio.h      | 2 ++
 arch/arm64/include/asm/kvm_emulate.h | 5 +++++
 arch/arm64/include/asm/kvm_mmio.h    | 6 ++----
 virt/kvm/arm/mmio.c                  | 6 ++++++
 5 files changed, 20 insertions(+), 4 deletions(-)

```
#### [GIT PULL] First batch of KVM changes for 5.6 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11358543
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CBBFC112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:20:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76C4420CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:20:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="vMV1q8gw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729170AbgA3SUv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 13:20:51 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:40519 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729160AbgA3SUv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 13:20:51 -0500
Received: by mail-wr1-f67.google.com with SMTP id j104so5315680wrj.7;
        Thu, 30 Jan 2020 10:20:48 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=8gwBn7uhDjDgCnfgdECDrqw2ZvqtgNeTVvmwZMgvlPc=;
        b=vMV1q8gwB6bSdcHfKtPFTFUfa0PHxBkOH2TlebnU8E+aMu+xBo37PH8y0QU1wmRhKE
         wC7057dxmrX43polIaUeRnKD3XL6NZItwjvxVKh0twofbBk1RTC0tQ01D/hbs9LCxcP6
         KMu5qL3CEo1kbp7Pdc3kYH824af//RkZ2MzqnVz1XEYkO+zLCA/oKQ1SWE7KHT0vcR9h
         D9iF4XpFsbxTO3QWn6ipOKG9oxUFbg6092Xqj8llsIsQ8PE9Iu7cl95IJwse8otrGS7+
         Y8I1W+PlGya2AuwybLRVQVi6wHFt7wGb1ucxIdoGaUsfEKglst60M7R4RHLxwKubawk7
         LOkw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=8gwBn7uhDjDgCnfgdECDrqw2ZvqtgNeTVvmwZMgvlPc=;
        b=Ip96dO6hu78R9312SphsH1LeXfXCzNjp8Gxa59B+ZbpIgNB/R+su76rsKOwR8HWDqe
         ytSSJeLwto54xdLu93eMPVBgYSclS/++ef4L9nhs2n0itNXTfwCvbJxA2h17LvSSg7nF
         dmOXwdj86A3b2P7E3bzr4MGBuNqQc8Fb9w1XHbZKrW+tGyeBmBHIeQmzZFAP6ODkQHN9
         TLDYaPz6FZBNS0H9ixBFipEc5/pytX572bpwXkH3Rp16TgRFj5/c06OxEHRSmldlhcRi
         RT1RXWtraSeHRzb4OuUfoq6WTbcq5emG3xYe996eL8Afpr/+pVYkSc5g8MsrRY1XPHiX
         CmMQ==
X-Gm-Message-State: APjAAAWUB5VlF2HUlgXJHvVsrf83HMhMDLyhmGEjvbwBr8r5zw3F3+ty
        8WxA85yvgLVDCzJlT9cKerQAnYASXwI=
X-Google-Smtp-Source: 
 APXvYqwQjatAf9f2pIqmCQOoErO3MJ2YsAknqhEbBYamBzFNclbEtjSHD0gncY0CyQe8OSAshKz+DQ==
X-Received: by 2002:a5d:46c7:: with SMTP id g7mr6824729wrs.11.1580408447325;
        Thu, 30 Jan 2020 10:20:47 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 i11sm8288292wrs.10.2020.01.30.10.20.46
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 30 Jan 2020 10:20:46 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] First batch of KVM changes for 5.6 merge window
Date: Thu, 30 Jan 2020 19:20:42 +0100
Message-Id: <1580408442-23916-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit ae6088216ce4b99b3a4aaaccd2eb2dd40d473d42:

  Merge tag 'trace-v5.5-rc5' of git://git.kernel.org/pub/scm/linux/kernel/git/rostedt/linux-trace (2020-01-06 15:38:38 -0800)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/kvm-5.6-1

for you to fetch changes up to 4cbc418a44d5067133271bb6eeac2382f2bf94f7:

  Merge branch 'cve-2019-3016' into kvm-next-5.6 (2020-01-30 18:47:59 +0100)

----------------------------------------------------------------

ARM: Cleanups and corner case fixes

PPC: Bugfixes

x86:
* Support for mapping DAX areas with large nested page table entries.
* Cleanups and bugfixes here too.  A particularly important one is
a fix for FPU load when the thread has TIF_NEED_FPU_LOAD.  There is
also a race condition which could be used in guest userspace to exploit
the guest kernel, for which the embargo expired today.
* Fast path for IPI delivery vmexits, shaving about 200 clock cycles
from IPI latency.
* Protect against "Spectre-v1/L1TF" (bring data in the cache via
speculative out of bound accesses, use L1TF on the sibling hyperthread
to read it), which unfortunately is an even bigger whack-a-mole game
than SpectreV1.

Sean continues his mission to rewrite KVM.  In addition to a sizable
number of x86 patches, this time he contributed a pretty large refactoring
of vCPU creation that affects all architectures but should not have any
visible effect.

s390 will come next week together with some more x86 patches.

----------------------------------------------------------------
Alex Shi (1):
      KVM: remove unused guest_enter

Alexandru Elisei (1):
      KVM: arm64: Treat emulated TVAL TimerValue as a signed 32-bit integer

Andrew Jones (1):
      arm64: KVM: Add UAPI notes for swapped registers

Bharata B Rao (1):
      KVM: PPC: Book3S HV: Release lock on page-out failure path

Boris Ostrovsky (5):
      x86/kvm: Be careful not to clear KVM_VCPU_FLUSH_TLB bit
      x86/kvm: Introduce kvm_(un)map_gfn()
      x86/kvm: Cache gfn to pfn translation
      x86/KVM: Make sure KVM_VCPU_FLUSH_TLB flag is not missed
      x86/KVM: Clean up host's steal time structure

Christoffer Dall (1):
      KVM: arm64: Only sign-extend MMIO up to register width

David Michael (1):
      KVM: PPC: Book3S PR: Fix -Werror=return-type build failure

Eric Auger (5):
      KVM: arm/arm64: vgic-its: Fix restoration of unmapped collections
      KVM: arm64: pmu: Don't increment SW_INCR if PMCR.E is unset
      KVM: arm64: pmu: Don't mark a counter as chained if the odd one is disabled
      KVM: arm64: pmu: Fix chained SW_INCR counters
      KVM: arm64: pmu: Only handle supported event counters

Gavin Shan (2):
      tools/kvm_stat: Fix kvm_exit filter name
      KVM: arm/arm64: Fix young bit from mmu notifier

Haiwei Li (1):
      Adding 'else' to reduce checking.

James Morse (3):
      KVM: arm/arm64: Re-check VMA on detecting a poisoned page
      KVM: arm: Fix DFSR setting for non-LPAE aarch32 guests
      KVM: arm: Make inject_abt32() inject an external abort instead

Jim Mattson (3):
      kvm: nVMX: VMWRITE checks VMCS-link pointer before VMCS field
      kvm: nVMX: VMWRITE checks unsupported field before read-only field
      kvm: nVMX: Aesthetic cleanup of handle_vmread and handle_vmwrite

John Allen (1):
      kvm/svm: PKU not currently supported

Krish Sadhukhan (1):
      KVM: nVMX: Check GUEST_DR7 on vmentry of nested guests

Leonardo Bras (2):
      KVM: PPC: Book3S: Replace current->mm by kvm->mm
      KVM: PPC: Book3E: Replace current->mm by kvm->mm

Marc Zyngier (1):
      KVM: arm/arm64: Cleanup MMIO handling

Marios Pomonis (13):
      KVM: x86: Protect x86_decode_insn from Spectre-v1/L1TF attacks
      KVM: x86: Protect kvm_hv_msr_[get|set]_crash_data() from Spectre-v1/L1TF attacks
      KVM: x86: Refactor picdev_write() to prevent Spectre-v1/L1TF attacks
      KVM: x86: Protect ioapic_read_indirect() from Spectre-v1/L1TF attacks
      KVM: x86: Protect ioapic_write_indirect() from Spectre-v1/L1TF attacks
      KVM: x86: Protect kvm_lapic_reg_write() from Spectre-v1/L1TF attacks
      KVM: x86: Protect MSR-based index computations in fixed_msr_to_seg_unit() from Spectre-v1/L1TF attacks
      KVM: x86: Protect MSR-based index computations in pmu.h from Spectre-v1/L1TF attacks
      KVM: x86: Protect MSR-based index computations from Spectre-v1/L1TF attacks in x86.c
      KVM: x86: Refactor prefix decoding to prevent Spectre-v1/L1TF attacks
      KVM: x86: Protect exit_reason from being used in Spectre-v1/L1TF attacks
      KVM: x86: Protect DR-based index computations from Spectre-v1/L1TF attacks
      KVM: x86: Protect pmu_intel.c from Spectre-v1/L1TF attacks

Mark Brown (1):
      arm64: KVM: Annotate guest entry/exit as a single function

Mark Rutland (3):
      KVM: arm64: Correct PSTATE on exception entry
      KVM: arm/arm64: Correct CPSR on exception entry
      KVM: arm/arm64: Correct AArch32 SPSR on exception entry

Miaohe Lin (19):
      KVM: vmx: remove unreachable statement in vmx_get_msr_feature()
      KVM: get rid of var page in kvm_set_pfn_dirty()
      KVM: explicitly set rmap_head->val to 0 in pte_list_desc_remove_entry()
      KVM: x86: Fix some comment typos
      KVM: lib: use jump label to handle resource release in irq_bypass_register_consumer()
      KVM: lib: use jump label to handle resource release in irq_bypass_register_producer()
      KVM: x86: check kvm_pit outside kvm_vm_ioctl_reinject()
      KVM: Fix some wrong function names in comment
      KVM: Fix some out-dated function names in comment
      KVM: Fix some comment typos and missing parentheses
      KVM: Fix some grammar mistakes
      KVM: hyperv: Fix some typos in vcpu unimpl info
      KVM: Fix some writing mistakes
      KVM: vmx: delete meaningless nested_vmx_prepare_msr_bitmap() declaration
      KVM: nVMX: vmread should not set rflags to specify success in case of #PF
      KVM: x86: avoid clearing pending exception event twice
      KVM: apic: short-circuit kvm_apic_accept_pic_intr() when pic intr is accepted
      KVM: VMX: remove duplicated segment cache clear
      KVM: X86: Add 'else' to unify fastop and execute call path

Milan Pandurov (1):
      kvm: Refactor handling of VM debugfs files

Oliver Upton (1):
      KVM: nVMX: WARN on failure to set IA32_PERF_GLOBAL_CTRL

Paolo Bonzini (11):
      KVM: x86: use CPUID to locate host page table reserved bits
      KVM: x86: fix overlap between SPTE_MMIO_MASK and generation
      KVM: x86: list MSR_IA32_UCODE_REV as an emulated MSR
      KVM: async_pf: drop kvm_arch_async_page_present wrappers
      KVM: x86: avoid incorrect writes to host MSR_IA32_SPEC_CTRL
      Revert "KVM: x86: Add a WARN on TIF_NEED_FPU_LOAD in kvm_load_guest_fpu()"
      KVM: Move running VCPU from ARM to common code
      KVM: x86: inline memslot_valid_for_gpte
      Merge tag 'kvmarm-5.6' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      Merge tag 'kvm-ppc-next-5.6-2' of git://git.kernel.org/.../paulus/powerpc into HEAD
      Merge branch 'cve-2019-3016' into kvm-next-5.6

Peng Hao (1):
      kvm/x86: export kvm_vector_hashing_enabled() is unnecessary

Peter Xu (10):
      KVM: X86: Fix kvm_bitmap_or_dest_vcpus() to use irq shorthand
      KVM: X86: Move irrelevant declarations out of ioapic.h
      KVM: X86: Use APIC_DEST_* macros properly in kvm_lapic_irq.dest_mode
      KVM: X86: Drop KVM_APIC_SHORT_MASK and KVM_APIC_DEST_MASK
      KVM: X86: Fix callers of kvm_apic_match_dest() to use correct macros
      KVM: X86: Convert the last users of "shorthand = 0" to use macros
      KVM: Remove kvm_read_guest_atomic()
      KVM: Add build-time error check on kvm_run size
      KVM: X86: Don't take srcu lock in init_rmode_identity_map()
      KVM: X86: Drop x86_set_memory_region()

Russell King (1):
      arm64: kvm: Fix IDMAP overlap with HYP VA

Sean Christopherson (100):
      KVM: x86: Fix potential put_fpu() w/o load_fpu() on MPX platform
      KVM: x86: Add a WARN on TIF_NEED_FPU_LOAD in kvm_load_guest_fpu()
      KVM: x86: Use gpa_t for cr2/gpa to fix TDP support on 32-bit KVM
      KVM: x86/mmu: Move definition of make_mmu_pages_available() up
      KVM: x86/mmu: Fold nonpaging_map() into nonpaging_page_fault()
      KVM: x86/mmu: Move nonpaging_page_fault() below try_async_pf()
      KVM: x86/mmu: Refactor handling of cache consistency with TDP
      KVM: x86/mmu: Refactor the per-slot level calculation in mapping_level()
      KVM: x86/mmu: Refactor handling of forced 4k pages in page faults
      KVM: x86/mmu: Incorporate guest's page level into max level for shadow MMU
      KVM: x86/mmu: Persist gfn_lpage_is_disallowed() to max_level
      KVM: x86/mmu: Rename lpage_disallowed to account_disallowed_nx_lpage
      KVM: x86/mmu: Consolidate tdp_page_fault() and nonpaging_page_fault()
      KVM: x86/mmu: Move transparent_hugepage_adjust() above __direct_map()
      KVM: x86/mmu: Move calls to thp_adjust() down a level
      KVM: x86/mmu: Move root_hpa validity checks to top of page fault handler
      KVM: x86/mmu: WARN on an invalid root_hpa
      KVM: x86/mmu: WARN if root_hpa is invalid when handling a page fault
      KVM: VMX: Add non-canonical check on writes to RTIT address MSRs
      KVM: VMX: Add helper to consolidate up PT/RTIT WRMSR fault logic
      KVM: x86: Don't let userspace set host-reserved cr4 bits
      KVM: x86: Ensure all logical CPUs have consistent reserved cr4 bits
      KVM: x86: Drop special XSAVE handling from guest_cpuid_has()
      KVM: x86: Add macro to ensure reserved cr4 bits checks stay in sync
      KVM: x86: Add dedicated emulator helpers for querying CPUID features
      KVM: x86: Move bit() helper to cpuid.h
      KVM: x86: Add CPUID_7_1_EAX to the reverse CPUID table
      KVM: x86: Expand build-time assertion on reverse CPUID usage
      KVM: x86: Refactor and rename bit() to feature_bit() macro
      KVM: x86/mmu: Reorder the reserved bit check in prefetch_invalid_gpte()
      KVM: x86/mmu: Micro-optimize nEPT's bad memptype/XWR checks
      KVM: x86/mmu: Apply max PA check for MMIO sptes to 32-bit KVM
      KVM: PPC: Book3S HV: Uninit vCPU if vcore creation fails
      KVM: PPC: Book3S PR: Free shared page if mmu initialization fails
      KVM: x86: Free wbinvd_dirty_mask if vCPU creation fails
      KVM: VMX: Allocate VPID after initializing VCPU
      KVM: VMX: Use direct vcpu pointer during vCPU create/free
      KVM: SVM: Use direct vcpu pointer during vCPU create/free
      KVM: x86: Allocate vcpu struct in common x86 code
      KVM: x86: Move FPU allocation to common x86 code
      KVM: x86: Move allocation of pio_data page down a few lines
      KVM: x86: Move kvm_vcpu_init() invocation to common code
      KVM: PPC: e500mc: Add build-time assert that vcpu is at offset 0
      KVM: PPC: Allocate vcpu struct in common PPC code
      KVM: PPC: Book3S PR: Allocate book3s and shadow vcpu after common init
      KVM: PPC: e500mc: Move reset of oldpir below call to kvm_vcpu_init()
      KVM: PPC: Move kvm_vcpu_init() invocation to common code
      KVM: MIPS: Use kvm_vcpu_cache to allocate vCPUs
      KVM: MIPS: Drop kvm_arch_vcpu_free()
      KVM: PPC: Drop kvm_arch_vcpu_free()
      KVM: arm: Drop kvm_arch_vcpu_free()
      KVM: x86: Remove spurious kvm_mmu_unload() from vcpu destruction path
      KVM: x86: Remove spurious clearing of async #PF MSR
      KVM: x86: Drop kvm_arch_vcpu_free()
      KVM: Remove kvm_arch_vcpu_free() declaration
      KVM: Add kvm_arch_vcpu_precreate() to handle pre-allocation issues
      KVM: s390: Move guts of kvm_arch_vcpu_init() into kvm_arch_vcpu_create()
      KVM: s390: Invoke kvm_vcpu_init() before allocating sie_page
      KVM: MIPS: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
      KVM: x86: Invoke kvm_vcpu_uninit() immediately prior to freeing vcpu
      KVM: Introduce kvm_vcpu_destroy()
      KVM: Move vcpu alloc and init invocation to common code
      KVM: Unexport kvm_vcpu_cache and kvm_vcpu_{un}init()
      KVM: Move initialization of preempt notifier to kvm_vcpu_init()
      KVM: x86: Move guts of kvm_arch_vcpu_setup() into kvm_arch_vcpu_create()
      KVM: MIPS: Move .vcpu_setup() call to kvm_arch_vcpu_create()
      KVM: s390: Manually invoke vcpu setup during kvm_arch_vcpu_create()
      KVM: PPC: BookE: Setup vcpu during kvmppc_core_vcpu_create()
      KVM: Drop kvm_arch_vcpu_setup()
      KVM: x86: Move all vcpu init code into kvm_arch_vcpu_create()
      KVM: MIPS: Move all vcpu init code into kvm_arch_vcpu_create()
      KVM: ARM: Move all vcpu init code into kvm_arch_vcpu_create()
      KVM: PPC: Move all vcpu init code into kvm_arch_vcpu_create()
      KVM: arm64: Free sve_state via arm specific hook
      KVM: Drop kvm_arch_vcpu_init() and kvm_arch_vcpu_uninit()
      KVM: Move putting of vcpu->pid to kvm_vcpu_destroy()
      KVM: Move vcpu->run page allocation out of kvm_vcpu_init()
      KVM: x86: Handle TIF_NEED_FPU_LOAD in kvm_{load,put}_guest_fpu()
      KVM: x86: Ensure guest's FPU state is loaded when accessing for emulation
      KVM: x86: Revert "KVM: X86: Fix fpu state crash in kvm guest"
      KVM: x86: Remove unused ctxt param from emulator's FPU accessors
      KVM: x86: Perform non-canonical checks in 32-bit KVM
      KVM: Check for a bad hva before dropping into the ghc slow path
      KVM: Clean up __kvm_gfn_to_hva_cache_init() and its callers
      KVM: Return immediately if __kvm_gfn_to_hva_cache_init() fails
      KVM: x86/mmu: Enforce max_level on HugeTLB mappings
      mm: thp: KVM: Explicitly check for THP when populating secondary MMU
      KVM: Use vcpu-specific gva->hva translation when querying host page size
      KVM: Play nice with read-only memslots when querying host page size
      x86/mm: Introduce lookup_address_in_mm()
      KVM: x86/mmu: Refactor THP adjust to prep for changing query
      KVM: x86/mmu: Walk host page tables to find THP mappings
      KVM: x86/mmu: Drop level optimization from fast_page_fault()
      KVM: x86/mmu: Rely on host page tables to find HugeTLB mappings
      KVM: x86/mmu: Remove obsolete gfn restoration in FNAME(fetch)
      KVM: x86/mmu: Zap any compound page when collapsing sptes
      KVM: x86/mmu: Fold max_mapping_level() into kvm_mmu_hugepage_adjust()
      KVM: x86/mmu: Remove lpage_is_disallowed() check from set_spte()
      KVM: x86/mmu: Use huge pages for DAX-backed files
      KVM: x86: Use a typedef for fastop functions

Shannon Zhao (1):
      KVM: ARM: Call hyp_cpu_pm_exit at the right place

Sukadev Bhattiprolu (2):
      KVM: PPC: Add skip_page_out parameter to uvmem functions
      KVM: PPC: Book3S HV: Implement H_SVM_INIT_ABORT hcall

Tom Lendacky (1):
      KVM: SVM: Override default MMIO mask if memory encryption is enabled

Vitaly Kuznetsov (1):
      x86/kvm/hyper-v: remove stale evmcs_already_enabled check from nested_enable_evmcs()

Wanpeng Li (2):
      KVM: VMX: FIXED+PHYSICAL mode single target IPI fastpath
      KVM: LAPIC: micro-optimize fixed mode ipi delivery

Xiaoyao Li (3):
      KVM: VMX: Rename INTERRUPT_PENDING to INTERRUPT_WINDOW
      KVM: VMX: Rename NMI_PENDING to NMI_WINDOW
      KVM: VMX: Fix the spelling of CPU_BASED_USE_TSC_OFFSETTING

YueHaibing (1):
      KVM: arm: Remove duplicate include

Zenghui Yu (4):
      KVM: Remove duplicated declaration of kvm_vcpu_kick
      KVM: arm/arm64: vgic: Handle GICR_PENDBASER.PTZ filed as RAZ
      KVM: arm/arm64: vgic-its: Properly check the unmapped coll in DISCARD handler
      KVM: arm/arm64: vgic: Drop the kvm_vgic_register_mmio_region()

zhengbin (1):
      KVM: PPC: Remove set but not used variable 'ra', 'rs', 'rt'

 Documentation/powerpc/ultravisor.rst               |  60 ++
 Documentation/virt/kvm/api.txt                     |   9 +
 arch/arm/include/asm/kvm_emulate.h                 |  27 +-
 arch/arm/include/asm/kvm_host.h                    |  16 +-
 arch/arm/include/asm/kvm_hyp.h                     |   1 +
 arch/arm/include/asm/kvm_mmio.h                    |  26 -
 arch/arm/kvm/guest.c                               |   5 -
 arch/arm64/include/asm/kvm_emulate.h               |  40 +-
 arch/arm64/include/asm/kvm_host.h                  |  16 +-
 arch/arm64/include/asm/kvm_mmio.h                  |  29 -
 arch/arm64/include/asm/ptrace.h                    |   1 +
 arch/arm64/include/uapi/asm/kvm.h                  |  12 +-
 arch/arm64/include/uapi/asm/ptrace.h               |   1 +
 arch/arm64/kvm/guest.c                             |   5 -
 arch/arm64/kvm/hyp/entry.S                         |   7 +-
 arch/arm64/kvm/inject_fault.c                      |  70 ++-
 arch/arm64/kvm/reset.c                             |   2 +-
 arch/arm64/kvm/va_layout.c                         |  56 +-
 arch/mips/kvm/mips.c                               |  84 +--
 arch/powerpc/include/asm/hvcall.h                  |   1 +
 arch/powerpc/include/asm/kvm_book3s_uvmem.h        |  10 +-
 arch/powerpc/include/asm/kvm_host.h                |   1 +
 arch/powerpc/include/asm/kvm_ppc.h                 |   5 +-
 arch/powerpc/kvm/book3s.c                          |   9 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |   4 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |   2 +-
 arch/powerpc/kvm/book3s_64_vio.c                   |  10 +-
 arch/powerpc/kvm/book3s_hv.c                       |  42 +-
 arch/powerpc/kvm/book3s_hv_uvmem.c                 |  34 +-
 arch/powerpc/kvm/book3s_pr.c                       |  34 +-
 arch/powerpc/kvm/book3s_xive_native.c              |   2 +-
 arch/powerpc/kvm/booke.c                           |  67 +--
 arch/powerpc/kvm/e500.c                            |  36 +-
 arch/powerpc/kvm/e500mc.c                          |  30 +-
 arch/powerpc/kvm/emulate_loadstore.c               |   5 -
 arch/powerpc/kvm/powerpc.c                         |  88 +--
 arch/s390/include/asm/kvm_host.h                   |   1 -
 arch/s390/kvm/kvm-s390.c                           | 118 ++--
 arch/x86/include/asm/kvm_emulate.h                 |   4 +
 arch/x86/include/asm/kvm_host.h                    |  34 +-
 arch/x86/include/asm/pgtable_types.h               |   4 +
 arch/x86/include/asm/vmx.h                         |   6 +-
 arch/x86/include/uapi/asm/vmx.h                    |   4 +-
 arch/x86/kvm/cpuid.c                               |   9 +-
 arch/x86/kvm/cpuid.h                               |  45 +-
 arch/x86/kvm/emulate.c                             | 133 +++--
 arch/x86/kvm/hyperv.c                              |  17 +-
 arch/x86/kvm/i8259.c                               |   6 +-
 arch/x86/kvm/ioapic.c                              |  41 +-
 arch/x86/kvm/ioapic.h                              |   6 -
 arch/x86/kvm/irq.h                                 |   3 +
 arch/x86/kvm/irq_comm.c                            |  18 +-
 arch/x86/kvm/lapic.c                               |  37 +-
 arch/x86/kvm/lapic.h                               |   9 +-
 arch/x86/kvm/mmu/mmu.c                             | 605 +++++++++------------
 arch/x86/kvm/mmu/paging_tmpl.h                     |  88 +--
 arch/x86/kvm/mmutrace.h                            |  12 +-
 arch/x86/kvm/mtrr.c                                |   8 +-
 arch/x86/kvm/pmu.h                                 |  18 +-
 arch/x86/kvm/svm.c                                 | 134 +++--
 arch/x86/kvm/vmx/capabilities.h                    |   5 +
 arch/x86/kvm/vmx/evmcs.c                           |   5 -
 arch/x86/kvm/vmx/nested.c                          | 189 +++----
 arch/x86/kvm/vmx/pmu_intel.c                       |  24 +-
 arch/x86/kvm/vmx/vmcs_shadow_fields.h              |   4 +-
 arch/x86/kvm/vmx/vmx.c                             | 294 +++++-----
 arch/x86/kvm/x86.c                                 | 569 +++++++++++--------
 arch/x86/kvm/x86.h                                 |  23 +-
 arch/x86/mm/pageattr.c                             |  11 +
 include/linux/context_tracking.h                   |   9 -
 include/linux/huge_mm.h                            |   6 +
 include/linux/kvm_host.h                           |  40 +-
 include/linux/kvm_types.h                          |   9 +-
 mm/huge_memory.c                                   |  11 +
 tools/arch/x86/include/uapi/asm/vmx.h              |   4 +-
 tools/kvm/kvm_stat/kvm_stat                        |   8 +-
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |   8 +-
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c     |   2 +-
 virt/kvm/arm/aarch32.c                             | 131 ++++-
 virt/kvm/arm/arch_timer.c                          |   5 +-
 virt/kvm/arm/arm.c                                 | 113 +---
 virt/kvm/arm/mmio.c                                |  68 +--
 virt/kvm/arm/mmu.c                                 |  32 +-
 virt/kvm/arm/perf.c                                |   6 +-
 virt/kvm/arm/pmu.c                                 | 114 ++--
 virt/kvm/arm/vgic/vgic-its.c                       |   6 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                   |   5 +-
 virt/kvm/arm/vgic/vgic-mmio.c                      |  15 +-
 virt/kvm/arm/vgic/vgic-mmio.h                      |   5 -
 virt/kvm/async_pf.c                                |  31 +-
 virt/kvm/kvm_main.c                                | 435 +++++++++------
 virt/lib/irqbypass.c                               |  38 +-
 92 files changed, 2387 insertions(+), 2045 deletions(-)
 delete mode 100644 arch/arm/include/asm/kvm_mmio.h
 delete mode 100644 arch/arm64/include/asm/kvm_mmio.h
```
#### [GIT PULL] Please pull my kvm-ppc-next-5.6-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11357317
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6734B14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:54:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4021B2071E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:54:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="UZAkl/nr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726989AbgA3AyU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 19:54:20 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:44895 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726618AbgA3AyU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 19:54:20 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 487MLf4YKhz9sPJ; Thu, 30 Jan 2020 11:54:18 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1580345658; bh=vSwTx+l4dx4nZFxfAd0KlQypvSZiAM/yuxNdihNDKN0=;
        h=Date:From:To:Cc:Subject:From;
        b=UZAkl/nrVwHCXZU2lhHJgb+Shq8vfk0Jw+IKLxpfYVtB7yHlqdygRIOK6PZhAvRHt
         tYhp7IZ693zXEzODNrG8WROm81pAhLFHwc40WQqCey+MbGqMfl+o33Qyza6vYxRP9C
         1njU1hoKP1A0y+47yidwixv2ZjPxVPJltk34GUynJ4L7glpenkuivbQonSu+T5kywO
         z3cNsL0eTJPMOCrLEltaXM53soLoHav0bLEAPUbDOZah4qm8rlUptyxe/t3lriMZPe
         9UjHkbuDehJxVc4/PR46bwBPKN9HbPcRHWjYeUDRUAPDvKgkYHTMqbnk9hkizKyrLI
         s1nsWMOi+jssQ==
Date: Thu, 30 Jan 2020 11:54:16 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.6-2 tag
Message-ID: <20200130005416.GA25802@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

I have a second KVM PPC update for you.  I have added two more commits
which are both one-line fixes.  One is a compile warning fix and the
other fixes a locking error where we could incorrectly leave a mutex
locked when an error occurs.

Thanks,
Paul.

The following changes since commit 3a43970d55e9fd5475d3c4e5fe398ab831ec6c3a:

  KVM: PPC: Book3S HV: Implement H_SVM_INIT_ABORT hcall (2020-01-17 15:08:31 +1100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.6-2

for you to fetch changes up to fd24a8624eb29d3b6b7df68096ce0321b19b03c6:

  KVM: PPC: Book3S PR: Fix -Werror=return-type build failure (2020-01-29 16:47:45 +1100)

----------------------------------------------------------------
Second KVM PPC update for 5.6

* Fix compile warning on 32-bit machines
* Fix locking error in secure VM support

----------------------------------------------------------------
Bharata B Rao (1):
      KVM: PPC: Book3S HV: Release lock on page-out failure path

David Michael (1):
      KVM: PPC: Book3S PR: Fix -Werror=return-type build failure

 arch/powerpc/kvm/book3s_hv_uvmem.c | 2 +-
 arch/powerpc/kvm/book3s_pr.c       | 1 +
 2 files changed, 2 insertions(+), 1 deletion(-)
```
#### [kvm-unit-tests PATCH v2 1/9] arm64: Provide read/write_sysreg_s
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11357739
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A9CB192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:25:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7E875215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:25:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IxK3372j"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727093AbgA3LZb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 06:25:31 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:21941 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726980AbgA3LZb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 06:25:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580383530;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=5QgGQR5lmCzHdU2tw8u26Dp0LVz138MaKuXfv7AyzLc=;
        b=IxK3372jjIT44H9oQ/ZeKfZ4p6iyhzQZ8Xqx9qNkUzoV8DcTqE61E+xVU/0HYRaEamhb7t
        wT10g7wJ8BDrSMlu6p6eT9EuGvjL/BZSUk49uSehAcmwQZ5Wh6l2xGqZnTK2/AjPiRsr8B
        2vpDGLr9d1vQP7OUPovCPSrNyMADw4A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-126-cMBhXBiuMBGb8VIjkEFuNw-1; Thu, 30 Jan 2020 06:25:28 -0500
X-MC-Unique: cMBhXBiuMBGb8VIjkEFuNw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 35C8210054E3;
        Thu, 30 Jan 2020 11:25:27 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 715341001B05;
        Thu, 30 Jan 2020 11:25:22 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v2 1/9] arm64: Provide read/write_sysreg_s
Date: Thu, 30 Jan 2020 12:25:02 +0100
Message-Id: <20200130112510.15154-2-eric.auger@redhat.com>
In-Reply-To: <20200130112510.15154-1-eric.auger@redhat.com>
References: <20200130112510.15154-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Andrew Jones <drjones@redhat.com>

Sometimes we need to test access to system registers which are
missing assembler mnemonics.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 lib/arm64/asm/sysreg.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH 1/5] KVM: Pass kvm_init()'s opaque param to additional arch funcs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11357247
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BB3D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:10:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED8F020716
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:10:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727180AbgA3AK3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 19:10:29 -0500
Received: from mga06.intel.com ([134.134.136.31]:48383 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726750AbgA3AK1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 19:10:27 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 16:10:25 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,379,1574150400";
   d="scan'208";a="261990347"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 29 Jan 2020 16:10:24 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH 1/5] KVM: Pass kvm_init()'s opaque param to additional arch
 funcs
Date: Wed, 29 Jan 2020 16:10:19 -0800
Message-Id: <20200130001023.24339-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200130001023.24339-1-sean.j.christopherson@intel.com>
References: <20200130001023.24339-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Pass @opaque to kvm_arch_hardware_setup() and
kvm_arch_check_processor_compat() to allow architecture specific code to
reference @opaque without having to stash it away in a temporary global
variable.  This will enable x86 to separate its vendor specific callback
ops, which are passed via @opaque, into "init" and "runtime" ops without
having to stash away the "init" ops.

No functional change intended.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/mips/kvm/mips.c       |  4 ++--
 arch/powerpc/kvm/powerpc.c |  4 ++--
 arch/s390/kvm/kvm-s390.c   |  4 ++--
 arch/x86/kvm/x86.c         |  4 ++--
 include/linux/kvm_host.h   |  4 ++--
 virt/kvm/arm/arm.c         |  4 ++--
 virt/kvm/kvm_main.c        | 18 ++++++++++++++----
 7 files changed, 26 insertions(+), 16 deletions(-)

```
#### [PATCH v9 1/6] KVM: s390: do not clobber registers during guest reset/store status
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11357857
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1F05D92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:34:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 07C852083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:34:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727145AbgA3Meu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 07:34:50 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:59216 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726873AbgA3Meu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 07:34:50 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00UCYPfZ044760
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:34:49 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xu5q68jrn-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:34:48 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 30 Jan 2020 12:34:47 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 30 Jan 2020 12:34:45 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00UCYiQe48038074
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 12:34:44 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 234ED52051;
        Thu, 30 Jan 2020 12:34:44 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.44])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id A38FF5204F;
        Thu, 30 Jan 2020 12:34:42 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v9 1/6] KVM: s390: do not clobber registers during guest
 reset/store status
Date: Thu, 30 Jan 2020 07:34:29 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200130123434.68129-1-frankja@linux.ibm.com>
References: <20200130123434.68129-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20013012-0016-0000-0000-000002E2285B
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20013012-0017-0000-0000-00003344F261
Message-Id: <20200130123434.68129-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_03:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 priorityscore=1501 mlxlogscore=880
 clxscore=1015 mlxscore=0 bulkscore=0 spamscore=0 suspectscore=1
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christian Borntraeger <borntraeger@de.ibm.com>

The initial CPU reset clobbers the userspace fpc and the store status
ioctl clobbers the guest acrs + fpr.  As these calls are only done via
ioctl (and not via vcpu_run), no CPU context is loaded, so we can (and
must) act directly on the sync regs, not on the thread context.

Cc: stable@kernel.org
Fixes: e1788bb995be ("KVM: s390: handle floating point registers in the run ioctl not in vcpu_put/load")
Fixes: 31d8b8d41a7e ("KVM: s390: handle access registers in the run ioctl not in vcpu_put/load")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: s390: Cleanup initial cpu reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11357637
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A856913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 09:11:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8EA5E20702
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 09:11:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726909AbgA3JLG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 04:11:06 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:22700 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726882AbgA3JLG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 04:11:06 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00U98ruo069557
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 04:11:05 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xue96r1e0-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 04:11:05 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 30 Jan 2020 09:11:02 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 30 Jan 2020 09:11:00 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00U9AxKj34472068
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 09:10:59 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BBBE94C050;
        Thu, 30 Jan 2020 09:10:59 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CFEA64C040;
        Thu, 30 Jan 2020 09:10:58 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.99.188])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 30 Jan 2020 09:10:58 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH] KVM: s390: Cleanup initial cpu reset
Date: Thu, 30 Jan 2020 04:10:55 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200129200312.3200-1-frankja@linux.ibm.com>
References: <20200129200312.3200-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20013009-0008-0000-0000-0000034E0FDE
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20013009-0009-0000-0000-00004A6E8F79
Message-Id: <20200130091055.1857-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_02:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0
 priorityscore=1501 suspectscore=1 malwarescore=0 spamscore=0 bulkscore=0
 phishscore=0 clxscore=1015 impostorscore=0 mlxlogscore=999 mlxscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300065
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The code seems to be quite old and uses lots of unneeded spaces for
alignment, which doesn't really help with readability.

Let's:
* Get rid of the extra spaces
* Remove the ULs as they are not needed on 0s
* Define constants for the CR 0 and 14 initial values
* Use the sizeof of the gcr array to memset it to 0

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---

I only send out 4 of the 5 patches...

---
 arch/s390/include/asm/kvm_host.h |  5 +++++
 arch/s390/kvm/kvm-s390.c         | 18 +++++++-----------
 2 files changed, 12 insertions(+), 11 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Emulate split-lock access as a write
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11357849
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92E6D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:24:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7968D214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:24:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727170AbgA3MYt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 07:24:49 -0500
Received: from mga07.intel.com ([134.134.136.100]:49436 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726902AbgA3MYs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 07:24:48 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Jan 2020 04:24:48 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,381,1574150400";
   d="scan'208";a="262155251"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by fmsmga002.fm.intel.com with ESMTP; 30 Jan 2020 04:24:46 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, x86@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86: Emulate split-lock access as a write
Date: Thu, 30 Jan 2020 20:19:38 +0800
Message-Id: <20200130121939.22383-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20200130121939.22383-1-xiaoyao.li@intel.com>
References: <20200130121939.22383-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If split lock detect is enabled (warn/fatal), #AC handler calls die()
when split lock happens in kernel.

A sane guest should never tigger emulation on a split-lock access, but
it cannot prevent malicous guest from doing this. So just emulating the
access as a write if it's a split-lock access to avoid malicous guest
polluting the kernel log.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/cpu.h  | 12 ++++++++++++
 arch/x86/kernel/cpu/intel.c | 12 ++++++------
 arch/x86/kvm/x86.c          | 11 +++++++++++
 3 files changed, 29 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests PULL 1/6] s390x: export sclp_setup_int
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11357941
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D67D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 13:11:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7ABAD2082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 13:11:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KtLZKfgh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727165AbgA3NLc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 08:11:32 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26804 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726980AbgA3NLc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 08:11:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580389891;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/yBCkgn6MjP+rp3S4FWnEQM+jVlF/8K3ad/cp5egTrw=;
        b=KtLZKfghbxeu9yEf2W8EW1qp+4KxsYF66/ALAbGYF+56zeOqFZ/KlkyJexdby5ma/5wn6+
        qR7xBGjs38+csg+/qgL5cSp5XqW1hvao5eCrtWT4BxExwYbrF77E1F5oUV07kJ1VEHJqoY
        Z3RR/1M4NxJ4CIFvzzUBiU7bt7kGf2A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-253-4kMBjVA2O5CHeH1LEnes0w-1; Thu, 30 Jan 2020 08:11:28 -0500
X-MC-Unique: 4kMBjVA2O5CHeH1LEnes0w-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 65692800D4E;
        Thu, 30 Jan 2020 13:11:27 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-117-219.ams2.redhat.com [10.36.117.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 41E9677927;
        Thu, 30 Jan 2020 13:11:25 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Huth <thuth@redhat.com>, david@redhat.com,
        Janosch Frank <frankja@linux.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [kvm-unit-tests PULL 1/6] s390x: export sclp_setup_int
Date: Thu, 30 Jan 2020 14:11:11 +0100
Message-Id: <20200130131116.12386-2-david@redhat.com>
In-Reply-To: <20200130131116.12386-1-david@redhat.com>
References: <20200130131116.12386-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Claudio Imbrenda <imbrenda@linux.ibm.com>

Export sclp_setup_int() so that it can be used in tests.

Needed for an upcoming unit test.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Message-Id: <20200120184256.188698-2-imbrenda@linux.ibm.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp.c | 2 +-
 lib/s390x/sclp.h | 1 +
 2 files changed, 2 insertions(+), 1 deletion(-)

```
#### [FYI PATCH 1/5] x86/kvm: Be careful not to clear KVM_VCPU_FLUSH_TLB bit
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11358503
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D238D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:02:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC52A2083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:02:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="gu2kirdO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727718AbgA3SCE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 13:02:04 -0500
Received: from mail-wr1-f67.google.com ([209.85.221.67]:46024 "EHLO
        mail-wr1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727547AbgA3SCD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 13:02:03 -0500
Received: by mail-wr1-f67.google.com with SMTP id a6so5198956wrx.12;
        Thu, 30 Jan 2020 10:02:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=wxAE+rmvrsDq27Iqeo6nEv/48a4RUlHGSm7qdXtegOw=;
        b=gu2kirdOGx8YQhv8sLhotM0mi1J0Qxp5BjsY+pQjI6/ZTbFWCJPndiRPKWm/HDqmLJ
         XrdZ/pum1kE1hsiSoUh/EwOf/XbPnUKFxGxLJ1Dbp+NNYYYBhuqB7vb2BTf+CDy/avLi
         XHyEr141cj3gsW9MYKy5q7JhbjkYtRveUIYo+Fk55BKddNPHSm2u0+kkc+dPi5wMnIhh
         xKrU3B21Uv9NcBZ+nAevzs4JtE7ZljK2Gyx02Ro6oVF6ISuvlsfwjcd+ixxDvnxbmZG9
         i7OJ34QStHDTlibxr38Bj7/0XItrSlEGP6GEweIruQlZGbn/mZxqXTdoOolIQDQ0o6MV
         wcag==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=wxAE+rmvrsDq27Iqeo6nEv/48a4RUlHGSm7qdXtegOw=;
        b=tS1P9AFKY6kFApHdhoQVBE7L4ahgjPz+P+jWTjV2rH+sBUlDlm+8x6vkREvLo2UPTb
         MCva3xpjVHa6ZzttQ2pYjCQExKGmcWU/wqYr5LDcMN1xe2OlcDGMFaA4PX872PIsUJTD
         dPh9AIV+bmfNfGCDkC0Hhzlzlo8hmTX2yvix4DrrqI1FYhHZn0mAzGdYyCn+S835F35w
         VrE3UNbTmKqawDIKC67BC7CchuBjCN7C98praSCfgoiixgI6nkNIu0CF6q3Y0AXZnmDd
         CJsWHDqtHnb3JOQ/bVFrqLG7PN1YF1SlX82LXlg/RwxavYM1U2c/LNvOdV0I1pRzCJjf
         W6Jg==
X-Gm-Message-State: APjAAAX9HVGtSJBGKzTekqsmi+6KD45sMBTsSHaeFakQp5XgkOiKizQV
        o3Pw+8YnHoJHtUjp8mgzFXshWVfPbWw=
X-Google-Smtp-Source: 
 APXvYqwxNN2iCPg7v5ok/gV29ASxuj2urpqlce/yebuWXUT28AiUgavY1YOz82pb/64V0SWdvoCNeA==
X-Received: by 2002:a5d:4c88:: with SMTP id z8mr6804519wrs.395.1580407321318;
        Thu, 30 Jan 2020 10:02:01 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w19sm6956878wmc.22.2020.01.30.10.02.00
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 30 Jan 2020 10:02:00 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        stable@vger.kernel.org
Subject: [FYI PATCH 1/5] x86/kvm: Be careful not to clear KVM_VCPU_FLUSH_TLB
 bit
Date: Thu, 30 Jan 2020 19:01:52 +0100
Message-Id: <1580407316-11391-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1580407316-11391-1-git-send-email-pbonzini@redhat.com>
References: <1580407316-11391-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Boris Ostrovsky <boris.ostrovsky@oracle.com>

kvm_steal_time_set_preempted() may accidentally clear KVM_VCPU_FLUSH_TLB
bit if it is called more than once while VCPU is preempted.

This is part of CVE-2019-3016.

(This bug was also independently discovered by Jim Mattson
<jmattson@google.com>)

Signed-off-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH/FIXUP FOR STABLE BEFORE THIS SERIES] KVM: s390: do not clobber user space fpc during guest reset
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11357629
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15CFD112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 08:55:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F1D232083E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 08:55:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727167AbgA3IzH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 03:55:07 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:34802 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727132AbgA3IzH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 03:55:07 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00U8sfh2025080;
        Thu, 30 Jan 2020 03:55:06 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xttw843wj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 03:55:05 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 00U8t5dq025970;
        Thu, 30 Jan 2020 03:55:05 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xttw843vj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 03:55:05 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 00U8qoYh012061;
        Thu, 30 Jan 2020 08:55:04 GMT
Received: from b01cxnp22035.gho.pok.ibm.com (b01cxnp22035.gho.pok.ibm.com
 [9.57.198.25])
        by ppma02wdc.us.ibm.com with ESMTP id 2xrda72fev-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 08:55:04 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22035.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 00U8t3Dr51118382
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 08:55:03 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CF9C2112064;
        Thu, 30 Jan 2020 08:55:03 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D6C89112065;
        Thu, 30 Jan 2020 08:55:02 +0000 (GMT)
Received: from oc7455500831.ibm.com (unknown [9.152.224.41])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 30 Jan 2020 08:55:02 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: frankja@linux.ibm.com
Cc: borntraeger@de.ibm.com, cohuck@redhat.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org, thuth@redhat.com,
        stable@kernel.org
Subject: [PATCH/FIXUP FOR STABLE BEFORE THIS SERIES] KVM: s390: do not clobber
 user space fpc during guest reset
Date: Thu, 30 Jan 2020 09:55:00 +0100
Message-Id: <1580374500-31247-1-git-send-email-borntraeger@de.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <20200129200312.3200-2-frankja@linux.ibm.com>
References: <20200129200312.3200-2-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_02:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1011 suspectscore=1
 lowpriorityscore=0 adultscore=0 malwarescore=0 phishscore=0
 priorityscore=1501 spamscore=0 mlxlogscore=852 impostorscore=0 bulkscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300063
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The initial CPU reset currently clobbers the userspace fpc. This was an
oversight during a fixup for the lazy fpu reloading rework.  The reset
calls are only done from userspace ioctls. No CPU context is loaded, so
we can (and must) act directly on the sync regs, not on the thread
context. Otherwise the fpu restore call will restore the zeroes fpc to
userspace.

Cc: stable@kernel.org
Fixes: 9abc2a08a7d6 ("KVM: s390: fix memory overwrites when vx is disabled")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2 01/12] scripts/checkpatch.pl: Only allow Python 3 interpreter
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11358389
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A828D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 16:33:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 860B02082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 16:33:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G5SEht04"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727320AbgA3QdQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 11:33:16 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:28521 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727285AbgA3QdQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 11:33:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580401995;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Psv1XrYMRp6/bio5BGEkLgfD58ErvuUMr6pDtw2Fzdk=;
        b=G5SEht04vyACEgCdJnWoJNYNAPs6i2MOU6KbpcXmGpsywEOrW7BhsAUJ2WNx2EJCQK00+P
        4KdSvqo0+ovcpYAZHwStsrjiAmrS7UufCCLhUV9hMhTGoeIKYEnrgGUaPZFbCrp7XEQuln
        nKMVJ/e3+3PujkE5PKchKCbfr+5J9YE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-ndvTu8k8M1myO9PxOaoeMQ-1; Thu, 30 Jan 2020 11:33:00 -0500
X-MC-Unique: ndvTu8k8M1myO9PxOaoeMQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4E899DB63;
        Thu, 30 Jan 2020 16:32:58 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-184.brq.redhat.com [10.40.205.184])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id D6C345DA75;
        Thu, 30 Jan 2020 16:32:47 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>,
 Eduardo Habkost <ehabkost@redhat.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Cleber Rosa <crosa@redhat.com>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>, qemu-block@nongnu.org,
 Stefan Hajnoczi <stefanha@redhat.com>, Juan Quintela <quintela@redhat.com>,
	=?utf-8?q?Daniel_P_=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Michael Roth <mdroth@linux.vnet.ibm.com>, Max Reitz <mreitz@redhat.com>,
 Markus Armbruster <armbru@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Fam Zheng <fam@euphon.net>, Kevin Wolf <kwolf@redhat.com>,
 kvm@vger.kernel.org, John Snow <jsnow@redhat.com>,
 Eric Blake <eblake@redhat.com>, Wei Yang <richardw.yang@linux.intel.com>
Subject: [PATCH v2 01/12] scripts/checkpatch.pl: Only allow Python 3
 interpreter
Date: Thu, 30 Jan 2020 17:32:21 +0100
Message-Id: <20200130163232.10446-2-philmd@redhat.com>
In-Reply-To: <20200130163232.10446-1-philmd@redhat.com>
References: <20200130163232.10446-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit ddf9069963 QEMU requires Python >= 3.5.

PEP 0394 [*] states that 'python3' should be available and
that 'python' is optional.

To avoid problem with unsupported versions, enforce the
shebang interpreter to Python 3.

[*] https://www.python.org/dev/peps/pep-0394/

Reported-by: John Snow <jsnow@redhat.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
Cc: Eric Blake <eblake@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Wei Yang <richardw.yang@linux.intel.com>
---
 scripts/checkpatch.pl | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v2] KVM: s390: do not clobber user space registers during guest reset/store status
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11357801
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6364C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:42:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A2AC214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:42:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727090AbgA3Lml (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 06:42:41 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:22460 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726873AbgA3Lml (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 06:42:41 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00UBeINb033366;
        Thu, 30 Jan 2020 06:42:38 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xtrmcf6x5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 06:42:37 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 00UBebBe034203;
        Thu, 30 Jan 2020 06:42:37 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xtrmcf6wu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 06:42:37 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 00UBarVO004708;
        Thu, 30 Jan 2020 11:42:36 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma02dal.us.ibm.com with ESMTP id 2xrda7693n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 30 Jan 2020 11:42:36 +0000
Received: from b01ledav003.gho.pok.ibm.com (b01ledav003.gho.pok.ibm.com
 [9.57.199.108])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 00UBgami31523144
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 11:42:36 GMT
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ED898B205F;
        Thu, 30 Jan 2020 11:42:35 +0000 (GMT)
Received: from b01ledav003.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F0EE1B2065;
        Thu, 30 Jan 2020 11:42:34 +0000 (GMT)
Received: from oc7455500831.ibm.com (unknown [9.152.224.41])
        by b01ledav003.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 30 Jan 2020 11:42:34 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: borntraeger@de.ibm.com
Cc: cohuck@redhat.com, david@redhat.com, frankja@linux.ibm.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org, stable@kernel.org,
        thuth@redhat.com
Subject: [PATCH v2] KVM: s390: do not clobber user space registers during
 guest reset/store status
Date: Thu, 30 Jan 2020 12:42:32 +0100
Message-Id: <1580384552-7964-1-git-send-email-borntraeger@de.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <7d031d9c-e2f6-73bf-c4d6-6e2753d9102f@de.ibm.com>
References: <7d031d9c-e2f6-73bf-c4d6-6e2753d9102f@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_03:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0
 priorityscore=1501 suspectscore=1 mlxlogscore=766 bulkscore=0
 lowpriorityscore=0 malwarescore=0 clxscore=1015 adultscore=0 spamscore=0
 mlxscore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300086
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The two ioctls for initial CPU reset and store status currently clobber
the userspace fpc and potentially access registers. This was an
oversight during a fixup for the lazy fpu reloading rework.  The reset
calls are only done from userspace ioctls.  No CPU context is loaded, so
we can (and must) act directly on the sync regs, not on the thread
context. Otherwise the fpu restore call will restore the zeroes fpc to
userspace.

Cc: stable@kernel.org
Fixes: e1788bb995be ("KVM: s390: handle floating point registers in the run ioctl not in vcpu_put/load")
Fixes: 31d8b8d41a7e ("KVM: s390: handle access registers in the run ioctl not in vcpu_put/load")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH v9] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11357921
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF76913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:56:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A3465206D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:56:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727290AbgA3M4K (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 07:56:10 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:27148 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727277AbgA3M4K (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 07:56:10 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00UCb9nv109656
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:56:09 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2xtpmu79wf-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:56:08 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 30 Jan 2020 12:56:06 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 30 Jan 2020 12:56:04 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00UCu38X41549988
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 12:56:03 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4C15111C04C;
        Thu, 30 Jan 2020 12:56:03 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B730311C054;
        Thu, 30 Jan 2020 12:56:01 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.44])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 30 Jan 2020 12:56:01 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v9] KVM: s390: Add new reset vcpu API
Date: Thu, 30 Jan 2020 07:55:59 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <9d64917a-2a0a-46e7-0d78-da2f31eb01c4@linux.ibm.com>
References: <9d64917a-2a0a-46e7-0d78-da2f31eb01c4@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20013012-4275-0000-0000-0000039C6BDB
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20013012-4276-0000-0000-000038B0898B
Message-Id: <20200130125559.30032-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_03:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 phishscore=0
 adultscore=0 clxscore=1015 priorityscore=1501 bulkscore=0 spamscore=0
 suspectscore=1 impostorscore=0 malwarescore=0 mlxlogscore=999
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The architecture states that we need to reset local IRQs for all CPU
resets. Because the old reset interface did not support the normal CPU
reset we never did that on a normal reset.

Let's implement an interface for the missing normal and clear resets
and reset all local IRQs, registers and control structures as stated
in the architecture.

Userspace might already reset the registers via the vcpu run struct,
but as we need the interface for the interrupt clearing part anyway,
we implement the resets fully and don't rely on userspace to reset the
rest.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 Documentation/virt/kvm/api.txt | 43 +++++++++++++++++
 arch/s390/kvm/kvm-s390.c       | 86 +++++++++++++++++++++++-----------
 include/uapi/linux/kvm.h       |  5 ++
 3 files changed, 106 insertions(+), 28 deletions(-)

```
