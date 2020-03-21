

#### [PATCH v10 0/8] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Mar 20 03:43:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11448379
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E75592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:41:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 295D42072D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 03:41:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726997AbgCTDkm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Mar 2020 23:40:42 -0400
Received: from mga01.intel.com ([192.55.52.88]:27908 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726614AbgCTDkm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Mar 2020 23:40:42 -0400
IronPort-SDR: 
 7KSMsZgXzrPUUMEW0z6kE78lrGpk3/r93bQFKXtvSYWbzIKsgCIT0xM7rJbGeyDg7g1dP9d0c1
 i1IGmxDcC9jg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2020 20:40:42 -0700
IronPort-SDR: 
 QdwArEsOoB/Ag/uHojP3s7h4UiV+1GVnKhjAA7Wm56Cafh3OhD9eCYzlEWJZbVK580A2lqPwAX
 bnHOW1v6dIkA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,283,1580803200";
   d="scan'208";a="263945572"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by orsmga002.jf.intel.com with ESMTP; 19 Mar 2020 20:40:39 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        sean.j.christopherson@intel.com, pbonzini@redhat.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v10 0/8] Introduce support for guest CET feature
Date: Fri, 20 Mar 2020 11:43:33 +0800
Message-Id: <20200320034342.26610-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM needs to update to enable guest CET feature.
This patchset implements CET related CPUID/XSAVES enumeration, MSRs
and vmentry/vmexit configuration etc.so that guest kernel can setup CET
runtime infrastructure based on them. Some CET MSRs and related feature
flags used reference the definitions in kernel patchset.

CET kernel patches are here:
https://lkml.org/lkml/2020/2/5/593
https://lkml.org/lkml/2020/2/5/604

v9 -> v10
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v8 -> v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v7 -> v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v6 -> v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v5 -> v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v4 -> v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v3 -> v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v2 -> v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v1 -> v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.

Sean Christopherson (1):
  KVM: X86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (7):
  KVM: VMX: Introduce CET VMX fields and flags
  KVM: VMX: Set up guest CET MSRs per KVM and host configuration
  KVM: VMX: Load CET states on vmentry/vmexit
  KVM: X86: Refresh CPUID on guest XSS change
  KVM: X86: Add userspace access interface for CET MSRs
  KVM: VMX: Enable CET support for nested VM
  KVM: X86: Set CET feature bits for CPUID enumeration

 arch/x86/include/asm/kvm_host.h |   3 +-
 arch/x86/include/asm/vmx.h      |   8 ++
 arch/x86/include/uapi/asm/kvm.h |   1 +
 arch/x86/kvm/cpuid.c            |  22 +++-
 arch/x86/kvm/vmx/capabilities.h |  10 ++
 arch/x86/kvm/vmx/nested.c       |  41 ++++++-
 arch/x86/kvm/vmx/vmcs12.c       |   6 +
 arch/x86/kvm/vmx/vmcs12.h       |  14 ++-
 arch/x86/kvm/vmx/vmx.c          | 202 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  44 ++++++-
 arch/x86/kvm/x86.h              |   2 +-
 11 files changed, 341 insertions(+), 12 deletions(-)
```
#### [kvm-unit-tests PATCH v7 00/13] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Mar 20 09:24:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11448711
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 923191392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 09:24:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7094F20775
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 09:24:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cDtHJOwd"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726878AbgCTJYs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 05:24:48 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:32257 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726791AbgCTJYr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 05:24:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584696285;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IeMxV+nJyYzaQLc3wwNQ9aEwBnBicqgUTnOCjDW6Sxo=;
        b=cDtHJOwdBSE+u1up9vDsINoYWQPnaF5lsTsjXGRsYWS1Wk0R0sHsv1EGA7UYj2Nb4NyEy7
        cer4cZJT2G0Mk97mnh6M4ho9+zBBMFEz2fWrP7tkb4/fs0P0+qpbTXwiXHm4zP7k9AiCyW
        owaex6uRxBgTGzqSQUvxlEgppl+lmtw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-451-MnieVj2aM-qS15lDWykShA-1; Fri, 20 Mar 2020 05:24:41 -0400
X-MC-Unique: MnieVj2aM-qS15lDWykShA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A75451083E80;
        Fri, 20 Mar 2020 09:24:39 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A84B45C1D8;
        Fri, 20 Mar 2020 09:24:32 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v7 00/13] arm/arm64: Add ITS tests
Date: Fri, 20 Mar 2020 10:24:15 +0100
Message-Id: <20200320092428.20880-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found related
to the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

The series can be fount at:
https://github.com/eauger/kut/tree/its-v7

Applies on top of arm/queue.

Best Regards

Eric

History:
v6 -> v7:
- Fixed issue reported by Drew in its-migrate-unmapped-collection (a collection
  could be allocated twice depending on the SMP value)
- Integrated changes prepared by Drew
- Use for_each_present_cpu()

v5 -> v6:
- Took into account Zenghui's comments, mostly functional: see invidual
  history logs
- fix wrong assert!

v4 -> v5:
- 32b stubs moved back to arm/gic.c
- some changes reordering
- minor style issues

v3 -> v4:
- addressed comments from Drew and Zenghui
- added "page_alloc: Introduce get_order()"
- removed "arm: gic: Provide per-IRQ helper functions"
- ITS files moved to lib64
- and many more, see individual logs

v2 -> v3:
- fix 32b compilation
- take into account Drew's comments (see individual diff logs)

v1 -> v2:
- took into account Zenghui's comments
- collect R-b's from Thomas

References:
[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

Execution:
x For other ITS tests:
  ./run_tests.sh -g its

x non migration tests can be launched invidually. For instance:
  ./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

x also tests can be compiled in standalone mode with
  "make standalone" and tests (even migration ones) can also be
  launched that way, for instance:
  MAX_SMP=4 tests/its-migrate-unmapped-collection

Eric Auger (13):
  libcflat: Add other size defines
  page_alloc: Introduce get_order()
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: gicv3: Set the LPI config and pending tables
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: Commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.arm64         |   1 +
 arm/Makefile.common        |   2 +-
 arm/gic.c                  | 460 ++++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  38 +++
 lib/alloc_page.c           |   7 +-
 lib/alloc_page.h           |   1 +
 lib/arm/asm/gic-v3-its.h   |  27 +++
 lib/arm/asm/gic-v3.h       |  29 +++
 lib/arm/asm/gic.h          |   1 +
 lib/arm/asm/processor.h    |   2 +
 lib/arm/gic-v3.c           |  78 +++++++
 lib/arm/gic.c              |  40 +++-
 lib/arm/io.c               |  28 +++
 lib/arm64/asm/gic-v3-its.h | 174 ++++++++++++++
 lib/arm64/gic-v3-its-cmd.c | 463 +++++++++++++++++++++++++++++++++++++
 lib/arm64/gic-v3-its.c     | 171 ++++++++++++++
 lib/libcflat.h             |   3 +
 18 files changed, 1496 insertions(+), 31 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm64/asm/gic-v3-its.h
 create mode 100644 lib/arm64/gic-v3-its-cmd.c
 create mode 100644 lib/arm64/gic-v3-its.c
```
#### [kvm-unit-tests PATCH 0/2] Add support of hvf accel
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id 1jBDfE4814zS; Fri, 20 Mar 2020 17:57:07 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 20A46412E8;
        Fri, 20 Mar 2020 17:57:07 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Fri, 20
 Mar 2020 17:57:07 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Cameron Esfahani <dirty@apple.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH 0/2] Add support of hvf accel
Date: Fri, 20 Mar 2020 17:55:39 +0300
Message-ID: <20200320145541.38578-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

HVF is a para-virtualized QEMU accelerator for macOS based on                                                                                                                 Hypervisor.framework (HVF). Hypervisor.framework is a thin user-space                                                                                                         wrapper around Intel VT/VMX that enables to run VMMs such as QEMU in                                                                                                          non-privileged mode.                                                                                                                                                                                                                                                                                                                                        The unit tests can be run on macOS to verify completeness of the HVF                                                                                                          accel implementation.

Roman Bolshakov (2):
  scripts/arch-run: Support testing of hvf accel
  README: Document steps to run the tests on macOS

 README.macOS.md       | 47 +++++++++++++++++++++++++++++++++++++++++++
 README.md             |  6 ++++--
 scripts/arch-run.bash | 13 ++++++++++++
 3 files changed, 64 insertions(+), 2 deletions(-)
 create mode 100644 README.macOS.md
```
#### [PATCH v10 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Mar 20 16:09:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11449723
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 705011667
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:09:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F44420753
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:09:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YBPEX9OE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727417AbgCTQJy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 12:09:54 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:32838 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727092AbgCTQJy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 12:09:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584720592;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mt6W53kP88DRiZTuoqb3J/Hxj12DaCnXpHIxP03GIz0=;
        b=YBPEX9OEmnYL/9bYWF1ElLnDFbSXSn6e/XS5i/g1RjdcBQ2XCcEmP0snCG8S18VnUEUEIW
        L18DbfFFYtDjgQT6awiK5FwVV0xy+lPENLADL5nCQF0NbMqJiY7NV2FHLi8u2KTYtwOgMs
        b0Nx5itKJ/j8U8Ad3m0+4w6NMOdQ9Ms=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-433-8p6GmzW8PH6jK-84OtJ-OQ-1; Fri, 20 Mar 2020 12:09:49 -0400
X-MC-Unique: 8p6GmzW8PH6jK-84OtJ-OQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7EA8B100550E;
        Fri, 20 Mar 2020 16:09:46 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 742A45C1D8;
        Fri, 20 Mar 2020 16:09:37 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, joro@8bytes.org,
        alex.williamson@redhat.com, jacob.jun.pan@linux.intel.com,
        yi.l.liu@intel.com, jean-philippe.brucker@arm.com,
        will.deacon@arm.com, robin.murphy@arm.com
Cc: marc.zyngier@arm.com, peter.maydell@linaro.org,
        zhangfei.gao@gmail.com
Subject: [PATCH v10 00/13] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Fri, 20 Mar 2020 17:09:19 +0100
Message-Id: <20200320160932.27222-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a rebase on top of Will's arm-smmu-updates branch
(git://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git tags/arm-smmu-updates)

This work has been stalled since Plumber 2019. Since then
some users expressed interest in that work and tested v9:
- https://patchwork.kernel.org/cover/11039995/#23012381
- https://patchwork.kernel.org/cover/11039995/#23197235

The VFIO series is sent separately.

Background:

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

The IOMMU API is extended to support 2 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/will-arm-smmu-updates-2stage-v10
(also includes the VFIO part)

History:

v9 -> v10:
- rebase on top of 5.6.0-rc3

v8 -> v9:
- rebase on 5.3
- split iommu/vfio parts

v6 -> v8:
- Implement VFIO-PCI device specific interrupt framework

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info

Eric Auger (11):
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Dynamically allocate s1_cfg and s2_cfg
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults

Jacob Pan (1):
  iommu: Introduce attach/detach_pasid_table API

Jean-Philippe Brucker (1):
  iommu/arm-smmu-v3: Maintain a SID->device structure

 drivers/iommu/arm-smmu-v3.c | 738 ++++++++++++++++++++++++++++++++----
 drivers/iommu/dma-iommu.c   | 142 ++++++-
 drivers/iommu/iommu.c       |  56 +++
 include/linux/dma-iommu.h   |  16 +
 include/linux/iommu.h       |  37 ++
 include/uapi/linux/iommu.h  |  51 +++
 6 files changed, 968 insertions(+), 72 deletions(-)
```
#### [PATCH v10 00/11] SMMUv3 Nested Stage Setup (VFIO part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Mar 20 16:19:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11449773
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A3D66CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:19:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 49A8820739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 16:19:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PoyNHGQu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727458AbgCTQTz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 12:19:55 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:46567 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726801AbgCTQTz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 20 Mar 2020 12:19:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584721193;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=S/DXlI3P2nbMXd69cOy84aTZ0SIJNFmNoyde3hKd4Ew=;
        b=PoyNHGQuN/KLNqgB+a6Z9qnaO3Nk/cWb+P+YLG/PyrpQGVdSB3gG8bbkyIAAEWfaKIy0b+
        8qgrU2OAPEj9wVo5A6ikcCTqYbjZxwdRsYcE47IQeULcSKhQBQzKGxJktNFxsFpkpUdxdS
        rhBqwQGG0jjIrZlHXhnWW+TJiPjHZSQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-126-g-dTOvKOMhqkiKp88uLICg-1; Fri, 20 Mar 2020 12:19:52 -0400
X-MC-Unique: g-dTOvKOMhqkiKp88uLICg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 44A79934C59;
        Fri, 20 Mar 2020 16:19:25 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-142.ams2.redhat.com
 [10.36.113.142])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 487BA60BFB;
        Fri, 20 Mar 2020 16:19:13 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, joro@8bytes.org,
        alex.williamson@redhat.com, jacob.jun.pan@linux.intel.com,
        yi.l.liu@intel.com, jean-philippe.brucker@arm.com,
        will.deacon@arm.com, robin.murphy@arm.com
Cc: marc.zyngier@arm.com, peter.maydell@linaro.org,
        zhangfei.gao@gmail.com
Subject: [PATCH v10 00/11] SMMUv3 Nested Stage Setup (VFIO part)
Date: Fri, 20 Mar 2020 17:19:00 +0100
Message-Id: <20200320161911.27494-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the VFIO part of HW nested paging support
in the SMMUv3.

This is a rebase on top of Will's arm-smmu-updates branch
(git://git.kernel.org/pub/scm/linux/kernel/git/will/linux.git tags/arm-smmu-updates)

This is basically a resend of v9 as patches still applied.

This work has been stalled since Plumber 2019. Since then
some users expressed interest in that work and tested v9:
- https://patchwork.kernel.org/cover/11039995/#23012381
- https://patchwork.kernel.org/cover/11039995/#23197235

The series depends on:
[PATCH v10 00/13] SMMUv3 Nested Stage Setup (IOMMU part)

3 new IOCTLs are introduced that allow the userspace to
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings
3) invalidate stage 1 related caches

They map onto the related new IOMMU API functions.

We introduce the capability to register specific interrupt
indexes (see [1]). A new DMA_FAULT interrupt index allows to register
an eventfd to be signaled whenever a stage 1 related fault
is detected at physical level. Also a specific region allows
to expose the fault records to the user space.

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/will-arm-smmu-updates-2stage-v10

It series includes Tina's patch steming from
[1] "[RFC PATCH v2 1/3] vfio: Use capability chains to handle device
specific irq" plus patches originally contributed by Yi.

History:

v9 -> v10
- rebase on top of 5.6.0-rc3 (no change versus v9)

v8 -> v9:
- introduce specific irq framework
- single fault region
- iommu_unregister_device_fault_handler failure case not handled
  yet.

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (8):
  vfio: VFIO_IOMMU_SET_MSI_BINDING
  vfio/pci: Add VFIO_REGION_TYPE_NESTED region type
  vfio/pci: Register an iommu fault handler
  vfio/pci: Allow to mmap the fault queue
  vfio: Add new IRQ for DMA fault reporting
  vfio/pci: Add framework for custom interrupt indices
  vfio/pci: Register and allow DMA FAULT IRQ signaling
  vfio: Document nested stage control

Liu, Yi L (2):
  vfio: VFIO_IOMMU_SET_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

Tina Zhang (1):
  vfio: Use capability chains to handle device specific irq

 Documentation/driver-api/vfio.rst   |  77 ++++++++
 drivers/vfio/pci/vfio_pci.c         | 283 ++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_intrs.c   |  62 ++++++
 drivers/vfio/pci/vfio_pci_private.h |  24 +++
 drivers/vfio/pci/vfio_pci_rdwr.c    |  45 +++++
 drivers/vfio/vfio_iommu_type1.c     | 166 ++++++++++++++++
 include/uapi/linux/vfio.h           | 109 ++++++++++-
 7 files changed, 747 insertions(+), 19 deletions(-)
```
#### [PATCH v9 0/6] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Fri Mar 20 17:28:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11449957
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A78CA6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:28:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8523120767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 17:28:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="bImwAdo4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727022AbgCTR2v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 13:28:51 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:44910 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbgCTR2v (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 13:28:51 -0400
Received: by mail-wr1-f66.google.com with SMTP id j14so623766wrb.11;
        Fri, 20 Mar 2020 10:28:49 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=dpvhqwRYw1qK6j1rjp4VmuYOJGPSPljg5Ewku7G0J+c=;
        b=bImwAdo43YjbEYIAW4e1v87x+01rV4kvnpJrmHuiDYu8guEawZVIIbEyBJpbl+i6XF
         qhBTlAoxUB2KVSPhLCgUEM3XXYaLWgQ37vqn9g8jlXLjYVZrJxxl2rTFm0e6aGkwXUEp
         u1vNNx5oTg+yLfHx6lEHLVXKOS5tveVA09o9S67yw26XWmYoW7w44mSYzhemhveyo93t
         w0jfLRZxuXNl/wuyLmH9Ode7HfhvagUZBcCz8oPnVlOpBXw4y6ol0gtgolFdTJhEg3dg
         Gj1eTv2AWgG1YzvE9GXGKyYvC/vlgh3PIvHskB6MbN0gSs8sF9YC1mu6IsfUIqsqNY/s
         qi0w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=dpvhqwRYw1qK6j1rjp4VmuYOJGPSPljg5Ewku7G0J+c=;
        b=e4foobh5YxJT0FG1x/15e6CPKMn04IxfFC/YvzYlVZgT6rT6QjHlHEPNSGFuGBIwI1
         nSJRWZGpgzTj1eGOzN6wxxK/ADIqwWN5El1h2QetaQDGe8BqtX3JqNL5ugqrpUq49794
         7gctlMaD6kugAOmcbJHnuXQMfUN5QBYDbnFHSb/Bczr6+mY/Qa3MkUaA+c+JsToabLaY
         oSlAs01L4YIPEDsw0JJ3gjm1tnJLUHOdJEBh1OFTD/N5pwEPMJvcvjvVzu53arB09ok7
         1uTFLdwcOODssmENf1wAE7FKBvoKta7+VvbW3YX4G5vcQohFasGrc8SqJxqDld+w9gbR
         3DNA==
X-Gm-Message-State: ANhLgQ2go1ZCIxnLu6SrFuD0BON8Of7YN6o5zffzVLhtteSXKmFohGkS
        ETX7xabCIo7lYBVXTJMNf3uThcxxBTk=
X-Google-Smtp-Source: 
 ADFU+vuqYqNrfEWDKPA1t64oIJcfbVFs/Kjhgs4cTypkOa67P8c/7QCwPUlNzRwkrqrOChHHuZKHKg==
X-Received: by 2002:adf:f309:: with SMTP id i9mr13332572wro.0.1584725328088;
        Fri, 20 Mar 2020 10:28:48 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 q4sm11028333wmj.1.2020.03.20.10.28.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 20 Mar 2020 10:28:47 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v9 0/6] x86/kvm/hyper-v: add support for synthetic debugger
Date: Fri, 20 Mar 2020 19:28:33 +0200
Message-Id: <20200320172839.1144395-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

Jon Doron (6):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/kvm/hyper-v: Simplify addition for custom cpuid leafs
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls without hypercall page with syndbg
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 Documentation/virt/kvm/api.rst     |  18 +++
 arch/x86/include/asm/hyperv-tlfs.h |   6 +
 arch/x86/include/asm/kvm_host.h    |  14 ++
 arch/x86/kvm/hyperv.c              | 235 +++++++++++++++++++++++++++--
 arch/x86/kvm/hyperv.h              |  33 ++++
 arch/x86/kvm/trace.h               |  51 +++++++
 arch/x86/kvm/x86.c                 |  13 ++
 include/uapi/linux/kvm.h           |  13 ++
 8 files changed, 368 insertions(+), 15 deletions(-)
```
#### [PATCH v6 00/23] irqchip/gic-v4: GICv4.1 architecture support
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Mar 20 18:23:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11450017
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B531513B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 18:25:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8C1B720782
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 18:25:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1584728730;
	bh=OjWX+qwHZ6kJjLfCNmQUx1QBDMRyFaiz20SBTxnP4VY=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=Q3myNDN/Mxm6vyuW7cqR0YudvvsPRT3lHQ027lak7mx/r0JC7Fzq00z8VrPP+OM7k
	 0GPVYDO+TkwsFjLK6ir63/7HmQBUA7+P4HLpljTLJsZPVGs86pG+PhJtbjHg3PYjff
	 8aRNKJbH96mxGg4ZaC9kpa+0h/Fjnq5jKCy1cBCU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727133AbgCTSYf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 14:24:35 -0400
Received: from mail.kernel.org ([198.145.29.99]:35630 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727070AbgCTSYf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 14:24:35 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id C4BFF20767;
        Fri, 20 Mar 2020 18:24:33 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1584728673;
        bh=OjWX+qwHZ6kJjLfCNmQUx1QBDMRyFaiz20SBTxnP4VY=;
        h=From:To:Cc:Subject:Date:From;
        b=AxQo+XSRfVNOtjYiVNPa9dIIogX1mu/9qfzW74IxW1pC7RhMbm0C5+X8c+w1hVSzE
         FUivaVM3+2TpCnpyDdGgiKnFGiOlPwNrbbKKOPsjKjzhHBkmpWn89R7i6xHf1N3p5p
         56OFSEOlR/L7NTWxvfs/vegxgadi/VP8yBejMHXQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jFMJs-00EKAx-4i; Fri, 20 Mar 2020 18:24:32 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Jason Cooper <jason@lakedaemon.net>,
        Thomas Gleixner <tglx@linutronix.de>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Eric Auger <eric.auger@redhat.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v6 00/23] irqchip/gic-v4: GICv4.1 architecture support
Date: Fri, 20 Mar 2020 18:23:43 +0000
Message-Id: <20200320182406.23465-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-kernel@vger.kernel.org, lorenzo.pieralisi@arm.com,
 jason@lakedaemon.net, tglx@linutronix.de, yuzenghui@huawei.com,
 eric.auger@redhat.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This (now shorter) series expands the existing GICv4 support to deal
with the new GICv4.1 architecture, which comes with a set of major
improvements compared to v4.0:

- One architectural doorbell per vcpu, instead of one doorbell per VLPI

- Doorbell entirely managed by the HW, with an "at most once" delivery
  guarantee per non-residency phase and only when requested by the
  hypervisor

- A shared memory scheme between ITSs and redistributors, allowing for an
  optimised residency sequence (the use of VMOVP becomes less frequent)

- Support for direct virtual SGI delivery (the injection path still involves
  the hypervisor), at the cost of losing the active state on SGIs. It
  shouldn't be a big deal, but some guest operating systems might notice
  (Linux definitely won't care).

Some documentation is now available [0] in the IHI0069F documentation
from ARM (although still not final).

The series is roughly organised in 3 parts:

(0) Fixes
(1) v4.1 doorbell management
(2) Virtual SGI support
(3) Plumbing of virtual SGIs in KVM

Notes:

  - The whole thing is tested on a FVP model, which can be obtained
    free of charge on ARM's developer website. It requires you to
    create an account, unfortunately...

  - This series has uncovered a behaviour that looks like a HW bug on
    the Cavium ThunderX (aka TX1) platform. The fix for this is now
    in mainline (d01fd161e859).

  - I'm extremely grateful for Zenghui Yu's huge effort in carefully
    reviewing this rather difficult series (if we ever get to meet
    face to face, drinks are definitely on me!).

  - Thanks to Eric Auger for having joined the fun and spotted a
    number of funky things!

  - This is now left to brew in -next. Any issue will be fixed by
    addtional patches.

* From v5 [5]
  - Fixed VMOVP not being issued on systems that are not single-VMOVP
    capable
  - Propagated error on irq_get_irqchip_state() failure for vSGIs
  - vSGI pending state is now get reported to userspace
  - Restoring a GICD_TYPER2 value that doesn't match what KVM can offer
    because nASSGIcap is different results in a failure
  - Fixed locking on switch between SGI implementations
  - Added more comments where required to clarify the behaviour of
    some of the most nebulous parts

* From v4 [4]
  - Rebased on v5.6-rc4
  - Fixed locking all over the shop now that we can bypass the ITS
  - Wait on INVALL at the RD level
  - Plentu of cleanups/fixes thanks to Zenghui's careful review effort

* From v3 [3]:
  - Rebased on v5.6-rc1
  - Considerably smaller thanks to the initial patches being merged
  - Small bug fix after the v5.6 merge window

* From v2 [2]:
  - Another bunch of fixes thanks to Zenghui Yu's very careful review
  - HW-accelerated SGIs are now optional thanks to new architected
    discovery/selection bits exposed by KVM and used by the guest kernel
  - Rebased on v5.5-rc2

* From v1 [1]:
  - A bunch of minor reworks after Zenghui Yu's review
  - A workaround for what looks like a new and unexpected TX1 bug
  - A subtle reorder of the series so that some patches can go in early

[0] https://static.docs.arm.com/ihi0069/f/IHI0069F_gic_architecture_specification_v3_and_v4.1.pdf
[1] https://lore.kernel.org/lkml/20190923182606.32100-1-maz@kernel.org/
[2] https://lore.kernel.org/lkml/20191027144234.8395-1-maz@kernel.org/
[3] https://lore.kernel.org/r/20191224111055.11836-1-maz@kernel.org/
[4] https://lore.kernel.org/r/20200214145736.18550-1-maz@kernel.org/
[5] https://lore.kernel.org/r/20200304203330.4967-1-maz@kernel.org/

Marc Zyngier (22):
  irqchip/gic-v3: Use SGIs without active state if offered
  irqchip/gic-v4.1: Skip absent CPUs while iterating over redistributors
  irqchip/gic-v4.1: Ensure mutual exclusion between vPE affinity change
    and RD access
  irqchip/gic-v4.1: Ensure mutual exclusion betwen invalidations on the
    same RD
  irqchip/gic-v4.1: Advertise support v4.1 to KVM
  irqchip/gic-v4.1: Map the ITS SGIR register page
  irqchip/gic-v4.1: Plumb skeletal VSGI irqchip
  irqchip/gic-v4.1: Add initial SGI configuration
  irqchip/gic-v4.1: Plumb mask/unmask SGI callbacks
  irqchip/gic-v4.1: Plumb get/set_irqchip_state SGI callbacks
  irqchip/gic-v4.1: Plumb set_vcpu_affinity SGI callbacks
  irqchip/gic-v4.1: Move doorbell management to the GICv4 abstraction
    layer
  irqchip/gic-v4.1: Add VSGI allocation/teardown
  irqchip/gic-v4.1: Add VSGI property setup
  irqchip/gic-v4.1: Eagerly vmap vPEs
  KVM: arm64: GICv4.1: Let doorbells be auto-enabled
  KVM: arm64: GICv4.1: Add direct injection capability to SGI registers
  KVM: arm64: GICv4.1: Allow SGIs to switch between HW and SW interrupts
  KVM: arm64: GICv4.1: Plumb SGI implementation selection in the
    distributor
  KVM: arm64: GICv4.1: Reload VLPI configuration on distributor
    enable/disable
  KVM: arm64: GICv4.1: Allow non-trapping WFI when using HW SGIs
  KVM: arm64: GICv4.1: Expose HW-based SGIs in debugfs

Zenghui Yu (1):
  irqchip/gic-v4.1: Wait for completion of redistributor's INVALL
    operation

 arch/arm/include/asm/kvm_host.h        |   1 +
 arch/arm64/include/asm/kvm_emulate.h   |   3 +-
 arch/arm64/include/asm/kvm_host.h      |   1 +
 drivers/irqchip/irq-gic-v3-its.c       | 422 +++++++++++++++++++++++--
 drivers/irqchip/irq-gic-v3.c           |  13 +-
 drivers/irqchip/irq-gic-v4.c           | 134 +++++++-
 include/kvm/arm_vgic.h                 |   4 +
 include/linux/irqchip/arm-gic-common.h |   2 +
 include/linux/irqchip/arm-gic-v3.h     |  20 +-
 include/linux/irqchip/arm-gic-v4.h     |  25 +-
 virt/kvm/arm/arm.c                     |   8 +
 virt/kvm/arm/vgic/vgic-debug.c         |  14 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c       |  81 ++++-
 virt/kvm/arm/vgic/vgic-mmio.c          |  88 +++++-
 virt/kvm/arm/vgic/vgic-v3.c            |   6 +-
 virt/kvm/arm/vgic/vgic-v4.c            | 141 +++++++--
 virt/kvm/arm/vgic/vgic.h               |   1 +
 17 files changed, 895 insertions(+), 69 deletions(-)
```
#### [PATCH 0/7] KVM: Fix memslot use-after-free bug
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Mar 20 20:55:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11450359
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9171C13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 20:56:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 71F8E20782
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 20:56:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727141AbgCTUzs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 16:55:48 -0400
Received: from mga11.intel.com ([192.55.52.93]:32133 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726738AbgCTUzr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 16:55:47 -0400
IronPort-SDR: 
 Mrtax5r6S7je/QHfg4sI2au75xzgLMcQ/DAQsUZy12gjghMc7G+ERsPFcTQ1PdU++ln95lU7Uf
 gZNnPWKTVK8A==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Mar 2020 13:55:47 -0700
IronPort-SDR: 
 Wokbp1xezwQOg04lztcVSu+PjFiTzDPfBLqx5B6LgK3OObVC7Tz3rYthmd8sfETKC33SiH7a3o
 +AAl+xhNCOJg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,285,1580803200";
   d="scan'208";a="280543314"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 20 Mar 2020 13:55:47 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Qian Cai <cai@lca.pw>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH 0/7] KVM: Fix memslot use-after-free bug
Date: Fri, 20 Mar 2020 13:55:39 -0700
Message-Id: <20200320205546.2396-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a bug introduced by dynamic memslot allocation where the LRU slot can
become invalid and lead to a out-of-bounds/use-after-free scenario.

The patch is different that what Qian has already tested, but I was able
to reproduce the bad behavior by enhancing the set memory region selftest,
i.e. I'm relatively confident the bug is fixed.

Patches 2-6 are a variety of selftest cleanup, with the aforementioned
set memory region enhancement coming in patch 7.

Note, I couldn't get the selftest to fail outright or with KASAN, but was
able to hit a WARN_ON an invalid slot 100% of the time (without the fix,
obviously).

Regarding s390, I played around a bit with merging gfn_to_memslot_approx()
into search_memslots().  Code wise it's trivial since they're basically
identical, but doing so increases the code footprint of search_memslots()
on x86 by 30 bytes, so I ended up abandoning the effort.

Sean Christopherson (7):
  KVM: Fix out of range accesses to memslots
  KVM: selftests: Fix cosmetic copy-paste error in vm_mem_region_move()
  KVM: selftests: Take vcpu pointer instead of id in vm_vcpu_rm()
  KVM: selftests: Add helpers to consolidate open coded list operations
  KVM: selftests: Add util to delete memory region
  KVM: selftests: Expose the primary memslot number to tests
  KVM: selftests: Add "delete" testcase to set_memory_region_test

 arch/s390/kvm/kvm-s390.c                      |   3 +
 include/linux/kvm_host.h                      |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 139 ++++++++++--------
 .../kvm/x86_64/set_memory_region_test.c       | 122 +++++++++++++--
 virt/kvm/kvm_main.c                           |   3 +
 6 files changed, 201 insertions(+), 72 deletions(-)
```
#### [PATCH v3 00/37] KVM: x86: TLB flushing fixes and enhancements
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Mar 20 21:27:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11450463
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65DCF92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 21:31:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4FA9020767
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 21:31:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726955AbgCTV2n (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 17:28:43 -0400
Received: from mga01.intel.com ([192.55.52.88]:48422 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726666AbgCTV2n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 17:28:43 -0400
IronPort-SDR: 
 GU+Q+QeM5AKetiqrihQwQXv2HpmM/C3sog9g2UTTYoPrLvZyNSzMpo6PoAccwxsQkljQhBJudl
 HFqSc1LIdJ2w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 20 Mar 2020 14:28:42 -0700
IronPort-SDR: 
 FG4X1vP1tOia9kFijfJtEYk1fqaXP7us9tlN+/O9DXilhz36QnPgodZEp9c7fjA/O52xXnqpU9
 YUw1Abe4ILFg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,286,1580803200";
   d="scan'208";a="269224390"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga004.fm.intel.com with ESMTP; 20 Mar 2020 14:28:42 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Ben Gardon <bgardon@google.com>,
        Junaid Shahid <junaids@google.com>,
        Liran Alon <liran.alon@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        John Haxby <john.haxby@oracle.com>,
        Miaohe Lin <linmiaohe@huawei.com>,
        Tom Lendacky <thomas.lendacky@amd.com>
Subject: [PATCH v3 00/37] KVM: x86: TLB flushing fixes and enhancements
Date: Fri, 20 Mar 2020 14:27:56 -0700
Message-Id: <20200320212833.3507-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

VMX TLB flushing cleanup series to fix a variety of bugs, and to avoid
unnecessary TLB flushes on nested VMX transitions.

  1) Nested VMX doesn't properly flush all ASIDs/contexts on system events,
     e.g. on mmu_notifier invalidate all contexts for L1 *and* L2 need to
     be invalidated, but KVM generally only flushes L1 or L2 (or just L1).

  2) #1 is largely benign because nested VMX always flushes the new
     context on nested VM-Entry/VM-Exit.

High level overview:

  a) Fix the main TLB flushing bug with a big hammer.

  b) Fix a few other flushing related bugs.

  c) Clean up vmx_tlb_flush(), i.e. what was v1 of this series.

  d) Reintroduce current-ASID/context flushing to regain some of the
     precision that got blasted away by the big hammer in #1.

  e) Fix random code paths that unnecessarily trigger TLB flushes on
     nested VMX transitions.

  f) Stop flushing on every nested VMX transition.

  g) Extra cleanup.


v3:
  - Fix freeing of roots during INVVPID, I botched things when tweaking
    Junaid's original patch.
  - Move "last vpid02" logic into nested VMX flushing helper. [Paolo]
  - Split "skip tlb flush" and "skip mmu sync" logic during fast roots
    switch. [Paolo]
  - Unconditionally skip tlb flush during fast roots switch on nested VMX
    transitions, i.e. let nested_vmx_transition_tlb_flush() do the work.
    This avoids flushing when EPT=0 and VPID=1. [Paolo]
  - Do more cr3->pgd conversions in related code that drove me bonkers
    when trying to figure out what was broken with VPID.  I think this
    knocks off the last code that uses "cr3" for variables/functions that
    work with cr3 or eptp.

v2:
  - Basically a new series.

v1:
  - https://patchwork.kernel.org/cover/11394987/

Junaid Shahid (2):
  KVM: nVMX: Invalidate all roots when emulating INVVPID without EPT
  KVM: x86: Sync SPTEs when injecting page/EPT fault into L1

Sean Christopherson (35):
  KVM: VMX: Flush all EPTP/VPID contexts on remote TLB flush
  KVM: nVMX: Validate the EPTP when emulating INVEPT(EXTENT_CONTEXT)
  KVM: nVMX: Invalidate all EPTP contexts when emulating INVEPT for L1
  KVM: x86: Export kvm_propagate_fault() (as
    kvm_inject_emulated_page_fault)
  KVM: x86: Consolidate logic for injecting page faults to L1
  KVM: VMX: Skip global INVVPID fallback if vpid==0 in
    vpid_sync_context()
  KVM: VMX: Use vpid_sync_context() directly when possible
  KVM: VMX: Move vpid_sync_vcpu_addr() down a few lines
  KVM: VMX: Handle INVVPID fallback logic in vpid_sync_vcpu_addr()
  KVM: VMX: Drop redundant capability checks in low level INVVPID
    helpers
  KVM: nVMX: Use vpid_sync_vcpu_addr() to emulate INVVPID with address
  KVM: x86: Move "flush guest's TLB" logic to separate kvm_x86_ops hook
  KVM: VMX: Clean up vmx_flush_tlb_gva()
  KVM: x86: Drop @invalidate_gpa param from kvm_x86_ops' tlb_flush()
  KVM: SVM: Wire up ->tlb_flush_guest() directly to svm_flush_tlb()
  KVM: VMX: Move vmx_flush_tlb() to vmx.c
  KVM: nVMX: Move nested_get_vpid02() to vmx/nested.h
  KVM: VMX: Introduce vmx_flush_tlb_current()
  KVM: SVM: Document the ASID logic in svm_flush_tlb()
  KVM: x86: Rename ->tlb_flush() to ->tlb_flush_all()
  KVM: nVMX: Add helper to handle TLB flushes on nested VM-Enter/VM-Exit
  KVM: x86: Introduce KVM_REQ_TLB_FLUSH_CURRENT to flush current ASID
  KVM: x86/mmu: Use KVM_REQ_TLB_FLUSH_CURRENT for MMU specific flushes
  KVM: nVMX: Selectively use TLB_FLUSH_CURRENT for nested
    VM-Enter/VM-Exit
  KVM: nVMX: Reload APIC access page on nested VM-Exit only if necessary
  KVM: VMX: Retrieve APIC access page HPA only when necessary
  KVM: VMX: Don't reload APIC access page if its control is disabled
  KVM: x86/mmu: Move fast_cr3_switch() side effects to
    __kvm_mmu_new_cr3()
  KVM: x86/mmu: Add separate override for MMU sync during fast CR3
    switch
  KVM: x86/mmu: Add module param to force TLB flush on root reuse
  KVM: nVMX: Skip MMU sync on nested VMX transition when possible
  KVM: nVMX: Don't flush TLB on nested VMX transition
  KVM: nVMX: Free only the affected contexts when emulating INVEPT
  KVM: x86: Replace "cr3" with "pgd" in "new cr3/pgd" related code
  KVM: VMX: Clean cr3/pgd handling in vmx_load_mmu_pgd()

 arch/x86/include/asm/kvm_host.h |  25 +++-
 arch/x86/kvm/mmu/mmu.c          | 145 +++++++++----------
 arch/x86/kvm/mmu/paging_tmpl.h  |   2 +-
 arch/x86/kvm/svm.c              |  19 ++-
 arch/x86/kvm/vmx/nested.c       | 249 ++++++++++++++++++++++----------
 arch/x86/kvm/vmx/nested.h       |   7 +
 arch/x86/kvm/vmx/ops.h          |  32 ++--
 arch/x86/kvm/vmx/vmx.c          | 119 ++++++++++++---
 arch/x86/kvm/vmx/vmx.h          |  19 +--
 arch/x86/kvm/x86.c              |  67 ++++++---
 arch/x86/kvm/x86.h              |   6 +
 11 files changed, 448 insertions(+), 242 deletions(-)
```
#### [RESEND][patch V3 00/23] x86/entry: Consolidation part II (syscalls)
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Fri Mar 20 17:59:56 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11450511
Return-Path: <SRS0=CcrQ=5F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34A4A13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 22:05:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E55621556
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 20 Mar 2020 22:05:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727671AbgCTWFI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 20 Mar 2020 18:05:08 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:37507 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727426AbgCTWET (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 20 Mar 2020 18:04:19 -0400
Received: from p5de0bf0b.dip0.t-ipconnect.de ([93.224.191.11]
 helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1jFPk1-0004TN-5N; Fri, 20 Mar 2020 23:03:45 +0100
Received: from nanos.tec.linutronix.de (localhost [IPv6:::1])
        by nanos.tec.linutronix.de (Postfix) with ESMTP id 9F4A8FFC8D;
        Fri, 20 Mar 2020 23:03:44 +0100 (CET)
Message-Id: <20200320175956.033706968@linutronix.de>
User-Agent: quilt/0.65
Date: Fri, 20 Mar 2020 18:59:56 +0100
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paul McKenney <paulmck@kernel.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        "Joel Fernandes (Google)" <joel@joelfernandes.org>,
        "Steven Rostedt (VMware)" <rostedt@goodmis.org>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Alexei Starovoitov <ast@kernel.org>,
        Frederic Weisbecker <frederic@kernel.org>,
        Mathieu Desnoyers <mathieu.desnoyers@efficios.com>,
        Brian Gerst <brgerst@gmail.com>,
        Juergen Gross <jgross@suse.com>,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Subject: [RESEND][patch V3 00/23] x86/entry: Consolidation part II (syscalls)
Content-transfer-encoding: 8-bit
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

Sorry for the resend noise. I managed to fatfinger one of my scripts
so it dropped all Ccs and sent it only to LKML. Sigh....

This is the third version of the syscall entry code consolidation
series. V2 can be found here:

  https://lore.kernel.org/r/20200308222359.370649591@linutronix.de

It applies on top of

  git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git x86/entry

and is also available from git:

    git://git.kernel.org/pub/scm/linux/kernel/git/tglx/devel entry-v3-part2

The changes vs. V2:

 - A massive rework utilizing Peter Zijlstras objtool patches to analyze
   the new .noinstr.text section:

   https://lore.kernel.org/r/20200317170234.897520633@infradead.org

   Working with this was really helpful as it clearly pin pointed code
   which calls out of the protected section which is much more efficient
   and focussed than chasing everything manually.

 - Picked up the two RCU patches from Paul for completeness. The bugfix
   is required anyway and the comments have been really helpful to see
   where the defense line has to be.

 - As the tool flagged KVM as red zone, I looked at the context tracking
   usage there and it has similar if not worse issues. New set of patches
   dealing with that.

Please have a close look at the approach and the resulting protected areas.

Known issues:

  - The kprobes '.noinstr.text' exclusion currently works only for built
    in code. Haven't figured out how to to fix that, but I'm sure that
    Masami knows :)

  - The various SANitizers if enabled ruin the picture. Peter and I still
    have no brilliant idea what to do about that.

Thanks,

	tglx
---
 arch/x86/entry/common.c                |  173 ++++++++++++++++++++++++---------
 arch/x86/entry/entry_32.S              |   24 ----
 arch/x86/entry/entry_64.S              |    6 -
 arch/x86/entry/entry_64_compat.S       |   32 ------
 arch/x86/entry/thunk_64.S              |   45 +++++++-
 arch/x86/include/asm/bug.h             |    3 
 arch/x86/include/asm/hardirq.h         |    4 
 arch/x86/include/asm/irqflags.h        |    3 
 arch/x86/include/asm/nospec-branch.h   |    4 
 arch/x86/include/asm/paravirt.h        |    3 
 arch/x86/kvm/svm.c                     |  152 ++++++++++++++++++----------
 arch/x86/kvm/vmx/ops.h                 |    4 
 arch/x86/kvm/vmx/vmenter.S             |    2 
 arch/x86/kvm/vmx/vmx.c                 |   78 +++++++++++---
 arch/x86/kvm/x86.c                     |    4 
 b/include/asm-generic/bug.h            |    9 +
 include/asm-generic/sections.h         |    3 
 include/asm-generic/vmlinux.lds.h      |    4 
 include/linux/compiler.h               |   24 ++++
 include/linux/compiler_types.h         |    4 
 include/linux/context_tracking.h       |   27 +++--
 include/linux/context_tracking_state.h |    6 -
 include/linux/irqflags.h               |    6 +
 include/linux/sched.h                  |    1 
 kernel/context_tracking.c              |   14 +-
 kernel/kprobes.c                       |   11 ++
 kernel/locking/lockdep.c               |   66 +++++++++---
 kernel/panic.c                         |    4 
 kernel/rcu/tree.c                      |   91 +++++++++++------
 kernel/rcu/tree_plugin.h               |    4 
 kernel/rcu/update.c                    |    7 -
 kernel/trace/trace_preemptirq.c        |   25 ++++
 lib/debug_locks.c                      |    2 
 lib/smp_processor_id.c                 |   10 -
 scripts/mod/modpost.c                  |    2 
 35 files changed, 590 insertions(+), 267 deletions(-)
```
