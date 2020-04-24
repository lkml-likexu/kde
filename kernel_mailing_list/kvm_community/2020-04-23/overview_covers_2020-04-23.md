

#### [PATCH 00/13] KVM: x86: Event fixes and cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Thu Apr 23 02:25:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11504893
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5AAFF81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 02:27:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 491852080D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 02:27:21 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726454AbgDWCZz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 22 Apr 2020 22:25:55 -0400
Received: from mga05.intel.com ([192.55.52.43]:43420 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725781AbgDWCZy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 22 Apr 2020 22:25:54 -0400
IronPort-SDR: 
 B6yYB+czKgIza8u3p+/gOOdQgnLyCR5cNN3u4OjX10pwcWGNqnyUVHrWgMNRNXhy3CEUMSDe0R
 Iz1tHWhm8N3Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Apr 2020 19:25:54 -0700
IronPort-SDR: 
 TAOiyz6URTSwcAdFpQTxkoZlu8HG4C1DvtPgwh6a5fmqoAhwOgfIkxG96kZe2au79BPHH6yisI
 AP5IWivucX7g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,305,1583222400";
   d="scan'208";a="259273930"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 22 Apr 2020 19:25:54 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Oliver Upton <oupton@google.com>,
        Peter Shier <pshier@google.com>
Subject: [PATCH 00/13] KVM: x86: Event fixes and cleanup
Date: Wed, 22 Apr 2020 19:25:37 -0700
Message-Id: <20200423022550.15113-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.26.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Most of this series only really affects nVMX, but there are a few x86
changes sprinkled in.

Patches 1 and 2 are alternative fixes[1][2] for bugs where a #DB destined
for L2 is dropped because a lower priority event, e.g. VMX preemption
timer, is serviced and triggers VM-Exit, and where correctly handling the
#DB can result in the preemption timer being dropped.

Patch 3 fixes a semi-theoretical bug.  I've been intermittently observing
failures when running the preemption timer unit test in L1, but have never
been able to consistently reproduce the bug.  I suspect the issue is
KVM_REQ_EVENT being lost, but can't really confirm this is the case due to
lack of a reproducer.

Patches 4-7 are cleanup/refactoring to fix non-exiting NMI/INTR priority
bugs (similar to above) in patch 8.  Although patch 8 is technically a bug
fix, I don't think it's stable material (no sane L1 will notice), which is
why I prioritized (da-dum ching) a clean implementation over an easily
backported patch (a single patch would have been ugly).

Patch 9 fixes a similar issue with SMI priority, and again is probably not
stable material.

Patch 10 addresses a gap in WARN coverage that's effectively introduced
by the bug fix in patch 1.

Patches 11 and 12 replace the extra call to check_nested_events() with a
more precise hack-a-fix.  This is a very small step towards a pipe dream
of processing each event class exactly once per run loop (more below).

Patch 13 is a random optimization that caught my eye when starting at this
code over and over.


I really, really dislike KVM's event handling flow.  In the (distant)
future I'd love to rework the event injection to process each event
exactly once per loop, as opposed to the current behavior where
check_nested_events() can be called at least twice, if not more depending
on blocking behavior.  That would make it much cleaner to correctly handle
event prioritization and likely to maintain the code, but getting there is
a significant rework with a fair number of scary changes.

[1] https://lkml.kernel.org/r/20200414000946.47396-2-jmattson@google.com
[2] https://lkml.kernel.org/r/20200414000946.47396-1-jmattson@google.com

Sean Christopherson (13):
  KVM: nVMX: Preserve exception priority irrespective of exiting
    behavior
  KVM: nVMX: Open a window for pending nested VMX preemption timer
  KVM: x86: Set KVM_REQ_EVENT if run is canceled with req_immediate_exit
    set
  KVM: x86: Make return for {interrupt_nmi}_allowed() a bool instead of
    int
  KVM: nVMX: Move nested_exit_on_nmi() to nested.h
  KVM: nVMX: Report NMIs as allowed when in L2 and Exit-on-NMI is set
  KVM: VMX: Split out architectural interrupt/NMI blocking checks
  KVM: nVMX: Preserve IRQ/NMI priority irrespective of exiting behavior
  KVM: nVMX: Prioritize SMI over nested IRQ/NMI
  KVM: x86: WARN on injected+pending exception even in nested case
  KVM: VMX: Use vmx_interrupt_blocked() directly from vmx_handle_exit()
  KVM: x86: Replace late check_nested_events() hack with more precise
    fix
  KVM: VMX: Use vmx_get_rflags() to query RFLAGS in
    vmx_interrupt_blocked()

 arch/x86/include/asm/kvm_host.h |  6 ++-
 arch/x86/kvm/svm/svm.c          | 10 ++--
 arch/x86/kvm/vmx/nested.c       | 42 +++++++++++------
 arch/x86/kvm/vmx/nested.h       |  5 ++
 arch/x86/kvm/vmx/vmx.c          | 84 +++++++++++++++++++++------------
 arch/x86/kvm/vmx/vmx.h          |  2 +
 arch/x86/kvm/x86.c              | 32 +++++--------
 7 files changed, 113 insertions(+), 68 deletions(-)
```
#### [PATCH v10 00/11] Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Thu Apr 23 08:14:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11505251
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8793E912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 08:17:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F4EA21655
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 08:17:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726398AbgDWIRh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 04:17:37 -0400
Received: from mga18.intel.com ([134.134.136.126]:57581 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725863AbgDWIRh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Apr 2020 04:17:37 -0400
IronPort-SDR: 
 V/s19IIxrtlQ44oziXriPiagTkyKmUyZoz82VyXJ0OG79JLbXY+QLHZpcPvwnsTUeNk5Z8Bpzg
 CuCXVsbWAv3Q==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Apr 2020 01:17:36 -0700
IronPort-SDR: 
 YOkfRaMmuAkWVr0GdonnkthHPBZU+8vdCN6EUZDW3i327Pb/nKOw68KgVPLm6xCDEzlmEd+6t4
 CJiT6hxdXbdA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,306,1583222400";
   d="scan'208";a="255910029"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga003.jf.intel.com with ESMTP; 23 Apr 2020 01:17:33 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, wei.w.wang@intel.com,
        ak@linux.intel.com, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v10 00/11] Guest Last Branch Recording Enabling
Date: Thu, 23 Apr 2020 16:14:01 +0800
Message-Id: <20200423081412.164863-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Please help review your interesting parts in this stable version,
e.g. the first five patches involve the perf event subsystem
and the sixth patch concerns the KVM userspace interface.

v9->v10 Changelog:
- new patch (0002) to refactor hw->idx checks and cleanup for host perf;
- refine comments in guest LBR constraint patch and rename functions;
- still ack LBRS_FROZEN for guest LBR event in the intel_pmu_ack_status();
- add more checks before enabling LBR in the kvm_vm_ioctl_enable_cap();
- add pmu_ops->deliver_pmi to clear LBR enable bit for guest debugctl_msr;
- use vmx_supported_perf_capabilities() to expose PDCM via kvm_cpu_cap*();

You may check more details in each commit.

Previous:
https://lore.kernel.org/kvm/20200313021616.112322-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

The userspace could configure whether it's enabled or not for each
guest via vm_ioctl KVM_CAP_X86_GUEST_LBR. As a first step, a guest
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

Like Xu (8):
  perf/x86/core: Refactor hw->idx checks and cleanup
  perf/x86/lbr: Add interface to get basic information about LBR stack
  perf/x86: Add constraint to create guest LBR event without hw counter
  perf/x86: Keep LBR stack unchanged in host context for guest LBR event
  KVM: x86: Add KVM_CAP_X86_GUEST_LBR to dis/enable LBR from user-space
  KVM: x86/pmu: Add LBR feature emulation via guest LBR event
  KVM: x86/pmu: Release guest LBR event via vPMU lazy release mechanism
  KVM: x86: Expose MSR_IA32_PERF_CAPABILITIES for LBR record format

Wei Wang (3):
  perf/x86: Fix variable type for LBR registers
  KVM: x86/pmu: Tweak kvm_pmu_get_msr to pass 'struct msr_data' in
  KVM: x86: Remove the common trap handler of the MSR_IA32_DEBUGCTLMSR

 Documentation/virt/kvm/api.rst    |  28 +++
 arch/x86/events/core.c            |  26 ++-
 arch/x86/events/intel/core.c      | 102 ++++++----
 arch/x86/events/intel/lbr.c       |  56 +++++-
 arch/x86/events/perf_event.h      |  18 +-
 arch/x86/include/asm/kvm_host.h   |  14 ++
 arch/x86/include/asm/perf_event.h |  28 ++-
 arch/x86/kvm/pmu.c                |  27 ++-
 arch/x86/kvm/pmu.h                |  17 +-
 arch/x86/kvm/svm/pmu.c            |   7 +-
 arch/x86/kvm/vmx/capabilities.h   |  15 ++
 arch/x86/kvm/vmx/pmu_intel.c      | 301 ++++++++++++++++++++++++++++--
 arch/x86/kvm/vmx/vmx.c            |  11 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  34 ++--
 include/linux/perf_event.h        |   7 +
 include/uapi/linux/kvm.h          |   1 +
 kernel/events/core.c              |   7 -
 18 files changed, 603 insertions(+), 98 deletions(-)
```
#### [PATCH v2 0/5] KVM: VMX: Tscdeadline timer emulation fastpath
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c
From patchwork Thu Apr 23 09:01:42 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11505313
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5EA65112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:02:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 447602084D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:02:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Nt7Qw0nr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726587AbgDWJB6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 05:01:58 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:49208 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725854AbgDWJB6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Apr 2020 05:01:58 -0400
Received: from mail-pj1-x1044.google.com (mail-pj1-x1044.google.com
 [IPv6:2607:f8b0:4864:20::1044])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E6E93C03C1AF;
        Thu, 23 Apr 2020 02:01:57 -0700 (PDT)
Received: by mail-pj1-x1044.google.com with SMTP id a7so2244237pju.2;
        Thu, 23 Apr 2020 02:01:57 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=lqQCA6uU2hlxAoFKS3Zl8BZd61e4Kf8xSgvVI/JGqC4=;
        b=Nt7Qw0nrmkNGLxtXMTEV5uYLLipfjl9h0i6pjbj/rQ5IrdUvVnE05yKMFte/E8X3gA
         v1ALEt/A9Q3qCfCyONPh2D2n7JlxUthelFPP/npXXozrmg46aM5BCpSXcZ14+D8PYNNR
         ohXxRhnTfXw0rOmY/i2f5QlSPSUFKmNG69HZS9PwS0uE5UeTFpk4VpcEEkHp6bbw/wgM
         32emtYxbXl6ZqkHeHp/U1nHsBtvbjrEd7nJVNWvC+AIB5ZRLew6yut1rqRwSsOqeDjx8
         t2Mdo33+eOkOxS+01/D29GVQhpBosV42glNCcF6dOb6+/Hl02IGJNxmKdT0d1lIFOX3i
         8JfA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=lqQCA6uU2hlxAoFKS3Zl8BZd61e4Kf8xSgvVI/JGqC4=;
        b=I142TcMwprwhQiG1lFuhbdY6bm9vB5KSwu8j3a+baf5sfANIP4GLBhkmcw+8y4IWws
         Mi2LC+1qf3Jsy0vfd67ht2mm391z14xUIDw+CvTt67hvIH0zOV1tNyFwbQ7MNw66h8Wf
         2BVoJv0rf2PT0wFEP7RgY95BSZHf9JJdy7sXHu6RGV8dTAIo1UUNNRg4Pv8GBn0amHs8
         Ls0LAkh7jBhGMgaiOyXpr8mA40e9YEJuMHEy2KDWn4WtBf8GkmpM1D8B5tKRk4bvlUsN
         eMfre/7AtzXX4E7kkXaqns3+n8F+OTgmCsWMudx9sCSArTKIE968rEvADfvVHzg4R8Tz
         pImA==
X-Gm-Message-State: AGi0PubjSdAmTbkbgneXDR/rPcZmtSFeTj8Rh8SD2A67HMiQMTLAdMCO
        STBymervjSQD0fnb6o96tMGBQApI
X-Google-Smtp-Source: 
 APiQypLV0DFMc3aCMJ+cJGdiGtokrQ/ZJbvaGZyluabiyAKYwRb9+7mcocgS5ufUqx/Tv5wjJUYD5g==
X-Received: by 2002:a17:902:7886:: with SMTP id
 q6mr2823565pll.237.1587632517257;
        Thu, 23 Apr 2020 02:01:57 -0700 (PDT)
Received: from localhost.localdomain ([103.7.29.6])
        by smtp.googlemail.com with ESMTPSA id
 w28sm1574204pgc.26.2020.04.23.02.01.54
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 23 Apr 2020 02:01:56 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Haiwei Li <lihaiwei@tencent.com>
Subject: [PATCH v2 0/5] KVM: VMX: Tscdeadline timer emulation fastpath
Date: Thu, 23 Apr 2020 17:01:42 +0800
Message-Id: <1587632507-18997-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

IPI and Timer cause the main vmexits in cloud environment observation, 
after single target IPI fastpath, let's optimize tscdeadline timer 
latency by introducing tscdeadline timer emulation fastpath, it will 
skip various KVM related checks when possible. i.e. after vmexit due 
to tscdeadline timer emulation, handle it and vmentry immediately 
without checking various kvm stuff when possible. 

Testing on SKX Server.

cyclictest in guest(w/o mwait exposed, adaptive advance lapic timer is default -1):

5632.75ns -> 4559.25ns, 19%

kvm-unit-test/vmexit.flat:

w/o APICv, w/o advance timer:
tscdeadline_immed: 4780.75 -> 3851    19.4%
tscdeadline:       7474    -> 6528.5  12.7%

w/o APICv, w/ adaptive advance timer default -1:
tscdeadline_immed: 4845.75 -> 3930.5  18.9%
tscdeadline:       6048    -> 5871.75    3%

w/ APICv, w/o avanced timer:
tscdeadline_immed: 2919    -> 2467.75 15.5%
tscdeadline:       5661.75 -> 5188.25  8.4%

w/ APICv, w/ adaptive advance timer default -1:
tscdeadline_immed: 3018.5  -> 2561    15.2%
tscdeadline:       4663.75 -> 4537     2.7%

Tested-by: Haiwei Li <lihaiwei@tencent.com>
Cc: Haiwei Li <lihaiwei@tencent.com>

v1 -> v2:
 * move more stuff from vmx.c to lapic.c
 * remove redundant checking
 * check more conditions to bail out CONT_RUN
 * not break AMD
 * not handle LVTT sepecial
 * cleanup codes

Wanpeng Li (5):
  KVM: LAPIC: Introduce interrupt delivery fastpath
  KVM: X86: Introduce need_cancel_enter_guest helper
  KVM: VMX: Introduce generic fastpath handler
  KVM: X86: TSCDEADLINE MSR emulation fastpath
  KVM: VMX: Handle preemption timer fastpath

 arch/x86/include/asm/kvm_host.h |  2 +
 arch/x86/kvm/lapic.c            | 98 +++++++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/lapic.h            |  2 +
 arch/x86/kvm/svm/avic.c         |  5 +++
 arch/x86/kvm/svm/svm.c          |  1 +
 arch/x86/kvm/svm/svm.h          |  1 +
 arch/x86/kvm/vmx/vmx.c          | 69 ++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c              | 42 ++++++++++++++----
 arch/x86/kvm/x86.h              |  1 +
 9 files changed, 199 insertions(+), 22 deletions(-)
```
#### [PATCH v2 00/10] s390x: smp: Improve smp code part 2
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Thu Apr 23 09:10:03 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11505339
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72E33112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:10:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 63C122075A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 09:10:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726474AbgDWJK1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 05:10:27 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:23356 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725854AbgDWJK1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 23 Apr 2020 05:10:27 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 03N98pF5066305
        for <kvm@vger.kernel.org>; Thu, 23 Apr 2020 05:10:25 -0400
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 30k7rkrsew-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 23 Apr 2020 05:10:25 -0400
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 23 Apr 2020 10:10:17 +0100
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 23 Apr 2020 10:10:14 +0100
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 03N9AJZ566912396
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 23 Apr 2020 09:10:19 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 960AB4C040;
        Thu, 23 Apr 2020 09:10:19 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DC5424C066;
        Thu, 23 Apr 2020 09:10:18 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu, 23 Apr 2020 09:10:18 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com
Subject: [PATCH v2 00/10] s390x: smp: Improve smp code part 2
Date: Thu, 23 Apr 2020 05:10:03 -0400
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20042309-0028-0000-0000-000003FD7B07
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20042309-0029-0000-0000-000024C3455C
Message-Id: <20200423091013.11587-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.676
 definitions=2020-04-23_07:2020-04-22,2020-04-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 clxscore=1015 mlxscore=0 mlxlogscore=518 adultscore=0
 bulkscore=0 impostorscore=0 malwarescore=0 suspectscore=0 spamscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004230070
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's continue cleaning up the smp test and smp related functions.

We add:
   * Test for external/emergency calls after reset
   * Test SIGP restart while running
   * SIGP stop and store status while running
   * CR testing on reset

We fix:
   * Proper check for sigp completion
   * smp_cpu_setup_state() loop and return address in r14


GIT: https://github.com/frankjaa/kvm-unit-tests/tree/smp_cleanup2

v2:
	* Added some rev-bys and acks
	* Explicitly stop and start cpu before hot restart test

Janosch Frank (10):
  s390x: smp: Test all CRs on initial reset
  s390x: smp: Dirty fpc before initial reset test
  s390x: smp: Test stop and store status on a running and stopped cpu
  s390x: smp: Test local interrupts after cpu reset
  s390x: smp: Loop if secondary cpu returns into cpu setup again
  s390x: smp: Remove unneeded cpu loops
  s390x: smp: Use full PSW to bringup new cpu
  s390x: smp: Wait for sigp completion
  s390x: smp: Add restart when running test
  s390x: Fix library constant definitions

 lib/s390x/asm/arch_def.h |  8 ++--
 lib/s390x/smp.c          | 10 +++++
 lib/s390x/smp.h          |  1 +
 s390x/cstart64.S         |  5 ++-
 s390x/smp.c              | 94 ++++++++++++++++++++++++++++++++++++----
 5 files changed, 105 insertions(+), 13 deletions(-)
```
#### [PATCH kvmtool v4 0/5] Add CFI flash emulation
##### From: Andre Przywara <andre.przywara@arm.com>

```c
From patchwork Thu Apr 23 17:38:39 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?q?Andr=C3=A9_Przywara?=
 <andre.przywara@arm.com>
X-Patchwork-Id: 11506127
Return-Path: <SRS0=WUL8=6H=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C6D981
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 17:39:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4E8A420857
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 23 Apr 2020 17:39:04 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729981AbgDWRjD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 23 Apr 2020 13:39:03 -0400
Received: from foss.arm.com ([217.140.110.172]:44742 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729802AbgDWRjD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 23 Apr 2020 13:39:03 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 2AC7430E;
        Thu, 23 Apr 2020 10:39:02 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 B996C3F68F;
        Thu, 23 Apr 2020 10:39:00 -0700 (PDT)
From: Andre Przywara <andre.przywara@arm.com>
To: Will Deacon <will@kernel.org>,
        Julien Thierry <julien.thierry.kdev@gmail.com>
Cc: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu,
        Raphael Gault <raphael.gault@arm.com>,
        Sami Mujawar <sami.mujawar@arm.com>,
        Alexandru Elisei <Alexandru.Elisei@arm.com>,
        Ard Biesheuvel <ardb@kernel.org>
Subject: [PATCH kvmtool v4 0/5] Add CFI flash emulation
Date: Thu, 23 Apr 2020 18:38:39 +0100
Message-Id: <20200423173844.24220-1-andre.przywara@arm.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

an update for the CFI flash emulation, addressing Alex' comments and
adding direct mapping support.
The actual code changes to the flash emulation are minimal, mostly this
is about renaming and cleanups.
This versions now adds some patches. 1/5 is a required fix, the last
three patches add mapping support as an extension. See below.

In addition to a branch with this series[1], I also put a git branch with
all the changes compared to v3[2] as separate patches on the server, please
have a look if you want to verify against a previous review.

===============
The EDK II UEFI firmware implementation requires some storage for the EFI
variables, which is typically some flash storage.
Since this is already supported on the EDK II side, and looks like a
generic standard, this series adds a CFI flash emulation to kvmtool.

Patch 2/5 is the actual emulation code, patch 1/5 is a bug-fix for
registering MMIO devices, which is needed for this device.
Patches 3-5 add support for mapping the flash memory into guest, should
it be in read-array mode. For this to work, patch 3/5 is cherry-picked
from Alex' PCIe reassignable BAR series, to support removing a memslot
mapping. Patch 4/5 adds support for read-only mappings, while patch 5/5
adds or removes the mapping based on the current state.
I am happy to squash 5/5 into 2/5, if we agree that patch 3/5 should be
merged either separately or the PCIe series is actually merged before
this one.

This is one missing piece towards a working UEFI boot with kvmtool on
ARM guests, the other is to provide writable PCI BARs, which is WIP.
This series alone already enables UEFI boot, but only with virtio-mmio.

Cheers,
Andre

[1] http://www.linux-arm.org/git?p=kvmtool.git;a=log;h=refs/heads/cfi-flash/v4
[2] http://www.linux-arm.org/git?p=kvmtool.git;a=log;h=refs/heads/cfi-flash/v3
git://linux-arm.org/kvmtool.git (branches cfi-flash/v3 and cfi-flash/v4)

Changelog v3 .. v4:
- Rename file to cfi-flash.c (dash instead of underscore).
- Unify macro names for states, modes and commands.
- Enforce one or two chips only.
- Comment on pow2_size() function.
- Use more consistent identifier spellings.
- Assign symbols to status register values.
- Drop RCR register emulation.
- Use numerical offsets instead of names for query offsets to match spec.
- Cleanup error path and reword info message in create_flash_device_file().
- Add fix to allow non-virtio MMIO device emulations.
- Support tearing down and adding read-only memslots.
- Add read-only memslot mapping when in read mode.

Changelog v2 .. v3:
- Breaking MMIO handling into three separate functions.
- Assing the flash base address in the memory map, but stay at 32 MB for now.
  The MMIO area has been moved up to 48 MB, to never overlap with the
  flash.
- Impose a limit of 16 MB for the flash size, mostly to fit into the
  (for now) fixed memory map.
- Trim flash size down to nearest power-of-2, to match hardware.
- Announce forced flash size trimming.
- Rework the CFI query table slightly, to add the addresses as array
  indicies.
- Fix error handling when creating the flash device.
- Fix pow2_size implementation for 0 and 1 as input values.
- Fix write buffer size handling.
- Improve some comments.

Changelog v1 .. v2:
- Add locking for MMIO handling.
- Fold flash read into handler.
- Move pow2_size() into generic header.
- Spell out flash base address.
Tested-by: Ard Biesheuvel <ardb@kernel.org>
```
