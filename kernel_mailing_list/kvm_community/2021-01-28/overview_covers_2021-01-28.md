

#### [PATCH v3 0/2] KVM: x86/mmu: Skip mmu_notifier changes when possible
##### From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>

```c
From patchwork Thu Jan 28 06:05:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Stevens <stevensd@chromium.org>
X-Patchwork-Id: 12051823
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C373EC433DB
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 06:06:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E78364DD6
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 06:06:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231307AbhA1GGP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 01:06:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47950 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229786AbhA1GGI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 01:06:08 -0500
Received: from mail-pg1-x532.google.com (mail-pg1-x532.google.com
 [IPv6:2607:f8b0:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 400B6C061573
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 22:05:28 -0800 (PST)
Received: by mail-pg1-x532.google.com with SMTP id o7so3614791pgl.1
        for <kvm@vger.kernel.org>; Wed, 27 Jan 2021 22:05:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=chromium.org; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Il8qZNLJiUnVs1yENR7U+/PHj95Y8fthqxWVAqkzlPM=;
        b=FOBAuUwtS7jVTeXxIChL9bNsz+Er77qc8WeJTUw3A9nq5VmzNwUAKBriJKft/2FquC
         lZ1AHyh5KOkJj9MCdwK+uRaOkDxeiWtZsQ5uhyci9WKjrgU878iPVblmqSfMotl3qqsZ
         AadDpgG2cJ01V8kMSBtXZ7XoVEWtzV5RpOGlc=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Il8qZNLJiUnVs1yENR7U+/PHj95Y8fthqxWVAqkzlPM=;
        b=Nzy8YZV4RKeWp0733XvPE9Xt+JO5bvrQ2LTf8nyxUrcHxrg8VAhRJ8kM+ePEIi4Llz
         O7G4OcdsjYdAZdlHwAc46S1hRkzfqCG/u5q/PoOlYQy8caRLonx0nHJ7Kc8hEtXUQNsa
         Tv26Nq78n/Gs7k84DpqtZG7EeukYlc99IY5aiSjNXHCK+rlDejnQ9N/kHW3GaxComGmg
         YF7X89ocHyRy0Ef5ExX6mQ68MXUe9NMFkMKIXPJCanzTyX4uHsfyZBdGsDOT0ZPomyHM
         E/3IzuBqp/H++NqTmbSFOPl8z2YOhjBobQonUnusWRLosmcbXRdL4+fEiAWl3ZVPMmPb
         GyBQ==
X-Gm-Message-State: AOAM530iE+jmsoEZIQYsG2RHjFjdr3Be4tSgNyDj1DFJcjXNFGH+W5+u
        bZTaYDmCo34QR8fz520uvtTebg==
X-Google-Smtp-Source: 
 ABdhPJxidwWhR7mlBTuFlylUNvopLRyxeu+Iq8ZjCqlH84G6RemXi1bI0gdxZW+QAPoQaFarpqDzPg==
X-Received: by 2002:a62:1690:0:b029:1c6:fdac:3438 with SMTP id
 138-20020a6216900000b02901c6fdac3438mr6879262pfw.43.1611813927818;
        Wed, 27 Jan 2021 22:05:27 -0800 (PST)
Received: from localhost ([2401:fa00:8f:203:919f:d6:7815:52bc])
        by smtp.gmail.com with ESMTPSA id
 z6sm4345903pfr.133.2021.01.27.22.05.23
        (version=TLS1_3 cipher=TLS_AES_128_GCM_SHA256 bits=128/128);
        Wed, 27 Jan 2021 22:05:27 -0800 (PST)
From: David Stevens <stevensd@chromium.org>
X-Google-Original-From: David Stevens <stevensd@google.com>
To: Sean Christopherson <seanjc@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        linux-mips@vger.kernel.org, Paul Mackerras <paulus@ozlabs.org>,
        kvm-ppc@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        David Stevens <stevensd@google.com>
Subject: [PATCH v3 0/2] KVM: x86/mmu: Skip mmu_notifier changes when possible
Date: Thu, 28 Jan 2021 15:05:13 +0900
Message-Id: <20210128060515.1732758-1-stevensd@google.com>
X-Mailer: git-send-email 2.30.0.280.ga3ce27912f-goog
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These patches reduce how often mmu_notifier updates block guest page
faults. The primary benefit of this is the reduction in the likelihood
of extreme latency when handling a page fault due to another thread
having been preempted while modifying host virtual addresses.

v2 -> v3:
 - Added patch to skip check for MMIO page faults
 - Style changes

David Stevens (1):
  KVM: x86/mmu: Consider the hva in mmu_notifier retry

Sean Christopherson (1):
  KVM: x86/mmu: Skip mmu_notifier check when handling MMIO page fault

 arch/powerpc/kvm/book3s_64_mmu_hv.c    |  2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c |  2 +-
 arch/x86/kvm/mmu/mmu.c                 | 16 ++++++++------
 arch/x86/kvm/mmu/paging_tmpl.h         |  7 ++++---
 include/linux/kvm_host.h               | 25 +++++++++++++++++++++-
 virt/kvm/kvm_main.c                    | 29 ++++++++++++++++++++++----
 6 files changed, 65 insertions(+), 16 deletions(-)
```
#### [PATCH RFC v2 00/10] vdpa: add vdpa simulator for block device
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
From patchwork Thu Jan 28 14:41:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12053795
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6B44CC433E0
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 14:43:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 26FCB60C41
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 14:43:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231663AbhA1OnQ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 09:43:16 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:21343 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231276AbhA1OnH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 Jan 2021 09:43:07 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611844901;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=oKQyktnzCEz0hqPUDHkW7dyXbU3t7aSFEMciUM7CkaI=;
        b=BAADef/ICk1xX1ZSazXf93rtvnjaKHt6z25/lDsw4o+PCsuEZig1DthmAwvCX1zrfv94Bv
        2AZAA9/bKHaV1fRjM5P1Siy38PZl/1p1NV+ZOqbZXq6s4Aa7ytZHKj62zHsLXnuXXEO9AY
        zuuzsTQhF1VYfps+VqmjxzdDn3mwSiU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-360-oddZIRJDMeiHx4rcSfnbdg-1; Thu, 28 Jan 2021 09:41:37 -0500
X-MC-Unique: oddZIRJDMeiHx4rcSfnbdg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 784211800D41;
        Thu, 28 Jan 2021 14:41:36 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-219.ams2.redhat.com
 [10.36.113.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 832AE60875;
        Thu, 28 Jan 2021 14:41:28 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: Xie Yongji <xieyongji@bytedance.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        linux-kernel@vger.kernel.org, Max Gurtovoy <mgurtovoy@nvidia.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org
Subject: [PATCH RFC v2 00/10] vdpa: add vdpa simulator for block device
Date: Thu, 28 Jan 2021 15:41:17 +0100
Message-Id: <20210128144127.113245-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v1: https://lore.kernel.org/lkml/93f207c0-61e6-3696-f218-e7d7ea9a7c93@redhat.com/

This series is the second part of the v1 linked above. The first part with
refactoring of vdpa_sim has already been merged.

The patches are based on Max Gurtovoy's work and extend the block simulator to
have a ramdisk behaviour.

As mentioned in the v1 there was 2 issues and I fixed them in this series:
1. The identical mapping in the IOMMU used until now in vdpa_sim created issues
   when mapping different virtual pages with the same physical address.
   Fixed by patch "vdpa_sim: use iova module to allocate IOVA addresses"

2. There was a race accessing the IOMMU between the vdpasim_blk_work() and the
   device driver that map/unmap DMA regions. Fixed by patch "vringh: add
   'iotlb_lock' to synchronize iotlb accesses"

Since this series is still a RFC, I used the Xie's patch as is to allow
vhost-vdpa to use block devices, but I'll rebase when he splits it into
multiple patches.

The series also includes small fixes for vdpa_sim that I discovered while
implementing the block simulator.

Thanks for your feedback,
Stefano

Max Gurtovoy (1):
  vdpa: add vdpa simulator for block device

Stefano Garzarella (8):
  vdpa_sim: use iova module to allocate IOVA addresses
  vringh: add 'iotlb_lock' to synchronize iotlb accesses
  vringh: reset kiov 'consumed' field in __vringh_iov()
  vringh: implement vringh_kiov_advance()
  vringh: add vringh_kiov_length() helper
  vdpa_sim: cleanup kiovs in vdpasim_free()
  vdpa_sim_blk: implement ramdisk behaviour
  vdpa_sim_blk: handle VIRTIO_BLK_T_GET_ID

Xie Yongji (1):
  vdpa: Remove the restriction that only supports virtio-net devices

 drivers/vdpa/vdpa_sim/vdpa_sim.h     |   2 +
 include/linux/vringh.h               |  19 +-
 drivers/vdpa/vdpa_sim/vdpa_sim.c     | 118 +++++++----
 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c | 288 +++++++++++++++++++++++++++
 drivers/vhost/vdpa.c                 |  28 +--
 drivers/vhost/vringh.c               |  54 +++--
 drivers/vdpa/Kconfig                 |   8 +
 drivers/vdpa/vdpa_sim/Makefile       |   1 +
 8 files changed, 433 insertions(+), 85 deletions(-)
 create mode 100644 drivers/vdpa/vdpa_sim/vdpa_sim_blk.c
```
#### [RFC PATCH 00/11] vfio/iommu_type1: Implement dirty log tracking
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Thu Jan 28 15:17:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12053951
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 231FAC433E9
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 15:18:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E945B64DEF
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 15:18:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231244AbhA1PSv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 10:18:51 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11213 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229504AbhA1PSs (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 10:18:48 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4DRPFQ4vV3zlC5j;
        Thu, 28 Jan 2021 23:16:26 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.498.0; Thu, 28 Jan 2021 23:17:53 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, <iommu@lists.linux-foundation.org>,
        Will Deacon <will@kernel.org>,
        "Alex Williamson" <alex.williamson@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        "Robin Murphy" <robin.murphy@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH 00/11] vfio/iommu_type1: Implement dirty log tracking
 based on smmuv3 HTTU
Date: Thu, 28 Jan 2021 23:17:31 +0800
Message-ID: <20210128151742.18840-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This patch series implement a new dirty log tracking method for vfio dma.

Intention：

As we know, vfio live migration is an important and valuable feature, but there
are still many hurdles to solve, including migration of interrupt, device state,
DMA dirty log tracking, and etc.

For now, the only dirty log tracking interface is pinning. It has some drawbacks:
1. Only smart vendor drivers are aware of this.
2. It's coarse-grained, the pinned-scope is generally bigger than what the device actually access.
3. It can't track dirty continuously and precisely, vfio populates all pinned-scope as dirty.
   So it doesn't work well with iteratively dirty log handling.

About SMMU HTTU:

HTTU (Hardware Translation Table Update) is a feature of ARM SMMUv3, it can update
access flag or/and dirty state of the TTD (Translation Table Descriptor) by hardware.
With HTTU, stage1 TTD is classified into 3 types:
                        DBM bit             AP[2](readonly bit)
1. writable_clean         1                       1
2. writable_dirty         1                       0
3. readonly               0                       1

If HTTU_HD (manage dirty state) is enabled, smmu can change TTD from writable_clean to
writable_dirty. Then software can scan TTD to sync dirty state into dirty bitmap. With
this feature, we can track the dirty log of DMA continuously and precisely.

About this series:

Patch 1-3: Add feature detection for smmu HTTU and enable HTTU for smmu stage1 mapping.
           And add feature detection for smmu BBML. We need to split block mapping when
           start dirty log tracking and merge page mapping when stop dirty log tracking,
		   which requires break-before-make procedure. But it might cause problems when the
		   TTD is alive. The I/O streams might not tolerate translation faults. So BBML
		   should be used.

Patch 4-7: Add four interfaces (split_block, merge_page, sync_dirty_log and clear_dirty_log)
           in IOMMU layer, they are essential to implement dma dirty log tracking for vfio.
		   We implement these interfaces for arm smmuv3.

Patch   8: Add HWDBM (Hardware Dirty Bit Management) device feature reporting in IOMMU layer.

Patch9-11: Implement a new dirty log tracking method for vfio based on iommu hwdbm. A new
           ioctl operation named VFIO_DIRTY_LOG_MANUAL_CLEAR is added, which can eliminate
		   some redundant dirty handling of userspace.

Optimizations TO Do:

1. We recognized that each smmu_domain (a vfio_container may has several smmu_domain) has its
   own stage1 mapping, and we must scan all these mapping to sync dirty state. We plan to refactor
   smmu_domain to support more than one smmu in one smmu_domain, then these smmus can share a same
   stage1 mapping.
2. We also recognized that scan TTD is a hotspot of performance. Recently, I have implement a
   SW/HW conbined dirty log tracking at MMU side [1], which can effectively solve this problem.
   This idea can be applied to smmu side too.

Thanks,
Keqian


[1] https://lore.kernel.org/linux-arm-kernel/20210126124444.27136-1-zhukeqian1@huawei.com/

jiangkunkun (11):
  iommu/arm-smmu-v3: Add feature detection for HTTU
  iommu/arm-smmu-v3: Enable HTTU for SMMU stage1 mapping
  iommu/arm-smmu-v3: Add feature detection for BBML
  iommu/arm-smmu-v3: Split block descriptor to a span of page
  iommu/arm-smmu-v3: Merge a span of page to block descriptor
  iommu/arm-smmu-v3: Scan leaf TTD to sync hardware dirty log
  iommu/arm-smmu-v3: Clear dirty log according to bitmap
  iommu/arm-smmu-v3: Add HWDBM device feature reporting
  vfio/iommu_type1: Add HWDBM status maintanance
  vfio/iommu_type1: Optimize dirty bitmap population based on iommu
    HWDBM
  vfio/iommu_type1: Add support for manual dirty log clear

 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c | 138 ++++++-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.h |  14 +
 drivers/iommu/io-pgtable-arm.c              | 392 +++++++++++++++++++-
 drivers/iommu/iommu.c                       | 227 ++++++++++++
 drivers/vfio/vfio_iommu_type1.c             | 235 +++++++++++-
 include/linux/io-pgtable.h                  |  14 +
 include/linux/iommu.h                       |  55 +++
 include/uapi/linux/vfio.h                   |  28 +-
 8 files changed, 1093 insertions(+), 10 deletions(-)
```
#### [RFC v2 0/4] Introduce MMIO/PIO dispatch file descriptors
##### From: Elena Afanasova <eafanasova@gmail.com>

```c
From patchwork Thu Jan 28 18:32:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Elena Afanasova <eafanasova@gmail.com>
X-Patchwork-Id: 12054403
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ED297C433DB
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:47:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A506E64E24
	for <kvm@archiver.kernel.org>; Thu, 28 Jan 2021 18:47:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232478AbhA1Sqq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 28 Jan 2021 13:46:46 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41398 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232049AbhA1Sol (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 Jan 2021 13:44:41 -0500
Received: from mail-lf1-x12f.google.com (mail-lf1-x12f.google.com
 [IPv6:2a00:1450:4864:20::12f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id D4A24C061786
        for <kvm@vger.kernel.org>; Thu, 28 Jan 2021 10:43:38 -0800 (PST)
Received: by mail-lf1-x12f.google.com with SMTP id i187so8975370lfd.4
        for <kvm@vger.kernel.org>; Thu, 28 Jan 2021 10:43:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gc8IAD89ohU9L5g7XLURxoRD1ypfXHd9129BbRQE4Vs=;
        b=ly0bdMEC9l7y2KBWFcGiVcAm4730SBb/exane8VwuSf7eQEN/tBlFKgh1wWslPiPdK
         37ltxyiH2T8+xJU06Ml7stRxi/Ex0Ya1CRIMhlTPUmDefMX6EA+U4O2zM0XtfJeNazP4
         1jTTH4LDF2wlGm0ieYFE9gBRPnfSavbNX1aRvsYZ80O8gHKIr1jBPaCe13ZdxnxmsK4M
         ioEMNRgjKwGTHgabRVNeV6fOik1F5HWarOIEhDwyrzFe8+LgF2Fat/D3WxAl3iAejIHY
         zQasTFhpR1OEbcI/s8uUBqI9ND6/+Hzc2OwqOGl+2kd6jaU9Zuza2H1H3vrl7CbA9zkr
         tTtg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=gc8IAD89ohU9L5g7XLURxoRD1ypfXHd9129BbRQE4Vs=;
        b=skHXRej8m5CwUKXz8AAm9LM0fGAQGOK9QxYVFPyQ8Alepx7xnP6YDGLvuhwkADDAjv
         LJgujH2HqSLaEZYcRKY63au0ciWBJ0TzKh/eCwnljC+3gCOD4OkGgau2r6XW5E5yVJvr
         3BzYPr8L/TJWf7m8m4lAriZuVrTXhqLG1+Boqf5EiwuydiXIewDCAv6VUQeWr7KzJSBX
         W/mbNUvJLbrizE5pOMdikj7TxC5O+R4AsDNhyPIfKISBXhpvboT+ADs5eWJajAY1ZYGo
         2BZUts4/mgjxkJpCBuAqUEx9HjTolBG0rayUl46eqbc4ifNxuMbf+cttXP0Rl/JcwcGI
         lQpA==
X-Gm-Message-State: AOAM533MVMSKYKhpqvfKZLNzf+XamMw8OWYwbwwxiY4085QKD72gwg6Z
        JndqN4IVHEK3bYFMGWCpf5JC2jHKh9LBmO3b
X-Google-Smtp-Source: 
 ABdhPJyr3hRBvWiLHLwPZGsn20Yns45V20s3ATv9DHDKcLfdt8ruTttYEjs9s+8jtiV8wSCtcGevng==
X-Received: by 2002:a19:ed0a:: with SMTP id y10mr174986lfy.601.1611859416938;
        Thu, 28 Jan 2021 10:43:36 -0800 (PST)
Received: from localhost.localdomain (37-145-186-126.broadband.corbina.ru.
 [37.145.186.126])
        by smtp.gmail.com with ESMTPSA id
 k8sm1750508lfg.41.2021.01.28.10.43.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 28 Jan 2021 10:43:36 -0800 (PST)
From: Elena Afanasova <eafanasova@gmail.com>
To: kvm@vger.kernel.org
Cc: stefanha@redhat.com, jag.raman@oracle.com,
        elena.ufimtseva@oracle.com, Elena Afanasova <eafanasova@gmail.com>
Subject: [RFC v2 0/4] Introduce MMIO/PIO dispatch file descriptors
 (ioregionfd)
Date: Thu, 28 Jan 2021 21:32:19 +0300
Message-Id: <cover.1611850290.git.eafanasova@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset introduces a KVM dispatch mechanism which can be used 
for handling MMIO/PIO accesses over file descriptors without returning 
from ioctl(KVM_RUN). This allows device emulation to run in another task 
separate from the vCPU task.

This is achieved through KVM vm ioctl for registering MMIO/PIO regions and 
a wire protocol that KVM uses to communicate with a task handling an 
MMIO/PIO access.

TODOs:
* Implement KVM_EXIT_IOREGIONFD_FAILURE
* Add non-x86 arch support
* Add kvm-unittests

Elena Afanasova (4):
  KVM: add initial support for KVM_SET_IOREGION
  KVM: x86: add support for ioregionfd signal handling
  KVM: add support for ioregionfd cmds/replies serialization
  KVM: enforce NR_IOBUS_DEVS limit if kmemcg is disabled

 arch/x86/kvm/Kconfig          |   1 +
 arch/x86/kvm/Makefile         |   1 +
 arch/x86/kvm/x86.c            | 216 ++++++++++++++-
 include/kvm/iodev.h           |  14 +
 include/linux/kvm_host.h      |  34 +++
 include/uapi/linux/ioregion.h |  32 +++
 include/uapi/linux/kvm.h      |  23 ++
 virt/kvm/Kconfig              |   3 +
 virt/kvm/eventfd.c            |  25 ++
 virt/kvm/eventfd.h            |  14 +
 virt/kvm/ioregion.c           | 479 ++++++++++++++++++++++++++++++++++
 virt/kvm/ioregion.h           |  15 ++
 virt/kvm/kvm_main.c           |  68 ++++-
 13 files changed, 905 insertions(+), 20 deletions(-)
 create mode 100644 include/uapi/linux/ioregion.h
 create mode 100644 virt/kvm/eventfd.h
 create mode 100644 virt/kvm/ioregion.c
 create mode 100644 virt/kvm/ioregion.h
```
