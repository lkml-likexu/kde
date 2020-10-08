

#### [PATCH 0/6] KVM: x86: KVM_SET_SREGS.CR4 bug fixes and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Oct  7 01:44:11 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11819645
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1CD78618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 01:44:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06EA52080A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 01:44:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727025AbgJGBoT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 21:44:19 -0400
Received: from mga09.intel.com ([134.134.136.24]:7786 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725996AbgJGBoT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 21:44:19 -0400
IronPort-SDR: 
 VoyZ/K2RKGL7K/1W/VtnQlAfNA1ewa2myzY3VJNqqkRkV8MKWgooDw8gT/u1UDsute5/P/INoU
 Fjq7Nn0iPIIA==
X-IronPort-AV: E=McAfee;i="6000,8403,9766"; a="164914594"
X-IronPort-AV: E=Sophos;i="5.77,344,1596524400";
   d="scan'208";a="164914594"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 Oct 2020 18:44:18 -0700
IronPort-SDR: 
 QPTpCXDbpGbu6qD+HFtns6yMfN22f+KJcQgpbAfbRrLy6DfIPy/g07l97PC9VS/cMfGoFbGEii
 lRi9br9NlMaA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,344,1596524400";
   d="scan'208";a="297410294"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.160])
  by fmsmga008.fm.intel.com with ESMTP; 06 Oct 2020 18:44:17 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Stas Sergeev <stsp@users.sourceforge.net>
Subject: [PATCH 0/6] KVM: x86: KVM_SET_SREGS.CR4 bug fixes and cleanup
Date: Tue,  6 Oct 2020 18:44:11 -0700
Message-Id: <20201007014417.29276-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two bug fixes to handle KVM_SET_SREGS without a preceding KVM_SET_CPUID2.

The overarching issue is that kvm_x86_ops.set_cr4() can fail, but its
invocation from __set_sregs(), a.k.a. KVM_SET_SREGS, ignores the result.
Fix the issue by moving all validity checks out of .set_cr4() in one way
or another.

I intentionally omitted a Cc to stable.  The first bug fix in particular
may break stable trees as it simply removes a check, and I don't know that
stable trees have the generic CR4 reserved bit check that is needed to
prevent the guest from setting VMXE when nVMX is not allowed.

Sean Christopherson (6):
  KVM: VMX: Drop guest CPUID check for VMXE in vmx_set_cr4()
  KVM: VMX: Drop explicit 'nested' check from vmx_set_cr4()
  KVM: SVM: Drop VMXE check from svm_set_cr4()
  KVM: x86: Move vendor CR4 validity check to dedicated kvm_x86_ops hook
  KVM: x86: Return bool instead of int for CR4 and SREGS validity checks
  KVM: selftests: Verify supported CR4 bits can be set before
    KVM_SET_CPUID2

 arch/x86/include/asm/kvm_host.h               |  3 +-
 arch/x86/kvm/svm/nested.c                     |  2 +-
 arch/x86/kvm/svm/svm.c                        | 12 ++-
 arch/x86/kvm/svm/svm.h                        |  2 +-
 arch/x86/kvm/vmx/nested.c                     |  2 +-
 arch/x86/kvm/vmx/vmx.c                        | 35 +++----
 arch/x86/kvm/vmx/vmx.h                        |  2 +-
 arch/x86/kvm/x86.c                            | 28 +++---
 arch/x86/kvm/x86.h                            |  2 +-
 .../selftests/kvm/include/x86_64/processor.h  | 17 ++++
 .../selftests/kvm/include/x86_64/vmx.h        |  4 -
 .../selftests/kvm/x86_64/set_sregs_test.c     | 92 ++++++++++++++++++-
 12 files changed, 153 insertions(+), 48 deletions(-)
```
#### [PATCH 0/5] Fix x2apic enablement and allow up to 32768 CPUs
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Wed Oct  7 12:20:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11820533
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BDC27618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 12:20:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 92FE920789
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 12:20:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="x/d2uFk8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728166AbgJGMUZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 08:20:25 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39834 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727927AbgJGMUZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Oct 2020 08:20:25 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CBA16C061755;
        Wed,  7 Oct 2020 05:20:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:Date:Cc:To:
        From:Subject:Message-ID:Sender:Reply-To:Content-Transfer-Encoding:Content-ID:
        Content-Description:In-Reply-To:References;
        bh=QVdD3TQ2H6lJ3p8rHm4Fp9Y1icR9/VihX18vHOISEEM=;
 b=x/d2uFk8Hy5K8rV8FK5BCbfmK4
        P/DG5WBcs5qbI0hOmIASOKELpBbPskWT0Gw+jopgoRvPaMAmdjMq4NWk+8nOSqmBeYt1COIEFtiMH
        pxf4u+e0klNXyoSBB3nzz7zp786+GIvi+XYK+OPNgs9oDZobWN5CdnQvQe9bj/laKopPCyuIkE8wH
        Wu6h2GiMBFn5M3BEe2rblqeRI3V7EsaWkYqOkKOdIF68SsM2rXQOJY9sum/WQwLthnN89a0Si1/Px
        c45Cl552vYxCzmVDLj6N1QwW+xFmiNwarpbo2/BguoAtorxV0Ai2zUab1GJAZ/fEAXpMW6FPy382R
        F3D8B6eg==;
Received: from [54.239.6.187] (helo=freeip.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kQ8Qg-0007ya-Mo; Wed, 07 Oct 2020 12:20:22 +0000
Message-ID: <803bb6b2212e65c568c84ff6882c2aa8a0ee03d5.camel@infradead.org>
Subject: [PATCH 0/5] Fix x2apic enablement and allow up to 32768 CPUs
 without IR where supported
From: David Woodhouse <dwmw2@infradead.org>
To: x86 <x86@kernel.org>
Cc: kvm <kvm@vger.kernel.org>, Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel <linux-kernel@vger.kernel.org>
Date: Wed, 07 Oct 2020 13:20:20 +0100
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Splitting out the simpler parts of my previous patch set. The full
support for per-irqdomain affinity limits will take a bit more work but
this part is quite simple.

Since we don't yet have per-irqdomain affinity, we currently attempt to
avoid bringing CPUs online at all if they can't be targeted by external
interrupts. Except we still let them get hotplugged later... which is
moderately suboptimal.

Fix that, and support the hypervisor enlightenment which at least
extends the range of targetable APIC IDs to 15 bits, as seen in the
patch at https://patchwork.kernel.org/patch/11816693/ for qemu.


David Woodhouse (5):
      x86/apic: Fix x2apic enablement without interrupt remapping
      x86/msi: Only use high bits of MSI address for DMAR unit
      x86/ioapic: Handle Extended Destination ID field in RTE
      x86/apic: Support 15 bits of APIC ID in IOAPIC/MSI where available
      x86/kvm: Add KVM_FEATURE_MSI_EXT_DEST_ID

 Documentation/virt/kvm/cpuid.rst     |  4 ++++
 arch/x86/include/asm/apic.h          |  1 +
 arch/x86/include/asm/io_apic.h       |  3 ++-
 arch/x86/include/asm/mpspec.h        |  1 +
 arch/x86/include/asm/x86_init.h      |  2 ++
 arch/x86/include/uapi/asm/kvm_para.h |  1 +
 arch/x86/kernel/apic/apic.c          | 27 +++++++++++++++++++++------
 arch/x86/kernel/apic/io_apic.c       | 19 +++++++++++++------
 arch/x86/kernel/apic/msi.c           | 41 +++++++++++++++++++++++++++++++++++------
 arch/x86/kernel/apic/x2apic_phys.c   |  9 +++++++++
 arch/x86/kernel/kvm.c                |  6 ++++++
 arch/x86/kernel/x86_init.c           |  1 +
 12 files changed, 96 insertions(+), 19 deletions(-)
```
#### [PATCH 00/13] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Wed Oct  7 16:44:13 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11821217
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB85314D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 16:46:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 83F30206FC
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 16:46:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="LKBDOiNh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727954AbgJGQqW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 12:46:22 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52672 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727958AbgJGQof (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 7 Oct 2020 12:44:35 -0400
Received: from mail-wr1-x444.google.com (mail-wr1-x444.google.com
 [IPv6:2a00:1450:4864:20::444])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 53AD4C0613D5
        for <kvm@vger.kernel.org>; Wed,  7 Oct 2020 09:44:34 -0700 (PDT)
Received: by mail-wr1-x444.google.com with SMTP id e18so2963963wrw.9
        for <kvm@vger.kernel.org>; Wed, 07 Oct 2020 09:44:34 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ioe0Byeg/DIJ2PK+KoHAeY/RgUBhGUsvQd2LPXMyjpk=;
        b=LKBDOiNhqwNLkwa9WP1zzXHrjwlM9UxdR+2aww5WQtbHhuceIwa/VXYYnC9UZ6hdtp
         mvYMFJ7UpZJyZnXE8eOz53fPGIesR/n7+X+8Z0F7CtzFKuDxeUJ2E389J/P0gE5voMHe
         oEJ9yMHSIcqvjSDbm4eT0/N3ZkXflXq1Fg4A8=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=ioe0Byeg/DIJ2PK+KoHAeY/RgUBhGUsvQd2LPXMyjpk=;
        b=FLxrZ7R+INh3Kl+VHhbDxkH0a46yy/kW44WmcOVo9UUZs3AwOkc62Oqh5VZpbZQ+fQ
         ZS9zTluPBlF+q4YGfuug4DOfPNizY+ObOzMmP2ANQvQTmWuIvHsTUBt+/6ySRfmzB5S7
         gYdq4BiX7g82vwRdGV7+/aP0MyjOAwZ6l8pUN+9xxs6Jq+RHRq/Hor0ZMpvbLhzupAmW
         i75kW2afdeQF76/GIYsJxpj+E8Bo21DjTJFmU6AKup6rVzzb3f5BIE1aM8Dh0zDAoBwv
         SYLdF5dAiVkT0dKxu446UaDI/y/CaIVoxsjaOyyob3Jmh297iwP7x38kuJ5qTPQOBqPp
         p7sA==
X-Gm-Message-State: AOAM533ZYG9x/QyISdoRKME4GEgp/HJGxTUbtENc/ylpW1Z9XVkVslaP
        /QT6eKXG4wL3YsSGMIAegs7rqeXqxBRdLy0y
X-Google-Smtp-Source: 
 ABdhPJzRELPHTJISw4N/fSU+gR/P4h8ZIocAzvLavw2ceiWiegfiQvvhsxcd+sZUYD7qwXN8jRsOdg==
X-Received: by 2002:adf:e74d:: with SMTP id c13mr4372958wrn.45.1602089072696;
        Wed, 07 Oct 2020 09:44:32 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 z191sm3332280wme.40.2020.10.07.09.44.31
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 07 Oct 2020 09:44:32 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        linux-s390@vger.kernel.org, Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH 00/13] follow_pfn and other iomap races
Date: Wed,  7 Oct 2020 18:44:13 +0200
Message-Id: <20201007164426.1812530-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

This developed from a discussion with Jason, starting with some patches
touching get_vaddr_frame that I typed up.

The problem is that way back VM_IO | VM_PFNMAP mappings were pretty
static, and so just following the ptes to derive a pfn and then use that
somewhere else was ok.

But we're no longer in such a world, there's tons of little races and some
fundamental problems.

This series here is an attempt to at least scope the problem, it's all the
issues I've found with quite some code reading all over the tree:
- first part tries to move mm/frame-vector.c away, it's fundamentally an
  unsafe thing
- two patches to close follow_pfn races by holding pt locks
- two pci patches where I spotted inconsinstencies between the 3 different
  ways userspace can map pci bars
- and finally some patches to mark up the remaining issue

No testing beyond "it compiles", this is very much an rfc to figure out
whether this makes sense, whether it's a real thing, and how to fix this
up properly.

Cheers, Daniel

Daniel Vetter (13):
  drm/exynos: Stop using frame_vector helpers
  drm/exynos: Use FOLL_LONGTERM for g2d cmdlists
  misc/habana: Stop using frame_vector helpers
  misc/habana: Use FOLL_LONGTERM for userptr
  mm/frame-vector: Use FOLL_LONGTERM
  media: videobuf2: Move frame_vector into media subsystem
  mm: close race in generic_access_phys
  s390/pci: Remove races against pte updates
  PCI: obey iomem restrictions for procfs mmap
  PCI: revoke mappings like devmem
  mm: add unsafe_follow_pfn
  media/videbuf1|2: Mark follow_pfn usage as unsafe
  vfio/type1: Mark follow_pfn as unsafe

 arch/s390/pci/pci_mmio.c                      | 98 +++++++++++--------
 drivers/char/mem.c                            | 16 ++-
 drivers/gpu/drm/exynos/Kconfig                |  1 -
 drivers/gpu/drm/exynos/exynos_drm_g2d.c       | 49 +++++-----
 drivers/media/common/videobuf2/Kconfig        |  1 -
 drivers/media/common/videobuf2/Makefile       |  1 +
 .../media/common/videobuf2}/frame_vector.c    | 40 +++-----
 drivers/media/platform/omap/Kconfig           |  1 -
 drivers/media/v4l2-core/videobuf-dma-contig.c |  2 +-
 drivers/misc/habanalabs/Kconfig               |  1 -
 drivers/misc/habanalabs/common/habanalabs.h   |  3 +-
 drivers/misc/habanalabs/common/memory.c       | 52 +++++-----
 drivers/pci/mmap.c                            |  3 +
 drivers/pci/proc.c                            |  5 +
 drivers/vfio/vfio_iommu_type1.c               |  4 +-
 include/linux/ioport.h                        |  2 +
 include/linux/mm.h                            | 47 +--------
 include/media/videobuf2-core.h                | 42 ++++++++
 mm/Kconfig                                    |  3 -
 mm/Makefile                                   |  1 -
 mm/memory.c                                   | 76 +++++++++++++-
 mm/nommu.c                                    | 17 ++++
 security/Kconfig                              | 13 +++
 23 files changed, 296 insertions(+), 182 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (90%)
```
#### [PATCH v3 0/5] Pass zPCI hardware information via VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Wed Oct  7 18:56:19 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11821611
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BB3F714D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 18:57:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9457E2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 18:57:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Z4+CNaEL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728188AbgJGS4d (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 14:56:33 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:31178 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726111AbgJGS4d (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 14:56:33 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 097IaMXY111478;
        Wed, 7 Oct 2020 14:56:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=ZY+GQVC1bcC8uF8DszSKcv11bWaq3iF8ovZZYd4c/1k=;
 b=Z4+CNaELJnrE3QdNA9Bbsvqoi9RbeTuuyW77Yk8w3LfElqjmbzxGMP/0181EnnRvAHa4
 /QI1HX+KtcMZTEmR2RUfRoCKSDmoD0XEZZ3H6Foqk8Lb3N/d/rjPm9uyKDX4ExLG0oI3
 ya3ctFLY/bCLQOfyS66xInXhPG7JqFIau1gwRVmW+BvF5lqzI513J0ATJXYhmkNHX/iD
 /pubC9Yt8vgIzk89ZkcGxIOus8eeh61TTOik+kBKTQpCntDmLGEzFs2WInGdmXxBJYJP
 j41VXEXNq331t8x5XRxkiEuGZtkkwYDye50HJAIUmoqv1oUi4jHKT9XU+G2m66ND0qjl 8w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341jehsp3w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 14:56:32 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 097IaZoN112746;
        Wed, 7 Oct 2020 14:56:31 -0400
Received: from ppma05wdc.us.ibm.com (1b.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.27])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341jehsp3m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 14:56:31 -0400
Received: from pps.filterd (ppma05wdc.us.ibm.com [127.0.0.1])
        by ppma05wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 097IkcDp014993;
        Wed, 7 Oct 2020 18:56:31 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma05wdc.us.ibm.com with ESMTP id 33xgx999cr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 18:56:31 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 097IuL5d58786116
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 7 Oct 2020 18:56:21 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D452A78060;
        Wed,  7 Oct 2020 18:56:27 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B666F78064;
        Wed,  7 Oct 2020 18:56:26 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.60.106])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Wed,  7 Oct 2020 18:56:26 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/5] Pass zPCI hardware information via VFIO
Date: Wed,  7 Oct 2020 14:56:19 -0400
Message-Id: <1602096984-13703-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-07_10:2020-10-07,2020-10-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 malwarescore=0
 mlxlogscore=986 impostorscore=0 spamscore=0 mlxscore=0 priorityscore=1501
 lowpriorityscore=0 suspectscore=0 adultscore=0 phishscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010070116
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset provides a means by which hardware information about the
underlying PCI device can be passed up to userspace (ie, QEMU) so that
this hardware information can be used rather than previously hard-coded
assumptions. The VFIO_DEVICE_GET_INFO ioctl is extended to allow capability
chains and zPCI devices provide the hardware information via capabilities.

A form of these patches saw some rounds last year but has been back-
tabled for a while.  The original work for this feature was done by Pierre
Morel. I'd like to refresh the discussion on this and get this finished up
so that we can move forward with better-supporting additional types of
PCI-attached devices.  

This feature is toggled via the CONFIG_VFIO_PCI_ZDEV configuration entry. 

Changes since v2:
- Added ACKs (thanks!)
- Patch 3+4: Re-write to use VFIO_DEVICE_GET_INFO capabilities rather than
  a vfio device region.

Matthew Rosato (5):
  s390/pci: stash version in the zpci_dev
  s390/pci: track whether util_str is valid in the zpci_dev
  vfio: Introduce capability definitions for VFIO_DEVICE_GET_INFO
  vfio-pci/zdev: Add zPCI capabilities to VFIO_DEVICE_GET_INFO
  MAINTAINERS: Add entry for s390 vfio-pci

 MAINTAINERS                         |   8 ++
 arch/s390/include/asm/pci.h         |   4 +-
 arch/s390/pci/pci_clp.c             |   2 +
 drivers/vfio/pci/Kconfig            |  13 ++++
 drivers/vfio/pci/Makefile           |   1 +
 drivers/vfio/pci/vfio_pci.c         |  37 ++++++++++
 drivers/vfio/pci/vfio_pci_private.h |  12 +++
 drivers/vfio/pci/vfio_pci_zdev.c    | 143 ++++++++++++++++++++++++++++++++++++
 include/uapi/linux/vfio.h           |  11 +++
 include/uapi/linux/vfio_zdev.h      |  78 ++++++++++++++++++++
 10 files changed, 308 insertions(+), 1 deletion(-)
 create mode 100644 drivers/vfio/pci/vfio_pci_zdev.c
 create mode 100644 include/uapi/linux/vfio_zdev.h
```
#### [PATCH v3 00/10] Retrieve zPCI hardware information from VFIO
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
From patchwork Wed Oct  7 19:04:05 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11821621
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F34BF109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 19:04:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA5012173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 19:04:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="gMBl5qJt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728111AbgJGTEe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 15:04:34 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:48636 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727463AbgJGTEe (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 15:04:34 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 097J2fIA010981;
        Wed, 7 Oct 2020 15:04:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=pp1;
 bh=UOaDIPUYd9d53EGnjMoc+nuXYhpqeBpClS36ypy/+fw=;
 b=gMBl5qJt2Ds3APOZasJVONoTVGQLqmlRLIlVRE3GluZuINe0PIn29VOPfpX+MMXTL+Vr
 QN1HcpEY+XRsVQBA35CfbAjYIDuH+6CLE50V/r6Sh/j+L6XSzHDxUaA0GXpfRH4kmCzq
 2QNtgaLBteMj7b8KgfjvjySiiEqaAN90troGiUpwHuSuiHrtbdmHzpekFXdc2Lj5FBoq
 vRaEo4UqAue3x3A0W96WbvhiQdeTbYno8+962UqiHSWyqkiHtff9ns46HT7SUmL7q9ax
 lT/U0CpyurVovF4xQ9p9r0yh9jalhOKUvTuERbAT4o/lW8Xgu0G3alLh4JZHmMDD5CKn VQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341k938be1-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 15:04:21 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 097J3QdM014045;
        Wed, 7 Oct 2020 15:04:21 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0b-001b2d01.pphosted.com with ESMTP id 341k938bdp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 15:04:21 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 097IkpgP005207;
        Wed, 7 Oct 2020 19:04:20 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma01wdc.us.ibm.com with ESMTP id 33xgx99a45-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 07 Oct 2020 19:04:20 +0000
Received: from b01ledav006.gho.pok.ibm.com (b01ledav006.gho.pok.ibm.com
 [9.57.199.111])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 097J4Jcb52232498
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 7 Oct 2020 19:04:20 GMT
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DB2C7AC060;
        Wed,  7 Oct 2020 19:04:19 +0000 (GMT)
Received: from b01ledav006.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B99F3AC05B;
        Wed,  7 Oct 2020 19:04:17 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.60.106])
        by b01ledav006.gho.pok.ibm.com (Postfix) with ESMTP;
        Wed,  7 Oct 2020 19:04:17 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v3 00/10] Retrieve zPCI hardware information from VFIO
Date: Wed,  7 Oct 2020 15:04:05 -0400
Message-Id: <1602097455-15658-1-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-07_10:2020-10-07,2020-10-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 mlxlogscore=999
 lowpriorityscore=0 bulkscore=0 clxscore=1015 malwarescore=0 suspectscore=0
 impostorscore=0 adultscore=0 priorityscore=1501 spamscore=0 phishscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010070118
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset adds code to s390 pci to examine the VFIO_DEVICE_GET_INFO 
capability chain, looking for capabilities that describe the underlying
hardware and features of the passed-through device.

The retrieval of this information is done once per function (and for a
subset of data, once per function group) and is performed at time of device
plug.  Some elements provided via the capability chain must still be forced
to default values for now to reflect what QEMU actually provides support
for.

The original work for this feature was done by Pierre Morel.

Associated kernel patchset:
https://lkml.org/lkml/2020/10/7/813

Tested using a host kernel with/without the VFIO_DEVICE_GET_INFO changes
and a QEMU with/without the VFIO_DEVICE_GET_INFO changes to validate
VFIO_DEVICE_GET_INFO remains backwards-compatible.


Changes since v2:
- Added ACKs/RBs (thanks!)
- Squashed the first 2 patches, and tried again using by formatting the 
  set with --find-renames / diff.renames.  (Thanks Richard and Paolo!)
  As before, this first patch can be applied separately but is included
  here for the sake of simplicity.
- Copied patch 'vfio: Create shared routine for scanning info capabilities'
  from the 'Accomodate vfio DMA limiting' set, as it's now needed here too.
  We can drop it from this set later once the former is applied.
- Refresh the linux-header placeholder.  Manually omit the qatomic->atomic
  pvrdma revert for now.
- New patch to add a helper function for finding VFIO_DEVICE_GET_INFO
  capabilities.  Depends on 'vfio: Create shared routine for scanning info
  capabilities'
- re-write the last patch to use VFIO_DEVICE_GET_INFO capabilities instead
  of a vfio device region

Matthew Rosato (7):
  s390x/pci: Move header files to include/hw/s390x
  vfio: Create shared routine for scanning info capabilities
  update-linux-headers: Add vfio_zdev.h
  linux-headers: update against 5.9-rc8
  s390x/pci: clean up s390 PCI groups
  vfio: Add routine for finding VFIO_DEVICE_GET_INFO capabilities
  s390x/pci: get zPCI function info from host

Pierre Morel (3):
  s390x/pci: create a header dedicated to PCI CLP
  s390x/pci: use a PCI Group structure
  s390x/pci: use a PCI Function structure

 MAINTAINERS                                        |   1 +
 hw/s390x/meson.build                               |   1 +
 hw/s390x/s390-pci-bus.c                            |  86 ++++++++-
 hw/s390x/s390-pci-inst.c                           |  33 ++--
 hw/s390x/s390-pci-vfio.c                           | 197 +++++++++++++++++++++
 hw/s390x/s390-virtio-ccw.c                         |   2 +-
 hw/vfio/common.c                                   |  31 +++-
 {hw => include/hw}/s390x/s390-pci-bus.h            |  13 ++
 .../hw/s390x/s390-pci-clp.h                        | 123 ++-----------
 include/hw/s390x/s390-pci-inst.h                   | 116 ++++++++++++
 include/hw/s390x/s390-pci-vfio.h                   |  19 ++
 include/hw/vfio/vfio-common.h                      |   2 +
 linux-headers/linux/kvm.h                          |   6 +-
 linux-headers/linux/vfio.h                         |  11 ++
 linux-headers/linux/vfio_zdev.h                    |  78 ++++++++
 scripts/update-linux-headers.sh                    |   2 +-
 16 files changed, 575 insertions(+), 146 deletions(-)
 create mode 100644 hw/s390x/s390-pci-vfio.c
 rename {hw => include/hw}/s390x/s390-pci-bus.h (96%)
 rename hw/s390x/s390-pci-inst.h => include/hw/s390x/s390-pci-clp.h (59%)
 create mode 100644 include/hw/s390x/s390-pci-inst.h
 create mode 100644 include/hw/s390x/s390-pci-vfio.h
 create mode 100644 linux-headers/linux/vfio_zdev.h
```
#### [PATCH v14 00/14] KVM: Dirty ring interface
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Wed Oct  7 20:53:28 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11821747
Return-Path: <SRS0=rZqs=DO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC8696CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 20:53:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7E9FB2083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  7 Oct 2020 20:53:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Utc6HGy0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728358AbgJGUxv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 7 Oct 2020 16:53:51 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:58606 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728258AbgJGUxu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 7 Oct 2020 16:53:50 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1602104028;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=k/g9AIU6SDlTST+2/p7pTvzGC7UsWFJgyzUTioBl12Q=;
        b=Utc6HGy0caH5NdeCnWesIVSlX6pGRrd0JMEW6xiubT5okYgAR4C4LXCsgXpJ77uttbTkyg
        5CyYnh3Gzc1fVRrNvV3BRS0kY5+EUAHTHmfyh9PRNb2M9r3QhUO76KA+gaZT2Gk+WtDbn2
        L0CfrAvth1MkhGxV6alSRpM5i7fOVYQ=
Received: from mail-qt1-f197.google.com (mail-qt1-f197.google.com
 [209.85.160.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-64-xDq4CYGVNE6zOCtpGqxMrQ-1; Wed, 07 Oct 2020 16:53:45 -0400
X-MC-Unique: xDq4CYGVNE6zOCtpGqxMrQ-1
Received: by mail-qt1-f197.google.com with SMTP id i8so2217872qtc.8
        for <kvm@vger.kernel.org>; Wed, 07 Oct 2020 13:53:45 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=k/g9AIU6SDlTST+2/p7pTvzGC7UsWFJgyzUTioBl12Q=;
        b=gSr0dPgdauwGOFefCtM86bJ4sSwl6fQJm9M1QdbPDve7gakC1X780WpCbYaVY9+A21
         7CrM9H+1xzjyerWthgI6c3LW85aujGgsHDirVj/cP3N80eqQidp8Wpy/sooociy9Niol
         XJfw5LETzIZDzM6dA0yJnyYjsef7xPYlAY5USd5OCxzpsfZgSrSqFm3t6SX/t64JTqOc
         pOV/AQWFceEz2nkwe2BMam9lW6fMmTwHf7BurCLCKWE0HEbIGFDOewItIQau4zV2okiH
         WN6yebLiRLz9X4FGaQsAHMHF98Oflwd0vBbLxoU2tYLBggMn1vDSJIVftEVQB1G52UNE
         cDvw==
X-Gm-Message-State: AOAM533eFy6UGctU6d/yyLHJfr3G9LTcricefD2kqu/zpLNLO1v8DhuS
        FvV6l+h6lykrDnixn15aLoWndeX2GOgK7lVS8XrDWBwZdr+pem/tqNuhCQdzb/Ih4fTaSPDdXYA
        bxP3UAUZEL68U
X-Received: by 2002:a05:620a:4084:: with SMTP id
 f4mr5297192qko.449.1602104024751;
        Wed, 07 Oct 2020 13:53:44 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwggmrQVX4PuVqXCy9WP48TRPFDgmVTNMsiIJ/tBunVCHTMruSimjxchw/T2K0qSfla6sCSCw==
X-Received: by 2002:a05:620a:4084:: with SMTP id
 f4mr5297174qko.449.1602104024408;
        Wed, 07 Oct 2020 13:53:44 -0700 (PDT)
Received: from xz-x1.redhat.com
 (toroon474qw-lp140-04-174-95-215-133.dsl.bell.ca. [174.95.215.133])
        by smtp.gmail.com with ESMTPSA id
 j24sm2390695qkg.107.2020.10.07.13.53.43
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 07 Oct 2020 13:53:43 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Andrew Jones <drjones@redhat.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>
Subject: [PATCH v14 00/14] KVM: Dirty ring interface
Date: Wed,  7 Oct 2020 16:53:28 -0400
Message-Id: <20201007205342.295402-1-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM branch:
  https://github.com/xzpeter/linux/tree/kvm-dirty-ring
  (applied one more patch there to fix kvm/queue break on msr filtering)

QEMU branch for testing:
  https://github.com/xzpeter/qemu/tree/kvm-dirty-ring

v14:
- fix a testcase race reported by kernel test robot.  More can be found at:
  https://lore.kernel.org/kvm/20201007204525.GF6026@xz-x1/

v13:
- rebase to kvm/queue rather than 5.9-rc7.  I think, kvm/queue is broken.  I
  can only test the dirty ring after I revert 3eb900173c71 ("KVM: x86: VMX:
  Prevent MSR passthrough when MSR access is denied", 2020-09-28), otherwise
  the guest will hang on vcpu0 looping forever during boot Linux.
- added another trivial patch "KVM: Documentation: Update entry for
  KVM_X86_SET_MSR_FILTER".  It should be squashed into 1a155254ff93 ("KVM: x86:
  Introduce MSR filtering", 2020-09-28) directly.

v12:
- add r-bs for Sean
- rebase

v11:
- rebased to kvm/queue (seems the newest)
- removed kvm_dirty_ring_waitqueue() tracepoint since not used
- set memslot->as_id in kvm_delete_memslot() [Sean]
- let __copy_to_user() always return -EFAULT [Sean]
- rename 'r' in alloc_apic_access_page into 'hva' [Sean]

For previous versions, please refer to:

V1: https://lore.kernel.org/kvm/20191129213505.18472-1-peterx@redhat.com
V2: https://lore.kernel.org/kvm/20191221014938.58831-1-peterx@redhat.com
V3: https://lore.kernel.org/kvm/20200109145729.32898-1-peterx@redhat.com
V4: https://lore.kernel.org/kvm/20200205025105.367213-1-peterx@redhat.com
V5: https://lore.kernel.org/kvm/20200304174947.69595-1-peterx@redhat.com
V6: https://lore.kernel.org/kvm/20200309214424.330363-1-peterx@redhat.com
V7: https://lore.kernel.org/kvm/20200318163720.93929-1-peterx@redhat.com
V8: https://lore.kernel.org/kvm/20200331190000.659614-1-peterx@redhat.com
V9: https://lore.kernel.org/kvm/20200523225659.1027044-1-peterx@redhat.com
V10: https://lore.kernel.org/kvm/20200601115957.1581250-1-peterx@redhat.com/

Overview
============

This is a continued work from Lei Cao <lei.cao@stratus.com> and Paolo
Bonzini on the KVM dirty ring interface.

The new dirty ring interface is another way to collect dirty pages for
the virtual machines. It is different from the existing dirty logging
interface in a few ways, majorly:

  - Data format: The dirty data was in a ring format rather than a
    bitmap format, so dirty bits to sync for dirty logging does not
    depend on the size of guest memory any more, but speed of
    dirtying.  Also, the dirty ring is per-vcpu, while the dirty
    bitmap is per-vm.

  - Data copy: The sync of dirty pages does not need data copy any more,
    but instead the ring is shared between the userspace and kernel by
    page sharings (mmap() on vcpu fd)

  - Interface: Instead of using the old KVM_GET_DIRTY_LOG,
    KVM_CLEAR_DIRTY_LOG interfaces, the new ring uses the new
    KVM_RESET_DIRTY_RINGS ioctl when we want to reset the collected
    dirty pages to protected mode again (works like
    KVM_CLEAR_DIRTY_LOG, but ring based).  To collecting dirty bits,
    we only need to read the ring data, no ioctl is needed.

Ring Layout
===========

KVM dirty ring is per-vcpu.  Each ring is an array of kvm_dirty_gfn
defined as:

struct kvm_dirty_gfn {
        __u32 flags;
        __u32 slot; /* as_id | slot_id */
        __u64 offset;
};

Each GFN is a state machine itself.  The state is embeded in the flags
field, as defined in the uapi header:

/*
 * KVM dirty GFN flags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (reset) | bit 0 (dirty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invalid GFN  |
 * |             0 |             1 | Dirty GFN    |
 * |             1 |             X | GFN to reset |
 * |---------------+---------------+--------------|
 *
 * Lifecycle of a dirty GFN goes like:
 *
 *      dirtied         collected        reset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The userspace program is only responsible for the 01->1X state
 * conversion (to collect dirty bits).  Also, it must not skip any
 * dirty bits so that dirty bits are always collected in sequence.
 */

Testing
=======

This series provided both the implementation of the KVM dirty ring and
the test case.  Also I've implemented the QEMU counterpart that can
run with the new KVM, link can be found at the top of the cover
letter.  However that's still a very initial version which is prone to
change and future optimizations.

I did some measurement with the new method with 24G guest running some
dirty workload, I don't see any speedup so far, even in some heavy
dirty load it'll be slower (e.g., when 800MB/s random dirty rate, kvm
dirty ring takes average of ~73s to complete migration while dirty
logging only needs average of ~55s).  However that's understandable
because 24G guest means only 1M dirty bitmap, that's still a suitable
case for dirty logging.  Meanwhile heavier workload means worst case
for dirty ring.

More tests are welcomed if there's bigger host/guest, especially on
COLO-like workload.

Please review, thanks.

Peter Xu (14):
  KVM: Documentation: Update entry for KVM_X86_SET_MSR_FILTER
  KVM: Cache as_id in kvm_memory_slot
  KVM: X86: Don't track dirty for KVM_SET_[TSS_ADDR|IDENTITY_MAP_ADDR]
  KVM: Pass in kvm pointer into mark_page_dirty_in_slot()
  KVM: X86: Implement ring-based dirty memory tracking
  KVM: Make dirty ring exclusive to dirty bitmap log
  KVM: Don't allocate dirty bitmap if dirty ring is enabled
  KVM: selftests: Always clear dirty bitmap after iteration
  KVM: selftests: Sync uapi/linux/kvm.h to tools/
  KVM: selftests: Use a single binary for dirty/clear log test
  KVM: selftests: Introduce after_vcpu_run hook for dirty log test
  KVM: selftests: Add dirty ring buffer test
  KVM: selftests: Let dirty_log_test async for dirty ring test
  KVM: selftests: Add "-c" parameter to dirty log test

 Documentation/virt/kvm/api.rst                | 126 ++++-
 arch/x86/include/asm/kvm_host.h               |   6 +-
 arch/x86/include/uapi/asm/kvm.h               |   1 +
 arch/x86/kvm/Makefile                         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  10 +-
 arch/x86/kvm/svm/avic.c                       |   9 +-
 arch/x86/kvm/vmx/vmx.c                        |  96 ++--
 arch/x86/kvm/x86.c                            |  46 +-
 include/linux/kvm_dirty_ring.h                | 103 ++++
 include/linux/kvm_host.h                      |  19 +
 include/trace/events/kvm.h                    |  63 +++
 include/uapi/linux/kvm.h                      |  53 ++
 tools/include/uapi/linux/kvm.h                |  77 ++-
 tools/testing/selftests/kvm/Makefile          |   2 -
 .../selftests/kvm/clear_dirty_log_test.c      |   6 -
 tools/testing/selftests/kvm/dirty_log_test.c  | 516 ++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  72 ++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   4 +
 virt/kvm/dirty_ring.c                         | 197 +++++++
 virt/kvm/kvm_main.c                           | 168 +++++-
 21 files changed, 1443 insertions(+), 138 deletions(-)
 create mode 100644 include/linux/kvm_dirty_ring.h
 delete mode 100644 tools/testing/selftests/kvm/clear_dirty_log_test.c
 create mode 100644 virt/kvm/dirty_ring.c
```
