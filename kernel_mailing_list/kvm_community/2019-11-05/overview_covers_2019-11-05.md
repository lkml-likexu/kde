

#### [PATCH V8 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Tue Nov  5 09:32:34 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11227365
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78DD41986
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:33:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4D23F21D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:33:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="YM36kONI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387917AbfKEJdv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:33:51 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:26961 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730693AbfKEJdv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 04:33:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572946429;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=E12QQhoLkodtr7tObwU2tg4h6lVPBMRwKLoDjj8IKNc=;
        b=YM36kONIdLW/acsucHq4hbC3waoVWoIaMlrOxnedoIxZGxP+NZRNPbs4MqIG5EuGZjU1bL
        0kAcN7QdeBbXT8MbCbYxgW8c6c3FwaiYhjMl7BhrzMEZAZ0dytZOrELHPYkiU8shtpb8uG
        1Afa/ME8MpcJueW0jfUde2OoLKFNTxc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-AOn84NNqPKWIK3fMNPFBLw-1; Tue, 05 Nov 2019 04:33:45 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EFDCD107ACC2;
        Tue,  5 Nov 2019 09:33:40 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-252.pek2.redhat.com [10.72.12.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 255BC5C1B2;
        Tue,  5 Nov 2019 09:32:45 +0000 (UTC)
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
Subject: [PATCH V8 0/6] mdev based hardware virtio offloading support
Date: Tue,  5 Nov 2019 17:32:34 +0800
Message-Id: <20191105093240.5135-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: AOn84NNqPKWIK3fMNPFBLw-1
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

Also a real ICF VF driver was also posted here[2] which is a good
reference for vendors who is interested in their own virtio datapath
offloading product.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/10/31/440
[2] https://lkml.org/lkml/2019/10/15/1226

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
 MAINTAINERS                                   |   2 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  60 ++
 drivers/vfio/mdev/mdev_driver.c               |  25 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 407 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mdev_vfio_ops.h                 |  52 ++
 include/linux/mdev_virtio_ops.h               | 149 ++++
 include/linux/mod_devicetable.h               |   8 +
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 685 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  11 +
 24 files changed, 1577 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/mdev_vfio_ops.h
 create mode 100644 include/linux/mdev_virtio_ops.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH 0/2] Intel IFC VF driver for VDPA
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Tue Nov  5 09:37:38 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11227403
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6114B1747
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:39:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48C312190F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 09:39:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730930AbfKEJjv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 04:39:51 -0500
Received: from mga02.intel.com ([134.134.136.20]:24242 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730630AbfKEJjv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 04:39:51 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Nov 2019 01:39:50 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,270,1569308400";
   d="scan'208";a="200323047"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.79])
  by fmsmga008.fm.intel.com with ESMTP; 05 Nov 2019 01:39:47 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        netdev@vger.kernel.org, dan.daly@intel.com,
        cunming.liang@intel.com, tiwei.bie@intel.com, jason.zeng@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/2] Intel IFC VF driver for VDPA
Date: Tue,  5 Nov 2019 17:37:38 +0800
Message-Id: <1572946660-26265-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:
  This series intends to introduce Intel IFC VF NIC driver for Vhost
Data Plane Acceleration(VDPA).
  
Here comes two main parts, one is ifcvf_base layer, which handles
hardware operations. The other is ifcvf_main layer handles VF
initialization, configuration and removal, which depends on
and complys to:
virtio_mdev https://lkml.org/lkml/2019/10/30/62 
vhost_mdev https://lkml.org/lkml/2019/10/31/440

This patchset passed netperf tests.

This is RFC V2, plese help review.

Changes from V1:
using le32_to_cpu() to convert PCI capabilities.
some set /get  operations will sync with the hardware, eg get_status
and get_generation.
remove feature bit VHOST_F_LOG_ALL, add VIRTIO_F_ORDERED_PLATFORM
add get/set_config functions.
split mdev type group into mdev_type_group_virtio and mdev_type_group_vhost
add ifcvf_mdev_get_mdev_features()
coding stype changes.

Zhu Lingshan (2):
  IFC hardware operation layer
  IFC VDPA layer

 drivers/vhost/ifcvf/ifcvf_base.c | 344 ++++++++++++++++++++++
 drivers/vhost/ifcvf/ifcvf_base.h | 132 +++++++++
 drivers/vhost/ifcvf/ifcvf_main.c | 605 +++++++++++++++++++++++++++++++++++++++
 3 files changed, 1081 insertions(+)
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.c
 create mode 100644 drivers/vhost/ifcvf/ifcvf_base.h
 create mode 100644 drivers/vhost/ifcvf/ifcvf_main.c
```
#### [kvm-unit-tests PATCH 0/2] s390x: Improve architectural compliance
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Nov  5 16:28:26 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11228265
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5580F13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:29:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3E2EB21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 16:29:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390213AbfKEQ3E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 11:29:04 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63804 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390156AbfKEQ3E (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 5 Nov 2019 11:29:04 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xA5GPFCR124650
        for <kvm@vger.kernel.org>; Tue, 5 Nov 2019 11:29:03 -0500
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w3bmf35ku-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 05 Nov 2019 11:29:02 -0500
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 5 Nov 2019 16:29:01 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 5 Nov 2019 16:28:59 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xA5GSweg50987232
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 5 Nov 2019 16:28:58 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1F3DC42049;
        Tue,  5 Nov 2019 16:28:58 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5B32342045;
        Tue,  5 Nov 2019 16:28:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  5 Nov 2019 16:28:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com
Subject: [kvm-unit-tests PATCH 0/2] s390x: Improve architectural compliance
 for diag308
Date: Tue,  5 Nov 2019 11:28:26 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19110516-0012-0000-0000-00000360F328
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19110516-0013-0000-0000-0000219C4D29
Message-Id: <20191105162828.2490-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-05_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=622 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1911050135
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When testing diag308 subcodes 0/1 on lpar with virtual mem set up, I
experienced spec PGMs and addressing PGMs due to the tests not setting
short psw bit 12 and leaving the DAT bit on.

The problem was not found under KVM/QEMU, because Qemu just ignores
all cpu mask bits... I'm working on a fix for that too.

Janosch Frank (2):
  s390x: Add CR save area
  s390x: Remove DAT and add short indication psw bits on diag308 reset

 lib/s390x/asm-offsets.c  |  3 ++-
 lib/s390x/asm/arch_def.h |  5 +++--
 lib/s390x/interrupt.c    |  4 ++--
 lib/s390x/smp.c          |  2 +-
 s390x/cstart64.S         | 29 ++++++++++++++++++++---------
 5 files changed, 28 insertions(+), 15 deletions(-)
```
#### [PATCH v2 0/4] Add support for capturing the highest observable L2
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Tue Nov  5 19:19:06 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11228439
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 508521515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 19:19:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 384C321882
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 19:19:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Q83ssdA7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390851AbfKETTQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 14:19:16 -0500
Received: from mail-qk1-f202.google.com ([209.85.222.202]:41126 "EHLO
        mail-qk1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390846AbfKETTQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 14:19:16 -0500
Received: by mail-qk1-f202.google.com with SMTP id c77so13535871qkb.8
        for <kvm@vger.kernel.org>; Tue, 05 Nov 2019 11:19:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=xfZE4ufavvJ0RzooombkODbK6fViaORENfN+oeuw9Y8=;
        b=Q83ssdA7PtucW8NOFV2LvEqAzAv7xHyjKpg28TyxhEvoAeRTc0S13eCVlam2e7zL3a
         f7HW4eufYRxFPVT66ZQCVhiKpx8bIa0B/BJtuxgtLyuy0WRJChmO5oiYXRCXp4LyucdU
         E6XZO7C8lF3iyA/wBRRoiZCao3RDtyLRsxb44u46rC/agZeLuA7U/+S52q4cikbMXDnu
         BsyMFRQb62Jtv/684iq9VC5/pNCXyhuXcVs5bEVkpzP1MyULSa/LdmWtR8SaeSu9Y95W
         hRKxK0Uj1iBraeXh/TO2gm5gCy175x71w1ZMyMVs0tBjhRAm/prXcDUqMs1t6I/esQrd
         uUFA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=xfZE4ufavvJ0RzooombkODbK6fViaORENfN+oeuw9Y8=;
        b=JILHBpbC/1k+XjbXDwKJMT1WpQXlE4Qa0WAzyBu5yfuIlzP/N8AAjyo8oDYY9iX3U/
         0WF3qDf+/KoUMhsku/qlaSB7juOWPsQagkA6kQHcA8VJJNuB1Y4HRT5Qi5oUKRELMVN9
         w+3bkx/qBNF7v2KuWiAKvHR67y7dTAmY3yqnEm+cxUdSXx4V7NgdFlQugGxyY6hZLsH+
         Y6dIFDpq8SK4yrEE7LdzicFNrDiQJ+ZCMue7OkvPByDSChFl6t1UL051OOJ8FfCT3vwt
         M4G5f5Kvwy5HboDPL2R+BGhv7bESYgrpi8rCMbWSVN3fvHOAYjScBsRUzlWA5/133knT
         b1MA==
X-Gm-Message-State: APjAAAWKee7BA/YSNKr/UVC32fHPo/cj705Hp+wwuzfaKSmi3YCLbM1+
        ymyLRWaulkVsAJSpYKXFMmYXMz5DZ1ZHFHO7FeGKLXiSa3L1KgZ9pXD4BLCY9IppokoIR7dpJ1Z
        Xl7xzUWZnd3LzInLFXK6G7WVZ/PiH28RfGKuyFGw/W9//8A89RuyB4PhgQgxmMdS6V+Wq
X-Google-Smtp-Source: 
 APXvYqxrWrFPYJzAJtXYVIj3X0cUbwWi5qEjLadWj/1xPJ1UEcmkCzu7nEWP5HLIlGBG/GtQA3HEu7Ej5gV9pco2
X-Received: by 2002:ac8:3fed:: with SMTP id
 v42mr11824280qtk.171.1572981554829;
 Tue, 05 Nov 2019 11:19:14 -0800 (PST)
Date: Tue,  5 Nov 2019 11:19:06 -0800
Message-Id: <20191105191910.56505-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [PATCH v2 0/4] Add support for capturing the highest observable L2
 TSC
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The L1 hypervisor may include the IA32_TIME_STAMP_COUNTER MSR in the
vmcs12 MSR VM-exit MSR-store area as a way of determining the highest
TSC value that might have been observed by L2 prior to VM-exit. The
current implementation does not capture a very tight bound on this
value.  To tighten the bound, add the IA32_TIME_STAMP_COUNTER MSR to the
vmcs02 VM-exit MSR-store area whenever it appears in the vmcs12 VM-exit
MSR-store area.  When L0 processes the vmcs12 VM-exit MSR-store area
during the emulation of an L2->L1 VM-exit, special-case the
IA32_TIME_STAMP_COUNTER MSR, using the value stored in the vmcs02
VM-exit MSR-store area to derive the value to be stored in the vmcs12
VM-exit MSR-store area.

v1 -> v2:
 - Rename function nested_vmx_get_msr_value() to
   nested_vmx_get_vmexit_msr_value().
 - Remove unneeded tag 'Change-Id' from commit messages.

Aaron Lewis (4):
  kvm: nested: Introduce read_and_check_msr_entry()
  kvm: vmx: Rename NR_AUTOLOAD_MSRS to NR_MSR_ENTRIES
  kvm: vmx: Rename function find_msr() to vmx_find_msr_index()
  KVM: nVMX: Add support for capturing highest observable L2 TSC

 arch/x86/kvm/vmx/nested.c | 127 ++++++++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.c    |  14 ++---
 arch/x86/kvm/vmx/vmx.h    |   9 ++-
 3 files changed, 122 insertions(+), 28 deletions(-)
---
2.24.0.rc1.363.gb1bccd3e3d-goog
```
#### [PATCH v4 0/5] KVM: Unify mmu_memory_cache functionality across
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
From patchwork Tue Nov  5 11:03:52 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christoffer Dall <christoffer.dall@arm.com>
X-Patchwork-Id: 11228495
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A27DD1850
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 20:30:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 948A221D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 20:30:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728400AbfKEU35 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 15:29:57 -0500
Received: from foss.arm.com ([217.140.110.172]:59866 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727339AbfKEU35 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 15:29:57 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 9120064F;
        Tue,  5 Nov 2019 12:29:56 -0800 (PST)
Received: from localhost (e113682-lin.copenhagen.arm.com [10.32.145.14])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1C9EE3FE14;
        Tue,  5 Nov 2019 03:04:00 -0800 (PST)
From: Christoffer Dall <christoffer.dall@arm.com>
To: kvm@vger.kernel.org
Cc: kvmarm@lists.cs.columbia.edu, Christoffer Dall <christoffer.dall@arm.com>,
 James Hogan <jhogan@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Marc Zyngier <maz@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Anshuman Khandual <anshuman.khandual@arm.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Mike Rapoport <rppt@linux.ibm.com>
Subject: [PATCH v4 0/5] KVM: Unify mmu_memory_cache functionality across
 architectures
Date: Tue,  5 Nov 2019 12:03:52 +0100
Message-Id: <20191105110357.8607-1-christoffer.dall@arm.com>
X-Mailer: git-send-email 2.18.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently have duplicated functionality for the mmu_memory_cache used
to pre-allocate memory for the page table manipulation code which cannot
allocate memory while holding spinlocks.  This functionality is
duplicated across x86, arm/arm64, and mips.

This was motivated by a debate of modifying the arm code to be more in
line with the x86 code and some discussions around changing the page
flags used for allocation.  This series should make it easier to take a
uniform approach across architectures.

While there's not a huge amount of code sharing, we come out with a net
gain, and the real win is in the consistency of how we allocate memory
for page tables used by secondary MMUs driven by KVM in Linux.

Only tested on arm/arm64, and only compile-tested on x86 and mips.  I'm
especially curious on getting feedback on the change of GFP flags for
x86 (patch 1) and on the use of __GFP_ACCOUNT for mips.

Changes since v3:
 - Moved to common GFP_PGTABLE_USER definition for page allocations in
   the MMU cache for all three architectures.  This follows recent work
   which already did this for arm/arm64.
 - Rebased on v5.4-rc4.

Changes since v2:
 - Simplified kalloc flag definitions as per Paolo's review comment.

Changes since v1:
 - Split out rename from initial x86 patch to have separate patches to
   move the logic to common code and to rename.
 - Introduce KVM_ARCH_WANT_MMU_MEMCACHE to avoid compile breakage on
   architectures that don't use this functionality.
 - Rename KVM_NR_MEM_OBJS to KVM_MMU_NR_MEMCACHE_OBJS

Christoffer Dall (5):
  KVM: x86: Move memcache allocation to GFP_PGTABLE_USER
  KVM: x86: Move mmu_memory_cache functions to common code
  KVM: x86: Rename mmu_memory_cache to kvm_mmu_memcache
  KVM: arm/arm64: Move to common kvm_mmu_memcache infrastructure
  KVM: mips: Move to common kvm_mmu_memcache infrastructure

 arch/arm/include/asm/kvm_host.h      | 13 +---
 arch/arm/include/asm/kvm_mmu.h       |  2 +-
 arch/arm/include/asm/kvm_types.h     |  9 +++
 arch/arm64/include/asm/kvm_host.h    | 13 +---
 arch/arm64/include/asm/kvm_mmu.h     |  2 +-
 arch/arm64/include/asm/kvm_types.h   |  9 +++
 arch/mips/include/asm/kvm_host.h     | 15 +----
 arch/mips/include/asm/kvm_types.h    |  9 +++
 arch/mips/kvm/mips.c                 |  2 +-
 arch/mips/kvm/mmu.c                  | 54 +++-------------
 arch/powerpc/include/asm/kvm_types.h |  5 ++
 arch/s390/include/asm/kvm_types.h    |  5 ++
 arch/x86/include/asm/kvm_host.h      | 17 +----
 arch/x86/include/asm/kvm_types.h     |  9 +++
 arch/x86/kvm/mmu.c                   | 97 ++++++----------------------
 arch/x86/kvm/paging_tmpl.h           |  4 +-
 include/linux/kvm_host.h             | 11 ++++
 include/linux/kvm_types.h            | 13 ++++
 virt/kvm/arm/arm.c                   |  2 +-
 virt/kvm/arm/mmu.c                   | 68 +++++--------------
 virt/kvm/kvm_main.c                  | 61 +++++++++++++++++
 21 files changed, 190 insertions(+), 230 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_types.h
 create mode 100644 arch/arm64/include/asm/kvm_types.h
 create mode 100644 arch/mips/include/asm/kvm_types.h
 create mode 100644 arch/powerpc/include/asm/kvm_types.h
 create mode 100644 arch/s390/include/asm/kvm_types.h
 create mode 100644 arch/x86/include/asm/kvm_types.h
```
#### [PATCH v3 0/2] Update UMIP config parameter and docs
##### From: "Moger, Babu" <Babu.Moger@amd.com>

```c
From patchwork Tue Nov  5 21:25:20 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Moger, Babu" <babu.moger@amd.com>
X-Patchwork-Id: 11228753
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D694112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 21:25:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7A7E121929
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 21:25:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="0PfJBUVa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729813AbfKEVZX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 16:25:23 -0500
Received: from mail-eopbgr720070.outbound.protection.outlook.com
 ([40.107.72.70]:53109
        "EHLO NAM05-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728515AbfKEVZX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 16:25:23 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=A8M8S9X8YHJZ9sfnUSwrTkEc21ilCSPZbUOMFGzfewyIZyK4fy90c7On2WKJUTRROg1q/awEER6h5VXijD5YtE0/TQloTC4SuxytmA5R/Fy5ms/9WlDweqjvdfC6iVTlPbbmk0e5Vbn/6TtBOIC2BDNWblN/5xaECKtZUGzJ2ONigvpNHmT+0hZZwoC32RlWM4UWqF5yqTh+Gb6UPUWzOwEoga76xmvLimvaSCtnw5wFuv20ZA2QGxhJYH3SumUu4N3mDFebh1ljtY2f8XEIWEzJ2hBLqp7+64RfrnL0kbrKHAqQOCo5akNq2YykZJgx3ggKwTUQYlXaCQZBsUxKPw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ag9cHqeXy5MJ57oTJjOmPRlWj0dDM16w01rExDwIc8Q=;
 b=A5cvmjE0FUyR3TyaP644a7YoFrAv9DbEeQK3E2lNYm/KIuN830m3kuetSU0ZaiaUouccfqK04CwQIZlG70KRWJvgcI6kHIR88tzGT1Aqdy4pbMFGshInXizGSYk7tN3r3Ezt2v2tdQCeMJWHV7IitcFuHmq9tld2f5TObEke9TU26ZNyRRlzDR6gjJq36/gI10mGDkyd6m7/8enhCwKVRUA+cRarC1ZSy28i2SKI2QLdzZUzy5cJxvkERT+wIvmkb5uyN1vIcvpXOIFAiMOwNLrlrzoqUy5fUIRiZu09ONDZiKbP67KirJ0hJnjNNwMS07xKx83WTMxhcZTFRhGu7Q==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ag9cHqeXy5MJ57oTJjOmPRlWj0dDM16w01rExDwIc8Q=;
 b=0PfJBUVaSbzcVRmzq1dcbuVaCrxMa4Yi/iLqfAe5CTQkaZNIo4tY3DuQdoAr5ZqndKd0L9jHnRVl1eRLdoltQw0EAsww9yEyMjgbeg6h5qBZtvotyM7d2H6+gRCuAa55MTu/oQe6UQ/91dnh7+dY4fqOKcGL7v9KGQckhJBHEPo=
Received: from DM5PR12MB2471.namprd12.prod.outlook.com (52.132.141.138) by
 DM5PR12MB1195.namprd12.prod.outlook.com (10.168.240.14) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2408.24; Tue, 5 Nov 2019 21:25:20 +0000
Received: from DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999]) by DM5PR12MB2471.namprd12.prod.outlook.com
 ([fe80::c5a3:6a2e:8699:1999%6]) with mapi id 15.20.2408.024; Tue, 5 Nov 2019
 21:25:20 +0000
From: "Moger, Babu" <Babu.Moger@amd.com>
To: "tglx@linutronix.de" <tglx@linutronix.de>,
        "mingo@redhat.com" <mingo@redhat.com>,
        "bp@alien8.de" <bp@alien8.de>, "hpa@zytor.com" <hpa@zytor.com>,
        "pbonzini@redhat.com" <pbonzini@redhat.com>,
        "rkrcmar@redhat.com" <rkrcmar@redhat.com>,
        "sean.j.christopherson@intel.com" <sean.j.christopherson@intel.com>,
        "vkuznets@redhat.com" <vkuznets@redhat.com>,
        "wanpengli@tencent.com" <wanpengli@tencent.com>,
        "jmattson@google.com" <jmattson@google.com>
CC: "x86@kernel.org" <x86@kernel.org>,
        "joro@8bytes.org" <joro@8bytes.org>,
        "Moger, Babu" <Babu.Moger@amd.com>,
        "luto@kernel.org" <luto@kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "nayna@linux.ibm.com" <nayna@linux.ibm.com>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "zohar@linux.ibm.com" <zohar@linux.ibm.com>,
        "yamada.masahiro@socionext.com" <yamada.masahiro@socionext.com>,
        "ebiederm@xmission.com" <ebiederm@xmission.com>,
        "ricardo.neri-calderon@linux.intel.com"
        <ricardo.neri-calderon@linux.intel.com>,
        "bshanks@codeweavers.com" <bshanks@codeweavers.com>
Subject: [PATCH v3 0/2] Update UMIP config parameter and docs
Thread-Topic: [PATCH v3 0/2] Update UMIP config parameter and docs
Thread-Index: AQHVlB+GGc0dpKFRika7sFVswTRcfQ==
Date: Tue, 5 Nov 2019 21:25:20 +0000
Message-ID: <157298900783.17462.2778215498449243912.stgit@naples-babu.amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: SN6PR2101CA0019.namprd21.prod.outlook.com
 (2603:10b6:805:106::29) To DM5PR12MB2471.namprd12.prod.outlook.com
 (2603:10b6:4:b5::10)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Babu.Moger@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.2]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: 62149737-f9b4-42d7-fd7b-08d76236a90c
x-ms-traffictypediagnostic: DM5PR12MB1195:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM5PR12MB119525CD471EF5BA27BB31FB957E0@DM5PR12MB1195.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:5797;
x-forefront-prvs: 0212BDE3BE
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(396003)(376002)(366004)(136003)(346002)(199004)(189003)(2201001)(54906003)(110136005)(8676002)(7416002)(103116003)(305945005)(81156014)(81166006)(66946007)(478600001)(25786009)(66556008)(64756008)(99286004)(66476007)(7736002)(316002)(26005)(2501003)(3846002)(102836004)(52116002)(6116002)(6436002)(6506007)(386003)(86362001)(66446008)(8936002)(15650500001)(2906002)(14454004)(71200400001)(71190400001)(4744005)(256004)(6512007)(476003)(486006)(186003)(4326008)(14444005)(5660300002)(6486002)(66066001)(921003)(1121003);DIR:OUT;SFP:1101;SCL:1;SRVR:DM5PR12MB1195;H:DM5PR12MB2471.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 oOnlPsQawJIRZnk/q9q7xfj0bJjvSRJxT6NhLffT9uCU4b8CDAqnbe9g1CoKBIVzUvursflKxBZkluGGKLgjy0c71m1AqcN7paAG7IIcTfq+2k7TdCGDJ/IwxvDoKLgML6ALFLrIx749eYtPlh1ESMAEGMopy29/aOxyglMOduQ52+a08dMlzl9z+owQpb/AAIAdvAGo2e8IWQQG8OppV1LkKr57U+ZFhFt/31g5h/piYC6BtTUq5MwkQFu3wTx8K7lwQObCzxaIOuACQ+XrpqyfjQeA/ffzprSDe/V1L2vgi+luQSTdJ5ghwIHPgBVekcVA6hQ3zpfGIe4d/Ee6QEUGICpMeBOFxNzjiOP1hJLkS7rHg0FfNfbRzWlsneJRN08bnykeMPG5feE6woHmyKICgKtBvR5m6Xb2xLMKtusho0LIzjsM9dN5uI5crU+U
Content-ID: <A91190F407264842AD2DC0C30F7225D5@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 62149737-f9b4-42d7-fd7b-08d76236a90c
X-MS-Exchange-CrossTenant-originalarrivaltime: 05 Nov 2019 21:25:20.2520
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 MgqHg9E1/9AiWOVru2ze++9ac88snNMmQlmF67IC5RLAILm45/Ge4+cqJuxxrao5
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1195
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD 2nd generation EPYC processors support the UMIP feature. 
So, update the Kconfig and umip related documentation.
---
v3:
  Removed X86 depend check. Just kept CPU_SUP_* check.
  Updated the comments in umip.c to make it bit generic.

v2:
  Learned that for the hardware that support UMIP, we dont need to
  emulate. Removed the emulation related code and just submitting
  the config changes.


Babu Moger (2):
      x86/Kconfig: Rename UMIP config parameter
      x86/umip: Update the comments to cover generic x86 processors


 arch/x86/Kconfig                         |   10 +++++-----
 arch/x86/include/asm/disabled-features.h |    2 +-
 arch/x86/include/asm/umip.h              |    4 ++--
 arch/x86/kernel/Makefile                 |    2 +-
 arch/x86/kernel/umip.c                   |   12 ++++++------
 5 files changed, 15 insertions(+), 15 deletions(-)

--
```
#### [PATCH v13 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Tue Nov  5 22:02:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11228827
Return-Path: <SRS0=X2oT=Y5=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 015F31515
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:02:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D156121D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  5 Nov 2019 22:02:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="WwfTCqzZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730193AbfKEWCF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 5 Nov 2019 17:02:05 -0500
Received: from mail-pf1-f193.google.com ([209.85.210.193]:42421 "EHLO
        mail-pf1-f193.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729747AbfKEWCE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Nov 2019 17:02:04 -0500
Received: by mail-pf1-f193.google.com with SMTP id s5so8762702pfh.9;
        Tue, 05 Nov 2019 14:02:02 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=Fcg154L/fnezX3/fSPC15hneW3cO4j3xqpyZ8n4o6QY=;
        b=WwfTCqzZwoHIq0TpTCX0zNoKhEtQbyFPZ17XAQSK404ALLkSpR0pKpzbYFAU0+i38n
         EkwitgqQCuqa7vf7ejCG7Z19NbXOT8aoZ3FVL4RYwuMOPhdjTkGoUcxGO4zOKVKiMKK4
         Al1hALGqK2hXj0nLmmqLSxfXRz5cyKoGfgRV/eq9Nkd8iN7lQdY7JQfs0ZU0A3JsXmvk
         lGQSpB9YVQcPp/ujGjRZ3TvVHTnGe3T12C+eMg/JPsjHKtvQ5ealhw4WL9AI3pgVfgc+
         DEMKcI24DYyKcBSukxg4QLjNYu07E/N10RSh2GAYradq0k1TBMh5VZmT/5kG6n1pnoh2
         AABg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=Fcg154L/fnezX3/fSPC15hneW3cO4j3xqpyZ8n4o6QY=;
        b=RAOVUXA5FWL1OmR9qbuqlUgG871RrcfUGShBzqWAo+9co4eMxlkq4RAqZaOjXhF5dF
         jetjvfCvhCrUo4jnkK2Gy0CmLG/QYFhk71BvBYBHox+l9JUf9JHoMCnZeJDs6U3Swj4I
         5z1bQL0AC49Qo2PUNCXX4db3JfFHBOXh7G8X2TVQW+2evHTRq5Dfc9p+qqbPxoxcqdQz
         W78IKTbtfo1lbvd7Lx6pr7f83zyU16dPWoJw6MfYUBMn7igAGplBpYOyPBMJV5UfTttK
         0b3T56hxP2/5vnTbvtsncWqAvV3+XQeoiRSlTWf+9hZ7JavvQQ4/udzKBsouqV4nO2sF
         jXWA==
X-Gm-Message-State: APjAAAVrh3vNtx9FdznHqk3qgG8BzwUQhN9xMnwt3GI6QBsi3S2SfckU
        TpPH95V9XfnSCBHWdsZsdjM=
X-Google-Smtp-Source: 
 APXvYqzDFKZThjskqAs3IVGBylZXSZ9ckHXVtlUqfVC3VhDWkPwD7r1lG7AJG/F0Bv0zBn4saCHvhg==
X-Received: by 2002:a63:f501:: with SMTP id w1mr40166118pgh.307.1572991321911;
        Tue, 05 Nov 2019 14:02:01 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 x70sm25528448pfd.132.2019.11.05.14.02.00
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 05 Nov 2019 14:02:01 -0800 (PST)
Subject: [PATCH v13 0/6] mm / virtio: Provide support for unused page
 reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, mst@redhat.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net,
        vbabka@suse.cz
Cc: yang.zhang.wz@gmail.com, nitesh@redhat.com, konrad.wilk@oracle.com,
        david@redhat.com, pagupta@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, alexander.h.duyck@linux.intel.com,
        osalvador@suse.de
Date: Tue, 05 Nov 2019 14:02:00 -0800
Message-ID: <20191105215940.15144.65968.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting unused guest
pages to a hypervisor so that the memory associated with those pages can
be dropped and reused by other processes and/or guests on the host. Using
this it is possible to avoid unnecessary I/O to disk and greatly improve
performance in the case of memory overcommit on the host.

When enabled it will allocate a set of statistics to track the number of
reported pages. When the nr_free for a given free_area is greater than
this by the high water mark we will schedule a worker to begin allocating
the non-reported memory and to provide it to the reporting interface via a
scatterlist.

Currently this is only in use by virtio-balloon however there is the hope
that at some point in the future other hypervisors might be able to make
use of it. In the virtio-balloon/QEMU implementation the hypervisor is
currently using MADV_DONTNEED to indicate to the host kernel that the page
is currently unused. It will be faulted back into the guest the next time
the page is accessed.

To track if a page is reported or not the Uptodate flag was repurposed and
used as a Reported flag for Buddy pages. While we are processing the pages
in a given zone we have a set of pointers we track called
reported_boundary that is used to keep our processing time to a minimum.
Without these we would have to iterate through all of the reported pages
which would become a significant burden. I measured as much as a 20%
performance degradation without using the boundary pointers. In the event
of something like compaction needing to process the zone at the same time
it currently resorts to resetting the boundary if it is rearranging the
list. However in the future it could choose to delay processing the zone
if a flag is set indicating that a zone is being actively processed.

Below are the results from various benchmarks. I primarily focused on two
tests. The first is the will-it-scale/page_fault2 test, and the other is
a modified version of will-it-scale/page_fault1 that was enabled to use
THP. I did this as it allows for better visibility into different parts
of the memory subsystem. The guest is running with 32G for RAM on one
node of a E5-2630 v3.

Test                page_fault1 (THP)     page_fault2
Baseline         1  1209281.00  +/-0.47%   411314.00  +/-0.42%
                16  8804587.33  +/-1.80%  3419453.00  +/-1.80%

Patches applied  1  1209369.67  +/-0.06%   412187.00  +/-0.10%
                16  8812606.33  +/-0.06%  3435339.33  +/-1.82%

Patches enabled  1  1209104.67  +/-0.11%   413067.67  +/-0.43%
 MADV disabled  16  8835481.67  +/-0.29%  3463485.67  +/-0.50%

Patches enabled  1  1210367.67  +/-0.58%   416962.00  +/-0.14%
                16  8433236.00  +/-0.58%  3437897.67  +/-0.34%

The results above are for a baseline with a linux-next-20191031 kernel,
that kernel with this patch set applied but page reporting disabled in
virtio-balloon, patches applied but the madvise disabled by direct
assigning a device, and the patches applied and page reporting fully
enabled.  These results include the deviation seen between the average
value reported here versus the high and/or low value. I observed that
during the test the memory usage for the first three tests never dropped
whereas with the patches fully enabled the VM would drop to using only a
few GB of the host's memory when switching from memhog to page fault tests.

Most of the overhead seen with this patch set fully enabled is due to the
fact that accessing the reported pages will cause a page fault and the host
will have to zero the page before giving it back to the guest. The overall
guest size is kept fairly small to only a few GB while the test is running.
This overhead is much more visible when using THP than with standard 4K
pages. As such for the case where the host memory is not oversubscribed
this results in a performance regression, however if the host memory were
oversubscribed this patch set should result in a performance improvement
as swapping memory from the host can be avoided.

A brief history on the background of unused page reporting can be found at:
https://lore.kernel.org/lkml/29f43d5796feed0dec8e8bb98b187d9dac03b900.camel@linux.intel.com/

Changes from v11:
https://lore.kernel.org/lkml/20191001152441.27008.99285.stgit@localhost.localdomain/
Removed unnecessary whitespace change from patch 2
Minor tweak to get_unreported_page to avoid excess writes to boundary
Rewrote cover page to lay out additional performance info.

Changes from v12:
https://lore.kernel.org/lkml/20191022221223.17338.5860.stgit@localhost.localdomain/
Rebased on linux-next 20191031
Renamed page_is_reported to page_reported
Renamed add_page_to_reported_list to mark_page_reported
Dropped unused definition of add_page_to_reported_list for non-reporting case
Split free_area_reporting out from get_unreported_tail
Minor updates to cover page
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      mm: Add device side and notifier for unused page reporting
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   88 ++++++++-
 include/linux/mmzone.h              |   60 ++----
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |   31 +++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |   11 +
 mm/Makefile                         |    1 
 mm/compaction.c                     |    5 
 mm/memory_hotplug.c                 |    2 
 mm/page_alloc.c                     |  199 +++++++++++++++-----
 mm/page_reporting.c                 |  353 +++++++++++++++++++++++++++++++++++
 mm/page_reporting.h                 |  226 ++++++++++++++++++++++
 mm/shuffle.c                        |   12 +
 mm/shuffle.h                        |    6 +
 15 files changed, 905 insertions(+), 102 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
