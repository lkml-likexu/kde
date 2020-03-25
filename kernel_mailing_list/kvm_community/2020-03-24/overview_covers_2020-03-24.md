

#### [PATCH V7 0/8] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Tue Mar 24 04:14:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11454417
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 06DBB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:15:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CA99B2073E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 04:15:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CSqU8yAG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727243AbgCXEPn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 00:15:43 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:37056 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727063AbgCXEPl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 00:15:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585023340;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=/axwIiBryEcrWRjK7QlRFkT8Que8Kl7fqB8RtGBmu4Q=;
        b=CSqU8yAGLxix9xxmBude5gwrDEQLakvxK8itG5eeHT6HuXDjPPgdhVQC2aOlk4uh4S4Y5v
        Yh3SXDjfDlUaCAPwY79U2XeAYtrn4bWdbcwFFyGqCpONX0W9UGn5Aqv7WMixQ8HSUw39vD
        zn3Ig03rh3d8PNG52asuxdh6HduNhMM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-310-GlINFfSdNKGQdEIE3IYZYA-1; Tue, 24 Mar 2020 00:15:23 -0400
X-MC-Unique: GlINFfSdNKGQdEIE3IYZYA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 103EC189F760;
        Tue, 24 Mar 2020 04:15:20 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-216.pek2.redhat.com [10.72.13.216])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F26EF10002A9;
        Tue, 24 Mar 2020 04:15:00 +0000 (UTC)
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
Subject: [PATCH V7 0/8] vDPA support
Date: Tue, 24 Mar 2020 12:14:50 +0800
Message-Id: <20200324041458.27384-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
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

Changes from V6:

- vdpa_alloc_device() will allocate parent strcture (Jason)
- remove the vdpa core dev info in IFCVF patch (Jason)
- provide a free method in the vdpa bus operations for drivet to free
  private data
- switch to use new layout in vdapsim and IFCVF
- make IFCVF depends on PCI_MSI (kbuild)
- some tweaks on the IFCVF driver

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

V6: https://lkml.org/lkml/2020/3/18/88
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
 drivers/virtio/vdpa/ifcvf/ifcvf_base.h  | 132 ++++
 drivers/virtio/vdpa/ifcvf/ifcvf_main.c  | 474 +++++++++++++
 drivers/virtio/vdpa/vdpa.c              | 180 +++++
 drivers/virtio/vdpa/vdpa_sim/Makefile   |   2 +
 drivers/virtio/vdpa/vdpa_sim/vdpa_sim.c | 629 +++++++++++++++++
 drivers/virtio/virtio_vdpa.c            | 396 +++++++++++
 include/linux/vdpa.h                    | 247 +++++++
 include/linux/vhost_iotlb.h             |  47 ++
 include/linux/vringh.h                  |  36 +
 include/uapi/linux/vhost.h              |  24 +
 include/uapi/linux/vhost_types.h        |   8 +
 29 files changed, 4204 insertions(+), 210 deletions(-)
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
#### [PATCH -tip 0/4] kvm: Use rcuwait for vcpu blocking
##### From: Davidlohr Bueso <dave@stgolabs.net>

```c
Received: from relay2.suse.de (unknown [195.135.220.254])
        by mx2.suse.de (Postfix) with ESMTP id EE759AE1C;
        Tue, 24 Mar 2020 04:46:04 +0000 (UTC)
From: Davidlohr Bueso <dave@stgolabs.net>
To: tglx@linutronix.de, pbonzini@redhat.com
Cc: bigeasy@linutronix.de, peterz@infradead.org, rostedt@goodmis.org,
        torvalds@linux-foundation.org, will@kernel.org,
        joel@joelfernandes.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, dave@stgolabs.net
Subject: [PATCH -tip 0/4] kvm: Use rcuwait for vcpu blocking
Date: Mon, 23 Mar 2020 21:44:49 -0700
Message-Id: <20200324044453.15733-1-dave@stgolabs.net>
X-Mailer: git-send-email 2.16.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The following is an updated revision of the kvm vcpu to rcuwait conversion[0],
following the work on completions using simple waitqueues.

Changes from then:
  - patch 2: Make rcuwait_wake_up() propagate the return value from
    wake_up_process - Sebastian and Peter.

  - patch 3:
      o Added mips changes I missed.
      o Fixed broken compilation on power, adding the vcore bits that
        kvm-hv uses (a vcore blocking when all vcpus are blocked) - Paolo.
      o Use TASK_IDLE instead of TASK_INTERRUPTIBLE - Peter.

  - patch 4: fixed swait function name typo.

This has only been run tested on x86 but compile tested on mips, powerpc
and arm32. 

This series applies on top of current -tip, which has the required rcuwait
api extension.

[0] https://lore.kernel.org/lkml/20200320085527.23861-3-dave@stgolabs.net/

Thanks!

Davidlohr Bueso (4):
  rcuwait: Fix stale wake call name in comment
  rcuwait: Let rcuwait_wake_up() return whether or not a task was awoken
  kvm: Replace vcpu->swait with rcuwait
  sched/swait: Reword some of the main description

 arch/mips/kvm/mips.c                  |  6 ++----
 arch/powerpc/include/asm/kvm_book3s.h |  2 +-
 arch/powerpc/include/asm/kvm_host.h   |  2 +-
 arch/powerpc/kvm/book3s_hv.c          | 22 ++++++++--------------
 arch/powerpc/kvm/powerpc.c            |  2 +-
 arch/x86/kvm/lapic.c                  |  2 +-
 include/linux/kvm_host.h              | 10 +++++-----
 include/linux/rcuwait.h               |  2 +-
 include/linux/swait.h                 | 23 +++++------------------
 kernel/exit.c                         |  9 ++++++---
 virt/kvm/arm/arch_timer.c             |  2 +-
 virt/kvm/arm/arm.c                    |  9 +++++----
 virt/kvm/async_pf.c                   |  3 +--
 virt/kvm/kvm_main.c                   | 31 +++++++++++--------------------
 14 files changed, 49 insertions(+), 76 deletions(-)
---
2.16.4
```
#### [PATCH v10 0/7] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Tue Mar 24 07:43:34 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11454629
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 962BB15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 07:44:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 73C8920724
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 07:44:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XynFwbRU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727381AbgCXHoA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 03:44:00 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:37247 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727291AbgCXHn7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 03:43:59 -0400
Received: by mail-wm1-f66.google.com with SMTP id d1so2310735wmb.2;
        Tue, 24 Mar 2020 00:43:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x83RKqJB2n+t2r4ylEIrnwFiRIR5HK76vMGn1RDuu7o=;
        b=XynFwbRUPKgZuXP41JonwGOogmnAma+S9VOj5HINOPYCNrMNteFbUrS7b6Jg15Mtfi
         DYDA1ENVBivYbMky3PV7SqTquxjJTV25rvQnxi4yLEv9s4MYrRj8RZJq2v40jONwxzPm
         OAzO7CCIHPXTtUJ0xj3lZKiUkQoyrXepE2HzTqzYbJlaBBvis5P4wQadOX3CBjHBsESN
         Xee54oYy4+4MbSqoZUKuDKAD9Ldb82gLtwS2yNA7DMT9cTU0StC6zwahzMCx3jclqxaJ
         kH40jDs/iN7cq/l6U1Byu1DEB1RIyF+oB4dy1QSLzdiQJkRjMEEoQVB0D7BuoiutytHU
         DLgg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=x83RKqJB2n+t2r4ylEIrnwFiRIR5HK76vMGn1RDuu7o=;
        b=Jl0mre1uIaa2BqNx4oFt6erBiEC6/QDUsi9jvrtEXIRGhCOPqXIz9MSE+53OgET0ae
         PlEk6B1tIXoC8AeLkrsaQDfCif4VFBv8366/eKlFTxB7+Ez6defSkXQcnZTrldAEd4Kp
         SKhn0cnZhrKGt0TXsADRAlIKqQZggG+6MT6UZS521girsSN+xjhoTtZuHfKhmxs87mcQ
         kWhYMvP0Oc2Yojqo2iAWA5O2m0Uj5cv5aadKZTxfsGdUaf1nqfgSDfKD98DG3jhY4xlT
         3SprxrqLm5noCVDiH91oDYIAVe3OGxVmFqRF100JtmGy+2Z1HKJ+qb9iBjk4zpoZyqVI
         lL4A==
X-Gm-Message-State: ANhLgQ39BRIDB4gcXGpa5OMvOKN1WNFJZl2CIaddRVDpEuvmZjb3DlVw
        lirAtGnxKarpsndUpEKFACL04T0mtYU=
X-Google-Smtp-Source: 
 ADFU+vuoTuJk1O6fps0iDtVnZm53HrP55jyibUyS6XqsTR2zqW67EDU6IZhQFJOlPL3XTsh0o9Qt0Q==
X-Received: by 2002:a7b:c8cc:: with SMTP id f12mr3543254wml.172.1585035837456;
        Tue, 24 Mar 2020 00:43:57 -0700 (PDT)
Received: from jondnuc.lan (IGLD-84-229-155-229.inter.net.il.
 [84.229.155.229])
        by smtp.gmail.com with ESMTPSA id
 r15sm22066122wra.19.2020.03.24.00.43.56
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 24 Mar 2020 00:43:56 -0700 (PDT)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v10 0/7] x86/kvm/hyper-v: add support for synthetic debugger
Date: Tue, 24 Mar 2020 09:43:34 +0200
Message-Id: <20200324074341.1770081-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information (undocumented so it's not
   going to the hyperv-tlfs.h)
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

The first mode implementation is to simply exit to user-space when
either the control MSR or the pending MSR are being set.
Then it's up-to userspace to implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

It's important to note that part of this feature has been subject to be
removed in future versions of Windows, which is why some of the
defintions will not be present the the TLFS but in the kvm hyperv header
instead.

Jon Doron (6):
  x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
  x86/kvm/hyper-v: Simplify addition for custom cpuid leafs
  x86/hyper-v: Add synthetic debugger definitions
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls without hypercall page with syndbg
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

Vitaly Kuznetsov (1):
  KVM: selftests: update hyperv_cpuid with SynDBG tests

 Documentation/virt/kvm/api.rst                |  18 ++
 arch/x86/include/asm/hyperv-tlfs.h            |   6 +
 arch/x86/include/asm/kvm_host.h               |  14 +
 arch/x86/kvm/hyperv.c                         | 242 ++++++++++++++++--
 arch/x86/kvm/hyperv.h                         |  33 +++
 arch/x86/kvm/trace.h                          |  51 ++++
 arch/x86/kvm/x86.c                            |  13 +
 include/uapi/linux/kvm.h                      |  13 +
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 139 ++++++----
 9 files changed, 469 insertions(+), 60 deletions(-)
```
#### [kvm-unit-tests PATCH 00/10] s390x: smp: Improve smp code part 2
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Mar 24 08:12:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11454755
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A41D139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 08:13:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 56A8220870
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 08:13:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727107AbgCXING (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 04:13:06 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:5938 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726166AbgCXING (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 04:13:06 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 02O85utI125783
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 04:13:05 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2ywd8ctk8m-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 24 Mar 2020 04:13:04 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 24 Mar 2020 08:13:01 -0000
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 24 Mar 2020 08:12:58 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 02O8CwOq45809846
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Mar 2020 08:12:58 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 938A8A4060;
        Tue, 24 Mar 2020 08:12:58 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F047A4054;
        Tue, 24 Mar 2020 08:12:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.9.40])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 24 Mar 2020 08:12:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com
Subject: [kvm-unit-tests PATCH 00/10] s390x: smp: Improve smp code part 2
Date: Tue, 24 Mar 2020 04:12:41 -0400
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20032408-0008-0000-0000-00000362DE2D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20032408-0009-0000-0000-00004A844979
Message-Id: <20200324081251.28810-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.645
 definitions=2020-03-24_02:2020-03-23,2020-03-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 suspectscore=0
 malwarescore=0 mlxlogscore=574 spamscore=0 lowpriorityscore=0 phishscore=0
 adultscore=0 priorityscore=1501 bulkscore=0 impostorscore=0 clxscore=1011
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2003240042
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's continue cleaning up the smp test and smp related functions.

We add:
   * Test for external/emergency calls after reset
   * Test SIGP restart while running
   * SIGP stop and store status while running
   * CR testing on reset

We fix:
   * Proper check for sigp completion
   * smp_cpu_setup_state() loop and return address in r14


GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup2


Janosch Frank (10):
  s390x: smp: Test all CRs on initial reset
  s390x: smp: Dirty fpc before initial reset test
  s390x: smp: Test stop and store status on a running and stopped cpu
  s390x: smp: Test local interrupts after cpu reset
  s390x: smp: Loop if secondary cpu returns into cpu setup again
  s390x: smp: Remove unneeded cpu loops
  s390x: smp: Use full PSW to bringup new cpu
  s390x: smp: Wait for sigp completion
  s390x: smp: Add restart when running test
  s390x: Fix library constant definitions

 lib/s390x/asm/arch_def.h |  8 ++--
 lib/s390x/smp.c          | 10 +++++
 lib/s390x/smp.h          |  1 +
 s390x/cstart64.S         |  5 ++-
 s390x/smp.c              | 84 ++++++++++++++++++++++++++++++++++++----
 5 files changed, 95 insertions(+), 13 deletions(-)
```
#### [PATCH 0/4] KVM: SVM: Move and split up svm.c
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Tue Mar 24 09:41:50 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11454915
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7182A913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 09:42:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5E5722080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 09:42:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727119AbgCXJmW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 05:42:22 -0400
Received: from 8bytes.org ([81.169.241.247]:55346 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727230AbgCXJmA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 05:42:00 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 279EF2E2; Tue, 24 Mar 2020 10:41:59 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Ashish Kalra <Ashish.Kalra@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/4] KVM: SVM: Move and split up svm.c
Date: Tue, 24 Mar 2020 10:41:50 +0100
Message-Id: <20200324094154.32352-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

here is a patch-set agains kvm/queue which moves svm.c into its own
subdirectory arch/x86/kvm/svm/ and splits moves parts of it into
separate source files:

	- The parts related to nested SVM to nested.c

	- AVIC implementation to avic.c

	- The SEV parts to sev.c

I have tested the changes in a guest with and without SEV.

Please review.

Thanks,

	Joerg

Joerg Roedel (4):
  kVM SVM: Move SVM related files to own sub-directory
  KVM: SVM: Move Nested SVM Implementation to nested.c
  KVM: SVM: Move AVIC code to separate file
  KVM: SVM: Move SEV code to separate file

 arch/x86/kvm/Makefile                 |    2 +-
 arch/x86/kvm/svm/avic.c               | 1025 ++++
 arch/x86/kvm/svm/nested.c             |  823 ++++
 arch/x86/kvm/{pmu_amd.c => svm/pmu.c} |    0
 arch/x86/kvm/svm/sev.c                | 1178 +++++
 arch/x86/kvm/{ => svm}/svm.c          | 6546 ++++++-------------------
 arch/x86/kvm/svm/svm.h                |  491 ++
 7 files changed, 5106 insertions(+), 4959 deletions(-)
 create mode 100644 arch/x86/kvm/svm/avic.c
 create mode 100644 arch/x86/kvm/svm/nested.c
 rename arch/x86/kvm/{pmu_amd.c => svm/pmu.c} (100%)
 create mode 100644 arch/x86/kvm/svm/sev.c
 rename arch/x86/kvm/{ => svm}/svm.c (56%)
 create mode 100644 arch/x86/kvm/svm/svm.h
```
#### [PATCH v2 0/7] Removing support for 32bit KVM/arm host
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Mar 24 10:33:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11455059
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B9B11731
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 10:34:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 53A20208E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 10:34:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1585046044;
	bh=bYlBEjd/f1p/2lpvFc3jhEpDR9HQLFUZ/kLJ31B5CWc=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=F9QHLmPfHa9uI3Pqy75MUnue0V2Ls5NGEPnzTtpDvB42dhGyB1cui4Xh4Jv6cGTmw
	 SPVLdN9lS9I1EI+J8GjdNk9PgzJQz7q3FTGzW6Ngd8guGKZjzCv3pF7HxrFUCFNcXc
	 kxFDqYWshFzii/bwEWZa0Xb1LQEmuyNmIU92HzgU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727163AbgCXKeC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 06:34:02 -0400
Received: from mail.kernel.org ([198.145.29.99]:55928 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727120AbgCXKeB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 06:34:01 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 4549620775;
        Tue, 24 Mar 2020 10:34:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1585046040;
        bh=bYlBEjd/f1p/2lpvFc3jhEpDR9HQLFUZ/kLJ31B5CWc=;
        h=From:To:Cc:Subject:Date:From;
        b=0RrKWVxxqJHLXM6u84gaBr9v6otD8EJJEHV2pLdXJW4KlWoISLAFAHD93FfrSI5eY
         +a19wUmSXRSfxWF0VILZPLNuekrclWG2p4pGHE/dey82+f2/S6Ax8ZVyzVv5LCTxXE
         Rs5Xr4f7CNlNaJmR6827T9uEjKOg0d4sEVtLFMW0=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jGgsg-00FE8V-FA; Tue, 24 Mar 2020 10:33:58 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Olof Johansson <olof@lixom.net>, Arnd Bergmann <arnd@arndb.de>,
        Will Deacon <will@kernel.org>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Linus Walleij <linus.walleij@linaro.org>,
        Christoffer Dall <christoffer.dall@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Quentin Perret <qperret@google.com>,
        Russell King <linux@arm.linux.org.uk>,
        Stefan Agner <stefan@agner.ch>,
        Jan Kiszka <jan.kiszka@siemens.com>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        Bartlomiej Zolnierkiewicz <b.zolnierkie@samsung.com>,
        Marek Szyprowski <m.szyprowski@samsung.com>,
        Takashi Yoshi <takashi@yoshi.email>,
        Daniel Golle <daniel@makrotopia.org>
Subject: [PATCH v2 0/7] Removing support for 32bit KVM/arm host
Date: Tue, 24 Mar 2020 10:33:43 +0000
Message-Id: <20200324103350.138077-1-maz@kernel.org>
X-Mailer: git-send-email 2.25.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, olof@lixom.net,
 arnd@arndb.de, will@kernel.org, vladimir.murzin@arm.com,
 catalin.marinas@arm.com, linus.walleij@linaro.org, christoffer.dall@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 pbonzini@redhat.com, qperret@google.com, linux@arm.linux.org.uk,
 stefan@agner.ch, jan.kiszka@siemens.com, krzk@kernel.org,
 b.zolnierkie@samsung.com, m.szyprowski@samsung.com, takashi@yoshi.email,
 daniel@makrotopia.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm was merged just over 7 years ago, and has lived a very quiet
life so far. It mostly works if you're prepared to deal with its
limitations, it has been a good prototype for the arm64 version,
but it suffers a few problems:

- It is incomplete (no debug support, no PMU)
- It hasn't followed any of the architectural evolutions
- It has zero^W very few users (I don't count myself here)
- It is more and more getting in the way of new arm64 developments

There has been quite a bit of discussion (see [1]) on whether we were
depriving users of something they were depending on. Most people
didn't object, and actually supported the removal. A few people *did*
object to the removal:

- Takashi uses it on a regular basis for developments
- Daniel uses it as well, although he doesn't depend on it
- Marek and Bartlomiej said that Samsung use it internally, without
  any description of their usage model

Alghouth I can really sympathetize with people above, I still don't
think we should keep the 32bit port artificially alive for the sake of
it, specially considering that the whole of the 32bit architecture is
in best effort, maintenance mode. I'd rather drop KVM support now,
while it is still in a decent shape, rather than seeing it bit-rot
like it happened for ia64. I also plan to keep maintaining it in the
various stable kernels, up to (and including) 5.6.

To reiterate: 32bit guest support for arm64 stays, of course. Only
32bit host goes. Once this is merged, I plan to move virt/kvm/arm to
arm64, and cleanup all the now unnecessary abstractions.

The patches have been generated with the -D option to avoid spamming
everyone with huge diffs, and there is a kvm-arm/goodbye branch in
my kernel.org repository.

* From v1:
  - Rebased on top of kvmarm/next
  - Simplified the HYP vector replacement code
  - Updated the MAINTAINERS file
  - Collected Acks

[1] https://lore.kernel.org/linux-arm-kernel/20200210141324.21090-1-maz@kernel.org/

Marc Zyngier (7):
  arm: Unplug KVM from the build system
  arm: Remove KVM from config files
  arm: Remove 32bit KVM host support
  arm: Remove HYP/Stage-2 page-table support
  arm: Remove GICv3 vgic compatibility macros
  arm: Remove the ability to set HYP vectors outside of the decompressor
  MAINTAINERS: RIP KVM/arm

 Documentation/virt/kvm/arm/hyp-abi.rst |    5 +
 MAINTAINERS                            |    5 +-
 arch/arm/Kconfig                       |    2 -
 arch/arm/Makefile                      |    1 -
 arch/arm/configs/axm55xx_defconfig     |    2 -
 arch/arm/include/asm/arch_gicv3.h      |  114 --
 arch/arm/include/asm/kvm_arm.h         |  239 ----
 arch/arm/include/asm/kvm_asm.h         |   77 --
 arch/arm/include/asm/kvm_coproc.h      |   36 -
 arch/arm/include/asm/kvm_emulate.h     |  372 ------
 arch/arm/include/asm/kvm_host.h        |  457 --------
 arch/arm/include/asm/kvm_hyp.h         |  127 ---
 arch/arm/include/asm/kvm_mmu.h         |  435 -------
 arch/arm/include/asm/kvm_ras.h         |   14 -
 arch/arm/include/asm/pgtable-3level.h  |   20 -
 arch/arm/include/asm/pgtable.h         |    9 -
 arch/arm/include/asm/sections.h        |    6 +-
 arch/arm/include/asm/stage2_pgtable.h  |   75 --
 arch/arm/include/asm/virt.h            |   17 -
 arch/arm/include/uapi/asm/kvm.h        |  314 -----
 arch/arm/kernel/asm-offsets.c          |   11 -
 arch/arm/kernel/hyp-stub.S             |   39 +-
 arch/arm/kernel/vmlinux-xip.lds.S      |    8 -
 arch/arm/kernel/vmlinux.lds.S          |    8 -
 arch/arm/kernel/vmlinux.lds.h          |   10 -
 arch/arm/kvm/Kconfig                   |   59 -
 arch/arm/kvm/Makefile                  |   43 -
 arch/arm/kvm/coproc.c                  | 1455 ------------------------
 arch/arm/kvm/coproc.h                  |  130 ---
 arch/arm/kvm/coproc_a15.c              |   39 -
 arch/arm/kvm/coproc_a7.c               |   42 -
 arch/arm/kvm/emulate.c                 |  166 ---
 arch/arm/kvm/guest.c                   |  387 -------
 arch/arm/kvm/handle_exit.c             |  175 ---
 arch/arm/kvm/hyp/Makefile              |   34 -
 arch/arm/kvm/hyp/banked-sr.c           |   70 --
 arch/arm/kvm/hyp/cp15-sr.c             |   72 --
 arch/arm/kvm/hyp/entry.S               |  121 --
 arch/arm/kvm/hyp/hyp-entry.S           |  295 -----
 arch/arm/kvm/hyp/s2-setup.c            |   22 -
 arch/arm/kvm/hyp/switch.c              |  242 ----
 arch/arm/kvm/hyp/tlb.c                 |   68 --
 arch/arm/kvm/hyp/vfp.S                 |   57 -
 arch/arm/kvm/init.S                    |  157 ---
 arch/arm/kvm/interrupts.S              |   36 -
 arch/arm/kvm/irq.h                     |   16 -
 arch/arm/kvm/reset.c                   |   86 --
 arch/arm/kvm/trace.h                   |   86 --
 arch/arm/kvm/vgic-v3-coproc.c          |   27 -
 arch/arm/mach-exynos/Kconfig           |    2 +-
 arch/arm/mm/mmu.c                      |   26 -
 51 files changed, 16 insertions(+), 6300 deletions(-)
 delete mode 100644 arch/arm/include/asm/kvm_arm.h
 delete mode 100644 arch/arm/include/asm/kvm_asm.h
 delete mode 100644 arch/arm/include/asm/kvm_coproc.h
 delete mode 100644 arch/arm/include/asm/kvm_emulate.h
 delete mode 100644 arch/arm/include/asm/kvm_host.h
 delete mode 100644 arch/arm/include/asm/kvm_hyp.h
 delete mode 100644 arch/arm/include/asm/kvm_mmu.h
 delete mode 100644 arch/arm/include/asm/kvm_ras.h
 delete mode 100644 arch/arm/include/asm/stage2_pgtable.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm.h
 delete mode 100644 arch/arm/kvm/Kconfig
 delete mode 100644 arch/arm/kvm/Makefile
 delete mode 100644 arch/arm/kvm/coproc.c
 delete mode 100644 arch/arm/kvm/coproc.h
 delete mode 100644 arch/arm/kvm/coproc_a15.c
 delete mode 100644 arch/arm/kvm/coproc_a7.c
 delete mode 100644 arch/arm/kvm/emulate.c
 delete mode 100644 arch/arm/kvm/guest.c
 delete mode 100644 arch/arm/kvm/handle_exit.c
 delete mode 100644 arch/arm/kvm/hyp/Makefile
 delete mode 100644 arch/arm/kvm/hyp/banked-sr.c
 delete mode 100644 arch/arm/kvm/hyp/cp15-sr.c
 delete mode 100644 arch/arm/kvm/hyp/entry.S
 delete mode 100644 arch/arm/kvm/hyp/hyp-entry.S
 delete mode 100644 arch/arm/kvm/hyp/s2-setup.c
 delete mode 100644 arch/arm/kvm/hyp/switch.c
 delete mode 100644 arch/arm/kvm/hyp/tlb.c
 delete mode 100644 arch/arm/kvm/hyp/vfp.S
 delete mode 100644 arch/arm/kvm/init.S
 delete mode 100644 arch/arm/kvm/interrupts.S
 delete mode 100644 arch/arm/kvm/irq.h
 delete mode 100644 arch/arm/kvm/reset.c
 delete mode 100644 arch/arm/kvm/trace.h
 delete mode 100644 arch/arm/kvm/vgic-v3-coproc.c
```
#### [PATCH 0/2] kvm-unit-tests: s390x MAINTAINERS tweaks
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From patchwork Tue Mar 24 12:17:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11455245
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DE3881392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:17:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BC4912080C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 12:17:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i9pZMveu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727348AbgCXMRd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 08:17:33 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:20317 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726968AbgCXMRc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Mar 2020 08:17:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585052252;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Fg2iU+81quK5qxNBft0sGOHtSxcJKoYxa8Ig+wK5Urk=;
        b=i9pZMveuUGkrcDeZ4a8rPv8WrudXQfEioajfzwM94drqz+3QT6zsqwqeUC3mcymP6LS+E0
        OFYU6LC30hU9BTBXsfwiIqWIE47d0SiNH1NvMzgVyaI7ewy/xj9MrckX0BIPIxaW8to38J
        yM3cMG/Umjdrr1e9zMIgSSo8hyTlJgU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-214-UoKbQMhiMJup6yE5wdbYqg-1; Tue, 24 Mar 2020 08:17:30 -0400
X-MC-Unique: UoKbQMhiMJup6yE5wdbYqg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 9126A800D50;
        Tue, 24 Mar 2020 12:17:29 +0000 (UTC)
Received: from localhost (ovpn-113-109.ams2.redhat.com [10.36.113.109])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 574335C290;
        Tue, 24 Mar 2020 12:17:26 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, Thomas Huth <thuth@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH 0/2] kvm-unit-tests: s390x MAINTAINERS tweaks
Date: Tue, 24 Mar 2020 13:17:20 +0100
Message-Id: <20200324121722.9776-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I'm trying to review s390x patches, so let's reflect that.
Also, it makes sense to cc: linux-s390 on s390x patches, I guess.

Cornelia Huck (2):
  s390x: add myself as reviewer
  s390x: add linux-s390 list

 MAINTAINERS | 2 ++
 1 file changed, 2 insertions(+)
```
#### [PATCH v6 0/8] x86/split_lock: Fix and virtualization of split lock
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Tue Mar 24 15:18:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11455791
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AF7A6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 15:37:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 42ADC20788
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 15:37:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728413AbgCXPhH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 11:37:07 -0400
Received: from mga05.intel.com ([192.55.52.43]:40198 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727980AbgCXPhF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 11:37:05 -0400
IronPort-SDR: 
 LLb5cSzLtWtvLZow8PQek16+ibtPBzmxOii4zVNpooSmTneWwN8ZbvO6xfms3Mb63Gd0Sl/iFA
 oJUuF1fBbo8Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Mar 2020 08:37:04 -0700
IronPort-SDR: 
 NW2j/PrriTw0QlQ/+lOlMn8Y1tzc6CVzaVQ2I5jYpByXrkvlhmdgGeOmwndNm65ka8Q/KZQbNV
 jugDFZwqC/0w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,300,1580803200";
   d="scan'208";a="393319653"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by orsmga004.jf.intel.com with ESMTP; 24 Mar 2020 08:37:00 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        hpa@zytor.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Tony Luck <tony.luck@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v6 0/8] x86/split_lock: Fix and virtualization of split lock
 detection
Date: Tue, 24 Mar 2020 23:18:51 +0800
Message-Id: <20200324151859.31068-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So sorry for the noise that I forgot to CC the maillist.

This series aims to add the virtualization of split lock detection for
guest, while containing some fixes of native kernel split lock handling. 

Note, this series is based on the kernel patch[1]. Patch 1-3 are x86
kernel patches that based on the linux/master branch. Patch 4-8 are kvm
patches that based on the kvm/queue branch.

Patch 1 is the fix and enhancement for kernel split lock detction. It
ensures X86_FEATURE_SPLIT_LOCK_DETECT flag is set only when feature does
exist and not disabled on kernel params. And it explicitly turn off split
lock when sld_off instead of assuming BIOS/firmware leaves it cleared.

Patch 2 optimizes the runtime MSR accessing.

Patch 3 are the preparation for enabling split lock detection
virtualization in KVM.

Patch 4 fixes the issue that malicious guest may exploit kvm emulator to
attcact host kernel.

Patch 5 handles guest's split lock when host turns split lock detect on.

Patch 6-8 implement the virtualization of split lock detection in kvm.

[1]: https://lore.kernel.org/lkml/158031147976.396.8941798847364718785.tip-bot2@tip-bot2/ 

Changes in v6:
 - Drop the sld_not_exist flag and use X86_FEATURE_SPLIT_LOCK_DETECT to
   check whether need to init split lock detection. [tglx]
 - Use tglx's method to verify the existence of split lock detectoin.
 - small optimization of sld_update_msr() that the default value of
   msr_test_ctrl_cache has split_lock_detect bit cleared.
 - Drop the patch3 in v5 that introducing kvm_only option. [tglx]
 - Rebase patch4-8 to kvm/queue.
 - use the new kvm-cpu-cap to expose X86_FEATURE_CORE_CAPABILITIES in
   Patch 6.

Changes in v5:
 - Use X86_FEATURE_SPLIT_LOCK_DETECT flag in kvm to ensure split lock
   detection is really supported.
 - Add and export sld related helper functions in their related usecase 
   kvm patches.

Changes in v4:
 - Add patch 1 to rework the initialization flow of split lock
   detection.
 - Drop percpu MSR_TEST_CTRL cache, just use a static variable to cache
   the reserved/unused bit of MSR_TEST_CTRL. [Sean]
 - Add new option for split_lock_detect kernel param.
 - Changlog refinement. [Sean]
 - Add a new patch to enable MSR_TEST_CTRL for intel guest. [Sean]

Xiaoyao Li (8):
  x86/split_lock: Rework the initialization flow of split lock detection
  x86/split_lock: Avoid runtime reads of the TEST_CTRL MSR
  x86/split_lock: Export handle_user_split_lock()
  kvm: x86: Emulate split-lock access as a write in emulator
  kvm: vmx: Extend VMX's #AC interceptor to handle split lock #AC
    happens in guest
  kvm: x86: Emulate MSR IA32_CORE_CAPABILITIES
  kvm: vmx: Enable MSR_TEST_CTRL for intel guest
  kvm: vmx: virtualize split lock detection

 arch/x86/include/asm/cpu.h      |  21 +++++-
 arch/x86/include/asm/kvm_host.h |   1 +
 arch/x86/kernel/cpu/intel.c     | 114 +++++++++++++++++++-------------
 arch/x86/kernel/traps.c         |   2 +-
 arch/x86/kvm/cpuid.c            |   1 +
 arch/x86/kvm/vmx/vmx.c          |  75 ++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.h          |   1 +
 arch/x86/kvm/x86.c              |  42 +++++++++++-
 8 files changed, 203 insertions(+), 54 deletions(-)
```
#### [PATCH v16 Kernel 0/7] KABIs to support migration for VFIO devices
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Tue Mar 24 19:32:32 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11456263
Return-Path: <SRS0=keX+=5J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 582F1139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 20:06:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 31C8C205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 24 Mar 2020 20:06:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="IkcnvMda"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726034AbgCXUGJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 24 Mar 2020 16:06:09 -0400
Received: from hqnvemgate26.nvidia.com ([216.228.121.65]:18871 "EHLO
        hqnvemgate26.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725927AbgCXUGJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Mar 2020 16:06:09 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate26.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5e7a68220000>; Tue, 24 Mar 2020 13:05:54 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Tue, 24 Mar 2020 13:06:07 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Tue, 24 Mar 2020 13:06:07 -0700
Received: from HQMAIL107.nvidia.com (172.20.187.13) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 24 Mar
 2020 20:06:07 +0000
Received: from kwankhede-dev.nvidia.com (172.20.13.39) by HQMAIL107.nvidia.com
 (172.20.187.13) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 24 Mar 2020 20:06:01 +0000
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
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH v16 Kernel 0/7] KABIs to support migration for VFIO devices
Date: Wed, 25 Mar 2020 01:02:32 +0530
Message-ID: <1585078359-20124-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1585080354; bh=Z2j+6gx1dsfGmQOm+VWO6MwVPydfmL204YqWASsyX9s=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=IkcnvMdaw/wLfFAcVde+tdG/OUzRlNCuGMyVQ4lMaPypvAB/h7ElumQ5D0giLUbeb
         5EojZ9TrWNSR8BEDtVERnipX5sjIMm/GgHMPKd+B899G5BIJhOpMmr2JHJyqjuw9+F
         roUXEk6s1OCXmobItd3kPoC1nkLKWaywmfnaf8420uKO5o5nZHqVSLwoUsu6FRyJ44
         5ttQ0hMraH3KEum3aKfSPHFXr3OG8RctJL7Yjn0Uo8Waqa+8LS8Bc9iIVzp6CIt6YQ
         ci8ChrfiVZ55w3l/MwGv4yNP7J+HF6It5d1AEl7Ei70EyZRCOo8tw8pIhY4yQbABvc
         u7+HKkz/WeRHg==
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

v15 -> v16
- Minor edits and nit picks (Auger Eric)
- On copying bitmap to user, re-populated bitmap only for pinned pages,
  excluding unmapped pages and CPU dirtied pages.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

v14 -> v15
- Minor edits and nit picks.
- In the verification of user allocated bitmap memory, added check of
   maximum size.
- Patches are on tag: next-20200318 and 1-3 patches from Yan's series
  https://lkml.org/lkml/2020/3/12/1255

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
 drivers/vfio/vfio_iommu_type1.c | 421 ++++++++++++++++++++++++++++++++++++++--
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 299 +++++++++++++++++++++++++++-
 4 files changed, 715 insertions(+), 22 deletions(-)
```
