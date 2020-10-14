#### [PATCH] Fixed vfio-fsl-mc driver compilation on 32 bit
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The FSL_MC_BUS on which the VFIO-FSL-MC driver is dependent on
can be compiled on other architectures as well (not only ARM64)
including 32 bit architectures.
Include linux/io-64-nonatomic-hi-lo.h to make writeq/readq used
in the driver available on 32bit platforms.

Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 drivers/vfio/fsl-mc/vfio_fsl_mc.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCHv2] unittests.cfg: Increase timeout for apic test
##### From: Po-Hsu Lin <po-hsu.lin@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Po-Hsu Lin <po-hsu.lin@canonical.com>
X-Patchwork-Id: 11835233
Return-Path: <SRS0=tiWW=DU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B712F14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 09:14:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A462620E65
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 09:14:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404228AbgJMJOb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 05:14:31 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:45946 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2403911AbgJMJOb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 05:14:31 -0400
Received: from mail-pj1-f70.google.com ([209.85.216.70])
        by youngberry.canonical.com with esmtps
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <po-hsu.lin@canonical.com>)
        id 1kSGO5-0007Ic-HY
        for kvm@vger.kernel.org; Tue, 13 Oct 2020 09:14:29 +0000
Received: by mail-pj1-f70.google.com with SMTP id r1so1820078pjp.5
        for <kvm@vger.kernel.org>; Tue, 13 Oct 2020 02:14:29 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=VNJOKkvPfRVJ4oA2MF0E6/OVvHsrdR5Ytgp8RCYFYlY=;
        b=VNBbeZu9qtiyrYse34uDRh6DKS+bRb6BHxYbLv/lFntiOSfJziHk6IhTCdO7a4/Jzl
         kMnVrpBHmx1kUoAOha0d2pPzFcETfo+NzWdj8Fa07gmwryunGCMOTIxoSFfsTtyxqmWP
         Undr8khgm5iG8wuSaXaPgcimcPV6nsrjMtI5yk84nN57v0whkGOxmRCXNn/M/Ra8IGGt
         zR+gKsRSDm7Ot/iRY36sneQ1PPCNgUdqjRceThxzB8lxFLdNyJnDvu0F9kpexPJ/t8Nj
         M02WThCCOb7wtDUqA0GIyl2ZWttbV02FTp9orbC52qt206DIWORMXAdWDsgWHPMCYcV2
         d11A==
X-Gm-Message-State: AOAM533eY3smldd2Ww39cUKoeNgDJJDZHBkFSqRq8LLX6mJdCCTpDoTl
        GSZpo//MViwCo8iKFH2uePyfhVfLQDPYcMFTezas6OY/q47x5tFpGJ5XPUusE+F9ySLA0jSnvE/
        lEGW2TTGAk71W6mjpNK9KdpBK21Wp
X-Received: by 2002:aa7:93b6:0:b029:155:3b0b:d47a with SMTP id
 x22-20020aa793b60000b02901553b0bd47amr23779681pff.47.1602580467914;
        Tue, 13 Oct 2020 02:14:27 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwgkPdSOroV9BNlKuvtOXnMSHizdH5O609f2SgXbAJfwi//GVI3+Ao6/PO6xSCXVyC2IVavwQ==
X-Received: by 2002:aa7:93b6:0:b029:155:3b0b:d47a with SMTP id
 x22-20020aa793b60000b02901553b0bd47amr23779665pff.47.1602580467618;
        Tue, 13 Oct 2020 02:14:27 -0700 (PDT)
Received: from localhost.localdomain ([2001:67c:1560:8007::aac:c227])
        by smtp.gmail.com with ESMTPSA id
 m22sm21112458pfk.214.2020.10.13.02.14.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 13 Oct 2020 02:14:26 -0700 (PDT)
From: Po-Hsu Lin <po-hsu.lin@canonical.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: po-hsu.lin@canonical.com
Subject: [kvm-unit-tests PATCHv2] unittests.cfg: Increase timeout for apic
 test
Date: Tue, 13 Oct 2020 17:12:37 +0800
Message-Id: <20201013091237.67132-1-po-hsu.lin@canonical.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We found that on Azure cloud hyperv instance Standard_D48_v3, it will
take about 45 seconds to run this apic test.

It takes even longer (about 150 seconds) to run inside a KVM instance
VM.Standard2.1 on Oracle cloud.

Bump the timeout threshold to give it a chance to finish.

Signed-off-by: Po-Hsu Lin <po-hsu.lin@canonical.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2] x86: vmx: Add test for SIPI signal processing
##### From: yadong.qi@intel.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Qi, Yadong" <yadong.qi@intel.com>
X-Patchwork-Id: 11834973
Return-Path: <SRS0=tiWW=DU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B6ACF14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 05:31:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9218C208FE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 05:31:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732404AbgJMF3L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 01:29:11 -0400
Received: from mga18.intel.com ([134.134.136.126]:27641 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726963AbgJMF3K (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 01:29:10 -0400
IronPort-SDR: 
 rxEe78uO7kC68cnBsfFEPr66z2ezXHQJh2+HY+/0CEOAJn8LPvu7PUncNf5PNUPvM1RztMRg2T
 xYm+GrWJ8v5g==
X-IronPort-AV: E=McAfee;i="6000,8403,9772"; a="153683401"
X-IronPort-AV: E=Sophos;i="5.77,369,1596524400";
   d="scan'208";a="153683401"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 12 Oct 2020 22:29:09 -0700
IronPort-SDR: 
 VZ/hPyiLtVwzDDjIwiOv0sOe1BhH1ZnJ0bmmbf2SOsKxbhZvwpCTyTaT1d6nRP+6iRbSk0dE+O
 CcbpptfVhtQg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,369,1596524400";
   d="scan'208";a="463360037"
Received: from yadong-antec.sh.intel.com ([10.239.158.61])
  by orsmga004.jf.intel.com with ESMTP; 12 Oct 2020 22:29:07 -0700
From: yadong.qi@intel.com
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, nadav.amit@gmail.com,
        Yadong Qi <yadong.qi@intel.com>
Subject: [kvm-unit-tests PATCH v2] x86: vmx: Add test for SIPI signal
 processing
Date: Tue, 13 Oct 2020 13:28:45 +0800
Message-Id: <20201013052845.249113-1-yadong.qi@intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yadong Qi <yadong.qi@intel.com>

The test verifies the following functionality:
A SIPI signal received when CPU is in VMX non-root mode:
    if ACTIVITY_STATE == WAIT_SIPI
        VMExit with (reason == 4)
    else
        SIPI signal is ignored

The test cases depends on IA32_VMX_MISC:bit(8), if this bit is 1
then the test cases would be executed, otherwise the test cases
would be skiped.

Signed-off-by: Yadong Qi <yadong.qi@intel.com>
---
v1->v2:
 * update CR3 on AP

---
 lib/x86/msr.h       |   1 +
 lib/x86/processor.h |   5 ++
 x86/apic.c          |   5 --
 x86/ioapic.c        |   5 --
 x86/unittests.cfg   |   8 +++
 x86/vmx.c           |   2 +-
 x86/vmx.h           |   3 +
 x86/vmx_tests.c     | 138 ++++++++++++++++++++++++++++++++++++++++++++
 8 files changed, 156 insertions(+), 11 deletions(-)

```
#### [PATCH 1/9] genirq/irqdomain: Implement get_name() method on irqchip fwnodes
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11835173
Return-Path: <SRS0=tiWW=DU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9637815E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 08:12:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6EE74214D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 08:12:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="Q+cMUieQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391266AbgJMIM6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 13 Oct 2020 04:12:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34072 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391063AbgJMIMI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 13 Oct 2020 04:12:08 -0400
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 18374C0613D7;
        Tue, 13 Oct 2020 01:12:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=EY8UHzC6+5/iDJsfDzabkl6LPehqG3ZtEqYxa4ewh6o=;
 b=Q+cMUieQWgDbWqlRk6eSdi2Goq
        w4opBNGckPwtNox/hjjkpzSKduFWkniiM62a9BNOz3omxqd7LmwuhvMMfKHhmvneRc2Y7q9Emk3IJ
        Gpq790hBMJOcSHeWvqDUp6HKrwkJkMcJT1o7eaiQDcZiqt+B82cdLbRHNpwwyVPibK/LszJfwbTKQ
        RCo0fhNtVRokIeFP3g5qGTj+LK/1pbZUHMuGcyAbofjzW7kGsyI4LiIGfsuUxJtL+/m8pJBLGeHLc
        3e/mg0uhAKUDX5nzK7YFhfi+ZDgKDC4BJPfudyanlNWmGHWWF0s1GHbq/BJDAE68MXZX36ehTaI/X
        CMZ69h8A==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kSFPM-0006fO-Qj; Tue, 13 Oct 2020 08:12:01 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kSFPM-006XXM-CG; Tue, 13 Oct 2020 09:11:44 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, iommu@lists.linux-foundation.org,
        joro@8bytes.org, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org, maz@misterjones.org
Subject: [PATCH 1/9] genirq/irqdomain: Implement get_name() method on irqchip
 fwnodes
Date: Tue, 13 Oct 2020 09:11:31 +0100
Message-Id: <20201013081139.1558200-2-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201013081139.1558200-1-dwmw2@infradead.org>
References: <0de733f6384874d68afba2606119d0d9b1e8b34e.camel@infradead.org>
 <20201013081139.1558200-1-dwmw2@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
---
 kernel/irq/irqdomain.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v2] vfio/fsl-mc: Fixed vfio-fsl-mc driver compilation on 32 bit
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The FSL_MC_BUS on which the VFIO-FSL-MC driver is dependent on
can be compiled on other architectures as well (not only ARM64)
including 32 bit architectures.
Include linux/io-64-nonatomic-hi-lo.h to make writeq/readq used
in the driver available on 32bit platforms.

Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
v1 --> v2
 - Added prefix to patch description

 drivers/vfio/fsl-mc/vfio_fsl_mc.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] vfio/platform: Replace spin_lock_irqsave by spin_lock in hard IRQ
##### From: Tian Tao <tiantao6@hisilicon.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tian Tao <tiantao6@hisilicon.com>
X-Patchwork-Id: 11834873
Return-Path: <SRS0=tiWW=DU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4FB5017D1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 02:45:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3AB8C20678
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 13 Oct 2020 02:45:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728499AbgJMCAV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 12 Oct 2020 22:00:21 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:15205 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728492AbgJMCAV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Oct 2020 22:00:21 -0400
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 6723A2474EE92E0AD1B6;
        Tue, 13 Oct 2020 10:00:18 +0800 (CST)
Received: from localhost.localdomain (10.69.192.56) by
 DGGEMS408-HUB.china.huawei.com (10.3.19.208) with Microsoft SMTP Server id
 14.3.487.0; Tue, 13 Oct 2020 10:00:10 +0800
From: Tian Tao <tiantao6@hisilicon.com>
To: <eric.auger@redhat.com>, <alex.williamson@redhat.com>,
        <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <song.bao.hua@hisilicon.com>
CC: <linuxarm@huawei.com>
Subject: [PATCH] vfio/platform: Replace spin_lock_irqsave by spin_lock in hard
 IRQ
Date: Tue, 13 Oct 2020 10:00:58 +0800
Message-ID: <1602554458-26927-1-git-send-email-tiantao6@hisilicon.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
X-Originating-IP: [10.69.192.56]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It is redundant to do irqsave and irqrestore in hardIRQ context.

Signed-off-by: Tian Tao <tiantao6@hisilicon.com>
---
 drivers/vfio/platform/vfio_platform_irq.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
