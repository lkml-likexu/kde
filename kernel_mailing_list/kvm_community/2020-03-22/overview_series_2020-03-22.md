#### [PATCH v1 01/22] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11451687
Return-Path: <SRS0=VAWz=5H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0DA491668
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:30:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E166E20732
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:30:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727026AbgCVMai (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 22 Mar 2020 08:30:38 -0400
Received: from mga17.intel.com ([192.55.52.151]:58572 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726940AbgCVMai (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 22 Mar 2020 08:30:38 -0400
IronPort-SDR: 
 WETHpbE3YDoZbVUpxwj38q9Do9e44OWSVm9cZBkccbTbThwXMRIYOgEMjZgwRUQ6gGlRR/tAm3
 NVWOmlHGmyOg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Mar 2020 05:30:38 -0700
IronPort-SDR: 
 htDY/owjdKMDnf6H8wwZhdcxULwRXP+FHsPWdgWI8nSmhCEYFBXpTgRTVHQgrHIXh25HyvV59a
 ioB6EBufEIWg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,292,1580803200";
   d="scan'208";a="239664353"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 22 Mar 2020 05:30:37 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: eric.auger@redhat.com, pbonzini@redhat.com, mst@redhat.com,
        david@gibson.dropbear.id.au, kevin.tian@intel.com,
        yi.l.liu@intel.com, jun.j.tian@intel.com, yi.y.sun@intel.com,
        kvm@vger.kernel.org, hao.wu@intel.com, jean-philippe@linaro.org,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH v1 01/22] scripts/update-linux-headers: Import iommu.h
Date: Sun, 22 Mar 2020 05:35:58 -0700
Message-Id: <1584880579-12178-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1584880579-12178-1-git-send-email-yi.l.liu@intel.com>
References: <1584880579-12178-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v1 1/8] vfio: Add VFIO_IOMMU_PASID_REQUEST(alloc/free)
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11451677
Return-Path: <SRS0=VAWz=5H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24CDF139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:27:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F0F45207FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:27:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727226AbgCVM0x (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 22 Mar 2020 08:26:53 -0400
Received: from mga18.intel.com ([134.134.136.126]:51561 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726756AbgCVM0Z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 22 Mar 2020 08:26:25 -0400
IronPort-SDR: 
 CH2Qsc4v6+3MwLJ2gcRPep9QECMA3bPWY+ZTEga/hiigxK+rqH6/CEJfDgsSKvFOeW78hopaVH
 MZ7odHuL6G+w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Mar 2020 05:26:23 -0700
IronPort-SDR: 
 ZK/YYV802jEaczSnu2jl2XuKM9yPHRrtgpD/8bTIknWnbmThjU3Xa8I7PoPuumtk6wIWV1xt6S
 gxMaFk0KBPhg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,292,1580803200";
   d="scan'208";a="239663865"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga008.jf.intel.com with ESMTP; 22 Mar 2020 05:26:23 -0700
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com, jean-philippe@linaro.org,
        peterx@redhat.com, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org, hao.wu@intel.com
Subject: [PATCH v1 1/8] vfio: Add VFIO_IOMMU_PASID_REQUEST(alloc/free)
Date: Sun, 22 Mar 2020 05:31:58 -0700
Message-Id: <1584880325-10561-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1584880325-10561-1-git-send-email-yi.l.liu@intel.com>
References: <1584880325-10561-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@intel.com>

For a long time, devices have only one DMA address space from platform
IOMMU's point of view. This is true for both bare metal and directed-
access in virtualization environment. Reason is the source ID of DMA in
PCIe are BDF (bus/dev/fnc ID), which results in only device granularity
DMA isolation. However, this is changing with the latest advancement in
I/O technology area. More and more platform vendors are utilizing the PCIe
PASID TLP prefix in DMA requests, thus to give devices with multiple DMA
address spaces as identified by their individual PASIDs. For example,
Shared Virtual Addressing (SVA, a.k.a Shared Virtual Memory) is able to
let device access multiple process virtual address space by binding the
virtual address space with a PASID. Wherein the PASID is allocated in
software and programmed to device per device specific manner. Devices
which support PASID capability are called PASID-capable devices. If such
devices are passed through to VMs, guest software are also able to bind
guest process virtual address space on such devices. Therefore, the guest
software could reuse the bare metal software programming model, which
means guest software will also allocate PASID and program it to device
directly. This is a dangerous situation since it has potential PASID
conflicts and unauthorized address space access. It would be safer to
let host intercept in the guest software's PASID allocation. Thus PASID
are managed system-wide.

This patch adds VFIO_IOMMU_PASID_REQUEST ioctl which aims to passdown
PASID allocation/free request from the virtual IOMMU. Additionally, such
requests are intended to be invoked by QEMU or other applications which
are running in userspace, it is necessary to have a mechanism to prevent
single application from abusing available PASIDs in system. With such
consideration, this patch tracks the VFIO PASID allocation per-VM. There
was a discussion to make quota to be per assigned devices. e.g. if a VM
has many assigned devices, then it should have more quota. However, it
is not sure how many PASIDs an assigned devices will use. e.g. it is
possible that a VM with multiples assigned devices but requests less
PASIDs. Therefore per-VM quota would be better.

This patch uses struct mm pointer as a per-VM token. We also considered
using task structure pointer and vfio_iommu structure pointer. However,
task structure is per-thread, which means it cannot achieve per-VM PASID
alloc tracking purpose. While for vfio_iommu structure, it is visible
only within vfio. Therefore, structure mm pointer is selected. This patch
adds a structure vfio_mm. A vfio_mm is created when the first vfio
container is opened by a VM. On the reverse order, vfio_mm is free when
the last vfio container is released. Each VM is assigned with a PASID
quota, so that it is not able to request PASID beyond its quota. This
patch adds a default quota of 1000. This quota could be tuned by
administrator. Making PASID quota tunable will be added in another patch
in this series.

Previous discussions:
https://patchwork.kernel.org/patch/11209429/

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
Signed-off-by: Yi Sun <yi.y.sun@linux.intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Reported-by: kbuild test robot <lkp@intel.com>
---
 drivers/vfio/vfio.c             | 130 ++++++++++++++++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 104 ++++++++++++++++++++++++++++++++
 include/linux/vfio.h            |  20 +++++++
 include/uapi/linux/vfio.h       |  41 +++++++++++++
 4 files changed, 295 insertions(+)

```
#### [PATCH v1 1/2] vfio/pci: Expose PCIe PASID capability to guest
##### From: "Liu, Yi L" <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11451681
Return-Path: <SRS0=VAWz=5H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E50EB913
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:27:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD94B20769
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 22 Mar 2020 12:27:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727285AbgCVM1d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 22 Mar 2020 08:27:33 -0400
Received: from mga14.intel.com ([192.55.52.115]:23953 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727043AbgCVM1d (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 22 Mar 2020 08:27:33 -0400
IronPort-SDR: 
 RZk2mM5o64gNf2wmRLEQMDAl4zHstOavOESo07JjzkUT950FtTlt9sT+jWun8gSQlXw5UPeNt6
 n47y3M7Q+l3Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Mar 2020 05:27:32 -0700
IronPort-SDR: 
 JTj7uc0RiWhatZgQOskzWH3SQgaANaBTrPWHGcjeB0aAHqUXXZDrkkbmGHYOeY5sGRaaqQUQso
 t0QFsS+FgF1g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,292,1580803200";
   d="scan'208";a="356846585"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by fmsmga001.fm.intel.com with ESMTP; 22 Mar 2020 05:27:32 -0700
From: "Liu, Yi L" <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        joro@8bytes.org, ashok.raj@intel.com, yi.l.liu@intel.com,
        jun.j.tian@intel.com, yi.y.sun@intel.com, jean-philippe@linaro.org,
        peterx@redhat.com, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org, hao.wu@intel.com
Subject: [PATCH v1 1/2] vfio/pci: Expose PCIe PASID capability to guest
Date: Sun, 22 Mar 2020 05:33:13 -0700
Message-Id: <1584880394-11184-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1584880394-11184-1-git-send-email-yi.l.liu@intel.com>
References: <1584880394-11184-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Liu Yi L <yi.l.liu@intel.com>

This patch exposes PCIe PASID capability to guest. Existing vfio_pci
driver hides it from guest by setting the capability length as 0 in
pci_ext_cap_length[].

This capability is required for vSVA enabling on pass-through PCIe
devices.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/pci/vfio_pci_config.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
