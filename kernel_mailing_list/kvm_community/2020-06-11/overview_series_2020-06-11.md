#### [PATCH 01/11] KVM: arm64: Flush the instruction cache if not unmapping the VM on reboot
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11599565
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7A8A7138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:10:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B9162081A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:10:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591866611;
	bh=/aiYNNuE8VR6SQq4tRJxdPUL75hAzzLtTkxxhFEWVGw=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=mpf4VXfOqc6GLVPUNmDTEBW9uc2epUBa3XtkH/67iF53etmb7fXG4DY5jaY6KI6aR
	 h/t974USS/F9Pls+V7u2kjLpY06v5r/NvhbHUSkr+hnHvetAOr8PRoZ58pakOpxSAT
	 BblQI+lpfa06DgKuFjs96LD+rqrS3RsXiX/JW9vY=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726973AbgFKJKK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 05:10:10 -0400
Received: from mail.kernel.org ([198.145.29.99]:49674 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726899AbgFKJKJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 05:10:09 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 334332078D;
        Thu, 11 Jun 2020 09:10:09 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591866609;
        bh=/aiYNNuE8VR6SQq4tRJxdPUL75hAzzLtTkxxhFEWVGw=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=mXVcqnkc2Hsyezw/WUEVPOraHUNfya8IIXpIMQdimEt1UVH3Mva3IbmkEIisHYi8s
         H1rAgXozuu6G1lkARw52RadTYpAepHNrVeGhX/EL9Azu8pXWRv/2cuIfX+z8gNhe5W
         y8hxnRJPgD5ujNJZB95/Vmf40DSYjYphpRJ6LPBo=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jjJDr-0022ZT-Op; Thu, 11 Jun 2020 10:10:07 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Subject: [PATCH 01/11] KVM: arm64: Flush the instruction cache if not
 unmapping the VM on reboot
Date: Thu, 11 Jun 2020 10:09:46 +0100
Message-Id: <20200611090956.1537104-2-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200611090956.1537104-1-maz@kernel.org>
References: <20200611090956.1537104-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, james.morse@arm.com, mark.rutland@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a system with FWB, we don't need to unmap Stage-2 on reboot,
as even if userspace takes this opportunity to repaint the whole
of memory, FWB ensures that the data side stays consistent even
if the guest uses non-cacheable mappings.

However, the I-side is not necessarily coherent with the D-side
if CTR_EL0.DIC is 0. In this case, invalidate the i-cache to
preserve coherency.

Reported-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Fixes: 892713e97ca1 ("KVM: arm64: Sidestep stage2_unmap_vm() on vcpu reset when S2FWB is supported")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/arm.c | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.8, take #1
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11599585
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 13FCD60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:10:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F1B36207C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:10:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1591866628;
	bh=LEb0TmHs9BwF0am32RadcRA4RU0L0oWhcV5wOopAYI8=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=PztpMSTuiHEKCRYNIdlj31UUJ2RfJkbx6fO+IjdCVgYQ43bTqBc4mWd6UfrRZ1Bk7
	 SnYuX5eP6yhzby/Yvt7kZETRs6xBYWNoxcg3I1Tooo9CDyKnNLyS/QSeHH+T7RveMb
	 XhcCGQSoxEPIkivVyg+CjvQnIhhwwn3QuSWYw+QU=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726965AbgFKJKK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 05:10:10 -0400
Received: from mail.kernel.org ([198.145.29.99]:49642 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726760AbgFKJKJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 05:10:09 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A390420760;
        Thu, 11 Jun 2020 09:10:08 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1591866608;
        bh=LEb0TmHs9BwF0am32RadcRA4RU0L0oWhcV5wOopAYI8=;
        h=From:To:Cc:Subject:Date:From;
        b=q1kTyCd8T/68YBv3CRIYzkVpMPW1eVFfsQhmwQGWah+mz+QtZQFif1Ws68NKb1Ewv
         5h33hP+50DG851IfhM3j8LD838jhq44IXS+5sTXtxTnDJ4e+bh7XESwG8QuHZGDUJE
         zliMhna5ReRYb8SpviD876yx5zB7YHXzQKgvvrPE=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jjJDr-0022ZT-4w; Thu, 11 Jun 2020 10:10:07 +0100
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Scull <ascull@google.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.8, take #1
Date: Thu, 11 Jun 2020 10:09:45 +0100
Message-Id: <20200611090956.1537104-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, alexandru.elisei@arm.com,
 ascull@google.com, james.morse@arm.com, mark.rutland@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

Here's a bunch of fixes that cropped up during the merge window,
mostly falling into two categories: 32bit system register accesses,
and 64bit pointer authentication handling.

Please pull,

	M.

The following changes since commit 8f7f4fe756bd5cfef73cf8234445081385bdbf7d:

  KVM: arm64: Drop obsolete comment about sys_reg ordering (2020-05-28 13:16:57 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.8-1

for you to fetch changes up to 15c99816ed9396c548eed2e84f30c14caccad1f4:

  Merge branch 'kvm-arm64/ptrauth-fixes' into kvmarm-master/next (2020-06-10 19:10:40 +0100)

----------------------------------------------------------------
KVM/arm64 fixes for Linux 5.8, take #1

* 32bit VM fixes:
  - Fix embarassing mapping issue between AArch32 CSSELR and AArch64
    ACTLR
  - Add ACTLR2 support for AArch32
  - Get rid of the useless ACTLR_EL1 save/restore
  - Fix CP14/15 accesses for AArch32 guests on BE hosts
  - Ensure that we don't loose any state when injecting a 32bit
    exception when running on a VHE host

* 64bit VM fixes:
  - Fix PtrAuth host saving happening in preemptible contexts
  - Optimize PtrAuth lazy enable
  - Drop vcpu to cpu context pointer
  - Fix sparse warnings for HYP per-CPU accesses

----------------------------------------------------------------
James Morse (3):
      KVM: arm64: Stop writing aarch32's CSSELR into ACTLR
      KVM: arm64: Add emulation for 32bit guests accessing ACTLR2
      KVM: arm64: Stop save/restoring ACTLR_EL1

Marc Zyngier (9):
      KVM: arm64: Flush the instruction cache if not unmapping the VM on reboot
      KVM: arm64: Save the host's PtrAuth keys in non-preemptible context
      KVM: arm64: Handle PtrAuth traps early
      KVM: arm64: Stop sparse from moaning at __hyp_this_cpu_ptr
      KVM: arm64: Remove host_cpu_context member from vcpu structure
      KVM: arm64: Make vcpu_cp1x() work on Big Endian hosts
      KVM: arm64: Synchronize sysreg state on injecting an AArch32 exception
      KVM: arm64: Move hyp_symbol_addr() to kvm_asm.h
      Merge branch 'kvm-arm64/ptrauth-fixes' into kvmarm-master/next

 arch/arm64/include/asm/kvm_asm.h     | 33 ++++++++++++++++--
 arch/arm64/include/asm/kvm_emulate.h |  6 ----
 arch/arm64/include/asm/kvm_host.h    |  9 +++--
 arch/arm64/include/asm/kvm_mmu.h     | 20 -----------
 arch/arm64/kvm/aarch32.c             | 28 ++++++++++++++++
 arch/arm64/kvm/arm.c                 | 20 ++++++-----
 arch/arm64/kvm/handle_exit.c         | 32 ++----------------
 arch/arm64/kvm/hyp/debug-sr.c        |  4 +--
 arch/arm64/kvm/hyp/switch.c          | 65 ++++++++++++++++++++++++++++++++++--
 arch/arm64/kvm/hyp/sysreg-sr.c       |  8 ++---
 arch/arm64/kvm/pmu.c                 |  8 ++---
 arch/arm64/kvm/sys_regs.c            | 25 +++++++-------
 arch/arm64/kvm/sys_regs_generic_v8.c | 10 ++++++
 13 files changed, 171 insertions(+), 97 deletions(-)
```
#### [RFC v6 01/25] scripts/update-linux-headers: Import iommu.h
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11599959
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 02CF3913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:48:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E91BD20747
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:48:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726520AbgFKMsB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 08:48:01 -0400
Received: from mga18.intel.com ([134.134.136.126]:58110 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726254AbgFKMsA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 08:48:00 -0400
IronPort-SDR: 
 Ur3/T5FU4lriLNq47uFNklz6MyyuqVx9WZ94OINzYO0likua88Uc5M07jsUmA52mhDLg/XVw8U
 XiOpB0JsxurQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Jun 2020 05:47:59 -0700
IronPort-SDR: 
 RnkDz4doH7jICI7Tfl9kgjTrzB4O6QxcHvVw2oHcq7VMRz9t0YiCaXtatk1nj36uyEE6v5GniX
 g44YYPhibz1Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,499,1583222400";
   d="scan'208";a="447911217"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga005.jf.intel.com with ESMTP; 11 Jun 2020 05:47:59 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: qemu-devel@nongnu.org, alex.williamson@redhat.com,
        peterx@redhat.com
Cc: mst@redhat.com, pbonzini@redhat.com, eric.auger@redhat.com,
        david@gibson.dropbear.id.au, jean-philippe@linaro.org,
        kevin.tian@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, hao.wu@intel.com, kvm@vger.kernel.org,
        Jacob Pan <jacob.jun.pan@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>,
        Cornelia Huck <cohuck@redhat.com>
Subject: [RFC v6 01/25] scripts/update-linux-headers: Import iommu.h
Date: Thu, 11 Jun 2020 05:54:00 -0700
Message-Id: <1591880064-30638-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1591880064-30638-1-git-send-email-yi.l.liu@intel.com>
References: <1591880064-30638-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Eric Auger <eric.auger@redhat.com>

Update the script to import the new iommu.h uapi header.

Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] KVM: X86: Move handling of INVPCID types to x86From: Babu Moger <babu.moger@amd.com>
##### From: Babu Moger <babu.moger@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Babu Moger <babu.moger@amd.com>
X-Patchwork-Id: 11600919
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EBB890
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 21:48:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0072420842
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 21:48:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="ohfXqpuj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726369AbgFKVsm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 17:48:42 -0400
Received: from mail-eopbgr680061.outbound.protection.outlook.com
 ([40.107.68.61]:20994
        "EHLO NAM04-BN3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726349AbgFKVsl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 17:48:41 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=U9AR4ORoEAtoQ8Jr4TQXFAf1b85rD1iDvq4GnlIWHqGqGWMK0Z810ZXVDZLyBGxnyuFQuzdGsTUgm8vZZ3ZKI6GFc4EDV/1i354kpHXrXDANCeyIcZWDEaF9IZy3r/dhH6FwPiTk2kOyd31/kZpLLre5ZwF6FwvczDp4HekhAfBVT1F59NNkZkJeb8k9fjNZ9crljMxNLRbYMdnV7kwSsOgkF2Gtonl2OBxo4NcllSHei95paf1YS+ZEyHdn1drSkv6rbLUYqYJ+IWY80df87Aaw2zTYRYmjdrgkzAZQapnAdEzma+8/9JAY60pkyBGnaNHH0Te7QiAMAZa2w1IK1g==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=wszXHOme3aEp+KG1tt9uh0LeRs6FwrR/e1hp0UE0DLg=;
 b=MNmmomBkCUevwKfOidy75yMJaPbeSP0li8FNqi7LRTVt1O1MVphSZ9iw0truIcDyKKNuVdm6fKu1wSZWk3JI0RFmFfM1r2fG2BlClZUGT+3wycQQKA8H7ndsJN+X9tfqfzhWSBjfXm/OBKO00paxqSSkiITv9Dc2We1rtpgPA8OUgNabdjbdvcFhV56G34JSmxRwJmkwlip8RDl0t1SYrbRWJTPqb48VlN5/yy7fcaSEl7VLLY5/iCdcEVZbBiTCElRiDlmmejaED7tKkN07jafmU5joDb0QyHaEfhop0ipnEPz1Q60rMDFqPWkUickGZDzCeWZLWBavIstSqhoqww==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=wszXHOme3aEp+KG1tt9uh0LeRs6FwrR/e1hp0UE0DLg=;
 b=ohfXqpujW1Ncvi03OLfL2eF5ey+44Vs0GewYF8mvo3DdskaT1xqfifJ9cWQ5oQe1BHl0gi5SgOsPYcGo1y5yrix0tl+iJAatpz1djMbABT+eXOcuzYdb5KGSrgpsHEgGtWaDj94yW43gyD5IkGShIG497DsNZOi97AukX3l7nQY=
Authentication-Results: tencent.com; dkim=none (message not signed)
 header.d=none;tencent.com; dmarc=none action=none header.from=amd.com;
Received: from SN1PR12MB2560.namprd12.prod.outlook.com (2603:10b6:802:26::19)
 by SA0PR12MB4589.namprd12.prod.outlook.com (2603:10b6:806:92::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.18; Thu, 11 Jun
 2020 21:48:37 +0000
Received: from SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2]) by SN1PR12MB2560.namprd12.prod.outlook.com
 ([fe80::2102:cc6b:b2db:4c2%3]) with mapi id 15.20.3088.021; Thu, 11 Jun 2020
 21:48:37 +0000
Subject: [PATCH 1/3] KVM: X86: Move handling of INVPCID types to x86
From: Babu Moger <babu.moger@amd.com>
To: wanpengli@tencent.com, joro@8bytes.org, x86@kernel.org,
        sean.j.christopherson@intel.com, mingo@redhat.com, bp@alien8.de,
        hpa@zytor.com, pbonzini@redhat.com, vkuznets@redhat.com,
        tglx@linutronix.de, jmattson@google.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Date: Thu, 11 Jun 2020 16:48:35 -0500
Message-ID: <159191211555.31436.7157754769653935735.stgit@bmoger-ubuntu>
In-Reply-To: <159191202523.31436.11959784252237488867.stgit@bmoger-ubuntu>
References: <159191202523.31436.11959784252237488867.stgit@bmoger-ubuntu>
User-Agent: StGit/0.17.1-dirty
X-ClientProxiedBy: DM6PR14CA0043.namprd14.prod.outlook.com
 (2603:10b6:5:18f::20) To SN1PR12MB2560.namprd12.prod.outlook.com
 (2603:10b6:802:26::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from [127.0.1.1] (165.204.77.1) by
 DM6PR14CA0043.namprd14.prod.outlook.com (2603:10b6:5:18f::20) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3088.18 via Frontend
 Transport; Thu, 11 Jun 2020 21:48:36 +0000
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 0531b781-295a-4231-0f21-08d80e51327f
X-MS-TrafficTypeDiagnostic: SA0PR12MB4589:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SA0PR12MB45899E157719D7B0BD67347695800@SA0PR12MB4589.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-Forefront-PRVS: 0431F981D8
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 Zi+jvI/Bc1Do1UzoquT50uT2GUlsbOMKhRKaH9YG1hC6xmlQIzik+CfMt/OlPfGPyMXBvCaDJkragv0NrxA/6kpGb2X72azCK22NfJRHTt5Djdeadbm0uPXe8VrecRUR7CRTZyQhEyN/EqIPA316qKn9RfKYrmQQvrAnks2V8qQi4jAyu34EayN1mhzQeDC1EYWK64VdbeH0kbqucxEiXAIw9UCYCA/g5MIlXeyQTZQe6moG5+TDOKB8fZfrwUkZLB/VjCzaGluFPJlPUiwR+DWVq7WHJtXc2BA0oAoQfzAWgs9hsQTREF0FAQFr9o7SA4L+NMr1LCruofQLfYOIetNevl06swFxHvJCp8xkJs/M2g8lp6ODHpqV6gK31pIk
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN1PR12MB2560.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(7916004)(4636009)(366004)(396003)(39860400002)(346002)(376002)(136003)(52116002)(33716001)(6486002)(16576012)(8936002)(2906002)(8676002)(16526019)(9686003)(7416002)(186003)(4326008)(316002)(478600001)(103116003)(44832011)(956004)(5660300002)(83380400001)(26005)(66476007)(66556008)(66946007)(86362001)(921003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Wvjv2Xh9WtQOcI5jIM34HAH2K6BzPPN7eMtPIeCeGKN9bZofh9ybQh8D3nM183vmKolF8LBus/Hgc4W/KvsWGXrusrnTVPIltUm/DGajJlS429guL9o4l0J6k0IrtPuuuMoW8T05kEWUqe0TFXBPm4xpYC6qziYnYEKxX6PMHW3XGrgU6ockDABRDW3HUXlrv/6ZAf/YmmBH1DJyvhMEp5hiNrwIzDHzp23spX2jXWawyRlt0BLJYSxOIK2IRXNQgjToaeU1NjmsKZEGEHcVCdr/j6hm8Q98H8yfu2MGpc69KWA++1kbP6cMDEhFCLg+BVfJVyf7fZxIqjoF0zC0ACQ4IY119+24zDuhXvvh07WJESaL77QCuXfsmMH4f8eo+2ywkNh2pf3pCSPoEkRc9ZgBDUYjdmzOfscbBaDBMFOHML12CqaK2+rv06sHfVNjicBq11mIHZRl+R+ayCyn4ARXWTgHbxyI3O6CDe33fI4=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 0531b781-295a-4231-0f21-08d80e51327f
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 11 Jun 2020 21:48:37.7911
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 SH+Ce0tvPFOBVX6S3g1525gggKhbJq/Mfr8uBHFu7CJVwmUPQG5f2kFk6Qq11xGH
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SA0PR12MB4589
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

INVPCID instruction handling is mostly same across both VMX and
SVM. So, move the code to common x86.c.

Signed-off-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/kvm/vmx/vmx.c |   78 +-----------------------------------------
 arch/x86/kvm/x86.c     |   89 ++++++++++++++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h     |    2 +
 3 files changed, 92 insertions(+), 77 deletions(-)

```
#### [PATCH] KVM: x86: do not pass poisoned hva to __kvm_set_memory_region
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11600537
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A41CE90
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 18:02:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 88EC620792
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 18:02:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OGGnElLT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728204AbgFKSCH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 14:02:07 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:55036 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727007AbgFKSCG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Jun 2020 14:02:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591898526;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=TaFY/pzHC7fb3rV1r0JXiWmdM/VEPKtAIoA1+kwyi30=;
        b=OGGnElLTKoWlkh8Odk+bsPk0P3gbGdq9oRM7CASTEUD4RCY/uLyvUPHnThY6NN9tZnZLj2
        XPc0nLnkt8wI/er8uD5JEcrIHG1594tYJj+HwzGxfYXIH/CjywWEbHOLjZf0aVJVzXLu2s
        rtojLPNT7PczlpxMdHgy6LFL549Abls=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-465-nQF5lnqxMvidAmlmphna0Q-1; Thu, 11 Jun 2020 14:02:01 -0400
X-MC-Unique: nQF5lnqxMvidAmlmphna0Q-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 18933107ACF2;
        Thu, 11 Jun 2020 18:02:00 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9CE977F4DB;
        Thu, 11 Jun 2020 18:01:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] KVM: x86: do not pass poisoned hva to __kvm_set_memory_region
Date: Thu, 11 Jun 2020 14:01:59 -0400
Message-Id: <20200611180159.26085-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__kvm_set_memory_region does not use the hva at all, so trying to
catch use-after-delete is pointless and, worse, it fails access_ok
now that we apply it to all memslots including private kernel ones.
This fixes an AVIC regression.

Fixes: 09d952c971a5 ("KVM: check userspace_addr for all memslots", 2020-06-01)
Reported-by: Maxim Levitsky <mlevitsk@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/x86.c | 7 +------
 1 file changed, 1 insertion(+), 6 deletions(-)

```
#### [PATCH v1] virtio-mem: add memory via add_memory_driver_managed()
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11599657
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4020F13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:35:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 265A72078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 09:35:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CiYkZgks"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726560AbgFKJfj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 05:35:39 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:20562 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726905AbgFKJfi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Jun 2020 05:35:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591868137;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=skekyVLdwFwBTm754pc77fwSJmldMeXVb8k3yiao8Zo=;
        b=CiYkZgksT71QAo9GQc/TM2XXvtrXM5TycKVm3BzS9JHAF2ZibGak5Fr0oL6MAyf1e1HDMM
        CheY6/Cqqu13PESHqjQIiJrAl3gnT/qroz5sBQHdKdK0gUCkPpeI+e5N2O5ryRgkuk9Oam
        c8oGE03bL2w2c+7fQl+N7mEVJzXdbGI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-46-79N41bhHNyOSrHDxFwNDUg-1; Thu, 11 Jun 2020 05:35:35 -0400
X-MC-Unique: 79N41bhHNyOSrHDxFwNDUg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 17C5E1883605;
        Thu, 11 Jun 2020 09:35:34 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-114-160.ams2.redhat.com [10.36.114.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B303110013C1;
        Thu, 11 Jun 2020 09:35:25 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        "Michael S . Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        teawater <teawaterz@linux.alibaba.com>
Subject: [PATCH v1] virtio-mem: add memory via add_memory_driver_managed()
Date: Thu, 11 Jun 2020 11:35:18 +0200
Message-Id: <20200611093518.5737-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Virtio-mem managed memory is always detected and added by the virtio-mem
driver, never using something like the firmware-provided memory map.
This is the case after an ordinary system reboot, and has to be guaranteed
after kexec. Especially, virtio-mem added memory resources can contain
inaccessible parts ("unblocked memory blocks"), blindly forwarding them
to a kexec kernel is dangerous, as unplugged memory will get accessed
(esp. written).

Let's use the new way of adding special driver-managed memory introduced
in commit 75ac4c58bc0d ("mm/memory_hotplug: introduce
add_memory_driver_managed()").

This will result in no entries in /sys/firmware/memmap ("raw firmware-
provided memory map"), the memory resource will be flagged
IORESOURCE_MEM_DRIVER_MANAGED (esp., kexec_file_load() will not place
kexec images on this memory), and it is exposed as "System RAM
(virtio_mem)" in /proc/iomem, so esp. kexec-tools can properly handle it.

Example /proc/iomem before this change:
  [...]
  140000000-333ffffff : virtio0
    140000000-147ffffff : System RAM
  334000000-533ffffff : virtio1
    338000000-33fffffff : System RAM
    340000000-347ffffff : System RAM
    348000000-34fffffff : System RAM
  [...]

Example /proc/iomem after this change:
  [...]
  140000000-333ffffff : virtio0
    140000000-147ffffff : System RAM (virtio_mem)
  334000000-533ffffff : virtio1
    338000000-33fffffff : System RAM (virtio_mem)
    340000000-347ffffff : System RAM (virtio_mem)
    348000000-34fffffff : System RAM (virtio_mem)
  [...]

Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: teawater <teawaterz@linux.alibaba.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
---

Based on latest Linus' tree (and not a tag) because
- virtio-mem has just been merged via the vhost tree
- add_memory_driver_managed() has been merged a week ago via the -mm tree

I'd like to have this patch in 5.8, with the initial merge of virtio-mem
if possible (so the user space representation of virtio-mem added memory
resources won't change anymore).

---
 drivers/virtio/virtio_mem.c | 25 ++++++++++++++++++++++---
 1 file changed, 22 insertions(+), 3 deletions(-)

```
#### [PATCH v2 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
##### From: Liu Yi L <yi.l.liu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liu Yi L <yi.l.liu@intel.com>
X-Patchwork-Id: 11599889
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BEC2B739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:10:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA81B2081A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 12:10:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728109AbgFKMJP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 08:09:15 -0400
Received: from mga17.intel.com ([192.55.52.151]:41824 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727918AbgFKMJL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 11 Jun 2020 08:09:11 -0400
IronPort-SDR: 
 HEz4hZzLj9qJg06HYIbdF3gxLv3194l3vB5yoR750xJR6Nuy5QkiPa9IsDR9ViL8zHJVZJU60v
 qgbaek5zLHsA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Jun 2020 05:09:09 -0700
IronPort-SDR: 
 5cIVrk4qVhZY9UMB6zFu6O9R1R2+oLGGKf67PZW/Yj3+a1SvbxkEgJD6QuMK8ednUJ9ep5AEZA
 LQV6ih69Xk6A==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,499,1583222400";
   d="scan'208";a="419082467"
Received: from jacob-builder.jf.intel.com ([10.7.199.155])
  by orsmga004.jf.intel.com with ESMTP; 11 Jun 2020 05:09:09 -0700
From: Liu Yi L <yi.l.liu@intel.com>
To: alex.williamson@redhat.com, eric.auger@redhat.com,
        baolu.lu@linux.intel.com, joro@8bytes.org
Cc: kevin.tian@intel.com, jacob.jun.pan@linux.intel.com,
        ashok.raj@intel.com, yi.l.liu@intel.com, jun.j.tian@intel.com,
        yi.y.sun@intel.com, jean-philippe@linaro.org, peterx@redhat.com,
        hao.wu@intel.com, iommu@lists.linux-foundation.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v2 01/15] vfio/type1: Refactor vfio_iommu_type1_ioctl()
Date: Thu, 11 Jun 2020 05:15:20 -0700
Message-Id: <1591877734-66527-2-git-send-email-yi.l.liu@intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1591877734-66527-1-git-send-email-yi.l.liu@intel.com>
References: <1591877734-66527-1-git-send-email-yi.l.liu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch refactors the vfio_iommu_type1_ioctl() to use switch instead of
if-else, and each cmd got a helper function.

Cc: Kevin Tian <kevin.tian@intel.com>
CC: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Eric Auger <eric.auger@redhat.com>
Cc: Jean-Philippe Brucker <jean-philippe@linaro.org>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Lu Baolu <baolu.lu@linux.intel.com>
Suggested-by: Christoph Hellwig <hch@infradead.org>
Signed-off-by: Liu Yi L <yi.l.liu@intel.com>
---
 drivers/vfio/vfio_iommu_type1.c | 183 +++++++++++++++++++++++-----------------
 1 file changed, 105 insertions(+), 78 deletions(-)

```
#### [PATCH RFC v8 01/11] vhost: option to fetch descriptors through an independent struct
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11599767
Return-Path: <SRS0=3MuQ=7Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E1D42138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 11:35:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA3FB207ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 11 Jun 2020 11:35:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="II04Nj5z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728054AbgFKLe3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jun 2020 07:34:29 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:26589 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727869AbgFKLeY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Jun 2020 07:34:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1591875262;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=wjgEeFu3a+LIiqg+5XiliZ73/V0mxb4sydm2yHd7x/A=;
        b=II04Nj5zN8r7GmDe6yjU2bMDck1uuPXOicr4x31xmmiwAZ1XnpNko3g7OGTX2Bi+bhjLAv
        MioVrJOW+pEJeR5bAq1PM5vbUuwSKpaAOHOeIFzwCilvFbDjOgcy0eZQzeyT0h4gbe4enD
        uFDsDQbsfGL2xeg3FF8pjfx0pmYWiHo=
Received: from mail-wm1-f70.google.com (mail-wm1-f70.google.com
 [209.85.128.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-273-5r2XbFd2PqKN291XudVHiA-1; Thu, 11 Jun 2020 07:34:20 -0400
X-MC-Unique: 5r2XbFd2PqKN291XudVHiA-1
Received: by mail-wm1-f70.google.com with SMTP id g84so1234621wmf.4
        for <kvm@vger.kernel.org>; Thu, 11 Jun 2020 04:34:20 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:references
         :mime-version:content-disposition:content-transfer-encoding
         :in-reply-to;
        bh=wjgEeFu3a+LIiqg+5XiliZ73/V0mxb4sydm2yHd7x/A=;
        b=A+fQj6TBO8cFcAbUl1jqcqQ9Ur/fpE5MT7LLHprO7fy1PH5VuD3t9aIOuiAeIDyLvA
         q1DUjyEsbItkuXPRqTcBDHP8/o/pDBCKxHFAd047tuIP6j6MHOEDQLmLBQnlhjq7MCUE
         ZZgSXO0HAnMJJFJFEojMrHguqwN1n8sB/jQtmVwKCsIDzLfBS0Zso+ovijJ1AzmG9Pjd
         qOMJHmIqUv8QeUPTqnDcq6xdIPV0aHxXbdp73hp3SrXDudm8UnEtSrIO4QGq9jhr+Fhv
         riPiQgm4K5OIPkCV1jKR+AUvE2i8+6IqXakMJ648dcfEza/rHx8rZjD3iCNY0SoWE2zO
         cX/w==
X-Gm-Message-State: AOAM530GsjoE66jV5/B1RQdp217gVKbC0Ynbpv0QGas7F442At6GlGuw
        ATzNfzL440ITcPLV2iXjFX0TsJA41YmLmXc/F11YZ3BLOV84Ff58vDO+ETmVL4ug+j8e5L3DdQt
        CHxwzi5HwnD+G
X-Received: by 2002:a1c:a1c5:: with SMTP id k188mr8099520wme.41.1591875259340;
        Thu, 11 Jun 2020 04:34:19 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxJjTP+Jltfvil3r7Eu5Xs33+bjgt+vVMAo54RDN03ftXfSQjwjTV1cnO4g7LuNMX5q4+LB7g==
X-Received: by 2002:a1c:a1c5:: with SMTP id k188mr8099486wme.41.1591875258829;
        Thu, 11 Jun 2020 04:34:18 -0700 (PDT)
Received: from redhat.com (bzq-79-181-55-232.red.bezeqint.net.
 [79.181.55.232])
        by smtp.gmail.com with ESMTPSA id
 f71sm3316834wmf.22.2020.06.11.04.34.17
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 11 Jun 2020 04:34:18 -0700 (PDT)
Date: Thu, 11 Jun 2020 07:34:16 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, virtualization@lists.linux-foundation.org,
        netdev@vger.kernel.org, Jason Wang <jasowang@redhat.com>,
        eperezma@redhat.com
Subject: [PATCH RFC v8 01/11] vhost: option to fetch descriptors through an
 independent struct
Message-ID: <20200611113404.17810-2-mst@redhat.com>
References: <20200611113404.17810-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200611113404.17810-1-mst@redhat.com>
X-Mailer: git-send-email 2.27.0.106.g8ac3dc51b1
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The idea is to support multiple ring formats by converting
to a format-independent array of descriptors.

This costs extra cycles, but we gain in ability
to fetch a batch of descriptors in one go, which
is good for code cache locality.

When used, this causes a minor performance degradation,
it's been kept as simple as possible for ease of review.
A follow-up patch gets us back the performance by adding batching.

To simplify benchmarking, I kept the old code around so one can switch
back and forth between old and new code. This will go away in the final
submission.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Eugenio Pérez <eperezma@redhat.com>
Link: https://lore.kernel.org/r/20200401183118.8334-2-eperezma@redhat.com
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 305 +++++++++++++++++++++++++++++++++++++++++-
 drivers/vhost/vhost.h |  16 +++
 2 files changed, 320 insertions(+), 1 deletion(-)

```
