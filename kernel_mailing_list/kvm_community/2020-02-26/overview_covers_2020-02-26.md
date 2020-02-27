

#### [PATCH V5 0/5] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Feb 26 06:04:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11405323
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 45D79138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 06:06:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 14BFF20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 06:06:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AfL3XMuC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726981AbgBZGGM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 01:06:12 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:28799 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726112AbgBZGGM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 26 Feb 2020 01:06:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582697170;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=enRjKsAhorQ7gtc4NEO5FtEZu0wodxPLamz1NrNNgF4=;
        b=AfL3XMuC37OJ85JUknAVZsLqaaOL70t03wBHdbE1vyRbknef22HFNIzs4g5bpsUOyJVpWV
        LSUeQDOoVJ9Cpvq0+aFju+LBjb5udOYgZ8GkCrz9R9CwpzrJg05ELBWwtULQttqDhhP242
        uh0iM5UuDLKZPGIFu8wGNgYXSNQdGNo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-429-aneCOgh5OHW2FiS47KIZvw-1; Wed, 26 Feb 2020 01:05:57 -0500
X-MC-Unique: aneCOgh5OHW2FiS47KIZvw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D61A5800D5E;
        Wed, 26 Feb 2020 06:05:53 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-217.pek2.redhat.com [10.72.13.217])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DC0D69297A;
        Wed, 26 Feb 2020 06:05:01 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jiri@mellanox.com,
        shahafs@mellanox.com, hanand@xilinx.com, mhabets@solarflare.com,
        gdawar@xilinx.com, saugatm@xilinx.com, vmireyno@marvell.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V5 0/5] vDPA support
Date: Wed, 26 Feb 2020 14:04:51 +0800
Message-Id: <20200226060456.27275-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

This is an update version of vDPA support in kernel.

vDPA device is a device that uses a datapath which complies with the
virtio specifications with vendor specific control path. vDPA devices
can be both physically located on the hardware or emulated by
software. vDPA hardware devices are usually implemented through PCIE
with the following types:

- PF (Physical Function) - A single Physical Function
- VF (Virtual Function) - Device that supports single root I/O
  virtualization (SR-IOV). Its Virtual Function (VF) represents a
  virtualized instance of the device that can be assigned to different
  partitions
- ADI (Assignable Device Interface) and its equivalents - With
  technologies such as Intel Scalable IOV, a virtual device (VDEV)
  composed by host OS utilizing one or more ADIs. Or its equivalent
  like SF (Sub function) from Mellanox.

From a driver's perspective, depends on how and where the DMA
translation is done, vDPA devices are split into two types:

- Platform specific DMA translation - From the driver's perspective,
  the device can be used on a platform where device access to data in
  memory is limited and/or translated. An example is a PCIE vDPA whose
  DMA request was tagged via a bus (e.g PCIE) specific way. DMA
  translation and protection are done at PCIE bus IOMMU level.
- Device specific DMA translation - The device implements DMA
  isolation and protection through its own logic. An example is a vDPA
  device which uses on-chip IOMMU.

To hide the differences and complexity of the above types for a vDPA
device/IOMMU options and in order to present a generic virtio device
to the upper layer, a device agnostic framework is required.

This series introduces a software vDPA bus which abstracts the
common attributes of vDPA device, vDPA bus driver and the
communication method, the bus operations (vdpa_config_ops) between the
vDPA device abstraction and the vDPA bus driver. This allows multiple
types of drivers to be used for vDPA device like the virtio_vdpa and
vhost_vdpa driver to operate on the bus and allow vDPA device could be
used by either kernel virtio driver or userspace vhost drivers as:

   virtio drivers  vhost drivers
          |             |
    [virtio bus]   [vhost uAPI]
          |             |
   virtio device   vhost device
   virtio_vdpa drv vhost_vdpa drv
             \       /
            [vDPA bus]
                 |
            vDPA device
            hardware drv
                 |
            [hardware bus]
                 |
            vDPA hardware

virtio_vdpa driver is a transport implementation for kernel virtio
drivers on top of vDPA bus operations. An alternative is to refactor
virtio bus which is sub-optimal since the bus and drivers are designed
to be use by kernel subsystem, a non-trivial major refactoring is
needed which may impact a brunches of drivers and devices
implementation inside the kernel. Using a new transport may grealy
simply both the design and changes.

vhost_vdpa driver is a new type of vhost device which allows userspace
vhost drivers to use vDPA devices via vhost uAPI (with minor
extension). This help to minimize the changes of existed vhost drivers
for using vDPA devices.

With the abstraction of vDPA bus and vDPA bus operations, the
difference and complexity of the under layer hardware is hidden from
upper layer. The vDPA bus drivers on top can use a unified
vdpa_config_ops to control different types of vDPA device.

This series contains the bus and virtio_vdpa implementation. We are
working on the vhost part and IFCVF (vDPA driver from Intel) which
will be posted in future few days.

Future work:

- direct doorbell mapping support
- direct interrupt support
- control virtqueue support
- dirty page tracking support
- management API (devlink)

Thanks

Changes from V4:

- use put_device() instead of kfree when fail to register virtio
  device (Jason)
- simplify the error handling when allocating vdpasim device (Jason)
- don't use device_for_each_child() during module exit (Jason)
- correct the error checking for vdpa_alloc_device() (Harpreet, Lingshan)

Changes from V3:

- various Kconfig fixes (Randy)

Changes from V2:

- release idr in the release function for put_device() unwind (Jason)
- don't panic when fail to register vdpa bus (Jason)
- use unsigned int instead of int for ida (Jason)
- fix the wrong commit log in virito_vdpa patches (Jason)
- make vdpa_sim depends on RUNTIME_TESTING_MENU (Michael)
- provide a bus release function for vDPA device (Jason)
- fix the wrong unwind when creating devices for vDPA simulator (Jason)
- move vDPA simulator to a dedicated directory (Lingshan)
- cancel the work before release vDPA simulator

Changes from V1:

- drop sysfs API, leave the management interface to future development
  (Michael)
- introduce incremental DMA ops (dma_map/dma_unmap) (Michael)
- introduce dma_device and use it instead of parent device for doing
  IOMMU or DMA from bus driver (Michael, Jason, Ling Shan, Tiwei)
- accept parent device and dma device when register vdpa device
- coding style and compile fixes (Randy)
- using vdpa_xxx instead of xxx_vdpa (Jason)
- ove vDPA accessors to header and make it static inline (Jason)
- split vdp_register_device() into two helpers vdpa_init_device() and
  vdpa_register_device() which allows intermediate step to be done (Jason)
- warn on invalidate queue state when fail to creating virtqueue (Jason)
- make to_virtio_vdpa_device() static (Jason)
- use kmalloc/kfree instead of devres for virtio vdpa device (Jason)
- avoid using cast in vdpa bus function (Jason)
- introduce module_vdpa_driver and fix module refcnt (Jason)
- fix returning freed address in vdapsim coherent DMA addr allocation (Dan)
- various other fixes and tweaks

V4: https://lkml.org/lkml/2020/2/20/59
V3: https://lkml.org/lkml/2020/2/19/1347
V2: https://lkml.org/lkml/2020/2/9/275
V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (5):
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

 MAINTAINERS                             |   2 +
 drivers/vhost/Kconfig                   |   6 +
 drivers/vhost/Kconfig.vringh            |   1 +
 drivers/vhost/Makefile                  |   2 +
 drivers/vhost/net.c                     |   2 +-
 drivers/vhost/vhost.c                   | 221 +++-----
 drivers/vhost/vhost.h                   |  36 +-
 drivers/vhost/vhost_iotlb.c             | 171 +++++++
 drivers/vhost/vringh.c                  | 421 +++++++++++++++-
 drivers/virtio/Kconfig                  |  15 +
 drivers/virtio/Makefile                 |   2 +
 drivers/virtio/vdpa/Kconfig             |  26 +
 drivers/virtio/vdpa/Makefile            |   3 +
 drivers/virtio/vdpa/vdpa.c              | 167 ++++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 645 ++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 396 +++++++++++++++
 include/linux/vdpa.h                    | 232 +++++++++
 include/linux/vhost_iotlb.h             |  45 ++
 include/linux/vringh.h                  |  36 ++
 20 files changed, 2227 insertions(+), 204 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 drivers/virtio/vdpa/Kconfig
 create mode 100644 drivers/virtio/vdpa/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa.c
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [kvm-unit-tests PATCH 0/7] Fixes for clang builds
##### From: morbo@google.com
From: Bill Wendling <morbo@google.com>

```c
From patchwork Wed Feb 26 07:44:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405441
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C7631395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 07:44:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C1E621D7E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 07:44:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="r1rbRrBo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727223AbgBZHou (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 02:44:50 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:34264 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726587AbgBZHou (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 02:44:50 -0500
Received: by mail-pj1-f73.google.com with SMTP id v8so3003392pju.1
        for <kvm@vger.kernel.org>; Tue, 25 Feb 2020 23:44:49 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Dvhrew6bJQSEcOdx0LzKYO1ItCUbvb7ulg82U8Cs/x4=;
        b=r1rbRrBoqOcHZEEks629lSsI0EwzmHU6fFI5X2n1T+ASmdVyGZAAioTDr6TYSItEmx
         zNIUkC3t18J8Cs7zAGnLlGGcLsJgsPdPZABWsNS96z0il8889+6clORwMhEhoZGsK2eE
         iL9Tv08RvRFmUfKLYSMykRjBsXEvFVUrWa0IcWwk+z0g4uhTQyLcCAe/7Z+Q0B2Ay+xZ
         xNxYqYMsakI/2SEX/dNepiMi2CZNsVt14BcGX2lsYO1NoMp4FXwhPeFRGD590PEPFDyM
         qDM02Ua/DRY6L+SAxIQBX+1re1J02sA5EjUsAGcQAikneReLiWj9f/s01JqpmCGu8CzN
         4hiQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Dvhrew6bJQSEcOdx0LzKYO1ItCUbvb7ulg82U8Cs/x4=;
        b=gYqKBT8fCX/xguZNrHZIKIqoAja0UdiF99a7xVl0rNg6hCgxCzwQ9mr5TR+VxbghQY
         +ZYiacLZq5T1zZ1i4DlqvZ2EDmMlDFB/AWjeM+GRt3BeJgOi2KFoLgfj1juW1yP84/7O
         PsPvR3cJFmk4ChOi1+UzC7jxs77AQw930HDRqn0XDAcCIJ8pR8UsUbj6CA23IWh4DKKz
         Ug6KqZ1vGoxnPEH/cCQTTgDeRMyDkbEeLlLoPg5E85Esw9PgmHy7Oj+j7Td3/mCxDwJq
         kaMwkOG+Jf9VvBYjeW1XrY1E16muaD9njzZ3kNWGbWug/edE9OO6vTXAzooFlPVNYdPR
         RukA==
X-Gm-Message-State: APjAAAXaW2/3jTmOWSsy0GD/MGEkwFs0xYAIEUztRNaISqTZ1H+IaXvI
        HjjgwGrSHrPeWZ8QJ234sQftldO3LzbsKVLUxEbofZh/EBdqNNgqtTfUv0zJMmEoP6ZVULEAqyp
        KbrkDFDTCN6xQVtt63e0JvGJRXFQ2brcL+O+nl3Ar2pUzKbGoBoid1A==
X-Google-Smtp-Source: 
 APXvYqyRwxXJMYEbSR91aXCwv5WqK+2o+xKZCoVWnh5Bm7FRiEEhQaoJDsdzgSeQhbyR4qS4Qd5PcbkoWw==
X-Received: by 2002:a63:e65:: with SMTP id 37mr2523168pgo.171.1582703089253;
 Tue, 25 Feb 2020 23:44:49 -0800 (PST)
Date: Tue, 25 Feb 2020 23:44:20 -0800
Message-Id: <20200226074427.169684-1-morbo@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH 0/7] Fixes for clang builds
From: morbo@google.com
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bill Wendling <morbo@google.com>

This is a series of patches which allow clang to build the
kvm-unit-tests.

Bill Wendling (7):
  x86: emulator: use "SSE2" for the target
  pci: use uint32_t for unsigned long values
  x86: realmode: syscall: add explicit size suffix to ambiguous
    instructions
  svm: change operand to output-only for matching constraint
  svm: convert neg shift to unsigned shift
  x86: VMX: use inline asm to get stack pointer
  x86: VMX: the "noclone" attribute is gcc-specific

 lib/linux/pci_regs.h |  4 ++--
 x86/emulator.c       |  2 +-
 x86/realmode.c       |  6 +++---
 x86/svm.c            |  6 +++---
 x86/syscall.c        |  2 +-
 x86/vmx_tests.c      | 11 ++++++++---
 6 files changed, 18 insertions(+), 13 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/7] Fixes for clang builds
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Wed Feb 26 09:44:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11405759
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A0BFA138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7DE5424673
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 09:44:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="bzZUNCNK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727359AbgBZJok (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 04:44:40 -0500
Received: from mail-pj1-f73.google.com ([209.85.216.73]:44250 "EHLO
        mail-pj1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726494AbgBZJoj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 04:44:39 -0500
Received: by mail-pj1-f73.google.com with SMTP id c31so1641103pje.9
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 01:44:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=qyh4wTyFO4XAmJigNXSlbgoQSA7Ex0nWckpueaZj5KI=;
        b=bzZUNCNKGH9NtjctDQoH0vyDnlb0zU8gAcHqE5bReEOPhZzubAYntLpgMu/TvSrWx8
         uFu5TEi3dQZ1o6uIkOQRL6KQRMAk1ny8WsL0t1Mp5r56pKFYoxfIPqUTdSpguiduSrN7
         XKhj3/F4t5Nxe1QfuUko0mRuQTDqdvIHcOC/nGCNEWkdOdc1aq0j8dmA9SDM+Wpw9kW4
         YWa/NqadFUGDsYLMSAiYUyfmSL9VSNxM4q1r5zRoB985bfoLAOxbMehLpoYa1EmNRJGR
         u1H71WZRhBUxq03UJ9M3ZDMhHsLKjx6EvXIEXu6qd4yo2ABxbbu7L71HkdX2rSh5EsO0
         a5iQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=qyh4wTyFO4XAmJigNXSlbgoQSA7Ex0nWckpueaZj5KI=;
        b=fbesTqzoP7LDOF17rK0GL3g+uuphKZOkBuosnVCFE30DwZyYQg9LY0H9p7sF4uz6pI
         BiAL/1hSA+aV4De7brPoeZ0MR89XKjs4+qVKY2gIogMOslPXCIzR3ZWyKp55cja5d2Uy
         erIjXloIEvAT1jKP1V83Ng7q6T9Po5I3frVwQRCaunL/RfK/aLQ7v2s/LMcWeAq2xJX2
         HGmcMorKC7qyyYiMoAKqSXly0k1Pw5o8U2krvvN2aeGHNYSBch5QPUUyVW65F0odA46e
         rVGUiY0k3nlZ8VpENwqKRxW/P0u1xevmyOq7QAQ5jBlkUNjzVbNtj2vHLjJj227bepjl
         /LWg==
X-Gm-Message-State: APjAAAW/E98yVDOgU1NB5rw5NQx70TafYb1Xsfalzqh/XRF/JFe5Z7iI
        Ce90dXcuPNtI4GrCKo9L5TzllCkM6saD6+g/es5736l84HD3vmoGgxBoRPwhMp+s81rH2K5G4cg
        3acORJ0yFX4phnl/14LenLbLEPxVxMObNHs+PD91saoinMmwTt/A8PA==
X-Google-Smtp-Source: 
 APXvYqzzPmf0vZiHJHpthgF0oVEk2ZScpl4RbdDd4FpukrtXpiYrs6V9YfMmJXC+VB23XIU6HgfaTil/Pg==
X-Received: by 2002:a63:4a47:: with SMTP id j7mr3063194pgl.196.1582710277242;
 Wed, 26 Feb 2020 01:44:37 -0800 (PST)
Date: Wed, 26 Feb 2020 01:44:19 -0800
In-Reply-To: <20200226074427.169684-1-morbo@google.com>
Message-Id: <20200226094433.210968-1-morbo@google.com>
Mime-Version: 1.0
References: <20200226074427.169684-1-morbo@google.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [kvm-unit-tests PATCH v2 0/7] Fixes for clang builds
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: oupton@google.com, pbonzini@redhat.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes to "pci: cast masks to uint32_t for unsigned long values" to
cast the masks instead of changing the values in the header.

Bill Wendling (2):
  x86: emulator: use "SSE2" for the target
  pci: cast masks to uint32_t for unsigned long values

Eric Hankland (2):
  x86: pmu: Test WRMSR on a running counter
  x86: pmu: Test perfctr overflow after WRMSR on a running counter

Oliver Upton (1):
  x86: VMX: Add tests for monitor trap flag

Paolo Bonzini (2):
  x86: provide enabled and disabled variation of the PCID test
  vmx: tweak XFAILS for #DB test
```
#### [kvm-unit-tests PATCH v3 0/7] Fixes for clang builds
##### From: Bill Wendling <morbo@google.com>

```c
From patchwork Wed Feb 26 20:12:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11407135
Return-Path: <SRS0=q2E5=4O=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4152714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 20:13:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 126EB24656
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 26 Feb 2020 20:13:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="TM42qedM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727305AbgBZUNE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 26 Feb 2020 15:13:04 -0500
Received: from mail-pl1-f201.google.com ([209.85.214.201]:33612 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727240AbgBZUNE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 26 Feb 2020 15:13:04 -0500
Received: by mail-pl1-f201.google.com with SMTP id bd7so357508plb.0
        for <kvm@vger.kernel.org>; Wed, 26 Feb 2020 12:13:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=eE7m91og2qy8dUqhBgCzX0N5xowRQsCQ0yF3s3lmQnM=;
        b=TM42qedM8DksnVEF0SiVXay32fTG103XsIThRVSSFezzKCW4SqZRIbLmpF38YQ2FQK
         ED0jqzm6gcFoJ8QYjOkmlw6dh2hwf3QbK8UM3++hYsBigXf8I0clqreV6yTl4TMz2idx
         NkDu5RM1qj01+zRUyd8UmKIum9VY+w0m5BImQxmEnS+VvQE7u+7f9yRd7MwF9XlpKSR2
         +7MLS3Iok08Ux1f2v4jEmSG1Vey5Tw6AB+isPo3KzPlO3G2NFJkFKr9U0R1AUgaU5X9p
         pXF2c+jR/HmhfahIicFZK/1k5jVcQ9Pvht0MxPFVfMg8Kom7ITzpvGgsZON/ijH4bhBJ
         QwCQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=eE7m91og2qy8dUqhBgCzX0N5xowRQsCQ0yF3s3lmQnM=;
        b=Ilxffo4LsBmuSW6/viyCfJWgvapdNAQtSKvjPR1bfobcKlBqLpJaxHvKRoFQfflpz2
         WWkM0wECGCy4DjWYAurRTBdPZRc90PvOXa/WQQP5yAvUzJBnm+obnF+yMFo9fMiAvRuN
         VKlg4PF+QXf7VlNgWzpY8O8jaukDMYvQ3LmOhBljAEjvImqHCp0BeryLVWqmm7amrSKB
         btJiRQxHduyM+X2N4wpuXfC3mrf7BthoOz5hMls//8p+ZIOSQme50ujwCjFuKXqUwESp
         6g33BtwMDjlqU0HoMY5fP/I6wvfhpIVMDsm7x2zeC6FTqu5a++QKRwqkEn9scD6P2gEe
         rZdw==
X-Gm-Message-State: APjAAAW9vQZf0EoJELmYrXopT3BPm3FJRTO7DTxpLaxGW3J2MNSVK1+T
        sn8CJ6xx1D3gknsafBPtOwZivWg9uled5pDYvMUk4wGc7ZOZO2tu9sVPnCdQADnT1MMJUEuXjAw
        0SW2swgJjbnns7tLnDEVM4fhCFsBGsl/9rUCcl+ZrtiLZpVwIWxtvrw==
X-Google-Smtp-Source: 
 APXvYqxfqT4rvxxcBLpgjXUmxhik05IecVBB4jbhiYl13UObopY2h4rIxVfYzU+bWy8WRwX/w3VvXKLt7g==
X-Received: by 2002:a63:1051:: with SMTP id 17mr482885pgq.291.1582747982494;
 Wed, 26 Feb 2020 12:13:02 -0800 (PST)
Date: Wed, 26 Feb 2020 12:12:36 -0800
In-Reply-To: <20200226094433.210968-1-morbo@google.com>
Message-Id: <20200226201243.86988-1-morbo@google.com>
Mime-Version: 1.0
References: <20200226094433.210968-1-morbo@google.com>
X-Mailer: git-send-email 2.25.1.481.gfbce0eb801-goog
Subject: [kvm-unit-tests PATCH v3 0/7] Fixes for clang builds
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, oupton@google.com, drjones@redhat.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes to "pci: cast masks to uint32_t for unsigned long values" to
cast the masks instead of changing the values in the header.

This is a re-send of the v2 patches, which included patches that
shouldn't have been included.

Bill Wendling (7):
  x86: emulator: use "SSE2" for the target
  pci: cast masks to uint32_t for unsigned long values
  x86: realmode: syscall: add explicit size suffix to ambiguous
    instructions
  svm: change operand to output-only for matching constraint
  svm: convert neg shift to unsigned shift
  x86: VMX: use inline asm to get stack pointer
  x86: VMX: the "noclone" attribute is gcc-specific

 lib/pci.c       |  3 ++-
 x86/emulator.c  |  2 +-
 x86/realmode.c  |  6 +++---
 x86/svm.c       |  6 +++---
 x86/syscall.c   |  2 +-
 x86/vmx_tests.c | 11 ++++++++---
 6 files changed, 18 insertions(+), 12 deletions(-)
```
