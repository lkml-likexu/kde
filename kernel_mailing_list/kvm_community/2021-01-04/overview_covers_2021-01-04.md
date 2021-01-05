

#### [RFC PATCH v2 0/4] KVM: arm64: Add VLPI migration support on GICv4.1
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Mon Jan  4 08:16:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 11996315
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6D2F3C433DB
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 08:18:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 290E4207B3
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 08:18:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726210AbhADIRk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 03:17:40 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10101 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726029AbhADIRk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 03:17:40 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4D8T341WJnzMF83;
        Mon,  4 Jan 2021 16:15:44 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.196) by
 DGGEMS403-HUB.china.huawei.com (10.3.19.203) with Microsoft SMTP Server id
 14.3.498.0; Mon, 4 Jan 2021 16:16:45 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Eric Auger <eric.auger@redhat.com>,
        "Will Deacon" <will@kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <lushenming@huawei.com>
Subject: [RFC PATCH v2 0/4] KVM: arm64: Add VLPI migration support on GICv4.1
Date: Mon, 4 Jan 2021 16:16:09 +0800
Message-ID: <20210104081613.100-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.196]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In GICv4.1, migration has been supported except for (directly-injected)
VLPI. And GICv4.1 Spec explicitly gives a way to get the VLPI's pending
state (which was crucially missing in GICv4.0). So we make VLPI migration
capable on GICv4.1 in this patch set.

In order to support VLPI migration, we need to save and restore all
required configuration information and pending states of VLPIs. But
in fact, the configuration information of VLPIs has already been saved
(or will be reallocated on the dst host...) in vgic(kvm) migration.
So we only have to migrate the pending states of VLPIs specially.

Below is the related workflow in migration.

On the save path:
	In migration completion:
		pause all vCPUs
				|
		call each VM state change handler:
			pause other devices (just keep from sending interrupts, and
			such as VFIO migration protocol has already realized it [1])
					|
			flush ITS tables into guest RAM
					|
			flush RDIST pending tables (also flush VLPI state here)
				|
		...
On the resume path:
	load each device's state:
		restore ITS tables (include pending tables) from guest RAM
				|
		for other (PCI) devices (paused), if configured to have VLPIs,
		establish the forwarding paths of their VLPIs (and transfer
		the pending states from kvm's vgic to VPT here)

We have tested this series in VFIO migration, and found some related
issues in QEMU [2].

Links:
[1] vfio: UAPI for migration interface for device state:
    https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/
    commit/?id=a8a24f3f6e38103b77cf399c38eb54e1219d00d6
[2] vfio: Some fixes and optimizations for VFIO migration:
    https://patchwork.ozlabs.org/cover/1413263/

History:

v1 -> v2:
 - Get the VLPI state from the KVM side.
 - Nit fixes.

Since there seems to be no better place to transfer the pending states
in patch 3, we just keep it unchanged.

Thanks,
Shenming


Shenming Lu (3):
  KVM: arm64: GICv4.1: Add function to get VLPI state
  KVM: arm64: GICv4.1: Try to save hw pending state in
    save_pending_tables
  KVM: arm64: GICv4.1: Give a chance to save VLPI's pending state

Zenghui Yu (1):
  KVM: arm64: GICv4.1: Restore VLPI's pending state to physical side

 .../virt/kvm/devices/arm-vgic-its.rst         |  2 +-
 arch/arm64/kvm/vgic/vgic-its.c                |  6 +-
 arch/arm64/kvm/vgic/vgic-v3.c                 | 58 +++++++++++++++++--
 arch/arm64/kvm/vgic/vgic-v4.c                 | 36 ++++++++++++
 arch/arm64/kvm/vgic/vgic.h                    |  1 +
 5 files changed, 93 insertions(+), 10 deletions(-)
```
#### [PATCH v3 00/17] KVM: x86/pmu: Add support to enable Guest PEBS via
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Mon Jan  4 13:15:25 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11996723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C5B47C4332B
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 13:24:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFBA1207AE
	for <kvm@archiver.kernel.org>; Mon,  4 Jan 2021 13:24:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727071AbhADNXp (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 4 Jan 2021 08:23:45 -0500
Received: from mga07.intel.com ([134.134.136.100]:23242 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726670AbhADNXp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 4 Jan 2021 08:23:45 -0500
IronPort-SDR: 
 z3GaPBpNJXsp3hPwymkFdKkGh4l7rgaWDTqIRgyRe6G0uwFvusOIdtN1DW06KozexoOPqJuZVD
 1EXxE5CwSsxw==
X-IronPort-AV: E=McAfee;i="6000,8403,9853"; a="241034275"
X-IronPort-AV: E=Sophos;i="5.78,474,1599548400";
   d="scan'208";a="241034275"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 04 Jan 2021 05:21:58 -0800
IronPort-SDR: 
 lzkg6p1+6NNiOiPW0WCngqzsAykXSvhzo6MF0xRaVv+20Y4hbGs1eCqQOjmuombyCV/BN9xHlb
 OGno8NOe65Uw==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.78,474,1599548400";
   d="scan'208";a="461944497"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga001.fm.intel.com with ESMTP; 04 Jan 2021 05:21:55 -0800
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>, eranian@google.com,
        kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Andi Kleen <andi@firstfloor.org>,
        Kan Liang <kan.liang@linux.intel.com>, wei.w.wang@intel.com,
        luwei.kang@intel.com, linux-kernel@vger.kernel.org
Subject: [PATCH v3 00/17] KVM: x86/pmu: Add support to enable Guest PEBS via
 DS
Date: Mon,  4 Jan 2021 21:15:25 +0800
Message-Id: <20210104131542.495413-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Precise Event Based Sampling (PEBS) facility on Intel Ice Lake Server
platforms can provide an architectural state of the instruction executed
after the guest instruction that caused the event. This patch set enables
the PEBS via DS feature for KVM guests on the Ice Lake Server.

We can use PEBS feature on the linux guest like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

The guest PEBS will be disabled on purpose when host is using PEBS. 
By default, KVM disables the co-existence of guest PEBS and host PEBS.

The whole patch set could be divided into three parts and the first two
parts enables the basic PEBS via DS feature which could be considered
to be merged and no regression about host perf is expected.

Compared to the first version, an important change here is the removal
of the forced 1-1 mapping of the virtual to physical PMC and we handle
the cross-mapping issue carefully in the part 3 which may address
artificial competition concern from PeterZ.

In general, there are 2 code paths to emulate guest PEBS facility.

1) Fast path (part 2, patch 0004-0012)

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
It works as the 1-1 mapping that we did in the first version.

2) Slow path (part 3, patch 0012-0017)

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure. 

Large PEBS needs to be disabled by KVM rewriting the
pebs_interrupt_threshold filed in DS to only one record in
the slow path.  This is because a guest may implicitly drain PEBS buffer,
e.g., context switch. KVM doesn't get a chance to update the PEBS buffer.
The physical PMC index will confuse the guest. The difficulty comes
when multiple events get rescheduled inside the guest. Hence disabling
large PEBS in this case might be an easy and safe way to keep it corrects
as an initial step here. 

We don't expect this change would break any guest 
code, which can generally tolerate
earlier PMIs. In the fast path with 1:1 mapping this is not needed.

The rewriting work is performed before delivering a vPMI to the guest to
notify the guest to read the record (before entering the guest, where
interrupt has been disabled so no counter reschedule would happen
at that point on the host).

For the DS area virtualization, the PEBS hardware is registered with the
guest virtual address (gva) of the guest DS memory.
In the past, the difficulty is that the host needs to pin the guest
DS memory, as the page fault caused by the PEBS hardware can't be fixed.
This isn't needed from ICX thanks to the hardware support.

KVM rewriting the guest DS area needs to walk the guest page tables to
translate gva to host virtual address (hva).

To reduce the translation overhead, we cache the translation on the first
time of DS memory rewriting. The cached translation is valid to use by
KVM until the guest disables PEBS (VMExits to KVM), which means the guest
may do re-allocation of the PEBS buffer next time and KVM needs
to re-walk the guest pages tables to update the cached translation.

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

v2->v3 Changelog:
- drop the counter_freezing check and disable guest PEBS when host uses PEBS;
- use kvm_read/write_guest_[offset]_cached() to reduce memory rewrite overhead;
- use GLOBAL_STATUS_BUFFER_OVF_BIT instead of 62;
- make intel_pmu_handle_event() static;
- rebased to kvm-queue d45f89f7437d;

Previous:
https://lore.kernel.org/kvm/20201109021254.79755-1-like.xu@linux.intel.com/

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
  KVM: vmx/pmu: Rewrite applicable_counters field in guest PEBS records
  KVM: x86/pmu: Save guest pebs reset values when pebs is configured
  KVM: x86/pmu: Adjust guest pebs reset values for crpss-mapped counters

 arch/x86/events/intel/core.c     |  45 +++++
 arch/x86/events/intel/ds.c       |  62 +++++++
 arch/x86/include/asm/kvm_host.h  |  18 ++
 arch/x86/include/asm/msr-index.h |   6 +
 arch/x86/kvm/pmu.c               |  92 +++++++--
 arch/x86/kvm/pmu.h               |  20 ++
 arch/x86/kvm/vmx/capabilities.h  |  17 +-
 arch/x86/kvm/vmx/pmu_intel.c     | 310 ++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c           |  29 +++
 arch/x86/kvm/x86.c               |  12 +-
 10 files changed, 592 insertions(+), 19 deletions(-)
```
