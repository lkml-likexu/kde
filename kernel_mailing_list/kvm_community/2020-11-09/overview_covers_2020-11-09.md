

#### [PATCH RFC v2 00/17] KVM: x86/pmu: Add support to enable Guest PEBS
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon Nov  9 02:12:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11890309
Return-Path: <SRS0=zqVv=EP=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=no autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9BA87C56201
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 59815206E3
	for <kvm@archiver.kernel.org>; Mon,  9 Nov 2020 02:16:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729080AbgKICQu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 8 Nov 2020 21:16:50 -0500
Received: from mga01.intel.com ([192.55.52.88]:64875 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728006AbgKICQu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 8 Nov 2020 21:16:50 -0500
IronPort-SDR: 
 cydSXvtAB7ITKVZ3/N01yR4Ub1rjyqMlmi0LCWhzT6oCJyXKhjqX22EfXxg6FXwkEgL9e/JJx4
 5JnvKXFsSmpw==
X-IronPort-AV: E=McAfee;i="6000,8403,9799"; a="187684535"
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="187684535"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga101.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Nov 2020 18:16:49 -0800
IronPort-SDR: 
 0isBKzzx4pbgmXS6CNxAlimbfIJmLVm3/pD/NOnTEAG5/wgQbLuX7BUMI+2mQtqsjNNKGYXWII
 CBxqjP5wc+Lw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.77,462,1596524400";
   d="scan'208";a="540646088"
Received: from e5-2699-v4-likexu.sh.intel.com ([10.239.48.39])
  by orsmga005.jf.intel.com with ESMTP; 08 Nov 2020 18:16:45 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Kan Liang <kan.liang@linux.intel.com>, luwei.kang@intel.com,
        Thomas Gleixner <tglx@linutronix.de>, wei.w.wang@intel.com,
        Tony Luck <tony.luck@intel.com>,
        Stephane Eranian <eranian@google.com>,
        Mark Gross <mgross@linux.intel.com>,
        Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH RFC v2 00/17] KVM: x86/pmu: Add support to enable Guest PEBS
 via DS
Date: Mon,  9 Nov 2020 10:12:37 +0800
Message-Id: <20201109021254.79755-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Precise Event Based Sampling(PEBS) supported on Intel Ice Lake server
platforms can provide an architectural state of the instruction executed
after the instruction that caused the event. This patch set enables the
the PEBS via DS feature for KVM (also non) Linux guest on the Ice Lake.
The Linux guest can use PEBS feature like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

If the counter_freezing is not enabled on the host, the guest PEBS will
be disabled on purpose when host is using PEBS facility. By default,
KVM disables the co-existence of guest PEBS and host PEBS.

The whole patch set could be divided into three parts and the first two
parts enables the basic PEBS via DS feature which could be considered
to be merged and no regression about host perf is expected.

- part 1: patch 0001-0003: preparation and minor fixes for vPMU overall;
- part 2: patch 0004-0012: enable guest PEBS when the guest PEBS counters
are not cross-mapped, which is the most usual case in practice;
- part 3: patch 0012-0017: enable guest PEBS when cross-mapping happens;

Compared to the first version, an important change here is the removal
of the forced 1-1 mapping of the virtual to physical PMC and we handle
the cross-mapping issue carefully in the part 3 which may address
artificial competition concern from PeterZ.

In general, there are 2 code paths to emulate guest PEBS facility.

1) Fast path (part 2)

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
It works as the 1-1 mapping that we did in the first version.

2) Slow path (part 3)

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure. Large PEBS
needs to be disabled by KVM rewriting the pebs_interrupt_threshold
filed in DS to only one record in the slow path. 

This is because a guest may implicitly drain PEBS buffer, e.g.,
context switch. KVM doesn't get a chance to update the PEBS buffer.
The physical PMC index will confuse the guest. The difficulty comes
when multiple events get rescheduled inside the guest.

Hence disabling large PEBS in this case might be an easy and safe way
to keep it corrects as an initial step here. 

We don't expect this to break any guest code, which can generally tolerate
earlier PMIs. In the fast path with 1:1 mapping this is not needed.

The rewriting work is performed before delivering a vPMI to the guest to
notify the guest to read the record (before entering the guest, where
interrupt has been disabled so no counter reschedule would happen
at that point on the host).

In summary, this patch set enables the guest PEBS to retrieve the correct
information from its own PEBS records on the Ice Lake server platforms
when host is not using PEBS facility at the same time. And we expect it
should work when migrating to another Ice Lake.

Here are the results of pebs test from guest/host for same workload:

perf report on guest:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1473377250
# Overhead  Command   Shared Object      Symbol
  57.74%  br_instr  br_instr           [.] lfsr_cond
  41.40%  br_instr  br_instr           [.] cmp_end
   0.21%  br_instr  [kernel.kallsyms]  [k] __lock_acquire

perf report on host:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1462721386
# Overhead  Command   Shared Object     Symbol
  57.90%  br_instr  br_instr          [.] lfsr_cond
  41.95%  br_instr  br_instr          [.] cmp_end
   0.05%  br_instr  [kernel.vmlinux]  [k] lock_acquire
   
Conclusion: the profiling results on the guest are similar to that on the host.

Please check more details in each commit and feel free to comment.

v1->v2 Changelog:
- drop the 1:1 counter mapping proposal for PeterZ;
- *add the guest PEBS records rewrite proposal* (new patch 0013 - 0017);
- drop the co-existence of guest PEBS and host PEBS w/o counter_freezing;
- drop the auto-reload configuration for guest PEBS event;
- use attr.precise_ip = 3 for guest PEBS PDIR counter;
- move msr-switch code to perf_guest_get_msrs();
- new user interface to dis/enable guest PEBS via IA32_PERF_CAPABILITIES;
- general vPMU related fixup patches (patch 0001 - 0003);
- rebased to the latest kvm-queue;

Previous:
https://lore.kernel.org/kvm/1583431025-19802-1-git-send-email-luwei.kang@intel.com

Like Xu (17):
  KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
  KVM: vmx/pmu: Use IA32_PERF_CAPABILITIES to adjust features visibility
  KVM: x86/pmu: Introduce the ctrl_mask value for fixed counter
  perf: x86/ds: Handle guest PEBS overflow PMI and inject it to guest
  KVM: x86/pmu: Reprogram guest PEBS event to emulate guest PEBS counter
  KVM: x86/pmu: Add IA32_PEBS_ENABLE MSR emulation for extended PEBS
  KVM: x86/pmu: Add IA32_DS_AREA MSR emulation to manage guest DS buffer
  KVM: x86/pmu: Add PEBS_DATA_CFG MSR emulation to support adaptive PEBS
  KVM: x86: Set PEBS_UNAVAIL in IA32_MISC_ENABLE when PEBS is enabled
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64
  KVM: x86/pmu: Adjust precise_ip to emulate Ice Lake guest PDIR counter
  KVM: x86/pmu: Disable guest PEBS when counters are cross-mapped
  KVM: x86/pmu: Add hook to emulate pebs for cross-mapped counters
  KVM: vmx/pmu: Limit pebs_interrupt_threshold in the guest DS area
  KVM: vmx/pmu: Rewrite applicable_counters field in the guest PEBS record
  KVM: x86/pmu: Save guest pebs reset value when a pebs counter is configured
  KVM: x86/pmu: Adjust guest DS pebs reset counter values for mapped counter

 arch/x86/events/intel/core.c     |  46 +++++
 arch/x86/events/intel/ds.c       |  64 +++++++
 arch/x86/include/asm/kvm_host.h  |  15 ++
 arch/x86/include/asm/msr-index.h |   6 +
 arch/x86/kvm/pmu.c               |  91 +++++++--
 arch/x86/kvm/pmu.h               |  20 ++
 arch/x86/kvm/vmx/capabilities.h  |  17 +-
 arch/x86/kvm/vmx/pmu_intel.c     | 313 ++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c           |  29 +++
 arch/x86/kvm/x86.c               |  12 +-
 10 files changed, 594 insertions(+), 19 deletions(-)
```
