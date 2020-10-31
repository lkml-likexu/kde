

#### [PATCH RESEND v13 00/10] Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Fri Oct 30 03:52:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11868421
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8C293C388F9
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 03:56:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BE6620725
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 03:56:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725996AbgJ3D4h (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 29 Oct 2020 23:56:37 -0400
Received: from mga09.intel.com ([134.134.136.24]:4238 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725780AbgJ3D4h (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Oct 2020 23:56:37 -0400
IronPort-SDR: 
 VMKVo7krnmGnC7XUZ5Kju+u3ot9aU9S2Uk7etFtpcivip6eXdgiLF4UtLS8CB9D9HJCPJ24pEW
 sRaUpeukVntw==
X-IronPort-AV: E=McAfee;i="6000,8403,9789"; a="168685723"
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="168685723"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Oct 2020 20:56:37 -0700
IronPort-SDR: 
 ASIsZXV24m2E6Y7pyH77ueexEcpNMS1k/QUGq5WkeYD+FjYebJAFlzH9BEKYA5Oiqb/AisT5wA
 Eha1MyJVNo3w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="525770378"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 29 Oct 2020 20:56:33 -0700
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
Subject: [PATCH RESEND v13 00/10] Guest Last Branch Recording Enabling
Date: Fri, 30 Oct 2020 11:52:10 +0800
Message-Id: <20201030035220.102403-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi All,

PMU features matter.  Please help review this rebased version for the
next kernel release and with this patch set, the following error will be
gone forever and cloud developers can better understand their
programs with less profiling overhead:

  $ perf record -b lbr ${WORKLOAD}
  or $ perf record --call-graph lbr ${WORKLOAD}
  Error:
  cycles: PMU Hardware doesn't support sampling/overflow-interrupts. Try 'perf stat'

We already have host perf support to implement guest LBR, please
check more details in each commit and feel free to test and comment.

v12->v13 Changelog:
- remove perf patches since they're merged already;
- add a minor patch to refactor MSR_IA32_DEBUGCTLMSR set/get handler;
- add a minor patch to expose vmx_set_intercept_for_msr();
- add a minor patch to adjust features visibility via IA32_PERF_CAPABILITIES;
- spilt the big patch to three pieces (0004-0006) for better understanding and review;
- make the LBR_FMT exposure patch as the last step to enable guest LBR;

Previous:
https://lore.kernel.org/kvm/20200613080958.132489-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

The user space could configure whether it's enabled or not for each
guest via MSR_IA32_PERF_CAPABILITIES msr. As a first step, a guest
could only enable LBR feature if its cpu model is the same as the
host since the LBR feature is still one of model specific features.

If it's enabled on the guest, the guest LBR driver would accesses the
LBR MSR (including IA32_DEBUGCTLMSR and records MSRs) as host does.
The first guest access on the LBR related MSRs is always interceptible.
The KVM trap would create a special LBR event (called guest LBR event)
which enables the callstack mode and none of hardware counter is assigned.
The host perf would enable and schedule this event as usual. 

Guest's first access to a LBR registers gets trapped to KVM, which
creates a guest LBR perf event. It's a regular LBR perf event which gets
the LBR facility assigned from the perf subsystem. Once that succeeds,
the LBR stack msrs are passed through to the guest for efficient accesses.
However, if another host LBR event comes in and takes over the LBR
facility, the LBR msrs will be made interceptible, and guest following
accesses to the LBR msrs will be trapped and meaningless. 

Because saving/restoring tens of LBR MSRs (e.g. 32 LBR stack entries) in
VMX transition brings too excessive overhead to frequent vmx transition
itself, the guest LBR event would help save/restore the LBR stack msrs
during the context switching with the help of native LBR event callstack
mechanism, including LBR_SELECT msr.

If the guest no longer accesses the LBR-related MSRs within a scheduling
time slice and the LBR enable bit is unset, vPMU would release its guest
LBR event as a normal event of a unused vPMC and the pass-through
state of the LBR stack msrs would be canceled.

---

LBR testcase:
echo 1 > /proc/sys/kernel/watchdog
echo 25 > /proc/sys/kernel/perf_cpu_time_max_percent
echo 5000 > /proc/sys/kernel/perf_event_max_sample_rate
echo 0 > /proc/sys/kernel/perf_cpu_time_max_percent
./perf record -b ./br_instr a

- Perf report on the host:
Samples: 72K of event 'cycles', Event count (approx.): 72512
Overhead  Command   Source Shared Object           Source Symbol                           Target Symbol                           Basic Block Cycles
  12.12%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           1
  11.05%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             5
   8.81%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             4
   5.04%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           20
   4.92%  br_instr  br_instr                       [.] lfsr_cond                           [.] cmp_end                             6
   4.88%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           6
   4.58%  br_instr  br_instr                       [.] cmp_end                             [.] lfsr_cond                           5

- Perf report on the guest:
Samples: 92K of event 'cycles', Event count (approx.): 92544
Overhead  Command   Source Shared Object  Source Symbol                                   Target Symbol                                   Basic Block Cycles
  12.03%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   1
  11.09%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     5
   8.57%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     4
   5.08%  br_instr  br_instr              [.] lfsr_cond                                   [.] cmp_end                                     6
   5.06%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   20
   4.87%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   6
   4.70%  br_instr  br_instr              [.] cmp_end                                     [.] lfsr_cond                                   5

Conclusion: the profiling results on the guest are similar to that on the host.

Like Xu (10):
  KVM: x86: Move common set/get handler of MSR_IA32_DEBUGCTLMSR to VMX
  KVM: x86/vmx: Make vmx_set_intercept_for_msr() non-static and expose it
  KVM: x86/pmu: Use IA32_PERF_CAPABILITIES to adjust features visibility
  KVM: vmx/pmu: Clear PMU_CAP_LBR_FMT when guest LBR is disabled
  KVM: vmx/pmu: Create a guest LBR event when vcpu sets DEBUGCTLMSR_LBR
  KVM: vmx/pmu: Pass-through LBR msrs to when the guest LBR event is ACTIVE
  KVM: vmx/pmu: Reduce the overhead of LBR pass-through or cancellation
  KVM: vmx/pmu: Emulate legacy freezing LBRs on virtual PMI
  KVM: vmx/pmu: Expose LBR_FMT in the MSR_IA32_PERF_CAPABILITIES
  KVM: vmx/pmu: Release guest LBR event via lazy release mechanism

 arch/x86/kvm/pmu.c              |  12 +-
 arch/x86/kvm/pmu.h              |   5 +
 arch/x86/kvm/vmx/capabilities.h |  22 ++-
 arch/x86/kvm/vmx/pmu_intel.c    | 292 +++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c          |  52 +++++-
 arch/x86/kvm/vmx/vmx.h          |  28 +++
 arch/x86/kvm/x86.c              |  15 +-
 7 files changed, 400 insertions(+), 26 deletions(-)
```
#### [PATCH v6 0/5] iommu aux-domain APIs extensions
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
From patchwork Fri Oct 30 04:58:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11868479
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AAF30C4741F
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 05:05:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 49B70221F9
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 05:05:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725806AbgJ3FFI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 01:05:08 -0400
Received: from mga06.intel.com ([134.134.136.31]:5284 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726042AbgJ3FFH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 01:05:07 -0400
IronPort-SDR: 
 AEDj3Sg4HS/CNXXZBfYKiBXA30f3WOL2e5opgr6fuo24A22dKinkFceEftY7xd0Qb07Xh7pP/J
 MuOdDZjz2qWQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9789"; a="230196538"
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="230196538"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 29 Oct 2020 22:05:04 -0700
IronPort-SDR: 
 yA/8uLhnMK0V46kNAp34cxMA+s1WXTmWTVtL9265fjUb9AtY4ndlRl2EAqyl1S3MC2fCwfyUEF
 LBIDN+mqCFTQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,432,1596524400";
   d="scan'208";a="425261524"
Received: from allen-box.sh.intel.com ([10.239.159.139])
  by fmsmga001.fm.intel.com with ESMTP; 29 Oct 2020 22:05:01 -0700
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
Subject: [PATCH v6 0/5] iommu aux-domain APIs extensions
Date: Fri, 30 Oct 2020 12:58:04 +0800
Message-Id: <20201030045809.957927-1-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Joerg and Alex,

A description of purpose for this series could be found here.

https://lore.kernel.org/linux-iommu/20200901033422.22249-1-baolu.lu@linux.intel.com/

The previous version was posted here.

https://lore.kernel.org/linux-iommu/20200922061042.31633-1-baolu.lu@linux.intel.com/

This version is evolved according to Joerg's comments posted here.

https://lore.kernel.org/linux-iommu/20200924095532.GK27174@8bytes.org/

This basic idea is that IOMMU registers an iommu_ops for subdevice
bus (for example, the vfio/mdev bus), so that the upper layer device
passthrough framework could use the standard iommu-core code to setup
the IOMMU logistics.

This series was tested by Dave Jiang <dave.jiang@intel.com> with his
idxd driver posted here. Very appreciated!

https://lore.kernel.org/lkml/160021250454.67751.3119489448651243709.stgit@djiang5-desk3.ch.intel.com/

Please help to review and comment.

Best regards,
baolu

Lu Baolu (5):
  vfio/mdev: Register mdev bus earlier during boot
  iommu: Use bus iommu ops for aux related callback
  iommu/vt-d: Make some static functions global
  iommu/vt-d: Add iommu_ops support for subdevice bus
  vfio/type1: Use mdev bus iommu_ops for IOMMU callbacks

 drivers/iommu/intel/Kconfig      |  13 ++++
 drivers/iommu/intel/Makefile     |   1 +
 drivers/iommu/intel/iommu.c      |  79 +++++--------------
 drivers/iommu/intel/siov.c       | 119 ++++++++++++++++++++++++++++
 drivers/iommu/iommu.c            |  16 ++--
 drivers/vfio/mdev/mdev_core.c    |  22 +-----
 drivers/vfio/mdev/mdev_driver.c  |   6 ++
 drivers/vfio/mdev/mdev_private.h |   1 -
 drivers/vfio/vfio_iommu_type1.c  | 128 +++----------------------------
 include/linux/intel-iommu.h      |  53 +++++++++++++
 include/linux/mdev.h             |  14 ----
 11 files changed, 236 insertions(+), 216 deletions(-)
 create mode 100644 drivers/iommu/intel/siov.c
```
#### [PATCH v5 00/15] follow_pfn and other iomap races
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
From patchwork Fri Oct 30 10:08:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11869017
Return-Path: <SRS0=2Kgf=EF=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 044FFC55178
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 10:08:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 952DE20825
	for <kvm@archiver.kernel.org>; Fri, 30 Oct 2020 10:08:40 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="Ghb99Upr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726171AbgJ3KIj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 30 Oct 2020 06:08:39 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:50300 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725876AbgJ3KIi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Oct 2020 06:08:38 -0400
Received: from mail-wr1-x443.google.com (mail-wr1-x443.google.com
 [IPv6:2a00:1450:4864:20::443])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 78B1FC0613D4
        for <kvm@vger.kernel.org>; Fri, 30 Oct 2020 03:08:38 -0700 (PDT)
Received: by mail-wr1-x443.google.com with SMTP id w1so5808402wrm.4
        for <kvm@vger.kernel.org>; Fri, 30 Oct 2020 03:08:38 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oyVNIJTztKiRHheNSQoUfnLRDya4SJw9IE1Vxl86s7c=;
        b=Ghb99UprNaKvFH2nWksoxxcjJMtuQ7UBnEvdaqQ2Xt27pEUza+n/3VR0T/qCjTsgrw
         pnOgvc7R/Us4ABF8mAoJmL0AdohhbtFrlQIZHCXvlxhr3ShQwZsUCHMdPOY4nT2sPNV2
         3n2sDDQkLekRqiTyUq6gRYR6GdNDanQomtL14=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oyVNIJTztKiRHheNSQoUfnLRDya4SJw9IE1Vxl86s7c=;
        b=Zg4aU0me6MVSMuMDj0oO9uYBc1qTZ1JndeuC7y/olMwamCd424zhIm9WNKCZKZ88f3
         VLQtTcnv8zwtHAemNJQbGHCceFV2mCqA97QkmMAfQ2XpEwa43yr7tFyT2bGeNPKs/lt2
         X25sP99UFsoKZeUU2M2ZOA34bdPWVtsDFU8oBuYQniNV7L5U9lv6XdfiyLxYeTM1+3UW
         SdjAFdMbfkcuThpoo4diGDCiryCTZZgP2cYL6PwJTQQqFHry/xfR2bkXcB7Im6cLj4Q5
         lo+5lkFCMR3byy8YBL0ypvfKPjLSYReJ9j7/t6RwVCo52QOI/MHIgV/EWeVNvOCarlsL
         /DCg==
X-Gm-Message-State: AOAM533Tu/3mLMGO0GcTSWbndnHJst7wXIlzj0bUwyEqoBJY26WiD8tM
        k2vRWXA6sfcLeXWExTHtWJi9dw==
X-Google-Smtp-Source: 
 ABdhPJw0H9VR4VRiDyzFX/cH5pwaV8XuDt6bBdU2cQb4UZ7RdbthoCu2zTbDyFJZiy6ZQIc6vY++Ww==
X-Received: by 2002:adf:f80a:: with SMTP id s10mr2082685wrp.275.1604052517093;
        Fri, 30 Oct 2020 03:08:37 -0700 (PDT)
Received: from phenom.ffwll.local ([2a02:168:57f4:0:efd0:b9e5:5ae6:c2fa])
        by smtp.gmail.com with ESMTPSA id
 v189sm4430947wmg.14.2020.10.30.03.08.35
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 30 Oct 2020 03:08:35 -0700 (PDT)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>,
        LKML <linux-kernel@vger.kernel.org>
Cc: kvm@vger.kernel.org, linux-mm@kvack.org,
        linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-media@vger.kernel.org,
        Daniel Vetter <daniel.vetter@ffwll.ch>
Subject: [PATCH v5 00/15] follow_pfn and other iomap races
Date: Fri, 30 Oct 2020 11:08:00 +0100
Message-Id: <20201030100815.2269-1-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.28.0
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

And the discussion that sparked this journey:

https://lore.kernel.org/dri-devel/20201007164426.1812530-1-daniel.vetter@ffwll.ch/

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
 .../media/common/videobuf2}/frame_vector.c    |  57 ++++------
 .../media/common/videobuf2/videobuf2-memops.c |   3 +-
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
 mm/memory.c                                   |  80 +++++++++++++-
 mm/nommu.c                                    |  27 ++++-
 security/Kconfig                              |  13 +++
 27 files changed, 360 insertions(+), 250 deletions(-)
 rename {mm => drivers/media/common/videobuf2}/frame_vector.c (84%)
 create mode 100644 include/media/frame_vector.h
```
