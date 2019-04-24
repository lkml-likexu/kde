#### [PATCH 01/56] KVM: Documentation: Document arm64 core registers in detail
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Dave Martin <Dave.Martin@arm.com>

Since the the sizes of individual members of the core arm64
registers vary, the list of register encodings that make sense is
not a simple linear sequence.

To clarify which encodings to use, this patch adds a brief list
to the documentation.

Signed-off-by: Dave Martin <Dave.Martin@arm.com>
Reviewed-by: Julien Grall <julien.grall@arm.com>
Reviewed-by: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 Documentation/virtual/kvm/api.txt | 24 ++++++++++++++++++++++++
 1 file changed, 24 insertions(+)

```
#### [PATCH kvmtool 1/2] list: Clean up ghost socket files
##### From: Andre Przywara <andre.przywara@arm.com>

```c
When kvmtool (or the host kernel) crashes or gets killed, we cannot
automatically remove the socket file we created for that VM.
A later call of "lkvm list" iterates over all those files and complains
about those "ghost socket files", as there is no one listening on
the other side. Also sometimes the automatic guest name generation
happens to generate the same name again, so an unrelated "lkvm run"
later complains and stops, which is bad for automation.

As the only code doing a listen() on this socket is kvmtool upon VM
*creation*, such an orphaned socket file will never come back to life,
so we can as well unlink() those sockets in the code. This spares the
user the messages and the burden of doing it herself.
We keep a message in the code to notify the user of this.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 kvm-ipc.c | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] kvm: x86: Move kvm_set_mmio_spte_mask() from x86.c to mmu.c
##### From: Kai Huang <kai.huang@linux.intel.com>

```c
As a prerequisite to fix several SPTE reserved bits related calculation
errors caused by MKTME, which requires kvm_set_mmio_spte_mask() to use
local static variable defined in mmu.c.

Also move call site of kvm_set_mmio_spte_mask() from kvm_arch_init() to
kvm_mmu_module_init() so that kvm_set_mmio_spte_mask() can be static.

Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Kai Huang <kai.huang@linux.intel.com>
---
 arch/x86/kvm/mmu.c | 31 +++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c | 31 -------------------------------
 2 files changed, 31 insertions(+), 31 deletions(-)

```
#### [GIT PULL] KVM/arm updates for 5.2
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

This is the 5.2 pull request for KVM/arm. Pretty substential update
this time, as we finally have SVE support in guests, which makes the
bulk of the changes. Additionnaly, we have the ARMv8.3 Pointer
Authentication support for guests, and some better support for perf
modifiers.

Please pull,

	M.

The following changes since commit 8c2ffd9174779014c3fe1f96d9dc3641d9175f00:

  Linux 5.1-rc2 (2019-03-24 14:02:26 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-for-v5.2

for you to fetch changes up to 9eecfc22e0bfc7a4c8ca007f083f0ae492d6e891:

  KVM: arm64: Fix ptrauth ID register masking logic (2019-05-01 17:21:51 +0100)

----------------------------------------------------------------
KVM/arm updates for 5.2

- guest SVE support
- guest Pointer Authentication support
- Better discrimination of perf counters between host and guests

----------------------------------------------------------------
Amit Daniel Kachhap (3):
      KVM: arm64: Add a vcpu flag to control ptrauth for guest
      KVM: arm64: Add userspace flag to enable pointer authentication
      KVM: arm64: Add capability to advertise ptrauth for guest

Andrew Murray (9):
      arm64: arm_pmu: Remove unnecessary isb instruction
      arm64: KVM: Encapsulate kvm_cpu_context in kvm_host_data
      arm64: KVM: Add accessors to track guest/host only counters
      arm64: arm_pmu: Add !VHE support for exclude_host/exclude_guest attributes
      arm64: KVM: Enable !VHE support for :G/:H perf event modifiers
      arm64: KVM: Enable VHE support for :G/:H perf event modifiers
      arm64: KVM: Avoid isb's by using direct pmxevtyper sysreg
      arm64: docs: Document perf event attributes
      arm64: KVM: Fix perf cycle counter support for VHE

Dave Martin (41):
      KVM: Documentation: Document arm64 core registers in detail
      arm64: fpsimd: Always set TIF_FOREIGN_FPSTATE on task state flush
      KVM: arm64: Delete orphaned declaration for __fpsimd_enabled()
      KVM: arm64: Refactor kvm_arm_num_regs() for easier maintenance
      KVM: arm64: Add missing #includes to kvm_host.h
      arm64/sve: Clarify role of the VQ map maintenance functions
      arm64/sve: Check SVE virtualisability
      arm64/sve: Enable SVE state tracking for non-task contexts
      KVM: arm64: Add a vcpu flag to control SVE visibility for the guest
      KVM: arm64: Propagate vcpu into read_id_reg()
      KVM: arm64: Support runtime sysreg visibility filtering
      KVM: arm64/sve: System register context switch and access support
      KVM: arm64/sve: Context switch the SVE registers
      KVM: Allow 2048-bit register access via ioctl interface
      KVM: arm64: Add missing #include of <linux/string.h> in guest.c
      KVM: arm64: Factor out core register ID enumeration
      KVM: arm64: Reject ioctl access to FPSIMD V-regs on SVE vcpus
      KVM: arm64/sve: Add SVE support to register access ioctl interface
      KVM: arm64: Enumerate SVE register indices for KVM_GET_REG_LIST
      arm64/sve: In-kernel vector length availability query interface
      KVM: arm/arm64: Add hook for arch-specific KVM initialisation
      KVM: arm/arm64: Add KVM_ARM_VCPU_FINALIZE ioctl
      KVM: arm64/sve: Add pseudo-register for the guest's vector lengths
      KVM: arm64/sve: Allow userspace to enable SVE for vcpus
      KVM: arm64: Add a capability to advertise SVE support
      KVM: Document errors for KVM_GET_ONE_REG and KVM_SET_ONE_REG
      KVM: arm64/sve: Document KVM API extensions for SVE
      arm64/sve: Clarify vq map semantics
      KVM: arm/arm64: Demote kvm_arm_init_arch_resources() to just set up SVE
      KVM: arm: Make vcpu finalization stubs into inline functions
      KVM: arm64/sve: sys_regs: Demote redundant vcpu_has_sve() checks to WARNs
      KVM: arm64/sve: Clean up UAPI register ID definitions
      KVM: arm64/sve: Miscellaneous tidyups in guest.c
      KVM: arm64/sve: Make register ioctl access errors more consistent
      KVM: arm64/sve: WARN when avoiding divide-by-zero in sve_reg_to_region()
      KVM: arm64/sve: Simplify KVM_REG_ARM64_SVE_VLS array sizing
      KVM: arm64/sve: Explain validity checks in set_sve_vls()
      KVM: arm/arm64: Clean up vcpu finalization function parameter naming
      KVM: Clarify capability requirements for KVM_ARM_VCPU_FINALIZE
      KVM: Clarify KVM_{SET,GET}_ONE_REG error code documentation
      KVM: arm64: Clarify access behaviour for out-of-range SVE register slice IDs

Kristina Martsenko (1):
      KVM: arm64: Fix ptrauth ID register masking logic

Marc Zyngier (1):
      arm64: KVM: Fix system register enumeration

Mark Rutland (1):
      KVM: arm/arm64: Context-switch ptrauth registers

 Documentation/arm64/perf.txt                   |  85 +++++
 Documentation/arm64/pointer-authentication.txt |  22 +-
 Documentation/virtual/kvm/api.txt              | 178 +++++++++++
 arch/arm/include/asm/kvm_emulate.h             |   2 +
 arch/arm/include/asm/kvm_host.h                |  26 +-
 arch/arm64/Kconfig                             |   6 +-
 arch/arm64/include/asm/fpsimd.h                |  29 +-
 arch/arm64/include/asm/kvm_asm.h               |   3 +-
 arch/arm64/include/asm/kvm_emulate.h           |  16 +
 arch/arm64/include/asm/kvm_host.h              | 101 +++++-
 arch/arm64/include/asm/kvm_hyp.h               |   1 -
 arch/arm64/include/asm/kvm_ptrauth.h           | 111 +++++++
 arch/arm64/include/asm/sysreg.h                |   3 +
 arch/arm64/include/uapi/asm/kvm.h              |  43 +++
 arch/arm64/kernel/asm-offsets.c                |   7 +
 arch/arm64/kernel/cpufeature.c                 |   2 +-
 arch/arm64/kernel/fpsimd.c                     | 179 +++++++----
 arch/arm64/kernel/perf_event.c                 |  50 ++-
 arch/arm64/kernel/signal.c                     |   5 -
 arch/arm64/kvm/Makefile                        |   2 +-
 arch/arm64/kvm/fpsimd.c                        |  17 +-
 arch/arm64/kvm/guest.c                         | 415 +++++++++++++++++++++++--
 arch/arm64/kvm/handle_exit.c                   |  36 ++-
 arch/arm64/kvm/hyp/entry.S                     |  15 +
 arch/arm64/kvm/hyp/switch.c                    |  80 ++++-
 arch/arm64/kvm/pmu.c                           | 239 ++++++++++++++
 arch/arm64/kvm/reset.c                         | 167 +++++++++-
 arch/arm64/kvm/sys_regs.c                      | 183 +++++++++--
 arch/arm64/kvm/sys_regs.h                      |  25 ++
 include/uapi/linux/kvm.h                       |   7 +
 virt/kvm/arm/arm.c                             |  40 ++-
 31 files changed, 1914 insertions(+), 181 deletions(-)
 create mode 100644 Documentation/arm64/perf.txt
 create mode 100644 arch/arm64/include/asm/kvm_ptrauth.h
 create mode 100644 arch/arm64/kvm/pmu.c

From patchwork Fri May  3 12:43:33 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 10928529
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 142C91398
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 May 2019 12:44:52 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 044D9285B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 May 2019 12:44:52 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id ECD31285BD; Fri,  3 May 2019 12:44:51 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 55997285B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 May 2019 12:44:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727952AbfECMou (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 May 2019 08:44:50 -0400
Received: from foss.arm.com ([217.140.101.70]:60006 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727032AbfECMou (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 May 2019 08:44:50 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.72.51.249])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id CC1D0374;
        Fri,  3 May 2019 05:44:49 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 95A253F220;
        Fri,  3 May 2019 05:44:46 -0700 (PDT)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Amit Daniel Kachhap <amit.kachhap@arm.com>,
 Andrew Jones <drjones@redhat.com>, Andrew Murray <andrew.murray@arm.com>,
 Christoffer Dall <christoffer.dall@arm.com>,
 Dave Martin <Dave.Martin@arm.com>, Julien Grall <julien.grall@arm.com>,
 Julien Thierry <julien.thierry@arm.com>,
 Kristina Martsenko <kristina.martsenko@arm.com>,
 Mark Rutland <mark.rutland@arm.com>,
 Peter Maydell <peter.maydell@linaro.org>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, Will Deacon <will.deacon@arm.com>,
 "zhang . lei" <zhang.lei@jp.fujitsu.com>,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org
Subject: [PATCH 02/56] arm64: fpsimd: Always set TIF_FOREIGN_FPSTATE on task
 state flush
Date: Fri,  3 May 2019 13:43:33 +0100
Message-Id: <20190503124427.190206-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190503124427.190206-1-marc.zyngier@arm.com>
References: <20190503124427.190206-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Dave Martin <Dave.Martin@arm.com>

This patch updates fpsimd_flush_task_state() to mirror the new
semantics of fpsimd_flush_cpu_state() introduced by commit
d8ad71fa38a9 ("arm64: fpsimd: Fix TIF_FOREIGN_FPSTATE after
invalidating cpu regs").  Both functions now implicitly set
TIF_FOREIGN_FPSTATE to indicate that the task's FPSIMD state is not
loaded into the cpu.

As a side-effect, fpsimd_flush_task_state() now sets
TIF_FOREIGN_FPSTATE even for non-running tasks.  In the case of
non-running tasks this is not useful but also harmless, because the
flag is live only while the corresponding task is running.  This
function is not called from fast paths, so special-casing this for
the task == current case is not really worth it.

Compiler barriers previously present in restore_sve_fpsimd_context()
are pulled into fpsimd_flush_task_state() so that it can be safely
called with preemption enabled if necessary.

Explicit calls to set TIF_FOREIGN_FPSTATE that accompany
fpsimd_flush_task_state() calls and are now redundant are removed
as appropriate.

fpsimd_flush_task_state() is used to get exclusive access to the
representation of the task's state via task_struct, for the purpose
of replacing the state.  Thus, the call to this function should
happen before manipulating fpsimd_state or sve_state etc. in
task_struct.  Anomalous cases are reordered appropriately in order
to make the code more consistent, although there should be no
functional difference since these cases are protected by
local_bh_disable() anyway.

Signed-off-by: Dave Martin <Dave.Martin@arm.com>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
Reviewed-by: Julien Grall <julien.grall@arm.com>
Tested-by: zhang.lei <zhang.lei@jp.fujitsu.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kernel/fpsimd.c | 25 +++++++++++++++++++------
 arch/arm64/kernel/signal.c |  5 -----
 2 files changed, 19 insertions(+), 11 deletions(-)

```
#### [GIT PULL] KVM fixes for 5.1-rc8 or final
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 7a223e06b1a411cef6c4cd7a9b9a33c8d225b10e:

  KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing (2019-04-16 15:38:08 +0200)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e8ab8d24b488632d07ce5ddb261f1d454114415b:

  KVM: nVMX: Fix size checks in vmx_set_nested_state (2019-05-01 00:43:44 +0200)

----------------------------------------------------------------
* PPC and ARM bugfixes from submaintainers
* Fix old Windows versions on AMD (recent regression)
* Fix old Linux versions on processors without EPT
* Fixes for LAPIC timer optimizations

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Book3S: Protect memslots while validating user address

Andrew Jones (2):
      KVM: arm/arm64: Ensure vcpu target is unset on reset failure
      Documentation: kvm: fix dirty log ioctl arch lists

Christoffer Dall (1):
      KVM: arm/arm64: Don't emulate virtual timers on userspace ioctls

Jim Mattson (1):
      KVM: nVMX: Fix size checks in vmx_set_nested_state

Liran Alon (1):
      KVM: x86: Consider LAPIC TSC-Deadline timer expired if deadline too short

Marc Zyngier (1):
      KVM: arm/arm64: vgic-v3: Retire pending interrupts on disabling LPIs

Paolo Bonzini (3):
      Merge tag 'kvm-ppc-fixes-5.1-1' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: fix KVM_CLEAR_DIRTY_LOG for memory slots of unaligned size
      Merge tag 'kvmarm-fixes-for-5.1-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

Rick Edgecombe (1):
      KVM: VMX: Move RSB stuffing to before the first RET after VM-Exit

Sean Christopherson (6):
      KVM: lapic: Disable timer advancement if adaptive tuning goes haywire
      KVM: lapic: Track lapic timer advance per vCPU
      KVM: lapic: Allow user to disable adaptive tuning of timer advancement
      KVM: lapic: Convert guest TSC to host time domain if necessary
      KVM: x86: Whitelist port 0x7e for pre-incrementing %rip
      KVM: lapic: Check for in-kernel LAPIC before deferencing apic pointer

Suraj Jitindar Singh (1):
      KVM: PPC: Book3S HV: Perserve PSSCR FAKE_SUSPEND bit on guest exit

Suzuki K Poulose (1):
      kvm: arm: Skip stage2 huge mappings for unaligned ipa backed by THP

Vitaly Kuznetsov (3):
      x86: kvm: hyper-v: deal with buggy TLB flush requests from WS2012
      x86/kvm/mmu: reset MMU context when 32-bit guest switches PAE
      KVM: selftests: make hyperv_cpuid test pass on AMD

Wei Huang (1):
      KVM: arm/arm64: arch_timer: Fix CNTP_TVAL calculation

 Documentation/virtual/kvm/api.txt                 | 11 ++--
 arch/powerpc/kvm/book3s_64_vio.c                  |  6 +-
 arch/powerpc/kvm/book3s_hv.c                      |  4 +-
 arch/x86/include/asm/kvm_host.h                   |  1 +
 arch/x86/include/uapi/asm/kvm.h                   |  1 +
 arch/x86/kvm/hyperv.c                             | 11 +++-
 arch/x86/kvm/lapic.c                              | 73 ++++++++++++++++-------
 arch/x86/kvm/lapic.h                              |  4 +-
 arch/x86/kvm/mmu.c                                |  1 +
 arch/x86/kvm/vmx/nested.c                         |  4 +-
 arch/x86/kvm/vmx/vmenter.S                        | 12 ++++
 arch/x86/kvm/vmx/vmx.c                            |  7 +--
 arch/x86/kvm/x86.c                                | 36 ++++++++---
 arch/x86/kvm/x86.h                                |  2 -
 tools/testing/selftests/kvm/dirty_log_test.c      |  9 ++-
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c |  9 ++-
 virt/kvm/arm/arch_timer.c                         | 17 +++---
 virt/kvm/arm/arm.c                                | 11 +++-
 virt/kvm/arm/mmu.c                                |  6 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                  |  3 +
 virt/kvm/arm/vgic/vgic.c                          | 21 +++++++
 virt/kvm/arm/vgic/vgic.h                          |  1 +
 virt/kvm/kvm_main.c                               |  7 ++-
 23 files changed, 192 insertions(+), 65 deletions(-)
```
#### [PATCH v6 1/3] arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Recent commits added the explicit notion of "workaround not required" to
the state of the Spectre v2 (aka. BP_HARDENING) workaround, where we
just had "needed" and "unknown" before.

Export this knowledge to the rest of the kernel and enhance the existing
kvm_arm_harden_branch_predictor() to report this new state as well.
Export this new state to guests when they use KVM's firmware interface
emulation.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arch/arm/include/asm/kvm_host.h     | 12 +++++++++---
 arch/arm64/include/asm/cpufeature.h |  6 ++++++
 arch/arm64/include/asm/kvm_host.h   | 16 ++++++++++++++--
 arch/arm64/kernel/cpu_errata.c      | 23 ++++++++++++++++++-----
 virt/kvm/arm/psci.c                 | 10 +++++++++-
 5 files changed, 56 insertions(+), 11 deletions(-)

```
#### [PATCH kvmtool 1/4] vfio: remove spurious ampersand
##### From: Andre Przywara <andre.przywara@arm.com>

```c
As clang rightfully pointed out, the ampersand in front of this member
looks wrong.

Remove it so we actually really compare against the count being 0.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 vfio/pci.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: x86: Fix L1TF mitigation for shadow MMU
##### From: Kai Huang <kai.huang@linux.intel.com>

```c
Currently KVM sets 5 most significant bits of physical address bits
reported by CPUID (boot_cpu_data.x86_phys_bits) for nonpresent or
reserved bits SPTE to mitigate L1TF attack from guest when using shadow
MMU. However for some particular Intel CPUs the physical address bits
of internal cache is greater than physical address bits reported by
CPUID.

Use the kernel's existing boot_cpu_data.x86_cache_bits to determine the
five most significant bits. Doing so improves KVM's L1TF mitigation in
the unlikely scenario that system RAM overlaps the high order bits of
the "real" physical address space as reported by CPUID. This aligns with
the kernel's warnings regarding L1TF mitigation, e.g. in the above
scenario the kernel won't warn the user about lack of L1TF mitigation
if x86_cache_bits is greater than x86_phys_bits.

Also initialize shadow_nonpresent_or_rsvd_mask explicitly to make it
consistent with other 'shadow_{xxx}_mask', and opportunistically add a
WARN once if KVM's L1TF mitigation cannot be applied on a system that
is marked as being susceptible to L1TF.

Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Kai Huang <kai.huang@linux.intel.com>
---

This patch was splitted from old patch I sent out around 2 weeks ago:

kvm: x86: Fix several SPTE mask calculation errors caused by MKTME

After reviewing with Sean Christopherson it's better to split this out,
since the logic in this patch is independent. And maybe this patch should
also be into stable.

---
 arch/x86/kvm/mmu.c | 18 +++++++++++++-----
 1 file changed, 13 insertions(+), 5 deletions(-)

```
#### [PATCH] mm: add account_locked_vm utility functionX-Mailer: git-send-email 2.21.0
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
locked_vm accounting is done roughly the same way in five places, so
unify them in a helper.  Standardize the debug prints, which vary
slightly.  Error codes stay the same, so user-visible behavior does too.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
Cc: Alan Tull <atull@kernel.org>
Cc: Alexey Kardashevskiy <aik@ozlabs.ru>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Christoph Lameter <cl@linux.com>
Cc: Christophe Leroy <christophe.leroy@c-s.fr>
Cc: Davidlohr Bueso <dave@stgolabs.net>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Moritz Fischer <mdf@kernel.org>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Steve Sistare <steven.sistare@oracle.com>
Cc: Wu Hao <hao.wu@intel.com>
Cc: linux-mm@kvack.org
Cc: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Cc: linuxppc-dev@lists.ozlabs.org
Cc: linux-fpga@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
---

Based on v5.1-rc7.  Tested with the vfio type1 driver.  Any feedback
welcome.

Andrew, this one patch replaces these six from [1]:

    mm-change-locked_vms-type-from-unsigned-long-to-atomic64_t.patch
    vfio-type1-drop-mmap_sem-now-that-locked_vm-is-atomic.patch
    vfio-spapr_tce-drop-mmap_sem-now-that-locked_vm-is-atomic.patch
    fpga-dlf-afu-drop-mmap_sem-now-that-locked_vm-is-atomic.patch
    kvm-book3s-drop-mmap_sem-now-that-locked_vm-is-atomic.patch
    powerpc-mmu-drop-mmap_sem-now-that-locked_vm-is-atomic.patch

That series converts locked_vm to an atomic, but on closer inspection causes at
least one accounting race in mremap, and fixing it just for this type
conversion came with too much ugly in the core mm to justify, especially when
the right long-term fix is making these drivers use pinned_vm instead.

Christophe's suggestion of cmpxchg[2] does prevent the races he
mentioned for pinned_vm, but others would still remain.  In perf_mmap
and the hfi1 driver, pinned_vm is checked against the rlimit racily and
then later increased when the pinned_vm originally read may have gone
stale.  Any fixes for that, that I could think of, seem about as good as
what's there now, so I left it.  I have a patch that uses cmpxchg with
pinned_vm if others feel strongly that the aforementioned races should
be fixed.

Daniel

[1] https://lore.kernel.org/linux-mm/20190402204158.27582-1-daniel.m.jordan@oracle.com/
[2] https://lore.kernel.org/linux-mm/964bd5b0-f1e5-7bf0-5c58-18e75c550841@c-s.fr/

 arch/powerpc/kvm/book3s_64_vio.c    | 44 +++---------------------
 arch/powerpc/mm/mmu_context_iommu.c | 41 +++-------------------
 drivers/fpga/dfl-afu-dma-region.c   | 53 +++--------------------------
 drivers/vfio/vfio_iommu_spapr_tce.c | 52 +++++-----------------------
 drivers/vfio/vfio_iommu_type1.c     | 23 ++++---------
 include/linux/mm.h                  | 19 +++++++++++
 mm/util.c                           | 48 ++++++++++++++++++++++++++
 7 files changed, 94 insertions(+), 186 deletions(-)


base-commit: 37624b58542fb9f2d9a70e6ea006ef8a5f66c30b

```
#### [PATCH v2 1/7] s390: vfio-ap: wait for queue empty on queue reset
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Refactors the AP queue reset function to wait until the queue is empty
after the PQAP(ZAPQ) instruction is executed to zero out the queue as
required by the AP architecture.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 35 ++++++++++++++++++++++++++++++++---
 1 file changed, 32 insertions(+), 3 deletions(-)

```
#### [PATCH 1/7] s390/cio: Update SCSW if it points to the end of the chain
##### From: Eric Farman <farman@linux.ibm.com>

```c
Per the POPs [1], when processing an interrupt the SCSW.CPA field of an
IRB generally points to 8 bytes after the last CCW that was executed
(there are exceptions, but this is the most common behavior).

In the case of an error, this points us to the first un-executed CCW
in the chain.  But in the case of normal I/O, the address points beyond
the end of the chain.  While the guest generally only cares about this
when possibly restarting a channel program after error recovery, we
should convert the address even in the good scenario so that we provide
a consistent, valid, response upon I/O completion.

[1] Figure 16-6 in SA22-7832-11.  The footnotes in that table also state
that this is true even if the resulting address is invalid or protected,
but moving to the end of the guest chain should not be a surprise.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] svm/avic: Allow avic_vcpu_load logic to support host APIC ID 255
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Current logic does not allow VCPU to be loaded onto CPU with
APIC ID 255. This should be allowed since the host physical APIC ID
field in the AVIC Physical APIC table entry is an 8-bit value,
and APIC ID 255 is valid in system with x2APIC enabled.

Instead, do not allow VCPU load if the host APIC ID cannot be
represented by an 8-bit value.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] svm/avic: Do not send AVIC doorbell to selfThread-Topic: [PATCH] svm/avic: Do not send AVIC doorbell to self
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
AVIC doorbell is used to notify a running vCPU that interrupts
has been injected into the vCPU AVIC backing page. Current logic
checks only if a VCPU is running before sending a doorbell.
However, the doorbell is not necessary if the destination
CPU is itself.

Add logic to check currently running CPU before sending doorbell.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 11 +++++++----
 1 file changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH v2] x86: Some cleanup of delay() and io_delay()
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

There is no guarantee that a self-IPI would be delivered immediately.
In eventinj, io_delay() is called after self-IPI is generated but does
nothing.

In general, there is mess in regard to delay() and io_delay(). There are
two definitions of delay() and they do not really look on the timestamp
counter and instead count invocations of "pause" (or even "nop"), which
might be different on different CPUs/setups, for example due to
different pause-loop-exiting configurations.

To address these issues change io_delay() to really do a delay, based on
timestamp counter, and move common functions into delay.[hc].

Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/delay.c | 9 ++++++---
 lib/x86/delay.h | 7 +++++++
 x86/eventinj.c  | 5 +----
 x86/ioapic.c    | 8 +-------
 4 files changed, 15 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/4] lib/alloc_page: Zero allocated pages
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

One of the most important properties of tests is reproducibility. For
tests to be reproducible, the same environment should be set on each
test invocation.

When it comes to memory content, this is not exactly the case in
kvm-unit-tests. The tests might, mistakenly or intentionally, assume
that memory is zeroed (by the BIOS or KVM).  However, failures might not
be reproducible if this assumption is broken.

As an example, consider x86 do_iret(), which mistakenly does not push
SS:RSP onto the stack on 64-bit mode, although they are popped
unconditionally on iret.

Do not assume that memory is zeroed. Clear it once it is allocated to
allow tests to easily be reproduced.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/alloc_page.c | 4 ++++
 1 file changed, 4 insertions(+)

```
