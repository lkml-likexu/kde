#### [PATCH 1/8] KVM: arm64: Reset the PMU in preemptible context
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
We've become very cautious to now always reset the vcpu when nothing
is loaded on the physical CPU. To do so, we now disable preemption
and do a kvm_arch_vcpu_put() to make sure we have all the state
in memory (and that it won't be loaded behind out back).

This now causes issues with resetting the PMU, which calls into perf.
Perf itself uses mutexes, which clashes with the lack of preemption.
It is worth realizing that the PMU is fully emulated, and that
no PMU state is ever loaded on the physical CPU. This means we can
perfectly reset the PMU outside of the non-preemptible section.

Fixes: e761a927bc9a ("KVM: arm/arm64: Reset the VCPU without preemption and vcpu state loaded")
Reported-by: Julien Grall <julien.grall@arm.com>
Tested-by: Julien Grall <julien.grall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/reset.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] Documentation: kvm: clarify KVM_SET_USER_MEMORY_REGION
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The documentation does not mention how to delete a slot, add the
information.

Reported-by: Nathaniel McCallum <npmccallum@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/api.txt | 18 ++++++++++--------
 1 file changed, 10 insertions(+), 8 deletions(-)

```
#### [GIT PULL] KVM/ARM fixes for 5.1-rc3
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Paolo, Radim,

Here's a handful of KVM/ARM fixes for 5.1-rc3. We have a number of
stage-2 page table fixes, some srcu fixes the the ITS emulation, a
reset fix for the virtual PMU, a GICv4 regression fix, and some
cleanups.

Please pull,

	M.

The following changes since commit 9e98c678c2d6ae3a17cb2de55d17f69dddaa231b:

  Linux 5.1-rc1 (2019-03-17 14:22:26 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.1

for you to fetch changes up to 8324c3d518cfd69f2a17866b52c13bf56d3042d8:

  KVM: arm/arm64: Comments cleanup in mmu.c (2019-03-28 13:17:17 +0000)

----------------------------------------------------------------
KVM/ARM fixes for 5.1

- Fix THP handling in the presence of pre-existing PTEs
- Honor request for PTE mappings even when THPs are available
- GICv4 performance improvement
- Take the srcu lock when writing to guest-controlled ITS data structures
- Reset the virtual PMU in preemptible context
- Various cleanups

----------------------------------------------------------------
Marc Zyngier (4):
      KVM: arm64: Reset the PMU in preemptible context
      arm64: KVM: Always set ICH_HCR_EL2.EN if GICv4 is enabled
      KVM: arm/arm64: vgic-its: Take the srcu lock when writing to guest memory
      KVM: arm/arm64: vgic-its: Take the srcu lock when parsing the memslots

Suzuki K Poulose (2):
      KVM: arm/arm64: Enforce PTE mappings at stage2 when needed
      KVM: arm/arm64: Fix handling of stage2 huge mappings

YueHaibing (1):
      KVM: arm/arm64: vgic-its: Make attribute accessors static

Zenghui Yu (1):
      KVM: arm/arm64: Comments cleanup in mmu.c

 arch/arm/include/asm/kvm_mmu.h        |  11 +++
 arch/arm/include/asm/stage2_pgtable.h |   2 +
 arch/arm64/include/asm/kvm_mmu.h      |  11 +++
 arch/arm64/kvm/reset.c                |   6 +-
 virt/kvm/arm/hyp/vgic-v3-sr.c         |   4 +-
 virt/kvm/arm/mmu.c                    | 125 ++++++++++++++++++++--------------
 virt/kvm/arm/vgic/vgic-its.c          |  31 +++++----
 virt/kvm/arm/vgic/vgic-v3.c           |   4 +-
 virt/kvm/arm/vgic/vgic.c              |  14 ++--
 9 files changed, 133 insertions(+), 75 deletions(-)

From patchwork Thu Mar 28 13:36:02 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <Marc.Zyngier@arm.com>
X-Patchwork-Id: 10874961
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B417922
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Mar 2019 13:36:43 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 0626A28DBC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Mar 2019 13:36:43 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id EE2EA28DC2; Thu, 28 Mar 2019 13:36:42 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 8356328DBC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 Mar 2019 13:36:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725816AbfC1Ngl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 Mar 2019 09:36:41 -0400
Received: from usa-sjc-mx-foss1.foss.arm.com ([217.140.101.70]:44542 "EHLO
        foss.arm.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726338AbfC1Ngl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Mar 2019 09:36:41 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.72.51.249])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 822DC15AB;
        Thu, 28 Mar 2019 06:36:40 -0700 (PDT)
Received: from filthy-habits.cambridge.arm.com
 (filthy-habits.cambridge.arm.com [10.1.196.92])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 D47043F59C;
        Thu, 28 Mar 2019 06:36:37 -0700 (PDT)
From: Marc Zyngier <marc.zyngier@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>,
        Julien Grall <julien.grall@arm.com>,
        Nianyao Tang <tangnianyao@huawei.com>,
        Shameerali Kolothum Thodi
        <shameerali.kolothum.thodi@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        YueHaibing <yuehaibing@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Zheng Xiang <zhengxiang9@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/8] arm64: KVM: Always set ICH_HCR_EL2.EN if GICv4 is enabled
Date: Thu, 28 Mar 2019 13:36:02 +0000
Message-Id: <20190328133608.110805-3-marc.zyngier@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190328133608.110805-1-marc.zyngier@arm.com>
References: <20190328133608.110805-1-marc.zyngier@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

The normal interrupt flow is not to enable the vgic when no virtual
interrupt is to be injected (i.e. the LRs are empty). But when a guest
is likely to use GICv4 for LPIs, we absolutely need to switch it on
at all times. Otherwise, VLPIs only get delivered when there is something
in the LRs, which doesn't happen very often.

Reported-by: Nianyao Tang <tangnianyao@huawei.com>
Tested-by: Shameerali Kolothum Thodi <shameerali.kolothum.thodi@huawei.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 virt/kvm/arm/hyp/vgic-v3-sr.c |  4 ++--
 virt/kvm/arm/vgic/vgic.c      | 14 ++++++++++----
 2 files changed, 12 insertions(+), 6 deletions(-)

```
#### [PATCH] kvm: move KVM_CAP_NR_MEMSLOTS to common code
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
All architectures except MIPS were defining it in the same way,
and memory slots are handled entirely by common code so there
is no point in keeping the definition per-architecture.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/api.txt | 5 ++---
 arch/powerpc/kvm/powerpc.c        | 3 ---
 arch/s390/kvm/kvm-s390.c          | 3 ---
 arch/x86/kvm/x86.c                | 3 ---
 virt/kvm/arm/arm.c                | 3 ---
 virt/kvm/kvm_main.c               | 2 ++
 6 files changed, 4 insertions(+), 15 deletions(-)

```
#### [PATCH][kvm-unit-test VMX]: Use #define for bit# 1 in GUEST_RFLAGS
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 x86/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC PATCH 01/18] KVM: x86: Move emulation of RSM, i.e. leave_smm, out of emulator
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_emulate.h |   1 +
 arch/x86/kvm/emulate.c             | 298 +--------------------------
 arch/x86/kvm/x86.c                 | 316 +++++++++++++++++++++++++++++
 3 files changed, 318 insertions(+), 297 deletions(-)

```
#### [PATCH RFC] KVM: x86: vmx: throttle immediate exit through preemtion timer to assist buggy guests
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
This is embarassing but we have another Windows/Hyper-V issue to workaround
in KVM (or QEMU). Hope "RFC" makes it less offensive.

It was noticed that Hyper-V guest on q35 KVM/QEMU VM hangs on boot if e.g.
'piix4-usb-uhci' device is attached. The problem with this device is that
it uses level-triggered interrupts.

The 'hang' scenario develops like this:
1) Hyper-V boots and QEMU is trying to inject two irq simultaneously. One
 of them is level-triggered. KVM injects the edge-triggered one and
 requests immediate exit to inject the level-triggered:

 kvm_set_irq:          gsi 23 level 1 source 0
 kvm_msi_set_irq:      dst 0 vec 80 (Fixed|physical|level)
 kvm_apic_accept_irq:  apicid 0 vec 80 (Fixed|edge)
 kvm_msi_set_irq:      dst 0 vec 96 (Fixed|physical|edge)
 kvm_apic_accept_irq:  apicid 0 vec 96 (Fixed|edge)
 kvm_nested_vmexit_inject: reason EXTERNAL_INTERRUPT info1 0 info2 0 int_info 80000060 int_info_err 0

2) Hyper-V requires one of its VMs to run to handle the situation but
 immediate exit happens:

 kvm_entry:            vcpu 0
 kvm_exit:             reason VMRESUME rip 0xfffff80006a40115 info 0 0
 kvm_entry:            vcpu 0
 kvm_exit:             reason PREEMPTION_TIMER rip 0xfffff8022f3d8350 info 0 0
 kvm_nested_vmexit:    rip fffff8022f3d8350 reason PREEMPTION_TIMER info1 0 info2 0 int_info 0 int_info_err 0
 kvm_nested_vmexit_inject: reason EXTERNAL_INTERRUPT info1 0 info2 0 int_info 80000050 int_info_err 0

3) Hyper-V doesn't want to deal with the second irq (as its VM still didn't
 process the first one) so it just does 'EOI' for level-triggered interrupt
 and this causes re-injection:

 kvm_exit:             reason EOI_INDUCED rip 0xfffff80006a17e1a info 50 0
 kvm_eoi:              apicid 0 vector 80
 kvm_userspace_exit:   reason KVM_EXIT_IOAPIC_EOI (26)
 kvm_set_irq:          gsi 23 level 1 source 0
 kvm_msi_set_irq:      dst 0 vec 80 (Fixed|physical|level)
 kvm_apic_accept_irq:  apicid 0 vec 80 (Fixed|edge)
 kvm_entry:            vcpu 0

4) As we arm preemtion timer again we get stuck in the infinite loop:

 kvm_exit:             reason VMRESUME rip 0xfffff80006a40115 info 0 0
 kvm_entry:            vcpu 0
 kvm_exit:             reason PREEMPTION_TIMER rip 0xfffff8022f3d8350 info 0 0
 kvm_nested_vmexit:    rip fffff8022f3d8350 reason PREEMPTION_TIMER info1 0 info2 0 int_info 0 int_info_err 0
 kvm_nested_vmexit_inject: reason EXTERNAL_INTERRUPT info1 0 info2 0 int_info 80000050 int_info_err 0
 kvm_entry:            vcpu 0
 kvm_exit:             reason EOI_INDUCED rip 0xfffff80006a17e1a info 50 0
 kvm_eoi:              apicid 0 vector 80
 kvm_userspace_exit:   reason KVM_EXIT_IOAPIC_EOI (26)
 kvm_set_irq:          gsi 23 level 1 source 0
 kvm_msi_set_irq:      dst 0 vec 80 (Fixed|physical|level)
 kvm_apic_accept_irq:  apicid 0 vec 80 (Fixed|edge)
 kvm_entry:            vcpu 0
 kvm_exit:             reason VMRESUME rip 0xfffff80006a40115 info 0 0
 ...

How does this work on hardware? I don't really know but it seems that we
were dealing with similar issues before, see commit 184564efae4d7 ("kvm:
ioapic: conditionally delay irq delivery duringeoi broadcast"). In case EOI
doesn't always cause an *immediate* interrupt re-injection some progress
can be made.

An alternative approach would be to port the above mentioned commit to
QEMU's ioapic implementation. I'm, however, not sure that level-triggered
interrupts is a must to trigger the issue.

HV_TIMER_THROTTLE/HV_TIMER_DELAY are more or less arbitrary. I haven't
looked at SVM yet but their immediate exit implementation does
smp_send_reschedule(), I'm not sure this can cause the above described
lockup.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmcs.h |  2 ++
 arch/x86/kvm/vmx/vmx.c  | 24 +++++++++++++++++++++++-
 2 files changed, 25 insertions(+), 1 deletion(-)

```
