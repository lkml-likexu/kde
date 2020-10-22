

#### [PATCH v3 00/16] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Wed Oct 21 08:56:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11848729
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EB3CDC4363A
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:57:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4059522249
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 08:57:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="VVnDgmxW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2441157AbgJUI5E (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 04:57:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41362 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2436472AbgJUI5D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 04:57:03 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 10B04C0613CF
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:03 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id c194so734058wme.2
        for <kvm@vger.kernel.org>; Wed, 21 Oct 2020 01:57:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Gont0CCKnHMdGa6wrKlYRfieb2OHeQGvhAdNIYmokXs=;
        b=VVnDgmxWGYk+ZwdNbZx6Qfo0t6kaRkEL0VNWUHATbLIt3jMjgaYOfdtnMpPlXBmHJZ
         gFnQDrMYEk/gKZHAwJOELTKxwsgwZW/CWn+u6zaKjIMCN9lm18HqsVeG9jRC0MGVpVvf
         8q8WCf23NrfOC9Q0xk18B4qoZ/OnP3rTMfyrA=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=Gont0CCKnHMdGa6wrKlYRfieb2OHeQGvhAdNIYmokXs=;
        b=cKKx0r53diIiS+MjTUlDwVcgXy+FXcvtKeuaVP56pUnKtU0j/wsVBUcpJY7IDIlTMw
         P6dmB4OqqKfNGR6fCFsg8iMWAafbwfDaGKnHWKaN401yQLj9egUwSep3XKT+SIdTbdqX
         vQFoLyVO/M5j0CALMJ0mQ86LV5i7QFTUCbkvrvqgnXoC0lV8U2QwtXk4ZC4f0IzLIwJG
         t9iIYn8hXBylflANWXOB5sQSWWYFopvFozxM+WcJKJEA8I8yRoPXfES4En/DIuXrRd8f
         U1Lbw8Nn2LJOC+TqYr5tWtt/P1lZdHGc3DDkCwiJMLSs++KTBminRDFrlUPDLR0sVm7X
         pbzQ==
X-Gm-Message-State: AOAM530gfiQN39xfBXGmSNjECatG3YEEJ0KmTGOdtQZuxJclVyGu82gC
        xwwkpA04HLV6w7IGH9jtYQweTA==
X-Google-Smtp-Source: 
 ABdhPJyYzWpMyeyH5q5wodO7eI820GbpOZirLgvPnOfJ1Y9pegsPCbV57mxWuzvlDgRCukgCBprgLQ==
X-Received: by 2002:a1c:dc8b:: with SMTP id
 t133mr2490486wmg.151.1603270621770;
        Wed, 21 Oct 2020 01:57:01 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 q8sm2675939wro.32.2020.10.21.01.57.00
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 21 Oct 2020 01:57:00 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        linux-s390@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v3 00/16] follow_pfn and other iomap races
Date: Wed, 21 Oct 2020 10:56:39 +0200
Message-Id: <20201021085655.1192025-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Round 3 of my patch series to clamp down a bunch of races and gaps
around follow_pfn and other access to iomem mmaps. Previous version:

v1: https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/
v2: https://lore.kernel.org/dri-devel/20201009075934.3509076-1-daniel.vetter@ffwll.ch

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

I was waiting for the testing result for habanalabs from Oded, but I guess
Oded was waiting for my v3.

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

The big thing I can't test are all the frame_vector changes in habanalbas,
exynos and media. Gerald has given the s390 patch a spin already.

Review, testing, feedback all very much welcome.

Cheers, Daniel
Daniel Vetter (16):
  drm/exynos: Stop using frame_vector helpers
  drm/exynos: Use FOLL_LONGTERM for g2d cmdlists
  misc/habana: Stop using frame_vector helpers
  misc/habana: Use FOLL_LONGTERM for userptr
  mm/frame-vector: Use FOLL_LONGTERM
  media: videobuf2: Move frame_vector into media subsystem
  mm: Close race in generic_access_phys
  s390/pci: Remove races against pte updates
  mm: Add unsafe_follow_pfn
  media/videbuf1|2: Mark follow_pfn usage as unsafe
  vfio/type1: Mark follow_pfn as unsafe
  PCI: Obey iomem restrictions for procfs mmap
  /dev/mem: Only set filp->f_mapping
  resource: Move devmem revoke code to resource framework
  sysfs: Support zapping of binary attr mmaps
  PCI: Revoke mappings like devmem

 arch/s390/pci/pci_mmio.c                      |  98 ++++++++++-------
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
 mm/memory.c                                   |  76 ++++++++++++-
 mm/nommu.c                                    |  17 +++
 security/Kconfig                              |  13 +++
 27 files changed, 403 insertions(+), 285 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (85%)
 create mode 100644 include/media/frame_vector.h
```
#### [PATCH v2 0/7] Split kvm_update_cpuid_runtime()
##### From: Robert Hoo <robert.hu@linux.intel.com>

```c
From patchwork Wed Oct 21 09:10:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Robert Hoo <robert.hu@linux.intel.com>
X-Patchwork-Id: 11848827
Return-Path: <SRS0=abDU=D4=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D8B56C4363A
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 09:10:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5EE0C21D6C
	for <kvm@archiver.kernel.org>; Wed, 21 Oct 2020 09:10:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390638AbgJUJKa (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 21 Oct 2020 05:10:30 -0400
Received: from mga07.intel.com ([134.134.136.100]:58972 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388839AbgJUJKa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 21 Oct 2020 05:10:30 -0400
IronPort-SDR: 
 aNvq4QnAN9zZo+KD8WvxulS+QzC3xjqREVTJfRM1v5PLdU4m4qu53/Bv/HGTd+incCLTER+wis
 RG9ijp4KSHqw==
X-IronPort-AV: E=McAfee;i="6000,8403,9780"; a="231530444"
X-IronPort-AV: E=Sophos;i="5.77,400,1596524400";
   d="scan'208";a="231530444"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 21 Oct 2020 02:10:27 -0700
IronPort-SDR: 
 PjtenZENvMSlNmZeRxBq/+kTsWE6pwO0C4rNTqwsnS5RuKGFRONI+f/WCd7+sYiArbjLLgl+91
 Uv34oyVPiOFg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,400,1596524400";
   d="scan'208";a="522682406"
Received: from sqa-gate.sh.intel.com (HELO robert-ivt.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 21 Oct 2020 02:10:23 -0700
From: Robert Hoo <robert.hu@linux.intel.com>
To: sean.j.christopherson@intel.com, pbonzini@redhat.com,
        xiaoyao.li@intel.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org
Cc: kvm@vger.kernel.org, robert.hu@intel.com,
        Robert Hoo <robert.hu@linux.intel.com>
Subject: [PATCH v2 0/7] Split kvm_update_cpuid_runtime()
Date: Wed, 21 Oct 2020 17:10:03 +0800
Message-Id: <1603271410-71343-1-git-send-email-robert.hu@linux.intel.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

kvm_update_cpuid_runtime() is currently called by various functions for the
purpose of updating vCPU's cpuid entries, due to specific runtime changes, e.g.
CR4 bits changes, XCR0 bits changes, etc. Each of them actually just needs to
update 1 ~ 2 CPUID entries. But current kvm_update_cpuid_runtime() packages all.
Given finding a target CPUID entry need to go through all CPUID entries, calling
kvm_update_cpuid_runtime() is a waste for each cause.

This patch set splits kvm_update_cpuid_runtime() into pieces according to
different updating causes.
Then let various callers call their specific necessary kvm_xxx_update_cpuid().
This patch set also refactors kvm_vcpu_after_set_cpuid().

This not only significantly saves each caller's time, but also eliminates
unnecessary couplings.
---
Change Log
v2:
Reorders patch set, let each extracted function with its caller in a patch.
Also, added a helper function guest_cpuid_change(), which is the extraction
of the common code.

Robert Hoo (7):
  kvm: x86: Extract kvm_apic_base_update_cpuid() from
    kvm_update_cpuid_runtime()
  kvm: x86: Extract kvm_xcr0_update_cpuid() from
    kvm_update_cpuid_runtime()
  kvm: x86: Extract kvm_osxsave_update_cpuid() and    
    kvm_pke_update_cpuid() from kvm_update_cpuid_runtime()
  kvm: x86: Extract kvm_mwait_update_cpuid() from
    kvm_update_cpuid_runtime()
  [Trivial] kvm: x86: cpuid_query_maxphyaddr(): Use a simple 'e' instead
    of     misleading 'best', as the variable name
  kvm: x86: Refactor kvm_vcpu_after_set_cpuid()
  kvm: x86: Remove kvm_update_cpuid_runtime()

 arch/x86/kvm/cpuid.c | 148 ++++++++++++++++++++++++++++++---------------------
 arch/x86/kvm/cpuid.h |   7 ++-
 arch/x86/kvm/lapic.c |   2 +-
 arch/x86/kvm/x86.c   |  29 ++++++----
 4 files changed, 113 insertions(+), 73 deletions(-)
```
