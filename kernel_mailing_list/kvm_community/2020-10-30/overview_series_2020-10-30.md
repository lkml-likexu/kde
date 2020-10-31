#### 
##### 

```c
```
#### [PATCH v5 01/15] drm/exynos: Stop using frame_vector helpers
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11869131
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8B527C63697
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 10:11:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2598521734
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 10:11:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="aKlzbno0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726540AbgJ3KK4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 06:10:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50312 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726198AbgJ3KIk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 06:08:40 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E45AAC0613D4
        for <kvm@vger.kernel.org>; Fri, 30 Oct 2020 03:08:39 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id d3so2388971wma.4
        for <kvm@vger.kernel.org>; Fri, 30 Oct 2020 03:08:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=5HSDx6z2iUpxgLk7STJ2LBrJWLho+Vrj3pPui9pXoI8=;
        b=aKlzbno033YLitqk2cu6P3GxwmA6KJS6TWty9sQ9M/iPUxDJOU1RZXpRtUUIGF7xnO
         Swv3BBEn+EDEZ2SaP7J2IxU1yLczM6UZuRRDl5xraJR6v6/wOJB5FFwkxWAxwAC34NZq
         IyAPMBXZG3141RKZo4/lB3rcCDQNXkL02GSOs=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=5HSDx6z2iUpxgLk7STJ2LBrJWLho+Vrj3pPui9pXoI8=;
        b=EahtumprvL3rsl0SC+CCWHJq8qdyPQC5TODamysa/yEelIN6CbnPYL7u9TbN0B+rWV
         g+UGmWwKqOtPLjXPIG7BwVAaWiygYqXjYWel14YYpQYiCMJXfAxVM8ko/rkb/9w8pzJY
         DMbJ1QhGdcnepDMQR0jQeLjIU3IXv8pKWrhF2laZriNXVNC5Lw8SOQMuWrx74wktQYeb
         TcLjmrOHHDko4qb/t/uHtB0lP5wVLLQCs/Q8vGhOgu6Q/99S670wLoUGjNJeRHoZNZYD
         CmKrpvcDgvzTor76f2uloi0KhItWiR/wcmxt+w/rVvZKpo8+oaTv2YyFa0adbF7Cnh8w
         xkCQ==
X-Gm-Message-State: AOAM533bQYUg2zIoH+45BoqSvQaXBwSda/I39NeUccP/ZgF9l8hDg+Zq
        RYkKEMyioFKBETb2Nor8UhfGDg==
X-Google-Smtp-Source: 
 ABdhPJylI0KOMbymdWD4o/sLacOvb/pRDxaSEXtH+RKYbEbEetFTaDUFpNXr6iZ7QCn2hD5tBOFSzw==
X-Received: by 2002:a1c:b486:: with SMTP id
 d128mr1694999wmf.164.1604052518673;
        Fri, 30 Oct 2020 03:08:38 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 v189sm4430947wmg.14.2020.10.30.03.08.37
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 30 Oct 2020 03:08:37 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
 linux-arm-kernel@lists.infradead.org, linux-samsung-soc@vger.kernel.org,
 linux-media@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>,
 John Hubbard <jhubbard@nvidia.com>, Daniel Vetter <daniel.vetter@intel.com>,
 Jason Gunthorpe <jgg@ziepe.ca>, Inki Dae <inki.dae@samsung.com>,
 Joonyoung Shim <jy0922.shim@samsung.com>,
 Seung-Woo Kim <sw0312.kim@samsung.com>,
 Kyungmin Park <kyungmin.park@samsung.com>, Kukjin Kim <kgene@kernel.org>,
 Krzysztof Kozlowski <krzk@kernel.org>,
 Andrew Morton <akpm@linux-foundation.org>,
 =?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Jan Kara <jack@suse.cz>, Dan Williams <dan.j.williams@intel.com>
Subject: [PATCH v5 01/15] drm/exynos: Stop using frame_vector helpers
Date: Fri, 30 Oct 2020 11:08:01 +0100
Message-Id: <20201030100815.2269-2-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201030100815.2269-1-daniel.vetter@ffwll.ch>
References: <20201030100815.2269-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All we need are a pages array, pin_user_pages_fast can give us that
directly. Plus this avoids the entire raw pfn side of get_vaddr_frames.

Reviewed-by: John Hubbard <jhubbard@nvidia.com>
Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Cc: Inki Dae <inki.dae@samsung.com>
Cc: Joonyoung Shim <jy0922.shim@samsung.com>
Cc: Seung-Woo Kim <sw0312.kim@samsung.com>
Cc: Kyungmin Park <kyungmin.park@samsung.com>
Cc: Kukjin Kim <kgene@kernel.org>
Cc: Krzysztof Kozlowski <krzk@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: Jérôme Glisse <jglisse@redhat.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: linux-mm@kvack.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-media@vger.kernel.org
Signed-off-by: Daniel Vetter <daniel.vetter@ffwll.ch>
---
v2: Use unpin_user_pages_dirty_lock (John)
---
 drivers/gpu/drm/exynos/Kconfig          |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c | 47 +++++++++++--------------
 2 files changed, 20 insertions(+), 28 deletions(-)

```
#### [GIT PULL] KVM/arm64 fixes for 5.10, take #1
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11870207
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-17.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D7202C55179
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89C292151B
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:28 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604076028;
	bh=5IdJB+vSy9WtqFoTUhuMK/Ne2TdAtmbDZodcpICYmnU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=ZLAKna01+xa8sFc5cb87EYzAcR/rZGulBIpNB1FIY0zZiCMaVUaMIWy31EyJXsCiL
	 SfRcvF5d493GchmgJgey36b2yP8ZNhCKzwUpM0m1BFxPyJhpArv42KINi1U7WbEGoO
	 xjjT41FWyn7hZhM87mFZCm5gCar/Bponavc5YY2M=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727115AbgJ3Qk1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 12:40:27 -0400
Received: from mail.kernel.org ([198.145.29.99]:56020 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726920AbgJ3Qk0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 12:40:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 692BA20756;
        Fri, 30 Oct 2020 16:40:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604076025;
        bh=5IdJB+vSy9WtqFoTUhuMK/Ne2TdAtmbDZodcpICYmnU=;
        h=From:To:Cc:Subject:Date:From;
        b=mY2QczB+bo87U8fMn7qv4VHllqSccKIUuhsW02/aX4Yuj8hqMHxzWIpI/pbvM9juv
         TIJ34uxNPzi5eMZdtSGLXP7Rq5BKtOojZdB/xkk1SA9Aoe32WIxPEu2mkS0OK998DC
         PcLczwkdcqVxVXvgyHHQBRK9HdIjhMRqE5f0cSfs=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kYXRu-005noK-96; Fri, 30 Oct 2020 16:40:22 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>, Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Qais Yousef <qais.yousef@arm.com>,
        Quentin Perret <qperret@google.com>,
        Santosh Shukla <sashukla@nvidia.com>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [GIT PULL] KVM/arm64 fixes for 5.10, take #1
Date: Fri, 30 Oct 2020 16:40:05 +0000
Message-Id: <20201030164017.244287-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com, gshan@redhat.com,
 james.morse@arm.com, mark.rutland@arm.com, qais.yousef@arm.com,
 qperret@google.com, sashukla@nvidia.com, vladimir.murzin@arm.com,
 will@kernel.org, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

[Apologies for the spam, I appear to have forgotten to Cc the lists in
 my initial posting]

Hi Paolo,

It was good to see you (and everyone else) at KVM Forum this week!

And to celebrate, here's a first batch of fixes for KVM/arm64. A bunch
of them are addressing issues introduced by the invasive changes that
took place in the 5.10 merge window (MM, nVHE host entry). A few
others are addressing some older bugs (VFIO PTE mappings, AArch32
debug, composite huge pages), and a couple of improvements
(HYP-visible capabilities are made more robust).

Please pull,

	M.

The following changes since commit 4e5dc64c43192b4fd4c96ac150a8f013065f5f5b:

  Merge branches 'kvm-arm64/pt-new' and 'kvm-arm64/pmu-5.9' into kvmarm-master/next (2020-10-02 09:25:55 +0100)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-5.10-1

for you to fetch changes up to 22f553842b14a1289c088a79a67fb479d3fa2a4e:

  KVM: arm64: Handle Asymmetric AArch32 systems (2020-10-30 16:06:22 +0000)

----------------------------------------------------------------
KVM/arm64 fixes for 5.10, take #1

- Force PTE mapping on device pages provided via VFIO
- Fix detection of cacheable mapping at S2
- Fallback to PMD/PTE mappings for composite huge pages
- Fix accounting of Stage-2 PGD allocation
- Fix AArch32 handling of some of the debug registers
- Simplify host HYP entry
- Fix stray pointer conversion on nVHE TLB invalidation
- Fix initialization of the nVHE code
- Simplify handling of capabilities exposed to HYP
- Nuke VCPUs caught using a forbidden AArch32 EL0

----------------------------------------------------------------
Gavin Shan (1):
      KVM: arm64: Use fallback mapping sizes for contiguous huge page sizes

Marc Zyngier (4):
      KVM: arm64: Don't corrupt tpidr_el2 on failed HVC call
      KVM: arm64: Remove leftover kern_hyp_va() in nVHE TLB invalidation
      KVM: arm64: Drop useless PAN setting on host EL1 to EL2 transition
      KVM: arm64: Fix AArch32 handling of DBGD{CCINT,SCRext} and DBGVCR

Mark Rutland (3):
      KVM: arm64: Factor out is_{vhe,nvhe}_hyp_code()
      arm64: cpufeature: reorder cpus_have_{const, final}_cap()
      arm64: cpufeature: upgrade hyp caps to final

Qais Yousef (1):
      KVM: arm64: Handle Asymmetric AArch32 systems

Santosh Shukla (1):
      KVM: arm64: Force PTE mapping on fault resulting in a device mapping

Will Deacon (2):
      KVM: arm64: Allocate stage-2 pgd pages with GFP_KERNEL_ACCOUNT
      KVM: arm64: Fix masks in stage2_pte_cacheable()

 arch/arm64/include/asm/cpufeature.h | 40 ++++++++++++++++++++++++++++---------
 arch/arm64/include/asm/kvm_host.h   |  1 +
 arch/arm64/include/asm/virt.h       |  9 ++++-----
 arch/arm64/kernel/image-vars.h      |  1 -
 arch/arm64/kvm/arm.c                | 19 ++++++++++++++++++
 arch/arm64/kvm/hyp/nvhe/host.S      |  2 --
 arch/arm64/kvm/hyp/nvhe/hyp-init.S  | 23 ++++++++++++++-------
 arch/arm64/kvm/hyp/nvhe/tlb.c       |  1 -
 arch/arm64/kvm/hyp/pgtable.c        |  4 ++--
 arch/arm64/kvm/mmu.c                | 27 ++++++++++++++++++-------
 arch/arm64/kvm/sys_regs.c           |  6 +++---
 11 files changed, 96 insertions(+), 37 deletions(-)

From patchwork Fri Oct 30 16:40:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11870213
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B5E80C55178
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 62A582151B
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604076027;
	bh=FdAucMQjtKAFDFTUjWlGgj+oR3wWcmsUGvauZ/aCLXI=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=luW3SMp04eK9oJgeVoPA5/nVI+5E7jwxRNAEuIjadfueZKvjq6iI5iNauKmsZ+4Hy
	 m42vm2EylahP9U7+AwIymYav59kBHUh6PGlA9SkaB7VsYSwXstWF/N+N5pD3DmH65n
	 k0VGXKgG+KBCoz5MTswA3RLERMiuvjNdkrh02BUw=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727086AbgJ3Qk1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 12:40:27 -0400
Received: from mail.kernel.org ([198.145.29.99]:56040 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726072AbgJ3Qk0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 12:40:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9F2922075E;
        Fri, 30 Oct 2020 16:40:25 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604076025;
        bh=FdAucMQjtKAFDFTUjWlGgj+oR3wWcmsUGvauZ/aCLXI=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=vNUiX9jU9UztYq5wLUe6zn2MN5nLk0yeP/8ipFoFw1zVxMOrygf15l2IOMLWaVI4L
         fBFj13z2VYBAxprsTDd+1S2k3kvbKQ3RjeelPPathZusPRrA2BgT2FmDipr+SDzkfO
         ww+Pzj/t2jJtf0WWc49XNnaiUiop/E+m723XE/l4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kYXRv-005noK-QG; Fri, 30 Oct 2020 16:40:23 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>, Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Qais Yousef <qais.yousef@arm.com>,
        Quentin Perret <qperret@google.com>,
        Santosh Shukla <sashukla@nvidia.com>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 02/12] KVM: arm64: Remove leftover kern_hyp_va() in nVHE TLB
 invalidation
Date: Fri, 30 Oct 2020 16:40:07 +0000
Message-Id: <20201030164017.244287-3-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201030164017.244287-1-maz@kernel.org>
References: <20201030164017.244287-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com, gshan@redhat.com,
 james.morse@arm.com, mark.rutland@arm.com, qais.yousef@arm.com,
 qperret@google.com, sashukla@nvidia.com, vladimir.murzin@arm.com,
 will@kernel.org, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The new calling convention says that pointers coming from the SMCCC
interface are turned into their HYP version in the host HVC handler.
However, there is still a stray kern_hyp_va() in the TLB invalidation
code, which could result in a corrupted pointer.

Drop the spurious conversion.

Fixes: a071261d9318 ("KVM: arm64: nVHE: Fix pointers during SMCCC convertion")
Signed-off-by: Marc Zyngier <maz@kernel.org>
Link: https://lore.kernel.org/r/20201026095116.72051-3-maz@kernel.org
---
 arch/arm64/kvm/hyp/nvhe/tlb.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH v6 1/5] vfio/mdev: Register mdev bus earlier during boot
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11868481
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5CA2AC4742C
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 05:05:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1462F221F9
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 05:05:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726237AbgJ3FFK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 01:05:10 -0400
Received: from mga06.intel.com ([134.134.136.31]:5284 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726042AbgJ3FFJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 01:05:09 -0400
IronPort-SDR: 
 HRKAOCkQB0XhU9b6UnZOVSYS/rFK62PwaV5U0QV1Cf8ugPYUm61jebuHELgWraSBfIDzCxYVUd
 xVfq+yHElVcQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9789"; a="230196547"
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="230196547"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Oct 2020 22:05:08 -0700
IronPort-SDR: 
 DBvYloqtZm7ZhjV0oDjwAGVxl8PMUs3l2Umcf5zMlwrfkQTu6eWd9tYUYj/E9GzsYU7VVH7G8V
 uo/wGP6DpSDQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="425261534"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga001.fm.intel.com with ESMTP; 29 Oct 2020 22:05:04 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: Robin Murphy <robin.murphy@arm.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Kevin Tian <kevin.tian@intel.com>,
        Ashok Raj <ashok.raj@intel.com>,
        Dave Jiang <dave.jiang@intel.com>,
        Liu Yi L <yi.l.liu@intel.com>, Zeng Xin <xin.zeng@intel.com>,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>
Subject: [PATCH v6 1/5] vfio/mdev: Register mdev bus earlier during boot
Date: Fri, 30 Oct 2020 12:58:05 +0800
Message-Id: <20201030045809.957927-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20201030045809.957927-1-baolu.lu@linux.intel.com>
References: <20201030045809.957927-1-baolu.lu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move mdev bus registration earlier than IOMMU probe processing so that
the IOMMU drivers could be able to set iommu_ops for the mdev bus. This
only applies when vfio-mdev module is setected to be built-in.

Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/vfio/mdev/mdev_core.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] kvm: s390: pv: Mark mm as protected after the set secure parameters and improve cleanup
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11869787
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CC06EC55178
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 14:01:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5775C221EB
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 14:01:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="MONT8pgO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726224AbgJ3OB6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 10:01:58 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:49028 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726754AbgJ3OB4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 30 Oct 2020 10:01:56 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09UDWgrf040664;
        Fri, 30 Oct 2020 10:01:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=XwBZSiGdxOOiSXm4d9FIjQh4CivXkkYs7jASRRe1l/U=;
 b=MONT8pgOiQOE2oW+cO09/fzwZYBMArqlM1m7r0YL88C5YmJq8Q7IQUivTDtlft76FhdC
 hRtsdLhseCy3WI4sJIu7TFlpCYJ1lZbLApUXPPB0d/ozsjv2uaUGx037ZRr/wAqC3h9r
 1ezLVOQdW/mq6xiinChNULOk9140YcPByCd3PKQLkhWoixsBwGc38lBY1KasHe3dvtcS
 a9lb+AKrhxPjr8tyKUSTue5VuujACK+xQegO3XU1enP5HSgzhDOnXnqAbZkWSVRZlpIX
 sZOlS9E2CQ4Bmi+ZGXAYQjj3J5OfsUHJNzfMt+yQWBiSC70SBCpbuCmXWwhEX5T40G89 Qg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34geqbjmry-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 30 Oct 2020 10:01:54 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09UDYDpQ050023;
        Fri, 30 Oct 2020 10:01:53 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34geqbjmmx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 30 Oct 2020 10:01:53 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09UDwiCs022488;
        Fri, 30 Oct 2020 14:01:46 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03fra.de.ibm.com with ESMTP id 34fpvrgssd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 30 Oct 2020 14:01:46 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 09UE1hOP28377432
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 30 Oct 2020 14:01:43 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 89ED2A405B;
        Fri, 30 Oct 2020 14:01:43 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C41D4A4055;
        Fri, 30 Oct 2020 14:01:42 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 30 Oct 2020 14:01:42 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, borntraeger@de.ibm.com,
        imbrenda@linux.ibm.com
Subject: [PATCH] kvm: s390: pv: Mark mm as protected after the set secure
 parameters and improve cleanup
Date: Fri, 30 Oct 2020 10:01:41 -0400
Message-Id: <20201030140141.106641-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-10-30_04:2020-10-30,2020-10-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 clxscore=1015 mlxscore=0 spamscore=0 priorityscore=1501 impostorscore=0
 suspectscore=13 bulkscore=0 adultscore=0 mlxlogscore=999 phishscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010300098
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We can only have protected guest pages after a successful set secure
parameters call as only then the UV allows imports and unpacks.

By moving the test we can now also check for it in s390_reset_acc()
and do an early return if it is 0.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 arch/s390/kvm/pv.c       | 3 ++-
 arch/s390/mm/gmap.c      | 2 ++
 3 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Fix NULL dereference at kvm_msr_ignored_check()
##### From: Takashi Iwai <tiwai@suse.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Takashi Iwai <tiwai@suse.de>
X-Patchwork-Id: 11870027
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 14830C4363A
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:14:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BFCAF20756
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:14:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726875AbgJ3POS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 11:14:18 -0400
Received: from mx2.suse.de ([195.135.220.15]:58886 "EHLO mx2.suse.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726806AbgJ3POS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 11:14:18 -0400
X-Virus-Scanned: by amavisd-new at test-mx.suse.de
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id A9BB9ADE8;
        Fri, 30 Oct 2020 15:14:16 +0000 (UTC)
From: Takashi Iwai <tiwai@suse.de>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Joerg Roedel <jroedel@suse.de>
Subject: [PATCH] KVM: x86: Fix NULL dereference at kvm_msr_ignored_check()
Date: Fri, 30 Oct 2020 16:14:14 +0100
Message-Id: <20201030151414.20165-1-tiwai@suse.de>
X-Mailer: git-send-email 2.16.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The newly introduced kvm_msr_ignored_check() tries to print error or
debug messages via vcpu_*() macros, but those may cause Oops when NULL
vcpu is passed for KVM_GET_MSRS ioctl.

Fix it by replacing the print calls with kvm_*() macros.

(Note that this will leave vcpu argument completely unused in the
 function, but I didn't touch it to make the fix as small as
 possible.  A clean up may be applied later.)

Fixes: 12bc2132b15e ("KVM: X86: Do the same ignore_msrs check for feature msrs")
BugLink: https://bugzilla.suse.com/show_bug.cgi?id=1178280
Cc: <stable@vger.kernel.org>
Signed-off-by: Takashi Iwai <tiwai@suse.de>
---

Alternatively, we may fix all vcpu_*() macros to handle NULL vcpu
object, too, as mentioned in the bugzilla entry above.
If that's a preferred change, let me know.  Thanks!

 arch/x86/kvm/x86.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: replace static const variables with macros
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11870405
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 79866C00A89
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 17:40:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 18991221EB
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 17:40:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="jWeuNdrA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726384AbgJ3Rk0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 13:40:26 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:40708 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725922AbgJ3RkZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 30 Oct 2020 13:40:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604079624;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZF7qERUUkIeahbTOL6C12Vf0o83/16+lgKINW+6oyco=;
        b=jWeuNdrAuCdxZT7vF+Yn7oJ8xt4LA3zG2Kv9Cje3uyrUkpeAvqMfYPW3Cv0rLxBGukFKPw
        q5SK+OBaWoWlrhI19xvu7oBhRVE6watPyZH0Un5p0YSHh1XmVhCUWdF1k6B8Zpg18iMSa5
        uEH0kVBjzPxCqkZ6YrHGYGK5siWnNyU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-525-CPmwK-hqOJeHd46fAALIrg-1; Fri, 30 Oct 2020 13:40:16 -0400
X-MC-Unique: CPmwK-hqOJeHd46fAALIrg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 957BD192AB64;
        Fri, 30 Oct 2020 17:40:14 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 472555DA2A;
        Fri, 30 Oct 2020 17:40:14 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: replace static const variables with macros
Date: Fri, 30 Oct 2020 13:40:13 -0400
Message-Id: <20201030174013.3961199-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even though the compiler is able to replace static const variables with
their value, it will warn about them being unused when Linux is built with W=1.
Use good old macros instead, this is not C++.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c  | 10 +++++-----
 arch/x86/kvm/mmu/spte.c | 16 ++++++++--------
 arch/x86/kvm/mmu/spte.h | 16 ++++++++--------
 3 files changed, 21 insertions(+), 21 deletions(-)

```
#### [PATCH 04/12] KVM: arm64: Allocate stage-2 pgd pages with GFP_KERNEL_ACCOUNT
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11870209
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A5F1DC00A89
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 470112076E
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604076031;
	bh=aO4GPkhwFMp13Q20m0gqeo+N2mUl41ti48Pxp5IzoSE=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=B05h8m4W3VrM7pVf+4v9VcEKMKV40ijBG9LRxnmfbhhF1M1Ut6Cwq/YEoE5X6AKha
	 NJMiXG93En39W9nStPEtALZknj3xTn3EksZsjId35+uTFsB+lMj3M+T0pFIGE/QtRU
	 iXWoBrm4n/3w2mgQwL6uqh3iT9lk0MbhbaFeCu50=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727190AbgJ3Qka (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 12:40:30 -0400
Received: from mail.kernel.org ([198.145.29.99]:56020 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727109AbgJ3Qk1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 12:40:27 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 14C5420A8B;
        Fri, 30 Oct 2020 16:40:27 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604076027;
        bh=aO4GPkhwFMp13Q20m0gqeo+N2mUl41ti48Pxp5IzoSE=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=ekcBw1GeLqqs9vwF/sJFpZa7/tVvioeWhSigK4ooXlJxfHdqffkFaQjHRKsp90y8p
         zkCyoj9cunNdRn7h5TfAFz6Wah9AyZ2zLBZSxORFj/Z3/Pqs3WZzQUhk3WfqYFyusK
         ti2zdyDDHbAJwgdBn9kfq8UfQQoA6m82d9YmGVG8=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kYXRx-005noK-9i; Fri, 30 Oct 2020 16:40:25 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>, Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Qais Yousef <qais.yousef@arm.com>,
        Quentin Perret <qperret@google.com>,
        Santosh Shukla <sashukla@nvidia.com>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 04/12] KVM: arm64: Allocate stage-2 pgd pages with
 GFP_KERNEL_ACCOUNT
Date: Fri, 30 Oct 2020 16:40:09 +0000
Message-Id: <20201030164017.244287-5-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201030164017.244287-1-maz@kernel.org>
References: <20201030164017.244287-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com, gshan@redhat.com,
 james.morse@arm.com, mark.rutland@arm.com, qais.yousef@arm.com,
 qperret@google.com, sashukla@nvidia.com, vladimir.murzin@arm.com,
 will@kernel.org, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Will Deacon <will@kernel.org>

For consistency with the rest of the stage-2 page-table page allocations
(performing using a kvm_mmu_memory_cache), ensure that __GFP_ACCOUNT is
included in the GFP flags for the PGD pages.

Signed-off-by: Will Deacon <will@kernel.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Gavin Shan <gshan@redhat.com>
Cc: Marc Zyngier <maz@kernel.org>
Cc: Quentin Perret <qperret@google.com>
Link: https://lore.kernel.org/r/20201026144423.24683-1-will@kernel.org
---
 arch/arm64/kvm/hyp/pgtable.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 03/12] KVM: arm64: Drop useless PAN setting on host EL1 to EL2 transition
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11870211
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 39EA5C55178
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D68CC221FA
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 16:40:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604076030;
	bh=C2KHtdO9bCq4PJbhH/iBlIoYeIiXNpTc5az68+9hcHQ=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=lzr29iPDQVlgXmhk0imNBnDp94HrvGFpmkOA4NhnfYOnO7+BMTUj0w4OAbILxA4J2
	 Z9n3xILqUhMS+t++yThoYB7CbOjMLfEHEd8Wo92p3rZAcvmi7wWPmP0i/f5pepLiIV
	 8Ytw6h3Ua7OS5rq8zcU3vDNsOpWvYcVJYSk/OQHo=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727159AbgJ3Qk3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 12:40:29 -0400
Received: from mail.kernel.org ([198.145.29.99]:56040 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727083AbgJ3Qk1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 12:40:27 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 5942B2076E;
        Fri, 30 Oct 2020 16:40:26 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604076026;
        bh=C2KHtdO9bCq4PJbhH/iBlIoYeIiXNpTc5az68+9hcHQ=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=P9wJff+MXWAld7WxezhIEVfGNg+0Vc5V14Xl38wuL6ordof+JXD0ysCTMiVRhWzJ0
         5fG85OCRSBTG/s/WOKdBpNNVXkZkd63tHgbutMIzCyagp0MUIWkhQ9xYFQd3iFcxiR
         Ow2ItBsgl8agM9N98sga4t1lOQ0/PvZKVvlYr5O4=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kYXRw-005noK-I5; Fri, 30 Oct 2020 16:40:24 +0000
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: David Brazdil <dbrazdil@google.com>, Gavin Shan <gshan@redhat.com>,
        James Morse <james.morse@arm.com>,
        Mark Rutland <mark.rutland@arm.com>,
        Qais Yousef <qais.yousef@arm.com>,
        Quentin Perret <qperret@google.com>,
        Santosh Shukla <sashukla@nvidia.com>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        kernel-team@android.com, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org, linux-arm-kernel@lists.infradead.org
Subject: [PATCH 03/12] KVM: arm64: Drop useless PAN setting on host EL1 to EL2
 transition
Date: Fri, 30 Oct 2020 16:40:08 +0000
Message-Id: <20201030164017.244287-4-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20201030164017.244287-1-maz@kernel.org>
References: <20201030164017.244287-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: pbonzini@redhat.com, dbrazdil@google.com, gshan@redhat.com,
 james.morse@arm.com, mark.rutland@arm.com, qais.yousef@arm.com,
 qperret@google.com, sashukla@nvidia.com, vladimir.murzin@arm.com,
 will@kernel.org, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 kernel-team@android.com, kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Setting PSTATE.PAN when entering EL2 on nVHE doesn't make much
sense as this bit only means something for translation regimes
that include EL0. This obviously isn't the case in the nVHE case,
so let's drop this setting.

Signed-off-by: Marc Zyngier <maz@kernel.org>
Reviewed-by: Vladimir Murzin <vladimir.murzin@arm.com>
Link: https://lore.kernel.org/r/20201026095116.72051-4-maz@kernel.org
---
 arch/arm64/kvm/hyp/nvhe/host.S | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH RESEND v13 01/10] KVM: x86: Move common set/get handler of MSR_IA32_DEBUGCTLMSR to VMX
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11868415
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 56340C4363A
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 03:56:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 09F4F20725
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 03:56:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726309AbgJ3D4l (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 23:56:41 -0400
Received: from mga09.intel.com ([134.134.136.24]:4238 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725780AbgJ3D4k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 23:56:40 -0400
IronPort-SDR: 
 DNDlacXL2VS4RFJZ50Ngw+icid+V5IwIvgjKug3z4/kWW9kopNt6CFPwuL+1s2dzQ/hKPyy32a
 C8TvSHw/OA0A==
X-IronPort-AV: E=McAfee;i="6000,8403,9789"; a="168685725"
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="168685725"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Oct 2020 20:56:39 -0700
IronPort-SDR: 
 Fd42gcGrJKxz9F3FkhPrRZTMExA3gHXJ3sGlRNmPOc2nQO9jQPviiZnFYuwR/mWVYidTTeo5fe
 bEMUd9GyTY0Q==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="525770385"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 29 Oct 2020 20:56:36 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org, "H . Peter Anvin" <hpa@zytor.com>,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH RESEND v13 01/10] KVM: x86: Move common set/get handler of
 MSR_IA32_DEBUGCTLMSR to VMX
Date: Fri, 30 Oct 2020 11:52:11 +0800
Message-Id: <20201030035220.102403-2-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20201030035220.102403-1-like.xu@linux.intel.com>
References: <20201030035220.102403-1-like.xu@linux.intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SVM already has specific handlers of MSR_IA32_DEBUGCTLMSR in the
svm_get/set_msr, so the x86 common part can be safely moved to VMX.

Add vmx_supported_debugctl() to refactor the throwing logic of #GP.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/capabilities.h |  5 +++++
 arch/x86/kvm/vmx/vmx.c          | 19 ++++++++++++++++---
 arch/x86/kvm/x86.c              | 13 -------------
 3 files changed, 21 insertions(+), 16 deletions(-)

```
#### [PATCH] [v3] x86: apic: avoid -Wshadow warning in header
##### From: Arnd Bergmann <arnd@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Arnd Bergmann <arnd@kernel.org>
X-Patchwork-Id: 11869795
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3F8E5C56201
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 14:08:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C076C2076E
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 14:08:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1604066931;
	bh=gVwo9EBasTd5741/ywKxMppouneV4DWFezQFj6Bex30=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=JPF9dF4dVASNmY0fQrQfWqbeuE82LhAtqsvIYrejtHJJEkxf2EVTSyzDvdaHRwhC0
	 pvP4/mu8iSVnhWOYVwdxfje4QJUXdyB70WtsTenJAGM1jg3MMw+GEUUk8Zn0965cbc
	 UT2+Ew+XKwxMUcFfDdMUm7wv3Al/mJXC2ShOdwNE=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726784AbgJ3OIs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 10:08:48 -0400
Received: from mail.kernel.org ([198.145.29.99]:55052 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726178AbgJ3OIr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 10:08:47 -0400
Received: from localhost.localdomain
 (HSI-KBW-46-223-126-90.hsi.kabel-badenwuerttemberg.de [46.223.126.90])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 51DEC206F7;
        Fri, 30 Oct 2020 14:08:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1604066923;
        bh=gVwo9EBasTd5741/ywKxMppouneV4DWFezQFj6Bex30=;
        h=From:To:Cc:Subject:Date:From;
        b=amwa4WWGtNqEMtFTjOayAnVMIGT2+0I8ryTpdaUUhYIGwxkBnRB3hQNLL/O0J2hrA
         Ov42nwGE4vasvA5nJfmNug6iqtaCKWSU/qS6PzumOb3Vzo5YfSXkGZDlcyzT5pPUeK
         s0r1NgHksnHH+J262ok0biKeJJvDQrYHt/MsamYE=
From: Arnd Bergmann <arnd@kernel.org>
To: Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        x86@kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>, Paolo Bonzini <pbonzini@redhat.com>,
        linux-hyperv@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-pm@vger.kernel.org, linux-edac@vger.kernel.org,
        kvm@vger.kernel.org, platform-driver-x86@vger.kernel.org,
        xen-devel@lists.xenproject.org, iommu@lists.linux-foundation.org
Subject: [PATCH] [v3] x86: apic: avoid -Wshadow warning in header
Date: Fri, 30 Oct 2020 15:06:36 +0100
Message-Id: <20201030140834.852488-1-arnd@kernel.org>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Arnd Bergmann <arnd@arndb.de>

There are hundreds of warnings in a W=2 build about a local
variable shadowing the global 'apic' definition:

arch/x86/kvm/lapic.h:149:65: warning: declaration of 'apic' shadows a global declaration [-Wshadow]

Avoid this by renaming the global 'apic' variable to the more descriptive
'x86_local_apic'. It was originally called 'genapic', but both that
and the current 'apic' seem to be a little overly generic for a global
variable.

Fixes: c48f14966cc4 ("KVM: inline kvm_apic_present() and kvm_lapic_enabled()")
Fixes: c8d46cf06dc2 ("x86: rename 'genapic' to 'apic'")
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
---
v3: rename the global from x86_system_apic to x86_local_apic

v2: rename the global instead of the local variable in the header

This is only tested in an allmodconfig build, after fixing up a
few mistakes in the original search&replace. It's likely that I
missed a few others, but this version should be sufficient to
decide whether this is a good idea in the first place, as well
as if there are better ideas for the new name.
---
 arch/x86/hyperv/hv_apic.c             |  2 ++
 arch/x86/hyperv/hv_spinlock.c         |  4 ++--
 arch/x86/include/asm/apic.h           | 18 +++++++++---------
 arch/x86/kernel/acpi/boot.c           |  2 +-
 arch/x86/kernel/apic/apic.c           | 18 +++++++++---------
 arch/x86/kernel/apic/apic_flat_64.c   |  8 ++++----
 arch/x86/kernel/apic/apic_numachip.c  |  4 ++--
 arch/x86/kernel/apic/bigsmp_32.c      |  2 +-
 arch/x86/kernel/apic/hw_nmi.c         |  2 +-
 arch/x86/kernel/apic/io_apic.c        | 19 ++++++++++---------
 arch/x86/kernel/apic/ipi.c            | 22 +++++++++++-----------
 arch/x86/kernel/apic/msi.c            |  2 +-
 arch/x86/kernel/apic/probe_32.c       | 20 ++++++++++----------
 arch/x86/kernel/apic/probe_64.c       | 12 ++++++------
 arch/x86/kernel/apic/vector.c         |  8 ++++----
 arch/x86/kernel/apic/x2apic_cluster.c |  3 ++-
 arch/x86/kernel/apic/x2apic_phys.c    |  2 +-
 arch/x86/kernel/apic/x2apic_uv_x.c    |  2 +-
 arch/x86/kernel/cpu/common.c          | 14 ++++++++------
 arch/x86/kernel/cpu/mce/inject.c      |  4 ++--
 arch/x86/kernel/cpu/topology.c        |  8 ++++----
 arch/x86/kernel/irq_work.c            |  2 +-
 arch/x86/kernel/kvm.c                 |  6 +++---
 arch/x86/kernel/nmi_selftest.c        |  2 +-
 arch/x86/kernel/smpboot.c             | 20 +++++++++++---------
 arch/x86/kernel/vsmp_64.c             |  2 +-
 arch/x86/kvm/vmx/vmx.c                |  2 +-
 arch/x86/mm/srat.c                    |  2 +-
 arch/x86/platform/uv/uv_irq.c         |  4 ++--
 arch/x86/platform/uv/uv_nmi.c         |  2 +-
 arch/x86/xen/apic.c                   |  8 ++++----
 drivers/iommu/amd/iommu.c             | 10 ++++++----
 drivers/iommu/intel/irq_remapping.c   |  4 ++--
 33 files changed, 125 insertions(+), 115 deletions(-)

```
#### [PATCH v4 01/17] irqchip: Add IMS (Interrupt Message Store) driverFrom: Dave Jiang <dave.jiang@intel.com>
##### From: Dave Jiang <dave.jiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dave Jiang <dave.jiang@intel.com>
X-Patchwork-Id: 11870583
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,UNWANTED_LANGUAGE_BODY,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DB8CEC55178
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 18:53:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 894F220797
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 18:53:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727562AbgJ3SxC (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 14:53:02 -0400
Received: from mga06.intel.com ([134.134.136.31]:65477 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727553AbgJ3SxA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 14:53:00 -0400
IronPort-SDR: 
 AXD8hg3gcAa468sDxByC0AX/0b3l+NaLWHHz6rZiXFYunomrDE8r7rs/EAY0nrz6HhYwoe/jL5
 p0rLDGDdDrbQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9790"; a="230287761"
X-IronPort-AV: E=Sophos;i="5.77,434,1596524400";
   d="scan'208";a="230287761"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Oct 2020 11:50:56 -0700
IronPort-SDR: 
 P/EszHGZMS3LYCtTJeIVgFGLl03yO2IZ+VGXlypcKQUAJNJmboelDzpeQyf2D7wTrVKdPF3TOC
 YCDdP23muVzw==
X-IronPort-AV: E=Sophos;i="5.77,434,1596524400";
   d="scan'208";a="527209865"
Received: from djiang5-desk3.ch.intel.com ([143.182.136.137])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 30 Oct 2020 11:50:55 -0700
Subject: [PATCH v4 01/17] irqchip: Add IMS (Interrupt Message Store) driver
From: Dave Jiang <dave.jiang@intel.com>
To: vkoul@kernel.org, megha.dey@intel.com, maz@kernel.org,
        bhelgaas@google.com, tglx@linutronix.de,
        alex.williamson@redhat.com, jacob.jun.pan@intel.com,
        ashok.raj@intel.com, jgg@mellanox.com, yi.l.liu@intel.com,
        baolu.lu@intel.com, kevin.tian@intel.com, sanjay.k.kumar@intel.com,
        tony.luck@intel.com, jing.lin@intel.com, dan.j.williams@intel.com,
        kwankhede@nvidia.com, eric.auger@redhat.com, parav@mellanox.com,
        jgg@mellanox.com, rafael@kernel.org, netanelg@mellanox.com,
        shahafs@mellanox.com, yan.y.zhao@linux.intel.com,
        pbonzini@redhat.com, samuel.ortiz@intel.com, mona.hossain@intel.com
Cc: dmaengine@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-pci@vger.kernel.org, kvm@vger.kernel.org
Date: Fri, 30 Oct 2020 11:50:54 -0700
Message-ID: 
 <160408385476.912050.16205225207591080075.stgit@djiang5-desk3.ch.intel.com>
In-Reply-To: 
 <160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com>
References: 
 <160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com>
User-Agent: StGit/0.23-29-ga622f1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

Generic IMS(Interrupt Message Store) irq chips and irq domain
implementations for IMS based devices which store the interrupt
messages in an array in device memory.

Allocation and freeing of interrupts happens via the generic
msi_domain_alloc/free_irqs() interface. No special purpose IMS magic
required as long as the interrupt domain is stored in the underlying
device struct.

Provide storage and a setter for an Address Space Identifier. The
identifier is stored in the top level irq_data and it only can be
modified when the interrupt is not active. Add the necessary storage
and helper functions and validate that interrupts which require an
ASID have one assigned.

[Megha : Fixed compile time errors
         Added necessary dependencies to IMS_MSI_ARRAY config
         Fixed polarity of IMS_VECTOR_CTRL
         Added reads after writes to flush writes to device
         Tested the IMS infrastructure with the IDXD driver]

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Megha Dey <megha.dey@intel.com>
Signed-off-by: Dave Jiang <dave.jiang@intel.com>
---
 drivers/irqchip/Kconfig             |   14 ++
 drivers/irqchip/Makefile            |    1 
 drivers/irqchip/irq-ims-msi.c       |  204 +++++++++++++++++++++++++++++++++++
 include/linux/interrupt.h           |    2 
 include/linux/irq.h                 |    4 +
 include/linux/irqchip/irq-ims-msi.h |   68 ++++++++++++
 kernel/irq/manage.c                 |   32 +++++
 7 files changed, 325 insertions(+)
 create mode 100644 drivers/irqchip/irq-ims-msi.c
 create mode 100644 include/linux/irqchip/irq-ims-msi.h

```
#### [PATCH] vfio/pci: Implement ioeventfd thread handler for contended memory lock
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11869997
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 375FFC4363A
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:02:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA8552076E
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:02:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PrGxf9Xt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727031AbgJ3PB7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 11:01:59 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:22093 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726880AbgJ3PB6 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 30 Oct 2020 11:01:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1604070117;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=HRlXzgPlOlTLzlZheP17qFCHXA+/zGO9eoSgNLbBfiQ=;
        b=PrGxf9XtP+6ElXABX5fH6t+gLlIISJrU5BIyrq1db0lbNhqvZ/47zSLt5wjrTlUE+R+oD4
        O8KQ6A2wsr3oOBxwAFBh1atzg8M9cAbdxQeuJAsyjeLjqg9//tE1jjLCv1ShhVzfyUpT4I
        vEHOWfWWJ4fsxTx8JQhmfenxKN4lOrM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-373-skMTrk0COkScOKr7YEaIdA-1; Fri, 30 Oct 2020 11:01:55 -0400
X-MC-Unique: skMTrk0COkScOKr7YEaIdA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E375787950C;
        Fri, 30 Oct 2020 15:01:53 +0000 (UTC)
Received: from gimli.home (ovpn-112-213.phx2.redhat.com [10.3.112.213])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8C6205B4AA;
        Fri, 30 Oct 2020 15:01:50 +0000 (UTC)
Subject: [PATCH] vfio/pci: Implement ioeventfd thread handler for contended
 memory lock
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Date: Fri, 30 Oct 2020 09:01:50 -0600
Message-ID: <160407008986.9986.83949368176304529.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ioeventfd is called under spinlock with interrupts disabled,
therefore if the memory lock is contended defer code that might
sleep to a thread context.

Fixes: bc93b9ae0151 ("vfio-pci: Avoid recursive read-lock usage")
Link: https://bugzilla.kernel.org/show_bug.cgi?id=209253#c1
Reported-by: Ian Pilcher <arequipeno@gmail.com>
Tested-by: Ian Pilcher <arequipeno@gmail.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_rdwr.c |   43 +++++++++++++++++++++++++++++++-------
 1 file changed, 35 insertions(+), 8 deletions(-)

```
#### [PATCH] vfio: platform: fix reference leak in vfio_platform_open
##### From: Zhang Qilong <zhangqilong3@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhang Qilong <zhangqilong3@huawei.com>
X-Patchwork-Id: 11870121
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1B2DAC00A89
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:37:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BE7732068E
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 15:37:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726992AbgJ3Phc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 11:37:32 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:7116 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726178AbgJ3Phc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 11:37:32 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4CN5zF0LPrzLmsJ;
        Fri, 30 Oct 2020 23:37:29 +0800 (CST)
Received: from huawei.com (10.90.53.225) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.487.0; Fri, 30 Oct 2020
 23:37:27 +0800
From: Zhang Qilong <zhangqilong3@huawei.com>
To: <eric.auger@redhat.com>, <alex.williamson@redhat.com>
CC: <cohuck@redhat.com>, <kvm@vger.kernel.org>
Subject: [PATCH] vfio: platform: fix reference leak in vfio_platform_open
Date: Fri, 30 Oct 2020 23:47:54 +0800
Message-ID: <20201030154754.99431-1-zhangqilong3@huawei.com>
X-Mailer: git-send-email 2.26.0.106.g9fadedd
MIME-Version: 1.0
X-Originating-IP: [10.90.53.225]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pm_runtime_get_sync() will increment pm usage counter even it
failed. Forgetting to call pm_runtime_put_noidle will result
in reference leak in vfio_platform_open, so we should fix it.

Signed-off-by: Zhang Qilong <zhangqilong3@huawei.com>
---
 drivers/vfio/platform/vfio_platform_common.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
