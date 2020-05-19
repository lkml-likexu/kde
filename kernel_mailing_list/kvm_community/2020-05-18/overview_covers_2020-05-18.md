

#### [RFC PATCH v4 00/10] Introduce vendor ops in vfio-pci
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Mon May 18 02:42:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11554617
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C44A138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 02:52:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4A142207BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 02:52:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726833AbgERCwT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 May 2020 22:52:19 -0400
Received: from mga03.intel.com ([134.134.136.65]:24736 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726639AbgERCwT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 May 2020 22:52:19 -0400
IronPort-SDR: 
 SmoqznO1D0dVkBH3AVfpSvsozgkXwBaEdEXwtE9Ub9mCKUgL1HQVMjET40QHv7iO1XV9tL2xfV
 oEnV6VTRDc3w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 May 2020 19:52:18 -0700
IronPort-SDR: 
 dGpONDL4XINzTKKYCkvwOCfkoLHItmlDUewrlGxjlXzMlcvILb+Ls18jDQ6NBVLjVAZWKaO2sb
 TyupXRUwlv2w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,405,1583222400";
   d="scan'208";a="267371304"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga006.jf.intel.com with ESMTP; 17 May 2020 19:52:15 -0700
From: Yan Zhao <yan.y.zhao@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: alex.williamson@redhat.com, cohuck@redhat.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        xin.zeng@intel.com, hang.yuan@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH v4 00/10] Introduce vendor ops in vfio-pci
Date: Sun, 17 May 2020 22:42:02 -0400
Message-Id: <20200518024202.13996-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using vfio-pci to pass through devices, though it's desired to use
its default implementations in most of time, it is also sometimes
necessary to call vendors specific operations.
For example, in order to do device live migration, the way of dirty
pages detection and device state save-restore may be varied from device
to device.
Vendors may want to add a vendor device region or may want to
intercept writes to a BAR region.
So, in this series, we introduce a way to allow vendors to provide vendor
specific ops for VFIO devices and meanwhile export several vfio-pci
interfaces as default implementations to simplify code of vendor driver
and avoid duplication.

Vendor driver registration/unregistration goes like this:
(1) macros are provided to let vendor drivers register/unregister
vfio_pci_vendor_driver_ops to vfio_pci in their module_init() and
module_exit().
vfio_pci_vendor_driver_ops contains callbacks probe() and remove() and a
pointer to vfio_device_ops.

(2) vendor drivers define their module aliases as
"vfio-pci:$vendor_id-$device_id".
E.g. A vendor module for VF devices of Intel(R) Ethernet Controller XL710
family can define its module alias as MODULE_ALIAS("vfio-pci:8086-154c").

(3) when module vfio_pci is bound to a device, it would call modprobe in
user space for modules of alias "vfio-pci:$vendor_id-$device_id", which
would trigger unloaded vendor drivers to register their
vfio_pci_vendor_driver_ops to vfio_pci.
Then it searches registered ops list and calls probe() to test whether this
vendor driver supports this physical device.
A success probe() would make bind vfio device to vendor provided
vfio_device_ops, which would call exported default implementations in
vfio_pci_ops if necessary. 


                                        _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
                                  
 __________   (un)register vendor ops  |  ___________    ___________   |
|          |<----------------------------|    VF    |   |           |   
| vfio-pci |                           | |  vendor  |   | PF driver |  |
|__________|---------------------------->|  driver  |   |___________|   
     |           probe/remove()        |  -----------          |       |
     |                                                         |         
     |                                 |_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _|
    \|/                                                       \|/
-----------                                              ------------
|    VF   |                                              |    PF    |
-----------                                              ------------
                   a typical usage in SRIOV



Ref counts:
(1) vendor drivers must be a module and compiled to depend on module
vfio_pci.
(2) In vfio_pci, a successful register would add refs of itself, and a
successful unregister would derefs of itself.
(3) In vfio_pci, a successful probe() of a vendor driver would add ref of
the vendor module. It derefs of the vendor module after calling remove().
(4) macro provided to make sure vendor module always unregister itself in
its module_exit

Those are to prevent below conditions:
a. vfio_pci is unloaded after a successful register from vendor driver.
   Though vfio_pci would later call modprobe to ask the vendor module to
   register again, it cannot help if vendor driver remain as loaded
   across unloading-loading of vfio_pci.
b. vendor driver unregisters itself after successfully probed by vfio_pci.
c. circular dependency between vfio_pci and the vendor driver.
   if vfio_pci adds refs to both vfio_pci and vendor driver on a successful
   register and if vendor driver only do the unregistration in its module_exit,
   then it would have no chance to do the unregistration.


Patch Overview
patches 1-2 provide register/unregister interfaces for vendor drivers
Patch 3     exports several members in vdev, including vendor_data, and
            exports functions in vfio_pci_ops to allow them accessible
	    from vendor drivers.
patches 4-5 export some more vdev members to vendor driver to simplify
            their implementations.
patch 6     is from Tina Zhang to define vendor specific Irq type
            capability.
patch 7     introduces a new vendor defined irq type
            VFIO_IRQ_TYPE_REMAP_BAR_REGION.
patches 8-10
            use VF live migration driver for Intel's 710 SRIOV devices
            as an example of how to implement this vendor ops interface.
    patch 8 first let the vendor ops pass through VFs.
    patch 9 implements a migration region based on migration protocol
            defined in [1][2].
            (Some dirty page tracking functions are intentionally
            commented out and would send out later in future.)
    patch 10 serves as an example of how to define vendor specific irq
            type. This irq will trigger qemu to dynamic map BAR regions
	    in order to implement software based dirty page track.

Changelog:
RFC v3- RFC v4:
- use exported function to make vendor driver access internal fields of
  vdev rather than make struct vfio_pci_device public. (Alex)
- add a new interface vfio_pci_get_barmap() to call vfio_pci_setup_barma()
  and let vfio_pci_setup_barmap() still able to return detailed errno.
  (Alex)
- removed sample code to pass through igd devices. instead, use the
  first patch (patch 8/10) of i40e vf migration as an mere pass-through
  example.
- rebased code to 5.7 and VFIO migration kernel patches v17 and qemu
  patches v16.
- added a demo of vendor defined irq type.

RFC v2- RFC v3:
- embedding struct vfio_pci_device into struct vfio_pci_device_private.
(Alex)

RFC v1- RFC v2:
- renamed mediate ops to vendor ops
- use of request_module and module alias to manage vendor driver load
  (Alex)
- changed from vfio_pci_ops calling vendor ops
  to vendor ops calling default vfio_pci_ops  (Alex)
- dropped patches for dynamic traps of BARs. will submit them later.

Links:
[1] VFIO migration kernel v17:
    https://patchwork.kernel.org/cover/11466129/
[2] VFIO migration qemu v16:
    https://patchwork.kernel.org/cover/11456557/

Previous versions:
RFC v3: https://lkml.org/lkml/2020/2/11/142

RFC v2: https://lkml.org/lkml/2020/1/30/956

RFC v1:
kernel part: https://www.spinics.net/lists/kernel/msg3337337.html.
qemu part: https://www.spinics.net/lists/kernel/msg3337337.html.


Tina Zhang (1):
  vfio: Define device specific irq type capability

Yan Zhao (9):
  vfio/pci: register/unregister vfio_pci_vendor_driver_ops
  vfio/pci: macros to generate module_init and module_exit for vendor
    modules
  vfio/pci: export vendor_data, irq_type, num_regions, pdev and
    functions in vfio_pci_ops
  vfio/pci: let vfio_pci know number of vendor regions and vendor irqs
  vfio/pci: export vfio_pci_get_barmap
  vfio/pci: introduce a new irq type VFIO_IRQ_TYPE_REMAP_BAR_REGION
  i40e/vf_migration: VF live migration - pass-through VF first
  i40e/vf_migration: register a migration vendor region
  i40e/vf_migration: vendor defined irq_type to support dynamic bar map

 drivers/net/ethernet/intel/Kconfig            |  10 +
 drivers/net/ethernet/intel/i40e/Makefile      |   2 +
 .../ethernet/intel/i40e/i40e_vf_migration.c   | 904 ++++++++++++++++++
 .../ethernet/intel/i40e/i40e_vf_migration.h   | 119 +++
 drivers/vfio/pci/vfio_pci.c                   | 181 +++-
 drivers/vfio/pci/vfio_pci_private.h           |   9 +
 drivers/vfio/pci/vfio_pci_rdwr.c              |  10 +
 include/linux/vfio.h                          |  58 ++
 include/uapi/linux/vfio.h                     |  30 +-
 9 files changed, 1311 insertions(+), 12 deletions(-)
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.c
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.h
```
#### [PATCH Kernel v22 0/8] Add UAPIs to support migration for VFIO
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
From patchwork Mon May 18 05:56:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11554787
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 38486913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:29:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1913E2070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:29:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="XVy6wqCU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726428AbgERG3v (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 02:29:51 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:16025 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726392AbgERG3u (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 02:29:50 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ec22ad10000>; Sun, 17 May 2020 23:27:29 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Sun, 17 May 2020 23:29:50 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Sun, 17 May 2020 23:29:50 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Mon, 18 May
 2020 06:29:50 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Mon, 18 May 2020 06:29:43 +0000
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
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v22 0/8] Add UAPIs to support migration for VFIO
 devices
Date: Mon, 18 May 2020 11:26:29 +0530
Message-ID: <1589781397-28368-1-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589783249; bh=z5s0G1rBNDFNSQh85iVTLhrKf5MN7oaEfN98Ihh4ZGE=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         X-NVConfidentiality:MIME-Version:Content-Type;
        b=XVy6wqCUTrRwPWt9etAsHLPEHZJNIRYBUW5uXvYyRRZuqbR0T8YC7R/453iq/+Ykc
         TLFxmLNYjVnQRPQQnA/Jzs+NhqKQiseQXD/3SAvg8a1RKT5UVTVP5+UcnYKXhBfQBR
         lUpTNm5P1vpV1MhKn1d1zbUQUYxKacWkS9D6dUV4rglR+swodlrrg+LXwG2DU8Srwq
         QHp5RDQYjTrXmo0lx0cDpfC3bbZdvYITBnk2oKEjIJqsoy2yEZOMB+HNYkDR6uEs6q
         1IZQawGBDrCW4fSc2Xj+Zh92Wq99uR4520GgJYJfHNrWcWgxjxCrugk4+NHP1a6Tkw
         ryxj0nabyqcMw==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This patch set adds:
* IOCTL VFIO_IOMMU_DIRTY_PAGES to get dirty pages bitmap with
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

* Patch 8 detect if IOMMU capable device driver is smart to report pages
  to be marked dirty by pinning pages using vfio_pin_pages() API.


Yet TODO:
Since there is no device which has hardware support for system memmory
dirty bitmap tracking, right now there is no other API from vendor driver
to VFIO IOMMU module to report dirty pages. In future, when such hardware
support will be implemented, an API will be required such that vendor
driver could report dirty pages to VFIO module during migration phases.

Adding revision history from previous QEMU patch set to understand KABI
changes done till now

v21 -> v22
- Fixed issue raised by Alex :
https://lore.kernel.org/kvm/20200515163307.72951dd2@w520.home/

v20 -> v21
- Added checkin for GET_BITMAP ioctl for vfio_dma boundaries.
- Updated unmap ioctl function - as suggested by Alex.
- Updated comments in DIRTY_TRACKING ioctl definition - as suggested by
  Cornelia.

v19 -> v20
- Fixed ioctl to get dirty bitmap to get bitmap of multiple vfio_dmas
- Fixed unmap ioctl to get dirty bitmap of multiple vfio_dmas.
- Removed flag definition from migration capability.

v18 -> v19
- Updated migration capability with supported page sizes bitmap for dirty
  page tracking and  maximum bitmap size supported by kernel module.
- Added patch to calculate and cache pgsize_bitmap when iommu->domain_list
  is updated.
- Removed extra buffers added in previous version for bitmap manipulation
  and optimised the code.

v17 -> v18
- Add migration capability to the capability chain for VFIO_IOMMU_GET_INFO
  ioctl
- Updated UMAP_DMA ioctl to return bitmap of multiple vfio_dma

v16 -> v17
- Fixed errors reported by kbuild test robot <lkp@intel.com> on i386

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




Kirti Wankhede (8):
  vfio: UAPI for migration interface for device state
  vfio iommu: Remove atomicity of ref_count of pinned pages
  vfio iommu: Cache pgsize_bitmap in struct vfio_iommu
  vfio iommu: Add ioctl definition for dirty pages tracking
  vfio iommu: Implementation of ioctl for dirty pages tracking
  vfio iommu: Update UNMAP_DMA ioctl to get dirty bitmap before unmap
  vfio iommu: Add migration capability to report supported features
  vfio: Selective dirty page tracking if IOMMU backed device pins pages

 drivers/vfio/vfio.c             |  13 +-
 drivers/vfio/vfio_iommu_type1.c | 576 ++++++++++++++++++++++++++++++++++++----
 include/linux/vfio.h            |   4 +-
 include/uapi/linux/vfio.h       | 315 ++++++++++++++++++++++
 4 files changed, 849 insertions(+), 59 deletions(-)
```
#### [PATCH 0/2] Expose KVM API to Linux Kernel
##### From: Anastassios Nanos <ananos@nubificus.co.uk>

```c
From patchwork Mon May 18 06:58:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anastassios Nanos <ananos@nubificus.co.uk>
X-Patchwork-Id: 11554903
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B27790
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:58:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F0A6720715
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 06:58:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726729AbgERG6M (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 02:58:12 -0400
Received: from mail-wr1-f66.google.com ([209.85.221.66]:42032 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726127AbgERG6M (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 02:58:12 -0400
Received: by mail-wr1-f66.google.com with SMTP id s8so10395725wrt.9;
        Sun, 17 May 2020 23:58:10 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition:user-agent;
        bh=+D77RfiJOu4D1YxT/E/Zl3KQA8PQ7qtZd5MuZFWy0Z8=;
        b=bdQ/cCAZQ1MOKoBpBHIzjPaR/Gs+HaeYxxDKTceBSKIAfY6Lp/Ckpf5TdtCi+9jiRL
         3ToZI9zfsBEXd2+YYDoS95rHpzCVDZnY3eozuL7bDs1tfGBVeFiVmbNrXgPNBXPUUAHJ
         OxcGrIfOGTLDxVsNVtAS/hnK0AzMlGBQE+QokfCJPYxlDJnhv7C2JdXQGMpZuLWuU0xx
         axvJ/HAq7U8TjvAxnQ44qi5ONpPY/RiMmcyAFhUszR2B44iL8TK/iPl3stOkDNQbQppo
         pthc+LNsIsr0e9wqJ8EkgFlSoEyCyYKfNN7VkjKKIX3ZP3kAklDicAPPArWH1KVLZ2RO
         ai0w==
X-Gm-Message-State: AOAM532WIBFvWXcTgxYqh5UoqRr8XnUvXxhgkqjh6S/RVSLfTaNmRUTq
        f44DaoBVl2drKVqbN6T7QmI=
X-Google-Smtp-Source: 
 ABdhPJyxw+2tvhwUPs5V0h23SzHGXLChNa2LJLySoY5UzfK9tiPx/GZscXXrz3LabEGdcG6dz3I77A==
X-Received: by 2002:adf:f981:: with SMTP id f1mr17802097wrr.244.1589785089337;
        Sun, 17 May 2020 23:58:09 -0700 (PDT)
Received: from bf.nubificus.co.uk ([2a02:587:b919:800:aaa1:59ff:fe09:f176])
        by smtp.gmail.com with ESMTPSA id
 x184sm15563684wmg.38.2020.05.17.23.58.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sun, 17 May 2020 23:58:08 -0700 (PDT)
Date: Mon, 18 May 2020 09:58:05 +0300
From: Anastassios Nanos <ananos@nubificus.co.uk>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-kernel@vger.kernel.org
Cc: Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH 0/2] Expose KVM API to Linux Kernel
Message-ID: <cover.1589784221.git.ananos@nubificus.co.uk>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To spawn KVM-enabled Virtual Machines on Linux systems, one has to use
QEMU, or some other kind of VM monitor in user-space to host the vCPU
threads, I/O threads and various other book-keeping/management mechanisms.
This is perfectly fine for a large number of reasons and use cases: for
instance, running generic VMs, running general purpose Operating systems
that need some kind of emulation for legacy boot/hardware etc.

What if we wanted to execute a small piece of code as a guest instance,
without the involvement of user-space? The KVM functions are already doing
what they should: VM and vCPU setup is already part of the kernel, the only
missing piece is memory handling.

With these series, (a) we expose to the Linux Kernel the bare minimum KVM
API functions in order to spawn a guest instance without the intervention
of user-space; and (b) we tweak the memory handling code of KVM-related
functions to account for another kind of guest, spawned in kernel-space.

PATCH #1 exposes the needed stub functions, whereas PATCH #2 introduces the
changes in the KVM memory handling code for x86_64 and aarch64.

An example of use is provided based on kvmtest.c
[https://lwn.net/Articles/658512/] at
https://github.com/cloudkernels/kvmmtest

Anastassios Nanos (2):
  KVMM: export needed symbols
  KVMM: Memory and interface related changes

 arch/arm64/include/asm/kvm_host.h   |   6 ++
 arch/arm64/kvm/fpsimd.c             |   8 +-
 arch/arm64/kvm/guest.c              |  48 +++++++++++
 arch/x86/include/asm/fpu/internal.h |  10 ++-
 arch/x86/kvm/cpuid.c                |  25 ++++++
 arch/x86/kvm/emulate.c              |   3 +-
 arch/x86/kvm/vmx/vmx.c              |   3 +-
 arch/x86/kvm/x86.c                  |  38 ++++++++-
 include/linux/kvm_host.h            |  36 +++++++++
 virt/kvm/arm/arm.c                  |  18 +++++
 virt/kvm/arm/mmu.c                  |  34 +++++---
 virt/kvm/async_pf.c                 |   4 +-
 virt/kvm/coalesced_mmio.c           |   6 ++
 virt/kvm/kvm_main.c                 | 120 ++++++++++++++++++++++------
 14 files changed, 316 insertions(+), 43 deletions(-)
```
#### [PATCH v2 0/7] exec/memory: Enforce checking MemTxResult values
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
From patchwork Mon May 18 15:53:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <f4bug@amsat.org>
X-Patchwork-Id: 11555617
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AAD73913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 15:53:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 941D6207ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 15:53:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="tLXmLd86"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728210AbgERPxL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 11:53:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42532 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727050AbgERPxL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 11:53:11 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 27674C061A0C
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 08:53:11 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id z72so32623wmc.2
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 08:53:11 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=W0NZH996mfqrH/xeDmImG2NwLarasbVlVoAElHsd8sQ=;
        b=tLXmLd86dVALrDyfRBSDM7xGyBzx8PJJWlY3i38vW6q9/Pq2n5mt3ItbF9uZKtViWL
         5wjAhT45r111vXSVIQUuwkb/+pC4BmSqWADibN6q3Locg2JVINUoZqSROZBnySBdcKu2
         o7icrgMjNdj41GvG+1h7CXICRijZyk9PCqmL73xjibtIUlwr5m8fU954ESI+FigCiT6C
         bs8ilZH4spkBeWmS9qFncwqfwwrAdAuMAk77e2TsE5z07YnW6/jjk8LqIzgX5aLh8Lf3
         32nm7cFpyxPY9VYf1Y8EuTeXM0FeWyXQRN+cYia6fpPx0obBb5QsL6e2VcrOwfrxbO5A
         rQTw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=W0NZH996mfqrH/xeDmImG2NwLarasbVlVoAElHsd8sQ=;
        b=cGNwaBONmF5FoTP5BpAY+ejnKL2dS3XoL/4EtY6D6qS1Zv7V3+mjW9cqceupD1TH0V
         sx13L+WxrO22b1KFkfyxb4zk/nc4Qtz6PvfTMqkM+rmT2fbpu5WBSrD75rUFzbXZxTrB
         Bo+vh1fyKkgqd44BBNELyZp282ZKuSs4Fjruf9/7IQGmo5cfx2nhKVpOcH59p9ZROYFC
         I/IbMeUOZiCR/naENPIy7GqDlckAxVyufPPkn+by06xZcV6skmIcM9NE5YZM9IkdNH2U
         KCqdKVZyz2s/Znf6YUMWdp5kurQqfNMRc83zDY/QIVW5Z1p8zOxlKUZytNYgaBVsVGw2
         +Dkw==
X-Gm-Message-State: AOAM530y64jPTVePt80POMU6WLkews+pAaa2mB033blNX8GApjvWbKhS
        O3H/W6dmLwyGI10bocDEbEI=
X-Google-Smtp-Source: 
 ABdhPJwFfUufdYrC8E/cFB2xycdYjZB2Yu69MdjITV5JZ/mrnUeCukTsqIzH1kqKOnPbmTGUwxINOQ==
X-Received: by 2002:a7b:c948:: with SMTP id i8mr41508wml.138.1589817189954;
        Mon, 18 May 2020 08:53:09 -0700 (PDT)
Received: from x1w.redhat.com (17.red-88-21-202.staticip.rima-tde.net.
 [88.21.202.17])
        by smtp.gmail.com with ESMTPSA id
 7sm17647462wra.50.2020.05.18.08.53.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 18 May 2020 08:53:09 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
 Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
 qemu-arm@nongnu.org, Richard Henderson <rth@twiddle.net>, =?utf-8?q?Philipp?=
	=?utf-8?q?e_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v2 0/7] exec/memory: Enforce checking MemTxResult values
Date: Mon, 18 May 2020 17:53:01 +0200
Message-Id: <20200518155308.15851-1-f4bug@amsat.org>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Various places ignore the MemTxResult indicator of
transaction failed. Fix the easy places.
The rest are the DMA devices, which require deeper
analysis.

Since v1:
- Dropped "exec/memory: Emit warning when MemTxResult is ignored"
  https://www.mail-archive.com/qemu-devel@nongnu.org/msg704180.html

Philippe Mathieu-Daudé (7):
  exec: Let address_space_read/write_cached() propagate MemTxResult
  exec: Propagate cpu_memory_rw_debug() error
  disas: Let disas::read_memory() handler return EIO on error
  hw/elf_ops: Do not ignore write failures when loading ELF
  hw/arm/boot: Abort if set_kernel_args() fails
  accel/kvm: Let KVM_EXIT_MMIO return error
  hw/core/loader: Assert loading ROM regions succeeds at reset

 include/exec/cpu-all.h |  1 +
 include/exec/memory.h  | 19 +++++++++++--------
 include/hw/elf_ops.h   | 11 ++++++++---
 accel/kvm/kvm-all.c    | 13 +++++++------
 disas.c                | 13 ++++++++-----
 exec.c                 | 28 ++++++++++++++++------------
 hw/arm/boot.c          | 19 +++++++++++++------
 hw/core/loader.c       |  8 ++++++--
 8 files changed, 70 insertions(+), 42 deletions(-)
```
#### [kvm-unit-tests PATCH v7 00/12] s390x: Testing the Channel Subsystem
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon May 18 16:07:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11555653
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE434739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 16:07:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD068207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 16:07:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728271AbgERQHj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 12:07:39 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55078 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727005AbgERQHj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 May 2020 12:07:39 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04IG1naA046194;
        Mon, 18 May 2020 12:07:38 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 312cayexp0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 12:07:37 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04IG1ol1046319;
        Mon, 18 May 2020 12:07:37 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 312cayexn3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 12:07:37 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04IG5dBY016149;
        Mon, 18 May 2020 16:07:35 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma04ams.nl.ibm.com with ESMTP id 3127t5mf8y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 May 2020 16:07:35 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04IG7XEX61866272
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 May 2020 16:07:33 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D98E811C050;
        Mon, 18 May 2020 16:07:32 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8326911C04A;
        Mon, 18 May 2020 16:07:32 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.158.244])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 18 May 2020 16:07:32 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v7 00/12] s390x: Testing the Channel Subsystem
 I/O
Date: Mon, 18 May 2020 18:07:19 +0200
Message-Id: <1589818051-20549-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-18_06:2020-05-15,2020-05-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0
 lowpriorityscore=0 mlxscore=0 suspectscore=1 spamscore=0 impostorscore=0
 malwarescore=0 adultscore=0 bulkscore=0 clxscore=1015 mlxlogscore=999
 priorityscore=1501 cotscore=-2147483648 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005180134
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Goal of the series is to have a framework to test Channel-Subsystem I/O with
QEMU/KVM.
  
To be able to support interrupt for CSS I/O and for SCLP we need to modify
the interrupt framework to allow re-entrant interruptions.
  
We add a registration for IRQ callbacks to the test program to define its own
interrupt handler. We need to do special work under interrupt like acknowledging
the interrupt.
  
Being working on PSW bits to allow I/O interrupt, we define new PSW bits
in arch_def.h and use __ASSEMBLER__ define to be able to include this header
in an assembler source file.

This series presents four major tests:
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
        the Control unit type being 0xc0ca
        Checks SSCH(READ) and IO-IRQ

- ping-pong:
        If the reference channel leads to the PONG device (0xc0ca),
        the test exchanges a string containing a 9 digit number with
        the PONG device and expecting this number to be incremented
        by the PONG device.
        Checks SSCH(WRITE)


Note:
- The following patches may be pulled first:
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them
  s390x: export the clock get_clock_ms() utility
  s390x: use get_clock_ms() to calculate a delay in ms

- I think this one if it receives reviewed-by can also be pulled now:
  s390x: define function to wait for interrupt

- this patch has a comment from Janosch who asks change so... need opinion:
  but since I need reviews for the next patches I let it here unchanged.
  s390x: interrupt registration

- These 5 patches are really I/O oriented and need reviewed-by:
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

Regards,
Pierre

Pierre Morel (12):
  s390x: saving regs for interrupts
  s390x: Use PSW bits definitions in cstart
  s390x: Move control register bit definitions and add AFP to them
  s390x: interrupt registration
  s390x: export the clock get_clock_ms() utility
  s390x: use get_clock_ms() to calculate a delay in ms
  s390x: Library resources for CSS tests
  s390x: css: stsch, enumeration test
  s390x: css: msch, enable test
  s390x: define function to wait for interrupt
  s390x: css: ssch/tsch with sense and interrupt
  s390x: css: ping pong

 lib/s390x/asm/arch_def.h |  32 +++-
 lib/s390x/asm/time.h     |  36 ++++
 lib/s390x/css.h          | 279 ++++++++++++++++++++++++++++++
 lib/s390x/css_dump.c     | 157 +++++++++++++++++
 lib/s390x/css_lib.c      |  55 ++++++
 lib/s390x/interrupt.c    |  23 ++-
 lib/s390x/interrupt.h    |   8 +
 s390x/Makefile           |   3 +
 s390x/css.c              | 355 +++++++++++++++++++++++++++++++++++++++
 s390x/cstart64.S         |  58 +++++--
 s390x/intercept.c        |  11 +-
 s390x/unittests.cfg      |   4 +
 12 files changed, 995 insertions(+), 26 deletions(-)
 create mode 100644 lib/s390x/asm/time.h
 create mode 100644 lib/s390x/css.h
 create mode 100644 lib/s390x/css_dump.c
 create mode 100644 lib/s390x/css_lib.c
 create mode 100644 lib/s390x/interrupt.h
 create mode 100644 s390x/css.c
```
#### [PATCH  0/2] Fix VMX preemption timer migration
##### From: Makarand Sonare <makarandsonare@google.com>

```c
From patchwork Mon May 18 20:15:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11556285
Return-Path: <SRS0=OZeJ=7A=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E9F313B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 20:16:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 037FB20674
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 May 2020 20:16:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="PtcPYJSW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726378AbgERUQS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 May 2020 16:16:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55806 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726250AbgERUQR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 May 2020 16:16:17 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B9AD0C061A0C
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 13:16:17 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id o16so13250426qto.12
        for <kvm@vger.kernel.org>; Mon, 18 May 2020 13:16:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=E/Lnnyqh/lIivI+1URST7q6N2yYOibnHjeOOhY+GB/M=;
        b=PtcPYJSWjRgmemqaf9hq8pOmW726EE92vxW7O2VPll+hIdFZJmUcU0wKaEx7c/O8xG
         rpW7rf/D7XLOXq9OT3kOZb5suGSrlzYRwNnz9qAkCO8C3zFjg+cMresPJE+7MQvj1Ky4
         tb2zXw/dPCGjpArbWXdXeqpO6a0J86QANu+nhkRwHc8ApVJ6/L0dwr0PjO4xonQ1HzHn
         w8OyimH8H+JdPNeEIK7VcALgT7SWQFLttW9f8UmhA5Eyt06+iiJGj2kZv8Lr9Zv6Kikf
         7npoJFCKx02vxw8/jJ/BQ56s0zKY22sNf3qsGhqkeTT9qBjd75XPreCswLbXm9TqCoax
         6zKw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=E/Lnnyqh/lIivI+1URST7q6N2yYOibnHjeOOhY+GB/M=;
        b=ueqDiIcX6GFpXcctp3W46NzhajnzeLy7H+RliO8w7BSq9gD5cIcVdBfXjP/EHgKtUf
         B3xgBiUcWEBtkRttPLeik1Dowezq1bZLxJXdgTUSNO6w9em5kBy5yjWQTDNd5yII6F1u
         7Zwo+lJIYPnB+IWpeBRVejHnQsaxvaei5R6fwJYneQ0WpbJvxwh6BtxRbKV18UykQWQ2
         puwjeMR8lwWdoS7ogpxWpnBAZ7Ukhgk05NlPm2lgiZOa26nslapnNdixklBVa41KBQH8
         bWrMrLoOg+mvUGA1WtNY1u8VrAvurX2g2b1bCp7VbBMOUTvPIClsr5jZ0JbXAq52s0Bh
         F7/Q==
X-Gm-Message-State: AOAM530XMjeDSZTrYBVyCvd6dETkVHdzBNbLzG92iZku3L00lDwYdTQd
        QeiBRx4MYjCgI8rwFFwo5bGvR+ppKdLQa4ssFbZ6n1MWxknjjW075Nf4EbuAyfuMefMgIGfbC1p
        JM5J01yWD7Ngm7nCCUtnAzO1i8eEOpnrYWhILxdn4S40ESJzz6Z8jvrEkfSiHWzxsrZvT6JZFvF
        BEZq8=
X-Google-Smtp-Source: 
 ABdhPJy691o5sLjc2nzmh9X7ocGJANa+iBKDwes9LiQsV058FJOvj21R96Dq4hERKutpZtjYsEgOz0FG574G6RctQNk6sg==
X-Received: by 2002:a25:4cc4:: with SMTP id
 z187mr30161244yba.274.1589832976751;
 Mon, 18 May 2020 13:16:16 -0700 (PDT)
Date: Mon, 18 May 2020 13:15:58 -0700
Message-Id: <20200518201600.255669-1-makarandsonare@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.26.2.761.g0e0b3e54be-goog
Subject: [PATCH  0/2] Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix VMX preemption timer migration. Add a selftest to ensure post migration
both L1 and L2 VM observe the VMX preemption timer exit close to the original
expiration deadline.

Makarand Sonare (1):
  KVM: selftests: VMX preemption timer migration test

Peter Shier (1):
  KVM: nVMX: Fix VMX preemption timer migration

 Documentation/virt/kvm/api.rst                |   4 +
 arch/x86/include/uapi/asm/kvm.h               |   2 +
 arch/x86/kvm/vmx/nested.c                     |  61 ++++-
 arch/x86/kvm/vmx/vmx.h                        |   1 +
 arch/x86/kvm/x86.c                            |   3 +-
 include/uapi/linux/kvm.h                      |   1 +
 tools/arch/x86/include/uapi/asm/kvm.h         |   3 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |  11 +-
 .../selftests/kvm/include/x86_64/vmx.h        |  27 ++
 .../kvm/x86_64/vmx_preemption_timer_test.c    | 256 ++++++++++++++++++
 13 files changed, 362 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_preemption_timer_test.c
---
2.26.2.761.g0e0b3e54be-goog
```
