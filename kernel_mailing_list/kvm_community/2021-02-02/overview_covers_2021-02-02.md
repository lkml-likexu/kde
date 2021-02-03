

#### [PATCH v8 00/13] Generalize memory encryption models
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Tue Feb  2 04:13:02 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 12060571
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 227F1C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 04:14:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E808964DE1
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 04:14:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231609AbhBBEOR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Feb 2021 23:14:17 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:42555 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231520AbhBBEOB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Feb 2021 23:14:01 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4DVBHx5DVZz9tkS; Tue,  2 Feb 2021 15:13:17 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1612239197;
        bh=C/CvveZV8v771qNCTCPNypMV4EecUIQrKmjTMt5Ss1Q=;
        h=From:To:Cc:Subject:Date:From;
        b=iMNCFAV8ljlf/pbAHHb047ThAznHrYrhFTvKrtL5L0KsjKYYNbcCk21iEfOGgPNOZ
         VDYZksrxZdQKqsuOQJH86C7IUVYT3Fq28N4VFxW4/qb+DbxTSliABghh8EQrv+F8hR
         yCfcd7gBhXMw5L/x5qCRpiw9pj7s/ojJ3X4nzTZA=
From: David Gibson <david@gibson.dropbear.id.au>
To: dgilbert@redhat.com, pair@us.ibm.com, qemu-devel@nongnu.org,
        brijesh.singh@amd.com, pasic@linux.ibm.com
Cc: pragyansri.pathi@intel.com, Greg Kurz <groug@kaod.org>,
        richard.henderson@linaro.org, berrange@redhat.com,
        David Hildenbrand <david@redhat.com>,
        mdroth@linux.vnet.ibm.com, kvm@vger.kernel.org,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        pbonzini@redhat.com, mtosatti@redhat.com, borntraeger@de.ibm.com,
        Cornelia Huck <cohuck@redhat.com>, qemu-ppc@nongnu.org,
        David Gibson <david@gibson.dropbear.id.au>,
        qemu-s390x@nongnu.org, thuth@redhat.com, mst@redhat.com,
        frankja@linux.ibm.com, jun.nakajima@intel.com,
        andi.kleen@intel.com, Eduardo Habkost <ehabkost@redhat.com>
Subject: [PATCH v8 00/13] Generalize memory encryption models
Date: Tue,  2 Feb 2021 15:13:02 +1100
Message-Id: <20210202041315.196530-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A number of hardware platforms are implementing mechanisms whereby the
hypervisor does not have unfettered access to guest memory, in order
to mitigate the security impact of a compromised hypervisor.

AMD's SEV implements this with in-cpu memory encryption, and Intel has
its own memory encryption mechanism.  POWER has an upcoming mechanism
to accomplish this in a different way, using a new memory protection
level plus a small trusted ultravisor.  s390 also has a protected
execution environment.

The current code (committed or draft) for these features has each
platform's version configured entirely differently.  That doesn't seem
ideal for users, or particularly for management layers.

AMD SEV introduces a notionally generic machine option
"machine-encryption", but it doesn't actually cover any cases other
than SEV.

This series is a proposal to at least partially unify configuration
for these mechanisms, by renaming and generalizing AMD's
"memory-encryption" property.  It is replaced by a
"confidential-guest-support" property pointing to a platform specific
object which configures and manages the specific details.

Note to Ram Pai: the documentation I've included for PEF is very
minimal.  If you could send a patch expanding on that, it would be
very helpful.

Changes since v7:
 * Tweaked and clarified meaning of the 'ready' flag
 * Polished the interface to the PEF internals
 * Shifted initialization for s390 PV later (I hope I've finally got
   this after apply_cpu_model() where it needs to be)
Changes since v6:
 * Moved to using OBJECT_DECLARE_TYPE and OBJECT_DEFINE_TYPE macros
 * Assorted minor fixes
Changes since v5:
 * Renamed from "securable guest memory" to "confidential guest
   support"
 * Simpler reworking of x86 boot time flash encryption
 * Added a bunch of documentation
 * Fixed some compile errors on POWER
Changes since v4:
 * Renamed from "host trust limitation" to "securable guest memory",
   which I think is marginally more descriptive
 * Re-organized initialization, because the previous model called at
   kvm_init didn't work for s390
 * Assorted fixes to the s390 implementation; rudimentary testing
   (gitlab CI) only
Changes since v3:
 * Rebased
 * Added first cut at handling of s390 protected virtualization
Changes since RFCv2:
 * Rebased
 * Removed preliminary SEV cleanups (they've been merged)
 * Changed name to "host trust limitation"
 * Added migration blocker to the PEF code (based on SEV's version)
Changes since RFCv1:
 * Rebased
 * Fixed some errors pointed out by Dave Gilbert

David Gibson (12):
  confidential guest support: Introduce new confidential guest support
    class
  sev: Remove false abstraction of flash encryption
  confidential guest support: Move side effect out of
    machine_set_memory_encryption()
  confidential guest support: Rework the "memory-encryption" property
  sev: Add Error ** to sev_kvm_init()
  confidential guest support: Introduce cgs "ready" flag
  confidential guest support: Move SEV initialization into arch specific
    code
  confidential guest support: Update documentation
  spapr: Add PEF based confidential guest support
  spapr: PEF: prevent migration
  confidential guest support: Alter virtio default properties for
    protected guests
  s390: Recognize confidential-guest-support option

Greg Kurz (1):
  qom: Allow optional sugar props

 accel/kvm/kvm-all.c                       |  38 ------
 accel/kvm/sev-stub.c                      |  10 +-
 accel/stubs/kvm-stub.c                    |  10 --
 backends/confidential-guest-support.c     |  33 +++++
 backends/meson.build                      |   1 +
 docs/amd-memory-encryption.txt            |   2 +-
 docs/confidential-guest-support.txt       |  49 ++++++++
 docs/papr-pef.txt                         |  30 +++++
 docs/system/s390x/protvirt.rst            |  19 ++-
 hw/core/machine.c                         |  63 ++++++++--
 hw/i386/pc_sysfw.c                        |  17 +--
 hw/ppc/meson.build                        |   1 +
 hw/ppc/pef.c                              | 140 ++++++++++++++++++++++
 hw/ppc/spapr.c                            |   8 +-
 hw/s390x/pv.c                             |  62 ++++++++++
 hw/s390x/s390-virtio-ccw.c                |   3 +
 include/exec/confidential-guest-support.h |  62 ++++++++++
 include/hw/boards.h                       |   2 +-
 include/hw/ppc/pef.h                      |  17 +++
 include/hw/s390x/pv.h                     |  17 +++
 include/qemu/typedefs.h                   |   1 +
 include/qom/object.h                      |   3 +-
 include/sysemu/kvm.h                      |  16 ---
 include/sysemu/sev.h                      |   4 +-
 qom/object.c                              |   4 +-
 softmmu/rtc.c                             |   3 +-
 softmmu/vl.c                              |  27 ++++-
 target/i386/kvm/kvm.c                     |  20 ++++
 target/i386/sev-stub.c                    |   5 +
 target/i386/sev.c                         |  95 ++++++---------
 target/ppc/kvm.c                          |  18 ---
 target/ppc/kvm_ppc.h                      |   6 -
 32 files changed, 595 insertions(+), 191 deletions(-)
 create mode 100644 backends/confidential-guest-support.c
 create mode 100644 docs/confidential-guest-support.txt
 create mode 100644 docs/papr-pef.txt
 create mode 100644 hw/ppc/pef.c
 create mode 100644 include/exec/confidential-guest-support.h
 create mode 100644 include/hw/ppc/pef.h
```
#### [PATCH v2 0/3] Add KVM support for bus lock debug exception
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Tue Feb  2 09:04:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12061163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E9927C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 09:02:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD12A64F5D
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 09:02:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232812AbhBBJCO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 04:02:14 -0500
Received: from mga02.intel.com ([134.134.136.20]:41952 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231860AbhBBJCG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 04:02:06 -0500
IronPort-SDR: 
 XrMKU2HkKx9fiW3b+H1yepyU/f6S4zqM/oXovb0QfotGbQqPIk0nKyEpINDWtcnov1J7rPAf5C
 YgLi144x3qzw==
X-IronPort-AV: E=McAfee;i="6000,8403,9882"; a="167929199"
X-IronPort-AV: E=Sophos;i="5.79,394,1602572400";
   d="scan'208";a="167929199"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Feb 2021 01:01:22 -0800
IronPort-SDR: 
 j3yg88fjdQC+eiSMyKy4p3zWzkI+sP40x0+NIYX0vo96ZYxg1B70EnzDxjKhf5KBBRDVDwY8lL
 k4TMvYAqMf3A==
X-IronPort-AV: E=Sophos;i="5.79,394,1602572400";
   d="scan'208";a="479491878"
Received: from chenyi-pc.sh.intel.com ([10.239.159.24])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 02 Feb 2021 01:01:20 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] Add KVM support for bus lock debug exception
Date: Tue,  2 Feb 2021 17:04:30 +0800
Message-Id: <20210202090433.13441-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A bus lock is acquired either through split locked access to writeback
(WB) memory or by using locks to uncacheable (UC) memory. This is
typically > 1000 cycles slower than atomic opertaion within a cache
line. It also disrupts performance on other cores.

Bus lock debug exception is a sub-feature of bus lock detection. It is
an ability to notify the kernel by an #DB trap after the instruction
acquires a bus lock when CPL>0. This allows the kernel to enforce user
application throttling or mitigatioins.

Expose the bus lock debug exception to guest by the enumeration of
CPUID.(EAX=7,ECX=0).ECX[24]. Software in guest can enable these
exceptions by setting the DEBUGCTLMSR_BUS_LOCK_DETECT(bit 2) of
MSR_IA32_DEBUTCTL.

The bus lock #DB exception can also be intercepted by the VMM and
identified through the bit 11 of the exit qualification at VM exit. The
bit 11 (DR6_BUS_LOCK) of DR6 register is introduced to indicate a bus
lock #DB exception. DR6_BUS_LOCK has formerly always been 1 and delivery
of a bus lock #DB clears it. The VMM should emulate the exceptions by
clearing the bit 11 of the guest DR6.

Bus lock debug exception kernel patches are available at:
https://lore.kernel.org/lkml/20201124205245.4164633-1-fenghua.yu@intel.com

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html
---

Changelogs

v1->v2:
- rename the DR6_INIT to DR6_LOW_ACTIVE suggested by Paolo and split it
  out as a new commit.
- KVM v1:https://lore.kernel.org/lkml/20210108064924.1677-1-chenyi.qiang@intel.com


Chenyi Qiang (3):
  KVM: X86: Rename DR6_INIT to DR6_ACTIVE_LOW
  KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit
  KVM: X86: Expose bus lock debug exception to guest

 arch/x86/include/asm/kvm_host.h | 14 +++++++--
 arch/x86/kvm/cpuid.c            |  3 +-
 arch/x86/kvm/emulate.c          |  2 +-
 arch/x86/kvm/svm/nested.c       |  2 +-
 arch/x86/kvm/svm/svm.c          |  6 ++--
 arch/x86/kvm/vmx/nested.c       |  4 +--
 arch/x86/kvm/vmx/vmx.c          | 27 ++++++++++++++---
 arch/x86/kvm/x86.c              | 52 +++++++++++++++------------------
 arch/x86/kvm/x86.h              |  2 ++
 9 files changed, 69 insertions(+), 43 deletions(-)
```
#### [PATCH v17 0/7] KVM: arm64: Add host/guest KVM-PTP support
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Feb  2 14:11:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12061879
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B54B3C433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 14:37:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 68A9664F50
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 14:37:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234320AbhBBOha (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 09:37:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:51596 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231628AbhBBORv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 09:17:51 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1658B64DDA;
        Tue,  2 Feb 2021 14:12:11 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l6wPY-00BVqw-VN; Tue, 02 Feb 2021 14:12:09 +0000
From: Marc Zyngier <maz@kernel.org>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com, seanjc@google.com,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        kernel-team@android.com
Subject: [PATCH v17 0/7] KVM: arm64: Add host/guest KVM-PTP support
Date: Tue,  2 Feb 2021 14:11:57 +0000
Message-Id: <20210202141204.3134855-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: netdev@vger.kernel.org, yangbo.lu@nxp.com,
 john.stultz@linaro.org, tglx@linutronix.de, pbonzini@redhat.com,
 seanjc@google.com, richardcochran@gmail.com, Mark.Rutland@arm.com,
 will@kernel.org, suzuki.poulose@arm.com, Andre.Przywara@arm.com,
 steven.price@arm.com, linux-kernel@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 kvm@vger.kernel.org, Steve.Capper@arm.com, justin.he@arm.com,
 jianyong.wu@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Given that this series[0] has languished in my Inbox for the best of the
past two years, and in an effort to eventually get it merged, I've
taken the liberty to pick it up and do the changes I wanted to see
instead of waiting to go through yet another round.

All the patches have a link to their original counterpart (though I
have squashed a couple of them where it made sense). Tested both 64
and 32bit guests for a good measure. Of course, I claim full
responsibility for any bug introduced here.

* From v16 [0]:
  - Moved the KVM service discovery to its own file, plugged it into
    PSCI instead of the arch code, dropped the inlining, made use of
    asm/hypervisor.h.
  - Tidied-up the namespacing
  - Cleanup the hypercall handler
  - De-duplicate the guest code
  - Tidied-up arm64-specific documentation
  - Dropped the generic PTP documentation as it needs a new location,
    and some cleanup
  - Squashed hypercall documentation and capability into the
    main KVM patch
  - Rebased on top of 5.11-rc4

[0] https://lore.kernel.org/r/20201209060932.212364-1-jianyong.wu@arm.com

Jianyong Wu (4):
  ptp: Reorganize ptp_kvm.c to make it arch-independent
  clocksource: Add clocksource id for arm arch counter
  KVM: arm64: Add support for the KVM PTP service
  ptp: arm/arm64: Enable ptp_kvm for arm/arm64

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (2):
  arm/arm64: Probe for the presence of KVM hypervisor
  KVM: arm64: Advertise KVM UID to guests via SMCCC

 Documentation/virt/kvm/api.rst              |  9 ++
 Documentation/virt/kvm/arm/index.rst        |  1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst      | 25 ++++++
 arch/arm/include/asm/hypervisor.h           |  3 +
 arch/arm64/include/asm/hypervisor.h         |  3 +
 arch/arm64/kvm/arm.c                        |  1 +
 arch/arm64/kvm/hypercalls.c                 | 80 +++++++++++++++--
 drivers/clocksource/arm_arch_timer.c        | 33 +++++++
 drivers/firmware/psci/psci.c                |  2 +
 drivers/firmware/smccc/Makefile             |  2 +-
 drivers/firmware/smccc/kvm_guest.c          | 51 +++++++++++
 drivers/firmware/smccc/smccc.c              |  1 +
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  2 +
 drivers/ptp/ptp_kvm_arm.c                   | 28 ++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 84 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 97 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 41 +++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/ptp_kvm.h                     | 19 ++++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  2 +
 kernel/time/timekeeping.c                   |  1 +
 25 files changed, 440 insertions(+), 78 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/firmware/smccc/kvm_guest.c
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
 create mode 100644 include/linux/ptp_kvm.h
```
#### [PATCH 0/3] use kvm_complete_insn_gp more
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue Feb  2 16:51:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12062309
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89AECC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:55:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3EDD364F72
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 16:55:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236970AbhBBQz3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 11:55:29 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46356 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236865AbhBBQxN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 11:53:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612284708;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=LV11/0c842FC4pXTtG9lqAW9PRJBf4lGS2WaCRXoDNM=;
        b=NlBVUnmm3j+MUtOt0Yj1yBjOiVfgsLrA3wJs7YAFsz23BMPRd8MU929UBjswfcedf2K38n
        l59jtm7A/IOreQyorJZ2ZLdikbNIbbh5KIgUF8M0PXuemDCjbs4f1A8HpKv+62rQ2ccAYR
        LTiPtr9UVK+CQl0rTAIUi5nkIuJkV04=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-91--oPDCLPCMAGVtpEc-aaSJQ-1; Tue, 02 Feb 2021 11:51:43 -0500
X-MC-Unique: -oPDCLPCMAGVtpEc-aaSJQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 36EDC195D56A;
        Tue,  2 Feb 2021 16:51:42 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CD77460862;
        Tue,  2 Feb 2021 16:51:41 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: seanjc@google.com
Subject: [PATCH 0/3] use kvm_complete_insn_gp more
Date: Tue,  2 Feb 2021 11:51:38 -0500
Message-Id: <20210202165141.88275-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_complete_insn_gp is a nice little function that dates back to more
than 10 years ago but was almost never used.

This simple series continues what was done for RDMSR/WRMSR in preparation
for SEV-ES support, using it in XSETBV, INVPCID and MOV to DR intercepts.

Paolo

Paolo Bonzini (3):
  KVM: x86: move kvm_inject_gp up from kvm_set_xcr to callers
  KVM: x86: move kvm_inject_gp up from kvm_handle_invpcid to callers
  KVM: x86: move kvm_inject_gp up from kvm_set_dr to callers

 arch/x86/kvm/svm/svm.c | 32 +++++++++++++++-----------------
 arch/x86/kvm/vmx/vmx.c | 35 ++++++++++++++++++-----------------
 arch/x86/kvm/x86.c     | 38 ++++++++++++--------------------------
 3 files changed, 45 insertions(+), 60 deletions(-)
```
#### [PATCH v2 0/2] s390/kvm: fix MVPG when in VSIE
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Tue Feb  2 18:00:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12062501
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DF37FC433DB
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:06:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9BA0D64FA0
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:06:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238043AbhBBSGF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 13:06:05 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:59470 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S234405AbhBBSBR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 2 Feb 2021 13:01:17 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 112HUxl6004795;
        Tue, 2 Feb 2021 13:00:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=xvHIsgzKyZQkrHD83FTOBU/tApKe6WvjIoLg2C2AXP8=;
 b=cwdpNrRxJ/zUjhQ+fJsDXxK0tJ9NwIoJHYynpeprhsPqe0IzjMbg6CJcZ6N0T8HBtIxI
 ACZN2p7hI7doMK/BDjFrp/oKCjFdcobad4qmda2wF/BtdYIkVw1luWoowqTNIY/5oY7n
 FBr08x6PPKeE8ROuJR0FR9Ja6/BcpXmvwFlvYQQIBh0XUTChrtRMbtYvGbe3zHsHOJ5/
 El10H/DMecbzk8MAy19IMVlFRuvbWMzHp/4BMHXvJMm5Us3UqhoghihVDOE6+3/EPpMs
 qgBIYOiAoSUvoWMvMj6P44pueiIvqFVEkfCMcBFWIXchtk7a6ZZRLZMN0P1/OEtLCyp1 2g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36fb3n14aj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 13:00:34 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 112HV3Id005344;
        Tue, 2 Feb 2021 13:00:34 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36fb3n149j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 13:00:34 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 112HrQ39030725;
        Tue, 2 Feb 2021 18:00:32 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06fra.de.ibm.com with ESMTP id 36cxqh9mqx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 02 Feb 2021 18:00:32 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 112I0K4v29819208
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 2 Feb 2021 18:00:20 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 61275AE057;
        Tue,  2 Feb 2021 18:00:29 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 054A7AE063;
        Tue,  2 Feb 2021 18:00:29 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.15.83])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  2 Feb 2021 18:00:28 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v2 0/2] s390/kvm: fix MVPG when in VSIE
Date: Tue,  2 Feb 2021 19:00:26 +0100
Message-Id: <20210202180028.876888-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-02_08:2021-02-02,2021-02-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 mlxscore=0 clxscore=1015 impostorscore=0 phishscore=0
 adultscore=0 lowpriorityscore=0 bulkscore=0 suspectscore=0 mlxlogscore=825
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102020112
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current handling of the MVPG instruction when executed in a nested
guest is wrong, and can lead to the nested guest hanging.

This patchset fixes the behaviour to be more architecturally correct,
and fixes the hangs observed.

v1->v2
* complete rewrite

Claudio Imbrenda (2):
  s390/kvm: extend kvm_s390_shadow_fault to return entry pointer
  s390/kvm: VSIE: correctly handle MVPG when in VSIE

 arch/s390/kvm/gaccess.c |  26 ++++++++--
 arch/s390/kvm/gaccess.h |   5 +-
 arch/s390/kvm/vsie.c    | 102 ++++++++++++++++++++++++++++++++++++----
 3 files changed, 119 insertions(+), 14 deletions(-)
```
#### [PATCH v2 00/28] Allow parallel MMU operations with TDP MMU
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue Feb  2 18:57:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12062665
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E7D85C433E9
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:59:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9004E64F61
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 18:59:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239283AbhBBS7u (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 13:59:50 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57266 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S239210AbhBBS6T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 13:58:19 -0500
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 54B29C0613ED
        for <kvm@vger.kernel.org>; Tue,  2 Feb 2021 10:57:39 -0800 (PST)
Received: by mail-pj1-x104a.google.com with SMTP id a18so2875276pjs.2
        for <kvm@vger.kernel.org>; Tue, 02 Feb 2021 10:57:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=tnlVsNI+nZgrGXxdOgd1okV91+LRu9Y5YI7uQwKH0UU=;
        b=Qfq3P/NISj2yjPjKvf7D0cPufC7LxazyawfI7KOQSX3qrmmp9s9IVzwnEvyalBtZmS
         LYV3x94JslciL687Bq480NezmotflkO9DQ4aLeRsHL/CrVTyCo51kXo0n0qbtaqywjs2
         CFOZnmiDplrlVnvX326KT4B4M7M9XDSKLAsSdof8pGsIV57gQ3aLXWgfhFKfLenKWf5C
         8YXF6KelCa+SydvCsSCbOl60Yi0xypbAcv9X6uND9SafIUO5YoKWJIHCpSiS47vph8Jh
         jhp0SXyecvGjWhQhE4POwh7Y8F6BWxsUSY/BrA7f1qgx8oNJ9i6BX0oyiz4aozJPJOid
         jHuA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=tnlVsNI+nZgrGXxdOgd1okV91+LRu9Y5YI7uQwKH0UU=;
        b=PDDPzYYHwQV8f2zuQlpltzgmBmCWLbzhZL/9wfNvo3qdU1O5hplHqMcPAYDPydCyMG
         EDZCXHGcJ8gF1rmd7iYUp8FWxgQjgh1BPk0ej75i34FyrdqkL95JzL0SllANwy5Lqr3u
         jylnqEZeFQAeYx6cxiw4sFNF6B6v1gcXMSHg+Z4+Vzw3ac657eETbUt7SvsqCNQdcRYw
         pxJnmeWwC17Fs4zyTklgyNRIGSU7FfW12vErN/fdP59O11j9Ow/ftbxkcRgP7bQgGOjs
         YshF3nwjfPZGmGs0DfPKfdWt3qokVw37+fStA40Sol5HST8nfpUhKwl4XBoquoyvQT1B
         hEJw==
X-Gm-Message-State: AOAM531uJTzJ9YSMh/WS4B1X5oGg2LuHdKHDB5nHbqmpIP5NzLa/Fq8y
        f6sOJN0GmxMkc0Tp36uk3Y53QYYijCQs
X-Google-Smtp-Source: 
 ABdhPJwt9QdkeZPUjxqfU3W0jnqT4uZJZvJqucaDYAgaVKy+4r7MbT8aMTwpvQUTl37Y7dg13B1RkbiALyQA
Sender: "bgardon via sendgmr" <bgardon@bgardon.sea.corp.google.com>
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:9090:561:5a98:6d47])
 (user=bgardon job=sendgmr) by 2002:a17:90a:4b49:: with SMTP id
 o9mr5623083pjl.182.1612292258781; Tue, 02 Feb 2021 10:57:38 -0800 (PST)
Date: Tue,  2 Feb 2021 10:57:06 -0800
Message-Id: <20210202185734.1680553-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH v2 00/28] Allow parallel MMU operations with TDP MMU
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Peter Feiner <pfeiner@google.com>,
        Junaid Shahid <junaids@google.com>,
        Jim Mattson <jmattson@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TDP MMU was implemented to simplify and improve the performance of
KVM's memory management on modern hardware with TDP (EPT / NPT). To build
on the existing performance improvements of the TDP MMU, add the ability
to handle vCPU page faults, enabling and disabling dirty logging, and
removing mappings, in parallel. In the current implementation,
vCPU page faults (actually EPT/NPT violations/misconfigurations) are the
largest source of MMU lock contention on VMs with many vCPUs. This
contention, and the resulting page fault latency, can soft-lock guests
and degrade performance. Handling page faults in parallel is especially
useful when booting VMs, enabling dirty logging, and handling demand
paging. In all these cases vCPUs are constantly incurring  page faults on
each new page accessed.

Broadly, the following changes were required to allow parallel page
faults (and other MMU operations):
-- Contention detection and yielding added to rwlocks to bring them up to
   feature parity with spin locks, at least as far as the use of the MMU
   lock is concerned.
-- TDP MMU page table memory is protected with RCU and freed in RCU
   callbacks to allow multiple threads to operate on that memory
   concurrently.
-- The MMU lock was changed to an rwlock on x86. This allows the page
   fault handlers to acquire the MMU lock in read mode and handle page
   faults in parallel, and other operations to maintain exclusive use of
   the lock by acquiring it in write mode.
-- An additional lock is added to protect some data structures needed by
   the page fault handlers, for relatively infrequent operations.
-- The page fault handler is modified to use atomic cmpxchgs to set SPTEs
   and some page fault handler operations are modified slightly to work
   concurrently with other threads.

This series also contains a few bug fixes and optimizations, related to
the above, but not strictly part of enabling parallel page fault handling.

Correctness testing:
The following tests were performed with an SMP kernel and DBX kernel on an
Intel Skylake machine. The tests were run both with and without the TDP
MMU enabled.
-- This series introduces no new failures in kvm-unit-tests
SMP + no TDP MMU no new failures
SMP + TDP MMU no new failures
DBX + no TDP MMU no new failures
DBX + TDP MMU no new failures
-- All KVM selftests behave as expected
SMP + no TDP MMU all pass except ./x86_64/vmx_preemption_timer_test
SMP + TDP MMU all pass except ./x86_64/vmx_preemption_timer_test
(./x86_64/vmx_preemption_timer_test also fails without this patch set,
both with the TDP MMU on and off.)
DBX + no TDP MMU all pass
DBX + TDP MMU all pass
-- A VM can be booted running a Debian 9 and all memory accessed
SMP + no TDP MMU works
SMP + TDP MMU works
DBX + no TDP MMU works
DBX + TDP MMU works

This series can be viewed in Gerrit at:
https://linux-review.googlesource.com/c/linux/kernel/git/torvalds/linux/+/7172

Changelog v1 -> v2:
- Removed the MMU lock union + using a spinlock when the TDP MMU is disabled
- Merged RCU commits
- Extended additional MMU operations to operate in parallel
- Ammended dirty log perf test to cover newly parallelized code paths
- Misc refactorings (see changelogs for individual commits)
- Big thanks to Sean and Paolo for their thorough review of v1

Ben Gardon (28):
  KVM: x86/mmu: change TDP MMU yield function returns to match
    cond_resched
  KVM: x86/mmu: Add comment on __tdp_mmu_set_spte
  KVM: x86/mmu: Add lockdep when setting a TDP MMU SPTE
  KVM: x86/mmu: Don't redundantly clear TDP MMU pt memory
  KVM: x86/mmu: Factor out handling of removed page tables
  locking/rwlocks: Add contention detection for rwlocks
  sched: Add needbreak for rwlocks
  sched: Add cond_resched_rwlock
  KVM: x86/mmu: Fix braces in kvm_recover_nx_lpages
  KVM: x86/mmu: Fix TDP MMU zap collapsible SPTEs
  KVM: x86/mmu: Merge flush and non-flush tdp_mmu_iter_cond_resched
  KVM: x86/mmu: Rename goal_gfn to next_last_level_gfn
  KVM: x86/mmu: Ensure forward progress when yielding in TDP MMU iter
  KVM: x86/mmu: Yield in TDU MMU iter even if no SPTES changed
  KVM: x86/mmu: Skip no-op changes in TDP MMU functions
  KVM: x86/mmu: Clear dirtied pages mask bit before early break
  KVM: x86/mmu: Protect TDP MMU page table memory with RCU
  KVM: x86/mmu: Use an rwlock for the x86 MMU
  KVM: x86/mmu: Factor out functions to add/remove TDP MMU pages
  KVM: x86/mmu: Use atomic ops to set SPTEs in TDP MMU map
  KVM: x86/mmu: Flush TLBs after zap in TDP MMU PF handler
  KVM: x86/mmu: Mark SPTEs in disconnected pages as removed
  KVM: x86/mmu: Allow parallel page faults for the TDP MMU
  KVM: x86/mmu: Allow zap gfn range to operate under the mmu read lock
  KVM: x86/mmu: Allow zapping collapsible SPTEs to use MMU read lock
  KVM: x86/mmu: Allow enabling / disabling dirty logging under MMU read
    lock
  KVM: selftests: Add backing src parameter to dirty_log_perf_test
  KVM: selftests: Disable dirty logging with vCPUs running

 arch/x86/include/asm/kvm_host.h               |  15 +
 arch/x86/kvm/mmu/mmu.c                        | 120 +--
 arch/x86/kvm/mmu/mmu_internal.h               |   9 +-
 arch/x86/kvm/mmu/page_track.c                 |   8 +-
 arch/x86/kvm/mmu/paging_tmpl.h                |   8 +-
 arch/x86/kvm/mmu/spte.h                       |  21 +-
 arch/x86/kvm/mmu/tdp_iter.c                   |  46 +-
 arch/x86/kvm/mmu/tdp_iter.h                   |  21 +-
 arch/x86/kvm/mmu/tdp_mmu.c                    | 741 ++++++++++++++----
 arch/x86/kvm/mmu/tdp_mmu.h                    |   5 +-
 arch/x86/kvm/x86.c                            |   4 +-
 include/asm-generic/qrwlock.h                 |  24 +-
 include/linux/kvm_host.h                      |   5 +
 include/linux/rwlock.h                        |   7 +
 include/linux/sched.h                         |  29 +
 kernel/sched/core.c                           |  40 +
 .../selftests/kvm/demand_paging_test.c        |   3 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  25 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   6 -
 .../selftests/kvm/include/perf_test_util.h    |   3 +-
 .../testing/selftests/kvm/include/test_util.h |  14 +
 .../selftests/kvm/lib/perf_test_util.c        |   6 +-
 tools/testing/selftests/kvm/lib/test_util.c   |  29 +
 virt/kvm/dirty_ring.c                         |  10 +
 virt/kvm/kvm_main.c                           |  46 +-
 25 files changed, 963 insertions(+), 282 deletions(-)
```
#### [PATCH v4 0/3] KVM: SVM: Refactor vcpu_load/put to use vmload/vmsave
##### From: Michael Roth <michael.roth@amd.com>

```c
From patchwork Tue Feb  2 19:01:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Michael Roth <michael.roth@amd.com>
X-Patchwork-Id: 12062685
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42CD0C433E6
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:05:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F1F264F5F
	for <kvm@archiver.kernel.org>; Tue,  2 Feb 2021 19:05:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239490AbhBBTFA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 2 Feb 2021 14:05:00 -0500
Received: from mail-mw2nam12hn2242.outbound.protection.outlook.com
 ([52.100.167.242]:26593
        "EHLO NAM12-MW2-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S239398AbhBBTCq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 2 Feb 2021 14:02:46 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=RT3Kpnut13EWImlL+reOFF3ffo5bpr7wkYi9xJ1kflOybAA0pEcQa3iESi9qpZSi0VqpcSn1RM70s0R7cn2sHTslz2zaYd3Vdxi14qJwTwBBHUYYs7Zz3dskz/kSmeYUTTpJcKGX4hSwmxZF3TDPX1WUeo8q7OEnaM53JPUmK3qJvrcrlKq94SKzX389d4av/AjYCBGKPOaWaBTmMNgDHqjBSqirhYJv5X0EuJvG9eUkCDRW3HRDKDeclHnQYskD2lmb8tNoIR0kgT5gdxdl+uWqcO/G/KFMqzCHjDiQ1NBVUrLR0HKtJXaC41OIomxk+8eTiaZHLTp9V+Mtr0baTg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Tg4DLzk/v5vHwbO0FrMeFu/54LmErVdbGkbAaUud/2Q=;
 b=KXqukssISv+b3RAYpyk9zZMjrGGp/UicBg0l5T07hjCMpmB5nLcCQACyfUi6rr7NgJ9nL4Cr641/rDGHqPwitw8+txHDarsC0Y/O/bV57tkYXIO1t+Ae32l/eQIi9bvSHeWM2bhcLudep/sqwwe+QwTzpXwqQDIZ9WkhgRuawccRZ29OLzXYBH3Z7fOa5fxzdPGsHwUKBGO2SvvWCuxOSCcudZhmUITG7TZ5kXRX5STpZAI/PCS0mxuZXtchZ6W1RHvp5npQq/Fi8GEcuV+xQjyWmdHF+VWjlLgtP4dKbtq7U8oF2obzjmStLMeQE01e4qISaKVkvFgkToGqApiduw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=Tg4DLzk/v5vHwbO0FrMeFu/54LmErVdbGkbAaUud/2Q=;
 b=o6YL/mzqcSFml+yj0HaU812UVlU8Hjd7zcmAC504OSxwIil02VsZJJ00VEbI35QvNdJ1qX43bZq5LCh6dwsf4oHzl/oyUVgphbZa7XeF9vJsNm912IczGSOhdetjKxT45SlfOggKEt+SNk29jlU/FBtdrTaMDVhdR5km2uF+QVg=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
 by CH2PR12MB4264.namprd12.prod.outlook.com (2603:10b6:610:a4::15) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.24; Tue, 2 Feb
 2021 19:01:57 +0000
Received: from CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f]) by CH2PR12MB4133.namprd12.prod.outlook.com
 ([fe80::81f6:605c:f345:b99f%3]) with mapi id 15.20.3805.027; Tue, 2 Feb 2021
 19:01:57 +0000
From: Michael Roth <michael.roth@amd.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Andy Lutomirski <luto@amacapital.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/3] KVM: SVM: Refactor vcpu_load/put to use vmload/vmsave
 for host state
Date: Tue,  2 Feb 2021 13:01:23 -0600
Message-Id: <20210202190126.2185715-1-michael.roth@amd.com>
X-Mailer: git-send-email 2.25.1
X-Originating-IP: [165.204.78.25]
X-ClientProxiedBy: SN6PR01CA0001.prod.exchangelabs.com (2603:10b6:805:b6::14)
 To CH2PR12MB4133.namprd12.prod.outlook.com (2603:10b6:610:7a::13)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost (165.204.78.25) by
 SN6PR01CA0001.prod.exchangelabs.com (2603:10b6:805:b6::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3825.17 via Frontend
 Transport; Tue, 2 Feb 2021 19:01:57 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 902c6264-e04e-4990-e841-08d8c7ad03a3
X-MS-TrafficTypeDiagnostic: CH2PR12MB4264:
X-Microsoft-Antispam-PRVS: 
 <CH2PR12MB426428A737A551BD7D24D03595B59@CH2PR12MB4264.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 X95fdZM6c4oB0Cs9qOjGLFYjzgdDkrZu1JyIUDUXkq4EwMmU//F7jyI9xDtwqBrWcIMJWjiKACRMGhw+YK7gAYH96xIey1KyAzXWt/xzDYNsU1ig7QgaiGg9bzwN2cX9dY+Z9OrA9qLODSJAKn6j3zWyVh6VkY0nalcfp8X1vXwvC6ZazO1ovFqFWVKYmUeclfCGbNVBC/oUtgrOckVp5IMN26SxL9K0CIfXD3DqyT9TNWEAdVs6NBSjllQvw22sNcoOCw7GHkMSo6cBEfiXJaHY2d1BBrVA/+b3yJnYb0ylmi8Mt5+VLPGE89SSjMTPG8C2DRxKxfhkK2CJDJMtTWXTQ4RLKkK4TGFGNt+Yxx5TGsVge/Td5y9kAlKIfwWFGdQ8l3h1+RxWL2azsfz9p9htvWfynGMb/ZLuM7yZBrlEg+9oTgB7zllYwtyrxi15vIXxftlr+IP4Wa2gUN30jPClJTonUyHFO8jv55QsSxSahOfAPw2YyJ+rhL31L0E0H202HzK86a1VfSt9s4TLiQZXh3YACP6gaHnD3trT+VyyaSe6ksfGOP6PtRzox7AQzdphi6jai/7d/9ZA1C3cbVWX16TkVLdTSuCv55QxSgFNbz/jMxESrQ3V01iMt5chg0awdFHO6tmXdoPqubd/J7bRqTcn211Z0n5VckNWGumOiX+qmR3mn8AXRNE87sVAydzUoBxylvJ8o/vwzBBViG0R+hK8mAyDF6Xt4kc8tg8YmfXFeh7DsYTycYE26+5hdQ4oN0FlOcAbMQXXJkZILfUU4erYhsPbF7k7cS87AE88fycRgwVwUxyADRVx/bwbf/sUr1BcewTjVgWDXRd9830lbabTpGJlpcUiXSs7/FDbQaaMm5mqoJ1GY7dNa84cteMqlV6JSKqTiMsoBr2DwEcm16wmA4gfShwfIENK3tCANZNAQWP3aAdvYrwYTk3JfkOmDV8A1TuJYAZoL732dQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:5;SRV:;IPV:NLI;SFV:SPM;H:CH2PR12MB4133.namprd12.prod.outlook.com;PTR:;CAT:OSPM;SFS:(4636009)(396003)(376002)(136003)(366004)(39860400002)(346002)(186003)(6666004)(16526019)(66476007)(66556008)(2616005)(956004)(36756003)(8936002)(44832011)(26005)(2906002)(54906003)(83380400001)(86362001)(478600001)(8676002)(966005)(6916009)(7416002)(1076003)(6486002)(52116002)(4326008)(5660300002)(66946007)(6496006)(316002)(23200700001);DIR:OUT;SFP:1501;
X-MS-Exchange-AntiSpam-MessageData: 
 pNsf4GPWuVjbb58olpTLMKDoVJkh3Cn/SoMeSHb3Cq6G3/xzhatkTtY3/zbtnNcNCRoGmDAgmtChx8u8A3dEEbvt3Aux4Ncn1oebOObof4YUB2IApoajrfMhA3FeY55WQtSlW1kv2IaRIaPJAIfRyHccEjVQYBuGgdmG9K21f/H85hlekp/pIWDmAv3DHFE7iKN1kmqNE3JUb/rTkZdKW6mqG+iYKXw0VVfY3Nou6aat09rrhb/uJN0LGAVX9eQhimwdSb/ftx6lhPPa4h/MToKRusRQ1IR/HJbPBx2E1IXH+3j76KeDNdEJJfZsFnDDBOUYkFg8r5K4ve6uo1DmNqNk8JE7y1K/2PREcPgvzoFdfRGwReTvw1XmSEHe4h2FoddFSGuqsHeRJMn8Rw4qN8VXh5WoooBBGhxeP2Erovu/bueoYHsr3E1wExXwv7GurUeqEFR6oDatPKpXJMRm2owqk0ta+hMUiFx+h7183nWLnfFQuULeL/KYYsV5frCmdxUGHlqeSmTr0GLz7T8HmzJXqoLhjv+chxyy1LY7y7NfLYIJmwEPE5szXVp4MVkPIbskLL4WqwmJrRijAyfvic/jqdrPqTU8663hyabDYhEze1hoxC2Ar8ldM24uVOTVMkdNbCnhfs6u/ZMFlyfFC+C/WvavP4DO1vM8LSPN8+Rqynh1sDTH1urDEQvg739hD93NtsQDztAwtI7j45oALELP4qaA4uyCSxHa9R85kgn7feOVdHMa+yfPpnLg5ExUv+Cyi/HEZrvnTtipX4j4hg0NIO4wRH9o4Fo9EvqgoZ/es6/XruEGuLvScQoLeAVKsLLKY1XfMT3lRgSomMSBMbIUO1Ml6NC20QZ0e75cGJ+wRTs6GC8Lp4nAbGKezFpZ+/Pq/Ojc+i9Hg6tGcxA9+bdAh4jWXxuUtgMIuzxn1mwmEnXrfXXxtc1mK/9pGouraiaCTTiA7Dy0spRtrtkACE7aR7I20pKBRcygh5ZJY7kg8SxqM2/imSt9n5eXyLMZW1GDKz5RcEQjtAUkxTzr6vT9HA2oQ5WrR/4ieH78cKioecPNLchNKsharJ2yL8acWt3n/L9ADKFi36MB1HUq1gA+B+YTPXU7MGdgoyBjvG/qzTGxn7bamxv7WhJzwFZkR7yYaB6WUsoPo14cQ83SvQ46gNKi1vZW9MHY6tAc4fPmpd60P3bIlcthrYHtsudx8IMoFt5i7okInRQADapw+l55mtjutMXjWTT3sHuRcOsEEc1nz84SJ44Ujgv9SNH/D+6IwYbxo92UsoGZ9s/BaGTa5ETTLZBLwWdFBEdgXq+rfusFYOLHEcjRVAdBB8hG
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 902c6264-e04e-4990-e841-08d8c7ad03a3
X-MS-Exchange-CrossTenant-AuthSource: CH2PR12MB4133.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Feb 2021 19:01:57.8174
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 Tht62JEYPw/S+MS/K/U2ulGlB8NCvOKByIaZzzvIQbyf6ZpzPkdkkV9FtDBN6m/CNCfV5HSVYuTgLBiXUszDeg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CH2PR12MB4264
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Sean, Paolo,

Following up from previous v3 discussion:

  https://lore.kernel.org/kvm/X%2FSfw15OWarseivB@google.com/

I got bit in internal testing by a bug in v3 of this series that Sean had
already pointed out in v3 comments, so I thought it might be good to go
ahead and send a v4 with those fixes included. I also saw that Sean's vmsave
helpers are now in kvm/queue, so I've rebased these on top of those, and
made use of the new vmsave/vmload helpers:

  https://lore.kernel.org/kvm/8880fedc-14aa-1f14-b87b-118ebe0932a2@redhat.com/

Thanks!

-Mike

= Overview =

This series re-works the SVM KVM implementation to use vmload/vmsave to
handle saving/restoring additional host MSRs rather than explicit MSR
read/writes, resulting in a significant performance improvement for some
specific workloads and simplifying some of the save/load code (PATCH 1).

With those changes some commonalities emerge between SEV-ES and normal
vcpu_load/vcpu_put paths, which we then take advantage of to share more code,
as well as refactor them in a way that more closely aligns with the VMX
implementation (PATCH 2 and 3).

v4:
 - rebased on kvm/queue
 - use sme_page_pa() when accessing save area (Sean)
 - make sure vmload during host reboot is handled (Sean)
 - introduce vmload() helper like we have with vmsave(), use that instead
   of moving the introduce to ASM (Sean)

v3:
 - rebased on kvm-next
 - remove uneeded braces from host MSR save/load loops (Sean)
 - use page_to_phys() in place of page_to_pfn() and shifting (Sean)
 - use stack instead of struct field to cache host save area outside of
   per-cpu storage, and pass as an argument to __svm_vcpu_run() to
   handle the VMLOAD in ASM code rather than inlining ASM (Sean/Andy)
 - remove now-uneeded index/sev_es_restored fields from
   host_save_user_msrs list
 - move host-saving/guest-loading of registers to prepare_guest_switch(),
   and host-loading of registers to prepare_host_switch, for both normal
   and sev-es paths (Sean)

v2:
 - rebase on latest kvm/next
 - move VMLOAD to just after vmexit so we can use it to handle all FS/GS
   host state restoration and rather than relying on loadsegment() and
   explicit write to MSR_GS_BASE (Andy)
 - drop 'host' field from struct vcpu_svm since it is no longer needed
   for storing FS/GS/LDT state (Andy)

 arch/x86/kvm/svm/sev.c     |  30 +-----------------------------
 arch/x86/kvm/svm/svm.c     | 107 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++---------------------------------------------------
 arch/x86/kvm/svm/svm.h     |  29 +++++------------------------
 arch/x86/kvm/svm/svm_ops.h |   5 +++++
 4 files changed, 67 insertions(+), 104 deletions(-)
```
