#### [PATCH v5 01/14] vfio/mdev: idxd: add theory of operation documentation for idxd mdev
##### From: Dave Jiang <dave.jiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Dave Jiang <dave.jiang@intel.com>
X-Patchwork-Id: 12070965
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2269CC433E6
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 21:15:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6FC864FBA
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 21:15:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233310AbhBEVPJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 16:15:09 -0500
Received: from mga12.intel.com ([192.55.52.136]:30881 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233282AbhBETLZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 14:11:25 -0500
IronPort-SDR: 
 wYDldr4DhXycNHLDSL9Yasl8x4khfqwaknoOdL4WiLLyrWgnI8xvWaAnhKadXt/TQAKEKoimN+
 xXIRLVUrjidg==
X-IronPort-AV: E=McAfee;i="6000,8403,9886"; a="160645130"
X-IronPort-AV: E=Sophos;i="5.81,156,1610438400";
   d="scan'208";a="160645130"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 12:53:01 -0800
IronPort-SDR: 
 UTqjwzv3JE77P49uRvkMuBpMF5TxMoIO2nJupHY3O3m2A/nBmkibq473+BYTa4o6nJhQYhf99X
 pLXKckMHRjqg==
X-IronPort-AV: E=Sophos;i="5.81,156,1610438400";
   d="scan'208";a="434596829"
Received: from djiang5-desk3.ch.intel.com ([143.182.136.137])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 12:52:59 -0800
Subject: [PATCH v5 01/14] vfio/mdev: idxd: add theory of operation
 documentation for idxd mdev
From: Dave Jiang <dave.jiang@intel.com>
To: alex.williamson@redhat.com, kwankhede@nvidia.com,
        tglx@linutronix.de, vkoul@kernel.org
Cc: megha.dey@intel.com, jacob.jun.pan@intel.com, ashok.raj@intel.com,
        jgg@mellanox.com, yi.l.liu@intel.com, baolu.lu@intel.com,
        kevin.tian@intel.com, sanjay.k.kumar@intel.com,
        tony.luck@intel.com, dan.j.williams@intel.com,
        eric.auger@redhat.com, parav@mellanox.com, netanelg@mellanox.com,
        shahafs@mellanox.com, pbonzini@redhat.com,
        dmaengine@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Date: Fri, 05 Feb 2021 13:52:59 -0700
Message-ID: 
 <161255837927.339900.13569654778245565488.stgit@djiang5-desk3.ch.intel.com>
In-Reply-To: 
 <161255810396.339900.7646244556839438765.stgit@djiang5-desk3.ch.intel.com>
References: 
 <161255810396.339900.7646244556839438765.stgit@djiang5-desk3.ch.intel.com>
User-Agent: StGit/0.23-29-ga622f1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add idxd vfio mediated device theory of operation documentation.
Provide description on mdev design, usage, and why vfio mdev was chosen.

Reviewed-by: Ashok Raj <ashok.raj@intel.com>
Reviewed-by: Kevin Tian <kevin.tian@intel.com>
Signed-off-by: Dave Jiang <dave.jiang@intel.com>
---
 Documentation/driver-api/vfio/mdev-idxd.rst |  397 +++++++++++++++++++++++++++
 MAINTAINERS                                 |    1 
 2 files changed, 398 insertions(+)
 create mode 100644 Documentation/driver-api/vfio/mdev-idxd.rst

diff --git a/Documentation/driver-api/vfio/mdev-idxd.rst b/Documentation/driver-api/vfio/mdev-idxd.rst
new file mode 100644
index 000000000000..9bf93eafc7c8
--- /dev/null
+++ b/Documentation/driver-api/vfio/mdev-idxd.rst
@@ -0,0 +1,397 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+=============
+IDXD Overview
+=============
+IDXD (Intel Data Accelerator Driver) is the driver for the Intel Data
+Streaming Accelerator (DSA).  Intel DSA is a high performance data copy
+and transformation accelerator. In addition to data move operations,
+the device also supports data fill, CRC generation, Data Integrity Field
+(DIF), and memory compare and delta generation. Intel DSA supports
+a variety of PCI-SIG defined capabilities such as Address Translation
+Services (ATS), Process address Space ID (PASID), Page Request Interface
+(PRI), Message Signalled Interrupts Extended (MSI-X), and Advanced Error
+Reporting (AER). Some of those capabilities enable the device to support
+Shared Virtual Memory (SVM), or also known as Shared Virtual Addressing
+(SVA). Intel DSA also supports Intel Scalable I/O Virtualization (SIOV)
+to improve scalability of device assignment.
+
+
+The Intel DSA device contains the following basic components:
+* Work queue (WQ)
+
+  A WQ is an on device storage to queue descriptors to the
+  device. Requests are added to a WQ by using new CPU instructions
+  (MOVDIR64B and ENQCMD(S)) to write the memory mapped “portal”
+  associated with each WQ.
+
+* Engine
+
+  Operation unit that pulls descriptors from WQs and processes them.
+
+* Group
+
+  Abstract container to associate one or more engines with one or more WQs.
+
+
+Two types of WQs are supported:
+* Dedicated WQ (DWQ)
+
+  A single client should owns this exclusively and can submit work
+  to it. The MOVDIR64B instruction is used to submit descriptors to
+  this type of WQ. The instruction is a posted write, therefore the
+  submitter must ensure not exceed the WQ length for submission. The
+  use of PASID is optional with DWQ. Multiple clients can submit to
+  a DWQ, but sychronization is required due to when the WQ is full,
+  the submission is silently dropped.
+
+* Shared WQ (SWQ)
+
+  Multiple clients can submit work to this WQ. The submitter must use
+  ENQMCDS (from supervisor mode) or ENQCMD (from user mode). These
+  instructions will indicate via EFLAGS.ZF bit whether a submission
+  succeeds. The use of PASID is mandatory to identify the address space
+  of each client.
+
+
+For more information about the new instructions [1][2].
+
+The IDXD driver is broken down into following usages:
+* In kernel interface through dmaengine subsystem API.
+* Userspace DMA support through character device. mmap(2) is utilized
+  to map directly to mmio address (or portals) for descriptor submission.
+* VFIO Mediated device (mdev) supporting device passthrough usages. This
+  is only for the mdev usage.
+
+
+=================================
+Assignable Device Interface (ADI)
+=================================
+The term ADI is used to represent the minimal unit of assignment for
+Intel Scalable IOV device. Each ADI instance refers to the set of device
+backend resources that are allocated, configured and organized as an
+isolated unit.
+
+Intel DSA defines each WQ as an ADI. The MMIO registers of each work queue
+are partitioned into two categories:
+* MMIO registers accessed for data-path operations.
+* MMIO registers accessed for control-path operations.
+
+Data-path MMIO registers of each WQ are contained within
+one or more system page size aligned regions and can be mapped in the
+CPU page table for direct access from the guest. Control-path MMIO
+registers of all WQs are located together but segregated from data-path
+MMIO regions. Therefore, guest updates to control-path registers must
+be intercepted and then go through the host driver to be reflected in
+the device.
+
+Data-path MMIO registers of DSA WQ are portals for submitting descriptors
+to the device. There are four portals per WQ, each being 64 bytes
+in size and located on a separate 4KB page in BAR2. Each portal has
+different implications regarding interrupt message type (MSI vs. IMS)
+and occupancy control (limited vs. unlimited). It is not necessary to
+map all portals to the guest.
+
+Control-path MMIO registers of DSA WQ include global configurations
+(shared by all WQs) and WQ-specific configurations. The owner
+(e.g. the guest) of the WQ is expected to only change WQ-specific
+configurations. Intel DSA spec introduces a “Configuration Support”
+capability which, if cleared, indicates that some fields of WQ
+configuration registers are read-only and the WQ configuration is
+pre-configured by the host.
+
+
+Interrupt Message Store (IMS)
+-----------------------------
+The ADI utilizes Interrupt Message Store (IMS), a device-specific MSI
+implementation, instead of MSIX for interrupts for the guest. This
+preserves MSIX for host usages and also allows a significantly larger
+number of interrupt vectors for large number of guests usage.
+
+Intel DSA device implements IMS as on-device memory mapped unified
+storage. Each interrupt message is stored as a DWORD size data payload
+and a 64-bit address (same as MSI-X). Access to the IMS is through the
+host idxd driver.
+
+The idxd driver makes use of the generic IMS irq chip and domain which
+stores the interrupt messages in an array in device memory. Allocation and
+freeing of interrupts happens via the generic msi_domain_alloc/free_irqs()
+interface. Driver only needs to ensure the interrupt domain is stored in
+the underlying device struct.
+
+
+ADI Isolation
+-------------
+Operations or functioning of one ADI must not affect the functioning
+of another ADI or the physical device. Upstream memory requests from
+different ADIs are distinguished using a Process Address Space Identifier
+(PASID). With the support of PASID-granular address translation in Intel
+VT-d, the address space targeted by a request from ADI can be a Host
+Virtual Address (HVA), Host I/O Virtual Address (HIOVA), Guest Physical
+Address (GPA), Guest Virtual Address (GVA), Guest I/O Virtual Address
+(GIOVA), etc. The PASID identity for an ADI is expected to be accessed
+or modified by privileged software through the host driver.
+
+=========================
+Virtual DSA (vDSA) Device
+=========================
+The DSA WQ itself is not a PCI device thus must be composed into a
+virtual DSA device to the guest.
+
+The composition logic needs to handle four main requirements:
+* Emulate PCI config space.
+* Map data-path portals for direct access from the guest.
+* Emulate control-path MMIO registers and selectively forward WQ
+  configuration requests through host driver to the device.
+* Forward and emulate WQ interrupts to the guest.
+
+The composition logic tells the guest aspects of WQ which are configurable
+through a combination of capability fields, e.g.:
+* Configuration Support (if cleared, most aspects are not modifiable).
+* WQ Mode Support (if cleared, cannot change between dedicated and
+  shared mode).
+* Dedicated Mode Support.
+* Shared Mode Support.
+* ...
+
+The virtual capability fields are set according to the vDSA
+type. Following is an example of vDSA types and related WQ configurability:
+* Type ‘1dwq-v1’
+   * One DSA gen1 dedicated WQ to this guest
+   * Guest cannot share the WQ between its clients (no guest SVA)
+   * Guest cannot change any WQ configuration
+
+Besides, the composition logic also needs to serve administrative commands
+(thru virtual CMD register) through host driver, including:
+* Drain/abort all descriptors submitted by this guest.
+* Drain/abort descriptors associated with a PASID.
+* Enable/disable/reset the WQ (when it’s not shared by multiple VMs).
+* Request interrupt handle.
+
+With this design, vDSA emulation is **greatly simplified**. Most
+registers are emulated in simple READ-ONLY flavor, and handling limited
+configurability is required only for a few registers.
+
+===========================
+VFIO mdev vs. userspace DMA
+===========================
+There are two avenues to support vDSA composition.
+1. VFIO mediated device (mdev)
+2. Userspace DMA through char device
+
+VFIO mdev provides a generic subdevice passthrough framework. Unified
+uAPIs are used for both device and subdevice passthrough, thus any
+userspace VMM which already supports VFIO device passthrough would
+naturally support mdev/subdevice passthrough. The implication of VFIO
+mdev is putting emulation of device interface in the kernel (part of
+host driver) which must be carefully scrutinized. Fortunately, vDSA
+composition includes only a small portion of emulation code, due to the
+fact that most registers are simply READ-ONLY to the guest. The majority
+logic of handling limited configurability and administrative commands
+is anyway required to sit in the kernel, regardless of which kernel uAPI
+is pursued. In this regard, VFIO mdev is a nice fit for vDSA composition.
+
+IDXD driver provides a char device interface for applications to
+map the WQ portal and directly submit descriptors to do DMA. This
+interface provides only data-path access to userspace and relies on
+the host driver to handle control-path configurations. Expanding such
+interface to support subdevice passthrough allows moving the emulation
+code to userspace. However, quite some work is required to grow it from
+an application-oriented interface into a passthrough-oriented interface:
+new uAPIs to handle guest WQ configurability and administrative commands,
+and new uAPIs to handle passthrough specific requirements (e.g. DMA map,
+guest SVA, live migration, posted interrupt, etc.). And once it is done,
+every userspace VMM has to explicitly bind to IDXD specific uAPI, even
+though the real user is in the guest (instead of the VMM itself) in the
+passthrough scenario.
+
+Although some generalization might be possible to reduce the work of
+handling passthrough, we feel the difference between userspace DMA
+and subdevice passthrough is distinct in IDXD. Therefore, we choose to
+build vDSA composition on top of VFIO mdev framework and leave userspace
+DMA intact after discussion at LPC 2020.
+
+=============================
+Host Registration and Release
+=============================
+
+Intel DSA reports support for Intel Scalable IOV via a PCI Express
+Designated Vendor Specific Extended Capability (DVSEC). In addition,
+PASID-granular address translation capability is required in the
+IOMMU. During host initialization, the IDXD driver should check the
+presence of both capabilities before calling mdev_register_device()
+to register with the VFIO mdev framework and provide a set of ops
+(struct mdev_parent_ops). The IOMMU capability is indicated by the
+IOMMU_DEV_FEAT_AUX feature flag with iommu_dev_has_feature() and enabled
+with iommu_dev_enable_feature().
+
+On release, iommu_dev_disable_feature() is called after
+mdev_unregister_device() to disable the IOMMU_DEV_FEAT_AUX flag that
+the driver enabled during host initialization.
+
+The mdev_parent_ops data structure is filled out by the driver to provide
+a number of ops called by VFIO mdev framework::
+
+        struct mdev_parent_ops {
+                .supported_type_groups
+                .create
+                .remove
+                .open
+                .release
+                .read
+                .write
+                .mmap
+                .ioctl
+        };
+
+Supported_type_groups
+---------------------
+At the moment only one vDSA type is supported.
+
+“1dwq-v1”:
+  Single dedicated WQ (DSA 1.0) with read-only configuration exposed to
+  the guest. On the guest kernel, a vDSA device shows up with a single
+  WQ that is pre-configured by the host. The configuration for the WQ
+  is entirely read-only and cannot be reconfigured. There is no support
+  of guest SVA on this WQ.
+
+  The interrupt vector 0 is emulated by the host driver to support the admin
+  command completion and error reporting. A second interrupt vector is
+  bound to the IMS and used for I/O operation. In this implementation,
+  there are only two vectors being supported.
+
+create
+------
+API function to create the mdev. mdev_set_iommu_device() is called to
+associate the mdev device to the parent PCI device. This function is
+where the driver sets up and initializes the resources to support a single
+mdev device. This is triggered through sysfs to initiate the creation.
+
+remove
+------
+API function that mirrors the create() function and releases all the
+resources backing the mdev.  This is also triggered through sysfs.
+
+open
+----
+API function that is called down from VFIO userspace to indicate to the
+driver that the upper layers are ready to claim and utilize the mdev. IMS
+entries are allocated and setup here.
+
+release
+-------
+The mirror function to open that releases the mdev by VFIO userspace.
+
+read / write
+------------
+This is where the Intel IDXD driver provides read/write emulation of
+PCI config space and MMIO registers. These paths are the “slow” path
+of the mediated device and emulation is used rather than direct access
+to the hardware resources. Typically configuration and administrative
+commands go through this path. This allows the mdev to show up as a
+virtual PCI device on the guest kernel.
+
+The emulation of PCI config space is nothing special, which is simply
+copied from kvmgt. In the future this part might be consolidated to
+reduce duplication.
+
+Emulating MMIO reads are simply memory copies. There is no side-effect
+to be emulated upon guest read.
+
+Emulating MMIO writes are required only for a few registers, due to
+read-only configuration on the ‘1dwq-v1’ type. Majority of composition
+logic is hooked in the CMD register for performing administrative commands
+such as WQ drain, abort, enable, disable and reset operations. The rest of
+the emulation is about handling errors (GENCTRL/SWERROR) and interrupts
+(INTCAUSE/MSIXPERM) on the vDSA device. Future mdev types might allow
+limited WQ configurability, which then requires additional emulation of
+the WQCFG register.
+
+mmap
+----
+This is the function that provides the setup to expose a portion of the
+hardware, also known as portals, for direct access for “fast” path
+operations through the mmap() syscall. A limited region of the hardware
+is mapped to the guest for direct I/O submission.
+
+There are four portals per WQ: unlimited MSI-X, limited MSI-X, unlimited
+IMS, limited IMS.  Descriptors submitted to limited portals are subject
+to threshold configuration limitations for shared WQs. The MSI-X portals
+are used for host submissions, and the IMS portals are mapped to vm for
+guest submission.
+
+ioctl
+-----
+This API function does several things
+* Provides general device information to VFIO userspace.
+* Provides device region information (PCI, mmio, etc).
+* Get interrupts information
+* Setup interrupts for the mediated device.
+* Mdev device reset
+
+For the Intel idxd driver, Interrupt Message Store (IMS) vectors are being
+used for mdev interrupts rather than MSIX vectors. IMS provides additional
+interrupt vectors outside of PCI MSIX specification in order to support
+significantly more vectors. The emulated interrupt (0) is connected through
+kernel eventfd. When interrupt 0 needs to be asserted, the driver will
+signal the eventfd to trigger vector 0 interrupt on the guest.
+The IMS interrupts are setup via eventfd as well. However, it utilizes
+irq bypass manager to directly inject the interrupt in the guest.
+
+To allocate IMS, we utilize the IMS array APIs. On host init, we need
+to create the MSI domain::
+
+        struct ims_array_info ims_info;
+        struct device *dev = &pci_dev->dev;
+
+
+        /* assign the device IMS size */
+        ims_info.max_slots = max_ims_size;
+        /* assign the MMIO base address for the IMS table */
+        ims_info.slots = mmio_base + ims_offset;
+        /* assign the MSI domain to the device */
+        dev->msi_domain = pci_ims_array_create_msi_irq_domain(pci_dev, &ims_info);
+
+When we are ready to allocate the interrupts::
+
+        struct device *dev = mdev_dev(mdev);
+
+        irq_domain = pci_dev->dev.msi_domain;
+        /* the irqs are allocated against device of mdev */
+        rc = msi_domain_alloc_irqs(irq_domain, dev, num_vecs);
+
+
+        /* we can retrieve the slot index from msi_entry */
+        for_each_msi_entry(entry, dev) {
+                slot_index = entry->device_msi.hwirq;
+                irq = entry->irq;
+        }
+
+        request_irq(irq, interrupt_handler_function, 0, “ims”, context);
+
+
+The DSA device is structured such that MSI-X table entry 0 is used for
+admin commands completion, error reporting, and other misc commands. The
+remaining MSI-X table entries are used for WQ completion. For vm support,
+the virtual device also presents a similar layout. Therefore, vector 0
+is emulated by the software. Additional vector(s) are associated with IMS.
+
+The index (slot) for the per device IMS entry is managed by the MSI
+core. The index is the “interrupt handle” that the guest kernel
+needs to program into a DMA descriptor. That interrupt handle tells the
+hardware which IMS vector to trigger the interrupt on for the host.
+
+The virtual device presents an admin command called “request interrupt
+handle” that is not supported by the physical device. On probe of
+the DSA device on the guest kernel, the guest driver will issue the
+“request interrupt handle” command in order to get the interrupt
+handle for descriptor programming. The host driver will return the
+assigned slot for the IMS entry table to the guest.
+
+==========
+References
+==========
+[1] https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html
+[2] https://software.intel.com/en-us/articles/intel-sdm
+[3] https://software.intel.com/sites/default/files/managed/cc/0e/intel-scalable-io-virtualization-technical-specification.pdf
+[4] https://software.intel.com/en-us/download/intel-data-streaming-accelerator-preliminary-architecture-specification
```
#### [PATCH] coresight: etm4x: Fix merge resolution for amba rework
##### From: =?utf-8?q?Uwe_Kleine-K=C3=B6nig?= <uwe@kleine-koenig.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Uwe_Kleine-K=C3=B6nig?=
 <uwe@kleine-koenig.org>
X-Patchwork-Id: 12070101
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BBA39C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 13:14:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6AB2064F3A
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 13:14:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229629AbhBENMb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 08:12:31 -0500
Received: from antares.kleine-koenig.org ([94.130.110.236]:34562 "EHLO
        antares.kleine-koenig.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231284AbhBENJ7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 08:09:59 -0500
Received: by antares.kleine-koenig.org (Postfix, from userid 1000)
        id D67A7AED6A1; Fri,  5 Feb 2021 14:08:50 +0100 (CET)
From: =?utf-8?q?Uwe_Kleine-K=C3=B6nig?= <uwe@kleine-koenig.org>
To: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Cc: Alexandre Belloni <alexandre.belloni@bootlin.com>,
 Dmitry Torokhov <dmitry.torokhov@gmail.com>, kvm@vger.kernel.org,
 David Airlie <airlied@linux.ie>, Linus Walleij <linus.walleij@linaro.org>,
 linux-fbdev@vger.kernel.org, dri-devel@lists.freedesktop.org,
 Jaroslav Kysela <perex@perex.cz>, Eric Anholt <eric@anholt.net>,
	=?utf-8?q?Uwe_Kleine-K=C3=B6nig?=  <u.kleine-koenig.org@pengutronix.de>,
 linux-i2c@vger.kernel.org, Jiri Slaby <jirislaby@kernel.org>,
 linux-stm32@st-md-mailman.stormreply.com, linux-watchdog@vger.kernel.org,
 linux-rtc@vger.kernel.org, Herbert Xu <herbert@gondor.apana.org.au>,
 Takashi Iwai <tiwai@suse.com>,
 Russell King - ARM Linux admin <linux@armlinux.org.uk>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Alexander Shishkin <alexander.shishkin@linux.intel.com>,
 linux-serial@vger.kernel.org, linux-input@vger.kernel.org,
 Ulf Hansson <ulf.hansson@linaro.org>, Guenter Roeck <linux@roeck-us.net>,
 Mike Leach <mike.leach@linaro.org>,
 Maxime Coquelin <mcoquelin.stm32@gmail.com>,
 Alexandre Torgue <alexandre.torgue@st.com>, alsa-devel@alsa-project.org,
 Suzuki K Poulose <suzuki.poulose@arm.com>, coresight@lists.linaro.org,
 Vladimir Zapolskiy <vz@mleia.com>, Eric Auger <eric.auger@redhat.com>,
 Alex Williamson <alex.williamson@redhat.com>,
 Mark Brown <broonie@kernel.org>, Matt Mackall <mpm@selenic.com>,
 Dan Williams <dan.j.williams@intel.com>,
 Wim Van Sebroeck <wim@linux-watchdog.org>, kernel@pengutronix.de,
 linux-arm-kernel@lists.infradead.org,
 Alessandro Zummo <a.zummo@towertech.it>,
 Mathieu Poirier <mathieu.poirier@linaro.org>,
 Cornelia Huck <cohuck@redhat.com>, linux-mmc@vger.kernel.org,
 linux-kernel@vger.kernel.org, linux-spi@vger.kernel.org,
 Vinod Koul <vkoul@kernel.org>, Arnd Bergmann <arnd@arndb.de>,
 linux-crypto@vger.kernel.org, Daniel Vetter <daniel@ffwll.ch>,
 Leo Yan <leo.yan@linaro.org>, dmaengine@vger.kernel.org
Subject: [PATCH] coresight: etm4x: Fix merge resolution for amba rework
Date: Fri,  5 Feb 2021 14:08:47 +0100
Message-Id: <20210205130848.20009-1-uwe@kleine-koenig.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This was non-trivial to get right because commits
c23bc382ef0e ("coresight: etm4x: Refactor probing routine") and
5214b563588e ("coresight: etm4x: Add support for sysreg only devices")
changed the code flow considerably. With this change the driver can be
built again.

Fixes: 0573d3fa4864 ("Merge branch 'devel-stable' of git://git.armlinux.org.uk/~rmk/linux-arm into char-misc-next")
Signed-off-by: Uwe Kleine-König <uwe@kleine-koenig.org>
---
On Fri, Feb 05, 2021 at 12:07:09PM +0100, Greg Kroah-Hartman wrote:
> On Fri, Feb 05, 2021 at 11:56:15AM +0100, Uwe Kleine-König wrote:
> > I didn't compile test, but I'm willing to bet your resolution is wrong.
> > You have no return statement in etm4_remove_dev() but its return type is
> > int and etm4_remove_amba() still returns int but should return void.
> 
> Can you send a patch to fix this up?

Sure, here it comes. As I'm unsure if you want to squash it into the
merge or want to keep it separate I crafted a commit message. If you
prefer squashing feel free to do so.

This change corresponds to the merge resolution I suggested before.

Best regards
Uwe

 drivers/hwtracing/coresight/coresight-etm4x-core.c | 7 ++++---
 1 file changed, 4 insertions(+), 3 deletions(-)

```
#### [GIT PULL] KVM fixes for 5.11-rc7
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12069545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 36611C43381
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:06:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8D7F64FB8
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:06:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231489AbhBEIGe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 03:06:34 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:41111 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231449AbhBEIG0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Feb 2021 03:06:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612512300;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Va8uAp49smeqnrGGNNLNfaP87j7pFRlQR8LmmQQElkQ=;
        b=Of1tirRHisVfp397yUBJbRCJpwcxZu/yGoeTT7ulxKwO5DuPhNq5qhD1PvQrqukpvIZYN1
        +NzrA6ra9megP7fh9v3Oxods5Ed1IDW1tNAN58vLZH/5FVPzZY2tH5+ghrva3xqTI2JYxe
        szn1yKLdfzsx1/704+HSp907QHMi6L4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-264-_G6phLwKNFSCJM1iRO4bTQ-1; Fri, 05 Feb 2021 03:04:58 -0500
X-MC-Unique: _G6phLwKNFSCJM1iRO4bTQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 42264192D785;
        Fri,  5 Feb 2021 08:04:57 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E2A275D9D3;
        Fri,  5 Feb 2021 08:04:56 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM fixes for 5.11-rc7
Date: Fri,  5 Feb 2021 03:04:56 -0500
Message-Id: <20210205080456.30446-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 9a78e15802a87de2b08dfd1bd88e855201d2c8fa:

  KVM: x86: allow KVM_REQ_GET_NESTED_STATE_PAGES outside guest mode for VMX (2021-01-25 18:54:09 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 031b91a5fe6f1ce61b7617614ddde9ed61e252be:

  KVM: x86: Set so called 'reserved CR3 bits in LM mask' at vCPU reset (2021-02-04 12:59:28 -0500)

----------------------------------------------------------------
x86 has lots of small bugfixes, mostly one liners.  It's quite late in
5.11-rc but none of them are related to this merge window; it's just
bugs coming in at the wrong time.  Of note among the others:
- "KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if tsx=off"
  (live migration failure seen on distros that hadn't switched to tsx=off
  right away)

ARM:
- Avoid clobbering extra registers on initialisation

----------------------------------------------------------------
Andrew Scull (1):
      KVM: arm64: Don't clobber x4 in __do_hyp_init

Ben Gardon (1):
      KVM: x86/mmu: Fix TDP MMU zap collapsible SPTEs

Michael Roth (1):
      KVM: x86: fix CPUID entries returned by KVM_GET_CPUID2 ioctl

Paolo Bonzini (3):
      Merge tag 'kvmarm-fixes-5.11-3' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      KVM: x86: Allow guests to see MSR_IA32_TSX_CTRL even if tsx=off
      KVM: x86: cleanup CR3 reserved bits checks

Peter Gonda (1):
      Fix unsynchronized access to sev members through svm_register_enc_region

Sean Christopherson (3):
      KVM: x86: Update emulator context mode if SYSENTER xfers to 64-bit mode
      KVM: SVM: Treat SVM as unsupported when running as an SEV guest
      KVM: x86: Set so called 'reserved CR3 bits in LM mask' at vCPU reset

Vitaly Kuznetsov (1):
      KVM: x86: Supplement __cr4_reserved_bits() with X86_FEATURE_PCID check

Yu Zhang (1):
      KVM: Documentation: Fix documentation for nested.

Zheng Zhan Liang (1):
      KVM/x86: assign hva with the right value to vm_munmap the pages

 Documentation/virt/kvm/nested-vmx.rst            |  6 +++--
 Documentation/virt/kvm/running-nested-guests.rst |  2 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S               | 20 ++++++++-------
 arch/x86/kvm/cpuid.c                             |  2 +-
 arch/x86/kvm/emulate.c                           |  2 ++
 arch/x86/kvm/mmu/tdp_mmu.c                       |  6 ++---
 arch/x86/kvm/svm/nested.c                        | 13 +++-------
 arch/x86/kvm/svm/sev.c                           | 17 +++++++------
 arch/x86/kvm/svm/svm.c                           |  5 ++++
 arch/x86/kvm/svm/svm.h                           |  3 ---
 arch/x86/kvm/vmx/vmx.c                           | 17 ++++++++++---
 arch/x86/kvm/x86.c                               | 31 ++++++++++++++++--------
 arch/x86/kvm/x86.h                               |  2 ++
 arch/x86/mm/mem_encrypt.c                        |  1 +
 14 files changed, 77 insertions(+), 50 deletions(-)
```
#### [GIT PULL] vdpa: last minute bugfix
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12071165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 10D82C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 22:34:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B14B464F06
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 22:34:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231927AbhBEWeO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 17:34:14 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:21903 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232145AbhBEONe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Feb 2021 09:13:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612540201;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=+vT+jbN1YVSVSpzQpXP9jC5D0CiFueilUGvKuUc6MhE=;
        b=Pl8mWrGNOndtC9XADvofyiyNyA7yNr4jLV7fQ7HkTEv01iiYkZkhAqR1yM5YzaiN2YhWb5
        MeHkfHu52tMdBcTxgPy5RPhFUZ9AC1jE/zzxwjz08MStHDGOBD3cn945gDqRCx5womwJPI
        LH+ynVwpC7f/9zBHw/+9+Dssweb3xU0=
Received: from mail-ej1-f69.google.com (mail-ej1-f69.google.com
 [209.85.218.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-317-MHFSqBXYMCqxh1jPH4qOyw-1; Fri, 05 Feb 2021 10:45:26 -0500
X-MC-Unique: MHFSqBXYMCqxh1jPH4qOyw-1
Received: by mail-ej1-f69.google.com with SMTP id ar1so3589893ejc.22
        for <kvm@vger.kernel.org>; Fri, 05 Feb 2021 07:45:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=+vT+jbN1YVSVSpzQpXP9jC5D0CiFueilUGvKuUc6MhE=;
        b=iaNX3MdIIDJTGbf5T3HI99WRR8rV4wiZD31tHPT7W34jAs/ATIcdwFkcsAky1LyoOG
         c79VcMUvl41tgqT7fUa7vc47QF5lPeds4ZkOYkASoDzDzkmZFp4FkEwEtslJjrje7cx2
         qEPe+sTBGBgGjNmRSSunfpFogbQxK59HMhvJRX1SYYE/vZC4YMFlaPIxpzKQ9gVIU/gq
         hCRC+rUH+srNByfkHejzosMHp2F+p6n+b7z03WCqFKFRf3FRoCE3a28o9ManQsjn8ou2
         2CrMIhsbWzIZv0qJPhuVpL7FpTYW942BbN1FWDe7oBC54/WehyjGv+qTyE4qHMXzHyPp
         MmVw==
X-Gm-Message-State: AOAM533n1M3tDinppiFLKzY0KXUuTKnhEfjvgbSB/YYsC3yU8/Y6rMqt
        CY387m1O4eD8sPaQXZX5FhNAxtE0YH+k1tf1tGu/PgVXD2s96fWvP04TzNdaHCjXk93YDA854Vi
        gGoEczWv/UuZT
X-Received: by 2002:a17:906:8292:: with SMTP id
 h18mr4553202ejx.342.1612539924140;
        Fri, 05 Feb 2021 07:45:24 -0800 (PST)
X-Google-Smtp-Source: 
 ABdhPJxqBUHpbvPYDpBnMWonVBrhZuXG+GwON2f3pVr2d/bLWj6ekzRtN+o9kgto+FKOSFfskxHUQg==
X-Received: by 2002:a17:906:8292:: with SMTP id
 h18mr4553187ejx.342.1612539923963;
        Fri, 05 Feb 2021 07:45:23 -0800 (PST)
Received: from redhat.com (bzq-79-180-2-31.red.bezeqint.net. [79.180.2.31])
        by smtp.gmail.com with ESMTPSA id
 y8sm4030809eje.37.2021.02.05.07.45.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 05 Feb 2021 07:45:23 -0800 (PST)
Date: Fri, 5 Feb 2021 10:45:20 -0500
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, jasowang@redhat.com, mst@redhat.com
Subject: [GIT PULL] vdpa: last minute bugfix
Message-ID: <20210205104520-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit 710eb8e32d04714452759f2b66884bfa7e97d495:

  vdpa/mlx5: Fix memory key MTT population (2021-01-20 03:47:04 -0500)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to b35ccebe3ef76168aa2edaa35809c0232cb3578e:

  vdpa/mlx5: Restore the hardware used index after change map (2021-02-05 10:28:04 -0500)

----------------------------------------------------------------
vdpa: last minute bugfix

A bugfix in the mlx driver I got at the last minute.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (1):
      vdpa/mlx5: Restore the hardware used index after change map

 drivers/vdpa/mlx5/net/mlx5_vnet.c | 18 ++++++++++++++++++
 1 file changed, 18 insertions(+)
```
#### [PATCH 1/2] mm: provide a sane PTE walking API for modules
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12069861
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 081B3C433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:45:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6FCE64F46
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:45:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231513AbhBEKpW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 05:45:22 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:49554 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231448AbhBEKed (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 5 Feb 2021 05:34:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1612521186;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=mj+Ly1k3UYPGQYxAhZFurZVICdhyrknCRIPzRSnG+Xc=;
        b=SMKf7zFYGkxf0DEFZK6mIWNscDR+sv4T8bs2Q4InrQRiRxH4GCIOnjHGKaZ1sAWWfcOIpf
        CdYtj4k8f7Oftb3VA3WKKNhKiH1TNH9R9Kj3RsNN892ulanNBqFFA4DIBQ8/l04Nnm5fkH
        QE75lY8UuAQOA/tRQzay6V5DVfpHLsE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-60-AFUaxDJtPIKnH-bT7enzFA-1; Fri, 05 Feb 2021 05:33:02 -0500
X-MC-Unique: AFUaxDJtPIKnH-bT7enzFA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 61A60102C7EE;
        Fri,  5 Feb 2021 10:33:01 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D832F1050E;
        Fri,  5 Feb 2021 10:33:00 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jgg@ziepe.ca, linux-mm@kvack.org,
        Andrew Morton <akpm@linux-foundation.org>,
        dan.j.williams@intel.com
Subject: [PATCH 1/2] mm: provide a sane PTE walking API for modules
Date: Fri,  5 Feb 2021 05:32:58 -0500
Message-Id: <20210205103259.42866-2-pbonzini@redhat.com>
In-Reply-To: <20210205103259.42866-1-pbonzini@redhat.com>
References: <20210205103259.42866-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, the follow_pfn function is exported for modules but
follow_pte is not.  However, follow_pfn is very easy to misuse,
because it does not provide protections (so most of its callers
assume the page is writable!) and because it returns after having
already unlocked the page table lock.

Provide instead a simplified version of follow_pte that does
not have the pmdpp and range arguments.  The older version
survives as follow_invalidate_pte() for use by fs/dax.c.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jason Gunthorpe <jgg@nvidia.com>
---
 arch/s390/pci/pci_mmio.c |  2 +-
 fs/dax.c                 |  5 +++--
 include/linux/mm.h       |  6 ++++--
 mm/memory.c              | 35 ++++++++++++++++++++++++++++++-----
 4 files changed, 38 insertions(+), 10 deletions(-)

```
#### [PATCH v4 1/5] KVM: VMX: Introduce PKS VMCS fields
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12069607
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3023CC433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:40:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F022364E0B
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 08:40:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229753AbhBEIfA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 03:35:00 -0500
Received: from mga09.intel.com ([134.134.136.24]:19405 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229570AbhBEIep (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 03:34:45 -0500
IronPort-SDR: 
 CjaSfGbhS8w0VW48Y9Mxhz653lme17vXY8wVkeBi0+EStjYl0BYNQEPZjmVMeVs7RKRpP337LV
 sZ0Dr9inckfA==
X-IronPort-AV: E=McAfee;i="6000,8403,9885"; a="181550686"
X-IronPort-AV: E=Sophos;i="5.81,154,1610438400";
   d="scan'208";a="181550686"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 00:34:02 -0800
IronPort-SDR: 
 D9bxMPuBg2nzCyVfrjWF55OoXB/SmRbMtsYcsuLmRw5/oepXFzJwCU24xmmVgFSfC5sFywQhJV
 LsOj6kE5xGsQ==
X-IronPort-AV: E=Sophos;i="5.81,154,1610438400";
   d="scan'208";a="393761893"
Received: from chenyi-pc.sh.intel.com ([10.239.159.24])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Feb 2021 00:34:00 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v4 1/5] KVM: VMX: Introduce PKS VMCS fields
Date: Fri,  5 Feb 2021 16:37:02 +0800
Message-Id: <20210205083706.14146-2-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20210205083706.14146-1-chenyi.qiang@intel.com>
References: <20210205083706.14146-1-chenyi.qiang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PKS(Protection Keys for Supervisor Pages) is a feature that extends the
Protection Key architecture to support thread-specific permission
restrictions on supervisor pages.

A new PKS MSR(PKRS) is defined in kernel to support PKS, which holds a
set of permissions associated with each protection domian.

Two VMCS fields {HOST,GUEST}_IA32_PKRS are introduced in
{host,guest}-state area to store the value of PKRS.

Every VM exit saves PKRS into guest-state area.
If VM_EXIT_LOAD_IA32_PKRS = 1, VM exit loads PKRS from the host-state
area.
If VM_ENTRY_LOAD_IA32_PKRS = 1, VM entry loads PKRS from the guest-state
area.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/vmx.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH 1/9] KVM: SVM: Move AVIC vCPU kicking snippet to helper function
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12069065
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9E0CEC433E0
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 00:59:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F63364DF8
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 00:59:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232409AbhBEA6p (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 19:58:45 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:48690 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232381AbhBEA6j (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 19:58:39 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 79B90C061794
        for <kvm@vger.kernel.org>; Thu,  4 Feb 2021 16:57:59 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id b125so5138772ybg.10
        for <kvm@vger.kernel.org>; Thu, 04 Feb 2021 16:57:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=s/7OLdaHi3yoUUX9wWrGdt8SN3RdwtsZAJpN80nW/RM=;
        b=qayTKsI/p7rDGHpuF8mEyIK52XOGj/oCB2Uoibej7fzaUQlWzPI8+idvL6VAqBfKvw
         UaEJAglAgz7aZRNql+wR5KiDIKD/aOs45vlizRO9mXGFhNow04ejrRdrA2IPnH2Hvxpx
         TtRbreH7UDYfxKbwrQxOCwrP4l9c1mzc48X+2EHCuW2oUD3sc8G4UpUPZhh8BSKTcuG/
         XHQCeP1outKwFvKKFudty5CsyMidykmp5F3JZm/muFPNaTGW8l2CYfy+NLOmlEC/KbvS
         KXTRV1cRD1U9VeR8OuT5WHnBuT6x4PUx1I+xAx/T/gTxbqyaXh9N8MbZed9/xvk8Bb4d
         EEPg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=s/7OLdaHi3yoUUX9wWrGdt8SN3RdwtsZAJpN80nW/RM=;
        b=WZSEqr4oREOdTb3I5rBe8UzL1XOt8F0a8I6lnVPCLfhrHIRR1lLnYpUHaStgXxUa8q
         RtPNEjtRwcRPNr+4HoDZ/rS9TO7EwA7xkQflMKj9fy7uyb6b9mBu59G1uIZXNiyZ9fmN
         oaAZfR8scvTSYhqmNX+BtfYTfHe2kygThvOUhMulXIhkOseMOcjSWofchkLV5kb4f0rZ
         fG98HeYqnOazZqZgBWb+bft/E5LQ7yR9GrKcxpUsPVjaNz+aNlN31DoA1KLYIFEtl9A1
         nKbO1WuJ6dlJUeayOlojDAVUxQXzYSqSpF6hoQ6BU3POtSQ28xdIHN0KZf+9aAu0b8Fp
         UStw==
X-Gm-Message-State: AOAM533fEUg3AqyE9eOAzyCEFRx7ynlooEEc0H2BJOmAIaZYUdFa0BWg
        xghWuNuouEBGfnNIq1YLRCp3xBuc5/U=
X-Google-Smtp-Source: 
 ABdhPJzL9xdiNeojWZKa6LwA6l9D94N3uAy+fqgTEczM2Vsyqd+0+QgUFzKXCtvoQt36LfqqDF/W4BO8Huw=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f16f:a28e:552e:abea])
 (user=seanjc job=sendgmr) by 2002:a25:5f43:: with SMTP id
 h3mr2950650ybm.122.1612486678782;
 Thu, 04 Feb 2021 16:57:58 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Feb 2021 16:57:42 -0800
In-Reply-To: <20210205005750.3841462-1-seanjc@google.com>
Message-Id: <20210205005750.3841462-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210205005750.3841462-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 1/9] KVM: SVM: Move AVIC vCPU kicking snippet to helper
 function
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Jiri Kosina <trivial@kernel.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a helper function to handle kicking non-running vCPUs when sending
virtual IPIs.  A future patch will change SVM's interception functions
to take @vcpu instead of @svm, at which piont declaring and modifying
'vcpu' in a case statement is confusing, and potentially dangerous.

No functional change intended.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/svm/avic.c | 35 +++++++++++++++++++----------------
 1 file changed, 19 insertions(+), 16 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Remove misleading DR6/DR7 adjustments from RSM emulation
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12069093
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B3DBCC433E6
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:26:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 789DF64FB1
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 01:26:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232693AbhBEBZp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 4 Feb 2021 20:25:45 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:54570 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232684AbhBEBZo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 4 Feb 2021 20:25:44 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 773EEC06178C
        for <kvm@vger.kernel.org>; Thu,  4 Feb 2021 17:25:04 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id 11so5188645ybl.21
        for <kvm@vger.kernel.org>; Thu, 04 Feb 2021 17:25:04 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=4+ZJwerbDVsZaT3Nm4onzePXjuWx4rquZa0E2PQ0OPo=;
        b=Q5vYf6q7JlAbA40tkuiP2Ie3muwYhUzkhhXWdh+O5bh4/X/jzNBlkjC2c1/YRE6fOa
         XLgCwZaTgrGp3yDJLKxnT+dxotYylkrw6vjZtTcE4Z4u6X9ox1jxQLtQd9JPknqHCLGt
         kkCW/MNZGrDeNKAaSIG/FFFl2q4qsXt36iHgQ7eVZau44P/z0OwTkTyCdsz0A/56hJNN
         YQmJZ87sS1qn9pY3zpSEdxq9V9zI0xrYMX07iuEO5d5bTrYeHpQSy756hksx5fJp9II9
         d9Lj73Qt91qxlyeohOqO3TT6N8orOzq2bb9rg2hIea0u7wJOjAiNQLfPBixfMa0lZbiB
         xbgA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=4+ZJwerbDVsZaT3Nm4onzePXjuWx4rquZa0E2PQ0OPo=;
        b=b6OuI9jADn3iFg3m/oLsKUxoAiPyz+sXgsFEbeIvL7Z3wwOQXx2lL/HCeevDRtcTMW
         GNLJ8vl8yXPXldZj6wQJQXsNZOqBzZky6N/tNbG/mNZakJBIC73/O9eaZfuoGlEghGUF
         bINBO6t+SquQkPSTC5jfV9JU1oH7U6VBMQPsoXpZbph5e7oIod5Tvp3dlyHbC/L/W6TM
         7fQj1G3DMtVMbATMDYTaWWIdjOunrsXGaAUAP7yDjAbkq1h1MoCmiPylexSTJits0uR2
         4zl9pCnOqbQTbaF/XVcsF3C6+7EnXpMsn6UXhwqhOP/Oqwx5Z4q1pBJZYLcNoB9mNlAA
         tQ7Q==
X-Gm-Message-State: AOAM533dqh3DZCq3n4ReFnGp73hAnpBKCUbEzIpH1h3V1BpyMLyhaayB
        pMAuQTTv2xfwio6vhhX9yc3tSBQ4Agg=
X-Google-Smtp-Source: 
 ABdhPJxQbWPhpPQhhPoWTyDSVbXIZYVUrwa5vnhzf2uPGaQqfBgUdlrMSaWK6HgCbCrO0XrrT9/xvLpw+f8=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f16f:a28e:552e:abea])
 (user=seanjc job=sendgmr) by 2002:a25:698d:: with SMTP id
 e135mr2856644ybc.281.1612488303713;
 Thu, 04 Feb 2021 17:25:03 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  4 Feb 2021 17:24:57 -0800
In-Reply-To: <20210205012458.3872687-1-seanjc@google.com>
Message-Id: <20210205012458.3872687-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210205012458.3872687-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.365.g02bc693789-goog
Subject: [PATCH 1/2] KVM: x86: Remove misleading DR6/DR7 adjustments from RSM
 emulation
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Drop the DR6/7 volatile+fixed bits adjustments in RSM emulation, which
are redundant and misleading.  The necessary adjustments are made by
kvm_set_dr(), which properly sets the fixed bits that are conditional
on the vCPU model.

Note, KVM incorrectly reads only bits 31:0 of the DR6/7 fields when
emulating RSM on x86-64.  On the plus side for this change, that bug
makes removing "& DRx_VOLATILE" a nop.

No functional change intended.

Signed-off-by: Sean Christopherson <seanjc@google.com>
---
 arch/x86/kvm/emulate.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH RESEND] perf/x86/kvm: Add Cascade Lake Xeon steppings to isolation_ucodes[]
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 12070811
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.2 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C1612C433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 19:17:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6CC6764E3E
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 19:17:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233310AbhBERfB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 12:35:01 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55202 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231449AbhBERce (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 12:32:34 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id DEE94C061756
        for <kvm@vger.kernel.org>; Fri,  5 Feb 2021 11:14:17 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id f127so8087113ybf.12
        for <kvm@vger.kernel.org>; Fri, 05 Feb 2021 11:14:17 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=npmBBKW1fSgppgegxbQ2UWGEM0GM2JjG3Wy9uRJQQLQ=;
        b=DjDliZ2GNF1xL3OrQ8Aga+aiMXLiwuQsXYEUJYqxrI5FAufPlol/zReUe4BfGCmTbu
         KJPw1455ue25FsX3DkIH04cTAmteirbkniJHxw/fEJaWpR0MftvAM7+wB5ZDcdZWvdlF
         c58O3n7x6WQtxgj4emJvEHC5BZd5F4JSeYfpyOOBbqyxyxWQjLIt54SE1W7Iwt8wrIk4
         Flygac3k27k8QdXs3NbjH2nlPTESW3bR5CPyZm0MLhgyJfNJqgs5e/fRUtDdzQwcBIct
         DAMAj1uMjVsGOGZdr3iyYb1MpIDIg2wwnW91R7fQaFdMcbryRL6WLRaxwm/oFO3eVakO
         RObA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=npmBBKW1fSgppgegxbQ2UWGEM0GM2JjG3Wy9uRJQQLQ=;
        b=lGeffXOAklXmA0D0Xz/7SOJpPd4FLiQVLRxV+PsNNWb9khr8UWtHFZ8fklfS0pbaYp
         vX56p03U2zenIGTAssntmQoFlBqB4MfbL0IBIS2rbu/npupU9+f6lAayrjvNxNzYGmk0
         zv9yaBRYyCyoNNrx+GTPcac3EBAcN1Hi3qXkr1JetA+JCBYk707vlghb20OLtDiKceGZ
         wOhUg9ZRmpoaXHLVmdScRQaq7YklRI4+fB7MsAo2GBhqzlLP37NkLjWDhBQsoJPzbEKp
         G2EoNpU+NBguOqFpNd12I8ZtdmAoAwDirHkYyRyeGUcY+RqTcqPSoLAqqjxk6w1uP8/j
         t14w==
X-Gm-Message-State: AOAM531Co9W87IY4i4ldlFkFrgARIhVglFJTf3rvdVHsnW9dLIGhtXhE
        ke5wX+YVV4vM0lMbb1KguZbgwo3WpJm32g==
X-Google-Smtp-Source: 
 ABdhPJw24IwZIi59zeab2KoOsEyIRKVsyFrqL567IiIuKLAf/cDx9C4DImvnr9p8ZuvdwqwAfS5VVqehpbLQMw==
Sender: "jmattson via sendgmr" <jmattson@turtle.sea.corp.google.com>
X-Received: from turtle.sea.corp.google.com
 ([2620:15c:100:202:14c9:c13c:1ec5:db47])
 (user=jmattson job=sendgmr) by 2002:a25:888f:: with SMTP id
 d15mr8822203ybl.12.1612552457117; Fri, 05 Feb 2021 11:14:17 -0800 (PST)
Date: Fri,  5 Feb 2021 11:13:24 -0800
Message-Id: <20210205191324.2889006-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH RESEND] perf/x86/kvm: Add Cascade Lake Xeon steppings to
 isolation_ucodes[]
From: Jim Mattson <jmattson@google.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: Jim Mattson <jmattson@google.com>, Andi Kleen <ak@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Ingo Molnar <mingo@redhat.com>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Alexander Shishkin <alexander.shishkin@linux.intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Namhyung Kim <namhyung@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cascade Lake Xeon parts have the same model number as Skylake Xeon
parts, so they are tagged with the intel_pebs_isolation
quirk. However, as with Skylake Xeon H0 stepping parts, the PEBS
isolation issue is fixed in all microcode versions.

Add the Cascade Lake Xeon steppings (5, 6, and 7) to the
isolation_ucodes[] table so that these parts benefit from Andi's
optimization in commit 9b545c04abd4f ("perf/x86/kvm: Avoid unnecessary
work in guest filtering").

Signed-off-by: Jim Mattson <jmattson@google.com>
Cc: Andi Kleen <ak@linux.intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Arnaldo Carvalho de Melo <acme@kernel.org>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Alexander Shishkin <alexander.shishkin@linux.intel.com>
Cc: Jiri Olsa <jolsa@redhat.com>
Cc: Namhyung Kim <namhyung@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Reviewed-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/events/intel/core.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [RFC: timer passthrough 2/9] KVM: vmx: enable host lapic timer offload preemtion timer
##### From: Zhimin Feng <fengzhimin@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhimin Feng <fengzhimin@bytedance.com>
X-Patchwork-Id: 12069785
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A25FEC433DB
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:07:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 47BDF64FB9
	for <kvm@archiver.kernel.org>; Fri,  5 Feb 2021 10:07:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230159AbhBEKG6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 5 Feb 2021 05:06:58 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52648 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229774AbhBEKEX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 5 Feb 2021 05:04:23 -0500
Received: from mail-pj1-x1035.google.com (mail-pj1-x1035.google.com
 [IPv6:2607:f8b0:4864:20::1035])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78349C0617AA
        for <kvm@vger.kernel.org>; Fri,  5 Feb 2021 02:03:40 -0800 (PST)
Received: by mail-pj1-x1035.google.com with SMTP id nm1so3348995pjb.3
        for <kvm@vger.kernel.org>; Fri, 05 Feb 2021 02:03:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=ioiNjnFim0WwNMLpqZvgmNVZtgITdPMhocz2H3dneLk=;
        b=tlKgPMwOuPKHyoNc2MRRwpS5hMH4652VyHhYA/JCs3/B+VjFdmgMPIgdUxHAebTVOb
         M9fr27VcfQJ3aizjqK1dBq4vbo6HiNzEikaiLLZmFHi9ZmHjovVVcIjCx1hSiB+cOWcj
         weXml2M/LSiW/4vKoGKdAfh35IP9qrkzLoJGPpldPeXuyeX0balA+u9v6rDvNTyb5K+W
         Vn6NOKz7MdwD58Qz2BEeR5Xs8c9tuuICGE2S4yCNbVvyvse01zPDsCIXt+iPjniC0Nc9
         iQhhMR+w4bO5nTCwLFkY+72+EXVsB/h1s+RYruzTrnErrsm/ptP6RmFqZcB1clR55o6S
         mvCw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=ioiNjnFim0WwNMLpqZvgmNVZtgITdPMhocz2H3dneLk=;
        b=mzqzyPys6TZqbkPm5TbSQ7Q5aRhjqZgwzhr4Fg5AFIW/s2YYl6mkn100+u4tdv2VzV
         74BfzesGh5++wwvrXFPXEWo4cDk+A2JO/fAlf0aoisDsgunoCruwGtvxDOrMEGpflt3r
         ng6pcxXverZZaTHNY8EVhEDVb63kMkVJ1VsdLS4lRAXNmyVksS2f1JEUe5DHR7jCpV6i
         PMl6JzDInIKxCS9ZLT5lDAv5J1dcbZinE7ok4WBCzkFQ91Nmb68Ytfq42ffoY9RSfKry
         fza0IbuwNjyWRAQ83n7Mr1XMtcJniUHZeAwxNfzZDqXz5l0ngA8EYGZqDiBKt2ZorcBv
         Si8g==
X-Gm-Message-State: AOAM533U5WiPNYuuVZ3qlLXVRdb3ci+G7bb7mjNv5EOSNzaCI/yiSE6f
        FhqnAyPSyeXmbsqDDbMy09S22g==
X-Google-Smtp-Source: 
 ABdhPJytYhEvPY5WfM5al4ZEHEIDG7FVy08PoUnjYPNpd+F/ePJ3S9H0vKaxn5uWbd7IuPASeTbSpg==
X-Received: by 2002:a17:902:6b89:b029:da:fc41:baec with SMTP id
 p9-20020a1709026b89b02900dafc41baecmr3584404plk.39.1612519420061;
        Fri, 05 Feb 2021 02:03:40 -0800 (PST)
Received: from C02CC49MMD6R.bytedance.net ([139.177.225.239])
        by smtp.gmail.com with ESMTPSA id
 l12sm8142562pjg.54.2021.02.05.02.03.33
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 05 Feb 2021 02:03:39 -0800 (PST)
From: Zhimin Feng <fengzhimin@bytedance.com>
To: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        fweisbec@gmail.com, zhouyibo@bytedance.com,
        zhanghaozhong@bytedance.com, Zhimin Feng <fengzhimin@bytedance.com>
Subject: [RFC: timer passthrough 2/9] KVM: vmx: enable host lapic timer
 offload preemtion timer
Date: Fri,  5 Feb 2021 18:03:10 +0800
Message-Id: <20210205100317.24174-3-fengzhimin@bytedance.com>
X-Mailer: git-send-email 2.24.1 (Apple Git-126)
In-Reply-To: <20210205100317.24174-1-fengzhimin@bytedance.com>
References: <20210205100317.24174-1-fengzhimin@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use preemption timer to handle host timer

Signed-off-by: Zhimin Feng <fengzhimin@bytedance.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx/vmx.c          | 54 +++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c              |  1 +
 3 files changed, 56 insertions(+)

```
