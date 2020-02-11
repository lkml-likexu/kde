

#### [PATCH V2 0/5] vDPA support
##### From: Jason Wang <jasowang@redhat.com>

```c
From patchwork Mon Feb 10 03:56:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11372415
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 092A9138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 03:57:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D0CD1208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 03:57:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DMcX/8Od"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbgBJD5b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 9 Feb 2020 22:57:31 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:23905 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726944AbgBJD5b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 9 Feb 2020 22:57:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581307050;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=FpaNsEwT/ks+uSjIzZvFcpf96lfi9mqPgeVQPWwqQKs=;
        b=DMcX/8Odtj6c1Z6BdlocRrW8K2Xz1cuZns/YKwcGfV8+UHsMrbAdQXUVtunFSexUdO2Q86
        V9ne2Q+SHhjp/JLK/1N3BjyvyF2MnnU4Mj/FZXqriYVzaGKqJYMK6vIWW3Srr3REH2L9ll
        XWxoLrLE9i6/MSuF4Z0JxMmYQeGyX8A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-3-zqTqYp5IPvKusquXu357Vg-1; Sun, 09 Feb 2020 22:57:27 -0500
X-MC-Unique: zqTqYp5IPvKusquXu357Vg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 03CD8800D5E;
        Mon, 10 Feb 2020 03:57:25 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-219.pek2.redhat.com [10.72.13.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DB5E9101D481;
        Mon, 10 Feb 2020 03:56:13 +0000 (UTC)
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
Subject: [PATCH V2 0/5] vDPA support
Date: Mon, 10 Feb 2020 11:56:03 +0800
Message-Id: <20200210035608.10002-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all:

This is an updated version of kernel support for vDPA device. Various
changes were made based on the feedback since last verion. One major
change is to drop the sysfs API and leave the management interface for
future development, and introudce the incremental DMA bus
operations. Please see changelog for more information.

The work on vhost, IFCVF (intel VF driver for vDPA) and qemu is
ongoing.

Please provide feedback.

Thanks

Change from V1:

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

V1: https://lkml.org/lkml/2020/1/16/353

Jason Wang (5):
  vhost: factor out IOTLB
  vringh: IOTLB support
  vDPA: introduce vDPA bus
  virtio: introduce a vDPA based transport
  vdpasim: vDPA device simulator

 MAINTAINERS                    |   2 +
 drivers/vhost/Kconfig          |   7 +
 drivers/vhost/Kconfig.vringh   |   1 +
 drivers/vhost/Makefile         |   2 +
 drivers/vhost/net.c            |   2 +-
 drivers/vhost/vhost.c          | 221 ++++-------
 drivers/vhost/vhost.h          |  36 +-
 drivers/vhost/vhost_iotlb.c    | 171 +++++++++
 drivers/vhost/vringh.c         | 421 ++++++++++++++++++--
 drivers/virtio/Kconfig         |  15 +
 drivers/virtio/Makefile        |   2 +
 drivers/virtio/vdpa/Kconfig    |  26 ++
 drivers/virtio/vdpa/Makefile   |   3 +
 drivers/virtio/vdpa/vdpa.c     | 160 ++++++++
 drivers/virtio/vdpa/vdpa_sim.c | 678 +++++++++++++++++++++++++++++++++
 drivers/virtio/virtio_vdpa.c   | 392 +++++++++++++++++++
 include/linux/vdpa.h           | 233 +++++++++++
 include/linux/vhost_iotlb.h    |  45 +++
 include/linux/vringh.h         |  36 ++
 19 files changed, 2249 insertions(+), 204 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 drivers/virtio/vdpa/Kconfig
 create mode 100644 drivers/virtio/vdpa/Makefile
 create mode 100644 drivers/virtio/vdpa/vdpa.c
 create mode 100644 drivers/virtio/vdpa/vdpa_sim.c
 create mode 100644 drivers/virtio/virtio_vdpa.c
 create mode 100644 include/linux/vdpa.h
 create mode 100644 include/linux/vhost_iotlb.h
```
#### [PATCH 00/28] docs: virt: manually convert text documents to ReST
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Mon Feb 10 06:02:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11372531
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 257D714B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:03:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 032BB24687
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:03:29 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581314609;
	bh=NuzkIMPNIATHPUl2aslNdscp/bAOQqrHc3oqypTnzvk=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=LcZMEs0IXVOy4v9Ci2B1o9FnM96DqpKExP6JMMtJIZskrXd1lVnBmAzoDnBTJxUi2
	 /fDvy8244EPI7gbfyC26EslNv+mXnfUGT8RAXsSIjiGDMVNrThYUEtbgdsTKdDzyBl
	 kY5f7kqQ6/ashotXSSvoy48LIIAIdQhRxbFeUYuA=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727662AbgBJGDW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 01:03:22 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:36454 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727579AbgBJGDN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 01:03:13 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:Content-Type:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=8IP+Foq83syk0a2uyR2F+XgF3E1vw2G4B3g0j4/F4us=;
 b=sfCBvQ7MNhogIlCcfR3+8HZa53
        rDOsE+SQoKoA986Wsk15ocRI2khmXCAUcKrsgvzUJaFKM/ryqHRnyOguerF6+z9KUS+HxjxNM5Yay
        41VpZ6cCSyLrc9Uvx5t+sGuKAP1v9AvhL25SMWaTdhnLBpvrT86C60/0jEJEumNGCSYYIaSd0unKJ
        iQZskDPCitiKIn+SFgi95AuWuuuFWopq/pEIGkPh/ZQuXguzElqfDxxByAy/nGnQQO5KP3cDzv6aN
        GaLnme5ceFhXukGL9d52krtmob5mEgGESeQxhGBmlkZV6ruVkVqX+zXY9XOcu/idKScNhQwQShn83
        Vj6LzIeA==;
Received: from [80.156.29.194] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1j12A3-0006Ta-Cq; Mon, 10 Feb 2020 06:03:11 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1j12A1-00C2Ua-MU; Mon, 10 Feb 2020 07:03:09 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Media Mailing List <linux-media@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Mauro Carvalho Chehab <mchehab@infradead.org>,
        linux-doc@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        linux-um@lists.infradead.org, Jonathan Corbet <corbet@lwn.net>,
        Jeff Dike <jdike@addtoit.com>,
        Anton Ivanov <anton.ivanov@cambridgegreys.com>,
        Richard Weinberger <richard@nod.at>, kvm@vger.kernel.org
Subject: [PATCH 00/28] docs: virt: manually convert text documents to ReST
 format
Date: Mon, 10 Feb 2020 07:02:38 +0100
Message-Id: <cover.1581314316.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Manually convert the documentation under Documentation/virt to ReST,
minimizing the usage of uneeded markups and preserving the documentation
writer's style.

PS.: Patches are against linux-next tree (20200204).

v3:

- locking.rst now uses tables for the two concurrency examples;
- The file guest-halt-polling.txt was still under Documentation/virtual.
  Converted to ReST and moved to Documentaion/virt;
- Addressed the issues pointed by Cornelia and Paolo.

v2:

- Solved a conflict with linux-next;
- Added SPDX headers.


Mauro Carvalho Chehab (28):
  docs: kvm: add arm/pvtime.rst to index.rst
  docs: virt: convert UML documentation to ReST
  docs: virt: user_mode_linux.rst: update compiling instructions
  docs: virt: user_mode_linux.rst: fix URL references
  docs: virt: convert halt-polling.txt to ReST format
  docs: virt: Convert msr.txt to ReST format
  docs: kvm: devices/arm-vgic-its.txt to ReST format
  docs: kvm: devices/arm-vgit-v3.txt to ReST
  docs: kvm: convert devices/arm-vgit.txt to ReST
  docs: kvm: convert devices/mpic.txt to ReST
  docs: kvm: convert devices/s390_flic.txt to ReST
  docs: kvm: convert devices/vcpu.txt to ReST
  docs: kvm: convert devices/vfio.txt to ReST
  docs: kvm: convert devices/vm.txt to ReST
  docs: kvm: convert devices/xics.txt to ReST
  docs: kvm: convert devices/xive.txt to ReST
  docs: kvm: Convert api.txt to ReST format
  docs: kvm: convert arm/hyp-abi.txt to ReST
  docs: kvm: arm/psci.txt: convert to ReST
  docs: kvm: Convert hypercalls.txt to ReST format
  docs: kvm: Convert locking.txt to ReST format
  docs: kvm: Convert mmu.txt to ReST format
  docs: kvm: Convert nested-vmx.txt to ReST format
  docs: kvm: Convert ppc-pv.txt to ReST format
  docs: kvm: Convert s390-diag.txt to ReST format
  docs: kvm: Convert timekeeping.txt to ReST format
  docs: kvm: review-checklist.txt: rename to ReST
  docs: virt: guest-halt-polling.txt convert to ReST

 .../guest-halt-polling.rst}                   |   12 +-
 Documentation/virt/index.rst                  |    2 +
 Documentation/virt/kvm/{api.txt => api.rst}   | 3348 ++++++++++-------
 .../virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst} |   28 +-
 Documentation/virt/kvm/arm/index.rst          |   12 +
 .../virt/kvm/arm/{psci.txt => psci.rst}       |   46 +-
 .../{arm-vgic-its.txt => arm-vgic-its.rst}    |  106 +-
 .../{arm-vgic-v3.txt => arm-vgic-v3.rst}      |  132 +-
 .../devices/{arm-vgic.txt => arm-vgic.rst}    |   89 +-
 Documentation/virt/kvm/devices/index.rst      |   19 +
 .../virt/kvm/devices/{mpic.txt => mpic.rst}   |   11 +-
 .../devices/{s390_flic.txt => s390_flic.rst}  |   70 +-
 Documentation/virt/kvm/devices/vcpu.rst       |  114 +
 Documentation/virt/kvm/devices/vcpu.txt       |   76 -
 .../virt/kvm/devices/{vfio.txt => vfio.rst}   |   25 +-
 .../virt/kvm/devices/{vm.txt => vm.rst}       |  206 +-
 .../virt/kvm/devices/{xics.txt => xics.rst}   |   28 +-
 .../virt/kvm/devices/{xive.txt => xive.rst}   |  148 +-
 .../{halt-polling.txt => halt-polling.rst}    |   86 +-
 .../kvm/{hypercalls.txt => hypercalls.rst}    |  129 +-
 Documentation/virt/kvm/index.rst              |   16 +
 Documentation/virt/kvm/locking.rst            |  243 ++
 Documentation/virt/kvm/locking.txt            |  215 --
 Documentation/virt/kvm/{mmu.txt => mmu.rst}   |   62 +-
 Documentation/virt/kvm/{msr.txt => msr.rst}   |  147 +-
 .../kvm/{nested-vmx.txt => nested-vmx.rst}    |   37 +-
 .../virt/kvm/{ppc-pv.txt => ppc-pv.rst}       |   26 +-
 ...iew-checklist.txt => review-checklist.rst} |    3 +
 .../virt/kvm/{s390-diag.txt => s390-diag.rst} |   13 +-
 .../kvm/{timekeeping.txt => timekeeping.rst}  |  221 +-
 ...odeLinux-HOWTO.txt => user_mode_linux.rst} | 1814 ++++-----
 31 files changed, 4194 insertions(+), 3290 deletions(-)
 rename Documentation/{virtual/guest-halt-polling.txt => virt/guest-halt-polling.rst} (91%)
 rename Documentation/virt/kvm/{api.txt => api.rst} (71%)
 rename Documentation/virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst} (79%)
 create mode 100644 Documentation/virt/kvm/arm/index.rst
 rename Documentation/virt/kvm/arm/{psci.txt => psci.rst} (60%)
 rename Documentation/virt/kvm/devices/{arm-vgic-its.txt => arm-vgic-its.rst} (71%)
 rename Documentation/virt/kvm/devices/{arm-vgic-v3.txt => arm-vgic-v3.rst} (77%)
 rename Documentation/virt/kvm/devices/{arm-vgic.txt => arm-vgic.rst} (66%)
 create mode 100644 Documentation/virt/kvm/devices/index.rst
 rename Documentation/virt/kvm/devices/{mpic.txt => mpic.rst} (91%)
 rename Documentation/virt/kvm/devices/{s390_flic.txt => s390_flic.rst} (87%)
 create mode 100644 Documentation/virt/kvm/devices/vcpu.rst
 delete mode 100644 Documentation/virt/kvm/devices/vcpu.txt
 rename Documentation/virt/kvm/devices/{vfio.txt => vfio.rst} (72%)
 rename Documentation/virt/kvm/devices/{vm.txt => vm.rst} (61%)
 rename Documentation/virt/kvm/devices/{xics.txt => xics.rst} (84%)
 rename Documentation/virt/kvm/devices/{xive.txt => xive.rst} (62%)
 rename Documentation/virt/kvm/{halt-polling.txt => halt-polling.rst} (64%)
 rename Documentation/virt/kvm/{hypercalls.txt => hypercalls.rst} (55%)
 create mode 100644 Documentation/virt/kvm/locking.rst
 delete mode 100644 Documentation/virt/kvm/locking.txt
 rename Documentation/virt/kvm/{mmu.txt => mmu.rst} (94%)
 rename Documentation/virt/kvm/{msr.txt => msr.rst} (74%)
 rename Documentation/virt/kvm/{nested-vmx.txt => nested-vmx.rst} (90%)
 rename Documentation/virt/kvm/{ppc-pv.txt => ppc-pv.rst} (91%)
 rename Documentation/virt/kvm/{review-checklist.txt => review-checklist.rst} (95%)
 rename Documentation/virt/kvm/{s390-diag.txt => s390-diag.rst} (90%)
 rename Documentation/virt/kvm/{timekeeping.txt => timekeeping.rst} (85%)
 rename Documentation/virt/uml/{UserModeLinux-HOWTO.txt => user_mode_linux.rst} (74%)
```
#### [RFC PATCH v10 0/9] Enable ptp_kvm for arm/arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Mon Feb 10 08:48:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11372743
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D0D4F14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 08:49:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE8A121739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 08:49:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727505AbgBJIt0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 03:49:26 -0500
Received: from foss.arm.com ([217.140.110.172]:57416 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726061AbgBJIt0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 03:49:26 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2197B31B;
        Mon, 10 Feb 2020 00:49:25 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 997A43F68F;
        Mon, 10 Feb 2020 00:49:19 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH v10 0/9] Enable ptp_kvm for arm/arm64
Date: Mon, 10 Feb 2020 16:48:57 +0800
Message-Id: <20200210084906.24870-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm ptp targets to provide high precision time sync between guest
and host in virtualization environment. Here, we enable kvm ptp
for arm64.

change log:
from v10 to v9
        (1) change code base to v5.5.
	(2) enable ptp_kvm both for arm32 and arm64.
        (3) let user choose which of virtual counter or physical counter
should return when using crosstimestamp mode of ptp_kvm for arm/arm64.
        (4) extend input argument for getcrosstimestamp API.

from v8 to v9:
        (1) move ptp_kvm.h to driver/ptp/
        (2) replace license declaration of ptp_kvm.h the same with other
header files in the same directory.

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v6 to v7:
        (1) include the omitted clocksource_id.h in last version.
        (2) reorder the header file in patch.
        (3) refine some words in commit message to make it more impersonal.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.

from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.

from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.


Jianyong Wu (8):
  psci: export psci conduit get helper.
  ptp: Reorganize ptp_kvm modules to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  psci: Add hypercall service for ptp_kvm.
  ptp: arm/arm64: Enable ptp_kvm for arm/arm64
  ptp: extend input argument for getcrosstimestamp API
  arm/arm64: add mechanism to let user choose which counter to return
  arm/arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

 drivers/clocksource/arm_arch_timer.c        | 33 ++++++++
 drivers/firmware/psci/psci.c                |  1 +
 drivers/net/ethernet/intel/e1000e/ptp.c     |  3 +-
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  5 ++
 drivers/ptp/ptp_chardev.c                   |  8 +-
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm.c                   | 53 +++++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 83 ++++++--------------
 drivers/ptp/ptp_kvm_x86.c                   | 87 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 21 +++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 13 +++
 include/linux/ptp_clock_kernel.h            |  3 +-
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 include/uapi/linux/ptp_clock.h              |  4 +-
 kernel/time/clocksource.c                   |  3 +
 kernel/time/timekeeping.c                   |  1 +
 virt/kvm/arm/arm.c                          |  1 +
 virt/kvm/arm/hypercalls.c                   | 44 ++++++++++-
 21 files changed, 323 insertions(+), 72 deletions(-)
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [RFC PATCH 0/5] Removing support for 32bit KVM/arm host
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Feb 10 14:13:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11373351
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 98C82921
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:13:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6DA41208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:13:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581344012;
	bh=r+j5gAVgCtkQ8J7jlJ6T58nEBoHtHCZIY6CJGtVKFOc=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=KIAygBNIjmLL5KSF3lBQ0TIpV8DBE0dGi4nK7tusGUirQO4/c0PdsCeTkxB+lBcHr
	 jvnHfnPrs0WKxnuehAu53xGxFIszukLyexFrWPK8vQJ8cd8beZ2g+Rjxt47IJKPPxm
	 tore9Vem7pjZAMoWv/LnGTOa4ST6QkQGr/W6/NIk=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728459AbgBJONb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 09:13:31 -0500
Received: from mail.kernel.org ([198.145.29.99]:49042 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727481AbgBJONb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 09:13:31 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1EBA020714;
        Mon, 10 Feb 2020 14:13:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581344010;
        bh=r+j5gAVgCtkQ8J7jlJ6T58nEBoHtHCZIY6CJGtVKFOc=;
        h=From:To:Cc:Subject:Date:From;
        b=PMfXM5QBXw6bvZAbWFaGKhv8hs7NJpPsgDZ1YHM1oxapmtngi4XHN3LBoim4jqmTg
         WKQKQZv9ha5K41MEhM1pbx3E9yeqJkL8EAzNHZLokEDqLJ/MXlao5xi56CjgN7Qa4l
         NZcb80T8GtagXnHUm8flgDsd+lXssVdSKRl0ZxtU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j19oW-0048kH-CM; Mon, 10 Feb 2020 14:13:28 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christoffer Dall <Christoffer.Dall@arm.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>,
        Russell King <linux@arm.linux.org.uk>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Anders Berg <anders.berg@lsi.com>,
        Arnd Bergmann <arnd@arndb.de>
Subject: [RFC PATCH 0/5] Removing support for 32bit KVM/arm host
Date: Mon, 10 Feb 2020 14:13:19 +0000
Message-Id: <20200210141324.21090-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, pbonzini@redhat.com,
 Christoffer.Dall@arm.com, will@kernel.org, qperret@google.com,
 linux@arm.linux.org.uk, vladimir.murzin@arm.com, anders.berg@lsi.com,
 arnd@arndb.de
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
- It has zero users (I don't count myself here)
- It is more and more getting in the way of new arm64 developments

So here it is: unless someone screams and shows that they rely on
KVM/arm to be maintained upsteam, I'll remove 32bit host support
form the tree. One of the reasons that makes me confident nobody is
using it is that I never receive *any* bug report. Yes, it is perfect.
But if you depend on KVM/arm being available in mainline, please shout.

To reiterate: 32bit guest support for arm64 stays, of course. Only
32bit host goes. Once this is merged, I plan to move virt/kvm/arm to
arm64, and cleanup all the now unnecessary abstractions.

The patches have been generated with the -D option to avoid spamming
everyone with huge diffs, and there is a kvm-arm/goodbye branch in
my kernel.org repository.

Marc Zyngier (5):
  arm: Unplug KVM from the build system
  arm: Remove KVM from config files
  arm: Remove 32bit KVM host support
  arm: Remove HYP/Stage-2 page-table support
  arm: Remove GICv3 vgic compatibility macros

 Documentation/virt/kvm/arm/hyp-abi.txt |    5 +
 arch/arm/Kconfig                       |    2 -
 arch/arm/Makefile                      |    1 -
 arch/arm/configs/axm55xx_defconfig     |    2 -
 arch/arm/include/asm/arch_gicv3.h      |  114 --
 arch/arm/include/asm/kvm_arm.h         |  239 ----
 arch/arm/include/asm/kvm_asm.h         |   77 --
 arch/arm/include/asm/kvm_coproc.h      |   36 -
 arch/arm/include/asm/kvm_emulate.h     |  372 ------
 arch/arm/include/asm/kvm_host.h        |  459 --------
 arch/arm/include/asm/kvm_hyp.h         |  127 ---
 arch/arm/include/asm/kvm_mmu.h         |  435 -------
 arch/arm/include/asm/kvm_ras.h         |   14 -
 arch/arm/include/asm/pgtable-3level.h  |   20 -
 arch/arm/include/asm/pgtable.h         |    9 -
 arch/arm/include/asm/sections.h        |    6 +-
 arch/arm/include/asm/stage2_pgtable.h  |   75 --
 arch/arm/include/asm/virt.h            |   12 -
 arch/arm/include/uapi/asm/kvm.h        |  314 -----
 arch/arm/kernel/asm-offsets.c          |   11 -
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
 49 files changed, 7 insertions(+), 6262 deletions(-)
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
Acked-by: Olof Johansson <olof@lixom.net>
Acked-by: Will Deacon <will@kernel.org>
Acked-by: Arnd Bergmann <arnd@arndb.de>
```
#### [PATCH 0/1] s390/uv: fix for ultravisor query function
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Feb 10 16:54:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11373629
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E6C2109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 16:54:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2927920661
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 16:54:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727852AbgBJQyo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 11:54:44 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41866 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727003AbgBJQyo (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 Feb 2020 11:54:44 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01AGsXMo111544;
        Mon, 10 Feb 2020 11:54:43 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2y1tnd7pjm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 11:54:42 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01AGsaMB111972;
        Mon, 10 Feb 2020 11:54:42 -0500
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2y1tnd7pj9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 11:54:42 -0500
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01AGoaUI001300;
        Mon, 10 Feb 2020 16:54:42 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma05wdc.us.ibm.com with ESMTP id 2y1mm6bfgq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 16:54:41 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01AGseOC41550112
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 Feb 2020 16:54:40 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A350C6E053;
        Mon, 10 Feb 2020 16:54:40 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0C4E16E050;
        Mon, 10 Feb 2020 16:54:39 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 10 Feb 2020 16:54:39 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Vasily Gorbik <gor@linux.ibm.com>
Subject: [PATCH 0/1] s390/uv: fix for ultravisor query function
Date: Mon, 10 Feb 2020 11:54:38 -0500
Message-Id: <20200210165439.3767-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-10_06:2020-02-10,2020-02-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0
 lowpriorityscore=0 malwarescore=0 suspectscore=0 bulkscore=0 phishscore=0
 impostorscore=0 adultscore=0 priorityscore=1501 clxscore=1015 mlxscore=0
 mlxlogscore=859 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002100127
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As outlined by the architects the query command could actually return more
than the minimal 168 bytes.

I will carry this with the KVM host support for protected virtualization

Christian Borntraeger (1):
  s390/uv: Fix handling of length extensions

 arch/s390/boot/uv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
