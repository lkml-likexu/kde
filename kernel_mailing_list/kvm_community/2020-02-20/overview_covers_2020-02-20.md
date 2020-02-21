

#### [PATCH V3 0/5] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Feb 20 03:56:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11393211
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A584517F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 03:57:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7471924672
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 03:57:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FZt8rc50"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727875AbgBTD52 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 19 Feb 2020 22:57:28 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:59380 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727476AbgBTD52 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 19 Feb 2020 22:57:28 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582171045;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=15SN9V81UVLGem5rXcaxlHKpBtKp5YAPvJYN8Vzu5VM=;
        b=FZt8rc50AXvQx0X0MrFNww4/F/5nEi26Gsvtf8jlmwnWJWMAMUlSRGjbmK9+DUPafSKWHE
        BEFp/PRTyLJ7Xuz1/2OaTQnkoikKkq5ezaSv0nBbRde+jDaSa1cnh3n2S2l/KnpeOyMEy3
        H+og/bD0d989L5gyjk1fipokdIe7VVA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-43-32L_vH3nO3qUInnWuDkhJA-1; Wed, 19 Feb 2020 22:57:14 -0500
X-MC-Unique: 32L_vH3nO3qUInnWuDkhJA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 48B34477;
        Thu, 20 Feb 2020 03:57:11 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-159.pek2.redhat.com [10.72.12.159])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 046505C219;
        Thu, 20 Feb 2020 03:56:52 +0000 (UTC)
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
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V3 0/5] vDPA support
Date: Thu, 20 Feb 2020 11:56:45 +0800
Message-Id: <20200220035650.7986-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
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
will be posted in future days.

Thanks

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

V2: https://lkml.org/lkml/2020/2/9/275
V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (5):
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

 MAINTAINERS                             |   2 +
 drivers/vhost/Kconfig                   |   7 +
 drivers/vhost/Kconfig.vringh            |   1 +
 drivers/vhost/Makefile                  |   2 +
 drivers/vhost/net.c                     |   2 +-
 drivers/vhost/vhost.c                   | 221 +++-----
 drivers/vhost/vhost.h                   |  36 +-
 drivers/vhost/vhost_iotlb.c             | 171 ++++++
 drivers/vhost/vringh.c                  | 421 ++++++++++++++-
 drivers/virtio/Kconfig                  |  15 +
 drivers/virtio/Makefile                 |   2 +
 drivers/virtio/vdpa/Kconfig             |  27 +
 drivers/virtio/vdpa/Makefile            |   3 +
 drivers/virtio/vdpa/vdpa.c              | 167 ++++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 660 ++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 392 ++++++++++++++
 include/linux/vdpa.h                    | 232 +++++++++
 include/linux/vhost_iotlb.h             |  45 ++
 include/linux/vringh.h                  |  36 ++
 20 files changed, 2240 insertions(+), 204 deletions(-)
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
#### [PATCH V4 0/5] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Thu Feb 20 06:11:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11393401
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DEA314BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 06:12:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4564720801
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 06:12:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZaeTz0nz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726799AbgBTGMU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 01:12:20 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:20170 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726165AbgBTGMU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 01:12:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582179138;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=mxrixuESiDQRJPG0EpTDwZw9g3MXQYNX4XsMJSeZOaU=;
        b=ZaeTz0nzADqnvf08TJjK/XSBssyY4dOU8EYVhHdbFbFJT8KPLUP9zFDU8kY+LOcJgLManF
        lM++bozSehGXfgcQ8w5qlT/qVOgR5mpiaOuHOrYvQIma+quMYEGZrVd2VwMqbLjRR2zY2B
        vH1mXsbJsvcx3nEiOikO0i8oiXxGuq4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-90-rDP2EHaaNniTRj94Y4QgYA-1; Thu, 20 Feb 2020 01:12:03 -0500
X-MC-Unique: rDP2EHaaNniTRj94Y4QgYA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C2B5F801E5C;
        Thu, 20 Feb 2020 06:12:00 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-159.pek2.redhat.com [10.72.12.159])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0F7375D9E2;
        Thu, 20 Feb 2020 06:11:44 +0000 (UTC)
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
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V4 0/5] vDPA support
Date: Thu, 20 Feb 2020 14:11:36 +0800
Message-Id: <20200220061141.29390-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
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

Thanks

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
 drivers/vhost/vhost_iotlb.c             | 171 ++++++
 drivers/vhost/vringh.c                  | 421 ++++++++++++++-
 drivers/virtio/Kconfig                  |  15 +
 drivers/virtio/Makefile                 |   2 +
 drivers/virtio/vdpa/Kconfig             |  26 +
 drivers/virtio/vdpa/Makefile            |   3 +
 drivers/virtio/vdpa/vdpa.c              | 167 ++++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 660 ++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 392 ++++++++++++++
 include/linux/vdpa.h                    | 232 +++++++++
 include/linux/vhost_iotlb.h             |  45 ++
 include/linux/vringh.h                  |  36 ++
 20 files changed, 2238 insertions(+), 204 deletions(-)
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
#### [PATCH v3 00/37] KVM: s390: Add support for protected VMs
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Thu Feb 20 10:39:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11393783
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47E58924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 10:40:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 284A52467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 10:40:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728063AbgBTKkm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 05:40:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4318 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727979AbgBTKkc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 05:40:32 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01KAYcx2057932;
        Thu, 20 Feb 2020 05:40:27 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8uchpgaa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 05:40:26 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01KAZmHm063773;
        Thu, 20 Feb 2020 05:40:26 -0500
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8uchpg8d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 05:40:26 -0500
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01KAH0AM020612;
        Thu, 20 Feb 2020 10:40:24 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma05wdc.us.ibm.com with ESMTP id 2y68973w8k-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 20 Feb 2020 10:40:24 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01KAeM7n53608710
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 20 Feb 2020 10:40:22 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D153A112062;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AE8AD112064;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Thu, 20 Feb 2020 10:40:22 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        Andrew Morton <akpm@linux-foundation.org>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>, linux-mm@kvack.org
Subject: [PATCH v3 00/37] KVM: s390: Add support for protected VMs
Date: Thu, 20 Feb 2020 05:39:43 -0500
Message-Id: <20200220104020.5343-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-20_02:2020-02-19,2020-02-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 mlxlogscore=999
 lowpriorityscore=0 malwarescore=0 suspectscore=0 adultscore=0
 clxscore=1015 impostorscore=0 spamscore=0 priorityscore=1501 bulkscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002200078
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

mm people: This series contains a "pretty small" common code memory
management change that will allow paging, guest backing with files etc
almost just like normal VMs. It should be a no-op for all architectures
not opting in. And it should be usable for others that also try to get
notified on "the pages are in the process of being used for things like
I/O". This time I included error handling and an ACK from Will Deacon.

mm-related patches CCed on linux-mm, the complete list can be found on
the KVM and linux-s390 list. 

Andrew, any chance to either take " mm:gup/writeback: add callbacks for
inaccessible pages" or ACK so that I can take it?

Overview
--------
Protected VMs (PVM) are KVM VMs, where KVM can't access the VM's state
like guest memory and guest registers anymore. Instead the PVMs are
mostly managed by a new entity called Ultravisor (UV), which provides
an API, so KVM and the PV can request management actions.

PVMs are encrypted at rest and protected from hypervisor access while
running. They switch from a normal operation into protected mode, so
we can still use the standard boot process to load a encrypted blob
and then move it into protected mode.

Rebooting is only possible by passing through the unprotected/normal
mode and switching to protected again.

All patches are in the protvirtv4 branch of the korg s390 kvm git
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=protvirtv5

Claudio presented the technology at his presentation at KVM Forum
2019.

https://static.sched.com/hosted_files/kvmforum2019/3b/ibm_protected_vms_s390x.pdf


v2 -> v3
- rebase against v5.6-rc2
- move some checks into the callers
- typo fixes
- extend UV query size
- do a tlb flush when entering/exiting protected mode
- more comments
- change interface to PV_ENABLE/DISABLE instead of vcpu/vm
  create/destroy
- lockdep checks for *is_protected calls
- locking improments
- move facility 161 to qemu
- checkpatch fixes
- merged error handling in mm patch
- removed vcpu pv commands
- use mp_state for setting the IPL PSW


v1 -> v2
- rebase on top of kvm/master
- pipe through rc and rrc. This might have created some churn here and
  there
- turn off sclp masking when rebooting into "unsecure"
- memory management simplification
- prefix page handling now via intercept 112
- io interrupt intervention request fix (do not use GISA)
- api.txt conversion to rst
- sample patches on top of mm/gup/writeback
- tons of review feedback
- kvm_uv debug feature fixes and unifications
- ultravisor information for /sys/firmware
- 

RFCv2 -> v1 (you can diff the protvirtv2 and the protvirtv3 branch)
- tons of review feedback integrated (see mail thread)
- memory management now complete and working
- Documentation patches merged
- interrupt patches merged
- CONFIG_KVM_S390_PROTECTED_VIRTUALIZATION_HOST removed
- SIDA interface integrated into memop
- for merged patches I removed reviews that were not in all patches


Christian Borntraeger (5):
  KVM: s390/mm: Make pages accessible before destroying the guest
  KVM: s390: protvirt: Add SCLP interrupt handling
  KVM: s390: protvirt: do not inject interrupts after start
  KVM: s390: rstify new ioctls in api.rst
  KVM: s390: protvirt: introduce and enable KVM_CAP_S390_PROTECTED

Claudio Imbrenda (3):
  mm:gup/writeback: add callbacks for inaccessible pages
  s390/mm: provide memory management functions for protected KVM guests
  KVM: s390/mm: handle guest unpin events

Janosch Frank (24):
  KVM: s390: protvirt: Add UV debug trace
  KVM: s390: add new variants of UV CALL
  KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
  KVM: s390: protvirt: Add KVM api documentation
  KVM: s390: protvirt: Secure memory is not mergeable
  KVM: s390: protvirt: Handle SE notification interceptions
  KVM: s390: protvirt: Instruction emulation
  KVM: s390: protvirt: Handle spec exception loops
  KVM: s390: protvirt: Add new gprs location handling
  KVM: S390: protvirt: Introduce instruction data area bounce buffer
  KVM: s390: protvirt: handle secure guest prefix pages
  KVM: s390: protvirt: Write sthyi data to instruction data area
  KVM: s390: protvirt: STSI handling
  KVM: s390: protvirt: disallow one_reg
  KVM: s390: protvirt: Do only reset registers that are accessible
  KVM: s390: protvirt: Only sync fmt4 registers
  KVM: s390: protvirt: Add program exception injection
  KVM: s390: protvirt: UV calls in support of diag308 0, 1
  KVM: s390: protvirt: Report CPU state to Ultravisor
  KVM: s390: protvirt: Support cmd 5 operation state
  KVM: s390: protvirt: Mask PSW interrupt bits for interception 104 and
    112
  KVM: s390: protvirt: Add UV cpu reset calls
  DOCUMENTATION: Protected virtual machine introduction and IPL
  s390: protvirt: Add sysfs firmware interface for Ultravisor
    information

Michael Mueller (1):
  KVM: s390: protvirt: Implement interrupt injection

Ulrich Weigand (1):
  KVM: s390/interrupt: do not pin adapter interrupt pages

Vasily Gorbik (3):
  s390/protvirt: introduce host side setup
  s390/protvirt: add ultravisor initialization
  s390/mm: add (non)secure page access exceptions handlers

 .../admin-guide/kernel-parameters.txt         |   5 +
 Documentation/virt/kvm/api.rst                |  91 +++-
 Documentation/virt/kvm/devices/s390_flic.rst  |  11 +-
 Documentation/virt/kvm/index.rst              |   2 +
 Documentation/virt/kvm/s390-pv-boot.rst       |  83 +++
 Documentation/virt/kvm/s390-pv.rst            | 116 ++++
 MAINTAINERS                                   |   1 +
 arch/s390/boot/Makefile                       |   2 +-
 arch/s390/boot/uv.c                           |  21 +-
 arch/s390/include/asm/gmap.h                  |   6 +
 arch/s390/include/asm/kvm_host.h              | 113 +++-
 arch/s390/include/asm/mmu.h                   |   2 +
 arch/s390/include/asm/mmu_context.h           |   1 +
 arch/s390/include/asm/page.h                  |   5 +
 arch/s390/include/asm/pgtable.h               |  35 +-
 arch/s390/include/asm/uv.h                    | 252 ++++++++-
 arch/s390/kernel/Makefile                     |   1 +
 arch/s390/kernel/pgm_check.S                  |   4 +-
 arch/s390/kernel/setup.c                      |   9 +-
 arch/s390/kernel/uv.c                         | 413 ++++++++++++++
 arch/s390/kvm/Makefile                        |   2 +-
 arch/s390/kvm/diag.c                          |   4 +
 arch/s390/kvm/intercept.c                     | 115 +++-
 arch/s390/kvm/interrupt.c                     | 399 ++++++++------
 arch/s390/kvm/kvm-s390.c                      | 509 +++++++++++++++---
 arch/s390/kvm/kvm-s390.h                      |  51 +-
 arch/s390/kvm/priv.c                          |  11 +-
 arch/s390/kvm/pv.c                            | 286 ++++++++++
 arch/s390/mm/fault.c                          |  78 +++
 arch/s390/mm/gmap.c                           |  65 ++-
 include/linux/gfp.h                           |   6 +
 include/uapi/linux/kvm.h                      |  43 +-
 mm/gup.c                                      |  15 +-
 mm/page-writeback.c                           |   5 +
 34 files changed, 2442 insertions(+), 320 deletions(-)
 create mode 100644 Documentation/virt/kvm/s390-pv-boot.rst
 create mode 100644 Documentation/virt/kvm/s390-pv.rst
 create mode 100644 arch/s390/kernel/uv.c
 create mode 100644 arch/s390/kvm/pv.c
```
#### [kvm-unit-tests PATCH v5 00/10] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Feb 20 12:00:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11393893
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 496C4159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 12:01:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 32C3E207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 12:01:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728019AbgBTMAx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 07:00:53 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:25817 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727962AbgBTMAx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 07:00:53 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01KBxiOG103106
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 07:00:51 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2y93kfxnx7-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 07:00:51 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Thu, 20 Feb 2020 12:00:48 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 20 Feb 2020 12:00:45 -0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01KC0iox23068750
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 20 Feb 2020 12:00:44 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3601CAE051;
        Thu, 20 Feb 2020 12:00:44 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 08CA1AE055;
        Thu, 20 Feb 2020 12:00:44 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.41])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 20 Feb 2020 12:00:43 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v5 00/10] s390x: Testing the Channel Subsystem
 I/O
Date: Thu, 20 Feb 2020 13:00:33 +0100
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
x-cbid: 20022012-0016-0000-0000-000002E893E2
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022012-0017-0000-0000-0000334BAFF8
Message-Id: <1582200043-21760-1-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-20_03:2020-02-19,2020-02-20 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 spamscore=0
 clxscore=1015 phishscore=0 mlxlogscore=999 impostorscore=0
 priorityscore=1501 adultscore=0 lowpriorityscore=0 malwarescore=0
 suspectscore=1 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002200091
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Goal of the series is to have a framwork to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test programm to define its own
interrupt handler. We need to do special work under interrupt like acknoledging
the interrupt.
  
Being working on PSW bits to allow I/O interrupt, we define new PSW bits
in arch_def.h and use __ASSEMBLER__ define to be able to include this header
in an assembler source file.

This series presents four major tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled  
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analysing the answer and expecting
        the Control unit type being 0xc0ca
        Checks SSCH(READ) and IO-IRQ

- ping-pong:
        If the reference channel leads to the PONG device (0xc0ca),
        the test exchanges a string containing a 9 digit number with
        the PONG device and expecting this number to be incremented
        by the PONG device.
        Checks SSCH(WRITE)


Pierre Morel (10):
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: cr0: adding AFP-register control bit
  s390x: interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

 lib/s390x/asm/arch_def.h |  19 ++-
 lib/s390x/asm/time.h     |  36 +++++
 lib/s390x/css.h          | 277 +++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 157 ++++++++++++++++++
 lib/s390x/css_lib.c      |  55 +++++++
 lib/s390x/interrupt.c    |  22 ++-
 lib/s390x/interrupt.h    |   7 +
 s390x/Makefile           |   3 +
 s390x/css.c              | 341 +++++++++++++++++++++++++++++++++++++++
 s390x/cstart64.S         |  40 +++--
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 12 files changed, 946 insertions(+), 26 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH v3 00/20] global exec/memory/dma APIs cleanup
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu Feb 20 13:05:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11394033
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D13B117E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 13:06:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A71F2222C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 13:06:03 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="MUCDutVh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728102AbgBTNGC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 08:06:02 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:24721 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728091AbgBTNGC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Feb 2020 08:06:02 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582203960;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
  content-type:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=gu1OfO+Xr177r6zD7C+F/TxHFq6mosreIYv9UCpXME0=;
        b=MUCDutVhDBbvX3ov+Fy1NTGQKNeK9o2RCCGMZwVhiQZnKU4Uy/2f+jQYVj8gng8mP/n+xj
        uGQBe1IlenUeVZppYdS5QW5juQnXTs6UhS0n+Xm1Bb1qAvwbFYSVD1pCv59YkyF0zf99GX
        +xK23nJuP5wx7gJCbcervH+B538rAU4=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-141-4YOFUXg1NmK0mY8QyJCT9A-1; Thu, 20 Feb 2020 08:05:54 -0500
X-MC-Unique: 4YOFUXg1NmK0mY8QyJCT9A-1
Received: by mail-wm1-f69.google.com with SMTP id g138so576653wmg.8
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 05:05:54 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gu1OfO+Xr177r6zD7C+F/TxHFq6mosreIYv9UCpXME0=;
        b=BhEp4ycat83vSIjyap75qQusN6HSbqeLXFCzj1zhvIyUJyHz6C63KrDLKON5aB0OIh
         R0xvrbev8VQhMJ6o1jOYE0N7bVwno1WRLzJaW136hUKysbwq0fBmnDwtHbv1FToDjihk
         7ijo4uAxzDHk+ksgVnG1KQk9sA78nHbYQH3o+dk2+GEnJ+K39JdPi2xpXR8GHvpRH2c1
         UYz9kEB8f9YgJWwWe2MMTrb3ymU4/uuLUTamnQ3oLD6kEiegyp2roDjwUhG0cXOmbb3Q
         vUNAJLD9o50N4RRQrkbAbyMwLBaLhZwSK9M/pSroHt/m2tJbR09tAyqpARcfMNjHJXiy
         ctaQ==
X-Gm-Message-State: APjAAAWq05mwhFG/vh+f73bHsDrIpkyN3tAM03eFWYeC3rWM5RAQMf9k
        L3Chow91Ogr0H4GlZKh296U8p10MOjBsdLsmQccjyoykmZQohRictYBCsvrx4bfD4jPqcDxOE35
        AltI7qxFmr1kn
X-Received: by 2002:a1c:f713:: with SMTP id v19mr4357657wmh.113.1582203953757;
        Thu, 20 Feb 2020 05:05:53 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqzh9hNepHCOwe2XDVm3wY3ajt8F8GOM+lVXRr3SymvEGFarpB4eXHypTAiBAMMl7y3VSmAESQ==
X-Received: by 2002:a1c:f713:: with SMTP id v19mr4357638wmh.113.1582203953503;
        Thu, 20 Feb 2020 05:05:53 -0800 (PST)
Received: from localhost.localdomain (78.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.78])
        by smtp.gmail.com with ESMTPSA id
 b67sm4594690wmc.38.2020.02.20.05.05.49
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 20 Feb 2020 05:05:52 -0800 (PST)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: Peter Maydell <peter.maydell@linaro.org>, qemu-devel@nongnu.org
Cc: "Edgar E. Iglesias" <edgar.iglesias@gmail.com>,
 Anthony Perard <anthony.perard@citrix.com>, Fam Zheng <fam@euphon.net>,
	=?utf-8?q?Herv=C3=A9_Poussineau?= <hpoussin@reactos.org>, =?utf-8?q?Philipp?=
	=?utf-8?q?e_Mathieu-Daud=C3=A9?= <philmd@redhat.com>, kvm@vger.kernel.org,
 Laurent Vivier <lvivier@redhat.com>, Thomas Huth <thuth@redhat.com>,
 Stefan Weil <sw@weilnetz.de>, Eric Auger <eric.auger@redhat.com>,
 Halil Pasic <pasic@linux.ibm.com>,
 Marcel Apfelbaum <marcel.apfelbaum@gmail.com>, qemu-s390x@nongnu.org,
 Aleksandar Rikalo <aleksandar.rikalo@rt-rk.com>,
 David Gibson <david@gibson.dropbear.id.au>, Michael Walle <michael@walle.cc>,
 qemu-ppc@nongnu.org, Gerd Hoffmann <kraxel@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>, qemu-arm@nongnu.org,
 Alistair Francis <alistair@alistair23.me>, qemu-block@nongnu.org,
	=?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>,
 Jason Wang <jasowang@redhat.com>, xen-devel@lists.xenproject.org,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Dmitry Fleytman <dmitry.fleytman@gmail.com>,
 Matthew Rosato <mjrosato@linux.ibm.com>,
 Eduardo Habkost <ehabkost@redhat.com>,
 Richard Henderson <richard.henderson@linaro.org>,
 "Michael S. Tsirkin" <mst@redhat.com>, David Hildenbrand <david@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Stefano Stabellini <sstabellini@kernel.org>,
 Igor Mitsyanko <i.mitsyanko@gmail.com>, Paul Durrant <paul@xen.org>,
 Richard Henderson <rth@twiddle.net>, John Snow <jsnow@redhat.com>
Subject: [PATCH v3 00/20] global exec/memory/dma APIs cleanup
Date: Thu, 20 Feb 2020 14:05:28 +0100
Message-Id: <20200220130548.29974-1-philmd@redhat.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is inspired from Peter Maydel cleanup patch:
https://www.mail-archive.com/qemu-devel@nongnu.org/msg680625.html

- Convert 'is_write' argument to boolean
- Use void pointer for blob buffer
- Remove unnecessary casts (Stefan Weil)
- Replace [API]_rw() by [API]_read/write() when is_write is constant

Supersedes: <20200218112457.22712-1-peter.maydell@linaro.org>

Peter Maydell (1):
  Avoid address_space_rw() with a constant is_write argument

Philippe Mathieu-Daudé (19):
  scripts/git.orderfile: Display Cocci scripts before code modifications
  hw: Remove unnecessary cast when calling dma_memory_read()
  exec: Let qemu_ram_*() functions take a const pointer argument
  exec: Rename ram_ptr variable
  exec: Let flatview API take void pointer arguments
  exec: Let the address_space API use void pointer arguments
  hw/net: Avoid casting non-const pointer, use address_space_write()
  Remove unnecessary cast when using the address_space API
  exec: Let the cpu_[physical]_memory API use void pointer arguments
  Remove unnecessary cast when using the cpu_[physical]_memory API
  hw/ide/internal: Remove unused DMARestartFunc typedef
  hw/ide: Let the DMAIntFunc prototype use a boolean 'is_write' argument
  hw/virtio: Let virtqueue_map_iovec() use a boolean 'is_write' argument
  hw/virtio: Let vhost_memory_map() use a boolean 'is_write' argument
  exec: Let address_space_unmap() use a boolean 'is_write' argument
  Let address_space_rw() calls pass a boolean 'is_write' argument
  exec: Let cpu_[physical]_memory API use a boolean 'is_write' argument
  Let cpu_[physical]_memory() calls pass a boolean 'is_write' argument
  Avoid cpu_physical_memory_rw() with a constant is_write argument

 scripts/coccinelle/exec_rw_const.cocci | 103 +++++++++++++++++++++++++
 include/exec/cpu-all.h                 |   2 +-
 include/exec/cpu-common.h              |  18 ++---
 include/exec/memory.h                  |  16 ++--
 include/hw/ide/internal.h              |   3 +-
 include/sysemu/xen-mapcache.h          |   4 +-
 target/i386/hvf/vmx.h                  |   7 +-
 accel/kvm/kvm-all.c                    |   6 +-
 dma-helpers.c                          |   4 +-
 exec.c                                 |  75 +++++++++---------
 hw/arm/boot.c                          |   6 +-
 hw/arm/smmu-common.c                   |   3 +-
 hw/arm/smmuv3.c                        |  10 +--
 hw/display/exynos4210_fimd.c           |   3 +-
 hw/display/milkymist-tmu2.c            |   8 +-
 hw/display/omap_dss.c                  |   2 +-
 hw/display/omap_lcdc.c                 |  10 +--
 hw/display/ramfb.c                     |   2 +-
 hw/dma/etraxfs_dma.c                   |  25 +++---
 hw/dma/rc4030.c                        |  10 +--
 hw/dma/xlnx-zdma.c                     |  11 +--
 hw/i386/xen/xen-mapcache.c             |   2 +-
 hw/ide/ahci.c                          |   2 +-
 hw/ide/core.c                          |   2 +-
 hw/ide/macio.c                         |   2 +-
 hw/ide/pci.c                           |   2 +-
 hw/misc/pc-testdev.c                   |   2 +-
 hw/net/cadence_gem.c                   |  21 +++--
 hw/net/dp8393x.c                       |  70 +++++++++--------
 hw/net/i82596.c                        |  25 +++---
 hw/net/lasi_i82596.c                   |   5 +-
 hw/nvram/spapr_nvram.c                 |   4 +-
 hw/ppc/pnv_lpc.c                       |   8 +-
 hw/ppc/ppc440_uc.c                     |   6 +-
 hw/ppc/spapr_hcall.c                   |   4 +-
 hw/s390x/css.c                         |  12 +--
 hw/s390x/ipl.c                         |   2 +-
 hw/s390x/s390-pci-bus.c                |   2 +-
 hw/s390x/virtio-ccw.c                  |   2 +-
 hw/scsi/vmw_pvscsi.c                   |   8 +-
 hw/sd/sdhci.c                          |  15 ++--
 hw/virtio/vhost.c                      |   8 +-
 hw/virtio/virtio.c                     |   7 +-
 hw/xen/xen_pt_graphics.c               |   2 +-
 qtest.c                                |  52 ++++++-------
 target/i386/hax-all.c                  |   6 +-
 target/i386/hvf/x86_mmu.c              |  12 +--
 target/i386/whpx-all.c                 |   2 +-
 target/s390x/excp_helper.c             |   2 +-
 target/s390x/helper.c                  |   6 +-
 target/s390x/mmu_helper.c              |   2 +-
 scripts/git.orderfile                  |   3 +
 52 files changed, 360 insertions(+), 266 deletions(-)
 create mode 100644 scripts/coccinelle/exec_rw_const.cocci
```
#### [PATCH RFC 0/2] KVM: nVMX: fix apicv disablement for L1
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Thu Feb 20 17:22:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11394719
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 93FFF14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 17:22:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3898F24680
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 17:22:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="a9QKLynW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728799AbgBTRWp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 12:22:45 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:42233 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728896AbgBTRWP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 12:22:15 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582219335;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rZyXD5q+onhmCDPHKZnUNJAstGhWUGrhi7Vh7fDt5g0=;
        b=a9QKLynW6RUm++W22qLQQxtWjevCgd061TBDDHsrTYQ6nYITuvStFDXPItVzdd71dDodCt
        0SytloLUuu3DN5cT6yVU0mJQ160bta3lGis185UIHS/akE7F+Gpx/wV6nlCXbo1fMQZctF
        V4KOxWt2xRTfurypSgVE2+WKcZBKNEs=
Received: from mail-wm1-f71.google.com (mail-wm1-f71.google.com
 [209.85.128.71]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-419-QhU0mJ4QO262gXPKlvMnXw-1; Thu, 20 Feb 2020 12:22:09 -0500
X-MC-Unique: QhU0mJ4QO262gXPKlvMnXw-1
Received: by mail-wm1-f71.google.com with SMTP id g138so842921wmg.8
        for <kvm@vger.kernel.org>; Thu, 20 Feb 2020 09:22:09 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rZyXD5q+onhmCDPHKZnUNJAstGhWUGrhi7Vh7fDt5g0=;
        b=DAo83Xtpj5PJODzXvLkXFPSMc3Kc29mKr78T3GS9WZM/Ly/AtlhgbruKDjpdYWnsPM
         4v7D58N2sFfByF6VUPpTnTNWDeLD+VVujyERHgosHBem2P/ELvChiH3GXIfMuRipQ5jN
         jpYJQ+ebRNrnO7OoRy81KKgX/444gbd5EOM3yL0wMCQRP9nlHXcOqa44rpX/3KohE/z5
         cJxGb13HLiWgcwZpZUnVkZiQflVK1/7/kztApaFT6Kpr8hzuvYyFXX9AsM4pAu9GSrxC
         /xaZEJA6dpFfdZiVK7srX3qexWivakk4PeLVRCyTZcSnCWSer5D2BorVKLsRThZCabCp
         /a4Q==
X-Gm-Message-State: APjAAAVESP7Lvs6V8jwgvTR7hTraNxuQjqJJ9AmEt4vHhg9KVI+sx+xg
        IM4vCBMWe8U8tzh5zFX7QXOLh5R8yixKvH1vWdD7fyoRYpUS9TXvC44yUtJ0aBSG6fvEgSvEybd
        iJbMtO31gFdwk
X-Received: by 2002:adf:fd87:: with SMTP id d7mr45699846wrr.226.1582219328193;
        Thu, 20 Feb 2020 09:22:08 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqyznpk/Mju2cxo6UDLosBl/WALhWP2M64Z82L2SgtLE3m4B2Qb1Kh7smxIT3jRFYoOJt4jZkQ==
X-Received: by 2002:adf:fd87:: with SMTP id d7mr45699820wrr.226.1582219327916;
        Thu, 20 Feb 2020 09:22:07 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 a184sm5355891wmf.29.2020.02.20.09.22.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 20 Feb 2020 09:22:07 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Jim Mattson <jmattson@google.com>, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH RFC 0/2] KVM: nVMX: fix apicv disablement for L1
Date: Thu, 20 Feb 2020 18:22:03 +0100
Message-Id: <20200220172205.197767-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was found that fine-grained VMX feature enablement in QEMU is broken
when combined with SynIC:

    qemu-system-x86_64 -machine q35,accel=kvm -cpu host,hv_vpindex,hv_synic -smp 2 -m 16384 -vnc :0
    qemu-system-x86_64: error: failed to set MSR 0x48d to 0xff00000016
    qemu-system-x86_64: <...>: kvm_buf_set_msrs: Assertion `ret == cpu->kvm_msr_buf->nmsrs' failed.
    Aborted

QEMU thread: https://lists.gnu.org/archive/html/qemu-devel/2020-02/msg04838.html

Turns out, this is a KVM issue: when SynIC is enabled, PIN_BASED_POSTED_INTR
gets filtered out from VMX MSRs for all newly created (but not existent!)
vCPUS. Patch1 addresses this. Also, apicv disablement for L1 doesn't seem
to disable it for L2 (at least on CPU0) so unless there's a good reason
to not allow this we need to make it work. PATCH2, suggested by Paolo,
is supposed to do the job.

RFC: I looked at the code and ran some tests and nothing suspicious popped
out, however, I'm still not convinced this is a good idea to have apicv
enabled for L2 when it's disabled for L1... Also, we may prefer to merge
or re-order these two patches.

Vitaly Kuznetsov (2):
  KVM: nVMX: clear PIN_BASED_POSTED_INTR from nested pinbased_ctls only
    when apicv is globally disabled
  KVM: nVMX: handle nested posted interrupts when apicv is disabled for
    L1

 arch/x86/include/asm/kvm_host.h |  2 +-
 arch/x86/kvm/lapic.c            |  5 +----
 arch/x86/kvm/svm.c              |  7 ++++++-
 arch/x86/kvm/vmx/capabilities.h |  1 +
 arch/x86/kvm/vmx/nested.c       |  5 ++---
 arch/x86/kvm/vmx/nested.h       |  3 +--
 arch/x86/kvm/vmx/vmx.c          | 23 +++++++++++++----------
 7 files changed, 25 insertions(+), 21 deletions(-)
```
#### [PATCH 00/10] KVM: x86: Clean up VMX's TLB flushing code
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Feb 20 20:43:46 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11394987
Return-Path: <SRS0=rqLM=4I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B434214BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 20:44:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9DD13208CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Feb 2020 20:44:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728976AbgBTUn6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Feb 2020 15:43:58 -0500
Received: from mga12.intel.com ([192.55.52.136]:13654 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728582AbgBTUn6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 20 Feb 2020 15:43:58 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Feb 2020 12:43:58 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,465,1574150400";
   d="scan'208";a="349237088"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga001.fm.intel.com with ESMTP; 20 Feb 2020 12:43:57 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 00/10] KVM: x86: Clean up VMX's TLB flushing code
Date: Thu, 20 Feb 2020 12:43:46 -0800
Message-Id: <20200220204356.8837-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is technically x86 wide, but it only superficially affects
SVM, the motivation and primary touchpoints are all about VMX.

The goal of this series to ultimately clean up __vmx_flush_tlb(), which,
for me, manages to be extremely confusing despite being only ten lines of
code.

The most confusing aspect of __vmx_flush_tlb() is that it is overloaded
for multiple uses:

 1) TLB flushes in response to a change in KVM's MMU

 2) TLB flushes during nested VM-Enter/VM-Exit when VPID is enabled

 3) Guest-scoped TLB flushes for paravirt TLB flushing

Handling (2) and (3) in the same flow as (1) is kludgy, because the rules
for (1) are quite different than the rules for (2) and (3).  They're all
squeezed into __vmx_flush_tlb() via the @invalidate_gpa param, which means
"invalidate gpa mappings", not "invalidate a specific gpa"; it took me
forever and a day to realize that.

To clean things up, handle (2) by directly calling vpid_sync_context()
instead of bouncing through __vmx_flush_tlb(), and handle (3) via a
dedicated kvm_x86_ops hook.  This allows for a less tricky implementation
of vmx_flush_tlb() for (1), and (hopefully) clarifies the rules for what
mappings must be invalidated when.

Sean Christopherson (10):
  KVM: VMX: Use vpid_sync_context() directly when possible
  KVM: VMX: Move vpid_sync_vcpu_addr() down a few lines
  KVM: VMX: Handle INVVPID fallback logic in vpid_sync_vcpu_addr()
  KVM: VMX: Fold vpid_sync_vcpu_{single,global}() into
    vpid_sync_context()
  KVM: nVMX: Use vpid_sync_vcpu_addr() to emulate INVVPID with address
  KVM: x86: Move "flush guest's TLB" logic to separate kvm_x86_ops hook
  KVM: VMX: Clean up vmx_flush_tlb_gva()
  KVM: x86: Drop @invalidate_gpa param from kvm_x86_ops' tlb_flush()
  KVM: VMX: Drop @invalidate_gpa from __vmx_flush_tlb()
  KVM: VMX: Fold __vmx_flush_tlb() into vmx_flush_tlb()

 arch/x86/include/asm/kvm_host.h |  8 +++++++-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/svm.c              | 14 ++++++++++----
 arch/x86/kvm/vmx/nested.c       | 12 ++++--------
 arch/x86/kvm/vmx/ops.h          | 32 +++++++++-----------------------
 arch/x86/kvm/vmx/vmx.c          | 26 +++++++++++++++++---------
 arch/x86/kvm/vmx/vmx.h          | 19 ++++++++++---------
 arch/x86/kvm/x86.c              |  8 ++++----
 8 files changed, 62 insertions(+), 59 deletions(-)
```
