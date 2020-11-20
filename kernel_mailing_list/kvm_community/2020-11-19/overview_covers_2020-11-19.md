

#### [RFC PATCH 0/2] Add KVM support for bus lock debug exception
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Thu Nov 19 09:29:55 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11916897
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D65D6C388F9
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 09:27:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7B812246A5
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 09:27:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726182AbgKSJ13 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 04:27:29 -0500
Received: from mga04.intel.com ([192.55.52.120]:20996 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725873AbgKSJ13 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 04:27:29 -0500
IronPort-SDR: 
 G0I8YsGUo222k3OLr892GzGLMnKkahldoX1Isq3sAYp2BVt90XmEaB0mJ+GeW61Ayhc/RZwagi
 O8d2fG+PWplg==
X-IronPort-AV: E=McAfee;i="6000,8403,9809"; a="168688338"
X-IronPort-AV: E=Sophos;i="5.77,490,1596524400";
   d="scan'208";a="168688338"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Nov 2020 01:27:29 -0800
IronPort-SDR: 
 TEg03bbl5rb7jwIcozDaM3tJpmDfJbPp2TnSGb0aRXUNaRUI4M+2z0h3OJUa/jVQiEOq+XpP4x
 G9v06joXuw2A==
X-IronPort-AV: E=Sophos;i="5.77,490,1596524400";
   d="scan'208";a="544939790"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga005-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Nov 2020 01:27:26 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RFC PATCH 0/2] Add KVM support for bus lock debug exception
Date: Thu, 19 Nov 2020 17:29:55 +0800
Message-Id: <20201119092957.16940-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A bus lock is acquired either through split locked access to writeback
(WB) memory or by using locks to uncacheable (UC) memory. This is
typically > 1000 cycles slower than atomic opertaion within a cache
line. It also disrupts performance on other cores.

Bus lock debug exception is a sub-feature of bus lock detection. It is
an ability to notify the kernel by an #DB trap after the instruction
acquires a bus lock when CPL>0. This allows the kernel to enforce user
application throttling or mitigatioins.

Expose the bus lock debug exception to guest by the enumeration of
CPUID.(EAX=7,ECX=0).ECX[24]. Software in guest can enable these
exceptions by setting the DEBUGCTLMSR_BUS_LOCK_DETECT(bit 2) of
MSR_IA32_DEBUTCTL. This patch series add the MSR handling for
DEBUGCTLMSR_BUS_LOCK_DETECT.

The bus lock #DB exception can alse be intercepted by the VMM and
identified through the bit 11 of the exit qualification at VM exit. The
bit 11 (DR6_BUS_LOCK) of DR6 register is introduced to indicate a bus
lock #DB exception. DR6_BUS_LOCK has formerly always been 1 and delivery
of a bus lock #DB clears it. The VMM should emulate the exceptions by
clearing the bit 11 of the guest DR6.

The kernel RFC patch set for bus lock debug exception is available at
https://lore.kernel.org/lkml/20201111192048.2602065-1-fenghua.yu@intel.com/

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

Chenyi Qiang (2):
  KVM: X86: Add support for the emulation of DR6_BUS_LOCK bit
  KVM: X86: Expose bus lock debug exception to guest

 arch/x86/include/asm/kvm_host.h |  5 ++--
 arch/x86/kvm/cpuid.c            |  3 ++-
 arch/x86/kvm/emulate.c          |  2 +-
 arch/x86/kvm/svm/svm.c          |  6 ++---
 arch/x86/kvm/vmx/nested.c       |  2 +-
 arch/x86/kvm/vmx/vmx.c          | 29 +++++++++++++++++++---
 arch/x86/kvm/x86.c              | 44 ++++++++++++++-------------------
 arch/x86/kvm/x86.h              |  2 ++
 8 files changed, 56 insertions(+), 37 deletions(-)
```
#### [PATCH v6 00/17] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Thu Nov 19 14:41:29 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11917665
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EBA17C6379D
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:42:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 96554246E1
	for <kvm@archiver.kernel.org>; Thu, 19 Nov 2020 14:42:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="QsUGwdze"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728044AbgKSOlz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 19 Nov 2020 09:41:55 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37382 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727074AbgKSOly (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Nov 2020 09:41:54 -0500
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EDF98C0613D4
        for <kvm@vger.kernel.org>; Thu, 19 Nov 2020 06:41:53 -0800 (PST)
Received: by mail-wr1-x444.google.com with SMTP id 23so6668363wrc.8
        for <kvm@vger.kernel.org>; Thu, 19 Nov 2020 06:41:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0+QV0eroCOghP6iF2qF6VQojb/qmwXTdLdxbXgSm38Q=;
        b=QsUGwdzetI9prZKoeP2iAhcymfOD+I5vw5uQlsYPHXPJ6OfnoBMufDTFzZUJjNMLZ9
         Yxrnkb3r0QOgb8tbJN+frKR3E7076su7FmADL1RedADyOMYsxHMJ1LuezxqfJ+4zvmNr
         w6i7QaH+qoovsm/gkgX6mzTZtHLEyBkDPfyDk=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=0+QV0eroCOghP6iF2qF6VQojb/qmwXTdLdxbXgSm38Q=;
        b=Gl5rU5oF0b4i87FT2nJi3yWf6N5ZsFDuZ14kjD1dx7GQWWavPANZE8qdz/uclSxpfM
         Xp+GxC7d7RurfJOdcsBbS+fz6ib4oE7zMB3lxflznezJ8fbjvzJLSI4NqGxkARv3EGXa
         h2NPhf0HyktlMgHlMhCbB+Tiry7+u1Kg/Wd8c4lDhalq6YoBoLdrS9yjEn9M9RggYtya
         wMQouNL/Ne8EuKpnGqPOxhVDUTAUsfhj8LY2cB7MBDa25cHwKLe+s1orrADmEOhjZpH9
         rMF0+o4gkyrq7gpS06ZjKbj0qNRuNMCmP/AveSQm8i5Ag4Tig+/mNSWHWU0rynzy5PRZ
         mN5g==
X-Gm-Message-State: AOAM533EkiE9PFs7Yh1BxOKxYfM5Fe9akbNffoSFffT0+jTi4jynYr+d
        uJJ/Fug401g9ppVman9fQFpPcQ==
X-Google-Smtp-Source: 
 ABdhPJwEr0+MWxW25HcjQdBlrf+fNcxCL3BoIHGbwL4k+zwCdrQxRdMboyjz6DNXtMlDrKrjaCEFzw==
X-Received: by 2002:a5d:4947:: with SMTP id r7mr9987226wrs.50.1605796912703;
        Thu, 19 Nov 2020 06:41:52 -0800 (PST)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id x63sm51292wmb.48.2020.11.19.06.41.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 19 Nov 2020 06:41:51 -0800 (PST)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v6 00/17] follow_pfn and other iomap races
Date: Thu, 19 Nov 2020 15:41:29 +0100
Message-Id: <20201119144146.1045202-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all

Another update of my patch series to clamp down a bunch of races and gaps
around follow_pfn and other access to iomem mmaps. Previous version:

v1: https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/
v2: https://lore.kernel.org/dri-devel/20201009075934.3509076-1-daniel.vetter@ffwll.ch
v3: https://lore.kernel.org/dri-devel/20201021085655.1192025-1-daniel.vetter@ffwll.ch/
v4: https://lore.kernel.org/dri-devel/20201026105818.2585306-1-daniel.vetter@ffwll.ch/
v5: https://lore.kernel.org/dri-devel/20201030100815.2269-1-daniel.vetter@ffwll.ch/

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

Unfortunately took way longer to update than I hoped, I got sidetracked
with a few things.

Changes in v6:
- Tested v4l userptr as Tomasz suggested. No boom observed
- Added RFC for locking down follow_pfn, per discussion with Christoph and
  Jason.
- Explain why pup_fast is safe in relevant patches, there was a bit a
  confusion when discussing v5.
- Fix up the resource patch, with CONFIG_IO_STRICT_DEVMEM it crashed on
  boot due to an unintended change (reported by John)

Changes in v5:
- Tomasz found some issues in the media patches
- Polish suggested by Christoph for the unsafe_follow_pfn patch

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

Daniel Vetter (17):
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
  RFC: kvm: pass kvm argument to follow_pfn callsites
  RFC: mm: add mmu_notifier argument to follow_pfn

 arch/powerpc/kvm/book3s_64_mmu_hv.c           |   2 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c        |   2 +-
 arch/powerpc/kvm/e500_mmu_host.c              |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |   8 +-
 drivers/char/mem.c                            |  86 +------------
 drivers/gpu/drm/exynos/Kconfig                |   1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c       |  48 ++++----
 drivers/media/common/videobuf2/Kconfig        |   1 -
 drivers/media/common/videobuf2/Makefile       |   1 +
 .../media/common/videobuf2}/frame_vector.c    |  57 +++------
 .../media/common/videobuf2/videobuf2-memops.c |   3 +-
 drivers/media/platform/omap/Kconfig           |   1 -
 drivers/media/v4l2-core/videobuf-dma-contig.c |   2 +-
 drivers/misc/habanalabs/Kconfig               |   1 -
 drivers/misc/habanalabs/common/habanalabs.h   |   6 +-
 drivers/misc/habanalabs/common/memory.c       |  50 +++-----
 drivers/pci/pci-sysfs.c                       |   4 +
 drivers/pci/proc.c                            |   6 +
 drivers/vfio/vfio_iommu_type1.c               |   4 +-
 fs/sysfs/file.c                               |  11 ++
 include/linux/ioport.h                        |   6 +-
 include/linux/kvm_host.h                      |   9 +-
 include/linux/mm.h                            |  50 +-------
 include/linux/sysfs.h                         |   2 +
 include/media/frame_vector.h                  |  47 +++++++
 include/media/videobuf2-core.h                |   1 +
 kernel/resource.c                             |  98 ++++++++++++++-
 mm/Kconfig                                    |   3 -
 mm/Makefile                                   |   1 -
 mm/memory.c                                   | 115 +++++++++++++++---
 mm/nommu.c                                    |  48 +++++++-
 security/Kconfig                              |  13 ++
 virt/kvm/kvm_main.c                           |  56 +++++----
 33 files changed, 447 insertions(+), 298 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (84%)
 create mode 100644 include/media/frame_vector.h
```
