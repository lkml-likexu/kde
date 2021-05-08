

#### [RFC PATCH v2 0/3] vfio/iommu_type1: Implement dirty log tracking
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri May  7 10:36:05 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12244355
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 67694C433ED
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 10:36:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 302206145D
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 10:36:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236940AbhEGKh5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 06:37:57 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:18009 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236915AbhEGKh4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 06:37:56 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Fc6HP36dszQkLN;
        Fri,  7 May 2021 18:33:37 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Fri, 7 May 2021 18:36:49 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>, <kvm@vger.kernel.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        "Cornelia Huck" <cohuck@redhat.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Tian Kevin <kevin.tian@intel.com>
CC: Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Will Deacon <will@kernel.org>, Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <yuzenghui@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 0/3] vfio/iommu_type1: Implement dirty log tracking
 based on IOMMU HWDBM
Date: Fri, 7 May 2021 18:36:05 +0800
Message-ID: <20210507103608.39440-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Alex and everyone,

This patch series implement vfio dma dirty log tracking based on IOMMU HWDBM (hardware
dirty bit management, such as SMMU with HTTU or intel IOMMU with SLADE).

This patch series is split from the series[1] that containes both IOMMU part and
VFIO part. Please refer the new IOMMU part v4[2] to review or test.

Changelog:

v2:
 - Use separate ioctl to get dirty log without clear it automatically. (Alex)
 - Implement based on new iommu dirty tracking framework.
 - Track hwdbm status at domain level.
 - Bugfix: When get_no_clear, we should recover dirty bitmap too.
 - Bugfix: When switch from full dirty policy to iommu hwdbm policy, we should populate full dirty.

Intention:

As we know, vfio live migration is an important and valuable feature, but there
are still many hurdles to solve, including migration of interrupt, device state,
DMA dirty log tracking, and etc.

For now, the only dirty log tracking interface is pinning. It has some drawbacks:
1. Only smart vendor drivers are aware of this.
2. It's coarse-grained, the pinned-scope is generally bigger than what the device actually access.
3. It can't track dirty continuously and precisely, vfio populates all pinned-scope as dirty.
   So it doesn't work well with iteratively dirty log handling.

About this series:

Implement a new dirty log tracking method for vfio based on iommu hwdbm. A new
ioctl operation named VFIO_DIRTY_LOG_MANUAL_CLEAR is added, which can eliminate
some redundant dirty handling of userspace.   
   
Optimizations Todo:

1. We recognized that each smmu_domain (a vfio_container may has several smmu_domain) has its
   own stage1 mapping, and we must scan all these mapping to sync dirty state. We plan to refactor
   smmu_domain to support more than one smmu in one smmu_domain, then these smmus can share a same
   stage1 mapping.
2. We also recognized that scan TTD is a hotspot of performance. Recently, I have implement a
   SW/HW conbined dirty log tracking at MMU side[3], which can effectively solve this problem.
   This idea can be applied to smmu side too.

Thanks,
Keqian

[1] https://lore.kernel.org/linux-iommu/20210310090614.26668-1-zhukeqian1@huawei.com/
[2] https://lore.kernel.org/linux-iommu/20210507102211.8836-1-zhukeqian1@huawei.com/ 
[3] https://lore.kernel.org/linux-arm-kernel/20210126124444.27136-1-zhukeqian1@huawei.com/


Kunkun Jiang (3):
  vfio/iommu_type1: Add HWDBM status maintenance
  vfio/iommu_type1: Optimize dirty bitmap population based on iommu
    HWDBM
  vfio/iommu_type1: Add support for manual dirty log clear

 drivers/vfio/vfio_iommu_type1.c | 315 ++++++++++++++++++++++++++++++--
 include/uapi/linux/vfio.h       |  36 +++-
 2 files changed, 337 insertions(+), 14 deletions(-)
```
#### [PATCH v5 0/2] kvm/arm64: Try stage2 block mapping for host device
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri May  7 11:03:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12244391
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AB854C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 11:04:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63DAC61460
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 11:04:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234314AbhEGLFr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 07:05:47 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:18791 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234061AbhEGLFq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 07:05:46 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4Fc6wJ5vdjzCqsL;
        Fri,  7 May 2021 19:02:08 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.498.0; Fri, 7 May 2021 19:04:37 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v5 0/2] kvm/arm64: Try stage2 block mapping for host device
 MMIO
Date: Fri, 7 May 2021 19:03:20 +0800
Message-ID: <20210507110322.23348-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Marc,

This rebases to newest mainline kernel.

Thanks,
Keqian


We have two pathes to build stage2 mapping for MMIO regions.

Create time's path and stage2 fault path.

Patch#1 removes the creation time's mapping of MMIO regions
Patch#2 tries stage2 block mapping for host device MMIO at fault path

Changelog:

v5:
 - Rebase to newest mainline.

v4:
 - use get_vma_page_shift() handle all cases. (Marc)
 - get rid of force_pte for device mapping. (Marc)

v3:
 - Do not need to check memslot boundary in device_rough_page_shift(). (Marc)


Keqian Zhu (2):
  kvm/arm64: Remove the creation time's mapping of MMIO regions
  kvm/arm64: Try stage2 block mapping for host device MMIO

 arch/arm64/kvm/mmu.c | 99 ++++++++++++++++++++++++--------------------
 1 file changed, 54 insertions(+), 45 deletions(-)
```
#### [patch 0/4] VMX: configure posted interrupt descriptor when assigning
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
From patchwork Fri May  7 13:06:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12244553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B7001C43461
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B7676145D
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 13:10:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236752AbhEGNLX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 09:11:23 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:39209 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S236467AbhEGNLV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 09:11:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620393021;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=TiiXf73jHYHnfY5U8cMctn8gIsgl068QB1DFfjUXLNk=;
        b=fIOLBCI1ZqMG/ty+eVC6gZpwbPM9dX0TalRunHb0yEqR1i8Sfjys/DB7DjV83ptNeI9zAp
        8XFjB6ELee6OGLWA+8l/k/4TfF1mu8oxpVmZ6ZhOT7/32xuGm07ZL6zHjU1R0+KV3zOv3r
        E/9N64sjcw6+cHdVoH78+pX1gMqPRm0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-281-GhpPj_GOM6q8t_xXBO6NaA-1; Fri, 07 May 2021 09:10:18 -0400
X-MC-Unique: GhpPj_GOM6q8t_xXBO6NaA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CA2021898297;
        Fri,  7 May 2021 13:10:17 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id CA83A60918;
        Fri,  7 May 2021 13:10:12 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 9CE6F41887F4; Fri,  7 May 2021 10:10:07 -0300 (-03)
Message-ID: <20210507130609.269153197@redhat.com>
User-Agent: quilt/0.66
Date: Fri, 07 May 2021 10:06:09 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [patch 0/4] VMX: configure posted interrupt descriptor when assigning
 device
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Configuration of the posted interrupt descriptor is incorrect when devices
are hotplugged to the guest (and vcpus are halted).

See patch 4 for details.
---

v2: rather than using a potentially racy IPI (vs vcpu->cpu switches),
    kick the vcpus when assigning a device and let the blocked per-CPU
    list manipulation happen locally at ->pre_block and ->post_block
    (Sean Christopherson).
```
#### [PATCH 0/2] KVM: x86: Fixes for SEV-ES state tracking
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Fri May  7 16:59:45 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12244963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89B25C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:59:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4340E61464
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 16:59:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S238455AbhEGRAy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 13:00:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:33612 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236776AbhEGRAx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 7 May 2021 13:00:53 -0400
Received: from mail-qv1-xf49.google.com (mail-qv1-xf49.google.com
 [IPv6:2607:f8b0:4864:20::f49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7DE64C061761
        for <kvm@vger.kernel.org>; Fri,  7 May 2021 09:59:53 -0700 (PDT)
Received: by mail-qv1-xf49.google.com with SMTP id
 a18-20020a0cca920000b02901d3c6996bb7so7093655qvk.6
        for <kvm@vger.kernel.org>; Fri, 07 May 2021 09:59:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=uGowWnX27OFq3X1gHuwjZTbUlKh4i8rvEkAnK10zYZE=;
        b=mnSStCy9NenGQ9//ObWsCgKQmNe7czVPdK7QhmoAJFZ7H/LYAa9AmCI99Q39bNSwzm
         wMCb0nAcQ/xgUJG/nSE0lqXCIni649ugapCTs6DEpVto8egto6V4nJXrw3Bk7FdEP4uz
         Lqo5yLB9lAo2KL2sAlNj5hvyWdOmkzxc1RTdayzCz1YQvt/sIuTFwwA3yuKFiK7DxBqh
         bzyCKol8nGb397q/Y5yz0m1nwvt+n2jeqfY/g751BFIEbuu5IZwoJ5ExXwAE1TxARvUK
         JOfclvETVaGiKMmizl6qxTkLLlGGoaPxEg1FOFobvWqX4EOY17u1i+OEioDZnBI3/y4E
         lmcQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=uGowWnX27OFq3X1gHuwjZTbUlKh4i8rvEkAnK10zYZE=;
        b=Hpm8d6pv60E0pCTnpBGRTJhosZHQyj9fhMZXwTx3CPxJdkwO01Qu4w2I+Kzhsq1TY1
         trkTNQm8J8SJYXMrUIf8BMZ8RRrypFLjW7yiloqwzSbRPhUweqv+3f2v4AaUuMOYd7JX
         xNYgML04f8XjgTpuwwjN8S5sg9A/zItLmvgltl612HbwKVvxSEndC9lIuhXcq/J/dz7X
         Z7FoXFqlqL+Xu4TnTopJ8CbUHW85UAjrR1l0i40CtGbDbnwgl0csFDNuVFiXopT2cGPW
         QzSpeqDZem/MnY/k+UQGDR9VBN6tyori+oPOBvU0OQqOgctBEPYe3whvkf6Dj6n0nb9W
         ifPQ==
X-Gm-Message-State: AOAM533LdagHfNwx1nRByMdalH4KWQGsKSyJDYlv+i2XMT3jTB86o1vv
        P3jqorSaaKwNdmHiyoWAGKBS1bOQ4uw=
X-Google-Smtp-Source: 
 ABdhPJxFM635GyWiSG/BnziS1EI1yIDc1gHO1U+htrLY1MFsVNaVy0Dc2UGxrhy5kab0tvrOWUBR6geOiUU=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:7352:5279:7518:418f])
 (user=seanjc job=sendgmr) by 2002:a0c:bd13:: with SMTP id
 m19mr10783603qvg.29.1620406792652;
 Fri, 07 May 2021 09:59:52 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Fri,  7 May 2021 09:59:45 -0700
Message-Id: <20210507165947.2502412-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH 0/2] KVM: x86: Fixes for SEV-ES state tracking
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Peter Gonda <pgonda@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For SEV-ES guests, Ensure KVM's model of EFER is up-to-date after a CR0
load, and let userspace set tracked state via KVM_SET_SREGS, relying on
the vendor code to not propagate the changes to hardware (VMCB in this
case).

Peter, patch 02 is different than what I sent to you off list.  I'm still
100% convinced that the load_pdptrs() call is flawed, but Maxim has an
in-progress series that's tackling the PDPTR save/restore mess.

Sean Christopherson (2):
  KVM: SVM: Update EFER software model on CR0 trap for SEV-ES
  KVM: x86: Allow userspace to update tracked sregs for protected guests

 arch/x86/kvm/svm/svm.c |  8 +++--
 arch/x86/kvm/x86.c     | 73 ++++++++++++++++++++++++------------------
 2 files changed, 47 insertions(+), 34 deletions(-)
```
#### [PATCH 0/6]  KVM: arm64: selftests: Fix get-reg-list
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Fri May  7 20:04:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12245165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 02388C433B4
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 20:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C2C096144F
	for <kvm@archiver.kernel.org>; Fri,  7 May 2021 20:04:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230034AbhEGUFa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 7 May 2021 16:05:30 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:23871 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229905AbhEGUF1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 7 May 2021 16:05:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620417867;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=UIav5HVsnw8DaGW40BBfIS/nkjpuzktpcWTdxzNgE2Q=;
        b=DHrTMGwVdNzkTDwX9mTmrYqYCkbw4ZKfz8Ot1/GXXCCvrQrbGdKYshSCXxoo1yw2tksCSM
        +RIv3EFcCGDj3r7839eH4ZWgW1ZabTB7ICv9fAkhxk3wT1qTvynRc6MA2iuv/A3hyWRl35
        Yil37u5/LhXBtpu2tmNZlmm/wXfJpnw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-239-EJE1MZTGO6uU2r0tF88VGg-1; Fri, 07 May 2021 16:04:26 -0400
X-MC-Unique: EJE1MZTGO6uU2r0tF88VGg-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5BD371854E21;
        Fri,  7 May 2021 20:04:24 +0000 (UTC)
Received: from gator.home (unknown [10.40.192.135])
        by smtp.corp.redhat.com (Postfix) with ESMTP id DB40119D61;
        Fri,  7 May 2021 20:04:17 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: maz@kernel.org, ricarkol@google.com, eric.auger@redhat.com,
        alexandru.elisei@arm.com, pbonzini@redhat.com
Subject: [PATCH 0/6]  KVM: arm64: selftests: Fix get-reg-list
Date: Fri,  7 May 2021 22:04:10 +0200
Message-Id: <20210507200416.198055-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Since KVM commit 11663111cd49 ("KVM: arm64: Hide PMU registers from
userspace when not available") the get-reg-list* tests have been
failing with

  ...
  ... There are 74 missing registers.
  The following lines are missing registers:
  ...

where the 74 missing registers are all PMU registers. This isn't a
bug in KVM that the selftest found, even though it's true that a
KVM userspace that wasn't setting the KVM_ARM_VCPU_PMU_V3 VCPU
flag, but still expecting the PMU registers to be in the reg-list,
would suddenly no longer have their expectations met. In that case,
the expectations were wrong, though, so that KVM userspace needs to
be fixed, and so does this selftest.

We could fix the test with a one-liner since we just need a

  init->features[0] |= 1 << KVM_ARM_VCPU_PMU_V3;

in prepare_vcpu_init(), but that's too easy, so here's a 6 patch patch
series instead :-)  The reason for all the patches and the heavy diffstat
is to prepare for other vcpu configuration testing, e.g. ptrauth and mte.
With the refactoring done in this series, we should now be able to easily
add register sublists and vcpu configs to the get-reg-list test, as the
last patch demonstrates with the pmu fix.

Thanks,
drew


Andrew Jones (6):
  KVM: arm64: selftests: get-reg-list: Factor out printing
  KVM: arm64: selftests: get-reg-list: Introduce vcpu configs
  KVM: arm64: selftests: get-reg-list: Prepare to run multiple configs
    at once
  KVM: arm64: selftests: get-reg-list: Provide config selection option
  KVM: arm64: selftests: get-reg-list: Remove get-reg-list-sve
  KVM: arm64: selftests: get-reg-list: Split base and pmu registers

 tools/testing/selftests/kvm/.gitignore        |   1 -
 tools/testing/selftests/kvm/Makefile          |   1 -
 .../selftests/kvm/aarch64/get-reg-list-sve.c  |   3 -
 .../selftests/kvm/aarch64/get-reg-list.c      | 442 +++++++++++++-----
 4 files changed, 313 insertions(+), 134 deletions(-)
 delete mode 100644 tools/testing/selftests/kvm/aarch64/get-reg-list-sve.c
```
