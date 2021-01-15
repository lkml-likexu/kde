

#### [RFC PATCH v3 0/2] Add platform check for subdevice irq domain
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Thu Jan 14 01:30:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 12018099
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A11BDC43219
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:43:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6144C235F8
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:43:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727788AbhANBln (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 20:41:43 -0500
Received: from mga05.intel.com ([192.55.52.43]:51491 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727184AbhANBlm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 20:41:42 -0500
IronPort-SDR: 
 mH9n4n3hcY8emYU04IYSsu3z9oSu6hiCVzgmjJKqZT+cQUnS4eIITShvvN7cbsvhfm0W8NRKLO
 Vwvo/pr3A3bg==
X-IronPort-AV: E=McAfee;i="6000,8403,9863"; a="263084524"
X-IronPort-AV: E=Sophos;i="5.79,345,1602572400";
   d="scan'208";a="263084524"
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jan 2021 17:38:18 -0800
IronPort-SDR: 
 70ByEuj6ZUTxoobpwmM7DnqLWj+gPglSHAzdk1Zcl51BXOPdoBO9ptYytiJ7aJ9FshTQjUNI11
 332Cn7+I7AeA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,345,1602572400";
   d="scan'208";a="569582482"
Received: from allen-box.sh.intel.com ([10.239.159.28])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jan 2021 17:38:11 -0800
From: Lu Baolu <baolu.lu@linux.intel.com>
To: tglx@linutronix.de, ashok.raj@intel.com, kevin.tian@intel.com,
        dave.jiang@intel.com, megha.dey@intel.com, dwmw2@infradead.org
Cc: alex.williamson@redhat.com, bhelgaas@google.com,
        dan.j.williams@intel.com, will@kernel.org, joro@8bytes.org,
        dmaengine@vger.kernel.org, eric.auger@redhat.com,
        jacob.jun.pan@intel.com, jgg@mellanox.com, kvm@vger.kernel.org,
        kwankhede@nvidia.com, linux-kernel@vger.kernel.org,
        linux-pci@vger.kernel.org, iommu@lists.linux-foundation.org,
        maz@kernel.org, mona.hossain@intel.com, netanelg@mellanox.com,
        parav@mellanox.com, pbonzini@redhat.com, rafael@kernel.org,
        samuel.ortiz@intel.com, sanjay.k.kumar@intel.com,
        shahafs@mellanox.com, tony.luck@intel.com, vkoul@kernel.org,
        yan.y.zhao@linux.intel.com, yi.l.liu@intel.com, leon@kernel.org,
        Lu Baolu <baolu.lu@linux.intel.com>
Subject: [RFC PATCH v3 0/2] Add platform check for subdevice irq domain
Date: Thu, 14 Jan 2021 09:30:01 +0800
Message-Id: <20210114013003.297050-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

Learnt from the discussions in this thread:

https://lore.kernel.org/linux-pci/160408357912.912050.17005584526266191420.stgit@djiang5-desk3.ch.intel.com/

The device IMS (Interrupt Message Storage) should not be enabled in any
virtualization environments unless there is a HYPERCALL domain which
makes the changes in the message store monitored by the hypervisor.

As the initial step, we allow the IMS to be enabled only if we are
running on the bare metal. It's easy to enable IMS in the virtualization
environments if above preconditions are met in the future.

This series is only for comments purpose. We will include it in the Intel
IMS implementation later once we reach a consensus.

Change log:
v2->v3:
 - v2:
   https://lore.kernel.org/linux-pci/20210106022749.2769057-1-baolu.lu@linux.intel.com/
 - Add all identified heuristics so far.

v1->v2:
 - v1:
   https://lore.kernel.org/linux-pci/20201210004624.345282-1-baolu.lu@linux.intel.com/
 - Rename probably_on_bare_metal() with on_bare_metal();
 - Some vendors might use the same name for both bare metal and virtual
   environment. Before we add vendor specific code to distinguish
   between them, let's return false in on_bare_metal(). This won't
   introduce any regression. The only impact is that the coming new
   platform msi feature won't be supported until the vendor specific code
   is provided.

Best regards,
baolu

Lu Baolu (2):
  iommu: Add capability IOMMU_CAP_VIOMMU
  platform-msi: Add platform check for subdevice irq domain

 arch/x86/pci/common.c        | 71 ++++++++++++++++++++++++++++++++++++
 drivers/base/platform-msi.c  |  8 ++++
 drivers/iommu/intel/iommu.c  | 20 ++++++++++
 drivers/iommu/virtio-iommu.c |  9 +++++
 include/linux/iommu.h        |  1 +
 include/linux/msi.h          |  1 +
 6 files changed, 110 insertions(+)
```
#### [PATCH v2 00/14] KVM: SVM: Misc SEV cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu Jan 14 00:36:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12018161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 73B63C433E9
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:49:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 43B8B20776
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 01:49:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728506AbhANBs7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 20:48:59 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:55674 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729924AbhANAi0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Jan 2021 19:38:26 -0500
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 01078C061575
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 16:37:34 -0800 (PST)
Received: by mail-qt1-x849.google.com with SMTP id b24so2953748qtt.22
        for <kvm@vger.kernel.org>; Wed, 13 Jan 2021 16:37:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=M4LPvVO0tM+kRKTIgz3UZuoOLiPTa+F2++4IgfISsGU=;
        b=i7ZE3PF376aaxN+KR1fKdzuL+kCPx/rAU4BbsW6Zsv5hRh80qwO4OekpJ/Q3LNVd+S
         buGljMOzOYmqZJeNpGO+/eE7DBn0+kPAz0VC1jUNpCJzIfth1ks/WwaKXag+n4X0BTu2
         2+o6sUyFYRn/yMn6sLiKJyQy2zSUYTDdkE3MFN3HaP9mK8weIglwU1E0Ta6JTmU9Egod
         dMr1QOE5kLBhWsEfEVYzD/vLA/kexAyTOcKR48vd2e6V2pWr2aAqzj0pKDKaCO4f0neg
         zqYXqyA3VlpudbEv7MQi//44BASoZUlPGuRgBHj2eQs1UAwmRQ8GEk7uPJCbvanhHTQ0
         gKYw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=M4LPvVO0tM+kRKTIgz3UZuoOLiPTa+F2++4IgfISsGU=;
        b=CRAfSmgLlx7yan0QM/ted6suR64/QglWK0IcWdDxLcDvCFcjhZiWQa9w414uh/qBN8
         QPc2pzX0ZvQp5AYW9PMCYI1khIZGQ0KAV59rsl1aGHTZwMv8vp8vWCUHKzdJ14XTarCG
         rmrKbYGunoVFd2mS2DaC4G6EcxMqzfxgaJEVLokplWxdac7z9Zs0aNtx51dLJDAnkd4f
         49a2vZXcB31BWlJ8IIepL/lKAJV9JDlGrm/+ayWKAcEq/KJdGHaYiSXHrHr/njxoQ5T5
         DkotIb4abSkxaUTGgo6JCyeRQyoWuBLa7sX7RtPYqMfF2prVq6l+Zkb30yaQQ9BEEAAW
         2xCg==
X-Gm-Message-State: AOAM530IfAL6FoIN6wZQ014Ugb76sFQQuTqpG+bhtOJMk/bvWqH9VBvQ
        IKr8jme14FFWvO3K9nIKfIz8rp6wyLE=
X-Google-Smtp-Source: 
 ABdhPJwbERTz6kYhk+OHyi8G3KqDtkL7UYRk6F/n3LLIR83DuPSgMDOE973G2VwAgirc0O4J+unHa1FD5X0=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1ea0:b8ff:fe73:50f5])
 (user=seanjc job=sendgmr) by 2002:a25:1b05:: with SMTP id
 b5mr7077713ybb.298.1610584653170;
 Wed, 13 Jan 2021 16:37:33 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 13 Jan 2021 16:36:54 -0800
Message-Id: <20210114003708.3798992-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.284.gd98b1dd5eaa7-goog
Subject: [PATCH v2 00/14] KVM: SVM: Misc SEV cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Andy Lutomirski <luto@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Borislav Petkov <bp@suse.de>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Minor bug fixes and refactorings of SEV related code, mainly to clean up
the KVM code for tracking whether or not SEV and SEV-ES are enabled.  E.g.
KVM has both sev_es and svm_sev_enabled(), and a global 'sev' flag while
also using 'sev' as a local variable in several places.

Based on kvm/master, commit 872f36eb0b0f ("KVM: x86: __kvm_vcpu_halt can
be static").

v2:
 - Remove the kernel's sev_enabled instead of renaming it to sev_guest.
 - Fix various build issues. [Tom]
 - Remove stable tag from the patch to free sev_asid_bitmap.  Keeping the
   bitmap on failure is truly only a leak once svm_sev_enabled() is
   dropped later in the series.  It's still arguably a fix since KVM will
   unnecessarily keep memory, but it's not stable material. [Tom]
 - Collect one Ack. [Tom]

v1:
 - https://lkml.kernel.org/r/20210109004714.1341275-1-seanjc@google.com

Sean Christopherson (14):
  KVM: SVM: Zero out the VMCB array used to track SEV ASID association
  KVM: SVM: Free sev_asid_bitmap during init if SEV setup fails
  KVM: SVM: Move SEV module params/variables to sev.c
  x86/cpufeatures: Assign dedicated feature word for AMD mem encryption
  KVM: x86: Override reported SME/SEV feature flags with host mask
  x86/sev: Drop redundant and potentially misleading 'sev_enabled'
  KVM: SVM: Append "_enabled" to module-scoped SEV/SEV-ES control
    variables
  KVM: SVM: Condition sev_enabled and sev_es_enabled on
    CONFIG_KVM_AMD_SEV=y
  KVM: SVM: Unconditionally invoke sev_hardware_teardown()
  KVM: SVM: Explicitly check max SEV ASID during sev_hardware_setup()
  KVM: SVM: Move SEV VMCB tracking allocation to sev.c
  KVM: SVM: Drop redundant svm_sev_enabled() helper
  KVM: SVM: Remove an unnecessary prototype declaration of
    sev_flush_asids()
  KVM: SVM: Skip SEV cache flush if no ASIDs have been used

 arch/x86/include/asm/cpufeature.h             |  7 +-
 arch/x86/include/asm/cpufeatures.h            | 17 +++--
 arch/x86/include/asm/disabled-features.h      |  3 +-
 arch/x86/include/asm/mem_encrypt.h            |  1 -
 arch/x86/include/asm/required-features.h      |  3 +-
 arch/x86/kernel/cpu/common.c                  |  3 +
 arch/x86/kernel/cpu/scattered.c               |  5 --
 arch/x86/kvm/cpuid.c                          |  2 +
 arch/x86/kvm/cpuid.h                          |  1 +
 arch/x86/kvm/svm/sev.c                        | 71 +++++++++++++------
 arch/x86/kvm/svm/svm.c                        | 35 +++------
 arch/x86/kvm/svm/svm.h                        |  8 +--
 arch/x86/mm/mem_encrypt.c                     | 12 ++--
 arch/x86/mm/mem_encrypt_identity.c            |  1 -
 .../arch/x86/include/asm/disabled-features.h  |  3 +-
 .../arch/x86/include/asm/required-features.h  |  3 +-
 16 files changed, 96 insertions(+), 79 deletions(-)
```
#### [PATCH 00/10] Fix documentation warnings at linux-next
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Thu Jan 14 07:53:35 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12018779
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1163AC433E9
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 07:54:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA5E6208E4
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 07:54:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727552AbhANHyc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 02:54:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:56658 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726819AbhANHyb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 02:54:31 -0500
Received: by mail.kernel.org (Postfix) with ESMTPSA id D4C4C239EF;
        Thu, 14 Jan 2021 07:53:49 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1610610830;
        bh=BXt2olIMSsLtD8I2dioNC1dF1gnxlCbQs+WN6FCb4nE=;
        h=From:To:Cc:Subject:Date:From;
        b=s0XxntmYYJHZOMEV2ezXMlavrLQamHOON6XCuxktQJvVAECs99C5z/1aJ9vJhpL8u
         ooeeAl2QTMZNzf+wMfEpKpWg40tk1M0qnksP48Wj5LotBytvL5l6d4s7r5DnGwrSaG
         EH99zAztLa1B6MMeto4xMR8BJQ0ZLi5vAvwqfqQhhWEPmUUPibd3hUMclqtKjDn9OB
         Utpv0Ju4+AOG0dmdSki7FZM9GtjIWxV8jruDU/sDouAY8GwvD2n2HBSlFqfv/WWpXP
         DJr7Fq0cZK3daZV+WRhSNlCFNyWFUZ+j72ACR35krQCcJ9iaizMmnvIhYttJJ/HyQS
         YKU4ctJMp8S5g==
Received: by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1kzxRz-00EPu1-2O; Thu, 14 Jan 2021 08:53:47 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Chao Yu <chao@kernel.org>, Daniel Vetter <daniel@ffwll.ch>,
        David Airlie <airlied@linux.ie>,
        Felipe Balbi <balbi@kernel.org>,
        Harry Wei <harryxiyou@gmail.com>,
        Ingo Molnar <mingo@redhat.com>,
        Jaegeuk Kim <jaegeuk@kernel.org>,
        Mauro Carvalho Chehab <mchehab@kernel.org>,
        Moritz Fischer <mdf@kernel.org>,
        Peter Zijlstra <peterz@infradead.org>,
        Tom Rix <trix@redhat.com>, Will Deacon <will@kernel.org>,
        Wu Hao <hao.wu@intel.com>, amd-gfx@lists.freedesktop.org,
        dri-devel@lists.freedesktop.org, kvm@vger.kernel.org,
        linux-f2fs-devel@lists.sourceforge.net, linux-fpga@vger.kernel.org,
        linux-media@vger.kernel.org, linux-usb@vger.kernel.org
Subject: [PATCH 00/10] Fix documentation warnings at linux-next
Date: Thu, 14 Jan 2021 08:53:35 +0100
Message-Id: <cover.1610610444.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series fixes the documentation warnings found at next-20210114.

Most of the changes here are trivial. 

While those patches could be merged via the docs tree during
the next merge window, It sounds better to have those patches 
merged directly via each maintainer's tree, where the new
warnings were introduced.

Regards,
Mauro

Mauro Carvalho Chehab (10):
  doc/zh_CN: fix Sphinx errors
  ABI: sysfs-fs-f2fs: fix a table identation
  KVM: x86: hyper-v: add a blank line to remove building warnings
  ABI: sysfs-firmware-sgi_uv
  docs: fpga: dfl.rst: Fix a couple building issues
  drm: amd: amdgpu_dm.h: fix a wrong kernel-doc markup
  dwc3: document gadget_max_speed
  doc: zh_CN/mips: fix doc cross-references
  media: v4l2-subdev.rst: fix a missing whitespace
  seqlock: kernel-doc: fix a prototype

 Documentation/ABI/testing/sysfs-firmware-sgi_uv       | 1 +
 Documentation/ABI/testing/sysfs-fs-f2fs               | 3 ++-
 Documentation/driver-api/media/v4l2-subdev.rst        | 2 +-
 Documentation/fpga/dfl.rst                            | 4 ++--
 Documentation/translations/zh_CN/mips/booting.rst     | 2 +-
 Documentation/translations/zh_CN/mips/features.rst    | 2 +-
 Documentation/translations/zh_CN/mips/index.rst       | 2 +-
 Documentation/translations/zh_CN/mips/ingenic-tcu.rst | 6 +++---
 Documentation/virt/kvm/api.rst                        | 1 +
 drivers/gpu/drm/amd/display/amdgpu_dm/amdgpu_dm.h     | 2 +-
 drivers/usb/dwc3/core.h                               | 1 +
 include/linux/seqlock.h                               | 2 +-
 12 files changed, 16 insertions(+), 12 deletions(-)
```
#### [PATCH v2 0/9] KVM/ARM: Some vgic fixes and init sequence KVM
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Thu Jan 14 10:36:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Auger Eric <eric.auger@redhat.com>
X-Patchwork-Id: 12019179
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7F670C4332D
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:41:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 52D9D23A50
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:41:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727762AbhANKir (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 05:38:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:42495 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727431AbhANKip (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Jan 2021 05:38:45 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610620640;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=HoKabFZExfQoqXWLgrTNIdYwFwDTVzFUWj3mj+mPnlI=;
        b=S8u32H0m+TOumlD8vnciw8y8wzmDZxZd2sljQOnlT3n+3aTfSd0HYYIMlvQQ+3n/LPvI5D
        07f/Lpb92Ckv0zTGsmLKh19JimxqTPwyt/MWz0MmgqNpdkKZOqgHY5VGSjLHZAdQTosD6G
        /mg/CTFf4RugOXpRI6WiIML0yeL4ezU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-179-o-aRXnmkOWeaGKvKExWNCQ-1; Thu, 14 Jan 2021 05:37:18 -0500
X-MC-Unique: o-aRXnmkOWeaGKvKExWNCQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 8A96A1009446;
        Thu, 14 Jan 2021 10:37:16 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-114-165.ams2.redhat.com
 [10.36.114.165])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7DBCF12D7E;
        Thu, 14 Jan 2021 10:37:10 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com
Cc: alexandru.elisei@arm.com, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH v2 0/9] KVM/ARM: Some vgic fixes and init sequence KVM
 selftests
Date: Thu, 14 Jan 2021 11:36:59 +0100
Message-Id: <20210114103708.26763-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While writting vgic v3 init sequence KVM selftests I noticed some
relatively minor issues. This was also the opportunity to try to
fix the issue laterly reported by Zenghui, related to the RDIST_TYPER
last bit emulation. The final patch is a first batch of VGIC init
sequence selftests. Of course they can be augmented with a lot more
register access tests, but let's try to move forward incrementally ...

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/vgic_kvmselftests_v2

History:
- Took into account all comments from Marc and Alexandru's except
  the has_run_once still after the map_resources (this would oblige
  me to revisit in depth the selftests)

Eric Auger (9):
  KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
  KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
  KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
  KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
  KVM: arm: move has_run_once after the map_resources
  docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
  KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
  KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
  KVM: selftests: aarch64/vgic-v3 init sequence tests

 .../virt/kvm/devices/arm-vgic-v3.rst          |   2 +-
 arch/arm64/kvm/arm.c                          |   4 +-
 arch/arm64/kvm/vgic/vgic-init.c               |   6 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   3 +
 arch/arm64/kvm/vgic/vgic-mmio-v3.c            |  30 +-
 arch/arm64/kvm/vgic/vgic-mmio.c               |  10 +-
 include/kvm/arm_vgic.h                        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/aarch64/vgic_init.c | 453 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   5 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  51 ++
 11 files changed, 546 insertions(+), 20 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/vgic_init.c
```
#### [PATCH 0/6] KVM: arm64: More PMU/debug ID register fixes
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Thu Jan 14 10:56:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12019227
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8251AC433E0
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:57:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2991F239CF
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 10:57:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726422AbhANK5c (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 05:57:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:37122 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725954AbhANK5b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 05:57:31 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 136B5239CF;
        Thu, 14 Jan 2021 10:56:51 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l00J6-007Tvz-TM; Thu, 14 Jan 2021 10:56:49 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com
Subject: [PATCH 0/6] KVM: arm64: More PMU/debug ID register fixes
Date: Thu, 14 Jan 2021 10:56:27 +0000
Message-Id: <20210114105633.2558739-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a respin of a series I posted in the 5.7 time frame, and
completely forgot about it until I noticed again that a few things
where not what I remembered... Given how long it has been, I'm
pretending this is v1 again.

Anyway, this covers a few gaps in our ID register handling for PMU and
Debug, plus the upgrade of the PMU support to 8.4 when possible.

I don't plan to take this into 5.11, but this is a likely candidate
for 5.12.

Marc Zyngier (6):
  KVM: arm64: Fix missing RES1 in emulation of DBGBIDR
  KVM: arm64: Fix AArch32 PMUv3 capping
  KVM: arm64: Add handling of AArch32 PCMEID{2,3} PMUv3 registers
  KVM: arm64: Refactor filtering of ID registers
  KVM: arm64: Limit the debug architecture to ARMv8.0
  KVM: arm64: Upgrade PMU support to ARMv8.4

 arch/arm64/kvm/sys_regs.c | 75 +++++++++++++++++++++++----------------
 1 file changed, 45 insertions(+), 30 deletions(-)
```
#### [PATCH v3 0/3] Some optimization for stage-2 translation
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Thu Jan 14 12:13:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12019391
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D424EC4332E
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:15:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA2742376E
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 12:15:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729001AbhANMOr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 07:14:47 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:11386 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727202AbhANMOq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 14 Jan 2021 07:14:46 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DGjrD4zP5z7VFy;
        Thu, 14 Jan 2021 20:13:00 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Thu, 14 Jan 2021 20:13:52 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v3 0/3] Some optimization for stage-2 translation
Date: Thu, 14 Jan 2021 20:13:47 +0800
Message-ID: <20210114121350.123684-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This patch series(v3) make some optimization for stage-2 translation.

About patch-1:
Procedures of hyp stage-1 map and guest stage-2 map are quite different,
but they are now tied closely by function kvm_set_valid_leaf_pte().
So adjust the relative code for ease of code maintenance in the future.

About patch-2:
There have been the separate map handler and perms handler used independently
for mapping and relaxing permissions in the new page-table infrastructure for
stage-2, yet there is still a specific case where we end up changing the access
permissions in the map path, and something unsatisfactory could happen because
of current handling for this case.

To solve above problem, we can filter out this case from the map path and abort
the PTE update. Instead, let the vCPU enter back the guest and it will exit next
time to go through the relax_perms path if still needed.

About patch-3:
We now set the pfn dirty and mark the page dirty before calling fault
handlers in user_mem_abort(), so we might end up having spurious dirty
pages if update of permissions or mapping has failed. Let's move these
two operations after the fault handlers, and they will be done only if
the fault has been handled successfully.

When an -EAGAIN errno is returned from the map handler, we hope to the
vcpu to enter guest directly instead of exiting back to userspace, so
adjust the return value at the end of function.
---

Changelogs

v2->v3:
- Rebased on top of v5.11-rc3
- Refine the commit messages
- Make some adjustment about return value in patch-2 and patch-3
- v2: https://lore.kernel.org/lkml/20201216122844.25092-1-wangyanan55@huawei.com/

v1->v2:
- Make part of the diff a seperate patch (patch-1)
- Add Will's Signed-off-by for patch-1
- Return an errno when meeting changing permissions case in map path
- Add a new patch (patch-3)
- v1: https://lore.kernel.org/lkml/20201211080115.21460-1-wangyanan55@huawei.com/

---

Yanan Wang (3):
  KVM: arm64: Adjust partial code of hyp stage-1 map and guest stage-2
    map
  KVM: arm64: Filter out the case of only changing permissions from
    stage-2 map path
  KVM: arm64: Mark the page dirty only if the fault is handled
    successfully

 arch/arm64/include/asm/kvm_pgtable.h |  5 ++
 arch/arm64/kvm/hyp/pgtable.c         | 83 ++++++++++++++++------------
 arch/arm64/kvm/mmu.c                 | 13 +++--
 3 files changed, 60 insertions(+), 41 deletions(-)
```
#### [PATCH v2 0/3] VMX: more nested fixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Jan 14 20:54:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12020901
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C1FAC433E0
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 20:56:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 172B423A9A
	for <kvm@archiver.kernel.org>; Thu, 14 Jan 2021 20:56:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728041AbhANU41 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 14 Jan 2021 15:56:27 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49400 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726573AbhANU41 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 14 Jan 2021 15:56:27 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610657701;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=ZyDfgALqUiawzmubBa6Wwvj+Dzw/MHsKyDI805lQ07Y=;
        b=i9XIuKNFJmaDeAYJuM57Nc2BjJnWoQDScF+nkulMW6D7VolNVUtzG16K6zyEUSrzjitOjI
        8YiFOZ67Bz0A0AJJTsrqO0FcGTrXFdIdyebv9h32Y8rauVA+bymEJiAEYvEVWcVul9wGKk
        3viDio1QEugPtjGbZqt0QLbv1Qiy78w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-291-D0uFwfSuOIeZyvrNomKfkg-1; Thu, 14 Jan 2021 15:54:57 -0500
X-MC-Unique: D0uFwfSuOIeZyvrNomKfkg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 83F358144E1;
        Thu, 14 Jan 2021 20:54:55 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.51])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4E1545C1C5;
        Thu, 14 Jan 2021 20:54:50 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>, x86@kernel.org,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        linux-kernel@vger.kernel.org, Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/3] VMX: more nested fixes
Date: Thu, 14 Jan 2021 22:54:46 +0200
Message-Id: <20210114205449.8715-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is hopefully the last fix for VMX nested migration
that finally allows my stress test of migration with a nested guest to pass.

In a nutshell after an optimization that was done in commit 7952d769c29ca,
some of vmcs02 fields which can be modified by the L2 freely while it runs
(like GSBASE and such) were not copied back to vmcs12 unless:

1. L1 tries to vmread them (update done on intercept)
2. vmclear or vmldptr on other vmcs are done.
3. nested state is read and nested guest is running.

What wasn't done was to sync these 'rare' fields when L1 is running
but still has a loaded vmcs12 which might have some stale fields,
if that vmcs was used to enter a guest already due to that optimization.

Plus I added two minor patches to improve VMX tracepoints
a bit. There is still a large room for improvement.

Best regards,
	Maxim Levitsky

Maxim Levitsky (3):
  KVM: nVMX: Always call sync_vmcs02_to_vmcs12_rare on migration
  KVM: nVMX: add kvm_nested_vmlaunch_resume tracepoint
  KVM: VMX: read idt_vectoring_info a bit earlier

 arch/x86/kvm/trace.h      | 30 ++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/nested.c | 19 ++++++++++++++-----
 arch/x86/kvm/vmx/vmx.c    |  3 ++-
 arch/x86/kvm/x86.c        |  1 +
 4 files changed, 47 insertions(+), 6 deletions(-)
```
