

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
#### [PATCH v2 0/5] KVM: s390: vsie: fixes and cleanups
##### From: David Hildenbrand <david@redhat.com>

```c
From patchwork Fri Apr  3 15:30:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11472993
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ED87F912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 15:31:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CC247207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 15:31:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HISUh9ln"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404268AbgDCPbD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 11:31:03 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:53809 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728203AbgDCPbD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 11:31:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585927862;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=oH2OHy+Eyviif1iebcrHo18si9PoFShEfkJbOhyf4JQ=;
        b=HISUh9lnLvk4QM0SD2MbZd9P4/7lWnvAaDY4Giz8iRLBdHG8jW1m1dOCrK3uuvy61oBR4g
        OtKvBw9/48HNk+PnaDpuDKfnTZ+99qqzyBZolbl477+CgZf5gYyCnwEQlBchK3ZmOgvDFj
        sY1ShPBcDUg9Xn30CChf4xOgA1WMRlc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-440-UbVvYl2_PIi2GI5z_52vtQ-1; Fri, 03 Apr 2020 11:30:58 -0400
X-MC-Unique: UbVvYl2_PIi2GI5z_52vtQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6082C190B2A2;
        Fri,  3 Apr 2020 15:30:57 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-112-213.ams2.redhat.com [10.36.112.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2AF0A26DC4;
        Fri,  3 Apr 2020 15:30:51 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        Vasily Gorbik <gor@linux.ibm.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>
Subject: [PATCH v2 0/5] KVM: s390: vsie: fixes and cleanups
Date: Fri,  3 Apr 2020 17:30:45 +0200
Message-Id: <20200403153050.20569-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some vsie/gmap fixes and two cleanups/improvements.

Patch #1 fixes an issue reported by Janosch. It was never observed so far,
because KVM usually doesn't use a region 1 table for it's guest (unless
memory would be exceeding something like 16 EB, which isn't even supported
by the HW). Older QEMU+KVM or other hypervisors can trigger this.

Patch #2 fixes a code path that probably was never taken and will most
probably not be taken very often in the future - unless somebody really
messes up the page tables for a guest (or writes a test for it). At some
point, a test case for this would be nice.

Patch #3 fixes a rare possible race. Don't think this is stable material.

Gave it some testing with my limited access to somewhat-fast s390x
machines. Booted a Linux kernel, supplying all possible number of
page table hiearchies.

v1 -> v2:
- "KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks"
-- Fix WARN_ON_ONCE
- "gmap_table_walk() simplifications"
-- Also init "table" directly

David Hildenbrand (5):
  KVM: s390: vsie: Fix region 1 ASCE sanity shadow address checks
  KVM: s390: vsie: Fix delivery of addressing exceptions
  KVM: s390: vsie: Fix possible race when shadowing region 3 tables
  KVM: s390: vsie: Move conditional reschedule
  KVM: s390: vsie: gmap_table_walk() simplifications

 arch/s390/kvm/vsie.c |  4 ++--
 arch/s390/mm/gmap.c  | 17 +++++++++++------
 2 files changed, 13 insertions(+), 8 deletions(-)
```
#### [PATCH 0/8] tools/vhost: Reset virtqueue on tests
##### From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>

```c
From patchwork Fri Apr  3 16:51:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
X-Patchwork-Id: 11473163
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 824C31392
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:51:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 605352080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 16:51:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ff4m51sA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2403996AbgDCQvf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 12:51:35 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:43579 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2403858AbgDCQve (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 12:51:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585932694;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=nhFm16Rn59ljHy8zT4BNa+1TatqX7wOcSX4H/Bklex4=;
        b=ff4m51sAAZVKHnOuFxX43uniOzhykFICXbEi9tNijM41/cOVxmj4DWUJnvv5eQEWFV/qGm
        dyLufyqMA7s2WroDSaclBfuNpke1EF8by7ehiDeln3S7SDgquXH0b/bZpUjgHeJcuYNHb3
        7OodOmBhefxGHOR4dKN7njFi4pgHqNQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-318-vq3TbPQyPVGdok5uH-fH2g-1; Fri, 03 Apr 2020 12:51:30 -0400
X-MC-Unique: vq3TbPQyPVGdok5uH-fH2g-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A4748100550D;
        Fri,  3 Apr 2020 16:51:28 +0000 (UTC)
Received: from eperezma.remote.csb (ovpn-113-28.ams2.redhat.com
 [10.36.113.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0D4AA18A85;
        Fri,  3 Apr 2020 16:51:23 +0000 (UTC)
From: =?utf-8?q?Eugenio_P=C3=A9rez?= <eperezma@redhat.com>
To: "Michael S. Tsirkin" <mst@redhat.com>
Cc: kvm list <kvm@vger.kernel.org>,
 "virtualization@lists.linux-foundation.org"
  <virtualization@lists.linux-foundation.org>,
 Linux Next Mailing List <linux-next@vger.kernel.org>, =?utf-8?q?Eugenio_P?=
	=?utf-8?q?=C3=A9rez?= <eperezma@redhat.com>,
 Stephen Rothwell <sfr@canb.auug.org.au>, Cornelia Huck <cohuck@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH 0/8] tools/vhost: Reset virtqueue on tests
Date: Fri,  3 Apr 2020 18:51:11 +0200
Message-Id: <20200403165119.5030-1-eperezma@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series add the tests used to validate the "vhost: Reset batched
descriptors on SET_VRING_BASE call" series, with a small change on the
reset code (delete an extra unneded reset on VHOST_SET_VRING_BASE).

They are based on the tests sent back them, the ones that were not
included (reasons in that thread). This series changes:

* Delete need to export the ugly function in virtio_ring, now all the
code is added in tools/virtio (except the one line fix).
* Add forgotten uses of vhost_vq_set_backend. Fix bad usage order in
vhost_test_set_backend.
* Drop random reset, not really needed.
* Minor changes updating tests code.

This serie is meant to be applied on top of
5de4e0b7068337cf0d4ca48a4011746410115aae in
git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git.

Eugenio Pérez (8):
  tools/virtio: fix virtio_test.c indentation
  vhost: Not cleaning batched descs in VHOST_SET_VRING_BASE ioctl
  vhost: Replace vq->private_data access by backend accesors
  vhost: Fix bad order in vhost_test_set_backend at enable
  tools/virtio: Use __vring_new_virtqueue in virtio_test.c
  tools/virtio: Extract virtqueue initialization in vq_reset
  tools/virtio: Reset index in virtio_test --reset.
  tools/virtio: Use tools/include/list.h instead of stubs

 drivers/vhost/test.c        |  8 ++---
 drivers/vhost/vhost.c       |  1 -
 tools/virtio/linux/kernel.h |  7 +----
 tools/virtio/linux/virtio.h |  5 ++--
 tools/virtio/virtio_test.c  | 58 +++++++++++++++++++++++++++----------
 tools/virtio/vringh_test.c  |  2 ++
 6 files changed, 51 insertions(+), 30 deletions(-)
```
#### [PATCH v2 0/2] selftests: kvm: Introduce the mem_slot_test test
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Fri Apr  3 17:24:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11473197
Return-Path: <SRS0=Xk8+=5T=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9237E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 17:24:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 711BB207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  3 Apr 2020 17:24:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Fki8HQR0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391143AbgDCRYr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 3 Apr 2020 13:24:47 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:40656 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2391126AbgDCRYr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 3 Apr 2020 13:24:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585934686;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=TeNYEnMMfU3AiH0HRgQNWv1IhmQIdH3VbtTA4I/7zoQ=;
        b=Fki8HQR0STTDXI20u7bY8oCYF/PdS/ozLY2QUReJdm40yfW/9UoLa90cHmWLvww0x0M9h7
        PitlSLEXbfCO4Gg6PayfZ0ygXl04TYMth4G5xZQp/PAJUWbAykpITHgZ8/NS5IuFeQQXSr
        SJic80bN1fd7shHKx5KJLIkfCe0GYrc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-77-AkRCr9DvPSGybudoVX-j4A-1; Fri, 03 Apr 2020 13:24:39 -0400
X-MC-Unique: AkRCr9DvPSGybudoVX-j4A-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 304B7100550D;
        Fri,  3 Apr 2020 17:24:38 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 135E05C1B0;
        Fri,  3 Apr 2020 17:24:30 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH v2 0/2] selftests: kvm: Introduce the mem_slot_test test
Date: Fri,  3 Apr 2020 14:24:26 -0300
Message-Id: <20200403172428.15574-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a new KVM selftest (mem_slot_test) that goal
is to verify memory slots can be added up to the maximum allowed. An
extra slot is attempted which should occur on error.

The patch 01 is needed so that the VM fd can be accessed from the
test code (for the ioctl call attempting to add an extra slot).

I ran the test successfully on x86_64, aarch64, and s390x.  This
is why it is enabled to build on those arches.

v1: https://lore.kernel.org/kvm/20200330204310.21736-1-wainersm@redhat.com

Changes v1 -> v2:
 - Rebased to queue
 - vm_get_fd() returns int instead of unsigned int (patch 01) [drjones]
 - Removed MEM_REG_FLAGS and GUEST_VM_MODE defines [drjones]
 - Replaced DEBUG() with pr_info() [drjones]
 - Calculate number of guest pages with vm_calc_num_guest_pages()
   [drjones]
 - Using memory region of 1 MB sized (matches mininum needed
   for s390x)
 - Removed the increment of guest_addr after the loop [drjones]
 - Added assert for the errno when adding a slot beyond-the-limit [drjones]
 - Prefer KVM_MEM_READONLY flag but on s390x it switch to KVM_MEM_LOG_DIRTY_PAGES,
   so ensure the coverage of both flags. Also somewhat tests the KVM_CAP_READONLY_MEM capability check [drjones]
 - Moved the test logic to test_add_max_slots(), this allows to more easily add new cases in the "suite".

Wainer dos Santos Moschetta (2):
  selftests: kvm: Add vm_get_fd() in kvm_util
  selftests: kvm: Add mem_slot_test test

 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  3 +
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  5 ++
 tools/testing/selftests/kvm/mem_slot_test.c   | 85 +++++++++++++++++++
 5 files changed, 95 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/mem_slot_test.c
```
