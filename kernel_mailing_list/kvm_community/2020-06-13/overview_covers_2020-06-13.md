

#### [PATCH v12 00/11] Guest Last Branch Recording Enabling
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Sat Jun 13 08:09:45 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11602583
Return-Path: <SRS0=SoHH=72=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F755618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B062207DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 13 Jun 2020 08:11:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726432AbgFMIK7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 13 Jun 2020 04:10:59 -0400
Received: from mga14.intel.com ([192.55.52.115]:29194 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725783AbgFMIK5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 13 Jun 2020 04:10:57 -0400
IronPort-SDR: 
 M+w4/YBj08MjvEhjWu0J/f0zFpE2omLQyalwQVf3kKnbhA8NXyvYkNKFZN8PUICibEl3GtJiPi
 KxDHyTrY1cMA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 13 Jun 2020 01:10:57 -0700
IronPort-SDR: 
 qshJJZDYaukelPetm3Jrr0NyCRhfa96f4HEIP5dLSs3cMKpry0O8Dgx4vx42etajZUvk6fjSEW
 LGuwaml+1asQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,506,1583222400";
   d="scan'208";a="474467288"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga006.fm.intel.com with ESMTP; 13 Jun 2020 01:10:52 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, ak@linux.intel.com,
        wei.w.wang@intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v12 00/11] Guest Last Branch Recording Enabling
Date: Sat, 13 Jun 2020 16:09:45 +0800
Message-Id: <20200613080958.132489-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Please help review this new version for the Kenrel 5.9 release.

Now, you may apply the last two qemu-devel patches to the upstream
qemu and try the guest LBR feature with '-cpu host' command line.

v11->v12 Changelog:
- apply "Signed-off-by" form PeterZ and his codes for the perf subsystem;
- add validity checks before expose LBR via MSR_IA32_PERF_CAPABILITIES;
- refactor MSR_IA32_DEBUGCTLMSR emulation with validity check;
- reorder "perf_event_attr" fields according to how they're declared;
- replace event_is_oncpu() with "event->state" check;
- make LBR emualtion specific to vmx rather than x86 generic;
- move pass-through LBR code to vmx.c instead of pmu_intel.c;
- add vmx_lbr_en/disable_passthrough layer to make code readable;
- rewrite pmu availability check with vmx_passthrough_lbr_msrs();

You may check more details in each commit.

Previous:
https://lore.kernel.org/kvm/20200514083054.62538-1-like.xu@linux.intel.com/
---

The last branch recording (LBR) is a performance monitor unit (PMU)
feature on Intel processors that records a running trace of the most
recent branches taken by the processor in the LBR stack. This patch
series is going to enable this feature for plenty of KVM guests.

The userspace could configure whether it's enabled or not for each
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
  perf/x86/core: Refactor hw->idx checks and cleanup
  perf/x86/lbr: Add interface to get LBR information
  perf/x86: Add constraint to create guest LBR event without hw counter
  perf/x86: Keep LBR records unchanged in host context for guest usage
  KVM: vmx/pmu: Expose LBR to guest via MSR_IA32_PERF_CAPABILITIES
  KVM: vmx/pmu: Unmask LBR fields in the MSR_IA32_DEBUGCTLMSR emualtion
  KVM: vmx/pmu: Pass-through LBR msrs when guest LBR event is scheduled
  KVM: vmx/pmu: Emulate legacy freezing LBRs on virtual PMI
  KVM: vmx/pmu: Reduce the overhead of LBR pass-through or cancellation
  KVM: vmx/pmu: Release guest LBR event via lazy release mechanism

Wei Wang (1):
  perf/x86: Fix variable types for LBR registers

Qemu-devel:
  target/i386: define a MSR based feature word - FEAT_PERF_CAPABILITIES
  target/i386: add -cpu,lbr=true support to enable guest LBR

 arch/x86/events/core.c            |  26 +--
 arch/x86/events/intel/core.c      | 109 ++++++++-----
 arch/x86/events/intel/lbr.c       |  51 +++++-
 arch/x86/events/perf_event.h      |   8 +-
 arch/x86/include/asm/perf_event.h |  34 +++-
 arch/x86/kvm/pmu.c                |  12 +-
 arch/x86/kvm/pmu.h                |   5 +
 arch/x86/kvm/vmx/capabilities.h   |  23 ++-
 arch/x86/kvm/vmx/pmu_intel.c      | 253 +++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |  86 +++++++++-
 arch/x86/kvm/vmx/vmx.h            |  17 ++
 arch/x86/kvm/x86.c                |  13 --
 12 files changed, 559 insertions(+), 78 deletions(-)
```
