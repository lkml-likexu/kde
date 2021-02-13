#### [GIT PULL] KVM/arm64 updates for 5.12
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12085407
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-22.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DC0CCC433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 14:38:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEE0064E6B
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 14:38:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230385AbhBLOiJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 09:38:09 -0500
Received: from mail.kernel.org ([198.145.29.99]:46892 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229815AbhBLOh4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 12 Feb 2021 09:37:56 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0E7CB64DD9;
        Fri, 12 Feb 2021 14:37:15 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lAZZJ-00DqME-4c; Fri, 12 Feb 2021 14:37:13 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        Ard Biesheuvel <ardb@kernel.org>,
        David Brazdil <dbrazdil@google.com>,
        Eric Auger <eric.auger@redhat.com>,
        Quentin Perret <qperret@google.com>,
        Will Deacon <will@kernel.org>,
        Yanan Wang <wangyanan55@huawei.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org, kernel-team@android.com
Subject: [GIT PULL] KVM/arm64 updates for 5.12
Date: Fri, 12 Feb 2021 14:36:57 +0000
Message-Id: <20210212143657.3312035-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, ardb@kernel.org, dbrazdil@google.com,
 eric.auger@redhat.com, qperret@google.com, will@kernel.org,
 wangyanan55@huawei.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's the initial set of KVM/arm64 updates for 5.11.

The most notable change this time is David's work to finally build the
nVHE EL2 object as a relocatable object. This makes the code a lot
cleaner, more reliable (we don't have to assume things about code
generation), and allows... function pointers, with any ugly hack!
Progress, at last, and a huge thank you to David!

We also gained support for the new TRNG standard hypercall, and a nice
optimisation for concurrent translation faults targeting the same
page. The rest is a small batch of fixes and other cleanups.

Note that there is another bunch of changes indirectly affecting
KVM/arm64 that are routed via the arm64 tree, as we turn upside down
the way we boot Linux on a VHE system. It's all good fun.

This pull request also comes with strings attached:
- the kvmarm-fixes-5.11-2 tag in order to avoid ugly conflicts, which
  explains a sense of déjà-vu in the short-log below
- the arm64/for-next/misc branch because of dependencies

Please pull,

	M.

The following changes since commit 19c329f6808995b142b3966301f217c831e7cf31:

  Linux 5.11-rc4 (2021-01-17 16:37:05 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-5.12

for you to fetch changes up to c93199e93e1232b7220482dffa05b7a32a195fe8:

  Merge branch 'kvm-arm64/pmu-debug-fixes-5.11' into kvmarm-master/next (2021-02-12 14:08:41 +0000)

----------------------------------------------------------------
KVM/arm64 updates for Linux 5.12

- Make the nVHE EL2 object relocatable, resulting in much more
  maintainable code
- Handle concurrent translation faults hitting the same page
  in a more elegant way
- Support for the standard TRNG hypervisor call
- A bunch of small PMU/Debug fixes
- Allow the disabling of symbol export from assembly code
- Simplification of the early init hypercall handling

----------------------------------------------------------------
Alexandru Elisei (2):
      KVM: arm64: Use the reg_to_encoding() macro instead of sys_reg()
      KVM: arm64: Correct spelling of DBGDIDR register

Andrew Scull (1):
      KVM: arm64: Simplify __kvm_hyp_init HVC detection

Ard Biesheuvel (2):
      firmware: smccc: Add SMCCC TRNG function call IDs
      KVM: arm64: Implement the TRNG hypervisor call

David Brazdil (9):
      KVM: arm64: Allow PSCI SYSTEM_OFF/RESET to return
      KVM: arm64: Rename .idmap.text in hyp linker script
      KVM: arm64: Set up .hyp.rodata ELF section
      KVM: arm64: Add symbol at the beginning of each hyp section
      KVM: arm64: Generate hyp relocation data
      KVM: arm64: Apply hyp relocations at runtime
      KVM: arm64: Fix constant-pool users in hyp
      KVM: arm64: Remove patching of fn pointers in hyp
      KVM: arm64: Remove hyp_symbol_addr

Marc Zyngier (20):
      KVM: arm64: Hide PMU registers from userspace when not available
      KVM: arm64: Simplify handling of absent PMU system registers
      arm64: Drop workaround for broken 'S' constraint with GCC 4.9
      KVM: arm64: Filter out v8.1+ events on v8.0 HW
      KVM: Forbid the use of tagged userspace addresses for memslots
      Merge branch 'arm64/for-next/misc' into kvm-arm64/hyp-reloc
      KVM: arm64: Make gen-hyprel endianness agnostic
      KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
      KVM: arm64: Fix AArch32 PMUv3 capping
      KVM: arm64: Add handling of AArch32 PCMEID{2,3} PMUv3 registers
      KVM: arm64: Refactor filtering of ID registers
      KVM: arm64: Limit the debug architecture to ARMv8.0
      KVM: arm64: Upgrade PMU support to ARMv8.4
      KVM: arm64: Use symbolic names for the PMU versions
      Merge tag 'kvmarm-fixes-5.11-2' into kvmarm-master/next
      Merge branch 'kvm-arm64/misc-5.12' into kvmarm-master/next
      Merge branch 'kvm-arm64/concurrent-translation-fault' into kvmarm-master/next
      Merge branch 'kvm-arm64/hyp-reloc' into kvmarm-master/next
      Merge branch 'kvm-arm64/rng-5.12' into kvmarm-master/next
      Merge branch 'kvm-arm64/pmu-debug-fixes-5.11' into kvmarm-master/next

Quentin Perret (2):
      asm-generic: export: Stub EXPORT_SYMBOL with __DISABLE_EXPORTS
      KVM: arm64: Stub EXPORT_SYMBOL for nVHE EL2 code

Steven Price (1):
      KVM: arm64: Compute TPIDR_EL2 ignoring MTE tag

Yanan Wang (3):
      KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2 map
      KVM: arm64: Filter out the case of only changing permissions from stage-2 map path
      KVM: arm64: Mark the page dirty only if the fault is handled successfully

 Documentation/virt/kvm/api.rst           |   3 +
 arch/arm64/include/asm/hyp_image.h       |  29 +-
 arch/arm64/include/asm/kvm_asm.h         |  26 --
 arch/arm64/include/asm/kvm_host.h        |   2 +
 arch/arm64/include/asm/kvm_mmu.h         |  61 ++---
 arch/arm64/include/asm/kvm_pgtable.h     |   5 +
 arch/arm64/include/asm/sections.h        |   3 +-
 arch/arm64/include/asm/sysreg.h          |   3 +
 arch/arm64/kernel/image-vars.h           |   1 -
 arch/arm64/kernel/smp.c                  |   4 +-
 arch/arm64/kernel/vmlinux.lds.S          |  18 +-
 arch/arm64/kvm/Makefile                  |   2 +-
 arch/arm64/kvm/arm.c                     |  10 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h  |   4 +-
 arch/arm64/kvm/hyp/nvhe/.gitignore       |   2 +
 arch/arm64/kvm/hyp/nvhe/Makefile         |  33 ++-
 arch/arm64/kvm/hyp/nvhe/gen-hyprel.c     | 438 +++++++++++++++++++++++++++++++
 arch/arm64/kvm/hyp/nvhe/host.S           |  29 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S       |  19 +-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c       |  11 +-
 arch/arm64/kvm/hyp/nvhe/hyp-smp.c        |   4 +-
 arch/arm64/kvm/hyp/nvhe/hyp.lds.S        |   9 +-
 arch/arm64/kvm/hyp/nvhe/psci-relay.c     |  37 ++-
 arch/arm64/kvm/hyp/pgtable.c             |  83 +++---
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c |   2 +-
 arch/arm64/kvm/hypercalls.c              |   6 +
 arch/arm64/kvm/mmu.c                     |  13 +-
 arch/arm64/kvm/pmu-emul.c                |  24 +-
 arch/arm64/kvm/sys_regs.c                | 178 ++++++++-----
 arch/arm64/kvm/trng.c                    |  85 ++++++
 arch/arm64/kvm/va_layout.c               |  34 ++-
 include/asm-generic/export.h             |   2 +-
 include/linux/arm-smccc.h                |  31 +++
 virt/kvm/kvm_main.c                      |   1 +
 34 files changed, 934 insertions(+), 278 deletions(-)
 create mode 100644 arch/arm64/kvm/hyp/nvhe/gen-hyprel.c
 create mode 100644 arch/arm64/kvm/trng.c
```
#### [PATCH v2 1/1] s390:kvm: diag9c forwarding
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12084935
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB77AC433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 08:41:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96D8064E39
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 08:41:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230105AbhBLIk7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 03:40:59 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:61158 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230209AbhBLIk1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 03:40:27 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11C8Xxie145185;
        Fri, 12 Feb 2021 03:39:44 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=eEyyw/JG8dndF7Hy8KSpk/rjQK2Wmj2BTdpkw6D7exM=;
 b=iD2kheKr9WbZKRVRfCEj5xziF+HDckvk8nD+A8jkblKMPMxjzawMEPMxFkOiBCHzMrCJ
 g2TKeeX6RS/ULz1KdOH9n5MnmfrpM8fUZII/MeFMXE0aGQVUfu5Gy8SYX6oJsclHEYyD
 NI0NdVFb6l7P1jNbDcBY8EcNkXJQIItkzX4ChO+iDg1wSGhPHV2O6JXv1OdCZZWQAVzc
 lcqcgB/xbGHMK1750tLk/uzqgNMgI1oW2Z3DOepdTeFSgoWYTlxe4mZ5x2izUoO1e8sK
 DdNCPCBgcQkpSCRU3nbbmTc7Xu2rUAGnn3qpc8sB7to6a9EvGbaW/GDZ9+NwYUJH+DhU bw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36nnyfgk6n-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 03:39:44 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11C8YJ65147319;
        Fri, 12 Feb 2021 03:39:44 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36nnyfgk5t-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 03:39:44 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11C8bDsS018646;
        Fri, 12 Feb 2021 08:39:41 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma06fra.de.ibm.com with ESMTP id 36hjch3cp6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 12 Feb 2021 08:39:41 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11C8dSEu32964874
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 12 Feb 2021 08:39:28 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C62CA42041;
        Fri, 12 Feb 2021 08:39:38 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 57B6842042;
        Fri, 12 Feb 2021 08:39:38 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.28.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 12 Feb 2021 08:39:38 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        frankja@linux.ibm.com, cohuck@redhat.com, david@redhat.com,
        thuth@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v2 1/1] s390:kvm: diag9c forwarding
Date: Fri, 12 Feb 2021 09:39:36 +0100
Message-Id: <1613119176-20864-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1613119176-20864-1-git-send-email-pmorel@linux.ibm.com>
References: <1613119176-20864-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-12_02:2021-02-12,2021-02-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 spamscore=0 mlxscore=0 mlxlogscore=999 bulkscore=0 adultscore=0
 malwarescore=0 suspectscore=0 clxscore=1015 lowpriorityscore=0
 phishscore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2102120060
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we receive intercept a DIAG_9C from the guest we verify
that the target real CPU associated with the virtual CPU
designated by the guest is running and if not we forward the
DIAG_9C to the target real CPU.

To avoid a diag9c storm we allow a maximal rate of diag9c forwarding.

The rate is calculated as a count per second defined as a
new parameter of the s390 kvm module: diag9c_forwarding_hz .

The default value is to not forward diag9c.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 Documentation/virt/kvm/s390-diag.rst | 33 ++++++++++++++++++++++++++++
 arch/s390/include/asm/kvm_host.h     |  1 +
 arch/s390/include/asm/smp.h          |  1 +
 arch/s390/kernel/smp.c               |  1 +
 arch/s390/kvm/diag.c                 | 31 +++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c             |  6 +++++
 arch/s390/kvm/kvm-s390.h             |  8 +++++++
 7 files changed, 78 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] KVM: SVM: Intercept INVPCID when it's disabled to inject #UD
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12084529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E2123C433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 00:35:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFB5264E55
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 00:35:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230339AbhBLAfI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 19:35:08 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57004 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230238AbhBLAe5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 19:34:57 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3093BC061786
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 16:34:17 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id u66so5993685qkd.13
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 16:34:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=XKAXpkAK94m0RVh5MFfko19Er9G2ZY3kVKxPG6EQzGU=;
        b=vjd6+zoLspGHBkN7ol8n4f+FjOIp8P2A/+YjMZg6o1//7bbDDw3LDFDWuQI/immX0s
         wXQdgoclJ2QdYDRqMi3zEeojvNCPe92KwX7KJ5fZ9UbzTqofpAt533+Jq84tbqxA4Y8B
         7cAx8qPdmBol9OoS8mgP6KYje4BE3GyGH87kFGokeMMb9OMtHyitSynWP52CX/MfFPg0
         5FeR/97QZf5daWhIOf+ZGCcWY5AoRPBzosRmBzWMEybSvVapSutS5FPHl8Y5y4Ve2klP
         dbrBNWf9g/wX4XGBcPOyHaVcSghSWi0fzrrKW2AtWRpDtzQ2zmMphIE52u6VDOM/+spw
         QT0A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=XKAXpkAK94m0RVh5MFfko19Er9G2ZY3kVKxPG6EQzGU=;
        b=Ko+/7yCOZ7H1pF4p26D7dVGG07E7EW/4G/zqgiCnt+DsiPQ4O/+r9obZoCG27Mpmz8
         jgcGpLKa/JZqJvYx+iA9WOG30MVrzskkiIGDKz3UT5HQASXn1niRCW28kJCozXrNeChG
         FKPU2kpYtbCFgnALvY6FOk8P66Ql6/NQ1Qx1Dc6NvSQMM1UppyAR8/67aygRrI1wDNP/
         tWabNcf4/PrC15GwlkojezYiHpZUMcAclqYUf84Fxmo8wAji1QoKMzD8MMB41TXilrdR
         JDyyecKcWgHLlaJ/6F8Tr31suumDrbLqJ73iV5LBzF3fhar+eYMHRAc0Y48OM6OGbZte
         ENSQ==
X-Gm-Message-State: AOAM533Wo6vI9VJg+mMhmXpG9jo9nZEZRj2VUwx/GUTsgPn1EFQB1RL2
        1Bzw0K9LQpn2xa479T8zX8hp4h91GlE=
X-Google-Smtp-Source: 
 ABdhPJzam5xHM6CKpgswhd+0Z76z2ZKGfRhz/IAvdhuId1g4omPd3547ZhuvaFerJAKBULuhxD/8NzglLrk=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f588:a708:f347:3ebb])
 (user=seanjc job=sendgmr) by 2002:a0c:f589:: with SMTP id
 k9mr552818qvm.0.1613090056322;
 Thu, 11 Feb 2021 16:34:16 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 11 Feb 2021 16:34:09 -0800
In-Reply-To: <20210212003411.1102677-1-seanjc@google.com>
Message-Id: <20210212003411.1102677-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210212003411.1102677-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 1/3] KVM: SVM: Intercept INVPCID when it's disabled to inject
 #UD
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Babu Moger <babu.moger@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intercept INVPCID if it's disabled in the guest, even when using NPT,
as KVM needs to inject #UD in this case.

Fixes: 4407a797e941 ("KVM: SVM: Enable INVPCID feature on AMD")
Cc: Babu Moger <babu.moger@amd.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/svm/svm.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH 1/3] vfio: Introduce vma ops registration and notifierFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12085977
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3754CC433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:29:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E661864DEC
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:29:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231977AbhBLT3V (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 14:29:21 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54741 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230390AbhBLT3Q (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 14:29:16 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613158070;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=+QyjDl1YGTxR6RiVnlw4Q0RJP2vN/bwyFH6oNtXuIi0=;
        b=cCKe11xdX7F/1f+a5TwW6iXpk1UzfkRKtNkiFcohzz82mifwnCMvpSIZeMXJH3uaBX4poi
        bb205QP1P8cDFVXEghejLGxQ2EQTml1imwR8TLOXV+VCeQWrbSuPLWz+JusSdsREBgox9c
        TnBv9OoKlliFIsmmG5mcEfXu8epGj5Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-96-GIBOazs_MQu_WbG5UIIbeA-1; Fri, 12 Feb 2021 14:27:47 -0500
X-MC-Unique: GIBOazs_MQu_WbG5UIIbeA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EB2E1C7403;
        Fri, 12 Feb 2021 19:27:45 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9A95360BE5;
        Fri, 12 Feb 2021 19:27:39 +0000 (UTC)
Subject: [PATCH 1/3] vfio: Introduce vma ops registration and notifier
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Fri, 12 Feb 2021 12:27:39 -0700
Message-ID: <161315805248.7320.13358719859656681660.stgit@gimli.home>
In-Reply-To: <161315658638.7320.9686203003395567745.stgit@gimli.home>
References: <161315658638.7320.9686203003395567745.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Create an interface through vfio-core where a vfio bus driver (ex.
vfio-pci) can register the vm_operations_struct it uses to map device
memory, along with a set of registration callbacks.  This allows
vfio-core to expose interfaces for IOMMU backends to match a
vm_area_struct to a bus driver and register a notifier for relavant
changes to the device mapping.  For now we define only a notifier
action for closing the device.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/vfio.c  |  120 ++++++++++++++++++++++++++++++++++++++++++++++++++
 include/linux/vfio.h |   20 ++++++++
 2 files changed, 140 insertions(+)

```
#### [PATCH] vfio/type1: Use follow_pte()From: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12085925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E2216C433DB
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:03:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A686564EA6
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 19:03:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231574AbhBLTDX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 14:03:23 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43349 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229832AbhBLTDV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 14:03:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613156514;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=7ooNXOow4Kc5cp7DA82+I6l6Eq7HpYL88e585qRTAoI=;
        b=NbW6EDLNIOfXrDnJ1cMAFxYOlDo7YOVBiuxrHnC6krNtC9MKlZOtGHLCkmZT7TgAMdInTH
        +SeJOJWABAVBZazDitZUoh9YN72AG/FK42JTTAwZhhNFfaF6Yi3ao1IJw427eQzLnuoUKf
        dzdFmpVV1Zc7RkPLy39k/HUXfbBfXDI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-460-naFLspz-PfSloqjQBz4ZfQ-1; Fri, 12 Feb 2021 14:01:52 -0500
X-MC-Unique: naFLspz-PfSloqjQBz4ZfQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E79449126D;
        Fri, 12 Feb 2021 19:01:50 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7A00660BF1;
        Fri, 12 Feb 2021 19:01:50 +0000 (UTC)
Subject: [PATCH] vfio/type1: Use follow_pte()
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pbonzini@redhat.com, jgg@nvidia.com,
        peterx@redhat.com
Date: Fri, 12 Feb 2021 12:01:50 -0700
Message-ID: <161315649533.7249.11715726297751446001.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

follow_pfn() doesn't make sure that we're using the correct page
protections, get the pte with follow_pte() so that we can test
protections and get the pfn from the pte.

Fixes: 5cbf3264bc71 ("vfio/type1: Fix VA->PA translation for PFNMAP VMAs in vaddr_get_pfn()")
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Reviewed-by: Jason Gunthorpe <jgg@nvidia.com>
Reported-by: kernel test robot <lkp@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c |   14 ++++++++++++--
 1 file changed, 12 insertions(+), 2 deletions(-)

```
#### [PATCH] virtio/s390: implement virtio-ccw revision 2 correctly
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 12085687
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.3 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CA425C433E0
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 17:06:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9743E64D74
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 17:06:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231327AbhBLRGO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 12 Feb 2021 12:06:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:46330 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231258AbhBLRFt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 12 Feb 2021 12:05:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613149463;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=muci2bFECA89B0jMNuPjwDVm80b8N6IObvOF04Qj7Xg=;
        b=hWpQlHCCFh4ogMSq10hmij7rj+fHYDBZmnfenppeHLP+pBQMkoedQj7kcnmDXpHI5m0Fli
        PtimYCZBfvgvOizqxbF3PG2QfR4oohAbdpFFMUAvOW8OQbwEP1hfnCr9QkhrUPZlZ156z8
        LML8Ozjv1rsAe1ZupNfBq0Dn6F6sL9A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-105-PCm_6tleO5CUMpRycwNyYw-1; Fri, 12 Feb 2021 12:04:20 -0500
X-MC-Unique: PCm_6tleO5CUMpRycwNyYw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 42AFA85B671;
        Fri, 12 Feb 2021 17:04:16 +0000 (UTC)
Received: from gondolin.redhat.com (ovpn-113-189.ams2.redhat.com
 [10.36.113.189])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A4F2B19D80;
        Fri, 12 Feb 2021 17:04:14 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Halil Pasic <pasic@linux.ibm.com>
Cc: Pierre Morel <pmorel@linux.ibm.com>, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] virtio/s390: implement virtio-ccw revision 2 correctly
Date: Fri, 12 Feb 2021 18:04:11 +0100
Message-Id: <20210212170411.992217-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CCW_CMD_READ_STATUS was introduced with revision 2 of virtio-ccw,
and drivers should only rely on it being implemented when they
negotiated at least that revision with the device.

However, virtio_ccw_get_status() issued READ_STATUS for any
device operating at least at revision 1. If the device accepts
READ_STATUS regardless of the negotiated revision (which it is
free to do), everything works as intended; a device rejecting the
command should also be handled gracefully. For correctness, we
should really limit the command to revision 2 or higher, though.

We also negotiated the revision to at most 1, as we never bumped
the maximum revision; let's do that now.

Fixes: 7d3ce5ab9430 ("virtio/s390: support READ_STATUS command for virtio-ccw")
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---

QEMU does not fence off READ_STATUS for revisions < 2, which is probably
why we never noticed this. I'm not aware of other hypervisors that do
fence it off, nor any that cannot deal properly with an unknown command.

Not sure whether this is stable worthy?

---
 drivers/s390/virtio/virtio_ccw.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] x86: Remove PCID test that INVPCID isn't enabled without PCID
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12084563
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C73C3C433E6
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 01:09:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8FEAA64E5F
	for <kvm@archiver.kernel.org>; Fri, 12 Feb 2021 01:09:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230365AbhBLBIn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 11 Feb 2021 20:08:43 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35720 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230180AbhBLBHJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Feb 2021 20:07:09 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1DCCDC0617A7
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 17:06:13 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id g17so5365814ybh.4
        for <kvm@vger.kernel.org>; Thu, 11 Feb 2021 17:06:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=Fhv1Q9NSxxwZmv6ZVWXSl3ZrCdVknKiV94qk2PWj5KY=;
        b=M6sNjp71JNXOPH26XcRa1YdrRCuZtL4Py6H/Hy2tsrpRa6Zhg12Hr8v7orLO2dXdjh
         A+KWhDigFcqg5KAxt2kGBBOqPgYElc0VsDwlZA2Pu6bkeJqiNP+cUu3ccFBa3Ije+s7t
         /jBtoGykJDuAQW+gcKxrwtnONoU/iok5WjANsDmK0mVOR3QwWPLdOI/9/6lIYrWX/kbj
         qKc3QHkhd8jippcsGugpP7eh6otMsYLmveRp715jRaN2Q9Er58/hQZKh9Hb69nKpBwpG
         bRWNJfX7J7x6SC41n4v/QE6e9r+toCi11KhZ7zao+fndrhyuGgQoIlfL3htU2i46BJjW
         EZ9g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=Fhv1Q9NSxxwZmv6ZVWXSl3ZrCdVknKiV94qk2PWj5KY=;
        b=TB5aMpmkTVfybXWlrLouwQtCTZEvr3oecc+PdyVbA0siXX7cDAB2cQ3CGDy3qM6PXd
         AqUsqbWCxkA8xakuvVaBiCDeMS9yB2v3B1at6sevht0OJOzxELaRcJbKsCWUb/7VBqjN
         DHRPdVG7di7VUQUu21Q1hTdxVnxLdIva6UuFh9HVtqdqAtFGrlNiN4xW/3pejxsTY0oL
         5MVHbdGUQaL7JZ1RQwhk1S+Jft2OWGyDG3XMdP8w0jI2cLvJ3sRkN0vvgu6EnQwuPqdJ
         jz+FivtYRjF+BOauYP82xdyEmSEgd1YajyTn9ikpfQ+X8Un5u8Ehnvtekcb6V9n4JtRx
         qEkw==
X-Gm-Message-State: AOAM530QjVdTHehVlCVpoxgNF8PgwOwtKRbvlwe6qp2aHoGswEj0p+1s
        V3c/GxF6CpGbHBpb8MPigWs/OTdXTU0=
X-Google-Smtp-Source: 
 ABdhPJxYLiR7Gj05G/CPO+CWigXBb8GTWY0DxsO//rw0ZXfWZiF/u6c32DhhVqZtgdkTylmeNAnIJoMIuj0=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f588:a708:f347:3ebb])
 (user=seanjc job=sendgmr) by 2002:a25:908f:: with SMTP id
 t15mr782326ybl.47.1613091972358;
 Thu, 11 Feb 2021 17:06:12 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu, 11 Feb 2021 17:06:03 -0800
In-Reply-To: <20210212010606.1118184-1-seanjc@google.com>
Message-Id: <20210212010606.1118184-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210212010606.1118184-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [kvm-unit-tests PATCH 1/4] x86: Remove PCID test that INVPCID isn't
 enabled without PCID
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop the test that verifies INVPCID isn't enabled in the guest without
PCID also being enabled.  SVM allows !PCID && INVPCID, and VMX will soon
follow.

https://lkml.kernel.org/r/20210212003411.1102677-1-seanjc@google.com

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 x86/pcid.c | 8 --------
 1 file changed, 8 deletions(-)

```
