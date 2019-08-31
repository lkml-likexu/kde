

#### [PATCH v3 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Fri Aug 30 01:36:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11122797
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34D371399
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 01:36:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 16C7021897
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 01:36:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727242AbfH3Bgd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 21:36:33 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55102 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727139AbfH3Bgc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 21:36:32 -0400
Received: from mail-pg1-f200.google.com (mail-pg1-f200.google.com
 [209.85.215.200])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 9379019D335
        for <kvm@vger.kernel.org>; Fri, 30 Aug 2019 01:36:32 +0000 (UTC)
Received: by mail-pg1-f200.google.com with SMTP id o8so256296pgp.12
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 18:36:32 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ESp2wQ+ShJ19lwVMIpcld726Rm6S3EhRfyVa4rRVDKo=;
        b=Q2myyjRHFyDBRiZV/xROZHb2K9lwBH+zrbM95ekXBS4J3mz+3cOPG47sfsBbdScYSP
         0aGeK8Q8KTCZTccCuTYnAIzAI4gIoE6QqyY7icLnP7/QW4zC9i9VBp7rOPVDcwh4xorG
         Zk0To3f3zVOvLyUdJnZhfOYWGUga6MyvkJCN3k0wJ+/7HTmX6qcoACPDxXUaGgK7e90q
         GzXPOQMLeEDa6SzxbqrhcPXNNYW6yZZFxuYZ6yYIscFERlOPnZjrBL776EYmBZ6hn/5k
         Io/vLhoZYLo0PTt7pppygZgBTOBn5nlzcdyAdIdzejhcG39pbsJ9UAGVRqOmeViW4/he
         1ntQ==
X-Gm-Message-State: APjAAAXQRkxKTrGoS6w/jcNlexgj1fizcx9kGrDxBjMdBxH6y3PZRUUs
        ZWLS/fhC1KltgKe7mSHI1hpn9CC1zUhNla21O3RyVLgrSdmO3bta4PG2WQhUeCRzR+gQWMadvFR
        zmir4nhXQlWPZ
X-Received: by 2002:a17:90a:8981:: with SMTP id
 v1mr12943055pjn.136.1567128992093;
        Thu, 29 Aug 2019 18:36:32 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyO5H/X/qZw+xcqx4rZ2rlEDXWN/KoGhZsygl5nudPWBd1hzN5yPn8cEHhBKqSIafucm/zQdA==
X-Received: by 2002:a17:90a:8981:: with SMTP id
 v1mr12943030pjn.136.1567128991881;
        Thu, 29 Aug 2019 18:36:31 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 l3sm3426323pjq.24.2019.08.29.18.36.27
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 29 Aug 2019 18:36:31 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH v3 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
Date: Fri, 30 Aug 2019 09:36:15 +0800
Message-Id: <20190830013619.18867-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v3:
- pick r-b
- refine DEBUG macro [Drew]

v2:
- pick r-bs
- rebased to master
- fix pa width detect, check cpuid(1):edx.PAE(bit 6)
- fix arm compilation issue [Drew]
- fix indents issues and ways to define macros [Drew]
- provide functions for fetching cpu pa/va bits [Drew]

This series originates from "[PATCH] KVM: selftests: Detect max PA
width from cpuid" [1] and one of Drew's comments - instead of keeping
the hackish line to overwrite guest_pa_bits all the time, this series
introduced the new mode VM_MODE_PXXV48_4K for x86_64 platform.

The major issue is that even all the x86_64 kvm selftests are
currently using the guest mode VM_MODE_P52V48_4K, many x86_64 hosts
are not using 52 bits PA (and in most cases, far less).  If with luck
we could be having 48 bits hosts, but it's more adhoc (I've observed 3
x86_64 systems, they are having different PA width of 36, 39, 48).  I
am not sure whether this is happening to the other archs as well, but
it probably makes sense to bring the x86_64 tests to the real world on
always using the correct PA bits.

A side effect of this series is that it will also fix the crash we've
encountered on Xeon E3-1220 as mentioned [1] due to the
differenciation of PA width.

With [1], we've observed AMD host issues when with NPT=off.  However a
funny fact is that after I reworked into this series, the tests can
instead pass on both NPT=on/off.  It could be that the series changes
vm->pa_bits or other fields so something was affected.  I didn't dig
more on that though, considering we should not lose anything.

[1] https://lkml.org/lkml/2019/8/26/141

Peter Xu (4):
  KVM: selftests: Move vm type into _vm_create() internally
  KVM: selftests: Create VM earlier for dirty log test
  KVM: selftests: Introduce VM_MODE_PXXV48_4K
  KVM: selftests: Remove duplicate guest mode handling

 tools/testing/selftests/kvm/dirty_log_test.c  | 79 +++++--------------
 .../testing/selftests/kvm/include/kvm_util.h  | 18 ++++-
 .../selftests/kvm/include/x86_64/processor.h  |  3 +
 .../selftests/kvm/lib/aarch64/processor.c     |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 67 ++++++++++++----
 .../selftests/kvm/lib/x86_64/processor.c      | 30 ++++++-
 6 files changed, 121 insertions(+), 79 deletions(-)
```
#### [PATCH v4 00/10] arm64: Stolen time support
##### From: Steven Price <steven.price@arm.com>

```c
From patchwork Fri Aug 30 08:42:45 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11123483
Return-Path: <SRS0=4maQ=W2=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E8EE14F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 08:44:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 84E3D238CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Aug 2019 08:44:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727242AbfH3InF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 30 Aug 2019 04:43:05 -0400
Received: from foss.arm.com ([217.140.110.172]:56140 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726200AbfH3InF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Aug 2019 04:43:05 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 76097344;
        Fri, 30 Aug 2019 01:43:04 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 54A853F718;
        Fri, 30 Aug 2019 01:43:02 -0700 (PDT)
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
Subject: [PATCH v4 00/10] arm64: Stolen time support
Date: Fri, 30 Aug 2019 09:42:45 +0100
Message-Id: <20190830084255.55113-1-steven.price@arm.com>
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

It doesn't implement support for Live Physical Time (LPT) as there are
some concerns about the overheads and approach in the above
specification, and I expect an updated version of the specification to
be released soon with just the stolen time parts.

NOTE: Patches 8 and 9 will conflict with Mark Rutland's series[1] cleaning
up the SMCCC conduit. I do feel that the addition of an _invoke() call
makes a number of call sites cleaner and it should be possible to
integrate both this and Mark's other cleanups.

[1] https://lore.kernel.org/linux-arm-kernel/20190809132245.43505-1-mark.rutland@arm.com/

Also available as a git tree:
git://linux-arm.org/linux-sp.git stolen_time/v4

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
  KVM: arm64: Implement PV_FEATURES call
  KVM: Implement kvm_put_guest()
  KVM: arm64: Support stolen time reporting via shared structure
  KVM: Allow kvm_device_ops to be const
  KVM: arm64: Provide VCPU attributes for stolen time
  arm/arm64: Provide a wrapper for SMCCC 1.1 calls
  arm/arm64: Make use of the SMCCC 1.1 wrapper
  arm64: Retrieve stolen time as paravirtualized guest

 Documentation/virt/kvm/arm/pvtime.txt   |  64 ++++++++++
 Documentation/virt/kvm/devices/vcpu.txt |  14 +++
 arch/arm/include/asm/kvm_host.h         |  26 +++++
 arch/arm/kvm/Makefile                   |   2 +-
 arch/arm/kvm/handle_exit.c              |   2 +-
 arch/arm/mm/proc-v7-bugs.c              |  13 +--
 arch/arm64/include/asm/kvm_host.h       |  30 ++++-
 arch/arm64/include/asm/paravirt.h       |   9 +-
 arch/arm64/include/asm/pvclock-abi.h    |  17 +++
 arch/arm64/include/uapi/asm/kvm.h       |   2 +
 arch/arm64/kernel/cpu_errata.c          |  80 +++++--------
 arch/arm64/kernel/paravirt.c            | 148 ++++++++++++++++++++++++
 arch/arm64/kernel/time.c                |   3 +
 arch/arm64/kvm/Kconfig                  |   1 +
 arch/arm64/kvm/Makefile                 |   2 +
 arch/arm64/kvm/guest.c                  |   9 ++
 arch/arm64/kvm/handle_exit.c            |   4 +-
 include/kvm/arm_hypercalls.h            |  43 +++++++
 include/kvm/arm_psci.h                  |   2 +-
 include/linux/arm-smccc.h               |  58 ++++++++++
 include/linux/cpuhotplug.h              |   1 +
 include/linux/kvm_host.h                |  26 ++++-
 include/linux/kvm_types.h               |   2 +
 include/uapi/linux/kvm.h                |   2 +
 virt/kvm/arm/arm.c                      |  11 ++
 virt/kvm/arm/hypercalls.c               |  68 +++++++++++
 virt/kvm/arm/psci.c                     |  84 +-------------
 virt/kvm/arm/pvtime.c                   | 124 ++++++++++++++++++++
 virt/kvm/kvm_main.c                     |   6 +-
 29 files changed, 699 insertions(+), 154 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
