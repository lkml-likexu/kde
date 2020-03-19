

#### [PATCH V6 0/8] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Mar 18 08:03:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11444679
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB4EC6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 08:04:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7753A2076E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 08:04:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="LYmvWYRl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727403AbgCRIED (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 04:04:03 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:33973 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727366AbgCRIED (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 04:04:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584518642;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=4Z+ky7ETeqltxx9IpjFVXU7xdjMTDYeoqNp1UDy2AfU=;
        b=LYmvWYRl3eD8PvHs40hBoaEyGs5Pk/cBweoLGpjbKrP+mquvOYxKtUQgZBa4cD0n9TATGO
        wzYXKtkVP/IwZYvp82ZdD86hUvChsn053MPSSmA2cgLGO/CXfBrFsCSwQjwqRT2s/mT6tb
        XgRrxlxViX+9EbJRpXxqUnD4IDmk3eY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-42-0UPhf8aKOG-38BxPxpMIqQ-1; Wed, 18 Mar 2020 04:03:50 -0400
X-MC-Unique: 0UPhf8aKOG-38BxPxpMIqQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 86E261005512;
        Wed, 18 Mar 2020 08:03:47 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-166.pek2.redhat.com [10.72.13.166])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 557EE19C58;
        Wed, 18 Mar 2020 08:03:30 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, lulu@redhat.com,
        parav@mellanox.com, kevin.tian@intel.com, stefanha@redhat.com,
        rdunlap@infradead.org, hch@infradead.org, aadam@redhat.com,
        jiri@mellanox.com, shahafs@mellanox.com, hanand@xilinx.com,
        mhabets@solarflare.com, gdawar@xilinx.com, saugatm@xilinx.com,
        vmireyno@marvell.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V6 0/8] vDPA support
Date: Wed, 18 Mar 2020 16:03:19 +0800
Message-Id: <20200318080327.21958-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
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

Two drivers were implemented with the framework introduced in this
series:

- Intel IFC VF driver which depends on the platform IOMMU for DMA
  translation
- VDPA simulator which is a software test device with an emulated
  onchip IOMMU

Future work:

- direct doorbell mapping support
- control virtqueue support
- dirty page tracking support
- direct interrupt support
- management API (devlink)

Please review.

Thanks

Changes from V5:

- include Intel IFCVF driver and vhost-vdpa drivers
- add the platform IOMMU support for vhost-vdpa
- check the return value of dev_set_name() (Jason)
- various tweaks and fixes

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

V5: https://lkml.org/lkml/2020/2/26/58
V4: https://lkml.org/lkml/2020/2/20/59
V3: https://lkml.org/lkml/2020/2/19/1347
V2: https://lkml.org/lkml/2020/2/9/275
V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (6):
  vhost: allow per device message handler
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

Tiwei Bie (1):
  vhost: introduce vDPA-based backend

Zhu Lingshan (1):
  virtio: Intel IFC VF driver for VDPA

 MAINTAINERS                             |   2 +
 drivers/vhost/Kconfig                   |  17 +
 drivers/vhost/Kconfig.vringh            |   1 +
 drivers/vhost/Makefile                  |   6 +
 drivers/vhost/iotlb.c                   | 177 +++++
 drivers/vhost/net.c                     |   5 +-
 drivers/vhost/scsi.c                    |   2 +-
 drivers/vhost/vdpa.c                    | 883 ++++++++++++++++++++++++
 drivers/vhost/vhost.c                   | 233 +++----
 drivers/vhost/vhost.h                   |  45 +-
 drivers/vhost/vringh.c                  | 421 ++++++++++-
 drivers/vhost/vsock.c                   |   2 +-
 drivers/virtio/Kconfig                  |  15 +
 drivers/virtio/Makefile                 |   2 +
 drivers/virtio/vdpa/Kconfig             |  35 +
 drivers/virtio/vdpa/Makefile            |   4 +
 drivers/virtio/vdpa/ifcvf/Makefile      |   3 +
 drivers/virtio/vdpa/ifcvf/ifcvf_base.c  | 386 +++++++++++
 drivers/virtio/vdpa/ifcvf/ifcvf_base.h  | 133 ++++
 drivers/virtio/vdpa/ifcvf/ifcvf_main.c  | 494 +++++++++++++
 drivers/virtio/vdpa/vdpa.c              | 174 +++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 646 +++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 397 +++++++++++
 include/linux/vdpa.h                    | 232 +++++++
 include/linux/vhost_iotlb.h             |  47 ++
 include/linux/vringh.h                  |  36 +
 include/uapi/linux/vhost.h              |  24 +
 include/uapi/linux/vhost_types.h        |   8 +
 29 files changed, 4222 insertions(+), 210 deletions(-)
 create mode 100644 drivers/vhost/iotlb.c
 create mode 100644 drivers/vhost/vdpa.c
 create mode 100644 drivers/virtio/vdpa/Kconfig
 create mode 100644 drivers/virtio/vdpa/Makefile
 create mode 100644 drivers/virtio/vdpa/ifcvf/Makefile
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_base.c
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_base.h
 create mode 100644 drivers/virtio/vdpa/ifcvf/ifcvf_main.c
 create mode 100644 drivers/virtio/vdpa/vdpa.c
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [PATCH v7 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Wed Mar 18 16:37:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11445699
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A6021392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 16:37:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 40E5C20757
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 16:37:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="N23P3NtM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727188AbgCRQhs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 12:37:48 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:55183 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727151AbgCRQhs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 12:37:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584549466;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+UbzLGkfckNn6naER8zwWd5/jxYv9RSpbtDrZv7dGK0=;
        b=N23P3NtM6TvNWJmUPrdKuHUPmvbb4+das99xq1GRX1ZVDUHAR9cKHOU7vCj5U/8hoLaiXP
        QQc5APoZ1e3CIXH8kI212SWWZyxTfBdhVS/+3wzbf0K+thcxq9dV+4ZduptqXWGHxkRFxv
        tSLlzlqGUKS45kGnGk6dF9PnwVHNFdw=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-354-_Csrk2oINm6MunH5n8YpNQ-1; Wed, 18 Mar 2020 12:37:28 -0400
X-MC-Unique: _Csrk2oINm6MunH5n8YpNQ-1
Received: by mail-wm1-f69.google.com with SMTP id z16so1287576wmi.2
        for <kvm@vger.kernel.org>; Wed, 18 Mar 2020 09:37:28 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=+UbzLGkfckNn6naER8zwWd5/jxYv9RSpbtDrZv7dGK0=;
        b=BNvnpbP2TjvZsw//a+br6FKGNU7uOoI6j2LzpDtC/zrHdSU/iV4cpijOEdpPh0PXbp
         8rNsDKcWWeDYdckCIaz+Gjdo3R2puD5TyFrRfgjfMQpVUTZ1WseryOZ+InU5gaYKTFzd
         E8GDrC+t2VBp9+krVvxni/dJnhkEXVKFXr0y0sjrz+M7Bh+SxaJYpKImI5njQhmtqs2U
         AZSPApZ530NIwtwse6Cu0H51ZHvY12+vkVX/z8bUG3YOvNpfZikXMJCVDo/YCBbwHmD5
         ySGZetVL+n+zwhTgXq+BVF0ECJG29aHNq9v8aCnSQzR4xnPMvx8xUhnlmYS3vE4xvBmh
         tlFQ==
X-Gm-Message-State: ANhLgQ0BBQwsdsiWBXSgDQ8vawqvEafDwv2RXZO4A1TEPsI48U+19kqU
        hCNqbR74D8R41QrBVcvvUdzjVPRiw6HdDWkwxtszGDgirvN4X0thDvYXbmPWnqBxfNCOL6jZe+P
        1QlW6p190G/z1
X-Received: by 2002:a1c:9658:: with SMTP id y85mr6012859wmd.63.1584549447218;
        Wed, 18 Mar 2020 09:37:27 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vuErvTnZoNeMlI+5nYQs8Cqq5KfLf5VuUoka93mGML+mnpnKCUgo64dYCWUTANi1F5x7RA5fg==
X-Received: by 2002:a1c:9658:: with SMTP id y85mr6012823wmd.63.1584549446877;
        Wed, 18 Mar 2020 09:37:26 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 i4sm10411120wrm.32.2020.03.18.09.37.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 09:37:26 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: "Michael S . Tsirkin" <mst@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Yan Zhao <yan.y.zhao@intel.com>, peterx@redhat.com,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Christophe de Dinechin <dinechin@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v7 00/14] KVM: Dirty ring interface
Date: Wed, 18 Mar 2020 12:37:06 -0400
Message-Id: <20200318163720.93929-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v7
- rebase to kvm/queue
- make as_id an u16 [Sean]
- init_rmode_tss: rename idx to i, remove data init to zero [Sean]
- update doc for __x86_set_memory_region on ret value after rebase [Sean]
- fix sparse warnings for __x86_set_memory_region [syzbot]
- test cases [Drew]
  - use print_skip()
  - dump log modes without '\b'
  - support "all" log mode
  - exit(s/-1/1/)
  - assert gfns mmap in vcpu_map_dirty_ring
  - make vcpu_thread/current_vm static

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (14):
  KVM: X86: Change parameter for fast_page_fault tracepoint
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 123 +++++
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/mmutrace.h                       |   9 +-
 arch/x86/kvm/svm.c                            |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  89 +--
 arch/x86/kvm/x86.c                            |  50 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  78 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  99 +++-
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 505 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  68 +++
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 195 +++++++
 virt/kvm/kvm_main.c                           | 162 +++++-
 22 files changed, 1460 insertions(+), 138 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
#### [PATCH v4 0/2] KVM: VMX: cleanup VMXON region allocation
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Mar 18 17:17:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11445759
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 76A721667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 17:18:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5622420753
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 17:18:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KAEdYPmH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727065AbgCRRR7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 13:17:59 -0400
Received: from us-smtp-delivery-74.mimecast.com ([216.205.24.74]:30361 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726765AbgCRRR6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 18 Mar 2020 13:17:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1584551878;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1tmYrjNBPlfS8Oz+KPrbLzllyHIAIh5B4HPxuEUJj2k=;
        b=KAEdYPmHElhrsGgEW1Nfnc1wgjL/RifeSa+HORDnsU05M/yShr74lm25w1+mPOiJxVnR5R
        KzgAmsLd4jGiBs4N0B4Kcv0Tj3UH0rwY6xSGkuwWMyhHy9nNUFutXkNA2qyVRNUHhU0rwy
        zRQLkyKzzsLxnM5w2z/QiuaPKL6Oh/g=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-105-CXuIpPxuPS6QkbNjE9NrDg-1; Wed, 18 Mar 2020 13:17:56 -0400
X-MC-Unique: CXuIpPxuPS6QkbNjE9NrDg-1
Received: by mail-wr1-f70.google.com with SMTP id t4so8385329wrr.1
        for <kvm@vger.kernel.org>; Wed, 18 Mar 2020 10:17:56 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=1tmYrjNBPlfS8Oz+KPrbLzllyHIAIh5B4HPxuEUJj2k=;
        b=M09a/QFPxAiQQ/0xTRYfuvsEmGZCIoynqZGqOQ9svDlaTOhnUSYLzBoTYDQe0+CL4O
         FJPdzpKPXTg6QaV/TooG6mAnzcqR7PWSfabz6WHd9VXLrHXUT9bdPzmte84eJyYa7xQS
         gnij679N7Pj18UgaMngKba3K1vZQi3z3FpZMaZf4JpULlpQI5NBemmR7NZ9IalZTB23c
         juexapzLhJZMhO1palB6Mm0qLY5pFtjdCrRCp3CndFh2k1dw/GQ8GZlg1Ng7U2qa1Na7
         0aBqNSaC9EojZNGAy+bCXVFJ8sc8t1/AaQdxAgyvtFHqufebxR5TCU2eTz0bwPOeYkcZ
         A66A==
X-Gm-Message-State: ANhLgQ3KcoPmxVOjwQ/H7ZSw2cZPzzrfDfG23BXPKyLjLp//bMz7gZup
        Dz+rzenYkc8kjTm2zhnG/fwGX2V+eEURyOZcsJubO+MSRMaP1jwe0qrVzZt4K7IWdBJKhZsv+8j
        VRc837cJnlUKb
X-Received: by 2002:a5d:680d:: with SMTP id w13mr6619018wru.227.1584551875099;
        Wed, 18 Mar 2020 10:17:55 -0700 (PDT)
X-Google-Smtp-Source: 
 ADFU+vuV4gL9NnrUrL3uhgtDnC8jCR+eQZlEHteghQ1cIvY0SDIXvFJgPy1bqpym7Ng4rNGsdr2PWA==
X-Received: by 2002:a5d:680d:: with SMTP id w13mr6618996wru.227.1584551874821;
        Wed, 18 Mar 2020 10:17:54 -0700 (PDT)
Received: from vitty.brq.redhat.com (g-server-2.ign.cz. [91.219.240.2])
        by smtp.gmail.com with ESMTPSA id
 r3sm10531597wrw.76.2020.03.18.10.17.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 18 Mar 2020 10:17:54 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/2] KVM: VMX: cleanup VMXON region allocation
Date: Wed, 18 Mar 2020 18:17:50 +0100
Message-Id: <20200318171752.173073-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor cleanup with no functional change (intended):
- Rename 'kvm_area' to 'vmxon_region'
- Simplify setting revision_id for VMXON region when eVMCS is in use

Changes since v3:
- Rebase to kvm/queue
- Added Krish's Reviewed-by: tag to PATCH1
- Re-name 'enum vmcs_type' members [Sean Christopherson]

Vitaly Kuznetsov (2):
  KVM: VMX: rename 'kvm_area' to 'vmxon_region'
  KVM: VMX: untangle VMXON revision_id setting when using eVMCS

 arch/x86/kvm/vmx/nested.c |  2 +-
 arch/x86/kvm/vmx/vmx.c    | 44 ++++++++++++++++++---------------------
 arch/x86/kvm/vmx/vmx.h    | 12 ++++++++---
 3 files changed, 30 insertions(+), 28 deletions(-)
```
#### [PATCH v14 Kernel 0/7] KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Wed Mar 18 19:41:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11445881
Return-Path: <SRS0=/h1i=5D=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEF88159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 20:14:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B39C92077A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 18 Mar 2020 20:14:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="SRTUjqRc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726954AbgCRUO7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 18 Mar 2020 16:14:59 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:19230 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726733AbgCRUO6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 18 Mar 2020 16:14:58 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e7281270002>; Wed, 18 Mar 2020 13:14:31 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Wed, 18 Mar 2020 13:14:45 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Wed, 18 Mar 2020 13:14:45 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 18 Mar
 2020 20:14:44 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 18 Mar 2020 20:14:38 +0000
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
Subject: [PATCH v14 Kernel 0/7] KABIs to support migration for VFIO devices
Date: Thu, 19 Mar 2020 01:11:07 +0530
Message-ID: <1584560474-19946-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1584562472; bh=ZrueuZTFqaYO2Tyxu8ekQbb5H0RhZW6vUFkSFnd4d8k=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=SRTUjqRc5MTOgYB8n1wT5ApTRru71ZwyssTwNhfEiTP84dTTrbJjjuiwZG5BYwVCK
         fZz3ud54iYmALv1k5YqBFGhkcuctkoBl2Cz7WPMYaRTRE6P9Bey2cxpRtaYlKhv+Xv
         S9BI61TNsplX58MWxGlmMIJNN1AxaaZfsAeDfHMriZqoBug9gZSIc6alNfWvKGiE/n
         3sahWwYoLFeMBIKoseZKezIidA9GS4UeKlxC2J91Az8UW4lpeX08ZelsVzNXTAEH9o
         zZ0EeiMsU5Q/UHAQTNFozOztsdAlQHgnrnz4ARZ5K2TNrmPn0diCaaQOuhEaWoTaKW
         w/RgT5UpJ3xqw==
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
  This ioctl is also used to start/stop dirty pages tracking for pinned and
  unpinned pages while migration is active.

* Updated IOCTL VFIO_IOMMU_UNMAP_DMA to get dirty pages bitmap before
  unmapping IO virtual address range.
  With vIOMMU, during pre-copy phase of migration, while CPUs are still
  running, IO virtual address unmap can happen while device still keeping
  reference of guest pfns. Those pages should be reported as dirty before
  unmap, so that VFIO user space application can copy content of those
  pages from source to destination.

* Patch 7 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v13 -> v14
- Added struct vfio_bitmap to kabi. updated structure
  vfio_iommu_type1_dirty_bitmap_get and vfio_iommu_type1_dma_unmap.
- All small changes suggested by Alex.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v12 -> v13
- Changed bitmap allocation in vfio_iommu_type1 to per vfio_dma
- Changed VFIO_IOMMU_DIRTY_PAGES ioctl behaviour to be per vfio_dma range.
- Changed vfio_iommu_type1_dirty_bitmap structure to have separate data
  field.

v11 -> v12
- Changed bitmap allocation in vfio_iommu_type1.
- Remove atomicity of ref_count.
- Updated comments for migration device state structure about error
  reporting.
- Nit picks from v11 reviews

v10 -> v11
- Fix pin pages API to free vpfn if it is marked as unpinned tracking page.
- Added proposal to detect if IOMMU capable device calls external pin pages
  API to mark pages dirty.
- Nit picks from v10 reviews

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


Kirti Wankhede (7):
  vfio: KABI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Add ioctl definition for dirty pages tracking.
  vfio iommu: Implementation of ioctl for dirty pages tracking.
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Adds flag to indicate dirty pages tracking capability
    support
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 345 ++++++++++++++++++++++++++++++++++++++--
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 298 +++++++++++++++++++++++++++++++++-
 4 files changed, 642 insertions(+), 18 deletions(-)
```
