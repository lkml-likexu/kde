

#### [RFC PATCH 0/4] Use 1st-level for DMA remapping in guest
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Mon Sep 23 12:24:50 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11156699
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E35B13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 12:27:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EA53720882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 12:27:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732274AbfIWM1U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 08:27:20 -0400
Received: from mga06.intel.com ([134.134.136.31]:4334 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730399AbfIWM1U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 08:27:20 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Sep 2019 05:27:19 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,539,1559545200";
   d="scan'208";a="203116655"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2019 05:27:16 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [RFC PATCH 0/4] Use 1st-level for DMA remapping in guest
Date: Mon, 23 Sep 2019 20:24:50 +0800
Message-Id: <20190923122454.9888-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset aims to move IOVA (I/O Virtual Address) translation
to 1st-level page table under scalable mode. The major purpose of
this effort is to make guest IOVA support more efficient.

As Intel VT-d architecture offers caching-mode, guest IOVA (GIOVA)
support is now implemented in a shadow page manner. The device
simulation software, like QEMU, has to figure out GIOVA->GPA mapping
and writes to a shadowed page table, which will be used by pIOMMU.
Each time when mappings are created or destroyed in vIOMMU, the
simulation software will intervene. The change on GIOVA->GPA will be
shadowed to host, and the pIOMMU will be updated via VFIO/IOMMU
interfaces.


     .-----------.
     |  vIOMMU   |
     |-----------|                 .--------------------.
     |           |IOTLB flush trap |        QEMU        |
     .-----------. (map/unmap)     |--------------------|
     | GVA->GPA  |---------------->|      .----------.  |
     '-----------'                 |      | GPA->HPA |  |
     |           |                 |      '----------'  |
     '-----------'                 |                    |
                                   |                    |
                                   '--------------------'
                                                |
            <------------------------------------
            |
            v VFIO/IOMMU API
      .-----------.
      |  pIOMMU   |
      |-----------|
      |           |
      .-----------.
      | GVA->HPA  |
      '-----------'
      |           |
      '-----------'

In VT-d 3.0, scalable mode is introduced, which offers two level
translation page tables and nested translation mode. Regards to
GIOVA support, it can be simplified by 1) moving the GIOVA support
over 1st-level page table to store GIOVA->GPA mapping in vIOMMU,
2) binding vIOMMU 1st level page table to the pIOMMU, 3) using pIOMMU
second level for GPA->HPA translation, and 4) enable nested (a.k.a.
dual stage) translation in host. Compared with current shadow GIOVA
support, the new approach is more secure and software is simplified
as we only need to flush the pIOMMU IOTLB and possible device-IOTLB
when an IOVA mapping in vIOMMU is torn down.

     .-----------.
     |  vIOMMU   |
     |-----------|                 .-----------.
     |           |IOTLB flush trap |   QEMU    |
     .-----------.    (unmap)      |-----------|
     | GVA->GPA  |---------------->|           |
     '-----------'                 '-----------'
     |           |                       |
     '-----------'                       |
           <------------------------------
           |      VFIO/IOMMU          
           |  cache invalidation and  
           | guest gpd bind interfaces
           v
     .-----------.
     |  pIOMMU   |
     |-----------|
     .-----------.
     | GVA->GPA  |<---First level
     '-----------'
     | GPA->HPA  |<---Scond level
     '-----------'
     '-----------'

This patch series only aims to achieve the first goal, a.k.a using
first level translation for IOVA mappings in vIOMMU. I am sending
it out for your comments. Any comments, suggestions and concerns are
welcomed.

Based-on-idea-by: Ashok Raj <ashok.raj@intel.com>
Based-on-idea-by: Kevin Tian <kevin.tian@intel.com>
Based-on-idea-by: Liu Yi L <yi.l.liu@intel.com>
Based-on-idea-by: Lu Baolu <baolu.lu@linux.intel.com>
Based-on-idea-by: Sanjay Kumar <sanjay.k.kumar@intel.com>

Lu Baolu (4):
  iommu/vt-d: Move domain_flush_cache helper into header
  iommu/vt-d: Add first level page table interfaces
  iommu/vt-d: Map/unmap domain with mmmap/mmunmap
  iommu/vt-d: Identify domains using first level page table

 drivers/iommu/Makefile             |   2 +-
 drivers/iommu/intel-iommu.c        | 142 ++++++++++--
 drivers/iommu/intel-pgtable.c      | 342 +++++++++++++++++++++++++++++
 include/linux/intel-iommu.h        |  31 ++-
 include/trace/events/intel_iommu.h |  60 +++++
 5 files changed, 553 insertions(+), 24 deletions(-)
 create mode 100644 drivers/iommu/intel-pgtable.c
```
#### [PATCH 0/6] mdev based hardware virtio offloading support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Mon Sep 23 13:03:25 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11156839
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BF27B17EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:04:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7A3C20882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:04:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395003AbfIWND6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 09:03:58 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55096 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390719AbfIWND5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 09:03:57 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 91A0310DCC84;
        Mon, 23 Sep 2019 13:03:56 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-93.pek2.redhat.com [10.72.12.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B17CD10013D9;
        Mon, 23 Sep 2019 13:03:33 +0000 (UTC)
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
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH 0/6] mdev based hardware virtio offloading support
Date: Mon, 23 Sep 2019 21:03:25 +0800
Message-Id: <20190923130331.29324-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.64]);
 Mon, 23 Sep 2019 13:03:57 +0000 (UTC)
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

Though the series only contains kernel driver support, the goal is to
make the transport generic enough to support userspace drivers. This
means vhost-mdev[1] could be built on top as well by resuing the
transport.

A sample driver is also implemented which simulate a virito-net
loopback ethernet device on top of vringh + workqueue. This could be
used as a reference implementation for real hardware driver.

Consider mdev framework only support VFIO device and driver right now,
this series also extend it to support other types. This is done
through introducing class id to the device and pairing it with
id_talbe claimed by the driver. On top, this seris also decouple
device specific parents ops out of the common ones.

Pktgen test was done with virito-net + mvnet loop back device.

Please review.

[1] https://lkml.org/lkml/2019/9/16/869

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
  mdev: introduce device specific ops
  mdev: introduce virtio device and its device ops
  virtio: introduce a mdev based transport
  vringh: fix copy direction of vringh_iov_push_kern()
  docs: sample driver to demonstrate how to implement virtio-mdev
    framework

 .../driver-api/vfio-mediated-device.rst       |  11 +-
 MAINTAINERS                                   |   3 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  17 +-
 drivers/s390/cio/vfio_ccw_ops.c               |  17 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  14 +-
 drivers/vfio/mdev/Kconfig                     |   7 +
 drivers/vfio/mdev/Makefile                    |   1 +
 drivers/vfio/mdev/mdev_core.c                 |  21 +-
 drivers/vfio/mdev/mdev_driver.c               |  14 +
 drivers/vfio/mdev/mdev_private.h              |   1 +
 drivers/vfio/mdev/vfio_mdev.c                 |  37 +-
 drivers/vfio/mdev/virtio_mdev.c               | 416 +++++++++++
 drivers/vhost/vringh.c                        |   8 +-
 include/linux/mdev.h                          |  47 +-
 include/linux/mod_devicetable.h               |   8 +
 include/linux/vfio_mdev.h                     |  53 ++
 include/linux/virtio_mdev.h                   | 144 ++++
 samples/Kconfig                               |   7 +
 samples/vfio-mdev/Makefile                    |   1 +
 samples/vfio-mdev/mbochs.c                    |  19 +-
 samples/vfio-mdev/mdpy.c                      |  19 +-
 samples/vfio-mdev/mtty.c                      |  17 +-
 samples/vfio-mdev/mvnet.c                     | 688 ++++++++++++++++++
 23 files changed, 1481 insertions(+), 89 deletions(-)
 create mode 100644 drivers/vfio/mdev/virtio_mdev.c
 create mode 100644 include/linux/vfio_mdev.h
 create mode 100644 include/linux/virtio_mdev.h
 create mode 100644 samples/vfio-mdev/mvnet.c
Acked-by: Michael S. Tsirkin <mst@redhat.com>
```
#### [PATCH kvmtool 00/16] arm: Allow the user to define the memory layout
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Mon Sep 23 13:35:06 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11156911
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B141476
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:35:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A2C9214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:35:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408094AbfIWNfh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 09:35:37 -0400
Received: from foss.arm.com ([217.140.110.172]:42276 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404581AbfIWNfh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 09:35:37 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id BCA021000;
        Mon, 23 Sep 2019 06:35:36 -0700 (PDT)
Received: from e121566-lin.cambridge.arm.com (e121566-lin.cambridge.arm.com
 [10.1.196.217])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 B7E4A3F694;
        Mon, 23 Sep 2019 06:35:35 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, will@kernel.org, julien.thierry.kdev@gmail.com
Cc: maz@kernel.org, suzuki.poulose@arm.com, julien.grall@arm.com,
        andre.przywara@arm.com
Subject: [PATCH kvmtool 00/16] arm: Allow the user to define the memory layout
Date: Mon, 23 Sep 2019 14:35:06 +0100
Message-Id: <1569245722-23375-1-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest memory layout created by kvmtool is fixed: regular MMIO is below
1G, PCI MMIO is below 2G, and the RAM always starts at the 2G mark. Real
hardware can have a different memory layout, and being able to create a
specific memory layout can be very useful for testing the guest kernel.

This series allows the user the specify the memory layout for the
virtual machine by expanding the -m/--mem option to take an <addr>
parameter, and by adding architecture specific options to define the I/O
ports, regular MMIO and PCI MMIO memory regions.

The user defined memory regions are implemented in patch #16; I consider
the patch to be an RFC because I'm not really sure that my approach is the
correct one; for example, I decided to make the options arch dependent
because that seemed like the path of least resistance, but they could have
just as easily implemented as arch independent and each architecture
advertised having support for them via a define (like with RAM base
address).

Summary:
 * Patches 1-8 are fixes and cleanups.
 * Patch 9 implements the option for the user to specify the RAM base
   address, but the MMIO regions are left unchanged.
 * Patches 10-12 represent another round of cleanups.
 * Patch 13 implements a memory allocator that allows the user the specify
   any RAM address. The MMIO regions are allocated from the remaining
   address space.
 * Patches 14-15 are cleanups in preparation for the patch will allow the
   user to define the memory layout.
 * Patch 16 implements the option for the user to define the memory layout.

The series are based on previous work by Julien Grall [1].

[1] https://www.spinics.net/lists/kvm/msg179408.html

Alexandru Elisei (10):
  kvmtool: Add helper to sanitize arch specific KVM configuration
  kvmtool: Use MB consistently
  builtin-run.c: Always use virtual machine ram_size in bytes
  arm: Remove redundant define ARM_PCI_CFG_SIZE
  arm: Allow the user to specify RAM base address
  arm/pci: Remove unused ioports
  arm: Allow any base address for RAM
  arm: Move memory related code to memory.c
  kvmtool: Make the size@addr option parser globally visible
  arm: Allow the user to define the MMIO regions

Julien Grall (4):
  kvm__arch_init: Don't pass hugetlbfs_path and ram_size in parameter
  virtio/scsi: Allow to use multiple banks
  arm: Move anything related to RAM initialization in kvm__init_ram
  Fold kvm__init_ram call in kvm__arch_init and rename it

Suzuki K Poulose (2):
  arm: Allow use of hugepage with 16K pagesize host
  kvmtool: Allow standard size specifiers for memory

 Documentation/kvmtool.1                  |   4 +-
 Makefile                                 |   2 +-
 arm/aarch32/include/kvm/kvm-arch.h       |   2 +-
 arm/aarch64/include/kvm/kvm-arch.h       |   6 +-
 arm/allocator.c                          | 150 ++++++++++++++
 arm/gic.c                                |  30 +--
 arm/include/arm-common/allocator.h       |  25 +++
 arm/include/arm-common/kvm-arch.h        |  59 +++---
 arm/include/arm-common/kvm-config-arch.h |  25 +++
 arm/include/arm-common/memory.h          |  13 ++
 arm/kvm.c                                |  58 ++----
 arm/memory.c                             | 326 +++++++++++++++++++++++++++++++
 arm/pci.c                                |   7 +-
 builtin-run.c                            | 119 +++++++++--
 include/kvm/kvm-config.h                 |   5 +-
 include/kvm/kvm.h                        |   7 +-
 kvm.c                                    |  15 +-
 mips/include/kvm/kvm-arch.h              |   4 +
 mips/kvm.c                               |  14 +-
 pci.c                                    |  36 +++-
 powerpc/include/kvm/kvm-arch.h           |   4 +
 powerpc/kvm.c                            |  14 +-
 util/util.c                              |   2 +-
 virtio/mmio.c                            |   7 +
 virtio/scsi.c                            |  21 +-
 x86/include/kvm/kvm-arch.h               |   4 +
 x86/kvm.c                                |  35 ++--
 27 files changed, 843 insertions(+), 151 deletions(-)
 create mode 100644 arm/allocator.c
 create mode 100644 arm/include/arm-common/allocator.h
 create mode 100644 arm/include/arm-common/memory.h
 create mode 100644 arm/memory.c
```
#### [PATCH 0/6] KVM: PPC: Book3S: HV: XIVE: Allocate less VPs in OPAL
##### From: Greg Kurz <groug@kaod.org>

```c
From patchwork Mon Sep 23 15:43:31 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11157153
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EF53C13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 15:43:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D7375207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 15:43:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732528AbfIWPnm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 11:43:42 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28742 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728252AbfIWPnm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 11:43:42 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NFgB0P032594
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 11:43:40 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v70cv9c95-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 11:43:39 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Mon, 23 Sep 2019 16:43:37 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 23 Sep 2019 16:43:33 +0100
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NFhWS339125128
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 15:43:32 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 58E98A405B;
        Mon, 23 Sep 2019 15:43:32 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EFC5CA4060;
        Mon, 23 Sep 2019 15:43:31 +0000 (GMT)
Received: from bahia.lan (unknown [9.145.22.84])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 15:43:31 +0000 (GMT)
Subject: [PATCH 0/6] KVM: PPC: Book3S: HV: XIVE: Allocate less VPs in OPAL
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Date: Mon, 23 Sep 2019 17:43:31 +0200
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19092315-0028-0000-0000-000003A18D89
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092315-0029-0000-0000-000024639F7C
Message-Id: <156925341155.974393.11681611197111945710.stgit@bahia.lan>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=728 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230148
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each vCPU of a VM allocates a XIVE VP in OPAL which is associated with
8 event queue (EQ) descriptors, one for each priority. A POWER9 socket
can handle a maximum of 1M event queues.

The powernv platform allocates NR_CPUS (== 2048) VPs for the hypervisor,
and each XIVE KVM device allocates KVM_MAX_VCPUS (== 2048) VPs. This
means that on a bi-socket system, we can create at most:

(2 * 1M) / (8 * 2048) - 1 == 127 XIVE KVM devices

ie, start at most 127 VMs benefiting from an in-kernel interrupt
controller. Subsequent VMs need to rely on a much slower userspace
emulated XIVE or XICS device in QEMU.

This is problematic as one can legitimately expect to start the same
number of mono-cpu VMs as the number of HW threads available on the
system, eg, 144 on a bi-socket POWER9 Witherspoon.

This series allows QEMU to tell KVM how many interrupt servers are needed,
which is likely less than 2048 with a typical VM, eg. it is only 256 for
32 vCPUs with a guest's core stride of 8 and 1 thread per core.

With this I could run ~500 SMP1 VMs on a Witherspoon system.

Patches 1 to 3 are preliminary fixes (1 and 2 have already been posted
but are provided for convenience).
---
Greg

---

Cédric Le Goater (1):
      KVM: PPC: Book3S HV: XIVE: initialize private pointer when VPs are allocated

Greg Kurz (5):
      KVM: PPC: Book3S HV: XIVE: Set kvm->arch.xive when VPs are allocated
      KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use
      KVM: PPC: Book3S HV: XIVE: Compute the VP id in a common helper
      KVM: PPC: Book3S HV: XIVE: Make VP block size configurable
      KVM: PPC: Book3S HV: XIVE: Allow userspace to set the # of VPs


 Documentation/virt/kvm/devices/xics.txt |   14 +++
 Documentation/virt/kvm/devices/xive.txt |    8 ++
 arch/powerpc/include/uapi/asm/kvm.h     |    3 +
 arch/powerpc/kvm/book3s_xive.c          |  145 +++++++++++++++++++++++++------
 arch/powerpc/kvm/book3s_xive.h          |   17 ++++
 arch/powerpc/kvm/book3s_xive_native.c   |   49 +++++-----
 6 files changed, 179 insertions(+), 57 deletions(-)
```
#### [PATCH 0/3] Replace current->mm by kvm->mm on powerpc/kvm
##### From: Leonardo Bras <leonardo@linux.ibm.com>

```c
From patchwork Mon Sep 23 21:24:06 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Leonardo Bras <leonardo@linux.ibm.com>
X-Patchwork-Id: 11157671
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B29B714E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:24:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9B81A222BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:24:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2503046AbfIWVYa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 17:24:30 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15256 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2390066AbfIWVY3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 17:24:29 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLNESS076409;
        Mon, 23 Sep 2019 17:24:18 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v72g46feq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 17:24:18 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLJNJV023606;
        Mon, 23 Sep 2019 21:24:17 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma02dal.us.ibm.com with ESMTP id 2v5bg74fee-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 21:24:17 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NLOG0A64684394
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 21:24:16 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 36782BE053;
        Mon, 23 Sep 2019 21:24:16 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DD269BE051;
        Mon, 23 Sep 2019 21:24:14 +0000 (GMT)
Received: from LeoBras.aus.stglabs.ibm.com (unknown [9.18.235.184])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 21:24:14 +0000 (GMT)
From: Leonardo Bras <leonardo@linux.ibm.com>
To: kvm@vger.kernel.org, kvm-ppc@vger.kernel.org
Cc: Leonardo Bras <leonardo@linux.ibm.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Michael Ellerman <mpe@ellerman.id.au>
Subject: [PATCH 0/3] Replace current->mm by kvm->mm on powerpc/kvm
Date: Mon, 23 Sep 2019 18:24:06 -0300
Message-Id: <20190923212409.7153-1-leonardo@linux.ibm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=8 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1011 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=640 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230179
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

By replacing, we would reduce the use of 'global' current on code,
relying more in the contents of kvm struct.

On code, I found that in kvm_create_vm() there is:
kvm->mm = current->mm;

And that on every kvm_*_ioctl we have tests like that:
if (kvm->mm != current->mm)
        return -EIO;

So this change would be safe.

I split the changes in 3 patches, so it would be easier to read
and reject separated parts. If decided that squashing is better,
I see no problem doing that.

Best regards,

Leonardo Bras (3):
  powerpc/kvm/book3s: Replace current->mm by kvm->mm
  powerpc/kvm/book3e: Replace current->mm by kvm->mm
  powerpc/kvm/e500: Replace current->mm by kvm->mm

 arch/powerpc/kvm/book3s_64_mmu_hv.c |  4 ++--
 arch/powerpc/kvm/book3s_64_vio.c    |  6 +++---
 arch/powerpc/kvm/book3s_hv.c        | 10 +++++-----
 arch/powerpc/kvm/booke.c            |  2 +-
 arch/powerpc/kvm/e500_mmu_host.c    |  6 +++---
 5 files changed, 14 insertions(+), 14 deletions(-)
```
