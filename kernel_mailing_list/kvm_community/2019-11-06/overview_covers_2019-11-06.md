

#### [PATCH V9 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Nov  6 07:05:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11229517
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 695F913BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:07:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 32890206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:07:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="O3Je4FWH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731423AbfKFHHT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 02:07:19 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:49689 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1731172AbfKFHHT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 02:07:19 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573024037;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=hZQT3duyyndR+0G+CA+4t+0Dt0ILcfgLE6OucGmmjrQ=;
        b=O3Je4FWHx3LyynioWJIxAOuCbXIxAF+FLn1tQZxIldAWHudUr5JlHg3l74UC/Ybl3ZhIcJ
        ayhyjTRUB6cz9XtOCDAFF/aZS06tBNAYzEGM+DAdDuGKIp6GK409V0zCGrLMOJQs1w9s/A
        TpWMaUkLnNlm6DGe2TDpdbxNMyVD0ZQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-230-sS4JHO2DNtCxuysVDg7ijQ-1; Wed, 06 Nov 2019 02:07:13 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 40F08477;
        Wed,  6 Nov 2019 07:07:09 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-193.pek2.redhat.com [10.72.12.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 90FEB1001B39;
        Wed,  6 Nov 2019 07:05:54 +0000 (UTC)
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
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V9 0/6] mdev based hardware virtio offloading support
Date: Wed,  6 Nov 2019 15:05:42 +0800
Message-Id: <20191106070548.18980-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: sS4JHO2DNtCxuysVDg7ijQ-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardwares that can do virtio datapath offloading while
having its own control path. This path tries to implement a mdev based
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

Also a real IFC VF driver was also posted here[2] which is a good
reference for vendors who is interested in their own virtio datapath
offloading product.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/11/5/424
[2] https://lkml.org/lkml/2019/11/5/227

Changes from V8:
- try silent checkpatch, some are still there becuase they were inherited
  from virtio_config_ops which needs to be resolved in an independent series
- tweak on the comment and doc
- remove VIRTIO_MDEV_F_VERSION_1 completely
- rename CONFIG_VIRTIO_MDEV_DEVICE to CONFIG_VIRTIO_MDEV

Changes from V7:
- drop {set|get}_mdev_features for virtio
- typo and comment style fixes

Changes from V6:
- rename ops files and compile guard

Changes from V5:
- use dev_warn() instead of WARN(1) when class id is not set
- validate id_table before trying to do matching between device and
  driver
- add wildcard for modpost script
- use unique name for id_table
- move get_mdev_features() to be the first member of virtio_device_ops
  and more comments for it
- typo fixes for the comments above virtio_mdev_ops

Changes from V4:
- keep mdev_set_class() for the device that doesn't use device ops
- use union for device ops pointer in mdev_device
- introduce class specific helper for getting is device ops
- use WARN_ON instead of BUG_ON in mdev_set_virtio_ops
- explain details of get_mdev_features() and get_vendor_id()
- distinguish the optional virito device ops from mandatory ones and
  make get_generation() optional
- rename vfio_mdev.h to vfio_mdev_ops.h, rename virito_mdev.h to
  virtio_mdev_ops.h
- don't abuse version fileds in virtio_mdev structure, use features
  instead
- fix warning during device remove
- style & docs tweaks and typo fixes

Changes from V3:
- document that class id (device ops) must be specified in create()
- add WARN() when trying to set class_id when it has already set
- add WARN() when class_id is not specified in create() and correctly
  return an error in this case
- correct the prototype of mdev_set_class() in the doc
- add documention of mdev_set_class()
- remove the unnecessary "class_id_fail" label when class id is not
  specified in create()
- convert id_table in vfio_mdev to const
- move mdev_set_class and its friends after mdev_uuid()
- suqash the patch of bus uevent into patch of introducing class id
- tweak the words in the docs per Cornelia suggestion
- tie class_id and device ops through class specific initialization
  routine like mdev_set_vfio_ops()
- typos fixes in the docs of virtio-mdev callbacks
- document the usage of virtqueues in struct virtio_mdev_device
- remove the useless vqs array in struct virtio_mdev_device
- rename MDEV_ID_XXX to MDEV_CLASS_ID_XXX

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

Jason Wang (6):
  mdev: class id support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  38 +-
 MAINTAINERS                                   |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  60 ++
 drivers/vfio/mdev/mdev_driver.c               |  25 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |  13 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 406 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mdev_vfio_ops.h                 |  52 ++
 include/linux/mdev_virtio_ops.h               | 147 ++++
 include/linux/mod_devicetable.h               |   8 +
 samples/Kconfig                               |  10 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 686 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  11 +
 24 files changed, 1585 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/mdev_vfio_ops.h
 create mode 100644 include/linux/mdev_virtio_ops.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH v6 0/9] Enable Sub-Page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed Nov  6 07:44:55 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11229599
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78ED416B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:43:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5C29821848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 07:43:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731068AbfKFHmm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 02:42:42 -0500
Received: from mga06.intel.com ([134.134.136.31]:15128 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726772AbfKFHmm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 02:42:42 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 23:42:41 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,274,1569308400";
   d="scan'208";a="232770668"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga002.fm.intel.com with ESMTP; 05 Nov 2019 23:42:39 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Cc: yu.c.zhang@linux.intel.com, alazar@bitdefender.com,
        edwin.zhai@intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v6 0/9] Enable Sub-Page Write Protection Support
Date: Wed,  6 Nov 2019 15:44:55 +0800
Message-Id: <20191106074504.14858-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

EPT-Based Sub-Page write Protection(SPP) allows Virtual Machine Monitor(VMM)
specify write-permission for guest physical memory at a sub-page(128 byte)
granularity. When SPP works, HW enforces write-access check for sub-pages
within a protected 4KB page.

The feature targets to provide fine-grained memory protection for
usages such as memory guard and VM introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), and subpage permission vector is stored in the
leaf entry of SPPT. The root page is referenced via a Sub-Page Permission
Table Pointer (SPPTP) in VMCS.

To enable SPP for guest memory, the guest page should be first mapped
to a 4KB EPT entry, then set SPP bit 61 of the corresponding entry. 
While HW walks EPT, it traverses SPPT with the gpa to look up the sub-page
permission vector within SPPT leaf entry. If the corresponding bit is set,
write to sub-page is permitted, otherwise, SPP induced EPT violation is generated.

This patch serial passed SPP function test and selftest on Ice-Lake platform.

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

SPP selftest patch:
https://lkml.org/lkml/2019/6/18/1197

Previous patch:
https://lkml.org/lkml/2019/9/17/180

Patch 1: Documentation for SPP and related API.
Patch 2: Add control flags for Sub-Page Protection(SPP).
Patch 3: Add SPP Table setup functions.
Patch 4: Add functions to create/destroy SPP bitmap block.
Patch 5: Introduce user-space SPP IOCTLs.
Patch 6: Set up SPP paging table at vmentry/vmexit.
Patch 7: Enable Lazy mode SPP protection.
Patch 8: Handle SPP protected pages when VM memory changes.
Patch 9: Add SPP protection check in emulation case.


Change logs:

V5 -> V6:
  1. Added SPP protection patch for emulation cases per Jim's review.
  2. Modified documentation and added API description per Jim's review.
  3. Other minior changes suggested by Jim.

V4 -> V5:
  1. Enable SPP support for Hugepage(1GB/2MB) to extend application.
  2. Make SPP miss vm-exit handler as the unified place to set up SPPT.
  3. If SPP protected pages are access-tracked or dirty-page-tracked,
     store SPP flag in reserved address bit, restore it in
     fast_page_fault() handler.
  4. Move SPP specific functions to vmx/spp.c and vmx/spp.h
  5. Rebased code to kernel v5.3
  6. Other change suggested by KVM community.
  
V3 -> V4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

V2 -> V3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

V2 -> V1:
  1. Rebased to 4.20-rc1
  2. Move VMCS change to a separated patch.
  3. Code refine and Bug fix 


Yang Weijiang (9):
  Documentation: Introduce EPT based Subpage Protection and related
    ioctls
  vmx: spp: Add control flags for Sub-Page Protection(SPP)
  mmu: spp: Add SPP Table setup functions
  mmu: spp: Add functions to create/destroy SPP bitmap block
  x86: spp: Introduce user-space SPP IOCTLs
  vmx: spp: Set up SPP paging table at vmentry/vmexit
  mmu: spp: Enable Lazy mode SPP protection
  mmu: spp: Handle SPP protected pages when VM memory changes
  x86: spp: Add SPP protection check in emulation.

 Documentation/virt/kvm/api.txt        |  46 ++
 Documentation/virtual/kvm/spp_kvm.txt | 180 +++++++
 arch/x86/include/asm/cpufeatures.h    |   1 +
 arch/x86/include/asm/kvm_host.h       |  10 +-
 arch/x86/include/asm/vmx.h            |  10 +
 arch/x86/include/uapi/asm/vmx.h       |   2 +
 arch/x86/kernel/cpu/intel.c           |   4 +
 arch/x86/kvm/mmu.c                    |  78 +++-
 arch/x86/kvm/mmu.h                    |   2 +
 arch/x86/kvm/vmx/capabilities.h       |   5 +
 arch/x86/kvm/vmx/spp.c                | 649 ++++++++++++++++++++++++++
 arch/x86/kvm/vmx/spp.h                |  28 ++
 arch/x86/kvm/vmx/vmx.c                |  97 ++++
 arch/x86/kvm/x86.c                    |  87 ++++
 include/uapi/linux/kvm.h              |  17 +
 15 files changed, 1214 insertions(+), 2 deletions(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
 create mode 100644 arch/x86/kvm/vmx/spp.c
 create mode 100644 arch/x86/kvm/vmx/spp.h
```
#### [PATCH v2 0/4] misc fixes on halt-poll code both KVM and guest
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
From patchwork Wed Nov  6 09:08:48 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11229685
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 526D5112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 09:09:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2D98F217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 09:09:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="j2sxpBb/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728256AbfKFJJf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 04:09:35 -0500
Received: from userp2120.oracle.com ([156.151.31.85]:45618 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727041AbfKFJJe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 04:09:34 -0500
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6990N6090942;
        Wed, 6 Nov 2019 09:09:23 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2019-08-05;
 bh=vtOUSXhJOWeZNpYZPR4dz6ez1tfCq89k9rogWBbRY90=;
 b=j2sxpBb/lPk6e1dqkColY5vG17mDQmIPt4iVQK1+2HUYK5wbbvi6oMc1BF3ahclFly3l
 E+eLHsmK/xeAnBrlQJGA5/1O8OrSPd3DT75xwFL914AdOK8ALKt5x8mqFR4frnMd7+z7
 qFKGRf82F909hXBBkpKrLrogskVGebi7mXWMPsXXfS5yQ4wSP/7j26UD2WXAOU+pArip
 b8RorxKwywk0k4PCn5tWZv953Mo/quv2oXWRr9ie3oI+WDuUzPOAlhfw47dAIrWO618A
 uBBFOBZtsPPDus3sqdggL9usJRw8C59LIym6ehNTTC8P+Xf2wW18qrXpK+7179CQe/Oh Cw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 2w12erca4k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 09:09:23 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA698rXT015312;
        Wed, 6 Nov 2019 09:09:22 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3020.oracle.com with ESMTP id 2w31631dsm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 09:09:22 +0000
Received: from abhmp0009.oracle.com (abhmp0009.oracle.com [141.146.116.15])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xA699LR2006042;
        Wed, 6 Nov 2019 09:09:21 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 01:09:21 -0800
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        rafael.j.wysocki@intel.com, joao.m.martins@oracle.com,
        mtosatti@redhat.com, Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH v2 0/4] misc fixes on halt-poll code both KVM and guest
Date: Wed,  6 Nov 2019 17:08:48 +0800
Message-Id: <1573031332-2121-1-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1911060096
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1911060096
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset tries to fix below issues:

1. Admin could set halt_poll_ns to 0 at runtime to disable poll and kernel
behave just like the generic halt driver. Then If guest_halt_poll_grow_start
is set to 0 and guest_halt_poll_ns set to nonzero later, cpu_halt_poll_us will
never grow beyond 0. The first two patches fix this issue from both kvm and
guest side.

2. guest_halt_poll_grow_start and guest_halt_poll_ns could be adjusted at
runtime by admin, this could make a window where cpu_halt_poll_us jump out
of the boundary. the window could be long in some cases(e.g. guest_halt_poll_grow_start
is bumped and cpu_halt_poll_us is shrinking) The last two patches fix this
issue from both kvm and guest side.

3. The 4th patch also simplifies branch check code.

v2:
Rewrite the patches and drop unnecessory changes

Zhenzhong Duan (4):
  cpuidle-haltpoll: ensure grow start value is nonzero
  KVM: ensure grow start value is nonzero
  cpuidle-haltpoll: ensure cpu_halt_poll_us in right scope
  KVM: ensure vCPU halt_poll_us in right scope

 drivers/cpuidle/governors/haltpoll.c | 50 ++++++++++++++++++++++++-----------
 virt/kvm/kvm_main.c                  | 51 ++++++++++++++++++++++++------------
 2 files changed, 68 insertions(+), 33 deletions(-)
```
#### [PATCH RESEND v2 0/4] misc fixes on halt-poll code for both KVM and
##### From: Zhenzhong Duan <zhenzhong.duan@oracle.com>

```c
From patchwork Wed Nov  6 11:54:58 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@oracle.com>
X-Patchwork-Id: 11230101
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE77C13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 11:56:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8A3C221A49
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 11:56:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="ECBRyQrD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730485AbfKFL4J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 06:56:09 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:37270 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730120AbfKFL4I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 06:56:08 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6BsP9Q061515;
        Wed, 6 Nov 2019 11:55:41 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2019-08-05;
 bh=vtOUSXhJOWeZNpYZPR4dz6ez1tfCq89k9rogWBbRY90=;
 b=ECBRyQrD0dB8jrv1x0LFRvrc3cO7pcmPZUyPQGkc0oeGvRC73YV890LmonDGPACREL6y
 YWlri1SAXf8V1f945+9v5YESTe5WG3i4AO7htghuicupNcHnHrQCUcUGOsDAdy8WoFJO
 cvu0V6LPTUpk3Z8d62q6LNGRk61MrH/UNilOktZ+mJCBMd67IrAbsjm+bHd3qGXvMd2R
 PasgF+xa0/w4FN0FSLu27OvmkKjZiryzze63TcnBDVgAvqWDlAVpFyfHQfsMRKROe0f8
 +AcOcxOQrVQYvfmie7U5TPGmuqQ0lOjdBmi3rIIUpE0jLb3avuFfEUxSwbGtOe3V7s5I NQ==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2130.oracle.com with ESMTP id 2w117u5p8d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 11:55:41 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6BsHBb051668;
        Wed, 6 Nov 2019 11:55:40 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3020.oracle.com with ESMTP id 2w31639sd8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 11:55:40 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xA6Btda5021392;
        Wed, 6 Nov 2019 11:55:39 GMT
Received: from z2.cn.oracle.com (/10.182.71.218)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 03:55:39 -0800
From: Zhenzhong Duan <zhenzhong.duan@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, rkrcmar@redhat.com,
        rafael.j.wysocki@intel.com, joao.m.martins@oracle.com,
        mtosatti@redhat.com, kvm@vger.kernel.org, linux-pm@vger.kernel.org,
        Zhenzhong Duan <zhenzhong.duan@oracle.com>
Subject: [PATCH RESEND v2 0/4] misc fixes on halt-poll code for both KVM and
 guest
Date: Wed,  6 Nov 2019 19:54:58 +0800
Message-Id: <1573041302-4904-1-git-send-email-zhenzhong.duan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1911060119
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9432
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1911060119
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset tries to fix below issues:

1. Admin could set halt_poll_ns to 0 at runtime to disable poll and kernel
behave just like the generic halt driver. Then If guest_halt_poll_grow_start
is set to 0 and guest_halt_poll_ns set to nonzero later, cpu_halt_poll_us will
never grow beyond 0. The first two patches fix this issue from both kvm and
guest side.

2. guest_halt_poll_grow_start and guest_halt_poll_ns could be adjusted at
runtime by admin, this could make a window where cpu_halt_poll_us jump out
of the boundary. the window could be long in some cases(e.g. guest_halt_poll_grow_start
is bumped and cpu_halt_poll_us is shrinking) The last two patches fix this
issue from both kvm and guest side.

3. The 4th patch also simplifies branch check code.

v2:
Rewrite the patches and drop unnecessory changes

Zhenzhong Duan (4):
  cpuidle-haltpoll: ensure grow start value is nonzero
  KVM: ensure grow start value is nonzero
  cpuidle-haltpoll: ensure cpu_halt_poll_us in right scope
  KVM: ensure vCPU halt_poll_us in right scope

 drivers/cpuidle/governors/haltpoll.c | 50 ++++++++++++++++++++++++-----------
 virt/kvm/kvm_main.c                  | 51 ++++++++++++++++++++++++------------
 2 files changed, 68 insertions(+), 33 deletions(-)
```
#### [kvm-unit-tests Patch v1 0/2] x86: Test IOAPIC physical and logical
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
From patchwork Wed Nov  6 12:47:07 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11230215
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 571831850
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 12:47:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2816D2187F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 12:47:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="am6ub5rt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730463AbfKFMrc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 07:47:32 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:56543 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1729960AbfKFMrc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 07:47:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573044451;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=pYRrDS+0x4JMzriQZzGqlme+/7LuWFuZEAXFd7mTkQ8=;
        b=am6ub5rt99aPaJwdHL8COA27NAxAD9/j+ecGcJTUMWlLiWxUOn46VQugYnKHfftHTctIuW
        lbxzY3sR+E1zAX0fzR08CkX24erpW++UNQlRIoXxxP94iP/JGU5lSbB10U/5AS2UKh40Wm
        B0YUCyMeiXqjOVPTX9HqTfzXpo6ZUnY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-369-OoiaJ6s-Pm-xlTdxl-6uUw-1; Wed, 06 Nov 2019 07:47:25 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7A1821005500
        for <kvm@vger.kernel.org>; Wed,  6 Nov 2019 12:47:24 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B8579600D5;
        Wed,  6 Nov 2019 12:47:20 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, thuth@redhat.com,
        mtosatti@redhat.com
Subject: [kvm-unit-tests Patch v1 0/2] x86: Test IOAPIC physical and logical
 destination mode
Date: Wed,  6 Nov 2019 07:47:07 -0500
Message-Id: <1573044429-7390-1-git-send-email-nitesh@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: OoiaJ6s-Pm-xlTdxl-6uUw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first patch adds smp configuration to ioapic unittest and
the second one adds the support to test both physical and logical destination
modes under fixed delivery mode.

Nitesh Narayan Lal (2):
  x86: ioapic: Add the smp configuration to ioapic unittest
  x86: ioapic: Test physical and logical destination mode

 x86/ioapic.c      | 65 +++++++++++++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg |  1 +
 2 files changed, 66 insertions(+)
```
#### [PATCH v1 0/2] KVM: deliver IOAPIC scan request only to the target
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
From patchwork Wed Nov  6 13:36:36 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Nitesh Narayan Lal <nitesh@redhat.com>
X-Patchwork-Id: 11230347
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B47481599
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8FEDE21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MT8FjZlC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731714AbfKFNhR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 08:37:17 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55597 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727022AbfKFNhE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 08:37:04 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573047423;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=a4A/mMQkY14kjAgt3Bt+aoHAn+YimNMP05kIez+opDg=;
        b=MT8FjZlC2HKlhqsEtif1OwmvxkSw9A2NMYjrPNqC5sziS3io0KIMoY+W57atFSOh2XYsWE
        dCqqQmlB0WH0/aDVyizMT9dhHy14GUH9uYp7WMvPMI47cnMooC3S+I1vVoJQd/ISGGKgIO
        8k1yCONs18cY5mkr/zpd9mJPHjk3fR4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-177-3lGQ8HhkMcaUc1z8XZXVGA-1; Wed, 06 Nov 2019 08:37:00 -0500
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2F3F7477;
        Wed,  6 Nov 2019 13:36:58 +0000 (UTC)
Received: from virtlab512.virt.lab.eng.bos.redhat.com
 (virtlab512.virt.lab.eng.bos.redhat.com [10.19.152.206])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 449395D9E5;
        Wed,  6 Nov 2019 13:36:51 +0000 (UTC)
From: Nitesh Narayan Lal <nitesh@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mtosatti@redhat.com, rkrcmar@redhat.com,
        vkuznets@redhat.com, sean.j.christopherson@intel.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org
Subject: [PATCH v1 0/2] KVM: deliver IOAPIC scan request only to the target
 vCPUs
Date: Wed,  6 Nov 2019 08:36:36 -0500
Message-Id: <1573047398-7665-1-git-send-email-nitesh@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-MC-Unique: 3lGQ8HhkMcaUc1z8XZXVGA-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IOAPIC scan requests with fixed delivery mode should only be delivered to the vCPUs
specified by the destination ID.
The second patch in this patch-set introduces an additional
kvm_get_dest_vcpus_mask() API which retrieves a bitmap with bits set for each
target vCPUs. This bitmap is later passed on to the kvm_make_vcpus_request_mask().

I have re-used the patch sent by Radim Krčmář, which adds the support to
remember the position of each vCPUs in kvm->vcpus array.
As I needed to find out the vCPUs index in kvm->vcpus array for setting the
bits in the bitmap corresponding to the target vCPUs.

This support will enable us to reduce the latency overhead on isolated
vCPUs caused by the IPI to process due to KVM_REQ_IOAPIC_SCAN. With the current
implementation, the KVM_REQ_IOAPIC_SCAN is flushed on to all the vCPUs even
if it is meant for just one of them.

Testing:
I have added the support for testing IOAPIC logical and physical destination
mode under Fixed Delivery mode to kvm-unit-test and used it to test this patch.
https://patchwork.kernel.org/cover/11230215/

Nitesh Narayan Lal (1):
  KVM: x86: deliver KVM IOAPIC scan request to target vCPUs

Radim Krčmář (1):
  KVM: remember position in kvm->vcpus array

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/ioapic.c           | 33 ++++++++++++++++++++++++++++--
 arch/x86/kvm/lapic.c            | 45 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/lapic.h            |  3 +++
 arch/x86/kvm/x86.c              |  6 ++++++
 include/linux/kvm_host.h        | 13 +++++-------
 virt/kvm/kvm_main.c             | 19 ++++++++++++++++-
 7 files changed, 110 insertions(+), 11 deletions(-)
```
#### [PATCH V10 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Nov  6 13:35:25 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11230349
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DBE914E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F2942218AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 13:37:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gmpRpEJE"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731752AbfKFNhc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 08:37:32 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:36421 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731734AbfKFNhb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Nov 2019 08:37:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573047450;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=/s0k4qOLB5UOKCj30GSBInNIxwTgiYyppdT2vH2+WjY=;
        b=gmpRpEJEe9WA8/VON8MCK3hKz35Iv88V5XwL2X4ogTWY9PKGGgE5dRWpjOwtcQejTaiHmG
        jIe1FgCdRVEhM5fg/rwgocs69V3jBdE1SHZqB261Gpy7zmx2CKVIiVg4ayJcfs1jjWSRXD
        dCHGEPs8KN7gu/6r2Joqe4338xu30uM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-343-L9tT79FEPFObmEa3AfYP2Q-1; Wed, 06 Nov 2019 08:37:27 -0500
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 24B2C8017E0;
        Wed,  6 Nov 2019 13:37:23 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-193.pek2.redhat.com [10.72.12.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2235A27067;
        Wed,  6 Nov 2019 13:35:45 +0000 (UTC)
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
        stefanha@redhat.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V10 0/6] mdev based hardware virtio offloading support
Date: Wed,  6 Nov 2019 21:35:25 +0800
Message-Id: <20191106133531.693-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-MC-Unique: L9tT79FEPFObmEa3AfYP2Q-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

There are hardwares that can do virtio datapath offloading while
having its own control path. This path tries to implement a mdev based
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

Also a real IFC VF driver was also posted here[2] which is a good
reference for vendors who is interested in their own virtio datapath
offloading product.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific ops out of the common ones for implementing class
specific operations over mdev bus.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/11/5/424
[2] https://lkml.org/lkml/2019/11/5/227

Changes from V9:
- Tweak the help text for virito-mdev kconfig

Changes from V8:
- try silent checkpatch, some are still there becuase they were inherited
  from virtio_config_ops which needs to be resolved in an independent series
- tweak on the comment and doc
- remove VIRTIO_MDEV_F_VERSION_1 completely
- rename CONFIG_VIRTIO_MDEV_DEVICE to CONFIG_VIRTIO_MDEV

Changes from V7:
- drop {set|get}_mdev_features for virtio
- typo and comment style fixes

Changes from V6:
- rename ops files and compile guard

Changes from V5:
- use dev_warn() instead of WARN(1) when class id is not set
- validate id_table before trying to do matching between device and
  driver
- add wildcard for modpost script
- use unique name for id_table
- move get_mdev_features() to be the first member of virtio_device_ops
  and more comments for it
- typo fixes for the comments above virtio_mdev_ops

Changes from V4:
- keep mdev_set_class() for the device that doesn't use device ops
- use union for device ops pointer in mdev_device
- introduce class specific helper for getting is device ops
- use WARN_ON instead of BUG_ON in mdev_set_virtio_ops
- explain details of get_mdev_features() and get_vendor_id()
- distinguish the optional virito device ops from mandatory ones and
  make get_generation() optional
- rename vfio_mdev.h to vfio_mdev_ops.h, rename virito_mdev.h to
  virtio_mdev_ops.h
- don't abuse version fileds in virtio_mdev structure, use features
  instead
- fix warning during device remove
- style & docs tweaks and typo fixes

Changes from V3:
- document that class id (device ops) must be specified in create()
- add WARN() when trying to set class_id when it has already set
- add WARN() when class_id is not specified in create() and correctly
  return an error in this case
- correct the prototype of mdev_set_class() in the doc
- add documention of mdev_set_class()
- remove the unnecessary "class_id_fail" label when class id is not
  specified in create()
- convert id_table in vfio_mdev to const
- move mdev_set_class and its friends after mdev_uuid()
- suqash the patch of bus uevent into patch of introducing class id
- tweak the words in the docs per Cornelia suggestion
- tie class_id and device ops through class specific initialization
  routine like mdev_set_vfio_ops()
- typos fixes in the docs of virtio-mdev callbacks
- document the usage of virtqueues in struct virtio_mdev_device
- remove the useless vqs array in struct virtio_mdev_device
- rename MDEV_ID_XXX to MDEV_CLASS_ID_XXX

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

Jason Wang (6):
  mdev: class id support
  modpost: add support for mdev class id
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  38 +-
 MAINTAINERS                                   |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  60 ++
 drivers/vfio/mdev/mdev_driver.c               |  25 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |  13 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 406 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mdev_vfio_ops.h                 |  52 ++
 include/linux/mdev_virtio_ops.h               | 147 ++++
 include/linux/mod_devicetable.h               |   8 +
 samples/Kconfig                               |  10 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 686 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  11 +
 24 files changed, 1585 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/mdev_vfio_ops.h
 create mode 100644 include/linux/mdev_virtio_ops.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH 0/2] KVM: MMU: Fix a refcount bug with ZONE_DEVICE pages
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Nov  6 17:07:25 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11230759
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 933EB1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:07:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7475A21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:07:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732336AbfKFRHf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 12:07:35 -0500
Received: from mga06.intel.com ([134.134.136.31]:58093 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727894AbfKFRH3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 12:07:29 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Nov 2019 09:07:28 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,275,1569308400";
   d="scan'208";a="192527997"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga007.jf.intel.com with ESMTP; 06 Nov 2019 09:07:28 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Adam Borowski <kilobyte@angband.pl>,
        David Hildenbrand <david@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH 0/2] KVM: MMU: Fix a refcount bug with ZONE_DEVICE pages
Date: Wed,  6 Nov 2019 09:07:25 -0800
Message-Id: <20191106170727.14457-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This mini-series fixes a suspected, but technically unconfirmed, bug in
KVM related to ZONE_DEVICE pages.  The suspected issue is that KVM treats
ZONE_DEVICE pages as reserved PFNs, and so doesn't put references to such
pages when dropping references via KVM's generic kvm_release_pfn_clean().

David Hildenbrand uncovered the bug during a discussion about removing
PG_reserved from ZONE_DEVICE pages, after Dan Williams pointed out[1] that
there was a bug report from Adam Borowski[2] that was likely related to
KVM's interaction with PageReserved().

Patch 1/2 contains the actual fix, patch 2/2 is a minor cleanup that is
mostly unrelated, but dependent and prompted by the fix in patch 1/2.

The fix itself is a bit more aggressive than what was proposed by David
and Dan, but I'm fairly confident it's the right direction for the long
term, and it also plays nice with the original PG_reserved removal series
that exposed the bug.

To be 100% clear, I haven't actually confirmed this fixes the bug reported
by Adam.

[1] http://lkml.kernel.org/r/20190919115547.GA17963@angband.pl
[2] https://lkml.kernel.org/r/01adb4cb-6092-638c-0bab-e61322be7cf5@redhat.com

Sean Christopherson (2):
  KVM: MMU: Do not treat ZONE_DEVICE pages as being reserved
  KVM: x86/mmu: Add helper to consolidate huge page promotion

 arch/x86/kvm/mmu.c       | 15 +++++++++------
 include/linux/kvm_host.h |  1 +
 virt/kvm/kvm_main.c      | 19 +++++++++++++++----
 3 files changed, 25 insertions(+), 10 deletions(-)
```
#### [PATCH v1 0/3] KVM: VMX: Posted Interrupts fixes
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
From patchwork Wed Nov  6 17:55:59 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11230801
Return-Path: <SRS0=/jDW=Y6=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0700A1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:57:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA4D621848
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  6 Nov 2019 17:57:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Z0gJMfyM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732492AbfKFR5v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 Nov 2019 12:57:51 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:59272 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727872AbfKFR5u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 Nov 2019 12:57:50 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6HsKGa015768;
        Wed, 6 Nov 2019 17:56:27 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=uBEGSNLJVxXMk9u64tP8o0TzUbcsZmdPCKdTVcSvJeg=;
 b=Z0gJMfyMXtJfFJvsCCk7dUZmTg2FxtLGV8ypVvVVh/r2U2ssB4M1JSKBCZ7ngUiSP63l
 TdlbQUPyRWyP6ztuSsDxHSmanSKzk6xbmNL7F9k60eduhnRKaZWaIT7iccE3JaaSVlDc
 YgmzhK8+aS0tRuuVYkD+6m3tuE6psYaKTD8q9+MJSVIpzYD/iLCj2feZBsnDdzsIQbEZ
 2GEscujetQ+ao/bCwK0nePNYneRimlznnObMkFA5mFK4rpd19CIKIbJ8giZO/k9rZrRd
 NsJLqYYIBn3R6Wq5a70K9RGXb5XAwtvBzcJhV2944sWfiSDAYu401kbJ6hFTFSuAYuH9 Jg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2130.oracle.com with ESMTP id 2w41w10m56-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 17:56:27 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xA6Hreox022490;
        Wed, 6 Nov 2019 17:56:26 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2w41wcvewg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 06 Nov 2019 17:56:26 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xA6HuNS0003881;
        Wed, 6 Nov 2019 17:56:24 GMT
Received: from paddy.uk.oracle.com (/10.175.178.239)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Wed, 06 Nov 2019 09:56:23 -0800
From: Joao Martins <joao.m.martins@oracle.com>
To: kvm@vger.kernel.org
Cc: Joao Martins <joao.m.martins@oracle.com>, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Liran Alon <liran.alon@oracle.com>, Jag Raman <jag.raman@oracle.com>
Subject: [PATCH v1 0/3] KVM: VMX: Posted Interrupts fixes
Date: Wed,  6 Nov 2019 17:55:59 +0000
Message-Id: <20191106175602.4515-1-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9433
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=600
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1910280000 definitions=main-1911060173
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9433
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=680 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1910280000
 definitions=main-1911060174
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hey,

This mini-series addresses two bugs plus a small cleanup: 

 1) Considering PID.PIR as opposed to just PID.ON for pending interrupt checks
    in the direct yield code path;
 
 2) Not changing NDST in vmx_vcpu_pi_load(), which addresses a regression. 
    Prior to this, we would observe Win2K12 guests hanging momentarily.
 
 3) Small cleanup to streamline PIR checks with a common helper.

The cleanup is done last to simplify backports.

	Joao

Joao Martins (3):
  KVM: VMX: Consider PID.PIR to determine if vCPU has pending interrupts
  KVM: VMX: Do not change PID.NDST when loading a blocked vCPU
  KVM: VMX: Introduce pi_is_pir_empty() helper

 arch/x86/kvm/vmx/vmx.c | 20 ++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.h | 11 +++++++++++
 2 files changed, 29 insertions(+), 2 deletions(-)
```
