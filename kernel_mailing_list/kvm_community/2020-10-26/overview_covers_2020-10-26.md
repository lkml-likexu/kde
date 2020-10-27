

#### [PATCH 0/8] KVM: arm64: Host EL2 entry improvements
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Oct 26 09:51:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11856273
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B53D7C55178
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:09:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 64E7722400
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 10:09:23 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603706963;
	bh=/871FOVPW0E/2Dr2XjwHcJP0LUAoYcByZt/uNRRFF80=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=PhP85PFVmnZK1lXI5b+bePQFKRVZEzaE+/+LznMojTcH0jdIXrmWEBokSi1q2Qt5e
	 zHkqbGNHqXhE53BLakYabKjyfAry9+N4V03pMoIcqJG3WPpUubxbbVB0nDpfWug8R/
	 LDVSSIDEX3JWIOcP3WWCNHMynKLfDAJlOpl1K6+E=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1769092AbgJZKJW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:09:22 -0400
Received: from mail.kernel.org ([198.145.29.99]:44084 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1737064AbgJZJvc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 05:51:32 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 612A020704;
        Mon, 26 Oct 2020 09:51:31 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603705891;
        bh=/871FOVPW0E/2Dr2XjwHcJP0LUAoYcByZt/uNRRFF80=;
        h=From:To:Cc:Subject:Date:From;
        b=WD43U8rqPf0syvCAvMG/IcVDofcUUOS/TFk/pC+UizH/0Db318ZDt6vTVU2Rcgkv4
         RlXt5wfgwCzqZ/XR+pQ9VcsifQtS4beZLAqrCNp3Z0rYfOSU4iZlofTv3hbplAoCyg
         aEXqP4KK1OlZD/ToX3ZQIuATp44SZNTLU4S1npGQ=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kWzA1-004HZn-7b; Mon, 26 Oct 2020 09:51:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>, kernel-team@android.com
Subject: [PATCH 0/8] KVM: arm64: Host EL2 entry improvements
Date: Mon, 26 Oct 2020 09:51:08 +0000
Message-Id: <20201026095116.72051-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, qperret@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This small series reworks various bits of the host EL2 entry after
Andrew's extensive rework to move from direct function calls to a
SMCCC implementation.

The first 3 patches are plain bug fixes, and candidates for immediate
merge into 5.10.

The following 2 patches allow the use of direct function pointers at
EL2, something that we can't do at the moment (other than PC-relative
addressing). This requires a helper to translate pointers at runtime,
but the result is neat enough. This allows the rewrite of the host HVC
handling in a more maintainable way.

A similar patch removes the direct use of kimage_voffset, which we
won't be able to trust for much longer.

The last two patches are just cleanups and optimisations.

Patches on top of 5.10-rc1.

Marc Zyngier (8):
  KVM: arm64: Don't corrupt tpidr_el2 on failed HVC call
  KVM: arm64: Remove leftover kern_hyp_va() in nVHE TLB invalidation
  KVM: arm64: Drop useless PAN setting on host EL1 to EL2 transition
  KVM: arm64: Add kimg_hyp_va() helper
  KVM: arm64: Turn host HVC handling into a dispatch table
  KVM: arm64: Patch kimage_voffset instead of loading the EL1 value
  KVM: arm64: Simplify __kvm_enable_ssbs()
  KVM: arm64: Avoid repetitive stack access on host EL1 to EL2 exception

 arch/arm64/include/asm/kvm_asm.h    |   2 -
 arch/arm64/include/asm/kvm_mmu.h    |  16 ++
 arch/arm64/include/asm/sysreg.h     |   1 +
 arch/arm64/kernel/image-vars.h      |   5 +-
 arch/arm64/kvm/hyp/nvhe/host.S      |  14 +-
 arch/arm64/kvm/hyp/nvhe/hyp-init.S  |  23 ++-
 arch/arm64/kvm/hyp/nvhe/hyp-main.c  | 231 +++++++++++++++++-----------
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c |  11 --
 arch/arm64/kvm/hyp/nvhe/tlb.c       |   1 -
 arch/arm64/kvm/va_layout.c          |  56 +++++++
 10 files changed, 236 insertions(+), 124 deletions(-)
```
#### [PATCH v4 00/15] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Mon Oct 26 10:58:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11856613
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.9 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2FEBCC56202
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 11:01:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9A8D22404
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 11:01:06 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="UWVGBGjy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1772355AbgJZK62 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 06:58:28 -0400
Received: from mail-wm1-f65.google.com ([209.85.128.65]:34995 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1771906AbgJZK61 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 06:58:27 -0400
Received: by mail-wm1-f65.google.com with SMTP id h22so878680wmb.0
        for <kvm@vger.kernel.org>; Mon, 26 Oct 2020 03:58:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FLkPK/wakWgPcP2XtBGkyHk3/K5f5jOPCyDZpBtuyVA=;
        b=UWVGBGjyj6MIRYbUDiITJq5L6QqEg6/q2/NHckpyd8RPSBh26b0bPaluvTWItOuYKc
         uaoPMBpxALWoXXsF90NCYVWJoITCFikSp8O7FpqdOPDdJXFgIlHFG/TgfvpItfUwxafp
         6wW5he4gsgXTW7dkqWJgYLc8PHDC8/A2/zOmc=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=FLkPK/wakWgPcP2XtBGkyHk3/K5f5jOPCyDZpBtuyVA=;
        b=V9ixA2N5dQSvmw+9wgCEYE0gOIxtkWOekOmHRKvE9+kHzpBeCllQJMdaYKJMMvzuX4
         U1WluKG/Q3Sm9FByAQkATRY5P0fhNt4FP4ePc7oWX0gElkshPVGLQznbc5X0bn/3FthV
         lItmk8CalLF3HAUhtu0PH5DPNrnQaXj0YiK2qctpTNiIQx9/56WTP04TKou9hZaWZR08
         /W8BXHR9X2kmCe9+RxpweiPtcC/Tn9M7+JMxfHtagorOyBLQtk/2IuFc25jylWcj7E6R
         euniknmj/yrwS/A1Gi71Nf7nn3QJC5O6yf6C6C/KNnocAcNQkABr2KxoYJOP6Nyc1tb2
         MaGQ==
X-Gm-Message-State: AOAM532cOWSOH5LTNq2FGy93WuCR1UM4eQkwQqV2xgyA8j1TOz2x3165
        D3tFfGpSK9qD9X2ZOBAe4VwuPWHpWb4q1yS2
X-Google-Smtp-Source: 
 ABdhPJxesVax0WQRMCyO4OuQvYno6G/x4zHb3UoXArN6uKT0KIo/6VWoGjLr6p0ejXLAy+E8fDIECg==
X-Received: by 2002:a1c:3243:: with SMTP id
 y64mr15267147wmy.175.1603709905111;
        Mon, 26 Oct 2020 03:58:25 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 w83sm21165156wmg.48.2020.10.26.03.58.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 26 Oct 2020 03:58:24 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        linux-s390@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v4 00/15] follow_pfn and other iomap races
Date: Mon, 26 Oct 2020 11:58:03 +0100
Message-Id: <20201026105818.2585306-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all

Round 3 of my patch series to clamp down a bunch of races and gaps
around follow_pfn and other access to iomem mmaps. Previous version:

v1: https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/
v2: https://lore.kernel.org/dri-devel/20201009075934.3509076-1-daniel.vetter@ffwll.ch
v3: https://lore.kernel.org/dri-devel/20201021085655.1192025-1-daniel.vetter@ffwll.ch/

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

Changes in v4:
- Drop the s390 patch, that was very stand-alone and now queued up to land
  through s390 trees.
- Comment polish per Dan's review.

Changes in v3:
- Bunch of polish all over, no functional changes aside from one barrier
  in the resource code, for consistency.
- A few more r-b tags.

Changes in v2:
- tons of small polish&fixes all over, thanks to all the reviewers who
  spotted issues
- I managed to test at least the generic_access_phys and pci mmap revoke
  stuff with a few gdb sessions using our i915 debug tools (hence now also
  the drm/i915 patch to properly request all the pci bar regions)
- reworked approach for the pci mmap revoke: Infrastructure moved into
  kernel/resource.c, address_space mapping is now set up at open time for
  everyone (which required some sysfs changes). Does indeed look a lot
  cleaner and a lot less invasive than I feared at first.

I feel like this is ready for some wider soaking. Since the remaining bits
are all kinda connnected probably simplest if it all goes through -mm.

Cheers, Daniel

Daniel Vetter (15):
  drm/exynos: Stop using frame_vector helpers
  drm/exynos: Use FOLL_LONGTERM for g2d cmdlists
  misc/habana: Stop using frame_vector helpers
  misc/habana: Use FOLL_LONGTERM for userptr
  mm/frame-vector: Use FOLL_LONGTERM
  media: videobuf2: Move frame_vector into media subsystem
  mm: Close race in generic_access_phys
  mm: Add unsafe_follow_pfn
  media/videbuf1|2: Mark follow_pfn usage as unsafe
  vfio/type1: Mark follow_pfn as unsafe
  PCI: Obey iomem restrictions for procfs mmap
  /dev/mem: Only set filp->f_mapping
  resource: Move devmem revoke code to resource framework
  sysfs: Support zapping of binary attr mmaps
  PCI: Revoke mappings like devmem

 drivers/char/mem.c                            |  86 +--------------
 drivers/gpu/drm/exynos/Kconfig                |   1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c       |  48 ++++-----
 drivers/media/common/videobuf2/Kconfig        |   1 -
 drivers/media/common/videobuf2/Makefile       |   1 +
 .../media/common/videobuf2}/frame_vector.c    |  54 ++++------
 drivers/media/platform/omap/Kconfig           |   1 -
 drivers/media/v4l2-core/videobuf-dma-contig.c |   2 +-
 drivers/misc/habanalabs/Kconfig               |   1 -
 drivers/misc/habanalabs/common/habanalabs.h   |   6 +-
 drivers/misc/habanalabs/common/memory.c       |  50 ++++-----
 drivers/pci/pci-sysfs.c                       |   4 +
 drivers/pci/proc.c                            |   6 ++
 drivers/vfio/vfio_iommu_type1.c               |   4 +-
 fs/sysfs/file.c                               |  11 ++
 include/linux/ioport.h                        |   6 +-
 include/linux/mm.h                            |  47 +-------
 include/linux/sysfs.h                         |   2 +
 include/media/frame_vector.h                  |  47 ++++++++
 include/media/videobuf2-core.h                |   1 +
 kernel/resource.c                             | 101 +++++++++++++++++-
 mm/Kconfig                                    |   3 -
 mm/Makefile                                   |   1 -
 mm/memory.c                                   |  78 +++++++++++++-
 mm/nommu.c                                    |  17 +++
 security/Kconfig                              |  13 +++
 26 files changed, 347 insertions(+), 245 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (85%)
 create mode 100644 include/media/frame_vector.h
```
#### [PATCH 00/11] KVM: arm64: Move PC/ELR/SPSR/PSTATE updatess to EL2
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Oct 26 13:34:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11857159
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DE9CAC4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 13:35:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 919612465B
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 13:35:05 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1603719305;
	bh=/7647TEuJSHw4E0GvVdhCJh7X525DLpULuJ4YUPi0HA=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=XzxeUPrjYtbltvdLykEWWwUQ6CjSfLpeIKKWIqoThb2DDOOausPG39qTPFMMNeY4g
	 mLb54o/4AGdqYvvmZKJjltQOzWvjKxGVLhB6JJr6YkvtuA+WjvuE8kaJ6uh8KziGtr
	 oBOTSKYKUHLFLhpup45hE1TDHfhzzwO+ZmHKWb40=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1769829AbgJZNfE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 09:35:04 -0400
Received: from mail.kernel.org ([198.145.29.99]:37642 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1769388AbgJZNfD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Oct 2020 09:35:03 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id D07C022284;
        Mon, 26 Oct 2020 13:35:01 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1603719302;
        bh=/7647TEuJSHw4E0GvVdhCJh7X525DLpULuJ4YUPi0HA=;
        h=From:To:Cc:Subject:Date:From;
        b=P2JyzTfwMKv3olGS4DmfWIGe7kgr9IT+Qx8REIzDOqD3kshQn02RYYPtNwEOKijPs
         K2Ef+WDySF7y/YaNNapyu4bbg8zXFbhnSWPloNGBQXG4rFqUVxPWwDzn4bHRiBRLWG
         mD5lZCio6b9mgniKGuDUBbH6hgpfq0Kj/wjfHn68=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1kX2eJ-004Kjh-Nx; Mon, 26 Oct 2020 13:34:59 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Scull <ascull@google.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>,
        David Brazdil <dbrazdil@google.com>, kernel-team@android.com
Subject: [PATCH 00/11] KVM: arm64: Move PC/ELR/SPSR/PSTATE updatess to EL2
Date: Mon, 26 Oct 2020 13:34:39 +0000
Message-Id: <20201026133450.73304-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, ascull@google.com,
 will@kernel.org, qperret@google.com, dbrazdil@google.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we progress towards being able to keep the guest state private to
the nVHE hypervisor, this series aims at moving anything that touches
the registers involved into an exception to EL2.

The general idea is that any update to these registers is driven by a
set of flags passed from EL1 to EL2, and EL2 will deal with the
register update itself, removing the need for EL1 to see the guest
state. It also results in a bunch of cleanup, mostly in the 32bit
department (negative diffstat, yay!).

Of course, none of that has any real effect on security yet. It is
only once we start having a private VCPU structure at EL2 that we can
enforce the isolation. Similarly, there is no policy enforcement, and
a malicious EL1 can still inject exceptions at random points. It can
also give bogus ESR values to the guest. Baby steps.

        M.

Marc Zyngier (11):
  KVM: arm64: Don't adjust PC on SError during SMC trap
  KVM: arm64: Move kvm_vcpu_trap_il_is32bit into kvm_skip_instr32()
  KVM: arm64: Make kvm_skip_instr() and co private to HYP
  KVM: arm64: Move PC rollback on SError to HYP
  KVM: arm64: Move VHE direct sysreg accessors into kvm_host.h
  KVM: arm64: Add basic hooks for injecting exceptions from EL2
  KVM: arm64: Inject AArch64 exceptions from HYP
  KVM: arm64: Inject AArch32 exceptions from HYP
  KVM: arm64: Remove SPSR manipulation primitives
  KVM: arm64: Consolidate exception injection
  KVM: arm64: Get rid of the AArch32 register mapping code

 arch/arm64/include/asm/kvm_emulate.h       |  70 +---
 arch/arm64/include/asm/kvm_host.h          | 115 ++++++-
 arch/arm64/kvm/Makefile                    |   4 +-
 arch/arm64/kvm/aarch32.c                   | 232 -------------
 arch/arm64/kvm/guest.c                     |  28 +-
 arch/arm64/kvm/handle_exit.c               |  23 +-
 arch/arm64/kvm/hyp/aarch32.c               |   4 +-
 arch/arm64/kvm/hyp/exception.c             | 368 +++++++++++++++++++++
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h |  62 ++++
 arch/arm64/kvm/hyp/include/hyp/switch.h    |  17 +
 arch/arm64/kvm/hyp/nvhe/Makefile           |   2 +-
 arch/arm64/kvm/hyp/nvhe/switch.c           |   3 +
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c   |   2 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c            |   2 +
 arch/arm64/kvm/hyp/vhe/Makefile            |   2 +-
 arch/arm64/kvm/hyp/vhe/switch.c            |   3 +
 arch/arm64/kvm/inject_fault.c              | 187 +++++------
 arch/arm64/kvm/mmio.c                      |   2 +-
 arch/arm64/kvm/mmu.c                       |   2 +-
 arch/arm64/kvm/regmap.c                    | 224 -------------
 arch/arm64/kvm/sys_regs.c                  |  83 +----
 21 files changed, 698 insertions(+), 737 deletions(-)
 delete mode 100644 arch/arm64/kvm/aarch32.c
 create mode 100644 arch/arm64/kvm/hyp/exception.c
 create mode 100644 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h
 delete mode 100644 arch/arm64/kvm/regmap.c
```
#### [PATCH 00/13] s390x/pci: s390-pci updates for kernel 5.10-rc1 
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Mon Oct 26 15:34:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11857571
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50D3CC4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 15:35:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0446322400
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 15:35:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="jEVzicKB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1783965AbgJZPfB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 11:35:01 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32562 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1783962AbgJZPfA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 11:35:00 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 09QFXfOS159479;
        Mon, 26 Oct 2020 11:34:51 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=pp1;
 bh=MPOOUrolEsOl3/XJNifqjJs1FTGO61oGzLzV+vkgnVI=;
 b=jEVzicKB4L2L0OhVktpVEPPBzejl/E0w/dpo6OsWI+ICw4C7cewr6CXhFR3xycyKdZxS
 P83ufex40y4L6vrZJMdZkZcO/xonWYOh51ad2M1zQtrn4Ijm8BmQuzvMOQZkKImmACP/
 wJWzVLEZfhGck17yLRvxYLj3iHf9Yqk3o6Hw0k6//NocMfseJdw2CyGdRlMyvQMqnsGb
 qvoTstGZKPeoeciV9tuO4dR8GzngX6sSjCfdG10Tcd+gLGqM/GKkQeCZy1US8EPI6dFM
 Le7CmsYDJcxVh37IF1XcgdS6zMMC8IaBtzFbIfWuuL/TeVD73WpvOrOgcwWgw03zgWHn 7w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34duwd2bw6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 11:34:51 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 09QFXqBu159980;
        Mon, 26 Oct 2020 11:34:51 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0b-001b2d01.pphosted.com with ESMTP id 34duwd2bvt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 11:34:51 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 09QFIEjA028487;
        Mon, 26 Oct 2020 15:34:50 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma04dal.us.ibm.com with ESMTP id 34cbw8vrn3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 26 Oct 2020 15:34:50 +0000
Received: from b01ledav004.gho.pok.ibm.com (b01ledav004.gho.pok.ibm.com
 [9.57.199.109])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 09QFYn8L1704660
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 26 Oct 2020 15:34:49 GMT
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 92638112063;
        Mon, 26 Oct 2020 15:34:49 +0000 (GMT)
Received: from b01ledav004.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7A5F7112061;
        Mon, 26 Oct 2020 15:34:45 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.49.29])
        by b01ledav004.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 26 Oct 2020 15:34:45 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        philmd@redhat.com, qemu-s390x@nongnu.org, qemu-devel@nongnu.org,
        kvm@vger.kernel.org
Subject: [PATCH 00/13] s390x/pci: s390-pci updates for kernel 5.10-rc1 
Date: Mon, 26 Oct 2020 11:34:28 -0400
Message-Id: <1603726481-31824-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.737
 definitions=2020-10-26_08:2020-10-26,2020-10-26 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501 mlxscore=0
 mlxlogscore=831 bulkscore=0 impostorscore=0 lowpriorityscore=0
 malwarescore=0 spamscore=0 phishscore=0 adultscore=0 suspectscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010260107
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Combined set of patches that exploit vfio/s390-pci features available in
kernel 5.10-rc1.  This patch set is a combination of 

[PATCH v4 0/5] s390x/pci: Accomodate vfio DMA limiting

and

[PATCH v3 00/10] Retrieve zPCI hardware information from VFIO

with duplicate patches removed and a single header sync.  All patches have
prior maintainer reviews except for:

- Patch 1 (update-linux-headers change to add new file) 
- Patch 2 (header sync against 5.10-rc1)
- Patch 13 - contains a functional (debug) change; I switched from using
  DPRINTFs to using trace events per Connie's request.



Matthew Rosato (10):
  update-linux-headers: Add vfio_zdev.h
  linux-headers: update against 5.10-rc1
  s390x/pci: Move header files to include/hw/s390x
  vfio: Create shared routine for scanning info capabilities
  vfio: Find DMA available capability
  s390x/pci: Add routine to get the vfio dma available count
  s390x/pci: Honor DMA limits set by vfio
  s390x/pci: clean up s390 PCI groups
  vfio: Add routine for finding VFIO_DEVICE_GET_INFO capabilities
  s390x/pci: get zPCI function info from host

Pierre Morel (3):
  s390x/pci: create a header dedicated to PCI CLP
  s390x/pci: use a PCI Group structure
  s390x/pci: use a PCI Function structure

 MAINTAINERS                                        |   1 +
 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  91 ++++++-
 hw/s390x/s390-pci-inst.c                           |  78 ++++--
 hw/s390x/s390-pci-vfio.c                           | 276 +++++++++++++++++++++
 hw/s390x/s390-virtio-ccw.c                         |   2 +-
 hw/s390x/trace-events                              |   6 +
 hw/vfio/common.c                                   |  62 ++++-
 {hw => include/hw}/s390x/s390-pci-bus.h            |  22 ++
 .../hw/s390x/s390-pci-clp.h                        | 123 +--------
 include/hw/s390x/s390-pci-inst.h                   | 119 +++++++++
 include/hw/s390x/s390-pci-vfio.h                   |  23 ++
 include/hw/vfio/vfio-common.h                      |   4 +
 .../drivers/infiniband/hw/vmw_pvrdma/pvrdma_ring.h |  14 +-
 .../infiniband/hw/vmw_pvrdma/pvrdma_verbs.h        |   2 +-
 include/standard-headers/linux/ethtool.h           |   2 +
 include/standard-headers/linux/fuse.h              |  50 +++-
 include/standard-headers/linux/input-event-codes.h |   4 +
 include/standard-headers/linux/pci_regs.h          |   6 +-
 include/standard-headers/linux/virtio_fs.h         |   3 +
 include/standard-headers/linux/virtio_gpu.h        |  19 ++
 include/standard-headers/linux/virtio_mmio.h       |  11 +
 include/standard-headers/linux/virtio_pci.h        |  11 +-
 linux-headers/asm-arm64/kvm.h                      |  25 ++
 linux-headers/asm-arm64/mman.h                     |   1 +
 linux-headers/asm-generic/hugetlb_encode.h         |   1 +
 linux-headers/asm-generic/unistd.h                 |  18 +-
 linux-headers/asm-mips/unistd_n32.h                |   1 +
 linux-headers/asm-mips/unistd_n64.h                |   1 +
 linux-headers/asm-mips/unistd_o32.h                |   1 +
 linux-headers/asm-powerpc/unistd_32.h              |   1 +
 linux-headers/asm-powerpc/unistd_64.h              |   1 +
 linux-headers/asm-s390/unistd_32.h                 |   1 +
 linux-headers/asm-s390/unistd_64.h                 |   1 +
 linux-headers/asm-x86/kvm.h                        |  20 ++
 linux-headers/asm-x86/unistd_32.h                  |   1 +
 linux-headers/asm-x86/unistd_64.h                  |   1 +
 linux-headers/asm-x86/unistd_x32.h                 |   1 +
 linux-headers/linux/kvm.h                          |  19 ++
 linux-headers/linux/mman.h                         |   1 +
 linux-headers/linux/vfio.h                         |  29 ++-
 linux-headers/linux/vfio_zdev.h                    |  78 ++++++
 scripts/update-linux-headers.sh                    |   2 +-
 43 files changed, 961 insertions(+), 173 deletions(-)
 create mode 100644 hw/s390x/s390-pci-vfio.c
 rename {hw => include/hw}/s390x/s390-pci-bus.h (94%)
 rename hw/s390x/s390-pci-inst.h => include/hw/s390x/s390-pci-clp.h (59%)
 create mode 100644 include/hw/s390x/s390-pci-inst.h
 create mode 100644 include/hw/s390x/s390-pci-vfio.h
 create mode 100644 linux-headers/linux/vfio_zdev.h
```
#### [PATCH v4 0/2] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Mon Oct 26 16:30:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11857785
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED autolearn=no
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 103B7C4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:30:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BD37D22284
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 16:30:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="gt+1Dd75"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1785958AbgJZQaV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 12:30:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:20679 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1776214AbgJZQaV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 12:30:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603729820;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/qVZfErBgM2F849WNZFnK/2eCYeC9hSvuEZ0ZfgFC2c=;
        b=gt+1Dd75zzfreQONIH9b2rG9k/L99CIijGswrNXdQ+cD7XiHkpsGOa3xbvipoQdUcLB4Kx
        4JjTgP+BgVzmC9M6h/2SdXim+UESjQEHXeWwg57bjrjLdLhGy6CUPWKu1t1gIaKI7n2NUE
        ICj0sPRTW6DodoGgg4bOM9HPVoEcyRM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-398-FPXA-Ii3NUahKeN95qi7FQ-1; Mon, 26 Oct 2020 12:30:18 -0400
X-MC-Unique: FPXA-Ii3NUahKeN95qi7FQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA7871084D64;
        Mon, 26 Oct 2020 16:30:16 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.8])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 861CF5B4AC;
        Mon, 26 Oct 2020 16:30:14 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Jon Doron <arilou@gmail.com>, linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/2] KVM: x86: hyper-v: make KVM_GET_SUPPORTED_HV_CPUID
 more useful
Date: Mon, 26 Oct 2020 17:30:11 +0100
Message-Id: <20201026163013.3164236-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v3:
- Rebase to the latest kvm/queue (KVM_CAP_SYS_HYPERV_CPUID changed to 191)

QEMU series using the feature:
https://lists.gnu.org/archive/html/qemu-devel/2020-09/msg02017.html

Original description:

KVM_GET_SUPPORTED_HV_CPUID was initially implemented as a vCPU ioctl but
this is not very useful when VMM is just trying to query which Hyper-V
features are supported by the host prior to creating VM/vCPUs. The data
in KVM_GET_SUPPORTED_HV_CPUID is mostly static with a few exceptions but
it seems we can change this. Add support for KVM_GET_SUPPORTED_HV_CPUID as
a system ioctl as well.

QEMU specific description:
In some cases QEMU needs to collect the information about which Hyper-V
features are supported by KVM and pass it up the stack. For non-hyper-v
features this is done with system-wide KVM_GET_SUPPORTED_CPUID/
KVM_GET_MSRS ioctls but Hyper-V specific features don't get in the output
(as Hyper-V CPUIDs intersect with KVM's). In QEMU, CPU feature expansion
happens before any KVM vcpus are created so KVM_GET_SUPPORTED_HV_CPUID
can't be used in its current shape.

Vitaly Kuznetsov (2):
  KVM: x86: hyper-v: allow KVM_GET_SUPPORTED_HV_CPUID as a system ioctl
  KVM: selftests: test KVM_GET_SUPPORTED_HV_CPUID as a system ioctl

 Documentation/virt/kvm/api.rst                | 16 ++--
 arch/x86/kvm/hyperv.c                         |  6 +-
 arch/x86/kvm/hyperv.h                         |  4 +-
 arch/x86/kvm/vmx/evmcs.c                      |  3 +-
 arch/x86/kvm/x86.c                            | 45 ++++++----
 include/uapi/linux/kvm.h                      |  3 +-
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 26 ++++++
 .../selftests/kvm/x86_64/hyperv_cpuid.c       | 87 +++++++++++--------
 9 files changed, 123 insertions(+), 69 deletions(-)
```
#### [PATCH v3 0/2] KVM: SVM: Create separate vmcbs for L1 and L2
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Mon Oct 26 17:42:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11857963
Return-Path: <SRS0=RIF0=EB=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3171FC4363A
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:42:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6753207C4
	for <kvm@archiver.kernel.org>; Mon, 26 Oct 2020 17:42:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="EKMRuDH8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1788140AbgJZRm3 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 26 Oct 2020 13:42:29 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:54566 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1422241AbgJZRm3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 26 Oct 2020 13:42:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603734148;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=Hr1VQIx12LkmscyRlZRpOxFqnwDRH9JcTtWbe8gtWCs=;
        b=EKMRuDH8l7t1Ok2qqkAhp3gGSiRkA5DS1+6bYyYc19RvppVcWmfMJeg7YyeYHSG+Q8c3M/
        wqvDtwfi4m0dKUAL7CkTjs++uwcxNFzSIJ6K+u+pweGYk7avmtMrcXz82MpTJMmH+dJ6YW
        DT0LhYawz4VVAsMIVrOdz28E2QDbwqQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-412-qjATM9bqNNS3voDuo7s8og-1; Mon, 26 Oct 2020 13:42:24 -0400
X-MC-Unique: qjATM9bqNNS3voDuo7s8og-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8879C56C89;
        Mon, 26 Oct 2020 17:42:23 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D84675577D;
        Mon, 26 Oct 2020 17:42:22 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com, mlevitsk@redhat.com,
        sean.j.christopherson@intel.com
Subject: [PATCH v3 0/2] KVM: SVM: Create separate vmcbs for L1 and L2
Date: Mon, 26 Oct 2020 13:42:20 -0400
Message-Id: <20201026174222.21811-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

svm->vmcb will now point to either a separate vmcb L1 ( not nested ) or L2 vmcb ( nested ).

Changes:
v2 -> v3
 - Added vmcb switching helper.
 - svm_set_nested_state always forces to L1 before determining state
   to set. This is more like vmx and covers any potential L2 to L2 nested state switch.
 - Moved svm->asid tracking to pre_svm_run and added ASID set dirty bit
   checking.

v1 -> v2
 - Removed unnecessary update check of L1 save.cr3 during nested_svm_vmexit.
 - Moved vmcb01_pa to svm.
 - Removed get_host_vmcb() function.
 - Updated vmsave/vmload corresponding vmcb state during L2
   enter and exit which fixed the L2 load issue.
 - Moved asid workaround to a new patch which adds asid to svm.
 - Init previously uninitialized L2 vmcb save.gpat and save.cr4

Tested:
kvm-unit-tests
kvm self tests
Loaded fedora nested guest on fedora

Cathy Avery (2):
  KVM: SVM: Track asid from vcpu_svm
  KVM: SVM: Use a separate vmcb for the nested L2 guest

 arch/x86/kvm/svm/nested.c | 125 ++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.c    |  58 +++++++++++-------
 arch/x86/kvm/svm/svm.h    |  51 +++++-----------
 3 files changed, 110 insertions(+), 124 deletions(-)
```
