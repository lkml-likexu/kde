

#### [PATCH v2 0/5] KVM: arm64: Assorted PMU emulation fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Oct  8 16:01:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11179821
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D22D18B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:01:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 33E38217D7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:01:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570550518;
	bh=hKiwaJhVxCSiCRF1bXZhTDlIgr8qrLaf2A0Ts8wmUUo=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=SQ0QZGB4XXNzxB6pxb8EpA0gzsJnJuD4YtR7b5JyeySOVm0eyE5mL+aWMOBhRD9ow
	 vChPcI6ntFobjoKsIWLuhlOs1VNCo8XJn681FjAWIhwPqFt0DgObpTZHztuaOdtnBC
	 vFhFjrjKxHzwfDvClzPuytddcuB1jxPiVUD9qePI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728459AbfJHQB5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 12:01:57 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:54549 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727970AbfJHQB5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Oct 2019 12:01:57 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iHrvs-0001rs-DQ; Tue, 08 Oct 2019 18:01:52 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Murray <andrew.murray@arm.com>
Subject: [PATCH v2 0/5] KVM: arm64: Assorted PMU emulation fixes
Date: Tue,  8 Oct 2019 17:01:23 +0100
Message-Id: <20191008160128.8872-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 mark.rutland@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, andrew.murray@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I recently came across a number of PMU emulation bugs, all which can
result in unexpected behaviours in an unsuspecting guest. The first
two patches already have been discussed on the list, but I'm including
them here as part of a slightly longer series.

The third patch is new as of v2, and fixes a bug preventing chained
events from ever being used.

The fourth patch is also new as of v2, and is an arm64 PMU change for
which I clearly don't know what I'm doing. I'd appreciate some
guidance from Will or Mark.

The last patch fixes an issue that has been here from day one, where
we confuse architectural overflow of a counter and perf sampling
period, and uses patch #4 to fix the issue.

I'l planning to send patches 1 through to 3 as fixes shortly, but I
expect the last two patches to require more discussions.

Marc Zyngier (5):
  KVM: arm64: pmu: Fix cycle counter truncation
  arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
  KVM: arm64: pmu: Set the CHAINED attribute before creating the
    in-kernel event
  arm64: perf: Add reload-on-overflow capability
  KVM: arm64: pmu: Reset sample period on overflow handling

 arch/arm64/include/asm/perf_event.h |  4 +++
 arch/arm64/kernel/perf_event.c      |  8 ++++-
 arch/arm64/kvm/sys_regs.c           |  4 +++
 virt/kvm/arm/pmu.c                  | 45 +++++++++++++++++++----------
 4 files changed, 45 insertions(+), 16 deletions(-)
```
#### [PATCH 0/3] selftests: kvm: improvements to VMX support check
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Oct  8 19:43:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11180049
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E258D1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 19:44:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CE1DC21924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 19:44:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730452AbfJHTnm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 15:43:42 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55416 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728465AbfJHTnm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 15:43:42 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 27CA2A44AF2;
        Tue,  8 Oct 2019 19:43:42 +0000 (UTC)
Received: from vitty.brq.redhat.com (ovpn-204-92.brq.redhat.com
 [10.40.204.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4396A5D6A7;
        Tue,  8 Oct 2019 19:43:40 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 0/3] selftests: kvm: improvements to VMX support check
Date: Tue,  8 Oct 2019 21:43:35 +0200
Message-Id: <20191008194338.24159-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.68]);
 Tue, 08 Oct 2019 19:43:42 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_dirty_log_test fails on AMD and this is no surprise as it is VMX
specific. Consolidate checks from other VMX tests into a library routine
and add a check to skip the test when !VMX.

Vitaly Kuznetsov (3):
  selftests: kvm: vmx_set_nested_state_test: don't check for VMX support
    twice
  selftests: kvm: consolidate VMX support checks
  selftests: kvm: vmx_dirty_log_test: skip the test when VMX is not
    supported

 tools/testing/selftests/kvm/include/x86_64/vmx.h    |  2 ++
 tools/testing/selftests/kvm/lib/x86_64/vmx.c        | 10 ++++++++++
 .../kvm/x86_64/vmx_close_while_nested_test.c        |  6 +-----
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c       |  2 ++
 .../kvm/x86_64/vmx_set_nested_state_test.c          | 13 ++-----------
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c      |  6 +-----
 6 files changed, 18 insertions(+), 21 deletions(-)
```
