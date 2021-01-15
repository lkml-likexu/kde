#### [PATCH] Add a reproducer for the AMD nested virtualization errata
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12019399
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9F49CC433E6
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:23:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 569BC23A55
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:23:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728240AbhANMXf (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 07:23:35 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33608 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726687AbhANMXe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Jan 2021 07:23:34 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610626928;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=XR2s4YFGROTlHAcNlvNLo586ZjIBWoE1m72oGkgf7L8=;
        b=KH4MmjEB7PLbHhZLRkPF+xZyh1y8pZoTL19R+uFRhYJ9l33CEBWrtz8w5obSRvWaHih706
        XA8e3prCkK7aD9awPjuJ6N7csv8i57WsD1jze6BVeODjYZNq3OCpVK41hhyUEqnN4UK5m+
        Ndmp5Fc5b/1EKhnGTFdKiSBgJO8ea/8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-442-ziYmnt3tOQKytvq-K5_f5w-1; Thu, 14 Jan 2021 07:22:06 -0500
X-MC-Unique: ziYmnt3tOQKytvq-K5_f5w-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 89C681005E4A;
        Thu, 14 Jan 2021 12:22:05 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.51])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C5DDA19C47;
        Thu, 14 Jan 2021 12:22:00 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Wei Huang <wei.huang2@amd.com>, Bandan Das <bsd@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] Add a reproducer for the AMD nested virtualization errata
Date: Thu, 14 Jan 2021 14:21:59 +0200
Message-Id: <20210114122159.1147290-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While this test doesn't test every case of this errata, it should
reproduce it on all systems where the errata is known to exist.

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 x86/svm_tests.c   | 68 +++++++++++++++++++++++++++++++++++++++++++++++
 x86/unittests.cfg |  2 +-
 2 files changed, 69 insertions(+), 1 deletion(-)

```
#### [RFC PATCH v3 1/2] iommu: Add capability IOMMU_CAP_VIOMMU
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 12018095
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E5C09C433DB
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:42:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AEADE23436
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:42:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727860AbhANBlt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 20:41:49 -0500
Received: from mga11.intel.com ([192.55.52.93]:41684 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727823AbhANBls (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 20:41:48 -0500
IronPort-SDR: 
 RaUoTjZiBmCHui8xFVLFb7sem/iA1FvA2IWD8DR+x7eeE+QFNzS8WyOXWMBp1L9G3KKj6Zhos9
 eCCMVv1YBgtw==
X-IronPort-AV: E=McAfee;i="6000,8403,9863"; a="174786159"
X-IronPort-AV: E=Sophos;i="5.79,345,1602572400";
   d="scan'208";a="174786159"
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jan 2021 17:38:24 -0800
IronPort-SDR: 
 pn1dl9IBHiG0ZLke/ddfHTH+J+J3s550xpbrnvKnzRL+7+3/XUH1L9nveDzCPWCvl1SxaA/1R9
 Wyo+suoELB9A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,345,1602572400";
   d="scan'208";a="569582521"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jan 2021 17:38:18 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: tglx@linutronix.de, ashok.raj@intel.com, kevin.tian@intel.com,
        dave.jiang@intel.com, megha.dey@intel.com, dwmw2@infradead.org
Cc: alex.williamson@redhat.com, bhelgaas@google.com,
        dan.j.williams@intel.com, will@kernel.org, joro@8bytes.org,
        dmaengine@vger.kernel.org, eric.auger@redhat.com,
        jacob.jun.pan@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        kwankhede@nvidia.com, linux-kernel@vger.kernel.org,
        linux-pci@vger.kernel.org, iommu@lists.linux-foundation.org,
        maz@kernel.org, mona.hossain@intel.com, netanelg@mellanox.com,
        parav@mellanox.com, pbonzini@redhat.com, rafael@kernel.org,
        samuel.ortiz@intel.com, sanjay.k.kumar@intel.com,
        shahafs@mellanox.com, tony.luck@intel.com, vkoul@kernel.org,
        yan.y.zhao@linux.intel.com, yi.l.liu@intel.com, leon@kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [RFC PATCH v3 1/2] iommu: Add capability IOMMU_CAP_VIOMMU
Date: Thu, 14 Jan 2021 09:30:02 +0800
Message-Id: <20210114013003.297050-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210114013003.297050-1-baolu.lu@linux.intel.com>
References: <20210114013003.297050-1-baolu.lu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some vendor IOMMU drivers are able to declare that it is running in a VM
context. This is very valuable for the features that only want to be
supported on bare metal. Add a capability bit so that it could be used.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel/iommu.c  | 20 ++++++++++++++++++++
 drivers/iommu/virtio-iommu.c |  9 +++++++++
 include/linux/iommu.h        |  1 +
 3 files changed, 30 insertions(+)

```
#### [PATCH 03/10] KVM: x86: hyper-v: add a blank line to remove building warnings
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12018781
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-19.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 865DCC433E6
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 07:56:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5063A238EA
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 07:56:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727981AbhANHza (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 02:55:30 -0500
Received: from mail.kernel.org ([198.145.29.99]:56964 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727839AbhANHzL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 02:55:11 -0500
Received: by mail.kernel.org (Postfix) with ESMTPSA id CA624233FD;
        Thu, 14 Jan 2021 07:53:49 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1610610830;
        bh=TrTQY3hajtzLk4b1OtE5yfKC0rZRhinwUQjn/1F4J0M=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=szafSbjx4BpAyqfIGLJSc9RiCobHoiCKUGdi8h9VPYgM03qq9ITPDEoQjFXd+4e2F
         wprL2LmT1ccAyVW/Yj8p8dQ6q8Tj0SjHxWbdEE03c0gP0Xyb1Sdl82fkv9OHl7jm74
         58mQZA79eTj0sZynB1HGp5/J82ffaZRg+uqyg7HWfDQU9z655sZdNLPNvwslr/iFeS
         jwNs0A3Bz/VGnIMxWLmBAW4wP1WdZo65cEyGaxFmee/AQg8S0v+SNFoKA10Ng03+D9
         UXLUdbfeMW88C0kIBeVu+MsBpI8KHQTQBLWWR/q3Lox41iTBIgAmX37JzKLYctyWfN
         pS4tAoDNd0oag==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1kzxRz-00EPu7-63; Thu, 14 Jan 2021 08:53:47 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Jonathan Corbet <corbet@lwn.net>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Linux Doc Mailing List" <linux-doc@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 03/10] KVM: x86: hyper-v: add a blank line to remove building
 warnings
Date: Thu, 14 Jan 2021 08:53:38 +0100
Message-Id: 
 <a5a20cd7ff9870b5316825fa1abad0b867832700.1610610444.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <cover.1610610444.git.mchehab+huawei@kernel.org>
References: <cover.1610610444.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

.../Documentation/virt/kvm/api.rst:4536: WARNING: Unexpected indentation.
.../Documentation/virt/kvm/api.rst:4538: WARNING: Block quote ends without a blank line; unexpected unindent.

Fixes: c21d54f0307f ("KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl")
Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/api.rst | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/6] KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12019229
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No,
 score=-17.0 required=3.0 tests=BAYES_00,INCLUDES_CR_TRAILER,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 993A7C433E6
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:57:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4DD1F23A3B
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:57:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726688AbhANK5c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 05:57:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:37158 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726236AbhANK5c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 05:57:32 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 8B70F23A50;
        Thu, 14 Jan 2021 10:56:51 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l00J7-007Tvz-Nj; Thu, 14 Jan 2021 10:56:49 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com,
        Peter Maydell <peter.maydell@linaro.org>
Subject: [PATCH 1/6] KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
Date: Thu, 14 Jan 2021 10:56:28 +0000
Message-Id: <20210114105633.2558739-2-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
In-Reply-To: <20210114105633.2558739-1-maz@kernel.org>
References: <20210114105633.2558739-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, kernel-team@android.com,
 peter.maydell@linaro.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The AArch32 CP14 DBGDIDR has bit 15 set to RES1, which our current
emulation doesn't set. Just add the missing bit.

Reported-by: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/sys_regs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
##### From: Eric Auger <eric.auger@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12019163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C3425C433E0
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:39:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7C73023A50
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:39:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728283AbhANKit (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 05:38:49 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43903 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727974AbhANKis (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Jan 2021 05:38:48 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610620643;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=oKdwrjYJNoYhljc3HaThzszr/6Fqa60W1Mc5o3lCwaY=;
        b=HQ2ji2VvDWjnbBi+vGHBLrIvdGQIvFLbazn9PHuZX/DdxsHHp220Y1+BNp84g79guYTLEU
        gix3k95vWXqHjfBi+CSWZGe3fD2fLExBQV3CQ23acxLGPBsixXVtfJ9sGixOuHjLsaaJkQ
        4/ljrRx+ZnJoSTFcl8+ItVfd44v6mWE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-314-eE_13MMTPVCU9lBs4wkM2g-1; Thu, 14 Jan 2021 05:37:21 -0500
X-MC-Unique: eE_13MMTPVCU9lBs4wkM2g-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA3281009456;
        Thu, 14 Jan 2021 10:37:19 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-165.ams2.redhat.com
 [10.36.114.165])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E266612D7E;
        Thu, 14 Jan 2021 10:37:16 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com
Cc: alexandru.elisei@arm.com, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH v2 1/9] KVM: arm64: vgic-v3: Fix some error codes when setting
 RDIST base
Date: Thu, 14 Jan 2021 11:37:00 +0100
Message-Id: <20210114103708.26763-2-eric.auger@redhat.com>
In-Reply-To: <20210114103708.26763-1-eric.auger@redhat.com>
References: <20210114103708.26763-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM_DEV_ARM_VGIC_GRP_ADDR group doc says we should return
-EEXIST in case the base address of the redist is already set.
We currently return -EINVAL.

However we need to return -EINVAL in case a legacy REDIST address
is attempted to be set while REDIST_REGIONS were set. This case
is discriminated by looking at the count field.

Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

v1 -> v2:
- simplify the check sequence
---
 arch/arm64/kvm/vgic/vgic-mmio-v3.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12019291
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0099EC433E0
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 11:28:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B46BC23A34
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 11:28:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727287AbhANL2C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 06:28:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:53936 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725982AbhANL2B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 06:28:01 -0500
Received: from mail-pl1-x636.google.com (mail-pl1-x636.google.com
 [IPv6:2607:f8b0:4864:20::636])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 70348C061574;
        Thu, 14 Jan 2021 03:27:15 -0800 (PST)
Received: by mail-pl1-x636.google.com with SMTP id b8so2769059plx.0;
        Thu, 14 Jan 2021 03:27:15 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=+ahAs1amo347RNXkYJWCZ9woGbW2UnM8CDWcOU1vF2o=;
        b=D/jG69CXI0DgiRLmOMiDexv151tVKOYLHzy7fqOI/Ojwr89bsBjpxk1jyjQbg6IyON
         HXKaOUzJOkB+WrW7inSnTeyzK4I4zZlI7MSXAXjCHer2yprVG4fAJ2n8KX6aB6JgNMD8
         FvMepAHoM44bmfY42U9MsZd6u1Huavhd5T/bjetdnBBJ/qYp5A+qR3jTwq7FCPhRNMvG
         mQs//5KPzdbOU0WOKlrfXT+cRvS8dqix5NM/E1cIiLyFX6TQYqQuui7aoIsr12iDExJD
         VpFRwNfoO1AfZ/QuG06nag5QEAI3ttJm6jYRGj3GVapfbgVVUUb7SOqq+/uA1qqnZs+M
         q7+Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=+ahAs1amo347RNXkYJWCZ9woGbW2UnM8CDWcOU1vF2o=;
        b=GqPp7FU2XN50oEXw6BeyvD9+bUxhBtJDzfAnoXH+GtYOdDLUGIaujCTQTSZ1ZW87cc
         MbAmtgtJEDgoOMLIL//9idGUevXz1wCXGYmcABClbDPS/t3o+SwLHGFfVOOl9q70GAza
         er2c7nHA2mUti8G9aPCoE4U6B5ZE1hk/D9B+Gm5idpx0jalcQPRta1wwOYJyIpSHNEfX
         aOIg8vnheGDllLPVAOBbkr0h8oHjDGicvytIlLhLPoThUu07ctzG02PpFUauS8LtnFxd
         Qs/xwbRdjHF2ztd3Mi1DkmELHhAeTn1/MxuzO/MHxEReoalDxGwKo+mLmGhD/kXaqaxd
         Znsg==
X-Gm-Message-State: AOAM532ubTHHKoyzxc+33G00zV2N478/C4n4PGqGSB7RuopZLlLqsKjv
        re/fyatuWgPMs8IrA/9RGvc+61R9bsI=
X-Google-Smtp-Source: 
 ABdhPJy7Da3wPrakUrDmoeu8jQQd+au8pjcn3oxJWf4szYLgljbRKTt+QfxsIyf++DNDfvEhYM0h2w==
X-Received: by 2002:a17:90a:d3cc:: with SMTP id
 d12mr4426882pjw.202.1610623634764;
        Thu, 14 Jan 2021 03:27:14 -0800 (PST)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 c24sm563629pjs.3.2021.01.14.03.27.12
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 14 Jan 2021 03:27:14 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [PATCH] KVM: kvmclock: Fix vCPUs > 64 can't be online/hotpluged
Date: Thu, 14 Jan 2021 19:27:03 +0800
Message-Id: <1610623624-18697-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The per-cpu vsyscall pvclock data pointer assigns either an element of the 
static array hv_clock_boot (#vCPU <= 64) or dynamically allocated memory 
hvclock_mem (vCPU > 64), the dynamically memory will not be allocated if 
kvmclock vsyscall is disabled, this can result in cpu hotpluged fails in 
kvmclock_setup_percpu() which returns -ENOMEM. This patch fixes it by not 
assigning vsyscall pvclock data pointer if kvmclock vdso_clock_mode is not 
VDSO_CLOCKMODE_PVCLOCK.

Fixes: 6a1cac56f4 ("x86/kvm: Use __bss_decrypted attribute in shared variables")
Reported-by: Zelin Deng <zelin.deng@linux.alibaba.com>
Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: stable@vger.kernel.org#v4.19-rc5+
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kernel/kvmclock.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 01/14] KVM: SVM: Zero out the VMCB array used to track SEV ASID association
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12018159
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 15926C433DB
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:49:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C5F9A235F8
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:49:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728447AbhANBso (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 20:48:44 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55694 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729928AbhANAi0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 19:38:26 -0500
Received: from mail-qv1-xf4a.google.com (mail-qv1-xf4a.google.com
 [IPv6:2607:f8b0:4864:20::f4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 93BF2C06179F
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 16:37:37 -0800 (PST)
Received: by mail-qv1-xf4a.google.com with SMTP id f7so2947251qvr.4
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 16:37:37 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:in-reply-to:message-id:mime-version:references
         :subject:from:to:cc;
        bh=+lfNaOH1CNuPDcxuYVHAHObVf+9wEEDIr0zVJxlAHxg=;
        b=gIjihO2I8gwcFheB4YOs8u4uVfZFwXse/1YgRjreNWQX/e2LFZ9vHhNU3O2UbMJppT
         hbZqpHYf8uNM9lVGC2jEABPKdK+55wkuZSf/POIfMsZ5LvFBacWcKJNaPDRCFWSRout+
         uMFxXkDz0idqm68ZyJ+iooMcEsfRvxeGZcE3jvqoHKICY5e/jlJ/Ce3WTRib5aCm+2mn
         UAxR2lfbyXAMgnM+w0ZAZdihFN2j4rNDsAn9pUY2X9QzpGeBGYiPFnqtIdSFRglaIAJC
         iory/Ch11tHGh9uc9FOYACz9x3TLLUhe0ZhJRFn9WwPDIRkKFroNhMwGXCzZWhWHkV8f
         7GRQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:in-reply-to:message-id
         :mime-version:references:subject:from:to:cc;
        bh=+lfNaOH1CNuPDcxuYVHAHObVf+9wEEDIr0zVJxlAHxg=;
        b=l32vKdMwJ+UhSAZ7C0Ayr51RJ+53ff4+HmjBgmsmptmkIDjKiLvBZKb75w64WxzXZn
         3jt9OdgL78+Wi9FZA/n3AAeC1R22DGwP8zfGayBNzXqBlJ+L6Z6bZoRJWQWAUY04ZnkL
         2xL4gBClxyqiAdGim6AqZA9N0M8rRYU44yX/5O6swu43EqPL1AJm/tWyVzfroboXmNco
         DP5LB1wlRP1AwlgzdbRBAzBZhX+iyOyJObKK5qI5o0BSLpmZuTEeGhLxpASbOlmgHUlO
         agoCnDh29jR35PMpcOyDrzIGOWhfIQwYbqR1iJPb3P8+nF3Hwz+VVgrOgyhqoirHEb0y
         DGDQ==
X-Gm-Message-State: AOAM5328ovgeqPZZXt7CYOe1Jvapx//IAyzJ14QiW7Z0nOUa/lqmmjgZ
        cUATG0IjvIEJb1Fqwf28shkbokGwrqE=
X-Google-Smtp-Source: 
 ABdhPJz6SZlx5VJJIc17Aooj99sknhXwjukqTwoNewwxv6DIs9ZCRWUkLmY0rTV2mz8FiqTixYZn5yW997c=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:8b:: with SMTP id
 133mr7308631yba.513.1610584656762;
 Wed, 13 Jan 2021 16:37:36 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 13 Jan 2021 16:36:55 -0800
In-Reply-To: <20210114003708.3798992-1-seanjc@google.com>
Message-Id: <20210114003708.3798992-2-seanjc@google.com>
Mime-Version: 1.0
References: <20210114003708.3798992-1-seanjc@google.com>
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH v2 01/14] KVM: SVM: Zero out the VMCB array used to track SEV
 ASID association
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Borislav Petkov <bp@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Zero out the array of VMCB pointers so that pre_sev_run() won't see
garbage when querying the array to detect when an SEV ASID is being
associated with a new VMCB.  In practice, reading random values is all
but guaranteed to be benign as a false negative (which is extremely
unlikely on its own) can only happen on CPU0 on the first VMRUN and would
only cause KVM to skip the ASID flush.  For anything bad to happen, a
previous instance of KVM would have to exit without flushing the ASID,
_and_ KVM would have to not flush the ASID at any time while building the
new SEV guest.

Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Fixes: 70cd94e60c73 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Sean Christopherson <seanjc@google.com>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
---
 arch/x86/kvm/svm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 1/3] KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2 map
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12019389
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BAFE0C43331
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EA9C23877
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:15:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729044AbhANMOt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 07:14:49 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11385 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728036AbhANMOr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 07:14:47 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DGjrD6PJFz7VLh;
        Thu, 14 Jan 2021 20:13:00 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Thu, 14 Jan 2021 20:13:53 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v3 1/3] KVM: arm64: Adjust partial code of hyp stage-1 map and
 guest stage-2 map
Date: Thu, 14 Jan 2021 20:13:48 +0800
Message-ID: <20210114121350.123684-2-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20210114121350.123684-1-wangyanan55@huawei.com>
References: <20210114121350.123684-1-wangyanan55@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Procedures of hyp stage-1 map and guest stage-2 map are quite different,
but they are tied closely by function kvm_set_valid_leaf_pte().
So adjust the relative code for ease of code maintenance in the future.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Yanan Wang <wangyanan55@huawei.com>
---
 arch/arm64/kvm/hyp/pgtable.c | 55 ++++++++++++++++++------------------
 1 file changed, 28 insertions(+), 27 deletions(-)

```
#### [PATCH v2 1/3] KVM: nVMX: Always call sync_vmcs02_to_vmcs12_rare on migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12020903
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A838BC433E6
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 20:56:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6C03B23A79
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 20:56:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729235AbhANU4e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 15:56:34 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:58551 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727152AbhANU4d (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Jan 2021 15:56:33 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610657707;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Sjyxhinw36uvHQq417p5mpNAZODTNW/mmcrP3tZ/skE=;
        b=WZr/O74j5Dsw1IamrVLKi+7cnLkeXwRrbeuYuu06UWcUJ/BvO4c6pidjZJLAGmBm4c9nOk
        z/X3XEzEvNtnRazBMxclA4aLpNpppVBVU7adtSX2xsGp3sgOz1zQRzw3wQPcM4EsQsYvh7
        UoB0iJtwaefNXd5OpE6omKMw4tRDLnM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-51-zCpK3h7iOsy7slLYsyEwHA-1; Thu, 14 Jan 2021 15:55:03 -0500
X-MC-Unique: zCpK3h7iOsy7slLYsyEwHA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 76082107ACF9;
        Thu, 14 Jan 2021 20:55:00 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.51])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA5E25C1C5;
        Thu, 14 Jan 2021 20:54:55 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>, x86@kernel.org,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 1/3] KVM: nVMX: Always call sync_vmcs02_to_vmcs12_rare on
 migration
Date: Thu, 14 Jan 2021 22:54:47 +0200
Message-Id: <20210114205449.8715-2-mlevitsk@redhat.com>
In-Reply-To: <20210114205449.8715-1-mlevitsk@redhat.com>
References: <20210114205449.8715-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even when we are outside the nested guest, some vmcs02 fields
are not in sync vs vmcs12.

However during the migration, the vmcs12 has to be up to date
to be able to load it later after the migration.

To fix that, call that function.

Fixes: 7952d769c29ca ("KVM: nVMX: Sync rarely accessed guest fields only when needed")

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 13 ++++++++-----
 1 file changed, 8 insertions(+), 5 deletions(-)

```
