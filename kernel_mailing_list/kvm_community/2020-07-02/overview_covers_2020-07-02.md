

#### [kvm-unit-tests PATCH v2 0/8] arm/arm64: Add IPI/LPI/vtimer latency
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
From patchwork Thu Jul  2 02:50:41 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11637769
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 52372913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 02:51:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4455E20781
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 02:51:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726363AbgGBCvu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 22:51:50 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:46242 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726156AbgGBCvu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 22:51:50 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 86C42AF8495509856FFE;
        Thu,  2 Jul 2020 10:51:46 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.42) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 10:51:36 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH v2 0/8] arm/arm64: Add IPI/LPI/vtimer latency
 test
Date: Thu, 2 Jul 2020 10:50:41 +0800
Message-ID: <20200702025049.6896-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.42]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With the development of arm gic architecture, we think it will be useful
to add some performance test in kut to measure the cost of interrupts.
In this series, we add GICv4.1 support for ipi latency test and
implement LPI/vtimer latency test.

This series of patches has been tested on GICv4.1 supported hardware.

* From v1:
  - Fix spelling mistake
  - Use the existing interface to inject hw sgi to simply the logic
  - Add two separate patches to limit the running times and time cost
    of each individual micro-bench test

Jingyi Wang (8):
  arm64: microbench: get correct ipi recieved num
  arm64: microbench: Use the funcions for ipi test as the general
    functions for gic(ipi/lpi/timer) test
  arm64: microbench: gic: Add gicv4.1 support for ipi latency test.
  arm64: its: Handle its command queue wrapping
  arm64: microbench: its: Add LPI latency test
  arm64: microbench: Allow each test to specify its running times
  arm64: microbench: Add time limit for each individual test
  arm64: microbench: Add vtimer latency test

 arm/micro-bench.c          | 218 +++++++++++++++++++++++++++++++------
 lib/arm/asm/gic-v3.h       |   3 +
 lib/arm/asm/gic.h          |   1 +
 lib/arm64/gic-v3-its-cmd.c |   3 +-
 4 files changed, 189 insertions(+), 36 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/8] arm/arm64: Add IPI/LPI/vtimer latency
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
From patchwork Thu Jul  2 03:01:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11637787
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 410DE92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 28F3520936
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727961AbgGBDCf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 23:02:35 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:47368 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726726AbgGBDCf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 23:02:35 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 8B49F91145ECB3840D36;
        Thu,  2 Jul 2020 11:02:30 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.42) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 11:02:19 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH v2 0/8] arm/arm64: Add IPI/LPI/vtimer latency
 test
Date: Thu, 2 Jul 2020 11:01:24 +0800
Message-ID: <20200702030132.20252-1-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.42]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With the development of arm gic architecture, we think it will be useful
to add some performance test in kut to measure the cost of interrupts.
In this series, we add GICv4.1 support for ipi latency test and
implement LPI/vtimer latency test.

This series of patches has been tested on GICv4.1 supported hardware.

* From v1:
  - Fix spelling mistake
  - Use the existing interface to inject hw sgi to simply the logic
  - Add two separate patches to limit the running times and time cost
    of each individual micro-bench test

Jingyi Wang (8):
  arm64: microbench: get correct ipi received num
  arm64: microbench: Use the funcions for ipi test as the general
    functions for gic(ipi/lpi/timer) test
  arm64: microbench: gic: Add gicv4.1 support for ipi latency test.
  arm64: its: Handle its command queue wrapping
  arm64: microbench: its: Add LPI latency test
  arm64: microbench: Allow each test to specify its running times
  arm64: microbench: Add time limit for each individual test
  arm64: microbench: Add vtimer latency test

 arm/micro-bench.c          | 218 +++++++++++++++++++++++++++++++------
 lib/arm/asm/gic-v3.h       |   3 +
 lib/arm/asm/gic.h          |   1 +
 lib/arm64/gic-v3-its-cmd.c |   3 +-
 4 files changed, 189 insertions(+), 36 deletions(-)
```
#### [RFC PATCH 00/22] Enhance VHOST to enable SoC-to-SoC communication
##### From: Kishon Vijay Abraham I <kishon@ti.com>

```c
From patchwork Thu Jul  2 08:21:21 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kishon Vijay Abraham I <kishon@ti.com>
X-Patchwork-Id: 11638107
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6632B6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:22:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 481BB20720
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:22:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ti.com header.i=@ti.com header.b="JYTSz6tC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727782AbgGBIWI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 04:22:08 -0400
Received: from lelv0142.ext.ti.com ([198.47.23.249]:59346 "EHLO
        lelv0142.ext.ti.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726362AbgGBIWI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 04:22:08 -0400
Received: from lelv0265.itg.ti.com ([10.180.67.224])
        by lelv0142.ext.ti.com (8.15.2/8.15.2) with ESMTP id 0628LuYq081675;
        Thu, 2 Jul 2020 03:21:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ti.com;
        s=ti-com-17Q1; t=1593678116;
        bh=KmDEx84ZylqeHRRIg+ywtR6uqUDz71eDn9DrKmWcHRo=;
        h=From:To:CC:Subject:Date;
        b=JYTSz6tCbffjaS8p0R98jFdU890cGlFgkaOIUX73Isf6MRMb/U17YWcenQm9dERCa
         uNWmCgLlLq60cM9CJqROng6gAsyNsVmRi/7u5UBoPIUD9KHejtBD55BvUyeeVEw5IC
         /B77fRU9Di3zLD24jEuw3XemZ32TkSelC9dgTAEw=
Received: from DFLE112.ent.ti.com (dfle112.ent.ti.com [10.64.6.33])
        by lelv0265.itg.ti.com (8.15.2/8.15.2) with ESMTPS id 0628LoK6065017
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=FAIL);
        Thu, 2 Jul 2020 03:21:51 -0500
Received: from DFLE109.ent.ti.com (10.64.6.30) by DFLE112.ent.ti.com
 (10.64.6.33) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.1979.3; Thu, 2 Jul
 2020 03:21:50 -0500
Received: from lelv0327.itg.ti.com (10.180.67.183) by DFLE109.ent.ti.com
 (10.64.6.30) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.1979.3 via
 Frontend Transport; Thu, 2 Jul 2020 03:21:50 -0500
Received: from a0393678ub.india.ti.com (ileax41-snat.itg.ti.com
 [10.172.224.153])
        by lelv0327.itg.ti.com (8.15.2/8.15.2) with ESMTP id 0628LiYC006145;
        Thu, 2 Jul 2020 03:21:45 -0500
From: Kishon Vijay Abraham I <kishon@ti.com>
To: Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Jon Mason <jdmason@kudzu.us>,
        Dave Jiang <dave.jiang@intel.com>,
        Allen Hubbe <allenbh@gmail.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Bjorn Helgaas <bhelgaas@google.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>
CC: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linux-remoteproc@vger.kernel.org>, <linux-ntb@googlegroups.com>,
        <linux-pci@vger.kernel.org>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>
Subject: [RFC PATCH 00/22] Enhance VHOST to enable SoC-to-SoC communication
Date: Thu, 2 Jul 2020 13:51:21 +0530
Message-ID: <20200702082143.25259-1-kishon@ti.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-EXCLAIMER-MD-CONFIG: e1e8a2fd-e40a-4ac6-ac9b-f7e9cc9ee180
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enhances Linux Vhost support to enable SoC-to-SoC
communication over MMIO. This series enables rpmsg communication between
two SoCs using both PCIe RC<->EP and HOST1-NTB-HOST2

1) Modify vhost to use standard Linux driver model
2) Add support in vring to access virtqueue over MMIO
3) Add vhost client driver for rpmsg
4) Add PCIe RC driver (uses virtio) and PCIe EP driver (uses vhost) for
   rpmsg communication between two SoCs connected to each other
5) Add NTB Virtio driver and NTB Vhost driver for rpmsg communication
   between two SoCs connected via NTB
6) Add configfs to configure the components

UseCase1 :

 VHOST RPMSG                     VIRTIO RPMSG
      +                               +
      |                               |
      |                               |
      |                               |
      |                               |
+-----v------+                 +------v-------+
|   Linux    |                 |     Linux    |
|  Endpoint  |                 | Root Complex |
|            <----------------->              |
|            |                 |              |
|    SOC1    |                 |     SOC2     |
+------------+                 +--------------+

UseCase 2:

     VHOST RPMSG                                      VIRTIO RPMSG
          +                                                 +
          |                                                 |
          |                                                 |
          |                                                 |
          |                                                 |
   +------v------+                                   +------v------+
   |             |                                   |             |
   |    HOST1    |                                   |    HOST2    |
   |             |                                   |             |
   +------^------+                                   +------^------+
          |                                                 |
          |                                                 |
+---------------------------------------------------------------------+
|  +------v------+                                   +------v------+  |
|  |             |                                   |             |  |
|  |     EP      |                                   |     EP      |  |
|  | CONTROLLER1 |                                   | CONTROLLER2 |  |
|  |             <----------------------------------->             |  |
|  |             |                                   |             |  |
|  |             |                                   |             |  |
|  |             |  SoC With Multiple EP Instances   |             |  |
|  |             |  (Configured using NTB Function)  |             |  |
|  +-------------+                                   +-------------+  |
+---------------------------------------------------------------------+

Software Layering:

The high-level SW layering should look something like below. This series
adds support only for RPMSG VHOST, however something similar should be
done for net and scsi. With that any vhost device (PCI, NTB, Platform
device, user) can use any of the vhost client driver.


    +----------------+  +-----------+  +------------+  +----------+
    |  RPMSG VHOST   |  | NET VHOST |  | SCSI VHOST |  |    X     |
    +-------^--------+  +-----^-----+  +-----^------+  +----^-----+
            |                 |              |              |
            |                 |              |              |
            |                 |              |              |
+-----------v-----------------v--------------v--------------v----------+
|                            VHOST CORE                                |
+--------^---------------^--------------------^------------------^-----+
         |               |                    |                  |
         |               |                    |                  |
         |               |                    |                  |
+--------v-------+  +----v------+  +----------v----------+  +----v-----+
|  PCI EPF VHOST |  | NTB VHOST |  |PLATFORM DEVICE VHOST|  |    X     |
+----------------+  +-----------+  +---------------------+  +----------+

This was initially proposed here [1]

[1] -> https://lore.kernel.org/r/2cf00ec4-1ed6-f66e-6897-006d1a5b6390@ti.com


Kishon Vijay Abraham I (22):
  vhost: Make _feature_ bits a property of vhost device
  vhost: Introduce standard Linux driver model in VHOST
  vhost: Add ops for the VHOST driver to configure VHOST device
  vringh: Add helpers to access vring in MMIO
  vhost: Add MMIO helpers for operations on vhost virtqueue
  vhost: Introduce configfs entry for configuring VHOST
  virtio_pci: Use request_threaded_irq() instead of request_irq()
  rpmsg: virtio_rpmsg_bus: Disable receive virtqueue callback when
    reading messages
  rpmsg: Introduce configfs entry for configuring rpmsg
  rpmsg: virtio_rpmsg_bus: Add Address Service Notification support
  rpmsg: virtio_rpmsg_bus: Move generic rpmsg structure to
    rpmsg_internal.h
  virtio: Add ops to allocate and free buffer
  rpmsg: virtio_rpmsg_bus: Use virtio_alloc_buffer() and
    virtio_free_buffer()
  rpmsg: Add VHOST based remote processor messaging bus
  samples/rpmsg: Setup delayed work to send message
  samples/rpmsg: Wait for address to be bound to rpdev for sending
    message
  rpmsg.txt: Add Documentation to configure rpmsg using configfs
  virtio_pci: Add VIRTIO driver for VHOST on Configurable PCIe Endpoint
    device
  PCI: endpoint: Add EP function driver to provide VHOST interface
  NTB: Add a new NTB client driver to implement VIRTIO functionality
  NTB: Add a new NTB client driver to implement VHOST functionality
  NTB: Describe the ntb_virtio and ntb_vhost client in the documentation

 Documentation/driver-api/ntb.rst              |   11 +
 Documentation/rpmsg.txt                       |   56 +
 drivers/ntb/Kconfig                           |   18 +
 drivers/ntb/Makefile                          |    2 +
 drivers/ntb/ntb_vhost.c                       |  776 +++++++++++
 drivers/ntb/ntb_virtio.c                      |  853 ++++++++++++
 drivers/ntb/ntb_virtio.h                      |   56 +
 drivers/pci/endpoint/functions/Kconfig        |   11 +
 drivers/pci/endpoint/functions/Makefile       |    1 +
 .../pci/endpoint/functions/pci-epf-vhost.c    | 1144 ++++++++++++++++
 drivers/rpmsg/Kconfig                         |   10 +
 drivers/rpmsg/Makefile                        |    3 +-
 drivers/rpmsg/rpmsg_cfs.c                     |  394 ++++++
 drivers/rpmsg/rpmsg_core.c                    |    7 +
 drivers/rpmsg/rpmsg_internal.h                |  136 ++
 drivers/rpmsg/vhost_rpmsg_bus.c               | 1151 +++++++++++++++++
 drivers/rpmsg/virtio_rpmsg_bus.c              |  184 ++-
 drivers/vhost/Kconfig                         |    1 +
 drivers/vhost/Makefile                        |    2 +-
 drivers/vhost/net.c                           |   10 +-
 drivers/vhost/scsi.c                          |   24 +-
 drivers/vhost/test.c                          |   17 +-
 drivers/vhost/vdpa.c                          |    2 +-
 drivers/vhost/vhost.c                         |  730 ++++++++++-
 drivers/vhost/vhost_cfs.c                     |  341 +++++
 drivers/vhost/vringh.c                        |  332 +++++
 drivers/vhost/vsock.c                         |   20 +-
 drivers/virtio/Kconfig                        |    9 +
 drivers/virtio/Makefile                       |    1 +
 drivers/virtio/virtio_pci_common.c            |   25 +-
 drivers/virtio/virtio_pci_epf.c               |  670 ++++++++++
 include/linux/mod_devicetable.h               |    6 +
 include/linux/rpmsg.h                         |    6 +
 {drivers/vhost => include/linux}/vhost.h      |  132 +-
 include/linux/virtio.h                        |    3 +
 include/linux/virtio_config.h                 |   42 +
 include/linux/vringh.h                        |   46 +
 samples/rpmsg/rpmsg_client_sample.c           |   32 +-
 tools/virtio/virtio_test.c                    |    2 +-
 39 files changed, 7083 insertions(+), 183 deletions(-)
 create mode 100644 drivers/ntb/ntb_vhost.c
 create mode 100644 drivers/ntb/ntb_virtio.c
 create mode 100644 drivers/ntb/ntb_virtio.h
 create mode 100644 drivers/pci/endpoint/functions/pci-epf-vhost.c
 create mode 100644 drivers/rpmsg/rpmsg_cfs.c
 create mode 100644 drivers/rpmsg/vhost_rpmsg_bus.c
 create mode 100644 drivers/vhost/vhost_cfs.c
 create mode 100644 drivers/virtio/virtio_pci_epf.c
 rename {drivers/vhost => include/linux}/vhost.h (66%)
```
#### [PATCH v2 0/8] KVM: arm64: Support HW dirty log based on DBM
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Jul  2 13:55:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11638969
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6400913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 13:57:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F9E320890
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 13:57:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729588AbgGBN5R (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 09:57:17 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:7354 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729263AbgGBN5K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 09:57:10 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 913E96BE24CEBCEA50BE;
        Thu,  2 Jul 2020 21:56:10 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 21:56:00 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Steven Price <steven.price@arm.com>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <liangpeng10@huawei.com>, <zhengxiang9@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 0/8] KVM: arm64: Support HW dirty log based on DBM
Date: Thu, 2 Jul 2020 21:55:48 +0800
Message-ID: <20200702135556.36896-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series add support for dirty log based on HW DBM.

It works well under some migration test cases, including VM with 4K
pages or 2M THP. I checked the SHA256 hash digest of all memory and
they keep same for source VM and destination VM, which means no dirty
pages is missed under hardware DBM.

Some key points:

1. Only support hardware updates of dirty status for PTEs. PMDs and PUDs
   are not involved for now.

2. About *performance*: In RFC patch, I have mentioned that for every 64GB
   memory, KVM consumes about 40ms to scan all PTEs to collect dirty log.
   This patch solves this problem through two ways: HW/SW dynamic switch
   and Multi-core offload.

   HW/SW dynamic switch: Give userspace right to enable/disable hw dirty
   log. This adds a new KVM cap named KVM_CAP_ARM_HW_DIRTY_LOG. We can
   achieve this by change the kvm->arch.vtcr value and kick vCPUs out to
   reload this value to VCTR_EL2. Then userspace can enable hw dirty log
   at the begining and disable it when dirty pages is little and about to
   stop VM, so VM downtime is not affected.

   Multi-core offload: Offload the PT scanning workload to multi-core can
   greatly reduce scanning time. To promise we can complete in time, I use
   smp_call_fuction to realize this policy, which utilize IPI to dispatch
   workload to other CPUs. Under 128U Kunpeng 920 platform, it just takes
   about 5ms to scan PTs of 256 RAM (use mempress and almost all PTs have
   been established). And We dispatch workload iterately (every CPU just
   scan PTs of 512M RAM for each iteration), so it won't affect physical
   CPUs seriously.

3. About correctness: Only add DBM bit when PTE is already writable, so
   we still have readonly PTE and some mechanisms which rely on readonly
   PTs are not broken.

4. About PTs modification races: There are two kinds of PTs modification.
   
   The first is adding or clearing specific bit, such as AF or RW. All
   these operations have been converted to be atomic, avoid covering
   dirty status set by hardware.
   
   The second is replacement, such as PTEs unmapping or changement. All
   these operations will invoke kvm_set_pte finally. kvm_set_pte have
   been converted to be atomic and we save the dirty status to underlying
   bitmap if dirty status is coverred.

Change log:

v2:
 - Address Steven's comments.
 - Add support of parallel dirty log sync.
 - Simplify and merge patches of v1.

v1:
 - Address Catalin's comments.

Keqian Zhu (8):
  KVM: arm64: Set DBM bit for writable PTEs
  KVM: arm64: Scan PTEs to sync dirty log
  KVM: arm64: Modify stage2 young mechanism to support hw DBM
  KVM: arm64: Save stage2 PTE dirty status if it is covered
  KVM: arm64: Steply write protect page table by mask bit
  KVM: arm64: Add KVM_CAP_ARM_HW_DIRTY_LOG capability
  KVM: arm64: Sync dirty log parallel
  KVM: Omit dirty log sync in log clear if initially all set

 arch/arm64/include/asm/kvm_host.h |   5 +
 arch/arm64/include/asm/kvm_mmu.h  |  43 ++++-
 arch/arm64/kvm/arm.c              |  45 ++++-
 arch/arm64/kvm/mmu.c              | 307 ++++++++++++++++++++++++++++--
 arch/arm64/kvm/reset.c            |   5 +
 include/uapi/linux/kvm.h          |   1 +
 tools/include/uapi/linux/kvm.h    |   1 +
 virt/kvm/kvm_main.c               |   3 +-
 8 files changed, 389 insertions(+), 21 deletions(-)
```
#### [kvm-unit-tests PATCH v10 0/9] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Thu Jul  2 16:31:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11639589
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4053013B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:31:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C8562084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:31:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726575AbgGBQbb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 12:31:31 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:24238 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726199AbgGBQb3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 2 Jul 2020 12:31:29 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 062GUZno170194;
        Thu, 2 Jul 2020 12:31:27 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 320t3gn1pn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 12:31:27 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 062GUbUk170491;
        Thu, 2 Jul 2020 12:31:26 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0b-001b2d01.pphosted.com with ESMTP id 320t3gn1ny-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 12:31:26 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 062GQQOv032129;
        Thu, 2 Jul 2020 16:31:24 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma02fra.de.ibm.com with ESMTP id 31wwr7tynx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 16:31:24 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 062GU2r653412218
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 2 Jul 2020 16:30:02 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7657911C050;
        Thu,  2 Jul 2020 16:31:22 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EA0E111C058;
        Thu,  2 Jul 2020 16:31:21 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.146.43])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  2 Jul 2020 16:31:21 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v10 0/9] s390x: Testing the Channel Subsystem
 I/O
Date: Thu,  2 Jul 2020 18:31:11 +0200
Message-Id: <1593707480-23921-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-02_09:2020-07-02,2020-07-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 impostorscore=0 mlxlogscore=999 bulkscore=0
 cotscore=-2147483648 adultscore=0 phishscore=0 clxscore=1015 mlxscore=0
 priorityscore=1501 spamscore=0 suspectscore=1 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007020111
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All,

Goal of the series is to have a framework to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test program to define its own
interrupt handler. We need to do special work under interrupt like acknowledging
the interrupt.
  
This series presents three tests:
- Enumeration:
        The CSS is enumerated using the STSCH instruction recursively on all
        potentially existing channels.
        Keeping the first channel found as a reference for future use.
        Checks STSCH
 
- Enable:
        If the enumeration succeeded the tests enables the reference
        channel with MSCH and verifies with STSCH that the channel is
        effectively enabled, retrying a predefined count on failure
	to enable the channel
        Checks MSCH       
 
- Sense:
        If the channel is enabled this test sends a SENSE_ID command
        to the reference channel, analyzing the answer and expecting
        the Control unit type being 0x3832, a.k.a. virtio-ccw.
        Checks SSCH(READ) and IO-IRQ

Note:
- The following 5 patches are general usage and may be pulled first:
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt

- These 4 patches are really I/O oriented:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

Regards,
Pierre

Pierre Morel (9):
  s390x: saving regs for interrupts
  s390x: I/O interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: clock and delays calculations
  s390x: define function to wait for interrupt
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt

 lib/s390x/asm/arch_def.h |  14 ++
 lib/s390x/asm/time.h     |  50 +++++++
 lib/s390x/css.h          | 286 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 152 +++++++++++++++++++++
 lib/s390x/css_lib.c      | 277 +++++++++++++++++++++++++++++++++++++
 lib/s390x/interrupt.c    |  23 +++-
 lib/s390x/interrupt.h    |   8 ++
 s390x/Makefile           |   3 +
 s390x/css.c              | 162 ++++++++++++++++++++++
 s390x/cstart64.S         |  41 +++++-
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 12 files changed, 1018 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
