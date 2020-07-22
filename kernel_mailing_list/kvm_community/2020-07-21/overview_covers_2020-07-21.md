

#### [patch V4 00/15] entry, x86, kvm: Generic entry/exit functionality
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
From patchwork Tue Jul 21 10:57:06 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11675481
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 311371392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:10:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 190DF2077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 11:10:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="oAtueUlx";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="aN0PaId2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729417AbgGULIg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 07:08:36 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51316 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727103AbgGULIg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 07:08:36 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 6652CC061794;
        Tue, 21 Jul 2020 04:08:36 -0700 (PDT)
Message-Id: <20200721105706.030914876@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1595329714;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=53zegY7mPEwf7yBdREoLaX8m4OIEIYVRvPFk/Ji8ifI=;
        b=oAtueUlx7L5mcMuTzK9Fyk01+ONyRlDDzaKEZMKXpTGihVqmHte1vgKJzN/yuPijPVDCVw
        qBBgJNDyfupd1tZRc/UlBpJr9QawbI55gUfu/h1dIzajsr7kT/iGbSdhtejBvuzKwfG2VS
        wUjq01pUDaHX/2rHpryrIybzygLWcadU2JuGgDsfkTZFz4bcB6NeOeSYS3DjFTxh0pHlpC
        Oqes7nJpC5BQCBVWmim0Bsb1rO2CAsXXAqp+zbzAp+uBG0UoKP1QZioyuOoOnPjtQlcSCG
        kXVGHPPqQGwEnpr/hec9QqGvYKuoEjc0068mh9sNSOCYuQcWYRMs1K4EM+TLRA==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1595329714;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:content-transfer-encoding:content-transfer-encoding;
        bh=53zegY7mPEwf7yBdREoLaX8m4OIEIYVRvPFk/Ji8ifI=;
        b=aN0PaId2u7QHeZPGnNEBzgCrSZbPEA/HKpmS04VML9CmSi9B9/tnTIu4LdOYuWDT3CdpyQ
        hQfrjZWYOpf8nxCw==
Date: Tue, 21 Jul 2020 12:57:06 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, linux-arch@vger.kernel.org,
        Will Deacon <will@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
        Mark Rutland <mark.rutland@arm.com>,
        Kees Cook <keescook@chromium.org>,
        Keno Fischer <keno@juliacomputing.com>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        Gabriel Krisman Bertazi <krisman@collabora.com>
Subject: [patch V4 00/15] entry, x86, kvm: Generic entry/exit functionality
 for host and guest
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is the 4rd version of generic entry/exit functionality for host and
guest.

The 3rd version is available here:

    https://lore.kernel.org/r/20200716182208.180916541@linutronix.de

Changes vs. V3:

  - Drop the architecture wrappers for seccomp and audit (Kees)
  - Move the user return notifier out of the loop
  - Bring I/O bitmap handling back
  - Use the existing helpers to get syscall number and return value
  - Drop dummy defines for SYSCALL_TRACE and NOTIFY_RESUME as all
    architectures define them
  - Fix TIF_SYSCALL_AUDIT dummy define
  - Adjust comments

The patches depend on:

    git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git x86/entry

The lot is also available from git:

    git://git.kernel.org/pub/scm/linux/kernel/git/tglx/devel.git x86/entry

Thanks,

	tglx
---
 arch/Kconfig                        |    3 
 arch/x86/Kconfig                    |    1 
 arch/x86/entry/common.c             |  632 ++----------------------------------
 arch/x86/entry/entry_32.S           |    2 
 arch/x86/entry/entry_64.S           |    2 
 arch/x86/include/asm/entry-common.h |   76 ++++
 arch/x86/include/asm/idtentry.h     |   39 --
 arch/x86/include/asm/ptrace.h       |    5 
 arch/x86/include/asm/signal.h       |    1 
 arch/x86/include/asm/thread_info.h  |    5 
 arch/x86/kernel/cpu/mce/core.c      |    4 
 arch/x86/kernel/kvm.c               |    6 
 arch/x86/kernel/signal.c            |    3 
 arch/x86/kernel/traps.c             |   24 -
 arch/x86/kvm/Kconfig                |    1 
 arch/x86/kvm/vmx/vmx.c              |   11 
 arch/x86/kvm/x86.c                  |   15 
 arch/x86/mm/fault.c                 |    6 
 include/linux/entry-common.h        |  372 +++++++++++++++++++++
 include/linux/entry-kvm.h           |   80 ++++
 include/linux/kvm_host.h            |    8 
 include/linux/seccomp.h             |    1 
 kernel/Makefile                     |    1 
 kernel/entry/Makefile               |    4 
 kernel/entry/common.c               |  374 +++++++++++++++++++++
 kernel/entry/kvm.c                  |   51 ++
 virt/kvm/Kconfig                    |    3 
 27 files changed, 1067 insertions(+), 663 deletions(-)
```
#### [PATCH RFC v2 00/18] Add VFIO mediated device support and DEV-MSI
##### From: Dave Jiang <dave.jiang@intel.com>

```c
From patchwork Tue Jul 21 16:02:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Dave Jiang <dave.jiang@intel.com>
X-Patchwork-Id: 11675947
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8A8E1618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 16:02:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 72200207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 16:02:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728281AbgGUQCT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 12:02:19 -0400
Received: from mga06.intel.com ([134.134.136.31]:36437 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726919AbgGUQCS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 12:02:18 -0400
IronPort-SDR: 
 Ikg01JIzU+9DmhvfZXnh7DgMu7ahluJn9lmpdhH04xbEGB/PhPB9MKk1kM+BU7wvrlppmOIs3c
 cC7KQvKplMWg==
X-IronPort-AV: E=McAfee;i="6000,8403,9689"; a="211707972"
X-IronPort-AV: E=Sophos;i="5.75,379,1589266800";
   d="scan'208";a="211707972"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Jul 2020 09:02:16 -0700
IronPort-SDR: 
 JMHzcjiPLeplMQlR4VYW9anJCqZ4TvwDn6hOSJgme6gv93lU3gu/moN1zQvfsvX+pglT4mvjLF
 beoMO0yTIbDA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,379,1589266800";
   d="scan'208";a="271755813"
Received: from djiang5-desk3.ch.intel.com ([143.182.136.137])
  by fmsmga008.fm.intel.com with ESMTP; 21 Jul 2020 09:02:15 -0700
Subject: [PATCH RFC v2 00/18] Add VFIO mediated device support and DEV-MSI
 support for the idxd driver
From: Dave Jiang <dave.jiang@intel.com>
To: vkoul@kernel.org, megha.dey@intel.com, maz@kernel.org,
        bhelgaas@google.com, rafael@kernel.org, gregkh@linuxfoundation.org,
        tglx@linutronix.de, hpa@zytor.com, alex.williamson@redhat.com,
        jacob.jun.pan@intel.com, ashok.raj@intel.com, jgg@mellanox.com,
        yi.l.liu@intel.com, baolu.lu@intel.com, kevin.tian@intel.com,
        sanjay.k.kumar@intel.com, tony.luck@intel.com, jing.lin@intel.com,
        dan.j.williams@intel.com, kwankhede@nvidia.com,
        eric.auger@redhat.com, parav@mellanox.com, jgg@mellanox.com,
        rafael@kernel.org, dave.hansen@intel.com, netanelg@mellanox.com,
        shahafs@mellanox.com, yan.y.zhao@linux.intel.com,
        pbonzini@redhat.com, samuel.ortiz@intel.com, mona.hossain@intel.com
Cc: dmaengine@vger.kernel.org, linux-kernel@vger.kernel.org,
        x86@kernel.org, linux-pci@vger.kernel.org, kvm@vger.kernel.org
Date: Tue, 21 Jul 2020 09:02:15 -0700
Message-ID: 
 <159534667974.28840.2045034360240786644.stgit@djiang5-desk3.ch.intel.com>
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v2:
IMS (now dev-msi):
With recommendations from Jason/Thomas/Dan on making IMS more generic:
Pass a non-pci generic device(struct device) for IMS management instead of mdev
Remove all references to mdev and symbol_get/put
Remove all references to IMS in common code and replace with dev-msi
remove dynamic allocation of platform-msi interrupts: no groups,no new msi list or list helpers
Create a generic dev-msi domain with and without interrupt remapping enabled.
Introduce dev_msi_domain_alloc_irqs and dev_msi_domain_free_irqs apis

mdev: 
Removing unrelated bits from SVA enabling that’s not necessary for the submission. (Kevin)
Restructured entire mdev driver series to make reviewing easier (Kevin)
Made rw emulation more robust (Kevin)
Removed uuid wq type and added single dedicated wq type (Kevin)
Locking fixes for vdev (Yan Zhao)
VFIO MSIX trigger fixes (Yan Zhao)

Link to previous discussions with Jason:
https://lore.kernel.org/lkml/57296ad1-20fe-caf2-b83f-46d823ca0b5f@intel.com/
The emulation part that can be moved to user space is very small due to the majority of the
emulations being control bits and need to reside in the kernel. We can revisit the necessity of
moving the small emulation part to userspace and required architectural changes at a later time.

This RFC series has been reviewed by Dan Williams <dan.j.williams@intel.com>

The actual code can be independent of the stage 2 driver code submission that adds support for SVM,
ENQCMD(S), PASID, and shared workqueues. This code series will match the support of the 5.6 kernel
(stage 1) driver but on guest. The code is dependent on Baolu’s iommu aux-domain API extensions
patches that’s still in process of being reviewed:
https://lkml.org/lkml/2020/7/14/48

Stage 1 of the driver has been accepted in v5.6 kernel. It supports dedicated workqueue (wq)
without Shared Virtual Memory (SVM) support. Stage 2 supports shared wq and SVM. It is pending
upstream review and targeting kernel v5.9.

VFIO mediated device framework allows vendor drivers to wrap a portion of device resources into
virtual devices (mdev). Each mdev can be assigned to different guest using the same set of VFIO
uAPIs as assigning a physical device. Accessing to the mdev resource is served with mixed policies.
For example, vendor drivers typically mark data-path interface as pass-through for fast guest
operations, and then trap-and-mediate the control-path interface to avoid undesired interference
between mdevs. Some level of emulation is necessary behind vfio mdev to compose the virtual device
interface. 

This series brings mdev to idxd driver to enable Intel Scalable IOV (SIOV), a hardware-assisted
mediated pass-through technology. SIOV makes each DSA wq independently assignable through
PASID-granular resource/DMA isolation. It helps improve scalability and reduces mediation
complexity against purely software-based mdev implementations. Each assigned wq is configured by
host and exposed to the guest in a read-only configuration mode, which allows the guest to use the
wq w/o additional setup. This design greatly reduces the emulation bits to focus on handling
commands from guests.

Introducing mdev types “1dwq” type. This mdev type allows allocation of a single dedicated wq from
available dedicated wqs. After a workqueue (wq) is enabled, the user will generate an uuid. On mdev
creation, the mdev driver code will find a dwq depending on the mdev type. When the create operation
is successful, the user generated uuid can be passed to qemu. When the guest boots up, it should
discover a DSA device when doing PCI discovery.

For example of “1dwq” type:
1. Enable wq with “mdev” wq type
2. A user generated uuid.
3. The uuid is written to the mdev class sysfs path:
echo $UUID > /sys/class/mdev_bus/0000\:00\:0a.0/mdev_supported_types/idxd-wq/create
4. Pass the following parameter to qemu:
"-device vfio-pci,sysfsdev=/sys/bus/pci/devices/0000:00:0a.0/$UUID"
 
The wq exported through mdev will have the read only config bit set for configuration. This means
that the device does not require the typical configuration. After enabling the device, the user
must set the WQ type and name. That is all is necessary to enable the WQ and start using it. The
single wq configuration is not the only way to create the mdev. Multi wqs support for mdev will be
in the future works.
 
The mdev utilizes Interrupt Message Store or IMS[3], a device-specific MSI implementation, instead
of MSIX for interrupts for the guest. This preserves MSIX for host usages and also allows a
significantly larger number of interrupt vectors for guest usage.

The idxd driver implements IMS as on-device memory mapped unified storage. Each interrupt message
is stored as a DWORD size data payload and a 64-bit address (same as MSI-X). Access to the IMS is
through the host idxd driver.

This patchset extends the existing platform-msi framework (which provides a generic mechanism to
support non-PCI compliant MSI interrupts) to benefit any driver which wants to allocate
msi-like(dev-msi) interrupts and provide its own ops functions (mask/unmask etc.)

Call-back functions defined by the kernel and implemented by the driver are used to
1. program the interrupt addr/data values instead of the kernel directly programming them.
2. mask/unmask the interrupt source

The kernel can specify the requirements for these callback functions (e.g., the driver is not
expected to block, or not expected to take a lock in the callback function).

Support for 2 new IRQ chip/domain is added(with and without IRQ_REMAP support- DEV-MSI/IR-DEV-MSI).

[1]: https://lore.kernel.org/lkml/157965011794.73301.15960052071729101309.stgit@djiang5-desk3.ch.intel.com/
[2]: https://software.intel.com/en-us/articles/intel-sdm
[3]: https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[4]: https://software.intel.com/en-us/download/intel-data-streaming-accelerator-preliminary-architecture-specification
[5]: https://01.org/blogs/2019/introducing-intel-data-streaming-accelerator
[6]: https://intel.github.io/idxd/
[7]: https://github.com/intel/idxd-driver idxd-stage2.5
---

Dave Jiang (13):
      dmaengine: idxd: add support for readonly config devices
      dmaengine: idxd: add interrupt handle request support
      dmaengine: idxd: add DEV-MSI support in base driver
      dmaengine: idxd: add device support functions in prep for mdev
      dmaengine: idxd: add basic mdev registration and helper functions
      dmaengine: idxd: add emulation rw routines
      dmaengine: idxd: prep for virtual device commands
      dmaengine: idxd: virtual device commands emulation
      dmaengine: idxd: ims setup for the vdcm
      dmaengine: idxd: add mdev type as a new wq type
      dmaengine: idxd: add dedicated wq mdev type
      dmaengine: idxd: add new wq state for mdev
      dmaengine: idxd: add error notification from host driver to mediated device

Jing Lin (1):
      dmaengine: idxd: add ABI documentation for mediated device support

Megha Dey (4):
      platform-msi: Introduce platform_msi_ops
      irq/dev-msi: Add support for a new DEV_MSI irq domain
      irq/dev-msi: Create IR-DEV-MSI irq domain
      irq/dev-msi: Introduce APIs to allocate/free dev-msi interrupts


 Documentation/ABI/stable/sysfs-driver-dma-idxd |   15 
 arch/x86/include/asm/hw_irq.h                  |    6 
 arch/x86/kernel/apic/msi.c                     |   12 
 drivers/base/Kconfig                           |    7 
 drivers/base/Makefile                          |    1 
 drivers/base/dev-msi.c                         |  170 ++++
 drivers/base/platform-msi.c                    |   62 +
 drivers/base/platform-msi.h                    |   23 
 drivers/dma/Kconfig                            |    7 
 drivers/dma/idxd/Makefile                      |    2 
 drivers/dma/idxd/cdev.c                        |    6 
 drivers/dma/idxd/device.c                      |  266 +++++-
 drivers/dma/idxd/idxd.h                        |   62 +
 drivers/dma/idxd/ims.c                         |  174 ++++
 drivers/dma/idxd/ims.h                         |   17 
 drivers/dma/idxd/init.c                        |  100 ++
 drivers/dma/idxd/irq.c                         |    6 
 drivers/dma/idxd/mdev.c                        | 1106 ++++++++++++++++++++++++
 drivers/dma/idxd/mdev.h                        |  118 +++
 drivers/dma/idxd/registers.h                   |   24 -
 drivers/dma/idxd/submit.c                      |   37 +
 drivers/dma/idxd/sysfs.c                       |   55 +
 drivers/dma/idxd/vdev.c                        |  962 +++++++++++++++++++++
 drivers/dma/idxd/vdev.h                        |   28 +
 drivers/dma/mv_xor_v2.c                        |    6 
 drivers/dma/qcom/hidma.c                       |    6 
 drivers/iommu/arm-smmu-v3.c                    |    6 
 drivers/iommu/intel/irq_remapping.c            |   11 
 drivers/irqchip/irq-mbigen.c                   |    8 
 drivers/irqchip/irq-mvebu-icu.c                |    6 
 drivers/mailbox/bcm-flexrm-mailbox.c           |    6 
 drivers/perf/arm_smmuv3_pmu.c                  |    6 
 include/linux/intel-iommu.h                    |    1 
 include/linux/irqdomain.h                      |   11 
 include/linux/msi.h                            |   35 +
 include/uapi/linux/idxd.h                      |    2 
 36 files changed, 3270 insertions(+), 100 deletions(-)
 create mode 100644 drivers/base/dev-msi.c
 create mode 100644 drivers/base/platform-msi.h
 create mode 100644 drivers/dma/idxd/ims.c
 create mode 100644 drivers/dma/idxd/ims.h
 create mode 100644 drivers/dma/idxd/mdev.c
 create mode 100644 drivers/dma/idxd/mdev.h
 create mode 100644 drivers/dma/idxd/vdev.c
 create mode 100644 drivers/dma/idxd/vdev.h

--
```
#### [PATCH v2 0/5] KVM_{GET,SET}_TSC_OFFSET ioctls
##### From: Oliver Upton <oupton@google.com>

```c
From patchwork Tue Jul 21 20:18:09 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11676571
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8F6DF1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 20:18:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 710A820717
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 20:18:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="sRXFES6q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730385AbgGUUSW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 16:18:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52324 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726029AbgGUUSV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jul 2020 16:18:21 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C18CAC061794
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 13:18:21 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id 8so26683126ybc.23
        for <kvm@vger.kernel.org>; Tue, 21 Jul 2020 13:18:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=TLYIx65uBhH8tKMZC20n1CzNlboYevH1hAYzToPXQyo=;
        b=sRXFES6q0Ey0/IU/nUy9UtsoyTTOrJ5vMzzf30Xx7HBy4yPhCiClOfbLXTSge3jGW4
         vd4/h+wvkflMMufw78SHihakxCqgrw0Lh0IAzftfaE+KbaGasqS+oufao0HVWtVgfTZ6
         7IUugwUAnDptaqm19MCiTNSKEJKjo5sMU0DcF3JtnU10sKLxOnwQVqK6SCoHFIz0gtmJ
         /5GwwZYWsygKYhB2qhvSQn4PU/yJ+Cpr9hRxMcx9Z3vTFaZeuNOmoBQaytE6+S9k+Eac
         et7GtpplD6WRZmVPOHcJAhvinaQFo5+FU+Xx2NnOgBgkRjDs13agKpaQbYoMWhttyrxO
         JE8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=TLYIx65uBhH8tKMZC20n1CzNlboYevH1hAYzToPXQyo=;
        b=C7Wi0H0fFuZZB42+FZwcWN4p9WZAGVoTc0Xs4Odja7mWpvsQ3xdrn83gD5ELYVyYcM
         pIxfRiYt3Jnwp6jHXQCNpxayQ8MOmT56bLbugnI9+FgKXliXKS8x11sw/2wz3cgKIrV/
         4obK4bqbanGLkMf+aLp0wXWSSfUEKQfgDbAwiF7yd2H2ODxvG64klTCBzCmNLNERoTWh
         nKBRj3d8mHtZSUXyJ1bYMHzkD3I8MhFwUEGr1S4LNUtoG4PgZFk87WyI3yD5Nh/CVYAN
         hbWDWuPk+4EuKP4LMs1Y2ly1uo8l6/I5IJHMq3xNyd8qyfAjg7toL0p9S7ItvesUWz2K
         lk/g==
X-Gm-Message-State: AOAM53242kkuX8QT/hyAzNUXx9dkkTzVqqPQM7XDqUImO8T1dEy8x0Ce
        x168WctY0w1pKr16wfxBh2UxiyaBIpRdsxo/kOTE8aOGezMxq7egxu5z0CmDf1cazdpOihOoKDe
        jjlYqLs53iTfT+gLuB5IxzYej+aTtFACDAN5K8bf4bCj+wR4HXFVAesTJXg==
X-Google-Smtp-Source: 
 ABdhPJzvO8GTRdE8c2WMbR+gJ3+WIZYQ0HJzgJ1iT2yUDXY11NGWU5ddaeAjCanDq9QislIMkySk89cs+ts=
X-Received: by 2002:a25:ae4f:: with SMTP id
 g15mr45255291ybe.441.1595362699898;
 Tue, 21 Jul 2020 13:18:19 -0700 (PDT)
Date: Tue, 21 Jul 2020 20:18:09 +0000
Message-Id: <20200721201814.2340705-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.rc0.142.g3c755180ce-goog
Subject: [PATCH v2 0/5] KVM_{GET,SET}_TSC_OFFSET ioctls
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Peter Hornyack <peterhornyack@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To date, VMMs have typically restored the guest's TSCs by value using
the KVM_SET_MSRS ioctl for each vCPU. However, restoring the TSCs by
value introduces some challenges with synchronization as the TSCs
continue to tick throughout the restoration process. As such, KVM has
some heuristics around TSC writes to infer whether or not the guest or
host is attempting to synchronize the TSCs.

Instead of guessing at the intentions of a VMM, it'd be better to
provide an interface that allows for explicit synchronization of the
guest's TSCs. To that end, this series introduces the
KVM_{GET,SET}_TSC_OFFSET ioctls, yielding control of the TSC offset to
userspace.

v1 => v2:
 - Added clarification to the documentation of KVM_SET_TSC_OFFSET to
   indicate that it can be used instead of an IA32_TSC MSR restore
   through KVM_SET_MSRS
 - Fixed KVM_SET_TSC_OFFSET to participate in the existing TSC
   synchronization heuristics, thereby enabling the KVM masterclock when
   all vCPUs are in phase.

Oliver Upton (4):
  kvm: x86: refactor masterclock sync heuristics out of kvm_write_tsc
  kvm: vmx: check tsc offsetting with nested_cpu_has()
  selftests: kvm: use a helper function for reading cpuid
  selftests: kvm: introduce tsc_offset_test

Peter Hornyack (1):
  kvm: x86: add KVM_{GET,SET}_TSC_OFFSET ioctls

 Documentation/virt/kvm/api.rst                |  31 ++
 arch/x86/include/asm/kvm_host.h               |   1 +
 arch/x86/kvm/vmx/vmx.c                        |   2 +-
 arch/x86/kvm/x86.c                            | 147 ++++---
 include/uapi/linux/kvm.h                      |   5 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/test_util.h |   3 +
 .../selftests/kvm/include/x86_64/processor.h  |  15 +
 .../selftests/kvm/include/x86_64/svm_util.h   |  10 +-
 .../selftests/kvm/include/x86_64/vmx.h        |   9 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   1 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |  11 +
 .../selftests/kvm/x86_64/tsc_offset_test.c    | 362 ++++++++++++++++++
 14 files changed, 550 insertions(+), 49 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/tsc_offset_test.c
```
#### [PATCH v9 00/84] VM introspection
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From patchwork Tue Jul 21 21:07:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 11676751
Return-Path: <SRS0=uGOU=BA=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E87F2138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 21:18:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D315020720
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jul 2020 21:18:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731174AbgGUVS0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jul 2020 17:18:26 -0400
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:37850 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1731210AbgGUVQB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jul 2020 17:16:01 -0400
Received: from smtp.bitdefender.com (smtp02.buh.bitdefender.net [10.17.80.76])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 030ED30747C8;
        Wed, 22 Jul 2020 00:09:19 +0300 (EEST)
Received: from localhost.localdomain (unknown [91.199.104.27])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 81723303EF1A;
        Wed, 22 Jul 2020 00:09:18 +0300 (EEST)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>,
 Edwin Zhai <edwin.zhai@intel.com>, Jan Kiszka <jan.kiszka@siemens.com>,
 Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>,
 Mathieu Tarral <mathieu.tarral@protonmail.com>,
 Patrick Colp <patrick.colp@oracle.com>,
 =?utf-8?q?Samuel_Laur=C3=A9n?= <samuel.lauren@iki.fi>,
 Stefan Hajnoczi <stefanha@redhat.com>, Tamas K Lengyel <tamas@tklengyel.com>,
 Weijiang Yang <weijiang.yang@intel.com>, Yu C Zhang <yu.c.zhang@intel.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Joerg Roedel <joro@8bytes.org>, Vitaly Kuznetsov <vkuznets@redhat.com>,
 Wanpeng Li <wanpengli@tencent.com>, Jim Mattson <jmattson@google.com>
Subject: [PATCH v9 00/84] VM introspection
Date: Wed, 22 Jul 2020 00:07:58 +0300
Message-Id: <20200721210922.7646-1-alazar@bitdefender.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The KVM introspection subsystem provides a facility for applications
running on the host or in a separate VM, to control the execution of
other VMs (pause, resume, shutdown), query the state of the vCPUs (GPRs,
MSRs etc.), alter the page access bits in the shadow page tables (only
for the hardware backed ones, eg. Intel's EPT) and receive notifications
when events of interest have taken place (shadow page table level faults,
key MSR writes, hypercalls etc.). Some notifications can be responded
to with an action (like preventing an MSR from being written), others
are mere informative (like breakpoint events which can be used for
execution tracing).  With few exceptions, all events are optional. An
application using this subsystem will explicitly register for them.

The use case that gave way for the creation of this subsystem is to
monitor the guest OS and as such the ABI/API is highly influenced by how
the guest software (kernel, applications) sees the world. For example,
some events provide information specific for the host CPU architecture
(eg. MSR_IA32_SYSENTER_EIP) merely because its leveraged by guest software
to implement a critical feature (fast system calls).

At the moment, the target audience for KVMI are security software authors
that wish to perform forensics on newly discovered threats (exploits)
or to implement another layer of security like preventing a large set
of kernel rootkits simply by "locking" the kernel image in the shadow
page tables (ie. enforce .text r-x, .rodata rw- etc.). It's the latter
case that made KVMI a separate subsystem, even though many of these
features are available in the device manager. The ability to build a
security application that does not interfere (in terms of performance)
with the guest software asks for a specialized interface that is designed
for minimum overhead.

This patch series is based on kvm/master,
commit 3d9fdc252b52 ("KVM: MIPS: Fix build errors for 32bit kernel").

The previous version (v8) can be read here:

	https://lore.kernel.org/kvm/20200330101308.21702-1-alazar@bitdefender.com/

Patches 1-36: make preparatory changes

Patches 38-82: add basic introspection capabilities

Patch 83: support introspection tools that write-protect guest page tables

Patch 84: notify the introspection tool even on emulation failures
          (when the read/write callbacks used by the emulator,
           kvm_page_preread/kvm_page_prewrite, are not invoked)

Changes since v8:
  - rebase on 5.8
  - fix non-x86 builds (avoid including the UAPI headers from kvmi_host.h)
  - fix the clean-up for KVMI_VCPU_SINGLESTEP [Mathieu]
  - extend KVMI_VM_SET_PAGE_ACCESS with the 'visible' option
  - improve KVMI_VM_GET_MAX_GFN (skip read-only, invalid or non-user memslots)
  - add KVMI_VM_CONTROL_CLEANUP [Tamas, Mathieu]
  - add KVMI_VCPU_GET_XCR and KVMI_VCPU_SET_XSAVE (SSE emulation)
  - move KVM_REQ_INTROSPECTION in the range of arch-independent requests
  - better split of x86 vs arch-independent code
  - cover more error codes with tools/testing/selftests/kvm/x86_64/kvmi_test.c
  - remove more error messages and close the introspection connection
    when an error code can't be sent back or it doesn't make sense to send it
  - other small changes (code refactoring, message validation, etc.).

Adalbert Lazăr (22):
  KVM: UAPI: add error codes used by the VM introspection code
  KVM: add kvm_vcpu_kick_and_wait()
  KVM: doc: fix the hypercall numbering
  KVM: x86: add .control_cr3_intercept() to struct kvm_x86_ops
  KVM: x86: add .desc_ctrl_supported()
  KVM: x86: add .control_desc_intercept()
  KVM: x86: export kvm_vcpu_ioctl_x86_set_xsave()
  KVM: introspection: add hook/unhook ioctls
  KVM: introspection: add permission access ioctls
  KVM: introspection: add the read/dispatch message function
  KVM: introspection: add KVMI_GET_VERSION
  KVM: introspection: add KVMI_VM_CHECK_COMMAND and KVMI_VM_CHECK_EVENT
  KVM: introspection: add KVMI_EVENT_UNHOOK
  KVM: introspection: add KVMI_VM_CONTROL_EVENTS
  KVM: introspection: add a jobs list to every introspected vCPU
  KVM: introspection: add KVMI_VCPU_PAUSE
  KVM: introspection: add KVMI_EVENT_PAUSE_VCPU
  KVM: introspection: add KVMI_VM_CONTROL_CLEANUP
  KVM: introspection: add KVMI_VCPU_GET_XCR
  KVM: introspection: add KVMI_VCPU_SET_XSAVE
  KVM: introspection: extend KVMI_GET_VERSION with struct kvmi_features
  KVM: introspection: add KVMI_VCPU_TRANSLATE_GVA

Marian Rotariu (1):
  KVM: introspection: add KVMI_VCPU_GET_CPUID

Mathieu Tarral (1):
  signal: export kill_pid_info()

Mihai Donțu (35):
  KVM: x86: add kvm_arch_vcpu_get_regs() and kvm_arch_vcpu_get_sregs()
  KVM: x86: avoid injecting #PF when emulate the VMCALL instruction
  KVM: x86: add .control_msr_intercept()
  KVM: x86: vmx: use a symbolic constant when checking the exit
    qualifications
  KVM: x86: save the error code during EPT/NPF exits handling
  KVM: x86: add .fault_gla()
  KVM: x86: add .spt_fault()
  KVM: x86: add .gpt_translation_fault()
  KVM: x86: extend kvm_mmu_gva_to_gpa_system() with the 'access'
    parameter
  KVM: x86: page track: provide all callbacks with the guest virtual
    address
  KVM: x86: page track: add track_create_slot() callback
  KVM: x86: page_track: add support for preread, prewrite and preexec
  KVM: x86: wire in the preread/prewrite/preexec page trackers
  KVM: introduce VM introspection
  KVM: introspection: add KVMI_VM_GET_INFO
  KVM: introspection: add KVMI_VM_READ_PHYSICAL/KVMI_VM_WRITE_PHYSICAL
  KVM: introspection: handle vCPU introspection requests
  KVM: introspection: handle vCPU commands
  KVM: introspection: add KVMI_VCPU_GET_INFO
  KVM: introspection: add the crash action handling on the event reply
  KVM: introspection: add KVMI_VCPU_CONTROL_EVENTS
  KVM: introspection: add KVMI_VCPU_GET_REGISTERS
  KVM: introspection: add KVMI_VCPU_SET_REGISTERS
  KVM: introspection: add KVMI_EVENT_HYPERCALL
  KVM: introspection: add KVMI_EVENT_BREAKPOINT
  KVM: introspection: add KVMI_VCPU_CONTROL_CR and KVMI_EVENT_CR
  KVM: introspection: add KVMI_VCPU_INJECT_EXCEPTION + KVMI_EVENT_TRAP
  KVM: introspection: add KVMI_EVENT_XSETBV
  KVM: introspection: add KVMI_VCPU_GET_XSAVE
  KVM: introspection: add KVMI_VCPU_GET_MTRR_TYPE
  KVM: introspection: add KVMI_VCPU_CONTROL_MSR and KVMI_EVENT_MSR
  KVM: introspection: add KVMI_VM_SET_PAGE_ACCESS
  KVM: introspection: add KVMI_EVENT_PF
  KVM: introspection: emulate a guest page table walk on SPT violations
    due to A/D bit updates
  KVM: x86: call the page tracking code on emulation failure

Mircea Cîrjaliu (2):
  KVM: x86: disable gpa_available optimization for fetch and page-walk
    SPT violations
  KVM: introspection: add vCPU related data

Nicușor Cîțu (21):
  KVM: x86: add kvm_arch_vcpu_set_regs()
  KVM: x86: add .bp_intercepted() to struct kvm_x86_ops
  KVM: x86: add .cr3_write_intercepted()
  KVM: svm: add support for descriptor-table exits
  KVM: x86: add .desc_intercepted()
  KVM: x86: export .msr_write_intercepted()
  KVM: x86: use MSR_TYPE_R, MSR_TYPE_W and MSR_TYPE_RW with AMD
  KVM: svm: pass struct kvm_vcpu to set_msr_interception()
  KVM: vmx: pass struct kvm_vcpu to the intercept msr related functions
  KVM: x86: add .control_singlestep()
  KVM: x86: export kvm_arch_vcpu_set_guest_debug()
  KVM: x86: export kvm_inject_pending_exception()
  KVM: x86: export kvm_vcpu_ioctl_x86_get_xsave()
  KVM: introspection: add cleanup support for vCPUs
  KVM: introspection: restore the state of #BP interception on unhook
  KVM: introspection: restore the state of CR3 interception on unhook
  KVM: introspection: add KVMI_EVENT_DESCRIPTOR
  KVM: introspection: restore the state of descriptor-table register
    interception on unhook
  KVM: introspection: restore the state of MSR interception on unhook
  KVM: introspection: add KVMI_VCPU_CONTROL_SINGLESTEP
  KVM: introspection: add KVMI_EVENT_SINGLESTEP

Ștefan Șicleru (2):
  KVM: add kvm_get_max_gfn()
  KVM: introspection: add KVMI_VM_GET_MAX_GFN

 Documentation/virt/kvm/api.rst                |  149 ++
 Documentation/virt/kvm/hypercalls.rst         |   39 +-
 Documentation/virt/kvm/kvmi.rst               | 1546 ++++++++++++
 arch/x86/include/asm/kvm_host.h               |   41 +-
 arch/x86/include/asm/kvm_page_track.h         |   71 +-
 arch/x86/include/asm/kvmi_host.h              |   96 +
 arch/x86/include/asm/vmx.h                    |    2 +
 arch/x86/include/uapi/asm/kvmi.h              |  153 ++
 arch/x86/kvm/Kconfig                          |   13 +
 arch/x86/kvm/Makefile                         |    2 +
 arch/x86/kvm/emulate.c                        |    4 +
 arch/x86/kvm/kvm_emulate.h                    |    1 +
 arch/x86/kvm/kvmi.c                           | 1413 +++++++++++
 arch/x86/kvm/mmu.h                            |    4 +
 arch/x86/kvm/mmu/mmu.c                        |  161 +-
 arch/x86/kvm/mmu/page_track.c                 |  142 +-
 arch/x86/kvm/svm/svm.c                        |  268 ++-
 arch/x86/kvm/svm/svm.h                        |   14 +
 arch/x86/kvm/vmx/capabilities.h               |    7 +-
 arch/x86/kvm/vmx/vmx.c                        |  261 +-
 arch/x86/kvm/vmx/vmx.h                        |    4 -
 arch/x86/kvm/x86.c                            |  305 ++-
 drivers/gpu/drm/i915/gvt/kvmgt.c              |    2 +-
 include/linux/kvm_host.h                      |   20 +
 include/linux/kvmi_host.h                     |  125 +
 include/uapi/linux/kvm.h                      |   20 +
 include/uapi/linux/kvm_para.h                 |    5 +
 include/uapi/linux/kvmi.h                     |  254 ++
 kernel/signal.c                               |    1 +
 tools/testing/selftests/kvm/Makefile          |    1 +
 .../testing/selftests/kvm/x86_64/kvmi_test.c  | 2143 +++++++++++++++++
 virt/kvm/introspection/kvmi.c                 | 1409 +++++++++++
 virt/kvm/introspection/kvmi_int.h             |  146 ++
 virt/kvm/introspection/kvmi_msg.c             | 1059 ++++++++
 virt/kvm/kvm_main.c                           |   92 +
 35 files changed, 9795 insertions(+), 178 deletions(-)
 create mode 100644 Documentation/virt/kvm/kvmi.rst
 create mode 100644 arch/x86/include/asm/kvmi_host.h
 create mode 100644 arch/x86/include/uapi/asm/kvmi.h
 create mode 100644 arch/x86/kvm/kvmi.c
 create mode 100644 include/linux/kvmi_host.h
 create mode 100644 include/uapi/linux/kvmi.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvmi_test.c
 create mode 100644 virt/kvm/introspection/kvmi.c
 create mode 100644 virt/kvm/introspection/kvmi_int.h
 create mode 100644 virt/kvm/introspection/kvmi_msg.c


base-commit: 3d9fdc252b52023260de1d12399cb3157ed28c07
CC: Edwin Zhai <edwin.zhai@intel.com>
CC: Jan Kiszka <jan.kiszka@siemens.com>
CC: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
CC: Mathieu Tarral <mathieu.tarral@protonmail.com>
CC: Patrick Colp <patrick.colp@oracle.com>
CC: Samuel Laurén <samuel.lauren@iki.fi>
CC: Stefan Hajnoczi <stefanha@redhat.com>
CC: Tamas K Lengyel <tamas@tklengyel.com>
CC: Weijiang Yang <weijiang.yang@intel.com>
CC: Yu C Zhang <yu.c.zhang@intel.com>
CC: Sean Christopherson <sean.j.christopherson@intel.com>
CC: Joerg Roedel <joro@8bytes.org>
CC: Vitaly Kuznetsov <vkuznets@redhat.com>
CC: Wanpeng Li <wanpengli@tencent.com>
CC: Jim Mattson <jmattson@google.com>
```
