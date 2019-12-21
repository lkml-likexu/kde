

#### [RFC 0/2] Paravirtualized Control Register pinning
##### From: John Andersen <john.s.andersen@intel.com>

```c
From patchwork Fri Dec 20 00:13:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11304529
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47E0513B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 00:13:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2556324680
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 00:13:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727084AbfLTANb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Dec 2019 19:13:31 -0500
Received: from mga06.intel.com ([134.134.136.31]:64772 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726964AbfLTANb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Dec 2019 19:13:31 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 19 Dec 2019 16:13:30 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,333,1571727600";
   d="scan'208";a="241340277"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga004.fm.intel.com with ESMTP; 19 Dec 2019 16:13:29 -0800
From: John Andersen <john.s.andersen@intel.com>
To: kvm@vger.kernel.org
Cc: John Andersen <john.s.andersen@intel.com>
Subject: [RFC 0/2] Paravirtualized Control Register pinning
Date: Thu, 19 Dec 2019 16:13:20 -0800
Message-Id: <20191220001322.22317-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paravirtualized Control Register pinning is a strengthened version of
existing protections on the Write Protect, Supervisor Mode Execution /
Access Protection, and User-Mode Instruction Prevention bits. The
existing protections prevent native_write_cr*() functions from writing
values which disable those bits. This patchset prevents any guest
writes to control registers from disabling pinned bits, not just writes
from native_write_cr*(). This stops attackers within the guest from
using ROP to disable protection bits.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

The protection is implemented by adding MSRs to KVM which contain the
bits that are allowed to be pinned, and the bits which are pinned. The
guest or userspace can enable bit pinning by reading MSRs to check
which bits are allowed to be pinned, and then writing MSRs to set which
bits they want pinned.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

We add a CR pin feature bit to the KVM cpuid, read only MSRs which
guests use to identify which bits they may request be pinned, and
CR pinned MSRs which contain the pinned bits. Guests can request that
KVM pin bits within control register 0 or 4 via the CR pinned MSRs.
Writes to the MSRs fail if they include bits that aren't allowed to be
pinned. Host userspace may clear or modify pinned bits at any time.
Once pinned bits are set, the guest may pin more allowed bits, but may
never clear pinned bits.

In the event that the guest vcpu attempts to disable any of the pinned
bits, the vcpu that issued the write is sent a general protection
fault, and the register is left unchanged.

Pinning is not active when running in SMM. Entering SMM disables pinned
bits, writes to control registers within SMM would therefore trigger
general protection faults if pinning was enforced.

The guest may never read pinned bits. If an attacker were to read the
CR pinned MSRs, they might decide to preform another attack which would
not cause a general protection fault.

Should userspace expose the CR pining CPUID feature bit, it must zero CR
pinned MSRs on reboot. If it does not, it runs the risk of having the
guest enable pinning and subsequently cause general protection faults on
next boot due to early boot code setting control registers to values
which do not contain the pinned bits.

When running with KVM guest support and paravirtualized CR pinning
enabled, paravirtualized and existing pinning are setup at the same
point on the boot CPU. Non-boot CPUs setup pinning upon identification.

Guests using the kexec system call currently do not support
paravirtualized control register pinning. This is due to early boot
code writing known good values to control registers, these values do
not contain the protected bits. This is due to CPU feature
identification being done at a later time, when the kernel properly
checks if it can enable protections.

Most distributions enable kexec. However, kexec could be made boot time
disableable. In this case if a user has disabled kexec at boot time
the guest will request that paravirtualized control register pinning
be enabled. This would expand the userbase to users of major
distributions.

Paravirtualized CR pinning will likely be incompatible with kexec for
the foreseeable future. Early boot code could possibly be changed to
not clear protected bits. However, a kernel that requests CR bits be
pinned can't know if the kernel it's kexecing has been updated to not
clear protected bits. This would result in the kernel being kexec'd
almost immediately receiving a general protection fault.

Security conscious kernel configurations disable kexec already, per KSPP
guidelines. Projects such as Kata Containers, AWS Lambda, ChromeOS
Termina, and others using KVM to virtualize Linux will benefit from
this protection.

The usage of SMM in SeaBIOS was explored as a way to communicate to KVM
that a reboot has occurred and it should zero the pinned bits. When
using QEMU and SeaBIOS, SMM initialization occurs on reboot. However,
prior to SMM initialization, BIOS writes zero values to CR0, causing a
general protection fault to be sent to the guest before SMM can signal
that the machine has booted.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction. Guests running with paravirtualized CR pinning are now
protected against the use of ROP to disable CR bits. The same bits that
are being pinned natively may be pinned via the CR pinned MSRs. These
bits are WP in CR0, and SMEP, SMAP, and UMIP in CR4.

Future patches could implement similar MSR and hypercall combinations
to protect bits in MSRs. The NXE bit of the EFER MSR is a prime
candidate.

John Andersen (2):
  KVM: X86: Add CR pin MSRs
  X86: Use KVM CR pin MSRs

 Documentation/virt/kvm/msr.txt       | 38 +++++++++++++++++++++++
 arch/x86/Kconfig                     |  9 ++++++
 arch/x86/include/asm/kvm_host.h      |  2 ++
 arch/x86/include/asm/kvm_para.h      | 10 +++++++
 arch/x86/include/uapi/asm/kvm_para.h |  5 ++++
 arch/x86/kernel/cpu/common.c         |  5 ++++
 arch/x86/kernel/kvm.c                | 17 +++++++++++
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/x86.c                   | 45 ++++++++++++++++++++++++++++
 9 files changed, 133 insertions(+), 1 deletion(-)
```
#### [PATCH v2 00/18] arm64: KVM: add SPE profiling support
##### From: Andrew Murray <andrew.murray@arm.com>

```c
From patchwork Fri Dec 20 14:30:07 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Murray <Andrew.Murray@arm.com>
X-Patchwork-Id: 11305673
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA7CB13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 14:34:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C163A21D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 14:34:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727747AbfLTOae (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 09:30:34 -0500
Received: from foss.arm.com ([217.140.110.172]:51172 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727732AbfLTOad (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 09:30:33 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 648A130E;
        Fri, 20 Dec 2019 06:30:32 -0800 (PST)
Received: from e119886-lin.cambridge.arm.com (unknown [10.37.6.20])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 8ABF43F718;
        Fri, 20 Dec 2019 06:30:30 -0800 (PST)
From: Andrew Murray <andrew.murray@arm.com>
To: Marc Zyngier <marc.zyngier@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will.deacon@arm.com>
Cc: Sudeep Holla <sudeep.holla@arm.com>, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Mark Rutland <mark.rutland@arm.com>
Subject: [PATCH v2 00/18] arm64: KVM: add SPE profiling support
Date: Fri, 20 Dec 2019 14:30:07 +0000
Message-Id: <20191220143025.33853-1-andrew.murray@arm.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements support for allowing KVM guests to use the Arm
Statistical Profiling Extension (SPE).

It has been tested on a model to ensure that both host and guest can
simultaneously use SPE with valid data. E.g.

$ perf record -e arm_spe/ts_enable=1,pa_enable=1,pct_enable=1/ \
        dd if=/dev/zero of=/dev/null count=1000
$ perf report --dump-raw-trace > spe_buf.txt

As we save and restore the SPE context, the guest can access the SPE
registers directly, thus in this version of the series we remove the
trapping and emulation.

In the previous series of this support, when KVM SPE isn't supported
(e.g. via CONFIG_KVM_ARM_SPE) we were able to return a value of 0 to
all reads of the SPE registers - as we can no longer do this there isn't
a mechanism to prevent the guest from using SPE - thus I'm keen for
feedback on the best way of resolving this.

It appears necessary to pin the entire guest memory in order to provide
guest SPE access - otherwise it is possible for the guest to receive
Stage-2 faults.

The last two extra patches are for the kvmtool if someone wants to play
with it.

Changes since v2:
	- Rebased on v5.5-rc2
	- Renamed kvm_spe structure 'irq' member to 'irq_num'
	- Added irq_level to kvm_spe structure
	- Clear PMBSR service bit on save to avoid spurious interrupts
	- Update kvmtool headers to 5.4
	- Enabled SPE in KVM init features
	- No longer trap and emulate
	- Add support for guest/host exclusion flags
	- Fix virq support for SPE
	- Adjusted sysreg_elx_s macros with merged clang build support

Andrew Murray (4):
  KVM: arm64: don't trap Statistical Profiling controls to EL2
  perf: arm_spe: Add KVM structure for obtaining IRQ info
  KVM: arm64: spe: Provide guest virtual interrupts for SPE
  perf: arm_spe: Handle guest/host exclusion flags

Sudeep Holla (12):
  dt-bindings: ARM SPE: highlight the need for PPI partitions on
    heterogeneous systems
  arm64: KVM: reset E2PB correctly in MDCR_EL2 when exiting the
    guest(VHE)
  arm64: KVM: define SPE data structure for each vcpu
  arm64: KVM: add SPE system registers to sys_reg_descs
  arm64: KVM/VHE: enable the use PMSCR_EL12 on VHE systems
  arm64: KVM: split debug save restore across vm/traps activation
  arm64: KVM/debug: drop pmscr_el1 and use sys_regs[PMSCR_EL1] in
    kvm_cpu_context
  arm64: KVM: add support to save/restore SPE profiling buffer controls
  arm64: KVM: enable conditional save/restore full SPE profiling buffer
    controls
  arm64: KVM/debug: use EL1&0 stage 1 translation regime
  KVM: arm64: add a new vcpu device control group for SPEv1
  KVM: arm64: enable SPE support
  KVMTOOL: update_headers: Sync kvm UAPI headers with linux v5.5-rc2
  KVMTOOL: kvm: add a vcpu feature for SPEv1 support

 .../devicetree/bindings/arm/spe-pmu.txt       |   5 +-
 Documentation/virt/kvm/devices/vcpu.txt       |  28 +++
 arch/arm64/include/asm/kvm_host.h             |  18 +-
 arch/arm64/include/asm/kvm_hyp.h              |   6 +-
 arch/arm64/include/asm/sysreg.h               |   1 +
 arch/arm64/include/uapi/asm/kvm.h             |   4 +
 arch/arm64/kvm/Kconfig                        |   7 +
 arch/arm64/kvm/Makefile                       |   1 +
 arch/arm64/kvm/debug.c                        |   2 -
 arch/arm64/kvm/guest.c                        |   6 +
 arch/arm64/kvm/hyp/debug-sr.c                 | 105 +++++---
 arch/arm64/kvm/hyp/switch.c                   |  18 +-
 arch/arm64/kvm/reset.c                        |   3 +
 arch/arm64/kvm/sys_regs.c                     |  11 +
 drivers/perf/arm_spe_pmu.c                    |  26 ++
 include/kvm/arm_spe.h                         |  82 ++++++
 include/uapi/linux/kvm.h                      |   1 +
 virt/kvm/arm/arm.c                            |  10 +-
 virt/kvm/arm/spe.c                            | 234 ++++++++++++++++++
 19 files changed, 521 insertions(+), 47 deletions(-)
 create mode 100644 include/kvm/arm_spe.h
 create mode 100644 virt/kvm/arm/spe.c
```
#### [RESEND RFC 0/2] Paravirtualized Control Register pinning
##### From: John Andersen <john.s.andersen@intel.com>

```c
From patchwork Fri Dec 20 19:26:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11306251
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3755114E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 19:27:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C14020866
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 19:27:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727531AbfLTT1j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 14:27:39 -0500
Received: from mga17.intel.com ([192.55.52.151]:28192 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727394AbfLTT1j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 14:27:39 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Dec 2019 11:27:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,336,1571727600";
   d="scan'208";a="222547137"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga001.fm.intel.com with ESMTP; 20 Dec 2019 11:27:38 -0800
From: John Andersen <john.s.andersen@intel.com>
To: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com
Cc: hpa@zytor.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        John Andersen <john.s.andersen@intel.com>
Subject: [RESEND RFC 0/2] Paravirtualized Control Register pinning
Date: Fri, 20 Dec 2019 11:26:59 -0800
Message-Id: <20191220192701.23415-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paravirtualized Control Register pinning is a strengthened version of
existing protections on the Write Protect, Supervisor Mode Execution /
Access Protection, and User-Mode Instruction Prevention bits. The
existing protections prevent native_write_cr*() functions from writing
values which disable those bits. This patchset prevents any guest
writes to control registers from disabling pinned bits, not just writes
from native_write_cr*(). This stops attackers within the guest from
using ROP to disable protection bits.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

The protection is implemented by adding MSRs to KVM which contain the
bits that are allowed to be pinned, and the bits which are pinned. The
guest or userspace can enable bit pinning by reading MSRs to check
which bits are allowed to be pinned, and then writing MSRs to set which
bits they want pinned.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

We add a CR pin feature bit to the KVM cpuid, read only MSRs which
guests use to identify which bits they may request be pinned, and
CR pinned MSRs which contain the pinned bits. Guests can request that
KVM pin bits within control register 0 or 4 via the CR pinned MSRs.
Writes to the MSRs fail if they include bits that aren't allowed to be
pinned. Host userspace may clear or modify pinned bits at any time.
Once pinned bits are set, the guest may pin more allowed bits, but may
never clear pinned bits.

In the event that the guest vcpu attempts to disable any of the pinned
bits, the vcpu that issued the write is sent a general protection
fault, and the register is left unchanged.

Pinning is not active when running in SMM. Entering SMM disables pinned
bits, writes to control registers within SMM would therefore trigger
general protection faults if pinning was enforced.

The guest may never read pinned bits. If an attacker were to read the
CR pinned MSRs, they might decide to preform another attack which would
not cause a general protection fault.

Should userspace expose the CR pining CPUID feature bit, it must zero CR
pinned MSRs on reboot. If it does not, it runs the risk of having the
guest enable pinning and subsequently cause general protection faults on
next boot due to early boot code setting control registers to values
which do not contain the pinned bits.

When running with KVM guest support and paravirtualized CR pinning
enabled, paravirtualized and existing pinning are setup at the same
point on the boot CPU. Non-boot CPUs setup pinning upon identification.

Guests using the kexec system call currently do not support
paravirtualized control register pinning. This is due to early boot
code writing known good values to control registers, these values do
not contain the protected bits. This is due to CPU feature
identification being done at a later time, when the kernel properly
checks if it can enable protections.

Most distributions enable kexec. However, kexec could be made boot time
disableable. In this case if a user has disabled kexec at boot time
the guest will request that paravirtualized control register pinning
be enabled. This would expand the userbase to users of major
distributions.

Paravirtualized CR pinning will likely be incompatible with kexec for
the foreseeable future. Early boot code could possibly be changed to
not clear protected bits. However, a kernel that requests CR bits be
pinned can't know if the kernel it's kexecing has been updated to not
clear protected bits. This would result in the kernel being kexec'd
almost immediately receiving a general protection fault.

Security conscious kernel configurations disable kexec already, per KSPP
guidelines. Projects such as Kata Containers, AWS Lambda, ChromeOS
Termina, and others using KVM to virtualize Linux will benefit from
this protection.

The usage of SMM in SeaBIOS was explored as a way to communicate to KVM
that a reboot has occurred and it should zero the pinned bits. When
using QEMU and SeaBIOS, SMM initialization occurs on reboot. However,
prior to SMM initialization, BIOS writes zero values to CR0, causing a
general protection fault to be sent to the guest before SMM can signal
that the machine has booted.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction. Guests running with paravirtualized CR pinning are now
protected against the use of ROP to disable CR bits. The same bits that
are being pinned natively may be pinned via the CR pinned MSRs. These
bits are WP in CR0, and SMEP, SMAP, and UMIP in CR4.

Future patches could protect bits in MSRs in a similar fashion. The NXE
bit of the EFER MSR is a prime candidate.

John Andersen (2):
  KVM: X86: Add CR pin MSRs
  X86: Use KVM CR pin MSRs

 Documentation/virt/kvm/msr.txt       | 38 +++++++++++++++++++++++
 arch/x86/Kconfig                     |  9 ++++++
 arch/x86/include/asm/kvm_host.h      |  2 ++
 arch/x86/include/asm/kvm_para.h      | 10 +++++++
 arch/x86/include/uapi/asm/kvm_para.h |  5 ++++
 arch/x86/kernel/cpu/common.c         |  5 ++++
 arch/x86/kernel/kvm.c                | 17 +++++++++++
 arch/x86/kvm/cpuid.c                 |  3 +-
 arch/x86/kvm/x86.c                   | 45 ++++++++++++++++++++++++++++
 9 files changed, 133 insertions(+), 1 deletion(-)
```
#### [PATCH v2 00/17] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Dec 20 21:01:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306279
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 89D53139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:01:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5385A2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:01:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="caln8y2I"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727474AbfLTVBx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:01:53 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:58730 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727402AbfLTVBx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Dec 2019 16:01:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576875711;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=caln8y2I1rCfd+UhlG1bUqUk4AmAzzj1ed52Ijl5Wl6GPOlK2riM2ZlEKkG49/RpNVqeBg
        ucOzI8s+LN9Oi7a3wSw2vOZlcY0Kut4SSFTh6OdsXj46j4iHAJa+zluwN4n4JSlLbfIyEL
        Z5wVmJATmgEe4+XDOUUC3c2zfZzOH80=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-250-w4p8R88OP1qgNZSyVNZEVQ-1; Fri, 20 Dec 2019 16:01:50 -0500
X-MC-Unique: w4p8R88OP1qgNZSyVNZEVQ-1
Received: by mail-qv1-f70.google.com with SMTP id c1so6694316qvw.17
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:01:50 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=GUvnpfiZhMVwiEE94Hs6oTrcUS7b+PXBwnPsOAEcCEeSjsCv0AxxBpcvkBBadj5Ufy
         9ZF59CNJQR8FvVbc4R/Z7ysi5QDAqLbYvOXfgKaSo1hpYvG0dJnbBIDGJBgDJtx4dhXB
         kM955rY475eSZiKCFW37UFuT3bHEKJjugsqjiX7FceVwd6QOLDV4hfrj4aHRkRDjc534
         av4pMB/R0CspU3I1CP+MSx98aK8rbeQF2P3pU+RYyl/MVHaxwy4SwlbgdLTY3qehPNM/
         Ooja1sqyyl7f3DZdzmp7VeulZziyxf2Q0vk0MQvooVDr1W2jreMyFpLjf4L33sdeLX8Q
         rynQ==
X-Gm-Message-State: APjAAAV85hsaGpD0MkldvZKQD9As+mYJHGbF8MAZSmGZsg7ItwscVg8G
        8X2HkMYpM55od3KUvAxoS2BqEQjhCchua0qwYquC7mDYsSX+jm5OnlNbhu/h0vX0BP2EWLM/UaT
        FGzrPOB+h6ap5
X-Received: by 2002:a0c:b502:: with SMTP id d2mr14274256qve.110.1576875709436;
        Fri, 20 Dec 2019 13:01:49 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyGmM74vFWoaMutRKZgJghXCmC8qtpjQHdkgeFSxk+2RHIAsRSW7UnwJFLzo8noHTV7kdaZaw==
X-Received: by 2002:a0c:b502:: with SMTP id d2mr14274206qve.110.1576875708992;
        Fri, 20 Dec 2019 13:01:48 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 q25sm3243836qkq.88.2019.12.20.13.01.47
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:01:48 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>, peterx@redhat.com,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "Michael S . Tsirkin" <mst@redhat.com>
Subject: [PATCH v2 00/17] KVM: Dirty ring interface
Date: Fri, 20 Dec 2019 16:01:30 -0500
Message-Id: <20191220210147.49617-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring
(based on 5.4.0)

This is v2 of the dirty ring series, and also the first non-RFC
version of it.  I didn't put a changelog from v1-rfc because I feel
like it would be easier to go into the patchset comparing to read that
lengthy and probably helpless changelog.  However I do like to do a
summary here on what has majorly changed, and also some conclusions on
the previous v1 discussions.

======================

* Per-vm ring is dropped

For x86 (which is still the major focus for now), we found that kvmgt
is probably the only one that still writes to the guest without a vcpu
context.  It would be a complete pity if we keep the per-vm ring only
for kvmgt (who shouldn't write directly to guest via kvm api after
all...), so remove it.  Work should be ongoing in parallel to refactor
kvmgt to not use kvm apis like kvm_write_guest().

However I don't want to break kvmgt before it's fixed.  So this series
uses an interim way to solve this by fallback no-vcpu-context writes
to vcpu0 if there is.  So we will keep the interface clean (per-vcpu
only), while we don't break the code base.  After kvmgt is fixed, we
can probably even drop this special fallback and kvm->dirty_ring_lock.

* Waitqueue is still kept (for now)

We did plan to drop the waitqueue, however again if with kvmgt we
still have chance to ful-fill a ring (and I feel like it'll definitely
happen if we migrate a kvmgt guest).  This series will only trigger
the waitqueue mechanism if it's the special case (no-vcpu-context) and
actually it naturally avoids another mmu lock deadlock issue I've
encountered, which is good.

For vcpu context writes, now the series is even more strict that we'll
directly fail the KVM_RUN if the dirty ring is soft full, until the
userspace collects the dirty rings first.  That'll guarantee the ring
will never be full.  With that, I dropped KVM_REQ_DIRTY_RING_FULL
together because then it's not needed.

Potentially this could still also be used by ARM when there're code
paths that dump the ARM device information to the guests
(e.g. KVM_DEV_ARM_ITS_SAVE_TABLES).  We'll see.  No matter what, even
if the code is there, x86 (as long as without kvmgt) should never
trigger waitqueue.

Although the waitqueue is kept, I dropped the complete waitqueue test,
simply because now I can never trigger it without kvmgt...

* Why not virtio?

There's already some discussion during v1 patchset on whether it's
good to use virtio for the data path of delivering dirty pages [1].
I'd confess the only thing that we might consider to use is the vring
layout (because virtqueue is tightly bound to devices, while we don't
have a device contet here), however it's a pity that even we only use
the most low-level vring api it'll be at least iov based which is
already an overkill for dirty ring (which is literally an array of
addresses).  So I just kept things easy.

======================

About the patchset:

Patch 1-5:    Mostly cleanups
Patch 6,7:    Prepare for the dirty ring interface
Patch 8-10:   Dirty ring implementation (majorly patch 8)
Patch 11-17:  Test cases update

Please have a look, thanks.

[1] V1 is here: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (16):
  KVM: Remove kvm_read_guest_atomic()
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Cache as_id in kvm_memory_slot
  KVM: Add build-time error check on kvm_run size
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.txt                |  96 ++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   3 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu.c                            |   6 +
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            |   9 +
 include/linux/kvm_dirty_ring.h                |  57 +++
 include/linux/kvm_host.h                      |  44 +-
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  31 ++
 tools/include/uapi/linux/kvm.h                |  36 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 420 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  64 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   3 +
 virt/kvm/arm/arch_timer.c                     |   2 +-
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 201 +++++++++
 virt/kvm/kvm_main.c                           | 269 +++++++++--
 27 files changed, 1274 insertions(+), 145 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v2 00/17] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Dec 20 21:03:09 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306299
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9392139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:03:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ADF3820866
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:03:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EI6CuogJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727569AbfLTVDd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:03:33 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:44530 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727422AbfLTVDd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 16:03:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576875811;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=EI6CuogJuW9FJdb6AYr4kzF+RBIoFzkrsTpbZUKFFU20MMsERIYKXvBErjTwI/xfBkeC45
        mViLsao+quFbok4Kelcj/y7PoxSWYebMc9SVBHoiNhGe9Xw2aXAgNqq+prTl9e6ZKKanEn
        68koJ0D3aVhSwlp0/W+7EgNMggYz2r0=
Received: from mail-qv1-f70.google.com (mail-qv1-f70.google.com
 [209.85.219.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-392-P09gxEWTMouHffPBa7NynQ-1; Fri, 20 Dec 2019 16:03:29 -0500
X-MC-Unique: P09gxEWTMouHffPBa7NynQ-1
Received: by mail-qv1-f70.google.com with SMTP id p3so6725059qvt.9
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:03:29 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=k8860HT3ZHWcFOG0w9vYu3wn/+o6TgPIhy+6YAvZABFRHgBtxX2SSAWPZR9uOkZR0h
         Mh3rSCdAA6JfkfG+KG0xlJVPSOqb1Ybgb5QsevkWdt/WTP5rFHedWqjlUgoaR4o3BQOW
         3tCSt0EaOoSDH/R4G8EwfTNj3bdHQIdr7PNvX7hV9BhUD5yrpFQ510DFPVo2bxIYfpHj
         lYrLvmQRogpC5o4a3gZmK8VQl/jPVOJV4iU8+OJuMQa6FoZpQh/p1G9YO01w29/G1GdX
         HaqtrzrUNFQxRugvDM3nnLnsO9/Jd+Jkrnhgi97FOgip7seIzSlimvFgRXENaCzWT/kJ
         qVUA==
X-Gm-Message-State: APjAAAUej9srJPKE36mJ1soZbP6abTEtP3se5k4vr+8iUqdBsAM/5nOa
        bkzHlMwd7o3Fs9S7dTPE6IUQM1nfzZGuX5ClCMJpg8+K5Ach7dXDj9Lgioh5E9O7te4UyOsv3Qc
        aiChafCcK4smA
X-Received: by 2002:a05:620a:1249:: with SMTP id
 a9mr15371321qkl.147.1576875809373;
        Fri, 20 Dec 2019 13:03:29 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxNbYO3PVO9DiJlsDM5QA6EqOziw2PrJRG9BO1NsiPl6nlb5EN0gtRHmuQNruK5f+wtokIJaQ==
X-Received: by 2002:a05:620a:1249:: with SMTP id
 a9mr15371291qkl.147.1576875809014;
        Fri, 20 Dec 2019 13:03:29 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 a9sm3061018qtb.36.2019.12.20.13.03.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:03:28 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH v2 00/17] KVM: Dirty ring interface
Date: Fri, 20 Dec 2019 16:03:09 -0500
Message-Id: <20191220210326.49949-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring
(based on 5.4.0)

This is v2 of the dirty ring series, and also the first non-RFC
version of it.  I didn't put a changelog from v1-rfc because I feel
like it would be easier to go into the patchset comparing to read that
lengthy and probably helpless changelog.  However I do like to do a
summary here on what has majorly changed, and also some conclusions on
the previous v1 discussions.

======================

* Per-vm ring is dropped

For x86 (which is still the major focus for now), we found that kvmgt
is probably the only one that still writes to the guest without a vcpu
context.  It would be a complete pity if we keep the per-vm ring only
for kvmgt (who shouldn't write directly to guest via kvm api after
all...), so remove it.  Work should be ongoing in parallel to refactor
kvmgt to not use kvm apis like kvm_write_guest().

However I don't want to break kvmgt before it's fixed.  So this series
uses an interim way to solve this by fallback no-vcpu-context writes
to vcpu0 if there is.  So we will keep the interface clean (per-vcpu
only), while we don't break the code base.  After kvmgt is fixed, we
can probably even drop this special fallback and kvm->dirty_ring_lock.

* Waitqueue is still kept (for now)

We did plan to drop the waitqueue, however again if with kvmgt we
still have chance to ful-fill a ring (and I feel like it'll definitely
happen if we migrate a kvmgt guest).  This series will only trigger
the waitqueue mechanism if it's the special case (no-vcpu-context) and
actually it naturally avoids another mmu lock deadlock issue I've
encountered, which is good.

For vcpu context writes, now the series is even more strict that we'll
directly fail the KVM_RUN if the dirty ring is soft full, until the
userspace collects the dirty rings first.  That'll guarantee the ring
will never be full.  With that, I dropped KVM_REQ_DIRTY_RING_FULL
together because then it's not needed.

Potentially this could still also be used by ARM when there're code
paths that dump the ARM device information to the guests
(e.g. KVM_DEV_ARM_ITS_SAVE_TABLES).  We'll see.  No matter what, even
if the code is there, x86 (as long as without kvmgt) should never
trigger waitqueue.

Although the waitqueue is kept, I dropped the complete waitqueue test,
simply because now I can never trigger it without kvmgt...

* Why not virtio?

There's already some discussion during v1 patchset on whether it's
good to use virtio for the data path of delivering dirty pages [1].
I'd confess the only thing that we might consider to use is the vring
layout (because virtqueue is tightly bound to devices, while we don't
have a device contet here), however it's a pity that even we only use
the most low-level vring api it'll be at least iov based which is
already an overkill for dirty ring (which is literally an array of
addresses).  So I just kept things easy.

======================

About the patchset:

Patch 1-5:    Mostly cleanups
Patch 6,7:    Prepare for the dirty ring interface
Patch 8-10:   Dirty ring implementation (majorly patch 8)
Patch 11-17:  Test cases update

Please have a look, thanks.

[1] V1 is here: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (16):
  KVM: Remove kvm_read_guest_atomic()
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Cache as_id in kvm_memory_slot
  KVM: Add build-time error check on kvm_run size
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.txt                |  96 ++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   3 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu.c                            |   6 +
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            |   9 +
 include/linux/kvm_dirty_ring.h                |  57 +++
 include/linux/kvm_host.h                      |  44 +-
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  31 ++
 tools/include/uapi/linux/kvm.h                |  36 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 420 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  64 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   3 +
 virt/kvm/arm/arch_timer.c                     |   2 +-
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 201 +++++++++
 virt/kvm/kvm_main.c                           | 269 +++++++++--
 27 files changed, 1274 insertions(+), 145 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v2 00/17] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Dec 20 21:16:17 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11306335
Return-Path: <SRS0=DMs7=2K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0EF2714F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:17:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D706521655
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Dec 2019 21:17:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gcSQhsWO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727549AbfLTVQm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Dec 2019 16:16:42 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35109 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727498AbfLTVQl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Dec 2019 16:16:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576876599;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=gcSQhsWOQ/ldEFAKZ2ElMggKfgp/aqim/yMVT1bKbgWr7Pxq+R8SCPX59wnEUWPD88e6rK
        bL5nliVDue5WKbYQQ0V+sKuSnicHNM+DNttQvTyQZhvuLS/91pKXt3zil4cZtYxXRp1/ll
        scakZfvmrbXBM4X0GLRbgJ4ynBUZpco=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-7-ftOnXsU4PO6F8UhGRz6uBA-1; Fri, 20 Dec 2019 16:16:38 -0500
X-MC-Unique: ftOnXsU4PO6F8UhGRz6uBA-1
Received: by mail-qk1-f197.google.com with SMTP id 12so6716136qkf.20
        for <kvm@vger.kernel.org>; Fri, 20 Dec 2019 13:16:38 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=xpJ+lIL1WdaXz/BCzKHdKAiz9jNb7HE3HwznYCminRs=;
        b=oaCw1nt0624xmOUIDrOjjdSXxe8JJ+m2o1Qh2pahvUQ9UcKJbiL3P+fG+LgTTNCbct
         tCw9Pz6lEALSVTqCdh2Dt13te1cscJeM5uUH2JPRCDtqSRBCmwDje5wzpjlRvmv9wH4s
         U7K49GSP6JjqGr/A/9yiQkDezayWstfVM5CxrIU3Z/hRWS701DXkmAWTZN9zcp/7zLN9
         oBo4zwBAnQMreQvkE3Vd924nt8of7SyCOOruPGgmrTqbKIm/qI7TnE1y78LSeBPLwP9W
         AV1YrMlZzG0pKG/U1Bk7PLcMkvMKqFt6gr3dRignoRPyyxbS1tOGwFrKMmEtr+ccyGG9
         ltPg==
X-Gm-Message-State: APjAAAU9srFAYM9nqbr9T+ZOBzrCUATvx85YCL9TvmqpcX9PmkcS7r8/
        jNykoGzGxASW+sXR7pNyOGx/RfaRuDGMrRJ1poj0h3Y+kM+HYY1GlVv3harWbHRH2NBBPJ45GUd
        ERxBZSH+bu7W7
X-Received: by 2002:a05:6214:209:: with SMTP id
 i9mr14198480qvt.54.1576876597124;
        Fri, 20 Dec 2019 13:16:37 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxYOgIqdrdoNfnGAtJZNMuyyAyAE7Jhe9XTqP9gOz9zR3whPpLQGpW7Nmhu3cOcwMYCB0sbaQ==
X-Received: by 2002:a05:6214:209:: with SMTP id
 i9mr14198444qvt.54.1576876596748;
        Fri, 20 Dec 2019 13:16:36 -0800 (PST)
Received: from xz-x1.redhat.com ([104.156.64.74])
        by smtp.gmail.com with ESMTPSA id
 d25sm3385231qtq.11.2019.12.20.13.16.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Dec 2019 13:16:36 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Michael S . Tsirkin" <mst@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>, peterx@redhat.com,
        Jason Wang <jasowang@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>
Subject: [PATCH v2 00/17] KVM: Dirty ring interface
Date: Fri, 20 Dec 2019 16:16:17 -0500
Message-Id: <20191220211634.51231-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Branch is here: https://github.com/xzpeter/linux/tree/kvm-dirty-ring
(based on 5.4.0)

This is v2 of the dirty ring series, and also the first non-RFC
version of it.  I didn't put a changelog from v1-rfc because I feel
like it would be easier to go into the patchset comparing to read that
lengthy and probably helpless changelog.  However I do like to do a
summary here on what has majorly changed, and also some conclusions on
the previous v1 discussions.

======================

* Per-vm ring is dropped

For x86 (which is still the major focus for now), we found that kvmgt
is probably the only one that still writes to the guest without a vcpu
context.  It would be a complete pity if we keep the per-vm ring only
for kvmgt (who shouldn't write directly to guest via kvm api after
all...), so remove it.  Work should be ongoing in parallel to refactor
kvmgt to not use kvm apis like kvm_write_guest().

However I don't want to break kvmgt before it's fixed.  So this series
uses an interim way to solve this by fallback no-vcpu-context writes
to vcpu0 if there is.  So we will keep the interface clean (per-vcpu
only), while we don't break the code base.  After kvmgt is fixed, we
can probably even drop this special fallback and kvm->dirty_ring_lock.

* Waitqueue is still kept (for now)

We did plan to drop the waitqueue, however again if with kvmgt we
still have chance to ful-fill a ring (and I feel like it'll definitely
happen if we migrate a kvmgt guest).  This series will only trigger
the waitqueue mechanism if it's the special case (no-vcpu-context) and
actually it naturally avoids another mmu lock deadlock issue I've
encountered, which is good.

For vcpu context writes, now the series is even more strict that we'll
directly fail the KVM_RUN if the dirty ring is soft full, until the
userspace collects the dirty rings first.  That'll guarantee the ring
will never be full.  With that, I dropped KVM_REQ_DIRTY_RING_FULL
together because then it's not needed.

Potentially this could still also be used by ARM when there're code
paths that dump the ARM device information to the guests
(e.g. KVM_DEV_ARM_ITS_SAVE_TABLES).  We'll see.  No matter what, even
if the code is there, x86 (as long as without kvmgt) should never
trigger waitqueue.

Although the waitqueue is kept, I dropped the complete waitqueue test,
simply because now I can never trigger it without kvmgt...

* Why not virtio?

There's already some discussion during v1 patchset on whether it's
good to use virtio for the data path of delivering dirty pages [1].
I'd confess the only thing that we might consider to use is the vring
layout (because virtqueue is tightly bound to devices, while we don't
have a device contet here), however it's a pity that even we only use
the most low-level vring api it'll be at least iov based which is
already an overkill for dirty ring (which is literally an array of
addresses).  So I just kept things easy.

======================

About the patchset:

Patch 1-5:    Mostly cleanups
Patch 6,7:    Prepare for the dirty ring interface
Patch 8-10:   Dirty ring implementation (majorly patch 8)
Patch 11-17:  Test cases update

Please have a look, thanks.

[1] V1 is here: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com

Paolo Bonzini (1):
  KVM: Move running VCPU from ARM to common code

Peter Xu (16):
  KVM: Remove kvm_read_guest_atomic()
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Cache as_id in kvm_memory_slot
  KVM: Add build-time error check on kvm_run size
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.txt                |  96 ++++
 arch/arm/include/asm/kvm_host.h               |   2 -
 arch/arm64/include/asm/kvm_host.h             |   2 -
 arch/x86/include/asm/kvm_host.h               |   3 +
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu.c                            |   6 +
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  25 +-
 arch/x86/kvm/x86.c                            |   9 +
 include/linux/kvm_dirty_ring.h                |  57 +++
 include/linux/kvm_host.h                      |  44 +-
 include/trace/events/kvm.h                    |  78 ++++
 include/uapi/linux/kvm.h                      |  31 ++
 tools/include/uapi/linux/kvm.h                |  36 ++
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   2 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 420 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  64 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   3 +
 virt/kvm/arm/arch_timer.c                     |   2 +-
 virt/kvm/arm/arm.c                            |  29 --
 virt/kvm/arm/perf.c                           |   6 +-
 virt/kvm/arm/vgic/vgic-mmio.c                 |  15 +-
 virt/kvm/dirty_ring.c                         | 201 +++++++++
 virt/kvm/kvm_main.c                           | 269 +++++++++--
 27 files changed, 1274 insertions(+), 145 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
