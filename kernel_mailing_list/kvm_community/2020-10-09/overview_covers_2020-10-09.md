

#### [PATCH v2 00/17] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Fri Oct  9 07:59:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11825175
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0B5FA1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 08:00:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E1762222C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 08:00:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="DEazGm3/"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732681AbgJIIAG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 04:00:06 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49448 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732644AbgJIH7x (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 03:59:53 -0400
Received: from mail-wm1-x341.google.com (mail-wm1-x341.google.com
 [IPv6:2a00:1450:4864:20::341])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1C262C0613D6
        for <kvm@vger.kernel.org>; Fri,  9 Oct 2020 00:59:53 -0700 (PDT)
Received: by mail-wm1-x341.google.com with SMTP id j136so8892645wmj.2
        for <kvm@vger.kernel.org>; Fri, 09 Oct 2020 00:59:53 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=immTPDdSm8V7ezbOteojXYm/j7WkY1f3P9Y0YpK7onQ=;
        b=DEazGm3//HS7eifrtPTNpv9gPNwxpuxjM7cgzXbcLG0mO5e39cJ73eX9iQKQEkxr4Y
         FwEAxZ/eknqujf87zOGqp6tESSOeL2I6VSIobgrZsNnXiWlr9VWW7WhVnV0GrVhO4vMj
         1v4YtSGCDuC7IGf+ELUEOwyj9sMdI3c9bq3Xg=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=immTPDdSm8V7ezbOteojXYm/j7WkY1f3P9Y0YpK7onQ=;
        b=G1+KsQSFRyzXgrsPUwP7Vv48pN0hgb5Nr7yYQMoD8JSu+JqRXoRqAU9e3EahUzNHLe
         PdoR2mJU980NSDZVqFgfV97v9HDeW1/F6rf+getqtQpDD8sBRgLJRHMyYkSWy6AmONf/
         YR5IrTff9g0FYAtRCfV8xqnHODzcLI/7Z/akDsYtUrodDVd/gwBdagb9G4lJEsTq4QKU
         eLBEXhpH0DhdHR1gbGKkavLMKkGZ1aZY2Alw4a2xAe5qtxiOxE1Wk1kW5Uv5rG/rEKJr
         eL5VlA98qgrFclx5i4Po+qYDQE158dvks+4GjViHTmwZ0tJ+eL7kF23KyLW/FjM2W85B
         Dvbg==
X-Gm-Message-State: AOAM5323IuOSkgAX4FcgTIt7QRJ64GG7Cvr2CmCv65NKhRNnjHvlLTmV
        Jq0SifDk2iL1z/YKC2SqhWITJw==
X-Google-Smtp-Source: 
 ABdhPJzyDJpFjA/Q+sv1RhX5gsGPQpkP/4WlxxT8RLqjQWQaBWIid1inU3iHz1dJQWF+W7VpBZ1zIA==
X-Received: by 2002:a1c:f311:: with SMTP id
 q17mr13703008wmq.168.1602230391713;
        Fri, 09 Oct 2020 00:59:51 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 u17sm11634118wri.45.2020.10.09.00.59.50
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 09 Oct 2020 00:59:50 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        linux-s390@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v2 00/17] follow_pfn and other iomap races
Date: Fri,  9 Oct 2020 09:59:17 +0200
Message-Id: <20201009075934.3509076-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Round two of my patch series to clamp down a bunch of races and gaps
around follow_pfn and other access to iomem mmaps. Previous version:

v1: https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

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

Daniel Vetter (17):
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
  drm/i915: Properly request PCI BARs

 arch/s390/pci/pci_mmio.c                      | 98 +++++++++++--------
 drivers/char/mem.c                            | 86 +---------------
 drivers/gpu/drm/exynos/Kconfig                |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c       | 48 ++++-----
 drivers/gpu/drm/i915/intel_uncore.c           | 25 ++++-
 drivers/media/common/videobuf2/Kconfig        |  1 -
 drivers/media/common/videobuf2/Makefile       |  1 +
 .../media/common/videobuf2}/frame_vector.c    | 54 ++++------
 drivers/media/platform/omap/Kconfig           |  1 -
 drivers/media/v4l2-core/videobuf-dma-contig.c |  2 +-
 drivers/misc/habanalabs/Kconfig               |  1 -
 drivers/misc/habanalabs/common/habanalabs.h   |  3 +-
 drivers/misc/habanalabs/common/memory.c       | 50 ++++------
 drivers/pci/pci-sysfs.c                       |  4 +
 drivers/pci/proc.c                            |  6 ++
 drivers/vfio/vfio_iommu_type1.c               |  4 +-
 fs/sysfs/file.c                               | 11 +++
 include/linux/ioport.h                        |  6 +-
 include/linux/mm.h                            | 47 +--------
 include/linux/sysfs.h                         |  2 +
 include/media/videobuf2-core.h                | 42 ++++++++
 kernel/resource.c                             | 95 +++++++++++++++++-
 mm/Kconfig                                    |  3 -
 mm/Makefile                                   |  1 -
 mm/memory.c                                   | 76 +++++++++++++-
 mm/nommu.c                                    | 17 ++++
 security/Kconfig                              | 13 +++
 27 files changed, 412 insertions(+), 286 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (85%)
```
#### [PATCH v2 0/8] Fix x2apic enablement and allow up to 32768 CPUs
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Fri Oct  9 10:46:08 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11825581
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A3BB15E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 10:47:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D9A76222BA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 10:47:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="NcGFYa2q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387797AbgJIKq1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 06:46:27 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47006 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2387783AbgJIKq0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 06:46:26 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id EA989C0613D2;
        Fri,  9 Oct 2020 03:46:25 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:
        To:From:Reply-To:Content-ID:Content-Description;
        bh=oifcmCxgengDm0xlwPlx0P/sTS4kOs7GnADWSNebHiM=;
 b=NcGFYa2qfSUwdH8mcITnks74J5
        EnDN910UORGykfR//CV5V5ibG5pfQ2Csav9qhmBWIDZ0dVZV3g/KHu16nm3SmADXEr25/oURzSh6V
        08n+YT8VuEwzVrWR0vkBE0PaIFdGemU3fYj/uBasz0CBl0KveLTPo3LqaSyHfanhIt3BrOjMUoJUJ
        RKGhZeIeOIEEqumnsPmzYPOr2qcEkkDGakVyFCdVHG295FzjZNaOpLh/OHV6rH+dzKQXLlW+Dxbif
        4KMtOfcH2qU46yr3aIv2Zx8LxPZcuJqyLpOq5242xyuoXmTqk3uiAuPbVrngiHcR4QhxYmdgZ6c50
        OZB9COXw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kQpuq-00050S-13; Fri, 09 Oct 2020 10:46:24 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.93 #3 (Red Hat
 Linux))
        id 1kQpup-005W3r-0K; Fri, 09 Oct 2020 11:46:23 +0100
From: David Woodhouse <dwmw2@infradead.org>
To: x86@kernel.org
Cc: kvm <kvm@vger.kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>,
        linux-hyperv@vger.kernel.org
Subject: [PATCH v2 0/8] Fix x2apic enablement and allow up to 32768 CPUs
 without IR where supported
Date: Fri,  9 Oct 2020 11:46:08 +0100
Message-Id: <20201009104616.1314746-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
References: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the conditions for enabling x2apic on guests without interrupt 
remapping, and support 15-bit Extended Destination ID to allow 32768 
CPUs without IR on hypervisors that support it.

The last patch in the series now makes io_apic.c generate its RTE from 
the MSI message created by the parent irqchip, and removes all the nasty 
hackery where IRQ remapping drivers would frob I/OAPIC RTEs for 
themselves directly. It's last because I'd quite like to see it tested 
especially with Hyper-V and it doesn't actually eliminate the need for 
io_apic.c to know about the 15-bit extension anyway.

v2:
 • Minor cleanups.
 • Move __irq_msi_compose_msg() to apic.c, make virt_ext_dest_id static.
 • Generate I/OAPIC RTE directly from parent irqchip's MSI messages.
 • Clean up HPET MSI support into hpet.c now that we can.

David Woodhouse (8):
      x86/apic: Fix x2apic enablement without interrupt remapping
      x86/msi: Only use high bits of MSI address for DMAR unit
      x86/apic: Always provide irq_compose_msi_msg() method for vector domain
      x86/ioapic: Handle Extended Destination ID field in RTE
      x86/apic: Support 15 bits of APIC ID in MSI where available
      x86/kvm: Add KVM_FEATURE_MSI_EXT_DEST_ID
      x86/hpet: Move MSI support into hpet.c
      x86/ioapic: Generate RTE directly from parent irqchip's MSI message

 Documentation/virt/kvm/cpuid.rst     |   4 +
 arch/x86/include/asm/apic.h          |   9 +--
 arch/x86/include/asm/hpet.h          |  11 ---
 arch/x86/include/asm/hw_irq.h        |  11 ++-
 arch/x86/include/asm/io_apic.h       |   3 +-
 arch/x86/include/asm/msidef.h        |   2 +
 arch/x86/include/asm/x86_init.h      |   2 +
 arch/x86/include/uapi/asm/kvm_para.h |   1 +
 arch/x86/kernel/apic/apic.c          |  68 ++++++++++++++--
 arch/x86/kernel/apic/io_apic.c       |  66 +++++++++------
 arch/x86/kernel/apic/msi.c           | 152 +++--------------------------------
 arch/x86/kernel/apic/vector.c        |   6 ++
 arch/x86/kernel/apic/x2apic_phys.c   |   9 +++
 arch/x86/kernel/hpet.c               | 116 ++++++++++++++++++++++++--
 arch/x86/kernel/kvm.c                |   6 ++
 arch/x86/kernel/x86_init.c           |   1 +
 drivers/iommu/amd/iommu.c            |  14 ----
 drivers/iommu/hyperv-iommu.c         |  31 -------
 drivers/iommu/intel/irq_remapping.c  |  19 ++---
 19 files changed, 276 insertions(+), 255 deletions(-)
```
#### [PATCH v2 0/4] Test MSR exits to userspace
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Fri Oct  9 11:46:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11825623
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C0A8139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 11:46:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5CC862226B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 11:46:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="vmHM3u9F"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732810AbgJILqW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 07:46:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56298 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732494AbgJILqV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 07:46:21 -0400
Received: from mail-pf1-x44a.google.com (mail-pf1-x44a.google.com
 [IPv6:2607:f8b0:4864:20::44a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4072DC0613D2
        for <kvm@vger.kernel.org>; Fri,  9 Oct 2020 04:46:20 -0700 (PDT)
Received: by mail-pf1-x44a.google.com with SMTP id c21so6444377pfd.16
        for <kvm@vger.kernel.org>; Fri, 09 Oct 2020 04:46:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=8iM9xn/WrbdOnFuGxBykwqYFqH+U6wmGWc28LA7ANGA=;
        b=vmHM3u9Fk5vGa5l4B4N8xfOMT21uq3Ldl8xcsNjyz1krtriX3lI8OWQcSh1oPn24Vv
         QTPsmqCu7WG2daYFSW5rexLXzWuF+0kQ/3eIpSOt0v3JmHAA5pgu26g1u0UxKVDN+pZ9
         eBaJwPJ5rQBQlSjQ4lwQEnVKI/TxUYTQmBN30sz05LFDo2EpYJLUVg41hibbx3ucUAyN
         O4Sam7RfW2VKoPWDk4CvWwOwnBxH1ZbBjlm9/Rw0QAAEsjti6+zTxsD+o6FwRk9T4d/w
         S19IqDnLCwH9dU5NF3GDyjVRqWtXgqoYbndyG8+P5MGJsPmWmzFTkcodhwUwstN0TFyU
         V2iw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=8iM9xn/WrbdOnFuGxBykwqYFqH+U6wmGWc28LA7ANGA=;
        b=KOyOkiFhkFThW42OsTKOfZMLXE4evWjQiFG37Ck7oD/AnkC5mE6v2o+B91Vq75mYIR
         QrsYkD6bHye7ph86t4He93QBkkgQrYQZy8n8wPC1Y+bs852DH75qiW4OLKhiLPMXVtKN
         4cXumRadCzgE0YPnVvZpyYIrgbFyqdMGFVt4cyAEIPamlP6X/EyOiQ8LI8/FOTTYeo8I
         7Ah6EqKAgBpZI242I7qgCw4l5BpRVkaBjuEZNneRXvYSIfnxNs32ClTCxXWct+VfTyiC
         JCVkE9TvHMP863R5nv5GAcfgKLK5MpoHsZMmlHMlM4Jq+OiBshIlzPYRPgmLBh9vxNyg
         u7pA==
X-Gm-Message-State: AOAM530+PktkEbjamd9nZdzaqVbiJvdzVkip3ok9hN0QxVQ0FxGQ7WSs
        /NYORlBjxl7xYh2iOyxBSozhn31L1aTlbiYF
X-Google-Smtp-Source: 
 ABdhPJws9cAPQxzbscQZD02qD18Rzeegqki4zpTvVnJ41clMz5tqZglma1vrY/k0ackWAqQ6PGmSPfPIMSM+H8Hd
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:a17:90a:940c:: with SMTP id
 r12mr1676173pjo.1.1602243979403; Fri, 09 Oct 2020 04:46:19 -0700 (PDT)
Date: Fri,  9 Oct 2020 04:46:11 -0700
Message-Id: <20201009114615.2187411-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.1011.ga647a8990f-goog
Subject: [PATCH v2 0/4] Test MSR exits to userspace
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset adds additional testing to the series ("Allow user space to
restrict and augment MSR emulation") by Alexander Graf <graf@amazon.com>,
and supliments the selftest in that series.

This patchset introduces exception handling into the kvm selftest framework
which is then used in the test to be able to handle #GPs that are injected
into the guest from userspace.

The test focuses on two main areas:
  1) It tests the MSR filter API.
  2) It tests MSR permission bitmaps.

v1 -> v2:

  - Use exception_handlers instead of gs base to pass table to the guest.
  - Move unexpected vector assert to processor.c.

Aaron Lewis (4):
  selftests: kvm: Fix the segment descriptor layout to match the actual
    layout
  selftests: kvm: Clear uc so UCALL_NONE is being properly reported
  selftests: kvm: Add exception handling to selftests
  selftests: kvm: Test MSR exiting to userspace

 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |  20 +-
 .../selftests/kvm/include/x86_64/processor.h  |  27 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |   7 +
 .../selftests/kvm/lib/kvm_util_internal.h     |   2 +
 tools/testing/selftests/kvm/lib/s390x/ucall.c |   3 +
 .../selftests/kvm/lib/x86_64/handlers.S       |  81 +++
 .../selftests/kvm/lib/x86_64/processor.c      | 117 +++-
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |   3 +
 .../kvm/x86_64/userspace_msr_exit_test.c      | 547 ++++++++++++++++++
 11 files changed, 800 insertions(+), 11 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/handlers.S
 create mode 100644 tools/testing/selftests/kvm/x86_64/userspace_msr_exit_test.c
```
#### [PATCH RFC PKS/PMEM 00/58] PMEM: Introduce stray write protection for
##### From: ira.weiny@intel.com
From: Ira Weiny <ira.weiny@intel.com>

```c
From patchwork Fri Oct  9 19:49:35 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ira Weiny <ira.weiny@intel.com>
X-Patchwork-Id: 11827309
Return-Path: <SRS0=Illt=DQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63B2B1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 19:50:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4F2CC223AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  9 Oct 2020 19:50:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389005AbgJITuq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 9 Oct 2020 15:50:46 -0400
Received: from mga02.intel.com ([134.134.136.20]:57507 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726357AbgJITup (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 9 Oct 2020 15:50:45 -0400
IronPort-SDR: 
 EgmAoyvHqLfUgUFSlazRhx1Cjp9MmVlenKbZYXMVRVRfgMzpJRftl57MJq2pMTa+nNfk+FbMHQ
 4ZNHJky2ihhA==
X-IronPort-AV: E=McAfee;i="6000,8403,9769"; a="152450718"
X-IronPort-AV: E=Sophos;i="5.77,355,1596524400";
   d="scan'208";a="152450718"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Oct 2020 12:50:41 -0700
IronPort-SDR: 
 wgvSBhlinBwJf2eRaqYm1d4mOPDeheaaBRmvXZpaWhx0BsPjq5MOqCRmfglsuVIrge+HvLIvQ5
 IT741lyNdN2Q==
X-IronPort-AV: E=Sophos;i="5.77,355,1596524400";
   d="scan'208";a="419536654"
Received: from iweiny-desk2.sc.intel.com (HELO localhost) ([10.3.52.147])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Oct 2020 12:50:41 -0700
From: ira.weiny@intel.com
To: Andrew Morton <akpm@linux-foundation.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Ira Weiny <ira.weiny@intel.com>, x86@kernel.org,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-nvdimm@lists.01.org,
        linux-fsdevel@vger.kernel.org, linux-mm@kvack.org,
        linux-kselftest@vger.kernel.org, linuxppc-dev@lists.ozlabs.org,
        kvm@vger.kernel.org, netdev@vger.kernel.org, bpf@vger.kernel.org,
        kexec@lists.infradead.org, linux-bcache@vger.kernel.org,
        linux-mtd@lists.infradead.org, devel@driverdev.osuosl.org,
        linux-efi@vger.kernel.org, linux-mmc@vger.kernel.org,
        linux-scsi@vger.kernel.org, target-devel@vger.kernel.org,
        linux-nfs@vger.kernel.org, ceph-devel@vger.kernel.org,
        linux-ext4@vger.kernel.org, linux-aio@kvack.org,
        io-uring@vger.kernel.org, linux-erofs@lists.ozlabs.org,
        linux-um@lists.infradead.org, linux-ntfs-dev@lists.sourceforge.net,
        reiserfs-devel@vger.kernel.org,
        linux-f2fs-devel@lists.sourceforge.net,
        linux-nilfs@vger.kernel.org, cluster-devel@redhat.com,
        ecryptfs@vger.kernel.org, linux-cifs@vger.kernel.org,
        linux-btrfs@vger.kernel.org, linux-afs@lists.infradead.org,
        linux-rdma@vger.kernel.org, amd-gfx@lists.freedesktop.org,
        dri-devel@lists.freedesktop.org, intel-gfx@lists.freedesktop.org,
        drbd-dev@lists.linbit.com, linux-block@vger.kernel.org,
        xen-devel@lists.xenproject.org, linux-cachefs@redhat.com,
        samba-technical@lists.samba.org, intel-wired-lan@lists.osuosl.org
Subject: [PATCH RFC PKS/PMEM 00/58] PMEM: Introduce stray write protection for
 PMEM
Date: Fri,  9 Oct 2020 12:49:35 -0700
Message-Id: <20201009195033.3208459-1-ira.weiny@intel.com>
X-Mailer: git-send-email 2.28.0.rc0.12.gb6a658bd00c9
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ira Weiny <ira.weiny@intel.com>

Should a stray write in the kernel occur persistent memory is affected more
than regular memory.  A write to the wrong area of memory could result in
latent data corruption which will will persist after a reboot.  PKS provides a
nice way to restrict access to persistent memory kernel mappings, while
providing fast access when needed.

Since the last RFC[1] this patch set has grown quite a bit.  It now depends on
the core patches submitted separately.

	https://lore.kernel.org/lkml/20201009194258.3207172-1-ira.weiny@intel.com/

And contained in the git tree here:

	https://github.com/weiny2/linux-kernel/tree/pks-rfc-v3

However, functionally there is only 1 major change from the last RFC.
Specifically, kmap() is most often used within a single thread in a 'map/do
something/unmap' pattern.  In fact this is the pattern used in ~90% of the
callers of kmap().  This pattern works very well for the pmem use case and the
testing which was done.  However, there were another ~20-30 kmap users which do
not follow this pattern.  Some of them seem to expect the mapping to be
'global' while others require a detailed audit to be sure.[2][3]

While we don't anticipate global mappings to pmem there is a danger in
changing the semantics of kmap().  Effectively, this would cause an unresolved
page fault with little to no information about why.

There were a number of options considered.

1) Attempt to change all the thread local kmap() calls to kmap_atomic()
2) Introduce a flags parameter to kmap() to indicate if the mapping should be
   global or not
3) Change ~20-30 call sites to 'kmap_global()' to indicate that they require a
   global mapping of the pages
4) Change ~209 call sites to 'kmap_thread()' to indicate that the mapping is to
   be used within that thread of execution only

Option 1 is simply not feasible kmap_atomic() is not the same semantic as
kmap() within a single tread.  Option 2 would require all of the call sites of
kmap() to change.  Option 3 seems like a good minimal change but there is a
danger that new code may miss the semantic change of kmap() and not get the
behavior intended for future users.  Therefore, option #4 was chosen.

To handle the global PKRS state in the most efficient manner possible.  We
lazily override the thread specific PKRS key value only when needed because we
anticipate PKS to not be needed will not be needed most of the time.  And even
when it is used 90% of the time it is a thread local call.


[1] https://lore.kernel.org/lkml/20200717072056.73134-1-ira.weiny@intel.com/

[2] The following list of callers continue calling kmap() (utilizing the global
PKRS).  It would be nice if more of them could be converted to kmap_thread()

	drivers/firewire/net.c:         ptr = kmap(dev->broadcast_rcv_buffer.pages[u]);
	drivers/gpu/drm/i915/gem/i915_gem_pages.c:              return kmap(sg_page(sgt->sgl));
	drivers/gpu/drm/ttm/ttm_bo_util.c:              map->virtual = kmap(map->page);
	drivers/infiniband/hw/qib/qib_user_sdma.c:      mpage = kmap(page);
	drivers/misc/vmw_vmci/vmci_host.c:      context->notify = kmap(context->notify_page) + (uva & (PAGE_SIZE - 1));
	drivers/misc/xilinx_sdfec.c:            addr = kmap(pages[i]);
	drivers/mmc/host/usdhi6rol0.c:  host->pg.mapped         = kmap(host->pg.page);
	drivers/mmc/host/usdhi6rol0.c:  host->pg.mapped = kmap(host->pg.page);
	drivers/mmc/host/usdhi6rol0.c:  host->pg.mapped = kmap(host->pg.page);
	drivers/nvme/target/tcp.c:              iov->iov_base = kmap(sg_page(sg)) + sg->offset + sg_offset;
	drivers/scsi/libiscsi_tcp.c:            segment->sg_mapped = kmap(sg_page(sg));
	drivers/target/iscsi/iscsi_target.c:            iov[i].iov_base = kmap(sg_page(sg)) + sg->offset + page_off;
	drivers/target/target_core_transport.c:         return kmap(sg_page(sg)) + sg->offset;
	fs/btrfs/check-integrity.c:             block_ctx->datav[i] = kmap(block_ctx->pagev[i]);
	fs/ceph/dir.c:          cache_ctl->dentries = kmap(cache_ctl->page);
	fs/ceph/inode.c:                ctl->dentries = kmap(ctl->page);
	fs/erofs/zpvec.h:               kmap_atomic(ctor->curr) : kmap(ctor->curr);
	lib/scatterlist.c:              miter->addr = kmap(miter->page) + miter->__offset;
	net/ceph/pagelist.c:    pl->mapped_tail = kmap(page);
	net/ceph/pagelist.c:            pl->mapped_tail = kmap(page);
	virt/kvm/kvm_main.c:                    hva = kmap(page);

[3] The following appear to follow the same pattern as ext2 which was converted
after some code audit.  So I _think_ they too could be converted to
k[un]map_thread().

	fs/freevxfs/vxfs_subr.c|75| kmap(pp);
	fs/jfs/jfs_metapage.c|102| kmap(page);
	fs/jfs/jfs_metapage.c|156| kmap(page);
	fs/minix/dir.c|72| kmap(page);
	fs/nilfs2/dir.c|195| kmap(page);
	fs/nilfs2/ifile.h|24| void *kaddr = kmap(ibh->b_page);
	fs/ntfs/aops.h|78| kmap(page);
	fs/ntfs/compress.c|574| kmap(page);
	fs/qnx6/dir.c|32| kmap(page);
	fs/qnx6/dir.c|58| kmap(*p = page);
	fs/qnx6/inode.c|190| kmap(page);
	fs/qnx6/inode.c|557| kmap(page);
	fs/reiserfs/inode.c|2397| kmap(bh_result->b_page);
	fs/reiserfs/xattr.c|444| kmap(page);
	fs/sysv/dir.c|60| kmap(page);
	fs/sysv/dir.c|262| kmap(page);
	fs/ufs/dir.c|194| kmap(page);
	fs/ufs/dir.c|562| kmap(page);


Ira Weiny (58):
  x86/pks: Add a global pkrs option
  x86/pks/test: Add testing for global option
  memremap: Add zone device access protection
  kmap: Add stray access protection for device pages
  kmap: Introduce k[un]map_thread
  kmap: Introduce k[un]map_thread debugging
  drivers/drbd: Utilize new kmap_thread()
  drivers/firmware_loader: Utilize new kmap_thread()
  drivers/gpu: Utilize new kmap_thread()
  drivers/rdma: Utilize new kmap_thread()
  drivers/net: Utilize new kmap_thread()
  fs/afs: Utilize new kmap_thread()
  fs/btrfs: Utilize new kmap_thread()
  fs/cifs: Utilize new kmap_thread()
  fs/ecryptfs: Utilize new kmap_thread()
  fs/gfs2: Utilize new kmap_thread()
  fs/nilfs2: Utilize new kmap_thread()
  fs/hfs: Utilize new kmap_thread()
  fs/hfsplus: Utilize new kmap_thread()
  fs/jffs2: Utilize new kmap_thread()
  fs/nfs: Utilize new kmap_thread()
  fs/f2fs: Utilize new kmap_thread()
  fs/fuse: Utilize new kmap_thread()
  fs/freevxfs: Utilize new kmap_thread()
  fs/reiserfs: Utilize new kmap_thread()
  fs/zonefs: Utilize new kmap_thread()
  fs/ubifs: Utilize new kmap_thread()
  fs/cachefiles: Utilize new kmap_thread()
  fs/ntfs: Utilize new kmap_thread()
  fs/romfs: Utilize new kmap_thread()
  fs/vboxsf: Utilize new kmap_thread()
  fs/hostfs: Utilize new kmap_thread()
  fs/cramfs: Utilize new kmap_thread()
  fs/erofs: Utilize new kmap_thread()
  fs: Utilize new kmap_thread()
  fs/ext2: Use ext2_put_page
  fs/ext2: Utilize new kmap_thread()
  fs/isofs: Utilize new kmap_thread()
  fs/jffs2: Utilize new kmap_thread()
  net: Utilize new kmap_thread()
  drivers/target: Utilize new kmap_thread()
  drivers/scsi: Utilize new kmap_thread()
  drivers/mmc: Utilize new kmap_thread()
  drivers/xen: Utilize new kmap_thread()
  drivers/firmware: Utilize new kmap_thread()
  drives/staging: Utilize new kmap_thread()
  drivers/mtd: Utilize new kmap_thread()
  drivers/md: Utilize new kmap_thread()
  drivers/misc: Utilize new kmap_thread()
  drivers/android: Utilize new kmap_thread()
  kernel: Utilize new kmap_thread()
  mm: Utilize new kmap_thread()
  lib: Utilize new kmap_thread()
  powerpc: Utilize new kmap_thread()
  samples: Utilize new kmap_thread()
  dax: Stray access protection for dax_direct_access()
  nvdimm/pmem: Stray access protection for pmem->virt_addr
  [dax|pmem]: Enable stray access protection

 Documentation/core-api/protection-keys.rst    |  11 +-
 arch/powerpc/mm/mem.c                         |   4 +-
 arch/x86/entry/common.c                       |  28 +++
 arch/x86/include/asm/pkeys.h                  |   6 +-
 arch/x86/include/asm/pkeys_common.h           |   8 +-
 arch/x86/kernel/process.c                     |  74 ++++++-
 arch/x86/mm/fault.c                           | 193 ++++++++++++++----
 arch/x86/mm/pkeys.c                           |  88 ++++++--
 drivers/android/binder_alloc.c                |   4 +-
 drivers/base/firmware_loader/fallback.c       |   4 +-
 drivers/base/firmware_loader/main.c           |   4 +-
 drivers/block/drbd/drbd_main.c                |   4 +-
 drivers/block/drbd/drbd_receiver.c            |  12 +-
 drivers/dax/device.c                          |   2 +
 drivers/dax/super.c                           |   2 +
 drivers/firmware/efi/capsule-loader.c         |   6 +-
 drivers/firmware/efi/capsule.c                |   4 +-
 drivers/gpu/drm/amd/amdgpu/amdgpu_ttm.c       |  12 +-
 drivers/gpu/drm/gma500/gma_display.c          |   4 +-
 drivers/gpu/drm/gma500/mmu.c                  |  10 +-
 drivers/gpu/drm/i915/gem/i915_gem_shmem.c     |   4 +-
 .../drm/i915/gem/selftests/i915_gem_context.c |   4 +-
 .../drm/i915/gem/selftests/i915_gem_mman.c    |   8 +-
 drivers/gpu/drm/i915/gt/intel_ggtt_fencing.c  |   4 +-
 drivers/gpu/drm/i915/gt/intel_gtt.c           |   4 +-
 drivers/gpu/drm/i915/gt/shmem_utils.c         |   4 +-
 drivers/gpu/drm/i915/i915_gem.c               |   8 +-
 drivers/gpu/drm/i915/i915_gpu_error.c         |   4 +-
 drivers/gpu/drm/i915/selftests/i915_perf.c    |   4 +-
 drivers/gpu/drm/radeon/radeon_ttm.c           |   4 +-
 drivers/infiniband/hw/hfi1/sdma.c             |   4 +-
 drivers/infiniband/hw/i40iw/i40iw_cm.c        |  10 +-
 drivers/infiniband/sw/siw/siw_qp_tx.c         |  14 +-
 drivers/md/bcache/request.c                   |   4 +-
 drivers/misc/vmw_vmci/vmci_queue_pair.c       |  12 +-
 drivers/mmc/host/mmc_spi.c                    |   4 +-
 drivers/mmc/host/sdricoh_cs.c                 |   4 +-
 drivers/mtd/mtd_blkdevs.c                     |  12 +-
 drivers/net/ethernet/intel/igb/igb_ethtool.c  |   4 +-
 .../net/ethernet/intel/ixgbe/ixgbe_ethtool.c  |   4 +-
 drivers/nvdimm/pmem.c                         |   6 +
 drivers/scsi/ipr.c                            |   8 +-
 drivers/scsi/pmcraid.c                        |   8 +-
 drivers/staging/rts5208/rtsx_transport.c      |   4 +-
 drivers/target/target_core_iblock.c           |   4 +-
 drivers/target/target_core_rd.c               |   4 +-
 drivers/target/target_core_transport.c        |   4 +-
 drivers/xen/gntalloc.c                        |   4 +-
 fs/afs/dir.c                                  |  16 +-
 fs/afs/dir_edit.c                             |  16 +-
 fs/afs/mntpt.c                                |   4 +-
 fs/afs/write.c                                |   4 +-
 fs/aio.c                                      |   4 +-
 fs/binfmt_elf.c                               |   4 +-
 fs/binfmt_elf_fdpic.c                         |   4 +-
 fs/btrfs/check-integrity.c                    |   4 +-
 fs/btrfs/compression.c                        |   4 +-
 fs/btrfs/inode.c                              |  16 +-
 fs/btrfs/lzo.c                                |  24 +--
 fs/btrfs/raid56.c                             |  34 +--
 fs/btrfs/reflink.c                            |   8 +-
 fs/btrfs/send.c                               |   4 +-
 fs/btrfs/zlib.c                               |  32 +--
 fs/btrfs/zstd.c                               |  20 +-
 fs/cachefiles/rdwr.c                          |   4 +-
 fs/cifs/cifsencrypt.c                         |   6 +-
 fs/cifs/file.c                                |  16 +-
 fs/cifs/smb2ops.c                             |   8 +-
 fs/cramfs/inode.c                             |  10 +-
 fs/ecryptfs/crypto.c                          |   8 +-
 fs/ecryptfs/read_write.c                      |   8 +-
 fs/erofs/super.c                              |   4 +-
 fs/erofs/xattr.c                              |   4 +-
 fs/exec.c                                     |  10 +-
 fs/ext2/dir.c                                 |   8 +-
 fs/ext2/ext2.h                                |   8 +
 fs/ext2/namei.c                               |  15 +-
 fs/f2fs/f2fs.h                                |   8 +-
 fs/freevxfs/vxfs_immed.c                      |   4 +-
 fs/fuse/readdir.c                             |   4 +-
 fs/gfs2/bmap.c                                |   4 +-
 fs/gfs2/ops_fstype.c                          |   4 +-
 fs/hfs/bnode.c                                |  14 +-
 fs/hfs/btree.c                                |  20 +-
 fs/hfsplus/bitmap.c                           |  20 +-
 fs/hfsplus/bnode.c                            | 102 ++++-----
 fs/hfsplus/btree.c                            |  18 +-
 fs/hostfs/hostfs_kern.c                       |  12 +-
 fs/io_uring.c                                 |   4 +-
 fs/isofs/compress.c                           |   4 +-
 fs/jffs2/file.c                               |   8 +-
 fs/jffs2/gc.c                                 |   4 +-
 fs/nfs/dir.c                                  |  20 +-
 fs/nilfs2/alloc.c                             |  34 +--
 fs/nilfs2/cpfile.c                            |   4 +-
 fs/ntfs/aops.c                                |   4 +-
 fs/reiserfs/journal.c                         |   4 +-
 fs/romfs/super.c                              |   4 +-
 fs/splice.c                                   |   4 +-
 fs/ubifs/file.c                               |  16 +-
 fs/vboxsf/file.c                              |  12 +-
 fs/zonefs/super.c                             |   4 +-
 include/linux/entry-common.h                  |   3 +
 include/linux/highmem.h                       |  63 +++++-
 include/linux/memremap.h                      |   1 +
 include/linux/mm.h                            |  43 ++++
 include/linux/pkeys.h                         |   6 +-
 include/linux/sched.h                         |   8 +
 include/trace/events/kmap_thread.h            |  56 +++++
 init/init_task.c                              |   6 +
 kernel/fork.c                                 |  18 ++
 kernel/kexec_core.c                           |   8 +-
 lib/Kconfig.debug                             |   8 +
 lib/iov_iter.c                                |  12 +-
 lib/pks/pks_test.c                            | 138 +++++++++++--
 lib/test_bpf.c                                |   4 +-
 lib/test_hmm.c                                |   8 +-
 mm/Kconfig                                    |  13 ++
 mm/debug.c                                    |  23 +++
 mm/memory.c                                   |   8 +-
 mm/memremap.c                                 |  90 ++++++++
 mm/swapfile.c                                 |   4 +-
 mm/userfaultfd.c                              |   4 +-
 net/ceph/messenger.c                          |   4 +-
 net/core/datagram.c                           |   4 +-
 net/core/sock.c                               |   8 +-
 net/ipv4/ip_output.c                          |   4 +-
 net/sunrpc/cache.c                            |   4 +-
 net/sunrpc/xdr.c                              |   8 +-
 net/tls/tls_device.c                          |   4 +-
 samples/vfio-mdev/mbochs.c                    |   4 +-
 131 files changed, 1284 insertions(+), 565 deletions(-)
 create mode 100644 include/trace/events/kmap_thread.h
```
