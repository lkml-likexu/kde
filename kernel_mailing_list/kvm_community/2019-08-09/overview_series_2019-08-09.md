#### [PATCH 1/4] KVM: arm/arm64: Sync ICH_VMCR_EL2 back when about to block
##### From: Marc Zyngier <maz@kernel.org>

```c
Since commit commit 328e56647944 ("KVM: arm/arm64: vgic: Defer
touching GICH_VMCR to vcpu_load/put"), we leave ICH_VMCR_EL2 (or
its GICv2 equivalent) loaded as long as we can, only syncing it
back when we're scheduled out.

There is a small snag with that though: kvm_vgic_vcpu_pending_irq(),
which is indirectly called from kvm_vcpu_check_block(), needs to
evaluate the guest's view of ICC_PMR_EL1. At the point were we
call kvm_vcpu_check_block(), the vcpu is still loaded, and whatever
changes to PMR is not visible in memory until we do a vcpu_put().

Things go really south if the guest does the following:

	mov x0, #0	// or any small value masking interrupts
	msr ICC_PMR_EL1, x0

	[vcpu preempted, then rescheduled, VMCR sampled]

	mov x0, #ff	// allow all interrupts
	msr ICC_PMR_EL1, x0
	wfi		// traps to EL2, so samping of VMCR

	[interrupt arrives just after WFI]

Here, the hypervisor's view of PMR is zero, while the guest has enabled
its interrupts. kvm_vgic_vcpu_pending_irq() will then say that no
interrupts are pending (despite an interrupt being received) and we'll
block for no reason. If the guest doesn't have a periodic interrupt
firing once it has blocked, it will stay there forever.

To avoid this unfortuante situation, let's resync VMCR from
kvm_arch_vcpu_blocking(), ensuring that a following kvm_vcpu_check_block()
will observe the latest value of PMR.

This has been found by booting an arm64 Linux guest with the pseudo NMI
feature, and thus using interrupt priorities to mask interrupts instead
of the usual PSTATE masking.

Cc: stable@vger.kernel.org # 4.12
Fixes: 328e56647944 ("KVM: arm/arm64: vgic: Defer touching GICH_VMCR to vcpu_load/put")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 include/kvm/arm_vgic.h      |  1 +
 virt/kvm/arm/arm.c          | 11 +++++++++++
 virt/kvm/arm/vgic/vgic-v2.c |  9 ++++++++-
 virt/kvm/arm/vgic/vgic-v3.c |  7 ++++++-
 virt/kvm/arm/vgic/vgic.c    | 11 +++++++++++
 virt/kvm/arm/vgic/vgic.h    |  2 ++
 6 files changed, 39 insertions(+), 2 deletions(-)

```
#### [PATCH V5 1/9] vhost: don't set uaddr for invalid address
##### From: Jason Wang <jasowang@redhat.com>

```c
We should not setup uaddr for the invalid address, otherwise we may
try to pin or prefetch mapping of wrong pages.

Fixes: 7f466032dc9e ("vhost: access vq metadata through kernel virtual address")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm updates for 5.3-rc4
##### From: Marc Zyngier <maz@kernel.org>

```c
Paolo, Radim,

Here's a set of update for -rc4. Yet another reset fix, and two subtle
VGIC fixes for issues that can be observed in interesting corner cases.

Note that this is on top of kvmarm-fixes-for-5.3[1], which hasn't been
pulled yet. Hopefully you can pull both at the same time!

Thanks,

	M.

[1] https://lore.kernel.org/kvmarm/20190731173650.12627-1-maz@kernel.org

The following changes since commit cdb2d3ee0436d74fa9092f2df46aaa6f9e03c969:

  arm64: KVM: hyp: debug-sr: Mark expected switch fall-through (2019-07-29 11:01:37 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.3-2

for you to fetch changes up to 16e604a437c89751dc626c9e90cf88ba93c5be64:

  KVM: arm/arm64: vgic: Reevaluate level sensitive interrupts on enable (2019-08-09 08:07:26 +0100)

----------------------------------------------------------------
KVM/arm fixes for 5.3, take #2

- Fix our system register reset so that we stop writing
  non-sensical values to them, and track which registers
  get reset instead.
- Sync VMCR back from the GIC on WFI so that KVM has an
  exact vue of PMR.
- Reevaluate state of HW-mapped, level triggered interrupts
  on enable.

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm/arm64: vgic: Reevaluate level sensitive interrupts on enable

Marc Zyngier (3):
      KVM: arm/arm64: Sync ICH_VMCR_EL2 back when about to block
      KVM: arm64: Don't write junk to sysregs on reset
      KVM: arm: Don't write junk to CP15 registers on reset

 arch/arm/kvm/coproc.c         | 23 +++++++++++++++--------
 arch/arm64/kvm/sys_regs.c     | 32 ++++++++++++++++++--------------
 include/kvm/arm_vgic.h        |  1 +
 virt/kvm/arm/arm.c            | 11 +++++++++++
 virt/kvm/arm/vgic/vgic-mmio.c | 16 ++++++++++++++++
 virt/kvm/arm/vgic/vgic-v2.c   |  9 ++++++++-
 virt/kvm/arm/vgic/vgic-v3.c   |  7 ++++++-
 virt/kvm/arm/vgic/vgic.c      | 11 +++++++++++
 virt/kvm/arm/vgic/vgic.h      |  2 ++
 9 files changed, 88 insertions(+), 24 deletions(-)

From patchwork Fri Aug  9 07:48:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11085607
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E88D213AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:49:05 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id DAAF628BDF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:49:05 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id CF2FD28C42; Fri,  9 Aug 2019 07:49:05 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 9833E28C50
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:49:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405908AbfHIHtD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Aug 2019 03:49:03 -0400
Received: from foss.arm.com ([217.140.110.172]:42774 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2405910AbfHIHtD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Aug 2019 03:49:03 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id A142B15BF;
        Fri,  9 Aug 2019 00:49:02 -0700 (PDT)
Received: from why.lan (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 021853F706;
        Fri,  9 Aug 2019 00:49:00 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/4] KVM: arm64: Don't write junk to sysregs on reset
Date: Fri,  9 Aug 2019 08:48:30 +0100
Message-Id: <20190809074832.13283-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190809074832.13283-1-maz@kernel.org>
References: <20190809074832.13283-1-maz@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

At the moment, the way we reset system registers is mildly insane:
We write junk to them, call the reset functions, and then check that
we have something else in them.

The "fun" thing is that this can happen while the guest is running
(PSCI, for example). If anything in KVM has to evaluate the state
of a system register while junk is in there, bad thing may happen.

Let's stop doing that. Instead, we track that we have called a
reset function for that register, and assume that the reset
function has done something. This requires fixing a couple of
sysreg refinition in the trap table.

In the end, the very need of this reset check is pretty dubious,
as it doesn't check everything (a lot of the sysregs leave outside of
the sys_regs[] array). It may well be axed in the near future.

Tested-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 32 ++++++++++++++++++--------------
 1 file changed, 18 insertions(+), 14 deletions(-)

```
#### [GIT PULL] KVM fixes for Linux 5.3-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 266e85a5ec9100dcd9ae03601453bbc96fefee5d:

  KVM: X86: Boost queue head vCPU to mitigate lock waiter preemption (2019-07-24 13:56:53 +0200)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to a738b5e75b4c13be3485c82eb62c30047aa9f164:

  Merge tag 'kvmarm-fixes-for-5.3-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2019-08-09 16:53:50 +0200)

----------------------------------------------------------------

Bugfixes (arm and x86) and cleanups.

----------------------------------------------------------------
Alexandru Elisei (1):
      KVM: arm/arm64: vgic: Reevaluate level sensitive interrupts on enable

Anders Roxell (3):
      arm64: KVM: regmap: Fix unexpected switch fall-through
      KVM: arm: vgic-v3: Mark expected switch fall-through
      arm64: KVM: hyp: debug-sr: Mark expected switch fall-through

Greg KH (1):
      KVM: no need to check return value of debugfs_create functions

Marc Zyngier (3):
      KVM: arm/arm64: Sync ICH_VMCR_EL2 back when about to block
      KVM: arm64: Don't write junk to sysregs on reset
      KVM: arm: Don't write junk to CP15 registers on reset

Naresh Kamboju (1):
      selftests: kvm: Adding config fragments

Paolo Bonzini (5):
      KVM: remove kvm_arch_has_vcpu_debugfs()
      x86: kvm: remove useless calls to kvm_para_available
      kvm: remove unnecessary PageReserved check
      Merge tag 'kvmarm-fixes-for-5.3' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      Merge tag 'kvmarm-fixes-for-5.3-2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Thomas Huth (1):
      KVM: selftests: Update gitignore file for latest changes

Wanpeng Li (3):
      KVM: LAPIC: Don't need to wakeup vCPU twice afer timer fire
      KVM: Check preempted_in_kernel for involuntary preemption
      KVM: Fix leak vCPU's VMCS value into other pCPU

Zenghui Yu (2):
      KVM: arm/arm64: Introduce kvm_pmu_vcpu_init() to setup PMU counter index
      KVM: arm64: Update kvm_arm_exception_class and esr_class_str for new EC

 arch/arm/kvm/coproc.c                  | 23 ++++++++-----
 arch/arm64/include/asm/kvm_arm.h       |  7 ++--
 arch/arm64/kernel/traps.c              |  1 +
 arch/arm64/kvm/hyp/debug-sr.c          | 30 +++++++++++++++++
 arch/arm64/kvm/regmap.c                |  5 +++
 arch/arm64/kvm/sys_regs.c              | 32 ++++++++++--------
 arch/mips/kvm/mips.c                   | 10 ------
 arch/powerpc/kvm/powerpc.c             | 15 +++------
 arch/s390/kvm/kvm-s390.c               | 10 ------
 arch/x86/include/asm/kvm_host.h        |  3 ++
 arch/x86/kernel/kvm.c                  |  8 -----
 arch/x86/kvm/debugfs.c                 | 46 ++++++++-----------------
 arch/x86/kvm/lapic.c                   |  8 -----
 arch/x86/kvm/svm.c                     |  6 ++++
 arch/x86/kvm/vmx/vmx.c                 |  6 ++++
 arch/x86/kvm/x86.c                     | 16 +++++++++
 include/kvm/arm_pmu.h                  |  2 ++
 include/kvm/arm_vgic.h                 |  1 +
 include/linux/kvm_host.h               |  6 ++--
 tools/testing/selftests/kvm/.gitignore |  3 +-
 tools/testing/selftests/kvm/config     |  3 ++
 virt/kvm/arm/arm.c                     | 18 +++++++---
 virt/kvm/arm/hyp/vgic-v3-sr.c          |  8 +++++
 virt/kvm/arm/pmu.c                     | 18 ++++++++--
 virt/kvm/arm/vgic/vgic-mmio.c          | 16 +++++++++
 virt/kvm/arm/vgic/vgic-v2.c            |  9 ++++-
 virt/kvm/arm/vgic/vgic-v3.c            |  7 +++-
 virt/kvm/arm/vgic/vgic.c               | 11 ++++++
 virt/kvm/arm/vgic/vgic.h               |  2 ++
 virt/kvm/kvm_main.c                    | 61 ++++++++++++++++++++--------------
 30 files changed, 249 insertions(+), 142 deletions(-)
```
#### [PATCH 1/3] x86/Hyper-V: Fix definition of struct hv_vp_assist_page
##### From: lantianyu1986@gmail.com

```c
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

The struct hv_vp_assist_page was defined incorrectly.
The "vtl_control" should be u64[3], "nested_enlightenments_control"
should be a u64 and there is 7 reserved bytes following "enlighten_vmentry".
This patch is to fix it.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: LAPIC: Periodically revaluate appropriate lapic_timer_advance_ns
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Even if for realtime CPUs, cache line bounces, frequency scaling, presence 
of higher-priority RT tasks, etc can cause different response. These 
interferences should be considered and periodically revaluate whether 
or not the lapic_timer_advance_ns value is the best, do nothing if it is,
otherwise recaluate again. 

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 16 +++++++++++++++-
 arch/x86/kvm/lapic.h |  1 +
 2 files changed, 16 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: nVMX: Check Host Address Space Size on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks Related to Address-Space Size" in Intel SDM
vol 3C, the following checks are performed on vmentry of nested guests:

    If the logical processor is outside IA-32e mode (if IA32_EFER.LMA = 0)
    at the time of VM entry, the following must hold:
	- The "IA-32e mode guest" VM-entry control is 0.
	- The "host address-space size" VM-exit control is 0.

    If the logical processor is in IA-32e mode (if IA32_EFER.LMA = 1) at the
    time of VM entry, the "host address-space size" VM-exit control must be 1.

    If the "host address-space size" VM-exit control is 0, the following must
    hold:
	- The "IA-32e mode guest" VM-entry control is 0.
	- Bit 17 of the CR4 field (corresponding to CR4.PCIDE) is 0.
	- Bits 63:32 in the RIP field are 0.

    If the "host address-space size" VM-exit control is 1, the following must
    hold:
	- Bit 5 of the CR4 field (corresponding to CR4.PAE) is 1.
	- The RIP field contains a canonical address.

    On processors that do not support Intel 64 architecture, checks are
    performed to ensure that the "IA-32e mode guest" VM-entry control and the
    "host address-space size" VM-exit control are both 0.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 28 ++++++++++++++++++++++++++++
 1 file changed, 28 insertions(+)

```
#### [PATCH kvm-unit-tests] x86: access: avoid undefined behavior
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
In this test, at->ptep is tested in one argument to ac_test_check
and dereferenced in another.  The compiler notices that and observes
that at->ptep cannot be NULL.  The test is indeed broken and has
been broken for 9+ years: the ac_test_check should not be performed at
all if there is no PTE.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/access.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] MAINTAINERS: add KVM x86 reviewers
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This is probably overdone---KVM x86 has quite a few contributors that
usually review each other's patches, which is really helpful to me.
Formalize this by listing them as reviewers.  I am including people
with various expertise:

- Joerg for SVM (with designated reviewers, it makes more sense to have
him in the main KVM/x86 stanza)

- Sean for MMU and VMX

- Jim for VMX

- Vitaly for Hyper-V and possibly SVM

- Wanpeng for LAPIC and paravirtualization.

Please ack if you are okay with this arrangement, otherwise speak up.

In other news, Radim is going to leave Red Hat soon.  However, he has
not been very much involved in upstream KVM development for some time,
and in the immediate future he is still going to help maintain kvm/queue
while I am on vacation.  Since not much is going to change, I will let
him decide whether he wants to keep the maintainer role after he leaves.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Joerg Roedel <joro@8bytes.org>
Acked-by: Wanpeng Li <wanpengli@tencent.com>
Acked-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Sean Christopherson <sean.j.christopherson@intel.com>
Acked-by: Jim Mattson <jmattson@google.com>
---
 MAINTAINERS | 17 +++++++++--------
 1 file changed, 9 insertions(+), 8 deletions(-)

```
#### [PATCH] MAINTAINERS: change list for KVM/s390
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
KVM/s390 does not have a list of its own, and linux-s390 is in the
loop anyway thanks to the generic arch/s390 match.  So use the generic
KVM list for s390 patches.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 MAINTAINERS | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/2] selftests: kvm: Adding config fragments
##### From: Naresh Kamboju <naresh.kamboju@linaro.org>

```c
selftests kvm all test cases need pre-required kernel config for the
tests to get pass.

CONFIG_KVM=y

The KVM tests are skipped without these configs:

        dev_fd = open(KVM_DEV_PATH, O_RDONLY);
        if (dev_fd < 0)
                exit(KSFT_SKIP);

Signed-off-by: Naresh Kamboju <naresh.kamboju@linaro.org>
Acked-by: Shuah Khan <skhan@linuxfoundation.org>
---
 tools/testing/selftests/kvm/config | 1 +
 1 file changed, 1 insertion(+)
 create mode 100644 tools/testing/selftests/kvm/config

diff --git a/tools/testing/selftests/kvm/config b/tools/testing/selftests/kvm/config
new file mode 100644
index 000000000000..14f90d8d6801
--- /dev/null
+++ b/tools/testing/selftests/kvm/config
@@ -0,0 +1 @@
+CONFIG_KVM=y

From patchwork Fri Aug  9 07:24:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Naresh Kamboju <naresh.kamboju@linaro.org>
X-Patchwork-Id: 11085523
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B5796C5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:24:39 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id F2B1428C28
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:24:38 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id E6C4728C2D; Fri,  9 Aug 2019 07:24:38 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.0 required=2.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,RCVD_IN_DNSWL_HI
	autolearn=unavailable version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id C5B0E28C28
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Aug 2019 07:24:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405737AbfHIHYe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Aug 2019 03:24:34 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:45876 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2405701AbfHIHYd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Aug 2019 03:24:33 -0400
Received: by mail-wr1-f66.google.com with SMTP id q12so7006891wrj.12
        for <kvm@vger.kernel.org>; Fri, 09 Aug 2019 00:24:32 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=linaro.org; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=WA0xD70S4mvb/PQJqRGInCwCmljrweMt295QtIocBXo=;
        b=ECmtJohNEbHkaOvigVwh0bY5ueXewlnzoOQL3GT3J/vW0jaj8QP331qzTa6/eZe6ap
         FtgCKyWaI2sflGgqWmktF07KsIvaDVTZBEzGpnEFoqdjFHQJDHfA6TYzamqpL5yRiPdz
         uzOe419XsGH1DRGPvc6b1Wp8Z7lObTT7ntP5WtqGMZegXUN+mD85FpgToBqnZGaLapZj
         DjzTHVUT4HPBs4xXsvS1e4ie34ZZ7+rF/Et9jLybklI17im+xbwHvu4Hh3XmCSCbRa/f
         bFvlZ1E4nmQpCKjIJTF0SoLjYwmUZGLZp2NP/4mOtA88cRweUiVPLKMKKkVDkdHIRvC4
         1cSQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=WA0xD70S4mvb/PQJqRGInCwCmljrweMt295QtIocBXo=;
        b=I5VrjCWc4ntq4BG/HM18f2+1wfaTa5o58clIJNYV34GBDN9M1MzziK9xXtCRxaiHWq
         D7xRT8SK3foMCrXqb4TuYjqsNgDFQLuWIMtOIQxXg9PhnjE8FbEeFftdpATPMI2xLy4c
         2ISfiN1OcrUWPY2cC9rVNuKMq8HpVyazTrDNkBAqD3N098qocPf7LZw+dlTglRP6phF8
         RP0jT6QmacHYvWQUgPF2W5vtPZBwp5L34srlg4CzWH3HaMD94aqAj6zrGwfIUoJfem7t
         XRg++0/DosoBGVdNyFMd/hVzBhjmvtSauT1yuEzFI75wyk8ZzGJ85Js+P88MXULNHVDQ
         IDlg==
X-Gm-Message-State: APjAAAVqmUsn2SGuTTS2EWTf6RW2hGB6YnsPZY834SF2tYw6uUY7S9TP
        xj/V8GtJo6re7xXjgcGZVqUSmw==
X-Google-Smtp-Source: 
 APXvYqzeCO+GY7pXqejgTG/gXxeki0mTFaAubI9/NXbDdkGSDD2/esm1gSsnUs44X+UO9i0yvJ2edQ==
X-Received: by 2002:a5d:4484:: with SMTP id j4mr22016063wrq.143.1565335471654;
        Fri, 09 Aug 2019 00:24:31 -0700 (PDT)
Received: from hackbox2.linaroharston ([81.128.185.34])
        by smtp.gmail.com with ESMTPSA id
 p13sm26232705wrw.90.2019.08.09.00.24.30
        (version=TLS1_3 cipher=AEAD-AES256-GCM-SHA384 bits=256/256);
        Fri, 09 Aug 2019 00:24:31 -0700 (PDT)
From: Naresh Kamboju <naresh.kamboju@linaro.org>
To: naresh.kamboju@linaro.org, pbonzini@redhat.com, shuah@kernel.org
Cc: linux-kernel@vger.kernel.org, drjones@redhat.com,
        sean.j.christopherson@intel.com, linux-kselftest@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH v3 2/2] selftests: kvm: x86_64: Adding config fragments
Date: Fri,  9 Aug 2019 08:24:15 +0100
Message-Id: <20190809072415.29305-2-naresh.kamboju@linaro.org>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190809072415.29305-1-naresh.kamboju@linaro.org>
References: <20190809072415.29305-1-naresh.kamboju@linaro.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

selftests kvm x86_64 test cases need pre-required kernel configs for the
tests to get pass when you are using Intel or AMD CPU.

CONFIG_KVM_INTEL=y
CONFIG_KVM_AMD=y

Signed-off-by: Naresh Kamboju <naresh.kamboju@linaro.org>
---
 tools/testing/selftests/kvm/x86_64/config | 2 ++
 1 file changed, 2 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/config

diff --git a/tools/testing/selftests/kvm/x86_64/config b/tools/testing/selftests/kvm/x86_64/config
new file mode 100644
index 000000000000..4df8c7f54885
--- /dev/null
+++ b/tools/testing/selftests/kvm/x86_64/config
@@ -0,0 +1,2 @@
+CONFIG_KVM_INTEL=y
+CONFIG_KVM_AMD=y
```
#### [RFC PATCH v6 01/92] kvm: introduce KVMI (VM introspection subsystem)
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From: Mihai Donțu <mdontu@bitdefender.com>

Besides the pointer to the new structure, the patch adds to the kvm
structure a reference counter (the new object will be used by the thread
receiving introspection commands/events) and a completion variable
(to signal that the VM can be hooked by the introspection tool).

Signed-off-by: Mihai Donțu <mdontu@bitdefender.com>
Co-developed-by: Mircea Cîrjaliu <mcirjaliu@bitdefender.com>
Signed-off-by: Mircea Cîrjaliu <mcirjaliu@bitdefender.com>
Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 Documentation/virtual/kvm/kvmi.rst | 75 ++++++++++++++++++++++++++++++
 arch/x86/kvm/Kconfig               |  7 +++
 arch/x86/kvm/Makefile              |  1 +
 include/linux/kvm_host.h           |  4 ++
 include/linux/kvmi.h               | 23 +++++++++
 include/uapi/linux/kvmi.h          | 68 +++++++++++++++++++++++++++
 virt/kvm/kvm_main.c                | 10 +++-
 virt/kvm/kvmi.c                    | 64 +++++++++++++++++++++++++
 virt/kvm/kvmi_int.h                | 12 +++++
 9 files changed, 263 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/virtual/kvm/kvmi.rst
 create mode 100644 include/linux/kvmi.h
 create mode 100644 include/uapi/linux/kvmi.h
 create mode 100644 virt/kvm/kvmi.c
 create mode 100644 virt/kvm/kvmi_int.h

diff --git a/Documentation/virtual/kvm/kvmi.rst b/Documentation/virtual/kvm/kvmi.rst
new file mode 100644
index 000000000000..d54caf8d974f
--- /dev/null
+++ b/Documentation/virtual/kvm/kvmi.rst
@@ -0,0 +1,75 @@
+=========================================================
+KVMI - The kernel virtual machine introspection subsystem
+=========================================================
+
+The KVM introspection subsystem provides a facility for applications running
+on the host or in a separate VM, to control the execution of other VM-s
+(pause, resume, shutdown), query the state of the vCPUs (GPRs, MSRs etc.),
+alter the page access bits in the shadow page tables (only for the hardware
+backed ones, eg. Intel's EPT) and receive notifications when events of
+interest have taken place (shadow page table level faults, key MSR writes,
+hypercalls etc.). Some notifications can be responded to with an action
+(like preventing an MSR from being written), others are mere informative
+(like breakpoint events which can be used for execution tracing).
+With few exceptions, all events are optional. An application using this
+subsystem will explicitly register for them.
+
+The use case that gave way for the creation of this subsystem is to monitor
+the guest OS and as such the ABI/API is highly influenced by how the guest
+software (kernel, applications) sees the world. For example, some events
+provide information specific for the host CPU architecture
+(eg. MSR_IA32_SYSENTER_EIP) merely because its leveraged by guest software
+to implement a critical feature (fast system calls).
+
+At the moment, the target audience for KVMI are security software authors
+that wish to perform forensics on newly discovered threats (exploits) or
+to implement another layer of security like preventing a large set of
+kernel rootkits simply by "locking" the kernel image in the shadow page
+tables (ie. enforce .text r-x, .rodata rw- etc.). It's the latter case that
+made KVMI a separate subsystem, even though many of these features are
+available in the device manager (eg. QEMU). The ability to build a security
+application that does not interfere (in terms of performance) with the
+guest software asks for a specialized interface that is designed for minimum
+overhead.
+
+API/ABI
+=======
+
+This chapter describes the VMI interface used to monitor and control local
+guests from a user application.
+
+Overview
+--------
+
+The interface is socket based, one connection for every VM. One end is in the
+host kernel while the other is held by the user application (introspection
+tool).
+
+The initial connection is established by an application running on the host
+(eg. QEMU) that connects to the introspection tool and after a handshake the
+socket is passed to the host kernel making all further communication take
+place between it and the introspection tool. The initiating party (QEMU) can
+close its end so that any potential exploits cannot take a hold of it.
+
+The socket protocol allows for commands and events to be multiplexed over
+the same connection. As such, it is possible for the introspection tool to
+receive an event while waiting for the result of a command. Also, it can
+send a command while the host kernel is waiting for a reply to an event.
+
+The kernel side of the socket communication is blocking and will wait for
+an answer from its peer indefinitely or until the guest is powered off
+(killed), restarted or the peer goes away, at which point it will wake
+up and properly cleanup as if the introspection subsystem has never been
+used on that guest. Obviously, whether the guest can really continue
+normal execution depends on whether the introspection tool has made any
+modifications that require an active KVMI channel.
+
+Memory access safety
+--------------------
+
+The KVMI API gives access to the entire guest physical address space but
+provides no information on which parts of it are system RAM and which are
+device-specific memory (DMA, emulated MMIO, reserved by a passthrough
+device etc.). It is up to the user to determine, using the guest operating
+system data structures, the areas that are safe to access (code, stack, heap
+etc.).
```
