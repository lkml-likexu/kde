

#### [Patch v4 0/2] cgroup: KVM: New Encryption IDs cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Fri Jan  8 01:28:44 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12005529
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.6 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12ACDC433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:29:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D2BD62370D
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:29:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729718AbhAHB3k (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 20:29:40 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47056 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729637AbhAHB3k (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 20:29:40 -0500
Received: from mail-pl1-x64a.google.com (mail-pl1-x64a.google.com
 [IPv6:2607:f8b0:4864:20::64a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 51BF5C0612F9
        for <kvm@vger.kernel.org>; Thu,  7 Jan 2021 17:29:00 -0800 (PST)
Received: by mail-pl1-x64a.google.com with SMTP id 32so5240153plf.3
        for <kvm@vger.kernel.org>; Thu, 07 Jan 2021 17:29:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=UMAjKymYTdkz3wAZcW0ar3R52PKBGQEKlAaIA5W8JIc=;
        b=VkP6PA7UE9/mTi1zArELyLAnbHzFz9zmWujz5LV472BF45d0K+LOCwmZjUewY/CnlL
         5p08Q87+7zDNT2cVA3FY2+GOOoMq399zFzY5srDg8xvmG+GEeACkNboVC/dBsSlAKIP/
         Tr3OBHba424Ambsx8muEqncyjt6Rcs56TQ7LAs9usMK5Y9Bh6eRMyWUSTwYvbRufYK5d
         btoxwHV6D1NXm3145EaHKhuIZzt3l9zAbeetJaubCXA43wZx7xdjgpSDCQvPlIDI9czw
         inPhXzb6umDZQYFrj1YJPJqlloNBcrEflq1i7le/blUzlVf0QOo9X+I9bdi0wQXQk95l
         mGew==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=UMAjKymYTdkz3wAZcW0ar3R52PKBGQEKlAaIA5W8JIc=;
        b=Q9cZyZO4vcHrECOfYjnUZVduZBWSJKmqZfKuquIkow5Y4of9iZU81C9TUpr2Id9JNa
         zooW0iyXs5/B7c0JPLUMwyXB4gL9AUKlxNYUndDKR4gQRDzimr/qRNyE0qvHIbMRqbQF
         fwUFuANXArErpJ2XwXjdwIYIkhFvunMB1lihqZ/rsZBxEjCZfjnm2GwPdAM6VYnpwjKC
         wCp1syIBEOFDXS0nVe3AaQZIMAXs3xagTlodImjCwoh9QiXBDoBa/cRsbJRSV4JDTGks
         GgSwEalHDRi9r4zuQ6KC7+1nfT2rFZCDr8yPbuhR176xaJmYhL1FQLGp3153CbN7bChY
         M/2A==
X-Gm-Message-State: AOAM533/jWdJoQM/jn8IViXKdgZ89xbrDg11vpZXqcTk+PRpzDpqKTlk
        C4eUUiG8i2yGV4+gpeu71iQ3QBJNdQty
X-Google-Smtp-Source: 
 ABdhPJywgrK9jyMUDKCNz3m0wFnLKznB0xVRQSlCqGFsJdE96eJQiXYDVSV4yV82EEY/h+cPxsoBC4cwL/qw
Sender: "vipinsh via sendgmr" <vipinsh@vipinsh.kir.corp.google.com>
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:1ea0:b8ff:fe75:b885])
 (user=vipinsh job=sendgmr) by 2002:aa7:8813:0:b029:19d:cd3b:6f89 with SMTP id
 c19-20020aa788130000b029019dcd3b6f89mr1241032pfo.42.1610069339726; Thu, 07
 Jan 2021 17:28:59 -0800 (PST)
Date: Thu,  7 Jan 2021 17:28:44 -0800
Message-Id: <20210108012846.4134815-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.29.2.729.g45daf8777d-goog
Subject: [Patch v4 0/2] cgroup: KVM: New Encryption IDs cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: thomas.lendacky@amd.com, brijesh.singh@amd.com, jon.grimm@amd.com,
        eric.vantassell@amd.com, pbonzini@redhat.com, seanjc@google.com,
        tj@kernel.org, lizefan@huawei.com, hannes@cmpxchg.org,
        frankja@linux.ibm.com, borntraeger@de.ibm.com, corbet@lwn.net
Cc: joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, tglx@linutronix.de, mingo@redhat.com,
        bp@alien8.de, hpa@zytor.com, gingell@google.com,
        rientjes@google.com, dionnaglaze@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch adds a new cgroup controller, Encryption IDs, to track and
limit the usage of encryption IDs on a host.

AMD provides Secure Encrypted Virtualization (SEV) and SEV with
Encrypted State (SEV-ES) to encrypt the guest OS's memory using limited
number of Address Space Identifiers (ASIDs).

This limited number of ASIDs creates issues like SEV ASID starvation and
unoptimized scheduling in the cloud infrastucture.

In the RFC patch v1, I provided only SEV cgroup controller but based
on the feedback and discussion it became clear that this cgroup
controller can be extended to be used by Intel's Trusted Domain
Extension (TDX) and s390's protected virtualization Secure Execution IDs
(SEID)

This patch series provides a generic Encryption IDs controller with
tracking support of the SEV and SEV-ES ASIDs.

Changes in v4:
- The max value can be set lower than the current.
- Added SEV-ES support.

Changes in v3:
- Fixes a build error when CONFIG_CGROUP is disabled.

Changes in v2:
- Changed cgroup name from sev to encryption_ids.
- Replaced SEV specific names in APIs and documentations with generic
  encryption IDs.
- Providing 3 cgroup files per encryption ID type. For example in SEV,
  - encryption_ids.sev.stat (only in the root cgroup directory).
  - encryption_ids.sev.max
  - encryption_ids.sev.current

[1] https://lore.kernel.org/lkml/20200922004024.3699923-1-vipinsh@google.com/
[2] https://lore.kernel.org/lkml/20201208213531.2626955-1-vipinsh@google.com/
[3] https://lore.kernel.org/lkml/20201209205413.3391139-1-vipinsh@google.com/

Vipin Sharma (2):
  cgroup: svm: Add Encryption ID controller
  cgroup: svm: Encryption IDs cgroup documentation.

 .../admin-guide/cgroup-v1/encryption_ids.rst  | 108 +++++
 Documentation/admin-guide/cgroup-v2.rst       |  78 +++-
 arch/x86/kvm/svm/sev.c                        |  52 ++-
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/encryption_ids_cgroup.h         |  72 +++
 include/linux/kvm_host.h                      |   4 +
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/encryption_ids.c                | 422 ++++++++++++++++++
 9 files changed, 741 insertions(+), 14 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/encryption_ids.rst
 create mode 100644 include/linux/encryption_ids_cgroup.h
 create mode 100644 kernel/cgroup/encryption_ids.c
```
#### [RESEND v13 00/10] KVM: x86/pmu: Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Fri Jan  8 01:36:54 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12005537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D11E4C433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:45:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8D03E23380
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 01:45:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729738AbhAHBot (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 7 Jan 2021 20:44:49 -0500
Received: from mga09.intel.com ([134.134.136.24]:27993 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727634AbhAHBot (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 Jan 2021 20:44:49 -0500
IronPort-SDR: 
 Si3ZSqnHgNXJ5Oe/4GkdoR0rojBIxungBMAtXuvzP2j+9mAYkgLuTngLHBCciz2ctSHd/d9qAf
 KyMxNpLz/uCg==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="177672366"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="177672366"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 17:43:03 -0800
IronPort-SDR: 
 ON+qHfVnF5AMtTJnehcONNkXAML15iZdFZM1+reyav651reoeq5IukL1a3LNVcdYWcUqw20BY6
 aFnaxTtJmSAg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="379938010"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by orsmga008.jf.intel.com with ESMTP; 07 Jan 2021 17:42:59 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Borislav Petkov <bp@alien8.de>,
        "H . Peter Anvin" <hpa@zytor.com>, ak@linux.intel.com,
        wei.w.wang@intel.com, kan.liang@intel.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v13 00/10] KVM: x86/pmu: Guest Last Branch Recording Enabling
Date: Fri,  8 Jan 2021 09:36:54 +0800
Message-Id: <20210108013704.134985-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi geniuses,

Please help review this rebased version which enables the guest LBR.

We already upstreamed the guest LBR support in the host perf, please
check more details in each commit and feel free to test and comment.

v13->v13 RESEND Changelog:
- Reviewed-by: Andi Kleen <ak@linux.intel.com>

v12->v13 Changelog:
- remove perf patches since they're merged already;
- add a minor patch to refactor MSR_IA32_DEBUGCTLMSR set/get handler;
- add a minor patch to expose vmx_set_intercept_for_msr();
- add a minor patch to adjust features visibility via IA32_PERF_CAPABILITIES;
- spilt the big patch to three pieces (0004-0006) for better understanding and review;
- make the LBR_FMT exposure patch as the last step to enable guest LBR;

Previous:
https://lore.kernel.org/kvm/20201030035220.102403-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

with this patch set, the following error will be gone forever and cloud
developers can better understand their programs with less profiling overhead:

  $ perf record -b lbr ${WORKLOAD}
  or $ perf record --call-graph lbr ${WORKLOAD}
  Error:
  cycles: PMU Hardware doesn't support sampling/overflow-interrupts. Try 'perf stat'

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
  KVM: x86/vmx: Make vmx_set_intercept_for_msr() non-static
  KVM: x86/pmu: Use IA32_PERF_CAPABILITIES to adjust features visibility
  KVM: vmx/pmu: Clear PMU_CAP_LBR_FMT when guest LBR is disabled
  KVM: vmx/pmu: Create a guest LBR event when vcpu sets DEBUGCTLMSR_LBR
  KVM: vmx/pmu: Pass-through LBR msrs when the guest LBR event is ACTIVE
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
#### [RESEND PATCH 0/2] Add KVM support for bus lock debug exception
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Jan  8 06:49:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12005871
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AFB47C433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:48:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6DCCE233EA
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:48:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726492AbhAHGrO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 01:47:14 -0500
Received: from mga11.intel.com ([192.55.52.93]:46170 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725308AbhAHGrM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 01:47:12 -0500
IronPort-SDR: 
 DQ2QybVtsjonNiIzLRTyhVGu0sEAA7Ejydan9WBmhJOTwxl7tyifRy6rPaJ2M1Tg3m3/zu9Xq4
 In7RmBf1P1pw==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="174042914"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="174042914"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:46:31 -0800
IronPort-SDR: 
 pFyLMaRzv+WEH1QYcKgHuc5a0QooMt5F8ow42IdCIG/ZCJHP4uuDSS+8PTIsDFXinVo2nd3fBw
 fLM4sykFZ0zg==
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="380017263"
Received: from chenyi-pc.sh.intel.com ([10.239.159.137])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:46:29 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND PATCH 0/2] Add KVM support for bus lock debug exception
Date: Fri,  8 Jan 2021 14:49:22 +0800
Message-Id: <20210108064924.1677-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Any comment on this rebased version? I'd appreciate it if anyone has
time to review this short series.
---

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
MSR_IA32_DEBUTCTL.

The bus lock #DB exception can also be intercepted by the VMM and
identified through the bit 11 of the exit qualification at VM exit. The
bit 11 (DR6_BUS_LOCK) of DR6 register is introduced to indicate a bus
lock #DB exception. DR6_BUS_LOCK has formerly always been 1 and delivery
of a bus lock #DB clears it. The VMM should emulate the exceptions by
clearing the bit 11 of the guest DR6.

The kernel support patches for bus lock debug exception is available at
https://lore.kernel.org/lkml/20201124205245.4164633-1-fenghua.yu@intel.com/

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

---

Changelogs

RFC->v1:
- rebase on top of v5.11-rc1, no difference compared with the last version
- v1:https://lore.kernel.org/lkml/20201119092957.16940-1-chenyi.qiang@intel.com/

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
#### [RESEND v5 0/4] Add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Jan  8 06:52:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12005873
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 34EEFC433E0
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:50:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7DE5233FB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:50:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727086AbhAHGu2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 01:50:28 -0500
Received: from mga03.intel.com ([134.134.136.65]:46163 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725816AbhAHGu2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 01:50:28 -0500
IronPort-SDR: 
 mVTmcVtFsfjJJtw+aRseR0F9czXDVMfqlEuyNGBvZ7lQCRCY4bvLCxrJcaDmGtv751AkUIpfFp
 fPg9XqV78f0A==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="177651207"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="177651207"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:49:47 -0800
IronPort-SDR: 
 omaiBlQj54zYjHGgM7Rm1RYwdeAZc/4Esq6botwNKolqYYwitnetMeXoCYYLd+kP2U2e8YNBwd
 yFRgDAOKcjhA==
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="570659829"
Received: from chenyi-pc.sh.intel.com ([10.239.159.137])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:49:44 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v5 0/4] Add bus lock VM exit support
Date: Fri,  8 Jan 2021 14:52:37 +0800
Message-Id: <20210108065241.2062-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Resend a rebased version. Hope to receive your comments.
---

This patch series add the support for bus lock VM exit in KVM. It is a
sub-feature of bus lock detection. When it is enabled by the VMM, the
processor generates a "Bus Lock" VM exit following execution of an
instruction if the processor detects that one or more bus locks were
caused the instruction was being executed (due to either direct access
by the instruction or stuffed accesses like through A/D updates).

Bus lock VM exit will introduce a new modifier bit (bit 26) in
exit_reason field in VMCS which indicates bus lock VM exit is preempted
by a higher priority VM exit. The first patch is to apply Sean's
refactor for vcpu_vmx.exit_reason as a preparation patch for bus lock
VM exit support.

The second patch is the refactor for vcpu->run->flags. Bus lock VM exit
will introduce a new field in the flags to inform the userspace that
there's a bus lock detected in guest. It's also a preparation patch.

The third patch is the concrete enabling working for bus lock VM exit.
Add the support to set the capability to enable bus lock VM exit. The
current implementation is just exiting to userspace when handling the
bus lock detected in guest.

The detail of throttling policy in user space is still to be discussed.
We may enforce ratelimit on bus lock in guest, inject some sleep time,
or... We hope to get more ideas on this.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

---

Changelogs

v5->v5:
- rebase on top of v5.11-rc1
- no difference compared with the last version
- v5:https://lore.kernel.org/lkml/20201106090315.18606-1-chenyi.qiang@intel.com/

v4->v5:
- rebase on top on v5.10-rc2
- add preparation patch that reset the vcpu->run->flags at the beginning
  of the vcpu_run.(Suggested by Sean)
- set the KVM_RUN_BUS_LOCK for all bus lock exit to avoid checking both
  exit_reason and run->flags
- add the document to introduce the new kvm capability
  (KVM_CAP_X86_BUS_LOCK_EXIT)
- v4:https://lore.kernel.org/lkml/20201012033542.4696-1-chenyi.qiang@intel.com/

v3->v4:
- rebase on top of v5.9
- some code cleanup.
- v3:https://lore.kernel.org/lkml/20200910083751.26686-1-chenyi.qiang@intel.com/

v2->v3:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
- v2:https://lore.kernel.org/lkml/20200817033604.5836-1-chenyi.qiang@intel.com/ 

v1->v2:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.
- v1:https://lore.kernel.org/lkml/20200628085341.5107-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (3):
  KVM: X86: Reset the vcpu->run->flags at the beginning of vcpu_run
  KVM: VMX: Enable bus lock VM exit
  KVM: X86: Add the Document for KVM_CAP_X86_BUS_LOCK_EXIT

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 Documentation/virt/kvm/api.rst     |  45 ++++++++++++-
 arch/x86/include/asm/kvm_host.h    |   7 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 +++++++-----
 arch/x86/kvm/vmx/vmx.c             | 105 +++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  28 +++++++-
 include/uapi/linux/kvm.h           |   5 ++
 12 files changed, 214 insertions(+), 56 deletions(-)
```
#### [RESEND v5 0/4] Add bus lock VM exit support
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
From patchwork Fri Jan  8 06:55:26 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 12005875
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7DB7CC433DB
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:53:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2C9D82368A
	for <kvm@archiver.kernel.org>; Fri,  8 Jan 2021 06:53:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727145AbhAHGxR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 8 Jan 2021 01:53:17 -0500
Received: from mga02.intel.com ([134.134.136.20]:45891 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727077AbhAHGxP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 Jan 2021 01:53:15 -0500
IronPort-SDR: 
 evJpOUl1qTWeW74AbrMiSgXs3Jgn2nWA2VURMbK20uWg9hmWdFf1TF/1pOHBs4Ajc4/IRyxYQe
 j4wg1hGNJIUA==
X-IronPort-AV: E=McAfee;i="6000,8403,9857"; a="164628707"
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="164628707"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga101.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:52:31 -0800
IronPort-SDR: 
 PTIsgJy2yblsUzrrYnvAAM4Fzh0srEgdQnKRopIlH6MLJVfQheFDCBKRi6T1mA9AsebcHLBp10
 UQbWoV9K91Jw==
X-IronPort-AV: E=Sophos;i="5.79,330,1602572400";
   d="scan'208";a="570660387"
Received: from chenyi-pc.sh.intel.com ([10.239.159.137])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jan 2021 22:52:30 -0800
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [RESEND v5 0/4] Add bus lock VM exit support
Date: Fri,  8 Jan 2021 14:55:26 +0800
Message-Id: <20210108065530.2135-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Resend a rebased version. Hope to receive your comments.
---

This patch series add the support for bus lock VM exit in KVM. It is a
sub-feature of bus lock detection. When it is enabled by the VMM, the
processor generates a "Bus Lock" VM exit following execution of an
instruction if the processor detects that one or more bus locks were
caused the instruction was being executed (due to either direct access
by the instruction or stuffed accesses like through A/D updates).

Bus lock VM exit will introduce a new modifier bit (bit 26) in
exit_reason field in VMCS which indicates bus lock VM exit is preempted
by a higher priority VM exit. The first patch is to apply Sean's
refactor for vcpu_vmx.exit_reason as a preparation patch for bus lock
VM exit support.

The second patch is the refactor for vcpu->run->flags. Bus lock VM exit
will introduce a new field in the flags to inform the userspace that
there's a bus lock detected in guest. It's also a preparation patch.

The third patch is the concrete enabling working for bus lock VM exit.
Add the support to set the capability to enable bus lock VM exit. The
current implementation is just exiting to userspace when handling the
bus lock detected in guest.

The detail of throttling policy in user space is still to be discussed.
We may enforce ratelimit on bus lock in guest, inject some sleep time,
or... We hope to get more ideas on this.

Document for Bus Lock Detection is now available at the latest "Intel
Architecture Instruction Set Extensions Programming Reference".

Document Link:
https://software.intel.com/content/www/us/en/develop/download/intel-architecture-instruction-set-extensions-programming-reference.html

---

Changelogs

v5->v5:
- rebase on top of v5.11-rc1
- no difference compared with the last version
- v5:https://lore.kernel.org/lkml/20201106090315.18606-1-chenyi.qiang@intel.com/

v4->v5:
- rebase on top on v5.10-rc2
- add preparation patch that reset the vcpu->run->flags at the beginning
  of the vcpu_run.(Suggested by Sean)
- set the KVM_RUN_BUS_LOCK for all bus lock exit to avoid checking both
  exit_reason and run->flags
- add the document to introduce the new kvm capability
  (KVM_CAP_X86_BUS_LOCK_EXIT)
- v4:https://lore.kernel.org/lkml/20201012033542.4696-1-chenyi.qiang@intel.com/

v3->v4:
- rebase on top of v5.9
- some code cleanup.
- v3:https://lore.kernel.org/lkml/20200910083751.26686-1-chenyi.qiang@intel.com/

v2->v3:
- use a bitmap to get/set the capability of bus lock detection. we support
  exit and off mode currently.
- put the handle of exiting to userspace in vmx.c, thus no need to
  define a shadow to track vmx->exit_reason.bus_lock_detected.
- remove the vcpu->stats.bus_locks since every bus lock exits to userspace.
- v2:https://lore.kernel.org/lkml/20200817033604.5836-1-chenyi.qiang@intel.com/ 

v1->v2:
- resolve Vitaly's comment to introduce the KVM_EXIT_BUS_LOCK and a
  capability to enable it.
- add the support to exit to user space when handling bus locks.
- extend the vcpu->run->flags to indicate bus lock detected for other
  exit reasons when exiting to user space.
- v1:https://lore.kernel.org/lkml/20200628085341.5107-1-chenyi.qiang@intel.com/

---

Chenyi Qiang (3):
  KVM: X86: Reset the vcpu->run->flags at the beginning of vcpu_run
  KVM: VMX: Enable bus lock VM exit
  KVM: X86: Add the Document for KVM_CAP_X86_BUS_LOCK_EXIT

Sean Christopherson (1):
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union

 Documentation/virt/kvm/api.rst     |  45 ++++++++++++-
 arch/x86/include/asm/kvm_host.h    |   7 ++
 arch/x86/include/asm/vmx.h         |   1 +
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/include/uapi/asm/vmx.h    |   4 +-
 arch/x86/kvm/vmx/capabilities.h    |   6 ++
 arch/x86/kvm/vmx/nested.c          |  42 +++++++-----
 arch/x86/kvm/vmx/vmx.c             | 105 +++++++++++++++++++----------
 arch/x86/kvm/vmx/vmx.h             |  25 ++++++-
 arch/x86/kvm/x86.c                 |  28 +++++++-
 include/uapi/linux/kvm.h           |   5 ++
 12 files changed, 214 insertions(+), 56 deletions(-)
```
