

#### [PATCH 0/3] Misc patches for core_capabilites and split lock
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
From patchwork Mon Mar 23 02:56:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11452223
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8CA03913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 03:14:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BF5C206F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 03:14:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727025AbgCWDOj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 22 Mar 2020 23:14:39 -0400
Received: from mga11.intel.com ([192.55.52.93]:48945 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726979AbgCWDOj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 22 Mar 2020 23:14:39 -0400
IronPort-SDR: 
 /f7kq6CiHoI/ypBK6MGA4hJkG5inR1+EzZ73vEfWCsku+xUlFd4vt9ZO9Z8LSPWLVKU0FfCIY4
 7FM9nf20Ct7g==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Mar 2020 20:14:38 -0700
IronPort-SDR: 
 jFOHaTOf/TbRq7blbQLJLeIdgf9zS7fRX2leFtroj+bcuNV1wOz4P98aETg3smzoqnW9YHubT8
 CvJ+foaSKvwQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,294,1580803200";
   d="scan'208";a="292453678"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.161])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Mar 2020 20:14:37 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>
Cc: kvm@vger.kernel.org, qemu-devel@nongnu.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 0/3] Misc patches for core_capabilites and split lock
 detection
Date: Mon, 23 Mar 2020 10:56:55 +0800
Message-Id: <20200323025658.4540-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 renames core_capability to core_capabilities to align with the
latest SDM.

Patch 2 adds MSR_TEST_CTRL support.

Patch 3 prints info when guest is going to be killed due to split lock #AC

Xiaoyao Li (3):
  target/i386: Rename CORE_CAPABILITY to CORE_CAPABILITIES
  target/i386: Add support for TEST_CTRL MSR
  target/i386: Tell why guest exits to user space due to #AC

 target/i386/cpu.c     | 12 ++++++------
 target/i386/cpu.h     |  8 +++++---
 target/i386/kvm.c     | 30 +++++++++++++++++++++++++-----
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 56 insertions(+), 14 deletions(-)
```
#### [PATCH kernel v2 0/7] powerpc/powenv/ioda: Allow huge DMA window at
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
From patchwork Mon Mar 23 07:53:47 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11452429
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2C53917D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 08:01:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0B10D2074D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 08:01:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727521AbgCWIBC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 04:01:02 -0400
Received: from 107-174-27-60-host.colocrossing.com ([107.174.27.60]:50660
 "EHLO
        ozlabs.ru" rhost-flags-OK-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727508AbgCWIBB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 04:01:01 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id A1E87AE80013;
        Mon, 23 Mar 2020 03:52:14 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Fabiano Rosas <farosas@linux.ibm.com>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel v2 0/7] powerpc/powenv/ioda: Allow huge DMA window at
 4GB
Date: Mon, 23 Mar 2020 18:53:47 +1100
Message-Id: <20200323075354.93825-1-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here is an attempt to support bigger DMA space for devices
supporting DMA masks less than 59 bits (GPUs come into mind
first). POWER9 PHBs have an option to map 2 windows at 0
and select a windows based on DMA address being below or above
4GB.

This adds the "iommu=iommu_bypass" kernel parameter and
supports VFIO+pseries machine - current this requires telling
upstream+unmodified QEMU about this via
-global spapr-pci-host-bridge.dma64_win_addr=0x100000000
or per-phb property. 4/4 advertises the new option but
there is no automation around it in QEMU (should it be?).

For now it is either 1<<59 or 4GB mode; dynamic switching is
not supported (could be via sysfs).

This is a rebased version of
https://lore.kernel.org/kvm/20191202015953.127902-1-aik@ozlabs.ru/

The main change since v1 is that now it is 7 patches with
clearer separation of steps.


This is based on 6c90b86a745a "Merge tag 'mmc-v5.6-rc6' of git://git.kernel.org/pub/scm/linux/kernel/git/ulfh/mmc"

Please comment. Thanks.



Alexey Kardashevskiy (7):
  powerpc/powernv/ioda: Move TCE bypass base to PE
  powerpc/powernv/ioda: Rework for huge DMA window at 4GB
  powerpc/powernv/ioda: Allow smaller TCE table levels
  powerpc/powernv/phb4: Use IOMMU instead of bypassing
  powerpc/iommu: Add a window number to
    iommu_table_group_ops::get_table_size
  powerpc/powernv/phb4: Add 4GB IOMMU bypass mode
  vfio/spapr_tce: Advertise and allow a huge DMA windows at 4GB

 arch/powerpc/include/asm/iommu.h              |   3 +
 arch/powerpc/include/asm/opal-api.h           |   9 +-
 arch/powerpc/include/asm/opal.h               |   2 +
 arch/powerpc/platforms/powernv/pci.h          |   4 +-
 include/uapi/linux/vfio.h                     |   2 +
 arch/powerpc/platforms/powernv/npu-dma.c      |   1 +
 arch/powerpc/platforms/powernv/opal-call.c    |   2 +
 arch/powerpc/platforms/powernv/pci-ioda-tce.c |   4 +-
 arch/powerpc/platforms/powernv/pci-ioda.c     | 234 ++++++++++++++----
 drivers/vfio/vfio_iommu_spapr_tce.c           |  17 +-
 10 files changed, 213 insertions(+), 65 deletions(-)
```
#### [PATCH 0/9] vfio/fsl-mc: VFIO support for FSL-MC devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

The patches are dependent on some changes in the mc-bus (bus/fsl-mc)
driver. The changes were needed in order to re-use code and to export
some more functions that are needed by the VFIO driver.
Currenlty the mc-bus patches are under review:
https://www.spinics.net/lists/kernel/msg3447567.html

Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (8):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 660 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 221 ++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  56 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 959 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
