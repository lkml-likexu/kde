

#### [PATCH RESEND v6 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
From patchwork Fri Oct 11 07:41:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11184943
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0244F1575
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 07:41:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D599C2064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 07:41:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727632AbfJKHlI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 03:41:08 -0400
Received: from mga04.intel.com ([192.55.52.120]:5858 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727068AbfJKHlH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 03:41:07 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Oct 2019 00:41:07 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,283,1566889200";
   d="scan'208";a="194257161"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga007.fm.intel.com with ESMTP; 11 Oct 2019 00:41:06 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH RESEND v6 0/2] x86: Enable user wait instructions
Date: Fri, 11 Oct 2019 15:41:01 +0800
Message-Id: <20191011074103.30393-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v6:
	Remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set.
        (Paolo)

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  2 +-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 19 +++++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 43 insertions(+), 1 deletion(-)
```
#### [PATCH V3 0/7] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Fri Oct 11 08:15:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11184965
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C41A51709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 08:17:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A57902084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 08:17:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726595AbfJKIRH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 04:17:07 -0400
Received: from mx1.redhat.com ([209.132.183.28]:58740 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726174AbfJKIRH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 04:17:07 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E63FC10DCCA2;
        Fri, 11 Oct 2019 08:17:05 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-241.pek2.redhat.com [10.72.12.241])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C32321001B08;
        Fri, 11 Oct 2019 08:15:57 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V3 0/7] mdev based hardware virtio offloading support
Date: Fri, 11 Oct 2019 16:15:50 +0800
Message-Id: <20191011081557.28302-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.64]);
 Fri, 11 Oct 2019 08:17:06 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardware that can do virtio datapath offloading while having
its own control path. This path tries to implement a mdev based
unified API to support using kernel virtio driver to drive those
devices. This is done by introducing a new mdev transport for virtio
(virtio_mdev) and register itself as a new kind of mdev driver. Then
it provides a unified way for kernel virtio driver to talk with mdev
device implementation.

Though the series only contains kernel driver support, the goal is to
make the transport generic enough to support userspace drivers. This
means vhost-mdev[1] could be built on top as well by resuing the
transport.

A sample driver is also implemented which simulate a virito-net
loopback ethernet device on top of vringh + workqueue. This could be
used as a reference implementation for real hardware driver.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/9/26/15

Changes from V2:

- fail when class_id is not specified
- drop the vringh patch
- match the doc to the code
- tweak the commit log
- move device_ops from parent to mdev device
- remove the unused MDEV_ID_VHOST

Changes from V1:

- move virtio_mdev.c to drivers/virtio
- store class_id in mdev_device instead of mdev_parent
- store device_ops in mdev_device instead of mdev_parent
- reorder the patch, vringh fix comes first
- really silent compiling warnings
- really switch to use u16 for class_id
- uevent and modpost support for mdev class_id
- vraious tweaks per comments from Parav

Changes from RFC-V2:

- silent compile warnings on some specific configuration
- use u16 instead u8 for class id
- reseve MDEV_ID_VHOST for future vhost-mdev work
- introduce "virtio" type for mvnet and make "vhost" type for future
  work
- add entries in MAINTAINER
- tweak and typos fixes in commit log

Changes from RFC-V1:

- rename device id to class id
- add docs for class id and device specific ops (device_ops)
- split device_ops into seperate headers
- drop the mdev_set_dma_ops()
- use device_ops to implement the transport API, then it's not a part
  of UAPI any more
- use GFP_ATOMIC in mvnet sample device and other tweaks
- set_vring_base/get_vring_base support for mvnet device

Jason Wang (7):
  mdev: class id support
  mdev: bus uevent support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  25 +-
 MAINTAINERS                                   |   2 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  18 +
 drivers/vfio/mdev/mdev_driver.c               |  22 +
 drivers/vfio/mdev/mdev_private.h              |   2 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 416 +++++++++++
 include/linux/mdev.h                          |  49 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev.h                     |  52 ++
 include/linux/virtio_mdev.h                   | 148 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  20 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 691 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  10 +
 24 files changed, 1523 insertions(+), 87 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev.h
 create mode 100644 include/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH v3 0/4] KVM: arm64: Assorted PMU emulation fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Oct 11 12:39:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11185351
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE96A1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A5F3A222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:40:20 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570797620;
	bh=Zt+pHSPxfhjzB1EMAAlN0b3r/E15xPAOqliI4X1I1t4=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=UHWbrIJo3GNbNshZVVwL91ynkx6TJHhja8/Ez4jc4ZORNRX6G7XXk3b6N2U2TiVJk
	 uM9+YfahaE8lUQaYCPHVRnQG3c0zxg0qAUPGswxKnJGLaay+QTk/OJq1zyghJ2RqOd
	 TRu3Xu9+XLtoT2QMR1TGO0A7sFOOK8oV7QXzKiG0=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728152AbfJKMkS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 08:40:18 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:36326 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727589AbfJKMkS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 11 Oct 2019 08:40:18 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iIuDO-00062U-Br; Fri, 11 Oct 2019 14:40:14 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Murray <andrew.murray@arm.com>
Subject: [PATCH v3 0/4] KVM: arm64: Assorted PMU emulation fixes
Date: Fri, 11 Oct 2019 13:39:50 +0100
Message-Id: <20191011123954.31378-1-maz@kernel.org>
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

The last patch fixes an issue that has been here from day one, where
we confuse architectural overflow of a counter and perf sampling
period, and uses a terrible hack^W^W creative way to interact with the
underlying PMU driver so that we can reload the period when handling
the overflow.

* From v2 [1]
  - Dropped PMUv3 patch and moved the logic into the KVM code
  - Properly use UPDATE/RELOAD
  - Collected Andrew's RB

[1] https://lore.kernel.org/kvmarm/20191008160128.8872-1-maz@kernel.org/

Marc Zyngier (4):
  KVM: arm64: pmu: Fix cycle counter truncation
  arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
  KVM: arm64: pmu: Set the CHAINED attribute before creating the
    in-kernel event
  KVM: arm64: pmu: Reset sample period on overflow handling

 arch/arm64/kvm/sys_regs.c |  4 ++++
 virt/kvm/arm/pmu.c        | 48 ++++++++++++++++++++++++++++-----------
 2 files changed, 39 insertions(+), 13 deletions(-)
```
#### [PATCH v6 00/10] arm64: Stolen time support
##### From: Steven Price <steven.price@arm.com>

```c
From patchwork Fri Oct 11 12:59:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11185387
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52F3C1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:59:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3DEB6206A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 12:59:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728217AbfJKM7j (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 08:59:39 -0400
Received: from foss.arm.com ([217.140.110.172]:59298 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727589AbfJKM7j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 08:59:39 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1F0F128;
        Fri, 11 Oct 2019 05:59:38 -0700 (PDT)
Received: from e112269-lin.cambridge.arm.com (e112269-lin.cambridge.arm.com
 [10.1.194.43])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1C8EA3F6C4;
        Fri, 11 Oct 2019 05:59:36 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v6 00/10] arm64: Stolen time support
Date: Fri, 11 Oct 2019 13:59:20 +0100
Message-Id: <20191011125930.40834-1-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series add support for paravirtualized time for arm64 guests and
KVM hosts following the specification in Arm's document DEN 0057A:

https://developer.arm.com/docs/den0057/a

It implements support for stolen time, allowing the guest to
identify time when it is forcibly not executing.

Note that Live Physical Time (LPT) which was previously part of the
above specification has now been removed.

Also available as a git tree:
git://linux-arm.org/linux-sp.git stolen_time/v6

Changes from v5:
https://lore.kernel.org/kvm/20191002145037.51630-1-steven.price@arm.com/
 * Convert document to RST format
 * Rename PV_FEATURES to PV_TIME_FEATURES to match spec
 * Correct SMC number of PV_TIME_ST

Changes from v4:
https://lore.kernel.org/kvm/20190830084255.55113-1-steven.price@arm.com/
 * Rebased to v5.4-rc1
 * Renamed KVM_ARM_VCPU_PVTIME_SET_IPA to remove _SET as it is used for
   both set/get operations
 * Added kvm/arm_hypercalls.h to header-test-$(CONFIG_ARM{,64}) as it is
   only buildable on arm/arm64
 * Documented no-steal-acc kernel parameter

Changes from v3:
https://lore.kernel.org/lkml/20190821153656.33429-1-steven.price@arm.com/
 * There's no longer a PV_TIME device, instead there are attributes on
   the VCPU. This allows the stolen time structures to be places
   arbitrarily by user space (subject to 64 byte alignment).
 * Split documentation between information on the hypercalls and the
   attributes on the VCPU
 * Fixed the type of SMCCC functions to return long not int

Changes from v2:
https://lore.kernel.org/lkml/20190819140436.12207-1-steven.price@arm.com/
 * Switched from using gfn_to_hva_cache to a new macro kvm_put_guest()
   that can provide the single-copy atomicity required (on arm64). This
   macro is added in patch 4.
 * Tidied up the locking for kvm_update_stolen_time().
   pagefault_disable() was unnecessary and the caller didn't need to
   take kvm->srcu as the function does it itself.
 * Removed struct kvm_arch_pvtime from the arm implementation, replaced
   instead with inline static functions which are empty for arm.
 * Fixed a few checkpatch --strict warnings.

Changes from v1:
https://lore.kernel.org/lkml/20190802145017.42543-1-steven.price@arm.com/
 * Host kernel no longer allocates the stolen time structure, instead it
   is allocated by user space. This means the save/restore functionality
   can be removed.
 * Refactored the code so arm has stub implementations and to avoid
   initcall
 * Rebased to pick up Documentation/{virt->virtual} change
 * Bunch of typo fixes

Christoffer Dall (1):
  KVM: arm/arm64: Factor out hypercall handling from PSCI code

Steven Price (9):
  KVM: arm64: Document PV-time interface
  KVM: arm64: Implement PV_TIME_FEATURES call
  KVM: Implement kvm_put_guest()
  KVM: arm64: Support stolen time reporting via shared structure
  KVM: Allow kvm_device_ops to be const
  KVM: arm64: Provide VCPU attributes for stolen time
  arm/arm64: Provide a wrapper for SMCCC 1.1 calls
  arm/arm64: Make use of the SMCCC 1.1 wrapper
  arm64: Retrieve stolen time as paravirtualized guest

 .../admin-guide/kernel-parameters.txt         |   6 +-
 Documentation/virt/kvm/arm/pvtime.rst         |  77 +++++++++
 Documentation/virt/kvm/devices/vcpu.txt       |  14 ++
 arch/arm/include/asm/kvm_host.h               |  26 +++
 arch/arm/kvm/Makefile                         |   2 +-
 arch/arm/kvm/handle_exit.c                    |   2 +-
 arch/arm/mm/proc-v7-bugs.c                    |  13 +-
 arch/arm64/include/asm/kvm_host.h             |  30 +++-
 arch/arm64/include/asm/paravirt.h             |   9 +-
 arch/arm64/include/asm/pvclock-abi.h          |  17 ++
 arch/arm64/include/uapi/asm/kvm.h             |   2 +
 arch/arm64/kernel/cpu_errata.c                |  80 ++++------
 arch/arm64/kernel/paravirt.c                  | 148 ++++++++++++++++++
 arch/arm64/kernel/time.c                      |   3 +
 arch/arm64/kvm/Kconfig                        |   1 +
 arch/arm64/kvm/Makefile                       |   2 +
 arch/arm64/kvm/guest.c                        |   9 ++
 arch/arm64/kvm/handle_exit.c                  |   4 +-
 include/Kbuild                                |   2 +
 include/kvm/arm_hypercalls.h                  |  43 +++++
 include/kvm/arm_psci.h                        |   2 +-
 include/linux/arm-smccc.h                     |  58 +++++++
 include/linux/cpuhotplug.h                    |   1 +
 include/linux/kvm_host.h                      |  26 ++-
 include/linux/kvm_types.h                     |   2 +
 include/uapi/linux/kvm.h                      |   2 +
 virt/kvm/arm/arm.c                            |  11 ++
 virt/kvm/arm/hypercalls.c                     |  68 ++++++++
 virt/kvm/arm/psci.c                           |  84 +---------
 virt/kvm/arm/pvtime.c                         | 124 +++++++++++++++
 virt/kvm/kvm_main.c                           |   6 +-
 31 files changed, 717 insertions(+), 157 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst
 create mode 100644 arch/arm64/include/asm/pvclock-abi.h
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c
 create mode 100644 virt/kvm/arm/pvtime.c
```
#### [PATCH net 0/2] vsock: don't allow half-closed socket in the host
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Fri Oct 11 13:07:56 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11185443
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 83C0015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:08:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6F5E42089F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:08:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728519AbfJKNIH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 09:08:07 -0400
Received: from mx1.redhat.com ([209.132.183.28]:13287 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728511AbfJKNIH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 09:08:07 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 0B6553082128;
        Fri, 11 Oct 2019 13:08:07 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-54.ams2.redhat.com
 [10.36.117.54])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AD59C60600;
        Fri, 11 Oct 2019 13:07:59 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
        Jorgen Hansen <jhansen@vmware.com>,
        "David S. Miller" <davem@davemloft.net>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Adit Ranadive <aditr@vmware.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH net 0/2] vsock: don't allow half-closed socket in the host
 transports
Date: Fri, 11 Oct 2019 15:07:56 +0200
Message-Id: <20191011130758.22134-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.42]);
 Fri, 11 Oct 2019 13:08:07 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are implementing a test suite for the VSOCK sockets and we discovered
that vmci_transport never allowed half-closed socket on the host side.

As Jorgen explained [1] this is due to the implementation of VMCI.

Since we want to have the same behaviour across all transports, this
series adds a section in the "Implementation notes" to exaplain this
behaviour, and changes the vhost_transport to behave the same way.

[1] https://patchwork.ozlabs.org/cover/847998/#1831400

Stefano Garzarella (2):
  vsock: add half-closed socket details in the implementation notes
  vhost/vsock: don't allow half-closed socket in the host

 drivers/vhost/vsock.c    | 17 ++++++++++++++++-
 net/vmw_vsock/af_vsock.c |  4 ++++
 2 files changed, 20 insertions(+), 1 deletion(-)
```
#### [PATCH RFC v1 0/2] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Fri Oct 11 13:45:54 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11185519
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DCA714DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:46:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 189932064A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 13:46:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728750AbfJKNqB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 09:46:01 -0400
Received: from mx1.redhat.com ([209.132.183.28]:48242 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728270AbfJKNqB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 09:46:01 -0400
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id D44D97575F
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 13:46:00 +0000 (UTC)
Received: by mail-qt1-f197.google.com with SMTP id r15so9434116qtn.12
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 06:46:00 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=o/nkRYTONx73WsD7MC8B77Hivj8w35ee4nLVJzmSYdg=;
        b=RHkRygy3KIYPlFH3O4IY5dnGFCvgrxtp96awOz7nGK6Ne32KOw0LK38T0oqtrWY80S
         qnOty6NWdvQmEg8z1Gvz1g2dyV96svvOrMhXN2qrhDSV0t2T7kXW2tYHz3fEi+ZOL+Ga
         6fr+OWDIE85tVbAJ86EHRKvVDGy9flHUxjFk5Ouobud5HBYbkohofDXxJdGqHUYiVy+9
         vdH13lrI5XX8quF5MiWFD71mUcDNmFPKa7w9liHdJBYyIdL88XI+XV7f/+QTs276VQqq
         YQ+bMZpu7oHysBwYUMFx0lpmMs14Z33AiVWPRhYCq0j8OE/WUJwv9o0IUbbKpINnOuyQ
         oUiQ==
X-Gm-Message-State: APjAAAXQsqXlYW3dar7+u+uvpCN2Wutx6eHbfd5BkqOQSkRPyqjYwi1u
        LwKjipb4Tt9sVT6arR283QNLKFfNcZXEUgX6g8Zrp8MJJDcLzfuQh1tjExlhmiJQTOGzqet1GHm
        aKSjaSyDBRHA9
X-Received: by 2002:ac8:2e10:: with SMTP id r16mr17460365qta.62.1570801560086;
        Fri, 11 Oct 2019 06:46:00 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyNkV+IdP+Wd7WKMbrFt0Q607s9maou4ckQQ4vu7F/qkVJUOjLTGMKOgQL8yhEDf1yVy213sQ==
X-Received: by 2002:ac8:2e10:: with SMTP id r16mr17460293qta.62.1570801559470;
        Fri, 11 Oct 2019 06:45:59 -0700 (PDT)
Received: from redhat.com (bzq-79-176-10-77.red.bezeqint.net. [79.176.10.77])
        by smtp.gmail.com with ESMTPSA id
 w6sm3944120qkj.136.2019.10.11.06.45.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 11 Oct 2019 06:45:58 -0700 (PDT)
Date: Fri, 11 Oct 2019 09:45:54 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: Jason Wang <jasowang@redhat.com>
Subject: [PATCH RFC v1 0/2] vhost: ring format independence
Message-ID: <20191011134358.16912-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.22.0.678.g13338e74b8
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So the idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

And perhaps more importantly, this is a very good fit for the packed
ring layout, where we get and put descriptors in order.

This patchset seems to already perform exactly the same as the original
code already based on a microbenchmark.  More testing would be very much
appreciated.

Biggest TODO before this first step is ready to go in is to
batch indirect descriptors as well.

Integrating into vhost-net is basically
s/vhost_get_vq_desc/vhost_get_vq_desc_batch/ -
or add a module parameter like I did in the test module.



Michael S. Tsirkin (2):
  vhost: option to fetch descriptors through an independent struct
  vhost: batching fetches

 drivers/vhost/test.c  |  19 ++-
 drivers/vhost/vhost.c | 333 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  20 ++-
 3 files changed, 365 insertions(+), 7 deletions(-)
```
#### [PATCH v2 0/5] Add support for XSAVES on AMD and unify it with Intel
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Fri Oct 11 19:40:27 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11186309
Return-Path: <SRS0=7oZ8=YE=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94EF215AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 19:40:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 750562084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 11 Oct 2019 19:40:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="K1PA1JbN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728937AbfJKTkv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 11 Oct 2019 15:40:51 -0400
Received: from mail-vk1-f201.google.com ([209.85.221.201]:53546 "EHLO
        mail-vk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728892AbfJKTkv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Oct 2019 15:40:51 -0400
Received: by mail-vk1-f201.google.com with SMTP id q5so3823770vkg.20
        for <kvm@vger.kernel.org>; Fri, 11 Oct 2019 12:40:50 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=+/jcGRcBsJzyIdBmTS9ExaE2iCkBC76r0L6qvqm8SAE=;
        b=K1PA1JbN3jWoC+Yzscc956ny8igDNYeg4F2KLHAhIuk6Bn6E9cUGr36qYC11FkcQJA
         MMwp10/9lO5c3Ioy9QrQUUPRUPoWiMBe4+UWc2LrOgZ+9HI41fYubVhfemf1p9FZl51r
         iCENgAbmQBStF1Uw5FcJYmsVqH5s76sKHNo7UrkNJ4RQz7kXA8hCdj0tOSLhf2rm1Po8
         FMxdMrYRemjkIhSWjpMbVZ6Lzoi15xgeQtdLsBkC5bSa2SsIcRCsiZrNeafOh4vpP+zz
         q8nxstt7di7/bEa1gWb5QSQviPDgevkyOqE6H/IUevO5Z02SFyy3RTWcReDtn8kn6D50
         wgqw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=+/jcGRcBsJzyIdBmTS9ExaE2iCkBC76r0L6qvqm8SAE=;
        b=cwy36YKrDJRHZDvlx1KVrbvdWpqemYYlwqUi7QdcywxwvU0PLpXx626wIGQXu9UY0D
         w3f5jMUBccYXGHR3WMVLHUnFS0+5Og8iOoiRfkrWX1JaUiZsQmkH9QG0xH4Trsyccde9
         SL8GHgkXx1iuKuIAQQlLG6zIhxteX3DrFtyRsGH8UmRG6ayvmr9x+vqXuDOi1/K7FZ1a
         n08XK/b/AjVZqOQBq3NtPd1wDHOWp2riVBPM5lwyUXNhsiiuCqOKKMUnIzuy8F5u0PXf
         WifvOlqhmRf+Zn+cby4XE4+gOYyHNMlfUPwmbv1+/fM84jqN6a4oFYDl0ePKEeKpbP06
         UlBA==
X-Gm-Message-State: APjAAAVDzcgN/ZYafIX8jjuOZzDsFvRDceDP+G5laRA0itfexmdso2E8
        YxOiMT6PzWorKviXGIG49gpfQv1U5N8J7y3K
X-Google-Smtp-Source: 
 APXvYqznQhZIPEGLrNQYQfiynO7xvd8eM3JxY8LXqIL6TbsAjmBFCoYnAdY9AWu7UvX1slIOiMdKo2G+8e6stcZC
X-Received: by 2002:ab0:6994:: with SMTP id t20mr3240391uaq.124.1570822849812;
 Fri, 11 Oct 2019 12:40:49 -0700 (PDT)
Date: Fri, 11 Oct 2019 12:40:27 -0700
Message-Id: <20191011194032.240572-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [PATCH v2 0/5] Add support for XSAVES on AMD and unify it with Intel
From: Aaron Lewis <aaronlewis@google.com>
To: Babu Moger <Babu.Moger@amd.com>,
        Yang Weijiang <weijiang.yang@intel.com>,
        Sebastian Andrzej Siewior <bigeasy@linutronix.de>,
        kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unify AMD's and Intel's approach for supporting XSAVES.  To do this
change Intel's approach from using the MSR-load areas to writing
the guest/host values to IA32_XSS on a VM-enter/VM-exit.  Switching to
this strategy allows for a common approach between both AMD and Intel.
Additionally, define svm_xsaves_supported() based on AMD's feedback, and
add IA32_XSS to the emulated_msrs list, in preparation for the day when
the guest IA32_XSS may contain a non-zero value.

This change sets up IA32_XSS to be a non-zero value in the future, which
may happen sooner than later with support for guest CET feature being
added.

v1 -> v2:
 - Add the flag xsaves_enabled to kvm_vcpu_arch to track when XSAVES is
   enabled in the guest, whether or not XSAVES is enumerated in the
   guest CPUID.
 - Remove code that sets the X86_FEATURE_XSAVES bit in the guest CPUID
   which was added in patch "Enumerate XSAVES in guest CPUID when it is
   available to the guest".  As a result we no longer need that patch.
 - Added a comment to kvm_set_msr_common to describe how to save/restore
   PT MSRS without using XSAVES/XRSTORS.
 - Added more comments to the "Add support for XSAVES on AMD" patch.
 - Replaced vcpu_set_msr_expect_result() with _vcpu_set_msr() in the
   test library.

Aaron Lewis (5):
  KVM: VMX: Remove unneeded check for X86_FEATURE_XSAVE
  KVM: VMX: Use wrmsr for switching between guest and host IA32_XSS
  kvm: svm: Add support for XSAVES on AMD
  kvm: x86: Add IA32_XSS to the emulated_msrs list
  kvm: tests: Add test to verify MSR_IA32_XSS

 arch/x86/include/asm/kvm_host.h               |  1 +
 arch/x86/kvm/svm.c                            | 19 +++--
 arch/x86/kvm/vmx/vmx.c                        | 46 ++++--------
 arch/x86/kvm/x86.c                            | 46 ++++++++++--
 arch/x86/kvm/x86.h                            |  4 +-
 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  1 +
 .../selftests/kvm/include/x86_64/processor.h  |  7 +-
 .../selftests/kvm/lib/x86_64/processor.c      | 72 ++++++++++++++++---
 .../selftests/kvm/x86_64/xss_msr_test.c       | 70 ++++++++++++++++++
 10 files changed, 210 insertions(+), 57 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/xss_msr_test.c
```
