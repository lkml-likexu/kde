

#### [RFC v3 0/8] vfio: expose virtual Shared Virtual Addressing to VMs
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
From patchwork Wed Jan 29 12:11:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11355983
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9761D138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:06:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7FF5020716
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:06:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726687AbgA2MGl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:06:41 -0500
Received: from mga03.intel.com ([134.134.136.65]:59027 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726067AbgA2MGk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:06:40 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:06:38 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="222433133"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 29 Jan 2020 04:06:38 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC v3 0/8] vfio: expose virtual Shared Virtual Addressing to VMs
Date: Wed, 29 Jan 2020 04:11:44 -0800
Message-Id: <1580299912-86084-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This VFIO series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes. For IOMMU and QEMU changes, they are in separate series (listed
in the "Related series").

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.


    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

There are roughly four parts in this patchset which are
corresponding to the basic vSVA support for PCI device
assignment
 1. vfio support for PASID allocation and free for VMs
 2. vfio support for guest page table binding request from VMs
 3. vfio support for IOMMU cache invalidation from VMs
 4. vfio support for vSVA usage on IOMMU-backed mdevs

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This RFC patchset is aiming for the phase 1 and phase 2, and works
together with the VT-d driver[1] changes and QEMU changes[2]. Complete
set for current vSVA can be found in below branch. This branch also
includes the patches for exposing PASID capability to VM, which will be
in another patchset.
https://github.com/luxis1999/linux-vsva: vsva-linux-5.5-rc3
old version: https://github.com/jacobpan/linux.git:siov_sva.

Related series:
[1] [PATCH V9 00/10] Nested Shared Virtual Address (SVA) VT-d support:
    https://lkml.org/lkml/2020/1/29/37
    [PATCH 0/3] IOMMU user API enhancement:
    https://lkml.org/lkml/2020/1/29/45

[2] [RFC v3 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
    The complete QEMU set can be found in below link:
    https://github.com/luxis1999/qemu.git: sva_vtd_v9_rfcv3

Changelog:
	- RFC v2 -> v3:
	  a) Refine the whole patchset to fit the roughly parts in this series
	  b) Adds complete vfio PASID management framework. e.g. pasid alloc,
	  free, reclaim in VM crash/down and per-VM PASID quota to prevent
	  PASID abuse.
	  c) Adds IOMMU uAPI version check and page table format check to ensure
	  version compatibility and hardware compatibility.
	  d) Adds vSVA vfio support for IOMMU-backed mdevs.

	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.

Liu Yi L (8):
  vfio: Add VFIO_IOMMU_PASID_REQUEST(alloc/free)
  vfio/type1: Make per-application (VM) PASID quota tunable
  vfio: Reclaim PASIDs when application is down
  vfio/type1: Add VFIO_NESTING_GET_IOMMU_UAPI_VERSION
  vfio/type1: Report 1st-level/stage-1 page table format to userspace
  vfio/type1: Bind guest page tables to host
  vfio/type1: Add VFIO_IOMMU_CACHE_INVALIDATE
  vfio/type1: Add vSVA support for IOMMU-backed mdevs

 drivers/vfio/vfio.c             | 183 +++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 421 ++++++++++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  21 ++
 include/uapi/linux/vfio.h       | 148 ++++++++++++++
 4 files changed, 773 insertions(+)
```
#### [RFC v3 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
From patchwork Wed Jan 29 12:16:31 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11356033
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 79C8F112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:11:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 56DAB20716
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:11:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726206AbgA2MLo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:11:44 -0500
Received: from mga04.intel.com ([192.55.52.120]:15927 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726140AbgA2MLo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:11:44 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:11:43 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="314070739"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga001.fm.intel.com with ESMTP; 29 Jan 2020 04:11:43 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, david@gibson.dropbear.id.au,
        pbonzini@redhat.com, alex.williamson@redhat.com, peterx@redhat.com
Cc: mst@redhat.com, eric.auger@redhat.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, jun.j.tian@intel.com, yi.y.sun@intel.com,
        kvm@vger.kernel.org, hao.wu@intel.com
Subject: [RFC v3 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
Date: Wed, 29 Jan 2020 04:16:31 -0800
Message-Id: <1580300216-86172-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

This QEMU series is intended to expose SVA usage to VMs. i.e. Sharing
guest application address space with passthru devices. This is called
vSVA in this series. The whole vSVA enabling requires QEMU/VFIO/IOMMU
changes. For IOMMU and VFIO changes, they are in separate series (listed
in the "Related series").

The high-level architecture for SVA virtualization is as below, the key
design of vSVA support is to utilize the dual-stage IOMMU translation (
also known as IOMMU nesting translation) capability in host IOMMU.

    .-------------.  .---------------------------.
    |   vIOMMU    |  | Guest process CR3, FL only|
    |             |  '---------------------------'
    .----------------/
    | PASID Entry |--- PASID cache flush -
    '-------------'                       |
    |             |                       V
    |             |                CR3 in GPA
    '-------------'
Guest
------| Shadow |--------------------------|--------
      v        v                          v
Host
    .-------------.  .----------------------.
    |   pIOMMU    |  | Bind FL for GVA-GPA  |
    |             |  '----------------------'
    .----------------/  |
    | PASID Entry |     V (Nested xlate)
    '----------------\.------------------------------.
    |             |   |SL for GPA-HPA, default domain|
    |             |   '------------------------------'
    '-------------'
Where:
 - FL = First level/stage one page tables
 - SL = Second level/stage two page tables

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This QEMU RFC patchset is aiming for the phase 1 and phase 2, and works
together with the VT-d driver[1] changes and VFIO changes[2].

Related series:
[1] [PATCH V9 00/10] Nested Shared Virtual Address (SVA) VT-d support:
    https://lkml.org/lkml/2020/1/29/37
    [PATCH 0/3] IOMMU user API enhancement:
    https://lkml.org/lkml/2020/1/29/45

[2] [RFC v3 0/8] vfio: expose virtual Shared Virtual Addressing to VMs
    https://lkml.org/lkml/2020/1/29/255

There are roughly four parts:
 1. Modify pci_setup_iommu() to set PCIIOMMUOps instead of setup PCIIOMMUFunc
 2. Introduce DualStageIOMMUObject as abstract of host IOMMU. It provides
    method for vIOMMU emulators to communicate with host IOMMU. e.g. propagate
    guest page table binding to host IOMMU to setup dual-stage DMA translation
    in host IOMMU and flush iommu iotlb.
 3. Introduce IOMMUContext as abstract of vIOMMU. It provides operations for
    VFIO to communicate with vIOMMU emulators. e.g. let vIOMMU emulators be
    aware of host IOMMU's dual-stage translation capability by registering
    DualStageIOMMUObject instances to vIOMMU emulators.
 4. Setup dual-stage IOMMU translation for Intel vIOMMU. Includes 
    - Check IOMMU uAPI version compatibility and hardware compatibility which
      is preparation for setting up dual-stage DMA translation in host IOMMU.
    - Propagate guest PASID allocation and free request to host.
    - Propagate guest page table binding to host to setup dual-stage IOMMU DMA
      translation in host IOMMU.
    - Propagate guest IOMMU cache invalidation to host to ensure iotlb
      correctness.

The complete QEMU set can be found in below link:
https://github.com/luxis1999/qemu.git: sva_vtd_v9_rfcv3

Complete kernel can be found in:
https://github.com/luxis1999/linux-vsva: vsva-linux-5.5-rc3

Changelog:
	- RFC v2 -> v3:
	  a) Introduce DualStageIOMMUObject to abstract the host IOMMU programming
	  capability. e.g. request PASID from host, setup IOMMU nesting translation
	  on host IOMMU. The pasid_alloc/bind_guest_page_table/iommu_cache_flush
	  operations are moved to be DualStageIOMMUOps. Thus, DualStageIOMMUObject
	  is an abstract layer which provides QEMU vIOMMU emulators with an explicit
	  method to program host IOMMU.
	  b) Compared with RFC v2, the IOMMUContext has also been updated. It is
	  modified to provide an abstract for vIOMMU emulators. It provides the
	  method for pass-through modules (like VFIO) to communicate with host IOMMU.
	  e.g. tell vIOMMU emulators about the IOMMU nesting capability on host side
	  and report the host IOMMU DMA translation faults to vIOMMU emulators.
	  RFC v2: https://www.spinics.net/lists/kvm/msg198556.html

	- RFC v1 -> v2:
	  Introduce IOMMUContext to abstract the connection between VFIO
	  and vIOMMU emulators, which is a replacement of the PCIPASIDOps
	  in RFC v1. Modify x-scalable-mode to be string option instead of
	  adding a new option as RFC v1 did. Refined the pasid cache management
	  and addressed the TODOs mentioned in RFC v1. 
	  RFC v1: https://patchwork.kernel.org/cover/11033657/

Eric Auger (1):
  scripts/update-linux-headers: Import iommu.h

Liu Yi L (23):
  hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
  hw/iommu: introduce DualStageIOMMUObject
  hw/pci: introduce pci_device_iommu_context()
  intel_iommu: provide get_iommu_context() callback
  header file update VFIO/IOMMU vSVA APIs
  vfio: pass IOMMUContext into vfio_get_group()
  vfio: check VFIO_TYPE1_NESTING_IOMMU support
  vfio: register DualStageIOMMUObject to vIOMMU
  vfio: get stage-1 pasid formats from Kernel
  vfio/common: add pasid_alloc/free support
  intel_iommu: modify x-scalable-mode to be string option
  intel_iommu: add virtual command capability support
  intel_iommu: process pasid cache invalidation
  intel_iommu: add PASID cache management infrastructure
  vfio: add bind stage-1 page table support
  intel_iommu: bind/unbind guest page table to host
  intel_iommu: replay guest pasid bindings to host
  intel_iommu: replay pasid binds after context cache invalidation
  intel_iommu: do not pass down pasid bind for PASID #0
  vfio: add support for flush iommu stage-1 cache
  intel_iommu: process PASID-based iotlb invalidation
  intel_iommu: propagate PASID-based iotlb invalidation to host
  intel_iommu: process PASID-based Device-TLB invalidation

Peter Xu (1):
  hw/iommu: introduce IOMMUContext

 hw/Makefile.objs                    |    1 +
 hw/alpha/typhoon.c                  |    6 +-
 hw/arm/smmu-common.c                |    6 +-
 hw/hppa/dino.c                      |    6 +-
 hw/i386/amd_iommu.c                 |    6 +-
 hw/i386/intel_iommu.c               | 1208 ++++++++++++++++++++++++++++++++++-
 hw/i386/intel_iommu_internal.h      |  119 ++++
 hw/i386/trace-events                |    6 +
 hw/iommu/Makefile.objs              |    2 +
 hw/iommu/dual_stage_iommu.c         |  101 +++
 hw/iommu/iommu_context.c            |   54 ++
 hw/pci-host/designware.c            |    6 +-
 hw/pci-host/ppce500.c               |    6 +-
 hw/pci-host/prep.c                  |    6 +-
 hw/pci-host/sabre.c                 |    6 +-
 hw/pci/pci.c                        |   39 +-
 hw/ppc/ppc440_pcix.c                |    6 +-
 hw/ppc/spapr_pci.c                  |    6 +-
 hw/s390x/s390-pci-bus.c             |    8 +-
 hw/vfio/ap.c                        |    2 +-
 hw/vfio/ccw.c                       |    2 +-
 hw/vfio/common.c                    |  244 ++++++-
 hw/vfio/pci.c                       |    3 +-
 hw/vfio/platform.c                  |    2 +-
 include/hw/i386/intel_iommu.h       |   59 +-
 include/hw/iommu/dual_stage_iommu.h |  103 +++
 include/hw/iommu/iommu_context.h    |   61 ++
 include/hw/pci/pci.h                |   13 +-
 include/hw/pci/pci_bus.h            |    2 +-
 include/hw/vfio/vfio-common.h       |    6 +-
 linux-headers/linux/iommu.h         |  372 +++++++++++
 linux-headers/linux/vfio.h          |  148 +++++
 scripts/update-linux-headers.sh     |    2 +-
 33 files changed, 2568 insertions(+), 49 deletions(-)
 create mode 100644 hw/iommu/Makefile.objs
 create mode 100644 hw/iommu/dual_stage_iommu.c
 create mode 100644 hw/iommu/iommu_context.c
 create mode 100644 include/hw/iommu/dual_stage_iommu.h
 create mode 100644 include/hw/iommu/iommu_context.h
 create mode 100644 linux-headers/linux/iommu.h
```
#### [RFC v1 0/2] vfio/pci: expose device's PASID capability to VMs
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
From patchwork Wed Jan 29 12:18:43 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Liu, Yi L" <yi.l.liu@intel.com>
X-Patchwork-Id: 11356107
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9D9561800
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:13:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7CF5020716
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 12:13:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726805AbgA2MNj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 07:13:39 -0500
Received: from mga18.intel.com ([134.134.136.126]:21973 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726484AbgA2MNc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 29 Jan 2020 07:13:32 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 29 Jan 2020 04:13:32 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,377,1574150400";
   d="scan'208";a="222434770"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 29 Jan 2020 04:13:32 -0800
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com,
        jean-philippe.brucker@arm.com, peterx@redhat.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RFC v1 0/2] vfio/pci: expose device's PASID capability to VMs
Date: Wed, 29 Jan 2020 04:18:43 -0800
Message-Id: <1580300325-86259-1-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Shared Virtual Addressing (SVA), a.k.a, Shared Virtual Memory (SVM) on
Intel platforms allows address space sharing between device DMA and
applications. SVA can reduce programming complexity and enhance security.

To enable SVA, device needs to have PASID capability, which is a key
capability for SVA. This patchset exposes the device's PASID capability
to guest instead of hiding it from guest.

The second patch emulates PASID capability for VFs (Virtual Function) since
VFs don't implement such capability per PCIe spec. This patch emulates such
capability and expose to VM if the capability is enabled in PF (Physical
Function).

However, there is an open for PASID emulation. If PF driver disables PASID
capability at runtime, then it may be an issue. e.g. PF should not disable
PASID capability if there is guest using this capability on any VF related
to this PF. To solve it, may need to introduce a generic communication
framework between vfio-pci driver and PF drivers. Please feel free to give
your suggestions on it.

Liu Yi L (2):
  vfio/pci: Expose PCIe PASID capability to guest
  vfio/pci: Emulate PASID/PRI capability for VFs

 drivers/vfio/pci/vfio_pci_config.c | 321 ++++++++++++++++++++++++++++++++++++-
 1 file changed, 318 insertions(+), 3 deletions(-)
```
#### [PATCH v8 0/4] KVM: s390: Add new reset vcpu API
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Jan 29 20:03:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11356757
Return-Path: <SRS0=InjK=3S=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8139B112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 20:03:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 691F72067C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 29 Jan 2020 20:03:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726332AbgA2UD2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 29 Jan 2020 15:03:28 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:60290 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726259AbgA2UD2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 29 Jan 2020 15:03:28 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00TJtkxH063564
        for <kvm@vger.kernel.org>; Wed, 29 Jan 2020 15:03:27 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xu5q5f34x-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 29 Jan 2020 15:03:27 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 29 Jan 2020 20:03:25 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 29 Jan 2020 20:03:22 -0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00TK2Tr644827116
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 29 Jan 2020 20:02:29 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CE42A11C04C;
        Wed, 29 Jan 2020 20:03:20 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3BFD611C050;
        Wed, 29 Jan 2020 20:03:19 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.2.173])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 29 Jan 2020 20:03:19 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com, david@redhat.com,
        cohuck@redhat.com, linux-s390@vger.kernel.org
Subject: [PATCH v8 0/4] KVM: s390: Add new reset vcpu API
Date: Wed, 29 Jan 2020 15:03:08 -0500
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012920-0028-0000-0000-000003D5957E
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012920-0029-0000-0000-00002499E1ED
Message-Id: <20200129200312.3200-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-29_06:2020-01-28,2020-01-29 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 impostorscore=0
 lowpriorityscore=0 adultscore=0 priorityscore=1501 mlxlogscore=852
 clxscore=1015 mlxscore=0 bulkscore=0 spamscore=0 suspectscore=1
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1911200001 definitions=main-2001290154
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's implement the remaining resets, namely the normal and clear
reset to improve architectural compliance. 

While we're at it, let's also start testing the new API.
Those tests are not yet complete, but will be extended in the future.

Janosch Frank (3):
  KVM: s390: Add new reset vcpu API
  selftests: KVM: Add fpu and one reg set/get library functions
  selftests: KVM: s390x: Add reset tests

Pierre Morel (1):
  selftests: KVM: testing the local IRQs resets

 Documentation/virt/kvm/api.txt                |  43 ++++
 arch/s390/kvm/kvm-s390.c                      | 103 +++++---
 include/uapi/linux/kvm.h                      |   5 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   6 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  48 ++++
 tools/testing/selftests/kvm/s390x/resets.c    | 222 ++++++++++++++++++
 7 files changed, 399 insertions(+), 29 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/s390x/resets.c
```
