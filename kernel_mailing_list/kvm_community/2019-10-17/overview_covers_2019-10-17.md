

#### [kvm-unit-tests v2 PATCH 0/2] realmode test fixes for clang
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Thu Oct 17 01:25:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11194617
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 112021668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 01:25:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E415C21E6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 01:25:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="tlwpsPsS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405704AbfJQBZQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 16 Oct 2019 21:25:16 -0400
Received: from mail-pf1-f201.google.com ([209.85.210.201]:40058 "EHLO
        mail-pf1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404111AbfJQBZP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 16 Oct 2019 21:25:15 -0400
Received: by mail-pf1-f201.google.com with SMTP id r19so420216pfh.7
        for <kvm@vger.kernel.org>; Wed, 16 Oct 2019 18:25:13 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=3zpaEGQT5nYlTpl6wba1fWX+9IJx5cUE67PkWsveMnI=;
        b=tlwpsPsSbFozrX6imGKPOZei0qoOozI4YHoP2/BcTIRg9f8u2raMCr7Jpm4wRpZnMV
         a7SR/RzykG/CHpJORSkjeB4SODCcT5v/e8oSuVJhXMYHp+3KxNVoxystw2K6JcoXXUtv
         Wfdwvvq6Dn2VvMhAjhpJZ649kOq2Q0IY7iabh2KcVGnGDVRmAAnrLRm93emzAmQUNDSE
         MSvxzpagpgGfEnQbhtmh06oZmBL08qdMxM0xElS/F6c7oy+l1OuNVjaBtaagDceB7Efw
         SS9LUECkuJo1OLZNwIkEot+qGf4QaSgHiXxaUsb76sJItt4zA81a646Fgv9dDCDCGv97
         Q8jA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=3zpaEGQT5nYlTpl6wba1fWX+9IJx5cUE67PkWsveMnI=;
        b=n59PhNhv4f0EOzyyZEjciY4hceRseDIXlNC8BoV3VlWA0sM6gMH48/PeRR7yuX9Vh4
         020KqwbxQZUYPA9k757q972ePV7+em8nDZnMi2OwHsEE+8xxlD86pu2dJIuZff5XHxN1
         rLNl0YtvB3rUW58PJCMHugkUecV/PXQmvqcq+elr+iblC26pv6yRdohPoiKQ7PQHIntv
         Np7bWjBkPLVXMgULVqc4Vljjap25bFMsvrql39n9Rw5I3S8Yqy8WcstRUrAgNjKtgTVW
         JZAwOj2DairqGdP/j3w/2iq1UEM3txOEVnXouKk4uNNclEmpKnyeHfRYVz57RqfNrx3j
         Rptg==
X-Gm-Message-State: APjAAAVvo2X5CQduxnXB3PdJ9lI73t29fx8H6O3tYNBev175gsOl6EcW
        +1VhT+jsyBkZT0z1+jq4Fx/4GsxLJcj+f3jMAbGQDkqCgLMJrkA2gYrcMKG1/VqUvGVr3vBFKYG
        4bAKe77060lk4nJQNSo7qO8rU3t0Z+FlYFUf3oFEtW5nAKVfYBpj/gA==
X-Google-Smtp-Source: 
 APXvYqzILPgJ5Gcjgfn7BxmNZpZCDZuVuv9e1oXGwlh4+vLvHNmmNLN+k7sbjw+7CHXU2JmsJBg3Qcrl+Q==
X-Received: by 2002:a63:5d06:: with SMTP id r6mr1222089pgb.216.1571275513053;
 Wed, 16 Oct 2019 18:25:13 -0700 (PDT)
Date: Wed, 16 Oct 2019 18:25:00 -0700
In-Reply-To: <20191012235859.238387-1-morbo@google.com>
Message-Id: <20191017012502.186146-1-morbo@google.com>
Mime-Version: 1.0
References: <20191012235859.238387-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests v2 PATCH 0/2] realmode test fixes for clang
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com, alexandru.elisei@arm.com,
        thuth@redhat.com
Cc: jmattson@google.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following patches fix some realmode test compatibility issues
between gcc and clang.

This update should address the comments by Jim Mattson.

Re explicitly copying the regs structure, I tried to use the inline asm
code you suggested, but wasn't able to get it to work for me. It never
seemed to copy the structure correctly. Doing the loop explicitly solved
the issue.

Bill Wendling (2):
  x86: realmode: explicitly copy regs structure
  x86: realmode: fix esp in call test

 x86/realmode.c | 19 +++++++++++++++----
 1 file changed, 15 insertions(+), 4 deletions(-)
```
#### [PATCH V4 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Oct 17 10:48:30 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11195405
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0294714E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 10:49:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D5B0721835
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 10:49:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408998AbfJQKtG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 06:49:06 -0400
Received: from mx1.redhat.com ([209.132.183.28]:6584 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404935AbfJQKtF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 06:49:05 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 625A62E97D5;
        Thu, 17 Oct 2019 10:49:04 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-185.pek2.redhat.com [10.72.12.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5A5E55D721;
        Thu, 17 Oct 2019 10:48:39 +0000 (UTC)
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
Subject: [PATCH V4 0/6] mdev based hardware virtio offloading support
Date: Thu, 17 Oct 2019 18:48:30 +0800
Message-Id: <20191017104836.32464-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.29]);
 Thu, 17 Oct 2019 10:49:04 +0000 (UTC)
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

[1] https://lkml.org/lkml/2019/9/26/15
[2] https://lkml.org/lkml/2019/10/15/1226

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

 .../driver-api/vfio-mediated-device.rst       |  22 +-
 MAINTAINERS                                   |   2 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  13 +-
 drivers/vfio/mdev/mdev_core.c                 |  38 +
 drivers/vfio/mdev/mdev_driver.c               |  22 +
 drivers/vfio/mdev/mdev_private.h              |   2 +
 drivers/vfio/mdev/vfio_mdev.c                 |  45 +-
 drivers/virtio/Kconfig                        |   7 +
 drivers/virtio/Makefile                       |   1 +
 drivers/virtio/virtio_mdev.c                  | 409 +++++++++++
 include/linux/mdev.h                          |  55 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev.h                     |  52 ++
 include/linux/virtio_mdev.h                   | 151 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 691 ++++++++++++++++++
 scripts/mod/devicetable-offsets.c             |   3 +
 scripts/mod/file2alias.c                      |  10 +
 24 files changed, 1541 insertions(+), 87 deletions(-)
 create mode 100644 drivers/virtio/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev.h
 create mode 100644 include/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
```
#### [PATCH net 0/2] vsock/virtio: make the credit mechanism more robust
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Oct 17 12:44:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 11195643
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA7011668
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 12:44:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C2C7121848
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 12:44:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502449AbfJQMoJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 08:44:09 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55216 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388531AbfJQMoJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 08:44:09 -0400
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 5127B30650DA;
        Thu, 17 Oct 2019 12:44:09 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-117-195.ams2.redhat.com
 [10.36.117.195])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E17AC5D9CA;
        Thu, 17 Oct 2019 12:44:03 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: netdev@vger.kernel.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "David S. Miller" <davem@davemloft.net>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        virtualization@lists.linux-foundation.org
Subject: [PATCH net 0/2] vsock/virtio: make the credit mechanism more robust
Date: Thu, 17 Oct 2019 14:44:01 +0200
Message-Id: <20191017124403.266242-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.45]);
 Thu, 17 Oct 2019 12:44:09 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series makes the credit mechanism implemented in the
virtio-vsock devices more robust.
Patch 1 sends an update to the remote peer when the buf_alloc
change.
Patch 2 prevents a malicious peer (especially the guest) can
consume all the memory of the other peer, discarding packets
when the credit available is not respected.

Stefano Garzarella (2):
  vsock/virtio: send a credit update when buffer size is changed
  vsock/virtio: discard packets if credit is not respected

 net/vmw_vsock/virtio_transport_common.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)
```
#### [PATCH RFC 0/3] kcov: collect coverage from usb and vhost
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
From patchwork Thu Oct 17 17:44:12 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrey Konovalov <andreyknvl@google.com>
X-Patchwork-Id: 11196497
Return-Path: <SRS0=YJ/O=YK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 588B113BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 17:44:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 359BE20820
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 17 Oct 2019 17:44:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="txWXUG/b"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2394466AbfJQRoV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 17 Oct 2019 13:44:21 -0400
Received: from mail-vk1-f201.google.com ([209.85.221.201]:54303 "EHLO
        mail-vk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727298AbfJQRoU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 17 Oct 2019 13:44:20 -0400
Received: by mail-vk1-f201.google.com with SMTP id i20so1224492vkk.21
        for <kvm@vger.kernel.org>; Thu, 17 Oct 2019 10:44:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=AepTsz+A74jxm03gyi80tnEG5pdCAiVEmB2VKmmYbAA=;
        b=txWXUG/bKJH+xYvRuY3lNWGbs0Fu/K7TeNieEqEzkwCbQ951DttsTLGCzkXdVPy3KY
         Km2w/kOt807GP8B2mwZNT/1sE4XCnhEOgDKdD2r4LCXjfxdltkSQyRv4CGCTq1VoGRr2
         91CJUZ7DeaO+yiJF+glAdddLlpQJvF72+eqedoBsFNo0bVaZHL++3E9pDK/04d2YWGe+
         np7G/lXqW7cVF7AenbULxn1+Hg8fqiLGg2q6O/L99nPop1TMN0R0LzXBRRMq6hiBGMPQ
         t+QwWnw5oWFay2e0WWPMTYmTGfrtu7hXElVim/VjermRHIFXL96frNDlAwKVbaRGZzxv
         pUGQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=AepTsz+A74jxm03gyi80tnEG5pdCAiVEmB2VKmmYbAA=;
        b=T6YflbqBIP6oAyRa0L5p43whmrnt7jKH5dEY1ZbDd6evx98hNGnLmHgTbOdRLeZdg7
         fGZehinyHNjZdaxQytY7Y5W3AXAa5AMuGjrbaaDLcIkcY4GAJKDkal4HCGd6m8MJ3ggB
         EaW5MCresBiflP6m8Ol/PnoCkSerlbldBu8C11Za5UCoUGD+pBAUbeLYKxWU702Pa3Qf
         0IfIklcPJiS3hiYMIDJvZ5+Vw7Beoy/J5exRVWuv9epNtwxErc0l/zS+Zrqe42fZ8RxQ
         0KcSpIoKXsMhQr8kSNICQDiHHxR9wuX9i7oGU0y8b3cN+VBGKyiVf+/UQ7KEBClyC+vO
         4xrA==
X-Gm-Message-State: APjAAAUy29lCQHhh0ex0/2ebBVktMMRC7BHbgoYbhHMhBEScxEt0Kxay
        f8wXlRYsAJIjNMVrXwUDgWrXeJJWHJjnHuq3
X-Google-Smtp-Source: 
 APXvYqw6C55wAy116NWvppt7eDZT+fCR1ORnXW7Efx/dADnmZz5XHGPkhTIDMeFVShexmVeAGLoCcWUsVfibJxkz
X-Received: by 2002:a9f:200a:: with SMTP id 10mr2884411uam.42.1571334259331;
 Thu, 17 Oct 2019 10:44:19 -0700 (PDT)
Date: Thu, 17 Oct 2019 19:44:12 +0200
Message-Id: <cover.1571333592.git.andreyknvl@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.866.gb869b98d4c-goog
Subject: [PATCH RFC 0/3] kcov: collect coverage from usb and vhost
From: Andrey Konovalov <andreyknvl@google.com>
To: linux-usb@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, Dmitry Vyukov <dvyukov@google.com>,
        Greg Kroah-Hartman <gregkh@linuxfoundation.org>,
        Alan Stern <stern@rowland.harvard.edu>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>,
        Arnd Bergmann <arnd@arndb.de>,
        Steven Rostedt <rostedt@goodmis.org>,
        David Windsor <dwindsor@gmail.com>,
        Elena Reshetova <elena.reshetova@intel.com>,
        Anders Roxell <anders.roxell@linaro.org>,
        Andrey Konovalov <andreyknvl@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset extends kcov to allow collecting coverage from the USB
subsystem and vhost workers. See the first patch description for details
about the kcov extension. The other two patches apply this kcov extension
to USB and vhost.

These patches have been used to enable coverage-guided USB fuzzing with
syzkaller for the last few years, see the details here:

https://github.com/google/syzkaller/blob/master/docs/linux/external_fuzzing_usb.md

Andrey Konovalov (3):
  kcov: remote coverage support
  usb, kcov: collect coverage from hub_event
  vhost, kcov: collect coverage from vhost_worker

 Documentation/dev-tools/kcov.rst |  99 +++++++
 drivers/usb/core/hub.c           |   4 +
 drivers/vhost/vhost.c            |  15 ++
 drivers/vhost/vhost.h            |   3 +
 include/linux/kcov.h             |  10 +
 include/linux/sched.h            |   6 +
 include/uapi/linux/kcov.h        |  18 ++
 kernel/kcov.c                    | 434 ++++++++++++++++++++++++++++---
 8 files changed, 554 insertions(+), 35 deletions(-)
```
