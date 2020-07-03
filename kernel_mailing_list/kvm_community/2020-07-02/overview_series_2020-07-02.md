#### 
##### 

```c
```
#### [kvm-unit-tests PATCH v2 2/8] arm64: microbench: Use the funcions for ipi test as the general functions for gic(ipi/lpi/timer) test
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11637795
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13E5B92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE21620884
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726514AbgGBDCd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 23:02:33 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:47214 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726345AbgGBDCc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 23:02:32 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 70D6486F3619031EC0BE;
        Thu,  2 Jul 2020 11:02:30 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.42) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 11:02:21 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH v2 2/8] arm64: microbench: Use the funcions for
 ipi test as the general functions for gic(ipi/lpi/timer) test
Date: Thu, 2 Jul 2020 11:01:26 +0800
Message-ID: <20200702030132.20252-3-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
In-Reply-To: <20200702030132.20252-1-wangjingyi11@huawei.com>
References: <20200702030132.20252-1-wangjingyi11@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.42]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following patches will use that.

Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arm/micro-bench.c | 39 ++++++++++++++++++++++-----------------
 1 file changed, 22 insertions(+), 17 deletions(-)

```
#### [RFC PATCH 01/22] vhost: Make _feature_ bits a property of vhost device
##### From: Kishon Vijay Abraham I <kishon@ti.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kishon Vijay Abraham I <kishon@ti.com>
X-Patchwork-Id: 11638231
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2B6D06C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:25:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EC31D20899
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:25:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ti.com header.i=@ti.com header.b="yXQ+RTwS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728192AbgGBIWP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 04:22:15 -0400
Received: from fllv0015.ext.ti.com ([198.47.19.141]:34350 "EHLO
        fllv0015.ext.ti.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726183AbgGBIWK (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 04:22:10 -0400
Received: from fllv0034.itg.ti.com ([10.64.40.246])
        by fllv0015.ext.ti.com (8.15.2/8.15.2) with ESMTP id 0628LuLH016993;
        Thu, 2 Jul 2020 03:21:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ti.com;
        s=ti-com-17Q1; t=1593678116;
        bh=ABGiAo420c56SSOxSDxeuSuOeuV6cI8PSAJ9Fas2di4=;
        h=From:To:CC:Subject:Date:In-Reply-To:References;
        b=yXQ+RTwS5M9CIUtd5IuR47WT4ucoslxL6bkH0Pgrp91jiJI5naqA5olIis/Zv0t0C
         +53APmY4ZnBgRw2ZA9ckgoq9xEf37dHIXMTrS2N5GrJndkPCjEYnOjadIWuGlQuGok
         pUdmwVPHhN0OqnGenibNZrzqA499mhcZzXaltE5c=
Received: from DLEE114.ent.ti.com (dlee114.ent.ti.com [157.170.170.25])
        by fllv0034.itg.ti.com (8.15.2/8.15.2) with ESMTPS id 0628Lu9h029608
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=FAIL);
        Thu, 2 Jul 2020 03:21:56 -0500
Received: from DLEE110.ent.ti.com (157.170.170.21) by DLEE114.ent.ti.com
 (157.170.170.25) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.1979.3; Thu, 2 Jul
 2020 03:21:56 -0500
Received: from lelv0327.itg.ti.com (10.180.67.183) by DLEE110.ent.ti.com
 (157.170.170.21) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256_P256) id 15.1.1979.3 via
 Frontend Transport; Thu, 2 Jul 2020 03:21:56 -0500
Received: from a0393678ub.india.ti.com (ileax41-snat.itg.ti.com
 [10.172.224.153])
        by lelv0327.itg.ti.com (8.15.2/8.15.2) with ESMTP id 0628LiYD006145;
        Thu, 2 Jul 2020 03:21:51 -0500
From: Kishon Vijay Abraham I <kishon@ti.com>
To: Ohad Ben-Cohen <ohad@wizery.com>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Jon Mason <jdmason@kudzu.us>,
        Dave Jiang <dave.jiang@intel.com>,
        Allen Hubbe <allenbh@gmail.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        Bjorn Helgaas <bhelgaas@google.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Stefano Garzarella <sgarzare@redhat.com>
CC: <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <linux-remoteproc@vger.kernel.org>, <linux-ntb@googlegroups.com>,
        <linux-pci@vger.kernel.org>, <kvm@vger.kernel.org>,
        <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>
Subject: [RFC PATCH 01/22] vhost: Make _feature_ bits a property of vhost
 device
Date: Thu, 2 Jul 2020 13:51:22 +0530
Message-ID: <20200702082143.25259-2-kishon@ti.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200702082143.25259-1-kishon@ti.com>
References: <20200702082143.25259-1-kishon@ti.com>
MIME-Version: 1.0
X-EXCLAIMER-MD-CONFIG: e1e8a2fd-e40a-4ac6-ac9b-f7e9cc9ee180
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended. The feature bits defined in virtio
specification is associated with virtio device and not virtqueue.
In order to correctly reflect this in the vhost backend, remove
"acked_features" from struct vhost_virtqueue and add "features" in
struct vhost_dev. This will also make it look symmetrical to virtio
in guest.

Signed-off-by: Kishon Vijay Abraham I <kishon@ti.com>
---
 drivers/vhost/net.c   |  7 ++++---
 drivers/vhost/scsi.c  | 22 ++++++++--------------
 drivers/vhost/test.c  | 14 +++++---------
 drivers/vhost/vhost.c | 33 +++++++++++++++++++++------------
 drivers/vhost/vhost.h |  6 +++---
 drivers/vhost/vsock.c | 18 ++++++------------
 6 files changed, 47 insertions(+), 53 deletions(-)

```
#### [PATCH v2 1/8] KVM: arm64: Set DBM bit for writable PTEs
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11638967
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13242161F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 13:57:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03831208B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 13:57:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729528AbgGBN5L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 09:57:11 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:7356 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729407AbgGBN5K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 09:57:10 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 8000126C23D4911ADAAC;
        Thu,  2 Jul 2020 21:56:10 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 21:56:01 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Catalin Marinas <catalin.marinas@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Will Deacon <will@kernel.org>,
        "Suzuki K Poulose" <suzuki.poulose@arm.com>,
        Steven Price <steven.price@arm.com>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Thomas Gleixner" <tglx@linutronix.de>,
        Andrew Morton <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <liangpeng10@huawei.com>, <zhengxiang9@huawei.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 1/8] KVM: arm64: Set DBM bit for writable PTEs
Date: Thu, 2 Jul 2020 21:55:49 +0800
Message-ID: <20200702135556.36896-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200702135556.36896-1-zhukeqian1@huawei.com>
References: <20200702135556.36896-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

DBM bit is used by MMU to differentiate a genuinely non-writable
page from a page that is only temporarily non-writable in order
to mark dirty.

Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
Signed-off-by: Peng Liang <liangpeng10@huawei.com>
---
 arch/arm64/include/asm/kvm_mmu.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH kvm-unit-tests] arm/arm64: timer: Extract irqs at setup time
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11638081
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAA8C739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:13:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A00D520874
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 08:13:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ARTn6apR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728192AbgGBINx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 04:13:53 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:51728 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725379AbgGBINx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 04:13:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593677631;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=gbJA/RmWRo4DsQRLNHyZabYf9h247N0ChofgtBrHV28=;
        b=ARTn6apRcseLHyGFappwKqsn/aMEnYR5aFZoAHyUNOAM8EqHrRNHEBeyaU6k7anzJqokNM
        OzDWUG1RtTBzOnB+J3sZVvD0NXs+llJqLgL7AYDkomIjNuuPAUeFlsdiCQvaoTpV2N3+vQ
        NV+1te96w4elwtv57pOLbw+dDwp7OYA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-186-3c3HQYISMbCahuG9rQWcKw-1; Thu, 02 Jul 2020 04:13:48 -0400
X-MC-Unique: 3c3HQYISMbCahuG9rQWcKw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6EF1F185B3B3;
        Thu,  2 Jul 2020 08:12:26 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.192.87])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 004EB610F2;
        Thu,  2 Jul 2020 08:12:20 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: wangjingyi11@huawei.com, maz@kernel.org,
        wanghaibin.wang@huawei.com, yuzenghui@huawei.com,
        eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests] arm/arm64: timer: Extract irqs at setup time
Date: Thu,  2 Jul 2020 10:12:19 +0200
Message-Id: <20200702081219.27176-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The timer can be useful for other tests besides the timer test.
Extract the DT parsing of the irqs out of the timer test into
setup and provide them along with some defines in a new timer.h
file.

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arm/timer.c           | 26 ++++----------------------
 lib/arm/asm/timer.h   | 31 +++++++++++++++++++++++++++++++
 lib/arm/setup.c       | 42 ++++++++++++++++++++++++++++++++++++++++++
 lib/arm64/asm/timer.h |  1 +
 4 files changed, 78 insertions(+), 22 deletions(-)
 create mode 100644 lib/arm/asm/timer.h
 create mode 100644 lib/arm64/asm/timer.h

```
#### [kvm-unit-tests PATCH v2 1/8] arm64: microbench: get correct ipi received num
##### From: Jingyi Wang <wangjingyi11@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jingyi Wang <wangjingyi11@huawei.com>
X-Patchwork-Id: 11637781
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9F42292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90C8F20720
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 03:02:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726718AbgGBDCd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 23:02:33 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:47128 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726374AbgGBDCc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 23:02:32 -0400
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 56DD46A6489F87F95C66;
        Thu,  2 Jul 2020 11:02:30 +0800 (CST)
Received: from DESKTOP-FPN2511.china.huawei.com (10.174.187.42) by
 DGGEMS405-HUB.china.huawei.com (10.3.19.205) with Microsoft SMTP Server id
 14.3.487.0; Thu, 2 Jul 2020 11:02:20 +0800
From: Jingyi Wang <wangjingyi11@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <maz@kernel.org>, <wanghaibin.wang@huawei.com>,
        <yuzenghui@huawei.com>, <eric.auger@redhat.com>,
        <wangjingyi11@huawei.com>
Subject: [kvm-unit-tests PATCH v2 1/8] arm64: microbench: get correct ipi
 received num
Date: Thu, 2 Jul 2020 11:01:25 +0800
Message-ID: <20200702030132.20252-2-wangjingyi11@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
In-Reply-To: <20200702030132.20252-1-wangjingyi11@huawei.com>
References: <20200702030132.20252-1-wangjingyi11@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.42]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If ipi_exec() fails because of timeout, we shouldn't increase
the number of ipi received.

Signed-off-by: Jingyi Wang <wangjingyi11@huawei.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 arm/micro-bench.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: use more precise cast and do not drop __user
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11638393
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E3D17739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 09:39:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA0A220884
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 09:39:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KuLrQtIC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728152AbgGBJjj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 05:39:39 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:57609 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727791AbgGBJji (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 05:39:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593682777;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=OU1abHmcvqlPXE7j6qY5NTPbjnWuDoW6srqdHAGVMo0=;
        b=KuLrQtICw7WxwjLWuFc0r8nMZRtg6o+v9u4dGs6PUqVBECKXj+LNpErY6apyBQPJqNQWmj
        vTALcbE2O/7GFe8vRHaRQ68b0vXS4OZRm/Z1kME44NjuHFGpDdqkx8uNixoMecGEricWy4
        zCqNf2jzGM8Fho4ziAhGnvSrGiLmoqc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-31-JnfcbkGbNaqoEPaIYrmDpA-1; Thu, 02 Jul 2020 05:39:36 -0400
X-MC-Unique: JnfcbkGbNaqoEPaIYrmDpA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B2DA8BFC3;
        Thu,  2 Jul 2020 09:39:34 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6344F5C541;
        Thu,  2 Jul 2020 09:39:34 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] kvm: use more precise cast and do not drop __user
Date: Thu,  2 Jul 2020 05:39:33 -0400
Message-Id: <20200702093933.20845-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sparse complains on a call to get_compat_sigset, fix it.  The "if"
right above explains that sigmask_arg->sigset is basically a
compat_sigset_t.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: x86: rewrite kvm_spec_ctrl_valid_bits
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11640041
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 820D0739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 17:45:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 69A3A2088E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 17:45:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="dBELHSjb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727906AbgGBRpM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 13:45:12 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:56779 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726754AbgGBRpL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 13:45:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1593711910;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=2+YKOFsMFqgKEAlgmAfFeYOf9HVs9QXIdHNLGDvzQ5Y=;
        b=dBELHSjb44DN1U+uAWX0eYnf7/7kAupfoZuv1SYt3qItdWn8DrfEq9m9U2pqB2rT0SAtRM
        y/Qjwf3a0cuUzaNnFby0QRO1o7maohSYiF5+JEDQCynmpi9CTfJaVuFe3fKX6b2isevSPy
        gCo6k+pLWgjI2MRz8vZlnx85fP1xJOI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-423-Dorxu1FDMIOrZb7rmwInbg-1; Thu, 02 Jul 2020 13:45:08 -0400
X-MC-Unique: Dorxu1FDMIOrZb7rmwInbg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 950A88015FE;
        Thu,  2 Jul 2020 17:45:06 +0000 (UTC)
Received: from starship.redhat.com (unknown [10.35.206.247])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D1CA4619C1;
        Thu,  2 Jul 2020 17:44:56 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        linux-kernel@vger.kernel.org, Joerg Roedel <joro@8bytes.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] kvm: x86: rewrite kvm_spec_ctrl_valid_bits
Date: Thu,  2 Jul 2020 20:44:55 +0300
Message-Id: <20200702174455.282252-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are few cases when this function was creating a bogus #GP condition,
for example case when and AMD host supports STIBP but doesn't support SSBD.

Follow the rules for AMD and Intel strictly instead.

AMD #GP rules for IA32_SPEC_CTRL can be found here:
https://bugzilla.kernel.org/show_bug.cgi?id=199889

Fixes: 6441fa6178f5 ("KVM: x86: avoid incorrect writes to host MSR_IA32_SPEC_CTRL")

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 57 ++++++++++++++++++++++++++++++++++------------
 1 file changed, 42 insertions(+), 15 deletions(-)

```
#### [kvm-unit-tests PATCH v10 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11639579
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C4E4739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:31:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F10E120720
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:31:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726710AbgGBQb3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 12:31:29 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:5434 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726465AbgGBQb3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 2 Jul 2020 12:31:29 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 062G4EhL049989;
        Thu, 2 Jul 2020 12:31:28 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 320s2a71fc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 12:31:28 -0400
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 062GKWce134787;
        Thu, 2 Jul 2020 12:31:27 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 320s2a71ea-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 12:31:27 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 062GMH0O019741;
        Thu, 2 Jul 2020 16:31:25 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 31wwch5vyx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 02 Jul 2020 16:31:25 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 062GVN3235979308
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 2 Jul 2020 16:31:23 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0DDC811C06C;
        Thu,  2 Jul 2020 16:31:23 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8C32611C058;
        Thu,  2 Jul 2020 16:31:22 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.146.43])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  2 Jul 2020 16:31:22 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v10 1/9] s390x: saving regs for interrupts
Date: Thu,  2 Jul 2020 18:31:12 +0200
Message-Id: <1593707480-23921-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1593707480-23921-1-git-send-email-pmorel@linux.ibm.com>
References: <1593707480-23921-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-02_09:2020-07-02,2020-07-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 bulkscore=0
 lowpriorityscore=0 suspectscore=1 mlxlogscore=999 impostorscore=0
 phishscore=0 cotscore=-2147483648 priorityscore=1501 adultscore=0
 mlxscore=0 spamscore=0 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2007020111
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers, the floating point registers and the floating point
control register on the stack in case of I/O interrupts

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/cstart64.S | 41 +++++++++++++++++++++++++++++++++++++++--
 1 file changed, 39 insertions(+), 2 deletions(-)

```
#### [PATCH v2] x86/speculation/l1tf: Add KConfig for setting the L1D cache flush mode
##### From: Abhishek Bhardwaj <abhishekbh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Abhishek Bhardwaj <abhishekbh@google.com>
X-Patchwork-Id: 11640449
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ED58414B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 21:38:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D292820899
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 21:38:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Dk979kDT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726148AbgGBViW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 17:38:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:57286 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725954AbgGBViV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 17:38:21 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 86C04C08C5C1
        for <kvm@vger.kernel.org>; Thu,  2 Jul 2020 14:38:21 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id j3so31519543yba.14
        for <kvm@vger.kernel.org>; Thu, 02 Jul 2020 14:38:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=3jFVmOWTZ7tfbragSeisWuV593ZLuszzQyS3jGQXGNo=;
        b=Dk979kDTJeU8TS2UZalznCkhwAAk6oVDP7ehiHAWnidaRkcctFc1ICv1lZHft17wne
         l4FHMTIEX/Qv4t2ItkVRx0k/K4zpIs+Z97Y4aerzejJR/J4O4YnmNxURCmUxliI+kpag
         gEe98j4v1HfOuRViBx9LDs/PEVeK/0ex5Vd9Dkxk88L7LkSEV4UbjK3xo4bjS+qrLZHu
         ahE49X8pltTgTVCRAA/xfyPyLueBbXAH/o6cOBsXzJ2B0FTDBmfXvkbWXQRKNSqeivIy
         UtPqk0Fb9kMmzlTYNf9MYnUZIV+NtWNqc1XnvElkMjVqWlEsIA/c2FByVBxaRrVBJmL/
         UIoQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=3jFVmOWTZ7tfbragSeisWuV593ZLuszzQyS3jGQXGNo=;
        b=EHoutIcUr2PnydHLnW4mFAh0QhUBqfLmtK7W1DR9IazL4niO8uP1+5LVmruPpLzskT
         N4zrOgiV2NVPsRLlVzY2LDoJ2eP/cS6ThIJccs8e4f+sihapg4Mfzn0RDylMQJ5N1KyN
         XzyHazvEy35QBCs/5LsxnCBdY7QMxZCHqYRe6bkrYo6SR0wZTUC8qGip1+WUuJNNSCAp
         2mRveoTM4/Ic9yvDW/MZ3QJuX+GQ9G5Fa98XLMBjmGhrowdcCWE8QRYqDZWz1xtvRzgN
         Xb25ZM9HvbZ48xNRnlXeMW6JY2ThBMyV0Y0q0/WTJlVmMvzylqNMm2N4+Cns8OO0lb/g
         tNOg==
X-Gm-Message-State: AOAM532DumhgJ/5PehMYwjFIjck7OD4VgWJ9c2CoLnrHxb1Mr/OGmb4S
        xgi2tHOzDEOJYYugkyRLcmwHXjr+PDuPXIHE
X-Google-Smtp-Source: 
 ABdhPJxAVfsuDW//QTW+DVgSQMyg8D5UHUYjhMGXNySyEZnJS+jNMSdZyoBRA5sXSiH6NQBqZANE7mFqyx25lBh7
X-Received: by 2002:a25:9904:: with SMTP id z4mr52596021ybn.146.1593725900728;
 Thu, 02 Jul 2020 14:38:20 -0700 (PDT)
Date: Thu,  2 Jul 2020 14:38:07 -0700
Message-Id: <20200702213807.2511503-1-abhishekbh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.212.ge8ba1cc988-goog
Subject: [PATCH v2] x86/speculation/l1tf: Add KConfig for setting the L1D
 cache flush mode
From: Abhishek Bhardwaj <abhishekbh@google.com>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Abhishek Bhardwaj <abhishekbh@google.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Mark Gross <mgross@linux.intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Waiman Long <longman@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds a new kernel configuration that sets the l1d cache
flush setting at compile time rather than at run time.

Signed-off-by: Abhishek Bhardwaj <abhishekbh@google.com>
---

Changes in v2:
- Fix typo in the help of the new KConfig.

 arch/x86/kernel/cpu/bugs.c |  8 ++++++++
 arch/x86/kvm/Kconfig       | 17 +++++++++++++++++
 2 files changed, 25 insertions(+)

```
#### [PATCH v3] x86/speculation/l1tf: Add KConfig for setting the L1D cache flush mode
##### From: Abhishek Bhardwaj <abhishekbh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Abhishek Bhardwaj <abhishekbh@google.com>
X-Patchwork-Id: 11640453
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8655513B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 22:12:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 68B2420885
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 22:12:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="miWQau21"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726228AbgGBWMo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 18:12:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34356 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726014AbgGBWMn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 18:12:43 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id A654DC08C5C1
        for <kvm@vger.kernel.org>; Thu,  2 Jul 2020 15:12:43 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id e20so31226788ybc.23
        for <kvm@vger.kernel.org>; Thu, 02 Jul 2020 15:12:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=PswgYOjFLHR50otlPxE8b2oGJ3kDUK3h2XTdWa425M0=;
        b=miWQau211dDj1fe/9wWIj67CDW+WofqWHYP6On71PKk8qGABIWIZgsg6QaVQF6200z
         2HekYUpa8CR/8ZH0IXD751av4uDRNbhIdcY+G8Phl/p+3Ou/pfeWlUvJIgpUw6vNbPJg
         LxXCichKPhMD8l+s3+ilWXjoveWcdwpx0o6QwAYWJPoH19aeUDoNCx4srH8TcWuUmzbN
         fYmAJzSvKt/ujCua/IZfLJDHYuK1Xv568YfbiYgddoviuLdQNfo+a9eRDZ0tdhsrYygC
         guLIit+pK9pvWkFfP5DnA3Lng+PSZWCC4j/lTxqrdiuUGwgxuonF2SjkKQZoO7u+xJ/j
         XPUw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=PswgYOjFLHR50otlPxE8b2oGJ3kDUK3h2XTdWa425M0=;
        b=ctg+6dYYIJqoQc5/GYNNnxG2qWqrOxOoD2MqdCh0G0KexRsDUDXyMsGzlPIvVBXcYE
         xbKHjckFwaz33jGn49NlkMH75S8gjDVj0GMe5FsrThQ4Jh1aHFh5sa45uWp5/goLgH3V
         NZujrUVw6pV2TjCebIcGM/noJJfDzMrXoXpxsERwNJz6953ZpcgPWGWG9rsfyFBe6O/f
         +fZ1XxgsZeP9KLxMvnbIOUvtiYhu3yt4iOn5LXGBs4mlZyITkUkixTNpvwaREAv57IP/
         mFAFZroFonmE2svXI80uhGlirb/ztDWI3BPnsiYxELp/i4Wc2pQICb3zralaffnBDZdt
         4xFA==
X-Gm-Message-State: AOAM532IvKnVToOkm/FPve5BmC0ZisIjXRng7loGepFWi0rgr6N9+BU5
        cHVHbRPxHvnJT21Fbs0dyJHRsDtxK1IW6aCv
X-Google-Smtp-Source: 
 ABdhPJxMgLnACwCz65RBY/9qPnP80m0LmIZzQopaUlX4E3h+C8yL6JDA7+Y5Ako8csmqguYSuHXJQYdGnP1puQAi
X-Received: by 2002:a25:38c5:: with SMTP id
 f188mr54720332yba.332.1593727962818;
 Thu, 02 Jul 2020 15:12:42 -0700 (PDT)
Date: Thu,  2 Jul 2020 15:12:37 -0700
Message-Id: <20200702221237.2517080-1-abhishekbh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.212.ge8ba1cc988-goog
Subject: [PATCH v3] x86/speculation/l1tf: Add KConfig for setting the L1D
 cache flush mode
From: Abhishek Bhardwaj <abhishekbh@google.com>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Abhishek Bhardwaj <abhishekbh@google.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Mark Gross <mgross@linux.intel.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Waiman Long <longman@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds a new kernel configuration that sets the l1d cache
flush setting at compile time rather than at run time.

Signed-off-by: Abhishek Bhardwaj <abhishekbh@google.com>
---

Changes in v3:
- Change depends on to only x86_64.
- Remove copy paste errors at the end of the KConfig.

Changes in v2:
- Fix typo in the help of the new KConfig.

 arch/x86/kernel/cpu/bugs.c |  8 ++++++++
 arch/x86/kvm/Kconfig       | 13 +++++++++++++
 2 files changed, 21 insertions(+)

```
#### [PATCH] x86/speculation/l1tf: Add KConfig for setting the L1D cache flush mode
##### From: Abhishek Bhardwaj <abhishekbh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Abhishek Bhardwaj <abhishekbh@google.com>
X-Patchwork-Id: 11639535
Return-Path: <SRS0=Tice=AN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0396C6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:19:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DE41B21473
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  2 Jul 2020 16:19:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="suMZCdb6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726379AbgGBQTW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 2 Jul 2020 12:19:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36420 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726082AbgGBQTW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 2 Jul 2020 12:19:22 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 00528C08C5C1
        for <kvm@vger.kernel.org>; Thu,  2 Jul 2020 09:19:21 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id h10so6136440qtc.4
        for <kvm@vger.kernel.org>; Thu, 02 Jul 2020 09:19:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=CXTe1dgoIkziCoFVfYKeWk3MqTpTpSjmG77p0bE6NoA=;
        b=suMZCdb64YsbSOryl020BrcFDQ3UYPbRVImF5H5v6pc9aBeBZtiSXm2zZ/33mPrnrb
         WxErBfDhtBLdxno5VWInb25pAdsvuAPINvWptBxml477CQfyEGDM3UfI6YJU3GkUxAce
         dD2tKHU0hLlD3swE/sXOkvX4FezCBbL2CLT77TSj6dWGSLou78WiYYmFPRjE0KnZZCS9
         m8R9XTNuKGncmUoCWNwAEnGp/RmNxWEICtYd5aEeoZB+zc0m1WR4/9SF/rdlNDw43VeA
         eJvJ4i9pIQ/aVIbIIRz0oZ+uoGCA/KjIwzJPxFewdN5NdyBvSRAONvVOOUamk+z9Sm6d
         cC7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=CXTe1dgoIkziCoFVfYKeWk3MqTpTpSjmG77p0bE6NoA=;
        b=ivcTZi5n/KYEZkIeTuTJVRpkPG7qs4DKutkp6FXrUToBnVbUKF3yo436bDM2d1pOOd
         wh6nwtDWvD+07vQt3JJcgjTE/qMXjnszW6zPK8zKo1rQ6pBg1vW5al8yoSP4V6Yj1MIf
         TM1M5pa5I1yydsepKefS6T4QtuXiS6fP/LWCarN6q1OFY5qf9Il700AI1Z+wXafJRARY
         l6g1a6Lf5+Tba6MABw9r1EDY8jLoHEN5ao25xPYstorJh+yDboI4h/vNKZ5t7SaA4BhD
         xYVuTr6dj3eBetePLwbicxn4QSn9r+2h2JOal6jlY+b/Xk7lmqLsvHtQNBORYAeKQtFO
         r1vw==
X-Gm-Message-State: AOAM533Di/NesDGlwmSF+oyEoF6LYNTucHr4B1Fn5vLrY3UMaFuZYPjV
        SgApDsWghnAVZ1MfRwSoNxL4yeU9h4yCXL4v
X-Google-Smtp-Source: 
 ABdhPJyMIMas8tgBt7VQOheH8xigvokD2vo4KZ/A/aw4GacYLB8/fzAlrqaYDQevZIT7u27IzMfwRvfLL/vjfnRF
X-Received: by 2002:ad4:4d83:: with SMTP id
 cv3mr31515092qvb.236.1593706761146;
 Thu, 02 Jul 2020 09:19:21 -0700 (PDT)
Date: Thu,  2 Jul 2020 09:19:16 -0700
Message-Id: <20200702161916.2456342-1-abhishekbh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.212.ge8ba1cc988-goog
Subject: [PATCH] x86/speculation/l1tf: Add KConfig for setting the L1D cache
 flush mode
From: Abhishek Bhardwaj <abhishekbh@google.com>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Abhishek Bhardwaj <abhishekbh@google.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Mark Gross <mgross@linux.intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Waiman Long <longman@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds a new kernel configuration that sets the l1d cache
flush setting at compile time rather than at run time.

Signed-off-by: Abhishek Bhardwaj <abhishekbh@google.com>
---

 arch/x86/kernel/cpu/bugs.c |  8 ++++++++
 arch/x86/kvm/Kconfig       | 17 +++++++++++++++++
 2 files changed, 25 insertions(+)

```
