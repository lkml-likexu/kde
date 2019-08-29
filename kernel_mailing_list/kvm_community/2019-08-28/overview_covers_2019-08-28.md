

#### [PATCH v2 0/2] KVM: x86: don't announce
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Aug 28 07:59:03 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11118143
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4A5E1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 07:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B5426205C9
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 07:59:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726614AbfH1H7W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 03:59:22 -0400
Received: from mx1.redhat.com ([209.132.183.28]:46960 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726341AbfH1H7J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 03:59:09 -0400
Received: from mail-wr1-f71.google.com (mail-wr1-f71.google.com
 [209.85.221.71])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E56CD882F2
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:59:08 +0000 (UTC)
Received: by mail-wr1-f71.google.com with SMTP id h8so915751wrb.11
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 00:59:08 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fXBfbXP94FsOpi1v9mBeSf+ahhRJGbCczR40mL5l1g0=;
        b=U7Tx30lc6gBp0fT27IDbb4TVDcqyQgaphuRJJjLSXofyf3VydY7t9R02lKFSvrSwUj
         mKuE1OKpg5FcPmUULgqxZwUetY2pcG6hJkYNyULWDZChsqzTG1YmXrf7WmuDFazs8Wcq
         wZMCrK6QaXZKSrWSPEzz6jL40yun3Ef2cKDicQGTYKk2Gvwb4WABGhIugzYdFGRdCKfl
         UF5tpzVkOZIujFX7PETdCJ5vo93REp1YIBAmRa9YcIP7Qd4bGkYI5gltSatPTYAdFiBj
         lKYN4CAWoVtDdE0A05Ah+BcRkiMvjKD4xUUreL+p8o5zck79TgysVQtxvSTPaXUMIggD
         Bd5w==
X-Gm-Message-State: APjAAAWC5hoQ3ad9vPUmZwHWoO63B48AuIq0Kah5aMJSmYij8WwVTXVX
        8rrDiY56GLS9XHGy0vU8Bcb/EaZ27sx5pRQGADjZrJrApdCuRXvl9D4ZRzXDe8d3UlrljN5jlAi
        dlvALVuFrYRdu
X-Received: by 2002:adf:db49:: with SMTP id f9mr2912024wrj.112.1566979147477;
        Wed, 28 Aug 2019 00:59:07 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqw6jeOXWHKp2OBmWJFh9i//W4b2alfBLT0xcTCuk+Wnz7ITWniIoIL5zWUQjKwG1rgsfWp0Gg==
X-Received: by 2002:adf:db49:: with SMTP id f9mr2912008wrj.112.1566979147295;
        Wed, 28 Aug 2019 00:59:07 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 a190sm2448469wme.8.2019.08.28.00.59.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Aug 2019 00:59:06 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH v2 0/2] KVM: x86: don't announce
 KVM_CAP_HYPERV_ENLIGHTENED_VMCS when it is unavailable
Date: Wed, 28 Aug 2019 09:59:03 +0200
Message-Id: <20190828075905.24744-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was discovered that hyperv_cpuid test now fails on AMD as it tries to
enable KVM_CAP_HYPERV_ENLIGHTENED_VMCS which is (wrongfully) reported as
available.

Changes since v1:
- This is a v2 for '[PATCH 0/3] KVM: x86: fix a couple of issues with
 Enlightened VMCS enablement' renamed as the first patch of the series
 was already merged.
- Added Jim's Reviewed-by: to PATCH1
- Added missing break in PATCH2 [Jim Mattson, Sean Christopherson] 

Vitaly Kuznetsov (2):
  KVM: x86: svm: remove unneeded nested_enable_evmcs() hook
  KVM: x86: announce KVM_CAP_HYPERV_ENLIGHTENED_VMCS support only when
    it is available

 arch/x86/kvm/svm.c | 9 +--------
 arch/x86/kvm/x86.c | 4 +++-
 2 files changed, 4 insertions(+), 9 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/4] s390x: Add skey removal facility test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Aug 28 11:36:11 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11118737
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DFB716B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 11:36:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5814822DA7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 11:36:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726300AbfH1Lg2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 07:36:28 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:1884 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726259AbfH1Lg2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 28 Aug 2019 07:36:28 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7SBXVik013793
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:36:27 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2unqfnu9s6-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 07:36:27 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 28 Aug 2019 12:36:25 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 28 Aug 2019 12:36:23 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7SBaM7Y38600884
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 28 Aug 2019 11:36:22 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3F6E6A4064;
        Wed, 28 Aug 2019 11:36:22 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7CEEAA405B;
        Wed, 28 Aug 2019 11:36:21 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 28 Aug 2019 11:36:21 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/4] s390x: Add skey removal facility test
Date: Wed, 28 Aug 2019 13:36:11 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19082811-0016-0000-0000-000002A3DC72
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082811-0017-0000-0000-000033042C98
Message-Id: <20190828113615.4769-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-28_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908280124
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The storage key removal facility (skrf) is an anti-facility, which
makes skey related instructions result in a special operation
exception when they handle storage keys. E.g. pfmf in clearing mode
does not result in an exception, but pfmf key setting does.

The skrf is always active in protected virtualization guests and can
be emulated by KVM (expected to be upstreamed with the remaining hpage
patches).

v2:
* Added march z12 bump patch
* Addressed review

Janosch Frank (4):
  s390x: Move pfmf to lib and make address void
  s390x: Storage key library functions now take void ptr addresses
  s390x: Bump march to zEC12
  s390x: Add storage key removal facility

 lib/s390x/asm/mem.h |  40 +++++++++++---
 s390x/Makefile      |   3 +-
 s390x/pfmf.c        |  71 +++++++++---------------
 s390x/skey.c        |  29 +++++-----
 s390x/skrf.c        | 128 ++++++++++++++++++++++++++++++++++++++++++++
 5 files changed, 205 insertions(+), 66 deletions(-)
 create mode 100644 s390x/skrf.c
Tested-by: Thomas Huth <thuth@redhat.com>
```
#### [kvm-unit-tests RFC PATCH 00/16] arm64: Run at EL2
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Wed Aug 28 13:38:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11119131
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8DC6014F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 13:38:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 76CE520828
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 13:38:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726395AbfH1Niv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 09:38:51 -0400
Received: from foss.arm.com ([217.140.110.172]:59500 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726197AbfH1Niv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 09:38:51 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 14E4628;
        Wed, 28 Aug 2019 06:38:50 -0700 (PDT)
Received: from e121566-lin.cambridge.arm.com (e121566-lin.cambridge.arm.com
 [10.1.196.217])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 E8D313F246;
        Wed, 28 Aug 2019 06:38:48 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, rkrcmar@redhat.com,
        maz@kernel.org, vladimir.murzin@arm.com, andre.przywara@arm.com
Subject: [kvm-unit-tests RFC PATCH 00/16] arm64: Run at EL2
Date: Wed, 28 Aug 2019 14:38:15 +0100
Message-Id: <1566999511-24916-1-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

ARMv8.3 added support for nested virtualization, which makes it possible
for a hypervisor to run another hypervisor as a guest. Support for nested
virtualization is being worked on in KVM [1].

This patch series aims to make it possible for kvm-unit-tests to run at EL2
under KVM. The focus has been on having all the infrastructure in place to
run at EL2, and not on adding comprehensive tests for this Exception Level.
All existing tests that fulfill KVM's requirements for a nested guest (the
architecture is arm64 and they use GICv3) will be able to be run at EL2.

To keep the changes minimal, kvm-unit-tests will run with VHE enabled when
it detects that has been booted at EL2. Functions for enabling and
disabling VHE have been added, with the aim to let the user specify to
disable VHE for a given test via command-line parameters. At the moment,
only the timer test has been modified to run with VHE disabled.

The series are firmly an RFC because:
* The patches that implement KVM nested support are themselves in the RFC
  phase.
* Some tests don't complete because of bugs in the current version of the
  KVM patches. Where appropriate, I will provide fixes to allow the tests
  to finish, however those fixes are my own have not been reviewed in any
  way. Use at your own risk.

To run the tests, one obviously needs KVM with nested virtualization
support from [2]. These patches have been tested from commit
78c66132035c ("arm64: KVM: nv: Allow userspace to request
KVM_ARM_VCPU_NESTED_VIRT"), on top of which the following patches have been
cherry-picked from upstream Linux:
* b4a1583abc83 ("KVM: arm/arm64: Fix emulated ptimer irq injection")
* 16e604a437c8 ("KVM: arm/arm64: vgic: Reevaluate level sensitive
  interrupts on enable")

Without those two patches some timer tests will fail.

A version of kvmtool that knows about nested virtualization is also
needed [3]. The kvmtool --nested parameter is required for releasing a
guest at EL2. For example, to run the newly added selftest-el2 test:

lkvm -f selftest.flat -c 2 -m 128 -p el2 --nested --console serial \
	--irqchip gicv3

Summary of the patches:
* Patches 1-10 are various fixes or enhancements and can be merged without
  the rest of the series.
* Patches 11-13 add support for running at EL2. A basic selftest-el2 test
  is added that targets EL2.
* Patches 14-16 add support for disabling VHE. The timer and selftest-el2
  tests are modified to use this feature.

[1] https://www.spinics.net/lists/arm-kernel/msg736687.html
[2] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-wip-5.2-rc5
[3] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5

Alexandru Elisei (16):
  arm: selftest.c: Remove redundant check for Exception Level
  arm/arm64: psci: Don't run C code without stack or vectors
  lib: arm/arm64: Add missing include for alloc_page.h in pgtable.h
  arm/arm64: selftest: Add prefetch abort test
  arm64: timer: Write to ICENABLER to disable timer IRQ
  arm64: timer: EOIR the interrupt after masking the timer
  arm64: timer: Test behavior when timer disabled or masked
  lib: arm/arm64: Refuse to disable the MMU with non-identity stack
    pointer
  lib: arm/arm64: Invalidate TLB before enabling MMU
  lib: Add UL and ULL definitions to linux/const.h
  lib: arm64: Run existing tests at EL2
  arm64: timer: Add test for EL2 timers
  arm64: selftest: Add basic test for EL2
  lib: arm64: Add support for disabling and re-enabling VHE
  arm64: selftest: Expand EL2 test to disable and re-enable VHE
  arm64: timer: Run tests with VHE disabled

 lib/linux/const.h             |   7 +-
 lib/arm/asm/gic-v3.h          |   1 +
 lib/arm/asm/gic.h             |   1 +
 lib/arm/asm/pgtable.h         |   1 +
 lib/arm/asm/processor.h       |   8 +
 lib/arm/asm/psci.h            |   1 +
 lib/arm64/asm/esr.h           |   5 +
 lib/arm64/asm/mmu.h           |  11 +-
 lib/arm64/asm/pgtable-hwdef.h |  55 +++++--
 lib/arm64/asm/pgtable.h       |   1 +
 lib/arm64/asm/processor.h     |  53 +++++++
 lib/arm64/asm/sysreg.h        |  28 ++++
 lib/arm/mmu.c                 |   5 +-
 lib/arm/processor.c           |  11 ++
 lib/arm/psci.c                |  43 +++++-
 lib/arm/setup.c               |   6 +
 lib/arm64/processor.c         |  69 ++++++++-
 arm/cstart.S                  |  11 ++
 arm/cstart64.S                | 221 ++++++++++++++++++++++++++-
 arm/micro-bench.c             |  17 ++-
 arm/psci.c                    |   5 +-
 arm/selftest.c                | 175 ++++++++++++++++++++--
 arm/timer.c                   | 340 +++++++++++++++++++++++++++++++++++++-----
 arm/unittests.cfg             |   8 +
 24 files changed, 1010 insertions(+), 73 deletions(-)
```
#### [PATCH v2 0/3] fix emulation error on Windows bootup
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
From patchwork Wed Aug 28 17:02:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11119489
Return-Path: <SRS0=KojS=WY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 258BC14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:03:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ED32B2339E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 28 Aug 2019 17:03:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="t4Tflww+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726583AbfH1RC6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 13:02:58 -0400
Received: from mail-eopbgr140095.outbound.protection.outlook.com
 ([40.107.14.95]:48192
        "EHLO EUR01-VE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726415AbfH1RC5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 13:02:57 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Knncb2YGp6rFvcdaawkryp+agerdZcF18Dl5W/D4nBUC3YAe7HYI4wroIxD1FO8Rqgu/cH0J7Rt5vDDuE8uMfOpIg1FutT3RiMU81MrzKa8CVXOYAVCml7EuY5iC9memyy59p4QTrZTTNbmGOvBaa7o6eVqpWBcuwUPKDfbsBaK0wcFdZWvsi2lwpLIDw8u7zmOm8scmgYLDRmec2u1MWPQEYQOLKe6ePve9qQbszkS9xQ1+UjgpRtrLHTD/V+2oqCKmeICbf2+AS9WnVpRl3fbNer5/QqonMBQQfXwVg/1x/kuKNOnypFYqCkjV0CiG66qz43o1jdvyWHzqBRWr3Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=myWY8g9AcvfNu6dTIgirU2weQVxzebMvrt7vFKAVqN8=;
 b=K9Kdb36XGBVnu7GCpYci+OEwCkKEreTZnqts7ptOZvPc07piIeIHpbBdagG9Dmfw71ic9GFFrcyg7F+9hYD84mWy251J5ih1vHmtneyoY+PYwf7dVNw2JU7GKije7OD+JSSSXSu0fMHk13Hr8VLpxsb33WB4i+NgDPDWKME34Lb2BYrPKvFUc1XHweFoCbv4Gm+DyXKDYadP+ISRtzvcZXV8wa3sVDwcfQ+nDjRu/KrTlZZKKaTYUYHmy7THmNigl8Eu53qaExr7BabpvmX+Qy2vzBNo07wC6e5JgnDdvV2fvhRSzSGawFvhwGwItlhI/XBrVIww3+WGP8pY/Ckdsg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=myWY8g9AcvfNu6dTIgirU2weQVxzebMvrt7vFKAVqN8=;
 b=t4Tflww+IlKSAoWnRrSKLe+hHs/oDBwsaGcCjQodWO6mtkZn98SMAKrIlmg6hWNKUCzx2nKdVy6fnZYfrePbbIql68gEshwgEuH0SzG/MJLWcMrMbme2wNAFJDsoRNAjdrBV7x9AqMKGdYoilnBb65FSLbv/eleK8HkMImF8I4k=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3181.eurprd08.prod.outlook.com (52.133.15.144) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.19; Wed, 28 Aug 2019 17:02:53 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Wed, 28 Aug 2019
 17:02:53 +0000
From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
To: "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: Jan Dakinevich <jan.dakinevich@virtuozzo.com>,
 Denis Lunev <den@virtuozzo.com>, Roman Kagan <rkagan@virtuozzo.com>,
 Denis Plotnikov <dplotnikov@virtuozzo.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?iso-8859-2?q?Radim_Kr=E8m=E1=F8?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Thomas Gleixner <tglx@linutronix.de>, Ingo Molnar <mingo@redhat.com>,
 Borislav Petkov <bp@alien8.de>, "H. Peter Anvin" <hpa@zytor.com>,
 "x86@kernel.org" <x86@kernel.org>,
 "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Subject: [PATCH v2 0/3] fix emulation error on Windows bootup
Thread-Topic: [PATCH v2 0/3] fix emulation error on Windows bootup
Thread-Index: AQHVXcJt7Trak7Eg4E+dkRqxYyQrAg==
Date: Wed, 28 Aug 2019 17:02:52 +0000
Message-ID: <1567011759-9969-1-git-send-email-jan.dakinevich@virtuozzo.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: HE1PR05CA0154.eurprd05.prod.outlook.com
 (2603:10a6:7:28::41) To VI1PR08MB2782.eurprd08.prod.outlook.com
 (2603:10a6:802:19::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=jan.dakinevich@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.1.4
x-originating-ip: [185.231.240.5]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 2962f05b-6e34-4746-f882-08d72bd99058
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(2017052603328)(7193020);SRVR:VI1PR08MB3181;
x-ms-traffictypediagnostic: VI1PR08MB3181:
x-ms-exchange-purlcount: 1
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB3181E67F2E4DBE1B129C3BB58AA30@VI1PR08MB3181.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:8273;
x-forefront-prvs: 014304E855
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(376002)(366004)(346002)(39850400004)(136003)(396003)(189003)(199004)(478600001)(26005)(4326008)(8936002)(186003)(102836004)(3846002)(256004)(476003)(44832011)(6486002)(66066001)(6512007)(305945005)(2906002)(2501003)(86362001)(6436002)(6116002)(66446008)(8676002)(66946007)(966005)(64756008)(66556008)(66476007)(316002)(7736002)(81156014)(52116002)(25786009)(81166006)(71190400001)(71200400001)(6506007)(486006)(386003)(14454004)(53936002)(99286004)(2616005)(5660300002)(6916009)(2351001)(54906003)(5640700003)(36756003)(6306002)(50226002)(7416002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3181;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 21WDfx4epCOmOonbGEuydhJUzYXUkuFmmNJwodILZGSk45HcS1WNwfPGgJvuOq/zzmg0WsS+ykBZMQnqY/fZLB6PZ0kUBe5NoUTNlv00An6zRlImMBRW2SYpgEOrz9K/hi4jTpwqwm3MkGyofhhVLzJ1nh05Y1jKNGdIlrFUFRE7vfVIgIFXSsIc/1QC98nOTZ4AY9zC+DE3V3SU2a3mTtiYrp3gC70i+2dMDUYq/U4xQaHcSwFc8rHKDgriL/Fwcb7FIdeonzJgBkNpAm99k8+Hle/GKp9deLJW96f6T9+hrrY7wZNfpEfAJvggMPpMXpvDqwAchJ3yAAVyBh1tC0qUxt0CECWrQjilha07KJ+2aIwJXBrVzwsmeqW/UZ05TiJK31nWkfEeTvvSD2QUJlEGpAZq28rar3ggiBsrykw=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 2962f05b-6e34-4746-f882-08d72bd99058
X-MS-Exchange-CrossTenant-originalarrivaltime: 28 Aug 2019 17:02:53.1128
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 POViCxvypt4B415UZXJeNOZ9/xUg8bkP0RA4CThLLT02RtWw9k69UP9uM50yzkiJM+5Oe7H68SWx1JwtaoIWbAmfb2tCQCYAtAjSm1e3EkA=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3181
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intended to fix (again) a bug that was a subject of the 
following change:

  6ea6e84 ("KVM: x86: inject exceptions produced by x86_decode_insn")

Suddenly, that fix had a couple mistakes. First, ctxt->have_exception was 
not set if fault happened during instruction decoding. Second, returning 
value of inject_emulated_instruction was used to make the decision to 
reenter guest, but this could happen iff on nested page fault, that is not 
the scope where this bug could occur.

v1:
  https://lkml.org/lkml/2019/8/27/881

v2
  - reorder commits, rebase on top kvm/queue
  - add sanity check for exception value of exception vector

Jan Dakinevich (3):
  KVM: x86: always stop emulation on page fault
  KVM: x86: make exception_class() and exception_type() globally visible
  KVM: x86: set ctxt->have_exception in x86_decode_insn()

 arch/x86/kvm/emulate.c |  5 +++++
 arch/x86/kvm/x86.c     | 50 +++-----------------------------------------------
 arch/x86/kvm/x86.h     | 46 ++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 54 insertions(+), 47 deletions(-)
```
