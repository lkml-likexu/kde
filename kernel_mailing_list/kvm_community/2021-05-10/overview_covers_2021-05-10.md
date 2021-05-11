

#### [PATCH 0/2] update virtio id table
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Mon May 10 08:10:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhu, Lingshan" <lingshan.zhu@intel.com>
X-Patchwork-Id: 12247143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 87C03C433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:15:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 672F361364
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:15:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230182AbhEJIQr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:16:47 -0400
Received: from mga18.intel.com ([134.134.136.126]:57585 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230045AbhEJIQr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:16:47 -0400
IronPort-SDR: 
 K6IWrOaXO8+7cLdFCy0N9+uBhFsraVyytdFkPz8umDwvBgwpqbRlMy1K+tOT+jjmH7WpHzu+iy
 hd4IuULNyF2g==
X-IronPort-AV: E=McAfee;i="6200,9189,9979"; a="186587919"
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="186587919"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:15:42 -0700
IronPort-SDR: 
 vqby9qWuqvjiN0JM+XxyZ4LIXeNrUYf1nt9zotvqg9xSUy2mDUTmSBNHDDaDIIZmT2++aWYeK6
 sHwCNEh+FROw==
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="436040620"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:15:40 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 0/2] update virtio id table
Date: Mon, 10 May 2021 16:10:13 +0800
Message-Id: <20210510081015.4212-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series updates virtio id table by adding
transitional device ids. Then reuses the ids
in ifcvf driver

Zhu Lingshan (2):
  virtio: update virtio id table, add transitional ids
  vDPA/ifcvf: reuse pre-defined macros for device ids and vendor ids

 drivers/vdpa/ifcvf/ifcvf_base.h | 12 ------------
 drivers/vdpa/ifcvf/ifcvf_main.c | 23 +++++++++++++----------
 include/uapi/linux/virtio_ids.h | 12 ++++++++++++
 3 files changed, 25 insertions(+), 22 deletions(-)
```
#### [RESEND PATCH v4 00/10] KVM: x86/pmu: Guest Architectural LBR
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon May 10 08:15:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12247149
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 41D03C433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:16:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 125856108B
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 08:16:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230146AbhEJIRU (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 04:17:20 -0400
Received: from mga12.intel.com ([192.55.52.136]:42716 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230059AbhEJIRU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 04:17:20 -0400
IronPort-SDR: 
 kTwoUV49CSQtICKqzAbwTsEW2M19tUkGb4igNiYrqFqcj05Rr00Kv4Fa3jbsgNgJHwyiFyqetM
 mjCsPXIRrmQQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9979"; a="178727651"
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="178727651"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 01:16:15 -0700
IronPort-SDR: 
 AdPc4YmQaJF/PrgQns47ijYSAa+cNsQPEOSpQFr1r9goPyObksljui00Ajk2RGFoc90nxbmQJl
 uNZ9IZbIkiXg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,287,1613462400";
   d="scan'208";a="408250810"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga002.jf.intel.com with ESMTP; 10 May 2021 01:16:13 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        wei.w.wang@intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [RESEND PATCH v4 00/10] KVM: x86/pmu: Guest Architectural LBR
 Enabling
Date: Mon, 10 May 2021 16:15:24 +0800
Message-Id: <20210510081535.94184-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi geniuses,

A new kernel cycle has begun, and this version looks promising. 

From the end user's point of view, the usage of Arch LBR is the same as
the legacy LBR we have merged in the mainline, but it is much faster.

The Architectural Last Branch Records (LBRs) is published 
in the 319433-040 release of Intel Architecture Instruction
Set Extensions and Future Features Programming Reference[0].

The main advantages for the Arch LBR users are [1]:
- Faster context switching due to XSAVES support and faster reset of
  LBR MSRs via the new DEPTH MSR
- Faster LBR read for a non-PEBS event due to XSAVES support, which
  lowers the overhead of the NMI handler.
- Linux kernel can support the LBR features without knowing the model
  number of the current CPU.

Please check more details in each commit and feel free to comment.

[0] https://software.intel.com/content/www/us/en/develop/download/
intel-architecture-instruction-set-extensions-and-future-features-programming-reference.html
[1] https://lore.kernel.org/lkml/1593780569-62993-1-git-send-email-kan.liang@linux.intel.com/
---
v13->v13 RESEND Changelog:
- Rebase to kvm/queue tree tag: kvm-5.13-2;
- Includes two XSS dependency patches from kvm/intel tree;

v3->v4 Changelog:
- Add one more host patch to reuse ARCH_LBR_CTL_MASK;
- Add reserve_lbr_buffers() instead of using GFP_ATOMIC;
- Fia a bug in the arch_lbr_depth_is_valid();
- Add LBR_CTL_EN to unify DEBUGCTLMSR_LBR and ARCH_LBR_CTL_LBREN;
- Add vmx->host_lbrctlmsr to save/restore host values;
- Add KVM_SUPPORTED_XSS to refactoring supported_xss;
- Clear Arch_LBR ans its XSS bit if it's not supported;
- Add negative testing to the related kvm-unit-tests;
- Refine code and commit messages;

Previous:
v4: https://lore.kernel.org/kvm/20210314155225.206661-1-like.xu@linux.intel.com/
v3: https://lore.kernel.org/kvm/20210303135756.1546253-1-like.xu@linux.intel.com/

Like Xu (8):
  perf/x86/intel: Fix the comment about guest LBR support on KVM
  perf/x86/lbr: Simplify the exposure check for the LBR_INFO registers
  KVM: vmx/pmu: Add MSR_ARCH_LBR_DEPTH emulation for Arch LBR
  KVM: vmx/pmu: Add MSR_ARCH_LBR_CTL emulation for Arch LBR
  KVM: vmx/pmu: Add Arch LBR emulation and its VMCS field
  KVM: x86: Expose Architectural LBR CPUID leaf
  KVM: x86: Refine the matching and clearing logic for supported_xss
  KVM: x86: Add XSAVE Support for Architectural LBRs

Sean Christopherson (1):
  KVM: x86: Report XSS as an MSR to be saved if there are supported
    features

Yang Weijiang (1):
  KVM: x86: Refresh CPUID on writes to MSR_IA32_XSS

 arch/x86/events/intel/core.c     |   3 +-
 arch/x86/events/intel/lbr.c      |   6 +-
 arch/x86/include/asm/kvm_host.h  |   1 +
 arch/x86/include/asm/msr-index.h |   1 +
 arch/x86/include/asm/vmx.h       |   4 ++
 arch/x86/kvm/cpuid.c             |  46 ++++++++++++--
 arch/x86/kvm/vmx/capabilities.h  |  25 +++++---
 arch/x86/kvm/vmx/pmu_intel.c     | 103 ++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.c           |  50 +++++++++++++--
 arch/x86/kvm/vmx/vmx.h           |   4 ++
 arch/x86/kvm/x86.c               |  19 +++++-
 11 files changed, 226 insertions(+), 36 deletions(-)
```
#### [PATCH 0/2] KVM: arm64: Fixup PC updates on exit to userspace
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon May 10 09:49:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12247427
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 65BA6C43461
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 09:49:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44BBA610CC
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 09:49:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230202AbhEJJun (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 05:50:43 -0400
Received: from mail.kernel.org ([198.145.29.99]:35662 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230098AbhEJJun (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 05:50:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 1915F613DC;
        Mon, 10 May 2021 09:49:35 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg2Xc-000LFh-R6; Mon, 10 May 2021 10:49:32 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        linux-arm-kernel@lists.infradead.org
Cc: Zenghui Yu <yuzenghui@huawei.com>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH 0/2] KVM: arm64: Fixup PC updates on exit to userspace
Date: Mon, 10 May 2021 10:49:13 +0100
Message-Id: <20210510094915.1909484-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
 linux-arm-kernel@lists.infradead.org, yuzenghui@huawei.com,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We recently moved anything related to PC updates into the guest entry
code to help with the protected KVM effort. However, I missed a
critical point: userspace needs to be able to observe state changes
when the vcpu exits. Otherwise, live migration is a bit broken and
vcpu reset can fail (as reported by Zenghui). Not good.

These two patches aim at fixing the above, and carry a Cc stable.

Marc Zyngier (2):
  KVM: arm64: Move __adjust_pc out of line
  KVM: arm64: Commit pending PC adjustemnts before returning to
    userspace

 arch/arm64/include/asm/kvm_asm.h           |  3 +++
 arch/arm64/kvm/arm.c                       | 10 ++++++++++
 arch/arm64/kvm/hyp/exception.c             | 18 +++++++++++++++++-
 arch/arm64/kvm/hyp/include/hyp/adjust_pc.h | 18 ------------------
 arch/arm64/kvm/hyp/nvhe/hyp-main.c         |  8 ++++++++
 arch/arm64/kvm/hyp/nvhe/switch.c           |  2 +-
 arch/arm64/kvm/hyp/vhe/switch.c            |  2 +-
 7 files changed, 40 insertions(+), 21 deletions(-)
```
#### [PATCH 00/53] Get rid of UTF-8 chars that can be mapped as ASCII
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Mon May 10 10:26:12 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 12247595
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.7 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B1B2DC433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 10:34:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 804D26191D
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 10:34:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231853AbhEJKfo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 06:35:44 -0400
Received: from mail.kernel.org ([198.145.29.99]:41508 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232056AbhEJKca (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 06:32:30 -0400
Received: by mail.kernel.org (Postfix) with ESMTPSA id B8B7061864;
        Mon, 10 May 2021 10:27:23 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=k20201202; t=1620642444;
        bh=ecNT6Qkny310TF2Gc5f4rT75sPCp5MHYtIZGEKTj06Y=;
        h=From:To:Cc:Subject:Date:From;
        b=UcevxFcEh3Li+i6O96esjAQwtO4uSF7OkmnaXbUGuKrV8uvn5D3YHrYAkQ2/PUQ+H
         W9TvnHIXs+6PuDeS1sySVDl5b+kZJLJNiKWzOaT28OTrcYXd41BcTT/W/xmDMiDYJc
         NXMcl5dkZF+skL/ecPvA5wTdK4o4x+GnunjH/NmxR/yJu8E4pznFJs+xWcx2gEwfA4
         XCBkfBQ0zIGZl9DOMzQHk7sBS5W6Hlu9kth9XR129w1/oLPDA2JZ/64ZgwSblnTghd
         iot0AnPlhuAm6nY73Msiw7+8VeDC0SCv/fIeb4QX1qF678zB0I6rD9S2HSN+p78ETw
         VllHul+Znpi9A==
Received: by mail.kernel.org with local (Exim 4.94.2)
        (envelope-from <mchehab@kernel.org>)
        id 1lg38C-000UOL-8L; Mon, 10 May 2021 12:27:20 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        alsa-devel@alsa-project.org, coresight@lists.linaro.org,
        dri-devel@lists.freedesktop.org, intel-gfx@lists.freedesktop.org,
        intel-wired-lan@lists.osuosl.org, keyrings@vger.kernel.org,
        kvm@vger.kernel.org, linux-acpi@vger.kernel.org,
        linux-arm-kernel@lists.infradead.org, linux-edac@vger.kernel.org,
        linux-ext4@vger.kernel.org, linux-f2fs-devel@lists.sourceforge.net,
        linux-fpga@vger.kernel.org, linux-hwmon@vger.kernel.org,
        linux-iio@vger.kernel.org, linux-input@vger.kernel.org,
        linux-integrity@vger.kernel.org, linux-media@vger.kernel.org,
        linux-pci@vger.kernel.org, linux-pm@vger.kernel.org,
        linux-rdma@vger.kernel.org, linux-riscv@lists.infradead.org,
        linux-sgx@vger.kernel.org, linux-usb@vger.kernel.org,
        mjpeg-users@lists.sourceforge.net, netdev@vger.kernel.org,
        rcu@vger.kernel.org, x86@kernel.org
Subject: [PATCH 00/53] Get rid of UTF-8 chars that can be mapped as ASCII
Date: Mon, 10 May 2021 12:26:12 +0200
Message-Id: <cover.1620641727.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are several UTF-8 characters at the Kernel's documentation.

Several of them were due to the process of converting files from
DocBook, LaTeX, HTML and Markdown. They were probably introduced
by the conversion tools used on that time.

Other UTF-8 characters were added along the time, but they're easily
replaceable by ASCII chars.

As Linux developers are all around the globe, and not everybody has UTF-8
as their default charset, better to use UTF-8 only on cases where it is really
needed.

The first 3 patches on this series were manually written, in order to solve
a few special cases.

The remaining patches on series address such cases on *.rst files and 
inside the Documentation/ABI, using this perl map table in order to do the
charset conversion:

my %char_map = (
	0x2010 => '-',		# HYPHEN
	0xad   => '-',		# SOFT HYPHEN
	0x2013 => '-',		# EN DASH
	0x2014 => '-',		# EM DASH

	0x2018 => "'",		# LEFT SINGLE QUOTATION MARK
	0x2019 => "'",		# RIGHT SINGLE QUOTATION MARK
	0xb4   => "'",		# ACUTE ACCENT

	0x201c => '"',		# LEFT DOUBLE QUOTATION MARK
	0x201d => '"',		# RIGHT DOUBLE QUOTATION MARK

	0x2212 => '-',		# MINUS SIGN
	0x2217 => '*',		# ASTERISK OPERATOR
	0xd7   => 'x',		# MULTIPLICATION SIGN

	0xbb   => '>',		# RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK

	0xa0   => ' ',		# NO-BREAK SPACE
	0xfeff => '',		# ZERO WIDTH NO-BREAK SPACE
);

After the conversion, those UTF-8 chars will be kept:

	- U+00a9 ('©'): COPYRIGHT SIGN
	- U+00ac ('¬'): NOT SIGN		# only at Documentation/powerpc/transactional_memory.rst
	- U+00ae ('®'): REGISTERED SIGN
	- U+00b0 ('°'): DEGREE SIGN
	- U+00b1 ('±'): PLUS-MINUS SIGN
	- U+00b2 ('²'): SUPERSCRIPT TWO
	- U+00b5 ('µ'): MICRO SIGN
	- U+00b7 ('·'): MIDDLE DOT		# See below
	- U+00bd ('½'): VULGAR FRACTION ONE HALF
	- U+00c7 ('Ç'): LATIN CAPITAL LETTER C WITH CEDILLA
	- U+00df ('ß'): LATIN SMALL LETTER SHARP S
	- U+00e1 ('á'): LATIN SMALL LETTER A WITH ACUTE
	- U+00e4 ('ä'): LATIN SMALL LETTER A WITH DIAERESIS
	- U+00e6 ('æ'): LATIN SMALL LETTER AE
	- U+00e7 ('ç'): LATIN SMALL LETTER C WITH CEDILLA
	- U+00e9 ('é'): LATIN SMALL LETTER E WITH ACUTE
	- U+00ea ('ê'): LATIN SMALL LETTER E WITH CIRCUMFLEX
	- U+00eb ('ë'): LATIN SMALL LETTER E WITH DIAERESIS
	- U+00f3 ('ó'): LATIN SMALL LETTER O WITH ACUTE
	- U+00f4 ('ô'): LATIN SMALL LETTER O WITH CIRCUMFLEX
	- U+00f6 ('ö'): LATIN SMALL LETTER O WITH DIAERESIS
	- U+00f8 ('ø'): LATIN SMALL LETTER O WITH STROKE
	- U+00fa ('ú'): LATIN SMALL LETTER U WITH ACUTE
	- U+00fc ('ü'): LATIN SMALL LETTER U WITH DIAERESIS
	- U+00fd ('ý'): LATIN SMALL LETTER Y WITH ACUTE
	- U+011f ('ğ'): LATIN SMALL LETTER G WITH BREVE
	- U+0142 ('ł'): LATIN SMALL LETTER L WITH STROKE
	- U+03bc ('μ'): GREEK SMALL LETTER MU
	- U+2026 ('…'): HORIZONTAL ELLIPSIS
	- U+2122 ('™'): TRADE MARK SIGN
	- U+2191 ('↑'): UPWARDS ARROW
	- U+2192 ('→'): RIGHTWARDS ARROW
	- U+2193 ('↓'): DOWNWARDS ARROW
	- U+2264 ('≤'): LESS-THAN OR EQUAL TO
	- U+2265 ('≥'): GREATER-THAN OR EQUAL TO
	- U+2500 ('─'): BOX DRAWINGS LIGHT HORIZONTAL
	- U+2502 ('│'): BOX DRAWINGS LIGHT VERTICAL
	- U+2514 ('└'): BOX DRAWINGS LIGHT UP AND RIGHT
	- U+251c ('├'): BOX DRAWINGS LIGHT VERTICAL AND RIGHT
	- U+2b0d ('⬍'): UP DOWN BLACK ARROW

PS.: maintainers were bcc on patch 00/53, in order to reduce the
risk of patch 00 to be rejected by list servers.

-

For U+00b7 ('·'): MIDDLE DOT, I opted to keep it on a few places:

- Documentation/devicetree/bindings/clock/qcom,rpmcc.txt

  As this file will be some day converted to yaml, where the 
  MIDDLE DOT will be removed, I guess it is not worth touching it.

- Documentation/scheduler/sched-deadline.rst

  There, it is used on a math expressions. So, better to keep.

- Documentation/devicetree/bindings/media/video-interface-devices.yaml

  There, it part of an ASCII artwork.

- translations/zh_CN

  I prefer not touching it, as it might have some special meaning in Simplified Chinese.

Mauro Carvalho Chehab (53):
  docs: cdrom-standard.rst: get rid of uneeded UTF-8 chars
  docs: ABI: remove a meaningless UTF-8 character
  docs: ABI: remove some spurious characters
  docs: index.rst: avoid using UTF-8 chars
  docs: hwmon: avoid using UTF-8 chars
  docs: admin-guide: avoid using UTF-8 chars
  docs: admin-guide: media: ipu3.rst: avoid using UTF-8 chars
  docs: admin-guide: sysctl: kernel.rst: avoid using UTF-8 chars
  docs: admin-guide: perf: imx-ddr.rst: avoid using UTF-8 chars
  docs: admin-guide: pm: avoid using UTF-8 chars
  docs: trace: coresight: coresight-etm4x-reference.rst: avoid using
    UTF-8 chars
  docs: driver-api: avoid using UTF-8 chars
  docs: driver-api: fpga: avoid using UTF-8 chars
  docs: driver-api: iio: avoid using UTF-8 chars
  docs: driver-api: thermal: avoid using UTF-8 chars
  docs: driver-api: media: drivers: avoid using UTF-8 chars
  docs: driver-api: firmware: other_interfaces.rst: avoid using UTF-8
    chars
  docs: driver-api: nvdimm: btt.rst: avoid using UTF-8 chars
  docs: fault-injection: nvme-fault-injection.rst: avoid using UTF-8
    chars
  docs: usb: avoid using UTF-8 chars
  docs: process: avoid using UTF-8 chars
  docs: block: data-integrity.rst: avoid using UTF-8 chars
  docs: userspace-api: media: fdl-appendix.rst: avoid using UTF-8 chars
  docs: userspace-api: media: v4l: avoid using UTF-8 chars
  docs: userspace-api: media: dvb: avoid using UTF-8 chars
  docs: vm: zswap.rst: avoid using UTF-8 chars
  docs: filesystems: f2fs.rst: avoid using UTF-8 chars
  docs: filesystems: ext4: avoid using UTF-8 chars
  docs: kernel-hacking: avoid using UTF-8 chars
  docs: hid: avoid using UTF-8 chars
  docs: security: tpm: avoid using UTF-8 chars
  docs: security: keys: trusted-encrypted.rst: avoid using UTF-8 chars
  docs: riscv: vm-layout.rst: avoid using UTF-8 chars
  docs: networking: scaling.rst: avoid using UTF-8 chars
  docs: networking: devlink: devlink-dpipe.rst: avoid using UTF-8 chars
  docs: networking: device_drivers: avoid using UTF-8 chars
  docs: x86: avoid using UTF-8 chars
  docs: scheduler: sched-deadline.rst: avoid using UTF-8 chars
  docs: dev-tools: testing-overview.rst: avoid using UTF-8 chars
  docs: power: powercap: powercap.rst: avoid using UTF-8 chars
  docs: ABI: avoid using UTF-8 chars
  docs: doc-guide: contributing.rst: avoid using UTF-8 chars
  docs: PCI: acpi-info.rst: avoid using UTF-8 chars
  docs: gpu: avoid using UTF-8 chars
  docs: sound: kernel-api: writing-an-alsa-driver.rst: avoid using UTF-8
    chars
  docs: arm64: arm-acpi.rst: avoid using UTF-8 chars
  docs: infiniband: tag_matching.rst: avoid using UTF-8 chars
  docs: timers: no_hz.rst: avoid using UTF-8 chars
  docs: misc-devices: ibmvmc.rst: avoid using UTF-8 chars
  docs: firmware-guide: acpi: lpit.rst: avoid using UTF-8 chars
  docs: firmware-guide: acpi: dsd: graph.rst: avoid using UTF-8 chars
  docs: virt: kvm: avoid using UTF-8 chars
  docs: RCU: avoid using UTF-8 chars

 .../obsolete/sysfs-kernel-fadump_registered   |   2 +-
 .../obsolete/sysfs-kernel-fadump_release_mem  |   2 +-
 ...sfs-class-chromeos-driver-cros-ec-lightbar |   2 +-
 .../ABI/testing/sysfs-class-net-cdc_ncm       |   2 +-
 .../ABI/testing/sysfs-devices-platform-ipmi   |   2 +-
 .../testing/sysfs-devices-platform-trackpoint |   2 +-
 Documentation/ABI/testing/sysfs-devices-soc   |   4 +-
 Documentation/ABI/testing/sysfs-module        |   4 +-
 Documentation/PCI/acpi-info.rst               |  26 +-
 .../Data-Structures/Data-Structures.rst       |  52 ++--
 .../Expedited-Grace-Periods.rst               |  40 +--
 .../Tree-RCU-Memory-Ordering.rst              |  10 +-
 .../RCU/Design/Requirements/Requirements.rst  | 126 ++++-----
 Documentation/admin-guide/index.rst           |   2 +-
 Documentation/admin-guide/media/ipu3.rst      |   2 +-
 Documentation/admin-guide/module-signing.rst  |   4 +-
 Documentation/admin-guide/perf/imx-ddr.rst    |   2 +-
 Documentation/admin-guide/pm/intel_idle.rst   |   4 +-
 Documentation/admin-guide/pm/intel_pstate.rst |   4 +-
 Documentation/admin-guide/ras.rst             |  94 +++----
 .../admin-guide/reporting-issues.rst          |  12 +-
 Documentation/admin-guide/sysctl/kernel.rst   |   2 +-
 Documentation/arm64/arm-acpi.rst              |   8 +-
 Documentation/block/data-integrity.rst        |   2 +-
 Documentation/cdrom/cdrom-standard.rst        |  30 +--
 Documentation/dev-tools/testing-overview.rst  |   4 +-
 Documentation/doc-guide/contributing.rst      |   2 +-
 .../driver-api/firmware/other_interfaces.rst  |   2 +-
 Documentation/driver-api/fpga/fpga-bridge.rst |  10 +-
 Documentation/driver-api/fpga/fpga-mgr.rst    |  12 +-
 .../driver-api/fpga/fpga-programming.rst      |   8 +-
 Documentation/driver-api/fpga/fpga-region.rst |  20 +-
 Documentation/driver-api/iio/buffers.rst      |   8 +-
 Documentation/driver-api/iio/hw-consumer.rst  |  10 +-
 .../driver-api/iio/triggered-buffers.rst      |   6 +-
 Documentation/driver-api/iio/triggers.rst     |  10 +-
 Documentation/driver-api/index.rst            |   2 +-
 Documentation/driver-api/ioctl.rst            |   8 +-
 .../media/drivers/sh_mobile_ceu_camera.rst    |   8 +-
 .../driver-api/media/drivers/vidtv.rst        |   4 +-
 .../driver-api/media/drivers/zoran.rst        |   2 +-
 Documentation/driver-api/nvdimm/btt.rst       |   2 +-
 .../driver-api/thermal/cpu-idle-cooling.rst   |  14 +-
 .../driver-api/thermal/intel_powerclamp.rst   |   6 +-
 .../thermal/x86_pkg_temperature_thermal.rst   |   2 +-
 .../fault-injection/nvme-fault-injection.rst  |   2 +-
 Documentation/filesystems/ext4/attributes.rst |  20 +-
 Documentation/filesystems/ext4/bigalloc.rst   |   6 +-
 Documentation/filesystems/ext4/blockgroup.rst |   8 +-
 Documentation/filesystems/ext4/blocks.rst     |   2 +-
 Documentation/filesystems/ext4/directory.rst  |  16 +-
 Documentation/filesystems/ext4/eainode.rst    |   2 +-
 Documentation/filesystems/ext4/inlinedata.rst |   6 +-
 Documentation/filesystems/ext4/inodes.rst     |   6 +-
 Documentation/filesystems/ext4/journal.rst    |   8 +-
 Documentation/filesystems/ext4/mmp.rst        |   2 +-
 .../filesystems/ext4/special_inodes.rst       |   4 +-
 Documentation/filesystems/ext4/super.rst      |  10 +-
 Documentation/filesystems/f2fs.rst            |   6 +-
 .../firmware-guide/acpi/dsd/graph.rst         |   2 +-
 Documentation/firmware-guide/acpi/lpit.rst    |   2 +-
 Documentation/gpu/i915.rst                    |   2 +-
 Documentation/gpu/komeda-kms.rst              |   2 +-
 Documentation/hid/hid-sensor.rst              |  70 ++---
 Documentation/hid/intel-ish-hid.rst           | 246 +++++++++---------
 Documentation/hwmon/ir36021.rst               |   2 +-
 Documentation/hwmon/ltc2992.rst               |   2 +-
 Documentation/hwmon/pm6764tr.rst              |   2 +-
 Documentation/hwmon/tmp103.rst                |   4 +-
 Documentation/index.rst                       |   4 +-
 Documentation/infiniband/tag_matching.rst     |   8 +-
 Documentation/kernel-hacking/hacking.rst      |   2 +-
 Documentation/kernel-hacking/locking.rst      |   2 +-
 Documentation/misc-devices/ibmvmc.rst         |   8 +-
 .../device_drivers/ethernet/intel/i40e.rst    |  12 +-
 .../device_drivers/ethernet/intel/iavf.rst    |   6 +-
 .../device_drivers/ethernet/netronome/nfp.rst |  12 +-
 .../networking/devlink/devlink-dpipe.rst      |   2 +-
 Documentation/networking/scaling.rst          |  18 +-
 Documentation/power/powercap/powercap.rst     | 210 +++++++--------
 Documentation/process/code-of-conduct.rst     |   2 +-
 .../process/kernel-enforcement-statement.rst  |   2 +-
 Documentation/riscv/vm-layout.rst             |   2 +-
 Documentation/scheduler/sched-deadline.rst    |   4 +-
 .../security/keys/trusted-encrypted.rst       |   4 +-
 Documentation/security/tpm/tpm_event_log.rst  |   2 +-
 Documentation/security/tpm/xen-tpmfront.rst   |   2 +-
 .../kernel-api/writing-an-alsa-driver.rst     |  68 ++---
 Documentation/timers/no_hz.rst                |   2 +-
 .../coresight/coresight-etm4x-reference.rst   |  16 +-
 Documentation/usb/ehci.rst                    |   2 +-
 Documentation/usb/gadget_printer.rst          |   2 +-
 Documentation/usb/mass-storage.rst            |  36 +--
 Documentation/usb/mtouchusb.rst               |   2 +-
 Documentation/usb/usb-serial.rst              |   2 +-
 .../media/dvb/audio-set-bypass-mode.rst       |   2 +-
 .../userspace-api/media/dvb/audio.rst         |   2 +-
 .../userspace-api/media/dvb/dmx-fopen.rst     |   2 +-
 .../userspace-api/media/dvb/dmx-fread.rst     |   2 +-
 .../media/dvb/dmx-set-filter.rst              |   2 +-
 .../userspace-api/media/dvb/intro.rst         |   6 +-
 .../userspace-api/media/dvb/video.rst         |   2 +-
 .../userspace-api/media/fdl-appendix.rst      |  64 ++---
 .../userspace-api/media/v4l/biblio.rst        |   8 +-
 .../userspace-api/media/v4l/crop.rst          |  16 +-
 .../userspace-api/media/v4l/dev-decoder.rst   |   6 +-
 .../userspace-api/media/v4l/diff-v4l.rst      |   2 +-
 .../userspace-api/media/v4l/open.rst          |   2 +-
 .../media/v4l/vidioc-cropcap.rst              |   4 +-
 Documentation/virt/kvm/api.rst                |  28 +-
 .../virt/kvm/running-nested-guests.rst        |  12 +-
 Documentation/vm/zswap.rst                    |   4 +-
 Documentation/x86/resctrl.rst                 |   2 +-
 Documentation/x86/sgx.rst                     |   4 +-
 114 files changed, 807 insertions(+), 807 deletions(-)
```
#### [PATCH v3 0/9] KVM: arm64: Initial host support for the Apple M1
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon May 10 13:48:15 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12248253
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFDDEC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:51:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A3B8161090
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:51:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241025AbhEJNww (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 09:52:52 -0400
Received: from mail.kernel.org ([198.145.29.99]:51562 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S242708AbhEJNu0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 09:50:26 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id DBC1A61076;
        Mon, 10 May 2021 13:49:21 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg6Hf-000Rol-LV; Mon, 10 May 2021 14:49:19 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Eric Auger <eric.auger@redhat.com>,
        Hector Martin <marcan@marcan.st>,
        Mark Rutland <mark.rutland@arm.com>, kernel-team@android.com
Subject: [PATCH v3 0/9] KVM: arm64: Initial host support for the Apple M1
Date: Mon, 10 May 2021 14:48:15 +0100
Message-Id: <20210510134824.1910399-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, james.morse@arm.com, suzuki.poulose@arm.com,
 alexandru.elisei@arm.com, eric.auger@redhat.com, marcan@marcan.st,
 mark.rutland@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a new version of the series previously posted at [2], reworking
the vGIC and timer code to cope with the M1 braindead^Wamusing nature.

Hardly any change this time around, mostly rebased on top of upstream
now that the dependencies have made it in.

Tested with multiple concurrent VMs running from an initramfs.

* From v2:
  - Rebased on 5.13-rc1
  - Fixed a couple of nits in the GIC registration code

* From v1 [1]:
  - Rebased on Hector's v4 posting[0]
  - Dropped a couple of patches that have been merged in the above series
  - Fixed irq_ack callback on the timer path

[0] https://lore.kernel.org/r/20210402090542.131194-1-marcan@marcan.st
[1] https://lore.kernel.org/r/20210316174617.173033-1-maz@kernel.org
[2] https://lore.kernel.org/r/20210403112931.1043452-1-maz@kernel.org

Marc Zyngier (9):
  irqchip/gic: Split vGIC probing information from the GIC code
  KVM: arm64: Handle physical FIQ as an IRQ while running a guest
  KVM: arm64: vgic: Be tolerant to the lack of maintenance interrupt
  KVM: arm64: vgic: Let an interrupt controller advertise lack of HW
    deactivation
  KVM: arm64: vgic: move irq->get_input_level into an ops structure
  KVM: arm64: vgic: Implement SW-driven deactivation
  KVM: arm64: timer: Refactor IRQ configuration
  KVM: arm64: timer: Add support for SW-based deactivation
  irqchip/apple-aic: Advertise some level of vGICv3 compatibility

 arch/arm64/kvm/arch_timer.c            | 161 +++++++++++++++++++++----
 arch/arm64/kvm/hyp/hyp-entry.S         |   6 +-
 arch/arm64/kvm/vgic/vgic-init.c        |  34 +++++-
 arch/arm64/kvm/vgic/vgic-v2.c          |  19 ++-
 arch/arm64/kvm/vgic/vgic-v3.c          |  19 ++-
 arch/arm64/kvm/vgic/vgic.c             |  14 +--
 drivers/irqchip/irq-apple-aic.c        |   8 ++
 drivers/irqchip/irq-gic-common.c       |  13 --
 drivers/irqchip/irq-gic-common.h       |   2 -
 drivers/irqchip/irq-gic-v3.c           |   6 +-
 drivers/irqchip/irq-gic.c              |   6 +-
 include/kvm/arm_vgic.h                 |  41 +++++--
 include/linux/irqchip/arm-gic-common.h |  25 +---
 include/linux/irqchip/arm-vgic-info.h  |  43 +++++++
 14 files changed, 291 insertions(+), 106 deletions(-)
 create mode 100644 include/linux/irqchip/arm-vgic-info.h
```
#### [kvm-unit-tests PATCH v2 0/6] s390x: uv: Extend guest test and add
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon May 10 13:51:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12248287
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id ACC54C433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:56:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 785CF61041
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 13:56:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237890AbhEJN5T (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 09:57:19 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64988 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237059AbhEJNxQ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 09:53:16 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14ADXJjQ154698;
        Mon, 10 May 2021 09:52:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=Q+7Zj+sId07YdnyuQKTNdwpNALxH64Rq4oYQa5Y8ywQ=;
 b=fmentmrNlw1A+V+zOpRM2YmkrbdKEVsKkT27wlE8HgWk0VfjqxDJrnnflAnsABmUmh2G
 IH57mcQTb5ARMIC8u0Oh+8trvjvQNkHibdzXGrjdJnzahUGxcMuKbnJPKVDpsVrTByiQ
 buEn1l/vTK4s1ZXa25gZHddb+t/sS8CbOAolRgX6PUJ/HJW2rrKn0/tzy5unIYyI0vGP
 h0DtIDUI0K3zMXWqFICC1ligeXJZsU3n3RD2XYEO2xRBPFujNAcaIhaoFT+l0L3PF65R
 2XuqCrp8VFMam85G5jXWOcGXQg6TKQ/1jI7k/FpQq53CnWQKQ276poQpv7Gcg9XMNMpG wQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f3scvyf4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 09:52:08 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14ADXhwk158340;
        Mon, 10 May 2021 09:52:08 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38f3scvye4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 09:52:08 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14ADgeBA001637;
        Mon, 10 May 2021 13:52:05 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03ams.nl.ibm.com with ESMTP id 38dj9890cn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 13:52:05 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14ADq16p38732266
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 13:52:01 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B1F36A405F;
        Mon, 10 May 2021 13:52:01 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EEBB4A4055;
        Mon, 10 May 2021 13:52:00 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 13:52:00 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/6] s390x: uv: Extend guest test and add
 host test
Date: Mon, 10 May 2021 13:51:42 +0000
Message-Id: <20210510135148.1904-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: 34i-dDaPE6WTEsU0Q8v7mE5HVw-4d5te
X-Proofpoint-GUID: FP-gzwibUrgvf7F1ZUoySFVU_T4RCifs
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_07:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 bulkscore=0
 malwarescore=0 clxscore=1015 mlxlogscore=999 spamscore=0
 priorityscore=1501 lowpriorityscore=0 adultscore=0 mlxscore=0
 impostorscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2104190000 definitions=main-2105100096
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

My stack of patches is starting to lean, so lets try to put some of
them upstream...

The first part is just additions to the UV guest test and a library
that makes checking the installed UV calls easier. Additionally we now
check for the proper UV share/unshare availability when allocating IO
memory instead of only relying on stfle 158.

The second part adds a UV host test with a large number UV of return
code checks.

v2:
	* Added rev-bys
	* Added stfle 158 check to uv_os_is_host/guest
	* Added asserts to uv_query_test_feature()
	  * Prevent specifying bit nr outside of range
	  * Prevent checking for features without having queried them
	* Added !feature bit check to uv guest/host invalid command test
	* Renamed uv_query_test_feature() to uv_query_test_call()

Janosch Frank (6):
  s390x: uv-guest: Add invalid share location test
  s390x: Add more Ultravisor command structure definitions
  s390x: uv: Add UV lib
  s390x: Test for share/unshare call support before using them
  s390x: uv-guest: Test invalid commands
  s390x: Add UV host test

 lib/s390x/asm/uv.h    | 152 ++++++++++++-
 lib/s390x/io.c        |   2 +
 lib/s390x/malloc_io.c |   5 +-
 lib/s390x/uv.c        |  45 ++++
 lib/s390x/uv.h        |  10 +
 s390x/Makefile        |   2 +
 s390x/uv-guest.c      |  60 +++++-
 s390x/uv-host.c       | 480 ++++++++++++++++++++++++++++++++++++++++++
 8 files changed, 743 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/uv.c
 create mode 100644 lib/s390x/uv.h
 create mode 100644 s390x/uv-host.c
```
#### [kvm-unit-tests PATCH 0/4] s390x: cpumodel: Add sclp checks
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Mon May 10 15:00:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12248427
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9C6E6C43461
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:05:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61C4C61481
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:05:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240628AbhEJPGk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 11:06:40 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63167 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S230449AbhEJPDH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 11:03:07 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AEaCA6137361;
        Mon, 10 May 2021 11:02:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=Hx/5zR/k53Kf7li0NdC6hyS24oZzz50dQguaxaXkf4Q=;
 b=gIDOgwCGEGwewdIqDQ8UCe5BkFqqVQfi5EmqA2QJqGjLt88ukJgz6YdGt+XcKXnfa/mT
 tPPoVvsTo79WiIbt+HVXy8p+yRx+yUiqFOJhysoFY3BQ/VOhT44fU8R6/3516kxwFgI+
 Asqy0U+WqY9IO6fOXXe5I8GwHjqxt7my0rcnucedkstF2xLY0DMAY9lJmAU5pRTBH18+
 B7FOtefxnWONxsnTUF92WxAAZ/kR2Q/j4lO7ZTw14NRmUsthgNS5TJRmyPQTBV0K4ram
 hxpIRvjNYrchefCGLXUuPLaEzv3LTdqd5Jw2EGrnp+ASshOQ4ugPYPBliinQm0ZyscIx +w==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f487wkcq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 11:02:01 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AEaelO140130;
        Mon, 10 May 2021 11:02:00 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f487wkbp-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 11:02:00 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AEqeKc006431;
        Mon, 10 May 2021 15:01:59 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03ams.nl.ibm.com with ESMTP id 38dj9891w5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 15:01:58 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14AF1tMs29688120
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 15:01:55 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B35EBAE057;
        Mon, 10 May 2021 15:01:55 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E510BAE056;
        Mon, 10 May 2021 15:01:54 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 15:01:54 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, cohuck@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        thuth@redhat.com
Subject: [kvm-unit-tests PATCH 0/4] s390x: cpumodel: Add sclp checks
Date: Mon, 10 May 2021 15:00:11 +0000
Message-Id: <20210510150015.11119-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: UZJiiUjQE-151fYV8XfrnvfXgS-etEsR
X-Proofpoint-GUID: sPD8wiwQyUIMEv8Rbok5nE3iFZ2I5zEB
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_09:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 clxscore=1015
 suspectscore=0 priorityscore=1501 malwarescore=0 mlxscore=0 spamscore=0
 bulkscore=0 mlxlogscore=999 impostorscore=0 lowpriorityscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105100105
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

SCLP facilities have been a bit overlooked in cpumodel tests and have
recently caused some headaches. So lets extend the tests and the
library with a bit of sclp feature checking.

Based on the uv_host branch / patches.

Janosch Frank (4):
  s390x: sclp: Only fetch read info byte 134 if cpu entries are above it
  lib: s390x: sclp: Extend feature probing
  s390x: cpumodel: FMT4 SCLP test
  s390x: cpumodel: FMT2 SCLP implies test

 lib/s390x/sclp.c | 23 +++++++++++++++-
 lib/s390x/sclp.h | 38 ++++++++++++++++++++++++--
 s390x/cpumodel.c | 71 +++++++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 127 insertions(+), 5 deletions(-)
```
#### [PATCH v6 0/2] fallback for emulation errors
##### From: Aaron Lewis <aaronlewis@google.com>

```c
From patchwork Mon May 10 14:48:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12248497
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 77CAAC433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:19:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 55F0F61139
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:19:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233990AbhEJPUO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 11:20:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45424 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234543AbhEJPSu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 11:18:50 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E63C3C061574
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 07:48:38 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id
 u7-20020a259b470000b02904dca50820c2so19966404ybo.11
        for <kvm@vger.kernel.org>; Mon, 10 May 2021 07:48:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=Eoa6ihgecNBdFQExHytcx2mx1a+eIjFgjkpb1S01aME=;
        b=SXRFfdTupE+ft3atKQ7rOk+izjlVlxelHEkRgHbANZ2q8q6XU9nwXZZ6NgYEwgmnly
         73W/fN8nSNTbL3oxe/BlDmkDFMwy2vsfqX0+N2XwnSPT8LlDuxkGEu9GCb+wBH2fNH59
         WRIRz4cAaizuXe+BUMtfpv8ZjE848jz3vUQkuEZtS6Ni0HwQ5J98pYQcMCCW76eiWtN+
         Xk+HNnqqHZGk3XELA4bFUOev57e2IQ1SZ7/iP/eKVOVUC/h+1sKLbck7HOi7nVx4qoY7
         mMWr16bSRSmxSPyD1KjXA+CSikaHr16oaq+o+/AgpHcB4Dv9raCxIq41DFd5VFrsc731
         PkvA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=Eoa6ihgecNBdFQExHytcx2mx1a+eIjFgjkpb1S01aME=;
        b=NRQbCSz1E89uFirIXWTQWP6x/akzcS2Lqx2q70vMjrbC47yKw4wpguWUd1/y/LWhfQ
         kq436WzPvsRng37sOX9MPBHvr6gJIRKfMiSuz17nb26zoHjtwxs+juGUjFtbpK0FJo5k
         i6lCei04Kd+8iF3IREulGffhfwpfjQczkKTfFHx7zu1nl6L12d17dRV2ISUl/HQEYAdw
         0Qk6ANOYs+3xZCfejlg1FBZOFKeQb/IzZtoQYSligl8d4fShHWPwJzeqNGEI197Yr6IZ
         j0z0R2ftahqBUAJblYUJ8rtxj2R0rTFGnO8akDdk3GdK84JSjAbswuFIA3/ZN2xkiuDn
         AtEA==
X-Gm-Message-State: AOAM533JNfkCHxbvti/Z/+7QA1628tF7jiGn0JrOhCgKopMFPVvuzmHW
        ePx65hJ/l2yCKwKCHwEv2Eu3hSGKD3mVXvJX
X-Google-Smtp-Source: 
 ABdhPJzvAS2X3pPt3UXGTnxNFMFyZSRhqMZ+qdIpkAXN5cZCT3vYvPEgKkiBoH+UPTMWHci5USPdHfioo8bChEtI
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:3396:9513:fac0:8ec7])
 (user=aaronlewis job=sendgmr) by 2002:a25:4ac4:: with SMTP id
 x187mr29286178yba.478.1620658117824; Mon, 10 May 2021 07:48:37 -0700 (PDT)
Date: Mon, 10 May 2021 07:48:32 -0700
Message-Id: <20210510144834.658457-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v6 0/2] fallback for emulation errors
From: Aaron Lewis <aaronlewis@google.com>
To: david.edmondson@oracle.com, seanjc@google.com, jmattson@google.com
Cc: kvm@vger.kernel.org, Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset allows userspace to be a fallback for handling emulation errors.

v1 -> v2:

 - Added additional documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - In prepare_emulation_failure_exit():
   - Created a local variable for vcpu->run.
   - Cleared the flags, emulation_failure.flags.
   - Or'd the instruction bytes flag on to emulation_failure.flags.
 - Updated the comment for KVM_INTERNAL_ERROR_EMULATION flags on how they are
   to be used.
 - Updated the comment for struct emulation_failure.

v2 -> v3:

 - Update documentation for KVM_CAP_EXIT_ON_EMULATION_FAILURE.
 - Fix spacing in prepare_emulation_failure_exit().

v3 -> v4:

 - In prepare_emulation_failure_exit():
   - Clear instruction bytes to 0x90.
   - Copy over insn_size bytes rather than sizeof(ctxt->fetch.data).
 - set_page_table_entry() takes a pte rather than mask.
 - In _vm_get_page_table_entry():
   - Removed check for page aligned addresses only.
   - Added canonical check.
   - Added a check to make sure no reserved bits are set along the walk except
     for the final pte (the pte cannot have the reserved bits checked otherwise
     the test would fail).
   - Added check to ensure superpage bits are clear.
 - Added check in test for 'allow_smaller_maxphyaddr' module parameter.
 - If the is_flds() check fails, only look at the first byte.
 - Don't use labels to increment the RIP.  Decode the instruction well enough to
   ensure it is only 2-bytes.

v4 -> v5:

 - Switch 'insn_size' to u32.
 - Add documentation for how the flags are used.
 - Remove 'max_insn_size' and use 'sizeof(run->emulation_failure.insn_bytes)' instead.
 - Fix typos.
 - Fix canonical check.
 - Add reserved check for bit-7 of PML4E.
 - Add reserved check for bit-63 of all page table levels if EFER.NXE = 0.
 - Remove opcode check (it might be a prefix).
 - Remove labels.
 - Remove detritus (rogue cpuid entry in the test).

v5 -> v6

 - Fix documentation.

Aaron Lewis (2):
  kvm: x86: Allow userspace to handle emulation errors
  selftests: kvm: Allows userspace to handle emulation errors.

 Documentation/virt/kvm/api.rst                |  19 ++
 arch/x86/include/asm/kvm_host.h               |   6 +
 arch/x86/kvm/x86.c                            |  37 ++-
 include/uapi/linux/kvm.h                      |  23 ++
 tools/include/uapi/linux/kvm.h                |  23 ++
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   4 +
 .../selftests/kvm/lib/x86_64/processor.c      |  94 ++++++++
 .../kvm/x86_64/emulator_error_test.c          | 219 ++++++++++++++++++
 10 files changed, 423 insertions(+), 4 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/emulator_error_test.c
```
#### [for-6.1 v3 0/3] virtiofsd: Add support for FUSE_SYNCFS request
##### From: Greg Kurz <groug@kaod.org>

```c
From patchwork Mon May 10 15:55:36 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 12248613
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4EC21C433B4
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:55:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 29DC06161E
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 15:55:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231600AbhEJP44 convert rfc822-to-8bit (ORCPT
        <rfc822;kvm@archiver.kernel.org>); Mon, 10 May 2021 11:56:56 -0400
Received: from us-smtp-delivery-44.mimecast.com ([207.211.30.44]:25060 "EHLO
        us-smtp-delivery-44.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230492AbhEJP4y (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 11:56:54 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-399-Dv24lgUpNayROI3ptof5aQ-1; Mon, 10 May 2021 11:55:44 -0400
X-MC-Unique: Dv24lgUpNayROI3ptof5aQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 537B3100A61E;
        Mon, 10 May 2021 15:55:43 +0000 (UTC)
Received: from bahia.redhat.com (ovpn-112-152.ams2.redhat.com [10.36.112.152])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D638819C44;
        Mon, 10 May 2021 15:55:40 +0000 (UTC)
From: Greg Kurz <groug@kaod.org>
To: qemu-devel@nongnu.org
Cc: Vivek Goyal <vgoyal@redhat.com>, virtio-fs@redhat.com,
        "Michael S. Tsirkin" <mst@redhat.com>, kvm@vger.kernel.org,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Miklos Szeredi <miklos@szeredi.hu>, Greg Kurz <groug@kaod.org>
Subject: [for-6.1 v3 0/3] virtiofsd: Add support for FUSE_SYNCFS request
Date: Mon, 10 May 2021 17:55:36 +0200
Message-Id: <20210510155539.998747-1-groug@kaod.org>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

FUSE_SYNCFS allows the client to flush the host page cache.
This isn't available in upstream linux yet, but the following
tree can be used to test:

https://gitlab.com/gkurz/linux/-/tree/virtio-fs-sync

v3: - track submounts and do per-submount syncfs() (Vivek)
    - based on new version of FUSE_SYNCFS (still not upstream)
      https://listman.redhat.com/archives/virtio-fs/2021-May/msg00025.html

v2: - based on new version of FUSE_SYNCFS
      https://listman.redhat.com/archives/virtio-fs/2021-April/msg00166.html
    - propagate syncfs() errors to client (Vivek)

Greg Kurz (3):
  Update linux headers to 5.13-rc1 + FUSE_SYNCFS
  virtiofsd: Track mounts
  virtiofsd: Add support for FUSE_SYNCFS request

 .../infiniband/hw/vmw_pvrdma/pvrdma_verbs.h   |  35 -
 include/standard-headers/drm/drm_fourcc.h     |  23 +-
 include/standard-headers/linux/ethtool.h      | 109 ++-
 include/standard-headers/linux/fuse.h         |  27 +-
 include/standard-headers/linux/input.h        |   2 +-
 include/standard-headers/linux/virtio_ids.h   |   2 +
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |   7 +
 linux-headers/asm-generic/unistd.h            |  13 +-
 linux-headers/asm-mips/unistd_n32.h           | 752 +++++++--------
 linux-headers/asm-mips/unistd_n64.h           | 704 +++++++-------
 linux-headers/asm-mips/unistd_o32.h           | 844 ++++++++---------
 linux-headers/asm-powerpc/kvm.h               |   2 +
 linux-headers/asm-powerpc/unistd_32.h         | 857 +++++++++---------
 linux-headers/asm-powerpc/unistd_64.h         | 801 ++++++++--------
 linux-headers/asm-s390/unistd_32.h            |   5 +
 linux-headers/asm-s390/unistd_64.h            |   5 +
 linux-headers/asm-x86/kvm.h                   |   1 +
 linux-headers/asm-x86/unistd_32.h             |   5 +
 linux-headers/asm-x86/unistd_64.h             |   5 +
 linux-headers/asm-x86/unistd_x32.h            |   5 +
 linux-headers/linux/kvm.h                     | 134 +++
 linux-headers/linux/userfaultfd.h             |  36 +-
 linux-headers/linux/vfio.h                    |  35 +
 tools/virtiofsd/fuse_lowlevel.c               |  11 +
 tools/virtiofsd/fuse_lowlevel.h               |  12 +
 tools/virtiofsd/passthrough_ll.c              |  80 +-
 tools/virtiofsd/passthrough_seccomp.c         |   1 +
 27 files changed, 2465 insertions(+), 2048 deletions(-)
```
#### [PATCH v16 00/14] s390/vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
From patchwork Mon May 10 16:44:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12248747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C7355C433ED
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:44:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA998611AB
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:44:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231783AbhEJQpn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 12:45:43 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32916 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231712AbhEJQpl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 12:45:41 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AGXdd9171240;
        Mon, 10 May 2021 12:44:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=cKjCThNs1Z8S62us0vpN/UVaWEorE/JCpbGrQY8nvDQ=;
 b=GeqQsLpcXAYfEIXr+NmWEQX0AJFEF8N8OViFH5azSdXenWumLXqHgZj+jROn5lO1ZtZd
 PXYKnJ669H/vwAxPHpY/c8CPFwHc7PawyFU0FHSvXhC9HuqfVxulqHvr4A7F9CRMlSUg
 gS2FbpvrUCG8qctuO+MpBeMPXUN1vF4v0vS4NtbUkpUqNzjuTbyttiCafRi33LPM7/Mz
 T5BuhznlOdlldh83NMiQeL8CvywtcsvelTK9xDQTNCIq0sGr5CBFCm6xdTtEE2zeGYJA
 ycNUuiC5LVs0vA86bbpDYPRPJob3ebpYuxKmeFz99DpgF21CKLmKbA66AXsDPbPnozf2 /Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f7vn18y2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 12:44:34 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AGXcIm171182;
        Mon, 10 May 2021 12:44:33 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38f7vn18xg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 12:44:33 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AGgpnH003007;
        Mon, 10 May 2021 16:44:32 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma01dal.us.ibm.com with ESMTP id 38dj99bj5w-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:44:32 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 14AGiVEp12780300
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 16:44:31 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E8F41AE060;
        Mon, 10 May 2021 16:44:30 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 165BCAE05F;
        Mon, 10 May 2021 16:44:28 +0000 (GMT)
Received: from cpe-172-100-179-72.stny.res.rr.com.com (unknown [9.85.140.234])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 10 May 2021 16:44:27 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: jjherne@linux.ibm.com, freude@linux.ibm.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, mjrosato@linux.ibm.com,
        pasic@linux.ibm.com, alex.williamson@redhat.com,
        kwankhede@nvidia.com, fiuczy@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v16 00/14] s390/vfio-ap: dynamic configuration support
Date: Mon, 10 May 2021 12:44:09 -0400
Message-Id: <20210510164423.346858-1-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: WInjpa1s4P9SUG2eIXWfrbkn2PxO6iOs
X-Proofpoint-GUID: O0RFpyWQNFre2KEws2frUzbcy32PmxFh
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_09:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999
 suspectscore=0 priorityscore=1501 spamscore=0 phishscore=0 clxscore=1011
 impostorscore=0 malwarescore=0 bulkscore=0 mlxscore=0 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105100113
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note: Patch 1, "s390/vfio-ap: fix memory leak in mdev remove callback"
      does not belong to this series. It is currently being reviewed
      and is included here because it will be a pre-req for this series
      when it is accepted and merged.

The current design for AP pass-through does not support making dynamic
changes to the AP matrix of a running guest resulting in a few
deficiencies this patch series is intended to mitigate:

1. Adapters, domains and control domains can not be added to or removed
   from a running guest. In order to modify a guest's AP configuration,
   the guest must be terminated; only then can AP resources be assigned
   to or unassigned from the guest's matrix mdev. The new AP
   configuration becomes available to the guest when it is subsequently
   restarted.

2. The AP bus's /sys/bus/ap/apmask and /sys/bus/ap/aqmask interfaces can
   be modified by a root user without any restrictions. A change to
   either mask can result in AP queue devices being unbound from the
   vfio_ap device driver and bound to a zcrypt device driver even if a
   guest is using the queues, thus giving the host access to the guest's
   private crypto data and vice versa.

3. The APQNs derived from the Cartesian product of the APIDs of the
   adapters and APQIs of the domains assigned to a matrix mdev must
   reference an AP queue device bound to the vfio_ap device driver. The
   AP architecture allows assignment of AP resources that are not
   available to the system, so this artificial restriction is not
   compliant with the architecture.

4. The AP configuration profile can be dynamically changed for the linux
   host after a KVM guest is started. For example, a new domain can be
   dynamically added to the configuration profile via the SE or an HMC
   connected to a DPM enabled lpar. Likewise, AP adapters can be
   dynamically configured (online state) and deconfigured (standby state)
   using the SE, an SCLP command or an HMC connected to a DPM enabled
   lpar. This can result in inadvertent sharing of AP queues between the
   guest and host.

5. A root user can manually unbind an AP queue device representing a
   queue in use by a KVM guest via the vfio_ap device driver's sysfs
   unbind attribute. In this case, the guest will be using a queue that
   is not bound to the driver which violates the device model.

This patch series introduces the following changes to the current design
to alleviate the shortcomings described above as well as to implement
more of the AP architecture:

1. A root user will be prevented from making edits to the AP bus's
   /sys/bus/ap/apmask or /sys/bus/ap/aqmask if the change would transfer
   ownership of an APQN from the vfio_ap device driver to a zcrypt driver
   while the APQN is assigned to a matrix mdev.

2. Allow a root user to hot plug/unplug AP adapters, domains and control
   domains for a KVM guest using the matrix mdev via its sysfs
   assign/unassign attributes.

4. Allow assignment of an AP adapter or domain to a matrix mdev even if
   it results in assignment of an APQN that does not reference an AP
   queue device bound to the vfio_ap device driver, as long as the APQN
   is not reserved for use by the default zcrypt drivers (also known as
   over-provisioning of AP resources). Allowing over-provisioning of AP
   resources better models the architecture which does not preclude
   assigning AP resources that are not yet available in the system. Such
   APQNs, however, will not be assigned to the guest using the matrix
   mdev; only APQNs referencing AP queue devices bound to the vfio_ap
   device driver will actually get assigned to the guest.

5. Handle dynamic changes to the AP device model.

1. Rationale for changes to AP bus's apmask/aqmask interfaces:
----------------------------------------------------------
Due to the extremely sensitive nature of cryptographic data, it is
imperative that great care be taken to ensure that such data is secured.
Allowing a root user, either inadvertently or maliciously, to configure
these masks such that a queue is shared between the host and a guest is
not only avoidable, it is advisable. It was suggested that this scenario
is better handled in user space with management software, but that does
not preclude a malicious administrator from using the sysfs interfaces
to gain access to a guest's crypto data. It was also suggested that this
scenario could be avoided by taking access to the adapter away from the
guest and zeroing out the queues prior to the vfio_ap driver releasing the
device; however, stealing an adapter in use from a guest as a by-product
of an operation is bad and will likely cause problems for the guest
unnecessarily. It was decided that the most effective solution with the
least number of negative side effects is to prevent the situation at the
source.

2. Rationale for hot plug/unplug using matrix mdev sysfs interfaces:
----------------------------------------------------------------
Allowing a user to hot plug/unplug AP resources using the matrix mdev
sysfs interfaces circumvents the need to terminate the guest in order to
modify its AP configuration. Allowing dynamic configuration makes
reconfiguring a guest's AP matrix much less disruptive.

3. Rationale for allowing over-provisioning of AP resources:
-----------------------------------------------------------
Allowing assignment of AP resources to a matrix mdev and ultimately to a
guest better models the AP architecture. The architecture does not
preclude assignment of unavailable AP resources. If a queue subsequently
becomes available while a guest using the matrix mdev to which its APQN
is assigned, the guest will be given access to it. If an APQN
is dynamically unassigned from the underlying host system, it will
automatically become unavailable to the guest.

Change log v15-v16:
------------------
* Added patch to reset queues after an adapter or domain is unassigned in
  case of re-assignment to a different mdev (see patch description for
  patch 9, "s390/vfio-ap: reset queues after adapter/domain unassignment").

* Fixed circular lockdep re-introduced by hot plugging of AP resources into
  a KVM guest (see changes to vfio_ap_mdev_commit_apcb() function in patch
  8, "s390/vfio-ap: allow hot plug/unplug of AP resources using mdev
  device"). 


Change log v14-v15:
------------------
* Fixed bug: Unlink mdev from all queues when the mdev is removed.

Change log v13-v14:
------------------
* Removed patch "s390/vfio-ap: clean up vfio_ap resources when KVM pointer
  invalidated". The patch is not necessary because that is handled
  with patch 1 of this series (currently being merged) and
  commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")

* Removed patch "s390/vfio-ap: No need to disable IRQ after queue reset",
  that has already been merged with
  commit 6c12a6384e0c ("s390/vfio-ap: No need to disable IRQ after queue reset").

* Initialize the vfio_ap_queue object before setting the drvdata in
  the probe callback

* Change return code from mdev assignment interfaces to -EAGAIN when
  mutex_trylock fails for the mdev lock.

* Restored missing hunk from v12 in the group notifier callback, but
  had to restore it to the vfio_ap_mdev_set_kvm() function due to
  changes made via merged commits noted above.

* Reordered patch "s390/vfio-ap: sysfs attribute to display the
  guest's matrix" to follow the patches that modify the shadow
  APCB.

* Remove queue from APCB before resetting it in the remove
  callback.

* Split the vfio_ap_mdev_unlink_queue() function into two
  functions: one to remove the link from the matrix mdev to
  the queue; and, one to remove the link from the queue to the matrix
  mdev.

* Removed the QCI call and the shadow_apcb memcpy from the
  vfio_ap_mdev_filter_apcb() function.

* Do not clear shadow_apcb when there are not adapters or domains
  assigned.

* Moved filtering code from "s390/vfio-ap: allow hot plug/unplug of
  AP resources using mdev device" into its own patch.

* Squashed the two patches comprising the handling of changes to
  the AP configuration into one patch.

* Added code to delay hot plug during probe until the AP bus scan
  is complete if the APID of the queue is in the bitmap of adapters
  currently being added to the AP configuration.

Change log v12-v13:
------------------
* Combined patches 12/13 from previous series into one patch

* Moved all changes for linking queues and mdevs into a single patch

* Re-ordered some patches to aid in review

* Using mutex_trylock() function in adapter/domain assignment functions
  to avoid potential deadlock condition with in_use callback

* Using filtering function for refreshing the guest's APCB for all events
  that change the APCB: assign/unassign adapters, domains, control domains;
  bind/unbind of queue devices; and, changes to the host AP configuration.

Change log v11-v12:
------------------
* Moved matrix device lock to protect group notifier callback

* Split the 'No need to disable IRQ after queue reset' patch into
  multiple patches for easier review (move probe/remove callback
  functions and remove disable IRQ after queue reset)

* Added code to decrement reference count for KVM in group notifier
  callback

* Using mutex_trylock() in functions implementing the sysfs assign_adapter
  and assign_domain as well as the in_use callback to avoid deadlock
  between the AP bus's ap_perms mutex and the matrix device lock used by
  vfio_ap driver.

* The sysfs guest_matrix attribute of the vfio_ap mdev will now display
  the shadow APCB regardless of whether a guest is using the mdev or not

* Replaced vfio_ap mdev filtering function with a function that initializes
  the guest's APCB by filtering the vfio_ap mdev by APID.

* No longer using filtering function during adapter/domain assignment
  to/from the vfio_ap mdev; replaced with new hot plug/unplug
  adapter/domain functions.

* No longer using filtering function during bind/unbind; replaced with
  hot plug/unplug queue functions.

* No longer using filtering function for bulk assignment of new adapters
  and domains in on_scan_complete callback; replaced with new hot plug
  functions.


Change log v10-v11:
------------------
* The matrix mdev's configuration is not filtered by APID so that if any
  APQN assigned to the mdev is not bound to the vfio_ap device driver,
  the adapter will not get plugged into the KVM guest on startup, or when
  a new adapter is assigned to the mdev.

* Replaced patch 8 by squashing patches 8 (filtering patch) and 15 (handle
  probe/remove).

* Added a patch 1 to remove disable IRQ after a reset because the reset
  already disables a queue.

* Now using filtering code to update the KVM guest's matrix when
  notified that AP bus scan has completed.

* Fixed issue with probe/remove not inititiated by a configuration change
  occurring within a config change.


Change log v9-v10:
-----------------
* Updated the documentation in vfio-ap.rst to include information about the
  AP dynamic configuration support

Change log v8-v9:
----------------
* Fixed errors flagged by the kernel test robot

* Fixed issue with guest losing queues when a new queue is probed due to
  manual bind operation.

Change log v7-v8:
----------------
* Now logging a message when an attempt to reserve APQNs for the zcrypt
  drivers will result in taking a queue away from a KVM guest to provide
  the sysadmin a way to ascertain why the sysfs operation failed.

* Created locked and unlocked versions of the ap_parse_mask_str() function.

* Now using new interface provided by an AP bus patch -
  s390/ap: introduce new ap function ap_get_qdev() - to retrieve
  struct ap_queue representing an AP queue device. This patch is not a
  part of this series but is a prerequisite for this series.

Change log v6-v7:
----------------
* Added callbacks to AP bus:
  - on_config_changed: Notifies implementing drivers that
    the AP configuration has changed since last AP device scan.
  - on_scan_complete: Notifies implementing drivers that the device scan
    has completed.
  - implemented on_config_changed and on_scan_complete callbacks for
    vfio_ap device driver.
  - updated vfio_ap device driver's probe and remove callbacks to handle
    dynamic changes to the AP device model.
* Added code to filter APQNs when assigning AP resources to a KVM guest's
  CRYCB

Change log v5-v6:
----------------
* Fixed a bug in ap_bus.c introduced with patch 2/7 of the v5
  series. Harald Freudenberer pointed out that the mutex lock
  for ap_perms_mutex in the apmask_store and aqmask_store functions
  was not being freed.

* Removed patch 6/7 which added logging to the vfio_ap driver
  to expedite acceptance of this series. The logging will be introduced
  with a separate patch series to allow more time to explore options
  such as DBF logging vs. tracepoints.

* Added 3 patches related to ensuring that APQNs that do not reference
  AP queue devices bound to the vfio_ap device driver are not assigned
  to the guest CRYCB:

  Patch 4: Filter CRYCB bits for unavailable queue devices
  Patch 5: sysfs attribute to display the guest CRYCB
  Patch 6: update guest CRYCB in vfio_ap probe and remove callbacks

* Added a patch (Patch 9) to version the vfio_ap module.

* Reshuffled patches to allow the in_use callback implementation to
  invoke the vfio_ap_mdev_verify_no_sharing() function introduced in
  patch 2.

Change log v4-v5:
----------------
* Added a patch to provide kernel s390dbf debug logs for VFIO AP

Change log v3->v4:
-----------------
* Restored patches preventing root user from changing ownership of
  APQNs from zcrypt drivers to the vfio_ap driver if the APQN is
  assigned to an mdev.

* No longer enforcing requirement restricting guest access to
  queues represented by a queue device bound to the vfio_ap
  device driver.

* Removed shadow CRYCB and now directly updating the guest CRYCB
  from the matrix mdev's matrix.

* Rebased the patch series on top of 'vfio: ap: AP Queue Interrupt
  Control' patches.

* Disabled bind/unbind sysfs interfaces for vfio_ap driver

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (14):
  s390/vfio-ap: fix memory leak in mdev remove callback
  s390/vfio-ap: use new AP bus interface to search for queue devices
  s390/vfio-ap: move probe and remove callbacks to vfio_ap_ops.c
  s390/vfio-ap: manage link between queue struct and matrix mdev
  s390/vfio-ap: introduce shadow APCB
  s390/vfio-ap: refresh guest's APCB by filtering APQNs assigned to mdev
  s390/vfio-ap: allow assignment of unavailable AP queues to mdev device
  s390/vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390/vfio-ap: reset queues after adapter/domain unassignment
  s390/zcrypt: driver callback to indicate resource in use
  s390/vfio-ap: implement in-use callback for vfio_ap driver
  s390/vfio-ap: sysfs attribute to display the guest's matrix
  s390/zcrypt: notify drivers on config changed and scan complete
    callbacks
  s390/vfio-ap: update docs to include dynamic config support

 Documentation/s390/vfio-ap.rst        |  383 +++++++---
 drivers/s390/crypto/ap_bus.c          |  249 +++++-
 drivers/s390/crypto/ap_bus.h          |   16 +
 drivers/s390/crypto/vfio_ap_drv.c     |   46 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 1008 ++++++++++++++++++-------
 drivers/s390/crypto/vfio_ap_private.h |   28 +-
 6 files changed, 1322 insertions(+), 408 deletions(-)
```
#### [PATCH v4 00/66] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon May 10 16:58:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12248797
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 75930C43462
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:59:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5C36F61581
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 16:59:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232090AbhEJRAv (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:00:51 -0400
Received: from mail.kernel.org ([198.145.29.99]:52796 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231151AbhEJRAq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 13:00:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 079E3611CE;
        Mon, 10 May 2021 16:59:41 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94.2)
        (envelope-from <maz@kernel.org>)
        id 1lg9Fq-000Uqg-Qy; Mon, 10 May 2021 17:59:39 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Haibo Xu <haibo.xu@linaro.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        kernel-team@android.com
Subject: [PATCH v4 00/66] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
 support
Date: Mon, 10 May 2021 17:58:14 +0100
Message-Id: <20210510165920.1913477-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, jintack@cs.columbia.edu, haibo.xu@linaro.org,
 james.morse@arm.com, suzuki.poulose@arm.com, alexandru.elisei@arm.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Here the bi-annual drop of the KVM/arm64 NV support code.

Not a lot has changed since [1], except for a discovery mechanism for
the EL2 support, some tidying up in the idreg emulation, dropping RMR
support, and a rebase on top of 5.13-rc1.

As usual, blame me for any bug, and nobody else.

It is still massively painful to run on the FVP, but if you have a
Neoverse V1 or N2 system that is collecting dust, I have the right
stuff to keep it busy!

	M.

[1] https://lore.kernel.org/r/20201210160002.1407373-1-maz@kernel.org

Andre Przywara (1):
  KVM: arm64: nv: vgic: Allow userland to set VGIC maintenance IRQ

Christoffer Dall (15):
  KVM: arm64: nv: Introduce nested virtualization VCPU feature
  KVM: arm64: nv: Reset VCPU to EL2 registers if VCPU nested virt is set
  KVM: arm64: nv: Allow userspace to set PSR_MODE_EL2x
  KVM: arm64: nv: Add nested virt VCPU primitives for vEL2 VCPU state
  KVM: arm64: nv: Reset VMPIDR_EL2 and VPIDR_EL2 to sane values
  KVM: arm64: nv: Handle trapped ERET from virtual EL2
  KVM: arm64: nv: Emulate PSTATE.M for a guest hypervisor
  KVM: arm64: nv: Trap EL1 VM register accesses in virtual EL2
  KVM: arm64: nv: Only toggle cache for virtual EL2 when SCTLR_EL2
    changes
  KVM: arm64: nv: Implement nested Stage-2 page table walk logic
  KVM: arm64: nv: Unmap/flush shadow stage 2 page tables
  KVM: arm64: nv: arch_timer: Support hyp timer emulation
  KVM: arm64: nv: vgic: Emulate the HW bit in software
  KVM: arm64: nv: Add nested GICv3 tracepoints
  KVM: arm64: nv: Sync nested timer state with ARMv8.4

Jintack Lim (18):
  arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
  KVM: arm64: nv: Handle HCR_EL2.NV system register traps
  KVM: arm64: nv: Support virtual EL2 exceptions
  KVM: arm64: nv: Inject HVC exceptions to the virtual EL2
  KVM: arm64: nv: Trap SPSR_EL1, ELR_EL1 and VBAR_EL1 from virtual EL2
  KVM: arm64: nv: Trap CPACR_EL1 access in virtual EL2
  KVM: arm64: nv: Handle PSCI call via smc from the guest
  KVM: arm64: nv: Respect virtual HCR_EL2.TWX setting
  KVM: arm64: nv: Respect virtual CPTR_EL2.{TFP,FPEN} settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV bit setting
  KVM: arm64: nv: Respect virtual HCR_EL2.TVM and TRVM settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV1 bit setting
  KVM: arm64: nv: Emulate EL12 register accesses from the virtual EL2
  KVM: arm64: nv: Configure HCR_EL2 for nested virtualization
  KVM: arm64: nv: Introduce sys_reg_desc.forward_trap
  KVM: arm64: nv: Set a handler for the system instruction traps
  KVM: arm64: nv: Trap and emulate AT instructions from virtual EL2
  KVM: arm64: nv: Nested GICv3 Support

Marc Zyngier (32):
  KVM: arm64: nv: Add EL2 system registers to vcpu context
  KVM: arm64: nv: Add non-VHE-EL2->EL1 translation helpers
  KVM: arm64: nv: Handle virtual EL2 registers in
    vcpu_read/write_sys_reg()
  KVM: arm64: nv: Handle SPSR_EL2 specially
  KVM: arm64: nv: Handle HCR_EL2.E2H specially
  KVM: arm64: nv: Save/Restore vEL2 sysregs
  KVM: arm64: nv: Forward debug traps to the nested guest
  KVM: arm64: nv: Filter out unsupported features from ID regs
  KVM: arm64: nv: Hide RAS from nested guests
  KVM: arm64: nv: Support multiple nested Stage-2 mmu structures
  KVM: arm64: nv: Handle shadow stage 2 page faults
  KVM: arm64: nv: Restrict S2 RD/WR permissions to match the guest's
  KVM: arm64: nv: Trap and emulate TLBI instructions from virtual EL2
  KVM: arm64: nv: Fold guest's HCR_EL2 configuration into the host's
  KVM: arm64: nv: Add handling of EL2-specific timer registers
  KVM: arm64: nv: Load timer before the GIC
  KVM: arm64: nv: Don't load the GICv4 context on entering a nested
    guest
  KVM: arm64: nv: Implement maintenance interrupt forwarding
  KVM: arm64: nv: Allow userspace to request KVM_ARM_VCPU_NESTED_VIRT
  KVM: arm64: nv: Add handling of ARMv8.4-TTL TLB invalidation
  KVM: arm64: nv: Invalidate TLBs based on shadow S2 TTL-like
    information
  KVM: arm64: Allow populating S2 SW bits
  KVM: arm64: nv: Tag shadow S2 entries with nested level
  KVM: arm64: nv: Add include containing the VNCR_EL2 offsets
  KVM: arm64: Map VNCR-capable registers to a separate page
  KVM: arm64: nv: Move nested vgic state into the sysreg file
  KVM: arm64: Add ARMv8.4 Enhanced Nested Virt cpufeature
  KVM: arm64: nv: Synchronize PSTATE early on exit
  KVM: arm64: nv: Allocate VNCR page when required
  KVM: arm64: nv: Enable ARMv8.4-NV support
  KVM: arm64: nv: Fast-track 'InHost' exception returns
  KVM: arm64: nv: Fast-track EL1 TLBIs for VHE guests

 .../admin-guide/kernel-parameters.txt         |    4 +
 .../virt/kvm/devices/arm-vgic-v3.rst          |   12 +-
 arch/arm64/include/asm/cpucaps.h              |    2 +
 arch/arm64/include/asm/esr.h                  |    6 +
 arch/arm64/include/asm/kvm_arm.h              |   28 +-
 arch/arm64/include/asm/kvm_asm.h              |    4 +
 arch/arm64/include/asm/kvm_emulate.h          |  145 +-
 arch/arm64/include/asm/kvm_host.h             |  174 ++-
 arch/arm64/include/asm/kvm_hyp.h              |    2 +
 arch/arm64/include/asm/kvm_mmu.h              |   18 +-
 arch/arm64/include/asm/kvm_nested.h           |  152 +++
 arch/arm64/include/asm/kvm_pgtable.h          |   10 +
 arch/arm64/include/asm/sysreg.h               |  105 +-
 arch/arm64/include/asm/vncr_mapping.h         |   73 +
 arch/arm64/include/uapi/asm/kvm.h             |    2 +
 arch/arm64/kernel/cpufeature.c                |   35 +
 arch/arm64/kvm/Makefile                       |    4 +-
 arch/arm64/kvm/arch_timer.c                   |  189 ++-
 arch/arm64/kvm/arm.c                          |   37 +-
 arch/arm64/kvm/at.c                           |  231 ++++
 arch/arm64/kvm/emulate-nested.c               |  186 +++
 arch/arm64/kvm/guest.c                        |    6 +
 arch/arm64/kvm/handle_exit.c                  |   81 +-
 arch/arm64/kvm/hyp/exception.c                |   45 +-
 arch/arm64/kvm/hyp/include/hyp/switch.h       |   28 +-
 arch/arm64/kvm/hyp/include/hyp/sysreg-sr.h    |   28 +-
 arch/arm64/kvm/hyp/nvhe/switch.c              |   10 +-
 arch/arm64/kvm/hyp/nvhe/sysreg-sr.c           |    2 +-
 arch/arm64/kvm/hyp/pgtable.c                  |    6 +
 arch/arm64/kvm/hyp/vgic-v3-sr.c               |    2 +-
 arch/arm64/kvm/hyp/vhe/switch.c               |  207 ++-
 arch/arm64/kvm/hyp/vhe/sysreg-sr.c            |  125 +-
 arch/arm64/kvm/hyp/vhe/tlb.c                  |   83 ++
 arch/arm64/kvm/inject_fault.c                 |   63 +-
 arch/arm64/kvm/mmu.c                          |  191 ++-
 arch/arm64/kvm/nested.c                       |  910 ++++++++++++
 arch/arm64/kvm/reset.c                        |   14 +-
 arch/arm64/kvm/sys_regs.c                     | 1215 ++++++++++++++++-
 arch/arm64/kvm/sys_regs.h                     |    8 +
 arch/arm64/kvm/trace_arm.h                    |   65 +-
 arch/arm64/kvm/vgic/vgic-init.c               |   30 +
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   22 +
 arch/arm64/kvm/vgic/vgic-nested-trace.h       |  137 ++
 arch/arm64/kvm/vgic/vgic-v3-nested.c          |  240 ++++
 arch/arm64/kvm/vgic/vgic-v3.c                 |   39 +-
 arch/arm64/kvm/vgic/vgic.c                    |   44 +
 arch/arm64/kvm/vgic/vgic.h                    |   10 +
 include/kvm/arm_arch_timer.h                  |    7 +
 include/kvm/arm_vgic.h                        |   16 +
 include/uapi/linux/kvm.h                      |    1 +
 tools/arch/arm/include/uapi/asm/kvm.h         |    1 +
 51 files changed, 4893 insertions(+), 162 deletions(-)
 create mode 100644 arch/arm64/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/include/asm/vncr_mapping.h
 create mode 100644 arch/arm64/kvm/at.c
 create mode 100644 arch/arm64/kvm/emulate-nested.c
 create mode 100644 arch/arm64/kvm/nested.c
 create mode 100644 arch/arm64/kvm/vgic/vgic-nested-trace.h
 create mode 100644 arch/arm64/kvm/vgic/vgic-v3-nested.c
```
#### [patch 0/4] VMX: configure posted interrupt descriptor when assigning
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
From patchwork Mon May 10 17:26:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12249181
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81F81C43460
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E3F1611F0
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 17:54:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233296AbhEJRzu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 13:55:50 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:60050 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233238AbhEJRzg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 13:55:36 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620669271;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=zGAx3lT0Af5JXR+dtPqi2eB2KHwQq7HfmXkTkY8h0d0=;
        b=A5AdZePpjo5EivEbH9G64vWbtr1ym3yoskRL0+sutSJqFTaQzi3kGbtBKAL0SqN+ZoQizS
        rEGSMx+svURh04F9PJfNLo7fmn1lKe9SUEWF87KB5ZE8pOVTZT2zHWwfnACxjbW0+ZHu0k
        /I8Si02VICiF4ZYClX8gpmk4r8omgpA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-199-8Gj3r4FEMOONqDok0TUXKg-1; Mon, 10 May 2021 13:54:29 -0400
X-MC-Unique: 8Gj3r4FEMOONqDok0TUXKg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 82AEA8014D8;
        Mon, 10 May 2021 17:54:28 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-8.gru2.redhat.com [10.97.112.8])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 2C6305C1BB;
        Mon, 10 May 2021 17:54:20 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id 73DAE406E9D9; Mon, 10 May 2021 14:54:15 -0300 (-03)
Message-ID: <20210510172646.930550753@redhat.com>
User-Agent: quilt/0.66
Date: Mon, 10 May 2021 14:26:46 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Xu <peterx@redhat.com>
Subject: [patch 0/4] VMX: configure posted interrupt descriptor when assigning
 device (v3)
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Configuration of the posted interrupt descriptor is incorrect when devices
are hotplugged to the guest (and vcpus are halted).

See patch 4 for details.
---

v3: improved comments (Sean)
    use kvm_vcpu_wake_up (Sean)
    drop device_count from start_assignment function (Peter Xu)

v2: rather than using a potentially racy IPI (vs vcpu->cpu switches),
    kick the vcpus when assigning a device and let the blocked per-CPU
    list manipulation happen locally at ->pre_block and ->post_block
    (Sean Christopherson).
```
#### [RFC PATCH v5 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Mon May 10 20:56:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12249323
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 872E5C43603
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 20:57:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5F066613CA
	for <kvm@archiver.kernel.org>; Mon, 10 May 2021 20:57:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232816AbhEJU6E (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 16:58:04 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26828 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232847AbhEJU6A (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 May 2021 16:58:00 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14AKiMOs076650;
        Mon, 10 May 2021 16:56:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=3ejgp9ieQVOHbjTpuh55gWqJ5Sk7YcDs3R1J9dJEvXI=;
 b=FnxBdsPurdMu/XUtxCwUyhNiFLHUvIHcKBmgC2ob/EsLXnQfyIV/yMATck29s2SOufy1
 bGc1KSkPmyhp3+zhU24MBoCkoXNJAPzaHcAU7YfIVCQdzU1A7e8KGsRjs79Q2qqI/fYc
 bLB6su/EG7yZyB3H1FFySkAejWXo54q/K0j5ZImpDuArd+vFpXFpHO4CU8S8Gudha/G9
 zw2RKa9VqDqJW3tzBvQHZkZOcwxxkez7GZonDZp0yhBk5KP8qjJgiUIdf8mRhLirzG95
 2Gdu2h0pwkk6T4z5hTKK7gpvuvM9vdOeh8jOT4zQ/8UPJbPc2bXv4xMGtjC/sEMHwXeg OA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fc4mg95u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:56:54 -0400
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14AKjfAE087857;
        Mon, 10 May 2021 16:56:54 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fc4mg948-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 16:56:54 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14AKtI0f003065;
        Mon, 10 May 2021 20:56:52 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma05fra.de.ibm.com with ESMTP id 38dj98gpec-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 May 2021 20:56:51 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14AKumAC23855390
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 May 2021 20:56:48 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 99ABEA405C;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 85FF5A4054;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 10 May 2021 20:56:48 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 2B7B6E028D; Mon, 10 May 2021 22:56:48 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH v5 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Mon, 10 May 2021 22:56:43 +0200
Message-Id: <20210510205646.1845844-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: 9npWSwHlq46qtu_gfjb56wneFsKSX4PR
X-Proofpoint-ORIG-GUID: sHfTEOP3pOjOvzHyi5DyQ5z4UfYKzsE4
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-10_12:2021-05-10,2021-05-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 phishscore=0
 malwarescore=0 mlxlogscore=999 clxscore=1015 mlxscore=0 impostorscore=0
 priorityscore=1501 spamscore=0 adultscore=0 bulkscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104190000
 definitions=main-2105100140
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Conny, Matt, Halil,

Here's the update to my proposed series for handling the collision
between interrupts for START SUBCHANNEL and HALT/CLEAR SUBCHANNEL.
I'm feeling more confident in the state of them now based on the
discussion on v4, so will keep the cover letter brief. :)

I carried patches 1 and 3 from the last version forward, as patch
1 and 2 here. (Thanks, Conny, for the r-b's on them.)

I dropped patches 2 and 4 from the last version, as part of this
newest attempt.  The conversation on patch 4 [1] has formed into
the new patch 3.

As we'd discussed offline last week, I still have the todo for
a more proper audit of the serialization across these codepaths.
But this seems a better, simpler, fix for the code in its current
form, which addresses my problematic test case and does not
impact my usual regression tests. Any further rework for the
serialization [2] will be more invasive, and take a bit longer.

Thanks,
Eric

Changelog:
v4->v5:
 - Applied Conny's r-b to patches 1 and 3
 - Dropped patch 2 and 4
 - Use a "finished" flag in the interrupt completion path

Previous versions:
v4: https://lore.kernel.org/kvm/20210413182410.1396170-1-farman@linux.ibm.com/
v3: https://lore.kernel.org/kvm/20200616195053.99253-1-farman@linux.ibm.com/
v2: https://lore.kernel.org/kvm/20200513142934.28788-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20200124145455.51181-1-farman@linux.ibm.com/

References:
[1] https://lore.kernel.org/kvm/2c1c1e73d488673ec39d7c085a343cbd6b50fb41.camel@linux.ibm.com/
[2] https://lore.kernel.org/kvm/20210416164137.23f4631b.cohuck@redhat.com/

Eric Farman (3):
  vfio-ccw: Check initialized flag in cp_init()
  vfio-ccw: Reset FSM state to IDLE inside FSM
  vfio-ccw: Serialize FSM IDLE state with I/O completion

 drivers/s390/cio/vfio_ccw_cp.c  | 4 ++++
 drivers/s390/cio/vfio_ccw_drv.c | 8 +++++---
 drivers/s390/cio/vfio_ccw_fsm.c | 1 +
 drivers/s390/cio/vfio_ccw_ops.c | 2 --
 4 files changed, 10 insertions(+), 5 deletions(-)
```
