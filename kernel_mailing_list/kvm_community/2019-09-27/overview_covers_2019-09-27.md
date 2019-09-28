

#### [PATCH v7 0/7] Introduce support for Guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Fri Sep 27 02:19:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11163629
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 631B6112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 02:17:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4A959207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 02:17:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727897AbfI0CRJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 26 Sep 2019 22:17:09 -0400
Received: from mga17.intel.com ([192.55.52.151]:25572 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726140AbfI0CRJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 26 Sep 2019 22:17:09 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 26 Sep 2019 19:17:08 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,553,1559545200";
   d="scan'208";a="193020627"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga003.jf.intel.com with ESMTP; 26 Sep 2019 19:17:06 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v7 0/7] Introduce support for Guest CET feature
Date: Fri, 27 Sep 2019 10:19:20 +0800
Message-Id: <20190927021927.23057-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. It includes two
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).

KVM modification is required to support Guest CET feature.
This patch serial implemented CET related CPUID/XSAVES enumeration, MSRs
and VMEntry configuration etc.so that Guest kernel can setup CET
runtime infrastructure based on them. Some MSRs and related feature
flags used in the patches reference the definitions in kernel patch.

CET kernel patches is here:
https://lkml.org/lkml/2019/8/13/1110
https://lkml.org/lkml/2019/8/13/1109

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


PATCH 1    : Fix CPUID(0xD, n) enumeration to support XSS MSR.
PATCH 2    : Define CET VMCS fields and bits.
PATCH 3    : Pass through CET MSRs to Guest.
PATCH 4    : Load Guest CET states when CET is enabled.
PATCH 5    : Add CET CR4 bit and CET xsaves support in XSS MSR.
PATCH 6    : Load Guest FPU states for XSAVES managed MSRs.
PATCH 7    : Add user-space CET MSR access interface.


Sean Christopherson (1):
  KVM: x86: Load Guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (6):
  KVM: CPUID: Fix IA32_XSS support in CPUID(0xd,i) enumeration
  KVM: VMX: Define CET VMCS fields and CPUID flags
  KVM: VMX: Pass through CET related MSRs to Guest
  KVM: VMX: Load Guest CET via VMCS when CET is enabled in Guest
  KVM: X86: Add CET CR4 bit and XSS support
  KVM: X86: Add user-space access interface for CET MSRs

 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/include/asm/vmx.h      |   8 ++
 arch/x86/kvm/cpuid.c            | 110 ++++++++++++++-------
 arch/x86/kvm/cpuid.h            |   2 +
 arch/x86/kvm/svm.c              |   7 ++
 arch/x86/kvm/vmx/vmx.c          | 169 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              |  22 ++++-
 arch/x86/kvm/x86.h              |   8 ++
 8 files changed, 287 insertions(+), 44 deletions(-)
```
#### [kvm-unit-tests PATCH 0/6] arm: Use stable test output lines
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Fri Sep 27 10:42:21 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andre Przywara <andre.przywara@arm.com>
X-Patchwork-Id: 11164335
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A84A912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 10:42:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0BF78217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 10:42:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727195AbfI0Kml (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 06:42:41 -0400
Received: from foss.arm.com ([217.140.110.172]:48720 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726087AbfI0Kmh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 06:42:37 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EF95728;
        Fri, 27 Sep 2019 03:42:33 -0700 (PDT)
Received: from donnerap.arm.com (donnerap.cambridge.arm.com [10.1.197.44])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 2B2FC3F534;
        Fri, 27 Sep 2019 03:42:33 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>
Cc: kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org
Subject: [kvm-unit-tests PATCH 0/6] arm: Use stable test output lines
Date: Fri, 27 Sep 2019 11:42:21 +0100
Message-Id: <20190927104227.253466-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using kvm-unit-tests inside automated testing frameworks,
variable test naming becomes a problem. Some frameworks recognise tests
by their test output line and group the outputs from various runs for
statistical and reporting purposes. Having variable output like timer
values in there spoils this approach. Also the test name should be
somewhat self-explanatory, which is not true for every test.
Some examples highlighting the problem (TAP output from run-tests.sh -t):
ok 1 - selftest: setup: smp: nr_cpus = 2
ok 2 - selftest: setup: mem: size = 256 MB
ok 8 - selftest: smp: CPU(  1) mpidr=0080000001
ok 9 - selftest: smp: CPU(  2) mpidr=0080000002
ok 54 - gicv2: mmio: ITARGETSR: byte writes successful (0x1f => 0x01010001)
ok 55 - gicv2: mmio: all 3 CPUs have interrupts
ok 73 - invalid-function
ok 76 - cpu-on
ok 90 - ptimer-busy-loop: timer has expired (-8445)

This series aims to fix most of the problems, by making the actual test
report output line stable. I think this is best practises in the testing
world, at least when using TAP. We still retain the full information, by
moving every variable output into INFO: lines (which are still logged,
but typically filtered for automated processing).
The above lines now look like this:
ok 1 - selftest: setup: smp: number of CPUs matches expectation
ok 2 - selftest: setup: mem: memory size matches expectation
ok 8 - selftest: smp: MPIDR test on all CPUs
ok 49 - gicv2: mmio: ITARGETSR: byte writes successful
ok 50 - gicv2: mmio: all CPUs have interrupts
ok 68 - psci: invalid-function
ok 71 - psci: cpu-on
ok 85 - ptimer-busy-loop: timer has expired

Looks a bit more boring, but it's nicer for automated processing and
logging.

I am open for a discussion about the general approach, thus this is
dealing with ARM tests for now only.

Looking forward to any feedback!

Cheers,
Andre

Andre Przywara (6):
  arm: gic: check_acked: add test description
  arm: gic: Split variable output data from test name
  arm: timer: Split variable output data from test name
  arm: selftest: Split variable output data from test name
  arm: selftest: Make MPIDR output stable
  arm: Add missing test name prefix calls

 arm/gic.c      | 64 ++++++++++++++++++++++++++++++--------------------
 arm/pci-test.c |  2 ++
 arm/psci.c     |  2 ++
 arm/selftest.c | 23 ++++++++++++++----
 arm/timer.c    |  3 ++-
 5 files changed, 62 insertions(+), 32 deletions(-)
```
#### [PATCH v2 0/3] KVM: MMU: fix nested guest live migration with PML
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Fri Sep 27 11:15:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11164361
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF14517EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:16:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8C726217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:16:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="J1It2fck"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726594AbfI0LPt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:15:49 -0400
Received: from mail-wm1-f67.google.com ([209.85.128.67]:54672 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725992AbfI0LPs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 07:15:48 -0400
Received: by mail-wm1-f67.google.com with SMTP id p7so6150225wmp.4;
        Fri, 27 Sep 2019 04:15:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=KM5/fL2Yt0ZifkcygAo4LHNxxbfupXEym28ra8qTLbk=;
        b=J1It2fckNyXTHriDkvoPhArrNWQ61s/q+CcHPM86GDjlu3yV/E30GGKi06M5gZcTUJ
         5Weme2PW+RFADwyGaVDgf+o1HyXScwzisYSrqzqlkaG92KV4s/IfPfHxGQeCqwNy9YZr
         fyK0Qv+U1PlZ8A75KLv13rIFgMF62pDHMPhi4CaARRsuFBzziali0yDpdC0cD80EAxhi
         ETza7tpuWouCNJTynMhq1UM4FTcr8eaSlqrfSD88BuahkZRYrrFI5LS3yVaxCexemLCs
         4YnocKfMigCdOm7ulq4Kpi603M4DV4jlZRx2Uuhp6CHmEuuycQiXFCOcnYhdtElwxAYV
         5ieA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=KM5/fL2Yt0ZifkcygAo4LHNxxbfupXEym28ra8qTLbk=;
        b=LGwDq0/FiHw0dbQFGJBXydnOfVrUj+ByHpiMRfwQb+1A/MkFnKaprOrgJK2B9hoTP8
         Fj+j6Bz3ay+Wv3AZ39K7Zdv0qFfgq53emo/zwwkV3ts5CtkGBgwzHtw/k9jnB2Wqn7j6
         O5bM0jIWDgFSvJDXy0JgSLboSvLX4ClNUV5MOsPUzI45vwgGBiCE2yNlqORvsQAO/w3V
         OaNPRtB+J6htOezYhJgxNimUju61Oggsqga9GqWIIjg3UGn1CHlKDTr2EQpuYS1NJNQw
         RLFgGwEk7SlJYKWHfiTapOsSiKHHOQ7NBQAI0HvmZOFOYJzlGxwaLYfUYPETtoF6qPzJ
         An+g==
X-Gm-Message-State: APjAAAUiyPOVt96gblXV1r5feMqlI27AvBF/TvQy0GLAtqFjIN9AdQuF
        XH4aed+kZnQSPBdpFRk/yfaLnBsu
X-Google-Smtp-Source: 
 APXvYqze5BcvyPMMQhinLxNxJJjbNrKHXTnEhYvRSJiYH2P41iv6PpSAah/uL9xk67roqKzZRCpsuw==
X-Received: by 2002:a05:600c:290c:: with SMTP id
 i12mr7014897wmd.77.1569582946521;
        Fri, 27 Sep 2019 04:15:46 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 r28sm2913848wrr.94.2019.09.27.04.15.45
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 27 Sep 2019 04:15:45 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Junaid Shahid <junaids@google.com>
Subject: [PATCH v2 0/3] KVM: MMU: fix nested guest live migration with PML
Date: Fri, 27 Sep 2019 13:15:40 +0200
Message-Id: <1569582943-13476-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shadow paging is fundamentally incompatible with the page-modification
log, because the GPAs in the log come from the wrong memory map.
In particular, for the EPT page-modification log, the GPAs in the log come
from L2 rather than L1.  (If there was a non-EPT page-modification log,
we couldn't use it for shadow paging because it would log GVAs rather
than GPAs).

Therefore, we need to rely on write protection to record dirty pages.
This has the side effect of bypassing PML, since writes now result in an
EPT violation vmexit.

This turns out to be a surprisingly small patch---the testcase is what's
guilty of the scary diffstat.  But that is because the KVM MMU code is
absurdly clever, so a very close review is appreciated.

Paolo

v1->v2: don't place the new code in spte_clear_dirty [Junaid]

Paolo Bonzini (3):
  KVM: x86: assign two bits to track SPTE kinds
  KVM: x86: fix nested guest live migration with PML
  selftests: kvm: add test for dirty logging inside nested guests

 arch/x86/include/asm/kvm_host.h                    |   7 -
 arch/x86/kvm/mmu.c                                 |  65 +++++--
 tools/testing/selftests/kvm/Makefile               |   1 +
 .../selftests/kvm/include/x86_64/processor.h       |   3 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |  14 ++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   2 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   3 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 201 ++++++++++++++++++++-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c      | 156 ++++++++++++++++
 9 files changed, 426 insertions(+), 26 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_dirty_log_test.c
```
#### [RFC PATCH 00/13] vsock: add multi-transports support
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Fri Sep 27 11:26:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11164363
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DBA81800
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:27:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E9DE2217D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:27:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726843AbfI0L1S (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:27:18 -0400
Received: from mx1.redhat.com ([209.132.183.28]:52976 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725890AbfI0L1R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 07:27:17 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E42E0C05975D;
        Fri, 27 Sep 2019 11:27:16 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-249.ams2.redhat.com
 [10.36.117.249])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7D2685D9C9;
        Fri, 27 Sep 2019 11:27:04 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Sasha Levin <sashal@kernel.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, "David S. Miller" <davem@davemloft.net>,
        virtualization@lists.linux-foundation.org,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Jason Wang <jasowang@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Dexuan Cui <decui@microsoft.com>,
        Jorgen Hansen <jhansen@vmware.com>
Subject: [RFC PATCH 00/13] vsock: add multi-transports support
Date: Fri, 27 Sep 2019 13:26:50 +0200
Message-Id: <20190927112703.17745-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.32]);
 Fri, 27 Sep 2019 11:27:17 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,
this series adds the multi-transports support to vsock, following
this proposal:
https://www.spinics.net/lists/netdev/msg575792.html

With the multi-transports support, we can use vsock with nested VMs
(using also different hypervisors) loading both guest->host and
host->guest transports at the same time.
Before this series, vmci-transport supported this behavior but only
using VMware hypervisor on L0, L1, etc.

The first 8 patches are cleanups and preparations, maybe some of
these can go regardless of this series.

Patch 9 changes the hvs_remote_addr_init(). setting the
VMADDR_CID_HOST as remote CID instead of VMADDR_CID_ANY to make
the choice of transport to be used work properly.
@Dexuan Could this change break anything?

Patch 10 adds multi-transports support.
RFC:
- I'd like to move MODULE_ALIAS_NETPROTO(PF_VSOCK) to af_vsock.c.
  @Jorgen could this break the VMware products?

- DGRAM sockets are handled as before, I don't know if make sense
  work on it now, or when another transport will support DGRAM.
  The big issues here is that we cannot link 1-1 a socket to
  transport as for stream sockets since DGRAM is not
  connection-oriented.

Patches 11 and 12 maybe can be merged with patch 10.
Patch 11 maybe is tricky, but it allows to have vmci_transport and
vhost_vsock loaded at the same time and it also alleviates the
problem of having MODULE_ALIAS_NETPROTO(PF_VSOCK) in vmci_transport.c
Patch 12 prevents the transport modules unloading while sockets are
assigned to them.

Patch 13 fixes an issue in the bind() logic discoverable only with
the new multi-transport support.

I've tested this series with nested KVM (vsock-transport [L0,L1],
virtio-transport[L1,L2]) and with VMware (L0) + KVM (L1)
(vmci-transport [L0,L1], vhost-transport [L1], virtio-transport[L2]).

@Dexuan please can you test on HyperV that I didn't break anything
even without nested VMs?
I'll try to setup a Windows host where to test the nested VMs.

Thanks in advance for your comments and suggestions,
Stefano

Stefano Garzarella (13):
  vsock/vmci: remove unused VSOCK_DEFAULT_CONNECT_TIMEOUT
  vsock: remove vm_sockets_get_local_cid()
  vsock: remove include/linux/vm_sockets.h file
  vsock: add 'transport' member in the struct vsock_sock
  vsock/virtio: add transport parameter to the
    virtio_transport_reset_no_sock()
  vsock: add 'struct vsock_sock *' param to vsock_core_get_transport()
  vsock: handle buffer_size sockopts in the core
  vsock: move vsock_insert_unbound() in the vsock_create()
  hv_sock: set VMADDR_CID_HOST in the hvs_remote_addr_init()
  vsock: add multi-transports support
  vsock: add 'transport_hg' to handle g2h\h2g transports
  vsock: prevent transport modules unloading
  vsock: fix bind() behaviour taking care of CID

 drivers/vhost/vsock.c                   |  96 +++---
 include/linux/virtio_vsock.h            |  18 +-
 include/linux/vm_sockets.h              |  15 -
 include/net/af_vsock.h                  |  35 ++-
 include/net/vsock_addr.h                |   2 +-
 net/vmw_vsock/af_vsock.c                | 374 ++++++++++++++++++------
 net/vmw_vsock/hyperv_transport.c        |  68 ++---
 net/vmw_vsock/virtio_transport.c        | 177 ++++++-----
 net/vmw_vsock/virtio_transport_common.c | 127 +++-----
 net/vmw_vsock/vmci_transport.c          | 123 +++-----
 net/vmw_vsock/vmci_transport.h          |   3 -
 net/vmw_vsock/vmci_transport_notify.h   |   1 -
 12 files changed, 555 insertions(+), 484 deletions(-)
 delete mode 100644 include/linux/vm_sockets.h
```
#### [PATCH v2 0/6] KVM: PPC: Book3S: HV: XIVE: Allocate less VPs in OPAL
##### From: Greg Kurz <groug@kaod.org>

```c
From patchwork Fri Sep 27 11:53:32 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11164413
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 66F8413BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:53:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F50C20872
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 11:53:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726295AbfI0Lxn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 07:53:43 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:51230 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726144AbfI0Lxn (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 27 Sep 2019 07:53:43 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8RBkiTp120526
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 07:53:40 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v9gv3jdch-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 07:53:40 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Fri, 27 Sep 2019 12:53:38 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 27 Sep 2019 12:53:34 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8RBrXKQ24445092
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 27 Sep 2019 11:53:33 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id F326AAE057;
        Fri, 27 Sep 2019 11:53:32 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 992F4AE055;
        Fri, 27 Sep 2019 11:53:32 +0000 (GMT)
Received: from bahia.lan (unknown [9.145.172.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 27 Sep 2019 11:53:32 +0000 (GMT)
Subject: [PATCH v2 0/6] KVM: PPC: Book3S: HV: XIVE: Allocate less VPs in OPAL
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org, stable@vger.kernel.org
Date: Fri, 27 Sep 2019 13:53:32 +0200
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19092711-4275-0000-0000-0000036BC507
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092711-4276-0000-0000-0000387E46F9
Message-Id: <156958521220.1503771.2119482814236775333.stgit@bahia.lan>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-27_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=330 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909270112
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This brings some fixes and allows to start more VMs with an in-kernel
XIVE or XICS-on-XIVE device.

Changes since v1 (https://patchwork.ozlabs.org/cover/1166099/):
- drop a useless patch
- add a patch to show VP ids in debugfs
- update some changelogs
- fix buggy check in patch 5
- Cc: stable
---
Greg

---

Greg Kurz (6):
      KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when VPs are allocated
      KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use
      KVM: PPC: Book3S HV: XIVE: Show VP id in debugfs
      KVM: PPC: Book3S HV: XIVE: Compute the VP id in a common helper
      KVM: PPC: Book3S HV: XIVE: Make VP block size configurable
      KVM: PPC: Book3S HV: XIVE: Allow userspace to set the # of VPs


 Documentation/virt/kvm/devices/xics.txt |   14 +++
 Documentation/virt/kvm/devices/xive.txt |    8 ++
 arch/powerpc/include/uapi/asm/kvm.h     |    3 +
 arch/powerpc/kvm/book3s_xive.c          |  142 ++++++++++++++++++++++++-------
 arch/powerpc/kvm/book3s_xive.h          |   17 ++++
 arch/powerpc/kvm/book3s_xive_native.c   |   40 +++------
 6 files changed, 167 insertions(+), 57 deletions(-)
```
#### [PATCH 0/9] Create a userfaultfd demand paging test
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Fri Sep 27 16:18:28 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11164791
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DD8DF924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:18:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BA37421841
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 16:18:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Ar9jvV5x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727932AbfI0QSl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 12:18:41 -0400
Received: from mail-vk1-f201.google.com ([209.85.221.201]:42470 "EHLO
        mail-vk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727472AbfI0QSl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 12:18:41 -0400
Received: by mail-vk1-f201.google.com with SMTP id 18so2721764vkm.9
        for <kvm@vger.kernel.org>; Fri, 27 Sep 2019 09:18:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=Ar9jvV5xbA8qUlUV3OgckW5CkZ9INmnhnI96YfE1/pFNlm5HZsEljt+QQVsrxnO3Gj
         XD1JMtkUA5ixzhD0C6yhT/hf3TwzBIblDAaOKkGYhmI6nC1sK3xNSVC7CNXDflGHKr+l
         VsD43N8JrjQw11Ev6iDSbJ9/LISWjc3S//kDUW5Au9ju1PxNBO1IQbSBYGWMXGUnwdRk
         JnC4rp7aVpgyGN8B+f0E+5sjCwllidxf0s/pSlbaHmvCn1iLPFgB7p0kNxY2kI+q/aH+
         KeVFAKFnMdWf5bLWG5UEyc7c4/9+IlX8NupoKoBf7vfOJ3IVhuN3KQm5UPBCVvo55hdJ
         chHA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=QBk1De+neBM44JDW8dJBkgj4d51R52aSrFCiyt6odwjK1E/TNVr4FCEoBGeKYjZhZt
         3FegSrAKWX48PqYQ2iDTcKwTzeOggTNB/HlhYWpSRYSY3WUKjkd49DlyVwjdlXBvTdab
         qtRQq88bEcr0Xm4tFNAU6GbLPRs3ncFsFxyl9afAHdxmozp+M71+iJogUZQp1ik7K99g
         asErJtzNozhSN3KPFsG8Vj/3dKAiREnGlxJ9aHjfwL9Qg23LtzVGdE7oXiDcuVvEeZ15
         y+xEp2+Zx5kE6TNzdbETs3VOdWtA05AcKhQ0o3RitKad66XdIHpYdckVfuV3ptELtyN9
         bODw==
X-Gm-Message-State: APjAAAWariyEjMyZfvqiQU2la+iSgJWOvUdZOu7AGVUsUxwHbjQH4Zgi
        /5uIX1qymJaCg25LYRooVUhQuQstE43eOP5tVpv08t2X0hdI5bIzI4E56bn1Cq63yLd1+0I9QcH
        GERO5xSeatNfO7bE2dMSoTg9grdz3PyF+0buMJ1Al+GnP32ccptSuVviaWKXF
X-Google-Smtp-Source: 
 APXvYqxokp5DF4qLKfyp3zZnmBXiq2/CPP9dLbJ1WOoMDDMLgAqqKqO7z3xRx+ZjRpWsHGDd0hiIS9P0JfZP
X-Received: by 2002:ac5:cd4a:: with SMTP id n10mr2362832vkm.82.1569601119998;
 Fri, 27 Sep 2019 09:18:39 -0700 (PDT)
Date: Fri, 27 Sep 2019 09:18:28 -0700
Message-Id: <20190927161836.57978-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.444.g18eeb5a265-goog
Subject: [PATCH 0/9] Create a userfaultfd demand paging test
From: Ben Gardon <bgardon@google.com>
To: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When handling page faults for many vCPUs during demand paging, KVM's MMU
lock becomes highly contended. This series creates a test with a naive
userfaultfd based demand paging implementation to demonstrate that
contention. This test serves both as a functional test of userfaultfd
and a microbenchmark of demand paging performance with a variable number
of vCPUs and memory per vCPU.

The test creates N userfaultfd threads, N vCPUs, and a region of memory
with M pages per vCPU. The N userfaultfd polling threads are each set up
to serve faults on a region of memory corresponding to one of the vCPUs.
Each of the vCPUs is then started, and touches each page of its disjoint
memory region, sequentially. In response to faults, the userfaultfd
threads copy a static buffer into the guest's memory. This creates a
worst case for MMU lock contention as we have removed most of the
contention between the userfaultfd threads and there is no time required
to fetch the contents of guest memory.

This test was run successfully on Intel Haswell, Broadwell, and
Cascadelake hosts with a variety of vCPU counts and memory sizes.

This test was adapted from the dirty_log_test.

The series can also be viewed in Gerrit here:
https://linux-review.googlesource.com/c/virt/kvm/kvm/+/1464
(Thanks to Dmitry Vyukov <dvyukov@google.com> for setting up the Gerrit
instance)

Ben Gardon (9):
  KVM: selftests: Create a demand paging test
  KVM: selftests: Add demand paging content to the demand paging test
  KVM: selftests: Add memory size parameter to the demand paging test
  KVM: selftests: Pass args to vCPU instead of using globals
  KVM: selftests: Support multiple vCPUs in demand paging test
  KVM: selftests: Time guest demand paging
  KVM: selftests: Add parameter to _vm_create for memslot 0 base paddr
  KVM: selftests: Support large VMs in demand paging test
  Add static flag

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   4 +-
 .../selftests/kvm/demand_paging_test.c        | 610 ++++++++++++++++++
 tools/testing/selftests/kvm/dirty_log_test.c  |   2 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |   7 +-
 6 files changed, 621 insertions(+), 6 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/demand_paging_test.c
```
#### [PATCH v2 0/8] KVM: x86: nVMX GUEST_CR3 bug fix, and then some...
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Fri Sep 27 21:45:15 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11165187
Return-Path: <SRS0=cTVl=XW=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1891713B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 21:46:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F351C20863
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 27 Sep 2019 21:46:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728464AbfI0VpZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 27 Sep 2019 17:45:25 -0400
Received: from mga12.intel.com ([192.55.52.136]:45951 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726029AbfI0VpZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 27 Sep 2019 17:45:25 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Sep 2019 14:45:24 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,557,1559545200";
   d="scan'208";a="196852054"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by FMSMGA003.fm.intel.com with ESMTP; 27 Sep 2019 14:45:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Reto Buerki <reet@codelabs.ch>,
        Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v2 0/8] KVM: x86: nVMX GUEST_CR3 bug fix, and then some...
Date: Fri, 27 Sep 2019 14:45:15 -0700
Message-Id: <20190927214523.3376-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

*sigh*

v2 was shaping up to be a trivial update, until I started working on
Vitaly's suggestion to add a helper to test for register availability.

The primary purpose of this series is to fix a CR3 corruption in L2
reported by Reto Buerki when running with HLT interception disabled in L1.
On a nested VM-Enter that puts L2 into HLT, KVM never actually enters L2
and instead mimics HLT interception by canceling the nested run and
pretending that VM-Enter to L2 completed and then exited on HLT (which
KVM intercepted).  Because KVM never actually runs L2, KVM skips the
pending MMU update for L2 and so leaves a stale value in vmcs02.GUEST_CR3.
If the next wake event for L2 triggers a nested VM-Exit, KVM will refresh
vmcs12->guest_cr3 from vmcs02.GUEST_CR3 and consume the stale value.

Fix the issue by unconditionally writing vmcs02.GUEST_CR3 during nested
VM-Enter instead of deferring the update to vmx_set_cr3(), and skip the
update of GUEST_CR3 in vmx_set_cr3() when running L2.  I.e. make the
nested code fully responsible for vmcs02.GUEST_CR3.

Patch 02/08 is a minor optimization to skip the GUEST_CR3 update if
vmcs01 is already up-to-date.

Patches 03 and beyond are Vitaly's fault ;-).

Patches 03 and 04 are tangentially related cleanup to vmx_set_rflags()
that was discovered when working through the avail/dirty testing code.
Ideally they'd be sent as a separate series, but they conflict with the
avail/dirty helper changes and are themselves minor and straightforward.

Patches 05 and 06 clean up the register caching code so that there is a
single enum for all registers which use avail/dirty tracking.  While not
a true prerequisite for the avail/dirty helpers, the cleanup allows the
new helpers to take an 'enum kvm_reg' instead of a less helpful 'int reg'.

Patch 07 is the helpers themselves, as suggested by Vitaly.

Patch 08 is a truly optional change to ditch decache_cr3() in favor of
handling CR3 via cache_reg() like any other avail/dirty register.


Note, I collected the Reviewed-by and Tested-by tags for patches 01 and 02
even though I inverted the boolean from 'skip_cr3' to 'update_guest_cr3'.
Please drop the tags if that constitutes a non-trivial functional change.

v2:
  - Invert skip_cr3 to update_guest_cr3.  [Liran]
  - Reword the changelog and comment to be more explicit in detailing
    how/when KVM will process a nested VM-Enter without runnin L2.  [Liran]
  - Added Reviewed-by and Tested-by tags.
  - Add a comment in vmx_set_cr3() to explicitly state that nested
    VM-Enter is responsible for loading vmcs02.GUEST_CR3.  [Jim]
  - All of the loveliness in patches 03-08. [Vitaly]

Sean Christopherson (8):
  KVM: nVMX: Always write vmcs02.GUEST_CR3 during nested VM-Enter
  KVM: VMX: Skip GUEST_CR3 VMREAD+VMWRITE if the VMCS is up-to-date
  KVM: VMX: Consolidate to_vmx() usage in RFLAGS accessors
  KVM: VMX: Optimize vmx_set_rflags() for unrestricted guest
  KVM: x86: Add WARNs to detect out-of-bounds register indices
  KVM: x86: Fold 'enum kvm_ex_reg' definitions into 'enum kvm_reg'
  KVM: x86: Add helpers to test/mark reg availability and dirtiness
  KVM: x86: Fold decache_cr3() into cache_reg()

 arch/x86/include/asm/kvm_host.h |  5 +-
 arch/x86/kvm/kvm_cache_regs.h   | 67 +++++++++++++++++------
 arch/x86/kvm/svm.c              |  5 --
 arch/x86/kvm/vmx/nested.c       | 14 ++++-
 arch/x86/kvm/vmx/vmx.c          | 94 ++++++++++++++++++---------------
 arch/x86/kvm/x86.c              | 13 ++---
 arch/x86/kvm/x86.h              |  6 +--
 7 files changed, 123 insertions(+), 81 deletions(-)
```
