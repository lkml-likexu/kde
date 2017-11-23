#### [PATCH 01/28] arm64: KVM: Skip MMIO insn after emulation
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Mark Rutland <mark.rutland@arm.com>

When we emulate an MMIO instruction, we advance the CPU state within
decode_hsr(), before emulating the instruction effects.

Having this logic in decode_hsr() is opaque, and advancing the state
before emulation is problematic. It gets in the way of applying
consistent single-step logic, and it prevents us from being able to fail
an MMIO instruction with a synchronous exception.

Clean this up by only advancing the CPU state *after* the effects of the
instruction are emulated.

Cc: Peter Maydell <peter.maydell@linaro.org>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
Reviewed-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 virt/kvm/arm/mmio.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
#### [GIT PULL 1/2] KVM: s390: unregister debug feature on failing arch init
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Michael Mueller <mimu@linux.ibm.com>

Make sure the debug feature and its allocated resources get
released upon unsuccessful architecture initialization.

A related indication of the issue will be reported as kernel
message.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Message-Id: <20181130143215.69496-2-mimu@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

```
#### [GIT PULL] KVM/arm updates for 4.21
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

This is the KVM/arm updates for 4.21. The biggest thing is the support
for 1GB PUD support for HugeTLB backed guest memory. The rest is a
bunch of cleanups and other fixes.

Please pull,

	M.

The following changes since commit 2e6e902d185027f8e3cb8b7305238f7e35d6a436:

  Linux 4.20-rc4 (2018-11-25 14:19:31 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-for-v4.21

for you to fetch changes up to 8c33df1afd86c611da8473dc6fc5f3af3dabe984:

  arm: KVM: Add S2_PMD_{MASK,SIZE} constants (2018-12-19 17:48:21 +0000)

----------------------------------------------------------------
KVM/arm updates for 4.21

- Large PUD support for HugeTLB
- Single-stepping fixes
- Improved tracing
- Various timer and vgic fixups

----------------------------------------------------------------
Christoffer Dall (9):
      KVM: arm/arm64: Fix VMID alloc race by reverting to lock-less
      KVM: arm/arm64: vgic-v2: Set active_source to 0 when restoring state
      KVM: arm64: Clarify explanation of STAGE2_PGTABLE_LEVELS
      KVM: arm/arm64: vgic: Consider priority and active state for pending irq
      KVM: arm/arm64: Fixup the kvm_exit tracepoint
      KVM: arm/arm64: Remove arch timer workqueue
      KVM: arm/arm64: arch_timer: Simplify kvm_timer_vcpu_terminate
      KVM: arm64: Make vcpu const in vcpu_read_sys_reg
      KVM: arm/arm64: Fix unintended stage 2 PMD mappings

Gustavo A. R. Silva (1):
      KVM: arm/arm64: vgic: Fix off-by-one bug in vgic_get_irq()

Julien Thierry (1):
      KVM: arm/arm64: vgic: Do not cond_resched_lock() with IRQs disabled

Marc Zyngier (5):
      KVM: arm/arm64: vgic: Cap SPIs to the VM-defined maximum
      arm64: KVM: Add trapped system register access tracepoint
      arm/arm64: KVM: vgic: Force VM halt when changing the active state of GICv3 PPIs/SGIs
      arm/arm64: KVM: Add ARM_EXCEPTION_IS_TRAP macro
      arm: KVM: Add S2_PMD_{MASK,SIZE} constants

Mark Rutland (3):
      arm64: KVM: Skip MMIO insn after emulation
      arm64: KVM: Consistently advance singlestep when emulating instructions
      KVM: arm/arm64: Log PSTATE for unhandled sysregs

Punit Agrawal (8):
      KVM: arm/arm64: Share common code in user_mem_abort()
      KVM: arm/arm64: Re-factor setting the Stage 2 entry to exec on fault
      KVM: arm/arm64: Introduce helpers to manipulate page table entries
      KVM: arm64: Support dirty page tracking for PUD hugepages
      KVM: arm64: Support PUD hugepage in stage2_is_exec()
      KVM: arm64: Support handling access faults for PUD hugepages
      KVM: arm64: Update age handlers to support PUD hugepages
      KVM: arm64: Add support for creating PUD hugepages at stage 2

Will Deacon (1):
      arm64: KVM: Avoid setting the upper 32 bits of VTCR_EL2 to 1

 arch/arm/include/asm/kvm_asm.h           |   4 +
 arch/arm/include/asm/kvm_host.h          |   5 -
 arch/arm/include/asm/kvm_mmu.h           |  61 +++++
 arch/arm/include/asm/stage2_pgtable.h    |   8 +
 arch/arm/kvm/coproc.c                    |   4 +-
 arch/arm64/include/asm/kvm_arm.h         |   6 +-
 arch/arm64/include/asm/kvm_asm.h         |   7 +
 arch/arm64/include/asm/kvm_emulate.h     |  35 ++-
 arch/arm64/include/asm/kvm_host.h        |   3 +-
 arch/arm64/include/asm/kvm_mmu.h         |  48 ++++
 arch/arm64/include/asm/pgtable-hwdef.h   |   4 +
 arch/arm64/include/asm/pgtable.h         |   9 +
 arch/arm64/include/asm/stage2_pgtable.h  |  16 +-
 arch/arm64/kvm/debug.c                   |  21 --
 arch/arm64/kvm/handle_exit.c             |  14 +-
 arch/arm64/kvm/hyp/switch.c              |  43 +---
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c |  12 +-
 arch/arm64/kvm/sys_regs.c                |  12 +-
 arch/arm64/kvm/sys_regs.h                |   4 +
 arch/arm64/kvm/trace.h                   |  35 +++
 include/kvm/arm_arch_timer.h             |   4 -
 virt/kvm/arm/arch_timer.c                |  35 +--
 virt/kvm/arm/arm.c                       |  25 +-
 virt/kvm/arm/hyp/vgic-v3-sr.c            |   6 +-
 virt/kvm/arm/mmio.c                      |  11 +-
 virt/kvm/arm/mmu.c                       | 384 +++++++++++++++++++++++--------
 virt/kvm/arm/trace.h                     |  18 +-
 virt/kvm/arm/vgic/vgic-mmio.c            |  44 ++--
 virt/kvm/arm/vgic/vgic.c                 |  13 +-
 29 files changed, 595 insertions(+), 296 deletions(-)

From patchwork Wed Dec 19 18:03:23 2018
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 10737835
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8DD2014DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Dec 2018 18:04:18 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 7F6152B76B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Dec 2018 18:04:18 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 730922B7A6; Wed, 19 Dec 2018 18:04:18 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 8D49A2B76B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 19 Dec 2018 18:04:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730383AbeLSSEQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Dec 2018 13:04:16 -0500
Received: from foss.arm.com ([217.140.101.70]:40054 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730373AbeLSSEP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 19 Dec 2018 13:04:15 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.72.51.249])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 3098B15BE;
        Wed, 19 Dec 2018 10:04:15 -0800 (PST)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.196.62])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 81D7B3F675;
        Wed, 19 Dec 2018 10:04:12 -0800 (PST)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Christoffer Dall <christoffer.dall@arm.com>,
 "Gustavo A . R . Silva" <gustavo@embeddedor.com>,
 Julien Thierry <julien.thierry@arm.com>, Lukas Braun <koomi@moshbit.net>,
 Mark Rutland <mark.rutland@arm.com>, Punit Agrawal <punit.agrawal@arm.com>,
 Suzuki Poulose <suzuki.poulose@arm.com>, Will Deacon <will.deacon@arm.com>,
 punitagrawal@gmail.com, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [PATCH 02/28] arm64: KVM: Consistently advance singlestep when
 emulating instructions
Date: Wed, 19 Dec 2018 18:03:23 +0000
Message-Id: <20181219180349.242681-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20181219180349.242681-1-marc.zyngier@arm.com>
References: <20181219180349.242681-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Mark Rutland <mark.rutland@arm.com>

When we emulate a guest instruction, we don't advance the hardware
singlestep state machine, and thus the guest will receive a software
step exception after a next instruction which is not emulated by the
host.

We bodge around this in an ad-hoc fashion. Sometimes we explicitly check
whether userspace requested a single step, and fake a debug exception
from within the kernel. Other times, we advance the HW singlestep state
rely on the HW to generate the exception for us. Thus, the observed step
behaviour differs for host and guest.

Let's make this simpler and consistent by always advancing the HW
singlestep state machine when we skip an instruction. Thus we can rely
on the hardware to generate the singlestep exception for us, and never
need to explicitly check for an active-pending step, nor do we need to
fake a debug exception from the guest.

Cc: Peter Maydell <peter.maydell@linaro.org>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
Reviewed-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Mark Rutland <mark.rutland@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_host.h          |  5 ---
 arch/arm64/include/asm/kvm_emulate.h     | 35 ++++++++++++++-----
 arch/arm64/include/asm/kvm_host.h        |  1 -
 arch/arm64/kvm/debug.c                   | 21 ------------
 arch/arm64/kvm/handle_exit.c             | 14 +-------
 arch/arm64/kvm/hyp/switch.c              | 43 +++---------------------
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c | 12 +++++--
 virt/kvm/arm/arm.c                       |  2 --
 virt/kvm/arm/hyp/vgic-v3-sr.c            |  6 +++-
 9 files changed, 46 insertions(+), 93 deletions(-)

```
#### [GIT PULL] KVM fixes for 4.20-rc8 (or final)
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 7566ec393f4161572ba6f11ad5171fd5d59b0fbd:

  Linux 4.20-rc7 (2018-12-16 15:46:55 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 0e1b869fff60c81b510c2d00602d778f8f59dd9a:

  kvm: x86: Add AMD's EX_CFG to the list of ignored MSRs (2018-12-18 22:15:44 +0100)

----------------------------------------------------------------
* One nasty use-after-free bugfix, from this merge window however
* A less nasty use-after-free that can only zero some words at
the beginning of the page, and hence is not really exploitable
* A NULL pointer dereference
* A dummy implementation of an AMD chicken bit MSR that Windows uses
for some unknown reason

----------------------------------------------------------------
Cfir Cohen (1):
      KVM: Fix UAF in nested posted interrupt processing

Eduardo Habkost (1):
      kvm: x86: Add AMD's EX_CFG to the list of ignored MSRs

Eric Biggers (1):
      KVM: fix unregistering coalesced mmio zone from wrong bus

Wanpeng Li (1):
      KVM: X86: Fix NULL deref in vcpu_scan_ioapic

 arch/x86/include/asm/msr-index.h | 1 +
 arch/x86/kvm/vmx.c               | 2 ++
 arch/x86/kvm/x86.c               | 4 +++-
 virt/kvm/coalesced_mmio.c        | 6 +++++-
 4 files changed, 11 insertions(+), 2 deletions(-)
```
#### [PATCH v5 01/15] KVM: s390: unregister debug feature on failing arch init
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Make sure the debug feature and its allocated resources get
released upon unsuccessful architecture initialization.

A related indication of the issue will be reported as kernel
message.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Message-Id: <20181130143215.69496-2-mimu@linux.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 Documentation/kmsg/s390/kvm | 12 ++++++++++++
 arch/s390/kvm/kvm-s390.c    | 17 ++++++++++++++---
 2 files changed, 26 insertions(+), 3 deletions(-)
 create mode 100644 Documentation/kmsg/s390/kvm

diff --git a/Documentation/kmsg/s390/kvm b/Documentation/kmsg/s390/kvm
new file mode 100644
index 000000000000..76ffe2012254
--- /dev/null
+++ b/Documentation/kmsg/s390/kvm
@@ -0,0 +1,12 @@
+/*?
+ * Text: "Failed to register FLIC rc=%d\n"
+ * Severity: Error
+ * Parameter:
+ *   @1: return code of the FLIC registration call
+ * Description:
+ * The registration of the FLIC (Floating Interrupt Controller Interface)
+ * was not successful.
+ * User action:
+ * If this problem persists after a reload of the kvm kernel module, gather
+ * Linux debug data and contact your support organization.
+ */
```
#### [PATCH] KVM: x86: nSVM: fix switch to guest mmu
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Recent optimizations in MMU code broke nested SVM with NPT in L1
completely: when we do nested_svm_{,un}init_mmu_context() we want
to switch from TDP MMU to shadow MMU, both init_kvm_tdp_mmu() and
kvm_init_shadow_mmu() check if re-configuration is needed by looking
at cache source data. The data, however, doesn't change - it's only
the type of the MMU which changes. We end up not re-initializing
guest MMU as shadow and everything goes off the rails.

The issue could have been fixed by putting MMU type into extended MMU
role but this is not really needed. We can just split root and guest MMUs
the exact same way we did for nVMX, their types never change in the
lifetime of a vCPU.

There is still room for improvement: currently, we reset all MMU roots
when switching from L1 to L2 and back and this is not needed.

Fixes: 7dcd57552008 ("x86/kvm/mmu: check if tdp/shadow MMU reconfiguration is needed")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: svm: report MSR_IA32_MCG_EXT_CTL as unsupported
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
AMD doesn't seem to implement MSR_IA32_MCG_EXT_CTL and svm code in kvm
knows nothing about it, however, this MSR is among emulated_msrs and
thus returned with KVM_GET_MSR_INDEX_LIST. The consequent KVM_GET_MSRS,
of course, fails.

Report the MSR as unsupported to not confuse userspace.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### linux-next: build failure after merge of the kvm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Hi all,

After merging the kvm tree, today's linux-next build (x86_64 allmodconfig)
failed like this:

arch/x86/kvm/vmx/nested.c: In function 'prepare_vmcs02_full':
arch/x86/kvm/vmx/nested.c:2242:6: error: implicit declaration of function 'kvm_mpx_supported'; did you mean 'vmx_mpx_supported'? [-Werror=implicit-function-declaration]
  if (kvm_mpx_supported()) {
      ^~~~~~~~~~~~~~~~~
      vmx_mpx_supported

Caused by commit

  55d2375e58a6 ("KVM: nVMX: Move nested code to dedicated files")

interacting with commit

  eb012ef3b4e3 ("x86: Remove Intel MPX")

from the tip tree.

I applied the following merge fix patch for today:

From: Stephen Rothwell <sfr@canb.auug.org.au>
Date: Wed, 19 Dec 2018 15:28:31 +1100
Subject: [PATCH] kvm: tidy up from MPX removal

Signed-off-by: Stephen Rothwell <sfr@canb.auug.org.au>
---
 arch/x86/kvm/vmx/nested.c | 13 -------------
 arch/x86/kvm/vmx/vmx.c    | 40 +++------------------------------------
 2 files changed, 3 insertions(+), 50 deletions(-)

```
#### [PULL 1/1] virtio-ccw: diag 500 may return a negative cookie
##### From: Cornelia Huck <cohuck@redhat.com>

```c
If something goes wrong in the kvm io bus handling, the virtio-ccw
diagnose may return a negative error value in the cookie gpr.

Document this.

Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virtual/kvm/s390-diag.txt | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PULL] virtio fix
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Sorry about the last-minute pull req.
But it does seem very very safe and also the tests
aren't automatically built right now so the 0 day
infrastructure won't help anyway.

The following changes since commit 7566ec393f4161572ba6f11ad5171fd5d59b0fbd:

  Linux 4.20-rc7 (2018-12-16 15:46:55 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to c5c08bed843c2b2c048c16d1296d7631d7c1620e:

  virtio: fix test build after uio.h change (2018-12-19 18:23:49 -0500)

----------------------------------------------------------------
virtio fix

A last-minute fix for a test build.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Michael S. Tsirkin (1):
      virtio: fix test build after uio.h change

 tools/virtio/linux/kernel.h | 4 ++++
 1 file changed, 4 insertions(+)
```
#### [PATCH] selftests: kvm: report failed stage when exit reason is unexpected
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
When we get a report like

==== Test Assertion Failure ====
  x86_64/state_test.c:157: run->exit_reason == KVM_EXIT_IO
  pid=955 tid=955 - Success
     1	0x0000000000401350: main at state_test.c:154
     2	0x00007fc31c9e9412: ?? ??:0
     3	0x000000000040159d: _start at ??:?
  Unexpected exit reason: 8 (SHUTDOWN),

it is not obvious which particular stage failed. Add the info.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/evmcs_test.c | 4 ++--
 tools/testing/selftests/kvm/x86_64/state_test.c | 4 ++--
 2 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] x86: Add CPUID KVM support for new instruction WBNOINVD
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
Signed-off-by: Robert Hoo <robert.hu@linux.intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kvm/cpuid.c               | 2 +-
 2 files changed, 2 insertions(+), 1 deletion(-)

```
