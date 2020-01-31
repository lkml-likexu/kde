

#### [PATCH 0/5] KVM: Move x86 init ops to separate struct
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Jan 30 00:10:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11357255
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF8E91398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:10:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B826F20716
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 00:10:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgA3AK0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 19:10:26 -0500
Received: from mga06.intel.com ([134.134.136.31]:48383 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726671AbgA3AK0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 19:10:26 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 16:10:25 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,379,1574150400";
   d="scan'208";a="261990342"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga002.fm.intel.com with ESMTP; 29 Jan 2020 16:10:24 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-mips@vger.kernel.org, kvm@vger.kernel.org,
        kvm-ppc@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, linux-kernel@vger.kernel.org
Subject: [PATCH 0/5] KVM: Move x86 init ops to separate struct
Date: Wed, 29 Jan 2020 16:10:18 -0800
Message-Id: <20200130001023.24339-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The non-x86 part of this series is wholly contained in patch 01.  Compared
to other recent kvm-wide changes, this one is very straightforward (famous
last words).

Like a few other architectures, e.g. PPC, x86 uses a set of global hooks
to call back into vendor code on demand.  A handlful of the x86 hooks are
used only within the scope of kvm_init().  This series moves the init-only
hooks to a separate struct, partly to clean up the code a bit, but mainly
so that the runtime hooks can be made available only after the x86 vendor
has completed its ->hardware_setup().  While working on a different series
I spent a fair bit of time scratching my as to why a kvm_x86_ops wasn't
working, and eventually realized VMX's callback wasn't "ready" because the
vmcs_config hadn't yet been populated.

Due to lack of a cross-compiling setup, the non-x86 changes in patch 01
are untested.

The SVM changes in patch 02 are fairly well tested, e.g. fudged things
enough to ensure KVM didn't explode on a null pointer.

Patch 05 is a bit scary as a rogue dereference of kvm_x86_ops before
->hardware_setup() will crash KVM (maybe the kernel?).  I didn't find any
obvious ways to use kvm_x86_ops on AMD, and tested on a few different
Intel CPUs, so I'm reasonably confident that there are no existing
violations.

Sean Christopherson (5):
  KVM: Pass kvm_init()'s opaque param to additional arch funcs
  KVM: x86: Move init-only kvm_x86_ops to separate struct
  KVM: VMX: Move hardware_setup() definition below vmx_x86_ops
  KVM: VMX: Configure runtime hooks using vmx_x86_ops
  KVM: x86: Set kvm_x86_ops only after ->hardware_setup() completes

 arch/mips/kvm/mips.c            |   4 +-
 arch/powerpc/kvm/powerpc.c      |   4 +-
 arch/s390/kvm/kvm-s390.c        |   4 +-
 arch/x86/include/asm/kvm_host.h |  13 +-
 arch/x86/kvm/svm.c              |  15 +-
 arch/x86/kvm/vmx/nested.c       |  15 +-
 arch/x86/kvm/vmx/nested.h       |   3 +-
 arch/x86/kvm/vmx/vmx.c          | 345 ++++++++++++++++----------------
 arch/x86/kvm/x86.c              |  16 +-
 include/linux/kvm_host.h        |   4 +-
 virt/kvm/arm/arm.c              |   4 +-
 virt/kvm/kvm_main.c             |  18 +-
 12 files changed, 238 insertions(+), 207 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/9] KVM: arm64: PMUv3 Event Counter Tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Thu Jan 30 11:25:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11357737
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3362139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:25:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7F52206D3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 11:25:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TW7uZIfh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726967AbgA3LZ2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 06:25:28 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:23293 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726902AbgA3LZ2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 06:25:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580383527;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=RD3+Ld7Dxp10D8lHwl6kiXjd9vd6HKHz9XGO3ilgvRk=;
        b=TW7uZIfh8x7YozKJ/q2QERwpQ0NiE+LIF72kO8rJI8JasWJ+OtCt2hnjIv5N3EuCGvCQG5
        5s0ACZamqFe9S/Hhm3AfsoU4gFJJHLKhX3o9sr9SePHrrmbVfsCHFUHTl3munfHwnx1da7
        xD21hF/ucjVVrqEsMzdX3Q4o7RiW+8I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-415-Z7hfLdmJPPalT3OyO1uCZg-1; Thu, 30 Jan 2020 06:25:23 -0500
X-MC-Unique: Z7hfLdmJPPalT3OyO1uCZg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DB762100551B;
        Thu, 30 Jan 2020 11:25:21 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-37.ams2.redhat.com [10.36.116.37])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 02B211001B05;
        Thu, 30 Jan 2020 11:25:13 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v2 0/9] KVM: arm64: PMUv3 Event Counter Tests
Date: Thu, 30 Jan 2020 12:25:01 +0100
Message-Id: <20200130112510.15154-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements tests exercising the PMUv3 event counters.
It tests both the 32-bit and 64-bit versions. Overflow interrupts
also are checked. Those tests only are written for arm64.

It allowed to reveal some issues related to SW_INCR implementation
(esp. related to 64-bit implementation), some problems related to
32-bit <-> 64-bit transitions and consistency of enabled states
of odd and event counters (See [1]).

Overflow interrupt testing relies of one patch from Andre
("arm: gic: Provide per-IRQ helper functions") to enable the
PPI 23, coming from "arm: gic: Test SPIs and interrupt groups"
(https://patchwork.kernel.org/cover/11234975/). Drew kindly
provided "arm64: Provide read/write_sysreg_s".

All PMU tests can be launched with:
./run_tests.sh -g pmu
Tests also can be launched individually. For example:
./arm-run arm/pmu.flat -append 'chained-sw-incr'

With KVM:
- chain-promotion and chained-sw-incr are known to be failing.
  [1] proposed a fix.
- On TX2, I have some random failures due to MEM_ACCESS event
  measured with a great disparity. This is not observed on
  other machines I have access to.
With TCG:
- all new tests are skipped

The series can be found at:
https://github.com/eauger/kut/tree/pmu_event_counters_v2

References:
[1] [PATCH 0/4] KVM/ARM: Misc PMU fixes
(https://www.spinics.net/lists/kvm-arm/msg38886.html)

History:
- Took into account Andre's comments except I did not
  use cnbz in the mem_access_loop() and I did not use
  @loop directly. Those changes had side effects I
  cannot explain on the tests. Anyway I think this can
  be improved later on.
- removed [kvm-unit-tests PATCH 09/10] arm/arm64: gic:
  Introduce setup_irq() helper

RFC -> v1:
- Use new report() proto
- Style cleanup
- do not warn about ARM spec recommendations
- add a comment about PMCEID0/1 splits

Andre Przywara (1):
  arm: gic: Provide per-IRQ helper functions

Andrew Jones (1):
  arm64: Provide read/write_sysreg_s

Eric Auger (7):
  arm: pmu: Let pmu tests take a sub-test parameter
  arm: pmu: Add a pmu struct
  arm: pmu: Check Required Event Support
  arm: pmu: Basic event counter Tests
  arm: pmu: Test chained counter
  arm: pmu: test 32-bit <-> 64-bit transitions
  arm: pmu: Test overflow interrupts

 arm/pmu.c              | 786 ++++++++++++++++++++++++++++++++++++++++-
 arm/unittests.cfg      |  55 ++-
 lib/arm/asm/gic-v3.h   |   2 +
 lib/arm/asm/gic.h      |   9 +
 lib/arm/gic.c          |  90 +++++
 lib/arm64/asm/sysreg.h |  11 +
 6 files changed, 936 insertions(+), 17 deletions(-)
```
#### [PATCH 0/2] kvm: split_lock: Fix emulator and extend #AC handler 
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Thu Jan 30 12:19:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11357853
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E02413B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:24:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D1B420CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:24:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727074AbgA3MYs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 07:24:48 -0500
Received: from mga07.intel.com ([134.134.136.100]:49436 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726902AbgA3MYr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 07:24:47 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Jan 2020 04:24:46 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,381,1574150400";
   d="scan'208";a="262155240"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by fmsmga002.fm.intel.com with ESMTP; 30 Jan 2020 04:24:44 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, x86@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH 0/2] kvm: split_lock: Fix emulator and extend #AC handler 
Date: Thu, 30 Jan 2020 20:19:37 +0800
Message-Id: <20200130121939.22383-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As kernel split lock patch[1] merged into tip tree, kvm emulator needs to be
fixed and vmx's #AC handler needs to be extended.

Patch 1 fixes x86/emulator to emualte split lock access as write to avoid
malicous guest[2] exploiting it to populate host kernel log.

Patch 2 extends vmx's #AC handler that we can make old guestes (has split_lock
buges) survive on certain cases.

[1] https://lore.kernel.org/lkml/158031147976.396.8941798847364718785.tip-bot2@tip-bot2/
[2] https://lore.kernel.org/lkml/8c5b11c9-58df-38e7-a514-dc12d687b198@redhat.com/

Xiaoyao Li (2):
  KVM: x86: Emulate split-lock access as a write
  KVM: VMX: Extend VMX's #AC handding

 arch/x86/include/asm/cpu.h  | 13 ++++++++++++
 arch/x86/kernel/cpu/intel.c | 18 ++++++++++------
 arch/x86/kvm/vmx/vmx.c      | 42 ++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.h      |  3 +++
 arch/x86/kvm/x86.c          | 11 ++++++++++
 5 files changed, 78 insertions(+), 9 deletions(-)
```
#### [PATCH v9 0/6] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Jan 30 12:34:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11357855
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40FD092A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:34:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 28D89206F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 12:34:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727112AbgA3Met (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 07:34:49 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49184 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726873AbgA3Mes (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 07:34:48 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00UCYQMU044821
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:34:47 -0500
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xu5q68jr5-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 30 Jan 2020 07:34:47 -0500
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 30 Jan 2020 12:34:45 -0000
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 30 Jan 2020 12:34:43 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00UCYg7l60227718
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 30 Jan 2020 12:34:42 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 56A945204F;
        Thu, 30 Jan 2020 12:34:42 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.44])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id B80AB5204E;
        Thu, 30 Jan 2020 12:34:40 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v9 0/6] KVM: s390: Add new reset vcpu API
Date: Thu, 30 Jan 2020 07:34:28 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20013012-0020-0000-0000-000003A57967
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20013012-0021-0000-0000-000021FD2E83
Message-Id: <20200130123434.68129-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-30_03:2020-01-28,2020-01-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 priorityscore=1501 mlxlogscore=809
 clxscore=1015 mlxscore=0 bulkscore=0 spamscore=0 suspectscore=1
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001300092
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's implement the remaining resets, namely the normal and clear
reset to improve architectural compliance. 

While we're at it, let's also start testing the new API.
Those tests are not yet complete, but will be extended in the future.

Christian Borntraeger (1):
  KVM: s390: do not clobber registers during guest reset/store status

Janosch Frank (4):
  KVM: s390: Cleanup initial cpu reset
  KVM: s390: Add new reset vcpu API
  selftests: KVM: Add fpu and one reg set/get library functions
  selftests: KVM: s390x: Add reset tests

Pierre Morel (1):
  selftests: KVM: testing the local IRQs resets

 Documentation/virt/kvm/api.txt                |  43 ++++
 arch/s390/include/asm/kvm_host.h              |   5 +
 arch/s390/kvm/kvm-s390.c                      |  86 ++++++--
 include/uapi/linux/kvm.h                      |   5 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  48 +++++
 tools/testing/selftests/kvm/s390x/resets.c    | 203 ++++++++++++++++++
 8 files changed, 379 insertions(+), 18 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/s390x/resets.c
```
#### [PATCH v2 00/12] python: Explicit usage of Python 3
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu Jan 30 16:32:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11358385
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 502A2924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 16:32:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 24F942082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 16:32:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="J93ZCXZ9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727266AbgA3Qc5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 11:32:57 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:22563 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727191AbgA3Qc5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 30 Jan 2020 11:32:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1580401976;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=O+P0Tz8NZRB9Hi7OjfGryLokEBLJcJzSqJTk8bv6+vQ=;
        b=J93ZCXZ9Y62z4ghXHy/a0w1cyUaoY5X/savmx2I22rXr64jAAkJVeDqym8nGgPC8O1/PYb
        /zE+0U5foVN5204yQtWmYTMd9FO1aPW7NVS+XhX2afv6aNcdjSA6PRK/9c1BIgGZ3p0WbM
        rPpxT8gawoATPYgsJwvCQeHMdDiTAH0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-71-Up64THfAPlK0--ObGnnmcA-1; Thu, 30 Jan 2020 11:32:49 -0500
X-MC-Unique: Up64THfAPlK0--ObGnnmcA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6678018CA241;
        Thu, 30 Jan 2020 16:32:47 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-184.brq.redhat.com [10.40.205.184])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 94C525DA8C;
        Thu, 30 Jan 2020 16:32:34 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Richard Henderson <rth@twiddle.net>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>,
 Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>,
 Eduardo Habkost <ehabkost@redhat.com>,
 "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
 Cleber Rosa <crosa@redhat.com>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>, qemu-block@nongnu.org,
 Stefan Hajnoczi <stefanha@redhat.com>, Juan Quintela <quintela@redhat.com>,
	=?utf-8?q?Daniel_P_=2E_Berrang=C3=A9?= <berrange@redhat.com>,
 Michael Roth <mdroth@linux.vnet.ibm.com>, Max Reitz <mreitz@redhat.com>,
 Markus Armbruster <armbru@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Fam Zheng <fam@euphon.net>, Kevin Wolf <kwolf@redhat.com>,
 kvm@vger.kernel.org
Subject: [PATCH v2 00/12] python: Explicit usage of Python 3
Date: Thu, 30 Jan 2020 17:32:20 +0100
Message-Id: <20200130163232.10446-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

These are mechanical sed patches used to convert the
code base to Python 3, as suggested on this thread:
https://www.mail-archive.com/qemu-devel@nongnu.org/msg675024.html

Since v1:
- new checkpatch.pl patch
- addressed Kevin and Vladimir review comments
- added R-b/A-b tags

Regards,

Phil.

Philippe Mathieu-Daudé (12):
  scripts/checkpatch.pl: Only allow Python 3 interpreter
  tests/qemu-iotests/check: Allow use of python3 interpreter
  tests/qemu-iotests: Explicit usage of Python 3 (scripts with __main__)
  tests: Explicit usage of Python 3
  scripts: Explicit usage of Python 3 (scripts with __main__)
  scripts/minikconf: Explicit usage of Python 3
  tests/acceptance: Remove shebang header
  scripts/tracetool: Remove shebang header
  tests/vm: Remove shebang header
  tests/qemu-iotests: Explicit usage of Python3 (scripts without
    __main__)
  scripts: Explicit usage of Python 3 (scripts without __main__)
  tests/qemu-iotests/check: Only check for Python 3 interpreter

 scripts/analyse-9p-simpletrace.py                | 2 +-
 scripts/analyse-locks-simpletrace.py             | 2 +-
 scripts/checkpatch.pl                            | 6 ++++++
 scripts/decodetree.py                            | 2 +-
 scripts/device-crash-test                        | 2 +-
 scripts/kvm/kvm_flightrecorder                   | 2 +-
 scripts/minikconf.py                             | 1 +
 scripts/qapi-gen.py                              | 2 +-
 scripts/qmp/qemu-ga-client                       | 2 +-
 scripts/qmp/qmp                                  | 2 +-
 scripts/qmp/qmp-shell                            | 2 +-
 scripts/qmp/qom-fuse                             | 2 +-
 scripts/render_block_graph.py                    | 2 +-
 scripts/replay-dump.py                           | 2 +-
 scripts/simpletrace.py                           | 2 +-
 scripts/tracetool.py                             | 2 +-
 scripts/tracetool/__init__.py                    | 1 -
 scripts/tracetool/backend/__init__.py            | 1 -
 scripts/tracetool/backend/dtrace.py              | 1 -
 scripts/tracetool/backend/ftrace.py              | 1 -
 scripts/tracetool/backend/log.py                 | 1 -
 scripts/tracetool/backend/simple.py              | 1 -
 scripts/tracetool/backend/syslog.py              | 1 -
 scripts/tracetool/backend/ust.py                 | 1 -
 scripts/tracetool/format/__init__.py             | 1 -
 scripts/tracetool/format/c.py                    | 1 -
 scripts/tracetool/format/d.py                    | 1 -
 scripts/tracetool/format/h.py                    | 1 -
 scripts/tracetool/format/log_stap.py             | 1 -
 scripts/tracetool/format/simpletrace_stap.py     | 1 -
 scripts/tracetool/format/stap.py                 | 1 -
 scripts/tracetool/format/tcg_h.py                | 1 -
 scripts/tracetool/format/tcg_helper_c.py         | 1 -
 scripts/tracetool/format/tcg_helper_h.py         | 1 -
 scripts/tracetool/format/tcg_helper_wrapper_h.py | 1 -
 scripts/tracetool/format/ust_events_c.py         | 1 -
 scripts/tracetool/format/ust_events_h.py         | 1 -
 scripts/tracetool/transform.py                   | 1 -
 scripts/tracetool/vcpu.py                        | 1 -
 scripts/vmstate-static-checker.py                | 2 +-
 tests/acceptance/virtio_seg_max_adjust.py        | 1 -
 tests/acceptance/x86_cpu_model_versions.py       | 1 -
 tests/docker/travis.py                           | 2 +-
 tests/qapi-schema/test-qapi.py                   | 2 +-
 tests/qemu-iotests/030                           | 2 +-
 tests/qemu-iotests/040                           | 2 +-
 tests/qemu-iotests/041                           | 2 +-
 tests/qemu-iotests/044                           | 2 +-
 tests/qemu-iotests/045                           | 2 +-
 tests/qemu-iotests/055                           | 2 +-
 tests/qemu-iotests/056                           | 2 +-
 tests/qemu-iotests/057                           | 2 +-
 tests/qemu-iotests/065                           | 2 +-
 tests/qemu-iotests/093                           | 2 +-
 tests/qemu-iotests/096                           | 2 +-
 tests/qemu-iotests/118                           | 2 +-
 tests/qemu-iotests/124                           | 2 +-
 tests/qemu-iotests/129                           | 2 +-
 tests/qemu-iotests/132                           | 2 +-
 tests/qemu-iotests/136                           | 2 +-
 tests/qemu-iotests/139                           | 2 +-
 tests/qemu-iotests/147                           | 2 +-
 tests/qemu-iotests/148                           | 2 +-
 tests/qemu-iotests/149                           | 2 +-
 tests/qemu-iotests/151                           | 2 +-
 tests/qemu-iotests/152                           | 2 +-
 tests/qemu-iotests/155                           | 2 +-
 tests/qemu-iotests/163                           | 2 +-
 tests/qemu-iotests/165                           | 2 +-
 tests/qemu-iotests/169                           | 2 +-
 tests/qemu-iotests/194                           | 2 +-
 tests/qemu-iotests/196                           | 2 +-
 tests/qemu-iotests/199                           | 2 +-
 tests/qemu-iotests/202                           | 2 +-
 tests/qemu-iotests/203                           | 2 +-
 tests/qemu-iotests/205                           | 2 +-
 tests/qemu-iotests/206                           | 2 +-
 tests/qemu-iotests/207                           | 2 +-
 tests/qemu-iotests/208                           | 2 +-
 tests/qemu-iotests/209                           | 2 +-
 tests/qemu-iotests/210                           | 2 +-
 tests/qemu-iotests/211                           | 2 +-
 tests/qemu-iotests/212                           | 2 +-
 tests/qemu-iotests/213                           | 2 +-
 tests/qemu-iotests/216                           | 2 +-
 tests/qemu-iotests/218                           | 2 +-
 tests/qemu-iotests/219                           | 2 +-
 tests/qemu-iotests/222                           | 2 +-
 tests/qemu-iotests/224                           | 2 +-
 tests/qemu-iotests/228                           | 2 +-
 tests/qemu-iotests/234                           | 2 +-
 tests/qemu-iotests/235                           | 2 +-
 tests/qemu-iotests/236                           | 2 +-
 tests/qemu-iotests/237                           | 2 +-
 tests/qemu-iotests/238                           | 2 +-
 tests/qemu-iotests/242                           | 2 +-
 tests/qemu-iotests/245                           | 2 +-
 tests/qemu-iotests/246                           | 2 +-
 tests/qemu-iotests/248                           | 2 +-
 tests/qemu-iotests/254                           | 2 +-
 tests/qemu-iotests/255                           | 2 +-
 tests/qemu-iotests/256                           | 2 +-
 tests/qemu-iotests/257                           | 2 +-
 tests/qemu-iotests/258                           | 2 +-
 tests/qemu-iotests/260                           | 2 +-
 tests/qemu-iotests/262                           | 2 +-
 tests/qemu-iotests/264                           | 2 +-
 tests/qemu-iotests/266                           | 2 +-
 tests/qemu-iotests/277                           | 2 +-
 tests/qemu-iotests/280                           | 2 +-
 tests/qemu-iotests/281                           | 2 +-
 tests/qemu-iotests/check                         | 2 +-
 tests/qemu-iotests/nbd-fault-injector.py         | 2 +-
 tests/qemu-iotests/qcow2.py                      | 2 +-
 tests/qemu-iotests/qed.py                        | 2 +-
 tests/vm/basevm.py                               | 1 -
 tests/vm/centos                                  | 2 +-
 tests/vm/fedora                                  | 2 +-
 tests/vm/freebsd                                 | 2 +-
 tests/vm/netbsd                                  | 2 +-
 tests/vm/openbsd                                 | 2 +-
 tests/vm/ubuntu.i386                             | 2 +-
 122 files changed, 101 insertions(+), 120 deletions(-)
 mode change 100755 => 100644 tests/acceptance/virtio_seg_max_adjust.py
 mode change 100755 => 100644 tests/vm/basevm.py
```
#### [FYI PATCH 0/5] Missing TLB flushes
##### From: Paolo Bonzini <pbonzini@redhat.com>
From: Boris Ostrovsky <boris.ostrovsky@oracle.com>

```c
From patchwork Thu Jan 30 18:01:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11358513
Return-Path: <SRS0=dXSl=3T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67F131398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:02:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 44DD9214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 30 Jan 2020 18:02:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="VHjvC2MD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727695AbgA3SCC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 30 Jan 2020 13:02:02 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:54613 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727686AbgA3SCC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 30 Jan 2020 13:02:02 -0500
Received: by mail-wm1-f68.google.com with SMTP id g1so4791567wmh.4;
        Thu, 30 Jan 2020 10:02:01 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=SYieBB/2kuVcsp1riYZ+n5BLf07jGwls7F2V1rzJ3UY=;
        b=VHjvC2MDwl9sh5TlMQ3R5zp7aZFDa04ymIQepWEvPED2hYwGw7b3vcuccjQUp8lBqO
         x+cdljjnRAdkNRpmK+lCja97sGD21n4hd4ykycwRlQUMkOmLvro7sy90mGIRtsC5IFHG
         Sq7jBV/CVeY1HM3mvflTltaTMk6JroxMPeod8/ur1g3sZVL5vCBqzBP/lXHzjPiEv45u
         KT54Vp2rvIGOcnlaQpcwTLgJESDbjMr6EEyYyAsMLCeGl7gTmlS9D5h1a8JwzaIyTyVP
         iUbZu6Se09ZsuCJQCWzZfDtNLsC0Nns2u0DtoZzyryz+tJhSC6yXT9Q2A0Xka3SelWQX
         e1yA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=SYieBB/2kuVcsp1riYZ+n5BLf07jGwls7F2V1rzJ3UY=;
        b=D3rnpkegRRqT5q7tBEtQU7K+dRGP3iQVCMLKdzSt7tOl7wEWemDg4NBvZfsoaz3BBM
         eyy4lxuzPKc/E88btZb82shkULu500QDoRE7lXvK63iZGUE0FqWNlLTZtuu8Tj5WXJor
         nF9UY07Pe26qTTKWO/T36eNzUR5NjroVUheqg2vlPAXu5ejnNmRu0uz2vhyZQ8XQjLtU
         rj2BGugzcb8hR0NTyOA1gl8dAXtoGTfLSkdV8U0etLW7Dc5pZvj5M3xXCrBMKYU3DiWf
         BIquK5Vm1N3g/nyQMcgNNVR6U/aDCBQi3lAN3+TNO+UZkDeUm6dsKWanuuoHOyimeOKm
         nXNQ==
X-Gm-Message-State: APjAAAW7IO5KPeA96bixCWLeDNDImOyUClDyULXygz+NKa/lWb/CPvx8
        +j3xlYpf7Uf2fVDovTjlTP/+E6vPsPE=
X-Google-Smtp-Source: 
 APXvYqwk+4/JCgeGyjZ/mpDE7Vgne7VBWyta/l9CF3RrDc5EnDtWTmoFxk0VhAYlbmyR7r+tGxyimw==
X-Received: by 2002:a7b:cbd6:: with SMTP id n22mr7161001wmi.118.1580407320372;
        Thu, 30 Jan 2020 10:02:00 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 w19sm6956878wmc.22.2020.01.30.10.01.58
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 30 Jan 2020 10:01:59 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Subject: [FYI PATCH 0/5] Missing TLB flushes
Date: Thu, 30 Jan 2020 19:01:51 +0100
Message-Id: <1580407316-11391-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Boris Ostrovsky <boris.ostrovsky@oracle.com>

The KVM hypervisor may provide a guest with ability to defer remote TLB
flush when the remote VCPU is not running. When this feature is used,
the TLB flush will happen only when the remote VPCU is scheduled to run
again. This will avoid unnecessary (and expensive) IPIs.

Under certain circumstances, when a guest initiates such deferred action,
the hypervisor may miss the request. It is also possible that the guest
may mistakenly assume that it has already marked remote VCPU as needing
a flush when in fact that request had already been processed by the
hypervisor. In both cases this will result in an invalid translation
being present in a vCPU, potentially allowing accesses to memory locations
in that guest's address space that should not be accessible.

Note that only intra-guest memory is vulnerable.

The attached patches address both of these problems:
1. The first patch makes sure the hypervisor doesn't accidentally clear
guest's remote flush request
2. The rest of the patches prevent the race between hypervisor
acknowledging a remote flush request and guest issuing a new one.

Boris Ostrovsky (5):
  x86/kvm: Be careful not to clear KVM_VCPU_FLUSH_TLB bit
  x86/kvm: Introduce kvm_(un)map_gfn()
  x86/kvm: Cache gfn to pfn translation
  x86/KVM: Make sure KVM_VCPU_FLUSH_TLB flag is not missed
  x86/KVM: Clean up host's steal time structure

 arch/x86/include/asm/kvm_host.h |   4 +-
 arch/x86/kvm/x86.c              |  69 +++++++++++++++---------
 include/linux/kvm_host.h        |   5 ++
 include/linux/kvm_types.h       |   9 +++-
 virt/kvm/kvm_main.c             | 113 ++++++++++++++++++++++++++++++++++------
 5 files changed, 154 insertions(+), 46 deletions(-)
```
