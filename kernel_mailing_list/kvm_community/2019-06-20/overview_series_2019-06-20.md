#### [PATCH 1/4] KVM: arm64: Implement vq_present() as a macro
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Viresh Kumar <viresh.kumar@linaro.org>

This routine is a one-liner and doesn't really need to be function and
can be implemented as a macro.

Suggested-by: Dave Martin <Dave.Martin@arm.com>
Reviewed-by: Dave Martin <Dave.Martin@arm.com>
Signed-off-by: Viresh Kumar <viresh.kumar@linaro.org>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/guest.c | 12 +++---------
 1 file changed, 3 insertions(+), 9 deletions(-)

```
#### [RFC PATCH v2 01/11] KVM: SVM: Add KVM_SEV SEND_START commandThread-Topic: [RFC PATCH v2 01/11] KVM: SVM: Add KVM_SEV SEND_START command
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 .../virtual/kvm/amd-memory-encryption.rst     |  27 +++++
 arch/x86/kvm/svm.c                            | 105 ++++++++++++++++++
 include/uapi/linux/kvm.h                      |  12 ++
 3 files changed, 144 insertions(+)

```
#### [RFC PATCH v1 01/12] linux-headers: update kernel header to include SEV migration commands
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---
 linux-headers/linux/kvm.h | 53 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 53 insertions(+)

```
#### [GIT PULL] KVM/arm fixes for 5.2-rc6
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

Here's the second (and hopefully last) set of fixes for v5.2. We have
our usual timer fix (we obviously will never get it right), a memory
leak plug, a sysreg reporting fix, and an small SVE cleanup.

Please pull.

	M.

The following changes since commit 623e1528d4090bd1abaf93ec46f047dee9a6fb32:

  KVM: arm/arm64: Move cc/it checks under hyp's Makefile to avoid instrumentation (2019-05-24 14:53:20 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.2-2

for you to fetch changes up to e4e5a865e9a9e8e47ac1959b629e9f3ae3b062f2:

  KVM: arm/arm64: Fix emulated ptimer irq injection (2019-06-19 15:47:52 +0100)

----------------------------------------------------------------
KVM/arm fixes for 5.2, take #2

- SVE cleanup killing a warning with ancient GCC versions
- Don't report non-existent system registers to userspace
- Fix memory leak when freeing the vgic ITS
- Properly lower the interrupt on the emulated physical timer

----------------------------------------------------------------
Andrew Jones (1):
      KVM: arm/arm64: Fix emulated ptimer irq injection

Dave Martin (2):
      KVM: arm64: Filter out invalid core register IDs in KVM_GET_REG_LIST
      KVM: arm/arm64: vgic: Fix kvm_device leak in vgic_its_destroy

Viresh Kumar (1):
      KVM: arm64: Implement vq_present() as a macro

 arch/arm64/kvm/guest.c       | 65 +++++++++++++++++++++++++++++---------------
 virt/kvm/arm/arch_timer.c    |  5 ++--
 virt/kvm/arm/vgic/vgic-its.c |  1 +
 3 files changed, 47 insertions(+), 24 deletions(-)

From patchwork Thu Jun 20 11:22:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 11006505
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3890A14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Jun 2019 11:23:17 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 2A71A1FF60
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Jun 2019 11:23:17 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 1EB12286BE; Thu, 20 Jun 2019 11:23:17 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 8793C286C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Jun 2019 11:23:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726704AbfFTLXP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Jun 2019 07:23:15 -0400
Received: from foss.arm.com ([217.140.110.172]:60556 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726602AbfFTLXP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Jun 2019 07:23:15 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 7A2EF11B3;
        Thu, 20 Jun 2019 04:23:14 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.197.61])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 082F73F718;
        Thu, 20 Jun 2019 04:23:12 -0700 (PDT)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Andrew Jones <drjones@redhat.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Viresh Kumar <viresh.kumar@linaro.org>,
        Julien Thierry <julien.thierry@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 2/4] KVM: arm64: Filter out invalid core register IDs in
 KVM_GET_REG_LIST
Date: Thu, 20 Jun 2019 12:22:59 +0100
Message-Id: <20190620112301.138137-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190620112301.138137-1-marc.zyngier@arm.com>
References: <20190620112301.138137-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Dave Martin <Dave.Martin@arm.com>

Since commit d26c25a9d19b ("arm64: KVM: Tighten guest core register
access from userspace"), KVM_{GET,SET}_ONE_REG rejects register IDs
that do not correspond to a single underlying architectural register.

KVM_GET_REG_LIST was not changed to match however: instead, it
simply yields a list of 32-bit register IDs that together cover the
whole kvm_regs struct.  This means that if userspace tries to use
the resulting list of IDs directly to drive calls to KVM_*_ONE_REG,
some of those calls will now fail.

This was not the intention.  Instead, iterating KVM_*_ONE_REG over
the list of IDs returned by KVM_GET_REG_LIST should be guaranteed
to work.

This patch fixes the problem by splitting validate_core_offset()
into a backend core_reg_size_from_offset() which does all of the
work except for checking that the size field in the register ID
matches, and kvm_arm_copy_reg_indices() and num_core_regs() are
converted to use this to enumerate the valid offsets.

kvm_arm_copy_reg_indices() now also sets the register ID size field
appropriately based on the value returned, so the register ID
supplied to userspace is fully qualified for use with the register
access ioctls.

Cc: stable@vger.kernel.org
Fixes: d26c25a9d19b ("arm64: KVM: Tighten guest core register access from userspace")
Signed-off-by: Dave Martin <Dave.Martin@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
Tested-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/guest.c | 53 +++++++++++++++++++++++++++++++-----------
 1 file changed, 40 insertions(+), 13 deletions(-)

```
#### [GIT PULL] KVM changes for 5.2-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit f8d221d2e0e1572d0d60174c118e3554d1aa79fa:

  Merge tag 'kvm-s390-master-5.2-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into kvm-master (2019-06-01 00:49:02 +0200)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to b21e31b253048b7f9768ca7cc270e67765fd6ba2:

  Merge tag 'kvmarm-fixes-for-5.2-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2019-06-20 18:24:18 +0200)

----------------------------------------------------------------

Fixes for ARM and x86, plus selftest patches and nicer structs
for nested state save/restore.

----------------------------------------------------------------
Aaron Lewis (2):
      kvm: tests: Sort tests in the Makefile alphabetically
      tests: kvm: Check for a kernel warning

Andrew Jones (1):
      KVM: arm/arm64: Fix emulated ptimer irq injection

Dave Martin (2):
      KVM: arm64: Filter out invalid core register IDs in KVM_GET_REG_LIST
      KVM: arm/arm64: vgic: Fix kvm_device leak in vgic_its_destroy

Dennis Restle (1):
      KVM: fix typo in documentation

Liran Alon (1):
      KVM: x86: Modify struct kvm_nested_state to have explicit fields for data

Paolo Bonzini (2):
      KVM: nVMX: reorganize initial steps of vmx_set_nested_state
      Merge tag 'kvmarm-fixes-for-5.2-2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Sean Christopherson (1):
      KVM: x86/mmu: Allocate PAE root array when using SVM's 32-bit NPT

Viresh Kumar (1):
      KVM: arm64: Implement vq_present() as a macro

Vitaly Kuznetsov (1):
      KVM: nVMX: use correct clean fields when copying from eVMCS

 Documentation/virtual/kvm/api.txt                  |  48 +++++---
 arch/arm64/kvm/guest.c                             |  65 +++++++----
 arch/x86/include/uapi/asm/kvm.h                    |  33 ++++--
 arch/x86/kvm/mmu.c                                 |  16 ++-
 arch/x86/kvm/vmx/nested.c                          | 103 +++++++++--------
 arch/x86/kvm/vmx/vmcs12.h                          |   5 +-
 tools/arch/x86/include/uapi/asm/kvm.h              |   2 +-
 tools/testing/selftests/kvm/.gitignore             |   1 +
 tools/testing/selftests/kvm/Makefile               |  21 ++--
 tools/testing/selftests/kvm/include/kvm_util.h     |   2 +
 .../selftests/kvm/include/x86_64/processor.h       |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |  36 ++++++
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  16 +++
 .../selftests/kvm/x86_64/mmio_warning_test.c       | 126 +++++++++++++++++++++
 .../kvm/x86_64/vmx_set_nested_state_test.c         |  68 ++++++-----
 virt/kvm/arm/arch_timer.c                          |   5 +-
 virt/kvm/arm/vgic/vgic-its.c                       |   1 +
 17 files changed, 405 insertions(+), 145 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/mmio_warning_test.c
```
#### [PATCH] KVM: svm: add nrips module parameter
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Allow testing code for old processors that lack the next RIP save
feature, by disabling usage of the next_rip field.

Nested hypervisors however get the feature unconditionally.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 15 ++++++++++++---
 1 file changed, 12 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: vmx: Fix the broken usage of vmx_xsaves_supported
##### From: Tao Xu <tao3.xu@intel.com>

```c
The helper vmx_xsaves_supported() returns the bit value of
SECONDARY_EXEC_XSAVES in vmcs_config.cpu_based_2nd_exec_ctrl, which
remains unchanged true if vmcs supports 1-setting of this bit after
setup_vmcs_config(). It should check the guest's cpuid not this
unchanged value when get/set msr.

Besides, vmx_compute_secondary_exec_control() adjusts
SECONDARY_EXEC_XSAVES bit based on guest cpuid's X86_FEATURE_XSAVE
and X86_FEATURE_XSAVES, it should use updated value to decide whether
set XSS_EXIT_BITMAP.

Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: VMX: Raise #GP when guest read/write forbidden IA32_XSS
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Raise #GP when guest read/write forbidden IA32_XSS.  

Fixes: 203000993de5 (kvm: vmx: add MSR logic for XSAVES) 
Reported-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Reported-by: Tao Xu <tao3.xu@intel.com>
Cc: Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: stable@vger.kernel.org
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH v5 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
Reviewed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---

Changes in v5:
	remove vmx_waitpkg_supported() and use
	guest_cpuid_has(vcpu, X86_FEATURE_WAITPKG) directly (Xiaoyao)
---
 arch/x86/include/asm/vmx.h | 1 +
 arch/x86/kvm/cpuid.c       | 2 +-
 arch/x86/kvm/vmx/vmx.c     | 4 ++++
 3 files changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH RFC 1/5] x86: KVM: svm: don't pretend to advance RIP in case wrmsr_interception() results in #GP
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
svm->next_rip is only used by skip_emulated_instruction() and in case
kvm_set_msr() fails we rightfully don't do that. Move svm->next_rip
advancement to 'else' branch to avoid creating false impression that
it's always advanced.

By the way, rdmsr_interception() has it right already.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RFC] kvm: x86: Expose AVX512_BF16 feature to guest
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
AVX512 BFLOAT16 instructions support 16-bit BFLOAT16 floating-point
format (BF16) for deep learning optimization.

Intel adds AVX512 BFLOAT16 feature in CooperLake, which is CPUID.7.1.EAX[5].

Detailed information of the CPUID bit can be found here,
https://software.intel.com/sites/default/files/managed/c5/15/\
architecture-instruction-set-extensions-programming-reference.pdf.

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 16 ++++++++++++++--
 1 file changed, 14 insertions(+), 2 deletions(-)

```
#### [RFC v1 1/1] vfio-ccw: Don't call cp_free if we are processing a channel program
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
There is a small window where it's possible that an interrupt can
arrive and can call cp_free, while we are still processing a channel
program (i.e allocating memory, pinnging pages, translating
addresses etc). This can lead to allocating and freeing at the same
time and can cause memory corruption.

Let's not call cp_free if we are currently processing a channel program.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---

I have been running my test overnight with this patch and I haven't
seen the stack traces that I mentioned about earlier. I would like
to get some reviews on this and also if this is the right thing to
do?

Thanks
Farhan

 drivers/s390/cio/vfio_ccw_drv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [tip:x86/cpu] x86/cpufeatures: Combine word 11 and 12 into a new scattered features word
##### From: tip-bot for Fenghua Yu <tipbot@zytor.com>

```c
Commit-ID:  acec0ce081de0c36459eea91647faf99296445a3
Gitweb:     https://git.kernel.org/tip/acec0ce081de0c36459eea91647faf99296445a3
Author:     Fenghua Yu <fenghua.yu@intel.com>
AuthorDate: Wed, 19 Jun 2019 18:51:09 +0200
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Thu, 20 Jun 2019 12:38:44 +0200

x86/cpufeatures: Combine word 11 and 12 into a new scattered features word

It's a waste for the four X86_FEATURE_CQM_* feature bits to occupy two
whole feature bits words. To better utilize feature words, re-define
word 11 to host scattered features and move the four X86_FEATURE_CQM_*
features into Linux defined word 11. More scattered features can be
added in word 11 in the future.

Rename leaf 11 in cpuid_leafs to CPUID_LNX_4 to reflect it's a
Linux-defined leaf.

Rename leaf 12 as CPUID_DUMMY which will be replaced by a meaningful
name in the next patch when CPUID.7.1:EAX occupies world 12.

Maximum number of RMID and cache occupancy scale are retrieved from
CPUID.0xf.1 after scattered CQM features are enumerated. Carve out the
code into a separate function.

KVM doesn't support resctrl now. So it's safe to move the
X86_FEATURE_CQM_* features to scattered features word 11 for KVM.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
Signed-off-by: Borislav Petkov <bp@suse.de>
Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Babu Moger <babu.moger@amd.com>
Cc: "Chang S. Bae" <chang.seok.bae@intel.com>
Cc: "Sean J Christopherson" <sean.j.christopherson@intel.com>
Cc: Frederic Weisbecker <frederic@kernel.org>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Jann Horn <jannh@google.com>
Cc: Juergen Gross <jgross@suse.com>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: Masahiro Yamada <yamada.masahiro@socionext.com>
Cc: Masami Hiramatsu <mhiramat@kernel.org>
Cc: Nadav Amit <namit@vmware.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Pavel Tatashin <pasha.tatashin@oracle.com>
Cc: Peter Feiner <pfeiner@google.com>
Cc: "Peter Zijlstra (Intel)" <peterz@infradead.org>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: "Rafael J. Wysocki" <rafael.j.wysocki@intel.com>
Cc: Ravi V Shankar <ravi.v.shankar@intel.com>
Cc: Sherry Hurwitz <sherry.hurwitz@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Thomas Lendacky <Thomas.Lendacky@amd.com>
Cc: x86 <x86@kernel.org>
Link: https://lkml.kernel.org/r/1560794416-217638-2-git-send-email-fenghua.yu@intel.com
---
 arch/x86/include/asm/cpufeature.h  |  4 ++--
 arch/x86/include/asm/cpufeatures.h | 17 ++++++++++-------
 arch/x86/kernel/cpu/common.c       | 38 +++++++++++++++-----------------------
 arch/x86/kernel/cpu/cpuid-deps.c   |  3 +++
 arch/x86/kernel/cpu/scattered.c    |  4 ++++
 arch/x86/kvm/cpuid.h               |  2 --
 6 files changed, 34 insertions(+), 34 deletions(-)

```
