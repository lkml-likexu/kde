

#### [PATCH v7 00/10] arm64: Stolen time support
##### From: Steven Price <steven.price@arm.com>

```c
From patchwork Mon Oct 21 15:28:13 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11202515
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7E322112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 15:28:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5CCB321A4A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 15:28:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729489AbfJUP24 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 11:28:56 -0400
Received: from [217.140.110.172] ([217.140.110.172]:55712 "EHLO foss.arm.com"
        rhost-flags-FAIL-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727926AbfJUP24 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 11:28:56 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 5A9E3CA3;
        Mon, 21 Oct 2019 08:28:33 -0700 (PDT)
Received: from e112269-lin.cambridge.arm.com (e112269-lin.cambridge.arm.com
 [10.1.194.43])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 532DD3F71F;
        Mon, 21 Oct 2019 08:28:31 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v7 00/10] arm64: Stolen time support
Date: Mon, 21 Oct 2019 16:28:13 +0100
Message-Id: <20191021152823.14882-1-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series add support for paravirtualized time for arm64 guests and
KVM hosts following the specification in Arm's document DEN 0057A:

https://developer.arm.com/docs/den0057/a

It implements support for stolen time, allowing the guest to
identify time when it is forcibly not executing.

Note that Live Physical Time (LPT) which was previously part of the
above specification has now been removed.

Also available as a git tree:
git://linux-arm.org/linux-sp.git stolen_time/v7

Changes from v6:
https://lore.kernel.org/kvm/20191011125930.40834-1-steven.price@arm.com/
 * Rebased onto Mark Rutland's SMCCC cleanup
 * Added comment about putting stolen time structures in their own 64k
   page
 * Split 'init' functionality out from kvm_update_stolen_time()
 * Enforce address provided by user space for structure is in a valid
   memslot
 * Rename functions/structures in paravirt.c to avoid 'KVM' since the
   functionality isn't specific to KVM
 * Minor cleanups from review comments

Changes from v5:
https://lore.kernel.org/kvm/20191002145037.51630-1-steven.price@arm.com/
 * Convert document to RST format
 * Rename PV_FEATURES to PV_TIME_FEATURES to match spec
 * Correct SMC number of PV_TIME_ST

Changes from v4:
https://lore.kernel.org/kvm/20190830084255.55113-1-steven.price@arm.com/
 * Rebased to v5.4-rc1
 * Renamed KVM_ARM_VCPU_PVTIME_SET_IPA to remove _SET as it is used for
   both set/get operations
 * Added kvm/arm_hypercalls.h to header-test-$(CONFIG_ARM{,64}) as it is
   only buildable on arm/arm64
 * Documented no-steal-acc kernel parameter

Changes from v3:
https://lore.kernel.org/lkml/20190821153656.33429-1-steven.price@arm.com/
 * There's no longer a PV_TIME device, instead there are attributes on
   the VCPU. This allows the stolen time structures to be places
   arbitrarily by user space (subject to 64 byte alignment).
 * Split documentation between information on the hypercalls and the
   attributes on the VCPU
 * Fixed the type of SMCCC functions to return long not int

Changes from v2:
https://lore.kernel.org/lkml/20190819140436.12207-1-steven.price@arm.com/
 * Switched from using gfn_to_hva_cache to a new macro kvm_put_guest()
   that can provide the single-copy atomicity required (on arm64). This
   macro is added in patch 4.
 * Tidied up the locking for kvm_update_stolen_time().
   pagefault_disable() was unnecessary and the caller didn't need to
   take kvm->srcu as the function does it itself.
 * Removed struct kvm_arch_pvtime from the arm implementation, replaced
   instead with inline static functions which are empty for arm.
 * Fixed a few checkpatch --strict warnings.

Changes from v1:
https://lore.kernel.org/lkml/20190802145017.42543-1-steven.price@arm.com/
 * Host kernel no longer allocates the stolen time structure, instead it
   is allocated by user space. This means the save/restore functionality
   can be removed.
 * Refactored the code so arm has stub implementations and to avoid
   initcall
 * Rebased to pick up Documentation/{virt->virtual} change
 * Bunch of typo fixes

Christoffer Dall (1):
  KVM: arm/arm64: Factor out hypercall handling from PSCI code

Steven Price (9):
  KVM: arm64: Document PV-time interface
  KVM: arm64: Implement PV_TIME_FEATURES call
  KVM: Implement kvm_put_guest()
  KVM: arm64: Support stolen time reporting via shared structure
  KVM: Allow kvm_device_ops to be const
  KVM: arm64: Provide VCPU attributes for stolen time
  arm/arm64: Provide a wrapper for SMCCC 1.1 calls
  arm/arm64: Make use of the SMCCC 1.1 wrapper
  arm64: Retrieve stolen time as paravirtualized guest

 .../admin-guide/kernel-parameters.txt         |   6 +-
 Documentation/virt/kvm/arm/pvtime.rst         |  81 ++++++++++
 Documentation/virt/kvm/devices/vcpu.txt       |  14 ++
 arch/arm/include/asm/kvm_host.h               |  25 ++++
 arch/arm/kvm/Makefile                         |   2 +-
 arch/arm/kvm/handle_exit.c                    |   2 +-
 arch/arm/mm/proc-v7-bugs.c                    |  13 +-
 arch/arm64/include/asm/kvm_host.h             |  29 ++++
 arch/arm64/include/asm/paravirt.h             |   9 +-
 arch/arm64/include/asm/pvclock-abi.h          |  17 +++
 arch/arm64/include/uapi/asm/kvm.h             |   2 +
 arch/arm64/kernel/cpu_errata.c                |  81 ++++------
 arch/arm64/kernel/paravirt.c                  | 140 ++++++++++++++++++
 arch/arm64/kernel/time.c                      |   3 +
 arch/arm64/kvm/Kconfig                        |   1 +
 arch/arm64/kvm/Makefile                       |   2 +
 arch/arm64/kvm/guest.c                        |   9 ++
 arch/arm64/kvm/handle_exit.c                  |   4 +-
 include/Kbuild                                |   2 +
 include/kvm/arm_hypercalls.h                  |  43 ++++++
 include/kvm/arm_psci.h                        |   2 +-
 include/linux/arm-smccc.h                     |  59 ++++++++
 include/linux/cpuhotplug.h                    |   1 +
 include/linux/kvm_host.h                      |  26 +++-
 include/linux/kvm_types.h                     |   2 +
 include/uapi/linux/kvm.h                      |   2 +
 virt/kvm/arm/arm.c                            |  11 ++
 virt/kvm/arm/hypercalls.c                     |  71 +++++++++
 virt/kvm/arm/psci.c                           |  84 +----------
 virt/kvm/arm/pvtime.c                         | 131 ++++++++++++++++
 virt/kvm/kvm_main.c                           |   6 +-
 31 files changed, 724 insertions(+), 156 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
