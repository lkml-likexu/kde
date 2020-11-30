

#### [PATCH v12 00/15] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Nov 16 10:43:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11908167
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 84C40C4742C
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:06:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1B7C122263
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:06:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OyvZcUve"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729210AbgKPKnj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 05:43:39 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:26253 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727398AbgKPKni (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 05:43:38 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605523418;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=uXqx5Ho/BGflxGNGIUa2LXehbjyeIn4bhOsfc7gDmnk=;
        b=OyvZcUve3fwiEbUVcrvSQC42ZWYOtzk2gKWGjqVfWTuNy8J0xq1tXvXhu1hz0VrL+AxtHb
        7VEK/NnJV97jORdSadJJtzap5nCKBVCC7lCMuVEXiY2oMQsMFo5SiA7X6aMVP5EXddYuhH
        Y5Gy1spmjj9HjWuiaQUzRBc5wZioXIU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-528-RCDH81_pM9Slp_IaylvHhg-1; Mon, 16 Nov 2020 05:43:32 -0500
X-MC-Unique: RCDH81_pM9Slp_IaylvHhg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 49FF78030D1;
        Mon, 16 Nov 2020 10:43:30 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-230.ams2.redhat.com
 [10.36.113.230])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 267A15C5AF;
        Mon, 16 Nov 2020 10:43:18 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com, alex.williamson@redhat.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com
Subject: [PATCH v12 00/15] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Mon, 16 Nov 2020 11:43:01 +0100
Message-Id: <20201116104316.31816-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

The IOMMU API is extended to support 2 new API functionalities:
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings

Then those capabilities gets implemented in the SMMUv3 driver.

The virtualizer passes information through the VFIO user API
which cascades them to the iommu subsystem. This allows the guest
to own stage 1 tables and context descriptors (so-called PASID
table) while the host owns stage 2 tables and main configuration
structures (STE).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/5.10-rc4-2stage-v12
(including the VFIO part)

The series includes a patch from Jean-Philippe. It is better to
review the original patch:
[PATCH v8 2/9] iommu/arm-smmu-v3: Maintain a SID->device structure

The VFIO series is sent separately.

History:

v11 -> v12:
- rebase on top of v5.10-rc4

Two new patches paving the way for vSVA/ARM (Shameer's input)
- iommu/smmuv3: Accept configs with more than one context descriptor
- iommu/smmuv3: Add PASID cache invalidation per PASID

v10 -> v11:
- S2TTB reset when S2 is off
- fix compil issue when CONFIG_IOMMU_DMA is not set

v9 -> v10:
- rebase on top of 5.6.0-rc3

v8 -> v9:
- rebase on 5.3
- split iommu/vfio parts

v6 -> v8:
- Implement VFIO-PCI device specific interrupt framework

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (15):
  iommu: Introduce attach/detach_pasid_table API
  iommu: Introduce bind/unbind_guest_msi
  iommu/arm-smmu-v3: Maintain a SID->device structure
  iommu/smmuv3: Dynamically allocate s1_cfg and s2_cfg
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: Report non recoverable faults
  iommu/smmuv3: Accept configs with more than one context descriptor
  iommu/smmuv3: Add PASID cache invalidation per PASID

 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 650 ++++++++++++++++++--
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h |  98 ++-
 drivers/iommu/dma-iommu.c                   | 142 ++++-
 drivers/iommu/iommu.c                       | 104 ++++
 include/linux/dma-iommu.h                   |  16 +
 include/linux/iommu.h                       |  41 ++
 include/uapi/linux/iommu.h                  |  54 ++
 7 files changed, 1035 insertions(+), 70 deletions(-)
```
#### [PATCH v11 00/13] SMMUv3 Nested Stage Setup (VFIO part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Mon Nov 16 11:00:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 11908245
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C8259C4742C
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:30:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70E0922263
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:30:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="a8JWZ9c+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729296AbgKPLA4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 06:00:56 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:31713 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729283AbgKPLA4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 06:00:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605524454;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=QzuoH1p35VV4g03kwoyeAFURWii+1W0hJfGTpTcqbBw=;
        b=a8JWZ9c+8Vh3Drl51dRMLpvDr3elpJAcWx+OddYP8Nc0mYgT9XdjbLXzb06/uTVwh3hLt8
        i6XFcaKWG3tE8mjDYxMCJXb7DXGS5sBpgwcMf4pIUQrdQPe+2KcZMI7f5NtTpM95Uvltln
        Yqf6SLdaN6pgq/lMPUmADibXYidRPnA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-211-raXlza9pOOy6h8sdQaSZuA-1; Mon, 16 Nov 2020 06:00:50 -0500
X-MC-Unique: raXlza9pOOy6h8sdQaSZuA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6844C1902EC7;
        Mon, 16 Nov 2020 11:00:47 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-113-230.ams2.redhat.com
 [10.36.113.230])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4B6F35C5AF;
        Mon, 16 Nov 2020 11:00:35 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        joro@8bytes.org, maz@kernel.org, robin.murphy@arm.com,
        alex.williamson@redhat.com
Cc: jean-philippe@linaro.org, zhangfei.gao@linaro.org,
        zhangfei.gao@gmail.com, vivek.gautam@arm.com,
        shameerali.kolothum.thodi@huawei.com,
        jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com, tn@semihalf.com,
        nicoleotsuka@gmail.com, yuzenghui@huawei.com
Subject: [PATCH v11 00/13] SMMUv3 Nested Stage Setup (VFIO part)
Date: Mon, 16 Nov 2020 12:00:17 +0100
Message-Id: <20201116110030.32335-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the VFIO part of HW nested paging support
in the SMMUv3.

This is a rebase on top of v5.10-rc4

The series depends on:
[PATCH v12 00/15] SMMUv3 Nested Stage Setup (IOMMU part)

3 new IOCTLs are introduced that allow the userspace to
1) pass the guest stage 1 configuration
2) pass stage 1 MSI bindings
3) invalidate stage 1 related caches

They map onto the related new IOMMU API functions.

We introduce the capability to register specific interrupt
indexes (see [1]). A new DMA_FAULT interrupt index allows to register
an eventfd to be signaled whenever a stage 1 related fault
is detected at physical level. Also two specific regions allow to
- expose the fault records to the user space and
- inject page responses.

This latter functionality is not exercised in this series
but is provided as a POC for further vSVA activities (Shameer's input).

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/5.10-rc4-2stage-v12

The series series includes Tina's patch steming from
[1] "[RFC PATCH v2 1/3] vfio: Use capability chains to handle device
specific irq" plus patches originally contributed by Yi.

History:

v10 -> v11:
- rebase on top of v5.10-rc4
- adapt to changes on the IOMMU API (compliant with the doc
  written by Jacob/Yi)
- addition of the page response region
- Took into account Zenghui's comments
- In this version I have kept the ioctl separate. Since
  Yi's series [2] is currently stalled, I've just rebased here.

[2] [PATCH v7 00/16] vfio: expose virtual Shared Virtual Addressing
to VMs

v9 -> v10
- rebase on top of 5.6.0-rc3 (no change versus v9)

v8 -> v9:
- introduce specific irq framework
- single fault region
- iommu_unregister_device_fault_handler failure case not handled
  yet.

v7 -> v8:
- rebase on top of v5.2-rc1 and especially
  8be39a1a04c1  iommu/arm-smmu-v3: Add a master->domain pointer
- dynamic alloc of s1_cfg/s2_cfg
- __arm_smmu_tlb_inv_asid/s1_range_nosync
- check there is no HW MSI regions
- asid invalidation using pasid extended struct (change in the uapi)
- add s1_live/s2_live checks
- move check about support of nested stages in domain finalise
- fixes in error reporting according to the discussion with Robin
- reordered the patches to have first iommu/smmuv3 patches and then
  VFIO patches

v6 -> v7:
- removed device handle from bind/unbind_guest_msi
- added "iommu/smmuv3: Nested mode single MSI doorbell per domain
  enforcement"
- added few uapi comments as suggested by Jean, Jacop and Alex

v5 -> v6:
- Fix compilation issue when CONFIG_IOMMU_API is unset

v4 -> v5:
- fix bug reported by Vincent: fault handler unregistration now happens in
  vfio_pci_release
- IOMMU_FAULT_PERM_* moved outside of struct definition + small
  uapi changes suggested by Kean-Philippe (except fetch_addr)
- iommu: introduce device fault report API: removed the PRI part.
- see individual logs for more details
- reset the ste abort flag on detach

v3 -> v4:
- took into account Alex, jean-Philippe and Robin's comments on v3
- rework of the smmuv3 driver integration
- add tear down ops for msi binding and PASID table binding
- fix S1 fault propagation
- put fault reporting patches at the beginning of the series following
  Jean-Philippe's request
- update of the cache invalidate and fault API uapis
- VFIO fault reporting rework with 2 separate regions and one mmappable
  segment for the fault queue
- moved to PATCH

v2 -> v3:
- When registering the S1 MSI binding we now store the device handle. This
  addresses Robin's comment about discimination of devices beonging to
  different S1 groups and using different physical MSI doorbells.
- Change the fault reporting API: use VFIO_PCI_DMA_FAULT_IRQ_INDEX to
  set the eventfd and expose the faults through an mmappable fault region

v1 -> v2:
- Added the fault reporting capability
- asid properly passed on invalidation (fix assignment of multiple
  devices)
- see individual change logs for more info


Eric Auger (10):
  vfio: VFIO_IOMMU_SET_MSI_BINDING
  vfio/pci: Add VFIO_REGION_TYPE_NESTED region type
  vfio/pci: Register an iommu fault handler
  vfio/pci: Allow to mmap the fault queue
  vfio/pci: Add framework for custom interrupt indices
  vfio: Add new IRQ for DMA fault reporting
  vfio/pci: Register and allow DMA FAULT IRQ signaling
  vfio: Document nested stage control
  vfio/pci: Register a DMA fault response region
  vfio/pci: Inject page response upon response region fill

Liu, Yi L (2):
  vfio: VFIO_IOMMU_SET_PASID_TABLE
  vfio: VFIO_IOMMU_CACHE_INVALIDATE

Tina Zhang (1):
  vfio: Use capability chains to handle device specific irq

 Documentation/driver-api/vfio.rst   |  77 +++++
 drivers/vfio/pci/vfio_pci.c         | 430 ++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_intrs.c   |  62 ++++
 drivers/vfio/pci/vfio_pci_private.h |  33 +++
 drivers/vfio/pci/vfio_pci_rdwr.c    |  84 ++++++
 drivers/vfio/vfio_iommu_type1.c     | 186 ++++++++++++
 include/uapi/linux/vfio.h           | 140 ++++++++-
 7 files changed, 993 insertions(+), 19 deletions(-)
```
#### [PATCH v3 0/4] KVM: selftests: Cleanups, take 2
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Mon Nov 16 12:19:38 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11908359
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=no
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 731F4C84510
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F70522265
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 12:38:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QV+8ez2K"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730027AbgKPMTx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 07:19:53 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:44388 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727027AbgKPMTx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 16 Nov 2020 07:19:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605529192;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=7mt6aGqCxvZDfH2yiikjg7G5wIctdLOxkaOhYTJfOw0=;
        b=QV+8ez2Kf+B0dfXmCiYF77X5us5vtctJDu0lWB/dxQQd2esozgO7FO+UE+IZQ9K8m3OFaF
        TUgpEB/HhIThRgLxr4IOeU+xBfpkuzciMM17IuKD644tr5A/9SU+gvLMecWf3q3hCGP5a+
        B7DKp5jJFl0Ek6XHljR5XlFCvYveiaM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-587-hCSP_0dMM4axlbHXv0GL9Q-1; Mon, 16 Nov 2020 07:19:50 -0500
X-MC-Unique: hCSP_0dMM4axlbHXv0GL9Q-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B7ACF1008550;
        Mon, 16 Nov 2020 12:19:48 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.122])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2071E60BF1;
        Mon, 16 Nov 2020 12:19:43 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v3 0/4] KVM: selftests: Cleanups, take 2
Date: Mon, 16 Nov 2020 13:19:38 +0100
Message-Id: <20201116121942.55031-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up demand_paging_test, dirty_log_perf_test,
and dirty_log_test by factoring out common code, creating some new API
along the way. It also splits include/perf_test_util.h into a more
conventional header and source pair.

I've tested on x86 and AArch64 (one config each), but not s390x.

v3:
 - Rebased remaining four patches from v2 onto kvm/queue
 - Picked up r-b's from Peter and Ben

v2: https://www.spinics.net/lists/kvm/msg228711.html   

Thanks,
drew


Andrew Jones (4):
  KVM: selftests: Factor out guest mode code
  KVM: selftests: dirty_log_test: Remove create_vm
  KVM: selftests: Use vm_create_with_vcpus in create_vm
  KVM: selftests: Implement perf_test_util more conventionally

 tools/testing/selftests/kvm/Makefile          |   2 +-
 .../selftests/kvm/demand_paging_test.c        | 118 ++++--------
 .../selftests/kvm/dirty_log_perf_test.c       | 145 +++++---------
 tools/testing/selftests/kvm/dirty_log_test.c  | 179 +++++-------------
 .../selftests/kvm/include/guest_modes.h       |  21 ++
 .../testing/selftests/kvm/include/kvm_util.h  |   9 +
 .../selftests/kvm/include/perf_test_util.h    | 167 ++--------------
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 +++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |   9 +-
 .../selftests/kvm/lib/perf_test_util.c        | 134 +++++++++++++
 10 files changed, 378 insertions(+), 476 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c
 create mode 100644 tools/testing/selftests/kvm/lib/perf_test_util.c
```
#### [RFC PATCH 00/67] KVM: X86: TDX support
##### From: isaku.yamahata@intel.com
From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
From patchwork Mon Nov 16 18:25:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: isaku.yamahata@intel.com
X-Patchwork-Id: 11910461
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 25DDDC64E7D
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:34:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B821520A8B
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:34:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732510AbgKPS1y (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 13:27:54 -0500
Received: from mga06.intel.com ([134.134.136.31]:20621 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731805AbgKPS1x (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 13:27:53 -0500
IronPort-SDR: 
 QGSRKg69Dw2Jo99HBCvwKnkDx4zM/Fvu7Yj/nFKJmistVAcjdqNpV2sWNMQgiXmWgEqpvnOhl2
 5wUJ6PCZPA3A==
X-IronPort-AV: E=McAfee;i="6000,8403,9807"; a="232409988"
X-IronPort-AV: E=Sophos;i="5.77,483,1596524400";
   d="scan'208";a="232409988"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Nov 2020 10:27:52 -0800
IronPort-SDR: 
 wAOEqpP8Eq0Nw8gPyBrYrJgv8XAhxL1db3YYwAvgTvp0Nyma+xuhgHhczhs1GlrjD9xPH1uiLZ
 beojlMYybeTQ==
X-IronPort-AV: E=Sophos;i="5.77,483,1596524400";
   d="scan'208";a="400527722"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 16 Nov 2020 10:27:51 -0800
From: isaku.yamahata@intel.com
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, x86@kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: isaku.yamahata@intel.com, isaku.yamahata@gmail.com
Subject: [RFC PATCH 00/67] KVM: X86: TDX support
Date: Mon, 16 Nov 2020 10:25:45 -0800
Message-Id: <cover.1605232743.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Isaku Yamahata <isaku.yamahata@intel.com>

* What's TDX?
TDX stands for Trust Domain Extensions which isolates VMs from
the virtual-machine manager (VMM)/hypervisor and any other software on
the platform. [1]
For details, the specifications, [2], [3], [4], [5], [6], [7], are
available.


* The goal of this RFC patch
The purpose of this post is to get feedback early on high level design
issue of KVM enhancement for TDX. The detailed coding (variable naming
etc) is not cared of. This patch series is incomplete (not working).
Although multiple software components, not only KVM but also QEMU,
guest Linux and virtual bios, need to be updated, this includes only
KVM VMM part. For those who are curious to changes to other
component, there are public repositories at github. [8], [9]


* Terminology
Here are short explanations of key concepts.
For detailed explanation or other terminologies, please refer to the
specifications. [2], [3], [4], [5], [6], [7].
- Trusted Domain(TD)
  Hardware-isolated virtual machines managed by TDX-module.
- Secure-Arbitration Mode(SEAM)
  A new mode of the CPU. It consists of SEAM Root and SEAM Non-Root
  which corresponds to VMX Root and VMX Non-Root.
- TDX-module
  TDX-module runs in SEAM Root that manages TD guest state.
  It provides ABI for VMM to manages TDs. It's expensive operation.
- SEAM loader(SEAMLDR)
  Authenticated Code Module(ACM) to load the TDX-module.
- Secure EPT (S-EPT)
  An extended Page table that is encrypted.
  Shared bit(bit 51 or 47) in GPA selects shared vs private.
  0: private to TD, 1: shared with host VMM.


* Major touch/discussion points
The followings are the major touch points where feedback is wanted.

** the file location of the boot code
BSP launches SEAM Loader on BSP to load TDX module. TDX module is on
all CPUs. The directory, arch/x86/kvm/boot/seam, is chosen to locate
the related files in near directory. When maintenance/enhancement in
future, it will be easy to identify that they're related to be synced
with.

- arch/x86/kvm/boot/seam: the current choice
  Pros:
  - The directory clearly indicates that the code is related to only
    KVM.
  - Keep files near to the related code (KVM TDX code).
  Cons:
  - It doesn't follow the existing convention.

Alternative:
The alternative is to follow the existing convention.
- arch/x86/kernel/cpu/
  Pros:
  - It follows the existing convention.
  Cons:
  - It's unclear that it's related to only KVM TDX.

- drivers/firmware/
  As TDX module can be considered a firmware, yet other choice is
  Pros:
  - It follows the existing convention. it clarifies that TDX module
    is a firmware.
  Cons:
  - It's hard to understand the firmware is only for KVM TDX.
  - The files are far from the related code(KVM TDX).

** Coexistence of normal(VMX) VM and TD VM
It's required to allow both legacy(normal VMX) VMs and new TD VMs to
coexist. Otherwise the benefits of VM flexibility would be eliminated.
The main issue for it is that the logic of kvm_x86_ops callbacks for
TDX is different from VMX. On the other hand, the variable,
kvm_x86_ops, is global single variable. Not per-VM, not per-vcpu.

Several points to be considered.
  . No or minimal overhead when TDX is disabled(CONFIG_KVM_INTEL_TDX=n).
  . Avoid overhead of indirect call via function pointers.
  . Contain the changes under arch/x86/kvm/vmx directory and share logic
    with VMX for maintenance.
    Even though the ways to operation on VM (VMX instruction vs TDX
    SEAM call) is different, the basic idea remains same. So, many
    logic can be shared.
  . Future maintenance
    The huge change of kvm_x86_ops in (near) future isn't expected.
    a centralized file is acceptable.

- Wrapping kvm x86_ops: The current choice
  Introduce dedicated file for arch/x86/kvm/vmx/main.c (the name,
  main.c, is just chosen to show main entry points for callbacks.) and
  wrapper functions around all the callbacks with
  "if (is-tdx) tdx-callback() else vmx-callback()".

  Pros:
  - No major change in common x86 KVM code. The change is (mostly)
    contained under arch/x86/kvm/vmx/.
  - When TDX is disabled(CONFIG_KVM_INTEL_TDX=n), the overhead is
    optimized out.
  - Micro optimization by avoiding function pointer.
  Cons:
  - Many boiler plates in arch/x86/kvm/vmx/main.c.

Alternative:
- Introduce another callback layer under arch/x86/kvm/vmx.
  Pros:
  - No major change in common x86 KVM code. The change is (mostly)
    contained under arch/x86/kvm/vmx/.
  - clear separation on callbacks.
  Cons:
  - overhead in VMX even when TDX is disabled(CONFIG_KVM_INTEL_TDX=n).

- Allow per-VM kvm_x86_ops callbacks instead of global kvm_x86_ops
  Pros:
  - clear separation on callbacks.
  Cons:
  - Big change in common x86 code.
  - overhead in common code even when TDX is
    disabled(CONFIG_KVM_INTEL_TDX=n).

- Introduce new directory arch/x86/kvm/tdx
  Pros:
  - It clarifies that TDX is different from VMX.
  Cons:
  - Given the level of code sharing, it complicates code sharing.

** KVM MMU Changes
KVM MMU needs to be enhanced to handle Secure/Shared-EPT. The
high-level execution flow is mostly same to normal EPT case.
EPT violation/misconfiguration -> invoke TDP fault handler ->
resolve TDP fault -> resume execution. (or emulate MMIO)
The difference is, that S-EPT is operated(read/write) via TDX SEAM
call which is expensive instead of direct read/write EPT entry.
One bit of GPA (51 or 47 bit) is repurposed so that it means shared
with host(if set to 1) or private to TD(if cleared to 0).

- The current implementation
  . Reuse the existing MMU code with minimal update.  Because the
    execution flow is mostly same. But additional operation, TDX call
    for S-EPT, is needed. So add hooks for it to kvm_x86_ops.
  . For performance, minimize TDX SEAM call to operate on S-EPT. When
    getting corresponding S-EPT pages/entry from faulting GPA, don't
    use TDX SEAM call to read S-EPT entry. Instead create shadow copy
    in host memory.
    Repurpose the existing kvm_mmu_page as shadow copy of S-EPT and
    associate S-EPT to it.
  . Treats share bit as attributes. mask/unmask the bit where
    necessary to keep the existing traversing code works.
    Introduce kvm.arch.gfn_shared_mask and use "if (gfn_share_mask)"
    for special case.
    = 0 : for non-TDX case
    = 51 or 47 bit set for TDX case.

  Pros:
  - Large code reuse with minimal new hooks.
  - Execution path is same.
  Cons:
  - Complicates the existing code.
  - Repurpose kvm_mmu_page as shadow of Secure-EPT can be confusing.

Alternative:
- Replace direct read/write on EPT entry with TDX-SEAM call by
  introducing callbacks on EPT entry.
  Pros:
  - Straightforward.
  Cons:
  - Too many touching point.
  - Too slow due to TDX-SEAM call.
  - Overhead even when TDX is disabled(CONFIG_KVM_INTEL_TDX=n).

- Sprinkle "if (is-tdx)" for TDX special case
  Pros:
  - Straightforward.
  Cons:
  - The result is non-generic and ugly.
  - Put TDX specific logic into common KVM MMU code.

** New KVM API, ioctl (sub)command, to manage TD VMs
Additional KVM API are needed to control TD VMs. The operations on TD
VMs are specific to TDX.

- Piggyback and repurpose KVM_MEMORY_ENCRYPT_OP
  Although not all operation isn't memory encryption, repupose to get
  TDX specific ioctls.
  Pros:
  - No major change in common x86 KVM code.
  Cons:
  - The operations aren't actually memory encryption, but operations
    on TD VMs.

Alternative:
- Introduce new ioctl for guest protection like
  KVM_GUEST_PROTECTION_OP and introduce subcommand for TDX.
  Pros:
  - Clean name.
  Cons:
  - One more new ioctl for guest protection.
  - Confusion with KVM_MEMORY_ENCRYPT_OP with KVM_GUEST_PROTECTION_OP.

- Rename KVM_MEMORY_ENCRYPT_OP to KVM_GUEST_PROTECTION_OP and keep
  KVM_MEMORY_ENCRYPT_OP as same value for user API for compatibility.
  "#define KVM_MEMORY_ENCRYPT_OP KVM_GUEST_PROTECTION_OP" for uapi
  compatibility.
  Pros:
  - No new ioctl with more suitable name.
  Cons:
  - May cause confusion to the existing user program.


* Items unsupported/out of the scope
Those items are unsupported at the moment or out of the scope.
- Large page(2MB, 1GB) support
- Page migration
- Debugger support(qemu gdb stub)
- Removing user space(qemu) mapping of guest private memory
  Because this topic itself is big and will take time, the effort is
  taking place independently. [12]
- Attestation
  The end-to-end integration is required.
- Live migration
  TDX 1.0 doesn't support this.
- Nested virtualization
  TDX 1.0 doesn't support this.


* Related repositories
TDX enabling software are composed of several components. Not only
KVM/x86 enablement, but also other components. There are several
publicly available repositories in github. Those are not complete, not
working, but only for reference for those who are curious.
- TDX host/guest [8]
- TDX Virtual Firmware [9]
- qemu change isn't published (yet).


* Related presentations
At KVM forum 2020, several presentation related to TDX were given. [10] [11]
They are helpful to understand TDX and KVM/qemu related changes.


* Patch organization
The main changes are only 2 patches(62 and 64).
The preceding patches(01-61) are refactoring the code and introducing
additional hooks. The patch 64 plugs hooks into TDX implementation.

- patch 01-16: They are preparations. introduce architecture
               constants, code refactoring, export symbols for
               following patches.
- patch 17-33: start to introduce the new type of VM and allow the
               coexistence of multiple type of VM. allow/disallow KVM
               ioctl where appropriate. Especially make per-system
               ioctl to per-VM ioctl.
- patch 34-43: refactoring KVM MMU and adding new hooks for Secure
               EPT.
- patch 44-48: refactoring KVM/VMX code + wrapper for kvm_x86_ops for
               VMX and TDX.
- patch 52-61: introducing TDX architectural constants/structures and
               helper functions.
- patch 62-63: load/init TDX module during boot.
- patch 64-65: main patch to add "basic" support for building/running
               TDX.
- patch 66   : This patch is not for review, but to make build success.


[1] TDX specification
   https://software.intel.com/content/www/us/en/develop/articles/intel-trust-domain-extensions.html
[2] Intel Trust Domain Extensions (Intel TDX)
   https://software.intel.com/content/dam/develop/external/us/en/documents/tdx-whitepaper-final9-17.pdf
[3] Intel CPU Architectural Extensions Specification
   https://software.intel.com/content/dam/develop/external/us/en/documents/intel-tdx-cpu-architectural-specification.pdf
[4] Intel TDX Module 1.0 EAS
   https://software.intel.com/content/dam/develop/external/us/en/documents/intel-tdx-module-1eas.pdf
[5] Intel TDX Loader Interface Specification
   https://software.intel.com/content/dam/develop/external/us/en/documents/intel-tdx-seamldr-interface-specification.pdf
[6] Intel TDX Guest-Hypervisor Communication Interface
   https://software.intel.com/content/dam/develop/external/us/en/documents/intel-tdx-guest-hypervisor-communication-interface.pdf
[7] Intel TDX Virtual Firmware Design Guide
   https://software.intel.com/content/dam/develop/external/us/en/documents/tdx-virtual-firmware-design-guide-rev-1.
[8] intel public github
   kvm TDX branch: https://github.com/intel/tdx/tree/kvm
   TDX guest branch: https://github.com/intel/tdx/tree/guest
[9] tdvf
    https://github.com/tianocore/edk2-staging/tree/TDVF
[10] KVM forum 2020: Intel Virtualization Technology Extensions to
     Enable Hardware Isolated VMs
     https://osseu2020.sched.com/event/eDzm/intel-virtualization-technology-extensions-to-enable-hardware-isolated-vms-sean-christopherson-intel
[11] Linux Security Summit EU 2020:
     Architectural Extensions for Hardware Virtual Machine Isolation
     to Advance Confidential Computing in Public Clouds - Ravi Sahita
     & Jun Nakajima, Intel Corporation
     https://osseu2020.sched.com/event/eDOx/architectural-extensions-for-hardware-virtual-machine-isolation-to-advance-confidential-computing-in-public-clouds-ravi-sahita-jun-nakajima-intel-corporation
[12] [RFCv2,00/16] KVM protected memory extension
     https://lkml.org/lkml/2020/10/20/66


Isaku Yamahata (4):
  KVM: x86: Make KVM_CAP_X86_SMM a per-VM capability
  KVM: Add per-VM flag to mark read-only memory as unsupported
  fixup! KVM: TDX: Add "basic" support for building and running Trust
    Domains
  KVM: X86: not for review: add dummy file for TDX-SEAM module

Kai Huang (3):
  KVM: x86: Add per-VM flag to disable in-kernel I/O APIC and level
    routes
  KVM: TDX: Add SEAMRR related MSRs macro definition
  cpu/hotplug: Document that TDX also depends on booting CPUs once

Rick Edgecombe (1):
  KVM: x86: Add infrastructure for stolen GPA bits

Sean Christopherson (58):
  x86/cpufeatures: Add synthetic feature flag for TDX (in host)
  x86/msr-index: Define MSR_IA32_MKTME_KEYID_PART used by TDX
  KVM: Export kvm_io_bus_read for use by TDX for PV MMIO
  KVM: Enable hardware before doing arch VM initialization
  KVM: x86: Split core of hypercall emulation to helper function
  KVM: x86: Export kvm_mmio tracepoint for use by TDX for PV MMIO
  KVM: x86/mmu: Zap only leaf SPTEs for deleted/moved memslot by default
  KVM: Add infrastructure and macro to mark VM as bugged
  KVM: Export kvm_make_all_cpus_request() for use in marking VMs as
    bugged
  KVM: x86: Use KVM_BUG/KVM_BUG_ON to handle bugs that are fatal to the
    VM
  KVM: x86/mmu: Mark VM as bugged if page fault returns RET_PF_INVALID
  KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd()
  KVM: Add max_vcpus field in common 'struct kvm'
  KVM: x86: Add vm_type to differentiate legacy VMs from protected VMs
  KVM: x86: Hoist kvm_dirty_regs check out of sync_regs()
  KVM: x86: Introduce "protected guest" concept and block disallowed
    ioctls
  KVM: x86: Add per-VM flag to disable direct IRQ injection
  KVM: x86: Add flag to disallow #MC injection / KVM_X86_SETUP_MCE
  KVM: x86: Add flag to mark TSC as immutable (for TDX)
  KVM: Add per-VM flag to disable dirty logging of memslots for TDs
  KVM: x86: Allow host-initiated WRMSR to set X2APIC regardless of CPUID
  KVM: x86: Add kvm_x86_ops .cache_gprs() and .flush_gprs()
  KVM: x86: Add support for vCPU and device-scoped KVM_MEMORY_ENCRYPT_OP
  KVM: x86: Introduce vm_teardown() hook in kvm_arch_vm_destroy()
  KVM: x86: Add a switch_db_regs flag to handle TDX's auto-switched
    behavior
  KVM: x86: Check for pending APICv interrupt in kvm_vcpu_has_events()
  KVM: x86: Add option to force LAPIC expiration wait
  KVM: x86: Add guest_supported_xss placholder
  KVM: Export kvm_is_reserved_pfn() for use by TDX
  KVM: x86/mmu: Explicitly check for MMIO spte in fast page fault
  KVM: x86/mmu: Track shadow MMIO value on a per-VM basis
  KVM: x86/mmu: Ignore bits 63 and 62 when checking for "present" SPTEs
  KVM: x86/mmu: Allow non-zero init value for shadow PTE
  KVM: x86/mmu: Refactor shadow walk in __direct_map() to reduce
    indentation
  KVM: x86/mmu: Return old SPTE from mmu_spte_clear_track_bits()
  KVM: x86/mmu: Frame in support for private/inaccessible shadow pages
  KVM: x86/mmu: Move 'pfn' variable to caller of direct_page_fault()
  KVM: x86/mmu: Introduce kvm_mmu_map_tdp_page() for use by TDX
  KVM: VMX: Modify NMI and INTR handlers to take intr_info as param
  KVM: VMX: Move NMI/exception handler to common helper
  KVM: VMX: Split out guts of EPT violation to common/exposed function
  KVM: VMX: Define EPT Violation architectural bits
  KVM: VMX: Define VMCS encodings for shared EPT pointer
  KVM: VMX: Add 'main.c' to wrap VMX and TDX
  KVM: VMX: Move setting of EPT MMU masks to common VT-x code
  KVM: VMX: Move register caching logic to common code
  KVM: TDX: Add TDX "architectural" error codes
  KVM: TDX: Add architectural definitions for structures and values
  KVM: TDX: Define TDCALL exit reason
  KVM: TDX: Add macro framework to wrap TDX SEAMCALLs
  KVM: TDX: Stub in tdx.h with structs, accessors, and VMCS helpers
  KVM: VMX: Add macro framework to read/write VMCS for VMs and TDs
  KVM: VMX: Move AR_BYTES encoder/decoder helpers to common.h
  KVM: VMX: MOVE GDT and IDT accessors to common code
  KVM: VMX: Move .get_interrupt_shadow() implementation to common VMX
    code
  KVM: TDX: Load and init TDX-SEAM module during boot
  KVM: TDX: Add "basic" support for building and running Trust Domains
  KVM: x86: Mark the VM (TD) as bugged if non-coherent DMA is detected

Zhang Chen (1):
  x86/cpu: Move get_builtin_firmware() common code (from microcode only)

 arch/arm64/include/asm/kvm_host.h     |    3 -
 arch/arm64/kvm/arm.c                  |    7 +-
 arch/arm64/kvm/vgic/vgic-init.c       |    6 +-
 arch/x86/Kbuild                       |    1 +
 arch/x86/include/asm/cpu.h            |    5 +
 arch/x86/include/asm/cpufeatures.h    |    1 +
 arch/x86/include/asm/kvm_boot.h       |   43 +
 arch/x86/include/asm/kvm_host.h       |   52 +-
 arch/x86/include/asm/microcode.h      |    3 -
 arch/x86/include/asm/msr-index.h      |   10 +
 arch/x86/include/asm/vmx.h            |    6 +
 arch/x86/include/asm/vmxfeatures.h    |    2 +-
 arch/x86/include/uapi/asm/kvm.h       |   55 +
 arch/x86/include/uapi/asm/vmx.h       |    4 +-
 arch/x86/kernel/cpu/common.c          |   20 +
 arch/x86/kernel/cpu/intel.c           |    4 +
 arch/x86/kernel/cpu/microcode/core.c  |   18 -
 arch/x86/kernel/cpu/microcode/intel.c |    1 +
 arch/x86/kernel/setup.c               |    3 +
 arch/x86/kvm/Kconfig                  |    8 +
 arch/x86/kvm/Makefile                 |    2 +-
 arch/x86/kvm/boot/Makefile            |    5 +
 arch/x86/kvm/boot/seam/seamldr.S      |  188 +++
 arch/x86/kvm/boot/seam/seamloader.c   |  162 +++
 arch/x86/kvm/boot/seam/tdx.c          | 1131 +++++++++++++++
 arch/x86/kvm/ioapic.c                 |    4 +
 arch/x86/kvm/irq_comm.c               |    6 +-
 arch/x86/kvm/lapic.c                  |    9 +-
 arch/x86/kvm/lapic.h                  |    2 +-
 arch/x86/kvm/mmu.h                    |   33 +-
 arch/x86/kvm/mmu/mmu.c                |  519 +++++--
 arch/x86/kvm/mmu/mmu_internal.h       |    5 +
 arch/x86/kvm/mmu/paging_tmpl.h        |   27 +-
 arch/x86/kvm/mmu/spte.c               |   36 +-
 arch/x86/kvm/mmu/spte.h               |   30 +-
 arch/x86/kvm/svm/svm.c                |   22 +-
 arch/x86/kvm/trace.h                  |   57 +
 arch/x86/kvm/vmx/common.h             |  180 +++
 arch/x86/kvm/vmx/main.c               | 1130 +++++++++++++++
 arch/x86/kvm/vmx/posted_intr.c        |    6 +
 arch/x86/kvm/vmx/tdx.c                | 1847 +++++++++++++++++++++++++
 arch/x86/kvm/vmx/tdx.h                |  245 ++++
 arch/x86/kvm/vmx/tdx_arch.h           |  230 +++
 arch/x86/kvm/vmx/tdx_errno.h          |   91 ++
 arch/x86/kvm/vmx/tdx_ops.h            |  544 ++++++++
 arch/x86/kvm/vmx/tdx_stubs.c          |   45 +
 arch/x86/kvm/vmx/vmenter.S            |  140 ++
 arch/x86/kvm/vmx/vmx.c                |  537 ++-----
 arch/x86/kvm/vmx/vmx.h                |    2 +
 arch/x86/kvm/x86.c                    |  296 +++-
 include/linux/kvm_host.h              |   51 +-
 include/uapi/linux/kvm.h              |    2 +
 kernel/cpu.c                          |    4 +
 lib/firmware/intel-seam/libtdx.so     |    0
 tools/arch/x86/include/uapi/asm/kvm.h |   55 +
 tools/include/uapi/linux/kvm.h        |    2 +
 virt/kvm/kvm_main.c                   |   45 +-
 57 files changed, 7230 insertions(+), 712 deletions(-)
 create mode 100644 arch/x86/include/asm/kvm_boot.h
 create mode 100644 arch/x86/kvm/boot/Makefile
 create mode 100644 arch/x86/kvm/boot/seam/seamldr.S
 create mode 100644 arch/x86/kvm/boot/seam/seamloader.c
 create mode 100644 arch/x86/kvm/boot/seam/tdx.c
 create mode 100644 arch/x86/kvm/vmx/common.h
 create mode 100644 arch/x86/kvm/vmx/main.c
 create mode 100644 arch/x86/kvm/vmx/tdx.c
 create mode 100644 arch/x86/kvm/vmx/tdx.h
 create mode 100644 arch/x86/kvm/vmx/tdx_arch.h
 create mode 100644 arch/x86/kvm/vmx/tdx_errno.h
 create mode 100644 arch/x86/kvm/vmx/tdx_ops.h
 create mode 100644 arch/x86/kvm/vmx/tdx_stubs.c
 create mode 100644 lib/firmware/intel-seam/libtdx.so
```
#### [PATCH 00/11] Add QEMU debug support for SEV guests
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Mon Nov 16 18:48:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11910539
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E41FCC2D0A3
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:49:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8F6F92224B
	for <kvm@archiver.kernel.org>; Mon, 16 Nov 2020 18:49:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="uhuj9bCj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728267AbgKPSsl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 16 Nov 2020 13:48:41 -0500
Received: from mail-dm6nam08on2055.outbound.protection.outlook.com
 ([40.107.102.55]:32128
        "EHLO NAM04-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727852AbgKPSsl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Nov 2020 13:48:41 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lioW1Kctv0pULbwXVjxWcRMCyFL6Wfm3C5oxokdwniTK9gDNevTcBtFtejZCgXQ7CoozcPAXpfrW/1QLbmSyV5UF1BxSxAm3LCV74iy9YIhbCn+vSOPXZZMMxR4cfDpzk2JSzrMgIStpmN1rfQ/drYg8S3Ha1EOgZ0ZdYDZntm+WGsyB3IKrQ3ZR3D9i4tGNdnyP3xF9hwOU4Cuz+Rm5pqU4U3df1Tv9i3KL8WifAQKgENZtRZQhxqnngVFE91U6IWckYKGfxveDhb80VmUDOrBEygYeccaa9u/ZNE53i8fUjYMPgs8nlV9tIGhq/WY/xkFKrl1q+dxfoPR4pD+Gbg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IKE/Uoe+YycYp4dENPgGTLg3L4L3gwfpPsOFlfdazJs=;
 b=d6zD01R+NMFxUVq2PLwX0Kmr0vXAyrM4a6bO1qWuCWg2aKNBhaW4zciyPqs/TxGde4AIyB4C8KjWJo+ZVUuQYL2MC93v3sDAQ4WLJEMDI1zH9biGJM4kMehRd0PfHF1c50Ft8QQ36loXFcczwsu2vR6Q7Ruwy0EhTXW0NWcVL7dVavE2ZlZcbjdTkWCmpJNc7WM7JTXH2ChWt4jbjW9SEslqNMAKCKcHp2DlKL7RxWzXAufrdo7eD2OMja18qNNQgB/D2hMkIhgCeZinIw2ZLXDA6GTdlTn45VyN8ZzCoiB9fEpDGYsRXThcKF5WJhmufYnkx4Sfmlbi246lTfFDBQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=IKE/Uoe+YycYp4dENPgGTLg3L4L3gwfpPsOFlfdazJs=;
 b=uhuj9bCjZD+LOwsMiAlLTdJIksoT9zwrl93fn8Mg1y5MXEZkYP4Ke6wEKJzD3GsQMA66dqmpJOPwDxjplpO5E1lA9Tfeg3PZyk+s4E7dr9CZLcRWjz0R0WvLM0FZjB54kNLMPgOxUCTDNiNdqjQg44l6O6OHA3bnut5A58EqFHI=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2782.namprd12.prod.outlook.com (2603:10b6:805:73::19) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3499.19; Mon, 16 Nov
 2020 18:48:35 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::d8f2:fde4:5e1d:afec%3]) with mapi id 15.20.3541.025; Mon, 16 Nov 2020
 18:48:35 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: qemu-devel@nongnu.org, rth@twiddle.net, armbru@redhat.com,
        dgilbert@redhat.com, ehabkost@redhat.com, kvm@vger.kernel.org,
        mst@redhat.com, marcel.apfelbaum@gmail.com, mtosatti@redhat.com,
        Thomas.Lendacky@amd.com, brijesh.singh@amd.com,
        ssg.sos.patches@amd.com
Subject: [PATCH 00/11] Add QEMU debug support for SEV guests
Date: Mon, 16 Nov 2020 18:48:24 +0000
Message-Id: <cover.1605316268.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: DM5PR07CA0112.namprd07.prod.outlook.com
 (2603:10b6:4:ae::41) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM5PR07CA0112.namprd07.prod.outlook.com (2603:10b6:4:ae::41) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3564.28 via Frontend
 Transport; Mon, 16 Nov 2020 18:48:34 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0e6c01e9-f661-4db3-76e8-08d88a60394a
X-MS-TrafficTypeDiagnostic: SN6PR12MB2782:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB27824E23E9AAD2623E47C47B8EE30@SN6PR12MB2782.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8273;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 2IWaVGE5KqNBfjjnO+SAwdpMLaFv7c8u0U3RXbPk5SBcxVtn+fkdBtfkuullMDz1r1RSSSvrYpomnSbp4G2wu22ZIR2mjeN+9ULTNW68vXubc1Kbu9tHQmIzjuQU3RS3lPcJKjAHgHVC1nEsDONzZKn1v/RJgGvrdIOnoaPE12Rz/sYxnIQHYlkSnHsIjlUVqoCRN1yo0HJWtFB95EWp7tNlj9CAGxMzi/SD5NlLoOxvVQ+LqNMdSK8UylH7CtlWyi9J62+C+VfZ2Rv6byuNb1WCywh06+1ISAF+EDhXXiWzFo2zSdMOf4rLbBmQhKg6
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(376002)(39860400002)(366004)(396003)(346002)(7416002)(6666004)(186003)(83380400001)(478600001)(4326008)(5660300002)(8936002)(2616005)(66556008)(8676002)(66476007)(6916009)(16526019)(66946007)(86362001)(316002)(7696005)(36756003)(52116002)(2906002)(26005)(6486002)(956004);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 FCUO8amu29drj4ZAY9teRNEjKR0QsmLPL8Fwp3Upl8w404zv+V9/Q+eaIb7yewra6KuuvAGTyVFUu0PSM7WsfZuH7MEA3O2TKgklBO6DPrQ6mv/7YET8cqX+ZQwd0/LcsMQteJZ4u+wBG16HLc1aQBb1DvS9fMBCmtqFjZ9GkRSw6yK42FCWsvVW50FFJu21H6VZxiY68dMVKwXi/clyIDdzq0vTFRyMGlPSheZhJQhDhhUsI1LsuTmGUrmS9NGgSF5DpNFC1XHowHytNpdB+kNPiWBwXka0zHl89xUkqQ2vV9kgL984C45bqxVUTljYybjacQafFbH1hIakCv66E2f1Q52Xc3XYAK5yeJXHGHGmAldhAQwvdTc7P8TUxPBMReVh2Z3v4UJzZW0xfDCluZjQEr4WGx4MWFw7HyDUhLAZFa18sRs5sfgeEEnzdB+N5WX4IEvvGgHxvkpRwi0H3Urwi10GJSW4B+NhItYBvCblFpBDvdhwyXYzyxDLqiZM0yCHJPpWWgpbKkAGL10Oz011hm2Bgi9pGORU9NUSIl5BRaZEhTO7akfa5uOj8138+colPGzYVdaJs60lp3Nf9ie43PKxTIPUlGRsmaxuLBCKNACbcMCFFx3Gh5wUdD0R86LiZwbGAeH71n/l4Xoilq/hBfIWdijxa8E7dWZhKtdSEcFIduyzuMf1dn15n0/5ubE2GNWueqV3YKRbw/dg8ff5wgK5mgyxLJ50ODLMNTt9iNsbrov+mEG7/ZLICuWDPpfg8a+pCumfdMPUTPI7Ylnn4dIeFbIq8dcDsH17WP72xUnfy4lmn7djnkCvxH2v1MG5G+L3y4R+umCIWw6V+oeCE3clRAfs/Q+pfKsRh89+thn1d2ukpluBTip7//SoMSAHxkmS7IJk54TFDpyGVw==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0e6c01e9-f661-4db3-76e8-08d88a60394a
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 16 Nov 2020 18:48:35.7099
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 mNFKoiplmUI1+A+qBTwC67OVJTheV75xXRfnyJEExvjXqBy/2sB0LcXdp0y/Hcw1Mdsl8Cu2TCfN8bTzhgAT0A==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2782
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

This patchset adds QEMU debug support for SEV guests. Debug requires access to the guest pages, which is encrypted when SEV is enabled.

KVM_SEV_DBG_DECRYPT and KVM_SEV_DBG_ENCRYPT commands are available to decrypt/encrypt the guest pages, if the guest policy allows for debugging.

Changes are made to the guest page table walker since SEV guest pte entries will have the C-bit set.

Also introduces new MemoryDebugOps which hook into guest virtual and physical memory debug interfaces such as cpu_memory_rw_debug,
to allow vendor specific assist/hooks for debugging and delegating accessing the guest memory.  This is used for example in case of
AMD SEV platform where the guest memory is encrypted and a SEV specific debug assist/hook will be required to access the guest memory.

The MemoryDebugOps are used by cpu_memory_rw_debug() and default to address_space_read and address_space_write_rom as described below.

typedef struct MemoryDebugOps {
    MemTxResult (*read)(AddressSpace *as, hwaddr phys_addr,
                        MemTxAttrs attrs, void *buf,
                        hwaddr len);
    MemTxResult (*write)(AddressSpace *as, hwaddr phys_addr,
                         MemTxAttrs attrs, const void *buf,
                         hwaddr len);
} MemoryDebugOps;

These ops would be used only by cpu_memory_rw_debug and would default to

static const MemoryDebugOps default_debug_ops = {
    .translate = cpu_get_phys_page_attrs_debug,
    .read = address_space_read,
    .write = address_space_write_rom
};

static const MemoryDebugOps *debug_ops = &default_debug_ops;

Ashish Kalra (3):
  exec: Add new MemoryDebugOps.
  exec: Add address_space_read and address_space_write debug helpers.
  sev/i386: add SEV specific MemoryDebugOps.

Brijesh Singh (8):
  memattrs: add debug attribute
  exec: add ram_debug_ops support
  exec: add debug version of physical memory read and write API
  monitor/i386: use debug APIs when accessing guest memory
  kvm: introduce debug memory encryption API
  sev/i386: add debug encrypt and decrypt commands
  hw/i386: set ram_debug_ops when memory encryption is enabled
  target/i386: clear C-bit when walking SEV guest page table

 accel/kvm/kvm-all.c       |  22 ++++
 accel/kvm/sev-stub.c      |   8 ++
 accel/stubs/kvm-stub.c    |   8 ++
 hw/i386/pc.c              |   9 ++
 hw/i386/pc_sysfw.c        |   6 +
 include/exec/cpu-common.h |  18 +++
 include/exec/memattrs.h   |   2 +
 include/exec/memory.h     |  49 ++++++++
 include/sysemu/kvm.h      |  15 +++
 include/sysemu/sev.h      |  12 ++
 monitor/misc.c            |   4 +-
 softmmu/cpus.c            |   2 +-
 softmmu/physmem.c         | 170 +++++++++++++++++++++++++-
 target/i386/kvm.c         |   4 +
 target/i386/monitor.c     | 124 +++++++++++--------
 target/i386/sev.c         | 244 ++++++++++++++++++++++++++++++++++++++
 target/i386/trace-events  |   1 +
 17 files changed, 642 insertions(+), 56 deletions(-)
```
