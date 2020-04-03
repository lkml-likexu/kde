

#### [kvm-unit-tests PATCH v4 00/12] KVM: arm64: PMUv3 Event Counter Tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Fri Apr  3 07:13:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11471937
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7072C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4D7FD20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 07:13:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gucKaM+E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389010AbgDCHNn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 03:13:43 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:42073 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730759AbgDCHNn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 03:13:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585898021;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ozI3eRo5MHiGvv1ljzippiG2WaPze3ybClTx3Rcz8Hg=;
        b=gucKaM+Evw1VCrklP5gh2n9N8BqJbQmPOi5pwoknz0WvydlLR5uVc4MUt1BNgROOD18wnn
        AvK107NLQ3bAw2/v7vgeFRdJdhkRSrWF1Wn3FqwhNU7uiMNvRgCKgfo94e0TUR4PTwd9sN
        Xaoq0WeQ2GWxQamFoVvJPCbS5m69GWU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-378-2Z4fimH_O9u0RX99QlL5cg-1; Fri, 03 Apr 2020 03:13:37 -0400
X-MC-Unique: 2Z4fimH_O9u0RX99QlL5cg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B85568017F3;
        Fri,  3 Apr 2020 07:13:35 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-58.ams2.redhat.com [10.36.112.58])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2716948;
        Fri,  3 Apr 2020 07:13:29 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH v4 00/12] KVM: arm64: PMUv3 Event Counter Tests
Date: Fri,  3 Apr 2020 09:13:14 +0200
Message-Id: <20200403071326.29932-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
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
of odd and event counters. Fixes now are upstream.

Drew kindly provided "arm64: Provide read/write_sysreg_s".

All PMU tests can be launched with:
./run_tests.sh -g pmu
Tests also can be launched individually. For example:
./arm-run arm/pmu.flat -append 'pmu-chained-sw-incr'

With KVM:
- On TX2, I have some random failures due to MEM_ACCESS event
  measured with a great disparity. This is not observed on
  other machines I have access to.

The series can be found at:
https://github.com/eauger/kut/tree/pmu_event_counters_v4

History:
v3 -> v4:
- Drew reported that some report messages were repeated.
  This version makes sure all messages are different.

v2 -> v3:
- Took into account numerous comments from Drew
- Applied Andre's R-b when code has not changed too much
- Don't check PMCR.IMP anymore
- better handling of version
- put simple SW_INCR tests for easier TCG testing

v1 -> v2:
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

Andrew Jones (1):
  arm64: Provide read/write_sysreg_s

Eric Auger (11):
  arm: pmu: Let pmu tests take a sub-test parameter
  arm: pmu: Don't check PMCR.IMP anymore
  arm: pmu: Add a pmu struct
  arm: pmu: Introduce defines for PMU versions
  arm: pmu: Check Required Event Support
  arm: pmu: Basic event counter Tests
  arm: pmu: Test SW_INCR event count
  arm: pmu: Test chained counters
  arm: pmu: test 32-bit <-> 64-bit transitions
  arm: gic: Introduce gic_irq_set_clr_enable() helper
  arm: pmu: Test overflow interrupts

 arm/pmu.c              | 838 +++++++++++++++++++++++++++++++++++++++--
 arm/unittests.cfg      |  61 ++-
 lib/arm/asm/gic.h      |   4 +
 lib/arm/gic.c          |  31 ++
 lib/arm64/asm/sysreg.h |  17 +
 lib/bitops.h           |   3 +
 6 files changed, 917 insertions(+), 37 deletions(-)
```
