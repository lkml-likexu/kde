

#### [PATCH v15 00/12] SMMUv3 Nested Stage Setup (IOMMU part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Sun Apr 11 11:12:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12196187
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B9B9FC433ED
	for <kvm@archiver.kernel.org>; Sun, 11 Apr 2021 11:12:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8ECE5610CB
	for <kvm@archiver.kernel.org>; Sun, 11 Apr 2021 11:12:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235369AbhDKLNN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 11 Apr 2021 07:13:13 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:38132 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S235247AbhDKLNM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 11 Apr 2021 07:13:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618139575;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=VZ5ZgqkLKGzZ6mZcaLAP7WgqAO/FhHDbjCu61E17AlI=;
        b=EPvZ9Edgvp/SK/fDwAuxSJg8akO/XnOUWtOExuy9AU117guzj46rVy036cojPLjaGRG200
        X4Avge2VIlooLuwDe3nQcEWMvSSptjHVpA+syC7q7OD3iNf17p6qx5Q9gXse9FgImbXMsy
        rvJ5Fgzq/5Rmf7ql1MVzUhdfSy/Csi4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-424-Lz5o6dudMNmUzPQlCMbKnQ-1; Sun, 11 Apr 2021 07:12:51 -0400
X-MC-Unique: Lz5o6dudMNmUzPQlCMbKnQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 61CFD107ACC7;
        Sun, 11 Apr 2021 11:12:48 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-22.ams2.redhat.com [10.36.112.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B064C100164A;
        Sun, 11 Apr 2021 11:12:32 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jean-philippe@linaro.org,
        zhangfei.gao@linaro.org, zhangfei.gao@gmail.com,
        vivek.gautam@arm.com, shameerali.kolothum.thodi@huawei.com,
        yuzenghui@huawei.com, nicoleotsuka@gmail.com,
        lushenming@huawei.com, vsethi@nvidia.com,
        chenxiang66@hisilicon.com, vdumpa@nvidia.com,
        jiangkunkun@huawei.com
Subject: [PATCH v15 00/12] SMMUv3 Nested Stage Setup (IOMMU part)
Date: Sun, 11 Apr 2021 13:12:16 +0200
Message-Id: <20210411111228.14386-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SMMUv3 Nested Stage Setup (IOMMU part)

This series brings the IOMMU part of HW nested paging support
in the SMMUv3. The VFIO part is submitted separately.

This is based on Jean-Philippe's
[PATCH v14 00/10] iommu: I/O page faults for SMMUv3
https://www.spinics.net/lists/arm-kernel/msg886518.html
(including the patches that were not pulled for 5.13)

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
v5.12-rc6-jean-iopf-14-2stage-v15
(including the VFIO part in its last version: v13)

The VFIO series is sent separately.

History:

Previous version:
https://github.com/eauger/linux/tree/v5.11-stallv12-2stage-v14

v14 -> v15:
- on S1 invalidation, always use CMDQ_OP_TLBI_NH_VA
  independently on host ARM_SMMU_FEAT_E2H support (Zenghui)
- remove  iommu/smmuv3: Accept configs with more than one
  context descriptor
- Remove spurious arm_smmu_cmdq_issue_sync in
  IOMMU_INV_GRANU_ADDR cache invalidation (Zenghui)
- dma-iommu.c changes induced by Zenghui's comments
  including the locking rework
- fix cache invalidation when guest uses RIL
  and host does not support it (Chenxiang)
- removed iommu/smmuv3: Accept configs with more than one
  context descriptor (Zenghui, Shameer)
- At this point I have kept the MSI binding API.

v13 -> v14:
- Took into account all received comments I think. Great
  thanks to all the testers for their effort and sometimes
  tentative fixes. I am really grateful to you!
- numerous fixes including guest running in
  noiommu, iommu.strict=0, iommu.passthrough=on,
  enable_unsafe_noiommu_mode

v12 -> v13:
- fixed compilation issue with CONFIG_ARM_SMMU_V3_SVA
  reported by Shameer. This urged me to revisit patch 4 into
  iommu/smmuv3: Allow s1 and s2 configs to coexist where
  s1_cfg and s2_cfg are not dynamically allocated anymore.
  Instead I use a new set field in existing structs
- fixed 2 others config checks
- Updated "iommu/arm-smmu-v3: Maintain a SID->device structure"
  according to the last version

v11 -> v12:
- rebase on top of v5.10-rc4


Eric Auger (12):
  iommu: Introduce attach/detach_pasid_table API
  iommu: Introduce bind/unbind_guest_msi
  iommu/smmuv3: Allow s1 and s2 configs to coexist
  iommu/smmuv3: Get prepared for nested stage support
  iommu/smmuv3: Implement attach/detach_pasid_table
  iommu/smmuv3: Allow stage 1 invalidation with unmanaged ASIDs
  iommu/smmuv3: Implement cache_invalidate
  dma-iommu: Implement NESTED_MSI cookie
  iommu/smmuv3: Nested mode single MSI doorbell per domain enforcement
  iommu/smmuv3: Enforce incompatibility between nested mode and HW MSI
    regions
  iommu/smmuv3: Implement bind/unbind_guest_msi
  iommu/smmuv3: report additional recoverable faults

 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 463 ++++++++++++++++++--
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h |  14 +-
 drivers/iommu/dma-iommu.c                   | 180 +++++++-
 drivers/iommu/iommu.c                       | 106 +++++
 include/linux/dma-iommu.h                   |  16 +
 include/linux/iommu.h                       |  47 ++
 include/uapi/linux/iommu.h                  |  54 +++
 7 files changed, 838 insertions(+), 42 deletions(-)
```
#### [PATCH v13 00/13] SMMUv3 Nested Stage Setup (VFIO part)
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Sun Apr 11 11:46:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 12196217
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2E810C433B4
	for <kvm@archiver.kernel.org>; Sun, 11 Apr 2021 11:47:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DF762610E9
	for <kvm@archiver.kernel.org>; Sun, 11 Apr 2021 11:47:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235417AbhDKLrq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 11 Apr 2021 07:47:46 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:44368 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232223AbhDKLrp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sun, 11 Apr 2021 07:47:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618141647;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=i/Qya5gYlpQU+h8vw6iTmP2eW8gYE13bTztPj4lYMq4=;
        b=EnsudmBe4W6V79c3+XuqGJ/6M8dlAOuQwYfvFAVsJPaiONhzAZlwhhSuVltVBAj5Z8ehLE
        qsBi/e2LZSQZRSAa25xAhnEz8FClc4rBm8iDpkvvhPGb+1G5wlgbHE8QJSBQ98faQvWwCd
        1fauKKHAQIfrWhtvzqs1Ita4Ond7Hf0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-592-26xNIX_tNuykPaTM3aRqmQ-1; Sun, 11 Apr 2021 07:47:23 -0400
X-MC-Unique: 26xNIX_tNuykPaTM3aRqmQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 721E71006701;
        Sun, 11 Apr 2021 11:47:20 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-112-22.ams2.redhat.com [10.36.112.22])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7A66B5C22A;
        Sun, 11 Apr 2021 11:47:02 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu, will@kernel.org,
        maz@kernel.org, robin.murphy@arm.com, joro@8bytes.org,
        alex.williamson@redhat.com, tn@semihalf.com, zhukeqian1@huawei.com
Cc: jacob.jun.pan@linux.intel.com, yi.l.liu@intel.com,
        wangxingang5@huawei.com, jean-philippe@linaro.org,
        zhangfei.gao@linaro.org, zhangfei.gao@gmail.com,
        vivek.gautam@arm.com, shameerali.kolothum.thodi@huawei.com,
        yuzenghui@huawei.com, nicoleotsuka@gmail.com,
        lushenming@huawei.com, vsethi@nvidia.com,
        chenxiang66@hisilicon.com, vdumpa@nvidia.com,
        jiangkunkun@huawei.com
Subject: [PATCH v13 00/13] SMMUv3 Nested Stage Setup (VFIO part)
Date: Sun, 11 Apr 2021 13:46:46 +0200
Message-Id: <20210411114659.15051-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series brings the VFIO part of HW nested paging support
in the SMMUv3.

The series depends on:
[PATCH v15 00/13] SMMUv3 Nested Stage Setup (IOMMU part)

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
https://github.com/eauger/linux/tree/v5.12-rc6-jean-iopf-14-2stage-v15

The series series includes Tina's patch steming from
[1] "[RFC PATCH v2 1/3] vfio: Use capability chains to handle device
specific irq" plus patches originally contributed by Yi.

History:

v12 -> v13:
- Comment fix for VFIO_IOMMU_SET_PASID_TABLE (Zenghui)

v11 -> v12:
- numerous fixes following feedbacks. Many thanks to all of you
- See individual history log.

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
 drivers/vfio/pci/vfio_pci.c         | 447 ++++++++++++++++++++++++++--
 drivers/vfio/pci/vfio_pci_intrs.c   |  62 ++++
 drivers/vfio/pci/vfio_pci_private.h |  33 ++
 drivers/vfio/pci/vfio_pci_rdwr.c    |  84 ++++++
 drivers/vfio/vfio_iommu_type1.c     | 178 +++++++++++
 include/uapi/linux/vfio.h           | 142 ++++++++-
 7 files changed, 1003 insertions(+), 20 deletions(-)
```
