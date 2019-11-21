#### [PATCH 01/22] KVM: arm/arm64: Allow reporting non-ISV data aborts to userspace
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11254399
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E9EA13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 16:43:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 768B92089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 16:43:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1574268189;
	bh=ZQ9MPGT+BHzl1JSIB+vGWn4stEHI9oRSQJ+x1CuhuU4=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=jSBMuCcUkO5Fbb3zLXku2BR7dWmlyyEMEmMg4YrZ1lDHnd8ubbxNnIoOcKjEG/UKw
	 weh9EKGyihMtscrOh2EFD02TO3a0tCFFDa3WB/9NmY6uJAmRsn7BhHwxZKnLqgizLJ
	 bU1OhE7k7WsG1FaLbjvCngxhUv8N5iACXlFDQaBc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732873AbfKTQnI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 11:43:08 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:58401 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732858AbfKTQnH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 Nov 2019 11:43:07 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iXT4A-0007RI-GB; Wed, 20 Nov 2019 17:42:54 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Heinrich Schuchardt <xypron.glpk@gmx.de>,
        Julien Grall <julien.grall@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Steven Price <steven.price@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [PATCH 01/22] KVM: arm/arm64: Allow reporting non-ISV data aborts to
 userspace
Date: Wed, 20 Nov 2019 16:42:15 +0000
Message-Id: <20191120164236.29359-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191120164236.29359-1-maz@kernel.org>
References: <20191120164236.29359-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com, graf@amazon.com,
 drjones@redhat.com, borntraeger@de.ibm.com, christoffer.dall@arm.com,
 eric.auger@redhat.com, xypron.glpk@gmx.de, julien.grall@arm.com,
 mark.rutland@arm.com, bigeasy@linutronix.de, steven.price@arm.com,
 tglx@linutronix.de, will@kernel.org, yuzenghui@huawei.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Christoffer Dall <christoffer.dall@arm.com>

For a long time, if a guest accessed memory outside of a memslot using
any of the load/store instructions in the architecture which doesn't
supply decoding information in the ESR_EL2 (the ISV bit is not set), the
kernel would print the following message and terminate the VM as a
result of returning -ENOSYS to userspace:

  load/store instruction decoding not implemented

The reason behind this message is that KVM assumes that all accesses
outside a memslot is an MMIO access which should be handled by
userspace, and we originally expected to eventually implement some sort
of decoding of load/store instructions where the ISV bit was not set.

However, it turns out that many of the instructions which don't provide
decoding information on abort are not safe to use for MMIO accesses, and
the remaining few that would potentially make sense to use on MMIO
accesses, such as those with register writeback, are not used in
practice.  It also turns out that fetching an instruction from guest
memory can be a pretty horrible affair, involving stopping all CPUs on
SMP systems, handling multiple corner cases of address translation in
software, and more.  It doesn't appear likely that we'll ever implement
this in the kernel.

What is much more common is that a user has misconfigured his/her guest
and is actually not accessing an MMIO region, but just hitting some
random hole in the IPA space.  In this scenario, the error message above
is almost misleading and has led to a great deal of confusion over the
years.

It is, nevertheless, ABI to userspace, and we therefore need to
introduce a new capability that userspace explicitly enables to change
behavior.

This patch introduces KVM_CAP_ARM_NISV_TO_USER (NISV meaning Non-ISV)
which does exactly that, and introduces a new exit reason to report the
event to userspace.  User space can then emulate an exception to the
guest, restart the guest, suspend the guest, or take any other
appropriate action as per the policy of the running system.

Reported-by: Heinrich Schuchardt <xypron.glpk@gmx.de>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 Documentation/virt/kvm/api.txt       | 33 ++++++++++++++++++++++++++++
 arch/arm/include/asm/kvm_arm.h       |  1 +
 arch/arm/include/asm/kvm_emulate.h   |  5 +++++
 arch/arm/include/asm/kvm_host.h      |  8 +++++++
 arch/arm64/include/asm/kvm_emulate.h |  5 +++++
 arch/arm64/include/asm/kvm_host.h    |  8 +++++++
 include/uapi/linux/kvm.h             |  7 ++++++
 virt/kvm/arm/arm.c                   | 21 ++++++++++++++++++
 virt/kvm/arm/mmio.c                  |  9 +++++++-
 9 files changed, 96 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm updates for 5.5
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11254397
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A9FF186D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 16:43:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 180C32089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 16:43:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1574268189;
	bh=Omcl9wlNP7NURVFJh9E69ewTmowfuE79PqmPPaFQ4X4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=cHIyWAV/y9K0a9ssGmMHpNaec7UO7T+zPZn/PfSVOufWnO5Kw2Ya76fnBoBwwn3yv
	 XksW96ATssreV9msG9QMVMbjEUxYA1izXH/lBBWecR6yYPXfK7CrpX3LJ3AmTZv0QS
	 l12SUqLf808a9fZIaygSV3lJAnYPt0bLq2IhspGM=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732870AbfKTQnI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 11:43:08 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:36603 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732847AbfKTQnH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 20 Nov 2019 11:43:07 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iXT49-0007RI-KJ; Wed, 20 Nov 2019 17:42:53 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Heinrich Schuchardt <xypron.glpk@gmx.de>,
        Julien Grall <julien.grall@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        Steven Price <steven.price@arm.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Will Deacon <will@kernel.org>,
        Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Subject: [GIT PULL] KVM/arm updates for 5.5
Date: Wed, 20 Nov 2019 16:42:14 +0000
Message-Id: <20191120164236.29359-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, rkrcmar@redhat.com, graf@amazon.com,
 drjones@redhat.com, borntraeger@de.ibm.com, christoffer.dall@arm.com,
 eric.auger@redhat.com, xypron.glpk@gmx.de, julien.grall@arm.com,
 mark.rutland@arm.com, bigeasy@linutronix.de, steven.price@arm.com,
 tglx@linutronix.de, will@kernel.org, yuzenghui@huawei.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo, Radim,

Here's the bulk of KVM/arm updates for 5.5. On the menu, two new features:
- Stolen time is finally exposed to guests. Yay!
- We can report (and potentially emulate) instructions that KVM cannot
  handle in kernel space to userspace. Yay again!

Apart from that, a fairly mundane bag of perf optimization, cleanup and
bug fixes.

Note that this series is based on a shared branch with the arm64 tree,
avoiding a potential delicate merge.

Please pull,

	M.

The following changes since commit e6ea46511b1ae8c4491904c79411fcd29139af14:

  firmware: arm_sdei: use common SMCCC_CONDUIT_* (2019-10-14 10:55:14 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.5

for you to fetch changes up to cd7056ae34af0e9424da97bbc7d2b38246ba8a2c:

  Merge remote-tracking branch 'kvmarm/misc-5.5' into kvmarm/next (2019-11-08 11:27:29 +0000)

----------------------------------------------------------------
KVM/arm updates for Linux 5.5:

- Allow non-ISV data aborts to be reported to userspace
- Allow injection of data aborts from userspace
- Expose stolen time to guests
- GICv4 performance improvements
- vgic ITS emulation fixes
- Simplify FWB handling
- Enable halt pool counters
- Make the emulated timer PREEMPT_RT compliant

----------------------------------------------------------------
Christian Borntraeger (1):
      KVM: arm/arm64: Show halt poll counters in debugfs

Christoffer Dall (4):
      KVM: arm/arm64: Allow reporting non-ISV data aborts to userspace
      KVM: arm/arm64: Allow user injection of external data aborts
      KVM: arm/arm64: Factor out hypercall handling from PSCI code
      KVM: arm64: Don't set HCR_EL2.TVM when S2FWB is supported

Marc Zyngier (6):
      Merge remote-tracking branch 'arm64/for-next/smccc-conduit-cleanup' into kvm-arm64/stolen-time
      Merge remote-tracking branch 'kvmarm/kvm-arm64/stolen-time' into kvmarm-master/next
      KVM: arm64: vgic-v4: Move the GICv4 residency flow to be driven by vcpu_load/put
      KVM: vgic-v4: Track the number of VLPIs per vcpu
      KVM: arm64: Opportunistically turn off WFI trapping when using direct LPI injection
      Merge remote-tracking branch 'kvmarm/misc-5.5' into kvmarm/next

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

Thomas Gleixner (1):
      KVM: arm/arm64: Let the timer expire in hardirq context on RT

Zenghui Yu (3):
      KVM: arm/arm64: vgic: Remove the declaration of kvm_send_userspace_msi()
      KVM: arm/arm64: vgic: Fix some comments typo
      KVM: arm/arm64: vgic: Don't rely on the wrong pending table

 Documentation/admin-guide/kernel-parameters.txt |   6 +-
 Documentation/virt/kvm/api.txt                  |  55 +++++++++-
 Documentation/virt/kvm/arm/pvtime.rst           |  80 ++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt         |  14 +++
 arch/arm/include/asm/kvm_arm.h                  |   1 +
 arch/arm/include/asm/kvm_emulate.h              |   9 +-
 arch/arm/include/asm/kvm_host.h                 |  33 ++++++
 arch/arm/include/uapi/asm/kvm.h                 |   3 +-
 arch/arm/kvm/Makefile                           |   2 +-
 arch/arm/kvm/guest.c                            |  14 +++
 arch/arm/kvm/handle_exit.c                      |   2 +-
 arch/arm/mm/proc-v7-bugs.c                      |  13 +--
 arch/arm64/include/asm/kvm_arm.h                |   3 +-
 arch/arm64/include/asm/kvm_emulate.h            |  26 ++++-
 arch/arm64/include/asm/kvm_host.h               |  37 +++++++
 arch/arm64/include/asm/paravirt.h               |   9 +-
 arch/arm64/include/asm/pvclock-abi.h            |  17 +++
 arch/arm64/include/uapi/asm/kvm.h               |   5 +-
 arch/arm64/kernel/cpu_errata.c                  |  81 +++++---------
 arch/arm64/kernel/paravirt.c                    | 140 ++++++++++++++++++++++++
 arch/arm64/kernel/time.c                        |   3 +
 arch/arm64/kvm/Kconfig                          |   4 +
 arch/arm64/kvm/Makefile                         |   2 +
 arch/arm64/kvm/guest.c                          |  23 ++++
 arch/arm64/kvm/handle_exit.c                    |   4 +-
 arch/arm64/kvm/inject_fault.c                   |   4 +-
 drivers/irqchip/irq-gic-v4.c                    |   7 +-
 include/Kbuild                                  |   2 +
 include/kvm/arm_hypercalls.h                    |  43 ++++++++
 include/kvm/arm_psci.h                          |   2 +-
 include/kvm/arm_vgic.h                          |   8 +-
 include/linux/arm-smccc.h                       |  59 ++++++++++
 include/linux/cpuhotplug.h                      |   1 +
 include/linux/irqchip/arm-gic-v4.h              |   4 +
 include/linux/kvm_host.h                        |  26 ++++-
 include/linux/kvm_types.h                       |   2 +
 include/uapi/linux/kvm.h                        |  10 ++
 virt/kvm/arm/arch_timer.c                       |   8 +-
 virt/kvm/arm/arm.c                              |  49 ++++++++-
 virt/kvm/arm/hypercalls.c                       |  71 ++++++++++++
 virt/kvm/arm/mmio.c                             |   9 +-
 virt/kvm/arm/psci.c                             |  84 +-------------
 virt/kvm/arm/pvtime.c                           | 131 ++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic-init.c                   |   1 +
 virt/kvm/arm/vgic/vgic-its.c                    |   3 +
 virt/kvm/arm/vgic/vgic-v3.c                     |  12 +-
 virt/kvm/arm/vgic/vgic-v4.c                     |  59 +++++-----
 virt/kvm/arm/vgic/vgic.c                        |   4 -
 virt/kvm/arm/vgic/vgic.h                        |   2 -
 virt/kvm/kvm_main.c                             |   6 +-
 50 files changed, 968 insertions(+), 225 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
#### [RFC V4 1/2] This commit introduced ifcvf_base layer.
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11253391
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E819109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 09:19:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 737DD223D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 09:19:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728157AbfKTJTc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 04:19:32 -0500
Received: from mga06.intel.com ([134.134.136.31]:61597 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726001AbfKTJTc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 04:19:32 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Nov 2019 01:19:31 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,221,1571727600";
   d="scan'208";a="237660932"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga002.fm.intel.com with ESMTP; 20 Nov 2019 01:19:28 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC V4 1/2] This commit introduced ifcvf_base layer.
Date: Wed, 20 Nov 2019 17:17:10 +0800
Message-Id: <1574241431-24792-2-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1574241431-24792-1-git-send-email-lingshan.zhu@intel.com>
References: <1574241431-24792-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IFC NIC is a new type of Intel hardware virtio datapath
offloading card, this commit intend to handle hardware operations
and configurations.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_base.c | 326 +++++++++++++++++++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 129 ++++++++++++++++
 2 files changed, 455 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h

diff --git a/drivers/vhost/ifcvf/ifcvf_base.c b/drivers/vhost/ifcvf/ifcvf_base.c
new file mode 100644
index 0000000..6bf2ddd
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.c
@@ -0,0 +1,326 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include "ifcvf_base.h"
+
+static void *get_cap_addr(struct ifcvf_hw *hw, struct virtio_pci_cap *cap)
+{
+	struct ifcvf_adapter *ifcvf;
+	u32 length, offset;
+	u8 bar;
+
+	length = le32_to_cpu(cap->length);
+	offset = le32_to_cpu(cap->offset);
+	bar = le32_to_cpu(cap->bar);
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+
+	if (bar >= IFCVF_PCI_MAX_RESOURCE) {
+		IFC_DBG(ifcvf->dev,
+			"Invalid bar number %u to get capabilities\n", bar);
+		return NULL;
+	}
+
+	if (offset + length > hw->mem_resource[cap->bar].len) {
+		IFC_DBG(ifcvf->dev,
+			"offset(%u) + len(%u) overflows bar%u to get capabilities\n",
+			offset, length, bar);
+		return NULL;
+	}
+
+	return hw->mem_resource[bar].addr + offset;
+}
+
+int ifcvf_read_config_range(struct pci_dev *dev,
+			uint32_t *val, int size, int where)
+{
+	int ret, i;
+
+	for (i = 0; i < size; i += 4) {
+		ret = pci_read_config_dword(dev, where + i, val + i / 4);
+		if (ret < 0)
+			return ret;
+	}
+
+	return 0;
+}
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev)
+{
+	struct virtio_pci_cap cap;
+	u16 notify_off;
+	int ret;
+	u8 pos;
+	u32 i;
+
+	ret = pci_read_config_byte(dev, PCI_CAPABILITY_LIST, &pos);
+
+	if (ret < 0) {
+		IFC_ERR(&dev->dev, "Failed to read PCI capability list\n");
+		return -EIO;
+	}
+
+	while (pos) {
+		ret = ifcvf_read_config_range(dev, (u32 *)&cap,
+					      sizeof(cap), pos);
+
+		if (ret < 0) {
+			IFC_ERR(&dev->dev, "Failed to get PCI capability at %x\n",
+				pos);
+			break;
+		}
+
+		if (cap.cap_vndr != PCI_CAP_ID_VNDR)
+			goto next;
+
+		IFC_DBG(&dev->dev, "read PCI config: config type: %u, PCI bar: %u, PCI bar offset: %u, PCI config len: %u\n",
+			cap.cfg_type, cap.bar, cap.offset, cap.length);
+
+		switch (cap.cfg_type) {
+		case VIRTIO_PCI_CAP_COMMON_CFG:
+			hw->common_cfg = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->common_cfg = %p\n",
+				hw->common_cfg);
+			break;
+		case VIRTIO_PCI_CAP_NOTIFY_CFG:
+			pci_read_config_dword(dev, pos + sizeof(cap),
+					      &hw->notify_off_multiplier);
+			hw->notify_bar = cap.bar;
+			hw->notify_base = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->notify_base = %p\n",
+				hw->notify_base);
+			break;
+		case VIRTIO_PCI_CAP_ISR_CFG:
+			hw->isr = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->isr = %p\n", hw->isr);
+			break;
+		case VIRTIO_PCI_CAP_DEVICE_CFG:
+			hw->net_cfg = get_cap_addr(hw, &cap);
+			IFC_DBG(&dev->dev, "hw->net_cfg = %p\n", hw->net_cfg);
+			break;
+		}
+next:
+		pos = cap.cap_next;
+	}
+
+	if (hw->common_cfg == NULL || hw->notify_base == NULL ||
+	    hw->isr == NULL || hw->net_cfg == NULL) {
+		IFC_DBG(&dev->dev, "Incomplete PCI capabilities\n");
+		return -1;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		iowrite16(i, &hw->common_cfg->queue_select);
+		notify_off = ioread16(&hw->common_cfg->queue_notify_off);
+		hw->vring->notify_addr[i] = (void *)((u8 *)hw->notify_base +
+				     notify_off * hw->notify_off_multiplier);
+	}
+
+	hw->lm_cfg = hw->mem_resource[IFCVF_LM_BAR].addr;
+
+	IFC_DBG(&dev->dev, "PCI capability mapping: common cfg: %p, notify base: %p\n, isr cfg: %p, device cfg: %p, multiplier: %u\n",
+		hw->common_cfg, hw->notify_base, hw->isr,
+		hw->net_cfg, hw->notify_off_multiplier);
+
+	return 0;
+}
+
+u8 ifcvf_get_status(struct ifcvf_hw *hw)
+{
+	return ioread8(&hw->common_cfg->device_status);
+}
+
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status)
+{
+	iowrite8(status, &hw->common_cfg->device_status);
+}
+
+void ifcvf_reset(struct ifcvf_hw *hw)
+{
+	ifcvf_set_status(hw, 0);
+	ifcvf_get_status(hw);
+}
+
+static void ifcvf_add_status(struct ifcvf_hw *hw, u8 status)
+{
+	if (status != 0)
+		status |= ifcvf_get_status(hw);
+
+	ifcvf_set_status(hw, status);
+	ifcvf_get_status(hw);
+}
+
+u64 ifcvf_get_features(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+	u32 features_lo, features_hi;
+
+	iowrite32(0, &cfg->device_feature_select);
+	features_lo = ioread32(&cfg->device_feature);
+
+	iowrite32(1, &cfg->device_feature_select);
+	features_hi = ioread32(&cfg->device_feature);
+
+	return ((u64)features_hi << 32) | features_lo;
+}
+
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+		       void *dst, int length)
+{
+	u8 old_gen, new_gen, *p;
+	int i;
+
+	WARN_ON(offset + length > sizeof (struct virtio_net_config));
+
+	do {
+		old_gen = ioread8(&hw->common_cfg->config_generation);
+		p = dst;
+
+		for (i = 0; i < length; i++)
+			*p++ = ioread8((u8 *)hw->net_cfg + offset + i);
+
+		new_gen = ioread8(&hw->common_cfg->config_generation);
+	} while (old_gen != new_gen);
+}
+
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length)
+{
+	const u8 *p;
+	int i;
+
+	p = src;
+	WARN_ON(offset + length > sizeof(struct virtio_net_config));
+
+	for (i = 0; i < length; i++)
+		iowrite8(*p++, (u8 *)hw->net_cfg + offset + i);
+}
+
+static void ifcvf_set_features(struct ifcvf_hw *hw, u64 features)
+{
+	struct virtio_pci_common_cfg *cfg = hw->common_cfg;
+
+	iowrite32(0, &cfg->guest_feature_select);
+	iowrite32((u32)features, &cfg->guest_feature);
+
+	iowrite32(1, &cfg->guest_feature_select);
+	iowrite32(features >> 32, &cfg->guest_feature);
+}
+
+static int ifcvf_config_features(struct ifcvf_hw *hw)
+{
+	struct ifcvf_adapter *ifcvf;
+
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+	ifcvf_set_features(hw, hw->req_features);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_FEATURES_OK);
+
+	if (!(ifcvf_get_status(hw) & VIRTIO_CONFIG_S_FEATURES_OK)) {
+		IFC_ERR(ifcvf->dev, "Failed to set FEATURES_OK status\n");
+		return -EIO;
+	}
+
+	return 0;
+}
+
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi)
+{
+	iowrite32(val & ((1ULL << 32) - 1), lo);
+	iowrite32(val >> 32, hi);
+}
+
+static int ifcvf_hw_enable(struct ifcvf_hw *hw)
+{
+	struct ifcvf_lm_cfg __iomem *ifcvf_lm;
+	struct virtio_pci_common_cfg *cfg;
+	struct ifcvf_adapter *ifcvf;
+	u32 __iomem* idx_addr;
+	u32 i, val;
+
+	ifcvf_lm = (struct ifcvf_lm_cfg*)hw->lm_cfg;
+	ifcvf = container_of(hw, struct ifcvf_adapter, vf);
+	cfg = hw->common_cfg;
+	iowrite16(IFCVF_MSI_CONFIG_OFF, &cfg->msix_config);
+
+	if (ioread16(&cfg->msix_config) == VIRTIO_MSI_NO_VECTOR) {
+		IFC_ERR(ifcvf->dev, "No msix vector for device config\n");
+		return -1;
+	}
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		if (!hw->vring[i].ready)
+			break;
+
+		iowrite16(i, &cfg->queue_select);
+		io_write64_twopart(hw->vring[i].desc, &cfg->queue_desc_lo,
+				&cfg->queue_desc_hi);
+		io_write64_twopart(hw->vring[i].avail, &cfg->queue_avail_lo,
+				&cfg->queue_avail_hi);
+		io_write64_twopart(hw->vring[i].used, &cfg->queue_used_lo,
+				&cfg->queue_used_hi);
+		iowrite16(hw->vring[i].size, &cfg->queue_size);
+		idx_addr = &(ifcvf_lm->vring_lm_cfg[i/IFCVF_MAX_QUEUES].idx_addr[i%IFCVF_MAX_QUEUES]);
+		val = (u32)hw->vring[i].last_avail_idx |
+			((u32)hw->vring[i].last_used_idx << 16);
+		iowrite32(val, idx_addr);
+		iowrite16(i + IFCVF_MSI_QUEUE_OFF, &cfg->queue_msix_vector);
+
+		if (ioread16(&cfg->queue_msix_vector) ==
+		    VIRTIO_MSI_NO_VECTOR) {
+			IFC_ERR(ifcvf->dev,
+				"No msix vector for queue %u\n", i);
+			return -1;
+		}
+
+		iowrite16(1, &cfg->queue_enable);
+	}
+
+	return 0;
+}
+
+static void ifcvf_hw_disable(struct ifcvf_hw *hw)
+{
+	struct virtio_pci_common_cfg *cfg;
+	u32 i;
+
+	cfg = hw->common_cfg;
+	iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->msix_config);
+
+	for (i = 0; i < hw->nr_vring; i++) {
+		iowrite16(i, &cfg->queue_select);
+		iowrite16(0, &cfg->queue_enable);
+		iowrite16(VIRTIO_MSI_NO_VECTOR, &cfg->queue_msix_vector);
+	}
+
+	ioread16(&cfg->queue_msix_vector);
+}
+
+int ifcvf_start_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_reset(hw);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_ACKNOWLEDGE);
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER);
+
+	if (ifcvf_config_features(hw) < 0)
+		return -1;
+
+	if (ifcvf_hw_enable(hw) < 0)
+		return -1;
+
+	ifcvf_add_status(hw, VIRTIO_CONFIG_S_DRIVER_OK);
+
+	return 0;
+}
+
+void ifcvf_stop_hw(struct ifcvf_hw *hw)
+{
+	ifcvf_hw_disable(hw);
+	ifcvf_reset(hw);
+}
+
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid)
+{
+	iowrite16(qid, hw->vring->notify_addr[qid]);
+}
diff --git a/drivers/vhost/ifcvf/ifcvf_base.h b/drivers/vhost/ifcvf/ifcvf_base.h
new file mode 100644
index 0000000..d757f75
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_base.h
@@ -0,0 +1,129 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#ifndef _IFCVF_H_
+#define _IFCVF_H_
+
+#include <linux/mdev_virtio.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/pci_regs.h>
+#include <uapi/linux/virtio_net.h>
+#include <uapi/linux/virtio_config.h>
+#include <uapi/linux/virtio_pci.h>
+
+#define IFCVF_VENDOR_ID         0x1AF4
+#define IFCVF_DEVICE_ID         0x1041
+#define IFCVF_SUBSYS_VENDOR_ID  0x8086
+#define IFCVF_SUBSYS_DEVICE_ID  0x001A
+
+#define IFCVF_MDEV_LIMIT	1
+
+#define IFC_SUPPORTED_FEATURES \
+		((1ULL << VIRTIO_NET_F_MAC)			| \
+		 (1ULL << VIRTIO_F_ANY_LAYOUT)			| \
+		 (1ULL << VIRTIO_F_VERSION_1)			| \
+		 (1ULL << VIRTIO_F_ORDER_PLATFORM)		| \
+		 (1ULL << VIRTIO_NET_F_GUEST_ANNOUNCE)		| \
+		 (1ULL << VIRTIO_F_IOMMU_PLATFORM)		| \
+		 (1ULL << VIRTIO_NET_F_MRG_RXBUF)		| \
+
+/* Not support MQ, only one queue pair for now. */
+#define IFCVF_MAX_QUEUE_PAIRS		1
+#define IFCVF_MAX_QUEUES		2
+
+#define IFCVF_QUEUE_ALIGNMENT		PAGE_SIZE
+#define IFCVF_QUEUE_MAX		32 * 1024
+#define IFCVF_MSI_CONFIG_OFF	0
+#define IFCVF_MSI_QUEUE_OFF	1
+#define IFCVF_PCI_MAX_RESOURCE	6
+
+#define IFCVF_LM_CFG_SIZE		0x40
+#define IFCVF_LM_RING_STATE_OFFSET	0x20
+#define IFCVF_LM_BAR	4
+
+#define IFCVF_32_BIT_MASK		0xffffffff
+
+#define IFC_ERR(dev, fmt, ...)	dev_err(dev, fmt, ##__VA_ARGS__)
+#define IFC_DBG(dev, fmt, ...)	dev_dbg(dev, fmt, ##__VA_ARGS__)
+#define IFC_INFO(dev, fmt, ...)	dev_info(dev, fmt, ##__VA_ARGS__)
+
+#define IFC_PRIVATE_TO_VF(adapter) \
+	(&((struct ifcvf_adapter *)adapter)->vf)
+
+#define IFCVF_MAX_INTR (IFCVF_MAX_QUEUE_PAIRS * 2 + 1)
+
+struct ifcvf_pci_mem_resource {
+	/* Physical address, 0 if not resource. */
+	u64      phys_addr;
+	/* Length of the resource. */
+	u64      len;
+	/* Virtual address, NULL when not mapped. */
+	u8       *addr;
+};
+
+struct vring_info {
+	u64 desc;
+	u64 avail;
+	u64 used;
+	u16 size;
+	u16 last_avail_idx;
+	u16 last_used_idx;
+	bool ready;
+	char msix_name[256];
+	u16 __iomem *notify_addr[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct virtio_mdev_callback cb;
+};
+
+struct ifcvf_hw {
+	u8	*isr;
+	/* Bar to nofity the VF (queue) */
+	u8	notify_bar;
+	/* live migration */
+	u8	__iomem	*lm_cfg;
+	u8	nr_vring;
+	/* Notificaiton bar address*/
+	u16	*notify_base;
+	u32	notify_off_multiplier;
+	u64	req_features;
+	struct	virtio_pci_common_cfg __iomem	*common_cfg;
+	struct	virtio_net_config __iomem	*net_cfg;
+	struct	vring_info vring[IFCVF_MAX_QUEUE_PAIRS * 2];
+	struct	ifcvf_pci_mem_resource mem_resource[IFCVF_PCI_MAX_RESOURCE];
+};
+
+struct ifcvf_adapter {
+	struct	device *dev;
+	struct	mutex mdev_lock;
+	int	mdev_count;
+	int	vectors;
+	struct	ifcvf_hw vf;
+};
+
+struct ifcvf_vring_lm_cfg {
+	u32 idx_addr[2];
+	u8 reserved[IFCVF_LM_CFG_SIZE - 8];
+};
+
+struct ifcvf_lm_cfg {
+	u8 reserved[IFCVF_LM_RING_STATE_OFFSET];
+	struct ifcvf_vring_lm_cfg vring_lm_cfg[IFCVF_MAX_QUEUE_PAIRS];
+};
+
+int ifcvf_init_hw(struct ifcvf_hw *hw, struct pci_dev *dev);
+int ifcvf_start_hw(struct ifcvf_hw *hw);
+void ifcvf_stop_hw(struct ifcvf_hw *hw);
+void ifcvf_notify_queue(struct ifcvf_hw *hw, u16 qid);
+void ifcvf_read_net_config(struct ifcvf_hw *hw, u64 offset,
+			   void *dst, int length);
+void ifcvf_write_net_config(struct ifcvf_hw *hw, u64 offset,
+			    const void *src, int length);
+u8 ifcvf_get_status(struct ifcvf_hw *hw);
+void ifcvf_set_status(struct ifcvf_hw *hw, u8 status);
+void io_write64_twopart(u64 val, u32 *lo, u32 *hi);
+void ifcvf_reset(struct ifcvf_hw *hw);
+u64 ifcvf_get_features(struct ifcvf_hw *hw);
+
+#endif /* _IFCVF_H_ */

From patchwork Wed Nov 20 09:17:11 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11253393
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38979109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 09:19:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E9C1223D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 09:19:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728190AbfKTJTi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 04:19:38 -0500
Received: from mga06.intel.com ([134.134.136.31]:61597 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728176AbfKTJTf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 04:19:35 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Nov 2019 01:19:35 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.69,221,1571727600";
   d="scan'208";a="237660962"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga002.fm.intel.com with ESMTP; 20 Nov 2019 01:19:32 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        zhiyuan.lv@intel.com, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [RFC V4 2/2] This commit introduced IFC operations for vdpa
Date: Wed, 20 Nov 2019 17:17:11 +0800
Message-Id: <1574241431-24792-3-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1574241431-24792-1-git-send-email-lingshan.zhu@intel.com>
References: <1574241431-24792-1-git-send-email-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit intends to implement ops which complying to
virtio_mdev and vhost_mdev interfaces, handles IFC VF initialization,
configuration and removal.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/ifcvf/ifcvf_main.c | 582 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 582 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c

diff --git a/drivers/vhost/ifcvf/ifcvf_main.c b/drivers/vhost/ifcvf/ifcvf_main.c
new file mode 100644
index 0000000..cdc804f
--- /dev/null
+++ b/drivers/vhost/ifcvf/ifcvf_main.c
@@ -0,0 +1,582 @@
+// SPDX-License-Identifier: GPL-2.0-only
+/*
+ * Copyright (C) 2019 Intel Corporation.
+ */
+
+#include <linux/interrupt.h>
+#include <linux/module.h>
+#include <linux/mdev.h>
+#include <linux/pci.h>
+#include <linux/sysfs.h>
+#include "ifcvf_base.h"
+
+#define VERSION_STRING	"0.1"
+#define DRIVER_AUTHOR	"Intel Corporation"
+#define IFCVF_DRIVER_NAME	"ifcvf"
+
+static struct ifcvf_hw *mdev_to_vf(struct mdev_device *mdev)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+
+	return vf;
+}
+
+static irqreturn_t ifcvf_intr_handler(int irq, void *arg)
+{
+	struct vring_info *vring = arg;
+
+	if (vring->cb.callback)
+		return vring->cb.callback(vring->cb.private);
+
+	return IRQ_HANDLED;
+}
+
+static u64 ifcvf_mdev_get_features(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_features(vf);
+}
+
+static int ifcvf_mdev_set_features(struct mdev_device *mdev, u64 features)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->req_features = features;
+
+	return 0;
+}
+
+static u64 ifcvf_mdev_get_vq_state(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+	u16 last_avail_idx;
+	u16 __iomem *idx_addr;
+
+	idx_addr = (u16 __iomem*)(vf->lm_cfg + IFCVF_LM_RING_STATE_OFFSET +
+			(qid / 2) * IFCVF_LM_CFG_SIZE + (qid % 2) * 4);
+
+	last_avail_idx = ioread16(idx_addr);
+
+	return last_avail_idx;
+}
+
+static int ifcvf_mdev_set_vq_state(struct mdev_device *mdev, u16 qid, u64 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].last_avail_idx = num;
+
+	return 0;
+}
+
+static int ifcvf_mdev_set_vq_address(struct mdev_device *mdev, u16 idx,
+				     u64 desc_area, u64 driver_area,
+				     u64 device_area)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].desc = desc_area;
+	vf->vring[idx].avail = driver_area;
+	vf->vring[idx].used = device_area;
+
+	return 0;
+}
+
+static void ifcvf_mdev_set_vq_num(struct mdev_device *mdev, u16 qid, u32 num)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].size = num;
+}
+
+static void ifcvf_mdev_set_vq_ready(struct mdev_device *mdev,
+				    u16 qid, bool ready)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[qid].ready = ready;
+}
+
+static bool ifcvf_mdev_get_vq_ready(struct mdev_device *mdev, u16 qid)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return vf->vring[qid].ready;
+}
+
+static void ifcvf_mdev_set_vq_cb(struct mdev_device *mdev, u16 idx,
+				 struct virtio_mdev_callback *cb)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	vf->vring[idx].cb = *cb;
+}
+
+static void ifcvf_mdev_kick_vq(struct mdev_device *mdev, u16 idx)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	ifcvf_notify_queue(vf, idx);
+}
+
+static u8 ifcvf_mdev_get_status(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ifcvf_get_status(vf);
+}
+
+static u32 ifcvf_mdev_get_generation(struct mdev_device *mdev)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	return ioread8(&vf->common_cfg->config_generation);
+}
+
+static u32 ifcvf_mdev_get_device_id(struct mdev_device *mdev)
+{
+	return VIRTIO_ID_NET;
+}
+
+static u32 ifcvf_mdev_get_vendor_id(struct mdev_device *mdev)
+{
+	return IFCVF_VENDOR_ID;
+}
+
+static u16 ifcvf_mdev_get_vq_align(struct mdev_device *mdev)
+{
+	return IFCVF_QUEUE_ALIGNMENT;
+}
+
+static int ifcvf_start_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	struct ifcvf_adapter *ifcvf;
+	int ret = 0;
+	u8 status;
+
+	ifcvf = container_of(vf, struct ifcvf_adapter, vf);
+	vf->nr_vring = IFCVF_MAX_QUEUE_PAIRS * 2;
+	ret = ifcvf_start_hw(vf);
+
+	if (ret) {
+		status = ifcvf_get_status(vf);
+		status |= VIRTIO_CONFIG_S_FAILED;
+		ifcvf_set_status(vf, status);
+	}
+
+	return ret;
+}
+
+static int ifcvf_stop_datapath(void *private)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(private);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUES; i++)
+		vf->vring[i].cb.callback = NULL;
+
+	ifcvf_stop_hw(vf);
+
+	return 0;
+}
+
+static void ifcvf_reset_vring(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	int i;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vf->vring[i].last_used_idx = 0;
+		vf->vring[i].last_avail_idx = 0;
+		vf->vring[i].desc = 0;
+		vf->vring[i].avail = 0;
+		vf->vring[i].used = 0;
+		vf->vring[i].ready = 0;
+		vf->vring->cb.callback = NULL;
+		vf->vring->cb.private = NULL;
+
+	}
+
+	ifcvf_reset(vf);
+}
+
+static void ifcvf_mdev_set_status(struct mdev_device *mdev, u8 status)
+{
+	struct ifcvf_adapter *adapter = mdev_get_drvdata(mdev);
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	int ret = 0;
+
+	if (status == 0) {
+		ifcvf_stop_datapath(adapter);
+		ifcvf_reset_vring(adapter);
+		return;
+	}
+
+	if (status & VIRTIO_CONFIG_S_DRIVER_OK) {
+		ret = ifcvf_start_datapath(adapter);
+
+		if (ret)
+			IFC_ERR(adapter->dev, "Failed to set mdev status %u\n",
+				status);
+	}
+
+	ifcvf_set_status(vf, status);
+}
+
+static u16 ifcvf_mdev_get_vq_num_max(struct mdev_device *mdev)
+{
+
+	return (u16)IFCVF_QUEUE_MAX;
+}
+static void ifcvf_mdev_get_config(struct mdev_device *mdev, unsigned int offset,
+			     void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct virtio_net_config));
+	ifcvf_read_net_config(vf, offset, buf, len);
+}
+
+static void ifcvf_mdev_set_config(struct mdev_device *mdev, unsigned int offset,
+			     const void *buf, unsigned int len)
+{
+	struct ifcvf_hw *vf = mdev_to_vf(mdev);
+
+	WARN_ON(offset + len > sizeof(struct virtio_net_config));
+	ifcvf_write_net_config(vf, offset, buf, len);
+}
+
+static struct mdev_virtio_ops ifc_mdev_ops = {
+	.get_features  = ifcvf_mdev_get_features,
+	.set_features  = ifcvf_mdev_set_features,
+	.get_status    = ifcvf_mdev_get_status,
+	.set_status    = ifcvf_mdev_set_status,
+	.get_vq_num_max = ifcvf_mdev_get_vq_num_max,
+	.get_vq_state   = ifcvf_mdev_get_vq_state,
+	.set_vq_state   = ifcvf_mdev_set_vq_state,
+	.set_vq_cb      = ifcvf_mdev_set_vq_cb,
+	.set_vq_ready   = ifcvf_mdev_set_vq_ready,
+	.get_vq_ready	= ifcvf_mdev_get_vq_ready,
+	.set_vq_num     = ifcvf_mdev_set_vq_num,
+	.set_vq_address = ifcvf_mdev_set_vq_address,
+	.kick_vq        = ifcvf_mdev_kick_vq,
+	.get_generation	= ifcvf_mdev_get_generation,
+	.get_device_id	= ifcvf_mdev_get_device_id,
+	.get_vendor_id	= ifcvf_mdev_get_vendor_id,
+	.get_vq_align	= ifcvf_mdev_get_vq_align,
+	.get_config	= ifcvf_mdev_get_config,
+	.set_config	= ifcvf_mdev_set_config,
+};
+
+static int ifcvf_init_msix(struct ifcvf_adapter *adapter)
+{
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	struct ifcvf_hw *vf = &adapter->vf;
+	int vector, i, ret, irq;
+
+	ret = pci_alloc_irq_vectors(pdev, IFCVF_MAX_INTR,
+				    IFCVF_MAX_INTR, PCI_IRQ_MSIX);
+	if (ret < 0) {
+		IFC_ERR(adapter->dev, "Failed to alloc irq vectors\n");
+		return ret;
+	}
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		ret = request_irq(irq, ifcvf_intr_handler, 0,
+				pci_name(pdev), &vf->vring[i]);
+		if (ret) {
+			IFC_ERR(adapter->dev,
+				"Failed to request irq for vq %d\n", i);
+			return ret;
+		}
+	}
+
+	return 0;
+}
+
+static void ifcvf_destroy_adapter(struct ifcvf_adapter *adapter)
+{
+	struct ifcvf_hw *vf = IFC_PRIVATE_TO_VF(adapter);
+	struct pci_dev *pdev = to_pci_dev(adapter->dev);
+	int i, vector, irq;
+
+	for (i = 0; i < IFCVF_MAX_QUEUE_PAIRS * 2; i++) {
+		vector = i + IFCVF_MSI_QUEUE_OFF;
+		irq = pci_irq_vector(pdev, vector);
+		free_irq(irq, &vf->vring[i]);
+	}
+}
+
+static ssize_t name_show(struct kobject *kobj, struct device *dev, char *buf)
+{
+	const char *name = "IFC VF virtio/vhost accelerator (virtio ring compatible)";
+
+	return sprintf(buf, "%s\n", name);
+}
+MDEV_TYPE_ATTR_RO(name);
+
+static ssize_t device_api_show(struct kobject *kobj, struct device *dev,
+			       char *buf)
+{
+	//return sprintf(buf, "%s\n", VIRTIO_MDEV_DEVICE_API_STRING);
+	return sprintf(buf, "%s\n", "virtio_mdev");
+}
+MDEV_TYPE_ATTR_RO(device_api);
+
+static ssize_t available_instances_show(struct kobject *kobj,
+					struct device *dev, char *buf)
+{
+	struct pci_dev *pdev;
+	struct ifcvf_adapter *adapter;
+
+	pdev = to_pci_dev(dev);
+	adapter = pci_get_drvdata(pdev);
+
+	return sprintf(buf, "%d\n", adapter->mdev_count);
+}
+
+MDEV_TYPE_ATTR_RO(available_instances);
+
+static ssize_t type_show(struct kobject *kobj,
+			struct device *dev, char *buf)
+{
+	return sprintf(buf, "%s\n", "net");
+}
+
+MDEV_TYPE_ATTR_RO(type);
+
+
+static struct attribute *mdev_types_attrs[] = {
+	&mdev_type_attr_name.attr,
+	&mdev_type_attr_device_api.attr,
+	&mdev_type_attr_available_instances.attr,
+	&mdev_type_attr_type.attr,
+	NULL,
+};
+
+static struct attribute_group mdev_type_group_virtio = {
+	.name  = "virtio_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group mdev_type_group_vhost = {
+	.name  = "vhost_mdev",
+	.attrs = mdev_types_attrs,
+};
+
+static struct attribute_group *mdev_type_groups[] = {
+	&mdev_type_group_virtio,
+	&mdev_type_group_vhost,
+	NULL,
+};
+
+const struct attribute_group *mdev_dev_groups[] = {
+	NULL,
+};
+
+static int ifcvf_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	int ret = 0;
+
+	mutex_lock(&adapter->mdev_lock);
+
+	if (adapter->mdev_count < IFCVF_MDEV_LIMIT) {
+		IFC_ERR(&pdev->dev,
+			"Can not create mdev, reached limitation %d\n",
+			IFCVF_MDEV_LIMIT);
+		ret = -EINVAL;
+		goto out;
+	}
+
+	mdev_virtio_set_ops(mdev, &ifc_mdev_ops);
+
+	if (!strcmp(kobj->name, "ifcvf-virtio_mdev"))
+		mdev_virtio_set_class_id(mdev,MDEV_VIRTIO_CLASS_ID_VIRTIO);
+
+	if (!strcmp(kobj->name, "ifcvf-vhost_mdev"))
+		mdev_virtio_set_class_id(mdev,MDEV_VIRTIO_CLASS_ID_VHOST);
+
+	mdev_set_drvdata(mdev, adapter);
+	mdev_set_iommu_device(mdev_dev(mdev), dev);
+	adapter->mdev_count--;
+
+out:
+	mutex_unlock(&adapter->mdev_lock);
+	return ret;
+}
+
+static int ifcvf_mdev_remove(struct mdev_device *mdev)
+{
+	struct device *dev = mdev_parent_dev(mdev);
+	struct pci_dev *pdev = to_pci_dev(dev);
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+
+	mutex_lock(&adapter->mdev_lock);
+	adapter->mdev_count++;
+	mutex_unlock(&adapter->mdev_lock);
+
+	return 0;
+}
+
+static struct mdev_parent_ops ifcvf_mdev_fops = {
+	.owner			= THIS_MODULE,
+	.supported_type_groups	= mdev_type_groups,
+	.mdev_attr_groups	= mdev_dev_groups,
+	.create			= ifcvf_mdev_create,
+	.remove			= ifcvf_mdev_remove,
+};
+
+static int ifcvf_probe(struct pci_dev *pdev, const struct pci_device_id *id)
+{
+	struct device *dev = &pdev->dev;
+	struct ifcvf_adapter *adapter;
+	struct ifcvf_hw *vf;
+	int ret, i;
+
+	adapter = kzalloc(sizeof(struct ifcvf_adapter), GFP_KERNEL);
+
+	if (adapter == NULL) {
+		ret = -ENOMEM;
+		goto fail;
+	}
+
+	mutex_init(&adapter->mdev_lock);
+	adapter->mdev_count = IFCVF_MDEV_LIMIT;
+	adapter->dev = dev;
+	pci_set_drvdata(pdev, adapter);
+	ret = pci_enable_device(pdev);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to enable device\n");
+		goto free_adapter;
+	}
+
+	ret = pci_request_regions(pdev, IFCVF_DRIVER_NAME);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to request MMIO region\n");
+		goto disable_device;
+	}
+
+	pci_set_master(pdev);
+	ret = ifcvf_init_msix(adapter);
+
+	if (ret) {
+		IFC_ERR(adapter->dev, "Failed to initialize MSI-X\n");
+		goto free_msix;
+	}
+
+	vf = &adapter->vf;
+	
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		vf->mem_resource[i].phys_addr = pci_resource_start(pdev, i);
+		vf->mem_resource[i].len = pci_resource_len(pdev, i);
+		if (!vf->mem_resource[i].len) {
+			vf->mem_resource[i].addr = NULL;
+			continue;
+		}
+
+		vf->mem_resource[i].addr = pci_iomap_range(pdev, i, 0,
+				vf->mem_resource[i].len);
+		if (!vf->mem_resource[i].addr) {
+			IFC_ERR(adapter->dev, "Failed to map IO resource %d\n",
+				i);
+			ret = -1;
+			goto free_msix;
+		}
+	}
+
+	if (ifcvf_init_hw(vf, pdev) < 0) {
+		ret = -1;
+		goto destroy_adapter;
+	}
+
+	ret = mdev_virtio_register_device(dev, &ifcvf_mdev_fops);
+
+	if (ret) {
+		IFC_ERR(adapter->dev,  "Failed to register mdev device\n");
+		goto destroy_adapter;
+	}
+
+	return 0;
+
+destroy_adapter:
+	ifcvf_destroy_adapter(adapter);
+free_msix:
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+disable_device:
+	pci_disable_device(pdev);
+free_adapter:
+	kfree(adapter);
+fail:
+	return ret;
+}
+
+static void ifcvf_remove(struct pci_dev *pdev)
+{
+	struct ifcvf_adapter *adapter = pci_get_drvdata(pdev);
+	struct device *dev = &pdev->dev;
+	struct ifcvf_hw *vf;
+	int i;
+
+	mdev_virtio_unregister_device(dev);
+
+	vf = &adapter->vf;
+	for (i = 0; i < IFCVF_PCI_MAX_RESOURCE; i++) {
+		if (vf->mem_resource[i].addr) {
+			pci_iounmap(pdev, vf->mem_resource[i].addr);
+			vf->mem_resource[i].addr = NULL;
+		}
+	}
+
+	ifcvf_destroy_adapter(adapter);
+	pci_free_irq_vectors(pdev);
+	pci_release_regions(pdev);
+	pci_disable_device(pdev);
+	kfree(adapter);
+}
+
+static struct pci_device_id ifcvf_pci_ids[] = {
+	{ PCI_DEVICE_SUB(IFCVF_VENDOR_ID,
+			IFCVF_DEVICE_ID,
+			IFCVF_SUBSYS_VENDOR_ID,
+			IFCVF_SUBSYS_DEVICE_ID) },
+	{ 0 },
+};
+MODULE_DEVICE_TABLE(pci, ifcvf_pci_ids);
+
+static struct pci_driver ifcvf_driver = {
+	.name     = IFCVF_DRIVER_NAME,
+	.id_table = ifcvf_pci_ids,
+	.probe    = ifcvf_probe,
+	.remove   = ifcvf_remove,
+};
+
+static int __init ifcvf_init_module(void)
+{
+	int ret;
+
+	ret = pci_register_driver(&ifcvf_driver);
+	return ret;
+}
+
+static void __exit ifcvf_exit_module(void)
+{
+	pci_unregister_driver(&ifcvf_driver);
+}
+
+module_init(ifcvf_init_module);
+module_exit(ifcvf_exit_module);
+
+MODULE_LICENSE("GPL v2");
+MODULE_VERSION(VERSION_STRING);
+MODULE_AUTHOR(DRIVER_AUTHOR);
```
#### [PATCH] KVM: nVMX: Assume TLB entries of L1 and L2 are tagged differently if L0 use EPT
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11253753
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5D8E1593
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 12:28:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC64C2251D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 12:28:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="fQ0H+N8q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729473AbfKTM2N (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 07:28:13 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:34900 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728611AbfKTM2N (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 07:28:13 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKC93bm048834;
        Wed, 20 Nov 2019 12:28:06 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=HcfXjW7i3DttquHo0+qv6rMXzKPvIwZKw2tsvZKypvw=;
 b=fQ0H+N8qOxUE+WEuHFgNolPD+G5hXK1pKjxW7Da8+3rczxU6fEo60DiNkN3RWzhUDkvX
 Qle8VZP/kur7C/zNuGMRrqmX1qVNK9PdDwXd88AlMNmnl1cJVpAg3SilEATddkmCsiut
 hRVAZdnJjurzxUqgbprbazUcXgFZknCRVGEBaltTVcM8Zbh/IagyGfHVUOQo0sv1N3H9
 ijjcWfRqVXRIUdfgMHWPjs1WB8kZOKaY59z7xv+HB7a1lv3UT/ReFP6kFMmueEq3WOjl
 B27hrw4fan08QSQthoneQz4tS0ok5uDOKFYbOP3jVX68jEpzRAiefCSgfAdoXioREKu+ +w==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2wa92pw7f6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 12:28:06 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKCCuwx026291;
        Wed, 20 Nov 2019 12:26:06 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 2wd47v37wf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 12:26:06 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xAKCQ5d8005586;
        Wed, 20 Nov 2019 12:26:05 GMT
Received: from localhost.localdomain (/10.74.127.98)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 20 Nov 2019 04:26:05 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH] KVM: nVMX: Assume TLB entries of L1 and L2 are tagged
 differently if L0 use EPT
Date: Wed, 20 Nov 2019 14:24:52 +0200
Message-Id: <20191120122452.57462-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9446
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=655
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-1911200112
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9446
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=733 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-1911200112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since commit 1313cc2bd8f6 ("kvm: mmu: Add guest_mode to kvm_mmu_page_role"),
guest_mode was added to mmu-role and therefore if L0 use EPT, it will
always run L1 and L2 with different EPTP. i.e. EPTP01!=EPTP02.

Because TLB entries are tagged with EP4TA, KVM can assume
TLB entries populated while running L2 are tagged differently
than TLB entries populated while running L1.

Therefore, update nested_has_guest_tlb_tag() to consider if
L0 use EPT instead of if L1 use EPT.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: Do not mark vmcs02->apic_access_page as dirty when unpinning
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11254995
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61F9E14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 22:32:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3698820898
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 22:32:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ZXWpFhrb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726014AbfKTWcI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 17:32:08 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:45172 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725820AbfKTWcH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 17:32:07 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKMIxbi194931;
        Wed, 20 Nov 2019 22:32:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=jPiCHswE/8lrEBCyDTuCovZmy8rsk6cyZIiTyARLZAY=;
 b=ZXWpFhrbyDHS55dfYXxqlfGI9rZwlJYoyYBwWXL7f6tCAnsE/pjjJCarw2BrZVsMCRMF
 0Lvd2/YD3OuveucUkR1prrCKMmIXQSxk34AP4TVsu0v5GHMaR3bqWqJJlwgXE1tB1LOi
 AqtGtECfvyeb1VGL+3/eKwTE+b/QmmG017g4LWOydQwm9idRRquyh9Lta3sbvgNau7PN
 MSXLwXbbGgReGCKsM9ds23OmW1/ykfFQnwnxcNwap/RTEAL7fcyy3RnOobNVsD1fuNah
 stBjbfU8QkdHemVKTQt9PqfpRadIuSRBCtL2BYiTM++VnxCs74mJejn5HTCerXfO6/V3 qQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2130.oracle.com with ESMTP id 2wa8hu0k20-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 22:32:01 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKMJ8Ug006090;
        Wed, 20 Nov 2019 22:32:00 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3020.oracle.com with ESMTP id 2wcemja4ax-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 22:32:00 +0000
Received: from abhmp0004.oracle.com (abhmp0004.oracle.com [141.146.116.10])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xAKMVwhr009525;
        Wed, 20 Nov 2019 22:31:59 GMT
Received: from Lirans-MBP.Home (/79.176.218.68)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 20 Nov 2019 14:31:58 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: nVMX: Do not mark vmcs02->apic_access_page as dirty when
 unpinning
Date: Thu, 21 Nov 2019 00:31:47 +0200
Message-Id: <20191120223147.63358-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9447
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=2
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=501
 adultscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-1911200189
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9447
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=2 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=561 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-1911200189
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmcs->apic_access_page is simply a token that the hypervisor puts into
the PFN of a 4KB EPTE (or PTE if using shadow-paging) that triggers
APIC-access VMExit or APIC virtualization logic whenever a CPU running
in VMX non-root mode read/write from/to this PFN.

As every write either triggers an APIC-access VMExit or write is
performed on vmcs->virtual_apic_page, the PFN pointed to by
vmcs->apic_access_page should never actually be touched by CPU.

Therefore, there is no need to mark vmcs02->apic_access_page as dirty
after unpin it on L2->L1 emulated VMExit or when L1 exit VMX operation.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Remove unnecessary TLB flushes on L1<->L2 switches when L1 use apic-access-page
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11254007
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 290B6109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 14:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 01C1220898
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 14:34:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="lnSutISo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731469AbfKTOee (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 09:34:34 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:48730 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729591AbfKTOed (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 09:34:33 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKEEHLN140925;
        Wed, 20 Nov 2019 14:34:27 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=pwDdzj40sbmAyVkV0opfYQybjogY7MjzaKx70oXmVzQ=;
 b=lnSutISoYblEW1/J8HOT5/JhIXILrT04HHJcAzFGnws2c2Hy+x/JfnF/mTDhdHvnp8jh
 wxfTDw/Pq/E5O3HyCxfZeqjPJsohsSC/+imKkfbog1AW3eCLMrV1IRg5VtsIEEJyduZ5
 Gv32zGwUytPHLJa+ui0sNuRjqIlk85AAjyoCcrlzdru2iC2iyKkR1IZJxHyI45HGuvl4
 c4yt5dio124Qdi/FRXkICemm8KAxA648zBxKXem16pzuoMGw29jsbNAzwzHEhq7YfZl7
 s7oR5yYJPzfB8gKY7k51fOLlGiPW04IzKRWhbgpe72PibK67ZIEunqFK/aJyjdr9Tqob wA==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 2wa9rqnu7v-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 14:34:27 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAKEDxk8103780;
        Wed, 20 Nov 2019 14:34:26 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3020.oracle.com with ESMTP id 2wcemg3nph-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 20 Nov 2019 14:34:26 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xAKEYQVr030859;
        Wed, 20 Nov 2019 14:34:26 GMT
Received: from Lirans-MBP.Home (/79.176.218.68)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 20 Nov 2019 06:34:25 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] KVM: nVMX: Remove unnecessary TLB flushes on L1<->L2 switches
 when L1 use apic-access-page
Date: Wed, 20 Nov 2019 16:33:07 +0200
Message-Id: <20191120143307.59906-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9446
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-1911200128
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9446
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-1911200128
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to Intel SDM section 28.3.3.3/28.3.3.4 Guidelines for Use
of the INVVPID/INVEPT Instruction, there is a need to execute
INVVPID/INVEPT X in case CPU executes VMEntry with VPID/EPTP X and
either: "Virtualize APIC accesses" VM-execution control was changed
from 0 to 1, OR the value of apic_access_page was changed.

Examining prepare_vmcs02(), one could note that L0 won't flush
physical TLB only in case: L0 use VPID, L1 use VPID and L0
can guarantee TLB entries populated while running L1 are tagged
differently than TLB entries populated while running L2.
The last condition can only occur if either L0 use EPT or
L0 use different VPID for L1 and L2
(i.e. vmx->vpid != vmx->nested.vpid02).

If L0 use EPT, L0 use different EPTP when running L2 than L1
(Because guest_mode is part of mmu-role) and therefore SDM section
28.3.3.4 doesn't apply. Otherwise, L0 use different VPID when
running L2 than L1 and therefore SDM section 28.3.3.3 doesn't
apply.

Similarly, examining nested_vmx_vmexit()->load_vmcs12_host_state(),
one could note that L0 won't flush TLB only in cases that doesn't
apply to SDM sections 28.3.3.3 and 28.3.3.4.

Considering the above, there is therefore no need to specifically
flush TLB in case L1 don't use EPT and use "Virtualize APIC accesses".
Thus, remove this flush from prepare_vmcs02() and nested_vmx_vmexit().

Side-note: This patch can be viewed as removing parts of commit
fb6c81984313 ("kvm: vmx: Flush TLB when the APIC-access address changes”)
that is not relevant anymore since commit
1313cc2bd8f6 ("kvm: mmu: Add guest_mode to kvm_mmu_page_role”).
i.e. The first commit assumes that if L0 use EPT and L1 doesn’t use EPT,
then L0 will use same EPTP for both L0 and L1. Which indeed required
L0 to execute INVEPT before entering L2 guest. This assumption is
not true anymore since when guest_mode was added to mmu-role.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 7 -------
 1 file changed, 7 deletions(-)

```
#### [PATCH kvm-unit-tests] runtime: set MAX_SMP to number of online cpus
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11254003
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1FA51390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 14:19:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 77A412230F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 14:19:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JNxbbZgO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730665AbfKTOTd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 09:19:33 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20469 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729490AbfKTOTd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 09:19:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574259572;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pethWT0UbnfrUscN97QLS4gJaPBeIS0NMTqV57F0VQE=;
        b=JNxbbZgO3cRu40hC1IAmHkjP8WlZKquhkLKzj60Bkw9NgyAqu9UpIsEtMESsIgXpPiHrVn
        tf2g+ya5jhwOKsWHqh18qhLhAlTLs2AX3BHH5xqe56iHlDHKVWE1wU26OJXxq1soxkJjlp
        IVWjc8JhDZE23po0M+kXWzxTmcN6cLs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-340-rg5THV9WPIu6GvUykGlzXg-1; Wed, 20 Nov 2019 09:19:31 -0500
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9054D1883524
        for <kvm@vger.kernel.org>; Wed, 20 Nov 2019 14:19:30 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BDD8B5F77B;
        Wed, 20 Nov 2019 14:19:29 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] runtime: set MAX_SMP to number of online cpus
Date: Wed, 20 Nov 2019 15:19:28 +0100
Message-Id: <20191120141928.6849-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-MC-Unique: rg5THV9WPIu6GvUykGlzXg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can only use online cpus, so make sure we check specifically for
those.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Zero the IOAPIC scan request dest vCPUs bitmap
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11253737
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B20066C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 12:12:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9165B224E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 12:12:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="aSBoPSfX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729613AbfKTMMe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 20 Nov 2019 07:12:34 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55854 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729202AbfKTMMd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 20 Nov 2019 07:12:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574251952;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=KJxhVxnKLCqBwMe6QDFuzbqbvStQBH6WEDU+lUrFWvk=;
        b=aSBoPSfXa5gJ6kLgUz9nWk9ZiUdmiJS5CIQsFREk6J74TgTkBmB/Pl5mxZvSPkzy7MS0Zs
        Qo/o4595/e4ky3GTPydk+tr8QmEHATFOx6angxZxRbVnRuUUCOtirCAGMU2vZ+Ay9cq/PO
        qWZt6s/7vKCav+qdDe6jSv/cSwGuff4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-267-S82Tcyr9MOmDC_YEI1ZwyA-1; Wed, 20 Nov 2019 07:12:31 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 14F24107ACC7;
        Wed, 20 Nov 2019 12:12:29 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DB8AC3483A;
        Wed, 20 Nov 2019 12:12:24 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mtosatti@redhat.com, rkrcmar@redhat.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org
Subject: [PATCH] KVM: x86: Zero the IOAPIC scan request dest vCPUs bitmap
Date: Wed, 20 Nov 2019 07:12:24 -0500
Message-Id: <20191120121224.9850-1-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: S82Tcyr9MOmDC_YEI1ZwyA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Not zeroing the bitmap used for identifying the destination vCPUs for an
IOAPIC scan request in fixed delivery mode could lead to waking up unwanted
vCPUs. This patch zeroes the vCPU bitmap before passing it to
kvm_bitmap_or_dest_vcpus(), which is responsible for setting the bitmap
with the bits corresponding to the destination vCPUs.

Fixes: 7ee30bc132c6("KVM: x86: deliver KVM IOAPIC scan request to target vCPUs")
Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/kvm/ioapic.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3 1/2] KVM: VMX: FIXED+PHYSICAL mode single target IPI fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11252977
Return-Path: <SRS0=Ulro=ZM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A724413A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 03:42:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 616812244A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 20 Nov 2019 03:42:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="KXjTijsh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727465AbfKTDm0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 19 Nov 2019 22:42:26 -0500
Received: from mail-pf1-f196.google.com ([209.85.210.196]:34406 "EHLO
        mail-pf1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727264AbfKTDm0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 19 Nov 2019 22:42:26 -0500
Received: by mail-pf1-f196.google.com with SMTP id n13so13516376pff.1;
        Tue, 19 Nov 2019 19:42:25 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lTldptnXudJgcKsVCapkPtGQ4vvaqsnycm5q4DkmviQ=;
        b=KXjTijshyFozC++YLMZzACRo0PoeOUQ6RCBuke4CWYBT3i/nTCHWu+Repa+s4gfm8C
         3sOlFFyv494vicu1bRtoOeH+THgt3mSv0AvLhrVZRNZMwGhw0XSU4eVACcQb2YmsrVxU
         AVfHIxY6Chuux0aJaBBuawyq9v8Ttihl7RIki3PSowWwA5ErszLAZCfN65W0jgN21hxV
         BzwCaCRbPXaMFZ5yI4IwVIHdKi/NAQb5k+dEezv3ZmWsrKA/8yGe3paajc+WCwp9/j/5
         PSXz+rqlbzMTe5BTtmTWWy/7N5Qn54+rltUviS3ISX27G6d1pXGrs4aWtI7MS93URw5x
         OKwg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=lTldptnXudJgcKsVCapkPtGQ4vvaqsnycm5q4DkmviQ=;
        b=kfOKMQWY8AKQhaEyNqpCtn9JLiJnsb/O/nWf1crd1lu2gFUnizN04OqPUKGQkTygm3
         OoVBCte18XC+Fh2PGyb1XtDcWgwavcwJiwkOmFM+ccSGTST1ConU7/2brkgSLysGNfAa
         3ma6m0j4JawgN2c3DPBuwUisj+tK6S1GfVugQNmwVcqft0HGQI6gc/zVOwXsHxIX1MZF
         ABeH81eAr0kepfwztPcdjqDsPqfkl5hCZsG1ml+1Yi/uAaddf6fSI+VumjEyWmzvPWFk
         RAE3TWwKe+I9Ym4KdtDw2p395xgp33uRV7TFBsEB/qUh/7N1AUg6W0lQEsWNWtuJptEr
         4TlQ==
X-Gm-Message-State: APjAAAUZpL2Qn4ETxX/8I0JYcTA/HvMJhRrr91dECLxAdX69r9wWdSzW
        loM4r8+6oVPkOpBEXZR3SSEAGlWk
X-Google-Smtp-Source: 
 APXvYqxW7TvluACxmVHHosixk869AyV35AyNmqhTLIMgzbginP9jSFFdVlqsKAagnZtf4p1u4Hg//g==
X-Received: by 2002:a63:a5b:: with SMTP id z27mr704394pgk.416.1574221344758;
        Tue, 19 Nov 2019 19:42:24 -0800 (PST)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 w27sm25916842pgc.20.2019.11.19.19.42.21
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 19 Nov 2019 19:42:24 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v3 1/2] KVM: VMX: FIXED+PHYSICAL mode single target IPI
 fastpath
Date: Wed, 20 Nov 2019 11:42:08 +0800
Message-Id: <1574221329-12370-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

ICR and TSCDEADLINE MSRs write cause the main MSRs write vmexits in 
our product observation, multicast IPIs are not as common as unicast 
IPI like RESCHEDULE_VECTOR and CALL_FUNCTION_SINGLE_VECTOR etc.

This patch tries to optimize x2apic physical destination mode, fixed 
delivery mode single target IPI. The fast path is invoked at 
->handle_exit_irqoff() to emulate only the effect of the ICR write
itself, i.e. the sending of IPIs.  Sending IPIs early in the VM-Exit
flow reduces the latency of virtual IPIs by avoiding the expensive bits
of transitioning from guest to host, e.g. reacquiring KVM's SRCU lock.
Especially when running guest w/ KVM_CAP_X86_DISABLE_EXITS capability 
enabled or guest can keep running, IPI can be injected to target vCPU 
by posted-interrupt immediately.

Testing on Xeon Skylake server:

The virtual IPI latency from sender send to receiver receive reduces 
more than 200+ cpu cycles.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * for both VMX and SVM
 * vmx_handle_exit() get second parameter by value and not by pointer
 * rename parameter to “accel_exit_completion”
 * preserve tracepoint ordering
 * rename handler to handle_accel_set_msr_irqoff and more generic
 * add comments above handle_accel_set_msr_irqoff
 * msr index APIC_BASE_MSR + (APIC_ICR >> 4)
v1 -> v2:
 * add tracepoint
 * Instead of a separate vcpu->fast_vmexit, set exit_reason
  to vmx->exit_reason to -1 if the fast path succeeds.
 * move the "kvm_skip_emulated_instruction(vcpu)" to vmx_handle_exit
 * moving the handling into vmx_handle_exit_irqoff()

 arch/x86/include/asm/kvm_host.h | 11 ++++++++--
 arch/x86/kvm/svm.c              | 14 ++++++++----
 arch/x86/kvm/vmx/vmx.c          | 13 ++++++++---
 arch/x86/kvm/x86.c              | 48 +++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/x86.h              |  1 +
 5 files changed, 76 insertions(+), 11 deletions(-)

```
