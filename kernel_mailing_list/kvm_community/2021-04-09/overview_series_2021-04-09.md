#### [RFC PATCH v3 1/8] iommu: Evolve the device fault reporting framework
##### From: Shenming Lu <lushenming@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12192933
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4A1BDC433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:44:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13FFF61042
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:44:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233233AbhDIDo4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 23:44:56 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:15638 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232941AbhDIDoz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 23:44:55 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4FGkTF2QDmznZ7g;
        Fri,  9 Apr 2021 11:41:53 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Fri, 9 Apr 2021 11:44:33 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Eric Auger <eric.auger@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <linux-api@vger.kernel.org>
CC: Kevin Tian <kevin.tian@intel.com>,
        Lu Baolu <baolu.lu@linux.intel.com>, <yi.l.liu@intel.com>,
        Christoph Hellwig <hch@infradead.org>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Barry Song <song.bao.hua@hisilicon.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [RFC PATCH v3 1/8] iommu: Evolve the device fault reporting framework
Date: Fri, 9 Apr 2021 11:44:13 +0800
Message-ID: <20210409034420.1799-2-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
In-Reply-To: <20210409034420.1799-1-lushenming@huawei.com>
References: <20210409034420.1799-1-lushenming@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch follows the discussion here:

https://lore.kernel.org/linux-acpi/YAaxjmJW+ZMvrhac@myrica/

Besides SVA/vSVA, such as VFIO may also enable (2nd level) IOPF to remove
pinning restriction. In order to better support more scenarios of using
device faults, we extend iommu_register_fault_handler() with flags and
introduce FAULT_REPORT_ to describe the device fault reporting capability
under a specific configuration.

Note that we don't further distinguish recoverable and unrecoverable faults
by flags in the fault reporting cap, having PAGE_FAULT_REPORT_ +
UNRECOV_FAULT_REPORT_ seems not a clean way.

In addition, still take VFIO as an example, in nested mode, the 1st level
and 2nd level fault reporting may be configured separately and currently
each device can only register one iommu dev fault handler, so we add a
handler update interface for this.

Signed-off-by: Shenming Lu <lushenming@huawei.com>
---
 .../iommu/arm/arm-smmu-v3/arm-smmu-v3-sva.c   |  3 +-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c   | 18 ++++--
 drivers/iommu/iommu.c                         | 56 ++++++++++++++++++-
 include/linux/iommu.h                         | 19 ++++++-
 include/uapi/linux/iommu.h                    |  4 ++
 5 files changed, 90 insertions(+), 10 deletions(-)

```
#### [PATCH v5 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12193165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C453C43470
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 06:32:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46C5961179
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 06:32:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233417AbhDIGcS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 02:32:18 -0400
Received: from mga12.intel.com ([192.55.52.136]:32004 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231540AbhDIGcO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 02:32:14 -0400
IronPort-SDR: 
 hP7gFGqUVH58SYo4ZY3hC5BPX0H9QN8TPVTykCvQK8VEGLqHwyD87cP1dQRh4uLGJEtUDuMhE1
 CwJ9R8cH0PUA==
X-IronPort-AV: E=McAfee;i="6000,8403,9948"; a="173178633"
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="173178633"
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Apr 2021 23:31:28 -0700
IronPort-SDR: 
 P626zOnQb/jlEwz9PPcruxNNAnXgmuZhIMZMa1mZ7OmwtLuQREleq5Tetr4nWPIqDlijoENy4p
 mAWMoGjVHLPQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="380538728"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by orsmga003.jf.intel.com with ESMTP; 08 Apr 2021 23:31:26 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, seanjc@google.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v5 1/3] KVM: nVMX: Sync L2 guest CET states between L1/L2
Date: Fri,  9 Apr 2021 14:43:43 +0800
Message-Id: <20210409064345.31497-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20210409064345.31497-1-weijiang.yang@intel.com>
References: <20210409064345.31497-1-weijiang.yang@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

These fields are rarely updated by L1 QEMU/KVM, sync them when L1 is trying to
read/write them and after they're changed. If CET guest entry-load bit is not
set by L1 guest, migrate them to L2 manaully.

Opportunistically remove one blank line in previous patch.

Suggested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/kvm/cpuid.c      |  1 -
 arch/x86/kvm/vmx/nested.c | 30 ++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h    |  3 +++
 3 files changed, 33 insertions(+), 1 deletion(-)

```
#### [PATCH v3 5/8] docs: vcpu-requests.rst: fix reference for atomic ops
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12194081
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 92555C433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:48:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F4B161177
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:48:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233889AbhDIMsU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 08:48:20 -0400
Received: from mail.kernel.org ([198.145.29.99]:41836 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233569AbhDIMsP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 08:48:15 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id 6597D61178;
        Fri,  9 Apr 2021 12:48:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1617972481;
        bh=01jspTSWm7bLXEJy5cH57gxxdERvRXGSivEgicYhRac=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=dZnLzeh6l2g55cfYuzcG0DE0SLCajN0/Smc4h48GvGkxjCFxGCJb8AJfQJ3uoe3aS
         xddL7oE+1ApayJWqIGO76K/TTaQn6z7ToaccPknhLbpWpGLklbEgpiXmYIAgk8Zus0
         vGt2RcZCAbiErPqPNrnUrLNT29+gpJgwkVUGP3uuPXSMHo3Dew9an6yo3+EBQWncqE
         jXqeUiWf8Zs8Kk4Fu2hP0OOloofBopVDFVATqg+Dr6L5munEgZ3zMejAo6vIAHcTGW
         4woxFkqE5p96KxDxy/r/OnafHiBM2ncjqzZpZtiN65/BhwHmwFNnxlOBqUfO0qDuuf
         ejyEZNj9oFGsw==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1lUqYE-001SLo-AU; Fri, 09 Apr 2021 14:47:54 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Peter Zijlstra <peterz@infradead.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 5/8] docs: vcpu-requests.rst: fix reference for atomic ops
Date: Fri,  9 Apr 2021 14:47:49 +0200
Message-Id: 
 <fc194806772325d60b7406368ba726f07990b968.1617972339.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1617972339.git.mchehab+huawei@kernel.org>
References: <cover.1617972339.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changeset f0400a77ebdc ("atomic: Delete obsolete documentation")
got rid of atomic_ops.rst, pointing that this was superseded by
Documentation/atomic_*.txt.

Update its reference accordingly.

Fixes: f0400a77ebdc ("atomic: Delete obsolete documentation")
Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/vcpu-requests.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] vdpa/mlx5: last minute fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 12194579
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-25.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 85BFBC433B4
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 16:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51902610CA
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 16:48:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232642AbhDIQsg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 12:48:36 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:52093 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232395AbhDIQsf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 9 Apr 2021 12:48:35 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617986902;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=Chg6IKEuKKojYi7mhUKaMLERMRmxIjzmO/LXSZ+TUHU=;
        b=WE8yyCMnzFRiUCyrXjQmd2y/SFQuk0410KgVwtGc2o4yLRUDXkWPdp/1KlU6ZQaszgf3U1
        utOzKT35fHqb6IG91aMysACGLbVR3/YTePzUez1gCJGcpW7KzASAQw0K/eLrjiumxNGd39
        QMEQcqh4U0AEb6WU8b85bbzYlPMxHGw=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-264-NJ1MqecbMmuydVBFRpmMOw-1; Fri, 09 Apr 2021 12:48:20 -0400
X-MC-Unique: NJ1MqecbMmuydVBFRpmMOw-1
Received: by mail-wm1-f72.google.com with SMTP id
 b20-20020a7bc2540000b029010f7732a35fso4487998wmj.1
        for <kvm@vger.kernel.org>; Fri, 09 Apr 2021 09:48:20 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=Chg6IKEuKKojYi7mhUKaMLERMRmxIjzmO/LXSZ+TUHU=;
        b=sC789iOOoFUn8OkHGpfGGZECIAM4hvYaEhe/R7YKDH1Sye2bDDOP1iWh1+OVSEvbka
         lsIhXjbT5l/qKLQiKgdrzfSuhiftFLzKpCtDFaqawu2hkC0PC/i5yESYN+9uKfW+bafi
         /Y0YUXGlJXLhcejuqKDaES0+5XkzCYyLkv3HKJvM4dI2er2NAOzcJwV5/6/d1g0AXqac
         T29S618h4zrpXcObrngwf+qDAAotMLgDTYxyvxbIzITU5F+62ahg95yxJuSXunVBKBGk
         PlWc6Cwusuj4ayQdgjxLy/zcEYpBwT12/yLx2ZLaRKUEpLD6wOfQARebMVPtH+5B/68v
         KauQ==
X-Gm-Message-State: AOAM530X0hckLe8ajciLo6Qk1rJ2mXzKjNCMLZ4MPMGV29BHejwXkz/I
        QPLRcpaePFMoE7oszkU1NhnwL6P1JYa4MaxJogGSyuMpM3d6CZYWuG1UjeUDbB0lqxQxnbtaVSf
        FWzm56K3h/oUZ
X-Received: by 2002:a1c:9a16:: with SMTP id c22mr7681449wme.7.1617986899514;
        Fri, 09 Apr 2021 09:48:19 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJw2SClI5Njn6xjA2MPYxm2kpYJCEchwrX/9+aQChXy3FOe+I3afHnDGXz6jYj0V+5m4e1Tm6w==
X-Received: by 2002:a1c:9a16:: with SMTP id c22mr7681431wme.7.1617986899273;
        Fri, 09 Apr 2021 09:48:19 -0700 (PDT)
Received: from redhat.com ([2a10:800e:f0d3:0:b69b:9fb8:3947:5636])
        by smtp.gmail.com with ESMTPSA id
 o25sm6618101wmh.1.2021.04.09.09.48.17
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 09 Apr 2021 09:48:18 -0700 (PDT)
Date: Fri, 9 Apr 2021 12:48:16 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, linux-kernel@vger.kernel.org,
        elic@nvidia.com, jasowang@redhat.com, mst@redhat.com,
        si-wei.liu@oracle.com
Subject: [GIT PULL] vdpa/mlx5: last minute fixes
Message-ID: <20210409124816-mutt-send-email-mst@kernel.org>
MIME-Version: 1.0
Content-Disposition: inline
X-Mutt-Fcc: =sent
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following changes since commit e49d033bddf5b565044e2abe4241353959bc9120:

  Linux 5.12-rc6 (2021-04-04 14:15:36 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to bc04d93ea30a0a8eb2a2648b848cef35d1f6f798:

  vdpa/mlx5: Fix suspend/resume index restoration (2021-04-09 12:08:28 -0400)

----------------------------------------------------------------
vdpa/mlx5: last minute fixes

These all look like something we are better off having
than not ...

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Eli Cohen (4):
      vdpa/mlx5: Use the correct dma device when registering memory
      vdpa/mlx5: Retrieve BAR address suitable any function
      vdpa/mlx5: Fix wrong use of bit numbers
      vdpa/mlx5: Fix suspend/resume index restoration

Si-Wei Liu (1):
      vdpa/mlx5: should exclude header length and fcs from mtu

 drivers/vdpa/mlx5/core/mlx5_vdpa.h |  4 ++++
 drivers/vdpa/mlx5/core/mr.c        |  9 +++++++--
 drivers/vdpa/mlx5/core/resources.c |  3 ++-
 drivers/vdpa/mlx5/net/mlx5_vnet.c  | 40 +++++++++++++++++++++++---------------
 4 files changed, 37 insertions(+), 19 deletions(-)
```
#### [PATCH v4 1/2] KVM: arm64: Move CMOs from user_mem_abort to the fault handlers
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "wangyanan (Y)" <wangyanan55@huawei.com>
X-Patchwork-Id: 12192915
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93949C43460
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:38:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6D00961055
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 03:38:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233253AbhDIDiP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 23:38:15 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:16855 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233187AbhDIDiL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 23:38:11 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4FGkK51gGJz9xh4;
        Fri,  9 Apr 2021 11:34:49 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Fri, 9 Apr 2021 11:36:56 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Alexandru Elisei" <alexandru.elisei@arm.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v4 1/2] KVM: arm64: Move CMOs from user_mem_abort to the fault
 handlers
Date: Fri, 9 Apr 2021 11:36:51 +0800
Message-ID: <20210409033652.28316-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210409033652.28316-1-wangyanan55@huawei.com>
References: <20210409033652.28316-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We currently uniformly permorm CMOs of D-cache and I-cache in function
user_mem_abort before calling the fault handlers. If we get concurrent
guest faults(e.g. translation faults, permission faults) or some really
unnecessary guest faults caused by BBM, CMOs for the first vcpu are
necessary while the others later are not.

By moving CMOs to the fault handlers, we can easily identify conditions
where they are really needed and avoid the unnecessary ones. As it's a
time consuming process to perform CMOs especially when flushing a block
range, so this solution reduces much load of kvm and improve efficiency
of the page table code.

So let's move both clean of D-cache and invalidation of I-cache to the
map path and move only invalidation of I-cache to the permission path.
Since the original APIs for CMOs in mmu.c are only called in function
user_mem_abort, we now also move them to pgtable.c.

Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 31 ---------------
 arch/arm64/kvm/hyp/pgtable.c     | 68 +++++++++++++++++++++++++-------
 arch/arm64/kvm/mmu.c             | 23 ++---------
 3 files changed, 57 insertions(+), 65 deletions(-)

```
#### [PATCH v5 1/4] KVM: x86: Fix a spurious -E2BIG in KVM_GET_EMULATED_CPUID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12194127
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 11F8CC433B4
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:54:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E412F610E7
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 12:54:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233761AbhDIMyz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 08:54:55 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:53329 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233661AbhDIMyu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 9 Apr 2021 08:54:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617972877;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=UfpT86W/kEtT88MSCqogRvPyj1+EA4SWpFGICPB4Fvc=;
        b=YZXFgU/dhA71Ukfr7pnyKYHURWJ++DZcxPt0FZbH+oW2aiAZWY9rlQ6+ER+0iOLk/+EF9j
        5HN9i9WdzB0DLkiKDWWpw0Rsu1EbVxg4Ru3v7wQclWXGpyu350a/Y/XQXyKnTNITDzExa3
        Spg9DD+Z49gytSr1ecKqO0itMoMqg4A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-380-hXj-E_vrPeukmuGH_-0BBA-1; Fri, 09 Apr 2021 08:54:35 -0400
X-MC-Unique: hXj-E_vrPeukmuGH_-0BBA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E3B126D4EE;
        Fri,  9 Apr 2021 12:54:33 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-61.ams2.redhat.com
 [10.36.114.61])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EB1F810013C1;
        Fri,  9 Apr 2021 12:54:29 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH v5 1/4] KVM: x86: Fix a spurious -E2BIG in
 KVM_GET_EMULATED_CPUID
Date: Fri,  9 Apr 2021 14:54:20 +0200
Message-Id: <20210409125423.26288-2-eesposit@redhat.com>
In-Reply-To: <20210409125423.26288-1-eesposit@redhat.com>
References: <20210409125423.26288-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When retrieving emulated CPUID entries, check for an insufficient array
size if and only if KVM is actually inserting an entry.
If userspace has a priori knowledge of the exact array size,
KVM_GET_EMULATED_CPUID will incorrectly fail due to effectively requiring
an extra, unused entry.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
Fixes: 433f4ba19041 ("KVM: x86: fix out-of-bounds write in KVM_GET_EMULATED_CPUID (CVE-2019-19332)")
Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 arch/x86/kvm/cpuid.c | 33 ++++++++++++++++-----------------
 1 file changed, 16 insertions(+), 17 deletions(-)

```
#### [PATCH] [kvm-unit-tests PATCH] x86/access: Fix intermittent test failure
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 12193215
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4AE69C433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 07:43:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16845610C7
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 07:43:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231950AbhDIHnR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 03:43:17 -0400
Received: from mga04.intel.com ([192.55.52.120]:30006 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229751AbhDIHnR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 03:43:17 -0400
IronPort-SDR: 
 RcEna5pu8xMIp21wMNJ/mHFn77sWn44h0N8q2S/Z0IErMaVyORr5uU4BEJ7QyAHYhjOj0T1x0A
 hRsQDxIrkPig==
X-IronPort-AV: E=McAfee;i="6000,8403,9948"; a="191560039"
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="191560039"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Apr 2021 00:43:05 -0700
IronPort-SDR: 
 jAS780YL7WolSpmM2cAADVzf3M3ZmGn94XGB6Smo+hTMF8fFnTiBCOdOWC0l6u6OCQYHfazZJD
 0nbuHAJv3Z5g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,208,1613462400";
   d="scan'208";a="450104302"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.166])
  by fmsmga002.fm.intel.com with ESMTP; 09 Apr 2021 00:43:03 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH] [kvm-unit-tests PATCH] x86/access: Fix intermittent test
 failure
Date: Fri,  9 Apr 2021 15:55:18 +0800
Message-Id: <20210409075518.32065-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

During kvm-unit-test, below failure pattern is observed, this is due to testing thread
migration + cache "lazy" flush during test, so forcely flush the cache to avoid the issue.
Pin the test app to certain physical CPU can fix the issue as well. The error report is
misleading, pke is the victim of the issue.

test user cr4.pke: FAIL: error code 5 expected 4
Dump mapping: address: 0x123400000000
------L4: 21ea007
------L3: 21eb007
------L2: 21ec000
------L1: 2000000

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 x86/access.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v2 1/3] x86/kvm: Don't bother __pv_cpu_mask when !CONFIG_SMP
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12193003
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1838C433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 04:18:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7ED561026
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 04:18:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230118AbhDIESy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 00:18:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35534 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229526AbhDIESy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 00:18:54 -0400
Received: from mail-pj1-x1033.google.com (mail-pj1-x1033.google.com
 [IPv6:2607:f8b0:4864:20::1033])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 783E3C061760;
        Thu,  8 Apr 2021 21:18:42 -0700 (PDT)
Received: by mail-pj1-x1033.google.com with SMTP id i4so2259215pjk.1;
        Thu, 08 Apr 2021 21:18:42 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=Gd+gXcz6Jd6OEHUz9h21bPRreafNfkInMEF4YPsbOpk=;
        b=tefdWYpWO2XnAMMkeY/iwlwssVIS8QxEFUzgz5cgjuzgTa71RZuaRnkw6Ut8ArDbyt
         vDNQsQgqr3DIjUSZO6EfCN7beVAnJVrK9U+hlpT6YjmgOcs84zwx0bdl64ZbUg/9Dc7o
         Z733MXUGKLVBoLTrLPzWC5ZcJaPAw3fjuEdR7MrVOMS6t3oDGNH5vu9kcntpfYSZAFph
         RA/3iUXqQse83yjjcQ684JF+a0fhcRKpF7zMTgtUIqVQSobgttedo1xpusc1zPgXbfNA
         VBD4ecS7hAqyFryS25kHF0+mN8gbWKf9m4KtgMEZRXkrV+xr8ndqzxA/NYMfEuNbrLyh
         cWnA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=Gd+gXcz6Jd6OEHUz9h21bPRreafNfkInMEF4YPsbOpk=;
        b=Mb2s8ABvf6IUYFbVa5uq/3+rjIcsA2+1Jl79Go+6MrH6641uBdbjK/IwAXLd+xA83v
         nG1HLhEudgQEuXdrlWb0UUgYY+TTwUzfZcOdmx+o/y0FOvKQqfWf5GxYv1yRWh7t7gIu
         RjPwT3GBBUSbgcXFabDb3K5K2HWo2FeJGmY5JwJdbwNnJOlLwxa1VrYtzDp/SZLqNVYw
         Q5asMZejogj9RDJLVYQ48Zo3E3uDEI97uzQ9Zw+qG/qYumyfCoqIcTflF7pN/Gj04CNK
         kZoPxNLM0gB3fjPbBy91St3eVdTRKCW6x36Lgo9o4Imsp1o/grlq6zzJ9NKEMFoYbHed
         uzAg==
X-Gm-Message-State: AOAM531NDu+g+X63yWv3eq38AmOYyQYoSVXm9oP7TDD6Ia5InH8NbVf/
        xUcVEA18tanPK3CSG8QooYWA97qXjuo=
X-Google-Smtp-Source: 
 ABdhPJyYC5We5GOGs227qlbjCUawiRAdPZfMPTKKs2CTtjRaW/csMkfeTbEps/Ol1v0ogr1/E98Fpg==
X-Received: by 2002:a17:90a:5889:: with SMTP id
 j9mr12376248pji.69.1617941921712;
        Thu, 08 Apr 2021 21:18:41 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 gw24sm765553pjb.42.2021.04.08.21.18.39
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 08 Apr 2021 21:18:41 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v2 1/3] x86/kvm: Don't bother __pv_cpu_mask when !CONFIG_SMP
Date: Fri,  9 Apr 2021 12:18:29 +0800
Message-Id: <1617941911-5338-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Enable PV TLB shootdown when !CONFIG_SMP doesn't make sense. Let's 
move it inside CONFIG_SMP. In addition, we can avoid define and 
alloc __pv_cpu_mask when !CONFIG_SMP and get rid of 'alloc' variable 
in kvm_alloc_cpumask.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * shuffle things around a bit more

 arch/x86/kernel/kvm.c | 118 +++++++++++++++++++++++---------------------------
 1 file changed, 55 insertions(+), 63 deletions(-)

```
#### [PATCH v2] KVM: arm64: Fully zero the vcpu state on reset
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12194599
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D75EC433B4
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 17:33:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4583F6115B
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 17:33:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234330AbhDIRdS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 13:33:18 -0400
Received: from mail.kernel.org ([198.145.29.99]:38916 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234268AbhDIRdR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 13:33:17 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 94D8B6103E;
        Fri,  9 Apr 2021 17:33:04 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lUv0A-006ahk-HY; Fri, 09 Apr 2021 18:33:02 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Will Deacon <will@kernel.org>, kernel-team@android.com,
        stable@vger.kernel.org
Subject: [PATCH v2] KVM: arm64: Fully zero the vcpu state on reset
Date: Fri,  9 Apr 2021 18:32:57 +0100
Message-Id: <20210409173257.3031729-1-maz@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, will@kernel.org, kernel-team@android.com,
 stable@vger.kernel.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On vcpu reset, we expect all the registers to be brought back
to their initial state, which happens to be a bunch of zeroes.

However, some recent commit broke this, and is now leaving a bunch
of registers (such as the FP state) with whatever was left by the
guest. My bad.

Zero the reset of the state (32bit SPSRs and FPSIMD state).

Cc: stable@vger.kernel.org
Fixes: e47c2055c68e ("KVM: arm64: Make struct kvm_regs userspace-only")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---

Notes:
    v2: Only reset the FPSIMD state and the AArch32 SPSRs to avoid
    corrupting CNTVOFF in creative ways.

 arch/arm64/kvm/reset.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v2] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL commandFrom: Steve Rutherford <srutherford@google.com>
##### From: Steve Rutherford <srutherford@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steve Rutherford <srutherford@google.com>
X-Patchwork-Id: 12195131
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 756B6C433ED
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 22:08:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D3BB610A8
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 22:08:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234913AbhDIWIM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 18:08:12 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44328 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234798AbhDIWIK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 18:08:10 -0400
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3B20DC061763
        for <kvm@vger.kernel.org>; Fri,  9 Apr 2021 15:07:57 -0700 (PDT)
Received: by mail-qv1-xf4a.google.com with SMTP id bx8so4055266qvb.13
        for <kvm@vger.kernel.org>; Fri, 09 Apr 2021 15:07:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=2u0vXKObH3WGsffrNc9fPTVMDfChsBE9GCCsg/H8M68=;
        b=h/Tv8qqDFL0pawJZIOb3zQlQ+7bPo0b1mvHp3yydhAiEGDHgHeLfG3sISim9bRhCSZ
         hC5kLVMVEI2utZ4r+80y7gj+fchkXW3uIQfYa8i+JKXTWL8vF0j0bYufSs9qmykwvWVV
         3Tp1xRn3GEGBNYGyAf5wY79iWL3x9pdNVfqPq7gvzU0EuPEHX3ilmxgqFQ8DhsQ5yJqc
         4IY3nF3mcXHMQl6kl8SlNQK+JoyPhZbHHdjPbVQ8X2P3EjefEmtGLJwmAOXRAQT0AhgT
         ardAIyqTNmu9AOsOLdD72UMBSpKK99aT3KCfFhzpBht6tCR88Ic3hXhxu83lb0iFcLv3
         bgDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=2u0vXKObH3WGsffrNc9fPTVMDfChsBE9GCCsg/H8M68=;
        b=EPpC3NCPz4qYn8VMukxAyStbefo3lH411C0Ddux4agJ1iBuA3wRmogTZa2rxR+TnnP
         utO6KJm5riG2RUNBbCZWELyQepzZg8Cb1EKwWgkuHY2COQJzLDhqVu3viXKmkH0Ho/oB
         2v/1W1HLdyqOx5VBxEcQmobelu/PbuFfqWpdaDCl4VfzJEF4jUh/2/i9Ba6hiTSAwBey
         yEhFEB+eFNlcMPzBN31ek8Uyiq4002AuLv1A7MZbbVWwt5UNNkQLwR9ZFJ2DLsCANuGl
         +WIY2nM3C+7TW7dZAs3Rwy/+c9UFNzsQZHqvhu9TwFZ14z84QKJ5HVwvSs9aHmkgyVQW
         7Baw==
X-Gm-Message-State: AOAM531ooUGQ0+aVeQwTvR2OVJGDjmO1euB2Ndi9juNnrePBikbZvZX+
        5gmuSRT5cy90/1i7obP/Z+b0g4Le7xIf52wLiOYRQKYBSinIw0EjWGkhhsgm5C1pBikppzuqg9Y
        B3cEM3NdVE8ZJOkKYU6lj1gTQ106nvm1hqT08/1naLPe6R6WQ4Er5X32L51cwr3IYH2GvSOw=
X-Google-Smtp-Source: 
 ABdhPJwfHO47VlmafTdDfP3AuOncr1qecCve2z/OzMFX/Cn3ARCJoUDeda7GIgCjRlVw6UKUOtKqHc8TiPrAi/TrWw==
X-Received: from riemann.sea.corp.google.com
 ([2620:15c:158:202:a8f5:15cf:e225:5433])
 (user=srutherford job=sendgmr) by 2002:ad4:4c83:: with SMTP id
 bs3mr16388203qvb.41.1618006076216; Fri, 09 Apr 2021 15:07:56 -0700 (PDT)
Date: Fri,  9 Apr 2021 15:07:50 -0700
Message-Id: <20210409220750.1972030-1-srutherford@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH v2] KVM: SVM: Add support for KVM_SEV_SEND_CANCEL command
From: Steve Rutherford <srutherford@google.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, natet@google.com,
        Ashish.Kalra@amd.com, brijesh.singh@amd.com, pbonzini@redhat.com,
        Steve Rutherford <srutherford@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After completion of SEND_START, but before SEND_FINISH, the source VMM can
issue the SEND_CANCEL command to stop a migration. This is necessary so
that a cancelled migration can restart with a new target later.

Reviewed-by: Nathan Tempelman <natet@google.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Steve Rutherford <srutherford@google.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  9 ++++++++
 arch/x86/kvm/svm/sev.c                        | 23 +++++++++++++++++++
 drivers/crypto/ccp/sev-dev.c                  |  1 +
 include/linux/psp-sev.h                       | 10 ++++++++
 include/uapi/linux/kvm.h                      |  2 ++
 5 files changed, 45 insertions(+)

```
#### [PATCH v2] KVM: vmx: add mismatched size assertions in vmcs_check32()
##### From: lihaiwei.kernel@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Haiwei Li <lihaiwei.kernel@gmail.com>
X-Patchwork-Id: 12192819
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A2ED9C433B4
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 02:25:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73C87610C7
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 02:25:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232733AbhDICZ2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 8 Apr 2021 22:25:28 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38984 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232638AbhDICZ2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 8 Apr 2021 22:25:28 -0400
Received: from mail-pj1-x1035.google.com (mail-pj1-x1035.google.com
 [IPv6:2607:f8b0:4864:20::1035])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 96B05C061760;
        Thu,  8 Apr 2021 19:25:14 -0700 (PDT)
Received: by mail-pj1-x1035.google.com with SMTP id i4so2146698pjk.1;
        Thu, 08 Apr 2021 19:25:14 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=mOZ83lWyBCeICtWu3/0oO47MuS4gfmvFARW76Re2qv0=;
        b=pnksMaMbcw2Kq0VfamCd+NoAaO/msJ0ONuaV1DRYfmYaIxFlb9Ibt91G75cXrhGHnT
         oh99VNTSluVMwcibbbsy0eSx08PUlHc2G9NyJReUrCKHZAfAJ2WLcXAiqM2Cc7Iwht4/
         gcwmXs3iaSNBQRmUKQkRag7za8cHgINf07A7GYJ8ZWWtqTKKHZ29r5wy/rzfmcye/DQt
         GmQBcwgJpTvqx0xLEh0IWvpFgnvKRHeQJdV3S/5m6Fnxzh4PBX89o/yUN/42lnJgf0mG
         dRJzaaXjBgtTQKGyVeyK/pKEgKQ36d9BjVvGt/NJ2vTr2bycj0w0SVluU2W4S7D2lrud
         bcEQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=mOZ83lWyBCeICtWu3/0oO47MuS4gfmvFARW76Re2qv0=;
        b=eX+CuzwXYN0NdLwLXBzt+1QfNzmj6rRjDPC7r/BwaoyavbNJO5SopUXutROaUpaPgU
         VIP8gFkWVEbD2ltrk1mVN+sJXUz2N9cTonug84qaj56qxoeVQkME7M/AtmSGc7FuaJa8
         wot8Su4POQX8cmAIqtrGYBWlk/IlRWYLW/7TM9u6btNqQOamG99UDkZSHaxUSoFgKD0X
         qp3MDk8EgOvgxq16VTw8DWiwESZzjwOvncIapl+RTsHUdYjmfx8jO0XI2EGaN9pw4a5l
         CG5p0Wpo89a+aOmAeQ1SExdiXA0qfQe7YGQLG5LBqmZGY2G5KoBTvQtY1CwlSFvzrgNY
         hA5Q==
X-Gm-Message-State: AOAM531i/eOB9FKk22f6OHJowONKoF7jltBExkp8K8tEUQFTuBfXgISu
        VJSmkLORtESp792nAf+3Ukvsr/WPRQ==
X-Google-Smtp-Source: 
 ABdhPJxBqyPBV7mvWUarynkXmg0LYKsdjSQuLcC46ABbv+hpqtNFMZwBi9RUoevkzKAkBSzq7/URrQ==
X-Received: by 2002:a17:902:b602:b029:e6:cabb:10b9 with SMTP id
 b2-20020a170902b602b02900e6cabb10b9mr10449221pls.47.1617935113792;
        Thu, 08 Apr 2021 19:25:13 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.39])
        by smtp.gmail.com with ESMTPSA id r10sm608769pjf.5.2021.04.08.19.25.11
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 08 Apr 2021 19:25:13 -0700 (PDT)
From: lihaiwei.kernel@gmail.com
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v2] KVM: vmx: add mismatched size assertions in vmcs_check32()
Date: Fri,  9 Apr 2021 10:24:56 +0800
Message-Id: <20210409022456.23528-1-lihaiwei.kernel@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Haiwei Li <lihaiwei@tencent.com>

Add compile-time assertions in vmcs_check32() to disallow accesses to
64-bit and 64-bit high fields via vmcs_{read,write}32().  Upper level KVM
code should never do partial accesses to VMCS fields.  KVM handles the
split accesses automatically in vmcs_{read,write}64() when running as a
32-bit kernel.

Reviewed-and-tested-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Haiwei Li <lihaiwei@tencent.com>
---
v1 -> v2:
* Improve the changelog 

 arch/x86/kvm/vmx/vmx_ops.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v3] KVM: SVM: Make sure GHCB is mapped before updating
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12194305
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C746DC433B4
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 14:39:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9B09B610E6
	for <kvm@archiver.kernel.org>; Fri,  9 Apr 2021 14:39:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233998AbhDIOjR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 9 Apr 2021 10:39:17 -0400
Received: from mail-dm6nam11on2068.outbound.protection.outlook.com
 ([40.107.223.68]:10656
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S232990AbhDIOjQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Apr 2021 10:39:16 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=naMuSY1XZe+tp8Smgo/YZER8X+AcJU0HsEo3F3gV41klJ4oX+Gj0VgxY32E+/iRORiyDNWsKT6XWJh7RkbgHHCgHelD1psmtwU0yncOkUgjY3zlk7K2pSfaOd3IbD1eOeSO+0oFEMv2jPs0KJ6ovH+Vy1G0nPLo9k580xQ2jFF3o9SyBJd4CxfCx2qR4FN0+sM+5Sv0UcBmTynTKaEUZcjdT46TXXWVibqBIZLtiwa2xTkQ0NSG3FHBiyvBpsuDKAw+XNilJPO+cK5BkNTQ6SejRU8kwsUIYzEUQ/+uRL4s/3I0Hueja9bx/sxVns12Q0XFI5dAfC+JJcZsFGahZww==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K+aiyox32en7oa/GuwpXrDIQJAZsf73+oicLCivVhTY=;
 b=E/5mjK03rj2LVTYkPKOS7xdVjac82w7MR7Jb2UO7xvw/eI2hrZ0Zo3PHQe8vUWtbTr0bqB1Z3hjcymANKrWZzD2x/98iU4/C+JnAmTdrLfHeF3S0u5dwdKwkoQX9S366SOEDgJE/xck6alr4WhDNto8nvsKyv/QTZHIDCAF2wwg1jsS1uMXever2DGJuJTqNf2+dfYv/ciJxNcwNdRIeiD2b2hUaUpdV8LYOatuO4GCf9Lf2hS6J26q5zRWEREZ+g9bN8NW5yvWi9ip6m4/23uw6vnYlDs/TpZ8JaR1hDCZ8ubEbFEErj6Ai0ECEVoFA4FB3s54WL0HSG1rfwanGVw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=K+aiyox32en7oa/GuwpXrDIQJAZsf73+oicLCivVhTY=;
 b=c9a5mpOSmASf5/an+BlbVJ8VSBc++BoXaDfMsfr9WSIRGA0HfT4Y1jpQ3Oe20ZVCaVdf/xSsd9LjWPe/35NrrlNv7cfgawc8xgJlLtzgTQ1T8qhl1590/THRKeU3z4fk/050ytIwOz8++q9LT1/LuDR1lRUgZidmgIrwrMYSYCE=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM5PR1201MB0123.namprd12.prod.outlook.com (2603:10b6:4:50::22) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.4020.16; Fri, 9 Apr 2021 14:39:00 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::b914:4704:ad6f:aba9%12]) with mapi id 15.20.4020.021; Fri, 9 Apr 2021
 14:39:00 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH v3] KVM: SVM: Make sure GHCB is mapped before updating
Date: Fri,  9 Apr 2021 09:38:42 -0500
Message-Id: 
 <a5d3ebb600a91170fc88599d5a575452b3e31036.1617979121.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.31.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0501CA0109.namprd05.prod.outlook.com
 (2603:10b6:803:42::26) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN4PR0501CA0109.namprd05.prod.outlook.com (2603:10b6:803:42::26) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4042.8 via Frontend
 Transport; Fri, 9 Apr 2021 14:38:59 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 29161cff-df3a-493c-0116-08d8fb6536db
X-MS-TrafficTypeDiagnostic: DM5PR1201MB0123:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1201MB01232B054979176555EA9C92EC739@DM5PR1201MB0123.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:10000;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 1CP5BlPdmpqwtFvp9s47+vj/a6Fb173beEJf2GnXCJ8R4nIewiubLAdzCEM4ad7kA93yGWxFXX2D2opssSh+Gqkq4+ymkL9Ka9EbB8tdbJxquI0eGUDz9mr+FV34Vpda3wNdMBBFeUS3cUbacuoQakl7LIj/cOzlq0adf5rFGPmSW/pVSjaUXMDeHthJnUZKXeCXiJvma6w+BCq5UYuCtP4aO/Yw+wzmkSdeG8iwrhYKYuxCMLK3IA75/hgf2scXR/BQTo3YVEf1ql2xHebVj4Q7sc+m6rj1yr5OKBcSWmNqlsHs+CqnBG5IwVitZ9QLLx8a4b2lArdyi8vkWvxfZ71mVgnmAHBZaISxorz6Giamcmj8nHcoIjJQqwF6jzDPoKJ947cEtle4caOdOPYxCzT2UpKDWVsKCDVXkI2BH96yTnLy+bTdXEGwC46nldp47dy1SUxwJj6fOMa2HCN4WHKyjCIEF2SJN3kNUNRk1nDico5Xl7ejd+Nze/I4jHrArM1nOAT+h/YckvjfkqgzT0TV5utnrUEWuHjXN8FUffWpzP6P2ls596GkJCpzokhUSYkYrd/SVQFo/i249UCTh2jt1iRpZ/fGLWOLhTIRKZ08YUC2zRPhYKS1BWlks76DaS6vX2x8ssrN+FgXUOiCDDSvEtdK7AXIUGqQOOrYf+mSRFO3JSmV2Rb8a4hKpoyz
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(376002)(39850400004)(396003)(136003)(346002)(36756003)(54906003)(8676002)(5660300002)(316002)(8936002)(4326008)(38350700001)(38100700001)(16526019)(6666004)(52116002)(186003)(7416002)(83380400001)(2906002)(2616005)(956004)(478600001)(66476007)(66556008)(66946007)(26005)(86362001)(7696005)(6486002);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 c9Et9mnF1m6dT8csLrBwXVFdMIe7as1u9pumdpHxR1tUwcUMgwBSUg5r2tCcTS3CiUmfgdlvkdIECOdDUKgPb+hZQrLlKzsNCLJKIfUDKMuq46xPmRMap07rw1dp9wRFZkkKgAce+SyhBcf4Avq9N9OqklwpgE6Ih7kekwp9DSbG4c6WlkXRmiE/Z5m5hz33xy5WXVAYnsP+V6YSnCfDDsS2ZEt0mYh1NWKKC32l4nDYXQlySOii2yeTOZ4kp5Y74ajK2lw3aOyZFvfoLZd+FmRSmWKXCTTqv2cAwjNnqiK1HUXQX9owVKEi/BKRXRhDsBDWxeZcBdXEKc6dPXgTPz4GASnBgKSPpvnZUvGhypCdGQuJT+60oc6b717A5eH+glMnzewxNAxkkfCi2Vcc/+gYsees6GSmLnKg5WABpag1+62P3Q+lPqH108rXv9m6yBhB66AKl775ZRvLi55fKqIx4t5iOYmvgtntFuwKs4iUWG28e/4fQtD4v71NrPRhv/zf/jV9NZExmgUH/aQ5j+J8VePqPvKUu79gwoY3SSYmM8KNpucd+NhFC9m2IoTQKgQJhIHj8bI0O0T+Bz43drgq4y8d8MrlZXl0UEUNov70SeeoHm+JAls+gYIa5QsuRjbAUwqoehnUcxu5kcSQmaTPmovhH+I0KqqMnw4R6rluLHf7p2XoZopKnJnGKN502DzCyuPSdluwyAZzCQR9irkSZJnos4riFuyDl0LrlWesofBVn8aIZ8tpYWx3BFHvWfK/HCPso+LRhnXQ5G94nOaRg+D2rp2/3ZYN7dCIK+OUTCzLBdILnaYA0jbKOIg8E4JAzWKf/It1PIDid1NehZx8VSgTT3vK71IReRwxaxYe2i4YqCniIR5AkNgMI0BFIwPoPlCKDUOkoo9vbggp7sMCKR2XM/RqUJuABMa/ld/mRpXH9w+bgeAkIvtGbzr47u/gXXkE1n12QHOj6FVTT7FaGvjo+Y39Uf8vZi6SyX3LfoNsKWXNF/sqqTcSXCp2VlKcrD6rPIrlaGeF1L+lMzS3YoDXQ/IqC5q+L5Mdo5jVLd7PyprvuXS2enhyiKaqsZ38caQYBLjeCJrYtA+Pk5Bh9rrevrQNhINn9YzMqWQG28ukfDr8ET4ZkMQcEmT0qEHgjpkGuJ//WaaohqKezLQIRzVVc9cPzBwHBGK6E1L4/ZfUfQAJ3wDL9MQlAp0nvdibORg9B9rkemirJAmsyMOo3q6N82LGuKq5lGtHwPZ+FZkIOsQKPZeZi4V/9Fc+X0/EqwNgtUSoP9Kej7XPyCfFe10ZeBlLoxEPJouN80/iioyp5Xfv6lKDBnhCz2xj
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 29161cff-df3a-493c-0116-08d8fb6536db
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Apr 2021 14:39:00.5765
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 0FpKfBD0hkVPOeFParAAMwO2DusjQaWD4EJSfJ/1h/t5qyX2HHSowtQfBm3yMcUJnerpnB4zF0ookrV61gVHPQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1201MB0123
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

Access to the GHCB is mainly in the VMGEXIT path and it is known that the
GHCB will be mapped. But there are two paths where it is possible the GHCB
might not be mapped.

The sev_vcpu_deliver_sipi_vector() routine will update the GHCB to inform
the caller of the AP Reset Hold NAE event that a SIPI has been delivered.
However, if a SIPI is performed without a corresponding AP Reset Hold,
then the GHCB might not be mapped (depending on the previous VMEXIT),
which will result in a NULL pointer dereference.

The svm_complete_emulated_msr() routine will update the GHCB to inform
the caller of a RDMSR/WRMSR operation about any errors. While it is likely
that the GHCB will be mapped in this situation, add a safe guard
in this path to be certain a NULL pointer dereference is not encountered.

Fixes: f1c6366e3043 ("KVM: SVM: Add required changes to support intercepts under SEV-ES")
Fixes: 647daca25d24 ("KVM: SVM: Add support for booting APs in an SEV-ES guest")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Sean Christopherson <seanjc@google.com>
---

Changes from v2:
- Removed WARN_ON_ONCE() from the sev_vcpu_deliver_sipi_vector() path
  since it is guest triggerable and can crash systems with panic_on_warn
  and replaced with pr_warn_once().

Changes from v1:
- Added the svm_complete_emulated_msr() path as suggested by Sean
  Christopherson
- Add a WARN_ON_ONCE() to the sev_vcpu_deliver_sipi_vector() path
---
 arch/x86/kvm/svm/sev.c | 3 +++
 arch/x86/kvm/svm/svm.c | 2 +-
 2 files changed, 4 insertions(+), 1 deletion(-)

```
