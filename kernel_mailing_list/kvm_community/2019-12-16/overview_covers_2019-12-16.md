

#### [kvm-unit-tests PATCH 00/16] arm/arm64: Add ITS tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Dec 16 14:02:19 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11294245
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE04813B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 14:03:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8BB2E20684
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 14:03:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Bwdnvnv/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728070AbfLPODf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 09:03:35 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:43262 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727906AbfLPODf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 09:03:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576505014;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=A9SY0krHFjydIQmqzREy9ABCAZgjAKMUQ2ClrNvBGYM=;
        b=Bwdnvnv/tMRPue3PDfNYWJSBBNnoBsnYqXmgvVCpeGjmYlH5aiaZojBJAkIJuLGHBtD6zr
        x/ZCsekgESdwVLG8VAUoL7GfmcWhEwBrYb6yFHSwW6TIa7G9NIA4gz1nbrQhpQ+4XPtLJP
        l2JJSrgmgok3x7yp/zRx3fzxHaNEV3I=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-5-KZ0hcHf3OsqMUOdqJHz5Tw-1; Mon, 16 Dec 2019 09:03:25 -0500
X-MC-Unique: KZ0hcHf3OsqMUOdqJHz5Tw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B81C9100550E;
        Mon, 16 Dec 2019 14:03:22 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-117.ams2.redhat.com
 [10.36.116.117])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 60B4268860;
        Mon, 16 Dec 2019 14:03:16 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, yuzenghui@huawei.com,
        alexandru.elisei@arm.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 00/16] arm/arm64: Add ITS tests
Date: Mon, 16 Dec 2019 15:02:19 +0100
Message-Id: <20191216140235.10751-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a revival of an RFC series sent in Dec 2016 [1].
Given the amount of code and the lack of traction at that time,
I haven't respinned until now. However a recent bug found around
the ITS migration convinced me that this work may deserve to be
respinned and enhanced.

Tests exercise main ITS commands and also test migration.
With the migration framework, we are able to trigger the
migration from guest and that is very practical actually.

What is particular with the ITS programming is that most of
the commands are passed through queues and there is real error
handling. Invalid commands are just ignored and that is not
really tester friendly.

This series includes Andre's patch: "arm: gic: Provide
per-IRQ helper functions" [2]

The series can be fount at:
https://github.com/eauger/kut/tree/its-v1

Best Regards

Eric

[1] [kvm-unit-tests RFC 00/15] arm/arm64: add ITS framework
    https://lists.gnu.org/archive/html/qemu-devel/2016-12/msg00575.html

[2] [kvm-unit-tests PATCH 00/17] arm: gic: Test SPIs and interrupt groups
    https://patchwork.kernel.org/cover/11234975/

For ITS migration testing use:
./run_tests.sh -g migration (blocks on TCG but I think it is beyond the
scope of that series)

For other ITS tests:
./run_tests.sh -g its

non migration tests can be launched invidually. For instance:
./arm-run arm/gic.flat -smp 8 -append 'its-trigger'

Andre Przywara (1):
  arm: gic: Provide per-IRQ helper functions

Eric Auger (15):
  libcflat: Add other size defines
  arm/arm64: gic: Introduce setup_irq() helper
  arm/arm64: gicv3: Add some re-distributor defines
  arm/arm64: ITS: Introspection tests
  arm/arm64: ITS: Test BASER
  arm/arm64: ITS: Set the LPI config and pending tables
  arm/arm64: ITS: Init the command queue
  arm/arm64: ITS: Enable/Disable LPIs at re-distributor level
  arm/arm64: ITS: its_enable_defaults
  arm/arm64: ITS: Device and collection Initialization
  arm/arm64: ITS: commands
  arm/arm64: ITS: INT functional tests
  arm/run: Allow Migration tests
  arm/arm64: ITS: migration tests
  arm/arm64: ITS: pending table migration test

 arm/Makefile.common        |   3 +-
 arm/gic.c                  | 447 +++++++++++++++++++++++++++++++++--
 arm/run                    |   2 +-
 arm/unittests.cfg          |  39 ++++
 lib/arm/asm/gic-v3-its.h   | 217 +++++++++++++++++
 lib/arm/asm/gic-v3.h       |  87 +++++++
 lib/arm/asm/gic.h          |  13 ++
 lib/arm/gic-v3-its-cmd.c   | 462 +++++++++++++++++++++++++++++++++++++
 lib/arm/gic-v3-its.c       | 354 ++++++++++++++++++++++++++++
 lib/arm/gic.c              | 132 ++++++++++-
 lib/arm/io.c               |  13 ++
 lib/arm64/asm/gic-v3-its.h |   1 +
 lib/libcflat.h             |   3 +
 13 files changed, 1745 insertions(+), 28 deletions(-)
 create mode 100644 lib/arm/asm/gic-v3-its.h
 create mode 100644 lib/arm/gic-v3-its-cmd.c
 create mode 100644 lib/arm/gic-v3-its.c
 create mode 100644 lib/arm64/asm/gic-v3-its.h
```
#### [kvm-unit-tests PATCH 00/10] KVM: arm64: PMUv3 Event Counter Tests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Dec 16 20:47:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11295219
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 419FA138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:48:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E50724683
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:48:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LAd5XuBo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727415AbfLPUsP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 15:48:15 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:22523 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727324AbfLPUsM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 15:48:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1576529290;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+Fxv/08Xa0VbcqCSvsm0VgrWIKaPNFsllFhCVnw+YLI=;
        b=LAd5XuBoJG0V96QCFCi97ZHg6Um/NTWIVOwNmbZsNWJYj9CS5SRsy0QJ4C2c8+6F8KsA5i
        bgSKhLmDBYUWs0butAIbkl/0etKQEfBclrTfksfWcYk/WdHJ5oIT3i6nalIQecBMCnjgnx
        HU371tiYwqi51uy+o4iVYWUXhXD1N9E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-327-_3L8DJ-vNPWrTcGnvlpMrw-1; Mon, 16 Dec 2019 15:48:09 -0500
X-MC-Unique: _3L8DJ-vNPWrTcGnvlpMrw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9B4708D811D;
        Mon, 16 Dec 2019 20:48:07 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-116-117.ams2.redhat.com
 [10.36.116.117])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6C11B5D9C9;
        Mon, 16 Dec 2019 20:48:01 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com, maz@kernel.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, qemu-arm@nongnu.org
Cc: drjones@redhat.com, andrew.murray@arm.com, andre.przywara@arm.com,
        peter.maydell@linaro.org, alexandru.elisei@arm.com
Subject: [kvm-unit-tests PATCH 00/10] KVM: arm64: PMUv3 Event Counter Tests
Date: Mon, 16 Dec 2019 21:47:47 +0100
Message-Id: <20191216204757.4020-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
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
of odd and event counters.

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
- Problems were reported upstream.
With TCG:
- pmu-event-introspection is failing due to missing required events
  (we may remove this from TCG actually)
- chained-sw-incr also fails. I haven't investigated yet.

The series can be found at:
https://github.com/eauger/kut/tree/pmu_event_counters_v1

History:
v1 -> v2:
- Use new report() proto
- Style cleanup
- do not warn about ARM spec recommendations
- add a comment about PMCEID0/1 splits

Andre Przywara (1):
  arm: gic: Provide per-IRQ helper functions

Andrew Jones (1):
  arm64: Provide read/write_sysreg_s

Eric Auger (8):
  arm: pmu: Let pmu tests take a sub-test parameter
  arm: pmu: Add a pmu struct
  arm: pmu: Check Required Event Support
  arm: pmu: Basic event counter Tests
  arm: pmu: Test chained counter
  arm: pmu: test 32-bit <-> 64-bit transitions
  arm/arm64: gic: Introduce setup_irq() helper
  arm: pmu: Test overflow interrupts

 arm/gic.c              |  24 +-
 arm/pmu.c              | 783 ++++++++++++++++++++++++++++++++++++++++-
 arm/unittests.cfg      |  55 ++-
 lib/arm/asm/gic-v3.h   |   2 +
 lib/arm/asm/gic.h      |  12 +
 lib/arm/gic.c          | 101 ++++++
 lib/arm64/asm/sysreg.h |  11 +
 7 files changed, 950 insertions(+), 38 deletions(-)
```
#### [PATCH v10 Kernel 0/5] KABIs to support migration for VFIO devices 
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Mon Dec 16 20:21:35 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11295249
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DF57138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:50:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0B5C3218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 20:50:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Jp084s/E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726561AbfLPUu3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 15:50:29 -0500
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:15772 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726515AbfLPUu3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 15:50:29 -0500
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df7ee0b0000>; Mon, 16 Dec 2019 12:50:19 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Mon, 16 Dec 2019 12:50:27 -0800
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Mon, 16 Dec 2019 12:50:27 -0800
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 20:50:27 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 16 Dec 2019 20:50:20 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH v10 Kernel 0/5] KABIs to support migration for VFIO devices 
Date: Tue, 17 Dec 2019 01:51:35 +0530
Message-ID: <1576527700-21805-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576529419; bh=BgOwv2o4CTCcQspt5FGClKR4D3uCDj92wKjF5nLknrg=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=Jp084s/EeFOzyAT6SoeUUude2Rd7H/e1Ds++cHv+SAHcIUlCgh/y7nQFL5/RF7v0K
         HlCKpeXmJWRV4zzP7FSMXKNvucYDLTw6d0IRuq0qHD9sDi/43KgQgmnPMlvHYsUHDv
         faF8j0475HTsr2TSjR1gqTa0w3tS12ROgv/DjU8aWtpAcfv9nChKsMJmu5/CJ96lQz
         sVh0OQcszBZcsMrqiA7oY1bqaMjXhtcohDM5J5+T5v/s8zluvZdBAjfjHvdEKOrTC1
         dp3STCZHSWnJeV5E44PyVzSlDqrotFGezUb0xshxgHYVSRZPFm+2ohPbWxHd2QLuIv
         3WzUu2uCMseHQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* New IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
  respect to IOMMU container rather than per device. All pages pinned by
  vendor driver through vfio_pin_pages external API has to be marked as
  dirty during  migration. When IOMMU capable device is present in the
  container and all pages are pinned and mapped, then all pages are marked
  dirty.
  When there are CPU writes, CPU dirty page tracking can identify dirtied
  pages, but any page pinned by vendor driver can also be written by
  device. As of now there is no device which has hardware support for
  dirty page tracking. So all pages which are pinned should be considered
  as dirty.
  This ioctl is also used to start dirty pages tracking for unpinned pages
  while migration is active and device is running. These tracked unpinned
  pages information is cleaned on dirty bitmap read from VFIO application
  or if migration is failed or cancelled and unpinned pages tracking is
  stopped.
* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

If IOMMU capable device is present in the container, then all pages are
marked dirty. Need to think smart way to know if IOMMU capable device's
driver is smart to report pages to be marked dirty by pinning those pages
externally.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v9 -> v10:
- Updated existing VFIO_IOMMU_UNMAP_DMA ioctl to get dirty pages bitmap
  during unmap while migration is active
- Added flag in VFIO_IOMMU_GET_INFO to indicate driver support dirty page
  tracking.
- If iommu_mapped, mark all pages dirty.
- Added unpinned pages tracking while migration is active.
- Updated comments for migration device state structure with bit
  combination table and state transition details.

v8 -> v9:
- Split patch set in 2 sets, Kernel and QEMU.
- Dirty pages bitmap is queried from IOMMU container rather than from
  vendor driver for per device. Added 2 ioctls to achieve this.

v7 -> v8:
- Updated comments for KABI
- Added BAR address validation check during PCI device's config space load
  as suggested by Dr. David Alan Gilbert.
- Changed vfio_migration_set_state() to set or clear device state flags.
- Some nit fixes.

v6 -> v7:
- Fix build failures.

v5 -> v6:
- Fix build failure.

v4 -> v5:
- Added decriptive comment about the sequence of access of members of
  structure vfio_device_migration_info to be followed based on Alex's
  suggestion
- Updated get dirty pages sequence.
- As per Cornelia Huck's suggestion, added callbacks to VFIODeviceOps to
  get_object, save_config and load_config.
- Fixed multiple nit picks.
- Tested live migration with multiple vfio device assigned to a VM.

v3 -> v4:
- Added one more bit for _RESUMING flag to be set explicitly.
- data_offset field is read-only for user space application.
- data_size is read for every iteration before reading data from migration,
  that is removed assumption that data will be till end of migration
  region.
- If vendor driver supports mappable sparsed region, map those region
  during setup state of save/load, similarly unmap those from cleanup
  routines.
- Handles race condition that causes data corruption in migration region
  during save device state by adding mutex and serialiaing save_buffer and
  get_dirty_pages routines.
- Skip called get_dirty_pages routine for mapped MMIO region of device.
- Added trace events.
- Split into multiple functional patches.

v2 -> v3:
- Removed enum of VFIO device states. Defined VFIO device state with 2
  bits.
- Re-structured vfio_device_migration_info to keep it minimal and defined
  action on read and write access on its members.

v1 -> v2:
- Defined MIGRATION region type and sub-type which should be used with
  region type capability.
- Re-structured vfio_device_migration_info. This structure will be placed
  at 0th offset of migration region.
- Replaced ioctl with read/write for trapped part of migration region.
- Added both type of access support, trapped or mmapped, for data section
  of the region.
- Moved PCI device functions to pci file.
- Added iteration to get dirty page bitmap until bitmap for all requested
  pages are copied.

Thanks,
Kirti



Kirti Wankhede (5):
  vfio: KABI for migration interface for device state
  vfio iommu: Adds flag to indicate dirty pages tracking capability
    support
  vfio iommu: Add ioctl defination for dirty pages tracking.
  vfio iommu: Implementation of ioctl to for dirty pages tracking.
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap

 drivers/vfio/vfio_iommu_type1.c | 276 +++++++++++++++++++++++++++++++++++++---
 include/uapi/linux/vfio.h       | 240 +++++++++++++++++++++++++++++++++-
 2 files changed, 499 insertions(+), 17 deletions(-)
```
#### [PATCH 0/9] Create a userfaultfd demand paging test
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Mon Dec 16 21:35:23 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11295327
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 916AA109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:35:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6EFD724672
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:35:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="cLMpQGkx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727313AbfLPVfq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 16:35:46 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:50734 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726764AbfLPVfq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 16:35:46 -0500
Received: by mail-pg1-f201.google.com with SMTP id d129so5368324pgc.17
        for <kvm@vger.kernel.org>; Mon, 16 Dec 2019 13:35:46 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=cLMpQGkx99eeWLH4P/unEkS15oJ0X5gTpKr0Ot5VrGyjOzB4dA0ifIETD5xPnL915T
         rubBQ1Z1iW4qP8ZPAFTNHDSpa1zHhugbJ2QxmSBGJ8YFQSbzxHjfKNHTdoja8vQT2IGs
         ZJ9gn+5y5Ern0CrQyWiOXApsJgUmCFVLDPffnLDVVzBJuidyMrKqQVRQnBM8tnVfAagh
         afrkhSTDsBVhP4jgntZuieMwkliL0ZvcoC6Mlo8Oj52LTnAulg5T+H8eQl5xK6xNjN2+
         jtpvhLNqUrXAu9q2trjCcLueT55qoIgDlBNl9WNltONfRe97/+D2FG+d2akzZiwxjJPq
         fs/A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=Jhi8WAD7OVGPH/d223gy3SdnTHZOC0OV08AbsE0JEv53x3i9bCs57ixNozGDTtgQk+
         F3A9rJd0S2FD4SeDxN8qWjkTf9iug83bOiTK6FgJ+0XwIvRSGk/l1F0LtAagZZOgV9ow
         T2717uhEWVplpa7BgVPSrpGXi48R4q8WJ59Ey3+AoFWqhqR50rMZX3SuqdTLG0dHeGLB
         WaFJabpBMYD4StRPhCzVKbpcNKQLkOClbbIC9pvlzQsgvgd2/4pr5zCNjZMjj9udJXeY
         RjY9u0PWmG/kSExhfYPLsBfBUkKMIqfuYyskD0XWSLVUi0G6GfnP1vGs1TLQcqQ0dA2O
         ZAQQ==
X-Gm-Message-State: APjAAAVdZTYF8XWoqWRgMfnS2JX6zHYrNucKRxxXB9RX53Lc7SYEtGe0
        7t4/6jVQ+YxvbczTEI9m9ps3b5FsTJu2
X-Google-Smtp-Source: 
 APXvYqy1p58uD7ILOXRlPnATDG1C2VyIQV8EfLRJI2x+ZgT/v8x5ksiTotwGpJiUF6/nvEUtv7a0zUt3NmVO
X-Received: by 2002:a63:b642:: with SMTP id v2mr4217832pgt.126.1576532145784;
 Mon, 16 Dec 2019 13:35:45 -0800 (PST)
Date: Mon, 16 Dec 2019 13:35:23 -0800
Message-Id: <20191216213532.91237-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH 0/9] Create a userfaultfd demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
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
#### [PATCH v3 0/8] Create a userfaultfd demand paging test
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Mon Dec 16 21:38:53 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 11295369
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12CA26C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:39:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E4A1D24676
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 21:39:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tNj7oz/O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727516AbfLPVjG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 16:39:06 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:38755 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726681AbfLPVjF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 16:39:05 -0500
Received: by mail-pg1-f201.google.com with SMTP id l13so5968782pgt.5
        for <kvm@vger.kernel.org>; Mon, 16 Dec 2019 13:39:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=tNj7oz/OwoSNeC7zluPeALLNBPcWJXHClCBomAaTTJ3r1XoRHk4FzXlifGIQxkFHwr
         YyUiRjCh4I9ahZnOEgsvxBqjDsxM1kSxy/7UNJyu4T69g7p3dzMg6CzTOzSGAFXX/+Yq
         2aQeBvyGrS/w2jF4cwiKGr0dBjCSaj97giU1sSky3b3JJCv6rwsKPHYwSaeeWYauS7G2
         iSlKKO8bKmJxFWPLEmxj1PSSSe8kW4JVV5AmGyfbs6JIflu6e4EHrCeG+DRIVCC44dS7
         B1Kcbt1NsVz0gQx+6wyMRS3BAAlTsuwh3OQodCFgJvnK1535qy0qoZX2wE9esYJi1Yzr
         B//A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=flMQx0RQ+tn1L0OZWy96vlecDFYT8pwNVqw/lok2bBY=;
        b=UVR2iALeRV6PBRAVpjePfdRD2rh1YQ/TIwg82aivDXDJyaG7yU15Z/vVZv9IOJT5Pq
         Ogl9WCS1zEf6eYMxb0RLryv8/dR5M5+TtdAsIIQiTb+8cndeuAeBlf8Vefse3+h9JEgU
         XWKvuoO9qPTpOuInb4+R1xSdulE5XWcV9/56tdA3ST/LWPChZohjv58O4+dMvda1JIoW
         jX9lQKqD0faRaldEChVjkifcL2Pez95rFS2nb4XK+wpRAenQ3EyJereqxKHImoEfyljU
         LWzTxJGCKKDZJZm0PakMhTHuOHFCyjTLGp5990zxIrmBUkBtc0OnyNu4HHOzyaHt8lG1
         Qg2w==
X-Gm-Message-State: APjAAAVQD2ordlfxFjNUHUAww0k/Puv5LKjCnRIrKg/q2NePyrQFniMu
        qfHb2xGiq6ecAg5alJSbQrEYYusZGt0w
X-Google-Smtp-Source: 
 APXvYqyt7PiZ8I6H4u3XH7x8jvxymQ4VP2vS+iyUjYUqs1LQFO+Fm+X+YTzQ1i0lIBpLid8KhiK0ug3fKcWp
X-Received: by 2002:a65:6216:: with SMTP id
 d22mr20828964pgv.437.1576532345144;
 Mon, 16 Dec 2019 13:39:05 -0800 (PST)
Date: Mon, 16 Dec 2019 13:38:53 -0800
Message-Id: <20191216213901.106941-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.1.735.g03f4e72817-goog
Subject: [PATCH v3 0/8] Create a userfaultfd demand paging test
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Cannon Matthews <cannonmatthews@google.com>,
        Peter Xu <peterx@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Ben Gardon <bgardon@google.com>
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
#### [PATCH v11 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Mon Dec 16 22:25:12 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11295983
Return-Path: <SRS0=hJeD=2G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5ACF86C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 22:30:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22A9821835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 16 Dec 2019 22:30:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="rzU7HVYF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727647AbfLPWZm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Dec 2019 17:25:42 -0500
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:11884 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727438AbfLPWZl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Dec 2019 17:25:41 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5df8045b0000>; Mon, 16 Dec 2019 14:25:31 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Mon, 16 Dec 2019 14:25:40 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Mon, 16 Dec 2019 14:25:40 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 22:25:39 +0000
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 16 Dec
 2019 22:25:39 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 16 Dec 2019 22:25:39 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5df804630001>; Mon, 16 Dec 2019 14:25:39 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 "Mauro Carvalho Chehab" <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, "Paul Mackerras" <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH v11 00/25] mm/gup: track dma-pinned pages: FOLL_PIN
Date: Mon, 16 Dec 2019 14:25:12 -0800
Message-ID: <20191216222537.491123-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1576535131; bh=kXZgebWOzv1eD/Ow2mzRQKWqAbiWjhBemb2nahCMdfs=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=rzU7HVYFkQqLDEekcbNlZ7U9kWPrLZdc8v5rOtl3A/lvoezqPcu+V0KtJFNgfPPsc
         6DHoc0ogw3MwkbgdOUoUJcEMpknUsr0Gy51jZVrUKOjsry7e+Ygpfzym1D5BUlG5oP
         9puJA+Q5DJeVeEJ9McmJCEuT5wqguoEAHJcWyRSb4227weMCpnyLENCfFe2Lj0xD5o
         Qeb0SzZGjvV1Gttwrq9R/yC2rDSBuNXuDYyeHyAoDmYNjuGLcMW5R+xuGezgtVN86U
         uOfXfLZsswxEFeodfLwN8oAPQ1N7jhZH6+T3di/eHdxkJhuG6eh+wUZc4HbZF4xXvG
         VKc61q3+Yatpg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This implements an API naming change (put_user_page*() -->
unpin_user_page*()), and also implements tracking of FOLL_PIN pages. It
extends that tracking to a few select subsystems. More subsystems will
be added in follow up work.

Christoph Hellwig, a point of interest:

a) I've moved the bulk of the code out of the inline functions, as
   requested, for the devmap changes (patch 4: "mm: devmap: refactor
   1-based refcounting for ZONE_DEVICE pages").

Changes since v10: Remaining fixes resulting from Jan Kara's reviews:

* Shifted to using the sign bit in page_dma_pinned() to allow accurate
  results even in the overflow case. See the comments in that routine
  for details. This allowed getting rid of the new
  page_ref_zero_or_close_to_bias_overflow(), in favor of a simple
  sign check via "page_ref_count() <= 0").

* Simplified some of the huge_memory.c changes, and simplified a gup.c
  WARN invocation.

* Now using a standard -ENOMEM for most try_grab_page() failures.

* Got rid of tabs in the comment headers (I had thought they were
  required there, but it's actually the reverse: they are not
  allowed there).

* Rebased against 5.5-rc2 and retested.

* Added Jan Kara's reviewed-by tag for patch 23 (the main patch of the
  series).

Changes since v9: Fixes resulting from Jan Kara's and Jonathan Corbet's
reviews:

* Removed reviewed-by tags from the "mm/gup: track FOLL_PIN pages" (those
  were improperly inherited from the much smaller refactoring patch that
  was merged into it).

* Made try_grab_compound_head() and try_grab_page() behavior similar in
  their behavior with flags, in order to avoid "gotchas" later.

* follow_trans_huge_pmd(): moved the try_grab_page() to earlier in the
  routine, in order to avoid having to undo mlock_vma_page().

* follow_hugetlb_page(): removed a refcount overflow check that is now
  extraneous (and weaker than what try_grab_page() provides a few lines
  further down).

* Fixed up two Documentation flaws, pointed out by Jonathan Corbet's
  review.

Changes since v8:

* Merged the "mm/gup: pass flags arg to __gup_device_* functions" patch
  into the "mm/gup: track FOLL_PIN pages" patch, as requested by
  Christoph and Jan.

* Changed void grab_page() to bool try_grab_page(), and handled errors
  at the call sites. (From Jan's review comments.) try_grab_page()
  attempts to avoid page refcount overflows, even when counting up with
  GUP_PIN_COUNTING_BIAS increments.

* Fixed a bug that I'd introduced, when changing a BUG() to a WARN().

* Added Jan's reviewed-by tag to the " mm/gup: allow FOLL_FORCE for
  get_user_pages_fast()" patch.

* Documentation: pin_user_pages.rst: fixed an incorrect gup_benchmark
  invocation, left over from the pin_longterm days, spotted while preparing
  this version.

* Rebased onto today's linux.git (-rc1), and re-tested.

Changes since v7:

* Rebased onto Linux 5.5-rc1

* Reworked the grab_page() and try_grab_compound_head(), for API
  consistency and less diffs (thanks to Jan Kara's reviews).

* Added Leon Romanovsky's reviewed-by tags for two of the IB-related
  patches.

* patch 4 refactoring changes, as mentioned above.

There is a git repo and branch, for convenience:

    git@github.com:johnhubbard/linux.git pin_user_pages_tracking_v8

For the remaining list of "changes since version N", those are all in
v7, which is here:

  https://lore.kernel.org/r/20191121071354.456618-1-jhubbard@nvidia.com

============================================================
Overview:

This is a prerequisite to solving the problem of proper interactions
between file-backed pages, and [R]DMA activities, as discussed in [1],
[2], [3], and in a remarkable number of email threads since about
2017. :)

A new internal gup flag, FOLL_PIN is introduced, and thoroughly
documented in the last patch's Documentation/vm/pin_user_pages.rst.

I believe that this will provide a good starting point for doing the
layout lease work that Ira Weiny has been working on. That's because
these new wrapper functions provide a clean, constrained, systematically
named set of functionality that, again, is required in order to even
know if a page is "dma-pinned".

In contrast to earlier approaches, the page tracking can be
incrementally applied to the kernel call sites that, until now, have
been simply calling get_user_pages() ("gup"). In other words, opt-in by
changing from this:

    get_user_pages() (sets FOLL_GET)
    put_page()

to this:
    pin_user_pages() (sets FOLL_PIN)
    unpin_user_page()

============================================================
Testing:

* I've done some overall kernel testing (LTP, and a few other goodies),
  and some directed testing to exercise some of the changes. And as you
  can see, gup_benchmark is enhanced to exercise this. Basically, I've
  been able to runtime test the core get_user_pages() and
  pin_user_pages() and related routines, but not so much on several of
  the call sites--but those are generally just a couple of lines
  changed, each.

  Not much of the kernel is actually using this, which on one hand
  reduces risk quite a lot. But on the other hand, testing coverage
  is low. So I'd love it if, in particular, the Infiniband and PowerPC
  folks could do a smoke test of this series for me.

  Runtime testing for the call sites so far is pretty light:

    * io_uring: Some directed tests from liburing exercise this, and
                they pass.
    * process_vm_access.c: A small directed test passes.
    * gup_benchmark: the enhanced version hits the new gup.c code, and
                     passes.
    * infiniband: ran "ib_write_bw", which exercises the umem.c changes,
                  but not the other changes.
    * VFIO: compiles (I'm vowing to set up a run time test soon, but it's
                      not ready just yet)
    * powerpc: it compiles...
    * drm/via: compiles...
    * goldfish: compiles...
    * net/xdp: compiles...
    * media/v4l2: compiles...

[1] Some slow progress on get_user_pages() (Apr 2, 2019): https://lwn.net/Articles/784574/
[2] DMA and get_user_pages() (LPC: Dec 12, 2018): https://lwn.net/Articles/774411/
[3] The trouble with get_user_pages() (Apr 30, 2018): https://lwn.net/Articles/753027/

Dan Williams (1):
  mm: Cleanup __put_devmap_managed_page() vs ->page_free()

John Hubbard (24):
  mm/gup: factor out duplicate code from four routines
  mm/gup: move try_get_compound_head() to top, fix minor issues
  mm: devmap: refactor 1-based refcounting for ZONE_DEVICE pages
  goldish_pipe: rename local pin_user_pages() routine
  mm: fix get_user_pages_remote()'s handling of FOLL_LONGTERM
  vfio: fix FOLL_LONGTERM use, simplify get_user_pages_remote() call
  mm/gup: allow FOLL_FORCE for get_user_pages_fast()
  IB/umem: use get_user_pages_fast() to pin DMA pages
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  IB/{core,hw,umem}: set FOLL_PIN via pin_user_pages*(), fix up ODP
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  media/v4l2-core: pin_user_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_user_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_user_pages() and put_user_page()
  mm/gup_benchmark: use proper FOLL_WRITE flags instead of hard-coding
    "1"
  mm, tree-wide: rename put_user_page*() to unpin_user_page*()
  mm/gup: track FOLL_PIN pages
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage

 Documentation/core-api/index.rst            |   1 +
 Documentation/core-api/pin_user_pages.rst   | 232 ++++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  10 +-
 drivers/gpu/drm/via/via_dmablit.c           |   6 +-
 drivers/infiniband/core/umem.c              |  19 +-
 drivers/infiniband/core/umem_odp.c          |  13 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   8 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   4 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   8 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   4 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   4 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |   8 +-
 drivers/nvdimm/pmem.c                       |   6 -
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +-
 drivers/vfio/vfio_iommu_type1.c             |  35 +-
 fs/io_uring.c                               |   6 +-
 include/linux/mm.h                          | 155 ++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 626 +++++++++++++++-----
 mm/gup_benchmark.c                          |  74 ++-
 mm/huge_memory.c                            |  29 +-
 mm/hugetlb.c                                |  38 +-
 mm/memremap.c                               |  76 ++-
 mm/process_vm_access.c                      |  28 +-
 mm/swap.c                                   |  24 +
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  21 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 31 files changed, 1145 insertions(+), 369 deletions(-)
 create mode 100644 Documentation/core-api/pin_user_pages.rst
---
2.24.1
```
