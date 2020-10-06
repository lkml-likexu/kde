

#### [PATCH 0/13] Fix per-domain IRQ affinity, allow >255 CPUs on x86
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Mon Oct  5 15:28:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11816825
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 667A2139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 15:28:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 14004207BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 15:28:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="azF5mWxl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727413AbgJEP2f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 11:28:35 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48630 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727393AbgJEP2b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Oct 2020 11:28:31 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F416DC0613CE;
        Mon,  5 Oct 2020 08:28:30 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:Date:Cc:To:
        From:Subject:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=dFkgso4DV7mAFdVY77wdMaL2nqc+vFfAseQkT62QKIY=;
 b=azF5mWxlJrzpErgwCEWLNfLYXr
        YkAk6vHonHHNCW+5GFVc8Y0AvfGHMGT0Q1PdHV/OoIXDFZyBJ3Y7avI8aVx6GMWhPMj8WQnM+8pGk
        55Q7BvnBYB+Z8gVvSQPaellG773V/aUWS4djpbdkwXzelgB1spHBfOdwA4/uVfzOOJ0Px8uglKekR
        bi32CnSwQJZaiyf88KslB3ZzTpPgVHeKxrRseZQkw87DPPsdV+05CT1x2oVcR6g4YQzmWoM3xnFQx
        s3C4vCGbMCXHwBvYJyG1+LFLH4bSeFPOZUp6H8QCZm29gljX9jQdCLMqJc+Bpls63Rz+pXo5OAhRh
        OGrWredQ==;
Received: from 54-240-197-232.amazon.com ([54.240.197.232]
 helo=u3832b3a9db3152.ant.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kPSPa-0004Fx-7o; Mon, 05 Oct 2020 15:28:26 +0000
Message-ID: <77e64f977f559412f62b467fd062d051ea288f14.camel@infradead.org>
Subject: [PATCH 0/13] Fix per-domain IRQ affinity, allow >255 CPUs on x86
 without IRQ remapping
From: David Woodhouse <dwmw2@infradead.org>
To: x86 <x86@kernel.org>
Cc: iommu <iommu@lists.linux-foundation.org>,
        kvm <kvm@vger.kernel.org>, linux-hyperv@vger.kernel.org,
        Paolo Bonzini <pbonzini@redhat.com>
Date: Mon, 05 Oct 2020 16:28:24 +0100
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linux currently refuses to use >255 CPUs on x86 unless it has interrupt
remapping. This is a bit gratuitous because it could use those extra
CPUs just fine; it just can't target external interrupts at them.

The only problem is that our generic IRQ domain code cann't cope with
the concept of domains which can only target a subset of CPUs.

The hyperv-iommu IRQ remapping driver works around this — not by
actually doing any remapping, but just returning -EINVAL if the
affinity is ever set to an unreachable CPU. This almost works, but ends
up being a bit late because irq_set_affinity_locked() doesn't call into
the irqchip driver immediately; the error only happens later.

This patch series implements a per-domain "maximum affinity" set and
uses it for the non-remapped IOAPIC and MSI domains on x86. As well as
allowing more CPUs to be used without interrupt remapping, this also
fixes the case where some IOAPICs or PCI devices aren't actually in
scope of any active IOMMU and are operating without remapping.

While we're at it, recognise that the 8-bit limit is a bit gratuitous
and a hypervisor could offer at least 15 bits of APIC ID in the IOAPIC
RTE and MSI address bits 11-5 without even needing to use remapping.

David Woodhouse (13):
      x86/apic: Use x2apic in guest kernels even with unusable CPUs.
      x86/msi: Only use high bits of MSI address for DMAR unit
      x86/ioapic: Handle Extended Destination ID field in RTE
      x86/apic: Support 15 bits of APIC ID in IOAPIC/MSI where available
      genirq: Prepare for default affinity to be passed to __irq_alloc_descs()
      genirq: Add default_affinity argument to __irq_alloc_descs()
      irqdomain: Add max_affinity argument to irq_domain_alloc_descs()
      genirq: Add irq_domain_set_affinity()
      x86/irq: Add x86_non_ir_cpumask
      x86/irq: Limit IOAPIC and MSI domains' affinity without IR
      x86/smp: Allow more than 255 CPUs even without interrupt remapping
      iommu/irq_remapping: Kill most of hyperv-iommu.c now it's redundant
      x86/kvm: Add KVM_FEATURE_MSI_EXT_DEST_ID

 Documentation/virt/kvm/cpuid.rst     |   4 +
 arch/x86/include/asm/apic.h          |   1 +
 arch/x86/include/asm/io_apic.h       |   3 +-
 arch/x86/include/asm/mpspec.h        |   2 +
 arch/x86/include/asm/x86_init.h      |   2 +
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kernel/apic/apic.c          |  41 +++++++++-
 arch/x86/kernel/apic/io_apic.c       |  23 ++++--
 arch/x86/kernel/apic/msi.c           |  44 +++++++++--
 arch/x86/kernel/apic/x2apic_phys.c   |   9 +++
 arch/x86/kernel/kvm.c                |   6 ++
 arch/x86/kernel/x86_init.c           |   1 +
 drivers/iommu/hyperv-iommu.c         | 149 +----------------------------------
 include/linux/interrupt.h            |   2 +
 include/linux/irq.h                  |  10 ++-
 include/linux/irqdomain.h            |   7 +-
 kernel/irq/devres.c                  |   8 +-
 kernel/irq/ipi.c                     |   2 +-
 kernel/irq/irqdesc.c                 |  29 ++++---
 kernel/irq/irqdomain.c               |  69 ++++++++++++++--
 kernel/irq/manage.c                  |  19 ++++-
 21 files changed, 240 insertions(+), 192 deletions(-)
```
#### [PATCH v6 00/10] vfio/fsl-mc: VFIO support for FSL-MC device
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
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
Currenlty the mc-bus patches were queued for merging.
https://www.spinics.net/lists/kernel/msg3680670.html

v5 --> v6
- style fixes
- review fixes

v4 --> v5
- do not allow mmap for DPRCs
- style fixes

v3 --> v4
- use bus provided functions to tear down the DPRC
- added reset support

v2 --> v3
- There is no need to align region size to page size
- read/write implemented for all DPAA2 objects
- review fixes

v1 --> v2
- Fixed the container reset, a new flag added to the firmware command
- Implement a bus notifier for setting driver_override


Bharat Bhushan (1):
  vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices

Diana Craciun (9):
  vfio/fsl-mc: Scan DPRC objects on vfio-fsl-mc driver bind
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_INFO ioctl
  vfio/fsl-mc: Implement VFIO_DEVICE_GET_REGION_INFO ioctl call
  vfio/fsl-mc: Allow userspace to MMAP fsl-mc device MMIO regions
  vfio/fsl-mc: Added lock support in preparation for interrupt handling
  vfio/fsl-mc: Add irq infrastructure for fsl-mc devices
  vfio/fsl-mc: trigger an interrupt via eventfd
  vfio/fsl-mc: Add read/write support for fsl-mc devices
  vfio/fsl-mc: Add support for device reset

 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 +
 drivers/vfio/fsl-mc/Makefile              |   4 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 682 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c    | 194 ++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  55 ++
 include/uapi/linux/vfio.h                 |   1 +
 9 files changed, 953 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_intr.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h
```
#### [PATCH 0/2] KVM: VMX: x2APIC + APICV MSR fix and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Mon Oct  5 19:55:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11817467
Return-Path: <SRS0=R7/Q=DM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34B33112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 19:56:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2217E212CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  5 Oct 2020 19:56:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729526AbgJETz6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 5 Oct 2020 15:55:58 -0400
Received: from mga01.intel.com ([192.55.52.88]:42027 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729489AbgJETzy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 5 Oct 2020 15:55:54 -0400
IronPort-SDR: 
 oOb/qjoUubOY4mdg4Jm46SdoBitMgepHPkMNo3nb8wXlqDA/JtsIdCeqT+teDGqHnUuhVh9AOd
 UfGxuB607UFg==
X-IronPort-AV: E=McAfee;i="6000,8403,9765"; a="181660130"
X-IronPort-AV: E=Sophos;i="5.77,340,1596524400";
   d="scan'208";a="181660130"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Oct 2020 12:55:38 -0700
IronPort-SDR: 
 Qn6dcXyLS9GLxdy9yfod/VbkNOasp1nJSKcc4UGx8m5yfFHOpyna3foH/aVvptK8KO5ec9W/oh
 YLRX3kjIi0AA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,340,1596524400";
   d="scan'208";a="353550141"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga007.jf.intel.com with ESMTP; 05 Oct 2020 12:55:36 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Alexander Graf <graf@amazon.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Peter Xu <peterx@redhat.com>
Subject: [PATCH 0/2] KVM: VMX: x2APIC + APICV MSR fix and cleanup
Date: Mon,  5 Oct 2020 12:55:30 -0700
Message-Id: <20201005195532.8674-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Patch 1 is an unofficial patch from Peter to fix x2APIC MSR interception
on non-APICV systems.  As Peter suggested, it really should be squashed
with commit 3eb900173c71 ("KVM: x86: VMX: Prevent MSR passthrough when MSR
access is denied").  Without the fix, KVM is completely busted on
non-APICV systems.

Patch 2 is a cleanup of sorts to revert back to the pre-filtering approach
of initializing the x2APIC MSR bitmaps for APICV.

Note, I haven't tested on an APICV system.  My APICV system appears to
have crashed over the weekend and I haven't yet journeyed back to the
lab to kick it.

Peter Xu (1):
  KVM: VMX: Fix x2APIC MSR intercept handling on !APICV platforms

Sean Christopherson (1):
  KVM: VMX: Ignore userspace MSR filters for x2APIC when APICV is
    enabled

 arch/x86/kvm/vmx/vmx.c | 45 ++++++++++++++++++++++++++++--------------
 1 file changed, 30 insertions(+), 15 deletions(-)
```
