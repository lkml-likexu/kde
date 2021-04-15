

#### [PATCH v3 0/2] kvm/arm64: Try stage2 block mapping for host device
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Wed Apr 14 06:51:07 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12202029
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2B352C433B4
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 06:52:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EF2526120E
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 06:52:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1349418AbhDNGwY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 02:52:24 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:16992 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1349379AbhDNGwY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 02:52:24 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4FKtNz5FMxzNw2w;
        Wed, 14 Apr 2021 14:49:07 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.224) by
 DGGEMS402-HUB.china.huawei.com (10.3.19.202) with Microsoft SMTP Server id
 14.3.498.0; Wed, 14 Apr 2021 14:51:53 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>
CC: <wanghaibin.wang@huawei.com>
Subject: [PATCH v3 0/2] kvm/arm64: Try stage2 block mapping for host device
 MMIO
Date: Wed, 14 Apr 2021 14:51:07 +0800
Message-ID: <20210414065109.8616-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.224]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

We have two pathes to build stage2 mapping for MMIO regions.

Create time's path and stage2 fault path.

Patch#1 removes the creation time's mapping of MMIO regions
Patch#2 tries stage2 block mapping for host device MMIO at fault path

Changelog:

v3:
 - Do not need to check memslot boundary in device_rough_page_shift(). (Marc)

Thanks,
Keqian

Keqian Zhu (2):
  kvm/arm64: Remove the creation time's mapping of MMIO regions
  kvm/arm64: Try stage2 block mapping for host device MMIO

 arch/arm64/kvm/mmu.c | 75 +++++++++++++++++++++-----------------------
 1 file changed, 36 insertions(+), 39 deletions(-)
```
#### [PATCH 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Wed Apr 14 09:18:29 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12202271
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF89CC433ED
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 09:24:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2BD561242
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 09:24:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1350251AbhDNJYc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 05:24:32 -0400
Received: from mga17.intel.com ([192.55.52.151]:26128 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1348525AbhDNJYX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 05:24:23 -0400
IronPort-SDR: 
 9NukotK7CH+/DmWwoyCqcSiSwBwbBmVqv2rSSjlr51e4eD/V4hitCydUj0dg+wHz9BwveCcoD9
 AoB7Ptz6X+gw==
X-IronPort-AV: E=McAfee;i="6200,9189,9953"; a="174709601"
X-IronPort-AV: E=Sophos;i="5.82,221,1613462400";
   d="scan'208";a="174709601"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 02:24:02 -0700
IronPort-SDR: 
 iwdI7HnwIdnS0XlZHIxJCGkdcBm6ktLjaxolmmcNJxNuTmEHqlfrEgIYa+k7RMCKwDvIiA5KNa
 Z+jFF7kXoWxw==
X-IronPort-AV: E=Sophos;i="5.82,221,1613462400";
   d="scan'208";a="424648438"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 14 Apr 2021 02:23:59 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com,
        leonro@nvidia.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/3] vDPA/ifcvf: enables Intel C5000X-PL virtio-blk
Date: Wed, 14 Apr 2021 17:18:29 +0800
Message-Id: <20210414091832.5132-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-blk for vDPA.

This series requires:
Stefano's vdpa block patchset: https://lkml.org/lkml/2021/3/15/2113
my patchset to enable Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA:
https://lkml.org/lkml/2021/3/17/432

Thanks!

Zhu Lingshan (3):
  vDPA/ifcvf: deduce VIRTIO device ID when probe
  vDPA/ifcvf: enable Intel C5000X-PL virtio-block for vDPA
  vDPA/ifcvf: get_config_size should return dev specific config size

 drivers/vdpa/ifcvf/ifcvf_base.h | 18 +++++++++++++-
 drivers/vdpa/ifcvf/ifcvf_main.c | 43 ++++++++++++++++++++++-----------
 2 files changed, 46 insertions(+), 15 deletions(-)
```
#### [PATCH 0/5] x86/kvm: Refactor KVM PV features teardown and fix
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Apr 14 12:35:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12202699
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3127BC433B4
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 12:35:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13ABE6117A
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 12:35:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1350958AbhDNMgP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 08:36:15 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:25602 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1350951AbhDNMgO (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 14 Apr 2021 08:36:14 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1618403753;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1d76h5lbcfofHJsa9ymlWqG/TzME9YBSEisvqRIJKpc=;
        b=FwB3XDzT3Lpb0HnyARviir2Eq6zTtVRlaffuKksOrNitd5jdGixEyJPcUonkHNqCG+p3p/
        LpfQso9HzvDpfxigds4t4Ods6fILGZLZ717KFxgI5kj3yGEfCVu1MO9VMsvK5VYVET1y0Z
        LYWWpvwNg3hMfjBqZxNiL0FdPq/9d5Q=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-604-OxkhufTGPl-2DOZRw_2htQ-1; Wed, 14 Apr 2021 08:35:49 -0400
X-MC-Unique: OxkhufTGPl-2DOZRw_2htQ-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 37EF6801FCE;
        Wed, 14 Apr 2021 12:35:48 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.196.11])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6C2C45D9DE;
        Wed, 14 Apr 2021 12:35:45 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, x86@kernel.org,
        Lenny Szubowicz <lszubowi@redhat.com>,
        Mohamed Aboubakr <mabouba@amazon.com>,
        Xiaoyi Chen <cxiaoyi@amazon.com>, linux-kernel@vger.kernel.org
Subject: [PATCH 0/5] x86/kvm: Refactor KVM PV features teardown and fix
 restore from hibernation
Date: Wed, 14 Apr 2021 14:35:39 +0200
Message-Id: <20210414123544.1060604-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series is a successor of Lenny's "[PATCH] x86/kvmclock: Stop kvmclocks
for hibernate restore". While reviewing his patch I realized that PV
features teardown we have is a bit messy: it is scattered across kvm.c
and kvmclock.c and not all features are being shutdown an all paths.
This series unifies all teardown paths in kvm.c and makes sure all
features are disabled when needed.

Vitaly Kuznetsov (5):
  x86/kvm: Fix pr_info() for async PF setup/teardown
  x86/kvm: Teardown PV features on boot CPU as well
  x86/kvm: Disable kvmclock on all CPUs on shutdown
  x86/kvm: Disable all PV features on crash
  x86/kvm: Unify kvm_pv_guest_cpu_reboot() with kvm_guest_cpu_offline()

 arch/x86/include/asm/kvm_para.h |  10 +--
 arch/x86/kernel/kvm.c           | 113 +++++++++++++++++++++-----------
 arch/x86/kernel/kvmclock.c      |  26 +-------
 3 files changed, 78 insertions(+), 71 deletions(-)
```
#### [PATCH 0/5] perf: oprofile spring cleanup
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Wed Apr 14 13:44:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12202925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69924C41603
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 13:44:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5A8B4611B0
	for <kvm@archiver.kernel.org>; Wed, 14 Apr 2021 13:44:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1351594AbhDNNop (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 14 Apr 2021 09:44:45 -0400
Received: from mail.kernel.org ([198.145.29.99]:52252 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1351586AbhDNNoo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Apr 2021 09:44:44 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id B363A611AD;
        Wed, 14 Apr 2021 13:44:23 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lWfob-007RSZ-Jm; Wed, 14 Apr 2021 14:44:21 +0100
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
Subject: [PATCH 0/5] perf: oprofile spring cleanup
Date: Wed, 14 Apr 2021 14:44:04 +0100
Message-Id: <20210414134409.1266357-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
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

This small series builds on top of the work that was started with [1].

It recently became apparent that KVM/arm64 is the last bit of the
kernel that still uses perf_num_counters().

As I went ahead to address this, it became obvious that all traces of
oprofile had been eradicated from all architectures but arm64, s390
and sh (plus a bit of cruft in the core perf code). With KVM fixed,
perf_num_counters() and perf_pmu_name() are finally gone.

Thanks,

	M.

[1] https://lore.kernel.org/lkml/20210215050618.hgftdmfmslbdrg3j@vireshk-i7

Marc Zyngier (5):
  KVM: arm64: Divorce the perf code from oprofile helpers
  arm64: Get rid of oprofile leftovers
  s390: Get rid of oprofile leftovers
  sh: Get rid of oprofile leftovers
  perf: Get rid of oprofile leftovers

 arch/arm64/kvm/perf.c         |  7 +------
 arch/arm64/kvm/pmu-emul.c     |  2 +-
 arch/s390/kernel/perf_event.c | 21 ---------------------
 arch/sh/kernel/perf_event.c   | 18 ------------------
 drivers/perf/arm_pmu.c        | 30 ------------------------------
 include/kvm/arm_pmu.h         |  4 ++++
 include/linux/perf_event.h    |  2 --
 kernel/events/core.c          |  5 -----
 8 files changed, 6 insertions(+), 83 deletions(-)
```
