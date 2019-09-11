

#### [RFC PATCH 0/4] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Tue Sep 10 08:19:31 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11138905
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E7E51395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:20:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EA00221A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:20:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406732AbfIJIUE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 04:20:04 -0400
Received: from mx1.redhat.com ([209.132.183.28]:54330 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731155AbfIJIUE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 04:20:04 -0400
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 026D55859E;
        Tue, 10 Sep 2019 08:20:03 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-188.pek2.redhat.com [10.72.12.188])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 449B56092F;
        Tue, 10 Sep 2019 08:19:49 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, cohuck@redhat.com, tiwei.bie@intel.com,
        maxime.coquelin@redhat.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, rob.miller@broadcom.com, idos@mellanox.com,
        xiao.w.wang@intel.com, haotian.wang@sifive.com
Subject: [RFC PATCH 0/4] mdev based hardware virtio offloading support
Date: Tue, 10 Sep 2019 16:19:31 +0800
Message-Id: <20190910081935.30516-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.39]);
 Tue, 10 Sep 2019 08:20:03 +0000 (UTC)
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

Though the series only contain kernel driver support, the goal is to
make the transport generic enough to support userspace drivers. This
means vhost-mdev[1] could be built on top as well by resuing the
transport.

A sample driver is also implemented which simulate a virito-net
loopback ethernet device on top of vringh + workqueue. This could be
used as a reference implementation for real hardware driver.

Notes:

- Some of the key transport command for vhost-mdev(userspace driver)
  is not introduced. This includes:
  1) set/get virtqueue state (idx etc), this could be simply done by
     introducing new transport command
  2) dirty pages tracking, could be simply done by introducing new
     transport command
  3) set/get device internal state, this requires more thought, of
     course we can introduce device specific transport command, but it
     would be better to have a unified API
- Current mdev_parent_ops assumes all pointers are userspace pointer,
  this block the kernel driver, this series just abuse those as kernel
  pointer and this could be addressed by inventing new parent_ops.
- For quick POC, mdev transport was just derived from virtio-MMIO,
  I'm pretty sure it has lots of space to be optimized, please share
  your thought.

Please review.

[1] https://lkml.org/lkml/2019/8/28/35

Jason Wang (4):
  vringh: fix copy direction of vringh_iov_push_kern()
  mdev: introduce helper to set per device dma ops
  virtio: introudce a mdev based transport
  docs: Sample driver to demonstrate how to implement virtio-mdev
    framework

 drivers/vfio/mdev/Kconfig        |   7 +
 drivers/vfio/mdev/Makefile       |   1 +
 drivers/vfio/mdev/mdev_core.c    |   7 +
 drivers/vfio/mdev/virtio_mdev.c  | 500 ++++++++++++++++++++
 drivers/vhost/vringh.c           |   8 +-
 include/linux/mdev.h             |   2 +
 include/uapi/linux/virtio_mdev.h | 131 ++++++
 samples/Kconfig                  |   7 +
 samples/vfio-mdev/Makefile       |   1 +
 samples/vfio-mdev/mvnet.c        | 766 +++++++++++++++++++++++++++++++
 10 files changed, 1429 insertions(+), 1 deletion(-)
 create mode 100644 drivers/vfio/mdev/virtio_mdev.c
 create mode 100644 include/uapi/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH 0/2] KVM: CPUID: CPUID emulation flow adjustment and one minor
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Sep 10 08:24:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11138937
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AA105912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:39:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9113C208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 08:39:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727667AbfIJIjZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 04:39:25 -0400
Received: from mga04.intel.com ([192.55.52.120]:55164 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726099AbfIJIjZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 04:39:25 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Sep 2019 01:39:24 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,489,1559545200";
   d="scan'208";a="196468176"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by orsmga002.jf.intel.com with ESMTP; 10 Sep 2019 01:39:22 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org
Subject: [PATCH 0/2] KVM: CPUID: CPUID emulation flow adjustment and one minor
 refinement when updating maxphyaddr  
Date: Tue, 10 Sep 2019 16:24:40 +0800
Message-Id: <20190910082442.142702-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 adjusts the execution flow of CPUID instruction emulation, which
checks the leaf number first per CPUID specification.

Patch 2 moves physical address width updating to where we check the virtual
address width in function kvm_update_cpuid() since they two use the same
cpuid leaf, which makes it more reasonable and no functional change.  

Xiaoyao Li (2):
  KVM: CPUID: Check limit first when emulating CPUID instruction
  KVM: CPUID: Put maxphyaddr updating together with virtual address
    width checking

 arch/x86/kvm/cpuid.c | 56 +++++++++++++++++++++++++-------------------
 1 file changed, 32 insertions(+), 24 deletions(-)
```
#### [PATCH v2 0/2] KVM: CPUID: emulation flow adjustment and one minor
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Sep 10 10:27:40 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11139221
Return-Path: <SRS0=WlTH=XF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B4931395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 10:42:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8311520872
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 10 Sep 2019 10:42:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728293AbfIJKmX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 10 Sep 2019 06:42:23 -0400
Received: from mga04.intel.com ([192.55.52.120]:64085 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725797AbfIJKmX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 10 Sep 2019 06:42:23 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 10 Sep 2019 03:42:22 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,489,1559545200";
   d="scan'208";a="196512133"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.44])
  by orsmga002.jf.intel.com with ESMTP; 10 Sep 2019 03:42:20 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org
Subject: [PATCH v2 0/2] KVM: CPUID: emulation flow adjustment and one minor
 refinement when updating maxphyaddr
Date: Tue, 10 Sep 2019 18:27:40 +0800
Message-Id: <20190910102742.47729-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 adjusts the execution flow of CPUID instruction emulation, which
checks the leaf number first per CPUID specification.

Patch 2 moves physical address width updating to where we check the virtual
address width in function kvm_update_cpuid() since they two use the same
cpuid leaf, which makes it more reasonable and no functional change.  

Xiaoyao Li (2):
  KVM: CPUID: Check limit first when emulating CPUID instruction
  KVM: CPUID: Put maxphyaddr updating together with virtual address
    width checking

 arch/x86/kvm/cpuid.c | 57 ++++++++++++++++++++++++++------------------
 1 file changed, 34 insertions(+), 23 deletions(-)
```
