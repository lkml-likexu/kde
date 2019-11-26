#### [PATCH kvmtool 01/16] Makefile: Use correct objcopy binary when cross-compiling for x86_64
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11260107
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 80D9713A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:32:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BCDD2075C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:32:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727541AbfKYKcc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 05:32:32 -0500
Received: from foss.arm.com ([217.140.110.172]:47684 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727316AbfKYKcb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 05:32:31 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3701A55D;
        Mon, 25 Nov 2019 02:32:31 -0800 (PST)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 3D0363F52E;
        Mon, 25 Nov 2019 02:32:30 -0800 (PST)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przywara@arm.com, sami.mujawar@arm.com,
        lorenzo.pieralisi@arm.com
Subject: [PATCH kvmtool 01/16] Makefile: Use correct objcopy binary when
 cross-compiling for x86_64
Date: Mon, 25 Nov 2019 10:30:18 +0000
Message-Id: <20191125103033.22694-2-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191125103033.22694-1-alexandru.elisei@arm.com>
References: <20191125103033.22694-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use the compiler toolchain version of objcopy instead of the native one
when cross-compiling for the x86_64 architecture.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [RFC PATCH v8 1/8] arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11260179
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8EFCA138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:45:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A31020836
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 10:45:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727605AbfKYKpj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 05:45:39 -0500
Received: from foss.arm.com ([217.140.110.172]:48018 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727594AbfKYKpi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 05:45:38 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EC8A855D;
        Mon, 25 Nov 2019 02:45:37 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 56E063F52E;
        Mon, 25 Nov 2019 02:45:32 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com,
        Mark Rutland <mark.rutland@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>
Subject: [RFC PATCH v8 1/8] arm/arm64: smccc/psci: add
 arm_smccc_1_1_get_conduit()
Date: Mon, 25 Nov 2019 18:44:59 +0800
Message-Id: <20191125104506.36850-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191125104506.36850-1-jianyong.wu@arm.com>
References: <20191125104506.36850-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mark Rutland <mark.rutland@arm.com>

SMCCC callers are currently amassing a collection of enums for the SMCCC
conduit, and are having to dig into the PSCI driver's internals in order
to figure out what to do.

Let's clean this up, with common SMCCC_CONDUIT_* definitions, and an
arm_smccc_1_1_get_conduit() helper that abstracts the PSCI driver's
internal state.

We can kill off the PSCI_CONDUIT_* definitions once we've migrated users
over to the new interface.

Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Acked-by: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
Acked-by: Will Deacon <will.deacon@arm.com>
Signed-off-by: Catalin Marinas <catalin.marinas@arm.com>
---
 drivers/firmware/psci/psci.c | 15 +++++++++++++++
 include/linux/arm-smccc.h    | 16 ++++++++++++++++
 2 files changed, 31 insertions(+)

```
#### [GIT PULL] KVM changes for Linux 5.5 merge window
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11260223
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 641D513A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 11:02:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 30DF02084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 11:02:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="h4CxqIQA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727575AbfKYLB5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 06:01:57 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:54572 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727278AbfKYLB4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 06:01:56 -0500
Received: by mail-wm1-f65.google.com with SMTP id b11so5503197wmj.4;
        Mon, 25 Nov 2019 03:01:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gzjggcQb2lcCKNtYyVowVvwKwi39H4SAXOMCebbMiN8=;
        b=h4CxqIQAXZiGpKh3HpmAxHbh1O5brntFvKTxyaUJOngWH3TArVC3I56PLbCJ25Pw1p
         PSA7EZHyk0D72nvim0oUGMRsmPC4/K4x2RwJfnRq8foy9dzeT28ikyR6scLClWJwZCNE
         vzIQLqeCBH4pGpYJPB1+k7AIySBfKZyCrrcNk6MzQeXzZffoUaotiKvHsocjWXBvWasS
         i/i3DZeGrOUsLHfhbI2q9qalb/Js6p0/P3NY3/iAotT2LCy3g1ssy/J+HKb2GgqW162p
         J2kP5w+qR9DajzkrkqmqXv4ND4UoCOhxagE4nvzSyZEJt97TBupwYBRs/udp370tNph0
         dm3Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=gzjggcQb2lcCKNtYyVowVvwKwi39H4SAXOMCebbMiN8=;
        b=HpoXIDx6EqJ9mMe7oGC9a5CxKthu57EFmGP0k/oLjca0HMxG7rOsyQFtIcoqtI/RfN
         3nfiz8+/ccFcAY93yHc0n67dYTmBYETkqQmPi5Zhy9q3jOn0btANBxY5JA4BbInjn+6+
         oLDvHJpOCKJtnZtLAZvvB5KiVb/HKygPazBP9gSXnPAIeHHJGZOI8TT7e3SkoJypJKYh
         wTHMy7v1cay94wIN0V2YHUaH0FUwYQ5Th5LoaoZ8mFoJQNtIqStrPErYKfwDSvaq5gfS
         y2HbTgYxHjCHXPza/IfEWOxrSt15v4yGK+rnt5uqrP/g1jeSS+hd1AvvP5zE6d4RlyAJ
         Ndvw==
X-Gm-Message-State: APjAAAW0fnLpqCBMVkuemAoIRaS95Heno8b+D5B9rs9X7UZZfTM4ZRvt
        okux9eJmJw8mT2gIbvB2ZZWOsw4G
X-Google-Smtp-Source: 
 APXvYqxcsLojegqPX3jTEGYYoO0ToqgSJ/zzVCQkVX15S+yphKUg+JzDGus4hX2c3KJ/HDdq6u9Glg==
X-Received: by 2002:a1c:6485:: with SMTP id
 y127mr14353805wmb.19.1574679712593;
        Mon, 25 Nov 2019 03:01:52 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 c72sm8341791wmd.11.2019.11.25.03.01.42
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 25 Nov 2019 03:01:46 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@kernel.org,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.5 merge window
Date: Mon, 25 Nov 2019 12:01:40 +0100
Message-Id: <1574679700-32775-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9cb09e7c1c9af2968d5186ef9085f05641ab65d9:

  KVM: Add a comment describing the /dev/kvm no_compat handling (2019-11-15 10:14:04 +0100)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 96710247298df52a4b8150a62a6fe87083093ff3:

  Merge tag 'kvm-ppc-next-5.5-2' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into HEAD (2019-11-25 11:29:05 +0100)

----------------------------------------------------------------

ARM:
- Data abort report and injection
- Steal time support
- GICv4 performance improvements
- vgic ITS emulation fixes
- Simplify FWB handling
- Enable halt polling counters
- Make the emulated timer PREEMPT_RT compliant

s390:
- Small fixes and cleanups
- selftest improvements
- yield improvements

PPC:
- Add capability to tell userspace whether we can single-step the guest.
- Improve the allocation of XIVE virtual processor IDs
- Rewrite interrupt synthesis code to deliver interrupts in virtual
  mode when appropriate.
- Minor cleanups and improvements.

x86:
- XSAVES support for AMD
- more accurate report of nested guest TSC to the nested hypervisor
- retpoline optimizations
- support for nested 5-level page tables
- PMU virtualization optimizations, and improved support for nested
  PMU virtualization
- correct latching of INITs for nested virtualization
- IOAPIC optimization
- TSX_CTRL virtualization for more TAA happiness
- improved allocation and flushing of SEV ASIDs
- many bugfixes and cleanups

----------------------------------------------------------------
Aaron Lewis (13):
      KVM: x86: Introduce vcpu->arch.xsaves_enabled
      KVM: VMX: Fix conditions for guest IA32_XSS support
      KVM: x86: Remove unneeded kvm_vcpu variable, guest_xcr0_loaded
      KVM: SVM: Use wrmsr for switching between guest and host IA32_XSS on AMD
      KVM: VMX: Use wrmsr for switching between guest and host IA32_XSS on Intel
      KVM: x86: Move IA32_XSS-swapping on VM-entry/VM-exit to common x86 code
      kvm: x86: Move IA32_XSS to kvm_{get,set}_msr_common
      kvm: svm: Update svm_xsaves_supported
      kvm: tests: Add test to verify MSR_IA32_XSS
      kvm: nested: Introduce read_and_check_msr_entry()
      kvm: vmx: Rename NR_AUTOLOAD_MSRS to NR_LOADSTORE_MSRS
      kvm: vmx: Rename function find_msr() to vmx_find_msr_index()
      KVM: nVMX: Add support for capturing highest observable L2 TSC

Andrea Arcangeli (4):
      KVM: x86: optimize more exit handlers in vmx.c
      KVM: retpolines: x86: eliminate retpoline from vmx.c exit handlers
      KVM: retpolines: x86: eliminate retpoline from svm.c exit handlers
      x86: retpolines: eliminate retpoline from msr event handlers

Chenyi Qiang (1):
      KVM: nVMX: add CR4_LA57 bit to nested CR4_FIXED1

Christian Borntraeger (4):
      selftests: kvm: make syncregs more reliable on s390
      KVM: s390: count invalid yields
      KVM: s390: Do not yield when target is already running
      KVM: arm/arm64: Show halt poll counters in debugfs

Christoffer Dall (4):
      KVM: arm/arm64: Allow reporting non-ISV data aborts to userspace
      KVM: arm/arm64: Allow user injection of external data aborts
      KVM: arm/arm64: Factor out hypercall handling from PSCI code
      KVM: arm64: Don't set HCR_EL2.TVM when S2FWB is supported

Fabiano Rosas (1):
      KVM: PPC: Report single stepping capability

Greg Kurz (7):
      KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when VPs are allocated
      KVM: PPC: Book3S HV: XIVE: Show VP id in debugfs
      KVM: PPC: Book3S HV: XIVE: Compute the VP id in a common helper
      KVM: PPC: Book3S HV: XIVE: Make VP block size configurable
      KVM: PPC: Book3S HV: XIVE: Allow userspace to set the # of VPs
      KVM: PPC: Book3S HV: XIVE: Free previous EQ page when setting up a new one
      KVM: PPC: Book3S HV: XIVE: Fix potential page leak on error path

Janosch Frank (1):
      KVM: s390: Cleanup kvm_arch_init error path

Jim Mattson (1):
      kvm: nVMX: Relax guest IA32_FEATURE_CONTROL constraints

Leonardo Bras (2):
      KVM: PPC: Reduce calls to get current->mm by storing the value locally
      KVM: PPC: E500: Replace current->mm by kvm->mm

Like Xu (7):
      KVM: x86/vPMU: Declare kvm_pmu->reprogram_pmi field using DECLARE_BITMAP
      perf/core: Provide a kernel-internal interface to recalibrate event period
      perf/core: Provide a kernel-internal interface to pause perf_event
      KVM: x86/vPMU: Rename pmu_ops callbacks from msr_idx to rdpmc_ecx
      KVM: x86/vPMU: Introduce a new kvm_pmu_ops->msr_idx_to_pmc callback
      KVM: x86/vPMU: Reuse perf_event to avoid unnecessary pmc_reprogram_counter
      KVM: x86/vPMU: Add lazy mechanism to release perf_event per vPMC

Liran Alon (12):
      KVM: x86: Evaluate latched_init in KVM_SET_VCPU_EVENTS when vCPU not in SMM
      KVM: x86: Prevent set vCPU into INIT/SIPI_RECEIVED state when INIT are latched
      KVM: VMX: Consume pending LAPIC INIT event when exit on INIT_SIGNAL
      KVM: SVM: Remove check if APICv enabled in SVM update_cr8_intercept() handler
      KVM: VMX: Refactor update_cr8_intercept()
      KVM: nVMX: Update vmcs01 TPR_THRESHOLD if L2 changed L1 TPR
      KVM: x86: Optimization: Requst TLB flush in fast_cr3_switch() instead of do it directly
      KVM: nVMX: Use semi-colon instead of comma for exit-handlers initialization
      KVM: x86: Unexport kvm_vcpu_reload_apic_access_page()
      KVM: nVMX: Assume TLB entries of L1 and L2 are tagged differently if L0 use EPT
      KVM: nVMX: Do not mark vmcs02->apic_access_page as dirty when unpinning
      KVM: nVMX: Remove unnecessary TLB flushes on L1<->L2 switches when L1 use apic-access-page

Mao Wenan (1):
      KVM: x86: remove set but not used variable 'called'

Marc Zyngier (6):
      Merge remote-tracking branch 'arm64/for-next/smccc-conduit-cleanup' into kvm-arm64/stolen-time
      Merge remote-tracking branch 'kvmarm/kvm-arm64/stolen-time' into kvmarm-master/next
      KVM: arm64: vgic-v4: Move the GICv4 residency flow to be driven by vcpu_load/put
      KVM: vgic-v4: Track the number of VLPIs per vcpu
      KVM: arm64: Opportunistically turn off WFI trapping when using direct LPI injection
      Merge remote-tracking branch 'kvmarm/misc-5.5' into kvmarm/next

Marcelo Tosatti (1):
      KVM: x86: switch KVMCLOCK base to monotonic raw clock

Mark Rutland (5):
      arm/arm64: smccc/psci: add arm_smccc_1_1_get_conduit()
      arm64: errata: use arm_smccc_1_1_get_conduit()
      arm: spectre-v2: use arm_smccc_1_1_get_conduit()
      firmware/psci: use common SMCCC_CONDUIT_*
      firmware: arm_sdei: use common SMCCC_CONDUIT_*

Miaohe Lin (6):
      KVM: remove redundant code in kvm_arch_vm_ioctl
      KVM: x86: get rid of odd out jump label in pdptrs_changed
      KVM: MMIO: get rid of odd out_err label in kvm_coalesced_mmio_init
      KVM: X86: avoid unused setup_syscalls_segments call when SYSCALL check failed
      KVM: APIC: add helper func to remove duplicate code in kvm_pv_send_ipi
      KVM: Fix jump label out_free_* in kvm_init()

Nicholas Piggin (5):
      KVM: PPC: Book3S: Define and use SRR1_MSR_BITS
      KVM: PPC: Book3S: Replace reset_msr mmu op with inject_interrupt arch op
      KVM: PPC: Book3S HV: Reuse kvmppc_inject_interrupt for async guest delivery
      KVM: PPC: Book3S HV: Implement LPCR[AIL]=3 mode for injected interrupts
      KVM: PPC: Book3S HV: Reject mflags=2 (LPCR[AIL]=2) ADDR_TRANS_MODE mode

Nitesh Narayan Lal (2):
      KVM: x86: deliver KVM IOAPIC scan request to target vCPUs
      KVM: x86: Zero the IOAPIC scan request dest vCPUs bitmap

Oliver Upton (6):
      KVM: VMX: Add helper to check reserved bits in IA32_PERF_GLOBAL_CTRL
      KVM: nVMX: Check GUEST_IA32_PERF_GLOBAL_CTRL on VM-Entry
      KVM: nVMX: Check HOST_IA32_PERF_GLOBAL_CTRL on VM-Entry
      KVM: nVMX: Use kvm_set_msr to load IA32_PERF_GLOBAL_CTRL on VM-Exit
      KVM: nVMX: Load GUEST_IA32_PERF_GLOBAL_CTRL MSR on VM-Entry
      KVM: nVMX: Expose load IA32_PERF_GLOBAL_CTRL VM-{Entry,Exit} control

Paolo Bonzini (12):
      Merge tag 'kvm-ppc-next-5.5-1' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: nVMX: mark functions in the header as "static inline"
      Merge tag 'kvm-s390-next-5.5-1' of git://git.kernel.org/.../kvms390/linux into HEAD
      Merge tag 'kvmarm-5.5' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: x86: fix presentation of TSX feature in ARCH_CAPABILITIES
      KVM: x86: do not modify masked bits of shared MSRs
      KVM: x86: implement MSR_IA32_TSX_CTRL effect on CPUID
      KVM: vmx: implement MSR_IA32_TSX_CTRL disable RTM functionality
      KVM: vmx: use MSR_IA32_TSX_CTRL to hard-disable TSX on guest that lack it
      Merge branch 'kvm-tsx-ctrl' into HEAD
      KVM: x86: create mmu/ subdirectory
      Merge tag 'kvm-ppc-next-5.5-2' of git://git.kernel.org/.../paulus/powerpc into HEAD

Radim Krčmář (1):
      KVM: remember position in kvm->vcpus array

Sean Christopherson (12):
      KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested VM-Enter
      KVM: VMX: Skip GUEST_CR3 VMREAD+VMWRITE if the VMCS is up-to-date
      KVM: VMX: Consolidate to_vmx() usage in RFLAGS accessors
      KVM: VMX: Optimize vmx_set_rflags() for unrestricted guest
      KVM: x86: Add WARNs to detect out-of-bounds register indices
      KVM: x86: Fold 'enum kvm_ex_reg' definitions into 'enum kvm_reg'
      KVM: x86: Add helpers to test/mark reg availability and dirtiness
      KVM: x86: Fold decache_cr3() into cache_reg()
      KVM: Add separate helper for putting borrowed reference to kvm
      KVM: x86: Remove a spurious export of a static function
      KVM: x86: Open code shared_msr_update() in its only caller
      KVM: x86: Grab KVM's srcu lock when setting nested state

Steven Price (10):
      KVM: arm64: Document PV-time interface
      KVM: arm64: Implement PV_TIME_FEATURES call
      KVM: Implement kvm_put_guest()
      KVM: arm64: Support stolen time reporting via shared structure
      KVM: Allow kvm_device_ops to be const
      KVM: arm64: Provide VCPU attributes for stolen time
      arm/arm64: Provide a wrapper for SMCCC 1.1 calls
      arm/arm64: Make use of the SMCCC 1.1 wrapper
      arm64: Retrieve stolen time as paravirtualized guest
      KVM: arm64: Select TASK_DELAY_ACCT+TASKSTATS rather than SCHEDSTATS

Suthikulpanit, Suravee (1):
      kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm parameter

Thomas Gleixner (1):
      KVM: arm/arm64: Let the timer expire in hardirq context on RT

Thomas Huth (1):
      KVM: s390: Remove unused parameter from __inject_sigp_restart()

Tom Lendacky (4):
      KVM: SVM: Serialize access to the SEV ASID bitmap
      KVM: SVM: Guard against DEACTIVATE when performing WBINVD/DF_FLUSH
      KVM: SVM: Remove unneeded WBINVD and DF_FLUSH when starting SEV guests
      KVM: SVM: Reduce WBINVD/DF_FLUSH invocations

Wainer dos Santos Moschetta (1):
      selftests: kvm: Simplify loop in kvm_create_max_vcpus test

Xiaoyao Li (4):
      KVM: VMX: Write VPID to vmcs when creating vcpu
      KVM: VMX: Remove vmx->hv_deadline_tsc initialization from vmx_vcpu_setup()
      KVM: VMX: Initialize vmx->guest_msrs[] right after allocation
      KVM: VMX: Rename {vmx,nested_vmx}_vcpu_setup()

Yi Wang (1):
      x86/kvm: Fix -Wmissing-prototypes warnings

Zenghui Yu (3):
      KVM: arm/arm64: vgic: Remove the declaration of kvm_send_userspace_msi()
      KVM: arm/arm64: vgic: Fix some comments typo
      KVM: arm/arm64: vgic: Don't rely on the wrong pending table

 Documentation/admin-guide/kernel-parameters.txt    |   6 +-
 Documentation/virt/kvm/api.txt                     |  58 +++-
 Documentation/virt/kvm/arm/pvtime.rst              |  80 +++++
 Documentation/virt/kvm/devices/vcpu.txt            |  14 +
 Documentation/virt/kvm/devices/xics.txt            |  14 +-
 Documentation/virt/kvm/devices/xive.txt            |   8 +
 arch/arm/include/asm/kvm_arm.h                     |   1 +
 arch/arm/include/asm/kvm_emulate.h                 |   9 +-
 arch/arm/include/asm/kvm_host.h                    |  33 ++
 arch/arm/include/uapi/asm/kvm.h                    |   3 +-
 arch/arm/kvm/Makefile                              |   2 +-
 arch/arm/kvm/guest.c                               |  14 +
 arch/arm/kvm/handle_exit.c                         |   2 +-
 arch/arm/mm/proc-v7-bugs.c                         |  21 +-
 arch/arm64/include/asm/kvm_arm.h                   |   3 +-
 arch/arm64/include/asm/kvm_emulate.h               |  26 +-
 arch/arm64/include/asm/kvm_host.h                  |  37 +++
 arch/arm64/include/asm/paravirt.h                  |   9 +-
 arch/arm64/include/asm/pvclock-abi.h               |  17 ++
 arch/arm64/include/uapi/asm/kvm.h                  |   5 +-
 arch/arm64/kernel/cpu_errata.c                     | 102 ++-----
 arch/arm64/kernel/paravirt.c                       | 140 +++++++++
 arch/arm64/kernel/sdei.c                           |   3 +-
 arch/arm64/kernel/time.c                           |   3 +
 arch/arm64/kvm/Kconfig                             |   4 +
 arch/arm64/kvm/Makefile                            |   2 +
 arch/arm64/kvm/guest.c                             |  23 ++
 arch/arm64/kvm/handle_exit.c                       |   4 +-
 arch/arm64/kvm/inject_fault.c                      |   4 +-
 arch/powerpc/include/asm/kvm_host.h                |   1 -
 arch/powerpc/include/asm/kvm_ppc.h                 |   1 +
 arch/powerpc/include/asm/reg.h                     |  12 +
 arch/powerpc/include/uapi/asm/kvm.h                |   3 +
 arch/powerpc/kvm/book3s.c                          |  27 +-
 arch/powerpc/kvm/book3s.h                          |   3 +
 arch/powerpc/kvm/book3s_32_mmu.c                   |   6 -
 arch/powerpc/kvm/book3s_64_mmu.c                   |  15 -
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |  26 +-
 arch/powerpc/kvm/book3s_64_vio.c                   |   2 +-
 arch/powerpc/kvm/book3s_hv.c                       |  28 +-
 arch/powerpc/kvm/book3s_hv_builtin.c               |  82 ++++-
 arch/powerpc/kvm/book3s_hv_nested.c                |   2 +-
 arch/powerpc/kvm/book3s_pr.c                       |  40 ++-
 arch/powerpc/kvm/book3s_xive.c                     | 128 ++++++--
 arch/powerpc/kvm/book3s_xive.h                     |   5 +
 arch/powerpc/kvm/book3s_xive_native.c              |  82 ++---
 arch/powerpc/kvm/e500_mmu_host.c                   |   6 +-
 arch/powerpc/kvm/powerpc.c                         |   2 +
 arch/s390/include/asm/kvm_host.h                   |   1 +
 arch/s390/kvm/diag.c                               |  22 +-
 arch/s390/kvm/interrupt.c                          |   5 +-
 arch/s390/kvm/kvm-s390.c                           |  19 +-
 arch/x86/events/intel/core.c                       |  11 +
 arch/x86/include/asm/kvm_host.h                    |  32 +-
 arch/x86/kernel/kvm.c                              |   1 +
 arch/x86/kvm/Makefile                              |   4 +-
 arch/x86/kvm/cpuid.c                               |   8 +-
 arch/x86/kvm/emulate.c                             |   6 +-
 arch/x86/kvm/ioapic.c                              |  34 ++-
 arch/x86/kvm/kvm_cache_regs.h                      |  51 +++-
 arch/x86/kvm/lapic.c                               | 111 ++++---
 arch/x86/kvm/lapic.h                               |   3 +
 arch/x86/kvm/{ => mmu}/mmu.c                       |   2 +-
 arch/x86/kvm/{ => mmu}/page_track.c                |   0
 arch/x86/kvm/{ => mmu}/paging_tmpl.h               |   0
 arch/x86/kvm/pmu.c                                 | 124 +++++++-
 arch/x86/kvm/pmu.h                                 |  29 +-
 arch/x86/kvm/pmu_amd.c                             |  24 +-
 arch/x86/kvm/svm.c                                 | 140 ++++++---
 arch/x86/kvm/vmx/nested.c                          | 252 ++++++++++++---
 arch/x86/kvm/vmx/nested.h                          |   9 +-
 arch/x86/kvm/vmx/pmu_intel.c                       |  34 ++-
 arch/x86/kvm/vmx/vmx.c                             | 339 +++++++++++----------
 arch/x86/kvm/vmx/vmx.h                             |  12 +-
 arch/x86/kvm/x86.c                                 | 244 +++++++++------
 arch/x86/kvm/x86.h                                 |  15 +-
 drivers/crypto/ccp/psp-dev.c                       |   9 +
 drivers/firmware/arm_sdei.c                        |  12 +-
 drivers/firmware/psci/psci.c                       |  24 +-
 drivers/irqchip/irq-gic-v4.c                       |   7 +-
 include/Kbuild                                     |   2 +
 include/kvm/arm_hypercalls.h                       |  43 +++
 include/kvm/arm_psci.h                             |   2 +-
 include/kvm/arm_vgic.h                             |   8 +-
 include/linux/arm-smccc.h                          |  75 +++++
 include/linux/arm_sdei.h                           |   6 -
 include/linux/cpuhotplug.h                         |   1 +
 include/linux/irqchip/arm-gic-v4.h                 |   4 +
 include/linux/kvm_host.h                           |  41 ++-
 include/linux/kvm_types.h                          |   2 +
 include/linux/perf_event.h                         |  10 +
 include/linux/psci.h                               |   9 +-
 include/uapi/linux/kvm.h                           |  11 +
 kernel/events/core.c                               |  46 ++-
 tools/testing/selftests/kvm/.gitignore             |   1 +
 tools/testing/selftests/kvm/Makefile               |   1 +
 .../selftests/kvm/include/x86_64/processor.h       |   7 +-
 tools/testing/selftests/kvm/kvm_create_max_vcpus.c |   7 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  72 ++++-
 tools/testing/selftests/kvm/s390x/sync_regs_test.c |  15 +-
 tools/testing/selftests/kvm/x86_64/xss_msr_test.c  |  76 +++++
 virt/kvm/arm/arch_timer.c                          |   8 +-
 virt/kvm/arm/arm.c                                 |  49 ++-
 virt/kvm/arm/hypercalls.c                          |  71 +++++
 virt/kvm/arm/mmio.c                                |   9 +-
 virt/kvm/arm/psci.c                                |  84 +----
 virt/kvm/arm/pvtime.c                              | 131 ++++++++
 virt/kvm/arm/vgic/vgic-init.c                      |   1 +
 virt/kvm/arm/vgic/vgic-its.c                       |   3 +
 virt/kvm/arm/vgic/vgic-v3.c                        |  12 +-
 virt/kvm/arm/vgic/vgic-v4.c                        |  59 ++--
 virt/kvm/arm/vgic/vgic.c                           |   4 -
 virt/kvm/arm/vgic/vgic.h                           |   2 -
 virt/kvm/coalesced_mmio.c                          |   8 +-
 virt/kvm/kvm_main.c                                |  34 ++-
 115 files changed, 2641 insertions(+), 975 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 rename arch/x86/kvm/{ => mmu}/mmu.c (99%)
 rename arch/x86/kvm/{ => mmu}/page_track.c (100%)
 rename arch/x86/kvm/{ => mmu}/paging_tmpl.h (100%)
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/xss_msr_test.c
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
#### [GIT PULL] Please pull my kvm-ppc-next-5.5-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11259453
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C02614C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 00:58:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3C31020823
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 00:58:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="UMXTR6Ue"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727184AbfKYA6c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 24 Nov 2019 19:58:32 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:47659 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727126AbfKYA6c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 Nov 2019 19:58:32 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 47LpYy0Ym2z9sPf; Mon, 25 Nov 2019 11:58:29 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1574643510; bh=OFA72bnCsrg8Coz2J033yUMxPG/0CYGgg43ImyrX5as=;
        h=Date:From:To:Cc:Subject:From;
        b=UMXTR6Ueq1Mp1Xw7kFaK2/tR6xb6L9u4Qo+4ItVShcTkTkYLgZkgcnBNDztKuMKRh
         olEfTtgIY/ccRiGhobeVhlPh2rVmQel2thV5TGtfXRqeZqgpdFCvBB/+dw+DPyMEw2
         G05NKoaBCIdOUPbI4tvlYfXfU+zawTFqcp58oaqiylWtY/rgui2jJ71rFaTwoa0KTt
         rmR5hWt2HBGU/sotcZPlSXEedFIfhhY0GQWNbdx2sFtIC11A6e35Tnmd5QgzghINw2
         E8iXyMYmdyp9d319930Ok8/wM3gul4xprfeCkc6hyO6pvLaiRfckXIGDekRqmp1GIP
         Sr5d87CPvRw8Q==
Date: Mon, 25 Nov 2019 11:58:26 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, Greg Kurz <groug@kaod.org>
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.5-2 tag
Message-ID: <20191125005826.GA25463@oak.ozlabs.ibm.com>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-next-5.5-2 tag to get two more
commits which should go upstream for 5.5.  Although they are in my
kvm-ppc-next branch, they are actually bug fixes, fixing host memory
leaks in the XIVE interrupt controller code, so they should be fine to
go into v5.5 even though the merge window is now open.

Thanks,
Paul.

The following changes since commit 55d7004299eb917767761f01a208d50afad4f535:

  KVM: PPC: Book3S HV: Reject mflags=2 (LPCR[AIL]=2) ADDR_TRANS_MODE mode (2019-10-22 16:29:02 +1100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.5-2

for you to fetch changes up to 30486e72093ea2e594f44876b7a445c219449bce:

  KVM: PPC: Book3S HV: XIVE: Fix potential page leak on error path (2019-11-21 16:24:41 +1100)

----------------------------------------------------------------
Second KVM PPC update for 5.5

- Two fixes from Greg Kurz to fix memory leak bugs in the XIVE code.

----------------------------------------------------------------
Greg Kurz (2):
      KVM: PPC: Book3S HV: XIVE: Free previous EQ page when setting up a new one
      KVM: PPC: Book3S HV: XIVE: Fix potential page leak on error path

 arch/powerpc/kvm/book3s_xive_native.c | 44 +++++++++++++++++++++++------------
 1 file changed, 29 insertions(+), 15 deletions(-)
```
#### [kvm-unit-tests PATCH] x86: Add RDTSC testFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11260891
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 06890930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 22:45:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D9657207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 22:45:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="vhMiTCmQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727877AbfKYWpy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 25 Nov 2019 17:45:54 -0500
Received: from mail-pf1-f201.google.com ([209.85.210.201]:44279 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725946AbfKYWpx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 25 Nov 2019 17:45:53 -0500
Received: by mail-pf1-f201.google.com with SMTP id 2so10644490pfx.11
        for <kvm@vger.kernel.org>; Mon, 25 Nov 2019 14:45:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=swz/sjYKb6g3M40/hztc/tyAihR4u+28ellm/nQF/QM=;
        b=vhMiTCmQBcovEk45MSKnaR63E74jfHw/feAR7qBaPHmmJ0P4nu0KJClcbZ7wD0BQVa
         oBsdSgyld41ekvGr+x3M5HyMBCI2Cl9JZs+ZO7zNfGgFZffxZMCjdG3ehuWoY28GeQHD
         KH+2hFPVGPSdA2r5xfVHYaz8yGvMeGwB0gdrk4k7Y/bQYR20qcZ6UqvnVDFKMjJ9w8SJ
         IJ/QxDIVMMTQ7ThrRLA6yTrFSqEoSAvL45kaHlB0JlhPlOiewyM3m1mC5ymBPDHacddi
         V37HDrsCxGIqets9+f9Z2DCav3qDIVv8DJXduglAYMWbkW6vKb6WsXuYJX/kXOIBVp34
         SJqA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=swz/sjYKb6g3M40/hztc/tyAihR4u+28ellm/nQF/QM=;
        b=VHlHfMvRzvs00t+MyXoy0ckf05jRejv93SVFQv4HdlEJSFYa8ZkjLRduf3yWOwJwPs
         0GP8Yh1Rnjszm6Sja9G+zZrfR6TynGgXOEhDNPrhI//EieD+zzvjlWRX4McoHMG59fNs
         XwiHBuR+zjjpurQggfkzQwLsYxOciehFl29VlmvuaREacV3IK/PiLLhIogYs57yBWGL3
         7xtU4XDH4XTCaqWPeiMzanzSqZUnDrAZxJnXIHEkDRHMxMkca4YYRjKHzPSSvVgl/Ggb
         diQmpvPuAAjSdR2mypivuNIDVQ9+CZEU2vV8xzN3cJ7hsvH28LSVc6rOqEqCjDSQjqsv
         WKgg==
X-Gm-Message-State: APjAAAWT0RrKzAQmM/2JhUymeFswiAL+K2C+pbPp58+qPIw7C/aQ158J
        qXJUVLH8XrseM7weeWuVJeBogKV22UcVEBV/
X-Google-Smtp-Source: 
 APXvYqxM2JCnCwfekVNgzOEeFllNWJCuRATX0bZ5W1OhrqHWMmoi/HLhuhS7ZWsPK80pbfnPMQ0eGB5XuOFf2JX7
X-Received: by 2002:a63:750f:: with SMTP id
 q15mr35303993pgc.422.1574721951113;
 Mon, 25 Nov 2019 14:45:51 -0800 (PST)
Date: Mon, 25 Nov 2019 14:44:29 -0800
Message-Id: <20191125224428.77547-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.432.g9d3f5f5b63-goog
Subject: [kvm-unit-tests PATCH] x86: Add RDTSC test
From: Aaron Lewis <aaronlewis@google.com>
To: Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that the difference between an L2 RDTSC instruction and the
IA32_TIME_STAMP_COUNTER MSR value stored in the VMCS12's VM-exit
MSR-store list is less than 750 cycles, 99.9% of the time.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/unittests.cfg |  6 ++++
 x86/vmx_tests.c   | 89 +++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 95 insertions(+)

```
#### [PATCH 01/19] mm/gup: factor out duplicate code from four routines
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11259705
Return-Path: <SRS0=umKK=ZR=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3E8115AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 04:22:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ABB2B20748
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 25 Nov 2019 04:22:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="kbnYv7xF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727655AbfKYEV7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 24 Nov 2019 23:21:59 -0500
Received: from hqemgate16.nvidia.com ([216.228.121.65]:9429 "EHLO
        hqemgate16.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727237AbfKYEUV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 24 Nov 2019 23:20:21 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate16.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ddb567f0001>; Sun, 24 Nov 2019 20:20:15 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Sun, 24 Nov 2019 20:20:13 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Sun, 24 Nov 2019 20:20:13 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 25 Nov
 2019 04:20:13 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 25 Nov 2019 04:20:13 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5ddb567c0005>; Sun, 24 Nov 2019 20:20:13 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 Christoph Hellwig <hch@lst.de>,
 "Aneesh Kumar K . V" <aneesh.kumar@linux.ibm.com>
Subject: [PATCH 01/19] mm/gup: factor out duplicate code from four routines
Date: Sun, 24 Nov 2019 20:19:53 -0800
Message-ID: <20191125042011.3002372-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191125042011.3002372-1-jhubbard@nvidia.com>
References: <20191125042011.3002372-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1574655615; bh=NjEUDVUY50BsRhke7z2S9TxhDwSe8KFPL35zO7aJjtI=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=kbnYv7xF7oUGLgLIh4rwCdaQmCfVgsHWNFDiwX8EcsnRvWDPylmcMeF5/6w3IlG4J
         pxg+6Jjsxjz0lkri9YeCfd3M+gYEbAixMskJdJpKttexEKSPUTJ2prsW5PPNfQOuX5
         CX8iPaWncwM8W+P58MMMuv/DQwUkQ882++t6EFW9WE4d/hP0krYJCbpAHt3nTjojZ0
         OConKHdeZBjm2p3J72ruspdRMSf2BiWiisU7Fg4y8rHR1s9ipiibNKR50WwAg/4Smw
         cKZ4bc1xKrYAVhrpGMthOpUJ6wh8QBIn6D+OYnUkUfQkCjuYhi/yrIyDNpO2IWrGmA
         MwIwh91pUzbbA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are four locations in gup.c that have a fair amount of code
duplication. This means that changing one requires making the same
changes in four places, not to mention reading the same code four
times, and wondering if there are subtle differences.

Factor out the common code into static functions, thus reducing the
overall line count and the code's complexity.

Also, take the opportunity to slightly improve the efficiency of the
error cases, by doing a mass subtraction of the refcount, surrounded
by get_page()/put_page().

Also, further simplify (slightly), by waiting until the the successful
end of each routine, to increment *nr.

Reviewed-by: Christoph Hellwig <hch@lst.de>
Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Jan Kara <jack@suse.cz>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Aneesh Kumar K.V <aneesh.kumar@linux.ibm.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 mm/gup.c | 91 ++++++++++++++++++++++----------------------------------
 1 file changed, 36 insertions(+), 55 deletions(-)

```
