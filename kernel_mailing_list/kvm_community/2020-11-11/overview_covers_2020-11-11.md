

#### [PATCH v15 0/9] Enable ptp_kvm for arm/arm64
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
From patchwork Wed Nov 11 06:22:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11896339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1C5EDC56202
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:22:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B2258207BB
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:22:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725975AbgKKGWi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 01:22:38 -0500
Received: from foss.arm.com ([217.140.110.172]:41674 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725867AbgKKGWh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 01:22:37 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id C44BB31B;
        Tue, 10 Nov 2020 22:22:35 -0800 (PST)
Received: from localhost.localdomain (entos-thunderx2-desktop.shanghai.arm.com
 [10.169.212.215])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 703063F6CF;
        Tue, 10 Nov 2020 22:22:29 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        nd@arm.com
Subject: [PATCH v15 0/9] Enable ptp_kvm for arm/arm64
Date: Wed, 11 Nov 2020 14:22:02 +0800
Message-Id: <20201111062211.33144-1-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, we offen use ntp (sync time with remote network clock)
to sync time in VM. But the precision of ntp is subject to network delay
so it's difficult to sync time in a high precision.

kvm virtual ptp clock (ptp_kvm) offers another way to sync time in VM,
as the remote clock locates in the host instead of remote network clock.
It targets to sync time between guest and host in virtualization
environment and in this way, we can keep the time of all the VMs running
in the same host in sync. In general, the delay of communication between
host and guest is quiet small, so ptp_kvm can offer time sync precision
up to in order of nanosecond. Please keep in mind that ptp_kvm just
limits itself to be a channel which transmit the remote clock from
host to guest and leaves the time sync jobs to an application, eg. chrony,
in usersapce in VM.

How ptp_kvm works:
After ptp_kvm initialized, there will be a new device node under
/dev called ptp%d. A guest userspace service, like chrony, can use this
device to get host walltime, sometimes also counter cycle, which depends
on the service it calls. Then this guest userspace service can use those
data to do the time sync for guest.
here is a rough sketch to show how kvm ptp clock works.

|----------------------------|              |--------------------------|
|       guest userspace      |              |          host            |
|ioctl -> /dev/ptp%d         |              |                          |
|       ^   |                |              |                          |
|----------------------------|              |                          |
|       |   | guest kernel   |              |                          |
|       |   V      (get host walltime/counter cycle)                   |
|      ptp_kvm -> hypercall - - - - - - - - - - ->hypercall service    |
|                         <- - - - - - - - - - - -                     |
|----------------------------|              |--------------------------|

1. time sync service in guest userspace call ptp device through /dev/ptp%d.
2. ptp_kvm module in guest recive this request then invoke hypercall to route
into host kernel to request host walltime/counter cycle.
3. ptp_kvm hypercall service in host response to the request and send data back.
4. ptp (not ptp_kvm) in guest copy the data to userspace.

This ptp_kvm implementation focuses itself to step 2 and 3 and step 2 works
in guest comparing step 3 works in host kernel.

change log:

from v14 to v15
        (1) enable ptp_kvm on arm32 guest, also ptp_kvm has been tested
on both arm64 and arm32 guest running on arm64 kvm host.
        (2) move arch-agnostic part of ptp_kvm.rst into timekeeping.rst.
        (3) rename KVM_CAP_ARM_PTP_KVM to KVM_CAP_PTP_KVM as it should be
arch agnostic.
        (4) add description for KVM_CAP_PTP_KVM in Documentation/virt/kvm/api.rst.
        (5) adjust dependency in Kconfig for ptp_kvm.
        (6) refine multi-arch process in driver/ptp/Makefile.
        (7) fix make pdfdocs htmldocs issue for ptp_kvm doc.
        (8) address other issues from comments in v14.
        (9) fold hypercall service of ptp_kvm as a function.
        (10) rebase to 5.10-rc3.

from v13 to v14
        (1) rebase code on 5.9-rc3.
        (2) add a document to introduce implementation of PTP_KVM on
arm64.
        (3) fix comments issue in hypercall.c.
        (4) export arm_smccc_1_1_get_conduit using EXPORT_SYMBOL_GPL.
        (5) fix make issue on x86 reported by kernel test robot.

from v12 to v13:
        (1) rebase code on 5.8-rc1.
        (2) this patch set base on 2 patches of 1/8 and 2/8 from Will Decon.
        (3) remove the change to ptp device code of extend getcrosststamp.
        (4) remove the mechanism of letting user choose the counter type in
ptp_kvm for arm64.
        (5) add virtual counter option in ptp_kvm service to let user choose
the specific counter explicitly.

from v11 to v12:
        (1) rebase code on 5.7-rc6 and rebase 2 patches from Will Decon
including 1/11 and 2/11. as these patches introduce discover mechanism of
vendor smccc service.
        (2) rebase ptp_kvm hypercall service from standard smccc to vendor
smccc and add ptp_kvm to vendor smccc service discover mechanism.
        (3) add detail of why we need ptp_kvm and how ptp_kvm works in cover
letter.

from v10 to v11:
        (1) rebase code on 5.7-rc2.
        (2) remove support for arm32, as kvm support for arm32 will be
removed [1]
        (3) add error report in ptp_kvm initialization.

from v9 to v10:
        (1) change code base to v5.5.
        (2) enable ptp_kvm both for arm32 and arm64.
        (3) let user choose which of virtual counter or physical counter
should return when using crosstimestamp mode of ptp_kvm for arm/arm64.
        (4) extend input argument for getcrosstimestamp API.

from v8 to v9:
        (1) move ptp_kvm.h to driver/ptp/
        (2) replace license declaration of ptp_kvm.h the same with other
header files in the same directory.

from v7 to v8:
        (1) separate adding clocksource id for arm_arch_counter as a
single patch.
        (2) update commit message for patch 4/8.
        (3) refine patch 7/8 and patch 8/8 to make them more independent.

from v5 to v6:
        (1) apply Mark's patch[4] to get SMCCC conduit.
        (2) add mechanism to recognize current clocksource by add
clocksouce_id value into struct clocksource instead of method in patch-v5.
        (3) rename kvm_arch_ptp_get_clock_fn into
kvm_arch_ptp_get_crosststamp.

from v4 to v5:
        (1) remove hvc delay compensasion as it should leave to userspace.
        (2) check current clocksource in hvc call service.
        (3) expose current clocksource by adding it to
system_time_snapshot.
        (4) add helper to check if clocksource is arm_arch_counter.
        (5) rename kvm_ptp.c to ptp_kvm_common.c

from v3 to v4:
        (1) fix clocksource of ptp_kvm to arch_sys_counter.
        (2) move kvm_arch_ptp_get_clock_fn into arm_arch_timer.c
        (3) subtract cntvoff before return cycles from host.
        (4) use ktime_get_snapshot instead of getnstimeofday and
get_current_counterval to return time and counter value.
        (5) split ktime and counter into two 32-bit block respectively
to avoid Y2038-safe issue.
        (6) set time compensation to device time as half of the delay of
hvc call.
        (7) add ARM_ARCH_TIMER as dependency of ptp_kvm for
arm64.

from v2 to v3:
        (1) fix some issues in commit log.
        (2) add some receivers in send list.

from v1 to v2:
        (1) move arch-specific code from arch/ to driver/ptp/
        (2) offer mechanism to inform userspace if ptp_kvm service is
available.
        (3) separate ptp_kvm code for arm64 into hypervisor part and
guest part.
        (4) add API to expose monotonic clock and counter value.
        (5) refine code: remove no necessary part and reconsitution.

[1] https://patchwork.kernel.org/cover/11373351/


Jianyong Wu (6):
  ptp: Reorganize ptp_kvm module to make it arch-independent.
  clocksource: Add clocksource id for arm arch counter
  arm64/kvm: Add hypercall service for kvm ptp.
  ptp: arm/arm64: Enable ptp_kvm for arm/arm64
  doc: add ptp_kvm introduction for arm64 support
  arm64: Add kvm capability check extension for ptp_kvm

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (2):
  arm64: Probe for the presence of KVM hypervisor
  arm/arm64: KVM: Advertise KVM UID to guests via SMCCC

 Documentation/virt/kvm/api.rst              |  9 ++
 Documentation/virt/kvm/arm/index.rst        |  1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst      | 29 +++++++
 Documentation/virt/kvm/timekeeping.rst      | 35 ++++++++
 arch/arm/kernel/setup.c                     |  1 +
 arch/arm64/kernel/setup.c                   |  1 +
 arch/arm64/kvm/arm.c                        |  1 +
 arch/arm64/kvm/hypercalls.c                 | 88 +++++++++++++++++--
 drivers/clocksource/arm_arch_timer.c        | 30 +++++++
 drivers/firmware/smccc/smccc.c              | 37 ++++++++
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  2 +
 drivers/ptp/ptp_kvm.h                       | 11 +++
 drivers/ptp/ptp_kvm_arm.c                   | 44 ++++++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 85 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 95 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 60 +++++++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  2 +
 kernel/time/timekeeping.c                   |  1 +
 23 files changed, 488 insertions(+), 77 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/ptp/ptp_kvm.h
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
```
#### [RFC PATCH 0/3] Get supported_xss ready for XSS dependent
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed Nov 11 06:41:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11896409
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BC8EBC388F9
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:31:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 669F620786
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 06:31:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725925AbgKKGb1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 01:31:27 -0500
Received: from mga17.intel.com ([192.55.52.151]:43536 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725867AbgKKGb0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 11 Nov 2020 01:31:26 -0500
IronPort-SDR: 
 UYNH1Sofp/fadFCUhHXR3Az/xoiNxZj6JYiMe35rf/vX08CWEHMOIJ0r1yfob2NwWJShw/4DGT
 WhCa+xnv6OMA==
X-IronPort-AV: E=McAfee;i="6000,8403,9801"; a="149951492"
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="149951492"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 Nov 2020 22:31:25 -0800
IronPort-SDR: 
 R095N3SAab1vQKKPDMgSJRzioTZQanof05ufeePtVKJRu1W+vHAiNc6IN+nYtbs5J2L5ZcJcUq
 Vnx6t3emNE0w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,468,1596524400";
   d="scan'208";a="323167572"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.156])
  by orsmga003.jf.intel.com with ESMTP; 10 Nov 2020 22:31:23 -0800
From: Yang Weijiang <weijiang.yang@intel.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [RFC PATCH 0/3] Get supported_xss ready for XSS dependent
Date: Wed, 11 Nov 2020 14:41:48 +0800
Message-Id: <20201111064151.1090-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Although supported_xss was added long time ago, yet it doesn't get ready for
XSS dependent new features usage, e.g., when guest update XSS MSRs, it's
necessary to update guest CPUID to reflect the correct info. So post this
patchset to get things ready, or at least as a hint to maintainers that
there're still a few things left before support feature bits in XSS.

Also added a few helpers to facilitate new features development. This part
of code originates from CET KVM patchset, with more and more new features
dependent on this part, post this patchset ahead of them.

Sean Christopherson (2):
  KVM: x86: Add helpers for {set|clear} bits in supported_xss
  KVM: x86: Load guest fpu state when accessing MSRs managed by XSAVES

Yang Weijiang (1):
  KVM: x86: Refresh CPUID when guest modifies MSR_IA32_XSS

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            | 21 ++++++++++++--
 arch/x86/kvm/vmx/vmx.c          | 22 +++++++++++++++
 arch/x86/kvm/x86.c              | 50 +++++++++++++++++++++++++++++++--
 4 files changed, 88 insertions(+), 6 deletions(-)
```
#### [PATCH v2 00/11] KVM: selftests: Cleanups, take 2
##### From: Andrew Jones <drjones@redhat.com>

```c
From patchwork Wed Nov 11 12:26:25 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11897503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-3.9 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 39972C388F9
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 12:26:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BBE1E20795
	for <kvm@archiver.kernel.org>; Wed, 11 Nov 2020 12:26:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IMch+M9Z"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726142AbgKKM0r (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 11 Nov 2020 07:26:47 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:43426 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725882AbgKKM0r (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 11 Nov 2020 07:26:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1605097605;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=5hWfLU3ylTgBjCk3h+FCJUcXrzNoR1rBAbf42gojaGw=;
        b=IMch+M9Zq0hI8w6/T1bnsqEOTlo9/UfQMf1H8fgTQE4CdnVVBKC140bk5KBuOtHuOpRj9P
        A7egaR4FFBBgjmZEddgE9jPPG98GIc9DfpNN1nizy05VMDwxXLc4mrLd1jcMO6lxcIi01c
        AAMsZRlYAbSXTeJrrnpgeoeLhtJ4F5w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-373-ebeZXl20NE2TTCjQXI9s6w-1; Wed, 11 Nov 2020 07:26:43 -0500
X-MC-Unique: ebeZXl20NE2TTCjQXI9s6w-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A2E5B879523;
        Wed, 11 Nov 2020 12:26:42 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.40.193.216])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F3D6A10013BD;
        Wed, 11 Nov 2020 12:26:37 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        bgardon@google.com, peterx@redhat.com
Subject: [PATCH v2 00/11] KVM: selftests: Cleanups, take 2
Date: Wed, 11 Nov 2020 13:26:25 +0100
Message-Id: <20201111122636.73346-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series attempts to clean up demand_paging_test, dirty_log_perf_test,
and dirty_log_test by factoring out common code, creating some new API
along the way. It also splits include/perf_test_util.h into a more
conventional header and source pair.

I've tested on x86 and AArch64 (one config each), but not s390x.

v2:
  - Use extra_mem instead of per-vcpu mem for the test mem in
    demand_paging_test and dirty_log_perf_test [Ben]

  - Couple more cleanups, like adding perf_test_destroy_vm()
    to balance create/destroy of a perf test vm [drew]

  - Added new patches [drew]:

    - Since dirty_log_perf_test works fine on AArch64,
      "KVM: selftests: Also build dirty_log_perf_test on AArch64"

    - More cleanup of redundant code,
      "KVM: selftests: x86: Set supported CPUIDs on default VM"

    - Keep test skipping consistent,
      "KVM: selftests: Make test skipping consistent"

I definitely want to get x86 people's review on "KVM: selftests: x86:
Set supported CPUIDs on default VM" to be sure it's OK to do that.

Thanks,
drew


Andrew Jones (11):
  KVM: selftests: Update .gitignore
  KVM: selftests: Remove deadcode
  KVM: selftests: Factor out guest mode code
  KVM: selftests: Make vm_create_default common
  KVM: selftests: Introduce vm_create_[default_]_with_vcpus
  KVM: selftests: dirty_log_test: Remove create_vm
  KVM: selftests: Use vm_create_with_vcpus in create_vm
  KVM: selftests: Implement perf_test_util more conventionally
  KVM: selftests: Also build dirty_log_perf_test on AArch64
  KVM: selftests: x86: Set supported CPUIDs on default VM
  KVM: selftests: Make test skipping consistent

 tools/testing/selftests/kvm/.gitignore        |   2 +-
 tools/testing/selftests/kvm/Makefile          |   3 +-
 .../selftests/kvm/demand_paging_test.c        | 118 +++--------
 .../selftests/kvm/dirty_log_perf_test.c       | 183 ++++--------------
 tools/testing/selftests/kvm/dirty_log_test.c  | 182 +++++------------
 .../selftests/kvm/include/guest_modes.h       |  21 ++
 .../testing/selftests/kvm/include/kvm_util.h  |  42 +++-
 .../selftests/kvm/include/perf_test_util.h    | 171 ++--------------
 .../selftests/kvm/lib/aarch64/processor.c     |  17 --
 tools/testing/selftests/kvm/lib/guest_modes.c |  70 +++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  67 ++++++-
 .../selftests/kvm/lib/perf_test_util.c        | 134 +++++++++++++
 .../selftests/kvm/lib/s390x/processor.c       |  22 ---
 .../selftests/kvm/lib/x86_64/processor.c      |  32 ---
 .../selftests/kvm/set_memory_region_test.c    |   2 -
 .../kvm/x86_64/cr4_cpuid_sync_test.c          |   1 -
 .../testing/selftests/kvm/x86_64/debug_regs.c |   1 -
 .../testing/selftests/kvm/x86_64/evmcs_test.c |   2 -
 .../selftests/kvm/x86_64/kvm_pv_test.c        |   4 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c |   2 -
 .../testing/selftests/kvm/x86_64/state_test.c |   1 -
 .../selftests/kvm/x86_64/svm_vmcall_test.c    |   1 -
 .../selftests/kvm/x86_64/tsc_msrs_test.c      |   1 -
 .../selftests/kvm/x86_64/user_msr_test.c      |   7 +-
 .../kvm/x86_64/vmx_apic_access_test.c         |   1 -
 .../kvm/x86_64/vmx_close_while_nested_test.c  |   1 -
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c |   1 -
 .../kvm/x86_64/vmx_preemption_timer_test.c    |  15 +-
 .../kvm/x86_64/vmx_set_nested_state_test.c    |  21 ++
 .../kvm/x86_64/vmx_tsc_adjust_test.c          |   1 -
 30 files changed, 499 insertions(+), 627 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/guest_modes.h
 create mode 100644 tools/testing/selftests/kvm/lib/guest_modes.c
 create mode 100644 tools/testing/selftests/kvm/lib/perf_test_util.c
```
