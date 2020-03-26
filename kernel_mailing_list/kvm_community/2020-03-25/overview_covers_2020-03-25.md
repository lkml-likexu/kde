

#### [PATCH 0/3] KVM: arm64: Some optimizations about enabling dirty log
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Wed Mar 25 04:24:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11456925
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CBA2F1667
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 04:26:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AAA5820714
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 04:26:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726065AbgCYE0m (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 00:26:42 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:12124 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725781AbgCYE0m (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 00:26:42 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id EBDB983B08E26A5DEBB8;
        Wed, 25 Mar 2020 12:26:38 +0800 (CST)
Received: from linux-kDCJWP.huawei.com (10.175.104.212) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.487.0; Wed, 25 Mar 2020 12:26:28 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: Marc Zyngier <maz@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>,
        "James Morse" <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Will Deacon <will@kernel.org>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jay Zhou <jianjay.zhou@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH 0/3] KVM: arm64: Some optimizations about enabling dirty log
Date: Wed, 25 Mar 2020 12:24:20 +0800
Message-ID: <20200325042423.12181-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
X-Originating-IP: [10.175.104.212]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series is for "queue" branch of [1] and based on patches[2].
It brings obvious time decreasement for migration with different page
size.

The QEMU counterpart will be sent out later, thanks.

[1] git://git.kernel.org/pub/scm/virt/kvm/kvm.git
[2] https://lore.kernel.org/kvm/20200227013227.1401-1-jianjay.zhou@huawei.com/

Keqian Zhu (3):
  KVM/memslot: Move the initial set of dirty bitmap to arch
  KVM/arm64: Support enabling dirty log graually in small chunks
  KVM/arm64: Only set bits of dirty bitmap with valid translation
    entries

 Documentation/virt/kvm/api.rst    |   2 +-
 arch/arm/include/asm/kvm_host.h   |   2 -
 arch/arm64/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/x86.c                |   3 +
 virt/kvm/arm/mmu.c                | 175 +++++++++++++++++++++++++-----
 virt/kvm/kvm_main.c               |   3 -
 6 files changed, 157 insertions(+), 33 deletions(-)
```
#### [PATCH V8 0/9] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Wed Mar 25 08:27:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11457159
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0BC4F1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 08:28:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CE17B2070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 08:28:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DgSLI2gD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726842AbgCYI21 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 04:28:27 -0400
Received: from us-smtp-delivery-74.mimecast.com ([63.128.21.74]:42392 "EHLO
        us-smtp-delivery-74.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725903AbgCYI21 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 25 Mar 2020 04:28:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1585124905;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=TFygb80jlF4QeDh0UcQJf4z7lxP0GjHs8oBGU5kZ/LY=;
        b=DgSLI2gD92rAher9NpkjKhTFLxQxip5kSW+2Iax8ugH9F3P+k+fkFkdC3G8DnaGkhnpaV7
        Ye7EMJRZVAa5NdoKSwceZalwcfDjMTyCZe+y81yVZ6y3rzoFNuXsqxaNWVmRGPbRQMgjtJ
        33KLuzaCaNXqutvz1gj3FiLL3ag5GaM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-398--wrucZ-_OuGjWFyt-5Vxzw-1; Wed, 25 Mar 2020 04:28:08 -0400
X-MC-Unique: -wrucZ-_OuGjWFyt-5Vxzw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E2AFC1902EA2;
        Wed, 25 Mar 2020 08:28:05 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-14-13.pek2.redhat.com [10.72.14.13])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C0023CFC5;
        Wed, 25 Mar 2020 08:27:20 +0000 (UTC)
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
Subject: [PATCH V8 0/9] vDPA support
Date: Wed, 25 Mar 2020 16:27:02 +0800
Message-Id: <20200325082711.1107-1-jasowang@redhat.com>
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

Changes from V7:

- refine kconfig to solve the dependency issues on archs that lacks of
  CONFIG_VIRTUALIZATION (kbuild)

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

V7: https://lkml.org/lkml/2020/3/24/21
V6: https://lkml.org/lkml/2020/3/18/88
V5: https://lkml.org/lkml/2020/2/26/58
V4: https://lkml.org/lkml/2020/2/20/59
V3: https://lkml.org/lkml/2020/2/19/1347
V2: https://lkml.org/lkml/2020/2/9/275
V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (7):
  vhost: refine vhost and vringh kconfig
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
 arch/arm/kvm/Kconfig                    |   2 -
 arch/arm64/kvm/Kconfig                  |   2 -
 arch/mips/kvm/Kconfig                   |   2 -
 arch/powerpc/kvm/Kconfig                |   2 -
 arch/s390/kvm/Kconfig                   |   4 -
 arch/x86/kvm/Kconfig                    |   4 -
 drivers/Kconfig                         |   2 +
 drivers/misc/mic/Kconfig                |   4 -
 drivers/net/caif/Kconfig                |   4 -
 drivers/vhost/Kconfig                   |  42 +-
 drivers/vhost/Kconfig.vringh            |   6 -
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
 drivers/virtio/vdpa/Kconfig             |  37 +
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
 38 files changed, 4224 insertions(+), 248 deletions(-)
 delete mode 100644 drivers/vhost/Kconfig.vringh
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
#### [PATCH v2 0/6] Fix errors when try to build kvm selftests on
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Wed Mar 25 14:01:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11457971
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8720C139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 14:19:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 67656215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 14:19:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727647AbgCYOTL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 10:19:11 -0400
Received: from mga04.intel.com ([192.55.52.120]:42324 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727549AbgCYOTK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 10:19:10 -0400
IronPort-SDR: 
 vCZkbwfm1OYWK4CBuTCsjI40i8ujIwCA4UpbwjtOfGh/9VcZ+wjjYtvCxGMr5otFDZucngBZdx
 tbxwnu59fqfw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 Mar 2020 07:19:10 -0700
IronPort-SDR: 
 4j5oJBDaQj2KzJ63xjdYy/OcamE8di33XJj7oIvv1g7nyN7ulox6D2Kwj7ntvS4qQBbqzX6vbQ
 QM7tIkCXSlnQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,304,1580803200";
   d="scan'208";a="270811071"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.39])
  by fmsmga004.fm.intel.com with ESMTP; 25 Mar 2020 07:19:08 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Shuah Khan <shuah@kernel.org>, Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kselftest@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v2 0/6] Fix errors when try to build kvm selftests on
 specified output
Date: Wed, 25 Mar 2020 22:01:27 +0800
Message-Id: <20200325140133.103236-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I attempted to build KVM selftests on a specified dir, unfortunately
neither	"make O=/path/to/mydir TARGETS=kvm" in tools/testing/selftests, nor
"make OUTPUT=/path/to/mydir" in tools/testing/selftests/kvm work.

This series aims to fix them.

Patch 1 fixes the issue that output directory is not exist.

Patch 2 and 3 are the preparation for kvm to get the right path of
installed linux headers.

Patch 4 and 6 prepare the INSTALL_HDR_PATH to tell sub TARGET where the
linux headers are installed.

Patch 5 fixes the issue that with OUTPUT specified, it still make the
linux tree dirty.

I only test the sub TARGET of kvm.
In theory, it won't break other TARGET of selftests.

Changes in v2:
 - fix the no directory issue in lib.mk
 - make kvm fixes seperate patch
 - Add the patch to fix linux src tree not clean issue

v1:
https://lore.kernel.org/kvm/20200315093425.33600-1-xiaoyao.li@intel.com/

Xiaoyao Li (6):
  selftests: Create directory when OUTPUT specified
  selftests: kvm: Include lib.mk earlier
  selftests: kvm: Use the default linux header path only when
    INSTALL_HDR_PATH not defined
  selftests: Create variable INSTALL_HDR_PATH if need to install linux
    headers to $(OUTPUT)/usr
  selftests: Generate build output of linux headers to
    $(OUTPUT)/linux-header-build
  selftests: export INSTALL_HDR_PATH if using "O" to specify output dir

 tools/testing/selftests/Makefile     |  6 +++++-
 tools/testing/selftests/kvm/Makefile |  9 +++++----
 tools/testing/selftests/lib.mk       | 19 ++++++++++++++++++-
 3 files changed, 28 insertions(+), 6 deletions(-)
```
#### [PATCH v2 0/3] SELinux support for anonymous inodes and UFFD
##### From: Daniel Colascione <dancol@google.com>

```c
From patchwork Wed Mar 25 23:02:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Colascione <dancol@google.com>
X-Patchwork-Id: 11458867
Return-Path: <SRS0=cO5m=5K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 553CD17D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:02:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35E302076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 25 Mar 2020 23:02:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="pErYkr8S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727456AbgCYXCz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 25 Mar 2020 19:02:55 -0400
Received: from mail-pj1-f74.google.com ([209.85.216.74]:34411 "EHLO
        mail-pj1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727389AbgCYXCz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 25 Mar 2020 19:02:55 -0400
Received: by mail-pj1-f74.google.com with SMTP id v8so4708558pju.1
        for <kvm@vger.kernel.org>; Wed, 25 Mar 2020 16:02:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=bbByUOh82ool+SbMsA1rd5UPSytjb2ekUWaOBWg/qH4=;
        b=pErYkr8SQ3js+o0QvaCZ2l96awDpkh8EUrjdNxFzM5tLCD4mbraW9JddFtQK0HyshT
         Avi04q5RiTad5YbeGKaK3qQDIhPmHtahpbjhp5ypqqp+ISs/DtHKySkISX00+naohPBc
         fD3TM90efw7F9/2EnWg7pGK8DCYDlEqC0oNDigZIPpWkrmi6AIFt6BNa1XFMFl7CJiAV
         hOVMaSzmXzi4wiklS783i7sQOVKxezXdi9uI4PDANgNCZwRz2ZppnvtKA8qRImOl3799
         C2kTOSxfz7k/WCYqwqQHvko0fPJ2rYwW0Ofl7E40p6/OWTpnb50TopRg525DkYJy2QEP
         maug==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=bbByUOh82ool+SbMsA1rd5UPSytjb2ekUWaOBWg/qH4=;
        b=l+JHB6Ko/xSWSBIHc40zivlaWq5eCvz4nYUYiE9gbhSoldXLFXCfDQzMU6o2bupwCS
         36wmjL4CgKCZSlYdp4F34OeXKj7TLrkj6eoHjn5G3TsvetX4zq1gtSSHPsoJW77l3KZ4
         zcPVS5TsktGLTllgQvnhYyreWDMInzAQjQnlx5t+F1Jlp01GcRSRx7xABVNoKGaB7kxM
         DJWY4Fuu6KIiq34RhI+w83rH0eH7939UsuxA1KT9Tij90nuikoP4OqGLIP0pzSnhp67g
         saT3N1viQxGlQ606quRM0WldfoaaZtj0a0xprs3x0hAkRt3CgjYlcd8nx3lQQ2LQ9OgH
         Xfjw==
X-Gm-Message-State: ANhLgQ3AaYphr32r78+qpXjP/Oz9NKtm0aeGmR/xgI2qm0pGzZ0bnHbz
        CEoTD15Y9UCcHxgvb3BZmZ4Lmz5pIYY=
X-Google-Smtp-Source: 
 ADFU+vtou3JvMD6bdJEzfSY7dZ8y8OPdFIieV20IdIhHvT/Kq/C6dfCeM9T+fChX6v9277hrJ2rP5pCwomI=
X-Received: by 2002:a17:90a:a484:: with SMTP id
 z4mr6308167pjp.77.1585177373743;
 Wed, 25 Mar 2020 16:02:53 -0700 (PDT)
Date: Wed, 25 Mar 2020 16:02:43 -0700
In-Reply-To: <20200214032635.75434-1-dancol@google.com>
Message-Id: <20200325230245.184786-1-dancol@google.com>
Mime-Version: 1.0
References: <20200214032635.75434-1-dancol@google.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH v2 0/3] SELinux support for anonymous inodes and UFFD
From: Daniel Colascione <dancol@google.com>
To: timmurray@google.com, selinux@vger.kernel.org,
        linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, viro@zeniv.linux.org.uk, paul@paul-moore.com,
        nnk@google.com, sds@tycho.nsa.gov, lokeshgidra@google.com
Cc: Daniel Colascione <dancol@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Userfaultfd in unprivileged contexts could be potentially very
useful. We'd like to harden userfaultfd to make such unprivileged use
less risky. This patch series allows SELinux to manage userfaultfd
file descriptors and in the future, other kinds of
anonymous-inode-based file descriptor.  SELinux policy authors can
apply policy types to anonymous inodes by providing name-based
transition rules keyed off the anonymous inode internal name (
"[userfaultfd]" in the case of userfaultfd(2) file descriptors) and
applying policy to the new SIDs thus produced.

Inside the kernel, a pair of new anon_inodes interface,
anon_inode_getfile_secure and anon_inode_getfd_secure, allow callers
to opt into this SELinux management. In this new "secure" mode,
anon_inodes creates new ephemeral inodes for anonymous file objects
instead of reusing the normal anon_inodes singleton dummy inode. A new
LSM hook gives security modules an opportunity to configure and veto
these ephemeral inodes.

This patch series is one of two fork of [1] and is an
alternative to [2].

The primary difference between the two patch series is that this
partch series creates a unique inode for each "secure" anonymous
inode, while the other patch series ([2]) continues using the
singleton dummy anonymous inode and adds a way to attach SELinux
security information directly to file objects.

I prefer the approach in this patch series because 1) it's a smaller
patch than [2], and 2) it produces a more regular security
architecture: in this patch series, secure anonymous inodes aren't
S_PRIVATE and they maintain the SELinux property that the label for a
file is in its inode. We do need an additional inode per anonymous
file, but per-struct-file inode creation doesn't seem to be a problem
for pipes and sockets.

The previous version of this feature ([1]) created a new SELinux
security class for userfaultfd file descriptors. This version adopts
the generic transition-based approach of [2].

This patch series also differs from [2] in that it doesn't affect all
anonymous inodes right away --- instead requiring anon_inodes callers
to opt in --- but this difference isn't one of basic approach. The
important question to resolve is whether we should be creating new
inodes or enhancing per-file data.

Changes from the first version of the patch:

  - Removed some error checks
  - Defined a new anon_inode SELinux class to resolve the
    ambiguity in [3]
  - Inherit sclass as well as descriptor from context inode

[1] https://lore.kernel.org/lkml/20200211225547.235083-1-dancol@google.com/
[2] https://lore.kernel.org/linux-fsdevel/20200213194157.5877-1-sds@tycho.nsa.gov/
[3] https://lore.kernel.org/lkml/23f725ca-5b5a-5938-fcc8-5bbbfc9ba9bc@tycho.nsa.gov/

Daniel Colascione (3):
  Add a new LSM-supporting anonymous inode interface
  Teach SELinux about anonymous inodes
  Wire UFFD up to SELinux

 fs/anon_inodes.c                    | 196 ++++++++++++++++++++++------
 fs/userfaultfd.c                    |  30 ++++-
 include/linux/anon_inodes.h         |  13 ++
 include/linux/lsm_hooks.h           |   9 ++
 include/linux/security.h            |   4 +
 security/security.c                 |  10 ++
 security/selinux/hooks.c            |  54 ++++++++
 security/selinux/include/classmap.h |   2 +
 8 files changed, 272 insertions(+), 46 deletions(-)
```
