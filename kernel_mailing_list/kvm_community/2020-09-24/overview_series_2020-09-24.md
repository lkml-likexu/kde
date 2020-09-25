#### [PATCH v7 5/7] KVM: arm64: pmu: Make overflow handler NMI safe
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11796975
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4FFF8139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 11:06:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C42A239A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 11:06:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727522AbgIXLGf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 07:06:35 -0400
Received: from foss.arm.com ([217.140.110.172]:42280 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727476AbgIXLGY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 07:06:24 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 1AB9E152B;
        Thu, 24 Sep 2020 04:06:23 -0700 (PDT)
Received: from monolith.localdoman (unknown [10.37.8.98])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 9A0723F73B;
        Thu, 24 Sep 2020 04:06:20 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org
Cc: mark.rutland@arm.com, sumit.garg@linaro.org, maz@kernel.org,
        swboyd@chromium.org, catalin.marinas@arm.com, will@kernel.org,
        Julien Thierry <julien.thierry@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Marc Zyngier <marc.zyngier@arm.com>,
        Will Deacon <will.deacon@arm.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Pouloze <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Subject: [PATCH v7 5/7] KVM: arm64: pmu: Make overflow handler NMI safe
Date: Thu, 24 Sep 2020 12:07:04 +0100
Message-Id: <20200924110706.254996-6-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200924110706.254996-1-alexandru.elisei@arm.com>
References: <20200924110706.254996-1-alexandru.elisei@arm.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Julien Thierry <julien.thierry@arm.com>

kvm_vcpu_kick() is not NMI safe. When the overflow handler is called from
NMI context, defer waking the vcpu to an irq_work queue.

A vcpu can be freed while it's not running by kvm_destroy_vm(). Prevent
running the irq_work for a non-existent vcpu by calling irq_work_sync() on
the PMU destroy path.

Cc: Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Catalin Marinas <catalin.marinas@arm.com>
Cc: James Morse <james.morse@arm.com>
Cc: Suzuki K Pouloze <suzuki.poulose@arm.com>
Cc: kvm@vger.kernel.org
Cc: kvmarm@lists.cs.columbia.edu
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
Tested-by: Sumit Garg <sumit.garg@linaro.org> (Developerbox)
[Alexandru E.: Added irq_work_sync()]
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
I suggested in v6 that I will add an irq_work_sync() to
kvm_pmu_vcpu_reset(). It turns out it's not necessary: a vcpu reset is done
by the vcpu being reset with interrupts enabled, which means all the work
has had a chance to run before the reset takes place.

 arch/arm64/kvm/pmu-emul.c | 26 +++++++++++++++++++++++++-
 include/kvm/arm_pmu.h     |  1 +
 2 files changed, 26 insertions(+), 1 deletion(-)

```
#### [RFC PATCH 01/24] vhost-vdpa: fix backend feature ioctls
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11795925
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1D30592C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 03:22:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 00C1123600
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 03:22:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="QfNmrvwJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726674AbgIXDV4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 23 Sep 2020 23:21:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:59898 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726634AbgIXDVz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 23 Sep 2020 23:21:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600917713;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=c1vAH2sOnIecyBuC1bgws2niE0JgFrbZ244nIj8c+DU=;
        b=QfNmrvwJBadRabo8pG733x/M+caGWv6Rz4YK7j+/V5WcSZll9sJP3xp2sva0dbzJ3q2AOj
        L6g29iRyWkeBMUuvIMZQXGuJJsyw4GsQxsABtcdgUw+AX2y5vIy2sHjDwe4OIqqWp9U+uQ
        0xz5cyDe4lcGGxT7RNUBZk2qEsyP4tc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-437-XMWz49fsN5a-IB1C8BEtBQ-1; Wed, 23 Sep 2020 23:21:51 -0400
X-MC-Unique: XMWz49fsN5a-IB1C8BEtBQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 269FE801AF7;
        Thu, 24 Sep 2020 03:21:50 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-193.pek2.redhat.com [10.72.13.193])
        by smtp.corp.redhat.com (Postfix) with ESMTP id BEC8855768;
        Thu, 24 Sep 2020 03:21:43 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com
Cc: lulu@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org, rob.miller@broadcom.com,
        lingshan.zhu@intel.com, eperezma@redhat.com, hanand@xilinx.com,
        mhabets@solarflare.com, eli@mellanox.com, amorenoz@redhat.com,
        maxime.coquelin@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, Eli Cohen <elic@nvidia.com>
Subject: [RFC PATCH 01/24] vhost-vdpa: fix backend feature ioctls
Date: Thu, 24 Sep 2020 11:21:02 +0800
Message-Id: <20200924032125.18619-2-jasowang@redhat.com>
In-Reply-To: <20200924032125.18619-1-jasowang@redhat.com>
References: <20200924032125.18619-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 653055b9acd4 ("vhost-vdpa: support get/set backend features")
introduces two malfunction backend features ioctls:

1) the ioctls was blindly added to vring ioctl instead of vdpa device
   ioctl
2) vhost_set_backend_features() was called when dev mutex has already
   been held which will lead a deadlock

This patch fixes the above issues.

Cc: Eli Cohen <elic@nvidia.com>
Reported-by: Zhu Lingshan <lingshan.zhu@intel.com>
Fixes: 653055b9acd4 ("vhost-vdpa: support get/set backend features")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 30 ++++++++++++++++--------------
 1 file changed, 16 insertions(+), 14 deletions(-)

```
#### [PATCH] cpuidle-haltpoll: fix error comments in arch_haltpoll_disable
##### From: Li Qiang <liq3ea@163.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li Qiang <liq3ea@163.com>
X-Patchwork-Id: 11797865
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D133112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:13:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C0E62396D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:13:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=163.com header.i=@163.com
 header.b="E/ILQ6Z1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727352AbgIXQNy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 12:13:54 -0400
Received: from mail-m971.mail.163.com ([123.126.97.1]:49992 "EHLO
        mail-m971.mail.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726426AbgIXQNy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 12:13:54 -0400
X-Greylist: delayed 938 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 24 Sep 2020 12:13:53 EDT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=163.com;
        s=s110527; h=From:Subject:Date:Message-Id:MIME-Version; bh=81LJb
        ZgEhFZ0fbUetUrd79c6ZgQwRmAgDqQCza3AI+0=; b=E/ILQ6Z1s5sh072UMuacB
        2A5qcVTTIiQRq+WwOZd2GueAqz18sRYlHBPeqCIx7pMpLwb9lVLfPP2wHMxSLuJm
        7JnGa5NQI8TINwsTJ+xEVsq4J8wlra8lVAroc6jQJU56UE447RzFBzYzzEsVnR7C
        k9zp4QJ8oOV0zIn76BwV5A=
Received: from ubuntu.localdomain (unknown [115.216.108.105])
        by smtp1 (Coremail) with SMTP id GdxpCgAH7h4Kwmxf_6nsCw--.274S4;
        Thu, 24 Sep 2020 23:58:03 +0800 (CST)
From: Li Qiang <liq3ea@163.com>
To: pbonzini@redhat.com, x86@kernel.org, kvm@vger.kernel.org,
        mtosatti@redhat.com
Cc: liq3ea@gmail.com, linux-kernel@vger.kernel.org,
        Li Qiang <liq3ea@163.com>
Subject: [PATCH] cpuidle-haltpoll: fix error comments in arch_haltpoll_disable
Date: Thu, 24 Sep 2020 08:58:00 -0700
Message-Id: <20200924155800.4939-1-liq3ea@163.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-CM-TRANSID: GdxpCgAH7h4Kwmxf_6nsCw--.274S4
X-Coremail-Antispam: 1Uf129KBjvdXoW7Xr18ZryDAr4fuw1xCryrXrb_yoWfGFX_XF
        13C398Cry3WrnrAay7Cw4rWF1agwnYqF4Fkas3tFWFy3srtr15Kan2yw1YyrnxZr4vyFZr
        Zw15Cw45Kw4UAjkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUvcSsGvfC2KfnxnUUI43ZEXa7IUUqg4DUUUUU==
X-Originating-IP: [115.216.108.105]
X-CM-SenderInfo: 5oltjvrd6rljoofrz/xtbBawupbVet2BDvSgAAsz
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The 'arch_haltpoll_disable' is used to disable guest halt poll.
Correct the comments.

Fixes: a1c4423b02b21 ("cpuidle-haltpoll: disable host side polling when kvm virtualized")
Signed-off-by: Li Qiang <liq3ea@163.com>
---
 arch/x86/kernel/kvm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: SVM: Add a dedicated INVD intercept routine
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11798081
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47B14112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:42:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FAA7235FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:42:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="mMGBGiAl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728767AbgIXSma (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 14:42:30 -0400
Received: from mail-bn8nam11on2076.outbound.protection.outlook.com
 ([40.107.236.76]:61492
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728758AbgIXSm3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 14:42:29 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Hd8NWbnWpPJdV/iIRuKdSNdNiVJzbZQh0ktUtICqdlVaUv8N89tjjw9RlgBq4qOqYrs/CX6C0fyht+QKAOxdttFD7vXrncEue0U3ab3EeSV+VUYb4q3RL5ksaqCH58zGla0K05SqhsUBJioB5Gv9V8Sa1rFCZ8n03B5xm8ZT6qkq16k0/6vFaL+8izoO879F+ScNX2Za/hZygj1eYSubj3+rq6XAczHC2Qp1AtVl3BQxQdARbzA/N1h7RATef0qeVBHRUVvXy3h2/QYZ7UYkQLu3F0cfLgXGQoucmBrofI3d4NE3KlVu6EjOGNOCgw0BWxIwokFjL+UCqsUISgT6/Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=wg6pImjmqhbxekmy4Snhg//pL+oxPOo5WsVYxfSczAE=;
 b=k1WesKWyaAY7lphl5LUEwuQ2UIpTcOcxNQ5QEvUu51ZFsBBvivRR0wIRqpfAwPtbYGAwTjYlAqkrp9s/iSpBdD6cWQ1prP2YKuxG0gKTjX+mrGd8KbRu28Fps0hjSolSdcidjhg5styDLC16wnyXRYsT10CKfeV14KKt2HVkfGGzpDslV7tgYejabHnpEtZt37ByOsKXxxdk93N7ODZsSxr/lyJlGi68dGPO5797S0P+qRHO8QVbeZIf+sK6KuG6XNczNXg2ystDlaiYZZWstO8rTLqrM9NFKQDKVCpxSb0+lwYjD3JUHbl/qb3LkfsIMy9W/e14bHca/VBk/+wHzg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=wg6pImjmqhbxekmy4Snhg//pL+oxPOo5WsVYxfSczAE=;
 b=mMGBGiAlLctiIM6nukepp810LvgqTyQNhTRcz0DSZe1RvFQAn4UPmGQ2+vNEzxT09QcErUw5FSurwDv2pC3J0fkzrhEZrHKnpiGT/u8aoAtL86cGaYyMMjikja6TfbLbJqDfFrLmJFxVewUkIWAaE15RjoQa+wAkLaZ//it+SWM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB3082.namprd12.prod.outlook.com (2603:10b6:5:11b::12) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3412.23; Thu, 24 Sep 2020 18:42:27 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::299a:8ed2:23fc:6346%3]) with mapi id 15.20.3391.024; Thu, 24 Sep 2020
 18:42:27 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>
Subject: [PATCH v2 1/2] KVM: SVM: Add a dedicated INVD intercept routine
Date: Thu, 24 Sep 2020 13:41:57 -0500
Message-Id: 
 <a0b9a19ffa7fef86a3cc700c7ea01cb2731e04e5.1600972918.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1600972918.git.thomas.lendacky@amd.com>
References: <cover.1600972918.git.thomas.lendacky@amd.com>
X-ClientProxiedBy: DM5PR19CA0056.namprd19.prod.outlook.com
 (2603:10b6:3:116::18) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 DM5PR19CA0056.namprd19.prod.outlook.com (2603:10b6:3:116::18) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3412.22 via Frontend
 Transport; Thu, 24 Sep 2020 18:42:26 +0000
X-Mailer: git-send-email 2.28.0
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 14d98264-5adb-4e5f-479f-08d860b995fb
X-MS-TrafficTypeDiagnostic: DM6PR12MB3082:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB308279B67D28EB15A3CE0983EC390@DM6PR12MB3082.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 QQ0uAnevC01XHzRv+Sp0Xuz7x+7Cd4w0G3ZvwEzdgXZVc2xtuF2z/yvgGW3/egZCSsITEWsutOrVfFusAu+kV+LB6gSGiHTnpnua9mrodoXygbcmYRmpVkxFzv/NKxWClNgNozOpaAoGjrFy5Phk2kk2r8aepl2rM/rv7yFUfnWC7XqS8vV5z3QnC0mnjhGoWby5sPN8Sdvq7+BdaSP50aHx/nXBI9JcSrQFn9gTfBR19xfengrUl1L4qzFPoprSsHcz/w9lGrtAYE4fsp5SB3h3UCUbYVBmRUynOdHC6UhIoZc7OfiYGXzzeOLm6/6r
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(366004)(376002)(346002)(136003)(39860400002)(7416002)(83380400001)(316002)(36756003)(2906002)(956004)(8676002)(8936002)(66556008)(26005)(66476007)(186003)(16526019)(54906003)(478600001)(52116002)(7696005)(2616005)(6666004)(5660300002)(66946007)(4326008)(6486002)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 IDRPMiyBUT95kJO9prunBqP7HkG5oSMvG7kYLurImWs1dtRZ2YIpX9haPhD8b1k4sUtJHVIekid4quqS0Em0nDqIBkqTrqVRE5f4+zz2ZLtNMYib8nIom0P4hdVzx0Tlzg20UoWfMoQVLPVdAPKtR+PDNnSJ+lsG+Jp73Mo1X0Q0asnY+eo5OHLuzIrzSRnd3BZ8FR0F4gKNFLlF0UQWmdFLjC5g2iHn+bn3kDnLpJ0+MwDiD5M6bpYlE/saLLCMxvcxzFdjWdG6vMgide6oRZehre2h5x1/RwyY7Q8fMBuprBZjnyGLadA0ZExC8ND8JKLnFYh7Zxy5plF139uQpOucSDx0rtmB5JT5c4O1gLpqECmnKdF+rI6PApBC0xk+w4WF3lSKwXPLFvb0oN3MfTDYBlAZz4LspXIvYWw4jWCDZPvDEIqcqSu+9VJJdW2aB1WlQqMDHqOzPQHlpcKvEXlShdmHU2i9i1PXXMKVdFDl+3V4iWLpx2ch6X7xrdHu+sqFEQ3DsNHTkUU6jTJCuYtYjIXg057uYKZIRtKIghggy7cCP7zESRnE9uIsbM4qmrcpVVvrG0eDQ//8MgIZp5sZmSynNodegX2z8OQdelc864cKAK5gVYJy2xwCl5ziUVlc00YXf4y/55vJ4g/EXg==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 14d98264-5adb-4e5f-479f-08d860b995fb
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 24 Sep 2020 18:42:27.5893
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 iNT53ouGahqYcYf6Vl56HPIPYHXsAyvmMCG9sJA80Cc/VfN2v55VoRI/sUi/TA6IMcosDidOxfyTS9ePP11OCw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3082
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

The INVD instruction intercept performs emulation. Emulation can't be done
on an SEV guest because the guest memory is encrypted.

Provide a dedicated intercept routine for the INVD intercept. And since
the instruction is emulated as a NOP, just skip it instead.

Fixes: 1654efcbc431 ("KVM: SVM: Add KVM_SEV_INIT command")
Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm/svm.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] configure: Test if compiler supports -m16 on x86
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11798071
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 40B52139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:24:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 23D2B2311B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:24:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="kTt0GcUS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728678AbgIXSYH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 14:24:07 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:35490 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728264AbgIXSYG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 14:24:06 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id DD711579F2;
        Thu, 24 Sep 2020 18:24:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1600971843; x=
        1602786244; bh=Nekod14rEitjpGsAgxjBkB5K4jNGoD1ieQohZPzbM4g=; b=k
        Tt0GcUSdnZCmaAhjgv1wOH2EPLM/NTOLduXV7FWO5Y3vEUgykOI4AsM/FAb9Q8i2
        oY1qBWExHRNol79nXukPchDUhZ8gqyNr+Z3QuCKUYhrwKoc8KmLKu8scSMf2TcP3
        SEfxLhs4eEsBNsUYvi42gZc1QB9LvFC70uWryCKXrM=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id jHkl3H-oJFQf; Thu, 24 Sep 2020 21:24:03 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 66DAC57933;
        Thu, 24 Sep 2020 21:24:03 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Thu, 24
 Sep 2020 21:24:03 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Thomas Huth <thuth@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH] configure: Test if compiler supports -m16 on
 x86
Date: Thu, 24 Sep 2020 21:24:01 +0300
Message-ID: <20200924182401.95891-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

-m16 option is available only since GCC 4.9.0 [1]. That causes a build
failure on centos-7 [2] that has GCC 4.8.5.

Fallback to -m32 if -m16 is not available.

1. http://gcc.gnu.org/bugzilla/show_bug.cgi?id=59672
2. https://gitlab.com/bonzini/kvm-unit-tests/-/jobs/755368387

Fixes: 2616ad934e2 ("x86: realmode: Workaround clang issues")
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 configure           | 11 +++++++++++
 x86/Makefile.common |  4 ++++
 2 files changed, 15 insertions(+)

```
#### [kvm-unit-tests PATCH] README: Reflect missing --getopt in configure
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11796875
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB827618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 10:07:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A738239A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 10:07:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="HpxAAJA6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727183AbgIXKHD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 06:07:03 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:39036 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726597AbgIXKHD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 06:07:03 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id CE57D57548;
        Thu, 24 Sep 2020 10:07:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1600942019; x=
        1602756420; bh=/H24eg0W8XTSkggmDnsMYMgefXEpcnRtF6/CGrEiMSo=; b=H
        pxAAJA63LjgPpMl2YKLLIApAo0z97+xbOIzmJ0rVR5Z6eB0rpVxJin7KofbHXkjG
        tRfOSjNxV0lbJ5YT8l3i9AIIuMNkBfnLCisn3V3135h6h3KbeU+rbXuX1rSWqdf4
        MQ/J+8T4xjA2rkm7xLw8zrI+Mh9KR9DSvq8Zh3TX7A=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id T-TfLxkxJUWu; Thu, 24 Sep 2020 13:06:59 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id BFD3A57D54;
        Thu, 24 Sep 2020 13:06:59 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Thu, 24
 Sep 2020 13:06:59 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Thomas Huth <thuth@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Roman Bolshakov <r.bolshakov@yadro.com>
Subject: [kvm-unit-tests PATCH] README: Reflect missing --getopt in configure
Date: Thu, 24 Sep 2020 13:06:14 +0300
Message-ID: <20200924100613.71136-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

83760814f637 ("configure: Check for new-enough getopt") has replaced
proposed patch and doesn't introduce --getopt option in configure.
Instead, `configure` and `run_tests.sh` expect proper getopt to be
available in PATH.

Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 README.macOS.md | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x/selftest: Fix constraint of inline assembly
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11797075
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33DD06CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 11:17:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 166BF239E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 11:17:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FkAkKHNs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727398AbgIXLR4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 07:17:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:24683 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726483AbgIXLR4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 07:17:56 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600946275;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=WkqZ/iREvhMbCNBzcXttwJxZSXR/+eOruAO+X3MZ0b8=;
        b=FkAkKHNspzQlAzCKL+zikJlBkkRt3g0ruA6QOT2cL5yVZ1YFClgWNz+AoaW3YR54Mh/J7N
        lmFOSN56dtHTxMmQ08HKDr6huRAg2MyNAKt/gAFSdHEp21I3lwlUTNl34sEP79l7SC57hp
        3/NRrbOd2gxk50x2sJ2xU7wkCUcP7h8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-91-beVbKS9UO_izwZ16RD0YQQ-1; Thu, 24 Sep 2020 07:17:53 -0400
X-MC-Unique: beVbKS9UO_izwZ16RD0YQQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D3E7356B55;
        Thu, 24 Sep 2020 11:17:52 +0000 (UTC)
Received: from thuth.com (ovpn-113-113.ams2.redhat.com [10.36.113.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3924255778;
        Thu, 24 Sep 2020 11:17:48 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests PATCH] s390x/selftest: Fix constraint of inline
 assembly
Date: Thu, 24 Sep 2020 13:17:46 +0200
Message-Id: <20200924111746.131633-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clang on s390x compains:

/home/thuth/devel/kvm-unit-tests/s390x/selftest.c:39:15: error:
 %r0 used in an address
        asm volatile("  stg %0,0(%0)\n" : : "r"(-1L));
                     ^
<inline asm>:1:13: note: instantiated into assembly here
                stg %r0,0(%r0)
                          ^

Right it is. We should not use address register 0 for STG.
Thus let's use the "a" constraint to avoid register 0 here.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/selftest.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: realmode: Workaround clang issues
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11797145
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55405112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 12:07:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C6DF23A32
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 12:07:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="nA7yfGOf"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727702AbgIXMHJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 08:07:09 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:45496 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727494AbgIXMHH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 08:07:07 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id 1AFFA579F2;
        Thu, 24 Sep 2020 12:07:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :x-mailer:message-id:date:date:subject:subject:from:from
        :received:received:received; s=mta-01; t=1600949222; x=
        1602763623; bh=cprXYP/GN+1p2Jw7sjgIsH/PpPAVv1sAHLGBkanaBwU=; b=n
        A7yfGOfsJwMceoqQq5584S7Qzz5X79lI9DNAuiXloyL1t2DskkD5c/LeFAzkuhQr
        Kr50oy0HP+wXpCo5pywvSM0hmeiDsHC7FZ6Z4OL9GBbGLY2FMmENhqaImjnx9VPX
        7iEwaxmwLKxf+4IB6gQjtlXIEa5Fb7M68vZ3vrdsA8=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id h8O6d-hiukJw; Thu, 24 Sep 2020 15:07:02 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id 3A82E579D6;
        Thu, 24 Sep 2020 15:07:02 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Thu, 24
 Sep 2020 15:07:02 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Roman Bolshakov <r.bolshakov@yadro.com>,
        Thomas Huth <thuth@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH] x86: realmode: Workaround clang issues
Date: Thu, 24 Sep 2020 15:05:17 +0300
Message-ID: <20200924120516.77299-1-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

clang doesn't properly support .code16gcc and generates wrong machine
code [1][2][3][4]. But the test works if object file is compiled with -m16 and
explicit suffixes are added for instructions.

1. https://lore.kernel.org/kvm/4d20fbce-d247-abf4-3ceb-da2c0d48fc50@redhat.com/
2. https://lore.kernel.org/kvm/20200915155959.GF52559@SPB-NB-133.local/
3. https://lore.kernel.org/kvm/788b7191-6987-9399-f352-2e661255157e@redhat.com/
4. https://lore.kernel.org/kvm/20200922212507.GA11460@SPB-NB-133.local/

Suggested-by: Thomas Huth <thuth@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 .travis.yml         |  2 +-
 x86/Makefile.common |  2 +-
 x86/realmode.c      | 44 ++++++++++++++++++++++----------------------
 3 files changed, 24 insertions(+), 24 deletions(-)

```
#### [PATCH v3 1/5] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR check
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11798185
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46D761580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 19:43:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2ED28239CF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 19:43:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726187AbgIXTmz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 15:42:55 -0400
Received: from mga18.intel.com ([134.134.136.126]:31793 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725208AbgIXTmz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 15:42:55 -0400
IronPort-SDR: 
 zLJCHE2dhFIe648NZH7wi5uvD7Ci/ZSZKiXFKBDDB0lz3Vz71W9Tsoqq8oRVQpWQt6bHtZ4cbY
 J177IJYOOQnw==
X-IronPort-AV: E=McAfee;i="6000,8403,9754"; a="149076387"
X-IronPort-AV: E=Sophos;i="5.77,299,1596524400";
   d="scan'208";a="149076387"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Sep 2020 12:42:52 -0700
IronPort-SDR: 
 dsuICRaW7RQs8ixQFzR01Icla57G8r4Ce37vrZK30G2Ghw6iTDvDUFeX/G1xSzG9IMvlTeZKyn
 dEYtQEt/7ZOA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,299,1596524400";
   d="scan'208";a="347953045"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by FMSMGA003.fm.intel.com with ESMTP; 24 Sep 2020 12:42:52 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/5] KVM: VMX: Use precomputed MAXPHYADDR for RTIT base MSR
 check
Date: Thu, 24 Sep 2020 12:42:46 -0700
Message-Id: <20200924194250.19137-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200924194250.19137-1-sean.j.christopherson@intel.com>
References: <20200924194250.19137-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use cpuid_maxphyaddr() instead of cpuid_query_maxphyaddr() for the
RTIT base MSR check.  There is no reason to recompute MAXPHYADDR as the
precomputed version is synchronized with CPUID updates, and
MSR_IA32_RTIT_OUTPUT_BASE is not written between stuffing CPUID and
refreshing vcpu->arch.maxphyaddr.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: Explicitly check for hv_remote_flush_tlb when loading pgd()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11798059
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5EE486CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:04:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B1DC23A1D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 18:04:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728736AbgIXSEc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 14:04:32 -0400
Received: from mga03.intel.com ([134.134.136.65]:45606 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727753AbgIXSEb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Sep 2020 14:04:31 -0400
IronPort-SDR: 
 EYQcTzeuJxdi0LyKEH6vU8EYlXbRcqmSNTIi8+6MR4ilgEfnQaI+K4f5AYP6Xac/70Nzb8GuYl
 Xi4lEGSGfO4Q==
X-IronPort-AV: E=McAfee;i="6000,8403,9754"; a="161365971"
X-IronPort-AV: E=Sophos;i="5.77,298,1596524400";
   d="scan'208";a="161365971"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 24 Sep 2020 11:04:30 -0700
IronPort-SDR: 
 FVWvApzr7I7krFoC4sTcxfib8ECY6LWic7dQfyRAgWsZsGuvkFQSuor72shP+nk5Ou7PhJmV3u
 MaZgTlXFREbA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,298,1596524400";
   d="scan'208";a="487023894"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by orsmga005.jf.intel.com with ESMTP; 24 Sep 2020 11:04:30 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Explicitly check for hv_remote_flush_tlb when
 loading pgd()
Date: Thu, 24 Sep 2020 11:04:29 -0700
Message-Id: <20200924180429.10016-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly check that kvm_x86_ops.tlb_remote_flush() points at Hyper-V's
implementation for PV flushing instead of assuming that a non-NULL
implementation means running on Hyper-V.  Wrap the related logic in
ifdeffery as hv_remote_flush_tlb() is defined iff CONFIG_HYPERV!=n.

Short term, the explicit check makes it more obvious why a non-NULL
tlb_remote_flush() triggers EPTP shenanigans.  Long term, this will
allow TDX to define its own implementation of tlb_remote_flush() without
running afoul of Hyper-V.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 7 +++++--
 arch/x86/kvm/vmx/vmx.h | 2 ++
 2 files changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: do not attempt TSC synchronization on guest writes
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11798019
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D00BE59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 17:20:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9247F238D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 17:20:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="FvOtymXu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728519AbgIXRUh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 13:20:37 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37658 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727216AbgIXRUh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 13:20:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600968035;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=g3XUAG08Omyl+siZbtQXelgG4mBXlZr6sOn7Cvu6YgI=;
        b=FvOtymXuVkHCgcKPVW/t+jWI/mZ3TR8iuGgyQZedmNSLhKTAcFUebiYNT374MFoLXLECXP
        O5RxXIaGCyRe2c8ZDUhY8YcTtZAFfzIxqgF2e0+Bo4srS4n54BYkTi/HK2JGLGRqwFA1PH
        TgmriZvKXEKMvOIB+qAHxx2UoRyW/4w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-445-zVy_QuEROaCZIXMQr4i7lQ-1; Thu, 24 Sep 2020 13:20:31 -0400
X-MC-Unique: zVy_QuEROaCZIXMQr4i7lQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 390648015A5;
        Thu, 24 Sep 2020 17:20:30 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CADDB55771;
        Thu, 24 Sep 2020 17:20:29 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: do not attempt TSC synchronization on guest writes
Date: Thu, 24 Sep 2020 13:20:29 -0400
Message-Id: <20200924172029.1760139-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM special-cases writes to MSR_IA32_TSC so that all CPUs have
the same base for the TSC.  This logic is complicated, and we
do not want it to have any effect once the VM is started.

In particular, if any guest started to synchronize its TSCs
with writes to MSR_IA32_TSC rather than MSR_IA32_TSC_ADJUST,
the additional effect of kvm_write_tsc code would be uncharted
territory.

Therefore, this patch makes writes to MSR_IA32_TSC behave
essentially the same as writes to MSR_IA32_TSC_ADJUST when
they come from the guest.  A new selftest (which passes
both before and after the patch) checks the current semantics
of writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST originating
from both the host and the guest.

Upcoming work to remove the special side effects
of host-initiated writes to MSR_IA32_TSC and MSR_IA32_TSC_ADJUST
will be able to build onto this test, adjusting the host side
to use the new APIs and achieve the same effect.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c                            |  30 ++--
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/tsc_msrs_test.c      | 168 ++++++++++++++++++
 3 files changed, 179 insertions(+), 20 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/tsc_msrs_test.c

```
#### [PATCH v2 1/7] KVM: x86: hyper-v: Mention SynDBG CPUID leaves in api.rst
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11797621
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C63ED6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 14:58:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A2A772388A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 14:58:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="iscagfQB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728306AbgIXO6O (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 10:58:14 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42254 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728199AbgIXO6N (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 10:58:13 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600959491;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DNn4YwQRBHPa5GtdZ/7RYlHQGoNXgh5enMfZlg0F2Yk=;
        b=iscagfQBHrukzWQkGkj3I/FkCJ8YjpxB9AmecsI3pF8NHBEqt5Lw4RqkHB7bzfRPfeBlUo
        HVYhretRsokbdEy/ykCwsDf/XKRT+NgKp3n4UTFPFqt62n/lxUMb7mkxFlqr9jGd2H+0oF
        pxNqOo0kdJjV2CrH1Un7s8ZAInRQUBM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-453-U6Dcz271NvWFnJeHznogyw-1; Thu, 24 Sep 2020 10:58:06 -0400
X-MC-Unique: U6Dcz271NvWFnJeHznogyw-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3C2121882FCB;
        Thu, 24 Sep 2020 14:58:04 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.192.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id ECC7555786;
        Thu, 24 Sep 2020 14:58:01 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/7] KVM: x86: hyper-v: Mention SynDBG CPUID leaves in
 api.rst
Date: Thu, 24 Sep 2020 16:57:51 +0200
Message-Id: <20200924145757.1035782-2-vkuznets@redhat.com>
In-Reply-To: <20200924145757.1035782-1-vkuznets@redhat.com>
References: <20200924145757.1035782-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We forgot to update KVM_GET_SUPPORTED_HV_CPUID's documentation in api.rst
when SynDBG leaves were added.

While on it, fix 'KVM_GET_SUPPORTED_CPUID' copy-paste error.

Fixes: f97f5a56f597 ("x86/kvm/hyper-v: Add support for synthetic debugger interface")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 Documentation/virt/kvm/api.rst | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH 1/9] travis.yml: Update from Bionic to Focal
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11797871
Return-Path: <SRS0=Ui5V=DB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E8746CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:16:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E4A52388A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 24 Sep 2020 16:16:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="TF8YmhqR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726841AbgIXQQd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Sep 2020 12:16:33 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:47089 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726652AbgIXQQc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 24 Sep 2020 12:16:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1600964191;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=4VyDfcbQv6DSbladqxeJEZpto2qmswqxERuS2zfS0lw=;
        b=TF8YmhqRbUInoZ0G4UO5W87dUoOa9QHGqWOEqXm8E08+KJlm4NcKoK+/J5+etire9Yrywq
        gtbBwBGHTdaSoTEtst1SKVg6rLSRqiows5wtGyW7kMkKvB1ICQaNWgZ6hRcNhk31F5h1Sh
        SCsFtDFTM/pPUTU2j7bKGfqIQmgdMb8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-292-o9Y1iHGiON2Zz_eDRt3LTQ-1; Thu, 24 Sep 2020 12:16:29 -0400
X-MC-Unique: o9Y1iHGiON2Zz_eDRt3LTQ-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7E27164099;
        Thu, 24 Sep 2020 16:16:28 +0000 (UTC)
Received: from thuth.com (ovpn-113-113.ams2.redhat.com [10.36.113.113])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C39CD73662;
        Thu, 24 Sep 2020 16:16:24 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Drew Jones <drjones@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests PATCH 1/9] travis.yml: Update from Bionic to Focal
Date: Thu, 24 Sep 2020 18:16:04 +0200
Message-Id: <20200924161612.144549-2-thuth@redhat.com>
In-Reply-To: <20200924161612.144549-1-thuth@redhat.com>
References: <20200924161612.144549-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The newer version of QEMU in Focal should help to run more tests
with TCG (which will be enabled in later patches).

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
