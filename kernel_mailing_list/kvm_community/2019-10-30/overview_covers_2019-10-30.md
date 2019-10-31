

#### [PATCH V6 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Oct 30 06:44:38 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11219029
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DBB49139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 06:45:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B0172208E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 06:45:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PLYAecqF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727416AbfJ3Gpa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 02:45:30 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:54236 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726187AbfJ3Gp3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 02:45:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1572417927;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=uffcSHdSJpmKK0bwfcL/G8ryMleDgj8IBQmRejUs9zw=;
        b=PLYAecqFMUFR1EEuKcMi4Yfxdemj+MQIZPlxRBFwJ++H3x1JNPGtrtCdABV9gpOOUhNHIV
        jqh+bvDyOVqPU6J5xSmmquthaoz32uGZM0l6STVAsVVKgqMr8ZbpL5Y3IrYAf5npWI+3yF
        MdTwslxmAiyUB703ibcLlI9RzgTw8tU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-361-bFM7k-DhNQOyvHmnP84ppw-1; Wed, 30 Oct 2019 02:45:24 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5D4A885B6EF;
        Wed, 30 Oct 2019 06:45:20 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-223.pek2.redhat.com [10.72.12.223])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2EB855D9C3;
        Wed, 30 Oct 2019 06:44:46 +0000 (UTC)
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
Subject: [PATCH V6 0/6] mdev based hardware virtio offloading support
Date: Wed, 30 Oct 2019 14:44:38 +0800
Message-Id: <20191030064444.21166-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-MC-Unique: bFM7k-DhNQOyvHmnP84ppw-1
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

[1] https://lkml.org/lkml/2019/10/29/335
[2] https://lkml.org/lkml/2019/10/15/1226

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
 drivers/vfio/mdev/mdev_core.c                 |  57 ++
 drivers/vfio/mdev/mdev_driver.c               |  25 +
 drivers/vfio/mdev/mdev_private.h              |   8 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 413 +++++++++++
 include/linux/mdev.h                          |  57 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev_ops.h                 |  52 ++
 include/linux/virtio_mdev_ops.h               | 161 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 691 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  11 +
 24 files changed, 1598 insertions(+), 91 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev_ops.h
 create mode 100644 include/linux/virtio_mdev_ops.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [kvm-unit-tests PATCH v3 0/6] Patches for clang compilation
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Wed Oct 30 21:04:13 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11220057
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 84C2E13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 21:04:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4F6DC20873
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 21:04:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MQlOk3Sp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726969AbfJ3VE1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 17:04:27 -0400
Received: from mail-ua1-f74.google.com ([209.85.222.74]:55185 "EHLO
        mail-ua1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726749AbfJ3VE1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 17:04:27 -0400
Received: by mail-ua1-f74.google.com with SMTP id r13so553859uam.21
        for <kvm@vger.kernel.org>; Wed, 30 Oct 2019 14:04:26 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=aiFlHLaj6X/N2ZURrJjEU4vYX3C5zBsE6x3F5CGlqEU=;
        b=MQlOk3SpDeMdM4ReP5nagv2SpEpRil0SLDyMLjMdVSvqiqSWuvOhMBXhj3mdJMROZ1
         VN88xMYE3Pvopi3XWY++qUtwz+jpdDmu5AYPGWb2zDHQRIZonAsSf1eS7adHlUNxvUqM
         RZETOg9V6JVIA76TaM5V7qmDrVryU9EXRurqzB1+1uXUBaSmLPTAD9BR9QgH/mcy0DDQ
         mNARyUNueyuuK7/WcOxoRZM7BeP8dKB75ELp8z+TZWtj7+y9RbXgDlj8P35hntJT0/lf
         hKDta/aqib+GJkLmH78PEIAwzNa+Dp3c6ptFZvTpsuz/NEGSENVHdLP/yzne51qyTE4G
         Zkuw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=aiFlHLaj6X/N2ZURrJjEU4vYX3C5zBsE6x3F5CGlqEU=;
        b=ek0y4g038jznyYDVIEgdMuXaR4ptGDYgY/jwpSuUzi5MMzSA38YFeMmHEaTv+gES3k
         LEDES8d8DiW5IzeFJXq3iPixIWGyYjPFB6UVlyEIuGogIshT1mO0BgjlSG1lrfPFN6Cr
         plqtDjrCVULA/8H9nUPEfiSdstNolONqokMDgVZwBTySz7z1wxIrqqE15ITLwpq6Sbat
         FZKB6ipZv01hx2Tq68OSp8Ob7O0CFZW0O/2J3pT+MIRSWBBHdK5TfNKGSTJxXN2Hz5j/
         elHz1liTZj/lhhBAe+zTV5ryLNRCbZ+LucxIhDDF08XfQY3sm+2q3YwkQS429kg88Vyp
         KQsw==
X-Gm-Message-State: APjAAAVtAxdGemy1oLfOXrYVb7kAuywpbPhmXQtdSrMCwFWOrrbF9ICu
        5B/Z828Vsnh0JIHzT8TgBUelXps+KIsTQybnEocTR7H8eoCTMBWbSoNhFXLI4RipYlx0qrkk70a
        nSy/ju99EZAJYJs759d+0uwSTp9UsqwBq/SvDZz70lUwSI0MwRasaLg==
X-Google-Smtp-Source: 
 APXvYqzOK5eWNslxZeCF5LENpEN/eRV7Hbm2Z9PdmCAbnjjpnQTeQRu9Kq5Y5U5lfdijW1FHsqu51G0iag==
X-Received: by 2002:a1f:6a02:: with SMTP id f2mr265410vkc.40.1572469465876;
 Wed, 30 Oct 2019 14:04:25 -0700 (PDT)
Date: Wed, 30 Oct 2019 14:04:13 -0700
In-Reply-To: <20191015000411.59740-1-morbo@google.com>
Message-Id: <20191030210419.213407-1-morbo@google.com>
Mime-Version: 1.0
References: <20191015000411.59740-1-morbo@google.com>
X-Mailer: git-send-email 2.24.0.rc1.363.gb1bccd3e3d-goog
Subject: [kvm-unit-tests PATCH v3 0/6] Patches for clang compilation
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, thuth@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series of patches includes extra from the original patch set:

- Changes to the "use -Werror in cc-option" patch to address Thomas
  Huth's comments.
- Two fixes for code clang warned about: shifting negative numbers, and
  misuse of the "registers for local variables" feature.

Bill Wendling (6):
  x86: emulator: use "SSE2" for the target
  pci: cast the masks to the appropriate size
  Makefile: use "-Werror" in cc-option
  Makefile: add "cxx-option" for C++ builds
  x86: use a non-negative number in shift
  x86: use inline asm to retrieve stack pointer

 Makefile        | 30 +++++++++++++++++++++++-------
 lib/pci.c       |  3 ++-
 x86/emulator.c  |  2 +-
 x86/svm.c       |  2 +-
 x86/vmx_tests.c |  8 ++++++--
 5 files changed, 33 insertions(+), 12 deletions(-)
```
#### [PATCH 00/19] mm/gup: track dma-pinned pages: FOLL_PIN, FOLL_LONGTERM
##### From: John Hubbard <jhubbard@nvidia.com>

```c
From patchwork Wed Oct 30 22:49:11 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11220441
Return-Path: <SRS0=Bujf=YX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E52261599
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 22:53:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ACD2F218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 30 Oct 2019 22:53:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="oSHxJf1E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727561AbfJ3Wtn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 30 Oct 2019 18:49:43 -0400
Received: from hqemgate15.nvidia.com ([216.228.121.64]:5214 "EHLO
        hqemgate15.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727064AbfJ3Wtn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 30 Oct 2019 18:49:43 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate15.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dba13850001>; Wed, 30 Oct 2019 15:49:41 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Wed, 30 Oct 2019 15:49:34 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Wed, 30 Oct 2019 15:49:34 -0700
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 30 Oct
 2019 22:49:34 +0000
Received: from rnnvemgw01.nvidia.com (10.128.109.123) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 30 Oct 2019 22:49:33 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 rnnvemgw01.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dba137b0002>; Wed, 30 Oct 2019 15:49:32 -0700
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
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>
Subject: [PATCH 00/19] mm/gup: track dma-pinned pages: FOLL_PIN, FOLL_LONGTERM
Date: Wed, 30 Oct 2019 15:49:11 -0700
Message-ID: <20191030224930.3990755-1-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.23.0
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1572475781; bh=hGPWt3QMTkMrTVgcNxptwRVsRQFog4chezBSn5RrX48=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         MIME-Version:X-NVConfidentiality:Content-Type:
         Content-Transfer-Encoding;
        b=oSHxJf1EatQQbMkaqcITETA6JEtlVNEdgum3xhm5ffOxR+XNpeSZn2n8WTQHBmpXQ
         XlkO24RsW/LfP+8EN9BTaQwIJCQeS6tAdSrqh0UNPmHthTKHhTKpacZ0s3MALr4vP4
         itdh7PP+CYbjuibtGti4rkBun1FGTraZnTUXeqaBCjMHeV5JXay6xNR7ZezCZ5Svft
         FFN/X5vLeUp/Ci4mFUSlT4/inZ55UOWuZDRaqx1HBrshBWu8j4oFc9DE2XSBK2JNQX
         6Jh4/4uKc510NHecCig4JLuKjY+bJQdP2CLVRpOkMVKoGbX2eD/Zh91jJYPyPfFHGf
         vWCpcQszWYTnQ==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This applies cleanly to linux-next and mmotm, and also to linux.git if
linux-next's commit 20cac10710c9 ("mm/gup_benchmark: fix MAP_HUGETLB
case") is first applied there.

This provides tracking of dma-pinned pages. This is a prerequisite to
solving the larger problem of proper interactions between file-backed
pages, and [R]DMA activities, as discussed in [1], [2], [3], and in
a remarkable number of email threads since about 2017. :)

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
    put_user_page()

Because there are interdependencies with FOLL_LONGTERM, a similar
conversion as for FOLL_PIN, was applied. The change was from this:

    get_user_pages(FOLL_LONGTERM) (also sets FOLL_GET)
    put_page()

to this:
    pin_longterm_pages() (sets FOLL_PIN | FOLL_LONGTERM)
    put_user_page()

============================================================
Patch summary:

* Patches 1-4: refactoring and preparatory cleanup, independent fixes
    (Patch 4: V4L2-core bug fix (can be separately applied))

* Patch 5: introduce pin_user_pages(), FOLL_PIN, but no functional
           changes yet
* Patches 6-11: Convert existing put_user_page() callers, to use the
                new pin*()
* Patch 12: Activate tracking of FOLL_PIN pages.
* Patches 13-15: convert FOLL_LONGTERM callers
* Patches: 16-17: gup_benchmark and run_vmtests support
* Patch 18: enforce FOLL_LONGTERM as a gup-internal (only) flag
* Patch 19: Documentation/vm/pin_user_pages.rst

============================================================
Testing:

* I've done some overall kernel testing (LTP, and a few other goodies),
  and some directed testing to exercise some of the changes. And as you
  can see, gup_benchmark is enhanced to exercise this. Basically, I've been
  able to runtime test the core get_user_pages() and pin_user_pages() and
  related routines, but not so much on several of the call sites--but those
  are generally just a couple of lines changed, each.

  Not much of the kernel is actually using this, which on one hand
  reduces risk quite a lot. But on the other hand, testing coverage
  is low. So I'd love it if, in particular, the Infiniband and PowerPC
  folks could do a smoke test of this series for me.

  Also, my runtime testing for the call sites so far is very weak:

    * io_uring: Some directed tests from liburing exercise this, and they pass.
    * process_vm_access.c: A small directed test passes.
    * gup_benchmark: the enhanced version hits the new gup.c code, and passes.
    * infiniband (still only have crude "IB pingpong" working, on a
                  good day: it's not exercising my conversions at runtime...)
    * VFIO: compiles (I'm vowing to set up a run time test soon, but it's
                      not ready just yet)
    * powerpc: it compiles...
    * drm/via: compiles...
    * goldfish: compiles...
    * net/xdp: compiles...
    * media/v4l2: compiles...

============================================================
Next:

* Get the block/bio_vec sites converted to use pin_user_pages().

* Work with Ira and Dave Chinner to weave this together with the
  layout lease stuff.

============================================================

[1] Some slow progress on get_user_pages() (Apr 2, 2019): https://lwn.net/Articles/784574/
[2] DMA and get_user_pages() (LPC: Dec 12, 2018): https://lwn.net/Articles/774411/
[3] The trouble with get_user_pages() (Apr 30, 2018): https://lwn.net/Articles/753027/

John Hubbard (19):
  mm/gup: pass flags arg to __gup_device_* functions
  mm/gup: factor out duplicate code from four routines
  goldish_pipe: rename local pin_user_pages() routine
  media/v4l2-core: set pages dirty upon releasing DMA buffers
  mm/gup: introduce pin_user_pages*() and FOLL_PIN
  goldish_pipe: convert to pin_user_pages() and put_user_page()
  infiniband: set FOLL_PIN, FOLL_LONGTERM via pin_longterm_pages*()
  mm/process_vm_access: set FOLL_PIN via pin_user_pages_remote()
  drm/via: set FOLL_PIN via pin_user_pages_fast()
  fs/io_uring: set FOLL_PIN via pin_user_pages()
  net/xdp: set FOLL_PIN via pin_user_pages()
  mm/gup: track FOLL_PIN pages
  media/v4l2-core: pin_longterm_pages (FOLL_PIN) and put_user_page()
    conversion
  vfio, mm: pin_longterm_pages (FOLL_PIN) and put_user_page() conversion
  powerpc: book3s64: convert to pin_longterm_pages() and put_user_page()
  mm/gup_benchmark: support pin_user_pages() and related calls
  selftests/vm: run_vmtests: invoke gup_benchmark with basic FOLL_PIN
    coverage
  mm/gup: remove support for gup(FOLL_LONGTERM)
  Documentation/vm: add pin_user_pages.rst

 Documentation/vm/index.rst                  |   1 +
 Documentation/vm/pin_user_pages.rst         | 213 +++++++
 arch/powerpc/mm/book3s64/iommu_api.c        |  15 +-
 drivers/gpu/drm/via/via_dmablit.c           |   2 +-
 drivers/infiniband/core/umem.c              |   5 +-
 drivers/infiniband/core/umem_odp.c          |  10 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   4 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   3 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   8 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   2 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   9 +-
 drivers/infiniband/sw/siw/siw_mem.c         |   5 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |  10 +-
 drivers/platform/goldfish/goldfish_pipe.c   |  35 +-
 drivers/vfio/vfio_iommu_type1.c             |  15 +-
 fs/io_uring.c                               |   5 +-
 include/linux/mm.h                          | 133 ++++-
 include/linux/mmzone.h                      |   2 +
 include/linux/page_ref.h                    |  10 +
 mm/gup.c                                    | 622 ++++++++++++++++----
 mm/gup_benchmark.c                          |  81 ++-
 mm/huge_memory.c                            |  32 +-
 mm/hugetlb.c                                |  28 +-
 mm/memremap.c                               |   4 +-
 mm/process_vm_access.c                      |  28 +-
 mm/vmstat.c                                 |   2 +
 net/xdp/xdp_umem.c                          |   4 +-
 tools/testing/selftests/vm/gup_benchmark.c  |  28 +-
 tools/testing/selftests/vm/run_vmtests      |  22 +
 29 files changed, 1066 insertions(+), 272 deletions(-)
 create mode 100644 Documentation/vm/pin_user_pages.rst
```
