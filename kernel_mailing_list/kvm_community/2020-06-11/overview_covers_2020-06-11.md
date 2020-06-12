

#### [PATCH RFC v8 00/11] vhost: ring format independence
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From patchwork Thu Jun 11 11:34:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11599769
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B46190
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 11:36:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 02D1C2072F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 11:36:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="etcfzlhY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728047AbgFKLe2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 07:34:28 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:36513 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727109AbgFKLeY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Jun 2020 07:34:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591875262;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=kvOkZNSYFeD+43Sy08lFqOoYp/OFi1aiv2h8v9KKAP4=;
        b=etcfzlhYUXUr2JMq/IBg38soc5HuV1HAeiqo2x94a/Tg0ypUhREMWcJZdIx5hJc3yK4ttw
        zf4GYyEsVma63FwKNYE00D9YpK3ZcKAY2kuRC5ZkyiMi5geamOQ1IuxBdO1Pao0qcFnEe1
        JwR+D0hQQCF8P67Mkjkq4oM+QNp4p/s=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-402-vAAHg8CLPie5P1gv1FhvHg-1; Thu, 11 Jun 2020 07:34:17 -0400
X-MC-Unique: vAAHg8CLPie5P1gv1FhvHg-1
Received: by mail-wm1-f70.google.com with SMTP id g84so1234584wmf.4
        for <kvm@vger.kernel.org>; Thu, 11 Jun 2020 04:34:17 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=kvOkZNSYFeD+43Sy08lFqOoYp/OFi1aiv2h8v9KKAP4=;
        b=bq6wfh3NBm7ZG55okWKCTjarWXEHWM0Qk3AaeVa5N2mzq1g8BU/uVpuHgKBkU6H+mu
         wFxyjlGZ5f2QUd0y1wDaKbx+XTuJRLrxLnS2pDN7lFNlDC6DidvSKOGOwWFjUUo4CeK7
         KFHPXYplLsBz8dUXoSGnMEQbBEhGZznr4V7GKzWXBhbqz7bckA3OVrfdHrlXdS7OjtcT
         WhHJ1LufZLMtKSbDTN8bnegtGvYTs9FTMMaSUVm+nWwO1thKbXD2eKNO4P3JXttWyBWV
         gBs/AaCNJDF+cpR+Jmfcg/1NdMijUzqUKJhFy66G/3wAt9vkecugkI10FjyrjHuJkITK
         lQUQ==
X-Gm-Message-State: AOAM533Q3TqQ1/KzKM7xm7UhCO21ab0Z/FubOBCwpH//8WUSQfvuMxtN
        euCm7lsP9GYk9ZiZN3UN0PJuRupxaCXp28EgVBQnFhjAZ9yLT08A4jnZ0oQ7FQSpY2/lFSXHnQJ
        xGzzUUNlxaLZI
X-Received: by 2002:adf:afc7:: with SMTP id y7mr9022430wrd.173.1591875256651;
        Thu, 11 Jun 2020 04:34:16 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJzMVwGtIAyLyKuJe/rvxpW01IwwfuztK2wzsTcAeYYTwafjhy8A/SBGUsb9zgk1wtRdA+tFzQ==
X-Received: by 2002:adf:afc7:: with SMTP id y7mr9022405wrd.173.1591875256447;
        Thu, 11 Jun 2020 04:34:16 -0700 (PDT)
Received: from redhat.com (bzq-79-181-55-232.red.bezeqint.net.
 [79.181.55.232])
        by smtp.gmail.com with ESMTPSA id
 k12sm4673844wrn.42.2020.06.11.04.34.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 11 Jun 2020 04:34:15 -0700 (PDT)
Date: Thu, 11 Jun 2020 07:34:14 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v8 00/11] vhost: ring format independence
Message-ID: <20200611113404.17810-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This still causes corruption issues for people so don't try
to use in production please. Posting to expedite debugging.

This adds infrastructure required for supporting
multiple ring formats.

The idea is as follows: we convert descriptors to an
independent format first, and process that converting to
iov later.

Used ring is similar: we fetch into an independent struct first,
convert that to IOV later.

The point is that we have a tight loop that fetches
descriptors, which is good for cache utilization.
This will also allow all kind of batching tricks -
e.g. it seems possible to keep SMAP disabled while
we are fetching multiple descriptors.

For used descriptors, this allows keeping track of the buffer length
without need to rescan IOV.

This seems to perform exactly the same as the original
code based on a microbenchmark.
Lightly tested.
More testing would be very much appreciated.

changes from v8:
	- squashed in fixes. no longer hangs but still known
	  to cause data corruption for some people. under debug.

changes from v6:
	- fixes some bugs introduced in v6 and v5

changes from v5:
	- addressed comments by Jason: squashed API changes, fixed up discard

changes from v4:
	- added used descriptor format independence
	- addressed comments by jason
	- fixed a crash detected by the lkp robot.

changes from v3:
        - fixed error handling in case of indirect descriptors
        - add BUG_ON to detect buffer overflow in case of bugs
                in response to comment by Jason Wang
        - minor code tweaks

Changes from v2:
	- fixed indirect descriptor batching
                reported by Jason Wang

Changes from v1:
	- typo fixes


Michael S. Tsirkin (14):
  vhost: option to fetch descriptors through an independent struct
  fixup! vhost: option to fetch descriptors through an independent
    struct


Michael S. Tsirkin (11):
  vhost: option to fetch descriptors through an independent struct
  vhost: use batched get_vq_desc version
  vhost/net: pass net specific struct pointer
  vhost: reorder functions
  vhost: format-independent API for used buffers
  vhost/net: convert to new API: heads->bufs
  vhost/net: avoid iov length math
  vhost/test: convert to the buf API
  vhost/scsi: switch to buf APIs
  vhost/vsock: switch to the buf API
  vhost: drop head based APIs

 drivers/vhost/net.c   | 174 +++++++++----------
 drivers/vhost/scsi.c  |  73 ++++----
 drivers/vhost/test.c  |  22 +--
 drivers/vhost/vhost.c | 378 +++++++++++++++++++++++++++---------------
 drivers/vhost/vhost.h |  44 +++--
 drivers/vhost/vsock.c |  30 ++--
 6 files changed, 439 insertions(+), 282 deletions(-)
```
#### [PATCH v2 00/15] vfio: expose virtual Shared Virtual Addressing to
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Thu Jun 11 12:15:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11599903
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 553F614B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:10:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3E79C2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:10:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728006AbgFKMJK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 08:09:10 -0400
Received: from mga17.intel.com ([192.55.52.151]:41824 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727849AbgFKMJK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 08:09:10 -0400
IronPort-SDR: 
 Qzh73Zpvtv4Q+8OeusGrmhzSWPyzLaF8qoEk+crYkCIic8dYaup/zGynwFoibennyF5QTcifRo
 AIiQDSj/nzIA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Jun 2020 05:09:09 -0700
IronPort-SDR: 
 slupFsEoGCu3+aZxDJFA/0zL5b17ZqrOsg0F2camZjWpwi38u1nWMEY+JyM7+b0EFAF+80FeiR
 uSzRmt7F1iIw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,499,1583222400";
   d="scan'208";a="419082464"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga004.jf.intel.com with ESMTP; 11 Jun 2020 05:09:09 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 00/15] vfio: expose virtual Shared Virtual Addressing to
 VMs
Date: Thu, 11 Jun 2020 05:15:19 -0700
Message-Id: <1591877734-66527-1-git-send-email-yi.l.liu@intel.com>
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

Patch Overview:
 1. a refactor to vfio_iommu_type1 ioctl (patch 0001)
 2. reports IOMMU nesting info to userspace ( patch 0002, 0003 and 0015)
 3. vfio support for PASID allocation and free for VMs (patch 0004, 0005, 0006)
 4. vfio support for binding guest page table to host (patch 0007, 0008, 0009, 0010)
 5. vfio support for IOMMU cache invalidation from VMs (patch 0011)
 6. vfio support for vSVA usage on IOMMU-backed mdevs (patch 0012)
 7. expose PASID capability to VM (patch 0013)
 8. add doc for VFIO dual stage control (patch 0014)

The complete vSVA kernel upstream patches are divided into three phases:
    1. Common APIs and PCI device direct assignment
    2. IOMMU-backed Mediated Device assignment
    3. Page Request Services (PRS) support

This patchset is aiming for the phase 1 and phase 2, and based on Jacob's
below series.
[PATCH v13 0/8] Nested Shared Virtual Address (SVA) VT-d support - merged
https://lkml.org/lkml/2020/5/13/1582

[PATCH v2 0/3] IOMMU user API enhancement - wip
https://lkml.org/lkml/2020/6/11/5

[PATCH 00/10] IOASID extensions for guest SVA - wip
https://lkml.org/lkml/2020/3/25/874

The latest IOASID code added below new interface for itertate all PASIDs of an
ioasid_set. The implementation is not sent out yet as Jacob needs some cleanup,
it can be found in branch vsva-linux-5.7-rc4-v2.
 int ioasid_set_for_each_ioasid(int sid, void (*fn)(ioasid_t id, void *data), void *data);

Complete set for current vSVA can be found in below branch.
This branch also includes some extra modifications to IOASID core code and
vt-d iommu driver cleanup patches.
https://github.com/luxis1999/linux-vsva.git:vsva-linux-5.7-rc4-v2

The corresponding QEMU patch series is included in below branch:
https://github.com/luxis1999/qemu.git:vsva_5.7_rc4_qemu_rfcv6


Regards,
Yi Liu

Changelog:
	- Patch v1 -> Patch v2:
	  a) Refactor vfio_iommu_type1_ioctl() per suggestion from Christoph
	     Hellwig.
	  b) Re-sequence the patch series for better bisect support.
	  c) Report IOMMU nesting cap info in detail instead of a format in
	     v1.
	  d) Enforce one group per nesting type container for vfio iommu type1
	     driver.
	  e) Build the vfio_mm related code from vfio.c to be a separate
	     vfio_pasid.ko.
	  f) Add PASID ownership check in IOMMU driver.
	  g) Adopted to latest IOMMU UAPI design. Removed IOMMU UAPI version
	     check. Added iommu_gpasid_unbind_data for unbind requests from
	     userspace.
	  h) Define a single ioctl:VFIO_IOMMU_NESTING_OP for bind/unbind_gtbl
	     and cahce_invld.
	  i) Document dual stage control in vfio.rst.
	  Patch v1: https://lore.kernel.org/linux-iommu/1584880325-10561-1-git-send-email-yi.l.liu@intel.com/

	- RFC v3 -> Patch v1:
	  a) Address comments to the PASID request(alloc/free) path
	  b) Report PASID alloc/free availabitiy to user-space
	  c) Add a vfio_iommu_type1 parameter to support pasid quota tuning
	  d) Adjusted to latest ioasid code implementation. e.g. remove the
	     code for tracking the allocated PASIDs as latest ioasid code
	     will track it, VFIO could use ioasid_free_set() to free all
	     PASIDs.
	  RFC v3: https://lore.kernel.org/linux-iommu/1580299912-86084-1-git-send-email-yi.l.liu@intel.com/

	- RFC v2 -> v3:
	  a) Refine the whole patchset to fit the roughly parts in this series
	  b) Adds complete vfio PASID management framework. e.g. pasid alloc,
	  free, reclaim in VM crash/down and per-VM PASID quota to prevent
	  PASID abuse.
	  c) Adds IOMMU uAPI version check and page table format check to ensure
	  version compatibility and hardware compatibility.
	  d) Adds vSVA vfio support for IOMMU-backed mdevs.
	  RFC v2: https://lore.kernel.org/linux-iommu/1571919983-3231-1-git-send-email-yi.l.liu@intel.com/

	- RFC v1 -> v2:
	  Dropped vfio: VFIO_IOMMU_ATTACH/DETACH_PASID_TABLE.
	  RFC v1: https://lore.kernel.org/linux-iommu/1562324772-3084-1-git-send-email-yi.l.liu@intel.com/


Eric Auger (1):
  vfio: Document dual stage control

Liu Yi L (13):
  vfio/type1: Refactor vfio_iommu_type1_ioctl()
  iommu: Report domain nesting info
  vfio/type1: Report iommu nesting info to userspace
  vfio: Add PASID allocation/free support
  iommu/vt-d: Support setting ioasid set to domain
  vfio/type1: Add VFIO_IOMMU_PASID_REQUEST (alloc/free)
  iommu/uapi: Add iommu_gpasid_unbind_data
  iommu/vt-d: Check ownership for PASIDs from user-space
  vfio/type1: Support binding guest page tables to PASID
  vfio/type1: Allow invalidating first-level/stage IOMMU cache
  vfio/type1: Add vSVA support for IOMMU-backed mdevs
  vfio/pci: Expose PCIe PASID capability to guest
  iommu/vt-d: Support reporting nesting capability info

Yi Sun (1):
  iommu: Pass domain and unbind_data to sva_unbind_gpasid()

 Documentation/driver-api/vfio.rst  |  64 ++++
 drivers/iommu/intel-iommu.c        | 107 ++++++-
 drivers/iommu/intel-svm.c          |  20 +-
 drivers/iommu/iommu.c              |   4 +-
 drivers/vfio/Kconfig               |   6 +
 drivers/vfio/Makefile              |   1 +
 drivers/vfio/pci/vfio_pci_config.c |   2 +-
 drivers/vfio/vfio_iommu_type1.c    | 614 ++++++++++++++++++++++++++++++++-----
 drivers/vfio/vfio_pasid.c          | 191 ++++++++++++
 include/linux/intel-iommu.h        |  23 +-
 include/linux/iommu.h              |  10 +-
 include/linux/vfio.h               |  54 ++++
 include/uapi/linux/iommu.h         |  47 +++
 include/uapi/linux/vfio.h          |  78 +++++
 14 files changed, 1134 insertions(+), 87 deletions(-)
 create mode 100644 drivers/vfio/vfio_pasid.c
```
#### [RFC v6 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
From patchwork Thu Jun 11 12:53:59 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11600003
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 89E5B618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:48:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7630E2078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:48:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726497AbgFKMsA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 08:48:00 -0400
Received: from mga18.intel.com ([134.134.136.126]:58110 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726095AbgFKMsA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 08:48:00 -0400
IronPort-SDR: 
 1W37q/1oDtWAoMHTlut0VzSTxSLxoBQuGUm87UHifPSFVfwwLDVEYjLC4m+cpPV1e4MLVbl+mj
 Ux2f6cqjBLXg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Jun 2020 05:47:59 -0700
IronPort-SDR: 
 ZR9eWu/92aYlQzrFf3INu69Eg3X3k2Trvn/gtugYqPrWneYkJKycA6ACHVNuD9sMZQIGmism/9
 hM3NebKbuhJA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,499,1583222400";
   d="scan'208";a="447911214"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga005.jf.intel.com with ESMTP; 11 Jun 2020 05:47:59 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org
Subject: [RFC v6 00/25] intel_iommu: expose Shared Virtual Addressing to VMs
Date: Thu, 11 Jun 2020 05:53:59 -0700
Message-Id: <1591880064-30638-1-git-send-email-yi.l.liu@intel.com>
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
changes.

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

This QEMU patchset is aiming for the phase 1 and phase 2. It is based
on the kernel series below:
[PATCH v2 00/15] vfio: expose virtual Shared Virtual Addressing to VMs
https://lore.kernel.org/linux-iommu/1591877734-66527-1-git-send-email-yi.l.liu@intel.com/

Patch Overview:
 1. patch 0001 - 0002: update kernel header files
 2. patch 0003 - 0007: select VFIO_TYPE1_NESTING_IOMMU for vIOMMU built
                       on IOMMU nesting translation.
 3. patch 0008 - 0010: set HostIOMMUContext to vIOMMU.
 4. patch 0011 - 0013: allocate PASID for vIOMMU.
 5. patch 0014 - 0015: PASID cache management for Intel vIOMMU.
 6. patch 0016 - 0020: bind guest page table to host.
 7. patch 0021 - 0024: flush first level/stage cache for vIOMMU.
 8. patch 0025: expose SVA to VM by x-scalable-mode="modern"

The complete QEMU set can be found in below link:
https://github.com/luxis1999/qemu.git:vsva_5.7_rc4_qemu_rfcv6

Complete kernel can be found in:
https://github.com/luxis1999/linux-vsva.git:vsva-linux-5.7-rc4-v2

Tests: basci vSVA functionality test, VM reboot/shutdown/crash, kernel build in
guest, boot VM with vSVA disabled, full comapilation with all archs, passthru
entire PCI device, passthru Scalable IOV ADI.

Regards,
Yi Liu

Changelog:
	- RFC v5 -> RFC v6:
	  a) Use RFC instead of formal patch as kernel patch is in progress.
	  b) Address comments from Peter and Eric.
	  c) Add get_iommu_attr() to advertise vIOMMU nesting requirement to
	     VFIO.
	  d) Update per latest kernel UAPI definition.
	  e) Add patch 0017 to check iommu nesting cap info in set_iommu().
	  RFC v5: https://www.spinics.net/lists/kvm/msg211475.html

	- RFC v4 -> RFC v5:
	  a) Refactor the vfio HostIOMMUContext init code (patch 0008 - 0009 of v1 series)
	  b) Refactor the pasid binding handling (patch 0011 - 0016 of v1 series)
	  RFC v4: https://patchwork.ozlabs.org/cover/1259648/

	- RFC v3.1 -> RFC v4:
	  a) Implement HostIOMMUContext in QOM manner.
	  b) Add pci_set/unset_iommu_context() to register HostIOMMUContext to
	     vIOMMU, thus the lifecircle of HostIOMMUContext is awared in vIOMMU
	     side. In such way, vIOMMU could use the methods provided by the
	     HostIOMMUContext safely.
	  c) Add back patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3.1: https://patchwork.kernel.org/cover/11397879/

	- RFC v3 -> v3.1:
	  a) Drop IOMMUContext, and rename DualStageIOMMUObject to HostIOMMUContext.
	     HostIOMMUContext is per-vfio-container, it is exposed to  vIOMMU via PCI
	     layer. VFIO registers a PCIHostIOMMUFunc callback to PCI layer, vIOMMU
	     could get HostIOMMUContext instance via it.
	  b) Check IOMMU uAPI version by VFIO_CHECK_EXTENSION
	  c) Add a check on VFIO_PASID_REQ availability via VFIO_GET_IOMMU_IHNFO
	  d) Reorder the series, put vSVA linux header file update in the beginning
	     put the x-scalable-mode option mofification in the end of the series.
	  e) Dropped patch "[RFC v3 01/25] hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps"
	  RFCv3: https://patchwork.kernel.org/cover/11356033/

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


*** BLURB HERE ***

Eric Auger (1):
  scripts/update-linux-headers: Import iommu.h

Liu Yi L (24):
  header file update VFIO/IOMMU vSVA APIs kernel 5.7-rc4
  hw/pci: modify pci_setup_iommu() to set PCIIOMMUOps
  hw/pci: introduce pci_device_get_iommu_attr()
  intel_iommu: add get_iommu_attr() callback
  vfio: pass nesting iommu requirement into vfio_get_group()
  vfio: check VFIO_TYPE1_NESTING_IOMMU support
  hw/iommu: introduce HostIOMMUContext
  hw/pci: introduce pci_device_set/unset_iommu_context()
  intel_iommu: add set/unset_iommu_context callback
  vfio/common: provide PASID alloc/free hooks
  vfio: init HostIOMMUContext per-container
  intel_iommu: add virtual command capability support
  intel_iommu: process PASID cache invalidation
  intel_iommu: add PASID cache management infrastructure
  vfio: add bind stage-1 page table support
  intel_iommu: sync IOMMU nesting cap info for assigned devices
  intel_iommu: bind/unbind guest page table to host
  intel_iommu: replay pasid binds after context cache invalidation
  intel_iommu: do not pass down pasid bind for PASID #0
  vfio: add support for flush iommu stage-1 cache
  intel_iommu: process PASID-based iotlb invalidation
  intel_iommu: propagate PASID-based iotlb invalidation to host
  intel_iommu: process PASID-based Device-TLB invalidation
  intel_iommu: modify x-scalable-mode to be string option

 hw/Makefile.objs                      |    1 +
 hw/alpha/typhoon.c                    |    6 +-
 hw/arm/smmu-common.c                  |    6 +-
 hw/hppa/dino.c                        |    6 +-
 hw/i386/amd_iommu.c                   |    6 +-
 hw/i386/intel_iommu.c                 | 1229 ++++++++++++++++++++++++++++++++-
 hw/i386/intel_iommu_internal.h        |  118 ++++
 hw/i386/trace-events                  |    6 +
 hw/iommu/Makefile.objs                |    1 +
 hw/iommu/host_iommu_context.c         |  171 +++++
 hw/pci-host/designware.c              |    6 +-
 hw/pci-host/pnv_phb3.c                |    6 +-
 hw/pci-host/pnv_phb4.c                |    6 +-
 hw/pci-host/ppce500.c                 |    6 +-
 hw/pci-host/prep.c                    |    6 +-
 hw/pci-host/sabre.c                   |    6 +-
 hw/pci/pci.c                          |   73 +-
 hw/ppc/ppc440_pcix.c                  |    6 +-
 hw/ppc/spapr_pci.c                    |    6 +-
 hw/s390x/s390-pci-bus.c               |    8 +-
 hw/vfio/ap.c                          |    2 +-
 hw/vfio/ccw.c                         |    2 +-
 hw/vfio/common.c                      |  297 +++++++-
 hw/vfio/pci.c                         |   26 +-
 hw/vfio/platform.c                    |    2 +-
 hw/virtio/virtio-iommu.c              |    6 +-
 include/hw/i386/intel_iommu.h         |   61 +-
 include/hw/iommu/host_iommu_context.h |  103 +++
 include/hw/pci/pci.h                  |   25 +-
 include/hw/pci/pci_bus.h              |    2 +-
 include/hw/vfio/vfio-common.h         |    7 +-
 linux-headers/linux/iommu.h           |  382 ++++++++++
 linux-headers/linux/vfio.h            |   78 +++
 scripts/update-linux-headers.sh       |    2 +-
 34 files changed, 2614 insertions(+), 60 deletions(-)
 create mode 100644 hw/iommu/Makefile.objs
 create mode 100644 hw/iommu/host_iommu_context.c
 create mode 100644 include/hw/iommu/host_iommu_context.h
 create mode 100644 linux-headers/linux/iommu.h
```
#### [PATCH 0/3] INVPCID support for the AMD guests
##### From: Babu Moger <babu.moger@amd.com>

```c
From patchwork Thu Jun 11 21:48:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11600917
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68629618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 21:48:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4BD5A20853
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 21:48:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="e1CLXy0E"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726300AbgFKVsd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 17:48:33 -0400
Received: from mail-co1nam11on2076.outbound.protection.outlook.com
 ([40.107.220.76]:56640
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725869AbgFKVsd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 17:48:33 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=c+YqsmGquX//lh1RwyiCIc/sZE/pRZDCAZlbI274GHu2Rqdmbom/8pz6hGgdEPtUPcxe+uy+YaWRWMr6Wq9XzQV/WggqKLh2sbxwQt5oWevv/6q6JlEkcPyov2EtsRd7ErfYA4YJBw9JE81HrIvalS4IiVW5mWaxVIoOTg7/yIWU7EQbA/p99A1bM4/aEhfOEPgRMOsoibscAQoW6PPHTySxGeNdq3flv/vyuHw5/YvDRFxwaxzMMEHz8V/Sp/Udi81JOHyFqkr+fmVPZi0Lv0vSyyS2vSDn2G63OUesKV1H3ma6AYgPxD/op9j+gMqcsOQI3+qTksueDlCUuFXNBA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ecAbjq9VTF3XrTXFvyqZkDKHIpSFuh8jbFK91mDPgN8=;
 b=mJNDGEDkobyLrwnJslc+rGI+RdeGXgnfSzbKndbXFFqZdeDuRA0DAOeL0Yk1YXO/ThLIpdZvKA/r9OECxh+yWjgITBAOGEhaW2s8c/y9ZTwT34UiYZcOTyGQ3WZURpG+fMPAtQOAK481wAxgvlv5+Qc5TM3B8GPTkrfy1kIpHSP1ebmdCMc7Ue6X0QQvQH63PcIM2XIC7NT6gGs7scnQwXklAUtHv3wCcE6pfF9hfv8Gn0Fedov86xO5/X+ZFVia379kVrBseeN6VxZ87mZ1yBKY99e3zm26XNkWIChp4pQ2PNgPaxFBcI0vaoQVLUZrDaaz1SFs5aWnhE2l7lxwdA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ecAbjq9VTF3XrTXFvyqZkDKHIpSFuh8jbFK91mDPgN8=;
 b=e1CLXy0EKIYbt/fSd7SRPHRD+E4RHgJCCGnlLjYkXlzRmSL54u+S+errOzGABbrAxax5OVMpR9Iozez552MCj80uR9RtdASidrTpE6uxs+h+dGxA3R0Uvr6aErwtkRr2+9CR10ChLA+axv3Suf2avmoQGk4QY/Mtu5Nu68CHIQQ=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4589.namprd12.prod.outlook.com (2603:10b6:806:92::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.18; Thu, 11 Jun
 2020 21:48:30 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2%3]) with mapi id 15.20.3088.021; Thu, 11 Jun 2020
 21:48:30 +0000
Subject: [PATCH 0/3] INVPCID support for the AMD guests
From: Babu Moger <babu.moger@amd.com>
To: wanpengli@tencent.com, joro@8bytes.org, x86@kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, vkuznets@redhat.com,
        tglx@linutronix.de, jmattson@google.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Thu, 11 Jun 2020 16:48:29 -0500
Message-ID: <159191202523.31436.11959784252237488867.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: SN4PR0501CA0155.namprd05.prod.outlook.com
 (2603:10b6:803:2c::33) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 SN4PR0501CA0155.namprd05.prod.outlook.com (2603:10b6:803:2c::33) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3109.10 via Frontend
 Transport; Thu, 11 Jun 2020 21:48:29 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 03a1b932-43d1-4a91-fdb0-08d80e512e2a
X-MS-TrafficTypeDiagnostic: SA0PR12MB4589:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB4589B91CA6B930498E11B24E95800@SA0PR12MB4589.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-Forefront-PRVS: 0431F981D8
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 78s97p+L/nbBx3+grFSKbdN/7nR356rKiVVkxDvxbKoEAJCCK5DjXM8t7pbfFc8kgWHQ9i1kOUs5d7DTpHwcoN5zE8bLsP2p3Fd3Q8j39Z9ElhRxXxJc5Sp32QIHxlN+UKJKQGdMvkT2FqJAvajuB/EQNrPx+m1E1eIzWQQZUdIX29lYg8MWT8x5MW19DW1QKBXRklb6Lzx3GV3HvFulW/s+cu0gaum+7axbB0zrTRJnw9kA8+YQrP7md4LljLTryypm0seoJUMImI8V6zYFqhieBRWUXvZzqJMCEqPbliRYCckeQMJztgyQj2k2Vyf4bvZ9z6fzop55KO+qal3XxhfK+FbDTGpEpxgeAb4TsuProg0pVxVzs89ocbaB9aK67GJrDEbzmODONvTVU7JcqiZ0KxATh60ot140DWgisIw5k8JuTkaYHRR7SB4lY2FbFKa8pbUHHrmu+gHxFiUITw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(7916004)(4636009)(366004)(396003)(39860400002)(346002)(376002)(136003)(52116002)(33716001)(6486002)(16576012)(8936002)(2906002)(8676002)(16526019)(9686003)(7416002)(186003)(4326008)(316002)(478600001)(966005)(103116003)(44832011)(956004)(5660300002)(83380400001)(26005)(66476007)(66556008)(66946007)(86362001)(921003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 CuU87wuiFbNr33VeQaNw0DrVlk+Aka0srMYMaIkTREuuWXiPAh6BuBPWbu2APfHLPOQiaiCVcjAPUBVZYT1AT+00plmZx2hPW17ecDzl8fxQ6lOIpe01fJu30T/JH5gJWYqufEGt8lTY047Nk9vGPnZ97xOAJOmJuPFB3Yufb2KgLkhZv+6SSTKmNQl6yEwcB721x/4ErK9WZEckNGBWV/ixV+A1iSMT9l3UZN6EPawh7aoQE4FK3Fwgbr9XRVDKxYCANPvylwU+c73zNYODWXb3EUAhljjP0n0oe+a3F17jUavTWd/ZU7VuyEMM6aYbVQOCaJ5VIra+Pjv7/7kLBanHcVtWdyOf6sE8DhbG+SDNB1r8J5e1zfum0BlMt/qqkkuy8Nvt9gQOGR7dGWZO3cI0mnUQ7PD5hHKO14NutlC6oCEiojkMbhV6YSPVou88GPpIxmCq8UVJRP5Vr5Q9Gm6Y708vI+IKaqtT39Hyosg=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 03a1b932-43d1-4a91-fdb0-08d80e512e2a
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 11 Jun 2020 21:48:30.3883
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 i8E+UbEyHxwKw6uB3BKb/U909P3YRgemcXmuuaoA/fSdsDz91kunk//LTTkCo/L3
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4589
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following series adds the support for PCID/INVPCID on AMD guests.

For the guests with nested page table (NPT) support, the INVPCID
feature works as running it natively. KVM does not need to do any
special handling in this case.

KVM interceptions are required in the following cases.
1. If the guest tries to disable the feature when the underlying
   hardware supports it. In this case hypervisor needs to report #UD.

2. When the guest is running with shadow page table enabled, in
   this case the hypervisor needs to handle the tlbflush based on the
   type of invpcid instruction type.

AMD documentation for INVPCID feature is available at "AMD64
Architecture Programmer’s Manual Volume 2: System Programming,
Pub. 24593 Rev. 3.34(or later)"

The documentation can be obtained at the links below:
Link: https://www.amd.com/system/files/TechDocs/24593.pdf
Link: https://bugzilla.kernel.org/show_bug.cgi?id=206537
---

babu Moger (3):
      KVM: X86: Move handling of INVPCID types to x86
      KVM:SVM: Add extended intercept support
      KVM:SVM: Enable INVPCID feature on AMD


 arch/x86/include/asm/svm.h      |    7 +++
 arch/x86/include/uapi/asm/svm.h |    2 +
 arch/x86/kvm/svm/nested.c       |    6 ++-
 arch/x86/kvm/svm/svm.c          |   43 +++++++++++++++++++
 arch/x86/kvm/svm/svm.h          |   18 ++++++++
 arch/x86/kvm/trace.h            |   12 ++++-
 arch/x86/kvm/vmx/vmx.c          |   78 ----------------------------------
 arch/x86/kvm/x86.c              |   89 +++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h              |    2 +
 9 files changed, 174 insertions(+), 83 deletions(-)

--
```
