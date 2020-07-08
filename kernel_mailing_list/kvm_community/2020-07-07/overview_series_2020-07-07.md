#### [PATCH v2 1/4] x86/cpufeatures: Add enumeration for SERIALIZE instruction
##### From: Cathy Zhang <cathy.zhang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Zhang <cathy.zhang@intel.com>
X-Patchwork-Id: 11647343
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9195618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 02:21:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C8FD8206F6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 02:21:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727869AbgGGCVu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 22:21:50 -0400
Received: from mga01.intel.com ([192.55.52.88]:27533 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727818AbgGGCVt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 22:21:49 -0400
IronPort-SDR: 
 8zPgb0rk8JpSItB9tH9ZExBcMunZXptqlhKc8dqpylig4MUPgodPHLHT/9f/xmDC1DEsGKot2Z
 RFEKvTx6AqRg==
X-IronPort-AV: E=McAfee;i="6000,8403,9674"; a="165601315"
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="165601315"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Jul 2020 19:21:49 -0700
IronPort-SDR: 
 TLZ0mnRcBfUrdDviTVvmweLBil3ZwiBntpc2hPMYfb7WZR3Z/jAlt+19hA/A89zGV1NDSW/Bw7
 wcNUeko2r5Ew==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="357633729"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.238.156.127])
  by orsmga001.jf.intel.com with ESMTP; 06 Jul 2020 19:21:43 -0700
From: Cathy Zhang <cathy.zhang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        joro@8bytes.org, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, ricardo.neri-calderon@linux.intel.com,
        kyung.min.park@intel.com, jpoimboe@redhat.com,
        gregkh@linuxfoundation.org, ak@linux.intel.com,
        dave.hansen@intel.com, tony.luck@intel.com,
        ravi.v.shankar@intel.com, Cathy Zhang <cathy.zhang@intel.com>
Subject: [PATCH v2 1/4] x86/cpufeatures: Add enumeration for SERIALIZE
 instruction
Date: Tue,  7 Jul 2020 10:16:20 +0800
Message-Id: <1594088183-7187-2-git-send-email-cathy.zhang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594088183-7187-1-git-send-email-cathy.zhang@intel.com>
References: <1594088183-7187-1-git-send-email-cathy.zhang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This instruction gives software a way to force the processor to complete
all modifications to flags, registers and memory from previous instructions
and drain all buffered writes to memory before the next instruction is
fetched and executed.

The same effect can be obtained using the cpuid instruction. However,
cpuid causes modification on the eax, ebx, ecx, and ecx regiters; it
also causes a VM exit.

A processor supports SERIALIZE instruction if CPUID.0x0x.0x0:EDX[14] is
present. The CPU feature flag is shown as "serialize" in /proc/cpuinfo.

Detailed information on the instructions and CPUID feature flag SERIALIZE
can be found in the latest Intel Architecture Instruction Set Extensions
and Future Features Programming Reference and Intel 64 and IA-32
Architectures Software Developer's Manual.

Signed-off-by: Ricardo Neri <ricardo.neri-calderon@linux.intel.com>
Signed-off-by: Cathy Zhang <cathy.zhang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/2] iommu: iommu_aux_at(de)tach_device() extension
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11647279
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B42C618
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 01:44:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3D20D20723
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 01:44:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727905AbgGGBoj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 6 Jul 2020 21:44:39 -0400
Received: from mga03.intel.com ([134.134.136.65]:40649 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727869AbgGGBoi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 6 Jul 2020 21:44:38 -0400
IronPort-SDR: 
 Rv2GJjuOfoZ9WhZAhEOHw2xRJEaNbqN2hHZr/laeQyREollWhmblfE3+76aAbDbk0hYespferH
 aai5TeJAW0cw==
X-IronPort-AV: E=McAfee;i="6000,8403,9674"; a="147536126"
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="147536126"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Jul 2020 18:44:37 -0700
IronPort-SDR: 
 r2MissJE+dKEGoM0n2MM/jZq/XvM0p1cLGMyoJVK5k4cwJx0TeWEtoYMFm5KqbGfyPA4zbYqOr
 Z+en8dUeNW8g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,321,1589266800";
   d="scan'208";a="266688930"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga007.fm.intel.com with ESMTP; 06 Jul 2020 18:44:35 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Robin Murphy <robin.murphy@arm.com>
Cc: Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v2 1/2] iommu: iommu_aux_at(de)tach_device() extension
Date: Tue,  7 Jul 2020 09:39:56 +0800
Message-Id: <20200707013957.23672-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200707013957.23672-1-baolu.lu@linux.intel.com>
References: <20200707013957.23672-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The hardware assistant vfio mediated device is a use case of iommu
aux-domain. The interactions between vfio/mdev and iommu during mdev
creation and passthr are:

- Create a group for mdev with iommu_group_alloc();
- Add the device to the group with
        group = iommu_group_alloc();
        if (IS_ERR(group))
                return PTR_ERR(group);

        ret = iommu_group_add_device(group, &mdev->dev);
        if (!ret)
                dev_info(&mdev->dev, "MDEV: group_id = %d\n",
                         iommu_group_id(group));
- Allocate an aux-domain
        iommu_domain_alloc()
- Attach the aux-domain to the physical device from which the mdev is
  created.
        iommu_aux_attach_device()

In the whole process, an iommu group was allocated for the mdev and an
iommu domain was attached to the group, but the group->domain leaves
NULL. As the result, iommu_get_domain_for_dev() doesn't work anymore.

The iommu_get_domain_for_dev() is a necessary interface for device
drivers that want to support aux-domain. For example,

        struct iommu_domain *domain;
        struct device *dev = mdev_dev(mdev);
        unsigned long pasid;

        domain = iommu_get_domain_for_dev(dev);
        if (!domain)
                return -ENODEV;

        pasid = iommu_aux_get_pasid(domain, dev->parent);
        if (pasid == IOASID_INVALID)
                return -EINVAL;

         /* Program the device context with the PASID value */
         ....

This extends iommu_aux_at(de)tach_device() so that the users could pass
in an optional device pointer (struct device for vfio/mdev for example),
and the necessary check and data link could be done.

Fixes: a3a195929d40b ("iommu: Add APIs for multiple domains per device")
Cc: Robin Murphy <robin.murphy@arm.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c           | 86 +++++++++++++++++++++++++++++----
 drivers/vfio/vfio_iommu_type1.c |  5 +-
 include/linux/iommu.h           | 12 +++--
 3 files changed, 87 insertions(+), 16 deletions(-)

```
#### [PATCH] KVM: arm64: Don't use has_vhe() for CHOOSE_HYP_SYM()
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11648903
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 33FBD92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 15:12:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1C91120773
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 15:12:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1594134722;
	bh=C4bPJbq0e1P34S5uLx3jO+V10U+5mus3QC4vneFLX1Y=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ZZEsyADK3mE18cWPxPVgbAR1gSfzIa7Z3c/cc4lYcgBWp+ZVHgh9i/wbKDnX6lTkO
	 rEUfuBQCxWs473FtZUp2BApYucinnslYbbcSIH6heDemIpz8hFasTu0hEUB4SdHaTC
	 zLabhXGEUR5HyIk1tu8f+HNJJgBOa2QTQ14k6RT8=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728172AbgGGPMB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 11:12:01 -0400
Received: from mail.kernel.org ([198.145.29.99]:52708 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726911AbgGGPMA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 11:12:00 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1BAF52065D;
        Tue,  7 Jul 2020 15:12:00 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1594134720;
        bh=C4bPJbq0e1P34S5uLx3jO+V10U+5mus3QC4vneFLX1Y=;
        h=From:To:Cc:Subject:Date:From;
        b=frYEk8iaPRhfVRhVtZ5aQCYq7V2EWVUpPQ1xar9FIMJtduC6Os5mcGHmWesD2xu0j
         bxNCIk4f9NvMsPil6ThxO/O7OddeaOOHn2PYV3T/QTBDeqhhHAgqRuAxsXYk1t++rw
         GVsJbkqA7f3SQDK8ZCTW/skBpHyrtMSbJrTVCyXQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=hot-poop.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jspGI-009mGD-I7; Tue, 07 Jul 2020 16:11:58 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com
Subject: [PATCH] KVM: arm64: Don't use has_vhe() for CHOOSE_HYP_SYM()
Date: Tue,  7 Jul 2020 16:11:12 +0100
Message-Id: <20200707151112.2514630-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The recently introduced CHOOSE_HYP_SYM() macro picks one symbol
or another, depending on whether the kernel run as a VHE
hypervisor or not. For that, it uses the has_vhe() helper, which
is itself implemented as a final capability.

Unfortunately, __copy_hyp_vect_bpi now indirectly uses CHOOSE_HYP_SYM
to get the __bp_harden_hyp_vecs symbol, using has_vhe() in the process.
At this stage, the capability isn't final and things explode:

[    0.000000] ACPI: SRAT not present
[    0.000000] percpu: Embedded 34 pages/cpu s101264 r8192 d29808 u139264
[    0.000000] Detected PIPT I-cache on CPU0
[    0.000000] ------------[ cut here ]------------
[    0.000000] kernel BUG at arch/arm64/include/asm/cpufeature.h:459!
[    0.000000] Internal error: Oops - BUG: 0 [#1] PREEMPT SMP
[    0.000000] Modules linked in:
[    0.000000] CPU: 0 PID: 0 Comm: swapper Not tainted 5.8.0-rc4-00080-gd630681366e5 #1388
[    0.000000] pstate: 80000085 (Nzcv daIf -PAN -UAO BTYPE=--)
[    0.000000] pc : check_branch_predictor+0x3a4/0x408
[    0.000000] lr : check_branch_predictor+0x2a4/0x408
[    0.000000] sp : ffff800011693e90
[    0.000000] x29: ffff800011693e90 x28: ffff8000116a1530
[    0.000000] x27: ffff8000112c1008 x26: ffff800010ca6ff8
[    0.000000] x25: ffff8000112c1000 x24: ffff8000116a1320
[    0.000000] x23: 0000000000000000 x22: ffff8000112c1000
[    0.000000] x21: ffff800010177120 x20: ffff8000116ae108
[    0.000000] x19: 0000000000000000 x18: ffff800011965c90
[    0.000000] x17: 0000000000022000 x16: 0000000000000003
[    0.000000] x15: 00000000ffffffff x14: ffff8000118c3a38
[    0.000000] x13: 0000000000000021 x12: 0000000000000022
[    0.000000] x11: d37a6f4de9bd37a7 x10: 000000000000001d
[    0.000000] x9 : 0000000000000000 x8 : ffff800011f8dad8
[    0.000000] x7 : ffff800011965ad0 x6 : 0000000000000003
[    0.000000] x5 : 0000000000000000 x4 : 0000000000000000
[    0.000000] x3 : 0000000000000100 x2 : 0000000000000004
[    0.000000] x1 : ffff8000116ae148 x0 : 0000000000000000
[    0.000000] Call trace:
[    0.000000]  check_branch_predictor+0x3a4/0x408
[    0.000000]  update_cpu_capabilities+0x84/0x138
[    0.000000]  init_cpu_features+0x2c0/0x2d8
[    0.000000]  cpuinfo_store_boot_cpu+0x54/0x64
[    0.000000]  smp_prepare_boot_cpu+0x2c/0x60
[    0.000000]  start_kernel+0x16c/0x574
[    0.000000] Code: 17ffffc7 91010281 14000198 17ffffca (d4210000)

This is addressed using a two-fold process:
- Replace has_vhe() with is_kernel_in_hyp_mode(), which tests
  whether we are running at EL2.
- Make CHOOSE_HYP_SYM() return an *undefined* symbol when
  compiled in the nVHE hypervisor, as we really should never
  use this helper in the nVHE-specific code.

With this in place, we're back to a bootable kernel again.

Fixes: b877e9849d41 ("KVM: arm64: Build hyp-entry.S separately for VHE/nVHE")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/include/asm/kvm_asm.h | 20 +++++++++++++++++++-
 1 file changed, 19 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x/cpumodel: The missing DFP facility on TCG is expected
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11647647
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67E9260D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 05:56:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 482F920739
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 05:56:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EAROSK1L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728114AbgGGF4b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 01:56:31 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:30820 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727827AbgGGF4b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 01:56:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594101388;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=KI7a2ClZlMwCFO1SBXPRqL8eILTZTxkGByXxhshBqFQ=;
        b=EAROSK1LohZqOuLZ8CpsyqoBxoiK9gfV+jGmit/veThXOD5RGmL+OnJ7GRCG4nY4TuinMJ
        ZbIsb0w2TsfpdIckO7cZvNr1f2GyHOcUFxlk8er29JiPi9d6x0NHfNyVx9EhF3MVpjvRDq
        SDk/PkXyQ7NW6NXqpKjVOOSdDemzDjg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-358-s1z1ynX6NUKY6W_P2OnKEQ-1; Tue, 07 Jul 2020 01:56:26 -0400
X-MC-Unique: s1z1ynX6NUKY6W_P2OnKEQ-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B946419067E3;
        Tue,  7 Jul 2020 05:56:25 +0000 (UTC)
Received: from thuth.com (ovpn-112-77.ams2.redhat.com [10.36.112.77])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6A33E70100;
        Tue,  7 Jul 2020 05:56:21 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests PATCH] s390x/cpumodel: The missing DFP facility on
 TCG is expected
Date: Tue,  7 Jul 2020 07:56:19 +0200
Message-Id: <20200707055619.6162-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running the kvm-unit-tests with TCG on s390x, the cpumodel test
always reports the error about the missing DFP (decimal floating point)
facility. This is kind of expected, since DFP is not required for
running Linux and thus nobody is really interested in implementing
this facility in TCG. Thus let's mark this as an expected error instead,
so that we can run the kvm-unit-tests also with TCG without getting
test failures that we do not care about.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/cpumodel.c | 51 ++++++++++++++++++++++++++++++++++++++++++------
 1 file changed, 45 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests v2 PATCH] s390x/cpumodel: The missing DFP facility on TCG is expected
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11648321
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7960E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 10:42:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 60B7720738
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 10:42:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XMJguhhl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727120AbgGGKmQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 06:42:16 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:47602 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726911AbgGGKmQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 06:42:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594118535;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=d/Cdj0P/nQnhxHtwDM4v2QMTaKgZjzQY/xCQv2QzIBo=;
        b=XMJguhhlRhUO/H8jdwliCb4EBO4kCK9wiOUNJXuzH5P7q7AqlFzt1rfCdcKWceAPCZ2cir
        wRVxIccVGRhhkBfktqqx9juzPTIRwzxXdEyXu3//BNo740sW7eGwCjTzxnnK/2u5buDBlH
        ZU/2EBYBBZwN6SyO7W3/bz2kFQRiXCI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-283-6UQ-BGgAO-ucpzXuoZDGJg-1; Tue, 07 Jul 2020 06:42:13 -0400
X-MC-Unique: 6UQ-BGgAO-ucpzXuoZDGJg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E953319253CD;
        Tue,  7 Jul 2020 10:42:11 +0000 (UTC)
Received: from thuth.com (ovpn-112-77.ams2.redhat.com [10.36.112.77])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5046B5F7D8;
        Tue,  7 Jul 2020 10:42:07 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [kvm-unit-tests v2 PATCH] s390x/cpumodel: The missing DFP facility on
 TCG is expected
Date: Tue,  7 Jul 2020 12:42:05 +0200
Message-Id: <20200707104205.25085-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running the kvm-unit-tests with TCG on s390x, the cpumodel test
always reports the error about the missing DFP (decimal floating point)
facility. This is kind of expected, since DFP is not required for
running Linux and thus nobody is really interested in implementing
this facility in TCG. Thus let's mark this as an expected error instead,
so that we can run the kvm-unit-tests also with TCG without getting
test failures that we do not care about.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v2:
 - Rewrote the logic, introduced expected_tcg_fail flag
 - Use manufacturer string instead of VM name to detect TCG

 s390x/cpumodel.c | 49 ++++++++++++++++++++++++++++++++++++++++++------
 1 file changed, 43 insertions(+), 6 deletions(-)

```
#### [PATCH] kvm: x86: Read PDPTEs on CR0.CD and CR0.NW changesFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11650363
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 97CBE13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 22:36:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 803402075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 22:36:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ddIDDwSA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729330AbgGGWgm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 18:36:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43626 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728299AbgGGWgl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 18:36:41 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 917E4C061755
        for <kvm@vger.kernel.org>; Tue,  7 Jul 2020 15:36:41 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id m81so9918839ybf.6
        for <kvm@vger.kernel.org>; Tue, 07 Jul 2020 15:36:41 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=iKsgbuR1fTpH0ZFi8jGnta3z0+1/5i8qIQmX7R8d9a0=;
        b=ddIDDwSAU2FmdCY55ER7+sD8F6BhDGcqVPI60KX3UznCZ29r7IW1XseZe5ol29nDQW
         302TolJ+AgKBxnY7U5N88aBj3W/Z/F0D1xrkGG9mYobua4fcII+rryuhm/7YYBNVW9Xh
         6uNzqLk5um6Jdl6faPbiUMMg/BWJimJqJzSaAMbdaMXnCfigVQmd7EobfD4AWl3M8dWQ
         5K8uSNqHmo8wrIuUfvHuctdH6lBXY0meA2iZvyjSdavFj0l5mc2uXky2ZSM26YKpVygk
         PuduzEcwBJFD/wUs08tLFyRXcO66mhuocTS9FMFgZIXCFZ3bikm3Wa88qeYVkm1XDm70
         /l/w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=iKsgbuR1fTpH0ZFi8jGnta3z0+1/5i8qIQmX7R8d9a0=;
        b=piZmYvfMZZuRgcESG6d3v92WHIpE0ppZdIVj13WUYoM5sqyt0FYPtqHxEJ6qTyEfks
         r+6uswdS9ZpsDT4nlKqbGAWdm873X/gu/pp2rdMUK/W4swGBVc4UQBqfB9eZj6CGmlY6
         tok0tnava336vlQORelpOgghnWssOY63zLHy/EXSIRPeOGZiQm+eWRR4PjeXCLU6jwAC
         pr8riLX+egZq76SL6Ei6hnnKZgayxh0Rm0YePzcd9NbWP6OtEXhKYj7l5KfaBpzjI2kn
         sndYkdxjH42/tSQa2S0hV+WD+Qh0QdaCXbCDJufmRhRSNxTX9OBhmC8Z+flNnhMYOATQ
         mJJQ==
X-Gm-Message-State: AOAM531RCL3X9lL/z1wECBaXm8uAopU+ppx3f6Rfyl7/5jkZXLhGx5NW
        Hn7PB9x+l3VcHrNBRccLd/nV4kmix6yDBZwSAQDDt78brMSQ7ZrvU0pYK8MgY+jPUZsL0JLsxG0
        /bx09qf86kgmdUQXABAjHmXfORENVTiPf6P7kFRN7DsGY7Uy+49FnezxnRX9JF8A=
X-Google-Smtp-Source: 
 ABdhPJyqGzXsogKiFMYP9vr5Cl6ht62P4lfONGd7FnWULuyATlBNwCEZCNwfy141caWCnZqnFQ2f0lYNHDY2OA==
X-Received: by 2002:a25:7582:: with SMTP id
 q124mr66565332ybc.208.1594161400577;
 Tue, 07 Jul 2020 15:36:40 -0700 (PDT)
Date: Tue,  7 Jul 2020 15:36:30 -0700
Message-Id: <20200707223630.336700-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.383.g050319c2ae-goog
Subject: [PATCH] kvm: x86: Read PDPTEs on CR0.CD and CR0.NW changes
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to the SDM, when PAE paging would be in use following a
MOV-to-CR0 that modifies any of CR0.CD, CR0.NW, or CR0.PG, then the
PDPTEs are loaded from the address in CR3. Previously, kvm only loaded
the PDPTEs when PAE paging would be in use following a MOV-to-CR0 that
modified CR0.PG.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/x86.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [RFC PATCH v2] kvm,x86: Exit to user space in case of page fault error
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11650135
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 95E7C92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 20:14:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 796E921532
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 20:14:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="B/JK38nu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728773AbgGGUOB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 16:14:01 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:50722 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728650AbgGGUOB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 16:14:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594152839;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=AF7OGVkrCC5pOrLUbiawA+5CmcjoicxjCc2P7pf7Qco=;
        b=B/JK38nuhb874KRxZvES80NZVvafhMa0RM6O9kxqCnl5H8QQ2YowzdgxYZyKbkcl9L7IHP
        sJ1KzwkZR4XJtQT3z+eST/MT12aV7HP5VqaHiP079JXvp55IHcQNH9FArsvLU5kd20obXb
        K80EKy5D/T46ol3w9H8EmuDNqaqI0q4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-436-peJDFMy5N5qEb0jmDWMmEg-1; Tue, 07 Jul 2020 16:13:57 -0400
X-MC-Unique: peJDFMy5N5qEb0jmDWMmEg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3728480183C;
        Tue,  7 Jul 2020 20:13:56 +0000 (UTC)
Received: from horse.redhat.com (ovpn-116-115.rdu2.redhat.com [10.10.116.115])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4120B73FC0;
        Tue,  7 Jul 2020 20:13:53 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id 9913A22055E; Tue,  7 Jul 2020 16:13:52 -0400 (EDT)
Date: Tue, 7 Jul 2020 16:13:52 -0400
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs-list <virtio-fs@redhat.com>, vkuznets@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Subject: [RFC PATCH v2] kvm,x86: Exit to user space in case of page fault
 error
Message-ID: <20200707201352.GA88802@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page fault error handling behavior in kvm seems little inconsistent when
page fault reports error. If we are doing fault synchronously
then we capture error (-EFAULT) returned by __gfn_to_pfn_memslot() and
exit to user space and qemu reports error, "error: kvm run failed Bad address".

But if we are doing async page fault, then async_pf_execute() will simply
ignore the error reported by get_user_pages_remote() or
by kvm_mmu_do_page_fault(). It is assumed that page fault was successful
and either a page ready event is injected in guest or guest is brought
out of artificial halt state and run again. In both the cases when guest
retries the instruction, it takes exit again as page fault was not
successful in previous attempt. And then this infinite loop continues
forever.

Trying fault in a loop will make sense if error is temporary and will
be resolved on retry. But I don't see any intention in the code to
determine if error is temporary or not.  Whether to do fault synchronously
or asynchronously, depends on so many variables but none of the varibales
is whether error is temporary or not. (kvm_can_do_async_pf()).

And that makes it very inconsistent or unpredictable to figure out whether
kvm will exit to qemu with error or it will just retry and go into an
infinite loop.

This patch tries to make this behavior consistent. That is instead of
getting into infinite loop of retrying page fault, exit to user space
and stop VM if page fault error happens.

In future this can be improved by injecting errors into guest. As of
now we don't have any race free method to inject errors in guest.

When page fault error happens in async path save that pfn and when next
time guest retries, do a sync fault instead of async fault. So that if error
is encountered, we exit to qemu and avoid infinite loop.

We maintain a cache of error gfns and force sync fault if a gfn is
found in cache of error gfn. There is a small possibility that we
miss an error gfn (as it got overwritten by a new error gfn). But
its just a hint and sooner or later some error pfn will match
and we will force sync fault and exit to user space.

Change from v1:

- Maintain a cache of error gfns, instead of single gfn. (Vitaly)

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/x86.c              | 61 +++++++++++++++++++++++++++++++--
 4 files changed, 62 insertions(+), 5 deletions(-)

```
#### [PATCH v4 1/2] virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11648051
Return-Path: <SRS0=0S4s=AS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8002A6C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 08:45:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 720A0206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  7 Jul 2020 08:45:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727003AbgGGIo7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 04:44:59 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:29812 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725874AbgGGIo7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 7 Jul 2020 04:44:59 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0678YDQB105510;
        Tue, 7 Jul 2020 04:44:52 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32482kn0p1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 04:44:51 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0678a9qW112042;
        Tue, 7 Jul 2020 04:44:49 -0400
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32482kn0jr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 04:44:49 -0400
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0678g2GC016988;
        Tue, 7 Jul 2020 08:44:43 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04fra.de.ibm.com with ESMTP id 322hd7smhe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 07 Jul 2020 08:44:43 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0678ienT47579346
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 7 Jul 2020 08:44:40 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5D69AA4069;
        Tue,  7 Jul 2020 08:44:40 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7C3B1A4057;
        Tue,  7 Jul 2020 08:44:39 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.29.12])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue,  7 Jul 2020 08:44:39 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v4 1/2] virtio: let arch validate VIRTIO features
Date: Tue,  7 Jul 2020 10:44:36 +0200
Message-Id: <1594111477-15401-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594111477-15401-1-git-send-email-pmorel@linux.ibm.com>
References: <1594111477-15401-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-07_05:2020-07-07,2020-07-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 spamscore=0 clxscore=1015 phishscore=0 suspectscore=1 cotscore=-2147483648
 mlxlogscore=999 adultscore=0 malwarescore=0 bulkscore=0 priorityscore=1501
 mlxscore=0 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2007070066
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may need to validate the VIRTIO devices features
based on architecture specificities.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 2 files changed, 20 insertions(+)

```
