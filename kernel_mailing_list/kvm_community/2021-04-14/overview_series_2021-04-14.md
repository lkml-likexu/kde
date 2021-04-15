#### [GIT PULL] VFIO fix for v5.12-rc8/final
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12203097
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-20.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E717C433ED
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 15:03:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CF826109D
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 15:03:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S235620AbhDNPDz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 11:03:55 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:44679 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230213AbhDNPDy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Apr 2021 11:03:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618412612;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=88s58SzYj2MxQQqxlXe2yFHWu8MlDxFM8fvj/JE9A8A=;
        b=RrMZnQyluQZOL4oWKnaIpg2pV+bXMcNz9gAyel/KmDzqe7a8DKZBiThOf1iscWrrjwK3BV
        VywpK3cy/3J1iu+8TlFI8ojiLsWccCXbMVRWz4fKPMnrRvsy/tO9nBh54/Z4h1Gs+pCkbl
        YHYXmPWao6tx69MligCMaUnHFIqPZ+Y=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-HyQaNGn_NxyF144W0WNB-A-1; Wed, 14 Apr 2021 11:03:28 -0400
X-MC-Unique: HyQaNGn_NxyF144W0WNB-A-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3C00D83DD20;
        Wed, 14 Apr 2021 15:03:27 +0000 (UTC)
Received: from omen (ovpn-117-254.rdu2.redhat.com [10.10.117.254])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 633C26087C;
        Wed, 14 Apr 2021 15:03:26 +0000 (UTC)
Date: Wed, 14 Apr 2021 09:03:25 -0600
From: Alex Williamson <alex.williamson@redhat.com>
To: Linus Torvalds <torvalds@linux-foundation.org>
Cc: <linux-kernel@vger.kernel.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>, lk@c--e.de
Subject: [GIT PULL] VFIO fix for v5.12-rc8/final
Message-ID: <20210414090325.3580db75@omen>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Linus,

Sorry for the late request.

The following changes since commit d434405aaab7d0ebc516b68a8fc4100922d7f5ef:

  Linux 5.12-rc7 (2021-04-11 15:16:13 -0700)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.12-rc8

for you to fetch changes up to 909290786ea335366e21d7f1ed5812b90f2f0a92:

  vfio/pci: Add missing range check in vfio_pci_mmap (2021-04-13 08:29:16 -0600)

----------------------------------------------------------------
VFIO fix for v5.12-rc8/final

 - Verify mmap region within range (Christian A. Ehrhardt)

----------------------------------------------------------------
Christian A. Ehrhardt (1):
      vfio/pci: Add missing range check in vfio_pci_mmap

 drivers/vfio/pci/vfio_pci.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)
```
#### [PATCH v3 1/2] kvm/arm64: Remove the creation time's mapping of MMIO regions
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12202033
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B0786C433B4
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 06:52:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 935946105A
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 06:52:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1349446AbhDNGwa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 02:52:30 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:16994 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1349426AbhDNGw1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 02:52:27 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FKtNz4ydKzNw04;
        Wed, 14 Apr 2021 14:49:07 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.498.0; Wed, 14 Apr 2021 14:51:54 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v3 1/2] kvm/arm64: Remove the creation time's mapping of MMIO
 regions
Date: Wed, 14 Apr 2021 14:51:08 +0800
Message-ID: <20210414065109.8616-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210414065109.8616-1-zhukeqian1@huawei.com>
References: <20210414065109.8616-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The MMIO regions may be unmapped for many reasons and can be remapped
by stage2 fault path. Map MMIO regions at creation time becomes a
minor optimization and makes these two mapping path hard to sync.

Remove the mapping code while keep the useful sanity check.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 arch/arm64/kvm/mmu.c | 38 +++-----------------------------------
 1 file changed, 3 insertions(+), 35 deletions(-)

```
#### [PATCH 1/5] KVM: arm64: Divorce the perf code from oprofile helpers
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12202927
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 60CD3C43462
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 13:44:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55BAB611EE
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 13:44:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1351605AbhDNNoq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 09:44:46 -0400
Received: from mail.kernel.org ([198.145.29.99]:52294 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1351587AbhDNNop (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 09:44:45 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 18C22611F0;
        Wed, 14 Apr 2021 13:44:24 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lWfoc-007RSZ-Cq; Wed, 14 Apr 2021 14:44:22 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        linux-s390@vger.kernel.org, linux-sh@vger.kernel.org
Cc: Mark Rutland <mark.rutland@arm.com>, Will Deacon <will@kernel.org>,
        Rich Felker <dalias@libc.org>,
        Yoshinori Sato <ysato@users.sourceforge.jp>,
        Peter Zijlstra <peterz@infradead.org>,
        Arnaldo Carvalho de Melo <acme@kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Heiko Carstens <hca@linux.ibm.com>, nathan@kernel.org,
        Viresh Kumar <viresh.kumar@linaro.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH 1/5] KVM: arm64: Divorce the perf code from oprofile helpers
Date: Wed, 14 Apr 2021 14:44:05 +0100
Message-Id: <20210414134409.1266357-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210414134409.1266357-1-maz@kernel.org>
References: <20210414134409.1266357-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
 linux-s390@vger.kernel.org, linux-sh@vger.kernel.org, mark.rutland@arm.com,
 will@kernel.org, dalias@libc.org, ysato@users.sourceforge.jp,
 peterz@infradead.org, acme@kernel.org, borntraeger@de.ibm.com,
 hca@linux.ibm.com, nathan@kernel.org, viresh.kumar@linaro.org,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM/arm64 is the sole user of perf_num_counters(), and really
could do without it. Stop using the obsolete API by relying on
the existing probing code.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/perf.c     | 7 +------
 arch/arm64/kvm/pmu-emul.c | 2 +-
 include/kvm/arm_pmu.h     | 4 ++++
 3 files changed, 6 insertions(+), 7 deletions(-)

```
#### [PATCH 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12202273
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 076EAC43461
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 09:24:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DC5CB61249
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 09:24:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1350286AbhDNJYe (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 05:24:34 -0400
Received: from mga17.intel.com ([192.55.52.151]:26133 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1348621AbhDNJY0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 05:24:26 -0400
IronPort-SDR: 
 xMnKtvwJML/HyIHFKrGTDdOnJetkWIawLpD7QZo+sH0Qg72eQxVAcnjgneE6u+agdktatFgeXn
 PVaugwso4smw==
X-IronPort-AV: E=McAfee;i="6200,9189,9953"; a="174709608"
X-IronPort-AV: E=Sophos;i="5.82,221,1613462400";
   d="scan'208";a="174709608"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 02:24:05 -0700
IronPort-SDR: 
 OC97/ZAKLwm9Tme1kR0NX3e9TUmlAIeVFUWlmLmUyKUpOMby++OUJVCdGNYY07mVdxgu3RYTvf
 hsD5kfR6CC9A==
X-IronPort-AV: E=Sophos;i="5.82,221,1613462400";
   d="scan'208";a="424648455"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 02:24:01 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/3] vDPA/ifcvf: deduce VIRTIO device ID when probe
Date: Wed, 14 Apr 2021 17:18:30 +0800
Message-Id: <20210414091832.5132-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
In-Reply-To: <20210414091832.5132-1-lingshan.zhu@intel.com>
References: <20210414091832.5132-1-lingshan.zhu@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This commit deduces VIRTIO device ID as device type when probe,
then ifcvf_vdpa_get_device_id() can simply return the ID.
ifcvf_vdpa_get_features() and ifcvf_vdpa_get_config_size()
can work properly based on the device ID.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vdpa/ifcvf/ifcvf_base.h |  1 +
 drivers/vdpa/ifcvf/ifcvf_main.c | 22 ++++++++++------------
 2 files changed, 11 insertions(+), 12 deletions(-)

```
#### [PATCH 1/5] x86/kvm: Fix pr_info() for async PF setup/teardown
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12202701
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 954FCC433B4
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 12:35:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7388561153
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 12:35:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1350961AbhDNMgR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 08:36:17 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:25807 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1350951AbhDNMgQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Apr 2021 08:36:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618403755;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=1dKkaTH7hpNFzDTl2DIM6SgVCwH1tMksVM+Mg4H8vkI=;
        b=M9mdFncKiY0efB915An8YOe2WzgZjhF88NegEp6acK/UJPj6QJIEsaGKEzLQ89Z6f/luq6
        r8lBDhJljvVlreVCkDp6Gap+Svsb1lJLnaESIZo6Ria+w+KGiKck4/5vVIL/Gd2KYcDnYu
        4Qn4J4DqQmeEijv5SJPR5kPVH8ovXiY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-504-mX3ssg0zNa-s_Yw0bGJN1g-1; Wed, 14 Apr 2021 08:35:53 -0400
X-MC-Unique: mX3ssg0zNa-s_Yw0bGJN1g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4B549188353B;
        Wed, 14 Apr 2021 12:35:51 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.196.11])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 86C285D9DE;
        Wed, 14 Apr 2021 12:35:48 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, x86@kernel.org,
        Lenny Szubowicz <lszubowi@redhat.com>,
        Mohamed Aboubakr <mabouba@amazon.com>,
        Xiaoyi Chen <cxiaoyi@amazon.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 1/5] x86/kvm: Fix pr_info() for async PF setup/teardown
Date: Wed, 14 Apr 2021 14:35:40 +0200
Message-Id: <20210414123544.1060604-2-vkuznets@redhat.com>
In-Reply-To: <20210414123544.1060604-1-vkuznets@redhat.com>
References: <20210414123544.1060604-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

'pr_fmt' already has 'kvm-guest: ' so 'KVM' prefix is redundant.
"Unregister pv shared memory" is very ambiguous, it's hard to
say which particular PV feature it relates to.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kernel/kvm.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
