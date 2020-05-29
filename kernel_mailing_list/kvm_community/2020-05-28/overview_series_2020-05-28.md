#### [PATCH 1/2] KVM: PPC: Book3S HV: Remove user-triggerable WARN_ON
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11574207
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94053159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 01:54:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B834207CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 01:54:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="tP6o7VvB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726451AbgE1ByT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 21:54:19 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38000 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725901AbgE1ByT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 21:54:19 -0400
Received: from ozlabs.org (bilbo.ozlabs.org [IPv6:2401:3900:2:1::2])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C515BC05BD1E;
        Wed, 27 May 2020 18:54:18 -0700 (PDT)
Received: by ozlabs.org (Postfix, from userid 1003)
        id 49XW2v42BNz9sSJ; Thu, 28 May 2020 11:54:15 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1590630855; bh=DOgMK8VCRcBCDfvcSWAbMi3HJx7pIBfkzj01lRn5oNE=;
        h=Date:From:To:Cc:Subject:From;
        b=tP6o7VvBFMax6KXJ1rUfHjl6HurJZN1gR+n7JqVp4o4IyFqVExhStTIVeE66LG+Py
         sxoDluYp/GK6/uX+qdb4XIuZK9TMKAYnROd0emEg9QW42u9B/s/iA4jYSDm3HiQH7s
         APNVTuO7HIoqlIkGQ/MLEFygB+u83Ah/ZWyrYmYfd6RMJJBfzoG8ah83VCrYNrHpAl
         XwRfzI/4/inzobX2+4E3jm44MiVBbnX1EGOMrxYNuhNqQxSVEth9K7ZJto9gHHfzJj
         dOO7GgwP5jPO1kCrpIix43usTpim6omC4DGJi7qZ0j17W5Z0z+RKJbf+WWRCzTGtG0
         nGAJjYci8QjmQ==
Date: Thu, 28 May 2020 11:53:31 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, Laurent Vivier <lvivier@redhat.com>,
        David Gibson <david@gibson.dropbear.id.au>,
        Nick Piggin <npiggin@au1.ibm.com>
Subject: [PATCH 1/2] KVM: PPC: Book3S HV: Remove user-triggerable WARN_ON
Message-ID: <20200528015331.GD307798@thinks.paulus.ozlabs.org>
MIME-Version: 1.0
Content-Disposition: inline
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Although in general we do not expect valid PTEs to be found in
kvmppc_create_pte when we are inserting a large page mapping, there
is one situation where this can occur.  That is when dirty page
logging is turned off for a memslot while the VM is running.
Because the new memslots are installed before the old memslot is
flushed in kvmppc_core_commit_memory_region_hv(), there is a
window where a hypervisor page fault can try to install a 2MB
(or 1GB) page where there are already small page mappings which
were installed while dirty page logging was enabled and which
have not yet been flushed.

Since we have a situation where valid PTEs can legitimately be
found by kvmppc_unmap_free_pte, and which can be triggered by
userspace, just remove the WARN_ON_ONCE, since it is undesirable
to have userspace able to trigger a kernel warning.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 11 +++++++----
 1 file changed, 7 insertions(+), 4 deletions(-)

```
#### [PATCH Kernel v24 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11576901
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 54675912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 21:04:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 30FD2208B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 21:04:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="HoAC4BEu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436481AbgE1VE3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 17:04:29 -0400
Received: from hqnvemgate25.nvidia.com ([216.228.121.64]:1946 "EHLO
        hqnvemgate25.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2436485AbgE1VEX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 May 2020 17:04:23 -0400
Received: from hqpgpgate101.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate25.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ed027020000>; Thu, 28 May 2020 14:02:58 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate101.nvidia.com (PGP Universal service);
  Thu, 28 May 2020 14:04:22 -0700
X-PGP-Universal: processed;
        by hqpgpgate101.nvidia.com on Thu, 28 May 2020 14:04:22 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Thu, 28 May
 2020 21:04:15 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Thu, 28 May 2020 21:04:08 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        Kirti Wankhede <kwankhede@nvidia.com>
Subject: [PATCH Kernel v24 1/8] vfio: UAPI for migration interface for device
 state
Date: Fri, 29 May 2020 02:00:47 +0530
Message-ID: <1590697854-21364-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1590697854-21364-1-git-send-email-kwankhede@nvidia.com>
References: <1590697854-21364-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590699778; bh=J8jSJlsdWqaPxNJIyC2rLrIDBGB36yiaUEQJm3QDKr4=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=HoAC4BEuk6j3Awc/dz2QJy9tJkRn/0NBu/15bNd3iHqe3C8UQJUqTEJd/7U0GXWuM
         QZ33XcLnqdlDqEaNJRtXp8axY2fEgQfM31orpMpV2YGF98rUxBpdz2gUPMo05Tkiqi
         9LE9EUw25COCtgPzqkmEKTi1PcpwRwBTv2O/dSxV9EAEZCFxBI8Yk+SwAF0H2kfQ9z
         vv9mlxpb8+h/xBtPZWhvw7JakU1t/+sGkXH/tMbohSvLVYT8H/zdrGVd0tZ5WmpoOw
         0Q9b7bEec6lf20l8eTN8YB1cDhpg6x9f+lduNLwc2yOT9d9Nln/XtPwzg+Zf0IPAay
         jyYa36YqQF/LA==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Yan Zhao <yan.y.zhao@intel.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH] KVM: arm64: Check advertised Stage-2 page size capability
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11575821
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 221C9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 13:13:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 087B7208E4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 13:13:21 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590671601;
	bh=88nAhcUdAjqSE5P8DmE4VKnsji8sqj9MbWPaJTGERCA=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ka0lGNQRikhA2wonCikx4abCm3Q6BkoZO3QUx+KuBW8OUPfmcVLQWHbqXbayb/V+y
	 u3WNkDfSCZQguSzFn41fUKG/MXLi4/l+nTdCFSlfh4ObXyzjKFDYrx+5JyOr5Yjryu
	 fs6dRxZYSW36kjdX9Is4Qzs55Id2lPLqPEckGsPc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390257AbgE1NNU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 09:13:20 -0400
Received: from mail.kernel.org ([198.145.29.99]:59894 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390252AbgE1NNP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 May 2020 09:13:15 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6774320814;
        Thu, 28 May 2020 13:13:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590671594;
        bh=88nAhcUdAjqSE5P8DmE4VKnsji8sqj9MbWPaJTGERCA=;
        h=From:To:Cc:Subject:Date:From;
        b=l2OHw/FQ9kerohAio4wp12902DOjbqbrMavpBZZOXeJk1Cey1Q+bKIje+2nVhDNvK
         WfulkPDPNpuEBUQA1KNabTOrlpcNAzHEz2FN7ZbdBGQ0pVUsJC0wZymO6GhkrEKsyG
         oK+/W9yovwCO4nBdu8ztZkfiyXkr+lh3SMcuJ0iM=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jeILQ-00Fzjb-KP; Thu, 28 May 2020 14:13:12 +0100
From: Marc Zyngier <maz@kernel.org>
To: Will Deacon <will@kernel.org>
Cc: Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        alexandru.elisei@arm.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kernel-team@android.com
Subject: [PATCH] KVM: arm64: Check advertised Stage-2 page size capability
Date: Thu, 28 May 2020 14:12:58 +0100
Message-Id: <20200528131259.860459-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: will@kernel.org, catalin.marinas@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With ARMv8.5-GTG, the hardware (or more likely a hypervisor) can
advertise the supported Stage-2 page sizes.

Let's check this at boot time.

Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
Hi Will,

Can you please take this patch via the arm64 tree, and apply it
to the for-next/cpufeature branch?

Thanks,

        M.
 arch/arm64/include/asm/kvm_host.h |  2 +-
 arch/arm64/include/asm/sysreg.h   |  3 +++
 arch/arm64/kernel/cpufeature.c    | 18 +++++++++++++++
 arch/arm64/kvm/reset.c            | 37 +++++++++++++++++++++++++++++--
 virt/kvm/arm/arm.c                |  4 +---
 5 files changed, 58 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11575819
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C4D86912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 13:13:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A8A1E207F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 13:13:19 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590671599;
	bh=/Cos/35WH/9xBlW4l4WxdAutfPImRn/S1JlIE5WiW/M=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=zyL60Y40ZPqPS9xAD13qPkWZ/ymbvwlXjIo/jXh3/EE+T2HSi6lp9xloU+u7jgjIY
	 wikUzZzgUdm1m9mz4TXblcMub7fV9nnNNQfGluUAx3snA6du1A9/vx9Gc0B5VMK9kS
	 BzzhK5/5ZJHKGeEqOePpTSCQJQQJ9etFSekHmi3k=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390254AbgE1NNS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 09:13:18 -0400
Received: from mail.kernel.org ([198.145.29.99]:59938 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2390241AbgE1NNP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 May 2020 09:13:15 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 0AE87207F5;
        Thu, 28 May 2020 13:13:15 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590671595;
        bh=/Cos/35WH/9xBlW4l4WxdAutfPImRn/S1JlIE5WiW/M=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=DZ6fO+7qKDgeN3v2pbcuHsNRzhZrc23w0LNJ5fjku4A3hLct/AICANqf9MhbJSTd1
         jnEdC05pelT1TVfaUb2YseBf8And1lM7A2RvTRZ+Nf6+GqWXAioRJvdLkxfGXfb7v/
         I54UGCNC66gq/D5xkNwBWba3INSUBkZVZIikIhkQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jeILR-00Fzjb-Bb; Thu, 28 May 2020 14:13:13 +0100
From: Marc Zyngier <maz@kernel.org>
To: Will Deacon <will@kernel.org>
Cc: Catalin Marinas <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        alexandru.elisei@arm.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
        kernel-team@android.com
Subject: [PATCH] KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
Date: Thu, 28 May 2020 14:12:59 +0100
Message-Id: <20200528131259.860459-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200528131259.860459-1-maz@kernel.org>
References: <20200528131259.860459-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: will@kernel.org, catalin.marinas@arm.com,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Having __load_guest_stage2 in kvm_hyp.h is quickly going to trigger
a circular include problem. In order to avoid this, let's move
it to kvm_mmu.h, where it will be a better fit anyway.

In the process, drop the __hyp_text annotation, which doesn't help
as the function is marked as __always_inline.

Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
Hi Will,

Can you please take this patch via the arm64 tree, and apply it
to the for-next/kvm/errata branch?

Thanks,

	M.

 arch/arm64/include/asm/kvm_hyp.h | 18 ------------------
 arch/arm64/include/asm/kvm_mmu.h | 17 +++++++++++++++++
 2 files changed, 17 insertions(+), 18 deletions(-)

```
#### [PATCH] KVM: selftests: Add .gitignore entry for KVM_SET_GUEST_DEBUG test
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11574237
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46C6C1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:16:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 377D920DD4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:16:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726836AbgE1CQ0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 22:16:26 -0400
Received: from mga12.intel.com ([192.55.52.136]:65126 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726086AbgE1CQZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 22:16:25 -0400
IronPort-SDR: 
 0s3OLJt46aCvM27fGNn0BJuSuOaDIevXtwxSmwTobwk3RGkDAZV9RsiT/OhHh5SYSsWQJZAxOG
 RVy5vTKx27BQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 19:16:25 -0700
IronPort-SDR: 
 KxXTxRiR8qvwMya+n1jxtQezw59GWa09vyxuwlNF/iejGh6wo2QsaRZyeSxRzsF+P2meBPWdFv
 zSoaz2qjtxQw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,443,1583222400";
   d="scan'208";a="442767711"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by orsmga005.jf.intel.com with ESMTP; 27 May 2020 19:16:24 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: selftests: Add .gitignore entry for KVM_SET_GUEST_DEBUG
 test
Date: Wed, 27 May 2020 19:16:24 -0700
Message-Id: <20200528021624.28348-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add the KVM_SET_GUEST_DEBUG test's output binary to .gitignore.

Fixes: 449aa906e67e ("KVM: selftests: Add KVM_SET_GUEST_DEBUG test")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 tools/testing/selftests/kvm/.gitignore | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: selftests: Ignore KVM 5-level paging support for VM_MODE_PXXV48_4K
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11574235
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7235D1391
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:15:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6665F2100A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:15:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726616AbgE1CPd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 22:15:33 -0400
Received: from mga06.intel.com ([134.134.136.31]:22236 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725849AbgE1CPc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 22:15:32 -0400
IronPort-SDR: 
 uchrLjJhGqkfY1psT2qsxRaS0/A9bwL5EfHY6aVSJQeeMO3P4wpVDQSbZHGASHQim7dzXuyB7X
 aNIZFWw35ZVQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 19:15:31 -0700
IronPort-SDR: 
 ZsxugPmsaGgauJHajFMQGUnZ6XilY3GjFeF91lsi/lhAwQe6yrP2U+awZ3oR0Yq9oqUgvuwlpf
 MliaLxRu/0YQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,443,1583222400";
   d="scan'208";a="376218319"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 27 May 2020 19:15:31 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sergio Perez Gonzalez <sergio.perez.gonzalez@intel.com>,
        Adriana Cervantes Jimenez <adriana.cervantes.jimenez@intel.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: selftests: Ignore KVM 5-level paging support for
 VM_MODE_PXXV48_4K
Date: Wed, 27 May 2020 19:15:30 -0700
Message-Id: <20200528021530.28091-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly set the VA width to 48 bits for the x86_64-only PXXV48_4K VM
mode instead of asserting the guest VA width is 48 bits.  The fact that
KVM supports 5-level paging is irrelevant unless the selftests opt-in to
5-level paging by setting CR4.LA57 for the guest.  The overzealous
assert prevents running the selftests on a kernel with 5-level paging
enabled.

Incorporate LA57 into the assert instead of removing the assert entirely
as a sanity check of KVM's CPUID output.

Fixes: 567a9f1e9deb ("KVM: selftests: Introduce VM_MODE_PXXV48_4K")
Reported-by: Sergio Perez Gonzalez <sergio.perez.gonzalez@intel.com>
Cc: Adriana Cervantes Jimenez <adriana.cervantes.jimenez@intel.com>
Cc: Peter Xu <peterx@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 11 +++++++++--
 1 file changed, 9 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] access: disable phys-bits=36 for now
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11575787
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8B78090
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 12:47:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7378B206F1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 12:47:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="fO8AzcPk"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389959AbgE1Mrw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 08:47:52 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:60298 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2389852AbgE1Mrr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 28 May 2020 08:47:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590670065;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=578lqEIwcFIGxMqIYDdaOt9NWnfXpZq3NaaADCB4Cx8=;
        b=fO8AzcPkqe/O7ZsHb7Dgc8YqatTRUvvHvwL/ZdkIZZSzLlEuNpP6M3jNycDu4kKrKySePI
        DuYJD3VAVtRaY0C9MtNE5pdLKFy32xIYMUszDP8J0SFbymxb3Tj9Do1cPE571bC6SopN//
        5XnSsTrQPbyDZgvc42+kNm6i8YkwneE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-188-A9L0eY6oOZiR7TfVl0C4uw-1; Thu, 28 May 2020 08:47:44 -0400
X-MC-Unique: A9L0eY6oOZiR7TfVl0C4uw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 84E4D18FE864
        for <kvm@vger.kernel.org>; Thu, 28 May 2020 12:47:43 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3F4A25D9EF;
        Thu, 28 May 2020 12:47:43 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [PATCH kvm-unit-tests] access: disable phys-bits=36 for now
Date: Thu, 28 May 2020 08:47:42 -0400
Message-Id: <20200528124742.28953-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Support for guest-MAXPHYADDR < host-MAXPHYADDR is not upstream yet,
it should not be enabled.  Otherwise, all the pde.36 and pte.36
fail and the test takes so long that it times out.

Reported-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Tested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: X86: Call kvm_x86_ops.cpuid_update() after CPUIDs fully updated
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11576121
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A595713B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 15:19:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 942FB20814
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 15:19:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404313AbgE1PTm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 11:19:42 -0400
Received: from mga02.intel.com ([134.134.136.20]:64188 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404219AbgE1PTl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 May 2020 11:19:41 -0400
IronPort-SDR: 
 kcd1/j7jzA7xbET44HnV5V8IPvDCH4kKnjisUW8iIzo7EUym2zw9RVHze1bmsOhs0/kPH8dxfn
 AwGj0u1NQyjw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 28 May 2020 08:19:32 -0700
IronPort-SDR: 
 PKpILhmpgWJ4LqD1TSyYiIUyogBt/I1Qqls+IXEYCQOudAO2v82YIWdazRGEUPJ3YlVKw1jWBs
 bknPGleRqmQA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,445,1583222400";
   d="scan'208";a="292030776"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by fmsmga004.fm.intel.com with ESMTP; 28 May 2020 08:19:30 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH] KVM: X86: Call kvm_x86_ops.cpuid_update() after CPUIDs fully
 updated
Date: Thu, 28 May 2020 23:19:27 +0800
Message-Id: <20200528151927.14346-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_x86_ops.cpuid_update() is used to update vmx/svm settings based on
updated CPUID settings. So it's supposed to be called after CPUIDs are
fully updated, not in the middle stage.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH v6] arch/x86: Update config and kernel doc for MPK feature on AMD
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11576269
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9B1F592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 16:08:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7DE5C207F9
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 16:08:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="dSehkjzM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404843AbgE1QIe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 28 May 2020 12:08:34 -0400
Received: from mail-bn8nam11on2075.outbound.protection.outlook.com
 ([40.107.236.75]:18040
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2404666AbgE1QIc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 28 May 2020 12:08:32 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=QZZHpA3+iXfVbi37N8Y62HGjbt9VMwBSloMK228o8mS8s1peFH93VzYJ5ayaAtdLII1ORnJS3ZAD1FAbM64uHgS2FYlpkKOv+gq1Nxf7Py+LHRCV3Ral/lSsyqdYQUGwsAT0oOoNOM6TIhqYt4SrYJThgHYwYGE9hyEtkWgPSlTEL3DthSTJvBIIyWqJuCXIRBu/Bk880jRKlCqQJV4Inpcudw/V7H8JjqHmLo8uiwRg2zyBZFpuotH+bUBlVXoDJfnzV4+ORr1g/mcd6YYNgKWkhyEoKwUc11h84H8wjNKaRM4tfm9/UoZVGtov5cbjIFvE8oNYQCsRLjYhc0v64A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CU/GTBcHcycOvPgCFYA1JDgb9C2f8ST1Y0nRkW9FPRA=;
 b=UWskvldeJby6BOMhFEdYjggPoMoIkEktJAP7+VwknkKQVbjAh/8ndfW9md7mXYVJtIhXlAwgEdlFy/0DrjPrZPiT2XI3ZQZOnVIw6i7x0o7j1d7jA90oh1bIamVSd9S8COhrLaAGddxbmLssdQvKhJx7UCKt1rfhVw9zCYju+2qlfycKkMhXEjtt5WO+3Mu1VvWb5l/jV8b8fFPFieEXlvJpPTdYeFTEUUslspeCOP4rRU4p/gE9F49mQXmaZWuK6sIzpxSKOhs3y3oUg4tKG8dVyO/1Kno5swMG5D3ywBWnR258u8M0q1LbavVjhbb8YxIM3oJmRUoPX2D7LDa+CQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=CU/GTBcHcycOvPgCFYA1JDgb9C2f8ST1Y0nRkW9FPRA=;
 b=dSehkjzMbWjWBHNDE7Jsppnhzs9KtcmC8MrgFGhQdoaIANwYdkXp6NLpe6+BvPDh7w8WgUwm9fyJnLFzQXQ029d7ELXLevB5MlKdZmtLpxPa/oEAHPUZRBAW/aX7YRROyusAyMryJuVw8i9XSioRxhmtAJ1TublQUXH1O7X9lew=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SN1PR12MB2527.namprd12.prod.outlook.com (2603:10b6:802:23::10) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3045.17; Thu, 28 May
 2020 16:08:25 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2%3]) with mapi id 15.20.3045.018; Thu, 28 May 2020
 16:08:25 +0000
Subject: [PATCH v6] arch/x86: Update config and kernel doc for MPK feature
 on AMD
From: Babu Moger <babu.moger@amd.com>
To: corbet@lwn.net, tglx@linutronix.de, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: x86@kernel.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, dave.hansen@linux.intel.com,
        luto@kernel.org, peterz@infradead.org, mchehab+samsung@kernel.org,
        babu.moger@amd.com, changbin.du@intel.com, namit@vmware.com,
        bigeasy@linutronix.de, yang.shi@linux.alibaba.com,
        asteinhauser@google.com, anshuman.khandual@arm.com,
        jan.kiszka@siemens.com, akpm@linux-foundation.org,
        steven.price@arm.com, rppt@linux.vnet.ibm.com, peterx@redhat.com,
        dan.j.williams@intel.com, arjunroy@google.com, logang@deltatee.com,
        thellstrom@vmware.com, aarcange@redhat.com, justin.he@arm.com,
        robin.murphy@arm.com, ira.weiny@intel.com, keescook@chromium.org,
        jgross@suse.com, andrew.cooper3@citrix.com,
        pawan.kumar.gupta@linux.intel.com, fenghua.yu@intel.com,
        vineela.tummalapalli@intel.com, yamada.masahiro@socionext.com,
        sam@ravnborg.org, acme@redhat.com, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Thu, 28 May 2020 11:08:23 -0500
Message-ID: 
 <159068199556.26992.17733929401377275140.stgit@naples-babu.amd.com>
User-Agent: StGit/unknown-version
X-ClientProxiedBy: SN2PR01CA0071.prod.exchangelabs.com (2603:10b6:800::39) To
 SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from naples-babu.amd.com (165.204.78.2) by
 SN2PR01CA0071.prod.exchangelabs.com (2603:10b6:800::39) with Microsoft SMTP
 Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3045.19 via Frontend
 Transport; Thu, 28 May 2020 16:08:23 +0000
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: f31b1e7a-6ace-41ca-19ca-08d803215a23
X-MS-TrafficTypeDiagnostic: SN1PR12MB2527:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB252781CA1FB5AD36027350CB958E0@SN1PR12MB2527.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-Forefront-PRVS: 0417A3FFD2
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 sZkPz0IDkSFWo7Q3RJXpkeeiLJaq7T5KlqxdMNHL/PGc+AEhZmQTtMb7Sbb0Vre0uNKw7JFv2SPjlmll9rn3n/Os3c0AFMiLxhbT+RA80YsVoauvoOVrCBGe+wyK+D1YvJBRbZT46iHyEx1rMSjx9V4dyKDk5RwTQBLbUPwBLlyHiP8e7x+7as0tH+7+Ks4R6n6/pYsE0U35ilH4k2VByiasYpfSPe/xIo6NHEax22e8lb7wJ/VnXmCoEm55mJvDW0TPjw6oYljppX+dx04lsr+q7NX9NQ7QiB34KbyUOL64kNoVxJUw2decYNO9BC9QoQW939Jm1cQNZi8ovNgd4o+h3ujPZSTyuPY+VHt8VzQTUdV1mqD0e+SS+NZzUFRHiGTYKvE8rqbmQzcJ3t7avw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(136003)(366004)(396003)(346002)(376002)(39860400002)(8936002)(956004)(8676002)(83380400001)(5660300002)(316002)(7406005)(55016002)(7416002)(66556008)(26005)(478600001)(15650500001)(4326008)(2906002)(86362001)(66946007)(103116003)(966005)(66476007)(186003)(52116002)(16526019)(7696005)(44832011);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 1QZXQTehOneLmFJ9KyeyiJPVJ6s/hzwND/7otIYcqHSWZokpOXT5c800NX7LNQblmMZNoYg0H3TV7aZ9CpTrWe6gBEyEoTBMryP+e9A0V3WGctGMp/mzIEfipi99JVfkQ8AyHGlWrOC+HmqMmSI/xchwZ2426vkSC1jFAAfpStzmzDufoaxQbSOUtiEvNE2CH4NhtM8SzJA0+ZMjb3eyJSclWctVG2RWsFyEglw7ZftvF/RJETEUa273C1LqZaBczAQ9SLqVWAEUJxIAk+7THaFa2hzfT8EZB3XoRsENQwdxBooHkYtrsKecHjpxUeYi0F7VjreQhMDd4FessywsmjtwUpTrKDqgpUmqz6v4J3FwDkZQ63OiDyaobWLQRaHDit1iw5cp0cY7/qJyPVIYHGBo8asrtsnvILrbuPfjcTiNNcMtR0rT4Osj9fHoGAdFP8x7e5FIM+AffRLs2cYExbK14SEYMNUgLzAsyLS6PRA=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 f31b1e7a-6ace-41ca-19ca-08d803215a23
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 28 May 2020 16:08:25.5018
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 TuSpuutpI5eP+1oIGFR8cQ25MS8BuWu6217iDjKOcaLbK9I0lvexQqT78RS+JLGJ
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2527
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD's next generation of EPYC processors support the MPK (Memory
Protection Keys) feature. Update the dependency and documentation.

Signed-off-by: Babu Moger <babu.moger@amd.com>
Reviewed-by: Dave Hansen <dave.hansen@linux.intel.com>
---
v6:
 - Removed X86_MEMORY_PROTECTION_KEYS. Just keeping the dependency
   and doc update. 

v5:
https://lore.kernel.org/lkml/158940940570.47998.17107695356894054769.stgit@naples-babu.amd.com/
 - Just submiting the first config update patch. Paulo said he already queued
   patch 2 & 3.
 - This patch addresses the few text changes suggested by Dave Hansen.

v4:
https://lore.kernel.org/lkml/158932780954.44260.4292038705292213548.stgit@naples-babu.amd.com/
- Removed all the source changes related to config parameter.
    Just kept the doc cahnges and add new config parameter
    X86_MEMORY_PROTECTION_KEYS which shadows X86_INTEL_MEMORY_PROTECTION_KEYS.
 - Minor change in feature detection in kvm/cpuid.c 

v3:
  https://lore.kernel.org/lkml/158923982830.20128.14580309786525588408.stgit@naples-babu.amd.com/#r
  - Fixed the problem Jim Mattson pointed out which can cause pkru
    resources to get corrupted during host and guest switches. 
  - Moved the PKU feature detection code from VMX.c to common code.
  
v2:
  https://lore.kernel.org/lkml/158897190718.22378.3974700869904223395.stgit@naples-babu.amd.com/
  - Introduced intermediate config option X86_MEMORY_PROTECTION_KEYS to
    avoid user propmpts. Kept X86_INTEL_MEMORY_PROTECTION_KEYS as is.
    Eventually, we will be moving to X86_MEMORY_PROTECTION_KEYS after
    couple of kernel revisions. 
  - Moved pkru data structures to kvm_vcpu_arch. Moved save/restore pkru
    to kvm_load_host_xsave_state/kvm_load_guest_xsave_state.

v1:
  https://lore.kernel.org/lkml/158880240546.11615.2219410169137148044.stgit@naples-babu.amd.com/

 Documentation/core-api/protection-keys.rst |    5 +++--
 arch/x86/Kconfig                           |    4 ++--
 2 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH] vfio/mdev: Fix reference count leak in add_mdev_supported_type.
##### From: wu000273@umn.edu

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: wu000273@umn.edu
X-Patchwork-Id: 11574231
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81A85739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:01:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 68822207CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 02:01:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=umn.edu header.i=@umn.edu
 header.b="FQLUT3B1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726928AbgE1CBV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 22:01:21 -0400
Received: from mta-p5.oit.umn.edu ([134.84.196.205]:42390 "EHLO
        mta-p5.oit.umn.edu" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726563AbgE1CBS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 22:01:18 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-p5.oit.umn.edu (Postfix) with ESMTP id 49XWC12Mpkz9vYBT
        for <kvm@vger.kernel.org>; Thu, 28 May 2020 02:01:17 +0000 (UTC)
X-Virus-Scanned: amavisd-new at umn.edu
Received: from mta-p5.oit.umn.edu ([127.0.0.1])
        by localhost (mta-p5.oit.umn.edu [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id BYkVvTmJVylL for <kvm@vger.kernel.org>;
        Wed, 27 May 2020 21:01:17 -0500 (CDT)
Received: from mail-io1-f69.google.com (mail-io1-f69.google.com
 [209.85.166.69])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mta-p5.oit.umn.edu (Postfix) with ESMTPS id 49XWC10fKwz9vFPQ
        for <kvm@vger.kernel.org>; Wed, 27 May 2020 21:01:17 -0500 (CDT)
DMARC-Filter: OpenDMARC Filter v1.3.2 mta-p5.oit.umn.edu 49XWC10fKwz9vFPQ
DKIM-Filter: OpenDKIM Filter v2.11.0 mta-p5.oit.umn.edu 49XWC10fKwz9vFPQ
Received: by mail-io1-f69.google.com with SMTP id g3so6981624ioc.20
        for <kvm@vger.kernel.org>; Wed, 27 May 2020 19:01:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=umn.edu; s=google;
        h=from:to:cc:subject:date:message-id;
        bh=BPs8LVcxoxf1YiKvvhf741vH5cSBxCq2p6KwCVlZJlU=;
        b=FQLUT3B1eErsvZ0Ocp4xVAs2C/j0jxi7sjHyq2fkRKXxUD5n5X0POfT2PAglwf+v0w
         F8TztGOERRorjskQK4YnoXOqcy7C2EBJ9tekEsCR0JWnPzY9v1QvriPPVUJL/I9BeHef
         Hy690sImJpeFn/YpIhEaeHhPaNZq7lCq6qM0f8X0wo6Q/j8NPNRM+OJCbUVXs9a/j2P9
         fXRb9V1JKefP3wwfANb+iq2lAfa/rdKKGKtR6P+c3vmdiAsVeD+4vhX5Bd+MxH6SsY2o
         S1z/esmZIrHRqbThvG3XVWtAXZtT0ln+pqjjM1jvyX/g/BPXvrME6Y9G+FvmpQqlqrox
         xx/A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=BPs8LVcxoxf1YiKvvhf741vH5cSBxCq2p6KwCVlZJlU=;
        b=pGyn1Quk+glBdFvm77g1Jv37P/p+Py0sntw+aEGbsR0ZOH/zPBJ5OdNYInNov+ygCT
         VMKPq2fNW2SU3U5AYdu/tCLHSoCIY2XykuVUIDpGwunuFZrWqyoaWWmEBMXF1xiIYIks
         ZjSZTq/5z2i2/s7bwynp6VyjpI1Pej4SxqsJp15lMRqxgo53LwGNisbOeJFuVr0ZVZ4T
         G2yRdYyAOvy+pnMK/936SDQ8dPXhgKSs6P3sPDt6XcfyLxj5IZgI5cE0ZT8MWA2C6l+a
         7CJPBkW9wEsit6hOVWiLFZsVbE38wXIOQU/OMGOV2iPez1KrVr3dfIG8cvYlXIsRD48T
         Kmfg==
X-Gm-Message-State: AOAM533hdmYUNvwi8mKxVe5kk9abL7Mijvx++CWFscsEkt7Y8+ptEmyt
        iEd2qt09ce/L13eH02lmNWrrw/S1eNIWJtn/LGjeqDvlHJ3t9CR0JmdtvpakKLqN1ySys0IdZvc
        C7jwvLEnd4GmZpXQ3
X-Received: by 2002:a92:b001:: with SMTP id x1mr931331ilh.18.1590631276457;
        Wed, 27 May 2020 19:01:16 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJyzseNODZL7xc5OcagCl2EGQR0kxsq3pWzWLytnWDMqV+TXhfavKonxOJKsgZL6Q5ghdTnh/g==
X-Received: by 2002:a92:b001:: with SMTP id x1mr931315ilh.18.1590631276118;
        Wed, 27 May 2020 19:01:16 -0700 (PDT)
Received: from qiushi.dtc.umn.edu (cs-kh5248-02-umh.cs.umn.edu.
 [128.101.106.4])
        by smtp.gmail.com with ESMTPSA id
 z12sm1965088iol.15.2020.05.27.19.01.14
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 27 May 2020 19:01:15 -0700 (PDT)
From: wu000273@umn.edu
To: kjlu@umn.edu
Cc: wu000273@umn.edu, Kirti Wankhede <kwankhede@nvidia.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, Neo Jia <cjia@nvidia.com>,
        Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>,
        Jike Song <jike.song@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] vfio/mdev: Fix reference count leak in
 add_mdev_supported_type.
Date: Wed, 27 May 2020 21:01:09 -0500
Message-Id: <20200528020109.31664-1-wu000273@umn.edu>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Qiushi Wu <wu000273@umn.edu>

kobject_init_and_add() takes reference even when it fails.
If this function returns an error, kobject_put() must be called to
properly clean up the memory associated with the object. Thus,
replace kfree() by kobject_put() to fix this issue. Previous
commit "b8eb718348b8" fixed a similar problem.

Fixes: 7b96953bc640 ("vfio: Mediated device Core driver")
Signed-off-by: Qiushi Wu <wu000273@umn.edu>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/vfio/mdev/mdev_sysfs.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: Remove defunct KVM_DEBUG_FS Kconfig
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11574265
Return-Path: <SRS0=G/HE=7K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3AD5914C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 03:11:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21D8D2084C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 28 May 2020 03:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727012AbgE1DLY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 27 May 2020 23:11:24 -0400
Received: from mga17.intel.com ([192.55.52.151]:35951 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726563AbgE1DLY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 27 May 2020 23:11:24 -0400
IronPort-SDR: 
 8syiTMz0xyRE3Deu3S6+P/0jx29FY88hFMeIFrJMiWrlKuuwWkB5yrh1eE22hbHmFAiKPPLlhs
 IBkssozOOX9w==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 27 May 2020 20:11:24 -0700
IronPort-SDR: 
 dalb1FmVAc4anaetpGsxmDx/4ESS/ijY749MVIqAzVgKL8OFW2Va0vqp6c/Af9NDQ6BwpnlgFb
 5847K/zfr8yQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,443,1583222400";
   d="scan'208";a="376231240"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.152])
  by fmsmga001.fm.intel.com with ESMTP; 27 May 2020 20:11:22 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Subject: [PATCH] x86/kvm: Remove defunct KVM_DEBUG_FS Kconfig
Date: Wed, 27 May 2020 20:11:21 -0700
Message-Id: <20200528031121.28904-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove KVM_DEBUG_FS, which can easily be misconstrued as controlling
KVM-as-a-host.  The sole user of CONFIG_KVM_DEBUG_FS was removed by
commit cfd8983f03c7b ("x86, locking/spinlocks: Remove ticket (spin)lock
implementation").

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/Kconfig      | 8 --------
 arch/x86/kernel/kvm.c | 1 -
 2 files changed, 9 deletions(-)

```
